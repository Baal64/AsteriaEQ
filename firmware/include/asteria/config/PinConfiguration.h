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

    /**
     * AS5048A chip-select lines.
     *
     * The two encoders share the hardware SPI bus.
     */
    constexpr uint8_t RIGHT_ASCENSION_ENCODER_CS = 7U;
    constexpr uint8_t DECLINATION_ENCODER_CS = 8U;

    /**
     * Hardware SPI bus.
     *
     * MISO : D14 / PB3
     * SCK  : D15 / PB1
     * MOSI : D16 / PB2
     *
     * These pins are controlled by the SPI peripheral
     * and are therefore not manually driven by Asteria.
     */
    constexpr uint8_t SPI_MISO = 14U;
    constexpr uint8_t SPI_SCK = 15U;
    constexpr uint8_t SPI_MOSI = 16U;

    constexpr uint8_t JOYSTICK_X = A1;
    constexpr uint8_t JOYSTICK_Y = A2;

} // namespace asteria::config::pins