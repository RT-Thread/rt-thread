/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-06     YangXi       The first version
 */

#include <rtdevice.h>
#include "fsl_lpi2c.h"
#include "fsl_lpi2c_edma.h"
#include "fsl_edma.h"


#ifdef RT_USING_I2C

enum
{
#ifdef BSP_USING_I2C0
    I2C0_INDEX,
#endif
#ifdef BSP_USING_I2C1
    I2C1_INDEX,
#endif
#ifdef BSP_USING_I2C2
    I2C2_INDEX,
#endif
};


#define i2c_dbg                 rt_kprintf

struct lpc_i2c_bus
{
    struct rt_i2c_bus_device    parent;
    LPI2C_Type                  *I2C;
    clock_attach_id_t           clock_attach_id;
    clock_div_name_t            clock_div_name;
    clock_name_t                clock_src;
    uint32_t                    baud;
    char                        *name;
};


struct lpc_i2c_bus lpc_obj[] =
{
#ifdef BSP_USING_I2C0
        {
            .I2C = LPI2C0,
            .baud = 100000U,
            .clock_attach_id = kFRO12M_to_FLEXCOMM0,
            .clock_div_name = kCLOCK_DivFlexcom0Clk,
            .clock_src = kCLOCK_Fro12M,
            .name = "i2c0",
        },
#endif
#ifdef BSP_USING_I2C1
        {
            .I2C = LPI2C1,
            .baud = 100000U,
            .clock_attach_id = kFRO12M_to_FLEXCOMM1,
            .clock_div_name = kCLOCK_DivFlexcom1Clk,
            .clock_src = kCLOCK_Fro12M,
            .name = "i2c1",
        },
#endif
#ifdef BSP_USING_I2C2
        {
            .I2C = LPI2C2,
            .baud = 100000U,
            .clock_attach_id = kFRO12M_to_FLEXCOMM2,
            .clock_div_name = kCLOCK_DivFlexcom2Clk,
            .clock_src = kCLOCK_Fro12M,
            .name = "i2c2",
        },
#endif
};

static rt_ssize_t lpc_i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    lpi2c_master_transfer_t xfer = {0};
    rt_uint32_t i;
    rt_ssize_t ret = 0;

    struct lpc_i2c_bus *lpc_i2c = (struct lpc_i2c_bus *)bus;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_RD)
        {
            xfer.slaveAddress = msg->addr;
            xfer.direction = kLPI2C_Read;
            xfer.subaddress = 0;
            xfer.subaddressSize = 0;
            xfer.data = msg->buf;
            xfer.dataSize = msg->len;
            if(i != 0)
                xfer.flags = kLPI2C_TransferRepeatedStartFlag;
            else
                xfer.flags = kLPI2C_TransferDefaultFlag;

            if (LPI2C_MasterTransferBlocking(lpc_i2c->I2C, &xfer) != kStatus_Success)
            {
                i2c_dbg("i2c bus read failed!\n");
                return i;
            }
        }
        else
        {
            xfer.slaveAddress = msg->addr;
            xfer.direction = kLPI2C_Write;
            xfer.subaddress = 0;
            xfer.subaddressSize = 0;
            xfer.data = msg->buf;
            xfer.dataSize = msg->len;
            if(i == 0)
                xfer.flags = kLPI2C_TransferNoStopFlag;
            else
                xfer.flags = kLPI2C_TransferDefaultFlag;

            if (LPI2C_MasterTransferBlocking(lpc_i2c->I2C, &xfer) != kStatus_Success)
            {
                i2c_dbg("i2c bus write failed!\n");
                return i;
            }
        }
    }
    ret = i;

    return ret;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    lpc_i2c_xfer,
    RT_NULL,
    RT_NULL
};

int rt_hw_i2c_init(void)
{
    int i;
    lpi2c_master_config_t masterConfig;

    for(i=0; i<ARRAY_SIZE(lpc_obj); i++)
    {
        CLOCK_SetClkDiv(lpc_obj[i].clock_div_name, 1u);
        CLOCK_AttachClk(lpc_obj[i].clock_attach_id);

        LPI2C_MasterGetDefaultConfig(&masterConfig);
        masterConfig.baudRate_Hz = lpc_obj[i].baud;

        LPI2C_MasterInit(lpc_obj[i].I2C, &masterConfig, CLOCK_GetFreq(lpc_obj[i].clock_src));

        lpc_obj[i].parent.ops = &i2c_ops;

        rt_i2c_bus_device_register(&lpc_obj[i].parent, lpc_obj[i].name);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */



