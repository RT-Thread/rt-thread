/**
  ******************************************************************************
  * @file               ft32f4xx_misc.c
  * @author             FMD AE
  * @brief              This file provides all the miscellaneous firmware functions (add-on
  *                     to CMSIS functions).
  * @version            V1.0.0
  * @data                   2025-07-01
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_misc.h"

/** @defgroup MISC
  * @brief MISC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup MISC_Private_Functions
  * @{
  */

/**
  * @brief  Configures the priority grouping: pre-emption priority and subpriority.
  * @param  NVIC_PriorityGroup: specifies the priority grouping bits length.
  *   This parameter can be one of the following values:
  *     @arg NVIC_PriorityGroup_0: 0 bits for pre-emption priority
  *                                4 bits for subpriority
  *     @arg NVIC_PriorityGroup_1: 1 bits for pre-emption priority
  *                                3 bits for subpriority
  *     @arg NVIC_PriorityGroup_2: 2 bits for pre-emption priority
  *                                2 bits for subpriority
  *     @arg NVIC_PriorityGroup_3: 3 bits for pre-emption priority
  *                                1 bits for subpriority
  *     @arg NVIC_PriorityGroup_4: 4 bits for pre-emption priority
  *                                0 bits for subpriority
  * @note   When the NVIC_PriorityGroup_0 is selected, IRQ pre-emption is no more possible.
  *         The pending IRQ priority will be managed only by the subpriority.
  * @retval None
  */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
    /* Check the parameters */
    assert_param(IS_NVIC_PRIORITY_GROUP(NVIC_PriorityGroup));

    /* Set the PRIGROUP[10:8] bits according to NVIC_PriorityGroup value */
    SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
  * @brief  Initializes the NVIC peripheral according to the specified
  *         parameters in the NVIC_InitStruct.
  * @note   To configure interrupts priority correctly, the NVIC_PriorityGroupConfig()
  *         function should be called before.
  * @param  NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains
  *         the configuration information for the specified NVIC peripheral.
  * @retval None
  */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
    uint8_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NVIC_InitStruct->NVIC_IRQChannelCmd));
    assert_param(IS_NVIC_PREEMPTION_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority));
    assert_param(IS_NVIC_SUB_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelSubPriority));

    if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
    {
        /* Compute the Corresponding IRQ Priority --------------------------------*/
        tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700)) >> 0x08;
        tmppre = (0x4 - tmppriority);
        tmpsub = tmpsub >> tmppriority;

        tmppriority = NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
        tmppriority |= (uint8_t)(NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub);

        tmppriority = tmppriority << 0x04;

        NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;

        /* Enable the Selected IRQ Channels --------------------------------------*/
        NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
            (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
    }
    else
    {
        /* Disable the Selected IRQ Channels -------------------------------------*/
        NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
            (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
    }
}

/**
  * @brief  Sets the vector table location and Offset.
  * @param  NVIC_VectTab: specifies if the vector table is in RAM or FLASH memory.
  *   This parameter can be one of the following values:
  *     @arg NVIC_VectTab_RAM: Vector Table in internal SRAM.
  *     @arg NVIC_VectTab_FLASH: Vector Table in internal FLASH.
  * @param  Offset: Vector Table base offset field. This value must be a multiple of 0x200.
  * @retval None
  */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{
    /* Check the parameters */
    assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
    assert_param(IS_NVIC_OFFSET(Offset));

    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/**
  * @brief  Selects the condition for the system to enter low power mode.
  * @param  LowPowerMode: Specifies the new mode for the system to enter low power mode.
  *   This parameter can be one of the following values:
  *     @arg NVIC_LP_SEVONPEND: Low Power SEV on Pend.
  *     @arg NVIC_LP_SLEEPDEEP: Low Power DEEPSLEEP request.
  *     @arg NVIC_LP_SLEEPONEXIT: Low Power Sleep on Exit.
  * @param  NewState: new state of LP condition. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_NVIC_LP(LowPowerMode));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        SCB->SCR |= LowPowerMode;
    }
    else
    {
        SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
    }
}


/* Systick initial ---------------------------------------------------------- */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @addtogroup Private_Variables
  * @{
  */
//__IO uint32_t uwTick;
//uint32_t uwTickPrio   = (1UL << 4U); /* Invalid PRIO */
//TickFreqTypeDef uwTickFreq = TICK_FREQ_DEFAULT;  /* 1KHz */
///**
//  * @}
//  */

//uint32_t SystemCoreClocktik = 210000000; /*SYSTEM clock frequece */

//#define TICK_INT_PRIORITY  (0x0FU) /*!< tick interrupt priority */


///**
//  * @brief  Initializes the System Timer and its its interrupt,and statrs the System Tick Timer.
//  *         Counter is in free running mode to generate periodic interrupts.
//  * @param  TicksNumb Specifies the ticks Number of ticks between two interrupts.
//  * @retval status: -0 Function succeeded.
//  *                 -1 Function failed.
//  */
//uint32_t SYSTICK_Config(uint32_t TicksNumb)
//{
//  return SysTick_Config(TicksNumb);
//}

///**
//  * @brief  This function configures the source of the time base.
//  *         The time source is configured  to have 1ms time base with a dedicated
//  *         Tick interrupt priority.
//  * @note   In the default implementation, SysTick timer is the source of time base.
//  *         It is used to generate interrupts at regular time intervals.
//  *         The SysTick interrupt must have higher priority (numerically lower)
//  *         than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
//  *         The function is declared as void __attribute__((weak))  to be overwritten  in case of other
//  *         implementation  in user file.
//  * @param  TickPriority Tick interrupt priority.
//  * @retval staus:
//  */
//void InitTick(uint32_t TickPriority,uint32_t SubPriority)
//{
//  uint32_t prioritygroup = 0x00U;

//  prioritygroup = NVIC_GetPriorityGrouping();

//  /* Configure the SysTick to have interrupt in 1ms time basis*/
//  if (SYSTICK_Config(SystemCoreClocktik / (1000U / uwTickFreq)) > 0U)
//  {
//    return;
//  }

//  /* Configure the SysTick IRQ priority */
//  if (TickPriority < (1UL << 4U))
//  {
//    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(prioritygroup, TickPriority, SubPriority));
//    uwTickPrio = TickPriority;
//  }
//  else
//  {
//    return;
//  }

//  return;
//}

///**
//  * @brief This function is called to increment  a global variable "uwTick"
//  *        used as application time base.
//  * @note  In the default implementation, this variable is incremented each 1ms
//  *        in SysTick ISR.
// * @note   This function is declared as void __attribute__((weak)) to be overwritten in case of other
//  *        implementations in user file.
//  * @retval None
//  */
//void IncTick(void)
//{
//  uwTick += uwTickFreq;
//}

///**
//  * @brief  Provides a tick value in millisecond.
//  * @note   This function is declared as void __attribute__((weak)) to be overwritten in case of other
//  *         implementations in user file.
//  * @retval tick value
//  */
//uint32_t GetTick(void)
//{
//  return uwTick;
//}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
