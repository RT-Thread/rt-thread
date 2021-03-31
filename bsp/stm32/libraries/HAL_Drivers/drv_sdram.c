/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-04     zylx         first version
 */

#include <board.h>

#ifdef BSP_USING_SDRAM
#include <sdram_port.h>

#define DRV_DEBUG
#define LOG_TAG             "drv.sdram"
#include <drv_log.h>

static SDRAM_HandleTypeDef hsdram1;
static FMC_SDRAM_CommandTypeDef command;
#ifdef RT_USING_MEMHEAP_AS_HEAP
static struct rt_memheap system_heap;
#endif

/**
  * @brief  Perform the SDRAM exernal memory inialization sequence
  * @param  hsdram: SDRAM handle
  * @param  Command: Pointer to SDRAM command structure
  * @retval None
  */
static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
    __IO uint32_t tmpmrd = 0;
    uint32_t target_bank = 0;

#if SDRAM_TARGET_BANK == 1
    target_bank = FMC_SDRAM_CMD_TARGET_BANK1;
#else
    target_bank = FMC_SDRAM_CMD_TARGET_BANK2;
#endif

    /* Configure a clock configuration enable command */
    Command->CommandMode           = FMC_SDRAM_CMD_CLK_ENABLE;
    Command->CommandTarget         = target_bank;
    Command->AutoRefreshNumber     = 1;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

    /* Insert 100 ms delay */
    /* interrupt is not enable, just to delay some time. */
    for (tmpmrd = 0; tmpmrd < 0xffffff; tmpmrd ++)
        ;

    /* Configure a PALL (precharge all) command */
    Command->CommandMode            = FMC_SDRAM_CMD_PALL;
    Command->CommandTarget          = target_bank;
    Command->AutoRefreshNumber      = 1;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

    /* Configure a Auto-Refresh command */
    Command->CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    Command->CommandTarget          = target_bank;
    Command->AutoRefreshNumber      = 8;
    Command->ModeRegisterDefinition = 0;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

    /* Program the external memory mode register */
#if SDRAM_DATA_WIDTH == 8
    tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1     |
#elif SDRAM_DATA_WIDTH == 16
    tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2     |
#else
    tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_4     |
#endif
             SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL        |
#if SDRAM_CAS_LATENCY == 3
             SDRAM_MODEREG_CAS_LATENCY_3                |
#else
             SDRAM_MODEREG_CAS_LATENCY_2                |
#endif
             SDRAM_MODEREG_OPERATING_MODE_STANDARD      |
             SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    Command->CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
    Command->CommandTarget          = target_bank;
    Command->AutoRefreshNumber      = 1;
    Command->ModeRegisterDefinition = tmpmrd;

    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

    /* Set the device refresh counter */
    HAL_SDRAM_ProgramRefreshRate(hsdram, SDRAM_REFRESH_COUNT);
}

