# Motion Command – Asteria EQ

Version : 0.1  
Statut : Draft

## Objectif

`MotionCommand` définit le langage commun utilisé pour exprimer une intention de mouvement dans Asteria EQ.

Il permet aux différents modules de proposer des mouvements sans piloter directement les axes.

---

## Principe

-   Une commande de mouvement est une intention.
-   Elle ne pilote pas le moteur.
-   Elle ne génère pas d’impulsions STEP.
-   Elle ne décide pas des priorités globales.
-   Elle décrit simplement ce qu’un module souhaite faire.

---

## Flux général
```Text
TrackingEngine
GuidingEngine
Joystick
HomeEngine
ParkEngine
GotoEngine
        ↓
 MotionCommand
        ↓
 MotionController
        ↓
      Axis
        ↓
 StepperDriver
```

## Types de mouvement
```C++
enum class MotionType
{
    None,
    Stop,
    Velocity,
    Position,
    Homing,
    Parking
};
```

## None

Aucune commande active.

## Stop

Demande d’arrêt contrôlé.

## Velocity

Commande en vitesse.

Utilisée par :

-   suivi sidéral ;
-   suivi solaire ;
-   suivi lunaire ;
-   joystick ;
-   guidage.

## Position

Commande vers une position cible.

Utilisée par :

-   Park ;
-   futur GoTo.

## Homing

Commande spécifique à la recherche Home.

## Parking

Commande spécifique à la mise en position Park.

## Sources
```C++
enum class MotionSource
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
```

La source permet de savoir quel module a produit la commande.

Elle est utile pour :

-   arbitrage ;
-   diagnostic ;
-   logs ;
-   debug.

## Priorités
```C++
enum class MotionPriority
{
    Low,
    Normal,
    High,
    Critical
};
```

Les priorités ne remplacent pas la politique d’arbitrage du MotionController.

Elles fournissent une information supplémentaire.
```Text
Exemple :

Safety est toujours prioritaire.
Tracking est généralement Low.
Guiding est généralement Normal.
Joystick est généralement High.
Park et Home peuvent être High.
Safety est Critical.
```

## Axe cible

Une commande doit pouvoir cibler :

-   RA ;
-   DEC ;
-   les deux axes.

```C++
enum class AxisId
{
    None,
    RA,
    DEC,
    Both
};
```

## Structure proposée
```C++
struct MotionCommand
{
    AxisId axis;

    MotionType type;
    MotionSource source;
    MotionPriority priority;

    float targetPositionDeg;
    float targetSpeedDegPerSec;
    float accelerationDegPerSec2;

    unsigned long durationMs;

    bool relative;
    bool enabled;
};
```

## Signification des champs
### axis

Axe concerné par la commande.

### type

Nature de la commande.

### source

Module ayant produit la commande.

### priority

Priorité indicative.

### targetPositionDeg

Position cible en degrés.

Utilisé principalement avec Position, Parking et futur Goto.

### targetSpeedDegPerSec

Vitesse cible en degrés par seconde.

Utilisé avec Velocity, Tracking, Guiding et Joystick.

### accelerationDegPerSec2

Accélération souhaitée.

Peut être ignorée en V1 si les rampes ne sont pas encore implémentées.

### durationMs

Durée éventuelle de validité de la commande.

Utilisé notamment pour certaines corrections temporaires.

### relative

Indique si la commande est relative à la position actuelle.

### enabled

Indique si la commande est active.

## Exemples

### Suivi sidéral RA
```C++
MotionCommand siderealTracking
{
    AxisId::RA,
    MotionType::Velocity,
    MotionSource::Tracking,
    MotionPriority::Low,
    0.0f,
    SIDEREAL_SPEED_DEG_PER_SEC,
    0.0f,
    0,
    false,
    true
};
```

### Correction ST4 RA+

```C++
MotionCommand guideRaPlus
{
    AxisId::RA,
    MotionType::Velocity,
    MotionSource::Guiding,
    MotionPriority::Normal,
    0.0f,
    GUIDE_SPEED_DEG_PER_SEC,
    0.0f,
    0,
    true,
    true
};
Déplacement joystick DEC
MotionCommand joystickDec
{
    AxisId::DEC,
    MotionType::Velocity,
    MotionSource::Joystick,
    MotionPriority::High,
    0.0f,
    -0.2f,
    0.0f,
    0,
    true,
    true
};
```

### Park

```C++
MotionCommand parkRa
{
    AxisId::RA,
    MotionType::Position,
    MotionSource::Park,
    MotionPriority::High,
    PARK_RA_POSITION_DEG,
    0.0f,
    PARK_ACCELERATION_DEG_PER_SEC2,
    0,
    false,
    true
};
```

##  Règles d’utilisation
-   Aucun module ne doit piloter directement un axe.
-   Tout mouvement doit être exprimé sous forme de MotionCommand.
-   MotionController est le seul module autorisé à arbitrer plusieurs commandes.
-   Une commande expirée ne doit plus être appliquée.
-   Une commande Safety doit pouvoir interrompre toute autre commande.
-   Une commande Tracking peut être combinée avec une commande Guiding.
-   Une commande Joystick peut suspendre ou modifier temporairement le suivi selon la politique choisie.

## Combinaisons prévues

| Commande de base	| Correction compatible	| Résultat |  
|:----------------- | :-------------------: | -------: |
| Tracking | Guiding | suivi corrigé |  
| Tracking | Joystick | déplacement manuel avec ou sans maintien du suivi |
| Tracking | Safety	| arrêt immédiat |
| Goto | Safety | arrêt immédiat |
|Park	| Safety | arrêt immédiat |
| Home | Safety | arrêt immédiat |

## Questions ouvertes

-   Le joystick doit-il suspendre le guidage ST4 ?
-   Le joystick doit-il suspendre le suivi RA ou le modifier temporairement ?
-   Une commande Park doit-elle être représentée comme Position ou comme Parking ?
-   Les vitesses doivent-elles être stockées en degrés/seconde ou en pas/seconde dans MotionCommand ?
-   Faut-il ajouter un champ timestampMs pour gérer précisément l’expiration des commandes ?



Petite remarque importante : la question des **unités** est à valider. Mon instinct : `MotionCommand` doit rester en unités métier, donc **degrés / degrés par seconde**, et la conversion en pas moteur doit rester dans `Axis`.