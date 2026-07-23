/**
  ******************************************************************************
  * @file    tae32f53xx_ll_cortex.c
  * @author  MCD Application Team
  * @brief   CORTEX LL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the CORTEX:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================

    [..]
    *** How to configure Interrupts using CORTEX LL driver ***
    ===========================================================
    [..]
    This section provides functions allowing to configure the NVIC interrupts (IRQ).
    The Cortex-M3 exceptions are managed by CMSIS functions.

    (#) Configure the NVIC Priority Grouping using LL_NVIC_SetPriorityGrouping()
        function according to the following table.
    (#) Configure the priority of the selected IRQ Channels using LL_NVIC_SetPriority().
    (#) Enable the selected IRQ Channels using LL_NVIC_EnableIRQ().
    (#) please refer to programming manual for details in how to configure priority.

     -@- When the NVIC_PRIORITYGROUP_0 is selected, IRQ preemption is no more possible.
         The pending IRQ priority will be managed only by the sub priority.

     -@- IRQ priority order (sorted by highest to lowest priority):
        (+@) Lowest preemption priority
        (+@) Lowest sub priority
        (+@) Lowest hardware priority (IRQ number)

    [..]
    *** How to configure Systick using CORTEX LL driver ***
    ========================================================
    [..]
    Setup SysTick Timer for time base.

   (+) The LL_SYSTICK_Config()function calls the SysTick_Config() function which
       is a CMSIS function that:
        (++) Configures the SysTick Reload register with value passed as function parameter.
        (++) Configures the SysTick IRQ priority to the lowest value 0x07.
        (++) Resets the SysTick Counter register.
        (++) Configures the SysTick Counter clock source to be Core Clock Source (HCLK).
        (++) Enables the SysTick Interrupt.
        (++) Starts the SysTick Counter.

   (+) You can change the SysTick Clock source to be HCLK_Div8 by calling the function
       LL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8) just after the
       LL_SYSTICK_Config() function call. The LL_SYSTICK_CLKSourceConfig() function is defined below.

   (+) You can change the SysTick IRQ priority by calling the
       LL_NVIC_SetPriority(SysTick_IRQn,...) function just after the LL_SYSTICK_Config() function
       call. The LL_NVIC_SetPriority() call the NVIC_SetPriority() function which is a CMSIS function.

   (+) To adjust the SysTick time base, use the following formula:

       Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
       (++) Reload Value is the parameter to be passed for LL_SYSTICK_Config() function
       (++) Reload Value should not exceed 0xFFFFFF

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"


#define DBG_TAG             "Cortex LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/**
  * @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup CORTEX_LL CORTEX LL
  * @brief    CORTEX LL module driver
  * @{
  */

#ifdef LL_CORTEX_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup CORTEX_LL_Exported_Functions CORTEX LL Exported Functions
  * @brief    CORTEX LL Exported Functions
  * @{
  */

/** @defgroup CORTEX_LL_Exported_Functions_Group1 NVIC Priority Config Functions
 *  @brief    NVIC Priority Config Functions
 *  @{
 */

/** @brief  Sets the priority grouping field (preemption priority and subpriority)
  *         using the required unlock sequence.
  * @param  PriorityGroup: The priority grouping bits length.
  *         This parameter can be one of the following values:
  *         @arg NVIC_PRIORITYGROUP_0: 0 bit  for pre-emption priority,
  *                                    3 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_1: 1 bit  for pre-emption priority,
  *                                    2 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_2: 2 bits for pre-emption priority,
  *                                    1 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_3: 3 bits for pre-emption priority,
  *                                    0 bit  for subpriority
  * @note   When the NVIC_PriorityGroup_0 is selected, IRQ preemption is no more possible.
  *         The pending IRQ priority will be managed only by the subpriority.
  * @return None
  */
void LL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
    /* Check the parameters */
    assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));

    /* Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value */
    NVIC_SetPriorityGrouping(PriorityGroup);
}

/**
  * @brief  Gets the priority grouping field from the NVIC Interrupt Controller.
  * @return Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field)
  */
