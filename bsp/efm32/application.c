/***************************************************************************//**
 * @file    application.c
 * @brief   application tasks
 *  COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author  Bernard, onelife
 * @version 0.4 beta
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2009-01-05   Bernard     first version
 * 2010-12-29   onelife     Modify for EFM32
 * 2011-05-06   onelife     Add SPI Flash DEMO
 * 2011-07-15   onelife     Add accelerometer DEMO
 * 2011-07-27   onelife     Modify Ethernet DEMO
 * 2011-08-23   onelife     Modify Ethernet DEMO according to the changes of
 *  lwIP API in reversion 1668
 * 2011-12-20   onelife     Add LCD DEMO
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <board.h>

#if defined(RT_USING_DFS)
/* dfs init */
#include <dfs_init.h>
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#include "dev_led.h"
#if defined(EFM32_USING_ACCEL)
#include "dev_accel.h"
#endif
#if defined(EFM32_USING_SFLASH)
#include "dev_sflash.h"
#endif
#if defined(EFM32_USING_SPISD)
#include "drv_sdcard.h"
#endif
#if defined(EFM32_USING_ETHERNET)
#include "drv_ethernet.h"
#endif
#if defined(EFM32_USING_LCD)
#include "dev_lcd.h"

#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/workbench.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/box.h>

#endif


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile rt_uint32_t    rt_system_status = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static rt_uint8_t index = 0 ;
static rt_bool_t view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		struct rtgui_rect rect;

		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL)
            return RT_FALSE;
		rtgui_widget_get_rect(widget, &rect);

		rtgui_dc_fill_rect(dc, &rect);
		rect.x2 -= 1; rect.y2 -= 1;
		rtgui_dc_draw_hline(dc, rect.x1, rect.x2, rect.y1);
		rtgui_dc_draw_vline(dc, rect.x1, rect.y1, rect.y2);

		rtgui_dc_draw_hline(dc, rect.x1, rect.x2, rect.y2);
		rtgui_dc_draw_vline(dc, rect.x2, rect.y1, rect.y2 + 1);

        /* shrink border */
		rtgui_rect_inflate(&rect, -1);

		/* draw text */
        rtgui_widget_get_rect(widget, &rect);
        rect.y1 += 25;
        rtgui_dc_draw_text(dc, "  EFM3 EFM32GG_DK3750 Kit", &rect);
        rect.y1 += 10;
        rtgui_dc_draw_text(dc, "  RT-Thread & RTGUI", &rect);
        rect.y1 += 10;
        rtgui_dc_draw_text(dc, "  中文也行!", &rect);

		rtgui_dc_end_drawing(dc);

		return RT_FALSE;
	}
    else if (event->type == RTGUI_EVENT_KBD)
    {
        struct rtgui_dc* dc;
        struct rtgui_rect rect;
        struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
        if (ekbd->type == RTGUI_KEYDOWN)
        {
            char key_str[16];
            switch (ekbd->key)
            {
                case RTGUIK_LEFT:
                rt_sprintf(key_str, "%s", "L");
                break;
                case RTGUIK_RIGHT:
                rt_sprintf(key_str, "%s", "R");
                break;
                case RTGUIK_DOWN:
                rt_sprintf(key_str, "%s", "D");
                break;
                case RTGUIK_UP:
                rt_sprintf(key_str, "%s", "U");
                break;
                default:
                rt_sprintf(key_str, "%s", "S");
                break;
            }
            dc = rtgui_dc_begin_drawing(widget);
            if (dc == RT_NULL)
                return RT_FALSE;
            rect.x1 = 118;
            rect.y1 = 1;
            rect.x2 = 127;
            rect.y2 = 10;
            rtgui_dc_fill_rect(dc, &rect);
            rtgui_dc_draw_text(dc, key_str, &rect);
            rtgui_dc_end_drawing(dc);
        }
        else if (ekbd->type == RTGUI_KEYUP)
        {
            dc = rtgui_dc_begin_drawing(widget);
            if (dc == RT_NULL)
                return RT_FALSE;
            rect.x1 = 118;
            rect.y1 = 1;
            rect.x2 = 127;
            rect.y2 = 10;
            rtgui_dc_fill_rect(dc, &rect);
            //rtgui_dc_draw_text(dc, key_str, &rect);
            rtgui_dc_end_drawing(dc);
        }
    }
    else if (event->type == RTGUI_EVENT_COMMAND)
    {
        char str[16];
        struct rtgui_dc* dc;
        struct rtgui_rect rect;
        struct rtgui_event_command* ecmd;
        rt_uint8_t major,minor;
        dc = rtgui_dc_begin_drawing(widget);
        if (dc == RT_NULL)
            return RT_FALSE;

        ecmd = (struct rtgui_event_command*)event;
        switch (ecmd->command_id)
        {
            default:
                rect.x1 = 1;
                rect.y1 = 1;
                rect.x2 = 117;
                rect.y2 = 10;
                rtgui_dc_fill_rect(dc, &rect);
			    rt_sprintf(str, "ADC = %d mv", 123);
			    rtgui_dc_draw_text(dc, str, &rect);
            break;
 /*           case ADC_UPDATE:
                rect.x1 = 1;
                rect.y1 = 1;
                rect.x2 = 117;
                rect.y2 = 10;
                rtgui_dc_fill_rect(dc, &rect);
			    rt_sprintf(str, "ADC = %d mv", adc_value);
			    rtgui_dc_draw_text(dc, str, &rect);
            break;
            case CPU_UPDATE:
                cpu_usage_get(&major, &minor);
                rect.x1 = 1;
                rect.y1 = 12;
                rect.x2 = 127;
                rect.y2 = 22;
                rtgui_dc_fill_rect(dc, &rect);
			    rt_sprintf(str, "CPU : %d.%d%", major, minor);
			    rtgui_dc_draw_text(dc, str, &rect);

                rect.y1 = 23;
                rect.y2 = 63;
                index++;
                if (index == 127)
                {
                    index = 1;
                    rtgui_dc_fill_rect(dc, &rect);
                }
                if (major>40)
                    rtgui_dc_draw_vline(dc, index, rect.y1, rect.y2);
                else
                    rtgui_dc_draw_vline(dc, index, rect.y2-major, rect.y2);
                break;
*/        }
        rtgui_dc_end_drawing(dc);
    }

	return rtgui_view_event_handler(widget, event);
}

