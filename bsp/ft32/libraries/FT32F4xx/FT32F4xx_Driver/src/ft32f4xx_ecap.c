/**
  ******************************************************************************
  * @file               ft32f4xx_ecap.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Enhanced Capture (ECAP):
  *                 + Initialization and Configuration
  *                 + ECAP control
  *                 + Data register access
  *                 + Interrupts and flags management
  * @version            V1.0.0
  * @data                   2025-04-22
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_ecap.h"
#include "ft32f4xx_rcc.h"


/** @defgroup ECAP
  * @brief ECAP driver modules
  * @{
  */


/**
  * @brief  Initialize the ECAP according to the specified parameters in the
  *         ECAP_InitTypeDef and initialize the associated handle.
  * @param  ECAP_InitStruct  pointer to a ECAP_InitTypeDef structure that contains the
  *         configuration information for the specified ECAP peripheral.
  * @retval None
  */
void ECAP_Init(ECAP_InitTypeDef* ECAP_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_ECAP_MODE(ECAP_InitStruct->ECAPMode));
    assert_param(IS_ECAP_EVENT_PRESCALER(ECAP_InitStruct->EventPrescaler));
    assert_param(IS_FUNCTIONAL_STATE(ECAP_InitStruct->CaptureLoad));
    assert_param(IS_FUNCTIONAL_STATE(ECAP_InitStruct->CaptureEvent4Reset));
    assert_param(IS_FUNCTIONAL_STATE(ECAP_InitStruct->CaptureEvent3Reset));
    assert_param(IS_FUNCTIONAL_STATE(ECAP_InitStruct->CaptureEvent2Reset));
    assert_param(IS_FUNCTIONAL_STATE(ECAP_InitStruct->CaptureEvent1Reset));
    assert_param(IS_ECAP_EVENT_POLARITY(ECAP_InitStruct->CaptureEvent4Polarity));
    assert_param(IS_ECAP_EVENT_POLARITY(ECAP_InitStruct->CaptureEvent3Polarity));
    assert_param(IS_ECAP_EVENT_POLARITY(ECAP_InitStruct->CaptureEvent2Polarity));
    assert_param(IS_ECAP_EVENT_POLARITY(ECAP_InitStruct->CaptureEvent1Polarity));
    assert_param(IS_ECAP_APWM_POLARITY(ECAP_InitStruct->APWMPolarity));
    assert_param(IS_FUNCTIONAL_STATE(ECAP_InitStruct->CounterSyncIn));
    assert_param(IS_ECAP_MOD_COUNTER_STOP_WRAP(ECAP_InitStruct->ModCounterStopWrap));
    assert_param(IS_ECAP_MOD_COUNTER_MODE(ECAP_InitStruct->ModCounterMode));
    assert_param(IS_ECAP_COUNTER_VALUE(ECAP_InitStruct->CounterValue));
    assert_param(IS_ECAP_COUNTER_PHASE_VALUE(ECAP_InitStruct->CounterPhaseValue));
    assert_param(IS_ECAP_CAPTURE1_REGISTER_VALUE(ECAP_InitStruct->Capture1RegisterValue));
    assert_param(IS_ECAP_CAPTURE2_REGISTER_VALUE(ECAP_InitStruct->Capture2RegisterValue));

    /* Config ECAP capture control1 */
    tmpreg = ((uint32_t)(ECAP_InitStruct->EventPrescaler        << 9U) |
              (ECAP_InitStruct->CaptureEvent4Polarity << 6U) |
              (ECAP_InitStruct->CaptureEvent3Polarity << 4U) |
              (ECAP_InitStruct->CaptureEvent2Polarity << 2U) |
              (ECAP_InitStruct->CaptureEvent1Polarity << 0U));

    if (ECAP_InitStruct->CaptureLoad == ENABLE)
    {
        tmpreg |= (uint32_t)ECAP_ECCTL1_CAPLDEN;
    }

    if (ECAP_InitStruct->CaptureEvent4Reset == ENABLE)
    {
        tmpreg |= (uint32_t)ECAP_ECCTL1_CTRRST4;
    }

    if (ECAP_InitStruct->CaptureEvent3Reset == ENABLE)
    {
        tmpreg |= (uint32_t)ECAP_ECCTL1_CTRRST3;
    }

    if (ECAP_InitStruct->CaptureEvent2Reset == ENABLE)
    {
        tmpreg |= (uint32_t)ECAP_ECCTL1_CTRRST2;
    }

    if (ECAP_InitStruct->CaptureEvent1Reset == ENABLE)
    {
        tmpreg |= (uint32_t)ECAP_ECCTL1_CTRRST1;
    }

    /* Write to ECAP ECCTL1 */
    ECAP->ECCTL1 = tmpreg;


    tmpreg = 0;

    /* Config ECAP capture control2 */
    tmpreg = ((uint32_t)(ECAP_InitStruct->ECAPMode) |
              (ECAP_InitStruct->ModCounterStopWrap) |
              (ECAP_InitStruct->ModCounterMode));

    //tmpreg &= (uint32_t)~ECAP_ECCTL2_STOP_WRAP;
    //tmpreg |= (uint32_t)(ECAP_InitStruct->ModCounterStopWrap);

    if (ECAP_InitStruct->CounterSyncIn == ENABLE)
    {
        tmpreg |= (uint32_t)ECAP_ECCTL2_SYNCI_EN;
    }

    /* Config ECAP APWM mode */
    if (ECAP_InitStruct->ECAPMode == ECAP_MODE_APWM)
    {
        /* Config APWM output polarity */
        tmpreg |= ((uint32_t)(ECAP_InitStruct->APWMPolarity));

        /* Config ECAP counter value */
        ECAP->TSCTR = ECAP_InitStruct->CounterValue;

        /* Config ECAP counter phase value */
        ECAP->CTRPHS = ECAP_InitStruct->CounterPhaseValue;

        /* Config ECAP capture 1 register value */
        ECAP->CAP1 = ECAP_InitStruct->Capture1RegisterValue;

        /* Config ECAP capture 2 register value */
        ECAP->CAP2 = ECAP_InitStruct->Capture2RegisterValue;
    }

    /* Write to ECAP ECCTL2 */
    ECAP->ECCTL2 = tmpreg;

}


