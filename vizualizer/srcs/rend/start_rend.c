#include <GL/gl.h>
#include <unistd.h>
#include "rend.h"
#include "lem_in.h"
#include "node.h"

void	clean_rend(t_rend rend);
void	load_map(t_rend rend, t_lem_in *data);
void	ants_movements(t_rend rend);

void	put_node(t_rend *rend, float x, float y);
void	put_link(t_rend rend, float x1, float y1, float x2, float y2);

int start_rend(t_rend rend, t_lem_in *data)
{
	XEvent xev;
	rend.width = WIDTH;
	rend.height = HEIGHT;

	while (1) 
	{
		while (XPending(rend.data.dpy)) {
			XNextEvent(rend.data.dpy, &xev);
			if (xev.type == ConfigureNotify) {
				XConfigureEvent xce = xev.xconfigure;
				rend.width = xce.width;
				rend.height = xce.height;
				glViewport(0, 0, rend.width, rend.height);

				load_map(rend, data);
			}

			if (xev.type == KeyPress) {
				KeySym ks = XLookupKeysym(&xev.xkey, 0);
				if (ks == XK_Escape)
				{
					clean_rend(rend);
					return (0);
				}
			}
		}

		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

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
		ants_movements(rend);

		glXSwapBuffers(rend.data.dpy, rend.data.win);
		
		usleep(16000); // environ 60 FPS
	}

	clean_rend(rend);
	return (0);
}
