#include "vector.h"

void	vec_iter(t_vector *vector, void (*f)(void *))
{
	for(unsigned int i = 0; i < vector->size; i++)
	{
		f(vector->array[i]);
	}
}