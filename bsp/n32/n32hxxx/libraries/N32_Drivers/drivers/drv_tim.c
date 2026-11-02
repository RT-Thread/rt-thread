/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-02-26     ox-horse         first version
 * 2026-08-19     ox-horse         Add N32H47X_48X
 * 2026-08-19     ox-horse         Add N32H49X
 */

#include <rtdevice.h>
#include "drv_config.h"
#include "drv_tim.h"

/* The driver owns the peripheral registers, so it pulls in the peripheral
 * header itself instead of relying on board.h to have declared it.
 */
#if defined(SOC_SERIES_N32H7xx)
#include <n32h7xx_tim.h>
#elif defined(SOC_SERIES_N32H49x)
#include <n32h49x_tim.h>
#elif defined(SOC_SERIES_N32H47x_48x)
#include <n32h47x_48x_tim.h>
#endif

//#define DRV_DEBUG
#define LOG_TAG "drv.tim"
#include <drv_log.h>

#if defined(SOC_SERIES_N32H7xx)
#if defined(BSP_USING_ATIM1) && !defined(ATIM1)
#error "A-timer1 doesn't exist in this N32 series, but you enabled the BSP_USING_ATIM1"
#endif
#if defined(BSP_USING_ATIM2) && !defined(ATIM2)
#error "A-timer2 doesn't exist in this N32 series, but you enabled the BSP_USING_ATIM2"
#endif
#if defined(BSP_USING_ATIM3) && !defined(ATIM3)
#error "A-timer3 doesn't exist in this N32 series, but you enabled the BSP_USING_ATIM3"
#endif
#if defined(BSP_USING_ATIM4) && !defined(ATIM4)
#error "A-timer4 doesn't exist in this N32 series, but you enabled the BSP_USING_ATIM4"
#endif
#if defined(BSP_USING_GTIMA1) && !defined(GTIMA1)
#error "G-timer-A1 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIMA1"
#endif
#if defined(BSP_USING_GTIMA2) && !defined(GTIMA2)
#error "G-timer-A2 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIMA2"
#endif
#if defined(BSP_USING_GTIMA3) && !defined(GTIMA3)
#error "G-timer-A3 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIMA3"
#endif
#if defined(BSP_USING_GTIMA4) && !defined(GTIMA4)
#error "G-timer-A4 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIMA4"
#endif
#if defined(BSP_USING_GTIMA5) && !defined(GTIMA5)
#error "G-timer-A5 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIMA5"
#endif
#if defined(BSP_USING_GTIMA6) && !defined(GTIMA6)
#error "G-timer-A6 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIMA6"
#endif
#if defined(BSP_USING_GTIMA7) && !defined(GTIMA7)
#error "G-timer-A7 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIMA7"
#endif
#if defined(BSP_USING_GTIMB1) && !defined(GTIMB1)
#error "G-timer-B1 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIMB1"
#endif
#if defined(BSP_USING_GTIMB2) && !defined(GTIMB2)
#error "G-timer-B2 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIMB2"
#endif
#if defined(BSP_USING_GTIMB3) && !defined(GTIMB3)
#error "G-timer-B3 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIMB3"
#endif
#if defined(BSP_USING_BTIM1) && !defined(BTIM1)
#error "B-timer1 doesn't exist in this N32 series, but you enabled the BSP_USING_BTIM1"
#endif
#if defined(BSP_USING_BTIM2) && !defined(BTIM2)
#error "B-timer2 doesn't exist in this N32 series, but you enabled the BSP_USING_BTIM2"
#endif
#if defined(BSP_USING_BTIM3) && !defined(BTIM3)
#error "B-timer3 doesn't exist in this N32 series, but you enabled the BSP_USING_BTIM3"
#endif
#if defined(BSP_USING_BTIM4) && !defined(BTIM4)
#error "B-timer4 doesn't exist in this N32 series, but you enabled the BSP_USING_BTIM4"
#endif
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
#if defined(BSP_USING_ATIM1) && !defined(ATIM1)
#error "A-timer1 doesn't exist in this N32 series, but you enabled the BSP_USING_ATIM1"
#endif
#if defined(BSP_USING_ATIM2) && !defined(ATIM2)
#error "A-timer2 doesn't exist in this N32 series, but you enabled the BSP_USING_ATIM2"
#endif
#if defined(BSP_USING_ATIM3) && !defined(ATIM3)
#error "A-timer3 doesn't exist in this N32 series, but you enabled the BSP_USING_ATIM3"
#endif
#if defined(BSP_USING_GTIM1) && !defined(GTIM1)
#error "G-timer1 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIM1"
#endif
#if defined(BSP_USING_GTIM2) && !defined(GTIM2)
#error "G-timer2 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIM2"
#endif
#if defined(BSP_USING_GTIM3) && !defined(GTIM3)
#error "G-timer3 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIM3"
#endif
#if defined(BSP_USING_GTIM4) && !defined(GTIM4)
#error "G-timer4 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIM4"
#endif
#if defined(BSP_USING_GTIM5) && !defined(GTIM5)
#error "G-timer5 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIM5"
#endif
#if defined(BSP_USING_GTIM6) && !defined(GTIM6)
#error "G-timer6 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIM6"
#endif
#if defined(BSP_USING_GTIM7) && !defined(GTIM7)
#error "G-timer7 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIM7"
#endif
#if defined(BSP_USING_GTIM8) && !defined(GTIM8)
#error "G-timer8 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIM8"
#endif
#if defined(BSP_USING_GTIM9) && !defined(GTIM9)
#error "G-timer9 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIM9"
#endif
#if defined(BSP_USING_GTIM10) && !defined(GTIM10)
#error "G-timer10 doesn't exist in this N32 series, but you enabled the BSP_USING_GTIM10"
#endif
#if defined(BSP_USING_BTIM1) && !defined(BTIM1)
#error "B-timer1 doesn't exist in this N32 series, but you enabled the BSP_USING_BTIM1"
#endif
#if defined(BSP_USING_BTIM2) && !defined(BTIM2)
#error "B-timer2 doesn't exist in this N32 series, but you enabled the BSP_USING_BTIM2"
#endif
#endif

