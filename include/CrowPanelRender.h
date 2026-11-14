#ifndef CROWPANEL_RENDER_H
#define CROWPANEL_RENDER_H
#include <M5GFX.h>

/** @brief Schnelle Übertragung opaker RGB565-Flächen in den DSI-Bildspeicher des CrowPanel. Das Panel liegt nativ quer: Rotation 0 überträgt ohne Drehung, Rotation 2 um 180 Grad gedreht in derselben Übertragung. */
namespace CrowPanelRender
{
    constexpr int PanelWidth = 1024;  ///< Pixel je Zeile des DSI-Bildspeichers
    constexpr int PanelHeight = 600;  ///< Zeilen des DSI-Bildspeichers
#if defined(ARDUINO_ARCH_ESP32)

    /** @brief Zähler der PPA-Zeitgrenze seit dem Start. */
    struct PpaCounters
    {
        uint32_t timeouts; ///< Übertragungen, deren PPA-Fertigmeldung nicht innerhalb der Zeitgrenze kam
        uint32_t late;     ///< Fertigmeldungen, die nach der Zeitgrenze noch kamen
        uint32_t jobs;     ///< PPA-Aufträge seit dem Start
        uint32_t fullUs;   ///< Dauer der letzten Vollbildübertragung in µs mit Cacheabgleich und Rückschreiben, 0 vor der ersten
        bool ready;        ///< PPA eingerichtet und ohne Fehler, sonst überträgt die CPU
    };

    /** @brief Bindet den 1024x600-DSI-Bildspeicher an und richtet die PPA samt Fertigmeldung ein. Ohne PPA bleibt der CPU-Weg. Die Rotation darf danach zwischen 0 und 2 wechseln. @param display Initialisiertes Display in Rotation 0 oder 2. @return false bei anderem Panel, anderer Größe oder anderer Rotation. */
    bool begin(lgfx::LGFX_Device &display);
    /** @brief Überträgt einen opaken 16-Bit-Sprite unter Beachtung des Display-Clippings, andere Sprites gehen über M5GFX. */
    void pushSprite(lgfx::LGFX_Device *display, lgfx::LGFX_Sprite &sprite, int x, int y);
    /** @brief Überträgt einen RGB565-Ausschnitt (M5GFX-Byteordnung) an die Position x/y und schreibt ihn für DSI zurück. In Rotation 2 dreht die PPA (oder die CPU) den Ausschnitt dabei um 180 Grad, x/y bleiben Bildkoordinaten. Andere Rotationen gehen über M5GFX. Nur aus dem UI-Task aufrufen. Wartet höchstens 500 ms auf die Fertigmeldung der PPA. Bleibt sie aus, überträgt die CPU diese Fläche und alle weiteren, bis die verspätete Meldung kommt. @param stride Zeilenbreite der Quelle in Pixeln. */
    void pushRegion(lgfx::LGFX_Device &display, const uint16_t *source, int stride, int x, int y, int width, int height);
    /** @brief Liefert die Zähler der PPA-Zeitgrenze und nimmt dabei eine inzwischen eingetroffene verspätete Meldung an. Nur aus dem UI-Task aufrufen. */
    PpaCounters ppaCounters();
    /** @brief Wartet auf die Fertigmeldung des nächsten Displaybildes (on_refresh_done des DPI-Treibers). Eine schon vorliegende Meldung zählt nicht. Nur aus dem UI-Task aufrufen. @param timeoutMs Höchstwartezeit in ms. @return false ohne Bildsignal oder nach der Zeitgrenze. */
    bool waitFrame(uint32_t timeoutMs);
    /** @brief Zeitpunkt der letzten Bildfertigmeldung auf der Basis von millis(), 0 ohne Signal. */
    uint32_t lastFrameMs();
    /** @brief Bildfertigmeldungen seit dem Start, 0 heißt, der DPI-Treiber meldet keine Bilder. */
    uint32_t frames();
    /** @brief Zeitpunkt der letzten Bildfertigmeldung in µs (untere 32 Bit von esp_timer), 0 ohne Signal. */
    uint32_t lastFrameUs();
    /** @brief Abstand der letzten beiden Bildfertigmeldungen in µs, 0 vor der zweiten Meldung. */
    uint32_t framePeriodUs();
    /** @brief Liefert den gebundenen DSI-Bildspeicher (PanelWidth x PanelHeight, RGB565 ohne Bytetausch) zum direkten Schreiben, wenn display gebunden ist und in Rotation 0 oder 2 steht. Bildpixel (x, y) liegt in Rotation 0 in Zeile y, Spalte x, in Rotation 2 in Zeile PanelHeight - 1 - y, Spalte PanelWidth - 1 - x. Sonst nullptr. Nur UI-Task. Nach dem Schreiben flushFramebuffer aufrufen. */
    uint16_t *framebuffer(lgfx::LGFX_Device &display);
    /** @brief Macht direkt in den Bildspeicher geschriebene Pixel eines Rechtecks in Bildkoordinaten sichtbar, die Panelimplementierung rechnet es in Panelzeilen um und schreibt die betroffenen Cachezeilen für DSI zurück. Nur UI-Task. */
    void flushFramebuffer(lgfx::LGFX_Device &display, int x, int y, int width, int height);
    /** @brief Name des Panels für das Startlog. @return "EK79007" bei gebundenem DSI-Panel, sonst "unbekannt". */
    const char *panelName(lgfx::LGFX_Device &display);
#else
    // Hostbau ohne DSI-Bildspeicher: zeilenweise über M5GFX.
    inline void pushRegion(lgfx::LGFX_Device &display, const uint16_t *source, int stride, int x, int y, int width, int height)
    {
        for (int row = 0; row < height; ++row)
            display.pushImage(x, y + row, width, 1, source + row * stride);
    }

    inline void pushSprite(lgfx::LGFX_Device *display, lgfx::LGFX_Sprite &sprite, int x, int y)
    {
        sprite.pushSprite(display, x, y);
    }

    // Ohne DSI-Bildspeicher gibt es kein Bildsignal, die Nadel läuft frei.
    inline bool waitFrame(uint32_t)
    {
        return false;
    }

    inline uint32_t lastFrameMs()
    {
        return 0;
    }

    inline uint32_t frames()
    {
        return 0;
    }

    inline uint32_t lastFrameUs()
    {
        return 0;
    }

    inline uint32_t framePeriodUs()
    {
        return 0;
    }

    inline uint16_t *framebuffer(lgfx::LGFX_Device &)
    {
        return nullptr;
    }

    inline void flushFramebuffer(lgfx::LGFX_Device &, int, int, int, int)
    {
    }
#endif
}
#endif
