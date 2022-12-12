/*!
    \file    gd32f30x_adc.c
    \brief   ADC driver

    \version 2017-02-10, V1.0.0, firmware for GD32F30x
    \version 2018-10-10, V1.1.0, firmware for GD32F30x
    \version 2018-12-25, V2.0.0, firmware for GD32F30x
    \version 2020-09-30, V2.1.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f30x_adc.h"

/*!
    \brief      reset ADC
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[out] none
    \retval     none
*/
void adc_deinit(uint32_t adc_periph)
{
    switch(adc_periph){
    case ADC0:
        rcu_periph_reset_enable(RCU_ADC0RST);
        rcu_periph_reset_disable(RCU_ADC0RST);
        break;
    case ADC1:
        rcu_periph_reset_enable(RCU_ADC1RST);
        rcu_periph_reset_disable(RCU_ADC1RST);
        break;
#if (defined(GD32F30X_HD) || defined(GD32F30X_XD))
    case ADC2:
        rcu_periph_reset_enable(RCU_ADC2RST);
        rcu_periph_reset_disable(RCU_ADC2RST);
        break;
#endif
    default:
        break;
    }
}

/*!
    \brief      enable ADC interface
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[out] none
    \retval     none
*/
void adc_enable(uint32_t adc_periph)
{
    if(RESET == (ADC_CTL1(adc_periph) & ADC_CTL1_ADCON)){
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_ADCON;
    }
}

/*!
    \brief      disable ADC interface
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[out] none
    \retval     none
*/
void adc_disable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ADCON);
}

/*!
    \brief      ADC calibration and reset calibration
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[out] none
    \retval     none
*/
void adc_calibration_enable(uint32_t adc_periph)
{
    /* reset the selected ADC calibration registers */
    ADC_CTL1(adc_periph) |= (uint32_t) ADC_CTL1_RSTCLB;
    /* check the RSTCLB bit state */
    while((ADC_CTL1(adc_periph) & ADC_CTL1_RSTCLB)){
    }
    /* enable ADC calibration process */
    ADC_CTL1(adc_periph) |= ADC_CTL1_CLB;
    /* check the CLB bit state */
    while((ADC_CTL1(adc_periph) & ADC_CTL1_CLB)){
    }
}

/*!
    \brief      enable DMA request
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[out] none
    \retval     none
*/
void adc_dma_mode_enable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) |= (uint32_t)(ADC_CTL1_DMA);
}

/*!
    \brief      disable DMA request
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[out] none
    \retval     none
*/
void adc_dma_mode_disable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_DMA);
}

/*!
    \brief      enable the temperature sensor and Vrefint channel
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_tempsensor_vrefint_enable(void)
{
    /* enable the temperature sensor and Vrefint channel */
    ADC_CTL1(ADC0) |= ADC_CTL1_TSVREN;
}

/*!
    \brief      disable the temperature sensor and Vrefint channel
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_tempsensor_vrefint_disable(void)
{
    /* disable the temperature sensor and Vrefint channel */
    ADC_CTL1(ADC0) &= ~ADC_CTL1_TSVREN;
}

/*!
    \brief      configure ADC resolution
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  resolution: ADC resolution
                only one among these parameters can be selected
      \arg        ADC_RESOLUTION_12B: 12-bit ADC resolution
      \arg        ADC_RESOLUTION_10B: 10-bit ADC resolution
      \arg        ADC_RESOLUTION_8B: 8-bit ADC resolution
      \arg        ADC_RESOLUTION_6B: 6-bit ADC resolution
    \param[out] none
    \retval     none
*/
void adc_resolution_config(uint32_t adc_periph , uint32_t resolution)
{
    ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)ADC_OVSAMPCTL_DRES);
    ADC_OVSAMPCTL(adc_periph) |= (uint32_t)resolution;
}

