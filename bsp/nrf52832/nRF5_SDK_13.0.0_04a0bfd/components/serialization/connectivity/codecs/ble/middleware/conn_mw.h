/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
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
#ifndef _CONN_MW_H
#define _CONN_MW_H

/**
 * @addtogroup sercon_mw_s132 Connectivity middleware codecs for S132 and S140 (connectivity side)
 * @{
 * @ingroup ser_codecs_mw
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Connectivity Middleware dispatcher function
 *
 * @details It handles decoding of the opcode from the RX buffer and based on the opcode, it searches
 *          for registered handler. Handler is called once it is found.
 *
 * @param[in]     p_rx_buf            Pointer to input buffer.
 * @param[in]     rx_buf_len          Size of @p p_rx_buf.
 * @param[out]    p_tx_buf            Pointer to output buffer.
 * @param[in,out] p_tx_buf_len        \c in: size of \p p_tx_buf buffer.
 *                                    \c out: Length of valid data in \p p_tx_buf.
 *
 * @retval NRF_SUCCESS                Handler success.
 * @retval NRF_ERROR_NULL             Handler failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Handler failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Handler failure. Invalid operation type.
 * @retval NRF_ERROR_NOT_SUPPORTED    Handler failure. Opcode not supported.
 */
uint32_t conn_mw_handler (uint8_t const * const p_rx_buf,
                          uint32_t              rx_buf_len,
                          uint8_t * const       p_tx_buf,
                          uint32_t      * const p_tx_buf_len);

#ifdef __cplusplus
}
#endif

/** @} */

#endif //_CONN_MW_H
