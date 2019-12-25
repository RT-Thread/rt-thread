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
#include "ble_lns.h"
#include "ble_ln_db.h"
#include "ble_ln_common.h"
#include "sdk_common.h"

#define NRF_LOG_MODULE_NAME ble_lns
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

// Location and Speed flag bits
#define LOC_SPEED_FLAG_INSTANT_SPEED_PRESENT             (0x01 << 0)         /**< Instantaneous Speed Present bit. */
#define LOC_SPEED_FLAG_TOTAL_DISTANCE_PRESENT            (0x01 << 1)         /**< Total Distance Present bit. */
#define LOC_SPEED_FLAG_LOCATION_PRESENT                  (0x01 << 2)         /**< Location Present bit. */
#define LOC_SPEED_FLAG_ELEVATION_PRESENT                 (0x01 << 3)         /**< Elevation Present bit. */
#define LOC_SPEED_FLAG_HEADING_PRESENT                   (0x01 << 4)         /**< Heading Present bit. */
#define LOC_SPEED_FLAG_ROLLING_TIME_PRESENT              (0x01 << 5)         /**< Rolling Time Present bit. */
#define LOC_SPEED_FLAG_UTC_TIME_PRESENT                  (0x01 << 6)         /**< UTC Time Present bit. */
#define LOC_SPEED_FLAG_POSITION_STATUS                   (0x03 << 7)         /**< Position Status bits(2). */
#define LOC_SPEED_FLAG_SPEED_AND_DIST_FORMAT             (0x01 << 9)         /**< Speed and Distance Format. */
#define LOC_SPEED_FLAG_ELEVATION_SOURCE                  (0x03 << 10)        /**< Elevation Source bits(2). */
#define LOC_SPEED_FLAG_HEADING_SOURCE                    (0x01 << 12)        /**< Heading Source. */

// Position Quality flag bits
#define POS_QUAL_FLAG_NUM_SATS_IN_SOLUTION_PRESENT       (0x01 << 0)         /**< Number of Satellites in Solution Present bit. */
#define POS_QUAL_FLAG_NUM_SATS_IN_VIEW_PRESENT           (0x01 << 1)         /**< Number of Satellites in View Present bit. */
#define POS_QUAL_FLAG_TIME_TO_FIRST_FIX_PRESESNT         (0x01 << 2)         /**< Time to First Fix Present bit. */
#define POS_QUAL_FLAG_EHPE_PRESENT                       (0x01 << 3)         /**< EHPE Present bit. */
#define POS_QUAL_FLAG_EVPE_PRESENT                       (0x01 << 4)         /**< EVPE Present bit. */
#define POS_QUAL_FLAG_HDOP_PRESENT                       (0x01 << 5)         /**< HDOP Present bit. */
#define POS_QUAL_FLAG_VDOP_PRESENT                       (0x01 << 6)         /**< VDOP Present bit. */
#define POS_QUAL_FLAG_POSITION_STATUS                    (0x03 << 7)         /**< Position Status bits(2). */

// Navigation flag bits
#define NAV_FLAG_REMAINING_DIST_PRESENT                  (0x01 << 0)         /**< Remaining Distance Present bit. */
#define NAV_FLAG_REAMINGING_VERT_DIST_PRESESNT           (0x01 << 1)         /**< Remaining Vertical Distance Present bit . */
#define NAV_FLAG_ETA_PRESENT                             (0x01 << 2)         /**< Estimated Time of Arrival Present bit. */
#define NAV_FLAG_POSITION_STATUS                         (0x03 << 3)         /**< Position Status bits(2). */
#define NAV_FLAG_HEADING_SOURCE                          (0x01 << 5)         /**< Heading Source bit. */
#define NAV_FLAG_NAVIGATION_INDICATOR_TYPE               (0x01 << 6)         /**< Navigation Indicator Type bit. */
#define NAV_FLAG_WAYPOINT_REACHED                        (0x01 << 7)         /**< Waypoint Reached bit. */
#define NAV_FLAG_DESTINATION_REACHED                     (0x01 << 8)         /**< Destination Reached bit. */

#define BLE_LNS_NAV_MAX_LEN                             19 /**< The length of a navigation notification when all features are enabled. See @ref ble_lns_navigation_t to see what this represents, or check https://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.navigation.xml. */


