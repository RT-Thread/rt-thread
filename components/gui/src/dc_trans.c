#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/dc.h>
#include <rtgui/dc_trans.h>

struct rtgui_dc_trans
{
    struct rtgui_matrix m;
    struct rtgui_dc *owner;
    int use_aa;
};

struct rtgui_dc_trans* rtgui_dc_trans_create(struct rtgui_dc *owner)
{
    struct rtgui_dc_trans *dct;

    dct = (struct rtgui_dc_trans*)rtgui_malloc(sizeof(*dct));
    if (!dct)
        return RT_NULL;

    rtgu_matrix_identity(&dct->m);
    dct->owner  = owner;
    dct->use_aa = 0;

    return dct;
}
RTM_EXPORT(rtgui_dc_trans_create);

void rtgui_dc_trans_destroy(struct rtgui_dc_trans *dct)
{
    rtgui_free(dct);
}
RTM_EXPORT(rtgui_dc_trans_destroy);

void rtgui_dc_trans_set_aa(struct rtgui_dc_trans *dct, int use_aa)
{
    RT_ASSERT(dct);

    dct->use_aa = use_aa;
}
RTM_EXPORT(rtgui_dc_trans_set_aa);

void rtgui_dc_trans_rotate(struct rtgui_dc_trans *dct, double degree)
{
    RT_ASSERT(dct);

    rtgui_matrix_rotate(&dct->m, degree * RTGUI_MATRIX_FRAC / 360.0);
}
RTM_EXPORT(rtgui_dc_trans_rotate);

void rtgui_dc_trans_scale(struct rtgui_dc_trans *dct,
                          double sx,
                          double sy)
{
    RT_ASSERT(dct);

    rtgui_matrix_scale(&dct->m, sx * RTGUI_MATRIX_FRAC, sy * RTGUI_MATRIX_FRAC);
}
RTM_EXPORT(rtgui_dc_trans_scale);

void rtgui_dc_trans_move(struct rtgui_dc_trans *dct,
                         int dx,
                         int dy)
{
    RT_ASSERT(dct);

    rtgui_matrix_move(&dct->m, dx, dy);
}
RTM_EXPORT(rtgui_dc_trans_move);

void rtgui_dc_trans_get_new_wh(struct rtgui_dc_trans *dct,
                               int *new_wp,
                               int *new_hp)
{
    struct rtgui_rect rect;
    struct rtgui_point topleft, topright, bottomright;

    RT_ASSERT(dct);

    if (!new_wp && !new_hp)
        return;

    rtgui_dc_get_rect(dct->owner, &rect);

    /* We ignore the movement components in the matrix. */
    /* Transform result of (0, h). */
    rtgui_matrix_mul_point_nomove(&topleft, 0, rect.y2,
                                  &dct->m);
    /* Transform result of (w, h). */
    rtgui_matrix_mul_point_nomove(&topright, rect.x2, rect.y2,
                                  &dct->m);
    /* Transform result of (w, 0). */
    rtgui_matrix_mul_point_nomove(&bottomright,
                                   rect.x2, 0, &dct->m);
    /* Transform result of (0, 0) is always (0, 0). */

#define NORMALIZE(x) do { if (x < 0) x = 0; } while (0)
    if (new_wp)
    {
        int neww;

        /* Ignore the nagtive parts. */
        NORMALIZE(topright.x);
        NORMALIZE(topleft.x);
        NORMALIZE(bottomright.x);

        neww = _UI_MAX(topright.x, _UI_ABS(topleft.x - bottomright.x))
            + dct->m.m[4];
        NORMALIZE(neww);

        *new_wp = neww;
    }
    if (new_hp)
    {
        int newh;

        NORMALIZE(topright.y);
        NORMALIZE(topleft.y);
        NORMALIZE(bottomright.y);

        newh = _UI_MAX(topright.y, _UI_ABS(topleft.y - bottomright.y))
            + dct->m.m[5];
        NORMALIZE(newh);

        *new_hp = newh;
    }
#undef NORMALIZE
}
RTM_EXPORT(rtgui_dc_trans_get_new_wh);

struct _fb_rect
{
    void *fb;
    /* unit: pixel */
    rt_uint16_t width, height;
    /* unit: pixel */
    rt_uint16_t skip;
};

