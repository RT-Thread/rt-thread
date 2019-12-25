/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#ifndef FDS_H__
#define FDS_H__

/**
 * @defgroup fds Flash Data Storage
 * @ingroup app_common
 * @{
 *
 * @brief   Flash Data Storage (FDS).
 *
 * @details Flash Data Storage is a minimalistic, record-oriented file system for the on-chip
 *          flash. Files are stored as a collection of  records of variable length. FDS supports
 *          synchronous read operations and asynchronous write operations (write, update,
 *          and delete). FDS can be used from multiple threads.
 */

#include <stdint.h>
#include <stdbool.h>
#include "sdk_errors.h"
#include "app_util_platform.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief   Invalid file ID.
 *
 * This value must not be used as a file ID by the application.
 */
#define FDS_FILE_ID_INVALID     (0xFFFF)


/**@brief   Record key for deleted records.
 *
 * This key is used to flag a record as "dirty", which means that it should be removed during
 * the next garbage collection. This value must not be used as a record key by the application.
 */
#define FDS_RECORD_KEY_DIRTY    (0x0000)


/**@brief   FDS return values.
 */
enum
{
    FDS_SUCCESS = NRF_SUCCESS,  //!< The operation completed successfully.
    FDS_ERR_OPERATION_TIMEOUT,  //!< Error. The operation timed out.
    FDS_ERR_NOT_INITIALIZED,    //!< Error. The module has not been initialized.
    FDS_ERR_UNALIGNED_ADDR,     //!< Error. The input data is not aligned to a word boundary.
    FDS_ERR_INVALID_ARG,        //!< Error. The parameter contains invalid data.
    FDS_ERR_NULL_ARG,           //!< Error. The parameter is NULL.
    FDS_ERR_NO_OPEN_RECORDS,    //!< Error. The record is not open, so it cannot be closed.
    FDS_ERR_NO_SPACE_IN_FLASH,  //!< Error. There is no space in flash memory.
    FDS_ERR_NO_SPACE_IN_QUEUES, //!< Error. There is no space in the internal queues.
    FDS_ERR_RECORD_TOO_LARGE,   //!< Error. The record exceeds the maximum allowed size.
    FDS_ERR_NOT_FOUND,          //!< Error. The record was not found.
    FDS_ERR_NO_PAGES,           //!< Error. No flash pages are available.
    FDS_ERR_USER_LIMIT_REACHED, //!< Error. The maximum number of users has been reached.
    FDS_ERR_CRC_CHECK_FAILED,   //!< Error. The CRC check failed.
    FDS_ERR_BUSY,               //!< Error. The underlying flash subsystem was busy.
    FDS_ERR_INTERNAL,           //!< Error. An internal error occurred.
};


/**@brief   The record metadata as stored in flash.
 * @warning Do not edit or reorder the fields in this structure.
 */
typedef struct
{
    uint16_t record_key;    //!< The record key.
    uint16_t length_words;  //!< The length of the record data (in 4-byte words).
    uint16_t file_id;       //!< The ID of the file that the record belongs to.
    uint16_t crc16;         //!< CRC16-CCITT check value.
                            /* The CRC is calculated over the entire record as stored in flash,
                             * including the record metadata except the CRC field itself.
                             */
    uint32_t record_id;     //!< The unique record ID (32 bits).
} fds_header_t;


/**@brief   The record descriptor structure that is used to manipulate records.
 *
 * This structure is used by the FDS module. You must provide the descriptor to the module when
 * you manipulate existing records. However, you should never modify it or use any of its fields.
 *
 * @note Never reuse the same descriptor for different records.
 */
typedef struct
{
    uint32_t         record_id;         //!< The unique record ID.
    uint32_t const * p_record;          //!< The last known location of the record in flash.
    uint16_t         gc_run_count;      //!< Number of times garbage collection has been run.
    bool             record_is_open;    //!< Whether the record is currently open.
} fds_record_desc_t;


