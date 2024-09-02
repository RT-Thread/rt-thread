/**
  **************************************************************************
  * @file     at32m412_416_adc.c
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

#include "at32m412_416_conf.h"

/** @addtogroup AT32M412_416_periph_driver
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
  * @param  none
  * @retval none
  */
void adc_reset(void)
{
  crm_periph_reset(CRM_ADC_PERIPH_RESET, TRUE);
  crm_periph_reset(CRM_ADC_PERIPH_RESET, FALSE);
}

/**
  * @brief  enable or disable the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  new_state: new state of a/d converter.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl2_bit.adcen = new_state;
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
  *         - (0x1~0xf)
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
  *         - ADC1, ADC2.
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
  *         - (0x1~0xf)
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
  * @brief  adc common default para init.
  * @param  combine_mode: configure the adc combine_mode mode.
  *         this parameter can be one of the following values:
  *         - ADC_INDEPENDENT_MODE                       - ADC_ORDINARY_SMLT_PREEMPT_SMLT_ONESLAVE_MODE   - ADC_ORDINARY_SMLT_PREEMPT_INTERLTRIG_ONESLAVE_MODE
  *         - ADC_PREEMPT_SMLT_ONLY_ONESLAVE_MODE        - ADC_ORDINARY_SMLT_ONLY_ONESLAVE_MODE           - ADC_ORDINARY_SHIFT_ONLY_ONESLAVE_MODE
  *         - ADC_PREEMPT_INTERLTRIG_ONLY_ONESLAVE_MODE  - ADC_ORDINARY_SMLT_PREEMPT_SMLT_TWOSLAVE_MODE   - ADC_ORDINARY_SMLT_PREEMPT_INTERLTRIG_TWOSLAVE_MODE
  *         - ADC_PREEMPT_SMLT_ONLY_TWOSLAVE_MODE        - ADC_ORDINARY_SMLT_ONLY_TWOSLAVE_MODE           - ADC_ORDINARY_SHIFT_ONLY_TWOSLAVE_MODE
  *         - ADC_PREEMPT_INTERLTRIG_ONLY_TWOSLAVE_MODE
  * @param  div: configure the adc division.
  *         this parameter can be one of the following values:
  *         - ADC_HCLK_DIV_2             - ADC_HCLK_DIV_3             - ADC_HCLK_DIV_4             - ADC_HCLK_DIV_5
  *         - ADC_HCLK_DIV_6             - ADC_HCLK_DIV_7             - ADC_HCLK_DIV_8             - ADC_HCLK_DIV_9
  *         - ADC_HCLK_DIV_10            - ADC_HCLK_DIV_11            - ADC_HCLK_DIV_12            - ADC_HCLK_DIV_13
  *         - ADC_HCLK_DIV_14            - ADC_HCLK_DIV_15            - ADC_HCLK_DIV_16            - ADC_HCLK_DIV_17
  * @param  common_dma_mode: configure the adc common dma mode.
  *         this parameter can be one of the following values:
  *         - ADC_COMMON_DMAMODE_DISABLE
  *         - ADC_COMMON_DMAMODE_1 <mode 1 can be used: all ordinary simultaneous mode,all ordinary shifting mode>
  *         - ADC_COMMON_DMAMODE_2 <mode 2 can be used: one slaver ordinary simultaneous mode,all ordinary shifting mode>
  *         - ADC_COMMON_DMAMODE_3 <mode 3 can be used: one slaver ordinary simultaneous mode in 6/8 bit resolution,ordinary shifting mode in 6/8 bit resolution>
  *         - ADC_COMMON_DMAMODE_4 <mode 4 can be used: two slaver ordinary simultaneous mode in 6/8 bit resolution,two slave ordinary shifting mode in 6/8 bit resolution>
  *         - ADC_COMMON_DMAMODE_5 <mode 5 can be used: all two slaver ordinary simultaneous mode,all two slave ordinary shifting mode>
  * @param  common_dma_request_repeat_state: set the adc common dma request repeat state.
  *         this parameter can be:TRUE or FALSE
  * @param  sampling_interval: configure the ordinary shifting mode adjacent adc sampling interval.
  *         this parameter can be one of the following values:
  *         - ADC_SAMPLING_INTERVAL_4CYCLES     - ADC_SAMPLING_INTERVAL_5CYCLES     - ADC_SAMPLING_INTERVAL_6CYCLES     - ADC_SAMPLING_INTERVAL_7CYCLES
  *         - ADC_SAMPLING_INTERVAL_8CYCLES     - ADC_SAMPLING_INTERVAL_9CYCLES     - ADC_SAMPLING_INTERVAL_10CYCLES    - ADC_SAMPLING_INTERVAL_11CYCLES
  *         - ADC_SAMPLING_INTERVAL_12CYCLES    - ADC_SAMPLING_INTERVAL_13CYCLES    - ADC_SAMPLING_INTERVAL_14CYCLES    - ADC_SAMPLING_INTERVAL_15CYCLES
  *         - ADC_SAMPLING_INTERVAL_16CYCLES    - ADC_SAMPLING_INTERVAL_17CYCLES    - ADC_SAMPLING_INTERVAL_18CYCLES    - ADC_SAMPLING_INTERVAL_19CYCLES
  * @param  tempervintrv_state: set the adc temperature sensor and vintrv state.
  *         this parameter can be:TRUE or FALSE
  * @retval none
  */
