#pragma once

#include <stdint.h>

namespace asteria::config::joystick
{

    constexpr uint16_t X_CENTER = 496U;
    constexpr uint16_t Y_CENTER = 541U;

    constexpr uint16_t DEAD_ZONE = 40U;

    constexpr float SWITCH_DEBOUNCE_SEC = 0.030F;

    constexpr float LONG_PRESS_THRESHOLD_SEC = 1.0F;

} // namespace asteria::config::joystick