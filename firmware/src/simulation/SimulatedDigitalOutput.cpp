#include <asteria/simulation/SimulatedDigitalOutput.h>

namespace asteria::simulation
{

    void SimulatedDigitalOutput::write(bool state)
    {
        state_ = state;
    }

    bool SimulatedDigitalOutput::state() const
    {
        return state_;
    }

} // namespace asteria::simulation