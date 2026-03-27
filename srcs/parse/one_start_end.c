#include "vector.h"
#include "node.h"

int	one_start(t_vector *nodes)
{
	int 	count = 0;
	t_node	*node;

	for (unsigned int i = 0; i < nodes->size; i++)
	{
		node = nodes->array[i];
		if (node->type == START)
			count++;
	}

	if (count != 1)
		return (0);
	return (1);
}

int	one_end(t_vector *nodes)
{
	int 	count = 0;
	t_node	*node;

	for (unsigned int i = 0; i < nodes->size; i++)
	{
		node = nodes->array[i];
		if (node->type == END)
			count++;
	}

	if (count != 1)
		return (0);
	return (1);
}