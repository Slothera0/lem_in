#include "node.h"

float get_minY_coord(t_vector *nodes)
{
	float min_y = get_y(nodes->array[0]);

	for (unsigned int i = 1; i < nodes->size; i++)
	{
		float y = get_y(nodes->array[i]);

		if (y < min_y)
			min_y = y;
	}

	return (min_y);
}