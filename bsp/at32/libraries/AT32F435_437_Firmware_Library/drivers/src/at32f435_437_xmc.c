/**
  **************************************************************************
  * @file     at32f435_437_xmc.c
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

#include "at32f435_437_conf.h"

/** @addtogroup AT32F435_437_periph_driver
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
  * @brief  xmc nand flash registers reset
  * @param  xmc_bank
  *         this parameter can be one of the following values:
  *         - XMC_BANK2_NAND
  *         - XMC_BANK3_NAND
  * @retval none
  */
void xmc_nand_reset(xmc_class_bank_type xmc_bank)
{
  /* set the xmc_bank2_nand registers to their reset values */
  if(xmc_bank == XMC_BANK2_NAND)
  {
    XMC_BANK2->bk2ctrl = 0x00000018;
    XMC_BANK2->bk2is = 0x00000040;
    XMC_BANK2->bk2tmgatt = 0xFCFCFCFC;
    XMC_BANK2->bk2tmgmem = 0xFCFCFCFC;
  }
  /* set the xmc_bank3_nand registers to their reset values */
  else
  {
    XMC_BANK3->bk3ctrl = 0x00000018;
    XMC_BANK3->bk3is = 0x00000040;
    XMC_BANK3->bk3tmgatt = 0xFCFCFCFC;
    XMC_BANK3->bk3tmgmem = 0xFCFCFCFC;
  }
}

/**
  * @brief  initialize the xmc nand banks according to the specified
  *         parameters in the xmc_nandinitstruct.
  * @param  xmc_nand_init_struct : pointer to a xmc_nand_init_type
  *         structure that contains the configuration information for the xmc
  *         nand specified banks.
  * @retval none
  */
void xmc_nand_init(xmc_nand_init_type* xmc_nand_init_struct)
{
  uint32_t tempctrl = 0x0;

  /* Set the tempctrl value according to xmc_nand_init_struct parameters */
  tempctrl = (uint32_t)xmc_nand_init_struct->wait_enable |
              xmc_nand_init_struct->bus_type |
              xmc_nand_init_struct->ecc_enable |
              xmc_nand_init_struct->ecc_pagesize |
              (xmc_nand_init_struct->delay_time_cycle << 9) |
              (xmc_nand_init_struct->delay_time_ar << 13) |
              0x00000008;

  /* xmc_bank2_nand registers configuration */
  if(xmc_nand_init_struct->nand_bank == XMC_BANK2_NAND)
  {
    XMC_BANK2->bk2ctrl = tempctrl;
  }
  /* xmc_bank3_nand registers configuration */
  else
  {
    XMC_BANK3->bk3ctrl = tempctrl;
  }
}

/**
  * @brief  initialize the xmc nand banks according to the specified
  *         parameters in the xmc_nandinitstruct.
  * @param  xmc_regular_spacetiming_struct : pointer to a xmc_nand_pccard_timinginit_type
  *         structure that contains the configuration information for the xmc
  *         nand specified banks.
  * @param  xmc_special_spacetiming_struct : pointer to a xmc_nand_pccard_timinginit_type
  *         structure that contains the configuration information for the xmc
  *         nand specified banks.
  * @retval none
  */
void xmc_nand_timing_config(xmc_nand_pccard_timinginit_type* xmc_regular_spacetiming_struct,
                            xmc_nand_pccard_timinginit_type* xmc_special_spacetiming_struct)
{
  uint32_t tempmem = 0x0, tempatt = 0x0;

  /* set the tempmem value according to xmc_nand_init_struct parameters */
  tempmem = (uint32_t)xmc_regular_spacetiming_struct->mem_setup_time |
            (xmc_regular_spacetiming_struct->mem_waite_time << 8) |
            (xmc_regular_spacetiming_struct->mem_hold_time << 16) |
            (xmc_regular_spacetiming_struct->mem_hiz_time << 24);

  /* set the tempatt value according to xmc_nand_init_struct parameters */
  tempatt = (uint32_t)xmc_special_spacetiming_struct->mem_setup_time |
            (xmc_special_spacetiming_struct->mem_waite_time << 8) |
            (xmc_special_spacetiming_struct->mem_hold_time << 16) |
            (xmc_special_spacetiming_struct->mem_hiz_time << 24);
  /* xmc_bank2_nand registers configuration */
  if(xmc_regular_spacetiming_struct->class_bank == XMC_BANK2_NAND)
  {
    XMC_BANK2->bk2tmgatt = tempatt;
    XMC_BANK2->bk2tmgmem = tempmem;
  }
  else
  {
    XMC_BANK3->bk3tmgatt = tempatt;
    XMC_BANK3->bk3tmgmem = tempmem;
  }
}

