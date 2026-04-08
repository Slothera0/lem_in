#include "../../includes/lem_in.h"
#include "../../includes/node.h"
#include "../../srcs/vector/vector.h"
#include "../../includes/ft_error.h"
#include <limits.h>
#include <stdio.h>

void reverse_path(t_vector *path);
t_vector *rebuild_path(t_node *current);
void	reset_nodes(t_vector *nodes);
t_vector *find_shortest_path(t_node *start);
void block_path(t_vector *path);
void sort_path_by_size(t_vector *all_path);
unsigned int best_k_path(t_vector *all_path, unsigned int nb_ants);
void remove_path_usless(t_vector *all_path, unsigned int k);

t_vector	*find_all_way(t_lem_in *data)
{
	t_node *start;
	t_vector *path;
	t_vector *all_path;
	t_vector *tmp;
	unsigned int nb_path;
	unsigned int k;

	nb_path = 5;
	if (data->nb_ants > 50)
		nb_path = data->nb_ants / 10;
	all_path = vec_create(10);
	if (!all_path)
		return (NULL);
	start = get_start(data->node);
	if (!start)
	{
		vec_free(all_path);
		return (NULL);
	}

	while(all_path->size < nb_path)
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
	sort_path_by_size(all_path);
	k = 0;
	k = best_k_path(all_path, data->nb_ants);
	remove_path_usless(all_path, k);

	return (all_path);
}

void remove_path_usless(t_vector *all_path, unsigned int k)
{
	t_vector *path;

	if (!all_path)
		return;
	if (k >= all_path->size)
		return;
	while (all_path->size > k)
	{
		path = (t_vector *)all_path->array[all_path->size - 1];
		vec_free(path);
		all_path->size = all_path->size - 1;
	}
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

void sort_path_by_size(t_vector *all_path)
{
	t_vector *a;
	t_vector *b;
	void *tmp;

	for (unsigned int i = 0; i < all_path->size; i++)
	{
		for (unsigned int j = i + 1; j < all_path->size; j++)
		{
			a = (t_vector *)all_path->array[i];
			b = (t_vector *)all_path->array[j];
			if (a->size > b->size)
			{
				tmp = all_path->array[i];
				all_path->array[i] = all_path->array[j];
				all_path->array[j] = tmp;
			}
		}
	}
}

unsigned int score_k_path(t_vector *all_path, unsigned int k, unsigned int nb_ants)
{
	unsigned int score;
	unsigned int size_path;
	unsigned int best_score;
	unsigned int *ants;
	unsigned int best_y;
	unsigned int max_turn;
	t_vector *tmp;

	if (!all_path || k == 0 || k > all_path->size)
		return(UINT_MAX);
	ants = calloc(k, sizeof(unsigned int));
	if (!ants)
		return (UINT_MAX);
	for (unsigned int i = 0; i < nb_ants; i++)
	{
		score = 0;
		best_score = UINT_MAX;
		for (unsigned int y = 0; y < k; y++)
		{
			tmp = all_path->array[y];
			size_path = tmp->size;
			score = (size_path - 1) + ants[y];
			if (score < best_score)
			{
				best_score = score;
				best_y = y;
			}
		}
		ants[best_y]++;
	}

	max_turn = 0;
	for (unsigned int i = 0; i < k; i++)
	{
		tmp = all_path->array[i];
		if (ants[i] > 0)
		{
			score = (tmp->size - 1) + ants[i] - 1;
			if (score > max_turn)
				max_turn = score;
		}
	}
	free(ants);
	return (max_turn);

}

unsigned int best_k_path(t_vector *all_path, unsigned int nb_ants)
{
	unsigned int best_score;
	unsigned int score;
	unsigned int best_path;
	
	if (!all_path || all_path->size == 0)
		return (0);
	best_score = UINT_MAX;
	best_path = 1;
	for (unsigned int i = 1; i <= all_path->size; i++)
	{
		score  = score_k_path(all_path, i, nb_ants);
		if (score < best_score)
		{
			best_score = score;
			best_path = i;
		}
	}
	return best_path;
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
