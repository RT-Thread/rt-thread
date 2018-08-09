/**
 * Copyright (c) 2011 - 2018, Nordic Semiconductor ASA
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
#ifndef NRF_ATFIFO_H__
#define NRF_ATFIFO_H__

#include <stdint.h>
#include <stdbool.h>
#include "sdk_config.h"
#include "nordic_common.h"
#include "nrf_assert.h"
#include "sdk_errors.h"
#include "nrf_log_instance.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_atfifo Atomic FIFO
 * @ingroup app_common
 *
 * @brief @tagAPI52 FIFO implementation that allows for making atomic transactions without
 * locking interrupts.
 *
 * @details There are two types of functions to prepare the FIFO writing:
 * - Single function for simple access:
 * @code
 * if (NRF_SUCCESS != nrf_atfifo_simple_put(my_fifo, &data, NULL))
 * {
 *      // Error handling
 * }
 * @endcode
 * - Function pair to limit data copying:
 * @code
 * struct point3d
 * {
 *      int x, y, z;
 * }point3d_t;
 * nrf_atfifo_context_t context;
 * point3d_t * point;
 *
 * if (NULL != (point = nrf_atfifo_item_alloc(my_fifo, &context)))
 * {
 *      point->x = a;
 *      point->y = b;
 *      point->z = c;
 *      if (nrf_atfifo_item_put(my_fifo, &context))
 *      {
 *          // Send information to the rest of the system
 *          // that there is new data in the FIFO available for reading.
 *      }
 * }
 * else
 * {
 *      // Error handling
 * }
 *
 * @endcode
 * @note
 * This atomic FIFO implementation requires that the operation that is
 * opened last is finished (committed/flushed) first.
 * This is typical for operations performed from the interrupt runtime
 * when the other operation is performed from the main thread.
 *
 * This implementation does not support typical multithreading operating system
 * access where operations can be started and finished in totally unrelated order.
 *
 * @{
 */

/**
 * @brief Read and write position structure.
 *
 * A structure that holds the read and write position used by the FIFO head and tail.
 */
typedef struct nrf_atfifo_postag_pos_s
{
    uint16_t wr; //!< First free space to write the data
    uint16_t rd; //!< A place after the last data to read
}nrf_atfifo_postag_pos_t;

/**
 * @brief End data index tag.
 *
 * A tag used to mark the end of data.
 * To properly realize atomic data committing, the whole variable has to be
 * accessed atomically.
 */
typedef union nrf_atfifo_postag_u
{
    uint32_t                tag; //!< Whole tag, used for atomic, 32-bit access
    nrf_atfifo_postag_pos_t pos; //!< Structure that holds reading and writing position separately
}nrf_atfifo_postag_t;

/**
 * @brief The FIFO instance.
 *
 * The instance of atomic FIFO.
 * Used with all FIFO functions.
 */
typedef struct nrf_atfifo_s
{
    void                * p_buf;        //!< Pointer to the data buffer
    nrf_atfifo_postag_t   tail;         //!< Read and write tail position tag
    nrf_atfifo_postag_t   head;         //!< Read and write head position tag
    uint16_t              buf_size;     //!< FIFO size in number of bytes (has to be divisible by @c item_size)
    uint16_t              item_size;    //!< Size of a single FIFO item
    NRF_LOG_INSTANCE_PTR_DECLARE(p_log) //!< Pointer to instance of the logger object (Conditionally compiled).
}nrf_atfifo_t;

/**
 * @brief FIFO write operation item context.
 *
 * Context structure used to mark an allocated space in FIFO that is ready for put.
 * All the data required to properly put allocated and written data.
 */
typedef struct nrf_atfifo_item_put_s
{
    nrf_atfifo_postag_t last_tail; //!< Tail tag value that was here when opening the FIFO to write
}nrf_atfifo_item_put_t;


/**
 * @brief FIFO read operation item context.
 *
 * Context structure used to mark an opened get operation to properly free an item after reading.
 */
typedef struct nrf_atfifo_rcontext_s
{
    nrf_atfifo_postag_t last_head; //!< Head tag value that was here when opening the FIFO to read
}nrf_atfifo_item_get_t;


/** @brief Name of the module used for logger messaging.
 */
#define NRF_ATFIFO_LOG_NAME atfifo

