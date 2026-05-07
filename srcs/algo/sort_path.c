#include "flow.h"

void sort_path_by_size(t_vector *all_path)
{
	t_vector *a;
	t_vector *b;
	void *tmp;

	for (unsigned int i = 0; i < all_path->size; i++)
	{
		for (unsigned int j = i + 1; j < all_path->size; j++)
		{
			a = (t_vector *)all_path->array[i];
			b = (t_vector *)all_path->array[j];
			if (a->size > b->size)
			{
				tmp = all_path->array[i];
				all_path->array[i] = all_path->array[j];
				all_path->array[j] = tmp;
			}
		}
	}
}