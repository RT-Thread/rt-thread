/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * 2021-11-19     xieyangrun     first version
 */

#include <rthw.h>
#include <rtdevice.h>

#include "sunxi_hal_twi.h"

#define DBG_LVL DBG_WARNING
#define DBG_TAG "drv/i2c"
#include <rtdbg.h>

struct hal_i2c_bus
{
    struct rt_i2c_bus_device parent;
    twi_port_t id;
    struct rt_mutex lock;
};

//connect am drv to rt drv.
static rt_ssize_t _i2c_master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg *msgs, rt_uint32_t num)
{
    struct hal_i2c_bus *_i2c_bus = (struct hal_i2c_bus *)bus;
    struct rt_i2c_msg *msg;
    twi_msg_t *twi_msg;
    int i;
    twi_status_t status;
    extern twi_status_t hal_twi_xfer(twi_port_t port, twi_msg_t *msgs, int32_t num);


    twi_msg = rt_malloc(sizeof(*twi_msg) * num);
    if (!twi_msg)
    {
        LOG_E("i2c xfer malloc(%d) failure\n", sizeof(*twi_msg) * num);
        return -RT_ENOMEM;
    }

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        if (msg->flags == RT_I2C_RD)
        {
            twi_msg[i].flags = TWI_M_RD;
        }
        else if(msg->flags == RT_I2C_WR)
        {
            twi_msg[i].flags = 0;
        }

        if (_i2c_bus->parent.flags & RT_I2C_DEV_CTRL_10BIT)
        {
            twi_msg[i].flags |= TWI_M_TEN;
        }

        twi_msg[i].addr = msg->addr;
        twi_msg[i].len = msg->len;
        twi_msg[i].buf = msg->buf;
    }

    rt_mutex_take(&_i2c_bus->lock, RT_WAITING_FOREVER);
    status = hal_twi_xfer(_i2c_bus->id, twi_msg, i);
    rt_mutex_release(&_i2c_bus->lock);

    if (status != TWI_STATUS_OK)
    {
        i = 0;
        LOG_E("i2c xfer failure\n");
    }

    rt_free(twi_msg);

    return i;
}

static const struct rt_i2c_bus_device_ops _i2c_ops =
{
    _i2c_master_xfer,
    RT_NULL,
    RT_NULL
};

#ifdef BSP_USING_I2C0
static struct hal_i2c_bus _i2c_bus_0 = {
    .id = TWI_MASTER_0
};
#endif

#ifdef BSP_USING_I2C1
static struct hal_i2c_bus _i2c_bus_1 = {
    .id = TWI_MASTER_1,
};
#endif

#ifdef BSP_USING_I2C2
static struct hal_i2c_bus _i2c_bus_2 = {
    .id = TWI_MASTER_2,
};
#endif

#ifdef BSP_USING_I2C3
static struct hal_i2c_bus _i2c_bus_3 = {
    .id = TWI_MASTER_3,
};
#endif

#define CFG_GPIO_PORT(p) ((p) - 'A' + 1)

static const user_gpio_set_t _i2c_gpio_cfg[][2] = {
    {// twi0
        {
            .gpio_name = "twi0.sck",
            .port = CFG_GPIO_PORT('B'),
            .port_num = 3, // PB3
            .mul_sel = 4,
            .pull = 1, // pull up
            .drv_level = 3,
            .data = 1,
        },
        {
            .gpio_name = "twi0.sda",
            .port = CFG_GPIO_PORT('B'),
            .port_num = 2, // PB2
            .mul_sel = 4,
            .pull = 1, // pull up
            .drv_level = 3,
            .data = 1,
        }
    },
    {// twi1
        {
            .gpio_name = "twi1.sck",
            .port = CFG_GPIO_PORT('B'),
            .port_num = 4, // PB4
            .mul_sel = 4,
            .pull = 1, // pull up
            .drv_level = 3,
            .data = 1,
        },
        {
            .gpio_name = "twi1.sda",
            .port = CFG_GPIO_PORT('B'),
            .port_num = 5, // PB5
            .mul_sel = 4,
            .pull = 1, // pull up
            .drv_level = 3,
            .data = 1,
        }
    },
#ifdef BSP_USING_MANGOPI // mango board
    {// twi2
        {
            .gpio_name = "twi2.sck",
            .port = CFG_GPIO_PORT('E'),
            .port_num = 12, // PE12
            .mul_sel = 2,
            .pull = 1, // pull up
            .drv_level = 3,
            .data = 1,
        },
        {
            .gpio_name = "twi2.sda",
            .port = CFG_GPIO_PORT('E'),
            .port_num = 13, // PE13
            .mul_sel = 2,
            .pull = 1, // pull up
            .drv_level = 3,
            .data = 1,
        }
    },
#elif defined(BSP_USING_M7)
    {// twi2
        {
            .gpio_name = "twi2.sck",
            .port = CFG_GPIO_PORT('G'),
            .port_num = 6, // PG6
            .mul_sel = 3,
            .pull = 1, // pull up
            .drv_level = 3,
            .data = 1,
        },
        {
            .gpio_name = "twi2.sda",
            .port = CFG_GPIO_PORT('G'),
            .port_num = 7, // PG7
            .mul_sel = 3,
            .pull = 1, // pull up
            .drv_level = 3,
            .data = 1,
        }
    },
#endif
    {// twi3
        {
            .gpio_name = "twi3.sck",
            .port = CFG_GPIO_PORT('B'),
            .port_num = 6, // PB6
            .mul_sel = 4,
            .pull = 1, // pull up
            .drv_level = 3,
            .data = 1,
        },
        {
            .gpio_name = "twi3.sda",
            .port = CFG_GPIO_PORT('B'),
            .port_num = 7, // PB7
            .mul_sel = 4,
            .pull = 1, // pull up
            .drv_level = 3,
            .data = 1,
        }
    },
};

