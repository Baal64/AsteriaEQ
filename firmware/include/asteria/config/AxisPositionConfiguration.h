#pragma once
#include <stdint.h>

namespace asteria::config::axisPosition
{

    /**
     * Absolute encoder calibration for the mount axes.
     *
     * The zero offset corresponds to the AS5048A angle measured
     * when the mechanical axis is in its reference position.
     *
     * Declination reference:
     *     DEC = 0 deg when the optical axis is parallel
     *     to the right ascension axis.
     *
     * The actual offsets will be determined during
     * mechanical calibration.
     */
    constexpr float RIGHT_ASCENSION_ZERO_OFFSET_DEG = 0.0F;
    constexpr float DECLINATION_ZERO_OFFSET_DEG = 56.84F;

    /**
     * Reverse the encoder direction when the positive mechanical
     * direction is opposite to the AS5048A angle direction.
     */
    /**
     * Declination sign convention:
     *
     * View from above the RA axis, looking along the axis,
     * with the DEC axis represented upward on the reference dial.
     *
     * Clockwise rotation        = positive DEC
     * Counter-clockwise rotation = negative DEC
     */
    constexpr bool RIGHT_ASCENSION_INVERT = true;
    /**
     * Declination sign convention:
     *
     * View from above the DEC axis, looking along the axis,
     * with the RA axis represented downward on the reference dial.
     *
     * Clockwise rotation        = positive DEC
     * Counter-clockwise rotation = negative DEC
     */
    constexpr bool DECLINATION_INVERT = true;

    constexpr float RIGHT_ASCENSION_MAX_POSITION_JUMP_DEG = 1.0F;
    constexpr float DECLINATION_MAX_POSITION_JUMP_DEG = 1.0F;
    constexpr uint8_t POSITION_VALIDATION_SAMPLE_COUNT = 3U;

    constexpr float RIGHT_ASCENSION_POSITION_ERROR_MARGIN_DEG = 1.0F;
    constexpr float DECLINATION_POSITION_ERROR_MARGIN_DEG = 1.0F;

    constexpr unsigned long RIGHT_ASCENSION_MAX_POSITION_INVALID_MS = 5000UL;
    constexpr unsigned long DECLINATION_MAX_POSITION_INVALID_MS = 2000UL;

    constexpr float RIGHT_ASCENSION_MAX_POSITION_UNCERTAINTY_DEG = 1.0F;
    constexpr float DECLINATION_MAX_POSITION_UNCERTAINTY_DEG = 1.0F;

    constexpr float RIGHT_ASCENSION_MAX_POSITION_INVALID_SEC = 30.0F;
    constexpr float DECLINATION_MAX_POSITION_INVALID_SEC = 30.0F;

} // namespace asteria::config::axisPosition