/**
 * @defgroup nrf_atfifo_instmacros FIFO instance macros
 *
 * A group of macros helpful for FIFO instance creation and initialization.
 * They may be used to create and initialize instances for most use cases.
 *
 * FIFO may also be created and initialized directly using
 * @ref nrf_atfifo_init function.
 * @{
 */
    /**
     * @brief Macro for generating the name for a data buffer.
     *
     * The name of the data buffer that would be created by
     * @ref NRF_ATFIFO_DEF macro.
     *
     * @param[in] fifo_id Identifier of the FIFO object.
     *
     * @return Name of the buffer variable.
     *
     * @note This is auxiliary internal macro and in normal usage
     *       it should not be called.
     */
    #define NRF_ATFIFO_BUF_NAME(fifo_id) CONCAT_2(fifo_id, _data)

    /**
     * @brief Macro for generating the name for a FIFO instance.
     *
     * The name of the instance variable that will be created by the
     * @ref NRF_ATFIFO_DEF macro.
     *
     * @param[in] fifo_id Identifier of the FIFO object.
     *
     * @return Name of the instance variable.
     *
     * @note This is auxiliary internal macro and in normal usage
     *       it should not be called.
     */
    #define NRF_ATFIFO_INST_NAME(fifo_id) CONCAT_2(fifo_id, _inst)

    /**
     * @brief Macro for creating an instance.
     *
     * Creates the FIFO object variable itself.
     *
     * Usage example:
     * @code
     * NRF_ATFIFO_DEF(my_fifo, uint16_t, 12);
     * NRF_ATFIFO_INIT(my_fifo);
     *
     * uint16_t some_val = 45;
     * nrf_atfifo_item_put(my_fifo, &some_val, sizeof(some_val), NULL);
     * nrf_atfifo_item_get(my_fifo, &some_val, sizeof(some_val), NULL);
     * @endcode
     *
     * @param[in] fifo_id      Identifier of a FIFO object.
     *                         This identifier will be a pointer to the instance.
     *                         It makes it possible to use this directly for the functions
     *                         that operate on the FIFO.
     *                         Because it is a static const object, it should be optimized by the compiler.
     * @param[in] storage_type Type of data that will be stored in the FIFO.
     * @param[in] item_cnt     Capacity of the created FIFO in maximum number of items that may be stored.
     *                         The phisical size of the buffer will be 1 element bigger.
     */
    #define NRF_ATFIFO_DEF(fifo_id, storage_type, item_cnt)                                     \
        static storage_type NRF_ATFIFO_BUF_NAME(fifo_id)[(item_cnt)+1];                         \
        NRF_LOG_INSTANCE_REGISTER(NRF_ATFIFO_LOG_NAME, fifo_id,                                 \
                                  NRF_ATFIFO_CONFIG_INFO_COLOR,                                 \
                                  NRF_ATFIFO_CONFIG_DEBUG_COLOR,                                \
                                  NRF_ATFIFO_CONFIG_LOG_INIT_FILTER_LEVEL,                      \
                                  NRF_ATFIFO_CONFIG_LOG_ENABLED ?                               \
                                          NRF_ATFIFO_CONFIG_LOG_LEVEL : NRF_LOG_SEVERITY_NONE); \
        static nrf_atfifo_t NRF_ATFIFO_INST_NAME(fifo_id) = {                                   \
                .p_buf = NULL,                                                                  \
                NRF_LOG_INSTANCE_PTR_INIT(p_log, NRF_ATFIFO_LOG_NAME, fifo_id)                  \
        };                                                                                      \
        static nrf_atfifo_t * const fifo_id = &NRF_ATFIFO_INST_NAME(fifo_id)

    /**
     * @brief Macro for initializing the FIFO that was previously declared by the macro.
     *
     * Use this macro to simplify FIFO initialization.
     *
     * @note
     * This macro can be only used on a FIFO object defined by @ref NRF_ATFIFO_DEF macro.
     *
     * @param[in] fifo_id Identifier of the FIFO object.
     *
     * @return Value from the @ref nrf_atfifo_init function.
     */
    #define NRF_ATFIFO_INIT(fifo_id)                \
        nrf_atfifo_init(                            \
            fifo_id,                                \
            NRF_ATFIFO_BUF_NAME(fifo_id),           \
            sizeof(NRF_ATFIFO_BUF_NAME(fifo_id)),   \
            sizeof(NRF_ATFIFO_BUF_NAME(fifo_id)[0]) \
        )

/** @} */

/**
 * @brief Function for initializing the FIFO.
 *
 * Preparing the FIFO instance to work.
 *
 * @param[out]    p_fifo    FIFO object to initialize.
 * @param[in,out] p_buf     FIFO buffer for storing data.
 * @param[in]     buf_size  Total buffer size (has to be divisible by @c item_size).
 * @param[in]     item_size Size of a single item held inside the FIFO.
 *
 * @retval     NRF_SUCCESS              If initialization was successful.
 * @retval     NRF_ERROR_NULL           If a NULL pointer is provided as the buffer.
 * @retval     NRF_ERROR_INVALID_LENGTH If size of the buffer provided is not divisible by @c item_size.
 *
 * @note
 * Buffer size must be able to hold one element more than the designed FIFO capacity.
 * This one, empty element is used for overflow checking.
 */
ret_code_t nrf_atfifo_init(nrf_atfifo_t * const p_fifo, void * p_buf, uint16_t buf_size, uint16_t item_size);