static void notification_buffer_process(ble_lns_t * p_lns)
{
    notification_t * p_notification;

    // See if a notification is pending
    if (p_lns->pending_loc_speed_notifications[0].is_pending == true)
    {
        p_notification = &p_lns->pending_loc_speed_notifications[0];
    }
    else if (p_lns->pending_loc_speed_notifications[1].is_pending == true)
    {
        p_notification = &p_lns->pending_loc_speed_notifications[1];
    }
    else if (p_lns->pending_navigation_notification.is_pending == true)
    {
        p_notification = &p_lns->pending_navigation_notification;
    }
    else
    {
        p_notification = NULL;
    }

    // send the notification if necessary
    if (p_notification != NULL)
    {
        uint32_t               err_code;
        ble_gatts_hvx_params_t hvx_params;

        memset(&hvx_params, 0, sizeof(hvx_params));

        uint16_t hvx_len = p_notification->len;

        hvx_params.handle   = p_notification->handle;
        hvx_params.type     = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset   = 0;
        hvx_params.p_len    = &hvx_len;
        hvx_params.p_data   = &p_notification->data[0];

        err_code = sd_ble_gatts_hvx(p_lns->conn_handle, &hvx_params);

        if ((err_code == NRF_SUCCESS) && (hvx_len == p_notification->len))
        {
            p_notification->is_pending = false;
        }
    }
}


/**@brief Connect event handler.
 *
 * @param[in]   p_lns       Location and Navigation Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_lns_t * p_lns, ble_evt_t const * p_ble_evt)
{
    p_lns->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;

    // clear pending notifications
    p_lns->pending_loc_speed_notifications[0].is_pending    = false;
    p_lns->pending_loc_speed_notifications[1].is_pending    = false;
    p_lns->pending_navigation_notification.is_pending       = false;
}


/**@brief Disconnect event handler.
 *
 * @param[in]   p_lns       Location and Navigation Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_lns_t * p_lns, ble_evt_t const * p_ble_evt)
{
    if (p_lns->conn_handle != p_ble_evt->evt.gatts_evt.conn_handle)
    {
        return;
    }

    p_lns->conn_handle = BLE_CONN_HANDLE_INVALID;
}


/**@brief Handle write events to the control point cccd.
 *
 * @param[in]   p_lncp       Location and Navigation Service structure.
 * @param[in]   p_evt_write Write event received from the BLE stack.
 */
static void on_ctrl_pt_cccd_write(ble_lns_t * p_lns, ble_gatts_evt_write_t const * p_evt_write)
{
    if (p_evt_write->len == BLE_CCCD_VALUE_LEN)
    {
        if (p_lns->evt_handler != NULL)
        {
            ble_lns_evt_t evt;

            if (ble_srv_is_indication_enabled(p_evt_write->data))
            {
                evt.evt_type = BLE_LNS_CTRLPT_EVT_INDICATION_ENABLED;
            }
            else
            {
                evt.evt_type = BLE_LNS_CTRLPT_EVT_INDICATION_DISABLED;
            }

            p_lns->evt_handler(p_lns, &evt);
        }
    }
}


/**@brief Handle write events to the Location and Speed cccd.
 *
 * @param[in]   p_lns       Location and Navigation Service structure.
 * @param[in]   p_evt_write Write event received from the BLE stack.
 */
static void on_loc_speed_cccd_write(ble_lns_t                   * p_lns,
                                    ble_gatts_evt_write_t const * p_evt_write)
{
    if (p_evt_write->len == BLE_CCCD_VALUE_LEN)
    {
        // CCCD written, update notification state
        p_lns->is_loc_speed_notification_enabled = ble_srv_is_notification_enabled(p_evt_write->data);
        if (p_lns->evt_handler != NULL)
        {
            ble_lns_evt_t evt;

            if (p_lns->is_loc_speed_notification_enabled)
            {
                evt.evt_type = BLE_LNS_LOC_SPEED_EVT_NOTIFICATION_ENABLED;
            }
            else
            {
                evt.evt_type = BLE_LNS_LOC_SPEED_EVT_NOTIFICATION_DISABLED;
            }

            p_lns->evt_handler(p_lns, &evt);
        }
    }
}


/**@brief Handle write events to the navigation cccd.
 *
 * @param[in]   p_lns       Location and Navigation Service structure.
 * @param[in]   p_evt_write Write event received from the BLE stack.
 */
static void on_nav_cccd_write(ble_lns_t                   * p_lns,
                              ble_gatts_evt_write_t const * p_evt_write)
{
    if (p_evt_write->len == BLE_CCCD_VALUE_LEN)
    {
        p_lns->is_nav_notification_enabled = ble_srv_is_notification_enabled(p_evt_write->data);
        if (p_lns->evt_handler != NULL)
        {
            ble_lns_evt_t evt;

            if (p_lns->is_nav_notification_enabled)
            {
                evt.evt_type = BLE_LNS_NAVIGATION_EVT_NOTIFICATION_ENABLED;
            }
            else
            {
                evt.evt_type = BLE_LNS_NAVIGATION_EVT_NOTIFICATION_DISABLED;
            }

            p_lns->evt_handler(p_lns, &evt);
        }
    }
}


