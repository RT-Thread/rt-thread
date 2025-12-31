/**
  ******************************************************************************
  * @file    ft32f4xx_tim.c
  * @author  FMD AE
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the TIM peripheral:
  *          + TimeBase management
  *          + Advanced-control timers specific features
  *          + Output Compare management
  *          + Input Capture management
  *          + Interrupts, DMA and flags management
  *          + Clocks management
  *          + Synchronization management
  *          + Specific interface management
  *          + Specific remapping management
  * @version V1.0.0
  * @date    2025-04-07
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_tim.h"
#include "ft32f4xx_rcc.h"


/* ------------------------ TIM registers bit mask -------------------------- */
#define SMCR_ETR_MASK               ((uint32_t)0x000000FF)
#define CCMR_OFFSET                 ((uint32_t)0x00000018)
#define CCER_CCE_SET                ((uint32_t)0x00000001)
#define CCER_CCNE_SET               ((uint32_t)0x00000004)


static void TI1_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter);
static void TI2_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter);
static void TI3_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter);
static void TI4_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter);

/**
  * @brief  Deinitializes the TIMx peripheral registers to their default reset values.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @retval None
  *
  */
void TIM_DeInit(TIM_TypeDef* TIMx)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    if (TIMx == TIM1)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);
    }
    else if (TIMx == TIM2)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
    }
    else if (TIMx == TIM3)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, DISABLE);
    }
    else if (TIMx == TIM4)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);
    }
    else if (TIMx == TIM5)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, DISABLE);
    }
    else if (TIMx == TIM6)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
    }
    else if (TIMx == TIM7)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, DISABLE);
    }
    else if (TIMx == TIM8)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, DISABLE);
    }
    else if (TIMx == TIM9)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, DISABLE);
    }
    else if (TIMx == TIM10)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM10, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM10, DISABLE);
    }
    else if (TIMx == TIM11)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM11, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM11, DISABLE);
    }
    else if (TIMx == TIM12)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, DISABLE);
    }
    else if (TIMx == TIM13)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13, DISABLE);
    }
    else
    {
        if (TIMx == TIM14)
        {
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, ENABLE);
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, DISABLE);
        }
    }
}

/**
  * @brief  Initializes the TIMx Time Base Unit peripheral according to
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef
  *         structure that contains the configuration information for
  *         the specified TIM peripheral.
  * @retval None
  */
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
    uint32_t tmpcr1 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_COUNTER_MODE(TIM_TimeBaseInitStruct->TIM_CounterMode));
    assert_param(IS_TIM_CKD_DIV(TIM_TimeBaseInitStruct->TIM_ClockDivision));

    tmpcr1 = TIMx->CR1;

    if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) ||
            (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
    {
        /* Select the Counter Mode */
        tmpcr1 &= (uint32_t)(~((uint32_t)(TIM_CR1_DIR | TIM_CR1_CMS)));
        tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_CounterMode;
    }

    if ((TIMx != TIM6) || (TIMx != TIM7))
    {
        /* Set the clock division */
        tmpcr1 &= (uint32_t)(~((uint32_t)TIM_CR1_CKD));
        tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_ClockDivision;
    }

    TIMx->CR1 = tmpcr1;

    /* Set the Autoreload value */
    TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period ;

    /* Set the Prescaler value */
    TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        /* Set the Repetition Counter value */
        TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
    }

    /* Generate an update event to reload the Prescaler and the Repetition counter
       values immediately */
    TIMx->EGR = TIM_PSCReloadMode_Immediate;
}

/**
  * @brief  Fills each TIM_TimeBaseInitStruct member with its default value.
  * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
    /* Set the default configuration */
    TIM_TimeBaseInitStruct->TIM_Period            = 0xFFFFFFFF;
    TIM_TimeBaseInitStruct->TIM_Prescaler         = 0x0000;
    TIM_TimeBaseInitStruct->TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct->TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct->TIM_RepetitionCounter = 0x0000;
}

/**
  * @brief  Configures the TIMx Prescaler.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @param  Prescaler: specifies the Prescaler Register value
  * @param  TIM_PSCReloadMode: specifies the TIM Prescaler Reload mode
  *          This parameter can be one of the following values:
  *            @arg TIM_PSCReloadMode_Update   : The Prescaler is loaded at the update event.
  *            @arg TIM_PSCReloadMode_Immediate: The Prescaler is loaded immediatly.
  * @retval None
  */
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint32_t Prescaler, uint32_t TIM_PSCReloadMode)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_PRESCALER_RELOAD(TIM_PSCReloadMode));

    /* Set the Prescaler value */
    TIMx->PSC = Prescaler;
    /* Set or reset the UG Bit */
    TIMx->EGR = TIM_PSCReloadMode;
}

/**
  * @brief  Specifies the TIMx Counter Mode to be used.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_CounterMode: specifies the Counter Mode to be used
  *          This parameter can be one of the following values:
  *            @arg TIM_CounterMode_Up            : TIM Up Counting Mode
  *            @arg TIM_CounterMode_Down          : TIM Down Counting Mode
  *            @arg TIM_CounterMode_CenterAligned1: TIM Center Aligned Mode1
  *            @arg TIM_CounterMode_CenterAligned2: TIM Center Aligned Mode2
  *            @arg TIM_CounterMode_CenterAligned3: TIM Center Aligned Mode3
  * @retval None
  */
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint32_t TIM_CounterMode)
{
    uint32_t tmpcr1 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_COUNTER_MODE(TIM_CounterMode));
    tmpcr1 = TIMx->CR1;

    /* Reset the CMS and DIR Bits */
    tmpcr1 &= (uint32_t)(~((uint32_t)(TIM_CR1_DIR | TIM_CR1_CMS)));

    /* Set the Counter Mode */
    tmpcr1 |= TIM_CounterMode;

    /* Write to TIMx CR1 register */
    TIMx->CR1 = tmpcr1;
}

/**
  * @brief  Sets the TIMx Counter Register value
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @param  Counter: specifies the Counter register new value.
  * @retval None
  */
void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    /* Set the Counter Register value */
    TIMx->CNT = Counter;
}

/**
  * @brief  Sets the TIMx Autoreload Register value
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @param  Autoreload: specifies the Autoreload register new value.
  * @retval None
  */
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint32_t Autoreload)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    /* Set the Autoreload Register value */
    TIMx->ARR = Autoreload;
}

/**
  * @brief  Sets the TIMx RepetitionCounter Register value
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  RepetitionCounter: specifies the RepetitionCounter register new value.
  * @retval None
  */
void TIM_SetRepetitionCounter(TIM_TypeDef* TIMx, uint32_t RepetitionCounter)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));

    /* Set the RepetitionCounter Register value */
    TIMx->RCR = RepetitionCounter;
}

/**
  * @brief  Gets the TIMx Counter value.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @retval Counter Register value.
  */
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    /* Get the Counter Register value */
    return TIMx->CNT;
}

/**
  * @brief  Gets the TIMx Prescaler value.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @retval Prescaler Register value.
  */
uint32_t TIM_GetPrescaler(TIM_TypeDef* TIMx)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    /* Get the Prescaler Register value */
    return TIMx->PSC;
}

/**
  * @brief  Enables or Disables the TIMx Update event.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @param  NewState: new state of the TIMx UDIS bit
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the Update Disable Bit */
        TIMx->CR1 |= TIM_CR1_UDIS;
    }
    else
    {
        /* Reset the Update Disable Bit */
        TIMx->CR1 &= (uint32_t)~((uint32_t)TIM_CR1_UDIS);
    }
}

/**
  * @brief  Configures the TIMx Update Request Interrupt source.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @param  TIM_UpdateSource: specifies the Update source.
  *          This parameter can be one of the following values:
  *            @arg TIM_UpdateSource_Global : Source of update is the counter overflow/underflow
  *                                           or the setting of UG bit, or an update generation
  *                                           through the slave mode controller.
  *            @arg TIM_UpdateSource_Regular: Source of update is counter overflow/underflow.
  * @retval None
  */
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint32_t TIM_UpdateSource)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_UPDATE_SOURCE(TIM_UpdateSource));

    if (TIM_UpdateSource != TIM_UpdateSource_Global)
    {
        /* Set the URS Bit */
        TIMx->CR1 |= TIM_CR1_URS;
    }
    else
    {
        /* Reset the URS Bit */
        TIMx->CR1 &= (uint32_t)~((uint32_t)TIM_CR1_URS);
    }
}

/**
  * @brief  Enables or disables TIMx peripheral Preload register on ARR.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @param  NewState: new state of the TIMx peripheral Preload register
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the ARR Preload Bit */
        TIMx->CR1 |= TIM_CR1_ARPE;
        TIMx->EGR |= TIM_EGR_UG;
        TIMx->SR &= (uint32_t)~((uint32_t)TIM_SR_UIF);
    }
    else
    {
        /* Reset the ARR Preload Bit */
        TIMx->CR1 &= (uint32_t)~((uint32_t)TIM_CR1_ARPE);
    }
}

/**
  * @brief  Selects the TIMx's One Pulse Mode.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @param  TIM_OPMode: specifies the OPM Mode to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM_OPMode_Single
  *            @arg TIM_OPMode_Repetitive
  * @retval None
  */
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint32_t TIM_OPMode)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_OPM_MODE(TIM_OPMode));

    /* Reset the OPM Bit */
    TIMx->CR1 &= (uint32_t)~((uint32_t)TIM_CR1_OPM);

    /* Configure the OPM Mode */
    TIMx->CR1 |= TIM_OPMode;
}

/**
  * @brief  Sets the TIMx Clock Division value.
  * @param  TIMx: where x can be  1, 2, 3, 4, 5, 8, 9, 10, 11, 12,
  *         13 and 14 to select the TIM peripheral.
  * @param  TIM_CKD: specifies the clock division value.
  *          This parameter can be one of the following value:
  *            @arg TIM_CKD_DIV1: TDTS = 1*Tck_tim
  *            @arg TIM_CKD_DIV2: TDTS = 2*Tck_tim
  *            @arg TIM_CKD_DIV4: TDTS = 4*Tck_tim
  * @retval None
  */
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint32_t TIM_CKD)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_CKD_DIV(TIM_CKD));

    /* Reset the CKD Bits */
    TIMx->CR1 &= (uint32_t)~((uint32_t)TIM_CR1_CKD);

    /* Set the CKD value */
    TIMx->CR1 |= TIM_CKD;
}

/**
  * @brief  Enables or disables the specified TIM peripheral.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @param  NewState: new state of the TIMx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the TIM Counter */
        TIMx->CR1 |= TIM_CR1_CEN;
    }
    else
    {
        /* Disable the TIM Counter */
        TIMx->CR1 &= (uint32_t)(~((uint32_t)TIM_CR1_CEN));
    }
}

/**
  * @}
  */

/**
  * @brief  Configures the: Break feature, dead time, Lock level, OSSI/OSSR State
  *         and the AOE(automatic output enable).
  * @param  TIMx: where x can be  1 or 8 to select the TIM
  * @param  TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef structure that
  *         contains the BDTR Register configuration information for the TIM peripheral.
  * @retval None
  */
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef* TIM_BDTRInitStruct)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_DEADTIME(TIM_BDTRInitStruct->TIM_DeadTime));
    assert_param(IS_TIM_LOCK_LEVEL(TIM_BDTRInitStruct->TIM_LOCKLevel));
    assert_param(IS_TIM_OSSI_STATE(TIM_BDTRInitStruct->TIM_OSSIState));
    assert_param(IS_TIM_OSSR_STATE(TIM_BDTRInitStruct->TIM_OSSRState));
    assert_param(IS_TIM_BREAK_STATE(TIM_BDTRInitStruct->TIM_Break));
    assert_param(IS_TIM_BREAK_POLARITY(TIM_BDTRInitStruct->TIM_BreakPolarity));
    assert_param(IS_TIM_AUTOMATIC_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_AutomaticOutput));
    assert_param(IS_TIM_BREAK_FILTER(TIM_BDTRInitStruct->TIM_BreakFilter));
    assert_param(IS_TIM_BREAK_BID_MODE(TIM_BDTRInitStruct->TIM_BreakBIDMode));
    assert_param(IS_TIM_CONTROL_PWM_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_CtrlPWMOutput));

    /* Set the Lock level LOCK[1:0], the Break enable Bit BKE and the Ploarity BKP, the OSSR State,
       the OSSI State, the dead time value DTG[7:0], the Automatic Output Enable Bit AOE, the Break
       Filter BKF[3:0], output control MOE bit and the bidirectional function mode of break input
       bit BKBID */
    TIMx->BDTR  = (uint32_t)TIM_BDTRInitStruct->TIM_DeadTime                       |
                  TIM_BDTRInitStruct->TIM_LOCKLevel                      |
                  TIM_BDTRInitStruct->TIM_OSSIState                      |
                  TIM_BDTRInitStruct->TIM_OSSRState                      |
                  TIM_BDTRInitStruct->TIM_Break                          |
                  TIM_BDTRInitStruct->TIM_BreakPolarity                  |
                  TIM_BDTRInitStruct->TIM_AutomaticOutput                |
                  TIM_BDTRInitStruct->TIM_CtrlPWMOutput                  |
                  ((TIM_BDTRInitStruct->TIM_BreakFilter) << (uint32_t)16) |
                  TIM_BDTRInitStruct->TIM_BreakBIDMode                   ;
}

/**
  * @brief  Fills each TIM_BDTRInitStruct member with its default value.
  * @param  TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef structure which
  *         will be initialized.
  * @retval None
  */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct)
{
    /* Set the default configuration */
    TIM_BDTRInitStruct->TIM_DeadTime        = 0x00;
    TIM_BDTRInitStruct->TIM_LOCKLevel       = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStruct->TIM_OSSIState       = TIM_OSSIState_Disable;
    TIM_BDTRInitStruct->TIM_OSSRState       = TIM_OSSRState_Disable;
    TIM_BDTRInitStruct->TIM_Break           = TIM_Break_Disable;
    TIM_BDTRInitStruct->TIM_BreakPolarity   = TIM_BreakPolarity_Low;
    TIM_BDTRInitStruct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
    TIM_BDTRInitStruct->TIM_BreakFilter     = 0x0;
    TIM_BDTRInitStruct->TIM_BreakBIDMode    = TIM_Break_Bid_MODE_INPUT;
}

/**
  * @brief  Configures the: Break feature, dead time, Lock level, OSSI/OSSR State
  *         and the AOE(automatic output enable).
  * @param  TIMx: where x can be  1 or 8 to select the TIM
  * @param  TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef structure that
  *         contains the BDTR Register configuration  information for the TIM peripheral.
  * @retval None
  */

/**
  * @brief  Configures the break input source.
  * @param  TIMx: where x can be  1 or 8 to select the TIM
  * @param  BreakInputConfig: pointer to a TIMx_BreakInputConfigTypeDef structure that
  *         contains the AF1 Register Break input source configuration information for
  *         the TIM peripheral.
  *
  *         There are three instance variables in BreakInputConfig as follows:
  *
  *   -     TIM_Break_Input_Source: specifies the source of the timer break input.
  *          This parameter can be one of the following value:
  *            @arg TIM_BREAKINPUTSOURCE_BKIN : An external source (GPIO) is connected to the BKIN pin
  *            @arg TIM_BREAKINPUTSOURCE_COMP1: The COMP1 output is connected to the break input
  *            @arg TIM_BREAKINPUTSOURCE_COMP2: The COMP2 output is connected to the break input
  *            @arg TIM_BREAKINPUTSOURCE_COMP3: The COMP3 output is connected to the break input
  *            @arg TIM_BREAKINPUTSOURCE_COMP4: The COMP4 output is connected to the break input
  *            @arg TIM_BREAKINPUTSOURCE_COMP5: The COMP5 output is connected to the break input
  *            @arg TIM_BREAKINPUTSOURCE_COMP6: The COMP6 output is connected to the break input
  *
  *   -     TIM_Enable: specifies whether or not the break input source is enabled.
  *          This parameter can be one of the following value:
  *            @arg TIM_BREAKINPUTSOURCE_DISABLE: Break input source is disabled
  *            @arg TIM_BREAKINPUTSOURCE_ENABLE : Break input source is enabled
  *
  *   -     TIM_Polarity: specifies the break input source polarity.
  *          This parameter can be one of the following value:
  *            @arg TIM_BREAKINPUTSOURCE_POLARITY_INVERTED    : Break input source is inverted
  *                                                             (active high if BKP = 0, active low if BKP = 1)
  *            @arg TIM_BREAKINPUTSOURCE_POLARITY_NOT_INVERTED: Break input source is not inverted
  *                                                             (active low if BKP = 0, active high if BKP = 1)
  *
  * @retval None
  */
