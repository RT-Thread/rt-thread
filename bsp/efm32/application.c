/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05   Bernard     first version
 * 2010-12-29   onelife     Modify for EFM32
 * 2011-05-06   onelife     Add SPI Flash DEMO
 * 2011-07-15   onelife     Add accelerometer DEMO
 * 2011-07-27   onelife     Modify Ethernet DEMO
 * 2011-08-23   onelife     Modify Ethernet DEMO according to the changes of
 *                          lwIP API in reversion 1668
 * 2011-12-20   onelife     Add LCD DEMO
 * 2012-02-16   onelife     Add photo frame DEMO
 * 2012-xx-xx   onelife     Add low energy test code
 * 2012-05-17   onelife     Modify photo frame DEMO according to new version of RTGUI
 */

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <board.h>

#if defined(RT_USING_DFS)
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
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/box.h>
#include <rtgui/image.h>

 #if defined(RTGUI_USING_DFS_FILERW)
 #include <dfs_posix.h>
 #define PATH_SEPARATOR     '/'
 #endif
#if defined(RTGUI_USING_DFS_FILERW)
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#define PATH_SEPARATOR     '/'
#endif
#endif

/* Private typedef -----------------------------------------------------------*/
#if defined(RT_USING_RTGUI)
struct photo_event
{
    struct rtgui_event_win win;
    rt_uint32_t cmd;
    rt_uint8_t* path;
    rt_uint8_t* format;
};

/* Private defines -----------------------------------------------------------*/
#define APP_CMD_PHOTO_FRAME 0x00000001
#define APP_PHOTO_FRAME
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile rt_uint32_t    rt_system_status = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if defined(RT_USING_RTGUI)
static rt_bool_t pic_view_event_handler(rtgui_object_t *object, rtgui_event_t *event)
{
    rt_bool_t result;
    rt_bool_t load = RT_FALSE;

    result = rtgui_container_event_handler(object, event);

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

        image = rtgui_image_create_from_file("jpg", "/test9.jpg", RT_FALSE);
//        image = rtgui_image_create_from_file("bmp", "/test_565.bmp", RT_FALSE);

        dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(object));
        if (dc == RT_NULL)
        {
            return result;
        }

        rtgui_widget_get_rect(RTGUI_WIDGET(object), &rect);
 //       rtgui_widget_rect_to_device(widget, &rect);
        rect.x1 +=10;
        rect.y1 +=10;

        if (image != RT_NULL)
        {
            rtgui_image_blit(image, dc, &rect);
            rtgui_image_destroy(image);
        }
        else
        {
            rt_kprintf("APP err: no image found!\n");
        }

        rtgui_dc_end_drawing(dc, RT_TRUE);
    }

    return result;
}

