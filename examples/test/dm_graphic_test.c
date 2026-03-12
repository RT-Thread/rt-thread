/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/misc.h>

#ifdef RT_USING_GRAPHIC
typedef rt_int32_t fixed;       /* Q16.16 */

#define FIX_ONE     65536
#define FIX_06      19661      /* 0.3 */
#define FIX_35      22938      /* 0.35 */
#define FIX_14      917504     /* 14.0 */
#define FIX_286     187432     /* 2.86 */
#define FIX_75      49152      /* 0.75 */
#define FIX_1_3     21845
#define FIX_2_3     43690
#define FIX_6       393216
#define FIX_3       196608
#define FIX_255     16711680   /* 255 */

#define FMUL(a,b)    ((fixed)(((rt_int64_t)(a) * (b)) >> 16))
#define FDIV(a,b)    ((fixed)(((rt_int64_t)(a) << 16) / (b)))

typedef struct { fixed x, y, z; } vec3f;

rt_inline fixed fix_floor(fixed x)
{
    return x & 0xffff0000;
}

rt_inline fixed fix_fract(fixed x)
{
    return x & 0x0000ffff;
}

rt_inline fixed fix_abs(fixed x)
{
    return rt_abs(x);
}

rt_inline fixed fix_clamp(fixed x, fixed a, fixed b)
{
    return rt_clamp(x, a, b);
}

static vec3f clamp3(vec3f v, fixed a, fixed b)
{
    vec3f r =
    {
        .x = fix_clamp(v.x, a, b),
        .y = fix_clamp(v.y, a, b),
        .z = fix_clamp(v.z, a, b),
    };

    return r;
}

static vec3f mix3(vec3f A, vec3f B, fixed t)
{
    fixed omt = FIX_ONE - t;
    vec3f r =
    {
        .x = FMUL(A.x, omt) + FMUL(B.x, t),
        .y = FMUL(A.y, omt) + FMUL(B.y, t),
        .z = FMUL(A.z, omt) + FMUL(B.z, t),
    };

    return r;
}

static vec3f hsv2rgb(vec3f c)
{
    vec3f t, r, base, mixed;
    fixed pX = FMUL(fix_fract(c.x + FIX_ONE), FIX_6);
    fixed pY = FMUL(fix_fract(c.x + FIX_2_3), FIX_6);
    fixed pZ = FMUL(fix_fract(c.x + FIX_1_3), FIX_6);

    pX = fix_abs(pX - FIX_3);
    pY = fix_abs(pY - FIX_3);
    pZ = fix_abs(pZ - FIX_3);

    t.x = pX - FIX_ONE;
    t.y = pY - FIX_ONE;
    t.z = pZ - FIX_ONE;
    t = clamp3(t, 0, FIX_ONE);

    base.x = FIX_ONE;
    base.y = FIX_ONE;
    base.z = FIX_ONE;

    mixed = mix3(base, t, c.y);

    r.x = FMUL(c.z, mixed.x);
    r.y = FMUL(c.z, mixed.y);
    r.z = FMUL(c.z, mixed.z);

    return r;
}

static void shader_frame(int px, int py, int width, int height, int frame,
    rt_uint8_t *r, rt_uint8_t *g, rt_uint8_t *b)
{
    vec3f col;
    fixed uv_x, uv_y, shift, size_computed, st, x;

    uv_x = FDIV((fixed)(px << 16), (fixed)(width << 16));
    uv_y = FDIV((fixed)(py << 16), (fixed)(width << 16));

    shift = fix_fract(FDIV(FMUL((frame << 16), FIX_06), FIX_286));
    shift = FMUL(shift, FIX_286);

    size_computed = FMUL(uv_x + shift - uv_y, FIX_35);

    st = FMUL(size_computed, FIX_14);
    x = FDIV(fix_floor(st), FIX_14);

    col = hsv2rgb((vec3f){ x, FIX_75, FIX_ONE });

    *r = (rt_uint8_t)((FMUL(col.x, FIX_255) >> 16) & 255);
    *g = (rt_uint8_t)((FMUL(col.y, FIX_255) >> 16) & 255);
    *b = (rt_uint8_t)((FMUL(col.z, FIX_255) >> 16) & 255);
}

static void conv_gray4(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    rt_uint8_t gray = (r * 30 + g * 59 + b * 11) / 100;
    *(rt_uint8_t *)pixel = gray >> 4;
}

static void conv_gray16(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    rt_uint16_t gray = (r * 30 + g * 59 + b * 11) / 100;
    rt_uint16_t out  = (gray << 8) | gray;
    *(rt_uint16_t *)pixel = out;
}

