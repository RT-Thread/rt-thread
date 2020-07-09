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
#include "nrf_ble_dfu.h"

#include <stddef.h>
#include "sdk_common.h"
#include "nrf_dfu_req_handler.h"
#include "nrf_dfu_transport.h"
#include "nrf_dfu_mbr.h"
#include "nrf_bootloader_info.h"
#include "ble_conn_params.h"
#include "boards.h"
#include "nrf_log.h"
#include "ble_hci.h"
#include "app_timer.h"
#include "softdevice_handler_appsh.h"
#include "nrf_log.h"
#include "nrf_delay.h"
#include "nrf_dfu_handling_error.h"

#define ADVERTISING_LED_PIN_NO              BSP_LED_0                                               /**< Is on when device is advertising. */
#define CONNECTED_LED_PIN_NO                BSP_LED_1                                               /**< Is on when device has connected. */

#define DEVICE_NAME                         "DfuTarg"                                               /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                   "NordicSemiconductor"                                   /**< Manufacturer. Will be passed to Device Information Service. */

#define MIN_CONN_INTERVAL                   (uint16_t)(MSEC_TO_UNITS(15, UNIT_1_25_MS))             /**< Minimum acceptable connection interval. */
#define MAX_CONN_INTERVAL_MS                30                                                      /**< Maximum acceptable connection interval in milliseconds. */
#define MAX_CONN_INTERVAL                   (uint16_t)(MSEC_TO_UNITS(MAX_CONN_INTERVAL_MS, UNIT_1_25_MS))   /**< Maximum acceptable connection interval . */
#define SLAVE_LATENCY                       0                                                       /**< Slave latency. */
#define CONN_SUP_TIMEOUT                    (4 * 100)                                               /**< Connection supervisory timeout (4 seconds). */

#define FIRST_CONN_PARAMS_UPDATE_DELAY      APP_TIMER_TICKS(100)                                    /**< Time from the Connected event to first time sd_ble_gap_conn_param_update is called (100 milliseconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY       APP_TIMER_TICKS(500)                                    /**< Time between each call to sd_ble_gap_conn_param_update after the first call (500 milliseconds). */
#define MAX_CONN_PARAMS_UPDATE_COUNT        3                                                       /**< Number of attempts before giving up the connection parameter negotiation. */

#define MAX_ADV_DATA_LENGTH                 20                                                      /**< Maximum length of advertising data. */

#define APP_ADV_INTERVAL                    MSEC_TO_UNITS(25, UNIT_0_625_MS)                        /**< The advertising interval (25 ms.). */
#define APP_ADV_TIMEOUT_IN_SECONDS          BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED                   /**< The advertising timeout in units of seconds. This is set to @ref BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED so that the advertisement is done as long as there there is a call to @ref dfu_transport_close function.*/

#define APP_FEATURE_NOT_SUPPORTED           BLE_GATT_STATUS_ATTERR_APP_BEGIN + 2                    /**< Reply when unsupported features are requested. */

#define MAX_DFU_PKT_LEN                     (20)                                                    /**< Maximum length (in bytes) of the DFU Packet characteristic. */
#define PKT_CREATE_PARAM_LEN                (6)                                                     /**< Length (in bytes) of the parameters for Create Object request. */
#define PKT_SET_PRN_PARAM_LEN               (3)                                                     /**< Length (in bytes) of the parameters for Set Packet Receipt Notification request. */
#define PKT_READ_OBJECT_INFO_PARAM_LEN      (2)                                                     /**< Length (in bytes) of the parameters for Read Object Info request. */
#define MAX_RESPONSE_LEN                    (17)                                                    /**< Maximum length (in bytes) of the response to a Control Point command. */

#define DFU_BLE_FLAG_NONE                   (0)
#define DFU_BLE_FLAG_SERVICE_INITIALIZED    (1 << 0)                                                /**< Flag to check if the DFU service was initialized by the application.*/
#define DFU_BLE_FLAG_IS_ADVERTISING         (1 << 1)                                                /**< Flag to indicate if advertising is ongoing.*/
#define DFU_BLE_FLAG_TEAR_DOWN_IN_PROGRESS  (1 << 2)                                                /**< Flag to indicate whether a tear down is in progress. A tear down could be because the application has initiated it or the peer has disconnected. */

static ble_dfu_t                            m_dfu;                                                  /**< Structure used to identify the Device Firmware Update service. */
static uint16_t                             m_pkt_notif_target;                                     /**< Number of packets of firmware data to be received before transmitting the next Packet Receipt Notification to the DFU Controller. */
static uint16_t                             m_pkt_notif_target_cnt;                                 /**< Number of packets of firmware data received after sending last Packet Receipt Notification or since the receipt of a @ref BLE_DFU_PKT_RCPT_NOTIF_ENABLED event from the DFU service, which ever occurs later.*/
static uint16_t                             m_conn_handle = BLE_CONN_HANDLE_INVALID;                /**< Handle of the current connection. */
static uint32_t                             m_flags;
static uint8_t                              m_notif_buffer[MAX_RESPONSE_LEN];                       /**< Buffer used for sending notifications to peer. */

