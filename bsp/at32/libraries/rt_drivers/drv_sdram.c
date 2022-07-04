/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#include "drv_common.h"

#ifdef BSP_USING_SDRAM
#include "drv_sdram.h"

#define DRV_DEBUG
#define LOG_TAG                         "drv.sdram"
#include <drv_log.h>

#ifdef RT_USING_MEMHEAP_AS_HEAP
static struct rt_memheap system_heap;
#endif

static void sdram_init_sequence(xmc_cmd_bank1_2_type cmd_bank)
{
    xmc_sdram_cmd_type sdram_cmd_struct;
    uint32_t timeout = 0xffff, delay = 0;

    sdram_cmd_struct.cmd = XMC_CMD_CLK;
    sdram_cmd_struct.auto_refresh = 1;
    sdram_cmd_struct.cmd_banks = cmd_bank;
    sdram_cmd_struct.data = 0;
    xmc_sdram_cmd(&sdram_cmd_struct);

    while((xmc_flag_status_get(XMC_BANK5_6_SDRAM, XMC_BUSY_FLAG) != RESET) && (timeout > 0))
    {
        timeout --;
    }

    /* insert 100 ms delay */
    for (delay = 0; delay < 0xffff; delay ++)
        ;

    sdram_cmd_struct.cmd = XMC_CMD_PRECHARG_ALL;
    sdram_cmd_struct.auto_refresh = 1;
    sdram_cmd_struct.cmd_banks = cmd_bank;
    sdram_cmd_struct.data = 0;
    xmc_sdram_cmd(&sdram_cmd_struct);

    timeout = 0xffff;
    while((xmc_flag_status_get(XMC_BANK5_6_SDRAM, XMC_BUSY_FLAG) != RESET) && (timeout > 0))
    {
        timeout --;
    }

    /* set refresh rate */
    xmc_sdram_refresh_counter_set(SDRAM_REFRESH_COUNT);

    sdram_cmd_struct.cmd = XMC_CMD_AUTO_REFRESH;
    sdram_cmd_struct.auto_refresh = 8;
    sdram_cmd_struct.cmd_banks = cmd_bank;
    sdram_cmd_struct.data = 0;
    xmc_sdram_cmd(&sdram_cmd_struct);

    timeout = 0xffff;
    while((xmc_flag_status_get(XMC_BANK5_6_SDRAM, XMC_BUSY_FLAG) != RESET) && (timeout > 0))
    {
        timeout --;
    }

    sdram_cmd_struct.cmd = XMC_CMD_LOAD_MODE;
    sdram_cmd_struct.auto_refresh = 1;
    sdram_cmd_struct.cmd_banks = cmd_bank;

#if SDRAM_DATA_WIDTH == 8
    sdram_cmd_struct.data = (uint32_t)SDRAM_BURST_LEN_1   |
#elif SDRAM_DATA_WIDTH == 16
    sdram_cmd_struct.data = (uint32_t)SDRAM_BURST_LEN_2   |
#endif
                            SDRAM_BURST_SEQUENTIAL        |
#if SDRAM_CAS_LATENCY == 3
                            SDRAM_CAS_LATENCY_3           |
#else
                            SDRAM_CAS_LATENCY_2           |
#endif
                            SDRAM_OPERATING_MODE_STANDARD |
                            SDRAM_WR_BURST_SINGLE;

    xmc_sdram_cmd(&sdram_cmd_struct);

    timeout = 0xffff;
    while((xmc_flag_status_get(XMC_BANK5_6_SDRAM, XMC_BUSY_FLAG) != RESET) && (timeout > 0))
    {
        timeout --;
    }
}

