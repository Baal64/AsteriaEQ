#include <asteria/core/sources/TrackingMotionSource.h>

#include <asteria/config/AsteriaConfig.h>
#include <asteria/core/MotionCommand.h>

namespace asteria::core
{

    TrackingMotionSource::TrackingMotionSource(
        const TrackingMode mode)
        : mode_(mode)
    {
    }

    void TrackingMotionSource::setMode(
        const TrackingMode mode)
    {
        mode_ = mode;
    }

    TrackingMode TrackingMotionSource::mode() const
    {
        return mode_;
    }

    float TrackingMotionSource::velocityDegPerSec() const
    {
        return velocityForMode(mode_);
    }

    MotionProposal TrackingMotionSource::update(
        float deltaTimeSec)
    {
        (void)deltaTimeSec;

        return MotionProposal::with(
            MotionCommand::baseVelocity(
                velocityDegPerSec()));
    }

    float TrackingMotionSource::velocityForMode(
        const TrackingMode mode)
    {
        switch (mode)
        {
        case TrackingMode::Sidereal:
            return config::motion::
                SIDEREAL_RATE_DEG_PER_SEC;

        case TrackingMode::Lunar:
            return config::motion::
                LUNAR_RATE_DEG_PER_SEC;

        case TrackingMode::Solar:
            return config::motion::
                SOLAR_RATE_DEG_PER_SEC;
        }

        return config::motion::
            SIDEREAL_RATE_DEG_PER_SEC;
    }

} // namespace asteria::core