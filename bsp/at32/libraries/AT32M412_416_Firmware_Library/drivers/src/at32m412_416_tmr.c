/**
  **************************************************************************
  * @file     at32m412_416_tmr.c
  * @brief    contains all the functions for the tmr firmware library
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

/** @defgroup TMR
  * @brief TMR driver modules
  * @{
  */

#ifdef TMR_MODULE_ENABLED

/** @defgroup TMR_private_functions
  * @{
  */

/**
  * @brief  tmr reset by crm reset register
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @retval none
  */
void tmr_reset(tmr_type *tmr_x)
{
  if(tmr_x == TMR1)
  {
    crm_periph_reset(CRM_TMR1_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_TMR1_PERIPH_RESET, FALSE);
  }
  else if(tmr_x == TMR3)
  {
    crm_periph_reset(CRM_TMR3_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_TMR3_PERIPH_RESET, FALSE);
  }
  else if(tmr_x == TMR4)
  {
    crm_periph_reset(CRM_TMR4_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_TMR4_PERIPH_RESET, FALSE);
  }
  else if(tmr_x == TMR6)
  {
    crm_periph_reset(CRM_TMR6_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_TMR6_PERIPH_RESET, FALSE);
  }
  else if(tmr_x == TMR7)
  {
    crm_periph_reset(CRM_TMR7_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_TMR7_PERIPH_RESET, FALSE);
  }
  else if(tmr_x == TMR9)
  {
    crm_periph_reset(CRM_TMR9_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_TMR9_PERIPH_RESET, FALSE);
  }
  else if(tmr_x == TMR10)
  {
    crm_periph_reset(CRM_TMR10_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_TMR10_PERIPH_RESET, FALSE);
  }
  else if(tmr_x == TMR11)
  {
    crm_periph_reset(CRM_TMR11_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_TMR11_PERIPH_RESET, FALSE);
  }
}

/**
  * @brief  enable or disable tmr counter
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_counter_enable(tmr_type *tmr_x, confirm_state new_state)
{
  /* tmr counter enable  */
  tmr_x->ctrl1_bit.tmren = new_state;
}

/**
  * @brief  init tmr output default para
  * @param  tmr_output_struct
  *         - to the structure of tmr_output_config_type
  * @retval none
  */
void tmr_output_default_para_init(tmr_output_config_type *tmr_output_struct)
{
  tmr_output_struct->oc_mode = TMR_OUTPUT_CONTROL_OFF;
  tmr_output_struct->oc_idle_state = FALSE;
  tmr_output_struct->occ_idle_state = FALSE;
  tmr_output_struct->oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct->occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
  tmr_output_struct->oc_output_state = FALSE;
  tmr_output_struct->occ_output_state = FALSE;
}

/**
  * @brief  init tmr input default para
  * @param  tmr_input_struct
  *         - to the structure of tmr_input_config_type
  * @retval none
  */
void tmr_input_default_para_init(tmr_input_config_type *tmr_input_struct)
{
  tmr_input_struct->input_channel_select = TMR_SELECT_CHANNEL_1;
  tmr_input_struct->input_polarity_select = TMR_INPUT_RISING_EDGE;
  tmr_input_struct->input_mapped_select = TMR_CC_CHANNEL_MAPPED_DIRECT;
  tmr_input_struct->input_filter_value = 0x0;
}

/**
  * @brief  init tmr brkdt default para
  * @param  tmr_brkdt_struct
  *         - to the structure of tmr_brkdt_config_type
  * @retval none
  */
void tmr_brkdt_default_para_init(tmr_brkdt_config_type *tmr_brkdt_struct)
{
  tmr_brkdt_struct->deadtime = 0x0;
  tmr_brkdt_struct->auto_output_enable = FALSE;
  tmr_brkdt_struct->fcsoen_state = FALSE;
  tmr_brkdt_struct->fcsodis_state = FALSE;
  tmr_brkdt_struct->brk_enable = FALSE;
  tmr_brkdt_struct->brk_polarity = TMR_BRK_INPUT_ACTIVE_LOW;
  tmr_brkdt_struct->wp_level = TMR_WP_OFF;
}

/**
  * @brief  init tmr blanking default para
  * @param  tmr_blk_struct
  *         - to the structure of tmr_blk_config_type
  * @retval none
  */
void tmr_blk_default_para_init(tmr_blk_config_type *tmr_blk_struct)
{
  tmr_blk_struct->input_channel_select = TMR_SELECT_CHANNEL_1;
  tmr_blk_struct->input_blk_state = TMR_BLK_STATE_LOW;
  tmr_blk_struct->blk_source_select = TMR_BLK_SOURCE_0;
  tmr_blk_struct->blk_source_polarity = TMR_BLK_SOURCE_ACTIVE_HIGH;
  tmr_blk_struct->blk_enable = FALSE;
}

/**
  * @brief  init tmr base
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  tmr_pr: 0x0000~0xFFFF
  * @param  tmr_div: 0x0000~0xFFFF
  * @retval none
  */
void tmr_base_init(tmr_type* tmr_x, uint32_t tmr_pr, uint32_t tmr_div)
{
  /* set the pr value */
  tmr_x->pr = tmr_pr;

  /* set the div value */
  tmr_x->div = tmr_div;

  /* trigger the overflow event to immediately reload pr value and div value */
  tmr_x->swevt_bit.ovfswtr = TRUE;
}

/**
  * @brief  set tmr clock source division
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_clock_div
  *         this parameter can be one of the following values:
  *         - TMR_CLOCK_DIV1
  *         - TMR_CLOCK_DIV2
  *         - TMR_CLOCK_DIV4
  * @retval none
  */
void tmr_clock_source_div_set(tmr_type *tmr_x, tmr_clock_division_type tmr_clock_div)
{
  /* set tmr clock source division */
  tmr_x->ctrl1_bit.clkdiv = tmr_clock_div;
}

/**
  * @brief  set tmr counter count direction
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_cnt_dir
  *         this parameter can be one of the following values:
  *         - TMR_COUNT_UP
  *         - TMR_COUNT_DOWN
  *         - TMR_COUNT_TWO_WAY_1
  *         - TMR_COUNT_TWO_WAY_2
  *         - TMR_COUNT_TWO_WAY_3
  * @retval none
  */
void tmr_cnt_dir_set(tmr_type *tmr_x, tmr_count_mode_type tmr_cnt_dir)
{
  /* set the cnt direct */
  tmr_x->ctrl1_bit.cnt_dir = tmr_cnt_dir;
}

/**
  * @brief  get tmr counter count direction
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @retval tmr counter count direction
  *         - 0: TMR_COUNT_UP
  *         - 1: TMR_COUNT_DOWN
  */
uint32_t tmr_cnt_dir_get(tmr_type *tmr_x)
{
  /* get the cnt direct */
  return tmr_x->ctrl1_bit.cnt_dir & 1U;
}

/**
  * @brief  set the repetition counter register(rpr) value
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR9, TMR10, TMR11
  * @param  tmr_rpr_value (for tmr1 0x0000~0xFFFF, for tmr9, tmr10
  *         and tmr11 0x00~0xFF)
  * @retval none
  */
void tmr_repetition_counter_set(tmr_type *tmr_x, uint16_t tmr_rpr_value)
{
  /* set the repetition counter value */
  if(tmr_x == TMR1 || tmr_x == TMR9 || tmr_x == TMR10 || tmr_x == TMR11)
  {
    tmr_x->rpr_bit.rpr = tmr_rpr_value;
  }
}

/**
  * @brief  set tmr counter value
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  tmr_cnt_value: 0x0000~0xFFFF
  * @retval none
  */
void tmr_counter_value_set(tmr_type *tmr_x, uint32_t tmr_cnt_value)
{
  /* set the tmr counter value */
  tmr_x->cval = tmr_cnt_value;
}

/**
  * @brief  get tmr counter value
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @retval tmr counter value
  */
uint32_t tmr_counter_value_get(tmr_type *tmr_x)
{
  return (tmr_x->cval & 0xFFFF);
}

/**
  * @brief  set tmr div value
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  tmr_div_value: 0x0000~0xFFFF
  * @retval none
  */
void tmr_div_value_set(tmr_type *tmr_x, uint32_t tmr_div_value)
{
  /* set the tmr div value */
  tmr_x->div = tmr_div_value;
}

/**
  * @brief  get tmr div value
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @retval tmr div value
  */
uint32_t tmr_div_value_get(tmr_type *tmr_x)
{
  return tmr_x->div;
}

/**
  * @brief  config tmr output channel
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_4
  *         - TMR_SELECT_CHANNEL_5
  *         - TMR_SELECT_CHANNEL_6
  * @param  tmr_output_struct
  *         - to the structure of tmr_output_config_type
  * @retval none
  */