static void conv_rgb332(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    *(rt_uint8_t*)pixel = ((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6);
}

static void conv_rgb444(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    *(rt_uint16_t *)pixel = ((r >> 4) << 8) | ((g >> 4) << 4) | (b >> 4);
}

static void conv_rgb565(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    *(rt_uint16_t *)pixel = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

static void conv_rgb565p(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    *(rt_uint16_t *)pixel = ((g >> 2) << 10) | ((r >> 3) << 5) | (b >> 3);
}

static void conv_bgr565(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    *(rt_uint16_t *)pixel = ((b >> 3) << 11) | ((g >> 2) << 5) | (r >> 3);
}

static void conv_rgb666(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    rt_uint8_t *p = (rt_uint8_t *)pixel;

    p[0] = r & 0xfc;
    p[1] = g & 0xfc;
    p[2] = b & 0xfc;
}

static void conv_rgb888(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    rt_uint8_t *p = (rt_uint8_t *)pixel;

    p[0] = r;
    p[1] = g;
    p[2] = b;
}

static void conv_bgr888(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    rt_uint8_t *p = (rt_uint8_t*)pixel;
    p[0] = b;
    p[1] = g;
    p[2] = r;
}

static void conv_argb888(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    *(rt_uint32_t *)pixel = (0xffU << 24) | (r << 16) | (g << 8) | b;
}

static void conv_abgr888(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel)
{
    *(rt_uint32_t *)pixel = (0xffU << 24) | (b << 16) | (g << 8) | r;
}

static void (*conv_funcs[])(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel) =
{
    [RTGRAPHIC_PIXEL_FORMAT_GRAY4]      = conv_gray4,
    [RTGRAPHIC_PIXEL_FORMAT_GRAY16]     = conv_gray16,
    [RTGRAPHIC_PIXEL_FORMAT_RGB332]     = conv_rgb332,
    [RTGRAPHIC_PIXEL_FORMAT_RGB444]     = conv_rgb444,
    [RTGRAPHIC_PIXEL_FORMAT_RGB565]     = conv_rgb565,
    [RTGRAPHIC_PIXEL_FORMAT_RGB565P]    = conv_rgb565p,
    [RTGRAPHIC_PIXEL_FORMAT_BGR565]     = conv_bgr565,
    [RTGRAPHIC_PIXEL_FORMAT_RGB666]     = conv_rgb666,
    [RTGRAPHIC_PIXEL_FORMAT_RGB888]     = conv_rgb888,
    [RTGRAPHIC_PIXEL_FORMAT_BGR888]     = conv_bgr888,
    [RTGRAPHIC_PIXEL_FORMAT_ARGB888]    = conv_argb888,
    [RTGRAPHIC_PIXEL_FORMAT_ABGR888]    = conv_abgr888,
};

rt_err_t graphic_start(const char *gdev, int count)
{
    rt_err_t err;
    rt_uint8_t *vfb, *fb, *pixel, bpp;
    struct rt_device_graphic_info info;
    struct rt_device *dev = rt_device_find(gdev);
    void (*conv_func)(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b, void *pixel);

    if (!dev)
    {
        return -RT_EINVAL;
    }

    if ((err = rt_device_open(dev, 0)))
    {
        return err;
    }

    if ((err = rt_device_control(dev, RTGRAPHIC_CTRL_GET_INFO, &info)))
    {
        goto _end;
    }

    if (!(vfb = rt_malloc(info.smem_len)))
    {
        err = -RT_ENOMEM;
        goto _end;
    }

    bpp = info.bits_per_pixel / 8;
    conv_func = conv_funcs[info.pixel_format];

    for (int frame = 0; frame < count; ++frame)
    {
        fb = vfb;

        for (int y = 0; y < info.height; ++y)
        {
            pixel = fb;

            for (int x = 0; x < info.width; ++x)
            {
                rt_uint8_t r, g, b;

                shader_frame(x, y, info.width, info.height, frame, &r, &g, &b);

                conv_func(r, g, b, pixel);

                pixel += bpp;
            }

            fb += info.pitch;
        }

        rt_memcpy(info.framebuffer, vfb, info.smem_len);
    }

    rt_free(vfb);

_end:
    rt_device_close(dev);

    return err;
}

#ifdef RT_USING_FINSH
#include <stdlib.h>

static int _graphic_start(int argc, char**argv)
{
    int count = 10;
    const char *gdev = "fb0";

    if (argc > 1)
    {
        gdev = argv[1];
    }
    if (argc > 2)
    {
        count = atoi(argv[2]);
    }

    return (int)graphic_start(gdev, count);
}
MSH_CMD_EXPORT_ALIAS(_graphic_start, graphic_start, fixed resolution only e.g: graphic_start("fb0", 10));
#endif /* RT_USING_FINSH */
#endif /* RT_USING_GRAPHIC */
