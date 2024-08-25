/**
  **************************************************************************
  * @file     at32f421_flash.c
  * @brief    contains all the functions for the flash firmware library
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

/** @defgroup FLASH
  * @brief FLASH driver modules
  * @{
  */

#ifdef FLASH_MODULE_ENABLED

/** @defgroup FLASH_private_functions
  * @{
  */

/**
  * @brief  check whether the specified flash flag is set or not.
  * @param  flash_flag: specifies the flash flag to check.
  *         this parameter can be one of flash flag status:
  *         - FLASH_OBF_FLAG
  *         - FLASH_ODF_FLAG
  *         - FLASH_PRGMERR_FLAG
  *         - FLASH_EPPERR_FLAG
  *         - FLASH_USDERR_FLAG
  * @retval the new state of flash_flag (SET or RESET).
  */
flag_status flash_flag_get(uint32_t flash_flag)
{
  flag_status status = RESET;
  uint32_t flag_position;
  flag_position = flash_flag & 0x70000000;
  flash_flag &= 0x8FFFFFFF;
  switch(flag_position)
  {
    case 0x00000000:
      if(FLASH->sts & flash_flag)
        status = SET;
      break;
    case 0x40000000:
      if(FLASH->usd & flash_flag)
        status = SET;
      break;
    default:
      break;
  }
  /* return the new state of flash_flag (SET or RESET) */
  return status;
}

/**
  * @brief  clear the flash flag.
  * @param  flash_flag: specifies the flash flags to clear.
  *         this parameter can be any combination of the following values:
  *         - FLASH_ODF_FLAG
  *         - FLASH_PRGMERR_FLAG
  *         - FLASH_EPPERR_FLAG
  * @retval none
  */
void flash_flag_clear(uint32_t flash_flag)
{
  FLASH->sts = flash_flag;
}

/**
  * @brief  return the flash operation status.
  * @param  none
  * @retval status: the returned value can be: FLASH_OPERATE_BUSY,
  *         FLASH_PROGRAM_ERROR, FLASH_EPP_ERROR or FLASH_OPERATE_DONE.
  */
flash_status_type flash_operation_status_get(void)
{
  flash_status_type flash_status = FLASH_OPERATE_DONE;
  if(FLASH->sts_bit.obf != RESET)
  {
    flash_status = FLASH_OPERATE_BUSY;
  }
  else if(FLASH->sts_bit.prgmerr != RESET)
  {
    flash_status = FLASH_PROGRAM_ERROR;
  }
  else if(FLASH->sts_bit.epperr != RESET)
  {
    flash_status = FLASH_EPP_ERROR;
  }
  else
  {
    flash_status = FLASH_OPERATE_DONE;
  }
  /* return the flash status */
  return flash_status;
}

/**
  * @brief  wait for flash operation complete or timeout.
  * @param  time_out: flash operation timeout
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_operation_wait_for(uint32_t time_out)
{
  flash_status_type status = FLASH_OPERATE_DONE;
  /* check for the flash status */
  status = flash_operation_status_get();

  while((status == FLASH_OPERATE_BUSY) && (time_out != 0x00))
  {
    status = flash_operation_status_get();
    time_out--;
  }
  if(time_out == 0x00)
  {
    status = FLASH_OPERATE_TIMEOUT;
  }
  /* return the status */
  return status;
}

/**
  * @brief  unlock the flash controller.
  * @param  none
  * @retval none
  */
void flash_unlock(void)
{
  FLASH->unlock = FLASH_UNLOCK_KEY1;
  FLASH->unlock = FLASH_UNLOCK_KEY2;
}

/**
  * @brief  lock the flash controller.
  * @param  none
  * @retval none
  */
void flash_lock(void)
{
  FLASH->ctrl_bit.oplk = TRUE;
}

/**
  * @brief  erase a specified flash sector.
  * @param  sector_address: the sector address to be erased.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_sector_erase(uint32_t sector_address)
{
  flash_status_type status = FLASH_OPERATE_DONE;

  FLASH->ctrl_bit.secers = TRUE;
  FLASH->addr = sector_address;
  FLASH->ctrl_bit.erstr = TRUE;

  /* wait for operation to be completed */
  status = flash_operation_wait_for(ERASE_TIMEOUT);

  /* disable the secers bit */
  FLASH->ctrl_bit.secers = FALSE;

  /* return the erase status */
  return status;
}