static int SDRAM_Init(void)
{
    int result = RT_EOK;
    FMC_SDRAM_TimingTypeDef SDRAM_Timing;

    /* SDRAM device configuration */
    hsdram1.Instance = FMC_SDRAM_DEVICE;
    SDRAM_Timing.LoadToActiveDelay    = LOADTOACTIVEDELAY;
    SDRAM_Timing.ExitSelfRefreshDelay = EXITSELFREFRESHDELAY;
    SDRAM_Timing.SelfRefreshTime      = SELFREFRESHTIME;
    SDRAM_Timing.RowCycleDelay        = ROWCYCLEDELAY;
    SDRAM_Timing.WriteRecoveryTime    = WRITERECOVERYTIME;
    SDRAM_Timing.RPDelay              = RPDELAY;
    SDRAM_Timing.RCDDelay             = RCDDELAY;

#if SDRAM_TARGET_BANK == 1
    hsdram1.Init.SDBank             = FMC_SDRAM_BANK1;
#else
    hsdram1.Init.SDBank             = FMC_SDRAM_BANK2;
#endif
#if SDRAM_COLUMN_BITS == 8
    hsdram1.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_8;
#elif SDRAM_COLUMN_BITS == 9
    hsdram1.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_9;
#elif SDRAM_COLUMN_BITS == 10
    hsdram1.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_10;
#else
    hsdram1.Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_11;
#endif
#if SDRAM_ROW_BITS == 11
    hsdram1.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_11;
#elif SDRAM_ROW_BITS == 12
    hsdram1.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_12;
#else
    hsdram1.Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_13;
#endif

#if SDRAM_DATA_WIDTH == 8
    hsdram1.Init.MemoryDataWidth    = FMC_SDRAM_MEM_BUS_WIDTH_8;
#elif SDRAM_DATA_WIDTH == 16
    hsdram1.Init.MemoryDataWidth    = FMC_SDRAM_MEM_BUS_WIDTH_16;
#else
    hsdram1.Init.MemoryDataWidth    = FMC_SDRAM_MEM_BUS_WIDTH_32;
#endif
    hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
#if SDRAM_CAS_LATENCY == 1
    hsdram1.Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_1;
#elif SDRAM_CAS_LATENCY == 2
    hsdram1.Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_2;
#else
    hsdram1.Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_3;
#endif
    hsdram1.Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
#if SDCLOCK_PERIOD == 2
    hsdram1.Init.SDClockPeriod      = FMC_SDRAM_CLOCK_PERIOD_2;
#else
    hsdram1.Init.SDClockPeriod      = FMC_SDRAM_CLOCK_PERIOD_3;
#endif
    hsdram1.Init.ReadBurst          = FMC_SDRAM_RBURST_ENABLE;
#if SDRAM_RPIPE_DELAY == 0
    hsdram1.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_0;
#elif SDRAM_RPIPE_DELAY == 1
    hsdram1.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_1;
#else
    hsdram1.Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_2;
#endif

    /* Initialize the SDRAM controller */
    if (HAL_SDRAM_Init(&hsdram1, &SDRAM_Timing) != HAL_OK)
    {
        LOG_E("SDRAM init failed!");
        result = -RT_ERROR;
    }
    else
    {
        /* Program the SDRAM external device */
        SDRAM_Initialization_Sequence(&hsdram1, &command);
        LOG_D("sdram init success, mapped at 0x%X, size is %d bytes, data width is %d", SDRAM_BANK_ADDR, SDRAM_SIZE, SDRAM_DATA_WIDTH);
#ifdef RT_USING_MEMHEAP_AS_HEAP
        /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SDRAM is initialized to the heap */
        rt_memheap_init(&system_heap, "sdram", (void *)SDRAM_BANK_ADDR, SDRAM_SIZE);
#endif
    }

    return result;
}
INIT_BOARD_EXPORT(SDRAM_Init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
int sdram_test(void)
{
    int i = 0;
    uint32_t start_time = 0, time_cast = 0;
#if SDRAM_DATA_WIDTH == 8
    char data_width = 1;
    uint8_t data = 0;
#elif SDRAM_DATA_WIDTH == 16
    char data_width = 2;
    uint16_t data = 0;
#else
    char data_width = 4;
    uint32_t data = 0;
#endif

    /* write data */
    LOG_D("Writing the %ld bytes data, waiting....", SDRAM_SIZE);
    start_time = rt_tick_get();
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
#if SDRAM_DATA_WIDTH == 8
        *(__IO uint8_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint8_t)(i % 100);
#elif SDRAM_DATA_WIDTH == 16
        *(__IO uint16_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint16_t)(i % 1000);
#else
        *(__IO uint32_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint32_t)(i % 1000);
#endif
    }
    time_cast = rt_tick_get() - start_time;
    LOG_D("Write data success, total time: %d.%03dS.", time_cast / RT_TICK_PER_SECOND,
          time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));

    /* read data */
    LOG_D("start Reading and verifying data, waiting....");
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
#if SDRAM_DATA_WIDTH == 8
        data = *(__IO uint8_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != i % 100)
        {
            LOG_E("SDRAM test failed!");
            break;
        }
#elif SDRAM_DATA_WIDTH == 16
        data = *(__IO uint16_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != i % 1000)
        {
            LOG_E("SDRAM test failed!");
            break;
        }
#else
        data = *(__IO uint32_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != i % 1000)
        {
            LOG_E("SDRAM test failed!");
            break;
        }
#endif
    }

    if (i >= SDRAM_SIZE / data_width)
    {
        LOG_D("SDRAM test success!");
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(sdram_test, sdram test)
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_SDRAM */
