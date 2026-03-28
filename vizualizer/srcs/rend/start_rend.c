#include <GL/gl.h>
#include <unistd.h>
#include "rend.h"

void clean_rend(t_rend rend);
void fill_map(t_rend rend);
void put_node(t_rend rend, float x, float y);

int start_rend(t_rend rend)
{
	XEvent xev;
	rend.width = WIDTH;
	rend.height = HEIGHT;

	while (1) 
	{
		while (XPending(rend.dpy)) {
			XNextEvent(rend.dpy, &xev);
			if (xev.type == ConfigureNotify) {
				XConfigureEvent xce = xev.xconfigure;
				rend.width = xce.width;
				rend.height = xce.height;
				glViewport(0, 0, rend.width, rend.height);

				glClear(GL_COLOR_BUFFER_BIT);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				if (rend.text.id) {
					fill_map(rend);
					put_node(rend, 0.0f, 0.0f);
				}
				glXSwapBuffers(rend.dpy, rend.win);
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

		
		usleep(16000); // environ 60 FPS
	}

	clean_rend(rend);
	return (0);
}
