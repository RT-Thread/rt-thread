/*!
    \file  gd32f4xx_adc.c
    \brief ADC driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "gd32f4xx_adc.h"

#define REGULAR_CHANNEL_LENGTH_OFFSET             ((uint32_t)20U)
#define INSERTED_CHANNEL_LENGTH_OFFSET            ((uint32_t)20U)
#define REGULAR_DISCONTINUOUS_NUMBER              ((uint32_t)13U)
#define REGULAR_TRIGGER_MODE                      ((uint32_t)28U)
#define INSERTED_TRIGGER_MODE                     ((uint32_t)20U)

/*!
    \brief      ADC reset
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
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  none
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
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_disable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ADCON);
}

/*!
    \brief      ADC data alignment config
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  inserted_channel : insert channel select
      \arg        ADC_DATAALIGN_RIGHT: LSB alignment
      \arg        ADC_DATAALIGN_LEFT: MSB alignment
    \param[out] none
    \retval     none
*/
void adc_data_alignment_config(uint32_t adc_periph , uint8_t data_alignment)
{
    if(data_alignment){
        ADC_CTL1(adc_periph) |= ADC_CTL1_DAL;
    }else{
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_DAL);
    }
}

/*!
    \brief      ADC resolution config
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  resolution: ADC resolution
      \arg        ADC_RESOLUTION_12B: 12-bit ADC resolution
      \arg        ADC_RESOLUTION_10B: 10-bit ADC resolution
      \arg        ADC_RESOLUTION_8B: 8-bit ADC resolution
      \arg        ADC_RESOLUTION_6B: 6-bit ADC resolution
    \param[out] none
    \retval     none
*/
void adc_resolution_config(uint32_t adc_periph , uint32_t resolution)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_DRES);
    ADC_CTL0(adc_periph) |= (uint32_t)resolution;
}

/*!
    \brief      ADC calibration and reset calibration
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_calibration_enable(uint32_t adc_periph)
{
    /* reset the selected ADC1 calibration registers */
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
    \brief      ADC discontinuous mode config
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_channel_group: select the channel group
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  length: number of conversions in discontinuous mode,the number can be 1..8
                        for regular channel ,the number is no effect for inserted channel
    \param[out] none
    \retval     none
*/
void adc_discontinuous_mode_config(uint32_t adc_periph , uint8_t adc_channel_group , uint8_t length)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)( ADC_CTL0_DISRC | ADC_CTL0_DISIC ));
    switch(adc_channel_group){
    case ADC_REGULAR_CHANNEL:
        /* config the number of conversions in discontinuous mode  */
        ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_DISNUM);
        if((length <= 8U) && (length >= 1U)){
            ADC_CTL0(adc_periph) |= ((uint32_t)length - 1U) << REGULAR_DISCONTINUOUS_NUMBER;
        }
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_DISRC;
        break;
    case ADC_INSERTED_CHANNEL:
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_DISIC;
        break;
    default:
        break;
    }
}

/*!
    \brief      config end of conversion mode
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  end_selection: end of conversion mode
      \arg        ADC_EOC_SET_SEQUENCE: only at the end of a sequence of regular conversions, the EOC bit is set
      \arg        ADC_EOC_SET_CONVERSION: at the end of each regular conversion, the EOC bit is set.
    \param[out] none
    \retval     none
*/
void adc_end_of_conversion_config(uint32_t adc_periph , uint8_t end_selection)
{
    switch(end_selection){
        case ADC_EOC_SET_SEQUENCE:
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_EOCM);
            break;
        case ADC_EOC_SET_CONVERSION:
            ADC_CTL1(adc_periph) |= (uint32_t)(ADC_CTL1_EOCM);
            break;
        default:
            break;
    }
}

