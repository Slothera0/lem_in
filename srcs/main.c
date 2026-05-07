#include "../includes/node.h"
#include "../includes/lem_in.h"
#include "../includes/flow.h"
#include "../libs/vector/vector.h"
#include "../includes/distrib_ants.h"
#include <stdlib.h>

t_lem_in	*read_term();
void		free_node(void *data);
t_distrib_ants *distrib_ants(t_lem_in *data, t_vector *all_path);
int print_walk(t_distrib_ants *distrib, unsigned int assigned_ants);

void	print_node(void *data);
void	print_way(void *data);
t_node 	*get_start(t_vector *vector);
void print_all_path(t_vector *all_path);
void free_distrib_ants(void *data);

int	main()
{
	
	t_lem_in *data;
	t_vector *nodes;
	t_vector *path;
	t_distrib_ants *distrib;

	data = read_term();

	nodes = data->node;

	path = edmonds_karp(data);
	if (!path)
	{
		vec_iter(nodes, free_node);
		vec_free(nodes);
		free(data);
		return (1);
	}
	distrib = distrib_ants(data, path);
	if (!distrib)
	{
		vec_iter(path, vec_free);
		vec_free(path);
		vec_iter(nodes, free_node);
		vec_free(nodes);
		free(data);
		return (1);
	}
	print_walk(distrib, data->nb_ants);

	free(distrib);
	vec_iter(path, vec_free);
	vec_free(path);
	vec_iter(nodes, free_node);
	vec_free(nodes);
	free(data);
	return (0);
}