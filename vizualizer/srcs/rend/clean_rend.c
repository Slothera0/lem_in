#include "rend.h"

void clean_rend(t_rend rend)
{
	glXMakeCurrent(rend.data.dpy, None, NULL);
	glXDestroyContext(rend.data.dpy, rend.data.ctx);
	if (rend.text.id)
		glDeleteTextures(1, &rend.text.id);
	XDestroyWindow(rend.data.dpy, rend.data.win);
	XFreeColormap(rend.data.dpy, rend.data.cmap);
	XFree(rend.data.vi);
	XCloseDisplay(rend.data.dpy);
}