/* FrameRect to FrameRect, same format, 2 Bytes/pixel. */
static void _blit_rotate_FR2FR_SF2B(struct _fb_rect* RTGUI_RESTRICT src,
                                    const struct rtgui_point *dc_point,
                                    struct _fb_rect* RTGUI_RESTRICT dst,
                                    const struct rtgui_matrix *invm)
{
    rt_uint16_t* RTGUI_RESTRICT srcp = (rt_uint16_t*)src->fb;
    rt_uint16_t* RTGUI_RESTRICT dstp = (rt_uint16_t*)dst->fb;
    int neww = dst->width;
    int newh = dst->height;
    int oriw = src->width;
    int orih = src->height;
    int nx, ny;
    int dx, dy;

    /* Delta of bx/by when nx++. */
    dx = invm->m[0];
    dy = invm->m[1];

    for (ny = dc_point->y; ny < newh; ny++)
    {
        /* Base x, y. */
        int bx, by;

        bx = dc_point->x * dx + ny * invm->m[2] + RTGUI_MATRIX_FRAC * invm->m[4];
        by = dc_point->x * dy + ny * invm->m[3] + RTGUI_MATRIX_FRAC * invm->m[5];

        for (nx = dc_point->x; nx < neww; nx++, dstp++)
        {
            /* The coordinate in the source frame. */
            int rx, ry;

            bx += dx;
            by += dy;

            if (bx < 0 || by < 0)
                continue;

            rx = bx / RTGUI_MATRIX_FRAC;
            ry = by / RTGUI_MATRIX_FRAC;

            if (oriw <= rx || orih <= ry)
                continue;

            /* We take the source as a whole and ignore the src->skip. */
            *dstp = srcp[ry * oriw + rx];
        }
        dstp += dst->skip - neww;
    }
}

/* FrameRect to FrameRect, same format, 2 Bytes/pixel, with AA. */
static void _blit_rotate_FR2FR_SF2B_AA(struct _fb_rect* RTGUI_RESTRICT src,
                                       const struct rtgui_point *dc_point,
                                       struct _fb_rect* RTGUI_RESTRICT dst,
                                       const struct rtgui_matrix *invm)
{
    rt_uint16_t* RTGUI_RESTRICT srcp = (rt_uint16_t*)src->fb;
    rt_uint16_t* RTGUI_RESTRICT dstp = (rt_uint16_t*)dst->fb;
    int neww = dst->width;
    int newh = dst->height;
    int oriw = src->width;
    int orih = src->height;
    int nx, ny;
    int dx, dy;

    dx = invm->m[0];
    dy = invm->m[1];

    for (ny = dc_point->y; ny < newh; ny++)
    {
        /* Base x, y. */
        int bx, by;

        bx = dc_point->x * dx + ny * invm->m[2] + RTGUI_MATRIX_FRAC * invm->m[4];
        by = dc_point->x * dy + ny * invm->m[3] + RTGUI_MATRIX_FRAC * invm->m[5];

        for (nx = dc_point->x; nx < neww; nx++, dstp++)
        {
            /* Color of pixels:
             *     c00 c01
             *     c10 c11     */
            rt_uint32_t c00, c01, c10, c11;
            int rx, ry, sx, sy;

            bx += dx;
            by += dy;

            if (bx < 0 || by < 0)
                continue;

            rx = bx / RTGUI_MATRIX_FRAC;
            ry = by / RTGUI_MATRIX_FRAC;

            if (oriw - 1 <= rx || orih - 1 <= ry)
                continue;

            c00 = srcp[ry * oriw + rx];
            c01 = srcp[ry * oriw + rx + 1];
            c10 = srcp[(ry + 1) * oriw + rx];
            c11 = srcp[(ry + 1) * oriw + rx + 1];

            c00 = (c00 | c00 << 16) & 0x07e0f81f;
            c01 = (c01 | c01 << 16) & 0x07e0f81f;
            c10 = (c10 | c10 << 16) & 0x07e0f81f;
            c11 = (c11 | c11 << 16) & 0x07e0f81f;

            /* We down scale the interpolate factor to 5 bits to avoid color
             * corruption. */
            sx = ((unsigned int)bx % RTGUI_MATRIX_FRAC) >> (RTGUI_MATRIX_FRAC_BITS - 5);
            sy = ((unsigned int)by % RTGUI_MATRIX_FRAC) >> (RTGUI_MATRIX_FRAC_BITS - 5);

            if (sx)
                c00 = ((c01 - c00) * sx / 32 + c00) & 0x07e0f81f;
            if (sx && sy)
                c10 = ((c11 - c10) * sx / 32 + c10) & 0x07e0f81f;
            if (sy)
                c00 = ((c10 - c00) * sy / 32 + c00) & 0x07e0f81f;

            /* We take the source as a whole and ignore the src->skip. */
            *dstp = c00 | (c00 >> 16);
        }
        dstp += dst->skip - neww;
    }
}

