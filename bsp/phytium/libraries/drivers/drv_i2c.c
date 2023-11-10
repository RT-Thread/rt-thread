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
#if defined BSP_USING_I2C

#define LOG_TAG      "i2c_drv"
#include "drv_log.h"
#include "drv_i2c.h"
#include "fi2c.h"
#include "fi2c_hw.h"
#include "fio_mux.h"
#include "fmio_hw.h"
#include "fmio.h"
#include "drivers/i2c.h"
#include "fparameters.h"
#ifdef RT_USING_SMART
    #include <ioremap.h>
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
static struct phytium_i2c_bus i2c_bus[FI2C_NUM] =
{
    {
        .name = "I2C0",
        .i2c_handle.config.instance_id = 0,
    },
    {
        .name = "I2C1",
        .i2c_handle.config.instance_id = 1,
    },
    {
        .name = "I2C2",
        .i2c_handle.config.instance_id = 2,
    },
};
#endif

#if defined(I2C_USE_MIO)
static struct phytium_i2c_bus i2c_mio_bus[FMIO_NUM] =
{
#if defined(TARGET_E2000D) ||defined(TARGET_E2000Q)
    {
        .name = "MIO0",
        .i2c_handle.config.instance_id = 0,
    },
    {
        .name = "MIO1",
        .i2c_handle.config.instance_id = 1,
    },
    {
        .name = "MIO2",
        .i2c_handle.config.instance_id = 2,
    },
    {
        .name = "MIO3",
        .i2c_handle.config.instance_id = 3,
    },
    {
        .name = "MIO4",
        .i2c_handle.config.instance_id = 4,
    },
    {
        .name = "MIO5",
        .i2c_handle.config.instance_id = 5,
    },
    {
        .name = "MIO6",
        .i2c_handle.config.instance_id = 6,
    },
    {
        .name = "MIO7",
        .i2c_handle.config.instance_id = 7,
    },
    {
        .name = "MIO8",
        .i2c_handle.config.instance_id = 8,
    },
    {
        .name = "MIO9",
        .i2c_handle.config.instance_id = 9,
    },
    {
        .name = "MIO10",
        .i2c_handle.config.instance_id = 10,
    },
    {
        .name = "MIO11",
        .i2c_handle.config.instance_id = 11,
    },
    {
        .name = "MIO12",
        .i2c_handle.config.instance_id = 12,
    },
    {
        .name = "MIO13",
        .i2c_handle.config.instance_id = 13,
    },
    {
        .name = "MIO14",
        .i2c_handle.config.instance_id = 14,
    },
    {
        .name = "MIO15",
        .i2c_handle.config.instance_id = 15,
    },
#elif defined(TARGET_PHYTIUMPI)
    {
        .name = "MIO0",
        .i2c_handle.config.instance_id = 0,
    },
    {
        .name = "MIO1",
        .i2c_handle.config.instance_id = 1,
    },
    {
        .name = "MIO2",
        .i2c_handle.config.instance_id = 2,
    },
    {
        .name = "MIO10",
        .i2c_handle.config.instance_id = 10,
    },
#endif
};

#endif

#if defined(I2C_USE_CONTROLLER)
static rt_err_t i2c_config(struct phytium_i2c_bus *i2c_bus)
{
    RT_ASSERT(i2c_bus);
    FI2cConfig input_cfg;
    const FI2cConfig *config_p = NULL;
    FI2c *instance_p = &i2c_bus->i2c_handle;
    FError ret = FI2C_SUCCESS;
    u32 *cpu_id;

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

        return RT_ERROR;
    }

    /*Enable i2c interrupt*/
    GetCpuId(&cpu_id);
    rt_hw_interrupt_set_target_cpus(i2c_bus->i2c_handle.config.irq_num, cpu_id);
    rt_hw_interrupt_set_priority(i2c_bus->i2c_handle.config.irq_num, 16);
    rt_hw_interrupt_install(i2c_bus->i2c_handle.config.irq_num, FI2cMasterIntrHandler, &(i2c_bus->i2c_handle), i2c_bus->name);
    rt_hw_interrupt_umask(i2c_bus->i2c_handle.config.irq_num);

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
    u32 *cpu_id;

    mio_handle.config = *FMioLookupConfig(instance_p->config.instance_id);
