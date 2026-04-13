#include "rend.h"
#include "lem_in.h"
#include "node.h"
#include "vector.h"


#include <stdio.h>

t_lem_in	*read_term();
float		normalize_coord(t_vector *nodes);
t_vector	*read_ants_path();
t_ant		*create_ant(int ants_nb, float x, float y);

int init_window(t_rend *rend_adr);
int start_rend(t_rend rend, t_lem_in *data);

int main()
{
	t_lem_in *data;
	t_vector *nodes;

	data = read_term();

	nodes = data->node;

	t_rend rend;

	rend.nodes = nodes;

	rend.ant_paths = read_ants_path();
	if (!rend.ant_paths)
	{
		vec_iter(nodes, free_node);
		vec_free(nodes);
		free(data);
		perror("ERROR");
		exit(1);
	}

	rend.scale = 1 / normalize_coord(nodes);
	t_node *start_node = get_start(nodes);
	rend.ants = create_ant(data->nb_ants, start_node->x, start_node->y);
	if (!rend.ants)
	{
		vec_iter(nodes, free_node);
		vec_free(nodes);
		free(data);
		vec_iter(rend.ant_paths, vec_free);
		vec_free(rend.ant_paths);
		perror("ERROR");
		return (1);
	}

	if (init_window(&rend) != 0)
	{
		vec_iter(nodes, free_node);
		vec_free(nodes);
		free(data);
		vec_iter(rend.ant_paths, vec_free);
		vec_free(rend.ant_paths);
		free(rend.ants);
		perror("ERROR");
		return (1);
	}
	if (start_rend(rend, data) != 0)
	{
		vec_iter(nodes, free_node);
		vec_free(nodes);
		free(data);
		vec_iter(rend.ant_paths, vec_free);
		vec_free(rend.ant_paths);
		free(rend.ants);
		perror("ERROR");
		return (1);
	}

	vec_iter(nodes, free_node);
	vec_free(nodes);
	free(data);
	vec_iter(rend.ant_paths, vec_free);
	vec_free(rend.ant_paths);
	free(rend.ants);
	return (0);
}