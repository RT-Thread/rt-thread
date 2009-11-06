#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>

#include "libpng/png.h"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned int hdc_color_t;

typedef unsigned short hdc_pixel_t;

#define HDC_ARGB(a, r, g, b)	\
	((hdc_color_t)(((uint8_t)(r)|\
	(((unsigned)(uint8_t)(g))<<8))|\
	(((unsigned long)(uint8_t)(b))<<16)|\
	(((unsigned long)(uint8_t)(a))<<24)))
#define HDC_RGB(r, g, b)	HDC_ARGB(255, (r), (g), (b))

#define HDC_RGB_R(c)	((c) & 0xff)
#define HDC_RGB_G(c)	(((c) >> 8)  & 0xff)
#define HDC_RGB_B(c)	(((c) >> 16) & 0xff)
#define HDC_RGB_A(c)	(((c) >> 24) & 0xff)

/* convert HDC color to BBBBBGGGGGGRRRRR */
uint16_t hdc_color_to_565(hdc_color_t c)
{
	uint16_t pixel;

	pixel = ((HDC_RGB_B(c)>> 3) << 11) | ((HDC_RGB_G(c) >> 2) << 5) | (HDC_RGB_R(c) >> 3);

	return pixel;
}
/* convert HDC color to RRRRRGGGGGGBBBBB */
uint16_t hdc_color_to_565p(hdc_color_t c)
{
	uint16_t pixel;

	pixel = ((HDC_RGB_R(c) >> 3) << 11) | ((HDC_RGB_G(c) >> 2) << 5) | (HDC_RGB_B(c)>> 3);
	return pixel;
}

/* png image information */
png_structp png_ptr;
png_infop info_ptr;

struct hdc_image_header
{
	uint32_t magic;

	uint32_t width;
	uint32_t height;

	/* transparent color */
	uint32_t tmask;

	/* reserved */
	uint32_t reserved;
};
struct hdc_image_header header;

int main(int argc, char** argv)
{
	int bit_depth;
	int color_type;
	double gamma;
	int width, height;
	FILE *src_fp, *dst_fp;
	png_uint_32 x, y;
	png_bytep row;
	png_bytep data;
	hdc_pixel_t *ptr;

	src_fp = fopen(argv[1], "rb");
	dst_fp = fopen(argv[2], "wb");

	if (src_fp == NULL || dst_fp == NULL) 
	{
		printf("can't open file for read or write\n");
		return -1;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL)
	{
		return -1;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL)
	{
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return -1;
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_read_end(png_ptr, NULL);

		/* destroy png struct */
		png_destroy_info_struct(png_ptr, &info_ptr);
		png_destroy_read_struct(&png_ptr, NULL, NULL);

		fclose(src_fp);fclose(dst_fp);

		return (-1);
	}

	png_init_io(png_ptr, src_fp);

	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth,
		&color_type, NULL, NULL, NULL);

	if (bit_depth == 16)
		png_set_strip_16(png_ptr);
	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_expand(png_ptr);
	if (bit_depth < 8)
		png_set_expand(png_ptr);
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_expand(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);

	/* set gamma conversion */
	if (png_get_gAMA(png_ptr, info_ptr, &gamma))
		png_set_gamma(png_ptr, (double)2.2, gamma);

	png_read_update_info(png_ptr, info_ptr);

	/* write HDC file header */
	sprintf((char *)&header.magic, "HDC%c", '\0');
	header.width	= info_ptr->width;
	header.height	= info_ptr->height;
	header.tmask	= 0;
	header.reserved = 0;
	fwrite(&header, 1, sizeof(struct hdc_image_header), dst_fp);

	row = (png_bytep) malloc (png_get_rowbytes(png_ptr, info_ptr));
	if (row == NULL) goto _return;

	ptr = (hdc_pixel_t*) malloc (header.width * header.height * sizeof(hdc_pixel_t));
	switch (info_ptr->color_type)
	{
	case PNG_COLOR_TYPE_RGBA:
		for (y = 0; y < info_ptr->height; y++)
		{
			png_read_row(png_ptr, row, png_bytep_NULL);
			for (x = 0; x < info_ptr->width; x++)
			{
				data = &(row[x * 4]);

				ptr[x + y * info_ptr->width] = hdc_color_to_565p(HDC_ARGB((255 - data[3]), data[0], data[1], data[2]));
			}
		}

		break;

	case PNG_COLOR_TYPE_PALETTE:
		for (y = 0; y < info_ptr->height; y++)
		{
			png_read_row(png_ptr, row, png_bytep_NULL);
			for (x = 0; x < info_ptr->width; x++)
			{
				data = &(row[x]);

				ptr[x] = hdc_color_to_565p(HDC_ARGB(0, info_ptr->palette[data[0]].red,
					info_ptr->palette[data[0]].green,
					info_ptr->palette[data[0]].blue));
			}
		}

	default:
		break;
	};

	fwrite(ptr, 1, header.height * header.width * sizeof(hdc_pixel_t), dst_fp);

_return:
	png_read_end(png_ptr, NULL);

	/* destroy png struct */
	png_destroy_info_struct(png_ptr, &info_ptr);
	png_destroy_read_struct(&png_ptr, NULL, NULL);

	fclose(src_fp);
	fclose(dst_fp);
	free(ptr);

	return 0;
}
