/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-08-21     heyuanjie87    first version
 * 2023-03-31     Vandoul        formatting code.
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "i2c.h"
#include "gpiohs.h"
#include "utils.h"
#include "sleep.h"
#include "fpioa.h"
#ifdef RT_USING_I2C

#ifndef BSP_I2C0_SCL_PIN
#define BSP_I2C0_SCL_PIN            0
#endif
#ifndef BSP_I2C0_SDA_PIN
#define BSP_I2C0_SDA_PIN            1
#endif
#ifndef BSP_I2C1_SCL_PIN
#define BSP_I2C1_SCL_PIN            30
#endif
#ifndef BSP_I2C1_SDA_PIN
#define BSP_I2C1_SDA_PIN            31
#endif
#ifndef BSP_I2C2_SCL_PIN
#define BSP_I2C2_SCL_PIN            4
#endif
#ifndef BSP_I2C2_SDA_PIN
#define BSP_I2C2_SDA_PIN            5
#endif

static rt_err_t ki2c_send(
    volatile i2c_t *i2c_adapter,
    rt_uint8_t *send_buf,
    rt_uint32_t send_buf_len)
{
    rt_uint32_t fifo_len, index;

    while (send_buf_len)
    {
        fifo_len = 8 - i2c_adapter->txflr;
        fifo_len = send_buf_len < fifo_len ? send_buf_len : fifo_len;
        for (index = 0; index < fifo_len; index++)
            i2c_adapter->data_cmd = I2C_DATA_CMD_DATA(*send_buf++);
        if (i2c_adapter->tx_abrt_source != 0)
        {
            while (i2c_adapter->status & I2C_STATUS_ACTIVITY);  //
            i2c_adapter->clr_intr = i2c_adapter->clr_intr;      //
            return -RT_ERROR;
        }

        send_buf_len -= fifo_len;
    }

    return RT_EOK;
}

static rt_err_t ki2c_recv(
    volatile i2c_t *i2c_adapter,
    rt_uint8_t *receive_buf,
    rt_uint32_t receive_buf_len)
{
    rt_uint32_t fifo_len, index;
    rt_uint32_t rx_len = receive_buf_len;

    while (receive_buf_len || rx_len)
    {
        fifo_len = i2c_adapter->rxflr;
        fifo_len = rx_len < fifo_len ? rx_len : fifo_len;
        for (index = 0; index < fifo_len; index++)
            *receive_buf++ = (rt_uint8_t)i2c_adapter->data_cmd;
        rx_len -= fifo_len;
        fifo_len = 8 - i2c_adapter->txflr;
        fifo_len = receive_buf_len < fifo_len ? receive_buf_len : fifo_len;
        for (index = 0; index < fifo_len; index++)
            i2c_adapter->data_cmd = I2C_DATA_CMD_CMD;
        if (i2c_adapter->tx_abrt_source != 0)
            return -RT_ERROR;
        receive_buf_len -= fifo_len;
    }

    return RT_EOK;
}

static void ki2c_setaddr(
    volatile i2c_t *i2c_adapter,
    rt_uint16_t addr,
    int width)
{
    i2c_adapter->tar = I2C_TAR_ADDRESS(addr) & I2C_TAR_ADDRESS_MASK;

    if(width == 10)
    {
        i2c_adapter->tar |= I2C_TAR_10BITADDR_MASTER;
    }
    else
    {
        i2c_adapter->tar &= ~I2C_TAR_10BITADDR_MASTER;
    }

}

static int ki2c_waittx(volatile i2c_t *i2c_adapter, int timeout_ms)
{
    rt_tick_t start;

    start = rt_tick_get();
    while ((i2c_adapter->status & I2C_STATUS_ACTIVITY) || !(i2c_adapter->status & I2C_STATUS_TFE))
    {
        if (rt_tick_from_millisecond(rt_tick_get() - start) > timeout_ms)
            break;
    }

    if (i2c_adapter->tx_abrt_source != 0)
        return -RT_ERROR;

    return RT_EOK;
}

