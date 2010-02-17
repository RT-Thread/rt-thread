/*
 * File      : title.c
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
#include <rtgui/widgets/title.h>
#include <rtgui/rtgui_system.h>

/* there is no event handler in wintitle but handle the event on topwin of server */
static void _rtgui_wintitle_constructor(rtgui_wintitle_t* wintitle)
{
	wintitle->title = RT_NULL;
	RTGUI_WIDGET(wintitle)->flag = RTGUI_WIDGET_FLAG_DEFAULT;
	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(wintitle)) = RTGUI_ALIGN_CENTER_VERTICAL;
}

static void _rtgui_wintitle_deconstructor(rtgui_wintitle_t* wintitle)
{
	rt_free(wintitle->title);
	wintitle->title = RT_NULL;
}

rtgui_type_t* rtgui_wintitle_type_get()
{
	static rtgui_type_t *wintitle_type = RT_NULL;

	if (!wintitle_type)
	{
		wintitle_type = rtgui_type_create("wintitle", RTGUI_TOPLEVEL_TYPE,
			sizeof(rtgui_wintitle_t), 
			RTGUI_CONSTRUCTOR(_rtgui_wintitle_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_wintitle_deconstructor));
	}

	return wintitle_type;
}

rtgui_wintitle_t* rtgui_wintitle_create(const char* title)
{
	rtgui_wintitle_t* wintitle;

	wintitle = (rtgui_wintitle_t*)rtgui_widget_create(RTGUI_WINTITLE_TYPE);
	if (wintitle != RT_NULL)
	{
		rtgui_wintitle_set_title(wintitle, title);
	}

	return wintitle;
}

void rtgui_wintitle_destroy(rtgui_wintitle_t* wintitle)
{
	rtgui_widget_destroy(RTGUI_WIDGET(wintitle));
}

void rtgui_wintitle_set_title(rtgui_wintitle_t* wintitle, const char* title)
{
	RT_ASSERT(wintitle != RT_NULL);

	if (wintitle->title != RT_NULL)
	{
		rtgui_free(wintitle->title);
	}

	if (title != RT_NULL) wintitle->title = (char*)rt_strdup((const char*)title);
	else wintitle->title = RT_NULL;
}

char *rtgui_wintitle_get_title(rtgui_wintitle_t* wintitle)
{
	RT_ASSERT(wintitle != RT_NULL);

	return wintitle->title;
}
