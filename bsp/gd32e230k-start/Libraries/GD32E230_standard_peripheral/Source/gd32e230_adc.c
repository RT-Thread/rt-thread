/*!
    \file    gd32e230_adc.c
    \brief   ADC driver
    
    \version 2018-06-19, V1.0.0, firmware for GD32E230
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#include "gd32e230_adc.h"

/*!
    \brief      reset ADC
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_deinit(void)
{
    rcu_periph_reset_enable(RCU_ADCRST);
    rcu_periph_reset_disable(RCU_ADCRST);
}

/*!
    \brief      enable ADC interface
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_enable(void)
{
    if(RESET == (ADC_CTL1 & ADC_CTL1_ADCON)){
        ADC_CTL1 |= (uint32_t)ADC_CTL1_ADCON;
    }
}

/*!
    \brief      disable ADC interface
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_disable(void)
{
    ADC_CTL1 &= ~((uint32_t)ADC_CTL1_ADCON);
}

/*!
    \brief      ADC calibration and reset calibration
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_calibration_enable(void)
{
    /* reset the selected ADC calibration register */
    ADC_CTL1 |= (uint32_t) ADC_CTL1_RSTCLB;
    /* check the RSTCLB bit state */
    while((ADC_CTL1 & ADC_CTL1_RSTCLB)){
    }

    /* enable ADC calibration process */
    ADC_CTL1 |= ADC_CTL1_CLB;
    /* check the CLB bit state */
    while((ADC_CTL1 & ADC_CTL1_CLB)){
    }
}

/*!
    \brief      enable DMA request 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_dma_mode_enable(void)
{
    ADC_CTL1 |= (uint32_t)(ADC_CTL1_DMA);
}

/*!
    \brief      disable DMA request 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_dma_mode_disable(void)
{
    ADC_CTL1 &= ~((uint32_t)ADC_CTL1_DMA);
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
    ADC_CTL1 |= ADC_CTL1_TSVREN;
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
    ADC_CTL1 &= ~ADC_CTL1_TSVREN;
}

/*!
    \brief      configure ADC discontinuous mode 
    \param[in]  channel_group: select the channel group
                only one parameter can be selected which is shown as below:
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
      \arg        ADC_CHANNEL_DISCON_DISABLE: disable discontinuous mode of regular and inserted channel
    \param[in]  length: number of conversions in discontinuous mode, the number can be 1..8
                        for regular channel, the number has no effect for inserted channel
    \param[out] none
    \retval     none
*/
void adc_discontinuous_mode_config(uint8_t channel_group, uint8_t length)
{
    ADC_CTL0 &= ~((uint32_t)(ADC_CTL0_DISRC | ADC_CTL0_DISIC));
    
    switch(channel_group){
    case ADC_REGULAR_CHANNEL:
        /* configure the number of conversions in discontinuous mode */
        ADC_CTL0 &= ~((uint32_t)ADC_CTL0_DISNUM);
        ADC_CTL0 |= CTL0_DISNUM(((uint32_t)length - 1U));
        ADC_CTL0 |= (uint32_t)ADC_CTL0_DISRC;
        break;
    case ADC_INSERTED_CHANNEL:
        ADC_CTL0 |= (uint32_t)ADC_CTL0_DISIC;
        break;
    case ADC_CHANNEL_DISCON_DISABLE:
    default:
        break;
    }
}

/*!
    \brief      configure ADC special function
    \param[in]  function: the function to configure
                one or more parameters can be selected which is shown as below:
      \arg        ADC_SCAN_MODE: scan mode select
      \arg        ADC_INSERTED_CHANNEL_AUTO: inserted channel group convert automatically
      \arg        ADC_CONTINUOUS_MODE: continuous mode select
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_special_function_config(uint32_t function, ControlStatus newvalue)
{
    if(newvalue){
        /* enable ADC scan mode */
        if(RESET != (function & ADC_SCAN_MODE)){
            ADC_CTL0 |= ADC_SCAN_MODE;
        }
        /* enable ADC inserted channel group convert automatically */
        if(RESET != (function & ADC_INSERTED_CHANNEL_AUTO)){
            ADC_CTL0 |= ADC_INSERTED_CHANNEL_AUTO;
        }
        /* enable ADC continuous mode */
        if(RESET != (function & ADC_CONTINUOUS_MODE)){
            ADC_CTL1 |= ADC_CONTINUOUS_MODE;
        }
    }else{
        /* disable ADC scan mode */
        if(RESET != (function & ADC_SCAN_MODE)){
            ADC_CTL0 &= ~ADC_SCAN_MODE;
        }
        /* disable ADC inserted channel group convert automatically */
        if(RESET != (function & ADC_INSERTED_CHANNEL_AUTO)){
            ADC_CTL0 &= ~ADC_INSERTED_CHANNEL_AUTO;
        }
        /* disable ADC continuous mode */
        if(RESET != (function & ADC_CONTINUOUS_MODE)){
            ADC_CTL1 &= ~ADC_CONTINUOUS_MODE;
        }
    }
}

