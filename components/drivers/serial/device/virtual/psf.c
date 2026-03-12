/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include "psf.h"

static void psf_read_header(struct psf_font *psf)
{
    if (psf->header1->magic[0] == PSF1_MAGIC0 &&
        psf->header1->magic[1] == PSF1_MAGIC1)
    {
        psf->font_map = (void *)&psf->header1[1];
        psf->type = PSF_TYPE_1;

        if (psf->header1->mode & PSF1_MODE512)
        {
            psf->count = 512;
        }
        else
        {
            psf->count = 256;
        }

        psf->size = psf->header1->charsize;
        psf->height = psf->header1->charsize;
        psf->width = 8;
    }
    else if (psf->header2->magic[0] == PSF2_MAGIC0 &&
            psf->header2->magic[1] == PSF2_MAGIC1 &&
            psf->header2->magic[2] == PSF2_MAGIC2 &&
            psf->header2->magic[3] == PSF2_MAGIC3)
    {
        psf->font_map = (void *)&psf->header2[1];
        psf->type = PSF_TYPE_2;
        psf->count = psf->header2->length;
        psf->size = psf->header2->charsize;
        psf->height = psf->header2->height;
        psf->width = psf->header2->width;
    }
    else
    {
        psf->type = PSF_TYPE_UNKNOW;
    }

    psf->glyph = psf->height * psf->width;
}

rt_err_t psf_initialize(const void *psf_data, struct psf_font *out_psf)
{
    struct psf_font *psf = out_psf;

    psf->raw_data = psf_data;
    psf_read_header(psf);

    if (psf->type == PSF_TYPE_UNKNOW)
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

rt_err_t psf_parse(struct psf_font *psf, const rt_uint8_t *font_data,
        rt_uint8_t *tmpglyph, rt_uint32_t color_size,
        rt_uint32_t foreground, rt_uint32_t background)
{
    rt_uint8_t *font = (void *)font_data, *map = (void *)psf->font_map;

    psf->font_data = font_data;

    for (int n = 0; n < psf->count; ++n, map += psf->size)
    {
        rt_memcpy(tmpglyph, map, psf->size);

        for (int i = 0; i < psf->size; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                if (i % (psf->size / psf->height) * 8 + j < psf->width)
                {
                    if (tmpglyph[i] & 0x80)
                    {
                        rt_memcpy(font, &foreground, color_size);
                    }
                    else
                    {
                        rt_memcpy(font, &background, color_size);
                    }

                    font += color_size;
                }

                tmpglyph[i] = tmpglyph[i] << 1;
            }
        }
    }

    return RT_EOK;
}
