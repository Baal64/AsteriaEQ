#pragma once

#include <stdint.h>

namespace asteria::platform::avr
{

    /**
     * Paramètres calculés pour produire une fréquence
     * à l'aide d'un timer fonctionnant en mode CTC avec
     * bascule automatique de sa sortie de comparaison.
     */
    struct StepTimerSettings
    {
        uint16_t compareValue{0U};
        uint16_t prescaler{0U};
        float actualFrequencyHz{0.0F};
    };

    /**
     * Calcule les paramètres nécessaires à la génération
     * matérielle d'un signal STEP.
     *
     * Cette classe ne dépend ni d'Arduino ni des registres AVR.
     */
    class StepTimerCalculator
    {
    public:
        /**
         * Calcule le prescaler et la valeur de comparaison.
         *
         * @param timerClockHz Fréquence d'horloge du timer.
         * @param requestedFrequencyHz Fréquence STEP demandée.
         * @param settings Paramètres calculés en sortie.
         *
         * @return true si la fréquence peut être produite
         *         par un timer 16 bits ; false sinon.
         */
        static bool calculate(
            uint32_t timerClockHz,
            float requestedFrequencyHz,
            StepTimerSettings &settings);
    };

} // namespace asteria::platform::avr