#include "../../includes/flow.h"

t_door *create_door(t_node *room)
{
    t_door *door;
    t_edge *forward;
    t_edge *reverse;
    unsigned int cap;

    door = malloc(sizeof(t_door));
    if(!door)
        return (NULL);
    door->in = create_fnode(room);
    if(!door->in)
    {
        free(door);
        return (NULL);
    }
    door->out = create_fnode(room);
    if(!door->out)
    {
        free(door->in);
        free(door);
        return (NULL);
    }

    if(room->type == NORMAL)
        cap = 1;
    else
        cap = UINT_MAX;

    add_flow_edge(door->in, door->out, cap);

    return (door);
}