/*!
    \brief      configure ADC data alignment 
    \param[in]  data_alignment: data alignment select
                only one parameter can be selected which is shown as below:
      \arg        ADC_DATAALIGN_RIGHT: right alignment
      \arg        ADC_DATAALIGN_LEFT: left alignment
    \param[out] none
    \retval     none
*/
void adc_data_alignment_config(uint32_t data_alignment)
{
    if(ADC_DATAALIGN_RIGHT != data_alignment){
        ADC_CTL1 |= ADC_CTL1_DAL;
    }else{
        ADC_CTL1 &= ~((uint32_t)ADC_CTL1_DAL);
    }
}

/*!
    \brief      configure the length of regular channel group or inserted channel group
    \param[in]  channel_group: select the channel group
                only one parameter can be selected which is shown as below:
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  length: the length of the channel
                        regular channel 1-16
                        inserted channel 1-4
    \param[out] none
    \retval     none
*/
void adc_channel_length_config(uint8_t channel_group, uint32_t length)
{
    switch(channel_group){
    case ADC_REGULAR_CHANNEL:
        /* configure the length of regular channel group */
        ADC_RSQ0 &= ~((uint32_t)ADC_RSQ0_RL);
        ADC_RSQ0 |= RSQ0_RL((uint32_t)(length-1U));
        break;
    case ADC_INSERTED_CHANNEL:
        /* configure the length of inserted channel group */
        ADC_ISQ &= ~((uint32_t)ADC_ISQ_IL);
        ADC_ISQ |= ISQ_IL((uint32_t)(length-1U));
        break;
    default:
        break;
    }
}

