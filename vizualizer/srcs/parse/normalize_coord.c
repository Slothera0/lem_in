#include "node.h"
#include "vector.h"

float	normalize_coord(t_vector *nodes)
{
	float min_x = get_minX_coord(nodes);
	float min_y = get_minY_coord(nodes);
	float max_x = get_maxX_coord(nodes);
	float max_y = get_maxY_coord(nodes);

	float range_x = max_x - min_x;
	float range_y = max_y - min_y;
	float margin_left = 0.10f;
	float margin_right = 0.10f;
	float margin_bottom = 0.10f;
	float margin_top = 0.25f;
	float scale_x = 1.0f - margin_left - margin_right;
	float scale_y = 1.0f - margin_bottom - margin_top;

	if (range_x == 0.0f)
		range_x = 1.0f;
	if (range_y == 0.0f)
		range_y = 1.0f;

	for (unsigned int i = 0; i < nodes->size; i++)
	{
		t_node *node = nodes->array[i];
		float nx = (node->x - min_x) / range_x;
		float ny = (node->y - min_y) / range_y;

		node->x = (nx * scale_x + margin_left) * 2.0f - 1.0f;
		node->y = (ny * scale_y + margin_bottom) * 2.0f - 1.0f;
	}

	return ((range_x > range_y) ? range_x : range_y);
}
