#pragma once

#include <asteria/core/PositionHealth.h>

namespace asteria::core
{

    struct AxisState
    {
        float positionDeg{0.0F};
        float velocityDegPerSec{0.0F};

        PositionHealth positionHealth{
            PositionHealth::TemporarilyInvalid};

        bool withinLimits{true};
    };

} // namespace asteria::core