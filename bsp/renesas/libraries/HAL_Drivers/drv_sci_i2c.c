/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     vandoul       first version
 */

#include <rtdevice.h>
#include <rtthread.h>
#include "board.h"

#include <stdlib.h>

#ifdef BSP_USING_SCI_I2C

#define DBG_TAG              "drv.sci2c"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

#include <hal_data.h>

struct ra_sci_i2c_handle
{
    struct rt_i2c_bus_device bus;
    char bus_name[RT_NAME_MAX];
    const i2c_master_cfg_t *i2c_cfg;
    void *i2c_ctrl;
    struct rt_event event;
};

enum
{
    I2C_EVENT_ABORTED     = 1UL<<I2C_MASTER_EVENT_ABORTED    ,  ///< A transfer was aborted
    I2C_EVENT_RX_COMPLETE = 1UL<<I2C_MASTER_EVENT_RX_COMPLETE,  ///< A receive operation was completed successfully
    I2C_EVENT_TX_COMPLETE = 1UL<<I2C_MASTER_EVENT_TX_COMPLETE,  ///< A transmit operation was completed successfully
};
#define I2C_EVENT_ALL       (I2C_EVENT_ABORTED|I2C_EVENT_RX_COMPLETE|I2C_EVENT_TX_COMPLETE)

//static volatile  = I2C_MASTER_EVENT_ABORTED;
static struct ra_sci_i2c_handle ra_sci_i2cs[] =
{
#ifdef BSP_USING_SCI_I2C0
    {.bus_name = "sci2c0", .i2c_cfg = &g_sci_i2c0_cfg, .i2c_ctrl = &g_sci_i2c0_ctrl,},
#endif
#ifdef BSP_USING_SCI_I2C1
    {.bus_name = "sci2c1", .i2c_cfg = &g_sci_i2c1_cfg, .i2c_ctrl = &g_sci_i2c1_ctrl,},
#endif
#ifdef BSP_USING_SCI_I2C2
    {.bus_name = "sci2c2", .i2c_cfg = &g_sci_i2c2_cfg, .i2c_ctrl = &g_sci_i2c2_ctrl,},
#endif
#ifdef BSP_USING_SCI_I2C3
    {.bus_name = "sci2c3", .i2c_cfg = &g_sci_i2c3_cfg, .i2c_ctrl = &g_sci_i2c3_ctrl,},
#endif
#ifdef BSP_USING_SCI_I2C4
    {.bus_name = "sci2c4", .i2c_cfg = &g_sci_i2c4_cfg, .i2c_ctrl = &g_sci_i2c4_ctrl,},
#endif
#ifdef BSP_USING_SCI_I2C5
    {.bus_name = "sci2c5", .i2c_cfg = &g_sci_i2c5_cfg, .i2c_ctrl = &g_sci_i2c5_ctrl,},
#endif
};

void sci_i2c_master_callback(i2c_master_callback_args_t *p_args)
{
    if (NULL != p_args)
    {
        /* capture callback event for validating the i2c transfer event*/
        struct ra_sci_i2c_handle *ra_sci_i2c = (struct ra_sci_i2c_handle *)p_args->p_context;
        rt_event_send(&ra_sci_i2c->event, 1UL << p_args->event);
        LOG_D("event:%x", p_args->event);
    }
    LOG_D("p_args:%p", p_args);
}

static rt_err_t validate_i2c_event(struct ra_sci_i2c_handle *handle)
{
    rt_uint32_t event = 0;
    if(RT_EOK != rt_event_recv(&handle->event, I2C_EVENT_ALL, RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR, (rt_int32_t)rt_tick_from_millisecond(10), &event))
    {
        return -RT_ETIMEOUT;
    }
    if(event != I2C_EVENT_ABORTED)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

static rt_ssize_t ra_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                struct rt_i2c_msg msgs[],
                                rt_uint32_t num)
{
    rt_size_t i;
    struct rt_i2c_msg *msg = msgs;
    RT_ASSERT(bus != RT_NULL);
    struct ra_sci_i2c_handle *ra_sci_i2c = rt_container_of(bus, struct ra_sci_i2c_handle, bus);
    i2c_master_ctrl_t *master_ctrl = ra_sci_i2c->i2c_ctrl;
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
            //LOG_E("10Bit not support");
            //break;
            R_SCI_I2C_SlaveAddressSet(master_ctrl, msg[i].addr, I2C_MASTER_ADDR_MODE_10BIT);
        }
        else
        {
            //master_ctrl->slave = msg[i].addr;
            R_SCI_I2C_SlaveAddressSet(master_ctrl, msg[i].addr, I2C_MASTER_ADDR_MODE_7BIT);
        }

        if (msg[i].flags & RT_I2C_RD)
        {
            err = R_SCI_I2C_Read(master_ctrl, msg[i].buf, msg[i].len, restart);
            if (FSP_SUCCESS == err)
            {
                /* handle error */
                if(RT_EOK != validate_i2c_event(ra_sci_i2c))
                {
                    //LOG_E("POWER_CTL reg I2C read failed,%d", ra_sci_i2c->event);
                    break;
                }
            }
            /* handle error */
            else
            {
                /* Write API returns itself is not successful */
                //LOG_E("R_IIC_MASTER_Write API failed");
                break;
            }
        }
        else
        {
            err = R_SCI_I2C_Write(master_ctrl, msg[i].buf, msg[i].len, restart);
            if (FSP_SUCCESS == err)
            {
                if(RT_EOK != validate_i2c_event(ra_sci_i2c))
                {
                    //LOG_E("POWER_CTL reg I2C write failed,%d", ra_sci_i2c->event);
                    break;
                }
            }
            /* handle error */
            else
            {
                /* Write API returns itself is not successful */
                //LOG_E("R_IIC_MASTER_Write API failed");
                break;
            }
        }
    }
    return (rt_ssize_t)i;
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
    for(rt_uint32_t i=0; i<sizeof(ra_sci_i2cs)/sizeof(ra_sci_i2cs[0]); i++)
    {
        ra_sci_i2cs[i].bus.ops = &ra_i2c_ops;
        ra_sci_i2cs[i].bus.priv = 0;
        if(RT_EOK != rt_event_init(&ra_sci_i2cs[i].event, ra_sci_i2cs[i].bus_name, RT_IPC_FLAG_FIFO))
        {
            LOG_E("init event failed");
            continue;
        }
        /* opening IIC master module */
        err = R_SCI_I2C_Open(ra_sci_i2cs[i].i2c_ctrl, ra_sci_i2cs[i].i2c_cfg);
        if(err != FSP_SUCCESS)
        {
            LOG_E("R_IIC_MASTER_Open API failed,%d", err);
            continue;
        }
        err = R_SCI_I2C_CallbackSet(ra_sci_i2cs[i].i2c_ctrl, sci_i2c_master_callback, &ra_sci_i2cs[i], RT_NULL);
        /* handle error */
        if (FSP_SUCCESS != err)
        {
            LOG_E("R_SCI_I2C_CallbackSet API failed,%d", err);
            continue;
        }
        rt_i2c_bus_device_register(&ra_sci_i2cs[i].bus, ra_sci_i2cs[i].bus_name);
    }

    return 0;
}
INIT_DEVICE_EXPORT(ra_hw_i2c_init);

#endif /* BSP_USING_I2C */
