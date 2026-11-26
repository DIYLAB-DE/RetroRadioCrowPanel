# esptool-js

Unveränderte Kopie aus dem npm-Paket `esptool-js` 0.7.1 von Espressif Systems, Quelle [espressif/esptool-js](https://github.com/espressif/esptool-js). Der Web-Flasher spricht damit über Web Serial mit dem ROM-Bootloader des ESP32-P4.

| Datei | Herkunft | SHA-256 |
| --- | --- | --- |
| `bundle.js` | `package/bundle.js` | `d6a4b0b7c9b747a7370cfa976164a962f56332d5faa7c3b45cdb95a2a8b1d456` |
| `LICENSE` | `package/LICENSE` (Apache License 2.0) | `1c25f29242785d63e9adb0be7fdc137551dfbbc0756b622fcd26d9cd7de3a4f3` |
| `pako-LICENSE` | `package/LICENSE` aus dem npm-Paket `pako` 2.1.0 | `a04665b3b2de56c66730c1f720f528175739e4104f79073614aa611da1e85539` |

- Paketarchiv: `https://registry.npmjs.org/esptool-js/-/esptool-js-0.7.1.tgz`, Prüfsumme der Registry `sha512-vw1isT5ROHgpRmMG3y6B81dceeZ7O1WhF1x05qFbAlH8N0N/pOQqODzJLA+36lCbOXCw06iA4CWctyrQQ7VeSA==`.
- `bundle.js` ist ein einzelnes ES-Modul. Es enthält die Hilfsprogramme für den Arbeitsspeicher der Chips (Flasher-Stubs von Espressif) und die Kompression pako 2.1.0 ([nodeca/pako](https://github.com/nodeca/pako), MIT und Zlib, Archiv `https://registry.npmjs.org/pako/-/pako-2.1.0.tgz`).
- Nichts in diesem Ordner wird bearbeitet. Eine neue Fassung ersetzt alle drei Dateien und diese Tabelle. Danach `webflasher/geraet.js` gegen die neue Schnittstelle prüfen und am Gerät testen.
