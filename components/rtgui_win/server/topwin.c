/*
 * File      : win_server.c
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
#include "panel.h"
#include "topwin.h"
#include "mouse.h"
#include <rtgui/rtgui_system.h>

#include <rtgui/event.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>

rtgui_win_t* rtgui_server_focus_win = RT_NULL;

static rtgui_list_t _rtgui_win_show_list;
static rtgui_list_t _rtgui_win_hide_list;

void rtgui_panel_redraw(rtgui_rect_t* rect);

void rtgui_win_init(void)
{
	//初始化窗口列表
	rtgui_list_init(&_rtgui_win_show_list);
	rtgui_list_init(&_rtgui_win_hide_list);
}

static rt_bool_t rtgui_win_search_in_list(rtgui_win_t* win, rtgui_list_t *list)
{
	rtgui_list_t *node;
	rtgui_win_t* wid;

	/* search in list */
	rtgui_list_foreach(node, list)
	{
		wid = rtgui_list_entry(node, rtgui_win_t, list);
		if(wid == win) return RT_TRUE;
	}

	return RT_FALSE;
}

//添加一个窗口到隐藏窗口列表(默认新建的窗口处于隐藏状态)
rt_err_t rtgui_topwin_add(rtgui_win_t* win)
{
	if(win != RT_NULL)
	{
		/* update clip info */
		rtgui_widget_update_clip(win);
		list_insert(&(_rtgui_win_hide_list), &(win->list));
		return RT_EOK;
	}
	return RT_ERROR;
}

/* 移除一个窗口 */
rt_err_t rtgui_topwin_remove(rtgui_win_t* win)
{
	RT_ASSERT(win != RT_NULL);

	if(rtgui_win_search_in_list(win,&_rtgui_win_show_list))
	{	/* in show list */
		rtgui_list_t *node;
		rtgui_win_t *wid;
		rtgui_rect_t rect = RTGUI_WIDGET_EXTENT(win);
		int front_num=0;//计算Z序在当前窗口之上的窗口数量

		/* remove node from list */
		rtgui_list_remove(&_rtgui_win_show_list, &(win->list));

		rtgui_update_external_clip_info();

		rtgui_list_foreach(node, &_rtgui_win_show_list)
		{	
			wid = rtgui_list_entry(node, rtgui_win_t, list);
			/* 更新"已显示"窗口中与"刚删除的窗口"重叠的区域 */
			rtgui_toplevel_update_clip(wid, &rect, front_num);
			rtgui_win_ondraw(wid);
			front_num++;
		}

		/* 激活下一个窗口 */
		if(_rtgui_win_show_list.next != RT_NULL)
		{
			rtgui_win_t* wnd = rtgui_list_entry(_rtgui_win_show_list.next,rtgui_win_t, list);
			
			rtgui_topwin_raise(wnd);
			rtgui_server_focus_win = wnd;
		}
		else
		{
			/* 没有可以显示的窗口 */
			rtgui_server_focus_win = RT_NULL;
		}
		
		rtgui_panel_redraw(&rect);

		return RT_EOK;
	}
	else if(rtgui_win_search_in_list(win, &_rtgui_win_hide_list))
	{//在"隐藏"列表中
		/* remove node from list */
		rtgui_list_remove(&_rtgui_win_hide_list, &(win->list));
		return RT_EOK;
	}
	
	return RT_ERROR;
}

/* activate a win
 */
rt_err_t rtgui_topwin_activate(rtgui_win_t* win)
{	
	if((rtgui_server_focus_win != RT_NULL) && (rtgui_server_focus_win != win))
	{
		rtgui_topwin_deactivate(rtgui_server_focus_win);
	}
	
	win->status |= RTGUI_WIN_STATUS_ACTIVATE;
	rtgui_server_focus_win = win;

	rtgui_widget_update_clip(win);

	rtgui_widget_focus(win);
	rtgui_widget_update(win);

	return RT_EOK;
}

/*
 * deactivate a win
 */
rt_err_t rtgui_topwin_deactivate(rtgui_win_t* win)
{
	win->status &= ~RTGUI_WIN_STATUS_ACTIVATE;

	/* 该窗口在之前应该是活动的,所有可以直接绘图 */
	rtgui_theme_draw_win_title(win);

	if(rtgui_server_focus_win == win)
	{
		rtgui_server_focus_win = RT_NULL;
	}

	return RT_EOK;
}

