#pragma once

#include <asteria/hardware/IDigitalOutput.h>

namespace asteria::simulation
{

    class SimulatedDigitalOutput final
        : public hardware::IDigitalOutput
    {
    public:
        void write(bool state) override;

        bool state() const override;

    private:
        bool state_ = false;
    };

} // namespace asteria::simulation