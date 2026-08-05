#pragma once

#include <stdint.h>

#include <asteria/hardware/IStepPulseGenerator.h>
#include <asteria/platform/avr/StepTimerCalculator.h>

namespace asteria::platform::avr
{

    /**
     * Timer matériel utilisé pour générer un signal STEP.
     *
     * Timer1 pilote OC1A, affecté à l'axe RA.
     * Timer3 pilote OC3A, affecté à l'axe DEC.
     */
    enum class StepTimer : uint8_t
    {
        Timer1,
        Timer3
    };

    /**
     * Génère un signal STEP avec une sortie de comparaison
     * matérielle de l'ATmega32U4.
     *
     * Le timer fonctionne en mode CTC et bascule automatiquement
     * la sortie OCnA à chaque comparaison.
     */
    class Atmega32u4StepPulseGenerator final
        : public hardware::IStepPulseGenerator
    {
    public:
        explicit Atmega32u4StepPulseGenerator(
            StepTimer timer);

        /**
         * Prépare la broche STEP et remet le timer
         * dans un état connu, sans le démarrer.
         */
        void begin();

        /**
         * Démarre le générateur ou remplace sa fréquence.
         *
         * Une fréquence inférieure ou égale à zéro
         * provoque l'arrêt du générateur.
         */
        void start(float frequencyHz) override;

        /**
         * Arrête le timer et force STEP à LOW.
         */
        void stop() override;

        bool isRunning() const override;

        /**
         * Retourne la fréquence réellement produite,
         * après arrondi de la valeur de comparaison.
         */
        float frequencyHz() const override;

    private:
        void configureOutputPin();
        void resetTimer();

        void applyTimerSettings(
            const StepTimerSettings &settings);

        void applyTimer1Settings(
            const StepTimerSettings &settings);

        void applyTimer3Settings(
            const StepTimerSettings &settings);

        void disableTimer();
        void forceOutputLow();

        uint8_t clockSelectBitsFromPrescaler(
            uint16_t prescaler) const;

        StepTimer timer_;

        float frequencyHz_ = 0.0F;

        bool initialized_ = false;
        bool isRunning_ = false;
    };

} // namespace asteria::platform::avr