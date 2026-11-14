#ifndef SETTINGS_LAYOUT_H
#define SETTINGS_LAYOUT_H

/**
 * @brief Native 1024x600-Geometrie der Einstellungen und ihrer Dialoge ohne Skalierung.
 *
 * Regel wie beim Radio (RadioLayout.h): Größen, Höhen, Abstände und Schriften 1,25-fach, halbe Pixel aufgerundet, Rahmen und Linien mit Originalbreite 1 werden 2 Pixel breit. Das Menü verteilt sich über die volle Höhe und nutzt Comfortaa Bold 23, seine Breite folgt dem längsten Eintrag, die übrige Breite nimmt der Arbeitsbereich auf. Dialoge liegen 1,25-fach mittig wie im Original. Werte der Seiten sind relativ zur linken oberen Ecke des Arbeitsbereichs, Werte der Dialoge relativ zu deren linker oberer Ecke.
 */
namespace SettingsLayout
{
    constexpr int WIDTH = 1024; ///< Szene deckungsgleich mit dem Display, Original 800
    constexpr int HEIGHT = 600; ///< Original 480

    /** @brief Gemeinsame Rahmen, Radien und Linien von Zeilen, Feldern und Tasten. */
    namespace Style
    {
        constexpr int BORDER = 2;           ///< Rahmen von Feldern, Kacheln und Tasten, Original 1
        constexpr int BORDER_PRESSED = 3;   ///< Rahmen gedrückter Tasten, Original 2
        constexpr int LINE = 2;             ///< Trennlinien, Original 1
        constexpr int FIELD_R = 10;         ///< Zeilen, Felder und Kacheln, Original 8
        constexpr int FIELD_INNER_R = 9;   ///< Original 7
        constexpr int BUTTON_R = 8;         ///< Tasten, Original 6
        constexpr int BUTTON_INNER_R = 6;   ///< Original 5
        constexpr int ACCENT_INSET = 10;    ///< Akzentstreifen oben und unten eingerückt, Original 8
    }

    /** @brief Grobaufteilung: Menü links, Scrollbalken, Arbeitsbereich rechts, Fußzeile unten. */
    namespace Frame
    {
        constexpr int FOOTER_H = 70;                          ///< Original 56
        constexpr int VIEWPORT_H = HEIGHT - FOOTER_H;         ///< 530, Original 424
        constexpr int FOOTER_Y = VIEWPORT_H;                  ///< Original 424
        constexpr int MENU_X = 3;                             ///< Original 2
        constexpr int MENU_W = 228;                           ///< Original 170, Einzug 13 + "Time & time server" in Comfortaa Bold 23 (202) + Rand 13
        constexpr int SECTION_ROW_H = 36;                     ///< Sektionskopf, Original 28, mit den zwölf Einträgen (elf wie im Original-RetroRadio und UKW) über die volle Höhe verteilt (2 x 36 + 12 x 44 = 600)
        constexpr int ITEM_ROW_H = 44;                        ///< Menüeintrag, Original 36, Comfortaa Bold 23 ist 32 px hoch (Aufstrich 25, Unterlänge 7), jeder Menütext in DE und EN bleibt einzeilig
        constexpr int ITEM_ACCENT_W = 5;                      ///< Kategoriestreifen, Original 4
        constexpr int ITEM_TEXT_X = ITEM_ACCENT_W + 8;        ///< 13, Original 4+6
        constexpr int SCROLLBAR_X = MENU_X + MENU_W + 5;      ///< 236, Original 176 (4 nach dem Menü)
        constexpr int SCROLLBAR_W = 8;                        ///< Original 6
        constexpr int DIVIDER_X = SCROLLBAR_X + SCROLLBAR_W;  ///< 244, Original 182
        constexpr int WORK_X = DIVIDER_X + 13;                ///< 257, Original 192 (10 nach dem Scrollbalken)
        constexpr int WORK_Y = 6;                             ///< Original 5
        constexpr int WORK_W = WIDTH - WORK_X - 13;           ///< 754, Original 598 (Rand 10), nimmt die übrige Breite auf
        constexpr int WORK_H = VIEWPORT_H - WORK_Y;           ///< 524, Original 419
        constexpr int WORK_R = 15;                            ///< Original 12
    }

