Contexte :

Plusieurs modules peuvent demander simultanément un mouvement (Tracking, Guiding, GoTo, Home, Park, Joystick).

Décision :

Toutes les demandes de mouvement transitent par MotionController, seul autorisé à transmettre des commandes aux axes.

Conséquences :

✅ Une seule politique de priorité.
✅ Pas d'ordres contradictoires.
✅ Les moteurs restent indépendants des moteurs de calcul.
✅ Les futurs modules (PEC, Remote Control, Scheduler...) s'intègrent naturellement.
