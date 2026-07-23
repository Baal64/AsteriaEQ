#include <asteria/core/Mount.h>

namespace asteria::core
{

    Mount::Mount(
        AxisController &rightAscension,
        AxisController &declination)
        : rightAscension_(rightAscension),
          declination_(declination),
          enabled_(false)
    {
    }

    void Mount::enable()
    {
        enabled_ = true;
    }

    void Mount::disable()
    {
        enabled_ = false;
    }

    void Mount::update(float deltaTimeSec)
    {
        if (!enabled_)
        {
            return;
        }

        rightAscension_.update(deltaTimeSec);
        declination_.update(deltaTimeSec);
    }

} // namespace asteria::core