    /** @brief Titelbox oben im Arbeitsbereich. */
    namespace Title
    {
        constexpr int BOX_X = 13;                        ///< Original 10
        constexpr int BOX_Y = 13;                        ///< Original 10
        constexpr int BOX_W = Frame::WORK_W - 2 * BOX_X; ///< 728, Original 578
        constexpr int BOX_H = 86;                       ///< Original 69
        constexpr int BOX_R = 13;                        ///< Original 10
        constexpr int TEXT_X = 35;                       ///< Titel und Untertitel, Original 28
        constexpr int TEXT_Y = 23;                       ///< Original 18
        constexpr int SUB_Y = 63;                        ///< Original 50
    }

    /** @brief Inhaltsbereich unter der Titelbox. */
    namespace Content
    {
        constexpr int X = Title::BOX_X;                      ///< Original 10
        constexpr int Y = Title::BOX_Y + Title::BOX_H + 15;  ///< 114, Original 91
        constexpr int W = Frame::WORK_W - 2 * X;             ///< 728, Original 578
        constexpr int H = Frame::WORK_H - Y - 13;            ///< 397, Original 318
    }

    /** @brief WLAN: drei Profilzeilen, Tastenreihe und Netzwerknamenfeld. */
    namespace Wifi
    {
        constexpr int ROW_H = 58;           ///< Original 46
        constexpr int ROW_GAP = 10;         ///< Original 8
        constexpr int ROW_ACCENT_INSET = 8; ///< Original 6
        constexpr int DOT_X = 28;           ///< Statuspunkt, Original 22
        constexpr int DOT_R = 8;            ///< Original 6
        constexpr int TEXT_X = 50;          ///< Name und Status, Original 40
        constexpr int NAME_Y = 20;          ///< Mitte des Namens, Original 16
        constexpr int STATUS_DY = 18;       ///< Mitte des Status über der Zeilenunterkante, Original 14
        constexpr int ACTION_GAP_Y = 8;     ///< Tastenreihe unter den Profilen, Original 6
        constexpr int ACTION_H = 55;        ///< Original 44
        constexpr int ACTION_GAP = 13;      ///< Original 10
        constexpr int HOST_H = 80;          ///< Netzwerknamenfeld, Original 64
        constexpr int HOST_BOTTOM_GAP = 13; ///< Original 10
        constexpr int HOST_PAD_X = 18;      ///< Original 14
        constexpr int HOST_LINE_GAP = 5;    ///< Original 4
        constexpr int EDIT_W = 163;         ///< ändern-Knopf, Original 130
        constexpr int EDIT_H = 55;          ///< Original 44
    }

    /** @brief Bluetooth (ohne Vorbild im Original): eine Gerätezeile wie ein WLAN-Profil, darunter die Tastenreihe im Abstand der WLAN-Tasten zum letzten Profil und unten das Senderfeld anstelle des Netzwerknamens, alles mit den Maßen aus Wifi. */
    namespace Bluetooth
    {
        constexpr int ACTION_COUNT = 3;                           ///< suchen, test, vergessen
        constexpr int ACTION_SLOTS[ACTION_COUNT] = {0, 2, 3};     ///< Spalten im Raster der vier WLAN-Tasten: jede Taste steht unter ihrem WLAN-Gegenstück (scannen, test, löschen), die Spalte von „passwort“ bleibt frei und trennt die Suche nach neuen Geräten von den Tasten für das gespeicherte
        constexpr int ACTION_Y = Wifi::ROW_H + Wifi::ROW_GAP + Wifi::ACTION_GAP_Y; ///< 76 unter dem Inhaltsanfang, Abstand zur Zeile wie bei WLAN
    }