/*!
    \brief      configure ADC discontinuous mode
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_channel_group: select the channel group
                only one among these parameters can be selected
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
      \arg        ADC_CHANNEL_DISCON_DISABLE: disable discontinuous mode of regular & inserted channel
    \param[in]  length: number of conversions in discontinuous mode,the number can be 1..8
                        for regular channel ,the number has no effect for inserted channel
    \param[out] none
    \retval     none
*/
void adc_discontinuous_mode_config(uint32_t adc_periph, uint8_t adc_channel_group, uint8_t length)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)( ADC_CTL0_DISRC | ADC_CTL0_DISIC ));
    switch(adc_channel_group){
    case ADC_REGULAR_CHANNEL:
        /* config the number of conversions in discontinuous mode  */
        ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_DISNUM);
        ADC_CTL0(adc_periph) |= CTL0_DISNUM(((uint32_t)length - 1U));

        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_DISRC;
        break;
    case ADC_INSERTED_CHANNEL:
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_DISIC;
        break;
    case ADC_CHANNEL_DISCON_DISABLE:
    default:
        break;
    }
}

/*!
    \brief      configure the ADC sync mode
    \param[in]  mode: ADC mode
                only one among these parameters can be selected
      \arg        ADC_MODE_FREE: all the ADCs work independently
      \arg        ADC_DAUL_REGULAL_PARALLEL_INSERTED_PARALLEL: ADC0 and ADC1 work in combined regular parallel + inserted parallel mode
      \arg        ADC_DAUL_REGULAL_PARALLEL_INSERTED_ROTATION: ADC0 and ADC1 work in combined regular parallel + trigger rotation mode
      \arg        ADC_DAUL_INSERTED_PARALLEL_REGULAL_FOLLOWUP_FAST: ADC0 and ADC1 work in combined inserted parallel + follow-up fast mode
      \arg        ADC_DAUL_INSERTED_PARALLEL_REGULAL_FOLLOWUP_SLOW: ADC0 and ADC1 work in combined inserted parallel + follow-up slow mode
      \arg        ADC_DAUL_INSERTED_PARALLEL: ADC0 and ADC1 work in inserted parallel mode only
      \arg        ADC_DAUL_REGULAL_PARALLEL: ADC0 and ADC1 work in regular parallel mode only
      \arg        ADC_DAUL_REGULAL_FOLLOWUP_FAST: ADC0 and ADC1 work in follow-up fast mode only
      \arg        ADC_DAUL_REGULAL_FOLLOWUP_SLOW: ADC0 and ADC1 work in follow-up slow mode only
      \arg        ADC_DAUL_INSERTED_TRRIGGER_ROTATION: ADC0 and ADC1 work in trigger rotation mode only
    \param[out] none
    \retval     none
*/
void adc_mode_config(uint32_t mode)
{
    ADC_CTL0(ADC0) &= ~(ADC_CTL0_SYNCM);
    ADC_CTL0(ADC0) |= mode;
}

/*!
    \brief      enable or disable ADC special function
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  function: the function to config
                one or more parameters can be selected below
      \arg        ADC_SCAN_MODE: scan mode select
      \arg        ADC_INSERTED_CHANNEL_AUTO: inserted channel group convert automatically
      \arg        ADC_CONTINUOUS_MODE: continuous mode select
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_special_function_config(uint32_t adc_periph , uint32_t function , ControlStatus newvalue)
{
    if(newvalue){
        if(0U != (function & ADC_SCAN_MODE)){
            ADC_CTL0(adc_periph) |= ADC_SCAN_MODE;
        }
        if(0U != (function & ADC_INSERTED_CHANNEL_AUTO)){
            ADC_CTL0(adc_periph) |= ADC_INSERTED_CHANNEL_AUTO;
        }
        if(0U != (function & ADC_CONTINUOUS_MODE)){
            ADC_CTL1(adc_periph) |= ADC_CONTINUOUS_MODE;
        }
    }else{
        if(0U != (function & ADC_SCAN_MODE)){
            ADC_CTL0(adc_periph) &= ~ADC_SCAN_MODE;
        }
        if(0U != (function & ADC_INSERTED_CHANNEL_AUTO)){
            ADC_CTL0(adc_periph) &= ~ADC_INSERTED_CHANNEL_AUTO;
        }
        if(0U != (function & ADC_CONTINUOUS_MODE)){
            ADC_CTL1(adc_periph) &= ~ADC_CONTINUOUS_MODE;
        }
    }
}

/*!
    \brief      configure ADC data alignment
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  data_alignment: data alignment select
                only one parameter can be selected
      \arg        ADC_DATAALIGN_RIGHT: LSB alignment
      \arg        ADC_DATAALIGN_LEFT: MSB alignment
    \param[out] none
    \retval     none
*/
void adc_data_alignment_config(uint32_t adc_periph , uint32_t data_alignment)
{
    if(ADC_DATAALIGN_RIGHT != data_alignment){
        ADC_CTL1(adc_periph) |= ADC_CTL1_DAL;
    }else{
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_DAL);
    }
}

