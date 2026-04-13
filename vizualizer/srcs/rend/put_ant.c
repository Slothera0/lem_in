#include "rend.h"

void put_ant(t_rend rend, float x, float y)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, rend.ant_text.id);
	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float max_border = rend.width > rend.height ? rend.height : rend.width;
	float size_px = rend.scale * 1.7f;


	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(x - (size_px/2.0f * (max_border / rend.width)), y - (size_px/2.0f * (max_border / rend.height)));
		glTexCoord2f(0.0f, 1.0f); glVertex2f(x + (size_px/2.0f * (max_border / rend.width)), y - (size_px/2.0f * (max_border / rend.height)));
		glTexCoord2f(0.0f, 0.0f); glVertex2f(x + (size_px/2.0f * (max_border / rend.width)), y + (size_px/2.0f * (max_border / rend.height)));
		glTexCoord2f(1.0f, 0.0f); glVertex2f(x - (size_px/2.0f * (max_border / rend.width)), y + (size_px/2.0f * (max_border / rend.height)));
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}