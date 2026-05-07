#include "vector.h"
#include "node.h"
#include "libft.h"
#include <errno.h>

t_vector *create_node(t_vector *nodes, char **args, t_room_type type)
{
	t_node	*new;

	if ((ft_sstrlen(args) != 3 || get_node(nodes, args[0])) || (ft_strchr(args[0], '-') || args[0][0] == 'L'))
	{
		errno = PARSE_ERROR;
		return (nodes);
	}

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	
	new->links = vec_create(10);
	if (!new->links)
	{
		free(new);
		return (NULL);
	}

	new->name = ft_strdup(args[0]);
	if (!new->name)
	{
		vec_free(new->links);
		free(new);
		return (NULL);
	}

	if (!is_a_num(args[1]) || !is_a_num(args[2]))
	{
		errno = PARSE_ERROR;
		free_node(new);
		return (nodes);
	}

	new->x = ft_atoi(args[1]);
	new->y = ft_atoi(args[2]);
	new->type = type;
	new->visited = 0;

	nodes = vec_append(nodes, new);
	if (!nodes)	
		free_node(new);

	return (nodes);
}