#if defined(SOC_SERIES_N32H7xx)

#define INT_MAX (0x7FFFFFFF)

static int int_pow(int x, int y)
{
    if (y == 0)
    {
        return 1;
    }

    if (x == 0)
    {
        if (y > 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }

    if (y < 0)
    {
        return -1;
    }

    int result = 1;
    int base = x;
    int exponent = y;

    /* Fast exponentiation algorithm (binary exponentiation) */
    while (exponent > 0)
    {
        /* Check for overflow */
        if (result > INT_MAX / base)
        {
            return -1;
        }

        if (exponent % 2 == 1)
        {
            result *= base;
        }

        exponent /= 2;

        if (exponent > 0)
        {
            if (base > INT_MAX / base)
            {
                return -1;
            }

            base *= base;
        }
    }

    return result;
}

#endif /* SOC_SERIES_N32H7xx */

void n32_tim_ahbx_div_get(TIM_Module *timer, rt_uint32_t *div)
{
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(div != RT_NULL);

    *div = 1;

#if defined(SOC_SERIES_N32H7xx)
    rt_uint8_t tim_div, i;
    const rt_uint8_t div_group[] = { 0x00U, 0x04U, 0x05U, 0x06U, 0x07U };

    if ((timer == BTIM1) || (timer == BTIM2) || (timer == BTIM3) || (timer == BTIM4))
    {
        tim_div = ((RCC->APB1DIV1 & RCC_APB1DIV1_APB1BTIMDIV) >> 24U);
    }
    else if ((timer == ATIM1) || (timer == ATIM2))
    {
        tim_div = ((RCC->APB2DIV1 & RCC_APB2DIV1_APB2ATIMDIV) >> 28U);
    }
    else if ((timer == ATIM3) || (timer == ATIM4))
    {
        tim_div = ((RCC->APB5DIV1 & RCC_APB5DIV1_APB5ATIMDIV) >> 28U);
    }
    else if ((timer == GTIMA1) || (timer == GTIMA2) || (timer == GTIMA3))
    {
        tim_div = ((RCC->APB2DIV1 & RCC_APB2DIV1_APB2GTIMDIV) >> 24U);
    }
    else
    {
        tim_div = ((RCC->APB1DIV1 & RCC_APB1DIV1_APB1GTIMDIV) >> 16U);
    }

    for (i = 0; i < 5U; i++)
    {
        if (div_group[i] == tim_div)
        {
            *div = int_pow(2, i);
            break;
        }
    }
#endif /* defined(SOC_SERIES_N32H7xx) */
}

#if defined(SOC_SERIES_N32H47x_48x)
rt_uint32_t n32_tim_clock_freq_get(TIM_Module *timer)
{
    RCC_ClocksType rcc_clocks;

    RT_ASSERT(timer != RT_NULL);
    RCC_GetClocksFreqValue(&rcc_clocks);

    if (RT_FALSE)
        ;
#ifdef ATIM1
    else if (timer == ATIM1)
    {
        return (RCC->CFG2 & RCC_CFG2_ATIMCLKSEL) ? rcc_clocks.HclkFreq : rcc_clocks.SysclkFreq;
    }
#endif /* ATIM1 */
#ifdef ATIM2
    else if (timer == ATIM2)
    {
        return (RCC->CFG2 & RCC_CFG2_ATIMCLKSEL) ? rcc_clocks.HclkFreq : rcc_clocks.SysclkFreq;
    }
#endif /* ATIM2 */
#ifdef ATIM3
    else if (timer == ATIM3)
    {
        return (RCC->CFG2 & RCC_CFG2_ATIMCLKSEL) ? rcc_clocks.HclkFreq : rcc_clocks.SysclkFreq;
    }
#endif /* ATIM3 */
#ifdef GTIM8
    else if (timer == GTIM8)
    {
        return (RCC->CFG2 & RCC_CFG2_GTIMCLKSEL) ? rcc_clocks.SysclkFreq : ((rcc_clocks.Pclk2Freq == rcc_clocks.HclkFreq) ? rcc_clocks.Pclk2Freq : (rcc_clocks.Pclk2Freq * 2U));
    }
#endif /* GTIM8 */
#ifdef GTIM9
    else if (timer == GTIM9)
    {
        return (RCC->CFG2 & RCC_CFG2_GTIMCLKSEL) ? rcc_clocks.SysclkFreq : ((rcc_clocks.Pclk2Freq == rcc_clocks.HclkFreq) ? rcc_clocks.Pclk2Freq : (rcc_clocks.Pclk2Freq * 2U));
    }
#endif /* GTIM9 */
#ifdef GTIM10
    else if (timer == GTIM10)
    {
        return (RCC->CFG2 & RCC_CFG2_GTIMCLKSEL) ? rcc_clocks.SysclkFreq : ((rcc_clocks.Pclk2Freq == rcc_clocks.HclkFreq) ? rcc_clocks.Pclk2Freq : (rcc_clocks.Pclk2Freq * 2U));
    }
#endif /* GTIM10 */
    else
    {
        /* GTIM1-7 and BTIM use PCLK1, doubled when APB1 is prescaled. */
        return (rcc_clocks.Pclk1Freq == rcc_clocks.HclkFreq) ? rcc_clocks.Pclk1Freq : (rcc_clocks.Pclk1Freq * 2U);
    }

    return 0U;
}
#endif /* SOC_SERIES_N32H47x_48x */

#if defined(SOC_SERIES_N32H49x)
rt_uint32_t n32_tim_clock_freq_get(TIM_Module *timer)
{
    RCC_ClocksType rcc_clocks;

    RT_ASSERT(timer != RT_NULL);
    RCC_GetClocksFreqValue(&rcc_clocks);

    if (RT_FALSE)
        ;
#ifdef ATIM1
    else if (timer == ATIM1)
    {
        /* N32H49x: ATIMCLKSEL semantics are opposite to N32H47x_48x.
         * 49x: 0 -> HCLK, 1 -> SYSCLK (n32h49x_rcc.h RCC_ATIM_CLKSRC_HCLK = 0). */
        return (RCC->CFG2 & RCC_CFG2_ATIMCLKSEL) ? rcc_clocks.SysclkFreq : rcc_clocks.HclkFreq;
    }
#endif /* ATIM1 */
#ifdef ATIM2
    else if (timer == ATIM2)
    {
        /* N32H49x: ATIMCLKSEL semantics are opposite to N32H47x_48x. */
        return (RCC->CFG2 & RCC_CFG2_ATIMCLKSEL) ? rcc_clocks.SysclkFreq : rcc_clocks.HclkFreq;
    }
#endif /* ATIM2 */
#ifdef ATIM3
    else if (timer == ATIM3)
    {
        /* N32H49x: ATIMCLKSEL semantics are opposite to N32H47x_48x. */
        return (RCC->CFG2 & RCC_CFG2_ATIMCLKSEL) ? rcc_clocks.SysclkFreq : rcc_clocks.HclkFreq;
    }
#endif /* ATIM3 */
#ifdef GTIM8
    else if (timer == GTIM8)
    {
        return (RCC->CFG2 & RCC_CFG2_GTIMCLKSEL) ? rcc_clocks.SysclkFreq : ((rcc_clocks.Pclk2Freq == rcc_clocks.HclkFreq) ? rcc_clocks.Pclk2Freq : (rcc_clocks.Pclk2Freq * 2U));
    }
#endif /* GTIM8 */
#ifdef GTIM9
    else if (timer == GTIM9)
    {
        return (RCC->CFG2 & RCC_CFG2_GTIMCLKSEL) ? rcc_clocks.SysclkFreq : ((rcc_clocks.Pclk2Freq == rcc_clocks.HclkFreq) ? rcc_clocks.Pclk2Freq : (rcc_clocks.Pclk2Freq * 2U));
    }
#endif /* GTIM9 */
#ifdef GTIM10
    else if (timer == GTIM10)
    {
        return (RCC->CFG2 & RCC_CFG2_GTIMCLKSEL) ? rcc_clocks.SysclkFreq : ((rcc_clocks.Pclk2Freq == rcc_clocks.HclkFreq) ? rcc_clocks.Pclk2Freq : (rcc_clocks.Pclk2Freq * 2U));
    }
#endif /* GTIM10 */
    else
    {
        /* GTIM1-7 and BTIM use PCLK1, doubled when APB1 is prescaled. */
        return (rcc_clocks.Pclk1Freq == rcc_clocks.HclkFreq) ? rcc_clocks.Pclk1Freq : (rcc_clocks.Pclk1Freq * 2U);
    }

    return 0U;
}
#endif /* SOC_SERIES_N32H49x */

void n32_tim_enable_clock(TIM_Module *timer)
{
    RT_ASSERT(timer != RT_NULL);

#if defined(SOC_SERIES_N32H7xx)
    if (RT_FALSE)
        ;
#ifdef ATIM1
    else if (timer == ATIM1)
    {
        RCC_EnableAPB2PeriphClk1(RCC_APB2_PERIPHEN_M7_ATIM1 | RCC_APB2_PERIPHEN_M4_ATIM1 | RCC_APB2_PERIPHEN_M7_ATIM1LP | RCC_APB2_PERIPHEN_M4_ATIM1LP, ENABLE);
    }
#endif /* ATIM1 */
#ifdef ATIM2
    else if (timer == ATIM2)
    {
        RCC_EnableAPB2PeriphClk1(RCC_APB2_PERIPHEN_M7_ATIM2 | RCC_APB2_PERIPHEN_M4_ATIM2 | RCC_APB2_PERIPHEN_M7_ATIM2LP | RCC_APB2_PERIPHEN_M4_ATIM2LP, ENABLE);
    }
#endif /* ATIM2 */
#ifdef ATIM3
    else if (timer == ATIM3)
    {
        RCC_EnableAPB5PeriphClk1(RCC_APB5_PERIPHEN_M7_ATIM3 | RCC_APB5_PERIPHEN_M4_ATIM3 | RCC_APB5_PERIPHEN_M7_ATIM3LP | RCC_APB5_PERIPHEN_M4_ATIM3LP, ENABLE);
    }
#endif /* ATIM3 */
#ifdef ATIM4
    else if (timer == ATIM4)
    {
        RCC_EnableAPB5PeriphClk1(RCC_APB5_PERIPHEN_M7_ATIM4 | RCC_APB5_PERIPHEN_M4_ATIM4 | RCC_APB5_PERIPHEN_M7_ATIM4LP | RCC_APB5_PERIPHEN_M4_ATIM4LP, ENABLE);
    }
#endif /* ATIM4 */
#ifdef GTIMA1
    else if (timer == GTIMA1)
    {
        RCC_EnableAPB2PeriphClk1(RCC_APB2_PERIPHEN_M7_GTIMA1 | RCC_APB2_PERIPHEN_M4_GTIMA1 | RCC_APB2_PERIPHEN_M7_GTIMA1LP | RCC_APB2_PERIPHEN_M4_GTIMA1LP, ENABLE);
    }
#endif /* GTIMA1 */
#ifdef GTIMA2
    else if (timer == GTIMA2)
    {
        RCC_EnableAPB2PeriphClk1(RCC_APB2_PERIPHEN_M7_GTIMA2 | RCC_APB2_PERIPHEN_M4_GTIMA2 | RCC_APB2_PERIPHEN_M7_GTIMA2LP | RCC_APB2_PERIPHEN_M4_GTIMA2LP, ENABLE);
    }
#endif /* GTIMA2 */
#ifdef GTIMA3
    else if (timer == GTIMA3)
    {
        RCC_EnableAPB2PeriphClk1(RCC_APB2_PERIPHEN_M7_GTIMA3 | RCC_APB2_PERIPHEN_M4_GTIMA3 | RCC_APB2_PERIPHEN_M7_GTIMA3LP | RCC_APB2_PERIPHEN_M4_GTIMA3LP, ENABLE);
    }
#endif /* GTIMA3 */
#ifdef GTIMA4
    else if (timer == GTIMA4)
    {
        RCC_EnableAPB1PeriphClk1(RCC_APB1_PERIPHEN_M7_GTIMA4 | RCC_APB1_PERIPHEN_M4_GTIMA4 | RCC_APB1_PERIPHEN_M7_GTIMA4LP | RCC_APB1_PERIPHEN_M4_GTIMA4LP, ENABLE);
    }
#endif /* GTIMA4 */
#ifdef GTIMA5
    else if (timer == GTIMA5)
    {
        RCC_EnableAPB1PeriphClk2(RCC_APB1_PERIPHEN_M7_GTIMA5 | RCC_APB1_PERIPHEN_M4_GTIMA5 | RCC_APB1_PERIPHEN_M7_GTIMA5LP | RCC_APB1_PERIPHEN_M4_GTIMA5LP, ENABLE);
    }
#endif /* GTIMA5 */
#ifdef GTIMA6
    else if (timer == GTIMA6)
    {
        RCC_EnableAPB1PeriphClk2(RCC_APB1_PERIPHEN_M7_GTIMA6 | RCC_APB1_PERIPHEN_M4_GTIMA6 | RCC_APB1_PERIPHEN_M7_GTIMA6LP | RCC_APB1_PERIPHEN_M4_GTIMA6LP, ENABLE);
    }
#endif /* GTIMA6 */
#ifdef GTIMA7
    else if (timer == GTIMA7)
    {
        RCC_EnableAPB1PeriphClk2(RCC_APB1_PERIPHEN_M7_GTIMA7 | RCC_APB1_PERIPHEN_M4_GTIMA7 | RCC_APB1_PERIPHEN_M7_GTIMA7LP | RCC_APB1_PERIPHEN_M4_GTIMA7LP, ENABLE);
    }
#endif /* GTIMA7 */
#ifdef GTIMB1
    else if (timer == GTIMB1)
    {
        RCC_EnableAPB1PeriphClk1(RCC_APB1_PERIPHEN_M7_GTIMB1 | RCC_APB1_PERIPHEN_M4_GTIMB1 | RCC_APB1_PERIPHEN_M7_GTIMB1LP | RCC_APB1_PERIPHEN_M4_GTIMB1LP, ENABLE);
    }
#endif /* GTIMB1 */
#ifdef GTIMB2
    else if (timer == GTIMB2)
    {
        RCC_EnableAPB1PeriphClk1(RCC_APB1_PERIPHEN_M7_GTIMB2 | RCC_APB1_PERIPHEN_M4_GTIMB2 | RCC_APB1_PERIPHEN_M7_GTIMB2LP | RCC_APB1_PERIPHEN_M4_GTIMB2LP, ENABLE);
    }
#endif /* GTIMB2 */
#ifdef GTIMB3
    else if (timer == GTIMB3)
    {
        RCC_EnableAPB1PeriphClk1(RCC_APB1_PERIPHEN_M7_GTIMB3 | RCC_APB1_PERIPHEN_M4_GTIMB3 | RCC_APB1_PERIPHEN_M7_GTIMB3LP | RCC_APB1_PERIPHEN_M4_GTIMB3LP, ENABLE);
    }
#endif /* GTIMB3 */
#ifdef BTIM1
    else if (timer == BTIM1)
    {
        RCC_EnableAPB1PeriphClk1(RCC_APB1_PERIPHEN_M7_BTIM1 | RCC_APB1_PERIPHEN_M4_BTIM1 | RCC_APB1_PERIPHEN_M7_BTIM1LP | RCC_APB1_PERIPHEN_M4_BTIM1LP, ENABLE);
    }
#endif /* BTIM1 */
#ifdef BTIM2
    else if (timer == BTIM2)
    {
        RCC_EnableAPB1PeriphClk1(RCC_APB1_PERIPHEN_M7_BTIM2 | RCC_APB1_PERIPHEN_M4_BTIM2 | RCC_APB1_PERIPHEN_M7_BTIM2LP | RCC_APB1_PERIPHEN_M4_BTIM2LP, ENABLE);
    }
#endif /* BTIM2 */
#ifdef BTIM3
    else if (timer == BTIM3)
    {
        RCC_EnableAPB1PeriphClk1(RCC_APB1_PERIPHEN_M7_BTIM3 | RCC_APB1_PERIPHEN_M4_BTIM3 | RCC_APB1_PERIPHEN_M7_BTIM3LP | RCC_APB1_PERIPHEN_M4_BTIM3LP, ENABLE);
    }
#endif /* BTIM3 */
#ifdef BTIM4
    else if (timer == BTIM4)
    {
        RCC_EnableAPB1PeriphClk1(RCC_APB1_PERIPHEN_M7_BTIM4 | RCC_APB1_PERIPHEN_M4_BTIM4 | RCC_APB1_PERIPHEN_M7_BTIM4LP | RCC_APB1_PERIPHEN_M4_BTIM4LP, ENABLE);
    }
#endif /* BTIM4 */
    else
    {
        RT_ASSERT(RT_FALSE);
    }
#elif defined(SOC_SERIES_N32H47x_48x)
    if (RT_FALSE)
        ;
#ifdef ATIM1
    else if (timer == ATIM1)
    {
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_ATIM1, ENABLE);
    }
#endif /* ATIM1 */
#ifdef ATIM2
    else if (timer == ATIM2)
    {
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_ATIM2, ENABLE);
    }
