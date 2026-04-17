#include "rend.h"
#include "vector.h"
#include "node.h"

#include <stdio.h>

void calculate_ant_step(t_rend rend, t_vector *path, double turn_progress)
{
	for (unsigned int i = 0; rend.ants[i].id != -1; i++)
	{
		rend.ants[i].step_x = 0;
		rend.ants[i].step_y = 0;
	}

	for (unsigned int i = 0; i < path->size; i++)
	{
		t_path *p = path->array[i];
		t_ant *ant = &rend.ants[p->ant - 1];
		t_node *current_node = get_node(rend.nodes, p->node);
		if (!current_node)
			continue ;
		float target_x = (float)current_node->x;
		float target_y = (float)current_node->y;
		ant->step_x = (target_x - ant->x) / (((double)TURN_TIME - turn_progress) / rend.input.speed);
		ant->step_y = (target_y - ant->y) / (((double)TURN_TIME - turn_progress) / rend.input.speed);
	}
}