    /** @brief Umschalter in den Profilzeilen. */
    namespace Toggle
    {
        constexpr int W = 69;       ///< Original 55
        constexpr int H = 36;       ///< Original 29
        constexpr int MARGIN = 18;  ///< Abstand zum rechten Zeilenrand, Original 14
        constexpr int INSET = 3;    ///< Gehäuserand, Original 2
        constexpr int KNOB_R = 13;  ///< Original 10
        constexpr int KNOB_GAP = 1; ///< Abstand des Knopfes zum Innenrand, Original 1
    }

    /** @brief Sprachzeilen. */
    namespace Language
    {
        constexpr int ROW_H = 68;        ///< Original 54
        constexpr int ROW_GAP = 15;      ///< Original 12
        constexpr int ROW_R = 13;        ///< Original 10
        constexpr int TEXT_X = 30;       ///< Original 24
        constexpr int ACTIVE_RIGHT = 25; ///< Original 20
        constexpr int HEADING_H = 40;    ///< Rubriküberschrift „Sprache“ bzw. „Serielle Logs“ auf der Seite Allgemein, Original 32
        constexpr int SECTION_GAP = 30;  ///< Abstand zwischen den Rubriken, die Trennlinie liegt in der Mitte, Original 24
    }

    /** @brief Themenseite (ohne Vorbild im Original): Zeilen wie auf der Sprachseite, so hoch, dass links eine Minivorschau im Seitenverhältnis des Displays Platz hat. */
    namespace Theme
    {
        constexpr int ROW_H = 115;                                  ///< Drei Zeilen und zwei Abstände füllen 375 der 397 Inhaltspixel
        constexpr int ROW_GAP = Language::ROW_GAP;                  ///< 15
        constexpr int PREVIEW_X = Language::TEXT_X;                 ///< 30, Einzug wie der Sprachname
        constexpr int PREVIEW_H = ROW_H - 2 * Style::ACCENT_INSET;  ///< 95, oben und unten bündig mit dem Akzentstreifen
        constexpr int PREVIEW_W = 162;                              ///< 1024:600 wie das Display
        constexpr int PREVIEW_R = Style::BUTTON_R;                  ///< 8
        constexpr int TEXT_X = PREVIEW_X + PREVIEW_W + Language::TEXT_X; ///< 222, Name rechts der Vorschau
        constexpr int CLOCK_R = 38;                                 ///< Zifferblatt links in der Vorschau
        constexpr int CARD_INSET = 10;                              ///< Abstand der Fläche rechts in der Vorschau zum Rand
    }

    /** @brief Sicherheitsseite: Schalter der PIN-Sperre oben, darunter PIN-Hinweis, PIN-Punkte und Ziffernfeld. */
    namespace Security
    {
        constexpr int HINT_Y = Toggle::H + 40; ///< Mitte des Hinweises unter dem Schalter der PIN-Sperre, 76, Original TOGGLE_H + 32
        constexpr int DOTS_Y = HINT_Y + 45;    ///< Mitte der Punkte, 121, Original PIN_HINT_Y + 36
        constexpr int DOT_R = 16;              ///< Original 13
        constexpr int DOT_STEP = 45;           ///< Abstand zweier Punktmitten, die Punkte stehen einzeln, Original 36
        constexpr int PAD_GAP = 5;   ///< Ziffernfeld, Original 4
        constexpr int PAD_KEY_H = 34; ///< Original 27
        constexpr int PAD_R = 8;     ///< Original 6
        constexpr int PAD_TEXT_OY = 3; ///< Original 2
    }