static int sdram_init(void)
{
    int result = RT_EOK;
    xmc_cmd_bank1_2_type target_bank = XMC_CMD_BANK1;

    xmc_sdram_init_type sdram_init_struct;
    xmc_sdram_timing_type sdram_timing_struct;

    at32_msp_sdram_init(NULL);

    /* xmc configuration */
    xmc_sdram_default_para_init(&sdram_init_struct, &sdram_timing_struct);

#if SDRAM_TARGET_BANK == 1
    sdram_init_struct.sdram_bank = XMC_SDRAM_BANK1;
#else
    sdram_init_struct.sdram_bank = XMC_SDRAM_BANK2;
#endif
#if SDRAM_COLUMN_BITS == 8
    sdram_init_struct.column_address = XMC_COLUMN_8;
#elif SDRAM_COLUMN_BITS == 9
    sdram_init_struct.column_address = XMC_COLUMN_9;
#elif SDRAM_COLUMN_BITS == 10
    sdram_init_struct.column_address = XMC_COLUMN_10;
#else
    sdram_init_struct.column_address = XMC_COLUMN_11;
#endif
#if SDRAM_ROW_BITS == 11
    sdram_init_struct.row_address = XMC_ROW_11;
#elif SDRAM_ROW_BITS == 12
    sdram_init_struct.row_address = XMC_ROW_12;
#else
    sdram_init_struct.row_address = XMC_ROW_13;
#endif
#if SDRAM_DATA_WIDTH == 8
    sdram_init_struct.width = XMC_MEM_WIDTH_8;
#elif SDRAM_DATA_WIDTH == 16
    sdram_init_struct.width = XMC_MEM_WIDTH_16;
#endif

    sdram_init_struct.internel_banks = XMC_INBK_4;

#if SDRAM_CAS_LATENCY == 1
    sdram_init_struct.cas = XMC_CAS_1;
#elif SDRAM_CAS_LATENCY == 2
    sdram_init_struct.cas = XMC_CAS_2;
#else
    sdram_init_struct.cas = XMC_CAS_3;
#endif
#if SDRAM_RPIPE_DELAY == 0
    sdram_init_struct.read_delay = XMC_READ_DELAY_0;
#elif SDRAM_RPIPE_DELAY == 1
    sdram_init_struct.read_delay = XMC_READ_DELAY_1;
#else
    sdram_init_struct.read_delay = XMC_READ_DELAY_2;
#endif
#if SDCLOCK_PERIOD == 2
    sdram_init_struct.clkdiv = XMC_CLKDIV_2;
#else
    sdram_init_struct.clkdiv = XMC_CLKDIV_3;
#endif

    sdram_init_struct.write_protection = FALSE;
    sdram_init_struct.burst_read = TRUE;

    sdram_timing_struct.tmrd = LOADTOACTIVEDELAY;
    sdram_timing_struct.txsr = EXITSELFREFRESHDELAY;
    sdram_timing_struct.tras = SELFREFRESHTIME;
    sdram_timing_struct.trc = ROWCYCLEDELAY;
    sdram_timing_struct.twr = WRITERECOVERYTIME;
    sdram_timing_struct.trp = RPDELAY;
    sdram_timing_struct.trcd = RCDDELAY;

    xmc_sdram_init(&sdram_init_struct, &sdram_timing_struct);

#if SDRAM_TARGET_BANK == 1
    target_bank = XMC_CMD_BANK1;
#else
    target_bank = XMC_CMD_BANK2;
#endif

    sdram_init_sequence(target_bank);

#ifdef RT_USING_MEMHEAP_AS_HEAP
        /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SDRAM is initialized to the heap */
        rt_memheap_init(&system_heap, "sdram", (void *)SDRAM_BANK_ADDR, SDRAM_SIZE);
#endif

    return result;
}

INIT_BOARD_EXPORT(sdram_init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
int sdram_sample(void)
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
    LOG_D("writing the %ld bytes data, waiting....", SDRAM_SIZE);
    start_time = rt_tick_get();
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
#if SDRAM_DATA_WIDTH == 8
        *(__IO uint8_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint8_t)(i % 100);
#elif SDRAM_DATA_WIDTH == 16
        *(__IO uint16_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint16_t)(i % 1000);
#endif
    }
    time_cast = rt_tick_get() - start_time;
    LOG_D("write data success, total time: %d.%03dS.", time_cast / RT_TICK_PER_SECOND,
          time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));

    /* read data */
    LOG_D("start reading and verifying data, waiting....");
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
#if SDRAM_DATA_WIDTH == 8
        data = *(__IO uint8_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != i % 100)
        {
            LOG_E("sdram test failed!");
            break;
        }
#elif SDRAM_DATA_WIDTH == 16
        data = *(__IO uint16_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != (uint16_t)(i % 1000))
        {
            LOG_E("sdram test failed, i = %d!", i);
            break;
        }
#endif
    }

    if (i >= SDRAM_SIZE / data_width)
    {
        LOG_D("sdram test success!");
    }

    return RT_EOK;
}

MSH_CMD_EXPORT(sdram_sample, sdram sample test)

#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_SDRAM */
