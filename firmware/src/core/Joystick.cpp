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
        const uint16_t deadZone,
        const float switchDebounceSec)
        : xInput_(xInput),
          yInput_(yInput),
          switchInput_(switchInput),
          xCenter_(xCenter),
          yCenter_(yCenter),
          deadZone_(deadZone),
          switchDebounceSec_(switchDebounceSec)
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
        return stablePressed_;
    }

    bool Joystick::clicked() const
    {
        return clicked_;
    }

    uint32_t Joystick::clickCount() const
    {
        return clickCount_;
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

    void Joystick::update(
        const float deltaTimeSec)
    {
        clicked_ = false;

        const bool currentRawPressed =
            !switchInput_.read();

        if (currentRawPressed != rawPressed_)
        {
            rawPressed_ =
                currentRawPressed;

            switchDebounceElapsedSec_ =
                0.0F;

            return;
        }

        if (rawPressed_ == stablePressed_)
        {
            return;
        }

        switchDebounceElapsedSec_ +=
            deltaTimeSec;

        if (
            switchDebounceElapsedSec_ <
            switchDebounceSec_)
        {
            return;
        }

        stablePressed_ =
            rawPressed_;

        switchDebounceElapsedSec_ =
            0.0F;

        if (stablePressed_)
        {
            clicked_ = true;
            ++clickCount_;
        }
    }

} // namespace asteria::core