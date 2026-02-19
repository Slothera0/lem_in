#include "vector.h"


void	vec_copy(t_vector *src, t_vector *dest)
{
	unsigned int	i;

	i = 0;

	while (i < src->size && i < dest->max_size)
	{
		dest->array[i] = src->array[i];
		i++;
	}
	
	if (src->size > dest->max_size)
		dest->size = dest->max_size;
	else
		dest->size = src->size;
}
