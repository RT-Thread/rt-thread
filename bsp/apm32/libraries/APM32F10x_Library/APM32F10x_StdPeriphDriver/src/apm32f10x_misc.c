/*!
 * @file        apm32f10x_misc.c
 *
 * @brief       This file provides all the miscellaneous firmware functions.
 *             Include NVIC,SystemTick and Power management.
 *
 * @version     V1.0.4
 *
 * @date        2022-12-01
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "apm32f10x_misc.h"

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup MISC_Driver MISC Driver
  @{
*/

/** @defgroup MISC_Macros Macros
  @{
*/

#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

/**@} end of group MISC_Macros*/


/** @defgroup MISC_Functions Functions
  @{
*/

/*!
 * @brief     Configures the priority grouping: pre-emption priority and subpriority.
 *
 * @param     priorityGroup : specifies the priority grouping bits length.
 *                            This parameter can be one of the following values:
 *                            @arg NVIC_PRIORITY_GROUP_0
 *                            @arg NVIC_PRIORITY_GROUP_1
 *                            @arg NVIC_PRIORITY_GROUP_2
 *                            @arg NVIC_PRIORITY_GROUP_3
 *                            @arg NVIC_PRIORITY_GROUP_4
 *
 * @retval    None
 */
void NVIC_ConfigPriorityGroup(NVIC_PRIORITY_GROUP_T priorityGroup)
{
    SCB->AIRCR = AIRCR_VECTKEY_MASK | priorityGroup;
}

/*!
 * @brief     Enable NVIC request
 *
 * @param     irq: the NVIC interrupt request, detailed in IRQn_Type
 *            For the complete APM32 Devices IRQ Channels list,please refer to apm32f10x.h file
 *
 * @param     preemptionPriority: the pre-emption priority needed to set
 *
 * @param     subPriority: the subpriority needed to set
 *
 * @retval    None
 */
void NVIC_EnableIRQRequest(IRQn_Type irq, uint8_t preemptionPriority, uint8_t subPriority)
{
    uint32_t tempPriority, tempPrePri, tempSubPri;
    uint32_t priorityGrp;

    /* Get priority group */
    priorityGrp = (SCB->AIRCR) & (uint32_t)0x700U;

    /* get pre-emption priority and subpriority */
    switch (priorityGrp)
    {
        case NVIC_PRIORITY_GROUP_0:
            tempPrePri = 0;
            tempSubPri = 4;
            break;

        case NVIC_PRIORITY_GROUP_1:
            tempPrePri = 1;
            tempSubPri = 3;
            break;

        case NVIC_PRIORITY_GROUP_2:
            tempPrePri = 2;
            tempSubPri = 2;
            break;

        case NVIC_PRIORITY_GROUP_3:
            tempPrePri = 3;
            tempSubPri = 1;
            break;

        case NVIC_PRIORITY_GROUP_4:
            tempPrePri = 4;
            tempSubPri = 0;
            break;

        default:
            NVIC_ConfigPriorityGroup(NVIC_PRIORITY_GROUP_0);
            tempPrePri = 0;
            tempSubPri = 4;
            break;
    }

    tempPrePri = 4 - tempPrePri;
    tempSubPri = 4 - tempSubPri;
    tempPriority = preemptionPriority << tempPrePri;
    tempPriority |= subPriority & (0x0f >> tempSubPri);
    tempPriority <<= 4;
    NVIC->IP[irq] = (uint8_t)tempPriority;

    /* enable the selected IRQ */
    NVIC->ISER[irq >> 0x05U] = (uint32_t)0x01U << (irq & (uint8_t)0x1FU);
}

/*!
 * @brief     Disable NVIC request
 *
 * @param     irq: the NVIC interrupt request, detailed in IRQn_Type
 *
 * @retval    None
 */
void NVIC_DisableIRQRequest(IRQn_Type irq)
{
    /* disable the selected IRQ.*/
    NVIC->ICER[irq >> 0x05U] = (uint32_t)0x01U << (irq & (uint8_t)0x1FU);
}

/*!
 * @brief     Configs the vector table location and Offset.
 *
 * @param     vectTab: specifies if the vector table is in RAM or FLASH memory
 *                     This parameter can be one of the following values:
 *                     @arg NVIC_VECT_TAB_RAM
 *                     @arg NVIC_VECT_TAB_FLASH
 *
 * @param     Offset   Vector Table base offset field. This value must be a multiple of 0x200
 *
 * @retval    None
 */
void NVIC_ConfigVectorTable(NVIC_VECT_TAB_T vectTab, uint32_t offset)
{
    SCB->VTOR = vectTab | (offset & (uint32_t)0x1FFFFF80);
}

/*!
 * @brief     set the state of the low power mode
 *
 * @param     lowPowerMode: the low power mode state
 *                          This parameter can be one of the following values:
 *                          @arg NVIC_LOWPOWER_SEVONPEND
 *                          @arg NVIC_LOWPOWER_SLEEPDEEP
 *                          @arg NVIC_LOWPOWER_SLEEPONEXIT
 *
 * @retval    None
 */
void NVIC_SetSystemLowPower(NVIC_LOWPOWER_T lowPowerMode)
{
    SCB->SCR |= lowPowerMode;
}

/*!
 * @brief     reset the state of the low power mode
 *
 * @param     lowPowerMode: the low power mode state
 *                          This parameter can be one of the following values:
 *                          @arg NVIC_LOWPOWER_SEVONPEND
 *                          @arg NVIC_LOWPOWER_SLEEPDEEP
 *                          @arg NVIC_LOWPOWER_SLEEPONEXIT
 *
 * @retval    None
 */
void NVIC_ResetystemLowPower(NVIC_LOWPOWER_T lowPowerMode)
{
    SCB->SCR &= (uint32_t)(~(uint32_t)lowPowerMode);
}

/*!
 * @brief     Configures the SysTick clock source
 *
 * @param     clkSource: specifies the SysTick clock source
 *                       This parameter can be one of the following values:
 *                       @arg SYSTICK_CLK_SOURCE_HCLK_DIV8: AHB clock divided by 8 selected as SysTick clock source.
 *                       @arg SYSTICK_CLK_SOURCE_HCLK: AHB clock selected as SysTick clock source.
 *
 * @retval    None
 */
void SysTick_ConfigCLKSource(SYSTICK_CLK_SOURCE_T clkSource)
{
    if (clkSource == SYSTICK_CLK_SOURCE_HCLK)
    {
        SysTick->CTRL |= (uint32_t)BIT2;
    }
    else
    {
        SysTick->CTRL &= (uint32_t)(~BIT2);
    }
}

/**@} end of group MISC_Functions*/
/**@} end of group MISC_Driver */
/**@} end of group APM32F10x_StdPeriphDriver*/