void adc_common_default_para_init(adc_common_config_type *adc_common_struct)
{
  adc_common_struct->combine_mode = ADC_INDEPENDENT_MODE;
  adc_common_struct->div = ADC_HCLK_DIV_2;
  adc_common_struct->common_dma_mode = ADC_COMMON_DMAMODE_DISABLE;
  adc_common_struct->common_dma_request_repeat_state = FALSE;
  adc_common_struct->sampling_interval = ADC_SAMPLING_INTERVAL_4CYCLES;
  adc_common_struct->tempervintrv_state = FALSE;
}

/**
  * @brief  adc common default para init.
  * @param  combine_mode: configure the adc combine_mode mode.
  *         this parameter can be one of the following values:
  *         - ADC_INDEPENDENT_MODE                       - ADC_ORDINARY_SMLT_PREEMPT_SMLT_ONESLAVE_MODE   - ADC_ORDINARY_SMLT_PREEMPT_INTERLTRIG_ONESLAVE_MODE
  *         - ADC_PREEMPT_SMLT_ONLY_ONESLAVE_MODE        - ADC_ORDINARY_SMLT_ONLY_ONESLAVE_MODE           - ADC_ORDINARY_SHIFT_ONLY_ONESLAVE_MODE
  *         - ADC_PREEMPT_INTERLTRIG_ONLY_ONESLAVE_MODE  - ADC_ORDINARY_SMLT_PREEMPT_SMLT_TWOSLAVE_MODE   - ADC_ORDINARY_SMLT_PREEMPT_INTERLTRIG_TWOSLAVE_MODE
  *         - ADC_PREEMPT_SMLT_ONLY_TWOSLAVE_MODE        - ADC_ORDINARY_SMLT_ONLY_TWOSLAVE_MODE           - ADC_ORDINARY_SHIFT_ONLY_TWOSLAVE_MODE
  *         - ADC_PREEMPT_INTERLTRIG_ONLY_TWOSLAVE_MODE
  * @param  div: configure the adc division.
  *         this parameter can be one of the following values:
  *         - ADC_HCLK_DIV_2             - ADC_HCLK_DIV_3             - ADC_HCLK_DIV_4             - ADC_HCLK_DIV_5
  *         - ADC_HCLK_DIV_6             - ADC_HCLK_DIV_7             - ADC_HCLK_DIV_8             - ADC_HCLK_DIV_9
  *         - ADC_HCLK_DIV_10            - ADC_HCLK_DIV_11            - ADC_HCLK_DIV_12            - ADC_HCLK_DIV_13
  *         - ADC_HCLK_DIV_14            - ADC_HCLK_DIV_15            - ADC_HCLK_DIV_16            - ADC_HCLK_DIV_17
  * @param  common_dma_mode: configure the adc common dma mode.
  *         this parameter can be one of the following values:
  *         - ADC_COMMON_DMAMODE_DISABLE
  *         - ADC_COMMON_DMAMODE_1 <mode 1 can be used: all ordinary simultaneous mode,all ordinary shifting mode>
  *         - ADC_COMMON_DMAMODE_2 <mode 2 can be used: one slaver ordinary simultaneous mode,all ordinary shifting mode>
  *         - ADC_COMMON_DMAMODE_3 <mode 3 can be used: one slaver ordinary simultaneous mode in 6/8 bit resolution,ordinary shifting mode in 6/8 bit resolution>
  *         - ADC_COMMON_DMAMODE_4 <mode 4 can be used: two slaver ordinary simultaneous mode in 6/8 bit resolution,two slave ordinary shifting mode in 6/8 bit resolution>
  *         - ADC_COMMON_DMAMODE_5 <mode 5 can be used: all two slaver ordinary simultaneous mode,all two slave ordinary shifting mode>
  * @param  common_dma_request_repeat_state: set the adc common dma request repeat state.
  *         this parameter can be:TRUE or FALSE
  * @param  sampling_interval: configure the ordinary shifting mode adjacent adc sampling interval.
  *         this parameter can be one of the following values:
  *         - ADC_SAMPLING_INTERVAL_5CYCLES     - ADC_SAMPLING_INTERVAL_6CYCLES     - ADC_SAMPLING_INTERVAL_7CYCLES     - ADC_SAMPLING_INTERVAL_8CYCLES
  *         - ADC_SAMPLING_INTERVAL_9CYCLES     - ADC_SAMPLING_INTERVAL_10CYCLES    - ADC_SAMPLING_INTERVAL_11CYCLES    - ADC_SAMPLING_INTERVAL_12CYCLES
  *         - ADC_SAMPLING_INTERVAL_13CYCLES    - ADC_SAMPLING_INTERVAL_14CYCLES    - ADC_SAMPLING_INTERVAL_15CYCLES    - ADC_SAMPLING_INTERVAL_16CYCLES
  *         - ADC_SAMPLING_INTERVAL_17CYCLES    - ADC_SAMPLING_INTERVAL_18CYCLES    - ADC_SAMPLING_INTERVAL_19CYCLES    - ADC_SAMPLING_INTERVAL_20CYCLES
  * @param  tempervintrv_state: set the adc temperature sensor and vintrv state.
  *         this parameter can be:TRUE or FALSE
  * @retval none
  */
