#include "rend.h"

void fill_map(t_rend rend)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, rend.text.id);
	glColor3f(1.0f, 1.0f, 1.0f);

	int tiles_x = rend.width / rend.text.width + 1;
	int tiles_y = rend.height / rend.text.height + 1;

	for(int y = 0; y < tiles_y; y++) {
		for(int x = 0; x < tiles_x; x++) {
			float x0 = (float)x * rend.text.width / rend.width * 2 - 1;
			float y0 = (float)y * rend.text.height / rend.height * 2 - 1;
			float x1 = (float)(x + 1) * rend.text.width / rend.width * 2 - 1;
			float y1 = (float)(y + 1) * rend.text.height / rend.height * 2 - 1;

			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex2f(x0, y0);
				glTexCoord2f(1.0f, 0.0f); glVertex2f(x1, y0);
				glTexCoord2f(1.0f, 1.0f); glVertex2f(x1, y1);
				glTexCoord2f(0.0f, 1.0f); glVertex2f(x0, y1);
			glEnd();
		}
	}


	glDisable(GL_TEXTURE_2D);
}