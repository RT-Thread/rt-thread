/**
  *********************************************************************************
  *
  * @file    ald_nand.c
  * @brief   NAND module driver.
  *
  * @version V1.0
  * @date    18 March 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  * @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================   
    [..]
	This driver is used as follows:
      (#) NAND flash memory configuration sequence using the function ald_nand_init() 
          with control and timing parameters for both common and attribute spaces.  
      (#) Read NAND flash memory maker and device IDs using the function
          ald_nand_read_id(). The read information is stored in the nand_id_typedef 
          structure declared by the function caller. 
      (#) Access NAND flash memory by read/write operations using the functions
          ald_nand_read_page_8b()/nand_read_SpareArea_8b(), 
          ald_nand_write_page_8b()/ald_nand_write_sparearea_8b(),
          ald_nand_read_page_16b()/ald_nand_read_sparearea_16b(), 
          ald_nand_write_page_16b()/ald_nand_write_sparearea_16b()
          to read/write page(s)/spare area(s).
      (#) Perform NAND flash Reset chip operation using the function ald_nand_reset().
      (#) Perform NAND flash erase block operation using the function ald_nand_erase_block().
      (#) Read the NAND flash status operation using the function ald_nand_read_status().
      (#) You can also control the NAND device by calling the control APIs ald_nand_ecc_enable()/
          ald_nand_ecc_disable() to respectively enable/disable the ECC code correction
          feature or the function ald_nand_get_ecc() to get the ECC correction code. 

    @endverbatim
  ******************************************************************************
  */

