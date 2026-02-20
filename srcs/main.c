#include "lem_in.h"
#include "vector.h"
#include <stdio.h>

t_vector *read_term();

int	main()
{
	
	t_vector *nodes;

	nodes = read_term();

	for (unsigned int i = 0; i < nodes->size; i++)
	{
		printf("Node: %s  %i-%i\n", ((t_node *)nodes->array[i])->name, ((t_node *)nodes->array[i])->x, ((t_node *)nodes->array[i])->y);
	}
	vec_free(nodes);
	return (0);
}