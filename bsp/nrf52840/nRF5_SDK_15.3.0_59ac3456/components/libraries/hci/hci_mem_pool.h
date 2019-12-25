/**
 * Copyright (c) 2013 - 2019, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup hci_mem_pool Memory pool
 * @{
 * @ingroup app_common
 *
 * @brief Memory pool implementation
 *
 * Memory pool implementation, based on circular buffer data structure, which supports asynchronous
 * processing of RX data. The current default implementation supports 1 TX buffer and 4 RX buffers.
 * The memory managed by the pool is allocated from static storage instead of heap. The internal
 * design of the circular buffer implementing the RX memory layout is illustrated in the picture
 * below.
 *
 * @image html memory_pool.svg "Circular buffer design"
 *
 * The expected call order for the RX APIs is as follows:
 * - hci_mem_pool_rx_produce
 * - hci_mem_pool_rx_data_size_set
 * - hci_mem_pool_rx_extract
 * - hci_mem_pool_rx_consume
 *
 * @warning If the above mentioned expected call order is violated the end result can be undefined.
 *
 * \par Component specific configuration options
 *
 * The following compile time configuration options are available to suit various implementations:
 * - TX_BUF_SIZE TX buffer size in bytes.
 * - RX_BUF_SIZE RX buffer size in bytes.
 * - RX_BUF_QUEUE_SIZE RX buffer element size.
 */

#ifndef HCI_MEM_POOL_H__
#define HCI_MEM_POOL_H__

#include <stdint.h>
#include "nrf_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Function for opening the module.
 *
 * @retval NRF_SUCCESS          Operation success.
 */
uint32_t hci_mem_pool_open(void);

/**@brief Function for closing the module.
 *
 * @retval NRF_SUCCESS          Operation success.
 */
uint32_t hci_mem_pool_close(void);

/**@brief Function for allocating requested amount of TX memory.
 *
 * @param[out] pp_buffer        Pointer to the allocated memory.
 *
 * @retval NRF_SUCCESS          Operation success. Memory was allocated.
 * @retval NRF_ERROR_NO_MEM     Operation failure. No memory available for allocation.
 * @retval NRF_ERROR_NULL       Operation failure. NULL pointer supplied.
 */
uint32_t hci_mem_pool_tx_alloc(void ** pp_buffer);

/**@brief Function for freeing previously allocated TX memory.
 *
 * @note Memory management follows the FIFO principle meaning that free() order must match the
 *       alloc(...) order, which is the reason for omitting exact memory block identifier as an
 *       input parameter.
 *
 * @retval NRF_SUCCESS          Operation success. Memory was freed.
 */
uint32_t hci_mem_pool_tx_free(void);

/**@brief Function for producing a free RX memory block for usage.
 *
 * @note Upon produce request amount being 0, NRF_SUCCESS is returned.
 *
 * @param[in]  length           Amount, in bytes, of free memory to be produced.
 * @param[out] pp_buffer        Pointer to the allocated memory.
 *
 * @retval NRF_SUCCESS          Operation success. Free RX memory block produced.
 * @retval NRF_ERROR_NO_MEM     Operation failure. No suitable memory available for allocation.
 * @retval NRF_ERROR_DATA_SIZE  Operation failure. Request size exceeds limit.
 * @retval NRF_ERROR_NULL       Operation failure. NULL pointer supplied.
 */
uint32_t hci_mem_pool_rx_produce(uint32_t length, void ** pp_buffer);

/**@brief Function for setting the length of the last produced RX memory block.
 *
 * @warning If call to this API is omitted the end result is that the following call to
 *          mem_pool_rx_extract will return incorrect data in the p_length output parameter.
 *
 * @param[in]  length           Amount, in bytes, of actual memory used.
 *
 * @retval NRF_SUCCESS          Operation success. Length was set.
 */
uint32_t hci_mem_pool_rx_data_size_set(uint32_t length);

/**@brief Function for extracting a packet, which has been filled with read data, for further
 * processing.
 *
 * @param[out] pp_buffer        Pointer to the packet data.
 * @param[out] p_length         Length of packet data in bytes.
 *
 * @retval NRF_SUCCESS          Operation success.
 * @retval NRF_ERROR_NO_MEM     Operation failure. No packet available to extract.
 * @retval NRF_ERROR_NULL       Operation failure. NULL pointer supplied.
 */
uint32_t hci_mem_pool_rx_extract(uint8_t ** pp_buffer, uint32_t * p_length);

/**@brief Function for freeing previously extracted packet, which has been filled with read data.
 *
 * @param[in] p_buffer             Pointer to consumed buffer.
 *
 * @retval NRF_SUCCESS             Operation success.
 * @retval NRF_ERROR_NO_MEM        Operation failure. No packet available to free.
 * @retval NRF_ERROR_INVALID_ADDR  Operation failure. Not a valid pointer.
 */
uint32_t hci_mem_pool_rx_consume(uint8_t * p_buffer);


#ifdef __cplusplus
}
#endif

#endif // HCI_MEM_POOL_H__

/** @} */