/**
 * @brief Function for clearing the FIFO.
 *
 * Function for clearing the FIFO.
 *
 * If this function is called during an opened and uncommitted write operation,
 * the FIFO is cleared up to the currently ongoing commit.
 * There is no possibility to cancel an ongoing commit.
 *
 * If this function is called during an opened and unflushed read operation,
 * the read position in the head is set, but copying it into the write head position
 * is left to read closing operation.
 *
 * This way, there is no more data to read, but the memory is released
 * in the moment when it is safe.
 *
 * @param[in,out] p_fifo FIFO object.
 *
 * @retval NRF_SUCCESS    FIFO totally cleared.
 * @retval NRF_ERROR_BUSY Function called in the middle of writing or reading operation.
 *                        If it is called in the middle of writing operation,
 *                        FIFO was cleared up to the already started and uncommitted write.
 *                        If it is called in the middle of reading operation,
 *                        write head was only moved. It will be copied into read tail when the reading operation
 *                        is flushed.
 */
ret_code_t nrf_atfifo_clear(nrf_atfifo_t * const p_fifo);

/**
 * @brief Function for atomically putting data into the FIFO.
 *
 * It uses memcpy function inside and in most situations, it is more suitable to
 * use @ref nrf_atfifo_item_alloc, write the data, and @ref nrf_atfifo_item_put to store a new value
 * in a FIFO.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[in]     p_var     Variable to copy.
 * @param[in]     size      Size of the variable to copy.
 *                          Can be smaller or equal to the FIFO item size.
 * @param[out]    p_visible See value returned by @ref nrf_atfifo_item_put.
 *                          It may be NULL if the caller does not require the current operation status.
 *
 * @retval NRF_SUCCESS      If an element has been successfully added to the FIFO.
 * @retval NRF_ERROR_NO_MEM If the FIFO is full.
 *
 * @note
 * To avoid data copying, you can use the @ref nrf_atfifo_item_alloc and @ref nrf_atfifo_item_put
 * functions pair.
 */
ret_code_t nrf_atfifo_alloc_put(nrf_atfifo_t * const p_fifo, void const * const p_var, size_t size, bool * const p_visible);

/**
 * @brief Function for opening the FIFO for writing.
 *
 * Function called to start the FIFO write operation and access the given FIFO buffer directly.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[out]    p_context Operation context, required by @ref nrf_atfifo_item_put.
 *
 * @return Pointer to the space where variable data can be stored.
 *         NULL if there is no space in the buffer.
 */
void * nrf_atfifo_item_alloc(nrf_atfifo_t * const p_fifo, nrf_atfifo_item_put_t * p_context);

/**
 * @brief Function for closing the writing operation.
 *
 * Puts a previously allocated context into FIFO.
 * This function must be called to commit an opened write operation.
 * It sets all the buffers and marks the data, so that it is visible to read.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[in]     p_context Operation context, filled by the @ref nrf_atfifo_item_alloc function.
 *
 * @retval true  Data is currently ready and will be visible to read.
 * @retval false The internal commit was marked, but the writing operation interrupted another writing operation.
 *               The data will be available to read when the interrupted operation is committed.
 */
bool nrf_atfifo_item_put(nrf_atfifo_t * const p_fifo, nrf_atfifo_item_put_t * p_context);

/**
 * @brief Function for getting a single value from the FIFO.
 *
 * This function gets the value from the top of the FIFO.
 * The value is removed from the FIFO memory.
 *
 * @param[in,out] p_fifo     FIFO object.
 * @param[out]    p_var      Pointer to the variable to store the data.
 * @param[in]     size       Size of the data to be loaded.
 * @param[out]    p_released See the values returned by @ref nrf_atfifo_item_free.
 *
 * @retval NRF_SUCCESS         Element was successfully copied from the FIFO memory.
 * @retval NRF_ERROR_NOT_FOUND No data in the FIFO.
 */
ret_code_t nrf_atfifo_get_free(nrf_atfifo_t * const p_fifo, void * const p_var, size_t size, bool * p_released);

/**
 * @brief Function for opening the FIFO for reading.
 *
 * Function called to start the FIFO read operation and access the given FIFO buffer directly.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[out]    p_context The operation context, required by @ref nrf_atfifo_item_free
 *
 * @return Pointer to data buffer or NULL if there is no data in the FIFO.
 */
void * nrf_atfifo_item_get(nrf_atfifo_t * const p_fifo, nrf_atfifo_item_get_t * p_context);

/**
 * @brief Function for closing the reading operation.
 *
 * Function used to finish the reading operation.
 * If this reading operation does not interrupt another reading operation, the head write buffer is moved.
 * If this reading operation is placed in the middle of another reading, only the new read pointer is written.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[in]     p_context Context of the reading operation to be closed.
 *
 * @retval true  This operation is not generated in the middle of another read operation and the write head will be updated to the read head (space is released).
 * @retval false This operation was performed in the middle of another read operation and the write buffer head was not moved (no space is released).
 */
bool nrf_atfifo_item_free(nrf_atfifo_t * const p_fifo, nrf_atfifo_item_get_t * p_context);


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* NRF_ATFIFO_H__ */
