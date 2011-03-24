/*
 * File      : view.h
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
#ifndef __RTGUI_MENU_H__
#define __RTGUI_MENU_H__

#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/widgets/widget.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int  HMENU;

#define RTGUI_MENU_HEIGHT 43	/*菜单项高度*/
#define RTGUI_MENU_BORDER	2

#define RTGUI_MENU_IMAGE_W	24
#define RTGUI_MENU_IMAGE_H	24

#define ITEM (System,Name,ID) \
rtgui_menu_append(hPopupMenu_##System, MF_ENABLED, ID, Name); 

/*菜单项标志*/
#define RTGUI_MENU_POPUP       		0x00000080L

typedef struct rtgui_menu_item 	rtgui_menu_item_t; //普通菜单
typedef struct rtgui_menu		rtgui_menu_t;//菜单


/** Gets the type of a view */
#define RTGUI_MENU_TYPE       (rtgui_menu_type_get())
/** Casts the object to an rtgui_view_t */
#define RTGUI_MENU(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_MENU_TYPE, rtgui_menu_t))
/** Checks if the object is an rtgui_view_t */
#define RTGUI_IS_MENU(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_MENU_TYPE))

struct rtgui_menu
{        
	rtgui_widget_t			parent;
	char*					name;
	/* 用于辅助绘图的参数,如果无需绘图,去掉这些参数没有影响 */
	rt_uint32_t     		orient;		   /* 排列方向 */
	rt_uint32_t     		item_size;	   /* 菜单项尺寸 */
	rt_uint16_t 			item_count;	   /* 菜单项数 */

	rtgui_menu_item_t*  	current_item;  /* 当前的菜单项 */
	rtgui_menu_item_t*		forego_item;   /* 上一个菜单项 */ 

	/*下级菜单项 */
    rtgui_menu_item_t*  	head;    /*头*/
	rtgui_menu_item_t*  	tail;    /*尾*/
	/*上级菜单项 */
	rtgui_menu_item_t*  	farther; 
};

struct rtgui_menu_item
{
    char*     				caption;  //菜单名
	rt_uint32_t				item_id; 
	rt_uint32_t 			type;	  //菜单的创建类型   
    rt_uint32_t				shortcut;
	rt_bool_t				bexit;	  //调用该菜单后，是否退出菜单
	
	rtgui_menu_item_t* 		next;	 
	rtgui_menu_item_t* 		prev;

	rtgui_image_t*			image;	  //绑定的图标
	rtgui_menu_t* 			sub_menu; //子菜单
	 
	void(*func_updown)(rtgui_menu_t *menu);	//在UP/DOWN动作之后运行的函数
	void(*func_enter)(void);	  //在确认后执行的函数
};

rtgui_type_t *rtgui_menu_type_get(void);

rtgui_menu_t* rtgui_menu_create(PVOID parent, const char* name);
void rtgui_menu_destroy(rtgui_menu_t* menu);


HMENU rtgui_menu_popup_create (void);
rt_bool_t rtgui_menu_append(rtgui_menu_t *menu,rt_uint32_t flags,rt_uint32_t ID,char * caption);
void rtgui_menu_popup_delete(rtgui_menu_t* menu);
rtgui_menu_t* rtgui_menu_item_delete(rtgui_menu_t* menu,rtgui_menu_item_t* pItem);
void rtgui_menu_on_down(rtgui_menu_t* menu);
void rtgui_menu_on_up(rtgui_menu_t* menu);
void rtgui_menu_on_exit(rtgui_menu_t* menu);
void rtgui_menu_set_selected(rtgui_menu_t* menu, int selected);

#ifdef __cplusplus
}
#endif

#endif