/*!
    \brief      ADC special function enable or disable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  function: select the function to config
      \arg        ADC_SCAN_MODE: scan mode select
      \arg        ADC_INSERTED_CHANNEL_AUTO: inserted channel group convert automatically
      \arg        ADC_CONTINUOUS_MODE: continuous mode select
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_special_function_config(uint32_t adc_periph , uint8_t function , ControlStatus newvalue)
{
    if(newvalue){
        switch(function){
        case ADC_SCAN_MODE:
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_SM;
            break;
        case ADC_INSERTED_CHANNEL_AUTO:
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_ICA;
            break;
        case ADC_CONTINUOUS_MODE:
            ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_CTN;
            break;
        default:
            break;
        }
    }else{
        switch(function){
        case ADC_SCAN_MODE:
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_SM);
            break;
        case ADC_INSERTED_CHANNEL_AUTO:
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_ICA);
            break;
        case ADC_CONTINUOUS_MODE:
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_CTN);
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      configure the ADC clock for all the ADCs
    \param[in]  prescaler: configure ADCs prescaler ratio
      \arg        ADC_ADCCK_PCLK2_DIV2: PCLK2 div2
      \arg        ADC_ADCCK_PCLK2_DIV4: PCLK2 div4
      \arg        ADC_ADCCK_PCLK2_DIV6: PCLK2 div6
      \arg        ADC_ADCCK_PCLK2_DIV8: PCLK2 div8
      \arg        ADC_ADCCK_HCLK_DIV5: HCLK div5
      \arg        ADC_ADCCK_HCLK_DIV6: HCLK div6
      \arg        ADC_ADCCK_HCLK_DIV10: HCLK div10
      \arg        ADC_ADCCK_HCLK_DIV20: HCLK div20
    \param[out] none
    \retval     none
*/
void adc_clock_config(uint32_t prescaler)
{
    ADC_SYNCCTL &= ~((uint32_t)ADC_SYNCCTL_ADCCK);
    ADC_SYNCCTL |= (uint32_t) prescaler;
}