void TIM_ConfigBreakInput(TIM_TypeDef* TIMx, TIM_BreakInputConfigTypeDef* BreakInputConfig)

{
    uint32_t tmporx;
    uint32_t bkin_enable_mask;
    uint32_t bkin_polarity_mask;
    uint32_t bkin_enable_bitpos;
    uint32_t bkin_polarity_bitpos;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_BREAKINPUTSOURCE(BreakInputConfig->TIM_Source));
    assert_param(IS_TIM_BREAKINPUTSOURCE_STATE(BreakInputConfig->TIM_Enable));
    assert_param(IS_TIM_BREAKINPUTSOURCE_POLARITY(BreakInputConfig->TIM_Polarity));

    switch (BreakInputConfig->TIM_Source)
    {
    case TIM_BREAKINPUTSOURCE_BKIN:
    {
        bkin_enable_mask     = TIM_AF_BKINE;
        bkin_enable_bitpos   = TIM_AF_BKINE_Pos;
        bkin_polarity_mask   = TIM_AF_BKINP;
        bkin_polarity_bitpos = TIM_AF_BKINP_Pos;
        break;
    }
    case TIM_BREAKINPUTSOURCE_COMP1:
    {
        bkin_enable_mask     = TIM_AF_BKCMP1E;
        bkin_enable_bitpos   = TIM_AF_BKCMP1E_Pos;
        bkin_polarity_mask   = TIM_AF_BKCMP1P;
        bkin_polarity_bitpos = TIM_AF_BKCMP1P_Pos;
        break;
    }
    case TIM_BREAKINPUTSOURCE_COMP2:
    {
        bkin_enable_mask     = TIM_AF_BKCMP2E;
        bkin_enable_bitpos   = TIM_AF_BKCMP2E_Pos;
        bkin_polarity_mask   = TIM_AF_BKCMP2P;
        bkin_polarity_bitpos = TIM_AF_BKCMP2P_Pos;
        break;
    }
    case TIM_BREAKINPUTSOURCE_COMP3:
    {
        bkin_enable_mask     = TIM_AF_BKCMP3E;
        bkin_enable_bitpos   = TIM_AF_BKCMP3E_Pos;
        bkin_polarity_mask   = TIM_AF_BKCMP3P;
        bkin_polarity_bitpos = TIM_AF_BKCMP3P_Pos;
        break;
    }
    case TIM_BREAKINPUTSOURCE_COMP4:
    {
        bkin_enable_mask     = TIM_AF_BKCMP4E;
        bkin_enable_bitpos   = TIM_AF_BKCMP4E_Pos;
        bkin_polarity_mask   = TIM_AF_BKCMP4P;
        bkin_polarity_bitpos = TIM_AF_BKCMP4P_Pos;
        break;
    }
    case TIM_BREAKINPUTSOURCE_COMP5:
    {
        bkin_enable_mask     = TIM_AF_BKCMP5E;
        bkin_enable_bitpos   = TIM_AF_BKCMP5E_Pos;
        /* No palarity bit for this COMP. Variable bkin_polarity_mask keeps its default value 0 */
        bkin_polarity_mask   = 0U;
        bkin_polarity_bitpos = 0U;
        break;
    }
    case TIM_BREAKINPUTSOURCE_COMP6:
    {
        bkin_enable_mask     = TIM_AF_BKCMP6E;
        bkin_enable_bitpos   = TIM_AF_BKCMP6E_Pos;
        /* No palarity bit for this COMP. Variable bkin_polarity_mask keeps its default value 0 */
        bkin_polarity_mask   = 0U;
        bkin_polarity_bitpos = 0U;
        break;
    }
    default:
    {
        bkin_enable_mask     = 0U;
        bkin_polarity_mask   = 0U;
        bkin_enable_bitpos   = 0U;
        bkin_polarity_bitpos = 0U;
        break;
    }
    }

    /* Get the TIMx_AF1 register value */
    tmporx = TIMx->AF1;

    /* Enable the break input */
    tmporx &= ~bkin_enable_mask;
    tmporx |= (BreakInputConfig->TIM_Enable << bkin_enable_bitpos) & bkin_enable_mask;

    /* Set the break input polarity */
    tmporx &= ~bkin_polarity_mask;
    tmporx |= (BreakInputConfig->TIM_Polarity << bkin_polarity_bitpos) & bkin_polarity_mask;

    /* Set TIMx_AF1 */
    TIMx->AF1 = tmporx;
}

/**
  * @brief  Enables or disables the TIM peripheral Main Outputs.
  * @param  TIMx: where x can be 1 or 8 to select the TIMx peripheral.
  * @param  NewState: new state of the TIM peripheral Main Outputs.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the TIM Main Output */
        TIMx->BDTR |= TIM_BDTR_MOE;
    }
    else
    {
        /* Disable the TIM Main Output */
        TIMx->BDTR &= (uint32_t)(~((uint32_t)TIM_BDTR_MOE));
    }
}

/**
  * @brief  Disarm the designated break input (when it operates in bidirectional mode).
  * @param  TIMx: where x can be 1 or 8 to select the TIMx peripheral.
  * @note   The break input can be disarmed only when it is configured in
  *         bidirectional mode and when when MOE is reset.
  * @note   Purpose is to be able to have the input voltage back to high-state,
  *         whatever the time constant on the output.
  * @retval None
  */
void TIM_DisarmBreakInput(TIM_TypeDef* TIMx)
{
    uint32_t tmpbdtr;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));

    /* Check initial conditions */
    tmpbdtr = TIMx->BDTR;

    if ((((TIMx->BDTR)&TIM_BDTR_BKBID) == TIM_BDTR_BKBID) &&
            (((TIMx->BDTR)&TIM_BDTR_MOE) != TIM_BDTR_MOE))
    {
        /* Break input BRK is disarmed */
        TIMx->BDTR |= TIM_BDTR_BKDSRM;
    }
}

/**
  * @brief  Wait the BKDSRM bit is cleared by hardware when no break source active
  *         (when it operates in bidirectional mode).
  * @param  TIMx: where x can be 1 or 8 to select the TIMx peripheral.
  * @note   The BKDSRM bit is cleared by hardware when no break source active.
  * @retval The new state of BKDSRM (SET or RESET).
  */
FlagStatus TIM_WaitBkdsrmIsHardwareClear(TIM_TypeDef* TIMx)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));

    /* Check initial conditions */
    if (((TIMx->BDTR)&TIM_BDTR_BKBID) == TIM_BDTR_BKBID)
    {
        /* Break input BRK is re-armed automatically by hardware. Poll to check whether fault condition disappeared */
        if ((TIMx->BDTR & TIM_BDTR_BKDSRM) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    return bitstatus;
}

/**
  * @}
  */

/**
  * @brief  Initializes the TIMx Channel1 according to the specified
  *         parameters in the TIM_OCInitStruct.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13
  *         and 14 to select the TIM peripheral.
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM
  *         peripheral.
  * @retval None
  */
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
    uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

    /* Disable the Channel 1: Reset the CC1E Bit */
    TIMx->CCER &= (uint32_t)(~(uint32_t)TIM_CCER_CC1E);

    /* Get the TIMx CCER register value */
    tmpccer = TIMx->CCER;

    /* Get the TIMx CR2 register value */
    tmpcr2  =  TIMx->CR2;

    /* Get the TIMx CCMR1 register value */
    tmpccmrx = TIMx->CCMR1;

    /* Reset the Output Compare Mode Bits */
    tmpccmrx &= (uint32_t)(~((uint32_t)TIM_CCMR1_OC1M));
    tmpccmrx &= (uint32_t)(~((uint32_t)TIM_CCMR1_CC1S));
    /* Select the Output Compare Mode */
    tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;

    /* Reset the Output Polarity level */
    tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC1P));
    /* Set the Output Compare Polarity */
    tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;

    /* Set the Output State */
    tmpccer |= TIM_OCInitStruct->TIM_OutputState;

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
        assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
        assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

        /* Reset the Output N Polarity level */
        tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC1NP));
        /* Set the Output N Polarity */
        tmpccer |= TIM_OCInitStruct->TIM_OCNPolarity;

        /* Reset the Output N State */
        tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC1NE));
        /* Set the Output N State */
        tmpccer |= TIM_OCInitStruct->TIM_OutputNState;

        /* Reset the Ouput Compare and Output Compare N IDLE State */
        tmpcr2 &= (uint32_t)(~((uint32_t)TIM_CR2_OIS1));
        tmpcr2 &= (uint32_t)(~((uint32_t)TIM_CR2_OIS1N));
        /* Set the Output Idle state */
        tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;
        /* Set the Output N Idle state */
        tmpcr2 |= TIM_OCInitStruct->TIM_OCNIdleState;
    }
    /* Write to TIMx CR2 */
    TIMx->CR2 = tmpcr2;

    /* Set the Capture Compare Register value */
    if (((TIMx->CCMR1)&TIM_CCMR1_OC1PE) != TIM_CCMR1_OC1PE)
    {
        TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse;
    }
    else if (((TIMx->CCMR1)&TIM_CCMR1_OC1PE) == TIM_CCMR1_OC1PE)
    {
        TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse;
        TIMx->EGR |= TIM_EGR_UG;
        TIMx->SR &= (uint32_t)~((uint32_t)TIM_SR_UIF);
    }

    /* Write to TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmrx;

    /* Write to TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Initializes the TIMx Channel2 according to the specified
  *         parameters in the TIM_OCInitStruct.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select
  *         the TIM peripheral.
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM
  *         peripheral.
  *
  * @retval None
  */
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
    uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

    /* Disable the Channel 2: Reset the CC2E Bit */
    TIMx->CCER &= (uint32_t)(~((uint32_t)TIM_CCER_CC2E));

    /* Get the TIMx CCER register value */
    tmpccer = TIMx->CCER;

    /* Get the TIMx CR2 register value */
    tmpcr2 =  TIMx->CR2;

    /* Get the TIMx CCMR1 register value */
    tmpccmrx = TIMx->CCMR1;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    tmpccmrx &= (uint32_t)(~((uint32_t)TIM_CCMR1_OC2M));
    tmpccmrx &= (uint32_t)(~((uint32_t)TIM_CCMR1_CC2S));

    /* Select the Output Compare Mode */
    tmpccmrx |= (uint32_t)(TIM_OCInitStruct->TIM_OCMode << 8);

    /* Reset the Output Polarity level */
    tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC2P));
    /* Set the Output Compare Polarity */
    tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCPolarity << 4);

    /* Set the Output State */
    tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputState << 4);

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        /* Check the parameters */
        assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
        assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
        assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

        /* Reset the Output N Polarity level */
        tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC2NP));
        /* Set the Output N Polarity */
        tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCNPolarity << 4);

        /* Reset the Output N State */
        tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC2NE));
        /* Set the Output N State */
        tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputNState << 4);

        /* Reset the Output Compare N IDLE State */
        tmpcr2 &= (uint32_t)(~((uint32_t)TIM_CR2_OIS2));
        tmpcr2 &= (uint32_t)(~((uint32_t)TIM_CR2_OIS2N));
        /* Set the Output Idle state */
        tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCIdleState << 2);
        /* Set the Output N Idle state */
        tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCNIdleState << 2);
    }
    /* Write to TIMx CR2 */
    TIMx->CR2 = tmpcr2;

    /* Set the Capture Compare Register value */
    if (((TIMx->CCMR1)&TIM_CCMR1_OC2PE) != TIM_CCMR1_OC2PE)
    {
        TIMx->CCR2 = TIM_OCInitStruct->TIM_Pulse;
    }
    else if (((TIMx->CCMR1)&TIM_CCMR1_OC2PE) == TIM_CCMR1_OC2PE)
    {
        TIMx->CCR2 = TIM_OCInitStruct->TIM_Pulse;
        TIMx->EGR |= TIM_EGR_UG;
        TIMx->SR &= (uint32_t)~((uint32_t)TIM_SR_UIF);
    }

    /* Write to TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmrx;

    /* Write to TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Initializes the TIMx Channel3 according to the specified
  *         parameters in the TIM_OCInitStruct.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM
  *         peripheral.
  * @retval None
  */
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
    uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

    /* Disable the Channel 3: Reset the CC3E Bit */
    TIMx->CCER &= (uint32_t)(~((uint32_t)TIM_CCER_CC3E));

    /* Get the TIMx CCER register value */
    tmpccer = TIMx->CCER;

    /* Get the TIMx CR2 register value */
    tmpcr2 =  TIMx->CR2;

    /* Get the TIMx CCMR2 register value */
    tmpccmrx = TIMx->CCMR2;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    tmpccmrx &= (uint32_t)(~((uint32_t)TIM_CCMR2_OC3M));
    tmpccmrx &= (uint32_t)(~((uint32_t)TIM_CCMR2_CC3S));
    /* Select the Output Compare Mode */
    tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;

    /* Reset the Output Polarity level */
    tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC3P));
    /* Set the Output Compare Polarity */
    tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCPolarity << 8);

    /* Set the Output State */
    tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputState << 8);

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
        assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
        assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

        /* Reset the Output N Polarity level */
        tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC3NP));
        /* Set the Output N Polarity */
        tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCNPolarity << 8);

        /* Reset the Output N State */
        tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC3NE));
        /* Set the Output N State */
        tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputNState << 8);

        /* Reset the Ouput Compare and Output Compare N IDLE State */
        tmpcr2 &= (uint32_t)(~((uint32_t)TIM_CR2_OIS3));
        tmpcr2 &= (uint32_t)(~((uint32_t)TIM_CR2_OIS3N));
        /* Set the Output Idle state */
        tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCIdleState << 4);
        /* Set the Output N Idle state */
        tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCNIdleState << 4);
    }
    /* Write to TIMx CR2 */
    TIMx->CR2 = tmpcr2;

    /* Set the Capture Compare Register value */
    if (((TIMx->CCMR2)&TIM_CCMR2_OC3PE) != TIM_CCMR2_OC3PE)
    {
        TIMx->CCR3 = TIM_OCInitStruct->TIM_Pulse;
    }
    else if (((TIMx->CCMR2)&TIM_CCMR2_OC3PE) == TIM_CCMR2_OC3PE)
    {
        TIMx->CCR3 = TIM_OCInitStruct->TIM_Pulse;
        TIMx->EGR |= TIM_EGR_UG;
        TIMx->SR &= (uint32_t)~((uint32_t)TIM_SR_UIF);
    }

    /* Write to TIMx CCMR2 */
    TIMx->CCMR2 = tmpccmrx;

    /* Write to TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Initializes the TIMx Channel4 according to the specified
  *         parameters in the TIM_OCInitStruct.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM
  *         peripheral.
  * @retval None
  */
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
    uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

    /* Disable the Channel 4: Reset the CC4E Bit */
    TIMx->CCER &= (uint32_t)(~((uint32_t)TIM_CCER_CC4E));

    /* Get the TIMx CCER register value */
    tmpccer = TIMx->CCER;

    /* Get the TIMx CR2 register value */
    tmpcr2 =  TIMx->CR2;

    /* Get the TIMx CCMR2 register value */
    tmpccmrx = TIMx->CCMR2;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    tmpccmrx &= (uint32_t)(~((uint32_t)TIM_CCMR2_OC4M));
    tmpccmrx &= (uint32_t)(~((uint32_t)TIM_CCMR2_CC4S));

    /* Select the Output Compare Mode */
    tmpccmrx |= (uint32_t)(TIM_OCInitStruct->TIM_OCMode << 8);

    /* Reset the Output Polarity level */
    tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC4P));
    /* Set the Output Compare Polarity */
    tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCPolarity << 12);

    /* Set the Output State */
    tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputState << 12);

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

        /* Reset the Ouput Compare IDLE State */
        tmpcr2 &= (uint32_t)(~((uint32_t)TIM_CR2_OIS4));
        /* Set the Output Idle state */
        tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCIdleState << 6);
    }
    /* Write to TIMx CR2 */
    TIMx->CR2 = tmpcr2;

    /* Set the Capture Compare Register value */
    if (((TIMx->CCMR2)&TIM_CCMR2_OC4PE) != TIM_CCMR2_OC4PE)
    {
        TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;
    }
    else if (((TIMx->CCMR2)&TIM_CCMR2_OC4PE) == TIM_CCMR2_OC4PE)
    {
        TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;
        TIMx->EGR |= TIM_EGR_UG;
        TIMx->SR &= (uint32_t)~((uint32_t)TIM_SR_UIF);
    }

    /* Write to TIMx CCMR2 */
    TIMx->CCMR2 = tmpccmrx;

    /* Write to TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Initializes the TIMx Channel5 according to the specified
  *         parameters in the TIM_OCInitStruct.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM
  *         peripheral.
  * @retval None
  */
