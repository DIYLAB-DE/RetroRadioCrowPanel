# Fehlerhilfe

[RetroRadioCrowPanel](../README.md) > [Dokumentation](../README.md#dokumentation) > Fehlerhilfe

| Beobachtung | Prüfen und beheben |
| --- | --- |
| Kein serieller Anschluss | Datenkabel statt Ladekabel verwenden, es gehört in die Buchse **UART0**. Schalter **POWER** einschalten und das CrowPanel möglichst direkt am Rechner anschließen. Unter Windows und macOS kann ein Treiber für den CH340 fehlen, unter Linux die Berechtigung, siehe [Erstinstallation](RetroRadioCrowPanel-Ersteinrichtung.md#11-hilfe-bei-problemen). |
| Upload meldet **Kein CH340 gefunden** | Wie oben. Das Kabel steckt in der Buchse **USB2.0** statt **UART0**, oder der Rechner hat den Wandler nicht erkannt. |
| Upload meldet **Mehrere CH340 gefunden** | Am Rechner hängt ein zweites Gerät mit demselben Wandler, etwa ein weiteres CrowPanel. Den Anschluss mit `--upload-port` angeben, siehe [Erstinstallation](RetroRadioCrowPanel-Ersteinrichtung.md#7-retroradiocrowpanel-übertragen). |
| Upload meldet, die Revision **passt nicht zur Kernvariante** | Gewählt ist die Umgebung `crowpanel_p4v3`, die bisher geprüften CrowPanel brauchen `crowpanel_p4es`. Auf das Gerät wurde nichts geschrieben. |
| Upload oder Web-Flasher nennt den **Platinenstand V2.0** oder findet keine Firmware für die Chiprevision | Das CrowPanel hat einen ESP32-P4 ab Revision 3.0 und damit nach Herstellerangabe den Platinenstand V2.0 mit anderem Tonweg. RetroRadioCrowPanel unterstützt ihn noch nicht. Auf das Gerät wurde nichts geschrieben, es startet mit seiner bisherigen Firmware. |
| Web-Flasher: **Verbinden** ist gesperrt | Die Seite nennt den Grund in roter Schrift: Der Browser kann nicht auf serielle Anschlüsse zugreifen oder ist mit dem Web-Flasher nicht geprüft. Chrome, Edge, Opera oder Firefox ab Version 160 auf einem Rechner verwenden. |
| Web-Flasher: In der Auswahl des Browsers erscheint kein Anschluss | Wie bei „Kein serieller Anschluss“ oben. Die Auswahl zeigt nur den USB-Wandler des CrowPanel, andere Geräte bietet sie nicht an. |
| Web-Flasher meldet **Das Gerät antwortet nicht** | Andere Programme schließen, die den Anschluss belegen. Hilft das nicht, **BOOT** gedrückt halten, **RST** kurz drücken, **BOOT** loslassen und erneut verbinden. |
| Nach einem Abbruch im Web-Flasher bleibt der Bildschirm dunkel | Das CrowPanel wartet im Download-Modus. **RST** drücken oder **POWER** aus- und wieder einschalten, dann die Installation wiederholen. |
| Terminal meldet einen Python-Fehler mit **resultcallback** und `platformio==4.3.4` | Das Terminal startet ein veraltetes PlatformIO aus den Paketquellen der Linux-Distribution. Das Terminal über **PlatformIO: New Terminal** öffnen oder `~/.platformio/penv/bin/pio` mit vollem Pfad aufrufen, siehe [Erstinstallation](RetroRadioCrowPanel-Ersteinrichtung.md#pio-bricht-mit-resultcallback-ab). |
| Upload-Port belegt | Serielle Monitore und andere Programme schließen, die denselben Anschluss geöffnet haben. |
| Bild bleibt schwarz oder das Gerät startet immer wieder neu | Die Versorgung reicht nicht. Ein USB-Netzteil mit 5 V und mindestens 2 A an **USB2.0** anschließen, empfohlen ist ein USB-C-Netzteil mit 20 W. Das Datenkabel an **UART0** darf stecken bleiben, siehe [Versorgung](Geräte-und-Anschlüsse.md#versorgung). |
| WLAN bleibt getrennt | 2,4-GHz-Netz, Passwort und aktiviertes Profil prüfen. **test** ausführen, speichern und einen angebotenen Neustart durchführen. Nach einem Test mit falschem Passwort weisen manche Router das Gerät einige Minuten lang ab. |
| Radiosymbol ist gesperrt | Ohne WLAN-Verbindung lässt sich das Radio nicht öffnen. WLAN einrichten, der SD-Player geht auch ohne. |
| Browser erreicht das CrowPanel nicht | Die aktuelle IP-Adresse am Gerät ablesen und mit `http://` öffnen. Rechner und CrowPanel müssen sich erreichen können, Gastnetz oder Client-Isolation können das verhindern. |
| Radiosteuerung fehlt im Browser | Das Radio am Gerät öffnen und die Weboberfläche entsperren. |
| Sender bleibt stumm | Anderen Sender testen, Stummschaltung und Lautstärke prüfen. Unter **Einstellungen -> Klang** muss **Lautsprecher** auf **An** stehen. Lautsprecherstecker an **SPK** prüfen. Eine direkte Audio-Stream-Adresse verwenden, eine Webseite ersetzt keinen Stream. Bei HTTPS zusätzlich die Uhrzeit prüfen. |
| Links und rechts klingen vertauscht | Die Lautsprecher nach der Aufschrift an den Buchsen stecken: links neben **BAT**, rechts neben der SD-Karte, siehe [Lautsprecher](Geräte-und-Anschlüsse.md#lautsprecher). |
| Infozeile zeigt **Stream unterbrochen** | Das Radio versucht den Sender selbst neu zu starten. Bleibt es dabei, WLAN-Empfang und Stream-Adresse prüfen. |
| SD-Player meldet **Keine SD-Karte** oder **SD-Karte nicht lesbar** | Sitz der Karte prüfen und das CrowPanel neu starten. Die Karte muss mit FAT32 formatiert sein, exFAT wird nicht gelesen. Die Karte am Rechner prüfen, RetroRadioCrowPanel formatiert sie nie. |
| SD-Player meldet **Anforderung nicht angenommen** | Dateimanager oder FTP greifen gerade auf die Karte zu. Übertragung abwarten und erneut starten. |
| SD-Dateien fehlen | Im Web-Dateimanager kontrollieren, ob die Dateien auf der Karte sichtbar sind. Unterstützt werden MP3, AAC, M4A, FLAC und OGG. |
| Cover fehlt | Ein `folder.jpg` in den Musikordner legen oder eine Datei mit eingebettetem Cover verwenden. Die [Bildgrenzen](Radio-und-Musik.md#ordnercover-und-bildgrenzen) beachten. |
| FTP-Programm verbindet nicht oder bricht ab | FTP in der Weboberfläche einschalten, nach jedem Neustart ist es aus. Passiven Modus, unverschlüsseltes FTP und eine Verbindung zur Zeit einstellen. Hochladen geht nur, solange kein Radio läuft. |
| PIN vergessen | Ohne die aktuelle PIN lässt sich die Sperre weder am Gerät noch in der Weboberfläche aufheben, auch ein Firmware-Update ändert die PIN nicht. Notiere Dir eine geänderte PIN deshalb an einem sicheren Ort. |
| Bild steht auf dem Kopf | Unter **Einstellungen -> Bildschirm** bei **Bild** die andere Lage wählen und speichern. |
| Uhrzeit fehlt nach dem Einschalten | Ohne Uhr DS1307 kommt die Zeit erst mit dem WLAN. Mit DS1307 Verkabelung am Stecker **I2C** (Grove-Kabel ungedreht), die entfernte Diode D1 und die Knopfzelle prüfen. Unter **Info & Neustart** muss in der Zeile **I2C** die Adresse `0x68` stehen, siehe [Uhr DS1307](Geräte-und-Anschlüsse.md#uhr-ds1307). |
| Uhrzeit falsch | Zeitzone, Zeitserver und letzten Abgleich unter **Einstellungen -> Zeit & Zeitserver** beziehungsweise **Info & Neustart** prüfen. |
| Änderungen scheinbar verloren | Bei Einstellungen die zugehörige **speichern**-Taste verwenden. Ein Neustart ohne vorheriges Speichern übernimmt noch nicht gespeicherte Eingaben nicht. |

Für einen Fehlerbericht das Modell (7, 9 oder 10,1 Zoll) und den Platinenstand (Aufdruck auf der Platine), die Firmwareversion unter **Einstellungen -> Info & Neustart**, die betroffene Anwendung und eine kurze reproduzierbare Schrittfolge angeben. Screenshots helfen bei Darstellungsfehlern. Netzwerkadressen, WLAN-Namen und Zugangsdaten vorher unkenntlich machen. Die Diagnosemeldungen schaltest Du unter **Einstellungen -> Allgemein -> Ausgabe über USB** ein, sie kommen an der Buchse **UART0** mit 115200 Baud. Ein Zurücksetzen auf Werkseinstellungen ist kein allgemeiner erster Lösungsversuch.

[Erstinstallation](RetroRadioCrowPanel-Ersteinrichtung.md) | [Bedienung](Bedienung.md) | [Weboberfläche](Weboberfläche.md) | [Geräte und Anschlüsse](Geräte-und-Anschlüsse.md)

[RetroRadioCrowPanel](../README.md) > [Dokumentation](../README.md#dokumentation) > Fehlerhilfe
