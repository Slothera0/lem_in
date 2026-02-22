#ifndef LEM_IN_H
# define LEM_IN_H

#include "vector.h"

typedef enum e_room_type {
    START,
    END,
    NORMAL
}   t_room_type;


typedef struct s_node
{
	char 			*name;
	t_vector 		*links;
	int 			x;
	int 			y;
	t_room_type 	type;
} t_node ;



#endif