void adc_common_config(adc_common_config_type *adc_common_struct)
{
  ADCCOM->cctrl_bit.mssel = adc_common_struct->combine_mode;
  ADCCOM->cctrl_bit.adcdiv = adc_common_struct->div;
  if(adc_common_struct->common_dma_mode & 0x04)
  {
    ADCCOM->cctrl_bit.msdmasel_h = TRUE;
  }
  else
  {
    ADCCOM->cctrl_bit.msdmasel_h = FALSE;
  }
  ADCCOM->cctrl_bit.msdmasel_l = adc_common_struct->common_dma_mode &0x03;
  ADCCOM->cctrl_bit.msdrcen = adc_common_struct->common_dma_request_repeat_state;
  ADCCOM->cctrl_bit.asisel = adc_common_struct->sampling_interval;
  ADCCOM->cctrl_bit.itsrven = adc_common_struct->tempervintrv_state;
}

/**
  * @brief  set resolution of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  resolution: set the conversion resolution.
  *         this parameter can be one of the following values:
  *         - ADC_RESOLUTION_12B
  *         - ADC_RESOLUTION_10B
  *         - ADC_RESOLUTION_8B
  *         - ADC_RESOLUTION_6B
  * @retval none
  */
void adc_resolution_set(adc_type *adc_x, adc_resolution_type resolution)
{
  adc_x->ctrl1_bit.crsel = resolution;
}

