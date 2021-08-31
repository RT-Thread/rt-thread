/***************COPYRIGHT(C)  2019 WCH. A11 rights reserved*********************
* File Name          : ch32f10x_iwdg.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2019/10/15
* Description        : This file provides all the IWDG firmware functions.
*******************************************************************************/ 
#include "ch32f10x_iwdg.h"
  
/* CTLR register bit mask */
#define CTLR_KEY_Reload    ((uint16_t)0xAAAA)
#define CTLR_KEY_Enable    ((uint16_t)0xCCCC)

/*******************************************************************************
* Function Name  : IWDG_WriteAccessCmd
* Description    : Enables or disables write access to IWDG_PR and IWDG_RLR registers.
* Input          : WDG_WriteAccess: new state of write access to IWDG_PR and 
*      IWDG_RLR registers.
*                    IWDG_WriteAccess_Enable: Enable write access to IWDG_PR and
*      IWDG_RLR registers.
*                    IWDG_WriteAccess_Disable: Disable write access to IWDG_PR 
*      and IWDG_RLR registers.
* Return         : None
*******************************************************************************/
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess)
{
  IWDG->CTLR = IWDG_WriteAccess;
}

/*******************************************************************************
* Function Name  : IWDG_SetPrescaler
* Description    : Sets IWDG Prescaler value.
* Input          : IWDG_Prescaler: specifies the IWDG Prescaler value.
*                    IWDG_Prescaler_4: IWDG prescaler set to 4.
*                    IWDG_Prescaler_8: IWDG prescaler set to 8.
*                    IWDG_Prescaler_16: IWDG prescaler set to 16.
*                    IWDG_Prescaler_32: IWDG prescaler set to 32.
*                    IWDG_Prescaler_64: IWDG prescaler set to 64.
*                    IWDG_Prescaler_128: IWDG prescaler set to 128.
*                    IWDG_Prescaler_256: IWDG prescaler set to 256.
* Return         : None
*******************************************************************************/
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler)
{
  IWDG->PSCR = IWDG_Prescaler;
}

/*******************************************************************************
* Function Name  : IWDG_SetReload
* Description    : Sets IWDG Reload value.
* Input          : Reload: specifies the IWDG Reload value.
*                    This parameter must be a number between 0 and 0x0FFF.
* Return         : None
*******************************************************************************/
void IWDG_SetReload(uint16_t Reload)
{
  IWDG->RLDR = Reload;
}

/*******************************************************************************
* Function Name  : IWDG_ReloadCounter
* Description    : Reloads IWDG counter with value defined in the reload register.
* Input          : None
* Return         : None
*******************************************************************************/
void IWDG_ReloadCounter(void)
{
  IWDG->CTLR = CTLR_KEY_Reload;
}

/*******************************************************************************
* Function Name  : IWDG_Enable
* Description    : Enables IWDG (write access to IWDG_PR and IWDG_RLR registers disabled).
* Input          : None
* Return         : None
*******************************************************************************/
void IWDG_Enable(void)
{
  IWDG->CTLR = CTLR_KEY_Enable;
}

/*******************************************************************************
* Function Name  : IWDG_GetFlagStatus
* Description    : Checks whether the specified IWDG flag is set or not.
* Input          : IWDG_FLAG: specifies the flag to check.
*                    IWDG_FLAG_PVU: Prescaler Value Update on going.
*                    IWDG_FLAG_RVU: Reload Value Update on going.
* Return         : FlagStatus: SET or RESET.
*******************************************************************************/
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG)
{
  FlagStatus bitstatus = RESET;

  if ((IWDG->STATR & IWDG_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}





