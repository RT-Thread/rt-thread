/**
  ******************************************************************************
  * @file    lib_cmp.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   CMP library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_cmp.h"

/* CMP1 reset values */
#define CMP1_REG2_Msk            (0x13UL)
#define CMP1_REG3_Msk            (0x02UL)
#define CMP1_REG5_Msk            (0x03UL)
#define CMP1_REGF_Msk            (0x01UL)
#define CMP1_CTRL_Msk            (0x300003UL)
#define CMP1_INTSTS_Msk          (0x04UL)
#define CMP1_INTEN_Msk           (0x04UL)
#define CMP1_THR_Msk             (0xFFFFUL)
#define CMP1_CTL_Msk             (0x300FFUL)
/* CMP2 reset values */
#define CMP2_REG2_Msk            (0x2CUL)
#define CMP2_REG3_Msk            (0x04UL)
#define CMP2_REG5_Msk            (0x0CUL)
#define CMP2_REGF_Msk            (0x02UL)
#define CMP2_CTRL_Msk            (0xC0000CUL)
#define CMP2_INTSTS_Msk          (0x08UL)
#define CMP2_INTEN_Msk           (0x08UL)
#define CMP2_THR_Msk             (0xFFFF0000UL)
#define CMP2_CTL_Msk             (0x30FF00UL)

/**
  * @brief  Initializes the Comparator peripheral registers to their default reset values.
  * @param  CMPx:
                CMP_1
                CMP_2
  * @retval None
  */
void CMP_DeInit(uint32_t CMPx)
{
  /* Check parameters */
  assert_parameters(IS_CMP(CMPx));

  if (CMPx == CMP_1)
  {
    ANA->REG2 &= ~CMP1_REG2_Msk;
    ANA->REG3 &= ~CMP1_REG3_Msk;
    ANA->REG5 &= ~CMP1_REG5_Msk;
    ANA->REGF &= ~CMP1_REGF_Msk;
    ANA->CTRL &= ~CMP1_CTRL_Msk;
    ANA->INTSTS = CMP1_INTSTS_Msk;
    ANA->INTEN &= ~CMP1_INTEN_Msk;
    ANA->CMPTHR &= ~CMP1_THR_Msk;
    ANA->CMPCTL &= ~CMP1_CTL_Msk;
    ANA->CMPCNT1 = 0;
  }
  else
  {
    ANA->REG2 &= ~CMP2_REG2_Msk;
    ANA->REG3 &= ~CMP2_REG3_Msk;
    ANA->REG5 &= ~CMP2_REG5_Msk;
    ANA->REGF &= ~CMP2_REGF_Msk;
    ANA->CTRL &= ~CMP2_CTRL_Msk;
    ANA->INTSTS = CMP2_INTSTS_Msk;
    ANA->INTEN &= ~CMP2_INTEN_Msk;
    ANA->CMPTHR &= ~CMP2_THR_Msk;
    ANA->CMPCTL &= ~CMP2_CTL_Msk;
    ANA->CMPCNT2 = 0;
  }
}

/**
  * @brief  Initializes comparator.
  * @param  CMPx:
                CMP_1
                CMP_2
            InitStruct: Comparator configuration
                DebSel:
                    CMP_DEB_NONE
                    CMP_DEB_RTCCLK_2
                    CMP_DEB_RTCCLK_3
                    CMP_DEB_RTCCLK_4
                SignalSourceSel:
                    CMP_SIGNALSRC_PPIN_TO_VREF
                    CMP_SIGNALSRC_PPIN_TO_BGPREF
                    CMP_SIGNALSRC_PBAT_TO_VREF
                    CMP_SIGNALSRC_PBAT_TO_BGPREF
                    CMP_SIGNALSRC_NPIN_TO_VREF
                    CMP_SIGNALSRC_NPIN_TO_BGPREF
                    CMP_SIGNALSRC_PPIN_TO_NPIN
                    CMP_SIGNALSRC_PBAT_TO_NPIN
                BiasSel:
                    CMP_BIAS_20nA
                    CMP_BIAS_100nA
                    CMP_BIAS_500nA
  * @retval None
  */
