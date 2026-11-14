#!/usr/bin/env python3
r"""Gerätewerkzeug für das CrowPanel Advanced (7", 9", 10.1"): Anschluss wählen, Startlog lesen, identifizieren, Flash sichern, geprüft schreiben.

Nur „schreiben“ verändert das Gerät, es läuft über den Upload von PlatformIO. Aufruf mit dem Python der Projekt-Toolchain, das esptool und pyserial mitbringt:

  .pio-core/penv/bin/python scripts/crowpanel_geraet.py port
  .pio-core/penv/bin/python scripts/crowpanel_geraet.py startlog [Sekunden]
  .pio-core/penv/bin/python scripts/crowpanel_geraet.py mitlesen [Sekunden]
  .pio-core/penv/bin/python scripts/crowpanel_geraet.py identifizieren
  .pio-core/penv/bin/python scripts/crowpanel_geraet.py sichern
  .pio-core/penv/bin/python scripts/crowpanel_geraet.py schreiben <Kernvariante> <Buildordner> <Partitionen.csv>

Unter Windows liegt das Python unter .pio-core\penv\Scripts\python, Umgebungsvariablen setzt PowerShell mit $env:CROWPANEL_PORT="COM5". Unter macOS gelten die Linux-Schreibweisen.

Bricht ein Befehl vor dem Schreiben ab, startet das CrowPanel neu, statt im Download-Modus mit dunklem Bildschirm stehen zu bleiben. Nach einem Fehler beim Schreiben bleibt es dort, damit kein halb geschriebenes Abbild startet.

Baudrate von startlog und mitlesen: Umgebungsvariable CROWPANEL_BAUD, ohne Angabe 115200.

Anschluss: Umgebungsvariable CROWPANEL_PORT oder, ohne Angabe, der einzige angeschlossene CH340. Espressif-Boards mit USB-Serial-JTAG (303a:1001) und der Programmieradapter des Bluetooth-Pico (CH9102F 1a86:55d4) werden nie gewählt.

Gerät: Mit der Umgebungsvariablen CROWPANEL_MAC (zwölf Hexziffern, Doppelpunkte und Bindestriche erlaubt) schreibt „schreiben“ nur auf das CrowPanel mit dieser P4-MAC, ein anderes startet unverändert neu. Ohne Angabe schreibt es auf jedes passende CrowPanel. Ist CROWPANEL_MAC_PFLICHT gesetzt, verlangt „schreiben“ CROWPANEL_MAC und endet ohne sie vor dem ersten Gerätezugriff. Der Upload setzt die Pflicht, wenn die unversionierte platformio_lokal.ini custom_crowpanel_mac_pflicht = ja trägt, so gilt sie nur auf diesem Rechner.

Der Entwicklungsbuild meldet an J16 zusätzlich einen CDC-Kanal (303a:0002, Produkt „RetroRadioCrowPanel10“, Seriennummer = P4-MAC). waehle_usb() findet ihn für die Bildschirmaufnahme, CROWPANEL_USB wählt bei mehreren. Flashen, startlog und mitlesen bleiben an UART0.
"""

import hashlib
import os
import re
import subprocess
import sys
import time
from pathlib import Path

import serial
from serial.tools import list_ports

CH340_VID = 0x1A86
CH340_PIDS = (0x7522, 0x7523)
AUSGESCHLOSSEN = {
    (0x303A, 0x1001): "Espressif USB-Serial-JTAG",
    (0x1A86, 0x55D4): "Programmieradapter des Bluetooth-Pico (CH9102F)",
}
PROJEKT = Path(__file__).resolve().parent.parent
MESSUNGEN = PROJEKT / ".pio" / "messungen"
RECOVERY = PROJEKT / ".pio" / "recovery"
GEN_PART = PROJEKT / ".pio-core" / "packages" / "framework-arduinoespressif32" / "tools" / "gen_esp32part.py"
LESE_BAUD = 921600
USB_VID, USB_PID = 0x303A, 0x0002  # Vorgabe des Arduino-Kerns für TinyUSB, verschieden von USB-Serial-JTAG (303a:1001)
USB_PRODUKT = "RetroRadioCrowPanel10"
# Baudrate der Anwendung, 921600 im Entwicklungsbuild mit -DCROWPANEL_USB_FERNSTEUERUNG=1. Das ROM-Log bleibt bei 115200.
APP_BAUD = int(os.environ.get("CROWPANEL_BAUD", "115200"))
# esptool schreibt Fortschrittsbalken mit █ und ░ auch in eine Pipe. Ohne PYTHONIOENCODING nähme ein Kindprozess unter Windows dafür die ANSI-Codepage, die diese Zeichen nicht kennt.
KIND_UMGEBUNG = dict(os.environ, PYTHONIOENCODING="utf-8")
TEXT = {"encoding": "utf-8", "errors": "replace"}  # Dekodierung der Ausgabe von Kindprozessen


