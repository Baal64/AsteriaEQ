#include <Arduino.h>

#include <asteria/platform/avr/Atmega32u4AnalogInput.h>

namespace asteria::platform::avr
{

    Atmega32u4AnalogInput::Atmega32u4AnalogInput(
        const uint8_t pin)
        : pin_(pin)
    {
    }

    void Atmega32u4AnalogInput::begin()
    {
        pinMode(pin_, INPUT);
    }

    uint16_t Atmega32u4AnalogInput::read() const
    {
        return static_cast<uint16_t>(
            analogRead(pin_));
    }

} // namespace asteria::platform::avr