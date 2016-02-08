#include <rtthread.h>
#include <rtgui/dc_hw.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/image_hdc.h>
#include <rtgui/blit.h>

#define HDC_MAGIC_LEN       4

extern int fastlz_decompress(const void *input, int length, void *output, int maxout);

struct rtgui_image_hdc
{
    rt_bool_t is_loaded;

    /* hdc image information */
    rt_uint16_t byte_per_pixel;
    rt_uint16_t pitch;
    rt_uint8_t  pixel_format;

    rt_size_t   pixel_offset;
    rt_uint8_t *pixels;

    struct rtgui_filerw *filerw;
};

static rt_bool_t rtgui_image_hdc_check(struct rtgui_filerw *file);
static rt_bool_t rtgui_image_hdc_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load);
static void rtgui_image_hdc_unload(struct rtgui_image *image);
static void rtgui_image_hdc_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect);
static void rtgui_image_hdcmm_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *dst_rect);

struct rtgui_image_engine rtgui_image_hdc_engine =
{
    "hdc",
    { RT_NULL },
    rtgui_image_hdc_check,
    rtgui_image_hdc_load,
    rtgui_image_hdc_unload,
    rtgui_image_hdc_blit,
};

const struct rtgui_image_engine rtgui_image_hdcmm_engine =
{
    "hdcmm",
    {RT_NULL},
    RT_NULL,
    RT_NULL,
    RT_NULL,
    rtgui_image_hdcmm_blit,
};

static rt_bool_t rtgui_image_hdc_check(struct rtgui_filerw *file)
{
    int start;
    rt_bool_t is_HDC;
    rt_uint8_t magic[4];

    if (!file) return 0;

    start = rtgui_filerw_tell(file);

    /* move to the beginning of file */
    rtgui_filerw_seek(file, 0, RTGUI_FILE_SEEK_SET);

    is_HDC = RT_FALSE;
    if (rtgui_filerw_read(file, magic, 1, sizeof(magic)) == sizeof(magic))
    {
        if (magic[0] == 'H' &&
                magic[1] == 'D' &&
                magic[2] == 'C' &&
                magic[3] == '\0')
        {
            is_HDC = RT_TRUE;
        }
    }
    rtgui_filerw_seek(file, start, RTGUI_FILE_SEEK_SET);

    return (is_HDC);
}

static rt_bool_t rtgui_image_hdc_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load)
{
    rt_uint32_t header[5];
    struct rtgui_image_hdc *hdc;

    hdc = (struct rtgui_image_hdc *) rtgui_malloc(sizeof(struct rtgui_image_hdc));
    if (hdc == RT_NULL) return RT_FALSE;

    rtgui_filerw_read(file, (char *)&header, 1, sizeof(header));

    /* set image information */
    image->w = (rt_uint16_t)header[1];
    image->h = (rt_uint16_t)header[2];
    image->engine = &rtgui_image_hdc_engine;
    image->data = hdc;
    hdc->pixel_format = header[3];
    hdc->filerw = file;
    if (header[3] == 0)
    {
        /* 0.x version */
        hdc->pixel_format = rtgui_graphic_driver_get_default()->pixel_format;
    }
    else if (header[3] == 1)
    {
        /* 1.x version */
        hdc->pixel_format = header[4];
    }
    else if (header[3] == 2)
    {
        /* 2.x version */
        hdc->pixel_format = header[4];
    }

    hdc->byte_per_pixel = rtgui_color_get_bpp(hdc->pixel_format);
    hdc->pitch = image->w * hdc->byte_per_pixel;
    hdc->pixel_offset = rtgui_filerw_tell(file);

    if (load == RT_TRUE)
    {
        if (header[3] == 2)
        {
#if 0   /* TODO: add HDC with fastlz compressed */
            int data_length, dec_length;
            rt_uint8_t *data;

            data_length = rtgui_filerw_seek(hdc->filerw, 0, SEEK_END) - sizeof(header);
            rtgui_filerw_seek(hdc->filerw, sizeof(header), SEEK_SET);

            data = (rt_uint8_t *)rtgui_malloc(data_length);
            if (data == RT_NULL)
            {
                /* release data */
                rtgui_free(hdc);
                return RT_FALSE;
            }

            if (rtgui_filerw_read(hdc->filerw, data, 1, data_length) != data_length)
            {
                rtgui_filerw_close(hdc->filerw);
                /* release data */
                rtgui_free(hdc);
                return RT_FALSE;
            }
            rtgui_filerw_close(hdc->filerw);
            hdc->filerw = RT_NULL;

            hdc->pixels = (rt_uint8_t *)rtgui_malloc(image->h * hdc->pitch);
            if (hdc->pixels == RT_NULL)
            {
                /* release data */
                rtgui_free(hdc);
                rtgui_free(data);
                return RT_FALSE;
            }

            dec_length = fastlz_decompress(data, data_length, hdc->pixels, image->h * hdc->pitch);
            if (dec_length != image->h * hdc->pitch)
            {
                /* release data */
                rtgui_free(hdc->pixels);
                rtgui_free(hdc);
                rtgui_free(data);
                return RT_FALSE;
            }
            hdc->pixel_offset = 0;
            rtgui_free(data);
#endif
        }
        else
        {
            /* load all pixels */
            hdc->pixels = rtgui_malloc(image->h * hdc->pitch);
            if (hdc->pixels == RT_NULL)
            {
                /* release data */
                rtgui_free(hdc);
                return RT_FALSE;
            }

            rtgui_filerw_read(hdc->filerw, hdc->pixels, 1, image->h * hdc->pitch);
            rtgui_filerw_close(hdc->filerw);
            hdc->filerw = RT_NULL;
            hdc->pixel_offset = 0;
        }
    }
    else
    {
        hdc->pixels = RT_NULL;
    }

    return RT_TRUE;
}

