/*
 * File      : edit.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-06-04     amsl         firist version.
 * 2012-08-09     amsl         beta 0.1
 */
#include <rtgui/dc.h>
#include <rtgui/widgets/edit.h>
#include <rtgui/widgets/scrollbar.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/filerw.h>

extern int isprint(unsigned char ch); /* Quote from shell.c */
static void rtgui_edit_draw_caret(struct rtgui_edit *edit);
static void rtgui_edit_timeout(struct rtgui_timer* timer, void* parameter);
static rt_bool_t rtgui_edit_onfocus(struct rtgui_object* object, rtgui_event_t* event);
static rt_bool_t rtgui_edit_onunfocus(struct rtgui_object* object, rtgui_event_t* event);
#ifdef RTGUI_EDIT_USING_SCROLL
static rt_bool_t rtgui_edit_hscroll_handle(struct rtgui_widget* widget, rtgui_event_t* event);
static rt_bool_t rtgui_edit_vscroll_handle(struct rtgui_widget* widget, rtgui_event_t* event);
#endif

void _rtgui_edit_constructor(struct rtgui_edit *edit)
{
	rtgui_rect_t font_rect;
	RTGUI_WIDGET_FLAG(edit) |= RTGUI_WIDGET_FLAG_FOCUSABLE;

	rtgui_object_set_event_handler(RTGUI_OBJECT(edit), rtgui_edit_event_handler);
	rtgui_widget_set_onfocus(RTGUI_WIDGET(edit), rtgui_edit_onfocus);
	rtgui_widget_set_onunfocus(RTGUI_WIDGET(edit), rtgui_edit_onunfocus);
	
	RTGUI_WIDGET_FOREGROUND(edit) = black;
	RTGUI_WIDGET_BACKGROUND(edit) = white;
	/* set default text align */
	RTGUI_WIDGET_TEXTALIGN(edit) = RTGUI_ALIGN_CENTER_VERTICAL;
	rtgui_widget_set_border(RTGUI_WIDGET(edit), RTGUI_BORDER_SUNKEN);
	/* set proper of control */
	edit->caret_timer = RT_NULL;
	edit->caret = RT_NULL;

	edit->tabsize = 4;
	edit->margin  = 1;
	edit->max_rows = edit->max_cols = 0;
	edit->visual.x = edit->visual.y = 0;
	edit->upleft.x = edit->upleft.y = 0;
	edit->row_per_page = edit->col_per_page = 0;

	edit->update_buf = RT_NULL;
	edit->flag = RTGUI_EDIT_NONE;
#ifdef RTGUI_EDIT_USING_SCROLL
	edit->flag |= RTGUI_EDIT_VSCROLL;
	edit->flag |= RTGUI_EDIT_HSCROLL;
#endif
	/* allocate default line buffer */
	edit->bzsize = 16;
	
	rtgui_font_get_metrics(RTGUI_WIDGET_FONT(edit), "H", &font_rect);
	edit->font_width = rtgui_rect_width(font_rect);
	edit->font_height = rtgui_rect_height(font_rect);

	edit->dbl_buf = rtgui_dc_buffer_create(edit->font_width*2+1, edit->font_height+1);
	
	edit->head = RT_NULL;
	edit->tail = RT_NULL;
	edit->first_line = RT_NULL;
#ifdef RTGUI_EDIT_USING_SCROLL	
	edit->hscroll = RT_NULL;
	edit->vscroll = RT_NULL;
#endif
}

void _rtgui_edit_deconstructor(struct rtgui_edit *edit)
{
	if(edit->max_rows > 0)
	{
		while(edit->max_rows > 0)
			rtgui_edit_delete_line(edit, edit->head);
		edit->max_rows = 0;
	}
	if(edit->caret_timer != RT_NULL)
		rtgui_timer_destory(edit->caret_timer);
	edit->caret_timer = RT_NULL;

	if(edit->caret != RT_NULL)
		rtgui_free(edit->caret);
	edit->caret = RT_NULL;
	if(edit->update_buf != RT_NULL)
		rtgui_free(edit->update_buf);

	rtgui_dc_destory(edit->dbl_buf);
}

DEFINE_CLASS_TYPE(edit, "edit",
                  RTGUI_CONTAINER_TYPE,
                  _rtgui_edit_constructor,
                  _rtgui_edit_deconstructor,
                  sizeof(struct rtgui_edit));

#ifdef RTGUI_EDIT_USING_SCROLL
void rtgui_edit_adjust_scroll(rtgui_scrollbar_t *bar)
{
	struct rtgui_edit *edit;
	
	RT_ASSERT(bar != RT_NULL);
	
	if(bar->widget_link != RT_NULL)
	{
		rtgui_rect_t rect;
		rt_uint32_t _left=0,_top=0,_width=RTGUI_DEFAULT_SB_WIDTH,_len=0;

		edit = bar->widget_link;
		rtgui_widget_get_rect(edit, &rect);
		rtgui_widget_rect_to_device(edit,&rect);
		if(bar->orient==RTGUI_HORIZONTAL)
		{
			if(RTGUI_WIDGET_IS_HIDE(edit->hscroll))
			{
				if(edit->max_rows > edit->row_per_page)
				{
					RTGUI_WIDGET_SHOW(edit->hscroll);
					rtgui_scrollbar_set_line_step(edit->hscroll, 1);
					rtgui_scrollbar_set_page_step(edit->hscroll, edit->row_per_page);
					rtgui_scrollbar_set_range(edit->hscroll, edit->max_rows);
				}
				else
					RTGUI_WIDGET_HIDE(edit->vscroll);
				rtgui_widget_update_clip(RTGUI_WIDGET(edit));
			}
			else
			{
				_left = RTGUI_WIDGET_BORDER(edit);
				_top = rtgui_rect_height(rect)-RTGUI_WIDGET_BORDER(edit)-_width;
				_len = rtgui_rect_width(rect)-RTGUI_WIDGET_BORDER(edit)*2;
				
				if(!RTGUI_WIDGET_IS_HIDE(edit->vscroll)) 
					_len -= _width;
				rect.x1 += _left;
				rect.y1 += _top;
				rect.x2 = rect.x1+_len;
				rect.y2 = rect.y1+_width;
			}
		}
		else if(bar->orient==RTGUI_VERTICAL)
		{
			_left = rtgui_rect_width(rect)-RTGUI_WIDGET_BORDER(edit)-_width;
			_top = RTGUI_WIDGET_BORDER(edit);
			_len = rtgui_rect_height(rect)-RTGUI_WIDGET_BORDER(edit)*2;
			
			if(!RTGUI_WIDGET_IS_HIDE(edit->hscroll))  
				_len -= _width;
			rect.x1 += _left;
			rect.y1 += _top;
			rect.x2 = rect.x1+_width;
			rect.y2 = rect.y1+_len;
		}
		rtgui_widget_set_rect(bar,&rect);
	}
}
RTM_EXPORT(rtgui_edit_adjust_scroll);
#endif

struct rtgui_edit* rtgui_edit_create(struct rtgui_container* container, int left, int top, int w, int h)
{
	struct rtgui_edit* edit;

	RT_ASSERT(container != RT_NULL);

