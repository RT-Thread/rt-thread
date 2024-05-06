/**
  **************************************************************************
  * @file     at32a403a_adc.c
  * @brief    contains all the functions for the adc firmware library
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32a403a_conf.h"

/** @addtogroup AT32A403A_periph_driver
  * @{
  */

/** @defgroup ADC
  * @brief ADC driver modules
  * @{
  */

#ifdef ADC_MODULE_ENABLED

/** @defgroup ADC_private_functions
  * @{
  */

/**
  * @brief  deinitialize the adc peripheral registers to their default reset values.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @retval none
  */
void adc_reset(adc_type *adc_x)
{
  if(adc_x == ADC1)
  {
    crm_periph_reset(CRM_ADC1_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_ADC1_PERIPH_RESET, FALSE);
  }
  else if(adc_x == ADC2)
  {
    crm_periph_reset(CRM_ADC2_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_ADC2_PERIPH_RESET, FALSE);
  }
  else if(adc_x == ADC3)
  {
    crm_periph_reset(CRM_ADC3_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_ADC3_PERIPH_RESET, FALSE);
  }
}

/**
  * @brief  enable or disable the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  new_state: new state of a/d converter.
  *         this parameter can be: TRUE or FALSE.
  *         note:after adc ready,user set adcen bit will cause ordinary conversion
  * @retval none
  */
void adc_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl2_bit.adcen = new_state;
}

/**
  * @brief  select combine mode of the specified adc peripheral.
  * @param  combine_mode: select the adc combine mode.
  *         this parameter can be one of the following values:
  *         - ADC_INDEPENDENT_MODE
  *         - ADC_ORDINARY_SMLT_PREEMPT_SMLT_MODE
  *         - ADC_ORDINARY_SMLT_PREEMPT_INTERLTRIG_MODE
  *         - ADC_ORDINARY_SHORTSHIFT_PREEMPT_SMLT_MODE
  *         - ADC_ORDINARY_LONGSHIFT_PREEMPT_SMLT_MODE
  *         - ADC_PREEMPT_SMLT_ONLY_MODE
  *         - ADC_ORDINARY_SMLT_ONLY_MODE
  *         - ADC_ORDINARY_SHORTSHIFT_ONLY_MODE
  *         - ADC_ORDINARY_LONGSHIFT_ONLY_MODE
  *         - ADC_PREEMPT_INTERLTRIG_ONLY_MODE
  *         note:these bits are reserved in adc2 and adc3
  * @retval none
  */
void adc_combine_mode_select(adc_combine_mode_type combine_mode)
{
    ADC1->ctrl1_bit.mssel = combine_mode;
}

/**
  * @brief  adc base default para init.
  * @param  sequence_mode: set the state of adc sequence mode.
  *         this parameter can be:TRUE or FALSE
  * @param  repeat_mode: set the state of adc repeat conversion mode.
  *         this parameter can be:TRUE or FALSE
  * @param  data_align: set the state of adc data alignment.
  *         this parameter can be one of the following values:
  *         - ADC_RIGHT_ALIGNMENT
  *         - ADC_LEFT_ALIGNMENT
  * @param  ordinary_channel_length: configure the adc ordinary channel sequence length.
  *         this parameter can be:
  *         - (0x1~0x10)
  * @retval none
  */
void adc_base_default_para_init(adc_base_config_type *adc_base_struct)
{
  adc_base_struct->sequence_mode = FALSE;
  adc_base_struct->repeat_mode = FALSE;
  adc_base_struct->data_align = ADC_RIGHT_ALIGNMENT;
  adc_base_struct->ordinary_channel_length = 1;
}

/**
  * @brief  initialize the adc peripheral according to the specified parameters.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  sequence_mode: set the state of adc sequence mode.
  *         this parameter can be:TRUE or FALSE
  * @param  repeat_mode: set the state of adc repeat conversion mode.
  *         this parameter can be:TRUE or FALSE
  * @param  data_align: set the state of adc data alignment.
  *         this parameter can be one of the following values:
  *         - ADC_RIGHT_ALIGNMENT
  *         - ADC_LEFT_ALIGNMENT
  * @param  ordinary_channel_length: configure the adc ordinary channel sequence length.
  *         this parameter can be:
  *         - (0x1~0x10)
  * @retval none
  */
