#ifndef LEM_IN_H
# define LEM_IN_H

# include "vector.h"

typedef struct s_lem_in
{
    unsigned int    nb_ants;
    t_vector        *node;
    t_vector        *map;
}   t_lem_in;

#endif
