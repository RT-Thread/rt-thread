/**
  ******************************************************************************
  * @file    lib_comp.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   COMP library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_comp.h"

extern __IO uint32_t ana_reg3_tmp;
/**
  * @brief  Comparator debounce configure.
  * @param  COMPx:
                COMP_1
                COMP_2
            Debounce:
                COMP_DEB_0
                COMP_DEB_1
                COMP_DEB_2
                COMP_DEB_3
  * @retval None
  */
void COMP_DEBConfig(uint32_t COMPx, uint32_t Debounce)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  assert_parameters(IS_COMP_DEB(Debounce));  
  
  tmp = ANA->CTRL;
  tmp &= ~(ANA_CTRL_CMP1DEB << COMPx);
  tmp |= Debounce << COMPx;
  ANA->CTRL = tmp;
}

/**
  * @brief  Comparator mode configure.
  * @param  COMPx:
                COMP_1
                COMP_2
            Mode:
                COMP_MODE_OFF    
                COMP_MODE_RISING 
                COMP_MODE_FALLING
                COMP_MODE_BOTH   
  * @retval None
  */
void COMP_ModeConfig(uint32_t COMPx, uint32_t Mode)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  assert_parameters(IS_COMP_MODE(Mode));
  
  tmp = ANA->CTRL;
  tmp &= ~(ANA_CTRL_COMP1_SEL << COMPx);
  tmp |= Mode << COMPx;
  ANA->CTRL = tmp; 
}

/**
  * @brief  Configure signal source.
  * @param  COMPx: 
  *             COMP_1
  *             COMP_2
  *         SourceSelect:
  *             COMP_SIGNALSRC_P_TO_REF
  *             COMP_SIGNALSRC_N_TO_REF
  *             COMP_SIGNALSRC_P_TO_N
  * @retval None
  */
void COMP_SignalSourceConfig(uint32_t COMPx, uint32_t SourceSelect)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  assert_parameters(IS_COMP_SIGNALSRC(SourceSelect));
  
  tmp = ANA->REG2;
  tmp &= ~(ANA_REG2_CMP1_SEL << COMPx);
  tmp |= SourceSelect << COMPx;
  
  ANA->REG2 = tmp;
}

/**
  * @brief  Comparator configure REF selection.
  * @param  COMPx: 
  *             COMP_1
  *             COMP_2
  *         REFSelect:
  *             COMP_REF_VREF
  *             COMP_REF_BGPREF
  * @retval None
  */
void COMP_REFConfig(uint32_t COMPx, uint32_t REFSelect)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  assert_parameters(IS_COMP_REF(REFSelect));
  
  tmp = ANA->REG2;
  tmp &= ~(ANA_REG2_REFSEL_CMP1 << (COMPx / 2));
  tmp |= REFSelect << (COMPx / 2);
  
  ANA->REG2 = tmp;
}

/**
  * @brief  Comparator configure Bias current selection.
  * @param  COMPx: 
  *             COMP_1
  *             COMP_2
  *         BiasSel:
  *             COMP_BIAS_20nA
  *             COMP_BIAS_100nA
  *             COMP_BIAS_500nA
  * @retval None
  */
void COMP_BiasConfig(uint32_t COMPx, uint32_t BiasSel)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  assert_parameters(IS_COMP_BIAS(BiasSel));  
  
  tmp = ANA->REG5;
  tmp &= ~(ANA_REG5_IT_CMP1 << COMPx);
  tmp |= BiasSel << COMPx;
  
  ANA->REG5 = tmp;
}

/**
  * @brief  Get comparator count value.
  * @param  COMPx:
                 COMP_1
                 COMP_2
  * @retval Comparator count value.
  */
uint32_t COMP_GetCNTValue(uint32_t COMPx)
{
  __IO uint32_t *addr;

  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  
  addr = &ANA->CMPCNT1 + (COMPx / 2);
    
  return (*addr);
}

/**
  * @brief  Clear comparator counter value.
  * @param  COMPx:
                 COMP_1
                 COMP_2
  * @retval None
  */
void COMP_ClearCNTValue(uint32_t COMPx)
{
  __IO uint32_t *addr;

  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  
  addr = &ANA->CMPCNT1 + (COMPx / 2);
  *addr = 0;
}

/**
  * @brief  comparator output enable control.
  * @param  COMPx:
                 COMP_1
                 COMP_2
            NewState: 
                ENABLE
                DISABLE
  * @retval None
  */
void COMP_Output_Cmd(uint32_t COMPx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState == ENABLE)
  {
    if (COMPx == COMP_1)
      GPIOAF->SELE |= IOE_SEL_SEL7;
    else
      PMU->IOASEL |= PMU_IOASEL_SEL6;
  }
  else
  {
    if (COMPx == COMP_1)
      GPIOAF->SELE &= ~IOE_SEL_SEL7;
    else
      PMU->IOASEL &= ~PMU_IOASEL_SEL6;  
  }
}

/**
  * @brief  Comparator enable control.
  * @param  COMPx:
                 COMP_1
                 COMP_2
            NewState: 
                ENABLE
                DISABLE
  * @retval None
  */
void COMP_Cmd(uint32_t COMPx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 

  if (COMPx == COMP_1)
  {
    if (NewState == ENABLE)
      ana_reg3_tmp |= ANA_REG3_CMP1PDN;
    else
      ana_reg3_tmp &= ~ANA_REG3_CMP1PDN;
  }
  else
  {
    if (NewState == ENABLE)
      ana_reg3_tmp |= ANA_REG3_CMP2PDN;
    else
      ana_reg3_tmp &= ~ANA_REG3_CMP2PDN;
  }
  ANA->REG3 = ana_reg3_tmp;
}

/**
  * @brief  Get comparator 1 output level
  * @param  None
  * @retval None
  */
uint8_t COMP1_GetOutputLevel(void)
{
  if (ANA->COMPOUT & ANA_COMPOUT_COMP1)
    return 1;
  else
    return 0;
}

/**
  * @brief  Get comparator 2 output level
  * @param  None
  * @retval None
  */
uint8_t COMP2_GetOutputLevel(void)
{
  if (ANA->COMPOUT & ANA_COMPOUT_COMP2)
    return 1;
  else
    return 0;
}

/**
  * @brief  Comparator interrupt enable control.
  * @param  COMPx:
  *              COMP_1
  *              COMP_2
  *         NewState: 
  *             ENABLE
  *             DISABLE
  * @retval None
  */
void COMP_INTConfig(uint32_t COMPx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  
  if (NewState == ENABLE)
  {
    ANA->INTEN |= ANA_INTEN_INTEN2 << (COMPx/2);
  }
  else
  {
    ANA->INTEN &= ~(ANA_INTEN_INTEN2 << (COMPx/2));
  }
}

/**
  * @brief  Get comparator interrupt flag status.
  * @param  COMPx:
  *              COMP_1
  *              COMP_2
  * @retval flag status
  *              0: status not set
  *              1: status set
  */
uint8_t COMP_GetINTStatus(uint32_t COMPx)
{
  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  
  if (ANA->INTSTS & (ANA_INTSTS_INTSTS2 << (COMPx/2)))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clear comparator interrupt flag.
  * @param  COMPx:
  *              COMP_1
  *              COMP_2
  * @retval None
  */
void COMP_ClearINTStatus(uint32_t COMPx)
{
  /* Check parameters */
  assert_parameters(IS_COMP(COMPx));
  
  ANA->INTSTS = ANA_INTSTS_INTSTS2 << (COMPx/2);
}

/*********************************** END OF FILE ******************************/
