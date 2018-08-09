/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef NRF_FSTORAGE_H__
#define NRF_FSTORAGE_H__

/**
 * @file
 *
 * @defgroup nrf_fstorage Flash storage (fstorage)
 * @ingroup app_common
 * @{
 *
 * @brief   Flash abstraction library that provides basic read, write, and erase operations.
 *
 * @details The fstorage library can be implemented in different ways. Two implementations are provided:
 * - The @ref nrf_fstorage_sd implements flash access through the SoftDevice.
 * - The @ref nrf_fstorage_nvmc implements flash access through the non-volatile memory controller.
 *
 * You can select the implementation that should be used independently for each instance of fstorage.
 */

#include <stdint.h>
#include <stdbool.h>
#include "sdk_errors.h"
#include "nrf_section.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief   Macro for defining an fstorage instance.
 *
 * Users of fstorage must define an instance variable by using this macro.
 * Each instance is tied to an API implementation and contains information such
 * as the program and erase units for the target flash peripheral.
 * Instance variables are placed in the "fs_data" section of the binary.
 *
 * @param[in]   inst    A definition of an @ref nrf_fstorage_t variable.
 */
#define NRF_FSTORAGE_DEF(inst)          NRF_SECTION_ITEM_REGISTER(fs_data, inst)

/**@brief   Macro for retrieving an fstorage instance. */
#define NRF_FSTORAGE_INSTANCE_GET(i)    NRF_SECTION_ITEM_GET(fs_data, nrf_fstorage_t, (i))

/**@brief   Macro for retrieving the total number of fstorage instances. */
#define NRF_FSTORAGE_INSTANCE_CNT       NRF_SECTION_ITEM_COUNT(fs_data, nrf_fstorage_t)


/**@brief   Event IDs. */
typedef enum
{
    NRF_FSTORAGE_EVT_READ_RESULT,
    NRF_FSTORAGE_EVT_WRITE_RESULT,  //!< Event for @ref nrf_fstorage_write.
    NRF_FSTORAGE_EVT_ERASE_RESULT   //!< Event for @ref nrf_fstorage_erase.
} nrf_fstorage_evt_id_t;


/**@brief   An fstorage event. */
typedef struct
{
    nrf_fstorage_evt_id_t   id;         //!< The event ID.
    ret_code_t              result;     //!< Result of the operation.
    uint32_t                addr;       //!< Address at which the operation was performed.
    void            const * p_src;      //!< Buffer written to flash.
    uint32_t                len;        //!< Length of the operation.
    void                  * p_param;    //!< User-defined parameter passed to the event handler.
} nrf_fstorage_evt_t;


/**@brief   Event handler function prototype.
 *
 * @param[in]   p_evt   The event.
 */
typedef void (*nrf_fstorage_evt_handler_t)(nrf_fstorage_evt_t * p_evt);


/**@brief   Information about the implementation and the flash peripheral. */
typedef struct
{
    uint32_t erase_unit;        //!< Size of a flash page (in bytes). A flash page is the smallest unit that can be erased.
    uint32_t program_unit;      //!< Size of the smallest programmable unit (in bytes).
    bool     rmap;              //!< The device address space is memory mapped to the MCU address space.
    bool     wmap;              //!< The device address space is memory mapped to a writable MCU address space.
} const nrf_fstorage_info_t;


/* Necessary forward declaration. */
struct nrf_fstorage_api_s;


/**@brief   An fstorage instance.
 *
 * @details Use the @ref NRF_FSTORAGE_DEF macro to define an fstorage instance.
 *
 * An instance is tied to an API implementation and contains information about the flash device,
 * such as the program and erase units as well and implementation-specific functionality.
 */
typedef struct
{
    /**@brief   The API implementation used by this instance. */
    struct nrf_fstorage_api_s const * p_api;

    /**@brief   Information about the implementation functionality and the flash peripheral. */
    nrf_fstorage_info_t * p_flash_info;

    /**@brief   The event handler function.
     *
     * If set to NULL, no events will be sent.
     */
    nrf_fstorage_evt_handler_t evt_handler;

    /**@brief   The beginning of the flash space on which this fstorage instance should operate.
     *          All flash operations must be within the address specified in
     *          this field and @ref end_addr.
     *
     * This field must be set manually.
     */
    uint32_t start_addr;

    /**@brief   The last address (exclusive) of flash on which this fstorage instance should operate.
     *          All flash operations must be within the address specified in
     *          this field and @ref start_addr.
     *
     * This field must be set manually.
     */
    uint32_t end_addr;
} nrf_fstorage_t;


