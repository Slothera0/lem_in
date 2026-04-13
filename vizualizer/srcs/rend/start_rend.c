#include <GL/gl.h>
#include <unistd.h>
#include "rend.h"
#include "lem_in.h"

void	clean_rend(t_rend rend);
void	load_map(t_rend rend, t_lem_in *data);
void	ants_movements(t_rend rend);

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

		ants_movements(rend);
		
		usleep(16000); // environ 60 FPS
	}

	clean_rend(rend);
	return (0);
}
