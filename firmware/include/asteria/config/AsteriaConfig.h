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

        constexpr float ST4_GUIDING_RATE_FACTOR =
            0.5F;

        constexpr float ST4_GUIDING_RATE_DEG_PER_SEC =
            SIDEREAL_RATE_DEG_PER_SEC * ST4_GUIDING_RATE_FACTOR;

        constexpr float TRACKING_MODE_SELECTION_TIMEOUT_SEC =
            10.0F;

    } // namespace motion

    namespace homing
    {
        constexpr float RIGHT_ASCENSION_POSITION_DEG =
            0.0F;

        constexpr float DECLINATION_POSITION_DEG =
            0.0F;

        constexpr float RIGHT_ASCENSION_VELOCITY_DEG_PER_SEC =
            0.5F;
        constexpr float DECLINATION_VELOCITY_DEG_PER_SEC =
            0.5F;

        constexpr float POSITION_TOLERANCE_DEG =
            0.1F;

    } // namespace homing
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