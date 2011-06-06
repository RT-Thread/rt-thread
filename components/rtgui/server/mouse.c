/*
 * File      : mouse.c
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

#include "mouse.h"
#include <rtgui/region.h>
#include <rtgui/driver.h>
#include <rtgui/rtgui_system.h>

struct rtgui_cursor
{
	/* screen byte per pixel */
	rt_uint16_t bpp;

	/* screen pitch */
	rt_uint16_t screen_pitch;

	/* current cursor x and y */
	rt_uint16_t cx, cy;

#ifdef RTGUI_USING_MOUSE_CURSOR
	/* cursor pitch */
	rt_uint16_t cursor_pitch;

	/* show cursor and show cursor count */
	rt_bool_t show_cursor;
	rt_base_t show_cursor_count;

	/* cursor rect info */
	rtgui_rect_t rect;

	/* cursor image and saved cursor */
	rtgui_image_t	*cursor_image;
	rt_uint8_t		*cursor_saved;
#endif

#ifdef RTGUI_USING_WINMOVE
	/* move window rect and border */
	struct rtgui_topwin *topwin;
	rtgui_rect_t	win_rect;
	rt_uint8_t		*win_left, *win_right;
	rt_uint8_t		*win_top, *win_bottom;
	rt_bool_t		win_rect_show, win_rect_has_saved;
#endif

	/* screen framebuffer */
	rt_uint8_t*		framebuffer;
};

struct rtgui_cursor* _rtgui_cursor;

#ifdef RTGUI_USING_MOUSE_CURSOR
struct rt_mutex cursor_mutex;
static const rt_uint8_t * cursor_xpm[] = {
	"16 16 35 1",
	" 	c None",
	".	c #A0B8D0",
	"+	c #F0F0F0",
	"@	c #FFFFFF",
	"#	c #F0F8F0",
	"$	c #A0B0D0",
	"%	c #90A8C0",
	"&	c #A0B0C0",
	"*	c #E0E8F0",
	"=	c #8090B0",
	"-	c #D0D8E0",
	";	c #7080A0",
	">	c #90A0B0",
	",	c #FFF8FF",
	"'	c #F0F8FF",
	")	c #607090",
	"!	c #8098B0",
	"~	c #405060",
	"{	c #405070",
	"]	c #506070",
	"^	c #607080",
	"/	c #708090",
	"(	c #7088A0",
	"_	c #D0D0E0",
	":	c #607890",
	"<	c #C0D0E0",
	"[	c #C0C8D0",
	"}	c #506880",
	"|	c #5F778F",
	"1	c #D0D8F0",
	"2	c #506080",
	"3	c #C0C8E0",
	"4	c #A0A8C0",
	"5	c #405870",
	"6	c #5F6F8F",
	"   .            ",
	"   ..           ",
	"   .+.          ",
	"   .@#$         ",
	"   $@@+%        ",
	"   &@@@*=       ",
	"   %@@@@-;      ",
	"   >@@,''-)     ",
	"   !,''+)~{]    ",
	"   ='-^*/       ",
	"   (_{:<[^      ",
	"   ;} |:12      ",
	"   /   )345     ",
	"       6}${     ",
	"        5{      ",
	"                "};

static void rtgui_cursor_restore	(void);
static void rtgui_cursor_save		(void);
static void rtgui_cursor_show		(void);
#endif

#ifdef RTGUI_USING_WINMOVE
static void rtgui_winrect_restore	(void);
static void rtgui_winrect_save		(void);
static void rtgui_winrect_show		(void);
#endif