void tmr_output_channel_config(tmr_type *tmr_x, tmr_channel_select_type tmr_channel, \
                               tmr_output_config_type *tmr_output_struct)
{
  tmr_channel_select_type channel;
  uint8_t cxoctrl_bit2_0 = tmr_output_struct->oc_mode&7U;
  uint8_t cxoctrl_bit3 = tmr_output_struct->oc_mode>>3U;

  /* set channel output mode */
  channel = tmr_channel;

  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->ctrl2_bit.c1ios = tmr_output_struct->oc_idle_state;
      tmr_x->ctrl2_bit.c1cios = tmr_output_struct->occ_idle_state;
      tmr_x->cm1_output_bit.c1octrl = cxoctrl_bit2_0;
      tmr_x->cm1_output_bit.c1octrl_3 = cxoctrl_bit3;    
      tmr_x->cctrl_bit.c1p = tmr_output_struct->oc_polarity;
      tmr_x->cctrl_bit.c1cp = tmr_output_struct->occ_polarity;
      tmr_x->cctrl_bit.c1en = tmr_output_struct->oc_output_state;
      tmr_x->cctrl_bit.c1cen = tmr_output_struct->occ_output_state;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->ctrl2_bit.c2ios = tmr_output_struct->oc_idle_state;
      tmr_x->ctrl2_bit.c2cios = tmr_output_struct->occ_idle_state;
      tmr_x->cm1_output_bit.c2octrl = cxoctrl_bit2_0;
      tmr_x->cm1_output_bit.c2octrl_3 = cxoctrl_bit3;
      tmr_x->cctrl_bit.c2p = tmr_output_struct->oc_polarity;
      tmr_x->cctrl_bit.c2cp = tmr_output_struct->occ_polarity;
      tmr_x->cctrl_bit.c2en = tmr_output_struct->oc_output_state;
      tmr_x->cctrl_bit.c2cen = tmr_output_struct->occ_output_state;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->ctrl2_bit.c3ios = tmr_output_struct->oc_idle_state;
      tmr_x->ctrl2_bit.c3cios = tmr_output_struct->occ_idle_state;
      tmr_x->cm2_output_bit.c3octrl = cxoctrl_bit2_0;
      tmr_x->cm2_output_bit.c3octrl_3 = cxoctrl_bit3;
      tmr_x->cctrl_bit.c3p = tmr_output_struct->oc_polarity;
      tmr_x->cctrl_bit.c3cp = tmr_output_struct->occ_polarity;
      tmr_x->cctrl_bit.c3en = tmr_output_struct->oc_output_state;
      tmr_x->cctrl_bit.c3cen = tmr_output_struct->occ_output_state;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->ctrl2_bit.c4ios = tmr_output_struct->oc_idle_state;
      tmr_x->cm2_output_bit.c4octrl = cxoctrl_bit2_0;
      tmr_x->cm2_output_bit.c4octrl_3 = cxoctrl_bit3;
      tmr_x->cctrl_bit.c4p = tmr_output_struct->oc_polarity;
      tmr_x->cctrl_bit.c4cp = tmr_output_struct->occ_polarity;
      tmr_x->cctrl_bit.c4en = tmr_output_struct->oc_output_state;
      tmr_x->cctrl_bit.c4cen = tmr_output_struct->occ_output_state;
      break;

    case TMR_SELECT_CHANNEL_5:
      tmr_x->ctrl2_bit.c5ios = tmr_output_struct->oc_idle_state;
      tmr_x->cm3_output_bit.c5octrl = cxoctrl_bit2_0;
      tmr_x->cm3_output_bit.c5octrl_3 = cxoctrl_bit3;
      tmr_x->cctrl_bit.c5p = tmr_output_struct->oc_polarity;
      tmr_x->cctrl_bit.c5en = tmr_output_struct->oc_output_state;
      break;

    case TMR_SELECT_CHANNEL_6:
      tmr_x->ctrl2_bit.c6ios = tmr_output_struct->oc_idle_state;
      tmr_x->cm3_output_bit.c6octrl = cxoctrl_bit2_0;
      tmr_x->cm3_output_bit.c6octrl_3 = cxoctrl_bit3;
      tmr_x->cctrl_bit.c6p = tmr_output_struct->oc_polarity;
      tmr_x->cctrl_bit.c6en = tmr_output_struct->oc_output_state;
      break;

    default:
      break;
  }
}

/**
  * @brief  select tmr output channel mode
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_4
  *         - TMR_SELECT_CHANNEL_5
  * @param  oc_mode
  *         this parameter can be one of the following values:
  *         - TMR_OUTPUT_CONTROL_OFF
  *         - TMR_OUTPUT_CONTROL_HIGH
  *         - TMR_OUTPUT_CONTROL_LOW
  *         - TMR_OUTPUT_CONTROL_SWITCH
  *         - TMR_OUTPUT_CONTROL_FORCE_HIGH
  *         - TMR_OUTPUT_CONTROL_FORCE_LOW
  *         - TMR_OUTPUT_CONTROL_PWM_MODE_A
  *         - TMR_OUTPUT_CONTROL_PWM_MODE_B
  *         - TMR_OUTPUT_CONTROL_RETRIG_OCM_A    
  *         - TMR_OUTPUT_CONTROL_RETRIG_OCM_B    
  *         - TMR_OUTPUT_CONTROL_COMBINED_PWM_A  
  *         - TMR_OUTPUT_CONTROL_COMBINED_PWM_B  
  *         - TMR_OUTPUT_CONTROL_ASYMMETRIC_PWM_A
  *         - TMR_OUTPUT_CONTROL_ASYMMETRIC_PWM_B
  * @retval none
  */
void tmr_output_channel_mode_select(tmr_type *tmr_x, tmr_channel_select_type tmr_channel, \
                                    tmr_output_control_mode_type oc_mode)
{
  uint16_t channel;
  uint8_t cxoctrl_bit2_0 = oc_mode&7U;
  uint8_t cxoctrl_bit3 = oc_mode>>3U;

  channel = tmr_channel;

  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->cm1_output_bit.c1octrl = cxoctrl_bit2_0;
      tmr_x->cm1_output_bit.c1octrl_3 = cxoctrl_bit3;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->cm1_output_bit.c2octrl = cxoctrl_bit2_0;
      tmr_x->cm1_output_bit.c2octrl_3 = cxoctrl_bit3;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->cm2_output_bit.c3octrl = cxoctrl_bit2_0;
      tmr_x->cm2_output_bit.c3octrl_3 = cxoctrl_bit3;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->cm2_output_bit.c4octrl = cxoctrl_bit2_0;
      tmr_x->cm2_output_bit.c4octrl_3 = cxoctrl_bit3;
      break;

    case TMR_SELECT_CHANNEL_5:
      tmr_x->cm3_output_bit.c5octrl = cxoctrl_bit2_0;
      tmr_x->cm3_output_bit.c5octrl_3 = cxoctrl_bit3;
      break;

    case TMR_SELECT_CHANNEL_6:
      tmr_x->cm3_output_bit.c6octrl = cxoctrl_bit2_0;
      tmr_x->cm3_output_bit.c6octrl_3 = cxoctrl_bit3;
      break;

    default:
      break;
  }
}
/**
  * @brief  set tmr period value
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  tmr_pr_value: timer period register value of counter
  *         (0x0000~0xFFFF)
  * @retval none
  */
void tmr_period_value_set(tmr_type *tmr_x, uint32_t tmr_pr_value)
{
  /* set tmr period value */
  tmr_x->pr = tmr_pr_value;
}

/**
  * @brief  get tmr period value
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @retval timer period register value of counter
  *         (0x0000~0xFFFF)
  */
uint32_t tmr_period_value_get(tmr_type *tmr_x)
{
  return tmr_x->pr;
}

/**
  * @brief  set tmr channel value
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_4
  *         - TMR_SELECT_CHANNEL_5
  *         - TMR_SELECT_CHANNEL_6
  *         - TMR_SELECT_CHANNEL_1A
  *         - TMR_SELECT_CHANNEL_2A
  *         - TMR_SELECT_CHANNEL_3A
  *         - TMR_SELECT_CHANNEL_4A
  * @param  tmr_channel_value: 0x0000~0xFFFF
  * @retval none
  */
void tmr_channel_value_set(tmr_type *tmr_x, tmr_channel_select_type tmr_channel, \
                           uint32_t tmr_channel_value)
{
  uint16_t channel;

  channel = tmr_channel;

  /* set tmr channel value */
  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->c1dt = tmr_channel_value;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->c2dt = tmr_channel_value;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->c3dt = tmr_channel_value;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->c4dt = tmr_channel_value;
      break;

    case TMR_SELECT_CHANNEL_5:
      tmr_x->c5dt_bit.c5dt = tmr_channel_value;
      break;

    case TMR_SELECT_CHANNEL_6:
      tmr_x->c6dt = tmr_channel_value;
      break;

    case TMR_SELECT_CHANNEL_1A:
      tmr_x->c1adt = tmr_channel_value;
      break;

    case TMR_SELECT_CHANNEL_2A:
      tmr_x->c2adt = tmr_channel_value;
      break;

    case TMR_SELECT_CHANNEL_3A:
      tmr_x->c3adt = tmr_channel_value;
      break;

    case TMR_SELECT_CHANNEL_4A:
      tmr_x->c4adt = tmr_channel_value;
      break;
    
    default:
      break;
  }
}

