/*
 * =====================================================================================
 *
 *       Filename:  fb.h
 *
 *    Description:  misc definition for display pixel format.
 *
 *        Version:  Melis3.0
 *         Create:  2017-11-03 11:38:28
 *       Revision:  none
 *       Compiler:  gcc version 6.3.0 (crosstool-NG crosstool-ng-1.23.0)
 *
 *         Author:  caozilong@allwinnertech.com
 *   Organization:  BU1-PSW
 *  Last Modified:  2019-03-29 17:49:54
 *
 * =====================================================================================
 */

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <typedef.h>
#include <kconfig.h>

typedef enum __PIXEL_YUVFMT
{
    PIXEL_YUV444                = 0x71,
    PIXEL_YUV422,
    PIXEL_YUV420,
    PIXEL_YUV411,
    PIXEL_CSIRGB,
    PIXEL_OTHERFMT,
} __pixel_yuvfmt_t;

typedef enum __YUV_MODE
{
    YUV_MOD_INTERLEAVED         = 0,
    YUV_MOD_NON_MB_PLANAR,
    YUV_MOD_MB_PLANAR,
    YUV_MOD_UV_NON_MB_COMBINED,
    YUV_MOD_UV_MB_COMBINED
} __yuv_mod_t;

typedef enum
{
    YUV_SEQ_UYVY                = 0,
    YUV_SEQ_YUYV,
    YUV_SEQ_VYUY,
    YUV_SEQ_YVYU,
    YUV_SEQ_AYUV                = 0x10,
    YUV_SEQ_VUYA,
    YUV_SEQ_UVUV                = 0x20,
    YUV_SEQ_VUVU,
    YUV_SEQ_OTHRS               = 0xff,
} __yuv_seq_t;


typedef struct
{
    __u32 width;
    __u32 height;
} SIZE;

typedef enum
{
    BT601                       = 0,
    BT709,
    YCC,
    VXYCC,
    MONO
} __cs_mode_t;

typedef struct
{
    __s32 x;
    __s32 y;
    __u32 width;
    __u32 height;
} RECT;

typedef enum
{
    FB_TYPE_RGB                 = 0,
    FB_TYPE_YUV                 = 1
} __fb_type_t;

typedef enum __PIXEL_RGBFMT
{
    PIXEL_MONO_1BPP             = 0x51,
    PIXEL_MONO_2BPP,
    PIXEL_MONO_4BPP,
    PIXEL_MONO_8BPP,
    PIXEL_COLOR_RGB655,
    PIXEL_COLOR_RGB565,
    PIXEL_COLOR_RGB556,
    PIXEL_COLOR_ARGB1555,
    PIXEL_COLOR_RGBA5551,
    PIXEL_COLOR_RGB0888,
    PIXEL_COLOR_ARGB8888,
} __pixel_rgbfmt_t;

typedef enum
{
    RGB_SEQ_ARGB                = 0x00,//for 32bpp
    RGB_SEQ_BRGA                = 0x02,
    RGB_SEQ_P10                 = 0x10,//for 16bpp
    RGB_SEQ_P01                 = 0x11,
    RGB_SEQ_P3210               = 0x20,//for 8bpp
    RGB_SEQ_P0123               = 0x21,
    RGB_SEQ_P76543210           = 0x30,//for 4bpp
    RGB_SEQ_P67452301           = 0x31,
    RGB_SEQ_P10325476           = 0x32,
    RGB_SEQ_P01234567           = 0x33,
    RGB_SEQ_2BPP_BIG_BIG        = 0x40,//for 2bpp
    RGB_SEQ_2BPP_BIG_LITTER     = 0x41,
    RGB_SEQ_2BPP_LITTER_BIG     = 0x42,
    RGB_SEQ_2BPP_LITTER_LITTER  = 0x43,
    RGB_SEQ_1BPP_BIG_BIG        = 0x50,//for 1bpp
    RGB_SEQ_1BPP_BIG_LITTER     = 0x51,
    RGB_SEQ_1BPP_LITTER_BIG     = 0x52,
    RGB_SEQ_1BPP_LITTER_LITTER  = 0x53,
} __rgb_seq_t;

typedef struct
{
    __fb_type_t                 type;
    union
    {
        struct
        {
            __pixel_rgbfmt_t    pixelfmt;
            __bool              br_swap;
            __rgb_seq_t         pixseq;
            struct
            {
                void            *addr;
                __u32           size;
            } palette;
        } rgb;
        struct
        {
            __pixel_yuvfmt_t    pixelfmt;
            __yuv_mod_t         mod;
            __yuv_seq_t         yuvseq;
        } yuv;
    } fmt;
    __cs_mode_t                 cs_mode;
} __fb_format_t;


typedef struct __FB
{
    SIZE                        size;
    void                        *addr[3];
    __fb_format_t               fmt;
} FB;

typedef struct
{
    __u8    alpha;
    __u8    red;
    __u8    green;
    __u8    blue;
} COLOR;        /* 32-bit (ARGB) color                  */

typedef struct
{
    __s32 x;
    __s32 y;
} OFFSET;       /* coordinate (x, y)                    */

typedef COLOR  __color_t;
typedef RECT   __rect_t;
typedef OFFSET __pos_t;
typedef SIZE   __rectsz_t;

#endif  /*FRAMEBUFFER_H*/
