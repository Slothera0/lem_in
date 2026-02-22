#include "vector.h"
#include "node.h"
#include "libft.h"
#include "ft_error.h"

void	free_node(void *data);
t_node	*get_node(t_vector *vector, char *name);

int create_node(t_vector *nodes, char **args, t_room_type type)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (MALLOC_ERROR);
	
	new->links = vec_create(10);
	if (!new->links)
	{
		free(new);
		return (MALLOC_ERROR);
	}
	
	if (ft_strchr(args[0], '-') || get_node(nodes, args[0]))
	{
		free(new->links);
		free(new);
		return (PARSE_ERROR);
	}

	new->name = ft_strdup(args[0]);
	if (!new->name)
	{
		free(new->links);
		free(new);
		return (MALLOC_ERROR);
	}

	new->x = ft_atoi(args[1]);
	new->y = ft_atoi(args[2]);
	new->type = type;

	if (!vec_append(nodes, new))
		free_node(new);

	return (0);
}