/**
  * @brief  Fills each ECAP_StructInit member with its default value.
  * @param  ECAP_StructInit  pointer to a ECAP_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void ECAP_StructInit(ECAP_InitTypeDef* ECAP_InitStruct)
{
    /*-------------- Reset ECAP init structure parameters values ------------------*/
    /* Initialize the ECAP mode */
    ECAP_InitStruct->ECAPMode = 0U;

    /* Initialize the prescaler of event filter */
    ECAP_InitStruct->EventPrescaler = 0U;

    /* Initialize the enable loading of CAP1-4 registers on a capture event */
    ECAP_InitStruct->CaptureLoad = DISABLE;

    /* Initialize the counter reset on capture event 4 */
    ECAP_InitStruct->CaptureEvent4Reset = DISABLE;

    /* Initialize the counter reset on capture event 3 */
    ECAP_InitStruct->CaptureEvent3Reset = DISABLE;

    /* Initialize the counter reset on capture event 2 */
    ECAP_InitStruct->CaptureEvent2Reset = DISABLE;

    /* Initialize the counter reset on capture event 1 */
    ECAP_InitStruct->CaptureEvent1Reset = DISABLE;

    /* Initialize the polarity of capture event 4 */
    ECAP_InitStruct->CaptureEvent4Polarity = ECAP_EVENT_POLARITY_RE;

    /* Initialize the polarity of capture event 3 */
    ECAP_InitStruct->CaptureEvent3Polarity = ECAP_EVENT_POLARITY_RE;

    /* Initialize the polarity of capture event 2 */
    ECAP_InitStruct->CaptureEvent2Polarity = ECAP_EVENT_POLARITY_RE;

    /* Initialize the polarity of capture event 1 */
    ECAP_InitStruct->CaptureEvent1Polarity = ECAP_EVENT_POLARITY_RE;

    /* Initialize the polarity of the APWM output */
    ECAP_InitStruct->APWMPolarity = 0U;

    /* Initialize the counter Sync-In */
    ECAP_InitStruct->CounterSyncIn = DISABLE;

    /* Initialize the stop/wrap value of Mod counter */
    ECAP_InitStruct->ModCounterStopWrap = ECAP_STOP_WRAP_EVENT1;

    /* Initialize the mode of Mod counter to continuous mode */
    ECAP_InitStruct->ModCounterMode = ECAP_MOD_COUNTER_CONT;

    /* Initialize the phase value of counter */
    ECAP_InitStruct->CounterPhaseValue = 0U;
}


