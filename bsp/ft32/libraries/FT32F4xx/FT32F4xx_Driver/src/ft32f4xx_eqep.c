/**
  ******************************************************************************
  * @file               ft32f4xx_eqep.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Enhanced Quadrature Encoder Pulse (eQEP):
  *                 + Initialization and Configuration
  *                 + EQEP control
  *                 + Data register access
  *                 + Interrupts and flags management
  * @version            V1.0.0
  * @date                   2025-04-22
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_eqep.h"
#include "ft32f4xx_rcc.h"


/** @defgroup EQEP
  * @brief EQEP driver modules
  * @{
  */


/**
  * @brief  Initialize the EQEP control according to the specified parameters in the
  *         EQEP_InitTypeDef and initialize the associated handle.
  * @param  EQEP_InitStruct  pointer to a EQEP_InitTypeDef structure that contains the
  *         configuration information for the specified EQEP peripheral.
  * @retval None
  */
void EQEP_Init(EQEP_InitTypeDef* EQEP_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_EQEP_RESET_SOURCE(EQEP_InitStruct->PosCounterResetSrc));
    assert_param(IS_EQEP_SE_INIT(EQEP_InitStruct->SEInitPosCounter));
    assert_param(IS_EQEP_IE_INIT(EQEP_InitStruct->IEInitPosCounter));
    assert_param(IS_EQEP_SE_LATCH(EQEP_InitStruct->SELatchPosCounter));
    assert_param(IS_EQEP_IE_LATCH(EQEP_InitStruct->IELatchPosCounter));
    assert_param(IS_EQEP_CAPTURELATCH_MODE(EQEP_InitStruct->CaptureLatchMode));
    assert_param(IS_EQEP_POS_COUNTER_VALUE(EQEP_InitStruct->PosCounterValue));
    assert_param(IS_EQEP_POS_COUNTER_INIT_VALUE(EQEP_InitStruct->PosCounterInitValue));
    assert_param(IS_EQEP_POS_COUNTER_MAX_VALUE(EQEP_InitStruct->PosCounterMaxValue));
    assert_param(IS_EQEP_POS_COUNTER_CMP_VALUE(EQEP_InitStruct->PosCounterCmpValue));
    assert_param(IS_EQEP_UNIT_TIMER_PERIOD_VALUE(EQEP_InitStruct->UnitTimerPeriodValue));
    assert_param(IS_EQEP_WDG_TIMER_PERIOD_VALUE(EQEP_InitStruct->WdgTimerPeriodValue));


    /* Config EQEP control register */
    tmpreg = (uint32_t)((EQEP_InitStruct->PosCounterResetSrc) |
                        (EQEP_InitStruct->SEInitPosCounter) |
                        (EQEP_InitStruct->IEInitPosCounter) |
                        (EQEP_InitStruct->SELatchPosCounter) |
                        (EQEP_InitStruct->IELatchPosCounter) |
                        (EQEP_InitStruct->CaptureLatchMode));

    /* Write to EQEP QEPCTL register */
    EQEP->QEPCTL = tmpreg;

    /* Write the EQEP position counter register */
    EQEP->QPOSCNT = EQEP_InitStruct->PosCounterValue;

    /* Config the initialization value of the EQEP position counter register */
    EQEP->QPOSINIT = EQEP_InitStruct->PosCounterInitValue;

    /* Config the maximum value of the EQEP position counter register */
    EQEP->QPOSMAX = EQEP_InitStruct->PosCounterMaxValue;

    /* Config the compare value of the EQEP position counter register */
    EQEP->QPOSCMP = EQEP_InitStruct->PosCounterCmpValue;

    /* Config the period value of the EQEP unit timer register */
    EQEP->QUPRD = EQEP_InitStruct->UnitTimerPeriodValue;

    /* Config the period value of the EQEP watch dog timer register */
    EQEP->QWDPRD = EQEP_InitStruct->WdgTimerPeriodValue;


}


/**
  * @brief  Initialize the EQEP quadrature decoder unit according to the specified parameters in the
  *         EQEP_QDUInitStruct.
  * @param  EQEP_QDUInitStruct  pointer to a EQEP_QDUInitTypeDef structure that contains the
  *         configuration information for the specified EQEP quadrature decoder unit.
  * @retval None
  */
