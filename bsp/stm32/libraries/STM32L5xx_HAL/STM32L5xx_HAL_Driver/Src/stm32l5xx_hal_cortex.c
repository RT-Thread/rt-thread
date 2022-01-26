/**
  ******************************************************************************
  * @file    stm32l5xx_hal_cortex.c
  * @author  MCD Application Team
  * @brief   CORTEX HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the CORTEX:
  *           + Initialization and Configuration functions
  *           + Peripheral Control functions
  *
  @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================

    [..]
    *** How to configure Interrupts using CORTEX HAL driver ***
    ===========================================================
    [..]
    This section provides functions allowing to configure the NVIC interrupts (IRQ).
    The Cortex-M33 exceptions are managed by CMSIS functions.

    (#) Configure the NVIC Priority Grouping using HAL_NVIC_SetPriorityGrouping() function.
    (#) Configure the priority of the selected IRQ Channels using HAL_NVIC_SetPriority().
    (#) Enable the selected IRQ Channels using HAL_NVIC_EnableIRQ().

     -@- When the NVIC_PRIORITYGROUP_0 is selected, IRQ pre-emption is no more possible.
         The pending IRQ priority will be managed only by the sub priority.

     -@- IRQ priority order (sorted by highest to lowest priority):
        (+@) Lowest pre-emption priority
        (+@) Lowest sub priority
        (+@) Lowest hardware priority (IRQ number)

    [..]
    *** How to configure SysTick using CORTEX HAL driver ***
    ========================================================
    [..]
    Setup SysTick Timer for time base.

   (+) The HAL_SYSTICK_Config() function calls the SysTick_Config() function which
       is a CMSIS function that:
        (++) Configures the SysTick Reload register with value passed as function parameter.
        (++) Configures the SysTick IRQ priority to the lowest value (0x07).
        (++) Resets the SysTick Counter register.
        (++) Configures the SysTick Counter clock source to be Core Clock Source (HCLK).
        (++) Enables the SysTick Interrupt.
        (++) Starts the SysTick Counter.

   (+) You can change the SysTick Clock source to be HCLK_Div8 by calling the macro
       __HAL_CORTEX_SYSTICKCLK_CONFIG(SYSTICK_CLKSOURCE_HCLK_DIV8) just after the
       HAL_SYSTICK_Config() function call. The __HAL_CORTEX_SYSTICKCLK_CONFIG() macro is defined
       inside the stm32l5xx_hal_cortex.h file.

   (+) You can change the SysTick IRQ priority by calling the
       HAL_NVIC_SetPriority(SysTick_IRQn,...) function just after the HAL_SYSTICK_Config() function
       call. The HAL_NVIC_SetPriority() call the NVIC_SetPriority() function which is a CMSIS function.

   (+) To adjust the SysTick time base, use the following formula:

       Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
       (++) Reload Value is the parameter to be passed for HAL_SYSTICK_Config() function
       (++) Reload Value should not exceed 0xFFFFFF

  @endverbatim
  ******************************************************************************

  The table below gives the allowed values of the pre-emption priority and subpriority according
  to the Priority Grouping configuration performed by HAL_NVIC_SetPriorityGrouping() function.

    ==========================================================================================================================
      NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  |       Description
    ==========================================================================================================================
     NVIC_PRIORITYGROUP_0  |                0                  |            0-7              | 0 bit for pre-emption priority
                           |                                   |                             | 3 bits for subpriority
    --------------------------------------------------------------------------------------------------------------------------
     NVIC_PRIORITYGROUP_1  |                0-1                |            0-3              | 1 bit for pre-emption priority
                           |                                   |                             | 2 bits for subpriority
    --------------------------------------------------------------------------------------------------------------------------
     NVIC_PRIORITYGROUP_2  |                0-3                |            0-1              | 2 bits for pre-emption priority
                           |                                   |                             | 1 bits for subpriority
    --------------------------------------------------------------------------------------------------------------------------
     NVIC_PRIORITYGROUP_3  |                0-7                |            0                | 3 bits for pre-emption priority
                           |                                   |                             | 0 bit for subpriority
    ==========================================================================================================================

  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal.h"

/** @addtogroup STM32L5xx_HAL_Driver
  * @{
  */