/**
  * @brief  get tmr channel value
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_4
  *         - TMR_SELECT_CHANNEL_5
  *         - TMR_SELECT_CHANNEL_6
  *         - TMR_SELECT_CHANNEL_1A
  *         - TMR_SELECT_CHANNEL_2A
  *         - TMR_SELECT_CHANNEL_3A
  *         - TMR_SELECT_CHANNEL_4A
  * @retval tmr channel value
  */
uint32_t tmr_channel_value_get(tmr_type *tmr_x, tmr_channel_select_type tmr_channel)
{
  uint32_t cc_value_get = 0;
  uint16_t channel;

  channel = tmr_channel;

  /* get tmr channel value */
  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      cc_value_get = tmr_x->c1dt;
      break;

    case TMR_SELECT_CHANNEL_2:
      cc_value_get = tmr_x->c2dt;
      break;

    case TMR_SELECT_CHANNEL_3:
      cc_value_get = tmr_x->c3dt;
      break;

    case TMR_SELECT_CHANNEL_4:
      cc_value_get = tmr_x->c4dt;
      break;

    case TMR_SELECT_CHANNEL_5:
      cc_value_get = tmr_x->c5dt;
      break;

    case TMR_SELECT_CHANNEL_6:
      cc_value_get = tmr_x->c6dt;
      break;

    case TMR_SELECT_CHANNEL_1A:
      cc_value_get = tmr_x->c1adt;
      break;

    case TMR_SELECT_CHANNEL_2A:
      cc_value_get = tmr_x->c2adt;
      break;

    case TMR_SELECT_CHANNEL_3A:
      cc_value_get = tmr_x->c3adt;
      break;

    case TMR_SELECT_CHANNEL_4A:
      cc_value_get = tmr_x->c4adt;
      break;

    default:
      break;
  }

  return cc_value_get;
}

/**
  * @brief  set tmr period buffer
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_period_buffer_enable(tmr_type *tmr_x, confirm_state new_state)
{
  /* tmr period buffer set */
  tmr_x->ctrl1_bit.prben = new_state;
}

/**
  * @brief  set tmr output channel buffer
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_4
  *         - TMR_SELECT_CHANNEL_5
  *         - TMR_SELECT_CHANNEL_6
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_output_channel_buffer_enable(tmr_type *tmr_x, tmr_channel_select_type tmr_channel, \
                                   confirm_state new_state)
{
  uint16_t channel;

  channel = tmr_channel;

  /* get tmr channel value */
  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->cm1_output_bit.c1oben = new_state;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->cm1_output_bit.c2oben = new_state;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->cm2_output_bit.c3oben = new_state;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->cm2_output_bit.c4oben = new_state;
      break;

    case TMR_SELECT_CHANNEL_5:
      tmr_x->cm3_output_bit.c5oben = new_state;
      break;

    case TMR_SELECT_CHANNEL_6:
      tmr_x->cm3_output_bit.c6oben = new_state;
      break;

    default:
      break;
  }
}

/**
  * @brief  set tmr output channel immediately
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_4
  *         - TMR_SELECT_CHANNEL_5
  *         - TMR_SELECT_CHANNEL_6
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_output_channel_immediately_set(tmr_type *tmr_x, tmr_channel_select_type tmr_channel, \
                                        confirm_state new_state)
{
  uint16_t channel;

  channel = tmr_channel;

  /* get tmr channel value */
  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->cm1_output_bit.c1oien = new_state;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->cm1_output_bit.c2oien = new_state;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->cm2_output_bit.c3oien = new_state;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->cm2_output_bit.c4oien = new_state;
      break;

    case TMR_SELECT_CHANNEL_5:
      tmr_x->cm3_output_bit.c5oien = new_state;
      break;

    case TMR_SELECT_CHANNEL_6:
      tmr_x->cm3_output_bit.c6oien = new_state;
      break;

    default:
      break;
  }
}

/**
  * @brief  set tmr output channel switch
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_4
  *         - TMR_SELECT_CHANNEL_5
  *         - TMR_SELECT_CHANNEL_6
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_output_channel_switch_set(tmr_type *tmr_x, tmr_channel_select_type tmr_channel, \
                                   confirm_state new_state)
{
  uint16_t channel;

  channel = tmr_channel;

  /* get tmr channel value */
  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->cm1_output_bit.c1osen = new_state;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->cm1_output_bit.c2osen = new_state;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->cm2_output_bit.c3osen = new_state;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->cm2_output_bit.c4osen = new_state;
      break;

    case TMR_SELECT_CHANNEL_5:
      tmr_x->cm3_output_bit.c5osen = new_state;
      break;

    case TMR_SELECT_CHANNEL_6:
      tmr_x->cm3_output_bit.c6osen = new_state;
      break;

    default:
      break;
  }
}

/**
  * @brief  enable or disable tmr one cycle mode
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_one_cycle_mode_enable(tmr_type *tmr_x, confirm_state new_state)
{
  /* tmr one cycle mode enable */
  tmr_x->ctrl1_bit.ocmen = new_state;
}

/**
  * @brief  select tmr the overflow event sources
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_overflow_request_source_set(tmr_type *tmr_x, confirm_state new_state)
{
  tmr_x->ctrl1_bit.ovfs = new_state;
}

/**
  * @brief  enable or disable tmr overflow event generation
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_overflow_event_disable(tmr_type *tmr_x, confirm_state new_state)
{
  tmr_x->ctrl1_bit.ovfen = new_state;
}

/**
  * @brief  init tmr input channel
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  input_struct
  *         - to the structure of tmr_input_config_type
  * @param  divider_factor
  *         this parameter can be one of the following values:
  *         - TMR_CHANNEL_INPUT_DIV_1
  *         - TMR_CHANNEL_INPUT_DIV_2
  *         - TMR_CHANNEL_INPUT_DIV_4
  *         - TMR_CHANNEL_INPUT_DIV_8
  * @retval none
  */
void tmr_input_channel_init(tmr_type *tmr_x, tmr_input_config_type *input_struct, \
                            tmr_channel_input_divider_type divider_factor)
{
  uint16_t channel = 0;

  /* get channel selected */
  channel = input_struct->input_channel_select;

  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->cctrl_bit.c1p        = (uint32_t)input_struct->input_polarity_select;
      tmr_x->cctrl_bit.c1cp       = (input_struct->input_polarity_select & 0x2) >> 1;
      tmr_x->cm1_input_bit.c1c    = input_struct->input_mapped_select;
      tmr_x->cm1_input_bit.c1df   = input_struct->input_filter_value;
      tmr_x->cm1_input_bit.c1idiv = divider_factor;
      tmr_x->cctrl_bit.c1en       = TRUE;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->cctrl_bit.c2p        = (uint32_t)input_struct->input_polarity_select;
      tmr_x->cctrl_bit.c2cp       = (input_struct->input_polarity_select & 0x2) >> 1;
      tmr_x->cm1_input_bit.c2c    = input_struct->input_mapped_select;
      tmr_x->cm1_input_bit.c2df   = input_struct->input_filter_value;
      tmr_x->cm1_input_bit.c2idiv = divider_factor;
      tmr_x->cctrl_bit.c2en       = TRUE;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->cctrl_bit.c3p        = (uint32_t)input_struct->input_polarity_select;
      tmr_x->cctrl_bit.c3cp       = (input_struct->input_polarity_select & 0x2) >> 1;
      tmr_x->cm2_input_bit.c3c    = input_struct->input_mapped_select;
      tmr_x->cm2_input_bit.c3df   = input_struct->input_filter_value;
      tmr_x->cm2_input_bit.c3idiv = divider_factor;
      tmr_x->cctrl_bit.c3en       = TRUE;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->cctrl_bit.c4p        = (uint32_t)input_struct->input_polarity_select;
      tmr_x->cctrl_bit.c4cp       = (input_struct->input_polarity_select & 0x2) >> 1;
      tmr_x->cm2_input_bit.c4c    = input_struct->input_mapped_select;
      tmr_x->cm2_input_bit.c4df   = input_struct->input_filter_value;
      tmr_x->cm2_input_bit.c4idiv = divider_factor;
      tmr_x->cctrl_bit.c4en       = TRUE;
      break;

    default:
      break;
  }
}

/**
  * @brief  init tmr input channel blanking
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR3, TMR4
  * @param  input_blk_struct
  *         - to the structure of tmr_blk_config_type
  * @retval none
  */
