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

#define DRV_DEBUG
#define LOG_TAG             "drv.hwi2c"
#include <drv_log.h>

#include <hal_data.h>

#define RA_SCI_EVENT_ABORTED        1
#define RA_SCI_EVENT_RX_COMPLETE    2
#define RA_SCI_EVENT_TX_COMPLETE    4
#define RA_SCI_EVENT_ERROR          8
#define RA_SCI_EVENT_ALL            15

struct ra_i2c_handle
{
    struct rt_i2c_bus_device bus;
    char bus_name[RT_NAME_MAX];
    const i2c_master_cfg_t *i2c_cfg;
    void *i2c_ctrl;
    struct rt_event event;
};

static struct ra_i2c_handle ra_i2cs[] =
{
#ifdef BSP_USING_HW_I2C0
    {.bus_name = "i2c0", .i2c_cfg = &g_i2c_master0_cfg, .i2c_ctrl = &g_i2c_master0_ctrl,},
#endif
#ifdef BSP_USING_HW_I2C1
    {.bus_name = "i2c1", .i2c_cfg = &g_i2c_master1_cfg, .i2c_ctrl = &g_i2c_master1_ctrl,},
#endif
#ifdef BSP_USING_HW_I2C2
    {.bus_name = "i2c2", .i2c_cfg = &g_i2c_master2_cfg, .i2c_ctrl = &g_i2c_master2_ctrl,},
#endif
};

void i2c_master_callback(i2c_master_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (NULL != p_args)
    {
        /* capture callback event for validating the i2c transfer event*/
        struct ra_i2c_handle *obj = (struct ra_i2c_handle *)p_args->p_context;
        uint32_t event = 0;
        RT_ASSERT(obj != RT_NULL);
        switch (p_args->event)
        {
        case I2C_MASTER_EVENT_ABORTED:
            event |= RA_SCI_EVENT_ABORTED;
            break;
        case I2C_MASTER_EVENT_RX_COMPLETE:
            event |= RA_SCI_EVENT_RX_COMPLETE;
            break;
        case I2C_MASTER_EVENT_TX_COMPLETE:
            event |= RA_SCI_EVENT_TX_COMPLETE;
            break;
        }
        rt_event_send(&obj->event, event);
    }
    rt_interrupt_leave();
}

static rt_err_t validate_i2c_event(struct ra_i2c_handle *handle)
{
    rt_uint32_t event = 0;
    if (RT_EOK != rt_event_recv(&handle->event, RA_SCI_EVENT_ALL, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, (int32_t)rt_tick_from_millisecond(100), &event))
    {
        return -RT_ETIMEOUT;
    }
    if ((event & (RA_SCI_EVENT_ABORTED | RA_SCI_EVENT_ERROR)) == 0)
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
    fsp_err_t err = FSP_SUCCESS;
    bool restart = false;

    struct ra_i2c_handle *ra_i2c = rt_container_of(bus, struct ra_i2c_handle, bus);
    i2c_master_ctrl_t *master_ctrl = ra_i2c->i2c_ctrl;

    for (i = 0; i < num; i++)
    {
        if (msg[i].flags & RT_I2C_NO_START)
        {
            restart = true;
        }
        if (msg[i].flags & RT_I2C_ADDR_10BIT)
        {
            R_IIC_MASTER_SlaveAddressSet(master_ctrl, msg[i].addr, I2C_MASTER_ADDR_MODE_10BIT);
        }
        else
        {
            R_IIC_MASTER_SlaveAddressSet(master_ctrl, msg[i].addr, I2C_MASTER_ADDR_MODE_7BIT);
        }

        if (msg[i].flags & RT_I2C_RD)
        {
            err = R_IIC_MASTER_Read(master_ctrl, msg[i].buf, msg[i].len, restart);
            if (FSP_SUCCESS == err)
            {
                if (RT_EOK != validate_i2c_event(ra_i2c))
                {
                    LOG_E("POWER_CTL reg I2C read failed");
                    break;
                }
            }
            /* handle error */
            else
            {
                /* Write API returns itself is not successful */
                LOG_E("R_I2C_MASTER_Write API failed");
                break;
            }
        }
        else
        {
            err = R_IIC_MASTER_Write(master_ctrl, msg[i].buf, msg[i].len, restart);
            if (FSP_SUCCESS == err)
            {
                if (RT_EOK != validate_i2c_event(ra_i2c))
                {
                    LOG_E("POWER_CTL reg I2C write failed");
                    break;
                }
            }
            /* handle error */
            else
            {
                /* Write API returns itself is not successful */
                LOG_E("R_I2C_MASTER_Write API failed");
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
    for (rt_uint32_t i = 0; i < sizeof(ra_i2cs) / sizeof(ra_i2cs[0]); i++)
    {
        ra_i2cs[i].bus.ops = &ra_i2c_ops;
        ra_i2cs[i].bus.priv = 0;

        if (RT_EOK != rt_event_init(&ra_i2cs[i].event, ra_i2cs[i].bus_name, RT_IPC_FLAG_FIFO))
        {
            LOG_E("Init event failed");
            continue;
        }
        /* opening IIC master module */
        err = R_IIC_MASTER_Open(ra_i2cs[i].i2c_ctrl, ra_i2cs[i].i2c_cfg);
        if (FSP_SUCCESS != err)
        {
            LOG_E("R_I2C_MASTER_Open API failed,%d", err);
            continue;
        }
        err = R_IIC_MASTER_CallbackSet(ra_i2cs[i].i2c_ctrl, i2c_master_callback, &ra_i2cs[i], RT_NULL);
        /* handle error */
        if (FSP_SUCCESS != err)
        {
            LOG_E("R_I2C_CallbackSet API failed,%d", err);
            continue;
        }
        rt_i2c_bus_device_register(&ra_i2cs[i].bus, ra_i2cs[i].bus_name);
    }

    return 0;
}
INIT_DEVICE_EXPORT(ra_hw_i2c_init);

#endif /* BSP_USING_I2C */