void adc_base_config(adc_type *adc_x, adc_base_config_type *adc_base_struct)
{
  adc_x->ctrl1_bit.sqen = adc_base_struct->sequence_mode;
  adc_x->ctrl2_bit.rpen = adc_base_struct->repeat_mode;
  adc_x->ctrl2_bit.dtalign = adc_base_struct->data_align;
  adc_x->osq1_bit.oclen = adc_base_struct->ordinary_channel_length - 1;
}

/**
  * @brief  enable or disable the adc dma transfer.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC3.
  *         note:this bit is reserved in adc2
  * @param  new_state: new state of the adc dma transfer.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_dma_mode_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl2_bit.ocdmaen = new_state;
}

/**
  * @brief  enable or disable the specified adc interrupts.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_int: specifies the adc interrupt sources to be enabled or disabled.
  *         this parameter can be one of the following values:
  *         - ADC_VMOR_INT
  *         - ADC_CCE_INT
  *         - ADC_PCCE_INT
  * @param  new_state: new state of the specified adc interrupts.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_interrupt_enable(adc_type *adc_x, uint32_t adc_int, confirm_state new_state)
{
  if(new_state == TRUE)
  {
    adc_x->ctrl1 |= adc_int;
  }
  else if(new_state == FALSE)
  {
    adc_x->ctrl1 &= ~adc_int;
  }
}

/**
  * @brief  initialize calibration register of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @retval none
  */
void adc_calibration_init(adc_type *adc_x)
{
  adc_x->ctrl2_bit.adcalinit = TRUE;
}

/**
  * @brief  get calibration register's initialize status of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @retval the new state of reset calibration register status(SET or RESET).
  */
