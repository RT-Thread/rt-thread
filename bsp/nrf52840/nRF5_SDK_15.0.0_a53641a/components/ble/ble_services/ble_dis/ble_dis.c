/**
 * Copyright (c) 2012 - 2018, Nordic Semiconductor ASA
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
 * To maintain compliance with Nordic Semiconductor ASA's Bluetooth profile
 * qualification listings, this section of source code must not be modified.
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_DIS)
#include "ble_dis.h"

#include <stdlib.h>
#include <string.h>
#include "app_error.h"
#include "ble_gatts.h"
#include "ble_srv_common.h"


#define BLE_DIS_SYS_ID_LEN 8  /**< Length of System ID Characteristic Value. */
#define BLE_DIS_PNP_ID_LEN 7  /**< Length of Pnp ID Characteristic Value. */

static uint16_t                 service_handle;
static ble_gatts_char_handles_t manufact_name_handles;
static ble_gatts_char_handles_t model_num_handles;
static ble_gatts_char_handles_t serial_num_handles;
static ble_gatts_char_handles_t hw_rev_handles;
static ble_gatts_char_handles_t fw_rev_handles;
static ble_gatts_char_handles_t sw_rev_handles;
static ble_gatts_char_handles_t sys_id_handles;
static ble_gatts_char_handles_t reg_cert_data_list_handles;
static ble_gatts_char_handles_t pnp_id_handles;


/**@brief Function for encoding a System ID.
 *
 * @param[out]  p_encoded_buffer   Buffer where the encoded data will be written.
 * @param[in]   p_sys_id           System ID to be encoded.
 */
static void sys_id_encode(uint8_t * p_encoded_buffer, ble_dis_sys_id_t const * p_sys_id)
{
    APP_ERROR_CHECK_BOOL(p_sys_id != NULL);
    APP_ERROR_CHECK_BOOL(p_encoded_buffer != NULL);

    p_encoded_buffer[0] = (p_sys_id->manufacturer_id & 0x00000000FF);
    p_encoded_buffer[1] = (p_sys_id->manufacturer_id & 0x000000FF00) >> 8;
    p_encoded_buffer[2] = (p_sys_id->manufacturer_id & 0x0000FF0000) >> 16;
    p_encoded_buffer[3] = (p_sys_id->manufacturer_id & 0x00FF000000) >> 24;
    p_encoded_buffer[4] = (p_sys_id->manufacturer_id & 0xFF00000000) >> 32;

    p_encoded_buffer[5] = (p_sys_id->organizationally_unique_id & 0x0000FF);
    p_encoded_buffer[6] = (p_sys_id->organizationally_unique_id & 0x00FF00) >> 8;
    p_encoded_buffer[7] = (p_sys_id->organizationally_unique_id & 0xFF0000) >> 16;
}


/**@brief Function for encoding a PnP ID.
 *
 * @param[out]  p_encoded_buffer   Buffer where the encoded data will be written.
 * @param[in]   p_pnp_id           PnP ID to be encoded.
 */
static void pnp_id_encode(uint8_t * p_encoded_buffer, ble_dis_pnp_id_t const * p_pnp_id)
{
    uint8_t len = 0;

    APP_ERROR_CHECK_BOOL(p_pnp_id != NULL);
    APP_ERROR_CHECK_BOOL(p_encoded_buffer != NULL);

    p_encoded_buffer[len++] = p_pnp_id->vendor_id_source;

    len += uint16_encode(p_pnp_id->vendor_id, &p_encoded_buffer[len]);
    len += uint16_encode(p_pnp_id->product_id, &p_encoded_buffer[len]);
    len += uint16_encode(p_pnp_id->product_version, &p_encoded_buffer[len]);

    APP_ERROR_CHECK_BOOL(len == BLE_DIS_PNP_ID_LEN);
}


