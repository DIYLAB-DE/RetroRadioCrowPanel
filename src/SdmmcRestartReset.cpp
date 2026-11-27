#include <esp_attr.h>
#include <esp_cpu.h>
#include <riscv/rv_utils.h>
#include <soc/lp_clkrst_reg.h>
#include <soc/soc.h>
#include <soc/soc_caps.h>

extern "C"
{
    /** @brief esp_restart_noos() der Kernbibliotheken, der letzte Schritt jedes Neustarts über esp_restart() und nach einem Absturz. Die Linker-Option --wrap=esp_restart_noos (platformio.ini) macht ihn unter diesem Namen erreichbar. */
    [[noreturn]] void __real_esp_restart_noos(void);

    /** @brief Setzt den SDMMC-Host zurück, bevor esp_restart_noos() die übrige Peripherie zurücksetzt. Die Linker-Option --wrap=esp_restart_noos leitet jeden Aufruf von esp_restart_noos() hierher, also ESP.restart(), den Neustart von ESP-Hosted ohne Antwort des C6 und den Neustart nach einem Absturz.
     *
     * Die Kernbibliotheken (ESP-IDF v5.5.2) setzen in esp_restart_noos() erst MSPI-AXI und weitere Peripherie zurück und den SDMMC-Host zuletzt. Überträgt dessen DMA in diesem Moment Daten für die SD-Karte (Slot 0) oder den C6 (Slot 1), bleibt er nach dem CPU-Reset beim Lesen des Deskriptors stehen: Kommandos ohne Daten gehen weiter durch, jeder Datentransfer endet mit Zeitüberschreitung (0x107), in jedem folgenden Start, bis zu einem Reset über CHIP_PU oder Aus- und Einschalten. Der Reset des SDMMC-Hosts vor den anderen behebt das (ESP-IDF, Commit dd47ea3696 „fix(esp_system): reset SDMMC before other peripherals on ESP32-P4 restart“). Diese Datei und die Linker-Option entfallen, sobald die Kernbibliotheken diesen Commit enthalten.
     *
     * Vor dem Reset hält die Funktion Unterbrechungen und den anderen Kern an, damit kein Task danach einen neuen Transfer beginnt. Sie nimmt keine Sperre, gibt nichts aus und ruft nur Code im RAM auf, weil nach einem Absturz der Flash-Cache aus sein kann und die Ausgabe des Arduino-Kerns im Flash liegt. */
    [[noreturn]] void IRAM_ATTR __wrap_esp_restart_noos(void)
    {
        rv_utils_intr_global_disable();
#if SOC_CPU_CORES_NUM > 1
        esp_cpu_stall(esp_cpu_get_core_id() == 0 ? 1 : 0);
#endif
        SET_PERI_REG_MASK(LP_CLKRST_HP_SDMMC_EMAC_RST_CTRL_REG, LP_CLKRST_RST_EN_SDMMC);
        CLEAR_PERI_REG_MASK(LP_CLKRST_HP_SDMMC_EMAC_RST_CTRL_REG, LP_CLKRST_RST_EN_SDMMC);
        __real_esp_restart_noos();
    }
}