/*!
    \brief      configure the length of regular channel group or inserted channel group
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_channel_group: select the channel group
                only one parameter can be selected
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  length: the length of the channel
                        regular channel 1-16
                        inserted channel 1-4
    \param[out] none
    \retval     none
*/
void adc_channel_length_config(uint32_t adc_periph, uint8_t adc_channel_group, uint32_t length)
{
    switch(adc_channel_group){
    case ADC_REGULAR_CHANNEL:
        ADC_RSQ0(adc_periph) &= ~((uint32_t)ADC_RSQ0_RL);
        ADC_RSQ0(adc_periph) |= RSQ0_RL((uint32_t)(length-1U));

        break;
    case ADC_INSERTED_CHANNEL:
        ADC_ISQ(adc_periph) &= ~((uint32_t)ADC_ISQ_IL);
        ADC_ISQ(adc_periph) |= ISQ_IL((uint32_t)(length-1U));

        break;
    default:
        break;
    }
}

/*!
    \brief      configure ADC regular channel
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  rank: the regular group sequence rank,this parameter must be between 0 to 15
    \param[in]  adc_channel: the selected ADC channel
                only one among these parameters can be selected
      \arg        ADC_CHANNEL_x(x=0..17)(x=16 and x=17 are only for ADC0): ADC Channelx
    \param[in]  sample_time: the sample time value
                only one parameter can be selected
      \arg        ADC_SAMPLETIME_1POINT5: 1.5 cycles
      \arg        ADC_SAMPLETIME_7POINT5: 7.5 cycles
      \arg        ADC_SAMPLETIME_13POINT5: 13.5 cycles
      \arg        ADC_SAMPLETIME_28POINT5: 28.5 cycles
      \arg        ADC_SAMPLETIME_41POINT5: 41.5 cycles
      \arg        ADC_SAMPLETIME_55POINT5: 55.5 cycles
      \arg        ADC_SAMPLETIME_71POINT5: 71.5 cycles
      \arg        ADC_SAMPLETIME_239POINT5: 239.5 cycles
    \param[out] none
    \retval     none
*/
void adc_regular_channel_config(uint32_t adc_periph , uint8_t rank , uint8_t adc_channel , uint32_t sample_time)
{
    uint32_t rsq,sampt;

    /* ADC regular sequence config */
    if(rank < 6U){
        rsq = ADC_RSQ2(adc_periph);
        rsq &=  ~((uint32_t)(ADC_RSQX_RSQN << (5U*rank)));
        rsq |= ((uint32_t)adc_channel << (5U*rank));
        ADC_RSQ2(adc_periph) = rsq;
    }else if(rank < 12U){
        rsq = ADC_RSQ1(adc_periph);
        rsq &= ~((uint32_t)(ADC_RSQX_RSQN << (5U*(rank-6U))));
        rsq |= ((uint32_t)adc_channel << (5U*(rank-6U)));
        ADC_RSQ1(adc_periph) = rsq;
    }else if(rank < 16U){
        rsq = ADC_RSQ0(adc_periph);
        rsq &= ~((uint32_t)(ADC_RSQX_RSQN << (5U*(rank-12U))));
        rsq |= ((uint32_t)adc_channel << (5U*(rank-12U)));
        ADC_RSQ0(adc_periph) = rsq;
    }else{
    }

    /* ADC sampling time config */
    if(adc_channel < 10U){
        sampt = ADC_SAMPT1(adc_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (3U*adc_channel)));
        sampt |= (uint32_t)(sample_time << (3U*adc_channel));
        ADC_SAMPT1(adc_periph) = sampt;
    }else if(adc_channel < 18U){
        sampt = ADC_SAMPT0(adc_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (3U*(adc_channel-10U))));
        sampt |= (uint32_t)(sample_time << (3U*(adc_channel-10U)));
        ADC_SAMPT0(adc_periph) = sampt;
    }else{
    }
}