uint32_t LL_NVIC_GetPriorityGrouping(void)
{
    /* Get the PRIGROUP[10:8] field value */
    return NVIC_GetPriorityGrouping();
}

/**
  * @brief  Sets the priority of an interrupt.
  * @param  IRQn: External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F53xx Devices IRQ Channels list, please refer to the appropriate CMSIS device file tae32f53xx.h)
  * @param  PreemptPriority: The preemption priority for the IRQn channel.
  *         This parameter can be a value between 0 and 7
  *         A lower priority value indicates a higher priority
  * @param  SubPriority: the subpriority level for the IRQ channel.
  *         This parameter can be a value between 0 and 7
  *         A lower priority value indicates a higher priority.
  * @note   The table below gives the allowed values of the pre-emption priority and subpriority according
  *         to the Priority Grouping configuration performed by LL_NVIC_SetPriorityGrouping() function.
  *           =========================================================================================
  *             NVIC_PriorityGroup   | PreemptPriority | SubPriority |          Description
  *           =========================================================================================
  *            NVIC_PRIORITYGROUP_0  |        0        |     0-7     | 0 bit for pre-emption priority
  *                                  |                 |             | 3 bits for subpriority
  *           -----------------------------------------------------------------------------------------
  *            NVIC_PRIORITYGROUP_1  |       0-1       |     0-3     | 1 bit for pre-emption priority
  *                                  |                 |             | 2 bits for subpriority
  *           -----------------------------------------------------------------------------------------
  *            NVIC_PRIORITYGROUP_2  |       0-3       |     0-1     | 2 bits for pre-emption priority
  *                                  |                 |             | 1 bits for subpriority
  *           -----------------------------------------------------------------------------------------
  *            NVIC_PRIORITYGROUP_3  |       0-7       |      0      | 3 bits for pre-emption priority
  *                                  |                 |             | 0 bit for subpriority
  *           =========================================================================================
  * @return None
  */
void LL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    uint32_t prioritygroup = 0x00U;

    /* Check the parameters */
    assert_param(IS_NVIC_SUB_PRIORITY(SubPriority));
    assert_param(IS_NVIC_PREEMPTION_PRIORITY(PreemptPriority));

    prioritygroup = NVIC_GetPriorityGrouping();

    NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
}

/**
  * @brief  Gets the priority of an interrupt.
  * @param  IRQn: External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F53xx Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f53xx.h))
  * @param  PriorityGroup: the priority grouping bits length.
  *         This parameter can be one of the following values:
  *           @arg NVIC_PRIORITYGROUP_0: 0 bits for preemption priority
  *                                      3 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_1: 1 bits for preemption priority
  *                                      2 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_2: 2 bits for preemption priority
  *                                      1 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_3: 3 bits for preemption priority
  *                                      0 bits for subpriority
  * @param  pPreemptPriority: Pointer on the Preemptive priority value (starting from 0).
  * @param  pSubPriority: Pointer on the Subpriority value (starting from 0).
  * @return None
  */
void LL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *pPreemptPriority, uint32_t *pSubPriority)
{
    /* Check the parameters */
    assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));

    /* Get priority for Cortex-M system or device specific interrupts */
    NVIC_DecodePriority(NVIC_GetPriority(IRQn), PriorityGroup, pPreemptPriority, pSubPriority);
}
/**
  * @}
  */


/** @defgroup CORTEX_LL_Exported_Functions_Group2 NVIC Enable and Pending Config Functions
  * @brief    NVIC Enable and Pending Config Functions
  * @{
  */

/**
  * @brief  Enables a device specific interrupt in the NVIC interrupt controller.
  * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
  *         function should be called before.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F53xx Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f53xx.h))
  * @return None
  */
void LL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

    /* Enable interrupt */
    NVIC_EnableIRQ(IRQn);
}

/**
  * @brief  Disables a device specific interrupt in the NVIC interrupt controller.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F53xx Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f53xx.h))
  * @return None
  */
void LL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

    /* Disable interrupt */
    NVIC_DisableIRQ(IRQn);
}