/**
  * @brief  DeInitialize the ECAP peripheral.
  * @retval None
  */
void ECAP_DeInit()
{

    /* Enable ECAP reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PeriphRst_ECAP, ENABLE);

    /* Release ECAP from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PeriphRst_ECAP, DISABLE);

}


/**
  * @brief  Enables or disables the ECAP counter(TSCTR).
  * @param  NewState  New state of the ECAP counter.
  *                   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ECAP_Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the ECAP, TSCTR free-running */
        ECAP->ECCTL2 |= (uint32_t)ECAP_ECCTL2_TSCTRSTOP;
    }
    else
    {
        /* Disable the ECAP, TSCRT stopped */
        ECAP->ECCTL2 &= (uint32_t)(~ECAP_ECCTL2_TSCTRSTOP);
    }
}


/**
  * @brief  Re-Ariming control.
  * @Note   The re-arm function is valid in one-shot or continuous mode.
  *         Write 0 : Has no effect;
  *         Write 1 : Arms the one-shot sequence as follows:
  *                   +Resets the Mod4 counter to zero
  *                   +Unfreezes the Mod4 counter
  *                   +Enables capture register loads
  * @retval None
  */
void ECAP_ReArm()
{
    uint32_t tmpreg = 0;

    /* Get the ECCTL2 value */
    tmpreg = ECAP->ECCTL2;

    /* Config the REARM bit of ECCTL2 */
    tmpreg |= (uint32_t)ECAP_ECCTL2_REARM;

    /* Write to ECCTL2 */
    ECAP->ECCTL2 = tmpreg;
}


/**
  * @brief  Software-forced counter(TSCTR) synchronizer.
  *         This provides the user a method to generate a synchronization pulse
  *         through software.
  *         Write 0 : Has no effect;
  *         Write 1 : Forces a TSCTR shadow load of current ECAP module.
  * @retval None
  */
void ECAP_SoftwareForceSync()
{
    uint32_t tmpreg = 0;

    /* Get the ECCTL2 value */
    tmpreg = ECAP->ECCTL2;

    /* Force a TSCTR shadow load */
    tmpreg |= (uint32_t)ECAP_ECCTL2_SWSYNC;

    /* Write to ECCTL2 */
    ECAP->ECCTL2 = tmpreg;
}


/**
  * @brief  Write a value to the specified data register.
  * @param  ECAP_DATA_REG ECAP data registers.
  *                       @arg ECAP_DATA_REG_TSCTR  Counter register
  *                       @arg ECAP_DATA_REG_CTRPHS Counter phase offset register
  *                       @arg ECAP_DATA_REG_CAP1   Capture 1 register
  *                       @arg ECAP_DATA_REG_CAP2   Capture 2 register
  *                       @arg ECAP_DATA_REG_CAP3   Capture 3 register
  *                       @arg ECAP_DATA_REG_CAP4   Capture 4 register
  * @param  Value  The value of data register.
  * @retval None
  */
void ECAP_WriteDataRegister(uint8_t ECAP_DATA_REG, uint32_t Value)
{
    /* Check the parameters */
    assert_param(IS_ECAP_DATA_REG(ECAP_DATA_REG));

    if (ECAP_DATA_REG == ECAP_DATA_REG_TSCTR)
    {
        /* Write the value to TSCTR */
        ECAP->TSCTR = ((uint32_t)Value);
    }
    if (ECAP_DATA_REG == ECAP_DATA_REG_CTRPHS)
    {
        /* Write the value to CTRPHS */
        ECAP->CTRPHS = ((uint32_t)Value);
    }
    if (ECAP_DATA_REG == ECAP_DATA_REG_CAP1)
    {
        /* Write the value to CAP1 */
        ECAP->CAP1 = ((uint32_t)Value);
    }
    if (ECAP_DATA_REG == ECAP_DATA_REG_CAP2)
    {
        /* Write the value to CAP2 */
        ECAP->CAP2 = ((uint32_t)Value);
    }
    if (ECAP_DATA_REG == ECAP_DATA_REG_CAP3)
    {
        /* Write the value to CAP3 */
        ECAP->CAP3 = ((uint32_t)Value);
    }
    if (ECAP_DATA_REG == ECAP_DATA_REG_CAP4)
    {
        /* Write the value to CAP4 */
        ECAP->CAP4 = ((uint32_t)Value);
    }
}


