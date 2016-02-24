/*
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-24     onelife      Reimplement to improve efficiency and add
 *  features. The new decoder uses configurable fixed size working buffer and
 *  provides scaledown function.
 */
#include <rtthread.h>
#include <rtgui/dc_hw.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/image_bmp.h>
#include <rtgui/blit.h>

#include <math.h>

#ifdef RTGUI_USING_DFS_FILERW
#include <dfs_posix.h>
#endif

#ifdef RTGUI_IMAGE_BMP
/* Compression encodings for BMP files */
#ifndef BI_RGB
#define BI_RGB          0
#define BI_RLE8         1
#define BI_RLE4         2
#define BI_BITFIELDS    3
#endif

#define BMP_WORKING_BUFFER_SIZE (384)   /* In multiple of 12 and bigger than 48 */
#define BMP_MAX_SCALING_FACTOR  (10)    // TODO: find the max value!
#define hw_driver               (rtgui_graphic_driver_get_default())

struct rtgui_image_bmp
{
    rt_bool_t is_loaded;
    rt_uint8_t *pixels;
    struct rtgui_filerw *filerw;
    rt_uint32_t w, h;
    rt_uint32_t pixel_offset;
    rt_uint32_t pitch;
    rt_uint8_t scale;
    rt_uint8_t bit_per_pixel;
    rt_uint8_t pad;
};

static rt_bool_t rtgui_image_bmp_check(struct rtgui_filerw *file);
static rt_bool_t rtgui_image_bmp_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load);
static void rtgui_image_bmp_unload(struct rtgui_image *image);
static void rtgui_image_bmp_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect);

struct rtgui_image_engine rtgui_image_bmp_engine =
{
    "bmp",
    { RT_NULL },
    rtgui_image_bmp_check,
    rtgui_image_bmp_load,
    rtgui_image_bmp_unload,
    rtgui_image_bmp_blit,
};

static rt_bool_t rtgui_image_bmp_check(struct rtgui_filerw *file)
{
    rt_uint8_t buffer[18];
    rt_bool_t is_bmp = RT_FALSE;

    do
    {
        if (!file)
        {
            break;
        }

        /* Prepare to decode */
        if (rtgui_filerw_seek(file, 0, RTGUI_FILE_SEEK_SET) < 0)
        {
            break;
        }
        if (rtgui_filerw_read(file, (void *)buffer, 18, 1) != 18)
        {
            break;
        }
        /* Read file type */
        if (buffer[0] != 'B' || buffer[1] != 'M')
        {
            break;
        }

        /* Read BMP header size */
        if (*(rt_uint32_t *)&buffer[14] == 12)
        {
            /* Bitmap Header Version 2.x */
            if (rtgui_filerw_read(file, (void *)buffer, 8, 1) != 8)
            {
                break;
            }
            /* Read image size */
            is_bmp = RT_TRUE;
        }
        else
        {
            /* Bitmap Header Version bigger than 2.x */
            if (rtgui_filerw_read(file, (void *)buffer, 8, 1) != 8)
            {
                break;
            }
            /* Read image size */
            is_bmp = RT_TRUE;
        }
    } while (0);

    return is_bmp;
}

static struct rtgui_image_palette *rtgui_image_bmp_load_palette(
    struct rtgui_filerw *file,
    rt_uint32_t colorsUsed,
    rt_bool_t alpha)
{
    /* Load the palette, if any */
    rt_uint32_t i;
    struct rtgui_image_palette *palette;

    palette = rtgui_image_palette_create(colorsUsed);
    if (palette == RT_NULL)
    {
        return RT_NULL;
    }

	palette->ncolors = colorsUsed;
    if (alpha)
    {
        rt_uint8_t temp[4];
        for (i = 0; i < colorsUsed; i++)
        {
            if (rtgui_filerw_read(file, (void *)&temp, 1, 4) != 4)
            {
                rtgui_free(palette);
                return RT_NULL;
            }
            palette->colors[i] = RTGUI_ARGB(temp[3], temp[2], temp[1], temp[0]);
        }
    }
    else
    {
        rt_uint8_t temp[3];
        for (i = 0; i < colorsUsed; i++)
        {
            if (rtgui_filerw_read(file, (void *)&temp, 1, 3) != 3)
            {
                rtgui_free(palette);
                return RT_NULL;
            }
            palette->colors[i] = RTGUI_RGB(temp[2], temp[1], temp[0]);
        }
    }

    return palette;
}

