/**
  *********************************************************************************
  *
  * @file    ald_nor_lcd.c
  * @brief   EBI_NOR_LCD module driver.
  *
  * @version V1.0
  * @date    25 Dec 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          25 Dec 2019     AE Team         The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  **********************************************************************************
  */

#include "ald_conf.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup NOR_LCD NOR_LCD
  * @brief NOR_LCD driver modules
  * @{
  */
#ifdef ALD_NOR

/** @defgroup NOR_LCD_Private_Variables NOR_LCD Private Variables
  * @{
  */
static uint32_t NORMEMDATWIDTH = NOR_MEMORY_8B;
/**
  * @}
  */

/** @defgroup NOR_LCD_Public_Functions NOR_LCD Public Functions
  * @brief NOR_LCD public functions
  * @{
  */
/** @defgroup NOR_LCD_Public_Functions_Group1 Initialization functions
  * @brief NOR_LCD Initialization functions 
  * @{
 */
/**
  * @brief  Perform the NOR memory Initialization sequence
  * @param  hperh: pointer to a nor_handle_t structure 
  * @param  timing: pointer to NOR control timing structure 
  * @param  ext_timing: pointer to NOR extended mode timing structure    
  * @retval ald status 
  */
ald_status_t ald_nor_init(nor_handle_t *hperh, ald_ebi_nor_sram_timing_t *timing, ald_ebi_nor_sram_timing_t *ext_timing)
{
	if (hperh == NULL)
		return ERROR;
	if (hperh->state == ALD_NOR_STATE_RESET)
		hperh->lock = UNLOCK;

	/* Initialize NOR control Interface */
	ald_ebi_nor_sram_init(hperh->instance, &(hperh->init));
	/* Initialize NOR timing Interface */
	ald_ebi_nor_sram_timing_init(hperh->instance, timing, hperh->init.bank);
	/* Initialize NOR extended mode timing Interface */
	ald_ebi_nor_sram_ext_timing_init(hperh->ext, ext_timing, hperh->init.bank, hperh->init.ext_mode);
	/* Enable the NORSRAM device */
	ald_ebi_nor_sram_enable(hperh->instance, hperh->init.bank);

	/* Initialize NOR Memory Data Width*/
	if (hperh->init.width == EBI_NORSRAM_MEM_BUS_WIDTH_8)
		NORMEMDATWIDTH = NOR_MEMORY_8B;
	else
		NORMEMDATWIDTH = NOR_MEMORY_16B;

	hperh->state = ALD_NOR_STATE_READY;
	return OK;
}

/**
  * @brief  Perform NOR memory De-Initialization sequence
  * @param  hperh: pointer to a nor_handle_t structure 
  * @retval ald status
  */
ald_status_t ald_nor_deinit(nor_handle_t *hperh)
{
	ald_ebi_nor_sram_deinit(hperh->instance, hperh->ext, hperh->init.bank);
	hperh->state = ALD_NOR_STATE_RESET;
	__UNLOCK(hperh);

	return OK;
}
/**
  * @}
  */

/** @defgroup NOR_LCD_Public_Functions_Group2 I/O operation functions
  * @brief NOR_LCD I/O operation functions
  * @{
  */
/**
  * @brief  Read NOR flash IDs
  * @param  hperh: pointer to a nor_handle_t structure
  * @param  id : pointer to NOR ID structure
  * @retval ald status
  */
ald_status_t ald_nor_read_id(nor_handle_t *hperh, nor_id_t *id)
{
	uint32_t devaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NOR_STATE_BUSY)
		return BUSY;

	/* Select the NOR device address */
	if (hperh->init.bank == EBI_NORSRAM_BANK1)
		devaddr = NOR_MEMORY_ADRESS1;
	else if (hperh->init.bank == EBI_NORSRAM_BANK2)
		devaddr = NOR_MEMORY_ADRESS2;
	else if (hperh->init.bank == EBI_NORSRAM_BANK3)
		devaddr = NOR_MEMORY_ADRESS3;
	else
		devaddr = NOR_MEMORY_ADRESS4;

	hperh->state = ALD_NOR_STATE_BUSY;

	/* Send read ID command */
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_THIRD), NOR_CMD_DATA_AUTO_SELECT);

	/* Read the NOR IDs */
	id->m_code       = *(__IO uint16_t *) NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, MC_ADDRESS);
	id->device_code1 = *(__IO uint16_t *) NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, DEVICE_CODE1_ADDR);
	id->device_code2 = *(__IO uint16_t *) NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, DEVICE_CODE2_ADDR);
	id->device_code3 = *(__IO uint16_t *) NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, DEVICE_CODE3_ADDR);

	hperh->state = ALD_NOR_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Returns the NOR memory to Read mode.
  * @param  hperh: pointer to a nor_handle_t structure 
  * @retval ald status
  */
