#include "node.h"
#include "lem_in.h"
#include "flow.h"
#include "vector.h"
#include "distrib_ants.h"

void free_all(t_lem_in *data, t_vector *nodes, t_vector *path, t_distrib_ants *distrib)
{
    if (distrib)
        free(distrib);
    if (path)
    {
        vec_iter(path, vec_free);
        vec_free(path);
    }
	vec_iter(nodes, free_node);
	vec_free(nodes);
	vec_iter(data->map, free);
	vec_free(data->map);
	free(data);
}