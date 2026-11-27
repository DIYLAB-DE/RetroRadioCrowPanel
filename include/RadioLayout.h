#ifndef RADIO_LAYOUT_H
#define RADIO_LAYOUT_H
#include "StationManager.h"

/**
 * @brief Native 1024x600-Geometrie des Radios ohne Skalierung.
 *
 * Abgeleitet aus dem Layout des Originals (800x480): Größen, Höhen und Schriften 1,25-fach (600/480), waagerechte Verteilung bis 1,28-fach (1024/800). Halbe Pixel werden aufgerundet. Rahmen und Linien mit Originalbreite 1 werden 2 Pixel breit, auch in den Dialogen. Auf 1 Pixel abgerundet wüchsen sie nicht mit, und die geglätteten Rundungen der Ecken blieben blass. Der Senderabstand ist 12,8 px, die Senderpositionen werden einzeln gerundet. Visualizer, Uhren und Tasten liegen im rechts unten bündigen Bereich Visual. Der Visualizer rechnet dort mit seiner eigenen 1,25-fachen Geometrie (VisualizerGeometry).
 */
namespace RadioLayout
{
    constexpr int WIDTH = 1024; ///< Breite der Radioszene, deckungsgleich mit dem Display
    constexpr int HEIGHT = 600; ///< Höhe der Radioszene

    /** @brief Senderskala, Trennlinien, Logo und Zeiger. */
    namespace Scale
    {
        constexpr int DIVIDER_HEIGHT = 4;     ///< Original 3
        constexpr int TOP_DIVIDER_Y = 0;      ///< Original 0
        constexpr int Y = 6;                  ///< Oberkante des Skalensprites, Original 5
        constexpr int HEIGHT = 375;           ///< Original 300
        constexpr int BOTTOM_DIVIDER_Y = 384; ///< Original 307
        constexpr int STATION_PITCH_NUM = 64; ///< Senderabstand als Bruch 64/5 = 12,8 px, Original 10, 1,28-fach wie die waagerechte Verteilung
        constexpr int STATION_PITCH_DEN = 5;

        /** @brief X-Position des Senders index, auf ganze Pixel gerundet. Original 10 + 10 x index. */
        constexpr int stationX(int index)
        {
            return ((index + 1) * STATION_PITCH_NUM * 2 + STATION_PITCH_DEN) / (2 * STATION_PITCH_DEN);
        }

        /** @brief Sender unter der Skalenspalte x. Wie im Original gehört zu jedem Sender der Streifen links von seiner Position, einen Senderabstand breit. */
        constexpr int stationAt(int x)
        {
            return x * STATION_PITCH_DEN / STATION_PITCH_NUM;
        }

