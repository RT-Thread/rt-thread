/*
 * File      : fileview.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-06     Bernard      first version
 */

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_object.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_theme.h>

#include <rtgui/list.h>
#include <rtgui/image.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/filelist_view.h>
#include <rtgui/widgets/listbox.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/dialog.h>
#include <lcd.h>

#include <uffs/uffs_fd.h>
#include <uffs_ext.h>
#include <dfs_posix.h>

//路径分割符
#define PATH_SEPARATOR		'/'

#include <string.h>

#include "file_hdc.h"		//文件图标

/* image for file and folder */
static rtgui_image_t *file_image   = RT_NULL;
static rtgui_image_t *folder_image = RT_NULL;

static rt_bool_t rtgui_fileview_onunfocus(PVOID wdt, rtgui_event_t* event);
static rt_bool_t rtgui_fileview_sbar_handle(PVOID wdt, rtgui_event_t* event);

static void _rtgui_fileview_constructor(rtgui_filelist_view_t *fview)
{	
	/* set default widget rect and set event handler */
	rtgui_widget_set_event_handler(fview, rtgui_filelist_view_event_handler);
	rtgui_widget_set_onunfocus(fview, rtgui_fileview_onunfocus);
	
	RTGUI_WIDGET_FLAG(fview) |= RTGUI_WIDGET_FLAG_FOCUSABLE;

	fview->frist_aloc = 0;
	fview->now_aloc = 0;
	fview->item_count = 0;
	fview->item_per_page = 0;

	fview->current_dir = RT_NULL;
	fview->pattern = RT_NULL;
	RTGUI_WIDGET_BACKGROUND(fview) = white;
	RTGUI_WIDGET_TEXTALIGN(fview) = RTGUI_ALIGN_CENTER_VERTICAL;
	
	if(file_image==RT_NULL)
		file_image = rtgui_image_create_from_mem("hdc",file_hdc, sizeof(file_hdc), TRUE);
	if(folder_image==RT_NULL)
		folder_image = rtgui_image_create_from_mem("hdc",folder_hdc, sizeof(folder_hdc), TRUE);	

}

static void _rtgui_fileview_destructor(rtgui_filelist_view_t *fview)
{
	rtgui_filelist_view_destroy(fview);	
}

rtgui_type_t *rtgui_filelist_view_type_get(void)
{
	static rtgui_type_t *fileview_type = RT_NULL;
	
	if(!fileview_type)
	{
		fileview_type = rtgui_type_create("fileview", RTGUI_CONTAINER_TYPE,
			sizeof(rtgui_filelist_view_t), 
			RTGUI_CONSTRUCTOR(_rtgui_fileview_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_fileview_destructor));
	}

	return fileview_type;
}


