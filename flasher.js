/** Oberfläche und Ablauf des Web-Flashers: Firmwareliste laden, Gerät zeigen, Dateien laden und prüfen, schreiben, vergleichen, neu starten. Die Reihenfolge der Prüfungen folgt dem geprüften Upload in scripts/crowpanel_geraet.py. */

import { CHIP_NAME, FIREFOX_AB, FlasherFehler, formatMac, formatMegabyte, formatRevision, gesamtFortschritt, pruefeAbbild, pruefeManifest, sha256Hex, waehleFassung } from "./kern.js";
import { TEXTE, text } from "./texte.js";

const MANIFEST = "firmware/manifest.json";
const BAUD_SCHNELL = 921600; // wie der geprüfte Upload
const BAUD_LANGSAM = 115200;
const SPRACHE_SCHLUESSEL = "webflasher.sprache";
const PROTOKOLL_ZEICHEN = 200000; // ältere Zeilen fallen weg, damit die Seite bei langen Übertragungen nicht wächst
const ANSICHTEN = ["Start", "Beschaeftigt", "Ziel", "Fertig", "Fehler"];

/**
 * Verbindet die Seite mit dem Gerätezugriff und zeigt die Startansicht.
 * @param {{browserHinweis: () => string | null, verbindeGeraet: (optionen: {baud: number, protokoll: (text: string) => void}) => Promise<object>}} zugriff im Betrieb die Funktionen aus geraet.js, im Test eine Attrappe mit denselben Rückgaben
 */
