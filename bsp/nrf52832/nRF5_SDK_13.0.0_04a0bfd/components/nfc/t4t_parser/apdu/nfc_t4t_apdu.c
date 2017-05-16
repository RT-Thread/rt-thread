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
#include "sdk_config.h"
#if NFC_T4T_APDU_ENABLED

#include "nfc_t4t_apdu.h"
#include "sdk_macros.h"
#include "nordic_common.h"
#include "app_util.h"

#define NRF_LOG_MODULE_NAME "NFC_T4T_APDU"
#if NFC_T4T_APDU_LOG_ENABLED
#define NRF_LOG_LEVEL       NFC_T4T_APDU_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NFC_T4T_APDU_LOG_COLOR
#else // NFC_T4T_APDU_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // NFC_T4T_APDU_LOG_ENABLED
#include "nrf_log.h"

/**
 * @brief Field sizes that can be present in CAPDU.
 */
#define CLASS_TYPE_SIZE       1U
#define INSTRUCTION_TYPE_SIZE 1U
#define PARAMETER_SIZE        2U
#define LC_SHORT_FORMAT_SIZE  1U
#define LC_LONG_FORMAT_SIZE   3U
#define LE_SHORT_FORMAT_SIZE  1U
#define LE_LONG_FORMAT_SIZE   2U

/**
 * @brief Values used to encode Lc field in CAPDU.
 */
#define LC_LONG_FORMAT_TOKEN  0x00
#define LC_LONG_FORMAT_THR    0xFF

/**
 * @brief Values used to encode Le field in CAPDU.
 */
#define LE_FIELD_ABSENT       0U
#define LE_LONG_FORMAT_THR    0x0100
#define LE_ENCODED_VAL_256    0x00


#define STATUS_SIZE           2U ///< Size of Status field contained in RAPDU.

/**
 * @brief Function for calculating size of CAPDU.
 */
__STATIC_INLINE uint16_t nfc_t4t_comm_apdu_size_calc(nfc_t4t_comm_apdu_t const * const p_cmd_apdu)
{
    uint16_t res = CLASS_TYPE_SIZE + INSTRUCTION_TYPE_SIZE + PARAMETER_SIZE;
    if (p_cmd_apdu->data.p_buff != NULL)
    {
        if (p_cmd_apdu->data.len > LC_LONG_FORMAT_THR)
        {
            res += LC_LONG_FORMAT_SIZE;
        }
        else
        {
            res += LC_SHORT_FORMAT_SIZE;
        }
    }
    res += p_cmd_apdu->data.len;
    if (p_cmd_apdu->resp_len != LE_FIELD_ABSENT)
    {
        if (p_cmd_apdu->resp_len > LE_LONG_FORMAT_THR)
        {
            res += LE_LONG_FORMAT_SIZE;
        }
        else
        {
            res += LE_SHORT_FORMAT_SIZE;
        }
    }
    return res;
}


/**
 * @brief Function for validating arguments used by CAPDU encoding procedure.
 */
__STATIC_INLINE ret_code_t nfc_t4t_comm_apdu_args_validate(nfc_t4t_comm_apdu_t const * const p_cmd_apdu,
                                                           uint8_t                         * p_raw_data,
                                                           uint16_t                  * const p_len)
{
    if((p_cmd_apdu == NULL) || (p_raw_data == NULL) || (p_len == NULL))
    {
        return NRF_ERROR_NULL;
    }

    if ((p_cmd_apdu->data.p_buff != NULL) && (p_cmd_apdu->data.len == 0))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    return NRF_SUCCESS;
}


