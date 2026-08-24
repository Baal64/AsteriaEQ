#pragma once

namespace asteria::platform::as5048a
{
    class As5048a;
}

namespace asteria::core
{

    class AbsoluteAxisPosition
    {
    public:
        AbsoluteAxisPosition(
            platform::as5048a::As5048a &encoder,
            float zeroOffsetDeg,
            bool invert);

        float positionDeg();

    private:
        static float normalizeSignedDeg(float angleDeg);

        platform::as5048a::As5048a &encoder_;

        float zeroOffsetDeg_;
        bool invert_;
    };

} // namespace asteria::core