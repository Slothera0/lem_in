#include "vector.h"

void	*vec_end(t_vector *vector)
{
	if (vector->size == 0)
		return (NULL);
	return (vector->array[vector->size - 1]);
}
