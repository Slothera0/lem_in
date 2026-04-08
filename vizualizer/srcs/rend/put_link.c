#include "rend.h"
#include <stdio.h>

void put_link(t_rend rend, float x1, float y1, float x2, float y2)
{
	if (x1 == x2);
	else if (x1 > x2)
	{
		x1 -= rend.circle_size;
		x2 += rend.circle_size;
	}
	else
	{
		x1 += rend.circle_size;
		x2 -= rend.circle_size;
	}
	if (y1 == y2);
	else if (y1 > y2)
	{
		y1 -= rend.circle_size;
		y2 += rend.circle_size;
	}
	else
	{
		y1 += rend.circle_size;
		y2 -= rend.circle_size;
	}

	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth((rend.height > rend.width ? rend.height : rend.width) * rend.circle_size * 0.5f);
	glColor4f(0.1f, 0.0f, 0.0f, 0.4f);
	glDepthMask(GL_FALSE);
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
