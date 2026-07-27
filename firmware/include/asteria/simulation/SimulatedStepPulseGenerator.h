#pragma once

#include <asteria/hardware/IStepPulseGenerator.h>

namespace asteria::hardware
{

    class SimulatedStepPulseGenerator final
        : public IStepPulseGenerator
    {
    public:
        void start(float frequencyHz) override;
        void stop() override;

        bool isRunning() const override;
        float frequencyHz() const override;

    private:
        float frequencyHz_ = 0.0F;
        bool isRunning_ = false;
    };

} // namespace asteria::hardware