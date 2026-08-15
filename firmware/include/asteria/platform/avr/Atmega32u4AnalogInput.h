#pragma once

#include <stdint.h>

namespace asteria::platform::avr
{

    class Atmega32u4AnalogInput
    {
    public:
        explicit Atmega32u4AnalogInput(uint8_t pin);

        void begin();

        uint16_t read() const;

    private:
        uint8_t pin_;
    };

} // namespace asteria::platform::avr