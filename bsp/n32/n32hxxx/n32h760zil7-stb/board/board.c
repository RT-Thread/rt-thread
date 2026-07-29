/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 * 2026-07-13     ox-horse         Add MPU_Config() and delect copy vector to ITCM
 */

#include "board.h"

/**
  * @brief  Configure MPU (Memory Protection Unit) memory region attributes.
  * @param  None
  * @retval None
  *
  * @note   The MPU controls memory attributes (Cache, Buffer, Share, etc.)
  *         for different address spaces.
  */
void MPU_Config(void)
{
#ifdef BSP_USING_NAND
    MPU_Region_InitType MPU_InitStruct = { 0 };

    /*
     * Configure NAND Flash address space as "Device" type memory
     * (TEX=1, C=0, B=1, S=1) to prevent CPU Cache from caching
     * FEMC MMIO accesses and to preserve access order.
     */
    MPU_Disable();

    MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
    MPU_InitStruct.Size             = MPU_REGION_SIZE_256MB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable     = MPU_ACCESS_BUFFERABLE;
    MPU_InitStruct.IsCacheable      = MPU_ACCESS_NOT_CACHEABLE;
    MPU_InitStruct.IsShareable      = MPU_ACCESS_SHAREABLE;
    MPU_InitStruct.Number           = MPU_REGION_NUMBER0;
    MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL1;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

#ifdef BSP_USING_NAND_BANK1
    MPU_InitStruct.BaseAddress = ((uint32_t)0xA0000000);
#endif /* BSP_USING_NAND_BANK1 */

#ifdef BSP_USING_NAND_BANK2
    MPU_InitStruct.BaseAddress = ((uint32_t)0xB0000000);
#endif /* BSP_USING_NAND_BANK2 */

    MPU_ConfigRegion(&MPU_InitStruct);

    /* Enable MPU, uncovered regions use default memory map */
    MPU_Enable(MPU_PRIVILEGED_DEFAULT);
#endif
}

/**
  * @brief  System_Initialize
  * @param  None
  * @retval None
  */
void System_Initialize(void)
{
    /* Initialize system clock and enable Peripheral clock */
    RCC_Configuration();

#ifdef N32H78x
    /* Enable Cortex-M4 boot*/
    RCC_EnableCM4(0x15080000);
#endif

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Config Peripheral GPIO */
    GPIO_Configuration();

    /* MPU Config */
    MPU_Config();
}