/*!
    \brief      configure the ADC clock for all the ADCs
    \param[in]  function: temperature sensor and internal reference voltage channel or VBAT channel 
      \arg        ADC_VBAT_CHANNEL_SWITCH: channel 18 (1/4 voltate of external battery) switch of ADC0
      \arg        ADC_TEMP_VREF_CHANNEL_SWITCH: channel 16 (temperature sensor) and 17 (internal reference voltage) switch of ADC0
    \param[in]  newvalue: ENABLE or DISABLE
\param[out] none
    \retval     none
*/
void adc_channel_16_to_18(uint8_t function,ControlStatus newvalue)
{
    if(newvalue){
        switch(function){
        case ADC_VBAT_CHANNEL_SWITCH:
            ADC_SYNCCTL |= (uint32_t)ADC_SYNCCTL_VBATEN;
            break;
        case ADC_TEMP_VREF_CHANNEL_SWITCH:
            ADC_SYNCCTL |= (uint32_t)ADC_SYNCCTL_TSVREN;
            break;
        default:
            break;
        }
    }else{
        switch(function){
        case ADC_VBAT_CHANNEL_SWITCH:
            ADC_SYNCCTL &= ~((uint32_t)ADC_SYNCCTL_VBATEN);
            break;
        case ADC_TEMP_VREF_CHANNEL_SWITCH:
            ADC_SYNCCTL &= ~((uint32_t)ADC_SYNCCTL_TSVREN);
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      config the length of regular channel group or inserted channel group
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_channel_group: select the channel group
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  length: the length of the channel
                        regular channel 1-16
                        inserted channel 1-4
    \param[out] none
    \retval     none
*/
void adc_channel_length_config(uint32_t adc_periph , uint8_t adc_channel_group , uint32_t length)
{
    switch(adc_channel_group){
    case ADC_REGULAR_CHANNEL:
        if((length >= 1U) && (length <= 16U)){
            ADC_RSQ0(adc_periph) &= ~((uint32_t)ADC_RSQ0_RL);
            ADC_RSQ0(adc_periph) |= (uint32_t)((length-1U) << REGULAR_CHANNEL_LENGTH_OFFSET);
        }
        break;
    case ADC_INSERTED_CHANNEL:
        if((length >= 1U) && (length <= 4U)){
            ADC_ISQ(adc_periph) &= ~((uint32_t)ADC_ISQ_IL);
            ADC_ISQ(adc_periph) |= (uint32_t)((length-1U) << INSERTED_CHANNEL_LENGTH_OFFSET);
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      ADC external trigger enable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_channel_group: select the channel group
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  trigger_mode: external trigger mode
      \arg        EXTERNAL_TRIGGER_DISABLE: external trigger disable
      \arg        EXTERNAL_TRIGGER_RISING: rising edge of external trigger
      \arg        EXTERNAL_TRIGGER_FALLING: falling edge of external trigger
      \arg        EXTERNAL_TRIGGER_RISING_FALLING: rising and falling edge of external trigger
    \param[out] none
    \retval     none
*/
void adc_external_trigger_config(uint32_t adc_periph , uint8_t adc_channel_group , uint32_t trigger_mode)
{
        switch(adc_channel_group){
        case ADC_REGULAR_CHANNEL:
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ETMRC);
            ADC_CTL1(adc_periph) |= (uint32_t) (trigger_mode << REGULAR_TRIGGER_MODE);
            break;
        case ADC_INSERTED_CHANNEL:
            ADC_CTL1(adc_periph) &=  ~((uint32_t)ADC_CTL1_ETMIC);
            ADC_CTL1(adc_periph) |= (uint32_t) (trigger_mode << INSERTED_TRIGGER_MODE);
            break;
        default:
            break;
        }
}

/*!
    \brief      ADC external trigger source config
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_channel_group: select the channel group
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  external_trigger_source: regular or inserted group trigger source
                for regular channel:
      \arg        ADC_EXTTRIG_REGULAR_T0_CH0: external trigger timer 0 CC0 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T0_CH1: external trigger timer 0 CC1 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T0_CH2: external trigger timer 0 CC2 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T1_CH1: external trigger timer 1 CC1 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T1_CH2: external trigger timer 1 CC2 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T1_CH3: external trigger timer 1 CC3 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T1_TRGO: external trigger timer 1 TRGO event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T2_CH0 : external trigger timer 2 CC0 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T2_TRGO : external trigger timer 2 TRGO event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T3_CH3: external trigger timer 3 CC3 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T4_CH0: external trigger timer 4 CC0 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T4_CH1: external trigger timer 4 CC1 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T4_CH2: external trigger timer 4 CC2 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T7_CH0: external trigger timer 7 CC0 event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_T7_TRGO: external trigger timer 7 TRGO event select for regular channel 
      \arg        ADC_EXTTRIG_REGULAR_EXTI_11: external trigger extiline 11 select for regular channel 
                for inserted channel:
      \arg        ADC_EXTTRIG_INSERTED_T0_CH3: timer0 capture compare 3 
      \arg        ADC_EXTTRIG_INSERTED_T0_TRGO: timer0 TRGO event 
      \arg        ADC_EXTTRIG_INSERTED_T1_CH0: timer1 capture compare 0 
      \arg        ADC_EXTTRIG_INSERTED_T1_TRGO: timer1 TRGO event 
      \arg        ADC_EXTTRIG_INSERTED_T2_CH1: timer2 capture compare 1 
      \arg        ADC_EXTTRIG_INSERTED_T2_CH3: timer2 capture compare 3 
      \arg        ADC_EXTTRIG_INSERTED_T3_CH0: timer3 capture compare 0 
      \arg        ADC_EXTTRIG_INSERTED_T3_CH1: timer3 capture compare 1 
      \arg        ADC_EXTTRIG_INSERTED_T3_CH2: timer3 capture compare 2 
      \arg        ADC_EXTTRIG_INSERTED_T3_TRGO: timer3 capture compare TRGO 
      \arg        ADC_EXTTRIG_INSERTED_T4_CH3: timer4 capture compare 3 
      \arg        ADC_EXTTRIG_INSERTED_T4_TRGO: timer4 capture compare TRGO 
      \arg        ADC_EXTTRIG_INSERTED_T7_CH1: timer7 capture compare 1 
      \arg        ADC_EXTTRIG_INSERTED_T7_CH2: timer7 capture compare 2 
      \arg        ADC_EXTTRIG_INSERTED_T7_CH3: timer7 capture compare 3 
      \arg        ADC_EXTTRIG_INSERTED_EXTI_15: external interrupt line 15 
    \param[out] none
    \retval     none
*/
void adc_external_trigger_source_config(uint32_t adc_periph , uint8_t adc_channel_group , uint32_t external_trigger_source)
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
    \brief      ADC software trigger enable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_channel_group: select the channel group
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[out] none
    \retval     none
*/
void adc_software_trigger_enable(uint32_t adc_periph , uint8_t adc_channel_group)
{
    switch(adc_channel_group){
    case ADC_REGULAR_CHANNEL:
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_SWRCST;
        break;
    case ADC_INSERTED_CHANNEL:
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_SWICST;
        break;
    default:
        break;
    }
}

/*!
    \brief      get the ADC flag bits
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_flag: the adc flag bits
      \arg        ADC_FLAG_WDE: analog watchdog event flag
      \arg        ADC_FLAG_EOC: end of group conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted group conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted channel group
      \arg        ADC_FLAG_STRC: start flag of regular channel group
      \arg        ADC_FLAG_ROVF: regular data register overflow flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_flag_get(uint32_t adc_periph , uint32_t adc_flag)
{
  if(ADC_STAT(adc_periph) & adc_flag){
    return SET;
  }
  return RESET;

}

/*!
    \brief      clear the ADC flag bits
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_flag: the adc flag bits
      \arg        ADC_FLAG_WDE: analog watchdog event flag
      \arg        ADC_FLAG_EOC: end of group conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted group conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted channel group
      \arg        ADC_FLAG_STRC: start flag of regular channel group
      \arg        ADC_FLAG_ROVF: regular data register overflow flag
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
    \param[in]  adc_interrupt: the adc interrupt bits
      \arg        ADC_INT_WDE: analog watchdog interrupt
      \arg        ADC_INT_EOC: end of group conversion interrupt
      \arg        ADC_INT_EOIC: end of inserted group conversion interrupt
      \arg        ADC_INT_ROVF: regular data register overflow interrupt
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph , uint32_t adc_interrupt)
{
    FlagStatus interrupt_flag = RESET;
    uint32_t state;
    /* check the interrupt bits */
    switch(adc_interrupt){
    case ADC_INT_WDE:
        state = ADC_STAT(adc_periph) & ADC_STAT_WDE;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_WDEIE) && state){
          interrupt_flag = SET;
        }
        break;
    case ADC_INT_EOC:
        state = ADC_STAT(adc_periph) & ADC_STAT_EOC;
          if((ADC_CTL0(adc_periph) & ADC_CTL0_EOCIE) && state){
            interrupt_flag = SET;
          }
        break;
    case ADC_INT_EOIC:
        state = ADC_STAT(adc_periph) & ADC_STAT_EOIC;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_EOICIE) && state){
            interrupt_flag = SET;
        }
        break;
    case ADC_INT_ROVF:
        state = ADC_STAT(adc_periph) & ADC_STAT_ROVF;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_ROVFIE) && state){
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
    \param[in]  adc_flag: the adc status flag
      \arg        ADC_INT_WDE: analog watchdog interrupt
      \arg        ADC_INT_EOC: end of group conversion interrupt
      \arg        ADC_INT_EOIC: end of inserted group conversion interrupt
      \arg        ADC_INT_ROVF: regular data register overflow interrupt
    \param[out] none
    \retval     none
*/
void adc_interrupt_flag_clear(uint32_t adc_periph , uint32_t adc_interrupt)
{
    ADC_STAT(adc_periph) &= ~((uint32_t)adc_interrupt);
}

/*!
    \brief      ADC interrupt enable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_flag: the adc interrupt flag
      \arg        ADC_INT_WDE: analog watchdog interrupt flag
      \arg        ADC_INT_EOC: end of group conversion interrupt flag
      \arg        ADC_INT_EOIC: end of inserted group conversion interrupt flag
      \arg        ADC_INT_ROVF: regular data register overflow interrupt flag
    \param[out] none
    \retval     none
*/
void adc_interrupt_enable(uint32_t adc_periph , uint32_t adc_interrupt)
{
    switch(adc_interrupt){
    case ADC_INT_WDE:
        ADC_CTL0(adc_periph) |= (uint32_t) ADC_CTL0_WDEIE;
        break;
    case ADC_INT_EOC:
        ADC_CTL0(adc_periph) |= (uint32_t) ADC_CTL0_EOCIE;
        break;
    case ADC_INT_EOIC:
        ADC_CTL0(adc_periph) |= (uint32_t) ADC_CTL0_EOICIE;
        break;
    case ADC_INT_ROVF:
        ADC_CTL0(adc_periph) |= (uint32_t) ADC_CTL0_ROVFIE;
        break;
    default:
        break;
    }
}

/*!
    \brief      ADC interrupt disable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_flag: the adc interrupt flag
      \arg        ADC_INT_WDE: analog watchdog interrupt flag
      \arg        ADC_INT_EOC: end of group conversion interrupt flag
      \arg        ADC_INT_EOIC: end of inserted group conversion interrupt flag
      \arg        ADC_INT_ROVF: regular data register overflow interrupt flag
    \param[out] none
    \retval     none
*/
void adc_interrupt_disable(uint32_t adc_periph , uint32_t adc_interrupt)
{
    switch(adc_interrupt){
    /* select the interrupt source */
    case ADC_INT_WDE:
        ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_WDEIE);
        break;
    case ADC_INT_EOC:
        ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_EOCIE);
        break;
    case ADC_INT_EOIC:
        ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_EOICIE);
        break;
    case ADC_INT_ROVF:
        ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_ROVFIE);
        break;
    default:
        break;
    }
}