        constexpr int STATION_X0 = stationX(0); ///< 13, X-Position des ersten Senders, Original 10
        constexpr int STATION_Y0 = 128;       ///< Zeile des ersten Senders, Original 102
        constexpr int STATION_STEP_Y = 25;    ///< Zeilenabstand, Original 20
        constexpr int ROW_WRAP_Y = 375;       ///< Zeilen darüber beginnen oben neu, Original 300
        constexpr int ROW_RESTART_Y = 3;      ///< Erste Zeile nach dem Umbruch, Original 2
        constexpr int MARKER_X = -5;          ///< Markerversatz zur Senderposition, Original -4. Mittig unter dem Zeiger
        constexpr int MARKER_Y = 6;           ///< Original 5, dort 1,5 Pixel über der Versalmitte
        constexpr int MARKER_W = 17;          ///< Original 14, ungerade Breite hält den Marker mittig unter dem 5 Pixel breiten Zeiger
        constexpr int MARKER_H = 8;           ///< Original 6
        constexpr int NAME_X = 20;            ///< Textversatz zur Senderposition, Original 16
        constexpr int NAME_Y = 0;             ///< Original 0
        constexpr int UNDERLINE_H = 1;        ///< Unterstreichung der Favoriten, Original 1
        constexpr int LOGO_X = 19;            ///< Original 15
        constexpr int LOGO_Y = 38;            ///< Original 30
        constexpr int LOGO_W = 113;           ///< Original 90
        constexpr int LOGO_H = 66;            ///< Original 53
        constexpr int NEEDLE_STRIP = 8;       ///< Wiederhergestellter Streifen je Zeigerposition, Original 6
        constexpr int NEEDLE_RED_X = 1;       ///< Versatz des roten Zeigers im Streifen, Original 1
        constexpr int NEEDLE_RED_W = 5;       ///< Breite des roten Zeigers, Original 4
        constexpr int NEEDLE_MAX_X = WIDTH - NEEDLE_STRIP; ///< Original 794
        constexpr float NEEDLE_SPEED = 270.0f; ///< Höchstgeschwindigkeit in px/s, ganze Skala in etwa 3,3 s. Bei rund 56 Bildern/s des Displays rückt der Zeiger so unter 5 px je Bild und überlappt sich von Bild zu Bild. Das Original fährt gleichförmig mit 166,6 px/s (nativ wären das 216,6)
        constexpr float NEEDLE_ACCEL = 1800.0f; ///< Anfahren und Bremsen in px/s², weich statt gleichförmig wie im Original. Volle Fahrt nach 0,15 s
        constexpr int NEEDLE_SUBSTEPS = 16;    ///< Teilschritte je Pixel: Während der Fahrt mischen die Randspalten der Nadel Rot und Hintergrund nach dem Bruchteil der Lage
        constexpr int NEEDLE_STAGING_W = 64;   ///< Größte Breite des Streifens aus alter und neuer Nadelstelle, die in einem Schritt direkt in die Panelzeilen geht, ohne Panelkopie über einen Zwischenpuffer dieser Breite. Breitere Sprünge gehen aus der Szene
        constexpr int TOUCH_RIGHT = MAX_STATIONS * STATION_PITCH_NUM / STATION_PITCH_DEN; ///< 896, rechte Grenze der Senderwahl, Original 700
    }

    /** @brief Infozeile mit Codec-Feld, Sender, Titel, Bitrate und Stereo-Symbol. */
    namespace Footer
    {
        constexpr int Y = 395;               ///< Original 316
        constexpr int HEIGHT = 40;           ///< Original 32
        constexpr int LINE = 2;              ///< Rahmenlinie oben und unten, Original 1
        constexpr int RESERVED = 116;        ///< Für Codec-Feld und Stereo-Symbol freigehaltene Breite, je Seite die Hälfte, Original 90
        constexpr int STEREO_W = 51;         ///< Original 41
        constexpr int STEREO_H = 31;         ///< Original 25
        constexpr int STEREO_X = WIDTH - STEREO_W - 1; ///< Original 800-41-1
        constexpr int STEREO_Y = 399;        ///< Original 319
        constexpr int STEREO_LEFT_X = 16;    ///< Mittelpunkt linker Ring, Original 13
        constexpr int STEREO_RIGHT_X = 35;   ///< Mittelpunkt rechter Ring, Original 28
        constexpr int STEREO_CY = 15;        ///< Original 12
        constexpr float STEREO_R = 13.75f;   ///< Original 11
        constexpr float STEREO_THICKNESS = 2.5f; ///< Original 2
        constexpr int CODEC_X = 1;           ///< Spiegelbildlich zum Stereo-Symbol, Original 1
        constexpr int CODEC_Y = STEREO_Y;    ///< Original 319
        constexpr int CODEC_W = 54;          ///< Original 43
        constexpr int CODEC_H = STEREO_H;    ///< Original 25
        constexpr int CODEC_BADGE_H = 23;    ///< Höhe der Marke wie im SD-Player, Original 18
        constexpr int CODEC_BADGE_PAD = 10;  ///< Zusatzbreite zum Text, Original 8
    }

