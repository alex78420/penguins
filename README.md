# Rapport de Projet : CY-FISH

## Membres de l'Équipe

- **Alexandre Klobb**
- **Aymane El Feddi**
- **Reine-Marie**

### Description du Projet

Le projet "CY-FISH" consiste en un jeu de type plateforme où entre 2 et 6 joueurs s'affrontent en contrôlant des pingouins sur une banquise. Le but du jeu est de récupérer un maximum de poissons à l'aide des pingouins, qui se déplacent sur une grille hexagonale. Les poissons et les pingouins sont positionnés aléatoirement au début du jeu. Le joueur ayant le plus de points lorsque la banquise a complètement fondu remporte la partie.

### Problèmes Rencontrés

1. **Problèmes de Couleurs :**
   - Les couleurs ne fonctionnaient que sur Linux, avec la bibliothèque `ncurses` sur l'ordinateur d'Alexandre utilisant WSL (Windows Subsystem for Linux).
   - Les autres membres, Aymane et Reine-Marie, avaient des Macs sur lesquels WSL ne pouvait pas être installé.
   - Nous avons décidé de ne pas utiliser `ncurses` pour ne pas pénaliser certains membres de l'équipe et sommes passés à une solution sans couleurs avec une grille plus ordinaire.

2. **Affichage des Pingouins :**
   - Sans les couleurs, nous avons rencontré des bugs d'affichage des pingouins.
   - Chaque caractère n'ayant pas la même longueur lors de l'affichage, cela cassait visuellement la grille de jeu.
   - Nous sommes donc revenus à une grille classique basique, mais toutes les fonctionnalités du jeu fonctionnent correctement.

### Solutions Apportées

1. **Environnement de Développement :**
   - Abandon de `ncurses` en faveur de solutions plus simples et universelles.
   - Passage à une grille sans couleur pour assurer la compatibilité sur toutes les machines de l'équipe.

2. **Affichage et Fonctionnalités :**
   - Utilisation de caractères simples pour représenter la banquise, les pingouins et les poissons, garantissant ainsi un affichage correct sur tous les systèmes.
   - Tous les déplacements et les règles du jeu ont été implémentés avec succès malgré les défis d'affichage.

### Résultats Obtenus

- La compilation se fait correctement sur toutes les machines de l'équipe.
- L'affichage est basique mais fonctionnel.
- Les déplacements des pingouins et la collecte des poissons fonctionnent comme prévu.
- Toutes les fonctionnalités essentielles du jeu sont opérationnelles.

### Organisation de l'Équipe

Pour communiquer et collaborer, nous avons utilisé GitHub pour l'hébergement du code et Discord pour la discussion. Alexandre utilise Ubuntu avec WSL sur Windows, tandis que Aymane et Reine-Marie utilisent macOS.

### Répartition des Tâches

| Semaine         | Alexandre Klobb | Aymane El Feddi          | Reine-Marie                   |
|-----------------|-----------------|--------------------------|-------------------------------|
| Semaine 1       | Création des structures et tableaux 2D | Fenêtre et déplacement d’un élément dedans | Fonctions de création d’éléments de structures |
| Semaine 2       | Première interface graphique et prototype de score | Vérifications des mouvements et affichage banquise | Déplacements des pingouins et debug Visual Studio Code |
| Semaine 3       | Correction de l’affichage et branchements conditionnels | Debug des erreurs de segmentation | Debug Visual Studio Code |
| Semaine 4       | Tests d’affichage avec l’unicode et relier la banquise au tableau | Affichage des poissons et corrections de bugs | Score et page d’accueil |
| Semaine 5       | Élaboration de la structure de plusieurs fichiers de code | Relier la banquise au tableau | Debug git et ncurses |
| Semaine 6       | Prototype de déplacement des pingouins et couleurs | Empêche les pingouins de sortir de la zone de jeu | Page d’accueil et robustesse du code |
| Semaine 7       | Vérifications et corrections des fonctions | Sélection pingouin et MakeFile | Esthétique du jeu et README final |

### Recommandations Futures

Nous avons perdu beaucoup de temps à cause de la différence de systèmes d'exploitation. À l'avenir, nous privilégierons une approche en ligne, comme Lightning ou GitHub Codespaces, permettant d'avoir le même environnement d'exécution pour tous. Nous ne connaissions pas ces outils avant de commencer ce projet, mais nous les utiliserons pour nos prochains travaux afin de garantir une compatibilité et une efficacité maximales.