/**@brief Functions provided by the API implementation. */
typedef struct nrf_fstorage_api_s
{
    /**@brief Initialize the flash peripheral. */
    ret_code_t (*init)(nrf_fstorage_t * p_fs, void * p_param);
    /**@brief Uninitialize the flash peripheral. */
    ret_code_t (*uninit)(nrf_fstorage_t * p_fs, void * p_param);
    /**@brief Read data from flash. */
    ret_code_t (*read)(nrf_fstorage_t const * p_fs, uint32_t src, void * p_dest, uint32_t len);
    /**@brief Write bytes to flash. */
    ret_code_t (*write)(nrf_fstorage_t const * p_fs, uint32_t dest, void const * p_src, uint32_t len, void * p_param);
    /**@brief Erase flash pages. */
    ret_code_t (*erase)(nrf_fstorage_t const * p_fs, uint32_t addr, uint32_t len, void * p_param);
    /**@brief Map a device address to a readable address within the MCU address space. */
    uint8_t const * (*rmap)(nrf_fstorage_t const * p_fs, uint32_t addr);
    /**@brief Map a device address to a writable address within the MCU address space. */
    uint8_t * (*wmap)(nrf_fstorage_t const * p_fs, uint32_t addr);
    /**@brief Check if there are any pending flash operations. */
    bool (*is_busy)(nrf_fstorage_t const * p_fs);
} const nrf_fstorage_api_t;


/**@brief   Function for initializing fstorage.
 *
 * @param[in]   p_fs        The fstorage instance to initialize.
 * @param[in]   p_api       The API implementation to use.
 * @param[in]   p_param     An optional parameter to pass to the implementation-specific API call.
 *
 * @retval  NRF_SUCCESS         If initialization was successful.
 * @retval  NRF_ERROR_NULL      If @p p_fs or @p p_api field in @p p_fs is NULL.
 * @retval  NRF_ERROR_INTERNAL  If another error occurred.
 */
ret_code_t nrf_fstorage_init(nrf_fstorage_t     * p_fs,
                             nrf_fstorage_api_t * p_api,
                             void               * p_param);


/**@brief   Function for uninitializing an fstorage instance.
 *
 * @param[in]   p_fs        The fstorage instance to uninitialize.
 * @param[in]   p_param     An optional parameter to pass to the implementation-specific API call.
 *
 * @retval  NRF_SUCCESS                 If uninitialization was successful.
 * @retval  NRF_ERROR_NULL              If @p p_fs is NULL.
 * @retval  NRF_ERROR_INVALID_STATE     If the module is not initialized.
 * @retval  NRF_ERROR_INTERNAL          If another error occurred.
 */
ret_code_t nrf_fstorage_uninit(nrf_fstorage_t * p_fs, void * p_param);


/**@brief   Function for reading data from flash.
 *
 * Copy @p len bytes from @p addr to @p p_dest.
 *
 * @param[in]   p_fs    The fstorage instance.
 * @param[in]   addr    Address in flash where to read from.
 * @param[in]   p_dest  Buffer where the data should be copied.
 * @param[in]   len     Length of the data to be copied (in bytes).
 *
 * @retval  NRF_SUCCESS                 If the operation was successful.
 * @retval  NRF_ERROR_NULL              If @p p_fs or @p p_dest is NULL.
 * @retval  NRF_ERROR_INVALID_STATE     If the module is not initialized.
 * @retval  NRF_ERROR_INVALID_LENGTH    If @p len is zero or otherwise invalid.
 * @retval  NRF_ERROR_INVALID_ADDR      If the address @p addr is outside the flash memory
 *                                      boundaries specified in @p p_fs, or if it is unaligned.
 */
ret_code_t nrf_fstorage_read(nrf_fstorage_t const * p_fs,
                             uint32_t               addr,
                             void                 * p_dest,
                             uint32_t               len);


