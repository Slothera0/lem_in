#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libpng/png.h>
#include "rend.h"

void clean_rend(t_rend rend);

int start_rend(t_rend rend)
{
	XEvent xev;
	int width = 800, height = 600;

	while (1) 
	{
		while (XPending(rend.dpy)) {
			XNextEvent(rend.dpy, &xev);
			if (xev.type == ConfigureNotify) {
				XConfigureEvent xce = xev.xconfigure;
				width = xce.width;
				height = xce.height;
				glViewport(0, 0, width, height);
			}
			if (xev.type == KeyPress) {
				KeySym ks = XLookupKeysym(&xev.xkey, 0);
				if (ks == XK_Escape)
				{
					clean_rend(rend);
					return (0);
				};
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if (rend.text.id) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, rend.text.id);
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.8f, -0.8f);
				glTexCoord2f(1.0f, 0.0f); glVertex2f( 0.8f, -0.8f);
				glTexCoord2f(1.0f, 1.0f); glVertex2f( 0.8f,  0.8f);
				glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.8f,  0.8f);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}

		glXSwapBuffers(rend.dpy, rend.win);
		usleep(16000); // environ 60 FPS
	}

	clean_rend(rend);
	return (0);
}