//lint -save -e545 -esym(526, dfu_trans) -esym(528, dfu_trans)
DFU_TRANSPORT_REGISTER(nrf_dfu_transport_t const dfu_trans) =
{
    .init_func  = ble_dfu_transport_init,
    .close_func = ble_dfu_transport_close
};
//lint -restore


/**@brief     Function for handling a Connection Parameters error.
 *
 * @param[in] nrf_error Error code.
 */
static void conn_params_error_handler(uint32_t nrf_error)
{
    APP_ERROR_HANDLER(nrf_error);
}


/**@brief Function for initializing the Connection Parameters module.
 */
static uint32_t conn_params_init(void)
{
    ble_conn_params_init_t cp_init = {0};

    cp_init.first_conn_params_update_delay = FIRST_CONN_PARAMS_UPDATE_DELAY;
    cp_init.next_conn_params_update_delay  = NEXT_CONN_PARAMS_UPDATE_DELAY;
    cp_init.max_conn_params_update_count   = MAX_CONN_PARAMS_UPDATE_COUNT;
    cp_init.start_on_notify_cccd_handle    = BLE_GATT_HANDLE_INVALID;
    cp_init.disconnect_on_fail             = false;
    cp_init.error_handler                  = conn_params_error_handler;

    return ble_conn_params_init(&cp_init);
}


/**@brief     Function for the Advertising functionality initialization.
 *
 * @details   Encodes the required advertising data and passes it to the stack.
 *            The advertising data encoded here is specific for DFU.
 *            Setting advertising data can by done by calling @ref ble_advdata_set.
 */
static uint32_t advertising_init(uint8_t adv_flags)
{
    uint32_t err_code;
    uint16_t len_advdata                 = 9;
    uint16_t max_device_name_length      = MAX_ADV_DATA_LENGTH - len_advdata;
    uint16_t actual_device_name_length   = max_device_name_length;

    uint8_t p_encoded_advdata[MAX_ADV_DATA_LENGTH];

    // Encode flags.
    p_encoded_advdata[0] = 0x2;
    p_encoded_advdata[1] = BLE_GAP_AD_TYPE_FLAGS;
    p_encoded_advdata[2] = adv_flags;

    // Encode 'more available' uuid list.
    p_encoded_advdata[3] = 0x3;
    p_encoded_advdata[4] = BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_MORE_AVAILABLE;
    p_encoded_advdata[5] = LSB_16(BLE_DFU_SERVICE_UUID);
    p_encoded_advdata[6] = MSB_16(BLE_DFU_SERVICE_UUID);

    // Get GAP device name and length
    err_code = sd_ble_gap_device_name_get(&p_encoded_advdata[9], &actual_device_name_length);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Set GAP device in advertising data.
    if (actual_device_name_length <= max_device_name_length)
    {
        p_encoded_advdata[7] = actual_device_name_length + 1; // (actual_length + ADV_AD_TYPE_FIELD_SIZE(1))
        p_encoded_advdata[8] = BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME;
        len_advdata += actual_device_name_length;
    }
    else
    {
        // Must use a shorter advertising name than the actual name of the device
        p_encoded_advdata[7] = max_device_name_length + 1; // (length + ADV_AD_TYPE_FIELD_SIZE(1))
        p_encoded_advdata[8] = BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME;
        len_advdata = MAX_ADV_DATA_LENGTH;
    }
    return sd_ble_gap_adv_data_set(p_encoded_advdata, len_advdata, NULL, 0);
}


/**@brief Function for starting advertising.
 */
