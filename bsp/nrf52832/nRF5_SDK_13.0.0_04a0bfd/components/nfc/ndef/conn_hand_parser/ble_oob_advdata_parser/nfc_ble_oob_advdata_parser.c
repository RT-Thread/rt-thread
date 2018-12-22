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
#include "nfc_ble_oob_advdata_parser.h"
#include "app_util.h"
#include "sdk_common.h"
#include "nrf_log.h"

#define BLE_GAP_AD_TYPE_LESC_CONFIRM_VALUE  0x22
#define BLE_GAP_AD_TYPE_LESC_RANDOM_VALUE   0x23

#define EARLY_TERMINATOR     0   /* Value of AD Structure Length field indicating an early
                                    termination of Advertising or Scan Response Data. */
#define FIELD_LEN_INC_VAL    1   /* Incorrect Value of AD Structure Length field. */

/** @brief Values used with @ref ad_type_counter_t. */
typedef enum
{
    AD_TYPE_NOT_PRESENT = 0,    /* Value indicating that AD type is not present. */
    AD_TYPE_OCCUR_THRES = 1     /* Maximal occurance number of any AD type within the buffer */
} ad_type_counter_values_t;

/**@brief Internal module structure indicating how many BLE AD fields of the same type are in the buffer. */
typedef struct
{
    uint8_t  name_type;                 /* Number of Short and Full Device Name AD Structures. */
    uint8_t  addr_type;                 /* Number of LE Bluetooth Device Address AD Structures. */
    uint8_t  appear_type;               /* Number of Appearance AD Structures. */
    uint8_t  flags_type;                /* Number of Flags AD Structures. */
    uint8_t  le_role_type;              /* Number of LE Role AD Structures. */
    uint8_t  tk_type;                   /* Number of Security Manager TK AD Structures. */
    uint8_t  sec_mgr_oob_flags_type;    /* Number of Security Manager OOB Flags AD Structures. */
    uint8_t  lesc_confirm_type;         /* Number of LESC OOB Confirmation Value AD Structures. */
    uint8_t  lesc_random_type;          /* Number of LESC OOB Random Value AD Structures. */
} ad_type_counter_t;