/*!
    \brief      ADC analog watchdog single channel disable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_watchdog_single_channel_disable(uint32_t adc_periph )
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_WDSC);
}

/*!
    \brief      ADC analog watchdog single channel enable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_channel: the selected ADC channel
      \arg        ADC_CHANNEL_x: ADC Channelx(x=0..18)
    \param[out] none
    \retval     none
*/
void adc_watchdog_single_channel_enable(uint32_t adc_periph , uint8_t adc_channel)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_WDCHSEL);

    ADC_CTL0(adc_periph) |= (uint32_t)adc_channel;
    ADC_CTL0(adc_periph) |= (uint32_t) ADC_CTL0_WDSC;
}

/*!
    \brief      adc analog watchdog group channel config
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_channel_group: the channel group use analog watchdog 
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
      \arg        ADC_REGULAR_INSERTED_CHANNEL: both regular and inserted group
    \param[out] none
    \retval     none
*/
void adc_watchdog_enable(uint32_t adc_periph , uint8_t adc_channel_group)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN | ADC_CTL0_WDSC));
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
    \brief      ADC analog watchdog disable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  adc_channel_group: the channel group use analog watchdog 
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
      \arg        ADC_REGULAR_INSERTED_CHANNEL: both regular and inserted group
    \param[out] none
    \retval     none