	edit = (struct rtgui_edit*)rtgui_widget_create(RTGUI_EDIT_TYPE);
	if(edit != RT_NULL)
	{
		rtgui_rect_t rect;
		int effe;
		rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
		rtgui_widget_rect_to_device(RTGUI_WIDGET(container),&rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+h;
		rtgui_widget_set_rect(RTGUI_WIDGET(edit),&rect);
		rtgui_container_add_child(container, RTGUI_WIDGET(edit));

		/* set character number */
		edit->item_height = edit->font_height; /* the same height */
		effe = h-(edit->margin + RTGUI_WIDGET_BORDER(edit))*2;
		edit->row_per_page = effe / edit->item_height;
		if(effe % edit->item_height)
			edit->row_per_page += 1;
		
		effe = w-(edit->margin + RTGUI_WIDGET_BORDER(edit))*2;
		edit->col_per_page = effe / edit->font_width;
		if(effe % edit->font_width)
			edit->col_per_page += 1;
		edit->update_buf = rtgui_malloc(edit->col_per_page + 1);

#ifdef RTGUI_EDIT_USING_SCROLL
		if(edit->hscroll == RT_NULL && edit->flag & RTGUI_EDIT_HSCROLL)
		{
			/* create horizontal scrollbar */
			rt_uint32_t _left,_top,_width=RTGUI_DEFAULT_SB_WIDTH,_len;
			_left = RTGUI_WIDGET_BORDER(edit);
			_top = rtgui_rect_height(rect)-RTGUI_WIDGET_BORDER(edit)-_width;
			_len = rtgui_rect_width(rect)-RTGUI_WIDGET_BORDER(edit)*2;
			if(edit->max_rows > edit->row_per_page)	_len -= _width;

			edit->hscroll = rtgui_scrollbar_create(edit,_left,_top,_width,_len,RTGUI_HORIZONTAL);

			if(edit->hscroll != RT_NULL)
			{
				edit->hscroll->widget_link = (pvoid)edit;
				edit->hscroll->on_scroll = rtgui_edit_hscroll_handle;
				RTGUI_WIDGET_HIDE(edit->hscroll);
			}
		}
		if(edit->vscroll == RT_NULL && edit->flag & RTGUI_EDIT_VSCROLL)
		{
			/* create vertical scrollbar */
			rt_uint32_t _left,_top,_width=RTGUI_DEFAULT_SB_WIDTH,_len;
			_left = rtgui_rect_width(rect)-RTGUI_WIDGET_BORDER(edit)-_width;
			_top = RTGUI_WIDGET_BORDER(edit);
			_len = rtgui_rect_height(rect)-RTGUI_WIDGET_BORDER(edit)*2;
			if(edit->max_cols > edit->col_per_page) _len -= _width;

			edit->vscroll = rtgui_scrollbar_create(edit,_left,_top,_width,_len,RTGUI_VERTICAL);

			if(edit->vscroll != RT_NULL)
			{
				edit->vscroll->widget_link = (pvoid)edit;
				edit->vscroll->on_scroll = rtgui_edit_vscroll_handle;
				RTGUI_WIDGET_HIDE(edit->vscroll);
			}
		}
#endif
	}

	return edit;
}
RTM_EXPORT(rtgui_edit_create);

void rtgui_edit_destroy(struct rtgui_edit* edit)
{
	rtgui_widget_destroy(RTGUI_WIDGET(edit));
}
RTM_EXPORT(rtgui_edit_destroy);

/**
 * calc line buffer alloc length
 *
 * @param n a standard buffer value, please use edit->bzsize
 * @param m given a reference value
 *
 * @return get a proper standard values 
 */
rt_inline rt_int16_t rtgui_edit_alloc_len(rt_int16_t n, rt_int16_t m)
{
	if(n > m) return n;
#ifndef RTGUI_USING_SMALL_SIZE
	return rtgui_edit_alloc_len(n*2, m);
#else
	return rtgui_edit_alloc_len(n+16, m);
#endif
}

/**
 * please use it to replace rt_strlen
 * especially in reading the source file.
 */
rt_inline rt_int16_t rtgui_edit_line_strlen(const char *s)
{
	const char *sc;
	/* ascii text end of 0x0A or 0x0D-0x0A*/
	for(sc = s; *sc != 0x0D && *sc != 0x0A && *sc != 0x00; ++sc);  
	return sc - s;
}

rt_bool_t rtgui_edit_append_line(struct rtgui_edit* edit, const char *text)
{
	rt_int16_t len;
	struct edit_line *line, *node;

	RT_ASSERT(edit != RT_NULL);

	line = rtgui_malloc(sizeof(struct edit_line));
	if(line == RT_NULL) return RT_FALSE;

	len = rtgui_edit_line_strlen(text);
	line->zsize = rtgui_edit_alloc_len(edit->bzsize, len+1);
	line->text = rtgui_malloc(line->zsize);
	rt_memcpy(line->text, text, len);
	*(line->text+len) = '\0';
	line->len = rtgui_edit_line_strlen(line->text);
	
	line->next = RT_NULL;
	edit->max_rows++;
	if(edit->max_cols < len) edit->max_cols = len;

	node = edit->head;
	if(node == RT_NULL)
	{
		edit->head = line;
		edit->tail = line;
		line->prev = RT_NULL;
		edit->first_line = line;
		return RT_TRUE;
	}
	while(node->next != RT_NULL) node = node->next;
	/* to tail item on to queue */
	node->next = line;
	line->prev = node;
	/* re-fixed position tail */
	edit->tail = line;
	
	return RT_TRUE;
}
RTM_EXPORT(rtgui_edit_append_line);

rt_bool_t rtgui_edit_insert_line(struct rtgui_edit *edit, struct edit_line *p, char *text)
{
	rt_int16_t len;
	struct edit_line *line;

	RT_ASSERT(edit != RT_NULL);
	RT_ASSERT(p != RT_NULL);

	if(p->next == RT_NULL)
	{
		rtgui_edit_append_line(edit, text);
		return RT_TRUE;
	}

	line = rtgui_malloc(sizeof(struct edit_line));
	if(line == RT_NULL) return RT_FALSE;

	line->prev = p;
	line->next = p->next;
	p->next = line;
	if(line->next != RT_NULL)
	{
		line->next->prev = line;
	}

	len = rtgui_edit_line_strlen(text);
	line->zsize = rtgui_edit_alloc_len(edit->bzsize, len+1);
	
	line->text = rtgui_malloc(line->zsize);
	rt_memset(line->text, 0, line->zsize);
	rt_memcpy(line->text, text, len);
	*(line->text+len) = '\0';
	
	edit->max_rows ++;
	line->len = rtgui_edit_line_strlen(line->text);
	
	return RT_TRUE;
}
RTM_EXPORT(rtgui_edit_insert_line);

rt_bool_t rtgui_edit_delete_line(struct rtgui_edit* edit, struct edit_line *line)
{
	RT_ASSERT(edit != RT_NULL);
	RT_ASSERT(line != RT_NULL);

	if(edit->max_rows == 0) return RT_FALSE;

	if(line->prev == RT_NULL)
	{
		if(line->next == RT_NULL)
		{
			/* only one item */
			edit->head = RT_NULL;
			edit->tail = RT_NULL;
		}
		else
		{
			/* first item */
			line->next->prev = RT_NULL;
			edit->head = line->next;
		}
	}
	else
	{
		if(line->next == RT_NULL)
		{
			/* last item */
			line->prev->next = RT_NULL;
			edit->tail = line->prev;
		}
		else
		{
			/* middle item */
			line->prev->next = line->next;
			line->next->prev = line->prev;
		}
	}

	if(edit->max_rows > 0)edit->max_rows--;
	if(line->text)
	{
		rtgui_free(line->text);
		line->text = RT_NULL;
	}
	rtgui_free(line);
	line = RT_NULL;

	return RT_TRUE;
}
RTM_EXPORT(rtgui_edit_delete_line);

rt_bool_t rtgui_edit_connect_line(struct rtgui_edit* edit, struct edit_line *line, struct edit_line *connect)
{
	rt_int16_t len1,len2;
	
	RT_ASSERT(edit != RT_NULL);
	RT_ASSERT(line != RT_NULL);
	RT_ASSERT(connect != RT_NULL);

	len1 = rtgui_edit_line_strlen(line->text);
	len2 = rtgui_edit_line_strlen(connect->text);

	line->zsize = rtgui_edit_alloc_len(edit->bzsize, len1+len2+1);
	line->text = rt_realloc(line->text, line->zsize);
	rt_memcpy(line->text+len1, connect->text, len2);
	*(line->text+len1+len2) = '\0';

	line->len = rtgui_edit_line_strlen(line->text);
	return RT_TRUE;
}
RTM_EXPORT(rtgui_edit_connect_line);

static void rtgui_edit_get_caret_rect(struct rtgui_edit *edit, rtgui_rect_t *rect, rtgui_point_t visual)
{
	RT_ASSERT(edit != RT_NULL);

	rtgui_widget_get_rect(RTGUI_WIDGET(edit), rect);

	rect->x1 += visual.x * edit->font_width + RTGUI_WIDGET_BORDER(edit) + edit->margin;
	rect->x2 = rect->x1+1; /* caret width: 1 */
	rect->y1 += visual.y * edit->item_height + RTGUI_WIDGET_BORDER(edit) + edit->margin;
	if((rect->y1 + edit->font_height) < (rect->y2 - RTGUI_WIDGET_BORDER(edit) - edit->margin))
		rect->y2 = rect->y1 + edit->font_height;
	else
		rect->y2 = rect->y2 - RTGUI_WIDGET_BORDER(edit) - edit->margin;
}

static void rtgui_edit_init_caret(struct rtgui_edit *edit, rtgui_point_t visual)
{
	struct rtgui_graphic_driver *hw_driver = rtgui_graphic_driver_get_default();
	int x, y;
	rtgui_color_t color;
	rtgui_rect_t rect;
	int ofs=0;

	RT_ASSERT(edit != RT_NULL);
	if(!RTGUI_WIDGET_IS_FOCUSED(edit)) return;

	rtgui_edit_get_caret_rect(edit, &edit->caret_rect, visual);
	rect = edit->caret_rect;
	rtgui_widget_rect_to_device(RTGUI_WIDGET(edit), &rect);

	if(edit->caret == RT_NULL)
		edit->caret = (rtgui_color_t*)rtgui_malloc(rtgui_rect_width(rect) * rtgui_rect_height(rect)*sizeof(rtgui_color_t));
	rtgui_timer_stop(edit->caret_timer);

	for(x=rect.x1; x<rect.x2; x++)
	{
		for(y=rect.y1; y<rect.y2; y++)
		{
			hw_driver->ops->get_pixel(&color,x,y);
			*(edit->caret + ofs++) = color;
		}
	}

	rtgui_timer_start(edit->caret_timer);
}

/* draw caret */
static void rtgui_edit_draw_caret(struct rtgui_edit *edit)
{
	int x,y;
	rtgui_color_t color;
	rtgui_rect_t rect;
	int ofs=0;
	struct rtgui_dc *dc;

	RT_ASSERT(edit != RT_NULL);
	if(edit->caret == RT_NULL) return;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(edit));
	if(dc == RT_NULL)return;

