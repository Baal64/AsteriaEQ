# Architecture – Asteria EQ

Version : 0.1  
Statut  : Draft  
Auteur  : Alexandre avec ChatGPT  
Dernière mise à jour : 2026-07-02

## Objectif

Ce document décrit l’architecture générale du firmware Asteria EQ.

Le firmware doit piloter une monture équatoriale à deux axes, RA et DEC, en séparant clairement :

- la logique métier astronomique ;
- le contrôle des moteurs ;
- la lecture des capteurs ;
- l’interface utilisateur ;
- la couche matérielle.

---

## Vue générale

```text
                         +----------------------+
                         |       Mount          |
                         +----------+-----------+
                                    |
      +-----------------------------+-----------------------------+
      |                             |                             |
      v                             v                             v
+-------------+             +---------------+             +---------------+
| StateMachine|             |      UI       |             | Diagnostics   |
+-------------+             +---------------+             +---------------+
      |                             |
      |                             +------------------------------+
      |                                                            |
      |                                                            v
      |                                                 +------------------+
      |                                                 | Guiding Manager  |
      |                                                 +------------------+
      |                                                            |
      |                                                            v
      +--------------------------->+------------------+<------------+
                                   | Tracking Engine  |
                                   +------------------+
                                             |
                          +------------------+------------------+
                          |                                     |
                          v                                     v
                    +-------------+                      +-------------+
                    |  Axis RA    |                      |  Axis DEC   |
                    +-------------+                      +-------------+
                          |                                     |
                +---------+--------+                  +---------+--------+
                |                  |                  |                  |
                v                  v                  v                  v
           TMC2209           AS5048A            TMC2209           AS5048A
```

## Principes fondamentaux

### 1. Responsabilité unique

Chaque objet possède une responsabilité clairement définie.

### 2. Unités physiques

Le cœur métier manipule uniquement des unités physiques.

### 3. Séparation du métier et du matériel

Le matériel est encapsulé derrière des interfaces.

### 4. Une seule source de vérité

Chaque information est modifiée par un seul composant.

Exemples :

- AxisState → uniquement Axis
- AxisTarget → uniquement MotionController
- MotionCommand → uniquement le module qui l'émet

### 5. Les abstractions émergent

On ne crée pas une abstraction parce qu'elle pourrait être utile, mais parce qu'une responsabilité distincte apparaît naturellement.

### 6. Création des classes

Une classe n'est terminée que lorsqu'on ne sait plus rien lui enlever sans perdre une responsabilité essentielle.

### 7 : les modules métier ne communiquent jamais directement

Ils communiquent uniquement via des objets de transfert (MotionCommand, AxisTarget) et des orchestrateurs (AxisController).
