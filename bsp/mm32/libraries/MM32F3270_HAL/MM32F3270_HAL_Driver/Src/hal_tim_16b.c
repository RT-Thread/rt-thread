/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_tim_16b.h"

bool TIM_16B_Init(TIM_16B_Type * TIMx, TIM_16B_Init_Type * init)
{
    uint32_t cr1 = TIMx->CR1 &~ ( TIM_16B_CR1_OPM_MASK
                                | TIM_16B_CR1_APRE_MASK
                                | TIM_16B_CR1_CMS_MASK
                                | TIM_16B_CR1_DIR_MASK
                                );
    cr1 |= TIM_16B_CR1_OPM(init->PeriodMode);
    cr1 |= ((init->EnablePreloadPeriod) ? TIM_16B_CR1_APRE_MASK: 0u);
    switch ( init->CountMode )
    {
        case TIM_16B_CountMode_Increasing:
            break;
        case TIM_16B_CountMode_Decreasing:
            cr1 |= TIM_16B_CR1_DIR_MASK;
            break;
        case TIM_16B_CountMode_CenterAligned1:
            cr1 |= TIM_16B_CR1_CMS(1u);
            break;
        case TIM_16B_CountMode_CenterAligned2:
            cr1 |= TIM_16B_CR1_CMS(2u);
            break;
        case TIM_16B_CountMode_CenterAligned3:
            cr1 |= TIM_16B_CR1_CMS(3u);
            break;
        default:
            break;
    }
    TIMx->CR1 = cr1;
    /* Check the vadility of StepFreqHz. */
    if ( (init->StepFreqHz == 0u) || (init->StepFreqHz > init->ClockFreqHz) )
    {
        return false;
    }
    /* Calculate the prescaler. */
    TIMx->PSC = init->ClockFreqHz / init->StepFreqHz - 1u;
    TIMx->ARR = init->Period;
    return true;
}

void TIM_16B_Start(TIM_16B_Type * TIMx)
{
    TIMx->CR1 |= TIM_16B_CR1_CEN_MASK;
}

void TIM_16B_Stop(TIM_16B_Type * TIMx)
{
    TIMx->CR1 &= ~TIM_16B_CR1_CEN_MASK;
}

uint32_t TIM_16B_GetCounterValue(TIM_16B_Type * TIMx)
{
    return TIMx->CNT;
}

void TIM_16B_ClearCounterValue(TIM_16B_Type * TIMx)
{
    TIMx->CNT = 0u;
}

void TIM_16B_EnableInterrupts(TIM_16B_Type * TIMx, uint32_t interrupts, bool enable)
{
    if (enable)
    {
        TIMx->DIER |= interrupts;
    }
    else
    {
        TIMx->DIER &= ~interrupts;
    }
}

void TIM_16B_EnableDMA(TIM_16B_Type * TIMx, uint32_t dmas, bool enable)
{
    if (enable)
    {
        TIMx->DIER |= dmas;
    }
    else
    {
        TIMx->DIER &= ~dmas;
    }
}

void TIM_16B_DoSwTrigger(TIM_16B_Type * TIMx, uint32_t swtrgs)
{
    TIMx->EGR = swtrgs;
}

uint32_t TIM_16B_GetInterruptStatus(TIM_16B_Type * TIMx)
{
    return TIMx->SR;
}

void TIM_16B_ClearInterruptStatus(TIM_16B_Type * TIMx, uint32_t status)
{
    TIMx->SR &= ~status;
}

/*******************************/
static void _TIM_16B_WriteChannelCtrlReg(TIM_16B_Type * TIMx, uint32_t channel, uint32_t regval)
{
    switch (channel)
    {
    case TIM_16B_CHN_1:
        TIMx->CCMR1 = (TIMx->CCMR1 & ~(0xFF)) | (regval & 0xFF);
        break;
    case TIM_16B_CHN_2:
        TIMx->CCMR1 = (TIMx->CCMR1 & ~(0xFF00)) | ((regval & 0xFF) << 8u);
        break;
    case TIM_16B_CHN_3:
        TIMx->CCMR2 = (TIMx->CCMR2 & ~(0xFF)) | (regval & 0xFF);
        break;
    case TIM_16B_CHN_4:
        TIMx->CCMR2 = (TIMx->CCMR2 & ~(0xFF00)) | ((regval & 0xFF) << 8u);
        break;
    default:
        break;
    }
}

