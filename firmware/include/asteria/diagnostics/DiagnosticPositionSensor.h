#pragma once

#include <asteria/core/IPositionSensor.h>

namespace asteria::diagnostics
{

    class DiagnosticPositionSensor final
        : public core::IPositionSensor
    {
    public:
        explicit DiagnosticPositionSensor(
            core::IPositionSensor &sensor);

        float positionDeg() override;
        bool isValid() const override;

        void setForcedInvalid(bool forcedInvalid);

        bool isForcedInvalid() const;

        void requestReacquisition() override;

    private:
        core::IPositionSensor &sensor_;

        bool forcedInvalid_{false};
    };

} // namespace asteria::diagnostics