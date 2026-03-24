#include "../../includes/node.h"
#include "../../srcs/vector/vector.h"

void block_path(t_vector *path)
{
    t_node *path_visited;

    if (!path || path->size < 3)
        return ;

    for (unsigned int i = 1; i + 1< path->size; i++)
    {
        path_visited = (t_node *)path->array[i];
        path_visited->blocked = 1;
    }
}