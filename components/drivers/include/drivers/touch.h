/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-20     tyustli      the first version
 */

#ifndef __TOUCH_H__
#define __TOUCH_H__

#include <rtthread.h>
#include "pin.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_RTC
#define  rt_touch_get_ts()  time(RT_NULL)          /* API for the touch to get the timestamp */
#else
#define  rt_touch_get_ts()  rt_tick_get()          /* API for the touch to get the timestamp */
#endif

/* Touch vendor types */
#define RT_TOUCH_VENDOR_UNKNOWN          (0)  /* unknown */
#define RT_TOUCH_VENDOR_GT               (1)  /* GTxx series */
#define RT_TOUCH_VENDOR_FT               (2)  /* FTxx series */

/* Touch ic type*/
#define  RT_TOUCH_TYPE_NONE              (0)  /* touch ic none */
#define  RT_TOUCH_TYPE_CAPACITANCE       (1)  /* capacitance ic */
#define  RT_TOUCH_TYPE_RESISTANCE        (2)  /* resistance ic */

/* Touch control cmd types */
#define  RT_TOUCH_CTRL_GET_ID            (RT_DEVICE_CTRL_BASE(Touch) + 0)   /* Get device id */
#define  RT_TOUCH_CTRL_GET_INFO          (RT_DEVICE_CTRL_BASE(Touch) + 1)   /* Get touch info */
#define  RT_TOUCH_CTRL_SET_MODE          (RT_DEVICE_CTRL_BASE(Touch) + 2)   /* Set touch's work mode. ex. RT_TOUCH_MODE_POLLING,RT_TOUCH_MODE_INT */
#define  RT_TOUCH_CTRL_SET_X_RANGE       (RT_DEVICE_CTRL_BASE(Touch) + 3)   /* Set x coordinate range */
#define  RT_TOUCH_CTRL_SET_Y_RANGE       (RT_DEVICE_CTRL_BASE(Touch) + 4)   /* Set y coordinate range */
#define  RT_TOUCH_CTRL_SET_X_TO_Y        (RT_DEVICE_CTRL_BASE(Touch) + 5)   /* Set X Y coordinate exchange */
#define  RT_TOUCH_CTRL_DISABLE_INT       (RT_DEVICE_CTRL_BASE(Touch) + 6)   /* Disable interrupt */
#define  RT_TOUCH_CTRL_ENABLE_INT        (RT_DEVICE_CTRL_BASE(Touch) + 7)   /* Enable interrupt */
#define  RT_TOUCH_CTRL_POWER_ON          (RT_DEVICE_CTRL_BASE(Touch) + 8)   /* Touch Power On */
#define  RT_TOUCH_CTRL_POWER_OFF         (RT_DEVICE_CTRL_BASE(Touch) + 9)   /* Touch Power Off */
#define  RT_TOUCH_CTRL_GET_STATUS        (RT_DEVICE_CTRL_BASE(Touch) + 10)  /* Get Touch Power Status */

/* Touch event */
#define RT_TOUCH_EVENT_NONE              (0)   /* Touch none */
#define RT_TOUCH_EVENT_UP                (1)   /* Touch up event */
#define RT_TOUCH_EVENT_DOWN              (2)   /* Touch down event */
#define RT_TOUCH_EVENT_MOVE              (3)   /* Touch move event */

struct rt_touch_info
{
    rt_uint8_t     type;                       /* The touch type */
    rt_uint8_t     vendor;                     /* Vendor of touchs */
    rt_uint8_t     point_num;                  /* Support point num */
    rt_int32_t     range_x;                    /* X coordinate range */
    rt_int32_t     range_y;                    /* Y coordinate range */
};

struct rt_touch_config
{
#ifdef RT_TOUCH_PIN_IRQ
    struct rt_device_pin_mode   irq_pin;       /* Interrupt pin, The purpose of this pin is to notification read data */
#endif
    char                        *dev_name;     /* The name of the communication device */
    void                        *user_data;
};

typedef struct rt_touch_device *rt_touch_t;
struct rt_touch_device
{
    struct rt_device            parent;        /* The standard device */
    struct rt_touch_info        info;          /* The touch info data */
    struct rt_touch_config      config;        /* The touch config data */

    const struct rt_touch_ops  *ops;           /* The touch ops */
    rt_err_t (*irq_handle)(rt_touch_t touch);  /* Called when an interrupt is generated, registered by the driver */
};

struct rt_touch_data
{
    rt_uint8_t          event;                 /* The touch event of the data */
    rt_uint8_t          track_id;              /* Track id of point */
    rt_uint8_t          width;                 /* Point of width */
    rt_uint16_t         x_coordinate;          /* Point of x coordinate */
    rt_uint16_t         y_coordinate;          /* Point of y coordinate */
    rt_tick_t           timestamp;             /* The timestamp when the data was received */
};

struct rt_touch_ops
{
    rt_size_t (*touch_readpoint)(struct rt_touch_device *touch, void *buf, rt_size_t touch_num);
    rt_err_t (*touch_control)(struct rt_touch_device *touch, int cmd, void *arg);
};

int rt_hw_touch_register(rt_touch_t    touch,
                         const char    *name,
                         rt_uint32_t   flag,
                         void          *data);

/* if you doesn't use pin device. you must call this function in your touch irq callback */
void rt_hw_touch_isr(rt_touch_t touch);

#ifdef __cplusplus
}
#endif

#endif /* __TOUCH_H__ */