/** @addtogroup CORTEX
  * @{
  */

#ifdef HAL_CORTEX_MODULE_ENABLED

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup CORTEX_Private_Functions CORTEX Private Functions
  * @{
  */
#if (__MPU_PRESENT == 1)
static void MPU_ConfigRegion(MPU_Type* MPUx, MPU_Region_InitTypeDef *MPU_RegionInit);
static void MPU_ConfigMemoryAttributes(MPU_Type* MPUx, MPU_Attributes_InitTypeDef *MPU_AttributesInit);
#endif /* __MPU_PRESENT */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup CORTEX_Exported_Functions
  * @{
  */


/** @addtogroup CORTEX_Exported_Functions_Group1
 *  @brief    Initialization and Configuration functions
 *
@verbatim
  ==============================================================================
              ##### Initialization and Configuration functions #####
  ==============================================================================
    [..]
      This section provides the CORTEX HAL driver functions allowing to configure Interrupts
      SysTick functionalities

@endverbatim
  * @{
  */


/**
  * @brief  Set the priority grouping field (pre-emption priority and subpriority)
  *         using the required unlock sequence.
  * @param  PriorityGroup The priority grouping bits length.
  *         This parameter can be one of the following values:
  *         @arg NVIC_PRIORITYGROUP_0  0 bit  for pre-emption priority,
  *                                    3 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_1  1 bit  for pre-emption priority,
  *                                    2 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_2  2 bits for pre-emption priority,
  *                                    1 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_3  3 bits for pre-emption priority,
  *                                    0 bit  for subpriority
  * @note   When the NVIC_PriorityGroup_0 is selected, IRQ pre-emption is no more possible.
  *         The pending IRQ priority will be managed only by the subpriority.
  * @retval None
  */
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  /* Check the parameters */
  assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));

  /* Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value */
  NVIC_SetPriorityGrouping(PriorityGroup);
}

/**
  * @brief  Set the priority of an interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32l5xxxx.h))
  * @param  PreemptPriority The pre-emption priority for the IRQn channel.
  *         This parameter can be a value between 0 and 7
  *         A lower priority value indicates a higher priority
  * @param  SubPriority The subpriority level for the IRQ channel.
  *         This parameter can be a value between 0 and 7
  *         A lower priority value indicates a higher priority.
  * @retval None
  */
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t prioritygroup;

  /* Check the parameters */
  assert_param(IS_NVIC_SUB_PRIORITY(SubPriority));
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(PreemptPriority));

  prioritygroup = NVIC_GetPriorityGrouping();

  NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
}

/**
  * @brief  Enable a device specific interrupt in the NVIC interrupt controller.
  * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
  *         function should be called before.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32l5xxxx.h))
  * @retval None
  */
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Enable interrupt */
  NVIC_EnableIRQ(IRQn);
}

/**
  * @brief  Disable a device specific interrupt in the NVIC interrupt controller.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32l5xxxx.h))
  * @retval None
  */
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
  /* Check the parameters */
  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

  /* Disable interrupt */
  NVIC_DisableIRQ(IRQn);
}

/**
  * @brief  Initiate a system reset request to reset the MCU.
  * @retval None
  */
void HAL_NVIC_SystemReset(void)
{
  /* System Reset */
  NVIC_SystemReset();
}

/**
  * @brief  Initialize the System Timer with interrupt enabled and start the System Tick Timer (SysTick):
  *         Counter is in free running mode to generate periodic interrupts.
  * @param  TicksNumb Specifies the ticks Number of ticks between two interrupts.
  * @retval status:  - 0  Function succeeded.
  *                  - 1  Function failed.
  */
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb)
{
  return SysTick_Config(TicksNumb);
}
/**
  * @}
  */

/** @addtogroup CORTEX_Exported_Functions_Group2
 *  @brief   Cortex control functions
 *
@verbatim
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================
    [..]
      This subsection provides a set of functions allowing to control the CORTEX
      (NVIC, SYSTICK, MPU) functionalities.


@endverbatim
  * @{
  */

