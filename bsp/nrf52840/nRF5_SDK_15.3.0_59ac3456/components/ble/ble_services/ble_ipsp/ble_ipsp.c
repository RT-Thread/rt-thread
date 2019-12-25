/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
#include <stdbool.h>
#include <string.h>
#include "nordic_common.h"
#include "sdk_errors.h"
#include "nrf.h"
#include "sdk_config.h"
#include "ble_ipsp.h"
#include "ble_srv_common.h"
#include "sdk_os.h"


/**
 * @defgroup ble_ipsp_log Module's Log Macros
 * @details Macros used for creating module logs which can be useful in understanding handling
 *          of events or actions on API requests. These are intended for debugging purposes and
 *          can be enabled by defining the IOT_BLE_IPSP_CONFIG_LOG_ENABLED to 1.
 * @note If NRF_LOG_ENABLED is disabled, having IOT_BLE_IPSP_CONFIG_LOG_ENABLED
 *       has no effect.
 * @{
 */

#if IOT_BLE_IPSP_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME ipsp

#define NRF_LOG_LEVEL       IOT_BLE_IPSP_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  IOT_BLE_IPSP_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR IOT_BLE_IPSP_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define BLE_IPSP_TRC        NRF_LOG_DEBUG                                                           /**< Used for getting trace of execution in the module. */
#define BLE_IPSP_ERR        NRF_LOG_ERROR                                                           /**< Used for logging errors in the module. */
#define BLE_IPSP_DUMP       NRF_LOG_HEXDUMP_DEBUG                                                   /**< Used for dumping octet information to get details of bond information etc. */

#define BLE_IPSP_ENTRY()                  BLE_IPSP_TRC(">> %s", __func__)
#define BLE_IPSP_EXIT()                   BLE_IPSP_TRC("<< %s", __func__)
#define BLE_IPSP_EXIT_WITH_RESULT(result) BLE_IPSP_TRC("<< %s, result 0x%08lX", __func__, result)

#else // IOT_BLE_IPSP_CONFIG_LOG_ENABLED

#define BLE_IPSP_TRC(...)                                                                           /**< Disables traces. */
#define BLE_IPSP_DUMP(...)                                                                          /**< Disables dumping of octet streams. */
#define BLE_IPSP_ERR(...)                                                                           /**< Disables error logs. */

#define BLE_IPSP_ENTRY(...)
#define BLE_IPSP_EXIT(...)
#define BLE_IPSP_EXIT_WITH_RESULT(...)

#endif // IOT_BLE_IPSP_CONFIG_LOG_ENABLED

#define IPSP_ANY_CID 0xFFFE                                                                         /**< Identifier for any channel. Usage: Search for existing channel on a connection handle. */

/**
 * @defgroup api_param_check API Parameters check macros.
 *
 * @details Macros that verify parameters passed to the module in the APIs. These macros
 *          could be mapped to nothing in final versions of code to save execution and size.
 *          BLE_HPS_DISABLE_API_PARAM_CHECK should be defined to disable these checks.
 *
 * @{
 */
#if (BLE_IPSP_DISABLE_API_PARAM_CHECK == 0)

/**@brief Macro to check is module is initialized before requesting one of the module procedures. */
#define VERIFY_MODULE_IS_INITIALIZED()                                                             \
        if (m_evt_handler == NULL)                                                                 \
        {                                                                                          \
            return (NRF_ERROR_MODULE_NOT_INITIALIZED + NRF_ERROR_BLE_IPSP_ERR_BASE);               \
        }

/**@brief Macro to check is module is initialized before requesting one of the module
         procedures but does not use any return code. */
#define VERIFY_MODULE_IS_INITIALIZED_VOID()                                                        \
        if (m_evt_handler == NULL)                                                                 \
        {                                                                                          \
            return;                                                                                \
        }

/**@brief Verify NULL parameters are not passed to API by application. */
#define NULL_PARAM_CHECK(PARAM)                                                                    \
        if ((PARAM) == NULL)                                                                       \
        {                                                                                          \
            return (NRF_ERROR_NULL + NRF_ERROR_BLE_IPSP_ERR_BASE);                                 \
        }

/**@brief Verify the connection handle passed to the API. */
#define VERIFY_CON_HANDLE(CON_HANDLE)                                                              \
        if ((CON_HANDLE) == BLE_CONN_HANDLE_INVALID)                                               \
        {                                                                                          \
            return (NRF_ERROR_INVALID_PARAM + NRF_ERROR_BLE_IPSP_ERR_BASE);                        \
        }

#else // BLE_IPSP_DISABLE_API_PARAM_CHECK

#define VERIFY_MODULE_IS_INITIALIZED()
#define VERIFY_MODULE_IS_INITIALIZED_VOID()
#define NULL_PARAM_CHECK(PARAM)
#define VERIFY_CON_HANDLE(CON_HANDLE)

