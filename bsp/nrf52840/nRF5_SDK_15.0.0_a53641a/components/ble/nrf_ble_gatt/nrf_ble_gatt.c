/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_BLE_GATT)

#include "nrf_ble_gatt.h"

#define NRF_LOG_MODULE_NAME nrf_ble_gatt
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#include "nrf_strerror.h"

#define BLE_GAP_DATA_LENGTH_DEFAULT     27          //!< The stack's default data length.
#define BLE_GAP_DATA_LENGTH_MAX         251         //!< Maximum data length.


STATIC_ASSERT(NRF_SDH_BLE_GAP_DATA_LENGTH < 252);


/**@brief Initialize a link's parameters to defaults. */
static void link_init(nrf_ble_gatt_link_t * p_link)
{
    p_link->att_mtu_desired            = NRF_SDH_BLE_GATT_MAX_MTU_SIZE;
    p_link->att_mtu_effective          = BLE_GATT_ATT_MTU_DEFAULT;
    p_link->att_mtu_exchange_pending   = false;
    p_link->att_mtu_exchange_requested = false;
#if !defined (S112)
    p_link->data_length_desired        = NRF_SDH_BLE_GAP_DATA_LENGTH;
    p_link->data_length_effective      = BLE_GAP_DATA_LENGTH_DEFAULT;
#endif // !defined (S112)
}

/**@brief   Start a data length update request procedure on a given connection. */
#if !defined (S112)
static ret_code_t data_length_update(uint16_t conn_handle, uint16_t data_length)
{
    NRF_LOG_DEBUG("Updating data length to %u on connection 0x%x.",
                  data_length, conn_handle);

    ble_gap_data_length_params_t const dlp =
    {
        .max_rx_octets  = data_length,
        .max_tx_octets  = data_length,
        .max_rx_time_us = BLE_GAP_DATA_LENGTH_AUTO,
        .max_tx_time_us = BLE_GAP_DATA_LENGTH_AUTO,
    };

    ble_gap_data_length_limitation_t dll = {0};

    ret_code_t err_code = sd_ble_gap_data_length_update(conn_handle, &dlp, &dll);
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("sd_ble_gap_data_length_update() (request) on connection 0x%x returned %s.",
                      conn_handle, nrf_strerror_get(err_code));

        if (   (dll.tx_payload_limited_octets != 0)
            || (dll.rx_payload_limited_octets != 0))
        {
            NRF_LOG_ERROR("The requested TX/RX packet length is too long by %u/%u octets.",
                          dll.tx_payload_limited_octets, dll.rx_payload_limited_octets);
        }

        if (dll.tx_rx_time_limited_us != 0)
        {
            NRF_LOG_ERROR("The requested combination of TX and RX packet lengths "
                          "is too long by %u microseconds.",
                          dll.tx_rx_time_limited_us);
        }
    }

    return err_code;
}
#endif // !defined (S112)


