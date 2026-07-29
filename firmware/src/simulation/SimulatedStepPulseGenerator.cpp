#include <asteria/simulation/SimulatedStepPulseGenerator.h>

namespace asteria::simulation
{

    void SimulatedStepPulseGenerator::start(
        const float frequencyHz)
    {
        if (frequencyHz <= 0.0F)
        {
            stop();
            return;
        }

        frequencyHz_ = frequencyHz;
        isRunning_ = true;
    }

    void SimulatedStepPulseGenerator::stop()
    {
        frequencyHz_ = 0.0F;
        isRunning_ = false;
    }

    bool SimulatedStepPulseGenerator::isRunning() const
    {
        return isRunning_;
    }

    float SimulatedStepPulseGenerator::frequencyHz() const
    {
        return frequencyHz_;
    }

} // namespace asteria::simulation