static void rtgui_image_hdc_unload(struct rtgui_image *image)
{
    struct rtgui_image_hdc *hdc;

    if (image != RT_NULL)
    {
        hdc = (struct rtgui_image_hdc *) image->data;

        if (hdc->pixels != RT_NULL)
            rtgui_free(hdc->pixels);
        if (hdc->filerw != RT_NULL)
            rtgui_filerw_close(hdc->filerw);

        /* release data */
        rtgui_free(hdc);
    }
}

static void rtgui_image_hdc_blit(struct rtgui_image *image,
                                 struct rtgui_dc *dc,
                                 struct rtgui_rect *dst_rect)
{
    rt_int16_t y, w, h, xoff, yoff;
    struct rtgui_image_hdc *hdc;

    RT_ASSERT(image != RT_NULL || dc != RT_NULL || dst_rect != RT_NULL);

    /* this dc is not visible */
    if (rtgui_dc_get_visible(dc) != RT_TRUE)
        return;

    if (!image)
        return;

    hdc = (struct rtgui_image_hdc *) image->data;
    RT_ASSERT(hdc != RT_NULL);

    xoff = 0;
    if (dst_rect->x1 < 0)
    {
        xoff = -dst_rect->x1;
        dst_rect->x1 = 0;
    }
    yoff = 0;
    if (dst_rect->y1 < 0)
    {
        yoff = -dst_rect->y1;
        dst_rect->y1 = 0;
    }

    if (dst_rect->x2 <= 0 || dst_rect->y2 <= 0)
        return;

    if (xoff >= image->w || yoff >= image->h)
        return;

    /* the minimum rect */
    w = _UI_MIN(image->w - xoff, rtgui_rect_width(*dst_rect));
    h = _UI_MIN(image->h - yoff, rtgui_rect_height(*dst_rect));

    if (w == 0 || h == 0)
        return;