void CMP_Init(uint32_t CMPx, CMP_TypeDef *InitStruct)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_CMP(CMPx));
  assert_parameters(IS_CMP_DEB(InitStruct->DebSel));
  assert_parameters(IS_CMP_SIGNALSRC(InitStruct->SignalSourceSel));
  assert_parameters(IS_CMP_BIAS(InitStruct->BiasSel));  

  /* CMP1 Configure */
  if (CMPx == CMP_1)
  {
    tmp = ANA->CTRL;
    tmp &= ~ANA_CTRL_CMP1DEB;
    tmp |= (InitStruct->DebSel << ANA_CTRL_CMP1DEB_Pos);
    ANA->CTRL = tmp;

    tmp = ANA->REG5;
    tmp &= ~ANA_REG5_CMP1IT;
    tmp |= (InitStruct->BiasSel << ANA_REG5_CMP1IT_Pos);
    ANA->REG5 = tmp;

    ANA->REG2 &= ~(ANA_REG2_CMP1SEL|ANA_REG2_CMP1REFSEL);
    ANA->REGF &= ~ANA_REGF_BAT1DETEN;
    switch(InitStruct->SignalSourceSel)
    {
      case CMP_SIGNALSRC_PPIN_TO_VREF:   
          break;
      case CMP_SIGNALSRC_PPIN_TO_BGPREF: ANA->REG2 |= ANA_REG2_CMP1REFSEL;
          break;
      case CMP_SIGNALSRC_PBAT_TO_VREF:   ANA->REGF |= ANA_REGF_BAT1DETEN;
          break;
      case CMP_SIGNALSRC_PBAT_TO_BGPREF: ANA->REG2 |= ANA_REG2_CMP1REFSEL;
                                         ANA->REGF |= ANA_REGF_BAT1DETEN;
          break;
      case CMP_SIGNALSRC_NPIN_TO_VREF:   ANA->REG2 |= ANA_REG2_CMP1SEL_1;
          break;
      case CMP_SIGNALSRC_NPIN_TO_BGPREF: ANA->REG2 |= (ANA_REG2_CMP1SEL_1|ANA_REG2_CMP1REFSEL);
          break;
      case CMP_SIGNALSRC_PPIN_TO_NPIN:   ANA->REG2 |= ANA_REG2_CMP1SEL_3;
          break;
      case CMP_SIGNALSRC_PBAT_TO_NPIN:   ANA->REG2 |= ANA_REG2_CMP1SEL_3;
                                         ANA->REGF |= ANA_REGF_BAT1DETEN;
          break;
      default:
          break;
    }
  }
  /* CMP2 Configure */
  else
  {
    tmp = ANA->CTRL;
    tmp &= ~ANA_CTRL_CMP2DEB;
    tmp |= (InitStruct->DebSel << ANA_CTRL_CMP2DEB_Pos);
    ANA->CTRL = tmp;

    tmp = ANA->REG5;
    tmp &= ~ANA_REG5_CMP2IT;
    tmp |= (InitStruct->BiasSel << ANA_REG5_CMP2IT_Pos);
    ANA->REG5 = tmp;

    ANA->REG2 &= ~(ANA_REG2_CMP2SEL|ANA_REG2_CMP2REFSEL);
    ANA->REGF &= ~ANA_REGF_BATRTCDETEN;
    switch(InitStruct->SignalSourceSel)
    {
      case CMP_SIGNALSRC_PPIN_TO_VREF:   
          break;
      case CMP_SIGNALSRC_PPIN_TO_BGPREF: ANA->REG2 |= ANA_REG2_CMP2REFSEL;
          break;
      case CMP_SIGNALSRC_PBAT_TO_VREF:   ANA->REGF |= ANA_REGF_BATRTCDETEN;
          break;
      case CMP_SIGNALSRC_PBAT_TO_BGPREF: ANA->REG2 |= ANA_REG2_CMP2REFSEL;
                                         ANA->REGF |= ANA_REGF_BATRTCDETEN;
          break;
      case CMP_SIGNALSRC_NPIN_TO_VREF:   ANA->REG2 |= ANA_REG2_CMP2SEL_1;
          break;
      case CMP_SIGNALSRC_NPIN_TO_BGPREF: ANA->REG2 |= (ANA_REG2_CMP2SEL_1|ANA_REG2_CMP2REFSEL);
          break;
      case CMP_SIGNALSRC_PPIN_TO_NPIN:   ANA->REG2 |= ANA_REG2_CMP2SEL_3;
          break;
      case CMP_SIGNALSRC_PBAT_TO_NPIN:   ANA->REG2 |= ANA_REG2_CMP2SEL_3;
                                         ANA->REGF |= ANA_REGF_BATRTCDETEN;
          break;
      default:
          break;
    }
  }
}

