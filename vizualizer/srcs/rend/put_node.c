#include "rend.h"
#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#include <stdio.h>

void put_node(t_rend *rend, float x, float y)
{	
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int segments = 32;
	float size_px = (rend->width > rend->height ? rend->height : rend->width) * 0.07f * rend->scale;
	float rx = (size_px / rend->width) * 2.0f;
	float ry = (size_px / rend->height) * 2.0f;
	rend->circle_size = rend->scale * 0.07f;

	glColor4f(0.1f, 0.0f, 0.0f, 0.6f);
	glDepthMask(GL_FALSE);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (int i = 0; i <= segments; ++i)
	{
		float a = (float)i / (float)segments * 2.0f * (float)M_PI;
		float vx = x + cosf(a) * rx;
		float vy = y + sinf(a) * ry;
		glVertex2f(vx, vy);
	}
	glEnd();

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

