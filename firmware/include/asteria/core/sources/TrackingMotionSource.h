#pragma once

#include <asteria/core/IMotionSource.h>
#include <asteria/core/TrackingMode.h>

namespace asteria::core
{

    class TrackingMotionSource final
        : public IMotionSource
    {
    public:
        explicit TrackingMotionSource(
            TrackingMode mode);

        void setMode(TrackingMode mode);

        TrackingMode mode() const;

        float velocityDegPerSec() const;

        MotionProposal update(
            float deltaTimeSec) override;

        void setEnabled(bool enabled);

        bool isEnabled() const;

    private:
        static float velocityForMode(
            TrackingMode mode);

        TrackingMode mode_;

        bool enabled_{false};
    };

} // namespace asteria::core