/**@brief Write event handler.
 *
 * @param[in]   p_lns     Location and Navigation Service structure.
 * @param[in]   p_ble_evt Event received from the BLE stack.
 */
static void on_write(ble_lns_t * p_lns, ble_evt_t const * p_ble_evt)
{
    if (p_lns->conn_handle != p_ble_evt->evt.gatts_evt.conn_handle)
    {
        return;
    }

    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if (p_evt_write->handle == p_lns->ctrlpt_handles.cccd_handle)
    {
        on_ctrl_pt_cccd_write(p_lns, p_evt_write);
    }
    else if (p_evt_write->handle == p_lns->loc_speed_handles.cccd_handle)
    {
        on_loc_speed_cccd_write(p_lns, p_evt_write);
    }
    else if (p_evt_write->handle == p_lns->navigation_handles.cccd_handle)
    {
        on_nav_cccd_write(p_lns, p_evt_write);
    }
}


/**@brief Tx Complete event handler. This is used to retry sending a packet.
 *
 * @details Tx Complete event handler.
 *          Handles WRITE events from the BLE stack and if an indication was pending try sending it
 *          again.
 *
 * @param[in]   p_lns  Location navigation structure.
 */
static void on_tx_complete(ble_lns_t * p_lns)
{
    notification_buffer_process(p_lns);
}


/**@brief Encode position quality.
 *
 * @param[in]   p_lns              Location and Navigation Service structure.
 * @param[in]   p_pos_qual         Position quality data to be encoded.
 * @param[out]  p_encoded_buffer   Buffer where the encoded data will be written.
 *
 * @return      Size of encoded data.
 */
static uint8_t pos_qual_encode(ble_lns_t             const * p_lns,
                               ble_lns_pos_quality_t const * p_pos_qual,
                               uint8_t                     * p_encoded_buffer)
{
    uint16_t flags = 0;
    uint8_t  len = 2;  // flags are added at last

    flags |= ((uint16_t)p_pos_qual->position_status << 7) & POS_QUAL_FLAG_POSITION_STATUS;

    if (p_pos_qual->number_of_satellites_in_solution_present)
    {
        flags |= POS_QUAL_FLAG_NUM_SATS_IN_SOLUTION_PRESENT;
        p_encoded_buffer[len++] = p_pos_qual->number_of_satellites_in_solution;
    }

    if (p_pos_qual->number_of_satellites_in_view_present)
    {
        flags |= POS_QUAL_FLAG_NUM_SATS_IN_VIEW_PRESENT;
        p_encoded_buffer[len++] = p_pos_qual->number_of_satellites_in_view;
    }

    if (p_pos_qual->time_to_first_fix_present)
    {
        flags |= POS_QUAL_FLAG_TIME_TO_FIRST_FIX_PRESESNT;
        len += uint16_encode(p_pos_qual->time_to_first_fix, &p_encoded_buffer[len]);
    }

    if (p_pos_qual->ehpe_present)
    {
        flags |= POS_QUAL_FLAG_EHPE_PRESENT;
        len += uint32_encode(p_pos_qual->ehpe, &p_encoded_buffer[len]);
    }

    if (p_pos_qual->evpe_present)
    {
        flags |= POS_QUAL_FLAG_EVPE_PRESENT;
        len += uint32_encode(p_pos_qual->evpe, &p_encoded_buffer[len]);
    }

    if (p_pos_qual->hdop_present)
    {
        flags |= POS_QUAL_FLAG_HDOP_PRESENT;
        p_encoded_buffer[len++] = p_pos_qual->hdop;
    }

    if (p_pos_qual->vdop_present)
    {
        flags |= POS_QUAL_FLAG_VDOP_PRESENT;
        p_encoded_buffer[len++] = p_pos_qual->vdop;
    }

    // Flags field
    uint16_encode(flags, &p_encoded_buffer[0]); //lint !e534 "Ignoring return value of function"

    return len;
}


/**@brief Encode Location and Speed data packet 1
 *
 * @param[in]   p_lns              Location and Navigation Service structure.
 * @param[in]   p_loc_speed        Location and Speed data to be encoded.
 * @param[out]  p_encoded_buffer   Pointer to buffer buffer where encoded data will be written.
 *
 * @return      Size of encoded data.
 *
 */