static void ki2c_clearerr(volatile i2c_t *i2c_adapter)
{
    i2c_adapter->clr_tx_abrt = i2c_adapter->clr_tx_abrt;
}

static rt_ssize_t _i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                               struct rt_i2c_msg msgs[],
                               rt_uint32_t num)
{
    rt_ssize_t i;
    i2c_t *kbus = (i2c_t *)bus->priv;
    rt_err_t status;
    int waittx = 0;

    RT_ASSERT(bus != RT_NULL);
    if(msgs[0].flags & RT_I2C_ADDR_10BIT)
    {
        ki2c_setaddr(kbus, msgs[0].addr, 10);
    }
    else
    {
        ki2c_setaddr(kbus, msgs[0].addr, 7);
    }


    ki2c_clearerr(kbus);

    for (i = 0; i < num; i++)
    {
        waittx = 0;

        if (msgs[i].flags & RT_I2C_RD)
        {
            status = ki2c_recv(kbus, msgs[i].buf, msgs[i].len);
        }
        else
        {
            status = ki2c_send(kbus, msgs[i].buf, msgs[i].len);
            waittx = 1;
        }

        if (status != RT_EOK)
        {
            goto _out;
        }
    }

    if (waittx)
    {
        status = ki2c_waittx(kbus, 2000);
        if (status != RT_EOK)
        {
            goto _out;
        }
    }

    return i;
_out:
    return status;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    .master_xfer = _i2c_mst_xfer,
    .slave_xfer = RT_NULL,
    .i2c_bus_control = RT_NULL,
};

#ifdef RT_USING_I2C_BITOPS

typedef struct pin_info_s {
    uint32_t    scl;
    uint32_t    sda;
} pin_info_t;

static void set_sda(void *data, rt_int32_t state)
{
    pin_info_t  *pin = (pin_info_t *)data;
    /* state = 1: disable output. state = 0: enable output.*/
    set_gpio_bit(gpiohs->output_en.u32, pin->sda, !state);
}

static void set_scl(void *data, rt_int32_t state)
{
    pin_info_t  *pin = (pin_info_t *)data;
    /* state = 1: disable output. state = 0: enable output.*/
    set_gpio_bit(gpiohs->output_en.u32, pin->scl, !state);
}

static rt_int32_t get_sda(void *data)
{
    pin_info_t  *pin = (pin_info_t *)data;
    /* disable output.*/
    set_gpio_bit(gpiohs->output_en.u32, pin->sda, 0);

    return get_gpio_bit(gpiohs->input_val.u32, pin->sda);
}

static rt_int32_t get_scl(void *data)
{
    pin_info_t  *pin = (pin_info_t *)data;
    /* disable output.*/
    set_gpio_bit(gpiohs->output_en.u32, pin->scl, 0);

    return get_gpio_bit(gpiohs->input_val.u32, pin->scl);
}

static void udelay(rt_uint32_t us)
{
    usleep((uint64_t)us);
}

static struct rt_i2c_bit_ops bit_ops_0 =
{
    RT_NULL,
    set_sda,
    set_scl,
    get_sda,
    get_scl,
    udelay,
    5,
    5
};

static struct rt_i2c_bit_ops bit_ops_1 =
{
    RT_NULL,
    set_sda,
    set_scl,
    get_sda,
    get_scl,
    udelay,
    5,
    5
};

static struct rt_i2c_bit_ops bit_ops_2 =
{
    RT_NULL,
    set_sda,
    set_scl,
    get_sda,
    get_scl,
    udelay,
    5,
    5
};

extern int get_pin_channel(rt_base_t pin_index);
#endif