/* raise window to front 将指定窗口提升为当前窗口 */
rt_err_t rtgui_topwin_raise(rtgui_win_t* win)
{
	RT_ASSERT(win != RT_NULL);

	/* find the twin node */	
	if(rtgui_win_search_in_list(win, &_rtgui_win_show_list))
	{//窗口在显示列表中
		rtgui_list_t *node;
		rtgui_win_t *wid;
		rtgui_rect_t rect = RTGUI_WIDGET_EXTENT(win);
		int front_num = 0;

		/* the window is already placed in front */
		if(&(win->list) == _rtgui_win_show_list.next)
		{/* 该窗口已经在最前面 */
			rtgui_server_focus_win = RT_NULL;
			rtgui_topwin_activate(win);
		    return RT_EOK;
		}

		if(rtgui_server_focus_win != RT_NULL && rtgui_server_focus_win != win)
		{/* 旧窗口置为非活动状态 */
			rtgui_topwin_deactivate(rtgui_server_focus_win);	
		}

		rtgui_list_foreach(node, &_rtgui_win_show_list)
		{/* 更新各窗口的剪切域 */
			wid = rtgui_list_entry(node, rtgui_win_t, list); 
			//除了"输入法"窗口,当前窗口不会被任何窗口覆盖
			if(wid == win) 
			{
				front_num++;
				continue;
			}
			//其它窗口则需要剪切掉当前窗口
			rtgui_toplevel_update_clip(wid, &rect, front_num);
			rtgui_win_ondraw(wid); //这个地方采用区域绘图效果会更好
			front_num++;			
		}
		
		/* remove node from list */
		rtgui_list_remove(&_rtgui_win_show_list, &(win->list));
		/* add to front */
		list_insert(&_rtgui_win_show_list, &(win->list));
		
		//新窗口置为活动状态
		rtgui_topwin_activate(win);

		return RT_EOK;
	}

	return RT_ERROR;
}

/* show a window */
rt_err_t rtgui_topwin_show(rtgui_win_t* win)
{
	rtgui_panel_t *panel = rtgui_panel_get();

	/* find it */
	if(win != RT_NULL)
	{	
		if(rtgui_win_search_in_list(win, &_rtgui_win_hide_list))
		{//在隐藏列表中
			/* remove node from hidden list */
			rtgui_list_remove(&_rtgui_win_hide_list, &(win->list));
	
			/* add node to show list */
			list_insert(&_rtgui_win_show_list, &(win->list));
			rtgui_update_external_clip_info();
			rtgui_panel_update_clip(panel);
			
			RTGUI_WIDGET_UNHIDE(win);
			
			/* activate this window */
			rtgui_topwin_activate(win);
		}
		else if(rtgui_win_search_in_list(win, &_rtgui_win_show_list))
		{//在显示列表中
			/* just raise it */
			rtgui_topwin_raise(win);
		}
		
		return RT_EOK;
	}
	
	return RT_ERROR;
}

/* hide a window */
rt_err_t rtgui_topwin_hide(rtgui_win_t* win)
{
	rtgui_panel_t *panel = rtgui_panel_get();

	/* found it */
	if(win != RT_NULL)
	{
		/* remove node from show list */
		rtgui_list_remove(&_rtgui_win_show_list, &(win->list));
		rtgui_update_external_clip_info();
		rtgui_panel_update_clip(panel);
		/* add node to hidden list */
		list_insert(&_rtgui_win_hide_list, &(win->list));

		/* redraw the old rect */
		rtgui_panel_redraw(&(RTGUI_WIDGET_EXTENT(win)));

		if(rtgui_server_focus_win == win)
		{
			/* activate the next window */
			if(_rtgui_win_show_list.next != RT_NULL)
			{
				/* get the win */
				win = rtgui_list_entry(_rtgui_win_show_list.next,rtgui_win_t, list);
				rtgui_server_focus_win = RT_NULL;
				rtgui_topwin_activate(win);
			}
			else
			{
				/* there is no shown window right now */
				rtgui_server_focus_win = RT_NULL;
			}
		}
		
		return RT_EOK;
	}
	
	return RT_ERROR;
}