/**
  * @brief  erase flash all internal sectors.
  * @param  none
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_internal_all_erase(void)
{
  flash_status_type status = FLASH_OPERATE_DONE;

  FLASH->ctrl_bit.bankers = TRUE;
  FLASH->ctrl_bit.erstr = TRUE;

  /* wait for operation to be completed */
  status = flash_operation_wait_for(ERASE_TIMEOUT);

  /* disable the bankers bit */
  FLASH->ctrl_bit.bankers = FALSE;

  /* return the erase status */
  return status;
}

/**
  * @brief  erase the flash user system data.
  * @note   this functions erases all user system data except the fap byte.
  *         when fap high level enabled, can't use this function.
  * @param  none
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_user_system_data_erase(void)
{
  flash_status_type status = FLASH_OPERATE_DONE;
  uint16_t fap_val = FAP_RELIEVE_KEY;
  /* get the flash access protection status */
  if(flash_fap_status_get() != RESET)
  {
    fap_val = 0x0000;
  }

  /* unlock the user system data */
  FLASH->usd_unlock = FLASH_UNLOCK_KEY1;
  FLASH->usd_unlock = FLASH_UNLOCK_KEY2;
  while(FLASH->ctrl_bit.usdulks==RESET);

  /* erase the user system data */
  FLASH->ctrl_bit.usders = TRUE;
  FLASH->ctrl_bit.erstr = TRUE;

  /* wait for operation to be completed */
  status = flash_operation_wait_for(ERASE_TIMEOUT);

  /* disable the usders bit */
  FLASH->ctrl_bit.usders = FALSE;

  if((status == FLASH_OPERATE_DONE) && (fap_val == FAP_RELIEVE_KEY))
  {
    /* enable the user system data programming operation */
    FLASH->ctrl_bit.usdprgm = TRUE;

    /* restore the last flash access protection value */
    USD->fap = (uint16_t)fap_val;

    /* wait for operation to be completed */
    status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);

    /*disable the usdprgm bit */
    FLASH->ctrl_bit.usdprgm = FALSE;
  }

  /* return the erase status */
  return status;
}

/**
  * @brief  program a word at a specified address.
  * @param  address: specifies the address to be programmed, word alignment is recommended.
  * @param  data: specifies the data to be programmed.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_word_program(uint32_t address, uint32_t data)
{
  flash_status_type status = FLASH_OPERATE_DONE;

  FLASH->ctrl_bit.fprgm = TRUE;
  *(__IO uint32_t*)address = data;
  /* wait for operation to be completed */
  status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);

  /* disable the fprgm bit */
  FLASH->ctrl_bit.fprgm = FALSE;

  /* return the program status */
  return status;
}

/**
  * @brief  program a halfword at a specified address.
  * @param  address: specifies the address to be programmed, halfword alignment is recommended.
  * @param  data: specifies the data to be programmed.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_halfword_program(uint32_t address, uint16_t data)
{
  flash_status_type status = FLASH_OPERATE_DONE;

  FLASH->ctrl_bit.fprgm = TRUE;
  *(__IO uint16_t*)address = data;
  /* wait for operation to be completed */
  status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);

  /* disable the fprgm bit */
  FLASH->ctrl_bit.fprgm = FALSE;

  /* return the program status */
  return status;
}

/**
  * @brief  program a byte at a specified address.
  * @param  address: specifies the address to be programmed.
  * @param  data: specifies the data to be programmed.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_byte_program(uint32_t address, uint8_t data)
{
  flash_status_type status = FLASH_OPERATE_DONE;

  FLASH->ctrl_bit.fprgm = TRUE;
  *(__IO uint8_t*)address = data;
  /* wait for operation to be completed */
  status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);

  /* disable the fprgm bit */
  FLASH->ctrl_bit.fprgm = FALSE;

  /* return the program status */
  return status;
}

