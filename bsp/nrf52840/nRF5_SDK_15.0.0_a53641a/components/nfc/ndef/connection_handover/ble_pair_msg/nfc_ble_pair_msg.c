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
#if NRF_MODULE_ENABLED(NFC_BLE_PAIR_MSG)

#include "nfc_ble_pair_msg.h"
#include "nfc_hs_rec.h"
#include "nfc_ac_rec.h"
#include "nfc_le_oob_rec.h"
#include "nfc_ep_oob_rec.h"
#include "nfc_ndef_msg.h"
#include "sdk_macros.h"

/**
 * @brief Descriptor of TK value locations in Connection Handover NDEF message.
 */
typedef struct
{
    uint8_t ** pp_tk_group;  /**< Pointer to array of pointer with TK locations in CH NDEF message. */
    uint8_t    tk_num;       /**< Number of valid TK locations. */
    uint8_t    tk_max_num;   /**< Maximal number of possible TK locations. */
} nfc_ble_tk_group_t;

/**
 * @brief Descriptor of LESC OOB data in Connection Handover NDEF message.
 */
typedef struct
{
    uint8_t * confirm; /**< Pointer to the LESC OOB confirmation value in the CH NDEF message. */
    uint8_t * random;  /**< Pointer to the LESC OOB random value in the CH NDEF message. */
} nfc_ble_lesc_data_pos_t;

static nfc_ble_lesc_data_pos_t  m_lesc_pos = {NULL, NULL}; /**< Descriptor used to update LESC keys in the NDEF Message */
static nfc_ble_tk_group_t       m_tk_group;                /**< Descriptor used to find TK locations in the NDEF Message which require update. */
static bool                     m_tk_modifier_on = false;  /**< Flag indicating that TK modifier feature is on. */

/* Default value for Security Manager Out Of Band Flags field in BLE AD structure */
/* which is used for EP OOB Record payload */
static const uint8_t sec_mgr_oob_flags =
    (AD_TYPE_SEC_MGR_OOB_FLAG_SET   << AD_TYPE_SEC_MGR_OOB_FLAG_OOB_DATA_PRESENT_POS) |
    (AD_TYPE_SEC_MGR_OOB_FLAG_SET   << AD_TYPE_SEC_MGR_OOB_FLAG_OOB_LE_SUPPORTED_POS) |
    (AD_TYPE_SEC_MGR_OOB_FLAG_CLEAR << AD_TYPE_SEC_MGR_OOB_FLAG_SIM_LE_AND_EP_POS)    |
    (AD_TYPE_SEC_MGR_OOB_ADDRESS_TYPE_RANDOM << AD_TYPE_SEC_MGR_OOB_FLAG_ADDRESS_TYPE_POS);

/**@brief Function for configuring TK group modifier feature.
 *
 * @details This function configures the structure which is responsible for tracking TK locations.
 *          These locations can be afterwards easily accessed with @ref nfc_tk_group_modifier_update
 *          and modified.
 *
 * @param[in]  pp_tk_group     Pointer to array of TK locations that should be modified with
 *                             @ref nfc_tk_group_modifier_update function.
 * @param[in]  max_group_size  Maximal number of TK locations that can added to \p pp_tk_group.
 */
__STATIC_INLINE void nfc_tk_group_modifier_config(uint8_t ** pp_tk_group, uint8_t max_group_size)
{
    m_tk_group.pp_tk_group = pp_tk_group;
    m_tk_group.tk_num      = 0;
    m_tk_group.tk_max_num  = max_group_size;
}

/** @brief Function for creating an AD structure with common configuration for EP and LE OOB records.
 *
 * This function creates an AD structure and initializes its fields with default content. Only
 * fields that are common for both EP and LE OOB records are filled.
 *
 * @param[in]       p_tk_value          Pointer to the authentication Temporary Key (TK). If NULL,
 *                                      TK field of the returned AD structure is empty.
 * @param[out]      p_adv_data          Pointer to BLE AD structure with common configuration for EP
 *                                      and LE OOB records.
 */
