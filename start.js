/** Einstieg der Seite: verbindet die Oberfläche mit dem echten Gerätezugriff. Ein Test ohne Gerät ersetzt nur diese Datei und übergibt eine Attrappe. */

import { starte } from "./flasher.js";
import { browserHinweis, verbindeGeraet } from "./geraet.js";

starte({ browserHinweis, verbindeGeraet });
