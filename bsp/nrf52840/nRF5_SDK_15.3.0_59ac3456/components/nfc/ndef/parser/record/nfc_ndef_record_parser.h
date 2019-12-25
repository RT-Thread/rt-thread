/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#ifndef NFC_NDEF_RECORD_PARSER_H__
#define NFC_NDEF_RECORD_PARSER_H__

#include <stdint.h>
#include "sdk_errors.h"
#include "nfc_ndef_record.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@file
 *
 * @defgroup nfc_ndef_record_parser Parser for NDEF records
 * @{
 * @ingroup  nfc_ndef_parser
 *
 * @brief    Parser for NFC NDEF records.
 *
 */


/**
 * @brief Function for parsing NDEF records.
 *
 * This parsing implementation uses the binary payload descriptor (@ref nfc_ndef_bin_payload_desc_t) to describe the payload for the record.
 *
 * @param[out]    p_bin_pay_desc     Pointer to the binary payload descriptor that will be filled and referenced by the record descriptor.
 * @param[out]    p_rec_desc         Pointer to the record descriptor that will be filled with parsed data.
 * @param[out]    p_record_location  Pointer to the record location.
 * @param[in]     p_nfc_data         Pointer to the raw data to be parsed.
 * @param[in,out] p_nfc_data_len     As input: size of the NFC data in the @p p_nfc_data buffer. As output: size of the parsed record.
 *
 * @retval NRF_SUCCESS               If the function completed successfully.
 * @retval NRF_ERROR_INVALID_LENGTH  If the expected record length is bigger than the provided input data amount.
 */
ret_code_t ndef_record_parser(nfc_ndef_bin_payload_desc_t * p_bin_pay_desc,
                              nfc_ndef_record_desc_t      * p_rec_desc,
                              nfc_ndef_record_location_t  * p_record_location,
                              uint8_t const               * p_nfc_data,
                              uint32_t                    * p_nfc_data_len);

/**
 * @brief Function for printing the parsed contents of the NDEF record.
 *
 * @param[in] num        Sequence number of the record within the NDEF message.
 * @param[in] p_rec_desc Pointer to the descriptor of the record that should be printed.
 *
 */
void ndef_record_printout(uint32_t num, nfc_ndef_record_desc_t * const p_rec_desc);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif // NFC_NDEF_RECORD_PARSER_H__