/**
  * @brief  program a halfword at a specified user system data address.
  * @param  address: specifies the address to be programmed.
  * @param  data: specifies the data to be programmed.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_user_system_data_program(uint32_t address, uint8_t data)
{
  flash_status_type status = FLASH_OPERATE_DONE;

  /* unlock the user system data */
  FLASH->usd_unlock = FLASH_UNLOCK_KEY1;
  FLASH->usd_unlock = FLASH_UNLOCK_KEY2;
  while(FLASH->ctrl_bit.usdulks==RESET);

  /* enable the user system data programming operation */
  FLASH->ctrl_bit.usdprgm = TRUE;
  *(__IO uint16_t*)address = data;

  /* wait for operation to be completed */
  status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);

  /* disable the usdprgm bit */
  FLASH->ctrl_bit.usdprgm = FALSE;

  /* return the user system data program status */
  return status;
}

/**
  * @brief  config erase/program protection for the desired sectors.
  * @param  sector_bits:
  *         the pointer of the address of the sectors to be erase/program protected.
  *         the first 16bits general every bit is used to protect the 4KB bytes. the
  *         bit 31 is used to protect the extension memory.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_epp_set(uint32_t *sector_bits)
{
  uint16_t epp_data[4] = {0xFFFF,0xFFFF,0xFFFF,0xFFFF};
  flash_status_type status = FLASH_OPERATE_DONE;
  sector_bits[0] = (uint32_t)(~sector_bits[0]);
  epp_data[0] = (uint16_t)((sector_bits[0] >> 0) & 0xFF);
  epp_data[1] = (uint16_t)((sector_bits[0] >> 8) & 0xFF);
  epp_data[2] = (uint16_t)((sector_bits[0] >> 16) & 0xFF);
  epp_data[3] = (uint16_t)((sector_bits[0] >> 24) & 0xFF);

  /* unlock the user system data */
  FLASH->usd_unlock = FLASH_UNLOCK_KEY1;
  FLASH->usd_unlock = FLASH_UNLOCK_KEY2;
  while(FLASH->ctrl_bit.usdulks==RESET);

  FLASH->ctrl_bit.usdprgm = TRUE;
  USD->epp0 = epp_data[0];
  /* wait for operation to be completed */
  status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);

  if(status == FLASH_OPERATE_DONE)
  {
    USD->epp1 = epp_data[1];
    /* wait for operation to be completed */
    status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);
  }
  if(status == FLASH_OPERATE_DONE)
  {
    USD->epp2 = epp_data[2];
    /* wait for operation to be completed */
    status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);
  }
  if(status == FLASH_OPERATE_DONE)
  {
    USD->epp3 = epp_data[3];
    /* wait for operation to be completed */
    status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);
  }
  /* disable the usdprgm bit */
  FLASH->ctrl_bit.usdprgm = FALSE;

  /* return the erase/program protection operation status */
  return status;
}

/**
  * @brief  return the flash erase/program protection status.
  * @param  sector_bits: pointer to get the epps register.
  * @retval none
  */
void flash_epp_status_get(uint32_t *sector_bits)
{
  /* return the flash erase/program protection register value */
  sector_bits[0] = (uint32_t)(FLASH->epps);
}

/**
  * @brief  enable or disable the flash access protection.
  * @note   if the user has already programmed the other user system data before calling
  *         this function, must re-program them since this function erase all user system data.
  * @param  new_state: new state of the flash access protection.
  *         this parameter can be: TRUE or FALSE.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_fap_enable(confirm_state new_state)
{
  flash_status_type status = FLASH_OPERATE_DONE;

  /* unlock the user system data */
  FLASH->usd_unlock = FLASH_UNLOCK_KEY1;
  FLASH->usd_unlock = FLASH_UNLOCK_KEY2;
  while(FLASH->ctrl_bit.usdulks==RESET);

  FLASH->ctrl_bit.usders = TRUE;
  FLASH->ctrl_bit.erstr = TRUE;
  /* wait for operation to be completed */
  status = flash_operation_wait_for(ERASE_TIMEOUT);

  /* disable the usders bit */
  FLASH->ctrl_bit.usders = FALSE;

  if(status == FLASH_OPERATE_DONE)
  {
    if(new_state == FALSE)
    {
      /* enable the user system data programming operation */
      FLASH->ctrl_bit.usdprgm = TRUE;
      USD->fap = FAP_RELIEVE_KEY;

      /* Wait for operation to be completed */
      status = flash_operation_wait_for(ERASE_TIMEOUT);

      /* disable the usdprgm bit */
      FLASH->ctrl_bit.usdprgm = FALSE;
    }
  }

  /* return the flash access protection operation status */
  return status;
}