static rt_bool_t rtgui_image_bmp_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load)
{
    rt_uint8_t scale = 0;
    rt_uint8_t *wrkBuffer = RT_NULL;
    struct rtgui_image_bmp *bmp = RT_NULL;
    rt_uint32_t bmpHeaderSize;
    rt_uint32_t colorsUsed;

    if (scale > BMP_MAX_SCALING_FACTOR)
    {
        return RT_FALSE;
    }

    do
    {
        wrkBuffer = (rt_uint8_t *)rtgui_malloc(BMP_WORKING_BUFFER_SIZE);
        if (wrkBuffer == RT_NULL)
        {
            rt_kprintf("BMP err: no mem\n");
            break;
        }

        bmp = (struct rtgui_image_bmp *)rtgui_malloc(sizeof(struct rtgui_image_bmp));
        if (bmp == RT_NULL)
        {
            break;
        }
        bmp->pixels = RT_NULL;

        /* Prepare to decode */
        if (rtgui_filerw_seek(file, 0, RTGUI_FILE_SEEK_SET) < 0)
        {
            break;
        }
        if (rtgui_filerw_read(file, (void *)wrkBuffer, 18, 1) != 18)
        {
            break;
        }
        /* Read file type */
        if (wrkBuffer[0] != 'B' || wrkBuffer[1] != 'M')
        {
            break;
        }
        /* Read pixel array offset */
        bmp->pixel_offset = *(rt_uint32_t *)&wrkBuffer[10];
        /* Read BMP header size */
        bmpHeaderSize = *(rt_uint32_t *)&wrkBuffer[14];
        colorsUsed = 0;
        if (bmpHeaderSize == 12)
        {
            /* Bitmap Header Version 2.x */
            if (rtgui_filerw_read(file, (void *)wrkBuffer, 8, 1) != 8)
            {
                break;
            }
            /* Read image size */
            bmp->w = (rt_uint32_t) * (rt_uint16_t *)&wrkBuffer[0];
            bmp->h = (rt_uint32_t) * (rt_uint16_t *)&wrkBuffer[2];
            /* Read bits per pixel */
            bmp->bit_per_pixel = (rt_uint8_t) * (rt_uint16_t *)&wrkBuffer[6];
        }
        else
        {
            /* Bitmap Header Version bigger than 2.x */
            rt_uint32_t compression;

            if (rtgui_filerw_read(file, (void *)wrkBuffer, 36, 1) != 36)
            {
                break;
            }
            /* Read image size */
            bmp->w = *(rt_uint32_t *)&wrkBuffer[0];
            bmp->h = *(rt_uint32_t *)&wrkBuffer[4];
            /* Read bits per pixel */
            bmp->bit_per_pixel = (rt_uint8_t) * (rt_uint16_t *)&wrkBuffer[10];
            if (bmp->bit_per_pixel > 32)
            {
                rt_kprintf("BMP err: unsupported format\n");
                break;
            }
            /* Read compression method */
            compression = *(rt_uint32_t *)&wrkBuffer[12];
            if (compression != BI_RGB && compression != BI_BITFIELDS)
            {
                rt_kprintf("BMP err: unsupported format\n");
                break;
            }
            /* Read number of colors */
            colorsUsed = *(rt_uint32_t *)&wrkBuffer[28];
        }
        if (!colorsUsed)
        {
            colorsUsed = 1 << bmp->bit_per_pixel;
        }

        /* Load palette */
        if (bmp->bit_per_pixel <= 8)
        {
            if (rtgui_filerw_seek(file, 14 + bmpHeaderSize, RTGUI_FILE_SEEK_SET) < 0)
            {
                break;
            }

            image->palette = rtgui_image_bmp_load_palette(file, colorsUsed,
                             bmpHeaderSize > 12 ? RT_TRUE : RT_FALSE);
            if (image->palette == RT_NULL)
            {
                break;
            }
        }

        /* Set image information */
        bmp->is_loaded = RT_FALSE;
        bmp->scale = scale;
        if (bmp->bit_per_pixel == 1)
        {
            bmp->pitch = (bmp->w + 7) >> 3;
        }
        else if (bmp->bit_per_pixel == 4)
        {
            bmp->pitch = (bmp->w + 1) >> 1;
        }
        else
        {
            bmp->pitch = bmp->w * (bmp->bit_per_pixel >> 3);
        }
        bmp->pad = ((bmp->pitch % 4) ? (4 - (bmp->pitch % 4)) : 0);
        bmp->filerw = file;

        image->w = (rt_uint16_t)bmp->w >> bmp->scale;
        image->h = (rt_uint16_t)bmp->h >> bmp->scale;
        image->engine = &rtgui_image_bmp_engine;
        image->data = bmp;

        /* Start to decode */
        if (load == RT_TRUE)
        {
            rt_bool_t error = RT_FALSE;
            rt_uint8_t *dst;
            rt_uint32_t imageWidth;
            rt_uint16_t readLength, readIndex, loadIndex;
            rt_uint8_t skipLength;
            rt_uint16_t y;
            rt_uint8_t bytePerPixel;
            rt_int8_t scale1, scale2;

            bytePerPixel = _UI_BITBYTES(bmp->bit_per_pixel);
            imageWidth = image->w * bytePerPixel;       /* Scaled width in byte */
            bmp->pixels = rtgui_malloc(image->h * imageWidth);
            if (bmp->pixels == RT_NULL)
            {
                rt_kprintf("BMP err: no mem to load (%d)\n", image->h * imageWidth);
                break;
            }

            /* Read the pixels.  Note that the bmp image is upside down */
            if (rtgui_filerw_seek(file, bmp->pixel_offset, RTGUI_FILE_SEEK_SET) < 0)
            {
                break;
            }

            if (bmp->bit_per_pixel == 1)
            {
                if (bmp->scale > 3)
                {
                    scale1 = bmp->scale - 3;
                    scale2 = 3;
                }
                else
                {
                    scale1 = 0;
                    scale2 = bmp->scale;
                }
            }
            else if (bmp->bit_per_pixel == 4)
            {
                if (bmp->scale > 1)
                {
                    scale1 = bmp->scale - 1;
                    scale2 = 1;
                }
                else
                {
                    scale1 = 0;
                    scale2 = bmp->scale;
                }
            }

            /* Process whole image */
            y = 0;
            while (y < image->h)
            {
                dst = bmp->pixels + (image->h - y - 1) * imageWidth;
                readIndex = 0;
                skipLength = 0;

                /* Process a line */
                while (readIndex < bmp->pitch)
                {
                    /* Read data to buffer */
                    readLength = (BMP_WORKING_BUFFER_SIZE > ((rt_uint16_t)bmp->pitch - readIndex)) ? \
                                 ((rt_uint16_t)bmp->pitch - readIndex) : BMP_WORKING_BUFFER_SIZE;
                    if (rtgui_filerw_read(file, (void *)wrkBuffer, 1, readLength) != readLength)
                    {
                        rt_kprintf("BMP err: read failed\n");
                        error = RT_TRUE;
                        break;
                    }
                    readIndex += readLength;

                    /* Process read buffer */
                    if (bmp->bit_per_pixel == 1)
                    {
                        rt_uint8_t j;

                        for (loadIndex = skipLength; loadIndex < readLength; loadIndex += 1 << scale1)
                        {
                            for (j = 0; j < 8; j += 1 << scale2)
                            {
                                *(dst++) = (wrkBuffer[loadIndex] & (1 << (7 - j))) >> (7 - j);
                            }
                        }
                        if (scale1 && (readLength % (1 << scale1)))
                        {
                            skipLength = (1 << scale1) - readLength % (1 << scale1);
                        }
                    }
                    else if (bmp->bit_per_pixel == 4)
                    {
                        rt_uint8_t j;

                        for (loadIndex = skipLength; loadIndex < readLength; loadIndex += 1 << scale1)
                        {
                            for (j = 0; j < 8; j += 1 << (2 + scale2))
                            {
                                *(dst++) = (wrkBuffer[loadIndex] & (0x0F << (4 - j))) >> (4 - j);
                            }
                        }
                        if (scale1 && (readLength % (1 << scale1)))
                        {
                            skipLength = (1 << scale1) - readLength % (1 << scale1);
                        }
                    }
                    else
                    {
                        if (bmp->scale == 0)
                        {
                            rt_memcpy((void *)dst, (void *)wrkBuffer, readLength);
                            dst += readLength;
                        }
                        else
                        {
                            for (loadIndex = skipLength; loadIndex < readLength; loadIndex += bytePerPixel << bmp->scale)
                            {
                                rt_memcpy((void *)dst, (void *)&wrkBuffer[loadIndex], bytePerPixel);
                                dst += bytePerPixel;
                            }
                            if (readLength % (1 << bmp->scale))
                            {
                                skipLength = (1 << bmp->scale) - readLength % (1 << bmp->scale);
                            }
                        }
                    }
                }
                if (error)
                {
                    break;
                }
                y++;

                /* Skip padding bytes  */
                if (bmp->pad)
                {
                    if (rtgui_filerw_seek(file, bmp->pad, RTGUI_FILE_SEEK_CUR) < 0)
                    {
                        error = RT_TRUE;
                        break;
                    }
                }

                /* Height scale down */
                if (bmp->scale)
                {
                    if (rtgui_filerw_seek(file, (bmp->pitch + bmp->pad) * ((1 << bmp->scale) - 1),
                                          RTGUI_FILE_SEEK_CUR) < 0)
                    {
                        error = RT_TRUE;
                        break;
                    }
                }
            }
            if (error)
            {
                break;
            }
            /* Close file */
            rtgui_filerw_close(bmp->filerw);
            bmp->filerw = RT_NULL;
            bmp->is_loaded = RT_TRUE;
        }

        /* Release memory */
        rtgui_free(wrkBuffer);
        return RT_TRUE;
    } while (0);

    /* Release memory */
    rtgui_free(wrkBuffer);
    rtgui_free(image->palette);
    if (bmp)
        rtgui_free(bmp->pixels);
    rtgui_free(bmp);
    return RT_FALSE;
}