	rect = edit->caret_rect;

	for(x=rect.x1; x<rect.x2; x++)
	{
		for(y=rect.y1; y<rect.y2; y++)
		{
			color = *(edit->caret + ofs);
			ofs++;
			if(edit->flag & RTGUI_EDIT_CARET)
			{
				color = ~color;
				rtgui_dc_draw_color_point(dc, x,y, color);
			}
			else
			{
				rtgui_dc_draw_color_point(dc, x,y, color);
			}
		}
	}

	rtgui_dc_end_drawing(dc);
}

static void rtgui_edit_timeout(struct rtgui_timer* timer, void* parameter)
{
	struct rtgui_edit* edit;

	edit = RTGUI_EDIT(parameter);
	/* set caret flag */
	if(edit->flag & RTGUI_EDIT_CARET)
		edit->flag &= ~RTGUI_EDIT_CARET;
	else
		edit->flag |= RTGUI_EDIT_CARET;

	rtgui_edit_draw_caret(edit);

	return;
}

struct edit_line* rtgui_edit_get_line_by_index(struct rtgui_edit *edit, rt_uint32_t index)
{
	struct edit_line *line = RT_NULL;
	
	RT_ASSERT(edit != RT_NULL);
	
	if(edit->head != RT_NULL)
	{
		int i=0;
		line = edit->first_line;
		while(line)
		{
			if((edit->upleft.y + i++)  == index) 
				break;
			line = line->next;
		}
	}
	return line;
}
RTM_EXPORT(rtgui_edit_get_line_by_index);

rt_uint32_t rtgui_edit_get_index_by_line(struct rtgui_edit *edit, struct edit_line *line)
{
	rt_uint32_t  index=0;
	struct edit_line *tmp;
	
	RT_ASSERT(edit != RT_NULL);
	RT_ASSERT(line != RT_NULL);
	
	if(edit->head != RT_NULL)
	{
		tmp = edit->first_line;
		index = edit->upleft.y;
		while(tmp)
		{
			if(tmp == line)
				break;
			index ++;
			tmp = tmp->next;
		}
	}
	return index;
}
RTM_EXPORT(rtgui_edit_get_index_by_line);

enum {
	EDIT_IDENT_DIR_BOTH,
	EDIT_IDENT_DIR_LEFT,
	EDIT_IDENT_DIR_RIGHT
};
/*
* identify a byte is double byte
* @param dir set direction.
* @param *p record the position of the effective.
* @return RT_TRUE is Got it, else not found.
*/
static rt_bool_t identify_double_byte(struct rtgui_edit *edit, struct edit_line *line, 
									  rt_uint32_t dir, rt_int16_t *p)
{
	int index, effe_nums;

	RT_ASSERT(edit != RT_NULL);
	RT_ASSERT(line != RT_NULL);

	if(dir == EDIT_IDENT_DIR_BOTH)
	{
	}
	else if(dir == EDIT_IDENT_DIR_LEFT)
	{
		if(edit->upleft.x == 0 && edit->visual.x == 0)
			return RT_FALSE;
		index = edit->upleft.x + edit->visual.x;
		effe_nums = 0;
		while(index--)
		{
			if((rt_uint8_t)(*(line->text + index)) >= 0x80)
				effe_nums ++;
			else
				break;
		}
		if(effe_nums > 0)
		{
			*p = 2-effe_nums%2;
			return RT_TRUE;
		}
	}
	else if(dir == EDIT_IDENT_DIR_RIGHT)
	{
		if(edit->upleft.x + edit->visual.x == line->len)
			return RT_FALSE;
		index = edit->upleft.x + edit->visual.x;
		effe_nums = 0;
		while(index < line->len)
		{
			if((rt_uint8_t)(*(line->text + index)) >= 0x80)
				effe_nums ++;
			else
				break;
			index ++;
		}
		if(effe_nums > 0)
		{
			*p = 2-effe_nums%2;
			return RT_TRUE;
		}
	}
	return RT_FALSE;
}