/**
  * @brief  check the flash access protection status.
  * @param  none
  * @retval flash access protection status(SET or RESET)
  */
flag_status flash_fap_status_get(void)
{
  return (flag_status)FLASH->usd_bit.fap;
}

/**
  * @brief  enable or disable the flash access protection high level.
  * @note   if the user has already programmed the other user system data before calling
  *         this function, must re-program them since this function erase all user system data.
  * @param  new_state: new state of the flash access protection high level.
  *         this parameter can be: TRUE or FALSE.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_fap_high_level_enable(confirm_state new_state)
{
  flash_status_type status = FLASH_OPERATE_DONE;

  /* unlock the user system data */
  FLASH->usd_unlock = FLASH_UNLOCK_KEY1;
  FLASH->usd_unlock = FLASH_UNLOCK_KEY2;
  while(FLASH->ctrl_bit.usdulks==RESET);

  if(new_state == FALSE)
  {
    FLASH->ctrl_bit.fap_hl_dis = TRUE;
    /* wait for operation to be completed */
    status = flash_operation_wait_for(ERASE_TIMEOUT);

    FLASH->ctrl_bit.usders = TRUE;
    FLASH->ctrl_bit.erstr = TRUE;
    /* wait for operation to be completed */
    status = flash_operation_wait_for(ERASE_TIMEOUT);

    /* disable the usders bit */
    FLASH->ctrl_bit.usders = FALSE;

    if(status == FLASH_OPERATE_DONE)
    {
      /* enable the user system data programming operation */
      FLASH->ctrl_bit.usdprgm = TRUE;
      USD->fap = FAP_RELIEVE_KEY;

      /* wait for operation to be completed */
      status = flash_operation_wait_for(ERASE_TIMEOUT);

      /* disable the usdprgm bit */
      FLASH->ctrl_bit.usdprgm = FALSE;
    }
  }
  else
  {
    FLASH->ctrl_bit.usders = TRUE;
    FLASH->ctrl_bit.erstr = TRUE;
    /* wait for operation to be completed */
    status = flash_operation_wait_for(ERASE_TIMEOUT);

    /* disable the usders bit */
    FLASH->ctrl_bit.usders = FALSE;

    if(status == FLASH_OPERATE_DONE)
    {
      /* enable the user system data programming operation */
      FLASH->ctrl_bit.usdprgm = TRUE;
      USD->fap = FAP_HIGH_LEVEL_KEY;

      /* wait for operation to be completed */
      status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);

      /* disable the usdprgm bit */
      FLASH->ctrl_bit.usdprgm = FALSE;
    }
  }

  /* return the flash access protection operation status */
  return status;
}

/**
  * @brief  check the flash access protection high level status.
  * @param  none
  * @retval flash access protection high level status(SET or RESET)
  */
flag_status flash_fap_high_level_status_get(void)
{
  return (flag_status)FLASH->usd_bit.fap_hl;
}

