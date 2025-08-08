/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-10-23     zhangyan     first version
 *
 */
#include "rtconfig.h"
#include <rtdevice.h>
#include <string.h>
#define LOG_TAG      "i2c_drv_msg"
#include "drv_log.h"
#include "drv_i2c_msg.h"
#include "fi2c_msg.h"
#include "fi2c_msg_hw.h"
#include "fi2c_msg_master.h"
#include "fio_mux.h"
#include "drivers/dev_i2c.h"
#include "fparameters.h"
#ifdef RT_USING_SMART
    #include <ioremap.h>
#endif

/*Please define the length of the mem_addr of the device*/
#ifndef FI2C_DEVICE_MEMADDR_LEN
    #define FI2C_DEVICE_MEMADDR_LEN 2
#endif
#define I2C_TIMEOUT_MS 1000

struct phytium_i2c_msg_bus
{
    struct rt_i2c_bus_device device;
    FI2cMsgCtrl i2c_handle;
    struct rt_i2c_msg *msg;
    const char *name;
};

static rt_err_t i2c_msg_config(struct phytium_i2c_msg_bus *i2c_bus)
{
    RT_ASSERT(i2c_bus);
    FI2cMsgConfig input_cfg;
    const FI2cMsgConfig *config_p = NULL;
    FI2cMsgCtrl *instance_p = &i2c_bus->i2c_handle;
    rt_uint32_t cpu_id = rt_hw_cpu_id();
    FError ret = FI2C_MSG_SUCCESS;
    FIOPadSetI2CMux(instance_p->config.instance_id);
    /* Lookup default configs by instance id */
    config_p = FI2cMsgLookupConfig(instance_p->config.instance_id);
    input_cfg = *config_p;
#ifdef RT_USING_SMART
    input_cfg.msg.shmem = (uintptr)rt_ioremap((void *)input_cfg.msg.shmem, 0x1000);
    input_cfg.msg.regfile= (uintptr)rt_ioremap((void *)input_cfg.msg.regfile, 0x1000);
#endif
    /* Initialization */
    ret = FI2cMsgCfgInitialize(instance_p, &input_cfg);
    if (ret != FI2C_MSG_SUCCESS)
    {
        LOG_E("FI2cMsgCfgInitialize failed, ret = %d", ret);
        return -RT_ERROR;
    }
    instance_p->speed_mode = FI2C_STANDARD_SPEED;
    instance_p->timeout_ms = I2C_TIMEOUT_MS;
    instance_p->clk_clock_frequency = FI2C_CLK_FREQ_HZ;

    rt_hw_interrupt_set_target_cpus(instance_p->config.irq_num, cpu_id);
    rt_hw_interrupt_set_priority(instance_p->config.irq_num, instance_p->config.irq_prority);
    rt_hw_interrupt_install(instance_p->config.irq_num, FI2cMsgMasterRegfileIsr, instance_p, i2c_bus->name);
    rt_hw_interrupt_umask(instance_p->config.irq_num);

    ret = FI2cMsgMasterVirtProbe(instance_p);
    if (ret != FI2C_MSG_SUCCESS)
    {
        LOG_E("FI2cMsgMasterVirtProbe failed, ret = %d", ret);
        return ret;
    }
    return RT_EOK;
}

static rt_err_t phytium_i2c_set_speed(struct phytium_i2c_msg_bus *i2c_bus, rt_uint32_t speed)
{
    RT_ASSERT(i2c_bus);
    FI2cMsgCtrl *instance_p = &i2c_bus->i2c_handle;

    switch (speed)
    {
        case FI2C_SPEED_STANDARD_RATE:
            instance_p->speed_mode = FI2C_STANDARD_SPEED;
            break;
        case FI2C_SPEED_FAST_RATE:
            instance_p->speed_mode = FI2C_FAST_SPEED;
            break;
        case FI2C_SPEED_HIGH_RATE:
            instance_p->speed_mode = FI2C_HIGH_SPEED;
            break;

        default:
            return -RT_EIO;
    }

    FI2cMsgSetBusSpeed(instance_p, instance_p->speed_mode, TRUE);

    return RT_EOK;
}

static rt_err_t i2c_msg_bus_control(struct rt_i2c_bus_device *device, int cmd, void *args)
{
    RT_ASSERT(device);
    struct phytium_i2c_msg_bus *i2c_bus;
    i2c_bus = (struct phytium_i2c_msg_bus *)(device);
    FI2cMsgConfig *config_p;

    switch (cmd)
    {
        case RT_I2C_DEV_CTRL_CLK:
            phytium_i2c_set_speed(i2c_bus, *(rt_uint32_t *)args);
            break;
        case RT_I2C_DEV_CTRL_10BIT:

            break;
        default:
            return -RT_EIO;
    }

    return RT_EOK;
}