    /** @brief Zeit: drei Auswahlzeilen, fünf Schrittgeber links, der Knopf zum Setzen rechts daneben, unten die Zeile des Sekundenzeigers. */
    namespace Time
    {
        constexpr int FIELD_H = 63;        ///< Original 50
        constexpr int FIELD_GAP = 8;       ///< Original 6
        constexpr int FIELD_PAD_X = 18;    ///< Original 14
        constexpr int LABEL_Y = 8;         ///< Original 6
        constexpr int VALUE_Y = 33;        ///< Original 26
        constexpr int FIELD_COUNT = 3;     ///< Zeitzone, NTP-Server, Intervall
        constexpr int COL_W = 88;         ///< Original 70
        constexpr int COL_GAP = 8;         ///< Original 6
        constexpr int STEP_H = 33;         ///< Plus und Minus, Original 26
        constexpr int VALUE_H = 40;        ///< Original 32
        constexpr int VALUE_GAP = 3;       ///< Zwischen Knopf und Wert, Original 2
        constexpr int TOTAL_H = 2 * STEP_H + VALUE_H + 2 * VALUE_GAP; ///< 112, Original 88
        constexpr int VALUE_OFFSET_Y = 4;  ///< Ziffern optisch mittig, Original 3
        constexpr int SECOND_Y = Content::H - FIELD_H; ///< 334, Zeile „Sekundenzeiger“ am unteren Rand des Inhalts, ohne Vorbild im Original
        constexpr int STEPPER_Y = (FIELD_COUNT * (FIELD_H + FIELD_GAP) - FIELD_GAP + SECOND_Y - TOTAL_H) / 2; ///< 213, mittig zwischen Auswahlzeilen und Sekundenzeile. Original 174 unter den Auswahlzeilen, die Schrittgeber dort mittig mit „zeit setzen“ darunter, hier linksbündig mit „zeit setzen“ rechts daneben
        constexpr int SET_W = 200;         ///< Original 160
        constexpr int SET_H = 56;          ///< Original 45
    }

    /** @brief Zeitfenster: sieben Wochentage mal 24 Stunden. */
    namespace Window
    {
        constexpr int DAY_LABEL_W = 35;  ///< Original 28, das Stundenraster nimmt die zusätzliche Breite auf
        constexpr int CELL_H = 34;       ///< Original 27
        constexpr int CHECK = 19;        ///< Kantenlänge der Checkbox, Original 15
        constexpr int CHECK_LINE = 1;    ///< Rahmen der Kästchen, Original 1, bleibt als Ausnahme 1 Pixel, 2 Pixel wirkten zusammen mit dem Haken zu kräftig
        constexpr int HEADER_H = 33;     ///< Original 26
        constexpr int TOP = 13;          ///< Abstand zum Inhalt, Original 10
        constexpr int DAY_TEXT_X = 10;   ///< Original 8
        constexpr int FRAME_R = 8;       ///< Original 6
        constexpr int INNER_R = 6;       ///< Original 5
        constexpr int FRAME_INSET = 2;   ///< Original 1
        constexpr int FRAME_PAD_Y = 4;   ///< Original 2, oben und unten Rahmen und Innenrand je FRAME_INSET wie im Original
        constexpr float TICK_R = 1.0f;   ///< Radius des Hakenstrichs für drawWideLine, der Strich wird rund doppelt so breit. Original 2 (Strich rund 4 Pixel), dünner, weil der Haken das Kästchen sonst fast füllte
        constexpr int HINT_GAP_Y = 20;   ///< Original 16
        constexpr int HINT_LINE_H = 24;  ///< Original 19
        constexpr int HINT_X = 5;        ///< Original 4
    }

    /** @brief Klang: sechs Zeilen mit Minus, Wert und Plus. */
    namespace Sound
    {
        constexpr int ROW_H = 55;         ///< Original 44
        constexpr int ROW_GAP = 6;        ///< Original 5
        constexpr int FIRST_Y = 5;        ///< Original 4
        constexpr int STEP_W = 73;        ///< Original 58
        constexpr int VALUE_W = 188;      ///< Original 150
        constexpr int STEP_GAP = 13;      ///< Original 10
        constexpr int LABEL_X = 5;        ///< Original 4
        constexpr int VALUE_OFFSET_Y = 4; ///< Original 3
    }

