/*
 * File      : app.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-06-25     Bernard      first version
 */

/**
 * @addtogroup Loongson SoC3210
 */
/*@{*/
#include <rtthread.h>
#include <soc3210.h>

struct rt_thread thread;
ALIGN(4)
rt_uint8_t thread_stack[1024];

#include <finsh.h>
void thread_entry(void* parameter)
{
	int i = 0;

	while (1)
	{
		rt_kprintf("i = %d, cause: 0x%08x, config: 0x%08x\n", i++, read_c0_cause(), read_c0_config());
		rt_kprintf("HSB_MISC_CFG 0x%08x\n", HSB_MISC_REG);
		rt_thread_delay(100);
	}
}
void thread_test()
{
	rt_err_t result = rt_thread_init(&thread, 
		"tid", 
		thread_entry, RT_NULL,
		&thread_stack, sizeof(thread_stack), 
		200,
		5);
	if (result == RT_EOK)
		rt_thread_startup(&thread);
	else
		rt_kprintf("init thread failed\n");
}
FINSH_FUNCTION_EXPORT(thread_test, test thread!!);

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#endif

int rt_application_init()
{
#ifdef RT_USING_RTGUI
	rtgui_rect_t rect;

	rtgui_system_server_init();

	/* register dock panel */
	rect.x1 = 0;
	rect.y1 = 0;
	rect.x2 = 400;
	rect.y2 = 480;
	rtgui_panel_register("panel", &rect);

	/* register main panel */
	rect.x1 = 400;
	rect.y1 = 0;
	rect.x2 = 800;
	rect.y2 = 480;
	rtgui_panel_register("main", &rect);
	rtgui_panel_set_default_focused("main");

	rt_hw_lcd_init();
#endif

	return 0;
}

/*@}*/