/*!
    \brief      configure ADC regular channel
    \param[in]  rank: the regular group sequence rank, this parameter must be between 0 to 15
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x(x=0..9,16,17): ADC Channelx
    \param[in]  sample_time: the sample time value
                only one parameter can be selected which is shown as below:
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
void adc_regular_channel_config(uint8_t rank, uint8_t channel, uint32_t sample_time)
{
    uint32_t rsq,sampt;
    
    /* configure ADC regular sequence */
    if(rank < 6U){
        rsq = ADC_RSQ2;
        rsq &=  ~((uint32_t)(ADC_RSQX_RSQN << (5U*rank)));
        rsq |= ((uint32_t)channel << (5U*rank));
        ADC_RSQ2 = rsq;
    }else if(rank < 12U){
        rsq = ADC_RSQ1;
        rsq &= ~((uint32_t)(ADC_RSQX_RSQN << (5U*(rank-6U))));
        rsq |= ((uint32_t)channel << (5U*(rank-6U)));
        ADC_RSQ1 = rsq;
    }else if(rank < 16U){
        rsq = ADC_RSQ0;
        rsq &= ~((uint32_t)(ADC_RSQX_RSQN << (5U*(rank-12U))));
        rsq |= ((uint32_t)channel << (5U*(rank-12U)));
        ADC_RSQ0 = rsq;
    }else{
    }
    
    /* configure ADC sampling time */
    if(channel < 10U){
        sampt = ADC_SAMPT1;
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (3U*channel)));
        sampt |= (uint32_t)(sample_time << (3U*channel));
        ADC_SAMPT1 = sampt;
    }else if(channel < 19U){
        sampt = ADC_SAMPT0;
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (3U*(channel-10U))));
        sampt |= (uint32_t)(sample_time << (3U*(channel-10U)));
        ADC_SAMPT0 = sampt;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure ADC inserted channel 
    \param[in]  rank: the inserted group sequencer rank,this parameter must be between 0 to 3
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x(x=0..9,16,17): ADC Channelx
    \param[in]  sample_time: The sample time value
                only one parameter can be selected which is shown as below:
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
void adc_inserted_channel_config(uint8_t rank, uint8_t channel, uint32_t sample_time)
{
    uint8_t inserted_length;
    uint32_t isq,sampt;

    inserted_length = (uint8_t)GET_BITS(ADC_ISQ , 20U , 21U);
  
    isq = ADC_ISQ;
    isq &= ~((uint32_t)(ADC_ISQ_ISQN << (15U - (inserted_length - rank)*5U)));
    isq |= ((uint32_t)channel << (15U - (inserted_length - rank)*5U));
    ADC_ISQ = isq;

    /* configure ADC sampling time */
    if(channel < 10U){
        sampt = ADC_SAMPT1;
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (3U*channel)));
        sampt |= (uint32_t) sample_time << (3U*channel);
        ADC_SAMPT1 = sampt;
    }else if(channel < 19U){
        sampt = ADC_SAMPT0;
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (3U*(channel - 10U))));
        sampt |= ((uint32_t)sample_time << (3U*(channel - 10U)));
        ADC_SAMPT0 = sampt;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      configure ADC inserted channel offset
    \param[in]  inserted_channel: insert channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_INSERTED_CHANNEL_0: ADC inserted channel 0
      \arg        ADC_INSERTED_CHANNEL_1: ADC inserted channel 1
      \arg        ADC_INSERTED_CHANNEL_2: ADC inserted channel 2
      \arg        ADC_INSERTED_CHANNEL_3: ADC inserted channel 3
    \param[in]  offset: the offset data
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_offset_config(uint8_t inserted_channel, uint16_t offset)
{
    uint8_t inserted_length;
    uint32_t num = 0U;

    inserted_length = (uint8_t)GET_BITS(ADC_ISQ, 20U, 21U);
    num = 3U - (inserted_length - inserted_channel);
    
    if(num <= 3U){
        /* calculate the offset of the register */
        num = num * 4U;
        /* configure the offset of the selected channels */
        REG32((ADC) + 0x14U + num) = IOFFX_IOFF((uint32_t)offset);
    }
}

/*!
    \brief      enable or disable ADC external trigger 
    \param[in]  channel_group: select the channel group
                one or more parameters can be selected which is shown as below:
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_external_trigger_config(uint8_t channel_group, ControlStatus newvalue)
{
    if(newvalue){
        /* external trigger enable for regular channel */
        if(RESET != (channel_group & ADC_REGULAR_CHANNEL)){
            ADC_CTL1 |= ADC_CTL1_ETERC;
        }
        /* external trigger enable for inserted channel */
        if(RESET != (channel_group & ADC_INSERTED_CHANNEL)){
            ADC_CTL1 |= ADC_CTL1_ETEIC;
        }
    }else{
        /* external trigger disable for regular channel */
        if(RESET != (channel_group & ADC_REGULAR_CHANNEL)){
            ADC_CTL1 &= ~ADC_CTL1_ETERC;
        }
        /* external trigger disable for inserted channel */
        if(RESET != (channel_group & ADC_INSERTED_CHANNEL)){
            ADC_CTL1 &= ~ADC_CTL1_ETEIC;
        }
    }
}

