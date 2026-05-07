#include "flow.h"

void free_fnode(void *data)
{
    t_fnode *fnode = (t_fnode *)data;

    vec_iter(fnode->edges, free_edge);
    vec_free(fnode->edges);
    free(fnode);
}