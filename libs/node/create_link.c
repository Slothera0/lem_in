#include "node.h"
#include "vector.h"
#include "libft.h"

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

	n1->links = vec_append(n1->links, n2);
	if (!n1->links)
		return (MALLOC_ERROR);

	n2->links = vec_append(n2->links, n1);
	if (!n2->links)
		return (MALLOC_ERROR);

	return (0);
}