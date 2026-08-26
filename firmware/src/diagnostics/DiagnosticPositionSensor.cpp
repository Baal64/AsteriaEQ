#include <asteria/diagnostics/DiagnosticPositionSensor.h>

namespace asteria::diagnostics
{

    DiagnosticPositionSensor::DiagnosticPositionSensor(
        core::IPositionSensor &sensor)
        : sensor_(sensor)
    {
    }

    float DiagnosticPositionSensor::positionDeg()
    {
        return sensor_.positionDeg();
    }

    bool DiagnosticPositionSensor::isValid() const
    {
        return !forcedInvalid_ &&
               sensor_.isValid();
    }

    void DiagnosticPositionSensor::setForcedInvalid(
        const bool forcedInvalid)
    {
        forcedInvalid_ = forcedInvalid;
    }

    bool DiagnosticPositionSensor::isForcedInvalid() const
    {
        return forcedInvalid_;
    }

    void DiagnosticPositionSensor::requestReacquisition()
    {
        sensor_.requestReacquisition();
    }

} // namespace asteria::diagnostics