/* move top window */
rt_err_t rtgui_topwin_move(rtgui_win_t* win, int x, int y)
{
	rtgui_panel_t *panel = rtgui_panel_get();

	if(win != RT_NULL)
	{
		int dx, dy;
		rtgui_list_t *node;
		rtgui_win_t *wid;
		rtgui_rect_t rect = RTGUI_WIDGET_EXTENT(win);
		int front_num = 0;

		/* get the delta move x, y */
		dx = x - RTGUI_WIDGET(win)->extent.x1;
		dy = y - RTGUI_WIDGET(win)->extent.y1;

		/* move window rect */
		rtgui_widget_move_to_logic(RTGUI_WIDGET(win), dx, dy);

		/* 窗口移动了,需要更新external信息 */
		rtgui_update_external_clip_info();

		rtgui_list_foreach(node, &_rtgui_win_show_list)
		{/* 更新各窗口的剪切域 */
			wid = rtgui_list_entry(node, rtgui_win_t, list);
			if(wid == win)
			{
				front_num++;
				continue;
			}
			rtgui_toplevel_update_clip(wid, &rect, front_num);
			rtgui_win_ondraw(wid);
			front_num++;
		}

		/* 当前窗口是活动的,直接更新它的clip */
		rtgui_widget_update_clip(win);
		rtgui_widget_update(win);

		/* update old window coverage area */
		rtgui_panel_redraw(&rect);

		rtgui_topwin_activate(win);
		return RT_EOK;
	}

	return RT_ERROR;
}

/*
 * resize a top win
 * Note: currently, only support resize hidden window
 */
rt_err_t rtgui_topwin_resize(rtgui_win_t* win, rtgui_rect_t* r)
{
	if(win != RT_NULL)
	{
		RTGUI_WIDGET_EXTENT(win) = *r;

		/* update title & border clip info */
		rtgui_widget_update_clip(win);

		return RT_EOK;
	}

	return RT_ERROR;
}

rtgui_win_t* rtgui_topwin_get_wnd(int x, int y)
{
	rtgui_list_t* node;
	rtgui_win_t* win;

	/* search in show win list */
	if(_rtgui_win_show_list.next != RT_NULL)
	{
		rtgui_list_foreach(node, &(_rtgui_win_show_list))
		{
			win = rtgui_list_entry(node, rtgui_win_t, list);
	
			/* is this window? */
			if(rtgui_rect_contains_point(&(RTGUI_WIDGET_EXTENT(win)), x, y) == RT_EOK)
			{
				return win;
			}
		}
	}
	return RT_NULL;
}

//front_num: 需要剪切掉的topwin层数,只剪切Z序在自己之上的
void rtgui_toplevel_update_clip(PVOID wdt, rtgui_rect_t *rect, int front_num)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_widget_t *child;
	rtgui_list_t *node;
	rtgui_rect_t new_rect;

	new_rect = widget->extent;

	if(rtgui_rect_is_intersect(rect, &new_rect) == RT_EOK)
	{//两个区域相交		
		rtgui_rect_intersect(rect, &new_rect);//计算重叠的区域
		rtgui_region_reset(&(widget->clip), &new_rect);//将重叠区域作为剪切域 
		
		if(front_num > 0)	
		{
			rt_int32_t i;
			rtgui_rect_t *ext_rect;
			
			ext_rect = external_clip_rect;
			for(i=0;i<front_num;i++)
			{
				rtgui_region_subtract_rect(&(widget->clip), &(widget->clip),ext_rect);
				ext_rect++;
			}
		}	
	}
	else
	{			
		rtgui_region_reset(&(widget->clip), &rtgui_empty_rect);
	}

	{/* 将控件clip限定在屏幕之内 */
		rtgui_rect_t screen_rect;
		rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(),&screen_rect);
		rtgui_region_intersect_rect(&(widget->clip), &(widget->clip), &screen_rect);
	}

	if(RTGUI_IS_CONTAINER(widget))
	{/* 是容器控件,则更新rect范围内的子控件 */
		rtgui_list_foreach(node, &(RTGUI_CONTAINER(widget)->children))
		{	
			child = rtgui_list_entry(node, rtgui_widget_t, sibling);
			if(RTGUI_WIDGET_IS_HIDE(child))continue;
			/* 复位子控件Clip */
			rtgui_region_subtract_rect(&(widget->clip), &(widget->clip),&(child->extent));
			rtgui_toplevel_update_clip(child, rect, front_num);
		}
	}
}

