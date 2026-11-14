"""Bindet den geprüften Upload in PlatformIO ein. Die Prüfungen und das Schreiben übernimmt scripts/crowpanel_geraet.py (Befehl „schreiben“)."""

import os
import subprocess
from pathlib import Path

Import("env")


def upload_crowpanel(source, target, env):
    """Schreibt Bootloader, Partitionstabelle und App dieser Umgebung nach den Prüfungen des Gerätewerkzeugs."""
    projekt = Path(env.subst("$PROJECT_DIR"))
    # Das penv-Python der Plattform, unter Linux und macOS penv/bin/python, unter Windows penv\Scripts\python.exe.
    python = env.subst("$PYTHONEXE")
    umgebung = dict(os.environ)
    port = env.subst("$UPLOAD_PORT")
    if port:
        umgebung["CROWPANEL_PORT"] = port
    # Nur aus der unversionierten platformio_lokal.ini: Rechner mit mehreren CrowPanel verlangen so bei jedem Upload CROWPANEL_MAC.
    if str(env.GetProjectOption("custom_crowpanel_mac_pflicht", "")).strip().lower() in ("1", "ja", "yes", "true"):
        umgebung["CROWPANEL_MAC_PFLICHT"] = "1"
    tabelle = Path(env.subst("$PARTITIONS_TABLE_CSV"))
    if not tabelle.is_absolute():
        tabelle = projekt / tabelle
    befehl = [python, str(projekt / "scripts" / "crowpanel_geraet.py"), "schreiben", env.BoardConfig().get("build.chip_variant"), env.subst("$BUILD_DIR"), str(tabelle)]
    return subprocess.run(befehl, env=umgebung).returncode


env.Replace(UPLOADCMD=env.VerboseAction(upload_crowpanel, "Geprüfter Upload auf das CrowPanel"))