static rt_ssize_t i2c_msg_master_xfer(struct rt_i2c_bus_device *device, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    RT_ASSERT(device);
    u32 ret;
    struct rt_i2c_msg *pmsg;
    rt_ssize_t i;
    struct phytium_i2c_msg_bus *i2c_bus;
    i2c_bus = (struct phytium_i2c_msg_bus *)(device);
    FI2cMsgCtrl *instance_p = &i2c_bus->i2c_handle;

    for (i = 0; i < num; i++)
    {
        pmsg = &msgs[i];
        if (pmsg->flags & RT_I2C_RD)
        {
            /*When performing a read operation, first write to the input memaddr, and then read*/
            struct FI2cMsg msg[2];
            msg[0].addr = pmsg->addr;
            msg[0].flags = FI2C_MSG_WD;
            msg[0].len = FI2C_DEVICE_MEMADDR_LEN;
            msg[0].buf = pmsg->buf;

            msg[1].addr = pmsg->addr;
            msg[1].flags = FI2C_MSG_RD;
            msg[1].len = pmsg->len;
            msg[1].buf = pmsg->buf;
            ret = FI2cMsgMasterVirtXfer(instance_p, msg, 2);
            if (ret != FI2C_MSG_SUCCESS)
            {
                LOG_E("FI2cMsgMasterVirtProbe read failed, ret = %d", ret);
            }
        }
        else
        {
            struct FI2cMsg msg;
            msg.addr = pmsg->addr;
            msg.buf = pmsg->buf;
            msg.len = pmsg->len;
            msg.flags = FI2C_MSG_WD;
            ret = FI2cMsgMasterVirtXfer(instance_p, &msg, 1); /*num = 1 ,只需发送一次写命令*/
            if (ret != FI2C_MSG_SUCCESS)
            {
                LOG_E("FI2cMsgMasterVirtProbe write failed, ret = %d", ret);
            }
        }
    }

    return i;
}

static const struct rt_i2c_bus_device_ops _i2c_ops =
{
    .master_xfer        = i2c_msg_master_xfer,
    .slave_xfer         = NULL,
    .i2c_bus_control    = i2c_msg_bus_control
};

static int i2c_msg_controller_init(struct phytium_i2c_msg_bus *i2c_controller_bus)
{
    rt_err_t ret = RT_EOK;
    ret = i2c_msg_config(i2c_controller_bus);
    if (ret != RT_EOK)
    {
        LOG_E("I2C config failed.\n");

        return -RT_ERROR;
    }
    i2c_controller_bus->device.ops = &_i2c_ops;
    ret = rt_i2c_bus_device_register(&i2c_controller_bus->device, i2c_controller_bus->name);
    RT_ASSERT(RT_EOK == ret);
    LOG_D("I2C bus reg success.\n");

    return ret;
}

#if defined(RT_USING_I2C0_MSG)
    static struct phytium_i2c_msg_bus i2c_msg_controller0_bus;
#endif
#if defined(RT_USING_I2C1_MSG)
    static struct phytium_i2c_msg_bus i2c_msg_controller1_bus;
#endif
#if defined(RT_USING_I2C2_MSG)
    static struct phytium_i2c_msg_bus i2c_msg_controller2_bus;
#endif
#if defined(RT_USING_I2C3_MSG)
    static struct phytium_i2c_msg_bus i2c_msg_controller3_bus;
#endif

int rt_hw_i2c_msg_init(void)
{
#if defined(RT_USING_I2C0_MSG)
    i2c_msg_controller0_bus.name = "I2C0_MSG";
    i2c_msg_controller0_bus.i2c_handle.config.instance_id = FI2C0_MSG_ID;
    i2c_msg_controller_init(&i2c_msg_controller0_bus);
#endif
#if defined(RT_USING_I2C1_MSG)
    i2c_msg_controller1_bus.name = "I2C1_MSG";
    i2c_msg_controller1_bus.i2c_handle.config.instance_id = FI2C1_MSG_ID;
    i2c_msg_controller_init(&i2c_msg_controller1_bus);
#endif
#if defined(RT_USING_I2C2_MSG)
    i2c_msg_controller2_bus.name = "I2C2_MSG";
    i2c_msg_controller2_bus.i2c_handle.config.instance_id = FI2C2_MSG_ID;
    i2c_msg_controller_init(&i2c_msg_controller2_bus);
#endif

#if defined(RT_USING_I2C3_MSG)
    i2c_msg_controller3_bus.name = "I2C3_MSG";
    i2c_msg_controller3_bus.i2c_handle.config.instance_id = FI2C3_MSG_ID;
    i2c_msg_controller_init(&i2c_msg_controller3_bus);
#endif

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_msg_init);