void EQEP_QDUInit(EQEP_QDUInitTypeDef* EQEP_QDUInitStruct)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_EQEP_POSCNTSRC_MODE(EQEP_QDUInitStruct->PosCounterSource));
    assert_param(IS_FUNCTIONAL_STATE(EQEP_QDUInitStruct->SyncOutput));
    assert_param(IS_EQEP_SYNC_OUTPUT_PIN(EQEP_QDUInitStruct->SyncOutputPin));
    assert_param(IS_EQEP_EXTERNAL_CLOCK_RATE(EQEP_QDUInitStruct->ExternalClockRate));
    assert_param(IS_FUNCTIONAL_STATE(EQEP_QDUInitStruct->ClockDirSwap));
    assert_param(IS_FUNCTIONAL_STATE(EQEP_QDUInitStruct->IndexGate));
    assert_param(IS_EQEP_QEPA_POLARITY(EQEP_QDUInitStruct->QEPAPolarity));
    assert_param(IS_EQEP_QEPB_POLARITY(EQEP_QDUInitStruct->QEPBPolarity));
    assert_param(IS_EQEP_QEPI_POLARITY(EQEP_QDUInitStruct->QEPIPolarity));
    assert_param(IS_EQEP_QEPS_POLARITY(EQEP_QDUInitStruct->QEPSPolarity));


    /* Get the EQEP QEPCTL value */
    tmpreg = EQEP->QDECCTL;

    /* Config EQEP quadrature decoder control register */
    tmpreg &= (uint32_t)~EQEP_QDECCTL_QSRC;
    tmpreg |= (uint32_t)(EQEP_QDUInitStruct->PosCounterSource);

    tmpreg |= (uint32_t)((EQEP_QDUInitStruct->ExternalClockRate) |
                         (EQEP_QDUInitStruct->IndexGate    << 9U) |
                         (EQEP_QDUInitStruct->QEPAPolarity) |
                         (EQEP_QDUInitStruct->QEPBPolarity) |
                         (EQEP_QDUInitStruct->QEPIPolarity) |
                         (EQEP_QDUInitStruct->QEPSPolarity));

    if (EQEP_QDUInitStruct->SyncOutput == ENABLE)
    {
        tmpreg |= (uint32_t)(EQEP_QDECCTL_SOEN |
                             (EQEP_QDUInitStruct->SyncOutputPin));
    }

    if (EQEP_QDUInitStruct->ClockDirSwap == ENABLE)
    {
        tmpreg |= (uint32_t)EQEP_QDECCTL_SWAP;
    }

    if (EQEP_QDUInitStruct->IndexGate == ENABLE)
    {
        tmpreg |= (uint32_t)EQEP_QDECCTL_IGATE;
    }

    /* Write to EQEP QEPCTL register */
    EQEP->QDECCTL = tmpreg;

}


/**
  * @brief  Initialize the EQEP capture control according to the specified parameters in the
  *         EQEP_CAPInitStruct.
  * @param  EQEP_CAPInitStruct  pointer to a EQEP_CAPInitTypeDef structure that contains the
  *         configuration information for the specified EQEP capture unit.
  * @retval None
  */
void EQEP_CAPInit(EQEP_CAPInitTypeDef* EQEP_CAPInitStruct)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_EQEP_CLOCKPRESCALER(EQEP_CAPInitStruct->CaptureClockPrescaler));
    assert_param(IS_EQEP_EVENTPRESCALER(EQEP_CAPInitStruct->UnitPosEventPrescaler));
    assert_param(IS_EQEP_CAPTURE_PERIOD_VALUE(EQEP_CAPInitStruct->CapturePeriodValue));


    /* Get the EQEP QCAPCTL value */
    tmpreg = EQEP->QCAPCTL;

    /* Config EQEP capture control register */
    tmpreg &= (uint32_t)~EQEP_QCAPCTL_CEN;
    tmpreg |= (uint32_t)(EQEP_CAPInitStruct->CaptureClockPrescaler);
    tmpreg |= (uint32_t)(EQEP_CAPInitStruct->UnitPosEventPrescaler);

    /* Write to EQEP QCAPCTL register */
    EQEP->QCAPCTL = tmpreg;

    /* Config the period value of the EQEP capture counter register */
    EQEP->QCPRD = EQEP_CAPInitStruct->CapturePeriodValue;

}



/**
  * @brief  Initialize the EQEP position compare control according to the specified
  *         parameters in the EQEP_PosCmpInitStruct.
  * @param  EQEP_PosCmpInitStruct  pointer to a EQEP_PosCmpInitTypeDef structure
  *         that contains the configuration information for the specified
  *         EQEP position compare unit.
  * @retval None
  */
void EQEP_POSCMPInit(EQEP_PosCmpInitTypeDef* EQEP_PosCmpInitStruct)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(EQEP_PosCmpInitStruct->PosCompareShadow));
    assert_param(IS_EQEP_POSCMP_LOAD(EQEP_PosCmpInitStruct->PosCompareShadowLoad));
    assert_param(IS_EQEP_SYNCOUT_POLARITY(EQEP_PosCmpInitStruct->SyncOutPolarity));
    assert_param(IS_FUNCTIONAL_STATE(EQEP_PosCmpInitStruct->PosCompare));
    assert_param(IS_EQEP_SYNCOUT_PULSE_WIDTH(EQEP_PosCmpInitStruct->SyncOutPulseWidth));


    /* Get the EQEP QPOSCTL value */
    tmpreg = EQEP->QPOSCTL;

    /* Config EQEP position compare control register */
    if (EQEP_PosCmpInitStruct->PosCompareShadow == ENABLE)
    {
        tmpreg |= (uint32_t)EQEP_QPOSCTL_PCSHDW;
    }

    tmpreg |= (uint32_t)((EQEP_PosCmpInitStruct->PosCompareShadowLoad) |
                         (EQEP_PosCmpInitStruct->SyncOutPolarity));

    if (EQEP_PosCmpInitStruct->PosCompare == ENABLE)
    {
        tmpreg |= (uint32_t)EQEP_QPOSCTL_PCMPE;
    }

    tmpreg |= (uint32_t)(EQEP_PosCmpInitStruct->SyncOutPulseWidth);

    /* Write to EQEP QCAPCTL register */
    EQEP->QPOSCTL = tmpreg;

}


