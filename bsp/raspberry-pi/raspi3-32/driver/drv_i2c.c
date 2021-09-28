/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#include "drv_i2c.h"

//Maybe redefined
typedef unsigned long                   rt_ubase_t;
typedef rt_ubase_t                      rt_size_t;

rt_uint8_t i2c_read_or_write(volatile rt_uint32_t base, rt_uint8_t* buf, rt_uint32_t len, rt_uint8_t flag)
{
    rt_uint32_t status;
    rt_uint32_t remaining = len;
    rt_uint32_t i = 0;
    rt_uint8_t reason = BCM283X_I2C_REASON_OK;

    /* Clear FIFO */
    BCM283X_BSC_C(base) |= (BSC_C_CLEAR_1 & BSC_C_CLEAR_1);
    /* Clear Status */
    BCM283X_BSC_S(base) = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE;
    /* Set Data Length */
    BCM283X_BSC_DLEN(base) = len;
    if (flag)
    {
        /* Start read */
        BCM283X_BSC_C(base) = BSC_C_I2CEN | BSC_C_ST | BSC_C_READ;
        /* wait for transfer to complete */
        while (!(BCM283X_BSC_S(base) & BSC_S_DONE))
        {
            /* we must empty the FIFO as it is populated and not use any delay */
            while (remaining && (BCM283X_BSC_S(base) & BSC_S_RXD))
            {
                /* Read from FIFO, no barrier */
                buf[i] = BCM283X_BSC_FIFO(base);
                i++;
                remaining--;
            }
        }
        /* transfer has finished - grab any remaining stuff in FIFO */
        while (remaining && (BCM283X_BSC_S(base) & BSC_S_RXD))
        {
            /* Read from FIFO, no barrier */
            buf[i] = BCM283X_BSC_FIFO(base);
            i++;
            remaining--;
        }
    }
    else
    {
        /* pre populate FIFO with max buffer */
        while (remaining && (i < BSC_FIFO_SIZE))
        {
            BCM283X_BSC_FIFO(base) = buf[i];
            i++;
            remaining--;
        }

        /* Enable device and start transfer */
        BCM283X_BSC_C(base) = BSC_C_I2CEN | BSC_C_ST;

        /* Transfer is over when BCM2835_BSC_S_DONE */
        while (!(BCM283X_BSC_S(base) & BSC_S_DONE))
        {
            while (remaining && (BCM283X_BSC_S(base) & BSC_S_TXD))
            {
                /* Write to FIFO */
                BCM283X_BSC_FIFO(base) = buf[i];
                i++;
                remaining--;
            }
        }
    }

    status = BCM283X_BSC_S(base);
    if (status & BSC_S_ERR)
    {
        reason = BCM283X_I2C_REASON_ERROR_NACK;
    }
    else if (status & BSC_S_CLKT)
    {
        reason = BCM283X_I2C_REASON_ERROR_CLKT;
    }
    else if (remaining)
    {
        reason = BCM283X_I2C_REASON_ERROR_DATA;
    }
    BCM283X_BSC_C(base) |= (BSC_S_DONE & BSC_S_DONE);

    return reason;
}

struct raspi_i2c_hw_config
{
    rt_uint8_t bsc_num;
    rt_uint8_t sdl_pin;
    rt_uint8_t scl_pin;
    rt_uint8_t sdl_mode;
    rt_uint8_t scl_mode;
};

#if (defined(BSP_USING_I2C0) || defined(BSP_USING_I2C1))

static rt_size_t raspi_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num);
static rt_size_t raspi_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num);
static rt_err_t raspi_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                      rt_uint32_t,
                                      rt_uint32_t);

static rt_uint32_t i2c_byte_wait_us = 0;
static rt_size_t raspi_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    rt_size_t i;
    rt_uint8_t reason;
    RT_ASSERT(bus != RT_NULL);

    volatile rt_uint32_t base = (volatile rt_uint32_t)(bus->parent.user_data);

    if (bus->addr == 0)
        base = BCM283X_BSC0_BASE;
    else
        base = BCM283X_BSC1_BASE;

    BCM283X_BSC_A(base) = msgs->addr;

    for (i = 0; i < num; i++)
    {
        if (msgs[i].flags & RT_I2C_RD)
            reason = i2c_read_or_write(base, msgs->buf, msgs->len, 1);
        else
            reason = i2c_read_or_write(base, msgs->buf, msgs->len, 0);
    }
    return (reason == 0)? i : 0;
}

static rt_size_t raspi_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    return 0;
}
static rt_err_t raspi_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                      rt_uint32_t cmd,
                                      rt_uint32_t arg)
{
    return RT_EOK;
}

static const struct rt_i2c_bus_device_ops raspi_i2c_ops =
{
    .master_xfer = raspi_i2c_mst_xfer,
    .slave_xfer = raspi_i2c_slv_xfer,
    .i2c_bus_control = raspi_i2c_bus_control,
};


static rt_err_t raspi_i2c_configure(struct raspi_i2c_hw_config *cfg)
{
    RT_ASSERT(cfg != RT_NULL);

    volatile rt_uint32_t base = cfg->scl_mode ? BCM283X_BSC1_BASE : BCM283X_BSC0_BASE;

    GPIO_FSEL(cfg->sdl_pin, cfg->sdl_mode); /* SDA */
    GPIO_FSEL(cfg->scl_pin, cfg->scl_mode); /* SCL */

    /* use 0xFFFE mask to limit a max value and round down any odd number */
    rt_uint32_t divider = (BCM283X_CORE_CLK_HZ / 10000) & 0xFFFE;
    BCM283X_BSC_DIV(base) = (rt_uint16_t) divider;
    i2c_byte_wait_us = (divider * 1000000 * 9 / BCM283X_CORE_CLK_HZ);

    return RT_EOK;
}
#endif

#if defined (BSP_USING_I2C0)
#define I2C0_BUS_NAME    "i2c0"
static struct raspi_i2c_hw_config hw_device0 =
{
    .bsc_num = 0,
    .sdl_pin = RPI_GPIO_P1_27,
    .scl_pin = RPI_GPIO_P1_28,
    .sdl_mode = BCM283X_GPIO_FSEL_ALT0,
    .scl_mode = BCM283X_GPIO_FSEL_ALT0,
};

struct rt_i2c_bus_device device0 =
{
    .ops = &raspi_i2c_ops,
    .addr = 0,
};

#endif

#if defined (BSP_USING_I2C1)
#define I2C1_BUS_NAME    "i2c1"
static struct raspi_i2c_hw_config hw_device1 =
{
    .bsc_num = 1,
    .sdl_pin = RPI_GPIO_P1_03,
    .scl_pin = RPI_GPIO_P1_05,
    .sdl_mode = BCM283X_GPIO_FSEL_ALT0,
    .scl_mode = BCM283X_GPIO_FSEL_ALT0,
};
struct rt_i2c_bus_device device1 =
{
    .ops = &raspi_i2c_ops,
    .addr = 1,
};

#endif

int rt_hw_i2c_init(void)
{
#if defined(BSP_USING_I2C0)
    raspi_i2c_configure(&hw_device0);
    rt_i2c_bus_device_register(&device0, I2C0_BUS_NAME);
#endif

#if defined(BSP_USING_I2C1)
    raspi_i2c_configure(&hw_device1);
    rt_i2c_bus_device_register(&device1, I2C1_BUS_NAME);
#endif

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);
