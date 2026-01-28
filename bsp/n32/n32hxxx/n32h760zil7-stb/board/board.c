/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#include "board.h"


/**
  * @brief  System_Initialize
  * @param  None
  * @retval None
  */
void System_Initialize(void)
{
    /* Copy Vert Table to ITCM */
    CopyVectTable(FLASH_BASE, ITCM_BASE, VECT_SIZE);

    /* Initialize system clock and enable Peripheral clock */
    RCC_Configuration();

#ifdef N32H78x
    /* Enable Cortex-M4 boot*/
    RCC_EnableCM4(0x15080000);
#endif

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Config Peripheral GPIO */
    GPIO_Configuration();
}
