/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#ifndef NFC_NDEF_MSG_PARSER_H__
#define NFC_NDEF_MSG_PARSER_H__

/**@file
 *
 * @defgroup nfc_ndef_parser NDEF message parser
 * @{
 * @ingroup  nfc_modules
 *
 * @brief    Parser for NFC NDEF messages and records.
 *
 * @defgroup nfc_ndef_msg_parser Parser for NDEF messages
 * @{
 * @ingroup  nfc_ndef_parser
 *
 * @brief    Parser for NFC NDEF messages.
 *
 */

#include <stdint.h>
#include "nfc_ndef_msg_parser_local.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Macro for calculating the memory size required for holding the
 * description of a message that consists of a certain number of NDEF records.
 *
 * @param[in] max_count_of_records Maximum number of records to hold.
 */
#define NFC_NDEF_PARSER_REQIRED_MEMO_SIZE_CALC(max_count_of_records)   \
    ((uint32_t)(max_count_of_records) <= 1) ?                          \
    (sizeof(parsed_ndef_msg_1_t) * (uint32_t)(max_count_of_records)) : \
    (sizeof(parsed_ndef_msg_1_t) + ((NFC_PARSER_M_DELTA) *((uint32_t)(max_count_of_records) - 1)))

/**
 * @brief   Function for parsing NFC NDEF messages.
 *
 * This function parses NDEF messages using NDEF binary record descriptors.
 *
 * @param[out] p_result_buf        Pointer to the buffer that will be used to hold
 *                                 the NDEF message descriptor. After parsing is completed successfully, the first address
 *                                 in the buffer is filled by the NDEF message descriptor
 *                                 (@ref nfc_ndef_msg_desc_t), which provides a full description of
 *                                 the parsed NDEF message.
 * @param[in,out] p_result_buf_len As input: size of the buffer specified by @p p_result_buf.
 *                                 As output: size of the reserved (used) part of the buffer specified by
 *                                 @p p_result_buf.
 * @param[in]    p_nfc_data        Pointer to the data to be parsed.
 * @param[in,out] p_nfc_data_len   As input: size of the NFC data in the @p p_nfc_data buffer. As output: size of the parsed message.
 *
 * @retval NRF_SUCCESS               If the function completed successfully.
 * @retval NRF_ERROR_NO_MEM          If the provided buffer is too small to hold a one-record message or
 *                                   the buffer is too small to hold the actual result of the parsing.
 * @retval NRF_ERROR_INVALID_LENGTH  If the expected message length is bigger than the amount of the provided input data.
 * @retval NRF_ERROR_INVALID_DATA    If the message is not a valid NDEF message.
 */
ret_code_t ndef_msg_parser(uint8_t  * const p_result_buf,
                           uint32_t * const p_result_buf_len,
                           uint8_t  * const p_nfc_data,
                           uint32_t * const p_nfc_data_len);

/**
 * @brief Function for printing the parsed contents of an NDEF message.
 *
 * @param[in] p_msg_desc Pointer to the descriptor of the message that should be printed.
 */
void ndef_msg_printout(nfc_ndef_msg_desc_t * const p_msg_desc);

/**
 * @}
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif // NFC_NDEF_MSG_PARSER_H__