    /** @brief Anzeige: Röhrenkacheln und zwei Wahlzeilen des VU-Meters. */
    namespace Appearance
    {
        constexpr int HINT_H = 27;        ///< Zeilenhöhe von ComfortaaBold20 ohne die tiefere Unterlänge von Zeichen wie ą (Aufstrich 22, Unterlänge 5), Original 23
        constexpr int SEC_LINE_DY = 30;   ///< Linie unter der Überschrift, Original 24
        constexpr int SEC1_Y = 0;         ///< Original 0
        constexpr int TILE_Y = 36;        ///< Original 29
        constexpr int TILE_GAP = 18;      ///< Original 14
        constexpr int TILE_W = (Content::W - 3 * TILE_GAP) / 4; ///< 168, Original 134, die Kacheln füllen wie im Original die Inhaltsbreite
        constexpr int TILE_H = 118;       ///< Original 94
        constexpr int EYE_BOX = 88;      ///< Röhrenvorschau, Original 70
        constexpr int EYE_Y = 5;          ///< Original 4
        constexpr float RING = 6.25f;      ///< Original 5
        constexpr float EM80_HALF_W = 27.5f;  ///< Original 22
        constexpr float EM80_HALF_H = 36.25f;  ///< Original 29
        constexpr float EM84_HALF_W = 15.625f; ///< Original 12,5
        constexpr float EM84_HALF_H = 42.5f;  ///< Original 34
        constexpr int NAME_DY = 16;       ///< Mitte des Namens über der Kachelunterkante, Original 13
        constexpr int HINT1_Y = 160;      ///< Original 128
        constexpr int SEC2_Y = 199;       ///< Original 159
        constexpr int ROW1_Y = 236;       ///< Original 189
        constexpr int ROW2_Y = 320;       ///< Original 256
        constexpr int ROW_H = 45;         ///< Original 36
        constexpr int HINT_DY = 50;       ///< Original 39, 50 statt 49, damit die letzte Hinweiszeile wie im Original genau auf der Unterkante des Inhalts endet
        constexpr int LABEL_W = 188;      ///< Original 150
        constexpr int SEG_GAP = 8;        ///< Original 6
        constexpr int LEVEL_W = 275;      ///< Pegelanzeige, Original 220
        constexpr int LEVEL_GAP = 10;     ///< Zwischen Beschriftung und Pegel, Original 8
        constexpr int TEXT_X = 3;         ///< Überschriften und Hinweise, Original 2
    }

    /** @brief Bildschirmseite (ohne Vorbild im Original): Abschnitte im Raster der Anzeige-Seite, Helligkeit als Zeile wie auf der Klangseite. */
    namespace Screen
    {
        constexpr int ROW1_Y = Appearance::TILE_Y;              ///< Helligkeitszeile, so hoch wie eine Klangzeile
        constexpr int HINT1_Y = ROW1_Y + Sound::ROW_H + 8;      ///< Hinweis unter der Helligkeit
        constexpr int SEC2_Y = Appearance::SEC2_Y;              ///< Abschnitt Ausrichtung
        constexpr int ROW2_Y = Appearance::ROW1_Y;              ///< Wahlzeile normal oder 180 Grad gedreht
        constexpr int HINT2_Y = ROW2_Y + Appearance::HINT_DY;   ///< Hinweis darunter, die Fläche darunter bleibt frei
    }

    /** @brief UKW (ohne Vorbild im Original): eine Senderzeile wie ein WLAN-Profil mit Schalter, darunter Frequenz und Leistung als Klangzeilen (Beschriftung, Minus, Wert, Plus) mit je einem Hinweis, unten das Modulatorfeld anstelle des Netzwerknamens. */
    namespace Ukw
    {
        constexpr int ROW1_Y = Bluetooth::ACTION_Y;                     ///< Frequenzzeile, 76 unter dem Inhaltsanfang wie die Bluetooth-Tasten
        constexpr int HINT1_Y = ROW1_Y + Sound::ROW_H + 8;              ///< 139: Hinweis zur Frequenz
        constexpr int ROW2_Y = HINT1_Y + Appearance::HINT_H + 15;       ///< 181: Leistungszeile
        constexpr int HINT2_Y = ROW2_Y + Sound::ROW_H + 8;              ///< 244: erster Hinweis zur Leistung
        constexpr int HINT3_Y = HINT2_Y + Appearance::HINT_H;           ///< 271: zweiter Hinweis, endet vor dem Modulatorfeld (ab 304)
    }