#endif /* ATIM2 */
#ifdef ATIM3
    else if (timer == ATIM3)
    {
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_ATIM3, ENABLE);
    }
#endif /* ATIM3 */
#ifdef GTIM1
    else if (timer == GTIM1)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_GTIM1, ENABLE);
    }
#endif /* GTIM1 */
#ifdef GTIM2
    else if (timer == GTIM2)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_GTIM2, ENABLE);
    }
#endif /* GTIM2 */
#ifdef GTIM3
    else if (timer == GTIM3)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_GTIM3, ENABLE);
    }
#endif /* GTIM3 */
#ifdef GTIM4
    else if (timer == GTIM4)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_GTIM4, ENABLE);
    }
#endif /* GTIM4 */
#ifdef GTIM5
    else if (timer == GTIM5)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_GTIM5, ENABLE);
    }
#endif /* GTIM5 */
#ifdef GTIM6
    else if (timer == GTIM6)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_GTIM6, ENABLE);
    }
#endif /* GTIM6 */
#ifdef GTIM7
    else if (timer == GTIM7)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_GTIM7, ENABLE);
    }
#endif /* GTIM7 */
#ifdef GTIM8
    else if (timer == GTIM8)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GTIM8, ENABLE);
    }
#endif /* GTIM8 */
#ifdef GTIM9
    else if (timer == GTIM9)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GTIM9, ENABLE);
    }
