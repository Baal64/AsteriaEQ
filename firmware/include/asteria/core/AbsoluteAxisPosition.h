#pragma once

#include <asteria/core/IPositionSensor.h>
#include <stdint.h>

namespace asteria::platform::as5048a
{
    class As5048a;
}

namespace asteria::core
{

    class AbsoluteAxisPosition final
        : public IPositionSensor
    {
    public:
        AbsoluteAxisPosition(
            platform::as5048a::As5048a &encoder,
            float zeroOffsetDeg,
            bool invert,
            float maxPositionJumpDeg);

        float positionDeg() override;

        bool isValid() const override;

        float fromEncoderAngleDeg(float encoderAngleDeg) const;

        void requestReacquisition() override;

    private:
        static float normalizeSignedDeg(float angleDeg);

        platform::as5048a::As5048a &encoder_;

        float zeroOffsetDeg_;
        bool invert_;
        float maxPositionJumpDeg_;

        float lastValidPositionDeg_;
        bool hasLastValidPosition_;
        bool positionValid_;

        float candidatePositionDeg_;
        uint8_t coherentSampleCount_;
    };

} // namespace asteria::core