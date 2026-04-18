#include "rend.h"
#include "vector.h"

#include <stdio.h>

void 	put_ant(t_rend rend, float x, float y);
void 	calculate_ant_step(t_rend rend, t_vector *path, double turn_progress);
int 	ants_on_path(t_ant *ant, t_vector *path);
void	ants_spawn(t_rend rend);

static unsigned int turn = 0;
static double turn_progress = 0;
static double last_speed = 1.0;

void	ants_movements(t_rend rend)
{
	if (turn >= rend.ant_paths->size)
	{
		ants_spawn(rend);
		return ;
	}

	t_vector *path = rend.ant_paths->array[turn];

	if (turn_progress == 0 || rend.input.speed != last_speed)
	{
		calculate_ant_step(rend, path, turn_progress);
	}

	last_speed = rend.input.speed;

	for (unsigned int i = 0; rend.ants[i].id != -1; i++)
	{
		t_ant *ant = &rend.ants[i];
		if (ants_on_path(ant, path))
		{
			ant->x += ant->step_x;
			ant->y += ant->step_y;
		}
		put_ant(rend, ant->x, ant->y);
	}

	turn_progress = turn_progress + rend.input.speed;
	if (turn_progress >= TURN_TIME)
	{
		turn_progress = 0;
		turn++;
	}

}