rtgui_filelist_view_t* rtgui_filelist_view_create(PVOID parent, const char* directory, const char* pattern, int left, int top, int w, int h)
{
	rtgui_filelist_view_t* fview = RT_NULL;

	RT_ASSERT(parent != RT_NULL);

	/* create a new view */
	fview = rtgui_widget_create(RTGUI_FILELIST_VIEW_TYPE);

	if(fview != RT_NULL)
	{
		rtgui_rect_t rect;

		rtgui_widget_get_rect(parent, &rect);
		rtgui_widget_rect_to_device(parent,&rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+h;
		
		fview->items = RT_NULL;
		fview->pattern = rt_strdup(pattern);
		fview->item_per_page = rtgui_rect_height(rect) / (1 + SELECTED_HEIGHT);

		rtgui_widget_set_rect(fview,&rect);

		rtgui_container_add_child(parent, fview);
		
		{//创建卷标控件
			rt_uint32_t sLeft,sTop,sw=RTGUI_DEFAULT_SB_WIDTH,sLen;
			sLeft = rtgui_rect_width(rect)-RTGUI_WIDGET_BORDER(fview)-sw;
			sTop = RTGUI_WIDGET_BORDER(fview);

			sLen = rect.y2-rect.y1-RTGUI_WIDGET_BORDER(fview)*2;
			fview->sbar = rtgui_scrollbar_create(fview,sLeft,sTop,sw,sLen,RTGUI_VERTICAL);
			if(fview->sbar != RT_NULL)
			{
				fview->sbar->widgetlnk = fview;
				fview->sbar->on_scroll = rtgui_fileview_sbar_handle;
				RTGUI_WIDGET_HIDE(fview->sbar);//默认隐藏滚动条
			}
		}

		rtgui_filelist_view_set_directory(fview, directory);
	}

	return fview;
}

static void rtgui_filelist_view_clear(rtgui_filelist_view_t* view);

void rtgui_filelist_view_destroy(rtgui_filelist_view_t* fview)
{
    /* delete all file items */
    rtgui_filelist_view_clear(fview);

	/* delete current directory and pattern */
	if(fview->current_dir != RT_NULL)
		rt_free(fview->current_dir);
	fview->current_dir = RT_NULL;

	if(fview->pattern != RT_NULL)
		rt_free(fview->pattern);
	fview->pattern = RT_NULL;

	/* delete image */
	rtgui_image_destroy(file_image);
	file_image = RT_NULL;
	rtgui_image_destroy(folder_image);
	folder_image = RT_NULL;
}

static void rtgui_filelist_view_on_folder_item(rtgui_filelist_view_t *fview)
{
	char* dir_ptr;

	dir_ptr = (char*)rt_malloc(256);
	if(dir_ptr==RT_NULL)
	{
		return;
	}
	//没有子文件夹或子文件，则退出
	if(fview->items==RT_NULL)return;

	rtgui_filelist_view_get_fullpath(fview, dir_ptr, 256);

	rtgui_filelist_view_set_directory(fview, dir_ptr);
	rt_free(dir_ptr);
}

void rtgui_filelist_view_ondraw(rtgui_filelist_view_t* fview)
{
	rt_uint16_t frist, i,rx2;
	rtgui_filelist_view_item_t* item;
	rtgui_rect_t rect, item_rect, image_rect;
	rtgui_dc_t* dc;
	
	RT_ASSERT(fview != RT_NULL);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(fview);
	if(dc == RT_NULL)return;

	rtgui_widget_get_rect(fview, &rect); 
	rtgui_dc_draw_border(dc, &rect,RTGUI_WIDGET_BORDER_STYLE(fview));
	rtgui_rect_inflate(&rect,-RTGUI_WIDGET_BORDER(fview));
	RTGUI_DC_BC(dc) = white;
	rtgui_dc_fill_rect(dc,&rect);
	rtgui_rect_inflate(&rect,RTGUI_WIDGET_BORDER(fview));
	if(fview->sbar && !RTGUI_WIDGET_IS_HIDE(fview->sbar))
		rect.x2 -= rtgui_rect_width(fview->sbar->parent.extent);
	
	rect.x2 -=1; rect.y2 -= 1;

	/* get item base rect */
	item_rect = rect; 
	item_rect.x1 += RTGUI_WIDGET_BORDER(fview);
	item_rect.x2 -= RTGUI_WIDGET_BORDER(fview); rx2 = item_rect.x2;
	item_rect.y1 += RTGUI_WIDGET_BORDER(fview);	
	item_rect.y2 = item_rect.y1 + (1 + SELECTED_HEIGHT);

	/* get image base rect */
	image_rect.x1 = RTGUI_WIDGET_DEFAULT_MARGIN; 
	image_rect.y1 = 0;
	image_rect.x2 = RTGUI_WIDGET_DEFAULT_MARGIN + file_image->w; 
	image_rect.y2 = file_image->h;
	rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);

	
	//取得当前页
	frist = fview->frist_aloc;
	for(i = 0; i < fview->item_per_page; i ++)
	{	
		char str_size[16];

		if(frist + i >= fview->item_count) break;

		item = &(fview->items[frist + i]);

		/* draw item image */
		if(item->type == RTGUI_FITEM_FILE)
			rtgui_image_blit(file_image, dc, &image_rect);
		else
			rtgui_image_blit(folder_image, dc, &image_rect);

        /* draw text */
		item_rect.x1 += RTGUI_WIDGET_DEFAULT_MARGIN + file_image->w + 2;
		item_rect.x2 = item_rect.x1 + rtgui_font_get_string_width(RTGUI_DC_FONT(dc), item->name);
		if(frist + i == fview->now_aloc)
		{
			if(RTGUI_WIDGET_IS_FOCUSED(fview)) 
			{
				RTGUI_DC_BC(dc) = selected_color;
				RTGUI_DC_FC(dc) = white;
			}
			else
			{
				RTGUI_DC_BC(dc) = dark_grey;
				RTGUI_DC_FC(dc) = black;
			}
			rtgui_dc_fill_rect(dc, &item_rect);
			rtgui_dc_draw_text(dc, item->name, &item_rect);
		}
		else
		{
			/* draw background */
			RTGUI_DC_BC(dc) = white;
			RTGUI_DC_FC(dc) = black;
			rtgui_dc_fill_rect(dc,&item_rect);
			rtgui_dc_draw_text(dc, item->name, &item_rect);
		}

		
		{//显示文件大小信息
			rtgui_rect_t rect=item_rect;
			rect.x1 += 265;
			rect.x2 = rect.x1+64;
			if(item->type == RTGUI_FITEM_FILE)
				rt_snprintf(str_size, 32, "%d",item->size);
			else
				rt_snprintf(str_size, 32, "%s","DIR");
			RTGUI_DC_FC(dc) = black;
			rtgui_dc_draw_text(dc, str_size, &rect);
		}
			
		item_rect.x1 -= RTGUI_WIDGET_DEFAULT_MARGIN + file_image->w + 2;
		item_rect.x2 = rx2;
        /* move to next item position */
		item_rect.y1 += (SELECTED_HEIGHT + 1);
		item_rect.y2 += (SELECTED_HEIGHT + 1);

		image_rect.y1 += (SELECTED_HEIGHT + 1);
		image_rect.y2 += (SELECTED_HEIGHT + 1);
	}

	if(fview->sbar && !RTGUI_WIDGET_IS_HIDE(fview->sbar))
	{
		rtgui_theme_draw_scrollbar(fview->sbar);
	}

	rtgui_dc_end_drawing(dc);
}

