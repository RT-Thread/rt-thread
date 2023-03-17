/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2017-08-08     Yang          the first version
 * 2019-04-23     WillianChan   porting to ft6206
 * 2021-12-28     xiangxistu    copy by stm32f429-atk-apollo
 * 2021-04-23     xiangxistu    porting to GT9147
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include "drv_touch.h"

#include <stdint.h>
#include <string.h>

#ifdef BSP_USING_TOUCH_CAP

#define DBG_ENABLE
#define DBG_SECTION_NAME  "TOUCH.ft"
#define DBG_LEVEL         TOUCH_DBG_LEVEL
#define DBG_COLOR
#include <rtdbg.h>

static struct rt_i2c_bus_device *ft_i2c_bus;
static struct touch_drivers ft_driver;

static int ft_read(struct rt_i2c_bus_device *i2c_bus, rt_uint16_t addr, rt_uint8_t *buffer, rt_size_t length)
{
    int ret = -1;
    int retries = 0;
    rt_uint8_t register_16[3];
    register_16[0] = addr >> 8;
    register_16[1] = addr & 0xff;

    struct rt_i2c_msg msgs[] =
    {
        {
            .addr   = ft_driver.address,
            .flags  = RT_I2C_WR,
            .len    = 2,
            .buf    = register_16,
        },
        {
            .addr   = ft_driver.address,
            .flags  = RT_I2C_RD,
            .len    = length,
            .buf    = buffer,
        },
    };

    while (retries < IIC_RETRY_NUM)
    {
        ret = rt_i2c_transfer(i2c_bus, msgs, sizeof(msgs)/sizeof(struct rt_i2c_msg));
        if (ret == 2)break;
        retries++;
    }

    if (retries >= IIC_RETRY_NUM)
    {
        LOG_E("%s i2c read error: %d", __func__, ret);
        return -1;
    }

    return ret;
}

static void ft_write(struct rt_i2c_bus_device *i2c_bus, rt_uint16_t addr, rt_uint8_t *buffer, rt_size_t length)
{
    rt_uint8_t *send_buffer = rt_malloc(length + 2);

    RT_ASSERT(send_buffer);

    send_buffer[0] = addr >> 8;;
    send_buffer[1] = addr & 0xff;
    memcpy(send_buffer + 2, buffer, length);

    struct rt_i2c_msg msgs[] =
    {
        {
            .addr   = ft_driver.address,
            .flags  = RT_I2C_WR,
            .len    = length + 2,
            .buf    = send_buffer,
        }
    };

    length = rt_i2c_transfer(i2c_bus, msgs, 1);
    rt_free(send_buffer);
    send_buffer = RT_NULL;
}

static void ft_isr_enable(rt_bool_t enable)
{
    rt_pin_irq_enable(BSP_TOUCH_INT_PIN, enable);
}

static void ft_touch_isr(void *parameter)
{
    ft_isr_enable(RT_FALSE);
    rt_sem_release(ft_driver.isr_sem);
}

static rt_err_t ft_read_point(touch_msg_t msg)
{
    int ret = -1;
    uint8_t state = 0;
    uint8_t clear_state = 0;
    static uint8_t s_tp_down = 0;
    uint8_t point[5];
    ret = ft_read(ft_i2c_bus, 0X814E, &state, 1);
    if (ret < 0)
    {
        return -RT_ERROR;
    }

    /* According this state, to get point info */
    if(state&0X80&&((state&0XF)<6))
    {
        clear_state = 0;
        ft_write(ft_i2c_bus, 0X814E, &clear_state, 1);
    }
    else
    {
        if (s_tp_down)
        {
            s_tp_down = 0;
            msg->event = TOUCH_EVENT_UP;
            return RT_EOK;
        }
        msg->event = TOUCH_EVENT_NONE;
        return -RT_ERROR;
    }

    /* Only support one point */
    ret = ft_read(ft_i2c_bus, 0X8150, point, 4);
    if (ret < 0)
    {
        return -RT_ERROR;
    }

    msg->x = (point[1]&0x0F) << 8 | point[0];
    msg->y = (point[3]&0x0F) << 8 | point[2];
    LOG_D("x:%03d, y:%03d", msg->x, msg->y);

    if (s_tp_down)
    {
        msg->event = TOUCH_EVENT_MOVE;
        return RT_EOK;
    }
    msg->event = TOUCH_EVENT_DOWN;
    s_tp_down = 1;

    return RT_EOK;
}

static void ft_init(struct rt_i2c_bus_device *i2c_bus)
{
    if (ft_i2c_bus == RT_NULL)
    {
        ft_i2c_bus = i2c_bus;
    }
    ft_driver.isr_sem = rt_sem_create("ft", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(ft_driver.isr_sem);

    rt_pin_mode(BSP_TOUCH_INT_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(BSP_TOUCH_INT_PIN, PIN_IRQ_MODE_FALLING, ft_touch_isr, RT_NULL);

    rt_thread_mdelay(200);
}

static void ft_deinit(void)
{
    if (ft_driver.isr_sem)
    {
        rt_sem_delete(ft_driver.isr_sem);
        ft_driver.isr_sem = RT_NULL;
    }
}

struct touch_ops ft_ops =
{
    ft_isr_enable,
    ft_read_point,
    ft_init,
    ft_deinit,
};

static rt_bool_t ft_probe(struct rt_i2c_bus_device *i2c_bus)
{
#define TOUCH_CID_SIZE 4
    int err = 0;
    uint8_t cid[TOUCH_CID_SIZE + 1] = {0};

    ft_i2c_bus = i2c_bus;
    /* FT6206 Chip identification register address is 0xA8
     *
     * GT9147 ->  0X8140, CID
     *
     **/
    rt_memset(cid, 0, TOUCH_CID_SIZE + 1);
    err = ft_read(ft_i2c_bus, 0X8140, (uint8_t *)&cid, TOUCH_CID_SIZE);
    if (err < 0)
    {
        LOG_E("%s failed: %d", __func__, err);
        return RT_FALSE;
    }
    LOG_I("touch CID:0x%c%c%c%c", cid[0], cid[1], cid[2], cid[3]);

    /* FT6206 ID Value is 0x11
     * GT9147 ID will be 0x9147
     */
    if(rt_strncmp((char *)cid, "9147", TOUCH_CID_SIZE) == 0x0)
    {
        return RT_TRUE;
    }
    return RT_FALSE;
}

int ft_driver_register(void)
{
    /* TouchScreen FT6206 Slave I2C address is 0x54
     * 0x54 << 1 = 0x2A
     * 0x5D, 0x14  ------>   GT9147
     */
    ft_driver.address = 0x14;
    ft_driver.probe = ft_probe;
    ft_driver.ops = &ft_ops;
    ft_driver.user_data = RT_NULL;
    rt_touch_drivers_register(&ft_driver);
    return 0;
}
INIT_DEVICE_EXPORT(ft_driver_register);

#endif
