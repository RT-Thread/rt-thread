/**
  ******************************************************************************
  * @file    lib_adc_tiny.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   ADC_TINY library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_adc_tiny.h"

#define ANA_REGF_RSTValue (0U)

/**
  * @brief  Initializes the Tiny ADC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void TADC_DeInit(void)
{
  ANA->REGF = ANA_REGF_RSTValue;
  ANA->INTSTS = ANA_INTSTS_INTSTS13;
  ANA->MISC_A &= ~ANA_MISC_TADCTH;
}

/**
  * @brief  Fills each TADC_InitStruct member with its default value.
  * @param  TADC_InitStruct: pointer to an TADCInitType structure which will be initialized.
  * @retval None
  */
void TADC_StructInit(TADCInitType* TADC_InitStruct)
{
  /*--------------- Reset TADC init structure parameters values ---------------*/
  /* Initialize the SignalSel member */
  TADC_InitStruct->SignalSel = ADCTINY_SIGNALSEL_IOE6;
  /* Initialize the ADTREF1 member */
  TADC_InitStruct->ADTREF1 = ADCTINY_REF1_0_9;  
  /* Initialize the ADTREF2 member */
  TADC_InitStruct->ADTREF2 = ADCTINY_REF2_1_8;  
  /* Initialize the ADTREF3 member */
  TADC_InitStruct->ADTREF3 = ADCTINY_REF3_2_7;  
}

/**
  * @brief  Tiny ADC initialization.
  * @param  TADC_InitStruct
                SelADT:
                    ADCTINY_SIGNALSEL_IOE6
                    ADCTINY_SIGNALSEL_IOE7
                ADTREF1:
                    ADCTINY_REF1_0_9
                    ADCTINY_REF1_0_7
                ADTREF2:
                    ADCTINY_REF2_1_8
                    ADCTINY_REF2_1_6                
                ADTREF3:
                    ADCTINY_REF3_2_7
                    ADCTINY_REF3_2_5                  
  * @retval None
  */
void TADC_Init(TADCInitType* TADC_InitStruct)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ADCTINY_SELADT(TADC_InitStruct->SignalSel));
  assert_parameters(IS_ADCTINY_ADTREF1(TADC_InitStruct->ADTREF1));
  assert_parameters(IS_ADCTINY_ADTREF2(TADC_InitStruct->ADTREF2));
  assert_parameters(IS_ADCTINY_ADTREF3(TADC_InitStruct->ADTREF3));
  
  tmp = ANA->REGF;
  tmp &= ~(ANA_REGF_SELADT     \
           |ANA_REGF_ADTREF1SEL\
           |ANA_REGF_ADTREF2SEL\
           |ANA_REGF_ADTREF3SEL);
  tmp |= (TADC_InitStruct->SignalSel \
          |TADC_InitStruct->ADTREF1\
          |TADC_InitStruct->ADTREF2\
          |TADC_InitStruct->ADTREF3);
  ANA->REGF = tmp;
}

/**
  * @brief  TADC enable control.
  * @param  NewState
                ENABLE
                DISABLE
  * @retval None
  */
void TADC_Cmd(uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  if (NewState == ENABLE)
    ANA->REGF |= ANA_REGF_PDNADT;
  else
    ANA->REGF &= ~ANA_REGF_PDNADT;
}

/**
  * @brief  Get TADC output.
  * @param  None
  * @retval Output of Tiny ADC(0 ~ 3).
  */
uint8_t TADC_GetOutput(void)
{
  return ((ANA->COMPOUT & ANA_COMPOUT_TADCO) >> ANA_COMPOUT_TADCO_Pos);
}

/**
  * @brief  Configure Tiny ADC interrupt threshold.
  * @param  THSel:
                ADCTINY_THSEL_0
                ADCTINY_THSEL_1
                ADCTINY_THSEL_2
                ADCTINY_THSEL_3
  * @retval None.
  */
void TADC_IntTHConfig(uint32_t THSel)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ADCTINY_THSEL(THSel)); 
  
  tmp = ANA->MISC_A;
  tmp &= ~ANA_MISC_TADCTH;
  tmp |= THSel;
  ANA->MISC_A = tmp;
}

/**
  * @brief  TADC interrupt enable control.
  * @param  NewState
                ENABLE
                DISABLE
  * @retval None
  */
void TADC_INTConfig(uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  
  if (NewState == ENABLE)
    ANA->INTEN |= ANA_INTEN_INTEN13;
  else
    ANA->INTEN &= ~ANA_INTEN_INTEN13;
}

/**
  * @brief  Get Tiny ADC interrupt status.
  * @param  None
  * @retval Interrupt status.
  */
uint8_t TADC_GetINTStatus(void)
{
  if (ANA->INTSTS & ANA_INTSTS_INTSTS13)
    return 1;
  else
    return 0;
}
          
/**
  * @brief  Clear Tiny ADC interrupt status.
  * @param  None
  * @retval None
  */
void TADC_ClearINTStatus(void)
{
  ANA->INTSTS = ANA_INTSTS_INTSTS13;
}

/*********************************** END OF FILE ******************************/
