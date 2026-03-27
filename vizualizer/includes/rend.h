#ifndef REND_H
# define REND_H

# include <GL/glx.h>

typedef struct s_texture
{
	GLuint id;
	int width;
	int height;
}	t_texture;

typedef struct s_rend
{
	Display *dpy;
	Window win;
	GLXContext ctx;
	t_texture text;
	Colormap cmap;
	XVisualInfo *vi;
}	t_rend;

#endif