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
        const float switchDebounceSec,
        const float longPressThresholdSec)
        : xInput_(xInput),
          yInput_(yInput),
          switchInput_(switchInput),
          xCenter_(xCenter),
          yCenter_(yCenter),
          deadZone_(deadZone),
          switchDebounceSec_(switchDebounceSec),
          longPressThresholdSec_(longPressThresholdSec)
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
        longPressed_ = false;

        const bool currentRawPressed =
            !switchInput_.read();

        // -------------------------------------------------------------------------
        // Raw state changed: restart debounce
        // -------------------------------------------------------------------------

        if (currentRawPressed != rawPressed_)
        {
            rawPressed_ =
                currentRawPressed;

            switchDebounceElapsedSec_ =
                0.0F;

            return;
        }

        // -------------------------------------------------------------------------
        // Raw state already matches stable state
        // -------------------------------------------------------------------------

        if (rawPressed_ == stablePressed_)
        {
            if (stablePressed_)
            {
                pressDurationSec_ +=
                    deltaTimeSec;

                if (
                    !longPressTriggered_ &&
                    pressDurationSec_ >=
                        longPressThresholdSec_)
                {
                    longPressed_ = true;
                    longPressTriggered_ = true;

                    ++longPressCount_;
                }
            }

            return;
        }

        // -------------------------------------------------------------------------
        // Debounce candidate state
        // -------------------------------------------------------------------------

        switchDebounceElapsedSec_ +=
            deltaTimeSec;

        if (
            switchDebounceElapsedSec_ <
            switchDebounceSec_)
        {
            return;
        }

        // -------------------------------------------------------------------------
        // New stable state accepted
        // -------------------------------------------------------------------------

        stablePressed_ =
            rawPressed_;

        switchDebounceElapsedSec_ =
            0.0F;

        if (stablePressed_)
        {
            // Button has just been pressed.
            // Do NOT generate a click yet: we do not know
            // whether this will become a long press.
            pressDurationSec_ = 0.0F;
            longPressTriggered_ = false;
        }
        else
        {
            // Button has just been released.
            // Generate a short click only if no long press
            // was triggered during this press.
            if (!longPressTriggered_)
            {
                clicked_ = true;
                ++clickCount_;
            }

            pressDurationSec_ = 0.0F;
            longPressTriggered_ = false;
        }
    }

    bool Joystick::longPressed() const
    {
        return longPressed_;
    }

    uint32_t Joystick::longPressCount() const
    {
        return longPressCount_;
    }

} // namespace asteria::core