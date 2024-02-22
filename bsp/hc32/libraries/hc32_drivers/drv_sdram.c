/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-24     CDT          first version
 * 2024-02-20     CDT          modify exclk clock max frequency to 40MHz for HC32F4A0
 *                             add t_rcd_p/t_rfc_p/t_rp_p configuration
 */


/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>


#if defined(BSP_USING_EXMC)
#if defined(BSP_USING_SDRAM)

#include "drv_sdram.h"
#include "board_config.h"
#include "sdram_port.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
//#define DRV_DEBUG
#define LOG_TAG "drv.sdram"
#include <drv_log.h>

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
#if defined (BSP_USING_SDRAM)
    rt_err_t rt_hw_board_sdram_init(void);
#endif

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
#ifdef RT_USING_MEMHEAP_AS_HEAP
    static struct rt_memheap _system_heap;
#endif

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  SDRAM initialization sequence.
 * @param  [in] chip                        The command chip number.
 * @param  [in] md_reg_value                The SDRAM mode register value
 * @retval None
 */
static void _sdram_initialization_sequence(rt_uint32_t chip, rt_uint32_t md_reg_value)
{
    /* SDRAM initialization sequence:
       CMD NOP->PrechargeAll->AutoRefresh->AutoRefresh->MdRegConfig->NOP */
    (void)EXMC_DMC_SetCommand(chip, 0UL, EXMC_DMC_CMD_NOP, 0UL);
    (void)EXMC_DMC_SetCommand(chip, 0UL, EXMC_DMC_CMD_PRECHARGE_ALL, 0UL);
    (void)EXMC_DMC_SetCommand(chip, 0UL, EXMC_DMC_CMD_AUTO_REFRESH, 0UL);
    (void)EXMC_DMC_SetCommand(chip, 0UL, EXMC_DMC_CMD_AUTO_REFRESH, 0UL);
    (void)EXMC_DMC_SetCommand(chip, 0UL, EXMC_DMC_CMD_MDREG_CONFIG, md_reg_value);
    (void)EXMC_DMC_SetCommand(chip, 0UL, EXMC_DMC_CMD_NOP, 0UL);
}

/**
 * @brief  verify clock frequency.
 * @retval result
 */
static rt_int32_t _sdram_verify_clock_frequency(void)
{
    rt_int32_t ret = RT_EOK;

#if defined (HC32F4A0)
    /* EXCLK max frequency for SDRAM: 40MHz */
    if (CLK_GetBusClockFreq(CLK_BUS_EXCLK) > (40 * 1000000))
    {
        ret = -RT_ERROR;
    }
#endif

    return ret;
}

/**
 * @brief  SDRAM initialization.
 * @param  None
 * @retval result
 */