#endif /* GTIM9 */
#ifdef GTIM10
    else if (timer == GTIM10)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GTIM10, ENABLE);
    }
#endif /* GTIM10 */
#ifdef BTIM1
    else if (timer == BTIM1)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_BTIM1, ENABLE);
    }
#endif /* BTIM1 */
#ifdef BTIM2
    else if (timer == BTIM2)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_BTIM2, ENABLE);
    }
#endif /* BTIM2 */
    else
    {
        RT_ASSERT(RT_FALSE);
    }
#elif defined(SOC_SERIES_N32H49x)
    if (RT_FALSE)
        ;
#ifdef ATIM1
    else if (timer == ATIM1)
    {
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_ATIM1, ENABLE);
    }
#endif /* ATIM1 */
#ifdef ATIM2
    else if (timer == ATIM2)
    {
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_ATIM2, ENABLE);
    }
#endif /* ATIM2 */
#ifdef ATIM3
    else if (timer == ATIM3)
    {
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_ATIM3, ENABLE);
    }
#endif /* ATIM3 */
#ifdef GTIM1
    else if (timer == GTIM1)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_GTIM1, ENABLE);
    }
#endif /* GTIM1 */
#ifdef GTIM2
    else if (timer == GTIM2)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_GTIM2, ENABLE);
    }
