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
#if defined(BSP_USING_ON_CHIP_FLASH_ICODE_CACHE)
    EFM_ICacheCmd(ENABLE);
#endif
#if defined(BSP_USING_ON_CHIP_FLASH_DCODE_CACHE)
    EFM_DCacheCmd(ENABLE);
#endif
#if defined(BSP_USING_ON_CHIP_FLASH_ICODE_PREFETCH)
    EFM_PrefetchCmd(ENABLE);
#endif
    /* Reset the VBAT area */
    PWC_VBAT_Reset();
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{
    stc_clock_xtal_init_t stcXtalInit;
    stc_clock_pll_init_t stcPLLHInit;
#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
    stc_clock_pllx_init_t stcPLLAInit;
#endif
#if defined(BSP_RTC_USING_XTAL32) || defined(RT_USING_PM)
    stc_clock_xtal32_init_t stcXtal32Init;
#endif

    /* PCLK0, HCLK  Max 240MHz */
    /* PCLK1, PCLK4 Max 120MHz */
    /* PCLK2, PCLK3 Max 60MHz  */
    /* EX BUS Max 120MHz */
    CLK_SetClockDiv(CLK_BUS_CLK_ALL, \
                    (CLK_PCLK0_DIV1 | CLK_PCLK1_DIV2 | CLK_PCLK2_DIV4 | \
                     CLK_PCLK3_DIV4 | CLK_PCLK4_DIV2 | CLK_EXCLK_DIV2 | \
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
    /* VCO = (8/1)*120 = 960MHz*/
    stcPLLHInit.u8PLLState = CLK_PLL_ON;
    stcPLLHInit.PLLCFGR = 0UL;
    stcPLLHInit.PLLCFGR_f.PLLM = 1UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLN = 120UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLP = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLQ = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLR = 4UL - 1UL;
    stcPLLHInit.PLLCFGR_f.PLLSRC = CLK_PLL_SRC_XTAL;
    (void)CLK_PLLInit(&stcPLLHInit);

    /* Highspeed SRAM set to 0 Read/Write wait cycle */
    SRAM_SetWaitCycle(SRAM_SRAMH, SRAM_WAIT_CYCLE0, SRAM_WAIT_CYCLE0);
    /* SRAM1_2_3_4_backup set to 1 Read/Write wait cycle */
    SRAM_SetWaitCycle((SRAM_SRAM123 | SRAM_SRAM4 | SRAM_SRAMB), SRAM_WAIT_CYCLE1, SRAM_WAIT_CYCLE1);
    /* 0-wait @ 40MHz */
    (void)EFM_SetWaitCycle(EFM_WAIT_CYCLE5);
    /* 4 cycles for 200 ~ 250MHz */
    GPIO_SetReadWaitCycle(GPIO_RD_WAIT4);
    CLK_SetSysClockSrc(CLK_SYSCLK_SRC_PLL);

#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
    /* PLLX for USB */
    (void)CLK_PLLxStructInit(&stcPLLAInit);
    /* VCO = (8/2)*120 = 480MHz*/
    stcPLLAInit.u8PLLState = CLK_PLL_ON;
    stcPLLAInit.PLLCFGR = 0UL;
    stcPLLAInit.PLLCFGR_f.PLLM = 2UL - 1UL;
    stcPLLAInit.PLLCFGR_f.PLLN = 120UL - 1UL;
    stcPLLAInit.PLLCFGR_f.PLLP = 10UL - 1UL;
    stcPLLAInit.PLLCFGR_f.PLLQ = 4UL - 1UL;
    stcPLLAInit.PLLCFGR_f.PLLR = 4UL - 1UL;
    (void)CLK_PLLxInit(&stcPLLAInit);
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
#if defined(BSP_USING_CAN1)
    CLK_SetCANClockSrc(CLK_CAN1, CLK_CANCLK_SYSCLK_DIV6);
#endif
#if defined(BSP_USING_CAN2)
    CLK_SetCANClockSrc(CLK_CAN2, CLK_CANCLK_SYSCLK_DIV6);
#endif

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
