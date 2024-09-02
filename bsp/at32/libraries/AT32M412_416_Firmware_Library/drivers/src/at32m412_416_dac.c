/**
  **************************************************************************
  * @file     at32m412_416_dac.c
  * @brief    contains all the functions for the dac firmware library
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

/** @defgroup DAC
  * @brief DAC driver modules
  * @{
  */

#ifdef DAC_MODULE_ENABLED

/** @defgroup DAC_private_functions
  * @{
  */

/**
  * @brief  dac reset
  * @param  none
  * @retval none
  */
void dac_reset(void)
{
  crm_periph_reset(CRM_DAC_PERIPH_RESET, TRUE);
  crm_periph_reset(CRM_DAC_PERIPH_RESET, FALSE);
}

/**
  * @brief  enable or disable dac
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dac_enable(dac_select_type dac_select, confirm_state new_state)
{
  switch(dac_select)
  {
    case DAC1_SELECT:
      DAC->ctrl_bit.d1en = new_state;
      break;
    case DAC2_SELECT:
      DAC->ctrl_bit.d2en = new_state;
      break;
    default:
      break;
  }
}


/**
  * @brief  enable or disable dac trigger
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dac_trigger_enable(dac_select_type dac_select, confirm_state new_state)
{
  switch(dac_select)
  {
    case DAC1_SELECT:
      DAC->ctrl_bit.d1trgen = new_state;
      break;
    case DAC2_SELECT:
      DAC->ctrl_bit.d2trgen = new_state;
      break;
    default:
      break;
  }
}

/**
  * @brief  select dac trigger
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @param  dac_trigger_source
  *         this parameter can be one of the following values:
  *         - DAC_TMR6_TRGOUT_EVENT
  *         - DAC_TMR3_TRGOUT_EVENT
  *         - DAC_TMR7_TRGOUT_EVENT
  *         - DAC_TMR9_TRGOUT_EVENT
  *         - DAC_TMR4_TRGOUT_EVENT
  *         - DAC_EXTERNAL_INTERRUPT_LINE_9
  *         - DAC_SOFTWARE_TRIGGER
  * @retval none
  */
void dac_trigger_select(dac_select_type dac_select, dac_trigger_type dac_trigger_source)
{
  switch(dac_select)
  {
    case DAC1_SELECT:
      DAC->ctrl_bit.d1trgsel = dac_trigger_source;
      break;
    case DAC2_SELECT:
      DAC->ctrl_bit.d2trgsel = dac_trigger_source;
      break;
    default:
      break;
  }
}

/**
  * @brief  generate dac software trigger
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @retval none
  */
void dac_software_trigger_generate(dac_select_type dac_select)
{
  switch(dac_select)
  {
    case DAC1_SELECT:
      DAC->swtrg_bit.d1swtrg = TRUE;
      break;
    case DAC2_SELECT:
      DAC->swtrg_bit.d2swtrg = TRUE;
      break;
    default:
      break;
  }
}

/**
  * @brief  generate dac dual software trigger synchronously
  * @param  none
  * @retval none
  */
void dac_dual_software_trigger_generate(void)
{
  DAC->swtrg |= 0x03;
}

/**
  * @brief  enable or disable dac dma
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dac_dma_enable(dac_select_type dac_select, confirm_state new_state)
{
  switch(dac_select)
  {
    case DAC1_SELECT:
      DAC->ctrl_bit.d1dmaen = new_state;
      break;
    case DAC2_SELECT:
      DAC->ctrl_bit.d2dmaen = new_state;
      break;
    default:
      break;
  }
}

/**
  * @brief  get dac data output
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @retval dac channel data output
  */
uint8_t dac_data_output_get(dac_select_type dac_select)
{
  uint8_t data_output =0;
  switch(dac_select)
  {
    case DAC1_SELECT:
      data_output = DAC->d1odt_bit.d1odt;
      break;
    case DAC2_SELECT:
      data_output = DAC->d2odt_bit.d2odt;
      break;
    default:
      break;
  }
  return data_output;
}

/**
  * @brief  set dac1 data
  * @param  dac1_data :indecate from selected data holding register
  * @retval none
  */
