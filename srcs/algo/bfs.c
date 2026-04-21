#include "../../includes/flow.h"
#include "../../includes/lem_in.h"


void reset_fnodes(t_vector *graph);
int rebuilt_path(t_door *start_door, t_door *end_door, t_vector *path);
int has_positive_flow_path(t_door *start_door);

static t_vector *bfs_flow(t_door *start_door, t_door *end_door)
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

    graph = build_flow_graph(data, &start_door,&end_door);
    paths = vec_create(10);
    while(1)
    {
        reset_fnodes(graph);
        queue  = bfs_flow(start_door, end_door);
        if(!queue)
            break;
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
        rebuilt_path(start_door, end_door, path);
        paths = vec_append(paths, path);
    }
    return paths;
}

t_edge *find_positive_flow_edge(t_fnode *current)
{
    t_edge *edge;

    for( unsigned int i = 0; i < current->edges->size; i++ )
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

int rebuilt_path(t_door *start_door, t_door *end_door, t_vector *path)
{
    t_fnode *current;
    t_edge *edge;
    t_vector *tmp;
    t_node *last_room;

    current = start_door->out;
    last_room = start_door->out->room;
    tmp = vec_append(path, start_door->out->room);
    if (!tmp)
        return (0);
    path = tmp;
    while (current != end_door->in)
    {
        edge = find_positive_flow_edge(current);
        if(!edge)
            return (0);
        edge->flow -= 1;
        current = edge->to;
        if (current->room != last_room)
        {
            tmp = vec_append(path, current->room);
            if (!tmp)
                return (0);
            path = tmp;
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