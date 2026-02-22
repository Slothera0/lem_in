#include "node.h"
#include "vector.h"
#include "ft_printf.h"

char	*get_node_name(t_node *node);

void	print_node(void *data)
{
	t_node *node = (t_node *)data;

	ft_printf("node \"%s\" : %d:%d\n", node->name, node->x, node->y);
	
	ft_printf("links: ");
	unsigned int i = 0;
	for (; i < node->links->size - 1; i++)
	{
		ft_printf("%s, ", get_node_name(node->links->array[i]));
	}
	ft_printf("%s\n", get_node_name(node->links->array[i]));

}