#pragma once

#include <asteria/core/MotionCommand.h>

namespace asteria::core
{

    /**
     * Proposition produite par une source de mouvement.
     *
     * Une source peut :
     * - ne proposer aucune commande ;
     * - proposer exactement une MotionCommand.
     *
     * L'AxisController reste libre d'accepter, de composer
     * ou d'ignorer cette proposition.
     */
    class MotionProposal
    {
    public:
        static MotionProposal none()
        {
            return MotionProposal(
                false,
                MotionCommand::baseVelocity(0.0F));
        }

        static MotionProposal with(const MotionCommand &command)
        {
            return MotionProposal(true, command);
        }

        bool available() const
        {
            return available_;
        }

        const MotionCommand &command() const
        {
            return command_;
        }

    private:
        MotionProposal(
            bool available,
            const MotionCommand &command)
            : available_(available),
              command_(command)
        {
        }

        bool available_;
        MotionCommand command_;
    };

} // namespace asteria::core