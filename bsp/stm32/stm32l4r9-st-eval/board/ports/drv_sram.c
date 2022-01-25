/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-04     zylx         first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_SRAM
#include <sram_port.h>

#define DRV_DEBUG
#define LOG_TAG             "drv.sram"
#include <drv_log.h>

static SRAM_HandleTypeDef hsram;
static FMC_NORSRAM_TimingTypeDef SRAM_Timing;
#ifdef RT_USING_MEMHEAP_AS_HEAP
static struct rt_memheap system_heap;
#endif

static int SRAM_Init(void)
{
    int result = RT_EOK;

    /* SRAM device configuration */
    hsram.Instance  = FMC_NORSRAM_DEVICE;
    hsram.Extended  = FMC_NORSRAM_EXTENDED_DEVICE;

    /* SRAM device configuration */
    SRAM_Timing.AddressSetupTime       = ADDRESSSETUPTIME;
    SRAM_Timing.AddressHoldTime        = ADDRESSHOLDTIME;          /* Min value, Don't care on SRAM Access mode A */
    SRAM_Timing.DataSetupTime          = DATASETUPTIME;
    SRAM_Timing.DataHoldTime           = DATAHOLDTIME;
    SRAM_Timing.BusTurnAroundDuration  = BUSTURNAROUNDDURATION;
    SRAM_Timing.CLKDivision            = CLKDIVISION;              /* Min value, Don't care on SRAM Access mode A */
    SRAM_Timing.DataLatency            = DATALATENCY;              /* Min value, Don't care on SRAM Access mode A */
    SRAM_Timing.AccessMode             = ACCESSMODE;

    hsram.Init.NSBank             = FMC_NORSRAM_BANK1;
    hsram.Init.DataAddressMux     = FMC_DATA_ADDRESS_MUX_DISABLE;
    hsram.Init.MemoryType         = FMC_MEMORY_TYPE_SRAM;
#if SRAM_DATA_WIDTH == 8
    hsram.Init.MemoryDataWidth    = FMC_NORSRAM_MEM_BUS_WIDTH_8;
#elif SRAM_DATA_WIDTH == 16
    hsram.Init.MemoryDataWidth    = FMC_NORSRAM_MEM_BUS_WIDTH_16;
#else
    hsram.Init.MemoryDataWidth    = FMC_NORSRAM_MEM_BUS_WIDTH_32;
#endif
    hsram.Init.BurstAccessMode    = FMC_BURST_ACCESS_MODE_DISABLE;
    hsram.Init.WriteOperation     = FMC_WRITE_OPERATION_ENABLE;
    hsram.Init.WaitSignal         = FMC_WAIT_SIGNAL_DISABLE;
    hsram.Init.WaitSignalActive   = FMC_WAIT_TIMING_BEFORE_WS;
    hsram.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
    hsram.Init.ExtendedMode       = FMC_EXTENDED_MODE_DISABLE;
    hsram.Init.AsynchronousWait   = FMC_ASYNCHRONOUS_WAIT_DISABLE;
    hsram.Init.WriteBurst         = FMC_WRITE_BURST_DISABLE;
    hsram.Init.ContinuousClock    = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
    hsram.Init.WriteFifo          = FMC_WRITE_FIFO_DISABLE;
    hsram.Init.NBLSetupTime       = 0;
    hsram.Init.PageSize           = FMC_PAGE_SIZE_NONE;

    /* Initialize the SRAM controller */
    if (HAL_SRAM_Init(&hsram, &SRAM_Timing, &SRAM_Timing) != HAL_OK)
    {
        LOG_E("SRAM init failed!");
        result = -RT_ERROR;
    }
    else
    {
        LOG_D("sram init success, mapped at 0x%X, size is %d bytes, data width is %d", SRAM_BANK_ADDR, SRAM_SIZE, SRAM_DATA_WIDTH);
#ifdef RT_USING_MEMHEAP_AS_HEAP
        /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SRAM is initialized to the heap */
        rt_memheap_init(&system_heap, "sram", (void *)SRAM_BANK_ADDR, SRAM_SIZE);
#endif
    }

    return result;
}
INIT_BOARD_EXPORT(SRAM_Init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
int sram_test(void)
{
    int i = 0;
    uint32_t start_time = 0, time_cast = 0;
#if SRAM_DATA_WIDTH == 8
    char data_width = 1;
    uint8_t data = 0;
    uint8_t *ptr = (uint8_t *)SRAM_BANK_ADDR;
#elif SRAM_DATA_WIDTH == 16
    char data_width = 2;
    uint16_t data = 0;
    uint16_t *ptr = (uint16_t *)SRAM_BANK_ADDR;
#else
    char data_width = 4;
    uint32_t data = 0;
    uint32_t *ptr = (uint32_t *)SRAM_BANK_ADDR;
#endif

    /* write data */
    LOG_D("Writing the %ld bytes data, waiting....", SRAM_SIZE);
    start_time = rt_tick_get();
    for (i = 0; i < SRAM_SIZE / data_width; i++)
    {
#if SRAM_DATA_WIDTH == 8
        ((__IO uint8_t *)ptr)[i] = (uint8_t)0x55;
#elif SRAM_DATA_WIDTH == 16
        ((__IO uint16_t *)ptr)[i] = (uint16_t)0x5555;
#else
        ((__IO uint32_t *)ptr)[i] = (uint32_t)0x55555555;
#endif
    }
    time_cast = rt_tick_get() - start_time;
    LOG_D("Write data success, total time: %d.%03dS.", time_cast / RT_TICK_PER_SECOND,
          time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));

    /* read data */
    LOG_D("start Reading and verifying data, waiting....");
    for (i = 0; i < SRAM_SIZE / data_width; i++)
    {
#if SRAM_DATA_WIDTH == 8
        data = ((__IO uint8_t *)ptr)[i];
        if (data != 0x55)
        {
            LOG_E("SRAM test failed!");
            break;
        }
#elif SRAM_DATA_WIDTH == 16
        data = ((__IO uint16_t *)ptr)[i];
        if (data != 0x5555)
        {
            LOG_E("SRAM test failed!");
            break;
        }
#else
        data = ((__IO uint32_t *)ptr)[i];
        if (data != 0x55555555)
        {
            LOG_E("SRAM test failed!");
            break;
        }
#endif
    }

    if (i >= SRAM_SIZE / data_width)
    {
        LOG_D("SRAM test success!");
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(sram_test, sram test);
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_SRAM */
