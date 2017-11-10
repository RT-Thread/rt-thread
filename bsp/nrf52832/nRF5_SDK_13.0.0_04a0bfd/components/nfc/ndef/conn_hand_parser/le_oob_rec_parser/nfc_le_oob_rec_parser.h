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
/** @file
 *
 * @defgroup nfc_le_oob_rec_parser LE OOB records parser
 * @{
 * @ingroup nfc_ble_pair_msg
 * @brief Functions for parsing and decoding LE OOB records.
 */

#ifndef __NFC_LE_OOB_REC_PARSER_H__
#define __NFC_LE_OOB_REC_PARSER_H__

#include "nfc_ndef_record.h"
#include "nfc_ble_oob_advdata_parser.h"
#include "nfc_ble_pair_common.h"

/**
 * @brief Function for parsing general record description as LE OOB record.
 *
 * This function checks if record description matches the LE OOB record pattern and extracts BLE
 * OOB Advertising data structure. It is required for the record description to use binary payload
 * descriptor.
 *
 * @param[in]     p_rec_desc                   Pointer to the record descriptor.
 * @param[in,out] p_nfc_ble_oob_pairing_data   Pointer to the structure that will be used to hold
 *                                             parsed data.
 *
 * @retval NRF_SUCCESS              If the function completed successfully.
 * @retval NRF_ERROR_INVALID_DATA   If the NDEF record type or TNF is incorrect.
 * @retval NRF_ERROR_NOT_SUPPORTED  If the payload descriptor is not binary.
 * @retval Other                    An error code that might have been returned by
 *                                  @ref nfc_ble_oob_advdata_parse function.
 */
ret_code_t nfc_le_oob_rec_parse(nfc_ndef_record_desc_t     const * const p_rec_desc,
                                nfc_ble_oob_pairing_data_t       * const p_nfc_ble_oob_pairing_data);

#endif // __NFC_LE_OOB_REC_PARSER_H__

/** @} */