/**@brief   Structure that can be used to read the contents of a record stored in flash.
 *
 * This structure does not reflect the physical layout of a record in flash, but it points
 * to the locations where the record header (metadata) and the record data are stored.
 */
typedef struct
{
    fds_header_t const * p_header;  //!< Location of the record header in flash.
    void         const * p_data;    //!< Location of the record data in flash.
} fds_flash_record_t;


/**@brief   A record to be written to flash. */
typedef struct
{
    uint16_t file_id;           //!< The ID of the file that the record belongs to.
    uint16_t key;               //!< The record key.
    struct
    {
        void     const * p_data;
        uint32_t         length_words;
    } data;
} fds_record_t;


/**@brief   A token to a reserved space in flash, created by @ref fds_reserve.
 *
 * This token can be used to write the record in the reserved space (@ref fds_record_write_reserved)
 * or to cancel the reservation (@ref fds_reserve_cancel).
 */
typedef struct
{
    uint16_t page;           //!< The logical ID of the page where space was reserved.
    uint16_t length_words;   //!< The amount of space reserved (in 4-byte words).
} fds_reserve_token_t;


/**@brief   A token to keep information about the progress of @ref fds_record_find,
 *          @ref fds_record_find_by_key, and @ref fds_record_find_in_file.
 *
 * @note    Always zero-initialize the token before using it for the first time.
 * @note    Never reuse the same token to search for different records.
 */
typedef struct
{
    uint32_t const * p_addr;
    uint16_t         page;
} fds_find_token_t;


/**@brief   FDS event IDs.
 */
typedef enum
{
    FDS_EVT_INIT,       //!< Event for @ref fds_init.
    FDS_EVT_WRITE,      //!< Event for @ref fds_record_write and @ref fds_record_write_reserved.
    FDS_EVT_UPDATE,     //!< Event for @ref fds_record_update.
    FDS_EVT_DEL_RECORD, //!< Event for @ref fds_record_delete.
    FDS_EVT_DEL_FILE,   //!< Event for @ref fds_file_delete.
    FDS_EVT_GC          //!< Event for @ref fds_gc.
} fds_evt_id_t;


ANON_UNIONS_ENABLE;

/**@brief   An FDS event. */
typedef struct
{
    fds_evt_id_t id;        //!< The event ID. See @ref fds_evt_id_t.
    ret_code_t   result;    //!< The result of the operation related to this event.
    union
    {
        struct
        {
            uint32_t record_id;
            uint16_t file_id;
            uint16_t record_key;
            bool     is_record_updated;
        } write; //!< Information for @ref FDS_EVT_WRITE and @ref FDS_EVT_UPDATE events.
        struct
        {
            uint32_t record_id;
            uint16_t file_id;
            uint16_t record_key;
        } del; //!< Information for @ref FDS_EVT_DEL_RECORD and @ref FDS_EVT_DEL_FILE events.
    };
} fds_evt_t;

ANON_UNIONS_DISABLE;


/**@brief   File system statistics. */
typedef struct
{
    uint16_t pages_available;   //!< The number of pages available.
    uint16_t open_records;      //!< The number of open records.
    uint16_t valid_records;     //!< The number of valid records.
    uint16_t dirty_records;     //!< The number of deleted ("dirty") records.
    uint16_t words_reserved;    //!< The number of words reserved by @ref fds_reserve().

    /**@brief The number of words written to flash, including those reserved for future writes. */
    uint16_t words_used;

    /**@brief The largest number of free contiguous words in the file system.
     *
     * This number indicates the largest record that can be stored by FDS.
     * It takes into account all reservations for future writes.
     */
    uint16_t largest_contig;

    /**@brief The largest number of words that can be reclaimed by garbage collection.
     *
     * The actual amount of space freed by garbage collection might be less than this value if
     * records are open while garbage collection is run.
     */
    uint16_t freeable_words;

    /**@brief Filesystem corruption has been detected.
     *
     * One or more corrupted records were detected. FDS will heal the filesystem automatically
     * next time garbage collection is run, but some data may be lost.
     *
     * @note: This flag is unrelated to CRC failures.
     */
    bool corruption;
} fds_stat_t;