/**@brief   Function for writing data to flash.
 *
 * Write @p len bytes from @p p_src to @p dest.
 *
 * When using @ref nrf_fstorage_sd, the data is written by several calls to @ref sd_flash_write if
 * the length of the data exceeds @ref NRF_FSTORAGE_SD_MAX_WRITE_SIZE bytes.
 * Only one event is sent upon completion.
 *
 * @note The data to be written to flash must be kept in memory until the operation has
 *       terminated and an event is received.
 *
 * @param[in]   p_fs        The fstorage instance.
 * @param[in]   dest        Address in flash memory where to write the data.
 * @param[in]   p_src       Data to be written.
 * @param[in]   len         Length of the data (in bytes).
 * @param[in]   p_param     User-defined parameter passed to the event handler (may be NULL).
 *
 * @retval  NRF_SUCCESS                 If the operation was accepted.
 * @retval  NRF_ERROR_NULL              If @p p_fs or @p p_src is NULL.
 * @retval  NRF_ERROR_INVALID_STATE     If the module is not initialized.
 * @retval  NRF_ERROR_INVALID_LENGTH    If @p len is zero or not a multiple of the program unit,
 *                                      or if it is otherwise invalid.
 * @retval  NRF_ERROR_INVALID_ADDR      If the address @p dest is outside the flash memory
 *                                      boundaries specified in @p p_fs, or if it is unaligned.
 * @retval  NRF_ERROR_NO_MEM            If no memory is available to accept the operation.
 *                                      When using the @ref nrf_fstorage_sd, this error
 *                                      indicates that the internal queue of operations is full.
 */
ret_code_t nrf_fstorage_write(nrf_fstorage_t const * p_fs,
                              uint32_t               dest,
                              void           const * p_src,
                              uint32_t               len,
                              void                 * p_param);


/**@brief   Function for erasing flash pages.
 *
 * @details This function erases @p len pages starting from the page at address @p page_addr.
 *          The erase operation must be initiated on a page boundary.
 *
 * @param[in]   p_fs        The fstorage instance.
 * @param[in]   page_addr   Address of the page to erase.
 * @param[in]   len         Number of pages to erase.
 * @param[in]   p_param     User-defined parameter passed to the event handler (may be NULL).
 *
 * @retval  NRF_SUCCESS                 If the operation was accepted.
 * @retval  NRF_ERROR_NULL              If @p p_fs is NULL.
 * @retval  NRF_ERROR_INVALID_STATE     If the module is not initialized.
 * @retval  NRF_ERROR_INVALID_LENGTH    If @p len is zero.
 * @retval  NRF_ERROR_INVALID_ADDR      If the address @p page_addr is outside the flash memory
 *                                      boundaries specified in @p p_fs, or if it is unaligned.
 * @retval  NRF_ERROR_NO_MEM            If no memory is available to accept the operation.
 *                                      When using the @ref nrf_fstorage_sd, this error
 *                                      indicates that the internal queue of operations is full.
 */
ret_code_t nrf_fstorage_erase(nrf_fstorage_t const * p_fs,
                              uint32_t               page_addr,
                              uint32_t               len,
                              void                 * p_param);


/**@brief   Map a flash address to a pointer in the MCU address space that can be dereferenced.
 *
 * @param   p_fs    The fstorage instance.
 * @param   addr    The address to map.
 *
 * @retval  A pointer to the specified address,
 *          or @c NULL if the address cannot be mapped or if @p p_fs is @c NULL.
 */
uint8_t const * nrf_fstorage_rmap(nrf_fstorage_t const * p_fs, uint32_t addr);


/**@brief   Map a flash address to a pointer in the MCU address space that can be written to.
 *
 * @param   p_fs    The fstorage instance.
 * @param   addr    The address to map.
 *
 * @retval  A pointer to the specified address,
 *          or @c NULL if the address cannot be mapped or if @p p_fs is @c NULL.
 */
uint8_t * nrf_fstorage_wmap(nrf_fstorage_t const * p_fs, uint32_t addr);


/**@brief   Function for querying the status of fstorage.
 *
 * @details An uninitialized instance of fstorage is treated as not busy.
 *
 * @param[in]   p_fs    The fstorage instance. Pass NULL to query all instances.
 *
 * @returns If @p p_fs is @c NULL, this function returns true if any fstorage instance is busy or false otherwise.
 * @returns If @p p_fs is not @c NULL, this function returns true if the fstorage instance is busy or false otherwise.
 */
 bool nrf_fstorage_is_busy(nrf_fstorage_t const * p_fs);

/** @} */


#ifdef __cplusplus
}
#endif

#endif // NRF_FSTORAGE_H__
