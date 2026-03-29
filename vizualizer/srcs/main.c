#include "rend.h"
#include "lem_in.h"
#include "node.h"
#include "vector.h"

t_lem_in	*read_term();
float		normalize_coord(t_vector *nodes);

int init_window(t_rend *rend_adr);
int start_rend(t_rend rend, t_lem_in *data);

int main()
{
	t_lem_in *data;
	t_vector *nodes;

	data = read_term();

	nodes = data->node;

	normalize_coord(nodes);
	
	t_rend rend;

	if (init_window(&rend) != 0)
	{
		return (1);
	}
	if (start_rend(rend, data) != 0)
	{
		return (1);
	}

	vec_iter(nodes, free_node);
	vec_free(nodes);
	free(data);
	return (0);
}