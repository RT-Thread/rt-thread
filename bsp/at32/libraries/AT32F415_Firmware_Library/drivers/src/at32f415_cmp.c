/**
  **************************************************************************
  * @file     at32f415_cmp.c
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

#include "at32f415_conf.h"

/** @addtogroup AT32F415_periph_driver
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
    CMP->ctrlsts2_bit.cmp1ninvsel =  cmp_init_struct->cmp_non_inverting;
    CMP->ctrlsts1_bit.cmp1invsel  =  cmp_init_struct->cmp_inverting;
    CMP->ctrlsts1_bit.cmp1ssel    =  cmp_init_struct->cmp_speed;
    CMP->ctrlsts1_bit.cmp1tag     =  cmp_init_struct->cmp_output;
    CMP->ctrlsts1_bit.cmp1p       =  cmp_init_struct->cmp_polarity;
    CMP->ctrlsts1_bit.cmp1hyst    =  cmp_init_struct->cmp_hysteresis;
  }
  else
  {
    CMP->ctrlsts2_bit.cmp2ninvsel =  cmp_init_struct->cmp_non_inverting;
    CMP->ctrlsts1_bit.cmp2invsel  =  cmp_init_struct->cmp_inverting;
    CMP->ctrlsts1_bit.cmp2ssel    =  cmp_init_struct->cmp_speed;
    CMP->ctrlsts1_bit.cmp2tag     =  cmp_init_struct->cmp_output;
    CMP->ctrlsts1_bit.cmp2p       =  cmp_init_struct->cmp_polarity;
    CMP->ctrlsts1_bit.cmp2hyst    =  cmp_init_struct->cmp_hysteresis;
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
  cmp_init_struct->cmp_non_inverting = CMP_NON_INVERTING_PA1_PA3;
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
    CMP->ctrlsts1_bit.cmp1en  = new_state;
  }
  else
  {
    CMP->ctrlsts1_bit.cmp2en  = new_state;
  }
}

/**
  * @brief  enable or disable cmp input shift
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void cmp_input_shift_enable(confirm_state new_state)
{
  CMP->ctrlsts1_bit.cmp1is = new_state;
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
    cmpout = CMP->ctrlsts1_bit.cmp1value;
  }
  else
  {
    cmpout = CMP->ctrlsts1_bit.cmp2value;
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
    CMP->ctrlsts1_bit.cmp1wp = TRUE;
  }
  else
  {
    CMP->ctrlsts1_bit.cmp2wp = TRUE;
  }
}

/**
  * @brief  enable or disable double comparator mode
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void cmp_double_mode_enable(confirm_state new_state)
{
  CMP->ctrlsts1_bit.dcmpen = new_state;
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