/**@brief   FDS event handler function prototype.
 *
 * @param   p_evt   The event.
 */
typedef void (*fds_cb_t)(fds_evt_t const * p_evt);


/**@brief   Function for registering an FDS event handler.
 *
 * The maximum amount of handlers that can be registered can be configured by changing the value
 * of @ref FDS_MAX_USERS in fds_config.h.
 *
 * @param[in]   cb  The event handler function.
 *
 * @retval  FDS_SUCCESS                 If the event handler was registered successfully.
 * @retval  FDS_ERR_USER_LIMIT_REACHED  If the maximum number of registered callbacks is reached.
 */
ret_code_t fds_register(fds_cb_t cb);


/**@brief   Function for initializing the module.
 *
 * This function initializes the module and installs the file system (unless it is installed
 * already).
 *
 * This function is asynchronous. Completion is reported through an event. Make sure to call
 * @ref fds_register before calling @ref fds_init so that you receive the completion event.
 *
 * @retval  FDS_SUCCESS         If the operation was queued successfully.
 * @retval  FDS_ERR_NO_PAGES    If there is no space available in flash memory to install the
 *                              file system.
 */
ret_code_t fds_init(void);


/**@brief   Function for writing a record to flash.
 *
 * There are no restrictions on the file ID and the record key, except that the record key must be
 * different from @ref FDS_RECORD_KEY_DIRTY and the file ID must be different from
 * @ref FDS_FILE_ID_INVALID. In particular, no restrictions are made regarding the uniqueness of
 * the file ID or the record key. All records with the same file ID are grouped into one file.
 * If no file with the specified ID exists, it is created. There can be multiple records with the
 * same record key in a file.
 *
 * Some modules need exclusive use of certain file IDs and record keys.
 * See @ref lib_fds_functionality_keys for details.
 *
 * Record data can consist of multiple chunks. The data must be aligned to a 4 byte boundary, and
 * because it is not buffered internally, it must be kept in memory until the callback for the
 * operation has been received. The length of the data must not exceed @ref FDS_VIRTUAL_PAGE_SIZE
 * words minus 14 bytes.
 *
 * This function is asynchronous. Completion is reported through an event that is sent to
 * the registered event handler function.
 *
 * @param[out]  p_desc      The descriptor of the record that was written. Pass NULL if you do not
 *                          need the descriptor.
 * @param[in]   p_record    The record to be written to flash. The record is required to be word
 *                          aligned.
 *
 * @retval  FDS_SUCCESS                 If the operation was queued successfully.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_NULL_ARG            If @p p_record is NULL.
 * @retval  FDS_ERR_INVALID_ARG         If the file ID or the record key is invalid.
 * @retval  FDS_ERR_UNALIGNED_ADDR      If the record data is not aligned to a 4 byte boundary.
 * @retval  FDS_ERR_RECORD_TOO_LARGE    If the record data exceeds the maximum length.
 * @retval  FDS_ERR_NO_SPACE_IN_QUEUES  If the operation queue is full or there are more record
 *                                      chunks than can be buffered.
 * @retval  FDS_ERR_NO_SPACE_IN_FLASH   If there is not enough free space in flash to store the
 *                                      record.
 */
ret_code_t fds_record_write(fds_record_desc_t       * p_desc,
                            fds_record_t      const * p_record);


/**@brief   Function for reserving space in flash.
 *
 * This function can be used to reserve space in flash memory. To write a record into the reserved
 * space, use @ref fds_record_write_reserved. Alternatively, use @ref fds_reserve_cancel to cancel
 * a reservation.
 *
 * Note that this function does not write any data to flash.
 *
 * @param[out]  p_token         A token that can be used to write a record in the reserved space or
 *                              cancel the reservation.
 * @param[in]   length_words    The length of the record data (in 4-byte words).
 *
 * @retval  FDS_SUCCESS                 If the flash space was reserved successfully.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_NULL_ARG            If @p p_token is NULL instead of a valid token address.
 * @retval  FDS_ERR_RECORD_TOO_LARGE    If the record length exceeds the maximum length.
 * @retval  FDS_ERR_NO_SPACE_IN_FLASH   If there is not enough free space in flash to store the
 *                                      record.
 */
