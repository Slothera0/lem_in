#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "rend.h"
#include <errno.h>

XVisualInfo *init_visual(Display *dpy, int screen);
GLuint 		load_png_texture(const char *path, int *out_w, int *out_h);

int init_window(t_rend *rend_adr)
{
	t_rend rend = *rend_adr;
	
	rend.data.dpy = XOpenDisplay(NULL);
	if (!rend.data.dpy) {
		fprintf(stderr, "Could not open display\n");
		return (1);
	}

	int screen = DefaultScreen(rend.data.dpy);

	rend.data.vi = init_visual(rend.data.dpy, screen);
	if (!rend.data.vi) {
		XCloseDisplay(rend.data.dpy);
		return (1);
	}

	rend.data.cmap = XCreateColormap(rend.data.dpy, RootWindow(rend.data.dpy, screen), rend.data.vi->visual, AllocNone);
	XSetWindowAttributes swa;
	swa.colormap = rend.data.cmap;
	swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask;
	rend.data.win = XCreateWindow(rend.data.dpy, RootWindow(rend.data.dpy, screen), 0, 0, WIDTH, HEIGHT, 0, rend.data.vi->depth, InputOutput, rend.data.vi->visual, CWColormap | CWEventMask, &swa);
	XStoreName(rend.data.dpy, rend.data.win, WINDOW_TITLE);
	XMapWindow(rend.data.dpy, rend.data.win);

	XSizeHints hints;
	hints.min_width = 480;
	hints.min_height = 360;
	hints.max_width = 1920;
	hints.max_height = 1080;
	hints.flags = PMinSize | PMaxSize;
	XSetWMNormalHints(rend.data.dpy, rend.data.win, &hints);

	rend.data.ctx = glXCreateContext(rend.data.dpy, rend.data.vi, NULL, GL_TRUE);
	if (!rend.data.ctx) {
		fprintf(stderr, "Failed to create GLX context\n");
		XDestroyWindow(rend.data.dpy, rend.data.win);
		XFreeColormap(rend.data.dpy, rend.data.cmap);
		XFree(rend.data.vi);
		XCloseDisplay(rend.data.dpy);
		return (1);
	}
	glXMakeCurrent(rend.data.dpy, rend.data.win, rend.data.ctx);

	rend.ant_text.id = load_png_texture("textures/lrio.png", &rend.ant_text.width, &rend.ant_text.height);
	if (!rend.ant_text.id)
		fprintf(stderr, "warning: could not load lrio.png\n");
	rend.ant_text.width = 1;
	rend.ant_text.height = 1;

	rend.unsee_unused_text.id = load_png_texture("textures/eye.png", &rend.unsee_unused_text.width, &rend.unsee_unused_text.height);
	if (!rend.unsee_unused_text.id)
		fprintf(stderr, "warning: could not load eye.png\n");
	
	rend.see_unused_text.id = load_png_texture("textures/eye_bar3.png", &rend.see_unused_text.width, &rend.see_unused_text.height);
	if (!rend.see_unused_text.id)
		fprintf(stderr, "warning: could not load eye_bar3.png\n");

	rend.reset_text.id = load_png_texture("textures/reset.png", &rend.reset_text.width, &rend.reset_text.height);
	if (!rend.reset_text.id)
		fprintf(stderr, "warning: could not load reset.png\n");

	*rend_adr = rend;
	return (0);
}