/**
  **************************************************************************
  * @file     at32f421_cmp.c
  * @brief    contains all the functions for the gpio firmware library
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

#include "at32f421_conf.h"

/** @addtogroup AT32F421_periph_driver
  * @{
  */

/** @defgroup CMP
  * @brief CMP driver modules
  * @{
  */

#ifdef CMP_MODULE_ENABLED

/** @defgroup CMP_private_functions
  * @{
  */

#define CMP_CTRLSTS1_CLEAR_MASK              ((uint32_t)0x00039C7C)
#define CMP_INPINPUT_CLEAR_MASK              ((uint32_t)0x00000180)
#define CMP_HIGH_PULSE_CLEAR_MASK            ((uint16_t)0x003F)
#define CMP_LOW_PULSE_CLEAR_MASK             ((uint16_t)0x003F)

/**
  * @brief  reset the cmp register
  * @param  none
  * @retval none
  */
void cmp_reset(void)
{
  crm_periph_reset(CRM_CMP_PERIPH_RESET, TRUE);
  crm_periph_reset(CRM_CMP_PERIPH_RESET, FALSE);
}

/**
  * @brief  initialize the cmp peripheral
  * @param  cmp_sel: to select the cmp peripheral
  *         this parameter only can be CMP1_SELECTION
  * @param  cmp_init_struct: pointer to cmp init structure
  * @retval none
  */
void cmp_init(cmp_sel_type cmp_sel, cmp_init_type* cmp_init_struct)
{
  if(cmp_sel == CMP1_SELECTION)
  {
    CMP->ctrlsts_bit.cmpninvsel =  cmp_init_struct->cmp_non_inverting;
    CMP->ctrlsts_bit.cmpinvsel  =  cmp_init_struct->cmp_inverting;
    CMP->ctrlsts_bit.cmpssel    =  cmp_init_struct->cmp_speed;
    CMP->ctrlsts_bit.cmptag     =  cmp_init_struct->cmp_output;
    CMP->ctrlsts_bit.cmpp       =  cmp_init_struct->cmp_polarity;
    CMP->ctrlsts_bit.cmphyst    =  cmp_init_struct->cmp_hysteresis;
  }
}

/**
  * @brief  fill each cmp_init_type member with its default value.
  * @param  cmp_init_type : pointer to a cmp_init_type structure
  *         which will be initialized.
  * @retval none
  */
void cmp_default_para_init(cmp_init_type *cmp_init_struct)
{
  /* reset cmp init structure parameters values */
  cmp_init_struct->cmp_non_inverting = CMP_NON_INVERTING_PA1;
  cmp_init_struct->cmp_inverting = CMP_INVERTING_1_4VREFINT;
  cmp_init_struct->cmp_speed = CMP_SPEED_FAST;
  cmp_init_struct->cmp_output = CMP_OUTPUT_NONE;
  cmp_init_struct->cmp_polarity = CMP_POL_NON_INVERTING;
  cmp_init_struct->cmp_hysteresis = CMP_HYSTERESIS_NONE;
}

/**
  * @brief  enable or disable cmp
  * @param  cmp_sel: to select the cmp peripheral
  *         this parameter only can be CMP1_SELECTION.
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void cmp_enable(cmp_sel_type cmp_sel, confirm_state new_state)
{
  /* cmp enable */
  if(cmp_sel == CMP1_SELECTION)
  {
    CMP->ctrlsts_bit.cmpen  = new_state;
  }
}

/**
  * @brief  enable or disable cmp input shift
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void cmp_input_shift_enable(confirm_state new_state)
{
  CMP->ctrlsts_bit.cmpis = new_state;
}

/**
  * @brief  get cmp output value
  * @param  cmp_sel: to select the cmp peripheral
  *         this parameter only can be CMP1_SELECTION.
  * @retval cmp output value
  */
uint32_t cmp_output_value_get(cmp_sel_type cmp_sel)
{
  uint32_t cmpout = 0x0;
  if(cmp_sel == CMP1_SELECTION)
  {
    cmpout = CMP->ctrlsts_bit.cmpvalue;
  }

  /* return the comparator output level */
  return (uint32_t)(cmpout);
}

/**
  * @brief  enable cmp write protect
  * @param  cmp_sel: to select the cmp peripheral
  *         this parameter only can be CMP1_SELECTION.
  * @retval none
  */
void cmp_write_protect_enable(cmp_sel_type cmp_sel)
{
  if(cmp_sel == CMP1_SELECTION)
  {
    CMP->ctrlsts_bit.cmpwp = TRUE;
  }
}

/**
  * @brief  configure cmp glitch filter
  * @param  high_pulse_cnt: cmp high pulse count.
  *         this parameter must be a value between 0x00 and 0x3f
  * @param  low_pulse_cnt: cmp low pulse count.
  *         this parameter must be a value between 0x00 and 0x3f
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void cmp_filter_config(uint16_t high_pulse_cnt, uint16_t low_pulse_cnt, confirm_state new_state)
{
  if (new_state != FALSE)
  {
    /* enable the glitch filter */
    CMP->g_filter_en_bit.gfe = TRUE;

    /* write to cmp high_pulse and low_pulse */
    CMP->low_pulse_bit.l_pulse_cnt = low_pulse_cnt;
    CMP->high_pulse_bit.h_pulse_cnt = high_pulse_cnt;
  }
  else
  {
    /* disable the glitch filter */
    CMP->g_filter_en_bit.gfe = FALSE;

    /* reset the h_pulse_cnt and l_pulse_cnt bits */
    CMP->low_pulse_bit.l_pulse_cnt = low_pulse_cnt;
    CMP->high_pulse_bit.h_pulse_cnt = high_pulse_cnt;
  }
}

/**
  * @brief  configure cmp blanking source.
  * @param  blank_sel: cmp blanking source
  *         this parameter can be one of the following values:
  *         - CMP_BLANKING_NONE
  *         - CMP_BLANKING_TMR1_CH4
  *         - CMP_BLANKING_TMR3_CH3
  *         - CMP_BLANKING_TMR15_CH2
  *         - CMP_BLANKING_TMR15_CH1
  * @retval none
  */
void cmp_blanking_config(cmp_blanking_type blank_sel)
{
  CMP->ctrlsts_bit.cmpblanking =  blank_sel;
}

/**
  * @brief  configure cmp scale voltage and voltage bridge
  * @param  scal_brg: cmp scal&brg configure
  *         this parameter can be one of the following values:
  *         - CMP_SCAL_BRG_00: vrefint = 3/4 vrefint = 1/2 vrefint = 1/4 vrefint = 0v
  *         - CMP_SCAL_BRG_10: vrefint = 3/4 vrefint = 1/2 vrefint = 1/4 vrefint = 1.2v
  *         - CMP_SCAL_BRG_11: vrefint = 1.2v, 3/4 vrefint = 0.9v, 1/2 vrefint = 0.6v, 1/4 vrefint = 0.3v
  * @retval none
  */
void cmp_scal_brg_config(uint32_t scal_brg)
{
  uint32_t tmp_scal = 0, tmp_brg = 0;
  tmp_scal = scal_brg >> 1;
  tmp_brg = scal_brg & 0x01;

  CMP->ctrlsts_bit.scalen = tmp_scal;
  CMP->ctrlsts_bit.brgen = tmp_brg;
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
