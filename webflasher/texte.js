/** Texte der Seite in Deutsch und Englisch. Platzhalter stehen als {name}. Bezeichnungen am Gerät (UART0, POWER, BOOT, RST, USB2.0) wie aufgedruckt. */

export const TEXTE = {
  de: {
    "seite.titel": "RetroRadioCrowPanel installieren",
    "kopf.untertitel": "Fertige Firmware aus dem Browser auf das Elecrow CrowPanel Advanced ESP32-P4 mit 7, 9 oder 10,1 Zoll übertragen, zur Erstinstallation und für Updates.",
    "sprache.knopf": "English",
    "sprache.titel": "Switch to English",

    "firmware.zeile": "Firmware {version} vom {datum}",
    "firmware.laedt": "Firmwareliste wird geladen ...",

    "schritte.titel": "So geht es",
    "schritte.1": "Datenkabel in die Buchse UART0 stecken und mit dem Rechner verbinden. Schalter POWER einschalten.",
    "schritte.2": "„Verbinden“ wählen und im Fenster des Browsers den Anschluss auswählen. Er heißt meist „USB Serial“ oder trägt „CH340“ im Namen.",
    "schritte.3": "Die Seite zeigt das gefundene Gerät. „Installieren“ überträgt die Firmware und prüft sie, das dauert rund eine Minute.",
    "schritte.erhalten": "Einstellungen, PIN, WLAN-Zugangsdaten und Sender bleiben bei jedem Update erhalten. Die Firmware des WLAN-Chips wird nicht verändert.",

    "browser.fehlt": "Dieser Browser kann nicht auf serielle Anschlüsse zugreifen. Bitte Chrome, Edge oder Opera auf einem Rechner verwenden.",

    "knopf.verbinden": "Verbinden",
    "knopf.installieren": "Installieren",
    "knopf.abbrechen": "Abbrechen",
    "knopf.nochmal": "Erneut versuchen",
    "knopf.weiteres": "Weiteres Gerät",
    "option.langsam": "Langsam übertragen (115200 Baud). Nur nötig, wenn die Übertragung abbricht, sie dauert dann mehrere Minuten.",

    "status.verbinde": "Verbinde mit dem CrowPanel ...",
    "status.lade": "Lade Firmware ({mb} MB) ...",
    "status.schreibe": "Übertrage {name} ...",
    "status.pruefe": "Prüfe die geschriebenen Daten ...",
    "status.neustart": "Starte das CrowPanel neu ...",
    "status.warnung": "Kabel nicht trennen und diese Seite nicht schließen.",

    "ziel.titel": "Gefundenes Gerät",
    "ziel.chip": "Chip",
    "ziel.mac": "MAC-Adresse",
    "ziel.firmware": "Firmware",
    "ziel.chipwert": "{chip}, Revision {revision}",
    "ziel.firmwarewert": "{version} vom {datum}, passend zu dieser Revision",
    "ziel.hinweis": "Das CrowPanel wartet im Download-Modus, der Bildschirm ist dunkel. „Abbrechen“ startet es unverändert neu.",

    "fertig.titel": "Fertig",
    "fertig.text": "RetroRadioCrowPanel {version} ist installiert und geprüft. Das CrowPanel startet neu und zeigt den Sperrbildschirm.",
    "fertig.betrieb": "Das CrowPanel läuft am USB-Anschluss des Rechners weiter. Ein USB-Netzteil an USB2.0 ist nur nötig, wenn der Rechner zu wenig Strom liefert (der Bildschirm bleibt dunkel oder das Radio startet von selbst neu) oder wenn das Radio ohne Rechner laufen soll.",

    "fehler.titel": "Das hat nicht geklappt",
    "fehler.keinAnschluss": "Kein Anschluss gewählt. Erscheint in der Auswahl kein Anschluss, steckt das Kabel nicht in UART0, POWER ist aus, das Kabel ist ein reines Ladekabel oder der Treiber für den CH340 fehlt.",
    "fehler.falscherAnschluss": "Der gewählte Anschluss gehört nicht zu einem CrowPanel. Er wurde nicht geöffnet, an dem Gerät daran wurde nichts verändert. Bitte den Anschluss des Kabels an UART0 wählen.",
    "fehler.verbindung": "Das Gerät antwortet nicht. Andere Programme schließen, die den Anschluss belegen. Hilft das nicht, BOOT gedrückt halten, RST kurz drücken, BOOT loslassen und erneut verbinden.",
    "fehler.falscherChip": "Gefunden wurde ein {chip}, kein ESP32-P4. Nichts geschrieben, das Gerät startet unverändert neu.",
    "fehler.revisionUnbekannt": "Die Chiprevision ließ sich nicht lesen. Nichts geschrieben, das Gerät startet unverändert neu.",
    "fehler.keineFassung": "Für die Chiprevision {revision} gibt es keine passende Firmware. CrowPanel mit dem Platinenstand V2.0 (Chip ab v3.0, anderer Tonweg) werden noch nicht unterstützt. Nichts geschrieben, das Gerät startet unverändert neu.",
    "fehler.manifest": "Die Firmwareliste dieser Seite ließ sich nicht laden. Bitte die Seite neu laden.",
    "fehler.download": "Die Datei {name} ließ sich nicht vollständig laden. Nichts geschrieben, das CrowPanel startet unverändert neu.",
    "fehler.pruefsumme": "Die geladene Datei {name} ist beschädigt. Nichts geschrieben, das CrowPanel startet unverändert neu.",
    "fehler.abbild": "Die Datei {name} passt nicht zu diesem Chip. Nichts geschrieben, das CrowPanel startet unverändert neu.",
    "fehler.schreiben": "Die Übertragung ist abgebrochen. Das CrowPanel bleibt im Download-Modus, der Bildschirm ist dunkel. Kabel prüfen und die Installation wiederholen, bei erneutem Abbruch mit „Langsam übertragen“.",
    "fehler.vergleich": "Die geschriebenen Daten weichen bei {name} von der Firmware ab. Das CrowPanel bleibt im Download-Modus, der Bildschirm ist dunkel. Bitte die Installation wiederholen.",
    "fehler.unbekannt": "Unerwarteter Fehler: {text}",

    "hilfe.titel": "Wenn etwas nicht klappt",
    "hilfe.anschluss": "Kein Anschluss in der Auswahl: Datenkabel statt Ladekabel verwenden, Buchse UART0, Schalter POWER an. Unter Windows und macOS kann der Treiber für den CH340 fehlen, unter Linux die Berechtigung für serielle Anschlüsse.",
    "hilfe.boot": "Das Gerät antwortet nicht: BOOT gedrückt halten, RST kurz drücken, BOOT loslassen, dann erneut verbinden.",
    "hilfe.dunkel": "Der Bildschirm bleibt nach einem Abbruch dunkel: RST drücken oder POWER aus- und wieder einschalten.",
    "hilfe.v2": "Platinenstand V2.0 (Aufdruck auf der Platine): Er hat einen anderen Tonweg und wird noch nicht unterstützt. Die Seite erkennt solche Geräte am Chip und schreibt nichts.",
    "hilfe.mehr": "Mehr dazu in der",
    "hilfe.fehlerhilfe": "Fehlerhilfe",
    "protokoll.titel": "Protokoll der Übertragung",

    "fuss.projekt": "Projekt und Anleitungen",
    "fuss.quelle": "Quellcode dieser Version",
    "fuss.lizenzen": "Lizenzen",
    "fuss.text": "RetroRadioCrowPanel steht unter der GPL-3.0. Diese Seite überträgt mit esptool-js (Apache-2.0) und pako (MIT und Zlib), sie lädt nichts von fremden Servern und sendet keine Daten.",
  },
  en: {
    "seite.titel": "Install RetroRadioCrowPanel",
    "kopf.untertitel": "Put the ready-made firmware on the Elecrow CrowPanel Advanced ESP32-P4 with 7, 9 or 10.1 inches straight from the browser, for the first installation and for updates.",
    "sprache.knopf": "Deutsch",
    "sprache.titel": "Auf Deutsch umschalten",

    "firmware.zeile": "Firmware {version} of {datum}",
    "firmware.laedt": "Loading the firmware list ...",

    "schritte.titel": "How it works",
    "schritte.1": "Plug the data cable into the UART0 socket and connect it to the computer. Switch POWER on.",
    "schritte.2": "Choose “Connect” and select the port in the browser window. It is usually called “USB Serial” or has “CH340” in its name.",
    "schritte.3": "The page shows the device it found. “Install” transfers the firmware and verifies it, which takes about a minute.",
    "schritte.erhalten": "Settings, PIN, Wi-Fi credentials and stations are kept with every update. The firmware of the Wi-Fi chip is not changed.",

    "browser.fehlt": "This browser cannot access serial ports. Please use Chrome, Edge or Opera on a computer.",

    "knopf.verbinden": "Connect",
    "knopf.installieren": "Install",
    "knopf.abbrechen": "Cancel",
    "knopf.nochmal": "Try again",
    "knopf.weiteres": "Another device",
    "option.langsam": "Transfer slowly (115200 baud). Only needed if the transfer breaks off, it then takes several minutes.",

    "status.verbinde": "Connecting to the CrowPanel ...",
    "status.lade": "Loading firmware ({mb} MB) ...",
    "status.schreibe": "Transferring {name} ...",
    "status.pruefe": "Verifying the written data ...",
    "status.neustart": "Restarting the CrowPanel ...",
    "status.warnung": "Do not unplug the cable and do not close this page.",

    "ziel.titel": "Device found",
    "ziel.chip": "Chip",
    "ziel.mac": "MAC address",
    "ziel.firmware": "Firmware",
    "ziel.chipwert": "{chip}, revision {revision}",
    "ziel.firmwarewert": "{version} of {datum}, matching this revision",
    "ziel.hinweis": "The CrowPanel is waiting in download mode, its screen is dark. “Cancel” restarts it unchanged.",

    "fertig.titel": "Done",
    "fertig.text": "RetroRadioCrowPanel {version} is installed and verified. The CrowPanel restarts and shows the lock screen.",
    "fertig.betrieb": "The CrowPanel keeps running on the USB port of the computer. A USB power supply at USB2.0 is only needed if the computer delivers too little power (the screen stays dark or the radio restarts by itself) or if the radio is to run without a computer.",

    "fehler.titel": "That did not work",
    "fehler.keinAnschluss": "No port selected. If the list shows no port, the cable is not in UART0, POWER is off, the cable is a charging-only cable or the driver for the CH340 is missing.",
    "fehler.falscherAnschluss": "The selected port does not belong to a CrowPanel. It was not opened, nothing was changed on the device behind it. Please choose the port of the cable at UART0.",
    "fehler.verbindung": "The device does not answer. Close other programs that use the port. If that does not help, hold BOOT, press RST briefly, release BOOT and connect again.",
    "fehler.falscherChip": "Found a {chip}, not an ESP32-P4. Nothing was written, the device restarts unchanged.",
    "fehler.revisionUnbekannt": "The chip revision could not be read. Nothing was written, the device restarts unchanged.",
    "fehler.keineFassung": "There is no matching firmware for chip revision {revision}. CrowPanels with board version V2.0 (chip v3.0 or newer, different audio path) are not supported yet. Nothing was written, the device restarts unchanged.",
    "fehler.manifest": "The firmware list of this page could not be loaded. Please reload the page.",
    "fehler.download": "The file {name} could not be loaded completely. Nothing was written, the CrowPanel restarts unchanged.",
    "fehler.pruefsumme": "The loaded file {name} is damaged. Nothing was written, the CrowPanel restarts unchanged.",
    "fehler.abbild": "The file {name} does not match this chip. Nothing was written, the CrowPanel restarts unchanged.",
    "fehler.schreiben": "The transfer broke off. The CrowPanel stays in download mode, its screen is dark. Check the cable and repeat the installation, with “Transfer slowly” if it breaks off again.",
    "fehler.vergleich": "The written data differs from the firmware at {name}. The CrowPanel stays in download mode, its screen is dark. Please repeat the installation.",
    "fehler.unbekannt": "Unexpected error: {text}",

    "hilfe.titel": "If something goes wrong",
    "hilfe.anschluss": "No port in the list: use a data cable instead of a charging cable, the UART0 socket, POWER switched on. On Windows and macOS the driver for the CH340 may be missing, on Linux the permission for serial ports.",
    "hilfe.boot": "The device does not answer: hold BOOT, press RST briefly, release BOOT, then connect again.",
    "hilfe.dunkel": "The screen stays dark after an abort: press RST or switch POWER off and on again.",
    "hilfe.v2": "Board version V2.0 (printed on the board): it has a different audio path and is not supported yet. The page recognises such devices by their chip and writes nothing.",
    "hilfe.mehr": "More in the",
    "hilfe.fehlerhilfe": "troubleshooting guide (German)",
    "protokoll.titel": "Transfer log",

    "fuss.projekt": "Project and manuals (German)",
    "fuss.quelle": "Source code of this version",
    "fuss.lizenzen": "Licences",
    "fuss.text": "RetroRadioCrowPanel is licensed under the GPL-3.0. This page transfers with esptool-js (Apache-2.0) and pako (MIT and Zlib), it loads nothing from other servers and sends no data.",
  },
};

/** Text eines Schlüssels in der Sprache, Platzhalter {name} aus werte gefüllt. Ein unbekannter Schlüssel kommt selbst zurück, damit eine Lücke auffällt. */
export function text(sprache, schluessel, werte = {}) {
  const vorlage = TEXTE[sprache]?.[schluessel] ?? TEXTE.de[schluessel] ?? schluessel;
  return vorlage.replace(/\{(\w+)\}/g, (ganz, name) => (name in werte ? String(werte[name]) : ganz));
}
