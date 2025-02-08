/**
  **************************************************************************
  * @file     at32f45x_xmc.c
  * @brief    contains all the functions for the xmc firmware library
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

/** @defgroup XMC
  * @brief XMC driver modules
  * @{
  */

#ifdef XMC_MODULE_ENABLED

/** @defgroup XMC_private_functions
  * @{
  */

/**
  * @brief  xmc nor or sram registers reset
  * @param  xmc_subbank
  *         this parameter can be one of the following values:
  *         - XMC_BANK1_NOR_SRAM1
  *         - XMC_BANK1_NOR_SRAM2
  *         - XMC_BANK1_NOR_SRAM3
  *         - XMC_BANK1_NOR_SRAM4
  * @retval none
  */
void xmc_nor_sram_reset(xmc_nor_sram_subbank_type xmc_subbank)
{
  /* XMC_BANK1_NORSRAM1 */
  if(xmc_subbank == XMC_BANK1_NOR_SRAM1)
  {
    XMC_BANK1->ctrl_tmg_group[xmc_subbank].bk1ctrl = 0x000030DB;
  }
  /* XMC_BANK1_NORSRAM2,  XMC_BANK1_NORSRAM3 or XMC_BANK1_NORSRAM4 */
  else
  {
    XMC_BANK1->ctrl_tmg_group[xmc_subbank].bk1ctrl = 0x000030D2;
  }
  XMC_BANK1->ctrl_tmg_group[xmc_subbank].bk1tmg = 0x0FFFFFFF;
  XMC_BANK1->tmgwr_group[xmc_subbank].bk1tmgwr = 0x0FFFFFFF;
}

/**
  * @brief  initialize the xmc nor/sram banks according to the specified
  *         parameters in the xmc_norsraminitstruct.
  * @param  xmc_norsram_init_struct : pointer to a xmc_norsram_init_type
  *         structure that contains the configuration information for
  *         the xmc nor/sram specified banks.
  * @retval none
  */
void xmc_nor_sram_init(xmc_norsram_init_type* xmc_norsram_init_struct)
{
  /* bank1 nor/sram control register configuration */
  XMC_BANK1->ctrl_tmg_group[xmc_norsram_init_struct->subbank].bk1ctrl =
  (uint32_t)xmc_norsram_init_struct->data_addr_multiplex |
  xmc_norsram_init_struct->device |
  xmc_norsram_init_struct->bus_type |
  xmc_norsram_init_struct->burst_mode_enable |
  xmc_norsram_init_struct->asynwait_enable |
  xmc_norsram_init_struct->wait_signal_lv |
  xmc_norsram_init_struct->wrapped_mode_enable |
  xmc_norsram_init_struct->wait_signal_config |
  xmc_norsram_init_struct->write_enable |
  xmc_norsram_init_struct->wait_signal_enable |
  xmc_norsram_init_struct->write_timing_enable |
  xmc_norsram_init_struct->write_burst_syn;

  /* if nor flash device */
  if(xmc_norsram_init_struct->device == XMC_DEVICE_NOR)
  {
    XMC_BANK1->ctrl_tmg_group[xmc_norsram_init_struct->subbank].bk1ctrl_bit.noren = 0x1;
  }
}

/**
  * @brief  initialize the xmc nor/sram banks according to the specified
  *         parameters in the xmc_rw_timing_struct and xmc_w_timing_struct.
  * @param  xmc_rw_timing_struct : pointer to a xmc_norsram_timing_init_type
  *         structure that contains the configuration information for
  *         the xmc nor/sram specified banks.
  * @param  xmc_w_timing_struct : pointer to a xmc_norsram_timing_init_type
  *         structure that contains the configuration information for
  *         the xmc nor/sram specified banks.
  * @retval none
  */
