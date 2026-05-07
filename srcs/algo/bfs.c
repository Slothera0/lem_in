#include "../../includes/flow.h"
#include "../../includes/lem_in.h"

t_vector *bfs_flow(t_door *start_door, t_door *end_door, unsigned int *head)
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
    paths = vec_create(graph->size);
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