/**
  * @brief  program the flash system setting byte in usd: wdt_ato_en / depslp_rst / stdby_rst / boot1.
  * @param  usd_ssb: the system setting byte
  * @note   this parameter usd_ssb must contain a combination of all the following 4 types of data
  *         type 1: wdt_ato_en, select the wdt auto start
  *         this data can be one of the following values:
  *         - USD_WDT_ATO_DISABLE: disable wdt auto start
  *         - USD_WDT_ATO_ENABLE: enable wdt auto start
  *         type 2: depslp_rst, reset event when entering deepsleep mode.
  *         this data can be one of the following values:
  *         - USD_DEPSLP_NO_RST: no reset generated when entering in deepsleep
  *         - USD_DEPSLP_RST: reset generated when entering in deepsleep
  *         type 3: stdby_rst, reset event when entering standby mode.
  *         this data can be one of the following values:
  *         - USD_STDBY_NO_RST: no reset generated when entering in standby
  *         - USD_STDBY_RST: reset generated when entering in standby
  *         type 4: boot1, at startup, when boot0 pin is high level, selected the device boot from bootmem/sram.
  *         this data can be one of the following values:
  *         - USD_BOOT1_LOW: when boot0 is high level, boot from bootmem
  *         - USD_BOOT1_HIGH: when boot0 is high level, boot from sram
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_ssb_set(uint8_t usd_ssb)
{
  flash_status_type status = FLASH_OPERATE_DONE;

  /* unlock the user system data */
  FLASH->usd_unlock = FLASH_UNLOCK_KEY1;
  FLASH->usd_unlock = FLASH_UNLOCK_KEY2;
  while(FLASH->ctrl_bit.usdulks==RESET);

  /* enable the user system data programming operation */
  FLASH->ctrl_bit.usdprgm = TRUE;

  USD->ssb = usd_ssb;
  /* wait for operation to be completed */
  status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);

  /* disable the usdprgm bit */
  FLASH->ctrl_bit.usdprgm = FALSE;

  /* return the user system data program status */
  return status;
}

/**
  * @brief  return the flash system setting byte status.
  * @param  none
  * @retval values from flash_usd register: wdt_ato_en(bit0), depslp_rst(bit1),
  *         stdby_rst(bit2) and boot1(bit4).
  */
uint8_t flash_ssb_status_get(void)
{
  /* return the system setting byte status */
  return (uint8_t)(FLASH->usd >> 2);
}

/**
  * @brief  enable or disable the specified flash interrupts.
  * @param  flash_int: specifies the flash interrupt sources to be enabled or disabled.
  *         this parameter can be any combination of the following values:
  *         - FLASH_ERR_INT
  *         - FLASH_ODF_INT
  * @param  new_state: new state of the specified flash interrupts.
  *         this parameter can be: TRUE or FALSE.
  * @retval none
  */
void flash_interrupt_enable(uint32_t flash_int, confirm_state new_state)
{
  if(flash_int & FLASH_ERR_INT)
    FLASH->ctrl_bit.errie = new_state;
  if(flash_int & FLASH_ODF_INT)
    FLASH->ctrl_bit.odfie = new_state;
}

/**
  * @brief  enable main block security library function.
  * @param  pwd: slib password
  *         start_sector: security library start sector
  *         inst_start_sector: security library i-bus area start sector
  *         end_sector: security library end sector
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_slib_enable(uint32_t pwd, uint16_t start_sector, uint16_t inst_start_sector, uint16_t end_sector)
{
  uint32_t slib_range;
  flash_status_type status = FLASH_OPERATE_DONE;

  /*check range param limits*/
  if((start_sector > inst_start_sector) || ((inst_start_sector > end_sector) && \
     (inst_start_sector != 0x7FF)) || (start_sector > end_sector))
    return FLASH_PROGRAM_ERROR;

  /* unlock slib cfg register */
  FLASH->slib_unlock = SLIB_UNLOCK_KEY;
  while(FLASH->slib_misc_sts_bit.slib_ulkf==RESET);

  slib_range = ((uint32_t)(inst_start_sector << 11) & FLASH_SLIB_INST_START_SECTOR) | \
               ((uint32_t)(end_sector << 22) & FLASH_SLIB_END_SECTOR) | \
               (start_sector & FLASH_SLIB_START_SECTOR);
  /* configure slib, set pwd and range */
  FLASH->slib_set_pwd = pwd;
  status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);
  if(status == FLASH_OPERATE_DONE)
  {
    FLASH->slib_set_range = slib_range;
    status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);
  }

  return status;
}

/**
  * @brief  disable main block slib when slib enabled.
  * @param  pwd: slib password
  * @retval success or error
  */
error_status flash_slib_disable(uint32_t pwd)
{
  flash_status_type status = FLASH_OPERATE_DONE;
  /* write password to disable slib */
  FLASH->slib_pwd_clr = pwd;

  status = flash_operation_wait_for(ERASE_TIMEOUT);
  if(status == FLASH_OPERATE_DONE)
  {
    if(FLASH->slib_misc_sts_bit.slib_pwd_ok)
      return SUCCESS;
    else
      return ERROR;
  }
  return ERROR;
}

