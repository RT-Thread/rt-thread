/**
 * \file
 *
 * \brief Flash functionality implementation.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include "hal_flash.h"
#include <utils_assert.h>
#include <utils.h>
#include <hal_atomic.h>

/**
 * \brief Driver version
 */
#define DRIVER_VERSION 0x00000001u

static void flash_ready(struct _flash_device *device);
static void flash_error(struct _flash_device *device);

static int32_t flash_is_address_aligned(struct flash_descriptor *flash, const uint32_t flash_addr);

/**
 * \brief Initialize the FLASH HAL instance and hardware for callback mode.
 */
int32_t flash_init(struct flash_descriptor *flash, void *const hw)
{
	int32_t rc;

	ASSERT(flash && hw);

	rc = _flash_init(&flash->dev, hw);
	if (rc) {
		return rc;
	}

	flash->dev.flash_cb.ready_cb = flash_ready;
	flash->dev.flash_cb.error_cb = flash_error;

	return ERR_NONE;
}

/**
 * \brief  Deinitialize the FLASH HAL instance.
 */
int32_t flash_deinit(struct flash_descriptor *flash)
{
	ASSERT(flash);

	_flash_deinit(&flash->dev);

	return ERR_NONE;
}

/**
 * \brief Reads a number of bytes to a page in the internal Flash
 */
int32_t flash_read(struct flash_descriptor *flash, uint32_t src_addr, uint8_t *buffer, uint32_t length)
{
	ASSERT(flash && buffer && length);

	uint32_t page_size   = _flash_get_page_size(&flash->dev);
	uint32_t total_pages = _flash_get_total_pages(&flash->dev);

	/* Check if the address is valid */
	if ((src_addr > page_size * total_pages) || (src_addr + length > page_size * total_pages)) {
		return ERR_BAD_ADDRESS;
	}

	_flash_read(&flash->dev, src_addr, buffer, length);

	return ERR_NONE;
}

/**
 * \brief Updates several bytes to the internal Flash
 */
int32_t flash_write(struct flash_descriptor *flash, uint32_t dst_addr, uint8_t *buffer, uint32_t length)
{
	ASSERT(flash && buffer && length);

	uint32_t page_size   = _flash_get_page_size(&flash->dev);
	uint32_t total_pages = _flash_get_total_pages(&flash->dev);

	/* Check if the address is valid */
	if ((dst_addr > page_size * total_pages) || (dst_addr + length > page_size * total_pages)) {
		return ERR_BAD_ADDRESS;
	}

	if (_flash_is_locked(&flash->dev, dst_addr)) {
		return ERR_DENIED;
	}

	_flash_write(&flash->dev, dst_addr, buffer, length);

	return ERR_NONE;
}

/**
 * \brief Appends a number of bytes to a page in the internal Flash
 */
int32_t flash_append(struct flash_descriptor *flash, uint32_t dst_addr, uint8_t *buffer, uint32_t length)
{
	ASSERT(flash && buffer && length);

	uint32_t page_size   = _flash_get_page_size(&flash->dev);
	uint32_t total_pages = _flash_get_total_pages(&flash->dev);

	/* Check if the address is valid */
	if ((dst_addr > page_size * total_pages) || (dst_addr + length > page_size * total_pages)) {
		return ERR_BAD_ADDRESS;
	}

	if (_flash_is_locked(&flash->dev, dst_addr)) {
		return ERR_DENIED;
	}

	_flash_append(&flash->dev, dst_addr, buffer, length);

	return ERR_NONE;
}

/**
 * \brief Execute erase in the internal flash
 */
int32_t flash_erase(struct flash_descriptor *flash, const uint32_t dst_addr, const uint32_t page_nums)
{
	ASSERT(flash && page_nums);
	uint32_t page_size   = _flash_get_page_size(&flash->dev);
	uint32_t total_pages = _flash_get_total_pages(&flash->dev);
	int32_t  rc;

	rc = flash_is_address_aligned(flash, dst_addr);
	if (rc) {
		return rc;
	}

	if ((page_nums > total_pages) || (dst_addr / page_size + page_nums > total_pages)) {
		return ERR_INVALID_ARG;
	}

	_flash_erase(&flash->dev, dst_addr, page_nums);

	return ERR_NONE;
}