static void common_adv_data_create(ble_advdata_tk_value_t  * const p_tk_value,
                                   ble_gap_lesc_oob_data_t * const p_lesc_data,
                                   ble_advdata_t           * const p_adv_data)
{
    memset((uint8_t *) p_adv_data, 0, sizeof(ble_advdata_t));

    /* Set common configuration of AD structure for both Bluetooth EP and LE record */
    p_adv_data->include_appearance = true;
    p_adv_data->name_type          = BLE_ADVDATA_FULL_NAME;
    p_adv_data->p_tk_value         = NULL;
    if (p_tk_value != NULL)
    {
        p_adv_data->p_tk_value = p_tk_value;
    }

    p_adv_data->p_lesc_data = p_lesc_data;
}

/** @brief Function for creating an AD structure with default configuration for an LE OOB record.
 *
 * This function creates an AD structure and initializes its fields with default content for
 * LE OOB record payload.
 *
 * @param[in]       p_tk_value          Pointer to the authentication Temporary Key (TK). If NULL,
 *                                      TK field of the returned AD structure is empty.
 * @param[out]      p_le_adv_data       Pointer to BLE AD structure with default configuration
 *                                      for LE OOB record.
 */
static void le_oob_specific_adv_data_create(ble_advdata_tk_value_t  * const p_tk_value,
                                            ble_gap_lesc_oob_data_t * const p_lesc_data,
                                            ble_advdata_t           * const p_le_adv_data)
{
    /* Create default configuration which is common for both EP and LE OOB Records */
    common_adv_data_create(p_tk_value, p_lesc_data, p_le_adv_data);

    /* LE specific configuration */
    p_le_adv_data->include_ble_device_addr = true;
    p_le_adv_data->le_role                 = BLE_ADVDATA_ROLE_ONLY_PERIPH;
    p_le_adv_data->flags                   = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;
}

/** @brief Function for creating an AD structure with default configuration for an EP OOB record.
 *
 * This function creates an AD structure and initializes its fields with default content for
 * EP OOB record payload.
 *
 * @param[in]       p_tk_value          Pointer to the authentication Temporary Key (TK). If NULL,
 *                                      TK field of the returned AD structure is empty.
 * @param[out]      p_ep_adv_data       Pointer to BLE AD structure with default configuration
 *                                      for EP OOB record.
 */
static void ep_oob_specific_adv_data_create(ble_advdata_tk_value_t  * const p_tk_value,
                                            ble_gap_lesc_oob_data_t * const p_lesc_data,
                                            ble_advdata_t           * const p_ep_adv_data)
{
    /* Create default configuration which is common for both EP and LE OOB Records */
    common_adv_data_create(p_tk_value, p_lesc_data, p_ep_adv_data);

    /* EP specific configuration */
    p_ep_adv_data->p_sec_mgr_oob_flags = (uint8_t *) &sec_mgr_oob_flags;
}

ret_code_t nfc_ble_simplified_le_oob_msg_encode(ble_advdata_t const * const p_le_advdata,
                                                uint8_t             *       p_buf,
                                                uint32_t            *       p_len)
{
    ret_code_t err_code;

    /* Create NFC NDEF message description, capacity - 1 record */
    NFC_NDEF_MSG_DEF(nfc_le_oob_msg, 1);

    /* Create NFC NDEF LE OOB Record description without record ID field */
    NFC_NDEF_LE_OOB_RECORD_DESC_DEF(nfc_le_oob_rec, 0, p_le_advdata);

    /* Add LE OOB Record as lone record to message */
    err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_le_oob_msg),
                                       &NFC_NDEF_LE_OOB_RECORD_DESC(nfc_le_oob_rec));
    VERIFY_SUCCESS(err_code);
    VERIFY_PARAM_NOT_NULL(p_le_advdata);

    if (!m_tk_modifier_on)
    {
        nfc_tk_group_modifier_config(NULL, 0);
    }

    /* Encode whole message into buffer */
    err_code = nfc_ndef_msg_encode(&NFC_NDEF_MSG(nfc_le_oob_msg),
                                   p_buf,
                                   p_len);

    return err_code;
}

