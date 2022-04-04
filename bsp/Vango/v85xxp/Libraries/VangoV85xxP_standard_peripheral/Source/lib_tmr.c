/**
  ******************************************************************************
  * @file    lib_tmr.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   Timer library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_tmr.h"

#define TMR_CTRL_RSTValue       (0UL)
#define TMR_VALUE_RSTValue      (0UL)
#define TMR_RELOAD_RSTValue     (0UL)

/**
  * @brief  Initializes the timer peripheral registers to their default reset values.
  * @param  TMRx: 
                TMR0 ~ TMR3
  * @retval None
  */
void TMR_DeInit(TMR_Type *TMRx)
{
  /* Check parameters */
  assert_parameters(IS_TMR_ALL_INSTANCE(TMRx));
  
  /* Disable timer */
  TMRx->CTRL &= ~TMR_CTRL_EN;
  /* clear interrupt status */
  TMRx->INTSTS = TMR_INTSTS_INTSTS;
  /* write default reset values */
  TMRx->CTRL   = TMR_CTRL_RSTValue;
  TMRx->RELOAD = TMR_RELOAD_RSTValue;
  TMRx->VALUE  =  TMR_VALUE_RSTValue;   
}

/**
  * @brief  Initializes timer.
  * @param  TMRx: 
                TMR0 ~ TMR3
            InitStruct: Timer configuration.
                ClockSource:
                    TMR_CLKSRC_INTERNAL
                    TMR_CLKSRC_EXTERNAL
                EXTGT:
                    TMR_EXTGT_DISABLE
                    TMR_EXTGT_ENABLE
                Period: the auto-reload value
  * @retval None
  */
void TMR_Init(TMR_Type *TMRx, TMR_InitType *InitStruct)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_TMR_ALL_INSTANCE(TMRx)); 
  assert_parameters(IS_TMR_CLKSRC(InitStruct->ClockSource));
  assert_parameters(IS_TMR_EXTGT(InitStruct->EXTGT));
 
  tmp = TMRx->CTRL;
  tmp &= ~(TMR_CTRL_EXTCLK|TMR_CTRL_EXTEN);
  tmp |= (InitStruct->ClockSource|InitStruct->EXTGT);
  TMRx->CTRL = tmp;
  TMRx->VALUE = InitStruct->Period;
  TMRx->RELOAD = InitStruct->Period;
}

/**
  * @brief  Fills each TMR_InitType member with its default value.
  * @param  InitStruct: pointer to an TMR_InitType structure which will be initialized.
  * @retval None
  */
void TMR_StructInit(TMR_InitType *InitStruct)
{
  /*--------------- Reset TMR init structure parameters values ---------------*/
  /* Initialize the ClockSource member */
  InitStruct->ClockSource = TMR_CLKSRC_INTERNAL;
  /* Initialize the EXTGT member */
  InitStruct->EXTGT = TMR_EXTGT_DISABLE;  
  /* Initialize the Period member */
  InitStruct->Period = 0;   
}

/**
  * @brief  Enables or disables timer interrupt.
  * @param  TMRx:
                TMR0~TMR3
            NewState: 
                ENABLE
                DISABLE
  * @retval None
  */
void TMR_INTConfig(TMR_Type *TMRx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_TMR_ALL_INSTANCE(TMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    TMRx->CTRL |= TMR_CTRL_INTEN;
  }
  else
  {
    TMRx->CTRL &= ~TMR_CTRL_INTEN;
  }
}

/**
  * @brief  Gets timer interrupt status.
  * @param  TMRx:
                TMR0~TMR3
  * @retval Interrupt status.
  */
uint8_t TMR_GetINTStatus(TMR_Type *TMRx)
{
  /* Check parameters */
  assert_parameters(IS_TMR_ALL_INSTANCE(TMRx)); 
  
  if (TMRx->INTSTS & TMR_INTSTS_INTSTS)
    return 1;
  else
    return 0;
}

/**
  * @brief  Clears timer interrupt status bit.
  * @param  TMRx:
                TMR0~TMR3
  * @retval None.
  */
void TMR_ClearINTStatus(TMR_Type *TMRx)
{
  /* Check parameters */
  assert_parameters(IS_TMR_ALL_INSTANCE(TMRx));
  
  TMRx->INTSTS = TMR_INTSTS_INTSTS;
}

/**
  * @brief  Enables or disables timer.
  * @param  TMRx:
                TMR0~TMR3
            NewState: 
                ENABLE
                DISABLE
  * @retval None
  */
void TMR_Cmd(TMR_Type *TMRx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_TMR_ALL_INSTANCE(TMRx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
    TMRx->CTRL |= TMR_CTRL_EN;
  else
    TMRx->CTRL &= ~TMR_CTRL_EN;
}

/**
  * @brief  Gets timer current value.
  * @param  TMRx:
                TMR0~TMR3
  * @retval timer value.
  */
uint32_t TMR_GetCurrentValue(TMR_Type *TMRx)
{
  /* Check parameters */
  assert_parameters(IS_TMR_ALL_INSTANCE(TMRx));
  
  return (TMRx->VALUE);
}

/*********************************** END OF FILE ******************************/
