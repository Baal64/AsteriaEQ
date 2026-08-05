#include <Arduino.h>

#include <asteria/platform/avr/Atmega32u4DigitalOutput.h>

namespace asteria::platform::avr
{

    Atmega32u4DigitalOutput::Atmega32u4DigitalOutput(
        const uint8_t pin)
        : pin_(pin)
    {
    }

    void Atmega32u4DigitalOutput::begin(
        const bool initialState)
    {
        state_ = initialState;

        // Appliquer la valeur avant de passer en sortie limite
        // les transitions parasites lors de l'initialisation.
        digitalWrite(pin_, state_ ? HIGH : LOW);
        pinMode(pin_, OUTPUT);

        initialized_ = true;
    }

    void Atmega32u4DigitalOutput::write(
        const bool state)
    {
        state_ = state;

        if (!initialized_)
        {
            return;
        }

        digitalWrite(pin_, state_ ? HIGH : LOW);
    }

    bool Atmega32u4DigitalOutput::state() const
    {
        return state_;
    }

} // namespace asteria::platform::avr