/**@brief Decodes and stores AD Data from Flags AD Structure. */
__STATIC_INLINE ret_code_t flags_decode(uint8_t              const * p_flags_data,
                                        uint8_t                      len,
                                        nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    if (len !=  AD_TYPE_FLAGS_DATA_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    p_nfc_ble_pairing_data->flags = *p_flags_data;

    return NRF_SUCCESS;
}

void nfc_oob_data_printout(nfc_ble_oob_pairing_data_t const * const p_pairing_data)
{
    NRF_LOG_RAW_INFO("\r\n");
    NRF_LOG_INFO("BLE Advertising data contents\r\n");
    NRF_LOG_INFO("Device name: %s\r\n", nrf_log_push((char *)p_pairing_data->device_name.p_name));
    NRF_LOG_INFO("Device Address: ");

    for (int i=0; i < BLE_GAP_ADDR_LEN; ++i)
    {
        NRF_LOG_RAW_INFO("%02X ", p_pairing_data->p_device_addr->addr[i]);
    }
    NRF_LOG_RAW_INFO("\r\n");

    if(p_pairing_data->p_tk_value != NULL)
    {
        NRF_LOG_INFO("Device Temporary Key: ");
        for(int i=0; i < BLE_GAP_SEC_KEY_LEN; ++i)
        {
            NRF_LOG_RAW_INFO("%02X ", p_pairing_data->p_tk_value->tk[i]);
        }
        NRF_LOG_RAW_INFO("\r\n");
    }
    else
    {
        NRF_LOG_INFO("Device Temporary Key not present.\r\n");
    }

    if(p_pairing_data->p_lesc_confirm_value != NULL && p_pairing_data->p_lesc_random_value)
    {
        NRF_LOG_INFO("LESC Confirmation Value: ");
        for(int i=0; i < BLE_GAP_SEC_KEY_LEN; ++i)
        {
            NRF_LOG_RAW_INFO("%02X ", p_pairing_data->p_lesc_confirm_value[i]);
        }
        NRF_LOG_RAW_INFO("\r\n");

        NRF_LOG_INFO("LESC Random Value: ");
        for(int i=0; i < BLE_GAP_SEC_KEY_LEN; ++i)
        {
            NRF_LOG_RAW_INFO("%02X ", p_pairing_data->p_lesc_random_value[i]);
        }
        NRF_LOG_RAW_INFO("\r\n");
    }
    else
    {
        NRF_LOG_INFO("LESC data not present.\r\n");
    }

    NRF_LOG_RAW_INFO("\r\n");
}

/**@brief Decodes and stores AD Data that is common for Short and Full Device Name AD Structures. */
static ret_code_t name_decode(uint8_t              const * p_name_data,
                              uint8_t                      len,
                              nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    uint8_t * p_name     = p_nfc_ble_pairing_data->device_name.p_name;
    uint8_t * p_name_len = &p_nfc_ble_pairing_data->device_name.len;

    VERIFY_PARAM_NOT_NULL(p_name);
    if (*p_name_len < len)
    {
        return NRF_ERROR_NO_MEM;
    }

    memcpy(p_name, p_name_data, len);
    *p_name_len = len;

    return NRF_SUCCESS;
}

/**@brief Decodes and stores AD Data from Short Device Name AD Structure. */
__STATIC_INLINE ret_code_t short_name_decode(uint8_t              const * p_short_name_data,
                                             uint8_t                      len,
                                             nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    p_nfc_ble_pairing_data->device_name.name_type = BLE_ADVDATA_SHORT_NAME;

    return name_decode(p_short_name_data, len, p_nfc_ble_pairing_data);
}

/**@brief Decodes and stores AD Data from Full Device Name AD Structure. */
__STATIC_INLINE ret_code_t full_name_decode(uint8_t              const * p_full_name_data,
                                            uint8_t                      len,
                                            nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    p_nfc_ble_pairing_data->device_name.name_type = BLE_ADVDATA_FULL_NAME;

    return name_decode(p_full_name_data, len, p_nfc_ble_pairing_data);
}

/**@brief Decodes and stores AD Data from Security Manager TK AD Structure. */
static ret_code_t tk_value_decode(uint8_t              const * p_tk_value_data,
                                  uint8_t                      len,
                                  nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    if (len != AD_TYPE_TK_VALUE_DATA_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    ble_advdata_tk_value_t * p_tk_value = p_nfc_ble_pairing_data->p_tk_value;
    VERIFY_PARAM_NOT_NULL(p_tk_value);

    memcpy(p_tk_value->tk, p_tk_value_data, AD_TYPE_TK_VALUE_DATA_SIZE);

    return NRF_SUCCESS;
}

/**@brief Decodes and stores AD Data from Security Manager TK AD Structure. */
static ret_code_t lesc_confirm_value_decode(uint8_t              const * p_lesc_confirm_value_data,
                                            uint8_t                      len,
                                            nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    if (len != AD_TYPE_CONFIRM_VALUE_DATA_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    uint8_t * p_lesc_confirm_data = p_nfc_ble_pairing_data->p_lesc_confirm_value;
    VERIFY_PARAM_NOT_NULL(p_lesc_confirm_data);

    memcpy(p_lesc_confirm_data, p_lesc_confirm_value_data, AD_TYPE_CONFIRM_VALUE_DATA_SIZE);

    return NRF_SUCCESS;
}

/**@brief Decodes and stores AD Data from Security Manager TK AD Structure. */
static ret_code_t lesc_random_value_decode(uint8_t              const * p_lesc_random_value_data,
                                           uint8_t                      len,
                                           nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    if (len != AD_TYPE_RANDOM_VALUE_DATA_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    uint8_t * p_lesc_random_data = p_nfc_ble_pairing_data->p_lesc_random_value;
    VERIFY_PARAM_NOT_NULL(p_lesc_random_data);

    memcpy(p_lesc_random_data, p_lesc_random_value_data, AD_TYPE_RANDOM_VALUE_DATA_SIZE);

    return NRF_SUCCESS;
}

/**@brief Decodes and stores AD Data from Security Manager OOB Flags AD Structure. */
static ret_code_t sec_mgr_oob_flags_decode(uint8_t              const * p_sec_mgr_oob_flags_data,
                                           uint8_t                      len,
                                           nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    if (len != AD_TYPE_OOB_FLAGS_DATA_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    VERIFY_PARAM_NOT_NULL(p_nfc_ble_pairing_data->p_sec_mgr_oob_flags);
    *(p_nfc_ble_pairing_data->p_sec_mgr_oob_flags) = *(p_sec_mgr_oob_flags_data);

    return NRF_SUCCESS;
}

/**@brief Decodes and stores AD Data from Appearance AD Structure. */
static ret_code_t appearance_decode(uint8_t              const * p_appearance_data,
                                    uint8_t                      len,
                                    nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    if (len != AD_TYPE_APPEARANCE_DATA_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    p_nfc_ble_pairing_data->appearance = uint16_decode(p_appearance_data);

    return NRF_SUCCESS;
}

/**@brief Decodes and stores AD Data from LE Bluetooth Device Address AD Structure. */
static ret_code_t ble_device_addr_decode(uint8_t              const * p_dev_addr_data,
                                         uint8_t                      len,
                                         nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    if (len != AD_TYPE_BLE_DEVICE_ADDR_DATA_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    ble_gap_addr_t * p_device_addr = p_nfc_ble_pairing_data->p_device_addr;
    VERIFY_PARAM_NOT_NULL(p_device_addr);

    memcpy(p_device_addr->addr, p_dev_addr_data, BLE_GAP_ADDR_LEN);
    p_device_addr->addr_type = *(p_dev_addr_data + BLE_GAP_ADDR_LEN);

    return NRF_SUCCESS;
}

/**@brief Decodes and stores AD Data from LE Role AD Structure. */
static ret_code_t le_role_decode(uint8_t              const * p_le_role_data,
                                 uint8_t                      len,
                                 nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    if (len !=  AD_TYPE_LE_ROLE_DATA_SIZE)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    uint8_t le_role = *p_le_role_data;
    switch (le_role)
    {
        case NFC_BLE_ADVDATA_ROLE_ENCODED_ONLY_PERIPH:
            p_nfc_ble_pairing_data->le_role = BLE_ADVDATA_ROLE_ONLY_PERIPH;
            break;

        case NFC_BLE_ADVDATA_ROLE_ENCODED_ONLY_CENTRAL:
            p_nfc_ble_pairing_data->le_role = BLE_ADVDATA_ROLE_ONLY_CENTRAL;
            break;

        case NFC_BLE_ADVDATA_ROLE_ENCODED_BOTH_PERIPH_PREFERRED:
            p_nfc_ble_pairing_data->le_role = BLE_ADVDATA_ROLE_BOTH_PERIPH_PREFERRED;
            break;

        case NFC_BLE_ADVDATA_ROLE_ENCODED_BOTH_CENTRAL_PREFERRED:
            p_nfc_ble_pairing_data->le_role = BLE_ADVDATA_ROLE_BOTH_CENTRAL_PREFERRED;
            break;

        default:
            return NRF_ERROR_INVALID_PARAM;
    }

    return NRF_SUCCESS;
}

/**@brief Validates if Length field of AD structure is correct. */
__STATIC_INLINE ret_code_t field_length_validate(uint8_t field_length, uint8_t index, uint8_t len)
{
    if ( (field_length == FIELD_LEN_INC_VAL) || (index + field_length >= len) )
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    else
    {
        return NRF_SUCCESS;
    }
}

/**@brief Validates which AD types were not present in parsed data and checks if any
 *        AD Type occured more than once.
 */
__STATIC_INLINE ret_code_t field_type_validate(nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data,
                                               ad_type_counter_t          * ad_type_counter)
{
    /* Reset AD type fields which were not present in parsed buffer. */
    if (ad_type_counter->name_type == AD_TYPE_NOT_PRESENT)
    {
        p_nfc_ble_pairing_data->device_name.p_name    = NULL;
        p_nfc_ble_pairing_data->device_name.len       = 0;
        p_nfc_ble_pairing_data->device_name.name_type = BLE_ADVDATA_NO_NAME;
    }
    if ( (ad_type_counter->addr_type == AD_TYPE_NOT_PRESENT) &&
         (p_nfc_ble_pairing_data->p_device_addr != NULL) )
    {
        p_nfc_ble_pairing_data->p_device_addr = NULL;
    }
    if ( (ad_type_counter->tk_type == AD_TYPE_NOT_PRESENT) &&
         (p_nfc_ble_pairing_data->p_tk_value != NULL) )
    {
        p_nfc_ble_pairing_data->p_tk_value = NULL;
    }
    if ( (ad_type_counter->lesc_confirm_type == AD_TYPE_NOT_PRESENT) &&
         (p_nfc_ble_pairing_data->p_lesc_confirm_value != NULL) )
    {
        p_nfc_ble_pairing_data->p_lesc_confirm_value = NULL;
    }
    if ( (ad_type_counter->lesc_random_type == AD_TYPE_NOT_PRESENT) &&
         (p_nfc_ble_pairing_data->p_lesc_random_value != NULL) )
    {
        p_nfc_ble_pairing_data->p_lesc_random_value = NULL;
    }
    if ( (ad_type_counter->sec_mgr_oob_flags_type == AD_TYPE_NOT_PRESENT) &&
         (p_nfc_ble_pairing_data->p_sec_mgr_oob_flags != NULL) )
    {
        p_nfc_ble_pairing_data->p_sec_mgr_oob_flags = NULL;
    }
    if (ad_type_counter->appear_type == AD_TYPE_NOT_PRESENT)
    {
        p_nfc_ble_pairing_data->appearance = BLE_ADVDATA_APPEARANCE_NOT_PRESENT;
    }
    if (ad_type_counter->flags_type == AD_TYPE_NOT_PRESENT)
    {
        p_nfc_ble_pairing_data->flags = 0;
    }
    if (ad_type_counter->le_role_type == AD_TYPE_NOT_PRESENT)
    {
        p_nfc_ble_pairing_data->le_role = BLE_ADVDATA_ROLE_NOT_PRESENT;
    }

    /* Check if any AD Type was doubled. */
    if ( (ad_type_counter->name_type              > AD_TYPE_OCCUR_THRES) ||
         (ad_type_counter->addr_type              > AD_TYPE_OCCUR_THRES) ||
         (ad_type_counter->tk_type                > AD_TYPE_OCCUR_THRES) ||
         (ad_type_counter->sec_mgr_oob_flags_type > AD_TYPE_OCCUR_THRES) ||
         (ad_type_counter->appear_type            > AD_TYPE_OCCUR_THRES) ||
         (ad_type_counter->flags_type             > AD_TYPE_OCCUR_THRES) ||
         (ad_type_counter->le_role_type           > AD_TYPE_OCCUR_THRES) ||
         (ad_type_counter->lesc_confirm_type      > AD_TYPE_OCCUR_THRES) ||
         (ad_type_counter->lesc_random_type       > AD_TYPE_OCCUR_THRES) )
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    return NRF_SUCCESS;
}

ret_code_t nfc_ble_oob_advdata_parse(uint8_t              const * p_advdata,
                                     uint8_t                      len,
                                     nfc_ble_oob_pairing_data_t * p_nfc_ble_pairing_data)
{
    ret_code_t err_code = NRF_SUCCESS;
    uint8_t    index    = 0;

    ad_type_counter_t ad_type_counter;
    memset(&ad_type_counter, AD_TYPE_NOT_PRESENT, sizeof(ad_type_counter_t));

    if ( (p_nfc_ble_pairing_data == NULL) || (p_advdata == NULL) )
    {
        return NRF_ERROR_NULL;
    }

    while (index < len)
    {
        uint8_t field_length = p_advdata[index];
        if (field_length == EARLY_TERMINATOR)
        {
            return NRF_SUCCESS;
        }
        err_code = field_length_validate(field_length, index, len);
        VERIFY_SUCCESS(err_code);

        uint8_t         field_type     =  p_advdata[index + ADV_LENGTH_FIELD_SIZE];
        uint8_t const * p_field_data   =  &p_advdata[index + ADV_AD_DATA_OFFSET];
        uint8_t         field_data_len =  field_length - ADV_AD_TYPE_FIELD_SIZE;

        switch (field_type)
        {
            case BLE_GAP_AD_TYPE_FLAGS:
                ++ad_type_counter.flags_type;
                err_code = flags_decode(p_field_data,
                                        field_data_len,
                                        p_nfc_ble_pairing_data);
                break;

            case BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME:
                ++ad_type_counter.name_type;
                err_code = short_name_decode(p_field_data,
                                             field_data_len,
                                             p_nfc_ble_pairing_data);
                break;

            case BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME:
                ++ad_type_counter.name_type;
                err_code = full_name_decode(p_field_data,
                                            field_data_len,
                                            p_nfc_ble_pairing_data);
                break;

            case BLE_GAP_AD_TYPE_SECURITY_MANAGER_TK_VALUE:
                ++ad_type_counter.tk_type;
                err_code = tk_value_decode(p_field_data,
                                           field_data_len,
                                           p_nfc_ble_pairing_data);
                break;

            case BLE_GAP_AD_TYPE_LESC_CONFIRM_VALUE:
                ++ad_type_counter.lesc_confirm_type;
                err_code = lesc_confirm_value_decode(p_field_data,
                                                    field_data_len,
                                                    p_nfc_ble_pairing_data);
                break;

            case BLE_GAP_AD_TYPE_LESC_RANDOM_VALUE:
                ++ad_type_counter.lesc_random_type;
                err_code = lesc_random_value_decode(p_field_data,
                                                    field_data_len,
                                                    p_nfc_ble_pairing_data);
                break;

            case BLE_GAP_AD_TYPE_SECURITY_MANAGER_OOB_FLAGS:
                ++ad_type_counter.sec_mgr_oob_flags_type;
                err_code = sec_mgr_oob_flags_decode(p_field_data,
                                                    field_data_len,
                                                    p_nfc_ble_pairing_data);
                break;

            case BLE_GAP_AD_TYPE_APPEARANCE:
                ++ad_type_counter.appear_type;
                err_code = appearance_decode(p_field_data,
                                             field_data_len,
                                             p_nfc_ble_pairing_data);
                break;

            case BLE_GAP_AD_TYPE_LE_BLUETOOTH_DEVICE_ADDRESS:
                ++ad_type_counter.addr_type;
                err_code = ble_device_addr_decode(p_field_data,
                                                  field_data_len,
                                                  p_nfc_ble_pairing_data);
                break;

            case BLE_GAP_AD_TYPE_LE_ROLE:
                ++ad_type_counter.le_role_type;
                err_code = le_role_decode(p_field_data,
                                          field_data_len,
                                          p_nfc_ble_pairing_data);
                break;

            default:
                /* AD Structure Type field unknown for parser. */
                return NRF_ERROR_NOT_SUPPORTED;
        }

        VERIFY_SUCCESS(err_code);

        index += field_length + ADV_LENGTH_FIELD_SIZE;
    }

    err_code = field_type_validate(p_nfc_ble_pairing_data, &ad_type_counter);
    return err_code;
}

ret_code_t nfc_ble_oob_advdata_parser_field_find(uint8_t    type,
                                                 uint8_t *  p_advdata,
                                                 uint8_t *  p_len,
                                                 uint8_t ** pp_field_data)
{
    uint8_t    index    = 0;
    ret_code_t err_code = NRF_SUCCESS;

    if ( (pp_field_data == NULL) || (p_len == NULL) || (p_advdata == NULL) )
    {
        return NRF_ERROR_NULL;
    }

    while (index < *p_len)
    {
        uint8_t field_length = p_advdata[index];
        if (field_length == EARLY_TERMINATOR)
        {
            return NRF_ERROR_NOT_FOUND;
        }
        err_code = field_length_validate(field_length, index, *p_len);
        VERIFY_SUCCESS(err_code);

        uint8_t field_type   = p_advdata[index + ADV_LENGTH_FIELD_SIZE];
        if (field_type == type)
        {
            *pp_field_data  = &p_advdata[index + ADV_AD_DATA_OFFSET];
            *p_len          = field_length - ADV_AD_TYPE_FIELD_SIZE;
            return NRF_SUCCESS;
        }
        index += field_length + ADV_LENGTH_FIELD_SIZE;
    }
    return NRF_ERROR_NOT_FOUND;
}