/**
  * @brief  Fills each EQEP_StructInit member with its default value.
  * @param  EQEP_InitStruct  pointer to a EQEP_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void EQEP_StructInit(EQEP_InitTypeDef* EQEP_InitStruct)
{
    /*---- Reset the parameter values of the EQEP structure ----*/
    /* Initialize the EQEP_PosCounterResetSrc member */
    EQEP_InitStruct->PosCounterResetSrc = 0U;

    /* Initialize the EQEP_SEInitPosCounter member */
    EQEP_InitStruct->SEInitPosCounter = 0U;

    /* Initialize the EQEP_IEInitPosCounter member */
    EQEP_InitStruct->IEInitPosCounter = 0U;

    /* Initialize the EQEP_SELatchPosCounter member */
    EQEP_InitStruct->SELatchPosCounter = 0U;

    /* Initialize the EQEP_IELatchPosCounter member */
    EQEP_InitStruct->IELatchPosCounter = 0U;

    /* Initialize the EQEP_CaptureLatchMode member */
    EQEP_InitStruct->CaptureLatchMode = 0U;

    /* Initialize the EQEP_PosCounterValue member */
    EQEP_InitStruct->PosCounterValue = 0U;

    /* Initialize the EQEP_PosCounterInitValue member */
    EQEP_InitStruct->PosCounterInitValue = 0U;

    /* Initialize the EQEP_PosCounterMaxValue member */
    EQEP_InitStruct->PosCounterMaxValue = 0U;

    /* Initialize the EQEP_PosCounterCmpValue member */
    EQEP_InitStruct->PosCounterCmpValue = 0U;

    /* Initialize the EQEP_UnitTimerPeriodValue member */
    EQEP_InitStruct->UnitTimerPeriodValue = 0U;

    /* Initialize the EQEP_WdgTimerPeriodValue member */
    EQEP_InitStruct->WdgTimerPeriodValue = 0U;

}


/**
  * @brief  Fills each EQEP_QDUStructInit member with its default value.
  * @param  EQEP_QDUInitStruct  pointer to a EQEP_QDUInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void EQEP_QDUStructInit(EQEP_QDUInitTypeDef* EQEP_QDUInitStruct)
{
    /*---- Reset the parameter values of the EQEP quadrature decoder structure ----*/
    /* Initialize the EQEP_PosCounterSource member */
    EQEP_QDUInitStruct->PosCounterSource = 0U;

    /* Initialize the EQEP_SyncOutput member */
    EQEP_QDUInitStruct->SyncOutput = DISABLE;

    /* Initialize the EQEP_SyncOutputPin member */
    EQEP_QDUInitStruct->SyncOutputPin = 0U;

    /* Initialize the EQEP_ExternalClockRate member */
    EQEP_QDUInitStruct->ExternalClockRate = 0U;

    /* Initialize the EQEP_ClockDirSwap member */
    EQEP_QDUInitStruct->ClockDirSwap = DISABLE;

    /* Initialize the EQEP_IndexGate member */
    EQEP_QDUInitStruct->IndexGate = DISABLE;

    /* Initialize the EQEP_QEPAPolarity member */
    EQEP_QDUInitStruct->QEPAPolarity = 0U;

    /* Initialize the EQEP_QEPBPolarity member */
    EQEP_QDUInitStruct->QEPBPolarity = 0U;

    /* Initialize the EQEP_QEPIPolarity member */
    EQEP_QDUInitStruct->QEPIPolarity = 0U;

    /* Initialize the EQEP_QEPSPolarity member */
    EQEP_QDUInitStruct->QEPSPolarity = 0U;

}


/**
  * @brief  Fills each EQEP_CAPStructInit member with its default value.
  * @param  EQEP_CAPInitStruct  pointer to a EQEP_CAPInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void EQEP_CAPStructInit(EQEP_CAPInitTypeDef* EQEP_CAPInitStruct)
{
    /*---- Reset the parameter values of the EQEP capture structure ----*/
    /* Initialize the EQEP_CaptureClockPrescaler member */
    EQEP_CAPInitStruct->CaptureClockPrescaler = 0U;

    /* Initialize the EQEP_UnitPosEventPrescaler member */
    EQEP_CAPInitStruct->UnitPosEventPrescaler = 0U;

    /* Initialize the EQEP_CapturePeriodValue member */
    EQEP_CAPInitStruct->CapturePeriodValue = 0U;

}


