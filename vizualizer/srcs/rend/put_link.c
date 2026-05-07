#include "rend.h"

void put_link(t_rend rend, float x1, float y1, float x2, float y2)
{
	glLineWidth((rend.height > rend.width ? rend.height : rend.width) * rend.scale * 0.7f * 0.4f);
	glColor4f(NODE_COLOR);
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}