#define WIN_MOVE_BORDER	4
void rtgui_mouse_init()
{
	const struct rtgui_graphic_driver* gd = rtgui_graphic_driver_get_default();

	_rtgui_cursor = (struct rtgui_cursor*) rtgui_malloc(sizeof(struct rtgui_cursor));
	rt_memset(_rtgui_cursor, 0, sizeof(struct rtgui_cursor));

#ifdef RTGUI_USING_MOUSE_CURSOR
	rt_mutex_init(&cursor_mutex, "cursor", RT_IPC_FLAG_FIFO);
#endif

	/* init cursor */
	_rtgui_cursor->bpp = gd->bits_per_pixel/8;
	_rtgui_cursor->framebuffer = rtgui_graphic_driver_get_framebuffer(gd);
	_rtgui_cursor->screen_pitch = _rtgui_cursor->bpp * gd->width;

#ifdef RTGUI_USING_MOUSE_CURSOR
	/* init cursor image */
	_rtgui_cursor->cursor_image = rtgui_image_create_from_mem("xpm", cursor_xpm, sizeof(cursor_xpm));
	if (_rtgui_cursor->cursor_image == RT_NULL)
	{
		rtgui_free(_rtgui_cursor);
		_rtgui_cursor = RT_NULL;

		return;
	}

	/* init rect */
	_rtgui_cursor->rect.x1 = _rtgui_cursor->rect.y1 = 0;
	_rtgui_cursor->rect.x2 = _rtgui_cursor->cursor_image->w;
	_rtgui_cursor->rect.y2 = _rtgui_cursor->cursor_image->h;

	_rtgui_cursor->cursor_pitch = _rtgui_cursor->cursor_image->w * _rtgui_cursor->bpp;

	_rtgui_cursor->show_cursor = RT_TRUE;
	_rtgui_cursor->show_cursor_count = 0;
	_rtgui_cursor->cursor_saved = rtgui_malloc(_rtgui_cursor->cursor_image->w *
		_rtgui_cursor->cursor_image->h * _rtgui_cursor->bpp);
#endif

#ifdef RTGUI_USING_WINMOVE
	/* init window move save image */
	_rtgui_cursor->win_rect_has_saved	= RT_FALSE;
	_rtgui_cursor->win_rect_show		= RT_FALSE;

	_rtgui_cursor->win_left		= rtgui_malloc(_rtgui_cursor->bpp * gd->height * WIN_MOVE_BORDER);
	_rtgui_cursor->win_right	= rtgui_malloc(_rtgui_cursor->bpp * gd->height * WIN_MOVE_BORDER);
	_rtgui_cursor->win_top		= rtgui_malloc(_rtgui_cursor->bpp * gd->width  * WIN_MOVE_BORDER);
	_rtgui_cursor->win_bottom	= rtgui_malloc(_rtgui_cursor->bpp * gd->width  * WIN_MOVE_BORDER);
#endif
}

void rtgui_mouse_moveto(int x, int y)
{
#ifdef RTGUI_USING_MOUSE_CURSOR
	rt_mutex_take(&cursor_mutex, RT_WAITING_FOREVER);
#endif

	if (x != _rtgui_cursor->cx ||
		y != _rtgui_cursor->cy)
	{
#ifdef RTGUI_USING_WINMOVE
		if (_rtgui_cursor->win_rect_show)
		{
			if (_rtgui_cursor->win_rect_has_saved == RT_TRUE)
			{
				rtgui_winrect_restore();
			}

#ifdef RTGUI_USING_MOUSE_CURSOR
			rtgui_mouse_hide_cursor();
#endif

			/* move winrect */
			rtgui_rect_moveto(&(_rtgui_cursor->win_rect), x - _rtgui_cursor->cx,
				y - _rtgui_cursor->cy);
			rtgui_winrect_save();

			/* move current cursor */
			_rtgui_cursor->cx = x;
			_rtgui_cursor->cy = y;

#ifdef RTGUI_USING_MOUSE_CURSOR
			/* show cursor */
			rtgui_mouse_show_cursor();
#endif
			/* show winrect */
			rtgui_winrect_show();
		}
		else
#endif
		{
#ifdef RTGUI_USING_MOUSE_CURSOR
			rtgui_mouse_hide_cursor();
#endif
			/* move current cursor */
			_rtgui_cursor->cx = x;
			_rtgui_cursor->cy = y;

#ifdef RTGUI_USING_MOUSE_CURSOR
			/* show cursor */
			rtgui_mouse_show_cursor();
#endif
		}
	}

#ifdef RTGUI_USING_MOUSE_CURSOR
	rt_mutex_release(&cursor_mutex);
#endif
}

