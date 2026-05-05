#include "flow.h"

void free_door(void *data)
{
    t_door *door;

    door = (t_door *)data;
    free_fnode(door->in);
    free_fnode(door->out);
    free(door);
}