void tmr_input_channel_blk_config(tmr_type *tmr_x, tmr_blk_config_type *input_blk_struct)
{
  uint16_t channel = 0;

  /* get channel selected */
  channel = input_blk_struct->input_channel_select;

  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->blkctrl_bit.ch1blkss = input_blk_struct->blk_source_select;
      tmr_x->blkctrl_bit.ch1blkp = input_blk_struct->blk_source_polarity;
      tmr_x->blkctrl_bit.ch1blkst = input_blk_struct->input_blk_state;
      tmr_x->blkctrl_bit.ch1blken = input_blk_struct->blk_enable;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->blkctrl_bit.ch2blkss = input_blk_struct->blk_source_select;
      tmr_x->blkctrl_bit.ch2blkp = input_blk_struct->blk_source_polarity;
      tmr_x->blkctrl_bit.ch2blkst = input_blk_struct->input_blk_state;      
      tmr_x->blkctrl_bit.ch2blken = input_blk_struct->blk_enable;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->blkctrl_bit.ch3blkss = input_blk_struct->blk_source_select;
      tmr_x->blkctrl_bit.ch3blkp = input_blk_struct->blk_source_polarity;
      tmr_x->blkctrl_bit.ch3blkst = input_blk_struct->input_blk_state;      
      tmr_x->blkctrl_bit.ch3blken = input_blk_struct->blk_enable;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->blkctrl_bit.ch4blkss = input_blk_struct->blk_source_select;
      tmr_x->blkctrl_bit.ch4blkp = input_blk_struct->blk_source_polarity;
      tmr_x->blkctrl_bit.ch4blkst = input_blk_struct->input_blk_state;     
      tmr_x->blkctrl_bit.ch4blken = input_blk_struct->blk_enable;
      break;

    default:
      break;
  }
}

/**
  * @brief  tmr channel enable
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_1C
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_2C
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_3C
  *         - TMR_SELECT_CHANNEL_4
  *         - TMR_SELECT_CHANNEL_4C
  *         - TMR_SELECT_CHANNEL_5
  *         - TMR_SELECT_CHANNEL_6
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_channel_enable(tmr_type *tmr_x, tmr_channel_select_type tmr_channel, confirm_state new_state)
{
  uint16_t channel;

  channel = tmr_channel;

  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->cctrl_bit.c1en         = new_state;
      break;

    case TMR_SELECT_CHANNEL_1C:
      tmr_x->cctrl_bit.c1cen        = new_state;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->cctrl_bit.c2en         = new_state;
      break;

    case TMR_SELECT_CHANNEL_2C:
      tmr_x->cctrl_bit.c2cen        = new_state;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->cctrl_bit.c3en         = new_state;
      break;

    case TMR_SELECT_CHANNEL_3C:
      tmr_x->cctrl_bit.c3cen        = new_state;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->cctrl_bit.c4en         = new_state;
      break;

    case TMR_SELECT_CHANNEL_4C:
      tmr_x->cctrl_bit.c4cen        = new_state;
      break;

    case TMR_SELECT_CHANNEL_5:
      tmr_x->cctrl_bit.c5en         = new_state;
      break;

    case TMR_SELECT_CHANNEL_6:
      tmr_x->cctrl_bit.c6en         = new_state;
      break;

    default:
      break;
  }
}

/**
  * @brief  set tmr input channel filter
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_4
  * @param  filter_value (0x0~0xf)
  * @retval none
  */
void tmr_input_channel_filter_set(tmr_type *tmr_x, tmr_channel_select_type tmr_channel, \
                                  uint16_t filter_value)
{
  uint16_t channel;

  channel = tmr_channel;

  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->cm1_input_bit.c1df = filter_value;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->cm1_input_bit.c2df = filter_value;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->cm2_input_bit.c3df = filter_value;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->cm2_input_bit.c4df = filter_value;
      break;

    default:
      break;
  }
}

/**
  * @brief  config tmr pwm input
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  input_struct
  *         - to the structure of tmr_input_config_type
  * @param  divider_factor
  *         this parameter can be one of the following values:
  *         - TMR_CHANNEL_INPUT_DIV_1
  *         - TMR_CHANNEL_INPUT_DIV_2
  *         - TMR_CHANNEL_INPUT_DIV_4
  *         - TMR_CHANNEL_INPUT_DIV_8
  * @retval none
  */
void tmr_pwm_input_config(tmr_type *tmr_x, tmr_input_config_type *input_struct, \
                          tmr_channel_input_divider_type divider_factor)
{
  uint16_t channel = 0;

  /* get channel selected */
  channel = input_struct->input_channel_select;

  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      if(input_struct->input_polarity_select == TMR_INPUT_RISING_EDGE)
      {
        /* set channel polarity */
        tmr_x->cctrl_bit.c1p          = TMR_INPUT_RISING_EDGE;
        tmr_x->cctrl_bit.c2p          = TMR_INPUT_FALLING_EDGE;
      }
      else if(input_struct->input_polarity_select == TMR_INPUT_FALLING_EDGE)
      {
        /* set channel polarity */
        tmr_x->cctrl_bit.c1p          = TMR_INPUT_FALLING_EDGE;
        tmr_x->cctrl_bit.c2p          = TMR_INPUT_RISING_EDGE;
      }

      if(input_struct->input_mapped_select == TMR_CC_CHANNEL_MAPPED_DIRECT)
      {
        /* ic1 is mapped on ti1 */
        tmr_x->cm1_input_bit.c1c = TMR_CC_CHANNEL_MAPPED_DIRECT;

        /* ic1 is mapped on ti2 */
        tmr_x->cm1_input_bit.c2c = TMR_CC_CHANNEL_MAPPED_INDIRECT;
      }
      else if(input_struct->input_mapped_select == TMR_CC_CHANNEL_MAPPED_INDIRECT)
      {
        /* ic1 is mapped on ti1 */
        tmr_x->cm1_input_bit.c1c = TMR_CC_CHANNEL_MAPPED_INDIRECT;

        /* ic1 is mapped on ti2 */
        tmr_x->cm1_input_bit.c2c = TMR_CC_CHANNEL_MAPPED_DIRECT;
      }

      /* set input ch1 and ch2 filter value*/
      tmr_x->cm1_input_bit.c1df = input_struct->input_filter_value;
      tmr_x->cm1_input_bit.c2df = input_struct->input_filter_value;

      /*set input ch1 and ch2 divider value*/
      tmr_x->cm1_input_bit.c1idiv = divider_factor;
      tmr_x->cm1_input_bit.c2idiv = divider_factor;

      tmr_x->cctrl_bit.c1en = TRUE;
      tmr_x->cctrl_bit.c2en = TRUE;
      break;

    case TMR_SELECT_CHANNEL_2:
      if(input_struct->input_polarity_select == TMR_INPUT_RISING_EDGE)
      {
        /* set channel polarity */
        tmr_x->cctrl_bit.c2p          = TMR_INPUT_RISING_EDGE;
        tmr_x->cctrl_bit.c1p          = TMR_INPUT_FALLING_EDGE;
      }
      else if(input_struct->input_polarity_select == TMR_INPUT_FALLING_EDGE)
      {
        /* set channel polarity */
        tmr_x->cctrl_bit.c2p          = TMR_INPUT_FALLING_EDGE;
        tmr_x->cctrl_bit.c1p          = TMR_INPUT_RISING_EDGE;
      }

      if(input_struct->input_mapped_select == TMR_CC_CHANNEL_MAPPED_DIRECT)
      {
        /* set mapped direct */
        tmr_x->cm1_input_bit.c2c = TMR_CC_CHANNEL_MAPPED_DIRECT;
        tmr_x->cm1_input_bit.c1c = TMR_CC_CHANNEL_MAPPED_INDIRECT;
      }
      else if(input_struct->input_mapped_select == TMR_CC_CHANNEL_MAPPED_INDIRECT)
      {
        /* set mapped direct */
        tmr_x->cm1_input_bit.c2c = TMR_CC_CHANNEL_MAPPED_INDIRECT;
        tmr_x->cm1_input_bit.c1c = TMR_CC_CHANNEL_MAPPED_DIRECT;
      }

      /* set input ch1 and ch2 filter value*/
      tmr_x->cm1_input_bit.c1df = input_struct->input_filter_value;
      tmr_x->cm1_input_bit.c2df = input_struct->input_filter_value;

      /*set input ch1 and ch2 divider value*/
      tmr_x->cm1_input_bit.c1idiv = divider_factor;
      tmr_x->cm1_input_bit.c2idiv = divider_factor;

      tmr_x->cctrl_bit.c1en = TRUE;
      tmr_x->cctrl_bit.c2en = TRUE;
      break;

    default:
      break;
  }
}