ald_status_t ald_nor_return_readmode(nor_handle_t *hperh)
{
	uint32_t devaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NOR_STATE_BUSY)
		return BUSY;

	/* Select the NOR device address */
	if (hperh->init.bank == EBI_NORSRAM_BANK1)
		devaddr = NOR_MEMORY_ADRESS1;
	else if (hperh->init.bank == EBI_NORSRAM_BANK2)
		devaddr = NOR_MEMORY_ADRESS2;
	else if (hperh->init.bank == EBI_NORSRAM_BANK3)
		devaddr = NOR_MEMORY_ADRESS3;
	else
		devaddr = NOR_MEMORY_ADRESS4;

	NOR_WRITE(devaddr, NOR_CMD_DATA_READ_RESET);
	hperh->state = ALD_NOR_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Read data from NOR memory 
  * @param  hperh: pointer to a nor_handle_t structure
  * @param  addr: pointer to Device address
  * @param  data: pointer to read data  
  * @retval ald status
  */
ald_status_t ald_nor_read(nor_handle_t *hperh, uint32_t *addr, uint16_t *data)
{
	uint32_t devaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NOR_STATE_BUSY)
		return BUSY;

	if (hperh->init.bank == EBI_NORSRAM_BANK1)
		devaddr = NOR_MEMORY_ADRESS1;
	else if (hperh->init.bank == EBI_NORSRAM_BANK2)
		devaddr = NOR_MEMORY_ADRESS2;
	else if (hperh->init.bank == EBI_NORSRAM_BANK3)
		devaddr = NOR_MEMORY_ADRESS3;
	else
		devaddr = NOR_MEMORY_ADRESS4;

	hperh->state = ALD_NOR_STATE_BUSY;

	/* Send read data command */
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
	NOR_WRITE((uint32_t)addr, NOR_CMD_DATA_READ_RESET);

	*data = *(__IO uint32_t *)(uint32_t)addr;
	hperh->state = ALD_NOR_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Program data to NOR memory 
  * @param  hperh: pointer to a nor_handle_t structure 
  * @param  addr: device address
  * @param  data: pointer to the data to write   
  * @retval ald status
  */
ald_status_t ald_nor_program(nor_handle_t *hperh, uint32_t *addr, uint16_t *data)
{
	uint32_t devaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NOR_STATE_BUSY)
		return BUSY;

	/* Select the NOR device address */
	if (hperh->init.bank == EBI_NORSRAM_BANK1)
		devaddr = NOR_MEMORY_ADRESS1;
	else if (hperh->init.bank == EBI_NORSRAM_BANK2)
		devaddr = NOR_MEMORY_ADRESS2;
	else if (hperh->init.bank == EBI_NORSRAM_BANK3)
		devaddr = NOR_MEMORY_ADRESS3;
	else /* EBI_NORSRAM_BANK4 */
		devaddr = NOR_MEMORY_ADRESS4;

	hperh->state = ALD_NOR_STATE_BUSY;

	/* Send program data command */
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_THIRD), NOR_CMD_DATA_PROGRAM);

	/* Write the data */
	NOR_WRITE(addr, *data);
	hperh->state = ALD_NOR_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Reads a block of data from the EBI NOR memory
  * @param  hperh: pointer to a nor_handle_t structure 
  * @param  addr: nor memory internal address to read from
  * @param  data: pointer to the buffer that receives the data read from the 
  *         NOR memory
  * @param  size : number of Half word to read
  * @retval ald status
  */
