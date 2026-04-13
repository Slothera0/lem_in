#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

GLuint load_png_texture(const char *path, int *out_w, int *out_h)
{
	FILE *fp = fopen(path, "rb");
	if (!fp)
		return 0;

	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png)
	{
		fclose(fp);
		return (0); 
	}

	png_infop info = png_create_info_struct(png);
	if (!info)
	{
		png_destroy_read_struct(&png, NULL, NULL);
		fclose(fp);
		return (0);
	}

	if (setjmp(png_jmpbuf(png)))
	{
		png_destroy_read_struct(&png, &info, NULL);
		fclose(fp);
		return 0;
	}

	png_init_io(png, fp);
	png_read_info(png, info);

	int width  = png_get_image_width(png, info);
	int height = png_get_image_height(png, info);
	int color_type = png_get_color_type(png, info);
	int bit_depth  = png_get_bit_depth(png, info);

	if (bit_depth == 16)
		png_set_strip_16(png);

	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);

	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);

	int has_alpha = png_get_valid(png, info, PNG_INFO_tRNS);
	if (has_alpha)
		png_set_tRNS_to_alpha(png);

	if (!has_alpha && (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE))
		png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);

	png_read_update_info(png, info);

	png_bytep *rows = (png_bytep*)malloc(sizeof(png_bytep) * height);
	int rowbytes = png_get_rowbytes(png, info);
	unsigned char *image_data = (unsigned char*)malloc(rowbytes * height);
	if (!rows || !image_data) {
		free(rows); free(image_data);
		png_destroy_read_struct(&png, &info, NULL);
		fclose(fp);
		return 0;
	}

	for (int y = 0; y < height; y++)
		rows[y] = image_data + y * rowbytes;

	png_read_image(png, rows);

	GLuint tex = 0;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	free(rows);
	free(image_data);
	png_destroy_read_struct(&png, &info, NULL);
	fclose(fp);

	if (out_w)
		*out_w = width;
	if (out_h)
		*out_h = height;
	return (tex);
}