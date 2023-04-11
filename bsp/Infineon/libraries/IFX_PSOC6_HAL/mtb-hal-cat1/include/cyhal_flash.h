/***************************************************************************//**
* \file cyhal_flash.h
*
* \brief
* Provides a high level interface for interacting with the Infineon Flash memory.
* This interface abstracts out the chip specific details. If any chip specific
* functionality is necessary, or performance is critical the low level functions
* can be used directly.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_hal_flash Flash (Flash System Routine)
* \ingroup group_hal
* \{
* High level interface to the internal flash memory.
*
* Flash memory provides non-volatile storage for user firmware, user configuration
* data, and bulk data storage.
*
* This driver allows data to be read from and written to flash. It also provides the
* ability to obtain information about the address and characteristics of the flash
* block(s) contained on the device. During flash write time, the device should not be
* reset (including XRES pin, software reset, and watchdog) or unexpected changes may
* be made to portions of the flash. Also, the low-voltage detect circuits should be
* configured to generate an interrupt instead of a reset.
*
* \note A Read while Write violation may occur for some devices when a flash Read
* operation is initiated in the same or neighboring flash sector where the flash
* Write, Erase, or Program operation is working. Refer the the device datasheet
* for more  information. This violation may cause a HardFault exception. To avoid
* the Read while Write violation, the user must carefully split the Read and Write
* operations on flash sectors which are not neighboring, considering all cores in
* a multi-processor device. You may edit the linker script to place the code into
* neighboring sectors. For example, use sectors number 0 and 1 for code and sectors
* 2 and 3 for data storage.
*
* \section features Features
* * Flash operations are performed on a per-page (program) or per-sector (erase) basis
* * Supports blocking or partially blocking erase, program and write
* \section code_snippet Code Snippets
* \subsection subsection_flash_use_case_1 Snippet 1: Discovering flash characteristics
* Following code snippet demonstrates how to discover flash characteristics. Refer \ref
* cyhal_flash_info_t for more information.
* \snippet hal_flash.c snippet_cyhal_flash_get_flash_info
*
* \subsection subsection_flash_use_case_2 Snippet 2: Blocking Flash Write Operation
* Following code snippet demonstrates blocking flash write.
* It uses a constant array with a size equaling the size of one flash row. This
* array is placed at an address in flash such that it occupies one complete flash row.
* It uses blocking flash write operation which blocks the caller until the write is
* completed. It then verifies the flash data by comparing the flash data with the
* written data.
* \snippet hal_flash.c flag_snippet_cyhal_flash_blocking_mode_flashwrite
* \note It is recommended to declare the flash array as global variable.
*
* \subsection subsection_flash_use_case_3 Snippet 3: Non-blocking Flash Write Operation using polling
* Following code snippet implements the non-blocking flash write using polling to
* complete the flash write operation. It uses a constant array with a size equaling
* the size of one flash row. This array is placed at an address in flash such that it
* occupies one complete flash row. It uses a polling method to complete the flash
* write operation. It then verifies the flash data by comparing the flash data with
* the written data.
* \snippet hal_flash.c flag_snippet_cyhal_flash_partially_blocking_mode_polling_flashwrite
* \note It is recommended to declare the flash array as global variable.
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
*       Defines
*******************************************************************************/

/** \addtogroup group_hal_results_flash Flash HAL Results
 *  Flash specific return codes
 *  \ingroup group_hal_results
 *  \{ *//**
 */

/** Invalid argument */
#define CYHAL_FLASH_RSLT_ERR_ADDRESS                    \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_FLASH, 0))
/** API is not supported */
#define CYHAL_FLASH_RSLT_ERR_NOT_SUPPORTED              \
    (CY_RSLT_CREATE_EX(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_ABSTRACTION_HAL, CYHAL_RSLT_MODULE_FLASH, 1))
/** Unable to support due to power state */
/**
 * \}
 */

/** @brief Information about a single block of flash memory */
typedef struct
{
    uint32_t start_address; //!< Start address of the memory
    uint32_t size;          //!< Size of the flash memory
    uint32_t sector_size;   //!< Sector size of the memory
    uint32_t page_size;     //!< Page size of the memory
    uint8_t  erase_value;   //!< The flash erase value
} cyhal_flash_block_info_t;

/** @brief Information about all of the blocks of flash memory */
typedef struct
{
    uint8_t block_count; //!< The number of distinct flash blocks
    const cyhal_flash_block_info_t *blocks; //!< Array of the distinct flash blocks
} cyhal_flash_info_t;


/*******************************************************************************
*       Functions
*******************************************************************************/

/** Initialize the \ref cyhal_flash_t object for accessing flash through the HAL
 *
 * @param[out] obj  Pointer to a flash object. The caller must allocate the memory
 *  for this object but the init function will initialize its contents.
 * @return The status of the init request. Returns \ref CY_RSLT_SUCCESS on successful operation.
 */
cy_rslt_t cyhal_flash_init(cyhal_flash_t *obj);

/** Free resources associated with flash object through the HAL.
 *
 * @param[out] obj The flash object.
 *
 */
void cyhal_flash_free(cyhal_flash_t *obj);

/** Gets flash characteristics like the start address, size, erase values etc.
 * Refer \ref cyhal_flash_info_t for more information.
 *
 * @param[in]  obj  The flash object.
 * @param[out] info The flash characteristic info.
 *
 * Refer \ref subsection_flash_use_case_1 for more information.
 */
