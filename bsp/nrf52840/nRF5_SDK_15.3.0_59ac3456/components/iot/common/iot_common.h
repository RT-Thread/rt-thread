/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
/** @file iot_common.h
 *
 * @defgroup iot_common Common utils
 * @ingroup iot_sdk_common
 * @{
 * @brief Common IoT macros that are needed by IoT modules.
 *
 * @details This module abstracts common macros related to IoT. These macros can be used by all IoT modules.
 */

#ifndef IOT_COMMON_H__
#define IOT_COMMON_H__

#include <stdint.h>
#include <stdbool.h>
#include "iot_defines.h"
#include "iot_errors.h"
#include "sdk_os.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Context identifiers used in stateful compression. */
typedef struct
{
    uint8_t src_cntxt_id;                                                                           /**< Source context identifier (if any). IPV6_CONTEXT_IDENTIFIER_NONE by default. IP Stack can set this on the interface if needed. */
    uint8_t dest_cntxt_id;                                                                          /**< Destination context identifier (if any). IPV6_CONTEXT_IDENTIFIER_NONE by default. IP Stack can set this on the interface if needed. */
} iot_context_id_t;

/**@brief Context structure used for efficient compression and decompression. */
typedef struct
{
    uint8_t      context_id;                                                                        /**< Context identifier (CID) number. */
    uint8_t      prefix_len;                                                                        /**< Length of prefix for CID. */
    ipv6_addr_t  prefix;                                                                            /**< Prefix for CID. */
    bool         compression_flag;                                                                  /**< Indicates if the context can be used for compression. */
} iot_context_t;

/**@brief Encapsulates all information of the 6LoWPAN interface. */
typedef struct
{
    eui64_t            local_addr;                                                                  /**< Local EUI-64 address. */
    eui64_t            peer_addr;                                                                   /**< Peer EUI-64 address. */
    iot_context_id_t   tx_contexts;                                                                 /**< TX contexts can be used for effective compression. */
    void             * p_upper_stack;                                                               /**< Block to upper stack. */
    void             * p_transport;                                                                 /**< Transport reference. */
} iot_interface_t;

#ifdef __cplusplus
}
#endif

#endif //IOT_COMMON_H__

/**@} */