ald_status_t ald_nor_read_buffer(nor_handle_t *hperh, uint32_t addr, uint16_t *data, uint32_t size)
{
	uint32_t devaddr = 0;

	/* Process Locked */
	__LOCK(hperh);

	if (hperh->state == ALD_NOR_STATE_BUSY)
		return BUSY;

	if (hperh->init.bank == EBI_NORSRAM_BANK1)
		devaddr = NOR_MEMORY_ADRESS1;
	else if (hperh->init.bank == EBI_NORSRAM_BANK2)
		devaddr = NOR_MEMORY_ADRESS2;
	else if (hperh->init.bank == EBI_NORSRAM_BANK3)
		devaddr = NOR_MEMORY_ADRESS3;
	else
		devaddr = NOR_MEMORY_ADRESS4;

	hperh->state = ALD_NOR_STATE_BUSY;

	/* Send read data command */
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
	NOR_WRITE(addr, NOR_CMD_DATA_READ_RESET);

	/* Read buffer */
	while (size > 0) {
		*data++ = *(__IO uint16_t *)addr;
		addr += 2U;
		size--;
	}

	hperh->state = ALD_NOR_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Writes a half-word buffer to the EBI NOR memory
  * @param  hperh: pointer to a nor_handle_t structure
  * @param  addr: nor memory internal address from which the data 
  * @param  data: pointer to source data buffer 
  * @param  size: number of Half words to write  
  * @retval ald status
  */ 
ald_status_t ald_nor_program_buffer(nor_handle_t *hperh, uint32_t addr, uint16_t *data, uint32_t size)
{
	uint16_t * p_currentaddr = (uint16_t *)NULL;
	uint16_t * p_endaddr = (uint16_t *)NULL;
	uint32_t lastloadedaddr = 0, devaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NOR_STATE_BUSY)
		return BUSY;

	if (hperh->init.bank == EBI_NORSRAM_BANK1)
		devaddr = NOR_MEMORY_ADRESS1;
	else if (hperh->init.bank == EBI_NORSRAM_BANK2)
		devaddr = NOR_MEMORY_ADRESS2;
	else if (hperh->init.bank == EBI_NORSRAM_BANK3)
		devaddr = NOR_MEMORY_ADRESS3;
	else
		devaddr = NOR_MEMORY_ADRESS4;

	hperh->state = ALD_NOR_STATE_BUSY;

	/* Initialize variables */
	p_currentaddr  = (uint16_t*)((uint32_t)(addr));
	p_endaddr      = p_currentaddr + (size - 1U);
	lastloadedaddr = (uint32_t)(addr);

	/* Issue unlock command sequence */
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
	/* Write Buffer Load Command */
	NOR_WRITE((uint32_t)(p_currentaddr), NOR_CMD_DATA_BUFFER_AND_PROG);
	NOR_WRITE((uint32_t)(p_currentaddr), (size - 1U));

	/* Load Data into NOR Buffer */
	while (p_currentaddr <= p_endaddr) {
		lastloadedaddr = (uint32_t)p_currentaddr;
		NOR_WRITE(p_currentaddr, *data++);
		p_currentaddr++;
	}

	NOR_WRITE((uint32_t)(lastloadedaddr), NOR_CMD_DATA_BUFFER_AND_PROG_CONFIRM);
	hperh->state = ALD_NOR_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Erase the specified block of the NOR memory 
  * @param  hperh: pointer to a nor_handle_t structure 
  * @param  blkaddr : block to erase address 
  * @param  addr: device address
  * @retval ald status
  */
ald_status_t ald_nor_erase_block(nor_handle_t *hperh, uint32_t blkaddr, uint32_t addr)
{
	uint32_t devaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NOR_STATE_BUSY)
		return BUSY;

	if (hperh->init.bank == EBI_NORSRAM_BANK1)
		devaddr = NOR_MEMORY_ADRESS1;
	else if (hperh->init.bank == EBI_NORSRAM_BANK2)
		devaddr = NOR_MEMORY_ADRESS2;
	else if (hperh->init.bank == EBI_NORSRAM_BANK3)
		devaddr = NOR_MEMORY_ADRESS3;
	else
		devaddr = NOR_MEMORY_ADRESS4;

	hperh->state = ALD_NOR_STATE_BUSY;

	/* Send block erase command sequence */
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_THIRD), NOR_CMD_DATA_CHIP_BLOCK_ERASE_THIRD);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FOURTH), NOR_CMD_DATA_CHIP_BLOCK_ERASE_FOURTH);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FIFTH), NOR_CMD_DATA_CHIP_BLOCK_ERASE_FIFTH);
	NOR_WRITE((uint32_t)(blkaddr + addr), NOR_CMD_DATA_BLOCK_ERASE);

	hperh->state = ALD_NOR_STATE_READY;
	__UNLOCK(hperh);

	return OK;

}

