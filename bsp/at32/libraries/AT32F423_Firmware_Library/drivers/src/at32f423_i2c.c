/**
  **************************************************************************
  * @file     at32f423_i2c.c
  * @brief    contains all the functions for the i2c firmware library
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

#include "at32f423_conf.h"

/** @addtogroup AT32F423_periph_driver
  * @{
  */

/** @defgroup I2C
  * @brief I2C driver modules
  * @{
  */

#ifdef I2C_MODULE_ENABLED

/** @defgroup I2C_private_functions
  * @{
  */

/**
  * @brief  reset the i2c register
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @retval none
  */
void i2c_reset(i2c_type *i2c_x)
{
  if(i2c_x == I2C1)
  {
    crm_periph_reset(CRM_I2C1_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_I2C1_PERIPH_RESET, FALSE);
  }
  else if(i2c_x == I2C2)
  {
    crm_periph_reset(CRM_I2C2_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_I2C2_PERIPH_RESET, FALSE);
  }
  else if(i2c_x == I2C3)
  {
    crm_periph_reset(CRM_I2C3_PERIPH_RESET, TRUE);
    crm_periph_reset(CRM_I2C3_PERIPH_RESET, FALSE);
  }
}

/**
  * @brief  init i2c digit filters and clock control register.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  dfilters: number of digit filters (0x00~0x0F).
  * @param  clk: i2c clock control register (0x00000000~0xFFFFFFFF).
  * @retval none
  */
void i2c_init(i2c_type *i2c_x, uint8_t dfilters, uint32_t clk)
{
  /* disable i2c peripheral */
  i2c_x->ctrl1_bit.i2cen = FALSE;

  /* write clkctrl register*/
  i2c_x->clkctrl = clk;

  /* write digital filter register*/
  i2c_x->ctrl1_bit.dflt = dfilters;
}

/**
  * @brief  config i2c own address 1.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  mode: i2c address mode.
  *         this parameter can be one of the following values:
  *         - I2C_ADDRESS_MODE_7BIT: 7bit address.
  *         - I2C_ADDRESS_MODE_10BIT: 10bit address.
  * @param  address: own address 1, such as 0xB0.
  * @retval none
  */
void i2c_own_address1_set(i2c_type *i2c_x, i2c_address_mode_type mode, uint16_t address)
{
  /* config address mode */
  i2c_x->oaddr1_bit.addr1mode = mode;

  /* config address */
  i2c_x->oaddr1_bit.addr1 = address & 0x03FF;

  /* enable address */
  i2c_x->oaddr1_bit.addr1en = TRUE;
}

/**
  * @brief  config i2c own address 2 and mask.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  address: own address 1, such as 0xC0.
  * @param  mask: own address 2 mask.
  *         this parameter can be one of the following values:
  *         - I2C_ADDR2_NOMASK: compare bit      [7:1].
  *         - I2C_ADDR2_MASK01: only compare bit [7:2].
  *         - I2C_ADDR2_MASK02: only compare bit [7:3].
  *         - I2C_ADDR2_MASK03: only compare bit [7:4].
  *         - I2C_ADDR2_MASK04: only compare bit [7:5].
  *         - I2C_ADDR2_MASK05: only compare bit [7:6].
  *         - I2C_ADDR2_MASK06: only compare bit [7].
  *         - I2C_ADDR2_MASK07: response all addresses other than those reserved for i2c.
  * @retval none
  */
void i2c_own_address2_set(i2c_type *i2c_x, uint8_t address, i2c_addr2_mask_type mask)
{
  i2c_x->oaddr2_bit.addr2mask = mask;

  i2c_x->oaddr2_bit.addr2 = (address >> 1) & 0x7F;
}

