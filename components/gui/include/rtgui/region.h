/*
 * File      : region.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#ifndef __RTGUI_REGION_H__
#define __RTGUI_REGION_H__

#include <rtgui/rtgui.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef struct rtgui_region_data rtgui_region_data_t;
struct rtgui_dc;

struct rtgui_region_data
{
    rt_uint32_t size;
    rt_uint32_t numRects;
    /* XXX: And why, exactly, do we have this bogus struct definition? */
    /* rtgui_rect_t rects[size]; in memory but not explicitly declared */
};

typedef struct rtgui_region
{
    rtgui_rect_t          extents;
    rtgui_region_data_t  *data;
} rtgui_region_t;

typedef enum
{
    RTGUI_REGION_STATUS_FAILURE,
    RTGUI_REGION_STATUS_SUCCESS
} rtgui_region_status_t;

/* creation/destruction */

void rtgui_region_init(rtgui_region_t *region);
void rtgui_region_init_rect(rtgui_region_t *region,
                            int x, int y, unsigned int width, unsigned int height);
void rtgui_region_init_with_extents(rtgui_region_t *region, const rtgui_rect_t *extents);
void rtgui_region_fini(rtgui_region_t *region);

void rtgui_region_translate(rtgui_region_t *region, int x, int y);

rtgui_region_status_t rtgui_region_copy(rtgui_region_t *dest, rtgui_region_t *source);

rtgui_region_status_t rtgui_region_intersect(rtgui_region_t *newReg, rtgui_region_t *reg1, rtgui_region_t *reg2);
rtgui_region_status_t rtgui_region_intersect_rect(rtgui_region_t *newReg, rtgui_region_t *reg1, rtgui_rect_t *rect);
rtgui_region_status_t rtgui_region_union(rtgui_region_t *newReg, rtgui_region_t *reg1, rtgui_region_t *reg2);
rtgui_region_status_t rtgui_region_union_rect(rtgui_region_t *dest, rtgui_region_t *source, rtgui_rect_t *rect);
rtgui_region_status_t rtgui_region_subtract(rtgui_region_t *regD, rtgui_region_t *regM, rtgui_region_t *regS);
rtgui_region_status_t rtgui_region_subtract_rect(rtgui_region_t *regD, rtgui_region_t *regM, rtgui_rect_t *rect);
rtgui_region_status_t rtgui_region_inverse(rtgui_region_t *newReg, rtgui_region_t *reg1, rtgui_rect_t *invRect);

int rtgui_region_num_rects(rtgui_region_t *region);

rtgui_rect_t *rtgui_region_rects(rtgui_region_t *region);

#define RTGUI_REGION_OUT    0
#define RTGUI_REGION_IN     1
#define RTGUI_REGION_PART   2

int rtgui_region_contains_point(rtgui_region_t *region, int x, int y, rtgui_rect_t *box);
int rtgui_region_contains_rectangle(rtgui_region_t *rtgui_region_t, rtgui_rect_t *prect);

int rtgui_region_not_empty(rtgui_region_t *region);
rtgui_rect_t *rtgui_region_extents(rtgui_region_t *region);

rtgui_region_status_t rtgui_region_append(rtgui_region_t *dest, rtgui_region_t *region);
rtgui_region_status_t rtgui_region_validate(rtgui_region_t *badreg, int *pOverlap);

void rtgui_region_reset(rtgui_region_t *region, rtgui_rect_t *rect);
void rtgui_region_empty(rtgui_region_t *region);
void rtgui_region_dump(rtgui_region_t *region);
void rtgui_region_draw_clip(rtgui_region_t *region, struct rtgui_dc *dc);
int rtgui_region_is_flat(rtgui_region_t *region);

/* rect functions */
extern rtgui_rect_t rtgui_empty_rect;

void rtgui_rect_moveto(rtgui_rect_t *rect, int x, int y);
void rtgui_rect_moveto_align(const rtgui_rect_t *rect, rtgui_rect_t *to, int align);
void rtgui_rect_inflate(rtgui_rect_t *rect, int d);
void rtgui_rect_intersect(rtgui_rect_t *src, rtgui_rect_t *dest);
int  rtgui_rect_contains_point(const rtgui_rect_t *rect, int x, int y);
int  rtgui_rect_is_intersect(const rtgui_rect_t *rect1, const rtgui_rect_t *rect2);
int  rtgui_rect_is_equal(const rtgui_rect_t *rect1, const rtgui_rect_t *rect2);
rtgui_rect_t *rtgui_rect_set(rtgui_rect_t *rect, int x, int y, int w, int h);
rt_bool_t rtgui_rect_is_empty(const rtgui_rect_t *rect);

rt_inline void rtgui_rect_init(rtgui_rect_t* rect, int x, int y, int width, int height)
{
	rect->x1 = x; rect->y1 = y;
	rect->x2 = x + width; rect->y2 = y + height;
}

#define RTGUI_RECT(rect, x, y, w, h)	\
	do { \
	rect.x1 = x; rect.y1 = y; \
	rect.x2 = (x) + (w); rect.y2 = (y) + (h); \
	} while (0)

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _PIXMAN_H_ */
