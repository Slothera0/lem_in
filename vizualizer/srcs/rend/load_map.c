#include <GL/gl.h>
#include "rend.h"
#include "lem_in.h"
#include "node.h"

void	fill_map(t_rend rend);
void	ants_spawn(t_rend rend);
void 	menu(t_rend *rend);
void	put_all_nodes_and_links(t_rend rend, t_vector *nodes);

void	load_map(t_rend rend, t_lem_in *data)
{
	glClearColor(BACKGROUND_COLOR);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	put_all_nodes_and_links(rend, data->node);

	ants_spawn(rend);
	menu(&rend);

	glXSwapBuffers(rend.data.dpy, rend.data.win);
}