#include "../../includes/distrib_ants.h"
#include "../../includes/lem_in.h"
#include "../../srcs/vector/vector.h"
#include <limits.h>
#include <stdlib.h>

unsigned int get_ants_path(t_distrib_ants *distrib, unsigned int assigned_ants, unsigned int index_path); 

t_distrib_ants *distrib_ants(t_lem_in *data, t_vector *all_path) {

  t_distrib_ants *distrib;
  unsigned int best_cost;
  unsigned int cost_path;
  unsigned int index_path;
  t_vector *path;

  cost_path = 0;
  distrib = malloc(sizeof(t_distrib_ants) * data->nb_ants);
  if (!distrib)
    return (NULL);
  for (unsigned int ant = 0; ant < data->nb_ants; ant++) {
    best_cost = INT_MAX;
    index_path = 0;
    for (unsigned int i = 0; i < all_path->size; i++) {
        path = (t_vector *)all_path->array[i];
        cost_path = path->size + get_ants_path(distrib, ant, i);
        if (cost_path < best_cost)
        {
            best_cost = cost_path;
            index_path = (int)i;
        }
    }
    distrib[ant].ants_id = ant + 1;
    distrib[ant].path_index = index_path;
    distrib[ant].path = (t_vector *)all_path->array[index_path];
    distrib[ant].arrived = 0;
    distrib[ant].path_step = 0;
  }
  return distrib;
}

unsigned int get_ants_path(t_distrib_ants *distrib, unsigned int assigned_ants, unsigned int index_path) {
  unsigned int nb_ants;

  nb_ants = 0;
  for (unsigned int i = 0; i < assigned_ants; i++) {
    if (distrib[i].path_index == index_path)
        nb_ants++;
  }
  return nb_ants;
}