void TIM_OC5Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
    uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

    /* Disable the Channel 5: Reset the CC5E Bit */
    TIMx->CCER &= (uint32_t)(~((uint32_t)TIM_CCER_CC5E));

    /* Get the TIMx CCER register value */
    tmpccer = TIMx->CCER;

    /* Get the TIMx CR2 register value */
    tmpcr2 =  TIMx->CR2;

    /* Get the TIMx CCMR3 register value */
    tmpccmrx = TIMx->CCMR3;

    /* Reset the Output Compare mode Bits */
    tmpccmrx &= (uint32_t)(~((uint32_t)TIM_CCMR3_OC5M));
    /* Select the Output Compare Mode */
    tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;

    /* Reset the Output Polarity level */
    tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC5P));
    /* Set the Output Compare Polarity */
    tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCPolarity << 16);

    /* Set the Output State */
    tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputState << 16);

    /* Check the parameters */
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

    /* Reset the Ouput Compare IDLE State */
    tmpcr2 &= (uint32_t)(~((uint32_t)TIM_CR2_OIS5));
    /* Set the Output Idle state */
    tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCIdleState << 8);

    /* Write to TIMx CR2 */
    TIMx->CR2 = tmpcr2;

    /* Set the Capture Compare Register value */
    if (((TIMx->CCMR3)&TIM_CCMR3_OC5PE) != TIM_CCMR3_OC5PE)
    {
        TIMx->CCR5 = TIM_OCInitStruct->TIM_Pulse;
    }
    else if (((TIMx->CCMR3)&TIM_CCMR3_OC5PE) == TIM_CCMR3_OC5PE)
    {
        TIMx->CCR5 = TIM_OCInitStruct->TIM_Pulse;
        TIMx->EGR |= TIM_EGR_UG;
        TIMx->SR &= (uint32_t)~((uint32_t)TIM_SR_UIF);
    }


    /* Write to TIMx CCMR3 */
    TIMx->CCMR3 = tmpccmrx;

    /* Write to TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Initializes the TIMx Channel6 according to the specified
  *         parameters in the TIM_OCInitStruct.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
  *         that contains the configuration information for the specified TIM
  *         peripheral.
  * @retval None
  */
void TIM_OC6Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
    uint32_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

    /* Disable the Channel 6: Reset the CC6E Bit */
    TIMx->CCER &= (uint32_t)(~((uint32_t)TIM_CCER_CC6E));

    /* Get the TIMx CCER register value */
    tmpccer = TIMx->CCER;

    /* Get the TIMx CR2 register value */
    tmpcr2 =  TIMx->CR2;

    /* Get the TIMx CCMR3 register value */
    tmpccmrx = TIMx->CCMR3;

    /* Reset the Output Compare mode Bits */
    tmpccmrx &= (uint32_t)(~((uint32_t)TIM_CCMR3_OC6M));
    /* Select the Output Compare Mode */
    tmpccmrx |= (uint32_t)(TIM_OCInitStruct->TIM_OCMode << 8);

    /* Reset the Output Polarity level */
    tmpccer &= (uint32_t)(~((uint32_t)TIM_CCER_CC6P));
    /* Set the Output Compare Polarity */
    tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OCPolarity << 20);

    /* Set the Output State */
    tmpccer |= (uint32_t)(TIM_OCInitStruct->TIM_OutputState << 20);

    /* Check the parameters */
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

    /* Reset the Ouput Compare IDLE State */
    tmpcr2 &= (uint32_t)(~((uint32_t)TIM_CR2_OIS6));
    /* Set the Output Idle state */
    tmpcr2 |= (uint32_t)(TIM_OCInitStruct->TIM_OCIdleState << 10);

    /* Write to TIMx CR2 */
    TIMx->CR2 = tmpcr2;

    /* Set the Capture Compare Register value */
    if (((TIMx->CCMR3)&TIM_CCMR3_OC6PE) != TIM_CCMR3_OC6PE)
    {
        TIMx->CCR6 = TIM_OCInitStruct->TIM_Pulse;
    }
    else if (((TIMx->CCMR3)&TIM_CCMR3_OC6PE) == TIM_CCMR3_OC6PE)
    {
        TIMx->CCR6 = TIM_OCInitStruct->TIM_Pulse;
        TIMx->EGR |= TIM_EGR_UG;
        TIMx->SR &= (uint32_t)~((uint32_t)TIM_SR_UIF);
    }

    /* Write to TIMx CCMR3 */
    TIMx->CCMR3 = tmpccmrx;

    /* Write to TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Group channel 5 and channel 1, 2 or 3
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_Group_Channel5 specifies the reference signal(s) the OC5REF is combined with.
  *         This parameter can be any combination of the following values:
  *         TIM_GroupCH5_None   : No effect of OC5REF on OC1REFC, OC2REFC and OC3REFC
  *         TIM_GroupCH5_OC1Refc: OC1REFC is the logical AND of OC1REFC and OC5REF
  *         TIM_GroupCH5_OC2Refc: OC2REFC is the logical AND of OC2REFC and OC5REF
  *         TIM_GroupCH5_OC3Refc: OC3REFC is the logical AND of OC3REFC and OC5REF
  * @retval None
  */
void TIM_GroupChannel5(TIM_TypeDef* TIMx, uint32_t TIM_Group_Channel5)
{
    /* Check parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_GROUPCH5(TIM_Group_Channel5));

    /* Clear GC5Cx bit fields */
    TIMx->CCR5 &= ~(TIM_CCR5_GC5C3 | TIM_CCR5_GC5C2 | TIM_CCR5_GC5C1);

    /* Set GC5Cx bit fields */
    TIMx->CCR5 |= TIM_Group_Channel5;
}

/**
  * @brief  Fills each TIM_OCInitStruct member with its default value.
  * @param  TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct)
{
    /* Set the default configuration */
    TIM_OCInitStruct->TIM_OCMode       = TIM_OCMode_Timing;
    TIM_OCInitStruct->TIM_OutputState  = TIM_OutputState_Disable;
    TIM_OCInitStruct->TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStruct->TIM_Pulse        = 0x0000000;
    TIM_OCInitStruct->TIM_OCPolarity   = TIM_OCPolarity_High;
    TIM_OCInitStruct->TIM_OCNPolarity  = TIM_OCNPolarity_High;
    TIM_OCInitStruct->TIM_OCIdleState  = TIM_OCIdleState_Reset;
    TIM_OCInitStruct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

/**
  * @brief  Selects the TIM Output Compare Mode.
  * @note   This function disables the selected channel before changing the Output
  *         Compare Mode.
  *         User has to enable this channel using TIM_CCxCmd and TIM_CCxNCmd functions.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14 to select
  *         the TIM peripheral.
  * @param  TIM_Channel: specifies the TIM Channel
  *          This parameter can be one of the following values:
  *            @arg TIM_Channel_1: TIM Channel 1
  *            @arg TIM_Channel_2: TIM Channel 2
  *            @arg TIM_Channel_3: TIM Channel 3
  *            @arg TIM_Channel_4: TIM Channel 4
  *            @arg TIM_Channel_5: TIM Channel 5
  *            @arg TIM_Channel_6: TIM Channel 6
  * @param  TIM_OCMode: specifies the TIM Output Compare Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCMode_Timing
  *            @arg TIM_OCMode_Active
  *            @arg TIM_OCMode_Inactive
  *            @arg TIM_OCMode_Toggle
  *            @arg TIM_OCMODE_Forced_Inactive
  *            @arg TIM_OCMODE_Forced_Active
  *            @arg TIM_OCMode_PWM1
  *            @arg TIM_OCMode_PWM2
  *            @arg TIM_OCMode_Combined_PWM1
  *            @arg TIM_OCMode_Combined_PWM2
  *            @arg TIM_OCMode_Asymmetric_PWM1
  *            @arg TIM_OCMode_Asymmetric_PWM2
  * @retval None
  */
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint32_t TIM_Channel, uint32_t TIM_OCMode)
{
    uint32_t tmp = 0;
    uint32_t tmp1 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OC_MODE(TIM_OCMode));

    /* Check the parameters - TIM_Channel */
    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        assert_param(IS_TIM_CHANNEL(TIM_Channel));
    }
    else if ((TIMx == TIM2) || (TIMx == TIM3) ||
             (TIMx == TIM4) || (TIMx == TIM5))
    {
        assert_param(IS_TIM_2_TO_5_CHANNEL(TIM_Channel));
    }
    else if ((TIMx == TIM9) || (TIMx == TIM12))
    {
        assert_param(IS_TIM_9_AND_12_CHANNEL(TIM_Channel));
    }
    else/*if((TIMx == TIM10) || (TIMx == TIM11) ||
           (TIMx == TIM13) || (TIMx == TIM14))*/
    {
        assert_param(IS_TIM_10_11_13_14_CHANNEL(TIM_Channel));
    }

    tmp = (uint32_t) TIMx;
    tmp += CCMR_OFFSET;

    tmp1 = CCER_CCE_SET << (uint32_t)TIM_Channel;

    /* Disable the Channel: Reset the CCxE Bit */
    TIMx->CCER &= (uint32_t) ~tmp1;

    if ((TIM_Channel == TIM_Channel_1) || (TIM_Channel == TIM_Channel_3) || (TIM_Channel == TIM_Channel_5))
    {
        if ((TIM_Channel == TIM_Channel_1) || (TIM_Channel == TIM_Channel_3))
        {
            tmp += (TIM_Channel >> 1);
        }
        else /* if(TIM_Channel == TIM_Channel_5) */
        {
            tmp += ((uint32_t)0x0000003C);
        }

        /* Reset the OCxM bits in the CCMRx register */
        *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)TIM_CCMR1_OC1M);

        /* Configure the OCxM bits in the CCMRx register */
        *(__IO uint32_t *) tmp |= TIM_OCMode;
    }
    else
    {
        if ((TIM_Channel == TIM_Channel_2) || (TIM_Channel == TIM_Channel_4))
        {
            tmp += (uint32_t)(TIM_Channel - (uint32_t)4) >> (uint32_t)1;
        }
        else /* if(TIM_Channel == TIM_Channel_6) */
        {
            tmp += ((uint32_t)0x0000003C);
        }

        /* Reset the OCxM bits in the CCMRx register */
        *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)TIM_CCMR1_OC2M);

        /* Configure the OCxM bits in the CCMRx register */
        *(__IO uint32_t *) tmp |= (uint32_t)(TIM_OCMode << 8);
    }
}

/**
  * @brief  Sets the TIMx Capture Compare1 Register value
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14
  *         to select the TIM peripheral.
  * @param  Compare1: specifies the Capture Compare1 register new value.
  * @retval None
  */
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));

    /* Set the Capture Compare1 Register value */
    TIMx->CCR1 = Compare1;
}

/**
  * @brief  Sets the TIMx Capture Compare2 Register value
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select
  *         the TIM peripheral.
  * @param  Compare2: specifies the Capture Compare2 register new value.
  * @retval None
  */
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));

    /* Set the Capture Compare2 Register value */
    TIMx->CCR2 = Compare2;
}

/**
  * @brief  Sets the TIMx Capture Compare3 Register value
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  Compare3: specifies the Capture Compare3 register new value.
  * @retval None
  */
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));

    /* Set the Capture Compare3 Register value */
    TIMx->CCR3 = Compare3;
}

/**
  * @brief  Sets the TIMx Capture Compare4 Register value
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  Compare4: specifies the Capture Compare4 register new value.
  * @retval None
  */
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));

    /* Set the Capture Compare4 Register value */
    TIMx->CCR4 = Compare4;
}

/**
  * @brief  Sets the TIMx Capture Compare5 Register value
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  Compare5: specifies the Capture Compare5 register new value.
  * @retval None
  */
void TIM_SetCompare5(TIM_TypeDef* TIMx, uint32_t Compare5)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));

    /* Set the Capture Compare5 Register value */
    TIMx->CCR5 = Compare5;
}

/**
  * @brief  Sets the TIMx Capture Compare6 Register value
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  Compare6: specifies the Capture Compare6 register new value.
  * @retval None
  */
void TIM_SetCompare6(TIM_TypeDef* TIMx, uint32_t Compare6)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));

    /* Set the Capture Compare6 Register value */
    TIMx->CCR6 = Compare6;
}

/**
  * @brief  Forces the TIMx output 1 waveform to active or inactive level.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14 to select the
  *         TIM peripheral.
  * @param  TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM_ForcedAction_Active  : Force active level on OC1REF
  *            @arg TIM_ForcedAction_InActive: Force inactive level on OC1REF.
  * @retval None
  */
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmr1 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));

    tmpccmr1 = TIMx->CCMR1;

    /* Reset the OC1M Bits */
    tmpccmr1 &= (uint32_t)~((uint32_t)TIM_CCMR1_OC1M);

    /* Configure The Forced output Mode */
    tmpccmr1 |= TIM_ForcedAction;

    /* Write to TIMx CCMR1 register */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Forces the TIMx output 2 waveform to active or inactive level.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select the TIM peripheral.
  * @param  TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM_ForcedAction_Active  : Force active level on OC2REF
  *            @arg TIM_ForcedAction_InActive: Force inactive level on OC2REF.
  * @retval None
  */
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmr1 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr1 = TIMx->CCMR1;

    /* Reset the OC2M Bits */
    tmpccmr1 &= (uint32_t)~((uint32_t)TIM_CCMR1_OC2M);

    /* Configure The Forced output Mode */
    tmpccmr1 |= (uint32_t)(TIM_ForcedAction << 8);

    /* Write to TIMx CCMR1 register */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Forces the TIMx output 3 waveform to active or inactive level.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM_ForcedAction_Active  : Force active level on OC3REF
  *            @arg TIM_ForcedAction_InActive: Force inactive level on OC3REF.
  * @retval None
  */
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr2 = TIMx->CCMR2;

    /* Reset the OC3M Bits */
    tmpccmr2 &= (uint32_t)~((uint32_t)TIM_CCMR2_OC3M);

    /* Configure The Forced output Mode */
    tmpccmr2 |= TIM_ForcedAction;

    /* Write to TIMx CCMR2 register */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Forces the TIMx output 4 waveform to active or inactive level.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM_ForcedAction_Active  : Force active level on OC4REF
  *            @arg TIM_ForcedAction_InActive: Force inactive level on OC4REF.
  * @retval None
  */
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmr2 = 0;
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr2 = TIMx->CCMR2;

    /* Reset the OC4M Bits */
    tmpccmr2 &= (uint32_t)~((uint32_t)TIM_CCMR2_OC4M);

    /* Configure The Forced output Mode */
    tmpccmr2 |= (uint32_t)(TIM_ForcedAction << 8);

    /* Write to TIMx CCMR2 register */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Forces the TIMx output 5 waveform to active or inactive level.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM_ForcedAction_Active  : Force active level on OC5REF
  *            @arg TIM_ForcedAction_InActive: Force inactive level on OC5REF.
  * @retval None
  */
void TIM_ForcedOC5Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmr3 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr3 = TIMx->CCMR3;

    /* Reset the OC5M Bits */
    tmpccmr3 &= (uint32_t)~((uint32_t)TIM_CCMR3_OC5M);

    /* Configure The Forced output Mode */
    tmpccmr3 |= TIM_ForcedAction;

    /* Write to TIMx CCMR3 register */
    TIMx->CCMR3 = tmpccmr3;
}

