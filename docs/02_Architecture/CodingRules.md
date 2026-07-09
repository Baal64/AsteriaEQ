# Coding Rules – Asteria EQ

Version : 0.1  
Statut : Draft

## Objectif

Ce document définit les règles de codage du firmware Asteria EQ.

L’objectif est de conserver un code lisible, maintenable et portable.

---

## Langue

- Le code est écrit en anglais.
- La documentation projet est écrite en français.
- Les commentaires techniques dans le code peuvent être en anglais.

---

## Style général

- Une classe = une responsabilité.
- Pas de logique métier dans `main.cpp`.
- Pas de `delay()` dans le firmware applicatif.
- Pas d’accès direct aux broches hors couche Hardware.
- Pas de constantes magiques.
- Pas de dépendances circulaires entre modules.

---

## Nommage

### Classes

```cpp
class TrackingEngine;
class Axis;
class StateMachine;
```

### Méthodes

```cpp
void begin();
void update();
void setTrackingMode();
```

### Varaibles membres
```cpp
float currentSpeed_;
bool isEnabled_;
```

### Constentes
```cpp
constexpr float SIDEREAL_DAY_SECONDS = 86164.0905f;
constexpr uint16_t LED_BLINK_MS = 180;
```

### Énumérations
```cpp
enum class TrackingMode
{
    Stop,
    Sidereal,
    Solar,
    Lunar
};
```

### Interdictions
```cpp
delay();
```
A éviter dans le firmware applicatif
```cpp
#define STEP_PIN 2
```
Préférer
```cpp
constexpr uint8_t RA_STEP_PIN = 2;
```

### Structure
- Les interfaces publiques sont dans firmware/include/.
- Les implémentations sont dans firmware/src/.
- Les constantes sont centralisées dans Constants.h.
- Les broches sont centralisées dans Pins.h.

### Interruptions
- Les ISR doivent être courtes.
- Aucune logique métier complexe dans une ISR.
- Pas d’accès série dans une ISR.
- Les ISR modifient uniquement des variables simples ou déclenchent un tick.

### Logs
Les messages série doivent être courts et préfixés :

```cpp
[BOOT]
[HW]
[MOUNT]
[ERROR]
```

### Principe final
Le code doit raconter le domaine de la monture, pas les détails Arduino.
