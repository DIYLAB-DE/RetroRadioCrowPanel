# Änderungen

[RetroRadioCrowPanel](../README.md) > [Dokumentation](../README.md#dokumentation) > Änderungen

Hier steht, was sich von Version zu Version ändert, die neueste Version steht oben. Jede Version erscheint als [Release auf GitHub](https://github.com/DIYLAB-DE/RetroRadioCrowPanel/releases) mit eigener Nummer. Die Nummer zeigt das CrowPanel unter Einstellungen -> Info & Neustart und die Weboberfläche im Abschnitt System. Sie ändert sich nur mit einem neuen Release, auch wenn Du die Firmware selbst baust.

## Nachtrag vom 27.11.2026

Ohne neue Firmware, die Version bleibt v26.11.14. Wer sie schon aufgespielt hat, muss nichts tun.

- **Web-Flasher:** Die fertige Firmware lässt sich jetzt unter [diylab-de.github.io/RetroRadioCrowPanel](https://diylab-de.github.io/RetroRadioCrowPanel/) direkt aus Chrome, Edge, Opera oder Firefox ab Version 160 aufspielen, zur Erstinstallation und für Updates, siehe [Schnellweg: der Web-Flasher](RetroRadioCrowPanel-Ersteinrichtung.md#schnellweg-der-web-flasher). Die Quelle der Seite liegt unter `webflasher/`. Geprüft unter Linux in Chrome an zwei Geräten mit 10,1 Zoll, als Erstinstallation ab Werksfirmware und als Update, dazu in Firefox 160 als Update. Andere Browser, Smartphones und Tablets sperrt die Seite.
- **Platinenstand V2.0:** Der Hersteller führt seit November 2026 einen Platinenstand V2.0 mit ESP32-P4 Revision 3.2 und anderem Tonweg. RetroRadioCrowPanel unterstützt ihn noch nicht. Web-Flasher und Upload erkennen solche Geräte am Chip und schreiben nichts auf sie.
- **Netzteil:** Die Anleitungen empfehlen ein Netzteil nur noch, wenn der Rechner zu wenig Strom liefert oder das Radio ohne Rechner laufen soll. Alle geprüften Geräte liefen auch am USB-Anschluss eines Rechners.

## v26.11.14 vom 14.11.2026

Die erste öffentliche Version von RetroRadioCrowPanel, [v26.11.14 auf GitHub](https://github.com/DIYLAB-DE/RetroRadioCrowPanel/releases/tag/v26.11.14). Sie ist als Vorabversion gekennzeichnet, weil sie bisher nur an je einem Gerät jeder Größe geprüft ist.

### Umfang

- **Eine Firmware für drei Displays:** CrowPanel Advanced ESP32-P4 mit 7, 9 und 10,1 Zoll, alle mit 1024 x 600 Pixeln. Die Oberfläche ist ohne Skalierung nativ für diese Auflösung gezeichnet, Maße und Schriften sind aus dem Original-RetroRadio abgeleitet.
- **Hauptmenü:** große runde Uhr mit Datum und WLAN-Anzeige, daneben die Symbole für Radio, SD-Player und Einstellungen. Der Sekundenzeiger schleicht gleichmäßig oder springt in Sekundenschritten. Ein Sperrbildschirm mit PIN schützt das Gerät.
- **Radio:** Internetradio mit 70 Senderplätzen auf einer nachgebildeten Analogskala, Favoriten, vier magischen Augen, Lautstärke, Balance, Klangregler für Tiefen, Mitten und Höhen und Sleep-Timer. Wie im Original stellt ein ruhiger Druck von etwa 0,8 Sekunden auf den Knopf eines Reglers nur diesen auf null. Im Stand zeigt das magische Auge die Stärke des WLAN-Empfangs.
- **Visualisierungen:** acht Ansichten in Radio und SD-Player mit je zwei Fassungen, analoge und digitale VU-Meter, Spektrum, mittiges Spektrum, Wasserfall, Wellenform, Goniometer und Nordlicht.
- **SD-Player:** Musik von der microSD-Karte mit acht animierten Kassetten, Cover, Ordnerauswahl, Playlist und Wiederholung von Titel oder Liste.
- **Einstellungen:** WLAN, Zeit, Zeitfenster, Sprache, PIN-Sperre, Klang, Anzeige, Thema, Bildschirm und Geräteinformationen. Die Seiten Bluetooth und UKW sind für den geplanten Bluetooth-Sender vorbereitet.
- **Deutsch und Englisch:** Gerät und Weboberfläche lassen sich unter Einstellungen -> Allgemein auf Englisch umstellen.
- **Themen:** Retro mit den Farben des Originals, E-Paper in hellen Papiertönen und Individuell mit eigenen Farben aus der Weboberfläche.
- **Bildlage:** Bild und Bedienung lassen sich unter Einstellungen -> Bildschirm um 180° drehen, je nachdem, auf welcher Seite die Kabel stecken.
- **Weboberfläche:** Fernbedienung, Senderpflege mit Sortieren, Sichern und Laden der Senderliste, Systemeinstellungen, Farben, Dateimanager und Bildschirmaufnahme im Browser. Für größere Dateien gibt es einen FTP-Zugang zur SD-Karte.
- **Stereo:** Die beiden Lautsprecher spielen links und rechts getrennt, nach der Aufschrift an ihren Buchsen. Balance und Basisbreite wirken hörbar.
- **Uhr DS1307:** optional am Stecker I2C. Mit ihr steht die Uhrzeit sofort nach dem Einschalten bereit, und Sender, Lautstärke und Klang liegen wie im Original-RetroRadio in ihrem Speicher. Ohne sie kommt die Zeit aus dem Netz.
- **Geprüfter Upload:** Er schreibt nur über den USB-Seriell-Wandler an der Buchse UART0, prüft vor dem Schreiben die Chiprevision des ESP32-P4 und erhält Sender und Einstellungen. Die Firmware des WLAN-Chips bleibt unverändert.

### Abweichungen vom Original-RetroRadio

- Der Sekundenzeiger der Uhr im Hauptmenü schleicht ab Werk gleichmäßig. Die Sekundenschritte des Originals lassen sich unter Einstellungen -> Zeit & Zeitserver wählen.
- Die Tasten Zurücksetzen im Radio sowie Dateiauswahl, Liste leeren und Zurücksetzen im SD-Player zeigen Symbole statt Text.
- Das magische Auge EM34 steht senkrecht mit dem breiten Schatten oben, wie die Röhre in Radios meist eingebaut war.
- Meldungen in der Statuszeile des SD-Players stehen mittig zwischen zwei Strichen, etwa „- keine Wiedergabe -“.
- Rahmen und Trennlinien sind 2 Pixel breit, passend zu den größeren Tasten und Schriften.
- Die Haus-Taste unten rechts ersetzt die Ein/Aus-Taste des Originals.

### Bekannt und offen

- Der Betrieb mit Akku ist nicht geprüft, eine Ladeanzeige gibt es nicht.
- Ein CrowPanel mit ESP32-P4 ab Revision 3.0 ist nicht bekannt. Die Umgebung `crowpanel_p4v3` baut, ist aber nicht am Gerät geprüft.
- Die Erstinstallation wurde unter Linux geprüft. Unter Windows ist der Upload vorbereitet, aber noch nicht an einem Gerät durchgelaufen, unter macOS ebenso.
- Der Bluetooth-Sender mit UKW-Modulator und optischem Ausgang ist geplant, aber noch nicht Teil dieser Version.

[RetroRadioCrowPanel](../README.md) > [Dokumentation](../README.md#dokumentation) > Änderungen
