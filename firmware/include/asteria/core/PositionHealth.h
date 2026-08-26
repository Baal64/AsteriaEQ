#pragma once

namespace asteria::core
{

    /**
     * État de confiance associé à la position absolue d'un axe.
     */
    enum class PositionHealth
    {
        /**
         * La position absolue est connue et considérée fiable.
         */
        Valid,

        /**
         * La dernière mesure n'est pas fiable, mais la perte de position
         * reste suffisamment courte pour que l'axe puisse éventuellement
         * continuer son mouvement de manière contrôlée.
         */
        TemporarilyInvalid,

        /**
         * La position absolue ne peut plus être considérée comme connue.
         *
         * L'axe doit être arrêté et une réacquisition de position
         * est nécessaire avant de reprendre le fonctionnement normal.
         */
        Lost
    };

} // namespace asteria::core