/**
  * @brief  fill each xmc_nand_init_struct member with its default value.
  * @param  xmc_nand_init_struct: pointer to a xmc_nand_init_type
  *         structure which will be initialized.
  * @retval none
  */
void xmc_nand_default_para_init(xmc_nand_init_type* xmc_nand_init_struct)
{
  /* reset nand init structure parameters values */
  xmc_nand_init_struct->nand_bank = XMC_BANK2_NAND;
  xmc_nand_init_struct->wait_enable = XMC_WAIT_OPERATION_DISABLE;
  xmc_nand_init_struct->bus_type = XMC_BUSTYPE_8_BITS;
  xmc_nand_init_struct->ecc_enable = XMC_ECC_OPERATION_DISABLE;
  xmc_nand_init_struct->ecc_pagesize = XMC_ECC_PAGESIZE_256_BYTES;
  xmc_nand_init_struct->delay_time_cycle = 0x0;
  xmc_nand_init_struct->delay_time_ar = 0x0;
}

/**
  * @brief  fill each xmc_common_spacetiming_struct and xmc_attribute_spacetiming_struct member with its default value.
  * @param  xmc_common_spacetiming_struct: pointer to a xmc_nand_pccard_timinginit_type
  *         structure which will be initialized.
  * @param  xmc_special_spacetiming_struct: pointer to a xmc_nand_pccard_timinginit_type
  *         structure which will be initialized.
  * @retval none
  */
void xmc_nand_timing_default_para_init(xmc_nand_pccard_timinginit_type* xmc_regular_spacetiming_struct,
                                       xmc_nand_pccard_timinginit_type* xmc_special_spacetiming_struct)
{
  xmc_regular_spacetiming_struct->class_bank = XMC_BANK2_NAND;
  xmc_regular_spacetiming_struct->mem_hold_time  = 0xFC;
  xmc_regular_spacetiming_struct->mem_waite_time = 0xFC;
  xmc_regular_spacetiming_struct->mem_setup_time = 0xFC;
  xmc_regular_spacetiming_struct->mem_hiz_time = 0xFC;
  xmc_special_spacetiming_struct->class_bank = XMC_BANK2_NAND;
  xmc_special_spacetiming_struct->mem_hold_time = 0xFC;
  xmc_special_spacetiming_struct->mem_waite_time = 0xFC;
  xmc_special_spacetiming_struct->mem_setup_time = 0xFC;
  xmc_special_spacetiming_struct->mem_hiz_time = 0xFC;
}

/**
  * @brief  enable or disable the specified nand memory bank.
  * @param  xmc_bank: specifies the xmc bank to be used
  *   this parameter can be one of the following values:
  *   - XMC_BANK2_NAND
  *   - XMC_BANK3_NAND
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void xmc_nand_enable(xmc_class_bank_type xmc_bank, confirm_state new_state)
{
  /* enable or disable the nand bank2 by setting the en bit in the bk2ctrl register */
  if(xmc_bank == XMC_BANK2_NAND)
  {
    XMC_BANK2->bk2ctrl_bit.en = new_state;
  }
  /* enable or disable the nand bank3 by setting the en bit in the bk3ctrl register */
  else
  {
    XMC_BANK3->bk3ctrl_bit.en = new_state;
  }
}

