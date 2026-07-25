#pragma once

#include <stdint.h>

namespace asteria::hardware
{

    struct StepperDriverConfiguration
    {
        uint16_t motorStepsPerRevolution;
        uint16_t microsteps;
        float gearRatio;
        bool reverseDirection;
    };

}