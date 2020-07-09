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
 * @defgroup ble_lns Location and Navigation Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Location and Navigation Service module.
 *
 * @details This module implements the Location and Navigation Service with the Location and Speed, Position
 *          Quality, Feature, Control Point, and Navigation characteristics.
 *
 *          If an event handler is supplied by the application, the Location and Navigation Service will
 *          generate Location and Navigation Service events to the application.
 *
 * @note The application must propagate BLE stack events to the Location and Navigation Service module by calling
 *       @ref ble_lns_on_ble_evt() from the from the ble_stack_handler callback.
 */

#ifndef BLE_LNS_H__
#define BLE_LNS_H__

#include "ble_srv_common.h"
#include "ble_date_time.h"
#include "ble_ln_common.h"
#include "ble_ln_cp.h"
#include "sdk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Location and Navigation event type. This list defines the possible events types from the Location and Navigation Service. */
typedef enum {
    BLE_LNS_CTRLPT_EVT_INDICATION_ENABLED,         /**< Control Point value indication was enabled. */
    BLE_LNS_CTRLPT_EVT_INDICATION_DISABLED,        /**< Control Point value indication was disabled. */
    BLE_LNS_LOC_SPEED_EVT_NOTIFICATION_ENABLED,     /**< Location and Speed value notification was enabled. */
    BLE_LNS_LOC_SPEED_EVT_NOTIFICATION_DISABLED,    /**< Location and Speed value notification was disabled. */
    BLE_LNS_NAVIGATION_EVT_NOTIFICATION_ENABLED,    /**< Navigation value notification was enabled. */
    BLE_LNS_NAVIGATION_EVT_NOTIFICATION_DISABLED,   /**< Navigation value notification was disabled. */
} ble_lns_evt_type_t;

/** @brief Location and Navigation event structure. When an event occurs, the data structures of the module are automatically updated. */
typedef struct {
    ble_lns_evt_type_t               evt_type;
} ble_lns_evt_t;

// Forward declarations of the ble_lns types.
typedef struct ble_lns_init_s        ble_lns_init_t;
typedef struct ble_lns_s             ble_lns_t;
typedef struct ble_lns_loc_speed_s   ble_lns_loc_speed_t;
typedef struct ble_lns_pos_quality_s ble_lns_pos_quality_t;
typedef struct ble_lns_navigation_s  ble_lns_navigation_t;


typedef struct {
    bool     is_pending;
    uint16_t handle;
    uint16_t len;
#if (NRF_SD_BLE_API_VERSION <= 3)
    uint8_t  data[GATT_MTU_SIZE_DEFAULT];
#else
    uint8_t  data[BLE_GATT_ATT_MTU_DEFAULT];
#endif
} notification_t;


/**@brief Location and Navigation Service event handler type. */
typedef void (*ble_lns_evt_handler_t) (ble_lns_t const * p_lns, ble_lns_evt_t const * p_evt);


/**@brief Location and Navigation Service init structure. This structure contains all options and data needed to
 *        initialize the service. */
struct ble_lns_init_s
{
    ble_lns_evt_handler_t       evt_handler;                             /**< Event handler to be called for handling events in the Location and Navigation Service. */
    ble_lncp_evt_handler_t      lncp_evt_handler;
    ble_srv_error_handler_t     error_handler;                           /**< Errors will be sent back to this function. */

    bool                        is_position_quality_present;             /**< If set to true, the position quality characteristic will be added. Else not. */
    bool                        is_control_point_present;                /**< If set to true, the control point characteristic will be added. Else not. */
    bool                        is_navigation_present;                   /**< If set to true, the navigation characteristic will be added. Else not. */

    security_req_t              loc_nav_feature_security_req_read_perm;  /**< Read security level of the LN Feature characteristic. */
    security_req_t              loc_speed_security_req_cccd_write_perm;  /**< CCCD write security level of the Write Location and Speed characteristic. */
    security_req_t              position_quality_security_req_read_perm; /**< Read security level of the Position Quality characteristic. */
    security_req_t              navigation_security_req_cccd_write_perm; /**< CCCD write security level of the Navigation characteristic. */
    security_req_t              ctrl_point_security_req_write_perm;      /**< Read security level of the LN Control Point characteristic. */
    security_req_t              ctrl_point_security_req_cccd_write_perm; /**< CCCD write security level of the LN Control Point characteristic. */

