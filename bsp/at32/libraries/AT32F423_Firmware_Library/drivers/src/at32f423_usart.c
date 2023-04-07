/**
  **************************************************************************
  * @file     at32f423_usart.c
  * @brief    contains all the functions for the usart firmware library
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

/* includes ------------------------------------------------------------------*/
#include "at32f423_conf.h"

/** @addtogroup AT32F423_periph_driver
  * @{
  */

/** @defgroup USART
  * @brief USART driver modules
  * @{
  */

#ifdef USART_MODULE_ENABLED

/** @defgroup USART_private_functions
  * @{
  */

/**
  * @brief  deinitialize the usart peripheral registers to their default reset values.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7,or USART8.
  * @retval none
  */
void usart_reset(usart_type* usart_x)
{
  if(usart_x == USART1)
  {
    crm_periph_reset(CRM_USART1_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_USART1_PERIPH_RESET, FALSE);
  }
  else if(usart_x == USART2)
  {
    crm_periph_reset(CRM_USART2_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_USART2_PERIPH_RESET, FALSE);
  }
  else if(usart_x == USART3)
  {
    crm_periph_reset(CRM_USART3_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_USART3_PERIPH_RESET, FALSE);
  }
  else if(usart_x == USART4)
  {
    crm_periph_reset(CRM_USART4_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_USART4_PERIPH_RESET, FALSE);
  }
  else if(usart_x == USART5)
  {
    crm_periph_reset(CRM_USART5_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_USART5_PERIPH_RESET, FALSE);
  }
  else if(usart_x == USART6)
  {
    crm_periph_reset(CRM_USART6_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_USART6_PERIPH_RESET, FALSE);
  }
  else if(usart_x == USART7)
  {
    crm_periph_reset(CRM_USART7_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_USART7_PERIPH_RESET, FALSE);
  }
#if defined (AT32F423Kx) || defined (AT32F423Tx) || defined (AT32F423Cx) || \
    defined (AT32F423Rx) || defined (AT32F423Vx)
  else if(usart_x == USART8)
  {
    crm_periph_reset(CRM_USART8_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_USART8_PERIPH_RESET, FALSE);
  }
#endif
}

/**
  * @brief  initialize the usart peripheral according to the specified parameters.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4 ,USART5, USART6, USART7 or USART8.
  * @param  baud_rate: configure the usart communication baud rate.
  * @param  data_bit: data bits transmitted or received in a frame
  *         this parameter can be one of the following values:
  *         - USART_DATA_7BITS
  *         - USART_DATA_8BITS
  *         - USART_DATA_9BITS.
  * @param  stop_bit: stop bits transmitted
  *         this parameter can be one of the following values:
  *         - USART_STOP_1_BIT
  *         - USART_STOP_0_5_BIT.
  *         - USART_STOP_2_BIT
  *         - USART_STOP_1_5_BIT.
  * @retval none
  */
