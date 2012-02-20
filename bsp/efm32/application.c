/***************************************************************************//**
 * @file    application.c
 * @brief   Demo application
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
 * 2012-02-16   onelife     Add photo frame DEMO
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
#include <rtgui/image.h>

 #if defined(RTGUI_USING_DFS_FILERW)
 #include <dfs_posix.h>
 #define PATH_SEPARATOR     '/'
 #endif

#define APP_PHOTO_FRAME
#endif


/* Private typedef -----------------------------------------------------------*/
struct photo_event
{
	struct rtgui_event parent;
    rt_uint32_t cmd;
	rt_uint8_t* path;
	rt_uint8_t* format;
};

/* Private define ------------------------------------------------------------*/
#define APP_CMD_PHOTO_FRAME 0x00000001
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile rt_uint32_t    rt_system_status = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
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
	rtgui_label_t *label = rtgui_label_create("RT-Thread & RTGUI");
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

static rt_bool_t pic_view_event_handler(rtgui_widget_t* widget, rtgui_event_t *event)
{
	rt_bool_t result;
    rt_bool_t load = RT_FALSE;

	result = rtgui_view_event_handler(widget, event);

    switch(event->type)
    {
    case RTGUI_EVENT_PAINT:
        load = RT_TRUE;
        break;

    case RTGUI_EVENT_MOUSE_BUTTON:
        {
			struct rtgui_event_mouse *mouse = (struct rtgui_event_mouse *)event;

			if (mouse->button == RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_UP)
			{
                rt_kprintf("APP: left click (%x)\n", mouse->button);
			}
        }
        break;
    }

    if (load)
	{
		struct rtgui_dc* dc;
		rtgui_rect_t rect;
        rtgui_image_t* image;

    //    image = rtgui_image_create_from_file("jpg", "/test9.jpg", RT_FALSE);
        image = rtgui_image_create_from_file("bmp", "/test_565.bmp", RT_FALSE);

		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL)
        {
            return result;
        }

        rtgui_widget_get_rect(widget, &rect);
        rtgui_widget_rect_to_device(widget, &rect);
        rect.y1 +=20; rect.y2 +=20;

		if (image != RT_NULL)
        {
			rtgui_image_blit(image, dc, &rect);
            rtgui_image_destroy(image);
        }
        else
        {
            rt_kprintf("APP err: no image found!\n");
        }

		rtgui_dc_end_drawing(dc);
	}

	return result;
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
    view = rtgui_view_create("pic_view");
	if(view == RT_NULL)
    {
        rt_kprintf("Create view failed!\n");
        return;
    }
	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(view)) = white;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(view)) = red;
    rtgui_widget_set_event_handler(RTGUI_WIDGET(view), pic_view_event_handler);

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

    rtgui_label_t *label = rtgui_label_create("¹þÂÞ,íïÅÖ!");
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

static rt_bool_t photo_view_event_handler(rtgui_widget_t* widget, rtgui_event_t *event)
{
	rt_bool_t result = RT_FALSE;
    struct photo_event *photo_event = (struct photo_event *)event;

	result = rtgui_view_event_handler(widget, event);
    rt_kprintf("view event %x\n", event->type);

    if ((event->type == RTGUI_EVENT_COMMAND) && \
        (photo_event->cmd == APP_CMD_PHOTO_FRAME))
	{
        rtgui_rect_t rect;
        rtgui_image_t* image;
        struct rtgui_dc* dc;

        rtgui_widget_get_rect(widget, &rect);
        rtgui_widget_rect_to_device(widget, &rect);
        rect.y1 +=20; rect.y2 +=20;

        dc = rtgui_dc_begin_drawing(widget);
        if (dc == RT_NULL)
        {
            return result;
        }

        image = rtgui_image_create_from_file(photo_event->format,
            photo_event->path, RT_TRUE);
        if (image != RT_NULL)
        {
            rtgui_image_blit(image, dc, &rect);
            rtgui_image_destroy(image);
            return result;
        }

        return RT_TRUE;
    }

	return result;
}

static rt_bool_t photo_lable_event_handler(rtgui_widget_t* widget, rtgui_event_t *event)
{
	rt_bool_t result = RT_FALSE;

    rt_kprintf("lable event %x\n", event->type);

    if (event->type == RTGUI_EVENT_COMMAND)
	{
        struct photo_event *photo = (struct photo_event *)event;

        rtgui_label_set_text((rtgui_label_t *)widget, photo->path);
    }

	return result;
}