flag_status adc_calibration_init_status_get(adc_type *adc_x)
{
  if(adc_x->ctrl2_bit.adcalinit)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  start calibration process of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @retval none
  */
void adc_calibration_start(adc_type *adc_x)
{
  adc_x->ctrl2_bit.adcal = TRUE;
}

/**
  * @brief  get calibration status of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @retval the new state of calibration status(SET or RESET).
  */
flag_status adc_calibration_status_get(adc_type *adc_x)
{
  if(adc_x->ctrl2_bit.adcal)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  enable or disable the voltage monitoring on single/all ordinary or preempt channels of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_voltage_monitoring: choose the adc_voltage_monitoring config.
  *         this parameter can be one of the following values:
  *         - ADC_VMONITOR_SINGLE_ORDINARY
  *         - ADC_VMONITOR_SINGLE_PREEMPT
  *         - ADC_VMONITOR_SINGLE_ORDINARY_PREEMPT
  *         - ADC_VMONITOR_ALL_ORDINARY
  *         - ADC_VMONITOR_ALL_PREEMPT
  *         - ADC_VMONITOR_ALL_ORDINARY_PREEMPT
  *         - ADC_VMONITOR_NONE
  * @retval none
  */
void adc_voltage_monitor_enable(adc_type *adc_x, adc_voltage_monitoring_type adc_voltage_monitoring)
{
  adc_x->ctrl1_bit.ocvmen = FALSE;
  adc_x->ctrl1_bit.pcvmen = FALSE;
  adc_x->ctrl1_bit.vmsgen = FALSE;
  adc_x->ctrl1 |= adc_voltage_monitoring;
}

/**
  * @brief  set voltage monitoring's high and low thresholds value of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_high_threshold: voltage monitoring's high thresholds value.
  *         this parameter can be:
  *         - (0x000~0xFFF)
  * @param  adc_low_threshold: voltage monitoring's low thresholds value.
  *         this parameter can be:
  *         - (0x000~0xFFF)
  * @retval none
  */
void adc_voltage_monitor_threshold_value_set(adc_type *adc_x, uint16_t adc_high_threshold, uint16_t adc_low_threshold)
{
  adc_x->vmhb_bit.vmhb = adc_high_threshold;
  adc_x->vmlb_bit.vmlb = adc_low_threshold;
}

/**
  * @brief  select the voltage monitoring's channel of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_channel: select the channel.
  *         this parameter can be one of the following values:
  *         - ADC_CHANNEL_0    - ADC_CHANNEL_1    - ADC_CHANNEL_2    - ADC_CHANNEL_3
  *         - ADC_CHANNEL_4    - ADC_CHANNEL_5    - ADC_CHANNEL_6    - ADC_CHANNEL_7
  *         - ADC_CHANNEL_8    - ADC_CHANNEL_9    - ADC_CHANNEL_10   - ADC_CHANNEL_11
  *         - ADC_CHANNEL_12   - ADC_CHANNEL_13   - ADC_CHANNEL_14   - ADC_CHANNEL_15
  *         - ADC_CHANNEL_16   - ADC_CHANNEL_17
  * @retval none
  */
void adc_voltage_monitor_single_channel_select(adc_type *adc_x, adc_channel_select_type adc_channel)
{
  adc_x->ctrl1_bit.vmcsel = adc_channel;
}

/**
  * @brief  set ordinary channel's corresponding rank in the sequencer and sample time of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_channel: select the channel.
  *         this parameter can be one of the following values:
  *         - ADC_CHANNEL_0    - ADC_CHANNEL_1    - ADC_CHANNEL_2    - ADC_CHANNEL_3
  *         - ADC_CHANNEL_4    - ADC_CHANNEL_5    - ADC_CHANNEL_6    - ADC_CHANNEL_7
  *         - ADC_CHANNEL_8    - ADC_CHANNEL_9    - ADC_CHANNEL_10   - ADC_CHANNEL_11
  *         - ADC_CHANNEL_12   - ADC_CHANNEL_13   - ADC_CHANNEL_14   - ADC_CHANNEL_15
  *         - ADC_CHANNEL_16   - ADC_CHANNEL_17
  * @param  adc_sequence: set rank in the ordinary group sequencer.
  *         this parameter must be:
  *         - between 1 to 16
  * @param  adc_sampletime: set the sampletime of adc channel.
  *         this parameter can be one of the following values:
  *         - ADC_SAMPLETIME_1_5
  *         - ADC_SAMPLETIME_7_5
  *         - ADC_SAMPLETIME_13_5
  *         - ADC_SAMPLETIME_28_5
  *         - ADC_SAMPLETIME_41_5
  *         - ADC_SAMPLETIME_55_5
  *         - ADC_SAMPLETIME_71_5
  *         - ADC_SAMPLETIME_239_5
  * @retval none
  */
void adc_ordinary_channel_set(adc_type *adc_x, adc_channel_select_type adc_channel, uint8_t adc_sequence, adc_sampletime_select_type adc_sampletime)
{
  uint32_t tmp_reg;
  if(adc_channel < ADC_CHANNEL_10)
  {
    tmp_reg = adc_x->spt2;
    tmp_reg &= ~(0x07 << 3 * adc_channel);
    tmp_reg |= adc_sampletime << 3 * adc_channel;
    adc_x->spt2 = tmp_reg;
  }
  else
  {
    tmp_reg = adc_x->spt1;
    tmp_reg &= ~(0x07 << 3 * (adc_channel - ADC_CHANNEL_10));
    tmp_reg |= adc_sampletime << 3 * (adc_channel - ADC_CHANNEL_10);
    adc_x->spt1 = tmp_reg;
  }

  if(adc_sequence >= 13)
  {
    tmp_reg = adc_x->osq1;
    tmp_reg &= ~(0x01F << 5 * (adc_sequence - 13));
    tmp_reg |= adc_channel << 5 * (adc_sequence - 13);
    adc_x->osq1 = tmp_reg;
  }
  else if(adc_sequence >= 7)
  {
    tmp_reg = adc_x->osq2;
    tmp_reg &= ~(0x01F << 5 * (adc_sequence - 7));
    tmp_reg |= adc_channel << 5 * (adc_sequence - 7);
    adc_x->osq2 = tmp_reg;
  }
  else
  {
    tmp_reg = adc_x->osq3;
    tmp_reg &= ~(0x01F << 5 * (adc_sequence - 1));
    tmp_reg |= adc_channel << 5 * (adc_sequence - 1);
    adc_x->osq3 = tmp_reg;
  }
}

/**
  * @brief  set preempt channel lenghth of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_channel_lenght: set the adc preempt channel lenghth.
  *         this parameter can be:
  *         - (0x1~0x4)
  * @retval none
  */
void adc_preempt_channel_length_set(adc_type *adc_x, uint8_t adc_channel_lenght)
{
  adc_x->psq_bit.pclen =  adc_channel_lenght - 1;
}

/**
  * @brief  configure preempt channel's corresponding rank in the sequencer and sample time of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_channel: select the channel.
  *         this parameter can be one of the following values:
  *         - ADC_CHANNEL_0    - ADC_CHANNEL_1    - ADC_CHANNEL_2    - ADC_CHANNEL_3
  *         - ADC_CHANNEL_4    - ADC_CHANNEL_5    - ADC_CHANNEL_6    - ADC_CHANNEL_7
  *         - ADC_CHANNEL_8    - ADC_CHANNEL_9    - ADC_CHANNEL_10   - ADC_CHANNEL_11
  *         - ADC_CHANNEL_12   - ADC_CHANNEL_13   - ADC_CHANNEL_14   - ADC_CHANNEL_15
  *         - ADC_CHANNEL_16   - ADC_CHANNEL_17
  * @param  adc_sequence: set rank in the preempt group sequencer.
  *         this parameter must be:
  *         - between 1 to 4
  * @param  adc_sampletime: config the sampletime of adc channel.
  *         this parameter can be one of the following values:
  *         - ADC_SAMPLETIME_1_5
  *         - ADC_SAMPLETIME_7_5
  *         - ADC_SAMPLETIME_13_5
  *         - ADC_SAMPLETIME_28_5
  *         - ADC_SAMPLETIME_41_5
  *         - ADC_SAMPLETIME_55_5
  *         - ADC_SAMPLETIME_71_5
  *         - ADC_SAMPLETIME_239_5
  * @retval none
  */
void adc_preempt_channel_set(adc_type *adc_x, adc_channel_select_type adc_channel, uint8_t adc_sequence, adc_sampletime_select_type adc_sampletime)
{
  uint32_t tmp_reg;
  uint8_t sequence_index;
  if(adc_channel < ADC_CHANNEL_10)
  {
    tmp_reg = adc_x->spt2;
    tmp_reg &= ~(0x07 << 3 * adc_channel);
    tmp_reg |= adc_sampletime << 3 * adc_channel;
    adc_x->spt2 = tmp_reg;
  }
  else
  {
    tmp_reg = adc_x->spt1;
    tmp_reg &= ~(0x07 << 3 * (adc_channel - ADC_CHANNEL_10));
    tmp_reg |= adc_sampletime << 3 * (adc_channel - ADC_CHANNEL_10);
    adc_x->spt1 = tmp_reg;
  }

  sequence_index = adc_sequence + 3 - adc_x->psq_bit.pclen;
  switch(sequence_index)
  {
    case 1:
      adc_x->psq_bit.psn1 = adc_channel;
      break;
    case 2:
      adc_x->psq_bit.psn2 = adc_channel;
      break;
    case 3:
      adc_x->psq_bit.psn3 = adc_channel;
      break;
    case 4:
      adc_x->psq_bit.psn4 = adc_channel;
      break;
    default:
      break;
  }
}

/**
  * @brief  enable or disable the ordinary channel's external trigger and
  *         set external trigger event of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_ordinary_trig: select the external trigger event.
  *         this parameter can be one of the following values:
  *         adc1 & adc2
  *         - ADC12_ORDINARY_TRIG_TMR1CH1     - ADC12_ORDINARY_TRIG_TMR1CH2  - ADC12_ORDINARY_TRIG_TMR1CH3             - ADC12_ORDINARY_TRIG_TMR2CH2
  *         - ADC12_ORDINARY_TRIG_TMR3TRGOUT  - ADC12_ORDINARY_TRIG_TMR4CH4  - ADC12_ORDINARY_TRIG_EXINT11_TMR8TRGOUT  - ADC12_ORDINARY_TRIG_SOFTWARE
  *         - ADC12_ORDINARY_TRIG_TMR1TRGOUT  - ADC12_ORDINARY_TRIG_TMR8CH1  - ADC12_ORDINARY_TRIG_TMR8CH2
  *         adc3
  *         - ADC3_ORDINARY_TRIG_TMR3CH1      - ADC3_ORDINARY_TRIG_TMR2CH3   - ADC3_ORDINARY_TRIG_TMR1CH3              - ADC3_ORDINARY_TRIG_TMR8CH1
  *         - ADC3_ORDINARY_TRIG_TMR8TRGOUT   - ADC3_ORDINARY_TRIG_TMR5CH1   - ADC3_ORDINARY_TRIG_TMR5CH3              - ADC3_ORDINARY_TRIG_SOFTWARE
  *         - ADC3_ORDINARY_TRIG_TMR1TRGOUT   - ADC3_ORDINARY_TRIG_TMR1CH1   - ADC3_ORDINARY_TRIG_TMR8CH3
  * @param  new_state: new state of ordinary channel's external trigger.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_ordinary_conversion_trigger_set(adc_type *adc_x, adc_ordinary_trig_select_type adc_ordinary_trig, confirm_state new_state)
{
  if(adc_ordinary_trig > 7)
  {
    adc_x->ctrl2_bit.octesel_h = 1;
    adc_x->ctrl2_bit.octesel_l = adc_ordinary_trig & 0x7;
  }
  else
  {
    adc_x->ctrl2_bit.octesel_h = 0;
    adc_x->ctrl2_bit.octesel_l = adc_ordinary_trig & 0x7;
  }
  adc_x->ctrl2_bit.octen = new_state;
}

/**
  * @brief  enable or disable the preempt channel's external trigger and
  *         set external trigger event of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_preempt_trig: select the external trigger event.
  *         this parameter can be one of the following values:
  *         adc1 & adc2
  *         - ADC12_PREEMPT_TRIG_TMR1TRGOUT  - ADC12_PREEMPT_TRIG_TMR1CH4     - ADC12_PREEMPT_TRIG_TMR2TRGOUT      - ADC12_PREEMPT_TRIG_TMR2CH1
  *         - ADC12_PREEMPT_TRIG_TMR3CH4     - ADC12_PREEMPT_TRIG_TMR4TRGOUT  - ADC12_PREEMPT_TRIG_EXINT15_TMR8CH4 - ADC12_PREEMPT_TRIG_SOFTWARE
  *         - ADC12_PREEMPT_TRIG_TMR1CH1     - ADC12_PREEMPT_TRIG_TMR8CH1     - ADC12_PREEMPT_TRIG_TMR8TRGOUT
  *         adc3
  *         - ADC3_PREEMPT_TRIG_TMR1TRGOUT   - ADC3_PREEMPT_TRIG_TMR1CH4      - ADC3_PREEMPT_TRIG_TMR4CH3          - ADC3_PREEMPT_TRIG_TMR8CH2
  *         - ADC3_PREEMPT_TRIG_TMR8CH4      - ADC3_PREEMPT_TRIG_TMR5TRGOUT   - ADC3_PREEMPT_TRIG_TMR5CH4          - ADC3_PREEMPT_TRIG_SOFTWARE
  *         - ADC3_PREEMPT_TRIG_TMR1CH1      - ADC3_PREEMPT_TRIG_TMR1CH2      - ADC3_PREEMPT_TRIG_TMR8TRGOUT
  * @param  new_state: new state of preempt channel's external trigger.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_preempt_conversion_trigger_set(adc_type *adc_x, adc_preempt_trig_select_type adc_preempt_trig, confirm_state new_state)
{
  if(adc_preempt_trig > 7)
  {
    adc_x->ctrl2_bit.pctesel_h = 1;
    adc_x->ctrl2_bit.pctesel_l = adc_preempt_trig & 0x7;
  }
  else
  {
    adc_x->ctrl2_bit.pctesel_h = 0;
    adc_x->ctrl2_bit.pctesel_l = adc_preempt_trig & 0x7;
  }
  adc_x->ctrl2_bit.pcten = new_state;
}


/**
  * @brief  set preempt channel's conversion value offset of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_preempt_channel: select the preempt channel.
  *         this parameter can be one of the following values:
  *         - ADC_PREEMPT_CHANNEL_1
  *         - ADC_PREEMPT_CHANNEL_2
  *         - ADC_PREEMPT_CHANNEL_3
  *         - ADC_PREEMPT_CHANNEL_4
  * @param  adc_offset_value: set the adc preempt channel's conversion value offset.
  *         this parameter can be:
  *         - (0x000~0xFFF)
  * @retval none
  */
void adc_preempt_offset_value_set(adc_type *adc_x, adc_preempt_channel_type adc_preempt_channel, uint16_t adc_offset_value)
{
  switch(adc_preempt_channel)
  {
    case ADC_PREEMPT_CHANNEL_1:
      adc_x->pcdto1_bit.pcdto1 = adc_offset_value;
      break;
    case ADC_PREEMPT_CHANNEL_2:
      adc_x->pcdto2_bit.pcdto2 = adc_offset_value;
      break;
    case ADC_PREEMPT_CHANNEL_3:
      adc_x->pcdto3_bit.pcdto3 = adc_offset_value;
      break;
    case ADC_PREEMPT_CHANNEL_4:
      adc_x->pcdto4_bit.pcdto4 = adc_offset_value;
      break;
    default:
      break;
  }
}

/**
  * @brief  set partitioned mode channel count of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_channel_count: configure the adc partitioned mode channel count.
  *         this parameter can be:
  *         - (0x1~0x8)
  * @retval none
  */
void adc_ordinary_part_count_set(adc_type *adc_x, uint8_t adc_channel_count)
{

  adc_x->ctrl1_bit.ocpcnt =  adc_channel_count - 1;
}

/**
  * @brief  enable or disable the partitioned mode on ordinary channel of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  new_state: new state of ordinary channel's partitioned mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_ordinary_part_mode_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl1_bit.ocpen = new_state;
}

/**
  * @brief  enable or disable the partitioned mode on preempt channel of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  new_state: new state of preempt channel's partitioned mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_preempt_part_mode_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl1_bit.pcpen = new_state;
}

/**
  * @brief  enable or disable automatic preempt group conversion of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  new_state: new state of automatic preempt group conversion.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_preempt_auto_mode_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl1_bit.pcautoen = new_state;
}

/**
  * @brief  enable or disable the temperature sensor and vintrv channel.
  * @param  new_state: new state of Internal temperature sensor and vintrv.
  *         this parameter can be: TRUE or FALSE.
  *         note:this bit is present only in adc1
  * @retval none
  */
void adc_tempersensor_vintrv_enable(confirm_state new_state)
{
  ADC1->ctrl2_bit.itsrven = new_state;
}

/**
  * @brief  enable or disable ordinary software start conversion of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  new_state: new state of ordinary software start conversion.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_ordinary_software_trigger_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl2_bit.ocswtrg = new_state;
}

/**
  * @brief  get ordinary software start conversion status of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @retval the new state of ordinary software start conversion status(SET or RESET).
  */
flag_status adc_ordinary_software_trigger_status_get(adc_type *adc_x)
{
  if(adc_x->ctrl2_bit.ocswtrg)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  enable or disable preempt software start conversion of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  new_state: new state of preempt software start conversion.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_preempt_software_trigger_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl2_bit.pcswtrg = new_state;
}

/**
  * @brief  get preempt software start conversion status of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @retval the new state of preempt software start conversion status(SET or RESET).
  */
flag_status adc_preempt_software_trigger_status_get(adc_type *adc_x)
{
  if(adc_x->ctrl2_bit.pcswtrg)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  return the last conversion data for ordinary channel of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @retval the last conversion data for ordinary channel.
  */
uint16_t adc_ordinary_conversion_data_get(adc_type *adc_x)
{
  return (uint16_t)(adc_x->odt_bit.odt);
}

/**
  * @brief  return the last conversion data for ordinary channel of combine adc(adc1 and adc2).
  * @retval the last conversion data for ordinary channel.
  */
uint32_t adc_combine_ordinary_conversion_data_get(void)
{
  return (uint32_t)(ADC1->odt);
}

/**
  * @brief  return the conversion data for selection preempt channel of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_preempt_channel: select the preempt channel.
  *         this parameter can be one of the following values:
  *         - ADC_PREEMPT_CHANNEL_1
  *         - ADC_PREEMPT_CHANNEL_2
  *         - ADC_PREEMPT_CHANNEL_3
  *         - ADC_PREEMPT_CHANNEL_4
  * @retval the conversion data for selection preempt channel.
  */
uint16_t adc_preempt_conversion_data_get(adc_type *adc_x, adc_preempt_channel_type adc_preempt_channel)
{
  uint16_t preempt_conv_data_index = 0;
  switch(adc_preempt_channel)
  {
    case ADC_PREEMPT_CHANNEL_1:
      preempt_conv_data_index = (uint16_t)(adc_x->pdt1_bit.pdt1);
      break;
    case ADC_PREEMPT_CHANNEL_2:
      preempt_conv_data_index = (uint16_t)(adc_x->pdt2_bit.pdt2);
      break;
    case ADC_PREEMPT_CHANNEL_3:
      preempt_conv_data_index = (uint16_t)(adc_x->pdt3_bit.pdt3);
      break;
    case ADC_PREEMPT_CHANNEL_4:
      preempt_conv_data_index = (uint16_t)(adc_x->pdt4_bit.pdt4);
      break;
    default:
      break;
  }
  return preempt_conv_data_index;
}

/**
  * @brief  get flag of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_flag: select the adc flag.
  *         this parameter can be one of the following values:
  *         - ADC_VMOR_FLAG
  *         - ADC_CCE_FLAG
  *         - ADC_PCCE_FLAG
  *         - ADC_PCCS_FLAG(no interrupt associated)
  *         - ADC_OCCS_FLAG(no interrupt associated)
  * @retval the new state of adc flag status(SET or RESET).
  */
flag_status adc_flag_get(adc_type *adc_x, uint8_t adc_flag)
{
  flag_status status = RESET;

  if((adc_x->sts & adc_flag) == RESET)
  {
    status = RESET;
  }
  else
  {
    status = SET;
  }
  return status;
}

/**
  * @brief  get interrupt flag of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_flag: select the adc flag.
  *         this parameter can be one of the following values:
  *         - ADC_VMOR_FLAG
  *         - ADC_CCE_FLAG
  *         - ADC_PCCE_FLAG
  * @retval the new state of adc flag status(SET or RESET).
  */
flag_status adc_interrupt_flag_get(adc_type *adc_x, uint8_t adc_flag)
{
  flag_status status = RESET;
  switch(adc_flag)
  {
    case ADC_VMOR_FLAG:
      if(adc_x->sts_bit.vmor && adc_x->ctrl1_bit.vmorien)
      {
        status = SET;
      }
      break;
    case ADC_CCE_FLAG:
      if(adc_x->sts_bit.cce && adc_x->ctrl1_bit.cceien)
      {
        status = SET;
      }
      break;
    case ADC_PCCE_FLAG:
      if(adc_x->sts_bit.pcce && adc_x->ctrl1_bit.pcceien)
      {
        status = SET;
      }
      break;
    default:
      break;
  }
  return status;
}

/**
  * @brief  clear flag of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         ADC1, ADC2, ADC3.
  * @param  adc_flag: select the adc flag.
  *         this parameter can be any combination of the following values:
  *         - ADC_VMOR_FLAG
  *         - ADC_CCE_FLAG(also can clear by reading the adc_x->odt)
  *         - ADC_PCCE_FLAG
  *         - ADC_PCCS_FLAG
  *         - ADC_OCCS_FLAG
  * @retval none
  */
void adc_flag_clear(adc_type *adc_x, uint32_t adc_flag)
{
  adc_x->sts = ~adc_flag;
}

/**
  * @}
  */

#endif

/**
  * @}
  */

/**
  * @}
  */
