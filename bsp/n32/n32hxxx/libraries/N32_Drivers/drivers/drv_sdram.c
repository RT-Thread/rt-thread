/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-21     ox-horse     first version for N32, based on N32 SDK bsp_sdram.c
 */

#include <board.h>
#include <rtthread.h>

#ifdef BSP_USING_SDRAM
#include <sdram_port.h>
#include <n32h7xx_rcc.h>
#include <n32h7xx_sdram.h>

#define DRV_DEBUG
#define LOG_TAG "drv.sdram"
#include <drv_log.h>

#ifdef RT_USING_MEMHEAP_AS_HEAP
static struct rt_memheap system_heap;
#endif

static SDRAM_DeviceType sdram_device;

/*----------------------------------------------------------------------------
 * Macro translation: standard sdram_port.h -> N32 HAL
 *---------------------------------------------------------------------------*/

/* Row bits + Column bits -> N32 address configuration */
#if SDRAM_ROW_BITS == 11
#if SDRAM_COLUMN_BITS == 8
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW2048_COL256
#elif SDRAM_COLUMN_BITS == 9
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW2048_COL512
#elif SDRAM_COLUMN_BITS == 10
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW2048_COL1024
#elif SDRAM_COLUMN_BITS == 11
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW2048_COL2048
#endif
#elif SDRAM_ROW_BITS == 12
#if SDRAM_COLUMN_BITS == 8
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW4096_COL256
#elif SDRAM_COLUMN_BITS == 9
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW4096_COL512
#elif SDRAM_COLUMN_BITS == 10
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW4096_COL1024
#elif SDRAM_COLUMN_BITS == 11
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW4096_COL2048
#endif
#elif SDRAM_ROW_BITS == 13
#if SDRAM_COLUMN_BITS == 8
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW8192_COL256
#elif SDRAM_COLUMN_BITS == 9
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW8192_COL512
#elif SDRAM_COLUMN_BITS == 10
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW8192_COL1024
#elif SDRAM_COLUMN_BITS == 11
#define SDRAM_ADDR_CFG SDRAM_BANK4_ROW8192_COL2048
#endif
#endif

/* Data width -> N32 bus width */
#if SDRAM_DATA_WIDTH == 8
#define SDRAM_HAL_BUS_WIDTH     SDRAM_DEVICE_BUSWID_8BITS
#define SDRAM_HAL_BURSTLEN      SDRAM_DEVICE_BURSTLEN_8
#define SDRAM_LOADMODE_BURSTLEN 3
#elif SDRAM_DATA_WIDTH == 16
#define SDRAM_HAL_BUS_WIDTH     SDRAM_DEVICE_BUSWID_16BITS
#define SDRAM_HAL_BURSTLEN      SDRAM_DEVICE_BURSTLEN_4
#define SDRAM_LOADMODE_BURSTLEN 2
#elif SDRAM_DATA_WIDTH == 32
#define SDRAM_HAL_BUS_WIDTH     SDRAM_DEVICE_BUSWID_32BITS
#define SDRAM_HAL_BURSTLEN      SDRAM_DEVICE_BURSTLEN_2
#define SDRAM_LOADMODE_BURSTLEN 1
#endif

/* CAS latency -> N32 CAS */
#ifdef BSP_SDRAM_CAS_LATENCY_1
#define SDRAM_HAL_CAS_LATENCY     SDRAM_DEVICE_CASLTCY_1
#define SDRAM_LOADMODE_CASLATENCY 1
#endif /* BSP_SDRAM_CAS_LATENCY_1 */
#ifdef BSP_SDRAM_CAS_LATENCY_2
#define SDRAM_HAL_CAS_LATENCY     SDRAM_DEVICE_CASLTCY_2
#define SDRAM_LOADMODE_CASLATENCY 2
#endif /* BSP_SDRAM_CAS_LATENCY_2 */
#ifdef BSP_SDRAM_CAS_LATENCY_3
#define SDRAM_HAL_CAS_LATENCY     SDRAM_DEVICE_CASLTCY_3
#define SDRAM_LOADMODE_CASLATENCY 3
#endif /* BSP_SDRAM_CAS_LATENCY_3 */