union _rgba
{
    rt_uint32_t blk;
    struct
    {
        rt_uint8_t r, g, b, a;
    } d;
};

/* FrameRect to FrameRect, same format, 4 Bytes/pixel. */
static void _blit_rotate_FR2FR_SF4B(struct _fb_rect* RTGUI_RESTRICT src,
                                    const struct rtgui_point *dc_point,
                                    struct _fb_rect* RTGUI_RESTRICT dst,
                                    const struct rtgui_matrix *invm)
{
    rt_uint32_t* RTGUI_RESTRICT srcp = (rt_uint32_t*)src->fb;
    rt_uint32_t* RTGUI_RESTRICT dstp = (rt_uint32_t*)dst->fb;
    int neww = dst->width;
    int newh = dst->height;
    int oriw = src->width;
    int orih = src->height;
    int nx, ny;
    int dx, dy;

    dx = invm->m[0];
    dy = invm->m[1];

    for (ny = dc_point->y; ny < newh; ny++)
    {
        /* Base x, y. */
        int bx, by;

        bx = dc_point->x * dx + ny * invm->m[2] + RTGUI_MATRIX_FRAC * invm->m[4];
        by = dc_point->x * dy + ny * invm->m[3] + RTGUI_MATRIX_FRAC * invm->m[5];

        for (nx = dc_point->x; nx < neww; nx++, dstp++)
        {
            union _rgba spix, dpix;
            int rx, ry, a;

            bx += dx;
            by += dy;

            if (bx < 0 || by < 0)
                continue;

            rx = bx / RTGUI_MATRIX_FRAC;
            ry = by / RTGUI_MATRIX_FRAC;

            if (oriw <= rx || orih <= ry)
                continue;

            spix.blk = srcp[ry * oriw + rx];
            /* Down scale the alpha to 5 bits. */
            a = spix.d.a >> 3;

            if (a == 0)
                continue;

            if (a == 31)
            {
                *dstp = spix.blk;
                continue;
            }

            dpix.blk = *dstp;
            dpix.d.r = (spix.d.r - dpix.d.r) * a / 32 + dpix.d.r;
            dpix.d.g = (spix.d.g - dpix.d.g) * a / 32 + dpix.d.g;
            dpix.d.b = (spix.d.b - dpix.d.b) * a / 32 + dpix.d.b;
            *dstp = dpix.blk;
        }
        dstp += dst->skip - neww;
    }
}

