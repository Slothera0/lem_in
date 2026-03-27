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

XVisualInfo *init_visual(Display *dpy, int screen);

int start_rend(t_rend rend)
{
	XEvent xev;
	int width = 800, height = 600;

	/* Main loop: handle events and draw a textured quad */
	for (;;) {
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
				if (ks == XK_Escape) goto cleanup;
			}
		}

		/* Render */
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
		} else {
			/* fallback: colored triangle */
			glBegin(GL_TRIANGLES);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex2f(0.0f, 0.6f);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex2f(-0.6f, -0.6f);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex2f(0.6f, -0.6f);
			glEnd();
		}

		glXSwapBuffers(rend.dpy, rend.win);
		usleep(16000); /* ~60 FPS throttle */
	}

cleanup:
	glXMakeCurrent(rend.dpy, None, NULL);
	glXDestroyContext(rend.dpy, rend.ctx);
	if (rend.text.id) glDeleteTextures(1, &rend.text.id);
	XDestroyWindow(rend.dpy, rend.win);
	XFreeColormap(rend.dpy, rend.cmap);
	XFree(rend.vi);
	XCloseDisplay(rend.dpy);
	return (0);
}
