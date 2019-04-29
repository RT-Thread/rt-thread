/**
******************************************************************************
* @file    HAL_misc.c
* @author  AE Team
* @version V1.0.0
* @date    28/7/2017
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

/** @defgroup MISC_Private_Macros
* @{
*/

/**
* @}
*/

/** @defgroup MISC_Private_Variables
* @{
*/

/**
* @}
*/

/** @defgroup MISC_Private_FunctionPrototypes
* @{
*/

/**
* @}
*/

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
* @retval None
*/
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
    
    
    /* Set the PRIGROUP[10:8] bits according to NVIC_PriorityGroup value */
    SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
* @brief  Initializes the NVIC peripheral according to the specified
*         parameters in the NVIC_InitStruct.
* @param  NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains
*         the configuration information for the specified NVIC peripheral.
* @retval None
*/
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
    uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
    
    
    
    if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
    {
        /* Compute the Corresponding IRQ Priority --------------------------------*/    
        tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
        tmppre = (0x4 - tmppriority);
        tmpsub = tmpsub >> tmppriority;
        
        tmppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
        tmppriority |=  NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
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
    
    tmppre = NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05];
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
    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
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
