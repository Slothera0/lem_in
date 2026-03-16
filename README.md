# lem-in

Projet d'algorithmie de l'ecole 42.

Le but de `lem-in` est de lire une fourmiliere depuis l'entree standard, de trouver la meilleure facon de faire traverser toutes les fourmis de `start` vers `end`, puis d'afficher les mouvements en respectant exactement le format demande par le sujet.

## Objectif

Le programme doit :

- lire le nombre de fourmis ;
- parser les salles et les liens ;
- construire un graphe representant la fourmiliere ;
- trouver un ou plusieurs chemins utiles entre `start` et `end` ;
- repartir les fourmis de facon optimale ;
- afficher la simulation tour par tour.

Le critere principal est de minimiser le nombre total de tours.

## Etat actuel du projet

## Compilation

```bash
make
```

Regles disponibles :

- `make`
- `make clean`
- `make fclean`
- `make re`

L'executable genere est :

```bash
./lem_in
```

## Utilisation

Exemple :

```bash
./lem_in < maps/simple.txt
```

## Format d'entree

Le programme lit sur l'entree standard :

1. le nombre de fourmis ;
2. les salles au format `name x y` ;
3. les liens au format `name1-name2`.

Regles importantes du sujet :

- `##start` designe la salle de depart ;
- `##end` designe la salle d'arrivee ;
- les lignes commencant par `#` sont des commentaires ;
- un nom de salle ne commence jamais par `L` ni `#` ;
- les coordonnees sont des entiers ;
- en cas d'entree invalide, le programme doit afficher `ERROR`.