*/
void adc_watchdog_disable(uint32_t adc_periph , uint8_t adc_channel_group)
{
    /* select the group */
    switch(adc_channel_group){
    case ADC_REGULAR_CHANNEL:
        ADC_CTL0(adc_periph) &=  ~((uint32_t)ADC_CTL0_RWDEN);
        break;
    case ADC_INSERTED_CHANNEL:
        ADC_CTL0(adc_periph) &=  ~((uint32_t)ADC_CTL0_IWDEN);
        break;
    case ADC_REGULAR_INSERTED_CHANNEL:
        ADC_CTL0(adc_periph) &=  ~((uint32_t)(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN));
        break;
    default:
        break;
    }
}

/*!
    \brief      ADC analog watchdog threshold config
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  low_threshold: analog watchdog low threshold,0..4095
    \param[in]  high_threshold: analog watchdog high threshold,0..4095
    \param[out] none
    \retval     none
*/
void adc_watchdog_threshold_config(uint32_t adc_periph , uint16_t low_threshold , uint16_t high_threshold)
{
    ADC_WDLT(adc_periph) = (uint32_t)low_threshold;
    ADC_WDHT(adc_periph) = (uint32_t)high_threshold;
}

/*!
    \brief      ADC regular channel config
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  rank: the regular group sequencer rank,this parameter must be between 0 to 15
    \param[in]  adc_channel: the selected ADC channel
      \arg        ADC_CHANNEL_x(x=0..18): ADC Channelx
    \param[in]  sample_time: the sample time value
      \arg        ADC_SAMPLETIME_3: 3 cycles
      \arg        ADC_SAMPLETIME_15: 15 cycles
      \arg        ADC_SAMPLETIME_28: 28 cycles
      \arg        ADC_SAMPLETIME_56: 56 cycles
      \arg        ADC_SAMPLETIME_84: 84 cycles
      \arg        ADC_SAMPLETIME_112: 112 cycles
      \arg        ADC_SAMPLETIME_144: 144 cycles
      \arg        ADC_SAMPLETIME_480: 480 cycles
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
    }else if(adc_channel < 19U){
        sampt = ADC_SAMPT0(adc_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (3U*(adc_channel-10U))));
        sampt |= (uint32_t)(sample_time << (3U*(adc_channel-10U)));
        ADC_SAMPT0(adc_periph) = sampt;
    }else{
    }
}

/*!
    \brief      ADC regular group data register read
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  none
    \param[out] none
    \retval     the conversion value
*/
uint16_t adc_regular_data_read(uint32_t adc_periph)
{
    return (uint16_t)(ADC_RDATA(adc_periph));
}