/**
  * @brief  select tmr channel1 input
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4
  * @param  ti1_connect
  *         this parameter can be one of the following values:
  *         - TMR_CHANEL1_CONNECTED_C1IRAW
  *         - TMR_CHANEL1_2_3_CONNECTED_C1IRAW_XOR
  * @retval none
  */
void tmr_channel1_input_select(tmr_type *tmr_x, tmr_channel1_input_connected_type ti1_connect)
{
  tmr_x->ctrl2_bit.c1insel = ti1_connect;
}

/**
  * @brief  set tmr input channel divider
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_4
  * @param  divider_factor
  *         this parameter can be one of the following values:
  *         - TMR_CHANNEL_INPUT_DIV_1
  *         - TMR_CHANNEL_INPUT_DIV_2
  *         - TMR_CHANNEL_INPUT_DIV_4
  *         - TMR_CHANNEL_INPUT_DIV_8
  * @retval none
  */
void tmr_input_channel_divider_set(tmr_type *tmr_x, tmr_channel_select_type tmr_channel, \
                                   tmr_channel_input_divider_type divider_factor)
{
  uint16_t channel;

  channel = tmr_channel;

  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->cm1_input_bit.c1idiv = divider_factor;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->cm1_input_bit.c2idiv = divider_factor;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->cm2_input_bit.c3idiv = divider_factor;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->cm2_input_bit.c4idiv = divider_factor;
      break;

    default:
      break;
  }
}

/**
  * @brief  select tmr primary mode
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9
  * @param  primary_mode
  *         this parameter can be one of the following values:
  *         - TMR_PRIMARY_SEL_RESET
  *         - TMR_PRIMARY_SEL_ENABLE
  *         - TMR_PRIMARY_SEL_OVERFLOW
  *         - TMR_PRIMARY_SEL_COMPARE
  *         - TMR_PRIMARY_SEL_C1ORAW
  *         - TMR_PRIMARY_SEL_C2ORAW
  *         - TMR_PRIMARY_SEL_C3ORAW
  *         - TMR_PRIMARY_SEL_C4ORAW
  * @retval none
  */
void tmr_primary_mode_select(tmr_type *tmr_x, tmr_primary_select_type primary_mode)
{
  uint8_t pm = primary_mode&7U;
  tmr_x->ctrl2_bit.ptos = pm;
}

/**
  * @brief  select tmr subordinate mode
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9
  * @param  sub_mode
  *         this parameter can be one of the following values:
  *         - TMR_SUB_MODE_DIABLE
  *         - TMR_SUB_ENCODER_MODE_A
  *         - TMR_SUB_ENCODER_MODE_B
  *         - TMR_SUB_ENCODER_MODE_C
  *         - TMR_SUB_RESET_MODE
  *         - TMR_SUB_HANG_MODE
  *         - TMR_SUB_TRIGGER_MODE
  *         - TMR_SUB_EXTERNAL_CLOCK_MODE_A
  *         - TMR_SUB_RESET_TRIGGER_MODE
  * @retval none
  */
void tmr_sub_mode_select(tmr_type *tmr_x, tmr_sub_mode_select_type sub_mode)
{
  uint8_t smsel_bit2_0 = sub_mode&7U;
  uint8_t smsel_bit3 = sub_mode>>3U;
  tmr_x->stctrl_bit.smsel = smsel_bit2_0;
  tmr_x->stctrl_bit.smsel_3 = smsel_bit3;
}

/**
  * @brief  select tmr channel dma
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9
  * @param  cc_dma_select
  *         this parameter can be one of the following values:
  *         - TMR_DMA_REQUEST_BY_CHANNEL
  *         - TMR_DMA_REQUEST_BY_OVERFLOW
  * @retval none
  */
void tmr_channel_dma_select(tmr_type *tmr_x, tmr_dma_request_source_type cc_dma_select)
{
  tmr_x->ctrl2_bit.drs = cc_dma_select;
}

/**
  * @brief  select tmr hall
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR9, TMR10, TMR11
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_hall_select(tmr_type *tmr_x,  confirm_state new_state)
{
  tmr_x->ctrl2_bit.ccfs = new_state;
}

/**
  * @brief  select tmr channel buffer
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR9, TMR10, TMR11
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_channel_buffer_enable(tmr_type *tmr_x, confirm_state new_state)
{
  tmr_x->ctrl2_bit.cbctrl = new_state;
}

/**
  * @brief  select tmr trgout2
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_trgout2_enable(tmr_type *tmr_x, confirm_state new_state)
{
  tmr_x->ctrl2_bit.trgout2en = new_state;
}

/**
  * @brief  select tmr sub-trigger
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9
  * @param  trigger_select
  *         this parameter can be one of the following values:
  *         - TMR_SUB_INPUT_SEL_IS0
  *         - TMR_SUB_INPUT_SEL_IS1
  *         - TMR_SUB_INPUT_SEL_IS2
  *         - TMR_SUB_INPUT_SEL_IS3
  *         - TMR_SUB_INPUT_SEL_C1INC
  *         - TMR_SUB_INPUT_SEL_C1DF1
  *         - TMR_SUB_INPUT_SEL_C2DF2
  *         - TMR_SUB_INPUT_SEL_EXTIN
  * @retval none
  */
void tmr_trigger_input_select(tmr_type *tmr_x, sub_tmr_input_sel_type trigger_select)
{
  tmr_x->stctrl_bit.stis = trigger_select;
}

/**
  * @brief  set tmr subordinate synchronization mode
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_sub_sync_mode_set(tmr_type *tmr_x, confirm_state new_state)
{
  tmr_x->stctrl_bit.sts = new_state;
}

/**
  * @brief  enable or disable tmr dma request
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  dma_request
  *         this parameter can be one of the following values:
  *         - TMR_OVERFLOW_DMA_REQUEST
  *         - TMR_C1_DMA_REQUEST
  *         - TMR_C2_DMA_REQUEST
  *         - TMR_C3_DMA_REQUEST
  *         - TMR_C4_DMA_REQUEST
  *         - TMR_HALL_DMA_REQUEST
  *         - TMR_TRIGGER_DMA_REQUEST
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_dma_request_enable(tmr_type *tmr_x, tmr_dma_request_type dma_request, confirm_state new_state)
{
  if(new_state == TRUE)
  {
    tmr_x->iden |= dma_request;
  }
  else if(new_state == FALSE)
  {
    tmr_x->iden &= ~dma_request;
  }
}

/**
  * @brief  enable or disable tmr interrupt
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  tmr_interrupt
  *         this parameter can be one of the following values:
  *         - TMR_OVF_INT
  *         - TMR_C1_INT
  *         - TMR_C2_INT
  *         - TMR_C3_INT
  *         - TMR_C4_INT
  *         - TMR_HALL_INT
  *         - TMR_TRIGGER_INT
  *         - TMR_BRK_INT
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_interrupt_enable(tmr_type *tmr_x, uint32_t tmr_interrupt, confirm_state new_state)
{
  if(new_state == TRUE)
  {
    tmr_x->iden |= tmr_interrupt;
  }
  else if(new_state == FALSE)
  {
    tmr_x->iden &= ~tmr_interrupt;
  }
}

/**
  * @brief  get tmr interrupt flag
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR2, TMR3, TMR6, TMR7, TMR13, TMR14, TMR15,
  *         TMR16, TMR17
  * @param  tmr_flag
  *         this parameter can be one of the following values:
  *         - TMR_OVF_FLAG
  *         - TMR_C1_FLAG
  *         - TMR_C2_FLAG
  *         - TMR_C3_FLAG
  *         - TMR_C4_FLAG
  *         - TMR_HALL_FLAG
  *         - TMR_TRIGGER_FLAG
  *         - TMR_BRK_FLAG
  * @retval state of tmr interrupt flag
  */
