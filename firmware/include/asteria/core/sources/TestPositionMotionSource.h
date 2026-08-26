#pragma once

#include <asteria/core/IMotionSource.h>

namespace asteria::core
{

    class TestPositionMotionSource final
        : public IMotionSource
    {
    public:
        TestPositionMotionSource(
            float targetPositionDeg,
            float maximumVelocityDegPerSec);

        MotionProposal update(
            float deltaTimeSec) override;

    private:
        float targetPositionDeg_;
        float maximumVelocityDegPerSec_;
    };

} // namespace asteria::core