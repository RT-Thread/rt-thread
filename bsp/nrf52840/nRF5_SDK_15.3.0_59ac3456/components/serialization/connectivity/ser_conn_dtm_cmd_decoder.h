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
/**
 * @addtogroup ser_conn Connectivity application code
 * @ingroup ble_sdk_lib_serialization
 */

/** @file
 *
 * @defgroup ser_dtm_decoder DTM Command Decoder in the Connectivity Chip
 * @{
 * @ingroup ser_conn
 *
 * @brief   Decoder for serialized DTM commands from the Application Chip.
 *
 * @details This file contains declaration of common function used for DTM commands decoding and
 *          sending responses back to the Application Chip after a DTM command is processed.
 */

#ifndef SER_CONN_DTM_CMD_DECODER_H__
#define SER_CONN_DTM_CMD_DECODER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief A function for processing the encoded DTM commands from the Application Chip.
 *
 * @details     The function decodes encoded DTM commands and calls the appropriate DTM API.
 *              Then creates a DTM Command Response packet with the return value from the
 *              DTM API encoded in it and sends it to the Application Chip.
 *
 * @param[in]   p_command      The encoded command.
 * @param[in]   command_len    Length of the encoded command.
 *
 * @retval      NRF_SUCCESS    If the decoding of the command was successful, the DTM API
 *                             was called, and the command response was sent to peer, otherwise an
 *                             error code.
 */
uint32_t ser_conn_dtm_command_process(uint8_t * p_command, uint16_t command_len);


/**@brief A function for checking if the Connectivity Chip is ready to enter the DTM mode.
 *
 * @details     The function checks if the Connectivity Chip is ready to enter into DTM mode.
 *              If it is ready, then it disables the SoftDevice, closes HAL Transport Layer,
 *              and starts DTM mode.
 */
void ser_conn_is_ready_to_enter_dtm(void);


#ifdef __cplusplus
}
#endif

#endif /* SER_CONN_DTM_CMD_DECODER_H__ */

/** @} */

