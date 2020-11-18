/**
  *********************************************************************************
  *
  * @file    ald_flash.c
  * @brief   FLASH module driver.
  *
  * @version V1.0
  * @date    17 Jun 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  *
  *********************************************************************************
  * @verbatim
  ==============================================================================
                    ##### FLASH Peripheral features #####
  ==============================================================================
  [..]
  Base address is 0x00000000

  [..]
  FLASH have just one programme mode , word programme.
  word programme can programme 8 bytes once ;

  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
  This driver provide private functions for ald_flash_ext.c to use
  @endverbatim
  */

#include "ald_flash.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup FLASH FLASH
  * @brief FLASH module driver
  * @{
  */

#ifdef ALD_FLASH

#if defined ( __ICCARM__ )
#define __RAMFUNC       __ramfunc
#else
#define __RAMFUNC
#endif

/** @defgroup Flash_Private_Variables Flash Private Variables
  * @{
  */
/* global variable*/
static op_cmd_type OP_CMD = OP_FLASH;
/**
  * @}
  */

/** @defgroup Flash_Private_Functions Flash Private Functions
  *  @brief   Flash Private functions
  * @{
  */
/**
  * @brief  Unlock the flash.
  * @retval Status, see @ref ald_status_t.
  */
__RAMFUNC static ald_status_t flash_unlock(void)
{
	uint16_t i;
	uint16_t op_cmd = OP_CMD;

	if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_BUSY_MSK))
		return ERROR;

	FLASH_REG_UNLOCK();
	FLASH_IAP_ENABLE();
	FLASH_REQ();

	for (i = 0; i < 0xFFFF; i++) {
		if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_FLASHACK_MSK))
			break;
	}

	return i == 0xFFFF ? ERROR : OK;
}

/**
  * @brief  Lock the flash.
  * @retval Status, see @ref ald_status_t.
  */
__RAMFUNC static ald_status_t flash_lock(void)
{
	uint16_t i;
	uint16_t op_cmd = OP_CMD;

	FLASH_REG_UNLOCK();
	WRITE_REG(MSC->FLASHCR, 0x0);

	for (i = 0; i < 0xFFFF; i++) {
		if (!(READ_BIT(MSC->FLASHSR, MSC_FLASHSR_FLASHACK_MSK)))
			break;
	}

	return i == 0xFFFF ? ERROR : OK;
}

/**
  * @brief  Erase one page.
  * @param  addr: The erased page's address
  * @retval Status, see @ref ald_status_t.
  */
__RAMFUNC ald_status_t flash_page_erase(uint32_t addr)
{
	uint32_t i;
	uint16_t op_cmd = OP_CMD;

	if (flash_unlock() != OK)
		goto end;

	if (op_cmd == OP_FLASH) {
		CLEAR_BIT(MSC->FLASHADDR, MSC_FLASHADDR_IFREN_MSK);
		MODIFY_REG(MSC->FLASHADDR, MSC_FLASHADDR_ADDR_MSK, FLASH_PAGE_ADDR(addr) << MSC_FLASHADDR_ADDR_POSS);
	}
	else {
		SET_BIT(MSC->FLASHADDR, MSC_FLASHADDR_IFREN_MSK);
		MODIFY_REG(MSC->FLASHADDR, MSC_FLASHADDR_ADDR_MSK, INFO_PAGE_ADDR(addr) << MSC_FLASHADDR_ADDR_POSS);
	}

	WRITE_REG(MSC->FLASHCMD, FLASH_CMD_PE);

	for (i = 0; i < 0xFFFF; i++) {
		if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_BUSY_MSK))
			continue;
		if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_ADDR_OV_MSK))
			goto end;
		if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_WRP_FLAG_MSK))
			goto end;
		if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_SERA_MSK))
			break;
	}

	if (i == 0xFFFF)
		goto end;

	if (flash_lock() == ERROR)
		goto end;

	return OK;
end:
	flash_lock();
	return ERROR;
}

/**
  * @brief  Programme a word.
  * @param  addr: The word's address, it is must word align.
  * @param  data: The 8 bytes data be write.
  * @param  len: The number of data be write.
  * @param  fifo: Choose if use fifo.
  * @retval Status, see @ref ald_status_t.
  */
__RAMFUNC ald_status_t flash_word_program(uint32_t addr, uint32_t *data, uint32_t len, uint32_t fifo)
{
	uint16_t i;
	uint16_t prog_len;
	uint32_t *p_data = data;
	uint16_t op_cmd = OP_CMD;

	if (flash_unlock() != OK)
		goto end;

	if (op_cmd == OP_FLASH)
		CLEAR_BIT(MSC->FLASHADDR, MSC_FLASHADDR_IFREN_MSK);
	else
		SET_BIT(MSC->FLASHADDR, MSC_FLASHADDR_IFREN_MSK);

	MODIFY_REG(MSC->FLASHADDR, MSC_FLASHADDR_ADDR_MSK, addr << MSC_FLASHADDR_ADDR_POSS);
	MODIFY_REG(MSC->FLASHCR, MSC_FLASHCR_FIFOEN_MSK, fifo << MSC_FLASHCR_FIFOEN_POS);

	for (prog_len = 0; prog_len < len; prog_len++) {
		if (fifo) {
			WRITE_REG(MSC->FLASHFIFO, p_data[0]);
			WRITE_REG(MSC->FLASHFIFO, p_data[1]);
		}
		else {
			WRITE_REG(MSC->FLASHDL, p_data[0]);
			WRITE_REG(MSC->FLASHDH, p_data[1]);
			WRITE_REG(MSC->FLASHCMD, FLASH_CMD_WP);
		}

		p_data += 2;

		for (i = 0; i < 0xFFFF; i++) {
			if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_BUSY_MSK))
				continue;
			if (READ_BIT(MSC->FLASHSR, MSC_FLASHSR_PROG_MSK))
				break;
		}
	}
	if (i == 0xFFFF)
		goto end;

	if (flash_lock() == ERROR)
		goto end;

	return OK;
end:
	flash_lock();
	return ERROR;
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
