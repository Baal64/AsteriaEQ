
# Asteria EQ - C++ Guidelines (v1)

## 1. Philosophie

Le firmware doit privilégier :

- la lisibilité ;
- la simplicité ;
- la prédictibilité ;
- la testabilité.

Une solution simple est toujours préférée à une solution complexe.

## 2. Style

Classes :

```C++
MotionController
```

Méthodes :

```C++
submitCommand()

update()

enable()
```

Variables membres :

```C++
driver_

encoder_

currentCommand_
```

Variables locales :

```C++
targetSpeed

currentPosition
```

Constantes :

```C++
constexpr float SiderealRate = ...
```

## 3. Namespace

Tout le projet sera sous :

```C++
namespace asteria
{
}
```

Puis :

```C++
namespace asteria::core
```

```C++
namespace asteria::hardware
```

```C++
namespace asteria::motion
```

```C++
namespace asteria::utils
```

Je pense qu'on n'aura probablement jamais besoin de plus.

## 4. Interdictions

Pas de :

```C++
new

delete

malloc

free
```

en V1.

Pas d'exceptions.

Pas de RTTI.

Pas de Singleton.

## 5. Préférer

Toujours :

```C++
enum class
```

plutôt que

```C++
enum
```

Toujours :

```C++
constexpr
```

plutôt que

```C++
#define
```

Lorsque c'est possible.

## 6. Interfaces

Les interfaces commencent toujours par :

```C++
I
```

Par exemple :

```C++
IStepperDriver

IAbsoluteEncoder

ILogger
```

## 7. Injection de dépendances

Une classe métier ne crée jamais ses dépendances.

Toujours :

```C++
Axis(IStepperDriver&, IAbsoluteEncoder&)
```

Jamais :

```C++
Axis()
{
    driver = new TMC2209(...);
}
```

## 8. Responsabilité

Une classe possède une seule responsabilité.

Si elle dépasse environ 500 à 700 lignes, on réévalue sa conception.

## 9. Documentation

Les .h expliquent :

- ce que fait la classe ;
- pourquoi elle existe.

Les .cpp expliquent :

- comment elle fonctionne.

## 10. Git

Aucun commit ne casse :

- la compilation ;
- la CI ;
- les tests.
