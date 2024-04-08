/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#include "board.h"
#include "board_config.h"

/* unlock/lock peripheral */
#define EXAMPLE_PERIPH_WE               (LL_PERIPH_GPIO | LL_PERIPH_EFM | LL_PERIPH_FCG | \
                                         LL_PERIPH_PWC_CLK_RMU | LL_PERIPH_SRAM)
#define EXAMPLE_PERIPH_WP               (LL_PERIPH_EFM | LL_PERIPH_FCG | LL_PERIPH_SRAM)

#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
/**
 * @brief Switch clock stable time
 * @note Approx. 30us
 */
#define CLK_SYSCLK_SW_STB               (HCLK_VALUE / 50000UL)
/**
 * @brief Clk delay function
 * @param [in] u32Delay         count
 * @retval when switch clock source, should be delay some time to wait stable.
 */
static void CLK_Delay(uint32_t u32Delay)
{
    __IO uint32_t u32Timeout = 0UL;

    while (u32Timeout < u32Delay)
    {
        u32Timeout++;
    }
}
#endif

/** System Base Configuration
*/
void SystemBase_Config(void)
{
#if defined(BSP_USING_ON_CHIP_FLASH_CACHE)
    EFM_CacheCmd(ENABLE);
#endif
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{
    stc_clock_xtal_init_t     stcXtalInit;
    stc_clock_pll_init_t      stcMpllInit;
#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
    stc_clock_pllx_init_t stcUpllInit;
#endif
#if defined(BSP_RTC_USING_XTAL32) || defined(RT_USING_PM)
    stc_clock_xtal32_init_t stcXtal32Init;
#endif

    /* PCLK0, HCLK  Max 200MHz */
    /* PCLK1, PCLK4 Max 100MHz */
    /* PCLK2, PCLK3 Max 50MHz  */
    /* EX BUS Max 100MHz */
    CLK_SetClockDiv(CLK_BUS_CLK_ALL, (CLK_HCLK_DIV1 | CLK_EXCLK_DIV2 | CLK_PCLK0_DIV1 | CLK_PCLK1_DIV2 | \
                                      CLK_PCLK2_DIV4 | CLK_PCLK3_DIV4 | CLK_PCLK4_DIV2));

    GPIO_AnalogCmd(XTAL_PORT, XTAL_IN_PIN | XTAL_OUT_PIN, ENABLE);
    (void)CLK_XtalStructInit(&stcXtalInit);
    /* Config Xtal and enable Xtal */
    stcXtalInit.u8Mode  = CLK_XTAL_MD_OSC;
    stcXtalInit.u8Drv   = CLK_XTAL_DRV_ULOW;
    stcXtalInit.u8State = CLK_XTAL_ON;
    stcXtalInit.u8StableTime = CLK_XTAL_STB_2MS;
    (void)CLK_XtalInit(&stcXtalInit);

    (void)CLK_PLLStructInit(&stcMpllInit);
    /* MPLL config (XTAL / pllmDiv * plln / PllpDiv = 200M). */
    stcMpllInit.u8PLLState = CLK_PLL_ON;
    stcMpllInit.PLLCFGR = 0UL;
    stcMpllInit.PLLCFGR_f.PLLM = 1UL - 1UL;
    stcMpllInit.PLLCFGR_f.PLLN = 50UL - 1UL;
    stcMpllInit.PLLCFGR_f.PLLP = 2UL - 1UL;
    stcMpllInit.PLLCFGR_f.PLLQ = 2UL - 1UL;
    stcMpllInit.PLLCFGR_f.PLLR = 2UL - 1UL;
    stcMpllInit.PLLCFGR_f.PLLSRC = CLK_PLL_SRC_XTAL;
    (void)CLK_PLLInit(&stcMpllInit);

    /* sram init include read/write wait cycle setting */
    SRAM_SetWaitCycle(SRAM_SRAMH, SRAM_WAIT_CYCLE0, SRAM_WAIT_CYCLE0);
    SRAM_SetWaitCycle((SRAM_SRAM12 | SRAM_SRAM3 | SRAM_SRAMR), SRAM_WAIT_CYCLE1, SRAM_WAIT_CYCLE1);

    /* flash read wait cycle setting */
    (void)EFM_SetWaitCycle(EFM_WAIT_CYCLE5);
    /* 3 cycles for 126MHz ~ 200MHz */
    GPIO_SetReadWaitCycle(GPIO_RD_WAIT3);
    /* Switch driver ability */
    (void)PWC_HighSpeedToHighPerformance();
    /* Switch system clock source to MPLL. */
    CLK_SetSysClockSrc(CLK_SYSCLK_SRC_PLL);

#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
    /* PLLX for USB */
    (void)CLK_PLLxStructInit(&stcUpllInit);
    /* VCO = (8/2)*120 = 480MHz*/
    stcUpllInit.u8PLLState = CLK_PLL_ON;
    stcUpllInit.PLLCFGR = 0UL;
    stcUpllInit.PLLCFGR_f.PLLM = 2UL - 1UL;
    stcUpllInit.PLLCFGR_f.PLLN = 120UL - 1UL;
    stcUpllInit.PLLCFGR_f.PLLP = 10UL - 1UL;
    stcUpllInit.PLLCFGR_f.PLLQ = 6UL - 1UL;
    stcUpllInit.PLLCFGR_f.PLLR = 6UL - 1UL;
    (void)CLK_PLLxInit(&stcUpllInit);
#endif

#if defined(BSP_RTC_USING_XTAL32) || defined(RT_USING_PM)
    /* Xtal32 config */
    GPIO_AnalogCmd(XTAL32_PORT, XTAL32_IN_PIN | XTAL32_OUT_PIN, ENABLE);
    (void)CLK_Xtal32StructInit(&stcXtal32Init);
    stcXtal32Init.u8State  = CLK_XTAL32_ON;
    stcXtal32Init.u8Drv    = CLK_XTAL32_DRV_HIGH;
    stcXtal32Init.u8Filter = CLK_XTAL32_FILTER_RUN_MD;
    (void)CLK_Xtal32Init(&stcXtal32Init);
#endif
}

/** Peripheral Clock Configuration
*/
void PeripheralClock_Config(void)
{
#if defined(RT_USING_ADC)
    CLK_SetPeriClockSrc(CLK_PERIPHCLK_PCLK);
#endif

#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
    CLK_SetUSBClockSrc(CLK_USBCLK_PLLXP);
    /* Wait stable here, since the current DDL API does not include this */
    CLK_Delay(CLK_SYSCLK_SW_STB);
#endif
}

/** Peripheral Registers Unlock
*/
void PeripheralRegister_Unlock(void)
{
    LL_PERIPH_WE(EXAMPLE_PERIPH_WE);
}

/*@}*/
