#include "node.h"
#include "vector.h"

#include <stdio.h>

float	normalize_coord(t_vector *nodes)
{
	float min_x = get_x(nodes->array[0]);
	float min_y = get_y(nodes->array[0]);
	float max_x = min_x;
	float max_y = min_y;

	for (unsigned int i = 1; i < nodes->size; i++)
	{
		float x = get_x(nodes->array[i]);
		float y = get_y(nodes->array[i]);

		if (x < min_x)
			min_x = x;
		if (y < min_y)
			min_y = y;
		if (x > max_x)
			max_x = x;
		if (y > max_y)
			max_y = y;
	}

	float range_x = max_x - min_x;
	float range_y = max_y - min_y;

	for (unsigned int i = 0; i < nodes->size; i++)
	{
		t_node *node = nodes->array[i];
		node->x = ((node->x - min_x) / range_x) * 1.50 - 0.75;
		node->y = ((node->y - min_y) / range_y) * 1.50 - 0.75;
	}

	return (1.50 / (range_x > range_y ? range_x : range_y));
}