ret_code_t fds_reserve(fds_reserve_token_t * p_token, uint16_t length_words);


/**@brief   Function for canceling an @ref fds_reserve operation.
 *
 * @param[in]   p_token     The token that identifies the reservation, produced by @ref fds_reserve.
 *
 * @retval  FDS_SUCCESS             If the reservation was canceled.
 * @retval  FDS_ERR_NOT_INITIALIZED If the module is not initialized.
 * @retval  FDS_ERR_NULL_ARG        If @p p_token is NULL instead of a valid token address.
 * @retval  FDS_ERR_INVALID_ARG     If @p p_token contains invalid data.
 */
ret_code_t fds_reserve_cancel(fds_reserve_token_t * p_token);


/**@brief   Function for writing a record to a space in flash that was reserved using
 *          @ref fds_reserve.
 *
 * There are no restrictions on the file ID and the record key, except that the record key must be
 * different from @ref FDS_RECORD_KEY_DIRTY and the file ID must be different from
 * @ref FDS_FILE_ID_INVALID. In particular, no restrictions are made regarding the uniqueness of
 * the file ID or the record key. All records with the same file ID are grouped into one file.
 * If no file with the specified ID exists, it is created. There can be multiple records with the
 * same record key in a file.
 *
 * Record data can consist of multiple chunks. The data must be aligned to a 4 byte boundary, and
 * because it is not buffered internally, it must be kept in memory until the callback for the
 * operation has been received. The length of the data must not exceed @ref FDS_VIRTUAL_PAGE_SIZE
 * words minus 14 bytes.
 *
 * This function is asynchronous. Completion is reported through an event that is sent to the
 * registered event handler function.
 *
 * @note
 * This function behaves similarly to @ref fds_record_write, with the exception that it never
 * fails with the error @ref FDS_ERR_NO_SPACE_IN_FLASH.
 *
 * @param[out]  p_desc      The descriptor of the record that was written. Pass NULL if you do not
 *                          need the descriptor.
 * @param[in]   p_record    The record to be written to flash. The record is required
 *                          to be word aligned.
 * @param[in]   p_token     The token that identifies the space reserved in flash.
 *
 * @retval  FDS_SUCCESS                 If the operation was queued successfully.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_NULL_ARG            If @p p_token is NULL instead of a valid token address.
 * @retval  FDS_ERR_INVALID_ARG         If the file ID or the record key is invalid.
 * @retval  FDS_ERR_UNALIGNED_ADDR      If the record data is not aligned to a 4 byte boundary.
 * @retval  FDS_ERR_RECORD_TOO_LARGE    If the record data exceeds the maximum length.
 * @retval  FDS_ERR_NO_SPACE_IN_QUEUES  If the operation queue is full or there are more record
 *                                      chunks than can be buffered.
 */
ret_code_t fds_record_write_reserved(fds_record_desc_t         * p_desc,
                                     fds_record_t        const * p_record,
                                     fds_reserve_token_t const * p_token);


/**@brief   Function for deleting a record.
 *
 * Deleted records cannot be located using @ref fds_record_find, @ref fds_record_find_by_key, or
 * @ref fds_record_find_in_file. Additionally, they can no longer be opened using
 * @ref fds_record_open.
 *
 * Note that deleting a record does not free the space it occupies in flash memory.
 * To reclaim flash space used by deleted records, call @ref fds_gc to run garbage collection.
 *
 * This function is asynchronous. Completion is reported through an event that is sent to the
 * registered event handler function.
 *
 * @param[in]   p_desc      The descriptor of the record that should be deleted.
 *
 * @retval  FDS_SUCCESS                 If the operation was queued successfully.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_NULL_ARG            If the specified record descriptor @p p_desc is NULL.
 * @retval  FDS_ERR_NO_SPACE_IN_QUEUES  If the operation queue is full.
 */