/**
  * @brief  Forces the TIMx output 6 waveform to active or inactive level.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_ForcedAction: specifies the forced Action to be set to the output waveform.
  *          This parameter can be one of the following values:
  *            @arg TIM_ForcedAction_Active  : Force active level on OC6REF
  *            @arg TIM_ForcedAction_InActive: Force inactive level on OC6REF.
  * @retval None
  */
void TIM_ForcedOC6Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction)
{
    uint32_t tmpccmr3 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr3 = TIMx->CCMR3;

    /* Reset the OC6M Bits */
    tmpccmr3 &= (uint32_t)~((uint32_t)TIM_CCMR3_OC6M);

    /* Configure The Forced output Mode */
    tmpccmr3 |= (uint32_t)(TIM_ForcedAction << 8);

    /* Write to TIMx CCMR3 register */
    TIMx->CCMR3 = tmpccmr3;
}

/**
  * @brief  Sets or Resets the TIM peripheral Capture Compare Preload Control bit.
  * @param  TIMx: where x can be 1 or 8 to select the TIMx peripheral
  * @param  NewState: new state of the Capture Compare Preload Control bit
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Set the CCPC Bit */
        TIMx->CR2 |= TIM_CR2_CCPC;
    }
    else
    {
        /* Reset the CCPC Bit */
        TIMx->CR2 &= (uint32_t)~((uint32_t)TIM_CR2_CCPC);
    }
}


/**
  * @brief  Enables or disables the TIMx peripheral Preload register on CCR1.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 and 14 to
  *         select the TIM peripheral.
  * @param  TIM_OCPreload: new state of the TIMx peripheral Preload register
  *          This parameter can be one of the following values:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * @retval None
  */
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmr1 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

    tmpccmr1 = TIMx->CCMR1;

    /* Reset the OC1PE Bit */
    tmpccmr1 &= (uint32_t)~((uint32_t)TIM_CCMR1_OC1PE);

    /* Enable or Disable the Output Compare Preload feature */
    tmpccmr1 |= TIM_OCPreload;

    /* Write to TIMx CCMR1 register */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Enables or disables the TIMx peripheral Preload register on CCR2.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 and 12 to select the
  *         TIM peripheral.
  * @param  TIM_OCPreload: new state of the TIMx peripheral Preload register
  *          This parameter can be one of the following values:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * @retval None
  */
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmr1 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

    tmpccmr1 = TIMx->CCMR1;

    /* Reset the OC2PE Bit */
    tmpccmr1 &= (uint32_t)~((uint32_t)TIM_CCMR1_OC2PE);

    /* Enable or Disable the Output Compare Preload feature */
    tmpccmr1 |= (uint32_t)(TIM_OCPreload << 8);

    /* Write to TIMx CCMR1 register */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Enables or disables the TIMx peripheral Preload register on CCR3.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCPreload: new state of the TIMx peripheral Preload register
  *          This parameter can be one of the following values:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * @retval None
  */
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

    tmpccmr2 = TIMx->CCMR2;

    /* Reset the OC3PE Bit */
    tmpccmr2 &= (uint32_t)~((uint32_t)TIM_CCMR2_OC3PE);

    /* Enable or Disable the Output Compare Preload feature */
    tmpccmr2 |= TIM_OCPreload;

    /* Write to TIMx CCMR2 register */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Enables or disables the TIMx peripheral Preload register on CCR4.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCPreload: new state of the TIMx peripheral Preload register
  *          This parameter can be one of the following values:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * @retval None
  */
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

    tmpccmr2 = TIMx->CCMR2;

    /* Reset the OC4PE Bit */
    tmpccmr2 &= (uint32_t)~((uint32_t)TIM_CCMR2_OC4PE);

    /* Enable or Disable the Output Compare Preload feature */
    tmpccmr2 |= (uint32_t)(TIM_OCPreload << 8);

    /* Write to TIMx CCMR2 register */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Enables or disables the TIMx peripheral Preload register on CCR5.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCPreload: new state of the TIMx peripheral Preload register
  *          This parameter can be one of the following values:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * @retval None
  */
void TIM_OC5PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmr3 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

    tmpccmr3 = TIMx->CCMR3;

    /* Reset the OC5PE Bit */
    tmpccmr3 &= (uint32_t)~((uint32_t)TIM_CCMR3_OC5PE);

    /* Enable or Disable the Output Compare Preload feature */
    tmpccmr3 |= TIM_OCPreload;

    /* Write to TIMx CCMR3 register */
    TIMx->CCMR3 = tmpccmr3;
}

/**
  * @brief  Enables or disables the TIMx peripheral Preload register on CCR6.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCPreload: new state of the TIMx peripheral Preload register
  *          This parameter can be one of the following values:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * @retval None
  */
void TIM_OC6PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload)
{
    uint32_t tmpccmr3 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

    tmpccmr3 = TIMx->CCMR3;

    /* Reset the OC6PE Bit */
    tmpccmr3 &= (uint32_t)~((uint32_t)TIM_CCMR3_OC6PE);

    /* Enable or Disable the Output Compare Preload feature */
    tmpccmr3 |= (uint32_t)(TIM_OCPreload << 8);

    /* Write to TIMx CCMR3 register */
    TIMx->CCMR3 = tmpccmr3;
}

/**
  * @brief  Configures the TIMx Output Compare 1 Fast feature.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14
  *         to select the TIM peripheral.
  * @param  TIM_OCFast: new state of the Output Compare Fast Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCFast_Enable : TIM output compare fast enable
  *            @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None
  */
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmr1 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

    /* Get the TIMx CCMR1 register value */
    tmpccmr1 = TIMx->CCMR1;

    /* Reset the OC1FE Bit */
    tmpccmr1 &= (uint32_t)~((uint32_t)TIM_CCMR1_OC1FE);

    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmr1 |= TIM_OCFast;

    /* Write to TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Configures the TIMx Output Compare 2 Fast feature.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select
  *         the TIM peripheral.
  * @param  TIM_OCFast: new state of the Output Compare Fast Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCFast_Enable : TIM output compare fast enable
  *            @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None
  */
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmr1 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

    /* Get the TIMx CCMR1 register value */
    tmpccmr1 = TIMx->CCMR1;

    /* Reset the OC2FE Bit */
    tmpccmr1 &= (uint32_t)~((uint32_t)TIM_CCMR1_OC2FE);

    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmr1 |= (uint32_t)(TIM_OCFast << 8);

    /* Write to TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Configures the TIMx Output Compare 3 Fast feature.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCFast: new state of the Output Compare Fast Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCFast_Enable : TIM output compare fast enable
  *            @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None
  */
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

    /* Get the TIMx CCMR2 register value */
    tmpccmr2 = TIMx->CCMR2;

    /* Reset the OC3FE Bit */
    tmpccmr2 &= (uint32_t)~((uint32_t)TIM_CCMR2_OC3FE);

    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmr2 |= TIM_OCFast;

    /* Write to TIMx CCMR2 */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the TIMx Output Compare 4 Fast feature.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCFast: new state of the Output Compare Fast Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCFast_Enable : TIM output compare fast enable
  *            @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None
  */
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

    /* Get the TIMx CCMR2 register value */
    tmpccmr2 = TIMx->CCMR2;

    /* Reset the OC4FE Bit */
    tmpccmr2 &= (uint32_t)~((uint32_t)TIM_CCMR2_OC4FE);

    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmr2 |= (uint32_t)(TIM_OCFast << 8);

    /* Write to TIMx CCMR2 */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Configures the TIMx Output Compare 5 Fast feature.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCFast: new state of the Output Compare Fast Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCFast_Enable : TIM output compare fast enable
  *            @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None
  */
void TIM_OC5FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmr3 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

    /* Get the TIMx CCMR3 register value */
    tmpccmr3 = TIMx->CCMR3;

    /* Reset the OC5FE Bit */
    tmpccmr3 &= (uint32_t)~((uint32_t)TIM_CCMR3_OC5FE);

    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmr3 |= TIM_OCFast;

    /* Write to TIMx CCMR3 */
    TIMx->CCMR3 = tmpccmr3;
}

/**
  * @brief  Configures the TIMx Output Compare 6 Fast feature.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCFast: new state of the Output Compare Fast Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCFast_Enable : TIM output compare fast enable
  *            @arg TIM_OCFast_Disable: TIM output compare fast disable
  * @retval None
  */
void TIM_OC6FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast)
{
    uint32_t tmpccmr3 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

    /* Get the TIMx CCMR3 register value */
    tmpccmr3 = TIMx->CCMR3;

    /* Reset the OC6FE Bit */
    tmpccmr3 &= (uint32_t)~((uint32_t)TIM_CCMR3_OC6FE);

    /* Enable or Disable the Output Compare Fast Bit */
    tmpccmr3 |= (uint32_t)(TIM_OCFast << 8);

    /* Write to TIMx CCMR3 */
    TIMx->CCMR3 = tmpccmr3;
}

/**
  * @brief  Clears or safeguards the OCREF1 signal on an external event
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCClear: new state of the Output Compare Clear Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCClear_Enable : TIM Output clear enable
  *            @arg TIM_OCClear_Disable: TIM Output clear disable
  * @retval None
  */
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmr1 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

    tmpccmr1 = TIMx->CCMR1;

    /* Reset the OC1CE Bit */
    tmpccmr1 &= (uint32_t)~((uint32_t)TIM_CCMR1_OC1CE);

    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmr1 |= TIM_OCClear;

    /* Write to TIMx CCMR1 register */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Clears or safeguards the OCREF2 signal on an external event
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCClear: new state of the Output Compare Clear Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCClear_Enable : TIM Output clear enable
  *            @arg TIM_OCClear_Disable: TIM Output clear disable
  * @retval None
  */
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmr1 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

    tmpccmr1 = TIMx->CCMR1;

    /* Reset the OC2CE Bit */
    tmpccmr1 &= (uint32_t)~((uint32_t)TIM_CCMR1_OC2CE);

    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmr1 |= (uint32_t)(TIM_OCClear << 8);

    /* Write to TIMx CCMR1 register */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * @brief  Clears or safeguards the OCREF3 signal on an external event
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCClear: new state of the Output Compare Clear Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCClear_Enable : TIM Output clear enable
  *            @arg TIM_OCClear_Disable: TIM Output clear disable
  * @retval None
  */
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

    tmpccmr2 = TIMx->CCMR2;

    /* Reset the OC3CE Bit */
    tmpccmr2 &= (uint32_t)~((uint32_t)TIM_CCMR2_OC3CE);

    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmr2 |= TIM_OCClear;

    /* Write to TIMx CCMR2 register */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Clears or safeguards the OCREF4 signal on an external event
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCClear: new state of the Output Compare Clear Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCClear_Enable : TIM Output clear enable
  *            @arg TIM_OCClear_Disable: TIM Output clear disable
  * @retval None
  */
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmr2 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

    tmpccmr2 = TIMx->CCMR2;

    /* Reset the OC4CE Bit */
    tmpccmr2 &= (uint32_t)~((uint32_t)TIM_CCMR2_OC4CE);

    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmr2 |= (uint32_t)(TIM_OCClear << 8);

    /* Write to TIMx CCMR2 register */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * @brief  Clears or safeguards the OCREF5 signal on an external event
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCClear: new state of the Output Compare Clear Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCClear_Enable : TIM Output clear enable
  *            @arg TIM_OCClear_Disable: TIM Output clear disable
  * @retval None
  */
void TIM_ClearOC5Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmr3 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

    tmpccmr3 = TIMx->CCMR3;

    /* Reset the OC5CE Bit */
    tmpccmr3 &= (uint32_t)~((uint32_t)TIM_CCMR3_OC5CE);

    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmr3 |= TIM_OCClear;

    /* Write to TIMx CCMR3 register */
    TIMx->CCMR3 = tmpccmr3;
}

/**
  * @brief  Clears or safeguards the OCREF6 signal on an external event
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCClear: new state of the Output Compare Clear Enable Bit.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCClear_Enable : TIM Output clear enable
  *            @arg TIM_OCClear_Disable: TIM Output clear disable
  * @retval None
  */
void TIM_ClearOC6Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear)
{
    uint32_t tmpccmr3 = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

    tmpccmr3 = TIMx->CCMR3;

    /* Reset the OC6CE Bit */
    tmpccmr3 &= (uint32_t)~((uint32_t)TIM_CCMR3_OC6CE);

    /* Enable or Disable the Output Compare Clear Bit */
    tmpccmr3 |= (uint32_t)(TIM_OCClear << 8);

    /* Write to TIMx CCMR3 register */
    TIMx->CCMR3 = tmpccmr3;
}

/**
  * @brief  Configures the TIMx channel 1 polarity.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13
  *         or 14 to select the TIM peripheral.
  * @param  TIM_OCPolarity: specifies the OC1 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCPolarity_High: Output Compare active high
  *            @arg TIM_OCPolarity_Low : Output Compare active low
  * @retval None
  */
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
    uint32_t tmpccer = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

    tmpccer = TIMx->CCER;

    /* Set or Reset the CC1P Bit */
    tmpccer &= (uint32_t)~((uint32_t)TIM_CCER_CC1P);
    tmpccer |= TIM_OCPolarity;

    /* Write to TIMx CCER register */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx Channel 1N polarity.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCNPolarity: specifies the OC1N Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCNPolarity_High: Output Compare active high
  *            @arg TIM_OCNPolarity_Low : Output Compare active low
  * @retval None
  */
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity)
{
    uint32_t tmpccer = 0;
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));

    tmpccer = TIMx->CCER;

    /* Set or Reset the CC1NP Bit */
    tmpccer &= (uint32_t)~((uint32_t)TIM_CCER_CC1NP);
    tmpccer |= TIM_OCNPolarity;

    /* Write to TIMx CCER register */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx channel 2 polarity.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to
  *         select the TIM peripheral.
  * @param  TIM_OCPolarity: specifies the OC2 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCPolarity_High: Output Compare active high
  *            @arg TIM_OCPolarity_Low : Output Compare active low
  * @retval None
  */
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
    uint32_t tmpccer = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

    tmpccer = TIMx->CCER;

    /* Set or Reset the CC2P Bit */
    tmpccer &= (uint32_t)~((uint32_t)TIM_CCER_CC2P);
    tmpccer |= (uint32_t)(TIM_OCPolarity << 4);

    /* Write to TIMx CCER register */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx Channel 2N polarity.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCNPolarity: specifies the OC2N Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCNPolarity_High: Output Compare active high
  *            @arg TIM_OCNPolarity_Low : Output Compare active low
  * @retval None
  */
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity)
{
    uint32_t tmpccer = 0;
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));

    tmpccer = TIMx->CCER;

    /* Set or Reset the CC2NP Bit */
    tmpccer &= (uint32_t)~((uint32_t)TIM_CCER_CC2NP);
    tmpccer |= (uint32_t)(TIM_OCNPolarity << 4);

    /* Write to TIMx CCER register */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx channel 3 polarity.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select
  *         the TIM peripheral.
  * @param  TIM_OCPolarity: specifies the OC3 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCPolarity_High: Output Compare active high
  *            @arg TIM_OCPolarity_Low : Output Compare active low
  * @retval None
  */
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
    uint32_t tmpccer = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

    tmpccer = TIMx->CCER;

    /* Set or Reset the CC3P Bit */
    tmpccer &= (uint32_t)~((uint32_t)TIM_CCER_CC3P);
    tmpccer |= (uint32_t)(TIM_OCPolarity << 8);

    /* Write to TIMx CCER register */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx Channel 3N polarity.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCNPolarity: specifies the OC3N Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCNPolarity_High: Output Compare active high
  *            @arg TIM_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity)
{
    uint32_t tmpccer = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));

    tmpccer = TIMx->CCER;

    /* Set or Reset the CC3NP Bit */
    tmpccer &= (uint32_t)~((uint32_t)TIM_CCER_CC3NP);
    tmpccer |= (uint32_t)(TIM_OCNPolarity << 8);

    /* Write to TIMx CCER register */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx channel 4 polarity.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select
  *         the TIM peripheral.
  * @param  TIM_OCPolarity: specifies the OC4 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCPolarity_High: Output Compare active high
  *            @arg TIM_OCPolarity_Low : Output Compare active low
  * @retval None
  */
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
    uint32_t tmpccer = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

    tmpccer = TIMx->CCER;

    /* Set or Reset the CC4P Bit */
    tmpccer &= (uint32_t)~((uint32_t)TIM_CCER_CC4P);
    tmpccer |= (uint32_t)(TIM_OCPolarity << 12);

    /* Write to TIMx CCER register */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx channel 5 polarity.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCPolarity: specifies the OC5 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCPolarity_High: Output Compare active high
  *            @arg TIM_OCPolarity_Low : Output Compare active low
  * @retval None
  */
