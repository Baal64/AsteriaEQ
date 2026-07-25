#include <asteria/hardware/StepperKinematics.h>

namespace asteria::hardware
{

    StepperKinematics::StepperKinematics(
        const StepperDriverConfiguration &configuration)
        : configuration_(configuration)
    {
    }

    float StepperKinematics::stepFrequencyFromAxisVelocity(
        float axisVelocityDegPerSec) const
    {
        const float stepsPerAxisRevolution =
            static_cast<float>(
                configuration_.motorStepsPerRevolution) *
            static_cast<float>(
                configuration_.microsteps) *
            configuration_.gearRatio;

        return axisVelocityDegPerSec * stepsPerAxisRevolution / 360.0F;
    }

}