/* Target bank -> device select */
#ifdef BSP_SDRAM_BANK1
#define SDRAM_CS_SELECT SDRAM_CS_SDRAM1_ONLY
#endif
#ifdef BSP_SDRAM_BANK2
#define SDRAM_CS_SELECT SDRAM_CS_SDRAM2_ONLY
#endif


#ifndef SDRAM_RP_DELAY
#define SDRAM_RP_DELAY (RPDELAY)
#endif
#ifndef SDRAM_REFRESH_CYCLE
#define SDRAM_REFRESH_CYCLE (ROWCYCLEDELAY)
#endif
#ifndef SDRAM_ADDRESS_MASK
#define SDRAM_ADDRESS_MASK ((uint32_t)(0xFFFFFFFF - ((BSP_SDRAM_SIZE * 1024U * 1024U) - 1)))
#endif

/*----------------------------------------------------------------------------
 * SDRAM Load Mode Register type (from N32 SDK bsp_sdram.h)
 * Represents the value sent to the SDRAM chip via LOADMODE command.
 *---------------------------------------------------------------------------*/
typedef union
{
    uint32_t cmd;
    struct
    {
        uint32_t BurstLen   : 3;   /* M2:0  Burst Length         */
        uint32_t BurstType  : 1;   /* M3    Burst Type           */
        uint32_t CASLatency : 3;   /* M6:4  CAS Latency          */
        uint32_t OpMode     : 2;   /* M8:7  Operating Mode       */
        uint32_t WBMode     : 1;   /* M9    Write Burst Mode     */
        uint32_t Reserved   : 22;
    } Bits;
} SDRAM_LoadModeRegisterType;

/* Mode register field values (from N32 SDK bsp_sdram.h) */
#define LOADMODE_BURSTLEN_1            0
#define LOADMODE_BURSTLEN_2            1
#define LOADMODE_BURSTLEN_4            2
#define LOADMODE_BURSTLEN_8            3
#define LOADMODE_BURSTTYPE_SEQUENTIAL  0
#define LOADMODE_BURSTTYPE_INTERLEAVED 1
#define LOADMODE_CASLATENCY_2          2
#define LOADMODE_CASLATENCY_3          3
#define LOADMODE_OPMODE_STANDARD       0
#define LOADMODE_WBMODE_BURST          0
#define LOADMODE_WBMODE_SINGLE         1

/*----------------------------------------------------------------------------
 * SDRAM RCC Clock Configuration  (rt_weak, override in board.c if needed)
 *---------------------------------------------------------------------------*/
rt_weak void rt_hw_sdram_clock_init(void)
{
    /* Configure SDRAM delay chain (board-specific, default 0.2ns step) */
    RCC_ConfigSDRAMDelay(RCC_SDRAM_DELAY_0_2NS);
    RCC_EnableSDRAMDelayChain(ENABLE);
}

/*----------------------------------------------------------------------------
 * SDRAM Initialization Sequence
 * Based on N32 SDK SDRAM_DeviceInit() + SDRAM_OperationInit() pattern.
 *---------------------------------------------------------------------------*/