/*!
    \brief      ADC inserted channel config
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  rank: the inserted group sequencer rank,this parameter must be between 0 to 3
    \param[in]  adc_channel: the selected ADC channel
      \arg        ADC_CHANNEL_x(x=0..18): ADC Channelx
    \param[in]  sample_time: The sample time value
      \arg        ADC_SAMPLETIME_3: 3 cycles
      \arg        ADC_SAMPLETIME_15: 15 cycles
      \arg        ADC_SAMPLETIME_28: 28 cycles
      \arg        ADC_SAMPLETIME_56: 56 cycles
      \arg        ADC_SAMPLETIME_84: 84 cycles
      \arg        ADC_SAMPLETIME_112: 112 cycles
      \arg        ADC_SAMPLETIME_144: 144 cycles
      \arg        ADC_SAMPLETIME_480: 480 cycles
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_config(uint32_t adc_periph , uint8_t rank , uint8_t adc_channel , uint8_t sample_time)
{
    uint8_t inserted_length;
    uint32_t isq,sampt;

    inserted_length = (uint8_t)GET_BITS(ADC_ISQ(adc_periph) , 20U , 21U);
    if(rank < 4U){
        isq = ADC_ISQ(adc_periph);
        isq &= ~((uint32_t)(ADC_ISQ_ISQN << (15U-(inserted_length-rank)*5U)));
        isq |= ((uint32_t)adc_channel << (15U-(inserted_length-rank)*5U));
        ADC_ISQ(adc_periph) = isq;
    }

    if(adc_channel < 10U){
        sampt = ADC_SAMPT1(adc_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (3U*adc_channel)));
        sampt |= (uint32_t) sample_time << (3U*adc_channel);
        ADC_SAMPT1(adc_periph) = sampt;
    }else if(adc_channel < 19U){
        sampt = ADC_SAMPT0(adc_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (3U*(adc_channel-10U))));
        sampt |= ((uint32_t)sample_time << (3U*(adc_channel-10U)));
        ADC_SAMPT0(adc_periph) = sampt;
    }else{
    }
}

/*!
    \brief      ADC inserted channel offset config
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  inserted_channel : insert channel select
      \arg        ADC_INSERTED_CHANNEL_0: inserted channel0
      \arg        ADC_INSERTED_CHANNEL_1: inserted channel1
      \arg        ADC_INSERTED_CHANNEL_2: inserted channel2
      \arg        ADC_INSERTED_CHANNEL_3: inserted channel3
    \param[in]  offset : the offset data
    \param[out] none
    \retval     the conversion value
*/
void adc_inserted_channel_offset_config(uint32_t adc_periph , uint8_t inserted_channel , uint16_t offset)
{
    /* config the offset of the selected channels */
  if(ADC_INSERTED_CHANNEL_0 == inserted_channel){
      ADC_IOFF0(adc_periph) = (uint32_t)offset;
  }else if(ADC_INSERTED_CHANNEL_1 == inserted_channel){
      ADC_IOFF1(adc_periph) = (uint32_t)offset;
  }else if(ADC_INSERTED_CHANNEL_2 == inserted_channel){
      ADC_IOFF2(adc_periph) = (uint32_t)offset;
  }else if(ADC_INSERTED_CHANNEL_3 == inserted_channel){
      ADC_IOFF3(adc_periph) = (uint32_t)offset;
  }else{
  }
}