static void wb_photo(void* parameter)
{
	rt_mq_t mq;
	rtgui_view_t *view;
	rtgui_workbench_t *workbench;

    /* Create message queue for self */
	mq = rt_mq_create("photo", 256, 4, RT_IPC_FLAG_FIFO);
	if(mq == RT_NULL)
    {
        rt_kprintf("Create mq failed!\n");
        return;
    }
	rtgui_thread_register(rt_thread_self(), mq);

    /* Create workbench */
	workbench = rtgui_workbench_create("main", "photo");
	if(workbench == RT_NULL)
    {
        rt_kprintf("Create wb failed!\n");
        return;
    }
    /* Create a view */
    view = rtgui_view_create("view");
	if(view == RT_NULL)
    {
        rt_kprintf("Create view failed!\n");
        return;
    }
	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(view)) = white;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(view)) = blue;
    rtgui_widget_set_event_handler(RTGUI_WIDGET(view), photo_view_event_handler);
//    rtgui_widget_set_oncommand(RTGUI_WIDGET(view), photo_view_event_handler);

	/* Create a lable */
	rtgui_label_t* label = rtgui_label_create("Photo Frame Demo");
	if(label == RT_NULL)
    {
        rt_kprintf("Create lable failed!\n");
        return;
    }
	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(label)) = white;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(label)) = blue;

    /* Set lable position */
    rtgui_rect_t rect;
	rect.x1 = 0; rect.y1 = 2;
	rect.x2 = 300; rect.y2 = 20;
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_widget_set_event_handler(RTGUI_WIDGET(label), photo_lable_event_handler);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

    /* Add view to workbench */
	rtgui_workbench_add_view(workbench, view);

    /* Show view */
	rtgui_view_show(view, RT_FALSE);

    /* Workbench loop */
	rtgui_workbench_event_loop(workbench);

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

#if (defined(EFM32_USING_LCD) && !defined(APP_PHOTO_FRAME))
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

#if defined(APP_PHOTO_FRAME)
{
    rt_kprintf("Photo frame DEMO start...\n");

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
    rect.y2 = lcd_info.height;
    rtgui_panel_register("main", &rect);
    rtgui_panel_set_default_focused("main");

    /* Creat thread */
    rt_thread_t photo = rt_thread_create(
        "photo",
        wb_photo,
        RT_NULL,
        2048,
        25,
        10);
    if (photo != RT_NULL)
    {
        rt_thread_startup(photo);
    }
    else
    {
        rt_kprintf("Create workbench \"photo\" failed!\n");
    }

    /* start display photos */
    DIR* dir = opendir("/photo");
    struct photo_event event;
    struct dirent* dirent;
    rt_uint8_t path[100];
    const rt_uint8_t bmp[] = "bmp";
    const rt_uint8_t jpeg[] = "jpeg";

    event.parent.type = RTGUI_EVENT_COMMAND;
    event.parent.user = sizeof(struct photo_event);
    event.parent.sender = RT_NULL;
    event.parent.ack = RT_NULL;
    event.cmd = APP_CMD_PHOTO_FRAME;
    event.path = path;

    rt_thread_sleep(100);
    do
    {
        /* get a photo */
        dirent = readdir(dir);
        if (dirent == RT_NULL)
        {
            break;
        }
        if ((strcmp(dirent->d_name, ".") == 0) || \
            (strcmp(dirent->d_name, "..") == 0))
        {
            continue;
        }
        rt_sprintf(path, "%s%c%s", "/photo", PATH_SEPARATOR, dirent->d_name);

        /* display it */
        if ((rt_strstr(path, ".bmp") != RT_NULL) || \
            (rt_strstr(path, ".BMP") != RT_NULL))
        {
            event.format = &bmp[0];
            rt_kprintf("bmp: %s\n", path);
        }
        else if ((rt_strstr(path, ".jpg") != RT_NULL) || \
            (rt_strstr(path, ".JPG") != RT_NULL))
        {
            event.format = &jpeg[0];
            rt_kprintf("jpeg: %s\n", path);
        }
        else
        {
            rt_kprintf("skip: %s\n", path);
            continue;
        }

        rtgui_server_post_event((&event.parent), sizeof(event));
        rt_thread_sleep(1000);
    } while (dirent != RT_NULL);
    closedir(dir);

    rt_kprintf("Photo frame end.\n");
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
