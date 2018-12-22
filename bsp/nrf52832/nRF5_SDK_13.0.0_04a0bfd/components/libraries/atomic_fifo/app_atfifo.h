/**
 * Copyright (c) 2011 - 2017, Nordic Semiconductor ASA
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
#ifndef APP_ATFIFO_H__
#define APP_ATFIFO_H__

#include <stdint.h>
#include "nordic_common.h"
#include "nrf_assert.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_atfifo Atomic FIFO implementation
 * @ingroup app_common
 *
 * @brief @tagAPI52 FIFO implementation that allows for making atomic transactions without
 * locking interrupts.
 *
 * @details There are two types of functions to prepare FIFO writing:
 * - Single function for simple access:
 * @code
 * if(NRF_SUCCESS != nrf_atfifo_put(&my_fifo, &data, NULL))
 * {
 *      // Error handling
 * }
 * @endcode
 * - Function pair to limit data coping:
 * @code
 * struct point3d
 * {
 *      int x, y, z;
 * }point3d_t;
 * nrf_atfifo_context_t context;
 * point3d_t * point;
 *
 * if(NULL != (point = nrf_atfifo_wopen(&my_fifo, &context)))
 * {
 *      ret_code_t ret;
 *      point->x = a;
 *      point->y = b;
 *      point->z = c;
 *      if(nrf_atfifo_wcommit(&my_fifo, &context))
 *      {
 *          // Send an information to the rest of the system
 *          // that there is new data in the FIFO available to read.
 *      }
 * }
 * else
 * {
 *      // Error handling
 * }
 *
 * @endcode
 * @note
 * This Atomic FIFO implementation requires that the operation that was
 * opened last would be finished (committed/flushed) first.
 * This is typical for operations performed from the interrupt runtime
 * when the other operation is performed from main thread.
 *
 * This implementation does not support typical multithreading operating system
 * access where operations can be started and finished in totally unrelated order.
 *
 * @{
 */

/**
 * @brief Read and write position structure
 *
 * A structure that holds read and write position used by fifo head and tail.
 */
typedef struct nrf_atfifo_postag_pos_s
{
    uint16_t wr; //!< First free space to write a data
    uint16_t rd; //!< A place after the last data to read
}nrf_atfifo_postag_pos_t;

/**
 * @brief End data index tag
 *
 * A tag used to mark end of data.
 * To properly realize atomic data committing the whole variable has to be
 * accessed atomically.
 */
typedef union nrf_atfifo_postag_u
{
    uint32_t                tag; //!< Whole tag, used for atomic, 32 bit access
    nrf_atfifo_postag_pos_t pos; //! Structure that holds reading and writing position separately
}nrf_atfifo_postag_t;

/**
 * @brief The FIFO instance
 *
 * The instance of atomic FIFO.
 * Used with all FIFO functions.
 */
typedef struct app_atfifo_s
{
    void                * p_buf;     //!< Pointer to the data buffer
    nrf_atfifo_postag_t   tail;      //!< Read and write tail position tag
    nrf_atfifo_postag_t   head;      //!< Read and write head position tag
    uint16_t              buf_size;  //!< FIFO size in number of bytes (has to be divisible by @c item_size)
    uint16_t              item_size; //!< Size of single FIFO item
}app_atfifo_t;

/**
 * @brief FIFO write operation context
 *
 * Context structure used to mark opened commit.
 * All the data required to properly access the data and then commit it after writing.
 */
typedef struct app_atfifo_wcontext_s
{
    nrf_atfifo_postag_t last_tail; //!< Tail tag value that was here when opening FIFO to write
}app_atfifo_wcontext_t;


/**
 * @brief FIFO read operation context
 *
 * Context structure used to mark opened read operation.
 * All the data required to properly flush the accessed data after accessing.
 */
typedef struct app_atfifo_rcontext_s
{
    nrf_atfifo_postag_t last_head; //!< Head tag value that was here when opening FIFO to read
}app_atfifo_rcontext_t;


