// Herkunft: abgeleitet aus Arduino-ESP32 3.3.7, variants/esp32p4/pins_arduino.h (Espressif Systems, LGPL-2.1).
// Werte für das Elecrow CrowPanel Advanced 7", 9" und 10.1" V1.2 nach den Schaltplänen des Herstellers.

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>
#include "soc/soc_caps.h"

// UART0 am CH340K (Programmieren und Log)
static const uint8_t TX = 37;
static const uint8_t RX = 38;

// I2C an IO45/IO46 mit Touch, Codec ES8311, ADC ES7210, STC8 und den Steckern J11/J13. Die IO-Domäne versorgt LDO4.
static const uint8_t SDA = 45;
static const uint8_t SCL = 46;

// SPI zum Funkmodulsockel J9, IO9 liegt an J11
static const uint8_t SS = 9;
static const uint8_t MOSI = 6;
static const uint8_t MISO = 7;
static const uint8_t SCK = 8;

// ADC-fähige Pins des P4 wie in der Ausgangsvariante, auf dem CrowPanel großteils anders belegt
static const uint8_t A0 = 16;
static const uint8_t A1 = 17;
static const uint8_t A2 = 18;
static const uint8_t A3 = 19;
static const uint8_t A4 = 20;
static const uint8_t A5 = 21;
static const uint8_t A6 = 22;
static const uint8_t A7 = 23;
static const uint8_t A8 = 49;
static const uint8_t A9 = 50;
static const uint8_t A10 = 51;
static const uint8_t A11 = 52;
static const uint8_t A12 = 53;
static const uint8_t A13 = 54;

// SD-Karte an Slot 0 (IOMUX: CLK IO43, CMD IO44, D0 IO39), nur 1 Bit. Ohne Versorgungspin und ohne LDO-Kanal, weil LDO4 auch I2C und Touch versorgt und deshalb der Firmware gehört, nicht SD_MMC.
#define BOARD_HAS_SDMMC
#define BOARD_SDMMC_SLOT 0

// WLAN über den ESP32-C6 an SDIO, Datenleitungen absteigend, EN an IO32
#define BOARD_HAS_SDIO_ESP_HOSTED
#define BOARD_SDIO_ESP_HOSTED_CLK   18
#define BOARD_SDIO_ESP_HOSTED_CMD   19
#define BOARD_SDIO_ESP_HOSTED_D0    17
#define BOARD_SDIO_ESP_HOSTED_D1    16
#define BOARD_SDIO_ESP_HOSTED_D2    15
#define BOARD_SDIO_ESP_HOSTED_D3    14
#define BOARD_SDIO_ESP_HOSTED_RESET 32

#endif /* Pins_Arduino_h */
