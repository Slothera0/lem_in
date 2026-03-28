#include "node.h"
#include "vector.h"

#include <stdio.h>

void	normalize_coord(t_vector *nodes)
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

	// float range_x = max_x - min_x;
	// float range_y = max_y - min_y;

	printf("min_x: %f, max_x: %f, min_y: %f, max_y: %f\n", min_x, max_x, min_y, max_y);

	for (unsigned int i = 0; i < nodes->size; i++)
	{
		t_node *node = nodes->array[i];
		node->x = ((node->x) / max_x) * 1.5 - 0.75;
		node->y = ((node->y) / max_y) * 1.5 - 0.75;
		printf("node \"%s\" : %f:%f\n", node->name, node->x, node->y);
	}
}