//更新FileView的界面
void rtgui_filelist_view_update_current(rtgui_filelist_view_t* fview)
{
	rtgui_filelist_view_item_t* item;
	rtgui_rect_t rect, item_rect, image_rect;
	rtgui_win_t* win;
	struct OpenDlgSt *dlgst=RT_NULL;
	rtgui_dc_t* dc;
	
	RT_ASSERT(fview != RT_NULL);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(fview);
	if(dc == RT_NULL)return;

	win = rtgui_win_get_win_by_widget(fview);
	if(win == RT_NULL)return;
	if(win->user_data != RT_NULL)
	{
		dlgst = (struct OpenDlgSt*)win->user_data;
	}

	//当文件夹为空时，不处理
	if(fview->items==RT_NULL)return;

	rtgui_widget_get_rect(fview, &rect);
	if(fview->sbar && !RTGUI_WIDGET_IS_HIDE(fview->sbar))
		rect.x2 -= rtgui_rect_width(fview->sbar->parent.extent);

	if((fview->old_aloc >= fview->frist_aloc) && 
	   (fview->old_aloc < fview->frist_aloc+fview->item_per_page) &&
	   (fview->old_aloc != fview->now_aloc))
	{//这些条件,可以最大限度的减少绘图闪烁现象
		//取得旧的项目
		item_rect = rect;
		item_rect.x1 += RTGUI_WIDGET_BORDER(fview);
		item_rect.x2 -= RTGUI_WIDGET_BORDER(fview);
		item_rect.y1 += RTGUI_WIDGET_BORDER(fview);	
		item_rect.y1 += ((fview->old_aloc-fview->frist_aloc) % fview->item_per_page) * (1 + SELECTED_HEIGHT);
		item_rect.y2 = item_rect.y1 + (1 + SELECTED_HEIGHT);
	
		//取得图像矩形
		image_rect.x1 = RTGUI_WIDGET_DEFAULT_MARGIN; image_rect.y1 = 0;
		image_rect.x2 = RTGUI_WIDGET_DEFAULT_MARGIN + file_image->w; image_rect.y2 = file_image->h;
		rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);
		
		//绘制旧的项目
		item = &(fview->items[fview->old_aloc]);
		if(item->type == RTGUI_FITEM_FILE) /* draw item image */
			rtgui_image_blit(file_image, dc, &image_rect);
		else
			rtgui_image_blit(folder_image, dc, &image_rect);
	
		item_rect.x1 += RTGUI_WIDGET_DEFAULT_MARGIN + file_image->w + 2;
		item_rect.x2 = item_rect.x1 + rtgui_font_get_string_width(RTGUI_DC_FONT(dc), item->name);
		RTGUI_DC_BC(dc) = white;
		RTGUI_DC_FC(dc) = black;
		rtgui_dc_fill_rect(dc,&item_rect);
		rtgui_dc_draw_text(dc, item->name, &item_rect);
	}
	//绘制当前项目
	item_rect = rect;
	item_rect.x1 += RTGUI_WIDGET_BORDER(fview);
	item_rect.x2 -= RTGUI_WIDGET_BORDER(fview);
	item_rect.y1 += RTGUI_WIDGET_BORDER(fview);
	item_rect.y1 += ((fview->now_aloc-fview->frist_aloc) % fview->item_per_page) * (1 + SELECTED_HEIGHT);
	item_rect.y2 = item_rect.y1 + (1 + SELECTED_HEIGHT);

	/* get image base rect */
	image_rect.x1 = RTGUI_WIDGET_DEFAULT_MARGIN; image_rect.y1 = 0;
	image_rect.x2 = RTGUI_WIDGET_DEFAULT_MARGIN + file_image->w; image_rect.y2 = file_image->h;
	rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);

	item = &(fview->items[fview->now_aloc]);
	if(item->type == RTGUI_FITEM_FILE) /* draw item image */
		rtgui_image_blit(file_image, dc, &image_rect);
	else
		rtgui_image_blit(folder_image, dc, &image_rect);

	if(dlgst->filename) rt_free(dlgst->filename);
	dlgst->filename = rt_strdup(item->name);
	dlgst->type = item->type;
	dlgst->size = item->size;

	item_rect.x1 += RTGUI_WIDGET_DEFAULT_MARGIN + file_image->w + 2;
	item_rect.x2 = item_rect.x1 + rtgui_font_get_string_width(RTGUI_DC_FONT(dc), item->name);

	{
		if(RTGUI_WIDGET_IS_FOCUSED(fview)) 
		{
			RTGUI_DC_BC(dc) = selected_color;
			RTGUI_DC_FC(dc) = white;
		}
		else
		{
			RTGUI_DC_BC(dc) = dark_grey;
			RTGUI_DC_FC(dc) = black;	
		}
		rtgui_dc_fill_rect(dc, &item_rect);
		rtgui_dc_draw_text(dc, item->name, &item_rect);
	}
	if(item->type == RTGUI_FITEM_FILE)
		rtgui_textbox_set_value(dlgst->tbox_filename,dlgst->filename);
	RTGUI_DC_FC(dc) = black;
	rtgui_theme_draw_textbox(dlgst->tbox_filename);

	rtgui_dc_end_drawing(dc);
}

