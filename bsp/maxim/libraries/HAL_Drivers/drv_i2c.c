/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-26     Jackistang   first version
 *
 */

#include "drv_i2c.h"
#include "i2c.h"
#include <rtdevice.h>
#include <rtthread.h>
#include "board.h"

#ifdef RT_USING_I2C

#if !defined(BSP_USING_I2C0) && !defined(BSP_USING_I2C1)
    #error "Please define at least one BSP_USING_I2Cx"
    /* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable I2C */
#endif

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG                "drv.i2c"

/* mxc config class */
struct mxc_i2c_config
{
    const char *name;
    mxc_i2c_regs_t *i2c_periph;
    i2c_speed_t speed;
    IRQn_Type irq_type;
};

struct mxc_i2c
{
    struct rt_i2c_bus_device bus;
    struct mxc_i2c_config *config;
};

static struct mxc_i2c_config i2c_config[] =
{
#ifdef BSP_USING_I2C0
    {
        .name       = "i2c0",
        .i2c_periph = MXC_I2C_GET_I2C(0),
        .irq_type   = MXC_I2C_GET_IRQ(0),
        .speed      = I2C_STD_MODE,
        /*I2C_STD_MODE: 100KHz, I2C_FAST_MODE: 400KHz, I2C_FASTPLUS_MODE: 1MHz, I2C_HS_MODE: 3.4MHz */
    },
#endif
#ifdef BSP_USING_I2C1
    {
        .name       = "i2c1",
        .i2c_periph = MXC_I2C_GET_I2C(1),
        .irq_type   = MXC_I2C_GET_IRQ(1),
        .speed      = I2C_STD_MODE,
        /*I2C_STD_MODE: 100KHz, I2C_FAST_MODE: 400KHz, I2C_FASTPLUS_MODE: 1MHz, I2C_HS_MODE: 3.4MHz */
    },
#endif
};

static struct mxc_i2c i2c_obj[sizeof(i2c_config) / sizeof(i2c_config[0])] = {0};


static rt_ssize_t mxc_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                  struct rt_i2c_msg msgs[],
                                  rt_uint32_t num)
{
    rt_uint32_t i, ret;
    rt_uint16_t addr;
    int error;
    int restart = 0;
    struct rt_i2c_msg *msg;
    struct mxc_i2c *obj = (struct mxc_i2c *)bus;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_ADDR_10BIT || msg->flags & RT_I2C_NO_START || msg->flags & RT_I2C_IGNORE_NACK || msg->flags & RT_I2C_NO_READ_ACK)
        {
            LOG_E("Not support RT_I2C_ADDR_10BIT or RT_I2C_NO_START or RT_I2C_IGNORE_NACK or RT_I2C_NO_READ_ACK");
            return 0;
        }

        if (msg->flags & RT_I2C_NO_STOP)
        {
            restart = 1;
        }

        if (msg->flags & RT_I2C_RD)
        {
            addr = msg->addr << 1;
            if ((error = I2C_MasterRead(obj->config->i2c_periph, (uint8_t)addr, msg->buf, msg->len, restart)) != msg->len)
            {
                LOG_E("Error writing %d", error);
                return 0;
            }
        }
        else    /* RT_I2C_WR */
        {
            addr = msg->addr << 1;
            if ((error = I2C_MasterWrite(obj->config->i2c_periph, (uint8_t)addr, msg->buf, msg->len, restart)) != msg->len)
            {
                LOG_E("Error writing %d", error);
                return 0;
            }
        }
    }
    ret = i;

    return ret;
}

static const struct rt_i2c_bus_device_ops mxc_i2c_ops =
{
    mxc_i2c_mst_xfer,
    RT_NULL,
    RT_NULL,
};

int rt_hw_i2c_init(void)
{
    rt_size_t obj_num;
    int index;
    rt_err_t result = 0;

#ifdef BSP_USING_I2C0
    NVIC_EnableIRQ(I2C0_IRQn);
#endif
#ifdef BSP_USING_I2C1
    NVIC_EnableIRQ(I2C1_IRQn);
#endif

    obj_num = sizeof(i2c_obj) / sizeof(struct mxc_i2c);
    for (index = 0; index < obj_num; index++)
    {
        /* init i2c object */
        i2c_obj[index].config = &i2c_config[index];
        i2c_obj[index].bus.ops = &mxc_i2c_ops;

        /* init i2c device */
        I2C_Shutdown(i2c_config[index].i2c_periph);
        I2C_Init(i2c_config[index].i2c_periph, i2c_config[index].speed, RT_NULL);

        /* register i2c device */
        result = rt_i2c_bus_device_register(&i2c_obj[index].bus,
                                            i2c_obj[index].config->name
                                           );
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#ifdef BSP_USING_I2C0
void I2C0_IRQHandler(void)
{
    rt_interrupt_enter();
    I2C_Handler(MXC_I2C0);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_I2C1
void I2C1_IRQHandler(void)
{
    rt_interrupt_enter();
    I2C_Handler(MXC_I2C1);
    rt_interrupt_leave();
}
#endif

#endif /* RT_USING_I2C */