/**
  * @brief  get the main block slib state.
  * @param  none
  * @retval SET or RESET
  */
flag_status flash_slib_state_get(void)
{
  if(FLASH->slib_sts0_bit.slib_enf)
    return SET;
  else
    return RESET;
}

/**
 * @brief  get the main block start sector of slib.
 * @param  none
 * @retval uint16_t
 */
uint16_t flash_slib_start_sector_get(void)
{
  return (uint16_t)FLASH->slib_sts1_bit.slib_ss;
}

/**
 * @brief  get the main block inst start sector of slib.
 * @param  none
 * @retval uint16_t
 */
uint16_t flash_slib_inststart_sector_get(void)
{
  return (uint16_t)FLASH->slib_sts1_bit.slib_inst_ss;
}

/**
 * @brief  get the main block end sector of slib.
 * @param  none
 * @retval uint16_t
 */
uint16_t flash_slib_end_sector_get(void)
{
  return (uint16_t)FLASH->slib_sts1_bit.slib_es;
}

/**
  * @brief  flash crc calibration.
  * @param  start_addr: crc calibration start sector address
  *         sector_cnt: crc calibration sector count
  * @retval uint32: crc calibration result
  */
uint32_t flash_crc_calibrate(uint32_t start_addr, uint32_t sector_cnt)
{
  FLASH->crc_addr = start_addr;
  FLASH->crc_ctrl = sector_cnt | 0x10000;
  flash_operation_wait_for(OPERATION_TIMEOUT);
  return FLASH->crc_chkr;
}

/**
  * @brief  enable boot memory as extension mode.
  * @note   this function is irreversible, can not disable!!!
  * @param  none
  * @retval none.
  */
void flash_boot_memory_extension_mode_enable(void)
{
  if(FLASH->slib_sts0_bit.btm_ap_enf == RESET)
  {
    FLASH->slib_unlock = SLIB_UNLOCK_KEY;
    while(FLASH->slib_misc_sts_bit.slib_ulkf==RESET);
    FLASH->btm_mode_set = 0;
    flash_operation_wait_for(OPERATION_TIMEOUT);
  }
}

/**
  * @brief  enable extension memory security library function.
  * @param  pwd: slib password
  *         inst_start_sector: extension memory security library i-bus area start sector, range 0~3 or 0xFF
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
flash_status_type flash_extension_memory_slib_enable(uint32_t pwd, uint16_t inst_start_sector)
{
  flash_status_type status = FLASH_OPERATE_DONE;

  /* unlock slib cfg register */
  FLASH->slib_unlock = SLIB_UNLOCK_KEY;
  while(FLASH->slib_misc_sts_bit.slib_ulkf==RESET);

  /* configure slib, set pwd and range */
  FLASH->slib_set_pwd = pwd;
  status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);
  if(status == FLASH_OPERATE_DONE)
  {
    FLASH->em_slib_set  = (uint32_t)(inst_start_sector << 16) + (uint32_t)0x5AA5;
    status = flash_operation_wait_for(PROGRAMMING_TIMEOUT);
  }

  return status;
}

/**
  * @brief  get the extension memory slib state.
  * @param  none
  * @retval SET or RESET
  */
flag_status flash_extension_memory_slib_state_get(void)
{
  if(FLASH->slib_sts0_bit.em_slib_enf)
    return SET;
  else
    return RESET;
}

/**
 * @brief  get the extension memory inst start sector of slib.
 * @param  none
 * @retval uint16_t
 */
uint16_t flash_em_slib_inststart_sector_get(void)
{
  return (uint16_t)FLASH->slib_sts0_bit.em_slib_inst_ss;
}

/**
 * @brief  config flash low power mode enable or disable.
 *         if enabled, when system entry deep sleep mode, flash also entry low power mode.
 * @param  new_state: new state of the flash low power mode.
 *         this parameter can be: TRUE or FALSE.
 * @retval none
 */
void flash_low_power_mode_enable(confirm_state new_state)
{
  FLASH->ctrl_bit.lpmen = new_state;
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