/**
  * @brief  enable or disable own address 2.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_own_address2_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->oaddr2_bit.addr2en = new_state;
}

/**
  * @brief  enable or disable smbus mode.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  mode: smbus device mode.
  *         this parameter can be one of the following values:
  *         - I2C_SMBUS_MODE_DEVICE: smbus device.
  *         - I2C_SMBUS_MODE_HOST: smbus host.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_smbus_enable(i2c_type *i2c_x, i2c_smbus_mode_type mode, confirm_state new_state)
{
  switch (mode)
  {
    case I2C_SMBUS_MODE_DEVICE:
      i2c_x->ctrl1_bit.devaddren = new_state;
      break;
    case I2C_SMBUS_MODE_HOST:
       i2c_x->ctrl1_bit.haddren = new_state;
      break;
    default:
      break;
  }
}

/**
  * @brief  enable or disable peripheral.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl1_bit.i2cen = new_state;
}

/**
  * @brief  enable or disable clock stretch.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_clock_stretch_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl1_bit.stretch = (!new_state);
}

/**
  * @brief  enable or disable ack.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none.
  */
void i2c_ack_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl2_bit.nacken  = (!new_state);
}

/**
  * @brief  enable or disable 10-bit address mode (master transfer).
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_addr10_mode_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl2_bit.addr10 = new_state;
}

/**
  * @brief  config the slave address to be transmitted.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  address: slave address.
  * @retval none
  */
void i2c_transfer_addr_set(i2c_type *i2c_x, uint16_t address)
{
  i2c_x->ctrl2_bit.saddr = address & 0x03FF;
}

/**
  * @brief  get the slave address to be transmitted.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @retval slave address
  */
uint16_t i2c_transfer_addr_get(i2c_type *i2c_x)
{
  return i2c_x->ctrl2_bit.saddr;
}

/**
  * @brief  config the master transfer direction.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  i2c_direction: transfer request direction.
  *         this parameter can be one of the following values:
  *         - I2C_DIR_TRANSMIT: master request a write transfer.
  *         - I2C_DIR_RECEIVE: master request a read transfer.
  * @retval none
  */
void i2c_transfer_dir_set(i2c_type *i2c_x, i2c_transfer_dir_type i2c_direction)
{
  i2c_x->ctrl2_bit.dir = i2c_direction;
}

/**
  * @brief  slave get the i2c transfer direction.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @retval the value of the slave direction
  *         - I2C_DIR_TRANSMIT: master request a write transfer, slave enters receiver mode.
  *         - I2C_DIR_RECEIVE: master request a read transfer, slave enters transmitter mode.
  */
i2c_transfer_dir_type i2c_transfer_dir_get(i2c_type *i2c_x)
{
  if (i2c_x->sts_bit.sdir == 0)
  {
    return I2C_DIR_TRANSMIT;
  }
  else
  {
    return I2C_DIR_RECEIVE;
  }
}

/**
  * @brief  get the i2c slave matched address.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @retval slave matched address.
  */
uint8_t i2c_matched_addr_get(i2c_type *i2c_x)
{
  return (i2c_x->sts_bit.addr << 1);
}

/**
  * @brief  enable or disable auto send stop mode.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_auto_stop_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl2_bit.astopen = new_state;
}

/**
  * @brief  enable or disable cnt reload mode.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_reload_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl2_bit.rlden = new_state;
}

/**
  * @brief  config the transfer cnt .
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  cnt: transfer cnt.
  * @retval none
  */
void i2c_cnt_set(i2c_type *i2c_x, uint8_t cnt)
{
  i2c_x->ctrl2_bit.cnt = cnt;
}

/**
  * @brief  enable or disable read 10-bit header, this mode
  *         only used in 10-bit address mode read.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_addr10_header_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl2_bit.readh10 = new_state;
}

/**
  * @brief  enable or disable general call mode.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_general_call_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl1_bit.gcaen = new_state;
}

/**
  * @brief  drives the smbus alert pin high or low.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  level
  *         this parameter can be one of the following values:
  *         - I2C_SMBUS_ALERT_LOW: smbus alert set low.
  *         - I2C_SMBUS_ALERT_HIGH: smbus alert set high.
  * @retval none
  */
