#ifndef FLOW_H
# define FLOW_H


#include "../includes/vector.h"
#include "../includes/node.h"
#include "../includes/lem_in.h"
#include <limits.h>

typedef struct s_edge t_edge;
typedef struct s_fnode t_fnode;
typedef struct s_door t_door;

t_fnode *create_fnode(t_node *room);
void add_flow_edge(t_fnode *from, t_fnode *to, int cap);
t_door *create_door(t_node *room);
t_vector *build_flow_graph(t_lem_in *data, t_door **start_door, t_door **end_door);
t_vector *edmonds_karp(t_lem_in *data);
void free_edge(void *data);
void free_fnode(void *data);
void free_door(void *data);
void free_all(void *data);
void sort_path_by_size(t_vector *all_path);
unsigned int score_k_path(t_vector *all_path, unsigned int k, unsigned int nb_ants);
unsigned int best_k_path(t_vector *all_path, unsigned int nb_ants);
void reset_fnodes(t_vector *graph);
void remove_path_usless(t_vector *all_path, unsigned int k);
int rebuilt_path(t_door *start_door, t_door *end_door, t_vector **path);
int has_positive_flow_path(t_door *start_door);
t_vector *get_path(t_vector *graph, t_door *start_door, t_door *end_door, unsigned int nb_ants);
t_vector *bfs_flow(t_door *start_door, t_door *end_door, unsigned int *head);

typedef struct s_edge
{
    t_fnode *to;
    int cap;
    int flow;
    t_edge *rev;
}   t_edge;

typedef struct s_door
{
    t_fnode *in;
    t_fnode *out;
}   t_door;

typedef struct s_fnode
{
    t_node *room;
    t_vector *edges;
    unsigned int visited;
    t_edge *parent_edge;
}   t_fnode;


#endif