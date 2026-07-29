#pragma once

#include <asteria/hardware/IStepPulseGenerator.h>

namespace asteria::simulation
{

    class SimulatedStepPulseGenerator final
        : public hardware::IStepPulseGenerator
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

} // namespace asteria::simulation