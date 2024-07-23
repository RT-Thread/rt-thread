/**
  **************************************************************************
  * @file     at32f435_437_qspi.c
  * @brief    contain all the functions for qspi firmware library
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

#include "at32f435_437_conf.h"

/** @addtogroup AT32F435_437_periph_driver
  * @{
  */

/** @defgroup QSPI
  * @brief QSPI driver modules
  * @{
  */

#ifdef QSPI_MODULE_ENABLED

/** @defgroup QSPI_private_functions
  * @{
  */

/**
  * @brief  deinitialize the qspi peripheral registers to their default reset values.
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @retval none
  */
void qspi_reset(qspi_type* qspi_x)
{
  if(qspi_x == QSPI1)
  {
    crm_periph_reset(CRM_QSPI1_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_QSPI1_PERIPH_RESET, FALSE);
  }
  else if(qspi_x == QSPI2)
  {
    crm_periph_reset(CRM_QSPI2_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_QSPI2_PERIPH_RESET, FALSE);
  }
}

/**
  * @brief  enable/disable encryption for qspi.
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void qspi_encryption_enable(qspi_type* qspi_x, confirm_state new_state)
{
  qspi_x->ctrl_bit.keyen = new_state;
}

/**
  * @brief  set qspi sck mode.
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_mode: new state to be set
  *         this parameter can be one of the following values:
  *         - QSPI_SCK_MODE_0
  *         - QSPI_SCK_MODE_3
  * @retval none
  */
void qspi_sck_mode_set(qspi_type* qspi_x, qspi_clk_mode_type new_mode)
{
  qspi_x->ctrl_bit.sckmode = new_mode;
}

/**
  * @brief  set qspi clock division
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_clkdiv: new division value
  *         this parameter can be one of the following values:
  *         - QSPI_CLK_DIV_2
  *         - QSPI_CLK_DIV_4
  *         - QSPI_CLK_DIV_6
  *         - QSPI_CLK_DIV_8
  *         - QSPI_CLK_DIV_3
  *         - QSPI_CLK_DIV_5
  *         - QSPI_CLK_DIV_10
  *         - QSPI_CLK_DIV_12
  * @retval none
  */
void qspi_clk_division_set(qspi_type* qspi_x, qspi_clk_div_type new_clkdiv)
{
  qspi_x->ctrl_bit.clkdiv = new_clkdiv;
}

/**
  * @brief  enable/disable cache in xip mode
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_state (TRUE or FALSE)
  *         TRUE: disable cache
  *         FALSE: enable cache
  * @retval none
  */
void qspi_xip_cache_bypass_set(qspi_type* qspi_x, confirm_state new_state)
{
  qspi_x->xip_cmd_w3_bit.bypassc = new_state;
}

/**
  * @brief  enable/disable interrupt when command is completed
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void qspi_interrupt_enable(qspi_type* qspi_x, confirm_state new_state)
{
  qspi_x->ctrl2_bit.cmdie = new_state;
}

/**
  * @brief  get status flags.
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  flag: specifies the flag to check.
  *         this parameter can be one of the following values:
  *         - QSPI_RXFIFORDY_FLAG
  *         - QSPI_TXFIFORDY_FLAG
  *         - QSPI_CMDSTS_FLAG
  * @retval the new state of the flag (SET or RESET).
  */
flag_status qspi_flag_get(qspi_type* qspi_x, uint32_t flag)
{
  flag_status bit_status = RESET;
  switch(flag)
  {
    case QSPI_RXFIFORDY_FLAG:
      bit_status = (flag_status)qspi_x->fifosts_bit.rxfifordy;
      break;
    case QSPI_TXFIFORDY_FLAG:
      bit_status = (flag_status)qspi_x->fifosts_bit.txfifordy;
      break;
    case QSPI_CMDSTS_FLAG:
      bit_status = (flag_status)qspi_x->cmdsts_bit.cmdsts;
      break;
    default:
      break;
  }
  return bit_status;
}

/**
  * @brief  get interrupt flags.
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  flag: only QSPI_CMDSTS_FLAG valid.
  * @retval the new state of the flag (SET or RESET).
  */
flag_status qspi_interrupt_flag_get(qspi_type* qspi_x, uint32_t flag)
{
  if(QSPI_CMDSTS_FLAG != flag)
    return RESET;
  if(qspi_x->cmdsts_bit.cmdsts && qspi_x->ctrl2_bit.cmdie)
    return SET;
  else
    return RESET;
}

/**
  * @brief  clear flags
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  flag: flags to be clear
  *         this parameter can be one of the following values:
  *         - QSPI_CMDSTS_FLAG
  * @retval none
  */
