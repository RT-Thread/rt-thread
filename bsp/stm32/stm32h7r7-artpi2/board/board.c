/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-10     RealThread   first version
 */

#include "board.h"

#define DBG_TAG "board"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    //Notice: system main clock is set in user boot stage.
    //you can modify it but be aware on XPI1 and XPI2 status.
    return;
}

int clock_information(void)
{
    LOG_I("System Clock information");
    LOG_I("SYSCLK_Frequency = %d", HAL_RCC_GetSysClockFreq());
    LOG_I("HCLK_Frequency   = %d", HAL_RCC_GetHCLKFreq());
    LOG_I("PCLK1_Frequency  = %d", HAL_RCC_GetPCLK1Freq());
    LOG_I("PCLK2_Frequency  = %d", HAL_RCC_GetPCLK2Freq());
    LOG_I("XSPI1_Frequency  = %d", HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI1));
    LOG_I("XSPI2_Frequency  = %d", HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI2));
    return RT_EOK;
}
INIT_BOARD_EXPORT(clock_information);
