#ifndef SD_PLAYER_LAYOUT_H
#define SD_PLAYER_LAYOUT_H
#include "RadioLayout.h"

/**
 * @brief Native 1024x600-Geometrie des SD-Players und seines Dateidialogs ohne Skalierung.
 *
 * Regel wie beim Radio (RadioLayout.h): Größen, Höhen und Schriften 1,25-fach, halbe Pixel aufgerundet, Rahmen und Linien mit Originalbreite 1 werden 2 Pixel breit. Der untere Bereich mit Drehknopf, Reglern, Visualizer, Uhren und Tasten liegt exakt wie beim Radio (RadioLayout). Oben behalten Kassette und Cover 1,25-fach ihre Lage am linken Rand. Die zusätzliche Breite der nativen Fläche nimmt die Playlist auf.
 */
namespace SdPlayerLayout
{
    namespace RL = RadioLayout;
    constexpr int WIDTH = RL::WIDTH;   ///< Breite der Szene, deckungsgleich mit dem Display
    constexpr int HEIGHT = RL::HEIGHT; ///< Höhe der Szene

    /** @brief Trennlinien, dunkle Spielerfläche und Lücke zur Playlist. */
    namespace Frame
    {
        constexpr int DIVIDER_H = RL::Scale::DIVIDER_HEIGHT;     ///< Original 3
        constexpr int TOP_DIVIDER_Y = RL::Scale::TOP_DIVIDER_Y;  ///< Original 0
        constexpr int BOTTOM_DIVIDER_Y = RL::Scale::BOTTOM_DIVIDER_Y; ///< Original 307
        constexpr int PANEL_Y = RL::Scale::Y;                    ///< Original 5
        constexpr int PANEL_H = RL::Scale::HEIGHT;               ///< Original 300
        constexpr int PANEL_W = 676;                             ///< Original 540, endet bündig mit dem Cover
        constexpr int GAP_W = 13;                                ///< Schwarze Lücke vor der Playlist, Original 10
    }

    /** @brief Kassette mit Fortschritt und Transporttasten darunter. */
    namespace Cassette
    {
        constexpr int X = 13;   ///< Original 10. Rand 1,28-fach wie die Senderskala des Radios
        constexpr int Y = 19;   ///< Original 15
        constexpr int W = 356;  ///< Original 285
        constexpr int H = 230;  ///< Original 184
        constexpr int WRAP_SPRITE = 64;     ///< Naben-Sprite, Original 48. Fasst den größten umgerechneten Deckradius 30,2
        constexpr int LABEL_MARGIN = 8;     ///< Textrand im Etikettstreifen, Original 6
    }

    /** @brief Fortschrittsbalken mit Zeitanzeige. */
    namespace Progress
    {
        constexpr int X = Cassette::X;   ///< Original 10
        constexpr int Y = 264;           ///< Original 211
        constexpr int W = Cassette::W;   ///< Original 285, bündig mit Kassette und Tastenreihe
        constexpr int H = 30;            ///< Original 24
        constexpr int TOUCH_Y = 254;     ///< Trefferfläche, Original 203
        constexpr int TOUCH_H = 50;      ///< Original 40
        constexpr int BAR_LINE_Y = 28;   ///< Rote Linie am unteren Rand, Original 22
        constexpr int BAR_LINE_H = 3;    ///< Original 2
        constexpr int TEXT_Y = 15;       ///< Textmitte, Original 12
        constexpr int CURRENT_X = 115;   ///< Linke Kante der Laufzeit, Original 92
        constexpr int SLASH_X = 178;     ///< Mitte des Schrägstrichs, Original 142
        constexpr int END_X = 190;       ///< Linke Kante der Gesamtzeit, Original 152
    }

    /** @brief Fünf Transporttasten unter der Kassette. */
    namespace Transport
    {
        constexpr int Y = 313;           ///< Original 250
        constexpr int SIZE = 56;         ///< Original 45
        constexpr int GAP = 19;          ///< Original 15, 19 statt 18,75 füllt die Reihe wie im Original genau die Kassettenbreite
        constexpr int X0 = Cassette::X;  ///< Original 10
        constexpr int STEP = SIZE + GAP; ///< Original 60
        constexpr int RADIUS = RL::Buttons::RADIUS;             ///< Original 4
        constexpr int BORDER = RL::Buttons::BORDER;             ///< Original 1
        constexpr int BORDER_PRESSED = RL::Buttons::BORDER_PRESSED; ///< Original 2
    }

