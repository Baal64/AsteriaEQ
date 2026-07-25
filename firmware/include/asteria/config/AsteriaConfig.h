#pragma once

#include <stdint.h>

#include <asteria/hardware/StepperDriverConfiguration.h>

namespace asteria::config
{

    namespace system
    {

        constexpr uint32_t SERIAL_BAUD_RATE = 115200UL;

    }

    namespace motion
    {

        constexpr float SIDEREAL_RATE_DEG_PER_SEC =
            360.0F / 86164.0905F;

    }

    namespace mechanics
    {

        constexpr hardware::StepperDriverConfiguration
            RIGHT_ASCENSION_STEPPER{
                400U,
                16U,
                188.0F,
                false};

        constexpr hardware::StepperDriverConfiguration
            DECLINATION_STEPPER{
                400U,
                16U,
                2.0F,
                false};

    }

}