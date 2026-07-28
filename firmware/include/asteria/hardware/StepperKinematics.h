#pragma once

#include <asteria/config/StepperDriverConfiguration.h>

namespace asteria::hardware
{

    class StepperKinematics
    {
    public:
        explicit StepperKinematics(
            const StepperDriverConfiguration &configuration);

        float stepFrequencyFromAxisVelocity(
            float axisVelocityDegPerSec) const;

    private:
        StepperDriverConfiguration configuration_;
    };

}