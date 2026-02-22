#include <stdio.h>
#include "vector.h"
#include "lem_in.h"
#include "libft.h"
#include "ft_error.h"

t_node *get_node(t_vector *vector, char *name);

int create_link(t_vector *nodes, char *args)
{
	char **split = ft_split(args, '-');

	if (ft_sstrlen(split) != 2)
	{
		ft_free_array(split);
		return (PARSE_ERROR);	
	}

	t_node *n1 = get_node(nodes, split[0]);
	t_node *n2 = get_node(nodes, split[1]);

	ft_free_array(split);

	if (!n1 || !n2)
		return (PARSE_ERROR);

	if (!vec_append(n1->links, n2))
		return (MALLOC_ERROR);

	if (!vec_append(n2->links, n1))
		return (MALLOC_ERROR);

	return (0);
}