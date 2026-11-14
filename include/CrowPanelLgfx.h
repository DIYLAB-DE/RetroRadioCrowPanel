#ifndef CROWPANEL_LGFX_H
#define CROWPANEL_LGFX_H

#include <M5GFX.h>
#include <lgfx/v1/platforms/esp32p4/Bus_DSI.hpp>
#include <lgfx/v1/platforms/esp32p4/Panel_DSI.hpp>

/** @brief EK79007 an MIPI-DSI als M5GFX-Panel. Startet wie esp_lcd_ek79007 2.0.2 von Espressif (Befehlsfolge, dann DPI) und schreibt, anders als Panel_DSI, kein MADCTL und COLMOD: Die Lage kommt aus den Strap-Widerständen des Panels (in H5 ohne Spiegelung bestätigt). */
class Panel_EK79007 : public lgfx::Panel_DSI
{
public:
    /** @brief Wie Panel_DSI::init, mit eigener Panelfolge. @return true, wenn DPI läuft und der Bildspeicher als Zeilenfeld gebunden ist. */
    bool init(bool use_reset) override;
};

/** @brief Display der CrowPanel Advanced 7", 9" und 10.1" (gleiches Panel-IC und Timing): Bus_DSI mit 2 Lanes zu 900 Mbit/s und LDO3, Panel_EK79007 mit dem Hersteller-Timing (1024x600, rund 55,9 Hz), Hintergrundlicht PWM an IO31. Kein Touch hier, der GT911 läuft über CrowPanelTouch und Wire. */
class CrowPanelLgfx : public lgfx::LGFX_Device
{
public:
    static constexpr int Width = 1024;  ///< Pixel waagerecht, das Panel liegt nativ quer
    static constexpr int Height = 600;  ///< Pixel senkrecht

    CrowPanelLgfx();

private:
    lgfx::Bus_DSI m_bus;
    Panel_EK79007 m_panel;
    lgfx::Light_PWM m_light;
};

#endif