ret_code_t fds_record_delete(fds_record_desc_t * p_desc);


/**@brief   Function for deleting all records in a file.
 *
 * This function deletes a file, including all its records. Deleted records cannot be located
 * using @ref fds_record_find, @ref fds_record_find_by_key, or @ref fds_record_find_in_file.
 * Additionally, they can no longer be opened using @ref fds_record_open.
 *
 * Note that deleting records does not free the space they occupy in flash memory.
 * To reclaim flash space used by deleted records, call @ref fds_gc to run garbage collection.
 *
 * This function is asynchronous. Completion is reported through an event that is sent to the
 * registered event handler function.
 *
 * @param[in]   file_id     The ID of the file to be deleted.
 *
 * @retval  FDS_SUCCESS                 If the operation was queued successfully.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_INVALID_ARG         If the specified @p file_id is invalid.
 * @retval  FDS_ERR_NO_SPACE_IN_QUEUES  If the operation queue is full.
 */
ret_code_t fds_file_delete(uint16_t file_id);


/**@brief   Function for updating a record.
 *
 * Updating a record first writes a new record (@p p_record) to flash and then deletes the
 * old record (identified by @p p_desc).
 *
 * There are no restrictions on the file ID and the record key, except that the record key must be
 * different from @ref FDS_RECORD_KEY_DIRTY and the file ID must be different from
 * @ref FDS_FILE_ID_INVALID. In particular, no restrictions are made regarding the uniqueness of
 * the file ID or the record key. All records with the same file ID are grouped into one file.
 * If no file with the specified ID exists, it is created. There can be multiple records with the
 * same record key in a file.
 *
 * Record data can consist of multiple chunks. The data must be aligned to a 4 byte boundary, and
 * because it is not buffered internally, it must be kept in memory until the callback for the
 * operation has been received. The length of the data must not exceed @ref FDS_VIRTUAL_PAGE_SIZE
 * words minus 14 bytes.
 *
 * This function is asynchronous. Completion is reported through an event that is sent to the
 * registered event handler function.
 *
 * @param[in, out]  p_desc      The descriptor of the record to update. When the function
 *                              returns with FDS_SUCCESS, this parameter contains the
 *                              descriptor of the newly written record.
 * @param[in]       p_record    The updated record to be written to flash. The record is required
 *                              to be word aligned.
 *
 * @retval  FDS_SUCCESS                 If the operation was queued successfully.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_INVALID_ARG         If the file ID or the record key is invalid.
 * @retval  FDS_ERR_UNALIGNED_ADDR      If the record data is not aligned to a 4 byte boundary.
 * @retval  FDS_ERR_RECORD_TOO_LARGE    If the record data exceeds the maximum length.
 * @retval  FDS_ERR_NO_SPACE_IN_QUEUES  If the operation queue is full or there are more record
 *                                      chunks than can be buffered.
 * @retval  FDS_ERR_NO_SPACE_IN_FLASH   If there is not enough free space in flash to store the
 *                                      updated record.
 */
ret_code_t fds_record_update(fds_record_desc_t       * p_desc,
                             fds_record_t      const * p_record);


/**@brief   Function for iterating through all records in flash.
 *
 * To search for the next record, call the function again and supply the same @ref fds_find_token_t
 * structure to resume searching from the last record that was found.
 *
 * Note that the order with which records are iterated is not defined.
 *
 * @param[out]  p_desc      The descriptor of the record that was found.
 * @param[out]  p_token     A token containing information about the progress of the operation.
 *
 * @retval  FDS_SUCCESS                 If a record was found.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_NULL_ARG            If @p p_desc or @p p_token is NULL.
 * @retval  FDS_ERR_NOT_FOUND           If no matching record was found.
 */
