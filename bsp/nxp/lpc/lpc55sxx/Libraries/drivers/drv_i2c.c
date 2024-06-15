/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-15     Magicoe      The first version for LPC55S6x
 * 2023-02-17     Vandoul      Add status to lpc_i2c_bus.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "fsl_iocon.h"
#include "fsl_gpio.h"
#include "fsl_i2c.h"
#include "fsl_i2c_dma.h"

#ifdef BSP_USING_I2C

enum
{
#ifdef BSP_USING_I2C1
    I2C1_INDEX,
#endif
#ifdef BSP_USING_I2C4
    I2C4_INDEX,
#endif
};


#define i2c_dbg                 rt_kprintf

struct lpc_i2c_bus
{
    struct rt_i2c_bus_device    parent;
    I2C_Type                    *I2C;
    DMA_Type                    *DMA;
    i2c_master_dma_handle_t     i2c_mst_dma_handle;
    dma_handle_t                dmaHandle;
    rt_sem_t                    sem;
    clock_attach_id_t           i2c_clock_id;
    uint32_t                    dma_chl;
    uint32_t                    instance;
    uint32_t                    baud;
    char                        *device_name;
    uint32_t                    status;
};


struct lpc_i2c_bus lpc_obj[] =
{
#ifdef BSP_USING_I2C1
        {
            .I2C = I2C1,
            .DMA = DMA0,
            .dma_chl = 7,
            .device_name = "i2c1",
            .baud = 100000U,
            .instance = 1U,
            .i2c_clock_id = kFRO12M_to_FLEXCOMM1,
        },
#endif
#ifdef BSP_USING_I2C4
        {
            .I2C = I2C4,
            .DMA = DMA0,
            .dma_chl = 13,
            .device_name = "i2c4",
            .baud = 400000U,
            .instance = 4U,
            .i2c_clock_id = kFRO12M_to_FLEXCOMM4,
        },
#endif
};


static void i2c_mst_dma_callback(I2C_Type *base, i2c_master_dma_handle_t *handle, status_t status, void *userData)
{
    struct lpc_i2c_bus *lpc_i2c = (struct lpc_i2c_bus*)userData;
    lpc_i2c->status = status;
    rt_sem_release(lpc_i2c->sem);
}

static rt_ssize_t lpc_i2c_xfer(struct rt_i2c_bus_device *bus,
                              struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    i2c_master_transfer_t xfer = {0};
    rt_uint32_t i;
    rt_err_t ret = -RT_ERROR;

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

          //  if (I2C_MasterTransferBlocking(lpc_i2c->I2C, &xfer) != kStatus_Success)
            if(I2C_MasterTransferDMA(lpc_i2c->I2C, &lpc_i2c->i2c_mst_dma_handle, &xfer) != kStatus_Success)
            {
                i2c_dbg("i2c bus read failed!\n");
                return i;
            }
            rt_sem_take(lpc_i2c->sem, RT_WAITING_FOREVER);
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

            //if (I2C_MasterTransferBlocking(lpc_i2c->I2C, &xfer) != kStatus_Success)
            if(I2C_MasterTransferDMA(lpc_i2c->I2C, &lpc_i2c->i2c_mst_dma_handle, &xfer) != kStatus_Success)
            {
                i2c_dbg("i2c bus write failed!\n");
                return i;
            }
            rt_sem_take(lpc_i2c->sem, RT_WAITING_FOREVER);
            if(lpc_i2c->status != kStatus_Success)
            {
                break;
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
    i2c_master_config_t masterConfig;

    for(i=0; i<ARRAY_SIZE(lpc_obj); i++)
    {
        CLOCK_AttachClk(lpc_obj[i].i2c_clock_id);

        I2C_MasterGetDefaultConfig(&masterConfig);
        masterConfig.baudRate_Bps = lpc_obj[i].baud;

        /* Initialize the I2C master peripheral */
        I2C_MasterInit(lpc_obj[i].I2C, &masterConfig, CLOCK_GetFlexCommClkFreq(lpc_obj[i].instance));

        lpc_obj[i].parent.ops = &i2c_ops;
        lpc_obj[i].sem = rt_sem_create("sem_i2c", 0, RT_IPC_FLAG_FIFO);

        DMA_CreateHandle(&lpc_obj[i].dmaHandle, lpc_obj[i].DMA, lpc_obj[i].dma_chl);
        I2C_MasterTransferCreateHandleDMA(lpc_obj[i].I2C, &lpc_obj[i].i2c_mst_dma_handle, i2c_mst_dma_callback, &lpc_obj[i], &lpc_obj[i].dmaHandle);

        rt_i2c_bus_device_register(&lpc_obj[i].parent, lpc_obj[i].device_name);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* BSP_USING_I2C */
