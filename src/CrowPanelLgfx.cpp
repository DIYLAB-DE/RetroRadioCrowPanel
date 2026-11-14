#include "CrowPanelLgfx.h"

#include <cstring>

#include <esp_lcd_mipi_dsi.h>
#include <esp_lcd_panel_ops.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace
{
    constexpr uint16_t LaneMbps = 900;      ///< Hardwareleitfaden V1.2
    constexpr uint8_t Lanes = 2;
    constexpr uint8_t LdoDsiChannel = 3;    ///< versorgt VDD_MIPI_DPHY
    constexpr uint32_t LdoDsiMillivolt = 2500;
    constexpr uint8_t LcdResetPin = 41;     ///< Pull-up 2 kOhm auf VDDPST_5 (LDO4)
    constexpr uint8_t BacklightPin = 31;
    constexpr uint32_t BacklightHz = 30000;

    // Befehlsfolge aus esp_lcd_ek79007 2.0.2 (Espressif, Apache-2.0, esp-iot-solution 5fbb2597): 0xB2 mit 0x10 wählt 2 Lanes, 0x80 bis 0x86 sind die Herstellervorgaben, 0x11 verlässt den Schlaf. Format von M5GFX Panel_DSI: Länge (Befehl plus Daten), Befehl, Daten, Ende mit 0.
    constexpr uint8_t InitFolge[] = {
        2, 0xB2, 0x10,
        2, 0x80, 0x8B,
        2, 0x81, 0x78,
        2, 0x82, 0x84,
        2, 0x83, 0x88,
        2, 0x84, 0xA8,
        2, 0x85, 0xE3,
        2, 0x86, 0x88,
        1, 0x11,
        0};
    constexpr uint32_t SchlafEndeMs = 120; ///< Wartezeit nach 0x11 laut Espressif-Treiber
}

bool Panel_EK79007::init(bool use_reset)
{
    // Ablauf von M5GFX Panel_DSI::init (M5GFX 0.2.33, Lizenz FreeBSD), nur die Panelfolge ist ersetzt.
    if (_lines_buffer != nullptr)
        return false;
    if (!Panel_FrameBufferBase::init(use_reset))
        return false;
    auto *bus = getBusDSI();
    if (bus == nullptr || !init_dpi(bus))
        return false;
    for (const uint8_t *p = InitFolge; p[0] != 0; p += p[0] + 1)
        bus->writeParams(p[1], &p[2], p[0] - 1);
    vTaskDelay(pdMS_TO_TICKS(SchlafEndeMs));
    if (esp_lcd_panel_init(_disp_panel_handle) != ESP_OK)
        return false;
    esp_lcd_dpi_panel_get_frame_buffer(_disp_panel_handle, 1, &(_config_detail.buffer));
    auto *ptr = static_cast<uint8_t *>(_config_detail.buffer);
    if (ptr == nullptr)
        return false;
    const auto height = _cfg.panel_height;
    const size_t tableBytes = height * sizeof(void *);
    auto **lines = static_cast<uint8_t **>(lgfx::heap_alloc_dma(tableBytes));
    if (lines == nullptr)
        return false;
    memset(lines, 0, tableBytes);
    const size_t lineBytes = ((_cfg.panel_width * _write_bits >> 3) + 3) & ~3;
    _lines_buffer = lines;
    for (int y = 0; y < height; ++y)
    {
        lines[y] = ptr;
        ptr += lineBytes;
    }
    return true;
}

CrowPanelLgfx::CrowPanelLgfx()
{
    {
        auto config = m_bus.config();
        config.lane_mbps = LaneMbps;
        config.lane_num = Lanes;
        config.bus_id = 0;
        config.ldo_chan_id = LdoDsiChannel;
        config.ldo_voltage_mv = LdoDsiMillivolt;
        m_bus.config(config);
        m_panel.setBus(&m_bus);
    }
    {
        auto config = m_panel.config();
        config.memory_width = Width;
        config.memory_height = Height;
        config.panel_width = Width;
        config.panel_height = Height;
        config.offset_x = 0;
        config.offset_y = 0;
        config.offset_rotation = 0;
        config.pin_rst = LcdResetPin;
        config.readable = true;
        config.rgb_order = true;
        m_panel.config(config);
    }
    {
        auto detail = m_panel.config_detail();
        // Hersteller-Timing aus dem Hardwareleitfaden V1.2 (H5): Espressifs Vorgabe versetzt das Bild sichtbar.
        detail.dpi_freq_mhz = 51;
        detail.hsync_back_porch = 160;
        detail.hsync_pulse_width = 70;
        detail.hsync_front_porch = 160;
        detail.vsync_back_porch = 23;
        detail.vsync_pulse_width = 10;
        detail.vsync_front_porch = 12;
        m_panel.config_detail(detail);
    }
    {
        auto config = m_light.config();
        config.pin_bl = BacklightPin;
        config.invert = false;
        config.freq = BacklightHz;
        config.pwm_channel = 7;
        m_light.config(config);
        m_panel.setLight(&m_light);
    }
    setPanel(&m_panel);
}