/* FrameRect to FrameRect, same format, 4 Bytes/pixel, with AA. */
static void _blit_rotate_FR2FR_SF4B_AA(struct _fb_rect* RTGUI_RESTRICT src,
                                       const struct rtgui_point *dc_point,
                                       struct _fb_rect* RTGUI_RESTRICT dst,
                                       const struct rtgui_matrix *invm)
{
    rt_uint32_t* RTGUI_RESTRICT srcp = (rt_uint32_t*)src->fb;
    rt_uint32_t* RTGUI_RESTRICT dstp = (rt_uint32_t*)dst->fb;
    int neww = dst->width;
    int newh = dst->height;
    int oriw = src->width;
    int orih = src->height;
    int nx, ny;
    int dx, dy;

    dx = invm->m[0];
    dy = invm->m[1];

    for (ny = dc_point->y; ny < newh; ny++)
    {
        /* Base x, y. */
        int bx, by;

        bx = dc_point->x * dx + ny * invm->m[2] + RTGUI_MATRIX_FRAC * invm->m[4];
        by = dc_point->x * dy + ny * invm->m[3] + RTGUI_MATRIX_FRAC * invm->m[5];

        for (nx = dc_point->x; nx < neww; nx++, dstp++)
        {
            union _rgba spix00, spix01, spix10, spix11, dpix;
            int rx, ry, a, sx, sy;

            bx += dx;
            by += dy;

            if (bx < 0 || by < 0)
                continue;

            rx = bx / RTGUI_MATRIX_FRAC;
            ry = by / RTGUI_MATRIX_FRAC;

            if (oriw - 1 <= rx || orih - 1 <= ry)
                continue;

            spix00.blk = srcp[ry * oriw + rx];

            /* Down scale the interpolate factor to 5 bits. */
            sx = ((unsigned int)bx % RTGUI_MATRIX_FRAC) >> (RTGUI_MATRIX_FRAC_BITS - 5);
            sy = ((unsigned int)by % RTGUI_MATRIX_FRAC) >> (RTGUI_MATRIX_FRAC_BITS - 5);

            spix01.blk = srcp[ry * oriw + rx + 1];
            spix10.blk = srcp[(ry + 1) * oriw + rx];
            spix11.blk = srcp[(ry + 1) * oriw + rx + 1];

            if (sx)
                spix00.d.a = (spix01.d.a - spix00.d.a) * sx / 32 + spix00.d.a;

            if (sx && sy)
                spix10.d.a = (spix11.d.a - spix10.d.a) * sx / 32 + spix10.d.a;

            if (sy)
                spix00.d.a = (spix10.d.a - spix00.d.a) * sy / 32 + spix00.d.a;

            a = spix00.d.a >> 3;

            if (a == 0)
                continue;

            if (sx)
            {
                spix00.d.r = (spix01.d.r - spix00.d.r) * sx / 32 + spix00.d.r;
                spix00.d.g = (spix01.d.g - spix00.d.g) * sx / 32 + spix00.d.g;
                spix00.d.b = (spix01.d.b - spix00.d.b) * sx / 32 + spix00.d.b;
            }

            if (sx && sy)
            {
                spix10.d.r = (spix11.d.r - spix10.d.r) * sx / 32 + spix10.d.r;
                spix10.d.g = (spix11.d.g - spix10.d.g) * sx / 32 + spix10.d.g;
                spix10.d.b = (spix11.d.b - spix10.d.b) * sx / 32 + spix10.d.b;
            }

            if (sy)
            {
                spix00.d.r = (spix10.d.r - spix00.d.r) * sy / 32 + spix00.d.r;
                spix00.d.g = (spix10.d.g - spix00.d.g) * sy / 32 + spix00.d.g;
                spix00.d.b = (spix10.d.b - spix00.d.b) * sy / 32 + spix00.d.b;
            }

            if (a == (255 >> 3))
            {
                *dstp = spix00.blk;
                continue;
            }

            dpix.blk = *dstp;
            dpix.d.r = (spix00.d.r - dpix.d.r) * a / 32 + dpix.d.r;
            dpix.d.g = (spix00.d.g - dpix.d.g) * a / 32 + dpix.d.g;
            dpix.d.b = (spix00.d.b - dpix.d.b) * a / 32 + dpix.d.b;
            *dstp = dpix.blk;
        }
        dstp += dst->skip - neww;
    }
}

/* FrameRect to FrameRect, from ARGB8888 to RGB565. */
static void _blit_rotate_FR2FR_ARGB2RGB565(struct _fb_rect* RTGUI_RESTRICT src,
                                           const struct rtgui_point *dc_point,
                                           struct _fb_rect* RTGUI_RESTRICT dst,
                                           const struct rtgui_matrix *invm)
{
    rt_uint32_t* RTGUI_RESTRICT srcp = (rt_uint32_t*)src->fb;
    rt_uint16_t* RTGUI_RESTRICT dstp = (rt_uint16_t*)dst->fb;
    int neww = dst->width;
    int newh = dst->height;
    int oriw = src->width;
    int orih = src->height;
    int nx, ny;
    int dx, dy;

    dx = invm->m[0];
    dy = invm->m[1];

    for (ny = dc_point->y; ny < newh; ny++)
    {
        /* Base x, y. */
        int bx, by;

        bx = dc_point->x * dx + ny * invm->m[2] + RTGUI_MATRIX_FRAC * invm->m[4];
        by = dc_point->x * dy + ny * invm->m[3] + RTGUI_MATRIX_FRAC * invm->m[5];

        for (nx = dc_point->x; nx < neww; nx++, dstp++)
        {
            int rx, ry;
            int alpha;
            rt_uint32_t op;

            bx += dx;
            by += dy;

            if (bx < 0 || by < 0)
                continue;

            rx = bx / RTGUI_MATRIX_FRAC;
            ry = by / RTGUI_MATRIX_FRAC;

            if (oriw <= rx || orih <= ry)
                continue;

            /* We take the source as a whole and ignore the src->skip. */
            op = srcp[ry * oriw + rx];
            /* downscale alpha to 5 bits */
            alpha = op >> 27;
            if (alpha == (255 >> 3))
            {
                *dstp = (rt_uint16_t)((op >> 8 & 0xf800) +
                                      (op >> 5 & 0x7e0) +
                                      (op >> 3 & 0x1f));
            }
            else if (alpha != 0)
            {
                /* We take the source as a whole and ignore the src->skip. */
                rt_uint32_t d = *dstp;
                /*
                 * convert source and destination to G0RAB65565
                 * and blend all components at the same time
                 */
                op = ((op & 0xfc00) << 11) + (op >> 8 & 0xf800)
                    + (op >> 3 & 0x1f);
                d = (d | d << 16) & 0x07e0f81f;
                d += (op - d) * alpha >> 5;
                d &= 0x07e0f81f;
                *dstp = (rt_uint16_t)(d | d >> 16);
            }
        }
        dstp += dst->skip - neww;
    }
}

