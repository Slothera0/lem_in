#include "lem_in.h"
#include "vector.h"

void	free_node(void *data)
{
	t_node *node = (t_node *)data;

	vec_free(node->links);
	free(node->name);
	free(node);
}