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
#define LOG_TAG      "i2c_drv"
#include "drv_log.h"
#include "drv_i2c.h"
#include "fi2c.h"
#include "fi2c_hw.h"
#include "fio_mux.h"
#include "fmio_hw.h"
#include "fmio.h"
#include "drivers/dev_i2c.h"
#include "fparameters.h"
#ifdef RT_USING_SMART
    #include <ioremap.h>
#endif

/*Please define the length of the mem_addr of the device*/
#ifndef FI2C_DEVICE_MEMADDR_LEN
    #define FI2C_DEVICE_MEMADDR_LEN 2
#endif
#define FI2C_DEFAULT_ID 0
#define I2C_USE_MIO
#if defined(I2C_USE_MIO)
    static FMioCtrl mio_handle;
#endif

struct phytium_i2c_bus
{
    struct rt_i2c_bus_device device;
    FI2c i2c_handle;
    struct rt_i2c_msg *msg;
    const char *name;
};

#if defined(I2C_USE_CONTROLLER)
static rt_err_t i2c_config(struct phytium_i2c_bus *i2c_bus)
{
    RT_ASSERT(i2c_bus);
    FI2cConfig input_cfg;
    const FI2cConfig *config_p = NULL;
    FI2c *instance_p = &i2c_bus->i2c_handle;
    FError ret = FI2C_SUCCESS;

    /* Lookup default configs by instance id */
    config_p = FI2cLookupConfig(instance_p->config.instance_id);
    input_cfg = *config_p;
#ifdef RT_USING_SMART
    input_cfg.base_addr = (uintptr)rt_ioremap((void *)input_cfg.base_addr, 0x1000);
#endif
    input_cfg.speed_rate = FI2C_SPEED_STANDARD_RATE;
    input_cfg.work_mode = FI2C_MASTER;
    FI2cDeInitialize(&i2c_bus->i2c_handle);
    /* Initialization */
    ret = FI2cCfgInitialize(instance_p, &input_cfg);
    if (ret != FI2C_SUCCESS)
    {
        LOG_E("Init master I2c failed, ret: 0x%x", ret);

        return -RT_ERROR;
    }

    return RT_EOK;
}
#endif

#if defined(I2C_USE_MIO)
static rt_err_t i2c_mio_config(struct phytium_i2c_bus *i2c_bus)
{
    RT_ASSERT(i2c_bus);
    FI2cConfig input_cfg;
    const FI2cConfig *config_p = NULL;
    FI2c *instance_p = &i2c_bus->i2c_handle;
    FError ret = FI2C_SUCCESS;

    mio_handle.config = *FMioLookupConfig(instance_p->config.instance_id);
#ifdef RT_USING_SMART
    mio_handle.config.func_base_addr = (uintptr)rt_ioremap((void *)mio_handle.config.func_base_addr, 0x1200);
    mio_handle.config.mio_base_addr = (uintptr)rt_ioremap((void *)mio_handle.config.mio_base_addr, 0x200);
#endif
    ret = FMioFuncInit(&mio_handle, FMIO_FUNC_SET_I2C);
    if (ret != FT_SUCCESS)
    {
        LOG_E("MIO initialize error.");
        return -RT_ERROR;
    }

    FIOPadSetMioMux(instance_p->config.instance_id);

    config_p = FI2cLookupConfig(FI2C_DEFAULT_ID);
    if (NULL == config_p)
    {
        LOG_E("Config of mio instance %d non found.", instance_p->config.instance_id);
        return -RT_ERROR;
    }

    input_cfg = *config_p;
    input_cfg.instance_id = instance_p->config.instance_id;
    input_cfg.base_addr = FMioFuncGetAddress(&mio_handle, FMIO_FUNC_SET_I2C);
    input_cfg.irq_num = FMioFuncGetIrqNum(&mio_handle, FMIO_FUNC_SET_I2C);
    input_cfg.ref_clk_hz = FMIO_CLK_FREQ_HZ;
    input_cfg.speed_rate = FI2C_SPEED_STANDARD_RATE;
    ret = FI2cCfgInitialize(&i2c_bus->i2c_handle, &input_cfg);
    if (FI2C_SUCCESS != ret)
    {
        LOG_E("Init mio master failed, ret: 0x%x", ret);
        return -RT_ERROR;
    }
    mio_handle.is_ready = 0;
    rt_memset(&mio_handle, 0, sizeof(mio_handle));

    return RT_EOK;
}
#endif

