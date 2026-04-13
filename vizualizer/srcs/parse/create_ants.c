#include "rend.h"



t_ant	*create_ant(int ants_nb, float x, float y)
{
	t_ant *ant = malloc(sizeof(t_ant) * (ants_nb + 1));
	if (!ant)
		return (NULL);
	for (int i = 1; i <= ants_nb; i++)
	{
		ant[i - 1].id = i;
		ant[i - 1].x = x;
		ant[i - 1].y = y;
		ant[i - 1].step_x = 0;
		ant[i - 1].step_y = 0;
	}
	ant[ants_nb].id = -1;
	ant[ants_nb].x = 0;
	ant[ants_nb].y = 0;
	ant[ants_nb].step_x = 0;
	ant[ants_nb].step_y = 0;
	return (ant);
}