/**
 * \brief Register a function as FLASH transfer completion callback
 */
int32_t flash_register_callback(struct flash_descriptor *flash, const enum flash_cb_type type, flash_cb_t func)
{
	ASSERT(flash);

	switch (type) {
	case FLASH_CB_READY:
		flash->callbacks.cb_ready = func;
		break;

	case FLASH_CB_ERROR:
		flash->callbacks.cb_error = func;
		break;

	default:
		return ERR_INVALID_ARG;
	}

	_flash_set_irq_state(&flash->dev, (enum _flash_cb_type)type, NULL != func);

	return ERR_NONE;
}

/**
 * \brief Execute lock in the internal flash
 */
int32_t flash_lock(struct flash_descriptor *flash, const uint32_t dst_addr, const uint32_t page_nums)
{
	ASSERT(flash && page_nums);
	uint32_t page_size   = _flash_get_page_size(&flash->dev);
	uint32_t total_pages = _flash_get_total_pages(&flash->dev);
	int32_t  rc;

	rc = flash_is_address_aligned(flash, dst_addr);
	if (rc) {
		return rc;
	}

	if ((page_nums > total_pages) || (dst_addr / page_size + page_nums > total_pages)) {
		return ERR_INVALID_ARG;
	}

	return _flash_lock(&flash->dev, dst_addr, page_nums);
}

/**
 * \brief Execute unlock in the internal flash
 */
int32_t flash_unlock(struct flash_descriptor *flash, const uint32_t dst_addr, const uint32_t page_nums)
{
	ASSERT(flash && page_nums);
	uint32_t page_size   = _flash_get_page_size(&flash->dev);
	uint32_t total_pages = _flash_get_total_pages(&flash->dev);
	int32_t  rc;

	rc = flash_is_address_aligned(flash, dst_addr);
	if (rc) {
		return rc;
	}

	if ((page_nums > total_pages) || (dst_addr / page_size + page_nums > total_pages)) {
		return ERR_INVALID_ARG;
	}

	return _flash_unlock(&flash->dev, dst_addr, page_nums);
}

/**
 * \brief Get the flash page size.
 */
uint32_t flash_get_page_size(struct flash_descriptor *flash)
{
	ASSERT(flash);
	return _flash_get_page_size(&flash->dev);
}

/**
 * \brief Get the numbers of flash page.
 */
uint32_t flash_get_total_pages(struct flash_descriptor *flash)
{
	ASSERT(flash);
	return _flash_get_total_pages(&flash->dev);
}

/**
 * \brief Retrieve the current driver version
 */
uint32_t flash_get_version(void)
{
	return DRIVER_VERSION;
}

/**
 * \internal check the address whether it is aligned
 * \param[in, out] flash        Pointer to the HAL FLASH instance.
 * \param[in]  flash_addr       address to be check in flash
 *
 * \return whether it is valid
 *  \retval 0 Valid.
 *  \retval -1 Error, invalid.
 */
static int32_t flash_is_address_aligned(struct flash_descriptor *flash, const uint32_t flash_addr)
{
	ASSERT(flash);

	uint32_t page_size = _flash_get_page_size(&flash->dev);

	/* Check if the read address not aligned to the start of a page */
	if (flash_addr & (page_size - 1)) {
		return ERR_BAD_ADDRESS;
	}
	return ERR_NONE;
}

/**
 * \internal Ready for a new flash command
 *
 * \param[in] device The pointer to flash device structure
 */
static void flash_ready(struct _flash_device *device)
{
	struct flash_descriptor *const descr = CONTAINER_OF(device, struct flash_descriptor, dev);
	if (descr->callbacks.cb_ready) {
		descr->callbacks.cb_ready(descr);
	}
}

/**
 * \internal Error occurs in flash command
 *
 * \param[in] device The pointer to flash device structure
 */
static void flash_error(struct _flash_device *device)
{
	struct flash_descriptor *const descr = CONTAINER_OF(device, struct flash_descriptor, dev);
	if (descr->callbacks.cb_error) {
		descr->callbacks.cb_error(descr);
	}
}