static void rtgui_edit_onmouse(struct rtgui_edit* edit, struct rtgui_event_mouse* emouse)
{
	rtgui_rect_t rect;

	RT_ASSERT(edit != RT_NULL);
	RT_ASSERT(emouse != RT_NULL);

	rtgui_widget_get_rect(RTGUI_WIDGET(edit), &rect);
	if((rtgui_region_contains_point(&(RTGUI_WIDGET(edit)->clip), emouse->x, emouse->y, &rect) == RT_EOK))
	{
		rt_uint16_t x, y;

		/* multiline text */
		x = (emouse->x - rect.x1) / (edit->font_width);
		y = (emouse->y - rect.y1) / (edit->item_height);
		if((x < edit->col_per_page) && (y < edit->row_per_page))
		{
			if(emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
			{
				struct edit_line *line;
				rt_int16_t tmp_pos=0;
				
				edit->visual.x = x;
				edit->visual.y = y;
				
				line = rtgui_edit_get_line_by_index(edit, edit->upleft.y+edit->visual.y);
				if(line == RT_NULL)
					return;
				
				if(edit->visual.x > line->len)
					edit->visual.x = line->len;
				if(edit->upleft.x > 0)
				{
					if(edit->upleft.x >= line->len)
						edit->upleft.x = 0;
					else
						edit->visual.x -= edit->upleft.x;
					rtgui_edit_ondraw(edit);
				}
				if(identify_double_byte(edit, line, EDIT_IDENT_DIR_LEFT, &tmp_pos))
					edit->visual.x -= (2-tmp_pos);
				if(edit->flag & RTGUI_EDIT_CARET)
				{
					if(edit->caret_timer != RT_NULL)
						rtgui_timer_stop(edit->caret_timer);

					edit->flag &= ~RTGUI_EDIT_CARET;
					rtgui_edit_draw_caret(edit);

					if(edit->caret_timer != RT_NULL)
						rtgui_timer_start(edit->caret_timer);
				}

				/* set widget focus */
				rtgui_widget_focus(RTGUI_WIDGET(edit));

				if(RTGUI_WIDGET_IS_FOCUSED(edit))
				{
					rtgui_edit_init_caret(edit, edit->visual);
					edit->flag |= RTGUI_EDIT_CARET;
					rtgui_edit_draw_caret(edit);
				}
			}
			else if(emouse->button & RTGUI_MOUSE_BUTTON_UP)
			{
				/* please add codes at here. */
			}
#ifdef RTGUI_EDIT_USING_SCROLL			
			if(edit->vscroll && !RTGUI_WIDGET_IS_HIDE(edit))
			{
				if(!RTGUI_WIDGET_IS_HIDE(edit->vscroll))
					rtgui_scrollbar_set_value(edit->vscroll,edit->upleft.y);
			}
			if(edit->hscroll && !RTGUI_WIDGET_IS_HIDE(edit))
			{
				if(!RTGUI_WIDGET_IS_HIDE(edit->hscroll))
					rtgui_scrollbar_set_value(edit->hscroll,edit->upleft.x);
			}
#endif
		}
	}		
}

rt_inline rt_uint16_t query_shift_code(rt_uint16_t key)
{
	if(key >= RTGUIK_a && key <= RTGUIK_z)
		return (key - ('a'-'A'));
	else
	{
		switch (key)
		{
		case '1': return '!';
		case '2': return '@';
		case '3': return '#';
		case '4': return '$';
		case '5': return '%';
		case '6': return '^';
		case '7': return '&';
		case '8': return '*';
		case '9': return '(';
		case '0': return ')';
		case '-': return '_';
		case '=': return '+';
		case '\\':return '|';
		case ';': return ':';
		case '\'':return '"';
		case ',': return '<';
		case '.': return '>';
		case '/': return '?';
		case '`': return '~';
		}
	}
	return key;
}

rt_inline rt_uint16_t query_caps_code(rt_uint16_t key)
{
	if(key >= RTGUIK_a && key <= RTGUIK_z)
		return (key - ('a'-'A'));
	return key;
}

rt_inline rt_bool_t is_small_keyboard(rt_uint16_t *key)
{
	if(*key >= RTGUIK_KP0 && *key <= RTGUIK_KP9)
	{
		*key = *key - (RTGUIK_KP0 - RTGUIK_0);
		return RT_TRUE;
	}
	else if(*key == RTGUIK_KP_PERIOD)
	{
		*key = '.';
		return RT_TRUE;
	}
	else if(*key == RTGUIK_KP_DIVIDE)
	{
		*key = '/';
		return RT_TRUE;
	}
	else if(*key == RTGUIK_KP_MULTIPLY)
	{
		*key = '*';
		return RT_TRUE;
	}
	else if(*key == RTGUIK_KP_MINUS)
	{
		*key = '-';
		return RT_TRUE;
	}
	else if(*key == RTGUIK_KP_PLUS)
	{
		*key = '+';
		return RT_TRUE;
	}
	else if(*key == RTGUIK_KP_ENTER)
	{
		*key = RTGUIK_RETURN;
		return RT_TRUE;
	}
	return RT_FALSE;
}

void kbd_event_set_key(struct rtgui_event_kbd *ekbd, rt_uint16_t key)
{
	RTGUI_EVENT_KBD_INIT(ekbd);
	ekbd->mod  = RTGUI_KMOD_NONE;
	ekbd->unicode = 0;

	ekbd->key = key;
	ekbd->type = RTGUI_KEYDOWN;
}

static rt_bool_t rtgui_edit_onkey(struct rtgui_object* object, rtgui_event_t* event)
{
	enum { EDIT_NONE, EDIT_ONDRAW, EDIT_UPDATE };
	struct rtgui_edit *edit = RTGUI_EDIT(object);
	struct rtgui_event_kbd *ekbd = (struct rtgui_event_kbd*)event;
	struct edit_line *line=RT_NULL;
	rt_bool_t update_type = EDIT_NONE;
	
	RT_ASSERT(edit != RT_NULL);
	RT_ASSERT(ekbd != RT_NULL);

	if (RTGUI_KBD_IS_UP(ekbd))
	{	/* reset function key */
		if(ekbd->key == RTGUIK_RCTRL || ekbd->key == RTGUIK_LCTRL)
			edit->flag &= ~RTGUI_EDIT_CTRL;
		else if(ekbd->key == RTGUIK_RALT || ekbd->key == RTGUIK_LALT)
			edit->flag &= ~RTGUI_EDIT_ALT;
		else if(ekbd->key == RTGUIK_RSHIFT || ekbd->key == RTGUIK_LSHIFT)
			edit->flag &= ~RTGUI_EDIT_SHIFT;
		else if(ekbd->key == RTGUIK_CAPSLOCK)
			edit->flag &= ~RTGUI_EDIT_CAPSLOCK;
		else if(ekbd->key == RTGUIK_NUMLOCK)
			edit->flag &= ~RTGUI_EDIT_NUMLOCK;
		return RT_TRUE;
	}
	
	line = rtgui_edit_get_line_by_index(edit, edit->upleft.y + edit->visual.y);
	if(line == RT_NULL) 
		return RT_FALSE;

	/* rt_kprintf("key=%04X ",ekbd->key); */
	if(ekbd->key == RTGUIK_RCTRL || ekbd->key == RTGUIK_LCTRL)
	{	/* use CTRL key */
		edit->flag |= RTGUI_EDIT_CTRL;
		return RT_FALSE;
	}
	else if(ekbd->key == RTGUIK_RALT || ekbd->key == RTGUIK_LALT)
	{	/* use ALT key */
		edit->flag |= RTGUI_EDIT_ALT;
		return RT_FALSE;
	}
	else if(ekbd->key == RTGUIK_RSHIFT || ekbd->key == RTGUIK_LSHIFT)
	{	/* use SHIFT key */
		edit->flag |= RTGUI_EDIT_SHIFT;
		return RT_FALSE;
	}
	else if(ekbd->key == RTGUIK_CAPSLOCK)
	{
		edit->flag |= RTGUI_EDIT_CAPSLOCK;
		return RT_FALSE;
	}
	else if(ekbd->key == RTGUIK_NUMLOCK)
	{
		edit->flag |= RTGUI_EDIT_NUMLOCK;
		return RT_FALSE;
	}
	else if(ekbd->key == RTGUIK_DELETE)
	{	/* delete latter character */
		int ofs = edit->upleft.x + edit->visual.x;
		if(ofs > line->len - 1 || (ofs==0 && line->len==0))
		{	/* will the next line marges into the current line */
			struct edit_line* next_line = line->next;
			if(next_line != RT_NULL)
			{
				struct edit_line *update_end_line;
				
				update_type = EDIT_UPDATE;
				edit->update.start = edit->visual;

				rtgui_edit_connect_line(edit, line, next_line);
				rtgui_edit_delete_line(edit, next_line);

				if(edit->max_rows-edit->upleft.y > edit->row_per_page)
				{
					update_end_line = rtgui_edit_get_line_by_index(edit, edit->upleft.y+edit->row_per_page);
					if(update_end_line != RT_NULL)
					{
						edit->update.end.x = edit->col_per_page;
						edit->update.end.y = edit->upleft.y + edit->row_per_page;
					}
				}
				else
				{
					int update_end_index = rtgui_edit_get_index_by_line(edit, edit->tail);
					edit->update.end.x = edit->col_per_page;
					edit->update.end.y = update_end_index+1;
				}
			}
			line->len = rtgui_edit_line_strlen(line->text);
			goto _edit_exit;
		}
		else if(ofs == line->len - 1)
		{
			line->text[ofs] = '\0';
		}
		else
		{
			char *c;
			rt_int16_t tmp_pos=1;
			identify_double_byte(edit, line, EDIT_IDENT_DIR_RIGHT, &tmp_pos);
			/* remove character */
			for(c = &line->text[ofs]; c[tmp_pos] != '\0'; c++)
				*c = c[tmp_pos];
			*c = '\0';
		}
		update_type = EDIT_UPDATE;
		edit->update.start = edit->visual;
		edit->update.end.x = line->len-edit->upleft.x;
		if (edit->update.end.x > edit->col_per_page)
			edit->update.end.x = edit->col_per_page;
		edit->update.end.y = edit->visual.y;
	}
	else if(ekbd->key == RTGUIK_BACKSPACE)
	{	
		if(edit->visual.x == 0)
		{   /* incorporated into prev line */
			struct rtgui_event_kbd event_kbd;
			struct edit_line* prev_line = line->prev;
			if(prev_line != RT_NULL)
			{
				struct edit_line *update_end_line;
				
				update_type = EDIT_UPDATE;
				edit->visual.x = prev_line->len;

				rtgui_edit_connect_line(edit, prev_line, line);
				kbd_event_set_key(&event_kbd, RTGUIK_UP);
				rtgui_edit_onkey(object, (rtgui_event_t*)&event_kbd);
				rtgui_edit_delete_line(edit, line);

				edit->update.start = edit->visual; /* update.start.y is changed */
				if(edit->max_rows-edit->upleft.y > edit->row_per_page)
				{
					update_end_line = rtgui_edit_get_line_by_index(edit, edit->upleft.y+edit->row_per_page);
					if(update_end_line != RT_NULL)
					{
						edit->update.end.x = edit->col_per_page;
						edit->update.end.y = edit->upleft.y + edit->row_per_page;
					}
				}
				else
				{
					int update_end_index = rtgui_edit_get_index_by_line(edit, edit->tail);
					edit->update.end.x = edit->col_per_page;
					edit->update.end.y = update_end_index+1;
				}
			}
			goto _edit_exit;
		}
		
		/* delete front character */
		if(edit->visual.x == line->len)
		{
			rt_int16_t tmp_pos=1;
			identify_double_byte(edit, line, EDIT_IDENT_DIR_LEFT, &tmp_pos);
			line->text[edit->visual.x-tmp_pos] = '\0';
			edit->visual.x -= tmp_pos;
		}
		else if(edit->visual.x != 0)
		{	/* remove current character */
			char *c;
			rt_int16_t tmp_pos=1;
			identify_double_byte(edit, line, EDIT_IDENT_DIR_LEFT, &tmp_pos);
			/* remove character */
			for(c = &line->text[edit->visual.x - tmp_pos]; c[tmp_pos] != '\0'; c++)
			{
				*c = c[tmp_pos];
			}
			*c = '\0';
			edit->visual.x -= tmp_pos;
		}
		/* adjusted line buffer length */
		if(rtgui_edit_alloc_len(edit->bzsize, line->len+2) < line->zsize)
		{	
			line->zsize = rtgui_edit_alloc_len(edit->bzsize, line->len+1);
			line->text = rt_realloc(line->text, line->zsize);
		}
		update_type = EDIT_UPDATE;
		edit->update.start = edit->visual; 
		edit->update.end.x = line->len;
		edit->update.end.y = edit->visual.y;
	}
	else if(ekbd->key == RTGUIK_UP)
	{	/* move to prev line */
		struct edit_line* prev_line;
		if(edit->visual.y > 0)
			edit->visual.y --;
		else
		{
			/* change first row */
			if(edit->upleft.y > 0)
			{
				edit->upleft.y --;
				if(edit->first_line->prev != RT_NULL)
					edit->first_line = edit->first_line->prev;
				update_type = EDIT_ONDRAW;
			}
		}
		
		/* The position of the recount X */
		prev_line = rtgui_edit_get_line_by_index(edit, edit->upleft.y+edit->visual.y);
		if(prev_line == RT_NULL)
			return RT_FALSE;

		if(edit->upleft.x > 0)
		{
			if(prev_line->len <= edit->upleft.x)
			{
				if(prev_line->len <= edit->col_per_page)
				{
					edit->upleft.x = 0;
					edit->visual.x = prev_line->len;
				}
				else
				{
					edit->upleft.x = prev_line->len - (edit->col_per_page-1);
					edit->visual.x = edit->col_per_page-1;
				}
				update_type = EDIT_ONDRAW;
			}
			else if(prev_line->len - edit->upleft.x < edit->col_per_page)
			{
				if(edit->visual.x > prev_line->len - edit->upleft.x)
					edit->visual.x = prev_line->len - edit->upleft.x;
				else
				{
					rt_int16_t tmp_pos=0;
					if(identify_double_byte(edit, prev_line, EDIT_IDENT_DIR_LEFT, &tmp_pos))
						edit->visual.x -= (2-tmp_pos);
				}
			}
		}
		else if(edit->visual.x > prev_line->len)
			edit->visual.x = prev_line->len;
		else if(prev_line->len >= 2)
		{
			rt_int16_t tmp_pos=0;
			if(identify_double_byte(edit, prev_line, EDIT_IDENT_DIR_LEFT, &tmp_pos))
				edit->visual.x -= (2-tmp_pos);
		}

#ifdef RTGUI_EDIT_USING_SCROLL		
		/* update vscroll */
		if(edit->vscroll && !RTGUI_WIDGET_IS_HIDE(edit))
		{
			if(!RTGUI_WIDGET_IS_HIDE(edit->vscroll))
				rtgui_scrollbar_set_value(edit->vscroll,edit->upleft.y);
		}
#endif
	}
	else if(ekbd->key == RTGUIK_DOWN)
	{	
		struct edit_line *tail_line, *next_line;
		tail_line = rtgui_edit_get_line_by_index(edit, edit->upleft.y + edit->visual.y);
		if(tail_line != RT_NULL)
		{	/* it is tail line */
			if(tail_line == edit->tail) return RT_FALSE;
		}
		/* move to next line */
		if(edit->visual.y < edit->row_per_page - 2)
		{
			edit->visual.y ++;
		}
		else if(edit->visual.y+edit->upleft.y < edit->max_rows-1)
		{
			/* change first row */
			edit->upleft.y++;
			if(edit->first_line->next != RT_NULL)
				edit->first_line = edit->first_line->next;
			update_type = EDIT_ONDRAW;
		}
		
		/* adjust next line end position */
		next_line = rtgui_edit_get_line_by_index(edit, edit->upleft.y+edit->visual.y);
		if(next_line == RT_NULL)	
			return RT_FALSE;
		
		if(edit->upleft.x > 0)
		{
			if(next_line->len <= edit->upleft.x)
			{
				if(next_line->len <= edit->col_per_page)
				{
					edit->upleft.x = 0;
					edit->visual.x = next_line->len;
				}
				else
				{
					edit->upleft.x = next_line->len - (edit->col_per_page-1);
					edit->visual.x = edit->col_per_page-1;
				}
				update_type = EDIT_ONDRAW;
			}
			else if(next_line->len - edit->upleft.x < edit->col_per_page)
			{
				if(edit->visual.x > next_line->len - edit->upleft.x)
					edit->visual.x = next_line->len - edit->upleft.x;
				else
				{
					rt_int16_t tmp_pos=0;
					if(identify_double_byte(edit, next_line, EDIT_IDENT_DIR_LEFT, &tmp_pos))
						edit->visual.x -= (2-tmp_pos);
				}
			}
		}
		else if(edit->visual.x > next_line->len)
			edit->visual.x = next_line->len;
		else if(next_line->len >= 2)
		{
			rt_int16_t tmp_pos=0;
			if(identify_double_byte(edit, next_line, EDIT_IDENT_DIR_LEFT, &tmp_pos))
				edit->visual.x -= (2-tmp_pos);
		}

#ifdef RTGUI_EDIT_USING_SCROLL		
		/* update vscroll */
		if(edit->vscroll && !RTGUI_WIDGET_IS_HIDE(edit))
		{
			if(!RTGUI_WIDGET_IS_HIDE(edit->vscroll))
				rtgui_scrollbar_set_value(edit->vscroll,edit->upleft.y);
		}
#endif
	}
	else if(ekbd->key == RTGUIK_LEFT)
	{	/* move to prev char */
		if(edit->visual.x > 0)
		{
			rt_int16_t tmp_pos=1;
			identify_double_byte(edit, line, EDIT_IDENT_DIR_LEFT, &tmp_pos);
			edit->visual.x -= tmp_pos;
			if(edit->visual.x == -1)
			{
				edit->visual.x = 0;
				edit->upleft.x --;
				update_type = EDIT_ONDRAW;
			}
		}
		else
		{
			if(edit->upleft.x > 0)
			{
				rt_int16_t tmp_pos=1;
				identify_double_byte(edit, line, EDIT_IDENT_DIR_LEFT, &tmp_pos);
				edit->upleft.x -= tmp_pos;
				update_type = EDIT_ONDRAW;
			}
			else
			{	
				struct rtgui_event_kbd event_kbd;
				struct edit_line* first_line;
				first_line = rtgui_edit_get_line_by_index(edit, edit->upleft.y + edit->visual.y);
				if(first_line != RT_NULL)
				{	/* it is head line */
					if(first_line == edit->head) return RT_FALSE;
				}
				/* move the caret to the prev line end */
				kbd_event_set_key(&event_kbd, RTGUIK_UP);
				rtgui_edit_onkey(object, (rtgui_event_t*)&event_kbd);
				kbd_event_set_key(&event_kbd, RTGUIK_END);
				rtgui_edit_onkey(object, (rtgui_event_t*)&event_kbd);
			}
		}
	}
	else if(ekbd->key == RTGUIK_RIGHT)
	{	/* move to next char */
		if(line->len >= edit->col_per_page)
		{
			if(edit->upleft.x+edit->col_per_page <= line->len)
			{
				if(edit->visual.x < edit->col_per_page-1)
				{
					rt_int16_t tmp_pos=1;
					identify_double_byte(edit, line, EDIT_IDENT_DIR_RIGHT, &tmp_pos);
					edit->visual.x += tmp_pos;
				}
				else if(edit->visual.x == edit->col_per_page-1)
				{
					if(edit->upleft.x+edit->col_per_page < line->len)
						edit->upleft.x ++;
					else
						edit->upleft.x = line->len - edit->col_per_page + 1;
					update_type = EDIT_ONDRAW;
				}
			}
			else
			{
				struct rtgui_event_kbd event_kbd;
				/* move to next head */
				kbd_event_set_key(&event_kbd, RTGUIK_DOWN);
				rtgui_edit_onkey(object, (rtgui_event_t*)&event_kbd);
				kbd_event_set_key(&event_kbd, RTGUIK_HOME);
				rtgui_edit_onkey(object, (rtgui_event_t*)&event_kbd);
			}
		}
		else
		{
			if(edit->visual.x < line->len)
			{
				rt_int16_t tmp_pos=1;
				identify_double_byte(edit, line, EDIT_IDENT_DIR_RIGHT, &tmp_pos);
				edit->visual.x += tmp_pos;
			}
			else
			{
				struct rtgui_event_kbd event_kbd;
				struct edit_line* tail_line;
				tail_line = rtgui_edit_get_line_by_index(edit, edit->upleft.y + edit->visual.y);
				if(tail_line != RT_NULL)
				{	/* it is tail line */
					if(tail_line == edit->tail) return RT_FALSE;
				}
				/* move the caret to the next line head */
				kbd_event_set_key(&event_kbd, RTGUIK_DOWN);
				rtgui_edit_onkey(object, (rtgui_event_t*)&event_kbd);
				kbd_event_set_key(&event_kbd, RTGUIK_HOME);
				rtgui_edit_onkey(object, (rtgui_event_t*)&event_kbd);
			}
		}
	}
	else if(ekbd->key == RTGUIK_HOME)
	{	/* move cursor to line head */
		edit->visual.x = 0;
		if(edit->upleft.x > 0)
		{
			edit->upleft.x = 0;
			update_type = EDIT_ONDRAW;
		}
	}
	else if(ekbd->key == RTGUIK_END)
	{	/* move cursor to line tail */
		if(line->len >= edit->col_per_page)
		{
			edit->visual.x = edit->col_per_page - 1;
			edit->upleft.x = line->len - (edit->col_per_page-1);
			update_type = EDIT_ONDRAW;
		}
		else
			edit->visual.x = line->len;
	}
	else if(ekbd->key == RTGUIK_TAB)
	{
		int space_nums;
		struct rtgui_event_kbd event_kbd;
		/* using spaces to replace TAB */
		space_nums = edit->tabsize - (edit->upleft.x+edit->visual.x) % edit->tabsize;
		while(space_nums--)
		{
			kbd_event_set_key(&event_kbd, RTGUIK_SPACE);
			rtgui_edit_onkey(object, (rtgui_event_t*)&event_kbd);
		}
	}
	else if(ekbd->key == RTGUIK_RETURN)
	{
		struct edit_line *update_end_line;
		struct rtgui_event_kbd event_kbd;
	
		/* insert a new line buffer */
		rtgui_edit_insert_line(edit, line, line->text + edit->upleft.x + edit->visual.x);
		line->text[edit->upleft.x + edit->visual.x] = '\0';
		line->len = rtgui_edit_line_strlen(line->text);

		if((edit->max_rows-edit->upleft.y) < edit->row_per_page)
		{
			int update_end_index = rtgui_edit_get_index_by_line(edit, edit->tail);
			update_type = EDIT_UPDATE;
			edit->update.start = edit->visual;
			edit->update.end.x = edit->tail->len;
			edit->update.end.y = update_end_index;
		} 
		else
		{
			/* nothing */
			/* it will be adjusted upleft.y when entering DOWN case */
		}
		
		/* move the caret to the next line head */
		kbd_event_set_key(&event_kbd, RTGUIK_DOWN);
		rtgui_edit_onkey(object, (rtgui_event_t*)&event_kbd);
		kbd_event_set_key(&event_kbd, RTGUIK_HOME);
		rtgui_edit_onkey(object, (rtgui_event_t*)&event_kbd);
		/* adjust update line end position */
		if((edit->max_rows-edit->upleft.y) >= edit->row_per_page)
		{	
			update_type = EDIT_UPDATE;
			edit->update.start = edit->visual;
			edit->update.start.y -= 1;
			update_end_line = rtgui_edit_get_line_by_index(edit, edit->upleft.y+edit->row_per_page-1);
			
			if(update_end_line != RT_NULL)
			{
				edit->update.end.x = update_end_line->len;
				edit->update.end.y = edit->upleft.y + edit->row_per_page;
			}
		}
	}
	else
	{
		if(isprint((unsigned char)ekbd->key))
		{	/* it's may print character */
			update_type = EDIT_UPDATE;
			edit->update.start = edit->visual;
			
			if(edit->flag & RTGUI_EDIT_SHIFT)
				ekbd->key = query_shift_code(ekbd->key);
			if(edit->flag & RTGUI_EDIT_CAPSLOCK)
				ekbd->key = query_caps_code(ekbd->key);

			if(line->len < line->zsize-1)
			{
				int ofs = edit->upleft.x + edit->visual.x;
				if(edit->visual.x >= edit->col_per_page-1)
				{
					edit->upleft.x ++;
					update_type = EDIT_ONDRAW;
				}

				if(ofs < line->len)
				{
					char* c;
					for(c = &line->text[line->len]; c != &line->text[ofs]; c--)
						*c = *(c-1);
				}
				line->text[ofs] = (char)ekbd->key;
				if(edit->visual.x < edit->col_per_page-1)
					edit->visual.x ++;
				line->text[line->len+1] = '\0';
				line->len = rtgui_edit_line_strlen(line->text);
				edit->update.end.x = line->len;
				if(edit->update.end.x > edit->col_per_page)
					edit->update.end.x = edit->col_per_page;
				edit->update.end.y = edit->visual.y;
			}
			else
			{	/* adjust line buffer's zone size */
				line->zsize = rtgui_edit_alloc_len(edit->bzsize, line->len+1);
				line->text = rt_realloc(line->text, line->zsize);
				rtgui_edit_onkey(object, event); /* reentry */
			}
		}
		else
		{
			/* Is small keyboard ? */
			if(edit->flag & RTGUI_EDIT_NUMLOCK)
			{
				if(is_small_keyboard(&ekbd->key))
					rtgui_edit_onkey(object, event);
				/* small keyboard another value reserved */
			}
		}
	}
	line->len = rtgui_edit_line_strlen(line->text); 

_edit_exit:
	if(edit->flag & RTGUI_EDIT_CARET)
	{
		if(edit->caret_timer != RT_NULL)
			rtgui_timer_stop(edit->caret_timer);

		edit->flag &= ~RTGUI_EDIT_CARET;
		rtgui_edit_draw_caret(edit);/* refresh it */
		if(edit->caret_timer != RT_NULL)
			rtgui_timer_start(edit->caret_timer);
	}

	/* re-draw edit widget */
	if(update_type == EDIT_ONDRAW)
		rtgui_edit_ondraw(edit);
	else if(update_type == EDIT_UPDATE)
		rtgui_edit_update(edit);

	if(RTGUI_WIDGET_IS_FOCUSED(edit))
	{
		rtgui_edit_init_caret(edit, edit->visual);
		edit->flag |= RTGUI_EDIT_CARET;
		rtgui_edit_draw_caret(edit);
	}
	return RT_TRUE;
}

static rt_bool_t rtgui_edit_onfocus(struct rtgui_object* object, rtgui_event_t* event)
{
	struct rtgui_edit* edit = RTGUI_EDIT(object);

	edit->caret_timer = rtgui_timer_create(50, RT_TIMER_FLAG_PERIODIC,
											rtgui_edit_timeout, (void*)edit);
	/* set caret to show */
	edit->flag |= RTGUI_EDIT_CARET;
	/* start caret timer */
	if(edit->caret_timer != RT_NULL)
		rtgui_timer_start(edit->caret_timer);

	return RT_TRUE;
}

static rt_bool_t rtgui_edit_onunfocus(struct rtgui_object* object, rtgui_event_t* event)
{
	struct rtgui_edit* edit = RTGUI_EDIT(object);

	/* stop caret timer */
	if(edit->caret_timer != RT_NULL)
	{
		rtgui_timer_stop(edit->caret_timer);
		rtgui_timer_destory(edit->caret_timer);
	}
	/* set caret to hide */
	edit->flag &= ~RTGUI_EDIT_CARET;
	rtgui_edit_draw_caret(edit);
	
	return RT_TRUE;
}

#ifdef RTGUI_EDIT_USING_SCROLL
static rt_bool_t rtgui_edit_hscroll_handle(struct rtgui_widget* widget, rtgui_event_t* event)
{
	struct rtgui_edit *edit = RTGUI_EDIT(widget);

	/* adjust first display row when dragging */
	edit->upleft.y = edit->hscroll->value;

	rtgui_edit_ondraw(edit);

	return RT_TRUE;
}

static rt_bool_t rtgui_edit_vscroll_handle(struct rtgui_widget* widget, rtgui_event_t* event)
{
	struct rtgui_edit *edit = RTGUI_EDIT(widget);

	/* adjust first display row when dragging */
	edit->upleft.x = edit->vscroll->value;

	rtgui_edit_ondraw(edit);

	return RT_TRUE;
}
#endif

/* local area update */
void rtgui_edit_update(struct rtgui_edit *edit)
{
	rt_int16_t i,cpy_len=0,prev_len;
	rtgui_rect_t rect, r;
	struct rtgui_dc *dc;
	char *src;
	
	RT_ASSERT(edit != RT_NULL);
	
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(edit));
	if(dc == RT_NULL) return;
	
	rtgui_widget_get_rect(RTGUI_WIDGET(edit), &rect);
	rtgui_rect_inflate(&rect, -(edit->margin + RTGUI_WIDGET_BORDER(edit)));

	if(edit->update_buf == RT_NULL) 
	{   /* try again allocate */
		edit->update_buf = rtgui_malloc(edit->col_per_page+1);
	}
	
	prev_len = edit->col_per_page;
	for(i=edit->update.start.y; i<=edit->update.end.y; i++)
	{
		struct edit_line *line = rtgui_edit_get_line_by_index(edit, edit->upleft.y + i);

		if(i > edit->upleft.y+edit->row_per_page) break;
		if(line == RT_NULL) 
		{	/* when use "RTGUIK_BACKSPACE" backspace forward,
			 * the last line is blank, that only fill background. */
			r.x1 = rect.x1;
			r.x2 = rect.x1 + prev_len * edit->font_width;
			r.y1 = rect.y1 + i * edit->font_height;
			r.y2 = r.y1 + edit->font_height;
			if(r.x2 > rect.x2) r.x2 = rect.x2;
			if(r.y2 > rect.y2) r.y2 = rect.y2;
			rtgui_dc_fill_rect(dc, &r);
			break;
		}
		
		if(edit->update.start.y == edit->update.end.y)
		{
			r.x1 = rect.x1 + edit->update.start.x * edit->font_width;
			r.x2 = rect.x1 + edit->update.end.x * edit->font_width;
			r.y1 = rect.y1 + i * edit->font_height;
			r.y2 = r.y1 + edit->font_height;
			cpy_len = edit->update.end.x - edit->update.start.x;
			src = line->text + edit->update.start.x + edit->upleft.x;
		}
		else 
		{
			if(i == edit->update.start.y)
			{
				r.x1 = rect.x1 + edit->update.start.x * edit->font_width;
				r.x2 = rect.x2;
				r.y1 = rect.y1 + i * edit->font_height;
				r.y2 = r.y1 + edit->font_height;
				cpy_len = line->len - edit->update.start.x - edit->upleft.x;
				if(cpy_len > (edit->col_per_page-edit->update.start.x))
					cpy_len = edit->col_per_page-edit->update.start.x;
				src = line->text + edit->update.start.x + edit->upleft.x;
			}
			else if(i == edit->update.end.y)
			{
				r.x1 = rect.x1;
				r.x2 = rect.x1 + edit->update.end.x * edit->font_width;
				cpy_len = edit->update.end.x;
				r.y1 = rect.y1 + i * edit->font_height;
				r.y2 = r.y1 + edit->font_height;
				src = line->text + edit->upleft.x;
			}
			else
			{
				r.x1 = rect.x1;
				r.x2 = rect.x2;
				r.y1 = rect.y1 + i * edit->font_height;
				r.y2 = r.y1 + edit->font_height;
				cpy_len = line->len - edit->upleft.x;
				if(cpy_len > edit->col_per_page)
					cpy_len = edit->col_per_page;
				src = line->text + edit->upleft.x;
			}
		} 
		if(r.y1 > rect.y2) break;
		if(r.x2 > rect.x2) r.x2 = rect.x2;
		if(r.y2 > rect.y2) r.y2 = rect.y2;
		
		rt_memcpy(edit->update_buf, src, cpy_len);
		*(edit->update_buf + cpy_len) = '\0';
		
		rtgui_dc_fill_rect(dc, &r);
		rtgui_dc_draw_text(dc, edit->update_buf, &r);
		prev_len = line->len;
	}
	
	rtgui_dc_end_drawing(dc);
}

