#include <asteria/core/sources/JoystickMotionSource.h>

#include <asteria/core/Joystick.h>
#include <asteria/core/MotionCommand.h>

#include <asteria/config/JoystickMotionConfiguration.h>

#include <math.h>

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

        if (axisValue >= config::joystickMotion::FULL_SCALE_THRESHOLD)
            axisValue = 1.0F;
        else if (axisValue <= -config::joystickMotion::FULL_SCALE_THRESHOLD)
            axisValue = -1.0F;

        if (axisValue == 0.0F)
        {
            quantizedVelocityDegPerSec_ = 0.0F;
            return MotionProposal::none();
        }

        const float shapedAxisValue =
            copysignf(
                powf(
                    fabsf(axisValue),
                    config::joystickMotion::RESPONSE_EXPONENT),
                axisValue);

        const float rawVelocityDegPerSec =
            shapedAxisValue * maximumVelocityDegPerSec_;

        const float targetVelocityDegPerSec =
            roundf(
                rawVelocityDegPerSec /
                config::joystickMotion::VELOCITY_STEP_DEG_PER_SEC) *
            config::joystickMotion::VELOCITY_STEP_DEG_PER_SEC;

        if (targetVelocityDegPerSec >
            quantizedVelocityDegPerSec_)
        {
            const float upperThreshold =
                quantizedVelocityDegPerSec_ +
                (config::joystickMotion::VELOCITY_STEP_DEG_PER_SEC * 0.5F) +
                config::joystickMotion::VELOCITY_HYSTERESIS_DEG_PER_SEC;

            if (rawVelocityDegPerSec >= upperThreshold)
            {
                quantizedVelocityDegPerSec_ =
                    targetVelocityDegPerSec;
            }
        }
        else if (targetVelocityDegPerSec <
                 quantizedVelocityDegPerSec_)
        {
            const float lowerThreshold =
                quantizedVelocityDegPerSec_ -
                (config::joystickMotion::VELOCITY_STEP_DEG_PER_SEC * 0.5F) -
                config::joystickMotion::VELOCITY_HYSTERESIS_DEG_PER_SEC;

            if (rawVelocityDegPerSec <= lowerThreshold)
            {
                quantizedVelocityDegPerSec_ =
                    targetVelocityDegPerSec;
            }
        }

        if (quantizedVelocityDegPerSec_ == 0.0F)
            return MotionProposal::none();

        return MotionProposal::with(
            MotionCommand::overrideVelocity(
                quantizedVelocityDegPerSec_,
                MotionPriority::Takeover));
    }

} // namespace asteria::core