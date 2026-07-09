# State Machine – Asteria EQ

Version : 0.1  
Statut : Draft

## Objectif

Ce document décrit la machine d’états principale du firmware Asteria EQ.

La machine d’états définit le comportement global de la monture et encadre les transitions entre les phases de démarrage, initialisation, recherche Home, suivi, guidage, parking et erreur.

---

## États principaux

```text
BOOT
SELF_TEST
HOME_REQUIRED
HOMING
READY
TRACKING
GUIDING
MANUAL_MOVE
PARKING
PARKED
ERROR