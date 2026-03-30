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
	t_vector *tmp;

	all_path = vec_create(10);
	if (!all_path)
		return (NULL);
	start = get_start(data->node);
	if (!start)
	{
		vec_free(all_path);
		return (NULL);
	}

	while(1)
	{
		reset_nodes(data->node);
		start->visited = 1;
		start->parent = NULL;
		path = find_shortest_path(start);
		if (!path)
			break;
		tmp = vec_append(all_path, path);
        if (!tmp)
        {
            vec_free(path);
            vec_free(all_path);
            return (NULL);
        }
        all_path = tmp;
		block_path(path);
	}
	return (all_path);
}

t_vector *find_shortest_path(t_node *start)
{
	t_node *child;
	t_vector *queue;
	t_vector *tmp;
	t_node *current;
	unsigned int head;

	head = 0;
	queue = vec_create(10);
	if (!queue)
		return (NULL);
	tmp = vec_append(queue, start);
	if (!tmp)
	{
		vec_free(queue);
		return (NULL);
	}
	queue = tmp;
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
				tmp = vec_append(queue, child);
				if (!tmp)
				{
					vec_free(queue);
					return (NULL);
				}
				queue = tmp;
			}
		}
	}
	vec_free(queue);
	return (NULL);
}

t_vector *rebuild_path(t_node *current)
{
	t_vector *path;
	t_vector *tmp;

	path = vec_create(10);
	if (!path)
		return (NULL);
	while (current)
	{
		tmp = vec_append(path, current);
		if (!tmp)
		{
			vec_free(path);
			return (NULL);
		}
		path = tmp;
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
	if (!path || path->size < 2)
		return;
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