void rtgui_edit_ondraw(struct rtgui_edit *edit)
{
	rtgui_rect_t rect, r;
	struct rtgui_dc *dc;
#ifdef RTGUI_EDIT_USING_SCROLL
	int hscroll_flag=0;
	int vscroll_flag=0;
#endif

	RT_ASSERT(edit != RT_NULL);

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(edit));
	if(dc == RT_NULL) return;

	/* get widget rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(edit), &rect);
	rtgui_rect_inflate(&rect, -RTGUI_WIDGET_BORDER(edit));

	/* fill widget rect with edit background color */
	RTGUI_DC_BC(dc) = RTGUI_WIDGET_BACKGROUND(edit);
	rtgui_dc_fill_rect(dc, &rect);

	rtgui_rect_inflate(&rect, RTGUI_WIDGET_BORDER(edit));
	/* draw border */
	rtgui_dc_draw_border(dc, &rect, RTGUI_WIDGET_BORDER_STYLE(edit));

	rtgui_rect_inflate(&rect, -(edit->margin + RTGUI_WIDGET_BORDER(edit)));

#ifdef RTGUI_EDIT_USING_SCROLL
	if(edit->vscroll && !RTGUI_WIDGET_IS_HIDE(edit->vscroll))
	{
		rect.x2 = rect.x2 - rtgui_rect_width(edit->vscroll->parent.extent);
	}
	if(edit->hscroll && !RTGUI_WIDGET_IS_HIDE(edit->hscroll))
	{
		rect.y2 = rect.y2 - rtgui_rect_height(edit->hscroll->parent.extent);
	}
