/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang         the first version
 * 2018-10-29     XY
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_touch.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"


#define TP_INT_PIN 54       /* GPIO_AD_B0_11 */
#define TP_RST_PIN 45       /* GPIO_AD_B0_02 */

#define FT5x06_TS_ADDR      (0x38)

#if 0
#define TPDEBUG     rt_kprintf
#else
#define TPDEBUG(...)
#endif

static struct touch_driver ft5x06_driver;

typedef enum _touch_event
{
    kTouch_Down = 0,    /*!< The state changed to touched. */
    kTouch_Up = 1,      /*!< The state changed to not touched. */
    kTouch_Contact = 2, /*!< There is a continuous touch being detected. */
    kTouch_Reserved = 3 /*!< No touch information available. */
} touch_event_t;

typedef struct _touch_point
{
    touch_event_t TOUCH_EVENT;  /*!< Indicates the state or event of the touch point. */
    uint8_t TOUCH_ID;           /*!< Id of the touch point. This numeric value stays constant between down and up event. */
    uint16_t TOUCH_X;           /*!< X coordinate of the touch point */
    uint16_t TOUCH_Y;           /*!< Y coordinate of the touch point */
} touch_point_t;

typedef struct _ft5406_touch_point
{
    uint8_t XH;
    uint8_t XL;
    uint8_t YH;
    uint8_t YL;
    uint8_t RESERVED[2];
} ft5406_touch_point_t;

typedef struct _ft5406_touch_data
{
    uint8_t DEVIDE_MODE;
    uint8_t GEST_ID;
    uint8_t TD_STATUS;
    ft5406_touch_point_t TOUCH;
} ft5406_touch_data_t;

#define TOUCH_POINT_GET_EVENT(T)    ((touch_event_t)((T).XH >> 6))
#define TOUCH_POINT_GET_ID(T)       ((T).YH >> 4)
#define TOUCH_POINT_GET_X(T)        ((((T).XH & 0x0f) << 8) | (T).XL)
#define TOUCH_POINT_GET_Y(T)        ((((T).YH & 0x0f) << 8) | (T).YL)

static int ft5406_read_touch(touch_point_t *dp)
{
    rt_uint8_t cmd = 0;
    ft5406_touch_data_t touch_data;

    if (rt_touch_read(FT5x06_TS_ADDR, &cmd, 1, &touch_data, sizeof(ft5406_touch_data_t)) != 0)
        return -1;

    dp->TOUCH_X     = TOUCH_POINT_GET_Y(touch_data.TOUCH);
    dp->TOUCH_Y     = TOUCH_POINT_GET_X(touch_data.TOUCH);
    dp->TOUCH_EVENT = TOUCH_POINT_GET_EVENT(touch_data.TOUCH);
    dp->TOUCH_ID    = TOUCH_POINT_GET_ID(touch_data.TOUCH);

    if (dp->TOUCH_EVENT == 3) return -1;

    if (touch_data.TD_STATUS != 0)
        return 0;
    else
        return -1;
}

static void ft5x06_isr_enable(rt_bool_t enable)
{
    if(enable == RT_TRUE)
    {
        rt_pin_irq_enable(TP_INT_PIN, PIN_IRQ_ENABLE);
    }
    else
    {
        rt_pin_irq_enable(TP_INT_PIN, PIN_IRQ_DISABLE);
    }
}

static void ft5x06_touch_isr(void *parameter)
{
    TPDEBUG("[TP] ft5x06_touch_isr\n");

    ft5x06_isr_enable(RT_FALSE);
    rt_sem_release(ft5x06_driver.isr_sem);
}

