/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-15     Magicoe      The first version for LPC55S6x
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "fsl_iocon.h"
#include "fsl_gpio.h"
#include "fsl_i2c.h"

#ifdef RT_USING_I2C

struct lpc_i2c_bus
{
    struct rt_i2c_bus_device parent;
    I2C_Type *I2C;
    char *device_name;
};

static rt_size_t lpc_i2c_xfer(struct rt_i2c_bus_device *bus,
                              struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    i2c_master_transfer_t xfer = {0};
    rt_uint32_t i;
    rt_err_t ret = RT_ERROR;

    struct lpc_i2c_bus *lpc_i2c = (struct lpc_i2c_bus *)bus;

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
            if(i != 0)
                xfer.flags = kI2C_TransferRepeatedStartFlag;
            else
                xfer.flags = kI2C_TransferDefaultFlag;

            if (I2C_MasterTransferBlocking(lpc_i2c->I2C, &xfer) != kStatus_Success)
            {
                i2c_dbg("i2c bus write failed,i2c bus stop!\n");
                goto out;
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
            if(i == 0)
                xfer.flags = kI2C_TransferNoStopFlag;
            else
                xfer.flags = kI2C_TransferDefaultFlag;

            if (I2C_MasterTransferBlocking(lpc_i2c->I2C, &xfer) != kStatus_Success)
            {
                i2c_dbg("i2c bus write failed,i2c bus stop!\n");
                goto out;
            }
        }
    }
    ret = i;

out:
    i2c_dbg("send stop condition\n");

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
    i2c_master_config_t masterConfig;
#ifdef BSP_USING_I2C1
    static struct lpc_i2c_bus lpc_i2c1;
    /* attach 12 MHz clock to FLEXCOMM2 (I2C master for touch controller) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM1);

    I2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Bps = 100000U;

    /* Initialize the I2C master peripheral */
    I2C_MasterInit(I2C1, &masterConfig, 12000000);

    rt_memset((void *)&lpc_i2c1, 0, sizeof(struct lpc_i2c_bus));
    lpc_i2c1.parent.ops = &i2c_ops;
    lpc_i2c1.I2C = I2C1;
    lpc_i2c1.device_name = "LPC Flexcomm1 as I2C";
    rt_i2c_bus_device_register(&lpc_i2c1.parent, "i2c1");
#endif /* BSP_USING_I2C1 */

#ifdef BSP_USING_I2C4
    static struct lpc_i2c_bus lpc_i2c4;
    /* attach 12 MHz clock to FLEXCOMM2 (I2C master for touch controller) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);

    I2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Bps = 100000U;

    /* Initialize the I2C master peripheral */
    I2C_MasterInit(I2C4, &masterConfig, 12000000);

    rt_memset((void *)&lpc_i2c4, 0, sizeof(struct lpc_i2c_bus));
    lpc_i2c4.parent.ops = &i2c_ops;
    lpc_i2c4.I2C = I2C4;
    lpc_i2c4.device_name = "LPC Flexcomm4 as I2C";
    rt_i2c_bus_device_register(&lpc_i2c4.parent, BSP_USING_MMA8562I2C);

#endif /* BSP_USING_I2C4 */

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */
