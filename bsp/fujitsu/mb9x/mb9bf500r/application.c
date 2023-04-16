/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-24     Bernard      the first version
 */

/**
 * @addtogroup FM3
 */

/*@{*/

#include <rtthread.h>
#include "board.h"
#include "led.h"
#include "key.h"
#include "adc.h"
#include "lcd.h"
#include "cpuusage.h"

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#include <rtgui/driver.h>
extern void rtgui_startup();
#endif

struct rt_messagequeue mq;
static char msg_pool[2048];

void rt_init_thread_entry(void *parameter)
{
    rt_device_t lcd;

    rt_hw_led_init();
    rt_hw_key_init();
    rt_hw_adc_init();
    rt_hw_lcd_init();
    rt_hw_cpu_init();

#ifdef RT_USING_RTGUI
    extern void rtgui_system_server_init(void);

    /* find lcd device */
    lcd = rt_device_find("lcd");

    /* set lcd device as rtgui graphic driver */
    rtgui_graphic_set_device(lcd);

    /* init rtgui system server */
    rtgui_system_server_init();

    /* startup rtgui */
    rtgui_startup();
#else
    {
    char buf[20] = {'\0'};
    struct lcd_msg msg;
    rt_device_t device;
    device = rt_device_find("lcd");
    rt_device_control(device, RT_DEVICE_CTRL_LCD_CLEAR_SCR, RT_NULL);
    x = 1;
    y = 1;
    rt_device_control(device, RT_DEVICE_CTRL_LCD_PUT_STRING, "ADC");
    x = 1;
    y = 20;
    rt_device_control(device, RT_DEVICE_CTRL_LCD_PUT_STRING, "CPU");
    x = 1;
    y = 40;
    rt_device_control(device, RT_DEVICE_CTRL_LCD_PUT_STRING, "KEY");

    while(1)
    {
        if (rt_mq_recv(&mq, &msg, sizeof(msg), RT_WAITING_FOREVER) >= 0)
        {
            switch(msg.type)
            {
                case ADC_MSG:
                    x = 40;
                    y = 1;
                    rt_memset(buf, 0, sizeof(buf));
                    rt_sprintf(buf, "%04d", msg.adc_value);
                    rt_device_control(device, RT_DEVICE_CTRL_LCD_PUT_STRING, buf);
                    break;
                case CPU_MSG:
                    x = 40;
                    y = 20;
                    rt_memset(buf, 0, sizeof(buf));
                    rt_sprintf(buf, "%03d %03d", msg.major, msg.minor);
                    rt_device_control(device, RT_DEVICE_CTRL_LCD_PUT_STRING, buf);
                    break;
                case KEY_MSG:
                    x = 40;
                    y = 40;
                    rt_memset(buf, 0, sizeof(buf));
                    switch(msg.key)
                    {
                        case KEY_DOWN:
                            rt_sprintf(buf, "DOWN KEY ");
                            break;
                        case KEY_UP:
                            rt_sprintf(buf, "UP KEY   ");
                            break;
                        case KEY_RIGHT:
                            rt_sprintf(buf, "RIGHT KEY");
                            break;
                        case KEY_LEFT:
                            rt_sprintf(buf, "LEFT KEY ");
                            break;
                        case KEY_ENTER:
                            rt_sprintf(buf, "ENTER KEY");
                            break;
                        default:
                            rt_sprintf(buf, "NO KEY   ");
                            break;
                    }
                    rt_device_control(device, RT_DEVICE_CTRL_LCD_PUT_STRING, buf);
                    break;
            }
        }
    }
    }
#endif
}

int rt_application_init(void)
{
    rt_thread_t init_thread;

    rt_mq_init(&mq, "mqt", &msg_pool[0], 128 - sizeof(void*), sizeof(msg_pool), RT_IPC_FLAG_FIFO);

    init_thread = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 1024, 21, 20);
    if(init_thread != RT_NULL)
        rt_thread_startup(init_thread);

    return 0;
}

/*@}*/