#ifdef RTGUI_USING_MOUSE_CURSOR
void rtgui_mouse_set_cursor_enable(rt_bool_t enable)
{
	_rtgui_cursor->show_cursor = enable;
}

/* set current cursor image */
void rtgui_mouse_set_cursor(rtgui_image_t* cursor)
{
}

void rtgui_mouse_get_cursor_rect(rtgui_rect_t* rect)
{
	if (rect != RT_NULL)
	{
		*rect = _rtgui_cursor->rect;
	}
}

void rtgui_mouse_show_cursor()
{
	if (_rtgui_cursor->show_cursor == RT_FALSE)
		return;

	_rtgui_cursor->show_cursor_count ++;
	if (_rtgui_cursor->show_cursor_count == 1)
	{
		/* save show mouse area */
		rtgui_cursor_save();

		/* show mouse cursor */
		rtgui_cursor_show();
	}
}

void rtgui_mouse_hide_cursor()
{
	if (_rtgui_cursor->show_cursor == RT_FALSE)
		return;

	if (_rtgui_cursor->show_cursor_count == 1)
	{
		/* display the cursor coverage area */
		rtgui_cursor_restore();
	}
	_rtgui_cursor->show_cursor_count --;
}

rt_bool_t rtgui_mouse_is_intersect(rtgui_rect_t* r)
{
	return rtgui_rect_is_intersect(&(_rtgui_cursor->rect), r) == RT_EOK? RT_TRUE : RT_FALSE;
}

/* display the saved cursor area to screen */
static void rtgui_cursor_restore()
{
	rt_base_t idx, height, cursor_pitch;
	rt_uint8_t *cursor_ptr, *fb_ptr;

	fb_ptr = _rtgui_cursor->framebuffer + _rtgui_cursor->cy * _rtgui_cursor->screen_pitch
		+ _rtgui_cursor->cx * _rtgui_cursor->bpp;
	cursor_ptr = _rtgui_cursor->cursor_saved;

	height = (_rtgui_cursor->cy + _rtgui_cursor->cursor_image->h <
		rtgui_graphic_driver_get_default()->height)? _rtgui_cursor->cursor_image->h :
		rtgui_graphic_driver_get_default()->height - _rtgui_cursor->cy;

	cursor_pitch = (_rtgui_cursor->cx + _rtgui_cursor->cursor_image->w <
		rtgui_graphic_driver_get_default()->width)? _rtgui_cursor->cursor_pitch :
		(rtgui_graphic_driver_get_default()->width - _rtgui_cursor->cx) * _rtgui_cursor->bpp;

	for (idx = 0; idx < height; idx ++)
	{
		rt_memcpy(fb_ptr, cursor_ptr, cursor_pitch);

		fb_ptr += _rtgui_cursor->screen_pitch;
		cursor_ptr += _rtgui_cursor->cursor_pitch;
	}
}

/* save the cursor coverage area from screen */
static void rtgui_cursor_save()
{
	rt_base_t idx, height, cursor_pitch;
	rt_uint8_t *cursor_ptr, *fb_ptr;

	fb_ptr = _rtgui_cursor->framebuffer + _rtgui_cursor->cy * _rtgui_cursor->screen_pitch +
		_rtgui_cursor->cx * _rtgui_cursor->bpp;
	cursor_ptr = _rtgui_cursor->cursor_saved;

	height = (_rtgui_cursor->cy + _rtgui_cursor->cursor_image->h <
		rtgui_graphic_driver_get_default()->height)? _rtgui_cursor->cursor_image->h :
		rtgui_graphic_driver_get_default()->height - _rtgui_cursor->cy;

	cursor_pitch = (_rtgui_cursor->cx + _rtgui_cursor->cursor_image->w <
		rtgui_graphic_driver_get_default()->width)? _rtgui_cursor->cursor_pitch :
		(rtgui_graphic_driver_get_default()->width - _rtgui_cursor->cx) * _rtgui_cursor->bpp;

	for (idx = 0; idx < height; idx ++)
	{
		rt_memcpy(cursor_ptr, fb_ptr, cursor_pitch);

		fb_ptr += _rtgui_cursor->screen_pitch;
		cursor_ptr += _rtgui_cursor->cursor_pitch;
	}
}