def kandidaten():
    """Alle angeschlossenen CH340-Anschlüsse."""
    return [p for p in list_ports.comports() if p.vid == CH340_VID and p.pid in CH340_PIDS]


def beschreibe(p):
    """Eine Zeile mit Gerät, Kennung, Seriennummer und Ort am USB."""
    kennung = f"{p.vid:04x}:{p.pid:04x}" if p.vid is not None else "----:----"
    return f"{p.device}  {kennung}  Seriennummer={p.serial_number or '-'}  Ort={p.location or '-'}  {p.description or ''}"


def gleicher_anschluss(gewuenscht, geraet):
    """Vergleicht einen angegebenen Anschluss mit einem Gerätepfad. Unter Linux und macOS folgt er Links wie /dev/serial/by-path/. Unter Windows zählt nur der Name ohne Schreibweise (com5 und COM5), COM-Anschlüsse haben dort keine Links."""
    if os.name == "nt":
        return os.path.normcase(gewuenscht) == os.path.normcase(geraet)
    return os.path.realpath(gewuenscht) == os.path.realpath(geraet)


def waehle_port():
    """Gibt den Gerätepfad des CrowPanel zurück oder bricht mit einer Erklärung ab."""
    alle = list(list_ports.comports())
    passend = kandidaten()
    gewuenscht = os.environ.get("CROWPANEL_PORT")
    if gewuenscht:
        for p in passend:
            if gleicher_anschluss(gewuenscht, p.device):
                return p.device
        sys.exit(f"CROWPANEL_PORT={gewuenscht} ist kein angeschlossener CH340.")
    if len(passend) == 1:
        return passend[0].device
    for p in alle:
        if (p.vid, p.pid) in AUSGESCHLOSSEN:
            print(f"ausgeschlossen: {beschreibe(p)} -> {AUSGESCHLOSSEN[(p.vid, p.pid)]}")
    if not passend:
        sys.exit("Kein CH340 gefunden. Datenkabel an der USB-C-Buchse UART0 und Schalter POWER an?")
    liste = "\n".join(beschreibe(p) for p in passend)
    sys.exit(f"Mehrere CH340 gefunden, CROWPANEL_PORT setzen:\n{liste}")


def waehle_usb():
    """Gibt den Gerätepfad des CDC-Kanals an J16 zurück oder None. Erkennung über Kennung und Produktname, nie ein anderes Espressif-Board."""
    passend = [p for p in list_ports.comports() if (p.vid, p.pid) == (USB_VID, USB_PID) and p.product == USB_PRODUKT]
    gewuenscht = os.environ.get("CROWPANEL_USB")
    if gewuenscht:
        for p in passend:
            if gleicher_anschluss(gewuenscht, p.device):
                return p.device
        sys.exit(f"CROWPANEL_USB={gewuenscht} ist kein CrowPanel an J16.")
    if len(passend) > 1:
        liste = "\n".join(beschreibe(p) for p in passend)
        sys.exit(f"Mehrere CrowPanel an J16, CROWPANEL_USB setzen:\n{liste}")
    return passend[0].device if passend else None


def esptool_befehl(port, baud):
    """Aufruf von esptool mit dem Python dieser Toolchain, ohne Unterbefehl."""
    return [sys.executable, "-m", "esptool", "--chip", "esp32p4", "--port", port, "--baud", str(baud)]