int rt_hw_i2c_init(void)
{
    struct  rt_i2c_bus_device *busdev;

#ifdef BSP_USING_I2C0
    static  struct rt_i2c_bus_device i2c_dev0;
    busdev = &i2c_dev0;

    #ifdef RT_USING_I2C_BITOPS
    fpioa_set_function(BSP_I2C0_SCL_PIN, FUNC_RESV0);
    fpioa_set_function(BSP_I2C0_SDA_PIN, FUNC_RESV0);

    rt_pin_write(BSP_I2C0_SCL_PIN, PIN_LOW);
    rt_pin_write(BSP_I2C0_SDA_PIN, PIN_LOW);
    rt_pin_mode(BSP_I2C0_SCL_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(BSP_I2C0_SDA_PIN, PIN_MODE_INPUT_PULLUP);

    static  pin_info_t  pin0;
    pin0.scl = get_pin_channel(BSP_I2C0_SCL_PIN);
    pin0.sda = get_pin_channel(BSP_I2C0_SDA_PIN);
    bit_ops_0.data = (void *)&pin0;

    busdev->priv = (void *)&bit_ops_0;
    rt_i2c_bit_add_bus(busdev, "i2c0");
    #else

    busdev->ops = &i2c_ops;
    busdev->priv = (void *)I2C0_BASE_ADDR;

    i2c_init(I2C_DEVICE_0, 0, 7, 100000);
    rt_i2c_bus_device_register(busdev, "i2c0");
    #endif
#endif

#ifdef BSP_USING_I2C1
    static  struct rt_i2c_bus_device i2c_dev1;
    busdev = &i2c_dev1;

    #ifdef RT_USING_I2C_BITOPS
    fpioa_set_function(BSP_I2C1_SCL_PIN, FUNC_RESV0);
    fpioa_set_function(BSP_I2C1_SDA_PIN, FUNC_RESV0);

    rt_pin_write(BSP_I2C1_SCL_PIN, PIN_LOW);
    rt_pin_write(BSP_I2C1_SDA_PIN, PIN_LOW);
    rt_pin_mode(BSP_I2C1_SCL_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(BSP_I2C1_SDA_PIN, PIN_MODE_INPUT_PULLUP);

    static  pin_info_t  pin1;
    pin1.scl = get_pin_channel(BSP_I2C1_SCL_PIN);
    pin1.sda = get_pin_channel(BSP_I2C1_SDA_PIN);
    bit_ops_1.data = (void *)&pin1;

    busdev->priv = (void *)&bit_ops_1;
    rt_i2c_bit_add_bus(busdev, "i2c1");
    #else

    busdev->ops = &i2c_ops;
    busdev->priv = (void *)I2C1_BASE_ADDR;

    i2c_init(I2C_DEVICE_1, 0, 7, 100000);
    rt_i2c_bus_device_register(busdev, "i2c1");
    #endif
#endif

#ifdef BSP_USING_I2C2
    static  struct rt_i2c_bus_device i2c_dev2;
    busdev = &i2c_dev2;

    #ifdef RT_USING_I2C_BITOPS
    fpioa_set_function(BSP_I2C2_SCL_PIN, FUNC_RESV0);
    fpioa_set_function(BSP_I2C2_SDA_PIN, FUNC_RESV0);

    rt_pin_write(BSP_I2C2_SCL_PIN, PIN_LOW);
    rt_pin_write(BSP_I2C2_SDA_PIN, PIN_LOW);
    rt_pin_mode(BSP_I2C2_SCL_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(BSP_I2C2_SDA_PIN, PIN_MODE_INPUT_PULLUP);

    static  pin_info_t  pin2;
    pin2.scl = get_pin_channel(BSP_I2C2_SCL_PIN);
    pin2.sda = get_pin_channel(BSP_I2C2_SDA_PIN);
    bit_ops_2.data = (void *)&pin2;

    busdev->priv = (void *)&bit_ops_2;
    rt_i2c_bit_add_bus(busdev, "i2c2");
    #else

    busdev->ops = &i2c_ops;
    busdev->priv = (void *)I2C2_BASE_ADDR;

    i2c_init(I2C_DEVICE_2, 0, 7, 100000);
    rt_i2c_bus_device_register(busdev, "i2c2");
    #endif
#endif
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);
#endif