void TIM_OC5PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
    uint32_t tmpccer = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

    tmpccer = TIMx->CCER;

    /* Set or Reset the CC5P Bit */
    tmpccer &= (uint32_t)~((uint32_t)TIM_CCER_CC5P);
    tmpccer |= (uint32_t)(TIM_OCPolarity << 16);

    /* Write to TIMx CCER register */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configures the TIMx channel 6 polarity.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_OCPolarity: specifies the OC6 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_OCPolarity_High: Output Compare active high
  *            @arg TIM_OCPolarity_Low : Output Compare active low
  * @retval None
  */
void TIM_OC6PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity)
{
    uint32_t tmpccer = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

    tmpccer = TIMx->CCER;

    /* Set or Reset the CC6P Bit */
    tmpccer &= (uint32_t)~((uint32_t)TIM_CCER_CC6P);
    tmpccer |= (uint32_t)(TIM_OCPolarity << 20);

    /* Write to TIMx CCER register */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Selects the OCReference Clear source.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCReferenceClear: specifies the OCReference Clear source.
  *          This parameter can be one of the following values:
  *            @arg TIM_OCReferenceClear_ETRF    : The internal OCreference clear input is connected to ETRF.
  *            @arg TIM_OCReferenceClear_OCREFCLR: The internal OCreference clear input is connected to OCREF_CLR input.
  * @retval None
  */
void TIM_SelectOCREFClear(TIM_TypeDef* TIMx, uint32_t TIM_OCReferenceClear)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(TIM_OCREFERENCECECLEAR_SOURCE(TIM_OCReferenceClear));

    /* Set the TIM_OCReferenceClear source */
    TIMx->SMCR &= (uint32_t)~((uint32_t)TIM_SMCR_OCCS);
    TIMx->SMCR |=  TIM_OCReferenceClear;
}

/**
  * @brief  Enables or disables the TIM Capture Compare Channel x.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14 to select
  *         the TIM peripheral.
  * @param  TIM_Channel: specifies the TIM Channel
  *          This parameter can be one of the following values:
  *            @arg TIM_Channel_1: TIM Channel 1
  *            @arg TIM_Channel_2: TIM Channel 2
  *            @arg TIM_Channel_3: TIM Channel 3
  *            @arg TIM_Channel_4: TIM Channel 4
  *            @arg TIM_Channel_5: TIM Channel 5
  *            @arg TIM_Channel_6: TIM Channel 6
  * @param  TIM_CCx: specifies the TIM Channel CCxE bit new state.
  *          This parameter can be: TIM_CCx_Enable or TIM_CCx_Disable .
  * @retval None
  */
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint32_t TIM_Channel, uint32_t TIM_CCx)
{
    uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_TIM_CCX(TIM_CCx));

    /* Check the parameters - TIM_Channel */
    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        assert_param(IS_TIM_CHANNEL(TIM_Channel));
    }
    else if ((TIMx == TIM2) || (TIMx == TIM3) ||
             (TIMx == TIM4) || (TIMx == TIM5))
    {
        assert_param(IS_TIM_2_TO_5_CHANNEL(TIM_Channel));
    }
    else if ((TIMx == TIM9) || (TIMx == TIM12))
    {
        assert_param(IS_TIM_9_AND_12_CHANNEL(TIM_Channel));
    }
    else/*if((TIMx == TIM10) || (TIMx == TIM11) ||
           (TIMx == TIM13) || (TIMx == TIM14))*/
    {
        assert_param(IS_TIM_10_11_13_14_CHANNEL(TIM_Channel));
    }

    tmp = CCER_CCE_SET << TIM_Channel;

    /* Reset the CCxE Bit */
    TIMx->CCER &= (uint32_t)~ tmp;

    /* Set or reset the CCxE Bit */
    TIMx->CCER |= (uint32_t)(TIM_CCx << TIM_Channel);
}

/**
  * @brief  Enables or disables the TIM Capture Compare Channel xN.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_Channel: specifies the TIM Channel
  *          This parmeter can be one of the following values:
  *            @arg TIM_Channel_1: TIM Channel 1
  *            @arg TIM_Channel_2: TIM Channel 2
  *            @arg TIM_Channel_3: TIM Channel 3
  * @param  TIM_CCxN: specifies the TIM Channel CCxNE bit new state.
  *          This parameter can be: TIM_CCxN_Enable or TIM_CCxN_Disable.
  * @retval None
  */
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint32_t TIM_Channel, uint32_t TIM_CCxN)
{
    uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_COMPLEMENTARY_CHANNEL(TIM_Channel));
    assert_param(IS_TIM_CCXN(TIM_CCxN));

    tmp = CCER_CCNE_SET << TIM_Channel;

    /* Reset the CCxNE Bit */
    TIMx->CCER &= (uint32_t) ~tmp;

    /* Set or reset the CCxNE Bit */
    TIMx->CCER |= (uint32_t)(TIM_CCxN << TIM_Channel);
}

/**
  * @brief  Selects the TIM peripheral Commutation event.
  * @param  TIMx: where x can be  1 or 8 to select the TIMx peripheral
  * @param  NewState: new state of the Commutation event.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the COM Bit */
        TIMx->CR2 |= TIM_CR2_CCUS;
    }
    else
    {
        /* Reset the COM Bit */
        TIMx->CR2 &= (uint32_t)~((uint32_t)TIM_CR2_CCUS);
    }
}

/**
  * @}
  */
/**
  * @brief  Initializes the TIM peripheral according to the specified
  *         parameters in the TIM_ICInitStruct.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14
  *         to select the TIM peripheral.
  * @param  TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure
  *         that contains the configuration information for the specified TIM
  *         peripheral.
  * @retval None
  */
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_CHANNEL(TIM_ICInitStruct->TIM_Channel));
    assert_param(IS_TIM_IC_SELECTION(TIM_ICInitStruct->TIM_ICSelection));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICInitStruct->TIM_ICPrescaler));
    assert_param(IS_TIM_IC_FILTER(TIM_ICInitStruct->TIM_ICFilter));
    assert_param(IS_TIM_IC_POLARITY(TIM_ICInitStruct->TIM_ICPolarity));

    if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
    {
        assert_param(IS_TIM_LIST4_PERIPH(TIMx));
        /* TI1 Configuration */
        TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
    else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_2)
    {
        assert_param(IS_TIM_LIST5_PERIPH(TIMx));
        /* TI2 Configuration */
        TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
    else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_3)
    {
        assert_param(IS_TIM_LIST3_PERIPH(TIMx));
        /* TI3 Configuration */
        TI3_Config(TIMx,  TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetIC3Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
    else
    {
        assert_param(IS_TIM_LIST3_PERIPH(TIMx));
        /* TI4 Configuration */
        TI4_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetIC4Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
}

/**
  * @brief  Fills each TIM_ICInitStruct member with its default value.
  * @param  TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct)
{
    /* Set the default configuration */
    TIM_ICInitStruct->TIM_Channel     = TIM_Channel_1;
    TIM_ICInitStruct->TIM_ICPolarity  = TIM_ICPolarity_Rising;
    TIM_ICInitStruct->TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct->TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct->TIM_ICFilter    = 0x00;
}

/**
  * @brief  Configures the TIM peripheral according to the specified
  *         parameters in the TIM_ICInitStruct to measure an external PWM signal.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select the TIM peripheral.
  * @param  TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure
  *         that contains the configuration information for the specified TIM
  *         peripheral.
  * @retval None
  */
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
    uint32_t icoppositepolarity  = TIM_ICPolarity_Rising;
    uint32_t icoppositeselection = TIM_ICSelection_DirectTI;

    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));

    /* Select the Opposite Input Polarity */
    if (TIM_ICInitStruct->TIM_ICPolarity == TIM_ICPolarity_Rising)
    {
        icoppositepolarity = TIM_ICPolarity_Falling;
    }
    else
    {
        icoppositepolarity = TIM_ICPolarity_Rising;
    }

    /* Select the Opposite Input */
    if (TIM_ICInitStruct->TIM_ICSelection == TIM_ICSelection_DirectTI)
    {
        icoppositeselection = TIM_ICSelection_IndirectTI;
    }
    else
    {
        icoppositeselection = TIM_ICSelection_DirectTI;
    }

    if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
    {
        /* TI1 Configuration */
        TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
        /* TI2 Configuration */
        TI2_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
    else
    {
        /* TI2 Configuration */
        TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
        /* TI1 Configuration */
        TI1_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
        /* Set the Input Capture Prescaler value */
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
}

/**
  * @brief  Gets the TIMx Input Capture 1 value.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14
  *         to select the TIM peripheral.
  * @retval Capture Compare 1 Register value.
  */
uint32_t TIM_GetCapture1(TIM_TypeDef* TIMx)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));

    /* Get the Capture 1 Register value */
    return TIMx->CCR1;
}

/**
  * @brief  Gets the TIMx Input Capture 2 value.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select the
  *         TIM peripheral.
  * @retval Capture Compare 2 Register value.
  */
uint32_t TIM_GetCapture2(TIM_TypeDef* TIMx)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));

    /* Get the Capture 2 Register value */
    return TIMx->CCR2;
}

/**
  * @brief  Gets the TIMx Input Capture 3 value.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @retval Capture Compare 3 Register value.
  */
uint32_t TIM_GetCapture3(TIM_TypeDef* TIMx)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));

    /* Get the Capture 3 Register value */
    return TIMx->CCR3;
}

/**
  * @brief  Gets the TIMx Input Capture 4 value.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @retval Capture Compare 4 Register value.
  */
uint32_t TIM_GetCapture4(TIM_TypeDef* TIMx)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));

    /* Get the Capture 4 Register value */
    return TIMx->CCR4;
}

/**
  * @brief  Gets the TIMx Input Capture 5 value.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @retval Capture Compare 5 Register value.
  */
uint32_t TIM_GetCapture5(TIM_TypeDef* TIMx)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));

    /* Get the Capture 5 Register value */
    return TIMx->CCR5;
}

/**
  * @brief  Gets the TIMx Input Capture 6 value.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @retval Capture Compare 6 Register value.
  */
uint32_t TIM_GetCapture6(TIM_TypeDef* TIMx)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));

    /* Get the Capture 6 Register value */
    return TIMx->CCR6;
}

/**
  * @brief  Sets the TIMx Input Capture 1 prescaler.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14
  *         to select the TIM peripheral.
  * @param  TIM_ICPSC: specifies the Input Capture1 prescaler new value.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPSC_DIV1: no prescaler
  *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

    /* Reset the IC1PSC Bits */
    TIMx->CCMR1 &= (uint32_t)~((uint32_t)TIM_CCMR1_IC1PSC);

    /* Set the IC1PSC value */
    TIMx->CCMR1 |= TIM_ICPSC;
}

/**
  * @brief  Sets the TIMx Input Capture 2 prescaler.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select the TIM peripheral.
  * @param  TIM_ICPSC: specifies the Input Capture2 prescaler new value.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPSC_DIV1: no prescaler
  *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

    /* Reset the IC2PSC Bits */
    TIMx->CCMR1 &= (uint32_t)~((uint32_t)TIM_CCMR1_IC2PSC);

    /* Set the IC2PSC value */
    TIMx->CCMR1 |= (uint32_t)(TIM_ICPSC << 8);
}

/**
  * @brief  Sets the TIMx Input Capture 3 prescaler.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_ICPSC: specifies the Input Capture3 prescaler new value.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPSC_DIV1: no prescaler
  *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

    /* Reset the IC3PSC Bits */
    TIMx->CCMR2 &= (uint32_t)~((uint32_t)TIM_CCMR2_IC3PSC);

    /* Set the IC3PSC value */
    TIMx->CCMR2 |= TIM_ICPSC;
}

/**
  * @brief  Sets the TIMx Input Capture 4 prescaler.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_ICPSC: specifies the Input Capture4 prescaler new value.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPSC_DIV1: no prescaler
  *            @arg TIM_ICPSC_DIV2: capture is done once every 2 events
  *            @arg TIM_ICPSC_DIV4: capture is done once every 4 events
  *            @arg TIM_ICPSC_DIV8: capture is done once every 8 events
  * @retval None
  */
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

    /* Reset the IC4PSC Bits */
    TIMx->CCMR2 &= (uint32_t)~((uint32_t)TIM_CCMR2_IC4PSC);

    /* Set the IC4PSC value */
    TIMx->CCMR2 |= (uint32_t)(TIM_ICPSC << 8);
}

/**
  * @}
  */

/**
  * @brief  Enables or disables the specified TIM interrupts.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 or 14
  *         to select the TIMx peripheral.
  * @param  TIM_IT: specifies the TIM interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg TIM_IT_Update : TIM update Interrupt source
  *            @arg TIM_IT_CC1    : TIM Capture Compare 1 Interrupt source
  *            @arg TIM_IT_CC2    : TIM Capture Compare 2 Interrupt source
  *            @arg TIM_IT_CC3    : TIM Capture Compare 3 Interrupt source
  *            @arg TIM_IT_CC4    : TIM Capture Compare 4 Interrupt source
  *            @arg TIM_IT_COM    : TIM Commutation Interrupt source
  *            @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  *            @arg TIM_IT_Break  : TIM Break Interrupt source
  *
  * @note   TIM2, TIM3, TIM4 and TIM5 can generate TIM_IT_Update, TIM_IT_CC1,
  *         TIM_IT_CC2, TIM_IT_CC3, TIM_IT_CC4 and TIM_IT_Trigger interrupt.
  * @note   TIM6 and TIM7 can only generate an update interrupt.
  * @note   TIM9 and TIM12 can generate TIM_IT_Update, TIM_IT_CC1, TIM_IT_CC2 and
  *         TIM_IT_Trigger interrupt.
  * @note   TIM10, TIM11, TIM13 and TIM14 can generate TIM_IT_Update and TIM_IT_CC1
  *         interrupt.
  *
  * @note   TIM_IT_Break is used only with TIM1 and TIM8.
  * @note   TIM_IT_COM is used only with TIM1 and TIM8.
  *
  * @param  NewState: new state of the TIM interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_ITConfig(TIM_TypeDef* TIMx, uint32_t TIM_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_IT(TIM_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the Interrupt sources */
        TIMx->DIER |= TIM_IT;
    }
    else
    {
        /* Disable the Interrupt sources */
        TIMx->DIER &= (uint32_t)~TIM_IT;
    }
}

/**
  * @brief  Configures the TIMx event to be generate by software.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 or 14
  *         to select the TIMx peripheral.
  * @param  TIM_EventSource: specifies the event source.
  *          This parameter can be one or more of the following values:
  *            @arg TIM_EventSource_Update : Timer update Event source
  *            @arg TIM_EventSource_CC1    : Timer Capture Compare 1 Event source
  *            @arg TIM_EventSource_CC2    : Timer Capture Compare 2 Event source
  *            @arg TIM_EventSource_CC3    : Timer Capture Compare 3 Event source
  *            @arg TIM_EventSource_CC4    : Timer Capture Compare 4 Event source
  *            @arg TIM_EventSource_COM    : Timer COM event source
  *            @arg TIM_EventSource_Trigger: Timer Trigger Event source
  *            @arg TIM_EventSource_Break  : Timer Break event source
  *
  * @note   TIM2, TIM3, TIM4 and TIM5 can generate Update, CC1, CC2, CC3, CC4 and trigger event.
  * @note   TIM6 and TIM7 can only generate an update event.
  * @note   TIM9 and TIM12 can generate Update, CC1, CC2 and trigger event.
  * @note   TIM10, TIM11, TIM13 and TIM14 can generate Update and CC1 event.
  * @note   TIM_EventSource_COM and TIM_EventSource_Break are used only with TIM1 and TIM8.
  *
  * @retval None
  */
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint32_t TIM_EventSource)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_EVENT_SOURCE(TIM_EventSource));

    /* Set the event sources */
    TIMx->EGR = TIM_EventSource;
}

