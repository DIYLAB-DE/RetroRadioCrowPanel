#ifndef CROWPANEL_USB_H
#define CROWPANEL_USB_H

#include <Arduino.h>

/** @brief Diagnosekanal an der USB-2.0-Buchse J16 im Entwicklungsbuild: CDC über TinyUSB am High-Speed-PHY des P4, neben UART0 am CH340K. Trägt Log, Befehle und Bildschirmaufnahmen. Flashen, ROM- und Bootlog bleiben an UART0 (J1), J16 gibt es nur, solange die Anwendung läuft. Nur mit CROWPANEL_USB_FERNSTEUERUNG übersetzt, der Standardbuild nutzt J16 nicht. */
class CrowPanelUsb
{
public:
    /** @brief Meldet das Gerät als „RetroRadioCrowPanel10“ (USB-Kennung des Arduino-Kerns 303a:0002) mit der P4-MAC als Seriennummer an. Neustart in den Bootloader über DTR/RTS oder 1200 Baud bleibt aus. Einmal aus setup() aufrufen. @return USB-Stack gestartet. */
    static bool begin();

    /** @brief Der CDC-Kanal, auch ohne Host. Schreiben ohne verbundenen Host kehrt sofort mit 0 zurück, mit Host wartet ein Schreibaufruf höchstens TxTimeoutMs. Erst nach begin() verwenden. */
    static Stream &stream();

    /** @brief Meldet einen verbundenen Host (DTR und RTS gesetzt, so öffnen die Skripte). Aus jedem Task aufrufbar. */
    static bool connected();

    static constexpr uint32_t TxTimeoutMs = 20; ///< Längste Wartezeit eines Schreibaufrufs, wenn der Host nicht abholt
};

#endif
