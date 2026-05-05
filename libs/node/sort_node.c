#include "vector.h"
#include "node.h"

void	sort_nodes(t_vector *vec)
{
	int		i;
	int		j;
	void	*key;

	i = 1;
	while (i < (int)vec->size)
	{
		key = vec->array[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp(get_node_name(vec->array[j]),get_node_name(key)) > 0)
		{
			vec->array[j + 1] = vec->array[j];
			j--;
		}
		vec->array[j + 1] = key;
		i++;
	}
}