    if (hdc->pixels != RT_NULL)
    {
        rt_uint8_t *ptr;

        /* get pixel pointer */
        ptr = hdc->pixels + hdc->pitch * yoff + hdc->byte_per_pixel * xoff;

        if (hdc->pixel_format == rtgui_dc_get_pixel_format(dc) &&
                hdc->pixel_format != RTGRAPHIC_PIXEL_FORMAT_ARGB888)
        {
            for (y = 0; y < h; y ++)
            {
                dc->engine->blit_line(dc,
                                      dst_rect->x1,
                                      dst_rect->x1 + w,
                                      dst_rect->y1 + y,
                                      ptr);
                ptr += hdc->pitch;
            }
        }
        else if (dc->type == RTGUI_DC_CLIENT)
        {
            const struct rtgui_graphic_driver *hw_driver;
            struct rtgui_widget *owner = RTGUI_CONTAINER_OF(dc, struct rtgui_widget, dc_type);

            hw_driver = rtgui_graphic_driver_get_default();
            if (hdc->pixel_format == RTGRAPHIC_PIXEL_FORMAT_ARGB888)
            {
                rt_uint8_t alpha;

                for (y = 0; y < h; y ++)
                {
                    int x;

                    rtgui_color_t *pixel = (rtgui_color_t *)(hdc->pixels + hdc->pitch * (yoff + y) + hdc->byte_per_pixel * xoff);

                    for (x = 0; x < w; x ++)
                    {
                        alpha = RTGUI_RGB_A(*pixel);

                        if (alpha == 0) { }
                        if (alpha == 0xff)
                        {
                            rtgui_dc_draw_color_point(dc, dst_rect->x1 + x, dst_rect->y1 + y, *pixel);
                        }
                        else
                        {
                            /* draw an alpha blending point */
                            if (hw_driver->framebuffer != RT_NULL)
                                rtgui_dc_blend_point(dc, dst_rect->x1 + x, dst_rect->y1 + y, RTGUI_BLENDMODE_BLEND,
                                                     RTGUI_RGB_R(*pixel), RTGUI_RGB_G(*pixel), RTGUI_RGB_B(*pixel), RTGUI_RGB_A(*pixel));
                        }

                        pixel ++;
                    }
                }
            }
        }
        else
        {
            struct rtgui_blit_info info;
            info.a = 0;

            /* initialize source blit information */
            info.src = ptr;
            info.src_h = h;
            info.src_w = w;
            info.src_fmt = hdc->pixel_format;
            info.src_pitch = hdc->pitch;
            info.src_skip = hdc->pitch - w * rtgui_color_get_bpp(hdc->pixel_format);

            /* initialize destination blit information */
            if (dc->type == RTGUI_DC_BUFFER)
            {
                struct rtgui_dc_buffer *buffer;
                buffer = (struct rtgui_dc_buffer *)dc;

                info.dst = rtgui_dc_buffer_get_pixel(RTGUI_DC(buffer)) + dst_rect->y1 * buffer->pitch +
                           dst_rect->x1 * rtgui_color_get_bpp(buffer->pixel_format);
                info.dst_h = h;
                info.dst_w = w;
                info.dst_fmt = buffer->pixel_format;
                info.dst_pitch = buffer->pitch;
                info.dst_skip = info.dst_pitch - info.dst_w * rtgui_color_get_bpp(buffer->pixel_format);
            }
            else if (dc->type == RTGUI_DC_HW)
            {
                struct rtgui_widget *owner;
                struct rtgui_rect r;
                struct rtgui_dc_hw *ddc = (struct rtgui_dc_hw *)dc;

                owner = ((struct rtgui_dc_hw *)dc)->owner;

                rtgui_graphic_driver_get_rect(RT_NULL, &r);

                /* blit destination */
                info.dst = (rt_uint8_t *)ddc->hw_driver->framebuffer;
                info.dst = info.dst + (owner->extent.y1 + dst_rect->y1) * ddc->hw_driver->pitch +
                           (owner->extent.x1 + dst_rect->x1) * rtgui_color_get_bpp(ddc->hw_driver->pixel_format);
                info.dst_fmt = ddc->hw_driver->pixel_format;
                info.dst_h = h;
                info.dst_w = w;
                info.dst_pitch = ddc->hw_driver->pitch;
                info.dst_skip = info.dst_pitch - info.dst_w * rtgui_color_get_bpp(ddc->hw_driver->pixel_format);
            }

            rtgui_blit(&info);
        }
    }
    else
    {
        rt_uint8_t *ptr;
        ptr = rtgui_malloc(hdc->byte_per_pixel * w);
        if (ptr == RT_NULL)
            return; /* no memory */

        /* seek to the begin of pixel data */
        rtgui_filerw_seek(hdc->filerw,
                          hdc->pixel_offset + hdc->pitch * yoff + hdc->byte_per_pixel * xoff,
                          RTGUI_FILE_SEEK_SET);

        for (y = 0; y < h; y ++)
        {
            /* read pixel data */
            if (rtgui_filerw_read(hdc->filerw, ptr, 1,
                                  hdc->byte_per_pixel * w) != hdc->byte_per_pixel * w)
                break; /* read data failed */

            dc->engine->blit_line(dc,
                                  dst_rect->x1,
                                  dst_rect->x1 + w,
                                  dst_rect->y1 + y,
                                  ptr);
            rtgui_filerw_seek(hdc->filerw, hdc->byte_per_pixel * xoff, RTGUI_FILE_SEEK_CUR);
        }

        rtgui_free(ptr);
    }
}

static void rtgui_image_hdcmm_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *dst_rect)
{
    rt_uint8_t *ptr;
    rt_uint16_t y, w, h, xoff, yoff;
    struct rtgui_image_hdcmm *hdc;

    RT_ASSERT(image != RT_NULL && dc != RT_NULL && dst_rect != RT_NULL);

    /* this dc is not visible */
    if (rtgui_dc_get_visible(dc) != RT_TRUE)
        return;

    hdc = (struct rtgui_image_hdcmm *) image;
    if (!hdc->pixels)
        return;

    xoff = 0;
    if (dst_rect->x1 < 0)
    {
        xoff = -dst_rect->x1;
        dst_rect->x1 = 0;
    }
    yoff = 0;
    if (dst_rect->y1 < 0)
    {
        yoff = -dst_rect->y1;
        dst_rect->y1 = 0;
    }

    if (xoff >= image->w || yoff >= image->h)
        return;

    /* the minimum rect */
    w = _UI_MIN(image->w - xoff, rtgui_rect_width(*dst_rect));
    h = _UI_MIN(image->h - yoff, rtgui_rect_height(*dst_rect));

    /* get pixel pointer */
    ptr = hdc->pixels + hdc->pitch * yoff + hdc->byte_per_pixel * xoff;

    for (y = 0; y < h; y++)
    {
        dc->engine->blit_line(dc, dst_rect->x1, dst_rect->x1 + w, dst_rect->y1 + y, ptr);
        ptr += hdc->pitch;
    }
}

void rtgui_image_hdc_init()
{
    /* register hdc on image system */
    rtgui_image_register_engine(&rtgui_image_hdc_engine);
}

