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
*  To maintain compliance with Nordic Semiconductor ASA's Bluetooth profile
*  qualification listings, this section of source code must not be modified.
*/

#include "ble_dfu.h"
#include "nrf_log.h"
#include <string.h>
#include "ble_hci.h"
#include "sdk_macros.h"
#include "ble_srv_common.h"
#include "nrf_nvic.h"
#include "nrf_sdm.h"
#include "nrf_soc.h"
#include "nrf_log.h"

#define MAX_CTRL_POINT_RESP_PARAM_LEN   3
#define IRQ_ENABLED                     0x01                        /**< Field that identifies if an interrupt is enabled. */
#define MAX_NUMBER_INTERRUPTS           32                          /**< Maximum number of interrupts available. */
#define BOOTLOADER_DFU_START            0xB1

#define BLE_DFU_SERVICE_UUID            0xFE59                      //!< The 16-bit UUID of the Secure DFU Service.

/**@brief Function for disabling all interrupts before jumping from bootloader to application.
 */
static void interrupts_disable(void)
{
    uint32_t interrupt_setting_mask;
    uint32_t irq;

    // Fetch the current interrupt settings.
    interrupt_setting_mask = NVIC->ISER[0];

    // Loop from interrupt 0 for disabling of all interrupts.
    for (irq = 0; irq < MAX_NUMBER_INTERRUPTS; irq++)
    {
        if (interrupt_setting_mask & (IRQ_ENABLED << irq))
        {
            // The interrupt was enabled, hence disable it.
            NVIC_DisableIRQ((IRQn_Type)irq);
        }
    }
}

/**@brief Function for preparing the reset, disabling SoftDevice, and jumping to the bootloader.
 *
 */
static uint32_t bootloader_start(void)
{
    uint32_t err_code;

    err_code = sd_power_gpregret_clr(0, 0xffffffff);
    VERIFY_SUCCESS(err_code);

    err_code = sd_power_gpregret_set(0, BOOTLOADER_DFU_START);
    VERIFY_SUCCESS(err_code);

    err_code = sd_softdevice_disable();
    VERIFY_SUCCESS(err_code);

    err_code = sd_softdevice_vector_table_base_set(NRF_UICR->NRFFW[0]);
    VERIFY_SUCCESS(err_code);

    NVIC_ClearPendingIRQ(SWI2_IRQn);
    interrupts_disable();

    NVIC_SystemReset();
    return NRF_SUCCESS;
}

static void enter_bootloader(ble_dfu_t * p_dfu)
{
    if (p_dfu->evt_handler != NULL)
    {
        ble_dfu_evt_t evt;

        evt.type = BLE_DFU_EVT_ENTERING_BOOTLOADER;

        p_dfu->evt_handler(p_dfu, &evt);
    }

    // Set the flag to indicate that the device will be reset when we have
    // received hvc confirmation on indication
    p_dfu->is_waiting_for_reset = true;
}


