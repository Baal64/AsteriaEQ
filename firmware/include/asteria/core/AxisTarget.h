#pragma once

namespace asteria::core
{

    /**
     * Mode de consigne finale transmis à un axe.
     *
     * AxisTarget est produit uniquement par AxisController.
     * Il représente la décision finale après arbitrage des MotionCommand.
     */
    enum class AxisTargetType
    {
        Idle,
        Stop,
        Velocity,
        Position
    };

    /**
     * Consigne finale comprise par Axis.
     *
     * Contrairement à MotionCommand, AxisTarget ne contient ni source,
     * ni priorité, ni contexte métier. L'axe ne connaît que le mouvement
     * qu'il doit exécuter.
     *
     * Unités :
     * - position : degrés ;
     * - vitesse : degrés par seconde.
     */
    struct AxisTarget
    {
        AxisTargetType type{AxisTargetType::Idle};

        float positionDeg{0.0F};
        float velocityDegPerSec{0.0F};

        /**
         * Indique si la position cible est relative à la position actuelle.
         *
         * Ce champ n'a de sens que pour AxisTargetType::Position.
         */
        bool relative{false};
    };

} // namespace asteria::core
