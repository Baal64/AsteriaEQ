#pragma once

#include <asteria/core/IMotionSource.h>

namespace asteria::core
{

    class Joystick;

    class JoystickMotionSource final
        : public IMotionSource
    {
    public:
        JoystickMotionSource(
            Joystick &joystick,
            bool useXAxis,
            float maximumVelocityDegPerSec,
            bool invertAxis = false);

        MotionProposal update(float deltaTimeSec) override;

    private:
        Joystick &joystick_;

        bool useXAxis_;
        bool invertAxis_;

        float maximumVelocityDegPerSec_;
    };

} // namespace asteria::core