/**@brief Function for adding RX characteristic.
 *
 * @param[in] p_dfu       Nordic DFU Service structure.
 * @param[in] p_dfu_init  Information needed to initialize the service.
 *
 * @return NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t buttonless_char_pt_add(ble_dfu_t * p_dfu, const ble_dfu_init_t * p_dfu_init)
{
    ble_gatts_char_md_t char_md         = {{0}};
    ble_gatts_attr_md_t cccd_md         = {{0}};
    ble_gatts_attr_t    attr_char_value = {0};
    ble_gatts_attr_md_t attr_md         = {{0}};
    ble_uuid_t          char_uuid;


    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);

    cccd_md.vloc = BLE_GATTS_VLOC_STACK;

    char_md.char_props.indicate = 1;
    char_md.char_props.write  = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = &cccd_md;
    char_md.p_sccd_md         = NULL;

    char_uuid.type = p_dfu->uuid_type;
    char_uuid.uuid = BLE_DFU_BUTTONLESS_CHAR_UUID;

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc    = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth = 0;
    attr_md.wr_auth = 1;
    attr_md.vlen    = 1;

    attr_char_value.p_uuid    = &char_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = 0;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = BLE_GATT_ATT_MTU_DEFAULT;
    attr_char_value.p_value   = 0;

    return sd_ble_gatts_characteristic_add(p_dfu->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_dfu->control_point_char);
}



uint32_t ble_dfu_init(ble_dfu_t * p_dfu, const ble_dfu_init_t * p_dfu_init)
{
    uint32_t        err_code;
    ble_uuid_t      service_uuid;
    ble_uuid128_t   nordic_base_uuid = BLE_NORDIC_VENDOR_BASE_UUID;

    VERIFY_PARAM_NOT_NULL(p_dfu);
    VERIFY_PARAM_NOT_NULL(p_dfu_init);

    // Initialize the service structure.
    p_dfu->conn_handle                  = BLE_CONN_HANDLE_INVALID;
    p_dfu->evt_handler                  = p_dfu_init->evt_handler;
    p_dfu->is_waiting_for_reset         = false;
    p_dfu->is_ctrlpt_indication_enabled = false;


    BLE_UUID_BLE_ASSIGN(service_uuid, BLE_DFU_SERVICE_UUID);

    // Add proprietary service
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &(p_dfu->service_handle));

    VERIFY_SUCCESS(err_code);

    // Add vendor specific UUID to use with the Buttonless DFU characteristic
    err_code = sd_ble_uuid_vs_add(&nordic_base_uuid, &p_dfu->uuid_type);
    VERIFY_SUCCESS(err_code);

    // Add the Buttonless DFU Characteristic.
    err_code = buttonless_char_pt_add(p_dfu, p_dfu_init);
    VERIFY_SUCCESS(err_code);

    return NRF_SUCCESS;
}

static void resp_send(ble_dfu_t * p_dfu, ble_dfu_buttonless_op_code_t op_code, ble_dfu_rsp_code_t rsp_code)
{
    // Send notification
    uint16_t               hvx_len;
    uint8_t                hvx_data[MAX_CTRL_POINT_RESP_PARAM_LEN];
    ble_gatts_hvx_params_t hvx_params;

    memset(&hvx_params, 0, sizeof(hvx_params));

    hvx_len = 3;
    hvx_data[0] = DFU_OP_RESPONSE_CODE;
    hvx_data[1] = (uint8_t)op_code;
    hvx_data[2] = (uint8_t)rsp_code;

    hvx_params.handle   = p_dfu->control_point_char.value_handle;
    hvx_params.type     = BLE_GATT_HVX_INDICATION;
    hvx_params.offset   = 0;
    hvx_params.p_len    = &hvx_len;
    hvx_params.p_data   = hvx_data;

    (void)sd_ble_gatts_hvx(p_dfu->conn_handle, &hvx_params);
}



/**@brief Handle write events to the Location and Navigation Service Control Point characteristic.
 *
 * @param[in]   p_dfu         DFU Service structure.
 * @param[in]   p_evt_write   Write event received from the BLE stack.
 */
static void on_ctrlpt_write(ble_dfu_t * p_dfu, ble_gatts_evt_write_t const * p_evt_write)
{
    uint32_t      err_code;
    ble_dfu_rsp_code_t rsp_code = DFU_RSP_OPERATION_FAILED;

    ble_gatts_rw_authorize_reply_params_t write_authorize_reply;
    memset(&write_authorize_reply, 0, sizeof(write_authorize_reply));

    write_authorize_reply.type   = BLE_GATTS_AUTHORIZE_TYPE_WRITE;

    if (p_dfu->is_ctrlpt_indication_enabled)
    {
        write_authorize_reply.params.write.update      = 1;
        write_authorize_reply.params.write.gatt_status = BLE_GATT_STATUS_SUCCESS;
    }
    else
    {
        write_authorize_reply.params.write.gatt_status = DFU_RSP_CCCD_CONFIG_IMPROPER;
    }

    // reply to the write authorization
    do {
        err_code = sd_ble_gatts_rw_authorize_reply(p_dfu->conn_handle, &write_authorize_reply);
    } while (err_code == NRF_ERROR_BUSY);


    if (write_authorize_reply.params.write.gatt_status != BLE_GATT_STATUS_SUCCESS)
    {
        return;
    }

    // Start executing the control point write action
    NRF_LOG_INFO("on_ctrlpt_write: execute enter\r\n");
    switch (p_evt_write->data[0])
    {
        case BLE_DFU_ENTER_BOOTLOADER:
            NRF_LOG_DEBUG("on_ctrlpt_write: execuing!!\r\n");
            rsp_code = DFU_RSP_SUCCESS;
            break;

         // Unrecognized Op Code
        default:
            rsp_code = DFU_RSP_OP_CODE_NOT_SUPPORTED;
            break;
    }

    resp_send(p_dfu, (ble_dfu_buttonless_op_code_t)p_evt_write->data[0], rsp_code);

    if (rsp_code == DFU_RSP_SUCCESS
        && p_evt_write->data[0] == BLE_DFU_ENTER_BOOTLOADER)
    {
        enter_bootloader(p_dfu);
    }
}


