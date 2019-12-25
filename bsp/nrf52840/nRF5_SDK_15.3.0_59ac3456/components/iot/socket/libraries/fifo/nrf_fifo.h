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
#ifndef NRF_FIFO_H__
#define NRF_FIFO_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file nrf_fifo.h
 *
 * @defgroup iot_socket_fifo FIFO
 * @ingroup iot_sdk_socket
 * @{
 * @brief A wait-free bounded FIFO of pointers for single producer/single consumer use.
 *
 * This FIFO is safe to use in single producer/single consumer patterns. In addition, the following
 * restrictions apply for init/deinit:
 *
 * a) nrf_fifo_enq() and nrf_fifo_deq() may only be called after nrf_fifo_init() is called.
 *
 * b) All calls to nrf_fifo_enq() and nrf_fifo_deq() must be finished and no new calls must be made before nrf_fifo_deinit() is called.
 *
 * These restrictions must be handled by the user of the module, for instance by using a mutex.
 */

/**
 * @brief Wait function for blocking enqueue/dequeue.
 *
 * Should return NRF_SUCCESS as long as there are no errors while waiting.
 */
typedef uint32_t (*fifo_wait_fn)(void);

/**
 * @brief Flush function called on deinit.
 *
 * On deinit, this function will be called with each remaining element in the FIFO as argument. This
 * can be used to ensure that memory is deallocated properly.
 *
 * @param[in] p_data Pointer to data that is flushed from FIFO.
 */
typedef void (*fifo_flush_fn)(void * p_data);

/**
 * @brief FIFO data structure.
 */
typedef struct {
    void           ** pp_elements; /**< The array of elements in the FIFO.      */
    uint32_t          nmemb;       /**< The number of elements in this FIFO.    */
    fifo_wait_fn      wait;        /**< The wait function used if blocking.     */
    fifo_flush_fn     flush;       /**< The flush function used on deinit.      */
    volatile uint32_t read_pos;    /**< Read pointer to next element to read.   */
    volatile uint32_t write_pos;   /**< Write pointer to next element to write. */
} nrf_fifo_t;

/**
 * @brief Function for initializing the FIFO.
 *
 * @param[out] p_fifo   The FIFO to initialize.
 * @param[in]  nmemb    The maximum number of elements in the FIFO.
 * @param[in]  wait_fn  The wait function to use for blocking enqueue/dequeue. If NULL, the enq/deq
 *                      functions will never block.
 * @param[in]  flush_fn The flush function to call on deinit. If NULL, the flush function will not
 *                      be called.
 *
 * @retval NRF_SUCCESS if fifo was initialized successfully.
 */
uint32_t nrf_fifo_init(nrf_fifo_t * p_fifo, uint32_t nmemb, fifo_wait_fn wait_fn, fifo_flush_fn flush_fn);

/**
 * @brief Function for deinitializing the FIFO.
 *
 * Frees all memory allocated by this FIFO. All elements are removed. If a flush function was
 * specified in nrf_fifo_init(), the function will be called for each remaining element in the
 * FIFO.
 *
 * @param[in, out] p_fifo The FIFO to deinitialize.
 */
void nrf_fifo_deinit(nrf_fifo_t * p_fifo);

/**
 * @brief Function for enqueuing an element on the FIFO.
 *
 * @param[in, out] p_fifo The FIFO to enqueue elements on.
 * @param[in]      p_ctx  The pointer to enqueue.
 * @param[in]      wait   If true, this function will block until the FIFO has available space. Any
 *                        errors returned by this function will be propagated to the caller.
 *
 * @retval NRF_SUCCESS if the element was queued.
 * @retval NRF_ERROR_NO_MEM if wait was set to false and no space was available.
 */
uint32_t nrf_fifo_enq(nrf_fifo_t * p_fifo, void * p_ctx, bool wait);

/**
 * @brief Function for dequeuing an element from the FIFO.
 *
 * @param[in, out] p_fifo The FIFO to dequeue elements from.
 * @param[out]     pp_ctx Pointer to where the dequeued element should be stored.
 * @param[in]      wait   If true, this function will block until the FIFO has elements for dequeuing.
 *                        Any errors returned by this function will be propagated to the caller.
 *
 * @retval NRF_SUCCESS if the element was queued.
 * @retval NRF_ERROR_NO_MEM if wait was set to false and no space was available.
 */
uint32_t nrf_fifo_deq(nrf_fifo_t * p_fifo, void ** pp_ctx, bool wait);

/**
 * @brief Function for checking if the FIFO is empty.
 *
 * @param[in] p_fifo The FIFO to check.
 * @return true if empty, false if not.
 */
bool nrf_fifo_empty(nrf_fifo_t * p_fifo);

/**
 * @brief Function for checking if the FIFO is full.
 *
 * @param[in] p_fifo The FIFO to check.
 * @return true if full, false if not.
 */
bool nrf_fifo_full(nrf_fifo_t * p_fifo);

/**@} */

#ifdef __cplusplus
}
#endif

#endif // NRF_FIFO_H__
