#ifndef REND_H
# define REND_H

# include <GL/glx.h>

# define HEIGHT 600
# define WIDTH 800
# define MAX_COORD 50.0f

# define BACKGROUND_COLOR 0.0f, 0.0f, 0.0f, 1.0f
# define NODE_COLOR 0.4f, 0.1f, 0.4f, 1.0f 

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
	t_texture ant_text;
	Colormap cmap;
	XVisualInfo *vi;
	int height;
	int width;
	float scale;
}	t_rend;

#endif