/**
  * @brief  enable or disable the xmc nand ecc feature.
  * @param  xmc_bank: specifies the xmc bank to be used
  *   this parameter can be one of the following values:
  *   - XMC_BANK2_NAND
  *   - XMC_BANK3_NAND
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void xmc_nand_ecc_enable(xmc_class_bank_type xmc_bank, confirm_state new_state)
{
  /* enable the selected nand bank2 ecc function by setting the eccen bit in the bk2ctrl register */
  if(xmc_bank == XMC_BANK2_NAND)
  {
    XMC_BANK2->bk2ctrl_bit.eccen = new_state;
  }
  /* enable the selected nand bank3 ecc function by setting the eccen bit in the bk3ctrl register */
  else
  {
    XMC_BANK3->bk3ctrl_bit.eccen = new_state;
  }
}

/**
  * @brief  return the error correction code register value.
  * @param  xmc_bank: specifies the xmc bank to be used
  *   this parameter can be one of the following values:
  *   - XMC_BANK2_NAND
  *   - XMC_BANK3_NAND
  * @retval the error correction code (ecc) value.
  */
uint32_t xmc_ecc_get(xmc_class_bank_type xmc_bank)
{
  uint32_t eccvaule = 0x0;

  /* get the bk2ecc register value */
  if(xmc_bank == XMC_BANK2_NAND)
  {
    eccvaule = XMC_BANK2->bk2ecc;
  }
  /* get the bk3ecc register value */
  else
  {
    eccvaule = XMC_BANK3->bk3ecc;
  }
   /* return the error correction code value */
  return eccvaule;
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
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].clkdiv = xmc_sdram_init_struct->clkdiv;

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
    XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].clkdiv = xmc_sdram_init_struct->clkdiv;

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
  *         - XMC_BANK2_NAND
  *         - XMC_BANK3_NAND
  *         - XMC_BANK4_PCCARD
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
    /* enable the selected xmc_bank2 interrupts */
    if(xmc_bank == XMC_BANK2_NAND)
    {
      XMC_BANK2->bk2is |= xmc_int;
    }
    /* enable the selected xmc_bank3 interrupts */
    else if(xmc_bank == XMC_BANK3_NAND)
    {
      XMC_BANK3->bk3is |= xmc_int;
    }
    /* enable the selected xmc_bank4 interrupts */
    else if(xmc_bank == XMC_BANK4_PCCARD)
    {
      XMC_BANK4->bk4is |= xmc_int;
    }
    /* enable the selected xmc_sdram interrupts */
    else
    {
      XMC_SDRAM->rcnt |= xmc_int;
    }
  }
  else
  {
    /* disable the selected xmc_bank2 interrupts */
    if(xmc_bank == XMC_BANK2_NAND)
    {
      XMC_BANK2->bk2is &= ~xmc_int;
    }
    /* disable the selected xmc_bank3 interrupts */
    else if(xmc_bank == XMC_BANK3_NAND)
    {
      XMC_BANK3->bk3is &= ~xmc_int;
    }
    /* disable the selected xmc_bank4 interrupts */
    else if(xmc_bank == XMC_BANK4_PCCARD)
    {
      XMC_BANK4->bk4is &= ~xmc_int;
    }
    /* disable the selected xmc_sdram interrupts */
    else
    {
      XMC_SDRAM->rcnt &= ~xmc_int;
    }
  }
}

/**
  * @brief  check whether the specified xmc flag is set or not.
  * @param  xmc_bank: specifies the xmc bank to be used
  *         this parameter can be one of the following values:
  *         - XMC_BANK2_NAND
  *         - XMC_BANK3_NAND
  *         - XMC_BANK4_PCCARD
  *         - XMC_BANK5_6_SDRAM
  * @param  xmc_flag: specifies the flag to check.
  *         this parameter can be any combination of the following values:
  *         - XMC_RISINGEDGE_FLAG
  *         - XMC_LEVEL_FLAG
  *         - XMC_FALLINGEDGE_FLAG
  *         - XMC_FEMPT_FLAG
  *         - XMC_BUSY_FLAG
  *         - XMC_ERR_FLAG
  * @retval none
  */