flag_status tmr_interrupt_flag_get(tmr_type *tmr_x, uint32_t tmr_flag)
{
  flag_status status = RESET;

  if((tmr_x->ists & tmr_flag) && (tmr_x->iden & tmr_flag))
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/**
  * @brief  get tmr flag
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  tmr_flag
  *         this parameter can be one of the following values:
  *         - TMR_OVF_FLAG
  *         - TMR_C1_FLAG
  *         - TMR_C2_FLAG
  *         - TMR_C3_FLAG
  *         - TMR_C4_FLAG
  *         - TMR_HALL_FLAG
  *         - TMR_TRIGGER_FLAG
  *         - TMR_BRK_FLAG
  *         - TMR_BRK2_FLAG
  *         - TMR_C1_RECAPTURE_FLAG
  *         - TMR_C2_RECAPTURE_FLAG
  *         - TMR_C3_RECAPTURE_FLAG
  *         - TMR_C4_RECAPTURE_FLAG
  *         - TMR_SYS_BRK_FLAG
  *         - TMR_C5_FLAG
  *         - TMR_C6_FLAG
  * @retval state of tmr flag
  */
flag_status tmr_flag_get(tmr_type *tmr_x, uint32_t tmr_flag)
{
  flag_status status = RESET;

  if((tmr_x->ists & tmr_flag) != RESET)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/**
  * @brief  clear tmr flag
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  tmr_flag
  *         this parameter can be any combination of the following values:
  *         - TMR_OVF_FLAG
  *         - TMR_C1_FLAG
  *         - TMR_C2_FLAG
  *         - TMR_C3_FLAG
  *         - TMR_C4_FLAG
  *         - TMR_HALL_FLAG
  *         - TMR_TRIGGER_FLAG
  *         - TMR_BRK_FLAG
  *         - TMR_BRK2_FLAG
  *         - TMR_C1_RECAPTURE_FLAG
  *         - TMR_C2_RECAPTURE_FLAG
  *         - TMR_C3_RECAPTURE_FLAG
  *         - TMR_C4_RECAPTURE_FLAG
  *         - TMR_SYS_BRK_FLAG
  *         - TMR_C5_FLAG
  *         - TMR_C6_FLAG
  * @retval none
  */
void tmr_flag_clear(tmr_type *tmr_x, uint32_t tmr_flag)
{
  tmr_x->ists = ~tmr_flag;
}

/**
  * @brief  generate tmr event
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  tmr_event
  *         this parameter can be one of the following values:
  *         - TMR_OVERFLOW_SWTRIG
  *         - TMR_C1_SWTRIG
  *         - TMR_C2_SWTRIG
  *         - TMR_C3_SWTRIG
  *         - TMR_C4_SWTRIG
  *         - TMR_HALL_SWTRIG
  *         - TMR_TRIGGER_SWTRIG
  *         - TMR_BRK_SWTRIG
  *         - TMR_BRK2_SWTRIG
  * @retval none
  */
void tmr_event_sw_trigger(tmr_type *tmr_x, tmr_event_trigger_type tmr_event)
{
  tmr_x->swevt |= tmr_event;
}

/**
  * @brief  tmr output enable(oen),this function is important for advtm output enable
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR9, TMR10, TMR11
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_output_enable(tmr_type *tmr_x, confirm_state new_state)
{
  tmr_x->brk_bit.oen = new_state;
}

/**
  * @brief  set tmr select internal clock
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9
  * @retval none
  */
void tmr_internal_clock_set(tmr_type *tmr_x)
{
  tmr_x->stctrl_bit.smsel = TMR_SUB_MODE_DIABLE;
}

/**
  * @brief  set tmr output channel polarity
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_4
  *         - TMR_SELECT_CHANNEL_5
  *         - TMR_SELECT_CHANNEL_6
  *         - TMR_SELECT_CHANNEL_1C
  *         - TMR_SELECT_CHANNEL_2C
  *         - TMR_SELECT_CHANNEL_3C
  *         - TMR_SELECT_CHANNEL_4C
  * @param  oc_polarity
  *         this parameter can be one of the following values:
  *         - TMR_POLARITY_ACTIVE_HIGH
  *         - TMR_POLARITY_ACTIVE_LOW
  * @retval none
  */
void tmr_output_channel_polarity_set(tmr_type *tmr_x, tmr_channel_select_type tmr_channel, \
                                     tmr_polarity_active_type oc_polarity)
{
  uint16_t channel;

  channel = tmr_channel;

  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->cctrl_bit.c1p = (uint32_t)oc_polarity;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->cctrl_bit.c2p = (uint32_t)oc_polarity;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->cctrl_bit.c3p = (uint32_t)oc_polarity;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->cctrl_bit.c4p = (uint32_t)oc_polarity;
      break;

    case TMR_SELECT_CHANNEL_5:
      tmr_x->cctrl_bit.c5p = (uint32_t)oc_polarity;
      break;

    case TMR_SELECT_CHANNEL_6:
      tmr_x->cctrl_bit.c6p = (uint32_t)oc_polarity;
      break;

    case TMR_SELECT_CHANNEL_1C:
      tmr_x->cctrl_bit.c1cp = (uint32_t)oc_polarity;
      break;

    case TMR_SELECT_CHANNEL_2C:
      tmr_x->cctrl_bit.c2cp = (uint32_t)oc_polarity;
      break;

    case TMR_SELECT_CHANNEL_3C:
      tmr_x->cctrl_bit.c3cp = (uint32_t)oc_polarity;
      break;

    case TMR_SELECT_CHANNEL_4C:
      tmr_x->cctrl_bit.c4cp = (uint32_t)oc_polarity;
      break;

    default:
      break;
  }
}

/**
  * @brief  enable or disable tmr external clock
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_external_clock_enable(tmr_type *tmr_x, confirm_state new_state)
{
  tmr_x->stctrl_bit.ecmben = new_state;
}

/**
  * @brief  config tmr external clock
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4
  * @param  es_divide
  *         this parameter can be one of the following values:
  *         - TMR_ES_FREQUENCY_DIV_1
  *         - TMR_ES_FREQUENCY_DIV_2
  *         - TMR_ES_FREQUENCY_DIV_4
  *         - TMR_ES_FREQUENCY_DIV_8
  * @param  es_polarity
  *         this parameter can be one of the following values:
  *         - TMR_ES_POLARITY_NON_INVERTED
  *         - TMR_ES_POLARITY_INVERTED
  * @param  es_filter (0x0~0xf)
  * @retval none
  */
void tmr_external_clock_config(tmr_type *tmr_x, tmr_external_signal_divider_type es_divide, \
                               tmr_external_signal_polarity_type  es_polarity, uint16_t es_filter)
{
  tmr_x->stctrl_bit.esdiv = es_divide;
  tmr_x->stctrl_bit.esp = es_polarity;
  tmr_x->stctrl_bit.esf = es_filter;
}

/**
  * @brief  config tmr external clock mode1
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9
  * @param  es_divide
  *         this parameter can be one of the following values:
  *         - TMR_ES_FREQUENCY_DIV_1
  *         - TMR_ES_FREQUENCY_DIV_2
  *         - TMR_ES_FREQUENCY_DIV_4
  *         - TMR_ES_FREQUENCY_DIV_8
  * @param  es_polarity
  *         this parameter can be one of the following values:
  *         - TMR_ES_POLARITY_NON_INVERTED
  *         - TMR_ES_POLARITY_INVERTED
  * @param  es_filter (0x0~0xf)
  * @retval none
  */
void tmr_external_clock_mode1_config(tmr_type *tmr_x, tmr_external_signal_divider_type es_divide, \
                                     tmr_external_signal_polarity_type  es_polarity, uint16_t es_filter)
{
  tmr_external_clock_config(tmr_x, es_divide, es_polarity, es_filter);
  tmr_x->stctrl_bit.smsel = TMR_SUB_EXTERNAL_CLOCK_MODE_A;
  tmr_x->stctrl_bit.stis = TMR_SUB_INPUT_SEL_EXTIN;
}

/**
  * @brief  config tmr external clock mode2
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4
  * @param  es_divide
  *         this parameter can be one of the following values:
  *         - TMR_ES_FREQUENCY_DIV_1
  *         - TMR_ES_FREQUENCY_DIV_2
  *         - TMR_ES_FREQUENCY_DIV_4
  *         - TMR_ES_FREQUENCY_DIV_8
  * @param  es_polarity
  *         this parameter can be one of the following values:
  *         - TMR_ES_POLARITY_NON_INVERTED
  *         - TMR_ES_POLARITY_INVERTED
  * @param  es_filter (0x0~0xf)
  * @retval none
  */
void tmr_external_clock_mode2_config(tmr_type *tmr_x, tmr_external_signal_divider_type es_divide, \
                                     tmr_external_signal_polarity_type  es_polarity, uint16_t es_filter)
{
  tmr_external_clock_config(tmr_x, es_divide, es_polarity, es_filter);
  tmr_x->stctrl_bit.ecmben = TRUE;
}

/**
  * @brief  config tmr encoder mode
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4
  * @param  encoder_mode
  *         this parameter can be one of the following values:
  *         - TMR_ENCODER_MODE_A
  *         - TMR_ENCODER_MODE_B
  *         - TMR_ENCODER_MODE_C
  * @param  ic1_polarity
  *         this parameter can be one of the following values:
  *         - TMR_INPUT_RISING_EDGE
  *         - TMR_INPUT_FALLING_EDGE
  *         - TMR_INPUT_BOTH_EDGE
  * @param  ic2_polarity
  *         this parameter can be one of the following values:
  *         - TMR_INPUT_RISING_EDGE
  *         - TMR_INPUT_FALLING_EDGE
  *         - TMR_INPUT_BOTH_EDGE
  * @retval none
  */
void tmr_encoder_mode_config(tmr_type *tmr_x, tmr_encoder_mode_type encoder_mode, tmr_input_polarity_type \
                             ic1_polarity, tmr_input_polarity_type ic2_polarity)
{
  tmr_x->stctrl_bit.smsel = encoder_mode;

  /* set ic1 polarity */
  tmr_x->cctrl_bit.c1p =  (ic1_polarity & 0x1);
  tmr_x->cctrl_bit.c1cp = (ic1_polarity >> 1);
  /* set ic1 as input channel */
  tmr_x->cm1_input_bit.c1c = TMR_CC_CHANNEL_MAPPED_DIRECT;

  /* set ic2 polarity */
  tmr_x->cctrl_bit.c2p =  (ic2_polarity & 0x1);
  tmr_x->cctrl_bit.c2cp = (ic2_polarity >> 1);
  /* set ic2 as input channel */
  tmr_x->cm1_input_bit.c2c = TMR_CC_CHANNEL_MAPPED_DIRECT;
}

/**
  * @brief  set tmr force output
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  tmr_channel
  *         this parameter can be one of the following values:
  *         - TMR_SELECT_CHANNEL_1
  *         - TMR_SELECT_CHANNEL_2
  *         - TMR_SELECT_CHANNEL_3
  *         - TMR_SELECT_CHANNEL_4
  *         - TMR_SELECT_CHANNEL_5
  *         - TMR_SELECT_CHANNEL_6
  * @param  force_output
  *         this parameter can be one of the following values:
  *         - TMR_FORCE_OUTPUT_HIGH
  *         - TMR_FORCE_OUTPUT_LOW
  * @retval none
  */
void tmr_force_output_set(tmr_type *tmr_x,  tmr_channel_select_type tmr_channel, \
                          tmr_force_output_type force_output)
{
  uint16_t channel;

  channel = tmr_channel;

  switch(channel)
  {
    case TMR_SELECT_CHANNEL_1:
      tmr_x->cm1_output_bit.c1octrl = force_output;
      break;

    case TMR_SELECT_CHANNEL_2:
      tmr_x->cm1_output_bit.c2octrl = force_output;
      break;

    case TMR_SELECT_CHANNEL_3:
      tmr_x->cm2_output_bit.c3octrl = force_output;
      break;

    case TMR_SELECT_CHANNEL_4:
      tmr_x->cm2_output_bit.c4octrl = force_output;
      break;

    case TMR_SELECT_CHANNEL_5:
      tmr_x->cm3_output_bit.c5octrl = force_output;
      break;

    case TMR_SELECT_CHANNEL_6:
      tmr_x->cm3_output_bit.c6octrl = force_output;
      break;

    default:
      break;
  }
}

/**
  * @brief  config tmr dma control
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  dma_length
  *         this parameter can be one of the following values:
  *         - TMR_DMA_TRANSFER_1BYTE
  *         - TMR_DMA_TRANSFER_2BYTES
  *         - TMR_DMA_TRANSFER_3BYTES
  *         ...
  *         - TMR_DMA_TRANSFER_17BYTES
  *         - TMR_DMA_TRANSFER_18BYTES
  * @param  dma_base_address
  *         this parameter can be one of the following values:
  *         - TMR_CTRL1_ADDRESS
  *         - TMR_CTRL2_ADDRESS
  *         - TMR_STCTRL_ADDRESS
  *         - TMR_IDEN_ADDRESS
  *         - TMR_ISTS_ADDRESS
  *         - TMR_SWEVT_ADDRESS
  *         - TMR_CM1_ADDRESS
  *         - TMR_CM2_ADDRESS
  *         - TMR_CCTRL_ADDRESS
  *         - TMR_CVAL_ADDRESS
  *         - TMR_DIV_ADDRESS
  *         - TMR_PR_ADDRESS
  *         - TMR_RPR_ADDRESS
  *         - TMR_C1DT_ADDRESS
  *         - TMR_C2DT_ADDRESS
  *         - TMR_C3DT_ADDRESS
  *         - TMR_C4DT_ADDRESS
  *         - TMR_BRK_ADDRESS
  * @retval none
  */
void tmr_dma_control_config(tmr_type *tmr_x, tmr_dma_transfer_length_type dma_length, \
                            tmr_dma_address_type dma_base_address)
{
  tmr_x->dmactrl_bit.dtb = dma_length;
  tmr_x->dmactrl_bit.addr = dma_base_address;
}

/**
  * @brief  config tmr brake mode and dead-time
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR9, TMR10, TMR11
  * @param  brkdt_struct
  *         - to the structure of tmr_brkdt_config_type
  * @retval none
  */
void tmr_brkdt_config(tmr_type *tmr_x, tmr_brkdt_config_type *brkdt_struct)
{
  tmr_x->brk_bit.dtc = brkdt_struct->deadtime;
  tmr_x->brk_bit.fcsodis = brkdt_struct->fcsodis_state;
  tmr_x->brk_bit.fcsoen = brkdt_struct->fcsoen_state;
  tmr_x->brk_bit.brkv = brkdt_struct->brk_polarity;
  tmr_x->brk_bit.aoen = brkdt_struct->auto_output_enable;	
  tmr_x->brk_bit.brken = brkdt_struct->brk_enable;
  tmr_x->brk_bit.wpc = brkdt_struct->wp_level;
}

/**
  * @brief  set tmr break input filter value
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR9, TMR10, TMR11
  * @param  filter_value (0x0~0xf)
  * @retval none
  */
void tmr_brk_filter_value_set(tmr_type *tmr_x, uint8_t filter_value)
{
  tmr_x->brk_bit.brkf = filter_value;
}

/**
  * @brief  config tmr brake 2
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1
  * @param  brk2_struct
  *         - to the structure of tmr_brk2_config_type
  * @retval none
  */
void tmr_brk2_config(tmr_type *tmr_x, tmr_brk2_config_type *brk2_struct)
{
  tmr_x->brk_bit.brk2v = brk2_struct->brk2_polarity;
  tmr_x->brk_bit.brk2f = brk2_struct->brk2_filter;
  tmr_x->brk_bit.brk2en = brk2_struct->brk2_enable;
}

/**
  * @brief  remapping tmr overflow status
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_overflow_flag_remap(tmr_type *tmr_x, confirm_state new_state)
{
  /* tmr overflow remap set */
  tmr_x->ctrl1_bit.ovfifrmp = new_state;
}