static void rtgui_cursor_show()
{
	rt_uint16_t x, y;
	rtgui_color_t* ptr;
	rtgui_rect_t rect;
	void (*set_pixel) (rtgui_color_t *c, rt_uint16_t x, rt_uint16_t y);

	ptr = (rtgui_color_t*) _rtgui_cursor->cursor_image->data;
	set_pixel = rtgui_graphic_driver_get_default()->set_pixel;

	rtgui_mouse_get_cursor_rect(&rect);
	rtgui_rect_moveto(&rect, _rtgui_cursor->cx, _rtgui_cursor->cy);

	/* draw each point */
	for (y = rect.y1; y < rect.y2; y ++)
	{
		for (x = rect.x1; x < rect.x2; x++)
		{
			/* not alpha */
			if ((*ptr >> 24) != 255)
			{
				set_pixel(ptr, x, y);
			}

			/* move to next color buffer */
			ptr ++;
		}
	}

	/* update rect */
	rtgui_graphic_driver_get_default()->screen_update(&rect);
}
#endif

#ifdef RTGUI_USING_WINMOVE
void rtgui_winrect_set(struct rtgui_topwin* topwin)
{
	/* set win rect show */
	_rtgui_cursor->win_rect_show = RT_TRUE;

	/* set win rect */
	_rtgui_cursor->win_rect = topwin->title == RT_NULL? topwin->extent : RTGUI_WIDGET(topwin->title)->extent;
	_rtgui_cursor->topwin = topwin;
}

rt_bool_t rtgui_winrect_moved_done(rtgui_rect_t* winrect, struct rtgui_topwin** topwin)
{
	rt_bool_t moved = RT_FALSE;

	/* no win rect */
	if (winrect == RT_NULL) return RT_FALSE;

	/* restore winrect */
	if (_rtgui_cursor->win_rect_has_saved)
	{
		rtgui_winrect_restore();

		moved = RT_TRUE;
	}

	/* clear win rect show */
	_rtgui_cursor->win_rect_show = RT_FALSE;
	_rtgui_cursor->win_rect_has_saved = RT_FALSE;

	/* return win rect */
	*winrect = _rtgui_cursor->win_rect;
	*topwin = _rtgui_cursor->topwin;

	return moved;
}

rt_bool_t rtgui_winrect_is_moved()
{
	return _rtgui_cursor->win_rect_show;
}

/* show winrect */
static void rtgui_winrect_show()
{
	rt_uint16_t x, y;
	rtgui_color_t c;
	rtgui_rect_t screen_rect, win_rect, win_rect_inner;
	void (*set_pixel) (rtgui_color_t *c, rt_base_t x, rt_base_t y);

	c = black;
	set_pixel = rtgui_graphic_driver_get_default()->ops->set_pixel;

	win_rect = _rtgui_cursor->win_rect;
	win_rect_inner = win_rect;
	rtgui_rect_inflate(&win_rect_inner, -WIN_MOVE_BORDER);

	rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(),
		&screen_rect);
	rtgui_rect_intersect(&screen_rect, &win_rect);
	rtgui_rect_intersect(&screen_rect, &win_rect_inner);

	/* draw left */
	for (y = win_rect.y1; y < win_rect.y2; y ++)
	{
		for (x = win_rect.x1; x < win_rect_inner.x1; x++)
			if ((x + y) & 0x01) set_pixel(&c, x, y);
	}

	/* draw right */
	for (y = win_rect.y1; y < win_rect.y2; y ++)
	{
		for (x = win_rect_inner.x2; x < win_rect.x2; x++)
			if ((x + y) & 0x01) set_pixel(&c, x, y);
	}

	/* draw top border */
	for (y = win_rect.y1; y < win_rect_inner.y1; y ++)
	{
		for (x = win_rect_inner.x1; x < win_rect_inner.x2; x++)
			if ((x + y) & 0x01) set_pixel(&c, x, y);
	}

	/* draw bottom border */
	for (y = win_rect_inner.y2; y < win_rect.y2; y ++)
	{
		for (x = win_rect_inner.x1; x < win_rect_inner.x2; x++)
			if ((x + y) & 0x01) set_pixel(&c, x, y);
	}

	/* update rect */
	rtgui_graphic_driver_screen_update(rtgui_graphic_driver_get_default(), &win_rect);
}