static uint8_t loc_speed_encode_packet1(ble_lns_t           const * p_lns,
                                        ble_lns_loc_speed_t const * p_loc_speed,
                                        uint8_t                   * p_encoded_buffer)
{
    uint16_t flags = 0;
    uint8_t  len   = 2;

    ble_lncp_mask_t const mask = ble_lncp_mask_get(&p_lns->ctrl_pt);

    // Instantaneous Speed
    if (p_lns->available_features & BLE_LNS_FEATURE_INSTANT_SPEED_SUPPORTED)
    {
        if (p_loc_speed->instant_speed_present && !mask.instantaneous_speed)
        {
            flags |= LOC_SPEED_FLAG_INSTANT_SPEED_PRESENT;
            flags |= ((uint16_t)p_loc_speed->data_format<<9) & LOC_SPEED_FLAG_SPEED_AND_DIST_FORMAT;
            len += uint16_encode(p_loc_speed->instant_speed, &p_encoded_buffer[len]);
        }
    }

    // Total Distance
    if (p_lns->available_features & BLE_LNS_FEATURE_TOTAL_DISTANCE_SUPPORTED)
    {
        if (p_loc_speed->total_distance_present && !mask.total_distance)
        {
            uint32_t const total_distance = ble_lncp_total_distance_get(&p_lns->ctrl_pt);
            flags |= LOC_SPEED_FLAG_TOTAL_DISTANCE_PRESENT;
            len += uint24_encode(total_distance, &p_encoded_buffer[len]);
        }
    }

    // Location
    if (p_lns->available_features & BLE_LNS_FEATURE_LOCATION_SUPPORTED)
    {
        if (p_loc_speed->location_present && !mask.location)
        {
            flags |= LOC_SPEED_FLAG_LOCATION_PRESENT;
            flags |= ((uint16_t)p_loc_speed->position_status <<7) & LOC_SPEED_FLAG_POSITION_STATUS;
            len += uint32_encode(p_loc_speed->latitude,  &p_encoded_buffer[len]);
            len += uint32_encode(p_loc_speed->longitude, &p_encoded_buffer[len]);
        }
    }

    // Flags field
    uint16_encode(flags, &p_encoded_buffer[0]); //lint !e534 "Ignoring return value of function"

    return len;
}


/**@brief Encode Location and Speed data packet 2
 *
 * @param[in]   p_lns              Location and Navigation Service structure.
 * @param[in]   p_loc_speed        Location and Speed data to be encoded.
 * @param[out]  p_encoded_buffer   Pointer to buffer buffer where encoded data will be written.
 *
 * @return      Size of encoded data.
 *
 */
static uint8_t loc_speed_encode_packet2(ble_lns_t           const * p_lns,
                                        ble_lns_loc_speed_t const * p_loc_speed,
                                        uint8_t                   * p_encoded_buffer)
{
    uint16_t flags = 0;
    uint8_t  len   = 2;

    ble_lncp_mask_t const mask = ble_lncp_mask_get(&p_lns->ctrl_pt);

    // Elevation
    if (p_lns->available_features & BLE_LNS_FEATURE_ELEVATION_SUPPORTED)
    {
        if (p_loc_speed->elevation_present && !mask.elevation)
        {
            uint32_t const elevation = ble_lncp_elevation_get(&p_lns->ctrl_pt);

            flags |= LOC_SPEED_FLAG_ELEVATION_PRESENT;
            flags |= ((uint16_t) p_loc_speed->elevation_source << 10) & LOC_SPEED_FLAG_ELEVATION_SOURCE;
            len += uint24_encode(elevation, &p_encoded_buffer[len]);
        }
    }

    // Heading
    if (p_lns->available_features & BLE_LNS_FEATURE_HEADING_SUPPORTED)
    {
        if (p_loc_speed->heading_present && !mask.heading)
        {
            flags |= LOC_SPEED_FLAG_HEADING_PRESENT;
            flags |= ((uint16_t) p_loc_speed->heading_source << 12) & LOC_SPEED_FLAG_HEADING_SOURCE;
            len += uint16_encode(p_loc_speed->heading, &p_encoded_buffer[len]);
        }
    }

    // Rolling Time
    if (p_lns->available_features & BLE_LNS_FEATURE_ROLLING_TIME_SUPPORTED)
    {
        if ((p_loc_speed->rolling_time_present && !mask.rolling_time))
        {
            flags |= LOC_SPEED_FLAG_ROLLING_TIME_PRESENT;
            p_encoded_buffer[len++] = p_loc_speed->rolling_time;
        }
    }

    // UTC Time
    if (p_lns->available_features & BLE_LNS_FEATURE_UTC_TIME_SUPPORTED)
    {
        if ((p_loc_speed->utc_time_time_present && !mask.utc_time))
        {
            flags |= LOC_SPEED_FLAG_UTC_TIME_PRESENT;
            len += ble_date_time_encode(&p_loc_speed->utc_time, &p_encoded_buffer[len]);
        }
    }
    // Flags field
    uint16_encode(flags, &p_encoded_buffer[0]); //lint !e534 "Ignoring return value of function"

    return len;
}