#endif /* GTIM2 */
#ifdef GTIM3
    else if (timer == GTIM3)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_GTIM3, ENABLE);
    }
#endif /* GTIM3 */
#ifdef GTIM4
    else if (timer == GTIM4)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_GTIM4, ENABLE);
    }
#endif /* GTIM4 */
#ifdef GTIM5
    else if (timer == GTIM5)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_GTIM5, ENABLE);
    }
#endif /* GTIM5 */
#ifdef GTIM6
    else if (timer == GTIM6)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_GTIM6, ENABLE);
    }
#endif /* GTIM6 */
#ifdef GTIM7
    else if (timer == GTIM7)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_GTIM7, ENABLE);
    }
#endif /* GTIM7 */
#ifdef GTIM8
    else if (timer == GTIM8)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_GTIM8, ENABLE);
    }
#endif /* GTIM8 */
#ifdef GTIM9
    else if (timer == GTIM9)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_GTIM9, ENABLE);
    }
#endif /* GTIM9 */
#ifdef GTIM10
    else if (timer == GTIM10)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_GTIM10, ENABLE);
    }
#endif /* GTIM10 */
#ifdef BTIM1
    else if (timer == BTIM1)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_BTIM1, ENABLE);
    }
#endif /* BTIM1 */
#ifdef BTIM2
    else if (timer == BTIM2)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_BTIM2, ENABLE);
    }
#endif /* BTIM2 */
    else
    {
        RT_ASSERT(RT_FALSE);
    }
#endif /* SOC_SERIES_N32H7xx */
}

#ifdef BSP_USING_CLOCK_TIMER

enum
{
#ifdef BSP_USING_ATIM1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_ATIM2
    TIM2_INDEX,
#endif
#ifdef BSP_USING_ATIM3
    TIM3_INDEX,
#endif
#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_ATIM4
    TIM4_INDEX,
#endif
#endif /* SOC_SERIES_N32H7xx */
#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_GTIMA1
    TIM5_INDEX,
#endif
#ifdef BSP_USING_GTIMA2
    TIM6_INDEX,
#endif
#ifdef BSP_USING_GTIMA3
    TIM7_INDEX,
#endif
#ifdef BSP_USING_GTIMA4
    TIM8_INDEX,
#endif
#ifdef BSP_USING_GTIMA5
    TIM9_INDEX,
#endif
#ifdef BSP_USING_GTIMA6
    TIM10_INDEX,
#endif
#ifdef BSP_USING_GTIMA7
    TIM11_INDEX,
#endif
#ifdef BSP_USING_GTIMB1
    TIM12_INDEX,
#endif
#ifdef BSP_USING_GTIMB2
    TIM13_INDEX,
#endif
#ifdef BSP_USING_GTIMB3
    TIM14_INDEX,
#endif
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
#ifdef BSP_USING_GTIM1
    TIM5_INDEX,
#endif
#ifdef BSP_USING_GTIM2
    TIM6_INDEX,
#endif
#ifdef BSP_USING_GTIM3
    TIM7_INDEX,
#endif
#ifdef BSP_USING_GTIM4
    TIM8_INDEX,
#endif
#ifdef BSP_USING_GTIM5
    TIM9_INDEX,
#endif
#ifdef BSP_USING_GTIM6
    TIM10_INDEX,
#endif
#ifdef BSP_USING_GTIM7
    TIM11_INDEX,
#endif
#ifdef BSP_USING_GTIM8
    TIM12_INDEX,
#endif
#ifdef BSP_USING_GTIM9
    TIM13_INDEX,
#endif
#ifdef BSP_USING_GTIM10
    TIM14_INDEX,
#endif
#endif /* SOC_SERIES_N32H7xx */
#ifdef BSP_USING_BTIM1
    TIM15_INDEX,
#endif
#ifdef BSP_USING_BTIM2
    TIM16_INDEX,
#endif
#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_BTIM3
    TIM17_INDEX,
#endif
#ifdef BSP_USING_BTIM4
    TIM18_INDEX,
#endif
#endif /* SOC_SERIES_N32H7xx */
};

