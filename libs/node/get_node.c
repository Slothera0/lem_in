#include "node.h"
#include "vector.h"
#include "libft.h"

t_node *get_node(t_vector *vector, char *name)
{
	for (unsigned int i = 0; i < vector->size; i++)
	{
		if (ft_strcmp(name, get_node_name(vector->array[i])) == 0)
			return (vector->array[i]);
	}

	return (NULL);
}