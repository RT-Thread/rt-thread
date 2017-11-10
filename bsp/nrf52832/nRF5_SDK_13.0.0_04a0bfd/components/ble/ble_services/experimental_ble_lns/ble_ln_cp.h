/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
 * @defgroup ble_sdk_srv_lncp Location and Navigation Service Control Point
 * @{
 * @ingroup ble_sdk_srv
 * @brief Location and Navigation Service Control Point module
 *
 * @details This module implements the Location and Navigation Service Control Point behavior.
 */

#ifndef BLE_LN_CTRLPT_H__
#define BLE_LN_CTRLPT_H__

#include "ble_srv_common.h"
#include "sdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_LNS_MAX_ROUTE_NAME_LEN                                  BLE_GATT_ATT_MTU_DEFAULT - 5    /**< The maximum length of length of a route name. */
#define MAX_CTRL_POINT_RESP_PARAM_LEN                               BLE_LNS_MAX_ROUTE_NAME_LEN + 3  /**< Maximum length of a control point response. */

typedef struct ble_lncp_s ble_lncp_t;

/** @brief Location and Navigation event type. This list defines the possible events types from the Location and Navigation Service. */
typedef enum
{
    LNCP_EVT_ELEVATION_SET,        /**< Location and Navigation elevation was set. */
    LNCP_EVT_FIX_RATE_SET,         /**< Fix rate was set. */
    LNCP_EVT_ROUTE_SELECTED,       /**< A route was selected. */
    LNCP_EVT_NAV_COMMAND,          /**< A navigation command was issued. */
    LNCP_EVT_MASK_SET,             /**< Location and Speed feature mask was set. */
    LNCP_EVT_TOTAL_DISTANCE_SET   /**< Location and Navigation total distance was set. */
} ble_lncp_evt_type_t;


/** @brief Navigation commands. These commands can be sent to the control point and returned by an event callback. */
typedef enum
{
    LNCP_CMD_NAV_STOP          = 0x00,        /**< When received, is_navigation_running in @ref ble_lns_s will be set to false. */
    LNCP_CMD_NAV_START         = 0x01,        /**< When received, is_navigation_running in @ref ble_lns_s will be set to true. */
    LNCP_CMD_NAV_PAUSE         = 0x02,        /**< When received, is_navigation_running in @ref ble_lns_s will be set to false. */
    LNCP_CMD_NAV_CONTINUE      = 0x03,        /**< When received, is_navigation_running in @ref ble_lns_s will be set to true. */
    LNCP_CMD_NAV_SKIP_WAYPOINT = 0x04,        /**< When received, is_navigation_running in @ref ble_lns_s will not be affected. */
    LNCP_CMD_NAV_NEAREST       = 0x05,        /**< When received, is_navigation_running in @ref ble_lns_s will be set to true. */
} ble_lncp_nav_cmd_t;
#define LNCP_NAV_CMD_MAX 0x05
#define LNCP_NAV_CMD_LEN (OPCODE_LENGTH + 1)


#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#endif

/** @brief A mask can be used to temporarily enable and disable features of the Location and Speed characteristic.*/
typedef union
{
    uint8_t flags;
    struct
    {
        uint8_t instantaneous_speed :1;
        uint8_t total_distance      :1;
        uint8_t location            :1;
        uint8_t elevation           :1;
        uint8_t heading             :1;
        uint8_t rolling_time        :1;
        uint8_t utc_time            :1;
    };
} ble_lncp_mask_t;

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#endif

typedef struct
{
    ble_lncp_evt_type_t evt_type;
    union
    {
        ble_lncp_mask_t     mask;
        ble_lncp_nav_cmd_t  nav_cmd;
        uint32_t            total_distance;
        uint8_t             fix_rate;
        uint16_t            selected_route;
        uint32_t            elevation;
    } params;
} ble_lncp_evt_t;


// Location and Navigation Control Point response values
typedef enum
{
    LNCP_RSP_RESERVED              = 0x00,                                        /**< Reserved for future use. */
    LNCP_RSP_SUCCESS               = 0x01,                                        /**< Success. */
    LNCP_RSP_OP_CODE_NOT_SUPPORTED = 0x02,                                        /**< Op Code not supported. */
    LNCP_RSP_INVALID_PARAMETER     = 0x03,                                        /**< Invalid Parameter. */
    LNCP_RSP_OPERATION_FAILED      = 0x04,                                        /**< Operation Failed. */
    LNCP_RSP_PROC_ALR_IN_PROG      = BLE_GATT_STATUS_ATTERR_CPS_PROC_ALR_IN_PROG, /**< Control point procedure is already in progress. */
    LNCP_RSP_CCCD_CONFIG_IMPROPER  = BLE_GATT_STATUS_ATTERR_CPS_CCCD_CONFIG_ERROR /**< CCCD is improperly configured. */
} ble_lncp_rsp_code_t;


typedef ble_lncp_rsp_code_t (*ble_lncp_evt_handler_t) (ble_lncp_t const * p_lncp, ble_lncp_evt_t const * p_evt);

// Location and Navigation Control Point Op Code values
typedef enum
{
    LNCP_OP_RESERVED                         = 0x00, /**< Reserved for future use. */
    LNCP_OP_SET_CUMULATIVE_VALUE             = 0x01, /**< Set Cumulative Value. */
    LNCP_OP_MASK_LOC_SPEED_CONTENT           = 0x02, /**< Mask Location and Speed Characteristic Content. */
    LNCP_OP_NAV_CONTROL                      = 0x03, /**< Navigation Control. */
    LNCP_OP_REQ_NUM_ROUTES                   = 0x04, /**< Request Number of Routes. */
    LNCP_OP_REQ_NAME_OF_ROUTE                = 0x05, /**< Request Name of Route. */
    LNCP_OP_SELECT_ROUTE                     = 0x06, /**< Select Route. */
    LNCP_OP_SET_FIX_RATE                     = 0x07, /**< Set Fix Rate. */
    LNCP_OP_SET_ELEVATION                    = 0x08, /**< Set Elevation. */
    LNCP_OP_RESPONSE_CODE                    = 0x20  /**< Response code. */
} ble_lncp_op_code_t;


/** @brief Location and Navigation Control Point procedure status */
typedef enum
{
    LNCP_STATE_NO_PROC_IN_PROGRESS,                        /**< No procedure in progress. */
    LNCP_STATE_INDICATION_PENDING,                         /**< Control Point indication is pending. */
    LNCP_STATE_CONFIRMATION_PENDING,                 /**< Waiting for the indication confirmation. */
} ble_lncp_procedure_status_t;


/** @brief Information included in a control point write response indication. */
typedef struct
{
    ble_lncp_op_code_t  op_code;             /**< Opcode of the control point write action. */
    ble_lncp_rsp_code_t rsp_code;            /**< Response code of the control point write action. */
    uint8_t             rsp_param_len;
    uint8_t             rsp_param[MAX_CTRL_POINT_RESP_PARAM_LEN];
} ble_lncp_rsp_t;


typedef struct
{
    uint16_t                    service_handle;
    ble_lncp_evt_handler_t      evt_handler;
    ble_srv_error_handler_t     error_handler;

    uint32_t                    available_features;                      /**< Value of the LN feature. */
    bool                        is_position_quality_present;             /**< If set to true, the position quality characteristic will be added. Else not. */
    bool                        is_control_point_present;                /**< If set to true, the control point characteristic will be added. Else not. */
    bool                        is_navigation_present;                   /**< If set to true, the navigation characteristic will be added. Else not. */
    ble_gatts_char_handles_t    navigation_handles;

    uint32_t                    total_distance;
    uint32_t                    elevation;

    security_req_t              write_perm;
    security_req_t              cccd_write_perm;
} ble_lncp_init_t;


struct ble_lncp_s
{
    uint16_t                    conn_handle;
    uint16_t                    service_handle;
    ble_gatts_char_handles_t    ctrlpt_handles;
    ble_gatts_char_handles_t    navigation_handles;
    ble_lncp_evt_handler_t      evt_handler;
    ble_srv_error_handler_t     error_handler;
    ble_lncp_procedure_status_t procedure_status;
    ble_lncp_rsp_t              pending_rsp;

    ble_lncp_mask_t             mask;
    uint32_t                    total_distance;
    uint32_t                    elevation;
    uint8_t                     fix_rate;
    uint16_t                    selected_route;
    uint32_t                    available_features;             /**< Value of the LN feature. */
    bool                        is_position_quality_present;    /**< If set to true, the position quality characteristic will be added. Else not. */
    bool                        is_control_point_present;       /**< If set to true, the control point characteristic will be added. Else not. */
    bool                        is_navigation_present;          /**< If set to true, the navigation characteristic will be added. Else not. */
    bool                        is_navigation_running;          /**< This variable can be set using the control point. Must be true to be able to send navigation updates. */

    bool                        is_ctrlpt_indication_enabled;   /**< True if indication is enabled on the Control Point characteristic. */
    bool                        is_nav_notification_enabled;    /**< True if notification is enabled on the Navigation characteristic. */
};


void ble_lncp_on_ble_evt(ble_lncp_t * p_lncp, ble_evt_t const * p_ble_evt);

uint32_t ble_lncp_total_distance_get(ble_lncp_t const * p_lncp);

uint32_t ble_lncp_elevation_get(ble_lncp_t const * p_lncp);

ble_lncp_mask_t ble_lncp_mask_get(ble_lncp_t const * p_lncp);

bool ble_lncp_is_navigation_running(ble_lncp_t const * p_lncp);

ret_code_t ble_lncp_init(ble_lncp_t * p_lncp, ble_lncp_init_t const * p_lncp_init);


#ifdef __cplusplus
}
#endif

#endif //BLE_LN_CTRLPT_H__

/** @} */
