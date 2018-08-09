/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
 * @defgroup iot_context_manager Context Manager
 * @{
 * @ingroup iot_sdk_common
 * @brief Manages context identifiers and prefixes related to the identifiers.
 *
 * @details This module allows to handle context information throughout the IoT application.
 *          The module is used in the compression and decompression procedures of IPv6 addresses.
 *          It allows more efficient communication between two nodes using global addresses.
 *          The Context Manager contains tables of context, which can be accessed through API functions.
 *          The table is maintained by the IPv6 stack while is referenced by 6LoWPAN module to be able to
 *          compress and decompress packets.
 *
 *          You can configure the module by changing the @c sdk_config.h configuration file.
 */

#ifndef IOT_CONTEXT_MANAGER__
#define IOT_CONTEXT_MANAGER__

#include <stdint.h>
#include <stdbool.h>
#include "iot_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Function for initializing the module.
 *
 * @retval NRF_SUCCESS If the module was successfully initialized. Otherwise, an error code that indicates the reason for the failure is returned.
 */
uint32_t iot_context_manager_init(void);


/**@brief Function for allocating the table for the specific interface.
 *
 * @param[in] p_interface Pointer to the IoT interface.
 *
 * @retval NRF_SUCCESS If the table was successfully allocated. Otherwise, an error code that indicates the reason for the failure is returned.
 */
uint32_t iot_context_manager_table_alloc(const iot_interface_t * p_interface);


/**@brief Function for freeing the table for the specific interface.
 *
 * @param[in] p_interface Pointer to the IoT interface.
 *
 * @retval NRF_SUCCESS If the table was successfully freed. Otherwise, an error code that indicates the reason for the failure is returned.
 */
uint32_t iot_context_manager_table_free(const iot_interface_t * p_interface);


/**@brief Function for updating the context table.
 *
 * Update requests are treated as follows:
 * - If the context identifier already exists in the context table, the context
 *   is updated.
 * - If the context identifier does not exist yet, a new entry is generated. If
 *   no memory is available, NRF_ERROR_NO_MEMORY is returned.
 *
 * The compression flag indicates if a context can be used for compression.
 * The context table can hold up to 16 context's information.
 *
 * @param[in] p_interface Pointer to the IoT interface.
 * @param[in] p_context   Pointer to the context entry that shall be modified or added.
 *
 * @retval NRF_SUCCESS If the table was successfully updated. Otherwise, an error code that indicates the reason for the failure is returned.
 */
uint32_t iot_context_manager_update(const iot_interface_t * p_interface, iot_context_t * p_context);


/**@brief Function for removing context from the context table.
 *
 * @param[in] p_interface Pointer to the IoT interface.
 * @param[in] p_context   Pointer to the context entry, retrieved from @ref iot_context_manager_get_by_addr or
 *                        @ref iot_context_manager_get_by_cid.
 *
 * @retval NRF_SUCCESS If the context was successfully removed. Otherwise, an error code that indicates the reason for the failure is returned.
 */
uint32_t iot_context_manager_remove(const iot_interface_t * p_interface, iot_context_t * p_context);


/**@brief Function for searching the proper entry in the context table by IPv6 address.
 *        Only contexts with compression flag set to true, may be returned.
 *
 * @param[in] p_interface  Pointer to the IoT interface.
 * @param[in] p_addr       Pointer to IPv6 address to be compared with records in the context table.
 * @param[out] pp_context  Pointer to the context in the context table.
 *
 * @retval NRF_SUCCESS If the procedure succeeded. Otherwise, an error code that indicates the reason for the failure is returned.
 */
uint32_t iot_context_manager_get_by_addr(const iot_interface_t * p_interface,
                                         const ipv6_addr_t     * p_addr,
                                         iot_context_t        ** pp_context);


/**@brief Function for searching the proper entry in the context table by context identifier.
 *
 * @param[in]  p_interface Pointer to the IoT interface.
 * @param[in]  context_id  Context identifier to be compared with records in the context table.
 * @param[out] pp_context  Pointer to the context in the context table.
 *
 * @retval NRF_SUCCESS If the procedure succeeded. Otherwise, an error code that indicates the reason for the failure is returned.
 */
uint32_t iot_context_manager_get_by_cid(const iot_interface_t * p_interface,
                                        uint8_t                 context_id,
                                        iot_context_t        ** pp_context);

#ifdef __cplusplus
}
#endif

#endif // IOT_CONTEXT_MANAGER__

/**@} */