export async function starte({ browserHinweis, verbindeGeraet }) {
  const el = (id) => document.getElementById(id);
  const manifestUrl = new URL(MANIFEST, document.baseURI);
  let sprache = waehleSprache();
  let manifest = null;
  let geraet = null;
  let fassung = null;
  let beschaeftigt = false;
  // Textschlüssel, wenn der Browser nicht freigegeben ist. Dann bleibt „Verbinden“ gesperrt.
  const hinweis = browserHinweis();

  function waehleSprache() {
    let gespeichert = null;
    try {
      gespeichert = localStorage.getItem(SPRACHE_SCHLUESSEL);
    } catch {
      // Ohne Speicherzugriff gilt die Sprache des Browsers.
    }
    if (gespeichert in TEXTE) return gespeichert;
    return (navigator.language || "de").toLowerCase().startsWith("de") ? "de" : "en";
  }

  /** Merkt Schlüssel und Werte am Element, damit ein Sprachwechsel auch laufende Meldungen übersetzt. */
  function setze(element, schluessel, werte = {}) {
    element.dataset.i18n = schluessel;
    element.dataset.i18nWerte = JSON.stringify(werte);
    element.textContent = text(sprache, schluessel, werte);
  }

  function uebersetze() {
    document.documentElement.lang = sprache;
    document.title = text(sprache, "seite.titel");
    for (const element of document.querySelectorAll("[data-i18n]")) {
      element.textContent = text(sprache, element.dataset.i18n, JSON.parse(element.dataset.i18nWerte || "{}"));
    }
    for (const element of document.querySelectorAll("[data-i18n-title]")) {
      element.title = text(sprache, element.dataset.i18nTitle);
    }
  }

  function zeige(ansicht) {
    for (const name of ANSICHTEN) el(`ansicht${name}`).hidden = name !== ansicht;
  }

  function protokoll(zeile) {
    const feld = el("protokoll");
    const inhalt = feld.textContent + zeile;
    feld.textContent = inhalt.length > PROTOKOLL_ZEICHEN ? inhalt.slice(-PROTOKOLL_ZEICHEN) : inhalt;
    feld.scrollTop = feld.scrollHeight;
  }

  function zeigeFehler(fehler) {
    if (fehler instanceof FlasherFehler) {
      setze(el("fehlerText"), fehler.schluessel, fehler.werte);
    } else {
      protokoll(`${fehler?.stack || fehler}\n`);
      setze(el("fehlerText"), "fehler.unbekannt", { text: String(fehler?.message || fehler) });
    }
    zeige("Fehler");
  }

  /** Gibt den Anschluss frei. Ein Neustart nur, solange nichts geschrieben wurde oder alles geprüft ist, sonst liefe ein halb geschriebenes Abbild an. */
  async function gibFrei(neuStarten) {
    const altes = geraet;
    geraet = null;
    if (altes === null) return;
    if (neuStarten) await altes.neustart();
    await altes.trenne();
  }

  async function ladeManifest() {
    setze(el("firmware"), "firmware.laedt");
    try {
      const antwort = await fetch(manifestUrl, { cache: "no-store" });
      if (!antwort.ok) throw new Error(`HTTP ${antwort.status}`);
      manifest = pruefeManifest(await antwort.json());
    } catch (fehler) {
      protokoll(`Firmwareliste: ${fehler instanceof FlasherFehler ? fehler.werte.grund : fehler}\n`);
      el("firmware").classList.add("fehler");
      setze(el("firmware"), "fehler.manifest");
      return;
    }
    setze(el("firmware"), "firmware.zeile", { version: manifest.version, datum: manifest.datum });
    el("linkQuelle").href = manifest.quelle;
    el("verbinden").disabled = hinweis !== null;
  }

  async function ladeDatei(datei) {
    let daten;
    try {
      const antwort = await fetch(new URL(datei.pfad, manifestUrl));
      if (!antwort.ok) throw new Error(`HTTP ${antwort.status}`);
      daten = new Uint8Array(await antwort.arrayBuffer());
    } catch (fehler) {
      protokoll(`${datei.pfad}: ${fehler}\n`);
      throw new FlasherFehler("fehler.download", { name: datei.name });
    }
    if (daten.length !== datei.groesse) throw new FlasherFehler("fehler.download", { name: datei.name });
    if ((await sha256Hex(daten)) !== datei.sha256) throw new FlasherFehler("fehler.pruefsumme", { name: datei.name });
    pruefeAbbild(daten, geraet.revision, datei.name);
    protokoll(`${datei.name}: ${daten.length} Bytes geladen, SHA-256 stimmt\n`);
    return daten;
  }

  async function verbinde() {
    el("balken").removeAttribute("value");
    el("warnung").hidden = true;
    setze(el("status"), "status.verbinde");
    zeige("Beschaeftigt");
    try {
      geraet = await verbindeGeraet({ baud: el("langsam").checked ? BAUD_LANGSAM : BAUD_SCHNELL, protokoll });
    } catch (fehler) {
      geraet = null;
      zeigeFehler(fehler);
      return;
    }
    try {
      if (geraet.chip !== CHIP_NAME) throw new FlasherFehler("fehler.falscherChip", { chip: geraet.chip });
      if (geraet.revision === null) throw new FlasherFehler("fehler.revisionUnbekannt");
      fassung = waehleFassung(manifest, geraet.revision);
      if (fassung === null) throw new FlasherFehler("fehler.keineFassung", { revision: formatRevision(geraet.revision) });
    } catch (fehler) {
      await gibFrei(true);
      zeigeFehler(fehler);
      return;
    }
    setze(el("zielChip"), "ziel.chipwert", { chip: geraet.chip, revision: formatRevision(geraet.revision) });
    el("zielMac").textContent = formatMac(geraet.mac);
    setze(el("zielFirmware"), "ziel.firmwarewert", { version: manifest.version, datum: manifest.datum });
    zeige("Ziel");
  }

  async function installiere() {
    const groessen = fassung.dateien.map((datei) => datei.groesse);
    let geschrieben = false;
    beschaeftigt = true;
    el("balken").removeAttribute("value");
    el("warnung").hidden = false;
    setze(el("status"), "status.lade", { mb: formatMegabyte(groessen.reduce((a, b) => a + b, 0), sprache) });
    zeige("Beschaeftigt");
    try {
      const dateien = [];
      for (const datei of fassung.dateien) dateien.push({ ...datei, daten: await ladeDatei(datei) });
      geschrieben = true;
      el("balken").value = 0;
      let gemeldet = -1;
      await geraet.schreibe(dateien, (index, bytes, gesamt) => {
        if (index !== gemeldet) {
          gemeldet = index;
          setze(el("status"), "status.schreibe", { name: dateien[index].name });
        }
        el("balken").value = gesamtFortschritt(groessen, index, bytes, gesamt);
      });
      el("balken").removeAttribute("value");
      setze(el("status"), "status.pruefe");
      for (const datei of dateien) {
        const summe = await geraet.md5(datei.adresse, datei.groesse);
        protokoll(`Vergleich ${datei.name}: MD5 im Flash ${summe}, erwartet ${datei.md5}\n`);
        if (summe !== datei.md5) throw new FlasherFehler("fehler.vergleich", { name: datei.name }, true);
      }
      setze(el("status"), "status.neustart");
      await gibFrei(true);
      setze(el("fertigText"), "fertig.text", { version: manifest.version });
      zeige("Fertig");
    } catch (fehler) {
      await gibFrei(!geschrieben);
      if (geschrieben && !(fehler instanceof FlasherFehler)) {
        protokoll(`${fehler?.stack || fehler}\n`);
        zeigeFehler(new FlasherFehler("fehler.schreiben", {}, true));
      } else {
        zeigeFehler(fehler);
      }
    } finally {
      beschaeftigt = false;
    }
  }

  async function brichAb() {
    el("installieren").disabled = el("abbrechen").disabled = true;
    await gibFrei(true);
    el("installieren").disabled = el("abbrechen").disabled = false;
    zeige("Start");
  }

  el("sprache").addEventListener("click", () => {
    sprache = sprache === "de" ? "en" : "de";
    try {
      localStorage.setItem(SPRACHE_SCHLUESSEL, sprache);
    } catch {
      // Ohne Speicherzugriff gilt die Wahl bis zum Schließen der Seite.
    }
    uebersetze();
  });
  el("verbinden").addEventListener("click", verbinde);
  el("installieren").addEventListener("click", installiere);
  el("abbrechen").addEventListener("click", brichAb);
  el("nochmal").addEventListener("click", () => zeige("Start"));
  el("weiteres").addEventListener("click", () => zeige("Start"));
  // Der Browser fragt nach, bevor er die Seite während einer Übertragung schließt.
  window.addEventListener("beforeunload", (ereignis) => {
    if (beschaeftigt) {
      ereignis.preventDefault();
      ereignis.returnValue = "";
    }
  });

  el("verbinden").disabled = true;
  if (hinweis !== null) setze(el("browserFehlt"), hinweis, { firefox: FIREFOX_AB });
  el("browserFehlt").hidden = hinweis === null;
  uebersetze();
  zeige("Start");
  await ladeManifest();
}
