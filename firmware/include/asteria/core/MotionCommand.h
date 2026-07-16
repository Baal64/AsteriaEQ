#pragma once

#include <stdint.h>

namespace asteria::core
{

    /**
     * Identifie l'axe concerné par une demande de mouvement.
     *
     * Une commande cible toujours un seul axe. Une opération impliquant RA et DEC
     * produit donc deux commandes indépendantes.
     */
    enum class AxisId : uint8_t
    {
        Ra,
        Dec
    };

    /**
     * Nature élémentaire du mouvement demandé.
     *
     * Home, Park, Tracking ou Guiding ne sont pas des types de mouvement :
     * ce sont les sources ou les contextes qui produisent ces mouvements.
     */
    enum class MotionType : uint8_t
    {
        None,
        Stop,
        Velocity,
        Position
    };

    /**
     * Module à l'origine de la demande.
     */
    enum class MotionSource : uint8_t
    {
        None,
        Safety,
        Tracking,
        Guiding,
        Joystick,
        Home,
        Park,
        Goto
    };

    /**
     * Priorité indicative de la demande.
     *
     * La priorité seule ne définit pas toute la politique d'arbitrage :
     * MotionController reste responsable de la décision finale.
     */
    enum class MotionPriority : uint8_t
    {
        Low,
        Normal,
        High,
        Critical
    };

    /**
     * Intention de mouvement produite par un module métier.
     *
     * MotionCommand transporte uniquement des données. Elle ne pilote aucun axe,
     * n'effectue aucun arbitrage et ne convertit pas les unités métier en pas.
     *
     * Unités :
     * - position : degrés ;
     * - vitesse : degrés par seconde ;
     * - durée : millisecondes.
     */
    struct MotionCommand
    {
        AxisId axis{AxisId::Ra};
        MotionType type{MotionType::None};
        MotionSource source{MotionSource::None};
        MotionPriority priority{MotionPriority::Low};

        float targetPositionDeg{0.0F};
        float targetVelocityDegPerSec{0.0F};

        /**
         * Durée de validité d'une commande temporaire.
         *
         * La valeur zéro signifie que la commande reste valide jusqu'à son
         * remplacement ou son annulation explicite.
         */
        uint32_t durationMs{0U};

        /**
         * Indique si la position ou la vitesse exprimée est relative à la
         * consigne de base applicable.
         *
         * Exemple : une correction de guidage est relative au suivi courant.
         */
        bool relative{false};
    };

} // namespace asteria::core