ret_code_t fds_record_iterate(fds_record_desc_t * p_desc,
                              fds_find_token_t  * p_token);


/**@brief   Function for searching for records with a given record key in a file.
 *
 * This function finds the first record in a file that has the given record key. To search for the
 * next record with the same key in the file, call the function again and supply the same
 * @ref fds_find_token_t structure to resume searching from the last record that was found.
 *
 * @param[in]   file_id     The file ID.
 * @param[in]   record_key  The record key.
 * @param[out]  p_desc      The descriptor of the record that was found.
 * @param[out]  p_token     A token containing information about the progress of the operation.
 *
 * @retval  FDS_SUCCESS                 If a record was found.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_NULL_ARG            If @p p_desc or @p p_token is NULL.
 * @retval  FDS_ERR_NOT_FOUND           If no matching record was found.
 */
ret_code_t fds_record_find(uint16_t            file_id,
                           uint16_t            record_key,
                           fds_record_desc_t * p_desc,
                           fds_find_token_t  * p_token);


/**@brief   Function for searching for records with a given record key.
 *
 * This function finds the first record with a given record key, independent of the file it
 * belongs to. To search for the next record with the same key, call the function again and supply
 * the same @ref fds_find_token_t structure to resume searching from the last record that was found.
 *
 * @param[in]   record_key  The record key.
 * @param[out]  p_desc      The descriptor of the record that was found.
 * @param[out]  p_token     A token containing information about the progress of the operation.
 *
 * @retval  FDS_SUCCESS                 If a record was found.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_NULL_ARG            If @p p_desc or @p p_token is NULL.
 * @retval  FDS_ERR_NOT_FOUND           If no record with the given key was found.
 */
ret_code_t fds_record_find_by_key(uint16_t            record_key,
                                  fds_record_desc_t * p_desc,
                                  fds_find_token_t  * p_token);


/**@brief   Function for searching for any record in a file.
 *
 * This function finds the first record in a file, independent of its record key.
 * To search for the next record in the same file, call the function again and supply the same
 * @ref fds_find_token_t structure to resume searching from the last record that was found.
 *
 * @param[in]   file_id     The file ID.
 * @param[out]  p_desc      The descriptor of the record that was found.
 * @param[out]  p_token     A token containing information about the progress of the operation.
 *
 * @retval  FDS_SUCCESS                 If a record was found.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_NULL_ARG            If @p p_desc or @p p_token is NULL.
 * @retval  FDS_ERR_NOT_FOUND           If no matching record was found.
 */
ret_code_t fds_record_find_in_file(uint16_t            file_id,
                                   fds_record_desc_t * p_desc,
                                   fds_find_token_t  * p_token);


/**@brief   Function for opening a record for reading.
 *
 * This function opens a record that is stored in flash, so that it can be read. The function
 * initializes an @ref fds_flash_record_t structure, which can be used to access the record data as
 * well as its associated metadata. The pointers provided in the @ref fds_flash_record_t structure
 * are pointers to flash memory.
 *
 * Opening a record with @ref fds_record_open prevents garbage collection to run on the virtual
 * flash page in which record is stored, so that the contents of the memory pointed by fields in
 * @ref fds_flash_record_t are guaranteed to remain unmodified as long as the record is kept open.
 *
 * When you are done reading a record, call @ref fds_record_close to close it. Garbage collection
 * can then reclaim space on the virtual page where the record is stored. Note that you must
 * provide the same descriptor for @ref fds_record_close as you did for this function.
 *
 * @param[in]   p_desc          The descriptor of the record to open.
 * @param[out]  p_flash_record  The record, as stored in flash.
 *
 * @retval  FDS_SUCCESS                 If the record was opened successfully.
 * @retval  FDS_ERR_NULL_ARG            If @p p_desc or @p p_flash_record is NULL.
 * @retval  FDS_ERR_NOT_FOUND           If the record was not found. It might have been deleted, or
 *                                      it might not have been written yet.
 * @retval  FDS_ERR_CRC_CHECK_FAILED    If the CRC check for the record failed.
 */
