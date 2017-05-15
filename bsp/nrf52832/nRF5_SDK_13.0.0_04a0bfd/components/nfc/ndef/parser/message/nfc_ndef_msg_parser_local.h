/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef NFC_NDEF_MSG_PARSER_LOCAL_H__
#define NFC_NDEF_MSG_PARSER_LOCAL_H__

/**@file
 *
 * @defgroup nfc_ndef_msg_parser_local NDEF message parser (internal)
 * @{
 * @ingroup  nfc_ndef_msg_parser
 *
 * @brief    Internal part of the parser for NFC NDEF messages.
 *
 */

#include <stdint.h>
#include "nfc_ndef_msg.h"
#include "nfc_ndef_record_parser.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Type for holding descriptors that are used by the NDEF parser.
 */
typedef struct
{
    nfc_ndef_msg_desc_t         * p_msg_desc;     ///< Pointer to the message descriptor.
    nfc_ndef_bin_payload_desc_t * p_bin_pay_desc; ///< Pointer to the array of binary payload descriptors.
    nfc_ndef_record_desc_t      * p_rec_desc;     ///< Pointer to the array of record descriptors.
}  nfc_ndef_parser_memo_desc_t;

/**
 * @brief Memory allocated for a one-record message.
 */
typedef struct
{
    nfc_ndef_msg_desc_t         msg_desc;
    nfc_ndef_record_desc_t    * p_record_desc_array[1];
    nfc_ndef_bin_payload_desc_t bin_pay_desc[1];
    nfc_ndef_record_desc_t      rec_desc[1];
} parsed_ndef_msg_1_t;

/**
 * @brief Memory allocated for a two-record message.
 */
typedef struct
{
    nfc_ndef_msg_desc_t         msg_desc;
    nfc_ndef_record_desc_t    * p_record_desc_array[2];
    nfc_ndef_bin_payload_desc_t bin_pay_desc[2];
    nfc_ndef_record_desc_t      rec_desc[2];
} parsed_ndef_msg_2_t;

/**
 * @brief Amount of memory that is required per record in addition to the memory allocated for the message descriptor.
 */
#define NFC_PARSER_M_DELTA (sizeof(parsed_ndef_msg_2_t) - sizeof(parsed_ndef_msg_1_t))


/**
 * @brief Function for resolving data instances in the provided buffer according
 * to requirements of the function @ref internal_ndef_msg_parser.
 *
 * This internal function distributes the provided memory between certain data instances that are required
 * by @ref internal_ndef_msg_parser.
 *
 * This function should not be used directly.
 *
 * @param[in] p_result_buf         Pointer to the buffer that will be used to allocate
 *                                 data instances.
 * @param[in,out] p_result_buf_len As input: size of the buffer specified by @p p_result_buf.
 *                                 As output: size of the reserved (used) part of the buffer specified by
 *                                 @p p_result_buf.
 * @param[out] p_parser_memo_desc  Pointer to the structure for holding descriptors of the allocated data
 *                                 instances.
 *
 * @retval NRF_SUCCESS             If the function completed successfully.
 * @retval NRF_ERROR_NO_MEM        If the provided buffer is too small to hold a one-record message.
 */
ret_code_t ndef_parser_memo_resolve(uint8_t                     * const p_result_buf,
                                    uint32_t                    * const p_result_buf_len,
                                    nfc_ndef_parser_memo_desc_t * const p_parser_memo_desc);


/**
 * @brief Function for parsing NFC NDEF messages.
 *
 * This internal function parses NDEF messages into certain data instances.
 *
 * This function should not be used directly.
 *
 * @param[in,out] p_parser_memo_desc Pointer to the structure that holds descriptors of the allocated data
 *                                   instances for the parser. This structure contains the following fields: @n
 *                                   .p_msg_desc      Pointer to the message descriptor that will
 *                                                    be filled with parsed data. @n
 *                                   .p_bin_pay_desc  Pointer to the array of binary payload
 *                                                    descriptors that will be filled with parsed
 *                                                    data. @n
 *                                   .p_rec_desc      Pointer to the array of record descriptors
 *                                                    that will be filled with parsed data. @n
 *                                   The arrays specified by @p .p_bin_pay_desc and @p .p_rec_desc must not
 *                                   contain more elements than the  message descriptor
 *                                   specified by \p .p_msg_desc can hold.
 *
 * @param[in]     p_nfc_data      Pointer to the data to be parsed.
 * @param[in,out] p_nfc_data_len  As input: size of the NFC data in the @p p_nfc_data buffer.
 *                                As output: size of the parsed message.
 *
 * @retval NRF_SUCCESS               If the function completed successfully.
 * @retval NRF_ERROR_INVALID_LENGTH  If the expected message length is bigger than the amount of provided input data.
 * @retval NRF_ERROR_INVALID_DATA    If the message is not a valid NDEF message.
 * @retval NRF_ERROR_NO_MEM          If the provided memory resources are too small to hold the parsing result.
 */
ret_code_t internal_ndef_msg_parser(nfc_ndef_parser_memo_desc_t * const p_parser_memo_desc,
                                    uint8_t                     const * p_nfc_data,
                                    uint32_t                    * const p_nfc_data_len);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif // NFC_NDEF_MSG_PARSER_LOCAL_H__
