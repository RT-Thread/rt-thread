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
/** @file
 *
 * @defgroup nrf_ble_gatt GATT module
 * @{
 * @ingroup ble_sdk_lib
 * @brief Module for negotiating and keeping track of GATT connection parameters and updating the data length.
 */

#ifndef NRF_BLE_GATT_H__
#define NRF_BLE_GATT_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "ble.h"
#include "ble_gatt.h"
#include "sdk_config.h"
#include "sdk_errors.h"
#include "app_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a nrf_ble_gatt instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define NRF_BLE_GATT_DEF(_name)                                                                     \
static nrf_ble_gatt_t _name;                                                                        \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     NRF_BLE_GATT_BLE_OBSERVER_PRIO,                                                \
                     nrf_ble_gatt_on_ble_evt, &_name)

/**@brief   The maximum number of peripheral and central connections combined.
 *          This value is based on what is configured in the SoftDevice handler sdk_config.
 */
#define NRF_BLE_GATT_LINK_COUNT (NRF_SDH_BLE_PERIPHERAL_LINK_COUNT + NRF_SDH_BLE_CENTRAL_LINK_COUNT)


/**@brief   GATT module event types. */
typedef enum
{
  NRF_BLE_GATT_EVT_ATT_MTU_UPDATED     = 0xA77,  //!< The ATT_MTU size was updated.
  NRF_BLE_GATT_EVT_DATA_LENGTH_UPDATED = 0xDA7A, //!< The data length was updated.
} nrf_ble_gatt_evt_id_t;

/**@brief   GATT module event. */
typedef struct
{
    nrf_ble_gatt_evt_id_t evt_id;       //!< Event ID.
    uint16_t              conn_handle;  //!< Connection handle on which the event happened.
    union
    {
        uint16_t att_mtu_effective;     //!< Effective ATT_MTU.
#if !defined (S112)
        uint8_t  data_length;           //!< Data length value.
#endif // !defined (S112)
    } params;
} nrf_ble_gatt_evt_t;

// Forward declaration of the nrf_ble_gatt_t type.
typedef struct nrf_ble_gatt_s nrf_ble_gatt_t;

/**@brief   GATT module event handler type.
 *
 * The GATT module calls a function of this type when a parameter value is changed.
 */
typedef void (*nrf_ble_gatt_evt_handler_t) (nrf_ble_gatt_t * p_gatt, nrf_ble_gatt_evt_t const * p_evt);

/**@brief   GATT information for each connection. */
typedef struct
{
    uint16_t att_mtu_desired;               //!< Requested ATT_MTU size (in bytes).
    uint16_t att_mtu_effective;             //!< Effective ATT_MTU size (in bytes).
    bool     att_mtu_exchange_pending;      //!< Indicates that an ATT_MTU exchange request is pending (the call to @ref sd_ble_gattc_exchange_mtu_request returned @ref NRF_ERROR_BUSY).
    bool     att_mtu_exchange_requested;    //!< Indicates that an ATT_MTU exchange request was made.
#if !defined (S112)
    uint8_t  data_length_desired;           //!< Desired data length (in bytes).
    uint8_t  data_length_effective;         //!< Requested data length (in bytes).
#endif // !defined (S112)
} nrf_ble_gatt_link_t;


/**@brief   GATT structure that contains status information for the GATT module. */
struct nrf_ble_gatt_s
{
    uint16_t                   att_mtu_desired_periph;          //!< Requested ATT_MTU size for the next peripheral connection that is established.
    uint16_t                   att_mtu_desired_central;         //!< Requested ATT_MTU size for the next central connection that is established.
    uint8_t                    data_length;                     //!< Data length to use for the next connection that is established.
    nrf_ble_gatt_link_t        links[NRF_BLE_GATT_LINK_COUNT];  //!< GATT related information for all active connections.
    nrf_ble_gatt_evt_handler_t evt_handler;                     //!< GATT event handler.
};


/**@brief   Function for initializing the GATT module.
 *
 * @param[in]   evt_handler Event handler.
 * @param[out]  p_gatt      Pointer to the GATT structure.
 *
 * @retval NRF_SUCCESS      If the operation was successful.
 * @retval NRF_ERROR_NULL   If @p p_gatt is NULL.
 */
ret_code_t nrf_ble_gatt_init(nrf_ble_gatt_t * p_gatt, nrf_ble_gatt_evt_handler_t evt_handler);


