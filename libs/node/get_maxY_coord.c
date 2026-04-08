#include "node.h"

float get_maxY_coord(t_vector *nodes)
{
	float max_y = get_y(nodes->array[0]);

	for (unsigned int i = 1; i < nodes->size; i++)
	{
		float y = get_y(nodes->array[i]);

		if (y > max_y)
			max_y = y;
	}

	return (max_y);
}