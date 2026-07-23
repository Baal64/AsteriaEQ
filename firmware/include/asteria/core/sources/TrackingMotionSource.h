#pragma once

#include <asteria/core/IMotionSource.h>

namespace asteria::core
{

    class TrackingMotionSource final : public IMotionSource
    {
    public:
        explicit TrackingMotionSource(float velocityDegPerSec);

        void setVelocityDegPerSec(float velocityDegPerSec);

        float velocityDegPerSec() const;

        MotionProposal update(float deltaTimeSec) override;

    private:
        float velocityDegPerSec_;
    };

} // namespace asteria::core