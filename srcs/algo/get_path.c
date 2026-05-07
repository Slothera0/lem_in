#include "../../includes/flow.h"

t_vector *get_path(t_vector *graph, t_door *start_door, t_door *end_door, unsigned int nb_ants)
{
    t_vector *paths;
    t_vector *path;
    t_vector *tmp;
    unsigned int path_good;
    
    paths = vec_create(graph->size);
    if (!paths)
    {
        free_all(graph);
        return(NULL);
    }

    while(has_positive_flow_path(start_door))
    {
        path = vec_create(10);
        if(!path)
        {
            vec_iter(paths,vec_free);
            vec_free(paths);
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
    path_good = best_k_path(paths, nb_ants);
    remove_path_usless(paths, path_good);
    free_all(graph);
    return paths;
}