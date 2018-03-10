/*
 * File      : drv_ft5x06.c
 *             ft5x06 touch driver
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-08     Yang        the first version
 */
 
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#endif

#include "board.h"

#define BSP_TOUCH_SAMPLE_HZ     30
#define I2CBUS_NAME             "i2c0"
#define FT5x06_TS_ADDR          0x38
#define TP_MAX_TOUCH_POINT      5
#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...)           rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)   
#endif

#define CTRL_NOAUTO_MONITOR    0x00
#define CTRL_AUTO_MONITOR      0x01

#define PMODE_ACTIVE           0x00
#define PMODE_MONITOR          0x01
#define PMODE_STANDBY          0x02
#define PMODE_HIBERNATE        0x03

#define G_MODE_POLLING         0x00
#define G_MODE_TRIGGER         0x01

#define TOUCH_POINT_GET_EVENT(T)    ((touch_event_t)((T).XH >> 6))
#define TOUCH_POINT_GET_ID(T)       ((T).YH >> 4)
#define TOUCH_POINT_GET_X(T)        ((((T).XH & 0x0f) << 8) | (T).XL)
#define TOUCH_POINT_GET_Y(T)        ((((T).YH & 0x0f) << 8) | (T).YL)

typedef enum _touch_event
{
    kTouch_Down = 0,        /*!< The state changed to touched. */
    kTouch_Up = 1,          /*!< The state changed to not touched. */
    kTouch_Contact = 2,     /*!< There is a continuous touch being detected. */
    kTouch_Reserved = 3     /*!< No touch information available. */
} touch_event_t;

typedef struct _touch_point
{
    touch_event_t TOUCH_EVENT;  /*!< Indicates the state or event of the touch point. */
    uint8_t TOUCH_ID;           /*!< Id of the touch point. This numeric value stays constant between down and up event. */
    uint16_t TOUCH_X;           /*!< X coordinate of the touch point */
    uint16_t TOUCH_Y;           /*!< Y coordinate of the touch point */
} touch_point_t;

typedef struct _ft5x06_touch_point
{
    uint8_t XH;
    uint8_t XL;
    uint8_t YH;
    uint8_t YL;
} ft5x06_touch_point_t;

typedef struct _ft5x06_touch_data
{
    uint8_t DEVIDE_MODE;
    uint8_t GEST_ID;
    uint8_t TD_STATUS;
    ft5x06_touch_point_t TOUCH;
} ft5x06_touch_data_t;

static struct rt_i2c_bus_device *_i2c_bus;

static int _ft5x06_read(unsigned char cmd,
                        void *buf,
                        size_t len)
{
    struct rt_i2c_msg msgs[2];

    msgs[0].addr  = FT5x06_TS_ADDR;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &cmd;
    msgs[0].len   = sizeof(cmd);

    msgs[1].addr  = FT5x06_TS_ADDR;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = buf;
    msgs[1].len   = len;

    if (rt_i2c_transfer(_i2c_bus, msgs, 2) == 2)
        return len;
    else
        return -1;
}

#ifdef RT_USING_FINSH
static int search_ft5x06(void)
{
    struct rt_i2c_msg msgs[2];
    uint8_t cmd = 0xA3;
    uint8_t buf = 0;

    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf   = &cmd;
    msgs[0].len   = sizeof(cmd);

    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf   = &buf;
    msgs[1].len   = 1;

    for (int i = 0; i <= 0x7f; i++)
    {
        int len;
        msgs[0].addr  = i;
        msgs[1].addr  = i;
        len = rt_i2c_transfer(_i2c_bus, msgs, 2);
        if (len == 2)
        {
            rt_kprintf("add:%02X transfer success, id: %02X\n", i, buf);
        } 
    }
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(search_ft5x06, sft, search ft5x06 chip);

static int ft5x06_dump(void)
{
    uint8_t i;
    uint8_t reg_value;
    
    DEBUG_PRINTF("[FTS] Touch Chip\r\n");
        
    for (i = 0; i < UINT8_MAX; i++)
    {
        _ft5x06_read(i, &reg_value, 1);
        
        if (i % 8 == 7)
            DEBUG_PRINTF("0x%02X = 0x%02X\r\n", i, reg_value);
        else
            DEBUG_PRINTF("0x%02X = 0x%02X ", i, reg_value);
    }
    DEBUG_PRINTF("\n");
    
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(ft5x06_dump, ftdump, ft5x06 dump registers);
#endif

static int ft5x06_read_touch(touch_point_t *dp)
{
#if 0
    uint8_t data[33];
    int i;
    
    _ft5x06_read(0, data, sizeof(data));
    
    for (i = 0; i < sizeof(data)/sizeof(data[0]); i++)
    {
        DEBUG_PRINTF("%02X ", data[i]);
    }
    DEBUG_PRINTF("\n");
    
    return -1;
#else
    ft5x06_touch_data_t touch_data;
    
    _ft5x06_read(0, &touch_data, sizeof(ft5x06_touch_data_t));

    dp->TOUCH_X = TOUCH_POINT_GET_Y(touch_data.TOUCH);
    dp->TOUCH_Y = TOUCH_POINT_GET_X(touch_data.TOUCH);

    DEBUG_PRINTF(" ==> status : %d (%d, %d)\n", touch_data.TD_STATUS, dp->TOUCH_X, dp->TOUCH_Y);

    if (touch_data.TD_STATUS != 0)
        return 0;
    else
        return -1;
#endif
}

static void _touch_session()
{
    touch_point_t tpd;
#ifdef RT_USING_RTGUI
    struct rtgui_event_mouse emouse;
#endif
    
    ft5x06_read_touch(&tpd);

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
        if (ft5x06_read_touch(&tpd) != 0)
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

}

static void touch_entry(void *p)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_GPIOH_CLK_ENABLE();

    /*Configure GPIO pin : PH7 */
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    while(1)
    {
        rt_thread_delay(RT_TICK_PER_SECOND / 60);

        if (HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_7) == GPIO_PIN_RESET)
        {
            _touch_session();
        }
        else
            continue;
    }
}

int ft5x06_hw_init(void)
{
    rt_thread_t tid;
    rt_device_t dev;

    dev = rt_device_find(I2CBUS_NAME);
    if (!dev) 
    {
        DEBUG_PRINTF("search device failed: %s\n", I2CBUS_NAME);
        return -1;
    }

    if (rt_device_open(dev, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        DEBUG_PRINTF("open device failed: %s\n", I2CBUS_NAME);
        return -1;
    }

    DEBUG_PRINTF("ft5x06 set i2c bus to %s\n", I2CBUS_NAME);
    _i2c_bus = (struct rt_i2c_bus_device *)dev;

    tid = rt_thread_create("touch", touch_entry, RT_NULL, 2048, 10, 20);
    if (!tid)
    {
        rt_device_close(dev);
        return -1;
    }

    rt_thread_startup(tid);

    return 0;
}
INIT_APP_EXPORT(ft5x06_hw_init);