/*!
    \brief      ADC inserted group data register read
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  inserted_channel : insert channel select
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
    \brief      DMA request enable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_dma_mode_enable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) |= (uint32_t)(ADC_CTL1_DMA);
}

/*!
    \brief      DMA request disable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_dma_mode_disable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_DMA);
}

/*!
    \brief      when DMA=1, the DMA engine issues a request at end of each regular conversion
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_dma_request_after_last_enable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) |= (uint32_t)(ADC_CTL1_DDM);
}

/*!
    \brief      the DMA engine is disabled after the end of transfer signal from DMA controller is detected
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_dma_request_after_last_disable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_DDM);
}

/*!
    \brief      ADC oversample mode config
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[in]  mode: ADC oversampling mode
      \arg        ADC_OVERSAMPLING_ALL_CONVERT: all oversampled conversions for a channel are done consecutively after a trigger
      \arg        ADC_OVERSAMPLING_ONE_CONVERT: each oversampled conversion for a channel needs a trigger
    \param[in]  shift: ADC oversampling shift
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
void adc_oversample_mode_config(uint32_t adc_periph , uint8_t mode , uint16_t shift , uint8_t ratio)
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
    \brief      ADC oversample mode enable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_enable(uint32_t adc_periph)
{
    ADC_OVSAMPCTL(adc_periph) |= ADC_OVSAMPCTL_OVSEN;
}

/*!
    \brief      ADC oversample mode disable
    \param[in]  adc_periph: ADCx,x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_disable(uint32_t adc_periph)
{
    ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)ADC_OVSAMPCTL_OVSEN);
}

/*!
    \brief      configure the ADC sync mode
    \param[in]  sync_mode: ADC sync mode 
      \arg        ADC_SYNC_MODE_INDEPENDENT: all the ADCs work independently
      \arg        ADC_DAUL_REGULAL_PARALLEL_INSERTED_PARALLEL: ADC0 and ADC1 work in combined regular parallel & inserted parallel mode
      \arg        ADC_DAUL_REGULAL_PARALLEL_INSERTED_ROTATION: ADC0 and ADC1 work in combined regular parallel & trigger rotation mode
      \arg        ADC_DAUL_INSERTED_PARALLEL: ADC0 and ADC1 work in inserted parallel mode
      \arg        ADC_DAUL_REGULAL_PARALLEL: ADC0 and ADC1 work in regular parallel mode
      \arg        ADC_DAUL_REGULAL_FOLLOW_UP: ADC0 and ADC1 work in follow-up mode
      \arg        ADC_DAUL_INSERTED_TRRIGGER_ROTATION: ADC0 and ADC1 work in trigger rotation mode
      \arg        ADC_ALL_REGULAL_PARALLEL_INSERTED_PARALLEL: all ADCs work in combined regular parallel & inserted parallel mode
      \arg        ADC_ALL_REGULAL_PARALLEL_INSERTED_ROTATION: all ADCs work in combined regular parallel & trigger rotation mode
      \arg        ADC_ALL_INSERTED_PARALLEL: all ADCs work in inserted parallel mode
      \arg        ADC_ALL_REGULAL_PARALLEL: all ADCs work in regular parallel mode
      \arg        ADC_ALL_REGULAL_FOLLOW_UP: all ADCs work in follow-up mode
      \arg        ADC_ALL_INSERTED_TRRIGGER_ROTATION: all ADCs work in trigger rotation mode
    \param[out] none
    \retval     none
*/
void adc_sync_mode_config(uint32_t sync_mode)
{
    ADC_SYNCCTL &= ~(ADC_SYNCCTL_SYNCM);
    ADC_SYNCCTL |= sync_mode;
}

