#pragma once

#include <stdint.h>

namespace asteria::hardware
{

    struct StepperDriverConfiguration
    {
        float motorStepAngleDeg = 1.8F;
        uint16_t microsteps = 1;
        float gearRatio = 1.0F;

        bool enableActiveLow = true;
        bool invertDirection = false;
    };

} // namespace asteria::hardware