/*!
    \brief      configure ADC inserted channel
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  rank: the inserted group sequencer rank,this parameter must be between 0 to 3
    \param[in]  adc_channel: the selected ADC channel
                only one among these parameters can be selected
      \arg        ADC_CHANNEL_x(x=0..17)(x=16 and x=17 are only for ADC0): ADC Channelx
    \param[in]  sample_time: The sample time value
                only one parameter can be selected
      \arg        ADC_SAMPLETIME_1POINT5: 1.5 cycles
      \arg        ADC_SAMPLETIME_7POINT5: 7.5 cycles
      \arg        ADC_SAMPLETIME_13POINT5: 13.5 cycles
      \arg        ADC_SAMPLETIME_28POINT5: 28.5 cycles
      \arg        ADC_SAMPLETIME_41POINT5: 41.5 cycles
      \arg        ADC_SAMPLETIME_55POINT5: 55.5 cycles
      \arg        ADC_SAMPLETIME_71POINT5: 71.5 cycles
      \arg        ADC_SAMPLETIME_239POINT5: 239.5 cycles
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_config(uint32_t adc_periph , uint8_t rank , uint8_t adc_channel , uint32_t sample_time)
{
    uint8_t inserted_length;
    uint32_t isq,sampt;

    inserted_length = (uint8_t)GET_BITS(ADC_ISQ(adc_periph) , 20U , 21U);

    isq = ADC_ISQ(adc_periph);
    isq &= ~((uint32_t)(ADC_ISQ_ISQN << (5U * ((3 + rank) - inserted_length))));
    isq |= ((uint32_t)adc_channel << (5U * ((3 + rank) - inserted_length)));
    ADC_ISQ(adc_periph) = isq;

    /* ADC sampling time config */
    if(adc_channel < 10U){
        sampt = ADC_SAMPT1(adc_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (3U*adc_channel)));
        sampt |= (uint32_t) sample_time << (3U*adc_channel);
        ADC_SAMPT1(adc_periph) = sampt;
    }else if(adc_channel < 18U){
        sampt = ADC_SAMPT0(adc_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (3U*(adc_channel-10U))));
        sampt |= ((uint32_t)sample_time << (3U*(adc_channel-10U)));
        ADC_SAMPT0(adc_periph) = sampt;
    }else{
    }
}

/*!
    \brief      configure ADC inserted channel offset
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  inserted_channel : insert channel select
                only one parameter can be selected
      \arg        ADC_INSERTED_CHANNEL_0: inserted channel0
      \arg        ADC_INSERTED_CHANNEL_1: inserted channel1
      \arg        ADC_INSERTED_CHANNEL_2: inserted channel2
      \arg        ADC_INSERTED_CHANNEL_3: inserted channel3
    \param[in]  offset : the offset data
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_offset_config(uint32_t adc_periph , uint8_t inserted_channel , uint16_t offset)
{
    uint8_t inserted_length;
    uint32_t num = 0U;

    inserted_length = (uint8_t)GET_BITS(ADC_ISQ(adc_periph) , 20U , 21U);
    num = 3U - (inserted_length - inserted_channel);

    if(num <= 3U){
        /* calculate the offset of the register */
        num = num * 4U;
        /* config the offset of the selected channels */
        REG32((adc_periph) + 0x14U + num) = IOFFX_IOFF((uint32_t)offset);
    }
}