/**
  * @brief  enable or disable the adc dma transfer.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  new_state: new state of the adc dma transfer.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_dma_mode_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl2_bit.ocdmaen = new_state;
}

/**
  * @brief  enable or disable the adc dma request repeat.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  new_state: the adc dma request repeat state.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_dma_request_repeat_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl2_bit.ocdrcen = new_state;
}

/**
  * @brief  enable or disable the specified adc interrupts.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  adc_int: specifies the adc interrupt sources to be enabled or disabled.
  *         this parameter can be one of the following values:
  *         - ADC_OCCE_INT
  *         - ADC_VMOR_INT
  *         - ADC_PCCE_INT
  *         - ADC_OCCO_INT
  *         - ADC_TCF_INT
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
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
  * @param  adc_high_threshold: voltage monitoring's high thresholds value.
  *         this parameter can be:
  *         - (0x0000~0xFFFF)
  * @param  adc_low_threshold: voltage monitoring's low thresholds value.
  *         this parameter can be:
  *         - (0x0000~0xFFFF)
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
  *         - ADC1, ADC2.
  * @param  adc_channel: select the channel.
  *         when adc_x is ADC1, this parameter can be one of the following values:
  *         - ADC_CHANNEL_0    - ADC_CHANNEL_2    - ADC_CHANNEL_4    - ADC_CHANNEL_6
  *         - ADC_CHANNEL_9    - ADC_CHANNEL_11   - ADC_CHANNEL_12   - ADC_CHANNEL_14
  *         - ADC_CHANNEL_15   - ADC_CHANNEL_16   - ADC_CHANNEL_17   - ADC_CHANNEL_19
  *         - ADC_CHANNEL_20   - ADC_CHANNEL_21   - ADC_CHANNEL_22   - ADC_CHANNEL_23
  *         - ADC_CHANNEL_24   - ADC_CHANNEL_26
  * @param  adc_channel: select the channel.
  *         when adc_x is ADC2, this parameter can be one of the following values:
  *         - ADC_CHANNEL_0    - ADC_CHANNEL_1    - ADC_CHANNEL_2    - ADC_CHANNEL_3
  *         - ADC_CHANNEL_4    - ADC_CHANNEL_5    - ADC_CHANNEL_6    - ADC_CHANNEL_7
  *         - ADC_CHANNEL_8    - ADC_CHANNEL_9    - ADC_CHANNEL_10   - ADC_CHANNEL_11
  *         - ADC_CHANNEL_12   - ADC_CHANNEL_14   - ADC_CHANNEL_16   - ADC_CHANNEL_17
  *         - ADC_CHANNEL_19   - ADC_CHANNEL_20
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
  *         - ADC1, ADC2.
  * @param  adc_channel: select the channel.
  *         when adc_x is ADC1, this parameter can be one of the following values:
  *         - ADC_CHANNEL_0    - ADC_CHANNEL_2    - ADC_CHANNEL_4    - ADC_CHANNEL_6
  *         - ADC_CHANNEL_9    - ADC_CHANNEL_11   - ADC_CHANNEL_12   - ADC_CHANNEL_14
  *         - ADC_CHANNEL_15   - ADC_CHANNEL_16   - ADC_CHANNEL_17   - ADC_CHANNEL_19
  *         - ADC_CHANNEL_20   - ADC_CHANNEL_21   - ADC_CHANNEL_22   - ADC_CHANNEL_23
  *         - ADC_CHANNEL_24   - ADC_CHANNEL_26
  * @param  adc_channel: select the channel.
  *         when adc_x is ADC2, this parameter can be one of the following values:
  *         - ADC_CHANNEL_0    - ADC_CHANNEL_1    - ADC_CHANNEL_2    - ADC_CHANNEL_3
  *         - ADC_CHANNEL_4    - ADC_CHANNEL_5    - ADC_CHANNEL_6    - ADC_CHANNEL_7
  *         - ADC_CHANNEL_8    - ADC_CHANNEL_9    - ADC_CHANNEL_10   - ADC_CHANNEL_11
  *         - ADC_CHANNEL_12   - ADC_CHANNEL_14   - ADC_CHANNEL_16   - ADC_CHANNEL_17
  *         - ADC_CHANNEL_19   - ADC_CHANNEL_20
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
  switch(adc_channel)
  {
    case ADC_CHANNEL_0:
      adc_x->spt2_bit.cspt0 = adc_sampletime;
      break;
    case ADC_CHANNEL_1:
      adc_x->spt2_bit.cspt1 = adc_sampletime;
      break;
    case ADC_CHANNEL_2:
      adc_x->spt2_bit.cspt2 = adc_sampletime;
      break;
    case ADC_CHANNEL_3:
      adc_x->spt2_bit.cspt3 = adc_sampletime;
      break;
    case ADC_CHANNEL_4:
      adc_x->spt2_bit.cspt4 = adc_sampletime;
      break;
    case ADC_CHANNEL_5:
      adc_x->spt2_bit.cspt5 = adc_sampletime;
      break;
    case ADC_CHANNEL_6:
      adc_x->spt2_bit.cspt6 = adc_sampletime;
      break;
    case ADC_CHANNEL_7:
      adc_x->spt2_bit.cspt7 = adc_sampletime;
      break;
    case ADC_CHANNEL_8:
      adc_x->spt2_bit.cspt8 = adc_sampletime;
      break;
    case ADC_CHANNEL_9:
      adc_x->spt2_bit.cspt9 = adc_sampletime;
      break;
    case ADC_CHANNEL_10:
      adc_x->spt1_bit.cspt10 = adc_sampletime;
      break;
    case ADC_CHANNEL_11:
      adc_x->spt1_bit.cspt11 = adc_sampletime;
      break;
    case ADC_CHANNEL_12:
      adc_x->spt1_bit.cspt12 = adc_sampletime;
      break;
    case ADC_CHANNEL_14:
      adc_x->spt1_bit.cspt14 = adc_sampletime;
      break;
    case ADC_CHANNEL_15:
      adc_x->spt1_bit.cspt15 = adc_sampletime;
      break;
    case ADC_CHANNEL_16:
      adc_x->spt1_bit.cspt16 = adc_sampletime;
      break;
    case ADC_CHANNEL_17:
      adc_x->spt1_bit.cspt17 = adc_sampletime;
      break;
    case ADC_CHANNEL_19:
      adc_x->spt1_bit.cspt19 = adc_sampletime;
      break;
    case ADC_CHANNEL_20:
      adc_x->spt3_bit.cspt20 = adc_sampletime;
      break;
    case ADC_CHANNEL_21:
      adc_x->spt3_bit.cspt21 = adc_sampletime;
      break;
    case ADC_CHANNEL_22:
      adc_x->spt3_bit.cspt22 = adc_sampletime;
      break;
    case ADC_CHANNEL_23:
      adc_x->spt3_bit.cspt23 = adc_sampletime;
      break;
    case ADC_CHANNEL_24:
      adc_x->spt3_bit.cspt24 = adc_sampletime;
      break;
    case ADC_CHANNEL_26:
      adc_x->spt3_bit.cspt26 = adc_sampletime;
      break;
    default:
      break;
  }
  switch(adc_sequence)
  {
    case 1:
      adc_x->osq3_bit.osn1 = adc_channel;
      break;
    case 2:
      adc_x->osq3_bit.osn2 = adc_channel;
      break;
    case 3:
      adc_x->osq3_bit.osn3 = adc_channel;
      break;
    case 4:
      adc_x->osq3_bit.osn4 = adc_channel;
      break;
    case 5:
      adc_x->osq3_bit.osn5 = adc_channel;
      break;
    case 6:
      adc_x->osq3_bit.osn6 = adc_channel;
      break;
    case 7:
      adc_x->osq2_bit.osn7 = adc_channel;
      break;
    case 8:
      adc_x->osq2_bit.osn8 = adc_channel;
      break;
    case 9:
      adc_x->osq2_bit.osn9 = adc_channel;
      break;
    case 10:
      adc_x->osq2_bit.osn10 = adc_channel;
      break;
    case 11:
      adc_x->osq2_bit.osn11 = adc_channel;
      break;
    case 12:
      adc_x->osq2_bit.osn12 = adc_channel;
      break;
    case 13:
      adc_x->osq1_bit.osn13 = adc_channel;
      break;
    case 14:
      adc_x->osq1_bit.osn14 = adc_channel;
      break;
    case 15:
      adc_x->osq1_bit.osn15 = adc_channel;
      break;
    case 16:
      adc_x->osq1_bit.osn16 = adc_channel;
      break;
    default:
      break;
  }
}

/**
  * @brief  set preempt channel lenghth of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
  * @param  adc_channel: select the channel.
  *         when adc_x is ADC1, this parameter can be one of the following values:
  *         - ADC_CHANNEL_0    - ADC_CHANNEL_2    - ADC_CHANNEL_4    - ADC_CHANNEL_6
  *         - ADC_CHANNEL_9    - ADC_CHANNEL_11   - ADC_CHANNEL_12   - ADC_CHANNEL_14
  *         - ADC_CHANNEL_15   - ADC_CHANNEL_16   - ADC_CHANNEL_17   - ADC_CHANNEL_19
  *         - ADC_CHANNEL_20   - ADC_CHANNEL_21   - ADC_CHANNEL_22   - ADC_CHANNEL_23
  *         - ADC_CHANNEL_24   - ADC_CHANNEL_26
  * @param  adc_channel: select the channel.
  *         when adc_x is ADC2, this parameter can be one of the following values:
  *         - ADC_CHANNEL_0    - ADC_CHANNEL_1    - ADC_CHANNEL_2    - ADC_CHANNEL_3
  *         - ADC_CHANNEL_4    - ADC_CHANNEL_5    - ADC_CHANNEL_6    - ADC_CHANNEL_7
  *         - ADC_CHANNEL_8    - ADC_CHANNEL_9    - ADC_CHANNEL_10   - ADC_CHANNEL_11
  *         - ADC_CHANNEL_12   - ADC_CHANNEL_14   - ADC_CHANNEL_16   - ADC_CHANNEL_17
  *         - ADC_CHANNEL_19   - ADC_CHANNEL_20
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
  uint16_t sequence_index=0;
  switch(adc_channel)
  {
    case ADC_CHANNEL_0:
      adc_x->spt2_bit.cspt0 = adc_sampletime;
      break;
    case ADC_CHANNEL_1:
      adc_x->spt2_bit.cspt1 = adc_sampletime;
      break;
    case ADC_CHANNEL_2:
      adc_x->spt2_bit.cspt2 = adc_sampletime;
      break;
    case ADC_CHANNEL_3:
      adc_x->spt2_bit.cspt3 = adc_sampletime;
      break;
    case ADC_CHANNEL_4:
      adc_x->spt2_bit.cspt4 = adc_sampletime;
      break;
    case ADC_CHANNEL_5:
      adc_x->spt2_bit.cspt5 = adc_sampletime;
      break;
    case ADC_CHANNEL_6:
      adc_x->spt2_bit.cspt6 = adc_sampletime;
      break;
    case ADC_CHANNEL_7:
      adc_x->spt2_bit.cspt7 = adc_sampletime;
      break;
    case ADC_CHANNEL_8:
      adc_x->spt2_bit.cspt8 = adc_sampletime;
      break;
    case ADC_CHANNEL_9:
      adc_x->spt2_bit.cspt9 = adc_sampletime;
      break;
    case ADC_CHANNEL_10:
      adc_x->spt1_bit.cspt10 = adc_sampletime;
      break;
    case ADC_CHANNEL_11:
      adc_x->spt1_bit.cspt11 = adc_sampletime;
      break;
    case ADC_CHANNEL_12:
      adc_x->spt1_bit.cspt12 = adc_sampletime;
      break;
    case ADC_CHANNEL_14:
      adc_x->spt1_bit.cspt14 = adc_sampletime;
      break;
    case ADC_CHANNEL_15:
      adc_x->spt1_bit.cspt15 = adc_sampletime;
      break;
    case ADC_CHANNEL_16:
      adc_x->spt1_bit.cspt16 = adc_sampletime;
      break;
    case ADC_CHANNEL_17:
      adc_x->spt1_bit.cspt17 = adc_sampletime;
      break;
    case ADC_CHANNEL_19:
      adc_x->spt1_bit.cspt19 = adc_sampletime;
      break;
    case ADC_CHANNEL_20:
      adc_x->spt3_bit.cspt20 = adc_sampletime;
      break;
    case ADC_CHANNEL_21:
      adc_x->spt3_bit.cspt21 = adc_sampletime;
      break;
    case ADC_CHANNEL_22:
      adc_x->spt3_bit.cspt22 = adc_sampletime;
      break;
    case ADC_CHANNEL_23:
      adc_x->spt3_bit.cspt23 = adc_sampletime;
      break;
    case ADC_CHANNEL_24:
      adc_x->spt3_bit.cspt24 = adc_sampletime;
      break;
    case ADC_CHANNEL_26:
      adc_x->spt3_bit.cspt26 = adc_sampletime;
      break;
    default:
      break;
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
  * @brief  set the ordinary channel's external trigger edge and
  *         set external trigger event of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  adc_ordinary_trig: select the external trigger event.
  *         this parameter can be one of the following values:
  *         - ADC_ORDINARY_TRIG_TMR1CH1     - ADC_ORDINARY_TRIG_TMR1CH2      - ADC_ORDINARY_TRIG_TMR1CH3      - ADC_ORDINARY_TRIG_TMR2CH2
  *         - ADC_ORDINARY_TRIG_TMR2CH3     - ADC_ORDINARY_TRIG_TMR2CH4      - ADC_ORDINARY_TRIG_TMR2TRGOUT   - ADC_ORDINARY_TRIG_TMR3CH1
  *         - ADC_ORDINARY_TRIG_TMR3TRGOUT  - ADC_ORDINARY_TRIG_TMR4CH4      - ADC_ORDINARY_TRIG_TMR5CH1      - ADC_ORDINARY_TRIG_TMR5CH2
  *         - ADC_ORDINARY_TRIG_TMR5CH3     - ADC_ORDINARY_TRIG_TMR8CH1      - ADC_ORDINARY_TRIG_TMR8TRGOUT   - ADC_ORDINARY_TRIG_EXINT11
  *         - ADC_ORDINARY_TRIG_TMR20TRGOUT - ADC_ORDINARY_TRIG_TMR20TRGOUT2 - ADC_ORDINARY_TRIG_TMR20CH1     - ADC_ORDINARY_TRIG_TMR20CH2
  *         - ADC_ORDINARY_TRIG_TMR20CH3    - ADC_ORDINARY_TRIG_TMR8TRGOUT2  - ADC_ORDINARY_TRIG_TMR1TRGOUT2  - ADC_ORDINARY_TRIG_TMR4TRGOUT
  *         - ADC_ORDINARY_TRIG_TMR6TRGOUT  - ADC_ORDINARY_TRIG_TMR3CH4      - ADC_ORDINARY_TRIG_TMR4CH1      - ADC_ORDINARY_TRIG_TMR1TRGOUT
  *         - ADC_ORDINARY_TRIG_TMR2CH1     - ADC_ORDINARY_TRIG_TMR7TRGOUT
  * @param  adc_ordinary_trig_edge: ordinary channel conversion's external_trigger_edge.
  *         this parameter can be one of the following values:
  *         - ADC_ORDINARY_TRIG_EDGE_NONE
  *         - ADC_ORDINARY_TRIG_EDGE_RISING
  *         - ADC_ORDINARY_TRIG_EDGE_FALLING
  *         - ADC_ORDINARY_TRIG_EDGE_RISING_FALLING
  * @retval none
  */
