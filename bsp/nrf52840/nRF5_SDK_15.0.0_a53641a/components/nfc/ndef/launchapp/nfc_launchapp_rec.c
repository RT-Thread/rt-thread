/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NFC_NDEF_LAUNCHAPP_REC)

#include "nfc_launchapp_rec.h"
#include <string.h>
#include "nrf_error.h"
#include "app_util.h"
#include "nfc_ndef_record.h"

/* Record Payload Type for NFC NDEF Android Application Record */
const uint8_t ndef_android_launchapp_rec_type[] =
{
    'a', 'n', 'd', 'r', 'o', 'i', 'd', '.', 'c','o', 'm', ':', 'p', 'k', 'g'
};

/* Record Payload Type for NFC NDEF Windows LaunchApp record */
const uint8_t ndef_windows_launchapp_rec_type[] =
{
    'w', 'i', 'n', 'd', 'o', 'w', 's', '.', 'c', 'o', 'm', '/', 'L', 'a', 'u',
    'n', 'c', 'h', 'A', 'p', 'p'
};
/* Platform type used in Record Payload of NFC NDEF Windows LaunchApp record */
const uint8_t ndef_windows_launchapp_plat_type[] =
{
    'W', 'i', 'n', 'd', 'o', 'w', 's', 'P', 'h', 'o', 'n', 'e'
};

#define WIN_LAUNCHAPP_EMPTY_PARAMETER 0x20 ///< The empty parameter value for the Windows LaunchApp Record.

ret_code_t nfc_win_launchapp_payload_constructor(win_launchapp_payload_desc_t * p_input,
                                                 uint8_t                      * p_buff,
                                                 uint32_t                     * p_len)
{

    win_launchapp_payload_desc_t * launch_desc = (win_launchapp_payload_desc_t *) p_input;

    uint32_t temp_len = (uint32_t)launch_desc->platform_length + launch_desc->app_id_length + 7;

    if (p_buff != NULL)
    {
        if (temp_len > *p_len)
        {
            return NRF_ERROR_NO_MEM;
        }

        *p_buff++ = 0x00; // platform count: 1
        *p_buff++ = 0x01; // -||-

        *p_buff++ = launch_desc->platform_length;
        memcpy(p_buff, launch_desc->platform, launch_desc->platform_length); // platform
        p_buff += launch_desc->platform_length;


        *p_buff++ = launch_desc->app_id_length;
        memcpy(p_buff, launch_desc->app_id, launch_desc->app_id_length);
        p_buff += launch_desc->app_id_length;

        *p_buff++ = 0x00; // parameters length 1B
        *p_buff++ = 0x01; // -||-
        *p_buff++ = WIN_LAUNCHAPP_EMPTY_PARAMETER; // empty parameter
    }

    *p_len = temp_len;

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(NFC_NDEF_LAUNCHAPP_REC)