#endif //BLE_IPSP_DISABLE_API_PARAM_CHECK

/**
 * @defgroup ble_ipsp_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case the need to use an alternative architecture arises.
 * @{
 */
#define BLE_IPSP_MUTEX_LOCK()         SDK_MUTEX_LOCK(m_ipsp_mutex)                                  /**< Lock module using mutex */
#define BLE_IPSP_MUTEX_UNLOCK()       SDK_MUTEX_UNLOCK(m_ipsp_mutex)                                /**< Unlock module using mutex */
/** @} */

#define IPSP_MAX_CONNECTED_DEVICES    BLE_IPSP_MAX_CHANNELS                                         /**< Table for maximum number of connected devices the module will keep track of. */
#define RX_BUFFER_TOTAL_SIZE          (BLE_IPSP_RX_BUFFER_SIZE * BLE_IPSP_RX_BUFFER_COUNT)          /**< Total receive buffer size reserved for each IPSP channel. */
#define MAX_L2CAP_RX_BUFFER           (RX_BUFFER_TOTAL_SIZE * BLE_IPSP_MAX_CHANNELS)                /**< Total receive buffer received for all channels. */
#define INVALID_CHANNEL_INSTANCE      0xFF                                                          /**< Indicates channel instance is invalid. */


/**@brief IPSP Channel States. */
typedef enum
{
    CHANNEL_IDLE,                                                                                   /**< Indicates the channel is free and not in use. */
    CHANNEL_CONNECTING,                                                                             /**< Indicates the channel creation is requested and is awaiting a response. */
    CHANNEL_CONNECTED,                                                                              /**< Indicates the channel is connected and ready for data exchange. */
    CHANNEL_DISCONNECTING                                                                           /**< Indicates the channel is in the process of being disconnected. */
} channel_state_t;


/**@brief Possible response actions for an incoming channel. Default is to accept. */
typedef enum
{
    INCOMING_CHANNEL_ACCEPT,                                                                       /**< Indicates that the incoming channel should be accepted if all other criteria are met. */
    INCOMING_CHANNEL_REJECT                                                                        /**< Indicates that the incoming channel for IPSP PSM should be rejected regardless of the other criteria. */
} incoming_channel_action_t;

/**@brief Data type for book keeping connected devices.
 *
 * @note Not all connected devices establish an L2CAP connection.
 */
typedef struct
{
    volatile incoming_channel_action_t  response;                                                   /**< Indicator if the incoming channel should be accepted or rejected. */
    ble_gap_addr_t                      ble_addr;                                                   /**< Bluetooth device address of the peer. */
    uint16_t                            conn_handle;                                                /**< Connection handle identifying the link with the peer. */
} peer_connection_t;


/**@brief IPSP Channel Information. */
typedef struct
{
    uint16_t     conn_handle;                                                                       /**< Identifies the BLE link on which channel is established. BLE_CONN_HANDLE_INVALID if channel is unassigned. */
    uint16_t     cid;                                                                               /**< L2CAP channel identifier needed to manage the channel once established. BLE_L2CAP_CID_INVALID if channel is unassigned. */
    uint16_t     rx_buffer_status;                                                                  /**< Usage status of RX buffers. */
    uint8_t      state;                                                                             /**< State information for the channel. See @ref channel_state_t for details. */
    uint8_t    * p_rx_buffer;                                                                       /**< Receive buffer for the channel. */
} channel_t;


static ble_ipsp_evt_handler_t m_evt_handler = NULL;                                                 /**< Asynchronous event notification callback registered with the module. */
static channel_t              m_channel[BLE_IPSP_MAX_CHANNELS];                                     /**< Table of channels managed by the module. */
static uint8_t                m_rx_buffer[MAX_L2CAP_RX_BUFFER];                                     /**< Receive buffer reserved for all channels to receive data on the L2CAP IPSP channel. */
static peer_connection_t      m_connected_device[IPSP_MAX_CONNECTED_DEVICES];                       /**< Table maintaining list of peer devices and the connection handle.
                                                                                                      \n This information is needed for the 6lowpan compression and decompression.
                                                                                                      \n And no interface exists to query the softdevice. */
SDK_MUTEX_DEFINE(m_ipsp_mutex)                                                                      /**< Mutex variable. Currently unused, this declaration does not occupy any space in RAM. */


/**@brief Initialize the peer connected device in the list.
 *
 * @param[in] index Identifies the list element to be initialized.
 */
static __INLINE void connected_device_init(uint32_t index)
{
    memset (&m_connected_device[index].ble_addr, 0, sizeof(ble_gap_addr_t));
    m_connected_device[index].conn_handle = BLE_CONN_HANDLE_INVALID;
    m_connected_device[index].response    = INCOMING_CHANNEL_ACCEPT;
}