#define display_direct_memcpy(src, dest, src_pitch, dest_pitch, height, len)	\
	for (idx = 0; idx < height; idx ++)		\
	{										\
		rt_memcpy(dest, src, len);			\
		src  += src_pitch;					\
		dest += dest_pitch;					\
	}

static void rtgui_winrect_restore()
{
	rt_uint8_t *winrect_ptr, *fb_ptr;
	int winrect_pitch, idx;
	rtgui_rect_t screen_rect, win_rect;

	win_rect = _rtgui_cursor->win_rect;

	rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(),
		&screen_rect);
	rtgui_rect_intersect(&screen_rect, &win_rect);

	/* restore winrect left */
	fb_ptr = _rtgui_cursor->framebuffer + win_rect.y1 * _rtgui_cursor->screen_pitch +
		win_rect.x1 * _rtgui_cursor->bpp;
	winrect_ptr = _rtgui_cursor->win_left;
	winrect_pitch = WIN_MOVE_BORDER * _rtgui_cursor->bpp;
	display_direct_memcpy(winrect_ptr, fb_ptr, winrect_pitch, _rtgui_cursor->screen_pitch,
		(win_rect.y2 - win_rect.y1), winrect_pitch);

	/* restore winrect right */
	fb_ptr = _rtgui_cursor->framebuffer + win_rect.y1 * _rtgui_cursor->screen_pitch +
		(win_rect.x2 - WIN_MOVE_BORDER) * _rtgui_cursor->bpp;
	winrect_ptr = _rtgui_cursor->win_right;
	winrect_pitch = WIN_MOVE_BORDER * _rtgui_cursor->bpp;
	display_direct_memcpy(winrect_ptr, fb_ptr, winrect_pitch, _rtgui_cursor->screen_pitch,
		(win_rect.y2 - win_rect.y1), winrect_pitch);

	/* restore winrect top */
	fb_ptr = _rtgui_cursor->framebuffer + win_rect.y1 * _rtgui_cursor->screen_pitch +
		(win_rect.x1 + WIN_MOVE_BORDER)* _rtgui_cursor->bpp;
	winrect_ptr = _rtgui_cursor->win_top;
	winrect_pitch = (win_rect.x2 - win_rect.x1 - 2 * WIN_MOVE_BORDER) * _rtgui_cursor->bpp;
	display_direct_memcpy(winrect_ptr, fb_ptr, winrect_pitch, _rtgui_cursor->screen_pitch,
		WIN_MOVE_BORDER, winrect_pitch);

	/* restore winrect bottom */
	fb_ptr = _rtgui_cursor->framebuffer + (win_rect.y2 - WIN_MOVE_BORDER) * _rtgui_cursor->screen_pitch +
		(win_rect.x1 + WIN_MOVE_BORDER) * _rtgui_cursor->bpp;
	winrect_ptr = _rtgui_cursor->win_bottom;
	display_direct_memcpy(winrect_ptr, fb_ptr, winrect_pitch, _rtgui_cursor->screen_pitch,
		WIN_MOVE_BORDER, winrect_pitch);
}

