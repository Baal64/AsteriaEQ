
## Exigences fonctionnelles

### Suivi

REQ-001  
La monture doit assurer un suivi sidéral continu.

REQ-002  
Le suivi sidéral ne doit jamais être interrompu lors d’une correction ST4.

REQ-003  
Le système doit être capable de retrouver sa position Home.

REQ-004  
La monture doit pouvoir reprendre une position connue si les encodeurs absolus fournissent une position cohérente.

REQ-005  
L’utilisateur doit pouvoir sélectionner un mode de suivi parmi :

- sidéral ;
- solaire ;
- lunaire ;
- arrêt.

REQ-006  
Le changement de mode de suivi ne doit pas provoquer de mouvement brusque ni de perte de pas.

---

### Déplacement manuel

REQ-007  
L’utilisateur doit pouvoir déplacer l’axe RA au joystick pour le cadrage.

REQ-008  
L’utilisateur doit pouvoir déplacer l’axe DEC au joystick pour le cadrage.

REQ-009  
Le déplacement manuel doit être progressif, avec une zone morte configurable afin d’éviter les mouvements involontaires.

REQ-010  
Le déplacement manuel doit pouvoir être effectué sans désactiver complètement le suivi RA.

---

### Guidage

REQ-011  
La monture doit accepter des corrections d’autoguidage via un port ST4 actif bas.

REQ-012  
Les corrections ST4 doivent pouvoir agir sur les axes RA et DEC.

REQ-013  
Les corrections ST4 doivent être appliquées comme des corrections autour du mouvement de suivi, et non comme un remplacement du suivi.

---

### Sécurité

REQ-014  
La monture doit pouvoir désactiver les moteurs en cas d’état d’erreur.

REQ-015  
La monture doit empêcher les mouvements dépassant les limites logicielles définies pour RA et DEC.

REQ-016  
La monture doit détecter une incohérence importante entre la position théorique moteur et la position réelle encodeur.

---

### Interface utilisateur

REQ-017  
La monture doit fournir une indication visuelle de son état via une LED.

REQ-018  
La LED doit indiquer au minimum :
- arrêt ;
- suivi sidéral ;
- suivi solaire ;
- suivi lunaire ;
- erreur.

REQ-019  
La monture doit fournir des messages de diagnostic via la liaison série USB.

---

### Configuration

REQ-020  
La monture doit conserver en mémoire non volatile le dernier mode de suivi utilisé.

REQ-021  
Les paramètres mécaniques principaux doivent être centralisés dans un fichier de configuration.

REQ-022  

Les rapports de réduction RA et DEC doivent être modifiables sans modifier la logique métier du firmware.

---

## Exigences futures

REQ-F001  
La monture devra pouvoir exécuter une mise en position Park.

REQ-F002  
La monture devra pouvoir effectuer une correction d’erreur périodique PEC.

REQ-F003  
La monture devra pouvoir recevoir des commandes depuis un ordinateur.

REQ-F004  
La monture devra pouvoir configurer les drivers TMC2209 via UART.

REQ-F005  
La monture devra pouvoir effectuer des déplacements GoTo.