#ifdef RT_USING_SMART
    mio_handle.config.func_base_addr = (uintptr)rt_ioremap((void *)mio_handle.config.func_base_addr, 0x1200);
    mio_handle.config.mio_base_addr = (uintptr)rt_ioremap((void *)mio_handle.config.mio_base_addr, 0x200);
#endif
    ret = FMioFuncInit(&mio_handle, FMIO_FUNC_SET_I2C);
    if (ret != FT_SUCCESS)
    {
        LOG_E("MIO initialize error.");
        return RT_ERROR;
    }

    FIOPadSetMioMux(instance_p->config.instance_id);

    config_p = FI2cLookupConfig(FI2C_DEFAULT_ID);
    if (NULL == config_p)
    {
        LOG_E("Config of mio instance %d non found.", instance_p->config.instance_id);
        return RT_ERROR;
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
        return RT_ERROR;
    }

    /*Enable i2c interrupt*/
    GetCpuId(&cpu_id);
    rt_hw_interrupt_set_target_cpus(i2c_bus->i2c_handle.config.irq_num, cpu_id);
    rt_hw_interrupt_set_priority(i2c_bus->i2c_handle.config.irq_num, 16);
    rt_hw_interrupt_install(i2c_bus->i2c_handle.config.irq_num, FI2cMasterIntrHandler, &(i2c_bus->i2c_handle), i2c_bus->name);
    rt_hw_interrupt_umask(i2c_bus->i2c_handle.config.irq_num);

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
        return RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t i2c_bus_control(struct rt_i2c_bus_device *device, int cmd, void *args)
{
    RT_ASSERT(device);
    struct phytium_i2c_bus *i2c_bus;
    i2c_bus = (struct phytium_i2c_bus *)(device);

    switch (cmd)
    {
        case RT_I2C_DEV_CTRL_CLK:
            phytium_i2c_set_speed(i2c_bus, *(rt_uint32_t *)args);
            break;
        case RT_I2C_DEV_CTRL_10BIT:
            FI2cConfig *config_p = &i2c_bus->i2c_handle.config;
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
    struct phytium_i2c_bus *i2c_bus;
    i2c_bus = (struct phytium_i2c_bus *)(device);
    u8 mem_addr = msgs->buf[0];

    for (int i = 0; i < num; i++)
    {
        pmsg = i2c_bus->msg = &msgs[i];
        i2c_bus->i2c_handle.config.slave_addr = pmsg->addr;
        if (pmsg->flags & RT_I2C_RD)
        {
            /*Under the default configuration of interrupts, only one byte can be read or written at a time*/
            ret = FI2cMasterReadIntr(&i2c_bus->i2c_handle, mem_addr, 1, &pmsg->buf[0], 1);
            if (ret != FI2C_SUCCESS)
            {
                LOG_E("I2C master read failed!\n");
                return RT_ERROR;
            }
        }
        else
        {
            /*Under the default configuration of interrupts, only one byte can be read or written at a time*/
            ret = FI2cMasterWriteIntr(&i2c_bus->i2c_handle, mem_addr, 1, &pmsg->buf[1], 1);
            if (ret != FI2C_SUCCESS)
            {
                LOG_E("I2C master write failed!\n");
                return RT_ERROR;
            }
        }
    }

    return RT_EOK;
}

static const struct rt_i2c_bus_device_ops _i2c_ops =
{
    .master_xfer        = i2c_master_xfer,
    .slave_xfer         = NULL,
    .i2c_bus_control    = i2c_bus_control
};

#if defined(I2C_USE_CONTROLLER)
static int i2c_controller_init(u32 i2c_id)
{
    u32 ret = RT_EOK;
    ret = i2c_config(&i2c_bus[i2c_id]);
    if (ret != FI2C_SUCCESS)
    {
        LOG_E("I2C config failed.\n");

        return RT_ERROR;
    }
    i2c_bus[i2c_id].device.ops = &_i2c_ops;
    ret = rt_i2c_bus_device_register(&i2c_bus[i2c_id].device, i2c_bus[i2c_id].name);
    LOG_D("I2C bus reg success.\n");
    RT_ASSERT(RT_EOK == ret);

    return ret;
}
#endif

#if defined(I2C_USE_MIO)
static int i2c_mio_init(u32 i2c_mio_id)
{
    u32 ret = RT_EOK;
    ret = i2c_mio_config(&i2c_mio_bus[i2c_mio_id]);
    if (ret != FI2C_SUCCESS)
    {
        LOG_E("I2C mio config failed.\n");

        return RT_ERROR;
    }
    i2c_mio_bus[i2c_mio_id].device.ops = &_i2c_ops;
    ret = rt_i2c_bus_device_register(&i2c_mio_bus[i2c_mio_id].device, i2c_mio_bus[i2c_mio_id].name);
    LOG_D("I2C mio bus reg success.\n");
    RT_ASSERT(RT_EOK == ret);

    return ret;
}
#endif

int rt_hw_i2c_init(void)
{
    rt_err_t ret = RT_EOK;
#if defined(I2C_USE_CONTROLLER)

#if defined(RT_USING_I2C0)
    i2c_controller_init(FI2C0_ID);
#endif
#if defined(RT_USING_I2C1)
    i2c_controller_init(FI2C1_ID);
#endif
#if defined(RT_USING_I2C2)
    i2c_controller_init(FI2C2_ID);
#endif

#endif

#if defined(I2C_USE_MIO)

#if defined(RT_USING_MIO0)
    i2c_mio_init(FMIO0_ID);
#endif
#if defined(RT_USING_MIO1)
    i2c_mio_init(FMIO1_ID);
#endif
#if defined(RT_USING_MIO2)
    i2c_mio_init(FMIO2_ID);
#endif
#if defined(RT_USING_MIO3)
    i2c_mio_init(FMIO3_ID);
#endif
#if defined(RT_USING_MIO4)
    i2c_mio_init(FMIO4_ID);
#endif
#if defined(RT_USING_MIO5)
    i2c_mio_init(FMIO5_ID);
#endif
#if defined(RT_USING_MIO6)
    i2c_mio_init(FMIO6_ID);
#endif
#if defined(RT_USING_MIO7)
    i2c_mio_init(FMIO7_ID);
#endif
#if defined(RT_USING_MIO8)
    i2c_mio_init(FMIO8_ID);
#endif
#if defined(RT_USING_MIO9)
    i2c_mio_init(FMIO9_ID);
#endif
#if defined(RT_USING_MIO10)
    i2c_mio_init(FMIO10_ID);
#endif
#if defined(RT_USING_MIO11)
    i2c_mio_init(FMIO11_ID);
#endif
#if defined(RT_USING_MIO12)
    i2c_mio_init(FMIO12_ID);
#endif
#if defined(RT_USING_MIO13)
    i2c_mio_init(FMIO13_ID);
#endif
#if defined(RT_USING_MIO14)
    i2c_mio_init(FMIO14_ID);
#endif
#if defined(RT_USING_MIO15)
    i2c_mio_init(FMIO15_ID);
#endif

#endif

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

static struct rt_i2c_bus_device *i2c_test_bus = RT_NULL;     /* I2C总线设备句柄 */

int i2c_sample(int argc, char *argv[])
{
    char name[RT_NAME_MAX];
    rt_strncpy(name, "MIO15", RT_NAME_MAX);
    i2c_test_bus = (struct rt_i2c_bus_device *)rt_device_find(name);

    /*0x02 is the mem_addr, need to be written in buf[0]*/
    rt_uint8_t read_buf[2] = {0x02, 0x0};
    rt_uint8_t write_buf[2] = {0x02, 0x01};
    if (i2c_test_bus == RT_NULL)
    {
        rt_kprintf("can't find %s device!\n", name);
    }
    else
    {
        rt_kprintf("find %s device!!!!\n", name);
    }

    struct rt_i2c_msg read_msgs;
    read_msgs.addr = 0x6B;
    read_msgs.flags = RT_I2C_RD;
    read_msgs.buf = read_buf;
    read_msgs.len = 1;
    rt_i2c_transfer(i2c_test_bus, &read_msgs, 1);
    rt_thread_mdelay(5);
    rt_kprintf("read_buf = %x\n", *read_msgs.buf);

    struct rt_i2c_msg write_msgs;
    write_msgs.addr = 0x6B;
    write_msgs.flags = RT_I2C_WR;
    write_msgs.buf = write_buf;
    write_msgs.len = 1;
    rt_i2c_transfer(i2c_test_bus, &write_msgs, 1);
    rt_thread_mdelay(5);
    read_buf[0] = 0x02;
    rt_i2c_transfer(i2c_test_bus, &read_msgs, 1);
    rt_thread_mdelay(5);
    rt_kprintf("read_buf = %x\n", *read_msgs.buf);

    return RT_EOK;
}

MSH_CMD_EXPORT(i2c_sample, i2c device sample);

#endif