/*!
    \brief      configure ADC external trigger source 
    \param[in]  channel_group: select the channel group
                only one parameter can be selected which is shown as below:
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  external_trigger_source: regular or inserted group trigger source
                only one parameter can be selected which is shown as below:
                for regular channel:
      \arg        ADC_EXTTRIG_REGULAR_T0_CH0: TIMER0 CH0 event select 
      \arg        ADC_EXTTRIG_REGULAR_T0_CH1: TIMER0 CH1 event select 
      \arg        ADC_EXTTRIG_REGULAR_T0_CH2: TIMER0 CH2 event select  
      \arg        ADC_EXTTRIG_REGULAR_T2_TRGO: TIMER2 TRGO event select 
      \arg        ADC_EXTTRIG_REGULAR_T14_CH0:  TIMER14 CH0 event select 
      \arg        ADC_EXTTRIG_REGULAR_EXTI_11: external interrupt line 11
      \arg        ADC_EXTTRIG_REGULAR_NONE: software trigger
                for inserted channel:
      \arg        ADC_EXTTRIG_INSERTED_T0_TRGO: TIMER0 TRGO event select
      \arg        ADC_EXTTRIG_INSERTED_T0_CH3: TIMER0 CH3 event select 
      \arg        ADC_EXTTRIG_INSERTED_T2_CH3: TIMER2 CH3 event select 
      \arg        ADC_EXTTRIG_INSERTED_T14_TRGO: TIMER14 TRGO event select 
      \arg        ADC_EXTTRIG_INSERTED_EXTI_15: external interrupt line 15 
      \arg        ADC_EXTTRIG_INSERTED_NONE: software trigger
    \param[out] none
    \retval     none
*/
void adc_external_trigger_source_config(uint8_t channel_group, uint32_t external_trigger_source)
{   
    switch(channel_group){
    case ADC_REGULAR_CHANNEL:
        /* external trigger select for regular channel */
        ADC_CTL1 &= ~((uint32_t)ADC_CTL1_ETSRC);
        ADC_CTL1 |= (uint32_t)external_trigger_source;
        break;
    case ADC_INSERTED_CHANNEL:
        /* external trigger select for inserted channel */
        ADC_CTL1 &= ~((uint32_t)ADC_CTL1_ETSIC);
        ADC_CTL1 |= (uint32_t)external_trigger_source;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable ADC software trigger 
    \param[in]  channel_group: select the channel group
                one or more parameters can be selected which is shown as below:
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[out] none
    \retval     none
*/
void adc_software_trigger_enable(uint8_t channel_group)
{
    /* enable regular group channel software trigger */
    if(RESET != (channel_group & ADC_REGULAR_CHANNEL)){
        ADC_CTL1 |= ADC_CTL1_SWRCST;
    }
    /* enable inserted channel group software trigger */
    if(RESET != (channel_group & ADC_INSERTED_CHANNEL)){
        ADC_CTL1 |= ADC_CTL1_SWICST;
    }
}

/*!
    \brief      read ADC regular group data register 
    \param[in]  none
    \param[out] none
    \retval     the conversion value
*/
uint16_t adc_regular_data_read(void)
{
    return ((uint16_t)ADC_RDATA);
}

/*!
    \brief      read ADC inserted group data register 
    \param[in]  inserted_channel: inserted channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_INSERTED_CHANNEL_0: ADC inserted channel 0
      \arg        ADC_INSERTED_CHANNEL_1: ADC inserted channel 1
      \arg        ADC_INSERTED_CHANNEL_2: ADC inserted channel 2
      \arg        ADC_INSERTED_CHANNEL_3: ADC inserted channel 3
    \param[out] none
    \retval     the conversion value
*/
uint16_t adc_inserted_data_read(uint8_t inserted_channel)
{
    uint32_t idata;
    /* read the data of the selected channel */
    switch(inserted_channel){
    case ADC_INSERTED_CHANNEL_0:
        idata = ADC_IDATA0;
        break;
    case ADC_INSERTED_CHANNEL_1:
        idata = ADC_IDATA1;
        break;
    case ADC_INSERTED_CHANNEL_2:
        idata = ADC_IDATA2;
        break;
    case ADC_INSERTED_CHANNEL_3:
        idata = ADC_IDATA3;
        break;
    default:
        idata = 0U;
        break;
    }
    return (uint16_t)idata;
}

/*!
    \brief      get the ADC flag bits
    \param[in]  flag: the adc flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_WDE: analog watchdog event flag
      \arg        ADC_FLAG_EOC: end of group conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted group conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted channel group
      \arg        ADC_FLAG_STRC: start flag of regular channel group
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;
    
    if(ADC_STAT & flag){
        reval = SET;
    }
    return reval;
}

/*!
    \brief      clear the ADC flag 
    \param[in]  flag: the adc flag 
                one or more parameters can be selected which is shown as below:
      \arg        ADC_FLAG_WDE: analog watchdog event flag
      \arg        ADC_FLAG_EOC: end of group conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted group conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted channel group
      \arg        ADC_FLAG_STRC: start flag of regular channel group
    \param[out] none
    \retval     none
*/
void adc_flag_clear(uint32_t flag)
{
    ADC_STAT &= ~((uint32_t)flag);
}

/*!
    \brief      get the ADC interrupt flag
    \param[in]  flag: the adc interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_WDE: analog watchdog interrupt flag
      \arg        ADC_INT_FLAG_EOC: end of group conversion interrupt flag
      \arg        ADC_INT_FLAG_EOIC: end of inserted group conversion interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_interrupt_flag_get(uint32_t flag)
{
    FlagStatus interrupt_flag = RESET;
    uint32_t state;

    /* check the interrupt bits */
    switch(flag){
    case ADC_INT_FLAG_WDE:
        state = ADC_STAT & ADC_STAT_WDE;
        if((ADC_CTL0 & ADC_CTL0_WDEIE) && state){
          interrupt_flag = SET;
        }
        break;
    case ADC_INT_FLAG_EOC:
        state = ADC_STAT & ADC_STAT_EOC;
        if((ADC_CTL0 & ADC_CTL0_EOCIE) && state){
            interrupt_flag = SET;
          }
        break;
    case ADC_INT_FLAG_EOIC:
        state = ADC_STAT & ADC_STAT_EOIC;
        if((ADC_CTL0 & ADC_CTL0_EOICIE) && state){
            interrupt_flag = SET;
        }
        break;
    default:
        break;
    }
    return interrupt_flag;
}

/*!
    \brief      clear ADC interrupt flag
    \param[in]  flag: the adc interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_WDE: analog watchdog interrupt flag
      \arg        ADC_INT_FLAG_EOC: end of group conversion interrupt flag
      \arg        ADC_INT_FLAG_EOIC: end of inserted group conversion interrupt flag
    \param[out] none
    \retval     none
*/
void adc_interrupt_flag_clear(uint32_t flag)
{
    ADC_STAT &= ~((uint32_t)flag);
}

/*!
    \brief      enable ADC interrupt 
    \param[in]  interrupt: the adc interrupt
                one or more parameters can be selected which is shown as below:
      \arg        ADC_INT_WDE: analog watchdog interrupt 
      \arg        ADC_INT_EOC: end of group conversion interrupt 
      \arg        ADC_INT_EOIC: end of inserted group conversion interrupt 
    \param[out] none
    \retval     none
*/
void adc_interrupt_enable(uint32_t interrupt)
{
    /* enable analog watchdog interrupt */
    if(RESET != (interrupt & ADC_INT_WDE)){
        ADC_CTL0 |= (uint32_t)ADC_CTL0_WDEIE;
    }  

    /* enable end of group conversion interrupt */
    if(RESET != (interrupt & ADC_INT_EOC)){
        ADC_CTL0 |= (uint32_t)ADC_CTL0_EOCIE;
    }  

    /* enable end of inserted group conversion interrupt */
    if(RESET != (interrupt & ADC_INT_EOIC)){
        ADC_CTL0 |= (uint32_t)ADC_CTL0_EOICIE;
    }
}

/*!
    \brief      disable ADC interrupt 
    \param[in]  interrupt: the adc interrupt flag
                one or more parameters can be selected which is shown as below:
      \arg        ADC_INT_WDE: analog watchdog interrupt 
      \arg        ADC_INT_EOC: end of group conversion interrupt 
      \arg        ADC_INT_EOIC: end of inserted group conversion interrupt 
    \param[out] none
    \retval     none
*/
void adc_interrupt_disable(uint32_t interrupt)
{  
    /* disable analog watchdog interrupt */
    if(RESET != (interrupt & ADC_INT_WDE)){
        ADC_CTL0 &= ~(uint32_t)ADC_CTL0_WDEIE;
    }
    
    /* disable end of group conversion interrupt */
    if(RESET != (interrupt & ADC_INT_EOC)){
        ADC_CTL0 &= ~(uint32_t)ADC_CTL0_EOCIE;
    }
    
    /* disable end of inserted group conversion interrupt */
    if(RESET != (interrupt & ADC_INT_EOIC)){
        ADC_CTL0 &= ~(uint32_t)ADC_CTL0_EOICIE;
    }
}

/*!
    \brief      configure ADC analog watchdog single channel 
    \param[in]  channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x(x=0..9,16,17): ADC Channelx
    \param[out] none
    \retval     none
*/
void adc_watchdog_single_channel_enable(uint8_t channel)
{
    ADC_CTL0 &= (uint32_t)~(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN | ADC_CTL0_WDSC | ADC_CTL0_WDCHSEL);

    ADC_CTL0 |= (uint32_t)channel;
    ADC_CTL0 |= (uint32_t)(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN | ADC_CTL0_WDSC);
}

/*!
    \brief      configure ADC analog watchdog group channel 
    \param[in]  channel_group: the channel group use analog watchdog
                only one parameter can be selected which is shown as below: 
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
      \arg        ADC_REGULAR_INSERTED_CHANNEL: both regular and inserted group
    \param[out] none
    \retval     none
*/
void adc_watchdog_group_channel_enable(uint8_t channel_group)
{
    ADC_CTL0 &= (uint32_t)~(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN | ADC_CTL0_WDSC);

    /* select the group */
    switch(channel_group){
    case ADC_REGULAR_CHANNEL:
        ADC_CTL0 |= (uint32_t)ADC_CTL0_RWDEN;
        break;
    case ADC_INSERTED_CHANNEL:
        ADC_CTL0 |= (uint32_t)ADC_CTL0_IWDEN;
        break;
    case ADC_REGULAR_INSERTED_CHANNEL:
        ADC_CTL0 |= (uint32_t)(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN);
        break;
    default:
        break;
    }
}

/*!
    \brief      disable ADC analog watchdog 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_watchdog_disable(void)
{
    ADC_CTL0 &= (uint32_t)~(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN | ADC_CTL0_WDSC | ADC_CTL0_WDCHSEL);
}

/*!
    \brief      configure ADC analog watchdog threshold 
    \param[in]  low_threshold: analog watchdog low threshold,0..4095
    \param[in]  high_threshold: analog watchdog high threshold,0..4095
    \param[out] none
    \retval     none
*/
void adc_watchdog_threshold_config(uint16_t low_threshold, uint16_t high_threshold)
{
    ADC_WDLT = (uint32_t)WDLT_WDLT(low_threshold);
    ADC_WDHT = (uint32_t)WDHT_WDHT(high_threshold);
}


/*!
    \brief      configure ADC resolution 
    \param[in]  resolution: ADC resolution
                only one parameter can be selected which is shown as below:
      \arg        ADC_RESOLUTION_12B: 12-bit ADC resolution
      \arg        ADC_RESOLUTION_10B: 10-bit ADC resolution
      \arg        ADC_RESOLUTION_8B: 8-bit ADC resolution
      \arg        ADC_RESOLUTION_6B: 6-bit ADC resolution
    \param[out] none
    \retval     none
*/
void adc_resolution_config(uint32_t resolution)
{
    ADC_CTL0 &= ~((uint32_t)ADC_CTL0_DRES);
    ADC_CTL0 |= (uint32_t)resolution;
}

/*!
    \brief      configure ADC oversample mode 
    \param[in]  mode: ADC oversampling mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_OVERSAMPLING_ALL_CONVERT: all oversampled conversions for a channel are done consecutively after a trigger
      \arg        ADC_OVERSAMPLING_ONE_CONVERT: each oversampled conversion for a channel needs a trigger
    \param[in]  shift: ADC oversampling shift
                only one parameter can be selected which is shown as below:
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
                only one parameter can be selected which is shown as below:
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
void adc_oversample_mode_config(uint8_t mode, uint16_t shift, uint8_t ratio)
{
    /* configure ADC oversampling mode */
    if(ADC_OVERSAMPLING_ONE_CONVERT == mode){
        ADC_OVSAMPCTL |= (uint32_t)ADC_OVSAMPCTL_TOVS;
    }else{
        ADC_OVSAMPCTL &= ~((uint32_t)ADC_OVSAMPCTL_TOVS);
    }
    
    /* configure the shift and ratio */
    ADC_OVSAMPCTL &= ~((uint32_t)(ADC_OVSAMPCTL_OVSR | ADC_OVSAMPCTL_OVSS));
    ADC_OVSAMPCTL |= ((uint32_t)shift | (uint32_t)ratio);
}

/*!
    \brief      enable ADC oversample mode 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_enable(void)
{
    ADC_OVSAMPCTL |= ADC_OVSAMPCTL_OVSEN;
}

/*!
    \brief      disable ADC oversample mode 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_disable(void)
{
    ADC_OVSAMPCTL &= ~((uint32_t)ADC_OVSAMPCTL_OVSEN);
}