    /** @brief Cover und Infofeld darunter, bündig mit dem Ende der Spielerfläche. */
    namespace Cover
    {
        constexpr int W = 288;                    ///< Original 230
        constexpr int H = 275;                    ///< Original 220
        constexpr int X = Frame::PANEL_W - W;     ///< 388, Original 310 = 540-230
        constexpr int Y = Cassette::Y;            ///< Original 15
        constexpr int LINE = 2;                   ///< Seitenlinien, Original 1
        constexpr int INITIALS_XY = 19;           ///< Initialen, Original 15
        constexpr int TEXT_MARGIN = 19;           ///< Abstand der Textzeile vom Rand, Original 15
        constexpr int DETAILS_Y = Transport::Y;   ///< Infofeld, Original 250
        constexpr int DETAILS_H = Transport::SIZE; ///< Original 45
    }

    /** @brief Infofeld unter dem Cover mit Kapazität, Album, Titelnummer und Formatmarken. */
    namespace Details
    {
        constexpr int TEXT_X = 10;        ///< Original 8
        constexpr int LINE1_Y = 8;        ///< Original 6
        constexpr int LINE2_Y = 33;       ///< Original 26
        constexpr int TEXT_W = 268;       ///< Original 214
        constexpr int TEXT_W_PLAYING = 265; ///< Original 212
        constexpr int BADGE_Y = 29;       ///< Original 23
        constexpr int BADGE_H = 23;       ///< Original 18
        constexpr int BADGE_PAD = 10;     ///< Original 8
        constexpr int BADGE_GAP = 3;      ///< Original 2
        constexpr int BADGE_RIGHT = 6;    ///< Abstand zum rechten Rand, Original 5
        constexpr int TRACK_GAP = 6;      ///< Abstand der Titelnummer zu den Marken, Original 5
    }

    /** @brief Playlist rechts mit Scrollbalken am Displayrand. */
    namespace Playlist
    {
        constexpr int SCROLLBAR_W = 6;                                   ///< Original 5
        constexpr int X = Frame::PANEL_W + Frame::GAP_W;                 ///< 689, Original 550
        constexpr int Y = Frame::PANEL_Y;                                ///< Original 5
        constexpr int W = WIDTH - SCROLLBAR_W - X;                       ///< 329. Original 245, nimmt die zusätzliche Breite auf
        constexpr int H = Frame::PANEL_H;                                ///< Original 300
        constexpr int ROW_H = 34;                                        ///< Original 27
        constexpr int SCROLLBAR_X = WIDTH - SCROLLBAR_W;                 ///< Original 795
        constexpr int SCROLLBAR_MIN_H = 25;                              ///< Original 20
        constexpr int NUMBER_X = 13;                                     ///< Original 10
        constexpr int NAME_GAP = 19;                                     ///< Abstand nach "999.", Original 15
        constexpr int NAME_MARGIN = 13;                                  ///< Rechter Textrand, Original 10
        constexpr int OVERSCROLL = 63;                                   ///< Gedämpfter Überlauf beim Ziehen, Original 50
        constexpr int DRAG_THRESHOLD = 13;                               ///< Ab hier gilt der Kontakt als Ziehen, Original 10
        constexpr int EMPTY_ICON_SCALE = 5;                              ///< Ordnersymbol, Original 4
        constexpr int EMPTY_ICON_Y = 98;                                ///< Original 78
        constexpr int EMPTY_TITLE_Y = 210;                               ///< Original 168
        constexpr int EMPTY_HINT1_Y = 245;                               ///< Original 196
        constexpr int EMPTY_HINT2_Y = 270;                               ///< Original 216
        constexpr int EMPTY_HINT_MARGIN = 13;                            ///< Original 10
    }

    /** @brief Trefferfläche für Wisch- und Haltegesten auf dem Visualizer, ohne Uhren- und Tastenzeile. */
    namespace Visualizer
    {
        constexpr int TOUCH_H = 89; ///< Original 71
    }

    /** @brief Statuszeile wie die Infozeile des Radios. */
    namespace Footer
    {
        constexpr int Y = RL::Footer::Y;           ///< Original 316
        constexpr int HEIGHT = RL::Footer::HEIGHT; ///< Original 32
        constexpr int LINE = RL::Footer::LINE;     ///< Original 1
    }

