#include "CrowPanelTouch.h"

#include <Arduino.h>
#include <Wire.h>

#include "driver/gpio.h"

namespace
{
    constexpr gpio_num_t PIN_RESET = GPIO_NUM_40;   ///< Pull-up 2 kOhm auf VDDPST_5
    constexpr gpio_num_t PIN_INT = GPIO_NUM_42;     ///< ohne Pull-up auf der Platine (R75 nicht bestückt)
    constexpr uint32_t I2C_TAKT_HZ = 100000;          ///< wie im Original-RetroRadio: der ganze Bus mit 100 kHz, weil eine DS1307 nicht mehr verträgt
    constexpr uint16_t REG_PRODUKT = 0x8140;        ///< vier Byte ASCII, „911“
    constexpr uint16_t REG_KONFIGURATION = 0x8047;  ///< Konfigurationsversion, 0 = nicht geladen
    constexpr uint16_t REG_AUFLOESUNG = 0x8048;     ///< X und Y je 16 Bit, niederwertiges Byte zuerst
    constexpr uint16_t REG_STATUS = 0x814E;         ///< Bit 7 neue Daten, Bit 0 bis 3 Anzahl der Punkte
    constexpr uint16_t REG_PUNKT1 = 0x814F;         ///< je Punkt 8 Byte: Kennung, X, Y, Größe, frei
    constexpr size_t PUNKT_BYTES = 8;
} // namespace

bool CrowPanelTouch::begin()
{
    // Adresswahl nach Datenblatt: INT Low während Reset und mindestens 5 ms danach ergibt 0x5D, dann INT als Eingang.
    gpio_set_level(PIN_INT, 0);
    gpio_set_level(PIN_RESET, 0);
    gpio_config_t konfiguration = {};
    konfiguration.pin_bit_mask = (1ULL << PIN_INT) | (1ULL << PIN_RESET);
    konfiguration.mode = GPIO_MODE_OUTPUT;
    gpio_config(&konfiguration);
    gpio_set_level(PIN_INT, 0);
    gpio_set_level(PIN_RESET, 0);
    delay(10);
    gpio_set_level(PIN_RESET, 1);
    delay(10);
    gpio_set_direction(PIN_INT, GPIO_MODE_INPUT);
    delay(60);

    if (!Wire.begin(SDA, SCL, I2C_TAKT_HZ))
    {
        Serial.println("TOUCH I2C=fehlgeschlagen");
        return false;
    }
    uint8_t produkt[4] = {};
    uint8_t version = 0;
    uint8_t aufloesung[4] = {};
    if (!readRegister(REG_PRODUKT, produkt, sizeof(produkt)) || !readRegister(REG_KONFIGURATION, &version, 1) || !readRegister(REG_AUFLOESUNG, aufloesung, sizeof(aufloesung)))
    {
        Serial.printf("TOUCH Adresse=0x%02X antwortet=nein\n", m_address);
        return false;
    }
    char kennung[5] = {static_cast<char>(produkt[0]), static_cast<char>(produkt[1]), static_cast<char>(produkt[2]), static_cast<char>(produkt[3]), 0};
    const unsigned breite = aufloesung[0] | (aufloesung[1] << 8);
    const unsigned hoehe = aufloesung[2] | (aufloesung[3] << 8);
    m_ready = produkt[0] == '9' && produkt[1] == '1' && produkt[2] == '1' && version != 0;
    Serial.printf("TOUCH Adresse=0x%02X Produkt=%s Konfiguration=%u Aufloesung=%ux%u bereit=%s\n", m_address, kennung, version, breite, hoehe, m_ready ? "ja" : "nein");
    writeRegister(REG_STATUS, 0);
    return m_ready;
}

int CrowPanelTouch::read(Point *points, int maxPoints)
{
    if (!m_ready)
        return -1;
    uint8_t status = 0;
    if (!readRegister(REG_STATUS, &status, 1))
        return -1;
    if ((status & 0x80) == 0)
        return -2;
    int anzahl = status & 0x0F;
    if (anzahl > MaxPoints)
        anzahl = MaxPoints;
    if (anzahl > maxPoints)
        anzahl = maxPoints;
    uint8_t daten[MaxPoints * PUNKT_BYTES] = {};
    if (anzahl > 0 && !readRegister(REG_PUNKT1, daten, anzahl * PUNKT_BYTES))
        return -1;
    for (int i = 0; i < anzahl; ++i)
    {
        const uint8_t *p = daten + i * PUNKT_BYTES;
        points[i].x = static_cast<int16_t>(p[1] | (p[2] << 8));
        points[i].y = static_cast<int16_t>(p[3] | (p[4] << 8));
    }
    writeRegister(REG_STATUS, 0);
    return anzahl;
}

bool CrowPanelTouch::readRegister(uint16_t reg, uint8_t *data, size_t len)
{
    Wire.beginTransmission(m_address);
    Wire.write(static_cast<uint8_t>(reg >> 8));
    Wire.write(static_cast<uint8_t>(reg & 0xFF));
    if (Wire.endTransmission(false) != 0)
        return false;
    if (Wire.requestFrom(m_address, len) != len)
        return false;
    for (size_t i = 0; i < len; ++i)
        data[i] = Wire.read();
    return true;
}

bool CrowPanelTouch::writeRegister(uint16_t reg, uint8_t value)
{
    Wire.beginTransmission(m_address);
    Wire.write(static_cast<uint8_t>(reg >> 8));
    Wire.write(static_cast<uint8_t>(reg & 0xFF));
    Wire.write(value);
    return Wire.endTransmission() == 0;
}