void usart_init(usart_type* usart_x, uint32_t baud_rate, usart_data_bit_num_type data_bit, usart_stop_bit_num_type stop_bit)
{
  crm_clocks_freq_type clocks_freq;
  uint32_t apb_clock, temp_val;
  crm_usart_clock_source_type usart_clk;

  crm_clocks_freq_get(&clocks_freq);

  if(usart_x == USART1)
  {
    usart_clk = crm_usart_clock_get(CRM_USART1);
    if(CRM_USART_CLOCK_SOURCE_PCLK == usart_clk)
    {
      apb_clock = clocks_freq.apb2_freq;
    }
    else if(CRM_USART_CLOCK_SOURCE_SCLK == usart_clk)
    {
      apb_clock = clocks_freq.sclk_freq;
    }
    else if(CRM_USART_CLOCK_SOURCE_LEXT == usart_clk)
    {
      apb_clock = LEXT_VALUE;
    }
    else
    {
      apb_clock = HICK_VALUE;
    }
  }
  else if(usart_x == USART2)
  {
    usart_clk = crm_usart_clock_get(CRM_USART2);
    if(CRM_USART_CLOCK_SOURCE_PCLK == usart_clk)
    {
      apb_clock = clocks_freq.apb1_freq;
    }
    else if(CRM_USART_CLOCK_SOURCE_SCLK == usart_clk)
    {
      apb_clock = clocks_freq.sclk_freq;
    }
    else if(CRM_USART_CLOCK_SOURCE_LEXT == usart_clk)
    {
      apb_clock = LEXT_VALUE;
    }
    else
    {
      apb_clock = HICK_VALUE;
    }
  }
  else if(usart_x == USART3)
  {
    usart_clk = crm_usart_clock_get(CRM_USART3);
    if(CRM_USART_CLOCK_SOURCE_PCLK == usart_clk)
    {
      apb_clock = clocks_freq.apb1_freq;
    }
    else if(CRM_USART_CLOCK_SOURCE_SCLK == usart_clk)
    {
      apb_clock = clocks_freq.sclk_freq;
    }
    else if(CRM_USART_CLOCK_SOURCE_LEXT == usart_clk)
    {
      apb_clock = LEXT_VALUE;
    }
    else
    {
      apb_clock = HICK_VALUE;
    }
  }
  else if(usart_x == USART6)
  {
    apb_clock = clocks_freq.apb2_freq;
  }
  else
  {
    apb_clock = clocks_freq.apb1_freq;
  }

  temp_val = (apb_clock * 10 / baud_rate);
  if((temp_val % 10) < 5)
  {
    temp_val = (temp_val / 10);
  }
  else
  {
    temp_val = (temp_val / 10) + 1;
  }
  usart_x->baudr_bit.div = temp_val;

  if(data_bit == USART_DATA_7BITS)
  {
    usart_x->ctrl1_bit.dbn1 = 1;
    usart_x->ctrl1_bit.dbn0 = 0;
  }
  else if(data_bit == USART_DATA_8BITS)
  {
    usart_x->ctrl1_bit.dbn1 = 0;
    usart_x->ctrl1_bit.dbn0 = 0;
  }
  else
  {
    usart_x->ctrl1_bit.dbn1 = 0;
    usart_x->ctrl1_bit.dbn0 = 1;
  }
  usart_x->ctrl2_bit.stopbn = stop_bit;
}

/**
  * @brief  usart parity selection config.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4 ,USART5, USART6, USART7 or USART8.
  * @param  parity: select the none, odd or even parity.
  *         this parameter can be one of the following values:
  *         - USART_PARITY_NONE
  *         - USART_PARITY_EVEN.
  *         - USART_PARITY_ODD
  * @retval none
  */
void usart_parity_selection_config(usart_type* usart_x, usart_parity_selection_type parity)
{
  if(parity == USART_PARITY_NONE)
  {
    usart_x->ctrl1_bit.psel = FALSE;
    usart_x->ctrl1_bit.pen = FALSE;
  }
  else if(parity == USART_PARITY_EVEN)
  {
    usart_x->ctrl1_bit.psel = FALSE;
    usart_x->ctrl1_bit.pen = TRUE;
  }
  else if(parity == USART_PARITY_ODD)
  {
    usart_x->ctrl1_bit.psel = TRUE;
    usart_x->ctrl1_bit.pen = TRUE;
  }
}

/**
  * @brief  enable or disable the specified usart peripheral.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  new_state: new state of the usart peripheral.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl1_bit.uen = new_state;
}

/**
  * @brief  usart transmitter enable.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4 ,USART5, USART6, USART7 or USART8.
  * @param  new_state: TRUE or FALSE.
  * @retval none
  */
void usart_transmitter_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl1_bit.ten = new_state;
}

/**
  * @brief  usart receiver enable.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4 ,USART5, USART6, USART7 or USART8.
  * @param  new_state: TRUE or FALSE.
  * @retval none
  */
void usart_receiver_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl1_bit.ren = new_state;
}

/**
  * @brief  usart clock config.
  * @note   clock config are not available for USART4, USART5, USART7 and USART8.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3 or USART6.
  * @param  clk_pol: polarity of the clock output on the ck pin.
  *         this parameter can be one of the following values:
  *         - USART_CLOCK_POLARITY_LOW
  *         - USART_CLOCK_POLARITY_HIGH
  * @param  clk_pha: phase of the clock output on the ck pin.
  *         this parameter can be one of the following values:
  *         - USART_CLOCK_PHASE_1EDGE
  *         - USART_CLOCK_PHASE_2EDGE
  * @param  clk_lb: whether the clock pulse of the last data bit transmitted (MSB) is outputted on the ck pin.
  *         this parameter can be one of the following values:
  *         - USART_CLOCK_LAST_BIT_NONE
  *         - USART_CLOCK_LAST_BIT_OUTPUT
  * @retval none
  */