/**
  * @brief  Checks whether the specified TIM flag is set or not.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 or 14
  *         to select the TIMx peripheral.
  * @param  TIM_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg TIM_FLAG_Update : TIM update Flag
  *            @arg TIM_FLAG_CC1    : TIM Capture Compare 1 Flag
  *            @arg TIM_FLAG_CC2    : TIM Capture Compare 2 Flag
  *            @arg TIM_FLAG_CC3    : TIM Capture Compare 3 Flag
  *            @arg TIM_FLAG_CC4    : TIM Capture Compare 4 Flag
  *            @arg TIM_FLAG_CC5    : TIM Capture Compare 5 Flag
  *            @arg TIM_FLAG_CC6    : TIM Capture Compare 6 Flag
  *            @arg TIM_FLAG_COM    : TIM Commutation Flag
  *            @arg TIM_FLAG_Trigger: TIM Trigger Flag
  *            @arg TIM_FLAG_Break  : TIM Break Flag
  *            @arg TIM_FLAG_CC1OF  : TIM Capture Compare 1 overcapture Flag
  *            @arg TIM_FLAG_CC2OF  : TIM Capture Compare 2 overcapture Flag
  *            @arg TIM_FLAG_CC3OF  : TIM Capture Compare 3 overcapture Flag
  *            @arg TIM_FLAG_CC4OF  : TIM Capture Compare 4 overcapture Flag
  *
  * @note   TIM2, TIM3, TIM4 and TIM5 can have Update, CC1, CC2, CC3, CC4, trigger,
  *         CC1OF, CC2OF, CC3OF and CC4OF flag.
  * @note   TIM6 and TIM7 can have only one update flag.
  * @note   TIM9 and TIM12 can have Update, CC1, CC2, trigger, CC1OF and CC2OF flag.
  * @note   TIM10, TIM11, TIM13 and TIM14 can have Update, CC1 and CC1OF flag.
  * @note   TIM_FLAG_Break, TIM_FLAG_COM, TIM_FLAG_CC5 and TIM_FLAG_CC6 are used only
  *         with TIM1 and TIM8.
  *
  * @retval The new state of TIM_FLAG (SET or RESET).
  */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint32_t TIM_FLAG)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_GET_FLAG(TIM_FLAG));

    if ((TIMx->SR & TIM_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
  * @brief  Clears the TIMx's pending flags.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 or 14
  *         to select the TIMx peripheral.
  * @param  TIM_FLAG: specifies the flag bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg TIM_FLAG_Update : TIM update Flag
  *            @arg TIM_FLAG_CC1    : TIM Capture Compare 1 Flag
  *            @arg TIM_FLAG_CC2    : TIM Capture Compare 2 Flag
  *            @arg TIM_FLAG_CC3    : TIM Capture Compare 3 Flag
  *            @arg TIM_FLAG_CC4    : TIM Capture Compare 4 Flag
  *            @arg TIM_FLAG_CC5    : TIM Capture Compare 5 Flag
  *            @arg TIM_FLAG_CC6    : TIM Capture Compare 6 Flag
  *            @arg TIM_FLAG_COM    : TIM Commutation Flag
  *            @arg TIM_FLAG_Trigger: TIM Trigger Flag
  *            @arg TIM_FLAG_Break  : TIM Break Flag
  *            @arg TIM_FLAG_CC1OF  : TIM Capture Compare 1 overcapture Flag
  *            @arg TIM_FLAG_CC2OF  : TIM Capture Compare 2 overcapture Flag
  *            @arg TIM_FLAG_CC3OF  : TIM Capture Compare 3 overcapture Flag
  *            @arg TIM_FLAG_CC4OF  : TIM Capture Compare 4 overcapture Flag
  *
  * @note   TIM2, TIM3, TIM4 and TIM5 can have Update, CC1, CC2, CC3, CC4, trigger,
  *         CC1OF, CC2OF, CC3OF and CC4OF flag.
  * @note   TIM6 and TIM7 can have only one update flag.
  * @note   TIM9 and TIM12 can have Update, CC1, CC2, trigger, CC1OF and CC2OF flag.
  * @note   TIM10, TIM11, TIM13 and TIM14 can have Update, CC1 and CC1OF flag.
  * @note   TIM_FLAG_Break, TIM_FLAG_COM, TIM_FLAG_CC5 and TIM_FLAG_CC6 are used only
  *         with TIM1 and TIM8.
  *
  * @retval None
  */
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint32_t TIM_FLAG)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_CLEAR_FLAG(TIM_FLAG));

    /* Clear the flags */
    TIMx->SR = (uint32_t)~TIM_FLAG;
}

/**
  * @brief  Checks whether the TIM interrupt has occurred or not.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 or 14
  *         to select the TIMx peripheral.
  * @param  TIM_IT: specifies the TIM interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg TIM_IT_Update : TIM update Interrupt source
  *            @arg TIM_IT_CC1    : TIM Capture Compare 1 Interrupt source
  *            @arg TIM_IT_CC2    : TIM Capture Compare 2 Interrupt source
  *            @arg TIM_IT_CC3    : TIM Capture Compare 3 Interrupt source
  *            @arg TIM_IT_CC4    : TIM Capture Compare 4 Interrupt source
  *            @arg TIM_IT_COM    : TIM Commutation Interrupt source
  *            @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  *            @arg TIM_IT_Break  : TIM Break Interrupt source
  *
  * @note   TIM2, TIM3, TIM4 and TIM5 can generate TIM_IT_Update, TIM_IT_CC1,
  *         TIM_IT_CC2, TIM_IT_CC3, TIM_IT_CC4 and TIM_IT_Trigger interrupt.
  * @note   TIM6 and TIM7 can only generate an update interrupt.
  * @note   TIM9 and TIM12 can generate TIM_IT_Update, TIM_IT_CC1, TIM_IT_CC2 and
  *         TIM_IT_Trigger interrupt.
  * @note   TIM10, TIM11, TIM13 and TIM14 can generate TIM_IT_Update and TIM_IT_CC1
  *         interrupt.
  *
  * @note   TIM_IT_Break is used only with TIM1 and TIM8.
  * @note   TIM_IT_COM is used only with TIM1 and TIM8.
  *
  * @retval The new state of the TIM_IT(SET or RESET).
  */
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint32_t TIM_IT)
{
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0x0, itenable = 0x0;

    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_GET_IT(TIM_IT));

    itstatus = TIMx->SR & TIM_IT;

    itenable = TIMx->DIER & TIM_IT;
    if ((itstatus != (uint32_t)RESET) && (itenable != (uint32_t)RESET))
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
  * @brief  Clears the TIMx's interrupt pending bits.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 or 14
  *         to select the TIMx peripheral.
  * @param  TIM_IT: specifies the pending bit to clear.
  *          This parameter can be any combination of the following values:
  *            @arg TIM_IT_Update : TIM1 update Interrupt source
  *            @arg TIM_IT_CC1    : TIM Capture Compare 1 Interrupt source
  *            @arg TIM_IT_CC2    : TIM Capture Compare 2 Interrupt source
  *            @arg TIM_IT_CC3    : TIM Capture Compare 3 Interrupt source
  *            @arg TIM_IT_CC4    : TIM Capture Compare 4 Interrupt source
  *            @arg TIM_IT_COM    : TIM Commutation Interrupt source
  *            @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  *            @arg TIM_IT_Break  : TIM Break Interrupt source
  *
  * @note   TIM2, TIM3, TIM4 and TIM5 can generate TIM_IT_Update, TIM_IT_CC1,
  *         TIM_IT_CC2, TIM_IT_CC3, TIM_IT_CC4 and TIM_IT_Trigger interrupt.
  * @note   TIM6 and TIM7 can only generate an update interrupt.
  * @note   TIM9 and TIM12 can generate TIM_IT_Update, TIM_IT_CC1, TIM_IT_CC2 and
  *         TIM_IT_Trigger interrupt.
  * @note   TIM10, TIM11, TIM13 and TIM14 can generate TIM_IT_Update and TIM_IT_CC1
  *         interrupt.
  *
  * @note   TIM_IT_Break is used only with TIM1 and TIM8.
  * @note   TIM_IT_COM is used only with TIM1 and TIM8.
  *
  * @retval None
  */
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint32_t TIM_IT)
{
    /* Check the parameters */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_IT(TIM_IT));

    /* Clear the IT pending Bit */
    TIMx->SR = (uint32_t)~TIM_IT;
}

/**
  * @brief  Configures the TIMx's DMA interface.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_DMABase: DMA Base address.
  *          This parameter can be one of the following values:
  *            @arg TIM_DMABase_CR1
  *            @arg TIM_DMABase_CR2
  *            @arg TIM_DMABase_SMCR
  *            @arg TIM_DMABase_DIER
  *            @arg TIM_DMABase_SR
  *            @arg TIM_DMABase_EGR
  *            @arg TIM_DMABase_CCMR1
  *            @arg TIM_DMABase_CCMR2
  *            @arg TIM_DMABase_CCER
  *            @arg TIM_DMABase_CNT
  *            @arg TIM_DMABase_PSC
  *            @arg TIM_DMABase_ARR
  *            @arg TIM_DMABase_RCR
  *            @arg TIM_DMABase_CCR1
  *            @arg TIM_DMABase_CCR2
  *            @arg TIM_DMABase_CCR3
  *            @arg TIM_DMABase_CCR4
  *            @arg TIM_DMABase_BDTR
  *            @arg TIM_DMABase_DCR
  *            @arg TIM_DMABase_OR
  *            @arg TIM_DMABase_CCMR3
  *            @arg TIM_DMABase_CCR5
  *            @arg TIM_DMABase_CCR6
  *            @arg TIM_DMABase_AF1
  *            @arg TIM_DMABase_AF2
  *            @arg TIM_DMABase_TISEL
  * @param  TIM_DMABurstLength: DMA Burst length. This parameter can be one value
  *         between: TIM_DMABurstLength_1Transfer and TIM_DMABurstLength_18Transfers.
  * @retval None
  */
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint32_t TIM_DMABase, uint32_t TIM_DMABurstLength)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_DMA_BASE(TIM_DMABase));
    assert_param(IS_TIM_DMA_LENGTH(TIM_DMABurstLength));

    /* Set the DMA Base and the DMA Burst Length */
    TIMx->DCR = TIM_DMABase | TIM_DMABurstLength;
}

/**
  * @brief  Enables or disables the TIMx's DMA Requests.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7 or 8 to select the TIM peripheral.
  * @param  TIM_DMASource: specifies the DMA Request sources.
  *          This parameter can be any combination of the following values:
  *            @arg TIM_DMA_Update : TIM update Interrupt source
  *            @arg TIM_DMA_CC1    : TIM Capture Compare 1 DMA source
  *            @arg TIM_DMA_CC2    : TIM Capture Compare 2 DMA source
  *            @arg TIM_DMA_CC3    : TIM Capture Compare 3 DMA source
  *            @arg TIM_DMA_CC4    : TIM Capture Compare 4 DMA source
  *            @arg TIM_DMA_COM    : TIM Commutation DMA source
  *            @arg TIM_DMA_Trigger: TIM Trigger DMA source
  * @param  NewState: new state of the DMA Request sources.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_DMACmd(TIM_TypeDef* TIMx, uint32_t TIM_DMASource, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST6_PERIPH(TIMx));
    assert_param(IS_TIM_DMA_SOURCE(TIM_DMASource));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the DMA sources */
        TIMx->DIER |= TIM_DMASource;
    }
    else
    {
        /* Disable the DMA sources */
        TIMx->DIER &= (uint32_t)~TIM_DMASource;
    }
}

/**
  * @brief  Selects the TIMx peripheral Capture Compare DMA source.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the
  *         TIM peripheral.
  * @param  NewState: new state of the Capture Compare DMA source
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the CCDS Bit */
        TIMx->CR2 |= TIM_CR2_CCDS;
    }
    else
    {
        /* Reset the CCDS Bit */
        TIMx->CR2 &= (uint32_t)~((uint32_t)TIM_CR2_CCDS);
    }
}

/**
  * @}
  */

/**
  * @brief  Configures the TIMx internal Clock
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to
  *         select the TIM peripheral.
  * @retval None
  */
void TIM_InternalClockConfig(TIM_TypeDef* TIMx)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));

    /* Disable slave mode to clock the prescaler directly with the internal clock */
    TIMx->SMCR &= (uint32_t)(~((uint32_t)TIM_SMCR_SMS));
}

/**
  * @brief  Configures the TIMx Internal Trigger as External Clock
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select
  *         the TIM peripheral.
  * @param  TIM_ITRSource: Trigger source.
  *          This parameter can be one of the following values:
  *            @arg  TIM_TS_ITR0: Internal Trigger 0
  *            @arg  TIM_TS_ITR1: Internal Trigger 1
  *            @arg  TIM_TS_ITR2: Internal Trigger 2
  *            @arg  TIM_TS_ITR3: Internal Trigger 3
  * @retval None
  */
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint32_t TIM_InputTriggerSource)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_INTERNAL_TRIGGER_SELECTION(TIM_InputTriggerSource));

    /* Select the Internal Trigger */
    TIM_SelectInputTrigger(TIMx, TIM_InputTriggerSource);

    /* Select the External clock mode1 */
    TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
  * @brief  Configures the TIMx Trigger as External Clock
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select the
  *         TIM peripheral.
  * @param  TIM_TIxExternalCLKSource: Trigger source.
  *          This parameter can be one of the following values:
  *            @arg TIM_TIxExternalCLK1Source_TI1ED: TI1 Edge Detector
  *            @arg TIM_TIxExternalCLK1Source_TI1  : Filtered Timer Input 1
  *            @arg TIM_TIxExternalCLK1Source_TI2  : Filtered Timer Input 2
  * @param  TIM_ICPolarity: specifies the TIx Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  * @param  ICFilter: specifies the filter value.
  *          This parameter must be a value between 0x0 and 0xF.
  * @retval None
  */
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint32_t TIM_TIxExternalCLKSource,
                                uint32_t TIM_ICPolarity, uint32_t ICFilter)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_IC_POLARITY(TIM_ICPolarity));
    assert_param(IS_TIM_IC_FILTER(ICFilter));

    /* Configure the Timer Input Clock Source */
    if (TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2)
    {
        TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
    }
    else
    {
        TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
    }

    /* Select the Trigger source */
    TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);

    /* Select the External clock mode1 */
    TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
  * @brief  Configures the External clock Mode1
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_ExtTRGPrescaler: The external Trigger Prescaler.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPSC_OFF : ETRP Prescaler OFF.
  *            @arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *            @arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *            @arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  TIM_ExtTRGPolarity: The external Trigger Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPolarity_Inverted   : active low or falling edge active.
  *            @arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *          This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler, uint32_t TIM_ExtTRGPolarity,
                             uint32_t ExtTRGFilter)
{
    uint32_t tmpsmcr = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
    assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
    assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));

    /* Configure the ETR Clock source */
    TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);

    /* Get the TIMx SMCR register value */
    tmpsmcr = TIMx->SMCR;

    /* Reset the SMS Bits */
    tmpsmcr &= (uint32_t)(~((uint32_t)TIM_SMCR_SMS));

    /* Select the External clock mode1 */
    tmpsmcr |= TIM_SlaveMode_External1;

    /* Select the Trigger selection : ETRF */
    tmpsmcr &= (uint32_t)(~((uint32_t)TIM_SMCR_TS));
    tmpsmcr |= TIM_TS_ETRF;

    /* Write to TIMx SMCR */
    TIMx->SMCR = tmpsmcr;
}

/**
  * @brief  Configures the External clock Mode2
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_ExtTRGPrescaler: The external Trigger Prescaler.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPSC_OFF : ETRP Prescaler OFF.
  *            @arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *            @arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *            @arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  TIM_ExtTRGPolarity: The external Trigger Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPolarity_Inverted   : active low or falling edge active.
  *            @arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *          This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler,
                             uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
    assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
    assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));

    /* Configure the ETR Clock source */
    TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);

    /* Enable the External clock mode2 */
    TIMx->SMCR |= TIM_SMCR_ECE;
}

/**
  * @}
  */
