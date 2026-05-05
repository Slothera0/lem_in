#include "node.h"
#include "vector.h"
#include "libft.h"

char	*get_node_name(t_node *node);

t_node *get_node(t_vector *vector, char *name)
{
	int		lo;
	int		hi;
	int		mid;
	int		cmp;

	lo = 0;
	hi = (int)vector->size - 1;
	while (lo <= hi)
	{
		mid = (lo + hi) / 2;
		cmp = ft_strcmp(name, get_node_name(vector->array[mid]));
		if (cmp == 0)
			return (vector->array[mid]);
		else if (cmp < 0)
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	return (NULL);
}