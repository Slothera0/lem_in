#include <stdio.h>
#include "vector.h"
#include "lem_in.h"
#include "libft.h"

int create_node(t_vector *nodes, char **args, t_room_type type)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (-1);
	
	if (ft_strchr(args[0], '-'))
	{
		free(new);
		return (-2);
	}
	new->name = ft_strdup(args[0]);

	new->x = ft_atoi(args[1]);
	new->y = ft_atoi(args[2]);
	new->type = type;

	vec_append(nodes, new);

	return (0);
}