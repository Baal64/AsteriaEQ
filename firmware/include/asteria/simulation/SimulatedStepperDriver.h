#pragma once

#include <asteria/hardware/IStepperDriver.h>

namespace asteria::simulation
{

    class SimulatedStepperDriver final
        : public hardware::IStepperDriver
    {
    public:
        SimulatedStepperDriver();

        void enable() override;

        void disable() override;

        bool isEnabled() const override;

        void setVelocityDegPerSec(
            float velocityDegPerSec) override;

        void update(float deltaTimeSec) override;

        float velocityDegPerSec() const;

    private:
        bool enabled_;
        float velocityDegPerSec_;
    };

} // namespace asteria::simulation