    uint32_t                    available_features;                      /**< Value of the LN feature. */
    ble_lns_loc_speed_t         * p_location_speed;                      /**< Initial Location and Speed. */
    ble_lns_pos_quality_t       * p_position_quality;                    /**< Initial Position Quality. */
    ble_lns_navigation_t        * p_navigation;                          /**< Initial Navigation data structure. */
};


/**@brief Definition of a navigation route.*/
typedef struct
{
    uint16_t route_id;
    uint8_t  route_name[BLE_LNS_MAX_ROUTE_NAME_LEN];
} ble_lns_route_t;


/**@brief Location and Navigation Service structure. This structure contains various status information for the service. */
struct ble_lns_s
{
    ble_lns_evt_handler_t             evt_handler;                                       /**< Event handler to be called for handling events in the Location and Navigation Service. */
    ble_srv_error_handler_t           error_handler;                                     /**< Error handler. */

    bool                              is_navigation_present;                             /**< If set to true, the navigation characteristic is present. Else not. */

    uint16_t                          conn_handle;                                       /**< Handle of the current connection (as provided by the BLE stack; BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint16_t                          service_handle;                                    /**< Handle of Location and Navigation Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t          loc_speed_handles;                                 /**< Handles related to the Location and Speed characteristic. */
    ble_gatts_char_handles_t          feature_handles;                                   /**< Handles related to the Location and Navigation Feature characteristic. */
    ble_gatts_char_handles_t          navigation_handles;                                /**< Handles related to the Navigation characteristic. */
    ble_gatts_char_handles_t          pos_qual_handles;                                  /**< Handles related to the Position Quality characteristic. */
    ble_gatts_char_handles_t          ctrlpt_handles;
    uint32_t                          available_features;                                /**< Value of Location and Navigation feature. */

    bool                              is_loc_speed_notification_enabled;                 /**< True if notification is enabled on the Location and Speed characteristic. */
    bool                              is_nav_notification_enabled;                       /**< True if notification is enabled on the Navigation characteristic. */

    notification_t                    pending_loc_speed_notifications[2];                /**< This buffer holds location and speed notifications. */
    notification_t                    pending_navigation_notification;                   /**< This buffer holds navigation notifications. */
    ble_lns_loc_speed_t               * p_location_speed;                                /**< Location and Speed. */
    ble_lns_pos_quality_t             * p_position_quality;                              /**< Position measurement quality. */
    ble_lns_navigation_t              * p_navigation;                                    /**< Navigation data structure. */
    ble_lncp_t                        ctrl_pt;
};


/** @brief Position status. This enumeration defines how to interpret the position data. */
typedef enum
{
    BLE_LNS_NO_POSITION         = 0,
    BLE_LNS_POSITION_OK         = 1,
    BLE_LNS_ESTIMATED           = 2,
    BLE_LNS_LAST_KNOWN_POSITION = 3
} ble_lns_pos_status_type_t;


/** @brief The format of the position and speed measurements. */
typedef enum
{
    BLE_LNS_SPEED_DISTANCE_FORMAT_2D = 0,
    BLE_LNS_SPEED_DISTANCE_FORMAT_3D = 1
} ble_lns_speed_distance_format_t;


/** @brief Elevation source. */
typedef enum
{
    BLE_LNS_ELEV_SOURCE_POSITIONING_SYSTEM = 0,
    BLE_LNS_ELEV_SOURCE_BAROMETRIC         = 1,
    BLE_LNS_ELEV_SOURCE_DATABASE_SERVICE   = 2,
    BLE_LNS_ELEV_SOURCE_OTHER              = 3
} ble_lns_elevation_source_t;


/** @brief Heading source. */
typedef enum
{
    BLE_LNS_HEADING_SOURCE_MOVEMENT        = 0,
    BLE_LNS_HEADING_SOURCE_COMPASS         = 1
} ble_lns_heading_source_t;