/**@brief Allocate an entry for the peer connected device in the list.
 *
 * @param[in] p_peer_addr Pointer to peer's device address.
 * @param[in] conn_handle Connection handle identifying the link with the peer.
 */
static __INLINE void connected_device_allocate(ble_gap_addr_t const * p_peer_addr,
                                               uint16_t               conn_handle)
{
    for (uint32_t index = 0; index < IPSP_MAX_CONNECTED_DEVICES; index++)
    {
        if (m_connected_device[index].conn_handle == BLE_CONN_HANDLE_INVALID)
        {
            m_connected_device[index].conn_handle = conn_handle;
            memcpy(m_connected_device[index].ble_addr.addr, p_peer_addr->addr, BLE_GAP_ADDR_LEN);
            break;
        }
    }
}


/**@brief Search for an entry for the peer connected device in the list.
 *
 * @param[in] conn_handle Connection handle identifying the link with the peer.
 *
 * @retval A valid device index in the list if found, else,
 *         IPSP_MAX_CONNECTED_DEVICES indicating the search failed.
 */
static __INLINE uint32_t connected_device_search(uint16_t conn_handle)
{
    for (uint32_t index = 0; index < IPSP_MAX_CONNECTED_DEVICES; index++)
    {
        if (m_connected_device[index].conn_handle == conn_handle)
        {
            return index;
        }
    }
    return IPSP_MAX_CONNECTED_DEVICES;
}


/**@brief Initialize channel.
 *
 * @param[in] ch_id Identifies the IPSP channel on which the procedure is requested.
 */
static __INLINE void channel_init(uint8_t ch_id)
{
    m_channel[ch_id].conn_handle      = BLE_CONN_HANDLE_INVALID;
    m_channel[ch_id].cid              = BLE_L2CAP_CID_INVALID;
    m_channel[ch_id].rx_buffer_status = 0;
    m_channel[ch_id].state            = CHANNEL_IDLE;
    m_channel[ch_id].p_rx_buffer      = &m_rx_buffer[ch_id*RX_BUFFER_TOTAL_SIZE];
}


/**@brief Free channel.
 *
 * @param[in] ch_id Identifies the IPSP channel on which the procedure is requested.
 */
static __INLINE void channel_free(uint8_t ch_id)
{
    BLE_IPSP_TRC("[Index 0x%02X]:[Conn Handle 0x%04X]:[CID 0x%04X]: Freeing channel",
             ch_id, m_channel[ch_id].conn_handle, m_channel[ch_id].cid);

    channel_init(ch_id);
}


/**@brief Searches the IPSP channel based on connection handle and local L2CAP channel identifier.
 *
 * @param[in]  conn_handle The connection handle, identifying the peer device.
 * @param[in]  l2cap_cid   The local L2CAP channel identifier, identifying the L2CAP channel.
 * @param[out] p_ch_id     The IPSP channel identifier, if the search succeeded, else,
 *                         BLE_IPSP_MAX_CHANNELS indicating no IPSP channel was found.
 */
static __INLINE uint32_t channel_search(uint16_t conn_handle, uint16_t l2cap_cid, uint8_t * p_ch_id)
{
    BLE_IPSP_TRC("[Conn Handle 0x%04X]:[CID 0x%04X]: channel_search",
             conn_handle, l2cap_cid);

    for (int i = 0; i < BLE_IPSP_MAX_CHANNELS; i++)
    {
        BLE_IPSP_TRC("[@ Index 0x%02X] ==> Conn Handle: 0x%04X"
                 "                            CID        : 0x%04X",
                 i, m_channel[i].conn_handle, m_channel[i].cid);

        if (m_channel[i].conn_handle == conn_handle)
        {
            if ((l2cap_cid == IPSP_ANY_CID) || (m_channel[i].cid == l2cap_cid))
            {
                BLE_IPSP_TRC("channel_search succeeded, index 0x%04X", i);

                *p_ch_id = (uint8_t)i;
                return NRF_SUCCESS;
            }
        }
    }

    BLE_IPSP_TRC("No matching channel found!");
    return (NRF_ERROR_BLE_IPSP_ERR_BASE + NRF_ERROR_NOT_FOUND);
}


/**@brief Notify application of an event.
 *
 * @param[in] Identifies the IPSP instance for which the event is notified.
 * @param[in] Describes the notified event and its parameters, if any.
 */
static __INLINE void app_notify(ble_ipsp_handle_t * p_handle, ble_ipsp_evt_t * p_event)
{
    BLE_IPSP_MUTEX_UNLOCK();

    BLE_IPSP_TRC("[Conn Handle 0x%04X]:[CID 0x%04X]: Notifying application of event 0x%04X",
             p_handle->conn_handle, p_handle->cid, p_event->evt_id);

    UNUSED_VARIABLE(m_evt_handler(p_handle, p_event));

    BLE_IPSP_MUTEX_LOCK();
}