/**@brief   Function for setting the ATT_MTU size for the next connection that is established as peripheral.
 *
 * @param[in]   p_gatt      Pointer to the GATT structure.
 * @param[in]   desired_mtu Requested ATT_MTU size.
 *
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval NRF_ERROR_NULL           If @p p_gatt is NULL.
 * @retval NRF_ERROR_INVALID_PARAM  If the size of @p desired_mtu is bigger than
 *                                  @ref NRF_SDH_BLE_GATT_MAX_MTU_SIZE or smaller than
 *                                  @ref BLE_GATT_ATT_MTU_DEFAULT.
 */
ret_code_t nrf_ble_gatt_att_mtu_periph_set(nrf_ble_gatt_t * p_gatt, uint16_t desired_mtu);


/**@brief   Function for setting the ATT_MTU size for the next connection that is established as central.
 *
 * @param[in,out]   p_gatt      Pointer to the GATT structure.
 * @param[in]       desired_mtu Requested ATT_MTU size.
 *
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval NRF_ERROR_NULL           If @p p_gatt is NULL.
 * @retval NRF_ERROR_INVALID_PARAM  If the size of @p desired_mtu is bigger than
 *                                  @ref NRF_SDH_BLE_GATT_MAX_MTU_SIZE or smaller
 *                                  than @ref BLE_GATT_ATT_MTU_DEFAULT.
 */
ret_code_t nrf_ble_gatt_att_mtu_central_set(nrf_ble_gatt_t * p_gatt, uint16_t desired_mtu);


/**@brief   Function for setting the data length for a connection.
 *
 * @details If @p conn_handle is a handle to an existing connection, a data length update
 *          request is sent on that connection.
 *          If @p conn_handle is @ref BLE_CONN_HANDLE_INVALID, a data length update request
 *          is sent on the next connection that is established after the ATT_MTU
 *          exchange has completed. If no ATT_MTU exchange procedure is carried
 *          out (for example, if a default ATT_MTU size is used), the data length
 *          is not changed.
 */
#if !defined (S112)
ret_code_t nrf_ble_gatt_data_length_set(nrf_ble_gatt_t * p_gatt,
                                        uint16_t         conn_handle,
                                        uint8_t          data_length);
#endif // !defined (S112)

/**@brief   Function for retrieving the data length of a connection.
 *
 * @details If @p conn_handle is @ref BLE_CONN_HANDLE_INVALID, the function retrieves the data
 *          length that will be requested for the next connection.
 *          If @p conn_handle is a handle to an existing connection, the function retrieves
 *          the effective data length that was negotiated for that connection.
 *
 * @param[in,out]   p_gatt          Pointer to the GATT structure.
 * @param[in]       conn_handle     The connection for which to retrieve the data length, or
 *                                  @ref BLE_CONN_HANDLE_INVALID to retrieve the requested data length
 *                                  for the next connection.
 * @param[out]      p_data_length   The connection data length.
 *
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval NRF_ERROR_NULL           If @p p_gatt or @p p_data_length is NULL.
 * @retval NRF_ERROR_INVALID_PARAM  If @p conn_handle is larger than @ref NRF_BLE_GATT_LINK_COUNT.
 */
#if !defined (S112)
ret_code_t nrf_ble_gatt_data_length_get(nrf_ble_gatt_t const * p_gatt,
                                        uint16_t               conn_handle,
                                        uint8_t              * p_data_length);
#endif // !defined (S112)

/**@brief   Function for handling BLE stack events.
 *
 * @details This function handles events from the BLE stack that are of interest to the module.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Pointer to the GATT structure.
 */
void nrf_ble_gatt_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief   Function for getting the current ATT_MTU size for a given connection.
 *
 * @param[in]   p_gatt      Pointer to the GATT structure.
 * @param[in]   conn_handle Connection handle of the connection.
 *
 * @return  ATT_MTU size for the given connection.
 * @retval  0       If @p p_gatt is NULL or if @p conn_handle is larger than
 *                  the supported maximum number of connections.
 */
uint16_t nrf_ble_gatt_eff_mtu_get(nrf_ble_gatt_t const * p_gatt, uint16_t conn_handle);


#ifdef __cplusplus
}
#endif

#endif // NRF_BLE_GATT_H__

/** @} */