/**
  * @brief  Returns the value of data registers.
  * @param  ECAP_DATA_REG ECAP data registers.
  *                       @arg ECAP_DATA_REG_TSCTR  Counter register
  *                       @arg ECAP_DATA_REG_CTRPHS Counter phase offset register
  *                       @arg ECAP_DATA_REG_CAP1   Capture 1 register
  *                       @arg ECAP_DATA_REG_CAP2   Capture 2 register
  *                       @arg ECAP_DATA_REG_CAP3   Capture 3 register
  *                       @arg ECAP_DATA_REG_CAP4   Capture 4 register
  * @retval The value of data registers.
  */
uint32_t ECAP_GetDataRegister(uint8_t ECAP_DATA_REG)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_ECAP_DATA_REG(ECAP_DATA_REG));

    if (ECAP_DATA_REG == ECAP_DATA_REG_TSCTR)
    {
        /* Get the value of TSCTR */
        tmpreg = ((uint32_t)(ECAP->TSCTR));
    }
    if (ECAP_DATA_REG == ECAP_DATA_REG_CTRPHS)
    {
        /* Get the value of CTRPHS */
        tmpreg = ((uint32_t)(ECAP->CTRPHS));
    }
    if (ECAP_DATA_REG == ECAP_DATA_REG_CAP1)
    {
        /* Get the value of CAP1 */
        tmpreg = ((uint32_t)(ECAP->CAP1));
    }
    if (ECAP_DATA_REG == ECAP_DATA_REG_CAP2)
    {
        /* Get the value of CAP2 */
        tmpreg = ((uint32_t)(ECAP->CAP2));
    }
    if (ECAP_DATA_REG == ECAP_DATA_REG_CAP3)
    {
        /* Get the value of CAP3 */
        tmpreg = ((uint32_t)(ECAP->CAP3));
    }
    if (ECAP_DATA_REG == ECAP_DATA_REG_CAP4)
    {
        /* Get the value of CAP4 */
        tmpreg = ((uint32_t)(ECAP->CAP4));
    }

    /* Return the value of data register */
    return tmpreg;
}


/**
  * @brief  Enable the specified ECAP interrupts.
  * @param  ECAP_IT specifies the ECAP interrupt sources to be enabled or disabled.
  *                 This parameter can be any combination of the following values:
  *                 @arg ECAP_IT_CEVT1   Capture event 1 interrupt
  *                 @arg ECAP_IT_CEVT2   Capture event 2 interrupt
  *                 @arg ECAP_IT_CEVT3   Capture event 3 interrupt
  *                 @arg ECAP_IT_CEVT4   Capture event 4 interrupt
  *                 @arg ECAP_IT_CTROVF  Counter overflow interrupt
  *                 @arg ECAP_IT_CTRPRD  Counter equal period interrupt
  *                 @arg ECAP_IT_CTRCMP  Counter equal compare interrupt
  * @param  NewState  new state of the specified ECAP interrupt.
  *                   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ECAP_ITConfig(uint8_t ECAP_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ECAP_IT(ECAP_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));


    if (NewState != DISABLE)
    {
        /* Enable the selected ECAP interrupts */
        ECAP->ECEINT |= ECAP_IT;
    }
    else
    {
        /* Disable the selected ECAP interrupts */
        ECAP->ECEINT &= ~ECAP_IT;
    }
}


/**
  * @brief  Clears the ECAP interrupt flags.
  * @param  ECAP_FLAG  specifies the ECAP interrupt flag to clear.
  *                    This parameter can be one of the following values:
  *                    @arg ECAP_FLAG_INT     ECAP global interrupt flag
  *                    @arg ECAP_FLAG_CEVT1   Capture event 1 interrupt flag
  *                    @arg ECAP_FLAG_CEVT2   Capture event 2 interrupt flag
  *                    @arg ECAP_FLAG_CEVT3   Capture event 3 interrupt flag
  *                    @arg ECAP_FLAG_CEVT4   Capture event 3 interrupt flag
  *                    @arg ECAP_FLAG_CTROVF  Counter overflow interrupt flag
  *                    @arg ECAP_FLAG_CTRPRD  Counter equal period interrupt flag
  *                    @arg ECAP_FLAG_CTRCMP  Counter equal compare interrupt flag
  * @retval None
  */