static void rtgui_winrect_save()
{
	rt_uint8_t *winrect_ptr, *fb_ptr;
	int winrect_pitch, idx;
	rtgui_rect_t screen_rect, win_rect;

	win_rect = _rtgui_cursor->win_rect;

	rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(),
		&screen_rect);
	rtgui_rect_intersect(&screen_rect, &win_rect);

	/* set winrect has saved */
	_rtgui_cursor->win_rect_has_saved = RT_TRUE;

	/* save winrect left */
	fb_ptr = _rtgui_cursor->framebuffer + win_rect.y1 * _rtgui_cursor->screen_pitch +
		win_rect.x1 * _rtgui_cursor->bpp;
	winrect_ptr = _rtgui_cursor->win_left;
	winrect_pitch = WIN_MOVE_BORDER * _rtgui_cursor->bpp;
	display_direct_memcpy(fb_ptr, winrect_ptr, _rtgui_cursor->screen_pitch, winrect_pitch,
		(win_rect.y2 - win_rect.y1), winrect_pitch);

	/* save winrect right */
	fb_ptr = _rtgui_cursor->framebuffer + win_rect.y1 * _rtgui_cursor->screen_pitch +
		(win_rect.x2 - WIN_MOVE_BORDER) * _rtgui_cursor->bpp;
	winrect_ptr = _rtgui_cursor->win_right;
	winrect_pitch = WIN_MOVE_BORDER * _rtgui_cursor->bpp;
	display_direct_memcpy(fb_ptr, winrect_ptr, _rtgui_cursor->screen_pitch, winrect_pitch,
		(win_rect.y2 - win_rect.y1), winrect_pitch);

	/* save winrect top */
	fb_ptr = _rtgui_cursor->framebuffer + win_rect.y1 * _rtgui_cursor->screen_pitch +
		(win_rect.x1 + WIN_MOVE_BORDER)* _rtgui_cursor->bpp;
	winrect_ptr = _rtgui_cursor->win_top;
	winrect_pitch = (win_rect.x2 - win_rect.x1 - 2 * WIN_MOVE_BORDER) * _rtgui_cursor->bpp;
	display_direct_memcpy(fb_ptr, winrect_ptr, _rtgui_cursor->screen_pitch, winrect_pitch,
		WIN_MOVE_BORDER, winrect_pitch);

	/* save winrect bottom */
	fb_ptr = _rtgui_cursor->framebuffer + (win_rect.y2 - WIN_MOVE_BORDER) * _rtgui_cursor->screen_pitch +
		(win_rect.x1 + WIN_MOVE_BORDER) * _rtgui_cursor->bpp;
	winrect_ptr = _rtgui_cursor->win_bottom;
	display_direct_memcpy(fb_ptr, winrect_ptr, _rtgui_cursor->screen_pitch, winrect_pitch,
		WIN_MOVE_BORDER, winrect_pitch);
}
#endif

void rtgui_mouse_monitor_append(rtgui_list_t* head, rtgui_rect_t* rect)
{
	struct rtgui_mouse_monitor* mmonitor;

	/* check parameters */
	if (head == RT_NULL || rect == RT_NULL) return;

	/* create a mouse monitor node */
	mmonitor = (struct rtgui_mouse_monitor*) rtgui_malloc (sizeof(struct rtgui_mouse_monitor));
	if (mmonitor == RT_NULL) return; /* no memory */

	/* set mouse monitor node */
	mmonitor->rect = *rect;
	rtgui_list_init(&(mmonitor->list));

	/* append to list */
	rtgui_list_append(head, &(mmonitor->list));
}

void rtgui_mouse_monitor_remove(rtgui_list_t* head, rtgui_rect_t* rect)
{
	struct rtgui_list_node* node;
	struct rtgui_mouse_monitor* mmonitor;

	/* check parameters */
	if (head == RT_NULL || rect == RT_NULL) return;

	for (node = head->next; node != RT_NULL; node = node->next)
	{
		mmonitor = rtgui_list_entry(node, struct rtgui_mouse_monitor, list);
		if (mmonitor->rect.x1 == rect->x1 &&
			mmonitor->rect.x2 == rect->x2 &&
			mmonitor->rect.y1 == rect->y1 &&
			mmonitor->rect.y2 == rect->y2)
		{
			/* found node */
			rtgui_list_remove(head, node);
			rtgui_free(mmonitor);

			return ;
		}
	}
}

rt_bool_t rtgui_mouse_monitor_contains_point(rtgui_list_t* head, int x, int y)
{
	struct rtgui_list_node* node;

	/* check parameter */
	if (head == RT_NULL) return RT_FALSE;

	rtgui_list_foreach(node, head)
	{
		struct rtgui_mouse_monitor* monitor = rtgui_list_entry(node,
			struct rtgui_mouse_monitor, list);

		if (rtgui_rect_contains_point(&(monitor->rect), x, y) == RT_EOK)
		{
			return RT_TRUE;
		}
	}

	return RT_FALSE;
}