/**
  * @brief  Get the priority grouping field from the NVIC Interrupt Controller.
  * @retval Priority grouping field (SCB->AIRCR [10:8] PRIGROUP field)
  */
uint32_t HAL_NVIC_GetPriorityGrouping(void)
{
  /* Get the PRIGROUP[10:8] field value */
  return NVIC_GetPriorityGrouping();
}

/**
  * @brief  Get the priority of an interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32l5xxxx.h))
  * @param   PriorityGroup: the priority grouping bits length.
  *         This parameter can be one of the following values:
  *           @arg NVIC_PRIORITYGROUP_0  0 bit for pre-emption priority,
  *                                      3 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_1  1 bit for pre-emption priority,
  *                                      2 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_2  2 bits for pre-emption priority,
  *                                      1 bits for subpriority
  *           @arg NVIC_PRIORITYGROUP_3  3 bits for pre-emption priority,
  *                                      0 bit for subpriority
  * @param  pPreemptPriority Pointer on the Preemptive priority value (starting from 0).
  * @param  pSubPriority Pointer on the Subpriority value (starting from 0).
  * @retval None
  */
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *pPreemptPriority, uint32_t *pSubPriority)
{
  /* Check the parameters */
  assert_param(IS_NVIC_PRIORITY_GROUP(PriorityGroup));
 /* Get priority for Cortex-M system or device specific interrupts */
  NVIC_DecodePriority(NVIC_GetPriority(IRQn), PriorityGroup, pPreemptPriority, pSubPriority);
}

/**
  * @brief  Set Pending bit of an external interrupt.
  * @param  IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32l5xxxx.h))
  * @retval None
  */
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  /* Set interrupt pending */
  NVIC_SetPendingIRQ(IRQn);
}

/**
  * @brief  Get Pending Interrupt (read the pending register in the NVIC
  *         and return the pending bit for the specified interrupt).
  * @param  IRQn External interrupt number.
  *          This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32l5xxxx.h))
  * @retval status: - 0  Interrupt status is not pending.
  *                 - 1  Interrupt status is pending.
  */
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  /* Return 1 if pending else 0 */
  return NVIC_GetPendingIRQ(IRQn);
}

/**
  * @brief  Clear the pending bit of an external interrupt.
  * @param  IRQn External interrupt number.
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32l5xxxx.h))
  * @retval None
  */
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  /* Clear pending interrupt */
  NVIC_ClearPendingIRQ(IRQn);
}

/**
  * @brief  Get active interrupt (read the active register in NVIC and return the active bit).
  * @param  IRQn External interrupt number
  *         This parameter can be an enumerator of IRQn_Type enumeration
  *         (For the complete STM32 Devices IRQ Channels list, please refer to the appropriate CMSIS device file (stm32l5xxxx.h))
  * @retval status: - 0  Interrupt status is not pending.
  *                 - 1  Interrupt status is pending.
  */
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn)
{
  /* Return 1 if active else 0 */
  return NVIC_GetActive(IRQn);
}

/**
  * @brief  Configure the SysTick clock source.
  * @param  CLKSource specifies the SysTick clock source.
  *         This parameter can be one of the following values:
  *             @arg SYSTICK_CLKSOURCE_HCLK_DIV8: AHB clock divided by 8 selected as SysTick clock source.
  *             @arg SYSTICK_CLKSOURCE_HCLK: AHB clock selected as SysTick clock source.
  * @retval None
  */
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource)
{
  /* Check the parameters */
  assert_param(IS_SYSTICK_CLK_SOURCE(CLKSource));
  if (CLKSource == SYSTICK_CLKSOURCE_HCLK)
  {
    SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
  }
  else
  {
    SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
  }
}

/**
  * @brief  Handle SYSTICK interrupt request.
  * @retval None
  */
void HAL_SYSTICK_IRQHandler(void)
{
  HAL_SYSTICK_Callback();
}

/**
  * @brief  SYSTICK callback.
  * @retval None
  */
