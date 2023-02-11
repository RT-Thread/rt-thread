/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-11-28     bigmagic       first version
 */

#include "drv_i2c.h"
#include "drv_gpio.h"
#include "raspi4.h"
#include "mbox.h"

/*
* (3.3v)          -1   2-
* (SDA1/SDA3)     -3   4-
* (SCL1/SCL3)     -5   6-
* (SDA3)          -7   8-
*                 -9  10-
*                 -11 12-
*                 -13 14-
*                 -15 16-
*                 -17 18-
*                 -19 20-
* (SCL4)          -21 22-
*                 -23 24-    (SDA4)
*                 -25 26-    (SCL4)
*                 -27 28-
* (SCL3)          -29 30-
* (SDA4)          -31 32-
*/

#define DBG_TAG               "drv.i2c"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

struct raspi_i2c_hw_config
{
    rt_uint32_t bsc_num;
    rt_uint32_t bsc_rate;
    rt_uint32_t bsc_address;
    rt_uint32_t sda_pin;
    rt_uint32_t scl_pin;
    rt_uint32_t sda_mode;
    rt_uint32_t scl_mode;
};

rt_uint8_t i2c_read_or_write(volatile rt_uint32_t base, rt_uint8_t* buf, rt_uint32_t len, rt_uint8_t flag)
{
    rt_uint32_t status;
    rt_uint32_t remaining = len;
    rt_uint32_t i = 0;
    rt_uint8_t reason = I2C_REASON_OK;

    /* Clear FIFO */
    BSC_C(base) |= (BSC_C_CLEAR_1 & BSC_C_CLEAR_1);
    /* Clear Status */
    BSC_S(base) = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE;
    /* Set Data Length */
    BSC_DLEN(base) = len;
    if (flag)
    {
        /* Start read */
        BSC_C(base) = BSC_C_I2CEN | BSC_C_ST | BSC_C_READ;
        /* wait for transfer to complete */
        while (!(BSC_S(base) & BSC_S_DONE))
        {
            /* we must empty the FIFO as it is populated and not use any delay */
            while (remaining && (BSC_S(base) & BSC_S_RXD))
            {
                /* Read from FIFO, no barrier */
                buf[i] = BSC_FIFO(base);
                i++;
                remaining--;
            }
        }
        /* transfer has finished - grab any remaining stuff in FIFO */
        while (remaining && (BSC_S(base) & BSC_S_RXD))
        {
            /* Read from FIFO, no barrier */
            buf[i] = BSC_FIFO(base);
            i++;
            remaining--;
        }
    }
    else
    {
        LOG_D("i2c%d write start", flag);
        /* pre populate FIFO with max buffer */
        while (remaining && (i < BSC_FIFO_SIZE))
        {
            BSC_FIFO(base) = buf[i];
            i++;
            remaining--;
        }

        /* Enable device and start transfer */
        BSC_C(base) = BSC_C_I2CEN | BSC_C_ST;

        /* Transfer is over when BCM2835_BSC_S_DONE */
        while (!(BSC_S(base) & BSC_S_DONE))
        {
            while (remaining && (BSC_S(base) & BSC_S_TXD))
            {
                /* Write to FIFO */
                BSC_FIFO(base) = buf[i];
                i++;
                remaining--;
            }
        }
        LOG_D("i2c%d write end", flag);
    }

    status = BSC_S(base);
    if (status & BSC_S_ERR)
    {
        reason = I2C_REASON_ERROR_NACK;
    }
    else if (status & BSC_S_CLKT)
    {
        reason = I2C_REASON_ERROR_CLKT;
    }
    else if (remaining)
    {
        reason = I2C_REASON_ERROR_DATA;
    }
    BSC_C(base) |= (BSC_S_DONE & BSC_S_DONE);

    return reason;
}

static rt_ssize_t raspi_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    rt_size_t i;
    rt_uint8_t reason;
    RT_ASSERT(bus != RT_NULL);

    struct raspi_i2c_hw_config *i2c_hw_config = (struct raspi_i2c_hw_config*)(bus->priv);

    //Slave Address
    BSC_A(i2c_hw_config->bsc_address) = msgs->addr;

    for (i = 0; i < num; i++)
    {
        if (msgs[i].flags & RT_I2C_RD)
            reason = i2c_read_or_write(i2c_hw_config->bsc_address, msgs->buf, msgs->len, 1);
        else
            reason = i2c_read_or_write(i2c_hw_config->bsc_address, msgs->buf, msgs->len, 0);
    }
    return (reason == 0)? i : 0;
}

static rt_ssize_t raspi_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
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


static rt_err_t raspi_i2c_configure(struct raspi_i2c_hw_config *cfg)
{
    RT_ASSERT(cfg != RT_NULL);
    rt_uint32_t apb_clock = 0;
    prev_raspi_pin_mode(cfg->sda_pin, cfg->sda_mode);//sda
    prev_raspi_pin_mode(cfg->scl_pin, cfg->scl_mode);//scl
    /* use 0xFFFE mask to limit a max value and round down any odd number */
    apb_clock = bcm271x_mbox_clock_get_rate(CORE_CLK_ID);
    rt_uint32_t divider = (apb_clock / cfg->bsc_rate) & 0xFFFE;

    BSC_DIV(cfg->bsc_address) = (rt_uint16_t)divider;

    return RT_EOK;
}

