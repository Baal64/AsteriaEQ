## Contexte :

Plusieurs modules peuvent produire des demandes de mouvement.

## Décision :

Axis n'accepte que des AxisTarget produits par MotionController.

## Conséquences :

- l'axe reste indépendant des algorithmes métier ;
- les futurs modules s'intègrent sans modifier Axis ;
- le code est plus simple à tester.