struct n32_clock_timer
{
    rt_clock_timer_t time_device;
    TIM_Module *timer;
    IRQn_Type tim_irqn;
    char *name;
};

static struct n32_clock_timer n32_clock_timer_obj[] = {
#ifdef BSP_USING_ATIM1
    ATIM1_CONFIG,
#endif

#ifdef BSP_USING_ATIM2
    ATIM2_CONFIG,
#endif

#ifdef BSP_USING_ATIM3
    ATIM3_CONFIG,
#endif

#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_ATIM4
    ATIM4_CONFIG,
#endif
#endif /* SOC_SERIES_N32H7xx */

#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_GTIMA1
    GTIMA1_CONFIG,
#endif

#ifdef BSP_USING_GTIMA2
    GTIMA2_CONFIG,
#endif

#ifdef BSP_USING_GTIMA3
    GTIMA3_CONFIG,
#endif

#ifdef BSP_USING_GTIMA4
    GTIMA4_CONFIG,
#endif

#ifdef BSP_USING_GTIMA5
    GTIMA5_CONFIG,
#endif

#ifdef BSP_USING_GTIMA6
    GTIMA6_CONFIG,
#endif

#ifdef BSP_USING_GTIMA7
    GTIMA7_CONFIG,
#endif

#ifdef BSP_USING_GTIMB1
    GTIMB1_CONFIG,
#endif

#ifdef BSP_USING_GTIMB2
    GTIMB2_CONFIG,
#endif

#ifdef BSP_USING_GTIMB3
    GTIMB3_CONFIG,
#endif
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
#ifdef BSP_USING_GTIM1
    GTIM1_CONFIG,
#endif

#ifdef BSP_USING_GTIM2
    GTIM2_CONFIG,
#endif

#ifdef BSP_USING_GTIM3
    GTIM3_CONFIG,
#endif

#ifdef BSP_USING_GTIM4
    GTIM4_CONFIG,
#endif

#ifdef BSP_USING_GTIM5
    GTIM5_CONFIG,
#endif

#ifdef BSP_USING_GTIM6
    GTIM6_CONFIG,
#endif

#ifdef BSP_USING_GTIM7
    GTIM7_CONFIG,
#endif

#ifdef BSP_USING_GTIM8
    GTIM8_CONFIG,
#endif

#ifdef BSP_USING_GTIM9
    GTIM9_CONFIG,
#endif

#ifdef BSP_USING_GTIM10
    GTIM10_CONFIG,
#endif
#endif /* SOC_SERIES_N32H7xx */

#ifdef BSP_USING_BTIM1
    BTIM1_CONFIG,
#endif

#ifdef BSP_USING_BTIM2
    BTIM2_CONFIG,
#endif

#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_BTIM3
    BTIM3_CONFIG,
#endif

#ifdef BSP_USING_BTIM4
    BTIM4_CONFIG,
#endif
#endif /* SOC_SERIES_N32H7xx */
};

static void timer_init(struct rt_clock_timer_device *timer, rt_uint32_t state)
{
    uint32_t prescaler_value = 0;
#if defined(SOC_SERIES_N32H7xx)
    rt_uint32_t tim_div;
#endif
    struct n32_clock_timer *tim_device = RT_NULL;
#if defined(SOC_SERIES_N32H7xx)
    RCC_ClocksTypeDef RCC_Clocks;
#endif
    TIM_TimeBaseInitType TIM_TimeBaseStructure;

    RT_ASSERT(timer != RT_NULL);
    if (state)
    {
        tim_device = (struct n32_clock_timer *)timer;

        /* time init */
#if defined(SOC_SERIES_N32H7xx)
        n32_tim_ahbx_div_get(tim_device->timer, &tim_div);

        RCC_GetClocksFreqValue(&RCC_Clocks);

        if ((tim_device->timer == BTIM1) || (tim_device->timer == BTIM2) || (tim_device->timer == BTIM3) || (tim_device->timer == BTIM4))
        {
            prescaler_value = ((RCC_Clocks.AHB1ClkFreq / tim_div) / 10000U) - 1U;
        }
        else if ((tim_device->timer == ATIM1) || (tim_device->timer == ATIM2))
        {
            prescaler_value = ((RCC_Clocks.AHB2ClkFreq / tim_div) / 10000U) - 1U;
        }
        else if ((tim_device->timer == ATIM3) || (tim_device->timer == ATIM4))
        {
            prescaler_value = ((RCC_Clocks.AHB5ClkFreq / tim_div) / 10000U) - 1U;
        }
        else if ((tim_device->timer == GTIMA1) || (tim_device->timer == GTIMA2) || (tim_device->timer == GTIMA3))
        {
            prescaler_value = ((RCC_Clocks.AHB2ClkFreq / tim_div) / 10000U) - 1U;
        }
        else
        {
            prescaler_value = ((RCC_Clocks.AHB1ClkFreq / tim_div) / 10000U) - 1U;
        }
#endif
#if defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
        prescaler_value = (n32_tim_clock_freq_get(tim_device->timer) / 10000U) - 1U;
#endif /* SOC_SERIES_N32H47x_48x || SOC_SERIES_N32H49x */

        /* Enable tim clock */
        n32_tim_enable_clock(tim_device->timer);

        TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
        TIM_TimeBaseStructure.Period = 10000 - 1;
        TIM_TimeBaseStructure.Prescaler = prescaler_value;
        TIM_TimeBaseStructure.ClkDiv = TIM_CLK_DIV1;

        if (timer->info->cntmode == CLOCK_TIMER_CNTMODE_UP)
        {
            TIM_TimeBaseStructure.CounterMode = TIM_CNT_MODE_UP;
        }
        else
        {
            TIM_TimeBaseStructure.CounterMode = TIM_CNT_MODE_DOWN;
        }

        TIM_InitTimeBase(tim_device->timer, &TIM_TimeBaseStructure);

        /* set the TIMx priority */
        NVIC_SetPriority(tim_device->tim_irqn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 3, 0));
        /* enable the TIMx Interrupt */
        NVIC_EnableIRQ(tim_device->tim_irqn);

        TIM_ClearFlag(tim_device->timer, TIM_FLAG_UPDATE);
        LOG_D("%s init success", tim_device->name);
    }
}

