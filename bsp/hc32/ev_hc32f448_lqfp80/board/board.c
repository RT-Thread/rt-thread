/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 * 2024-06-07     CDT          Add XTAL divider config code for RTC
 */

#include "board.h"
#include "board_config.h"

/* unlock/lock peripheral */
#define EXAMPLE_PERIPH_WE               (LL_PERIPH_GPIO | LL_PERIPH_EFM | LL_PERIPH_FCG | \
                                         LL_PERIPH_PWC_CLK_RMU | LL_PERIPH_SRAM | LL_PERIPH_LVD)
#define EXAMPLE_PERIPH_WP               (LL_PERIPH_EFM | LL_PERIPH_FCG | LL_PERIPH_SRAM)

/** System Base Configuration
*/
void SystemBase_Config(void)
{
#if defined(BSP_USING_ON_CHIP_FLASH_ICODE_CACHE)
    EFM_ICacheCmd(ENABLE);
#endif
#if defined(BSP_USING_ON_CHIP_FLASH_DCODE_CACHE)
    EFM_DCacheCmd(ENABLE);
#endif
#if defined(BSP_USING_ON_CHIP_FLASH_ICODE_PREFETCH)
    EFM_PrefetchCmd(ENABLE);
#endif
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{
    stc_clock_xtal_init_t stcXtalInit;
    stc_clock_pll_init_t stcPLLHInit;
#if defined(BSP_RTC_USING_XTAL32) || defined(RT_USING_PM)
    stc_clock_xtal32_init_t stcXtal32Init;
#endif
#if defined(BSP_RTC_USING_XTAL_DIV)
    stc_clock_xtaldiv_init_t stcXtaldivInit;
#endif

    /* PCLK0, HCLK Max 200MHz */
    /* PCLK1, PCLK4 Max 100MHz */
    /* PCLK2, EXCLK Max 60MHz */
    /* PCLK3 Max 50MHz */
    CLK_SetClockDiv(CLK_BUS_CLK_ALL,
                    (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV2 | CLK_PCLK2_DIV4 |
                     CLK_PCLK3_DIV4 | CLK_PCLK4_DIV2 | CLK_EXCLK_DIV4 |
                     CLK_HCLK_DIV1));

    GPIO_AnalogCmd(XTAL_PORT, XTAL_IN_PIN | XTAL_OUT_PIN, ENABLE);
    (void)CLK_XtalStructInit(&stcXtalInit);
    /* Config Xtal and enable Xtal */
    stcXtalInit.u8Mode   = CLK_XTAL_MD_OSC;
    stcXtalInit.u8Drv    = CLK_XTAL_DRV_ULOW;
    stcXtalInit.u8State  = CLK_XTAL_ON;
    stcXtalInit.u8StableTime = CLK_XTAL_STB_2MS;
    (void)CLK_XtalInit(&stcXtalInit);

    (void)CLK_PLLStructInit(&stcPLLHInit);
    /* VCO = (8/1)*100 = 800MHz*/
    stcPLLHInit.u8PLLState = CLK_PLL_ON;
    stcPLLHInit.PLLCFGR = 0UL;
    stcPLLHInit.PLLCFGR_f.PLLM = 1UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLN = 100UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLP = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLQ = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLR = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLSRC = CLK_PLL_SRC_XTAL;
    (void)CLK_PLLInit(&stcPLLHInit);

    /* 3 cycles for 150 ~ 200MHz */
    (void)EFM_SetWaitCycle(EFM_WAIT_CYCLE3);
    /* 3 cycles for 150 ~ 200MHz */
    GPIO_SetReadWaitCycle(GPIO_RD_WAIT3);
    CLK_SetSysClockSrc(CLK_SYSCLK_SRC_PLL);

#if defined(BSP_RTC_USING_XTAL32) || defined(RT_USING_PM)
    /* Xtal32 config */
    GPIO_AnalogCmd(XTAL32_PORT, XTAL32_IN_PIN | XTAL32_OUT_PIN, ENABLE);
    (void)CLK_Xtal32StructInit(&stcXtal32Init);
    stcXtal32Init.u8State  = CLK_XTAL32_ON;
    stcXtal32Init.u8Drv    = CLK_XTAL32_DRV_HIGH;
    stcXtal32Init.u8Filter = CLK_XTAL32_FILTER_RUN_MD;
    (void)CLK_Xtal32Init(&stcXtal32Init);
#endif

#if defined(BSP_RTC_USING_XTAL_DIV)
    /* Xtal Div config */
    (void)CLK_XtalDivStructInit(&stcXtaldivInit);
    /* 8000000Hz / 32768Hz = 0x7A12 / 0x80 */
    stcXtaldivInit.u32Num = 0x7A12UL;
    stcXtaldivInit.u32Den = 0x80UL;
    stcXtaldivInit.u32State = CLK_XTALDIV_ON;
    (void)CLK_XtalDivInit(&stcXtaldivInit);
#endif
}

/** Peripheral Clock Configuration
*/
void PeripheralClock_Config(void)
{
#if defined(BSP_USING_MCAN1)
    CLK_SetCANClockSrc(CLK_MCAN1, CLK_MCANCLK_SYSCLK_DIV5);
#endif
#if defined(BSP_USING_MCAN2)
    CLK_SetCANClockSrc(CLK_MCAN2, CLK_MCANCLK_SYSCLK_DIV5);
#endif

#if defined(RT_USING_ADC)
    CLK_SetPeriClockSrc(CLK_PERIPHCLK_PCLK);
#endif
}

/** Peripheral Registers Unlock
*/
void PeripheralRegister_Unlock(void)
{
    LL_PERIPH_WE(EXAMPLE_PERIPH_WE);
}