void i2c_smbus_alert_set(i2c_type *i2c_x, i2c_smbus_alert_set_type level)
{
  i2c_x->ctrl1_bit.smbalert = level;
}

/**
  * @brief  enable or disable slave data control.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_slave_data_ctrl_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl1_bit.sctrl = new_state;
}

/**
  * @brief  enable or disable pec calculate.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_pec_calculate_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl1_bit.pecen = new_state;
}

/**
  * @brief  enable or disable pec transfer.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_pec_transmit_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl2_bit.pecten = new_state;
}

/**
  * @brief  get the i2c pec value.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @retval the value of the pec.
  */
uint8_t i2c_pec_value_get(i2c_type *i2c_x)
{
  return (uint8_t)(i2c_x->pec_bit.pecval);
}

/**
  * @brief  config the i2c bus timeout.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  timeout: timeout (0x0000~0x0FFF).
  * @retval none
  */
void i2c_timeout_set(i2c_type *i2c_x, uint16_t timeout)
{
  i2c_x->timeout_bit.totime = timeout;
}

/**
  * @brief  config the bus timeout detcet level.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  level
  *         this parameter can be one of the following values:
  *         - I2C_TIMEOUT_DETCET_HIGH: detect high level timeout.
  *         - I2C_TIMEOUT_DETCET_LOW: detect low level timeout.
  * @retval none
  */
void i2c_timeout_detcet_set(i2c_type *i2c_x, i2c_timeout_detcet_type mode)
{
  i2c_x->timeout_bit.tomode = mode;
}

/**
  * @brief  enable or disable bus timeout.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_timeout_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->timeout_bit.toen = new_state;
}

/**
  * @brief  config the i2c extend bus timeout.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  timeout: extend timeout (0x0000~0x0FFF).
  * @retval none
  */
void i2c_ext_timeout_set(i2c_type *i2c_x, uint16_t timeout)
{
  i2c_x->timeout_bit.exttime = timeout;
}

/**
  * @brief  enable or disable extend bus timeout.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_ext_timeout_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->timeout_bit.exten = new_state;
}

/**
  * @brief  enable or disable interrupts.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  i2c_int: interrupts sources.
  *         this parameter can be one of the following values:
  *         - I2C_TD_INT: transmit data interrupt.
  *         - I2C_RD_INT: receive data interrupt.
  *         - I2C_ADDR_INT: address match interrupt.
  *         - I2C_ACKFIAL_INT: ack fail interrupt.
  *         - I2C_STOP_INT: stop detect interrupt.
  *         - I2C_TDC_INT:  transmit data complete interrupt.
  *         - I2C_ERR_INT: bus error interrupt.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_interrupt_enable(i2c_type *i2c_x, uint32_t source, confirm_state new_state)
{
  if (new_state != FALSE)
  {
    i2c_x->ctrl1 |= source;
  }
  else
  {
    i2c_x->ctrl1 &= (uint32_t)~source;
  }
}

/**
  * @brief  get interrupt status
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  source
  *         this parameter can be one of the following values:
  *         - I2C_TD_INT: transmit data interrupt.
  *         - I2C_RD_INT: receive data interrupt.
  *         - I2C_ADDR_INT: address match interrupt.
  *         - I2C_ACKFIAL_INT: ack fail interrupt.
  *         - I2C_STOP_INT: stop detect interrupt.
  *         - I2C_TDC_INT:  transmit data complete interrupt.
  *         - I2C_ERR_INT: bus error interrupt.
  * @retval flag_status (SET or RESET)
  */