/**
  * @brief  Selects the Input Trigger source
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to
  *         select the TIM peripheral.
  * @param  TIM_InputTriggerSource: The Input Trigger source.
  *          This parameter can be one of the following values:
  *            @arg TIM_TS_ITR0   : Internal Trigger 0
  *            @arg TIM_TS_ITR1   : Internal Trigger 1
  *            @arg TIM_TS_ITR2   : Internal Trigger 2
  *            @arg TIM_TS_ITR3   : Internal Trigger 3
  *            @arg TIM_TS_TI1F_ED: TI1 Edge Detector
  *            @arg TIM_TS_TI1FP1 : Filtered Timer Input 1
  *            @arg TIM_TS_TI2FP2 : Filtered Timer Input 2
  *            @arg TIM_TS_ETRF   : External Trigger input
  *
  * @note   TIM9 and TIM12 don't include TIM_TS_ETRF.
  *
  * @retval None
  */
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint32_t TIM_InputTriggerSource)
{
    uint32_t tmpsmcr = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_TRIGGER_SELECTION(TIM_InputTriggerSource));

    /* Get the TIMx SMCR register value */
    tmpsmcr = TIMx->SMCR;

    /* Reset the TS Bits */
    tmpsmcr &= (uint32_t)(~((uint32_t)TIM_SMCR_TS));

    /* Set the Input Trigger source */
    tmpsmcr |= TIM_InputTriggerSource;

    /* Write to TIMx SMCR */
    TIMx->SMCR = tmpsmcr;
}

/**
  * @brief  Selects the TIMx Trigger Output Mode.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 6, 7 or 8 to select the TIM peripheral.
  * @param  TIM_TRGOSource: specifies the Trigger Output source.
  *          This parameter can be one of the following values:
  *
  *   - For all TIMx
  *            @arg TIM_TRGOSource_Reset : The UG bit in the TIM_EGR register is used as the trigger output (TRGO).
  *            @arg TIM_TRGOSource_Enable: The Counter Enable CEN is used as the trigger output (TRGO).
  *            @arg TIM_TRGOSource_Update: The update event is selected as the trigger output (TRGO).
  *
  *   - For all TIMx except TIM6 and TIM7
  *            @arg TIM_TRGOSource_OC1   : The trigger output sends a positive pulse when the CC1IF flag
  *                                        is to be set, as soon as a capture or compare match occurs (TRGO).
  *            @arg TIM_TRGOSource_OC1Ref: OC1REF signal is used as the trigger output (TRGO).
  *            @arg TIM_TRGOSource_OC2Ref: OC2REF signal is used as the trigger output (TRGO).
  *            @arg TIM_TRGOSource_OC3Ref: OC3REF signal is used as the trigger output (TRGO).
  *            @arg TIM_TRGOSource_OC4Ref: OC4REF signal is used as the trigger output (TRGO).
  *
  * @retval None
  */
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint32_t TIM_TRGOSource)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST6_PERIPH(TIMx));
    assert_param(IS_TIM_TRGO_SOURCE(TIM_TRGOSource));

    /* Reset the MMS Bits */
    TIMx->CR2 &= (uint32_t)~((uint32_t)TIM_CR2_MMS);

    /* Select the TRGO source */
    TIMx->CR2 |=  TIM_TRGOSource;
}

/**
  * @brief  Selects the TIMx Trigger Output Mode.
  * @param  TIMx: where x can be 1 or 8 to select the TIM peripheral.
  * @param  TIM_TRGOSource: specifies the Trigger Output source.
  *          This parameter can be one of the following values:
  *            @arg TIM_TRGO2Source_Reset                       : TIMx_EGR.UG bit is used as trigger output (TRGO2)
  *            @arg TIM_TRGO2Source_Enable                      : TIMx_CR1.CEN bit is used as trigger output (TRGO2)
  *            @arg TIM_TRGO2Source_Update                      : Update event is used as trigger output (TRGO2)
  *            @arg TIM_TRGO2Source_OC1                         : Capture or a compare match 1 is used as trigger output (TRGO2)
  *            @arg TIM_TRGO2Source_OC1Ref                      : OC1REF signal is used as trigger output (TRGO2)
  *            @arg TIM_TRGO2Source_OC2Ref                      : OC2REF signal is used as trigger output (TRGO2)
  *            @arg TIM_TRGO2Source_OC3Ref                      : OC3REF signal is used as trigger output (TRGO2)
  *            @arg TIM_TRGO2Source_OC4Ref                      : OC4REF signal is used as trigger output (TRGO2)
  *            @arg TIM_TRGO2Source_OC5Ref                      : OC5REF signal is used as trigger output (TRGO2)
  *            @arg TIM_TRGO2Source_OC6Ref                      : OC6REF signal is used as trigger output (TRGO2)
  *            @arg TIM_TRGO2Source_OC4Ref_RisingFalling        : OC4REF rising or falling edges generate pulses on TRGO2
  *            @arg TIM_TRGO2Source_OC6Ref_RisingFalling        : OC6REF rising or falling edges generate pulses on TRGO2
  *            @arg TIM_TRGO2Source_OC4Ref_Rising_OC6Ref_Rising : OC4REF or OC6REF rising edges generate pulses on TRGO2
  *            @arg TIM_TRGO2Source_OC4Ref_Rising_OC6Ref_Falling: OC4REF rising or OC6REF falling edges generate pulses on TRGO2
  *            @arg TIM_TRGO2Source_OC5Ref_Rising_OC6Ref_Rising : OC5REF or OC6REF rising edges generate pulses on TRGO2
  *            @arg TIM_TRGO2Source_OC5Ref_Rising_OC6Ref_Falling: OC5REF or OC6REF rising edges generate pulses on TRGO2
  *
  * @retval None
  */
void TIM_SelectOutputTrigger2(TIM_TypeDef* TIMx, uint32_t TIM_TRGO2Source)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_TRGO2_SOURCE(TIM_TRGO2Source));

    /* Reset the MMS Bits */
    TIMx->CR2 &= (uint32_t)~((uint32_t)TIM_CR2_MMS2);

    /* Select the TRGO source */
    TIMx->CR2 |=  TIM_TRGO2Source;
}

/**
  * @brief  Selects the TIMx Slave Mode.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select the TIM peripheral.
  * @param  TIM_SlaveMode: specifies the Timer Slave Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM_SlaveMode_Reset    : Rising edge of the selected trigger signal (TRGI) re-initializes
  *                                          the counter and triggers an update of the registers.
  *            @arg TIM_SlaveMode_Gated    : The counter clock is enabled when the trigger signal (TRGI) is high.
  *            @arg TIM_SlaveMode_Trigger  : The counter starts at a rising edge of the trigger TRGI.
  *            @arg TIM_SlaveMode_External1: Rising edges of the selected trigger (TRGI) clock the counter.
  * @retval None
  */
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint32_t TIM_SlaveMode)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_SLAVE_MODE(TIM_SlaveMode));

    /* Reset the SMS Bits */
    TIMx->SMCR &= (uint32_t)~((uint32_t)TIM_SMCR_SMS);

    /* Select the Slave Mode */
    TIMx->SMCR |= TIM_SlaveMode;
}

/**
  * @brief  Sets or Resets the TIMx Master/Slave Mode.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select the TIM peripheral.
  * @param  TIM_MasterSlaveMode: specifies the Timer Master Slave Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM_MasterSlaveMode_Enable : synchronization between the current timer
  *                                              and its slaves (through TRGO).
  *            @arg TIM_MasterSlaveMode_Disable: No action
  * @retval None
  */
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint32_t TIM_MasterSlaveMode)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_MSM_STATE(TIM_MasterSlaveMode));

    /* Reset the MSM Bit */
    TIMx->SMCR &= (uint32_t)~((uint32_t)TIM_SMCR_MSM);

    /* Set or Reset the MSM Bit */
    TIMx->SMCR |= TIM_MasterSlaveMode;
}

/**
  * @brief  Configures the TIMx External Trigger (ETR).
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_ExtTRGPrescaler: The external Trigger Prescaler.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPSC_OFF : ETRP Prescaler OFF.
  *            @arg TIM_ExtTRGPSC_DIV2: ETRP frequency divided by 2.
  *            @arg TIM_ExtTRGPSC_DIV4: ETRP frequency divided by 4.
  *            @arg TIM_ExtTRGPSC_DIV8: ETRP frequency divided by 8.
  * @param  TIM_ExtTRGPolarity: The external Trigger Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ExtTRGPolarity_Inverted: active low or falling edge active.
  *            @arg TIM_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *          This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler, uint32_t TIM_ExtTRGPolarity,
                   uint32_t ExtTRGFilter)
{
    uint32_t tmpsmcr = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
    assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
    assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));

    tmpsmcr = TIMx->SMCR;

    /* Reset the ETR Bits */
    tmpsmcr &= SMCR_ETR_MASK;

    /* Set the Prescaler, the Filter value and the Polarity */
    tmpsmcr |= (uint32_t)(TIM_ExtTRGPrescaler | (uint32_t)(TIM_ExtTRGPolarity | (uint32_t)(ExtTRGFilter << (uint32_t)8)));

    /* Write to TIMx SMCR */
    TIMx->SMCR = tmpsmcr;
}

/**
  * @}
  */
/**
  * @brief  Configures the TIMx Encoder Interface.
  * @param  TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_EncoderMode: specifies the TIMx Encoder Mode.
  *          This parameter can be one of the following values:
  *            @arg TIM_EncoderMode_TI1 : counts up/down on TI2FP2 edge depending on TI1FP1 level.
  *            @arg TIM_EncoderMode_TI2 : counts up/down on TI1FP1 edge depending on TI2FP2 level.
  *            @arg TIM_EncoderMode_TI12: Counter counts on both TI1FP1 and TI2FP2 edges depending
  *                                       on the level of the other input.
  * @param  TIM_IC1Polarity: specifies the IC1 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_ICPolarity_Falling: IC Falling edge.
  *            @arg TIM_ICPolarity_Rising : IC Rising edge.
  * @param  TIM_IC2Polarity: specifies the IC2 Polarity
  *          This parmeter can be one of the following values:
  *            @arg TIM_ICPolarity_Falling: IC Falling edge.
  *            @arg TIM_ICPolarity_Rising : IC Rising edge.
  * @retval None
  */
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint32_t TIM_EncoderMode,
                                uint32_t TIM_IC1Polarity, uint32_t TIM_IC2Polarity)
{
    uint32_t tmpsmcr  = 0;
    uint32_t tmpccmr1 = 0;
    uint32_t tmpccer  = 0;

    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_ENCODER_MODE(TIM_EncoderMode));
    assert_param(IS_TIM_IC_POLARITY(TIM_IC1Polarity));
    assert_param(IS_TIM_IC_POLARITY(TIM_IC2Polarity));

    /* Get the TIMx SMCR register value */
    tmpsmcr = TIMx->SMCR;

    /* Get the TIMx CCMR1 register value */
    tmpccmr1 = TIMx->CCMR1;

    /* Get the TIMx CCER register value */
    tmpccer = TIMx->CCER;

    /* Set the encoder Mode */
    tmpsmcr &= (uint32_t)(~((uint32_t)TIM_SMCR_SMS));
    tmpsmcr |= TIM_EncoderMode;

    /* Select the Capture Compare 1 and the Capture Compare 2 as input */
    tmpccmr1 &= (uint32_t)(((uint32_t)~((uint32_t)TIM_CCMR1_CC1S)) & (uint32_t)(~((uint32_t)TIM_CCMR1_CC2S)));
    tmpccmr1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;

    /* Set the TI1 and the TI2 Polarities */
    tmpccer &= (uint32_t)~((uint32_t)(TIM_CCER_CC1P | TIM_CCER_CC1NP)) & (uint32_t)~((uint32_t)(TIM_CCER_CC2P | TIM_CCER_CC2NP));
    tmpccer |= (uint32_t)(TIM_IC1Polarity | (uint32_t)(TIM_IC2Polarity << (uint32_t)4));

    /* Write to TIMx SMCR */
    TIMx->SMCR = tmpsmcr;

    /* Write to TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmr1;

    /* Write to TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Enables or disables the TIMx's Hall sensor interface.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  NewState: new state of the TIMx Hall sensor interface.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the TI1S Bit */
        TIMx->CR2 |= TIM_CR2_TI1S;
    }
    else
    {
        /* Reset the TI1S Bit */
        TIMx->CR2 &= (uint32_t)~((uint32_t)TIM_CR2_TI1S);
    }
}

/**
  * @}
  */

/**
  * @brief  Configures the TIM2 or TIM11 OR register Remapping input Capabilities.
  * @param  TIMx: where x can be 2 or 11 to select the TIM peripheral.
  * @param  TIM_Remap: specifies the TIM input reampping source.
  *          This parameter can be one of the following values:
  *
  *   - For TIM2
  *            @arg TIM2_ITR1ConnectTIM8Trgo: TIM8 TRGO  is connected to TIM2_ITR1 input
  *            @arg TIM2_ITR1ConnectPTPTrgo : PTP TRGO   is connected to TIM2_ITR1 input
  *            @arg TIM2_ITR1ConnectOTGFSSOF: OTG FS SOF is connected to TIM2_ITR1 input
  *            @arg TIM2_ITR1ConnectOTGHSSOF: OTG HS SOF is connected to TIM2_ITR1 input
  *
  *   - For TIM11
  *            @arg TIM11_IT1ConnectGPIO_0 : TIM11 GPIO    is connected to TIM11_TI1 input
  *            @arg TIM11_IT1ConnectGPIO_1 : TIM11 GPIO    is connected to TIM11_TI1 input
  *            @arg TIM11_IT1ConnectHSE_RTC: HSE RTC clock is connected to TIM11_TI1 input
  *            @arg TIM11_IT1ConnectGPIO_3 : TIM11 GPIO    is connected to TIM11_TI1 input
  *
  * @retval None
  */
void TIM_RemapConfig(TIM_TypeDef* TIMx, uint32_t TIM_Remap)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST7_PERIPH(TIMx));

    /* Check the parameters - TIM_Remap */
    if (TIMx == TIM2)
    {
        assert_param(IS_TIM2_ITR1REMAP(TIM_Remap));
    }
    else
    {
        assert_param(IS_TIM11_ITR1REMAP(TIM_Remap));
    }

    /* Clear the Timer ITR1_RMP or IT1_RMP remapping configuration */
    if (TIMx == TIM2)
    {
        TIMx->OR &= (uint32_t)(~(3 << (uint32_t)10));
    }
    else
    {
        TIMx->OR &= (uint32_t)(~(3 << (uint32_t)0));
    }

    /* Set the Timer remapping configuration */
    if (TIMx == TIM2)
    {
        TIMx->OR = (uint32_t)(TIM_Remap << (uint32_t)10);
    }
    else
    {
        TIMx->OR =  TIM_Remap;
    }
}