/**
 * @defgroup app_atfifo_instmacros FIFO instance macros
 *
 * A group of macros helpful for FIFO instance creation and initialization.
 * They may be used to create and initialize instances for most use cases.
 *
 * FIFO may also be created and initialized directly using
 * @ref app_atfifo_init function.
 * @{
 */
    /**
     * @brief Macro to generate the name for data buffer
     *
     * The name of the data buffer that would be created by
     * @ref APP_ATFIFO_DEF macro.
     *
     * @param[in] fifo_id The identifier of the FIFO object.
     *
     * @return The name of the buffer variable.
     */
    #define APP_ATFIFO_BUF_NAME(fifo_id) CONCAT_2(fifo_id, _data)

    /**
     * @brief Macro to generate the name for FIFO instance
     *
     * The name of instance variable that would be created by
     * @ref APP_ATFIFO_DEF macro.
     *
     * @param[in] fifo_id The identifier of the FIFO object.
     *
     * @return The name of the instance variable.
     */
    #define APP_ATFIFO_INST_NAME(fifo_id) CONCAT_2(fifo_id, _inst)

    /**
     * @brief Instance creation macro
     *
     * Creates FIFO object variable itself and
     *
     * Use example:
     * @code
     * APP_ATFIFO_DEF(my_fifo, uint16_t, 12);
     * APP_ATFIFO_INIT(my_fifo);
     *
     * uint16_t some_val = 45;
     * app_atfifo_put(my_fifo, &some_val, sizeof(some_val), NULL);
     * app_atfifo_get(my_fifo, &some_val, sizeof(some_val), NULL);
     * @endcode
     *
     * @param[in] fifo_id      The identifier of FIFO object.
     *                         This identifier would be a pointer to the instance.
     *                         It makes it possible to use this directly for the functions
     *                         that operates on the FIFO.
     *                         Because it is static const object, it should be optimized by the compiler.
     * @param[in] storage_type The type of data that would be stored in the FIFO.
     * @param[in] item_cnt     The capacity of created FIFO in maximum number of items that may be stored.
     *                         The phisical size of the buffer would be 1 element bigger.
     */
    #define APP_ATFIFO_DEF(fifo_id, storage_type, item_cnt)                 \
        static storage_type APP_ATFIFO_BUF_NAME(fifo_id)[(item_cnt)+1];     \
        static app_atfifo_t APP_ATFIFO_INST_NAME(fifo_id);                  \
        static app_atfifo_t * const fifo_id = &APP_ATFIFO_INST_NAME(fifo_id)

    /**
     * @brief Use this macro to initialize FIFO declared previously by the macro
     *
     * Use this macro to simplify FIFO initialization.
     *
     * @note
     * This macro can be only used on FIFO object defined by @ref APP_ATFIFO_DEF macro.
     *
     * @param[in] fifo_id The identifier of the FIFO object.
     *
     * @return The value from @ref app_atfifo_init function.
     */
    #define APP_ATFIFO_INIT(fifo_id)                \
        app_atfifo_init(                            \
            fifo_id,                                \
            &APP_ATFIFO_BUF_NAME(fifo_id),          \
            sizeof(APP_ATFIFO_BUF_NAME(fifo_id)),   \
            sizeof(APP_ATFIFO_BUF_NAME(fifo_id)[0]) \
        )

/** @} */

/**
 * @brief Initializing the FIFO
 *
 * Preparing FIFO instance to work.
 *
 * @param[out]    p_fifo    FIFO object to initialize.
 * @param[in,out] p_buf     FIFO buffer for storing data.
 * @param[in]     buf_size  Total buffer size (has to be divisible by @c item_size).
 * @param[in]     item_size Size of single item hold inside the FIFO.
 *
 * @retval     NRF_SUCCESS              If initialization was successful.
 * @retval     NRF_ERROR_NULL           If a NULL pointer is provided as buffer.
 * @retval     NRF_ERROR_INVALID_LENGTH If size of buffer provided is divisible by @c item_size.
 *
 * @note
 * Buffer size has to be able to fit 1 element more than designed FIFO capacity.
 * This one, empty element is used for overflow checking.
 */
ret_code_t app_atfifo_init(app_atfifo_t * const p_fifo, void * p_buf, uint16_t buf_size, uint16_t item_size);

/**
 * @brief Clear the FIFO
 *
 * Clearing the FIFO.
 *
 * If this function is called during some opened and uncommitted write operation,
 * the FIFO would be cleared up to the currently ongoing commit.
 * There is no possibility to cancel ongoing commit.
 *
 * If this function is called during some opened and unflushed read operation,
 * the read position in head would be set, but copying it into write head position
 * would be left to read closing operation.
 *
 * This way there would be no more data to read, but the memory would be released
 * in the moment when it is safe.
 *
 * @param[in,out] p_fifo FIFO object.
 *
 * @retval NRF_SUCCESS    FIFO totally cleared
 * @retval NRF_ERROR_BUSY Function called in the middle of writing or reading operation.
 *                        If we are in the middle of writing operation,
 *                        FIFO was cleared up to the already started, and uncommitted write.
 *                        If we are in the middle of write operation,
 *                        write head was only moved. It would be copied into read tail when reading operation
 *                        would be flushed.
 */
ret_code_t app_atfifo_clear(app_atfifo_t * const p_fifo);

/**
 * @brief Put data into FIFO
 *
 * Function to that puts data into the FIFO atomically.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[in]     p_var     Variable to copy.
 * @param[in]     size      Size of the variable to copy.
 *                          Can be smaller or equal to the FIFO item size.
 * @param[out]    p_visible See value returned by @ref app_atfifo_wcommit.
 *                          If may be NULL if the caller does not care about current operation status.
 *
 * @retval NRF_SUCCESS      If an element has been successfully added to the FIFO.
 * @retval NRF_ERROR_NO_MEM If the FIFO is full.
 *
 * @note
 * To avoid data copying one may use @ref app_atfifo_wopen and @ref app_atfifo_wcommit
 * functions pair.
 */
