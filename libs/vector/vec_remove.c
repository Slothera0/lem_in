#include "vector.h"

int	vec_remove(t_vector *vector, void *content)
{

	for (unsigned int i = 0; i < vector->size; i++)
	{
		if (vector->array[i] == content)
		{
			for (unsigned int j = i; j < vector->size - 1; j++)
			{
				vector->array[j] = vector->array[j + 1];
			}

			vector->size -= 1;
			return (i);
		}
	}
	return (-1);
}