ret_code_t nfc_ble_simplified_ep_oob_msg_encode(ble_advdata_t const * const p_ep_advdata,
                                                uint8_t             *       p_buf,
                                                uint32_t            *       p_len)
{
    ret_code_t err_code;

    /* Create NFC NDEF message description, capacity - 1 record */
    NFC_NDEF_MSG_DEF(nfc_ep_oob_msg, 1);

    /* Create NFC NDEF EP OOB Record description without record ID field */
    NFC_NDEF_EP_OOB_RECORD_DESC_DEF(nfc_ep_oob_rec, 0, p_ep_advdata);

    /* Add EP OOB Record as lone record to message */
    err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_ep_oob_msg),
                                       &NFC_NDEF_EP_OOB_RECORD_DESC(nfc_ep_oob_rec));
    VERIFY_SUCCESS(err_code);
    VERIFY_PARAM_NOT_NULL(p_ep_advdata);

    if (!m_tk_modifier_on)
    {
        nfc_tk_group_modifier_config(NULL, 0);
    }

    /* Encode whole message into buffer */
    err_code = nfc_ndef_msg_encode(&NFC_NDEF_MSG(nfc_ep_oob_msg),
                                   p_buf,
                                   p_len);

    return err_code;
}

ret_code_t nfc_ble_full_handover_select_msg_encode(ble_advdata_t const * const p_le_advdata,
                                                   ble_advdata_t const * const p_ep_advdata,
                                                   uint8_t             *       p_buf,
                                                   uint32_t            *       p_len)
{
    ret_code_t err_code;

    // Carrier reference buffers for ac records.
    uint8_t carrier_le_reference = '0';
    uint8_t carrier_ep_reference = '1';

    // Create ac records for both message types.
    NFC_NDEF_AC_RECORD_DESC_DEF(ac_rec_le, NFC_AC_CPS_ACTIVE, 1, &carrier_le_reference, 1);
    NFC_NDEF_AC_RECORD_DESC_DEF(ac_rec_ep, NFC_AC_CPS_ACTIVE, 1, &carrier_ep_reference, 1);

    // Create a Hs record and assign existing ac records to it.
    NFC_NDEF_HS_RECORD_DESC_DEF(hs_rec, 1, 3, 2);
    err_code = nfc_hs_rec_local_record_add(&NFC_NDEF_HS_RECORD_DESC(hs_rec),
                                           &NFC_NDEF_AC_RECORD_DESC(ac_rec_le));
    VERIFY_SUCCESS(err_code);
    err_code = nfc_hs_rec_local_record_add(&NFC_NDEF_HS_RECORD_DESC(hs_rec),
                                           &NFC_NDEF_AC_RECORD_DESC(ac_rec_ep));
    VERIFY_SUCCESS(err_code);

    // Create LE and EP records with different record IDs.
    NFC_NDEF_LE_OOB_RECORD_DESC_DEF(nfc_le_oob_rec, carrier_le_reference, p_le_advdata);
    NFC_NDEF_EP_OOB_RECORD_DESC_DEF(nfc_ep_oob_rec, carrier_ep_reference, p_ep_advdata);

    // Create full NDEF Handover Select message for Connection Handover and assign Hs,
    // LE and EP records to it.
    NFC_NDEF_MSG_DEF(nfc_hs_full_msg, 3);
    err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_hs_full_msg),
                                       &NFC_NDEF_HS_RECORD_DESC(hs_rec));
    VERIFY_SUCCESS(err_code);
    err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_hs_full_msg),
                                       &NFC_NDEF_LE_OOB_RECORD_DESC(nfc_le_oob_rec));
    VERIFY_SUCCESS(err_code);
    err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_hs_full_msg),
                                       &NFC_NDEF_EP_OOB_RECORD_DESC(nfc_ep_oob_rec));
    VERIFY_SUCCESS(err_code);

    VERIFY_PARAM_NOT_NULL(p_le_advdata);
    VERIFY_PARAM_NOT_NULL(p_ep_advdata);

    if (!m_tk_modifier_on)
    {
        nfc_tk_group_modifier_config(NULL, 0);
    }

    /* Encode whole message into buffer */
    err_code = nfc_ndef_msg_encode(&NFC_NDEF_MSG(nfc_hs_full_msg),
                                   p_buf,
                                   p_len);

    return err_code;
}