/**@brief Encode Navigation data.
 *
 * @param[in]   p_lns              Location and Navigation Service structure.
 * @param[in]   p_navigation       Navigation data to be encoded.
 * @param[out]  p_encoded_buffer   Buffer where the encoded data will be written.
 *
 * @return      Size of encoded data.
 */
static uint8_t navigation_encode(ble_lns_t            const * p_lns,
                                 ble_lns_navigation_t const * p_navigation,
                                 uint8_t                    * p_encoded_buffer)
{
    uint16_t flags = 0;
    uint8_t  len   = 2;

    // Bearing
    len += uint16_encode(p_navigation->bearing, &p_encoded_buffer[len]);

    // Heading
    len += uint16_encode(p_navigation->heading, &p_encoded_buffer[len]);

    // Remaining Distance
    if (p_lns->available_features & BLE_LNS_FEATURE_REMAINING_DISTANCE_SUPPORTED)
    {
        if (p_navigation->remaining_dist_present)
        {
            flags |= NAV_FLAG_REMAINING_DIST_PRESENT;
            p_encoded_buffer[len++] = ((p_navigation->remaining_distance >>  0) & 0xFF);
            p_encoded_buffer[len++] = ((p_navigation->remaining_distance >>  8) & 0xFF);
            p_encoded_buffer[len++] = ((p_navigation->remaining_distance >> 16) & 0xFF);
        }
    }

    // Remaining Vertical Distance
    if (p_lns->available_features & BLE_LNS_FEATURE_REMAINING_VERT_DISTANCE_SUPPORTED)
    {
        if (p_navigation->remaining_vert_dist_present)
        {
            flags |= NAV_FLAG_REAMINGING_VERT_DIST_PRESESNT;
            p_encoded_buffer[len++] = ((p_navigation->remaining_vert_distance >>  0) & 0xFF);
            p_encoded_buffer[len++] = ((p_navigation->remaining_vert_distance >>  8) & 0xFF);
            p_encoded_buffer[len++] = ((p_navigation->remaining_vert_distance >> 16) & 0xFF);
        }
    }

    // Estimated Time of Arrival
    if (p_lns->available_features & BLE_LNS_FEATURE_EST_TIME_OF_ARRIVAL_SUPPORTED)
    {
        if (p_navigation->eta_present)
        {
            flags |= NAV_FLAG_ETA_PRESENT;
            len   += ble_date_time_encode(&p_navigation->eta, &p_encoded_buffer[len]);
        }
    }

    flags |= ((uint16_t)p_navigation->position_status          <<3) & NAV_FLAG_POSITION_STATUS;
    flags |= ((uint16_t)p_navigation->heading_source           <<5) & NAV_FLAG_HEADING_SOURCE;
    flags |= ((uint16_t)p_navigation->navigation_indicator_type<<6)& NAV_FLAG_NAVIGATION_INDICATOR_TYPE;
    flags |= ((uint16_t)p_navigation->waypoint_reached         <<7)& NAV_FLAG_WAYPOINT_REACHED;
    flags |= ((uint16_t)p_navigation->destination_reached      <<8)& NAV_FLAG_DESTINATION_REACHED;

    // Flags field
    uint16_encode(flags, &p_encoded_buffer[0]); //lint !e534 "Ignoring return value of function"

    return len;
}


