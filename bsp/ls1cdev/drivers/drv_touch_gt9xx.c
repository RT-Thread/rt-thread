/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     Zhangyihong  the first version
 * 2018-04-03     XY           gt9xx for 1024 * 600
 * 2018-04-14     liu2guang    optimize int and rst to pin framework
 * 2017-08-08     XY           imxrt1052
 * 2018-10-29     XY
 */

#include "drv_touch.h"
#include "string.h"

#ifdef TINA_USING_TOUCH

#define TP_INT_PIN 89
#define TP_RST_PIN 87

#ifndef TP_INT_PIN
#error "Please config touch panel INT pin."
#endif
#ifndef TP_RST_PIN
#error "Please config touch panel RST pin."
#endif

#ifndef IIC_RETRY_NUM
#define IIC_RETRY_NUM 2
#endif

#define GT9xx_TS_ADDR               (0x5D)

#define gt9xx_READ_XY_REG           (0x814E)    /* 坐标寄存器       */
#define gt9xx_CLEARBUF_REG          (0x814E)    /* 清除坐标寄存器   */
#define gt9xx_CONFIG_REG            (0x8047)    /* 配置参数寄存器   */
#define gt9xx_COMMAND_REG           (0x8040)    /* 实时命令         */
#define gt9xx_PRODUCT_ID_REG        (0x8140)    /* 产品ID           */
#define gt9xx_VENDOR_ID_REG         (0x814A)    /* 当前模组选项信息 */
#define gt9xx_CONFIG_VERSION_REG    (0x8047)    /* 配置文件版本号   */
#define gt9xx_CONFIG_CHECKSUM_REG   (0x80FF)    /* 配置文件校验码   */
#define gt9xx_FIRMWARE_VERSION_REG  (0x8144)    /* 固件版本号       */

#if 0
#define TPDEBUG     rt_kprintf
#else
#define TPDEBUG(...)
#endif

static struct touch_driver gt9xx_driver;

