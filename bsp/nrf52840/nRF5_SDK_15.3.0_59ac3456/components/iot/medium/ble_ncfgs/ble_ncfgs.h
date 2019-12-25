/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup ble_ncfgs Node Configuration Service
 * @{
 * @ingroup iot_sdk_common
 * @brief Node Configuration Service module.
 *
 * @details The Node Configuration Service allows configuration of the node during commissioning.
 *          During initialization it adds the Node Configuration Service and the corresponding
 *          characteristics to the BLE GATT database. It decodes and checks the received values
 *          and then passes them to the parent module.
 */

#ifndef BLE_NODE_CFG_H__
#define BLE_NODE_CFG_H__

#include <stdint.h>
#include "ble.h"
#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_UUID_NODE_CFG_SERVICE         0x7799
#define BLE_UUID_NCFGS_SSID_CHAR          0x77A9
#define BLE_UUID_NCFGS_KEYS_STORE_CHAR    0x77B9
#define BLE_UUID_NCFGS_CTRLPT_CHAR        0x77C9

#define APP_GATTERR_NOT_CONFIGURED        BLE_GATT_STATUS_ATTERR_APP_BEGIN + 1                      /**< ATT Error: Node configuration incomplete. */
#define APP_GATTERR_UNKNOWN_OPCODE        BLE_GATT_STATUS_ATTERR_APP_BEGIN + 2                      /**< ATT Error: Unknown opcode. */
#define APP_GATTERR_INVALID_ATTR_VALUE    BLE_GATT_STATUS_ATTERR_APP_BEGIN + 3                      /**< ATT Error: Invalid attribute value. */

#define NCFGS_SSID_MIN_LEN                6                                                         /**< SSID minimum length. */
#define NCFGS_SSID_MAX_LEN                16                                                        /**< SSID maximum length. */
#define NCFGS_KEYS_MAX_LEN                16                                                        /**< Keys maximum length. */
#define NCFGS_IDENTITY_DATA_MAX_LEN       8                                                         /**< Identity data maximum length. */

#define NCFGS_CTRLP_OPCODE_LEN            1                                                         /**< Ctrlp: Opcode value length. */
#define NCFGS_CTRLP_DELAY_LEN             4                                                         /**< Ctrlp: Length of action delay value. */
#define NCFGS_CTRLP_DURATION_LEN          4                                                         /**< Ctrlp: Length of next mode duration value. */
#define NCFGS_CTRLP_STATE_ON_FAILURE_LEN  1                                                         /**< Ctrlp: Length of state-on-failure value. */

#define NCFGS_CTRLP_ALL_BUT_ID_DATA_LEN   (NCFGS_CTRLP_OPCODE_LEN   +        \
                                           NCFGS_CTRLP_DELAY_LEN    +        \
                                           NCFGS_CTRLP_DURATION_LEN +        \
                                           NCFGS_CTRLP_STATE_ON_FAILURE_LEN)                        /**< Ctrlp: Total length of all values except identity data. */
#define NCFGS_CTRLP_VALUE_LEN             (NCFGS_CTRLP_OPCODE_LEN           +  \
                                           NCFGS_CTRLP_DELAY_LEN            +  \
                                           NCFGS_CTRLP_DURATION_LEN         +  \
                                           NCFGS_CTRLP_STATE_ON_FAILURE_LEN +  \
                                           NCFGS_IDENTITY_DATA_MAX_LEN)                             /**< Ctrlp: Total length of all values. */

#define HTONL(val)  ((((uint32_t) (val) & 0xff000000) >> 24)  |  \
                     (((uint32_t) (val) & 0x00ff0000) >> 8)   |  \
                     (((uint32_t) (val) & 0x0000ff00) << 8)   |  \
                     (((uint32_t) (val) & 0x000000ff) << 24))

