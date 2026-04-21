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
