#ifndef CROWPANEL_BOARD_H
#define CROWPANEL_BOARD_H

#include <cstddef>
#include <cstdint>

/** @brief Platinennahe Pins und Startfolge des CrowPanel Advanced 7", 9" und 10.1" V1.2, laut Schaltplänen und am Gerät gleich. Ton über zwei I2S-Verstärker NS4168 ohne Codec, Freigabe IO30. */
namespace CrowPanelBoard
{
    constexpr uint8_t I2cSda = 45;              ///< I2C-Bus mit Touch, STC8, optionaler DS1307 und den Steckern J11/J13 (IO-Domäne aus LDO4)
    constexpr uint8_t I2cScl = 46;
    constexpr uint32_t I2cFrequency = 100000;   ///< wie im Original-RetroRadio, eine DS1307 verträgt nicht mehr
    constexpr int8_t I2sMclk = -1;              ///< kein MCLK, die NS4168 brauchen keinen
    constexpr uint8_t I2sBclk = 22;             ///< I2S-Bittakt (GPIO)
    constexpr uint8_t I2sLrck = 21;             ///< I2S-Wortauswahl (GPIO)
    constexpr uint8_t I2sData = 23;             ///< I2S-Daten zu den NS4168 (GPIO)
    constexpr uint8_t AmplifierPin = 30;        ///< Freigabe der NS4168 über Q10, Pull-up 10 kOhm, High = aus, Low = an
    constexpr bool StereoSpeakers = true;       ///< Zwei Lautsprecher mit je einem NS4168, die CTRL-Spannung des Verstärkers wählt seinen Kanal
    constexpr bool SwapChannels = true;         ///< Ohne Tausch kommt der linke Kanal an der Lautsprecherbuchse mit der Aufschrift für rechts an (am Gerät gehört), deshalb tauscht die Ausgabe die Kanäle
    constexpr uint8_t UnusedGatePin = 29;       ///< Gate des nicht bestückten Q11, über 10 kOhm an 5 V, wird Low gehalten
    constexpr uint8_t BacklightPin = 31;        ///< EN/PWM des MT9201
    constexpr int LdoIoChannel = 4;             ///< versorgt IO39 bis IO48 (VDDPST_5)
    constexpr int LdoIoMillivolt = 3300;
    constexpr uint8_t HostedClk = 18;           ///< C6-SDIO, Slot 1 über die GPIO-Matrix, 4 Bit (ab Platinenstand V1.1)
    constexpr uint8_t HostedCmd = 19;
    constexpr uint8_t HostedD0 = 17;
    constexpr uint8_t HostedD1 = 16;
    constexpr uint8_t HostedD2 = 15;
    constexpr uint8_t HostedD3 = 14;
    constexpr uint8_t HostedReset = 32;         ///< C6-EN, Low hält den C6 im Reset
    constexpr uint8_t SdClk = 43;               ///< SD-Karte, Slot 0, nur 1 Bit (DAT1 und DAT2 nicht am P4, DAT3 am Spannungsteiler)
    constexpr uint8_t SdCmd = 44;
    constexpr uint8_t SdD0 = 39;
    // Vorläufige Pins für den Bluetooth-Sender, der Steckplan am CrowPanel ist noch offen. BtSender prüft nur die Ruhepegel und bleibt ohne Pico untätig.
    constexpr uint8_t BtUartTx = 47;            ///< J2 TXD1, vorläufig
    constexpr uint8_t BtUartRx = 48;            ///< J2 RXD1, vorläufig
    constexpr uint8_t BtBclk = 49;              ///< J7, vorläufig
    constexpr uint8_t BtWs = 50;                ///< J7, vorläufig
    constexpr uint8_t BtData = 51;              ///< J7, vorläufig

    /** @brief Erster Schritt nach dem Reset: Verstärker aus, IO29 Low, Hintergrundlicht aus, LDO4 auf 3,3 V für I2C, Touch, SD und LCD-Reset. @return true, wenn LDO4 bereitsteht. */
    bool silenceBeforeDisplay();
    /** @brief Prüft einen eigenen PSRAM-Puffer mit zwei Mustern und gibt ihn wieder frei. @param bytes Größe des Prüfpuffers in Bytes, durch vier teilbar. @return true bei vollständig erfolgreicher Prüfung. */
    bool testPsram(size_t bytes);
    /** @brief Ohne Codec nur: Verstärker aus. @return true. */
    bool prepareRadioCodec();
    /** @brief Verstärker aus, bevor die Quelle ihre Takte ändert oder stoppt. @return true. */
    bool powerDownRadioCodec();
    /** @brief Verstärker aus, I2S läuft weiter. @return true. */
    bool muteRadio();
    /** @brief Gibt den Verstärker frei. Der Aufrufer muss frisches, leises PCM sicherstellen. @param speaker false lässt ihn aus. @return true. */
    bool unmuteRadio(bool speaker);
    /** @brief Schaltet den Verstärker über IO30. @return true. */
    bool setSpeaker(bool on);
    /** @brief Liest den gesetzten Pegel von IO30 zurück. @param on true bei freigegebenem Verstärker. @return true. */
    bool readSpeaker(bool &on);
    /** @brief Das CrowPanel hat keine Kopfhörerbuchse. @param inserted immer false. @return true. */
    bool readHeadphone(bool &inserted);

    constexpr uint32_t HeadphonePollMs = 50;       ///< Abstand der Abfragen im UI-Task
    constexpr uint8_t HeadphoneStableReads = 3;    ///< So viele gleiche Abfragen in Folge übernehmen einen neuen Steckerzustand

    /** @brief Entprellung der Kopfhörererkennung. Ohne Buchse bleibt der Zustand „kein Stecker“, der Ablauf in main.cpp bleibt dadurch gleich. */
    class HeadphoneDebounce
    {
    public:
        /** @brief Prüft, ob die nächste Abfrage fällig ist. Überlaufsicher. @param now millis(). */
        bool due(uint32_t now) const
        {
            return static_cast<int32_t>(now - m_nextPoll) >= 0;
        }

        /** @brief Übernimmt eine Abfrage und plant die nächste. Ein abweichender Zustand gilt erst nach HeadphoneStableReads gleichen Abfragen in Folge. @param now millis(). @param read Lesen bestätigt. @param inserted Gelesener Steckerzustand. @return true, wenn sich der entprellte Zustand geändert hat. */
        bool update(uint32_t now, bool read, bool inserted)
        {
            m_nextPoll = now + HeadphonePollMs;
            if (!read || inserted == m_inserted)
            {
                m_count = 0;
                return false;
            }
            if (++m_count < HeadphoneStableReads)
                return false;
            m_count = 0;
            m_inserted = inserted;
            return true;
        }

        /** @brief Entprellter Steckerzustand. */
        bool inserted() const
        {
            return m_inserted;
        }

    private:
        uint32_t m_nextPoll = 0; ///< millis() der nächsten fälligen Abfrage
        uint8_t m_count = 0;     ///< Gleiche abweichende Abfragen in Folge
        bool m_inserted = false; ///< Entprellter Zustand, true bei gestecktem Stecker
    };
}

#endif