/**
  * @brief  Fills each EQEP_POSCMPStructInit member with its default value.
  * @param  EQEP_PosCmpInitStruct  pointer to a EQEP_PosCmpInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void EQEP_POSCMPStructInit(EQEP_PosCmpInitTypeDef* EQEP_PosCmpInitStruct)
{
    /*---- Reset the parameter values of the EQEP position compare structure ----*/
    /* Initialize the EQEP_PosCompareShadow member */
    EQEP_PosCmpInitStruct->PosCompareShadow = DISABLE;

    /* Initialize the EQEP_PosCompareShadowLoad member */
    EQEP_PosCmpInitStruct->PosCompareShadowLoad = 0U;

    /* Initialize the EQEP_SyncOutPolarity member */
    EQEP_PosCmpInitStruct->SyncOutPolarity = 0U;

    /* Initialize the EQEP_PosCompare member */
    EQEP_PosCmpInitStruct->PosCompare = DISABLE;

    /* Initialize the EQEP_SyncOutPulseWidth member */
    EQEP_PosCmpInitStruct->SyncOutPulseWidth = 0U;

}





/**
  * @brief  DeInitialize the EQEP peripheral.
  * @retval None
  */
void EQEP_DeInit()
{
    /* Enable EQEP reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PeriphRst_EQEP, ENABLE);

    /* Release EQEP from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PeriphRst_EQEP, DISABLE);

}


/**
  * @brief  Enables or disables the following EQEP counters.
  *         @arg Position counter(QPOSCNT)
  *         @arg Unit timer(QUTMR)
  *         @arg Watch dog timer(QWDTMR)
  *         @arg Capture timer(QCTMR)
  * @note   While resetting the position counter, the internal operating
  *         flags and read-only registers will also be reset. However,
  *         the control and configuration registers are not disturbed
  *         by the software reset.
  * @note   When QEPCTL.OPEN is disabled, some flags in the QFLG register
  *         do not get reset or cleared and show the actual state of that flag.
  * @param  EQEP_SUBMDU_TYPE The data registers of the EQEP.
  *                          This parameter can be one of the following values:
  *                          @arg EQEP_POS_CNT : EQEP position counter.
  *                          @arg EQEP_UNIT_TMR: EQEP unit timer.
  *                          @arg EQEP_WTD_TMR : EQEP watch dog timer.
  *                          @arg EQEP_CAP_TMR : EQEP capture timer.
  * @param  NewState  New state of the EQEP position counter.
  *                   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EQEP_Cmd(uint16_t EQEP_SUBMDU_TYPE, FunctionalState NewState)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_EQEP_SUBMDU_TYPE(EQEP_SUBMDU_TYPE));

    if ((EQEP_SUBMDU_TYPE & EQEP_POS_CNT) != 0U)
    {
        /* Enable the EQEP position counter, QPOSCNT free-running */
        tmpreg |= (uint32_t)EQEP_QEPCTL_QPEN;
    }
    if ((EQEP_SUBMDU_TYPE & EQEP_UNIT_TMR) != 0U)
    {
        /* Enable the EQEP unit timer, QUTMR free-running */
        tmpreg |= (uint32_t)EQEP_QEPCTL_UTE;
    }
    if ((EQEP_SUBMDU_TYPE & EQEP_WTD_TMR) != 0U)
    {
        /* Enable the EQEP watch dog timer, QWDTMR free-running */
        tmpreg |= (uint32_t)EQEP_QEPCTL_WDE;
    }
    if ((EQEP_SUBMDU_TYPE & EQEP_CAP_TMR) != 0U)
    {
        if (NewState != DISABLE)
        {
            /* Enable the EQEP capture timer, QCTMR free-running */
            EQEP->QCAPCTL |= (uint32_t)EQEP_QCAPCTL_CEN;
        }
        else
        {
            /* Disable the EQEP capture timer, QCTMR reset */
            EQEP->QCAPCTL &= (uint32_t)~EQEP_QCAPCTL_CEN;
        }
    }

    if (NewState != DISABLE)
    {
        /* Write to QEPCTL */
        EQEP->QEPCTL |= tmpreg;
    }
    else
    {
        /* Write to QEPCTL */
        EQEP->QEPCTL &= ~tmpreg;
    }
}

