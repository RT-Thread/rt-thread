/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
 * @defgroup background_dfu_transport background_dfu_state.h
 * @{
 * @ingroup background_dfu
 * @brief Background DFU transport API.
 *
 */

#ifndef BACKGROUND_DFU_TRANSPORT_H_
#define BACKGROUND_DFU_TRANSPORT_H_

#include "background_dfu_state.h"

/**@brief Create and send DFU block request with missing blocks.
 *
 * This function is used in multicast DFU.
 *
 * @param[in] p_dfu_ctx A pointer to the background DFU context.
 * @param[in] p_req_bmp A pointer to the bitmap structure that shall be sent.
 */
void background_dfu_transport_block_request_send(background_dfu_context_t        * p_dfu_ctx,
                                                 background_dfu_request_bitmap_t * p_req_bmp);

/**@brief Send background DFU request, based on DFU state.
 *
 * @param[in] p_dfu_ctx A pointer to the background DFU context.
 */
void background_dfu_transport_send_request(background_dfu_context_t * p_dfu_ctx);

/**@brief Update background DFU transport state.
 *
 * @param[in] p_dfu_ctx A pointer to the background DFU context.
 */
void background_dfu_transport_state_update(background_dfu_context_t * p_dfu_ctx);

/**@brief Get random value.
 *
 * @returns A random value of uint32_t type.
 */
uint32_t background_dfu_random(void);

/** @brief Handle DFU error.
 *
 *  Notify transport about DFU error.
 */
void background_dfu_handle_error(void);

#endif /* BACKGROUND_DFU_COAP_H_ */

/** @} */
