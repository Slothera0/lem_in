#include "lem_in.h"
#include "node.h"
#include "vector.h"
#include <errno.h>

#include <stdio.h>

char	*get_node_name(t_node *node);
t_node 	*get_node(t_vector *vector, char *name);
t_node 	*get_start(t_vector *vector);
int		ft_error(int statut);

static void		rec_find_all_way(t_vector *current);
static t_vector *get_unique_links(t_vector *way, t_vector *links);

static t_vector	*all_way;

t_vector	*find_all_way(t_lem_in *data)
{
	t_vector	*way;
	t_node		*start;

	all_way = vec_create(10);
	if (!all_way)
		ft_error(1);
	
	start = get_start(data->node);
	if (!start)
		ft_error(1);
	way = vec_create(10);
	if (!way)
		ft_error(1);

	vec_append(way, start);
	vec_append(all_way, way);
	rec_find_all_way(way);

	return (all_way);
}

static void	rec_find_all_way(t_vector *current)
{
	t_node		*current_node;
	t_vector	*new_way;
	t_vector	*unique_links;

	printf("Depth: %u, all_way size: %u\n", current->size, all_way->size);
	current_node = vec_end(current);
	
	if (current_node->type == END)
		return ;
	
	unique_links = get_unique_links(current, current_node->links);
	if (!unique_links)
		ft_error(1);
	
	if (unique_links->size <= 0)
	{
		vec_remove(all_way, current);
		vec_free(current);
		vec_free(unique_links);
		return ;
	}

	for (unsigned int i = 1; i < unique_links->size; i++)
	{
		new_way = vec_create(current->size + 1);
		if (!new_way)
			ft_error(1);
		
		vec_copy(current, new_way);

		new_way = vec_append(new_way, unique_links->array[i]);
		if (!new_way)
			ft_error(1);
		
		all_way = vec_append(all_way, new_way);
		if (!all_way)
			ft_error(1);
		
		rec_find_all_way(new_way);
	}

	vec_remove(all_way, current);
	current = vec_append(current, unique_links->array[0]);
	if (!current)
		ft_error(1);

	all_way = vec_append(all_way, current);
	if (!all_way)
		ft_error(1);
	
	vec_free(unique_links);
	rec_find_all_way(current);
}

static t_vector *get_unique_links(t_vector *way, t_vector *links)
{
	t_vector	*unique_links;

	unique_links = vec_create(links->size);
	if (!unique_links)
		ft_error(1);

	for (unsigned int i = 0; i < links->size; i++)
	{
		if (!get_node(way, get_node_name(links->array[i])))
		{
			unique_links = vec_append(unique_links, links->array[i]);
			if (!unique_links)
				ft_error(1);
		}
	}

	return (unique_links);
}