/**@brief Verifies if the buffer is TX buffer on the channel or not.
 *
 * @param[in] ch_id    Identifies the IPSP channel for which the procedure is requested.
 * @param[in] p_buffer Address of the buffer being verified to be TX or not.
 */
static __INLINE bool is_tx_buffer(uint32_t ch_id, const uint8_t * p_buffer)
{
    // If the buffer is in the RX buffer list, then it is not TX!
    if ((p_buffer >= (uint8_t *)&m_channel[ch_id].p_rx_buffer) &&
        (p_buffer <  (uint8_t *)&m_channel[ch_id].p_rx_buffer[RX_BUFFER_TOTAL_SIZE]))
    {
        return false;
    }

    return true;
}


/**@brief Submit receive buffers to the softdevice for a channel.
 *
 * @param[in] ch_id Identifies the IPSP channel for which the procedure is requested.
 */
static __INLINE void rx_buffers_submit(uint32_t ch_id)
{
    uint32_t retval;

    for (uint32_t buffer_index = 0; buffer_index < BLE_IPSP_RX_BUFFER_COUNT; buffer_index++)
    {
        const ble_data_t sdu_buf =
        {
            .p_data = (uint8_t *)&m_channel[ch_id].p_rx_buffer[buffer_index * BLE_IPSP_MTU],
            .len    = BLE_IPSP_MTU
        };

        if (IS_SET(m_channel[ch_id].rx_buffer_status, buffer_index) == 0)
        {
            retval = sd_ble_l2cap_ch_rx(m_channel[ch_id].conn_handle,
                                        m_channel[ch_id].cid,
                                        &sdu_buf);
            if (retval == NRF_SUCCESS)
            {
                 SET_BIT(m_channel[ch_id].rx_buffer_status, buffer_index);
            }
        }
    }
}


/**@brief Mark a receive buffer as not in use for a particular channel.
 *
 * @param[in] ch_id     Identifies the IPSP channel for which the procedure is requested.
 * @param[in] p_buffer  The buffer to be marked as unused.
 *
 * @note This is a temporary state for the receive buffer before it is resubmitted to the SoftDevice.
 */
static __INLINE void rx_buffer_mark_unused(uint32_t ch_id, uint8_t * p_buffer)
{
    for (uint32_t buffer_index = 0; buffer_index < BLE_IPSP_RX_BUFFER_COUNT; buffer_index++)
    {
        if (&m_channel[ch_id].p_rx_buffer[buffer_index * BLE_IPSP_MTU] == p_buffer)
        {
            CLR_BIT(m_channel[ch_id].rx_buffer_status, buffer_index);
        }
    }
}


