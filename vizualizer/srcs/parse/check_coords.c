#include "rend.h"
#include "node.h"
#include "vector.h"

int check_coords(t_vector *nodes)
{
	for (unsigned int i = 0; i < nodes->size; i++)
	{
		t_node *node = nodes->array[i];
		if (node->x > MAX_COORD || node->y > MAX_COORD || node->x < 0 || node->y < 0)
			return (0);
	}
	return (1);
}
