#include <asteria/core/sources/TestPositionMotionSource.h>

#include <asteria/core/MotionCommand.h>

namespace asteria::core
{

    TestPositionMotionSource::TestPositionMotionSource(
        const float targetPositionDeg,
        const float maximumVelocityDegPerSec)
        : targetPositionDeg_(targetPositionDeg),
          maximumVelocityDegPerSec_(
              maximumVelocityDegPerSec)
    {
    }

    MotionProposal TestPositionMotionSource::update(
        float deltaTimeSec)
    {
        (void)deltaTimeSec;

        return MotionProposal::with(
            MotionCommand::overridePosition(
                targetPositionDeg_,
                maximumVelocityDegPerSec_,
                false));
    }

} // namespace asteria::core