#include "ald_nand.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup NAND NAND
  * @brief NAND driver modules
  * @{
  */
#ifdef ALD_NAND

/** @defgroup Nand_Public_Functions NAND Public Functions
  * @brief NAND Public functions
  * @{
  */
/** @defgroup Nand_Public_Functions_Group1 Initialization functions
  * @brief NAND Initialization functions
  * @{
  */
/**
  * @brief  Perform NAND memory initialization sequence
  * @param  hperh: pointer to a nand_handle_t structure 
  * @param  ctiming: pointer to common space timing structure
  * @param  atiming: pointer to attribute space timing structure
  * @retval ald status
  */
ald_status_t ald_nand_init(nand_handle_t *hperh, ald_ebi_nand_timing_t *ctiming, ald_ebi_nand_timing_t *atiming)
{
	if (hperh == NULL)
		return ERROR;
	if (hperh->state == ALD_NAND_STATE_RESET)
		hperh->lock = UNLOCK;

	ald_ebi_nand_init(hperh->instance, &(hperh->init));
	ald_ebi_nand_comm_timing_init(hperh->instance, ctiming, hperh->init.bank);
	ald_ebi_nand_attr_timing_init(hperh->instance, atiming, hperh->init.bank);
	ald_ebi_nand_enable(hperh->instance, hperh->init.bank);
	hperh->state = ALD_NAND_STATE_READY;

	return OK;
}

/**
  * @brief  Perform NAND memory De-Initialization sequence
  * @param  hperh: pointer to a nand_handle_t structure 
  * @retval ald status
  */
ald_status_t ald_nand_deinit(nand_handle_t *hperh)
{
	ald_ebi_nand_deinit(hperh->instance, hperh->init.bank);
	hperh->state = ALD_NAND_STATE_RESET;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  NAND memory reset
  * @param  hperh: pointer to a nand_handle_t structure 
  * @retval ald status
  */
ald_status_t ald_nand_reset(nand_handle_t *hperh)
{
	uint32_t deviceaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		deviceaddr = NAND_DEVICE1;
	else
		deviceaddr = NAND_DEVICE2;

	hperh->state = ALD_NAND_STATE_BUSY;

	/* Send NAND reset command */  
	*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = 0xFF;

	hperh->state = ALD_NAND_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  configure the device: Enter the physical parameters of the device
  * @param  hperh: pointer to a nand_handle_t structure 
  * @param  pdcfg : pointer to nand_device_cfg_t structure
  * @retval ald status
  */
void nand_config_device(nand_handle_t *hperh, nand_device_cfg_t *pdcfg)
{
	hperh->config.page_size  = pdcfg->page_size;
	hperh->config.spare_size = pdcfg->spare_size;
	hperh->config.block_size = pdcfg->block_size;
	hperh->config.block_nbr  = pdcfg->block_nbr;
	hperh->config.plane_size = pdcfg->plane_size;
	hperh->config.plane_nbr  = pdcfg->plane_nbr;
	hperh->config.extra_cmd  = pdcfg->extra_cmd;
}
/**
  * @}
  */
/** @defgroup Nand_Public_Functions_Group2 IO operation functions
  * @brief IO operation functions
  * @{
  */
/**
  * @brief  Read the NAND memory electronic signature
  * @param  hperh: pointer to a nand_handle_t structure
  * @param  id: NAND ID structure
  * @retval ald status
  */
ald_status_t ald_nand_read_id(nand_handle_t *hperh, nand_id_t *id)
{
	__IO uint32_t data  = 0;
	__IO uint32_t data1 = 0;
	uint32_t deviceaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		deviceaddr = NAND_DEVICE1;
	else
		deviceaddr = NAND_DEVICE2;

	hperh->state = ALD_NAND_STATE_BUSY;

	/* Send Read ID command sequence */   
	*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA))  = NAND_CMD_READID;
	*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;

	if (hperh->init.width == EBI_NAND_MEM_BUS_WIDTH_8) {
		data = *(__IO uint32_t *)deviceaddr;

		id->maker_id  = ADDR_1ST_CYCLE(data);
		id->device_id = ADDR_2ND_CYCLE(data);
		id->third_id  = ADDR_3RD_CYCLE(data);
		id->fourth_id = ADDR_4TH_CYCLE(data);
	}
	else {
		data  = *(__IO uint32_t *)deviceaddr;
		data1 = *((__IO uint32_t *)deviceaddr + 4);

		/* Return the data read */
		id->maker_id  = ADDR_1ST_CYCLE(data);
		id->device_id = ADDR_3RD_CYCLE(data);
		id->third_id  = ADDR_1ST_CYCLE(data1);
		id->fourth_id = ADDR_3RD_CYCLE(data1);
	}

	hperh->state = ALD_NAND_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Read page(s) from NAND memory block (8-bits addressing)
  * @param  hperh: pointer to a nand_handle_t structure 
  * @param  addr: pointer to NAND address structure
  * @param  buf: pointer to destination read buffer
  * @param  nr: number of pages to read from block 
  * @retval ald status
  */
ald_status_t ald_nand_read_page_8b(nand_handle_t *hperh, nand_address_t *addr, uint8_t *buf, uint32_t nr)
{
	__IO uint32_t index  = 0;
	uint32_t tickstart = 0;
	uint32_t deviceaddr = 0, size = 0, num = 0, nandaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		deviceaddr = NAND_DEVICE1;
	else
		deviceaddr = NAND_DEVICE2;

	hperh->state = ALD_NAND_STATE_BUSY;

	/* NAND raw address calculation */
	nandaddr = ARRAY_ADDRESS(addr, hperh);

	/* Page(s) read loop */
	while ((nr != 0) && (nandaddr < ((hperh->config.block_size) * (hperh->config.block_nbr)))) {
		/* update the buffer size */
		size = (hperh->config.page_size) + ((hperh->config.page_size) * num);

		/* Send read page command sequence */
		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_A;

		/* Cards with page size <= 512 bytes */
		if ((hperh->config.page_size) <= 512U) {
			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else { /* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}
		else { /* (hperh->config.page_size) > 512 */
			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}

		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA))  = NAND_CMD_AREA_TRUE1;

		/* Check if an extra command is needed for reading pages  */
		if (hperh->config.extra_cmd == ENABLE) {
			/* Get tick */
			tickstart = ald_get_tick();

			/* Read status until NAND is ready */
			while (ald_nand_read_status(hperh) != NAND_READY) {
				if ((ald_get_tick() - tickstart ) > NAND_WRITE_TIMEOUT)
					return TIMEOUT;
			}

			/* Go back to read mode */
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = ((uint8_t)0x00);
		}

		/* Get Data into Buffer */    
		for (; index < size; index++) {
			*(uint8_t *)buf++ = *(uint8_t *)deviceaddr;
		}

		num++;
		nr--;
		nandaddr = (uint32_t)(nandaddr + 1U);
	}

	hperh->state = ALD_NAND_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Write page(s) to NAND memory block (8-bits addressing)
  * @param  hperh: pointer to a nand_handle_t structure 
  * @param  addr: pointer to NAND address structure
  * @param  buf: pointer to source buffer to write  
  * @param  nr: number of pages to write to block 
  * @retval ald status
  */
ald_status_t ald_nand_write_page_8b(nand_handle_t *hperh, nand_address_t *addr, uint8_t *buf, uint32_t nr)
{
	__IO uint32_t index = 0;
	uint32_t tickstart = 0;
	uint32_t deviceaddr = 0, size = 0, num = 0, nandaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		deviceaddr = NAND_DEVICE1;
	else
		deviceaddr = NAND_DEVICE2;

	/* Update the NAND controller state */ 
	hperh->state = ALD_NAND_STATE_BUSY;

	/* NAND raw address calculation */
	nandaddr = ARRAY_ADDRESS(addr, hperh);

	/* Page(s) write loop */
	while ((nr != 0) && (nandaddr < ((hperh->config.block_size) * (hperh->config.block_nbr)))) {
		/* update the buffer size */
		size = hperh->config.page_size + ((hperh->config.page_size) * num);

		/* Send write page command sequence */
		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_A;
		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_WRITE0;

		/* Cards with page size <= 512 bytes */
		if ((hperh->config.page_size) <= 512U) {
			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}
		else {/* (hperh->config.page_size) > 512 */
			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}

		/* Write data to memory */
		for (; index < size; index++)
			*(__IO uint8_t *)deviceaddr = *(uint8_t *)buf++;

		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_WRITE_TRUE1;

		/* Read status until NAND is ready */
		while (ald_nand_read_status(hperh) != NAND_READY) {
			/* Get tick */
			tickstart = ald_get_tick();

			if ((ald_get_tick() - tickstart ) > NAND_WRITE_TIMEOUT)
				return TIMEOUT;
		}

		num++;
		nr--;
		nandaddr = (uint32_t)(nandaddr + 1U);
	}

	hperh->state = ALD_NAND_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Read spare area(s) from NAND memory (8-bits addressing)
  * @param  hperh: pointer to a nand_handle_t structure 
  * @param  addr: pointer to NAND address structure
  * @param  buf: pointer to source buffer to write  
  * @param  nr: Number of spare area to read  
  * @retval ald status
*/
ald_status_t ald_nand_read_sparearea_8b(nand_handle_t *hperh, nand_address_t *addr, uint8_t *buf, uint32_t nr)
{
	__IO uint32_t index = 0;
	uint32_t tickstart = 0;
	uint32_t deviceaddr = 0, size = 0, num = 0, nandaddr = 0, columnaddr = 0;

	/* Process Locked */
	__LOCK(hperh);

	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		deviceaddr = NAND_DEVICE1;
	else
		deviceaddr = NAND_DEVICE2;

	/* Update the NAND controller state */
	hperh->state = ALD_NAND_STATE_BUSY;
	/* NAND raw address calculation */
	nandaddr = ARRAY_ADDRESS(addr, hperh);
	/* Column in page address */
	columnaddr = COLUMN_ADDRESS(hperh);

	/* Spare area(s) read loop */ 
	while ((nr != 0) && (nandaddr < ((hperh->config.block_size) * (hperh->config.block_nbr)))) {
		/* update the buffer size */
		size = (hperh->config.spare_size) + ((hperh->config.spare_size) * num);

		/* Cards with page size <= 512 bytes */
		if ((hperh->config.page_size) <= 512U) {
			/* Send read spare area command sequence */     
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_C;

			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}
		else {/* (hperh->config.page_size) > 512 */
			/* Send read spare area command sequence */ 
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_A;

			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_1ST_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_2ND_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_1ST_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_2ND_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}

		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_TRUE1;

		if (hperh->config.extra_cmd == ENABLE) {
			/* Get tick */
			tickstart = ald_get_tick();

			/* Read status until NAND is ready */
			while (ald_nand_read_status(hperh) != NAND_READY) {
				if ((ald_get_tick() - tickstart ) > NAND_WRITE_TIMEOUT)
					return TIMEOUT;
			}

			/* Go back to read mode */
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = ((uint8_t)0x00);
		}

		/* Get Data into Buffer */
		for (; index < size; index++)
			*(uint8_t *)buf++ = *(uint8_t *)deviceaddr;

		num++;
		nr--;
		nandaddr = (uint32_t)(nandaddr + 1U);
	}

	hperh->state = ALD_NAND_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Write spare area(s) to NAND memory (8-bits addressing)
  * @param  hperh: pointer to a nand_handle_t structure 
  * @param  addr: pointer to NAND address structure
  * @param  buf: pointer to source buffer to write  
  * @param  nr: number of spare areas to write to block
  * @retval ald status
  */
ald_status_t ald_nand_write_sparearea_8b(nand_handle_t *hperh, nand_address_t *addr, uint8_t *buf, uint32_t nr)
{
	__IO uint32_t index = 0;
	uint32_t tickstart = 0;
	uint32_t deviceaddr = 0, size = 0, num = 0, nandaddr = 0, columnaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		deviceaddr = NAND_DEVICE1;
	else
		deviceaddr = NAND_DEVICE2;

	/* Update the FSMC_NAND controller state */
	hperh->state = ALD_NAND_STATE_BUSY;
	/* Page address calculation */
	nandaddr = ARRAY_ADDRESS(addr, hperh);
	/* Column in page address */
	columnaddr = COLUMN_ADDRESS(hperh);

	/* Spare area(s) write loop */
	while ((nr != 0) && (nandaddr < ((hperh->config.block_size) * (hperh->config.block_nbr)))) {
		/* update the buffer size */
		size = (hperh->config.spare_size) + ((hperh->config.spare_size) * num);

		/* Cards with page size <= 512 bytes */
		if ((hperh->config.page_size) <= 512U) {
			/* Send write Spare area command sequence */
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_C;
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_WRITE0;

			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}
		else {/* (hperh->config.page_size) > 512 */
			/* Send write Spare area command sequence */
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_A;
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_WRITE0;

			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_1ST_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_2ND_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_1ST_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_2ND_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}

		/* Write data to memory */
		for (; index < size; index++)
			*(__IO uint8_t *)deviceaddr = *(uint8_t *)buf++;

		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_WRITE_TRUE1;
		tickstart = ald_get_tick();

		/* Read status until NAND is ready */
		while (ald_nand_read_status(hperh) != NAND_READY) {
			if ((ald_get_tick() - tickstart ) > NAND_WRITE_TIMEOUT)
				return TIMEOUT;
		}

		num++;
		nr--;
		nandaddr = (uint32_t)(nandaddr + 1U);
	}

	hperh->state = ALD_NAND_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Read page(s) from NAND memory block (16-bits addressing)
  * @param  hperh: pointer to a nand_handle_t structure 
  * @param  addr: pointer to NAND address structure
  * @param  buf: pointer to destination read buffer
  * @param  nr: number of pages to read from block 
  * @retval ald status
  */
ald_status_t ald_nand_read_page_16b(nand_handle_t *hperh, nand_address_t *addr, uint16_t *buf, uint32_t nr)
{
	__IO uint32_t index  = 0;
	uint32_t tickstart = 0;
	uint32_t deviceaddr = 0, size = 0, num = 0, nandaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		deviceaddr = NAND_DEVICE1;
	else
		deviceaddr = NAND_DEVICE2;

	hperh->state = ALD_NAND_STATE_BUSY;
	nandaddr = ARRAY_ADDRESS(addr, hperh);

	/* Page(s) read loop */  
	while ((nr != 0) && (nandaddr < ((hperh->config.block_size) * (hperh->config.block_nbr)))) {
		/* update the buffer size */
		size = (hperh->config.page_size) + ((hperh->config.page_size) * num);

		/* Send read page command sequence */
		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_A;

		/* Cards with page size <= 512 bytes */
		if ((hperh->config.page_size) <= 512U) {
			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}
		else {/* (hperh->config.page_size) > 512 */
			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}

		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA))  = NAND_CMD_AREA_TRUE1;

		if (hperh->config.extra_cmd == ENABLE) {
			/* Get tick */
			tickstart = ald_get_tick();

			/* Read status until NAND is ready */
			while (ald_nand_read_status(hperh) != NAND_READY) {
				if ((ald_get_tick() - tickstart ) > NAND_WRITE_TIMEOUT)
				  return TIMEOUT;
			}

			/* Go back to read mode */
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = ((uint8_t)0x00);
		}

		/* Get Data into Buffer */    
		for (; index < size; index++)
			*(uint16_t *)buf++ = *(uint16_t *)deviceaddr;

		num++;
		nr--;
		nandaddr = (uint32_t)(nandaddr + 1U);
	}

	hperh->state = ALD_NAND_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Write page(s) to NAND memory block (16-bits addressing)
  * @param  hperh: pointer to a nand_handle_t structure
  * @param  addr : pointer to NAND address structure
  * @param  buf : pointer to source buffer to write. pbuffer should be 16bits aligned
  * @param  nr : number of pages to write to block 
  * @retval ald status
  */
ald_status_t ald_nand_write_page_16b(nand_handle_t *hperh, nand_address_t *addr, uint16_t *buf, uint32_t nr)
{
	__IO uint32_t index = 0;
	uint32_t tickstart = 0;
	uint32_t deviceaddr = 0, size = 0, num = 0, nandaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		deviceaddr = NAND_DEVICE1;
	else
		deviceaddr = NAND_DEVICE2;

	hperh->state = ALD_NAND_STATE_BUSY;
	/* NAND raw address calculation */
	nandaddr = ARRAY_ADDRESS(addr, hperh);

	/* Page(s) write loop */
	while ((nr != 0) && (nandaddr < ((hperh->config.block_size) * (hperh->config.block_nbr)))) {
		/* update the buffer size */
		size = (hperh->config.page_size) + ((hperh->config.page_size) * num);

		/* Send write page command sequence */
		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_A;
		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_WRITE0;

		/* Cards with page size <= 512 bytes */
		if ((hperh->config.page_size) <= 512U) {
			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {	/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}
		else {	/* (hperh->config.page_size) > 512 */
			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {	/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}

		/* Write data to memory */
		for (; index < size; index++)
			*(__IO uint16_t *)deviceaddr = *(uint16_t *)buf++;

		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_WRITE_TRUE1;

		/* Read status until NAND is ready */
		while (ald_nand_read_status(hperh) != NAND_READY) {
			/* Get tick */
			tickstart = ald_get_tick();

			if ((ald_get_tick() - tickstart ) > NAND_WRITE_TIMEOUT)
			return TIMEOUT;
		}

		num++;
		nr--;
		nandaddr = (uint32_t)(nandaddr + 1U);
	}

	hperh->state = ALD_NAND_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}



/**
  * @brief  Read spare area(s) from NAND memory (16-bits addressing)
  * @param  hperh: pointer to a nand_handle_t structure 
  * @param  addr: pointer to NAND address structure
  * @param  buf: pointer to source buffer to write. pbuffer should be 16bits aligned.
  * @param  nr: Number of spare area to read  
  * @retval ald status
*/
ald_status_t ald_nand_read_sparearea_16b(nand_handle_t *hperh, nand_address_t *addr, uint16_t *buf, uint32_t nr)
{
	__IO uint32_t index = 0;
	uint32_t tickstart = 0;
	uint32_t deviceaddr = 0, size = 0, num = 0, nandaddr = 0, columnaddr = 0;

	__LOCK(hperh);

	/* Check the NAND controller state */
	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		deviceaddr = NAND_DEVICE1;
	else
		deviceaddr = NAND_DEVICE2;

	/* Update the NAND controller state */
	hperh->state = ALD_NAND_STATE_BUSY;
	/* NAND raw address calculation */
	nandaddr = ARRAY_ADDRESS(addr, hperh);
	/* Column in page address */
	columnaddr = (uint32_t)(COLUMN_ADDRESS(hperh) * 2U);

	/* Spare area(s) read loop */ 
	while ((nr != 0) && (nandaddr < ((hperh->config.block_size) * (hperh->config.block_nbr)))) {
		/* update the buffer size */
		size = (hperh->config.spare_size) + ((hperh->config.spare_size) * num);

		/* Cards with page size <= 512 bytes */
		if ((hperh->config.page_size) <= 512U) {
			/* Send read spare area command sequence */     
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_C;

			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}
		else {/* (hperh->config.page_size) > 512 */
			/* Send read spare area command sequence */     
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_A;

			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_1ST_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_2ND_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_1ST_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_2ND_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}

		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_TRUE1;

		if (hperh->config.extra_cmd == ENABLE) {
			/* Get tick */
			tickstart = ald_get_tick();

			/* Read status until NAND is ready */
			while (ald_nand_read_status(hperh) != NAND_READY) {
				if ((ald_get_tick() - tickstart ) > NAND_WRITE_TIMEOUT)
				  return TIMEOUT;
			}

			/* Go back to read mode */
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = ((uint8_t)0x00);
		}

		/* Get Data into Buffer */
		for (; index < size; index++)
			*(uint16_t *)buf++ = *(uint16_t *)deviceaddr;

		num++;
		nr--;
		nandaddr = (uint32_t)(nandaddr + 1U);
	}

	hperh->state = ALD_NAND_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}


/**
  * @brief  Write spare area(s) to NAND memory (16-bits addressing)
  * @param  hperh: pointer to a nand_handle_t structure 
  * @param  addr: pointer to NAND address structure
  * @param  buf: pointer to source buffer to write. pbuffer should be 16bits aligned.  
  * @param  nr: number of spare areas to write to block
  * @retval ald status
  */
ald_status_t ald_nand_write_sparearea_16b(nand_handle_t *hperh, nand_address_t *addr, uint16_t *buf, uint32_t nr)
{
	__IO uint32_t index = 0;
	uint32_t tickstart = 0;
	uint32_t deviceaddr = 0, size = 0, num = 0, nandaddr = 0, columnaddr = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		deviceaddr = NAND_DEVICE1;
	else
		deviceaddr = NAND_DEVICE2;

	/* Update the FSMC_NAND controller state */
	hperh->state = ALD_NAND_STATE_BUSY;
	/* NAND raw address calculation */
	nandaddr = ARRAY_ADDRESS(addr, hperh);
	/* Column in page address */
	columnaddr = (uint32_t)(COLUMN_ADDRESS(hperh) * 2);

	/* Spare area(s) write loop */
	while ((nr != 0) && (nandaddr < ((hperh->config.block_size) * (hperh->config.block_nbr)))) {
		/* update the buffer size */
		size = (hperh->config.spare_size) + ((hperh->config.spare_size) * num);

		/* Cards with page size <= 512 bytes */
		if ((hperh->config.page_size) <= 512U) {
			/* Send write Spare area command sequence */
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_C;
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_WRITE0;

			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
			*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
			*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
			*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
			*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = 0x00;
			*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
			*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}
		else {/* (hperh->config.page_size) > 512 */
			/* Send write Spare area command sequence */
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_AREA_A;
			*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_WRITE0;

			if (((hperh->config.block_size)* (hperh->config.block_nbr)) <= 65535U) {
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_1ST_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_2ND_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
			}
			else {/* ((hperh->config.block_size)*(hperh->config.block_nbr)) > 65535 */
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_1ST_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = COLUMN_2ND_CYCLE(columnaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(nandaddr);
				*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(nandaddr);
			}
		}

		/* Write data to memory */
		for (; index < size; index++)
			*(__IO uint16_t *)deviceaddr = *(uint16_t *)buf++;

		*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_WRITE_TRUE1;

		/* Read status until NAND is ready */
		while (ald_nand_read_status(hperh) != NAND_READY) {
			/* Get tick */
			tickstart = ald_get_tick();

			if ((ald_get_tick() - tickstart ) > NAND_WRITE_TIMEOUT)
			return TIMEOUT;
		}

		num++;
		nr--;
		nandaddr = (uint32_t)(nandaddr + 1U);
	}

	hperh->state = ALD_NAND_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  NAND memory Block erase 
  * @param  hperh: pointer to a nand_handle_t structure 
  * @param  addr: pointer to NAND address structure
  * @retval ald status
  */
ald_status_t ald_nand_erase_block(nand_handle_t *hperh, nand_address_t *addr)
{
	uint32_t deviceaddr = 0;
	uint32_t tickstart = 0;

	__LOCK(hperh);

	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		deviceaddr = NAND_DEVICE1;
	else
		deviceaddr = NAND_DEVICE2;

	/* Update the NAND controller state */
	hperh->state = ALD_NAND_STATE_BUSY;

	/* Send Erase block command sequence */
	*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_ERASE0;
	*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_1ST_CYCLE(ARRAY_ADDRESS(addr, hperh));
	*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_2ND_CYCLE(ARRAY_ADDRESS(addr, hperh));
	*(__IO uint8_t *)((uint32_t)(deviceaddr | ADDR_AREA)) = ADDR_3RD_CYCLE(ARRAY_ADDRESS(addr, hperh));
	*(__IO uint8_t *)((uint32_t)(deviceaddr | CMD_AREA)) = NAND_CMD_ERASE1;

	/* Update the NAND controller state */
	hperh->state = ALD_NAND_STATE_READY;
	/* Get tick */
	tickstart = ald_get_tick();

	/* Read status until NAND is ready */
	while (ald_nand_read_status(hperh) != NAND_READY) {
		if ((ald_get_tick() - tickstart ) > NAND_WRITE_TIMEOUT) {
			__UNLOCK(hperh);

			return TIMEOUT;
		}
	}

	__UNLOCK(hperh);

	return OK;
}
/**
  * @}
  */

/** @defgroup Nand_Public_Functions_Group3 NAND Control functions
  * @brief NAND Control functions
  * @{
  */
/**
  * @brief  This function handles NAND device interrupt request.
  * @param  hperh: pointer to a nand_handle_t structure
  * @retval ald status
*/
void ald_nand_irq_handler(nand_handle_t *hperh)
{
	/* Check NAND interrupt Rising edge flag */
	if (ald_ebi_nand_get_flag(hperh->instance, hperh->init.bank, EBI_FLAG_RISING_EDGE)) {
		ald_nand_irq_cbk(hperh);
		ald_ebi_nand_clear_flag(hperh->instance, hperh->init.bank, EBI_FLAG_RISING_EDGE);
	}

	/* Check NAND interrupt Level flag */
	if (ald_ebi_nand_get_flag(hperh->instance, hperh->init.bank, EBI_FLAG_LEVEL)) {
		ald_nand_irq_cbk(hperh);
		ald_ebi_nand_clear_flag(hperh->instance, hperh->init.bank, EBI_FLAG_LEVEL);
	}

	if (ald_ebi_nand_get_flag(hperh->instance, hperh->init.bank, EBI_FLAG_FALLING_EDGE)) {
		/* NAND interrupt callback*/
		ald_nand_irq_cbk(hperh);
		ald_ebi_nand_clear_flag(hperh->instance, hperh->init.bank, EBI_FLAG_FALLING_EDGE);
	}

	/* Check NAND interrupt FIFO empty flag */
	if (ald_ebi_nand_get_flag(hperh->instance, hperh->init.bank, EBI_FLAG_FEMPT)) {
		ald_nand_irq_cbk(hperh);
		ald_ebi_nand_clear_flag(hperh->instance, hperh->init.bank, EBI_FLAG_FEMPT);
	}
}

/**
  * @brief  NAND interrupt feature callback
  * @param  hperh: pointer to a nand_handle_t structure 
  * @retval None
  */
__weak void ald_nand_irq_cbk(nand_handle_t *hperh)
{
	  /* Prevent unused argument(s) compilation warning */
	  UNUSED(hperh);
}

/**
  * @brief  Increment the NAND memory address
  * @param  hperh: pointer to a nand_handle_t structure
  * @param  addr: pointer to NAND address structure
  * @retval The new status of the increment address operation. It can be:
  *           - NAND_VALID_ADDRESS: When the new address is valid address
  *           - NAND_INVALID_ADDRESS: When the new address is invalid address
  */
uint32_t ald_nand_address_inc(nand_handle_t *hperh, nand_address_t *addr)
{
	uint32_t status = NAND_VALID_ADDRESS;

	addr->page++;

	/* Check NAND address is valid */
	if (addr->page == hperh->config.block_size) {
		addr->page = 0;
		addr->block++;

		if (addr->block == hperh->config.plane_size) {
			addr->block = 0;
			addr->plane++;

			if (addr->plane == (hperh->config.plane_nbr))
				status = NAND_INVALID_ADDRESS;
		}
	}

	return status;
}

/**
  * @brief  NAND memory read status 
  * @param  hperh: pointer to a nand_handle_t structure 
  * @retval NAND status
  */
uint32_t ald_nand_read_status(nand_handle_t *hperh)
{
	uint32_t data = 0;
	uint32_t addr = 0;

	/* Identify the device address */
	if (hperh->init.bank == EBI_NAND_BANK2)
		addr = NAND_DEVICE1;
	else
		addr = NAND_DEVICE2;

	/* Send Read status operation command */
	*(__IO uint8_t *)((uint32_t)(addr | CMD_AREA)) = NAND_CMD_STATUS;
	/* Read status register data */
	data = *(__IO uint8_t *)addr;

	/* Return the status */
	if ((data & NAND_ERROR) == NAND_ERROR)
		return NAND_ERROR;
	else if ((data & NAND_READY) == NAND_READY)
		return NAND_READY;

	return NAND_BUSY;
}

/**
  * @brief  return the NAND state
  * @param  hperh: pointer to a nand_handle_t structure 
  * @retval ald state
  */
ald_nand_state_t ald_nand_get_state(nand_handle_t *hperh)
{
	return hperh->state;
}

/**
  * @brief  Enables dynamically NAND ECC feature.
  * @param  hperh: pointer to a nand_handle_t structure 
  * @retval ald status
  */    
ald_status_t ald_nand_ecc_enable(nand_handle_t *hperh)
{
	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Update the NAND state */
	hperh->state = ALD_NAND_STATE_BUSY;
	/* Enable ECC feature */
	ald_ebi_nand_ecc_enable(hperh->instance, hperh->init.bank);
	/* Update the NAND state */
	hperh->state = ALD_NAND_STATE_READY;

	return OK;
}

/**
  * @brief  Disables dynamically FSMC_NAND ECC feature.
  * @param  hperh: pointer to a nand_handle_t structure 
  * @retval ald status
  */  
ald_status_t ald_nand_ecc_disable(nand_handle_t *hperh)
{
	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	/* Update the NAND state */
	hperh->state = ALD_NAND_STATE_BUSY;
	/* Disable ECC feature */
	ald_ebi_nand_ecc_disable(hperh->instance, hperh->init.bank);
	hperh->state = ALD_NAND_STATE_READY;

	return OK;
}

/**
  * @brief  Disables dynamically NAND ECC feature.
  * @param  hperh: pointer to a nand_handle_t structure 
  * @param  val: pointer to ECC value 
  * @param  timeout: maximum timeout to wait    
  * @retval ald status
  */
ald_status_t ald_nand_get_ecc(nand_handle_t *hperh, uint32_t *val, uint32_t timeout)
{
	ald_status_t status = OK;

	if (hperh->state == ALD_NAND_STATE_BUSY)
		return BUSY;

	hperh->state = ALD_NAND_STATE_BUSY;
	status = ald_ebi_nand_get_ecc(hperh->instance, val, hperh->init.bank, timeout);
	hperh->state = ALD_NAND_STATE_READY;

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
