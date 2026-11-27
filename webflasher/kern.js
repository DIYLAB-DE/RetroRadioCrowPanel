/** Prüf- und Auswahlregeln des Web-Flashers. Ohne Gerät und ohne Seite benutzbar, damit sie sich einzeln testen lassen. */

export const CHIP_NAME = "ESP32-P4";
export const MANIFEST_FORMAT = 1;
const ABBILD_MAGIC = 0xe9; // erstes Byte eines ESP-Abbilds (Bootloader, Anwendung)
const ABBILD_CHIP_ID = 18; // Kennung des ESP32-P4 im Abbildkopf
const ABBILD_KOPF_BYTES = 24;
const SEKTOR = 0x1000; // Schreibadressen liegen auf Flash-Sektorgrenzen

/** USB-Kennungen des Wandlers an UART0 (CH340K und CH340), dieselben wie im geprüften Upload. */
export const CH340_KENNUNGEN = [
  { usbVendorId: 0x1a86, usbProductId: 0x7522 },
  { usbVendorId: 0x1a86, usbProductId: 0x7523 },
];

/** Fehler mit Textschlüssel für die Oberfläche. werte füllt die Platzhalter des Textes, geschrieben sagt, ob schon in den Flash geschrieben wurde. */
export class FlasherFehler extends Error {
  constructor(schluessel, werte = {}, geschrieben = false) {
    super(schluessel);
    this.name = "FlasherFehler";
    this.schluessel = schluessel;
    this.werte = werte;
    this.geschrieben = geschrieben;
  }
}

function ganzzahl(wert, minimum = 0) {
  return Number.isInteger(wert) && wert >= minimum;
}

function hexText(wert, stellen) {
  return typeof wert === "string" && wert.length === stellen && /^[0-9a-f]+$/.test(wert);
}

/** Ein Pfad im Manifest bleibt unterhalb des Manifestordners: relativ, ohne Schema, ohne "..". */
function pfadErlaubt(pfad) {
  return typeof pfad === "string" && pfad.length > 0 && !/^[\/\\]|[:\\]|(^|\/)\.\.(\/|$)/.test(pfad);
}

/**
 * Ob ein gewählter Anschluss der USB-Seriell-Wandler eines CrowPanel sein kann. Alles andere wird nicht geöffnet: Espressif-Boards mit USB-Serial-JTAG (303a:1001), andere Wandler und Anschlüsse ohne USB-Kennung.
 * @param {{usbVendorId?: number, usbProductId?: number} | null | undefined} info Rückgabe von SerialPort.getInfo()
 */
export function istCrowPanelAnschluss(info) {
  return CH340_KENNUNGEN.some((kennung) => kennung.usbVendorId === info?.usbVendorId && kennung.usbProductId === info?.usbProductId);
}

/**
 * Prüft ein geladenes Manifest und gibt es unverändert zurück.
 * Verlangt genau die Felder, die beim Zusammenstellen der Seite geschrieben werden. Revisionen stehen wie bei esptool als Haupt * 100 + Neben.
 * @throws {FlasherFehler} fehler.manifest mit dem Grund in werte.grund
 */