static void rtgui_image_bmp_unload(struct rtgui_image *image)
{
    struct rtgui_image_bmp *bmp;

    if (image != RT_NULL)
    {
        bmp = (struct rtgui_image_bmp *)image->data;

        /* Release memory */
        rtgui_free(bmp->pixels);
        if (bmp->filerw != RT_NULL)
        {
            /* Close file */
            rtgui_filerw_close(bmp->filerw);
            bmp->filerw = RT_NULL;
        }
        rtgui_free(bmp);
    }
}

static void rtgui_image_bmp_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *dst_rect)
{
    rt_uint16_t w, h;
    struct rtgui_image_bmp *bmp;
    rt_uint8_t bytePerPixel;
    rt_uint32_t imageWidth;
    rt_bool_t error;

    bmp = (struct rtgui_image_bmp *)image->data;
    RT_ASSERT(image != RT_NULL || dc != RT_NULL || dst_rect != RT_NULL || bmp != RT_NULL);

    bytePerPixel = _UI_BITBYTES(bmp->bit_per_pixel);

	imageWidth = image->w * bytePerPixel;       /* Scaled width in byte */
    error = RT_FALSE;

    do
    {
        /* this dc is not visible */
        if (rtgui_dc_get_visible(dc) != RT_TRUE) break;

        /* the minimum rect */
		w = _UI_MIN(image->w, rtgui_rect_width(*dst_rect));
		h = _UI_MIN(image->h, rtgui_rect_height(*dst_rect));

        if (!bmp->is_loaded)
        {
            rt_uint8_t *wrkBuffer;
            rt_uint16_t readLength, readIndex, loadIndex;
            rt_uint8_t skipLength;
            rt_uint16_t x, y;
            rt_int8_t scale1, scale2;
            rt_uint16_t y_start = dst_rect->y1 + h - 1;

            /* Read the pixels.  Note that the bmp image is upside down */
            if (rtgui_filerw_seek(bmp->filerw, bmp->pixel_offset, RTGUI_FILE_SEEK_SET) < 0)
            {
                break;
            }
            /* the image is upside down. So we need to start from middle if the
             * image is higher than the dst_rect. */
            if (image->h > rtgui_rect_height(*dst_rect))
            {
                int hdelta = image->h - rtgui_rect_height(*dst_rect);
                if (rtgui_filerw_seek(bmp->filerw, hdelta * (bmp->pitch + bmp->pad) * (1 << bmp->scale),
                                      RTGUI_FILE_SEEK_CUR) < 0)
                {
                    error = RT_TRUE;
                    break;
                }
            }

            if (bmp->bit_per_pixel == 1)
            {
                if (bmp->scale > 3)
                {
                    scale1 = bmp->scale - 3;
                    scale2 = 3;
                }
                else
                {
                    scale1 = 0;
                    scale2 = bmp->scale;
                }
            }
            else if (bmp->bit_per_pixel == 4)
            {
                if (bmp->scale > 1)
                {
                    scale1 = bmp->scale - 1;
                    scale2 = 1;
                }
                else
                {
                    scale1 = 0;
                    scale2 = bmp->scale;
                }
            }

            wrkBuffer = (rt_uint8_t *)rtgui_malloc(
                            (BMP_WORKING_BUFFER_SIZE > bmp->pitch) ? \
                            bmp->pitch : BMP_WORKING_BUFFER_SIZE);
            if (wrkBuffer == RT_NULL)
            {
                rt_kprintf("BMP err: no mem (%d)\n", BMP_WORKING_BUFFER_SIZE);
                break;
            }

            /* Process whole image */
            y = 0;
            while (y < h)
            {
                x = 0;
                readIndex = 0;
                skipLength = 0;

                /* Process a line */
                while (readIndex < bmp->pitch)
                {
                    /* Read data to buffer */
                    readLength = (BMP_WORKING_BUFFER_SIZE > ((rt_uint16_t)bmp->pitch - readIndex)) ? \
                                 ((rt_uint16_t)bmp->pitch - readIndex) : BMP_WORKING_BUFFER_SIZE;
                    if (rtgui_filerw_read(bmp->filerw, (void *)wrkBuffer, 1, readLength) != readLength)
                    {
                        rt_kprintf("BMP err: read failed\n");
                        error = RT_TRUE;
                        break;
                    }
                    readIndex += readLength;

                    /* Process read buffer */
                    if (bmp->bit_per_pixel == 1)
                    {
                        for (loadIndex = skipLength; loadIndex < readLength; loadIndex += 1 << scale1)
                        {
                            rt_uint8_t j;
                            for (j = 0; j < 8; j += 1 << scale2)
                            {
                                rtgui_color_t color;
                                color = image->palette->colors[(wrkBuffer[loadIndex] & (1 << (7 - j))) >> (7 - j)];
                                rtgui_dc_draw_color_point(dc,
                                                          dst_rect->x1 + x++,
                                                          y_start - y,
                                                          color);
                                if (x >= w)
                                    break;
                            }
                            if (scale1 && (readLength % (1 << scale1)))
                            {
                                skipLength = (1 << scale1) - readLength % (1 << scale1);
                            }
                        }
                    }
                    else if (bmp->bit_per_pixel == 4)
                    {
                        for (loadIndex = skipLength; loadIndex < readLength; loadIndex += 1 << scale1)
                        {
                            rt_uint8_t j;
                            for (j = 0; j < 8; j += 1 << (2 + scale2))
                            {
                                rtgui_color_t color;
                                color = image->palette->colors[(wrkBuffer[loadIndex] & (0x0F << (4 - j))) >> (4 - j)];
                                rtgui_dc_draw_color_point(dc,
                                                          dst_rect->x1 + x++,
                                                          y_start - y,
                                                          color);
                                if (x >= w)
                                    break;
                            }
                        }
                        if (scale1 && (readLength % (1 << scale1)))
                        {
                            skipLength = (1 << scale1) - readLength % (1 << scale1);
                        }
                    }
                    else if (bmp->bit_per_pixel == 8)
                    {
                        for (loadIndex = skipLength; loadIndex < readLength; loadIndex += 1 << bmp->scale)
                        {
                            rtgui_color_t color;
                            color = image->palette->colors[wrkBuffer[loadIndex]];
                            rtgui_dc_draw_color_point(dc,
                                                      dst_rect->x1 + x++,
                                                      y_start - y,
                                                      color);
                            if (x >= w)
                                break;
                        }
                        if (readLength % (1 << bmp->scale))
                        {
                            skipLength = (1 << bmp->scale) - readLength % (1 << bmp->scale);
                        }
                    }
                    else
                    {
                        rtgui_blit_line_func blit_line;
                        rt_uint8_t hw_bytePerPixel = _UI_BITBYTES(hw_driver->bits_per_pixel);
                        rt_uint8_t temp[4] = {0};

                        if (!hw_bytePerPixel)
                        {
                            hw_bytePerPixel = 1;
                        }

                        if (hw_driver->pixel_format == RTGRAPHIC_PIXEL_FORMAT_BGR565)
                        {
                            blit_line = rtgui_blit_line_get_inv(hw_bytePerPixel, bytePerPixel);
                        }
                        else
                        {
                            blit_line = rtgui_blit_line_get(hw_bytePerPixel, bytePerPixel);
                        }

                        for (loadIndex = skipLength;
                                loadIndex < readLength;
                                loadIndex += bytePerPixel << bmp->scale)
                        {
                            blit_line(temp, &wrkBuffer[loadIndex], bytePerPixel);
                            dc->engine->blit_line(dc,
                                                  dst_rect->x1 + x, dst_rect->x1 + x + 1,
                                                  y_start - y,
                                                  temp);
                            x++;
                            if (x >= w)
                                break;
                        }
                        if (readLength % (1 << bmp->scale))
                        {
                            skipLength = (1 << bmp->scale) - readLength % (1 << bmp->scale);
                        }
                    }
                }
                if (error)
                {
                    break;
                }
                y++;

                /* Skip padding bytes  */
                if (bmp->pad)
                {
                    if (rtgui_filerw_seek(bmp->filerw, bmp->pad, RTGUI_FILE_SEEK_CUR) < 0)
                    {
                        error = RT_TRUE;
                        break;
                    }
                }

                /* Height scale down */
                if (bmp->scale)
                {
                    if (rtgui_filerw_seek(bmp->filerw, (bmp->pitch + bmp->pad) * ((1 << bmp->scale) - 1),
                                          RTGUI_FILE_SEEK_CUR) < 0)
                    {
                        error = RT_TRUE;
                        break;
                    }
                }
            }
            if (error)
            {
                break;
            }
            /* Release memory */
            rtgui_free(wrkBuffer);
        }
        else
        {
            rt_uint16_t x, y;
            rt_uint8_t *ptr;

			if (bmp->bit_per_pixel <= 8)
			{
				rtgui_color_t color;

				/* 1bpp, and using palette */
				for (y = 0; y < h; y ++)
				{
                    ptr = bmp->pixels + (y * imageWidth);
					for (x = 0; x < w; x ++)
					{
						color = image->palette->colors[*(ptr++)];
						rtgui_dc_draw_color_point(dc,
							dst_rect->x1 + x, dst_rect->y1 + y,
							color);
					}
				}
			}
			else
			{
				rtgui_blit_line_func blit_line;
				rt_uint8_t hw_bytePerPixel = _UI_BITBYTES(hw_driver->bits_per_pixel);
				rt_uint8_t *line_data;

				if (hw_driver->pixel_format == RTGRAPHIC_PIXEL_FORMAT_BGR565)
				{
					blit_line = rtgui_blit_line_get_inv(hw_bytePerPixel, bytePerPixel);
				}
				else
				{
					blit_line = rtgui_blit_line_get(hw_bytePerPixel, bytePerPixel);
				}

				line_data = (rt_uint8_t *)rtgui_malloc(w * rtgui_color_get_bpp(hw_driver->pixel_format));
				if (line_data == RT_NULL) break; /* out of memory */

				ptr = bmp->pixels;
				for (y = 0; y < h; y ++)
				{
					blit_line(line_data, ptr, bytePerPixel * w);
					ptr += imageWidth;

					dc->engine->blit_line(dc, dst_rect->x1, dst_rect->x1 + w,
						dst_rect->y1 + y, line_data);
				}

				rtgui_free(line_data);
			}
        }
    } while (0);
}

