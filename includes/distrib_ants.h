#ifndef DISTRIB_ANTS_H
# define DISTRIB_ANTS_H

# include "../libs/vector/vector.h"

typedef struct s_distrib_ants
{
    unsigned int ants_id;
    t_vector *path;
    unsigned int path_index;
    unsigned int arrived;
    unsigned int path_step;
    unsigned int nb_ants;
} t_distrib_ants;

#endif