# Asteria EQ

## Vision

Asteria EQ est un contrôleur open-source destiné au pilotage de montures équatoriales astronomiques.

Le projet est né de la volonté de concevoir une solution maîtrisée de bout en bout, alliant mécanique, électronique et logiciel, afin d'obtenir une monture performante, évolutive et entièrement comprise par ses concepteurs.

Asteria EQ ne cherche pas à reproduire un produit commercial existant. Son objectif est de proposer une architecture claire, modulaire et durable, permettant d'ajouter progressivement de nouvelles fonctionnalités sans remettre en cause les fondations du système.

---

## Objectifs

Le firmware devra permettre :

- le suivi sidéral
- le suivi solaire
- le suivi lunaire
- le déplacement manuel des axes
- l'autoguidage ST4
- la recherche de la position Home
- la mise en position Park
- la gestion des encodeurs absolus
- la gestion des moteurs pas à pas

À plus long terme :

- GoTo
- PEC (Periodic Error Correction)
- communication avec un ordinateur
- configuration des drivers TMC2209 en UART
- interface utilisateur évoluée

---

## Philosophie

Le projet est guidé par les principes suivants.

### Architecture avant implémentation

Chaque évolution doit être pensée avant d'être développée.

Une fonctionnalité ne sera intégrée qu'après avoir défini clairement sa place dans l'architecture.

### Modularité

Chaque composant logiciel possède une responsabilité unique.

Les modules doivent être indépendants autant que possible.

### Évolutivité

Toute décision technique doit permettre l'évolution future du projet.

Le remplacement d'un composant matériel ne doit nécessiter que des modifications locales.

### Lisibilité

Le code est écrit pour être relu plusieurs années plus tard.

La clarté est privilégiée aux optimisations prématurées.

### Documentation

Toute décision importante est documentée.

La documentation fait partie intégrante du projet.

---

## Valeurs

Asteria EQ privilégie :

- la compréhension plutôt que la complexité
- la robustesse plutôt que la rapidité de développement
- la qualité plutôt que la quantité de fonctionnalités

---

## Équipe

Conception électronique et firmware

- Alexandre

Conception mécanique et impression 3D

- Virgil

Architecture logicielle

- Projet collaboratif