/* FrameRect to FrameRect, from ARGB8888 to RGB565. */
static void _blit_rotate_FR2FR_ARGB2RGB565_AA(struct _fb_rect* RTGUI_RESTRICT src,
                                              const struct rtgui_point *dc_point,
                                              struct _fb_rect* RTGUI_RESTRICT dst,
                                              const struct rtgui_matrix *invm)
{
    rt_uint32_t* RTGUI_RESTRICT srcp = (rt_uint32_t*)src->fb;
    rt_uint16_t* RTGUI_RESTRICT dstp = (rt_uint16_t*)dst->fb;
    int neww = dst->width;
    int newh = dst->height;
    int oriw = src->width;
    int orih = src->height;
    int nx, ny;
    int dx, dy;

    dx = invm->m[0];
    dy = invm->m[1];

    for (ny = dc_point->y; ny < newh; ny++)
    {
        /* Base x, y. */
        int bx, by;

        bx = dc_point->x * dx + ny * invm->m[2] + RTGUI_MATRIX_FRAC * invm->m[4];
        by = dc_point->x * dy + ny * invm->m[3] + RTGUI_MATRIX_FRAC * invm->m[5];

        for (nx = dc_point->x; nx < neww; nx++, dstp++)
        {
            rt_uint32_t op00, op01, op10, op11;
            rt_uint8_t a00, a01, a10, a11;
            int rx, ry, sx, sy;

            bx += dx;
            by += dy;

            if (bx < 0 || by < 0)
                continue;

            rx = bx / RTGUI_MATRIX_FRAC;
            ry = by / RTGUI_MATRIX_FRAC;

            if (oriw - 1 <= rx || orih - 1 <= ry)
                continue;

            op00 = srcp[ry * oriw + rx];
            op01 = srcp[ry * oriw + rx + 1];
            op10 = srcp[(ry + 1) * oriw + rx];
            op11 = srcp[(ry + 1) * oriw + rx + 1];

            /* Down scale the interpolate factor to 5 bits. */
            sx = ((unsigned int)bx % RTGUI_MATRIX_FRAC) >> (RTGUI_MATRIX_FRAC_BITS - 5);
            sy = ((unsigned int)by % RTGUI_MATRIX_FRAC) >> (RTGUI_MATRIX_FRAC_BITS - 5);

            a00 = op00 >> 27;
            a01 = op01 >> 27;
            a11 = op11 >> 27;
            a10 = op10 >> 27;

            if (sx)
                a00 = (a01 - a00) * sx / 32 + a00;
            if (sx && sy)
                a10 = (a11 - a10) * sx / 32 + a10;
            if (sy)
                a00 = (a10 - a00) * sy / 32 + a00;
            if (a00 == 0)
                continue;

            op00 = (((op00 >> 10) & 0x3f) << 21) | (((op00 >> 19) & 0x1f) << 11) | (op00 >> 3 & 0x1f);
            op10 = (((op10 >> 10) & 0x3f) << 21) | (((op10 >> 19) & 0x1f) << 11) | (op10 >> 3 & 0x1f);
            op01 = (((op01 >> 10) & 0x3f) << 21) | (((op01 >> 19) & 0x1f) << 11) | (op01 >> 3 & 0x1f);
            op11 = (((op11 >> 10) & 0x3f) << 21) | (((op11 >> 19) & 0x1f) << 11) | (op11 >> 3 & 0x1f);

            if (sx)
            {
                op00 = ((op01 - op00) * sx / 32 + op00) & 0x07e0f81f;
            }

            if (sx && sy)
            {
                op10 = ((op11 - op10) * sx / 32 + op10) & 0x07e0f81f;
            }

            if (sy)
            {
                op00 = ((op10 - op00) * sy / 32 + op00) & 0x07e0f81f;
            }

            if (a00 == (255 >> 3))
            {
                *dstp = op00 | (op00 >> 16);
            }
            else if (a00 != 0)
            {
                rt_uint32_t d = *dstp;

                d = (d | d << 16) & 0x07e0f81f;
                d += (op00 - d) * a00 >> 5;
                d &= 0x07e0f81f;
                *dstp = (rt_uint16_t)(d | d >> 16);
            }
        }
        dstp += dst->skip - neww;
    }
}

