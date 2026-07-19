#pragma once

#include <stdint.h>

#include <asteria/core/Axis.h>
#include <asteria/core/AxisTarget.h>
#include <asteria/core/IMotionSource.h>

namespace asteria::core
{

    /**
     * Coordonne les sources de mouvement associées à un axe.
     *
     * À chaque cycle, l'AxisController :
     * - interroge toutes les sources ;
     * - compose leurs propositions ;
     * - produit une unique AxisTarget ;
     * - transmet cette cible à l'Axis ;
     * - met à jour l'Axis.
     *
     * L'AxisController ne possède ni l'Axis ni les sources.
     * Leur durée de vie doit donc être supérieure à la sienne.
     */
    class AxisController
    {
    public:
        /**
         * Construit le contrôleur d'un axe.
         *
         * @param axis Axe piloté par ce contrôleur.
         * @param sources Tableau des sources de mouvement.
         * @param sourceCount Nombre de sources contenues dans le tableau.
         */
        AxisController(
            Axis &axis,
            IMotionSource *const *sources,
            uint8_t sourceCount)
            : axis_(axis),
              sources_(sources),
              sourceCount_(sourceCount)
        {
        }

        /**
         * Met à jour les sources, compose leurs propositions
         * et applique la cible obtenue à l'axe.
         *
         * @param deltaTimeSec Temps écoulé depuis le cycle précédent,
         *                     exprimé en secondes.
         */
        void update(float deltaTimeSec);

    private:
        /**
         * Interroge les sources et transforme leurs propositions
         * en une cible unique pour l'axe.
         *
         * @param deltaTimeSec Temps écoulé depuis le cycle précédent.
         * @return Cible à appliquer à l'axe.
         */
        AxisTarget composeTarget(float deltaTimeSec);

        Axis &axis_;
        IMotionSource *const *const sources_;
        const uint8_t sourceCount_;
    };

} // namespace asteria::core
