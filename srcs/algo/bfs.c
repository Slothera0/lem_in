#include "../../includes/flow.h"
#include "../../includes/lem_in.h"


void reset_fnodes(t_vector *graph);

t_vector *bfs_flow(t_vector *doors, t_door *start_door, t_door *end_door)
{
    t_vector *queue;
    t_vector *tmp;
    t_fnode *current;
    t_edge *edge;
    unsigned int head;

    head = 0;
    queue = vec_create(10);
    if(!queue)
        return (NULL);
    start_door->out->visited = 1;
    tmp = vec_append(queue, start_door->out);
    if(!tmp)
    {
        free(queue);
        return (NULL);
    }
    queue = tmp;

    while(queue->size > head)
    {
        current = (t_fnode *)queue->array[head];
        head++;
        if(current == end_door->in)
        {
            return (queue);
        }
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
}

int bfs(t_lem_in *data)
{
    t_door *start_door;
    t_door *end_door;
    t_vector *graph;
    t_vector *path;
    t_fnode *current;
    t_edge *edge;

    graph = build_flow_graph(data, &start_door,&end_door);
    reset_fnodes(graph);
    while(bfs_flow(graph, start_door, end_door))
    {
        current = (t_fnode *)end_door;
        while (current != start_door->in)
        {
            edge = current->parent_edge;
            path = vec_append(path, edge);
            current = edge->rev->to;
        }
    }
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