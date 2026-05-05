#include "vector.h"


void	vec_free(void *data)
{
	t_vector *vector = (t_vector *)data;

	free(vector->array);
	free(vector);
}
