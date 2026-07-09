# Architecture – Asteria EQ

Version : 0.1  
Statut  : Draft  
Auteur  : Alexandre avec ChatGPT  
Dernière mise à jour : 2026-07-02

## Objectif

Ce document décrit l’architecture générale du firmware Asteria EQ.

Le firmware doit piloter une monture équatoriale à deux axes, RA et DEC, en séparant clairement :

-   la logique métier astronomique ;
-   le contrôle des moteurs ;
-   la lecture des capteurs ;
-   l’interface utilisateur ;
-   la couche matérielle.

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
