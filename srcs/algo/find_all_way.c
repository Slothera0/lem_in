#include "lem_in.h"
#include "node.h"
#include "vector.h"

void	find_all_way(t_lem_in *data)
{
	t_vector	*all_way;
	t_node		*start;

	all_way = vec_create(10);
	if (!all_way)
		error();
	
	start = get_start(data->node);

	rec_find_all_way(start, all_way);
}