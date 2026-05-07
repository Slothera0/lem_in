#include <GL/gl.h>
#include <unistd.h>
#include "rend.h"
#include "lem_in.h"
#include "node.h"

void	clean_rend(t_rend *rend);
void	load_map(t_rend rend, t_lem_in *data);
void	ants_movements(t_rend rend);
void	ants_spawn(t_rend rend);
void 	menu(t_rend *rend);
int		handle_input(t_rend *rend, XEvent xev);
void	put_all_nodes_and_links(t_rend rend, t_vector *nodes);

int start_rend(t_rend rend, t_lem_in *data)
{
	XEvent xev;
	rend.width = WIDTH;
	rend.height = HEIGHT;
	rend.input.speed = 1.0;
	rend.input.pause = 0;
	rend.input.view_unused = 1;
	rend.wm_delete = XInternAtom(rend.data.dpy, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(rend.data.dpy, rend.data.win, &rend.wm_delete, 1);

	while (1) 
	{
		while (XPending(rend.data.dpy))
		{
			XNextEvent(rend.data.dpy, &xev);
			if (xev.type == ConfigureNotify)
			{
				XConfigureEvent xce = xev.xconfigure;
				rend.width = xce.width;
				rend.height = xce.height;
				glViewport(0, 0, rend.width, rend.height);

				load_map(rend, data);
			}

			if (handle_input(&rend, xev))
				return (0);
		}

		glClearColor(BACKGROUND_COLOR);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		put_all_nodes_and_links(rend, data->node);

		menu(&rend);

		if (!rend.input.pause)
			ants_movements(rend);
		else
			ants_spawn(rend);

		glXSwapBuffers(rend.data.dpy, rend.data.win);
		
		usleep(16000); // environ 60 FPS
	}

	clean_rend(&rend);
	return (0);
}
