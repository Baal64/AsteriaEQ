#pragma once

#include <stdint.h>

namespace asteria::config::pins
{

    /**
     * Sorties STEP pilotées directement par les sorties
     * de comparaison matérielles de l'ATmega32U4.
     *
     * RA  : D9 / PB5 / OC1A / Timer1
     * DEC : D5 / PC6 / OC3A / Timer3
     */
    constexpr uint8_t RIGHT_ASCENSION_STEP = 9U;
    constexpr uint8_t DECLINATION_STEP = 5U;
    constexpr uint8_t RIGHT_ASCENSION_DIR = 4U;
    constexpr uint8_t DECLINATION_DIR = 6U;

    constexpr uint8_t JOYSTICK_X = A1;
    constexpr uint8_t JOYSTICK_Y = A2;

} // namespace asteria::config::pins