/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
 * @defgroup ble_ots Object Transfer Service
 * @{
 * @ingroup  ble_sdk_srv
 * @brief    Object Transfer Service module
 *
 * @details  This is the main module of the OTS service.
 */

#ifndef BLE_OTS_H__
#define BLE_OTS_H__

#include <stdint.h>
#include "ble_srv_common.h"
#include "ble_date_time.h"
#include "ble_hvx_buffering.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_ots instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_OTS_DEF(_name)                                                                          \
static ble_ots_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _ble_obs,                                                             \
                     BLE_OTS_BLE_OBSERVER_PRIO,                                                     \
                     ble_ots_on_ble_evt, &_name)                                                    \


#define NRF_BLE_OTS_SIZE_CHAR_LEN       (2*sizeof(uint32_t))
#define BLE_OTS_FEATURE_LEN             (2*sizeof(uint32_t))
#define BLE_OTS_NAME_MAX_SIZE           128
#define BLE_OTS_MAX_OBJ_SIZE            1028
#define BLE_OTS_INVALID_CID             0x0000 /**< Invalid connection ID. */
#define BLE_OTS_PSM                     0x0025
#define BLE_OTS_MAX_OACP_SIZE           21
#define BLE_OTS_WRITE_MODE_TRUNCATE     (1 << 1)
#define BLE_OTS_WRITE_MODE_NO_TRUNCATE  0

// Forward declarations.
typedef struct ble_ots_s ble_ots_t;
typedef struct ble_ots_oacp_s ble_ots_oacp_t;
typedef struct ble_ots_l2cap_s ble_ots_l2cap_t;


/*------------------------------------------ BLE OTS OBJECT --------------------------------------*/

/**@brief Properties of an Object Transfer Service object. */
typedef union
{
    struct
    {
        bool is_delete_permitted  :1;
        bool is_execute_permitted :1;
        bool is_read_permitted    :1;
        bool is_write_permitted   :1;
        bool is_append_permitted  :1;
        bool is_truncate_permitted:1; /**< When writing using truncate mode, and the written length is shorter than the object, the object size is decreased. */
        bool is_patch_permitted   :1; /**< When patching, a part of the object is replaced. */
        bool is_marked            :1;
    } decoded;
    uint32_t raw;
} ble_ots_obj_properties_t;

/**@brief A structure representing the object type. */
typedef struct
{
    uint8_t len;                                            /**< The length of the object type in bytes. 2 and 16 are the only valid type lengths. */
    union
    {
        uint16_t type16;
        uint8_t  type128[16];
    } param;
} ble_ots_obj_type_t;

/**@brief The structure representing one Object Transfer Service object. */
typedef struct
{
    uint8_t                  name[BLE_OTS_NAME_MAX_SIZE];    /**< The name of the object. If the name is "", the object will be invalidated on disconnect. */
    uint8_t                  data[BLE_OTS_MAX_OBJ_SIZE];
    ble_ots_obj_type_t       type;
    ble_ots_obj_properties_t properties;
    uint32_t                 current_size;
    uint32_t                 alloc_len;
    bool                     is_valid;                       /**< States if the object will be shown in a list. */
    bool                     is_locked;                      /**< When an object is written or read, the object will be locked. */
} ble_ots_object_t;

/**@brief The definition of an event from the object characteristics. */
typedef struct
{
    enum
    {
        BLE_OTS_OBJECT_EVT_NAME_CHANGED,
        BLE_OTS_OBJECT_EVT_PROPERTIES_CHANGED,
    } type;
    union
    {
        ble_ots_object_t * p_object;
    } evt;
} ble_ots_object_evt_t;

/**@brief Initialization properties of the Object Transfer Service Object characteristics. */
typedef struct
{
    ble_ots_t      * p_ots;
    security_req_t   name_read_access;
    security_req_t   name_write_access;
    security_req_t   type_read_access;
    security_req_t   size_read_access;
    security_req_t   properties_read_access;
    security_req_t   properties_write_access;
} ble_ots_object_chars_init_t;

/**@brief The structure holding the state of the OTS object characteristics. */
typedef struct
{
    ble_ots_t                * p_ots;
    ble_gatts_char_handles_t   obj_name_handles;
    ble_gatts_char_handles_t   obj_type_handles;
    ble_gatts_char_handles_t   obj_size_handles;
    ble_gatts_char_handles_t   obj_properties_handles;
} ble_ots_object_chars_t;


