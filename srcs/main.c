#include "lem_in.h"
#include "vector.h"
#include <stdio.h>

t_vector	*read_term();
void		print_node(void *data);
void		free_node(void *data);

int	main()
{
	
	t_vector *nodes;

	nodes = read_term();

	vec_iter(nodes, print_node);
	vec_iter(nodes, free_node);
	vec_free(nodes);
	return (0);
}