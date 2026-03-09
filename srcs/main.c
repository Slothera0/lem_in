#include "node.h"
#include "vector.h"
#include "lem_in.h"
#include <stdio.h>
#include <errno.h>

t_lem_in	*read_term();
void		free_node(void *data);

void	print_node(void *data);
t_node 	*get_start(t_vector *vector);

int	main()
{
	
	t_lem_in *data;
	t_vector *nodes;

	data = read_term();

	nodes = data->node;
	vec_iter(nodes, print_node);
	print_node(get_start(nodes));

	vec_iter(nodes, free_node);
	vec_free(nodes);
	free(data);
	return (0);
}