ret_code_t fds_record_open(fds_record_desc_t  * p_desc,
                           fds_flash_record_t * p_flash_record);


/**@brief   Function for closing a record.
 *
 * Closing a record allows garbage collection to run on the virtual page in which the record is
 * stored (if no other records remain open on that page). The descriptor passed as an argument
 * must be the same as the one used to open the record using @ref fds_record_open.
 *
 * Note that closing a record does not invalidate its descriptor. You can still supply the
 * descriptor to all functions that accept a record descriptor as a parameter.
 *
 * @param[in]   p_desc  The descriptor of the record to close.
 *
 * @retval  FDS_SUCCESS             If the record was closed successfully.
 * @retval  FDS_ERR_NULL_ARG        If @p p_desc is NULL.
 * @retval  FDS_ERR_NO_OPEN_RECORDS If the record is not open.
 * @retval  FDS_ERR_NOT_FOUND       If the record could not be found.
 */
ret_code_t fds_record_close(fds_record_desc_t * p_desc);


/**@brief   Function for running garbage collection.
 *
 * Garbage collection reclaims the flash space that is occupied by records that have been deleted,
 * or that failed to be completely written due to, for example, a power loss.
 *
 * This function is asynchronous. Completion is reported through an event that is sent to the
 * registered event handler function.
 *
 * @retval  FDS_SUCCESS                 If the operation was queued successfully.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_NO_SPACE_IN_QUEUES  If the operation queue is full.
 */
ret_code_t fds_gc(void);


/**@brief   Function for obtaining a descriptor from a record ID.
 *
 * This function can be used to reconstruct a descriptor from a record ID, like the one that is
 * passed to the callback function.
 *
 * @note
 * This function does not check whether a record with the given record ID exists.
 * If a non-existing record ID is supplied, the resulting descriptor is invalid and will cause
 * other functions to fail when it is supplied as parameter.
 *
 * @param[out]  p_desc      The descriptor of the record with the given record ID.
 * @param[in]   record_id   The record ID for which a descriptor should be returned.
 *
 * @retval  FDS_SUCCESS         If a descriptor was returned.
 * @retval  FDS_ERR_NULL_ARG    If @p p_desc is NULL.
 */
ret_code_t fds_descriptor_from_rec_id(fds_record_desc_t * p_desc,
                                      uint32_t            record_id);


/**@brief   Function for obtaining a record ID from a record descriptor.
 *
 * This function can be used to extract a record ID from a descriptor. For example, you could use
 * it in the callback function to compare the record ID of an event to the record IDs of the
 * records for which you have a descriptor.
 *
 * @warning
 * This function does not check whether the record descriptor is valid. If the descriptor is not
 * initialized or has been tampered with, the resulting record ID might be invalid.
 *
 * @param[in]   p_desc          The descriptor from which the record ID should be extracted.
 * @param[out]  p_record_id     The record ID that is contained in the given descriptor.
 *
 * @retval  FDS_SUCCESS         If a record ID was returned.
 * @retval  FDS_ERR_NULL_ARG    If @p p_desc or @p p_record_id is NULL.
 */
ret_code_t fds_record_id_from_desc(fds_record_desc_t const * p_desc,
                                   uint32_t                * p_record_id);


/**@brief   Function for retrieving file system statistics.
 *
 * This function retrieves file system statistics, such as the number of open records, the space
 * that can be reclaimed by garbage collection, and others.
 *
 * @param[out]  p_stat      File system statistics.
 *
 * @retval  FDS_SUCCESS                 If the statistics were returned successfully.
 * @retval  FDS_ERR_NOT_INITIALIZED     If the module is not initialized.
 * @retval  FDS_ERR_NULL_ARG            If @p p_stat is NULL.
 */
ret_code_t fds_stat(fds_stat_t * p_stat);


/** @} */


#ifdef __cplusplus
}
#endif

#endif // FDS_H__