void adc_ordinary_conversion_trigger_set(adc_type *adc_x, adc_ordinary_trig_select_type adc_ordinary_trig, adc_ordinary_trig_edge_type adc_ordinary_trig_edge)
{
  if(adc_ordinary_trig > ADC_ORDINARY_TRIG_EXINT11)
  {
    adc_x->ctrl2_bit.octesel_h = 1;
    adc_x->ctrl2_bit.octesel_l = adc_ordinary_trig & 0x0F;
  }
  else
  {
    adc_x->ctrl2_bit.octesel_h = 0;
    adc_x->ctrl2_bit.octesel_l = adc_ordinary_trig & 0x0F;
  }
  adc_x->ctrl2_bit.ocete = adc_ordinary_trig_edge;
}

/**
  * @brief  enable or disable the preempt channel's external trigger and
  *         set external trigger event of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  adc_preempt_trig: select the external trigger event.
  *         this parameter can be one of the following values:
  *         - ADC_PREEMPT_TRIG_TMR1CH4      - ADC_PREEMPT_TRIG_TMR1TRGOUT   - ADC_PREEMPT_TRIG_TMR2CH1   - ADC_PREEMPT_TRIG_TMR2TRGOUT
  *         - ADC_PREEMPT_TRIG_TMR3CH2      - ADC_PREEMPT_TRIG_TMR3CH4      - ADC_PREEMPT_TRIG_TMR4CH1   - ADC_PREEMPT_TRIG_TMR4CH2
  *         - ADC_PREEMPT_TRIG_TMR4CH3      - ADC_PREEMPT_TRIG_TMR4TRGOUT   - ADC_PREEMPT_TRIG_TMR5CH4   - ADC_PREEMPT_TRIG_TMR5TRGOUT
  *         - ADC_PREEMPT_TRIG_TMR8CH2      - ADC_PREEMPT_TRIG_TMR8CH3      - ADC_PREEMPT_TRIG_TMR8CH4   - ADC_PREEMPT_TRIG_EXINT15
  *         - ADC_PREEMPT_TRIG_TMR20TRGOUT  - ADC_PREEMPT_TRIG_TMR20TRGOUT2 - ADC_PREEMPT_TRIG_TMR20CH4  - ADC_PREEMPT_TRIG_TMR1TRGOUT2
  *         - ADC_PREEMPT_TRIG_TMR8TRGOUT   - ADC_PREEMPT_TRIG_TMR8TRGOUT2  - ADC_PREEMPT_TRIG_TMR3CH3   - ADC_PREEMPT_TRIG_TMR3TRGOUT
  *         - ADC_PREEMPT_TRIG_TMR3CH1      - ADC_PREEMPT_TRIG_TMR6TRGOUT   - ADC_PREEMPT_TRIG_TMR4CH4   - ADC_PREEMPT_TRIG_TMR1CH3
  *         - ADC_PREEMPT_TRIG_TMR20CH2     - ADC_PREEMPT_TRIG_TMR7TRGOUT
  * @param  adc_preempt_trig_edge: preempt channel conversion's external_trigger_edge.
  *         this parameter can be one of the following values:
  *         - ADC_PREEMPT_TRIG_EDGE_NONE
  *         - ADC_PREEMPT_TRIG_EDGE_RISING
  *         - ADC_PREEMPT_TRIG_EDGE_FALLING
  *         - ADC_PREEMPT_TRIG_EDGE_RISING_FALLING
  * @retval none
  */
