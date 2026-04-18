#ifndef REND_H
# define REND_H

# include <GL/glx.h>

# include "vector.h"

# define WINDOW_TITLE "Lrio-min"

# define HEIGHT 600
# define WIDTH 800
# define MAX_COORD 50.0f

# define BACKGROUND_COLOR 0.0f, 0.0f, 0.0f, 1.0f
# define NODE_COLOR 0.4f, 0.1f, 0.4f, 1.0f

# define TURN_TIME 180

typedef struct s_button_pos
{
	float play_left;
	float play_right;
	float pause_left;
	float pause_right;
	float accel_left;
	float accel_right;
	float decel_left;
	float decel_right;
}	t_button_pos;

typedef struct s_texture
{
	GLuint 		id;
	int 		width;
	int 		height;
}	t_texture;

typedef struct s_data_gl
{
	Display		*dpy;
	Window		win;
	GLXContext	ctx;
	Colormap	cmap;
	XVisualInfo	*vi;
} t_data_gl;

typedef struct s_ant
{
	int			id;
	float		x;
	float		y;
	float		step_x;
	float		step_y;
}	t_ant;

typedef struct s_input
{
	int 		pause;
	double		speed;

} t_input;

typedef struct s_rend
{
	t_data_gl		data;
	t_texture		text;
	t_texture		ant_text;
	int				height;
	int				width;
	float			scale;
	t_vector		*ant_paths;
	t_ant 			*ants;
	t_vector		*nodes;
	t_input			input;
	t_button_pos	button_pos;
}	t_rend;

typedef struct s_path
{
	int			ant;
	char		*node;
}	t_path;

#endif