void xmc_nor_sram_timing_config(xmc_norsram_timing_init_type* xmc_rw_timing_struct,
                                xmc_norsram_timing_init_type* xmc_w_timing_struct)
{
  /* bank1 nor/sram timing register configuration */
  XMC_BANK1->ctrl_tmg_group[xmc_rw_timing_struct->subbank].bk1tmg =
  (uint32_t)xmc_rw_timing_struct->addr_setup_time |
  (xmc_rw_timing_struct->addr_hold_time << 4) |
  (xmc_rw_timing_struct->data_setup_time << 8) |
  (xmc_rw_timing_struct->bus_latency_time <<16) |
  (xmc_rw_timing_struct->clk_psc << 20) |
  (xmc_rw_timing_struct->data_latency_time << 24) |
  xmc_rw_timing_struct->mode;

  /* bank1 nor/sram timing register for write configuration, if extended mode is used */
  if(xmc_rw_timing_struct->write_timing_enable == XMC_WRITE_TIMING_ENABLE)
  {
    XMC_BANK1->tmgwr_group[xmc_w_timing_struct->subbank].bk1tmgwr =
    (uint32_t)xmc_w_timing_struct->addr_setup_time |
    (xmc_w_timing_struct->addr_hold_time << 4) |
    (xmc_w_timing_struct->data_setup_time << 8) |
    (xmc_w_timing_struct->bus_latency_time << 16) |
    (xmc_w_timing_struct->clk_psc << 20) |
    (xmc_w_timing_struct->data_latency_time << 24) |
    xmc_w_timing_struct->mode;
  }
  else
  {
    XMC_BANK1->tmgwr_group[xmc_w_timing_struct->subbank].bk1tmgwr = 0x0FFFFFFF;
  }
}

/**
  * @brief  fill each xmc_nor_sram_init_struct member with its default value.
  * @param  xmc_nor_sram_init_struct: pointer to a xmc_norsram_init_type
  *         structure which will be initialized.
  * @retval none
  */
void xmc_norsram_default_para_init(xmc_norsram_init_type* xmc_nor_sram_init_struct)
{
  /* reset nor/sram init structure parameters values */
  xmc_nor_sram_init_struct->subbank = XMC_BANK1_NOR_SRAM1;
  xmc_nor_sram_init_struct->data_addr_multiplex = XMC_DATA_ADDR_MUX_ENABLE;
  xmc_nor_sram_init_struct->device = XMC_DEVICE_SRAM;
  xmc_nor_sram_init_struct->bus_type = XMC_BUSTYPE_8_BITS;
  xmc_nor_sram_init_struct->burst_mode_enable = XMC_BURST_MODE_DISABLE;
  xmc_nor_sram_init_struct->asynwait_enable = XMC_ASYN_WAIT_DISABLE;
  xmc_nor_sram_init_struct->wait_signal_lv = XMC_WAIT_SIGNAL_LEVEL_LOW;
  xmc_nor_sram_init_struct->wrapped_mode_enable = XMC_WRAPPED_MODE_DISABLE;
  xmc_nor_sram_init_struct->wait_signal_config = XMC_WAIT_SIGNAL_SYN_BEFORE;
  xmc_nor_sram_init_struct->write_enable = XMC_WRITE_OPERATION_ENABLE;
  xmc_nor_sram_init_struct->wait_signal_enable = XMC_WAIT_SIGNAL_ENABLE;
  xmc_nor_sram_init_struct->write_timing_enable = XMC_WRITE_TIMING_DISABLE;
  xmc_nor_sram_init_struct->write_burst_syn = XMC_WRITE_BURST_SYN_DISABLE;
}

/**
  * @brief  fill each xmc_rw_timing_struct and xmc_w_timing_struct member with its default value.
  * @param  xmc_rw_timing_struct: pointer to a xmc_norsram_timing_init_type
  *         structure which will be initialized.
  * @param  xmc_w_timing_struct: pointer to a xmc_norsram_timing_init_type
  *         structure which will be initialized.
  * @retval none
  */
void xmc_norsram_timing_default_para_init(xmc_norsram_timing_init_type* xmc_rw_timing_struct,
                                          xmc_norsram_timing_init_type* xmc_w_timing_struct)
{
  xmc_rw_timing_struct->subbank = XMC_BANK1_NOR_SRAM1;
  xmc_rw_timing_struct->write_timing_enable = XMC_WRITE_TIMING_DISABLE;
  xmc_rw_timing_struct->addr_setup_time = 0xF;
  xmc_rw_timing_struct->addr_hold_time = 0xF;
  xmc_rw_timing_struct->data_setup_time = 0xFF;
  xmc_rw_timing_struct->bus_latency_time = 0xF;
  xmc_rw_timing_struct->clk_psc = 0xF;
  xmc_rw_timing_struct->data_latency_time = 0xF;
  xmc_rw_timing_struct->mode = XMC_ACCESS_MODE_A;
  xmc_w_timing_struct->subbank = XMC_BANK1_NOR_SRAM1;
  xmc_w_timing_struct->write_timing_enable = XMC_WRITE_TIMING_DISABLE;
  xmc_w_timing_struct->addr_setup_time = 0xF;
  xmc_w_timing_struct->addr_hold_time = 0xF;
  xmc_w_timing_struct->data_setup_time = 0xFF;
  xmc_w_timing_struct->bus_latency_time = 0xF;
  xmc_w_timing_struct->clk_psc = 0xF;
  xmc_w_timing_struct->data_latency_time = 0xF;
  xmc_w_timing_struct->mode = XMC_ACCESS_MODE_A;
}

