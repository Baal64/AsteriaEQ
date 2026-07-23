#pragma once

#include <asteria/hardware/IStepperDriver.h>

namespace asteria::hardware
{

    class FakeStepperDriver final : public IStepperDriver
    {
    public:
        FakeStepperDriver();

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

} // namespace asteria::hardware