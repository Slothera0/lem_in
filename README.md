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

```
<nb_fourmis>
##start
<nom> <x> <y>
##end
<nom> <x> <y>
<nom> <x> <y>
...
<nom1>-<nom2>
...
```

- `##start` désigne la salle de départ
- `##end` désigne la salle d'arrivée
- Les lignes commençant par `#` sont des commentaires
- Un nom de salle ne commence jamais par `L` ni `#`
- En cas d'entrée invalide, le programme affiche `ERROR`

## Architecture du projet

```
srcs/
  main.c
  algo/
    bfs.c               — orchestrateur Edmonds-Karp
    bfs_flow            — BFS interne (static dans bfs.c)
    add_flow_edge.c     — construction du graphe de flot
    rebuild_path.c      — extraction des chemins depuis le flot
    calculate_score.c   — score et sélection du k optimal
    sort_path.c         — tri des chemins par longueur
    reset_remove_path.c — reset des fnodes et suppression des chemins inutiles
    create_door.c       — allocation d'une t_door
    create_fnode.c      — allocation d'un t_fnode
    distrib_ants.c      — assignation des fourmis aux chemins
    print_walk.c        — simulation et affichage tour par tour
    free_*.c            — libération mémoire
  node/
    create_node.c / create_link.c / get_node.c / ...
  parse/
    read_term.c         — lecture et parsing de l'entrée standard
includes/
  flow.h      — structures t_edge, t_fnode, t_door et prototypes
  node.h      — structure t_node
  lem_in.h    — structure t_lem_in
maps/         — maps de test
```

## Algorithme

### Parsing

Le programme lit l'entrée ligne par ligne avec `get_next_line`. Les salles sont stockées dans un vecteur de `t_node`. Avant de parser les liens, les nœuds sont triés alphabétiquement par nom (`sort_nodes`) pour permettre une recherche binaire dans `get_node` lors de la résolution des liens.

### Construction du graphe de flot

Chaque salle `t_node` est transformée en une `t_door` composée de deux nœuds de flot (`t_fnode`) :

```
t_node  →  t_door
              ├── in   (fnode d'entrée)
              └── out  (fnode de sortie)

in ──[cap=1]──> out      (capacité interne = 1, force les chemins vertex-disjoints)
```

Pour `##start` et `##end` la capacité interne est `INT_MAX`.

Chaque lien `A-B` du fichier devient deux arêtes dans `add_flow_edge` :

```
doorA->out ──[forward: cap=1, flow=0]──> doorB->in
doorB->in  ──[reverse: cap=0, flow=0]──> doorA->out
```

L'arête reverse permet à Edmonds-Karp d'annuler un flot mal orienté lors d'une itération suivante. Un pointeur `node->door` est mis en cache dans chaque `t_node` pour un accès O(1) lors de la construction des arêtes.

### Structures de données

```
t_door (salle A)
  ├── in  (t_fnode)
  │     ├── room        → t_node "A"
  │     ├── edges       → [arête interne vers out, arêtes reverse entrantes]
  │     ├── visited     → 0 ou 1 (BFS)
  │     └── parent_edge → arête par laquelle le BFS est arrivé ici
  │
  └── out (t_fnode)
        ├── room        → t_node "A"
        ├── edges       → [arêtes forward vers les voisins]
        ├── visited     → 0 ou 1 (BFS)
        └── parent_edge → arête par laquelle le BFS est arrivé ici

t_edge (forward A->out vers B->in)
  ├── to   → B->in        (fnode de destination)
  ├── cap  → 1            (capacité max)
  ├── flow → 0            (flot actuel)
  └── rev  → t_edge       (arête inverse — pas le parent, l'opposé directionnel)
```

`rev` permet de remonter vers le fnode précédent via `edge->rev->to`, et sert à annuler le flot lors d'une itération Edmonds-Karp.

### Edmonds-Karp (BFS)

Edmonds-Karp est une implémentation de Ford-Fulkerson qui utilise un BFS pour trouver le chemin augmentant le plus court à chaque itération.

**Phase 1 — trouver les chemins augmentants (`bfs_flow`)**

À chaque itération, `bfs_flow` parcourt le graphe en largeur depuis `start_door->out`. Une arête est franchissable si `cap > flow` (capacité résiduelle > 0). Chaque fnode atteint enregistre son `parent_edge`.

Si `end_door->in` est atteint, on remonte les `parent_edge` pour mettre à jour le flot :

```c
edge->flow += 1;       // arête forward : utilisée
edge->rev->flow -= 1;  // arête reverse : devient franchissable (annulation possible)
current = edge->rev->to; // fnode précédent
```

**Arrêt anticipé**

On s'arrête dès que `k * (k + 1) > nb_ants * 4`. Au-delà, le gain marginal d'un chemin supplémentaire est inférieur à 1 tour.

**Phase 2 — extraire les chemins réels (`rebuild_path.c`)**

`rebuilt_path` suit les arêtes avec `flow > 0` depuis `start_door->out` jusqu'à `end_door->in` en décrémentant le flot à chaque passage. Seules les salles réelles (`t_node`) sont stockées dans le vecteur chemin.

### Sélection des chemins

Chaque fourmi est assignée au chemin où son coût d'arrivée est le plus faible. Le coût est `longueur du chemin + nombre de fourmis déjà sur ce chemin`. Cette assignation gloutonne garantit une répartition optimale sans recalcul global.

### Distribution des fourmis

À chaque tour, les fourmis sont déplacées du plus avancé au moins avancé (du plus grand `path_step` vers 0). Cela garantit qu'une fourmi libère sa salle avant que celle derrière elle tente d'y entrer. Une fourmi n'avance que si la salle suivante est libre, sauf pour `##end` qui peut accueillir plusieurs fourmis simultanément.

### Affichage

Chaque mouvement est affiché sous la forme `L<id>-<salle>`. Tous les mouvements d'un même tour sont sur la même ligne, séparés par des espaces, suivis d'un saut de ligne.