static void _blit_rotate_B2B(struct rtgui_dc_trans *dct,
                             const struct rtgui_point *dc_point,
                             struct rtgui_dc_buffer* RTGUI_RESTRICT dest,
                             struct rtgui_rect *rect,
                             const struct rtgui_matrix *invm,
                             int neww, int newh)
{
    struct rtgui_rect srcrect;
    struct rtgui_dc_buffer *dc = (struct rtgui_dc_buffer*)dct->owner;
    struct _fb_rect srcfb, dstfb;

    rtgui_dc_get_rect(dct->owner, &srcrect);

    srcfb.fb     = ((struct rtgui_dc_buffer*)dct->owner)->pixel;
    srcfb.width  = srcrect.x2;
    srcfb.height = srcrect.y2;
    srcfb.skip   = 0;

    dstfb.fb     = dest->pixel + rtgui_color_get_bpp(dest->pixel_format) * (rect->x1 + rect->y1 * dest->width);
    dstfb.width  = neww;
    dstfb.height = newh;
    dstfb.skip   = dest->width;

    if (dc->pixel_format == dest->pixel_format)
    {
        switch (rtgui_color_get_bpp(dest->pixel_format)) {
        case 2:
            if (dct->use_aa)
                _blit_rotate_FR2FR_SF2B_AA(&srcfb, dc_point,
                                           &dstfb, invm);
            else
                _blit_rotate_FR2FR_SF2B(&srcfb, dc_point,
                                        &dstfb, invm);
            break;
        case 4:
            if (dct->use_aa)
                _blit_rotate_FR2FR_SF4B_AA(&srcfb, dc_point,
                                           &dstfb, invm);
            else
                _blit_rotate_FR2FR_SF4B(&srcfb, dc_point,
                                        &dstfb, invm);
            break;
        default:
            rt_kprintf("could not handle bpp: %d\n",
                       rtgui_color_get_bpp(dest->pixel_format));
            return;
        }
    }
    else if (dc->pixel_format == RTGRAPHIC_PIXEL_FORMAT_ARGB888 &&
             dest->pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565)
    {
        if (dct->use_aa)
            _blit_rotate_FR2FR_ARGB2RGB565_AA(&srcfb, dc_point,
                                              &dstfb, invm);
        else
            _blit_rotate_FR2FR_ARGB2RGB565(&srcfb, dc_point,
                                           &dstfb, invm);
    }
    else
    {
        rt_kprintf("not implemented yet\n");
        return;
    }
}

