#include <asteria/core/Joystick.h>

#include <asteria/platform/avr/Atmega32u4AnalogInput.h>
#include <asteria/platform/mcp23017/Mcp23017DigitalInput.h>

namespace asteria::core
{

    Joystick::Joystick(
        platform::avr::Atmega32u4AnalogInput &xInput,
        platform::avr::Atmega32u4AnalogInput &yInput,
        platform::mcp23017::Mcp23017DigitalInput &switchInput,
        const uint16_t xCenter,
        const uint16_t yCenter,
        const uint16_t deadZone)
        : xInput_(xInput),
          yInput_(yInput),
          switchInput_(switchInput),
          xCenter_(xCenter),
          yCenter_(yCenter),
          deadZone_(deadZone)
    {
    }

    float Joystick::x() const
    {
        return normalize(
            xInput_.read(),
            xCenter_);
    }

    float Joystick::y() const
    {
        return normalize(
            yInput_.read(),
            yCenter_);
    }

    bool Joystick::pressed() const
    {
        // Pull-up actif :
        // HIGH = relâché
        // LOW  = appuyé
        return !switchInput_.read();
    }

    float Joystick::normalize(
        const uint16_t rawValue,
        const uint16_t center) const
    {
        const int32_t delta =
            static_cast<int32_t>(rawValue) -
            static_cast<int32_t>(center);

        if (delta >=
                -static_cast<int32_t>(deadZone_) &&
            delta <=
                static_cast<int32_t>(deadZone_))
        {
            return 0.0F;
        }

        if (delta < 0)
        {
            const float range =
                static_cast<float>(
                    center - deadZone_);

            const float value =
                static_cast<float>(
                    delta +
                    static_cast<int32_t>(deadZone_)) /
                range;

            return value < -1.0F
                       ? -1.0F
                       : value;
        }

        const float range =
            static_cast<float>(
                1023U -
                center -
                deadZone_);

        const float value =
            static_cast<float>(
                delta -
                static_cast<int32_t>(deadZone_)) /
            range;

        return value > 1.0F
                   ? 1.0F
                   : value;
    }

} // namespace asteria::core