    /** @brief Info: zwei Spalten mit Kopf, Zeilen und I2C-Zeile. */
    namespace Info
    {
        constexpr int COL_GAP = 18;        ///< Original 14
        constexpr int COL_W = (Content::W - COL_GAP) / 2; ///< 355, Original 282
        constexpr int HDR_H = 33;          ///< Original 26
        constexpr int HDR_PAD_X = 13;      ///< Original 10
        constexpr int ROWS_GAP = 5;        ///< Erste Zeile unter dem Kopf, Original 4
        constexpr int ROW_H = 32;          ///< Original 28 (1,25-fach wären 35), für zehn Zeilen links (mit FTP) über dem I2C-Streifen 32
        constexpr int ROW_PAD_X = 10;      ///< Original 8
        constexpr int I2C_LABEL_GAP = 13;  ///< Original 10
        constexpr int I2C_BOTTOM_GAP = 13; ///< Original 10
        constexpr int I2C_BADGE_Y = 1;     ///< Original 1
        constexpr int SIGNAL_W = 100;      ///< Original 80
        constexpr int SIGNAL_H = 10;       ///< Original 8
        constexpr int SIGNAL_R = 3;        ///< Original 2
        constexpr int SIGNAL_GAP = 8;      ///< Text vor dem Balken, Original 6
    }

    /** @brief Fußzeile mit Speichern, Textknöpfen, Klangfeld, Uhr und Haus-Taste. */
    namespace Footer
    {
        constexpr int CY = Frame::FOOTER_Y + Frame::FOOTER_H / 2; ///< 565, Original 452
        constexpr int BUTTON_Y = Frame::FOOTER_Y + 8;  ///< Original +6
        constexpr int BUTTON_H = 55;                   ///< Original 44
        constexpr int SAVE_W = 188;                    ///< Original 150
        constexpr int ACTION_MIN_W = 150;              ///< Textknöpfe, Original 120
        constexpr int ACTION_PAD = 60;                 ///< Zusatzbreite zum Text, Original 48
        constexpr int ACTION_GAP = 15;                 ///< Original 12
        constexpr int EXIT = 55;                       ///< Haus-Taste, Original 44
        constexpr int EXIT_CX = WIDTH - EXIT / 2 - 13; ///< 984, Original 768 (Rand 10)
        constexpr int CLOCK_W = 140;                   ///< "88:88" in Font7 unskaliert wie die Uhren von Radio und SD-Player, Original 104 bei Textgröße 0,75
        constexpr int CLOCK_H = 56;                    ///< Original 45
        constexpr int CLOCK_X = EXIT_CX - EXIT / 2 - 18 - CLOCK_W; ///< 799, Original 650 (14 vor der Haus-Taste)
        constexpr int CLOCK_Y = Frame::FOOTER_Y + (Frame::FOOTER_H - CLOCK_H) / 2 + 2; ///< 539, Original 430
        constexpr int CLOCK_GAP = 20;                  ///< Mindestabstand von Textknöpfen und Klangfeld zur Uhr, Original 16
    }

    /** @brief Klangfeld in der Fußzeile: Hörprobe, leiser, Lautstärke, lauter. */
    namespace SoundFooter
    {
        constexpr int BUTTON = 55;        ///< Original 44
        constexpr int GAP = 10;           ///< Original 8
        constexpr int DOT = 4;            ///< Original 3, mit Abstand 1 wird die Ziffer 24x34, 1,25-fach (Original 19x27)
        constexpr int DOT_100 = 3;        ///< Schmalere Punkte für 100, Original 2
        constexpr int DOT_SPACE = 1;      ///< Original 1
        constexpr int CHAR_SPACE = 6;     ///< Original 5
        constexpr int CHAR_W = 5 * DOT + 4 * DOT_SPACE;            ///< 24, Original 19
        constexpr int DIGITS_W = 2 * CHAR_W + CHAR_SPACE;          ///< 54, Original 43
        constexpr int DISP_W = 3 * (5 * DOT_100 + 4 * DOT_SPACE);  ///< 57 für 100, Original 43
        constexpr int DISP_H = 7 * DOT + 6 * DOT_SPACE;            ///< 34, Original 27
        constexpr int FRAME_PAD = 10;     ///< Original 8
        constexpr int FRAME_W = DISP_W + 2 * FRAME_PAD;            ///< 77, Original 59
        constexpr int BLOCK_W = BUTTON * 3 + FRAME_W + GAP * 3;    ///< 272, Original 215
        constexpr int BLOCK_RIGHT = Footer::CLOCK_X - Footer::CLOCK_GAP; ///< Original 634
        constexpr int PLAY_CX = BLOCK_RIGHT - BLOCK_W + BUTTON / 2;
        constexpr int DOWN_CX = PLAY_CX + BUTTON + GAP;
        constexpr int FRAME_X = DOWN_CX + BUTTON / 2 + GAP;
        constexpr int DISP_X = FRAME_X + FRAME_PAD;
        constexpr int UP_CX = FRAME_X + FRAME_W + GAP + BUTTON / 2;
    }

