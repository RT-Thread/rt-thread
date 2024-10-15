/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-20     tyustli      the first version
 */

#ifndef __DEV_TOUCH_H__
#define __DEV_TOUCH_H__

#include <rtthread.h>
#include "dev_pin.h"
/**
 * @addtogroup  Drivers          RTTHREAD Driver
 * @defgroup    Touch            Touch
 *
 * @brief       Touch driver api
 *
 * <b>Example</b>
 * @code {.c}
 * #include <rtthread.h>
 * #include "rtdevice.h"
 *
 * static rt_thread_t  gt9147_thread = RT_NULL;
 * static rt_sem_t     gt9147_sem = RT_NULL;
 * static rt_device_t  dev = RT_NULL;
 * static struct       rt_touch_data *read_data;
 *
 * // 读取数据线程入口函数
 * static void gt9147_entry(void *parameter)
 * {
 *     struct rt_touch_data *read_data;
 *     read_data = (struct rt_touch_data *)rt_malloc(sizeof(struct rt_touch_data) * 5);
 *
 *     while (1)
 *     {
 *         // 请求信号量
 *         rt_sem_take(gt9147_sem, RT_WAITING_FOREVER);
 *         // 读取五个点的触摸信息
 *         if (rt_device_read(dev, 0, read_data, 5) == 5)
 *         {
 *             for (rt_uint8_t i = 0; i < 5; i++)
 *             {
 *                 if (read_data[i].event == RT_TOUCH_EVENT_DOWN || read_data[i].event == RT_TOUCH_EVENT_MOVE)
 *                 {
 *                     rt_kprintf("%d %d %d %d %d\n",
 *                                 read_data[i].track_id,
 *                                 read_data[i].x_coordinate,
 *                                 read_data[i].y_coordinate,
 *                                 read_data[i].timestamp,
 *                                 read_data[i].width);
 *                 }
 *             }
 *         }
 *         // 打开中断
 *         rt_device_control(dev, RT_TOUCH_CTRL_ENABLE_INT, RT_NULL);
 *     }
 * }
 *
 * // 接收回调函数
 * static rt_err_t rx_callback(rt_device_t dev, rt_size_t size)
 * {
 *     // 关闭中断
 *     rt_device_control(dev, RT_TOUCH_CTRL_DISABLE_INT, RT_NULL);
 *     // 释放信号量
 *     rt_sem_release(gt9147_sem);
 *     return 0;
 * }
 *
 * static int gt9147_sample(void)
 * {
 *     // 查找 Touch 设备
 *     dev = rt_device_find("touch");
 *
 *     if (dev == RT_NULL)
 *     {
 *         rt_kprintf("can't find device:%s\n", "touch");
 *         return -1;
 *     }
 *     // 以中断的方式打开设备
 *     if (rt_device_open(dev, RT_DEVICE_FLAG_INT_RX) != RT_EOK)
 *     {
 *         rt_kprintf("open device failed!");
 *         return -1;
 *     }
 *     // 设置接收回调
 *     rt_device_set_rx_indicate(dev, rx_callback);
 *     // 创建信号量
 *     gt9147_sem = rt_sem_create("dsem", 0, RT_IPC_FLAG_PRIO);
 *
 *     if (gt9147_sem == RT_NULL)
 *     {
 *         rt_kprintf("create dynamic semaphore failed.\n");
 *         return -1;
 *     }
 *     // 创建读取数据线程
 *     gt9147_thread = rt_thread_create("thread1",
 *                                      gt9147_entry,
 *                                      RT_NULL,
 *                                      THREAD_STACK_SIZE,
 *                                      THREAD_PRIORITY,
 *                                      THREAD_TIMESLICE);
 *     // 启动线程
 *     if (gt9147_thread != RT_NULL)
 *         rt_thread_startup(gt9147_thread);
 *
 *     return 0;
 * }
 * MSH_CMD_EXPORT(gt9147_sample, gt9147 sample);
 * @endcode
 *
 * @ingroup     Drivers
 */

/*!
 * @addtogroup Touch
 * @{
 */
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

/**
 * @brief Touch information
*/
struct rt_touch_info
{
    rt_uint8_t     type;                       /* The touch type */
    rt_uint8_t     vendor;                     /* Vendor of touchs */
    rt_uint8_t     point_num;                  /* Support point num */
    rt_int32_t     range_x;                    /* X coordinate range */
    rt_int32_t     range_y;                    /* Y coordinate range */
};

/**
 * @brief Touch configuration
*/
struct rt_touch_config
{
#ifdef RT_TOUCH_PIN_IRQ
    struct rt_device_pin_mode   irq_pin;       /* Interrupt pin, The purpose of this pin is to notification read data */
#endif
    char                        *dev_name;     /* The name of the communication device */
    void                        *user_data;
};

typedef struct rt_touch_device *rt_touch_t;
/**
 * @brief Touch device
*/
struct rt_touch_device
{
    struct rt_device            parent;        /* The standard device */
    struct rt_touch_info        info;          /* The touch info data */
    struct rt_touch_config      config;        /* The touch config data */

    const struct rt_touch_ops  *ops;           /* The touch ops */
    rt_err_t (*irq_handle)(rt_touch_t touch);  /* Called when an interrupt is generated, registered by the driver */
};

/**
 * @brief Touch data
*/
struct rt_touch_data
{
    rt_uint8_t          event;                 /* The touch event of the data */
    rt_uint8_t          track_id;              /* Track id of point */
    rt_uint8_t          width;                 /* Point of width */
    rt_uint16_t         x_coordinate;          /* Point of x coordinate */
    rt_uint16_t         y_coordinate;          /* Point of y coordinate */
    rt_tick_t           timestamp;             /* The timestamp when the data was received */
};

/**
 * @brief Touch device operations
*/
struct rt_touch_ops
{
    rt_size_t (*touch_readpoint)(struct rt_touch_device *touch, void *buf, rt_size_t touch_num);
    rt_err_t (*touch_control)(struct rt_touch_device *touch, int cmd, void *arg);
};

/**
 * @brief register a touch device
 * @param touch the touch device
 * @param name the name of touch device
 * @param flag the flag of touch device
 * @param data the user data of touch device
 * @return rt_err_t error code
 */
int rt_hw_touch_register(rt_touch_t    touch,
                         const char    *name,
                         rt_uint32_t   flag,
                         void          *data);

/**
 * @brief Touch irq handle
 * @param touch the touch device
 *
 * @note If you doesn't use pin device. you must call this function in your touch irq callback
 */
void rt_hw_touch_isr(rt_touch_t touch);

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif /* __DEV_TOUCH_H__ */
