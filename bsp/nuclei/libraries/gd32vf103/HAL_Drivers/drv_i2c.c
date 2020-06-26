/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-27     hqfang       first implementation.
 */

#include "drv_i2c.h"

#ifdef RT_USING_I2C

#if !defined(BSP_USING_I2C0) && !defined(BSP_USING_I2C1)
    #error "Please define at least one BSP_USING_I2Cx"
    /* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable I2C */
#endif

static struct gd32_i2c_config i2c_config[] =
{
#ifdef BSP_USING_I2C0
    {
        "i2c0",
        I2C0,
        100000,
    },
#endif
#ifdef BSP_USING_I2C1
    {
        "i2c1",
        I2C1,
        100000,
    },
#endif
};

static struct gd32_i2c i2c_obj[sizeof(i2c_config) / sizeof(i2c_config[0])] = {0};

#define GD32_I2C_TIMEOUT    10

static int gd32_i2c_read(rt_uint32_t i2c_periph, rt_uint16_t slave_address, rt_uint8_t *p_buffer, rt_uint16_t cnt)
{
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, slave_address << 1, I2C_RECEIVER);

    /* wait until ADDSEND bit is set */
    while (!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND));

    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);

    /* while there is data to be read */
    while (cnt)
    {
        if (cnt == 1)
        {
            // Send NACK for last 1 byte receive
            i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
        }
        /* wait until the RBNE bit is set */
        while (i2c_flag_get(i2c_periph, I2C_FLAG_RBNE) == RESET);

        /* read a byte from i2c */
        *p_buffer = i2c_data_receive(i2c_periph);

        /* point to the next location where the byte read will be saved */
        p_buffer++;

        /* decrement the read bytes counter */
        cnt--;
    }

    return 0;
}

static int gd32_i2c_write(rt_uint32_t i2c_periph, uint16_t slave_address, uint8_t *p_buffer, uint16_t cnt)
{
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, slave_address << 1, I2C_TRANSMITTER);

    /* wait until ADDSEND bit is set */
    while (!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND));

    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);

    /* wait until the transmit data buffer is empty */
    while (SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE));

    /* while there is data to be read */
    while (cnt)
    {
        i2c_data_transmit(i2c_periph, *p_buffer);

        /* point to the next byte to be written */
        p_buffer++;

        /* decrement the write bytes counter */
        cnt--;

        /* wait until BTC bit is set */
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
    }

    return 0;
}

static void gd32_i2c_configure(struct gd32_i2c_config *i2c_cfg)
{
    RT_ASSERT(i2c_cfg != RT_NULL);

    /* configure i2c speed to 100Khz */
    i2c_clock_config(i2c_cfg->i2c_periph, i2c_cfg->speed, I2C_DTCY_2);
    /* enable I2C */
    i2c_enable(i2c_cfg->i2c_periph);
    /* enable acknowledge */
    i2c_ack_config(i2c_cfg->i2c_periph, I2C_ACK_ENABLE);
}


static rt_size_t gd32_i2c_xfer(struct rt_i2c_bus_device *device, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_err_t ret = RT_ERROR;
    rt_uint16_t last_flags;

    RT_ASSERT(device != RT_NULL);

    struct gd32_i2c *i2c_obj = (struct gd32_i2c *)(device);
    struct gd32_i2c_config *i2c_cfg = (struct gd32_i2c_config *)(i2c_obj->config);
    RT_ASSERT(i2c_cfg != RT_NULL);

    /* wait until I2C bus is idle */
    while (i2c_flag_get(i2c_cfg->i2c_periph, I2C_FLAG_I2CBSY));

    if (num)
    {
        if (msg[0].flags & RT_I2C_ADDR_10BIT)
        {
            i2c_mode_addr_config(i2c_cfg->i2c_periph, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_10BITS, 0x82);
        }
        else
        {
            i2c_mode_addr_config(i2c_cfg->i2c_periph, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, 0x82);
        }
    }
    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (!(msg->flags & RT_I2C_NO_START))
        {
            /* send a start condition to I2C bus */
            i2c_start_on_bus(i2c_cfg->i2c_periph);
            /* wait until SBSEND bit is set */
            while (!i2c_flag_get(i2c_cfg->i2c_periph, I2C_FLAG_SBSEND));
        }

        if (msg->flags & RT_I2C_RD)
        {
            gd32_i2c_read(i2c_cfg->i2c_periph, msg->addr, msg->buf, msg->len);
        }
        else
        {
            gd32_i2c_write(i2c_cfg->i2c_periph, msg->addr, msg->buf, msg->len);
        }
    }

    if (num)
    {
        /* send a stop condition to I2C bus */
        i2c_stop_on_bus(i2c_cfg->i2c_periph);

        /* wait until the stop condition is finished */
        while (I2C_CTL0(i2c_cfg->i2c_periph) & I2C_CTL0_STOP);
    }
    i2c_ack_config(i2c_cfg->i2c_periph, I2C_ACK_ENABLE);

    ret = i;

    return ret;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    gd32_i2c_xfer,
    RT_NULL,
    RT_NULL
};

int rt_hw_i2c_init(void)
{
    rt_size_t obj_num;
    int index;
    rt_err_t result = 0;

#ifdef BSP_USING_I2C0
    rcu_periph_clock_enable(RCU_I2C0);
#endif
#ifdef BSP_USING_I2C1
    rcu_periph_clock_enable(RCU_I2C1);
#endif

    obj_num = sizeof(i2c_obj) / sizeof(struct gd32_i2c);
    for (index = 0; index < obj_num; index++)
    {
        /* init i2c object */
        i2c_obj[index].config = &i2c_config[index];
        i2c_obj[index].bus.ops = &i2c_ops;

        /* init i2c device */
        gd32_i2c_configure(&i2c_config[index]);

        /* register i2c device */
        result = rt_i2c_bus_device_register(&i2c_obj[index].bus,
                                            i2c_obj[index].config->name
                                           );
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif
/* end of i2c driver */