/**@brief Handle a connected event.
 *
 * Begins an ATT MTU exchange procedure, followed by a data length update request as necessary.
 *
 * @param[in]   p_gatt      GATT structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connected_evt(nrf_ble_gatt_t * p_gatt, ble_evt_t const * p_ble_evt)
{
    ret_code_t            err_code;
    uint16_t              conn_handle = p_ble_evt->evt.common_evt.conn_handle;
    nrf_ble_gatt_link_t * p_link      = &p_gatt->links[conn_handle];

    // Update the link desired settings to reflect the current global settings.
#if !defined (S112)
    p_link->data_length_desired = p_gatt->data_length;
#endif // !defined (S112)

    switch (p_ble_evt->evt.gap_evt.params.connected.role)
    {
        case BLE_GAP_ROLE_PERIPH:
            p_link->att_mtu_desired = p_gatt->att_mtu_desired_periph;
            break;

#if !defined (S112)
        case BLE_GAP_ROLE_CENTRAL:
            p_link->att_mtu_desired = p_gatt->att_mtu_desired_central;
            break;
#endif // !defined (S112)

        default:
            // Ignore.
            break;
    }

    // Begin an ATT MTU exchange if necessary.
    if (p_link->att_mtu_desired > p_link->att_mtu_effective)
    {
        NRF_LOG_DEBUG("Requesting to update ATT MTU to %u bytes on connection 0x%x.",
                      p_link->att_mtu_desired, conn_handle);

        err_code = sd_ble_gattc_exchange_mtu_request(conn_handle, p_link->att_mtu_desired);

        if (err_code == NRF_SUCCESS)
        {
            p_link->att_mtu_exchange_requested = true;
        }
        else if (err_code == NRF_ERROR_BUSY)
        {
            p_link->att_mtu_exchange_pending = true;
            NRF_LOG_DEBUG("sd_ble_gattc_exchange_mtu_request()"
                          " on connection 0x%x returned busy, will retry.", conn_handle);
        }
        else
        {
            NRF_LOG_ERROR("sd_ble_gattc_exchange_mtu_request() returned %s.",
                          nrf_strerror_get(err_code));
        }
    }

#if !defined (S112)
    // Send a data length update request if necessary.
    if (p_link->data_length_desired > p_link->data_length_effective)
    {
        (void) data_length_update(conn_handle, p_link->data_length_desired);
    }
#endif // !defined (S112)
}


static void on_disconnected_evt(nrf_ble_gatt_t * p_gatt, ble_evt_t const * p_ble_evt)
{
    // Reset connection parameters.
    link_init(&p_gatt->links[p_ble_evt->evt.gap_evt.conn_handle]);
}


/**@brief   Handle a BLE_GATTC_EVT_EXCHANGE_MTU_RSP event.
 *
 * @details The effective ATT MTU is set to the lowest between what we requested and the peer's
 *          response. This events concludes the ATT MTU exchange. An event is sent to the user
 *          and a data length update procedure is started if necessary.
 *
 * @param[in]   p_gatt      GATT structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_exchange_mtu_rsp_evt(nrf_ble_gatt_t * p_gatt, ble_evt_t const * p_ble_evt)
{
    uint16_t conn_handle   = p_ble_evt->evt.gattc_evt.conn_handle;
    uint16_t server_rx_mtu = p_ble_evt->evt.gattc_evt.params.exchange_mtu_rsp.server_rx_mtu;

    nrf_ble_gatt_link_t * p_link = &p_gatt->links[conn_handle];

    // Determine the lowest MTU between our own desired MTU and the peer's.
    // The MTU may not be less than BLE_GATT_ATT_MTU_DEFAULT.
    p_link->att_mtu_effective = MIN(server_rx_mtu, p_link->att_mtu_desired);
    p_link->att_mtu_effective = MAX(p_link->att_mtu_effective, BLE_GATT_ATT_MTU_DEFAULT);

    NRF_LOG_DEBUG("ATT MTU updated to %u bytes on connection 0x%x (response).",
                  p_link->att_mtu_effective, conn_handle);

    // Trigger an event indicating that the ATT MTU size has changed.
    // Send an event to the application only if an ATT MTU exchange was requested.
    if ((p_gatt->evt_handler != NULL) && (p_link->att_mtu_exchange_requested))
    {
        nrf_ble_gatt_evt_t const evt =
        {
            .evt_id                   = NRF_BLE_GATT_EVT_ATT_MTU_UPDATED,
            .conn_handle              = conn_handle,
            .params.att_mtu_effective = p_link->att_mtu_effective,
        };

        p_gatt->evt_handler(p_gatt, &evt);
    }

    p_link->att_mtu_exchange_requested = false;
    p_link->att_mtu_exchange_pending   = false;
}


/**@brief Handle a BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST event.
 *
 * @param[in]   p_gatt      GATT structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_exchange_mtu_request_evt(nrf_ble_gatt_t * p_gatt, ble_evt_t const * p_ble_evt)
{
    ret_code_t err_code;
    uint16_t   conn_handle = p_ble_evt->evt.gatts_evt.conn_handle;
    uint16_t   client_mtu  = p_ble_evt->evt.gatts_evt.params.exchange_mtu_request.client_rx_mtu;

    nrf_ble_gatt_link_t * p_link = &p_gatt->links[conn_handle];

    NRF_LOG_DEBUG("Peer on connection 0x%x requested an ATT MTU of %u bytes.",
                  conn_handle, client_mtu);

    client_mtu = MAX(client_mtu, BLE_GATT_ATT_MTU_DEFAULT);
    p_link->att_mtu_effective = MIN(client_mtu, p_link->att_mtu_desired);
    p_link->att_mtu_exchange_pending = false;

    NRF_LOG_DEBUG("Updating ATT MTU to %u bytes (desired: %u) on connection 0x%x.",
                  p_link->att_mtu_effective, p_link->att_mtu_desired, conn_handle);

    err_code = sd_ble_gatts_exchange_mtu_reply(conn_handle, p_link->att_mtu_desired);

    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_ERROR("sd_ble_gatts_exchange_mtu_reply() returned %s.", nrf_strerror_get(err_code));
    }

    // If an ATT_MTU exchange was requested to the peer, defer sending
    // the data length update request and the event to the application until
    // the response for that request is received.
    if (p_link->att_mtu_exchange_requested)
    {
        return;
    }

    // The ATT MTU exchange has finished. Send an event to the application.
    if (p_gatt->evt_handler != NULL)
    {
        nrf_ble_gatt_evt_t const evt =
        {
            .evt_id                   = NRF_BLE_GATT_EVT_ATT_MTU_UPDATED,
            .conn_handle              = conn_handle,
            .params.att_mtu_effective = p_link->att_mtu_effective,
        };

        p_gatt->evt_handler(p_gatt, &evt);
    }
}


/**@brief   Handle a BLE_GAP_EVT_DATA_LENGTH_UPDATE event.
 *
 * @details Update the connection data length and send an event to the user.
 *
 * @param[in]   p_gatt      GATT structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
#if !defined (S112)
static void on_data_length_update_evt(nrf_ble_gatt_t * p_gatt, ble_evt_t const * p_ble_evt)
{
    ble_gap_evt_t const gap_evt     = p_ble_evt->evt.gap_evt;
    uint16_t      const conn_handle = gap_evt.conn_handle;

    // Update the connection data length.
    // The SoftDevice only supports symmetric RX/TX data length settings.
    p_gatt->links[conn_handle].data_length_effective =
        gap_evt.params.data_length_update.effective_params.max_tx_octets;

    NRF_LOG_DEBUG("Data length updated to %u on connection 0x%0x.",
                  p_gatt->links[conn_handle].data_length_effective,
                  conn_handle);

    NRF_LOG_DEBUG("max_rx_octets: %u",
                  gap_evt.params.data_length_update.effective_params.max_rx_octets);
    NRF_LOG_DEBUG("max_tx_octets: %u",
                  gap_evt.params.data_length_update.effective_params.max_tx_octets);
    NRF_LOG_DEBUG("max_rx_time: %u",
                  gap_evt.params.data_length_update.effective_params.max_rx_time_us);
    NRF_LOG_DEBUG("max_tx_time: %u",
                  gap_evt.params.data_length_update.effective_params.max_tx_time_us);

    if (p_gatt->evt_handler != NULL)
    {
        nrf_ble_gatt_evt_t const evt =
        {
            .evt_id             = NRF_BLE_GATT_EVT_DATA_LENGTH_UPDATED,
            .conn_handle        = conn_handle,
            .params.data_length = p_gatt->links[conn_handle].data_length_effective,
        };

        p_gatt->evt_handler(p_gatt, &evt);
    }
}


/**@brief   Handle a BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST event.
 *
 *@details  Reply with a sd_ble_gap_data_length_update() call, using the minimum between the
 *          link's preferred data length, and what requested by the peer.
 *          The link preferred data length is set to the global preferred data length
 *          upon connection and can be overridden by calling nrf_ble_gatt_data_length_set().
 *          The default is NRF_SDH_BLE_GAP_DATA_LENGTH.
 *
 *@note     The SoftDevice will not send any BLE_GAP_EVT_DATA_LENGTH_UPDATE events on this side.
 *          Therefore, the connection data length is updated immediately and an event is sent
 *          to the user.
 *
 * @param[in]   p_gatt      GATT structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_data_length_update_request_evt(nrf_ble_gatt_t * p_gatt, ble_evt_t const * p_ble_evt)
{
    ble_gap_evt_t       const * p_gap_evt = &p_ble_evt->evt.gap_evt;
    nrf_ble_gatt_link_t       * p_link    = &p_gatt->links[p_gap_evt->conn_handle];

    // The SoftDevice only supports symmetric RX/TX data length settings.
    uint8_t const data_length_requested =
        p_gap_evt->params.data_length_update_request.peer_params.max_tx_octets;

    NRF_LOG_DEBUG("Peer on connection 0x%x requested a data length of %u bytes.",
                  p_gap_evt->conn_handle, data_length_requested);

    uint8_t const data_length_effective = MIN(p_link->data_length_desired, data_length_requested);

    (void) data_length_update(p_gap_evt->conn_handle, data_length_effective);
}
#endif // !defined (S112)


ret_code_t nrf_ble_gatt_init(nrf_ble_gatt_t * p_gatt, nrf_ble_gatt_evt_handler_t evt_handler)
{
    VERIFY_PARAM_NOT_NULL(p_gatt);

    p_gatt->evt_handler             = evt_handler;
    p_gatt->att_mtu_desired_periph  = NRF_SDH_BLE_GATT_MAX_MTU_SIZE;
    p_gatt->att_mtu_desired_central = NRF_SDH_BLE_GATT_MAX_MTU_SIZE;
    p_gatt->data_length             = NRF_SDH_BLE_GAP_DATA_LENGTH;

    for (uint32_t i = 0; i < NRF_BLE_GATT_LINK_COUNT; i++)
    {
        link_init(&p_gatt->links[i]);
    }

    return NRF_SUCCESS;
}


ret_code_t nrf_ble_gatt_att_mtu_periph_set(nrf_ble_gatt_t * p_gatt, uint16_t desired_mtu)
{
    VERIFY_PARAM_NOT_NULL(p_gatt);

    if ((desired_mtu < BLE_GATT_ATT_MTU_DEFAULT) || (desired_mtu > NRF_SDH_BLE_GATT_MAX_MTU_SIZE))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    p_gatt->att_mtu_desired_periph = desired_mtu;
    return NRF_SUCCESS;
}


ret_code_t nrf_ble_gatt_att_mtu_central_set(nrf_ble_gatt_t * p_gatt, uint16_t desired_mtu)
{
    VERIFY_PARAM_NOT_NULL(p_gatt);

    if ((desired_mtu < BLE_GATT_ATT_MTU_DEFAULT) || (desired_mtu > NRF_SDH_BLE_GATT_MAX_MTU_SIZE))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    p_gatt->att_mtu_desired_central = desired_mtu;
    return NRF_SUCCESS;
}


uint16_t nrf_ble_gatt_eff_mtu_get(nrf_ble_gatt_t const * p_gatt, uint16_t conn_handle)
{
    if ((p_gatt == NULL) || (conn_handle >= NRF_BLE_GATT_LINK_COUNT))
    {
        return 0;
    }

    return p_gatt->links[conn_handle].att_mtu_effective;
}

#if !defined (S112)
ret_code_t nrf_ble_gatt_data_length_set(nrf_ble_gatt_t * p_gatt,
                                        uint16_t         conn_handle,
                                        uint8_t          data_length)
{
    if (p_gatt == NULL)
    {
        return NRF_ERROR_NULL;
    }

    // Check early to avoid requesting an invalid data length for upcoming connections.
    if (   (data_length > BLE_GAP_DATA_LENGTH_MAX)
        || (data_length < BLE_GAP_DATA_LENGTH_DEFAULT))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    if (conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        // Save value and request upon connection.
        p_gatt->data_length = data_length;
        return NRF_SUCCESS;
    }

    if (conn_handle >= NRF_BLE_GATT_LINK_COUNT)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    // Request data length on existing link.
    p_gatt->links[conn_handle].data_length_desired = data_length;

    return data_length_update(conn_handle, data_length);
}


ret_code_t nrf_ble_gatt_data_length_get(nrf_ble_gatt_t const * p_gatt,
                                        uint16_t               conn_handle,
                                        uint8_t              * p_data_length)
{
    if ((p_gatt == NULL) || (p_data_length == NULL))
    {
        return NRF_ERROR_NULL;
    }

    if (conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        *p_data_length = p_gatt->data_length;
        return NRF_SUCCESS;
    }

    if (conn_handle >= NRF_BLE_GATT_LINK_COUNT)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    *p_data_length = p_gatt->links[conn_handle].data_length_effective;
    return NRF_SUCCESS;
}
#endif // !defined (S112)


void nrf_ble_gatt_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    nrf_ble_gatt_t * p_gatt      = (nrf_ble_gatt_t *)p_context;
    uint16_t         conn_handle = p_ble_evt->evt.common_evt.conn_handle;

    if (conn_handle >= NRF_BLE_GATT_LINK_COUNT)
    {
        return;
    }

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connected_evt(p_gatt, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnected_evt(p_gatt, p_ble_evt);
            break;

        case BLE_GATTC_EVT_EXCHANGE_MTU_RSP:
            on_exchange_mtu_rsp_evt(p_gatt, p_ble_evt);
            break;

        case BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST:
            on_exchange_mtu_request_evt(p_gatt, p_ble_evt);
            break;

#if !defined (S112)
        case BLE_GAP_EVT_DATA_LENGTH_UPDATE:
            on_data_length_update_evt(p_gatt, p_ble_evt);
            break;

        case BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST:
            on_data_length_update_request_evt(p_gatt, p_ble_evt);
            break;
#endif // !defined (S112)

        default:
            break;
    }

    if (p_gatt->links[conn_handle].att_mtu_exchange_pending)
    {
        ret_code_t err_code;

        err_code = sd_ble_gattc_exchange_mtu_request(conn_handle,
                                                     p_gatt->links[conn_handle].att_mtu_desired);

        if (err_code == NRF_SUCCESS)
        {
            p_gatt->links[conn_handle].att_mtu_exchange_pending   = false;
            p_gatt->links[conn_handle].att_mtu_exchange_requested = true;

            NRF_LOG_DEBUG("Requesting to update ATT MTU to %u bytes on connection 0x%x (retry).",
                          p_gatt->links[conn_handle].att_mtu_desired, conn_handle);
        }
        else if (err_code != NRF_ERROR_BUSY)
        {
            NRF_LOG_ERROR("sd_ble_gattc_exchange_mtu_request() returned %s.",
                          nrf_strerror_get(err_code));
        }
    }
}

#endif //NRF_BLE_GATT_ENABLED
