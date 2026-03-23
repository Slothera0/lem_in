#include "../../includes/node.h"
#include "../../srcs/vector/vector.h"

void block_path(t_vector *path)
{
    t_node *current;
    t_node *path_visited;

    if (!path || path->size < 3)
        return ;

    for (unsigned int i = 1; i < path->size; i++)
    {
        path_visited = (t_node *)path->array[i];
        current->blocked = 1;
    }
}