/*!
    \brief      enable ADC external trigger
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_channel_group: select the channel group
                one or more parameters can be selected
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_external_trigger_config(uint32_t adc_periph, uint8_t adc_channel_group, ControlStatus newvalue)
{
    if(newvalue){
        if(0U != (adc_channel_group & ADC_REGULAR_CHANNEL)){
            ADC_CTL1(adc_periph) |= ADC_CTL1_ETERC;
        }
        if(0U != (adc_channel_group & ADC_INSERTED_CHANNEL)){
            ADC_CTL1(adc_periph) |= ADC_CTL1_ETEIC;
        }
    }else{
        if(0U != (adc_channel_group & ADC_REGULAR_CHANNEL)){
            ADC_CTL1(adc_periph) &= ~ADC_CTL1_ETERC;
        }
        if(0U != (adc_channel_group & ADC_INSERTED_CHANNEL)){
            ADC_CTL1(adc_periph) &= ~ADC_CTL1_ETEIC;
        }
    }
}

/*!
    \brief      configure ADC external trigger source
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_channel_group: select the channel group
                only one parameter can be selected
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  external_trigger_source: regular or inserted group trigger source
                only one parameter can be selected
                for regular channel:
      \arg        ADC0_1_EXTTRIG_REGULAR_T0_CH0: timer 0 CC0 event select
      \arg        ADC0_1_EXTTRIG_REGULAR_T0_CH1: timer 0 CC1 event select
      \arg        ADC0_1_EXTTRIG_REGULAR_T0_CH2: timer 0 CC2 event select
      \arg        ADC0_1_EXTTRIG_REGULAR_T1_CH1: timer 1 CC1 event select
      \arg        ADC0_1_EXTTRIG_REGULAR_T2_TRGO: timer 2 TRGO event select
      \arg        ADC0_1_EXTTRIG_REGULAR_T3_CH3: timer 3 CC3 event select
      \arg        ADC0_1_EXTTRIG_REGULAR_T7_TRGO: timer 7 TRGO event select
      \arg        ADC0_1_EXTTRIG_REGULAR_EXTI_11 : external interrupt line 11
      \arg        ADC2_EXTTRIG_REGULAR_T2_CH0: timer 2 CC0 event select
      \arg        ADC2_EXTTRIG_REGULAR_T1_CH2: timer 1 CC2 event select
      \arg        ADC2_EXTTRIG_REGULAR_T0_CH2: timer 0 CC2 event select
      \arg        ADC2_EXTTRIG_REGULAR_T7_CH0: timer 7 CC0 event select
      \arg        ADC2_EXTTRIG_REGULAR_T7_TRGO: timer 7 TRGO event select
      \arg        ADC2_EXTTRIG_REGULAR_T4_CH0: timer 4 CC0 event select
      \arg        ADC2_EXTTRIG_REGULAR_T4_CH2: timer 4 CC2 event select
      \arg        ADC0_1_2_EXTTRIG_REGULAR_NONE: software trigger
                for inserted channel:
      \arg        ADC0_1_EXTTRIG_INSERTED_T0_TRGO: timer 0 TRGO event select
      \arg        ADC0_1_EXTTRIG_INSERTED_T0_CH3: timer 0 CC3 event select
      \arg        ADC0_1_EXTTRIG_INSERTED_T1_TRGO: timer 1 TRGO event select
      \arg        ADC0_1_EXTTRIG_INSERTED_T1_CH0: timer 1 CC0 event select
      \arg        ADC0_1_EXTTRIG_INSERTED_T2_CH3: timer 2 CC3 event select
      \arg        ADC0_1_EXTTRIG_INSERTED_T3_TRGO: timer 3 TRGO event select
      \arg        ADC0_1_EXTTRIG_INSERTED_EXTI_15: external interrupt line 15
      \arg        ADC0_1_EXTTRIG_INSERTED_T7_CH3: timer 7 CC3 event select
      \arg        ADC2_EXTTRIG_INSERTED_T0_TRGO: timer 0 TRGO event select
      \arg        ADC2_EXTTRIG_INSERTED_T0_CH3: timer 0 CC3 event select
      \arg        ADC2_EXTTRIG_INSERTED_T3_CH2: timer 3 CC2 event select
      \arg        ADC2_EXTTRIG_INSERTED_T7_CH1: timer 7 CC1 event select
      \arg        ADC2_EXTTRIG_INSERTED_T7_CH3: timer 7 CC3 event select
      \arg        ADC2_EXTTRIG_INSERTED_T4_TRGO: timer 4 TRGO event select
      \arg        ADC2_EXTTRIG_INSERTED_T4_CH3: timer 4 CC3 event select
      \arg        ADC0_1_2_EXTTRIG_INSERTED_NONE: software trigger
    \param[out] none
    \retval     none
*/
void adc_external_trigger_source_config(uint32_t adc_periph, uint8_t adc_channel_group, uint32_t external_trigger_source)
{
    switch(adc_channel_group){
    case ADC_REGULAR_CHANNEL:
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ETSRC);
        ADC_CTL1(adc_periph) |= (uint32_t)external_trigger_source;
        break;
    case ADC_INSERTED_CHANNEL:
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ETSIC);
        ADC_CTL1(adc_periph) |= (uint32_t)external_trigger_source;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable ADC software trigger
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_channel_group: select the channel group
                one or more parameters can be selected
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[out] none
    \retval     none
