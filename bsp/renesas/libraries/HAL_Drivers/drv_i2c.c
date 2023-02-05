/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <rtdevice.h>
#include <rtthread.h>
#include "board.h"

#include <stdlib.h>

#ifdef BSP_USING_HW_I2C

#define DBG_TAG              "drv.hwi2c"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

#include <hal_data.h>

static struct rt_i2c_bus_device prv_ra_i2c;
static volatile i2c_master_event_t i2c_event = I2C_MASTER_EVENT_ABORTED;

void i2c_master_callback(i2c_master_callback_args_t *p_args)
{
    if (NULL != p_args)
    {
        /* capture callback event for validating the i2c transfer event*/
        i2c_event = p_args->event;
    }
}

static fsp_err_t validate_i2c_event(void)
{
    uint16_t local_time_out = UINT16_MAX;

    /* resetting call back event capture variable */
    i2c_event = (i2c_master_event_t)0;

    do
    {
        /* This is to avoid infinite loop */
        --local_time_out;

        if(0 == local_time_out)
        {
            return FSP_ERR_TRANSFER_ABORTED;
        }

    }while(i2c_event == 0);

    if(i2c_event != I2C_MASTER_EVENT_ABORTED)
    {
        /* Make sure this is always Reset before return*/
        i2c_event = (i2c_master_event_t)0;
        return FSP_SUCCESS;
    }

    /* Make sure this is always Reset before return */
    i2c_event = (i2c_master_event_t)0;
    return FSP_ERR_TRANSFER_ABORTED;
}

static rt_ssize_t ra_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                struct rt_i2c_msg msgs[],
                                rt_uint32_t num)
{
    rt_size_t i;
    struct rt_i2c_msg *msg = msgs;
    RT_ASSERT(bus != RT_NULL);
    fsp_err_t err     = FSP_SUCCESS;
    bool restart = false;

    for (i = 0; i < num; i++)
    {
        if (msg[i].flags & RT_I2C_NO_START)
        {
            restart = true;
        }
        if (msg[i].flags & RT_I2C_ADDR_10BIT)
        {
            LOG_E("10Bit not support");
            break;
        }
        else
        {
            g_i2c_master1_ctrl.slave = msg[i].addr;
        }

        if (msg[i].flags & RT_I2C_RD)
        {
            err = R_IIC_MASTER_Read(&g_i2c_master1_ctrl, msg[i].buf, msg[i].len, restart);
            if (FSP_SUCCESS == err)
            {
                err = validate_i2c_event();
                /* handle error */
                if(FSP_ERR_TRANSFER_ABORTED == err)
                {
                    LOG_E("POWER_CTL reg I2C read failed");
                    break;
                }
            }
            /* handle error */
            else
            {
                /* Write API returns itself is not successful */
                LOG_E("R_IIC_MASTER_Write API failed");
                break;
            }
        }
        else
        {
            err = R_IIC_MASTER_Write(&g_i2c_master1_ctrl, msg[i].buf, msg[i].len, restart);
            if (FSP_SUCCESS == err)
            {
                err = validate_i2c_event();
                /* handle error */
                if(FSP_ERR_TRANSFER_ABORTED == err)
                {
                    LOG_E("POWER_CTL reg I2C write failed");
                    break;
                }
            }
            /* handle error */
            else
            {
                /* Write API returns itself is not successful */
                LOG_E("R_IIC_MASTER_Write API failed");
                break;
            }
        }
    }
    return i;
}

static const struct rt_i2c_bus_device_ops ra_i2c_ops =
{
    .master_xfer        = ra_i2c_mst_xfer,
    .slave_xfer         = RT_NULL,
    .i2c_bus_control    = RT_NULL
};

int ra_hw_i2c_init(void)
{
    fsp_err_t err     = FSP_SUCCESS;
    prv_ra_i2c.ops = &ra_i2c_ops;
    prv_ra_i2c.priv = 0;
    /* opening IIC master module */
    err = R_IIC_MASTER_Open(&g_i2c_master1_ctrl, &g_i2c_master1_cfg);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        LOG_E("R_IIC_MASTER_Open API failed");
        return err;
    }
    rt_i2c_bus_device_register(&prv_ra_i2c, "i2c1");

    return 0;
}
INIT_DEVICE_EXPORT(ra_hw_i2c_init);

#endif /* BSP_USING_I2C */