__weak void HAL_SYSTICK_Callback(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SYSTICK_Callback could be implemented in the user file
   */
}

#if (__MPU_PRESENT == 1)

/**
  * @brief  Enable the MPU.
  * @param  MPU_Control Specifies the control mode of the MPU during hard fault,
  *         NMI, FAULTMASK and privileged accessto the default memory
  *         This parameter can be one of the following values:
  *            @arg MPU_HFNMI_PRIVDEF_NONE
  *            @arg MPU_HARDFAULT_NMI
  *            @arg MPU_PRIVILEGED_DEFAULT
  *            @arg MPU_HFNMI_PRIVDEF
  * @retval None
  */
void HAL_MPU_Enable(uint32_t MPU_Control)
{
  /* Enable the MPU */
  MPU->CTRL   = MPU_Control | MPU_CTRL_ENABLE_Msk;

  /* Enable fault exceptions */
  SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;

  /* Follow ARM recommendation with */
  /* - Data Memory Barrier and Instruction Synchronization to insure MPU usage */
  __DMB(); /* Force memory writes before continuing */
  __ISB(); /* Flush and refill pipeline with updated permissions */
}

/**
  * @brief  Disable the MPU.
  * @retval None
  */
void HAL_MPU_Disable(void)
{
  __DMB(); /* Force any outstanding transfers to complete before disabling MPU */

  /* Disable the MPU */
  MPU->CTRL  &= ~MPU_CTRL_ENABLE_Msk;
}

/**
  * @brief  Initialize and configure the Region and the memory to be protected.
  * @param  MPU_RegionInit Pointer to a MPU_Region_InitTypeDef structure that contains
  *                        the initialization and configuration information.
  * @retval None
  */
void HAL_MPU_ConfigRegion(MPU_Region_InitTypeDef *MPU_RegionInit)
{
  MPU_ConfigRegion(MPU, MPU_RegionInit);
}

/**
  * @brief  Initialize and configure the memory attributes.
  * @param  MPU_AttributesInit Pointer to a MPU_Attributes_InitTypeDef structure that contains
  *                            the initialization and configuration information.
  * @retval None
  */
void HAL_MPU_ConfigMemoryAttributes(MPU_Attributes_InitTypeDef *MPU_AttributesInit)
{
  MPU_ConfigMemoryAttributes(MPU, MPU_AttributesInit);
}

#ifdef MPU_NS
/**
  * @brief  Enable the non-secure MPU.
  * @param  MPU_Control Specifies the control mode of the MPU during hard fault,
  *         NMI, FAULTMASK and privileged accessto the default memory
  *         This parameter can be one of the following values:
  *            @arg MPU_HFNMI_PRIVDEF_NONE
  *            @arg MPU_HARDFAULT_NMI
  *            @arg MPU_PRIVILEGED_DEFAULT
  *            @arg MPU_HFNMI_PRIVDEF
  * @retval None
  */
void HAL_MPU_Enable_NS(uint32_t MPU_Control)
{
  /* Enable the MPU */
  MPU_NS->CTRL   = MPU_Control | MPU_CTRL_ENABLE_Msk;

  /* Enable fault exceptions */
  SCB_NS->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;

  /* Follow ARM recommendation with */
  /* - Data Memory Barrier and Instruction Synchronization to insure MPU usage */
  __DMB(); /* Force memory writes before continuing */
  __ISB(); /* Flush and refill pipeline with updated permissions */
}

/**
  * @brief  Disable the non-secure MPU.
  * @retval None
  */
void HAL_MPU_Disable_NS(void)
{
  __DMB(); /* Force any outstanding transfers to complete before disabling MPU */

  /* Disable the MPU */
  MPU_NS->CTRL  &= ~MPU_CTRL_ENABLE_Msk;
}

/**
  * @brief  Initialize and configure the Region and the memory to be protected for non-secure MPU.
  * @param  MPU_RegionInit Pointer to a MPU_Region_InitTypeDef structure that contains
  *                        the initialization and configuration information.
  * @retval None
  */
void HAL_MPU_ConfigRegion_NS(MPU_Region_InitTypeDef *MPU_RegionInit)
{
  MPU_ConfigRegion(MPU_NS, MPU_RegionInit);
}