static void app_main(void *parameter)
{
    /* find lcd device */
    rt_device_t lcd = rt_device_find(LCD_DEVICE_NAME);
    if (lcd == RT_NULL)
    {
        rt_kprintf("Can't find LCD\n");
        return;
    }

    /* read LCD info */
    struct rt_device_graphic_info lcd_info;
    lcd->control(lcd, RTGRAPHIC_CTRL_GET_INFO, (void *)&lcd_info);
    rt_kprintf("LCD size: %dX%d\n", lcd_info.width, lcd_info.height);

    /* create application */
    struct rtgui_app *app;
    app = rtgui_app_create("gui_app");
    if (app == RT_NULL)
    {
        rt_kprintf("Create application \"gui_app\" failed!\n");
        return;
    }

    struct rtgui_rect rect1, rect2, rect3;
    struct rtgui_win *win_info, *win_main, *win_hello;
    struct rtgui_container *container;
    struct rtgui_label* label;

    rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), &rect1);
    rect2.x1 = rect1.x1;
    rect2.y1 = 25;
    rect2.x2 = rect1.x2;
    rect2.y2 = rect1.y2;
    rect1.y2 = 25;

    /* create info window */
    win_info = rtgui_win_create(RT_NULL, "info",
                    &rect1,
                    RTGUI_WIN_STYLE_NO_BORDER | RTGUI_WIN_STYLE_NO_TITLE);
    if (win_info == RT_NULL)
    {
        rt_kprintf("Create window \"info\" failed!\n");
        rtgui_app_destroy(app);
        return;
    }

    /* create container in info window */
    container = rtgui_container_create();
    if (container == RT_NULL)
    {
        rt_kprintf("Create container failed!\n");
        return;
    }
    rtgui_widget_set_rect(RTGUI_WIDGET(container), &rect1);
    rtgui_container_add_child(RTGUI_CONTAINER(win_info), RTGUI_WIDGET(container));

    /* create lable in info window */
    label = rtgui_label_create("RT-Thread & RTGUI");
    if (label == RT_NULL)
    {
        rt_kprintf("Create lable failed!\n");
        return;
    }

    RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(label)) = RTGUI_ALIGN_LEFT;
    RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(label)) = red;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(label)) = white;

    rect3.x1 = rect1.x1 + 5;
    rect3.y1 = rect1.y1 + 5;
    rect3.x2 = rect1.x2 - 5;
    rect3.y2 = rect1.y2 - 5;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect3);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));


    /* create main window */
    win_main = rtgui_win_create(RT_NULL, "main",
                    &rect2,
                    RTGUI_WIN_STYLE_NO_BORDER | RTGUI_WIN_STYLE_NO_TITLE);
    if (win_main == RT_NULL)
    {
        rt_kprintf("Create window \"main\" failed!\n");
        rtgui_app_destroy(app);
        return;
    }

    /* create container in main window */
    container = rtgui_container_create();
    if (container == RT_NULL)
    {
        rt_kprintf("Create container failed!\n");
        return;
    }

    rtgui_widget_set_rect(RTGUI_WIDGET(container), &rect2);
    rtgui_object_set_event_handler(RTGUI_OBJECT(container), pic_view_event_handler);
    rtgui_container_add_child(RTGUI_CONTAINER(win_main), RTGUI_WIDGET(container));

    /* create lable in main window */
    label = rtgui_label_create("EFM32GG_DK3750 Kit");
    if (label == RT_NULL)
    {
        rt_kprintf("Create lable failed!\n");
        return;
    }
    RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(label)) = RTGUI_ALIGN_LEFT;
    RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(label)) = white;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(label)) = blue;

    rect3.x1 = rect2.x1 + 5;
    rect3.y1 = rect2.y1 + 5;
    rect3.x2 = rect2.x2 - 5;
    rect3.y2 = rect2.y1 + 20;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect3);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));


    /* create hello window */
    rect3.x1 = 80;
    rect3.y1 = 50;
    rect3.x2 = 320 - 80;
    rect3.y2 = 240 - 50;
    win_hello = rtgui_win_create(RT_NULL, "hello",
                    &rect3,
                    RTGUI_WIN_STYLE_DEFAULT);
    if (win_hello == RT_NULL)
    {
        rt_kprintf("Create window \"hello\" failed!\n");
        rtgui_app_destroy(app);
        return;
    }

    /* create a box */
    rtgui_box_t *box = rtgui_box_create(RTGUI_VERTICAL, RT_NULL);
    if(box == RT_NULL)
    {
        rt_kprintf("Create box failed!\n");
        return;
    }
//    rtgui_win_set_box(win_hello, box);

    label = rtgui_label_create("哈罗,盹胖!");
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


    rtgui_win_show(win_info, RT_FALSE);
    rtgui_win_show(win_main, RT_FALSE);
    rtgui_win_show(win_hello, RT_FALSE);

    rtgui_app_run(app);
    rtgui_app_destroy(app);
}