*/
void adc_software_trigger_enable(uint32_t adc_periph , uint8_t adc_channel_group)
{
    if(0U != (adc_channel_group & ADC_REGULAR_CHANNEL)){
        ADC_CTL1(adc_periph) |= ADC_CTL1_SWRCST;
    }
    if(0U != (adc_channel_group & ADC_INSERTED_CHANNEL)){
        ADC_CTL1(adc_periph) |= ADC_CTL1_SWICST;
    }
}

/*!
    \brief      read ADC regular group data register
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  none
    \param[out] none
    \retval     the conversion value
*/
uint16_t adc_regular_data_read(uint32_t adc_periph)
{
    return (uint16_t)(ADC_RDATA(adc_periph));
}

/*!
    \brief      read ADC inserted group data register
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  inserted_channel : insert channel select
                only one parameter can be selected
      \arg        ADC_INSERTED_CHANNEL_0: inserted Channel0
      \arg        ADC_INSERTED_CHANNEL_1: inserted channel1
      \arg        ADC_INSERTED_CHANNEL_2: inserted Channel2
      \arg        ADC_INSERTED_CHANNEL_3: inserted Channel3
    \param[out] none
    \retval     the conversion value
*/
uint16_t adc_inserted_data_read(uint32_t adc_periph , uint8_t inserted_channel)
{
    uint32_t idata;
    /* read the data of the selected channel */
    switch(inserted_channel){
    case ADC_INSERTED_CHANNEL_0:
        idata = ADC_IDATA0(adc_periph);
        break;
    case ADC_INSERTED_CHANNEL_1:
        idata = ADC_IDATA1(adc_periph);
        break;
    case ADC_INSERTED_CHANNEL_2:
        idata = ADC_IDATA2(adc_periph);
        break;
    case ADC_INSERTED_CHANNEL_3:
        idata = ADC_IDATA3(adc_periph);
        break;
    default:
        idata = 0U;
        break;
    }
    return (uint16_t)idata;
}

/*!
    \brief      read the last ADC0 and ADC1 conversion result data in sync mode
    \param[in]  none
    \param[out] none
    \retval     the conversion value
*/
uint32_t adc_sync_mode_convert_value_read(void)
{
    /* return conversion value */
    return ADC_RDATA(ADC0);
}

/*!
    \brief      get the ADC flag bits
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_flag: the adc flag bits
                only one parameter can be selected
      \arg        ADC_FLAG_WDE: analog watchdog event flag
      \arg        ADC_FLAG_EOC: end of group conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted group conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted channel group
      \arg        ADC_FLAG_STRC: start flag of regular channel group
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_flag_get(uint32_t adc_periph , uint32_t adc_flag)
{
    FlagStatus reval = RESET;
    if(ADC_STAT(adc_periph) & adc_flag){
        reval = SET;
    }
    return reval;
}

/*!
    \brief      clear the ADC flag bits
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_flag: the adc flag bits
                one or more parameters can be selected
      \arg        ADC_FLAG_WDE: analog watchdog event flag
      \arg        ADC_FLAG_EOC: end of group conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted group conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted channel group
      \arg        ADC_FLAG_STRC: start flag of regular channel group
    \param[out] none
    \retval     none
*/
void adc_flag_clear(uint32_t adc_periph , uint32_t adc_flag)
{
    ADC_STAT(adc_periph) &= ~((uint32_t)adc_flag);
}

/*!
    \brief      get the ADC interrupt bits
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_interrupt: the adc interrupt bits
                only oneparameter can be selected
      \arg        ADC_INT_FLAG_WDE: analog watchdog interrupt
      \arg        ADC_INT_FLAG_EOC: end of group conversion interrupt
      \arg        ADC_INT_FLAG_EOIC: end of inserted group conversion interrupt
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph , uint32_t adc_interrupt)
{
    FlagStatus interrupt_flag = RESET;
    uint32_t state;
    /* check the interrupt bits */
    switch(adc_interrupt){
    case ADC_INT_FLAG_WDE:
        state = ADC_STAT(adc_periph) & ADC_STAT_WDE;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_WDEIE) && state){
          interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_EOC:
        state = ADC_STAT(adc_periph) & ADC_STAT_EOC;
          if((ADC_CTL0(adc_periph) & ADC_CTL0_EOCIE) && state){
            interrupt_flag = SET;
          }
        break;
    case ADC_INT_FLAG_EOIC:
        state = ADC_STAT(adc_periph) & ADC_STAT_EOIC;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_EOICIE) && state){
            interrupt_flag = SET;
        }
        break;
    default:
        break;
    }
    return interrupt_flag;
}

