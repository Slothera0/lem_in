#include "vector.h"


void	vec_free(t_vector *vector)
{
	free(vector->array);
	free(vector);
}
