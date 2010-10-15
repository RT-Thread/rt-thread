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

#include <rtgui/rtgui.h>
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>

int rt_application_init()
{
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

	/* init example workbench */
	// workbench_init();

	return 0;
}

/* key simulator */
static struct rtgui_event_kbd kbd_event;
void key_simulator(int key)
{
    /* init keyboard event */
    RTGUI_EVENT_KBD_INIT(&kbd_event);
    kbd_event.mod  = RTGUI_KMOD_NONE;
    kbd_event.unicode = 0;
    kbd_event.type = RTGUI_KEYDOWN;
	kbd_event.key  = key;

	/* post down event */
	rtgui_server_post_event(&(kbd_event.parent), sizeof(kbd_event));
	
	/* delay to post up event */
	rt_thread_delay(50);

	/* post up event */
	kbd_event.type = RTGUI_KEYUP;
	rtgui_server_post_event(&(kbd_event.parent), sizeof(kbd_event));
}

void left()
{
	key_simulator(RTGUIK_LEFT);
}
FINSH_FUNCTION_EXPORT(left, left key);

void right()
{
	key_simulator(RTGUIK_LEFT);
}
FINSH_FUNCTION_EXPORT(right, right key);

void down()
{
	key_simulator(RTGUIK_DOWN);
}
FINSH_FUNCTION_EXPORT(down, down key);

void up()
{
	key_simulator(RTGUI_KEYUP);
}
FINSH_FUNCTION_EXPORT(up, up key);

/*@}*/
