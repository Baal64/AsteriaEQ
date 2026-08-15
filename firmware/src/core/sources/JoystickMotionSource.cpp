#include <asteria/core/sources/JoystickMotionSource.h>

#include <asteria/core/Joystick.h>
#include <asteria/core/MotionCommand.h>

namespace asteria::core
{

    JoystickMotionSource::JoystickMotionSource(
        Joystick &joystick,
        const bool useXAxis,
        const float maximumVelocityDegPerSec,
        const bool invertAxis)
        : joystick_(joystick),
          useXAxis_(useXAxis),
          invertAxis_(invertAxis),
          maximumVelocityDegPerSec_(
              maximumVelocityDegPerSec)
    {
    }

    MotionProposal JoystickMotionSource::update(
        float deltaTimeSec)
    {
        (void)deltaTimeSec;

        float axisValue =
            useXAxis_
                ? joystick_.x()
                : joystick_.y();

        if (invertAxis_)
        {
            axisValue = -axisValue;
        }

        if (axisValue == 0.0F)
        {
            return MotionProposal::none();
        }

        const float velocityDegPerSec =
            axisValue *
            maximumVelocityDegPerSec_;

        return MotionProposal::with(
            MotionCommand::overrideVelocity(
                velocityDegPerSec,
                MotionPriority::Takeover));
    }

} // namespace asteria::core