/**@brief Function for adding the Characteristic.
 *
 * @param[in]   uuid           UUID of characteristic to be added.
 * @param[in]   p_char_value   Initial value of characteristic to be added.
 * @param[in]   char_len       Length of initial value. This will also be the maximum value.
 * @param[in]   dis_attr_md    Security settings of characteristic to be added.
 * @param[out]  p_handles      Handles of new characteristic.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t char_add(uint16_t                        uuid,
                         uint8_t                       * p_char_value,
                         uint16_t                        char_len,
                         ble_srv_security_mode_t const * dis_attr_md,
                         ble_gatts_char_handles_t      * p_handles)
{
    ble_uuid_t          ble_uuid;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_gatts_attr_md_t attr_md;

    APP_ERROR_CHECK_BOOL(p_char_value != NULL);
    APP_ERROR_CHECK_BOOL(char_len > 0);

    // The ble_gatts_char_md_t structure uses bit fields. So we reset the memory to zero.
    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read  = 1;
    char_md.p_char_user_desc = NULL;
    char_md.p_char_pf        = NULL;
    char_md.p_user_desc_md   = NULL;
    char_md.p_cccd_md        = NULL;
    char_md.p_sccd_md        = NULL;

    BLE_UUID_BLE_ASSIGN(ble_uuid, uuid);

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = dis_attr_md->read_perm;
    attr_md.write_perm = dis_attr_md->write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = char_len;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = char_len;
    attr_char_value.p_value   = p_char_value;

    return sd_ble_gatts_characteristic_add(service_handle, &char_md, &attr_char_value, p_handles);
}


uint32_t ble_dis_init(ble_dis_init_t const * p_dis_init)
{
    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    // Add service
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_DEVICE_INFORMATION_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add characteristics
    if (p_dis_init->manufact_name_str.length > 0)
    {
        err_code = char_add(BLE_UUID_MANUFACTURER_NAME_STRING_CHAR,
                            p_dis_init->manufact_name_str.p_str,
                            p_dis_init->manufact_name_str.length,
                            &p_dis_init->dis_attr_md,
                            &manufact_name_handles);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    if (p_dis_init->model_num_str.length > 0)
    {
        err_code = char_add(BLE_UUID_MODEL_NUMBER_STRING_CHAR,
                            p_dis_init->model_num_str.p_str,
                            p_dis_init->model_num_str.length,
                            &p_dis_init->dis_attr_md,
                            &model_num_handles);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    if (p_dis_init->serial_num_str.length > 0)
    {
        err_code = char_add(BLE_UUID_SERIAL_NUMBER_STRING_CHAR,
                            p_dis_init->serial_num_str.p_str,
                            p_dis_init->serial_num_str.length,
                            &p_dis_init->dis_attr_md,
                            &serial_num_handles);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    if (p_dis_init->hw_rev_str.length > 0)
    {
        err_code = char_add(BLE_UUID_HARDWARE_REVISION_STRING_CHAR,
                            p_dis_init->hw_rev_str.p_str,
                            p_dis_init->hw_rev_str.length,
                            &p_dis_init->dis_attr_md,
                            &hw_rev_handles);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    if (p_dis_init->fw_rev_str.length > 0)
    {
        err_code = char_add(BLE_UUID_FIRMWARE_REVISION_STRING_CHAR,
                            p_dis_init->fw_rev_str.p_str,
                            p_dis_init->fw_rev_str.length,
                            &p_dis_init->dis_attr_md,
                            &fw_rev_handles);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    if (p_dis_init->sw_rev_str.length > 0)
    {
        err_code = char_add(BLE_UUID_SOFTWARE_REVISION_STRING_CHAR,
                            p_dis_init->sw_rev_str.p_str,
                            p_dis_init->sw_rev_str.length,
                            &p_dis_init->dis_attr_md,
                            &sw_rev_handles);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    if (p_dis_init->p_sys_id != NULL)
    {
        uint8_t encoded_sys_id[BLE_DIS_SYS_ID_LEN];

        sys_id_encode(encoded_sys_id, p_dis_init->p_sys_id);
        err_code = char_add(BLE_UUID_SYSTEM_ID_CHAR,
                            encoded_sys_id,
                            BLE_DIS_SYS_ID_LEN,
                            &p_dis_init->dis_attr_md,
                            &sys_id_handles);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    if (p_dis_init->p_reg_cert_data_list != NULL)
    {
        err_code = char_add(BLE_UUID_IEEE_REGULATORY_CERTIFICATION_DATA_LIST_CHAR,
                            p_dis_init->p_reg_cert_data_list->p_list,
                            p_dis_init->p_reg_cert_data_list->list_len,
                            &p_dis_init->dis_attr_md,
                            &reg_cert_data_list_handles);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }
    if (p_dis_init->p_pnp_id != NULL)
    {
        uint8_t encoded_pnp_id[BLE_DIS_PNP_ID_LEN];

        pnp_id_encode(encoded_pnp_id, p_dis_init->p_pnp_id);
        err_code = char_add(BLE_UUID_PNP_ID_CHAR,
                            encoded_pnp_id,
                            BLE_DIS_PNP_ID_LEN,
                            &p_dis_init->dis_attr_md,
                            &pnp_id_handles);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    return NRF_SUCCESS;
}
#endif // NRF_MODULE_ENABLED(BLE_DIS)
