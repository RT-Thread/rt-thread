/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-05     linyiyang    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_EXT_SRAM
#include <sram_port.h>

#define DRV_DEBUG
#define LOG_TAG             "drv.ext_sram"
#include <drv_log.h>

static SRAM_HandleTypeDef hsram1;
#ifdef RT_USING_MEMHEAP_AS_HEAP
static struct rt_memheap system_heap;
#endif

static int external_sram_init(void)
{
    int result = RT_EOK;

    FSMC_NORSRAM_TimingTypeDef Timing = {0};

    /** Perform the SRAM1 memory initialization sequence
    */
    hsram1.Instance                 = FSMC_NORSRAM_DEVICE;
    hsram1.Extended                 = FSMC_NORSRAM_EXTENDED_DEVICE;

    /* hsram1.Init */
    hsram1.Init.NSBank              = FSMC_NORSRAM_BANK3;
    hsram1.Init.DataAddressMux      = FSMC_DATA_ADDRESS_MUX_DISABLE;
    hsram1.Init.MemoryType          = FSMC_MEMORY_TYPE_SRAM;
#if EXTERNAL_SRAM_DATA_WIDTH == 8
    hsram1.Init.MemoryDataWidth     = FSMC_NORSRAM_MEM_BUS_WIDTH_8;
#elif EXTERNAL_SRAM_DATA_WIDTH == 16
    hsram1.Init.MemoryDataWidth     = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
#else
    hsram1.Init.MemoryDataWidth     = FSMC_NORSRAM_MEM_BUS_WIDTH_32;
#endif
    hsram1.Init.BurstAccessMode     = FSMC_BURST_ACCESS_MODE_DISABLE;
    hsram1.Init.WaitSignalPolarity  = FSMC_WAIT_SIGNAL_POLARITY_LOW;
    hsram1.Init.WrapMode            = FSMC_WRAP_MODE_DISABLE;
    hsram1.Init.WaitSignalActive    = FSMC_WAIT_TIMING_BEFORE_WS;
    hsram1.Init.WriteOperation      = FSMC_WRITE_OPERATION_ENABLE;
    hsram1.Init.WaitSignal          = FSMC_WAIT_SIGNAL_DISABLE;
    hsram1.Init.ExtendedMode        = FSMC_EXTENDED_MODE_DISABLE;
    hsram1.Init.AsynchronousWait    = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
    hsram1.Init.WriteBurst          = FSMC_WRITE_BURST_DISABLE;

    /* Timing */
    Timing.AddressSetupTime         = 0;
    Timing.AddressHoldTime          = 15;
    Timing.DataSetupTime            = 3;
    Timing.BusTurnAroundDuration    = 0;
    Timing.CLKDivision              = 16;
    Timing.DataLatency              = 17;
    Timing.AccessMode               = FSMC_ACCESS_MODE_A;
    /* ExtTiming */

    /* Initialize the SRAM controller */
    if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
    {
        LOG_E("External SRAM init failed!");
        result = -RT_ERROR;
    }
    else
    {
        LOG_D("External sram init success, mapped at 0x%X, size is %d bytes, data width is %d", EXTERNAL_SRAM_BANK_ADDR, EXTERNAL_SRAM_SIZE, EXTERNAL_SRAM_DATA_WIDTH);
#ifdef RT_USING_MEMHEAP_AS_HEAP
        /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SRAM is initialized to the heap */
        rt_memheap_init(&system_heap, "ext_sram", (void *)EXTERNAL_SRAM_BANK_ADDR, EXTERNAL_SRAM_SIZE);
#endif
    }

    /** Disconnect NADV
    */

    __HAL_AFIO_FSMCNADV_DISCONNECTED();

    return result;
}
INIT_BOARD_EXPORT(external_sram_init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
int external_sram_test(void)
{
    int i = 0;
    uint32_t start_time = 0, time_cast = 0;
#if EXTERNAL_SRAM_DATA_WIDTH == 8
    char data_width = 1;
    uint8_t data = 0;
    uint8_t *ptr = (uint8_t *)EXTERNAL_SRAM_BANK_ADDR;
#elif EXTERNAL_SRAM_DATA_WIDTH == 16
    char data_width = 2;
    uint16_t data = 0;
    uint16_t *ptr = (uint16_t *)EXTERNAL_SRAM_BANK_ADDR;
#else
    char data_width = 4;
    uint32_t data = 0;
    uint32_t *ptr = (uint32_t *)EXTERNAL_SRAM_BANK_ADDR;
#endif

    /* write data */
    LOG_D("Writing the %ld bytes data, waiting....", EXTERNAL_SRAM_SIZE);
    start_time = rt_tick_get();
    for (i = 0; i < EXTERNAL_SRAM_SIZE / data_width; i++)
    {
#if EXTERNAL_SRAM_DATA_WIDTH == 8
        ((__IO uint8_t *)ptr)[i] = (uint8_t)0x55;
#elif EXTERNAL_SRAM_DATA_WIDTH == 16
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
    for (i = 0; i < EXTERNAL_SRAM_SIZE / data_width; i++)
    {
#if EXTERNAL_SRAM_DATA_WIDTH == 8
        data = ((__IO uint8_t *)ptr)[i];
        if (data != 0x55)
        {
            LOG_E("External SRAM test failed!");
            break;
        }
#elif EXTERNAL_SRAM_DATA_WIDTH == 16
        data = ((__IO uint16_t *)ptr)[i];
        if (data != 0x5555)
        {
            LOG_E("External SRAM test failed!");
            break;
        }
#else
        data = ((__IO uint32_t *)ptr)[i];
        if (data != 0x55555555)
        {
            LOG_E("External SRAM test failed!");
            break;
        }
#endif
    }

    if (i >= EXTERNAL_SRAM_SIZE / data_width)
    {
        LOG_D("External SRAM test success!");
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(external_sram_test, sram test);
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_EXT_SRAM */
