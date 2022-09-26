/*
 * Copyright (c) 2020-2022, CQ 100ask Development Team
 *
 * Change Logs:
 *   Date           Author          Notes
 * 2022-05-29        Alen       first version
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
    /* 使能总线外设时钟 */
    RCC->AHB1ENR |= (1u << 13u);    // 使能FLASH外设
    FLASH->ACR |= (4<<0);           // 设置Flash的等待周期

    /* 使能PWR/DBG */
    RCC->APB1ENR |= (1<<28);
    PWR->CR1 &= ~(2<<14);
    PWR->CR1 |= (2<<14);    // 如果系统时钟需要达到最大频率 120MHz，需要将 VOS 设置为 2’b10 即 1.7V

    RCC->CR &= ~((1<<16) | (1<<24) ); // 关闭HSE/PLL

    /* 配置HSE和PLL */
    RCC->CR |= (1<<16);             // 使能HSE
    while(0 == ((RCC->CR)&(1<<17)));// 等待HSE稳定

    RCC->PLLCFGR |= (1<<0);         // 配置PLL的时钟源HSE
    RCC->PLLCFGR &= ~(1<<1);        // 配置PLL的时钟源HSE不分频后再作为时钟输入源
    RCC->PLLCFGR &= ~(0x7F<<16);
    RCC->PLLCFGR |= (19<<16);       // 配置PLL的倍频系数:20倍 -> 12MHz/2*20 = 120MHz
    RCC->PLLCFGR &= ~(0x7<<8);
    RCC->PLLCFGR |= (1<<8);         // 配置PLL的分频系数:2

    RCC->CR |= (1<<24);             // 使能PLL
    while(0 == (RCC->CR & (1<<25)));// 等待PLL时钟稳定

    /* 配置系统时钟、AHB、APB时钟 */
    RCC->CFGR |= (0<<4);            // AHB不分频
    RCC->CFGR |= (4<<8);            // APB1 2分频
    RCC->CFGR |= (4<<11);           // APB2 2分频
    RCC->CFGR |= (2<<22);           // PLL输出时钟3分频后输出给USB：120MHz/3=40MHz
    RCC->CFGR |= (7<<24);           // PLL输出时钟2分频后输出到MCO
    RCC->CFGR |= (2<<0);            // 选择PLL输出用作系统时钟
    while(0 == (RCC->CFGR & (2<<2)));   // 等待PLL输出用作系统时钟稳定

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
    /* 获取系统时钟源 */
    switch(tmpreg & RCC_CFGR_SWS_MASK)
    {
        case RCC_SYSCLKSOURCE_STATUS_HSI:
        {
            sysclockfreq = HSI_VALUE;
            break;
        }
        case RCC_SYSCLKSOURCE_STATUS_HSE:
        {
            sysclockfreq = HSE_VALUE;
            break;
        }
        case RCC_SYSCLKSOURCE_STATUS_LSI:
        {
            sysclockfreq = LSI_VALUE;
            break;
        }
        case RCC_SYSCLKSOURCE_STATUS_PLLCLK:
        {
            /* 获取PLL的输入时钟源 */
            if(RCC->PLLCFGR&0x01)       // HSE用作PLL的输入时钟
            {
                if(RCC->PLLCFGR&0x02)   // HSE二分频后输入给PLL
                {
                    pllclk = HSE_VALUE>>1;
                }
                else                    // HSE部分变频直接输出给PLL
                {
                    pllclk = HSE_VALUE;
                }
            }
            else    // HSI用作PLL的输入时钟
            {
                pllclk = HSI_VALUE;
            }
            prediv = (RCC->PLLCFGR>>8)&0x07;    // PLL的分频系数：PLLCFGR[10:8]
            pllmul = (RCC->PLLCFGR>>16)&0x7F;   // PLL的倍频系数: PLLCFGR[22:16]
            sysclockfreq = pllclk * (pllmul+1) / (prediv+1);

            break;
        }
        default:break;
    }

    SystemClockFreq = sysclockfreq;
}

static void update_ahb_clock(void)
{
    uint32_t tmpreg = RCC->CFGR;
    uint8_t hpre = (tmpreg>>4)&0x0F;
    if((hpre&0x08) == 0)   // 不分频
        AHBClockFreq = SystemClockFreq;
    else
    {
        hpre = (hpre&0x07) + 1;
        AHBClockFreq = SystemClockFreq>>hpre;
    }
}

static void update_apb1_clock(void)
{
    uint32_t tmpreg = RCC->CFGR;
    uint8_t ppre1 = (tmpreg>>8)&0x0F;
    if((ppre1&0x04) == 0)   // 不分频
        APB1ClockFreq = AHBClockFreq;
    else
    {
        ppre1 = (ppre1&0x03) + 1;
        APB1ClockFreq = AHBClockFreq>>ppre1;
    }
}

static void update_apb2_clock(void)
{
    uint32_t tmpreg = RCC->CFGR;
    uint8_t ppre2 = (tmpreg>>11)&0x0F;
    if((ppre2&0x04) == 0)   // 不分频
        APB2ClockFreq = AHBClockFreq;
    else
    {
        ppre2 = (ppre2&0x03) + 1;
        APB2ClockFreq = AHBClockFreq>>ppre2;
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

