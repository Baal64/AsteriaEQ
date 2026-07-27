#include <asteria/core/AxisController.h>

namespace asteria::core
{

    void AxisController::update(float deltaTimeSec)
    {
        const AxisTarget target = composeTarget(deltaTimeSec);

        axis_.setTarget(target);
        axis_.update(deltaTimeSec);
    }

    AxisTarget AxisController::composeTarget(float deltaTimeSec)
    {
        MotionProposal bestOverride = MotionProposal::none();
        MotionProposal bestBase = MotionProposal::none();

        float correctionVelocityDegPerSec = 0.0F;
        bool hasCorrection = false;

        if (sources_ == nullptr)
        {
            return AxisTarget{};
        }

        for (uint8_t index = 0; index < sourceCount_; ++index)
        {
            IMotionSource *const source = sources_[index];

            if (source == nullptr)
            {
                // TODO: signaler une source nulle dans le système de diagnostic.
                continue;
            }

            const MotionProposal proposal = source->update(deltaTimeSec);

            if (!proposal.available())
            {
                continue;
            }

            const MotionCommand &command = proposal.command();

            switch (command.mode())
            {
            case MotionMode::Base:
                if (!bestBase.available() ||
                    command.priority() > bestBase.command().priority())
                {
                    bestBase = proposal;
                }
                else if (
                    command.priority() == bestBase.command().priority())
                {
                    /*
                     * La première commande rencontrée est conservée.
                     *
                     * TODO: signaler plusieurs commandes Base de même
                     * priorité dans le système de diagnostic.
                     */
                }
                break;

            case MotionMode::Correction:
                correctionVelocityDegPerSec +=
                    command.velocityDegPerSec();

                hasCorrection = true;
                break;

            case MotionMode::Override:
                if (!bestOverride.available() ||
                    command.priority() > bestOverride.command().priority())
                {
                    bestOverride = proposal;
                }
                else if (
                    command.priority() == bestOverride.command().priority())
                {
                    /*
                     * La première commande rencontrée est conservée.
                     *
                     * TODO: signaler plusieurs commandes Override de même
                     * priorité dans le système de diagnostic.
                     */
                }
                break;
            }
        }

        if (bestOverride.available())
        {
            const MotionCommand &command = bestOverride.command();

            AxisTarget target{};

            switch (command.type())
            {
            case MotionType::Velocity:
                target.type = AxisTargetType::Velocity;
                target.velocityDegPerSec =
                    command.velocityDegPerSec();
                break;

            case MotionType::Position:
                target.type = AxisTargetType::Position;
                target.positionDeg = command.positionDeg();
                target.velocityDegPerSec =
                    command.velocityDegPerSec();
                target.relative = command.isRelative();
                break;
            }

            return target;
        }

        if (bestBase.available() || hasCorrection)
        {
            float velocityDegPerSec =
                correctionVelocityDegPerSec;

            if (bestBase.available())
            {
                velocityDegPerSec +=
                    bestBase.command().velocityDegPerSec();
            }

            AxisTarget target{};
            target.type = AxisTargetType::Velocity;
            target.velocityDegPerSec = velocityDegPerSec;

            return target;
        }

        return AxisTarget{};
    }

} // namespace asteria::core