/**@brief Write authorization request event handler.
 *
 * @details The write authorization request event handler is called when writing to the control point.
 *
 * @param[in]   p_dfu     DFU structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_rw_authorize_req(ble_dfu_t * p_dfu, ble_evt_t const * p_ble_evt)
{
    if (p_ble_evt->evt.gatts_evt.conn_handle != p_dfu->conn_handle)
    {
        return;
    }

    const ble_gatts_evt_rw_authorize_request_t * p_auth_req =
        &p_ble_evt->evt.gatts_evt.params.authorize_request;

    if (
        (p_auth_req->type == BLE_GATTS_AUTHORIZE_TYPE_WRITE)
        &&
        (p_auth_req->request.write.handle == p_dfu->control_point_char.value_handle)
        &&
        (p_auth_req->request.write.op != BLE_GATTS_OP_PREP_WRITE_REQ)
        &&
        (p_auth_req->request.write.op != BLE_GATTS_OP_EXEC_WRITE_REQ_NOW)
        &&
        (p_auth_req->request.write.op != BLE_GATTS_OP_EXEC_WRITE_REQ_CANCEL)
       )
    {
        on_ctrlpt_write(p_dfu, &p_auth_req->request.write);
    }
}

/**@brief Connect event handler.
 *
 * @param[in]   p_dfu       DFU Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_dfu_t * p_dfu, ble_evt_t const * p_ble_evt)
{
    p_dfu->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}


/**@brief Disconnect event handler.
 *
 * @param[in]   p_dfu      DFU Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_dfu_t * p_dfu, ble_evt_t const * p_ble_evt)
{
    if (p_dfu->conn_handle != p_ble_evt->evt.gatts_evt.conn_handle)
    {
        return;
    }

    p_dfu->conn_handle = BLE_CONN_HANDLE_INVALID;
}

/**@brief Write event handler.
 *
 * @param[in]   p_dfu     DFU Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.rtt
 */
static void on_write(ble_dfu_t * p_dfu, ble_evt_t const * p_ble_evt)
{
    const ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if (p_evt_write->handle != p_dfu->control_point_char.cccd_handle)
    {
        return;
    }

    if (p_evt_write->len == BLE_CCCD_VALUE_LEN)
    {
        // CCCD written, update indications state
        p_dfu->is_ctrlpt_indication_enabled = ble_srv_is_indication_enabled(p_evt_write->data);

        NRF_LOG_INFO("Received indication state %d, notification state %d\r\n", p_dfu->is_ctrlpt_indication_enabled, ble_srv_is_notification_enabled(p_evt_write->data));

        if (p_dfu->evt_handler != NULL)
        {
            ble_dfu_evt_t evt;

            if (p_dfu->is_ctrlpt_indication_enabled)
            {
                evt.type = BLE_DFU_EVT_INDICATION_ENABLED;
            }
            else
            {
                evt.type = BLE_DFU_EVT_INDICATION_DISABLED;
            }

            p_dfu->evt_handler(p_dfu, &evt);
        }
    }
}


/**@brief Function for handling the HVC event.
 *
 * @details Handles HVC events from the BLE stack.
 *
 * @param[in] p_dfu      DFU Service structure.
 * @param[in] p_ble_evt  Event received from the BLE stack.
 */
static void on_hvc(ble_dfu_t * p_dfu, ble_evt_t * p_ble_evt)
{
    ble_gatts_evt_hvc_t * p_hvc = &p_ble_evt->evt.gatts_evt.params.hvc;

    if (p_hvc->handle == p_dfu->control_point_char.value_handle)
    {
        // Enter bootloader if we were waiting for reset after hvc indication confimation.
        if (p_dfu->is_waiting_for_reset)
        {
            (void)bootloader_start();
        }
    }
}


void ble_dfu_on_ble_evt(ble_dfu_t * p_dfu, ble_evt_t * p_ble_evt)
{
    VERIFY_PARAM_NOT_NULL_VOID(p_dfu);
    VERIFY_PARAM_NOT_NULL_VOID(p_ble_evt);

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_dfu, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_dfu, p_ble_evt);
            break;

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            on_rw_authorize_req(p_dfu, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_dfu, p_ble_evt);
            break;

        case BLE_GATTS_EVT_HVC:
            on_hvc(p_dfu, p_ble_evt);
            break;

        default:
            // no implementation
            break;
    }

}
