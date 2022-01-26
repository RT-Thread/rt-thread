/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-19     zylx         first version
 */

#include "board.h"

#ifdef BSP_USING_EXT_FMC_IO

//#define DRV_DEBUG
#define LOG_TAG             "drv.ext_io"
#include <drv_log.h>

#include "drv_ext_io.h"
#define  HC574_PORT  *(volatile rt_uint32_t *)0x64001000

volatile rt_uint32_t HC574_state = 0;

void HC574_SetPin(rt_uint32_t _pin, uint8_t _value)
{
    if (_value == 0)
    {
        HC574_state &= (~_pin);
    }
    else
    {
        HC574_state |= _pin;
    }

    HC574_PORT = HC574_state;
}

rt_uint8_t HC574_GetPin(rt_uint32_t _pin)
{
    if (HC574_state & _pin)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static void HC574_Config_FMC(void)
{
    FMC_NORSRAM_TimingTypeDef timing = {0};
    SRAM_HandleTypeDef sram2 = {0};

    /*
        For LCD compatibility，select 3-0-6-1-0-0
        3-0-5-1-0-0  : RD high level 75ns，low level 50ns. Read 8 channels of data into memory in 1us.
        1-0-1-1-0-0  : RD high level 75ns，low level 12ns，trailing edge 12ns.
    */
    /* FMC_Bank1_NORSRAM2 configuration */
    timing.AddressSetupTime = 3;
    timing.AddressHoldTime = 0;
    timing.DataSetupTime = 6;
    timing.BusTurnAroundDuration = 1;
    timing.CLKDivision = 0;
    timing.DataLatency = 0;
    timing.AccessMode = FMC_ACCESS_MODE_A;

    /*
     LCD configured as follow:
        - Data/Address MUX = Disable
        - Memory Type = SRAM
        - Data Width = 32bit
        - Write Operation = Enable
        - Extended Mode = Enable
        - Asynchronous Wait = Disable
    */
    sram2.Instance = FMC_NORSRAM_DEVICE;
    sram2.Extended = FMC_NORSRAM_EXTENDED_DEVICE;

    sram2.Init.NSBank = FMC_NORSRAM_BANK2;
    sram2.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
    sram2.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
    sram2.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_32;
    sram2.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
    sram2.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
    sram2.Init.WrapMode = FMC_WRAP_MODE_DISABLE;
    sram2.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
    sram2.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
    sram2.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
    sram2.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
    sram2.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
    sram2.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
    sram2.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
    sram2.Init.PageSize = FMC_PAGE_SIZE_1024;

    if (HAL_SRAM_Init(&sram2, &timing, NULL) != HAL_OK)
    {
        LOG_E("extend IO init failed!");
    }
    else
    {
        LOG_D("extend IO init success");
    }
}

static int stm32_ext_io_init(void)
{
    HC574_Config_FMC();
    /* Set the chip select to high level */
    HC574_state = (NRF24L01_CE | VS1053_XDCS | LED1 | LED2 | LED3 | LED4 );
    /* Change IO state */
    HC574_PORT = HC574_state;

    return RT_EOK;
}
INIT_BOARD_EXPORT(stm32_ext_io_init);
#endif /* BSP_USING_EXT_FMC_IO */
