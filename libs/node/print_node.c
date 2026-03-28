#include "node.h"
#include "vector.h"
#include "ft_printf.h"

char	*get_node_name(t_node *node);

void	print_node(void *data)
{
	t_node *node = (t_node *)data;

	ft_printf("node \"%s\" : %d:%d\n", node->name, node->x, node->y);
	
	switch (node->type)
	{
	case START:
		ft_printf("type: Start\n");
		break;
	case END:
		ft_printf("type: End\n");
		break;
	case NORMAL:
		ft_printf("type: Normal\n");
		break;
	
	}
	ft_printf("links: ");
	unsigned int i = 0;
	for (; i + 1 < node->links->size; i++)
	{
		ft_printf("%s, ", get_node_name(node->links->array[i]));
	}
	if (node->links->size > 0)
		ft_printf("%s\n", get_node_name(node->links->array[i]));
	else
		ft_printf("\n");
}