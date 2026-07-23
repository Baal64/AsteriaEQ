#include <asteria/core/sources/NullMotionSource.h>

namespace asteria::core
{

    MotionProposal NullMotionSource::update(float deltaTimeSec)
    {
        (void)deltaTimeSec;

        return MotionProposal::none();
    }

} // namespace asteria::core