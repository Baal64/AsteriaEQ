#pragma once

#include <asteria/core/IMotionSource.h>

namespace asteria::core
{

    class NullMotionSource final : public IMotionSource
    {
    public:
        MotionProposal update(float deltaTimeSec) override;
    };

} // namespace asteria::core