def esptool(port, *argumente, baud=115200):
    """Führt esptool aus und gibt die Ausgabe zurück. Bei einem Fehler endet das Skript, vorher startet das CrowPanel neu, außer nach write-flash."""
    befehl = [*esptool_befehl(port, baud), *argumente]
    print("$ " + " ".join(befehl[1:]), flush=True)
    ergebnis = subprocess.run(befehl, capture_output=True, env=KIND_UMGEBUNG, **TEXT)
    ausgabe = ergebnis.stdout + ergebnis.stderr
    print(ausgabe, flush=True)
    if ergebnis.returncode != 0:
        meldung = f"esptool endete mit {ergebnis.returncode}"
        # Nach einem Schreibfehler kein Neustart, damit kein halb geschriebenes Abbild startet.
        if "write-flash" in argumente:
            sys.exit(f"{meldung}. Das CrowPanel bleibt im Download-Modus, Upload wiederholen.")
        abbruch(port, meldung)
    return ausgabe


def neustart_nach_abbruch(port):
    """Startet das CrowPanel nach einem Abbruch ohne Schreiben neu. esptool lässt es nach Zugriffen mit --after no-reset im Download-Modus stehen, dort bleibt der Bildschirm dunkel. Ein Fehler beim Neustart überdeckt den Abbruchgrund nicht."""
    print("Abbruch ohne Schreiben, das CrowPanel startet unverändert neu.", flush=True)
    if subprocess.run([*esptool_befehl(port, 115200), "--after", "hard-reset", "read-mac"], capture_output=True, env=KIND_UMGEBUNG, **TEXT).returncode != 0:
        print("Neustart nicht gelungen. Bleibt der Bildschirm dunkel, das CrowPanel einmal aus- und wieder einschalten.", flush=True)


def abbruch(port, meldung):
    """Startet das CrowPanel neu und beendet das Skript mit der Meldung. Nur vor dem ersten Schreiben aufrufen."""
    neustart_nach_abbruch(port)
    sys.exit(meldung)