void rtgui_filelist_view_on_enter(rtgui_filelist_view_t* fview)
{	
	if(fview->items==RT_NULL)return;
	if(fview->item_count==0)return;

	if(fview->items[fview->now_aloc].type == RTGUI_FITEM_DIR)
	{//文件夹
		rtgui_filelist_view_on_folder_item(fview);
	}
	else
	{//文件
		
	}
}

rt_bool_t rtgui_filelist_view_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_filelist_view_t* fview = RT_NULL;

	fview = RTGUI_FILELIST_VIEW(widget);
	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:
			rtgui_filelist_view_ondraw(fview);
			return FALSE;
	
	    case RTGUI_EVENT_RESIZE:
	        {
				rtgui_event_resize_t* resize;
	
				resize = (rtgui_event_resize_t*)event;
	
	            /* recalculate page items */
				if(file_image != RT_NULL)
					fview->item_per_page = resize->h  / (1 + SELECTED_HEIGHT);
				else
					fview->item_per_page = resize->h / (2 + 14);
	        }
	        break;
	
		case RTGUI_EVENT_MOUSE_BUTTON:
			{
				rtgui_rect_t rect;
				rtgui_event_mouse_t* emouse;
	
				emouse = (rtgui_event_mouse_t*)event;
	
				//计算选择的项目位置
	
				rtgui_widget_focus(fview);
				/* get physical extent information */
				rtgui_widget_get_rect(fview, &rect);
				rtgui_widget_rect_to_device(fview, &rect);
				
				if(fview->sbar && !RTGUI_WIDGET_IS_HIDE(fview->sbar))
					rect.x2 -= rtgui_rect_width(fview->sbar->parent.extent);
				
				if((rtgui_rect_contains_point(&rect, emouse->x, emouse->y) == RT_EOK) && fview->item_count>0)
				{
					rt_uint16_t i;
	
					i = (emouse->y - rect.y1) / (2 + SELECTED_HEIGHT);
					
					/* set focus */
					rtgui_widget_focus(fview);

					if((i < fview->item_count) && (i < fview->item_per_page))
					{
						//设置选择项
						if(emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
						{
							fview->old_aloc = fview->now_aloc;
							fview->now_aloc = fview->frist_aloc + i;
							rtgui_filelist_view_update_current(fview);
						}
						else if(emouse->button & RTGUI_MOUSE_BUTTON_UP)
						{
							if(fview->now_aloc==fview->old_aloc) return FALSE;

							rtgui_filelist_view_update_current(fview);
						}
						if(fview->sbar && !RTGUI_WIDGET_IS_HIDE(fview))
						{
							if(!RTGUI_WIDGET_IS_HIDE(fview->sbar))
								rtgui_scrollbar_set_value(fview->sbar,fview->frist_aloc);
						}
					}
					return TRUE;
				}
			}
			break;
	
	    case RTGUI_EVENT_KBD:
	        {
	            rtgui_event_kbd_t* ekbd = (rtgui_event_kbd_t*)event;
	            if(RTGUI_KBD_IS_DOWN(ekbd))
	            {	
					switch (ekbd->key)
	                {
		                case RTGUIK_UP: //一次上翻一条
							if(fview->now_aloc > 0)
							{
								fview->old_aloc = fview->now_aloc;
								fview->now_aloc --;

								if(fview->now_aloc < fview->frist_aloc)
								{//向上翻页了
									fview->frist_aloc = fview->now_aloc;
									rtgui_filelist_view_ondraw(fview);
								}
								else
								{//当前页中
									rtgui_filelist_view_update_current(fview);
								}

								if(fview->sbar && !RTGUI_WIDGET_IS_HIDE(fview))
								{
									if(!RTGUI_WIDGET_IS_HIDE(fview->sbar))
										rtgui_scrollbar_set_value(fview->sbar,fview->frist_aloc);
								}
							}
							return TRUE;
		
		                case RTGUIK_DOWN: //一次下翻一条
							if(fview->now_aloc < fview->item_count-1)
							{
								fview->old_aloc = fview->now_aloc;
								fview->now_aloc ++;
								
								if(fview->now_aloc >= fview->frist_aloc+fview->item_per_page)
								{//翻页了
									fview->frist_aloc++;
									rtgui_filelist_view_ondraw(fview);
								}
								else
								{//在当前页中
									rtgui_filelist_view_update_current(fview);
								}
								if(fview->sbar && !RTGUI_WIDGET_IS_HIDE(fview))
								{
									if(!RTGUI_WIDGET_IS_HIDE(fview->sbar))
										rtgui_scrollbar_set_value(fview->sbar,fview->frist_aloc);
								}
							}
							return TRUE;
		
						case RTGUIK_LEFT:
							if(fview->item_count==0)return FALSE;
							fview->old_aloc = fview->now_aloc;
							fview->now_aloc -= fview->item_per_page;

							if(fview->now_aloc < 0)
								fview->now_aloc = 0;
							
							if(fview->now_aloc < fview->frist_aloc)
							{
								fview->frist_aloc = fview->now_aloc;
								rtgui_filelist_view_ondraw(fview);
							}
							else
							{
								rtgui_filelist_view_update_current(fview);
							}
							if(fview->sbar && !RTGUI_WIDGET_IS_HIDE(fview))
							{
								if(!RTGUI_WIDGET_IS_HIDE(fview->sbar))
									rtgui_scrollbar_set_value(fview->sbar,fview->frist_aloc);
							}
							return TRUE;
		
						case RTGUIK_RIGHT:
							if(fview->item_count==0)return FALSE;
							fview->old_aloc = fview->now_aloc;
							fview->now_aloc += fview->item_per_page;

							if(fview->now_aloc > fview->item_count-1)
								fview->now_aloc = fview->item_count-1;
							
							if(fview->now_aloc >= fview->frist_aloc+fview->item_per_page)
							{
								fview->frist_aloc += fview->item_per_page;
								if(fview->frist_aloc >fview->item_count-fview->item_per_page)
								{
									fview->frist_aloc = fview->item_count-fview->item_per_page;
									fview->now_aloc = fview->frist_aloc;
								}
								rtgui_filelist_view_ondraw(fview);
							}
							else
							{
								rtgui_filelist_view_update_current(fview);
							}
							if(fview->sbar && !RTGUI_WIDGET_IS_HIDE(fview))
							{
								if(!RTGUI_WIDGET_IS_HIDE(fview->sbar))
									rtgui_scrollbar_set_value(fview->sbar,fview->frist_aloc);
							}
							return TRUE;
		
						case RTGUIK_RETURN:
							//GoToSubFolder(fview,RT_NULL);
							return TRUE;
						case RTGUIK_BACKSPACE:
							//GoToTopFolder(fview,RT_NULL);
							return TRUE;
		                default:
		                    break;
	                }
	            }
	        }
			return FALSE;
		default:
			return rtgui_container_event_handler(widget, event);
	}

    /* use view event handler */
    return rtgui_container_event_handler(widget, event);
}

