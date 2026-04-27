#include "rend.h"
#include "vector.h"

int ants_on_path(t_ant *ant, t_vector *path)
{
	for (unsigned int i = 0; i < path->size; i++)
	{
		t_path *p = path->array[i];
		if (ant->id == p->ant)
			return (1);
	}
	return (0);
}
