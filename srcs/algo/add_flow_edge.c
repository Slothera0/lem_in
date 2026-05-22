#include "flow.h"
#include "lem_in.h"

void link_edges(t_lem_in *data, t_door **start_door, t_door **end_door);

void add_flow_edge(t_fnode *from, t_fnode *to, int cap)
{
    t_edge *forward;
    t_edge *reverse;
    t_vector *tmp;
 
    forward = malloc(sizeof(t_edge));
    if (!forward)
        return ;
    reverse = malloc(sizeof(t_edge));
    if (!reverse)
    {
        free(forward);
        return ;
    }

    forward->to = to;
    forward->cap = cap;
    forward->flow = 0;
    forward->rev = reverse;

    reverse->to = from;
    reverse->cap = 0;
    reverse->flow = 0;
    reverse->rev = forward;

    tmp = vec_append(from->edges, forward);
    if (!tmp)
    {
        free_edge(forward);
        free_edge(reverse);
        return ;
    }
    from->edges = tmp;
    tmp = vec_append(to->edges, reverse);
    if (!tmp)
    {
        free_edge(reverse);
        return ;
    }
    to->edges = tmp;

}

t_vector *build_flow_graph(t_lem_in *data, t_door **start_door, t_door **end_door)
{
    t_vector *graph;
    t_vector *tmp;
    t_door *doorA;
    t_node *node;

    graph = vec_create(data->node->size);
    if (!graph)
        return (NULL);
    for (unsigned int i = 0; i < data->node->size; i++)
    {
        node = (t_node *) data->node->array[i];
        if (!node)
            continue;
        doorA = create_door(node);
        if (!doorA)
            continue;
        node->door = doorA;
        tmp = vec_append(graph, doorA);
        if (!tmp)
        {
            free_door(doorA);
            free_flow_graph(graph);
            return (NULL);
        }
        graph = tmp;
    }
    link_edges(data, start_door, end_door);
    return (graph);
}

void link_edges(t_lem_in *data, t_door **start_door, t_door **end_door)
{
    t_door *doorA;
    t_door *doorB;
    t_node *node;
    t_node *node_link;

    for (unsigned int i = 0; i < data->node->size; i++)
    {
        node = (t_node *) data->node->array[i];
        if (!node)
            continue;
        if (node->type == START)
            *start_door = node->door;
        if (node->type == END)
            *end_door = node->door;
        doorA = node->door;
        
        for (unsigned int y = 0; y < node->links->size; y++)
        {
            node_link = (t_node *)node->links->array[y];
            if(!node_link)
                continue;
            doorB = node_link->door;
            if (!doorB)
                continue;
            add_flow_edge(doorA->out, doorB->in, 1);
        }
    }
}