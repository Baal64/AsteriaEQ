#include <asteria/core/AbsoluteAxisPosition.h>

#include <asteria/platform/as5048a/As5048a.h>

namespace asteria::core
{

    AbsoluteAxisPosition::AbsoluteAxisPosition(
        platform::as5048a::As5048a &encoder,
        const float zeroOffsetDeg,
        const bool invert)
        : encoder_(encoder),
          zeroOffsetDeg_(zeroOffsetDeg),
          invert_(invert)
    {
    }

    float AbsoluteAxisPosition::positionDeg()
    {
        return fromEncoderAngleDeg(
            encoder_.angleDeg());
    }

    float AbsoluteAxisPosition::normalizeSignedDeg(
        float angleDeg)
    {
        while (angleDeg >= 180.0F)
        {
            angleDeg -= 360.0F;
        }

        while (angleDeg < -180.0F)
        {
            angleDeg += 360.0F;
        }

        return angleDeg;
    }

    float AbsoluteAxisPosition::fromEncoderAngleDeg(
        const float encoderAngleDeg) const
    {
        float position =
            encoderAngleDeg -
            zeroOffsetDeg_;

        if (invert_)
        {
            position = -position;
        }

        return normalizeSignedDeg(position);
    }

    bool AbsoluteAxisPosition::isValid() const
    {
        return !encoder_.hasError();
    }

} // namespace asteria::core