/**@brief Add Location and Navigation Feature characteristic.
 *
 * @param[in]   p_lns        Location and Navigation Service structure.
 * @param[in]   p_lns_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static ret_code_t loc_and_nav_feature_char_add(ble_lns_t * p_lns, ble_lns_init_t const * p_lns_init)
{
    uint8_t               init_value_encoded[sizeof(uint32_t)];
    uint8_t               len;
    ble_add_char_params_t add_char_params;

    len = uint32_encode(p_lns_init->available_features, init_value_encoded);

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid              = BLE_UUID_LN_FEATURE_CHAR;
    add_char_params.max_len           = len;
    add_char_params.init_len          = len;
    add_char_params.p_init_value      = &init_value_encoded[0];
    add_char_params.char_props.read   = true;
    add_char_params.read_access       = p_lns_init->loc_nav_feature_security_req_read_perm;

    return characteristic_add(p_lns->service_handle,
                              &add_char_params,
                              &p_lns->feature_handles);
}


/**@brief Add Location and Speed characteristic.
 *
 * @param[in]   p_lns        Location and Navigation Service structure.
 * @param[in]   p_lns_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static ret_code_t loc_speed_char_add(ble_lns_t * p_lns, ble_lns_init_t const * p_lns_init)
{
    uint8_t               encoded_initial_loc_speed1[BLE_GATT_ATT_MTU_DEFAULT];
    uint8_t               len;
    ble_add_char_params_t add_char_params;

    len = loc_speed_encode_packet1(p_lns, p_lns_init->p_location_speed, &encoded_initial_loc_speed1[0]);

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid              = BLE_UUID_LN_LOCATION_AND_SPEED_CHAR;
    add_char_params.max_len           = BLE_GATT_ATT_MTU_DEFAULT ;
    add_char_params.init_len          = len;
    add_char_params.p_init_value      = &encoded_initial_loc_speed1[0];
    add_char_params.is_var_len        = true;
    add_char_params.char_props.notify = true;
    add_char_params.cccd_write_access = p_lns_init->loc_speed_security_req_cccd_write_perm;

    return characteristic_add(p_lns->service_handle,
                              &add_char_params,
                              &p_lns->loc_speed_handles);
}


/**@brief Add Location and Navigation position quality characteristic.
 *
 * @param[in]   p_lns        Location and Navigation Service structure.
 * @param[in]   p_lns_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static ret_code_t pos_quality_char_add(ble_lns_t * p_lns, ble_lns_init_t const * p_lns_init)
{
    uint8_t               len;
    uint8_t               init_value_encoded[BLE_GATT_ATT_MTU_DEFAULT];
    ble_add_char_params_t add_char_params;

    len = pos_qual_encode(p_lns, p_lns_init->p_position_quality, init_value_encoded);

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid            = BLE_UUID_LN_POSITION_QUALITY_CHAR;
    add_char_params.max_len         = BLE_GATT_ATT_MTU_DEFAULT ;
    add_char_params.init_len        = len;
    add_char_params.p_init_value    = init_value_encoded;
    add_char_params.char_props.read = true;
    add_char_params.read_access     = p_lns_init->position_quality_security_req_read_perm;

    return characteristic_add(p_lns->service_handle,
                              &add_char_params,
                              &p_lns->pos_qual_handles);
}


/**@brief Add Navigation characteristic.
 *
 * @param[in]   p_lns        Location and Navigation Service structure.
 * @param[in]   p_lns_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static ret_code_t navigation_char_add(ble_lns_t * p_lns, ble_lns_init_t const * p_lns_init)
{
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid              = BLE_UUID_LN_NAVIGATION_CHAR;
    add_char_params.max_len           = BLE_LNS_NAV_MAX_LEN;
    add_char_params.init_len          = 0;
    add_char_params.p_init_value      = NULL;
    add_char_params.char_props.notify = true;
    add_char_params.cccd_write_access = p_lns_init->navigation_security_req_cccd_write_perm;

    return characteristic_add(p_lns->service_handle,
                              &add_char_params,
                              &p_lns->navigation_handles);
}


/** @brief Check if there is a mismatch in initialization parameters.
 *
 *  @details It is possible to give an input which has an internal mismatch. Such a mismatch can arise in two different ways.
 *           One possibility is a mismatch between the characteristic present indicators and the available features specified.
 *           The other mismatch arises when no pointer to the characteristic data structure is specified.
 *
 *  @param[in] p_lns_init The init structure which will be checked
 *
 *  @return    false if there is no mismatch. true if there is a mismatch
 */
static bool init_param_mismatch_present(ble_lns_init_t const * p_lns_init)
{
    if (p_lns_init->is_position_quality_present == false)
    {
        if (p_lns_init->available_features &
             (BLE_LNS_FEATURE_NUM_SATS_IN_SOLUTION_SUPPORTED       |
              BLE_LNS_FEATURE_NUM_SATS_IN_VIEW_SUPPORTED           |
              BLE_LNS_FEATURE_TIME_TO_FIRST_FIX_SUPPORTED          |
              BLE_LNS_FEATURE_EST_HORZ_POS_ERROR_SUPPORTED         |
              BLE_LNS_FEATURE_EST_VERT_POS_ERROR_SUPPORTED         |
              BLE_LNS_FEATURE_HORZ_DILUTION_OF_PRECISION_SUPPORTED |
              BLE_LNS_FEATURE_VERT_DILUTION_OF_PRECISION_SUPPORTED)
           )
        {
            return true;
        }
        if (p_lns_init->p_position_quality != NULL)
        {
            return true;
        }
    }
    else if (p_lns_init->is_position_quality_present == true)
    {
        if (p_lns_init->p_position_quality == NULL)
        {
            return true;
        }
    }

    if (p_lns_init->is_control_point_present == false)
    {
        if (p_lns_init->available_features &
              (BLE_LNS_FEATURE_LOC_AND_SPEED_CONTENT_MASKING_SUPPORTED |
               BLE_LNS_FEATURE_FIX_RATE_SETTING_SUPPORTED              |
               BLE_LNS_FEATURE_ELEVATION_SETTING_SUPPORTED)
            )
        {
            return true;
        }
    }

    if (p_lns_init->is_navigation_present == false)
    {
        if (p_lns_init->available_features &
              (BLE_LNS_FEATURE_REMAINING_DISTANCE_SUPPORTED      |
               BLE_LNS_FEATURE_REMAINING_VERT_DISTANCE_SUPPORTED |
               BLE_LNS_FEATURE_EST_TIME_OF_ARRIVAL_SUPPORTED)
            )
        {
            return true;
        }
        if (p_lns_init->p_navigation != NULL)
        {
            return true;
        }
    }
    else if (p_lns_init->is_navigation_present == true)
    {
        if (p_lns_init->p_navigation == NULL)
        {
            return true;
        }
    }

    // location and speed must always be specified
    if (p_lns_init->p_location_speed == NULL)
    {
        return true;
    }

    return false;
}