#endif
	r = rect;
	
	/* draw text */
	if(edit->head != RT_NULL)
	{
		struct edit_line *line = edit->first_line;
		int num=0;
		
		rect.y2 = rect.y1 + edit->item_height;
		while(line)
		{
			rt_int16_t tmp_pos=0, ofs;
			char *str = line->text+edit->upleft.x;

			if(edit->upleft.x < line->len)
			{
				rtgui_point_t p = edit->visual; /* backup */
				edit->visual.x = 0;
				identify_double_byte(edit, line, EDIT_IDENT_DIR_LEFT, &tmp_pos);
				ofs = tmp_pos % 2;
				if(ofs == 1)
				{	/* use dc_buffer draw the left half of double byte */
					char dbl_bmp[3];
					rtgui_point_t pot = {0};
					rtgui_rect_t r = {0};

					pot.x = edit->font_width;
					r.x2 = edit->font_width*2;
					r.y2 = edit->font_height;
					dbl_bmp[0] = *(str-1);
					dbl_bmp[1] = *str;
					dbl_bmp[2] = '\0';
					RTGUI_DC_BC(edit->dbl_buf) = RTGUI_WIDGET_BACKGROUND(edit);
					rtgui_dc_fill_rect(edit->dbl_buf, &r);
					RTGUI_DC_FC(edit->dbl_buf) = RTGUI_WIDGET_FOREGROUND(edit);
					rtgui_dc_draw_text(edit->dbl_buf, dbl_bmp, &r);
					rtgui_dc_blit(edit->dbl_buf, &pot, dc, &rect);
				}
				rect.x1 += ofs * edit->font_width;
				rtgui_dc_draw_text(dc, line->text+edit->upleft.x+ofs, &rect);
				rect.x1 -= ofs * edit->font_width;
				edit->visual = p; /* restore */
			}

			line = line->next;
			
			rect.y1 += edit->item_height;
			if((rect.y1 + edit->item_height) < r.y2)
				rect.y2 = rect.y1 + edit->item_height;
			else
				rect.y2 = r.y2;
			
			if(num++ >= edit->row_per_page)
				break;
		}
	}

