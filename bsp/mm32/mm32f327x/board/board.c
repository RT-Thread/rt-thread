/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-05     mazhiyuan   first version
 */

#include "board.h"
#include "hal_rcc.h"

static uint32_t SystemClockFreq = HSI_VALUE;
static uint32_t AHBClockFreq = HSI_VALUE;
static uint32_t APB1ClockFreq = HSI_VALUE;
static uint32_t APB2ClockFreq = HSI_VALUE;

static void update_systemclock(void);
static void update_ahb_clock(void);
static void update_apb1_clock(void);
static void update_apb2_clock(void);

void SystemClock_Config(void)
{
    RCC->AHB1ENR |= RCC_AHB1_PERIPH_FLASH;
    FLASH->ACR |= (4 << 0);

    RCC->APB1ENR |= RCC_APB1_PERIPH_PWR;
    PWR->CR1 &= ~(2 << 14);
    PWR->CR1 |= (2 << 14);

    RCC->CR &= ~((1 << 16) | (1 << 24));

    RCC->CR |= (1 << 16);
    while (0 == (RCC->CR & (1 << 17)))
    {
    }

    RCC->PLLCFGR |= (1 << 0);
    RCC->PLLCFGR &= ~(1 << 1);
    RCC->PLLCFGR &= ~(0x7F << 16);
    RCC->PLLCFGR |= (19 << 16);
    RCC->PLLCFGR &= ~(0x7 << 8);
    RCC->PLLCFGR |= (1 << 8);

    RCC->CR |= (1 << 24);
    while (0 == (RCC->CR & (1 << 25)))
    {
    }

    RCC->CFGR |= (0 << 4);
    RCC->CFGR |= (4 << 8);
    RCC->CFGR |= (4 << 11);
    RCC->CFGR |= (2 << 22);
    RCC->CFGR |= (7 << 24);
    RCC->CFGR |= (2 << 0);
    while (0 == (RCC->CFGR & (2 << 2)))
    {
    }

    update_systemclock();
    update_ahb_clock();
    update_apb1_clock();
    update_apb2_clock();
}

static void update_systemclock(void)
{
    uint32_t tmpreg = 0U, prediv = 0U, pllclk = 0U, pllmul = 0U;
    uint32_t sysclockfreq = HSI_VALUE;

    tmpreg = RCC->CFGR;
    switch (tmpreg & RCC_CFGR_SWS_Msk)
    {
    case RCC_SYSCLKSOURCE_STATUS_HSI:
        sysclockfreq = HSI_VALUE;
        break;
    case RCC_SYSCLKSOURCE_STATUS_HSE:
        sysclockfreq = HSE_VALUE;
        break;
    case RCC_SYSCLKSOURCE_STATUS_LSI:
        sysclockfreq = LSI_VALUE;
        break;
    case RCC_SYSCLKSOURCE_STATUS_PLLCLK:
        if (RCC->PLLCFGR & 0x01)
        {
            if (RCC->PLLCFGR & 0x02)
            {
                pllclk = HSE_VALUE >> 1;
            }
            else
            {
                pllclk = HSE_VALUE;
            }
        }
        else
        {
            pllclk = HSI_VALUE;
        }
        prediv = (RCC->PLLCFGR >> 8) & 0x07;
        pllmul = (RCC->PLLCFGR >> 16) & 0x7F;
        sysclockfreq = pllclk * (pllmul + 1) / (prediv + 1);
        break;
    default:
        break;
    }

    SystemClockFreq = sysclockfreq;
}

static void update_ahb_clock(void)
{
    uint32_t tmpreg = RCC->CFGR;
    uint8_t hpre = (tmpreg >> 4) & 0x0F;

    if ((hpre & 0x08) == 0)
    {
        AHBClockFreq = SystemClockFreq;
    }
    else
    {
        hpre = (hpre & 0x07) + 1;
        AHBClockFreq = SystemClockFreq >> hpre;
    }
}

static void update_apb1_clock(void)
{
    uint32_t tmpreg = RCC->CFGR;
    uint8_t ppre1 = (tmpreg >> 8) & 0x0F;

    if ((ppre1 & 0x04) == 0)
    {
        APB1ClockFreq = AHBClockFreq;
    }
    else
    {
        ppre1 = (ppre1 & 0x03) + 1;
        APB1ClockFreq = AHBClockFreq >> ppre1;
    }
}

static void update_apb2_clock(void)
{
    uint32_t tmpreg = RCC->CFGR;
    uint8_t ppre2 = (tmpreg >> 11) & 0x0F;

    if ((ppre2 & 0x04) == 0)
    {
        APB2ClockFreq = AHBClockFreq;
    }
    else
    {
        ppre2 = (ppre2 & 0x03) + 1;
        APB2ClockFreq = AHBClockFreq >> ppre2;
    }
}

uint32_t HAL_GetSysClockFreq(void)
{
    return SystemClockFreq;
}

uint32_t HAL_Get_AHB_Clock(void)
{
    return AHBClockFreq;
}

uint32_t HAL_Get_APB1_Clock(void)
{
    return APB1ClockFreq;
}

uint32_t HAL_Get_APB2_Clock(void)
{
    return APB2ClockFreq;
}