void ble_ipsp_evt_handler(ble_evt_t const * p_evt)
{
    VERIFY_MODULE_IS_INITIALIZED_VOID();

    ble_ipsp_handle_t    handle;
    ble_ipsp_evt_t       ipsp_event;
    uint32_t             retval;
    uint8_t              ch_id;
    bool                 notify_event;
    bool                 submit_rx_buffer;

    ch_id                 = INVALID_CHANNEL_INSTANCE;
    notify_event          = false;
    submit_rx_buffer      = false;
    retval                = NRF_SUCCESS;
    ipsp_event.evt_result = NRF_SUCCESS;
    handle.conn_handle    = BLE_CONN_HANDLE_INVALID;
    handle.cid            = BLE_L2CAP_CID_INVALID;

    BLE_IPSP_TRC("Received BLE Event 0x%04X",p_evt->header.evt_id);

    BLE_IPSP_MUTEX_LOCK();

    switch (p_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
            // Create an entry in the connected devices table.
            // This is needed to be able to fetch the peer address on IPSP channel establishment.
            connected_device_allocate(&p_evt->evt.gap_evt.params.connected.peer_addr,
                                      p_evt->evt.gap_evt.conn_handle);
            break;
        }
        case BLE_L2CAP_EVT_CH_SETUP_REQUEST:
        {
            // This event is generated for the acceptor role and indicates an channel establishment
            // request from the peer.
            ble_l2cap_ch_setup_params_t reply_param;
            uint16_t                    local_cid;

            memset(&reply_param, 0, sizeof(ble_l2cap_ch_setup_params_t));

            reply_param.le_psm            = p_evt->evt.l2cap_evt.params.ch_setup_request.le_psm;
            reply_param.rx_params.rx_mtu  = BLE_IPSP_MTU;
            reply_param.rx_params.rx_mps  = BLE_IPSP_RX_MPS;

            // Check if a channel already exists with the peer.
            retval = channel_search(p_evt->evt.l2cap_evt.conn_handle,
                                    IPSP_ANY_CID,
                                    &ch_id);

            BLE_IPSP_TRC("Exiting channel_search result 0x%08X", ch_id);

            if (retval == NRF_SUCCESS)
            {
                BLE_IPSP_TRC("Rejecting channel, as IPSP channel already exists "
                         "0x%08X in state 0x%08X", ch_id, m_channel[ch_id].state);

                reply_param.status = BLE_L2CAP_CH_STATUS_CODE_NO_RESOURCES;

                // Reinitialize ch_id to invalid so that existing channel is not impacted.
                ch_id = INVALID_CHANNEL_INSTANCE;
            }
            else
            {
                uint32_t peer_device_index = connected_device_search(p_evt->evt.l2cap_evt.conn_handle);
                local_cid                  = p_evt->evt.l2cap_evt.local_cid;

                if (p_evt->evt.l2cap_evt.params.ch_setup_request.le_psm != BLE_IPSP_PSM)
                {
                    reply_param.status = BLE_L2CAP_CH_STATUS_CODE_LE_PSM_NOT_SUPPORTED;
                    BLE_IPSP_TRC("Rejecting L2CAP Channel, unknown PSM %04X!",
                              p_evt->evt.l2cap_evt.params.ch_setup_request.le_psm);
                }
                else if ((peer_device_index != IPSP_MAX_CONNECTED_DEVICES) &&
                        (m_connected_device[peer_device_index].response == INCOMING_CHANNEL_REJECT))
                {
                    reply_param.status = BLE_L2CAP_CH_STATUS_CODE_NO_RESOURCES;
                    BLE_IPSP_ERR("Barred incoming requests by the application. "
                                 "Rejecting L2CAP Channel %04X!",
                                 p_evt->evt.l2cap_evt.params.ch_setup_request.le_psm);
                }
                else if (p_evt->evt.l2cap_evt.params.ch_setup_request.tx_params.tx_mtu < BLE_IPSP_MTU)
                {
                    reply_param.status = BLE_L2CAP_CH_STATUS_CODE_UNACCEPTABLE_PARAMS;
                    BLE_IPSP_TRC("Rejecting L2CAP Channel, unacceptable TX parameters!");
                }
                else
                {
                    // Peer request acceptable, look for a free channel.
                    retval = channel_search(BLE_CONN_HANDLE_INVALID, BLE_L2CAP_CID_INVALID, &ch_id);
                    BLE_IPSP_TRC("Free channel search result 0x%08X", ch_id);

                    if (retval != NRF_SUCCESS)
                    {
                        BLE_IPSP_TRC("Rejecting L2CAP Channel, no resources!");
                        reply_param.status = BLE_L2CAP_CH_STATUS_CODE_NO_RESOURCES;
                    }
                    else
                    {
                        BLE_IPSP_TRC("Accepting L2CAP Channel");
                        reply_param.rx_params.sdu_buf.p_data = NULL;
                        reply_param.rx_params.sdu_buf.len    = 0;
                        reply_param.status                   = BLE_L2CAP_CH_STATUS_CODE_SUCCESS;
                    }
                }
            }

            retval = sd_ble_l2cap_ch_setup(p_evt->evt.l2cap_evt.conn_handle,
                                           &local_cid,
                                           &reply_param);

            BLE_IPSP_TRC("sd_ble_l2cap_ch_setup result = 0x%08lX", retval);

            if ((retval == NRF_SUCCESS) &&
                (reply_param.status == BLE_L2CAP_CH_STATUS_CODE_SUCCESS) &&
                (ch_id != INVALID_CHANNEL_INSTANCE))
            {
                BLE_IPSP_TRC("[0x%04X][0x%04X]: Channel Connected. Rx MPS = 0x%04X",
                         p_evt->evt.l2cap_evt.conn_handle,
                         p_evt->evt.l2cap_evt.local_cid,
                         reply_param.rx_params.rx_mps);

                ipsp_event.evt_id     = BLE_IPSP_EVT_CHANNEL_CONNECTED;
                ipsp_event.evt_result = NRF_SUCCESS;

                // Channel is assigned to this link.
                m_channel[ch_id].state       = CHANNEL_CONNECTING;
                m_channel[ch_id].conn_handle = p_evt->evt.l2cap_evt.conn_handle;
                m_channel[ch_id].cid         = local_cid;
            }
            else if (ch_id != INVALID_CHANNEL_INSTANCE)
            {
                // Free the allocated channel.
                channel_init(ch_id);
            }
            break;
        }
        case BLE_L2CAP_EVT_CH_SETUP:
        {
            // This event is generated for both initiator and acceptor roles.
            // This event indicates that the IPSP channel is successfully established.
            retval = channel_search(p_evt->evt.l2cap_evt.conn_handle,
                                    p_evt->evt.l2cap_evt.local_cid,
                                    &ch_id);

            if (retval != NRF_SUCCESS)
            {
                BLE_IPSP_TRC("Reply on unknown channel, dropping the event.");
            }
            else
            {
                if (m_channel[ch_id].state == CHANNEL_CONNECTING)
                {
                    // Channel created successfully.

                    // Initialize IPSP handle.
                    handle.conn_handle = p_evt->evt.l2cap_evt.conn_handle;
                    handle.cid         = p_evt->evt.l2cap_evt.local_cid;

                    // Initialize the event.
                    ipsp_event.evt_id     = BLE_IPSP_EVT_CHANNEL_CONNECTED;
                    ipsp_event.evt_result = NRF_SUCCESS;

                    // Set the channel state appropriately.
                    m_channel[ch_id].state = CHANNEL_CONNECTED;

                    // Set the flag to trigger submission of the receive buffers to the softdevice.
                    submit_rx_buffer = true;

                    // Notify the event to the application.
                    notify_event = true;
                }
            }
            break;
        }
        case BLE_L2CAP_EVT_CH_SETUP_REFUSED:
        {
            // This event is generated for both initiator and acceptor roles.
            // This event indicates that the IPSP channel establishment failed.
            retval = channel_search(p_evt->evt.l2cap_evt.conn_handle,
                                p_evt->evt.l2cap_evt.local_cid,
                                &ch_id);

            if (retval != NRF_SUCCESS)
            {
                BLE_IPSP_TRC("Reply on unknown channel, dropping the event.");
            }
            else
            {
                if (m_channel[ch_id].state == CHANNEL_CONNECTING)
                {
                    // Channel creation failed as peer rejected the connection.

                    // Initialize the event.
                    ipsp_event.evt_id     = BLE_IPSP_EVT_CHANNEL_CONNECTED;
                    ipsp_event.evt_result = NRF_ERROR_BLE_IPSP_PEER_REJECTED;

                    BLE_IPSP_ERR("Peer rejected channel creation request, reason %d",
                              p_evt->evt.l2cap_evt.params.ch_setup_refused.status);

                    // Free the channel.
                    channel_free(ch_id);

                    // Notify the event to the application.
                    notify_event = true;
                }
            }
            break;
        }
        case BLE_L2CAP_EVT_CH_RELEASED:
        {
            BLE_IPSP_TRC("L2CAP Channel disconnected.");

            ipsp_event.evt_id    = BLE_IPSP_EVT_CHANNEL_DISCONNECTED;

            retval = channel_search(p_evt->evt.l2cap_evt.conn_handle,
                                    p_evt->evt.l2cap_evt.local_cid,
                                    &ch_id);

            // Notify application of disconnection.
            if (retval == NRF_SUCCESS)
            {
                handle.conn_handle = p_evt->evt.l2cap_evt.conn_handle;
                handle.cid         = p_evt->evt.l2cap_evt.local_cid;

                channel_free(ch_id);

                // Notify the event to the application.
                notify_event = true;
            }
            break;
        }
        case BLE_L2CAP_EVT_CH_RX:
        {
            ipsp_event.evt_id = BLE_IPSP_EVT_CHANNEL_DATA_RX;

            retval = channel_search(p_evt->evt.l2cap_evt.conn_handle,
                                    p_evt->evt.l2cap_evt.local_cid,
                                    &ch_id);

            if (retval == NRF_SUCCESS)
            {
                handle.conn_handle = p_evt->evt.l2cap_evt.conn_handle;
                handle.cid         = p_evt->evt.l2cap_evt.local_cid;

                rx_buffer_mark_unused(ch_id, p_evt->evt.l2cap_evt.params.rx.sdu_buf.p_data);

                // Set the flag to trigger submission of the receive buffers to the softdevice.
                submit_rx_buffer = true;

                // Notify the event to the application.
                notify_event = true;
            }
            break;
        }
        case BLE_L2CAP_EVT_CH_TX:
        {
            BLE_IPSP_TRC("BLE_L2CAP_EVT_CH_TX --> p_sdu_buf = %p, p_sdu_buf.p_data = %p",
                     &p_evt->evt.l2cap_evt.params.tx.sdu_buf, p_evt->evt.l2cap_evt.params.tx.sdu_buf.p_data);

            retval = channel_search(p_evt->evt.l2cap_evt.conn_handle,
                                    p_evt->evt.l2cap_evt.local_cid,
                                    &ch_id);

            if ((ch_id != INVALID_CHANNEL_INSTANCE) &&
                p_evt->evt.l2cap_evt.local_cid == m_channel[ch_id].cid)
            {
                // Initialize the event.
                ipsp_event.evt_id = BLE_IPSP_EVT_CHANNEL_DATA_TX_COMPLETE;

                // Initialize the handle.
                handle.conn_handle = m_channel[ch_id].conn_handle;
                handle.cid         = m_channel[ch_id].cid;

                // Notify the event to the application.
                notify_event = true;
            }
            break;
        }
        case BLE_L2CAP_EVT_CH_SDU_BUF_RELEASED:
        {
            BLE_IPSP_TRC("BLE_L2CAP_EVT_CH_SDU_BUF_RELEASED --> p_sdu_buf = %p, p_sdu_buf.p_data = %p",
                    &p_evt->evt.l2cap_evt.params.ch_sdu_buf_released.sdu_buf,
                    p_evt->evt.l2cap_evt.params.ch_sdu_buf_released.sdu_buf.p_data);

            retval = channel_search(p_evt->evt.l2cap_evt.conn_handle,
                                    p_evt->evt.l2cap_evt.local_cid,
                                    &ch_id);

            if ((ch_id != INVALID_CHANNEL_INSTANCE) &&
                (p_evt->evt.l2cap_evt.local_cid == m_channel[ch_id].cid) &&
                (is_tx_buffer(ch_id, p_evt->evt.l2cap_evt.params.ch_sdu_buf_released.sdu_buf.p_data)))
            {
                // Initialize the event.
                ipsp_event.evt_id     = BLE_IPSP_EVT_CHANNEL_DATA_TX_COMPLETE;
                ipsp_event.evt_result = NRF_ERROR_BLE_IPSP_LINK_DISCONNECTED;

                // Initialize the handle.
                handle.conn_handle = m_channel[ch_id].conn_handle;
                handle.cid         = m_channel[ch_id].cid;

                // Notify the event to the application.
                notify_event = true;
            }
            break;
        }
        case BLE_GAP_EVT_DISCONNECTED:
        {
            uint32_t peer_device_index = connected_device_search(handle.conn_handle);
            if (peer_device_index < IPSP_MAX_CONNECTED_DEVICES)
            {
                connected_device_init(peer_device_index);
            }
            break;
        }
        default:
            break;
    }

    if (notify_event)
    {
        ble_ipsp_event_param_t event_param;
        uint32_t               peer_device_index;

        peer_device_index = connected_device_search(handle.conn_handle);

        if (peer_device_index < IPSP_MAX_CONNECTED_DEVICES)
        {
            event_param.p_peer = &m_connected_device[peer_device_index].ble_addr;
            BLE_IPSP_TRC("Found peer device. Address type = 0x%02x",
                      event_param.p_peer->addr_type);
            BLE_IPSP_DUMP((uint8_t *)event_param.p_peer->addr, 6);
        }
        else
        {
            event_param.p_peer = NULL;
        }

        event_param.p_l2cap_evt = &p_evt->evt.l2cap_evt;
        ipsp_event.p_evt_param  = &event_param;

        app_notify(&handle, &ipsp_event);
    }

    // Trigger submission of the receive buffers to the softdevice.
    if (submit_rx_buffer)
    {
        rx_buffers_submit(ch_id);
    }

    BLE_IPSP_MUTEX_UNLOCK();
    UNUSED_VARIABLE(retval);
}