    /** @brief Magisches Auge oben rechts in der Skala. */
    namespace MagicEye
    {
        constexpr int SIZE = 88;               ///< Breite und Höhe des Sprites, Original 70
        constexpr int X = 910;                 ///< Linke Kante, Original 710. Der Mittelpunkt liegt im gleichen Breitenverhältnis wie im Original
        constexpr int Y = 25;                  ///< Original 20
        constexpr float RING_THICKNESS = 6.25f; ///< Außenring EM11/EM34, Original 5
        constexpr float EM80_HALF_W = 27.5f;   ///< Original 22
        constexpr float EM80_HALF_H = 36.25f;  ///< Original 29
        constexpr float EM84_HALF_W = 15.625f; ///< Original 12,5
        constexpr float EM84_HALF_H = 42.5f;   ///< Original 34
    }

    /** @brief Lautstärkedrehknopf mit Beschriftung darüber. */
    namespace Knob
    {
        constexpr int X = 0;                    ///< Original 0
        constexpr int Y = 467;                  ///< Original 373, ungerade Kantenlänge hält den Mittelpunkt auf einem Pixel
        constexpr int SIZE = 133;               ///< Original 107
        constexpr int MID = SIZE / 2;           ///< Mittelpunkt im Sprite, Original 53
        constexpr int LABEL_H = 17;             ///< Beschriftungsstreifen über dem Knopf, Original 13. Beginnt wie die Reglerbeschriftung bei y 450
        constexpr float RING_R = MID - 1.25f;   ///< Original MID-1
        constexpr float RING_THICKNESS = 3.75f; ///< Original 3
        constexpr int MARKER_OFFSET = 25;       ///< Abstand der Markerbahn vom Rand, Original 20
        constexpr float MARKER_R = 16.25f;      ///< Original 13
        constexpr float MARKER_THICKNESS = 3.75f; ///< Original 3
        constexpr int VALUE_Y = 19;             ///< Oberkante der Zahl über der Mitte, Original 15
        constexpr int MUTE_ICON = 35;           ///< Stummsymbol, Original 28
        constexpr float MUTE_ICON_SCALE = 1.25f; ///< Faktor für IconShapes::draw
        constexpr int TOUCH_MUTE_R = 20;        ///< Stummschaltung bis zu diesem Radius, Original 16
        constexpr int TOUCH_RING_R = 25;        ///< Drehen ab diesem Radius, Original 20
        constexpr int TOUCH_MARGIN = 25;        ///< Trefferrand um den Knopf, Original 20
    }

    /** @brief Schieberegler für Balance, Tiefen, Mitten und Höhen in einem Sprite. */
    namespace Tracks
    {
        constexpr int X = 171;             ///< Original 130. Mittig zwischen Drehknopf und Visualizerfläche, je 38 px Abstand (Original 23 und 21)
        constexpr int Y = 450;             ///< Original 360
        constexpr int WIDTH = 241;         ///< Original 190, 241 statt 238, damit „Höhen“ in Comfortaa Bold 13 (46 px) am vierten Regler ganz hineinpasst
        constexpr int HEIGHT = 150;        ///< Original 120
        constexpr int SLIDER_X0 = 6;       ///< Linke Kante des ersten Reglers, Original 5
        constexpr int SLIDER_STEP = 63;    ///< Original 50
        constexpr int TOUCH_W = 39;        ///< Treffer- und Nulllinienbreite, Original 31
        constexpr int CENTER_X = 19;       ///< Mitte von Bahn, Nulllinie und Knopf im Regler, Original 15
        constexpr int GROOVE_W = 3;        ///< Original 3, ungerade Breite hält die Bahn mittig um CENTER_X
        constexpr int GROOVE_Y = 3;        ///< Original 2
        constexpr int GROOVE_H = 145;      ///< Original 116
        constexpr int PIXEL_MIN = 130;     ///< Knopfmitte bei -12 dB bzw. Balance links, Original 104
        constexpr int PIXEL_ZERO = 80;     ///< Original 64
        constexpr int PIXEL_MAX = 30;      ///< Original 24
        constexpr float KNOB_R = 16.25f;   ///< Original 13
        constexpr float KNOB_THICKNESS = 3.75f; ///< Original 3
        constexpr float KNOB_FILL_R = 12.5f;   ///< Original 10
        constexpr int HOLD_TOLERANCE = 8;  ///< Weg, den der Finger beim Halten auf dem Knopf wandern darf, Original 6
    }