flag_status i2c_interrupt_get(i2c_type *i2c_x, uint16_t source)
{
  if((i2c_x->ctrl1 & source) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  enable or disable dma requests.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  dma_req: dma transfer request.
  *         this parameter can be one of the following values:
  *         - I2C_DMA_REQUEST_TX: dma transmit request.
  *         - I2C_DMA_REQUEST_RX: dma receive request.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_dma_enable(i2c_type *i2c_x, i2c_dma_request_type dma_req, confirm_state new_state)
{
  if(dma_req == I2C_DMA_REQUEST_TX)
  {
    i2c_x->ctrl1_bit.dmaten = new_state;
  }
  else
  {
    i2c_x->ctrl1_bit.dmaren = new_state;
  }
}

/**
  * @brief  config data transfer.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  address: slave address.
  * @param  cnt: transfer conuter(0~255)
  * @param  rld_stop: config reload and gen stop condition mode.
  *         this parameter can be one of the following values:
  *         - I2C_AUTO_STOP_MODE: auto generate stop mode.
  *         - I2C_SOFT_STOP_MODE: soft generate stop mode.
  *         - I2C_RELOAD_MODE:  reload mode.
  * @param  start: config gen start condition mode.
  *         this parameter can be one of the following values:
  *         - I2C_WITHOUT_START: transfer data without start condition.
  *         - I2C_GEN_START_READ: read data and generate start.
  *         - I2C_GEN_START_WRITE: send data and generate start.
  * @retval none
  */
void i2c_transmit_set(i2c_type *i2c_x, uint16_t address, uint8_t cnt, i2c_reload_stop_mode_type rld_stop, i2c_start_mode_type start)
{
  uint32_t temp;

  /* copy ctrl2 value to temp */
  temp = i2c_x->ctrl2;

  /* clear ctrl2_bit specific bits */
  temp &= ~0x03FF67FF;

  /* transfer mode and address set */
  temp |= address | rld_stop | start;

  /* transfer counter set */
  temp |= (uint32_t)cnt << 16;

  /* update ctrl2 value */
  i2c_x->ctrl2 = temp;
}

/**
  * @brief  generate start condition.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @retval none
  */
void i2c_start_generate(i2c_type *i2c_x)
{
  i2c_x->ctrl2_bit.genstart = TRUE;
}

/**
  * @brief  generate stop condition.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @retval none
  */
void i2c_stop_generate(i2c_type *i2c_x)
{
  i2c_x->ctrl2_bit.genstop = TRUE;
}

/**
  * @brief  send a byte through the i2c periph.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  data: byte to be transmitted.
  * @retval none
  */
void i2c_data_send(i2c_type *i2c_x, uint8_t data)
{
  i2c_x->txdt = data;
}

/**
  * @brief  receive a byte through the i2c periph.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @retval the value of the received data.
  */
uint8_t i2c_data_receive(i2c_type *i2c_x)
{
  return (uint8_t)i2c_x->rxdt;
}

/**
  * @brief  get flag status.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  flag: specifies the flag to check.
  *         this parameter can be one of the following values:
  *         - I2C_TDBE_FLAG: transmit data buffer empty flag.
  *         - I2C_TDIS_FLAG: send interrupt status.
  *         - I2C_RDBF_FLAG: receive data buffer full flag.
  *         - I2C_ADDRF_FLAG: 0~7 bit address match flag.
  *         - I2C_ACKFAIL_FLAG: acknowledge failure flag.
  *         - I2C_STOPF_FLAG: stop condition generation complete flag.
  *         - I2C_TDC_FLAG: transmit data complete flag.
  *         - I2C_TCRLD_FLAG: transmission is complete, waiting to load data.
  *         - I2C_BUSERR_FLAG: bus error flag.
  *         - I2C_ARLOST_FLAG: arbitration lost flag.
  *         - I2C_OUF_FLAG: overflow or underflow flag.
  *         - I2C_PECERR_FLAG: pec receive error flag.
  *         - I2C_TMOUT_FLAG: smbus timeout flag.
  *         - I2C_ALERTF_FLAG: smbus alert flag.
  *         - I2C_BUSYF_FLAG: bus busy flag transmission mode.
  *         - I2C_SDIR_FLAG: slave data transmit direction.
  * @retval the new state of flag (SET or RESET).
  */
flag_status i2c_flag_get(i2c_type *i2c_x, uint32_t flag)
{
  if((i2c_x->sts & flag) != RESET)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  get interrupt flag status.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  flag: specifies the flag to check.
  *         this parameter can be one of the following values:
  *         - I2C_TDBE_FLAG: transmit data buffer empty flag.
  *         - I2C_TDIS_FLAG: send interrupt status.
  *         - I2C_RDBF_FLAG: receive data buffer full flag.
  *         - I2C_ADDRF_FLAG: 0~7 bit address match flag.
  *         - I2C_ACKFAIL_FLAG: acknowledge failure flag.
  *         - I2C_STOPF_FLAG: stop condition generation complete flag.
  *         - I2C_TDC_FLAG: transmit data complete flag.
  *         - I2C_TCRLD_FLAG: transmission is complete, waiting to load data.
  *         - I2C_BUSERR_FLAG: bus error flag.
  *         - I2C_ARLOST_FLAG: arbitration lost flag.
  *         - I2C_OUF_FLAG: overflow or underflow flag.
  *         - I2C_PECERR_FLAG: pec receive error flag.
  *         - I2C_TMOUT_FLAG: smbus timeout flag.
  *         - I2C_ALERTF_FLAG: smbus alert flag.
  * @retval the new state of flag (SET or RESET).
  */
flag_status i2c_interrupt_flag_get(i2c_type *i2c_x, uint32_t flag)
{
  __IO uint32_t iten = 0;

  switch(flag)
  {
    case I2C_TDIS_FLAG:
      iten = i2c_x->ctrl1_bit.tdien;
      break;
    case I2C_RDBF_FLAG:
      iten = i2c_x->ctrl1_bit.rdien;
      break;
    case I2C_ADDRF_FLAG:
      iten = i2c_x->ctrl1_bit.addrien;
      break;
    case I2C_ACKFAIL_FLAG:
      iten = i2c_x->ctrl1_bit.ackfailien;
      break;
    case I2C_STOPF_FLAG:
      iten = i2c_x->ctrl1_bit.stopien;
      break;
    case I2C_TDC_FLAG:
    case I2C_TCRLD_FLAG:
      iten = i2c_x->ctrl1_bit.tdcien;
      break;
    case I2C_BUSERR_FLAG:
    case I2C_ARLOST_FLAG:
    case I2C_OUF_FLAG:
    case I2C_PECERR_FLAG:
    case I2C_TMOUT_FLAG:
    case I2C_ALERTF_FLAG:
      iten = i2c_x->ctrl1_bit.errien;
      break;

    default:
      break;
  }

  if(((i2c_x->sts & flag) != RESET) && (iten))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  clear flag status
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1, I2C2, I2C3.
  * @param  flag: specifies the flag to clear.
  *         this parameter can be any combination of the following values:
  *         - I2C_ADDRF_FLAG: 0~7 bit address match flag.
  *         - I2C_ACKFAIL_FLAG: acknowledge failure flag.
  *         - I2C_STOPF_FLAG: stop condition generation complete flag.
  *         - I2C_BUSERR_FLAG: bus error flag.
  *         - I2C_ARLOST_FLAG: arbitration lost flag.
  *         - I2C_OUF_FLAG: overflow or underflow flag.
  *         - I2C_PECERR_FLAG: pec receive error flag.
  *         - I2C_TMOUT_FLAG: smbus timeout flag.
  *         - I2C_ALERTF_FLAG: smbus alert flag.
  * @retval none
  */
void i2c_flag_clear(i2c_type *i2c_x, uint32_t flag)
{
  i2c_x->clr = flag;
}

/**
  * @brief  enable or disable wakeup from deep sleep mode.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_wakeup_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl1_bit.wakeupen = new_state;
}

/**
  * @brief  enable or disable analog filter.
  * @param  i2c_x: to select the i2c peripheral.
  *         this parameter can be one of the following values:
  *         I2C1.
  * @param  new_state (TRUE or FALSE).
  * @retval none
  */
void i2c_analog_filter_enable(i2c_type *i2c_x, confirm_state new_state)
{
  i2c_x->ctrl1_bit.angnfoff = !new_state;
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