uint32_t ble_ipsp_init(const ble_ipsp_init_t * p_init)
{
    BLE_IPSP_ENTRY();

    ble_uuid_t    ble_uuid;
    uint32_t      err_code;
    uint16_t      handle;

    NULL_PARAM_CHECK(p_init);
    NULL_PARAM_CHECK(p_init->evt_handler);

    SDK_MUTEX_INIT(m_ipsp_mutex);

    BLE_IPSP_MUTEX_LOCK();

    // Add service to indicate IPSP support.
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_IPSP_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    m_evt_handler = p_init->evt_handler;

    // Initialize the channel.
    for (int i = 0; i < BLE_IPSP_MAX_CHANNELS; i++)
    {
        channel_init(i);
    }

    // Initialize the connected peer device table.
    for (int i = 0; i < IPSP_MAX_CONNECTED_DEVICES; i++)
    {
        connected_device_init(i);
    }
    BLE_IPSP_MUTEX_UNLOCK();

    BLE_IPSP_EXIT();

    return NRF_SUCCESS;
}


uint32_t ble_ipsp_connect(const ble_ipsp_handle_t * p_handle)
{
    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_handle);
    VERIFY_CON_HANDLE(p_handle->conn_handle);

    uint32_t err_code;
    uint8_t  ch_id  = INVALID_CHANNEL_INSTANCE;

    BLE_IPSP_TRC("[Conn Handle 0x%04X]: >> ble_ipsp_connect",
             p_handle->conn_handle);

    BLE_IPSP_MUTEX_LOCK();

    // Check if channel already exists with the peer.
    err_code = channel_search(p_handle->conn_handle, IPSP_ANY_CID, &ch_id);

    if (err_code == NRF_SUCCESS)
    {
        // IPSP channel already exists.
        err_code = NRF_ERROR_BLE_IPSP_CHANNEL_ALREADY_EXISTS;
    }
    else
    {
        // Search for a free channel.
        err_code = channel_search(BLE_CONN_HANDLE_INVALID, BLE_L2CAP_CID_INVALID, &ch_id);
        BLE_IPSP_TRC("2 channel_search result %08X", err_code);

        if (err_code == NRF_SUCCESS)
        {
            m_channel[ch_id].state = CHANNEL_CONNECTING;

            ble_l2cap_ch_setup_params_t param =
            {
                .le_psm = BLE_IPSP_PSM,
                .rx_params = {
                    .rx_mtu         = BLE_IPSP_MTU,
                    .rx_mps         = BLE_IPSP_RX_MPS,
                    .sdu_buf =
                    {
                        .p_data = NULL,
                        .len    = 0
                    }
                }
            };
            BLE_IPSP_TRC("Requesting sd_ble_l2cap_ch_setup");

            err_code = sd_ble_l2cap_ch_setup(p_handle->conn_handle,
                                             &m_channel[ch_id].cid,
                                             &param);

            if (err_code != NRF_SUCCESS)
            {
                BLE_IPSP_ERR("sd_ble_l2cap_ch_conn_request failed, reason %08lX", err_code);
                channel_free(ch_id);
            }
            else
            {
                BLE_IPSP_TRC("Local channel id from SD %04X.", m_channel[ch_id].cid);
                m_channel[ch_id].conn_handle = p_handle->conn_handle;
            }
        }
        else
        {
            err_code = (NRF_ERROR_BLE_IPSP_ERR_BASE + NRF_ERROR_NO_MEM);
        }
    }

    BLE_IPSP_MUTEX_UNLOCK();

    BLE_IPSP_EXIT_WITH_RESULT(err_code);

    return err_code;
}