void usart_clock_config(usart_type* usart_x, usart_clock_polarity_type clk_pol, usart_clock_phase_type clk_pha, usart_lbcp_type clk_lb)
{
  usart_x->ctrl2_bit.clkpol = clk_pol;
  usart_x->ctrl2_bit.clkpha = clk_pha;
  usart_x->ctrl2_bit.lbcp = clk_lb;
}

/**
  * @brief  usart enable the ck pin.
  * @note   clock enable are not available for USART4, USART5, USART7 and USART8.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3 or USART6.
  * @param  new_state: TRUE or FALSE
  * @retval none
  */
void usart_clock_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl2_bit.clken = new_state;
}

/**
  * @brief  enable or disable the specified usart interrupts.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  usart_int: specifies the USART interrupt sources to be enabled or disabled.
  *         this parameter can be one of the following values:
  *         - USART_IDLE_INT:  idle interrupt
  *         - USART_RDBF_INT:  rdbf interrupt
  *         - USART_TDC_INT:   tdc interrupt
  *         - USART_TDBE_INT:  tdbe interrupt
  *         - USART_PERR_INT:  perr interrupt
  *         - USART_BF_INT:    break frame interrupt
  *         - USART_ERR_INT:   err interrupt
  *         - USART_CTSCF_INT: ctscf interrupt
  * @param  new_state: new state of the specified usart interrupts.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_interrupt_enable(usart_type* usart_x, uint32_t usart_int, confirm_state new_state)
{
  if(new_state == TRUE)
    PERIPH_REG((uint32_t)usart_x, usart_int) |= PERIPH_REG_BIT(usart_int);
  else
    PERIPH_REG((uint32_t)usart_x, usart_int) &= ~PERIPH_REG_BIT(usart_int);
}

/**
  * @brief  enable or disable the usart's dma transmitter interface.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  new_state: new state of the dma request sources.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_dma_transmitter_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl3_bit.dmaten = new_state;
}

/**
  * @brief  enable or disable the usart's dma receiver interface.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  new_state: new state of the dma request sources.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_dma_receiver_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl3_bit.dmaren = new_state;
}

/**
  * @brief  set the wakeup id of the usart.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  usart_id: the matching id(0x0~0xFF).
  * @retval none
  */
void usart_wakeup_id_set(usart_type* usart_x, uint8_t usart_id)
{
  if(usart_x->ctrl2_bit.idbn == USART_ID_FIXED_4_BIT)
  {
    usart_x->ctrl2_bit.idl = (usart_id & 0x0F);
    usart_x->ctrl2_bit.idh = 0;
  }
  else
  {
    usart_x->ctrl2_bit.idl = (usart_id & 0x0F);
    usart_x->ctrl2_bit.idh = ((usart_id & 0xF0) >> 4);
  }
}

/**
  * @brief  select the usart wakeup method in multi-processor communication.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  wakeup_mode: determines the way to wake up usart method.
  *         this parameter can be one of the following values:
  *         - USART_WAKEUP_BY_IDLE_FRAME
  *         - USART_WAKEUP_BY_MATCHING_ID
  * @retval none
  */
void usart_wakeup_mode_set(usart_type* usart_x, usart_wakeup_mode_type wakeup_mode)
{
  usart_x->ctrl1_bit.wum = wakeup_mode;
}

/**
  * @brief  config the usart in mute mode in multi-processor communication.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  new_state: new state of the usart mute mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_receiver_mute_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl1_bit.rm = new_state;
}

/**
  * @brief  set the usart break frame bit num.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  break_bit: specifies the break bit num.
  *         this parameter can be one of the following values:
  *         - USART_BREAK_10BITS
  *         - USART_BREAK_11BITS
  * @retval none
  */
void usart_break_bit_num_set(usart_type* usart_x, usart_break_bit_num_type break_bit)
{
  usart_x->ctrl2_bit.bfbn = break_bit;
}

