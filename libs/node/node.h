#ifndef NODE_H
# define NODE_H

#include "vector.h"

#ifndef T_ERROR
# define T_ERROR
typedef enum e_error
{
	MALLOC_ERROR = -1,
	PARSE_ERROR = -2,
} t_error ;
#endif

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