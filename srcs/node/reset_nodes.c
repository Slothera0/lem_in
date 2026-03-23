#include "../../includes/node.h"
#include "../../srcs/vector/vector.h"

void	reset_nodes(t_vector *nodes)
{
    t_node *current;

    for (unsigned int i = 0; i < nodes->size; i++)
    {
        current = (t_node *)nodes->array[i];
        current->visited = 0;
        current->parent = NULL;
    }
}