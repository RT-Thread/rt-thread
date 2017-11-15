/*
 * File      : touch.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2017/11/13     EvalZero	first version
 */
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "nuc97x_conf.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "nuc97x.h"
#include "nuc97x_sys.h"
#include "nuc97x_adc.h"


#include "touch.h"

#include <rtgui/event.h>
#include <rtgui/kbddef.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>

 
#define TOUCH_SAMPLE_HZ   20

struct rtgui_touch_device
{
    struct rt_device parent;

    rt_timer_t poll_timer;
    rt_uint16_t x, y;

    rt_bool_t calibrating;
    // rt_touch_calibration_func_t calibration_func;

    rt_uint16_t min_x, max_x;
    rt_uint16_t min_y, max_y;
    rt_bool_t first_down_report;  
};
static struct rtgui_touch_device *touch = RT_NULL;

#if 0
static void rtgui_touch_calculate(void)
{
    if(touch != NULL)
    {
        rt_uint16_t tmpx[10];
        rt_uint16_t tmpy[10];
        rt_uint8_t i;
        
        for(i = 0; i < 10; i++)
        {
            /* Start Conversion*/
            adcIoctl(START_MST,0,0);
            if(adcReadXY(&tmpx[i],&tmpy[i],1) == 0)
            {
                rt_kprintf("read touch adc error! \rn");
            }
        }
        
        /* 去掉最高值和最低值，然后求平均值 */
        {
            rt_uint32_t min_x = 0xFFFF,min_y = 0xFFFF;
            rt_uint32_t max_x = 0,max_y = 0;
            rt_uint32_t total_x = 0;
            rt_uint32_t total_y = 0;
            rt_uint8_t i;

            for(i=0;i<10;i++)
            {
                if( tmpx[i] < min_x )
                {
                    min_x = tmpx[i];
                }
                if( tmpx[i] > max_x )
                {
                    max_x = tmpx[i];
                }
                total_x += tmpx[i];

                if( tmpy[i] < min_y )
                {
                    min_y = tmpy[i];
                }
                if( tmpy[i] > max_y )
                {
                    max_y = tmpy[i];
                }
                    total_y += tmpy[i];
            }
            total_x = total_x - min_x - max_x;
            total_y = total_y - min_y - max_y;
            touch->x = total_x / 8.0f;
            touch->y = total_y / 8.0f;
        }                
    }
}
#endif

static void read_xy_adc(short *x, short *y)
{
    rt_uint32_t value;
    
    value = inpw(REG_ADC_XYDATA);
    *x = value & 0xFFF;
    *y = (value >>16) & 0xFFF;

}

static void read_z_adc(short *z1, short *z2)
{
    rt_uint32_t value;
    
    value = inpw(REG_ADC_ZDATA);
    *z1 = value & 0xFFF;
    *z2 = (value >>16) & 0xFFF;

}

static rt_bool_t is_release(void)
{
    short z1, z2;
    
    read_z_adc(&z1, &z2);
    if(z2 - z1 < 4000) 
    {
         return RT_FALSE;
    }
    
    return RT_TRUE;
}

static void post_up_event(rt_uint16_t x, rt_uint16_t y, rt_tick_t ts)
{
    struct rtgui_event_mouse emouse;

    touch->x = x * 800 / 4096.0f;
    touch->y = y * 480 / 4096.0f;
    
    emouse.parent.sender = RT_NULL;
    emouse.wid = RT_NULL;
    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_UP;
    emouse.x = touch->x;
    emouse.y = touch->y;
    emouse.ts = rt_tick_get();
    emouse.id = ts;

    rtgui_server_post_event(&emouse.parent, sizeof(emouse)); 
    rt_kprintf("up event:x=%3d, y=%3d \r\n", emouse.x, emouse.y);
}