ret_code_t nfc_t4t_comm_apdu_encode(nfc_t4t_comm_apdu_t const * const p_cmd_apdu,
                                    uint8_t                         * p_raw_data,
                                    uint16_t                  * const p_len)
{
    // Validate passed arguments.
    ret_code_t err_code = nfc_t4t_comm_apdu_args_validate(p_cmd_apdu, p_raw_data, p_len);
    VERIFY_SUCCESS(err_code);

    // Check if there is enough memory in the provided buffer to store described CAPDU.
    uint16_t comm_apdu_len = nfc_t4t_comm_apdu_size_calc(p_cmd_apdu);
    if (comm_apdu_len > *p_len)
    {
        return NRF_ERROR_NO_MEM;
    }
    *p_len = comm_apdu_len;

    // Start to encode described CAPDU in the buffer.
    *p_raw_data++ = p_cmd_apdu->class_byte;
    *p_raw_data++ = p_cmd_apdu->instruction;
    *p_raw_data++ = MSB_16(p_cmd_apdu->parameter);
    *p_raw_data++ = LSB_16(p_cmd_apdu->parameter);

    // Check if optional data field should be included.
    if (p_cmd_apdu->data.p_buff != NULL)
    {
        if (p_cmd_apdu->data.len > LC_LONG_FORMAT_THR)   // Use long data length encoding.
        {
            *p_raw_data++ = LC_LONG_FORMAT_TOKEN;
            *p_raw_data++ = MSB_16(p_cmd_apdu->data.len);
            *p_raw_data++ = LSB_16(p_cmd_apdu->data.len);
        }
        else                                              // Use short data length encoding.
        {
            *p_raw_data++ = LSB_16(p_cmd_apdu->data.len);
        }
        memcpy(p_raw_data, p_cmd_apdu->data.p_buff, p_cmd_apdu->data.len);
        p_raw_data += p_cmd_apdu->data.len;
    }

    // Check if optional response length field present (Le) should be included.
    if (p_cmd_apdu->resp_len != LE_FIELD_ABSENT)
    {
        if (p_cmd_apdu->resp_len > LE_LONG_FORMAT_THR) // Use long response length encoding.
        {
            *p_raw_data++ = MSB_16(p_cmd_apdu->resp_len);
            *p_raw_data++ = LSB_16(p_cmd_apdu->resp_len);
        }
        else                                              // Use short response length encoding.
        {
            if (p_cmd_apdu->resp_len == LE_LONG_FORMAT_THR)
            {
                *p_raw_data++ = LE_ENCODED_VAL_256;
            }
            else
            {
                *p_raw_data++ = LSB_16(p_cmd_apdu->resp_len);
            }
        }
    }

    return NRF_SUCCESS;
}


/**
 * @brief Function for validating arguments used by RAPDU decoding procedure.
 */
__STATIC_INLINE ret_code_t nfc_t4t_resp_apdu_args_validate(nfc_t4t_resp_apdu_t const * const p_resp_apdu,
                                                           uint8_t             const * const p_raw_data,
                                                           uint16_t                          len)
{
    if ((p_resp_apdu == NULL) || (p_raw_data == NULL))
    {
        return NRF_ERROR_NULL;
    }

    if (len < STATUS_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    return NRF_SUCCESS;
}


ret_code_t nfc_t4t_resp_apdu_decode(nfc_t4t_resp_apdu_t * const p_resp_apdu,
                                    uint8_t       const * const p_raw_data,
                                    uint16_t                    len)
{
    // Validate passed arguments.
    ret_code_t err_code = nfc_t4t_resp_apdu_args_validate(p_resp_apdu, p_raw_data, len);
    VERIFY_SUCCESS(err_code);

    nfc_t4t_resp_apdu_clear(p_resp_apdu);
    if (len != STATUS_SIZE) // Optional data field is present in RAPDU.
    {
        p_resp_apdu->data.len    = len - STATUS_SIZE;
        p_resp_apdu->data.p_buff = (uint8_t *) p_raw_data;
    }
    p_resp_apdu->status = uint16_big_decode(p_raw_data + p_resp_apdu->data.len);

    return NRF_SUCCESS;
}


void nfc_t4t_resp_apdu_printout(nfc_t4t_resp_apdu_t * p_resp_apdu)
{
    NRF_LOG_INFO("R-APDU status: %4X \r\n", p_resp_apdu->status);
    if (p_resp_apdu->data.p_buff != NULL)
    {
        NRF_LOG_INFO("R-APDU data: \r\n");
        NRF_LOG_HEXDUMP_INFO(p_resp_apdu->data.p_buff, p_resp_apdu->data.len);
    }
    else
    {
        NRF_LOG_INFO("R-APDU no data field present.\r\n");
    }
}


#endif // NFC_T4T_APDU_ENABLED

