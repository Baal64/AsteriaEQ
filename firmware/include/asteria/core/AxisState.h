#pragma once

namespace asteria::core
{

    struct AxisState
    {
        float positionDeg{0.0F};
        float velocityDegPerSec{0.0F};

        bool positionValid{false};
        bool withinLimits{true};
    };

} // namespace asteria::core