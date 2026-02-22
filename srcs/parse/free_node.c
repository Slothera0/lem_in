#include "lem_in.h"

void	free_node(t_node *node)
{
	free(node->links);
	free(node->name);
	free(node);
}