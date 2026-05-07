#include "rend.h"

static void 	play_button(t_rend *rend);
static void 	pause_button(t_rend *rend);
static void 	accelerate_button(t_rend *rend);
static void 	decelerate_button(t_rend *rend);
static void		unused_button(t_rend *rend);
static void		reset_button(t_rend *rend);

void menu(t_rend *rend)
{
	glColor4f(NODE_COLOR);
	glBegin(GL_QUADS);
		glVertex2f(-1 , 0.80);
		glVertex2f(-1, 1);
		glVertex2f(1, 1);
		glVertex2f(1, 0.80);
	glEnd();

	float max_border = rend->width > rend->height ? rend->height : rend->width;

	rend->button_pos.play_left = -0.05 * (max_border / rend->width);
	rend->button_pos.play_right = 0.05 * (max_border / rend->width);

	rend->button_pos.pause_left = -0.05 * (max_border / rend->width);
	rend->button_pos.pause_right = 0.05 * (max_border / rend->width);

	rend->button_pos.accel_left = 0.20 * (max_border / rend->width);
	rend->button_pos.accel_right = 0.35 * (max_border / rend->width);

	rend->button_pos.decel_left = -0.35 * (max_border / rend->width);
	rend->button_pos.decel_right = -0.20 * (max_border / rend->width);

	rend->button_pos.unused_left = -0.67 * (max_border / rend->width);
	rend->button_pos.unused_right = -0.48 * (max_border / rend->width);

	rend->button_pos.reset_left = 0.48 * (max_border / rend->width);
	rend->button_pos.reset_right = 0.67 * (max_border / rend->width);

	if (!rend->input.pause)
		pause_button(rend);
	else
		play_button(rend);

	accelerate_button(rend);
	decelerate_button(rend);
	
	unused_button(rend);
	reset_button(rend);
	
}

static void 	play_button(t_rend *rend)
{
	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(rend->button_pos.play_left, 0.95);
	glVertex2f(rend->button_pos.play_left, 0.85);
	glVertex2f(rend->button_pos.play_right, 0.90);
	glEnd();
}

static void 	pause_button(t_rend *rend)
{
	float max_border = rend->width > rend->height ? rend->height : rend->width;

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_QUADS);
	glVertex2f(rend->button_pos.pause_left, 0.95);
	glVertex2f(rend->button_pos.pause_left, 0.85);
	glVertex2f(-0.01 * (max_border / rend->width), 0.85);
	glVertex2f(-0.01 * (max_border / rend->width), 0.95);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(0.01 * (max_border / rend->width), 0.95);
	glVertex2f(0.01 * (max_border / rend->width), 0.85);
	glVertex2f(rend->button_pos.pause_right, 0.85);
	glVertex2f(rend->button_pos.pause_right, 0.95);
	glEnd();
}

static void 	accelerate_button(t_rend *rend)
{
	float max_border = rend->width > rend->height ? rend->height : rend->width;

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(rend->button_pos.accel_left, 0.95);
	glVertex2f(rend->button_pos.accel_left, 0.85);
	glVertex2f(0.3 * (max_border / rend->width), 0.90);
	glEnd();

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.25 * (max_border / rend->width), 0.95);
	glVertex2f(0.25 * (max_border / rend->width), 0.85);
	glVertex2f(rend->button_pos.accel_right, 0.90);
	glEnd();
}

static void 	decelerate_button(t_rend *rend)
{
	float max_border = rend->width > rend->height ? rend->height : rend->width;

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(rend->button_pos.decel_right, 0.95);
	glVertex2f(rend->button_pos.decel_right, 0.85);
	glVertex2f(-0.3 * (max_border / rend->width), 0.90);
	glEnd();

	glColor4f(BACKGROUND_COLOR);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(-0.25 * (max_border / rend->width), 0.95);
	glVertex2f(-0.25 * (max_border / rend->width), 0.85);
	glVertex2f(rend->button_pos.decel_left, 0.90);
	glEnd();
}

static void	unused_button(t_rend *rend)
{
	glEnable(GL_TEXTURE_2D);
	if (rend->input.view_unused)
		glBindTexture(GL_TEXTURE_2D, rend->unsee_unused_text.id);
	else
		glBindTexture(GL_TEXTURE_2D, rend->see_unused_text.id);
	glColor3f(0.0f, 0.0f, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(rend->button_pos.unused_right, 0.84);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(rend->button_pos.unused_left, 0.84);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(rend->button_pos.unused_left, 0.98);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(rend->button_pos.unused_right, 0.98);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

static void	reset_button(t_rend *rend)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, rend->reset_text.id);
	glColor3f(0.0f, 0.0f, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(rend->button_pos.reset_right, 0.84);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(rend->button_pos.reset_left, 0.84);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(rend->button_pos.reset_left, 0.98);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(rend->button_pos.reset_right, 0.98);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
