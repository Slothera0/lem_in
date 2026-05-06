#include "node.h"
#include "lem_in.h"
#include "flow.h"
#include "vector.h"
#include "distrib_ants.h"
#include <stdlib.h>

t_lem_in		*read_term();
t_distrib_ants	*distrib_ants(t_lem_in *data, t_vector *all_path);
int				print_walk(t_distrib_ants *distrib, unsigned int assigned_ants);

void	print_way(void *data);
void	print_all_path(t_vector *all_path);

int	main()
{
	
	t_lem_in *data;
	t_vector *nodes;
	t_vector *path;
	t_distrib_ants *distrib;

	data = read_term();

	nodes = data->node;

	path = bfs(data);
	if (!path)
    	return (1);
	distrib = distrib_ants(data, path);
	if (!distrib)
		return (1);
	vec_iter(data->map, ft_put_vecstr);
	print_walk(distrib, data->nb_ants);

	free(distrib);
	vec_iter(path, vec_free);
	vec_free(path);
	vec_iter(nodes, free_node);
	vec_free(nodes);
	vec_iter(data->map, free);
	vec_free(data->map);
	free(data);
	return (0);
}
