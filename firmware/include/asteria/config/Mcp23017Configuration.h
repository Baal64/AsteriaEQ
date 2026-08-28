#pragma once

#include <stdint.h>

namespace asteria::config::mcp23017
{

    constexpr uint8_t I2C_ADDRESS = 0x27U;

    constexpr uint8_t RIGHT_ASCENSION_ENABLE_PIN = 0U; // GPA0
    constexpr uint8_t DECLINATION_ENABLE_PIN = 1U;     // GPA1
    constexpr uint8_t STATUS_LED_PIN = 2U;             // GPA2
    constexpr uint8_t JOYSTICK_SWITCH_PIN = 3U;        // GPA3

    constexpr uint8_t ST4_RIGHT_ASCENSION_PLUS_PIN = 4U;  // GPA4
    constexpr uint8_t ST4_RIGHT_ASCENSION_MINUS_PIN = 5U; // GPA5
    constexpr uint8_t ST4_DECLINATION_PLUS_PIN = 6U;      // GPA6
    constexpr uint8_t ST4_DECLINATION_MINUS_PIN = 7U;     // GPA7

} // namespace asteria::config::mcp23017