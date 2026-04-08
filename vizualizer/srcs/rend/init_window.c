#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "rend.h"

XVisualInfo *init_visual(Display *dpy, int screen);
GLuint 		load_png_texture(const char *path, int *out_w, int *out_h);

int init_window(t_rend *rend_adr)
{
	t_rend rend = *rend_adr;
	
	rend.dpy = XOpenDisplay(NULL);
	if (!rend.dpy) {
		fprintf(stderr, "Could not open display\n");
		return (1);
	}

	int screen = DefaultScreen(rend.dpy);

	rend.vi = init_visual(rend.dpy, screen);
	if (!rend.vi) {
		XCloseDisplay(rend.dpy);
		return (1);
	}

	rend.cmap = XCreateColormap(rend.dpy, RootWindow(rend.dpy, screen), rend.vi->visual, AllocNone);

	XSetWindowAttributes swa;
	swa.colormap = rend.cmap;
	swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

	rend.win = XCreateWindow(rend.dpy, RootWindow(rend.dpy, screen), 0, 0, WIDTH, HEIGHT, 0, rend.vi->depth, InputOutput, rend.vi->visual, CWColormap | CWEventMask, &swa);
	XStoreName(rend.dpy, rend.win, "lem_in Visualizer");
	XMapWindow(rend.dpy, rend.win);

	XSizeHints hints;
	hints.min_width = 480;
	hints.min_height = 360;
	hints.max_width = 1920;
	hints.max_height = 1080;
	hints.flags = PMinSize | PMaxSize;
	XSetWMNormalHints(rend.dpy, rend.win, &hints);

	rend.ctx = glXCreateContext(rend.dpy, rend.vi, NULL, GL_TRUE);
	if (!rend.ctx) {
		fprintf(stderr, "Failed to create GLX context\n");
		XDestroyWindow(rend.dpy, rend.win);
		XFreeColormap(rend.dpy, rend.cmap);
		XFree(rend.vi);
		XCloseDisplay(rend.dpy);
		return (1);
	}
	glXMakeCurrent(rend.dpy, rend.win, rend.ctx);

	glDisable(GL_DEPTH_TEST); // tester de le desactiver plus tard


	rend.text.id = load_png_texture("textures/dirt.png", &rend.text.width, &rend.text.height);
	if (!rend.text.id)
		fprintf(stderr, "warning: could not load dirt.png\n");

	rend.text.width = 100;
	rend.text.height = 100;
	*rend_adr = rend;
	return (0);
}