void ble_lns_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    VERIFY_PARAM_NOT_NULL_VOID(p_context);
    VERIFY_PARAM_NOT_NULL_VOID(p_ble_evt);

    ble_lns_t * p_lns = (ble_lns_t *)p_context;
    ble_lncp_on_ble_evt(&p_lns->ctrl_pt, p_ble_evt);

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_lns, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_lns, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_lns, p_ble_evt);
            break;

        case BLE_GATTS_EVT_HVN_TX_COMPLETE:
            on_tx_complete(p_lns);
            break;

        default:
            // no implementation
            break;
    }
}


ret_code_t ble_lns_init(ble_lns_t * p_lns, ble_lns_init_t const * p_lns_init)
{
    VERIFY_PARAM_NOT_NULL(p_lns);
    VERIFY_PARAM_NOT_NULL(p_lns_init);

    if (init_param_mismatch_present(p_lns_init) == true)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    uint32_t        err_code;
    ble_uuid_t      service_uuid;
    ble_lncp_init_t lncp_init;

    // Initialize service structure
    p_lns->evt_handler           = p_lns_init->evt_handler;
    p_lns->error_handler         = p_lns_init->error_handler;
    p_lns->conn_handle           = BLE_CONN_HANDLE_INVALID;
    p_lns->available_features    = p_lns_init->available_features;
    p_lns->is_navigation_present = p_lns_init->is_navigation_present;

    // clear pending notifications
    p_lns->pending_loc_speed_notifications[0].is_pending = false;
    p_lns->pending_loc_speed_notifications[1].is_pending = false;
    p_lns->pending_navigation_notification.is_pending    = false;

    p_lns->p_location_speed   = p_lns_init->p_location_speed;
    p_lns->p_position_quality = p_lns_init->p_position_quality;
    p_lns->p_navigation       = p_lns_init->p_navigation;

    p_lns->is_loc_speed_notification_enabled = false;
    p_lns->is_nav_notification_enabled       = false;

    ble_ln_db_init();

    // Add service
    BLE_UUID_BLE_ASSIGN(service_uuid, BLE_UUID_LOCATION_AND_NAVIGATION_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &service_uuid, &p_lns->service_handle);
    VERIFY_SUCCESS(err_code);

    // Add location and navigation feature characteristic
    err_code = loc_and_nav_feature_char_add(p_lns, p_lns_init);
    VERIFY_SUCCESS(err_code);

    // Add location and speed characteristic
    err_code = loc_speed_char_add(p_lns, p_lns_init);
    VERIFY_SUCCESS(err_code);

    if (p_lns_init->is_position_quality_present)
    {
        // Add Position quality characteristic
        err_code = pos_quality_char_add(p_lns, p_lns_init);
        VERIFY_SUCCESS(err_code);
    }
    else
    {
        p_lns->pos_qual_handles.cccd_handle      = BLE_GATT_HANDLE_INVALID;
        p_lns->pos_qual_handles.sccd_handle      = BLE_GATT_HANDLE_INVALID;
        p_lns->pos_qual_handles.user_desc_handle = BLE_GATT_HANDLE_INVALID;
        p_lns->pos_qual_handles.value_handle     = BLE_GATT_HANDLE_INVALID;
    }

    if (p_lns_init->is_navigation_present)
    {
        // Add navigation characteristic
        err_code = navigation_char_add(p_lns, p_lns_init);
        VERIFY_SUCCESS(err_code);
    }
    else
    {
        p_lns->navigation_handles.cccd_handle      = BLE_GATT_HANDLE_INVALID;
        p_lns->navigation_handles.sccd_handle      = BLE_GATT_HANDLE_INVALID;
        p_lns->navigation_handles.user_desc_handle = BLE_GATT_HANDLE_INVALID;
        p_lns->navigation_handles.value_handle     = BLE_GATT_HANDLE_INVALID;
    }

    if (p_lns_init->is_control_point_present)
    {
        lncp_init.error_handler                 = p_lns_init->error_handler;
        lncp_init.evt_handler                   = p_lns_init->lncp_evt_handler;
        lncp_init.write_perm                    = p_lns_init->ctrl_point_security_req_write_perm;
        lncp_init.cccd_write_perm               = p_lns_init->ctrl_point_security_req_cccd_write_perm;
        lncp_init.available_features            = p_lns_init->available_features;
        lncp_init.is_position_quality_present   = p_lns_init->is_position_quality_present;
        lncp_init.is_navigation_present         = p_lns_init->is_navigation_present;

        lncp_init.total_distance                = p_lns_init->p_location_speed->total_distance;
        lncp_init.elevation                     = p_lns_init->p_location_speed->elevation;

        lncp_init.service_handle                = p_lns->service_handle;
        lncp_init.navigation_handles            = p_lns->navigation_handles;

        // Add control pointer characteristic
        err_code = ble_lncp_init(&p_lns->ctrl_pt, &lncp_init);
        VERIFY_SUCCESS(err_code);

        memcpy(&p_lns->ctrlpt_handles, &p_lns->ctrl_pt.ctrlpt_handles, sizeof(ble_gatts_char_handles_t));
    }

    NRF_LOG_DEBUG("Initialized");

    return NRF_SUCCESS;
}