    /** @brief Auswahlliste für Zeitzone und Intervall, 1,25-fach mittig. */
    namespace Picker
    {
        constexpr int W = 575;            ///< Original 460
        constexpr int H = 500;            ///< Original 400
        constexpr int X = (WIDTH - W) / 2;  ///< 224, Original 170
        constexpr int Y = (HEIGHT - H) / 2; ///< 50, Original 40
        constexpr int BORDER = 3;         ///< Original 2
        constexpr int R = 15;             ///< Original 12
        constexpr int INNER_R = 13;       ///< Original 10
        constexpr int TITLE_Y = 43;       ///< Mitte des Titels, Original 34
        constexpr int LIST_X = 20;        ///< Original 16
        constexpr int LIST_Y = 75;        ///< Original 60
        constexpr int LIST_WIDTH = 535;   ///< Original 428
        constexpr int LIST_HEIGHT = 335;  ///< Original 268
        constexpr int ROW_STEP = 48;      ///< Original 38
        constexpr int ROW_H = 45;         ///< Original 36
        constexpr int ROW_R = 6;          ///< Original 5
        constexpr int TEXT_X = 18;        ///< Original 14
        constexpr int END_GAP = 3;        ///< Original 2
        constexpr int SELECT_Y = 158;     ///< Abstand des gewählten Eintrags zur Listenoberkante beim Öffnen, Original 126
        constexpr int DRAG = 6;           ///< Ziehschwelle, Original 5
        constexpr int CANCEL_X = 188;     ///< Original 150
        constexpr int CANCEL_Y = 425;     ///< Original 340
        constexpr int CANCEL_W = 200;     ///< Original 160
        constexpr int CANCEL_H = 55;      ///< Original 44
    }

    /** @brief Meldungen, die Innenmaße stehen nativ in SettingsMessageBox. */
    namespace Message
    {
        constexpr int X = 262;       ///< Original 200
        constexpr int Y = 175;       ///< Original 140
        constexpr int W = 500;       ///< Original 400
        constexpr int H = 250;       ///< Original 200
        constexpr int TALL_H = 275;  ///< Meldungen mit Neustartfrage, Original 220
        constexpr int WIDE_W = 525;  ///< Werkseinstellungen, Original 420
        constexpr int WIDE_Y = 163;  ///< Original 130
    }

    /** @brief Fortschrittsdialog des WLAN-Tests, mittig. */
    namespace Progress
    {
        constexpr int W = 500;          ///< Original 400
        constexpr int H = 250;          ///< Original 200
        constexpr int BORDER = 2;       ///< Original 1
        constexpr int R = 5;            ///< Original 4
        constexpr int MARGIN = 25;      ///< Original 20
        constexpr int TITLE_Y = 23;     ///< Original 18
        constexpr int LINE_Y = 60;      ///< Original 48
        constexpr int LINE_H = 3;       ///< Original 2
        constexpr int TEXT_Y = 82;      ///< Original 65
        constexpr int TEXT_LEADING = 4; ///< Original 2, ComfortaaBold18 ist 24 hoch, Zeilenraster 28 (Original 22)
        constexpr int BAR_DY = 82;      ///< Balkenoberkante über der Unterkante, Original 65
        constexpr int BAR_H = 50;       ///< Original 40
        constexpr int SEGMENT = 1;      ///< Original 1
        constexpr int SEGMENT_GAP = 3;  ///< Original 2
    }

