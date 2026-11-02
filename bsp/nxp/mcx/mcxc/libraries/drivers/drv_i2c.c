/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-03     Yilin Sun    Initial version
 */

#include <rtdevice.h>

#include "fsl_i2c.h"

#ifdef RT_USING_I2C

#define BSP_DEFAULT_I2C_FREQ (100000)

typedef struct
{
    struct rt_i2c_bus_device parent;
    I2C_Type *instance;
    uint32_t input_frequency;
} mcx_i2c_obj_t;

typedef struct
{
    I2C_Type *instance;
    uint8_t id;
} mcx_i2c_instance_t;

static const mcx_i2c_instance_t mcx_i2c_instances[] =
{
#ifdef BSP_USING_I2C0
    {I2C0, 0},
#endif

#ifdef BSP_USING_I2C1
    {I2C1, 1},
#endif
};

static mcx_i2c_obj_t mcx_i2c_list[ARRAY_SIZE(mcx_i2c_instances)];

static int mcx_i2c_master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    i2c_master_transfer_t xfer = {0};
    rt_uint32_t i;
    rt_ssize_t ret = 0;

    mcx_i2c_obj_t *i2c = (mcx_i2c_obj_t *)bus;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_RD)
        {
            xfer.slaveAddress = msg->addr;
            xfer.direction = kI2C_Read;
            xfer.subaddress = 0;
            xfer.subaddressSize = 0;
            xfer.data = msg->buf;
            xfer.dataSize = msg->len;

            xfer.flags = kI2C_TransferDefaultFlag;

            if (i != 0)
            {
                xfer.flags |= kI2C_TransferRepeatedStartFlag;
            }

            if (i != num - 1)
            {
                xfer.flags |= kI2C_TransferNoStopFlag;
            }


            if (I2C_MasterTransferBlocking(i2c->instance, &xfer) != kStatus_Success)
            {
                return i;
            }
        }
        else
        {
            xfer.slaveAddress = msg->addr;
            xfer.direction = kI2C_Write;
            xfer.subaddress = 0;
            xfer.subaddressSize = 0;
            xfer.data = msg->buf;
            xfer.dataSize = msg->len;

            xfer.flags = kI2C_TransferDefaultFlag;

            if (i != 0)
            {
                xfer.flags |= kI2C_TransferRepeatedStartFlag;
            }

            if (i != num - 1)
            {
                xfer.flags |= kI2C_TransferNoStopFlag;
            }

            if (I2C_MasterTransferBlocking(i2c->instance, &xfer) != kStatus_Success)
            {
                return i;
            }
        }
    }

    ret = num;

    return ret;
}

static const struct rt_i2c_bus_device_ops mcx_i2c_ops =
{
    mcx_i2c_master_xfer,
    RT_NULL,
    RT_NULL,
};

static int rt_hw_i2c_init(void)
{
    i2c_master_config_t master_cfg;
    char name_buf[16];

    for (size_t i = 0; i < ARRAY_SIZE(mcx_i2c_instances); i++)
    {
        mcx_i2c_list[i].input_frequency = CLOCK_GetCoreSysClkFreq();
        mcx_i2c_list[i].instance = mcx_i2c_instances[i].instance;
        mcx_i2c_list[i].parent.ops = &mcx_i2c_ops;

        I2C_MasterGetDefaultConfig(&master_cfg);

        master_cfg.baudRate_Bps = BSP_DEFAULT_I2C_FREQ;

        I2C_MasterInit(mcx_i2c_list[i].instance, &master_cfg, mcx_i2c_list[i].input_frequency);

        rt_snprintf(name_buf, 16, "i2c%d", mcx_i2c_instances[i].id);

        rt_i2c_bus_device_register(&mcx_i2c_list[i].parent, name_buf);
    }

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif
