#include "flow.h"
#include <limits.h>

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
            if (size_path == 2)
            {
                free(ants);
                return 1;
            }

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