/*!
    \brief      configure the delay between 2 sampling phases in ADC sync modes
    \param[in]  sample_delay:  the delay between 2 sampling phases in ADC sync modes 
      \arg        ADC_SYNC_DELAY_xCYCLE: x=5..20,the delay between 2 sampling phases in ADC sync modes is x ADC clock cycles
    \param[out] none
    \retval     none
*/
void adc_sync_delay_config(uint32_t sample_delay)
{
    ADC_SYNCCTL &= ~(ADC_SYNCCTL_SYNCDLY);
    ADC_SYNCCTL |= sample_delay;
}

/*!
    \brief      configure ADC sync DMA mode selection
    \param[in]  dma_mode:  ADC sync DMA mode
      \arg        ADC_SYNC_DMA_DISABLE: ADC sync DMA disabled
      \arg        ADC_SYNC_DMA_MODE0: ADC sync DMA disabled
      \arg        ADC_SYNC_DMA_MODE1: ADC sync DMA disabled
    \param[out] none
    \retval     none
*/
void adc_sync_dma_config(uint32_t dma_mode )
{
    ADC_SYNCCTL &= ~(ADC_SYNCCTL_SYNCDMA);
    ADC_SYNCCTL |= dma_mode;
}

/*!
    \brief      configure ADC sync DMA engine is disabled after the end of transfer signal from DMA controller is detected
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_sync_dma_request_after_last_enable(void)
{
    ADC_SYNCCTL |= ADC_SYNCCTL_SYNCDDM;
}

/*!
    \brief      configure ADC sync DMA engine issues requests according to the SYNCDMA bits
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_sync_dma_request_after_last_disable(void)
{
    ADC_SYNCCTL &= ~(ADC_SYNCCTL_SYNCDDM);
}

/*!
    \brief      ADC sync regular data register read
    \param[in]  none
    \param[out] none
    \retval     sync regular data
*/
uint32_t adc_sync_regular_data_read(void)
{
    return (uint32_t)ADC_SYNCDATA;
}