/**
  * @brief  Configures the TIMx ETRSEL[3:0] bits of AF1 register Remapping input Capabilities.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_ETRSel_Remap: specifies the TIM etrsel input reampping source.
  *          This parameter can be one of the following values:
  *
  *   - For TIM1 and TIM8
  *            @arg TIM_ETR_GPIO     : ETR input is connected to GPIO
  *            @arg TIM_ETR_COMP1    : ETR input is connected to COMP1_OUT
  *            @arg TIM_ETR_COMP2    : ETR input is connected to COMP2_OUT
  *            @arg TIM_ETR_COMP3    : ETR input is connected to COMP3_OUT
  *            @arg TIM_ETR_COMP4    : ETR input is connected to COMP4_OUT
  *            @arg TIM_ETR_COMP5    : ETR input is connected to COMP5_OUT
  *            @arg TIM_ETR_COMP6    : ETR input is connected to COMP6_OUT
  *            @arg TIM_ETR_ADC1_AWD1: ETR input is connected to ADC1 analog watchdog 1
  *            @arg TIM_ETR_ADC1_AWD2: ETR input is connected to ADC1 analog watchdog 2
  *            @arg TIM_ETR_ADC1_AWD3: ETR input is connected to ADC1 analog watchdog 3
  *            @arg TIM_ETR_ADC2_AWD1: ETR input is connected to ADC2 analog watchdog 1
  *            @arg TIM_ETR_ADC2_AWD2: ETR input is connected to ADC2 analog watchdog 2
  *            @arg TIM_ETR_ADC2_AWD3: ETR input is connected to ADC2 analog watchdog 3
  *            @arg TIM_ETR_ADC3_AWD1: ETR input is connected to ADC3 analog watchdog 1
  *            @arg TIM_ETR_ADC3_AWD2: ETR input is connected to ADC3 analog watchdog 2
  *            @arg TIM_ETR_ADC3_AWD3: ETR input is connected to ADC3 analog watchdog 3
  *
  *   - For TIM2, TIM3, TIM4 and TIM5
  *            @arg TIM_ETR_GPIO: ETR input is connected to GPIO
  *            @arg TIM_ETR_1   : ETR input is connected to ETR[ 1]
  *            @arg TIM_ETR_2   : ETR input is connected to ETR[ 2]
  *            @arg TIM_ETR_3   : ETR input is connected to ETR[ 3]
  *            @arg TIM_ETR_4   : ETR input is connected to ETR[ 4]
  *            @arg TIM_ETR_5   : ETR input is connected to ETR[ 5]
  *            @arg TIM_ETR_6   : ETR input is connected to ETR[ 6]
  *            @arg TIM_ETR_7   : ETR input is connected to ETR[ 7]
  *            @arg TIM_ETR_8   : ETR input is connected to ETR[ 8]
  *            @arg TIM_ETR_9   : ETR input is connected to ETR[ 9]
  *            @arg TIM_ETR_10  : ETR input is connected to ETR[10]
  *            @arg TIM_ETR_11  : ETR input is connected to ETR[11]
  *            @arg TIM_ETR_12  : ETR input is connected to ETR[12]
  *            @arg TIM_ETR_13  : ETR input is connected to ETR[13]
  *            @arg TIM_ETR_14  : ETR input is connected to ETR[14]
  *            @arg TIM_ETR_15  : ETR input is connected to ETR[15]
  *
  * @retval None
  */
void TIM_ETRSelRemapConfig(TIM_TypeDef* TIMx, uint32_t TIM_ETRSel_Remap)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));

    /* Check the parameters - TIM_ETRSel_Remap */
    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        assert_param(IS_TIM_ETRSEL_LIST1_REMAP(TIM_ETRSel_Remap));
    }
    else
    {
        if ((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
        {
            assert_param(IS_TIM_ETRSEL_LIST2_REMAP(TIM_ETRSel_Remap));
        }
    }

    /* Clear the Timer ETRSEL remapping configuration */
    TIMx->AF1 &= (uint32_t)(~TIM_AF1_ETRSEL);

    /* Set the Timer ETRSEL remapping configuration */
    TIMx->AF1 |= TIM_ETRSel_Remap;
}

/**
  * @brief  Configures the TIMx OCRSEL[2:0] bits of AF2 register Remapping input Capabilities.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_OCRSel_Remap: specifies the TIM ocrsel input reampping source.
  *          This parameter can be one of the following values:
  *
  *   - For TIM1 and TIM8
  *            @arg TIM_OCR_COMP1: OCxref clear source select COMP1_OUT
  *            @arg TIM_OCR_COMP2: OCxref clear source select COMP2_OUT
  *            @arg TIM_OCR_COMP3: OCxref clear source select COMP3_OUT
  *            @arg TIM_OCR_COMP4: OCxref clear source select COMP4_OUT
  *            @arg TIM_OCR_COMP5: OCxref clear source select COMP5_OUT
  *            @arg TIM_OCR_COMP6: OCxref clear source select COMP6_OUT
  *
  *   - For TIM2, TIM3, TIM4 and TIM5
  *            @arg TIM_OCR_CLEAR_0: OCxref clear source select ocrefcr[0]
  *            @arg TIM_OCR_CLEAR_1: OCxref clear source select ocrefcr[1]
  *            @arg TIM_OCR_CLEAR_2: OCxref clear source select ocrefcr[2]
  *            @arg TIM_OCR_CLEAR_3: OCxref clear source select ocrefcr[3]
  *            @arg TIM_OCR_CLEAR_4: OCxref clear source select ocrefcr[4]
  *            @arg TIM_OCR_CLEAR_5: OCxref clear source select ocrefcr[5]
  *            @arg TIM_OCR_CLEAR_6: OCxref clear source select ocrefcr[6]
  *            @arg TIM_OCR_CLEAR_7: OCxref clear source select ocrefcr[7]
  *
  * @retval None
  */
void TIM_OCRSelRemapConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCRSel_Remap)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));

    /* Check the parameters - TIM_OCRSel_Remap */
    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        assert_param(IS_TIM_OCRSEL_LIST1_REMAP(TIM_OCRSel_Remap));
    }
    else
    {
        if ((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
        {
            assert_param(IS_TIM_OCRSEL_LIST2_REMAP(TIM_OCRSel_Remap));
        }
    }

    /* Clear the Timer OCRSEL remapping configuration */
    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        TIMx->AF2 &= (uint32_t)(~(7 << (uint32_t)0));
    }
    else
    {
        if ((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
        {
            TIMx->AF2 &= (uint32_t)(~(TIM_AF2_OCRSEL));
        }
    }

    /* Set the Timer OCRSEL remapping configuration */
    TIMx->AF2 |= TIM_OCRSel_Remap;
}

/**
  * @brief  Configures the TIMx TIxSEL[2:0] bits of TISEL register Remapping input Capabilities.
  * @param  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIxSEL: where x can be 1, 2, 3 or 4 to select the TIM TISEL.
  * @param  TIM_TISel_Channel: specifies the TIM tisel input channel select.
  *          This parameter can be one of the following values:
  *
  *   - For TIM1 and TIM8
  *            @arg TIM_TISel_Channel1
  *
  *   - For TIM2, TIM3, TIM4 and TIM5
  *            @arg TIM_TISel_Channel1
  *            @arg TIM_TISel_Channel2
  *            @arg TIM_TISel_Channel3
  *            @arg TIM_TISel_Channel4
  *
  * @param  TIM_TISel_Remap: specifies the TIM tisel input reampping source.
  *          This parameter can be one of the following values:
  *
  *   - For TIM1 and TIM8
  *            @arg TIM_TI1_CH1  : TIM_CH1 input select GPIO
  *            @arg TIM_TI1_COMP1: TIM_CH1 input select COMP1_OUT
  *            @arg TIM_TI1_COMP2: TIM_CH1 input select COMP2_OUT
  *            @arg TIM_TI1_COMP3: TIM_CH1 input select COMP3_OUT
  *            @arg TIM_TI1_COMP4: TIM_CH1 input select COMP4_OUT
  *            @arg TIM_TI1_COMP5: TIM_CH1 input select COMP5_OUT
  *            @arg TIM_TI1_COMP6: TIM_CH1 input select COMP6_OUT
  *
  *   - For TIM2, TIM3, TIM4 and TIM5
  *            @arg TIM_TI_CH : TIM_CH input select GPIO
  *            @arg TIM_TI_I1 : TIM_CH input select ti_i[ 1]
  *            @arg TIM_TI_I2 : TIM_CH input select ti_i[ 2]
  *            @arg TIM_TI_I3 : TIM_CH input select ti_i[ 3]
  *            @arg TIM_TI_I4 : TIM_CH input select ti_i[ 4]
  *            @arg TIM_TI_I5 : TIM_CH input select ti_i[ 5]
  *            @arg TIM_TI_I6 : TIM_CH input select ti_i[ 6]
  *            @arg TIM_TI_I7 : TIM_CH input select ti_i[ 7]
  *            @arg TIM_TI_I8 : TIM_CH input select ti_i[ 8]
  *            @arg TIM_TI_I9 : TIM_CH input select ti_i[ 9]
  *            @arg TIM_TI_I10: TIM_CH input select ti_i[10]
  *            @arg TIM_TI_I11: TIM_CH input select ti_i[11]
  *            @arg TIM_TI_I12: TIM_CH input select ti_i[12]
  *            @arg TIM_TI_I13: TIM_CH input select ti_i[13]
  *            @arg TIM_TI_I14: TIM_CH input select ti_i[14]
  *            @arg TIM_TI_I15: TIM_CH input select ti_i[15]
  *
  * @retval None
  */
void TIM_TISelRemapConfig(TIM_TypeDef* TIMx, uint32_t TIM_TISel_Channel, uint32_t TIM_TISel_Remap)
{
    /* Check the parameters */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));

    /* Check the parameters - TIM_TISel_Remap */
    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        assert_param(IS_TIM_TISEL_LIST1_REMAP(TIM_TISel_Remap));
    }
    else
    {
        if ((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
        {
            assert_param(IS_TIM_TISEL_LIST2_REMAP(TIM_TISel_Remap));
        }
    }

    /* Clear the Timer TISEL remapping configuration */
    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        TIMx->TISEL &= (uint32_t)(~(7 << (uint32_t)TIM_TISel_Channel1));
    }
    else
    {
        if ((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
        {
            TIMx->TISEL &= (uint32_t)(~(TIM_TISEL_TI1SEL << TIM_TISel_Channel));
        }
    }

    /* Set the Timer TIxSEL remapping configuration */
    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        TIMx->TISEL |= (uint32_t)((TIM_TISel_Remap << (uint32_t)TIM_TISel_Channel1));
    }
    else
    {
        if ((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
        {
            TIMx->TISEL |= (uint32_t)((TIM_TISel_Remap << TIM_TISel_Channel));
        }
    }
}

/**
  * @}
  */

/**
  * @brief  Configure the TI1 as Input.
  * @param  TIMx: where x can from 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 or 14 to select the TIM peripheral.
  * @param  TIM_ICPolarity: The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  * @param  TIM_ICSelection: specifies the input to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICSelection_DirectTI  : TIM Input 1 is selected to be connected to IC1.
  *            @arg TIM_ICSelection_IndirectTI: TIM Input 1 is selected to be connected to IC2.
  *            @arg TIM_ICSelection_TRC       : TIM Input 1 is selected to be connected to TRC.
  * @param  TIM_ICFilter: Specifies the Input Capture Filter.
  *          This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI1_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter)
{
    uint32_t tmpccmr1 = 0, tmpccer = 0;

    /* Disable the Channel 1: Reset the CC1E Bit */
    TIMx->CCER &= (uint32_t)~((uint32_t)TIM_CCER_CC1E);
    tmpccmr1 = TIMx->CCMR1;
    tmpccer = TIMx->CCER;

    /* Select the Input and set the filter */
    tmpccmr1 &= (uint32_t)(((uint32_t)~((uint32_t)TIM_CCMR1_CC1S)) & ((uint32_t)~((uint32_t)TIM_CCMR1_IC1F)));
    tmpccmr1 |= (uint32_t)(TIM_ICSelection | (uint32_t)(TIM_ICFilter << (uint32_t)4));

    /* Select the Polarity and set the CC1E Bit */
    tmpccer &= (uint32_t)~((uint32_t)(TIM_CCER_CC1P | TIM_CCER_CC1NP));
    tmpccer |= (uint32_t)(TIM_ICPolarity | (uint32_t)TIM_CCER_CC1E);

    /* Write to TIMx CCMR1 and CCER registers */
    TIMx->CCMR1 = tmpccmr1;
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configure the TI2 as Input.
  * @param  TIMx: where x can from 1, 2, 3, 4, 5, 8, 9 or 12 to select the TIM peripheral.
  * @param  TIM_ICPolarity: The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  * @param  TIM_ICSelection: specifies the input to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICSelection_DirectTI  : TIM Input 2 is selected to be connected to IC2.
  *            @arg TIM_ICSelection_IndirectTI: TIM Input 2 is selected to be connected to IC1.
  *            @arg TIM_ICSelection_TRC       : TIM Input 2 is selected to be connected to TRC.
  * @param  TIM_ICFilter: Specifies the Input Capture Filter.
  *          This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI2_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter)
{
    uint32_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;

    /* Disable the Channel 2: Reset the CC2E Bit */
    TIMx->CCER &= (uint32_t)~((uint32_t)TIM_CCER_CC2E);
    tmpccmr1 = TIMx->CCMR1;
    tmpccer = TIMx->CCER;
    tmp = (uint32_t)(TIM_ICPolarity << 4);

    /* Select the Input and set the filter */
    tmpccmr1 &= (uint32_t)(((uint32_t)~((uint32_t)TIM_CCMR1_CC2S)) & ((uint32_t)~((uint32_t)TIM_CCMR1_IC2F)));
    tmpccmr1 |= (uint32_t)(TIM_ICFilter << 12);
    tmpccmr1 |= (uint32_t)(TIM_ICSelection << 8);

    /* Select the Polarity and set the CC2E Bit */
    tmpccer &= (uint32_t)~((uint32_t)(TIM_CCER_CC2P | TIM_CCER_CC2NP));
    tmpccer |= (uint32_t)(tmp | (uint32_t)TIM_CCER_CC2E);

    /* Write to TIMx CCMR1 and CCER registers */
    TIMx->CCMR1 = tmpccmr1 ;
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configure the TI3 as Input.
  * @param  TIMx: where x can from 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_ICPolarity: The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  * @param  TIM_ICSelection: specifies the input to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICSelection_DirectTI  : TIM Input 3 is selected to be connected to IC3.
  *            @arg TIM_ICSelection_IndirectTI: TIM Input 3 is selected to be connected to IC4.
  *            @arg TIM_ICSelection_TRC       : TIM Input 3 is selected to be connected to TRC.
  * @param  TIM_ICFilter: Specifies the Input Capture Filter.
  *          This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI3_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter)
{
    uint32_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

    /* Disable the Channel 3: Reset the CC3E Bit */
    TIMx->CCER &= (uint32_t)~((uint32_t)TIM_CCER_CC3E);
    tmpccmr2 = TIMx->CCMR2;
    tmpccer = TIMx->CCER;
    tmp = (uint32_t)(TIM_ICPolarity << 8);

    /* Select the Input and set the filter */
    tmpccmr2 &= (uint32_t)(((uint32_t)~((uint32_t)TIM_CCMR2_CC3S)) & ((uint32_t)~((uint32_t)TIM_CCMR2_IC3F)));
    tmpccmr2 |= (uint32_t)(TIM_ICSelection | (uint32_t)(TIM_ICFilter << (uint32_t)4));

    /* Select the Polarity and set the CC3E Bit */
    tmpccer &= (uint32_t)~((uint32_t)(TIM_CCER_CC3P | TIM_CCER_CC3NP));
    tmpccer |= (uint32_t)(tmp | (uint32_t)TIM_CCER_CC3E);

    /* Write to TIMx CCMR2 and CCER registers */
    TIMx->CCMR2 = tmpccmr2;
    TIMx->CCER = tmpccer;
}

/**
  * @brief  Configure the TI4 as Input.
  * @param  TIMx: where x can from 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
  * @param  TIM_ICPolarity: The Input Polarity.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  * @param  TIM_ICSelection: specifies the input to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM_ICSelection_DirectTI  : TIM Input 4 is selected to be connected to IC4.
  *            @arg TIM_ICSelection_IndirectTI: TIM Input 4 is selected to be connected to IC3.
  *            @arg TIM_ICSelection_TRC       : TIM Input 4 is selected to be connected to TRC.
  * @param  TIM_ICFilter: Specifies the Input Capture Filter.
  *          This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI4_Config(TIM_TypeDef* TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter)
{
    uint32_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

    /* Disable the Channel 4: Reset the CC4E Bit */
    TIMx->CCER &= (uint32_t)~((uint32_t)TIM_CCER_CC4E);
    tmpccmr2 = TIMx->CCMR2;
    tmpccer = TIMx->CCER;
    tmp = (uint32_t)(TIM_ICPolarity << 12);

    /* Select the Input and set the filter */
    tmpccmr2 &= (uint32_t)((uint32_t)(~(uint32_t)TIM_CCMR2_CC4S) & ((uint32_t)~((uint32_t)TIM_CCMR2_IC4F)));
    tmpccmr2 |= (uint32_t)(TIM_ICSelection << 8);
    tmpccmr2 |= (uint32_t)(TIM_ICFilter << 12);

    /* Select the Polarity and set the CC4E Bit */
    tmpccer &= (uint32_t)~((uint32_t)(TIM_CCER_CC4P));
    tmpccer |= (uint32_t)(tmp | (uint32_t)TIM_CCER_CC4E);

    /* Write to TIMx CCMR2 and CCER registers */
    TIMx->CCMR2 = tmpccmr2;
    TIMx->CCER = tmpccer;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