def sha256(pfad):
    """SHA256 einer Datei als Hex-Text."""
    h = hashlib.sha256()
    with open(pfad, "rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


def befehl_port():
    """Listet alle USB-Seriellanschlüsse und den gewählten."""
    for p in list_ports.comports():
        if p.vid is None:
            continue
        hinweis = AUSGESCHLOSSEN.get((p.vid, p.pid), "")
        print(beschreibe(p) + (f"  [{hinweis}]" if hinweis else ""))
    print("gewählt:", waehle_port())
    print("J16:", waehle_usb() or "-")


def befehl_startlog(sekunden):
    """Startet das Gerät über RTS neu (Normalstart, BOOT bleibt High) und liest UART0 mit APP_BAUD mit."""
    port = waehle_port()
    MESSUNGEN.mkdir(parents=True, exist_ok=True)
    ziel = MESSUNGEN / time.strftime("startlog_%Y-%m-%d_%H%M%S.txt")
    s = serial.Serial()
    s.port = port
    s.baudrate = APP_BAUD
    s.timeout = 0.1
    # Beide Leitungen inaktiv: Die Autoreset-Schaltung lässt dann CHIP_PU und BOOT in Ruhe.
    s.dtr = False
    s.rts = False
    s.open()
    daten = bytearray()
    try:
        # RTS allein zieht CHIP_PU auf Low, DTR inaktiv hält BOOT High: Neustart in die Werksfirmware.
        s.rts = True
        time.sleep(0.2)
        s.rts = False
        ende = time.monotonic() + sekunden
        while time.monotonic() < ende:
            daten += s.read(4096)
    finally:
        s.close()
    ziel.write_bytes(bytes(daten))
    print(bytes(daten).decode("utf-8", errors="replace"))
    print(f"\n{len(daten)} Byte nach {ziel}")


def befehl_mitlesen(sekunden):
    """Liest UART0 ohne Neustart mit. DTR und RTS bleiben gemeinsam aktiv, so schaltet die Autoreset-Schaltung weder CHIP_PU noch BOOT."""
    port = waehle_port()
    MESSUNGEN.mkdir(parents=True, exist_ok=True)
    ziel = MESSUNGEN / time.strftime("mitlesen_%Y-%m-%d_%H%M%S.txt")
    s = serial.Serial()
    s.port = port
    s.baudrate = APP_BAUD
    s.timeout = 0.1
    s.dtr = True
    s.rts = True
    s.open()
    daten = bytearray()
    try:
        ende = time.monotonic() + sekunden
        while time.monotonic() < ende:
            neu = s.read(4096)
            if neu:
                daten += neu
                print(neu.decode("utf-8", errors="replace"), end="", flush=True)
    finally:
        s.close()
    ziel.write_bytes(bytes(daten))
    print(f"\n{len(daten)} Byte nach {ziel}")


def befehl_identifizieren():
    """Liest Chip, Flash, MAC, Sicherheitsstatus und Partitionstabelle. @return (MAC ohne Doppelpunkte, Ordner)."""
    port = waehle_port()
    texte = []
    texte.append(esptool(port, "--after", "no-reset", "chip-id"))
    texte.append(esptool(port, "--after", "no-reset", "flash-id"))
    mac_text = esptool(port, "--after", "no-reset", "read-mac")
    texte.append(mac_text)
    texte.append(esptool(port, "--after", "no-reset", "get-security-info"))
    mac = lese_mac(mac_text)
    if mac is None:
        abbruch(port, "MAC nicht gefunden.")
    ordner = RECOVERY / f"werk_{mac}"
    ordner.mkdir(parents=True, exist_ok=True)
    tabelle = ordner / "partitionen_0x8000.bin"
    texte.append(esptool(port, "--after", "hard-reset", "read-flash", "0x8000", "0x1000", str(tabelle)))
    (ordner / "chip_id.txt").write_text("\n".join(texte), encoding="utf-8")
    dekodiert = subprocess.run([sys.executable, str(GEN_PART), str(tabelle)], capture_output=True, env=KIND_UMGEBUNG, **TEXT)
    (ordner / "partitionen.csv").write_text(dekodiert.stdout + dekodiert.stderr, encoding="utf-8")
    print("Partitionstabelle:\n" + dekodiert.stdout + dekodiert.stderr)
    print(f"Ablage: {ordner}")
    return mac, ordner, "\n".join(texte)


def befehl_sichern():
    """Identifiziert und liest danach den ganzen Flash zweimal. Gleiche SHA256 -> eine Datei bleibt, SHA256SUMS dazu."""
    mac, ordner, text = befehl_identifizieren()
    groesse = re.search(r"Detected flash size:\s*(\d+)MB", text)
    if not groesse:
        sys.exit("Flashgröße nicht erkannt.")
    nbytes = int(groesse.group(1)) * 1024 * 1024
    port = waehle_port()
    lauf = []
    for i in (1, 2):
        datei = ordner / f"flash_lauf{i}.bin"
        start = time.monotonic()
        esptool(port, "--after", "hard-reset" if i == 2 else "no-reset", "read-flash", "0", hex(nbytes), str(datei), baud=LESE_BAUD)
        lauf.append((datei, sha256(datei), time.monotonic() - start))
        print(f"Lauf {i}: {lauf[-1][1]}  {lauf[-1][2]:.0f} s", flush=True)
    if lauf[0][1] != lauf[1][1]:
        sys.exit("SHA256 der beiden Läufe verschieden. Beide Dateien bleiben zur Prüfung liegen.")
    endgueltig = ordner / f"flash_{nbytes // (1024 * 1024)}MiB.bin"
    lauf[0][0].rename(endgueltig)
    lauf[1][0].unlink()
    summen = [f"{sha256(p)}  {p.name}" for p in sorted(ordner.iterdir()) if p.is_file() and p.name != "SHA256SUMS"]
    (ordner / "SHA256SUMS").write_text("\n".join(summen) + "\n", encoding="utf-8")
    print("\n".join(summen))
    print(f"Sicherung vollständig: {endgueltig}")


def lese_revision(text):
    """Chiprevision (Haupt, Neben) aus der Ausgabe von esptool chip-id, None ohne Angabe."""
    treffer = re.search(r"revision v(\d+)\.(\d+)", text)
    return (int(treffer.group(1)), int(treffer.group(2))) if treffer else None


def lese_mac(text):
    """P4-MAC aus einer Ausgabe von esptool als zwölf Hexziffern in Großbuchstaben, None ohne Angabe."""
    treffer = re.search(r"MAC:\s*([0-9a-fA-F:]{17})", text)
    return treffer.group(1).replace(":", "").upper() if treffer else None


def erwartete_mac():
    """MAC aus CROWPANEL_MAC als zwölf Hexziffern in Großbuchstaben, None ohne Angabe. Endet bei ungültigem Wert oder bei CROWPANEL_MAC_PFLICHT ohne CROWPANEL_MAC, vor jedem Gerätezugriff aufrufen."""
    wert = os.environ.get("CROWPANEL_MAC", "").strip()
    if not wert:
        if os.environ.get("CROWPANEL_MAC_PFLICHT"):
            sys.exit("Auf diesem Rechner verlangt der Upload CROWPANEL_MAC mit der MAC des gemeinten CrowPanel, etwa CROWPANEL_MAC=E8F60A112233.")
        return None
    mac = re.sub(r"[:-]", "", wert).upper()
    if not re.fullmatch(r"[0-9A-F]{12}", mac):
        sys.exit(f"CROWPANEL_MAC={wert} ist keine MAC mit zwölf Hexziffern.")
    return mac


def app_offset(tabelle):
    """Offset der Factory-App aus einer Partitionstabelle im CSV-Format."""
    for zeile in Path(tabelle).read_text(encoding="utf-8").splitlines():
        felder = [f.strip() for f in zeile.split("#")[0].split(",")]
        if len(felder) >= 5 and felder[1] == "app" and felder[2] == "factory":
            return int(felder[3], 0)
    sys.exit(f"Keine Factory-App in {tabelle}.")


def befehl_schreiben(variante, build, tabelle):
    """Schreibt Bootloader, Tabelle und App, aber nur mit passender Chiprevision und, mit CROWPANEL_MAC, nur auf dieses Gerät. Passt eins nicht, startet das CrowPanel unverändert neu. Eine Flashsicherung setzt das Schreiben nicht voraus, die Werksfirmware gibt es als Herstellerdownload."""
    if variante not in ("esp32p4_es", "esp32p4"):
        sys.exit(f"Unbekannte Kernvariante {variante}.")
    # Tabelle und erwartete MAC werden vor dem ersten Gerätezugriff geprüft, ein Fehler darin lässt das CrowPanel so ungestört.
    offset = app_offset(tabelle)
    erwartet = erwartete_mac()
    port = waehle_port()
    text = esptool(port, "--after", "no-reset", "chip-id")
    mac = lese_mac(text)
    if erwartet and mac != erwartet:
        abbruch(port, f"Angeschlossen ist das CrowPanel mit der MAC {mac or 'unbekannt'}, erwartet {erwartet}. Nichts geschrieben.")
    print(f"Ziel: CrowPanel mit der MAC {mac or 'unbekannt'}" + (" (wie erwartet)" if erwartet else ""), flush=True)
    revision = lese_revision(text)
    if revision is None:
        abbruch(port, "Chiprevision nicht gefunden.")
    haupt, neben = revision
    if (variante == "esp32p4_es" and haupt >= 3) or (variante == "esp32p4" and haupt < 3):
        abbruch(port, f"P4 v{haupt}.{neben} passt nicht zur Kernvariante {variante}. Andere Umgebung wählen.")
    build = Path(build)
    esptool(port, "--after", "hard-reset", "write-flash", "0x2000", str(build / "bootloader.bin"), "0x8000", str(build / "partitions.bin"), hex(offset), str(build / "firmware.bin"), baud=LESE_BAUD)
    print("Geschrieben und geprüft.")


def main(argv):
    # Leitet die Windows-Konsole die Ausgabe in eine Datei oder Pipe um, schreibt Python in der ANSI-Codepage. Zeichen wie die Balken von esptool werden dann zu ? statt zum Abbruch.
    for strom in (sys.stdout, sys.stderr):
        if hasattr(strom, "reconfigure"):
            strom.reconfigure(errors="replace")
    if len(argv) < 2:
        print(__doc__)
        return 2
    befehl = argv[1]
    if befehl == "port":
        befehl_port()
    elif befehl == "startlog":
        befehl_startlog(float(argv[2]) if len(argv) > 2 else 12.0)
    elif befehl == "mitlesen":
        befehl_mitlesen(float(argv[2]) if len(argv) > 2 else 60.0)
    elif befehl == "identifizieren":
        befehl_identifizieren()
    elif befehl == "sichern":
        befehl_sichern()
    elif befehl == "schreiben" and len(argv) == 5:
        befehl_schreiben(argv[2], argv[3], argv[4])
    else:
        print(__doc__)
        return 2
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
