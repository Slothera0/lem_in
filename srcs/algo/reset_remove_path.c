#include "../../includes/flow.h"

void reset_fnodes(t_vector *graph)
{
    t_door *doors;

    for (unsigned int i = 0; i < graph->size; i++)
    {
        doors = (t_door *)graph->array[i];
        if (!doors)
            continue;
        doors->in->visited = 0;
        doors->in->parent_edge = NULL;
        doors->out->visited = 0;
        doors->out->parent_edge = NULL;
    }
}

void remove_path_usless(t_vector *all_path, unsigned int k)
{
	t_vector *path;

	if (!all_path)
		return;
	if (k >= all_path->size)
		return;
	while (all_path->size > k)
	{
		path = (t_vector *)all_path->array[all_path->size - 1];
		vec_free(path);
		all_path->size = all_path->size - 1;
	}
}