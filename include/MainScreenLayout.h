#ifndef MAINSCREEN_LAYOUT_H
#define MAINSCREEN_LAYOUT_H

/**
 * @brief Native 1024x600-Geometrie von MainScreen, Sperrbildschirm und Eckengeste ohne Skalierung.
 *
 * Regel wie beim Radio (RadioLayout.h): Größen, Abstände, Strichstärken und Schriften 1,25-fach, halbe Pixel aufgerundet, Rahmen mit Originalbreite 1 werden 2 Pixel breit. Das Symbolraster bleibt oben rechts bündig, die Uhr sitzt links am Rand. Die 24 Pixel Zusatzbreite (1,28-fach) liegen zwischen Uhr und Symbolen. Logo und Schriftzug der Sperre bleiben in Originalgröße (es gibt keine größere Vorlage, Vergrößern würde unscharf), nur ihr Abstand ist nativ. Werte der Uhr sind relativ zur linken oberen Ecke des Uhrsprites, Werte der Tasten relativ zum Tastenfeld.
 */
namespace MainScreenLayout
{
    constexpr int WIDTH = 1024; ///< Ansicht deckungsgleich mit dem Display, Original 800
    constexpr int HEIGHT = 600; ///< Original 480

    /** @brief Raster der quadratischen Symbole oben rechts, nur die erste Zeile ist belegt. */
    namespace Buttons
    {
        constexpr int EDGE_MARGIN = 28;                                  ///< Abstand zum oberen und rechten Rand, Original 22
        constexpr int SIZE = 125;                                        ///< Original 100
        constexpr int SPACING = 15;                                      ///< Original 12
        constexpr int COLS = 3;                                          ///< wie im Original
        constexpr int ROWS = 4;                                          ///< wie im Original, bestimmt die Uhrgröße
        constexpr int GRID_W = COLS * SIZE + (COLS - 1) * SPACING;       ///< 405, Original 324
        constexpr int GRID_H = ROWS * SIZE + (ROWS - 1) * SPACING;       ///< 545, Original 436
        constexpr int START_X = WIDTH - EDGE_MARGIN - GRID_W;            ///< 591, Original 454
        constexpr int START_Y = EDGE_MARGIN;                             ///< 28, Original 22
        constexpr int STEP_X = SIZE + SPACING;                           ///< 140, Original 112
        constexpr int RADIUS = 13;                                       ///< Ecken, Original 10
        constexpr int BORDER = 2;                                        ///< Rahmen, Original 1
        constexpr int BORDER_PRESSED = 3;                                ///< Rahmen beim Drücken, Original 2
        constexpr int ICON_INSET = 13;                                   ///< Original 10, 12,5 aufgerundet
        constexpr float ICON_SCALE = 1.25f;                              ///< Originalformen nativ neu gerechnet (IconShapes::draw)
        constexpr int ICON_SIZE = 100;                                   ///< Original 80
    }

    /** @brief Analoguhr mit Datumszeile in einem gemeinsamen Sprite links. */
    namespace Clock
    {
        constexpr int MARK_INSET = 13;                                                 ///< Abstand der Markierungen vom Uhrrand, Original 10
        constexpr int DATE_H = 45;                                                     ///< Höhe der Datumszeile, Original 36
        constexpr int DATE_OFFSET = 13;                                                ///< Abstand Uhr -> Datum, Original 10
        constexpr int DIAMETER = Buttons::GRID_H + MARK_INSET - DATE_OFFSET - DATE_H;  ///< 500, Original 400
        constexpr float RADIUS = DIAMETER / 2.0f;                                      ///< 250, Original 200
        constexpr int SPRITE_W = DIAMETER + 38;                                        ///< 538, Original 430 (Durchmesser + 30)
        constexpr int SPRITE_H = DIAMETER + DATE_OFFSET + DATE_H;                      ///< 558, Original 446
        constexpr int SPRITE_X = 15;                                                   ///< Original 12. Links am Rand, 38 Pixel bis zu den Symbolen
        constexpr int SPRITE_Y = Buttons::START_Y - MARK_INSET;                        ///< 15, Original 12
        constexpr int CENTER_X = SPRITE_W / 2;                                         ///< 269, Original 215
        constexpr int CENTER_Y = DIAMETER / 2;                                         ///< 250. Oberkante des Kreises bei 0, Original 200
        constexpr int DATE_Y = DIAMETER + DATE_OFFSET;                                 ///< 513. Oberkante der Datumszeile, Original 410
        constexpr float MINOR_MARK_W = 1.25f;                                          ///< Minutenstriche, Original 1
        constexpr float HOUR_MARK_W = 2.5f;                                            ///< Stundenstriche, Original 2
        constexpr float MAJOR_MARK_W = 3.75f;                                          ///< Viertelstunden sowie NTP und DST, Original 3
        constexpr float SECOND_TIP = 0.625f;                                           ///< Spitze des Sekundenzeigers, Original 0,5
    }