static void wb_info(void* parameter)
{
	rt_mq_t mq;
	rtgui_view_t *view;
	rtgui_workbench_t *workbench;

    /* Create message queue for self */
	mq = rt_mq_create("mq_wb1", 256, 4, RT_IPC_FLAG_FIFO);
	if(mq == RT_NULL)
    {
        rt_kprintf("Create mq failed!\n");
        return;
    }
	rtgui_thread_register(rt_thread_self(), mq);

    /* Create workbench */
	workbench = rtgui_workbench_create("info", "wb_1");
	if(workbench == RT_NULL)
    {
        rt_kprintf("Create wb failed!\n");
        return;
    }
    /* Create a view */
    view = rtgui_view_create("view_1");
	if(view == RT_NULL)
    {
        rt_kprintf("Create view failed!\n");
        return;
    }
	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(view)) = red;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(view)) = white;
//	rtgui_widget_set_event_handler(RTGUI_WIDGET(view), view_event_handler);

	/* Create a lable */
	rtgui_label_t *label = rtgui_label_create("R-Thread & RTGUI");
	if(label == RT_NULL)
    {
        rt_kprintf("Create lable failed!\n");
        return;
    }
	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(label)) = red;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(label)) = white;

    /* Set lable position */
    rtgui_rect_t rect;
	rect.x1 = 10; rect.y1 = 2;
	rect.x2 = 230; rect.y2 = 22;
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

    /* Add view to workbench */
	rtgui_workbench_add_view(workbench, view);

    /* this view can be focused */
//    RTGUI_WIDGET(view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
    /* set widget focus */
//    rtgui_widget_focus(RTGUI_WIDGET(view));

    /* Show view */
	rtgui_view_show(view, RT_FALSE);

    /* Workbench loop */
	rtgui_workbench_event_loop(workbench);

    /* Prepare for exit */
	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}


