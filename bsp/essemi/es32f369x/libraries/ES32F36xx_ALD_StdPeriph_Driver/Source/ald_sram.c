/**
  *********************************************************************************
  *
  * @file    ald_sram.c
  * @brief   SRAM module driver.
  *
  * @version V1.0
  * @date    25 Dec 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */
#include "ald_sram.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup SRAM SRAM
  * @brief SRAM module driver
  * @{
  */

#ifdef ALD_SRAM

/** @defgroup SRAM_Public_Functions SRAM Public Functions
  * @{
  */
/** @defgroup SRAM_Public_Functions_Group1 Initialization functions
  * @brief Initialization functions
  * @{
  */
/**
  * @brief  Performs the SRAM device initialization sequence
  * @param  hperh: pointer to a sram_handle_t structure
  * @param  timing: Pointer to SRAM control timing structure 
  * @param  ext_timing: Pointer to SRAM extended mode timing structure  
  * @retval ald status
  */
ald_status_t ald_sram_init(sram_handle_t *hperh, ald_ebi_nor_sram_timing_t *timing, ald_ebi_nor_sram_timing_t *ext_timing)
{
	if (hperh == NULL)
		return ERROR;

	if (hperh->state == ALD_SRAM_STATE_RESET)
		hperh->lock = UNLOCK;

	/* Initialize SRAM control Interface */
	ald_ebi_nor_sram_init(hperh->instance, &(hperh->init));
	/* Initialize SRAM timing Interface */
	ald_ebi_nor_sram_timing_init(hperh->instance, timing, hperh->init.bank);
	/* Initialize SRAM extended mode timing Interface */
	ald_ebi_nor_sram_ext_timing_init(hperh->ext, ext_timing, hperh->init.bank,  hperh->init.ext_mode);
	/* Enable the NORSRAM device */
	ald_ebi_nor_sram_enable(hperh->instance, hperh->init.bank);

	return OK;
}

/**
  * @brief  Performs the SRAM device De-initialization sequence.
  * @param  hperh: pointer to a sram_handle_t structure 
  * @retval ald status
  */
ald_status_t  ald_sram_deinit(sram_handle_t *hperh)
{
	ald_ebi_nor_sram_deinit(hperh->instance, hperh->ext, hperh->init.bank);
	hperh->state = ALD_SRAM_STATE_RESET;
	__UNLOCK(hperh);

	return OK;
}
/**
  * @}
  */

/** @defgroup SRAM_Public_Functions_Group2 I/O operation functions
  * @brief I/O operation functions
  * @{
  */
/**
  * @brief  Reads 8-bit buffer from SRAM memory. 
  * @param  hperh: pointer to a sram_handle_t structure 
  * @param  addr: Pointer to read start address
  * @param  buf: Pointer to destination buffer  
  * @param  size: Size of the buffer to read from memory
  * @retval ald status
  */
ald_status_t ald_sram_read_8b(sram_handle_t *hperh, uint32_t *addr, uint8_t *buf, uint32_t size)
{
	__IO uint8_t * psramaddr = (uint8_t *)addr;

	__LOCK(hperh);
	hperh->state = ALD_SRAM_STATE_BUSY;

	/* Read data from memory */
	for (; size != 0U; size--)
		*buf++ = *(__IO uint8_t *)psramaddr++;

	hperh->state = ALD_SRAM_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Writes 8-bit buffer to SRAM memory. 
  * @param  hperh: pointer to a sram_handle_t structure 
  * @param  addr: Pointer to write start address
  * @param  buf: Pointer to source buffer to write  
  * @param  size: Size of the buffer to write to memory
  * @retval ald status
  */
ald_status_t ald_sram_write_8b(sram_handle_t *hperh, uint32_t *addr, uint8_t *buf, uint32_t size)
{
	__IO uint8_t * psramaddr = (uint8_t *)addr;

	if (hperh->state == ALD_SRAM_STATE_PROTECTED)
		return  ERROR;

	__LOCK(hperh);
	hperh->state = ALD_SRAM_STATE_BUSY;

	/* Write data to memory */
	for (; size != 0U; size--)
		*(__IO uint8_t *)psramaddr++ = *buf++;

	hperh->state = ALD_SRAM_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Reads 16-bit buffer from SRAM memory. 
  * @param  hperh: pointer to a sram_handle_t structure that contains
  *                the configuration information for SRAM module.
  * @param  addr: Pointer to read start address
  * @param  buf: Pointer to destination buffer  
  * @param  size: Size of the buffer to read from memory
  * @retval ald status
  */
ald_status_t ald_sram_read_16b(sram_handle_t *hperh, uint32_t *addr, uint16_t *buf, uint32_t size)
{
	__IO uint16_t * psramaddr = (uint16_t *)addr;

	__LOCK(hperh);
	hperh->state = ALD_SRAM_STATE_BUSY;

	/* Read data from memory */
	for (; size != 0U; size--)
		*buf++ = *(__IO uint16_t *)psramaddr++;

	hperh->state = ALD_SRAM_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Writes 16-bit buffer to SRAM memory. 
  * @param  hperh: pointer to a sram_handle_t structure that contains
  *                the configuration information for SRAM module.
  * @param  addr: Pointer to write start address
  * @param  buf: Pointer to source buffer to write  
  * @param  size: Size of the buffer to write to memory
  * @retval ald status
  */
ald_status_t ald_sram_write_16b(sram_handle_t *hperh, uint32_t *addr, uint16_t *buf, uint32_t size)
{
	__IO uint16_t * psramaddr = (uint16_t *)addr;

	if (hperh->state == ALD_SRAM_STATE_PROTECTED)
		return  ERROR;

	__LOCK(hperh);
	hperh->state = ALD_SRAM_STATE_BUSY;

	/* Write data to memory */
	for (; size != 0U; size--)
		*(__IO uint16_t *)psramaddr++ = *buf++;

	hperh->state = ALD_SRAM_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Reads 32-bit buffer from SRAM memory. 
  * @param  hperh: pointer to a sram_handle_t structure 
  * @param  addr: Pointer to read start address
  * @param  buf: Pointer to destination buffer  
  * @param  size: Size of the buffer to read from memory
  * @retval ald status
  */
ald_status_t ald_sram_read_32b(sram_handle_t *hperh, uint32_t *addr, uint32_t *buf, uint32_t size)
{
	__LOCK(hperh);
	hperh->state = ALD_SRAM_STATE_BUSY;

	/* Read data from memory */
	for (; size != 0U; size--)
		*buf++ = *(__IO uint32_t *)addr++;

	hperh->state = ALD_SRAM_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Writes 32-bit buffer to SRAM memory. 
  * @param  hperh: pointer to a sram_handle_t structure that contains
  *                the configuration information for SRAM module.
  * @param  addr: Pointer to write start address
  * @param  buf: Pointer to source buffer to write  
  * @param  size: Size of the buffer to write to memory
  * @retval ald status
  */
ald_status_t ald_sram_write_32b(sram_handle_t *hperh, uint32_t *addr, uint32_t *buf, uint32_t size)
{
	if (hperh->state == ALD_SRAM_STATE_PROTECTED)
		return  ERROR;

	__LOCK(hperh);
	hperh->state = ALD_SRAM_STATE_BUSY;

	/* Write data to memory */
	for (; size != 0U; size--)
		*(__IO uint32_t *)addr++ = *buf++;

	hperh->state = ALD_SRAM_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

#ifdef ALD_DMA
/**
  * @brief  Reads a halfwords data from the SRAM memory using DMA transfer.
  * @param  hperh: pointer to a sram_handle_t structure that contains
  *                the configuration information for SRAM module.
  * @param  addr: Pointer to read start address
  * @param  buf: Pointer to destination buffer  
  * @param  size: Size of the buffer to read from memory
  * @param  ch: Index of DMA channel
  * @retval ald status
  */
ald_status_t ald_sram_read_by_dma(sram_handle_t *hperh, uint16_t *addr, uint16_t *buf, uint16_t size, uint8_t ch)
{
	if (buf == NULL)
		return ERROR;

	hperh->hdma.perh = DMA0;
	hperh->hdma.cplt_cbk = hperh->cplt_cbk;
	ald_dma_config_struct(&hperh->hdma.config);

	hperh->hdma.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdma.config.src        = (void *)addr;
	hperh->hdma.config.dst        = (void *)buf;
	hperh->hdma.config.size       = size;
	hperh->hdma.config.src_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdma.config.dst_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdma.config.msel       = DMA_MSEL_NONE;
	hperh->hdma.config.msigsel    = DMA_MSIGSEL_NONE;
	hperh->hdma.config.channel    = ch;
	hperh->hdma.config.R_power    = DMA_R_POWER_4;
	hperh->hdma.config.burst      = ENABLE;

	ald_dma_config_auto(&hperh->hdma);
	return OK;
}

/**
  * @brief  Write a halfwords data to the SRAM memory using DMA transfer.
  * @param  hperh: pointer to a sram_handle_t structure that contains
  *                the configuration information for SRAM module.
  * @param  addr: Pointer to write start address
  * @param  buf: Pointer to destination buffer  
  * @param  size: Size of the buffer to write from memory
  * @param  ch: Index of DMA channel
  * @retval ald status
  */
ald_status_t ald_sram_write_by_dma(sram_handle_t *hperh, uint16_t *addr, uint16_t *buf, uint16_t size, uint8_t ch)
{
	if (buf == NULL)
		return ERROR;
	;
	hperh->hdma.perh = DMA0;
	hperh->hdma.cplt_cbk = hperh->cplt_cbk;
	ald_dma_config_struct(&hperh->hdma.config);

	hperh->hdma.config.data_width = DMA_DATA_SIZE_HALFWORD;
	hperh->hdma.config.src        = (void *)buf;
	hperh->hdma.config.dst        = (void *)addr;
	hperh->hdma.config.size       = size;
	hperh->hdma.config.src_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdma.config.dst_inc    = DMA_DATA_INC_HALFWORD;
	hperh->hdma.config.msel       = DMA_MSEL_NONE;
	hperh->hdma.config.msigsel    = DMA_MSIGSEL_NONE;
	hperh->hdma.config.channel    = ch;
	hperh->hdma.config.R_power    = DMA_R_POWER_4;
	hperh->hdma.config.burst      = ENABLE;

	ald_dma_config_auto(&hperh->hdma);
	return OK;
}
#endif
/**
  * @}
  */

/** @defgroup SRAM_Public_Functions_Group3 Control functions
  * @brief Control functions
  * @{
  */
/**
  * @brief  Enables dynamically SRAM write operation.
  * @param  hperh: pointer to a sram_handle_t structure
  * @retval ald status
  */
ald_status_t ald_sram_write_enable(sram_handle_t *hperh)
{
	__LOCK(hperh);
	ald_ebi_nor_sram_write_enable(hperh->instance, hperh->init.bank);
	hperh->state = ALD_SRAM_STATE_READY;
	__UNLOCK(hperh);

	return OK;
}

/**
  * @brief  Disables dynamically SRAM write operation.
  * @param  hperh: pointer to a sram_handle_t structure 
  * @retval ald status
  */
ald_status_t ald_sram_write_disable(sram_handle_t *hperh)
{
	__LOCK(hperh);
	hperh->state = ALD_SRAM_STATE_BUSY;
	ald_ebi_nor_sram_write_disable(hperh->instance, hperh->init.bank);
	hperh->state = ALD_SRAM_STATE_PROTECTED;
	__UNLOCK(hperh);

	return OK;
}
/**
  * @}
  */

/** @addtogroup SRAM_Public_Functions_Group4 State functions
  * @brief State functions
  * @{
  */
/**
  * @brief  Returns the SRAM controller state
  * @param  hperh: pointer to a SRAM_HandleTypeDef structure 
  * @retval ald state
  */
ald_sram_state_t ald_sram_get_state(sram_handle_t *hperh)
{
	return hperh->state;
}
/**
  * @}
  */
/**
  * @}
  */
#endif /* ALD_SRAM */

/**
  * @}
  */
/**
  * @}
  */
