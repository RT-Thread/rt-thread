/**
 * Copyright (c) 2012 - 2017, Nordic Semiconductor ASA
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
/* Attention!
*  To maintain compliance with Nordic Semiconductor ASA’s Bluetooth profile
*  qualification listings, this section of source code must not be modified.
*/

#include "ble_srv_common.h"
#include <string.h>
#include "nordic_common.h"
#include "app_error.h"
#include "ble.h"

bool ble_srv_is_notification_enabled(uint8_t const * p_encoded_data)
{
    uint16_t cccd_value = uint16_decode(p_encoded_data);
    return ((cccd_value & BLE_GATT_HVX_NOTIFICATION) != 0);
}

bool ble_srv_is_indication_enabled(uint8_t const * p_encoded_data)
{
    uint16_t cccd_value = uint16_decode(p_encoded_data);
    return ((cccd_value & BLE_GATT_HVX_INDICATION) != 0);
}

uint8_t ble_srv_report_ref_encode(uint8_t                    * p_encoded_buffer,
                                  const ble_srv_report_ref_t * p_report_ref)
{
    uint8_t len = 0;

    p_encoded_buffer[len++] = p_report_ref->report_id;
    p_encoded_buffer[len++] = p_report_ref->report_type;

    APP_ERROR_CHECK_BOOL(len == BLE_SRV_ENCODED_REPORT_REF_LEN);
    return len;
}


void ble_srv_ascii_to_utf8(ble_srv_utf8_str_t * p_utf8, char * p_ascii)
{
    p_utf8->length = (uint16_t)strlen(p_ascii);
    p_utf8->p_str  = (uint8_t *)p_ascii;
}


/**@brief Function for setting security requirements of a characteristic.
 *
 * @param[in]  level   required security level.
 * @param[out] p_perm  Characteristic security requirements.
 *
 * @return     encoded security level and security mode.
 */
static inline void set_security_req(security_req_t level, ble_gap_conn_sec_mode_t * p_perm)
{


    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(p_perm);
    switch (level)
    {
        case SEC_NO_ACCESS:
            BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(p_perm);
        break;
        case SEC_OPEN:
            BLE_GAP_CONN_SEC_MODE_SET_OPEN(p_perm);
        break;
        case SEC_JUST_WORKS:
            BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(p_perm);
        break;
        case SEC_MITM:
            BLE_GAP_CONN_SEC_MODE_SET_ENC_WITH_MITM(p_perm);
        break;
        case SEC_SIGNED:
            BLE_GAP_CONN_SEC_MODE_SET_SIGNED_NO_MITM(p_perm);
        break;
        case SEC_SIGNED_MITM:
            BLE_GAP_CONN_SEC_MODE_SET_SIGNED_WITH_MITM(p_perm);
        break;
    }
    return;
}


