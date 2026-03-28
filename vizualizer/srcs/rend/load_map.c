#include <GL/gl.h>
#include "rend.h"
#include "lem_in.h"
#include "node.h"

void	fill_map(t_rend rend);
void	put_node(t_rend rend, float x, float y);

void	load_map(t_rend rend, t_lem_in *data)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (rend.text.id)
	{
		fill_map(rend);
	}

	t_vector *nodes = data->node;
	for (unsigned int i = 0; i < nodes->size; i++)
	{
		t_node *node = nodes->array[i];
		put_node(rend, (float)node->x, (float)node->y);
	}

	glXSwapBuffers(rend.dpy, rend.win);
}