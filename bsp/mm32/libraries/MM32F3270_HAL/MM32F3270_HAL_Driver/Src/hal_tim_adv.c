/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_tim_adv.h"

bool TIM_ADV_Init(TIM_ADV_Type * TIMx, TIM_ADV_Init_Type * init)
{
    uint32_t cr1 = TIMx->CR1 &~ ( TIM_ADV_CR1_OPM_MASK
                                | TIM_ADV_CR1_APRE_MASK
                                | TIM_ADV_CR1_CMS_MASK
                                | TIM_ADV_CR1_DIR_MASK
                                );
    cr1 |= TIM_ADV_CR1_OPM(init->PeriodMode);
    cr1 |= ((init->EnablePreloadPeriod) ? TIM_ADV_CR1_APRE_MASK: 0u);
    switch ( init->CountMode )
    {
        case TIM_ADV_CountMode_Increasing:
            break;
        case TIM_ADV_CountMode_Decreasing:
            cr1 |= TIM_ADV_CR1_DIR_MASK;
            break;
        case TIM_ADV_CountMode_CenterAligned1:
            cr1 |= TIM_ADV_CR1_CMS(1u);
            break;
        case TIM_ADV_CountMode_CenterAligned2:
            cr1 |= TIM_ADV_CR1_CMS(2u);
            break;
        case TIM_ADV_CountMode_CenterAligned3:
            cr1 |= TIM_ADV_CR1_CMS(3u);
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

void TIM_ADV_Start(TIM_ADV_Type * TIMx)
{
    TIMx->CR1 |= TIM_ADV_CR1_CEN_MASK;
}

void TIM_ADV_Stop(TIM_ADV_Type * TIMx)
{
    TIMx->CR1 &= ~TIM_ADV_CR1_CEN_MASK;
}

uint32_t TIM_ADV_GetCounterValue(TIM_ADV_Type * TIMx)
{
    return TIMx->CNT;
}

void TIM_ADV_ClearCounterValue(TIM_ADV_Type * TIMx)
{
    TIMx->CNT = 0u;
}

void TIM_ADV_EnableInterrupts(TIM_ADV_Type * TIMx, uint32_t interrupts, bool enable)
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

void TIM_ADV_EnableDMA(TIM_ADV_Type * TIMx, uint32_t dmas, bool enable)
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

void TIM_ADV_DoSwTrigger(TIM_ADV_Type * TIMx, uint32_t swtrgs)
{
    TIMx->EGR = swtrgs;
}

uint32_t TIM_ADV_GetInterruptStatus(TIM_ADV_Type * TIMx)
{
    return TIMx->SR;
}

void TIM_ADV_ClearInterruptStatus(TIM_ADV_Type * TIMx, uint32_t status)
{
    TIMx->SR &= ~status;
}

/*******************************/
static void _TIM_ADV_WriteChannelCtrlReg(TIM_ADV_Type * TIMx, uint32_t channel, uint32_t regval)
{
    switch (channel)
    {
    case TIM_ADV_CHN_1:
        TIMx->CCMR1 = (TIMx->CCMR1 & ~(0xFF)) | (regval & 0xFF);
        break;
    case TIM_ADV_CHN_2:
        TIMx->CCMR1 = (TIMx->CCMR1 & ~(0xFF00)) | ((regval & 0xFF) << 8u);
        break;
    case TIM_ADV_CHN_3:
        TIMx->CCMR2 = (TIMx->CCMR2 & ~(0xFF)) | (regval & 0xFF);
        break;
    case TIM_ADV_CHN_4:
        TIMx->CCMR2 = (TIMx->CCMR2 & ~(0xFF00)) | ((regval & 0xFF) << 8u);
        break;
    default:
        break;
    }
}

static void _TIM_ADV_EnableChannel5OutputCompare(TIM_ADV_Type * TIMx, TIM_ADV_OutputCompareConf_Type * conf)
{
    TIMx->CCMR3 = ( TIMx->CCMR3 & ~(0xFF) )
                | ( (conf->EnableFastOutput) ? TIM_ADV_CCMR3_OC5FE_MASK : 0u )
                | ( (conf->EnablePreLoadChannelValue) ? TIM_ADV_CCMR3_OC5PE_MASK : 0u )
                | TIM_ADV_CCMR3_OC5M(conf->RefOutMode);
    TIM_ADV_PutChannelValue(TIMx, TIM_ADV_CHN_5, conf->ChannelValue);
}

void TIM_ADV_EnableOutputCompare(TIM_ADV_Type * TIMx, uint32_t channel, TIM_ADV_OutputCompareConf_Type * conf)
{
    if ( channel == TIM_ADV_CHN_5)
    {
        _TIM_ADV_EnableChannel5OutputCompare(TIMx, conf);
    }
    else
    {
        uint32_t regval = TIM_ADV_CCMR1_CC1S(TIM_ADV_ChannelIOMode_Out) /* output compare mode. */
                | ( (conf->EnableFastOutput) ? TIM_ADV_CCMR1_OC1FE_MASK : 0u ) /* fast output. */
                | ( (conf->EnablePreLoadChannelValue) ? TIM_ADV_CCMR1_OC1PE_MASK : 0u) /* preload of channel value. */
                | TIM_ADV_CCMR1_OC1M(conf->RefOutMode) /* output compare comparison mode. */
                | ( (conf->ClearRefOutOnExtTrigger) ? TIM_ADV_CCMR1_OC1CE_MASK : 0u) /* external trigger clear ref. */
                ;

        _TIM_ADV_WriteChannelCtrlReg(TIMx, channel, regval);

        TIM_ADV_PutChannelValue(TIMx, channel, conf->ChannelValue);

        switch (conf->PinPolarity)
        {
            case TIM_ADV_PinPolarity_Disable:
                TIMx->CCER &= ~( ( TIM_ADV_CCER_CC1E_MASK
                                 | TIM_ADV_CCER_CC1NE_MASK
                                 ) << (channel<<2u) ); /* Disable both channel. */
                break;

            case TIM_ADV_PinPolarity_Rising:
                TIMx->CCER = ( ( TIMx->CCER & ~(0xF << (channel<<2u)) )
                           | ( ( TIM_ADV_CCER_CC1E_MASK ) /* Enable the pin output / input. */
                           | ( ( conf->COMPPinPolarity == TIM_ADV_PinPolarity_Falling) ? TIM_ADV_CCER_CC1NP_MASK : 0u )
                           | ( ( conf->COMPPinPolarity != TIM_ADV_PinPolarity_Disable) ? TIM_ADV_CCER_CC1NE_MASK : 0u )
                           ) << (channel<<2u));
                break;

            case TIM_ADV_PinPolarity_Falling:
                TIMx->CCER = ( TIMx->CCER & ~(0xF << (channel<<2u)) )
                           | (( TIM_ADV_CCER_CC1E_MASK /* Enable the pin output / input. */
                           |    TIM_ADV_CCER_CC1P_MASK /* Set output active polarity. */
                           | ( ( conf->COMPPinPolarity == TIM_ADV_PinPolarity_Falling) ? TIM_ADV_CCER_CC1NP_MASK : 0u )
                           | ( ( conf->COMPPinPolarity != TIM_ADV_PinPolarity_Disable) ? TIM_ADV_CCER_CC1NE_MASK : 0u )
                           ) << (channel<<2u));
                break;

            default:
                break;
        }
    }
}

void TIM_ADV_EnableOutputCompareSwitch(TIM_ADV_Type * TIMx, bool enable)
{
    if (enable)
    {
        TIMx->BDTR |= TIM_ADV_BDTR_MOE_MASK;
    }
    else
    {
        TIMx->BDTR &= ~ TIM_ADV_BDTR_MOE_MASK;
    }
}

void TIM_ADV_EnableInputCapture(TIM_ADV_Type * TIMx, uint32_t channel, TIM_ADV_InputCaptureConf_Type * conf)
{
    uint32_t regval = TIM_ADV_CCMR1_CC1S(TIM_ADV_ChannelIOMode_In) /* input capture mode. */
                    | TIM_ADV_CCMR1_IC1PSC(conf->InDiv)
                    | TIM_ADV_CCMR1_IC1F(conf->InFilter)
                    ;

    _TIM_ADV_WriteChannelCtrlReg(TIMx, channel, regval);

    switch (conf->PinPolarity)
    {
        case TIM_ADV_PinPolarity_Disable:
            TIMx->CCER &= ~(TIM_ADV_CCER_CC1E_MASK << (channel<<2u));
            break;
        case TIM_ADV_PinPolarity_Rising:
            TIMx->CCER = (TIMx->CCER & ~(0xF << (channel<<2u)) )
                       | (( TIM_ADV_CCER_CC1E_MASK /* Enable the pin output / input */
                       ) << (channel<<2u) );
            break;
        case TIM_ADV_PinPolarity_Falling:
            TIMx->CCER = ( TIMx->CCER & ~(0xF << (channel<<2u)) )
                       | (( TIM_ADV_CCER_CC1E_MASK /* Enable the pin output / input */
                       |    TIM_ADV_CCER_CC1P_MASK /* Set active input edge. */
                       ) << (channel<<2u) );
            break;
        case TIM_ADV_PinPolarity_RisingOrFalling:
            TIMx->CCER = ( TIMx->CCER & ~(0xF << (channel<<2u)) )
                       | (( TIM_ADV_CCER_CC1E_MASK /* Enable the pin output / input */
                       |    TIM_ADV_CCER_CC1P_MASK /* Set active input edge. */
                       |    TIM_ADV_CCER_CC1NP_MASK
                       ) << (channel<<2u) );
            break;
        default:
            break;
    }
}

uint16_t TIM_ADV_GetChannelValue(TIM_ADV_Type * TIMx, uint32_t channel)
{
    return TIMx->CCR[channel];
}

void TIM_ADV_PutChannelValue(TIM_ADV_Type * TIMx, uint32_t channel, uint16_t value)
{
    if ( channel == TIM_ADV_CHN_5 )
    {
        TIMx->CCR5 = value;
    }
    else
    {
        TIMx->CCR[channel] = value;
    }
}

void TIM_ADV_EnableDeadArea(TIM_ADV_Type * TIMx, TIM_ADV_DeadAreaConf_Type * conf)
{
    TIMx->CR1 = ( TIMx->CR1 &~ TIM_ADV_CR1_CKD_MASK )
              | ( TIM_ADV_CR1_CKD(conf->StepFreqHz) ); /* set the frequncy ratio. */
    TIMx->BDTR = ( TIMx->BDTR &~ TIM_ADV_BDTR_DTG_MASK )
               | ( TIM_ADV_BDTR_DTG(conf->DeadAreaCoef) ); /* set the coefficient. */
}

void TIM_ADV_EnableMasterMode(TIM_ADV_Type * TIMx, TIM_ADV_MasterModeConf_Type * conf)
{
    TIMx->CR2 = ( TIMx->CR2 &~ TIM_ADV_CR2_MMS_MASK )
              | ( TIM_ADV_CR2_MMS(conf->Out) ); /* Set master mode output. */

    uint32_t smcr = TIMx->SMCR &~ TIM_ADV_SMCR_MSM_MASK;
    if (conf->EnableSync) /* synchronize with slave timers. */
    {
        smcr |= TIM_ADV_SMCR_MSM_MASK;
    }
    TIMx->SMCR = smcr;
}

void TIM_ADV_EnableSlaveMode(TIM_ADV_Type * TIMx, TIM_ADV_SlaveModeConf_Type * conf)
{
    if ( conf->Resp != TIM_ADV_SlaveResp_Disable )
    {
        TIMx->SMCR = ( TIMx->SMCR &~ ( TIM_ADV_SMCR_TS_MASK
                                     | TIM_ADV_SMCR_SMS_MASK
                                     ) )
                   | TIM_ADV_SMCR_TS(conf->In) /* set input trigger source. */
                   | TIM_ADV_SMCR_SMS(conf->Resp); /* set response to the source */
    }
    else
    {
        TIMx->SMCR &= ~ TIM_ADV_SMCR_SMS_MASK;
    }
}

void TIM_ADV_EnableExtTriggerIn(TIM_ADV_Type * TIMx, TIM_ADV_ExtTriggerInConf_Type * conf)
{
    uint32_t smcr = TIMx->SMCR &~ ( TIM_ADV_SMCR_ETPS_MASK
                                  | TIM_ADV_SMCR_ETF_MASK
                                  | TIM_ADV_SMCR_ECE_MASK
                                  | TIM_ADV_SMCR_ETP_MASK
                                  );
    switch (conf->PinPolarity)
    {
        case TIM_ADV_PinPolarity_Disable:
            break;
        case TIM_ADV_PinPolarity_Rising:
            smcr |= TIM_ADV_SMCR_ECE_MASK; /* enable external trigger input. */
            break;
        case TIM_ADV_PinPolarity_Falling:
            smcr |= TIM_ADV_SMCR_ETP_MASK; /* falling edge active. */
            smcr |= TIM_ADV_SMCR_ECE_MASK; /* enable external trigger input. */
            break;
        default:
            break;
    }
    smcr |= TIM_ADV_SMCR_ETPS( conf->InDiv ); /* division to the input external trigger. */
    smcr |= TIM_ADV_SMCR_ETF( conf->InFilter ); /* set filter. */
    TIMx->SMCR = smcr;
}

uint32_t TIM_ADV_EnableDMABurst(TIM_ADV_Type * TIMx, TIM_ADV_DMABurstConf_Type * conf)
{
    TIMx->DCR = TIM_ADV_DCR_DBA(conf->BaseAddr) | TIM_ADV_DCR_DBL(conf->Length);
    return (uint32_t)(&(TIMx->DMAR));
}

TIM_ADV_EncoderDirection_Type TIM_ADV_GetEncoder(TIM_ADV_Type * TIMx, uint32_t * value)
{
    if (value)
    {
        * value = TIM_ADV_GetCounterValue(TIMx);
    }

    if ( (TIMx->CR1 & TIM_ADV_CR1_DIR_MASK) != 0u )
    {
        return TIM_ADV_EncoderDirection_Backward;
    }
    else
    {
        return TIM_ADV_EncoderDirection_Forward;
    }
}

void TIM_ADV_SetRepCounter(TIM_ADV_Type * TIMx, uint8_t value)
{
    TIMx->RCR = TIM_ADV_RCR_REP(value);
}

uint8_t TIM_ADV_GetRepCounterValue(TIM_ADV_Type * TIMx)
{
    return TIMx->RCR >> TIM_ADV_RCR_REPCNT_SHIFT;
}

void TIM_ADV_EnableIdleOut(TIM_ADV_Type * TIMx, uint32_t channel, TIM_ADV_IdleOut_Type * conf)
{
    uint32_t cr2 = TIMx->CR2 & ~ ( ( TIM_ADV_CR2_OIS1_MASK
                                   | TIM_ADV_CR2_OIS1N_MASK
                                   ) << ( channel << 1u )
                                 );
    if ( conf->PinPolarity == TIM_ADV_PinPolarity_Rising )
    {
        cr2 |= ( TIM_ADV_CR2_OIS1_MASK << ( channel << 1u ) );
    }
    if ( conf->COMPPinPolarity == TIM_ADV_PinPolarity_Rising )
    {
        cr2 |= ( TIM_ADV_CR2_OIS1N_MASK << ( channel << 1u ) );
    }
    TIMx->CR2 = cr2;
}

void TIM_ADV_EnableLock(TIM_ADV_Type * TIMx, TIM_ADV_LockLevel_Type lock)
{
    TIMx->BDTR = ( TIMx->BDTR & ~ TIM_ADV_BDTR_LOCK_MASK )
                 | TIM_ADV_BDTR_LOCK(lock);
}

void TIM_ADV_EnableBreakIn(TIM_ADV_Type * TIMx, TIM_ADV_BreakIn_Type * conf)
{
    uint32_t bdtr = TIMx->BDTR &~ ( TIM_ADV_BDTR_BKE_MASK
                                  | TIM_ADV_BDTR_BKP_MASK
                                  | TIM_ADV_BDTR_AOE_MASK
                                  | TIM_ADV_BDTR_DOE_MASK
                                  );
    switch (conf->PinPolarity)
    {
        case TIM_ADV_PinPolarity_Disable:
            break;
        case TIM_ADV_PinPolarity_Rising:
            bdtr |= ( TIM_ADV_BDTR_BKE_MASK
                    | TIM_ADV_BDTR_BKP_MASK
                    | ( conf->AutoSwitchOutput ? TIM_ADV_BDTR_AOE_MASK : 0u )
                    | ( conf->DirectIdleOutput ? TIM_ADV_BDTR_DOE_MASK : 0u )
                    );
            break;
        case TIM_ADV_PinPolarity_Falling:
            bdtr |= ( TIM_ADV_BDTR_BKE_MASK
                    | ( conf->AutoSwitchOutput ? TIM_ADV_BDTR_AOE_MASK : 0u )
                    | ( conf->DirectIdleOutput ? TIM_ADV_BDTR_DOE_MASK : 0u )
                    );
            break;
        default:
            break;
    }
}

void TIM_ADV_EnablePWMShift(TIM_ADV_Type * TIMx, uint32_t channel, uint16_t value)
{
    if ( value == TIM_ADV_GetChannelValue(TIMx, channel) )
    {
        TIMx->PDER &= ~( TIM_ADV_PDER_CCR1SHIFTEN_MASK << channel );
    }
    else
    {
        TIMx->PDER |= ( TIM_ADV_PDER_CCR1SHIFTEN_MASK << channel );
        TIMx->CCRFALL[channel] = value;
    }
}

/* EOF. */

