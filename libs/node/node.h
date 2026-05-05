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
	float 			x;
	float 			y;
	t_room_type 	type;
	int				visited;
} t_node ;

t_node		*get_node(t_vector *vector, char *name);
int 		create_link(t_vector *nodes, char *args);
void		free_node(void *data);
t_vector	*create_node(t_vector *nodes, char **args, t_room_type type);
void		free_node(void *data);
char 		*get_node_name(t_node *node);
t_room_type get_node_type(t_node *node);
t_node		*get_start(t_vector *vector);
void		print_node(void *data);
float		get_x(t_node *node);
float		get_y(t_node *node);
float		get_minX_coord(t_vector *nodes);
float		get_maxX_coord(t_vector *nodes);
float		get_minY_coord(t_vector *nodes);
float		get_maxY_coord(t_vector *nodes);
void		sort_nodes(t_vector *vec);

#endif