/**
  * @brief  select tmr primary mode2
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1
  * @param  primary_mode
  *         this parameter can be one of the following values:
  *         - TMR_PRIMARY_SEL_RESET
  *         - TMR_PRIMARY_SEL_ENABLE
  *         - TMR_PRIMARY_SEL_OVERFLOW
  *         - TMR_PRIMARY_SEL_COMPARE
  *         - TMR_PRIMARY_SEL_C1ORAW
  *         - TMR_PRIMARY_SEL_C2ORAW
  *         - TMR_PRIMARY_SEL_C3ORAW
  *         - TMR_PRIMARY_SEL_C4ORAW
  *         - TMR_PRIMARY_SEL_C5ORAW
  *         - TMR_PRIMARY_SEL_C6ORAW
  *         - TMR_PRIMARY_SEL_C4ORAW_EDGE
  *         - TMR_PRIMARY_SEL_C6ORAW_EDGE
  *         - TMR_PRIMARY_SEL_C4_RISING_C6_RISING
  *         - TMR_PRIMARY_SEL_C4_RISING_C6_FALLING
  *         - TMR_PRIMARY_SEL_C5_RISING_C6_RISING
  *         - TMR_PRIMARY_SEL_C5_RISING_C6_FALLING
  * @retval none
  */
void tmr_primary_mode2_select(tmr_type *tmr_x, tmr_primary_select_type primary_mode)
{
  tmr_x->ctrl2_bit.ptos2 = primary_mode;
}

/**
  * @brief  set the cxoraw clear input source
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4
  * @param  ocrefclearinputsource 
  *         this parameter can be one of the following values:
  *         - TMR_CORAW_CLR_EXT
  *         - TMR_CORAW_CLR_CMP1
  *         - TMR_CORAW_CLR_CMP2
  * @retval none
  */
void tmr_coraw_clear_set(tmr_type *tmr_x, tmr_coraw_clear_type coraw_clear)
{
  uint32_t input_src;
  input_src = coraw_clear>>1U;
  tmr_x->stctrl_bit.cossel = input_src;
  input_src = 0x01 & coraw_clear;
  tmr_x->opt1_bit.coraw_clr = input_src;
}

/**
  * @brief  get tmr overflow copy flag
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR6, TMR7, TMR9, TMR10, TMR11
  * @retval state of tmr overflow copy flag
  */
flag_status tmr_overflow_cpy_get(tmr_type *tmr_x)
{
  return (flag_status)tmr_x->cval_bit.ovfifcpy;
}