//void EQEP_Cmd(uint8_t EQEP_SUBMDU_TYPE, FunctionalState NewState)
//{
//  uint32_t tmpreg = 0;
//  /* Check the parameters */
//  assert_param(IS_FUNCTIONAL_STATE(NewState));
//  assert_param(IS_EQEP_SUBMDU_TYPE(EQEP_SUBMDU_TYPE));
//
//  if(NewState != DISABLE)
//  {
//    if((EQEP_SUBMDU_TYPE & EQEP_QPOSCNT) != 0U)
//    {
//      /* Enable the EQEP position counter, QPOSCNT free-running */
//      tmpreg |= (uint32_t)EQEP_QEPCTL_QPEN;
//    }
//    if((EQEP_SUBMDU_TYPE & EQEP_QUTMR) != 0U)
//    {
//      /* Enable the EQEP unit timer, QUTMR free-running */
//      tmpreg |= (uint32_t)EQEP_QEPCTL_UTE;
//    }
//    if((EQEP_SUBMDU_TYPE & EQEP_QWDTMR) != 0U)
//    {
//      /* Enable the EQEP watch dog timer, QWDTMR free-running */
//      tmpreg |= (uint32_t)EQEP_QEPCTL_WDE;
//    }
//    if((EQEP_SUBMDU_TYPE & EQEP_QCTMR) != 0U)
//    {
//      /* Enable the EQEP capture timer, QCTMR free-running */
//      EQEP->QCAPCTL |= (uint32_t)EQEP_QCAPCTL_CEN;
//    }
//
//    /* Write to QEPCTL */
//    EQEP->QEPCTL |= tmpreg;
//  }
//  else
//  {
//    tmpreg = EQEP->QEPCTL;
//
//    if((EQEP_SUBMDU_TYPE & EQEP_QPOSCNT) != 0U)
//    {
//      /* Disable the EQEP position counter, QPOSCNT reset */
//      tmpreg &= (uint32_t)~EQEP_QEPCTL_QPEN;
//    }
//    if((EQEP_SUBMDU_TYPE & EQEP_QUTMR) != 0U)
//    {
//      /* Disable the EQEP unit timer, QUTMR reset */
//      tmpreg &= (uint32_t)~EQEP_QEPCTL_UTE;
//    }
//    if((EQEP_SUBMDU_TYPE & EQEP_QWDTMR) != 0U)
//    {
//      /* Disable the EQEP watch dog timer, QWDTMR reset */
//      tmpreg &= (uint32_t)~EQEP_QEPCTL_WDE;
//    }
//    if((EQEP_SUBMDU_TYPE & EQEP_QCTMR) != 0U)
//    {
//      /* Disable the EQEP capture timer, QCTMR reset */
//      EQEP->QCAPCTL &= (uint32_t)~EQEP_QCAPCTL_CEN;
//    }
//
//    /* Write to QEPCTL */
//    EQEP->QEPCTL = tmpreg;
//  }
//}


/**
  * @brief  Software initialization position counter.
  * @note   The SWI bit will not be automatically cleared. It is
  *         necessary to use this function again and pass the DISABLE
  *         parameter to clear this bit.
  * @param  NewState  New state of the QEPCTL.SWI.
  *                   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EQEP_SoftwareInitPositionCounter(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the QEPCTL.SWI, initialize the position counter */
        EQEP->QEPCTL |= (uint32_t)EQEP_QEPCTL_SWI;
    }
    else
    {
        /* Disable the EQEP unit timer, QUTMR reset */
        EQEP->QEPCTL &= (uint32_t)~EQEP_QEPCTL_SWI;
    }
}





/**
  * @brief  Write a value to the specified EQEP register.
  * @param  EQEP_REG_TYPE  The data registers of the EQEP.
  *                        This parameter can be one of the following values:
  *                        @arg EQEP_QPOSCNT  : EQEP position counter register.
  *                        @arg EQEP_QPOSINIT : EQEP position counter initialization register.
  *                        @arg EQEP_QPOSMAX  : EQEP position counter maximum register.
  *                        @arg EQEP_QPOSCMP  : EQEP position counter compare register.
  *                        @arg EQEP_QUTMR    : EQEP unit timer.
  *                        @arg EQEP_QUPRD    : EQEP unit timer period register.
  *                        @arg EQEP_QWDTMR   : EQEP watch dog timer.
  *                        @arg EQEP_QWDPRD   : EQEP watch dog timer period register.
  *                        @arg EQEP_QCTMR    : EQEP capture timer.
  *                        @arg EQEP_QCPRD    : EQEP capture timer period register.
  * @param  Value  The values of the specified EQEP registers.
  * @retval None
  */
void EQEP_WriteDataRegister(uint16_t EQEP_REG_TYPE, uint32_t Value)
{
    /* Check the parameters */
    assert_param(IS_EQEP_REG_TYPE(EQEP_REG_TYPE));

    if (EQEP_REG_TYPE == EQEP_QPOSCNT)
    {
        /* Write the value to QPOSCNT */
        EQEP->QPOSCNT = ((uint32_t)Value);
    }
    if (EQEP_REG_TYPE == EQEP_QPOSINIT)
    {
        /* Write the value to QPOSINIT */
        EQEP->QPOSINIT = ((uint32_t)Value);
    }
    if (EQEP_REG_TYPE == EQEP_QPOSMAX)
    {
        /* Write the value to QPOSMAX */
        EQEP->QPOSMAX = ((uint32_t)Value);
    }
    if (EQEP_REG_TYPE == EQEP_QPOSCMP)
    {
        /* Write the value to QPOSCMP */
        EQEP->QPOSCMP = ((uint32_t)Value);
    }
    if (EQEP_REG_TYPE == EQEP_QUTMR)
    {
        /* Write the value to QUTMR */
        EQEP->QUTMR = ((uint32_t)Value);
    }
    if (EQEP_REG_TYPE == EQEP_QUPRD)
    {
        /* Write the value to QUPRD */
        EQEP->QUPRD = ((uint32_t)Value);
    }
    if (EQEP_REG_TYPE == EQEP_QWDTMR)
    {
        /* Write the value to QWDTMR */
        EQEP->QWDTMR = ((uint32_t)Value);
    }
    if (EQEP_REG_TYPE == EQEP_QWDPRD)
    {
        /* Write the value to QWDPRD */
        EQEP->QWDPRD = ((uint32_t)Value);
    }
    if (EQEP_REG_TYPE == EQEP_QCTMR)
    {
        /* Write the value to QCTMR */
        EQEP->QCTMR = ((uint32_t)Value);
    }
    if (EQEP_REG_TYPE == EQEP_QCPRD)
    {
        /* Write the value to QCPRD */
        EQEP->QCPRD = ((uint32_t)Value);
    }
}


