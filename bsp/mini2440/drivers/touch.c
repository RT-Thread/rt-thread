/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-01     Yi.Qiu      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <s3c24x0.h>

#ifdef PKG_USING_GUIENGINE
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/event.h>
#endif

#define TOUCH_SWAP_XY

#include "touch.h"

/* ADCCON Register Bits */
#define S3C2410_ADCCON_ECFLG            (1<<15)
#define S3C2410_ADCCON_PRSCEN           (1<<14)
#define S3C2410_ADCCON_PRSCVL(x)        (((x)&0xFF)<<6)
#define S3C2410_ADCCON_PRSCVLMASK       (0xFF<<6)
#define S3C2410_ADCCON_SELMUX(x)        (((x)&0x7)<<3)
#define S3C2410_ADCCON_MUXMASK          (0x7<<3)
#define S3C2410_ADCCON_STDBM            (1<<2)
#define S3C2410_ADCCON_READ_START       (1<<1)
#define S3C2410_ADCCON_ENABLE_START     (1<<0)
#define S3C2410_ADCCON_STARTMASK        (0x3<<0)

/* ADCTSC Register Bits */
#define S3C2410_ADCTSC_UD_SEN           (1<<8) /* ghcstop add for s3c2440a */
#define S3C2410_ADCTSC_YM_SEN           (1<<7)
#define S3C2410_ADCTSC_YP_SEN           (1<<6)
#define S3C2410_ADCTSC_XM_SEN           (1<<5)
#define S3C2410_ADCTSC_XP_SEN           (1<<4)
#define S3C2410_ADCTSC_PULL_UP_DISABLE  (1<<3)
#define S3C2410_ADCTSC_AUTO_PST         (1<<2)
#define S3C2410_ADCTSC_XY_PST(x)        (((x)&0x3)<<0)

/* ADCDAT0 Bits */
#define S3C2410_ADCDAT0_UPDOWN          (1<<15)
#define S3C2410_ADCDAT0_AUTO_PST        (1<<14)
#define S3C2410_ADCDAT0_XY_PST          (0x3<<12)
#define S3C2410_ADCDAT0_XPDATA_MASK     (0x03FF)

/* ADCDAT1 Bits */
#define S3C2410_ADCDAT1_UPDOWN          (1<<15)
#define S3C2410_ADCDAT1_AUTO_PST        (1<<14)
#define S3C2410_ADCDAT1_XY_PST          (0x3<<12)
#define S3C2410_ADCDAT1_YPDATA_MASK     (0x03FF)

#define WAIT4INT(x)  (((x)<<8) | \
             S3C2410_ADCTSC_YM_SEN | S3C2410_ADCTSC_YP_SEN | S3C2410_ADCTSC_XP_SEN | \
             S3C2410_ADCTSC_XY_PST(3))

#define AUTOPST      (S3C2410_ADCTSC_YM_SEN | S3C2410_ADCTSC_YP_SEN | S3C2410_ADCTSC_XP_SEN | \
             S3C2410_ADCTSC_AUTO_PST | S3C2410_ADCTSC_XY_PST(0))

#define X_MIN       74
#define X_MAX       934
#define Y_MIN       920
#define Y_MAX       89

struct s3c2410ts
{
    long xp;
    long yp;
    int count;
    int shift;

    int delay;
    int presc;

    char phys[32];
};
static struct s3c2410ts ts;

struct rtgui_touch_device
{
    struct rt_device parent;

    rt_timer_t poll_timer;
    rt_uint16_t x, y;

    rt_bool_t calibrating;
    rt_touch_calibration_func_t calibration_func;

    rt_touch_eventpost_func_t eventpost_func;
    void *eventpost_param;

    rt_uint16_t min_x, max_x;
    rt_uint16_t min_y, max_y;

    rt_uint16_t width;
    rt_uint16_t height;

    rt_bool_t first_down_report;
};
static struct rtgui_touch_device *touch = RT_NULL;

