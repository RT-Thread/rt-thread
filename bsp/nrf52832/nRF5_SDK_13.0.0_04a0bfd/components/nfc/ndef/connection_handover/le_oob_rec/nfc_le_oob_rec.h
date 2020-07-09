/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#ifndef NFC_LE_OOB_REC_H__
#define NFC_LE_OOB_REC_H__

/**@file
 *
 * @defgroup nfc_le_oob_rec LE OOB records
 * @{
 * @ingroup  nfc_ble_pair_msg
 *
 * @brief    Generation of NFC NDEF LE OOB records for NDEF messages.
 *
 */

#include <stdint.h>
#include "nfc_ndef_record.h"
#include "nfc_ble_oob_advdata.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Function for generating a description of an NFC NDEF Bluetooth Carrier Configuration LE Record.
 *
 * This function declares and initializes a static instance of an NFC NDEF record description
 * for a Bluetooth Carrier Configuration LE record.
 *
 * @note The record payload data (@p p_ble_advdata) should be declared as static. If it is
 *       declared as automatic, the NDEF message encoding (see @ref nfc_ble_simplified_le_oob_msg_encode)
 *       must be done in the same variable scope.
 *
 * @param[in]  rec_payload_id       NDEF record header Payload ID field (Limited to one byte).
 *                                  If 0, no ID is present in the record description.
 * @param[in]  p_ble_advdata        Pointer to the encoded BLE advertising data structure. This
 *                                  data is used to create the record payload.
 *
 * @return Pointer to the description of the record.
 */
nfc_ndef_record_desc_t * nfc_le_oob_rec_declare(uint8_t                        rec_payload_id,
                                                ble_advdata_t    const * const p_ble_advdata);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NFC_LE_OOB_REC_H__
