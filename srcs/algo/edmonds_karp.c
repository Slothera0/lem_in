#include "../../includes/flow.h"
#include "../../includes/lem_in.h"

t_vector *edmonds_karp(t_lem_in *data)
{
    t_door *start_door;
    t_door *end_door;
    t_vector *graph;
    t_vector *queue;
    t_vector *paths;
    t_edge *edge;
    t_fnode *current;
    unsigned int head;
    unsigned int nb_paths_found;

    nb_paths_found = 0;
    start_door = NULL;
    end_door = NULL;
    graph = build_flow_graph(data, &start_door,&end_door);
    if (!graph)
        return (NULL);
    edge = (t_edge *)start_door->out->edges->array[0];

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
    paths = get_path(graph,start_door,end_door,data->nb_ants);
    return paths;
}