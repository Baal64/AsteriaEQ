#include <asteria/hardware/StepperKinematics.h>

namespace asteria::hardware
{

    StepperKinematics::StepperKinematics(
        const StepperDriverConfiguration &configuration)
        : configuration_(configuration)
    {
    }

    float StepperKinematics::stepFrequencyFromAxisVelocity(
        const float axisVelocityDegPerSec) const
    {
        return (axisVelocityDegPerSec /
                configuration_.motorStepAngleDeg) *
               configuration_.gearRatio *
               configuration_.microsteps;
    }

}