/**
  * @brief  Fills each CMP_TypeDef member with its default value.
  * @param  InitStruct: pointer to an CMP_TypeDef structure which will be initialized.
  * @retval None
  */
void CMP_StructInit(CMP_TypeDef *InitStruct)
{
  InitStruct->DebSel = CMP_DEB_NONE;
  InitStruct->SignalSourceSel = CMP_SIGNALSRC_PPIN_TO_VREF;
  InitStruct->BiasSel = CMP_BIAS_20nA;
}

/**
  * @brief  Initializes comparator Count.
  * @param  CMPx:
                CMP_1
                CMP_2
            InitStruct: Comparator configuration
                ModeSel:
                    CMP_MODE_OFF
                    CMP_MODE_RISING
                    CMP_MODE_FALLING
                    CMP_MODE_BOTH
                CheckPeriod:
                    CMP_PERIOD_30US
                    CMP_PERIOD_7_8125MS
                    CMP_PERIOD_125MS
                    CMP_PERIOD_250MS
                    CMP_PERIOD_500MS
                CheckNum:
                    CMP_CHKNUM_1~CMP_CHKNUM_16
  * @retval None
  */
void CMP_CountInit(uint32_t CMPx, CMP_CountTypeDef *InitStruct)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_CMP(CMPx));
  assert_parameters(IS_CMP_MODE(InitStruct->ModeSel));
  assert_parameters(IS_CMP_CHECKPERIOD(InitStruct->CheckPeriod));
  assert_parameters(IS_CMP_CHKNUM(InitStruct->CheckNum));

  /* CMP1 Configure */
  if (CMPx == CMP_1)
  {
    /*           Configure ModeSel            */
    tmp = ANA->CTRL;
    tmp &= ~ANA_CTRL_CMP1SEL;
    tmp |= (InitStruct->ModeSel << ANA_CTRL_CMP1SEL_Pos);
    ANA->CTRL = tmp;

    /*           Configure CheckPeriod/CheckNum            */
    tmp = ANA->CMPCTL;
    tmp &= ~(ANA_CMPCTL_CMP1_CHK_FRQ|ANA_CMPCTL_CMP1_CHK_NUM);
    tmp |= ((InitStruct->CheckPeriod << ANA_CMPCTL_CMP1_CHK_FRQ_Pos) | \
            (InitStruct->CheckNum << ANA_CMPCTL_CMP1_CHK_NUM_Pos));
    ANA->CMPCTL = tmp;
  }
  /* CMP2 Configure */
  else
  {
    /*           Configure ModeSel            */
    tmp = ANA->CTRL;
    tmp &= ~ANA_CTRL_CMP2SEL;
    tmp |= (InitStruct->ModeSel << ANA_CTRL_CMP2SEL_Pos);
    ANA->CTRL = tmp;

    /*           Configure CheckPeriod/CheckNum            */
    tmp = ANA->CMPCTL;
    tmp &= ~(ANA_CMPCTL_CMP2_CHK_FRQ|ANA_CMPCTL_CMP2_CHK_NUM);
    tmp |= ((InitStruct->CheckPeriod << ANA_CMPCTL_CMP2_CHK_FRQ_Pos) | \
            (InitStruct->CheckNum << ANA_CMPCTL_CMP2_CHK_NUM_Pos));
    ANA->CMPCTL = tmp;
  }
}

/**
  * @brief  Fill each CMP_CountTypeDef member with its default value.
  * @param  InitStruct: pointer to an CMP_CountTypeDef structure which will be initialized.
  * @retval None
  */
void CMP_CountStructInit(CMP_CountTypeDef *InitStruct)
{
  InitStruct->ModeSel = CMP_MODE_OFF;
  InitStruct->CheckPeriod = CMP_PERIOD_30US;
  InitStruct->CheckNum = CMP_CHKNUM_1;
}

/**
  * @brief  Initializes Comparator interrupt.
  * @param  CMPx:
                CMP_1
                CMP_2
            InitStruct: Comparator configuration
                INTNumSel:
                    CMP_INTNUM_EVERY
                    CMP_INTNUM_1
                SubSel:
                     CMP_COUNT_NOSUB
                     CMP_COUNT_SUB
                THRNum:0~65535
  * @retval None
  */
