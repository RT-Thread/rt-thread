/**
  ****************************************************************************************************
  * @file    fm33lc0xx_fl_rcc.c
  * @author  FMSH Application Team
  * @brief   Src file of RCC FL Module
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  ****************************************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "fm33lc0xx_fl.h"

/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

#ifdef FL_RCC_DRIVER_ENABLED

/** @addtogroup RCC_FL_EF_Operation
  * @{
  */

/**
  * @brief  获取USB提供给系统总线时钟的频率
  *
  * @retval USB提供给SYSCLK的时钟频率(Hz)
  */
uint32_t FL_RCC_GetUSBClockFreqToSysclk(void)
{
    if(FL_RCC_GetUSBClockOutput() == FL_RCC_USB_CLK_OUT_48M)
    {
        return 48000000;
    }
    else
    {
        return 60000000;
    }
}

/**
  * @brief  获取系统当前工作时钟SYSCLK
  *
  * @note   函数中用到了 @ref XTHF_VALUE 宏，这个宏应该被定义为外部晶振的输入频率值
  *
  * @retval 系统时钟频率(Hz)
  *
  */
uint32_t FL_RCC_GetSystemClockFreq(void)
{
    uint32_t frequency = 0;
    /* 获取系统时钟源 */
    switch(FL_RCC_GetSystemClockSource())
    {
        /* 系统时钟源为内部RCHF */
        case FL_RCC_SYSTEM_CLK_SOURCE_RCHF:
            /* 内部RCHF默认为8MHz ,可以配置为16或24M */
            frequency = FL_RCC_GetRCHFClockFreq();
            break;
        /* 系统时钟源为XTHF */
        case FL_RCC_SYSTEM_CLK_SOURCE_XTHF:
            frequency = XTHFClock;
            break;
        /* 系统时钟源为PLL */
        case FL_RCC_SYSTEM_CLK_SOURCE_PLL:
            frequency = FL_RCC_GetPLLClockFreq();
            break;
        /* 系统时钟源为内部RCMF */
        case FL_RCC_SYSTEM_CLK_SOURCE_RCMF_PSC:
            /* 根据RCMF的分频配置得出系统时钟 */
            frequency = FL_RCC_GetRCMFClockFreq();
            break;
        /* 系统时钟源为LSCLK */
        case FL_RCC_SYSTEM_CLK_SOURCE_LSCLK:
            #ifdef USE_LSCLK_CLOCK_SRC_LPOSC
            frequency = 32000;
            #else
            frequency = XTLFClock;
            #endif
            break;
        /* 系统时钟源为USB BCK */
        case FL_RCC_SYSTEM_CLK_SOURCE_USBCLK:
            /* USB时钟频率获取 */
            frequency = FL_RCC_GetUSBClockFreqToSysclk();
            break;
        /* 系统时钟源为LPOSC */
        case FL_RCC_SYSTEM_CLK_SOURCE_LPOSC:
            frequency = 32000;
            break;
        default:
            frequency = FL_RCC_GetRCHFClockFreq();
            break;
    }
    return frequency;
}
/**
  * @brief  获取AHB总线时钟频率
  *
  * @retval AHB总线时钟频率(Hz)
  *
  */
uint32_t FL_RCC_GetAHBClockFreq(void)
{
    uint32_t frequency = 0;
    /* 获取AHB分频系数，AHB源自系统主时钟 */
    switch(FL_RCC_GetAHBPrescaler())
    {
        case FL_RCC_AHBCLK_PSC_DIV1:
            frequency = FL_RCC_GetSystemClockFreq();
            break;
        case FL_RCC_AHBCLK_PSC_DIV2:
            frequency = FL_RCC_GetSystemClockFreq() / 2;
            break;
        case FL_RCC_AHBCLK_PSC_DIV4:
            frequency = FL_RCC_GetSystemClockFreq() / 4;
            break;
        case FL_RCC_AHBCLK_PSC_DIV8:
            frequency = FL_RCC_GetSystemClockFreq() / 8;
            break;
        case FL_RCC_AHBCLK_PSC_DIV16:
            frequency = FL_RCC_GetSystemClockFreq() / 16;
            break;
        default:
            frequency = FL_RCC_GetSystemClockFreq();
            break;
    }
    return frequency;
}

/**
  * @brief  获取当前系统的APB1总线时钟
  *
  * @retval APB1总线时钟频率(Hz)
  *
  */
uint32_t FL_RCC_GetAPB1ClockFreq(void)
{
    uint32_t frequency = 0;
    /* 获取APB1分频系数，APB源自AHB */
    switch(FL_RCC_GetAPB1Prescaler())
    {
        case FL_RCC_APB1CLK_PSC_DIV1:
            frequency = FL_RCC_GetAHBClockFreq();
            break;
        case FL_RCC_APB1CLK_PSC_DIV2:
            frequency = FL_RCC_GetAHBClockFreq() / 2;
            break;
        case FL_RCC_APB1CLK_PSC_DIV4:
            frequency = FL_RCC_GetAHBClockFreq() / 4;
            break;
        case FL_RCC_APB1CLK_PSC_DIV8:
            frequency = FL_RCC_GetAHBClockFreq() / 8;
            break;
        case FL_RCC_APB1CLK_PSC_DIV16:
            frequency = FL_RCC_GetAHBClockFreq() / 16;
            break;
        default:
            frequency = FL_RCC_GetAHBClockFreq();
            break;
    }
    return frequency;
}
/**
  * @brief  获取当前系统的APB2总线时钟
  *
  * @retval APB2总线时钟频率(Hz)
  *
  */