static void SDRAM_Initialization_Sequence(SDRAM_DeviceType device)
{
    SDRAM_LoadModeRegisterType load_mode;
    __IO uint32_t delay;
    int i;

    /*--- Configure device: address, refresh, timing, bus width, etc. ---*/

    /* Step 1: Set device base address and address mask */
    SDRAM_SetDeviceAddress(device, SDRAM_BANK_ADDR, SDRAM_ADDRESS_MASK);

    /* Step 2: Set refresh interval */
    SDRAM_RefreshIntervalInit(SDRAM_REFRESH_COUNT);

    /* Step 3: Configure timing parameters
     * Mapping: STM32-style macro -> N32 SDRAM_TimingType register field
     *   SELFREFRESHTIME     -> RowActiveTime       (tRAS)
     *   ROWCYCLEDELAY       -> RowCycleTime        (tRC)
     *   SDRAM_RP_DELAY      -> RowActToRowActDelay (tRRD)
     *   RPDELAY             -> PrechargeTime       (tRP)
     *   WRITERECOVERYTIME   -> WriteRecoveryTime   (tWR)
     *   SDRAM_REFRESH_CYCLE -> RefreshCycleTime    (tRFC)
     *   RCDDELAY            -> RAstoCASDelay       (tRCD)
     */
    SDRAM_TimingType SDRAM_Timing;
    SDRAM_Timing.RowActiveTime = SELFREFRESHTIME;
    SDRAM_Timing.RowCycleTime = ROWCYCLEDELAY;
    SDRAM_Timing.RowActToRowActDelay = SDRAM_RP_DELAY;
    SDRAM_Timing.PrechargeTime = RPDELAY;
    SDRAM_Timing.WriteRecoveryTime = WRITERECOVERYTIME;
    SDRAM_Timing.RefreshCycleTime = SDRAM_REFRESH_CYCLE;
    SDRAM_Timing.RAStoCASDelay = RCDDELAY;
    SDRAM_TimingInit(&SDRAM_Timing);

    /* Step 4: Configure device parameters (same as SDRAM_ConfigurationInit in SDK) */
    SDRAM_EnableDevice(device, ENABLE);
    SDRAM_EnableRefreshCMD(device, ENABLE);
    SDRAM_EnableAutoPrecharge(device, DISABLE);
    SDRAM_EnablePrefetchRead(device, DISABLE);
    SDRAM_EnableSOM(device, ENABLE);
    SDRAM_EnableBankInterleave(device, DISABLE);
    SDRAM_ConfigBusWidth(device, SDRAM_HAL_BUS_WIDTH);
    SDRAM_ConfigBurstLength(device, SDRAM_HAL_BURSTLEN);
    SDRAM_ConfigCASLatency(device, SDRAM_HAL_CAS_LATENCY);
    SDRAM_ConfigAddress(device, SDRAM_ADDR_CFG);

    /*--- Send command sequence: Precharge -> Auto-Refresh -> Load Mode ---*/

    /* Step 5: Precharge all banks
     *   Per SDK pattern: set clock enable + opcode + chip select + bank + address,
     *   then trigger by dummy-read of SDRAM->OR register. */
    SDRAM_EnableClock(ENABLE);
    SDRAM_SetOperationCode(SDRAM_OPCODE_PRECHRG);
    SDRAM_SetDeviceSelect(SDRAM_CS_SELECT);
    SDRAM_SetBank(SDRAM_BANKADD_1);
    SDRAM_SetAddress(0);
    (void)(SDRAM->OR);  /* dummy access triggers the operation */

    /* Step 6: Auto refresh (2 cycles, per SDK convention) */
    for (i = 0; i < 2; i++)
    {
        SDRAM_EnableClock(ENABLE);
        SDRAM_SetOperationCode(SDRAM_OPCODE_REFRESH);
        SDRAM_SetDeviceSelect(SDRAM_CS_SELECT);
        SDRAM_SetBank(SDRAM_BANKADD_1);
        SDRAM_SetAddress(0);
        (void)(SDRAM->OR);
    }

    /* Step 7: Load mode register */
    load_mode.cmd = 0;
    load_mode.Bits.BurstLen = SDRAM_LOADMODE_BURSTLEN;
    load_mode.Bits.BurstType = LOADMODE_BURSTTYPE_SEQUENTIAL;
    load_mode.Bits.CASLatency = SDRAM_LOADMODE_CASLATENCY;
    load_mode.Bits.OpMode = LOADMODE_OPMODE_STANDARD;
    load_mode.Bits.WBMode = LOADMODE_WBMODE_BURST;

    SDRAM_EnableClock(ENABLE);
    SDRAM_SetOperationCode(SDRAM_OPCODE_LOADMODE);
    SDRAM_SetDeviceSelect(SDRAM_CS_SELECT);
    SDRAM_SetBank(SDRAM_BANKADD_1);
    SDRAM_SetAddress(load_mode.cmd);
    (void)(SDRAM->OR);

    /* Wait at least 300us for SDRAM stabilization (per SDK) */
    for (delay = 0; delay < 0xFFFF; delay++);
}
int sdram_test(void);
/*----------------------------------------------------------------------------
 * SDRAM Init (called via INIT_BOARD_EXPORT)
 *---------------------------------------------------------------------------*/