#ifdef PKG_USING_GUIENGINE
static void report_touch_input(int updown)
{
    struct rtgui_event_mouse emouse;

    RTGUI_EVENT_MOUSE_BUTTON_INIT(&emouse);
    emouse.wid = RT_NULL;

    /* set emouse button */
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT;
    emouse.parent.sender = RT_NULL;

    if (updown)
    {
        ts.xp = ts.xp / ts.count;
        ts.yp = ts.yp / ts.count;;

    #ifdef TOUCH_SWAP_XY
        ts.xp = ts.xp + ts.yp;
        ts.yp = ts.xp - ts.yp;
        ts.xp = ts.xp - ts.yp;
    #endif

        if ((touch->calibrating == RT_TRUE) && (touch->calibration_func != RT_NULL))
        {
            touch->x = ts.xp;
            touch->y = ts.yp;
        }
        else
        {
            if (touch->max_x > touch->min_x)
            {
                touch->x = touch->width * (ts.xp-touch->min_x)/(touch->max_x-touch->min_x);
            }
            else
            {
                touch->x = touch->width * ( touch->min_x - ts.xp ) / (touch->min_x-touch->max_x);
            }

            if (touch->max_y > touch->min_y)
            {
                touch->y = touch->height * ( ts.yp - touch->min_y ) / (touch->max_y-touch->min_y);
            }
            else
            {
                touch->y = touch->height * ( touch->min_y - ts.yp ) / (touch->min_y-touch->max_y);
            }
        }

        emouse.x = touch->x;
        emouse.y = touch->y;
        if (touch->first_down_report == RT_TRUE)
        {
            emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
            emouse.button |= RTGUI_MOUSE_BUTTON_DOWN;
        }
        else
        {
            emouse.parent.type = RTGUI_EVENT_MOUSE_MOTION;
            emouse.button = 0;
        }
    }
    else
    {
        emouse.x = touch->x;
        emouse.y = touch->y;
        emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
        emouse.button |= RTGUI_MOUSE_BUTTON_UP;
        if ((touch->calibrating == RT_TRUE) && (touch->calibration_func != RT_NULL))
        {
            /* callback function */
            touch->calibration_func(emouse.x, emouse.y);
        }
    }

    /* rt_kprintf("touch %s: ts.x: %d, ts.y: %d\n", updown? "down" : "up",
    touch->x, touch->y); */

    /* send event to server */
    if (touch->calibrating != RT_TRUE)
    {
        rtgui_server_post_event((&emouse.parent), sizeof(emouse));
    }
}
#else
static void report_touch_input(int updown)
{
    struct rt_touch_event touch_event;

    if (updown)
    {
        ts.xp = ts.xp / ts.count;
        ts.yp = ts.yp / ts.count;

        if ((touch->calibrating == RT_TRUE) && (touch->calibration_func != RT_NULL))
        {
            touch->x = ts.xp;
            touch->y = ts.yp;
        }
        else
        {
            if (touch->max_x > touch->min_x)
            {
                touch->x = touch->width * ( ts.xp - touch->min_x ) / (touch->max_x-touch->min_x);
            }
            else
            {
                touch->x = touch->width * ( touch->min_x - ts.xp ) / (touch->min_x-touch->max_x);
            }

            if (touch->max_y > touch->min_y)
            {
                touch->y = touch->height * ( ts.yp - touch->min_y ) / (touch->max_y-touch->min_y);
            }
            else
            {
                touch->y = touch->height * ( touch->min_y - ts.yp ) / (touch->min_y-touch->max_y);
            }
        }

        touch_event.x = touch->x;
        touch_event.y = touch->y;
        touch_event.pressed = 1;

        if (touch->first_down_report == RT_TRUE)
        {
            if (touch->calibrating != RT_TRUE && touch->eventpost_func)
            {
                touch->eventpost_func(touch->eventpost_param, &touch_event);
            }
        }
    }
    else
    {
        touch_event.x = touch->x;
        touch_event.y = touch->y;
        touch_event.pressed = 0;

        if ((touch->calibrating == RT_TRUE) && (touch->calibration_func != RT_NULL))
        {
            /* callback function */
            touch->calibration_func(touch_event.x, touch_event.y);
        }

        if (touch->calibrating != RT_TRUE && touch->eventpost_func)
        {
            touch->eventpost_func(touch->eventpost_param, &touch_event);
        }
    }
}
#endif

