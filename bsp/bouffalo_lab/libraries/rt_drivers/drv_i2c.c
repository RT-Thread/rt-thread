/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/05/10     flyingcys    first version
*/

#include <rthw.h>
#include <rtdevice.h>

#ifdef BSP_USING_I2C
#include "drv_i2c.h"

#define DBG_TAG "DRV.I2C"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

struct bl_i2c_bus
{
    struct rt_i2c_bus_device parent;
    struct bflb_device_s *i2c;
    struct rt_mutex lock;
};

static rt_ssize_t _i2c_master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg *msgs, rt_uint32_t num)
{
    struct bl_i2c_bus *_i2c_bus = (struct bl_i2c_bus *)bus;
    struct rt_i2c_msg *msg;
    struct bflb_i2c_msg_s *bflb_i2c_msg;
    int i;
    int ret;

    bflb_i2c_msg = rt_malloc(sizeof(struct bflb_i2c_msg_s) * num);
    if (!bflb_i2c_msg)
    {
        LOG_E("i2c xfer malloc(%d) failure\n", sizeof(struct bflb_i2c_msg_s) * num);
        return -RT_ENOMEM;
    }

    rt_memset(bflb_i2c_msg, 0, sizeof(struct bflb_i2c_msg_s) * num);

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        if (msg->flags & RT_I2C_RD)
        {
            bflb_i2c_msg[i].flags = I2C_M_READ;
        }
        else
        {
            bflb_i2c_msg[i].flags = 0;
        }

        if (_i2c_bus->parent.flags & RT_I2C_DEV_CTRL_10BIT)
        {
            bflb_i2c_msg[i].flags |= I2C_M_TEN;
        }

        bflb_i2c_msg[i].addr = msg->addr;
        bflb_i2c_msg[i].length = msg->len;
        bflb_i2c_msg[i].buffer = msg->buf;
    }

    rt_mutex_take(&_i2c_bus->lock, RT_WAITING_FOREVER);
    ret = bflb_i2c_transfer(_i2c_bus->i2c, bflb_i2c_msg, num);
    rt_mutex_release(&_i2c_bus->lock);

    rt_free(bflb_i2c_msg);
    bflb_i2c_msg = RT_NULL;

    if (ret < 0)
    {
        i = 0;
        LOG_E("i2c xfer failure %d\n", ret);
    }

    return i;
}

static const struct rt_i2c_bus_device_ops _i2c_ops =
{
    _i2c_master_xfer,
    RT_NULL,
    RT_NULL
};

int rt_hw_i2c_init(void)
{
    struct bflb_device_s *gpio;
    gpio = bflb_device_get_by_name("gpio");

#ifdef BSP_USING_I2C0
    static struct bl_i2c_bus i2c_bus0;

   /* I2C0_SCL */
    bflb_gpio_init(gpio, I2C0_GPIO_SCL, GPIO_FUNC_I2C0 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);
    /* I2C0_SDA */
    bflb_gpio_init(gpio, I2C0_GPIO_SDA, GPIO_FUNC_I2C0 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);

    /* init i2c bus device */
    rt_mutex_init(&i2c_bus0.lock, "i2c0_mutex", RT_IPC_FLAG_PRIO);

    i2c_bus0.parent.ops = &_i2c_ops;
    i2c_bus0.i2c = bflb_device_get_by_name("i2c0");
    bflb_i2c_init(i2c_bus0.i2c, I2C0_FREQUENCY);

    if (rt_i2c_bus_device_register(&i2c_bus0.parent, "i2c0") != RT_EOK)
        LOG_E("i2c bus register:%s failure\n", "i2c0");
#endif

#ifdef BSP_USING_I2C1
    static struct bl_i2c_bus i2c_bus1;

    /* I2C1_SCL */
    bflb_gpio_init(gpio, I2C1_GPIO_SCL, GPIO_FUNC_I2C1 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);
    /* I2C1_SDA */
    bflb_gpio_init(gpio, I2C1_GPIO_SDA, GPIO_FUNC_I2C1 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);

    /* init i2c bus device */
    rt_mutex_init(&i2c_bus1.lock, "i2c1_mutex", RT_IPC_FLAG_PRIO);

    i2c_bus1.parent.ops = &_i2c_ops;
    i2c_bus1.i2c = bflb_device_get_by_name("i2c1");
    bflb_i2c_init(i2c_bus1.i2c, I2C1_FREQUENCY);

    if (rt_i2c_bus_device_register(&i2c_bus1.parent, "i2c1") != RT_EOK)
        LOG_E("i2c bus register:%s failure\n", "i2c1");
#endif

#ifdef BSP_USING_I2C2
    static struct bl_i2c_bus i2c_bus2;

    /* I2C2_SCL */
    bflb_gpio_init(gpio, I2C2_GPIO_SCL, GPIO_FUNC_I2C2 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);
    /* I2C2_SDA */
    bflb_gpio_init(gpio, I2C2_GPIO_SDA, GPIO_FUNC_I2C2 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);

    /* init i2c bus device */
    rt_mutex_init(&i2c_bus2.lock, "i2c2_mutex", RT_IPC_FLAG_PRIO);

    i2c_bus2.parent.ops = &_i2c_ops;
    i2c_bus2.i2c = bflb_device_get_by_name("i2c2");
    bflb_i2c_init(i2c_bus2.i2c, I2C2_FREQUENCY);

    if (rt_i2c_bus_device_register(&i2c_bus2.parent, "i2c2") != RT_EOK)
        LOG_E("i2c bus register:%s failure\n", "i2c2");
#endif

#ifdef BSP_USING_I2C3
    static struct bl_i2c_bus i2c_bus3;

    /* I2C3_SCL */
    bflb_gpio_init(gpio, I2C3_GPIO_SCL, GPIO_FUNC_I2C3 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);
    /* I2C3_SDA */
    bflb_gpio_init(gpio, I2C3_GPIO_SDA, GPIO_FUNC_I2C3 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);

    /* init i2c bus device */
    rt_mutex_init(&i2c_bus3.lock, "i2c3_mutex", RT_IPC_FLAG_PRIO);

    i2c_bus3.parent.ops = &_i2c_ops;
    i2c_bus3.i2c = bflb_device_get_by_name("i2c3");
    bflb_i2c_init(i2c_bus3.i2c, I2C3_FREQUENCY);

    if (rt_i2c_bus_device_register(&i2c_bus3.parent, "i2c3") != RT_EOK)
        LOG_E("i2c bus register:%s failure\n", "i2c3");
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* BSP_USING_I2C */