    /** @brief WLAN-Anzeige und gedrehte NTP/DST-Beschriftungen im Zifferblatt. */
    namespace Indicators
    {
        constexpr int SIGNAL_BAR_COUNT = 5;                         ///< wie im Original
        constexpr int SIGNAL_BAR_W = 5;                             ///< Original 4
        constexpr int SIGNAL_BAR_GAP = 5;                           ///< Original 4
        constexpr int SIGNAL_BAR_H[SIGNAL_BAR_COUNT] = {8, 14, 20, 26, 33}; ///< Original 6, 11, 16, 21, 26 (Stufe 5)
        constexpr float SIGNAL_BAR_RADIAL_POS = 0.36f;              ///< Mitte der Balken relativ zum Radius, wie im Original
        constexpr int SSID_OFFSET_Y = 8;                            ///< Abstand Balken -> SSID, Original 6
        constexpr int IP_OFFSET_Y = 16;                             ///< Abstand SSID-Oberkante -> IP, Original 13
        constexpr int SSID_MAX_W = 150;                             ///< Original 120
        constexpr int LABEL_W = 53;                                 ///< NTP/DST-Beschriftung, Original 42
        constexpr int LABEL_H = 23;                                 ///< Original 18
        constexpr float LABEL_RADIAL_POS = 0.68f;                   ///< wie im Original
    }

    /** @brief Sperrbildschirm mit Logo, Schriftzug und PIN-Tastenfeld. */
    namespace Lock
    {
        constexpr int LOGO_W = 450;                                           ///< Originalgröße (logo_450)
        constexpr int LOGO_H = 263;                                           ///< Originalgröße
        constexpr int MADEIN_W = 212;                                         ///< Originalgröße (made_in_germany)
        constexpr int MADEIN_H = 40;                                          ///< Originalgröße
        constexpr int LOGO_GAP = 36;                                          ///< Original 29
        constexpr int LOGO_X = (WIDTH - LOGO_W) / 2;                          ///< 287, mittig wie im Original
        constexpr int LOGO_Y = (HEIGHT - LOGO_H - LOGO_GAP - MADEIN_H) / 2;   ///< 130, beide Bilder zusammen senkrecht mittig
        constexpr int MADEIN_X = (WIDTH - MADEIN_W) / 2;                      ///< 406
        constexpr int MADEIN_Y = LOGO_Y + LOGO_H + LOGO_GAP;                  ///< 429
        constexpr int KEY_W = 81;                                             ///< Original 65
        constexpr int KEY_H = 88;                                             ///< Original 70
        constexpr int KEY_GAP = 8;                                            ///< Original 6
        constexpr int KEY_COLS = 2;                                           ///< wie im Original
        constexpr int KEY_ROWS = 6;                                           ///< wie im Original
        constexpr int KEY_RADIUS = 5;                                         ///< Original 4, eingerückte Rahmenlinien konzentrisch je Pixel um 1 kleiner
        constexpr int KEY_BORDER = 2;                                         ///< Original 1
        constexpr int PULSE_FRAME = 4;                                        ///< Pulsrahmen einschließlich Tastenrand, Original 3
        constexpr int KEYPAD_W = KEY_COLS * KEY_W + (KEY_COLS - 1) * KEY_GAP; ///< 170, Original 136
        constexpr int KEYPAD_H = KEY_ROWS * KEY_H + (KEY_ROWS - 1) * KEY_GAP; ///< 568, Original 450
        constexpr int KEYPAD_MARGIN = 19;                                     ///< Abstand zum oberen und rechten Rand, Original 15. Unten bleiben 13
        constexpr int KEYPAD_X = WIDTH - KEYPAD_MARGIN - KEYPAD_W;            ///< 835, Original 649
        constexpr int KEYPAD_Y = KEYPAD_MARGIN;                               ///< 19, Original 15
    }

    /** @brief Diagonale Sperrgeste an den beiden linken Ecken des Displays. */
    namespace Corner
    {
        constexpr int START_ZONE = 188; ///< Startzonen an beiden linken Ecken, Original 150
        constexpr int CORNER = 40;      ///< Zielecken, Original 32
        constexpr int SWIPE = 63;       ///< Mindestweg je Achse, Original 50
    }
}

#endif
