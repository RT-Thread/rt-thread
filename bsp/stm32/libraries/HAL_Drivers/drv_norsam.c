/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-27     PiscesLyn   first version
 */

#include <board.h>

#ifdef BSP_USING_NORSRAM
#include <norsram_port.h>

#define DRV_DEBUG
#define LOG_TAG             "drv.norsram"
#include <drv_log.h>

static NOR_HandleTypeDef hnor1;

static int NORSRAM_Init(void)
{
    int result = RT_EOK;
    FMC_NORSRAM_TimingTypeDef NORSRAM_Timing;

    /* NORSRAM device configuration */
    hnor1.Instance = FMC_NORSRAM_DEVICE;
    hnor1.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
    NORSRAM_Timing.AddressSetupTime      = ADDRESSSETUPTIME;
    NORSRAM_Timing.AddressHoldTime       = ADDRESSHOLDTIME;
    NORSRAM_Timing.DataSetupTime         = DATASETUPTIME;
    NORSRAM_Timing.BusTurnAroundDuration = BUSTURNAROUNDDURATION;
    NORSRAM_Timing.CLKDivision           = CLKDIVISION;
    NORSRAM_Timing.DataLatency           = DATALATENCY;
#if NORSRAM_BURST_ACCESS_MODE == 0
    NORSRAM_Timing.AccessMode            = FMC_ACCESS_MODE_A;
#elif NORSRAM_BURST_ACCESS_MODE == 1
    NORSRAM_Timing.AccessMode            = FMC_ACCESS_MODE_B;
#elif NORSRAM_BURST_ACCESS_MODE == 2
    NORSRAM_Timing.AccessMode            = FMC_ACCESS_MODE_C;
#elif NORSRAM_BURST_ACCESS_MODE == 3
    NORSRAM_Timing.AccessMode            = FMC_ACCESS_MODE_D;
#endif

#if NORSRAM_TARGET_BANK == 1
    hnor1.Init.NSBank               = FMC_NORSRAM_BANK1;
#elif NORSRAM_TARGET_BANK == 2
    hnor1.Init.NSBank               = FMC_NORSRAM_BANK2;
#elif NORSRAM_TARGET_BANK == 3
    hnor1.Init.NSBank               = FMC_NORSRAM_BANK3;
#elif NORSRAM_TARGET_BANK == 4
    hnor1.Init.NSBank               = FMC_NORSRAM_BANK4;
#endif
#if NORSRAM_DATA_MUX_EN == 0
    hnor1.Init.DataAddressMux       = FMC_DATA_ADDRESS_MUX_DISABLE;
#else
    hnor1.Init.DataAddressMux       = FMC_DATA_ADDRESS_MUX_ENABLE;
#endif
#if NORSRAM_TYPE == 0
    hnor1.Init.MemoryType           = FMC_MEMORY_TYPE_SRAM;
#elif NORSRAM_TYPE == 1
    hnor1.Init.MemoryType           = FMC_MEMORY_TYPE_PSRAM;
#else
    hnor1.Init.MemoryType           = FMC_MEMORY_TYPE_NOR;
#endif
#if NORSRAM_DATA_WIDTH == 8
    hnor1.Init.MemoryDataWidth      = FMC_NORSRAM_MEM_BUS_WIDTH_8;
#elif NORSRAM_DATA_WIDTH == 16
    hnor1.Init.MemoryDataWidth      = FMC_NORSRAM_MEM_BUS_WIDTH_16;
#else
    hnor1.Init.MemoryDataWidth      = FMC_NORSRAM_MEM_BUS_WIDTH_32;
#endif
#if NORSRAM_BURST_ACCESS_MODE_EN == 0
    hnor1.Init.BurstAccessMode      = FMC_BURST_ACCESS_MODE_DISABLE;
#else
    hnor1.Init.BurstAccessMode      = FMC_BURST_ACCESS_MODE_ENABLE;
#endif
#if NORSRAM_WAIT_SIGNAL_POLARITY == 0
    hnor1.Init.WaitSignalPolarity   = FMC_WAIT_SIGNAL_POLARITY_LOW;
#else
    hnor1.Init.WaitSignalPolarity   = FMC_WAIT_SIGNAL_POLARITY_HIGH;
#endif
#if NORSRAM_WAIT_SIGNAL_ACTIVE == 0
    hnor1.Init.WaitSignalActive     = FMC_WAIT_TIMING_BEFORE_WS;
#else
    hnor1.Init.WaitSignalActive     = FMC_WAIT_TIMING_BEFORE_WS;
#endif
#if NORSRAM_WAIT_OPERATION_EN == 0
    hnor1.Init.WriteOperation       = FMC_WRITE_OPERATION_DISABLE;
#else
    hnor1.Init.WriteOperation       = FMC_WRITE_OPERATION_ENABLE;
#endif
#if NORSRAM_WAIT_SIGNAL == 0
    hnor1.Init.WaitSignal           = FMC_WAIT_SIGNAL_DISABLE;
#else
    hnor1.Init.WaitSignal           = FMC_WAIT_SIGNAL_ENABLE;
#endif
#if NORSRAM_EXTENDED_MODE_EN == 0
    hnor1.Init.ExtendedMode         = FMC_EXTENDED_MODE_DISABLE;
#else
    hnor1.Init.ExtendedMode         = FMC_EXTENDED_MODE_ENABLE;
#endif
#if NORSRAM_ASYNCHRONOUS_WAIT_EN == 0
    hnor1.Init.AsynchronousWait     = FMC_ASYNCHRONOUS_WAIT_DISABLE;
#else
    hnor1.Init.AsynchronousWait     = FMC_ASYNCHRONOUS_WAIT_ENABLE;
#endif
#if NORSRAM_WRITE_BURST_EN == 0
    hnor1.Init.WriteBurst           = FMC_WRITE_BURST_DISABLE;
#else
    hnor1.Init.WriteBurst           = FMC_WRITE_BURST_ENABLE;
#endif
#if NORSRAM_CONTINUOUS_CLOCK == 0
    hnor1.Init.ContinuousClock      = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
#else
    hnor1.Init.ContinuousClock      = FMC_CONTINUOUS_CLOCK_SYNC_ASYNC;
#endif
#if NORSRAM_WRITE_FIFO_EN == 0
    hnor1.Init.WriteFifo            = FMC_WRITE_FIFO_DISABLE;
#else
    hnor1.Init.WriteFifo            = FMC_WRITE_FIFO_ENABLE;
#endif
#if NORSRAM_PAGE_SIZE == 0
    hnor1.Init.PageSize             = FMC_PAGE_SIZE_NONE;
#elif NORSRAM_PAGE_SIZE == 128
    hnor1.Init.PageSize             = FMC_PAGE_SIZE_128;
#elif NORSRAM_PAGE_SIZE == 256
    hnor1.Init.PageSize             = FMC_PAGE_SIZE_256;
#elif NORSRAM_PAGE_SIZE == 512
    hnor1.Init.PageSize             = FMC_PAGE_SIZE_512;
#elif NORSRAM_PAGE_SIZE == 1024
    hnor1.Init.PageSize             = FMC_PAGE_SIZE_1024;
#endif

    /* Initialize the NORSRAM controller */
    if (HAL_NOR_Init(&hnor1, &NORSRAM_Timing, &NORSRAM_Timing) != HAL_OK)
    {
        LOG_E("NORSRAM init failed!");
        result = -RT_ERROR;
    }

    return result;
}
INIT_BOARD_EXPORT(NORSRAM_Init);

#endif /* BSP_USING_NORSRAM */