/**
  * @brief  enable brake bidirectional
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR9, TMR10, TMR11
  * @param  brk_sel
  *         this parameter can be one of the following values:
  *         - TMR_BRK_SELECT_1
  *         - TMR_BRK_SELECT_2
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_brk_bidir_enable(tmr_type *tmr_x, tmr_brk_type brk_sel, confirm_state new_state)
{
  if (brk_sel != TMR_BRK_SELECT_2)
  {
    tmr_x->brk_bit.brkbid = new_state;
  }
  else
  {
    tmr_x->brk_bit.brk2bid = new_state;
  }
}

/**
  * @brief  release brake bidirectional
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR9, TMR10, TMR11
  * @param  brk_sel
  *         this parameter can be one of the following values:
  *         - TMR_BRK_SELECT_1
  *         - TMR_BRK_SELECT_2
  * @retval none
  */
void tmr_brk_release(tmr_type *tmr_x, tmr_brk_type brk_sel)
{
  if (brk_sel != TMR_BRK_SELECT_2)
  {
    tmr_x->brk_bit.brkrls = TRUE;
  }
  else
  {
    tmr_x->brk_bit.brk2rls = TRUE;
  }
}

/**
  * @brief  check if brake bidirectional released
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR9, TMR10, TMR11
  * @param  brk
  *         this parameter can be one of the following values:
  *         - TMR_BRK_SELECT_1
  *         - TMR_BRK_SELECT_2
  * @retval tmr_brk_release_status
  *         - TMR_BRK_RELEASED  
  *         - TMR_BRK_UNRELEASED
  */
tmr_brk_release_status tmr_brk_release_check(tmr_type *tmr_x, tmr_brk_type brk)
{
  if (brk != TMR_BRK_SELECT_2)
  {
    return (tmr_brk_release_status)tmr_x->brk_bit.brkrls;
  }
  else
  {
    return (tmr_brk_release_status)tmr_x->brk_bit.brk2rls;
  }
}

/**
  * @brief  set channel5 combined
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1
  * @param  ch5_comb
  *         this parameter can be a combination of the following values:
  *         - TMR_CH5_COMBINED_NONE  
  *         - TMR_CH5_COMBINED_C1ORAW
  *         - TMR_CH5_COMBINED_C2ORAW
  *         - TMR_CH5_COMBINED_C3ORAW
  * @retval none
  */
void tmr_ch5_combined_set(tmr_type *tmr_x, uint32_t ch5_comb)
{
  tmr_x->c5dt |= ch5_comb;
}

/**
  * @brief  configures the brake input source.
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR9, TMR10, TMR11
  * @param  brkin_struct brake input source configuration
  * @retval none
  */
void tmr_brk_input_config(tmr_type *tmr_x, tmr_brkin_config_type *brkin_struct)
{
  if (brkin_struct->brk_sel != TMR_BRK_SELECT_2)
  {
    switch (brkin_struct->source)
    {
      case TMR_BRKIN_SOURCE_BRKIN:
      {
        tmr_x->opt2_bit.brkinen = brkin_struct->enable;
        tmr_x->opt2_bit.brkinp = brkin_struct->polarity;
        break;
      }
      case TMR_BRKIN_SOURCE_CMP1:
      {
        tmr_x->opt2_bit.brkcmp1en = brkin_struct->enable;
        tmr_x->opt2_bit.brkcmp1p = brkin_struct->polarity;
        break;
      }
      case TMR_BRKIN_SOURCE_CMP2:
      {
        tmr_x->opt2_bit.brkcmp2en = brkin_struct->enable;
        tmr_x->opt2_bit.brkcmp2p = brkin_struct->polarity;
        break;
      }
    }
  }
  else
  {
    switch (brkin_struct->source)
    {
      case TMR_BRKIN_SOURCE_BRKIN:
      {
        tmr_x->opt3_bit.brk2inen = brkin_struct->enable;
        tmr_x->opt3_bit.brk2inp = brkin_struct->polarity;
        break;
      }
      case TMR_BRKIN_SOURCE_CMP1:
      {
        tmr_x->opt3_bit.brk2cmp1en = brkin_struct->enable;
        tmr_x->opt3_bit.brk2cmp1p = brkin_struct->polarity;
        break;
      }
      case TMR_BRKIN_SOURCE_CMP2:
      {
        tmr_x->opt3_bit.brk2cmp2en = brkin_struct->enable;
        tmr_x->opt3_bit.brk2cmp2p = brkin_struct->polarity;
        break;
      }
    }
  }
}

/**
  * @brief  select external source 
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4
  * @param  ext_src
  *         this parameter can be one of the following values:
  *         for tmr1/tmr3/tmr4:
  *         - TMR_EXT_SOURCE_GPIO
  *         - TMR_EXT_SOURCE_CMP1
  *         - TMR_EXT_SOURCE_CMP2
  *         for tmr1:
  *         - TMR_EXT_SOURCE_ADC1_VM
  *         - TMR_EXT_SOURCE_ADC2_VM
  *         for tmr3:
  *         - TMR_EXT_SOURCE_TMR4_EXT
  *         for tmr4:
  *         - TMR_EXT_SOURCE_TMR3_EXT
  * @retval none
  */
void tmr_external_source_select(tmr_type *tmr_x, uint32_t ext_src)
{
  tmr_x->opt2_bit.extsel = ext_src;
}

/**
  * @brief  select input channel
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1, TMR3, TMR4, TMR9, TMR10, TMR11
  * @param  remap
  *         for tmr1 this parameter can be one of the following values:
  *         - TMR_TMR1_CH1_GPIO    
  *         - TMR_TMR1_CH1_CMP1    
  *         - TMR_TMR1_CH1_CMP2    
  *         - TMR_TMR1_CH2_GPIO    
  *         - TMR_TMR1_CH2_CMP1    
  *         - TMR_TMR1_CH2_CMP2    
  *         for tmr3 this parameter can be one of the following values:
  *         - TMR_TMR3_CH1_GPIO    
  *         - TMR_TMR3_CH1_CMP1    
  *         - TMR_TMR3_CH1_CMP2    
  *         - TMR_TMR3_CH1_TMR4CH1 
  *         - TMR_TMR3_CH2_GPIO    
  *         - TMR_TMR3_CH2_CMP1    
  *         - TMR_TMR3_CH2_CMP2    
  *         - TMR_TMR3_CH2_TMR4CH2 
  *         - TMR_TMR3_CH3_GPIO    
  *         - TMR_TMR3_CH3_CMP1    
  *         - TMR_TMR3_CH3_TMR4CH3 
  *         - TMR_TMR3_CH4_GPIO    
  *         - TMR_TMR3_CH4_CMP2    
  *         for tmr4 this parameter can be one of the following values:
  *         - TMR_TMR4_CH1_GPIO    
  *         - TMR_TMR4_CH1_CMP1    
            - TMR_TMR4_CH1_CMP2    
  *         - TMR_TMR4_CH1_TMR3CH1 
  *         - TMR_TMR4_CH2_GPIO    
  *         - TMR_TMR4_CH2_CMP1    
  *         - TMR_TMR4_CH2_CMP2    
  *         - TMR_TMR4_CH2_TMR3CH2 
  *         - TMR_TMR4_CH3_GPIO    
  *         - TMR_TMR4_CH3_CMP2    
  *         - TMR_TMR4_CH3_TMR3CH3 
  *         - TMR_TMR4_CH4_GPIO    
  *         - TMR_TMR4_CH4_CMP1    
  *         for tmr9 this parameter can be one of the following values:
  *         - TMR_TMR9_CH1_GPIO    
  *         - TMR_TMR9_CH1_CMP1    
  *         - TMR_TMR9_CH1_CMP2    
  *         - TMR_TMR9_CH2_GPIO    
  *         - TMR_TMR9_CH2_CMP1    
  *         - TMR_TMR9_CH2_CMP2    
  *         for tmr10 this parameter can be one of the following values:
  *         - TMR_TMR10_CH1_GPIO   
  *         - TMR_TMR10_CH1_CMP1   
  *         - TMR_TMR10_CH1_CMP2   
  *         for tmr11 this parameter can be one of the following values:
  *         - TMR_TMR11_CH1_GPIO   
  *         - TMR_TMR11_CH1_CMP1   
  *         - TMR_TMR11_CH1_CMP2   
  *         - TMR_TMR11_CH1_CLKOUT 
  *         - TMR_TMR11_CH1_HEXTDIV
  *         - TMR_TMR11_CH1_ERTCCLK
  *         - TMR_TMR11_CH1_LEXT   
  *         - TMR_TMR11_CH1_LICK   
  * @retval none
  */
void tmr_input_ch_select(tmr_type *tmr_x, uint32_t ch_src)
{
  tmr_x->chsel |= ch_src;
}

/**
  * @brief  enable independently asymmetric pwm mode
  * @param  tmr_x: select the tmr peripheral.
  *         this parameter can be one of the following values:
  *         TMR1
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void tmr_iasym_mode_enable(tmr_type *tmr_x, confirm_state new_state)
{
  tmr_x->ctrl2_bit.iasymen = new_state;
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