/**@brief Node Configuration Service control point opcode values. */
typedef enum
{
    NCFGS_OPCODE_GOTO_JOINING_MODE  = 0x01,
    NCFGS_OPCODE_GOTO_CONFIG_MODE   = 0x02,
    NCFGS_OPCODE_GOTO_IDENTITY_MODE = 0x03
} ble_ncfgs_opcode_t;

/**@brief Node Configuration Service configuration states. */
typedef enum
{
    NCFGS_STATE_IDLE               = 0x00,
    NCFGS_STATE_SSID_WRITTEN       = 0x01,
    NCFGS_STATE_KEYS_STORE_WRITTEN = 0x02
} ble_ncfgs_state_t;

/**@brief Node Configuration Service state-on-failure values. */
typedef enum
{
    NCFGS_SOF_NO_CHANGE   = 0x00,
    NCFGS_SOF_PWR_OFF     = 0x01,
    NCFGS_SOF_CONFIG_MODE = 0x02
} state_on_failure_t;

/**@brief Structure for storing keys received from the peer. */
typedef struct __attribute__ ((__packed__))
{
    uint8_t             keys_len;
    uint8_t             keys[NCFGS_KEYS_MAX_LEN];                    // Keys received from the router.
} keys_store_t;

/**@brief Structure for storing the SSID received from the peer. */
typedef struct __attribute__ ((__packed__))
{
    uint8_t             ssid_len;
    uint8_t             ssid[NCFGS_SSID_MAX_LEN];                    // SSID received from the router.
} ssid_store_t;

/**@brief Structure for storing the identity data from the peer. */
typedef struct __attribute__ ((__packed__))
{
    uint8_t             identity_data_len;
    uint8_t             identity_data[NCFGS_IDENTITY_DATA_MAX_LEN];  // Custom node identifier data.
} id_data_store_t;

/**@brief Structure for control point value. */
typedef struct __attribute__ ((__packed__))
{
    ble_ncfgs_opcode_t  opcode;                                // Mode to start.
    uint32_t            delay_sec;                             // Delay before entering >Opcode< mode.
    uint32_t            duration_sec;                          // General timeout for >Opcode< mode.
    state_on_failure_t  state_on_failure;                      // Mode to enter if >Opcode< mode fails (times out).
} ble_ncfgs_ctrlp_value_t;

/**@brief Structure for storing Node Configuration Service characteristic values. */
typedef struct __attribute__ ((__packed__))
{
    ble_ncfgs_ctrlp_value_t  ctrlp_value;
    ssid_store_t             ssid_from_router;                 // SSID received from the peer.
    keys_store_t             keys_from_router;                 // Keys received from the peer.
    id_data_store_t          id_data;                          // Identity data received from the peer.
} ble_ncfgs_data_t;

/**@brief Function for handling BLE events.
 *
 * @details This function must be called from the BLE stack event dispatcher
 *          to handle BLE events that are relevant for the Node Configuration Service module.
 *          It propagates an event to the parent layer if the Control Point characteristic
 *          was successfully written.
 *
 * @param[in] p_ble_evt BLE stack event.
 */
void ble_ncfgs_ble_evt_handler(const ble_evt_t * p_ble_evt);

/**@brief Node Configuration Service event handler type. */
typedef void (*ble_ncfgs_evt_handler_t) (ble_ncfgs_data_t * ncfgs_data);

/**@brief Function for initializing the Node Configuration Service module.
 *
 * @details Interface for the Commissioning module to create a GATT database to
 *          allow for node configuration.
 *
 * @param[in]    ble_ncfgs_cb    Function to be called in case of an error.
 *
 * @retval       NRF_SUCCESS     If initialization was successful. Otherwise, a propagated
 *                               error code is returned.
 *
 */
uint32_t ble_ncfgs_init(ble_ncfgs_evt_handler_t ble_ncfgs_cb);

#ifdef __cplusplus
}
#endif

#endif // BLE_NODE_CFG_H__

/** @} */
