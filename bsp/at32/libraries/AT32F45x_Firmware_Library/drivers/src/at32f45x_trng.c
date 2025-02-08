/**
  **************************************************************************
  * @file     at32f45x_trng.c
  * @brief    contains all the functions for the trng firmware library
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

#include "at32f45x_conf.h"

/** @addtogroup AT32F45x_periph_driver
  * @{
  */

/** @defgroup TRNG
  * @brief TRNG driver modules
  * @{
  */

#ifdef TRNG_MODULE_ENABLED

/** @defgroup TRNG_private_functions
  * @{
  */

/**
  * @brief  deinitializes the trng peripheral registers to their default reset values.
  * @param  none
  * @retval none
  */
void trng_reset(void)
{
  crm_periph_reset(CRM_TRNG_PERIPH_RESET, TRUE);
  crm_periph_reset(CRM_TRNG_PERIPH_RESET, FALSE);
}

/**
  * @brief  enable or disable the trng peripheral.
  * @param  new_state: new state of the trng peripheral.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void trng_enable(confirm_state new_state)
{
  TRNG->ctrl_bit.nsen = new_state;
}

/**
  * @brief  enable or disable the trng interrupt.
  * @param  trng_int: specifies the trng interrupt sources to be enabled or disabled.
  *         this parameter can be any combination of the following values:
  *         - TRNG_FIE_INT:   fail interrupt
  *         - TRNG_DTRIE_INT: data port ready interrupt
  * @param  new_state: new state of the specified trng interrupt.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void trng_interrupt_enable(uint32_t trng_int, confirm_state new_state)
{
  if(new_state)
  {
    TRNG->ctrl |= trng_int;
  }else
  {
    TRNG->ctrl &= ~trng_int;
  }
}

/**
  * @brief  set the trng clock divider factor
  * @param  factor: clock divider value, from 0 to 15
  * @retval none
  */
void trng_clock_divider_set(uint8_t factor)
{
  trng_conditioning_and_buffer_enable(FALSE);

  TRNG->ctrl_bit.clkdiv = factor;

  trng_conditioning_and_buffer_enable(TRUE);
}

/**
  * @brief  enable or disable conditioning unit and output buffer
  * @param  new_state: new state of the conditioning unit and output buffer.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void trng_conditioning_and_buffer_enable(confirm_state new_state)
{
  TRNG->ctrl_bit.cudis = !new_state;
}

/**
  * @brief  lock the programming register
  * @param  none
  * @retval none
  */
void trng_programing_register_lock(void)
{
  TRNG->ctrl_bit.prglk = TRUE;
}

/**
  * @brief  return a 32-bit random number.
  * @param  none
  * @retval 32-bit random number.
  */
uint32_t trng_value_get(void)
{
  return TRNG->dt;
}

/**
  * @brief  check whether the specified trng flag is set or not.
  * @param  flag: specifies the trng flag to check.
  *         this parameter can be one of the following values:
  *         - TRNG_DTRDY_FLAG: data ready flag.
  *         - TRNG_CKFES_FLAG: clock error current flag.
  *         - TRNG_ESFES_FLAG: entropy source error current flag.
  *         - TRNG_CEFIS_FLAG: clock error interrupt flag.
  *         - TRNG_ESFIS_FLAG: entropy source interrupt flag.
  * @retval the new state of flag (SET or RESET).
  */
flag_status trng_flag_get(uint32_t flag)
{
  if(TRNG->sts & flag)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  check whether the specified trng interrupt flag is set or not.
  * @param  flag: specifies the flag to check.
  *         this parameter can be one of the following values:
  *         - TRNG_DTRDY_FLAG: data ready flag.
  *         - TRNG_CKFES_FLAG: clock error current flag.
  *         - TRNG_ESFES_FLAG: entropy source error current flag.
  *         - TRNG_CEFIS_FLAG: clock error interrupt flag.
  *         - TRNG_ESFIS_FLAG: entropy source interrupt flag.
  * @retval the new state of usart_flag (SET or RESET).
  */
flag_status trng_interrupt_flag_get(uint32_t flag)
{
  flag_status bit_status = RESET;
  switch(flag)
  {
    case TRNG_DTRDY_FLAG:
      if(TRNG->ctrl & TRNG_DTRIE_INT)
      {
        bit_status = (TRNG->sts & flag) ? SET : RESET;
      }
      break;
    case TRNG_CKFES_FLAG:
    case TRNG_ESFES_FLAG:
    case TRNG_CEFIS_FLAG:
    case TRNG_ESFIS_FLAG:
      if(TRNG->ctrl & TRNG_FIE_INT)
      {
        bit_status = (TRNG->sts & flag) ? SET : RESET;
      }
      break;
    default:
      break;
  }
  return bit_status;
}

/**
  * @brief  clear the trng flag.
  * @param  flag: specifies the flag to clear.
  *         this parameter can be one of the following values:
  *         - TRNG_CKFES_FLAG: clock error current flag.
  *         - TRNG_ESFES_FLAG: entropy source error current flag.
  *         - TRNG_CEFIS_FLAG: clock error interrupt flag.
  *         - TRNG_ESFIS_FLAG: entropy source interrupt flag.
  * @retval none
  */
void trng_flag_clear(uint32_t flag)
{
  switch(flag)
  {
    case TRNG_CKFES_FLAG:
    case TRNG_ESFES_FLAG:
      TRNG->ctrl_bit.fesclr = TRUE;
      break;
    case TRNG_CEFIS_FLAG:
    case TRNG_ESFIS_FLAG:
      TRNG->sts = flag;
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