uint32_t FL_RCC_GetAPB2ClockFreq(void)
{
    uint32_t frequency = 0;
    /* 获取APB2分频系数，APB源自AHB */
    switch(FL_RCC_GetAPB2Prescaler())
    {
        case FL_RCC_APB2CLK_PSC_DIV1:
            frequency = FL_RCC_GetAHBClockFreq();
            break;
        case FL_RCC_APB2CLK_PSC_DIV2:
            frequency = FL_RCC_GetAHBClockFreq() / 2;
            break;
        case FL_RCC_APB2CLK_PSC_DIV4:
            frequency = FL_RCC_GetAHBClockFreq() / 4;
            break;
        case FL_RCC_APB2CLK_PSC_DIV8:
            frequency = FL_RCC_GetAHBClockFreq() / 8;
            break;
        case FL_RCC_APB2CLK_PSC_DIV16:
            frequency = FL_RCC_GetAHBClockFreq() / 16;
            break;
        default:
            frequency = FL_RCC_GetAHBClockFreq();
            break;
    }
    return frequency;
}
/**
  * @brief  获取RCMF输出时钟频率
  *
  * @retval RCMF输出时钟频率(Hz)
  *
  */
uint32_t FL_RCC_GetRCMFClockFreq(void)
{
    uint32_t frequency = 0;
    switch(FL_RCC_RCMF_GetPrescaler())
    {
        case FL_RCC_RCMF_PSC_DIV1:
            frequency = 4000000;
            break;
        case FL_RCC_RCMF_PSC_DIV4:
            frequency = 1000000;
            break;
        case FL_RCC_RCMF_PSC_DIV8:
            frequency = 500000;
            break;
        case FL_RCC_RCMF_PSC_DIV16:
            frequency = 250000;
            break;
        default:
            frequency = 4000000;
            break;
    }
    return frequency;
}
/**
  * @brief  获取RCHF输出时钟频率
  *
  * @retval 返回RCHF输出时钟频率(Hz)
  *
  */
uint32_t FL_RCC_GetRCHFClockFreq(void)
{
    uint32_t frequency = 0;
    switch(FL_RCC_RCHF_GetFrequency())
    {
        case FL_RCC_RCHF_FREQUENCY_8MHZ:
            frequency = 8000000;
            break;
        case FL_RCC_RCHF_FREQUENCY_16MHZ:
            frequency = 16000000;
            break;
        case FL_RCC_RCHF_FREQUENCY_24MHZ:
            frequency = 24000000;
            break;
        default:
            frequency = 8000000;
            break;
    }
    return frequency;
}
/**
  * @brief  获取PLL输出时钟频率
  *
  * @retval 返回PLL输出时钟频率(Hz)
  *
  */
uint32_t FL_RCC_GetPLLClockFreq(void)
{
    uint32_t frequency = 0;
    uint32_t multiplier = 0;
    /* 获取PLL时钟源 */
    switch(FL_RCC_PLL_GetClockSource())
    {
        case FL_RCC_PLL_CLK_SOURCE_RCHF:
            /* 获取RCHF配置主频 */
            frequency = FL_RCC_GetRCHFClockFreq();
            break;
        case FL_RCC_PLL_CLK_SOURCE_XTHF:
            frequency = XTHFClock;
            break;
        default:
            frequency = FL_RCC_GetRCHFClockFreq();
            break;
    }
    /* 获取PLL时钟分频系数 */
    switch(FL_RCC_PLL_GetPrescaler())
    {
        case FL_RCC_PLL_PSC_DIV1:
            break;
        case FL_RCC_PLL_PSC_DIV2:
            frequency /= 2;
            break;
        case FL_RCC_PLL_PSC_DIV4:
            frequency /= 4;
            break;
        case FL_RCC_PLL_PSC_DIV8:
            frequency /= 8;
            break;
        case FL_RCC_PLL_PSC_DIV12:
            frequency /= 12;
            break;
        case FL_RCC_PLL_PSC_DIV16:
            frequency /= 16;
            break;
        case FL_RCC_PLL_PSC_DIV24:
            frequency /= 24;
            break;
        case FL_RCC_PLL_PSC_DIV32:
            frequency /= 32;
            break;
        default:
            break;
    }
    multiplier = FL_RCC_PLL_ReadMultiplier() + 1;
    frequency *= multiplier;
    return frequency;
}

/**
  * @}
  */

#endif /* FL_RCC_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
