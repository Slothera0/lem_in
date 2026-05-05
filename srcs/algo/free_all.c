#include "../../includes/flow.h"

void free_all(void *data)
{
    t_vector *vec;

    vec = (t_vector *)data;
    vec_iter(vec, free_door);
    vec_free(vec);
}