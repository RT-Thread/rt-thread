/**
  ******************************************************************************
  * @file    lib_ana.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   Analog library.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
    
/* Includes ------------------------------------------------------------------*/
#include "lib_ana.h"

/**
  * @brief  Gets analog status.
  * @param  StatusMask:
                ANA_STATUS_AVCCLV
                ANA_STATUS_VDCINDROP
                ANA_STATUS_VDDALARM  
                ANA_STATUS_COMP2   
                ANA_STATUS_COMP1   
                ANA_STATUS_LOCKL   
                ANA_STATUS_LOCKH   
  * @retval Analog status
  */
uint8_t ANA_GetStatus(uint32_t StatusMask)
{
  /* Check parameters */
  assert_parameters(IS_ANA_STATUS(StatusMask));  
  
  if (ANA->CMPOUT & StatusMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Gets analog interrupt status.
  * @param  IntMask:
                ANA_INT_UPPER_TH3
                ANA_INT_LOWER_TH3
                ANA_INT_UPPER_TH2
                ANA_INT_LOWER_TH2
                ANA_INT_UPPER_TH1
                ANA_INT_LOWER_TH1
                ANA_INT_UPPER_TH0
                ANA_INT_LOWER_TH0
                ANA_INT_TADC_OVER
                ANA_INT_REGERR
                ANA_INT_SLPFAIL_VDCIN
                ANA_INT_AVCCLV
                ANA_INT_VDCINDROP
                ANA_INT_VDDALARM 
                ANA_INT_COMP2  
                ANA_INT_COMP1  
                ANA_INT_ADCA   
                ANA_INT_ADCM  
  * @retval interrupt status.
  */
uint8_t ANA_GetINTStatus(uint32_t IntMask)
{
  /* Check parameters */
  assert_parameters(IS_ANA_INTSTSR(IntMask));    
  
  if (ANA->INTSTS&IntMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clears analog interrupt status.
  * @param  IntMask:status to clear, can use the '|' operator.
                ANA_INT_UPPER_TH3
                ANA_INT_LOWER_TH3
                ANA_INT_UPPER_TH2
                ANA_INT_LOWER_TH2
                ANA_INT_UPPER_TH1
                ANA_INT_LOWER_TH1
                ANA_INT_UPPER_TH0
                ANA_INT_LOWER_TH0
                ANA_INT_TADC_OVER
                ANA_INT_REGERR
                ANA_INT_SLPFAIL_VDCIN
                ANA_INT_AVCCLV
                ANA_INT_VDCINDROP
                ANA_INT_VDDALARM 
                ANA_INT_COMP2  
                ANA_INT_COMP1  
                ANA_INT_ADCA   
                ANA_INT_ADCM   
  * @retval None
  */
void ANA_ClearINTStatus(uint32_t IntMask)
{
  /* Check parameters */
  assert_parameters(IS_ANA_INTSTSC(IntMask));   
  
  ANA->INTSTS = IntMask;
}

/**
  * @brief  Enables or disables analog interrupt.
  * @param  IntMask:status to clear, can use the '|' operator.
                ANA_INT_UPPER_TH3
                ANA_INT_LOWER_TH3
                ANA_INT_UPPER_TH2
                ANA_INT_LOWER_TH2
                ANA_INT_UPPER_TH1
                ANA_INT_LOWER_TH1
                ANA_INT_UPPER_TH0
                ANA_INT_LOWER_TH0
                ANA_INT_TADC_OVER
                ANA_INT_REGERR
                ANA_INT_SLPFAIL_VDCIN
                ANA_INT_AVCCLV
                ANA_INT_VDCINDROP
                ANA_INT_VDDALARM 
                ANA_INT_COMP2  
                ANA_INT_COMP1  
                ANA_INT_ADCA   
                ANA_INT_ADCM 
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void ANA_INTConfig(uint32_t IntMask, uint32_t NewState)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ANA_INT(IntMask)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
    
  tmp = ANA->INTEN;
  if (NewState == ENABLE)
  {
    tmp |= IntMask;
  }
  else
  {
    tmp &= ~IntMask;
  }
  ANA->INTEN = tmp;
}

/*********************************** END OF FILE ******************************/
