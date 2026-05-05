# lem-in

Projet d'algorithmie de l'école 42. Le programme lit une fourmilière sur l'entrée standard et trouve le chemin optimal pour faire traverser toutes les fourmis de `##start` vers `##end` en un minimum de tours.

## Prérequis

- Compilateur C gcc
- `make`
- Système Unix/Linux/macOS

Aucune bibliothèque externe. Toutes les dépendances sont incluses dans le projet (`libft`, `get_next_line`, `vector`).

## Compilation

```bash
make        # compile le projet
make re     # recompile from scratch
make clean  # supprime les .o
make fclean # supprime les .o et l'exécutable
```

## Utilisation

```bash
./lem_in < maps/simple.txt
./lem_in < maps/huge_4000.txt
```

Le programme lit sur l'entrée standard et affiche les mouvements tour par tour sur la sortie standard. Les erreurs sont affichées sur la sortie d'erreur.

## Format d'entrée

## Architecture du projet

## Algorithme

### Parsing

### Construction du graphe de flot

### Edmonds-Karp (BFS)

### Sélection des chemins
Grace au fichier distrib_ants je distribue les fourmies sur dans les differents path en calculant le cout le moins elever pour allouer la forumis a ce chemins 
### Distribution des fourmis
La distribution des fourmis est grer dans print_walk je recherhce la fourmis la plus avancer dans les salles quelles doit passer pour arriver a la fin et pouvoir les faire avancer sans restraindre les autre forumis qui veulent avancer dans leur prochaine room
### Affichage

## Optimisations

## Gestion des erreurs et mémoire

## Tests
