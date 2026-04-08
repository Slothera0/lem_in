#include "node.h"

float get_maxX_coord(t_vector *nodes)
{
	float max_x = get_x(nodes->array[0]);

	for (unsigned int i = 1; i < nodes->size; i++)
	{
		float x = get_x(nodes->array[i]);

		if (x > max_x)
			max_x = x;
	}

	return (max_x);
}