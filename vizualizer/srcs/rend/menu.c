#include "rend.h"
#include <stdio.h>

static void 	play_button(t_rend rend);
static void 	pause_button(t_rend rend);
static void 	accelerate_button(t_rend rend);
static void 	decelerate_button(t_rend rend);

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

	if (!rend.input.pause)
		pause_button(rend);
	else
		play_button(rend);

	accelerate_button(rend);
	decelerate_button(rend);
	
	
}

static void 	play_button(t_rend rend)
{
	float max_border = rend.width > rend.height ? rend.height : rend.width;

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(-0.05 * (max_border / rend.width), 0.95);
	glVertex2f(-0.05 * (max_border / rend.width), 0.85);
	glVertex2f(0.05 * (max_border / rend.width), 0.90);
	glEnd();
}

static void 	pause_button(t_rend rend)
{
	float max_border = rend.width > rend.height ? rend.height : rend.width;

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_QUADS);
	glVertex2f(-0.05 * (max_border / rend.width), 0.95);
	glVertex2f(-0.05 * (max_border / rend.width), 0.85);
	glVertex2f(-0.01 * (max_border / rend.width), 0.85);
	glVertex2f(-0.01 * (max_border / rend.width), 0.95);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(0.01 * (max_border / rend.width), 0.95);
	glVertex2f(0.01 * (max_border / rend.width), 0.85);
	glVertex2f(0.05 * (max_border / rend.width), 0.85);
	glVertex2f(0.05 * (max_border / rend.width), 0.95);
	glEnd();
}

static void 	accelerate_button(t_rend rend)
{
	float max_border = rend.width > rend.height ? rend.height : rend.width;

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.2 * (max_border / rend.width), 0.95);
	glVertex2f(0.2 * (max_border / rend.width), 0.85);
	glVertex2f(0.3 * (max_border / rend.width), 0.90);
	glEnd();

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.25 * (max_border / rend.width), 0.95);
	glVertex2f(0.25 * (max_border / rend.width), 0.85);
	glVertex2f(0.35 * (max_border / rend.width), 0.90);
	glEnd();
}

static void 	decelerate_button(t_rend rend)
{
	float max_border = rend.width > rend.height ? rend.height : rend.width;

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(-0.2 * (max_border / rend.width), 0.95);
	glVertex2f(-0.2 * (max_border / rend.width), 0.85);
	glVertex2f(-0.3 * (max_border / rend.width), 0.90);
	glEnd();

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(-0.25 * (max_border / rend.width), 0.95);
	glVertex2f(-0.25 * (max_border / rend.width), 0.85);
	glVertex2f(-0.35 * (max_border / rend.width), 0.90);
	glEnd();
}