/*------------------------------------------ BLE OTS L2CAP ---------------------------------------*/

/**@brief L2cap event types. */
typedef enum
{
    BLE_OTS_L2CAP_EVT_CH_CONNECTED,
    BLE_OTS_L2CAP_EVT_CH_DISCONNECTED,
    BLE_OTS_L2CAP_EVT_SEND_COMPLETE,
    BLE_OTS_L2CAP_EVT_RECV_COMPLETE,
} ble_ots_l2cap_evt_type_t;

/**@brief l2cap event. */
typedef struct
{
    ble_ots_l2cap_evt_type_t type;
    struct
    {
        uint8_t  * p_data;
        uint16_t   len;
    } param;
} ble_ots_l2cap_evt_t;

/**@brief L2CAP event handler. */
typedef void (*ble_ots_l2cap_evt_handler_t)(ble_ots_l2cap_t     * p_ots_l2cap,
                                            ble_ots_l2cap_evt_t * p_evt);

/**@brief The structure holding the l2cap connection oriented channels state. */
struct ble_ots_l2cap_s
{
    ble_ots_l2cap_evt_handler_t   evt_handler;
    ble_ots_oacp_t              * p_ots_oacp;
    enum
    {
        NOT_CONNECTED,
        CONNECTED,
        SENDING,
        RECEIVING
    } state;
    ble_data_t               tx_transfer_buffer;
    ble_l2cap_ch_rx_params_t rx_params;
    ble_l2cap_ch_tx_params_t tx_params;
    uint16_t                 remaining_bytes;       /**< The number of remaining bytes in the current transfer. */
    uint16_t                 transfered_bytes;
    uint16_t                 transfer_len;          /**< The total number of bytes in the current transfer. */
    uint16_t                 local_cid;             /**< Connection id of the current connection. */
    uint16_t                 conn_mtu;              /**< The maximum transmission unit, that is the number of packets that can be sent or received. */
    uint16_t                 conn_mps;              /**< MPS defines the maximum payload size in bytes. */
};

/**@brief The initialization structure of the l2cap module. */
typedef struct
{
    ble_ots_oacp_t              * p_ots_oacp;
    ble_ots_l2cap_evt_handler_t   evt_handler;
    uint8_t                     * p_transfer_buffer;    /**< The user must provide buffer for transfers. */
    uint16_t                      buffer_len;           /**< Length of the transfer buffer. */
} ble_ots_l2cap_init_t;


/*------------------------------------------ BLE OTS OCAP ----------------------------------------*/

/**< Types of Object Action Control Point Procedures. */
typedef enum
{
    BLE_OTS_OACP_PROC_CREATE        = 0x01, //!< Create object.
    BLE_OTS_OACP_PROC_DELETE        = 0x02, //!< Delete object.
    BLE_OTS_OACP_PROC_CALC_CHKSUM   = 0x03, //!< Calculate Checksum.
    BLE_OTS_OACP_PROC_EXECUTE       = 0x04, //!< Execute Object.
    BLE_OTS_OACP_PROC_READ          = 0x05, //!< Read object.
    BLE_OTS_OACP_PROC_WRITE         = 0x06, //!< Write object.
    BLE_OTS_OACP_PROC_ABORT         = 0x07, //!< Abort object.
    BLE_OTS_OACP_PROC_RESP          = 0x60  //!< Procedure response.
} ble_ots_oacp_proc_type_t;

/**< Object Action Control Point return codes. */
typedef enum
{
    BLE_OTS_OACP_RES_SUCCESS        = 0x01, //!< Success.
    BLE_OTS_OACP_RES_OPCODE_NOT_SUP = 0x02, //!< Not supported
    BLE_OTS_OACP_RES_INV_PARAM      = 0x03, //!< Invalid parameter
    BLE_OTS_OACP_RES_INSUFF_RES     = 0x04, //!< Insufficient resources.
    BLE_OTS_OACP_RES_INV_OBJ        = 0x05, //!< Invalid object.
    BLE_OTS_OACP_RES_CHAN_UNAVAIL   = 0x06, //!< Channel unavailable.
    BLE_OTS_OACP_RES_UNSUP_TYPE     = 0x07, //!< Unsupported procedure.
    BLE_OTS_OACP_RES_NOT_PERMITTED  = 0x08, //!< Procedure not permitted.
    BLE_OTS_OACP_RES_OBJ_LOCKED     = 0x09, //!< Object locked.
    BLE_OTS_OACP_RES_OPER_FAILED    = 0x0A  //!< Operation Failed.
} ble_ots_oacp_res_code_t;