uint32_t ble_ipsp_send(ble_ipsp_handle_t const * p_handle,
                       uint8_t const           * p_data,
                       uint16_t                  data_len)
{
    BLE_IPSP_ENTRY();

    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_handle);
    NULL_PARAM_CHECK(p_data);
    VERIFY_CON_HANDLE(p_handle->conn_handle);

    uint32_t err_code;
    uint8_t  ch_id;

    BLE_IPSP_MUTEX_LOCK();

    err_code = channel_search(p_handle->conn_handle, p_handle->cid, &ch_id);

    if (err_code == NRF_SUCCESS)
    {
        const ble_data_t p_sdu_buf =
        {
            .p_data = (uint8_t *)p_data,
            .len    = data_len
        };

        BLE_IPSP_TRC("p_sdu_buf = %p, p_sdu_buf.p_data = %p",
                 &p_sdu_buf, p_data);

        err_code = sd_ble_l2cap_ch_tx(p_handle->conn_handle,
                                      p_handle->cid,
                                      &p_sdu_buf);
    }

    BLE_IPSP_MUTEX_UNLOCK();

    BLE_IPSP_EXIT_WITH_RESULT(err_code);

    return err_code;
}


uint32_t ble_ipsp_disconnect(ble_ipsp_handle_t const * p_handle)
{
    BLE_IPSP_ENTRY();

    VERIFY_MODULE_IS_INITIALIZED();
    NULL_PARAM_CHECK(p_handle);
    VERIFY_CON_HANDLE(p_handle->conn_handle);

    uint32_t err_code;
    uint8_t  ch_id;

    BLE_IPSP_MUTEX_LOCK();

    err_code = channel_search(p_handle->conn_handle, p_handle->cid, &ch_id);

    if (err_code == NRF_SUCCESS)
    {
        m_channel[ch_id].state = CHANNEL_DISCONNECTING;

        err_code = sd_ble_l2cap_ch_release(p_handle->conn_handle,
                                           p_handle->cid);
    }

    BLE_IPSP_MUTEX_UNLOCK();

    BLE_IPSP_EXIT_WITH_RESULT(err_code);

    return err_code;
}


void ble_ipsp_incoming_channel_reject(uint16_t conn_handle)
{
    uint32_t peer_device_index = connected_device_search(conn_handle);

    if (peer_device_index != IPSP_MAX_CONNECTED_DEVICES)
    {
        m_connected_device[peer_device_index].response = INCOMING_CHANNEL_REJECT;
    }
}


void ble_ipsp_incoming_channel_accept(uint16_t conn_handle)
{
    uint32_t peer_device_index = connected_device_search(conn_handle);

    if (peer_device_index != IPSP_MAX_CONNECTED_DEVICES)
    {
        m_connected_device[peer_device_index].response = INCOMING_CHANNEL_ACCEPT;
    }
}
