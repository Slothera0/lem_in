#include "rend.h"
#include "vector.h"

#include <stdio.h>

void put_ant(t_rend rend, float x, float y);
void calculate_ant_step(t_rend rend, t_vector *path);

unsigned int turn = 0;
unsigned int turn_progress = 0;

void	ants_movements(t_rend rend)
{
	if (turn >= rend.ant_paths->size)
		return ;

	t_vector *path = rend.ant_paths->array[turn];

	if (turn_progress == 0)
	{
		calculate_ant_step(rend, path);
	}

	for (unsigned int i = 0; i < path->size; i++)
	{
		t_path *p = path->array[i];
		t_ant *ant = &rend.ants[p->ant - 1];
		ant->x += ant->step_x;
		ant->y += ant->step_y;
		put_ant(rend, ant->x, ant->y);
	}

	turn_progress++;
	if (turn_progress >= TURN_TIME)
	{
		turn_progress = 0;
		turn++;
	}

}