ret_code_t nfc_ble_pair_default_msg_encode(nfc_ble_pair_type_t             nfc_ble_pair_type,
                                           ble_advdata_tk_value_t  * const p_tk_value,
                                           ble_gap_lesc_oob_data_t * const p_lesc_data,
                                           uint8_t                 *       p_buf,
                                           uint32_t                *       p_len)
{
    ble_advdata_t le_adv_data;
    ble_advdata_t ep_adv_data;
    ret_code_t    err_code = NRF_SUCCESS;

    switch (nfc_ble_pair_type)
    {

        case NFC_BLE_PAIR_MSG_BLUETOOTH_LE_SHORT:
            le_oob_specific_adv_data_create(p_tk_value, p_lesc_data, &le_adv_data);
            err_code = nfc_ble_simplified_le_oob_msg_encode(&le_adv_data, p_buf, p_len);
            break;

        case NFC_BLE_PAIR_MSG_BLUETOOTH_EP_SHORT:
            ep_oob_specific_adv_data_create(p_tk_value, NULL, &ep_adv_data);
            err_code = nfc_ble_simplified_ep_oob_msg_encode(&ep_adv_data, p_buf, p_len);
            break;

        case NFC_BLE_PAIR_MSG_FULL:
            le_oob_specific_adv_data_create(p_tk_value, p_lesc_data, &le_adv_data);
            ep_oob_specific_adv_data_create(p_tk_value, NULL, &ep_adv_data);
            err_code = nfc_ble_full_handover_select_msg_encode(&le_adv_data,
                                                               &ep_adv_data,
                                                               p_buf,
                                                               p_len);
            break;

    }

    return err_code;
}

ret_code_t nfc_ble_pair_msg_updatable_tk_encode(nfc_ble_pair_type_t             nfc_ble_pair_type,
                                                ble_advdata_tk_value_t  * const p_tk_value,
                                                ble_gap_lesc_oob_data_t * const p_lesc_data,
                                                uint8_t                 *       p_buf,
                                                uint32_t                *       p_len,
                                                uint8_t                **       pp_tk_group,
                                                uint8_t                         max_group_size)
{
    ret_code_t err_code = NRF_SUCCESS;

    m_tk_modifier_on = true;
    nfc_tk_group_modifier_config(pp_tk_group, max_group_size);
    err_code = nfc_ble_pair_default_msg_encode(nfc_ble_pair_type, p_tk_value,
                                               p_lesc_data, p_buf, p_len);
    m_tk_modifier_on = false;

    return err_code;
}

ret_code_t nfc_tk_group_modifier_update(ble_advdata_tk_value_t * p_tk_value)
{
    VERIFY_PARAM_NOT_NULL(m_tk_group.pp_tk_group);
    for (uint8_t tk_index = 0; tk_index < m_tk_group.tk_num; ++tk_index)
    {
        uint8_t * p_tk_payload_data = m_tk_group.pp_tk_group[tk_index];
        nfc_tk_value_payload_encode(p_tk_value, p_tk_payload_data);
    }
    return NRF_SUCCESS;
}

ret_code_t nfc_tk_to_group_add(uint8_t * p_tk_location)
{
    // Feature was disabled.
    if (m_tk_group.pp_tk_group == NULL)
    {
        return NRF_SUCCESS;
    }

    if (m_tk_group.tk_num < m_tk_group.tk_max_num)
    {
        m_tk_group.pp_tk_group[m_tk_group.tk_num++] = p_tk_location;
        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_NO_MEM;
    }
}

ret_code_t nfc_lesc_pos_set(uint8_t * p_confirm, uint8_t * p_random)
{
    if ((p_confirm != NULL) && (p_random != NULL))
    {
        m_lesc_pos.confirm = p_confirm;
        m_lesc_pos.random = p_random;

        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_NULL;
    }
}

ret_code_t nfc_lesc_data_update(ble_gap_lesc_oob_data_t * p_ble_lesc_oob_data)
{
    if (p_ble_lesc_oob_data != NULL)
    {
        if ((m_lesc_pos.confirm != NULL) && (m_lesc_pos.random != NULL))
        {
            memcpy(m_lesc_pos.confirm, p_ble_lesc_oob_data->c, AD_TYPE_CONFIRM_VALUE_DATA_SIZE);
            memcpy(m_lesc_pos.random, p_ble_lesc_oob_data->r, AD_TYPE_RANDOM_VALUE_DATA_SIZE);

            return NRF_SUCCESS;
        }

        return NRF_ERROR_INVALID_STATE;
    }
    else
    {
        return NRF_ERROR_NULL;
    }
}

#endif // NRF_MODULE_ENABLED(NFC_BLE_PAIR_MSG)