/**< Object Action Control Point procedure definition. */
typedef struct
{
    ble_ots_oacp_proc_type_t type;
    union
    {
        struct
        {
            uint32_t size;
            ble_ots_obj_type_t * p_obj_type;
        } create_params;
        struct
        {
            uint32_t offset;
            uint32_t length;
        } checksum_params;
        struct
        {
            uint8_t cmd_data_len;
            uint8_t * p_cmd_data;
        } execute_params;
        struct
        {
            uint32_t offset;
            uint32_t length;
        } read_params;
        struct
        {
            uint32_t offset;
            uint32_t length;
            uint8_t  write_mode;
        } write_params;
    } params;
} ble_ots_oacp_proc_t;

/**@brief Definition of an OACP event. */
typedef struct
{
    enum
    {
        BLE_OTS_OACP_EVT_EXECUTE,
        BLE_OTS_OACP_EVT_REQ_READ,
        BLE_OTS_OACP_EVT_INCREASE_ALLOC_LEN,
        BLE_OTS_OACP_EVT_REQ_WRITE,
        BLE_OTS_OACP_EVT_ABORT,
    } type;
    union
    {
        ble_ots_object_t * p_object;
        struct
        {
            uint8_t   cmd_data_len;
            uint8_t * p_cmd_data;
        } execute_params;
    } evt;
} ble_ots_oacp_evt_t;

/**@brief OACP initialization properties. */
typedef struct
{
    ble_ots_t                * p_ots;
    uint32_t                   on_create_obj_properties_raw;    /**< The encoded properties of a newly created object.*/
    security_req_t             write_access;                    /**< The write security level for the OACP. */
    security_req_t             cccd_write_access;               /**< The write security level for the OACP CCCD. */
    uint8_t                  * p_l2cap_buffer;
    uint16_t                   l2cap_buffer_len;
} ble_ots_oacp_init_t;

struct ble_ots_oacp_s
{
    ble_ots_t                  * p_ots;
    uint32_t                     on_create_obj_properties_raw;  /**< The encoded properties of a newly created object.*/
    ble_ots_l2cap_t              ots_l2cap;                     /**< L2CAP connection oriented channel module. */
    ble_gatts_char_handles_t     oacp_handles;                  /**< The characteristic handles of the OACP. */
};


/*------------------------------------------ BLE OTS ---------------------------------------------*/

/**@brief The event type indicates which module the event is connected to.*/
typedef enum
{
    BLE_OTS_EVT_OACP,
    BLE_OTS_EVT_OBJECT,
    BLE_OTS_EVT_INDICATION_ENABLED,
    BLE_OTS_EVT_INDICATION_DISABLED,
    BLE_OTS_EVT_OBJECT_RECEIVED                                 /**< If this event is received, data is now available in the current object.*/
} ble_ots_evt_type_t;

/**@brief This structure represents the state of the Object Transfer Service. */
typedef struct
{
    ble_ots_evt_type_t type;
    union
    {
        ble_ots_oacp_evt_t   oacp_evt;
        ble_ots_object_evt_t object_evt;

    } evt;                                                      /**< Event data. */
} ble_ots_evt_t;

/**@brief OTS event handler. */
typedef void (*ble_ots_evt_handler_t) (ble_ots_t * p_ots, ble_ots_evt_t * p_evt);

/**@brief Structure for initializing the OTS. */
typedef struct
{
    ble_ots_evt_handler_t         evt_handler;
    ble_srv_error_handler_t       error_handler;
    ble_ots_object_t            * p_object;                     /**< Pointer to the object. */
    security_req_t                feature_char_read_access;     /**< Read security level for the feature characteristic value. */
    ble_ots_object_chars_init_t   object_chars_init;            /**< The initialization structure of the object characteristics. */
    ble_ots_oacp_init_t           oacp_init;                    /**< The initialization structure of the object action control point. */
    uint16_t                     rx_mps;                        /**< Size of L2CAP Rx MPS (must be at least BLE_L2CAP_MPS_MIN).*/
    uint16_t                     rx_mtu;                        /**< Size of L2CAP Rx MTU (must be at least BLE_L2CAP_MTU_MIN).*/
} ble_ots_init_t;

