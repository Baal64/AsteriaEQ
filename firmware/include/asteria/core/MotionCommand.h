#pragma once

#include <stdint.h>

namespace asteria::core
{

    /**
     * Rôle d'une commande dans la composition du mouvement.
     *
     * Base :
     *     mouvement de référence, par exemple le suivi sidéral.
     *
     * Correction :
     *     variation additive appliquée à une commande Base,
     *     par exemple une correction de guidage.
     *
     * Override :
     *     commande remplaçant entièrement les commandes Base
     *     et Correction, par exemple un GoTo ou le joystick.
     */
    enum class MotionMode : uint8_t
    {
        Base,
        Correction,
        Override
    };

    /**
     * Nature physique du mouvement demandé.
     */
    enum class MotionType : uint8_t
    {
        Velocity,
        Position
    };

    /**
     * Niveau de priorité utilisé pour départager plusieurs
     * commandes concurrentes d'un même mode.
     */
    enum class MotionPriority : uint8_t
    {
        Low,
        Normal,
        High,
        Critical
    };

    /**
     * Intention de mouvement proposée par un module métier.
     *
     * MotionCommand :
     * - ne connaît pas l'axe concerné ;
     * - ne connaît pas la source concrète ;
     * - ne pilote aucun matériel ;
     * - utilise uniquement des unités physiques.
     *
     * Unités :
     * - position : degrés ;
     * - vitesse : degrés par seconde.
     *
     * Les fabriques publiques empêchent la création de combinaisons
     * incohérentes, comme une correction additive de position.
     */
    class MotionCommand
    {
    public:
        static MotionCommand baseVelocity(
            float velocityDegPerSec,
            MotionPriority priority = MotionPriority::Low)
        {
            return MotionCommand(
                MotionMode::Base,
                MotionType::Velocity,
                priority,
                velocityDegPerSec,
                false);
        }

        static MotionCommand correctionVelocity(
            float deltaVelocityDegPerSec,
            MotionPriority priority = MotionPriority::Normal)
        {
            return MotionCommand(
                MotionMode::Correction,
                MotionType::Velocity,
                priority,
                deltaVelocityDegPerSec,
                false);
        }

        static MotionCommand overrideVelocity(
            float velocityDegPerSec,
            MotionPriority priority = MotionPriority::High)
        {
            return MotionCommand(
                MotionMode::Override,
                MotionType::Velocity,
                priority,
                velocityDegPerSec,
                false);
        }

        static MotionCommand overridePosition(
            float positionDeg,
            bool relative,
            MotionPriority priority = MotionPriority::High)
        {
            return MotionCommand(
                MotionMode::Override,
                MotionType::Position,
                priority,
                positionDeg,
                relative);
        }

        MotionMode mode() const
        {
            return mode_;
        }

        MotionType type() const
        {
            return type_;
        }

        MotionPriority priority() const
        {
            return priority_;
        }

        float value() const
        {
            return value_;
        }

        bool isRelative() const
        {
            return relative_;
        }

    private:
        MotionCommand(
            MotionMode mode,
            MotionType type,
            MotionPriority priority,
            float value,
            bool relative)
            : mode_(mode),
              type_(type),
              priority_(priority),
              value_(value),
              relative_(relative)
        {
        }

        MotionMode mode_;
        MotionType type_;
        MotionPriority priority_;

        float value_;
        bool relative_;
    };

} // namespace asteria::core