    /** @brief Vier Symboltasten rechts unten im Raster der Radiotasten X1 bis X4, alle so breit wie das Haus. */
    namespace Buttons
    {
        constexpr int Y = RL::Buttons::Y;         ///< Original 435
        constexpr int H = RL::Buttons::H;         ///< Original 45
        constexpr int W = RL::Buttons::W;         ///< 56, Original 45 bis 75 je nach Text
        constexpr int POWER_X = RL::Buttons::X4;  ///< 968, Original 755
        constexpr int RESET_X = RL::Buttons::X3;  ///< 899, Original 678
        constexpr int CLEAR_X = RL::Buttons::X2;  ///< 830, Original 598
        constexpr int BROWSE_X = RL::Buttons::X1; ///< 761, Original 513
    }

    /** @brief Dateidialog 1,25-fach mittig. Alle Innenmaße relativ zur linken oberen Ecke. */
    namespace Explorer
    {
        constexpr int W = 688;                    ///< Original 550
        constexpr int H = 438;                    ///< Original 350
        constexpr int X = (WIDTH - W + 1) / 2;    ///< 168, Original 125
        constexpr int Y = (HEIGHT - H + 1) / 2;   ///< 81, Original 65
        constexpr int BORDER = 2;                 ///< Original 1
        constexpr int RADIUS = 5;                 ///< Original 4
        constexpr int TEXT_X = 19;                ///< Titel, Pfad, Linien und Status, Original 15
        constexpr int TITLE_Y = 19;               ///< Original 15
        constexpr int PATH_Y = 44;                ///< Original 35
        constexpr int PATH_W = 650;               ///< Original 520
        constexpr int LINE_W = 650;               ///< Original 520
        constexpr int LINE_H = 2;                 ///< Original 1
        constexpr int LINE1_Y = 75;               ///< Original 60
        constexpr int LINE2_Y = 115;              ///< Original 92
        constexpr int HEADER_Y = 96;             ///< Mitte der Spaltenköpfe, Original 77
        constexpr int HEADER_NAME_X = 23;         ///< Original 18
        constexpr int HEADER_TYPE_X = 483;        ///< Original 386
        constexpr int HEADER_SIZE_X = 658;        ///< Original 526
        constexpr int LIST_X = 4;                 ///< Original 3
        constexpr int LIST_Y = 118;               ///< Original 94
        constexpr int LIST_WIDTH = 673;           ///< Original 538
        constexpr int LIST_HEIGHT = 239;          ///< Original 191
        constexpr int ROW_H = 39;                 ///< Original 31
        constexpr int ROW_TEXT_Y = 19;            ///< Original 15
        constexpr int ROW_LEFT = 19;              ///< Linker Rand der Zeile, Original 15
        constexpr int ICON_GAP = 30;              ///< Textversatz nach Ordnersymbol, Original 24
        constexpr int ICON_Y = 8;                 ///< Ordnersymbol, Original 6
        constexpr int ICON_UP_Y = 11;             ///< Symbol für den übergeordneten Ordner, Original 9
        constexpr float ICON_SCALE = 1.25f;        ///< Faktor für IconShapes::draw
        constexpr int TYPE_X = 479;               ///< Mitte der Typspalte in der Liste, Original 383
        constexpr int SIZE_RIGHT = 654;           ///< Rechte Kante der Größenspalte, Original 523
        constexpr int NAME_RESERVE = 63;          ///< Abstand des Namens vor der Typspalte, Original 50
        constexpr int SCROLLBAR_X = 678;          ///< Original 542
        constexpr int SCROLLBAR_W = 6;            ///< Original 5
        constexpr int SCROLLBAR_MIN_H = 25;       ///< Original 20
        constexpr int STATUS1_Y = 365;            ///< Original 292
        constexpr int STATUS2_Y = 388;            ///< Original 310
        constexpr int BUTTON_W = 113;             ///< Original 90
        constexpr int BUTTON_H = 56;              ///< Original 45
        constexpr int OK_CX = 481;                ///< Mitte "ok", Original 385
        constexpr int CANCEL_CX = 613;            ///< Mitte "abbruch", Original 490
        constexpr int BUTTON_CY = 391;            ///< Original 313
        constexpr int DRAG_THRESHOLD = 13;        ///< Original 10
        constexpr int OVERSCROLL = 100;           ///< Original 80
    }
}
#endif