static rt_err_t ft5x06_read_point(touch_message_t msg)
{
    touch_point_t dp;

    if (ft5406_read_touch(&dp) != 0)
    {
        msg->event = TOUCH_EVENT_UP;
    }
    else
    {
        if (dp.TOUCH_EVENT == kTouch_Up)
        {
            msg->event = TOUCH_EVENT_UP;
        }
        else if (dp.TOUCH_EVENT == kTouch_Down)
        {
            msg->event = TOUCH_EVENT_DOWN;
        }
        else if (dp.TOUCH_EVENT == kTouch_Contact)
        {
            msg->event = TOUCH_EVENT_MOVE;
        }
        else
        {
            msg->event = TOUCH_EVENT_UP;
        }
    }

    msg->x = dp.TOUCH_X;
    msg->y = dp.TOUCH_Y;

    TPDEBUG("[TP] [%d, %d] %s\n", msg->x, msg->y,
            msg->event == TOUCH_EVENT_DOWN ? "DOWN" : (msg->event == TOUCH_EVENT_MOVE ? "MOVE" : (msg->event == TOUCH_EVENT_UP ? "UP" : "NONE")));

    if (msg->event != TOUCH_EVENT_UP)
    {
        rt_sem_release(ft5x06_driver.isr_sem);
    }
    else
    {
        ft5x06_isr_enable(RT_TRUE);
    }

    return RT_EOK;
}

static void ft5x06_init(struct rt_i2c_bus_device *i2c_bus)
{
    ft5x06_driver.isr_sem = rt_sem_create("ft5x06", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(ft5x06_driver.isr_sem);

    rt_pin_attach_irq(TP_INT_PIN, PIN_IRQ_MODE_LOW_LEVEL, ft5x06_touch_isr, &ft5x06_driver);
    rt_pin_irq_enable(TP_INT_PIN, PIN_IRQ_ENABLE);
    rt_thread_delay(RT_TICK_PER_SECOND / 5);
}

static void ft5x06_deinit(void)
{
    if (ft5x06_driver.isr_sem)
    {
        rt_sem_delete(ft5x06_driver.isr_sem);
        ft5x06_driver.isr_sem = RT_NULL;
    }
}

struct touch_ops ft5x06_ops =
{
    ft5x06_init,
    ft5x06_deinit,
    ft5x06_read_point,
};

static void ft5406_hw_reset(void)
{
    gpio_pin_config_t pin_config =
    {
        kGPIO_DigitalOutput, 0,
    };

    CLOCK_EnableClock(kCLOCK_Gpio1);

    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_GPIO1_IO02, 0U);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_02_GPIO1_IO02, 0x10B0u);

    /* Enable touch panel controller */
    GPIO_PinInit(GPIO1, 2, &pin_config);
    GPIO_WritePinOutput(GPIO1, 2, 1);
    rt_thread_delay(RT_TICK_PER_SECOND / 20);
    GPIO_WritePinOutput(GPIO1, 2, 0);
    rt_thread_delay(RT_TICK_PER_SECOND / 20);
    GPIO_WritePinOutput(GPIO1, 2, 1);
}

static rt_bool_t ft5x06_probe(struct rt_i2c_bus_device *i2c_bus)
{
    rt_uint16_t cmd = 0x000c;
    rt_uint16_t tmp[2];
    rt_uint16_t CurVersion;

    ft5406_hw_reset();

    if (rt_touch_read(FT5x06_TS_ADDR, &cmd, 2, tmp, 2) != 0)
    {
        TPDEBUG("[TP] %s failed!\n", __func__);
        return RT_FALSE;
    }

    CurVersion = (tmp[0]<<8) | tmp[1];
    rt_kprintf("[TP] FT5X06 Touch Version : %d\n", CurVersion);

    return RT_TRUE;
}

int ft5x06_driver_register(void)
{
    ft5x06_driver.probe = ft5x06_probe;
    ft5x06_driver.ops = &ft5x06_ops;
    ft5x06_driver.user_data = RT_NULL;

    rt_touch_drivers_register(&ft5x06_driver);

    return 0;
}
INIT_ENV_EXPORT(ft5x06_driver_register);