/*!
    \brief      clear the ADC flag
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_interrupt: the adc status flag
                one or more parameters can be selected
      \arg        ADC_INT_FLAG_WDE: analog watchdog interrupt
      \arg        ADC_INT_FLAG_EOC: end of group conversion interrupt
      \arg        ADC_INT_FLAG_EOIC: end of inserted group conversion interrupt
    \param[out] none
    \retval     none
*/
void adc_interrupt_flag_clear(uint32_t adc_periph , uint32_t adc_interrupt)
{
    ADC_STAT(adc_periph) &= ~((uint32_t)adc_interrupt);
}

/*!
    \brief      enable ADC interrupt
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_interrupt: the adc interrupt
                one or more parameters can be selected
      \arg        ADC_INT_WDE: analog watchdog interrupt flag
      \arg        ADC_INT_EOC: end of group conversion interrupt flag
      \arg        ADC_INT_EOIC: end of inserted group conversion interrupt flag
    \param[out] none
    \retval     none
*/
void adc_interrupt_enable(uint32_t adc_periph , uint32_t adc_interrupt)
{
    if(0U != (adc_interrupt & ADC_INT_WDE)){
        ADC_CTL0(adc_periph) |= (uint32_t) ADC_CTL0_WDEIE;
    }

    if(0U != (adc_interrupt & ADC_INT_EOC)){
        ADC_CTL0(adc_periph) |= (uint32_t) ADC_CTL0_EOCIE;
    }

    if(0U != (adc_interrupt & ADC_INT_EOIC)){
        ADC_CTL0(adc_periph) |= (uint32_t) ADC_CTL0_EOICIE;
    }
}

/*!
    \brief      disable ADC interrupt
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_interrupt: the adc interrupt flag
                one or more parameters can be selected
      \arg        ADC_INT_WDE: analog watchdog interrupt flag
      \arg        ADC_INT_EOC: end of group conversion interrupt flag
      \arg        ADC_INT_EOIC: end of inserted group conversion interrupt flag
    \param[out] none
    \retval     none
*/
void adc_interrupt_disable(uint32_t adc_periph, uint32_t adc_interrupt)
{
    if(0U != (adc_interrupt & ADC_INT_WDE)){
        ADC_CTL0(adc_periph) &= ~(uint32_t) ADC_CTL0_WDEIE;
    }

    if(0U != (adc_interrupt & ADC_INT_EOC)){
        ADC_CTL0(adc_periph) &= ~(uint32_t) ADC_CTL0_EOCIE;
    }

    if(0U != (adc_interrupt & ADC_INT_EOIC)){
        ADC_CTL0(adc_periph) &= ~(uint32_t) ADC_CTL0_EOICIE;
    }
}

/*!
    \brief      configure ADC analog watchdog single channel
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_channel: the selected ADC channel
                only one among these parameters can be selected
      \arg        ADC_CHANNEL_x: ADC Channelx(x=0..17)(x=16 and x=17 are only for ADC0)
    \param[out] none
    \retval     none
*/
void adc_watchdog_single_channel_enable(uint32_t adc_periph, uint8_t adc_channel)
{
    ADC_CTL0(adc_periph) &= (uint32_t)~(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN | ADC_CTL0_WDSC | ADC_CTL0_WDCHSEL);

    ADC_CTL0(adc_periph) |= (uint32_t)adc_channel;
    ADC_CTL0(adc_periph) |= (uint32_t)(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN | ADC_CTL0_WDSC);
}

