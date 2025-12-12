/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __PSF_H__
#define __PSF_H__

#include <rtthread.h>

#define PSF1_MAGIC0             0x36
#define PSF1_MAGIC1             0x04

#define PSF1_MODE512            0x01
#define PSF1_MODEHASTAB         0x02
#define PSF1_MODEHASSEQ         0x04
#define PSF1_MAXMODE            0x05

#define PSF1_SEPARATOR          0xffff
#define PSF1_STARTSEQ           0xfffe

struct psf1_header
{
    rt_uint8_t magic[2];        /* Magic number */
    rt_uint8_t mode;            /* PSF font mode */
    rt_uint8_t charsize;        /* Character size */
};

#define PSF2_MAGIC0             0x72
#define PSF2_MAGIC1             0xb5
#define PSF2_MAGIC2             0x4a
#define PSF2_MAGIC3             0x86

/* bits used in flags */
#define PSF2_HAS_UNICODE_TABLE  0x01

/* max version recognized so far */
#define PSF2_MAXVERSION         0

/* UTF8 separators */
#define PSF2_SEPARATOR          0xff
#define PSF2_STARTSEQ           0xfe

struct psf2_header
{
    rt_uint8_t magic[4];
    rt_uint32_t version;
    rt_uint32_t headersize;     /* offset of bitmaps in file */
    rt_uint32_t flags;
    rt_uint32_t length;         /* number of glyphs */
    rt_uint32_t charsize;       /* number of bytes for each character, charsize = height * ((width + 7) / 8) */
    rt_uint32_t height, width;  /* max dimensions of glyphs */
};

enum psf_type
{
    PSF_TYPE_1,
    PSF_TYPE_2,
    PSF_TYPE_UNKNOW,
};

struct psf_font
{
    union
    {
        const rt_uint8_t *raw_data;
        struct psf1_header *header1;
        struct psf2_header *header2;
    };
    const rt_uint8_t *font_map;
    const rt_uint8_t *font_data;

    enum psf_type type;

    rt_uint32_t count;          /* fonts count */
    rt_uint32_t size;
    rt_uint32_t height;
    rt_uint32_t width;
    rt_uint32_t glyph;          /* height * width */
};

rt_err_t psf_initialize(const void *psf_data, struct psf_font *out_psf);
rt_err_t psf_parse(struct psf_font *psf, const rt_uint8_t *font_data,
        rt_uint8_t *tmpglyph, rt_uint32_t color_size,
        rt_uint32_t foreground, rt_uint32_t background);

#endif /* __PSF_H__ */
