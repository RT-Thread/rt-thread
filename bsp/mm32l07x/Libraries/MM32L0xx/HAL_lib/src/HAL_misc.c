/**
******************************************************************************
* @file    HAL_misc.c
* @author  AE Team
* @version  V2.0.0
* @date  22/08/2017
* @brief   This file provides all the miscellaneous firmware functions (add-on
*          to CMSIS functions).
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2017 MindMotion</center></h2>
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "HAL_misc.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup MISC 
* @brief MISC driver modules
* @{
*/

/** @defgroup MISC_Private_TypesDefinitions
* @{
*/

/**
* @}
*/ 

/** @defgroup MISC_Private_Defines
* @{
*/

#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)
/**
* @}
*/


/**
* @brief  Initializes the NVIC peripheral according to the specified
*         parameters in the NVIC_InitStruct.
* @param  NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains
*         the configuration information for the specified NVIC peripheral.
* @retval None
*/
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
  uint32_t tmppriority = 0x00;
  
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NVIC_InitStruct->NVIC_IRQChannelCmd));
  assert_param(IS_NVIC_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelPriority));  
    
  if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
  {
    /* Compute the Corresponding IRQ Priority --------------------------------*/    
    tmppriority = NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02];
    tmppriority &= (uint32_t)(~(((uint32_t)0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8)));
    tmppriority |= (uint32_t)((((uint32_t)NVIC_InitStruct->NVIC_IRQChannelPriority << 6) & 0xFF) << ((NVIC_InitStruct->NVIC_IRQChannel & 0x03) * 8));    
    
    NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel >> 0x02] = tmppriority;
    
    /* Enable the Selected IRQ Channels --------------------------------------*/
    NVIC->ISER[0] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* Disable the Selected IRQ Channels -------------------------------------*/
    NVIC->ICER[0] = (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

/**
* @brief  Sets the vector table location and Offset.
* @param  NVIC_VectTab: specifies if the vector table is in RAM or FLASH memory.
*   This parameter can be one of the following values:
*     @arg NVIC_VectTab_RAM
*     @arg NVIC_VectTab_FLASH
* @param  Offset: Vector Table base offset field. This value must be a multiple 
*         of 0x200.
* @retval None
*/
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
//    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/**
* @brief  Selects the condition for the system to enter low power mode.
* @param  LowPowerMode: Specifies the new mode for the system to enter low power mode.
*   This parameter can be one of the following values:
*     @arg NVIC_LP_SEVONPEND
*     @arg NVIC_LP_SLEEPDEEP
*     @arg NVIC_LP_SLEEPONEXIT
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

/**
* @brief  Configures the SysTick clock source.
* @param  SysTick_CLKSource: specifies the SysTick clock source.
*   This parameter can be one of the following values:
*     @arg SysTick_CLKSource_HCLK_Div8: AHB clock divided by 8 selected as SysTick clock source.
*     @arg SysTick_CLKSource_HCLK: AHB clock selected as SysTick clock source.
* @retval None
*/
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
    /* Check the parameters */
assert_param(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));
    
    if (SysTick_CLKSource == SysTick_CLKSource_HCLK)
    {
        SysTick->CTRL |= SysTick_CLKSource_HCLK;
    }
    else
    {
        SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
    }
}

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2017 MindMotion ----------------------*/
