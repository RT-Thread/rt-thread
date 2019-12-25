/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NFC_NDEF_URI_REC)

#include <string.h>
#include "nfc_uri_rec.h"
#include "nrf_error.h"

const uint8_t ndef_uri_record_type = 'U'; ///< URI Record type.

/**
 * @brief Function for constructing the payload for a URI record.
 *
 * This function encodes the payload according to the URI record definition. It implements an API
 * compatible with @ref p_payload_constructor_t.
 *
 * @param[in] p_input           Pointer to the description of the payload.
 * @param[out] p_buff           Pointer to payload destination. If NULL, function will
 *                              calculate the expected size of the URI record payload.
 *
 * @param[in,out] p_len         Size of available memory to write as input. Size of generated
 *                              payload as output.
 *
 * @retval NRF_SUCCESS          If the payload was encoded successfully.
 * @retval NRF_ERROR_NO_MEM     If the predicted payload size is bigger than the provided buffer space.
 */
ret_code_t nfc_uri_payload_constructor( uri_payload_desc_t * p_input,
                                        uint8_t * p_buff,
                                        uint32_t * p_len)
{
    if (p_buff != NULL)
    {
        /* Verify if there is enough available memory */
        if (p_input->uri_data_len >= *p_len)
        {
            return NRF_ERROR_NO_MEM;
        }

        /* Copy descriptor content into the buffer */
        *(p_buff++) = p_input->uri_id_code;
        memcpy(p_buff, p_input->p_uri_data, p_input->uri_data_len );
    }

    *p_len      = p_input->uri_data_len + 1;

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NFC_NDEF_URI_REC)