/*
 * config bitmap header.
 */
void rtgui_image_bmp_header_cfg(struct rtgui_image_bmp_header *bhr, rt_int32_t w, rt_int32_t h, rt_uint16_t bits_per_pixel)
{
    int image_size = w * h * _UI_BITBYTES(bits_per_pixel);
    int header_size = sizeof(struct rtgui_image_bmp_header);

    bhr->bfType = 0x4d42; /* BM */
    bhr->bfSize = header_size + image_size; /* data size */
    bhr->bfReserved1 = 0;
    bhr->bfReserved2 = 0;
    bhr->bfOffBits = header_size;

    bhr->biSize = 40; /* sizeof BITMAPINFOHEADER */
    bhr->biWidth = w;
    bhr->biHeight = h;
    bhr->biPlanes = 1;
    bhr->biBitCount = bits_per_pixel;
    bhr->biCompression = BI_BITFIELDS;
    bhr->biSizeImage = image_size;
    bhr->biXPelsPerMeter = 0;
    bhr->biYPelsPerMeter = 0;
    bhr->biClrUsed = 0;
    bhr->biClrImportant = 0;
    if (bhr->biBitCount == 16 && bhr->biCompression == BI_BITFIELDS)
    {
        bhr->bfSize += 12;
        bhr->bfOffBits += 12;
    }
}

