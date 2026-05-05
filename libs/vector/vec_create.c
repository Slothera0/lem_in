#include "vector.h"


t_vector	*vec_create(unsigned int size)
{
	t_vector	*new;

	new = malloc(sizeof(t_vector));
	if (!new)
		return (NULL);

	new->array = malloc(sizeof(new->array) * size);
	if (!(new->array))
	{
		free(new);
		return (NULL);
	}

	new->size = 0;
	new->max_size = size;
	
	return (new);
}
