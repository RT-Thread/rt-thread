/********************************** (C) COPYRIGHT  *******************************
* File Name          : ch32f20x_exti.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file provides all the EXTI firmware functions.
***************************************************************************************/
#include "ch32f20x_exti.h"

/* No interrupt selected */
#define EXTI_LINENONE    ((uint32_t)0x00000)  

/********************************************************************************
* Function Name  : EXTI_DeInit
* Description    : Deinitializes the EXTI peripheral registers to their default 
*                  reset values.
* Input          : None
* Return         : None
*********************************************************************************/	
void EXTI_DeInit(void)
{
  EXTI->INTENR = 0x00000000;
  EXTI->EVENR = 0x00000000;
  EXTI->RTENR = 0x00000000; 
  EXTI->FTENR = 0x00000000; 
  EXTI->INTFR = 0x000FFFFF;
}

/********************************************************************************
* Function Name  : EXTI_Init
* Description    : Initializes the EXTI peripheral according to the specified
*                  parameters in the EXTI_InitStruct.
* Input          : EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure
* Return         : None
*********************************************************************************/	
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  tmp = (uint32_t)EXTI_BASE;
  if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
  {
    EXTI->INTENR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->EVENR &= ~EXTI_InitStruct->EXTI_Line;
    tmp += EXTI_InitStruct->EXTI_Mode;
    *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
    EXTI->RTENR &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->FTENR &= ~EXTI_InitStruct->EXTI_Line;
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      EXTI->RTENR |= EXTI_InitStruct->EXTI_Line;
      EXTI->FTENR |= EXTI_InitStruct->EXTI_Line;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE;
      tmp += EXTI_InitStruct->EXTI_Trigger;
      *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->EXTI_Mode;
    *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
  }
}

/********************************************************************************
* Function Name  : EXTI_StructInit
* Description    : Fills each EXTI_InitStruct member with its reset value.
* Input          : EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure
* Return         : None
*********************************************************************************/	
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_Line = EXTI_LINENONE;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/********************************************************************************
* Function Name  : EXTI_GenerateSWInterrupt
* Description    : Generates a Software interrupt.
* Input          : EXTI_Line: specifies the EXTI lines to be enabled or disabled.
* Return         : None
*********************************************************************************/	
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
{
  EXTI->SWIEVR |= EXTI_Line;
}

/********************************************************************************
* Function Name  : EXTI_GetFlagStatus
* Description    : Checks whether the specified EXTI line flag is set or not.
* Input          : EXTI_Line: specifies the EXTI lines to be enabled or disabled.
* Return         : The new state of EXTI_Line (SET or RESET).
*********************************************************************************/	
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
{
  FlagStatus bitstatus = RESET;
  if ((EXTI->INTFR & EXTI_Line) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/********************************************************************************
* Function Name  : EXTI_ClearFlag
* Description    : Clears the EXTI's line pending flags.
* Input          : EXTI_Line: specifies the EXTI lines to be enabled or disabled.
* Return         : None
*********************************************************************************/	
void EXTI_ClearFlag(uint32_t EXTI_Line)
{  
  EXTI->INTFR = EXTI_Line;
}

/********************************************************************************
* Function Name  : EXTI_GetITStatus
* Description    : Checks whether the specified EXTI line is asserted or not.
* Input          : EXTI_Line: specifies the EXTI lines to be enabled or disabled.
* Return         : The new state of EXTI_Line (SET or RESET).
*********************************************************************************/	
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  
  enablestatus =  EXTI->INTENR & EXTI_Line;
  if (((EXTI->INTFR & EXTI_Line) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/********************************************************************************
* Function Name  : EXTI_ClearITPendingBit
* Description    : Clears the EXTI's line pending bits.
* Input          : EXTI_Line: specifies the EXTI lines to be enabled or disabled.
* Return         : None
*********************************************************************************/
void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{  
  EXTI->INTFR = EXTI_Line;
}