void cyhal_flash_get_info(const cyhal_flash_t *obj, cyhal_flash_info_t *info);

/** Read data starting at a defined address.
 *
 * @param[in]  obj     The flash object.
 * @param[in]  address Address to begin reading from.
 * @param[out] data    The buffer to read data into.
 * @param[in]  size    The number of bytes to read.
 * @return The status of the read request. Returns \ref CY_RSLT_SUCCESS on successful operation.
 *
 * Refer \ref subsection_flash_use_case_2 for more information.
 *
 */
cy_rslt_t cyhal_flash_read(cyhal_flash_t *obj, uint32_t address, uint8_t *data, size_t size);

/** Erase one sector starting at a defined address. The address must be at sector boundary. This
 *  will block until the erase operation is complete.
 *
 *  @see cyhal_flash_get_info() to get the flash characteristics for legal address values and
 *  the page erase size.
 *
 * @param[in] obj The flash object
 * @param[in] address The sector starting address
 * @return The status of the erase request. Returns \ref CY_RSLT_SUCCESS on successful operation.
 *
 *  Refer \ref subsection_flash_use_case_2 for more information.
 */
cy_rslt_t cyhal_flash_erase(cyhal_flash_t *obj, uint32_t address);

/** This function erases the page and writes the new data into the page starting at a defined
 *  address. The address must be at page boundary. This will block until the write operation is
 *  complete.
 *
 *  @see cyhal_flash_get_info() to get the flash characteristics for legal address values and
 *  the page write size. The provided data buffer must be at least as large as the flash
 *  page_size.
 *  @note Generally the \p data to be written must be located in the SRAM memory region.
 *
 * @param[in] obj The flash object
 * @param[in] address The page starting address
 * @param[in] data The data to write to the flash
 * @return The status of the write request. Returns \ref CY_RSLT_SUCCESS on successful operation.
 *
 * Refer \ref subsection_flash_use_case_2 for more information.
 */
cy_rslt_t cyhal_flash_write(cyhal_flash_t *obj, uint32_t address, const uint32_t *data);

/** Program one page with given data starting at defined address. The address must be at page
 *  boundary. This will block until the write operation is complete.
 *  \note This function does not erase the page prior to writing. The page must be erased
 *  first via a separate call to erase.
 *
 *  @see cyhal_flash_get_info() to get the flash characteristics for legal address values and
 *  the total page size. The provided data buffer must be at least as large as the flash
 *  page_size.
 *  @note Generally the \p data to be programmed must be located in the SRAM memory region.
 *
 * @param[in] obj The flash object
 * @param[in] address The sector starting address
 * @param[in] data The data buffer to be programmed
 * @return The status of the program request. Returns \ref CY_RSLT_SUCCESS on successful operation.
 */
cy_rslt_t cyhal_flash_program(cyhal_flash_t *obj, uint32_t address, const uint32_t *data);

/** Starts an asynchronous erase of a single sector of flash. Returns immediately and reports
 *  a successful start or reason for failure. The address must be aligned on a sector boundary.
 *
 *  @see cyhal_flash_get_info() to get the flash characteristics for legal address values and
 *  the page erase size.
 *
 * @param[in] obj The Flash object being operated on
 * @param[in] address The address to start erasing from
 * @return The status of the start_erase request.
 *
 * Refer \ref subsection_flash_use_case_3 for more information.
 */
cy_rslt_t cyhal_flash_start_erase(cyhal_flash_t *obj, uint32_t address);

/** Starts an asynchronous write to a single page of flash. Returns immediately and reports
 *  a successful start or reason for failure. The address must be aligned on a page boundary.
 *
 *  @see cyhal_flash_get_info() to get the flash characteristics for legal address values and
 *  the page write size. The provided data buffer must be at least as large as the flash
 *  page_size.
 *  @note Generally the \p data to be written must be located in the SRAM memory region.
 *
 * @param[in] obj The Flash object being operated on
 * @param[in] address The address to start writing to
 * @param[in] data The data to write to flash
 * @return The status of the start_write request.
 *
 * Refer \ref subsection_flash_use_case_3 for more information.
 */
cy_rslt_t cyhal_flash_start_write(cyhal_flash_t *obj, uint32_t address, const uint32_t* data);

/** Starts asynchronous programming of a single page of flash. Returns immediately and reports
 *  a successful start or reason for failure.
 *
 * \note Perform erase operation prior to calling this.
 *
 *  @see cyhal_flash_get_info() to get the flash characteristics for legal address values and
 *  the total page size. The provided data buffer must be at least as large as the flash
 *  page_size.
 *  @note Generally the \p data to be programmed must be located in the SRAM memory region.
 *
 * @param[in] obj The Flash object being operated on
 * @param[in] address The address to start programming
 * @param[in] data The data to write to flash
 * @return The status of the start_program request. Returns \ref CY_RSLT_SUCCESS on successful operation.
 */
cy_rslt_t cyhal_flash_start_program(cyhal_flash_t *obj, uint32_t address, const uint32_t* data);

/** Reports status of the flash operation
 *
 * @param[in]  obj      The Flash object being operated on
 * @return true if flash operation is complete. false otherwise.
 */
bool cyhal_flash_is_operation_complete(cyhal_flash_t *obj);


#if defined(__cplusplus)
}
#endif

#ifdef CYHAL_FLASH_IMPL_HEADER
#include CYHAL_FLASH_IMPL_HEADER
#endif /* CYHAL_FLASH_IMPL_HEADER */

/** \} group_hal_flash */
