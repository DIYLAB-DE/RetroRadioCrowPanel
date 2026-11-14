#include "CrowPanelUsb.h"

#if CROWPANEL_USB_FERNSTEUERUNG
#include <USB.h>
#include <esp_mac.h>

namespace
{
    constexpr size_t RxBytes = 1024;                     ///< Empfangspuffer, fasst mehrere Befehlszeilen
    constexpr const char *Product = "RetroRadioCrowPanel10"; ///< Produktname, an dem die Skripte J16 erkennen
    USBCDC s_cdc(0);                                     ///< Erste CDC-Schnittstelle, der Konstruktor meldet sie bei TinyUSB an
    bool s_started = false;                              ///< USB.begin() bestätigt
}

bool CrowPanelUsb::begin()
{
    if (s_started)
        return true;
    uint8_t mac[6] = {};
    char serial[13] = "000000000000";
    if (esp_efuse_mac_get_default(mac) == ESP_OK)
        snprintf(serial, sizeof(serial), "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    USB.productName(Product);
    USB.serialNumber(serial);
    // Die Skripte öffnen mit DTR und RTS. Ohne diese Sperre könnte eine Leitungsfolge den P4 in den Bootloader schicken.
    s_cdc.enableReboot(false);
    s_cdc.setRxBufferSize(RxBytes);
    s_cdc.setTxTimeoutMs(TxTimeoutMs);
    s_cdc.begin();
    s_started = USB.begin();
    return s_started;
}

Stream &CrowPanelUsb::stream()
{
    return s_cdc;
}

bool CrowPanelUsb::connected()
{
    return s_started && static_cast<bool>(s_cdc);
}

#endif