void adc_preempt_conversion_trigger_set(adc_type *adc_x, adc_preempt_trig_select_type adc_preempt_trig, adc_preempt_trig_edge_type adc_preempt_trig_edge)
{
  if(adc_preempt_trig > ADC_PREEMPT_TRIG_EXINT15)
  {
    adc_x->ctrl2_bit.pctesel_h = 1;
    adc_x->ctrl2_bit.pctesel_l = adc_preempt_trig & 0x0F;
  }
  else
  {
    adc_x->ctrl2_bit.pctesel_h = 0;
    adc_x->ctrl2_bit.pctesel_l = adc_preempt_trig & 0x0F;
  }
  adc_x->ctrl2_bit.pcete = adc_preempt_trig_edge;
}

/**
  * @brief  set preempt channel's conversion value offset of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
  * @param  new_state: new state of automatic preempt group conversion.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_preempt_auto_mode_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl1_bit.pcautoen = new_state;
}

/**
  * @brief  stop the ongoing conversion of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @retval none
  */
void adc_conversion_stop(adc_type *adc_x)
{
  adc_x->ctrl2_bit.adabrt = TRUE;
}

/**
  * @brief  get stop conversion's status of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @retval the new state of stop conversion's status(SET or RESET).
  */
flag_status adc_conversion_stop_status_get(adc_type *adc_x)
{
  if(adc_x->ctrl2_bit.adabrt)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  enable or disable each ordinary channel conversion set occe flag of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  new_state: new state of each ordinary channel conversion set occe flag.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_occe_each_conversion_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl2_bit.eocsfen = new_state;
}