flag_status xmc_flag_status_get(xmc_class_bank_type xmc_bank, xmc_interrupt_flag_type xmc_flag)
{
  flag_status status = RESET;
  uint32_t temp = 0;

  if(xmc_bank == XMC_BANK2_NAND)
  {
    temp = XMC_BANK2->bk2is;
  }
  else if(xmc_bank == XMC_BANK3_NAND)
  {
    temp = XMC_BANK3->bk3is;
  }
  else if(xmc_bank == XMC_BANK4_PCCARD)
  {
    temp = XMC_BANK4->bk4is;
  }
  else
  {
    temp = XMC_SDRAM->sts;
  }
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
  * @brief  check whether the specified xmc interrupt flag is set or not.
  * @param  xmc_bank: specifies the xmc bank to be used
  *         this parameter can be one of the following values:
  *         - XMC_BANK2_NAND
  *         - XMC_BANK3_NAND
  *         - XMC_BANK4_PCCARD
  * @param  xmc_flag: specifies the flag to check.
  *         this parameter can be any combination of the following values:
  *         - XMC_RISINGEDGE_FLAG
  *         - XMC_LEVEL_FLAG
  *         - XMC_FALLINGEDGE_FLAG
  * @retval none
  */
flag_status xmc_interrupt_flag_status_get(xmc_class_bank_type xmc_bank, xmc_interrupt_flag_type xmc_flag)
{
  flag_status status = RESET;

  if(xmc_bank == XMC_BANK2_NAND)
  {
    switch(xmc_flag)
    {
      case XMC_RISINGEDGE_FLAG:
        if(XMC_BANK2->bk2is_bit.reien && XMC_BANK2->bk2is_bit.res)
          status = SET;
        break;

      case XMC_LEVEL_FLAG:
        if(XMC_BANK2->bk2is_bit.feien && XMC_BANK2->bk2is_bit.fes)
          status = SET;
        break;

      case XMC_FALLINGEDGE_FLAG:
        if(XMC_BANK2->bk2is_bit.hlien && XMC_BANK2->bk2is_bit.hls)
          status = SET;
        break;

      default:
        break;
    }
  }
  else if(xmc_bank == XMC_BANK3_NAND)
  {
    switch(xmc_flag)
    {
      case XMC_RISINGEDGE_FLAG:
        if(XMC_BANK3->bk3is_bit.reien && XMC_BANK3->bk3is_bit.res)
          status = SET;
        break;

      case XMC_LEVEL_FLAG:
        if(XMC_BANK3->bk3is_bit.feien && XMC_BANK3->bk3is_bit.fes)
          status = SET;
        break;

      case XMC_FALLINGEDGE_FLAG:
        if(XMC_BANK3->bk3is_bit.hlien && XMC_BANK3->bk3is_bit.hls)
          status = SET;
        break;

      default:
        break;
    }
  }
  else if(xmc_bank == XMC_BANK4_PCCARD)
  {
    switch(xmc_flag)
    {
      case XMC_RISINGEDGE_FLAG:
        if(XMC_BANK4->bk4is_bit.reien && XMC_BANK4->bk4is_bit.res)
          status = SET;
        break;

      case XMC_LEVEL_FLAG:
        if(XMC_BANK4->bk4is_bit.feien && XMC_BANK4->bk4is_bit.fes)
          status = SET;
        break;

      case XMC_FALLINGEDGE_FLAG:
        if(XMC_BANK4->bk4is_bit.hlien && XMC_BANK4->bk4is_bit.hls)
          status = SET;
        break;

      default:
        break;
    }
  }
  /* return the flag status */
  return status;
}

/**
  * @brief  clear the xmc's pending flags.
  * @param  xmc_bank: specifies the xmc bank to be used
  *         this parameter can be one of the following values:
  *         - XMC_BANK2_NAND
  *         - XMC_BANK3_NAND
  *         - XMC_BANK4_PCCARD
  *         - XMC_BANK5_6_SDRAM
  * @param  xmc_flag: specifies the flag to check.
  *         this parameter can be any combination of the following values:
  *         - XMC_RISINGEDGE_FLAG
  *         - XMC_LEVEL_FLAG
  *         - XMC_FALLINGEDGE_FLAG
  *         - XMC_ERR_FLAG
  * @retval none
  */
void xmc_flag_clear(xmc_class_bank_type xmc_bank, xmc_interrupt_flag_type xmc_flag)
{
  __IO uint32_t int_state;
  if(xmc_bank == XMC_BANK2_NAND)
  {
    int_state = XMC_BANK2->bk2is & 0x38; /* keep interrupt state */
    XMC_BANK2->bk2is = (~(xmc_flag | 0x38) | int_state);
  }
  else if(xmc_bank == XMC_BANK3_NAND)
  {
    int_state = XMC_BANK3->bk3is & 0x38; /* keep interrupt state */
    XMC_BANK3->bk3is = (~(xmc_flag | 0x38) | int_state);
  }
  else if(xmc_bank == XMC_BANK4_PCCARD)
  {
    int_state = XMC_BANK4->bk4is & 0x38; /* keep interrupt state */
    XMC_BANK4->bk4is = (~(xmc_flag | 0x38) | int_state);
  }
  else
  {
    XMC_SDRAM->rcnt |= xmc_flag;
  }
}

/**
  * @brief  xmc pc card registers reset
  * @param  none
  * @retval none
  */
void xmc_pccard_reset(void)
{
  /* Set the XMC_Bank4 registers to their reset values */
  XMC_BANK4->bk4ctrl = 0x00000018;
  XMC_BANK4->bk4is = 0x00000000;
  XMC_BANK4->bk4tmgatt = 0xFCFCFCFC;
  XMC_BANK4->bk4tmgio = 0xFCFCFCFC;
  XMC_BANK4->bk4tmgmem = 0xFCFCFCFC;
}

/**
  * @brief  initialize the xmc pccard bank according to the specified
  *         parameters in the xmc_pccard_init_struct.
  * @param  xmc_pccard_init_struct : pointer to a xmc_pccard_init_type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @retval none
  */
void xmc_pccard_init(xmc_pccard_init_type* xmc_pccard_init_struct)
{
  /* set the bk4ctrl register value according to xmc_pccard_init_struct parameters */
  XMC_BANK4->bk4ctrl = (uint32_t)xmc_pccard_init_struct->enable_wait |
                       XMC_BUSTYPE_16_BITS |
                       (xmc_pccard_init_struct->delay_time_cr << 9) |
                       (xmc_pccard_init_struct->delay_time_ar << 13);
}

/**
  * @brief  initialize the xmc pccard bank according to the specified
  *         parameters in the xmc_common_spacetiming_struct/xmc_attribute_spacetiming_struct
  *         and xmc_iospace_timing_struct.
  * @param  xmc_regular_spacetiming_struct : pointer to a xmc_pccard_init_type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @param  xmc_special_spacetiming_struct : pointer to a xmc_pccard_init_type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @param  xmc_iospace_timing_struct : pointer to a xmc_pccard_init_type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @retval none
  */
void xmc_pccard_timing_config(xmc_nand_pccard_timinginit_type* xmc_regular_spacetiming_struct,
                              xmc_nand_pccard_timinginit_type* xmc_special_spacetiming_struct,
                              xmc_nand_pccard_timinginit_type* xmc_iospace_timing_struct)
{
  /* set bk4tmgmem register value according to xmc_regular_spacetiming_struct parameters */
  XMC_BANK4->bk4tmgmem = (uint32_t)xmc_regular_spacetiming_struct->mem_setup_time |
                         (xmc_regular_spacetiming_struct->mem_waite_time << 8) |
                         (xmc_regular_spacetiming_struct->mem_hold_time << 16) |
                         (xmc_regular_spacetiming_struct->mem_hiz_time << 24);

  /* Set bk4tmgatt register value according to xmc_special_spacetiming_struct parameters */
  XMC_BANK4->bk4tmgatt = (uint32_t)xmc_special_spacetiming_struct->mem_setup_time |
                         (xmc_special_spacetiming_struct->mem_waite_time << 8) |
                         (xmc_special_spacetiming_struct->mem_hold_time << 16) |
                         (xmc_special_spacetiming_struct->mem_hiz_time << 24);

  /* Set bk4tmgio register value according to xmc_iospace_timing_struct parameters */
  XMC_BANK4->bk4tmgio = (uint32_t)xmc_iospace_timing_struct->mem_setup_time |
                        (xmc_iospace_timing_struct->mem_waite_time << 8) |
                        (xmc_iospace_timing_struct->mem_hold_time << 16) |
                        (xmc_iospace_timing_struct->mem_hiz_time << 24);
}
/**
  * @brief  fill each xmc_pccard_init_struct member with its default value.
  * @param  xmc_pccard_init_struct: pointer to a xmc_pccardinittype
  *         structure which will be initialized.
  * @retval none
  */
void xmc_pccard_default_para_init(xmc_pccard_init_type* xmc_pccard_init_struct)
{
  /* reset pccard init structure parameters values */
  xmc_pccard_init_struct->enable_wait = XMC_WAIT_OPERATION_DISABLE;
  xmc_pccard_init_struct->delay_time_ar = 0x0;
  xmc_pccard_init_struct->delay_time_cr = 0x0;

}
/**
  * @brief  fill each xmc_common_spacetiming_struct/xmc_attribute_spacetiming_struct
  *         and xmc_iospace_timing_struct member with its default value.
  * @param  xmc_regular_spacetiming_struct : pointer to a xmc_pccard_init_type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @param  xmc_special_spacetiming_struct : pointer to a xmc_pccard_init_type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @param  xmc_iospace_timing_struct : pointer to a xmc_pccard_init_type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @retval none
  */
void xmc_pccard_timing_default_para_init(xmc_nand_pccard_timinginit_type* xmc_regular_spacetiming_struct,
                                         xmc_nand_pccard_timinginit_type* xmc_special_spacetiming_struct,
                                         xmc_nand_pccard_timinginit_type* xmc_iospace_timing_struct)
{
  xmc_regular_spacetiming_struct->class_bank = XMC_BANK4_PCCARD;
  xmc_regular_spacetiming_struct->mem_hold_time  = 0xFC;
  xmc_regular_spacetiming_struct->mem_waite_time = 0xFC;
  xmc_regular_spacetiming_struct->mem_setup_time = 0xFC;
  xmc_regular_spacetiming_struct->mem_hiz_time = 0xFC;
  xmc_special_spacetiming_struct->class_bank = XMC_BANK4_PCCARD;
  xmc_special_spacetiming_struct->mem_hold_time  = 0xFC;
  xmc_special_spacetiming_struct->mem_waite_time = 0xFC;
  xmc_special_spacetiming_struct->mem_setup_time = 0xFC;
  xmc_special_spacetiming_struct->mem_hiz_time = 0xFC;
  xmc_iospace_timing_struct->class_bank = XMC_BANK4_PCCARD;
  xmc_iospace_timing_struct->mem_hold_time = 0xFC;
  xmc_iospace_timing_struct->mem_waite_time = 0xFC;
  xmc_iospace_timing_struct->mem_setup_time = 0xFC;
  xmc_iospace_timing_struct->mem_hiz_time = 0xFC;
}
/**
  * @brief  enable or disable the pccard memory bank.
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void xmc_pccard_enable(confirm_state new_state)
{
  /* enable the pccard bank4 by setting the en bit in the bk4ctrl register */
  XMC_BANK4->bk4ctrl_bit.en = new_state;
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