/**
  * @brief  Erase the entire NOR chip.
  * @param  hperh: pointer to a nor_handle_t structure
  * @retval ald status
  */
ald_status_t ald_nor_erase_chip(nor_handle_t *hperh)
{
	uint32_t devaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NOR_STATE_BUSY)
		return BUSY;

	/* Select the NOR device address */
	if (hperh->init.bank == EBI_NORSRAM_BANK1)
		devaddr = NOR_MEMORY_ADRESS1;
	else if (hperh->init.bank == EBI_NORSRAM_BANK2)
		devaddr = NOR_MEMORY_ADRESS2;
	else if (hperh->init.bank == EBI_NORSRAM_BANK3)
		devaddr = NOR_MEMORY_ADRESS3;
	else
		devaddr = NOR_MEMORY_ADRESS4;

	hperh->state = ALD_NOR_STATE_BUSY;

	/* Send NOR chip erase command sequence */
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_THIRD), NOR_CMD_DATA_CHIP_BLOCK_ERASE_THIRD);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FOURTH), NOR_CMD_DATA_CHIP_BLOCK_ERASE_FOURTH);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FIFTH), NOR_CMD_DATA_CHIP_BLOCK_ERASE_FIFTH);
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_SIXTH), NOR_CMD_DATA_CHIP_ERASE);

	hperh->state = ALD_NOR_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Read NOR flash CFI IDs
  * @param  hperh: pointer to a nor_handle_t structure
  * @param  cfi: pointer to NOR CFI IDs structure  
  * @retval ald status
  */
ald_status_t ald_nor_read_cfi(nor_handle_t *hperh, nor_cfi_t *cfi)
{
	uint32_t devaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NOR_STATE_BUSY)
		return BUSY;

	/* Select the NOR device address */
	if (hperh->init.bank == EBI_NORSRAM_BANK1)
		devaddr = NOR_MEMORY_ADRESS1;
	else if (hperh->init.bank == EBI_NORSRAM_BANK2)
		devaddr = NOR_MEMORY_ADRESS2;
	else if (hperh->init.bank == EBI_NORSRAM_BANK3)
		devaddr = NOR_MEMORY_ADRESS3;
	else
		devaddr = NOR_MEMORY_ADRESS4;

	hperh->state = ALD_NOR_STATE_BUSY;
	NOR_WRITE(NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, NOR_CMD_ADDRESS_FIRST_CFI), NOR_CMD_DATA_CFI);

	cfi->cfi_1 = *(__IO uint16_t *) NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, CFI1_ADDRESS);
	cfi->cfi_2 = *(__IO uint16_t *) NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, CFI2_ADDRESS);
	cfi->cfi_3 = *(__IO uint16_t *) NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, CFI3_ADDRESS);
	cfi->cfi_4 = *(__IO uint16_t *) NOR_ADDR_SHIFT(devaddr, NORMEMDATWIDTH, CFI4_ADDRESS);

	hperh->state = ALD_NOR_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}
