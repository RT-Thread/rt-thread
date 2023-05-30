/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <finsh.h>

#ifdef RT_USING_RTGUI
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#endif

#include "board.h"

#include "fsl_iocon.h"
#include "fsl_gpio.h"
#include "fsl_i2c.h"
#include "fsl_gint.h"

#define LCD_WIDTH               480
#define LCD_HEIGHT              272
#define BSP_TOUCH_SAMPLE_HZ     30

#define I2CBUS_NAME  "i2c2"

#if 0
#define FTDEBUG      rt_kprintf
#else
#define FTDEBUG(...)
#endif

#define TOUCH_SLP_TIME          (RT_TICK_PER_SECOND * 5)

#define FT5206_TS_ADDR          0x38
#define TP_MAX_TOUCH_POINT      2

enum ft5x0x_ts_regs
{
    FT5X0X_REG_THGROUP                  = 0x80,
    FT5X0X_REG_THPEAK                   = 0x81,
    FT5X0X_REG_THCAL                    = 0x82,
    FT5X0X_REG_THWATER                  = 0x83,
    FT5X0X_REG_THTEMP                   = 0x84,
    FT5X0X_REG_THDIFF                   = 0x85,
    FT5X0X_REG_CTRL                     = 0x86,
    FT5X0X_REG_TIMEENTERMONITOR         = 0x87,
    FT5X0X_REG_PERIODACTIVE             = 0x88,
    FT5X0X_REG_PERIODMONITOR            = 0x89,
    FT5X0X_REG_HEIGHT_B                 = 0x8a,
    FT5X0X_REG_MAX_FRAME                = 0x8b,
    FT5X0X_REG_DIST_MOVE                = 0x8c,
    FT5X0X_REG_DIST_POINT               = 0x8d,
    FT5X0X_REG_FEG_FRAME                = 0x8e,
    FT5X0X_REG_SINGLE_CLICK_OFFSET      = 0x8f,
    FT5X0X_REG_DOUBLE_CLICK_TIME_MIN    = 0x90,
    FT5X0X_REG_SINGLE_CLICK_TIME        = 0x91,
    FT5X0X_REG_LEFT_RIGHT_OFFSET        = 0x92,
    FT5X0X_REG_UP_DOWN_OFFSET           = 0x93,
    FT5X0X_REG_DISTANCE_LEFT_RIGHT      = 0x94,
    FT5X0X_REG_DISTANCE_UP_DOWN         = 0x95,
    FT5X0X_REG_ZOOM_DIS_SQR             = 0x96,
    FT5X0X_REG_RADIAN_VALUE             = 0x97,
    FT5X0X_REG_MAX_X_HIGH               = 0x98,
    FT5X0X_REG_MAX_X_LOW                = 0x99,
    FT5X0X_REG_MAX_Y_HIGH               = 0x9a,
    FT5X0X_REG_MAX_Y_LOW                = 0x9b,
    FT5X0X_REG_K_X_HIGH                 = 0x9c,
    FT5X0X_REG_K_X_LOW                  = 0x9d,
    FT5X0X_REG_K_Y_HIGH                 = 0x9e,
    FT5X0X_REG_K_Y_LOW                  = 0x9f,
    FT5X0X_REG_AUTO_CLB_MODE            = 0xa0,
    FT5X0X_REG_LIB_VERSION_H            = 0xa1,
    FT5X0X_REG_LIB_VERSION_L            = 0xa2,
    FT5X0X_REG_CIPHER                   = 0xa3,
    FT5X0X_REG_G_MODE                   = 0xa4,
    FT5X0X_REG_PMODE                    = 0xa5, /* Power Consume Mode */
    FT5X0X_REG_FIRMID                   = 0xa6,
    FT5X0X_REG_STATE                    = 0xa7,
    FT5X0X_REG_VENDID                   = 0xa8,
    FT5X0X_REG_ERR                      = 0xa9,
    FT5X0X_REG_CLB                      = 0xaa,
};

#define CTRL_NOAUTO_MONITOR    0x00
#define CTRL_AUTO_MONITOR      0x01

#define PMODE_ACTIVE           0x00
#define PMODE_MONITOR          0x01
#define PMODE_STANDBY          0x02
#define PMODE_HIBERNATE        0x03

#define G_MODE_POLLING         0x00
#define G_MODE_TRIGGER         0x01

typedef enum _touch_event
{
    kTouch_Down = 0,    /*!< The state changed to touched. */
    kTouch_Up = 1,      /*!< The state changed to not touched. */
    kTouch_Contact = 2, /*!< There is a continuous touch being detected. */
    kTouch_Reserved = 3 /*!< No touch information available. */
} touch_event_t;

typedef struct _touch_point
{
    touch_event_t TOUCH_EVENT; /*!< Indicates the state or event of the touch point. */
    uint8_t TOUCH_ID; /*!< Id of the touch point. This numeric value stays constant between down and up event. */
    uint16_t TOUCH_X; /*!< X coordinate of the touch point */
    uint16_t TOUCH_Y; /*!< Y coordinate of the touch point */
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
    uint8_t GEST_ID;
    uint8_t TD_STATUS;
    ft5406_touch_point_t TOUCH;
} ft5406_touch_data_t;

