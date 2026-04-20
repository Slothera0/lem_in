#include "../../includes/flow.h"


t_fnode *create_fnode(t_node *room)
{
    t_fnode *node;

    node = malloc(sizeof(t_fnode));
    if (!node)
        return (NULL);
    node->room = room;
    node->edges = vec_create(10);
    node->visited = 0;
    node->parent_edge = NULL;
    return (node);
}
