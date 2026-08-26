#pragma once

#include <asteria/core/IMotionSource.h>

namespace asteria::core
{

    class PositionMotionSource final
        : public IMotionSource
    {
    public:
        PositionMotionSource(
            float targetPositionDeg,
            float maximumVelocityDegPerSec);

        void setTargetPositionDeg(
            float targetPositionDeg);

        void setMaximumVelocityDegPerSec(
            float maximumVelocityDegPerSec);

        MotionProposal update(
            float deltaTimeSec) override;

        void setEnabled(bool enabled);

        bool isEnabled() const;

    private:
        float targetPositionDeg_;
        float maximumVelocityDegPerSec_;
        bool enabled_{false};
    };

} // namespace asteria::core