static void touch_timer_fire(void *parameter)
{
    rt_uint32_t data0;
    rt_uint32_t data1;
    int updown;

    data0 = ADCDAT0;
    data1 = ADCDAT1;

    updown = (!(data0 & S3C2410_ADCDAT0_UPDOWN)) && (!(data1 & S3C2410_ADCDAT0_UPDOWN));

    if (updown)
    {
        if (ts.count != 0)
        {
            report_touch_input(updown);
        }

        ts.xp = 0;
        ts.yp = 0;
        ts.count = 0;

        ADCTSC = S3C2410_ADCTSC_PULL_UP_DISABLE | AUTOPST;
        ADCCON |= S3C2410_ADCCON_ENABLE_START;
    }
}

static void s3c2410_adc_stylus_action(void)
{
    rt_uint32_t data0;
    rt_uint32_t data1;

    data0 = ADCDAT0;
    data1 = ADCDAT1;

    ts.xp += data0 & S3C2410_ADCDAT0_XPDATA_MASK;
    ts.yp += data1 & S3C2410_ADCDAT1_YPDATA_MASK;
    ts.count ++;

    if (ts.count < (1<<ts.shift))
    {
        ADCTSC = S3C2410_ADCTSC_PULL_UP_DISABLE | AUTOPST;
        ADCCON |= S3C2410_ADCCON_ENABLE_START;
    }
    else
    {
        if (touch->first_down_report)
        {
            report_touch_input(1);
            ts.xp = 0;
            ts.yp = 0;
            ts.count = 0;
            touch->first_down_report = 0;
        }
        /* start timer */
        rt_timer_start(touch->poll_timer);
        ADCTSC = WAIT4INT(1);
    }

    SUBSRCPND |= BIT_SUB_ADC;
}

static void s3c2410_intc_stylus_updown(void)
{
    rt_uint32_t data0;
    rt_uint32_t data1;
    int updown;

    data0 = ADCDAT0;
    data1 = ADCDAT1;

    updown = (!(data0 & S3C2410_ADCDAT0_UPDOWN)) && (!(data1 & S3C2410_ADCDAT0_UPDOWN));

    /* rt_kprintf("stylus: %s\n", updown? "down" : "up"); */

    if (updown)
    {
        touch_timer_fire(0);
    }
    else
    {
        /* stop timer */
        rt_timer_stop(touch->poll_timer);
        touch->first_down_report = RT_TRUE;
        if (ts.xp >= 0 && ts.yp >= 0)
        {
            report_touch_input(updown);
        }
        ts.count = 0;
        ADCTSC = WAIT4INT(0);
    }

    SUBSRCPND |= BIT_SUB_TC;
}

static void rt_touch_handler(int irqno, void *param)
{
    if (SUBSRCPND & BIT_SUB_ADC)
    {
        /* INT_SUB_ADC */
        s3c2410_adc_stylus_action();
    }

    if (SUBSRCPND & BIT_SUB_TC)
    {
        /* INT_SUB_TC */
        s3c2410_intc_stylus_updown();
    }

    /* clear interrupt */
    INTPND |= (1ul << INTADC);
}

