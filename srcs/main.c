#include "node.h"
#include "lem_in.h"
#include "flow.h"
#include "vector.h"
#include "distrib_ants.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

t_lem_in		*read_term();
t_distrib_ants	*distrib_ants(t_lem_in *data, t_vector *all_path);
int				print_walk(t_distrib_ants *distrib, unsigned int assigned_ants);
void 			free_all(t_lem_in *data, t_vector *nodes, t_vector *path, t_distrib_ants *distrib);

void	print_way(void *data);
void	print_all_path(t_vector *all_path);

int	main()
{
	
	t_lem_in *data;
	t_vector *nodes;
	t_vector *path;
	t_distrib_ants *distrib;

	distrib = NULL;
	data = read_term();

	nodes = data->node;

	path = edmonds_karp(data);
	if (!path)
	{
		ft_putstr_fd("ERROR\n", 2);
		free_all(data, nodes, path, distrib);
		return (1);
	}
	distrib = distrib_ants(data, path);
	if (!distrib)
	{
		ft_putstr_fd("ERROR\n", 2);
		free_all(data, nodes, path, distrib);
		return (1);
	}
	ft_printf("%d\n", data->nb_ants);
	vec_iter(data->map, ft_put_vecstr);
	ft_printf("\n");

	print_walk(distrib, data->nb_ants);
	free_all(data, nodes, path, distrib);
	return (0);
}