void ECAP_ClearFlag(uint8_t  ECAP_FLAG)
{
    /* Check the parameters */
    assert_param(IS_ECAP_FLAG(ECAP_FLAG));

    /* Clear the selected ECAP flags */
    ECAP->ECCLR = ECAP_FLAG;
}


/**
  * @brief  Force the specified ECAP interrupt.
  * @param  ECAP_IT specifies the ECAP interrupt sources to be enabled or disabled.
  *                 This parameter can be any combination of the following values:
  *                 @arg ECAP_IT_CEVT1   Capture event 1 interrupt
  *                 @arg ECAP_IT_CEVT2   Capture event 2 interrupt
  *                 @arg ECAP_IT_CEVT3   Capture event 3 interrupt
  *                 @arg ECAP_IT_CEVT4   Capture event 4 interrupt
  *                 @arg ECAP_IT_CTROVF  Counter overflow interrupt
  *                 @arg ECAP_IT_CTRPRD  Counter equal period interrupt
  *                 @arg ECAP_IT_CTRCMP  Counter equal compare interrupt
  * @retval None
  */
void ECAP_ITForce(uint8_t ECAP_IT)
{
    /* Check the parameters */
    assert_param(IS_ECAP_IT(ECAP_IT));

    /* Force the selected ECAP interrupt */
    ECAP->ECFRC = ECAP_IT;
}

/**
  * @brief  Checks whether the specified ECAP interrupt has occurred or not.
  * @param  ECAP_IT specifies the ECAP interrupt sources to check.
  *                 This parameter can be any combination of the following values:
  *                 @arg ECAP_IT_CEVT1   Capture event 1 interrupt
  *                 @arg ECAP_IT_CEVT2   Capture event 2 interrupt
  *                 @arg ECAP_IT_CEVT3   Capture event 3 interrupt
  *                 @arg ECAP_IT_CEVT4   Capture event 4 interrupt
  *                 @arg ECAP_IT_CTROVF  Counter overflow interrupt
  *                 @arg ECAP_IT_CTRPRD  Counter equal period interrupt
  *                 @arg ECAP_IT_CTRCMP  Counter equal compare interrupt
  * @retval The new state of ECAP_IT (SET or RESET).
  */
ITStatus ECAP_GetITStatus(uint8_t ECAP_IT)
{
    /* Check the parameters */
    assert_param(IS_ECAP_IT(ECAP_IT));


    ITStatus bitstatus = RESET;

    /* Check the status of the specified ECAP interrupt */
    if ((uint32_t)(ECAP->ECEINT & ECAP_IT) != (uint32_t)RESET)
    {
        /* ECAP_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* ECAP_IT is reset */
        bitstatus = RESET;
    }
    /* Return the ECAP_IT status */
    return  bitstatus;
}



/**
  * @brief  Checks whether the specified ECAP flag has occurred or not.
  * @param  ECAP_FLAG specifies the ECAP flag to check.
  *                 This parameter can be any combination of the following values:
  *                 @arg ECAP_FLAG_INT     ECAP global interrupt flag
  *                 @arg ECAP_FLAG_CEVT1   Capture event 1 interrupt flag
  *                 @arg ECAP_FLAG_CEVT2   Capture event 2 interrupt flag
  *                 @arg ECAP_FLAG_CEVT3   Capture event 3 interrupt flag
  *                 @arg ECAP_FLAG_CEVT4   Capture event 4 interrupt flag
  *                 @arg ECAP_FLAG_CTROVF  Counter overflow interrupt flag
  *                 @arg ECAP_FLAG_CTRPRD  Counter equal period interrupt flag
  *                 @arg ECAP_FLAG_CTRCMP  Counter equal compare interrupt flag
  * @retval The new state of ECAP_FLAG (SET or RESET).
  */
FlagStatus ECAP_GetFlagStatus(uint8_t ECAP_FLAG)
{
    /* Check the parameters */
    assert_param(IS_ECAP_FLAG(ECAP_FLAG));


    FlagStatus bitstatus = RESET;

    /* Check the status of the specified ECAP interrupt */
    if ((uint32_t)(ECAP->ECFLG & ECAP_FLAG) != (uint32_t)RESET)
    {
        /* ECAP_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ECAP_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the ECAP_FLAG status */
    return  bitstatus;
}





/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
