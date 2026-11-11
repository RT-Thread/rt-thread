/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32f20x_misc.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file provides all the miscellaneous firmware functions .
*********************************************************************************/
#include "ch32f20x_misc.h"

#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)


/******************************************************************************************
* Function Name  : NVIC_PriorityGroupConfig
* Description    : Configures the priority grouping: pre-emption priority and subpriority. 
* Input          : NVIC_PriorityGroup: specifies the priority grouping bits length.
*                    NVIC_PriorityGroup_0: 0 bits for pre-emption priority
*                                          4 bits for subpriority
*										 NVIC_PriorityGroup_1: 1 bits for pre-emption priority	
*                                          3 bits for subpriority
*                    NVIC_PriorityGroup_2: 2 bits for pre-emption priority
*                                          2 bits for subpriority
*                    NVIC_PriorityGroup_3: 3 bits for pre-emption priority
*                                          1 bits for subpriority
*                    NVIC_PriorityGroup_4: 4 bits for pre-emption priority
*                                          0 bits for subpriority                        
* Return         : None
*******************************************************************************************/
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
  SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/******************************************************************************************
* Function Name  : NVIC_Init
* Description    : Initializes the NVIC peripheral according to the specified parameters in 
*                  the NVIC_InitStruct. 
* Input          : NVIC_InitStruct: pointer to a NVIC_InitTypeDef structure that contains the
*                                   configuration information for the specified NVIC peripheral.                 
* Return         : None
*******************************************************************************************/
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
  uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
    
  if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
  {
    /* Compute the Corresponding IRQ Priority */    
    tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |=  NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
    tmppriority = tmppriority << 0x04;
        
    NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;
    
    /* Enable the Selected IRQ Channels */
    NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* Disable the Selected IRQ Channels */
    NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

/******************************************************************************************
* Function Name  : NVIC_SetVectorTable
* Description    : Sets the vector table location and Offset. 
* Input          : NVIC_VectTab: specifies if the vector table is in RAM or FLASH memory.The
*                                value can be NVIC_VectTab_RAM or NVIC_VectTab_FLASH.
*                  Offset      : Vector Table base offset field. This value must be a multiple 
*                                of 0x200.
* Return         : None
*******************************************************************************************/
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/******************************************************************************************
* Function Name  : NVIC_SystemLPConfig
* Description    : Selects the condition for the system to enter low power mode.
* Input          : LowPowerMode: Specifies the new mode for the system to enter low power mode.
*                      NVIC_LP_SEVONPEND   
*                      NVIC_LP_SLEEPDEEP
*                      NVIC_LP_SLEEPONEXIT
*                  NewState    : new state of LP condition. This parameter can be: ENABLE or DISABLE. 
* Return         : None
*******************************************************************************************/
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

/******************************************************************************************
* Function Name  : SysTick_CLKSourceConfig
* Description    : Configures the SysTick clock source.
* Input          : SysTick_CLKSource: Specifies the new mode for the system to enter low power mode.
*                     ysTick_CLKSource_HCLK_Div8: AHB clock divided by 8 selected as SysTick clock source.  
*                     SysTick_CLKSource_HCLK: AHB clock selected as SysTick clock source.
* Return         : None
*******************************************************************************************/
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
  if (SysTick_CLKSource == SysTick_CLKSource_HCLK)
  {
    SysTick->CTRL |= SysTick_CLKSource_HCLK;
  }
  else
  {
    SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
  }
}