/**
  * @brief  enable or disable the specified nor/sram memory bank.
  * @param  xmc_subbank
  *         this parameter can be one of the following values:
  *         - XMC_BANK1_NOR_SRAM1
  *         - XMC_BANK1_NOR_SRAM2
  *         - XMC_BANK1_NOR_SRAM3
  *         - XMC_BANK1_NOR_SRAM4
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void xmc_nor_sram_enable(xmc_nor_sram_subbank_type xmc_subbank, confirm_state new_state)
{
  XMC_BANK1->ctrl_tmg_group[xmc_subbank].bk1ctrl_bit.en = new_state;
}

/**
  * @brief  config the bus turnaround phase.
  * @param  xmc_sub_bank
  *         this parameter can be one of the following values:
  *         - XMC_BANK1_NOR_SRAM1
  *         - XMC_BANK1_NOR_SRAM2
  *         - XMC_BANK1_NOR_SRAM3
  *         - XMC_BANK1_NOR_SRAM4
  * @param  w2w_timing :write timing
  * @param  r2r_timing :read timing
  * @retval none
  */
void xmc_ext_timing_config(volatile xmc_nor_sram_subbank_type xmc_sub_bank, uint16_t w2w_timing, uint16_t r2r_timing)
{
  XMC_BANK1->ext_bit[xmc_sub_bank].buslatr2r = r2r_timing;
  XMC_BANK1->ext_bit[xmc_sub_bank].buslatw2w = w2w_timing;
}

/**
  * @brief  xmc sdram registers reset
  * @param  xmc_bank
  *         this parameter can be one of the following values:
  *         - XMC_SDRAM_BANK1
  *         - XMC_SDRAM_BANK2
  * @retval none
  */
void xmc_sdram_reset(xmc_sdram_bank_type xmc_bank)
{
  XMC_SDRAM->ctrl[xmc_bank] = 0x000002D0;
  XMC_SDRAM->tm[xmc_bank]   = 0x0FFFFFFF;
  XMC_SDRAM->cmd            = 0x00000000;
  XMC_SDRAM->rcnt           = 0x00000000;
  XMC_SDRAM->sts            = 0x00000000;
}

/**
  * @brief  initialize the xmc sdram banks according to the specified
  *         parameters in the xmc_sdram_init_struct and xmc_sdram_timing_struct.
  * @param  xmc_sdram_init_struct : pointer to a xmc_sdram_init_type
  *         structure that contains the configuration information for the xmc
  *         sdram specified banks.
  * @param  xmc_sdram_timing_struct : pointer to a xmc_sdram_timing_type
  *         structure that contains the configuration information for the xmc
  *         sdram specified banks.
  * @retval none
  */
