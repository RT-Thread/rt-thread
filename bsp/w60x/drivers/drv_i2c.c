/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-9      fanwenl      1st version
 */

#include <rtdevice.h>
#include <rtthread.h>
#include "board.h"
#include "wm_i2c.h"
#include "wm_io.h"
#include "wm_gpio_afsel.h"
#include "pin_map.h"
#include "drv_i2c.h"

#ifdef BSP_USING_I2C

struct wm_i2c_bus
{
    struct rt_i2c_bus_device parent;
    struct rt_i2c_msg *msg;
    rt_uint32_t msg_cnt;
    volatile rt_uint32_t msg_ptr;
    volatile rt_uint32_t dptr;
};

static struct wm_i2c_bus wm_i2c;

static rt_ssize_t wm_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg msgs[],
                                 rt_uint32_t num);
static rt_ssize_t wm_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg msgs[],
                                 rt_uint32_t num);
static rt_err_t wm_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                   int cmd,
                                   void *args);

static const struct rt_i2c_bus_device_ops wm_i2c_ops =
{
    wm_i2c_mst_xfer,
    wm_i2c_slv_xfer,
    wm_i2c_bus_control,
};

static rt_err_t wm_i2c_send_address(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg *msg)
{
    uint8_t addr_msb, addr_lsb;

    if (msg->flags & RT_I2C_ADDR_10BIT)
    {
        addr_msb = 0xf0 | ((msg->addr >> 7) & 0x06);
        addr_lsb = msg->addr & 0xff;

        if (msg->flags & RT_I2C_RD)
        {
            addr_msb |= 0x01;
        }
        tls_i2c_write_byte(addr_msb, 1);
        tls_i2c_wait_ack();
        tls_i2c_write_byte(addr_lsb, 0);
        tls_i2c_wait_ack();
    }
    else
    {
        tls_i2c_write_byte((msg->addr << 1) | msg->flags, 1);
        tls_i2c_wait_ack();
    }

    return RT_EOK;
}

static rt_ssize_t wm_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg msgs[],
                                 rt_uint32_t num)
{
    struct wm_i2c_bus *wm_i2c;
    rt_size_t i;
    RT_ASSERT(bus != RT_NULL);
    wm_i2c = (struct wm_i2c_bus *)bus;

    wm_i2c->msg = msgs;
    wm_i2c->msg_ptr = 0;
    wm_i2c->msg_cnt = num;
    wm_i2c->dptr = 0;

    for (i = 0; i < wm_i2c->msg_cnt; i++)
    {
        if (!(wm_i2c->msg[i].flags & RT_I2C_NO_START))
        {
            wm_i2c_send_address(bus, &(wm_i2c->msg[i]));
        }
        if (wm_i2c->msg[i].flags & RT_I2C_RD)
        {
            while (wm_i2c->msg[i].len > 1)
            {
                *wm_i2c->msg[i].buf++ = tls_i2c_read_byte(1, 0);
                wm_i2c->msg[i].len--;
            }
            *wm_i2c->msg[i].buf = tls_i2c_read_byte(0, 0);
        }
        else
        {
            while (wm_i2c->msg[i].len > 0)
            {
                tls_i2c_write_byte(*wm_i2c->msg[i].buf, 0);
                tls_i2c_wait_ack();
                wm_i2c->msg[i].len--;
                wm_i2c->msg[i].buf++;
            }
        }
    }
    wm_i2c->msg = RT_NULL;
    wm_i2c->msg_ptr = 0;
    wm_i2c->msg_cnt = 0;
    wm_i2c->dptr = 0;

    tls_i2c_stop();
    for (int j = 0; j < 3000; j++);

    return i;
}
static rt_ssize_t wm_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg msgs[],
                                 rt_uint32_t num)
{
    return 0;
}
static rt_err_t wm_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                   int cmd,
                                   void *args)
{
    return -RT_ERROR;
}

void WM_I2C_IRQHandler(void)
{
    extern void I2C_IRQHandler(void);
    /* enter interrupt */
    rt_interrupt_enter();

    I2C_IRQHandler();

    /* leave interrupt */
    rt_interrupt_leave();
}

int wm_hw_i2c_init(void)
{
    rt_int16_t gpio_pin;

    gpio_pin = wm_get_pin(WM_I2C_SCL_PIN);
    if (gpio_pin >= 0)
    {
        wm_i2c_scl_config((enum tls_io_name)gpio_pin);
    }
    gpio_pin = wm_get_pin(WM_I2C_DAT_PIN);
    if (gpio_pin >= 0)
    {
        wm_i2c_sda_config((enum tls_io_name)gpio_pin);
    }

    tls_i2c_init(WM_HW_I2C_FREQ);

    wm_i2c.parent.ops = &wm_i2c_ops;
#ifdef WM_I2C_BUS_NAME
    rt_i2c_bus_device_register(&wm_i2c.parent, WM_I2C_BUS_NAME);
#else
    rt_i2c_bus_device_register(&wm_i2c.parent, "i2c");
#endif

    return 0;
}
INIT_DEVICE_EXPORT(wm_hw_i2c_init);

#endif /* BSP_USING_I2C */
