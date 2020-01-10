/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#include "drv_i2c.h"

#if defined (BSP_USING_I2C0)
#define I2C1BUS_NAME  "i2c0"
#endif /*BSP_USING_I2C0*/

#if defined (BSP_USING_I2C1)
#define I2C2BUS_NAME  "i2c1"
#endif /*BSP_USING_I2C1*/

static int i2c_byte_wait_us = 0;

#ifdef BSP_USING_I2C0

static struct raspi_i2c_bus raspi_i2c0 =
{
    .device_name = I2C1BUS_NAME,
};

static struct raspi_master_config_t raspi_i2c0_cfg =
{
    .sdl_pin = BCM_GPIO_PIN_0,
    .scl_pin = BCM_GPIO_PIN_1,
    .sdl_pin_mode = BCM283X_GPIO_FSEL_ALT0,
    .scl_pin_mode = BCM283X_GPIO_FSEL_ALT0,
    .slave_address = 8,
    .bsc_base = (PER_BASE + BCM283X_BSC0_BASE),
    .clk_div = BCM283X_I2C_CLOCK_DIVIDER_148,
};

#endif /* RT_USING_HW_I2C1 */

#ifdef BSP_USING_I2C1
static struct raspi_i2c_bus raspi_i2c1 =
{
    .device_name = I2C2BUS_NAME,
};

static struct raspi_master_config_t raspi_i2c1_cfg =
{
    .sdl_pin = BCM_GPIO_PIN_2,
    .scl_pin = BCM_GPIO_PIN_3,
    .sdl_pin_mode = BCM283X_GPIO_FSEL_ALT0,
    .scl_pin_mode = BCM283X_GPIO_FSEL_ALT0,
    .slave_address = 9,
    .bsc_base = (PER_BASE + BCM283X_BSC1_BASE),
    .clk_div = BCM283X_I2C_CLOCK_DIVIDER_148,
};
#endif /* RT_USING_HW_I2C2 */

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

void i2c_master_init(struct raspi_master_config_t *cfg)
{
    volatile rt_uint32_t addr;
    rt_uint32_t data;

    bcm283x_gpio_fsel(cfg->sdl_pin, cfg->sdl_pin_mode); /* SDA */
    bcm283x_gpio_fsel(cfg->scl_pin, cfg->scl_pin_mode); /* SCL */

    addr = cfg->bsc_base + BCM283X_BSC_DIV;
    data = bcm283x_peri_read(addr);
    i2c_byte_wait_us = ( data * 1000000 / BCM283X_CORE_CLK_HZ) * 9;

    addr = cfg->bsc_base + BCM283X_BSC_DIV;
    bcm283x_peri_write(addr, cfg->clk_div);

    //update
    i2c_byte_wait_us = (cfg->clk_div * 1000000 * 9 / BCM283X_CORE_CLK_HZ);
}

static rt_size_t raspi_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    volatile rt_uint32_t addr;
    struct raspi_i2c_bus *raspi_i2c;
    rt_size_t i;
    RT_ASSERT(bus != RT_NULL);
    raspi_i2c = (struct raspi_i2c_bus *) bus;
    raspi_i2c->msg = msgs;
    raspi_i2c->msg_ptr = 0;
    raspi_i2c->msg_cnt = num;
    raspi_i2c->dptr = 0;

    addr = raspi_i2c->cfg->bsc_base + BCM283X_BSC_A;
    bcm283x_peri_write(addr, msgs->addr);

    for (i = 0; i < num; i++)
    {
        if ( raspi_i2c->msg[i].flags & RT_I2C_RD )
        {
            bcm283x_i2c_read(raspi_i2c->cfg->bsc_base, raspi_i2c->msg->buf, num);
        }
        else
        {
            bcm283x_i2c_write(raspi_i2c->cfg->bsc_base, raspi_i2c->msg->buf, num);
        }
    }
    raspi_i2c->msg = RT_NULL;
    raspi_i2c->msg_ptr = 0;
    raspi_i2c->msg_cnt = 0;
    raspi_i2c->dptr = 0;
    return i;
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
    return RT_ERROR;
}

static const struct rt_i2c_bus_device_ops raspi_i2c_ops =
{
    .master_xfer = raspi_i2c_mst_xfer,
    .slave_xfer = raspi_i2c_slv_xfer,
    .i2c_bus_control = raspi_i2c_bus_control,
};

static rt_err_t raspi_i2c_configure(struct raspi_i2c_bus *bus, struct raspi_master_config_t *cfg)
{
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    bus->device.ops = &raspi_i2c_ops;
    bus->cfg = cfg;

    i2c_master_init(cfg);
    return RT_EOK;
}
#endif

int rt_hw_i2c_init(void)
{

#if defined(BSP_USING_I2C0)
    raspi_i2c_configure(&raspi_i2c0 , &raspi_i2c0_cfg);
    rt_i2c_bus_device_register(&raspi_i2c0.device, raspi_i2c0.device_name);
#endif  /* BSP_USING_I2C1 */

#if defined(BSP_USING_I2C1)

    raspi_i2c_configure(&raspi_i2c1 , &raspi_i2c1_cfg);
    rt_i2c_bus_device_register(&raspi_i2c1.device, raspi_i2c1.device_name);

#endif  /* BSP_USING_I2C2 */

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);
