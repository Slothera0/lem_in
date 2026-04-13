#include "rend.h"

#include <stdio.h>

void put_ant(t_rend rend, float x, float y);

void	ants_spawn(t_rend rend)
{
	for (unsigned int i = 0; rend.ants[i].id != -1; i++)
	{
		put_ant(rend, rend.ants[i].x, rend.ants[i].y);
	}
}