static void wb_main(void* parameter)
{
	rt_mq_t mq;
	rtgui_view_t *view;
	rtgui_workbench_t *workbench;

    /* Create message queue for self */
	mq = rt_mq_create("mq_wb2", 256, 4, RT_IPC_FLAG_FIFO);
	if(mq == RT_NULL)
    {
        rt_kprintf("Create mq failed!\n");
        return;
    }
	rtgui_thread_register(rt_thread_self(), mq);

    /* Create workbench */
	workbench = rtgui_workbench_create("main", "wb_2");
	if(workbench == RT_NULL)
    {
        rt_kprintf("Create wb failed!\n");
        return;
    }
    /* Create a view */
    view = rtgui_view_create("view_2");
	if(view == RT_NULL)
    {
        rt_kprintf("Create view failed!\n");
        return;
    }
	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(view)) = white;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(view)) = red;
//	rtgui_widget_set_event_handler(RTGUI_WIDGET(view), view_event_handler);

	/* Create a lable */
	rtgui_label_t* label = rtgui_label_create("EFM32GG_DK3750 Kit");
	if(label == RT_NULL)
    {
        rt_kprintf("Create lable failed!\n");
        return;
    }
	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(label)) = white;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(label)) = red;

    /* Set lable position */
    rtgui_rect_t rect;
	rect.x1 = 10; rect.y1 = 50;
	rect.x2 = 230; rect.y2 = 70;
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

    /* Add view to workbench */
	rtgui_workbench_add_view(workbench, view);

    /* this view can be focused */
//    RTGUI_WIDGET(view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
    /* set widget focus */
//    rtgui_widget_focus(RTGUI_WIDGET(view));

    /* Show view */
	rtgui_view_show(view, RT_FALSE);

    /* Workbench loop */
	rtgui_workbench_event_loop(workbench);

    /* Prepare for exit */
	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}

static void win_hello(void* parameter)
{
	rt_mq_t mq;
	struct rtgui_view* view;
	rtgui_win_t *win;

    /* Create message queue for self */
	mq = rt_mq_create("mq_win", 256, 4, RT_IPC_FLAG_FIFO);
	if(mq == RT_NULL)
    {
        rt_kprintf("Create mq failed!\n");
        return;
    }
	rtgui_thread_register(rt_thread_self(), mq);

    /* Window position */
    rtgui_rect_t rect;
	rect.x1 = 50; rect.y1 = 50;
	rect.x2 = 180; rect.y2 = 180;

    /* Create window */
    win = rtgui_win_create(RT_NULL, "Hello", &rect, RTGUI_WIN_STYLE_DEFAULT);
	if(win == RT_NULL)
    {
        rt_kprintf("Create win failed!\n");
        return;
    }

    /* Create a box */
    rtgui_box_t *box = rtgui_box_create(RTGUI_VERTICAL, RT_NULL);
	if(box == RT_NULL)
    {
        rt_kprintf("Create box failed!\n");
        return;
    }
    rtgui_win_set_box(win, box);

    rtgui_label_t *label = rtgui_label_create("哈罗,盹胖!");
	if(label == RT_NULL)
    {
        rt_kprintf("Create lable failed!\n");
        return;
    }
	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(label)) = white;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(label)) = black;
    RTGUI_WIDGET(label)->align = RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL;
    rtgui_widget_set_miniwidth(RTGUI_WIDGET(label),130);
    rtgui_box_append(box, RTGUI_WIDGET(label));

    /* Auto layout */
    rtgui_box_layout(box);

    /* Show window */
    rtgui_win_show(win, RT_FALSE);

    /* Window loop */
	rtgui_win_event_loop(win);

    /* Prepare for exit */
	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}

