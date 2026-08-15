#pragma once

#include <stdint.h>

namespace asteria::platform::avr
{
    class Atmega32u4AnalogInput;
}

namespace asteria::platform::mcp23017
{
    class Mcp23017DigitalInput;
}

namespace asteria::core
{

    class Joystick
    {
    public:
        Joystick(
            platform::avr::Atmega32u4AnalogInput &xInput,
            platform::avr::Atmega32u4AnalogInput &yInput,
            platform::mcp23017::Mcp23017DigitalInput &switchInput,
            uint16_t xCenter,
            uint16_t yCenter,
            uint16_t deadZone);

        float x() const;
        float y() const;

        bool pressed() const;

    private:
        float normalize(
            uint16_t rawValue,
            uint16_t center) const;

        platform::avr::Atmega32u4AnalogInput &xInput_;
        platform::avr::Atmega32u4AnalogInput &yInput_;

        platform::mcp23017::Mcp23017DigitalInput &switchInput_;

        uint16_t xCenter_;
        uint16_t yCenter_;
        uint16_t deadZone_;
    };

} // namespace asteria::core