struct ble_ots_s
{
    uint16_t                     conn_handle;                   /**< Connection handle of service. */
    uint16_t                     service_handle;                /**< THe service handle of OTS. */
    ble_ots_evt_handler_t        evt_handler;
    ble_srv_error_handler_t      error_handler;
    ble_gatts_char_handles_t     feature_handles;
    ble_ots_object_chars_t       object_chars;                  /**< The structure holding the object characteristics representation. */
    ble_ots_oacp_t               oacp_chars;                    /**< The structure holding the object action control point characteristics representation. */
    ble_ots_object_t           * p_current_object;              /**< Pointer to the currently selected object. */
    ble_hvx_buf_t                hvx_buf;                       /**< A buffer holding unsent handle value indications/notifications. */
};


/**@brief Function for initializing the Object Transfer Service.
 *
 * @param[out]  p_ots       Object Transfer Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_ots_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_ots_init(ble_ots_t * p_ots, ble_ots_init_t * p_ots_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Object Transfer Service.
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Object Transfer Service structure.
 */
void ble_ots_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);

/**@brief Function for setting the name of an object.
 *
 * @details     If p_object is the current selected object, and the notifications is enabled, the client will be notified that the object has changed.
 * @note        If the name of the object is "" on disconnection, the object will be invalidated.
 *
 * @param[in]   p_ots_object_chars  Object Transfer Service Object Characteristics structure.
 * @param[in]   p_object            Pointer to the object where the name will be changed.
 * @param[in]   new_name            The new name of the object.
 *
 * @return      NRF_SUCCESS         On success, otherwise an error code.
 */
uint32_t ble_ots_object_set_name(ble_ots_object_chars_t * p_ots_object_chars,
                                 ble_ots_object_t       * p_object,
                                 char const             * new_name);

/**@brief Function for setting the type of an object.
 *
 * @details     If p_object is the current selected object, and the notifications is enabled, the client will be notified that the object has changed.
 * @param[in]   p_ots_object_chars  Object Transfer Service Object Characteristics structure.
 * @param[in]   p_object            Pointer to the object where the type will be changed.
 * @param[in]   p_new_type          Pointer to the new type of the object.
 *
 * @return      NRF_SUCCESS         On success, otherwise an error code.
 */
uint32_t ble_ots_object_set_type(ble_ots_object_chars_t * p_ots_object_chars,
                                 ble_ots_object_t       * p_object,
                                 ble_ots_obj_type_t     * p_new_type);

/**@brief Function for setting the current size of an object.
 *
 * @details     If p_object is the current selected object, and the notifications is enabled, the client will be notified that the object has changed.
 * @note        If the new current size is smaller than the current size, the object will be truncated.
 *
 * @param[in]   p_ots_object_chars  Object Transfer Service Object Characteristics structure.
 * @param[in]   p_object            Pointer to the object where the current size will be changed.
 * @param[in]   new_current_size    The new current size of the object.
 *
 * @return      NRF_SUCCESS         On success, otherwise an error code.
 */
uint32_t ble_ots_object_set_current_size(ble_ots_object_chars_t * p_ots_object_chars,
                                         ble_ots_object_t       * p_object,
                                         uint32_t                 new_current_size);

/**@brief Function for setting the properties of an object.
 *
 * @details     If p_object is the current selected object, and the notifications is enabled, the client will be notified that the object has changed.
 *
 * @param[in]   p_ots_object_chars Object Transfer Service Object Characteristics structure.
 * @param[in]   p_object           Pointer to the object where the properties will be changed.
 * @param[in]   p_new_properties   The properties of the object.
 *
 * @return      NRF_SUCCESS         On success, otherwise an error code.
 */
uint32_t ble_ots_object_set_properties(ble_ots_object_chars_t   * p_ots_object_chars,
                                       ble_ots_object_t         * p_object,
                                       ble_ots_obj_properties_t * p_new_properties);



#endif // BLE_OTS_H__

/** @} */
