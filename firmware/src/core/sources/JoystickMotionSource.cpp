#include <asteria/core/sources/JoystickMotionSource.h>

#include <asteria/core/Joystick.h>
#include <asteria/core/MotionCommand.h>

#include <math.h>

namespace asteria::core
{

    namespace
    {
        constexpr float VELOCITY_STEP_DEG_PER_SEC = 0.01F;
        constexpr float VELOCITY_HYSTERESIS_DEG_PER_SEC = 0.0025F;
    }

    JoystickMotionSource::JoystickMotionSource(
        Joystick &joystick,
        const bool useXAxis,
        const float maximumVelocityDegPerSec,
        const bool invertAxis)
        : joystick_(joystick),
          useXAxis_(useXAxis),
          invertAxis_(invertAxis),
          maximumVelocityDegPerSec_(maximumVelocityDegPerSec)
    {
    }

    MotionProposal JoystickMotionSource::update(
        const float deltaTimeSec)
    {
        (void)deltaTimeSec;

        if (joystick_.pressed())
            return MotionProposal::none();

        float axisValue =
            useXAxis_
                ? joystick_.x()
                : joystick_.y();

        if (invertAxis_)
            axisValue = -axisValue;

        if (axisValue == 0.0F)
        {
            quantizedVelocityDegPerSec_ = 0.0F;
            return MotionProposal::none();
        }

        const float rawVelocityDegPerSec =
            axisValue * maximumVelocityDegPerSec_;

        const float difference =
            rawVelocityDegPerSec -
            quantizedVelocityDegPerSec_;

        const float threshold =
            (VELOCITY_STEP_DEG_PER_SEC * 0.5F) +
            VELOCITY_HYSTERESIS_DEG_PER_SEC;

        if (fabsf(difference) >= threshold)
        {
            quantizedVelocityDegPerSec_ =
                roundf(
                    rawVelocityDegPerSec /
                    VELOCITY_STEP_DEG_PER_SEC) *
                VELOCITY_STEP_DEG_PER_SEC;
        }

        if (quantizedVelocityDegPerSec_ == 0.0F)
            return MotionProposal::none();

        return MotionProposal::with(
            MotionCommand::overrideVelocity(
                quantizedVelocityDegPerSec_,
                MotionPriority::Takeover));
    }

} // namespace asteria::core