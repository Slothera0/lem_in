#include "rend.h"
#include "lem_in.h"
#include "node.h"
#include "vector.h"
#include "libft.h"
#include <errno.h>

#include <stdio.h>

t_lem_in	*read_term();
float		normalize_coord(t_vector *nodes);
t_vector	*read_ants_path(t_vector *nodes);
t_ant		*create_ant(int ants_nb, float x, float y);

int init_window(t_rend *rend_adr);
int start_rend(t_rend rend, t_lem_in *data);

void free_path(void *data);

int main()
{
	t_lem_in *data;
	t_vector *nodes;

	data = read_term();

	nodes = data->node;

	t_rend rend;

	rend.nodes = nodes;

	errno = 0;
	rend.ant_paths = read_ants_path(nodes);
	if (!rend.ant_paths)
	{
		vec_iter(nodes, free_node);
		vec_free(nodes);
		free(data);
		if (errno > 0)
			perror("ERROR");
		else
			ft_putstr_fd("ERROR\n", 2);
		exit(1);
	}

	rend.scale = 1 / normalize_coord(nodes);
	if (rend.scale > 0.1f)
		rend.scale = 0.1f;

	t_node *start_node = get_start(nodes);
	start_node->visited = 1;
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
		for(unsigned int i = 0; i < rend.ant_paths->size; i++)
		{
			vec_iter(rend.ant_paths->array[i], free_path);
		}
		vec_iter(rend.ant_paths, vec_free);
		vec_free(rend.ant_paths);
		free(rend.ants);
		perror("ERROR");
		return (1);
	}

	vec_iter(nodes, free_node);
	vec_free(nodes);
	free(data);
	for(unsigned int i = 0; i < rend.ant_paths->size; i++)
	{
		vec_iter(rend.ant_paths->array[i], free_path);
	}
	vec_iter(rend.ant_paths, vec_free);
	vec_free(rend.ant_paths);
	free(rend.ants);
	return (0);
}