    /** @brief WLAN-Auswahl mit fünf sichtbaren Zeilen, mittig. */
    namespace Networks
    {
        constexpr int W = 625;              ///< Original 500
        constexpr int H = 375;              ///< Original 300
        constexpr int X = (WIDTH - W) / 2;  ///< 199, Original 150
        constexpr int Y = (HEIGHT - H) / 2; ///< 112, Original 90
        constexpr int BORDER = 2;           ///< Original 1
        constexpr int R = 5;                ///< Original 4
        constexpr int TITLE_X = 13;         ///< Original 10
        constexpr int TITLE_Y = 32;         ///< Titelmitte, Original 25
        constexpr int CLOSE = 38;           ///< Schließen-Taste, Original 30
        constexpr int CLOSE_RIGHT = 50;     ///< Linke Kante vor dem rechten Rand, Original 40
        constexpr int CLOSE_Y = 13;         ///< Original 10
        constexpr int LIST_X = 13;          ///< Original 10
        constexpr int LIST_Y = 63;          ///< Original 50
        constexpr int LIST_WIDTH = W - 2 * LIST_X; ///< 599, Original 480
        constexpr int LIST_HEIGHT = 232;    ///< Original 185
        constexpr int ROW_H = 45;           ///< Original 36
        constexpr int ROW_TEXT_X = 13;      ///< Original 10
        constexpr int SIGNAL_RIGHT = 13;    ///< Original 10
        constexpr int LOCK_RIGHT = 85;     ///< Schlossmitte vor dem rechten Listenrand, Original 68
        constexpr int LOCK_Y = 20;          ///< Original 16
        constexpr int SEP_X = 6;            ///< Trennlinie eingerückt, Original 5
        constexpr int BUTTON_W = 100;       ///< Original 80
        constexpr int BUTTON_H = 56;        ///< Original 45
        constexpr int OK_RIGHT = 113;       ///< Linke Kante vor dem rechten Rand, Original 90
        constexpr int SCAN_RIGHT = 225;     ///< Original 180
        constexpr int BUTTON_DY = 69;       ///< Oberkante über der Unterkante, Original 55
        constexpr int SCROLL_RIGHT = 23;    ///< Original 18
        constexpr int SCROLL_W = 10;        ///< Original 8
        constexpr int SCROLL_MIN_H = 25;    ///< Original 20
        constexpr int SCROLL_R = 4;         ///< Original 3
        constexpr int DRAG = 6;             ///< Ziehschwelle, Original 5
    }

    /** @brief Bildschirmtastatur, mittig. */
    namespace Keyboard
    {
        constexpr int W = 963;           ///< Original 770
        constexpr int KEY_H = 56;         ///< Original 45
        constexpr int KEY_GAP = 5;        ///< Original 4
        constexpr int R = 5;              ///< Rahmen, Eingabefeld und Tasten, Original 4
        constexpr int BORDER = 2;         ///< Original 1
        constexpr int PADDING = 13;       ///< Original 10
        constexpr int LABEL_H = 50;       ///< Original 40
        constexpr int INPUT_H = 45;       ///< Original 36
        constexpr int INPUT_MARGIN = 10;  ///< Original 8
        constexpr int TITLE_Y = 32;       ///< Titelmitte, Original 25
        constexpr int CLOSE = 38;         ///< Schließen-Taste, Original 30
        constexpr int CLOSE_RIGHT = 50;   ///< Original 40
        constexpr int CLOSE_Y = 13;       ///< Original 10
        constexpr int TEXT_X = 10;        ///< Texteinzug im Eingabefeld, Original 8
        constexpr int HIDDEN_DY = 5;      ///< Sternchen tiefer gesetzt, Original 4
        constexpr int CURSOR_INSET = 8;   ///< Original 6
        constexpr int CURSOR_W = 1;       ///< Original 1
        constexpr int LABEL_OFFSET = 19;  ///< Einzug links oder rechts ausgerichteter Tastentexte, Original 15
    }
}
#endif
