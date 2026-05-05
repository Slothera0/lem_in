#include "../../includes/distrib_ants.h"
#include "../../includes/lem_in.h"
#include "../../srcs/vector/vector.h"
#include <limits.h>
#include <stdlib.h>

t_distrib_ants *distrib_ants(t_lem_in *data, t_vector *all_path)
{
	t_distrib_ants	*distrib;
	unsigned int	*count;
	unsigned int	best_cost;
	unsigned int	cost_path;
	unsigned int	index_path;
	t_vector		*path;

	if (all_path->size == 0)
	  return (NULL);
	distrib = malloc(sizeof(t_distrib_ants) * data->nb_ants);
	if (!distrib)
		return (NULL);
	count = calloc(all_path->size, sizeof(unsigned int));
	if (!count)
	{
		free(distrib);
		return (NULL);
	}
	for (unsigned int ant = 0; ant < data->nb_ants; ant++)
	{
		best_cost = UINT_MAX;
		index_path = 0;
		for (unsigned int i = 0; i < all_path->size; i++)
		{
			path = (t_vector *)all_path->array[i];
			cost_path = path->size + count[i];
			if (cost_path < best_cost)
			{
				best_cost = cost_path;
				index_path = i;
			}
		}
		count[index_path]++;
		distrib[ant].ants_id = ant + 1;
		distrib[ant].path_index = index_path;
		distrib[ant].path = (t_vector *)all_path->array[index_path];
		distrib[ant].arrived = 0;
		distrib[ant].path_step = 0;
	}
	free(count);
	return (distrib);
}