/** Zugriff auf das CrowPanel über Web Serial und esptool-js. Nur diese Datei kennt die Bibliothek, die Seite arbeitet mit dem Objekt aus verbindeGeraet(). */

import { ESPLoader, Transport } from "./esptool-js/bundle.js";
import { CH340_KENNUNGEN, CHIP_NAME, FlasherFehler, istCrowPanelAnschluss, pruefeBrowser } from "./kern.js";

const ROM_BAUD = 115200; // Geschwindigkeit des ROM-Bootloaders vor dem Wechsel
const RESET_MS = 100; // Dauer des Resetpulses über RTS

function warte(ms) {
  return new Promise((weiter) => setTimeout(weiter, ms));
}

/**
 * Liest die Merkmale des Browsers und gibt den Textschlüssel des Hinweises zurück, null für einen freigegebenen Browser. Web Serial gibt es nur über https oder localhost. Die Markennamen nennen nur Browser auf Chromium-Grundlage, Firefox nennt seine Version in der Kennung.
 */
export function browserHinweis() {
  const daten = navigator.userAgentData;
  const firefox = /Firefox\/(\d+)/.exec(navigator.userAgent);
  return pruefeBrowser({
    firefox: firefox ? Number(firefox[1]) : null,
    serial: "serial" in navigator,
    marken: daten?.brands?.map((marke) => marke.brand) ?? null,
    mobil: daten?.mobile ?? /Android|iPhone|iPad|iPod/i.test(navigator.userAgent),
  });
}

/**
 * Lässt den Anschluss wählen, bringt das Gerät in den Download-Modus und liest Chip, Revision und MAC. Geschrieben wird dabei nichts, esptool-js lädt nur sein Hilfsprogramm in den Arbeitsspeicher.
 * Muss aus einem Klick heraus aufgerufen werden, sonst öffnet der Browser die Anschlussauswahl nicht.
 * @param {{baud: number, protokoll: (text: string) => void}} optionen Übertragungsgeschwindigkeit und Senke für die Meldungen von esptool-js
 * @returns {Promise<object>} Gerät mit chip, revision (Haupt * 100 + Neben, null wenn kein ESP32-P4), mac sowie schreibe(), md5(), neustart() und trenne()
 * @throws {FlasherFehler} fehler.keinAnschluss ohne Auswahl, fehler.falscherAnschluss bei einem Anschluss ohne CH340, fehler.verbindung wenn das Gerät nicht antwortet
 */
export async function verbindeGeraet({ baud, protokoll }) {
  let port;
  try {
    // Der Filter lässt in der Auswahl des Browsers nur den CH340 zu.
    port = await navigator.serial.requestPort({ filters: CH340_KENNUNGEN });
  } catch (fehler) {
    // NotFoundError: Auswahl geschlossen, ohne einen Anschluss zu wählen.
    if (fehler?.name === "NotFoundError") throw new FlasherFehler("fehler.keinAnschluss");
    throw fehler;
  }
  // Zweite Sperre, falls ein Browser den Filter nicht anwendet: Ein anderer Anschluss wird gar nicht erst geöffnet, das Gerät daran bleibt ungestört.
  if (!istCrowPanelAnschluss(port.getInfo())) throw new FlasherFehler("fehler.falscherAnschluss");
  const transport = new Transport(port, false);
  const terminal = { clean() {}, writeLine: (text) => protokoll(`${text}\n`), write: protokoll };
  const lader = new ESPLoader({ transport, baudrate: baud, romBaudrate: ROM_BAUD, terminal, debugLogging: false });

  const trenne = async () => {
    try {
      await transport.disconnect();
    } catch (fehler) {
      protokoll(`Trennen: ${fehler}\n`);
    }
  };
  // RTS zieht den Reset, DTR bleibt aus, sonst startete der Chip erneut im Download-Modus. Beide Leitungen werden in einem Aufruf gesetzt: Transport.setRTS() setzt DTR auf den zuletzt gemerkten Wert, und der steht nach dem Verbinden auf "an".
  const neustart = async () => {
    try {
      await transport.setSignals(false, true);
      await warte(RESET_MS);
      await transport.setSignals(false, false);
    } catch (fehler) {
      protokoll(`Neustart: ${fehler}\n`);
    }
  };

  let revision = null;
  let mac = null;
  try {
    await lader.main();
    if (lader.chip.CHIP_NAME === CHIP_NAME && !lader.secureDownloadMode) {
      revision = (await lader.chip.getMajorChipVersion(lader)) * 100 + (await lader.chip.getMinorChipVersion(lader));
      mac = await lader.chip.readMac(lader);
    }
  } catch (fehler) {
    protokoll(`${fehler}\n`);
    // Der Verbindungsversuch kann den Chip schon in den Download-Modus gebracht haben, ohne Neustart bliebe der Bildschirm dunkel.
    await neustart();
    await trenne();
    throw new FlasherFehler("fehler.verbindung");
  }

  return {
    chip: lader.chip.CHIP_NAME,
    revision,
    mac,
    /**
     * Schreibt die Dateien komprimiert und ohne Änderung am Abbildkopf, ohne vorher etwas zu löschen.
     * @param {{daten: Uint8Array, adresse: number}[]} dateien
     * @param {(index: number, geschrieben: number, gesamt: number) => void} melde Fortschritt je Datei in komprimierten Bytes
     */
    async schreibe(dateien, melde) {
      await lader.writeFlash({
        fileArray: dateien.map((datei) => ({ data: datei.daten, address: datei.adresse })),
        flashMode: "keep",
        flashFreq: "keep",
        flashSize: "keep",
        eraseAll: false,
        compress: true,
        reportProgress: melde,
      });
    },
    /** MD5 eines Flashbereichs als Kleinbuchstaben-Hex, vom Gerät berechnet. */
    async md5(adresse, groesse) {
      return String(await lader.flashMd5sum(adresse, groesse)).toLowerCase();
    },
    neustart,
    trenne,
  };
}