/**
  * @brief  Returns the value of the specified EQEP registers.
  * @param  EQEP_REG_TYPE  The data registers of the EQEP.
  *                        This parameter can be one of the following values:
  *                        @arg EQEP_QPOSCNT  : EQEP position counter register.
  *                        @arg EQEP_QPOSINIT : EQEP position counter initialization register.
  *                        @arg EQEP_QPOSMAX  : EQEP position counter maximum register.
  *                        @arg EQEP_QPOSCMP  : EQEP position counter compare register.
  *                        @arg EQEP_QPOSILAT : EQEP index position latch register.
  *                        @arg EQEP_QPOSSLAT : EQEP strobe position latch register.
  *                        @arg EQEP_QPOSLAT  : EQEP position latch register.
  *                        @arg EQEP_QUTMR    : EQEP unit timer.
  *                        @arg EQEP_QUPRD    : EQEP unit timer period register.
  *                        @arg EQEP_QWDTMR   : EQEP watch dog timer.
  *                        @arg EQEP_QWDPRD   : EQEP watch dog timer period register.
  *                        @arg EQEP_QCTMR    : EQEP capture timer.
  *                        @arg EQEP_QCPRD    : EQEP capture timer period register.
  *                        @arg EQEP_QCTMRLAT : EQEP capture timer latch register.
  *                        @arg EQEP_QCPRDLAT : EQEP capture timer period latch register.
  * @retval The value of the specified EQEP registers.
  */
uint32_t EQEP_GetDataRegister(uint16_t EQEP_REG_TYPE)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_EQEP_REG_TYPE(EQEP_REG_TYPE));


    if (EQEP_REG_TYPE == EQEP_QPOSCNT)
    {
        /* Get the value of QPOSCNT */
        tmpreg = ((uint32_t)(EQEP->QPOSCNT));
    }
    if (EQEP_REG_TYPE == EQEP_QPOSINIT)
    {
        /* Get the value of QPOSINIT */
        tmpreg = ((uint32_t)(EQEP->QPOSINIT));
    }
    if (EQEP_REG_TYPE == EQEP_QPOSMAX)
    {
        /* Get the value of QPOSMAX */
        tmpreg = ((uint32_t)(EQEP->QPOSMAX));
    }
    if (EQEP_REG_TYPE == EQEP_QPOSCMP)
    {
        /* Get the value of QPOSCMP */
        tmpreg = ((uint32_t)(EQEP->QPOSCMP));
    }
    if (EQEP_REG_TYPE == EQEP_QPOSILAT)
    {
        /* Get the value of  */
        tmpreg = ((uint32_t)(EQEP->QPOSILAT));
    }
    if (EQEP_REG_TYPE == EQEP_QPOSSLAT)
    {
        /* Get the value of  */
        tmpreg = ((uint32_t)(EQEP->QPOSSLAT));
    }
    if (EQEP_REG_TYPE == EQEP_QPOSLAT)
    {
        /* Get the value of  */
        tmpreg = ((uint32_t)(EQEP->QPOSLAT));
    }
    if (EQEP_REG_TYPE == EQEP_QUTMR)
    {
        /* Get the value of QUTMR */
        tmpreg = ((uint32_t)(EQEP->QUTMR));
    }
    if (EQEP_REG_TYPE == EQEP_QUPRD)
    {
        /* Get the value of QUPRD */
        tmpreg = ((uint32_t)(EQEP->QUPRD));
    }
    if (EQEP_REG_TYPE == EQEP_QWDTMR)
    {
        /* Get the value of QWDTMR */
        tmpreg = ((uint32_t)(EQEP->QWDTMR));
    }
    if (EQEP_REG_TYPE == EQEP_QWDPRD)
    {
        /* Get the value of QWDPRD */
        tmpreg = ((uint32_t)(EQEP->QWDPRD));
    }
    if (EQEP_REG_TYPE == EQEP_QCTMR)
    {
        /* Get the value of QCTMR */
        tmpreg = ((uint32_t)(EQEP->QCTMR));
    }
    if (EQEP_REG_TYPE == EQEP_QCPRD)
    {
        /* Get the value of QCPRD */
        tmpreg = ((uint32_t)(EQEP->QCPRD));
    }
    if (EQEP_REG_TYPE == EQEP_QCTMRLAT)
    {
        /* Get the value of QCTMRLAT */
        tmpreg = ((uint32_t)(EQEP->QCTMRLAT));
    }
    if (EQEP_REG_TYPE == EQEP_QCPRDLAT)
    {
        /* Get the value of QCPRDLAT */
        tmpreg = ((uint32_t)(EQEP->QCPRDLAT));
    }

    /* Return the value of data register */
    return tmpreg;
}


