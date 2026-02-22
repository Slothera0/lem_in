#include "lem_in.h"
#include "vector.h"
#include "libft.h"

t_node *get_node(t_vector *vector, char *name)
{
	for (unsigned int i = 0; i < vector->size; i++)
	{
		if (ft_strcmp(name, ((t_node *)vector->array[i])->name) == 0)
			return (vector->array[i]);
	}

	return (NULL);
}