uint32_t characteristic_add(uint16_t                   service_handle,
                            ble_add_char_params_t *    p_char_props,
                            ble_gatts_char_handles_t * p_char_handle)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          char_uuid;
    ble_gatts_attr_md_t attr_md;
    ble_gatts_attr_md_t user_descr_attr_md;
    ble_gatts_attr_md_t cccd_md;

    if (p_char_props->uuid_type == 0)
    {
        char_uuid.type = BLE_UUID_TYPE_BLE;
    }
    else
    {
        char_uuid.type = p_char_props->uuid_type;
    }
    char_uuid.uuid = p_char_props->uuid;

    memset(&attr_md, 0, sizeof(ble_gatts_attr_md_t));
    set_security_req(p_char_props->read_access, &attr_md.read_perm);
    set_security_req(p_char_props->write_access, & attr_md.write_perm);
    attr_md.rd_auth    = (p_char_props->is_defered_read ? 1 : 0);
    attr_md.wr_auth    = (p_char_props->is_defered_write ? 1 : 0);
    attr_md.vlen       = (p_char_props->is_var_len ? 1 : 0);
    attr_md.vloc       = (p_char_props->is_value_user ? BLE_GATTS_VLOC_USER : BLE_GATTS_VLOC_STACK);


    memset(&char_md, 0, sizeof(ble_gatts_char_md_t));
    if ((p_char_props->char_props.notify == 1)||(p_char_props->char_props.indicate == 1))
    {

        memset(&cccd_md, 0, sizeof(cccd_md));
        set_security_req(p_char_props->cccd_write_access, &cccd_md.write_perm);
        BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);

        cccd_md.vloc       = BLE_GATTS_VLOC_STACK;

        char_md.p_cccd_md  = &cccd_md;
    }
    char_md.char_props     = p_char_props->char_props;
    char_md.char_ext_props = p_char_props->char_ext_props;

    memset(&attr_char_value, 0, sizeof(ble_gatts_attr_t));
    attr_char_value.p_uuid    = &char_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.max_len   = p_char_props->max_len;
    if (p_char_props->p_init_value != NULL)
    {
        attr_char_value.init_len  = p_char_props->init_len;
        attr_char_value.p_value   = p_char_props->p_init_value;
    }
    if (p_char_props->p_user_descr != NULL)
    {
        memset(&user_descr_attr_md, 0, sizeof(ble_gatts_attr_md_t));
        char_md.char_user_desc_max_size = p_char_props->p_user_descr->max_size;
        char_md.char_user_desc_size     = p_char_props->p_user_descr->size;
        char_md.p_char_user_desc        = p_char_props->p_user_descr->p_char_user_desc;

        char_md.p_user_desc_md          = &user_descr_attr_md;

        set_security_req(p_char_props->p_user_descr->read_access, &user_descr_attr_md.read_perm);
        set_security_req(p_char_props->p_user_descr->write_access, &user_descr_attr_md.write_perm);

        user_descr_attr_md.rd_auth      = (p_char_props->p_user_descr->is_defered_read ? 1 : 0);
        user_descr_attr_md.wr_auth      = (p_char_props->p_user_descr->is_defered_write ? 1 : 0);
        user_descr_attr_md.vlen         = (p_char_props->p_user_descr->is_var_len ? 1 : 0);
        user_descr_attr_md.vloc         = (p_char_props->p_user_descr->is_value_user ? BLE_GATTS_VLOC_USER : BLE_GATTS_VLOC_STACK);
    }
    if (p_char_props->p_presentation_format != NULL)
    {
        char_md.p_char_pf = p_char_props->p_presentation_format;
    }
    return sd_ble_gatts_characteristic_add(service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           p_char_handle);
}


uint32_t descriptor_add(uint16_t                   char_handle,
                        ble_add_descr_params_t *   p_descr_props,
                        uint16_t *                 p_descr_handle)
{
    ble_gatts_attr_t    descr_params;
    ble_uuid_t          desc_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&descr_params, 0, sizeof(descr_params));
    if (p_descr_props->uuid_type == 0)
    {
        desc_uuid.type = BLE_UUID_TYPE_BLE;
    }
    else
    {
        desc_uuid.type = p_descr_props->uuid_type;
    }
    desc_uuid.uuid = p_descr_props->uuid;
    descr_params.p_uuid = &desc_uuid;

    set_security_req(p_descr_props->read_access, &attr_md.read_perm);
    set_security_req(p_descr_props->write_access,&attr_md.write_perm);

    attr_md.rd_auth        = (p_descr_props->is_defered_read ? 1 : 0);
    attr_md.wr_auth        = (p_descr_props->is_defered_write ? 1 : 0);
    attr_md.vlen           = (p_descr_props->is_var_len ? 1 : 0);
    attr_md.vloc           = (p_descr_props->is_value_user ? BLE_GATTS_VLOC_USER : BLE_GATTS_VLOC_STACK);
    descr_params.p_attr_md = &attr_md;

    descr_params.init_len  = p_descr_props->init_len;
    descr_params.init_offs = p_descr_props->init_offs;
    descr_params.max_len   = p_descr_props->max_len;
    descr_params.p_value   = p_descr_props->p_value;

    return sd_ble_gatts_descriptor_add(char_handle, &descr_params, p_descr_handle);
}