/**
  * @brief  enable or disable the usart lin mode.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  new_state: new state of the usart lin mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_lin_mode_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl2_bit.linen = new_state;
}

/**
  * @brief  transmit single data through the usart peripheral.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  data: the data to transmit.
  * @retval none
  */
void usart_data_transmit(usart_type* usart_x, uint16_t data)
{
  usart_x->dt = (data & 0x01FF);
}

/**
  * @brief  return the most recent received data by the usart peripheral.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @retval the received data.
  */
uint16_t usart_data_receive(usart_type* usart_x)
{
  return (uint16_t)(usart_x->dt);
}

/**
  * @brief  transmit break characters.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @retval none
  */
void usart_break_send(usart_type* usart_x)
{
  usart_x->ctrl1_bit.sbf = TRUE;
}

/**
  * @brief  config the specified usart smartcard guard time.
  * @note   The guard time bits are not available for USART4, USART5, USART7 or USART8.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3 or USART6.
  * @param  guard_time_val: specifies the guard time (0x00~0xFF).
  * @retval none
  */
void usart_smartcard_guard_time_set(usart_type* usart_x, uint8_t guard_time_val)
{
  usart_x->gdiv_bit.scgt = guard_time_val;
}

/**
  * @brief  config the irda/smartcard division.
  * @note   the division are not available for USART4, USART5, USART7 or USART8.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3 or USART6.
  * @param  div_val: specifies the division.
  * @retval none
  */
void usart_irda_smartcard_division_set(usart_type* usart_x, uint8_t div_val)
{
  usart_x->gdiv_bit.isdiv = div_val;
}

/**
  * @brief  enable or disable the usart smart card mode.
  * @note   the smart card mode are not available for USART4, USART5, USART7 or USART8.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3 or USART6.
  * @param  new_state: new state of the smart card mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_smartcard_mode_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl3_bit.scmen = new_state;
}

/**
  * @brief  enable or disable nack transmission in smartcard mode.
  * @note   the smart card nack are not available for USART4, USART5, USART7 or USART8.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3 or USART6.
  * @param  new_state: new state of the nack transmission.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_smartcard_nack_set(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl3_bit.scnacken = new_state;
}

/**
  * @brief  enable or disable the usart single line bidirectional half-duplex communication.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  new_state: new state of the single line half-duplex select.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_single_line_halfduplex_select(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl3_bit.slben = new_state;
}

/**
  * @brief  enable or disable the usart's irda interface.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  new_state: new state of the irda mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_irda_mode_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl3_bit.irdaen = new_state;
}

/**
  * @brief  configure the usart's irda low power.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  new_state: new state of the irda mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_irda_low_power_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl3_bit.irdalp = new_state;
}

/**
  * @brief  configure the usart's hardware flow control.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3
  * @param  flow_state: specifies the hardware flow control.
  *         this parameter can be one of the following values:
  *         - USART_HARDWARE_FLOW_NONE
  *         - USART_HARDWARE_FLOW_RTS,
  *         - USART_HARDWARE_FLOW_CTS,
  *         - USART_HARDWARE_FLOW_RTS_CTS
  * @retval none
  */
void usart_hardware_flow_control_set(usart_type* usart_x,usart_hardware_flow_control_type flow_state)
{
  if(flow_state == USART_HARDWARE_FLOW_NONE)
  {
    usart_x->ctrl3_bit.rtsen = FALSE;
    usart_x->ctrl3_bit.ctsen = FALSE;
  }
  else if(flow_state == USART_HARDWARE_FLOW_RTS)
  {
    usart_x->ctrl3_bit.rtsen = TRUE;
    usart_x->ctrl3_bit.ctsen = FALSE;
  }
  else if(flow_state == USART_HARDWARE_FLOW_CTS)
  {
    usart_x->ctrl3_bit.rtsen = FALSE;
    usart_x->ctrl3_bit.ctsen = TRUE;
  }
  else if(flow_state == USART_HARDWARE_FLOW_RTS_CTS)
  {
    usart_x->ctrl3_bit.rtsen = TRUE;
    usart_x->ctrl3_bit.ctsen = TRUE;
  }
}