static void post_motion_event(rt_uint16_t x, rt_uint16_t y, rt_tick_t ts)
{
    struct rtgui_event_mouse emouse;

    touch->x = x * 800 / 4096.0f;
    touch->y = y * 480 / 4096.0f;
    
    emouse.parent.sender = RT_NULL;
    emouse.wid = RT_NULL;
    
    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN;
    emouse.x = touch->x;
    emouse.y = touch->y;
    emouse.ts = rt_tick_get();
    emouse.id = ts;

    rtgui_server_post_event(&emouse.parent, sizeof(emouse)); 
    rt_kprintf("motion event:x=%3d, y=%3d \r\n", emouse.x, emouse.y);    
}

static void post_down_event(rt_uint16_t x, rt_uint16_t y, rt_tick_t ts)
{
    struct rtgui_event_mouse emouse;

    touch->x = x * 800 / 4096.0f;
    touch->y = y * 480 / 4096.0f;
    
    emouse.parent.type = RTGUI_EVENT_MOUSE_MOTION;
    emouse.x = touch->x;
    emouse.y = touch->y;
    emouse.ts = rt_tick_get();
    emouse.id = ts;

    rtgui_server_post_event(&emouse.parent, sizeof(emouse)); 
    rt_kprintf("down event:x=%3d, y=%3d \r\n", emouse.x, emouse.y);    
}


void touch_timer_fire(void *parameter)
{
    static uint8_t  first_touch = 0;
    static rt_tick_t emouse_id = 0;
    short x = 0,y = 0;
    static struct _pos_previous
    {
        short x;
        short y;
    } pos_previous;
    
    adcIoctl(START_MST,0,0);

    /* 判断是否松手 */
    if((is_release() == RT_TRUE))
    {
        if(first_touch == 1)
        {
            // read_xy_adc(&x, &y);
            post_up_event(pos_previous.x, pos_previous.y, emouse_id);
            first_touch = 0;
        }
    }
    else
    {
        /* first touch */
        if(first_touch == 0)
        {
            emouse_id = rt_tick_get();
            read_xy_adc(&x, &y);
            post_down_event(x, y, emouse_id);
            first_touch = 1;
        }
        else
        {
            /* moving */
            read_xy_adc(&x, &y);
            post_motion_event(x, y, emouse_id);
            pos_previous.x = x;
            pos_previous.y = y;
        }
    }
}

static rt_err_t rtgui_touch_control (rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RT_TOUCH_CALIBRATION:
        touch->calibrating = RT_TRUE;
        // touch->calibration_func = (rt_touch_calibration_func_t)args;
        break;

    case RT_TOUCH_NORMAL:
        touch->calibrating = RT_FALSE;
        break;

    case RT_TOUCH_CALIBRATION_DATA:

    break;
    }

    return RT_EOK;
}

/* RT-Thread Device Interface */
static rt_err_t rtgui_touch_init (rt_device_t dev)
{   
    adcOpen();
    adcIoctl(T_ON,(UINT32)0, 0);
    adcIoctl(Z_ON, 0, 0);

    return RT_EOK;
}
int rtgui_touch_hw_init(void)
{   
    touch = (struct rtgui_touch_device*)rt_malloc (sizeof(struct rtgui_touch_device));
    if (touch == RT_NULL) return RT_ERROR; /* no memory yet */
    
    rtgui_touch_init(&(touch->parent));
    
    /* clear device structure */
    rt_memset(&(touch->parent), 0, sizeof(struct rt_device));
    touch->calibrating = false;

    /* init device structure */
    touch->parent.type = RT_Device_Class_Unknown;
    touch->parent.init = rtgui_touch_init;
    touch->parent.control = rtgui_touch_control;
    touch->parent.user_data = RT_NULL;

    /* create timer */
    touch->poll_timer = rt_timer_create("touch", touch_timer_fire, RT_NULL,
                                        RT_TICK_PER_SECOND/TOUCH_SAMPLE_HZ, RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);

    /* start timer */
    rt_timer_start(touch->poll_timer);
    /* register touch device to RT-Thread */
    rt_device_register(&(touch->parent), "touch", RT_DEVICE_FLAG_RDWR);
    
    return 0;
}

// INIT_ENV_EXPORT(rtgui_touch_hw_init);
