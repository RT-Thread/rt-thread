/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-05     bernard      first version.
 */

#ifndef RT_LCD_H__
#define RT_LCD_H__

/* ioctls
   0x46 is 'F'                                                          */

#define FBIOGET_VSCREENINFO     0x4600
#define FBIOPUT_VSCREENINFO     0x4601
#define FBIOGET_FSCREENINFO     0x4602
#define FBIOGETCMAP             0x4604
#define FBIOPUTCMAP             0x4605
#define FBIOPAN_DISPLAY         0x4606
#define FBIO_CURSOR             0x4608
/* #define FBIOGET_MONITORSPEC  0x460C */
/* #define FBIOPUT_MONITORSPEC  0x460D */
/* #define FBIOSWITCH_MONIBIT   0x460E */

#define FBIOGET_CON2FBMAP       0x460F
#define FBIOPUT_CON2FBMAP       0x4610
#define FBIOBLANK               0x4611          /* arg: 0 or vesa level + 1 */
#define FBIOGET_VBLANK          0x4612
#define FBIO_ALLOC              0x4613
#define FBIO_FREE               0x4614
#define FBIOGET_GLYPH           0x4615
#define FBIOGET_HWCINFO         0x4616
#define FBIOPUT_MODEINFO        0x4617
#define FBIOGET_DISPINFO        0x4618
#define FBIO_WAITFORVSYNC       0x4620

struct fb_bitfield
{
    uint32_t offset;        /* beginning of bitfield */
    uint32_t length;        /* length of bitfield */
    uint32_t msb_right;     /* != 0 : Most significant bit is */
    /* right */
};

struct fb_var_screeninfo
{
    uint32_t xres;               /* visible resolution */
    uint32_t yres;
    uint32_t xres_virtual;       /* virtual resolution  */
    uint32_t yres_virtual;
    uint32_t xoffset;            /* offset from virtual to visible */
    uint32_t yoffset;            /* resolution */

    uint32_t bits_per_pixel;     /* guess what */
    uint32_t grayscale;          /* 0 = color, 1 = grayscale, */
    /* >1 = FOURCC */
    struct fb_bitfield red;      /* bitfield in fb mem if true color, */
    struct fb_bitfield green;    /* else only length is significant */
    struct fb_bitfield blue;
    struct fb_bitfield transp;   /* transparency */

    uint32_t nonstd;             /* != 0 Non standard pixel format */

    uint32_t activate;           /* see FB_ACTIVATE_* */

    uint32_t height;             /* height of picture in mm */
    uint32_t width;              /* width of picture in mm */

    uint32_t accel_flags;        /* (OBSOLETE) see fb_info.flags */

    /* Timing: All values in pixclocks, except pixclock (of course) */
    uint32_t pixclock;          /* pixel clock in ps (pico seconds) */
    uint32_t left_margin;       /* time from sync to picture */
    uint32_t right_margin;      /* time from picture to sync */
    uint32_t upper_margin;      /* time from sync to picture */
    uint32_t lower_margin;
    uint32_t hsync_len;         /* length of horizontal sync */
    uint32_t vsync_len;         /* length of vertical sync */
    uint32_t sync;              /* see FB_SYNC_* */
    uint32_t vmode;             /* see FB_VMODE_* */
    uint32_t rotate;            /* angle we rotate counter clockwise */
    uint32_t colorspace;        /* colorspace for FOURCC-based modes */
    uint32_t reserved[4];       /* Reserved for future compatibility */
};

struct fb_fix_screeninfo
{
    char id[16];               /* identification string eg "TT Builtin" */
    unsigned long smem_start;  /* Start of frame buffer mem */
    /* (physical address) */
    uint32_t smem_len;         /* Length of frame buffer mem */
    uint32_t type;             /* see FB_TYPE_* */
    uint32_t type_aux;         /* Interleave for interleaved Planes */
    uint32_t visual;           /* see FB_VISUAL_* */
    uint16_t xpanstep;         /* zero if no hardware panning */
    uint16_t ypanstep;         /* zero if no hardware panning */
    uint16_t ywrapstep;        /* zero if no hardware ywrap */
    uint32_t line_length;      /* length of a line in bytes */
    unsigned long mmio_start;  /* Start of Memory Mapped I/O */
    /* (physical address) */
    uint32_t mmio_len;         /* Length of Memory Mapped I/O */
    uint32_t accel;            /* Indicate to driver which */
    /*  specific chip/card we have  */
    uint16_t capabilities;     /* see FB_CAP_* */
    uint16_t reserved[2];      /* Reserved for future compatibility */
};

#endif
