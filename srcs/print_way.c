#include "vector.h"
#include "node.h"
#include "ft_printf.h"

void	print_way(void *data)
{
	t_vector *vector = (t_vector *)data;

	ft_printf("Way of size %u:\n", vector->size);

	for (unsigned int i = 0; i < vector->size - 1; i++)
	{
		ft_printf("%s -> ", get_node_name(vector->array[i]));
	}
	ft_printf("%s\n", get_node_name(vector->array[vector->size - 1]));
}