/**
  * @brief  enable or disable ordinary software start conversion of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
  * @param  new_state: new state of preempt software start conversion.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_preempt_software_trigger_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl2_bit.pcswtrg = new_state;
  adc_x->ctrl2_bit.pcswtrg = FALSE;
}

/**
  * @brief  get preempt software start conversion status of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
  * @retval the last conversion data for ordinary channel.
  */
uint16_t adc_ordinary_conversion_data_get(adc_type *adc_x)
{
  return (uint16_t)(adc_x->odt_bit.odt);
}

/**
  * @brief  return the last ordinary conversion data of combine adc.
  * @retval the last conversion data for ordinary channel.
  */
uint32_t adc_combine_ordinary_conversion_data_get(void)
{
  return (uint32_t)(ADCCOM->codt);
}

/**
  * @brief  return the conversion data for selection preempt channel of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
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
  *         - ADC1, ADC2.
  * @param  adc_flag: select the adc flag.
  *         this parameter can be one of the following values:
  *         - ADC_VMOR_FLAG
  *         - ADC_OCCE_FLAG
  *         - ADC_PCCE_FLAG
  *         - ADC_PCCS_FLAG(no interrupt associated)
  *         - ADC_OCCS_FLAG(no interrupt associated)
  *         - ADC_OCCO_FLAG
  *         - ADC_RDY_FLAG(no interrupt associated)
  *         - ADC_TCF_FLAG
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
  *         - ADC1, ADC2.
  * @param  adc_flag: select the adc flag.
  *         this parameter can be one of the following values:
  *         - ADC_VMOR_FLAG
  *         - ADC_OCCE_FLAG
  *         - ADC_PCCE_FLAG
  *         - ADC_OCCO_FLAG
  *         - ADC_TCF_FLAG
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
    case ADC_OCCE_FLAG:
      if(adc_x->sts_bit.occe && adc_x->ctrl1_bit.occeien)
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
    case ADC_OCCO_FLAG:
      if(adc_x->sts_bit.occo && adc_x->ctrl1_bit.occoien)
      {
        status = SET;
      }
      break;
    case ADC_TCF_FLAG:
      if(adc_x->sts_bit.tcf && adc_x->ctrl1_bit.tcfien)
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
  *         ADC1, ADC2.
  * @param  adc_flag: select the adc flag.
  *         this parameter can be any combination of the following values:
  *         - ADC_VMOR_FLAG
  *         - ADC_OCCE_FLAG(also can clear by reading the adc_x->odt)
  *         - ADC_PCCE_FLAG
  *         - ADC_PCCS_FLAG
  *         - ADC_OCCS_FLAG
  *         - ADC_OCCO_FLAG
  *         - ADC_TCF_FLAG
  *         - note:"ADC_RDY_FLAG" cannot be choose!rdy bit is readonly bit,it means the adc is ready to accept conversion request
  * @retval none
  */