void TIM_16B_EnableOutputCompare(TIM_16B_Type * TIMx, uint32_t channel, TIM_16B_OutputCompareConf_Type * conf)
{

    uint32_t regval = TIM_16B_CCMR1_CC1S(TIM_16B_ChannelIOMode_Out) /* output compare mode. */
                    | ( (conf->EnableFastOutput) ? TIM_16B_CCMR1_OC1FE_MASK : 0u ) /* fast output. */
                    | ( (conf->EnablePreLoadChannelValue) ? TIM_16B_CCMR1_OC1PE_MASK : 0u) /* preload of channel value. */
                    | TIM_16B_CCMR1_OC1M(conf->RefOutMode) /* output compare comparison mode. */
                    | ( (conf->ClearRefOutOnExtTrigger) ? TIM_16B_CCMR1_OC1CE_MASK : 0u) /* external trigger clear ref. */
                    ;

    _TIM_16B_WriteChannelCtrlReg(TIMx, channel, regval);

    TIM_16B_PutChannelValue(TIMx, channel, conf->ChannelValue);

    switch (conf->PinPolarity)
    {
        case TIM_16B_PinPolarity_Disable:
            TIMx->CCER &= ~( TIM_16B_CCER_CC1E_MASK << (channel<<2u) );
            break;

        case TIM_16B_PinPolarity_Rising:
            TIMx->CCER = ( TIMx->CCER & ~(0xF << (channel<<2u)) )
                       | (( TIM_16B_CCER_CC1E_MASK /* Enable the pin output / input. */
                       ) << (channel<<2u));
            break;

        case TIM_16B_PinPolarity_Falling:
            TIMx->CCER = ( TIMx->CCER & ~(0xF << (channel<<2u)) )
                       | (( TIM_16B_CCER_CC1E_MASK /* Enable the pin output / input. */
                       |    TIM_16B_CCER_CC1P_MASK /* Set output active polarity. */
                       |   ~TIM_16B_CCER_CC1NP_MASK
                       ) << (channel<<2u));
            break;

        default:
            break;
    }
}

void TIM_16B_EnableInputCapture(TIM_16B_Type * TIMx, uint32_t channel, TIM_16B_InputCaptureConf_Type * conf)
{
    uint32_t regval = TIM_16B_CCMR1_CC1S(TIM_16B_ChannelIOMode_In) /* input capture mode. */
                    | TIM_16B_CCMR1_IC1PSC(conf->InDiv)
                    | TIM_16B_CCMR1_IC1F(conf->InFilter)
                    ;

    _TIM_16B_WriteChannelCtrlReg(TIMx, channel, regval);

    switch (conf->PinPolarity)
    {
        case TIM_16B_PinPolarity_Disable:
            TIMx->CCER &= ~(TIM_16B_CCER_CC1E_MASK << (channel<<2u));
            break;
        case TIM_16B_PinPolarity_Rising:
            TIMx->CCER = (TIMx->CCER & ~(0xF << (channel<<2u)) )
                       | (( TIM_16B_CCER_CC1E_MASK /* Enable the pin output / input */
                       ) << (channel<<2u) );
            break;
        case TIM_16B_PinPolarity_Falling:
            TIMx->CCER = ( TIMx->CCER & ~(0xF << (channel<<2u)) )
                       | (( TIM_16B_CCER_CC1E_MASK /* Enable the pin output / input */
                       |    TIM_16B_CCER_CC1P_MASK /* Set active input edge. */
                       ) << (channel<<2u) );
            break;
        case TIM_16B_PinPolarity_RisingOrFalling:
            TIMx->CCER = ( TIMx->CCER & ~(0xF << (channel<<2u)) )
                       | (( TIM_16B_CCER_CC1E_MASK /* Enable the pin output / input */
                       |    TIM_16B_CCER_CC1P_MASK /* Set active input edge. */
                       |    TIM_16B_CCER_CC1NP_MASK
                       ) << (channel<<2u) );
            break;
        default:
            break;
    }
}

