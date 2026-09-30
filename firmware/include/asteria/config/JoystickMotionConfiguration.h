#pragma once

namespace asteria::config::joystickMotion
{

    constexpr float MAX_RA_VELOCITY_DEG_PER_SEC = 3.0F;
    constexpr float MAX_DEC_VELOCITY_DEG_PER_SEC = 2.0F;

    constexpr float VELOCITY_STEP_DEG_PER_SEC = 0.01F;
    constexpr float VELOCITY_HYSTERESIS_DEG_PER_SEC = 0.01F;
    constexpr float FULL_SCALE_THRESHOLD = 0.97F;

    constexpr float RESPONSE_EXPONENT = 2.0F;

    constexpr bool INVERT_RA = false;
    constexpr bool INVERT_DEC = false;

} // namespace asteria::config::joystickMotion