/**
 * \file
 *
 * \brief FLASH related functionality declaration.
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
#ifndef _HPL_FLASH_H_INCLUDED
#define _HPL_FLASH_H_INCLUDED

/**
 * \addtogroup hpl__flash__group FLASH HPL APIs
 *
 */

/**@{*/

#include <compiler.h>
#include "hpl_irq.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief FLASH device structure
 *
 * The FLASH device structure forward declaration.
 */
struct _flash_device;

/** The callback types */
enum _flash_cb_type { FLASH_DEVICE_CB_READY, FLASH_DEVICE_CB_ERROR, FLASH_DEVICE_CB_N };

/**
 * \brief FLASH interrupt handlers structure
 */
struct _flash_callback {
	/** Ready to accept new command handler */
	void (*ready_cb)(struct _flash_device *device);
	/** Error handler */
	void (*error_cb)(struct _flash_device *device);
};

/**
 * \brief FLASH descriptor device structure.
 */
struct _flash_device {
	struct _flash_callback flash_cb; /*!< Interrupt handers  */
	struct _irq_descriptor irq;      /*!< Interrupt descriptor */
	void *                 hw;       /*!< Hardware module instance handler */
};

/**
 * \brief Initialize FLASH.
 *
 * This function does low level FLASH configuration.
 *
 * \param[in] device The pointer to FLASH device instance
 * \param[in] hw The pointer to hardware instance
 *
 * \return Initialize status.
 */
int32_t _flash_init(struct _flash_device *const device, void *const hw);

/**
 * \brief Deinitialize FLASH.
 *
 * \param[in] device The pointer to FLASH device instance
 */
void _flash_deinit(struct _flash_device *const device);

/**
 * \brief Reads a number of bytes in the internal Flash.
 *
 * \param[in] device         The pointer to FLASH device instance
 * \param[in]  src_addr      Source bytes address to read from flash
 * \param[out] buffer        Pointer to a buffer where the content
 *                           of the read page will be stored
 * \param[in]  length        Number of bytes to read
 */
void _flash_read(struct _flash_device *const device, const uint32_t src_addr, uint8_t *buffer, uint32_t length);

/**
 * \brief Writes a number of bytes in the internal Flash.
 *
 * \param[in] device         The pointer to FLASH device instance
 * \param[in]  dst_addr      Destination bytes address to write into flash
 * \param[in]  buffer        Pointer to buffer where the data to
 *                           write is stored
 * \param[in]  length        Number of bytes to write
 */
void _flash_write(struct _flash_device *const device, const uint32_t dst_addr, uint8_t *buffer, uint32_t length);

/**
 * \brief Appends a number of bytes in the internal Flash.
 *
 * \param[in] device         The pointer to FLASH device instance
 * \param[in]  dst_addr      Destination bytes address to write into flash
 * \param[in]  buffer        Pointer to buffer with data to write to flash
 * \param[in]  length        Number of bytes to write
 */
void _flash_append(struct _flash_device *const device, const uint32_t dst_addr, uint8_t *buffer, uint32_t length);

/** \brief Execute lock in the internal flash
 *  \param[in] device         The pointer to FLASH device instance
 *  \param[in]  dst_addr      Destination bytes address aligned with page
 *                            start to be locked
 *  \param[in]  page_nums     Number of pages to be locked
 *
 *  \return Real locked numbers of pages.
 */
int32_t _flash_lock(struct _flash_device *const device, const uint32_t dst_addr, uint32_t page_nums);

/** \brief Execute unlock in the internal flash
 *  \param[in] device         The pointer to FLASH device instance
 *  \param[in]  dst_addr      Destination bytes address aligned with page
 *                            start to be unlocked
 *  \param[in]  page_nums     Number of pages to be unlocked
 *
 *  \return Real unlocked numbers of pages.
 */
int32_t _flash_unlock(struct _flash_device *const device, const uint32_t dst_addr, uint32_t page_nums);

/** \brief check whether the region which is pointed by address
 *         is locked
 *  \param[in] device         The pointer to FLASH device instance
 *  \param[in]  dst_addr      Destination bytes address to check
 *
 *  \return The lock status of assigned address.
 */
bool _flash_is_locked(struct _flash_device *const device, const uint32_t dst_addr);

/** \brief Execute erase in the internal flash
 *  \param[in] device         The pointer to FLASH device instance
 *  \param[in]  dst_addr      Destination bytes address aligned with page
 *                            start to be erased
 *  \param[in]  page_nums     Number of pages to be erased
 */
void _flash_erase(struct _flash_device *const device, const uint32_t dst_addr, uint32_t page_nums);

/**
 * \brief Get the flash page size.
 *
 * \param[in] device         The pointer to FLASH device instance
 *
 * \return The flash page size
 */
uint32_t _flash_get_page_size(struct _flash_device *const device);

/**
 * \brief Get the numbers of flash page.
 *
 * \param[in] device         The pointer to FLASH device instance
 *
 * \return The flash total page numbers
 */
uint32_t _flash_get_total_pages(struct _flash_device *const device);

/**
 * \brief Get the number of wait states for read and write operations.
 *
 * \param[in] device         The pointer to FLASH device instance
 *
 * \return The number of wait states for read and write operations
 */
uint8_t _flash_get_wait_state(struct _flash_device *const device);

/**
 * \brief Set the number of wait states for read and write operations.
 *
 * \param[in] device         The pointer to FLASH device instance
 * \param[in] state The number of wait states
 *
 */
void _flash_set_wait_state(struct _flash_device *const device, uint8_t state);

/**
 * \brief Enable/disable Flash interrupt
 *
 * param[in] device The pointer to Flash device instance
 * param[in] type The type of interrupt to disable/enable if applicable
 * param[in] state Enable or disable
 */
void _flash_set_irq_state(struct _flash_device *const device, const enum _flash_cb_type type, const bool state);

/*
 * Below RWW flash APIs are only available for device which has RWWEE
 * flash array, such as SAM C20/C21/D21/L21/L22/R30/DA1/HA1 etc.
 */
/**
 * \brief Get the RWWEE flash page size.
 *
 * \param[in] device         The pointer to FLASH device instance
 *
 * \return The flash page size
 */
uint32_t _rww_flash_get_page_size(struct _flash_device *const device);

/**
 * \brief Get the total page numbers of RWWEE flash.
 *
 * \param[in] device         The pointer to FLASH device instance
 *
 * \return The flash total page numbers
 */
uint32_t _rww_flash_get_total_pages(struct _flash_device *const device);

/**
 * \brief Reads a number of bytes in the internal RWWEE Flash.
 *
 * \param[in] device         The pointer to FLASH device instance
 * \param[in]  src_addr      Source bytes address to read from flash
 * \param[out] buffer        Pointer to a buffer where the content
 *                           of the read page will be stored
 * \param[in]  length        Number of bytes to read
 *
 * \return Read status, ERR_NONE for successful read.
 */
int32_t _rww_flash_read(struct _flash_device *const device, const uint32_t src_addr, uint8_t *buffer, uint32_t length);

/**
 * \brief Writes a number of bytes in the internal RWWEE Flash.
 *
 * \param[in] device         The pointer to FLASH device instance
 * \param[in]  dst_addr      Destination bytes address to write into flash
 * \param[in]  buffer        Pointer to buffer where the data to
 *                           write is stored
 * \param[in]  length        Number of bytes to write
 *
 * \return Write status, ERR_NONE for successful write.
 */
int32_t _rww_flash_write(struct _flash_device *const device, const uint32_t dst_addr, uint8_t *buffer, uint32_t length);
#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* _HPL_FLASH_H_INCLUDED */