void qspi_flag_clear(qspi_type* qspi_x, uint32_t flag)
{
  qspi_x->cmdsts = QSPI_CMDSTS_FLAG;
}

/**
  * @brief  set dma threshold for dma rx
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_threshold: value to set
  *         this parameter can be one of the following values:
  *         - QSPI_DMA_FIFO_THOD_WORD08
  *         - QSPI_DMA_FIFO_THOD_WORD16
  *         - QSPI_DMA_FIFO_THOD_WORD24
  * @retval none
  */
void qspi_dma_rx_threshold_set(qspi_type* qspi_x, qspi_dma_fifo_thod_type new_threshold)
{
  qspi_x->ctrl2_bit.rxfifo_thod = new_threshold;
}

/**
  * @brief  set dma threshold for dma tx
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_threshold: value to set
  *         this parameter can be one of the following values:
  *         - QSPI_DMA_FIFO_THOD_WORD08
  *         - QSPI_DMA_FIFO_THOD_WORD16
  *         - QSPI_DMA_FIFO_THOD_WORD24
  * @retval none
  */
void qspi_dma_tx_threshold_set(qspi_type* qspi_x, qspi_dma_fifo_thod_type new_threshold)
{
  qspi_x->ctrl2_bit.txfifo_thod = new_threshold;
}

/**
  * @brief  enable/disable dma transfer
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void qspi_dma_enable(qspi_type* qspi_x, confirm_state new_state)
{
  qspi_x->ctrl2_bit.dmaen = new_state;
}

/**
  * @brief  set wip position in status register of flash
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  busy_pos: value to set
  *         this parameter can be one of the following values:
  *         - QSPI_BUSY_OFFSET_0
  *         - QSPI_BUSY_OFFSET_1
  *         - QSPI_BUSY_OFFSET_2
  *         - QSPI_BUSY_OFFSET_3
  *         - QSPI_BUSY_OFFSET_4
  *         - QSPI_BUSY_OFFSET_5
  *         - QSPI_BUSY_OFFSET_6
  *         - QSPI_BUSY_OFFSET_7
  * @retval none
  */
void qspi_busy_config(qspi_type* qspi_x, qspi_busy_pos_type busy_pos)
{
  qspi_x->ctrl_bit.busy = busy_pos;
}

/**
  * @brief  enable xip mode or command-port mode.
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void qspi_xip_enable(qspi_type* qspi_x, confirm_state new_state)
{
  register uint16_t dly=0;
  /* skip if state is no change */
  if(new_state == (confirm_state)(qspi_x->ctrl_bit.xipsel))
  {
    return;
  }

  /* wait until tx fifo is empty*/
  while(qspi_x->fifosts_bit.txfifordy == 0);

  /* make sure IO is transmitted */
  dly = 64;
  while(dly--)
  {
    __NOP();
  }

  /* flush and reset qspi state */
  qspi_x->ctrl_bit.xiprcmdf = 1;

  /* wait until action is finished */
  while(qspi_x->ctrl_bit.abort);

  /* make sure IO is transmitted */
  dly = 64;
  while(dly--)
  {
    __NOP();
  }
  /* set xip mode to new state */
  qspi_x->ctrl_bit.xipsel = new_state;

  /* wait until abort is not set */
  while(qspi_x->ctrl_bit.abort);

  /* wait until cache status valid*/
  if(new_state == TRUE)
  {
    while( qspi_x->xip_cmd_w3_bit.csts );
  }
}

/**
  * @brief  set command-port and qspi_x will start to work
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  qspi_cmd_struct: pointer to qspi cmd structure
  * @retval none
  */
void qspi_cmd_operation_kick(qspi_type* qspi_x, qspi_cmd_type* qspi_cmd_struct)
{
  uint32_t w1_val = 0, w3_val = 0;

  /* config analyse cmd_w0 register */
  qspi_x->cmd_w0 = (uint32_t)qspi_cmd_struct->address_code;

  /* config analyse cmd_w1 register */
  w1_val = (uint32_t)qspi_cmd_struct->address_length;
  w1_val |= (uint32_t)(qspi_cmd_struct->second_dummy_cycle_num << 16);
  w1_val |= (uint32_t)(qspi_cmd_struct->instruction_length << 24);
  w1_val |= (uint32_t)(qspi_cmd_struct->pe_mode_enable << 28);
  qspi_x->cmd_w1 = w1_val;

  /* config analyse cmd_w2 register */
  qspi_x->cmd_w2 = (uint32_t)qspi_cmd_struct->data_counter;

  /* config analyse cmd_w3 register */
  w3_val = (uint32_t)(qspi_cmd_struct->write_data_enable << 1);
  w3_val |= (uint32_t)(qspi_cmd_struct->read_status_enable << 2);
  w3_val |= (uint32_t)(qspi_cmd_struct->read_status_config << 3);
  w3_val |= (uint32_t)(qspi_cmd_struct->operation_mode << 5);
  w3_val |= (uint32_t)(qspi_cmd_struct->pe_mode_operate_code << 16);
  w3_val |= (uint32_t)(qspi_cmd_struct->instruction_code << 24);
  qspi_x->cmd_w3 = w3_val;
}

