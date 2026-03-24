#include "../../includes/lem_in.h"
#include "../../includes/node.h"
#include "../../srcs/vector/vector.h"
#include "../../includes/ft_error.h"
#include <stdio.h>

void reverse_path(t_vector *path);
t_vector *rebuild_path(t_node *current);
void	reset_nodes(t_vector *nodes);
t_vector *find_shortest_path(t_node *start);
void block_path(t_vector *path);

t_vector	*find_all_way(t_lem_in *data)
{
	t_node *start;
	t_vector *path;
	t_vector *all_path;
	unsigned int i;

	i = 0;
	all_path = vec_create(10);
	path = vec_create(10);

	start = get_start(data->node);
	if (!start)
		ft_error(1);

	while(i < 5)
	{
		printf("%u \n",i);
		reset_nodes(data->node);
		start->visited = 1;
		start->parent = NULL;
		path = find_shortest_path(start);
		if (!path)
			break;
		all_path = vec_append(all_path, path);
		block_path(path);
		reset_nodes(path);
		i++;
	}
	return (all_path);
}

t_vector *find_shortest_path(t_node *start)
{
	t_node *child;
	t_vector *queue;
	t_node *current;
	unsigned int head;

	head = 0;
	queue = vec_create(10);
	queue = vec_append(queue, start);

	while (head < queue->size)
	{
		current = (t_node *)queue->array[head];
		head++;
		if (current->type == END)
		{
			vec_free(queue);
			return (rebuild_path(current));
		}
		for (unsigned int i = 0; i < current->links->size; i++)
		{
			
			child = (t_node *)current->links->array[i];
			if (!child->visited && !child->blocked)
			{
				child->visited = 1;
				child->parent = current;
				queue = vec_append(queue, child);
				if (!queue)
					return (NULL);
			}
		}
	}
	return (NULL);
}

t_vector *rebuild_path(t_node *current)
{
	t_vector *path;

	path = vec_create(10);
	if (!path)
		return (NULL);
	while (current)
	{
		path = vec_append(path, current);
		if (!path)
			return (NULL);
		current = current->parent;
	}
	reverse_path(path);
	return (path);
}

void reverse_path(t_vector *path)
{
	void *tmp;
	unsigned int i;
	unsigned int j;

	i = 0;
	j = path->size-1;
	while (i < j)
	{
		tmp = path->array[i];
		path->array[i] = path->array[j];
		path->array[j] = tmp;
		i++;
		j--;
	}

}