static rt_err_t timer_start(rt_clock_timer_t *timer, rt_uint32_t t, rt_clock_timer_mode_t opmode)
{
    struct n32_clock_timer *tim_device = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim_device = (struct n32_clock_timer *)timer;

    /* set tim cnt */
    TIM_SetCnt(tim_device->timer, 0);
    /* set tim arr */
    TIM_SetAutoReload(tim_device->timer, t - 1U);

    if (opmode == CLOCK_TIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        TIM_SelectOnePulseMode(tim_device->timer, TIM_OPMODE_SINGLE);
    }
    else
    {
        TIM_SelectOnePulseMode(tim_device->timer, TIM_OPMODE_REPET);
    }

    TIM_ConfigInt(tim_device->timer, TIM_INT_UPDATE, ENABLE);
    TIM_Enable(tim_device->timer, ENABLE);

    return RT_EOK;
}

static void timer_stop(rt_clock_timer_t *timer)
{
    struct n32_clock_timer *tim_device = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim_device = (struct n32_clock_timer *)timer;

    /* disable interrupt */
    TIM_ConfigInt(tim_device->timer, TIM_INT_UPDATE, DISABLE);
    /* stop timer */
    TIM_Enable(tim_device->timer, DISABLE);

    /* set tim cnt */
    TIM_SetCnt(tim_device->timer, 0);
}

static rt_err_t timer_ctrl(rt_clock_timer_t *timer, rt_uint32_t cmd, void *arg)
{
    struct n32_clock_timer *tim_device = RT_NULL;
    rt_err_t result = -RT_ERROR;
    uint32_t prescaler_value = 0;
#if defined(SOC_SERIES_N32H7xx)
    rt_uint32_t tim_div;
    RCC_ClocksTypeDef RCC_Clocks;
#endif

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    tim_device = (struct n32_clock_timer *)timer;

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
    {
        rt_uint32_t freq;

        /* set timer frequence */
        freq = *((rt_uint32_t *)arg);

#if defined(SOC_SERIES_N32H7xx)
        if (freq == 0U)
        {
            result = -RT_EINVAL;
            break;
        }

        n32_tim_ahbx_div_get(tim_device->timer, &tim_div);

        RCC_GetClocksFreqValue(&RCC_Clocks);

        if ((tim_device->timer == BTIM1) || (tim_device->timer == BTIM2) || (tim_device->timer == BTIM3) || (tim_device->timer == BTIM4))
        {
            prescaler_value = ((RCC_Clocks.AHB1ClkFreq / tim_div) / freq) - 1U;
        }
        else if ((tim_device->timer == ATIM1) || (tim_device->timer == ATIM2))
        {
            prescaler_value = ((RCC_Clocks.AHB2ClkFreq / tim_div) / freq) - 1U;
        }
        else if ((tim_device->timer == ATIM3) || (tim_device->timer == ATIM4))
        {
            prescaler_value = ((RCC_Clocks.AHB5ClkFreq / tim_div) / freq) - 1U;
        }
        else if ((tim_device->timer == GTIMA1) || (tim_device->timer == GTIMA2) || (tim_device->timer == GTIMA3))
        {
            prescaler_value = ((RCC_Clocks.AHB2ClkFreq / tim_div) / freq) - 1U;
        }
        else
        {
            prescaler_value = ((RCC_Clocks.AHB1ClkFreq / tim_div) / freq) - 1U;
        }

        /* PSC is 16 bits wide; a larger value is silently truncated by
         * TIM_ConfigPrescaler() and the timer would then run at the wrong
         * frequency, so reject it here instead.
         */
        if (prescaler_value > 0xFFFFU)
        {
            result = -RT_EINVAL;
            break;
        }

        /* Update frequency value */
        TIM_ConfigPrescaler(tim_device->timer, prescaler_value, TIM_PSC_RELOAD_MODE_UPDATE);
#endif
#if defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
        if (freq == 0U)
        {
            result = -RT_EINVAL;
            break;
        }

        prescaler_value = (n32_tim_clock_freq_get(tim_device->timer) / freq) - 1U;

        /* PSC is 16 bits wide; a larger value is silently truncated by
         * TIM_ConfigPrescaler() and the timer would then run at the wrong
         * frequency, so reject it here instead.
         */
        if (prescaler_value > 0xFFFFU)
        {
            result = -RT_EINVAL;
            break;
        }

        /* Update frequency value.  The mode has to be IMMEDIATE: PSC is
         * buffered, and TIM_PSC_RELOAD_MODE_UPDATE is the mask 0, i.e. "send
         * no update event", so it leaves the counter on the old prescaler
         * until the next natural overflow.  IMMEDIATE sets EVTGEN.UDGN, which
         * is what actually latches the new value.
         */
        TIM_ConfigPrescaler(tim_device->timer, prescaler_value, TIM_PSC_RELOAD_MODE_IMMEDIATE);
#endif /* SOC_SERIES_N32H47x_48x || SOC_SERIES_N32H49x */
        result = RT_EOK;
    }
    break;
    default:
    {
        result = -RT_EINVAL;
    }
    break;
    }

    return result;
}

