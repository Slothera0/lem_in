#include <GL/gl.h>
#include "rend.h"
#include "lem_in.h"
#include "node.h"

void	fill_map(t_rend rend);
void	put_node(t_rend *rend, float x, float y);
void	put_link(t_rend rend, float x1, float y1, float x2, float y2);
void	put_ant(t_rend rend, float x, float y);

void	load_map(t_rend rend, t_lem_in *data)
{
	glClearColor(BACKGROUND_COLOR);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// if (rend.text.id)
	// {
 	// 	fill_map(rend);
	// }

	t_vector *nodes = data->node;
	for (unsigned int i = 0; i < nodes->size; i++)
	{
		t_node *node = nodes->array[i];
		put_node(&rend, (float)node->x, (float)node->y);
	}

	for (unsigned int i = 0; i < nodes->size; i++)
	{
		t_node *node = nodes->array[i];
		for (unsigned int j = 0; j < node->links->size; j++)
		{
			t_node *linked_node = node->links->array[j];
			put_link(rend, node->x, node->y, linked_node->x, linked_node->y);
		}
	}

	// t_node *start_node = get_start(nodes);
	// put_ant(rend, start_node->x, start_node->y); // TODO: positionner les fourmis correctement

	glXSwapBuffers(rend.data.dpy, rend.data.win);
}