/* RT-Thread Device Interface */
static rt_err_t rtgui_touch_init(rt_device_t dev)
{
    /* init touch screen structure */
    rt_memset(&ts, 0, sizeof(struct s3c2410ts));

    ts.delay = 50000;
    ts.presc = 9;
    ts.shift = 2;
    ts.count = 0;
    ts.xp = ts.yp = 0;

    ADCCON = S3C2410_ADCCON_PRSCEN | S3C2410_ADCCON_PRSCVL(ts.presc);
    ADCDLY = ts.delay;

    ADCTSC = WAIT4INT(0);

    rt_hw_interrupt_install(INTADC, rt_touch_handler, RT_NULL , "INTADC");
    rt_hw_interrupt_umask(INTADC);

    /* clear interrupt */
    INTPND |= (1ul << INTADC);

    SUBSRCPND |= BIT_SUB_TC;
    SUBSRCPND |= BIT_SUB_ADC;

    /* install interrupt handler */
    INTSUBMSK &= ~BIT_SUB_ADC;
    INTSUBMSK &= ~BIT_SUB_TC;

    touch->first_down_report = RT_TRUE;

    return RT_EOK;
}

static rt_err_t rtgui_touch_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RT_TOUCH_CALIBRATION:
        touch->calibrating = RT_TRUE;
        touch->calibration_func = (rt_touch_calibration_func_t)args;
        break;

    case RT_TOUCH_NORMAL:
        touch->calibrating = RT_FALSE;
        break;

    case RT_TOUCH_CALIBRATION_DATA:
    {
        struct calibration_data *data;

        data = (struct calibration_data *)args;

        /* update */
        touch->min_x = data->min_x;
        touch->max_x = data->max_x;
        touch->min_y = data->min_y;
        touch->max_y = data->max_y;

        /*
            rt_kprintf("min_x = %d, max_x = %d, min_y = %d, max_y = %d\n",
                touch->min_x, touch->max_x, touch->min_y, touch->max_y);
        */
    }
        break;

    case RT_TOUCH_EVENTPOST:
        touch->eventpost_func = (rt_touch_eventpost_func_t)args;
        break;

    case RT_TOUCH_EVENTPOST_PARAM:
        touch->eventpost_param = args;
        break;
    }

    return RT_EOK;
}

int rtgui_touch_hw_init(void)
{
    rt_err_t result = RT_FALSE;
    rt_device_t device = RT_NULL;
    struct rt_device_graphic_info info;

    touch = (struct rtgui_touch_device *)rt_malloc(sizeof(struct rtgui_touch_device));
    if (touch == RT_NULL)
        return -RT_ERROR; /* no memory yet */

    /* clear device structure */
    rt_memset(&(touch->parent), 0, sizeof(struct rt_device));
    touch->calibrating = RT_FALSE;
    touch->min_x = X_MIN;
    touch->max_x = X_MAX;
    touch->min_y = Y_MIN;
    touch->max_y = Y_MAX;
    touch->eventpost_func  = RT_NULL;
    touch->eventpost_param = RT_NULL;

    /* init device structure */
    touch->parent.type = RT_Device_Class_Unknown;
    touch->parent.init = rtgui_touch_init;
    touch->parent.control = rtgui_touch_control;
    touch->parent.user_data = RT_NULL;

    device = rt_device_find("lcd");
    if (device == RT_NULL)
    {
        rt_kprintf("No lcd found\n");
        return -RT_ERROR; /* no this device */
    }

    /* get graphic device info */
    result = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
    if (result != RT_EOK)
    {
        /* get device information failed */
        rt_kprintf("Get graphic device info failed\n");
        return -RT_ERROR;
    }

    touch->width = info.width;
    touch->height = info.height;

    /* create 1/8 second timer */
    touch->poll_timer = rt_timer_create("touch", touch_timer_fire, RT_NULL,
                                        RT_TICK_PER_SECOND/8, RT_TIMER_FLAG_PERIODIC);

    /* register touch device to RT-Thread */
    rt_device_register(&(touch->parent), "touch", RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}

INIT_PREV_EXPORT(rtgui_touch_hw_init);