void rtgui_panel_redraw(rtgui_rect_t* rect)
{
	rtgui_panel_t *panel = rtgui_panel_get();

	rtgui_toplevel_update_clip(panel,rect,external_clip_size);
	rtgui_theme_draw_panel(panel);
	/* reset panel clip */
	rtgui_update_external_clip_info();
	rtgui_panel_update_clip(panel);
}

void rtgui_topwin_title_onmouse(rtgui_win_t* win, rtgui_event_mouse_t* event)
{
	rtgui_rect_t rect;
	
	if(event->button & RTGUI_MOUSE_BUTTON_LEFT)
	{
		if(event->button & RTGUI_MOUSE_BUTTON_DOWN)
		{//鼠标按键按下
			if(win->style & RTGUI_WIN_CLOSEBOX)
			{//关闭
				rtgui_win_get_closebox_rect(win, &rect);
				rtgui_widget_rect_to_device(win, &rect);
				if(rtgui_rect_contains_point(&rect, event->x, event->y) == RT_EOK)
				{
					win->style |= RTGUI_WIN_CLOSEBOX_PRESSED;
					rtgui_theme_draw_win_closebox(win);
					return;
				}
			}
			if(win->style & RTGUI_WIN_MAXBOX)
			{//最大化
				rtgui_win_get_maxbox_rect(win, &rect);
				rtgui_widget_rect_to_device(win, &rect);
				if(rtgui_rect_contains_point(&rect, event->x, event->y) == RT_EOK)
				{
					win->style |= RTGUI_WIN_MAXBOX_PRESSED;
					rtgui_theme_draw_win_maxbox(win);
					return;
				}
			}
			if(win->style & RTGUI_WIN_MINBOX)
			{//最小化
				rtgui_win_get_minbox_rect(win, &rect);
				rtgui_widget_rect_to_device(win, &rect);
				if(rtgui_rect_contains_point(&rect, event->x, event->y) == RT_EOK)
				{
					win->style |= RTGUI_WIN_MINBOX_PRESSED;
					rtgui_theme_draw_win_minbox(win);
					return;
				}
			}
#ifdef RTGUI_USING_WINMOVE
			/* maybe move window */
			rtgui_cursor_set_location(event->x, event->y);
			rtgui_winrect_set(win);
#endif
		}
		else if(event->button & RTGUI_MOUSE_BUTTON_UP)
		{//数遍按键弹起
			if(win->style & RTGUI_WIN_CLOSEBOX)
			{//关闭
				rtgui_win_get_closebox_rect(win, &rect);
				rtgui_widget_rect_to_device(win, &rect);
				if(rtgui_rect_contains_point(&rect, event->x, event->y) == RT_EOK)
				{
					rtgui_event_win_t event;

					win->style &= ~RTGUI_WIN_CLOSEBOX_PRESSED;
					rtgui_theme_draw_win_closebox(win);

					/* 发送"关闭窗口"事件 */
					RTGUI_EVENT_WIN_CLOSE_INIT(&event);
					event.wid = win;	 
					
					rtgui_thread_send(win->tid, RTGUI_EVENT(&event), sizeof(rtgui_event_win_t));
					
					return;
				}
			}
			if(win->style & RTGUI_WIN_MAXBOX)
			{//最大化
				rtgui_win_get_maxbox_rect(win, &rect);
				rtgui_widget_rect_to_device(win, &rect);
				if(rtgui_rect_contains_point(&rect, event->x, event->y) == RT_EOK)
				{
					rtgui_event_win_t ewin;
	
					win->style &= ~RTGUI_WIN_MAXBOX_PRESSED;
					rtgui_theme_draw_win_maxbox(win);
	
					/* send close event to window */
					RTGUI_EVENT_WIN_MAX_INIT(&ewin);
					ewin.wid = win;
					rtgui_thread_send(win->tid, &(ewin.parent), sizeof(rtgui_event_win_t));
					return;
				}
			}
			if(win->style & RTGUI_WIN_MINBOX)
			{//最小化
				rtgui_win_get_minbox_rect(win, &rect);
				rtgui_widget_rect_to_device(win, &rect);
				if(rtgui_rect_contains_point(&rect, event->x, event->y) == RT_EOK)
				{
					rtgui_event_win_t ewin;
	
					win->style &= ~RTGUI_WIN_MINBOX_PRESSED;
					rtgui_theme_draw_win_minbox(win);
	
					/* send close event to window */
					RTGUI_EVENT_WIN_MIN_INIT(&ewin);
					ewin.wid = win;
					rtgui_thread_send(win->tid, &(ewin.parent), sizeof(rtgui_event_win_t));
					return;
				}
			}
		}
	}
}