void gt9xx_hw_reset(rt_uint8_t address)
{
    rt_tick_t delay = rt_tick_from_millisecond(30);

    rt_pin_mode(TP_RST_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(TP_INT_PIN, PIN_MODE_OUTPUT);

    if (address == 0x5D)
    {
        rt_pin_write(TP_RST_PIN, PIN_LOW);
        rt_pin_write(TP_INT_PIN, PIN_LOW);
        rt_thread_delay(delay);
        rt_pin_write(TP_RST_PIN, PIN_HIGH);
        rt_pin_write(TP_INT_PIN, PIN_LOW);
        rt_thread_delay(delay);
        rt_pin_write(TP_INT_PIN, PIN_LOW);
        rt_thread_delay(delay);
        rt_pin_write(TP_INT_PIN, PIN_HIGH);
    }
    else
    {
        rt_pin_write(TP_RST_PIN, PIN_LOW);
        rt_pin_write(TP_INT_PIN, PIN_HIGH);
        rt_thread_delay(delay);
        rt_pin_write(TP_RST_PIN, PIN_HIGH);
        rt_pin_write(TP_INT_PIN, PIN_HIGH);
        rt_thread_delay(delay);
        rt_pin_write(TP_INT_PIN, PIN_LOW);
        rt_thread_delay(delay);
        rt_pin_write(TP_INT_PIN, PIN_HIGH);
    }
}

static void gt9xx_soft_reset(struct rt_i2c_bus_device *i2c_bus)
{
    rt_uint8_t buf[3];

    buf[0] = (rt_uint8_t)((gt9xx_COMMAND_REG >> 8) & 0xFF);
    buf[1] = (rt_uint8_t)(gt9xx_COMMAND_REG & 0xFF);
    buf[2] = 0x02;
    rt_touch_write(GT9xx_TS_ADDR, buf, 3);
}

static rt_bool_t gt9xx_probe(struct rt_i2c_bus_device *i2c_bus)
{
    rt_uint8_t cmd[2];
    rt_uint8_t buffer[5] = {0};

    gt9xx_hw_reset(GT9xx_TS_ADDR);
    //gt9xx_soft_reset(i2c_bus);
    rt_thread_delay(RT_TICK_PER_SECOND / 5);

    cmd[0] = (rt_uint8_t)((gt9xx_PRODUCT_ID_REG >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(gt9xx_PRODUCT_ID_REG & 0xFF);
    if (rt_touch_read(GT9xx_TS_ADDR, &cmd, 2, buffer, 4) != 0)
    {
        TPDEBUG("[TP] %s failed!\n", __func__);
        return RT_FALSE;
    }

    buffer[4] = '\0';

    TPDEBUG("%#X %#X %#X %#X %#X\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

    if(!rt_strcmp((const char*)buffer, "911"))
    {
        rt_kprintf("[TP] Found chip gt911\n");
        return RT_TRUE;
    }
    else if(!rt_strcmp((const char*)buffer, "9147"))
    {
        rt_kprintf("[TP] Found chip gt9147\n");
        return RT_TRUE;
    }
    else if(!rt_strcmp((const char*)buffer, "9157"))
    {
        rt_kprintf("[TP] Found chip gt9157\n");
        return RT_TRUE;
    }
    else
    {
        rt_kprintf("[TP] Uknow chip gt9xx device: [%s]\n", buffer);
    }

    return RT_FALSE;
}

static void gt9xx_init(struct rt_i2c_bus_device *i2c_bus)
{
    rt_uint8_t buf = 0;
    rt_uint8_t cmd[2];

    gt9xx_driver.isr_sem = rt_sem_create("gt9xx", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(gt9xx_driver.isr_sem);

    cmd[0] = (rt_uint8_t)((gt9xx_CONFIG_VERSION_REG >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(gt9xx_CONFIG_VERSION_REG & 0xFF);
    rt_touch_read(GT9xx_TS_ADDR, &cmd, 2, &buf, 1);
    rt_kprintf("[TP] GT9xx Config version: 0x%02X\n", buf);

    cmd[0] = (rt_uint8_t)((gt9xx_VENDOR_ID_REG >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(gt9xx_VENDOR_ID_REG & 0xFF);
    rt_touch_read(GT9xx_TS_ADDR, &cmd, 2, &buf, 1);
    rt_kprintf("[TP] GT9xx Sensor id: 0x%02X\n", buf);

    rt_sem_release(gt9xx_driver.isr_sem);
}

static void gt9xx_deinit(void)
{
    rt_sem_delete(gt9xx_driver.isr_sem);
}

static rt_err_t gt9xx_read_point(touch_message_t msg)
{
    rt_uint8_t cmd[2];
    rt_uint8_t buf[8] = {0};
    static rt_uint8_t s_tp_down = 0;

    cmd[0] = (rt_uint8_t)((gt9xx_READ_XY_REG >> 8) & 0xFF);
    cmd[1] = (rt_uint8_t)(gt9xx_READ_XY_REG & 0xFF);
    rt_touch_read(GT9xx_TS_ADDR, &cmd, 2, buf, 8);

    if((buf[0] & 0x01) == 0)
    {
        if(s_tp_down)
        {
            s_tp_down = 0;
            msg->event = TOUCH_EVENT_UP;
        }
        else
        {
            msg->event = TOUCH_EVENT_NONE;
        }
    }
    else
    {
        msg->x = ((rt_uint16_t)buf[3] << 8) | buf[2];
        msg->y = ((rt_uint16_t)buf[5] << 8) | buf[4];

        if(s_tp_down)
        {
            msg->event = TOUCH_EVENT_MOVE;
        }
        else
        {
            msg->event = TOUCH_EVENT_DOWN;
            s_tp_down = 1;
        }
    }

    buf[0] = ((gt9xx_CLEARBUF_REG >> 8) & 0xFF);
    buf[1] = (gt9xx_CLEARBUF_REG & 0xFF);
    buf[2] = 0x00;
    rt_touch_write(GT9xx_TS_ADDR, buf, 3);

    rt_sem_release(gt9xx_driver.isr_sem);

    return RT_EOK;
}

struct touch_ops gt9xx_ops =
{
    .init       = gt9xx_init,
    .deinit     = gt9xx_deinit,
    .read_point = gt9xx_read_point,
};

static int gt9xx_driver_register(void)
{
    gt9xx_driver.probe     = gt9xx_probe;
    gt9xx_driver.ops       = &gt9xx_ops;
    gt9xx_driver.user_data = RT_NULL;

    rt_touch_drivers_register(&gt9xx_driver);

    return RT_EOK;
}
INIT_ENV_EXPORT(gt9xx_driver_register);

#endif