static rt_bool_t photo_view_event_handler(rtgui_object_t *object, rtgui_event_t *event)
{
    rt_bool_t result = RT_FALSE;
    struct photo_event *photo_event = (struct photo_event *)event;

    result = rtgui_container_event_handler(object, event);
    rt_kprintf("container event %x\n", event->type);

    struct rtgui_event_win* wevent = (struct rtgui_event_win*)event;
    rt_kprintf("wevent->wid %x\n", wevent->wid);

    if ((event->type == RTGUI_EVENT_COMMAND) && \
        (photo_event->cmd == APP_CMD_PHOTO_FRAME))
    {
        rtgui_rect_t rect;
        rtgui_image_t* image;
        struct rtgui_dc* dc;

        rtgui_widget_get_rect(RTGUI_WIDGET(object), &rect);
        rt_kprintf(" (%d, %d) (%d, %d)\n", rect.x1, rect.y1, rect.x2, rect.y2);
//        rtgui_widget_rect_to_device(RTGUI_WIDGET(object), &rect);
        rect.y1 +=15;

        dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(object));
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

static rt_bool_t photo_lable_event_handler(rtgui_object_t *object, rtgui_event_t *event)
{
    rt_bool_t result = RT_FALSE;

    result = rtgui_label_event_handler(object, event);
    rt_kprintf("lable event %x\n", event->type);

    if (event->type == RTGUI_EVENT_COMMAND)
    {
        struct photo_event *photo = (struct photo_event *)event;

        rtgui_label_set_text((rtgui_label_t *)object, photo->path);
        rt_kprintf("path %s\n", photo->path);
    }

    return result;
}

static void app_photo(void *parameter)
{
    struct photo_event *event = (struct photo_event *)parameter;

    /* find lcd device */
    rt_device_t lcd = rt_device_find(LCD_DEVICE_NAME);
    if (lcd == RT_NULL)
    {
        rt_kprintf("Can't find LCD\n");
        return;
    }

    /* read LCD info */
    struct rt_device_graphic_info lcd_info;
    lcd->control(lcd, RTGRAPHIC_CTRL_GET_INFO, (void *)&lcd_info);
    rt_kprintf("LCD size: %dX%d\n", lcd_info.width, lcd_info.height);

    /* create application */
    struct rtgui_app *app;
    app = rtgui_app_create("pho_app");
    if (app == RT_NULL)
    {
        rt_kprintf("Create application \"pho_app\" failed!\n");
        return;
    }

    struct rtgui_rect rect1, rect2;
    struct rtgui_win *window;
    struct rtgui_container *container;
    struct rtgui_label* label;

    rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), &rect1);

    /* create window */
    window = rtgui_win_create(RT_NULL, "photo",
                    &rect1,
                    RTGUI_WIN_STYLE_NO_BORDER | RTGUI_WIN_STYLE_NO_TITLE);
    if (window == RT_NULL)
    {
        rt_kprintf("Create window \"photo\" failed!\n");
        rtgui_app_destroy(app);
        return;
    }
    event->win.wid = window;

    /* create container */
    container = rtgui_container_create();
    if (container == RT_NULL)
    {
        rt_kprintf("Create container failed!\n");
        return;
    }
    rtgui_widget_set_rect(RTGUI_WIDGET(container), &rect1);
    rtgui_object_set_event_handler(RTGUI_OBJECT(container), photo_view_event_handler);
    rtgui_container_add_child(RTGUI_CONTAINER(window), RTGUI_WIDGET(container));

    /* create lable in info window */
    label = rtgui_label_create("Photo Frame Demo");
    if (label == RT_NULL)
    {
        rt_kprintf("Create lable failed!\n");
        return;
    }

    RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(label)) = RTGUI_ALIGN_LEFT;
    RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(label)) = white;
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(label)) = blue;

    rect2.x1 = rect1.x1;
    rect2.y1 = rect1.y1;
    rect2.x2 = rect1.x2;
    rect2.y2 = 15;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect2);
    rtgui_object_set_event_handler(RTGUI_OBJECT(label), photo_lable_event_handler);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));

    rtgui_win_show(window, RT_FALSE);

    rtgui_app_run(app);
    rtgui_app_destroy(app);
}
#endif

void rt_demo_thread_entry(void* parameter)
{
    emu_all_disable();

#if 0 //defined(EFM32_USING_ACCEL)
{
    struct efm32_accel_result_t result;

    rt_kprintf(">>> waiting\n");
    rt_thread_delay(6000);
    rt_kprintf(">>> start\n");
    while(1)
    {
        efm_accel_get_data(&result);
        rt_kprintf("Accel x: %x\n", result.x);
        rt_kprintf("Accel y: %x\n", result.y);
        rt_kprintf("Accel z: %x\n\n", result.z);
        rt_thread_delay(200);
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

    /* Create RTGUI application thread */
    rt_thread_t gui_app;
    gui_app = rt_thread_create(
        "gui_thd",
        app_main,
        RT_NULL,
        2048,
        25,
        10);
    if (gui_app != RT_NULL)
    {
        rt_thread_startup(gui_app);
    }
    else
    {
        rt_kprintf("Create gui_app thread failed!\n");
    }

    rt_kprintf("LCD DEMO end.\n");
}
#endif

#if defined(APP_PHOTO_FRAME)
{
    rt_kprintf("Photo frame DEMO start...\n");

    DIR* dir = opendir("/photo");
    struct photo_event event;
    struct dirent* dirent;
    rt_uint8_t path[100];
    const rt_uint8_t bmp[] = "bmp";
    const rt_uint8_t jpeg[] = "jpeg";

    RTGUI_EVENT_COMMAND_INIT(&event.win);
    event.cmd = APP_CMD_PHOTO_FRAME;
    event.path = path;

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

    /* Create photo frame thread */
    rt_thread_t photo_app;
    photo_app = rt_thread_create(
        "pho_thd",
        app_photo,
        (void *)&event,
        2048,
        25,
        10);
    if (photo_app != RT_NULL)
    {
        rt_thread_startup(photo_app);
    }
    else
    {
        rt_kprintf("Create photo frame thread failed!\n");
    }

    /* start display photos */
    rt_thread_delay(100);
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

        rtgui_send(photo_app, &event.win.parent, sizeof(event));
        rt_thread_delay(2000);
    } while (dirent != RT_NULL);
    closedir(dir);

    rt_kprintf("Photo frame end.\n");
}

#endif

    rt_kprintf("All Demo end.\n");

    emu_em2_enable();
    while(1)
    {
        rt_thread_delay(10);
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
