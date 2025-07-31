/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "drv_hw_i2c.h"

#ifdef RT_USING_I2C

#define LOG_TAG              "drv.hw_i2c"
#include <rtdbg.h>

#if !defined(BSP_USING_HW_I2C0) && !defined(BSP_USING_HW_I2C1)
#error "Please define at least one BSP_USING_HW_I2Cx in board.h"
#endif

static const struct gd32_i2c_config i2c_configs[] =
{
#ifdef BSP_USING_HW_I2C0
    {
        .i2c_periph = I2C0,
        .periph_clk = RCU_I2C0,

        .scl_clk = RCU_GPIOA,
        .scl_port = GPIOA,
        .scl_pin = GPIO_PIN_9,
        .scl_af = GPIO_AF_4,
        .sda_clk = RCU_GPIOA,
        .sda_port = GPIOA,
        .sda_pin = GPIO_PIN_10,
        .sda_af = GPIO_AF_4,

        .i2c_clock_hz = BSP_HW_I2C0_CLOCK_SPEED,
        .device_name = "i2c0",
    },
#endif
#ifdef BSP_USING_HW_I2C1
    {
        .i2c_periph = I2C1,
        .periph_clk = RCU_I2C1,

        .scl_clk = RCU_GPIOB,
        .scl_port = GPIOB,
        .scl_pin = GPIO_PIN_10,
        .scl_af = GPIO_AF_1,
        .sda_clk = RCU_GPIOB,
        .sda_port = GPIOB,
        .sda_pin = GPIO_PIN_11,
        .sda_af = GPIO_AF_1,
        .i2c_clock_hz = BSP_HW_I2C1_CLOCK_SPEED,
        .device_name = "i2c1",
    },
#endif
};

static struct gd32_i2c i2c_objs[sizeof(i2c_configs) / sizeof(i2c_configs[0])];

static rt_ssize_t gd32_i2c_master_xfer(struct rt_i2c_bus_device *bus,
                                       struct rt_i2c_msg msgs[],
                                       rt_uint32_t num)
{
    struct gd32_i2c *i2c_dev = rt_container_of(bus, struct gd32_i2c, parent);
    const struct gd32_i2c_config *config = i2c_dev->config;
    rt_uint32_t i2c_periph = config->i2c_periph;
    rt_uint32_t i;
    rt_err_t ret = RT_EOK;

    while (i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));

    for (i = 0; i < num; i++)
    {
        struct rt_i2c_msg *msg = &msgs[i];
        rt_uint16_t slave_addr = msg->addr;

        i2c_start_on_bus(i2c_periph);
        while (!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));

        if (msg->flags & RT_I2C_RD)
        {
            i2c_master_addressing(i2c_periph, slave_addr << 1, I2C_RECEIVER);
        }
        else
        {
            i2c_master_addressing(i2c_periph, slave_addr << 1, I2C_TRANSMITTER);
        }

        while (!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND));
        i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);

        if (msg->flags & RT_I2C_RD)
        {
            if (msg->len == 1)
            {
                i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
            }
            else
            {
                i2c_ack_config(i2c_periph, I2C_ACK_ENABLE);
            }

            for (rt_uint32_t j = 0; j < msg->len; j++)
            {
                if (j == msg->len - 1)
                {
                    i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
                }
                while (!i2c_flag_get(i2c_periph, I2C_FLAG_RBNE));
                msg->buf[j] = i2c_data_receive(i2c_periph);
            }
        }
        else
        {
            for (rt_uint32_t j = 0; j < msg->len; j++)
            {
                while (!i2c_flag_get(i2c_periph, I2C_FLAG_TBE));
                i2c_data_transmit(i2c_periph, msg->buf[j]);
            }
            while (!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
        }

        if (!(msg->flags & RT_I2C_NO_STOP))
        {
            i2c_stop_on_bus(i2c_periph);
            while(i2c_flag_get(i2c_periph, I2C_FLAG_STPDET));
        }
    }

    return (ret == RT_EOK) ? i : ret;
}


static const struct rt_i2c_bus_device_ops gd32_i2c_ops =
{
    .master_xfer = gd32_i2c_master_xfer,
    .slave_xfer  = RT_NULL,
    .i2c_bus_control = RT_NULL,
};

int rt_hw_i2c_init(void)
{
    rt_size_t obj_num = sizeof(i2c_objs) / sizeof(struct gd32_i2c);
    rt_err_t result;

    for (int i = 0; i < obj_num; i++)
    {
        struct gd32_i2c *i2c_obj = &i2c_objs[i];
        const struct gd32_i2c_config *config = &i2c_configs[i];

        i2c_obj->config = config;

        i2c_obj->i2c_clock_hz = config->i2c_clock_hz;

        rcu_periph_clock_enable(config->periph_clk);
        rcu_periph_clock_enable(config->scl_clk);
        rcu_periph_clock_enable(config->sda_clk);

        gpio_af_set(config->scl_port, config->scl_af, config->scl_pin);
        gpio_mode_set(config->scl_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, config->scl_pin);
        gpio_output_options_set(config->scl_port, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, config->scl_pin);

        gpio_af_set(config->sda_port, config->sda_af, config->sda_pin);
        gpio_mode_set(config->sda_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, config->sda_pin);
        gpio_output_options_set(config->sda_port, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ, config->sda_pin);

        i2c_deinit(config->i2c_periph);
        i2c_clock_config(config->i2c_periph, i2c_obj->i2c_clock_hz, I2C_DTCY_2);
        i2c_mode_addr_config(config->i2c_periph, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, 0x00);
        i2c_enable(config->i2c_periph);
        i2c_ack_config(config->i2c_periph, I2C_ACK_ENABLE);

        i2c_obj->parent.ops = &gd32_i2c_ops;
        result = rt_i2c_bus_device_register(&i2c_obj->parent, config->device_name);
        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init success, clock %dHz.", config->device_name, i2c_obj->i2c_clock_hz);
    }

    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif

