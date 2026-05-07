#include <GL/gl.h>
#include <GL/glx.h>
#include <stdlib.h>
#include <stdio.h>

XVisualInfo *init_visual(Display *dpy, int screen)
{
	int			count;
	static int	visual_attribs[] = { GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER, True,
        None
	};

	GLXFBConfig *configs = glXChooseFBConfig(dpy, screen, visual_attribs, &count);
	if (!configs)
	{
		fprintf(stderr, "No appropriate visual found\n");
		return (NULL);
	}

	XVisualInfo *vi = glXGetVisualFromFBConfig(dpy, configs[0]);
	XFree(configs);
	if (!vi)
	{
		fprintf(stderr, "No appropriate visual found\n");
		return (NULL);
	}
	return (vi);
}
