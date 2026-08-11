#pragma once

#include <stdint.h>
#include <asteria/platform/mcp23017/Mcp23017Types.h>

namespace asteria::platform::mcp23017
{

    enum class Mcp23017Port : uint8_t
    {
        PortA,
        PortB
    };

} // namespace asteria::platform::mcp23017