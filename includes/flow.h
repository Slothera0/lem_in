#ifndef FLOW_H
# define FLOW_H


#include "../srcs/vector/vector.h"
#include "../includes/node.h"
#include "../includes/lem_in.h"


typedef struct s_edge t_edge;
typedef struct s_fnode t_fnode;
typedef struct s_door t_door;

t_fnode *create_fnode(t_node *room);
void add_flow_edge(t_fnode *from, t_fnode *to, int cap);
t_door *create_door(t_node *room);
t_door *get_door_by_room(t_node *room, t_vector *doors);
t_vector *build_flow_graph(t_lem_in *data, t_door **start_door, t_door **end_door);
t_vector *bfs(t_lem_in *data);

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