/**
  * @}
  */

/** @defgroup NOR_LCD_Public_Functions_Group3 Control functions
  * @brief NOR_LCD Control functions
  * @{
  */
/**
  * @brief  Enables dynamically NOR write operation.
  * @param  hperh: pointer to a nor_handle_t structure
  * @retval ald status
  */
ald_status_t ald_nor_write_enable(nor_handle_t *hperh)
{
	__LOCK(hperh);
	/* Enable write operation */
	ald_ebi_nor_sram_write_enable(hperh->instance, hperh->init.bank);
	hperh->state = ALD_NOR_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Disables dynamically NOR write operation.
  * @param  hperh: pointer to a nor_handle_t structure
  * @retval ald status
  */
ald_status_t ald_nor_write_disable(nor_handle_t *hperh)
{
	__LOCK(hperh);
	hperh->state = ALD_NOR_STATE_BUSY;
	/* Disable write operation */
	ald_ebi_nor_sram_write_disable(hperh->instance, hperh->init.bank);
	hperh->state = ALD_NOR_STATE_PROTECTED;
	__UNLOCK(hperh);

	return OK;
}
/**
  * @}
  */

/** @defgroup NOR_LCD_Public_Functions_Group4 State functions
  * @brief NOR_LCD State functions
  * @{
  */
/**
  * @brief  return the NOR controller state
  * @param  hperh: pointer to a nor_handle_t structure 
  * @retval nor controller state
  */
ald_nor_state_t ald_nor_get_state(nor_handle_t *hperh)
{
	return hperh->state;
}

/**
  * @brief  Returns the NOR operation status.
  * @param  hperh: pointer to a nor_handle_t structure    
  * @param  addr: device address
  * @param  timeout: nor progamming timeout
  * @retval nor status
  */
nor_status_t ald_nor_get_status(nor_handle_t *hperh, uint32_t addr, uint32_t timeout)
{
	nor_status_t status = ALD_NOR_STATUS_ONGOING;
	uint16_t tmp_sr1 = 0, tmp_sr2 = 0;
	uint32_t tickstart = 0;

	/* Get tick */
	tickstart = ald_get_tick();
	while ((status != ALD_NOR_STATUS_SUCCESS) && (status != ALD_NOR_STATUS_TIMEOUT)) {
		/* Check for the Timeout */
		if (timeout != ALD_MAX_DELAY) {
			if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout))
				status = ALD_NOR_STATUS_TIMEOUT;
		}

		/* Read NOR status register (DQ6 and DQ5) */
		tmp_sr1 = *(__IO uint16_t *)addr;
		tmp_sr2 = *(__IO uint16_t *)addr;

		/* If DQ6 did not toggle between the two reads then return NOR_Success */
		if ((tmp_sr1 & NOR_MASK_STATUS_DQ6) == (tmp_sr2 & NOR_MASK_STATUS_DQ6))
			return ALD_NOR_STATUS_SUCCESS;

		if ((tmp_sr1 & NOR_MASK_STATUS_DQ5) != NOR_MASK_STATUS_DQ5)
			status = ALD_NOR_STATUS_ONGOING;

		tmp_sr1 = *(__IO uint16_t *)addr;
		tmp_sr2 = *(__IO uint16_t *)addr;

		/* If DQ6 did not toggle between the two reads then return NOR_Success */
		if ((tmp_sr1 & NOR_MASK_STATUS_DQ6) == (tmp_sr2 & NOR_MASK_STATUS_DQ6))
			return ALD_NOR_STATUS_SUCCESS;
		else if ((tmp_sr1 & NOR_MASK_STATUS_DQ5) == NOR_MASK_STATUS_DQ5)
			return ALD_NOR_STATUS_ERROR;
	}

	return status;
}
/**
  * @}
  */
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
