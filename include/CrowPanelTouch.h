#ifndef CROWPANEL_TOUCH_H
#define CROWPANEL_TOUCH_H

#include <stddef.h>
#include <stdint.h>

/** @brief Touchcontroller GT911 der CrowPanel Advanced 7", 9" und 10.1" an I2C IO45/IO46 (Wire, 100 kHz), Reset IO40, INT IO42. Abfrage ohne Interrupt. Nur aus einem Task verwenden, LDO4 muss laufen. */
class CrowPanelTouch
{
public:
    static constexpr int MaxPoints = 5; ///< Höchstzahl gleichzeitiger Punkte des GT911

    /** @brief Ein Berührungspunkt in Panelkoordinaten. */
    struct Point
    {
        int16_t x; ///< 0 bis 1023, links nach rechts
        int16_t y; ///< 0 bis 599, oben nach unten
    };

    /** @brief Setzt den GT911 zurück, wählt dabei Adresse 0x5D (INT Low) und liest Kennung, Konfigurationsversion und Auflösung ins Log. @return true, wenn die Kennung „911“ lautet und die Konfigurationsversion nicht 0 ist. */
    bool begin();

    /** @brief Fragt neue Punkte ab und quittiert sie. @return Anzahl der Punkte (0 = losgelassen), -2 ohne neue Daten, -1 bei I2C-Fehler. */
    int read(Point *points, int maxPoints);

private:
    /** @brief Liest len Byte ab dem 16-Bit-Register reg. */
    bool readRegister(uint16_t reg, uint8_t *data, size_t len);

    /** @brief Schreibt ein Byte in das 16-Bit-Register reg. */
    bool writeRegister(uint16_t reg, uint8_t value);

    uint8_t m_address = 0x5D; ///< 7-Bit-I2C-Adresse nach dem Reset
    bool m_ready = false;     ///< begin() erfolgreich
};

#endif