static rt_int32_t _sdram_init(void)
{
    rt_uint32_t md_reg_value;
    stc_exmc_dmc_init_t stcDmcInit;
    stc_exmc_dmc_chip_config_t stcCsConfig;

    /* verify SDRAM clock frequency */
    if (_sdram_verify_clock_frequency() != RT_EOK)
    {
        LOG_E("EXMC clock frequency is over limit for SDRAM!");
        return -RT_ERROR;
    }

    /* initialization SDRAM port.*/
    rt_hw_board_sdram_init();

    /* enable DMC clock */
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_DMC, ENABLE);

    /* enable DMC. */
    EXMC_DMC_Cmd(ENABLE);

    /* configure DMC width && refresh period & chip & timing. */
    (void)EXMC_DMC_StructInit(&stcDmcInit);
    stcDmcInit.u32RefreshPeriod        = SDRAM_REFRESH_COUNT;
    stcDmcInit.u32ColumnBitsNumber     = SDRAM_COLUMN_BITS;
    stcDmcInit.u32RowBitsNumber        = SDRAM_ROW_BITS;
    stcDmcInit.u32MemBurst             = SDRAM_BURST_LENGTH;
    stcDmcInit.u32AutoRefreshChips     = EXMC_DMC_AUTO_REFRESH_4CHIPS;
    stcDmcInit.stcTimingConfig.u8CASL  = SDRAM_CAS_LATENCY;
    stcDmcInit.stcTimingConfig.u8DQSS  = 0U;
    stcDmcInit.stcTimingConfig.u8MRD   = SDRAM_TMDR;
    stcDmcInit.stcTimingConfig.u8RAS   = SDRAM_TRAS;
    stcDmcInit.stcTimingConfig.u8RC    = SDRAM_TRC;
    stcDmcInit.stcTimingConfig.u8RCD_B = SDRAM_TRCD_B;
    stcDmcInit.stcTimingConfig.u8RCD_P = SDRAM_TRCD_P;
    stcDmcInit.stcTimingConfig.u8RFC_B = SDRAM_TRFC_B;
    stcDmcInit.stcTimingConfig.u8RFC_P = SDRAM_TRFC_P;
    stcDmcInit.stcTimingConfig.u8RP_B  = SDRAM_TRP_B;
    stcDmcInit.stcTimingConfig.u8RP_P  = SDRAM_TRP_P;
    stcDmcInit.stcTimingConfig.u8RRD   = SDRAM_TRRD;
    stcDmcInit.stcTimingConfig.u8WR    = SDRAM_TWR;
    stcDmcInit.stcTimingConfig.u8WTR   = SDRAM_TWTR;
    stcDmcInit.stcTimingConfig.u8XP    = SDRAM_TXP;
    stcDmcInit.stcTimingConfig.u8XSR   = SDRAM_TXSR;
    stcDmcInit.stcTimingConfig.u8ESR   = SDRAM_TESR;
    (void)EXMC_DMC_Init(&stcDmcInit);

    /* configure DMC address space. */
    stcCsConfig.u32AddrMatch      = (SDRAM_BANK_ADDR >> 24);
    stcCsConfig.u32AddrMask       = EXMC_DMC_ADDR_MASK_128MB;
    stcCsConfig.u32AddrDecodeMode = EXMC_DMC_CS_DECODE_ROWBANKCOL;
    (void)EXMC_DMC_ChipConfig(SDRAM_CHIP, &stcCsConfig);

    /* SDRAM initialization sequence. */
    md_reg_value = (SDRAM_MODEREG_BURST_TYPE | SDRAM_MODEREG_WRITEBURST_MODE | SDRAM_MODEREG_OPERATING_MODE);
    if (2U == stcDmcInit.stcTimingConfig.u8CASL)
    {
        md_reg_value |= SDRAM_MODEREG_CAS_LATENCY_2;
    }
    else
    {
        md_reg_value |= SDRAM_MODEREG_CAS_LATENCY_3;
    }

    if (EXMC_DMC_BURST_1BEAT == stcDmcInit.u32MemBurst)
    {
        md_reg_value |= SDRAM_MODEREG_BURST_LENGTH_1;
    }
    else if (EXMC_DMC_BURST_2BEAT == stcDmcInit.u32MemBurst)
    {
        md_reg_value |= SDRAM_MODEREG_BURST_LENGTH_2;
    }
    else if (EXMC_DMC_BURST_4BEAT == stcDmcInit.u32MemBurst)
    {
        md_reg_value |= SDRAM_MODEREG_BURST_LENGTH_4;
    }
    else
    {
        md_reg_value |= SDRAM_MODEREG_BURST_LENGTH_8;
    }

    _sdram_initialization_sequence(SDRAM_CHIP, md_reg_value);

    /* switch state from configure to ready */
    EXMC_DMC_SetState(EXMC_DMC_CTRL_STATE_GO);
    EXMC_DMC_SetState(EXMC_DMC_CTRL_STATE_WAKEUP);
    EXMC_DMC_SetState(EXMC_DMC_CTRL_STATE_GO);

    return RT_EOK;
}

int rt_hw_sdram_init(void)
{
    rt_int32_t ret;

    ret = _sdram_init();
    if (RT_EOK != ret)
    {
        LOG_E("SDRAM init failed!");
        return -RT_ERROR;
    }

#ifdef RT_USING_MEMHEAP_AS_HEAP
    /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SDRAM is initialized to the heap */
    rt_memheap_init(&_system_heap, "sdram", (void *)SDRAM_BANK_ADDR, SDRAM_SIZE);
#endif

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_sdram_init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
static int _sdram_test(void)
{
    rt_uint32_t i;
    rt_uint32_t start_time;
    rt_uint32_t time_cast;
#if SDRAM_DATA_WIDTH == EXMC_DMC_MEMORY_WIDTH_16BIT
    const char data_width = 2;
    rt_uint16_t data = 0;
#else
    char data_width = 4;
    rt_uint32_t data = 0;
#endif

    /* write data */
    LOG_D("writing the %ld bytes data, waiting....", SDRAM_SIZE);
    start_time = rt_tick_get();
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
#if SDRAM_DATA_WIDTH == EXMC_DMC_MEMORY_WIDTH_16BIT
        *(__IO uint16_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint16_t)(i % 1000);
#else
        *(__IO uint32_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint32_t)(i % 1000);
#endif
    }
    time_cast = rt_tick_get() - start_time;
    LOG_D("write data success, total time: %d.%03dS.", time_cast / RT_TICK_PER_SECOND,
          time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));

    /* read data */
    LOG_D("start reading and verifying data, waiting....");
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
#if SDRAM_DATA_WIDTH == EXMC_DMC_MEMORY_WIDTH_16BIT
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
MSH_CMD_EXPORT(_sdram_test, sdram test)
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_SDRAM */
#endif /* BSP_USING_EXMC */
