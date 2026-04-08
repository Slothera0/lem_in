#ifndef REND_H
# define REND_H

# include <GL/glx.h>

# define HEIGHT 600
# define WIDTH 800
# define MAX_COORD 50.0f

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
	int height;
	int width;
	float scale;
	float circle_size;
}	t_rend;

#endif