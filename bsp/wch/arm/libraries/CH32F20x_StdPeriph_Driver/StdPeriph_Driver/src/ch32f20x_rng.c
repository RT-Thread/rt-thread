/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32f20x_rng.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file provides all the RNG firmware functions.
********************************************************************************/
#include "ch32f20x_rng.h"
#include "ch32f20x_rcc.h"

/*******************************************************************************
* Function Name  : RNG_Cmd
* Description    : Enables or disables the RNG peripheral.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void RNG_Cmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RNG->CR |= RNG_CR_RNGEN;
  }
  else
  {
    RNG->CR &= ~RNG_CR_RNGEN;
  }
}

/*******************************************************************************
* Function Name  : RNG_GetRandomNumber
* Description    : Returns a 32-bit random number.
* Input          : None
* Return         : 32-bit random number.
*******************************************************************************/
uint32_t RNG_GetRandomNumber(void)
{
  return RNG->DR;
}

/*******************************************************************************
* Function Name  : RNG_ITConfig
* Description    : Enables or disables the RNG interrupt.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void RNG_ITConfig(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RNG->CR |= RNG_CR_IE;
  }
  else
  {
    RNG->CR &= ~RNG_CR_IE;
  }
}

/*******************************************************************************
* Function Name  : RNG_GetFlagStatus
* Description    : Checks whether the specified RNG flag is set or not.
* Input          : RNG_FLAG: specifies the RNG flag to check.
  *                  RNG_FLAG_DRDY: Data Ready flag.
  *                  RNG_FLAG_CECS: Clock Error Current flag.
  *                  RNG_FLAG_SECS: Seed Error Current flag.
* Return         : bitstatus£ºSET or RESET.
*******************************************************************************/
FlagStatus RNG_GetFlagStatus(uint8_t RNG_FLAG)
{
  FlagStatus bitstatus = RESET;

  if ((RNG->SR & RNG_FLAG) != (uint8_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return  bitstatus;
}

/*******************************************************************************
* Function Name  : RNG_ClearFlag
* Description    : Clears the RNG flags.
* Input          : RNG_FLAG: specifies the flag to clear.
*                    RNG_FLAG_CECS: Clock Error Current flag.
*                    RNG_FLAG_SECS: Seed Error Current flag.
* Return         : None
*******************************************************************************/
void RNG_ClearFlag(uint8_t RNG_FLAG)
{
  RNG->SR = ~(uint32_t)(((uint32_t)RNG_FLAG) << 4);
}

/*******************************************************************************
* Function Name  : RNG_GetFlagStatus
* Description    : Checks whether the specified RNG interrupt has occurred or not.
* Input          : RNG_IT: specifies the RNG interrupt source to check.
*                    RNG_IT_CEI: Clock Error Interrupt.
*                    RNG_IT_SEI: Seed Error Interrupt.
* Return         : bitstatus£ºSET or RESET.
*******************************************************************************/
ITStatus RNG_GetITStatus(uint8_t RNG_IT)
{
  ITStatus bitstatus = RESET;

  if ((RNG->SR & RNG_IT) != (uint8_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/*******************************************************************************
* Function Name  : RNG_ClearITPendingBit
* Description    : Clears the RNG interrupt pending bit(s).
* Input          : RNG_IT: specifies the RNG interrupt pending bit(s) to clear.
*                    RNG_IT_CEI: Clock Error Interrupt.
*                    RNG_IT_SEI: Seed Error Interrupt.
* Return         : None
*******************************************************************************/
void RNG_ClearITPendingBit(uint8_t RNG_IT)
{
  RNG->SR = (uint8_t)~RNG_IT;
}

