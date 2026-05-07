#include "../../includes/flow.h"

t_vector *bfs_flow(t_door *start_door, t_door *end_door, unsigned int *head)
{
    t_vector *queue;
    t_vector *tmp;
    t_fnode *current;
    t_edge *edge;

    *head = 0;
    queue = vec_create(10);
    if(!queue)
        return (NULL);
    start_door->out->visited = 1;
    tmp = vec_append(queue, start_door->out);
    if(!tmp)
    {
        vec_free(queue);
        return (NULL);
    }
    queue = tmp;

    while(queue->size > *head)
    {
        current = (t_fnode *)queue->array[*head];
        (*head)++;
        if(current == end_door->in)
            return (queue);
        for (unsigned int i = 0; i < current->edges->size; i++)
        {
            edge = (t_edge *)current->edges->array[i];
            if (edge->cap > edge->flow && edge->to->visited == 0)
            {
                edge->to->visited = 1;
                edge->to->parent_edge = edge;
                tmp = vec_append(queue, edge->to);
                if (!tmp)
                {
                    vec_free(queue);
                    return (NULL);
                }
                queue = tmp;
            }
        }
    }
    vec_free(queue);
    return (NULL);
}

