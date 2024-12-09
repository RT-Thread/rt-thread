/**
  **************************************************************************
  * @file     at32f423_xmc.c
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

#include "at32f423_conf.h"

/** @addtogroup AT32F423_periph_driver
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
  XMC_BANK1->ext_bit[xmc_sub_bank].buslatr2r = r2r_timing<<8;
  XMC_BANK1->ext_bit[xmc_sub_bank].buslatw2w = w2w_timing;
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
