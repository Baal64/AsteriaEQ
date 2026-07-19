#pragma once

#include <asteria/core/MotionProposal.h>

namespace asteria::core
{

    class IMotionSource
    {
    public:
        virtual ~IMotionSource() = default;

        virtual MotionProposal update(float deltaTimeSec) = 0;
    };

} // namespace asteria::core