/**
  * @brief  Enable the specified EQEP interrupts.
  * @param  EQEP_IT specifies the EQEP interrupt sources to be enabled or disabled.
  *                 This parameter can be any combination of the following values:
  *                 @arg EQEP_IT_PCE  Position counter error interrupt
  *                 @arg EQEP_IT_PHE  Quadrature phase error interrupt
  *                 @arg EQEP_IT_QDC  Quadrature direction change interrupt
  *                 @arg EQEP_IT_WTO  Watchdog time out interrupt
  *                 @arg EQEP_IT_PCU  Position counter underflow interrupt
  *                 @arg EQEP_IT_PCO  Position counter overflow interrupt
  *                 @arg EQEP_IT_PCR  Position compare ready interrupt
  *                 @arg EQEP_IT_PCM  Position compare match interrupt
  *                 @arg EQEP_IT_SEL  Strobe event latch interrupt
  *                 @arg EQEP_IT_IEL  Index event latch interrupt
  *                 @arg EQEP_IT_UTO  Unit time out interrupt
  * @param  NewState  new state of the specified EQEP interrupt.
  *                   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EQEP_ITConfig(uint16_t EQEP_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_EQEP_IT(EQEP_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));


    if (NewState != DISABLE)
    {
        /* Enable the selected EQEP interrupts */
        EQEP->QEINT |= EQEP_IT;
    }
    else
    {
        /* Disable the selected EQEP interrupts */
        EQEP->QEINT &= ~EQEP_IT;
    }
}


/**
  * @brief  Clears the EQEP interrupt flags.
  * @param  EQEP_FLAG  specifies the EQEP interrupt flag to clear.
  *                    This parameter can be one of the following values:
  *                    @arg EQEP_FLAG_INT  EQEP global interrupt flag
  *                    @arg EQEP_FLAG_PCE  Position counter error interrupt flag
  *                    @arg EQEP_FLAG_PHE  Quadrature phase error interrupt flag
  *                    @arg EQEP_FLAG_QDC  Quadrature direction change interrupt flag
  *                    @arg EQEP_FLAG_WTO  Watchdog time out interrupt flag
  *                    @arg EQEP_FLAG_PCU  Position counter underflow interrupt flag
  *                    @arg EQEP_FLAG_PCO  Position counter overflow interrupt flag
  *                    @arg EQEP_FLAG_PCR  Position compare ready interrupt flag
  *                    @arg EQEP_FLAG_PCM  Position compare match interrupt flag
  *                    @arg EQEP_FLAG_SEL  Strobe event latch interrupt flag
  *                    @arg EQEP_FLAG_IEL  Index event latch interrupt flag
  *                    @arg EQEP_FLAG_UTO  Unit time out interrupt flag
  * @retval None
  */
void EQEP_ClearFlag(uint16_t EQEP_FLAG)
{
    /* Check the parameters */
    assert_param(IS_EQEP_FLAG(EQEP_FLAG));

    /* Clear the selected EQEP flags */
    EQEP->QCLR = EQEP_FLAG;
}


/**
  * @brief  Force the specified EQEP interrupt.
  * @param  EQEP_IT specifies the EQEP interrupt sources to be enabled or disabled.
  *                 This parameter can be any combination of the following values:
  *                 @arg EQEP_IT_PCE  Position counter error interrupt
  *                 @arg EQEP_IT_PHE  Quadrature phase error interrupt
  *                 @arg EQEP_IT_QDC  Quadrature direction change interrupt
  *                 @arg EQEP_IT_WTO  Watchdog time out interrupt
  *                 @arg EQEP_IT_PCU  Position counter underflow interrupt
  *                 @arg EQEP_IT_PCO  Position counter overflow interrupt
  *                 @arg EQEP_IT_PCR  Position compare ready interrupt
  *                 @arg EQEP_IT_PCM  Position compare match interrupt
  *                 @arg EQEP_IT_SEL  Strobe event latch interrupt
  *                 @arg EQEP_IT_IEL  Index event latch interrupt
  *                 @arg EQEP_IT_UTO  Unit time out interrupt
  * @retval None
  */
void EQEP_ITForce(uint16_t EQEP_IT)
{
    /* Check the parameters */
    assert_param(IS_EQEP_IT(EQEP_IT));

    /* Force the selected EQEP interrupt */
    EQEP->QFRC = EQEP_IT;
}