void dac_1_data_set(uint8_t dac1_data)
{
  DAC->d1dth_bit.d1dth = dac1_data & 0x3F;
}

/**
  * @brief  set dac2 data
  * @param  dac2_data :indecate from selected data holding register
  * @retval none
  */
void dac_2_data_set(uint8_t dac2_data)
{
  DAC->d2dth_bit.d2dth = dac2_data & 0x3F;
}

/**
  * @brief  set dac dual data
  * @param  data1 :dac1 channel indecate from selected data holding register
  * @param  data2 :dac1 channel indecate from selected data holding register
  * @retval none
  */
void dac_dual_data_set(uint8_t data1, uint8_t data2)
{
  DAC->dddth = (uint16_t)((data2 & 0x3F) << 8) | (uint16_t)(data1 & 0x3F);
}

/**
  * @brief  enable/disable dac dma underrun interrupt
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dac_udr_enable(dac_select_type dac_select, confirm_state new_state)
{
  switch(dac_select)
  {
    case DAC1_SELECT:
      DAC->ctrl_bit.d1dmaudrien = new_state;
      break;
    case DAC2_SELECT:
      DAC->ctrl_bit.d2dmaudrien = new_state;
      break;
    default:
      break;
  }
}

/**
  * @brief  get flag of the dac dma underrun flag.
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @retval the new state of dac udr flag status(SET or RESET).
  */
flag_status dac_udr_flag_get(dac_select_type dac_select)
{
  flag_status status = RESET;

  switch(dac_select)
  {
    case DAC1_SELECT:
      if(DAC->sts_bit.d1dmaudrf != 0)
        status = SET;
      break;
    case DAC2_SELECT:
      if(DAC->sts_bit.d2dmaudrf != 0)
        status = SET;
      break;
    default:
      break;
  }
  return status;
}

/**
  * @brief  get flag of the dac dma underrun interrupt flag.
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @retval the new state of dac udr flag status(SET or RESET).
  */
flag_status dac_udr_interrupt_flag_get(dac_select_type dac_select)
{
  flag_status status = RESET;

  switch(dac_select)
  {
    case DAC1_SELECT:
      if((DAC->sts_bit.d1dmaudrf && DAC->ctrl_bit.d1dmaudrien) != 0)
        status = SET;
      break;
    case DAC2_SELECT:
      if((DAC->sts_bit.d2dmaudrf && DAC->ctrl_bit.d2dmaudrien) != 0)
        status = SET;
      break;
    default:
      break;
  }
  return status;
}

/**
  * @brief  clear the dac udr flag.
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @retval none
  */
void dac_udr_flag_clear(dac_select_type dac_select)
{
  switch(dac_select)
  {
    case DAC1_SELECT:
      DAC->sts = DAC1_D1DMAUDRF;
      break;
    case DAC2_SELECT:
      DAC->sts = DAC2_D2DMAUDRF;
      break;
    default:
      break;
  }
}

/**
  * @brief  select dac trigger
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @param  dac_reference_voltage
  *         this parameter can be one of the following values:
  *         - DAC_VDDA
  *         - DAC_VREF
  * @retval none
  */
void dac_reference_voltage_select(dac_select_type dac_select, dac_reference_voltage_type dac_reference_voltage)
{
  switch(dac_select)
  {
    case DAC1_SELECT:
      DAC->ctrl_bit.dac1_vref_sel = dac_reference_voltage;
      break;
    case DAC2_SELECT:
      DAC->ctrl_bit.dac2_vref_sel = dac_reference_voltage;
      break;
    default:
      break;
  }
}

/**
  * @brief  enable or disable dac output to gpio
  * @param  dac_select
  *         this parameter can be one of the following values:
  *         - DAC1_SELECT
  *         - DAC2_SELECT
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dac_output_enable(dac_select_type dac_select, confirm_state new_state)
{
  switch(dac_select)
  {
    case DAC1_SELECT:
      DAC->outen_bit.d1_io = new_state;
      break;
    case DAC2_SELECT:
      DAC->outen_bit.d2_io = new_state;
      break;
    default:
      break;
  }
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