/**
  * @brief  Initialize and configure the memory attributes for non-secure MPU.
  * @param  MPU_AttributesInit Pointer to a MPU_Attributes_InitTypeDef structure that contains
  *                            the initialization and configuration information.
  * @retval None
  */
void HAL_MPU_ConfigMemoryAttributes_NS(MPU_Attributes_InitTypeDef *MPU_AttributesInit)
{
  MPU_ConfigMemoryAttributes(MPU_NS, MPU_AttributesInit);
}
#endif /* MPU_NS */

#endif /* __MPU_PRESENT */

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup CORTEX_Private_Functions
  * @{
  */

#if (__MPU_PRESENT == 1)

static void MPU_ConfigRegion(MPU_Type* MPUx, MPU_Region_InitTypeDef *MPU_RegionInit)
{
  /* Check the parameters */
  assert_param(IS_MPU_REGION_NUMBER(MPU_RegionInit->Number));
  assert_param(IS_MPU_REGION_ENABLE(MPU_RegionInit->Enable));

  /* Follow ARM recommendation with Data Memory Barrier prior to MPU configuration */
  __DMB();

  /* Set the Region number */
  MPUx->RNR = MPU_RegionInit->Number;

  if (MPU_RegionInit->Enable != MPU_REGION_DISABLE)
  {
    /* Check the parameters */
    assert_param(IS_MPU_INSTRUCTION_ACCESS(MPU_RegionInit->DisableExec));
    assert_param(IS_MPU_REGION_PERMISSION_ATTRIBUTE(MPU_RegionInit->AccessPermission));
    assert_param(IS_MPU_ACCESS_SHAREABLE(MPU_RegionInit->IsShareable));

    MPUx->RBAR = (((uint32_t)MPU_RegionInit->BaseAddress & 0xFFFFFFE0U)  |
                  ((uint32_t)MPU_RegionInit->IsShareable      << MPU_RBAR_SH_Pos)  |
                  ((uint32_t)MPU_RegionInit->AccessPermission << MPU_RBAR_AP_Pos)  |
                  ((uint32_t)MPU_RegionInit->DisableExec      << MPU_RBAR_XN_Pos));

    MPUx->RLAR = (((uint32_t)MPU_RegionInit->LimitAddress & 0xFFFFFFE0U) |
                  ((uint32_t)MPU_RegionInit->AttributesIndex << MPU_RLAR_AttrIndx_Pos) |
                  ((uint32_t)MPU_RegionInit->Enable          << MPU_RLAR_EN_Pos));
  }
  else
  {
    MPUx->RBAR = 0U;
    MPUx->RLAR = 0U;
  }
}

static void MPU_ConfigMemoryAttributes(MPU_Type* MPUx, MPU_Attributes_InitTypeDef *MPU_AttributesInit)
{
  __IO uint32_t *mair;
  uint32_t      attr_values;
  uint32_t      attr_number;

  /* Check the parameters */
  assert_param(IS_MPU_ATTRIBUTES_NUMBER(MPU_AttributesInit->Number));
  /* No need to check Attributes value as all 0x0..0xFF possible */

  /* Follow ARM recommendation with Data Memory Barrier prior to MPUx configuration */
  __DMB();

  if(MPU_AttributesInit->Number < MPU_ATTRIBUTES_NUMBER4)
  {
    /* Program MPU_MAIR0 */
    mair = &(MPUx->MAIR0);
    attr_number = MPU_AttributesInit->Number;
  }
  else
  {
    /* Program MPU_MAIR1 */
    mair = &(MPUx->MAIR1);
    attr_number = (uint32_t)MPU_AttributesInit->Number - 4U;
  }

  attr_values = *(mair);
  attr_values &=  ~(0xFFU << (attr_number * 8U));
  *(mair) = attr_values | ((uint32_t)MPU_AttributesInit->Attributes << (attr_number * 8U));
}

#endif /* __MPU_PRESENT */

/**
  * @}
  */

#endif /* HAL_CORTEX_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
