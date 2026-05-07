#include "node.h"

float get_minX_coord(t_vector *nodes)
{
	float min_x = get_x(nodes->array[0]);

	for (unsigned int i = 1; i < nodes->size; i++)
	{
		float x = get_x(nodes->array[i]);

		if (x < min_x)
			min_x = x;
	}

	return (min_x);
}