void CMP_INTInit(uint32_t CMPx, CMP_INTTypeDef *InitStruct)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_CMP(CMPx)); 
  assert_parameters(IS_CMP_INTNUM(InitStruct->INTNumSel));
  assert_parameters(IS_CMP_COUNT(InitStruct->SubSel));
  assert_parameters(IS_CMP_THRNUM(InitStruct->THRNum));

  /* CMP1 Configure */
  if (CMPx == CMP_1)
  {
    /*           Configure INTNumSel/SubSel            */
    tmp = ANA->CMPCTL;
    tmp &= ~(ANA_CMPCTL_CMP1_THR_EN|ANA_CMPCTL_CMP1_INT_MASK_EN);
    tmp |= ((InitStruct->SubSel << ANA_CMPCTL_CMP1_THR_EN_Pos)       | \
            (InitStruct->INTNumSel << ANA_CMPCTL_CMP1_INT_MASK_EN_Pos));
    ANA->CMPCTL = tmp;

    /*           Configure THRNum            */
    tmp = ANA->CMPTHR;
    tmp &= ~ANA_CMPTHR_CMP1_THR;
    tmp |= (InitStruct->THRNum << ANA_CMPTHR_CMP1_THR_Pos);
    ANA->CMPTHR = tmp;
  }
  /* CMP2 Configure */
  else
  {
    /*           Configure INTNumSel/SubSel            */
    tmp = ANA->CMPCTL;
    tmp &= ~(ANA_CMPCTL_CMP2_THR_EN|ANA_CMPCTL_CMP2_INT_MASK_EN);
    tmp |= ((InitStruct->SubSel << ANA_CMPCTL_CMP2_THR_EN_Pos)       | \
            (InitStruct->INTNumSel << ANA_CMPCTL_CMP2_INT_MASK_EN_Pos));
    ANA->CMPCTL = tmp;

    /*           Configure THRNum            */
    tmp = ANA->CMPTHR;
    tmp &= ~ANA_CMPTHR_CMP2_THR;
    tmp |= (InitStruct->THRNum << ANA_CMPTHR_CMP2_THR_Pos);
    ANA->CMPTHR = tmp;
  }
}

/**
  * @brief  Fills each CMP_INTTypeDef member with its default value.
  * @param  InitStruct: pointer to an CMP_INTTypeDef structure which will be initialized.
  * @retval None
  */
void CMP_INTStructInit(CMP_INTTypeDef *InitStruct)
{
  InitStruct->INTNumSel = CMP_INTNUM_EVERY;
  InitStruct->SubSel = CMP_COUNT_NOSUB;
  InitStruct->THRNum = 0;
}

/**
  * @brief  Initializes Comparator Output IO.
  * @param  CMPx:
                CMP_1
                CMP_2
            InitStruct: Comparator configuration
                DebSel:
                    CMP_OUTPUT_DEB
                    CMP_OUTPUT_NODEB
                OutputSel:
                    ENABLE
                    DISABLE
  * @retval None
  */
void CMP_OutputInit(uint32_t CMPx, CMP_OutputTypeDef *InitStruct)
{
  /* Check parameters */
  assert_parameters(IS_CMP(CMPx));
  assert_parameters(IS_CMP_OUTPUTDEB(InitStruct->DebSel));
  assert_parameters(IS_FUNCTIONAL_STATE(InitStruct->OutputSel)); 

  /* CMP1 Configure */
  if (CMPx == CMP_1)
  {
    ANA->CMPCTL &= ~ANA_CMPCTL_CMP1_IO_NODEB;
    ANA->CMPCTL |= (InitStruct->DebSel << ANA_CMPCTL_CMP1_IO_NODEB_Pos);

    GPIOAF->IOE_SEL &= ~GPIOAF_IOE_SEL_SEL7;
    GPIOAF->IOE_SEL |= (InitStruct->OutputSel << GPIOAF_IOE_SEL_SEL7_Pos);
  }
  /* CMP2 Configure */
  else
  {
    ANA->CMPCTL &= ~ANA_CMPCTL_CMP2_IO_NODEB;
    ANA->CMPCTL |= (InitStruct->DebSel << ANA_CMPCTL_CMP2_IO_NODEB_Pos);

    GPIOA->SEL &= ~GPIOA_SEL_SEL6;
    GPIOA->SEL |= (InitStruct->OutputSel << GPIOA_SEL_SEL6_Pos);
  }
}

/**
  * @brief  Fills each CMP_OutputTypeDef member with its default value.
  * @param  InitStruct: pointer to an CMP_OutputTypeDef structure which will be initialized.
  * @retval None
  */