static rt_uint32_t timer_counter_get(rt_clock_timer_t *timer)
{
    struct n32_clock_timer *tim_device = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim_device = (struct n32_clock_timer *)timer;

    return TIM_GetCnt(tim_device->timer);
}

static const struct rt_clock_timer_info _info = TIM_DEV_INFO_CONFIG;
#if defined(SOC_SERIES_N32H49x)
static const struct rt_clock_timer_info _info_32bit = TIM_32BIT_DEV_INFO_CONFIG;
#endif /* SOC_SERIES_N32H49x */

static const struct rt_clock_timer_ops _ops = {
    .init = timer_init,
    .start = timer_start,
    .stop = timer_stop,
    .count_get = timer_counter_get,
    .control = timer_ctrl,
};

#ifdef BSP_USING_ATIM1
void ATIM1_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM1_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM1_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_ATIM1 */

#ifdef BSP_USING_ATIM2
void ATIM2_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM2_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM2_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_ATIM2 */

#ifdef BSP_USING_ATIM3
void ATIM3_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM3_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM3_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_ATIM3 */

#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_ATIM4
void ATIM4_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM4_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM4_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_ATIM4 */
#endif /* SOC_SERIES_N32H7xx */

#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_GTIMA1
void GTIMA1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM5_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM5_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIMA1 */

#ifdef BSP_USING_GTIMA2
void GTIMA2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM6_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM6_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIMA2 */

#ifdef BSP_USING_GTIMA3
void GTIMA3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM7_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM7_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIMA3 */

#ifdef BSP_USING_GTIMA4
void GTIMA4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM8_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM8_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIMA4 */

#ifdef BSP_USING_GTIMA5
void GTIMA5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM9_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM9_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIMA5 */

#ifdef BSP_USING_GTIMA6
void GTIMA6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM10_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM10_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIMA6 */

#ifdef BSP_USING_GTIMA7
void GTIMA7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM11_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM11_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIMA7 */

#ifdef BSP_USING_GTIMB1
void GTIMB1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM12_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM12_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIMB1 */

#ifdef BSP_USING_GTIMB2
void GTIMB2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM13_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM13_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIMB2 */

#ifdef BSP_USING_GTIMB3
void GTIMB3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM14_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM14_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIMB3 */
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
#ifdef BSP_USING_GTIM1
void GTIM1_IRQHandler(void)
{
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM5_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM5_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIM1 */

#ifdef BSP_USING_GTIM2
void GTIM2_IRQHandler(void)
{
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM6_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM6_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIM2 */

#ifdef BSP_USING_GTIM3
void GTIM3_IRQHandler(void)
{
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM7_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM7_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIM3 */

#ifdef BSP_USING_GTIM4
void GTIM4_IRQHandler(void)
{
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM8_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM8_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIM4 */

#ifdef BSP_USING_GTIM5
void GTIM5_IRQHandler(void)
{
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM9_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM9_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIM5 */

#ifdef BSP_USING_GTIM6
void GTIM6_IRQHandler(void)
{
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM10_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM10_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIM6 */

#ifdef BSP_USING_GTIM7
void GTIM7_IRQHandler(void)
{
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM11_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM11_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIM7 */

#ifdef BSP_USING_GTIM8
void GTIM8_IRQHandler(void)
{
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM12_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM12_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIM8 */

#ifdef BSP_USING_GTIM9
void GTIM9_IRQHandler(void)
{
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM13_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM13_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIM9 */

#ifdef BSP_USING_GTIM10
void GTIM10_IRQHandler(void)
{
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM14_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM14_INDEX].time_device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_GTIM10 */
#endif /* SOC_SERIES_N32H7xx */

#ifdef BSP_USING_BTIM1
void BTIM1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM15_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM15_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_BTIM1 */

#ifdef BSP_USING_BTIM2
void BTIM2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM16_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM16_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_BTIM2 */

#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_BTIM3
void BTIM3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM17_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM17_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_BTIM3 */

#ifdef BSP_USING_BTIM4
void BTIM4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    TIM_ClrIntPendingBit(n32_clock_timer_obj[TIM18_INDEX].timer, TIM_INT_UPDATE);
    rt_clock_timer_isr(&n32_clock_timer_obj[TIM18_INDEX].time_device);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_BTIM4 */
#endif /* SOC_SERIES_N32H7xx */

static int n32_clock_timer_init(void)
{
    rt_uint32_t i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(n32_clock_timer_obj) / sizeof(n32_clock_timer_obj[0]); i++)
    {
#if defined(SOC_SERIES_N32H49x)
        if (IS_GTIM1_4_DEVICE(n32_clock_timer_obj[i].timer))
        {
            n32_clock_timer_obj[i].time_device.info = &_info_32bit;
        }
        else
#endif /* SOC_SERIES_N32H49x */
        {
            n32_clock_timer_obj[i].time_device.info = &_info;
        }
        n32_clock_timer_obj[i].time_device.ops = &_ops;
        if (rt_clock_timer_register(&n32_clock_timer_obj[i].time_device,
                                    n32_clock_timer_obj[i].name, RT_NULL) == RT_EOK)
        {
            LOG_D("%s register success", n32_clock_timer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", n32_clock_timer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(n32_clock_timer_init);

#endif /* BSP_USING_CLOCK_TIMER */
