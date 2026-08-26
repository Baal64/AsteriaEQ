#pragma once

#include <stdint.h>

#include <asteria/config/StepperDriverConfiguration.h>

namespace asteria::config
{

    namespace system
    {

        constexpr uint32_t SERIAL_BAUD_RATE = 115200UL;

    } // namespace system

    namespace motion
    {

        constexpr float SIDEREAL_RATE_DEG_PER_SEC =
            360.0F / 86164.0905F;

        constexpr float LUNAR_RATE_DEG_PER_SEC =
            360.0F / 89428.0F;

        constexpr float SOLAR_RATE_DEG_PER_SEC =
            360.0F / 86400.0F;

    } // namespace motion

    namespace mechanics
    {

        constexpr hardware::StepperDriverConfiguration
            RIGHT_ASCENSION_STEPPER{
                0.9F,   // Motor step angle in degrees
                16U,    // Microsteps
                188.0F, // Gear ratio
                true,   // Enable signal is active-low
                false   // Do not invert direction
            };

        constexpr hardware::StepperDriverConfiguration
            DECLINATION_STEPPER{
                0.9F, // Motor step angle in degrees
                16U,  // Microsteps
                2.0F, // Gear ratio
                true, // Enable signal is active-low
                false // Do not invert direction
            };

    } // namespace mechanics

} // namespace asteria::config