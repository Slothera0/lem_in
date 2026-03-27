#include "rend.h"

void clean_rend(t_rend rend)
{
	glXMakeCurrent(rend.dpy, None, NULL);
	glXDestroyContext(rend.dpy, rend.ctx);
	if (rend.text.id)
		glDeleteTextures(1, &rend.text.id);
	XDestroyWindow(rend.dpy, rend.win);
	XFreeColormap(rend.dpy, rend.cmap);
	XFree(rend.vi);
	XCloseDisplay(rend.dpy);
}