ret_code_t ble_lns_loc_speed_send(ble_lns_t * p_lns)
{
    VERIFY_PARAM_NOT_NULL(p_lns);

    if (p_lns->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (!p_lns->is_loc_speed_notification_enabled)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    notification_t * notif1 = &p_lns->pending_loc_speed_notifications[0];
    notification_t * notif2 = &p_lns->pending_loc_speed_notifications[1];

    // clear previous unsent data. Previous data is invalid.
    notif1->is_pending = false;
    notif2->is_pending = false;

    // check if it is necessary to send packet 1
    if (p_lns->available_features & (BLE_LNS_FEATURE_INSTANT_SPEED_SUPPORTED
                                    | BLE_LNS_FEATURE_TOTAL_DISTANCE_SUPPORTED
                                    | BLE_LNS_FEATURE_LOCATION_SUPPORTED))
    {
        // encode
        notif1->len        = loc_speed_encode_packet1(p_lns, p_lns->p_location_speed, &notif1->data[0]);
        notif1->handle     = p_lns->loc_speed_handles.value_handle;
        notif1->is_pending = true;

        // send
        notification_buffer_process(p_lns);
    }

    // check if it is necessary to send packet 2
    if (p_lns->available_features & (BLE_LNS_FEATURE_ELEVATION_SUPPORTED
                                    | BLE_LNS_FEATURE_HEADING_SUPPORTED
                                    | BLE_LNS_FEATURE_ROLLING_TIME_SUPPORTED
                                    | BLE_LNS_FEATURE_UTC_TIME_SUPPORTED))
    {
        notif2->len        = loc_speed_encode_packet2(p_lns, p_lns->p_location_speed, &notif2->data[0]);
        notif2->handle     = p_lns->loc_speed_handles.value_handle;
        notif2->is_pending = true;

        // send
        notification_buffer_process(p_lns);
    }

    return NRF_SUCCESS;
}


ret_code_t ble_lns_navigation_send(ble_lns_t * p_lns)
{
    VERIFY_PARAM_NOT_NULL(p_lns);

    if (p_lns->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    notification_t * notif = &p_lns->pending_navigation_notification;

    // clear previous unsent data. Previous data is invalid.
    notif->is_pending = false;

    if (!p_lns->is_navigation_present)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    if (!p_lns->is_nav_notification_enabled)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (!ble_lncp_is_navigation_running(&p_lns->ctrl_pt))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    notif->len          = navigation_encode(p_lns, p_lns->p_navigation, &notif->data[0]);
    notif->handle       = p_lns->navigation_handles.value_handle;
    notif->is_pending   = true;

    notification_buffer_process(p_lns);

    return NRF_SUCCESS;
}


ret_code_t ble_lns_add_route(ble_lns_t * p_lns, ble_lns_route_t * p_route)
{
    VERIFY_PARAM_NOT_NULL(p_lns);
    VERIFY_PARAM_NOT_NULL(p_route);

    if (p_lns->is_navigation_present == false)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    return ble_ln_db_record_add(p_route);
}


ret_code_t ble_lns_remove_route(ble_lns_t * p_lns, uint16_t route_id)
{
    VERIFY_PARAM_NOT_NULL(p_lns);

    if (p_lns->is_navigation_present == false)
    {
        return NRF_ERROR_NOT_SUPPORTED;
    }

    return ble_ln_db_record_delete(route_id);
}