/* clear all file items */
static void rtgui_filelist_view_clear(rtgui_filelist_view_t* fview)
{
	rt_uint32_t index;
    rtgui_filelist_view_item_t* item;
	
	if(fview->items == RT_NULL) return;
		
	for(index = 0; index < fview->item_count; index ++)
	{
		item = &(fview->items[index]);

		/* release item name */
		if(item->name != RT_NULL)
		{
			rt_free(item->name);
			item->name = RT_NULL;
		}
	}

	/* release items */
	rt_free(fview->items);
	fview->items = RT_NULL;

	fview->item_count = 0;
	fview->now_aloc = 0;
}

void rtgui_filelist_view_set_directory(rtgui_filelist_view_t* fview, const char* directory)
{
	char fullpath[256];
	rtgui_filelist_view_item_t *item;
	rtgui_win_t* win;
	struct OpenDlgSt* dlgst=RT_NULL;
	
	win = rtgui_win_get_win_by_widget(fview);
	if(win == RT_NULL)return;
	if(win->user_data != RT_NULL)
	{
		dlgst = (struct OpenDlgSt*)win->user_data;
	}

	fview->frist_aloc = 0; 

    //首先清除文件项目
    rtgui_filelist_view_clear(fview);
    if(directory != RT_NULL)
    {
		DIR* dir;
		struct stat s;
		rt_uint32_t i;
		struct dirent* dirent;

		fview->item_count = 0;
		//打开文件夹
        dir = opendir(directory);
		if(dir == RT_NULL)  goto __return;

		//设置当前文件夹
		if(fview->current_dir != RT_NULL) 
			rt_free(fview->current_dir);
		fview->current_dir = rt_strdup(directory);

		if(dlgst->path != RT_NULL) rt_free(dlgst->path);
		dlgst->path = rt_strdup(fview->current_dir);

		rtgui_textbox_set_value(dlgst->tbox_path,dlgst->path);
		rtgui_theme_draw_textbox(dlgst->tbox_path);

		do{
			dirent = readdir(dir);
			if(dirent == RT_NULL) break;
			fview->item_count ++; 
		}while (dirent != RT_NULL);
		closedir(dir);

		if((fview->item_count > fview->item_per_page) && fview->sbar!=RT_NULL)
		{
			RTGUI_WIDGET_UNHIDE(fview->sbar);
			rtgui_scrollbar_set_line_step(fview->sbar,1);
			rtgui_scrollbar_set_page_step(fview->sbar, fview->item_per_page);
			rtgui_scrollbar_set_range(fview->sbar, fview->item_count);
		}
		else
		{
			RTGUI_WIDGET_HIDE(fview->sbar);
		}
		rtgui_widget_update_clip(fview);

		//开辟一个可以放下所有项目的空间
		fview->items = (rtgui_filelist_view_item_t*) rt_malloc(sizeof(rtgui_filelist_view_item_t) * fview->item_count);

		if(fview->items == RT_NULL) goto __return; /*under the folder has not sub files. */

		//重新打开文件夹
		dir = opendir(directory);
		if(dir == RT_NULL)  goto __return;

		for(i=0; i < fview->item_count; i ++)
		{
			dirent = readdir(dir);
			if(dirent == RT_NULL) break;

			item = &(fview->items[i]);
			item->name = rt_strdup(dirent->d_name);

			rt_memset(&s, 0, sizeof(struct stat));

			//构建每个文件的全路径
			if(directory[strlen(directory) - 1] != PATH_SEPARATOR)
				rt_sprintf(fullpath, "%s%c%s", directory, PATH_SEPARATOR, dirent->d_name);
			else
				rt_sprintf(fullpath, "%s%s", directory, dirent->d_name);

			stat(fullpath, &s);
			if( s.st_mode & S_IFDIR )
			{
				item->type = RTGUI_FITEM_DIR;
				item->size = 0;
			}
			else
			{
				item->type = RTGUI_FITEM_FILE;
				item->size = s.st_size;
			}
		}

		closedir(dir);
    }

	fview->now_aloc = 0;

__return:
    /* update view */
    rtgui_widget_update(fview);
}

