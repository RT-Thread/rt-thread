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

/**@file
 *
 * @defgroup ble_dis_c Device Information Service Client
 * @{
 * @ingroup  ble_sdk_srv
 * @brief    Device information Service Client module.
 *
 * @details  This module contains the APIs and types exposed by the Device information Service Client
 *           module. These APIs and types can be used by the application to perform discovery of
 *           the Device information Service at the peer and interact with it.
 *
 * @note    The application must register this module as BLE event observer using the
 *          NRF_SDH_BLE_OBSERVER macro. Example:
 *          @code
 *              ble_dis_c_t instance;
 *              NRF_SDH_BLE_OBSERVER(anything, BLE_DIS_C_BLE_OBSERVER_PRIO,
 *                                   ble_dis_c_on_ble_evt, &instance);
 *          @endcode
 *
 */


#ifndef BLE_DIS_C_H__
#define BLE_DIS_C_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_gatt.h"
#include "ble_db_discovery.h"
#include "ble_srv_common.h"
#include "ble_dis.h"
#include "nrf_sdh_ble.h"

#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_dis_c instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_DIS_C_DEF(_name)                          \
    static ble_dis_c_t _name;                         \
    NRF_SDH_BLE_OBSERVER(_name ## _obs,               \
                         BLE_DIS_C_BLE_OBSERVER_PRIO, \
                         ble_dis_c_on_ble_evt, &_name)

/** @brief Macro for defining multiple ble_dis_c instances.
 *
 * @param   _name   Name of the array of instances.
 * @param   _cnt    Number of instances to define.
 * @hideinitializer
 */
#define BLE_DIS_C_ARRAY_DEF(_name, _cnt)                     \
    static ble_dis_c_t _name[_cnt];                          \
    NRF_SDH_BLE_OBSERVERS(_name ## _obs,                     \
                          BLE_DIS_C_BLE_OBSERVER_PRIO,       \
                          ble_dis_c_on_ble_evt, &_name, _cnt)


/**@brief DIS Client event type. */
typedef enum
{
    BLE_DIS_C_EVT_DISCOVERY_COMPLETE,   /**< Event indicating that the DIS and its characteristics were discovered. See @ref ble_dis_c_evt_disc_complete_t. */
    BLE_DIS_C_EVT_DIS_C_READ_RSP,       /**< Event indicating that the client has received a read response from a peer. See @ref ble_dis_c_evt_read_rsp_t. */
    BLE_DIS_C_EVT_DIS_C_READ_RSP_ERROR, /**< Event indicating that the client's read request has failed. See @ref ble_dis_c_evt_read_rsp_err_t. */
    BLE_DIS_C_EVT_DISCONNECTED          /**< Event indicating that the DIS server has disconnected. */
} ble_dis_c_evt_type_t;

/**@brief DIS Client characteristic type. */
typedef enum
{
    BLE_DIS_C_MANUF_NAME,    /**< Manufacturer Name String characteristic. */
    BLE_DIS_C_MODEL_NUM,     /**< Model Number String characteristic. */
    BLE_DIS_C_SERIAL_NUM,    /**< Serial Number String characteristic. */
    BLE_DIS_C_HW_REV,        /**< Hardware Revision String characteristic. */
    BLE_DIS_C_FW_REV,        /**< Firmware Revision String characteristic. */
    BLE_DIS_C_SW_REV,        /**< Software Revision String characteristic. */
    BLE_DIS_C_SYS_ID,        /**< System ID characteristic. */
    BLE_DIS_C_CERT_LIST,     /**< IEEE 11073-20601 Regulatory Certification Data List characteristic. */
    BLE_DIS_C_PNP_ID,        /**< PnP ID characteristic. */
    BLE_DIS_C_CHAR_TYPES_NUM /**< Number of all possible characteristic types. */
} ble_dis_c_char_type_t;

/**@brief Attribute handle pointing to DIS characteristics on the connected peer device. */
typedef uint16_t ble_dis_c_handle_t;

/**@brief Event structure for @ref BLE_DIS_C_EVT_DISCOVERY_COMPLETE. */
typedef struct
{
    ble_dis_c_handle_t handles[BLE_DIS_C_CHAR_TYPES_NUM]; /**< Handles on the connected peer device needed to interact with it. */
} ble_dis_c_evt_disc_complete_t;