void xmc_sdram_init(xmc_sdram_init_type *xmc_sdram_init_struct, xmc_sdram_timing_type *xmc_sdram_timing_struct)
{
  if(xmc_sdram_init_struct->sdram_bank == XMC_SDRAM_BANK1)
  {
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].ca = xmc_sdram_init_struct->column_address;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].ra = xmc_sdram_init_struct->row_address;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].db = xmc_sdram_init_struct->width;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].inbk = xmc_sdram_init_struct->internel_banks;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].cas = xmc_sdram_init_struct->cas;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].wrp = xmc_sdram_init_struct->write_protection;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].bstr = xmc_sdram_init_struct->burst_read;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].rd = xmc_sdram_init_struct->read_delay;
    if(xmc_sdram_init_struct->clkdiv == XMC_CLKDIV_1)
    {
      XMC_SDRAM->clkdiv1 = XMC_CLKDIV_1;
      XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].clkdiv = 0;
    }else
    {
      XMC_SDRAM->clkdiv1 &= ~XMC_CLKDIV_1;
      XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].clkdiv = xmc_sdram_init_struct->clkdiv;
    }

    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].tmrd = xmc_sdram_timing_struct->tmrd;
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].txsr = xmc_sdram_timing_struct->txsr;
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].tras = xmc_sdram_timing_struct->tras;
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].trc = xmc_sdram_timing_struct->trc;
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].twr = xmc_sdram_timing_struct->twr;
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].trp = xmc_sdram_timing_struct->trp;
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].trcd = xmc_sdram_timing_struct->trcd;
  }

  if(xmc_sdram_init_struct->sdram_bank == XMC_SDRAM_BANK2)
  {
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].ca = xmc_sdram_init_struct->column_address;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].ra = xmc_sdram_init_struct->row_address;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].db = xmc_sdram_init_struct->width;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].inbk = xmc_sdram_init_struct->internel_banks;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].cas = xmc_sdram_init_struct->cas;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].wrp = xmc_sdram_init_struct->write_protection;
    /* sdctrl2 bstr is not care */
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].bstr = xmc_sdram_init_struct->burst_read;
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].rd = xmc_sdram_init_struct->read_delay;
    /* sdctrl2 clkdiv is not care */
    if(xmc_sdram_init_struct->clkdiv == XMC_CLKDIV_1)
    {
      XMC_SDRAM->clkdiv1 = XMC_CLKDIV_1;
      XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].clkdiv = 0;
    }else
    {
      XMC_SDRAM->clkdiv1 &= ~XMC_CLKDIV_1;
      XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].clkdiv = xmc_sdram_init_struct->clkdiv;
    }

    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK2].tmrd = xmc_sdram_timing_struct->tmrd;
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK2].txsr = xmc_sdram_timing_struct->txsr;
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK2].tras = xmc_sdram_timing_struct->tras;
    /* sdtm2 trc is not care */
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].trc = xmc_sdram_timing_struct->trc;
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK2].twr = xmc_sdram_timing_struct->twr;
    /* sdtm2 trp is not care */
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].trp = xmc_sdram_timing_struct->trp;
    XMC_SDRAM->tm_bit[XMC_SDRAM_BANK2].trcd = xmc_sdram_timing_struct->trcd;
  }
}

/**
  * @brief  fill each xmc_sdram_init_struct member with its default value.
  * @param  xmc_sdram_init_struct: pointer to a xmc_sdram_init_type
  *         structure which will be initialized.
  * @param  xmc_sdram_timing_struct: pointer to a xmc_sdram_timing_type
  *         structure which will be initialized.
  * @retval none
  */
void xmc_sdram_default_para_init(xmc_sdram_init_type *xmc_sdram_init_struct, xmc_sdram_timing_type *xmc_sdram_timing_struct)
{
  /* reset sdram init structure parameters values */
  xmc_sdram_init_struct->sdram_bank       = XMC_SDRAM_BANK1;
  xmc_sdram_init_struct->internel_banks   = XMC_INBK_4;
  xmc_sdram_init_struct->clkdiv           = XMC_NO_CLK;
  xmc_sdram_init_struct->write_protection = FALSE;
  xmc_sdram_init_struct->burst_read       = FALSE;
  xmc_sdram_init_struct->column_address   = XMC_COLUMN_8;
  xmc_sdram_init_struct->row_address      = XMC_ROW_11;
  xmc_sdram_init_struct->cas              = XMC_CAS_1;
  xmc_sdram_init_struct->width            = XMC_MEM_WIDTH_8;
  xmc_sdram_init_struct->read_delay       = XMC_READ_DELAY_1;

  xmc_sdram_timing_struct->tmrd           = XMC_DELAY_CYCLE_16;
  xmc_sdram_timing_struct->txsr           = XMC_DELAY_CYCLE_16;
  xmc_sdram_timing_struct->tras           = XMC_DELAY_CYCLE_16;
  xmc_sdram_timing_struct->trc            = XMC_DELAY_CYCLE_16;
  xmc_sdram_timing_struct->twr            = XMC_DELAY_CYCLE_16;
  xmc_sdram_timing_struct->trp            = XMC_DELAY_CYCLE_16;
  xmc_sdram_timing_struct->trcd           = XMC_DELAY_CYCLE_16;
}

