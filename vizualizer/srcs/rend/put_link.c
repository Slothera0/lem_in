#include "rend.h"

void put_link(t_rend rend, float x1, float y1, float x2, float y2)
{
	#include <stdio.h>
	printf("circle_size: %f\n", rend.circle_size);
	glLineWidth(rend.circle_size * 0.5f);
	glColor4f(0.1f, 0.0f, 0.0f, 0.6f);
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}
