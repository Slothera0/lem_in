#include "flow.h"

t_edge *find_positive_flow_edge(t_fnode *current);

int rebuilt_path(t_door *start_door, t_door *end_door, t_vector **path)
{
    t_fnode *current;
    t_edge *edge;
    t_vector *tmp;
    t_node *last_room;

    current = start_door->out;
    last_room = start_door->out->room;
    tmp = vec_append(*path, start_door->out->room);
    if (!tmp)
        return (0);
    *path = tmp;
    while (current != end_door->in)
    {
        edge = find_positive_flow_edge(current);
        if(!edge)
            return (0);
        edge->flow -= 1;
        current = edge->to;
        if (current->room != last_room)
        {
            tmp = vec_append(*path, current->room);
            if (!tmp)
                return (0);
            *path = tmp;
            last_room = current->room;
        }
    }
    return (1);
}

t_edge *find_positive_flow_edge(t_fnode *current)
{
    t_edge *edge;

    for(unsigned int i = 0; i < current->edges->size; i++)
    {
        edge = (t_edge *)current->edges->array[i];
        if (edge->flow > 0)
            return (edge);
    }
    return (NULL);
}

int has_positive_flow_path(t_door *start_door)
{
    t_fnode *current;
    t_edge  *edge;

    current = start_door->out;
    while (current)
    {
        edge = find_positive_flow_edge(current);
        if (!edge)
            return (0);
        if (edge->to->room && edge->to->room->type == END)
            return (1);
        current = edge->to;
    }
    return (0);
}