/**
  * @brief  Sets Pending bit of an external interrupt.
  * @param  IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F53xx Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f53xx.h))
  * @return None
  */
void LL_NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

    /* Set interrupt pending */
    NVIC_SetPendingIRQ(IRQn);
}

/**
  * @brief  Gets Pending Interrupt (reads the pending register in the NVIC
  *         and returns the pending bit for the specified interrupt).
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F53xx Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f53xx.h))
  * @return pending status
  *   @retval 0  Interrupt status is not pending.
  *   @retval 1  Interrupt status is pending.
  */
uint32_t LL_NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

    /* Return 1 if pending else 0 */
    return NVIC_GetPendingIRQ(IRQn);
}

/**
  * @brief  Clears the pending bit of an external interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F53xx Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f53xx.h))
  * @return None
  */
void LL_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

    /* Clear pending interrupt */
    NVIC_ClearPendingIRQ(IRQn);
}

/**
  * @brief Gets active interrupt ( reads the active register in NVIC and returns the active bit).
  * @param IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete TAE32F53xx Devices IRQ Channels list, please refer to the appropriate CMSIS device file (tae32f53xx.h))
  * @return status: - 0  Interrupt status is not pending.
  *                 - 1  Interrupt status is pending.
  */
uint32_t LL_NVIC_GetActive(IRQn_Type IRQn)
{
    /* Check the parameters */
    assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

    /* Return 1 if active else 0 */
    return NVIC_GetActive(IRQn);
}

/**
  * @brief  Initiates a system reset request to reset the MCU.
  * @param  None
  * @return None
  */
void LL_NVIC_SystemReset(void)
{
    /* System Reset */
    NVIC_SystemReset();
}
/**
  * @}
  */


/** @defgroup CORTEX_LL_Exported_Functions_Group3 SYSTICK Config Functions
  * @brief    SYSTICK Config Functions
  * @{
  */

/**
  * @brief  Configures the SysTick clock source.
  * @param  CLKSource: specifies the SysTick clock source.
  *         This parameter can be one of the following values:
  *             @arg SYSTICK_CLKSOURCE_HCLK_DIV8: AHB clock divided by 8 selected as SysTick clock source.
  *             @arg SYSTICK_CLKSOURCE_HCLK: AHB clock selected as SysTick clock source.
  * @return None
  */
void LL_SYSTICK_CLKSourceConfig(uint32_t CLKSource)
{
    /* Check the parameters */
    assert_param(IS_SYSTICK_CLK_SOURCE(CLKSource));

    if (CLKSource == SYSTICK_CLKSOURCE_HCLK) {
        SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
    } else {
        SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
    }
}

/**
  * @brief  Initializes the System Timer and its interrupt, and starts the System Tick Timer.
  *         Counter is in free running mode to generate periodic interrupts.
  * @param  TicksNumb: Specifies the ticks Number of ticks between two interrupts.
  * @retval status:  - 0  Function succeeded.
  *                  - 1  Function failed.
  */
uint32_t LL_SYSTICK_Config(uint32_t TicksNumb)
{
    return SysTick_Config(TicksNumb);
}
/**
  * @}
  */


/** @defgroup CORTEX_LL_Exported_Functions_Interrupt CORTEX Interrupt management
  * @brief    CORTEX Interrupt management
  *
@verbatim
  ==============================================================================
                        ##### Interrupt Management #####
  ==============================================================================
  [..]
    This section provides CORTEX interrupt handler functions.
@endverbatim
  * @{
  */

/**
  * @brief  This function handles SYSTICK interrupts requests.
  * @param  None
  * @return None
  */
void LL_SYSTICK_IRQHandler(void)
{
    LL_SYSTICK_Callback();
}

/**
  * @brief  SYSTICK callback.
  * @param  None
  * @retval None
  */
__WEAK void LL_SYSTICK_Callback(void)
{
    /* NOTE : This function Should not be modified, when the callback is needed,
              the LL_SYSTICK_Callback could be implemented in the user file
     */
}
/**
  * @}
  */


/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/


#endif /* LL_CORTEX_MODULE_ENABLE */

/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