static int SDRAM_Init(void)
{
    int result = RT_EOK;

#ifdef BSP_SDRAM_BANK1
    sdram_device = SDRAM_DEVICE_1;
#endif
#ifdef BSP_SDRAM_BANK2
    sdram_device = SDRAM_DEVICE_2;
#endif

    /* Reset SDRAM peripheral to default state */
    SDRAM_DeInit();

    /* Initialize SDRAM clock (board-specific, weak function) */
    rt_hw_sdram_clock_init();

    /* Configure and initialize the SDRAM device */
    SDRAM_Initialization_Sequence(sdram_device);

    LOG_D("sdram init success, mapped at 0x%X, size is %u bytes, data width is %d",
          SDRAM_BANK_ADDR, (BSP_SDRAM_SIZE * 1024U * 1024U), SDRAM_DATA_WIDTH);

#ifdef RT_USING_MEMHEAP_AS_HEAP
    /* Register SDRAM as system heap */
    rt_memheap_init(&system_heap, "sdram", (void *)SDRAM_BANK_ADDR, (BSP_SDRAM_SIZE * 1024U * 1024U));
    LOG_D("memheap registered: name=%s, start=0x%X, size=%u",
          ((struct rt_object *)&system_heap)->name,
          system_heap.start_addr, system_heap.pool_size);
#endif


    return result;
}
INIT_BOARD_EXPORT(SDRAM_Init);

/*----------------------------------------------------------------------------
 * SDRAM Test Command (Finsh shell, enabled by DRV_DEBUG)
 *---------------------------------------------------------------------------*/
#ifdef DRV_DEBUG
//#ifdef FINSH_USING_MSH
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

    /* Write data */
    LOG_D("Writing %u bytes data, waiting...", (BSP_SDRAM_SIZE * 1024U * 1024U));
    start_time = rt_tick_get();
    for (i = 0; i < (BSP_SDRAM_SIZE * 1024U * 1024U) / data_width; i++)
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
    LOG_D("Write done, time: %d.%03dS.",
          time_cast / RT_TICK_PER_SECOND,
          time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND + 999) / 1000));

    /* Read and verify */
    LOG_D("Reading and verifying data, waiting...");
    for (i = 0; i < (BSP_SDRAM_SIZE * 1024U * 1024U) / data_width; i++)
    {
#if SDRAM_DATA_WIDTH == 8
        data = *(__IO uint8_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != (uint8_t)(i % 100))
        {
            LOG_E("SDRAM test failed at offset 0x%X!", i * data_width);
            break;
        }
#elif SDRAM_DATA_WIDTH == 16
        data = *(__IO uint16_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != (uint16_t)(i % 1000))
        {
            LOG_E("SDRAM test failed at offset 0x%X!", i * data_width);
            break;
        }
#else
        data = *(__IO uint32_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != i % 1000)
        {
            LOG_E("SDRAM test failed at offset 0x%X!", i * data_width);
            break;
        }
#endif
    }

    if (i >= (BSP_SDRAM_SIZE * 1024U * 1024U) / data_width)
    {
        LOG_D("SDRAM test success!");
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(sdram_test, sdram read / write test)
//#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */

#endif /* BSP_USING_SDRAM */