#ifdef RTGUI_EDIT_USING_SCROLL
	if(edit->hscroll && !RTGUI_WIDGET_IS_HIDE(edit->hscroll))
	{
		hscroll_flag = 1;
		rtgui_scrollbar_ondraw(edit->hscroll);
	}
	if(edit->vscroll && !RTGUI_WIDGET_IS_HIDE(edit->vscroll))
	{
		vscroll_flag = 1;
		rtgui_scrollbar_ondraw(edit->vscroll);
	}

	if(hscroll_flag && vscroll_flag)
	{
		rtgui_color_t _bc;
		rtgui_widget_get_rect(RTGUI_WIDGET(edit), &rect);
		rect.x1 = rect.x2-RTGUI_WIDGET_BORDER(edit);
		rect.y1 = rect.y2-RTGUI_WIDGET_BORDER(edit);
		_bc = RTGUI_DC_BC(dc);
		RTGUI_DC_BC(dc) = default_background;
		rtgui_dc_fill_rect(dc,&rect);
		RTGUI_DC_BC(dc) = _bc;
	}
#endif
	rtgui_dc_end_drawing(dc);
}

/* set edit text */
void rtgui_edit_set_text(struct rtgui_edit* edit, const char* text)
{
	const char *begin, *ptr;
#ifdef RTGUI_EDIT_USING_SCROLL
	int hscroll_flag=0;
	int vscroll_flag=0;
#endif

	RT_ASSERT(edit != RT_NULL);

	while(edit->max_rows > 0)
		rtgui_edit_delete_line(edit, edit->head);
	edit->max_rows = 0;

	begin = text;
	for(ptr=begin; *ptr != '\0'; ptr++)
	{
		if(*ptr == 0x0A)
		{	/* unix style */
			rtgui_edit_append_line(edit, begin);
			begin = ptr+1;
		}
		else if(*ptr == 0x0D && *(ptr+1) == 0x0A)
		{	/* windows style */
			rtgui_edit_append_line(edit, begin);
			begin = ptr+2;
		}
	}
	if(*ptr == '\0')
	{
		if(begin < ptr)
			rtgui_edit_append_line(edit, begin);
	}
	
#ifdef RTGUI_EDIT_USING_SCROLL
	if(edit->hscroll != RT_NULL)
	{
		if(edit->max_cols > edit->col_per_page)
		{
			RTGUI_WIDGET_SHOW(edit->hscroll);
			rtgui_scrollbar_set_line_step(edit->hscroll, 1);
			rtgui_scrollbar_set_page_step(edit->hscroll, edit->col_per_page);
			rtgui_scrollbar_set_range(edit->hscroll, edit->max_cols);
			hscroll_flag = 1;
		}
		else
		{
			RTGUI_WIDGET_HIDE(edit->hscroll);
		}
	}
	if(edit->vscroll != RT_NULL)
	{
		if(edit->max_rows > edit->row_per_page)
		{
			RTGUI_WIDGET_SHOW(edit->vscroll);
			rtgui_scrollbar_set_line_step(edit->vscroll, 1);
			rtgui_scrollbar_set_page_step(edit->vscroll, edit->row_per_page);
			rtgui_scrollbar_set_range(edit->vscroll, edit->max_rows);
			vscroll_flag = 1;
		}
		else
		{
			RTGUI_WIDGET_HIDE(edit->vscroll);
		}
	}

	if(edit->hscroll != RT_NULL && !RTGUI_WIDGET_IS_HIDE(edit->hscroll))
	{
		rtgui_edit_adjust_scroll(edit->hscroll);
	}
	if(edit->vscroll != RT_NULL && !RTGUI_WIDGET_IS_HIDE(edit->vscroll))
	{
		rtgui_edit_adjust_scroll(edit->vscroll);
	}

	if(hscroll_flag || vscroll_flag)
	{
		rtgui_widget_update_clip(RTGUI_WIDGET(edit));
	}
#endif
}

