#include <asteria/core/sources/PositionMotionSource.h>

#include <asteria/core/MotionCommand.h>

namespace asteria::core
{

    PositionMotionSource::PositionMotionSource(
        const float targetPositionDeg,
        const float maximumVelocityDegPerSec)
        : targetPositionDeg_(targetPositionDeg),
          maximumVelocityDegPerSec_(
              maximumVelocityDegPerSec)
    {
    }

    void PositionMotionSource::setTargetPositionDeg(
        const float targetPositionDeg)
    {
        targetPositionDeg_ =
            targetPositionDeg;
    }

    void PositionMotionSource::setMaximumVelocityDegPerSec(
        const float maximumVelocityDegPerSec)
    {
        maximumVelocityDegPerSec_ =
            maximumVelocityDegPerSec;
    }

    MotionProposal PositionMotionSource::update(
        float deltaTimeSec)
    {
        (void)deltaTimeSec;

        if (!enabled_)
        {
            return MotionProposal::none();
        }

        return MotionProposal::with(
            MotionCommand::overridePosition(
                targetPositionDeg_,
                maximumVelocityDegPerSec_,
                false));
    }

    void PositionMotionSource::setEnabled(
        const bool enabled)
    {
        enabled_ = enabled;
    }

    bool PositionMotionSource::isEnabled() const
    {
        return enabled_;
    }

} // namespace asteria::core