static void _blit_rotate_B2H(struct rtgui_dc_trans *dct,
                             const struct rtgui_point *dc_point,
                             struct rtgui_dc_hw* dest,
                             struct rtgui_rect *rect,
                             const struct rtgui_matrix *invm,
                             int neww, int newh)
{
    struct rtgui_rect srcrect;
    int start_pix;
    struct _fb_rect srcfb, dstfb;
    struct rtgui_dc_buffer *dc = (struct rtgui_dc_buffer*)dct->owner;

    if (dest->hw_driver->framebuffer == RT_NULL)
    {
        rt_kprintf("Only support framebuffer hw dc\n");
        return;
    }

    rtgui_dc_get_rect(dct->owner, &srcrect);

    srcfb.fb     = ((struct rtgui_dc_buffer*)dct->owner)->pixel;
    srcfb.width  = srcrect.x2;
    srcfb.height = srcrect.y2;
    srcfb.skip   = 0;

    /* Start point of the widget. */
    start_pix = dest->owner->extent.x1 + dest->owner->extent.y1 * dest->hw_driver->width;
    /* Start point of the inner rect. */
    start_pix += rect->x1 + rect->y1 * dest->hw_driver->width;

    dstfb.fb     = (void*)(dest->hw_driver->framebuffer
                           + rtgui_color_get_bpp(dest->hw_driver->pixel_format) * start_pix);
    dstfb.width  = neww;
    dstfb.height = newh;
    dstfb.skip   = dest->hw_driver->width;

    if (dc->pixel_format == dest->hw_driver->pixel_format)
    {
        switch (rtgui_color_get_bpp(dest->hw_driver->pixel_format)) {
        case 2:
            if (dct->use_aa)
                _blit_rotate_FR2FR_SF2B_AA(&srcfb, dc_point,
                                           &dstfb, invm);
            else
                _blit_rotate_FR2FR_SF2B(&srcfb, dc_point,
                                        &dstfb, invm);
            break;
        case 4:
            if (dct->use_aa)
                _blit_rotate_FR2FR_SF4B_AA(&srcfb, dc_point,
                                           &dstfb, invm);
            else
                _blit_rotate_FR2FR_SF4B(&srcfb, dc_point,
                                        &dstfb, invm);
            break;
        default:
            rt_kprintf("could not handle bpp: %d\n",
                       rtgui_color_get_bpp(dest->hw_driver->pixel_format));
            return;
        }
    }
    else if (dc->pixel_format == RTGRAPHIC_PIXEL_FORMAT_ARGB888 &&
             dest->hw_driver->pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565)
    {
        if (dct->use_aa)
            _blit_rotate_FR2FR_ARGB2RGB565_AA(&srcfb, dc_point,
                                              &dstfb, invm);
        else
            _blit_rotate_FR2FR_ARGB2RGB565(&srcfb, dc_point,
                                           &dstfb, invm);
    }
    else
    {
        rt_kprintf("not implemented yet\n");
        return;
    }
}

void rtgui_dc_trans_blit(struct rtgui_dc_trans *dct,
                         struct rtgui_point *dc_point,
                         struct rtgui_dc *dest,
                         struct rtgui_rect *rect)
{
    struct rtgui_rect bkrect;
    struct rtgui_matrix invm;
    struct rtgui_point dp;
    int neww, newh;

    RT_ASSERT(dct);
    RT_ASSERT(dest);

    if (dc_point == RT_NULL)
    {
        dp.x = dp.y = 0;
        dc_point = &dp;
    }
    if (rect == RT_NULL)
    {
        rtgui_dc_get_rect(dest, &bkrect);
        rect = &bkrect;
    }

    rtgui_dc_trans_get_new_wh(dct, &neww, &newh);
    if (dc_point->x < 0)
    {
        neww -= dc_point->x;
        if (neww < 0)
            return;
        dc_point->x = 0;
    }
    else if (dc_point->x > neww)
        return;
    if (dc_point->y < 0)
    {
        newh -= dc_point->y;
        if (newh < 0)
            return;
        dc_point->y = 0;
    }
    else if (dc_point->y > newh)
        return;

    if (rtgui_matrix_inverse(&dct->m, &invm))
        return;

    if (rtgui_rect_width(*rect) < neww - dc_point->x)
        neww = dc_point->x + rtgui_rect_width(*rect);
    if (rtgui_rect_height(*rect) < newh - dc_point->y)
        newh = dc_point->y + rtgui_rect_height(*rect);

    /* Route to different optimized routines. */
    if (dct->owner->type == RTGUI_DC_BUFFER)
    {
        if (dest->type == RTGUI_DC_BUFFER)
                _blit_rotate_B2B(dct, dc_point,
                                 (struct rtgui_dc_buffer*)dest,
                                 rect, &invm, neww, newh);
        else if (dest->type == RTGUI_DC_HW)
                _blit_rotate_B2H(dct, dc_point,
                                 (struct rtgui_dc_hw*)dest,
                                 rect, &invm, neww, newh);
        else if (dest->type == RTGUI_DC_CLIENT)
            // TODO:
            ;
        else
            rt_kprintf("unknown dc for dc_trans\n");
    }
    else
        rt_kprintf("not implemented yet\n");
}
RTM_EXPORT(rtgui_dc_trans_blit);

