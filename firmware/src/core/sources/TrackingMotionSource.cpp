#include <asteria/core/sources/TrackingMotionSource.h>

#include <asteria/core/MotionCommand.h>

namespace asteria::core
{

    TrackingMotionSource::TrackingMotionSource(
        float velocityDegPerSec)
        : velocityDegPerSec_(velocityDegPerSec)
    {
    }

    void TrackingMotionSource::setVelocityDegPerSec(
        float velocityDegPerSec)
    {
        velocityDegPerSec_ = velocityDegPerSec;
    }

    float TrackingMotionSource::velocityDegPerSec() const
    {
        return velocityDegPerSec_;
    }

    MotionProposal TrackingMotionSource::update(
        float deltaTimeSec)
    {
        (void)deltaTimeSec;

        return MotionProposal::with(
            MotionCommand::baseVelocity(
                velocityDegPerSec_));
    }

} // namespace asteria::core