void rtgui_panel_update_clip(PVOID wdt)
{
	rtgui_list_t *node;
	rtgui_widget_t *child=RT_NULL, *widget;
	
	widget = (rtgui_widget_t*)wdt;

	rtgui_region_reset(&(widget->clip), &(widget->extent));
	//裁剪panel Clip
	
	if(external_clip_size > 0)	
	{
		rt_int32_t i;
		rtgui_rect_t *rect;
		rect = external_clip_rect;
		for(i=0;i<external_clip_size;i++)
		{
			rtgui_region_subtract_rect(&(widget->clip), &(widget->clip),rect);
			rect++;
		}
	}

	if(RTGUI_IS_CONTAINER(widget))
	{//首先复位panel下的子控件Clip
		rtgui_list_foreach(node, &(RTGUI_CONTAINER(widget)->children))
		{	
			child = rtgui_list_entry(node, rtgui_widget_t, sibling);
			if(RTGUI_WIDGET_IS_HIDE(child))continue;
			//if(RTGUI_IS_WIN(child))continue; //窗口不在这里处理
			//复位子控件Clip
			rtgui_region_subtract_rect(&(widget->clip), &(widget->clip),&(child->extent));
			rtgui_panel_update_clip(child);
		}
	}		
}

//更新Panel Clip时使用
void rtgui_update_external_clip_info(void)
{
	rtgui_rect_t *rect;
	rtgui_win_t *win;
	rtgui_list_t *node;
	rt_uint32_t count=0;
	rtgui_panel_t *panel=rtgui_panel_get();

	RT_ASSERT(panel != RT_NULL);

	if(external_clip_size > 0)
	{//清除原有数据
		rt_free(external_clip_rect);
		external_clip_rect = RT_NULL;
		external_clip_size = 0;
	}

	rtgui_list_foreach(node, &_rtgui_win_show_list)
	{//计算窗口个数
		count ++;
	}
	
	external_clip_rect = (rtgui_rect_t*)rt_malloc(sizeof(rtgui_rect_t)*count);
	external_clip_size = count;
	
	//rt_kprintf("external_clip_size=%d\n",external_clip_size);

	rect = external_clip_rect;

	rtgui_list_foreach(node, &_rtgui_win_show_list)
	{
		win = rtgui_list_entry(node, rtgui_win_t, list);
		*rect = RTGUI_WIDGET_EXTENT(win);
		rect ++;
	}
}

#ifdef RT_USING_FINSH
#include <finsh.h>
//列印窗口列表
rt_bool_t list_win(void)
{
	rtgui_list_t *node;
	rtgui_win_t* win;

	rt_kprintf("window'name      thread'name      modal            window'id\n");
	rt_kprintf("---------------- ---------------- ---------------- ----------\n");
	/* search in list */
	rtgui_list_foreach(node, &_rtgui_win_show_list)
	{
		win = rtgui_list_entry(node, rtgui_win_t, list);

		if(win != RT_NULL)
		{
			rt_kprintf("%-16s %-16s %-16s 0x%08X\n",
				win->title,win->tid->name,
				((RTGUI_WIN_IS_MODAL_MODE(win))?"MODAL_OK":"MODAL_CANCEL"),
				win);
		}
	}
	if(rtgui_server_focus_win != RT_NULL)
	{
		win = rtgui_server_focus_win;
		rt_kprintf("activate win=%-s,ID=0x%08X, st=%08X\n",
				win->title,win,win->status);
	}

	return RT_TRUE;
}
FINSH_FUNCTION_EXPORT(list_win, list show window);
#endif
