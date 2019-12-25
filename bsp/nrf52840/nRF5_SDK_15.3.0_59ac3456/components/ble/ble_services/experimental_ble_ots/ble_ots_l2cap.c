/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#include "ble_ots_l2cap.h"

#include <string.h>
#include "ble_l2cap.h"

#include "ble_ots.h"
#include "ble_ots_oacp.h"

#define NRF_LOG_MODULE_NAME ble_ots_l2cap
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define SDU_SIZE 1024


static uint8_t data[SDU_SIZE];
static ble_data_t m_sdu_buf =
{
    .p_data = data,
    .len    = SDU_SIZE
};

bool ble_ots_l2cap_is_channel_available(ble_ots_l2cap_t * p_ots_l2cap)
{
    return p_ots_l2cap->state == CONNECTED;
}

uint32_t ble_ots_l2cap_abort_transmission(ble_ots_l2cap_t * p_ots_l2cap)
{
    if (p_ots_l2cap == NULL)
    {
        return NRF_ERROR_NULL;
    }
    return NRF_ERROR_INVALID_PARAM;
}

uint32_t ble_ots_l2cap_init(ble_ots_l2cap_t * p_ots_l2cap, ble_ots_l2cap_init_t * p_ots_l2cap_init)
{
    if (p_ots_l2cap == NULL || p_ots_l2cap_init == NULL)
    {
        return NRF_ERROR_NULL;
    }
    if (p_ots_l2cap_init->p_transfer_buffer == NULL || p_ots_l2cap_init->buffer_len == 0)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    if (p_ots_l2cap_init->p_ots_oacp == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    if (p_ots_l2cap_init->evt_handler == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    memset(p_ots_l2cap, 0, sizeof(ble_ots_l2cap_t));

    p_ots_l2cap->local_cid  = BLE_OTS_INVALID_CID;

    p_ots_l2cap->p_ots_oacp               = p_ots_l2cap_init->p_ots_oacp;
    p_ots_l2cap->evt_handler              = p_ots_l2cap_init->evt_handler;
    p_ots_l2cap->rx_params.sdu_buf.len    = m_sdu_buf.len;
    p_ots_l2cap->rx_params.sdu_buf.p_data = m_sdu_buf.p_data;

    p_ots_l2cap->state = NOT_CONNECTED;

    return NRF_SUCCESS;
}

/**@brief This function receives the next MTU of the object.
 *
 * @param[in] p_ots_l2cap Object Transfer Service structure.
 */
static void receive_resume(ble_ots_l2cap_t * p_ots_l2cap)
{
    ret_code_t err_code;
    ble_data_t sdu_buf;

    sdu_buf.p_data = &p_ots_l2cap->rx_params.sdu_buf.p_data[p_ots_l2cap->received_bytes];
    sdu_buf.len    = p_ots_l2cap->rx_params.sdu_buf.len - p_ots_l2cap->received_bytes;

    err_code = sd_ble_l2cap_ch_rx(p_ots_l2cap->p_ots_oacp->p_ots->conn_handle,
                                  p_ots_l2cap->local_cid,
                                  &sdu_buf);

    if (err_code == NRF_ERROR_RESOURCES)
    {
        return; // Too many SDUs queued for transmission, the transmission will be tried again on the next BLE_L2CAP_EVT_CH_RX event.
    }

    if (err_code != NRF_SUCCESS && p_ots_l2cap->p_ots_oacp->p_ots->error_handler != NULL)
    {
            p_ots_l2cap->p_ots_oacp->p_ots->error_handler(err_code);
    }
}

/**@brief This function sends the next MTU of the object.
 *
 * @param[in] p_ots_l2cap Object Transfer Service structure.
 */
static void send_resume(ble_ots_l2cap_t * p_ots_l2cap)
{
    ret_code_t err_code;
    uint16_t   tx_size;

    tx_size = MIN(p_ots_l2cap->transfer_len - p_ots_l2cap->transmitted_bytes,
                  p_ots_l2cap->tx_params.tx_mtu);

    ble_data_t obj;
    obj.p_data = &p_ots_l2cap->tx_transfer_buffer.p_data[p_ots_l2cap->transmitted_bytes];
    obj.len    = tx_size;

    err_code = sd_ble_l2cap_ch_tx(p_ots_l2cap->p_ots_oacp->p_ots->conn_handle,
                                  p_ots_l2cap->local_cid,
                                  &obj);
    if (err_code == NRF_ERROR_RESOURCES)
    {
        return; // Too many SDUs queued for transmission, the transmission will be tried again on the next BLE_L2CAP_EVT_CH_TX event.
    }

    if (err_code != NRF_SUCCESS && p_ots_l2cap->p_ots_oacp->p_ots->error_handler != NULL)
    {
            p_ots_l2cap->p_ots_oacp->p_ots->error_handler(err_code);
    }
}


uint32_t ble_ots_l2cap_obj_send(ble_ots_l2cap_t * p_ots_l2cap, uint8_t * p_data, uint16_t data_len)
{
    if (p_ots_l2cap == NULL)
    {
        return NRF_ERROR_NULL;
    }
    if (p_data == NULL)
    {
        return NRF_ERROR_NULL;
    }
    if (data_len == 0)
    {
        return NRF_ERROR_INVALID_LENGTH;
    }
    if (p_ots_l2cap->local_cid == BLE_L2CAP_CID_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    if (p_ots_l2cap->state != CONNECTED)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    p_ots_l2cap->tx_transfer_buffer.p_data = p_data;
    p_ots_l2cap->tx_transfer_buffer.len    = data_len;

    p_ots_l2cap->transmitted_bytes = 0;
    p_ots_l2cap->transfer_len      = data_len;

    p_ots_l2cap->state = SENDING;

    send_resume(p_ots_l2cap);

    return NRF_SUCCESS;
}

uint32_t ble_ots_l2cap_start_recv(ble_ots_l2cap_t * p_ots_l2cap, uint16_t len)
{
    uint32_t err_code;

    if (p_ots_l2cap == NULL)
    {
        return NRF_ERROR_NULL;
    }
    if (p_ots_l2cap->state != CONNECTED)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    if (p_ots_l2cap->local_cid == BLE_L2CAP_CID_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    p_ots_l2cap->received_bytes  = 0;
    p_ots_l2cap->transfer_len    = len;

    err_code = sd_ble_l2cap_ch_rx(p_ots_l2cap->p_ots_oacp->p_ots->conn_handle,
                                  p_ots_l2cap->local_cid,
                                  &p_ots_l2cap->rx_params.sdu_buf);
    if (err_code == NRF_SUCCESS)
    {
        p_ots_l2cap->state = RECEIVING;
    }

    return err_code;
}

/**@brief This function is called on a channel setup request. It responds with the connection parameters.
 * @param[in]   p_ots_l2cap Object transfer service l2cap module structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static inline void on_l2cap_ch_setup_request(ble_ots_l2cap_t * p_ots_l2cap, ble_evt_t const * p_ble_evt)
{
    uint32_t                    err_code;
    ble_l2cap_ch_setup_params_t ch_setup_params = {{0}};

    if (p_ble_evt->evt.l2cap_evt.params.ch_setup_request.le_psm != BLE_OTS_PSM)
    {
        ch_setup_params.status = BLE_L2CAP_CH_STATUS_CODE_LE_PSM_NOT_SUPPORTED;
        NRF_LOG_WARNING("l2cap setup request for PSM 0x%x, rejecting since OTS PSM is 0x%x",
                        p_ble_evt->evt.l2cap_evt.params.ch_setup_request.le_psm,
                        BLE_L2CAP_CH_STATUS_CODE_LE_PSM_NOT_SUPPORTED);
    }

    else
    {
        ch_setup_params.status = BLE_L2CAP_CH_STATUS_CODE_SUCCESS;

        ch_setup_params.rx_params.rx_mps = p_ots_l2cap->conn_mps;
        if (ch_setup_params.rx_params.rx_mps < BLE_L2CAP_MPS_MIN)
        {
            ch_setup_params.rx_params.rx_mps = BLE_L2CAP_MPS_MIN;
        }
        ch_setup_params.rx_params.rx_mtu = p_ots_l2cap->conn_mtu;
        if (ch_setup_params.rx_params.rx_mtu < BLE_L2CAP_MTU_MIN)
        {
            ch_setup_params.rx_params.rx_mtu = BLE_L2CAP_MTU_MIN;
        }
        ch_setup_params.rx_params.sdu_buf.p_data = NULL;
    }

    p_ots_l2cap->local_cid = p_ble_evt->evt.l2cap_evt.local_cid;

    err_code = sd_ble_l2cap_ch_setup(p_ots_l2cap->p_ots_oacp->p_ots->conn_handle,
                                     &p_ots_l2cap->local_cid,
                                     &ch_setup_params);
    if (err_code != NRF_SUCCESS)
    {
        if (p_ots_l2cap->p_ots_oacp->p_ots->error_handler != NULL)
        {
            p_ots_l2cap->p_ots_oacp->p_ots->error_handler(err_code);
        }
    }
    NRF_LOG_INFO("Accepted L2CAP Channel");
}


/**@brief This function is called on a channel setup request. The parameters are stored. Events are forwarded.
 *
 * @param[in]   p_ots_l2cap Object transfer service l2cap module structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static inline void on_l2cap_ch_setup(ble_ots_l2cap_t * p_ots_l2cap, ble_evt_t const * p_ble_evt)
{
    p_ots_l2cap->local_cid         = p_ble_evt->evt.l2cap_evt.local_cid;
    p_ots_l2cap->tx_params.credits = p_ble_evt->evt.l2cap_evt.params.ch_setup.tx_params.credits;
    p_ots_l2cap->tx_params.tx_mps  = p_ble_evt->evt.l2cap_evt.params.ch_setup.tx_params.tx_mps;
    p_ots_l2cap->tx_params.tx_mtu  = p_ble_evt->evt.l2cap_evt.params.ch_setup.tx_params.tx_mtu;
    ble_ots_l2cap_evt_t evt;

    evt.type = BLE_OTS_L2CAP_EVT_CH_CONNECTED;

    p_ots_l2cap->state = CONNECTED;
    p_ots_l2cap->evt_handler(p_ots_l2cap, &evt);
}


/**@brief Function for handling the BLE_L2CAP_EVT_CH_RELEASED event.
 *
 * @param[in] p_ots_l2cap Object transfer service l2cap module structure.
 * @param[in] p_ble_evt   Pointer to the event received from BLE stack.
 */
static inline void on_l2cap_ch_released(ble_ots_l2cap_t * p_ots_l2cap, ble_evt_t const * p_ble_evt)
{
    if(p_ots_l2cap->local_cid != p_ble_evt->evt.l2cap_evt.local_cid)
    {
        return;
    }
    ble_ots_l2cap_evt_t evt;

    evt.type = BLE_OTS_L2CAP_EVT_CH_DISCONNECTED;

    p_ots_l2cap->evt_handler(p_ots_l2cap, &evt);

    p_ots_l2cap->state = NOT_CONNECTED;

    p_ots_l2cap->local_cid = BLE_OTS_INVALID_CID;

}


/**@brief Function for handling the BLE_L2CAP_EVT_CH_TX event.
 *
 * @param[in] p_ots_l2cap Object transfer service l2cap module structure.
 * @param[in] p_ble_evt   Pointer to the event received from BLE stack.
 */
static void on_l2cap_ch_tx(ble_ots_l2cap_t * p_ots_l2cap, ble_evt_t const * p_ble_evt)
{
    if(p_ots_l2cap->local_cid != p_ble_evt->evt.l2cap_evt.local_cid)
    {
        return;
    }

    NRF_LOG_DEBUG("Bytes sent in the previous PDU: %i",
                  p_ble_evt->evt.l2cap_evt.params.tx.sdu_buf.len);
    NRF_LOG_HEXDUMP_DEBUG(p_ble_evt->evt.l2cap_evt.params.tx.sdu_buf.p_data,
                          p_ble_evt->evt.l2cap_evt.params.tx.sdu_buf.len);

    p_ots_l2cap->transmitted_bytes += p_ble_evt->evt.l2cap_evt.params.tx.sdu_buf.len;
    uint16_t remaining_tx_bytes = p_ots_l2cap->tx_transfer_buffer.len - p_ots_l2cap->transmitted_bytes;

    NRF_LOG_DEBUG("Total bytes transmitted: %i ",
                  (p_ots_l2cap->transmitted_bytes));
    NRF_LOG_DEBUG("Total bytes remaining: %i",
                  (remaining_tx_bytes));

    if (remaining_tx_bytes == 0)
    {
        ble_ots_l2cap_evt_t evt;

        evt.type = BLE_OTS_L2CAP_EVT_SEND_COMPLETE;
        evt.param.len = p_ots_l2cap->transfer_len;
        evt.param.p_data = p_ots_l2cap->tx_transfer_buffer.p_data;
        evt.param.len = p_ots_l2cap->tx_transfer_buffer.len;

        p_ots_l2cap->evt_handler(p_ots_l2cap, &evt);

        p_ots_l2cap->state = CONNECTED;

        p_ots_l2cap->transfer_len = 0;
    }
    else
    {
        send_resume(p_ots_l2cap);
    }
}


static void on_l2cap_ch_rx(ble_ots_l2cap_t * p_ots_l2cap, ble_evt_t const * p_ble_evt)
{
    if(p_ots_l2cap->local_cid != p_ble_evt->evt.l2cap_evt.local_cid)
    {
        return;
    }

    NRF_LOG_DEBUG("Bytes received: %i", p_ble_evt->evt.l2cap_evt.params.rx.sdu_len);
    NRF_LOG_HEXDUMP_DEBUG(p_ble_evt->evt.l2cap_evt.params.rx.sdu_buf.p_data,
                          p_ble_evt->evt.l2cap_evt.params.rx.sdu_len);

    ble_ots_l2cap_evt_t evt;

    memcpy(&p_ots_l2cap->p_ots_oacp->p_ots->p_current_object->data[p_ots_l2cap->received_bytes],
           p_ble_evt->evt.l2cap_evt.params.rx.sdu_buf.p_data,
           p_ble_evt->evt.l2cap_evt.params.rx.sdu_len);

    p_ots_l2cap->received_bytes += p_ble_evt->evt.l2cap_evt.params.rx.sdu_len;

    uint16_t remaining_bytes = (p_ots_l2cap->transfer_len - p_ots_l2cap->received_bytes);

    NRF_LOG_DEBUG("Remaining bytes to receive: %i", remaining_bytes);

    if(remaining_bytes == 0)
    {
        evt.type         = BLE_OTS_L2CAP_EVT_RECV_COMPLETE;
        evt.param.len    = p_ots_l2cap->rx_params.sdu_buf.len;
        evt.param.p_data = p_ots_l2cap->rx_params.sdu_buf.p_data;
        p_ots_l2cap->evt_handler(p_ots_l2cap, &evt);
        p_ots_l2cap->state = CONNECTED;
        p_ots_l2cap->transfer_len = 0;
    }
    else
    {
        receive_resume(p_ots_l2cap);
    }
}



void ble_ots_l2cap_on_ble_evt(ble_ots_l2cap_t * p_ots_l2cap, ble_evt_t const * p_ble_evt)
{
    if ((p_ots_l2cap == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_L2CAP_EVT_CH_SETUP_REQUEST:
            on_l2cap_ch_setup_request(p_ots_l2cap, p_ble_evt);
            break;

        case BLE_L2CAP_EVT_CH_SETUP_REFUSED:
            // This should not happen because the client should be the initiator.
            if (p_ots_l2cap->p_ots_oacp->p_ots->error_handler != NULL)
            {
                p_ots_l2cap->p_ots_oacp->p_ots->error_handler(NRF_ERROR_INVALID_STATE);
            }
            break;

        case BLE_L2CAP_EVT_CH_SETUP:
            on_l2cap_ch_setup(p_ots_l2cap, p_ble_evt);
            break;

        case BLE_L2CAP_EVT_CH_RELEASED:
            on_l2cap_ch_released(p_ots_l2cap, p_ble_evt);
            break;

        case BLE_L2CAP_EVT_CH_SDU_BUF_RELEASED:
            break;

        case BLE_L2CAP_EVT_CH_CREDIT:
            break;

        case BLE_L2CAP_EVT_CH_RX:
            on_l2cap_ch_rx(p_ots_l2cap, p_ble_evt);
            break;

        case BLE_L2CAP_EVT_CH_TX:
            on_l2cap_ch_tx(p_ots_l2cap, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}
