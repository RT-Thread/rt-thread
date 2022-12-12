/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32f20x_wwdg.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file provides all the WWDG firmware functions.
**********************************************************************************/
#include "ch32f20x_wwdg.h"
#include "ch32f20x_rcc.h"

/* CTLR register bit mask */
#define CTLR_WDGA_Set      ((uint32_t)0x00000080)

/* CFGR register bit mask */
#define CFGR_WDGTB_Mask    ((uint32_t)0xFFFFFE7F)
#define CFGR_W_Mask        ((uint32_t)0xFFFFFF80)
#define BIT_Mask           ((uint8_t)0x7F)

/********************************************************************************
* Function Name  : WWDG_DeInit
* Description    : Deinitializes the WWDG peripheral registers to their default reset values
* Input          : None
* Return         : None
*********************************************************************************/	
void WWDG_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
}

/********************************************************************************
* Function Name  : WWDG_SetPrescaler
* Description    : Sets the WWDG Prescaler
* Input          : WWDG_Prescaler: specifies the WWDG Prescaler
*                    WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
*                    WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
*                    WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
*                    WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
* Return         : None
*********************************************************************************/	
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler)
{
  uint32_t tmpreg = 0;
  tmpreg = WWDG->CFGR & CFGR_WDGTB_Mask;
  tmpreg |= WWDG_Prescaler;
  WWDG->CFGR = tmpreg;
}

/********************************************************************************
* Function Name  : WWDG_SetWindowValue
* Description    : Sets the WWDG window value
* Input          : WindowValue: specifies the window value to be compared to the 
*                               downcounter,which must be lower than 0x80
* Return         : None
*********************************************************************************/	
void WWDG_SetWindowValue(uint8_t WindowValue)
{
  __IO uint32_t tmpreg = 0;

  tmpreg = WWDG->CFGR & CFGR_W_Mask;

  tmpreg |= WindowValue & (uint32_t) BIT_Mask;

  WWDG->CFGR = tmpreg;
}

/********************************************************************************
* Function Name  : WWDG_EnableIT
* Description    : Enables the WWDG Early Wakeup interrupt(EWI)
* Input          : None
* Return         : None
*********************************************************************************/
void WWDG_EnableIT(void)
{
	WWDG->CFGR |= (1<<9);
}

/********************************************************************************
* Function Name  : WWDG_SetCounter
* Description    : Sets the WWDG counter value
* Input          : Counter: specifies the watchdog counter value,which must be a 
*                           number between 0x40 and 0x7F
* Return         : None
*********************************************************************************/
void WWDG_SetCounter(uint8_t Counter)
{
  WWDG->CTLR = Counter & BIT_Mask;
}


/********************************************************************************
* Function Name  : WWDG_Enable
* Description    : Enables WWDG and load the counter value
* Input          : Counter: specifies the watchdog counter value,which must be a 
*                           number between 0x40 and 0x7F
* Return         : None
*********************************************************************************/
void WWDG_Enable(uint8_t Counter)
{
  WWDG->CTLR = CTLR_WDGA_Set | Counter;
}

/********************************************************************************
* Function Name  : WWDG_GetFlagStatus
* Description    : Checks whether the Early Wakeup interrupt flag is set or not
* Input          : None
* Return         : The new state of the Early Wakeup interrupt flag (SET or RESET)
*********************************************************************************/
FlagStatus WWDG_GetFlagStatus(void)
{
  return (FlagStatus)(WWDG->STATR);
}

/********************************************************************************
* Function Name  : WWDG_ClearFlag
* Description    : Clears Early Wakeup interrupt flag
* Input          : None
* Return         : None
*********************************************************************************/
void WWDG_ClearFlag(void)
{
  WWDG->STATR = (uint32_t)RESET;
}