/**@brief Response data for string-based DIS characteristics. */
typedef struct
{
    uint8_t * p_data; /**< Pointer to response data. */
    uint8_t   len;    /**< Response data length. */
} ble_dis_c_string_t;

/**@brief Event structure for @ref BLE_DIS_C_EVT_DIS_C_READ_RSP. */
typedef struct
{
    ble_dis_c_char_type_t char_type; /**< Characteristic type. */
    ble_dis_c_handle_t    handle;    /**< Attribute handle from the response event. */
    union
    {
        ble_dis_c_string_t           string;    /**< String-based characteristics response data. Filled when char_type is in the following range: @ref BLE_DIS_C_MANUF_NAME - @ref BLE_DIS_C_SW_REV (inclusive). */
        ble_dis_sys_id_t             sys_id;    /**< System ID characteristic response data. Filled when char_type is @ref BLE_DIS_C_SYS_ID. */
        ble_dis_reg_cert_data_list_t cert_list; /**< IEEE 11073-20601 Regulatory Certification Data List characteristic response data. Filled when char_type is @ref BLE_DIS_C_CERT_LIST. */
        ble_dis_pnp_id_t             pnp_id;    /**< PnP ID characteristic response data. Filled when char_type is @ref BLE_DIS_C_PNP_ID. */
    } content;
} ble_dis_c_evt_read_rsp_t;

/**@brief Event structure for @ref BLE_DIS_C_EVT_DIS_C_READ_RSP_ERROR. */
typedef struct
{
    ble_dis_c_char_type_t char_type;   /**< Characteristic type. */
    ble_dis_c_handle_t    err_handle;  /**< Attribute handle from the response event. */
    uint16_t              gatt_status; /**< GATT status code for the read operation, see @ref BLE_GATT_STATUS_CODES. */
} ble_dis_c_evt_read_rsp_err_t;

/**@brief Structure containing the DIS event data received from the peer. */
typedef struct
{
    ble_dis_c_evt_type_t evt_type;    /**< Type of the event. */
    uint16_t             conn_handle; /**< Connection handle on which the @ref ble_dis_c_evt_t event occurred.*/
    union
    {
        ble_dis_c_evt_disc_complete_t disc_complete; /**< Discovery Complete Event Parameters. Filled when evt_type is @ref BLE_DIS_C_EVT_DISCOVERY_COMPLETE. */
        ble_dis_c_evt_read_rsp_t      read_rsp;      /**< Read Response Event Parameters. Filled when evt_type is @ref BLE_DIS_C_EVT_DIS_C_READ_RSP. */
        ble_dis_c_evt_read_rsp_err_t  read_rsp_err;  /**< Read Response Error Event Parameters. Filled when evt_type is @ref BLE_DIS_C_EVT_DIS_C_READ_RSP_ERROR. */
    } params;
} ble_dis_c_evt_t;

// Forward declaration of the ble_dis_t type.
typedef struct ble_dis_c_s ble_dis_c_t;

/**@brief   Event handler type.
 *
 * @details This is the type of the event handler that should be provided by the application
 *          of this module to receive events.
 */
typedef void (* ble_dis_c_evt_handler_t)(ble_dis_c_t * p_ble_dis_c, ble_dis_c_evt_t const * p_evt);

/**@brief DIS Client structure. */
struct ble_dis_c_s
{
    uint16_t                conn_handle;                       /**< Handle of the current connection. Set with @ref ble_dis_c_handles_assign when connected. */
    uint16_t                char_mask;                         /**< Mask with enabled DIS characteristics.*/
    ble_dis_c_handle_t      handles[BLE_DIS_C_CHAR_TYPES_NUM]; /**< Handles on the connected peer device needed to interact with it. */
    ble_srv_error_handler_t error_handler;                     /**< Application error handler to be called in case of an error. */
    ble_dis_c_evt_handler_t evt_handler;                       /**< Application event handler to be called when there is an event related to the DIS. */
};

/**@brief Structure describing the group of DIS characteristics with which this module can interact. */
typedef struct
{
    ble_dis_c_char_type_t * p_char_type; /**< Pointer to array with selected characteristics. */
    uint8_t                 size;        /**< Group size. */
} ble_dis_c_char_group_t;

/**@brief DIS Client initialization structure. */
typedef struct
{
    ble_dis_c_char_group_t  char_group;    /**< Group of DIS characteristics that should be enabled for this module instance. */
    ble_srv_error_handler_t error_handler; /**< Application error handler to be called in case of an error. */
    ble_dis_c_evt_handler_t evt_handler;   /**< Application event handler to be called when there is an event related to the Device Information service. */
} ble_dis_c_init_t;