static const struct rt_i2c_bus_device_ops raspi_i2c_ops =
{
    .master_xfer = raspi_i2c_mst_xfer,
    .slave_xfer = raspi_i2c_slv_xfer,
    .i2c_bus_control = raspi_i2c_bus_control,
};

#if defined (BSP_USING_I2C0)
#define I2C0_BUS_NAME    "i2c0"
static struct raspi_i2c_hw_config hw_device0 =
{
    .bsc_num = 0,
    .bsc_rate = 100000,//100k
    .bsc_address = BSC0_BASE,
    .sda_pin = GPIO_PIN_0,
    .scl_pin = GPIO_PIN_1,
    .sda_mode = ALT0,
    .scl_mode = ALT0,
};

struct rt_i2c_bus_device device0 =
{
    .ops = &raspi_i2c_ops,
    .priv =  (void *)&hw_device0,
};
#endif

#if defined (BSP_USING_I2C1)
#define I2C1_BUS_NAME    "i2c1"
static struct raspi_i2c_hw_config hw_device1 =
{
    .bsc_num = 1,
    .bsc_rate = 100000,//100k
    .bsc_address = BSC1_BASE,
    .sda_pin = GPIO_PIN_2,
    .scl_pin = GPIO_PIN_3,
    .sda_mode = ALT0,
    .scl_mode = ALT0,
};

struct rt_i2c_bus_device device1 =
{
    .ops = &raspi_i2c_ops,
    .priv =  (void *)&hw_device1,
};
#endif

#if defined (BSP_USING_I2C3)
#define I2C3_BUS_NAME    "i2c3"
static struct raspi_i2c_hw_config hw_device3 =
{
    .bsc_num = 3,
    .bsc_rate = 100000,//100k
    .bsc_address = BSC3_BASE,
#ifndef BSP_USING_I2C3_0
    .sda_pin = GPIO_PIN_2,
    .scl_pin = GPIO_PIN_3,
#else
    .sda_pin = GPIO_PIN_4,
    .scl_pin = GPIO_PIN_5,
#endif
    .sda_mode = ALT5,
    .scl_mode = ALT5,
};

struct rt_i2c_bus_device device3 =
{
    .ops = &raspi_i2c_ops,
    .priv =  (void *)&hw_device3,
};
#endif

#if defined (BSP_USING_I2C4)
#define I2C4_BUS_NAME    "i2c4"
static struct raspi_i2c_hw_config hw_device4 =
{
    .bsc_num = 4,
    .bsc_rate = 100000,//100k
    .bsc_address = BSC4_BASE,
#ifdef BSP_USING_I2C4_0
    .sda_pin = GPIO_PIN_6,
    .scl_pin = GPIO_PIN_7,
#else
    .sda_pin = GPIO_PIN_8,
    .scl_pin = GPIO_PIN_9,
#endif
    .sda_mode = ALT5,
    .scl_mode = ALT5,
};

struct rt_i2c_bus_device device4 =
{
    .ops = &raspi_i2c_ops,
    .priv =  (void *)&hw_device4,
};
#endif

#if defined (BSP_USING_I2C5)
#define I2C5_BUS_NAME    "i2c5"
static struct raspi_i2c_hw_config hw_device5 =
{
    .bsc_num = 5,
    .bsc_rate = 100000,//100k
    .bsc_address = BSC5_BASE,
#ifdef BSP_USING_I2C5_0
    .sda_pin = GPIO_PIN_10,
    .scl_pin = GPIO_PIN_11,
#else
    .sda_pin = GPIO_PIN_12,
    .scl_pin = GPIO_PIN_13,
#endif
    .sda_mode = ALT5,
    .scl_mode = ALT5,
};

struct rt_i2c_bus_device device5 =
{
    .ops = &raspi_i2c_ops,
    .priv =  (void *)&hw_device5,
};
#endif

#if defined (BSP_USING_I2C6)
#define I2C6_BUS_NAME    "i2c6"
static struct raspi_i2c_hw_config hw_device6 =
{
    .bsc_num = 6,
    .bsc_rate = 100000,//100k
    .bsc_address = BSC6_BASE,
#ifdef BSP_USING_I2C5_0
    .sda_pin = GPIO_PIN_0,
    .scl_pin = GPIO_PIN_1,
#else
    .sda_pin = GPIO_PIN_22,
    .scl_pin = GPIO_PIN_23,
#endif
    .sda_mode = ALT5,
    .scl_mode = ALT5,
};

struct rt_i2c_bus_device device6 =
{
    .ops = &raspi_i2c_ops,
    .priv =  (void *)&hw_device6,
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

#if defined(BSP_USING_I2C3)
    raspi_i2c_configure(&hw_device3);
    rt_i2c_bus_device_register(&device3, I2C3_BUS_NAME);
#endif

#if defined(BSP_USING_I2C4)
    raspi_i2c_configure(&hw_device4);
    rt_i2c_bus_device_register(&device4, I2C4_BUS_NAME);
#endif

#if defined(BSP_USING_I2C5)
    raspi_i2c_configure(&hw_device5);
    rt_i2c_bus_device_register(&device5, I2C5_BUS_NAME);
#endif

#if defined(BSP_USING_I2C6)
    raspi_i2c_configure(&hw_device6);
    rt_i2c_bus_device_register(&device6, I2C6_BUS_NAME);
#endif
    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_i2c_init);
