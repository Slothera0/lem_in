#ifndef NODE_H
# define NODE_H

# include "../srcs/vector/vector.h"

typedef enum e_room_type
{
    START,
    END,
    NORMAL
}   t_room_type;

typedef struct s_node
{
    char        *name;
    t_vector    *links;
    int         x;
    int         y;
    t_room_type type;
    void        *door;
	struct s_node *parent;

}   t_node;

t_node  *get_start(t_vector *vector);
t_node  *get_node(t_vector *vector, char *name);
char    *get_node_name(t_node *node);
void	print_node(void *data);
void	reset_nodes(t_vector *nodes);

#endif