void rtgui_filelist_view_get_fullpath(rtgui_filelist_view_t* view, char* path, rt_size_t len)
{
	RT_ASSERT(view != RT_NULL);

	if(view->current_dir[strlen(view->current_dir) - 1] != PATH_SEPARATOR)
		rt_snprintf(path, len, "%s%c%s",view->current_dir, PATH_SEPARATOR,
			view->items[view->now_aloc].name);
	else
		rt_snprintf(path, len, "%s%s",view->current_dir, 
			view->items[view->now_aloc].name);
}

static rt_bool_t rtgui_fileview_onunfocus(PVOID wdt, rtgui_event_t* event)
{
	rtgui_filelist_view_t *fview = (rtgui_filelist_view_t*)wdt;

	if(fview == RT_NULL) return FALSE;

	if(!RTGUI_WIDGET_IS_FOCUSED(fview))
	{//清除焦点框
		rtgui_filelist_view_update_current(fview);	
	}

	return TRUE;
}

static rt_bool_t rtgui_fileview_sbar_handle(PVOID wdt, rtgui_event_t* event)
{
	rtgui_filelist_view_t *fview = (rtgui_filelist_view_t*)wdt;

	fview->frist_aloc = fview->sbar->value;

	rtgui_filelist_view_ondraw(fview);

	return TRUE;
}