uint16_t TIM_16B_GetChannelValue(TIM_16B_Type * TIMx, uint32_t channel)
{
    return TIMx->CCR[channel];
}

void TIM_16B_PutChannelValue(TIM_16B_Type * TIMx, uint32_t channel, uint16_t value)
{
    TIMx->CCR[channel] = value;
}

void TIM_16B_EnableDeadArea(TIM_16B_Type * TIMx, TIM_16B_DeadAreaConf_Type * conf)
{
    TIMx->CR1 = ( TIMx->CR1 &~ TIM_16B_CR1_CKD_MASK )
              | ( TIM_16B_CR1_CKD(conf->StepFreqHz) ); /* set the frequncy ratio. */
}

void TIM_16B_EnableMasterMode(TIM_16B_Type * TIMx, TIM_16B_MasterModeConf_Type * conf)
{
    TIMx->CR2 = ( TIMx->CR2 &~ TIM_16B_CR2_MMS_MASK )
              | ( TIM_16B_CR2_MMS(conf->Out) ); /* Set master mode output. */

    uint32_t smcr = TIMx->SMCR &~ TIM_16B_SMCR_MSM_MASK;
    if (conf->EnableSync) /* synchronize with slave timers. */
    {
        smcr |= TIM_16B_SMCR_MSM_MASK;
    }
    TIMx->SMCR = smcr;
}

void TIM_16B_EnableSlaveMode(TIM_16B_Type * TIMx, TIM_16B_SlaveModeConf_Type * conf)
{
    if ( conf->Resp != TIM_16B_SlaveResp_Disable )
    {
        TIMx->SMCR = ( TIMx->SMCR &~ ( TIM_16B_SMCR_TS_MASK
                                   | TIM_16B_SMCR_SMS_MASK
                                   ) )
                   | TIM_16B_SMCR_TS(conf->In) /* set input trigger source. */
                   | TIM_16B_SMCR_SMS(conf->Resp); /* set response to the source */
    }
    else
    {
        TIMx->SMCR &= ~ TIM_16B_SMCR_SMS_MASK;
    }
}

void TIM_16B_EnableExtTriggerIn(TIM_16B_Type * TIMx, TIM_16B_ExtTriggerInConf_Type * conf)
{
    uint32_t smcr = TIMx->SMCR &~ ( TIM_16B_SMCR_ETPS_MASK
                                  | TIM_16B_SMCR_ETF_MASK
                                  | TIM_16B_SMCR_ECE_MASK
                                  | TIM_16B_SMCR_ETP_MASK
                                  );
    switch (conf->PinPolarity)
    {
        case TIM_16B_PinPolarity_Disable:
            break;
        case TIM_16B_PinPolarity_Rising:
            smcr |= TIM_16B_SMCR_ECE_MASK; /* enable external trigger input. */
            break;
        case TIM_16B_PinPolarity_Falling:
            smcr |= TIM_16B_SMCR_ETP_MASK; /* falling edge active. */
            smcr |= TIM_16B_SMCR_ECE_MASK; /* enable external trigger input. */
            break;
        default:
            break;
    }
    smcr |= TIM_16B_SMCR_ETPS( conf->InDiv ); /* division to the input external trigger. */
    smcr |= TIM_16B_SMCR_ETF( conf->InFilter ); /* set filter. */
    TIMx->SMCR = smcr;
}

uint32_t TIM_16B_EnableDMABurst(TIM_16B_Type * TIMx, TIM_16B_DMABurstConf_Type * conf)
{
    TIMx->DCR = TIM_16B_DCR_DBA(conf->BaseAddr) | TIM_16B_DCR_DBL(conf->Length);
    return (uint32_t)(&(TIMx->DMAR));
}

TIM_16B_EncoderDirection_Type TIM_16B_GetEncoder(TIM_16B_Type * TIMx, uint32_t * value)
{
    if (value)
    {
        * value = TIM_16B_GetCounterValue(TIMx);
    }

    if ( (TIMx->CR1 & TIM_16B_CR1_DIR_MASK) != 0u )
    {
        return TIM_16B_EncoderDirection_Backward;
    }
    else
    {
        return TIM_16B_EncoderDirection_Forward;
    }
}

/* EOF. */