    /** @brief Rechter unterer Bereich für Visualizer, Uhren und Tasten: Originalbereich 341..800 x 354..480 1,25-fach, rechts unten bündig. */
    namespace Visual
    {
        constexpr int W = 574;          ///< Original 459
        constexpr int H = 158;          ///< Original 126
        constexpr int X = WIDTH - W;    ///< 450, Original 341
        constexpr int Y = HEIGHT - H;   ///< 442, Original 354
    }

    /** @brief Fünf Bedientasten rechts unten, gleich breit mit gleichen Abständen, rechte Taste am Rand. */
    namespace Buttons
    {
        constexpr int Y = 544;                 ///< Original 435
        constexpr int H = HEIGHT - Y;          ///< 56, Original 45
        constexpr int W = 56;                  ///< Original 45, gilt auch für Reset (Original 67 mit Text)
        constexpr int GAP = 13;                ///< Original 10
        constexpr int RADIUS = 5;              ///< Eckenradius, Original 4
        constexpr int BORDER = 2;              ///< Rahmen, Original 1
        constexpr int BORDER_PRESSED = 3;      ///< Rahmen gedrückt, Original 2
        constexpr int X4 = WIDTH - W;          ///< 968, Haus (Hauptmenü und Sleep-Timer)
        constexpr int X3 = X4 - GAP - W;       ///< 899, Reset
        constexpr int X2 = X3 - GAP - W;       ///< 830, Weiter
        constexpr int X1 = X2 - GAP - W;       ///< 761, Zurück
        constexpr int X0 = X1 - GAP - W;       ///< 692, Favoriten
    }

    /** @brief Uhren im unteren Bereich, Lage über die Originalkanten auf die Visualizerfläche abgebildet. */
    namespace Clock
    {
        constexpr int DIGITAL_X = Visual::X + 18;  ///< Original 355
        constexpr int DIGITAL_Y = Buttons::Y;      ///< Original 435
        constexpr int DIGITAL_W = 188;             ///< Original 150
        constexpr int DIGITAL_H = Buttons::H;      ///< Original 45
        constexpr int ANALOG_X = Visual::X + 475;  ///< Original 721, im Goniometermodus
        constexpr int ANALOG_Y = Visual::Y;        ///< Original 354
        constexpr int ANALOG_SIZE = 88;            ///< Original 70
    }

    /** @brief Dialoge 1,25-fach, mittig auf dem Display wie im Original. Die Innenmaße stehen nativ in den Dialogklassen. */
    namespace Dialog
    {
        constexpr int PRESETS_W = 750, PRESETS_H = 550; ///< Favoriten, Original 600x440 bei (100,20)
        constexpr int PRESETS_X = (WIDTH - PRESETS_W) / 2, PRESETS_Y = (HEIGHT - PRESETS_H) / 2;
        constexpr int MESSAGE_W = 375, MESSAGE_H = 250; ///< Reset-Rückfrage, Original 300x200 bei (250,140)
        constexpr int MESSAGE_X = (WIDTH - MESSAGE_W) / 2, MESSAGE_Y = (HEIGHT - MESSAGE_H) / 2;
        constexpr int SLEEP_W = 375, SLEEP_H = 375; ///< Schlaftimer, Original 300x300 bei (250,90)
        constexpr int SLEEP_X = (WIDTH - SLEEP_W) / 2, SLEEP_Y = (HEIGHT - SLEEP_H) / 2;
    }
}
#endif