/**@brief     Function for initializing the Device Information service client module.
 *
 * @details   This function registers with the Database Discovery module
 *            for the DIS. Doing so will make the Database Discovery
 *            module look for the presence of a DIS instance at the peer when a
 *            discovery is started.
 *
 * @param[in] p_ble_dis_c      Pointer to the DIS client structure.
 * @param[in] p_ble_dis_c_init Pointer to the DIS initialization structure containing the
 *                             initialization information.
 *
 * @retval    NRF_SUCCESS      If the module was initialized successfully.
 * @retval    NRF_ERROR_NULL   Any parameter is NULL.
 * @return    If functions from other modules return errors to this function
 *                        (@ref ble_db_discovery_evt_register), the @ref nrf_error are propagated.
 */
ret_code_t ble_dis_c_init(ble_dis_c_t * p_ble_dis_c, ble_dis_c_init_t * p_ble_dis_c_init);


/**@brief Function for handling events from the database discovery module.
 *
 * @details This function will handle an event from the database discovery module, and determine
 *          if it relates to the discovery of DIS at the peer. If so, it will
 *          call the application's event handler indicating that DIS has been
 *          discovered at the peer. It also populates the event with the service related
 *          information before providing it to the application.
 *
 * @param[in] p_ble_dis_c Pointer to the DIS client structure.
 * @param[in] p_evt       Pointer to the event received from the database discovery module.
 */
void ble_dis_c_on_db_disc_evt(ble_dis_c_t * p_ble_dis_c, ble_db_discovery_evt_t * p_evt);


/**@brief     Function for handling BLE events from the SoftDevice.
 *
 * @details   This function handles the BLE events received from the SoftDevice. If a BLE
 *            event is relevant to the DIS module, it is used to update internal variables
 *            and, if necessary, send events to the application.
 *
 * @param[in] p_ble_evt     Pointer to the BLE event.
 * @param[in] p_context     Pointer to the DIS client structure.
 */
void ble_dis_c_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief     Function for reading different characteristics from DIS.
 *
 * @details   This function can be used to read different characteristics that are available
 *            inside DIS. The response data will be provided from the response event
 *            @ref BLE_DIS_C_EVT_DIS_C_READ_RSP. The @ref BLE_DIS_C_EVT_DIS_C_READ_RSP_ERROR
 *            event can be generated if the read operation is unsuccessful.
 *
 * @param[in] p_ble_dis_c     Pointer to the DIS client structure.
 * @param[in] char_type       Type of characteristic to read.
 *
 * @retval    NRF_SUCCESS              If the operation was successful.
 * @retval    NRF_ERROR_NULL           If a \p p_ble_dis_c was a NULL pointer.
 * @retval    NRF_ERROR_INVALID_PARAM  If a \p char_type is not valid.
 * @retval    NRF_ERROR_INVALID_STATE  If connection handle or attribute handle is invalid.
 * @retval    NRF_ERROR_NO_MEM         If the client request queue is full.
 */
ret_code_t ble_dis_c_read(ble_dis_c_t * p_ble_dis_c, ble_dis_c_char_type_t char_type);


/**@brief Function for assigning handles to this instance of dis_c.
 *
 * @details Call this function when a link has been established with a peer to
 *          associate this link to this instance of the module. This makes it
 *          possible to handle several links and associate each link to a particular
 *          instance of this module. The connection handle and attribute handles will be
 *          provided from the discovery event @ref BLE_DIS_C_EVT_DISCOVERY_COMPLETE.
 *
 * @param[in] p_ble_dis_c    Pointer to the DIS client structure instance to associate with these
 *                           handles.
 * @param[in] conn_handle    Connection handle associated with the given DIS Instance.
 * @param[in] p_peer_handles Attribute handles on the DIS server that you want this DIS client to
 *                           interact with.
 *
 * @retval    NRF_SUCCESS    If the operation was successful.
 * @retval    NRF_ERROR_NULL If a \p p_ble_dis_c was a NULL pointer.
 */
ret_code_t ble_dis_c_handles_assign(ble_dis_c_t              * p_ble_dis_c,
                                    uint16_t                   conn_handle,
                                    ble_dis_c_handle_t const * p_peer_handles);


#ifdef __cplusplus
}
#endif

#endif // BLE_DIS_C_H__

/** @} */
