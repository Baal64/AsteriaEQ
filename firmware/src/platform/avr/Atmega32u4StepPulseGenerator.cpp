#include <Arduino.h>
#include <util/atomic.h>

#include <asteria/config/PinConfiguration.h>
#include <asteria/platform/avr/Atmega32u4StepPulseGenerator.h>

namespace asteria::platform::avr
{

    Atmega32u4StepPulseGenerator::
        Atmega32u4StepPulseGenerator(
            const StepTimer timer)
        : timer_(timer)
    {
    }

    void Atmega32u4StepPulseGenerator::begin()
    {
        configureOutputPin();
        resetTimer();

        frequencyHz_ = 0.0F;
        isRunning_ = false;
        initialized_ = true;
    }

    void Atmega32u4StepPulseGenerator::start(
        const float frequencyHz)
    {
        if (!initialized_)
        {
            return;
        }

        if (frequencyHz <= 0.0F)
        {
            stop();
            return;
        }

        StepTimerSettings settings;

        const bool settingsAvailable =
            StepTimerCalculator::calculate(
                F_CPU,
                frequencyHz,
                settings);

        if (!settingsAvailable)
        {
            stop();
            return;
        }

        applyTimerSettings(settings);

        frequencyHz_ = settings.actualFrequencyHz;
        isRunning_ = true;
    }

    void Atmega32u4StepPulseGenerator::stop()
    {
        if (initialized_)
        {
            disableTimer();
            forceOutputLow();
        }

        frequencyHz_ = 0.0F;
        isRunning_ = false;
    }

    bool Atmega32u4StepPulseGenerator::isRunning() const
    {
        return isRunning_;
    }

    float Atmega32u4StepPulseGenerator::frequencyHz() const
    {
        return frequencyHz_;
    }

    void Atmega32u4StepPulseGenerator::
        configureOutputPin()
    {
        const uint8_t pin =
            timer_ == StepTimer::Timer1
                ? config::pins::RIGHT_ASCENSION_STEP
                : config::pins::DECLINATION_STEP;

        // Fixer le niveau avant de configurer la broche
        // en sortie limite les transitions parasites.
        digitalWrite(pin, LOW);
        pinMode(pin, OUTPUT);
    }

    void Atmega32u4StepPulseGenerator::resetTimer()
    {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            switch (timer_)
            {
            case StepTimer::Timer1:
                TCCR1A = 0U;
                TCCR1B = 0U;
                TCNT1 = 0U;
                OCR1A = 0U;

                // Les indicateurs AVR sont effacés
                // en écrivant un bit à 1.
                TIFR1 = _BV(OCF1A);
                break;

            case StepTimer::Timer3:
                TCCR3A = 0U;
                TCCR3B = 0U;
                TCNT3 = 0U;
                OCR3A = 0U;

                TIFR3 = _BV(OCF3A);
                break;
            }
        }

        forceOutputLow();
    }

    void Atmega32u4StepPulseGenerator::
        applyTimerSettings(
            const StepTimerSettings &settings)
    {
        switch (timer_)
        {
        case StepTimer::Timer1:
            applyTimer1Settings(settings);
            break;

        case StepTimer::Timer3:
            applyTimer3Settings(settings);
            break;
        }
    }

    void Atmega32u4StepPulseGenerator::
        applyTimer1Settings(
            const StepTimerSettings &settings)
    {
        const uint8_t clockSelectBits =
            clockSelectBitsFromPrescaler(
                settings.prescaler);

        if (clockSelectBits == 0U)
        {
            return;
        }

        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            // Arrêter et déconnecter la sortie avant
            // de remplacer la configuration.
            TCCR1A = 0U;
            TCCR1B = 0U;

            TCNT1 = 0U;
            OCR1A = settings.compareValue;

            TIFR1 = _BV(OCF1A);

            // COM1A0 :
            // bascule automatique de OC1A lors d'une comparaison.
            TCCR1A = _BV(COM1A0);

            // WGM12 :
            // mode CTC avec OCR1A comme valeur maximale.
            //
            // Les bits CS12..CS10 démarrent ensuite le timer
            // avec le prescaler sélectionné.
            TCCR1B =
                _BV(WGM12) |
                clockSelectBits;
        }
    }

    void Atmega32u4StepPulseGenerator::
        applyTimer3Settings(
            const StepTimerSettings &settings)
    {
        const uint8_t clockSelectBits =
            clockSelectBitsFromPrescaler(
                settings.prescaler);

        if (clockSelectBits == 0U)
        {
            return;
        }

        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            TCCR3A = 0U;
            TCCR3B = 0U;

            TCNT3 = 0U;
            OCR3A = settings.compareValue;

            TIFR3 = _BV(OCF3A);

            // COM3A0 :
            // bascule automatique de OC3A.
            TCCR3A = _BV(COM3A0);

            // WGM32 :
            // mode CTC avec OCR3A comme valeur maximale.
            TCCR3B =
                _BV(WGM32) |
                clockSelectBits;
        }
    }

    void Atmega32u4StepPulseGenerator::disableTimer()
    {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            switch (timer_)
            {
            case StepTimer::Timer1:
                // Retirer les bits de sélection d'horloge :
                // Timer1 cesse de compter.
                TCCR1B &=
                    static_cast<uint8_t>(
                        ~(_BV(CS12) |
                          _BV(CS11) |
                          _BV(CS10)));

                // Déconnecter OC1A du timer.
                TCCR1A &=
                    static_cast<uint8_t>(
                        ~(_BV(COM1A1) |
                          _BV(COM1A0)));
                break;

            case StepTimer::Timer3:
                TCCR3B &=
                    static_cast<uint8_t>(
                        ~(_BV(CS32) |
                          _BV(CS31) |
                          _BV(CS30)));

                TCCR3A &=
                    static_cast<uint8_t>(
                        ~(_BV(COM3A1) |
                          _BV(COM3A0)));
                break;
            }
        }
    }

    void Atmega32u4StepPulseGenerator::forceOutputLow()
    {
        const uint8_t pin =
            timer_ == StepTimer::Timer1
                ? config::pins::RIGHT_ASCENSION_STEP
                : config::pins::DECLINATION_STEP;

        digitalWrite(pin, LOW);
    }

    uint8_t Atmega32u4StepPulseGenerator::
        clockSelectBitsFromPrescaler(
            const uint16_t prescaler) const
    {
        switch (prescaler)
        {
        case 1U:
            return 0x01U;

        case 8U:
            return 0x02U;

        case 64U:
            return 0x03U;

        case 256U:
            return 0x04U;

        case 1024U:
            return 0x05U;

        default:
            return 0U;
        }
    }

} // namespace asteria::platform::avr