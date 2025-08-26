/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-21     hywing       The first version
 */

#include <rtdevice.h>
#include "fsl_lpi2c.h"

#ifdef RT_USING_I2C

#define DBG_TAG "drv.i2c"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

enum
{
#ifdef BSP_USING_I2C0
    I2C0_INDEX,
#endif
#ifdef BSP_USING_I2C1
    I2C1_INDEX,
#endif
};


struct mcx_i2c_bus
{
    struct rt_i2c_bus_device i2c_bus;
    LPI2C_Type              *i2c_base;
    uint32_t                 baud;
    clock_ip_name_t          clock_ip_name;
    clock_ip_src_t           clock_ip_src;
    char                    *name;
};


static struct mcx_i2c_bus i2c_buses[] =
    {
#ifdef BSP_USING_I2C0
        {
                             .i2c_base      = LPI2C0,
                             .baud          = 100000U,
                             .clock_ip_name = kCLOCK_Lpi2c0,
                             .clock_ip_src  = kCLOCK_IpSrcSysOscAsync,
                             .name          = "i2c0",
                             },
#endif
#ifdef BSP_USING_I2C1
        {
                             .i2c_base      = LPI2C1,
                             .baud          = 100000U,
                             .clock_ip_name = kCLOCK_Lpi2c1,
                             .clock_ip_src  = kCLOCK_IpSrcSysOscAsync,
                             .name          = "i2c1",
                             },
#endif
};

static rt_ssize_t lpc_i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg      *msg;
    lpi2c_master_transfer_t xfer = {0};
    rt_uint32_t             i;
    rt_ssize_t              ret = 0;

    struct mcx_i2c_bus *priv = (struct mcx_i2c_bus *)bus;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_RD)
        {
            xfer.slaveAddress   = msg->addr;
            xfer.direction      = kLPI2C_Read;
            xfer.subaddress     = 0;
            xfer.subaddressSize = 0;
            xfer.data           = msg->buf;
            xfer.dataSize       = msg->len;

            xfer.flags = kLPI2C_TransferDefaultFlag;

            if (i != 0)
            {
                xfer.flags |= kLPI2C_TransferRepeatedStartFlag;
            }

            if (i != num - 1)
            {
                xfer.flags |= kLPI2C_TransferNoStopFlag;
            }

            if (LPI2C_MasterTransferBlocking(priv->i2c_base, &xfer) != kStatus_Success)
            {
                LOG_D("i2c bus read failed!\n");
                return i;
            }
        }
        else
        {
            xfer.slaveAddress   = msg->addr;
            xfer.direction      = kLPI2C_Write;
            xfer.subaddress     = 0;
            xfer.subaddressSize = 0;
            xfer.data           = msg->buf;
            xfer.dataSize       = msg->len;

            xfer.flags = kLPI2C_TransferDefaultFlag;

            if (i != 0)
            {
                xfer.flags |= kLPI2C_TransferRepeatedStartFlag;
            }

            if (i != num - 1)
            {
                xfer.flags |= kLPI2C_TransferNoStopFlag;
            }

            if (LPI2C_MasterTransferBlocking(priv->i2c_base, &xfer) != kStatus_Success)
            {
                LOG_D("i2c bus write failed!\n");
                return i;
            }
        }
    }
    ret = i;

    return ret;
}

static const struct rt_i2c_bus_device_ops i2c_ops = {
        .master_xfer     = lpc_i2c_xfer,
        .slave_xfer      = RT_NULL,
        .i2c_bus_control = RT_NULL,
};

int rt_hw_i2c_init(void)
{
    int                   i;
    lpi2c_master_config_t masterConfig;

    for (i = 0; i < ARRAY_SIZE(i2c_buses); i++)
    {
        struct mcx_i2c_bus *priv = &i2c_buses[i];
        CLOCK_SetIpSrc(i2c_buses[i].clock_ip_name, priv->clock_ip_src);

        LPI2C_MasterGetDefaultConfig(&masterConfig);
        masterConfig.baudRate_Hz = priv->baud;

        LPI2C_MasterInit(priv->i2c_base, &masterConfig, CLOCK_GetIpFreq(priv->clock_ip_name));

        priv->i2c_bus.ops = &i2c_ops;

        rt_i2c_bus_device_register(&priv->i2c_bus, priv->name);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */


