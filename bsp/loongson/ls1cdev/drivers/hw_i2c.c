/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2018-01-04     Sundm75        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "ls1c_i2c.h"
#include "../libraries/ls1c_pin.h"

#ifdef RT_USING_I2C

struct ls1c_i2c_bus
{
    struct rt_i2c_bus_device parent;
    rt_uint32_t u32Module;
};

rt_size_t rt_i2c_master_xfer(struct rt_i2c_bus_device *bus,
                          struct rt_i2c_msg         *msgs,
                          rt_uint32_t               num)
{
    struct ls1c_i2c_bus * i2c_bus = (struct ls1c_i2c_bus *)bus;
    ls1c_i2c_info_t i2c_info;
    struct rt_i2c_msg *msg;
    int i;
    rt_int32_t ret = RT_EOK;
    i2c_info.clock = 50000;       // 50kb/s
    i2c_info.I2Cx  = i2c_bus->u32Module;
    i2c_init(&i2c_info);

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        if (msg->flags == RT_I2C_RD)
        {
            i2c_send_start_and_addr(&i2c_info, msg->addr, LS1C_I2C_DIRECTION_READ);
            i2c_receive_ack(&i2c_info);
            i2c_receive_data(&i2c_info, (rt_uint8_t *)msg->buf, msg->len);
            i2c_send_stop(&i2c_info);
         }
        else if(msg->flags == RT_I2C_WR)
        {
            i2c_send_start_and_addr(&i2c_info, msg->addr, LS1C_I2C_DIRECTION_WRITE);
            i2c_receive_ack(&i2c_info);
            i2c_send_data(&i2c_info, (rt_uint8_t *)msg->buf, msg->len);
            i2c_send_stop(&i2c_info);
        }
        ret++;
    }
    return ret;
}

rt_err_t rt_i2c_bus_control(struct rt_i2c_bus_device *bus,
                          int                       cmd,
                          void                      *args)
{
    struct ls1c_i2c_bus * i2c_bus = (struct ls1c_i2c_bus *)bus;

    RT_ASSERT(bus != RT_NULL);
    i2c_bus = (struct ls1c_i2c_bus *)bus->parent.user_data;

    RT_ASSERT(i2c_bus != RT_NULL);

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CONFIG :
            break;
    }

    return RT_EOK;
}

static const struct rt_i2c_bus_device_ops ls1c_i2c_ops =
{
    rt_i2c_master_xfer,
    RT_NULL,
    rt_i2c_bus_control
};


#ifdef RT_USING_I2C0
static struct ls1c_i2c_bus ls1c_i2c_bus_0 =
{
    {1},
    LS1C_I2C_0,
};
#endif

#ifdef RT_USING_I2C1
static struct ls1c_i2c_bus ls1c_i2c_bus_1 =
{
    {1},
    LS1C_I2C_1,
};
#endif

#ifdef RT_USING_I2C2
static struct ls1c_i2c_bus ls1c_i2c_bus_2 =
{
    {1},
    LS1C_I2C_2,
};
#endif

int ls1c_hw_i2c_init(void)
{
    struct ls1c_i2c_bus* ls1c_i2c;

#ifdef RT_USING_I2C0
/*
    pin_set_purpose(2, PIN_PURPOSE_OTHER);
    pin_set_purpose(3, PIN_PURPOSE_OTHER);
    pin_set_remap(2, PIN_REMAP_SECOND);
    pin_set_remap(3, PIN_REMAP_SECOND);
    */
#endif
#ifdef RT_USING_I2C1
    pin_set_purpose(2, PIN_PURPOSE_OTHER);
    pin_set_purpose(3, PIN_PURPOSE_OTHER);
    pin_set_remap(2, PIN_REMAP_SECOND);
    pin_set_remap(3, PIN_REMAP_SECOND);
#endif
#ifdef RT_USING_I2C2
    pin_set_purpose(51, PIN_PURPOSE_OTHER);
    pin_set_purpose(50, PIN_PURPOSE_OTHER);
    pin_set_remap(51, PIN_REMAP_FOURTH);
    pin_set_remap(50, PIN_REMAP_FOURTH);
#endif


#ifdef RT_USING_I2C0
    ls1c_i2c = &ls1c_i2c_bus_0;
    ls1c_i2c->parent.ops = &ls1c_i2c_ops;
    rt_i2c_bus_device_register(&ls1c_i2c->parent, "i2c0");
    rt_kprintf("i2c0_init!\n");
#endif
#ifdef RT_USING_I2C1
    ls1c_i2c = &ls1c_i2c_bus_1;
    ls1c_i2c->parent.ops = &ls1c_i2c_ops;
    rt_i2c_bus_device_register(&ls1c_i2c->parent, "i2c1");
    rt_kprintf("i2c1_init!\n");
#endif

#ifdef RT_USING_I2C2
    ls1c_i2c = &ls1c_i2c_bus_2;
    ls1c_i2c->parent.ops = &ls1c_i2c_ops;
    rt_i2c_bus_device_register(&ls1c_i2c->parent, "i2c2");
    rt_kprintf("i2c2_init!\n");
#endif

    return RT_EOK;
}

INIT_BOARD_EXPORT(ls1c_hw_i2c_init);

#endif
