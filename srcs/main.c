#include "../includes/node.h"
#include "../includes/lem_in.h"
#include "../srcs/vector/vector.h"
#include "../includes/distrib_ants.h"
#include <stdlib.h>

t_lem_in	*read_term();
void		free_node(void *data);
t_vector	*find_all_way(t_lem_in *data);
t_distrib_ants *distrib_ants(t_lem_in *data, t_vector *all_path);
int print_walk(t_distrib_ants *distrib, unsigned int assigned_ants);

void	print_node(void *data);
void	print_way(void *data);
t_node 	*get_start(t_vector *vector);
void print_all_path(t_vector *all_path);

int	main()
{
	
	t_lem_in *data;
	t_vector *nodes;
	t_vector *path;
	t_distrib_ants *distrib;

	data = read_term();

	nodes = data->node;

	//vec_iter(nodes, print_node);
	//print_node(get_start(nodes));

	path = find_all_way(data);
	if (!path)
    	return (1);
	distrib = distrib_ants(data, path);
	if (!distrib)
        return (1);
    print_walk(distrib, data->nb_ants);
	print_all_path(path);

	// vec_iter(all_way, vec_free);
	// vec_free(all_way);
	vec_iter(nodes, free_node);
	vec_free(nodes);
	free(data);
	return (0);
}