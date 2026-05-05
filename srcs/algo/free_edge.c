#include "../../includes/flow.h"

void free_edge(void *data)
{
    t_edge *edge;

    edge = (t_edge *)data;
    free(edge);
}