int hal_i2c_gpio_cfg_load(user_gpio_set_t *gpio_cfg, int32_t GPIONum, int id)
{
    int i;

    if (id > sizeof(_i2c_gpio_cfg) / sizeof(_i2c_gpio_cfg[0]))
    {
        rt_kprintf("twi id %d>%d\n", id, sizeof(_i2c_gpio_cfg) / sizeof(_i2c_gpio_cfg[0]));
        return -1;
    }

    /* twi0 */
    for (i = 0; i < GPIONum; i++)
    {
        memcpy(gpio_cfg, &_i2c_gpio_cfg[id][i], sizeof(user_gpio_set_t));
        gpio_cfg++;
    }

    return 0;
}

static int _i2c_dev_register(struct hal_i2c_bus* bus, const char* name)
{
    rt_mutex_init(&bus->lock, name, RT_IPC_FLAG_PRIO);

    hal_twi_init(bus->id);
    bus->parent.ops = &_i2c_ops;

    if (rt_i2c_bus_device_register(&bus->parent, name) != RT_EOK)
    {
        LOG_E("i2c bus register:%s failure\n", name);
        return -1;
    }

    return 0;
}

int rt_hw_i2c_init(void)
{
#ifdef BSP_USING_I2C0
    /* init i2c bus device */
    _i2c_dev_register(&_i2c_bus_0, "i2c0");
#endif

#ifdef BSP_USING_I2C1
    /* init i2c bus device */
    _i2c_dev_register(&_i2c_bus_1, "i2c1");
#endif

#ifdef BSP_USING_I2C2
    _i2c_dev_register(&_i2c_bus_2, "i2c2");
#endif

#ifdef BSP_USING_I2C3
    _i2c_dev_register(&_i2c_bus_3, "i2c3");
#endif

    //rt_kprintf("i2c_init!\n");

    return 0;
}
// #ifdef RT_USING_COMPONENTS_INIT
INIT_BOARD_EXPORT(rt_hw_i2c_init);
// #endif

static void _i2c_test(int argc, char *args[])
{
    struct rt_i2c_bus_device *i2c_bus;
    struct rt_i2c_msg msg[2];
    uint8_t buf[3] = {0x12, 0x34, 0x56};

    if (argc < 2) return;

    i2c_bus = (struct rt_i2c_bus_device*)rt_device_find("i2c2");
    if (!i2c_bus)
    {
        rt_kprintf("i2c2 not found\n");
        return;
    }

    msg[0].addr = 0x36;
    msg[0].flags = 0;
    msg[0].buf = buf;
    msg[0].len = sizeof(buf);

    msg[1].addr = 0x36;
    msg[1].flags = RT_I2C_RD;
    msg[1].buf = buf;
    msg[1].len = sizeof(buf);

    if (atoi(args[1]) == 0)
    {
        rt_i2c_transfer(i2c_bus, &msg[0], 1);
    }
    else
    {
        rt_i2c_transfer(i2c_bus, &msg[0], 2);
    }
}
MSH_CMD_EXPORT_ALIAS(_i2c_test, i2c_test, i2c bus test);

static void _pin_test(void)
{
    int i;
    rt_base_t pin;

    pin = GPIO_PE10;

    rt_pin_mode(pin, PIN_MODE_OUTPUT);

    for (i = 0; i < 20; i++)
    {
        rt_pin_write(pin, !!(i & 1));
        rt_thread_mdelay(2);
    }
}
MSH_CMD_EXPORT_ALIAS(_pin_test, pin_test, gpio pin test);

/*@}*/