/**
  * @brief  Checks whether the specified EQEP interrupt has occurred or not.
  * @param  EQEP_IT specifies the EQEP interrupt sources to check.
  *                 This parameter can be any combination of the following values:
  *                 @arg EQEP_IT_PCE  Position counter error interrupt
  *                 @arg EQEP_IT_PHE  Quadrature phase error interrupt
  *                 @arg EQEP_IT_QDC  Quadrature direction change interrupt
  *                 @arg EQEP_IT_WTO  Watchdog time out interrupt
  *                 @arg EQEP_IT_PCU  Position counter underflow interrupt
  *                 @arg EQEP_IT_PCO  Position counter overflow interrupt
  *                 @arg EQEP_IT_PCR  Position compare ready interrupt
  *                 @arg EQEP_IT_PCM  Position compare match interrupt
  *                 @arg EQEP_IT_SEL  Strobe event latch interrupt
  *                 @arg EQEP_IT_IEL  Index event latch interrupt
  *                 @arg EQEP_IT_UTO  Unit time out interrupt
  * @retval The new state of EQEP_IT (SET or RESET).
  */
ITStatus EQEP_GetITStatus(uint16_t EQEP_IT)
{
    /* Check the parameters */
    assert_param(IS_EQEP_IT(EQEP_IT));


    ITStatus bitstatus = RESET;

    /* Check the status of the specified EQEP interrupt */
    if ((uint32_t)(EQEP->QEINT & EQEP_IT) != (uint32_t)RESET)
    {
        /* EQEP_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* EQEP_IT is reset */
        bitstatus = RESET;
    }
    /* Return the EQEP_IT status */
    return  bitstatus;

}


/**
  * @brief  Checks whether the specified EQEP flag has occurred or not.
  * @param  EQEP_FLAG specifies the EQEP flag to check.
  *                 This parameter can be any combination of the following values:
  *                 @arg EQEP_FLAG_INT  EQEP global interrupt flag
  *                 @arg EQEP_FLAG_PCE  Position counter error interrupt flag
  *                 @arg EQEP_FLAG_PHE  Quadrature phase error interrupt flag
  *                 @arg EQEP_FLAG_QDC  Quadrature direction change interrupt flag
  *                 @arg EQEP_FLAG_WTO  Watchdog time out interrupt flag
  *                 @arg EQEP_FLAG_PCU  Position counter underflow interrupt flag
  *                 @arg EQEP_FLAG_PCO  Position counter overflow interrupt flag
  *                 @arg EQEP_FLAG_PCR  Position compare ready interrupt flag
  *                 @arg EQEP_FLAG_PCM  Position compare match interrupt flag
  *                 @arg EQEP_FLAG_SEL  Strobe event latch interrupt flag
  *                 @arg EQEP_FLAG_IEL  Index event latch interrupt flag
  *                 @arg EQEP_FLAG_UTO  Unit time out interrupt flag
  * @retval The new state of EQEP_FLAG (SET or RESET).
  */
FlagStatus EQEP_GetFlagStatus(uint16_t EQEP_FLAG)
{
    /* Check the parameters */
    assert_param(IS_EQEP_FLAG(EQEP_FLAG));


    FlagStatus bitstatus = RESET;

    /* Check the status of the specified EQEP flag */
    if ((uint32_t)(EQEP->QFLG & EQEP_FLAG) != (uint32_t)RESET)
    {
        /* EQEP_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* EQEP_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the EQEP_FLAG status */
    return  bitstatus;

}


/**
  * @brief  Checks whether the specified EQEP status has occurred or not.
  * @param  EQEP_STATUS specifies the EQEP status sources to check.
  *                 This parameter can be any combination of the following values:
  *                 @arg EQEP_STATUS_UPEVNT  Unit position event flag
  *                 @arg EQEP_STATUS_FIDF    Direction on the first index marker
  *                 @arg EQEP_STATUS_QDF     Quadrature direction flag
  *                 @arg EQEP_STATUS_QDLF    EQEP direction latch flag
  *                 @arg EQEP_STATUS_COEF    Capture overflow error flag
  *                 @arg EQEP_STATUS_CDEF    Capture direction error flag
  *                 @arg EQEP_STATUS_FIMF    First index marker flag
  *                 @arg EQEP_STATUS_PCEF    Position counter error flag
  * @retval The new state of EQEP_STATUS (SET or RESET).
  */
FlagStatus EQEP_GetStatus(uint8_t EQEP_STATUS)
{
    /* Check the parameters */
    assert_param(IS_EQEP_STATUS(EQEP_STATUS));


    FlagStatus bitstatus = RESET;

    /* Check the status of the specified EQEP status */
    if ((uint32_t)(EQEP->QEPSTS & EQEP_STATUS) != (uint32_t)RESET)
    {
        /* EQEP_STATUS is set */
        bitstatus = SET;
    }
    else
    {
        /* EQEP_STATUS is reset */
        bitstatus = RESET;
    }
    /* Return the EQEP_STATUS status */
    return  bitstatus;

}






/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
