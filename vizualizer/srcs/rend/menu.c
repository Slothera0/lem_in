#include "rend.h"
#include <stdio.h>

void menu(t_rend rend)
{
	(void)rend;
	glColor4f(NODE_COLOR);
	glBegin(GL_QUADS);
		glVertex2f(-1 , 0.80);
		glVertex2f(-1, 1);
		glVertex2f(1, 1);
		glVertex2f(1, 0.80);
	glEnd();

	float max_border = rend.width > rend.height ? rend.height : rend.width;

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(-0.05, 0.95);
	glVertex2f(-0.05, 0.85);
	glVertex2f(0.05 * (max_border / rend.width), 0.90);
	glEnd();
}