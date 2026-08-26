#pragma once

#include <stdint.h>

namespace asteria::config::statusLed
{

    // -----------------------------------------------------------------------------
    // Error indication
    // -----------------------------------------------------------------------------

    constexpr uint16_t LOST_ON_MS = 150U;
    constexpr uint16_t LOST_OFF_MS = 150U;

    constexpr uint16_t TEMP_INVALID_ON_MS = 100U;
    constexpr uint16_t TEMP_INVALID_OFF_MS = 100U;
    constexpr uint16_t TEMP_INVALID_PAUSE_MS = 1200U;

    // -----------------------------------------------------------------------------
    // Tracking indication
    // -----------------------------------------------------------------------------

    constexpr uint16_t SIDEREAL_ON_MS = 900U;
    constexpr uint16_t SIDEREAL_OFF_MS = 100U;

    constexpr uint16_t LUNAR_ON_MS = 500U;
    constexpr uint16_t LUNAR_OFF_MS = 500U;

    constexpr uint16_t SOLAR_ON_MS = 100U;
    constexpr uint16_t SOLAR_OFF_MS = 900U;

} // namespace asteria::config::statusLed