/**@brief Location and Speed data structure. */
struct ble_lns_loc_speed_s
{
    bool                            instant_speed_present;                     /**< Instantaneous Speed present (0=not present, 1=present). */
    bool                            total_distance_present;                    /**< Total Distance present (0=not present, 1=present). */
    bool                            location_present;                          /**< Location present (0=not present, 1=present). */
    bool                            elevation_present;                         /**< Elevation present (0=not present, 1=present). */
    bool                            heading_present;                           /**< Heading present (0=not present, 1=present). */
    bool                            rolling_time_present;                      /**< Rolling Time present (0=not present, 1=present). */
    bool                            utc_time_time_present;                     /**< UTC Time present (0=not present, 1=present). */
    ble_lns_pos_status_type_t       position_status;                           /**< Status of current position */
    ble_lns_speed_distance_format_t data_format;                               /**< Format of data (either 2D or 3D). */
    ble_lns_elevation_source_t      elevation_source;                          /**< Source of the elevation measurement. */
    ble_lns_heading_source_t        heading_source;                            /**< Source of the heading measurement. */
    uint16_t                        instant_speed;                             /**< Instantaneous Speed (1/10 meter per sec). */
    uint32_t                        total_distance;                            /**< Total Distance (meters), size=24 bits. */
    int32_t                         latitude;                                  /**< Latitude (10e-7 degrees). */
    int32_t                         longitude;                                 /**< Longitude (10e-7 degrees). */
    int32_t                         elevation;                                 /**< Elevation (1/100 meters), size=24 bits. */
    uint16_t                        heading;                                   /**< Heading (1/100 degrees). */
    uint8_t                         rolling_time;                              /**< Rolling Time (seconds). */
    ble_date_time_t                 utc_time;                                  /**< UTC Time. */
};


/** @brief Position quality structure. */
struct ble_lns_pos_quality_s
{
    bool                            number_of_satellites_in_solution_present;  /**< The number of satellites present in solution (0=not present, 1=present). */
    bool                            number_of_satellites_in_view_present;      /**< The number of satellites present in solution (0=not present, 1=present). */
    bool                            time_to_first_fix_present;                 /**< Time to the first position fix present (0=not present, 1=present). */
    bool                            ehpe_present;                              /**< Error in horizontal position estimate present (0=not present, 1=present). */
    bool                            evpe_present;                              /**< Error in vertical position estimate present (0=not present, 1=present). */
    bool                            hdop_present;                              /**< Horizontal dilution of precision present (0=not present, 1=present). */
    bool                            vdop_present;                              /**< Vertical dilution of precision present (0=not present, 1=present). */
    ble_lns_pos_status_type_t       position_status;                           /**< Status of last measured position. */
    uint8_t                         number_of_satellites_in_solution;          /**< The number of satellites in solution (unitless, with a resolution of 1). */
    uint8_t                         number_of_satellites_in_view;              /**< The number of satellites in view (unitless, with a resolution of 1). */
    uint16_t                        time_to_first_fix;                         /**< Time to the first position fix (seconds, with a resolution of 1/10). */
    uint32_t                        ehpe;                                      /**< Error in horizontal position estimate (meters, with a resolution of 1/100). */
    uint32_t                        evpe;                                      /**< Error in vertical position estimate (meters, with a resolution of 1/100). */
    uint8_t                         hdop;                                      /**< Horizontal dilution of precision (unitless, with a resolution of 2/10). */
    uint8_t                         vdop;                                      /**< Vertical dilution of precision (unitless, with a resolution of 2/10). */
};


/** @brief Navigation indicator type. */
typedef enum
{
    BLE_LNS_NAV_TO_WAYPOINT    = 0,
    BLE_LNS_NAV_TO_DESTINATION = 1
} ble_lns_nav_indicator_type_t;


/**@brief Navigation data structure. */
struct ble_lns_navigation_s
{
    bool                             remaining_dist_present;                    /**< Remaining Distance present (0=not present, 1=present). */
    bool                             remaining_vert_dist_present;               /**< Remaining Vertical Distance present (0=not present, 1=present). */
    bool                             eta_present;                               /**< Estimated Time of Arrival present (0=not present, 1=present). */
    ble_lns_pos_status_type_t        position_status;                           /**< Status of last measured position. */
    ble_lns_heading_source_t         heading_source;                            /**< Source of the heading measurement. */
    ble_lns_nav_indicator_type_t     navigation_indicator_type;                 /**< Navigation indicator type. */
    bool                             waypoint_reached;                          /**< Waypoint Reached (0=not reached, 1=reached). */
    bool                             destination_reached;                       /**< Destination Reached (0=not reached, 1=reached). */
    uint16_t                         bearing;                                   /**< Bearing (1/100 degrees).*/
    uint16_t                         heading;                                   /**< Heading (1/100 degrees), size=24 bit. */
    uint32_t                         remaining_distance;                        /**< Remaining Distance (1/10 meters), size=24 bit. */
    int32_t                          remaining_vert_distance;                   /**< Remaining Vertical Distance (1/100 meters), size=24 bit. */
    ble_date_time_t                  eta;                                       /**< Estimated Time of Arrival. */
};