#define TOUCH_POINT_GET_EVENT(T) ((touch_event_t)((T).XH >> 6))
#define TOUCH_POINT_GET_ID(T) ((T).YH >> 4)
#define TOUCH_POINT_GET_X(T) ((((T).XH & 0x0f) << 8) | (T).XL)
#define TOUCH_POINT_GET_Y(T) ((((T).YH & 0x0f) << 8) | (T).YL)

static struct rt_i2c_bus_device *_i2c_bus;
static struct rt_semaphore _tp_sem;

static int _ft5406_read(unsigned char cmd,
                        void *buf,
                        size_t len)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = FT5206_TS_ADDR;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &cmd;
    msgs[0].len   = sizeof(cmd);

    msgs[1].addr  = FT5206_TS_ADDR;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = buf;
    msgs[1].len   = len;

    if (rt_i2c_transfer(_i2c_bus, msgs, 2) == 2)
        return len;
    else
        return -1;
}

static int ft5406_read_touch(touch_point_t *dp)
{
    ft5406_touch_data_t touch_data;

    _ft5406_read(0, &touch_data, sizeof(ft5406_touch_data_t));

    dp->TOUCH_X = TOUCH_POINT_GET_Y(touch_data.TOUCH);
    dp->TOUCH_Y = TOUCH_POINT_GET_X(touch_data.TOUCH);

    FTDEBUG(" ==> status : %d (%d, %d)\n", touch_data.TD_STATUS, dp->TOUCH_X, dp->TOUCH_Y);

    if (touch_data.TD_STATUS != 0)
        return 0;
    else
        return -1;
}

static void _touch_session()
{
    touch_point_t tpd;
#ifdef RT_USING_RTGUI
    struct rtgui_event_mouse emouse;
#endif

    ft5406_read_touch(&tpd);

#ifdef RT_USING_RTGUI
    emouse.parent.sender = RT_NULL;
    emouse.wid = RT_NULL;

    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN;
    emouse.x = tpd.TOUCH_X;
    emouse.y = tpd.TOUCH_Y;
    emouse.ts = rt_tick_get();
    emouse.id = emouse.ts;
    if (emouse.id == 0) emouse.id = 1;
    rtgui_server_post_event(&emouse.parent, sizeof(emouse));
#endif

    do
    {
        rt_thread_delay(RT_TICK_PER_SECOND / BSP_TOUCH_SAMPLE_HZ);
        if (ft5406_read_touch(&tpd) != 0)
            break;

#ifdef RT_USING_RTGUI
        emouse.parent.type = RTGUI_EVENT_MOUSE_MOTION;
        emouse.x = tpd.TOUCH_X;
        emouse.y = tpd.TOUCH_Y;
        emouse.ts = rt_tick_get();
        rtgui_server_post_event(&emouse.parent, sizeof(emouse));
#endif
    }
    while (1);

#ifdef RT_USING_RTGUI
    /* Always send touch up event. */
    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_UP;
    emouse.x = tpd.TOUCH_X;
    emouse.y = tpd.TOUCH_Y;
    emouse.ts = rt_tick_get();
    rtgui_server_post_event(&emouse.parent, sizeof(emouse));
#endif

    //} while (rt_sem_take(&_tp_sem, TOUCH_SLP_TIME) == RT_EOK);
}

void touch_down(void)
{
    rt_sem_release(&_tp_sem);
}

static void _touch(void *p)
{
    int io_s;

    gpio_pin_config_t pin_config =
    {
        kGPIO_DigitalInput, 0,
    };

    CLOCK_EnableClock(kCLOCK_Gpio4);

    /* Enable touch panel controller */
    GPIO_PinInit(GPIO, 4, 0, &pin_config);

    while(1)
    {
        rt_thread_delay(RT_TICK_PER_SECOND / 60);

        io_s = GPIO_ReadPinInput(GPIO, 4, 0);
        if (io_s == 0)
        {
            _touch_session();
        }
        else
            continue;
    }
}

int ft5406_hw_init(void)
{
    rt_thread_t tid;
    rt_device_t dev;

    dev = rt_device_find(I2CBUS_NAME);
    if (!dev) return -1;

    if (rt_device_open(dev, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
        return -1;

    FTDEBUG("ft5406 set i2c bus to %s\n", I2CBUS_NAME);
    _i2c_bus = (struct rt_i2c_bus_device *)dev;

    {
        gpio_pin_config_t pin_config =
        {
            kGPIO_DigitalOutput, 0,
        };

        CLOCK_EnableClock(kCLOCK_Gpio2);

        /* Enable touch panel controller */
        GPIO_PinInit(GPIO, 2, 27, &pin_config);
        GPIO_WritePinOutput(GPIO, 2, 27, 1);
        rt_thread_delay(50);
        GPIO_WritePinOutput(GPIO, 2, 27, 0);
        rt_thread_delay(50);
        GPIO_WritePinOutput(GPIO, 2, 27, 1);
    }

    rt_sem_init(&_tp_sem, "touch", 0, RT_IPC_FLAG_FIFO);
    tid = rt_thread_create("touch", _touch, RT_NULL,
                           2048, 10, 20);
    if (!tid)
    {
        rt_device_close(dev);
        return -1;
    }

    rt_thread_startup(tid);

    return 0;
}
INIT_APP_EXPORT(ft5406_hw_init);
