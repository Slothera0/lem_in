#include "flow.h"
#include "lem_in.h"
#include <limits.h>


void reset_fnodes(t_vector *graph);
int rebuilt_path(t_door *start_door, t_door *end_door, t_vector **path);
int has_positive_flow_path(t_door *start_door);

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


static t_vector *bfs_flow(t_door *start_door, t_door *end_door, unsigned int *head)
{
    t_vector *queue;
    t_vector *tmp;
    t_fnode *current;
    t_edge *edge;

    *head = 0;
    queue = vec_create(10);
    if(!queue)
        return (NULL);
    start_door->out->visited = 1;
    tmp = vec_append(queue, start_door->out);
    if(!tmp)
    {
        vec_free(queue);
        return (NULL);
    }
    queue = tmp;

    while(queue->size > *head)
    {
        current = (t_fnode *)queue->array[*head];
        (*head)++;
        if(current == end_door->in)
            return (queue);
        for (unsigned int i = 0; i < current->edges->size; i++)
        {
            edge = (t_edge *)current->edges->array[i];
            if (edge->cap > edge->flow && edge->to->visited == 0)
            {
                edge->to->visited = 1;
                edge->to->parent_edge = edge;
                tmp = vec_append(queue, edge->to);
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

t_vector *bfs(t_lem_in *data)
{
    t_door *start_door;
    t_door *end_door;
    t_vector *graph;
    t_vector *queue;
    t_vector *paths;
    t_vector *path;
    t_fnode *current;
    t_edge *edge;
    t_vector *tmp;
    unsigned int head;
    unsigned int path_good;
    unsigned int nb_paths_found;

    nb_paths_found = 0;
    start_door = NULL;
    end_door = NULL;
    graph = build_flow_graph(data, &start_door,&end_door);
    if (!graph)
        return (NULL);
    paths = vec_create(10);
    if (!paths)
    {
        free_all(graph);
        return(NULL);
    }
    while(1)
    {
        reset_fnodes(graph);
        queue  = bfs_flow(start_door, end_door, &head);
        if(!queue)
            break;
        nb_paths_found++;
        if (nb_paths_found * (nb_paths_found + 1) > data->nb_ants * 4)
        {
            vec_free(queue);
            break;
        }
        vec_free(queue);
        current = end_door->in;
        while (current != start_door->out)
        {
            edge = current->parent_edge;
            edge->flow += 1;
            edge->rev->flow -= 1;
            current = edge->rev->to;
        }
    }
    edge = (t_edge *)start_door->out->edges->array[0];
    while(has_positive_flow_path(start_door))
    {
        path = vec_create(10);
        if(!path)
        {
            free_all(graph);
            return (NULL);
        }
        if (rebuilt_path(start_door, end_door, &path) == 0)
        {
            vec_free(path);
            vec_iter(paths,vec_free);
            vec_free(paths);
            free_all(graph);
            return (NULL);
        }
        tmp = vec_append(paths, path);
        if(!tmp)
        {
            vec_free(path);
            vec_iter(paths,vec_free);
            vec_free(paths);
            free_all(graph);
            return (NULL);
        }
        paths = tmp;
    }
    sort_path_by_size(paths);
    path_good = best_k_path(paths, data->nb_ants);
    remove_path_usless(paths, path_good);
    free_all(graph);
    return paths;
}

t_edge *find_positive_flow_edge(t_fnode *current)
{
    t_edge *edge;

    for(unsigned int i = 0; i < current->edges->size; i++)
    {
        edge = (t_edge *)current->edges->array[i];
        if (edge->flow > 0)
            return (edge);
    }
    return (NULL);
}

int has_positive_flow_path(t_door *start_door)
{
    t_fnode *current;
    t_edge  *edge;

    current = start_door->out;
    while (current)
    {
        edge = find_positive_flow_edge(current);
        if (!edge)
            return (0);
        if (edge->to->room && edge->to->room->type == END)
            return (1);
        current = edge->to;
    }
    return (0);
}

int rebuilt_path(t_door *start_door, t_door *end_door, t_vector **path)
{
    t_fnode *current;
    t_edge *edge;
    t_vector *tmp;
    t_node *last_room;

    current = start_door->out;
    last_room = start_door->out->room;
    tmp = vec_append(*path, start_door->out->room);
    if (!tmp)
        return (0);
    *path = tmp;
    while (current != end_door->in)
    {
        edge = find_positive_flow_edge(current);
        if(!edge)
            return (0);
        edge->flow -= 1;
        current = edge->to;
        if (current->room != last_room)
        {
            tmp = vec_append(*path, current->room);
            if (!tmp)
                return (0);
            *path = tmp;
            last_room = current->room;
        }
    }
    return (1);
}

void reset_fnodes(t_vector *graph)
{
    t_door *doors;

    for (unsigned int i = 0; i < graph->size; i++)
    {
        doors = (t_door *)graph->array[i];
        if (!doors)
            continue;
        doors->in->visited = 0;
        doors->in->parent_edge = NULL;
        doors->out->visited = 0;
        doors->out->parent_edge = NULL;
    }
}