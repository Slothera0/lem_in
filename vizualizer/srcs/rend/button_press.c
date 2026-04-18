#include "rend.h"

void button_press(t_rend *rend, float x, float y)
{
	if (y < 0.85f - 0.02 || y > 0.95f + 0.02)
		return;
	
	if (x >= rend->button_pos.play_left - 0.02 && x <= rend->button_pos.play_right + 0.02)
	{
		if (!rend->input.pause)
			rend->input.pause = 1;
		else
			rend->input.pause = 0;
	}
	else if (x >= rend->button_pos.decel_left - 0.02 && x <= rend->button_pos.decel_right + 0.02)
	{
		if (rend->input.speed > 1.0)
		rend->input.speed = 1.0;
		else
		rend->input.speed = 0.5;
	}
	else if (x >= rend->button_pos.accel_left - 0.02 && x <= rend->button_pos.accel_right + 0.02)
	{
		if (rend->input.speed < 1.0)
		rend->input.speed = 1.0;
		else
		rend->input.speed = 1.5;
	}
}