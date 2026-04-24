#include "rend.h"

void clean_rend(t_rend *rend)
{
	glXMakeCurrent(rend->data.dpy, None, NULL);
	glXDestroyContext(rend->data.dpy, rend->data.ctx);

	if (rend->ant_text.id)
		glDeleteTextures(1, &rend->ant_text.id);
	if (rend->see_unused_text.id)
		glDeleteTextures(1, &rend->see_unused_text.id);
	if (rend->unsee_unused_text.id)
		glDeleteTextures(1, &rend->unsee_unused_text.id);
	if (rend->reset_text.id)
		glDeleteTextures(1, &rend->reset_text.id);

	XDestroyWindow(rend->data.dpy, rend->data.win);
	XFreeColormap(rend->data.dpy, rend->data.cmap);

	XFree(rend->data.vi);
	XCloseDisplay(rend->data.dpy);
}