/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-04     Haley        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "am_mcu_apollo.h"

/* I2C0 */
#define AM_I2C0_IOM_INST    0

#define I2C0_GPIO_SCL       5
#define I2C0_GPIO_CFG_SCK   AM_HAL_PIN_5_M0SCL
#define I2C0_GPIO_SDA       6
#define I2C0_GPIO_CFG_SDA   AM_HAL_PIN_6_M0SDA

/* I2C2 */
#define AM_I2C2_IOM_INST    2

#define I2C2_GPIO_SCL       27
#define I2C2_GPIO_CFG_SCK   AM_HAL_PIN_27_M2SCL
#define I2C2_GPIO_SDA       25
#define I2C2_GPIO_CFG_SDA   AM_HAL_PIN_25_M2SDA

/* I2C3 */
#define AM_I2C3_IOM_INST    3

#define I2C3_GPIO_SCL       42
#define I2C3_GPIO_CFG_SCK   AM_HAL_PIN_42_M3SCL
#define I2C3_GPIO_SDA       43
#define I2C3_GPIO_CFG_SDA   AM_HAL_PIN_43_M3SDA

/* I2C4 */
#define AM_I2C4_IOM_INST    4

#define I2C4_GPIO_SCL       39
#define I2C4_GPIO_CFG_SCK   AM_HAL_PIN_39_M4SCL
#define I2C4_GPIO_SDA       40
#define I2C4_GPIO_CFG_SDA   AM_HAL_PIN_40_M4SDA

static am_hal_iom_config_t g_sIOMConfig =
{
    AM_HAL_IOM_I2CMODE, // ui32InterfaceMode
    AM_HAL_IOM_100KHZ, // ui32ClockFrequency
    0, // bSPHA
    0, // bSPOL
    4, // ui8WriteThreshold
    60, // ui8ReadThreshold
};

/* AM i2c driver */
struct am_i2c_bus
{
    struct rt_i2c_bus_device parent;
    rt_uint32_t u32Module;
};

//connect am drv to rt drv.
rt_size_t rt_i2c_master_xfer(struct rt_i2c_bus_device *bus,
                          struct rt_i2c_msg         *msgs,
                          rt_uint32_t               num)
{
    struct am_i2c_bus * am_i2c_bus = (struct am_i2c_bus *)bus;
    struct rt_i2c_msg *msg;
    int i;
    rt_uint32_t msg_len = 0;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        if (msg->flags == RT_I2C_RD)
        {
            am_hal_iom_i2c_read(am_i2c_bus->u32Module, msg->addr, (uint32_t *)msg->buf, msg->len, AM_HAL_IOM_RAW);
            msg_len += msg->len;
        }
        else if(msg->flags == RT_I2C_WR)
        {
            am_hal_iom_i2c_write(am_i2c_bus->u32Module, msg->addr, (uint32_t *)msg->buf, msg->len, AM_HAL_IOM_RAW);
            msg_len += (msg->len - 1);
        }
    }

    return msg_len;
}

rt_err_t rt_i2c_bus_control(struct rt_i2c_bus_device *bus,
                          int                cmd,
                          void               *args)
{
    struct am_i2c_bus * am_i2c_bus = (struct am_i2c_bus *)bus;
    //rt_uint32_t ctrl_arg = *(rt_uint32_t *)args;

    RT_ASSERT(bus != RT_NULL);
    am_i2c_bus = (struct am_i2c_bus *)bus->parent.user_data;

    RT_ASSERT(am_i2c_bus != RT_NULL);

    switch (cmd)
    {
        /* I2C config */
        case RT_DEVICE_CTRL_CONFIG :
            break;
    }

    return RT_EOK;
}

static const struct rt_i2c_bus_device_ops am_i2c_ops =
{
    rt_i2c_master_xfer,
    RT_NULL,
    rt_i2c_bus_control
};

#ifdef RT_USING_I2C0
static struct am_i2c_bus am_i2c_bus_0 =
{
    {0},
    AM_I2C0_IOM_INST
};
#endif

#ifdef RT_USING_I2C1
static struct am_i2c_bus am_i2c_bus_1 =
{
    {1},
    AM_I2C1_IOM_INST
};
#endif

#ifdef RT_USING_I2C2
static struct am_i2c_bus am_i2c_bus_2 =
{
    {2},
    AM_I2C2_IOM_INST
};
#endif

#ifdef RT_USING_I2C3
static struct am_i2c_bus am_i2c_bus_3 =
{
    {3},
    AM_I2C3_IOM_INST
};
#endif