rt_bool_t rtgui_edit_event_handler(struct rtgui_object* object, rtgui_event_t* event)
{
	rtgui_widget_t *widget = RTGUI_WIDGET(object);
	struct rtgui_edit* edit = RTGUI_EDIT(object);

	switch(event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if(widget->on_draw != RT_NULL)
			widget->on_draw(object, event);
		else
#endif
			rtgui_edit_ondraw(edit);
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
#ifndef RTGUI_USING_SMALL_SIZE
		if(widget->on_mouseclick != RT_NULL)
			widget->on_mouseclick(object, event);
		else
#endif
			rtgui_edit_onmouse(edit, (struct rtgui_event_mouse*)event);
		return RT_TRUE;

	case RTGUI_EVENT_KBD:
#ifndef RTGUI_USING_SMALL_SIZE
		if(widget->on_key != RT_NULL)
			widget->on_key(object, event);
		else
#endif
		rtgui_edit_onkey(object, event);
		return RT_TRUE;

	default:
		return rtgui_widget_event_handler(object, event);
	}

	return RT_FALSE;
}

rtgui_point_t rtgui_edit_get_current_point(struct rtgui_edit *edit)
{
	rtgui_point_t p;

	RT_ASSERT(edit != RT_NULL);

	p.x = edit->upleft.x + edit->visual.x;
	p.y = edit->upleft.y + edit->visual.y;

	return p;
}

rt_uint32_t rtgui_edit_get_mem_consume(struct rtgui_edit *edit)
{
	rt_uint32_t mem_size;
	struct edit_line *line;

	mem_size = sizeof(struct rtgui_edit);
	mem_size += edit->col_per_page + 1; /* update_buf */
	if(edit->head != RT_NULL)
	{
		line = edit->head;
		while(line)
		{
			mem_size += line->zsize;
			mem_size += sizeof(struct edit_line);
			line = line->next;
		}
	}

	return mem_size;
}

#ifdef RTGUI_USING_DFS_FILERW
/** 
 * File access component, General File Access Interface
 */
rt_bool_t rtgui_edit_readin_file(struct rtgui_edit *edit, const char *filename)
{
	struct rtgui_filerw *filerw;
	int num=0, read_bytes, size ,len=0;
	char *text ,ch;

	filerw = rtgui_filerw_create_file(filename, "rb");
	if (filerw == RT_NULL) return RT_FALSE;
	/** 
	 * If it was in the debug of the win32, If document encode is UTF-8 or Unicode,
	 * Will read to garbled code when using the function read documents.
	 * You can Change of the document contains the source code for ANSI. 
	 */
	while(edit->max_rows > 0)
		rtgui_edit_delete_line(edit, edit->head);
	edit->max_rows = 0;

	size = edit->bzsize;
	text = rtgui_malloc(size);
	if(text == RT_NULL) return RT_FALSE;
	
	do {
		if ( (read_bytes = rtgui_filerw_read(filerw, &ch, 1, 1)) > 0 )
		{	/* rt_kprintf("ch=%02X ",ch); DEBUG */
			if(num >= size - 1)
				text = rt_realloc(text, rtgui_edit_alloc_len(size, num));
			if(ch == 0x09) //Tab
			{
				len = edit->tabsize - num%edit->tabsize;
				while(len--)
					*(text + num++) = ' ';
			}
			else
				*(text + num++) = ch;
			if(ch == 0x0A)
			{
				rtgui_edit_append_line(edit, text);
				num = 0;
			}
			
		}
		else if(num > 0)
		{	/* last line does not exist the end operator */
			*(text + num) = '\0';
			rtgui_edit_append_line(edit, text);
		}
	} while(read_bytes);
	
	rtgui_filerw_close(filerw);
	rtgui_free(text);
	rtgui_edit_ondraw(edit);

	return RT_TRUE;
}

rt_bool_t rtgui_edit_saveas_file(struct rtgui_edit *edit, const char *filename)
{
	struct rtgui_filerw *filerw;
	char ch_tailed = 0x0A;
	struct edit_line *line;

	filerw = rtgui_filerw_create_file(filename, "wb");
	if (filerw == RT_NULL) return RT_FALSE;
	
	line = edit->head;
	while(line)
	{
		rtgui_filerw_write(filerw, line->text, line->len, 1);
		if(line != edit->tail)
			rtgui_filerw_write(filerw, &ch_tailed, 1, 1);
		line = line->next;
	}
	
	rtgui_filerw_close(filerw);

	return RT_TRUE;
}
#endif
