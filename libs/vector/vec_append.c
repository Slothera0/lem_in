#include "vector.h"

t_vector	*vec_append(t_vector *vector, void *content)
{
	t_vector *new;

	if (vector->max_size == vector->size)
	{
		new = vec_create(vector->max_size * 2);
		if (!new)
		return (NULL);
		
		vec_copy(vector, new);
		vec_free(vector);
		vector = new;
	}
	
	vector->array[vector->size] = content;
	vector->size++;

	return (vector);
}