ret_code_t app_atfifo_put(app_atfifo_t * const p_fifo, void const * const p_var, size_t size, bool * const p_visible);

/**
 * @brief Open FIFO for writing, internal function
 *
 * Function called to start FIFO write operation and access the given FIFO buffer directly.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[out]    p_context The operation context, required by @ref app_atfifo_wcommit.
 *
 * @return Pointer to the space where variable data may be stored.
 *         NULL if there is no space in the buffer.
 *
 * @note
 * Do not use this function directly.
 * Use @ref app_atfifo_wopen instead.
 */
void * app_atfifo_wopen_internal(app_atfifo_t * const p_fifo, app_atfifo_wcontext_t * p_context);

/**
 * @brief Open FIFO for writing
 *
 * Function called to start FIFO write operation and access the given FIFO buffer directly.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[out]    p_context The operation context, required by @ref app_atfifo_wcommit.
 * @param[in]     size      Requested size of the buffer. Currently used only for integrity checking when debugging.
 *
 * @return Pointer to the space where variable data may be stored.
 *         NULL if there is no space in the buffer.
 *
 * @note Always finish writing operation by @ref app_atfifo_wcommit
 */
static inline void * app_atfifo_wopen(app_atfifo_t * const p_fifo, app_atfifo_wcontext_t * p_context, size_t size)
{
    ASSERT(size <= p_fifo->item_size);
    UNUSED_PARAMETER(size);
    return app_atfifo_wopen_internal(p_fifo, p_context);
}

/**
 * @brief Close the writing operation
 *
 * Function need to be called to finally commit opened write operation.
 * It sets all the buffers and finally mark the data to be visible to read.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[in]     p_context Operation context, filled by the @ref app_atfifo_wopen function.
 *
 * @retval true  The data is actually ready and would be visible to read.
 * @retval false The internal commit was marked, but the writing operation interrupted another writing operation.
 *               The data would be available to read when the interrupted operation would be committed.
 */
bool app_atfifo_wcommit(app_atfifo_t * const p_fifo, app_atfifo_wcontext_t * p_context);

/**
 * @brief Get single value from the FIFO
 *
 * Function gets the value from the top from the FIFO.
 * The value is removed from the FIFO memory.
 *
 * @param[in,out] p_fifo     FIFO object.
 * @param[out]    p_var      Pointer to the variable to store data.
 * @param[in]     size       Size of the data we are going to load.
 * @param[out]    p_released See the values returned by @ref app_atfifo_rflush.
 *
 * @retval NRF_SUCCESS         Element was successfully copied from FIFO memory.
 * @retval NRF_ERROR_NOT_FOUND No data in the FIFO.
 */
ret_code_t app_atfifo_get(app_atfifo_t * const p_fifo, void * const p_var, size_t size, bool * p_released);

/**
 * @brief Open FIFO for reading, internal function
 *
 * Function called to start FIFO read operation and access the given FIFO buffer directly.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[out]    p_context The operation context, required by @ref app_atfifo_rflush
 *
 * @return Pointer to data buffer or NULL if there is no data in the FIFO.
 *
 * @note
 * Do not use this function directly.
 * Use @ref app_atfifo_ropen instead.
 */
void const * app_atfifo_ropen_internal(app_atfifo_t * const p_fifo, app_atfifo_rcontext_t * p_context);


/**
 * @brief  Open FIFO for reading
 *
 * Function called to start FIFO read operation and access the FIFO buffer directly.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[out]    p_context The operation context, required by @ref app_atfifo_rflush
 * @param[in]     size      Requested size of the buffer. Currently used only for integrity checking when debugging.
 *
 * @return Pointer to data buffer or NULL if there is no data in the FIFO.
 */
static inline void const * app_atfifo_ropen(app_atfifo_t * const p_fifo, app_atfifo_rcontext_t * p_context, size_t size)
{
    ASSERT(size <= p_fifo->item_size);
    UNUSED_PARAMETER(size);
    return app_atfifo_ropen_internal(p_fifo, p_context);
}

/**
 * @brief Close reading operation
 *
 * Function used to finish reading operation.
 * If this reading operation did not interrupt another reading operation the head write buffer is moved.
 * If this reading operation was placed in the middle of another reading, the new read pointer is only written.
 *
 * @param[in,out] p_fifo    FIFO object.
 * @param[in]     p_context Context of the reading operation that we are going to close.
 *
 * @retval true  This operation is not generated in the middle of another read operation and the write head would be updated to read head (space is released).
 * @retval false This operation was performed in the middle of another read operation and the write buffer head was not moved (no space is released).
 */
bool app_atfifo_rflush(app_atfifo_t * const p_fifo, app_atfifo_rcontext_t * p_context);


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_ATFIFO_H__ */