/**
  * @brief  initial xip mode for qspi_x
  * @param  qspi_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  xip_init_struct: pointer to xip init structure.
  * @retval none.
  */
void qspi_xip_init(qspi_type* qspi_x, qspi_xip_type* xip_init_struct)
{
  uint32_t xc0_val = 0, xc1_val = 0, xc2_val = 0;
  /* config analyse xip_cmd_w0 register */
  xc0_val = (uint32_t)xip_init_struct->read_second_dummy_cycle_num;
  xc0_val |= (uint32_t)(xip_init_struct->read_operation_mode << 8);
  xc0_val |= (uint32_t)(xip_init_struct->read_address_length << 11);
  xc0_val |= (uint32_t)(xip_init_struct->read_instruction_code << 12);
  qspi_x->xip_cmd_w0 = xc0_val;

  /* config analyse xip_cmd_w1 register */
  xc1_val = (uint32_t)xip_init_struct->write_second_dummy_cycle_num;
  xc1_val |= (uint32_t)(xip_init_struct->write_operation_mode << 8);
  xc1_val |= (uint32_t)(xip_init_struct->write_address_length << 11);
  xc1_val |= (uint32_t)(xip_init_struct->write_instruction_code << 12);
  qspi_x->xip_cmd_w1 = xc1_val;

  /* config analyse xip_cmd_w2 register */
  xc2_val = (uint32_t)xip_init_struct->read_data_counter;
  xc2_val |= (uint32_t)(xip_init_struct->read_time_counter << 8);
  xc2_val |= (uint32_t)(xip_init_struct->read_select_mode << 15);
  xc2_val |= (uint32_t)(xip_init_struct->write_data_counter << 16);
  xc2_val |= (uint32_t)(xip_init_struct->write_time_counter << 24);
  xc2_val |= (uint32_t)(xip_init_struct->write_select_mode << 31);
  qspi_x->xip_cmd_w2 = xc2_val;
}

/**
  * @brief  read one byte from qspi device in command mode
  * @param  qspi_x: select the qspi peripheral.
  * @retval 8-bit data.
  */
uint8_t qspi_byte_read(qspi_type* qspi_x)
{
  return qspi_x->dt_u8;
}

/**
  * @brief  read one half-word from qspi device in command mode
  * @param  qspi_x: select the qspi peripheral.
  * @retval 16-bit data.
  */
uint16_t qspi_half_word_read(qspi_type* qspi_x)
{
  return qspi_x->dt_u16;
}

/**
  * @brief  read one word from qspi device in command mode
  * @param  qspi_x: select the qspi peripheral.
  * @retval 32-bit data.
  */
uint32_t qspi_word_read(qspi_type* qspi_x)
{
  return qspi_x->dt;
}

/**
  * @brief  write one byte to qspi device in command mode
  * @param  qspi_x: select the qspi peripheral.
  * @param  value:  8-bit data.
  * @retval none.
  */
void qspi_byte_write(qspi_type* qspi_x, uint8_t value)
{
  qspi_x->dt_u8 = value;
}

/**
  * @brief  write one half-word to qspi device in command mode
  * @param  qspi_x: select the qspi peripheral.
  * @param  value:  16-bit data.
  * @retval none.
  */
void qspi_half_word_write(qspi_type* qspi_x, uint16_t value)
{
  qspi_x->dt_u16 = value;
}

/**
  * @brief  write one word to qspi device in command mode
  * @param  qspi_x: select the qspi peripheral.
  * @param  value:  32-bit data.
  * @retval none.
  */
void qspi_word_write(qspi_type* qspi_x, uint32_t value)
{
  qspi_x->dt = value;
}

/**
  * @brief  enable auto input sampling phase correction
  * @param  qspi_x: select the qspi peripheral.
  * @retval none.
  */
void qspi_auto_ispc_enable(qspi_type* qspi_x)
{
  qspi_x->ctrl3_bit.ispc = TRUE;
  if(qspi_x == QSPI1)
    qspi_x->ctrl3_bit.ispd = 56;
  else if(qspi_x == QSPI2)
    qspi_x->ctrl3_bit.ispd = 50;
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
