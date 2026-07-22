/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-04-03     ox-horse         first version
 */

#include "board.h"

/**
  * @brief  System_Initialize
  * @param  None
  * @retval None
  */
void System_Initialize(void)
{
    /* Initialize system clock and enable Peripheral clock */
    RCC_Configuration();

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Config Peripheral GPIO */
    GPIO_Configuration();
}