void CMP_OutputStructInit(CMP_OutputTypeDef *InitStruct)
{
  InitStruct->DebSel = CMP_OUTPUT_DEB;
  InitStruct->OutputSel = DISABLE;
}

/**
  * @brief  Gets comparator count value.
  * @param  CMPx:
                 CMP_1
                 CMP_2
  * @retval Comparator count value.
  */
uint32_t CMP_GetCNTValue(uint32_t CMPx)
{
  /* Check parameters */
  assert_parameters(IS_CMP(CMPx));

  if (CMPx == CMP_1)
  {
    return ANA->CMPCNT1;
  }
  else
  {
    return ANA->CMPCNT2;
  }
}

/**
  * @brief  Clears comparator counter value.
  * @param  CMPx:
                 CMP_1
                 CMP_2
  * @retval None
  */
void CMP_ClearCNTValue(uint32_t CMPx)
{
  /* Check parameters */
  assert_parameters(IS_CMP(CMPx));

  if (CMPx == CMP_1)
  {
    ANA->CMPCNT1 = 0;
  }
  else
  {
    ANA->CMPCNT2 = 0;
  }
}

/**
  * @brief  Enables or disables Comparator.
  * @param  CMPx:
                 CMP_1
                 CMP_2
            NewState: 
                ENABLE
                DISABLE
  * @retval None
  */
void CMP_Cmd(uint32_t CMPx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_CMP(CMPx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 

  if (CMPx == CMP_1)
  {
    ANA->REG3 &= ~ANA_REG3_CMP1PDN;
    ANA->REG3 |= (NewState << ANA_REG3_CMP1PDN_Pos);
  }
  else
  {
    ANA->REG3 &= ~ANA_REG3_CMP2PDN;
    ANA->REG3 |= (NewState << ANA_REG3_CMP2PDN_Pos);
  }
}

/**
  * @brief  Gets comparator output level
  * @param  None
  * @retval Output of comparator
  */
uint8_t CMP_GetOutputValue(uint32_t CMPx)
{
  /* Check parameters */
  assert_parameters(IS_CMP(CMPx));

  if (CMPx == CMP_1)
  {
    return ((ANA->CMPOUT & ANA_CMPOUT_CMP1) >> ANA_CMPOUT_CMP1_Pos);
  }
  else
  {
    return ((ANA->CMPOUT & ANA_CMPOUT_CMP2) >> ANA_CMPOUT_CMP2_Pos);
  }
}

/**
  * @brief  Enables or disables Comparator interrupt.
  * @param  CMPx:
  *              CMP_1
  *              CMP_2
  *         NewState: 
  *             ENABLE
  *             DISABLE
  * @retval None
  */
void CMP_INTConfig(uint32_t CMPx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_CMP(CMPx));

  if (CMPx == CMP_1)
  {
    ANA->INTEN &= ~ANA_INTEN_INTEN2;
    ANA->INTEN |= (NewState<<ANA_INTEN_INTEN2_Pos);
  }
  else
  {
    ANA->INTEN &= ~ANA_INTEN_INTEN3;
    ANA->INTEN |= (NewState<<ANA_INTEN_INTEN3_Pos);
  }
}

/**
  * @brief  Gets comparator interrupt flag status.
  * @param  CMPx:
  *              CMP_1
  *              CMP_2
  * @retval flag status
  *              0: status not set
  *              1: status set
  */
uint8_t CMP_GetINTStatus(uint32_t CMPx)
{
  /* Check parameters */
  assert_parameters(IS_CMP(CMPx));
  
  if (CMPx == CMP_1)
  {
    return ((ANA->INTSTS & ANA_INTSTS_INTSTS2) >> ANA_INTSTS_INTSTS2_Pos);
  }
  else
  {
    return ((ANA->INTSTS & ANA_INTSTS_INTSTS3) >> ANA_INTSTS_INTSTS3_Pos);
  }
}

/**
  * @brief  Clears comparator interrupt flag.
  * @param  CMPx:
  *              CMP_1
  *              CMP_2
  * @retval None
  */
void CMP_ClearINTStatus(uint32_t CMPx)
{
  /* Check parameters */
  assert_parameters(IS_CMP(CMPx));
  
  if (CMPx == CMP_1)
  {
    ANA->INTSTS = ANA_INTSTS_INTSTS2;
  }
  else
  {
    ANA->INTSTS = ANA_INTSTS_INTSTS3;
  }
}

/*********************************** END OF FILE ******************************/
