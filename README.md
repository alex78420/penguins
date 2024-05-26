# README

## Projet : Jeu des Pingouins sur un Iceberg

### Description du Jeu

Le but de ce projet est de réaliser un jeu où des pingouins s'affrontent sur une grille hexagonale pour attraper le plus de poissons possible. Chaque joueur contrôle plusieurs pingouins qui se déplacent sur les cases hexagonales contenant des poissons. 

### Règles du Jeu

1. Le jeu se déroule sur une grille hexagonale.
2. Chaque case peut contenir entre 1 et 3 poissons.
3. Les joueurs déplacent leurs pingouins tour à tour en ligne droite.
4. Un pingouin ne peut pas traverser une case occupée ou fondue.
5. Après chaque déplacement, la case de départ est retirée et les poissons sont collectés par le joueur.
6. Le jeu continue jusqu'à ce que tous les joueurs soient bloqués et ne puissent plus déplacer leurs pingouins.
7. Le joueur avec le plus de poissons à la fin gagne la partie.

### Compilation et Exécution

#### Compilation

Pour compiler le jeu, ouvrez votre terminal et exécutez la commande suivante :

```sh
gcc -o runPenguinGame vscode.c
```

#### Exécution

Pour exécuter le jeu, utilisez la commande suivante après la compilation :

```sh
./runPenguinGame
```

### Comment Jouer

1. **Début du jeu** :
   - Le jeu vous demandera combien de joueurs participeront (entre 2 et 6).
   - Ensuite, chaque joueur doit entrer son nom.

2. **Affichage de la grille** :
   - La grille hexagonale avec les poissons et les pingouins sera affichée.
   - Chaque case peut contenir des poissons (`F1`, `F2`, `F3`), un pingouin (`P1`, `P2`, etc.), ou être vide (`XX` pour une case fondue).

3. **Tour de jeu** :
   - À chaque tour, le joueur sélectionne un de ses pingouins à déplacer. 
   - Les pingouins sont affichés avec leurs coordonnées (`y` et `x`).
   - Le joueur choisit la direction et le nombre de cases à déplacer.

4. **Déplacements** :
   - Utilisez les touches `a`, `e`, `q`, `d`, `w`, `c` pour les directions et spécifiez le nombre de cases (1-6).
   - Par exemple, pour déplacer un pingouin vers la gauche de 2 cases, entrez `a 2`.

5. **Fin de la partie** :
   - La partie se termine lorsque tous les joueurs ne peuvent plus déplacer leurs pingouins.
   - Les scores sont affichés et le ou les gagnants sont annoncés.

6. **Rejouer ou Quitter** :
   - Après chaque partie, vous pouvez choisir de rejouer ou de quitter en entrant `1` pour rejouer ou `2` pour quitter.

### Exemple d'Utilisation

```sh
gcc -o runPenguinGame vscode.c
./runPenguinGame
```

Amusez-vous bien en jouant à ce jeu des pingouins sur un iceberg !