#ifdef RT_USING_I2C4
static struct am_i2c_bus am_i2c_bus_4 =
{
    {4},
    AM_I2C4_IOM_INST
};
#endif

int rt_i2c_init(void)
{
    struct am_i2c_bus* am_i2c;

#ifdef RT_USING_I2C0
    /* init i2c gpio */
    am_hal_gpio_pin_config(I2C0_GPIO_SCL, I2C0_GPIO_CFG_SCK | AM_HAL_GPIO_PULL6K);
    am_hal_gpio_pin_config(I2C0_GPIO_SDA, I2C0_GPIO_CFG_SDA | AM_HAL_GPIO_PULL6K);

    /* Initialize IOM 0 in I2C mode at 100KHz */
    am_hal_iom_pwrctrl_enable(AM_I2C0_IOM_INST);
    g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_100KHZ;
    am_hal_iom_config(AM_I2C0_IOM_INST, &g_sIOMConfig);
    am_hal_iom_enable(AM_I2C0_IOM_INST);

    /* init i2c bus device */
    am_i2c = &am_i2c_bus_0;
    am_i2c->parent.ops = &am_i2c_ops;
    rt_i2c_bus_device_register(&am_i2c->parent, "i2c0");
#endif

#ifdef RT_USING_I2C2
    /* init i2c gpio */
    am_hal_gpio_pin_config(I2C2_GPIO_SCL, I2C2_GPIO_CFG_SCK | AM_HAL_GPIO_PULL6K);
    am_hal_gpio_pin_config(I2C2_GPIO_SDA, I2C2_GPIO_CFG_SDA | AM_HAL_GPIO_PULL6K);

    /* Initialize IOM 2 in I2C mode at 400KHz */
    am_hal_iom_pwrctrl_enable(AM_I2C2_IOM_INST);
    g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_400KHZ;
    am_hal_iom_config(AM_I2C2_IOM_INST, &g_sIOMConfig);
    am_hal_iom_enable(AM_I2C2_IOM_INST);

    /* init i2c bus device */
    am_i2c = &am_i2c_bus_2;
    am_i2c->parent.ops = &am_i2c_ops;
    rt_i2c_bus_device_register(&am_i2c->parent, "i2c2");
#endif

#ifdef RT_USING_I2C3
    /* init i2c gpio */
    am_hal_gpio_pin_config(I2C3_GPIO_SCL, I2C3_GPIO_CFG_SCK | AM_HAL_GPIO_PULL6K);
    am_hal_gpio_pin_config(I2C3_GPIO_SDA, I2C3_GPIO_CFG_SDA | AM_HAL_GPIO_PULL6K);

    /* Initialize IOM 3 in I2C mode at 400KHz */
    am_hal_iom_pwrctrl_enable(AM_I2C3_IOM_INST);
    g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_400KHZ;
    am_hal_iom_config(AM_I2C3_IOM_INST, &g_sIOMConfig);
    am_hal_iom_enable(AM_I2C3_IOM_INST);

    /* init i2c bus device */
    am_i2c = &am_i2c_bus_3;
    am_i2c->parent.ops = &am_i2c_ops;
    rt_i2c_bus_device_register(&am_i2c->parent, "i2c3");
#endif

#ifdef RT_USING_I2C4
    /* init i2c gpio */
    am_hal_gpio_pin_config(I2C4_GPIO_SCL, I2C4_GPIO_CFG_SCK | AM_HAL_GPIO_PULL6K);
    am_hal_gpio_pin_config(I2C4_GPIO_SDA, I2C4_GPIO_CFG_SDA | AM_HAL_GPIO_PULL6K);

    /* Initialize IOM 4 in I2C mode at 400KHz */
    am_hal_iom_pwrctrl_enable(AM_I2C4_IOM_INST);
    g_sIOMConfig.ui32ClockFrequency = AM_HAL_IOM_400KHZ;
    am_hal_iom_config(AM_I2C4_IOM_INST, &g_sIOMConfig);
    am_hal_iom_enable(AM_I2C4_IOM_INST);

    /* init i2c bus device */
    am_i2c = &am_i2c_bus_4;
    am_i2c->parent.ops = &am_i2c_ops;
    rt_i2c_bus_device_register(&am_i2c->parent, "i2c4");
#endif

    //rt_kprintf("i2c_init!\n");

    return 0;
}
#ifdef RT_USING_COMPONENTS_INIT
INIT_BOARD_EXPORT(rt_i2c_init);
#endif

/*@}*/