/**
  * @brief  sdram command confg
  * @param  xmc_sdram_cmd_struct: pointer to a xmc_sdram_cmd_type
  *         structure which will be initialized.
  * @retval none
  */
void xmc_sdram_cmd(xmc_sdram_cmd_type *xmc_sdram_cmd_struct)
{
  XMC_SDRAM->cmd = (xmc_sdram_cmd_struct->auto_refresh << 5) |
                       (xmc_sdram_cmd_struct->data << 9) |
                       xmc_sdram_cmd_struct->cmd |
                       xmc_sdram_cmd_struct->cmd_banks;
}


/**
  * @brief  get sdram bank status
  * @param  xmc_bank: specifies the xmc bank to be used
  *   this parameter can be one of the following values:
  *   - XMC_SDRAM_BANK1
  *   - XMC_SDRAM_BANK1
  * @retval the bank status
  */
uint32_t xmc_sdram_status_get(xmc_sdram_bank_type xmc_bank)
{
  if(xmc_bank == XMC_SDRAM_BANK1)
  {
    return ((XMC_SDRAM->sts >> 1) & XMC_STATUS_MASK);
  }
  else
  {
    return ((XMC_SDRAM->sts >> 3) & XMC_STATUS_MASK);
  }
}

/**
  * @brief  set sdram refresh counter
  * @param  counter: xmc sdram refresh counter
  * @retval none
  */
void xmc_sdram_refresh_counter_set(uint32_t counter)
{
  XMC_SDRAM->rcnt_bit.rc = counter;
}

/**
  * @brief  set sdram auto refresh number
  * @param  number: xmc sdram auto refresh number
  * @retval none
  */
void xmc_sdram_auto_refresh_set(uint32_t number)
{
  XMC_SDRAM->cmd_bit.art = number;
}

/**
  * @brief  enable or disable the specified xmc interrupts.
  * @param  xmc_bank: specifies the xmc bank to be used
  *         this parameter can be one of the following values:
  *         - XMC_BANK5_6_SDRAM
  * @param  xmc_int: specifies the xmc interrupt sources to be enabled or disabled.
  *         this parameter can be any combination of the following values:
  *         - XMC_INT_RISING_EDGE
  *         - XMC_INT_LEVEL
  *         - XMC_INT_FALLING_EDGE
  *         - XMC_INT_ERR
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void xmc_interrupt_enable(xmc_class_bank_type xmc_bank, xmc_interrupt_sources_type xmc_int, confirm_state new_state)
{
  if(new_state != FALSE)
  {
    XMC_SDRAM->rcnt |= xmc_int;
  }
  else
  {
    XMC_SDRAM->rcnt &= ~xmc_int;
  }
}

/**
  * @brief  check whether the specified xmc flag is set or not.
  * @param  xmc_bank: specifies the xmc bank to be used
  *         this parameter can be one of the following values:
  *         - XMC_BANK5_6_SDRAM
  * @param  xmc_flag: specifies the flag to check.
  *         this parameter can be any combination of the following values:
  *         - XMC_BUSY_FLAG
  *         - XMC_ERR_FLAG
  * @retval none
  */
flag_status xmc_flag_status_get(xmc_class_bank_type xmc_bank, xmc_interrupt_flag_type xmc_flag)
{
  flag_status status = RESET;
  uint32_t temp = 0;

  temp = XMC_SDRAM->sts;

  /* get the flag status */
  if((temp & xmc_flag) == RESET)
  {
    status = RESET;
  }
  else
  {
    status = SET;
  }
  /* return the flag status */
  return status;
}

/**
  * @brief  clear the xmc's pending flags.
  * @param  xmc_bank: specifies the xmc bank to be used
  *         this parameter can be one of the following values:
  *         - XMC_BANK5_6_SDRAM
  * @param  xmc_flag: specifies the flag to check.
  *         this parameter can be any combination of the following values:
  *         - XMC_ERR_FLAG
  * @retval none
  */
void xmc_flag_clear(xmc_class_bank_type xmc_bank, xmc_interrupt_flag_type xmc_flag)
{
  XMC_SDRAM->rcnt |= xmc_flag;
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
