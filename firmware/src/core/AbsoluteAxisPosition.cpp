#include <asteria/core/AbsoluteAxisPosition.h>

#include <asteria/platform/as5048a/As5048a.h>
#include <asteria/config/AxisPositionConfiguration.h>

namespace asteria::core
{

    AbsoluteAxisPosition::AbsoluteAxisPosition(
        platform::as5048a::As5048a &encoder,
        const float zeroOffsetDeg,
        const bool invert,
        const float maxPositionJumpDeg)
        : encoder_(encoder),
          zeroOffsetDeg_(zeroOffsetDeg),
          invert_(invert),
          maxPositionJumpDeg_(maxPositionJumpDeg),
          lastValidPositionDeg_(0.0F),
          hasLastValidPosition_(false),
          positionValid_(false),
          candidatePositionDeg_(0.0F),
          coherentSampleCount_(0U)
    {
    }

    float AbsoluteAxisPosition::positionDeg()
    {
        const float measuredPositionDeg =
            fromEncoderAngleDeg(
                encoder_.angleDeg());

        if (encoder_.hasError())
        {
            positionValid_ = false;

            if (!hasLastValidPosition_)
            {
                coherentSampleCount_ = 0U;
            }

            return hasLastValidPosition_
                       ? lastValidPositionDeg_
                       : measuredPositionDeg;
        }

        // -------------------------------------------------------------
        // Initial acquisition
        // -------------------------------------------------------------

        if (!hasLastValidPosition_)
        {
            if (coherentSampleCount_ == 0U)
            {
                candidatePositionDeg_ =
                    measuredPositionDeg;

                coherentSampleCount_ = 1U;
            }
            else
            {
                float deltaCandidateDeg =
                    measuredPositionDeg -
                    candidatePositionDeg_;

                if (deltaCandidateDeg > 180.0F)
                {
                    deltaCandidateDeg -= 360.0F;
                }
                else if (deltaCandidateDeg < -180.0F)
                {
                    deltaCandidateDeg += 360.0F;
                }

                if (
                    deltaCandidateDeg <= maxPositionJumpDeg_ &&
                    deltaCandidateDeg >= -maxPositionJumpDeg_)
                {
                    candidatePositionDeg_ =
                        measuredPositionDeg;

                    ++coherentSampleCount_;
                }
                else
                {
                    candidatePositionDeg_ =
                        measuredPositionDeg;

                    coherentSampleCount_ = 1U;
                }
            }

            if (
                coherentSampleCount_ >=
                config::axisPosition::
                    POSITION_VALIDATION_SAMPLE_COUNT)
            {
                lastValidPositionDeg_ =
                    candidatePositionDeg_;

                hasLastValidPosition_ = true;
                positionValid_ = true;
                coherentSampleCount_ = 0U;

                return lastValidPositionDeg_;
            }

            positionValid_ = false;

            return measuredPositionDeg;
        }

        // -------------------------------------------------------------
        // Normal operation / recovery
        // -------------------------------------------------------------

        float deltaFromLastValidDeg =
            measuredPositionDeg -
            lastValidPositionDeg_;

        if (deltaFromLastValidDeg > 180.0F)
        {
            deltaFromLastValidDeg -= 360.0F;
        }
        else if (deltaFromLastValidDeg < -180.0F)
        {
            deltaFromLastValidDeg += 360.0F;
        }

        if (
            deltaFromLastValidDeg > maxPositionJumpDeg_ ||
            deltaFromLastValidDeg < -maxPositionJumpDeg_)
        {
            positionValid_ = false;

            return lastValidPositionDeg_;
        }

        lastValidPositionDeg_ =
            measuredPositionDeg;

        positionValid_ = true;

        return lastValidPositionDeg_;
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
        return positionValid_;
    }

    void AbsoluteAxisPosition::requestReacquisition()
    {
        hasLastValidPosition_ = false;
        positionValid_ = false;
        coherentSampleCount_ = 0U;
    }

} // namespace asteria::core