/*!
    \brief      configure ADC analog watchdog group channel
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  adc_channel_group: the channel group use analog watchdog
                only one parameter can be selected
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
      \arg        ADC_REGULAR_INSERTED_CHANNEL: both regular and inserted group
    \param[out] none
    \retval     none
*/
void adc_watchdog_group_channel_enable(uint32_t adc_periph, uint8_t adc_channel_group)
{
    ADC_CTL0(adc_periph) &= (uint32_t)~(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN | ADC_CTL0_WDSC);
    /* select the group */
    switch(adc_channel_group){
    case ADC_REGULAR_CHANNEL:
        ADC_CTL0(adc_periph) |= (uint32_t) ADC_CTL0_RWDEN;
        break;
    case ADC_INSERTED_CHANNEL:
        ADC_CTL0(adc_periph) |= (uint32_t) ADC_CTL0_IWDEN;
        break;
    case ADC_REGULAR_INSERTED_CHANNEL:
        ADC_CTL0(adc_periph) |= (uint32_t)(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN);
        break;
    default:
        break;
    }
}

/*!
    \brief      disable ADC analog watchdog
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[out] none
    \retval     none
*/
void adc_watchdog_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= (uint32_t)~(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN | ADC_CTL0_WDSC | ADC_CTL0_WDCHSEL);
}

/*!
    \brief      configure ADC analog watchdog threshold
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  low_threshold: analog watchdog low threshold,0..4095
    \param[in]  high_threshold: analog watchdog high threshold,0..4095
    \param[out] none
    \retval     none
*/
void adc_watchdog_threshold_config(uint32_t adc_periph , uint16_t low_threshold , uint16_t high_threshold)
{
    ADC_WDLT(adc_periph) = (uint32_t)WDLT_WDLT(low_threshold);
    ADC_WDHT(adc_periph) = (uint32_t)WDHT_WDHT(high_threshold);
}

/*!
    \brief      configure ADC oversample mode
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[in]  mode: ADC oversampling mode
                only oneparameter can be selected
      \arg        ADC_OVERSAMPLING_ALL_CONVERT: all oversampled conversions for a channel are done consecutively after a trigger
      \arg        ADC_OVERSAMPLING_ONE_CONVERT: each oversampled conversion for a channel needs a trigger
    \param[in]  shift: ADC oversampling shift
                only oneparameter can be selected
      \arg        ADC_OVERSAMPLING_SHIFT_NONE: no oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_1B: 1-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_2B: 2-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_3B: 3-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_4B: 3-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_5B: 5-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_6B: 6-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_7B: 7-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_8B: 8-bit oversampling shift
    \param[in]  ratio: ADC oversampling ratio
                only oneparameter can be selected
      \arg        ADC_OVERSAMPLING_RATIO_MUL2: oversampling ratio multiple 2
      \arg        ADC_OVERSAMPLING_RATIO_MUL4: oversampling ratio multiple 4
      \arg        ADC_OVERSAMPLING_RATIO_MUL8: oversampling ratio multiple 8
      \arg        ADC_OVERSAMPLING_RATIO_MUL16: oversampling ratio multiple 16
      \arg        ADC_OVERSAMPLING_RATIO_MUL32: oversampling ratio multiple 32
      \arg        ADC_OVERSAMPLING_RATIO_MUL64: oversampling ratio multiple 64
      \arg        ADC_OVERSAMPLING_RATIO_MUL128: oversampling ratio multiple 128
      \arg        ADC_OVERSAMPLING_RATIO_MUL256: oversampling ratio multiple 256
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_config(uint32_t adc_periph, uint32_t mode, uint16_t shift, uint8_t ratio)
{
    if(ADC_OVERSAMPLING_ONE_CONVERT == mode){
        ADC_OVSAMPCTL(adc_periph) |= (uint32_t)ADC_OVSAMPCTL_TOVS;
    }else{
        ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)ADC_OVSAMPCTL_TOVS);
    }
    /* config the shift and ratio */
    ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)(ADC_OVSAMPCTL_OVSR | ADC_OVSAMPCTL_OVSS));
    ADC_OVSAMPCTL(adc_periph) |= ((uint32_t)shift | (uint32_t)ratio);
}

/*!
    \brief      enable ADC oversample mode
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_enable(uint32_t adc_periph)
{
    ADC_OVSAMPCTL(adc_periph) |= ADC_OVSAMPCTL_OVSEN;
}

/*!
    \brief      disable ADC oversample mode
    \param[in]  adc_periph: ADCx,x=0,1,2
                only one among these parameters can be selected
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_disable(uint32_t adc_periph)
{
    ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)ADC_OVSAMPCTL_OVSEN);
}
