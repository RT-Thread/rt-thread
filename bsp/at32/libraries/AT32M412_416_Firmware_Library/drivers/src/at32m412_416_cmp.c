/**
  **************************************************************************
  * @file     at32m412_416_cmp.c
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

#include "at32m412_416_conf.h"

/** @addtogroup AT32M412_416_periph_driver
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
  * @brief  initialize the cmp peripheral
  * @param  cmp_sel: to select the cmp peripheral
  *         this parameter can be CMP1_SELECTION or CMP2_SELECTION
  * @param  cmp_init_struct: pointer to cmp init structure
  * @retval none
  */
void cmp_init(cmp_sel_type cmp_sel, cmp_init_type* cmp_init_struct)
{
  if(cmp_sel == CMP1_SELECTION)
  {
    CMP->cmp1_ctrlsts_bit.cmpninvsel =  cmp_init_struct->cmp_non_inverting;
    CMP->cmp1_ctrlsts_bit.cmpinvsel  =  cmp_init_struct->cmp_inverting;
    CMP->cmp1_ctrlsts_bit.cmpssel    =  cmp_init_struct->cmp_speed;
    CMP->cmp1_ctrlsts_bit.cmpp       =  cmp_init_struct->cmp_polarity;
    CMP->cmp1_ctrlsts_bit.cmphyst    =  cmp_init_struct->cmp_hysteresis;
  }
  else
  {
    CMP->cmp2_ctrlsts_bit.cmpninvsel =  cmp_init_struct->cmp_non_inverting;
    CMP->cmp2_ctrlsts_bit.cmpinvsel  =  cmp_init_struct->cmp_inverting;
    CMP->cmp2_ctrlsts_bit.cmpssel    =  cmp_init_struct->cmp_speed;
    CMP->cmp2_ctrlsts_bit.cmpp       =  cmp_init_struct->cmp_polarity;
    CMP->cmp2_ctrlsts_bit.cmphyst    =  cmp_init_struct->cmp_hysteresis;
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
  cmp_init_struct->cmp_non_inverting = CMP_NON_INVERTING_INP0;
  cmp_init_struct->cmp_inverting = CMP_INVERTING_INM0;
  cmp_init_struct->cmp_speed = CMP_SPEED_FAST;
  cmp_init_struct->cmp_polarity = CMP_POL_NON_INVERTING;
  cmp_init_struct->cmp_hysteresis = CMP_HYSTERESIS_NONE;
}

/**
  * @brief  enable or disable cmp
  * @param  cmp_sel: to select the cmp peripheral
  *         this parameter can be CMP1_SELECTION or CMP2_SELECTION
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void cmp_enable(cmp_sel_type cmp_sel, confirm_state new_state)
{
  /* cmp enable */
  if(cmp_sel == CMP1_SELECTION)
  {
    CMP->cmp1_ctrlsts_bit.cmpen  = new_state;
  }
  else
  {
    CMP->cmp2_ctrlsts_bit.cmpen  = new_state;
  }
}

/**
  * @brief  get cmp output value
  * @param  cmp_sel: to select the cmp peripheral
  *         this parameter can be CMP1_SELECTION or CMP2_SELECTION
  * @retval cmp output value
  */
uint32_t cmp_output_value_get(cmp_sel_type cmp_sel)
{
  uint32_t cmpout = 0x0;
  if(cmp_sel == CMP1_SELECTION)
  {
    cmpout = CMP->cmp1_ctrlsts_bit.cmpvalue;
  }
  else
  {
    cmpout = CMP->cmp2_ctrlsts_bit.cmpvalue;
  }

  /* return the comparator output level */
  return (uint32_t)(cmpout);
}

/**
  * @brief  enable cmp write protect
  * @param  cmp_sel: to select the cmp peripheral
  *         this parameter can be CMP1_SELECTION or CMP2_SELECTION
  * @retval none
  */
void cmp_write_protect_enable(cmp_sel_type cmp_sel)
{
  if(cmp_sel == CMP1_SELECTION)
  {
    CMP->cmp1_ctrlsts_bit.cmpwp = TRUE;
  }
  else
  {
    CMP->cmp2_ctrlsts_bit.cmpwp = TRUE;
  }
}

/**
  * @brief  configure cmp glitch filter
  * @param  cmp_sel: to select the cmp peripheral
  *         this parameter can be CMP1_SELECTION or CMP2_SELECTION
  * @param  high_pulse_cnt: cmp high pulse count.
  *         this parameter must be a value between 0x00 and 0x3f
  * @param  low_pulse_cnt: cmp low pulse count.
  *         this parameter must be a value between 0x00 and 0x3f
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void cmp_filter_config(cmp_sel_type cmp_sel, uint16_t high_pulse_cnt, uint16_t low_pulse_cnt, confirm_state new_state)
{
  if(cmp_sel == CMP1_SELECTION)
  {
	  if (new_state != FALSE)
	  {
      /* enable the glitch filter */
      CMP->cmp1_g_filter_en_bit.gfe = TRUE;

      /* write to cmp high_pulse and low_pulse */
      CMP->cmp1_low_pulse_bit.l_pulse_cnt = low_pulse_cnt;
      CMP->cmp1_high_pulse_bit.h_pulse_cnt = high_pulse_cnt;
	  }
	  else
	  {
      /* disable the glitch filter */
      CMP->cmp1_g_filter_en_bit.gfe = FALSE;

      /* reset the h_pulse_cnt and l_pulse_cnt bits */
      CMP->cmp1_low_pulse_bit.l_pulse_cnt = low_pulse_cnt;
      CMP->cmp1_high_pulse_bit.h_pulse_cnt = high_pulse_cnt;
	  }
  }
  else
  {
	  if (new_state != FALSE)
	  {
      /* enable the glitch filter */
      CMP->cmp2_g_filter_en_bit.gfe = TRUE;

      /* write to cmp high_pulse and low_pulse */
      CMP->cmp2_low_pulse_bit.l_pulse_cnt = low_pulse_cnt;
      CMP->cmp2_high_pulse_bit.h_pulse_cnt = high_pulse_cnt;
	  }
	  else
	  {
      /* disable the glitch filter */
      CMP->cmp2_g_filter_en_bit.gfe = FALSE;

      /* reset the h_pulse_cnt and l_pulse_cnt bits */
      CMP->cmp2_low_pulse_bit.l_pulse_cnt = low_pulse_cnt;
      CMP->cmp2_high_pulse_bit.h_pulse_cnt = high_pulse_cnt;
	  }
  }
}

/**
  * @brief  configure cmp blanking source.
  * @param  cmp_sel: to select the cmp peripheral
  *         this parameter can be CMP1_SELECTION or CMP2_SELECTION
  * @param  blank_sel: cmp blanking source
  *         this parameter can be one of the following values:
  *         - CMP_BLANKING_NONE
  *         - CMP_BLANKING_TMR1_CH4
  *         - CMP_BLANKING_TMR1_CH5
  *         - CMP_BLANKING_TMR3_CH3
  *         - CMP_BLANKING_TMR9_CH2
  *         - CMP_BLANKING_TMR9_CH1
  *         - CMP_BLANKING_TMR4_CH3
  * @retval none
  */
void cmp_blanking_config(cmp_sel_type cmp_sel, cmp_blanking_type blank_sel)
{
  if(cmp_sel == CMP1_SELECTION)
  {
    CMP->cmp1_ctrlsts_bit.cmpblanking =  blank_sel;
  }
  else
  {
    CMP->cmp2_ctrlsts_bit.cmpblanking =  blank_sel;
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