/**
  * @brief  check whether the specified usart flag is set or not.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  flag: specifies the flag to check.
  *         this parameter can be one of the following values:
  *         - USART_RXON_FLAG:   transmit turned on flag  (not available for USART4,USART5,USART6,USART7 and USART8)
  *         - USART_TXON_FLAG:   receive turned on flag  (not available for USART4,USART5,USART6,USART7 and USART8)
  *         - USART_LPWUF_FLAG:  low power wake up flag  (not available for USART4,USART5,USART6,USART7 and USART8)
  *         - USART_CMDF_FLAG:   character match detection flag  (not available for USART4,USART5,USART6,USART7 and USART8)
  *         - USART_OCCUPY_FLAG: receiver occupy flag (not available for USART4,USART5,USART6,USART7 and USART8)
  *         - USART_RTODF_FLAG:  receiver time out detection flag
  *         - USART_CTSCF_FLAG: cts change flag (not available for USART4,USART5,USART6,USART7 and USART8)
  *         - USART_BFF_FLAG:   break frame flag
  *         - USART_TDBE_FLAG:  transmit data buffer empty flag
  *         - USART_TDC_FLAG:   transmit data complete flag
  *         - USART_RDBF_FLAG:  receive data buffer full flag
  *         - USART_IDLEF_FLAG: idle flag
  *         - USART_ROERR_FLAG: receiver overflow error flag
  *         - USART_NERR_FLAG:  noise error flag
  *         - USART_FERR_FLAG:  framing error flag
  *         - USART_PERR_FLAG:  parity error flag
  * @retval the new state of usart_flag (SET or RESET).
  */