static rt_err_t phytium_i2c_set_speed(struct phytium_i2c_bus *i2c_bus, rt_uint32_t speed)
{
    RT_ASSERT(i2c_bus);
    u32 ret;
    uintptr base_addr = i2c_bus->i2c_handle.config.base_addr;

    ret = FI2cSetSpeed(base_addr, speed);
    if (ret != FI2C_SUCCESS)
    {
        LOG_E("Set i2c speed failed!\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t i2c_bus_control(struct rt_i2c_bus_device *device, int cmd, void *args)
{
    RT_ASSERT(device);
    struct phytium_i2c_bus *i2c_bus;
    i2c_bus = (struct phytium_i2c_bus *)(device);
    FI2cConfig *config_p;

    switch (cmd)
    {
        case RT_I2C_DEV_CTRL_CLK:
            phytium_i2c_set_speed(i2c_bus, *(rt_uint32_t *)args);
            break;
        case RT_I2C_DEV_CTRL_10BIT:
            config_p = &i2c_bus->i2c_handle.config;
            config_p->use_7bit_addr = FALSE;
            FI2cCfgInitialize(&i2c_bus->i2c_handle, config_p);
            break;
        default:
            return -RT_EIO;
    }

    return RT_EOK;
}

static rt_ssize_t i2c_master_xfer(struct rt_i2c_bus_device *device, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    RT_ASSERT(device);
    u32 ret;
    struct rt_i2c_msg *pmsg;
    rt_ssize_t i;
    struct phytium_i2c_bus *i2c_bus;
    i2c_bus = (struct phytium_i2c_bus *)(device);
    uintptr mem_addr = 0;

    for (i = 0; i < num; i++)
    {
        pmsg = &msgs[i];
        for (u32 j = 0; j <FI2C_DEVICE_MEMADDR_LEN; j++)
        {
            mem_addr |= msgs[i].buf[j] << (8 * (FI2C_DEVICE_MEMADDR_LEN - 1 - j));
        }

        i2c_bus->i2c_handle.config.slave_addr = pmsg->addr;

        if (pmsg->flags & RT_I2C_RD)
        {
            rt_thread_delay(100);
            ret = FI2cMasterReadPoll(&i2c_bus->i2c_handle, mem_addr, FI2C_DEVICE_MEMADDR_LEN, &pmsg->buf[0], pmsg->len - FI2C_DEVICE_MEMADDR_LEN);
            if (ret != FI2C_SUCCESS)
            {
                LOG_E("I2C master read failed!\n");
                return -RT_ERROR;
            }
        }
        else
        {
            rt_thread_delay(100);
            ret = FI2cMasterWritePoll(&i2c_bus->i2c_handle, mem_addr, FI2C_DEVICE_MEMADDR_LEN, &pmsg->buf[FI2C_DEVICE_MEMADDR_LEN], pmsg->len - FI2C_DEVICE_MEMADDR_LEN);
            if (ret != FI2C_SUCCESS)
            {
                LOG_E("I2C master write failed!\n");
                return -RT_ERROR;
            }
        }
    }

    return i;
}

static const struct rt_i2c_bus_device_ops _i2c_ops =
{
    .master_xfer        = i2c_master_xfer,
    .slave_xfer         = NULL,
    .i2c_bus_control    = i2c_bus_control
};

#if defined(I2C_USE_CONTROLLER)
static int i2c_controller_init(struct phytium_i2c_bus *i2c_controller_bus)
{
    rt_err_t ret = RT_EOK;
    ret = i2c_config(i2c_controller_bus);
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
#endif

#if defined(I2C_USE_MIO)
static int i2c_mio_init(struct phytium_i2c_bus *i2c_mio_bus)
{
    rt_err_t ret = RT_EOK;
    ret = i2c_mio_config(i2c_mio_bus);
    if (ret != RT_EOK)
    {
        LOG_E("I2C mio config failed.\n");

        return -RT_ERROR;
    }
    i2c_mio_bus->device.ops = &_i2c_ops;
    ret = rt_i2c_bus_device_register(&i2c_mio_bus->device, i2c_mio_bus->name);
    RT_ASSERT(RT_EOK == ret);
    LOG_D("I2C mio bus reg success.\n");

    return ret;
}
#endif

#if defined(RT_USING_I2C0)
    static struct phytium_i2c_bus i2c_controller0_bus;
#endif
#if defined(RT_USING_I2C1)
    static struct phytium_i2c_bus i2c_controller1_bus;
#endif
#if defined(RT_USING_I2C2)
    static struct phytium_i2c_bus i2c_controller2_bus;
#endif

#if defined(RT_USING_MIO0)
    static struct phytium_i2c_bus i2c_mio0_bus;
#endif
#if defined(RT_USING_MIO1)
    static struct phytium_i2c_bus i2c_mio1_bus;
#endif
#if defined(RT_USING_MIO2)
    static struct phytium_i2c_bus i2c_mio2_bus;
#endif
#if defined(RT_USING_MIO3)
    static struct phytium_i2c_bus i2c_mio3_bus;
#endif
#if defined(RT_USING_MIO4)
    static struct phytium_i2c_bus i2c_mio4_bus;
#endif
#if defined(RT_USING_MIO5)
    static struct phytium_i2c_bus i2c_mio5_bus;
#endif
#if defined(RT_USING_MIO6)
    static struct phytium_i2c_bus i2c_mio6_bus;
#endif
#if defined(RT_USING_MIO7)
    static struct phytium_i2c_bus i2c_mio7_bus;
#endif
#if defined(RT_USING_MIO8)
    static struct phytium_i2c_bus i2c_mio8_bus;
#endif
#if defined(RT_USING_MIO9)
    static struct phytium_i2c_bus i2c_mio9_bus;
#endif
#if defined(RT_USING_MIO10)
    static struct phytium_i2c_bus i2c_mio10_bus;
#endif
#if defined(RT_USING_MIO11)
    static struct phytium_i2c_bus i2c_mio11_bus;
#endif
#if defined(RT_USING_MIO12)
    static struct phytium_i2c_bus i2c_mio12_bus;
#endif
#if defined(RT_USING_MIO13)
    static struct phytium_i2c_bus i2c_mio13_bus;
#endif
#if defined(RT_USING_MIO14)
    static struct phytium_i2c_bus i2c_mio14_bus;
#endif
#if defined(RT_USING_MIO15)
    static struct phytium_i2c_bus i2c_mio15_bus;
#endif

int rt_hw_i2c_init(void)
{
#if defined(RT_USING_I2C0)
    i2c_controller0_bus.name = "I2C0";
    i2c_controller0_bus.i2c_handle.config.instance_id = FI2C0_ID;
    i2c_controller_init(&i2c_controller0_bus);
#endif
#if defined(RT_USING_I2C1)
    i2c_controller1_bus.name = "I2C1";
    i2c_controller1_bus.i2c_handle.config.instance_id = FI2C1_ID;
    i2c_controller_init(&i2c_controller1_bus);
#endif
#if defined(RT_USING_I2C2)
    i2c_controller2_bus.name = "I2C2";
    i2c_controller2_bus.i2c_handle.config.instance_id = FI2C2_ID;
    i2c_controller_init(&i2c_controller2_bus);
#endif

#if defined(RT_USING_MIO0)
    i2c_mio0_bus.name = "MIO0";
    i2c_mio0_bus.i2c_handle.config.instance_id = FMIO0_ID;
    i2c_mio_init(&i2c_mio0_bus);
#endif
#if defined(RT_USING_MIO1)
    i2c_mio1_bus.name = "MIO1";
    i2c_mio1_bus.i2c_handle.config.instance_id = FMIO1_ID;
    i2c_mio_init(&i2c_mio1_bus);
#endif
#if defined(RT_USING_MIO2)
    i2c_mio2_bus.name = "MIO2";
    i2c_mio2_bus.i2c_handle.config.instance_id = FMIO2_ID;
    i2c_mio_init(&i2c_mio2_bus);
#endif
#if defined(RT_USING_MIO3)
    i2c_mio3_bus.name = "MIO3";
    i2c_mio3_bus.i2c_handle.config.instance_id = FMIO3_ID;
    i2c_mio_init(&i2c_mio3_bus);
#endif
#if defined(RT_USING_MIO4)
    i2c_mio4_bus.name = "MIO4";
    i2c_mio4_bus.i2c_handle.config.instance_id = FMIO4_ID;
    i2c_mio_init(&i2c_mio4_bus);
#endif
#if defined(RT_USING_MIO5)
    i2c_mio5_bus.name = "MIO5";
    i2c_mio5_bus.i2c_handle.config.instance_id = FMIO5_ID;
    i2c_mio_init(&i2c_mio5_bus);
#endif
#if defined(RT_USING_MIO6)
    i2c_mio6_bus.name = "MIO6";
    i2c_mio6_bus.i2c_handle.config.instance_id = FMIO6_ID;
    i2c_mio_init(&i2c_mio6_bus);
#endif
#if defined(RT_USING_MIO7)
    i2c_mio7_bus.name = "MIO2";
    i2c_mio7_bus.i2c_handle.config.instance_id = FMIO7_ID;
    i2c_mio_init(&i2c_mio7_bus);
#endif
#if defined(RT_USING_MIO8)
    i2c_mio8_bus.name = "MIO8";
    i2c_mio8_bus.i2c_handle.config.instance_id = FMIO8_ID;
    i2c_mio_init(&i2c_mio8_bus);
#endif
#if defined(RT_USING_MIO9)
    i2c_mio9_bus.name = "MIO9";
    i2c_mio9_bus.i2c_handle.config.instance_id = FMIO9_ID;
    i2c_mio_init(&i2c_mio9_bus);
#endif
#if defined(RT_USING_MIO10)
    i2c_mio10_bus.name = "MIO10";
    i2c_mio10_bus.i2c_handle.config.instance_id = FMIO10_ID;
    i2c_mio_init(&i2c_mio10_bus);
#endif
#if defined(RT_USING_MIO11)
    i2c_mio11_bus.name = "MIO11";
    i2c_mio11_bus.i2c_handle.config.instance_id = FMIO11_ID;
    i2c_mio_init(&i2c_mio11_bus);
#endif
#if defined(RT_USING_MIO12)
    i2c_mio12_bus.name = "MIO12";
    i2c_mio12_bus.i2c_handle.config.instance_id = FMIO12_ID;
    i2c_mio_init(&i2c_mio12_bus);
#endif
#if defined(RT_USING_MIO13)
    i2c_mio13_bus.name = "MIO13";
    i2c_mio13_bus.i2c_handle.config.instance_id = FMIO13_ID;
    i2c_mio_init(&i2c_mio13_bus);
#endif
#if defined(RT_USING_MIO14)
    i2c_mio14_bus.name = "MIO14";
    i2c_mio14_bus.i2c_handle.config.instance_id = FMIO14_ID;
    i2c_mio_init(&i2c_mio14_bus);
#endif
#if defined(RT_USING_MIO15)
    i2c_mio15_bus.name = "MIO15";
    i2c_mio15_bus.i2c_handle.config.instance_id = FMIO15_ID;
    i2c_mio_init(&i2c_mio15_bus);
#endif

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);
