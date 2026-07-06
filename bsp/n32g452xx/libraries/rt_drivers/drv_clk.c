/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     breo.com     first version
 */

#include "drv_clk.h"
#include "board.h"

void DumpClock(const char *msg)
{
    RCC_ClocksType RCC_ClockFreq;
    rt_kprintf("--------------------------------\n");
    rt_kprintf("%s:\n", msg);
    RCC_GetClocksFreqValue(&RCC_ClockFreq);
    rt_kprintf("SYSCLK: %d\n", RCC_ClockFreq.SysclkFreq);
    rt_kprintf("HCLK: %d\n", RCC_ClockFreq.HclkFreq);
    rt_kprintf("PCLK1: %d\n", RCC_ClockFreq.Pclk1Freq);
    rt_kprintf("PCLK2: %d\n", RCC_ClockFreq.Pclk2Freq);
}

void SetSysClockToHSI(void)
{
    RCC_DeInit();

    RCC_EnableHsi(ENABLE);

    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);

    /* Flash 0 wait state */
    FLASH_SetLatency(FLASH_LATENCY_0);

    /* HCLK = SYSCLK */
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);

    /* PCLK2 = HCLK */
    RCC_ConfigPclk2(RCC_HCLK_DIV1);

    /* PCLK1 = HCLK */
    RCC_ConfigPclk1(RCC_HCLK_DIV1);

    /* Select HSE as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_HSI);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSysclkSrc() != 0x00)
    {
    }
}

/**
 * @brief  Selects HSE as System clock source and configure HCLK, PCLK2
 *         and PCLK1 prescalers.
 */
void SetSysClockToHSE(void)
{
    ErrorStatus HSEStartUpStatus;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration
     * -----------------------------*/
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    /* Enable HSE */
    RCC_ConfigHse(RCC_HSE_ENABLE);

    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitHseStable();

    if (HSEStartUpStatus == SUCCESS)
    {
        /* Enable Prefetch Buffer */
        FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);

        if (HSE_Value <= 32000000)
        {
            /* Flash 0 wait state */
            FLASH_SetLatency(FLASH_LATENCY_0);
        }
        else
        {
            /* Flash 1 wait state */
            FLASH_SetLatency(FLASH_LATENCY_1);
        }

        /* HCLK = SYSCLK */
        RCC_ConfigHclk(RCC_SYSCLK_DIV1);

        /* PCLK2 = HCLK */
        RCC_ConfigPclk2(RCC_HCLK_DIV1);

        /* PCLK1 = HCLK */
        RCC_ConfigPclk1(RCC_HCLK_DIV1);

        /* Select HSE as system clock source */
        RCC_ConfigSysclk(RCC_SYSCLK_SRC_HSE);

        /* Wait till HSE is used as system clock source */
        while (RCC_GetSysclkSrc() != 0x04)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
           configuration. User can add here some code to deal with this error */

        /* Go to infinite loop */
        while (1)
        {
        }
    }
}

void SetSysClockToPLL(uint32_t freq, uint8_t src)
{
    uint32_t pllsrc = (src == SYSCLK_PLLSRC_HSI ? RCC_PLL_SRC_HSI_DIV2 : RCC_PLL_SRC_HSE_DIV2);
    uint32_t pllmul;
    uint32_t latency;
    uint32_t pclk1div, pclk2div;
    ErrorStatus HSEStartUpStatus;

    if (HSE_VALUE != 8000000)
    {
        /* HSE_VALUE == 8000000 is needed in this project! */
        while (1)
            ;
    }

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration
     * -----------------------------*/
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    if (src == SYSCLK_PLLSRC_HSE)
    {
        /* Enable HSE */
        RCC_ConfigHse(RCC_HSE_ENABLE);

        /* Wait till HSE is ready */
        HSEStartUpStatus = RCC_WaitHseStable();

        if (HSEStartUpStatus != SUCCESS)
        {
            /* If HSE fails to start-up, the application will have wrong clock
               configuration. User can add here some code to deal with this
               error */

            /* Go to infinite loop */
            while (1)
                ;
        }
    }

    switch (freq)
    {
    case 24000000:
        latency  = FLASH_LATENCY_0;
        pllmul   = RCC_PLL_MUL_6;
        pclk1div = RCC_HCLK_DIV1;
        pclk2div = RCC_HCLK_DIV1;
        break;
    case 36000000:
        latency  = FLASH_LATENCY_1;
        pllmul   = RCC_PLL_MUL_9;
        pclk1div = RCC_HCLK_DIV1;
        pclk2div = RCC_HCLK_DIV1;
        break;
    case 48000000:
        latency  = FLASH_LATENCY_1;
        pllmul   = RCC_PLL_MUL_12;
        pclk1div = RCC_HCLK_DIV2;
        pclk2div = RCC_HCLK_DIV1;
        break;
    case 56000000:
        latency  = FLASH_LATENCY_1;
        pllmul   = RCC_PLL_MUL_14;
        pclk1div = RCC_HCLK_DIV2;
        pclk2div = RCC_HCLK_DIV1;
        break;
    case 72000000:
        latency  = FLASH_LATENCY_2;
        pllmul   = RCC_PLL_MUL_18;
        pclk1div = RCC_HCLK_DIV2;
        pclk2div = RCC_HCLK_DIV1;
        break;
    case 96000000:
        latency  = FLASH_LATENCY_2;
        pllmul   = RCC_PLL_MUL_24;
        pclk1div = RCC_HCLK_DIV4;
        pclk2div = RCC_HCLK_DIV2;
        break;
    case 128000000:
        latency  = FLASH_LATENCY_3;
        pllmul   = RCC_PLL_MUL_32;
        pclk1div = RCC_HCLK_DIV4;
        pclk2div = RCC_HCLK_DIV2;
        break;
    case 144000000:
        /* must use HSE as PLL source */
        latency  = FLASH_LATENCY_4;
        pllsrc   = RCC_PLL_SRC_HSE_DIV1;
        pllmul   = RCC_PLL_MUL_18;
        pclk1div = RCC_HCLK_DIV4;
        pclk2div = RCC_HCLK_DIV2;
        break;
    default:
        while (1)
            ;
    }

    FLASH_SetLatency(latency);

    /* HCLK = SYSCLK */
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);

    /* PCLK2 = HCLK */
    RCC_ConfigPclk2(pclk2div);

    /* PCLK1 = HCLK */
    RCC_ConfigPclk1(pclk1div);

    RCC_ConfigPll(pllsrc, pllmul);

    /* Enable PLL */
    RCC_EnablePll(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRD) == RESET)
        ;

    /* Select PLL as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSysclkSrc() != 0x08)
        ;
}

