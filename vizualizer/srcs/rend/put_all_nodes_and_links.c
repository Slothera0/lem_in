#include "rend.h"
#include "node.h"

void	put_node(t_rend rend, float x, float y, t_room_type type);
void	put_link(t_rend rend, float x1, float y1, float x2, float y2);

void	put_all_nodes_and_links(t_rend rend, t_vector *nodes)
{
	for (unsigned int i = 0; i < nodes->size; i++)
	{
		t_node *node = nodes->array[i];
		for (unsigned int j = 0; j < node->links->size; j++)
		{
			t_node *linked_node = node->links->array[j];
			if (rend.input.view_unused || (node->visited && linked_node->visited))
				put_link(rend, node->x, node->y, linked_node->x, linked_node->y);
		}
	}
	for (unsigned int i = 0; i < nodes->size; i++)
	{
		t_node *node = nodes->array[i];
		if (rend.input.view_unused || node->visited)
			put_node(rend, (float)node->x, (float)node->y, node->type);
	}
}