export function pruefeManifest(manifest) {
  const ablehnen = (grund) => {
    throw new FlasherFehler("fehler.manifest", { grund });
  };
  if (manifest === null || typeof manifest !== "object") ablehnen("kein Objekt");
  if (manifest.format !== MANIFEST_FORMAT) ablehnen("unbekanntes Format");
  if (manifest.chip !== CHIP_NAME) ablehnen("anderer Chip");
  for (const feld of ["version", "datum", "quelle"]) {
    if (typeof manifest[feld] !== "string" || manifest[feld] === "") ablehnen(`${feld} fehlt`);
  }
  if (!/^https:\/\//.test(manifest.quelle)) ablehnen("quelle ist keine https-Adresse");
  if (!Array.isArray(manifest.fassungen) || manifest.fassungen.length === 0) ablehnen("keine Fassungen");
  const bereiche = [];
  for (const fassung of manifest.fassungen) {
    if (typeof fassung.umgebung !== "string" || fassung.umgebung === "") ablehnen("umgebung fehlt");
    if (!ganzzahl(fassung.revision_von) || !ganzzahl(fassung.revision_bis, fassung.revision_von)) ablehnen(`Revisionsbereich von ${fassung.umgebung}`);
    if (bereiche.some(([von, bis]) => fassung.revision_von <= bis && von <= fassung.revision_bis)) ablehnen("Revisionsbereiche überschneiden sich");
    bereiche.push([fassung.revision_von, fassung.revision_bis]);
    if (!Array.isArray(fassung.dateien) || fassung.dateien.length === 0) ablehnen(`keine Dateien in ${fassung.umgebung}`);
    let ende = 0;
    for (const datei of fassung.dateien) {
      if (typeof datei.name !== "string" || datei.name === "") ablehnen("Dateiname fehlt");
      if (!pfadErlaubt(datei.pfad)) ablehnen(`Pfad von ${datei.name}`);
      if (!ganzzahl(datei.adresse) || datei.adresse % SEKTOR !== 0) ablehnen(`Adresse von ${datei.name}`);
      // Vielfache von 4: esptool-js füllt sonst mit 0xFF auf, und die Prüfsumme der Datei gälte nicht mehr für den Flash.
      if (!ganzzahl(datei.groesse, 1) || datei.groesse % 4 !== 0) ablehnen(`Größe von ${datei.name}`);
      if (!hexText(datei.sha256, 64) || !hexText(datei.md5, 32)) ablehnen(`Prüfsumme von ${datei.name}`);
      if (datei.adresse < ende) ablehnen(`${datei.name} überschneidet die Datei davor`);
      ende = datei.adresse + datei.groesse;
    }
  }
  return manifest;
}

/** Die Fassung, deren Revisionsbereich die Chiprevision (Haupt * 100 + Neben) enthält, sonst null. */
export function waehleFassung(manifest, revision) {
  return manifest.fassungen.find((fassung) => fassung.revision_von <= revision && revision <= fassung.revision_bis) ?? null;
}

/**
 * Liest Chipkennung und Revisionsbereich aus dem Kopf eines ESP-Abbilds.
 * @param {Uint8Array} daten
 * @returns {{chipId: number, revisionVon: number, revisionBis: number} | null} null für Dateien ohne Abbildkopf wie die Partitionstabelle
 */
export function leseAbbildkopf(daten) {
  if (daten.length < ABBILD_KOPF_BYTES || daten[0] !== ABBILD_MAGIC) return null;
  const sicht = new DataView(daten.buffer, daten.byteOffset, daten.byteLength);
  return { chipId: sicht.getUint16(12, true), revisionVon: sicht.getUint16(15, true), revisionBis: sicht.getUint16(17, true) };
}

/**
 * Bricht ab, wenn ein Abbild für einen anderen Chip gebaut ist oder die Chiprevision ausschließt. Dieselbe Prüfung macht esptool vor dem Schreiben, esptool-js macht sie nicht.
 * @throws {FlasherFehler} fehler.abbild
 */
export function pruefeAbbild(daten, revision, name) {
  const kopf = leseAbbildkopf(daten);
  if (kopf === null) return;
  if (kopf.chipId !== ABBILD_CHIP_ID || revision < kopf.revisionVon || revision > kopf.revisionBis) {
    throw new FlasherFehler("fehler.abbild", { name });
  }
}

/** Chiprevision als Text, 103 wird "v1.3". */
export function formatRevision(revision) {
  return `v${Math.floor(revision / 100)}.${revision % 100}`;
}

/** MAC in Großbuchstaben mit Doppelpunkten, aus zwölf Hexziffern mit oder ohne Trennzeichen. Andere Eingaben bleiben unverändert. */
export function formatMac(mac) {
  const ziffern = String(mac).replace(/[:-]/g, "").toUpperCase();
  return /^[0-9A-F]{12}$/.test(ziffern) ? ziffern.match(/../g).join(":") : String(mac);
}

/** Größe in MB mit einer Nachkommastelle und dem Dezimalzeichen der Sprache. */
export function formatMegabyte(bytes, sprache) {
  return (bytes / (1024 * 1024)).toLocaleString(sprache, { minimumFractionDigits: 1, maximumFractionDigits: 1 });
}

/** SHA-256 als Kleinbuchstaben-Hex. Braucht die Web-Crypto-Schnittstelle, die Browser nur über https und localhost anbieten. */
export async function sha256Hex(daten) {
  const summe = new Uint8Array(await crypto.subtle.digest("SHA-256", daten));
  return Array.from(summe, (byte) => byte.toString(16).padStart(2, "0")).join("");
}

/**
 * Gesamtfortschritt einer Übertragung zwischen 0 und 1.
 * @param {number[]} groessen Dateigrößen in Schreibreihenfolge
 * @param {number} index Datei, die gerade geschrieben wird
 * @param {number} geschrieben gesendete Bytes dieser Datei, komprimiert gezählt
 * @param {number} gesamt komprimierte Größe dieser Datei
 */
export function gesamtFortschritt(groessen, index, geschrieben, gesamt) {
  const summe = groessen.reduce((a, b) => a + b, 0);
  if (summe === 0) return 0;
  const davor = groessen.slice(0, index).reduce((a, b) => a + b, 0);
  const anteil = gesamt > 0 ? Math.min(geschrieben / gesamt, 1) : 0;
  return Math.min((davor + anteil * (groessen[index] ?? 0)) / summe, 1);
}
