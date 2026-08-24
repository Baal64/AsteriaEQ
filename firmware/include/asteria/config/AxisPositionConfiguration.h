#pragma once

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
    constexpr float DECLINATION_ZERO_OFFSET_DEG = 0.0F;

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

} // namespace asteria::config::axisPosition