void adc_flag_clear(adc_type *adc_x, uint32_t adc_flag)
{
  adc_x->sts = ~adc_flag;
}

/**
  * @brief  enable or disable the ordinary oversampling of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  new_state: new state of ordinary oversampling.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_ordinary_oversample_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ovsp_bit.oosen = new_state;
}

/**
  * @brief  enable or disable the preempt oversampling of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  new_state: new state of preempt oversampling.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_preempt_oversample_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ovsp_bit.posen = new_state;
}

/**
  * @brief  config the oversampling ratio and shift of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  adc_oversample_ratio: set the oversample ratio.
  *         this parameter can be one of the following values:
  *         - ADC_OVERSAMPLE_RATIO_2
  *         - ADC_OVERSAMPLE_RATIO_4
  *         - ADC_OVERSAMPLE_RATIO_8
  *         - ADC_OVERSAMPLE_RATIO_16
  *         - ADC_OVERSAMPLE_RATIO_32
  *         - ADC_OVERSAMPLE_RATIO_64
  *         - ADC_OVERSAMPLE_RATIO_128
  *         - ADC_OVERSAMPLE_RATIO_256
  * @param  adc_oversample_shift: set the oversample shift.
  *         this parameter can be one of the following values:
  *         - ADC_OVERSAMPLE_SHIFT_0
  *         - ADC_OVERSAMPLE_SHIFT_1
  *         - ADC_OVERSAMPLE_SHIFT_2
  *         - ADC_OVERSAMPLE_SHIFT_3
  *         - ADC_OVERSAMPLE_SHIFT_4
  *         - ADC_OVERSAMPLE_SHIFT_5
  *         - ADC_OVERSAMPLE_SHIFT_6
  *         - ADC_OVERSAMPLE_SHIFT_7
  *         - ADC_OVERSAMPLE_SHIFT_8
  * @retval none
  */
void adc_oversample_ratio_shift_set(adc_type *adc_x, adc_oversample_ratio_type adc_oversample_ratio, adc_oversample_shift_type adc_oversample_shift)
{
  adc_x->ovsp_bit.osrsel = adc_oversample_ratio;
  adc_x->ovsp_bit.osssel = adc_oversample_shift;
}

/**
  * @brief  enable or disable the ordinary oversampling trigger mode of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  new_state: new state of ordinary oversampling trigger mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void adc_ordinary_oversample_trig_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ovsp_bit.oostren = new_state;
}

/**
  * @brief  set ordinary oversample restart mode of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  adc_or_oversample_restart: ordinary oversample restart mode.
  *         this parameter can be one of the following values:
  *         - ADC_OVERSAMPLE_CONTINUE
  *         - ADC_OVERSAMPLE_RESTART
  * @retval none
  */
void adc_ordinary_oversample_restart_set(adc_type *adc_x, adc_ordinary_oversample_restart_type adc_ordinary_oversample_restart)
{
  adc_x->ovsp_bit.oosrsel = adc_ordinary_oversample_restart;
}

/**
  * @brief  enable or disable adc trigger conversion fail auto conversion abort.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  new_state: new state of ordinary oversampling trigger mode.
  *         this parameter can be: TRUE or FALSE.
  *         - note: if you want to use "conversion fail auto conversion abort" function(tcfaca=1), you must enable enable tcf interrupt first(tcfien=1).
  * @retval none
  */
void adc_convert_fail_auto_abort_enable(adc_type *adc_x, confirm_state new_state)
{
  adc_x->ctrl1_bit.tcfien = new_state;
  adc_x->ctrl1_bit.tcfaca = new_state;
}

/**
  * @brief  return the conversion data for ordinary channel of the specified adc peripheral.
  * @param  adc_x: select the adc peripheral.
  *         this parameter can be one of the following values:
  *         - ADC1, ADC2.
  * @param  adc_sequence_number: the adc conversion sequence number.
  *         this parameter can be:
  *         - (0x1~0x10)
  * @retval the conversion data for ordinary channel.
  */
uint16_t adc_common_ordinary_data_get(adc_type *adc_x, uint16_t adc_sequence_number)
{
  uint32_t address_index = 0;
  if(adc_x == ADC1)
  {
    address_index = (uint32_t)&(ADCCOM->adc1_odt1) + (adc_sequence_number - 1) * 4;
  }
  else if(adc_x == ADC2)
  {
    address_index = (uint32_t)&(ADCCOM->adc2_odt1) + (adc_sequence_number - 1) * 4;
  }
  return (uint16_t)(*(uint32_t *)(address_index));
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