static uint32_t advertising_start(void)
{
    uint32_t err_code;
    ble_gap_adv_params_t adv_params;

    if ((m_flags & DFU_BLE_FLAG_IS_ADVERTISING) != 0)
    {
        return NRF_SUCCESS;
    }

    // Initialize advertising parameters (used when starting advertising).
    memset(&adv_params, 0, sizeof(adv_params));

    err_code = advertising_init(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    VERIFY_SUCCESS(err_code);

    adv_params.type        = BLE_GAP_ADV_TYPE_ADV_IND;
    adv_params.p_peer_addr = NULL;
    adv_params.fp          = BLE_GAP_ADV_FP_ANY;
    adv_params.interval    = APP_ADV_INTERVAL;
    adv_params.timeout     = APP_ADV_TIMEOUT_IN_SECONDS;

    err_code = sd_ble_gap_adv_start(&adv_params, BLE_CONN_CFG_TAG_DEFAULT);
    VERIFY_SUCCESS(err_code);

    nrf_gpio_pin_clear(ADVERTISING_LED_PIN_NO);
    nrf_gpio_pin_set(CONNECTED_LED_PIN_NO);

    m_flags |= DFU_BLE_FLAG_IS_ADVERTISING;
    return NRF_SUCCESS;
}


/**@brief Function for stopping advertising.
 */
static uint32_t advertising_stop(void)
{
    uint32_t err_code;

    if ((m_flags & DFU_BLE_FLAG_IS_ADVERTISING) == 0)
    {
        return NRF_SUCCESS;
    }

    err_code = sd_ble_gap_adv_stop();
    VERIFY_SUCCESS(err_code);

    nrf_gpio_pin_set(ADVERTISING_LED_PIN_NO);

    m_flags |= DFU_BLE_FLAG_IS_ADVERTISING;
    return NRF_SUCCESS;
}


static bool is_cccd_configured(ble_dfu_t * p_dfu)
{
    uint8_t  cccd_val_buf[BLE_CCCD_VALUE_LEN];
    ble_gatts_value_t gatts_value = {0};

    gatts_value.len     = BLE_CCCD_VALUE_LEN;
    gatts_value.p_value = cccd_val_buf;

    // Check the CCCD Value of DFU Control Point.
    uint32_t err_code = sd_ble_gatts_value_get(m_conn_handle,
                                               p_dfu->dfu_ctrl_pt_handles.cccd_handle,
                                               &gatts_value);
    VERIFY_SUCCESS(err_code);

    return ble_srv_is_notification_enabled(cccd_val_buf);
}


static uint32_t send_hvx(uint16_t conn_handle, uint16_t value_handle, uint16_t len)
{
    ble_gatts_hvx_params_t hvx_params   = {0};

    hvx_params.handle = value_handle;
    hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
    hvx_params.p_len  = &len;
    hvx_params.p_data = m_notif_buffer;

    return sd_ble_gatts_hvx(conn_handle, &hvx_params);
}


static uint32_t response_send(ble_dfu_t          * p_dfu,
                              uint8_t              op_code,
                              nrf_dfu_res_code_t   resp_val)
{
    uint16_t index = 0;

    NRF_LOG_DEBUG("Sending Response: [0x%01x, 0x%01x]\r\n", op_code, resp_val);

#ifndef NRF51
    if (p_dfu == NULL)
    {
        return NRF_ERROR_NULL;
    }
#endif

    if ((m_conn_handle == BLE_CONN_HANDLE_INVALID) || (m_flags & DFU_BLE_FLAG_SERVICE_INITIALIZED) == 0)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    m_notif_buffer[index++] = BLE_DFU_OP_CODE_RESPONSE;

    // Encode the Request Op code
    m_notif_buffer[index++] = op_code;

    // Encode the Response Value.
    m_notif_buffer[index++] = (uint8_t)resp_val;

    // If the error was an extended error code, add the error to the response.
    if (resp_val == NRF_DFU_RES_CODE_EXT_ERROR)
    {
        m_notif_buffer[index++] = ext_error_get();
        // Clear the last extended error code
        (void) ext_error_set(NRF_DFU_EXT_ERROR_NO_ERROR);
    }

    return send_hvx(m_conn_handle, p_dfu->dfu_ctrl_pt_handles.value_handle, index);
}


static uint32_t response_crc_cmd_send(ble_dfu_t * p_dfu,
                                      uint32_t    offset,
                                      uint32_t    crc)
{
    uint16_t index = 0;

    NRF_LOG_DEBUG("Sending CRC: [0x60, 0x03, 0x01, 0:x%08x, CRC:0x%08x]\r\n", offset, crc);

#ifndef NRF51
    if (p_dfu == NULL)
    {
        return NRF_ERROR_NULL;
    }
#endif

    if ((m_conn_handle == BLE_CONN_HANDLE_INVALID) || (m_flags & DFU_BLE_FLAG_SERVICE_INITIALIZED) == 0)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    m_notif_buffer[index++] = BLE_DFU_OP_CODE_RESPONSE;

    // Encode the Request Op code
    m_notif_buffer[index++] = BLE_DFU_OP_CODE_CALCULATE_CRC;

    // Encode the Response Value.
    m_notif_buffer[index++] = (uint8_t)NRF_DFU_RES_CODE_SUCCESS;

    // Encode the Offset Value.
    index += uint32_encode(offset, &m_notif_buffer[index]);

    // Encode the Crc Value.
    index += uint32_encode(crc, &m_notif_buffer[index]);

    return send_hvx(m_conn_handle, p_dfu->dfu_ctrl_pt_handles.value_handle, index);
}


static uint32_t response_select_object_cmd_send(ble_dfu_t * p_dfu,
                                                uint32_t    max_size,
                                                uint32_t    offset,
                                                uint32_t    crc)
{
    uint16_t index = 0;

    NRF_LOG_DEBUG("Sending Object Info: [0x60, 0x06, 0x01 max: 0:x%08x 0:x%08x, CRC:0x%08x]\r\n",
                  max_size, offset, crc);
#ifndef NRF51
    if (p_dfu == NULL)
    {
        return NRF_ERROR_NULL;
    }
#endif

    if ((m_conn_handle == BLE_CONN_HANDLE_INVALID) || (m_flags & DFU_BLE_FLAG_SERVICE_INITIALIZED) == 0)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    m_notif_buffer[index++] = BLE_DFU_OP_CODE_RESPONSE;

    // Encode the Request Op code
    m_notif_buffer[index++] = BLE_DFU_OP_CODE_SELECT_OBJECT;

    // Encode the Success Response Value.
    m_notif_buffer[index++] = (uint8_t)NRF_DFU_RES_CODE_SUCCESS;

    // Encode the Max Size Value.
    index += uint32_encode(max_size, &m_notif_buffer[index]);

    // Encode the Offset Value.
    index += uint32_encode(offset, &m_notif_buffer[index]);

    // Encode the Crc Value.
    index += uint32_encode(crc, &m_notif_buffer[index]);

    return send_hvx(m_conn_handle, p_dfu->dfu_ctrl_pt_handles.value_handle, index);
}


/**@brief     Function for handling a Write event on the Control Point characteristic.
 *
 * @param[in] p_dfu             DFU Service Structure.
 * @param[in] p_ble_write_evt   Pointer to the write event received from BLE stack.
 *
 * @return    NRF_SUCCESS on successful processing of control point write. Otherwise an error code.
 */
static uint32_t on_ctrl_pt_write(ble_dfu_t * p_dfu, ble_gatts_evt_write_t * p_ble_write_evt)
{
    nrf_dfu_res_code_t  res_code;
    nrf_dfu_req_t       dfu_req;
    nrf_dfu_res_t       dfu_res = {{{0}}};

    memset(&dfu_req, 0, sizeof(nrf_dfu_req_t));

    switch (p_ble_write_evt->data[0])
    {
        case BLE_DFU_OP_CODE_CREATE_OBJECT:

            if (p_ble_write_evt->len != PKT_CREATE_PARAM_LEN)
            {
                return response_send(p_dfu,
                                     BLE_DFU_OP_CODE_CREATE_OBJECT,
                                     NRF_DFU_RES_CODE_INVALID_PARAMETER);
            }

            NRF_LOG_DEBUG("Received create object\r\n");

            // Reset the packet receipt notification on create object
            m_pkt_notif_target_cnt = m_pkt_notif_target;

            // Get type parameter
            //lint -save -e415
            dfu_req.obj_type =  p_ble_write_evt->data[1];
            //lint -restore

            // Get length value
            //lint -save -e416
            dfu_req.object_size = uint32_decode(&(p_ble_write_evt->data[2]));
            //lint -restore

            // Set req type
            dfu_req.req_type = NRF_DFU_OBJECT_OP_CREATE;

            res_code = nrf_dfu_req_handler_on_req(NULL, &dfu_req, &dfu_res);
            return response_send(p_dfu, BLE_DFU_OP_CODE_CREATE_OBJECT, res_code);

        case BLE_DFU_OP_CODE_EXECUTE_OBJECT:
            NRF_LOG_DEBUG("Received execute object\r\n");

            // Set req type
            dfu_req.req_type =  NRF_DFU_OBJECT_OP_EXECUTE;

            res_code = nrf_dfu_req_handler_on_req(NULL, &dfu_req, &dfu_res);
            return response_send(p_dfu, BLE_DFU_OP_CODE_EXECUTE_OBJECT, res_code);

        case BLE_DFU_OP_CODE_SET_RECEIPT_NOTIF:
            NRF_LOG_DEBUG("Set receipt notif\r\n");
            if (p_ble_write_evt->len != PKT_SET_PRN_PARAM_LEN)
            {
                return (response_send(p_dfu,
                                      BLE_DFU_OP_CODE_SET_RECEIPT_NOTIF,
                                      NRF_DFU_RES_CODE_INVALID_PARAMETER));
            }

            //lint -save -e415
            m_pkt_notif_target = uint16_decode(&(p_ble_write_evt->data[1]));
            //lint -restore
            m_pkt_notif_target_cnt = m_pkt_notif_target;

            return response_send(p_dfu, BLE_DFU_OP_CODE_SET_RECEIPT_NOTIF, NRF_DFU_RES_CODE_SUCCESS);

        case BLE_DFU_OP_CODE_CALCULATE_CRC:
            NRF_LOG_DEBUG("Received calculate CRC\r\n");

            dfu_req.req_type =  NRF_DFU_OBJECT_OP_CRC;

            res_code = nrf_dfu_req_handler_on_req(NULL, &dfu_req, &dfu_res);
            if (res_code == NRF_DFU_RES_CODE_SUCCESS)
            {
                return response_crc_cmd_send(p_dfu, dfu_res.offset, dfu_res.crc);
            }
            else
            {
                return response_send(p_dfu, BLE_DFU_OP_CODE_CALCULATE_CRC, res_code);
            }

        case BLE_DFU_OP_CODE_SELECT_OBJECT:

            NRF_LOG_DEBUG("Received select object\r\n");
            if (p_ble_write_evt->len != PKT_READ_OBJECT_INFO_PARAM_LEN)
            {
                return response_send(p_dfu,
                                     BLE_DFU_OP_CODE_SELECT_OBJECT,
                                     NRF_DFU_RES_CODE_INVALID_PARAMETER);
            }

            // Set object type to read info about
            //lint -save -e415
            dfu_req.obj_type = p_ble_write_evt->data[1];
            //lint -restore

            dfu_req.req_type = NRF_DFU_OBJECT_OP_SELECT;

            res_code = nrf_dfu_req_handler_on_req(NULL, &dfu_req, &dfu_res);
            if (res_code == NRF_DFU_RES_CODE_SUCCESS)
            {
                return response_select_object_cmd_send(p_dfu, dfu_res.max_size, dfu_res.offset, dfu_res.crc);
            }
            else
            {
                return response_send(p_dfu, BLE_DFU_OP_CODE_SELECT_OBJECT, res_code);
            }

        default:
            NRF_LOG_WARNING("Received unsupported OP code\r\n");
            // Unsupported op code.
            return response_send(p_dfu,
                                 p_ble_write_evt->data[0],
                                 NRF_DFU_RES_CODE_INVALID_PARAMETER);
    }
}


/**@brief     Function for handling the @ref BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST event from the
 *            SoftDevice.
 *
 * @param[in] p_dfu     DFU Service Structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static bool on_rw_authorize_req(ble_dfu_t * p_dfu, ble_evt_t * p_ble_evt)
{
    uint32_t                                err_code;
    ble_gatts_rw_authorize_reply_params_t   auth_reply = {0};
    ble_gatts_evt_rw_authorize_request_t  * p_authorize_request;
    ble_gatts_evt_write_t                 * p_ble_write_evt;

    p_authorize_request = &(p_ble_evt->evt.gatts_evt.params.authorize_request);
    p_ble_write_evt = &(p_ble_evt->evt.gatts_evt.params.authorize_request.request.write);

    if ((p_authorize_request->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE)                           &&
        (p_authorize_request->request.write.handle == p_dfu->dfu_ctrl_pt_handles.value_handle)  &&
        (p_authorize_request->request.write.op != BLE_GATTS_OP_PREP_WRITE_REQ)                  &&
        (p_authorize_request->request.write.op != BLE_GATTS_OP_EXEC_WRITE_REQ_NOW)              &&
        (p_authorize_request->request.write.op != BLE_GATTS_OP_EXEC_WRITE_REQ_CANCEL)            )
    {
        auth_reply.type = BLE_GATTS_AUTHORIZE_TYPE_WRITE;
        auth_reply.params.write.update = 1;
        auth_reply.params.write.offset = p_ble_write_evt->offset;
        auth_reply.params.write.len = p_ble_write_evt->len;
        auth_reply.params.write.p_data = p_ble_write_evt->data;

        if (!is_cccd_configured(p_dfu))
        {
            // Send an error response to the peer indicating that the CCCD is improperly configured.
            auth_reply.params.write.gatt_status = BLE_GATT_STATUS_ATTERR_CPS_CCCD_CONFIG_ERROR;

            // Ignore response of auth reply
            (void)sd_ble_gatts_rw_authorize_reply(m_conn_handle, &auth_reply);
            return false;
        }

        auth_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;

        err_code = sd_ble_gatts_rw_authorize_reply(m_conn_handle, &auth_reply);
        return err_code  == NRF_SUCCESS ? true: false;
    }
    else
    {
        return false;
    }
}


/**@brief     Function for handling the @ref BLE_GATTS_EVT_WRITE event from the SoftDevice.
 *
 * @param[in] p_dfu     DFU Service Structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static void on_write(ble_dfu_t * p_dfu, ble_evt_t * p_ble_evt)
{
    if (p_ble_evt->evt.gatts_evt.params.write.handle == p_dfu->dfu_pkt_handles.value_handle)
    {
        nrf_dfu_res_code_t  res_code;
        nrf_dfu_req_t       dfu_req;
        nrf_dfu_res_t       dfu_res = {{{0}}};

        memset(&dfu_req, 0, sizeof(nrf_dfu_req_t));

        // Set req type
        dfu_req.req_type =  NRF_DFU_OBJECT_OP_WRITE;

        // Set data and length
        dfu_req.p_req    =  p_ble_evt->evt.gatts_evt.params.write.data;
        dfu_req.req_len  =  p_ble_evt->evt.gatts_evt.params.write.len;

        res_code = nrf_dfu_req_handler_on_req(NULL, &dfu_req, &dfu_res);
        if(res_code != NRF_DFU_RES_CODE_SUCCESS)
        {
            NRF_LOG_ERROR("Failure to run packet write\r\n");
        }

        // Check if a packet receipt notification is needed to be sent.
        if (m_pkt_notif_target != 0 && --m_pkt_notif_target_cnt == 0)
        {
            (void)response_crc_cmd_send(p_dfu, dfu_res.offset, dfu_res.crc);

            // Reset the counter for the number of firmware packets.
            m_pkt_notif_target_cnt = m_pkt_notif_target;
        }
    }
}


/**@brief Function for the Application's SoftDevice event handler.
 *
 * @param[in] p_ble_evt SoftDevice event.
 */
static void on_ble_evt(ble_evt_t * p_ble_evt)
{
    uint32_t err_code;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
            nrf_gpio_pin_clear(CONNECTED_LED_PIN_NO);
            nrf_gpio_pin_set(ADVERTISING_LED_PIN_NO);

            m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            m_flags &= ~DFU_BLE_FLAG_IS_ADVERTISING;
        } break;

        case BLE_GAP_EVT_DISCONNECTED:
        {
            // Restart advertising so that the DFU Controller can reconnect if possible.
            err_code = advertising_start();
            APP_ERROR_CHECK(err_code);

            m_conn_handle = BLE_CONN_HANDLE_INVALID;
        } break;

        case BLE_GATTS_EVT_HVN_TX_COMPLETE:
        {
            nrf_dfu_req_handler_reset_if_dfu_complete();
        } break;

        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
        {
            err_code = sd_ble_gap_sec_params_reply(m_conn_handle,
                                                   BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP,
                                                   NULL,
                                                   NULL);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GATTS_EVT_TIMEOUT:
        {
            if (p_ble_evt->evt.gatts_evt.params.timeout.src == BLE_GATT_TIMEOUT_SRC_PROTOCOL)
            {
                err_code = sd_ble_gap_disconnect(m_conn_handle,
                                                 BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
                APP_ERROR_CHECK(err_code);
            }
        } break;

        case BLE_EVT_USER_MEM_REQUEST:
        {
            err_code = sd_ble_user_mem_reply(m_conn_handle, NULL);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
        {
            if (p_ble_evt->evt.gatts_evt.params.authorize_request.type
                != BLE_GATTS_AUTHORIZE_TYPE_INVALID)
            {
                if (on_rw_authorize_req(&m_dfu, p_ble_evt))
                {
                    err_code = on_ctrl_pt_write(&m_dfu,
                           &(p_ble_evt->evt.gatts_evt.params.authorize_request.request.write));
#ifdef NRF_DFU_DEBUG_VERSION
                    if (err_code != NRF_SUCCESS)
                    {
                        NRF_LOG_ERROR("Could not handle on_ctrl_pt_write. err_code: 0x%04x\r\n", err_code);
                    }
#else
                    // Swallow result
                    (void) err_code;
#endif
                }
            }
        } break;

        case BLE_GAP_EVT_SEC_INFO_REQUEST:
        {
            err_code = sd_ble_gap_sec_info_reply(p_ble_evt->evt.gap_evt.conn_handle, NULL, NULL, NULL);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GATTS_EVT_SYS_ATTR_MISSING:
        {
            err_code = sd_ble_gatts_sys_attr_set(p_ble_evt->evt.gap_evt.conn_handle, NULL, 0, 0);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GATTS_EVT_WRITE:
        {
            on_write(&m_dfu, p_ble_evt);
        } break;

#if (NRF_SD_BLE_API_VERSION >= 3)
        case BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST:
        {
            err_code = sd_ble_gatts_exchange_mtu_reply(p_ble_evt->evt.gatts_evt.conn_handle,
                                                       BLE_GATT_ATT_MTU_DEFAULT);
            APP_ERROR_CHECK(err_code);
        } break; // BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST

        case BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST:
        {
            ble_gap_data_length_params_t const dlp =
            {
                .max_rx_octets = BLE_GAP_DATA_LENGTH_AUTO,
                .max_tx_octets = BLE_GAP_DATA_LENGTH_AUTO,
            };

            err_code = sd_ble_gap_data_length_update(p_ble_evt->evt.gatts_evt.conn_handle,
                                                     &dlp, NULL);
            APP_ERROR_CHECK(err_code);
        } break; // BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST
#endif

        default:
            // No implementation needed.
            break;
    }
}


/**@brief     Function for dispatching a SoftDevice event.
 *
 * @details   This function is called from the SoftDevice event interrupt handler after a
 *            SoftDevice event has been received.
 *
 * @param[in] p_ble_evt SoftDevice event.
 */
static void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{
    ble_conn_params_on_ble_evt(p_ble_evt);
    on_ble_evt(p_ble_evt);
}


/**@brief       Function for the LEDs initialization.
 *
 * @details     Initializes all LEDs used by this application.
 */
static void leds_init(void)
{
    nrf_gpio_cfg_output(ADVERTISING_LED_PIN_NO);
    nrf_gpio_cfg_output(CONNECTED_LED_PIN_NO);
    nrf_gpio_pin_set(ADVERTISING_LED_PIN_NO);
    nrf_gpio_pin_set(CONNECTED_LED_PIN_NO);
}


static uint32_t gap_address_change(void)
{
    uint32_t            err_code;
    ble_gap_addr_t      addr;

#if (NRF_SD_BLE_API_VERSION < 3)
    err_code = sd_ble_gap_address_get(&addr);
#else
    err_code = sd_ble_gap_addr_get(&addr);
#endif

    VERIFY_SUCCESS(err_code);

    // Increase the BLE address by one when advertising openly.
    addr.addr[0] += 1;

#if (NRF_SD_BLE_API_VERSION < 3)
    err_code = sd_ble_gap_address_set(BLE_GAP_ADDR_CYCLE_MODE_NONE, &addr);
#else
    err_code = sd_ble_gap_addr_set(&addr);
#endif

    VERIFY_SUCCESS(err_code);

    return NRF_SUCCESS;
}


/**@brief     Function for the GAP initialization.
 *
 * @details   This function will setup all the necessary GAP (Generic Access Profile) parameters of
 *            the device. It also sets the permissions and appearance.
 */
static uint32_t gap_params_init(void)
{
    uint32_t                err_code;
    ble_gap_conn_params_t   gap_conn_params = {0};
    ble_gap_conn_sec_mode_t sec_mode;

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

    err_code = gap_address_change();
    VERIFY_SUCCESS(err_code);

    err_code = sd_ble_gap_device_name_set(&sec_mode,
                                          (const uint8_t *)DEVICE_NAME,
                                          strlen(DEVICE_NAME));

    VERIFY_SUCCESS(err_code);

    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency     = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;

    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
    return err_code;
}


static uint32_t ble_stack_init(bool init_softdevice)
{
    uint32_t           err_code;
    nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;

    if (init_softdevice)
    {
        err_code = nrf_dfu_mbr_init_sd();
        VERIFY_SUCCESS(err_code);
    }

    NRF_LOG_DEBUG("vector table: 0x%08x\r\n", BOOTLOADER_START_ADDR);
    err_code = sd_softdevice_vector_table_base_set(BOOTLOADER_START_ADDR);
    VERIFY_SUCCESS(err_code);
    NRF_LOG_DEBUG("vector table: 0x%08x\r\n", BOOTLOADER_START_ADDR);

    NRF_LOG_DEBUG("Error code - sd_softdevice_vector_table_base_set: 0x%08x\r\n", err_code);

    NRF_LOG_DEBUG("Before SOFTDEVICE_HANDLER_APPSH_INIT\r\n");
    SOFTDEVICE_HANDLER_APPSH_INIT(&clock_lf_cfg, true);
    NRF_LOG_DEBUG("After SOFTDEVICE_HANDLER_APPSH_INIT\r\n");

    // Fetch the start address of the application RAM.
    uint32_t ram_start = 0;
    err_code = softdevice_app_ram_start_get(&ram_start);
    APP_ERROR_CHECK(err_code);

    // Overwrite some of the default configurations for the BLE stack.
    ble_cfg_t ble_cfg;

    // Configure the maximum number of connections.
    memset(&ble_cfg, 0, sizeof(ble_cfg));
    ble_cfg.gap_cfg.role_count_cfg.periph_role_count  = BLE_GAP_ROLE_COUNT_PERIPH_DEFAULT;
    ble_cfg.gap_cfg.role_count_cfg.central_role_count = 0;
    ble_cfg.gap_cfg.role_count_cfg.central_sec_count  = 0;
    err_code = sd_ble_cfg_set(BLE_GAP_CFG_ROLE_COUNT, &ble_cfg, ram_start);
    APP_ERROR_CHECK(err_code);
    NRF_LOG_INFO("Error code - sd_ble_cfg_set: 0x%08x\r\n", err_code);
    VERIFY_SUCCESS(err_code);

    NRF_LOG_DEBUG("Enabling softdevice.\r\n");
    // Enable BLE stack.
    err_code = softdevice_enable(&ram_start);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("Failed softdevice_enable: 0x%08x\r\n", err_code);
    }
    else
    {
        NRF_LOG_DEBUG("Softdevice enabled\r\n");
    }

    return err_code;
}


/**@brief       Function for adding DFU Packet characteristic to the BLE Stack.
 *
 * @param[in]   p_dfu DFU Service structure.
 *
 * @return      NRF_SUCCESS on success. Otherwise an error code.
 */
static uint32_t dfu_pkt_char_add(ble_dfu_t * const p_dfu)
{
    ble_gatts_char_md_t char_md         = {{0}};
    ble_gatts_attr_t    attr_char_value = {0};
    ble_gatts_attr_md_t attr_md         = {{0}};
    ble_uuid_t          char_uuid;

    char_md.char_props.write_wo_resp = 1;

    char_uuid.type = p_dfu->uuid_type;
    char_uuid.uuid = BLE_DFU_PKT_CHAR_UUID;

    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc    = BLE_GATTS_VLOC_STACK;
    attr_md.vlen    = 1;

    attr_char_value.p_uuid    = &char_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.max_len   = MAX_DFU_PKT_LEN;
    attr_char_value.p_value   = NULL;

    return sd_ble_gatts_characteristic_add(p_dfu->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_dfu->dfu_pkt_handles);
}


/**@brief       Function for adding DFU Control Point characteristic to the BLE Stack.
 *
 * @param[in]   p_dfu DFU Service structure.
 *
 * @return      NRF_SUCCESS on success. Otherwise an error code.
 */
static uint32_t dfu_ctrl_pt_add(ble_dfu_t * const p_dfu)
{
    ble_gatts_char_md_t char_md         = {{0}};
    ble_gatts_attr_t    attr_char_value = {0};
    ble_gatts_attr_md_t attr_md         = {{0}};
    ble_uuid_t          char_uuid;

    char_md.char_props.write  = 1;
    char_md.char_props.notify = 1;

    char_uuid.type = p_dfu->uuid_type;
    char_uuid.uuid = BLE_DFU_CTRL_PT_UUID;

    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc    = BLE_GATTS_VLOC_STACK;
    attr_md.wr_auth = 1;
    attr_md.vlen    = 1;

    attr_char_value.p_uuid    = &char_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.max_len   = BLE_GATT_ATT_MTU_DEFAULT;
    attr_char_value.p_value   = NULL;

    return sd_ble_gatts_characteristic_add(p_dfu->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_dfu->dfu_ctrl_pt_handles);
}


/**@brief     Function for checking if the CCCD of DFU Control point is configured for Notification.
 *
 * @details   This function checks if the CCCD of DFU Control Point characteristic is configured
 *            for Notification by the DFU Controller.
 *
 * @param[in] p_dfu DFU Service structure.
 *
 * @return    True if the CCCD of DFU Control Point characteristic is configured for Notification.
 *            False otherwise.
 */
uint32_t ble_dfu_init(ble_dfu_t * p_dfu)
{
    ble_uuid_t service_uuid;
    uint32_t   err_code;

#ifndef NRF51
    if (p_dfu == NULL)
    {
        return NRF_ERROR_NULL;
    }
#endif

    m_conn_handle = BLE_CONN_HANDLE_INVALID;

    BLE_UUID_BLE_ASSIGN(service_uuid, BLE_DFU_SERVICE_UUID);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &(p_dfu->service_handle));
    VERIFY_SUCCESS(err_code);

    const ble_uuid128_t base_uuid128 =
    {
        {
            0x50, 0xEA, 0xDA, 0x30, 0x88, 0x83, 0xB8, 0x9F,
            0x60, 0x4F, 0x15, 0xF3,  0x00, 0x00, 0xC9, 0x8E
        }
    };
    err_code = sd_ble_uuid_vs_add(&base_uuid128, &p_dfu->uuid_type);
    VERIFY_SUCCESS(err_code);

    err_code = dfu_pkt_char_add(p_dfu);
    VERIFY_SUCCESS(err_code);

    err_code = dfu_ctrl_pt_add(p_dfu);
    VERIFY_SUCCESS(err_code);

    m_flags |= DFU_BLE_FLAG_SERVICE_INITIALIZED;

    return NRF_SUCCESS;
}


uint32_t ble_dfu_transport_init(void)
{
    uint32_t err_code;

    m_flags &= ~DFU_BLE_FLAG_NONE;

    leds_init();

    err_code = ble_stack_init(true);
    VERIFY_SUCCESS(err_code);

    err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
    VERIFY_SUCCESS(err_code);

    err_code = gap_params_init();
    VERIFY_SUCCESS(err_code);

    // Initialize the Device Firmware Update Service.
    err_code = ble_dfu_init(&m_dfu);
    VERIFY_SUCCESS(err_code);

    err_code = conn_params_init();
    VERIFY_SUCCESS(err_code);

    err_code = advertising_start();
    VERIFY_SUCCESS(err_code);

    return NRF_SUCCESS;
}


uint32_t ble_dfu_transport_close(void)
{
    uint32_t err_code = NRF_SUCCESS;

    NRF_LOG_DEBUG("Disconnecting\r\n");

    if (m_conn_handle != BLE_CONN_HANDLE_INVALID)
    {
        // Disconnect from peer.
        err_code = sd_ble_gap_disconnect(m_conn_handle, BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
        VERIFY_SUCCESS(err_code);
    }
    else if ((m_flags & DFU_BLE_FLAG_IS_ADVERTISING) != 0)
    {
        // If not connected, then the device will be advertising. Hence stop the advertising.
        err_code = advertising_stop();
        VERIFY_SUCCESS(err_code);
    }

    // Stop the timer, disregard the result.
    (void)ble_conn_params_stop();
    return err_code;
}
