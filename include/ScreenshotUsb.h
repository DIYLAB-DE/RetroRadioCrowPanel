#ifndef SCREENSHOT_USB_H
#define SCREENSHOT_USB_H

#include <M5GFX.h>
#include "CrowPanelRender.h"

/** @brief Überträgt eine Displayaufnahme aus dem gemeinsamen Aufnahmeplatz als geprüfte RGB565-Lauflängen über den Kanal, der sie angefordert hat (UART0 oder CDC an J16). */
class ScreenshotUsb
{
public:
    /** @brief Bindet den gemeinsamen Aufnahmeplatz an, den auch der Web-Screenshot nutzt. @param pixels 1024x600 RGB565-Pixel, gehört dem Aufrufer und lebt bis zum Ende. @return true bei vorhandenem Platz. */
    bool begin(uint16_t *pixels);
    /** @brief Liest das Display im UI-Task in den Aufnahmeplatz. @param display Aktuelles 1024x600-Display. @param out Kanal der Anforderung, lebt bis zum Ende. @param uart true für UART0: Pakete gehen dann nur, solange in dessen Sendepuffer Platz für ein ganzes Paket ist. Der CDC-Kanal wartet je Paket höchstens CrowPanelUsb::TxTimeoutMs. */
    void capture(lgfx::LGFX_Device &display, Print &out, bool uart);
    /** @brief Überträgt 2 ms lang Pakete, an UART0 höchstens vier. Bricht eine Übertragung nach 120 s oder bei einem Schreibfehler ab. Aus dem UI-Task aufrufen. */
    void poll();

    /** @brief Bricht ausschließlich die laufende Bildübertragung ab. */
    void cancel()
    {
        m_active = false;
    }

    /** @brief Meldet eine laufende Übertragung, während der der Aufnahmeplatz nicht überschrieben werden darf. @return true bis zum Ende oder Abbruch. */
    bool active() const
    {
        return m_active;
    }

private:
    static constexpr uint32_t Width = CrowPanelRender::PanelWidth, Height = CrowPanelRender::PanelHeight, Pixels = Width * Height;
    uint16_t *m_pixels = nullptr;                      ///< Aufnahmeplatz, gehört dem Aufrufer
    Print *m_out = nullptr;                            ///< Kanal der laufenden Übertragung
    bool m_uart = true;                                ///< Kanal ist UART0 mit Flusskontrolle über den Sendepuffer
    uint32_t m_id = 0, m_position = 0, m_started = 0;  ///< Aufnahmenummer, nächstes Pixel der Übertragung, Startzeit in ms
    bool m_active = false, m_header = false;           ///< Übertragung läuft, Kopfzeile fehlt noch
};

#endif