void rt_demo_thread_entry(void* parameter)
{
#if 0 //defined(EFM32_USING_ACCEL)
{
    struct efm32_accel_result_t result;

    rt_kprintf(">>> waiting\n");
    rt_thread_sleep(6000);
    rt_kprintf(">>> start\n");
    while(1)
    {
        efm_accel_get_data(&result);
        rt_kprintf("Accel x: %x\n", result.x);
        rt_kprintf("Accel y: %x\n", result.y);
        rt_kprintf("Accel z: %x\n\n", result.z);
        rt_thread_sleep(200);
    }
}
#endif

#if defined(RT_USING_DFS)
{
    rt_kprintf("File system DEMO start...\n");
    /* Filesystem Initialization */
    dfs_init();

 #if defined(RT_USING_DFS_ELMFAT)
    /* init the elm chan FatFs filesystam*/
    elm_init();

  #if defined(EFM32_USING_SPISD)
    /* mount sd card fat partition 1 as root directory */
    if (dfs_mount(SPISD_DEVICE_NAME, "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("FatFs init OK\n");
    }
    else
    {
        rt_kprintf("FatFs init failed!\n");
    }
  #endif
 #endif
    rt_kprintf("File system DEMO end.\n");
}
#endif

#ifdef EFM32_USING_SFLASH
{
    rt_kprintf("SPI Flash DEMO start...\n");

    rt_uint8_t i;
    rt_uint8_t test[] = "123456789ABCDEF";
    rt_uint8_t buf[30], buf2[30];

    efm_spiFlash_cmd(sflash_inst_rdid_l, EFM32_NO_DATA, buf, sizeof(buf));
    rt_kprintf("Manuf ID: %x\n", buf[0]);
    rt_kprintf("Memory type: %x\n", buf[1]);
    rt_kprintf("Memory capacity: %x\n", buf[2]);
    rt_kprintf("CFD length: %x\n", buf[3]);
    rt_kprintf("CFD: %x%x%x...%x%x\n", buf[4], buf[5], buf[6], buf[18], buf[19]);

    efm_spiFlash_cmd(sflash_inst_wren, EFM32_NO_DATA, EFM32_NO_POINTER, EFM32_NO_DATA);
    do
    {
        efm_spiFlash_cmd(sflash_inst_rdsr, EFM32_NO_DATA, buf2, sizeof(buf2));
        rt_kprintf("Status: %x\n", buf2[0]);
    } while (buf2[0] == 0xFF);
    rt_kprintf("Status: %x\n", buf2[0]);

    //efm_spiFash_cmd(sflash_inst_pp, 0x000003F8, test, sizeof(test) - 1);

    efm_spiFlash_cmd(sflash_inst_rdsr, EFM32_NO_DATA, buf2, sizeof(buf2));
    rt_kprintf("Status: %x\n", buf2[0]);

    efm_spiFlash_cmd(sflash_inst_read, 0x00000300, buf, sizeof(buf));
    rt_kprintf("READ: \n");
    for (i = 0; i < sizeof(buf); i++)
    {
        rt_kprintf("%c\n", buf[i]);
    }

    //efm_spiFlash_deinit();
    rt_kprintf("SPI Flash DEMO end.\n");
}
#endif

#if defined(EFM32_USING_ETHERNET)
{
    rt_kprintf("Ethernet DEMO start...\n");
    extern void lwip_sys_init(void);
    /* init lwip system */
    lwip_sys_init();
    rt_kprintf("TCP/IP stack init OK!\n");

 #if defined(EFM32_USING_ETH_HTTPD)
    extern void httpd_init(void);
    /* init http server */
    httpd_init();
    rt_kprintf("Http service init OK!\n");
 #endif /* defined(EFM32_USING_ETH_HTTPD) */
    rt_kprintf("Ethernet DEMO end.\n");
}
#endif /* defined(EFM32_USING_ETHERNET) */

#if defined(EFM32_USING_LCD)
{
    rt_kprintf("LCD DEMO start...\n");

    /* find lcd device */
    rt_device_t lcd = rt_device_find(LCD_DEVICE_NAME);
    if (lcd == RT_NULL)
    {
        rt_kprintf("Can't find LCD\n");
    }

    /* read LCD info */
    struct rt_device_graphic_info lcd_info;
    lcd->control(lcd, RTGRAPHIC_CTRL_GET_INFO, (void *)&lcd_info);
    rt_kprintf("LCD size: %dX%d\n", lcd_info.width, lcd_info.height);

    /* register panels */
    rtgui_rect_t rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = lcd_info.width;
    rect.y2 = 25;
    rtgui_panel_register("info", &rect);
    rect.x1 = 0;
    rect.y1 = 25;
    rect.x2 = lcd_info.width;
    rect.y2 = lcd_info.height;
    rtgui_panel_register("main", &rect);
    rtgui_panel_set_default_focused("main");

    /* Create workbenc threads */
    rt_thread_t wb_tid;
    wb_tid = rt_thread_create(
        "wb_main",
        wb_main,
        RT_NULL,
        2048,
        25,
        10);
    if (wb_tid != RT_NULL)
    {
        rt_thread_startup(wb_tid);
    }
    else
    {
        rt_kprintf("Create workbench \"main\" failed!\n");
    }

    wb_tid = rt_thread_create(
        "wb_info",
        wb_info,
        RT_NULL,
        2048,
        25,
        10);
    if (wb_tid != RT_NULL)
    {
        rt_thread_startup(wb_tid);
    }
    else
    {
        rt_kprintf("Create workbench \"info\" failed!\n");
    }

    wb_tid = rt_thread_create(
        "win",
        win_hello,
        RT_NULL,
        2048,
        25,
        10);
    if (wb_tid != RT_NULL)
    {
        rt_thread_startup(wb_tid);
    }
    else
    {
        rt_kprintf("Create window \"win\" failed!\n");
    }

    rt_kprintf("LCD DEMO end.\n");
}
#endif
    rt_kprintf("All Demo end.\n");

    while(1)
    {
        rt_thread_sleep(10);
    }
}

void rt_led_thread_entry(void* parameter)
{
    rt_uint8_t n = 0;

    rt_hw_led_on(0);
    rt_hw_led_on(1);
    rt_hw_led_on(2);
    rt_hw_led_on(3);

    while(1)
    {
        /* Toggle a led per second */
        rt_hw_led_toggle(n++);
        if (n == LEDS_MAX_NUMBER)
        {
            n =0;
        }
        rt_thread_delay(100);
    }
}

int rt_application_init()
{
    rt_thread_t demo_thread, led_thread;

#if defined(EFM32_USING_ACCEL)
    if (efm_accel_init() != RT_EOK)
    {
        rt_kprintf("*** Init accelerometer driver failed!");
        while(1); //Or do something?
    }
#endif

#if defined(EFM32_USING_SFLASH)
    if (efm_spiFlash_init() != RT_EOK)
    {
        rt_kprintf("*** Init SPI Flash driver failed!");
        while(1); //Or do something?
    }
#endif

#if defined(EFM32_USING_SPISD)
    if (efm_spiSd_init() != RT_EOK)
    {
        rt_kprintf("*** Init SD card driver failed!");
        while(1); //Or do something?
    }
#endif

    /* Initialize all device drivers (dev_?.c) */
    if (rt_hw_led_init() != RT_EOK)
    {
        rt_kprintf("*** Init LED driver failed!");
        while(1); //Or do something?
    }
#if defined(RT_USING_MISC)
    if (rt_hw_misc_init() != RT_EOK)
    {
        rt_kprintf("*** Init miscellaneous driver failed!");
        while(1); //Or do something?
    }
#endif

#if defined(RT_USING_LWIP)
    {
        /* Create Ethernet Threads */
        if (eth_system_device_init() != RT_EOK)
        {
            rt_kprintf("*** Create Ethernet threads failed!");
            while(1); //Or do something?
        }
 #if defined(EFM32_USING_ETHERNET)
        if (efm_hw_eth_init() != RT_EOK)
        {
            rt_kprintf("*** Init Ethernet driver failed!");
            while(1); //Or do something?
        }
 #endif
    }
#endif

#if (RT_THREAD_PRIORITY_MAX == 32)
    demo_thread = rt_thread_create(
        "demo",
        rt_demo_thread_entry,
        RT_NULL,
        1024,
        5,
        20);

    led_thread = rt_thread_create(
        "led",
        rt_led_thread_entry,
        RT_NULL,
        256,
        5,
        20);
#else
#endif

    if(demo_thread != RT_NULL)
    {
        rt_kprintf("demo sp:%x\n", demo_thread->sp);
        rt_thread_startup(demo_thread);
    }

    if(led_thread != RT_NULL)
    {
        rt_thread_startup(led_thread);
    }

    return 0;
}

/***************************************************************************//**
 * @}
 ******************************************************************************/
