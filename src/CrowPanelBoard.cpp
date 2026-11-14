#include "CrowPanelBoard.h"

#include <driver/gpio.h>
#include <esp_heap_caps.h>
#include <esp_ldo_regulator.h>

namespace
{
    esp_ldo_channel_handle_t s_ldoIo = nullptr; ///< LDO4, bleibt bis zum Ausschalten belegt

    /** @brief Setzt einen Ausgang erst auf den Pegel und schaltet ihn dann als Ausgang, damit kein Zwischenpegel entsteht. */
    void setOutput(uint8_t pin, int level)
    {
        const auto gpio = static_cast<gpio_num_t>(pin);
        gpio_set_level(gpio, level);
        gpio_config_t config{};
        config.pin_bit_mask = 1ULL << pin;
        config.mode = GPIO_MODE_INPUT_OUTPUT;
        gpio_config(&config);
        gpio_set_level(gpio, level);
    }
}

bool CrowPanelBoard::silenceBeforeDisplay()
{
    setOutput(AmplifierPin, 1);
    setOutput(UnusedGatePin, 0);
    setOutput(BacklightPin, 0);
    if (s_ldoIo)
        return true;
    esp_ldo_channel_config_t ldo{};
    ldo.chan_id = LdoIoChannel;
    ldo.voltage_mv = LdoIoMillivolt;
    return esp_ldo_acquire_channel(&ldo, &s_ldoIo) == ESP_OK;
}

bool CrowPanelBoard::testPsram(size_t bytes)
{
    if (bytes == 0 || bytes % sizeof(uint32_t) != 0)
        return false;
    auto buffer = static_cast<volatile uint32_t *>(heap_caps_malloc(bytes, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT));
    if (!buffer)
        return false;
    bool passed = true;
    constexpr uint32_t Patterns[] = {0x55aa55aaU, 0xaa55aa55U};
    for (const uint32_t pattern : Patterns)
    {
        for (size_t index = 0; index < bytes / sizeof(uint32_t); ++index)
            buffer[index] = pattern ^ static_cast<uint32_t>(index);
        for (size_t index = 0; index < bytes / sizeof(uint32_t); ++index)
        {
            if (buffer[index] != (pattern ^ static_cast<uint32_t>(index)))
            {
                passed = false;
                break;
            }
        }
        if (!passed)
            break;
    }
    heap_caps_free(const_cast<uint32_t *>(buffer));
    return passed;
}

bool CrowPanelBoard::prepareRadioCodec()
{
    return setSpeaker(false);
}

bool CrowPanelBoard::powerDownRadioCodec()
{
    return setSpeaker(false);
}

bool CrowPanelBoard::muteRadio()
{
    return setSpeaker(false);
}

bool CrowPanelBoard::unmuteRadio(bool speaker)
{
    return setSpeaker(speaker);
}

bool CrowPanelBoard::setSpeaker(bool on)
{
    gpio_set_level(static_cast<gpio_num_t>(AmplifierPin), on ? 0 : 1);
    return true;
}

bool CrowPanelBoard::readSpeaker(bool &on)
{
    on = gpio_get_level(static_cast<gpio_num_t>(AmplifierPin)) == 0;
    return true;
}

bool CrowPanelBoard::readHeadphone(bool &inserted)
{
    inserted = false;
    return true;
}