#ifdef RTGUI_USING_DFS_FILERW
#define WRITE_CLUSTER_SIZE  2048
void bmp_align_write(struct rtgui_filerw *file, char *dest, char *src, rt_int32_t len, rt_int32_t *count)
{
    rt_int32_t len_bak = len;

    while (len)
    {
        if (*count >= WRITE_CLUSTER_SIZE)
        {
            rtgui_filerw_write(file, dest, WRITE_CLUSTER_SIZE, 1);
            *count = 0;
        }
        *(dest + *count) = *(src + (len_bak - len));
        len --;
        (*count) ++;
    }
}

/*
 * Grab screen and save as a BMP file
 * MACRO RGB_CONVERT_TO_BGR: If the pixel of colors is BGR mode, defined it.
 */
void screenshot(const char *filename)
{
    struct rtgui_filerw *file;
    int w, h, i, pitch;
    rt_uint16_t *src;
    rt_uint32_t mask;
    struct rtgui_image_bmp_header bhr;
    struct rtgui_graphic_driver *grp = hw_driver;
#ifdef RGB_CONVERT_TO_BGR
    int j;
    rt_uint16_t *line_buf;
    rt_uint16_t color, tmp;
#endif
    char *pixel_buf;
    rt_int32_t write_count = 0;

    file = rtgui_filerw_create_file(filename, "wb");
    if (file == RT_NULL)
    {
        rt_kprintf("create file failed\n");
        return;
    }

    w = grp->width;
    h = grp->height;

    pitch = w * sizeof(rt_uint16_t);
#ifdef RGB_CONVERT_TO_BGR
    line_buf = rt_malloc(pitch);
    if (line_buf == RT_NULL)
    {
        rt_kprintf("no memory!\n");
        return;
    }
#endif
    pixel_buf = rt_malloc(WRITE_CLUSTER_SIZE);
    if (pixel_buf == RT_NULL)
    {
        rt_kprintf("no memory!\n");
#ifdef RGB_CONVERT_TO_BGR
        rt_free(line_buf);
#endif
        return;
    }

    rtgui_image_bmp_header_cfg(&bhr, w, h, grp->bits_per_pixel);

    bmp_align_write(file, pixel_buf, (char *)&bhr,
                    sizeof(struct rtgui_image_bmp_header), &write_count);

    if (bhr.biCompression == BI_BITFIELDS)
    {
        mask = 0xF800; /* Red Mask */
        bmp_align_write(file, pixel_buf, (char *)&mask, 4, &write_count);
        mask = 0x07E0; /* Green Mask */
        bmp_align_write(file, pixel_buf, (char *)&mask, 4, &write_count);
        mask = 0x001F; /* Blue Mask */
        bmp_align_write(file, pixel_buf, (char *)&mask, 4, &write_count);
    }
    rtgui_screen_lock(RT_WAITING_FOREVER);
    if (grp->framebuffer != RT_NULL)
    {
        src = (rt_uint16_t *)grp->framebuffer;
        src += w * h;
        for (i = 0; i < h; i++)
        {
            src -= w;
#ifdef RGB_CONVERT_TO_BGR
            for (j = 0; j < w; j++)
            {
                tmp = *(src + j);
                color  = (tmp & 0x001F) << 11;
                color += (tmp & 0x07E0);
                color += (tmp & 0xF800) >> 11;

                *(line_buf + i) = color;
            }
            bmp_align_write(file, pixel_buf, (char *)line_buf, pitch, &write_count);
#else
            bmp_align_write(file, pixel_buf, (char *)src, pitch, &write_count);
#endif
        }
    }
    else
    {
        rtgui_color_t pixel_color;
        rt_uint16_t write_color;
        int x;
        for (i = h - 1; i >= 0; i--)
        {
            x = 0;
            if (i % 10 == 0)rt_kprintf(">", i);
            while (x < w)
            {
                grp->ops->get_pixel(&pixel_color, x, i);
                write_color = rtgui_color_to_565p(pixel_color);
                bmp_align_write(file, pixel_buf, (char *)&write_color,
                                sizeof(rt_uint16_t), &write_count);
                x++;
            }
        }
    }
    /* write The tail of the last */
    if (write_count < WRITE_CLUSTER_SIZE)
        rtgui_filerw_write(file, pixel_buf, write_count, 1);
    rtgui_screen_unlock();
#ifdef RGB_CONVERT_TO_BGR
    rt_free(line_buf);
#endif
    rt_free(pixel_buf);
    rt_kprintf("bmp create succeed.\n");
    rtgui_filerw_close(file);
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(screenshot, usage: screenshot(filename));
#endif
#endif

void rtgui_image_bmp_init()
{
    /* register bmp on image system */
    rtgui_image_register_engine(&rtgui_image_bmp_engine);
}
#endif