/**@brief Function for initializing the Location and Navigation Service.
 *
 * @param[out]    p_lns                  Location and Navigation Service structure. This structure must be supplied by
 *                                       the application. It is initialized by this function, and will later
 *                                       be used to identify this particular service instance.
 * @param[in]     p_lns_init             Information needed to initialize the service.
 *
 * @retval        NRF_SUCCESS            If the service was initialized successfully.
 * @retval        NRF_ERROR_NULL         If a NULL parameter was provided.
 * @retval        NRF_INVALID_PARAMS     If there is an inconsistency in the initialization structure.
 * @return        Otherwise, an error code from either sd_ble_gatts_service_add() or sd_ble_gatts_characteristic_add() is returned.
 */
ret_code_t ble_lns_init(ble_lns_t * p_lns, const ble_lns_init_t * p_lns_init);

/**@brief   Function for handling Location and Navigation Service BLE stack events.
 *
 * @details This function handles all events from the BLE stack that are of interest to the Location and Navigation Service.
 *
 * @note    The function returns when a NULL parameter is provided.
 *
 * @param[in]     p_lns                   Location and Navigation Service structure.
 * @param[in]     p_ble_evt               Event received from the BLE stack.
 *
 */
void ble_lns_on_ble_evt(ble_lns_t * p_lns, ble_evt_t const * p_ble_evt);

/**@brief   Function for sending location and speed data if notification has been enabled.
 *
 * @details The application calls this function after having performed a location and speed determination.
 *          If notification has been enabled, the location and speed data is encoded and sent to
 *          the client.
 *
 * @param[in]     p_lns                   Location and Navigation Service structure holding the location and speed data.
 *
 * @retval        NRF_SUCCESS             If the data was sent successfully.
 * @retval        NRF_ERROR_NULL          If a NULL parameter was provided.
 * @retval        NRF_ERROR_INVALID_STATE If notification is disabled.
 */
ret_code_t ble_lns_loc_speed_send(ble_lns_t * p_lns);

/**@brief Function for sending navigation data if notification has been enabled.
 *
 * @details The application calls this function after having performed a navigation determination.
 *          If notification has been enabled, the navigation data is encoded and sent to
 *          the client.
 *
 * @param[in]     p_lns                   Location and Navigation Service structure holding the navigation data.
 *
 * @retval        NRF_SUCCESS             If the data was sent successfully.
 * @retval        NRF_ERROR_NULL          If a NULL parameter was provided.
 * @retval        NRF_ERROR_NOT_SUPPORTED If the navigation characteristic is absent.
 * @retval        NRF_ERROR_INVALID_STATE If navigation is not running or notification is disabled.
 */
ret_code_t ble_lns_navigation_send(ble_lns_t * p_lns);

/**@brief Function for adding a route to the Location and Navigation Service.
 *
 * @param[in]     p_lns                   Location and Navigation Service structure.
 * @param[in,out] p_route                 The new route to be added. The route ID is updated.
 *
 * @retval        NRF_SUCCESS             If the route was added successfully.
 * @retval        NRF_ERROR_NULL          If a NULL parameter was provided.
 * @retval        NRF_ERROR_NOT_SUPPORTED If the navigation characteristic is absent.
 * @retval        NRF_ERROR_NO_MEM        If there is no memory left.
 * @retval        NRF_ERROR_INTERNAL      If there is an inconsistency in the routes table.
 */
ret_code_t ble_lns_add_route(ble_lns_t * p_lns, ble_lns_route_t * p_route);

/**@brief Function for removing a route from the Location and Navigation Service.
 *
 * @param[in]     p_lns                   Location and Navigation Service structure.
 * @param[in]     route_id                The ID of the route to be removed.
 *
 * @retval        NRF_SUCCESS             If the route was removed successfully.
 * @retval        NRF_ERROR_NULL          If a NULL parameter was provided.
 * @retval        NRF_ERROR_NOT_SUPPORTED If the navigation characteristic is absent.
 * @retval        NRF_INVALID_PARAM       If the route ID does not exist.
 */
ret_code_t ble_lns_remove_route(ble_lns_t * p_lns, uint16_t route_id);


#ifdef __cplusplus
}
#endif

#endif // BLE_LNS_H__

/** @} */
