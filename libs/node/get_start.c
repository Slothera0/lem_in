#include "node.h"
#include "vector.h"
#include "libft.h"

t_node *get_start(t_vector *vector)
{
	for (unsigned int i = 0; i < vector->size; i++)
	{
		if (START == get_node_type(vector->array[i]))
			return (vector->array[i]);
	}

	return (NULL);
}