flag_status usart_flag_get(usart_type* usart_x, uint32_t flag)
{
  if(usart_x->sts & flag)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  clear the usart's pending flags.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7 or USART8.
  * @param  flag: specifies the flag to clear.
  *         this parameter can be any combination of the following values:
  *         - USART_LPWUF_FLAG:  low power wake up flag  (not available for USART4,USART5,USART6,USART7 and USART8)
  *         - USART_CMDF_FLAG:   character match detection flag  (not available for USART4,USART5,USART6,USART7 and USART8)
  *         - USART_RTODF_FLAG:  receiver time out detection flag
  *         - USART_CTSCF_FLAG: (not available for USART4,USART5,USART6,USART7 and USART8).
  *         - USART_BFF_FLAG:
  *         - USART_TDC_FLAG:
  *         - USART_RDBF_FLAG:
  *         - USART_PERR_FLAG:
  *         - USART_FERR_FLAG:
  *         - USART_NERR_FLAG:
  *         - USART_ROERR_FLAG:
  *         - USART_IDLEF_FLAG:
  * @note
  *         - USART_PERR_FLAG, USART_FERR_FLAG, USART_NERR_FLAG, USART_ROERR_FLAG and USART_IDLEF_FLAG are cleared by software
  *           sequence: a read operation to usart sts register (usart_flag_get())
  *           followed by a read operation to usart dt register (usart_data_receive()).
  *         - USART_RDBF_FLAG can be also cleared by a read to the usart dt register(usart_data_receive()).
  *         - USART_TDC_FLAG can be also cleared by software sequence: a read operation to usart sts register (usart_flag_get())
  *           followed by a write operation to usart dt register (usart_data_transmit()).
  *         - USART_TDBE_FLAG is cleared only by a write to the usart dt register(usart_data_transmit()).
  * @retval none
  */
void usart_flag_clear(usart_type* usart_x, uint32_t flag)
{
  if(USART_RTODF_FLAG == flag)
  {
    usart_x->ifc = USART_RTODF_FLAG;
  }
  else if(USART_CMDF_FLAG == flag)
  {
    usart_x->ifc = USART_CMDF_FLAG;
  }
  else if(USART_LPWUF_FLAG == flag)
  {
    usart_x->ifc = USART_LPWUF_FLAG;
  }
  else if(flag & (USART_PERR_FLAG | USART_FERR_FLAG | USART_NERR_FLAG | USART_ROERR_FLAG | USART_IDLEF_FLAG))
  {
    UNUSED(usart_x->sts);
    UNUSED(usart_x->dt);
  }
  else
  {
    usart_x->sts = ~flag;
  }
}

/**
  * @brief  configure the usart's rs485 transmit delay time.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3
  * @param  start_delay_time: transmit start delay time.
  * @param  complete_delay_time: transmit complete delay time.
  * @retval none
  */
void usart_rs485_delay_time_config(usart_type* usart_x, uint8_t start_delay_time, uint8_t complete_delay_time)
{
  usart_x->ctrl1_bit.tsdt = start_delay_time;
  usart_x->ctrl1_bit.tcdt = complete_delay_time;
}

/**
  * @brief  swap the usart's transmit receive pin.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7,or USART8.
  * @param  new_state: new state of the usart peripheral.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_transmit_receive_pin_swap(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl2_bit.trpswap = new_state;
}

/**
  * @brief  set the usart's identification bit num.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7,or USART8.
  * @param  id_bit_num: the usart wakeup identification bit num.
  *         this parameter can be: USART_ID_FIXED_4_BIT or USART_ID_RELATED_DATA_BIT.
  * @retval none
  */
void usart_id_bit_num_set(usart_type* usart_x, usart_identification_bit_num_type id_bit_num)
{
  usart_x->ctrl2_bit.idbn = (uint8_t)id_bit_num;
}

/**
  * @brief  set the usart's de polarity.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7,or USART8.
  * @param  de_polarity: the usart de polarity selection.
  *         this parameter can be: USART_DE_POLARITY_HIGH or USART_DE_POLARITY_LOW.
  * @retval none
  */
void usart_de_polarity_set(usart_type* usart_x, usart_de_polarity_type de_polarity)
{
  usart_x->ctrl3_bit.dep = (uint8_t)de_polarity;
}

/**
  * @brief  enable or disable the usart's rs485 mode.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7,or USART8.
  * @param  new_state: new state of the irda mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_rs485_mode_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl3_bit.rs485en = new_state;
}

/**
  * @brief  configure the usart's low power wakeup method.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2 or USART3.
  * @param  wakeup_method: specifies the method of low power wakeup deep sleep.
  *         this parameter can be one of the following values:
  *         - USART_WAKEUP_METHOD_ID
  *         - USART_WAKEUP_METHOD_START
  *         - USART_WAKEUP_METHOD_RDBF
  * @retval none
  */
void usart_low_power_wakeup_set(usart_type* usart_x, usart_wakeup_method_type wakeup_method)
{
  usart_x->ctrl3_bit.lpwum = wakeup_method;
}

/**
  * @brief  enable or disable the usart's deep sleep mode.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2 or USART3.
  * @param  new_state: new state of the usart's deep sleep mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_deep_sleep_mode_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl3_bit.smusen = new_state;
}

/**
  * @brief  enable or disable the usart's most significant bit transmit first.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7,or USART8.
  * @param  new_state: new state of the irda mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_msb_transmit_first_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl2_bit.mtf = new_state;
}

/**
  * @brief  enable or disable the usart's dt register polarity reverse.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7,or USART8.
  * @param  new_state: new state of the irda mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_dt_polarity_reverse(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl2_bit.dtrev = new_state;
}

/**
  * @brief  enable or disable the usart's tx pin polarity reverse.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7,or USART8.
  * @param  new_state: new state of the irda mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_transmit_pin_polarity_reverse(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl2_bit.txrev = new_state;
}

/**
  * @brief  enable or disable the usart's rx pin polarity reverse.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7,or USART8.
  * @param  new_state: new state of the irda mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_receive_pin_polarity_reverse(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl2_bit.rxrev = new_state;
}

/**
  * @brief  enable or disable the usart's receiver timeout detection enable.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7,or USART8.
  * @param  new_state: new state of the irda mode.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void usart_receiver_timeout_detection_enable(usart_type* usart_x, confirm_state new_state)
{
  usart_x->ctrl1_bit.rtoden = new_state;
}

/**
  * @brief  config the usart receiver timeout value.
  * @param  usart_x: select the usart or the uart peripheral.
  *         this parameter can be one of the following values:
  *         USART1, USART2, USART3, USART4, USART5, USART6, USART7,or USART8.
  * @param  time: configure the usart receiver timeout value.
  * @retval none
  */
void usart_receiver_timeout_value_set(usart_type* usart_x, uint32_t time)
{
  usart_x->rtov = time;
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
