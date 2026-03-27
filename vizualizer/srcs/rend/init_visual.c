#include <GL/gl.h>
#include <GL/glx.h>
#include <stdlib.h>
#include <stdio.h>


XVisualInfo *init_visual(Display *dpy, int screen)
{
	static int visual_attribs[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	XVisualInfo *vi = glXChooseVisual(dpy, screen, visual_attribs);
	if (!vi) {
		fprintf(stderr, "No appropriate visual found\n");
		return (NULL);
	}
	return (vi);
}
