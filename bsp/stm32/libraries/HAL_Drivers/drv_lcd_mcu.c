/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-01     tyustli      the first version
 *
 */

#include "board.h"
#include <rtthread.h>

#define DBG_TAG "drv_mcu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

typedef struct
{
    rt_uint16_t lcd_cmd;
    rt_uint16_t lcd_data;
} lcd_typedef;

struct intf_mcu_device
{
    struct rt_lcd_intf  intf;
    FMC_NORSRAM_TimingTypeDef FMC_ReadWriteTim;
    FMC_NORSRAM_TimingTypeDef FMC_WriteTim;
    SRAM_HandleTypeDef SRAM_Handler;
    lcd_typedef *lcd_addr;
};
static struct intf_mcu_device lcd_intf;

static rt_err_t _lcd_intf_write_cmd(struct rt_lcd_intf *device, void *cmd, rt_uint32_t len)
{
    rt_uint32_t *write_cmd;
    struct intf_mcu_device *mcu_device;
    RT_ASSERT(device);

    mcu_device = (struct intf_mcu_device *)device;
    write_cmd = (rt_uint32_t *)cmd;
    while(len--)
    {
        mcu_device->lcd_addr->lcd_cmd = *write_cmd++;
    }

    return RT_EOK;
}

static rt_err_t _lcd_intf_write_data(struct rt_lcd_intf *device, void *data, rt_uint32_t len)
{
    rt_uint32_t *write_data;
    struct intf_mcu_device *mcu_device;
    RT_ASSERT(device);

    mcu_device = (struct intf_mcu_device *)device;
    write_data = (rt_uint32_t *)data;
    while(len--)
    {
        mcu_device->lcd_addr->lcd_data = *write_data++;
    }

    return RT_EOK;
}

static rt_err_t _lcd_intf_read_data(struct rt_lcd_intf *device, rt_uint32_t read_reg, void *read_data)
{
    struct intf_mcu_device *mcu_device;
    RT_ASSERT(device);

    mcu_device = (struct intf_mcu_device *)device;
    *(rt_uint32_t *)read_data = mcu_device->lcd_addr->lcd_data;

    return RT_EOK;
}

static rt_err_t _lcd_intf_write_reg(struct rt_lcd_intf *device, rt_uint32_t write_reg, rt_uint32_t write_data)
{
    struct intf_mcu_device *mcu_device;
    RT_ASSERT(device);

    mcu_device = (struct intf_mcu_device *)device;
    mcu_device->lcd_addr->lcd_cmd = write_reg;
    mcu_device->lcd_addr->lcd_data = write_data;

    return RT_EOK;
}

static rt_err_t _lcd_intf_config(struct rt_lcd_intf *device, struct rt_lcd_intf_config *config)
{
    struct intf_mcu_device *mcu_device;
    RT_ASSERT(device);

    mcu_device = (struct intf_mcu_device *)device;
    mcu_device->lcd_addr = (lcd_typedef *)config->addr;
    mcu_device->SRAM_Handler.Instance = FMC_NORSRAM_DEVICE;
    mcu_device->SRAM_Handler.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
    mcu_device->SRAM_Handler.Init.NSBank = config->channel;
    mcu_device->SRAM_Handler.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
    mcu_device->SRAM_Handler.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
    mcu_device->SRAM_Handler.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
    mcu_device->SRAM_Handler.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
    mcu_device->SRAM_Handler.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
    mcu_device->SRAM_Handler.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
    mcu_device->SRAM_Handler.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
    mcu_device->SRAM_Handler.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
    mcu_device->SRAM_Handler.Init.ExtendedMode = FMC_EXTENDED_MODE_ENABLE;
    mcu_device->SRAM_Handler.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
    mcu_device->SRAM_Handler.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
    mcu_device->SRAM_Handler.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ASYNC;

    mcu_device->FMC_ReadWriteTim.AddressSetupTime = 0x0F;
    mcu_device->FMC_ReadWriteTim.AddressHoldTime = 0x00;
    mcu_device->FMC_ReadWriteTim.DataSetupTime = 0x46;
    mcu_device->FMC_ReadWriteTim.AccessMode = FMC_ACCESS_MODE_A;

    mcu_device->FMC_WriteTim.AddressSetupTime = 0x0F;
    mcu_device->FMC_WriteTim.AddressHoldTime = 0x00;
    mcu_device->FMC_WriteTim.DataSetupTime = 0x0F;
    mcu_device->FMC_WriteTim.AccessMode = FMC_ACCESS_MODE_A;
    HAL_SRAM_Init(&mcu_device->SRAM_Handler, &mcu_device->FMC_ReadWriteTim, &mcu_device->FMC_WriteTim);
    rt_thread_mdelay(50);
    FMC_Bank1E->BWTR[0] &= ~(0XF << 0);
    FMC_Bank1E->BWTR[0] &= ~(0XF << 8);
    FMC_Bank1E->BWTR[0] |= 4 << 0;
    FMC_Bank1E->BWTR[0] |= 4 << 8;

    return RT_EOK;
}

static struct rt_lcd_intf_ops _lcd_intf_ops =
{
    _lcd_intf_write_cmd,
    _lcd_intf_write_data,
    _lcd_intf_read_data,
    _lcd_intf_write_reg,
    _lcd_intf_config,
};

int rt_lcd_intf_init(void)
{
    rt_err_t result;

    result = RT_EOK;

    result = rt_lcd_intf_register(&lcd_intf.intf, "lcd_intf", &_lcd_intf_ops, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("register lcd interface device failed error code = %d\n", result);
    }

    return result;
}

INIT_PREV_EXPORT(rt_lcd_intf_init);

/****************** end of file *******************/
