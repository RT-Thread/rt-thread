/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
 * @defgroup ant_sdm Stride Based Speed and Distance Monitor profile
 * @{
 * @ingroup ant_sdk_profiles
 * @brief This module implements the Stride Based Speed and Distance Monitor profile.
 *
 */

#ifndef ANT_SDM_H__
#define ANT_SDM_H__

#include <stdint.h>
#include <stdbool.h>
#include "ant_parameters.h"
#include "nrf_sdh_ant.h"
#include "ant_channel_config.h"
#include "ant_request_controller.h"
#include "ant_sdm_pages.h"
#include "sdk_errors.h"

#define SDM_DEVICE_TYPE       0x7Cu                                         ///< Device type reserved for ANT+ SDM.
#define SDM_ANTPLUS_RF_FREQ   0x39u                                         ///< Frequency, decimal 57 (2457 MHz).

#define SDM_MSG_PERIOD_4Hz    0x1FC6u                                       ///< Message period, decimal 8134 (4.03 Hz).
#define SDM_MSG_PERIOD_2Hz    0x3F8Cu                                       ///< Message period, decimal 16268 (2.01 Hz).

#define SDM_EXT_ASSIGN        0x00                                          ///< ANT ext assign (see Ext. Assign Channel Parameters in ant_parameters.h: @ref ant_parameters).
#define SDM_DISP_CHANNEL_TYPE CHANNEL_TYPE_SLAVE                            ///< RX SDM channel type.
#define SDM_SENS_CHANNEL_TYPE CHANNEL_TYPE_MASTER                           ///< TX SDM channel type.

/**@brief Initialize an ANT channel configuration structure for the SDM profile (Display).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  CHANNEL_NUMBER       Number of the channel assigned to the profile instance.
 * @param[in]  TRANSMISSION_TYPE    Type of transmission assigned to the profile instance.
 * @param[in]  DEVICE_NUMBER        Number of the device assigned to the profile instance.
 * @param[in]  NETWORK_NUMBER       Number of the network assigned to the profile instance.
 * @param[in]  SDM_MSG_PERIOD       Channel period in 32 kHz counts. The SDM profile supports only the following periods:
 *                                  @ref SDM_MSG_PERIOD_4Hz, @ref SDM_MSG_PERIOD_2Hz.
 */
#define SDM_DISP_CHANNEL_CONFIG_DEF(NAME,                                       \
                                    CHANNEL_NUMBER,                             \
                                    TRANSMISSION_TYPE,                          \
                                    DEVICE_NUMBER,                              \
                                    NETWORK_NUMBER,                             \
                                    SDM_MSG_PERIOD)                             \
static const ant_channel_config_t   CONCAT_2(NAME,_channel_sdm_disp_config) =   \
    {                                                                           \
        .channel_number     = (CHANNEL_NUMBER),                                 \
        .channel_type       = SDM_DISP_CHANNEL_TYPE,                            \
        .ext_assign         = SDM_EXT_ASSIGN,                                   \
        .rf_freq            = SDM_ANTPLUS_RF_FREQ,                              \
        .transmission_type  = (TRANSMISSION_TYPE),                              \
        .device_type        = SDM_DEVICE_TYPE,                                  \
        .device_number      = (DEVICE_NUMBER),                                  \
        .channel_period     = (SDM_MSG_PERIOD),                                 \
        .network_number     = (NETWORK_NUMBER),                                 \
    }
#define SDM_DISP_CHANNEL_CONFIG(NAME) &CONCAT_2(NAME,_channel_sdm_disp_config)

/**@brief Initialize an ANT channel configuration structure for the SDM profile (Sensor).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  CHANNEL_NUMBER       Number of the channel assigned to the profile instance.
 * @param[in]  TRANSMISSION_TYPE    Type of transmission assigned to the profile instance.
 * @param[in]  DEVICE_NUMBER        Number of the device assigned to the profile instance.
 * @param[in]  NETWORK_NUMBER       Number of the network assigned to the profile instance.
 */
#define SDM_SENS_CHANNEL_CONFIG_DEF(NAME,                                       \
                                    CHANNEL_NUMBER,                             \
                                    TRANSMISSION_TYPE,                          \
                                    DEVICE_NUMBER,                              \
                                    NETWORK_NUMBER)                             \
static const ant_channel_config_t   CONCAT_2(NAME,_channel_sdm_sens_config) =   \
    {                                                                           \
        .channel_number     = (CHANNEL_NUMBER),                                 \
        .channel_type       = SDM_SENS_CHANNEL_TYPE,                            \
        .ext_assign         = SDM_EXT_ASSIGN,                                   \
        .rf_freq            = SDM_ANTPLUS_RF_FREQ,                              \
        .transmission_type  = (TRANSMISSION_TYPE),                              \
        .device_type        = SDM_DEVICE_TYPE,                                  \
        .device_number      = (DEVICE_NUMBER),                                  \
        .channel_period     = SDM_MSG_PERIOD_4Hz,                               \
        .network_number     = (NETWORK_NUMBER),                                 \
    }
#define SDM_SENS_CHANNEL_CONFIG(NAME) &CONCAT_2(NAME,_channel_sdm_sens_config)

/**@brief Initialize an ANT profile configuration structure for the SDM profile (Display).
 *
 * @param[in]  NAME                         Name of related instance.
 * @param[in]  EVT_HANDLER                  Event handler to be called for handling events in the SDM profile.
 */
#define SDM_DISP_PROFILE_CONFIG_DEF(NAME,                                       \
                                    EVT_HANDLER)                                \
static ant_sdm_disp_cb_t            CONCAT_2(NAME,_sdm_disp_cb);                \
static const ant_sdm_disp_config_t  CONCAT_2(NAME,_profile_sdm_disp_config) =   \
    {                                                                           \
        .p_cb                       = &CONCAT_2(NAME,_sdm_disp_cb),             \
        .evt_handler                = (EVT_HANDLER),                            \
    }
#define SDM_DISP_PROFILE_CONFIG(NAME) &CONCAT_2(NAME,_profile_sdm_disp_config)


/**@brief Initialize an ANT profile configuration structure for the SDM profile (Sensor).
 *
 * @param[in]  NAME                         Name of related instance.
 * @param[in]  SUPPLEMENTARY_PAGE_NUMBER    Supplementary data page (ANT_SDM_PAGE_2 or ANT_SDM_PAGE_3). Use ANT_SDM_PAGE_1 to disable.
 * @param[in]  EVT_HANDLER                  Event handler to be called for handling events in the SDM profile.
 */
#define SDM_SENS_PROFILE_CONFIG_DEF(NAME,                                       \
                                    SUPPLEMENTARY_PAGE_NUMBER,                  \
                                    EVT_HANDLER)                                \
static ant_sdm_sens_cb_t            CONCAT_2(NAME,_sdm_sens_cb);                \
static const ant_sdm_sens_config_t  CONCAT_2(NAME,_profile_sdm_sens_config) =   \
    {                                                                           \
        .supplementary_page_number  = (SUPPLEMENTARY_PAGE_NUMBER),              \
        .p_cb                       = &CONCAT_2(NAME,_sdm_sens_cb),             \
        .evt_handler                = (EVT_HANDLER),                            \
    }
#define SDM_SENS_PROFILE_CONFIG(NAME) &CONCAT_2(NAME,_profile_sdm_sens_config)


/**@brief SDM page number type. */
typedef enum{
    ANT_SDM_PAGE_1  = 1,    ///< Required data page 1.
    ANT_SDM_PAGE_2  = 2,    ///< Supplementary data page 2.
    ANT_SDM_PAGE_3  = 3,    ///< Supplementary data page 3.
    ANT_SDM_PAGE_16 = 16,   ///< Page 16 (sent on request).
    ANT_SDM_PAGE_22 = 22,   ///< Page 22 (sent on request).
    ANT_SDM_PAGE_70 = ANT_COMMON_PAGE_70,
    ANT_SDM_PAGE_80 = ANT_COMMON_PAGE_80,
    ANT_SDM_PAGE_81 = ANT_COMMON_PAGE_81,
} ant_sdm_page_t;

/**@brief SDM profile event type. */
typedef enum{
    ANT_SDM_PAGE_1_UPDATED  = ANT_SDM_PAGE_1,       ///< Data page 1 and speed have been updated (Display) or sent (Sensor).
    ANT_SDM_PAGE_2_UPDATED  = ANT_SDM_PAGE_2,       ///< Data page 2 and speed have been updated (Display) or sent (Sensor).
    ANT_SDM_PAGE_3_UPDATED  = ANT_SDM_PAGE_3,       ///< Data page 3 and speed have been updated (Display) or sent (Sensor).
    ANT_SDM_PAGE_16_UPDATED = ANT_SDM_PAGE_16,      ///< Data page 16 has been updated (Display) or sent (Sensor).
    ANT_SDM_PAGE_22_UPDATED = ANT_SDM_PAGE_22,      ///< Data page 22 has been updated (Display) or sent (Sensor).
    ANT_SDM_PAGE_80_UPDATED = ANT_SDM_PAGE_80,      ///< Data page 80 has been updated (Display) or sent (Sensor).
    ANT_SDM_PAGE_81_UPDATED = ANT_SDM_PAGE_81,      ///< Data page 81 has been updated (Display) or sent (Sensor).
    ANT_SDM_PAGE_REQUEST_SUCCESS,                   ///< Data page request reached the destination.
    ANT_SDM_PAGE_REQUEST_FAILED,                    ///< Data page request did not reach the destination.
} ant_sdm_evt_t;

// Forward declaration of the ant_sdm_profile_t type.
typedef struct ant_sdm_profile_s ant_sdm_profile_t;

/**@brief SDM event handler type. */
typedef void (* ant_sdm_evt_handler_t) (ant_sdm_profile_t *, ant_sdm_evt_t);

#include "ant_sdm_local.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief SDM Sensor configuration structure. */
typedef struct
{
    ant_sdm_page_t          supplementary_page_number;  ///< Supplementary data page (ANT_SDM_PAGE_2 or ANT_SDM_PAGE_3). Use ANT_SDM_PAGE_1 to disable.
    ant_sdm_sens_cb_t     * p_cb;                       ///< Pointer to the data buffer for internal use.
    ant_sdm_evt_handler_t   evt_handler;                ///< Event handler to be called for handling events in the SDM profile.
} ant_sdm_sens_config_t;

/**@brief SDM Display configuration structure. */
typedef struct
{
    ant_sdm_disp_cb_t     * p_cb;           ///< Pointer to the data buffer for internal use.
    ant_sdm_evt_handler_t   evt_handler;    ///< Event handler to be called for handling events in the SDM profile.
} ant_sdm_disp_config_t;

/**@brief SDM profile structure. */
struct ant_sdm_profile_s
{
    uint8_t                     channel_number; ///< Channel number assigned to the profile.
    union {
        ant_sdm_disp_cb_t * p_disp_cb;
        ant_sdm_sens_cb_t * p_sens_cb;
    } _cb;                                      ///< Pointer to internal control block.
    ant_sdm_evt_handler_t       evt_handler;    ///< Event handler to be called for handling events in the SDM profile.
    ant_sdm_page1_data_t        page_1;         ///< Page 1.
    ant_sdm_page2_data_t        page_2;         ///< Page 2.
    ant_sdm_page3_data_t        page_3;         ///< Page 3.
    ant_sdm_page22_data_t       page_22;        ///< Page 22.
    ant_common_page80_data_t    page_80;        ///< Page 80.
    ant_common_page81_data_t    page_81;        ///< Page 81.
    ant_sdm_common_data_t       common;         ///< SDM common data.
};

/** @name Defines for accessing ant_sdm_profile_t members variables
@{ */
#define SDM_PROFILE_update_latency      page_1.update_latency
#define SDM_PROFILE_time                page_1.time
#define SDM_PROFILE_status              page_2.status.items
#define SDM_PROFILE_cadence             page_2.cadence
#define SDM_PROFILE_calories            page_3.calories
#define SDM_PROFILE_capabilities        page_22.capabilities.items
#define SDM_PROFILE_speed               common.speed
#define SDM_PROFILE_distance            common.distance
#define SDM_PROFILE_strides             common.strides
#define SDM_PROFILE_hw_revision         page_80.hw_revision
#define SDM_PROFILE_manufacturer_id     page_80.manufacturer_id
#define SDM_PROFILE_model_number        page_80.model_number
#define SDM_PROFILE_sw_revision_minor   page_81.sw_revision_minor
#define SDM_PROFILE_sw_revision_major   page_81.sw_revision_major
#define SDM_PROFILE_serial_number       page_81.serial_number
/** @} */

/**@brief Function for initializing the ANT SDM RX profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 * @param[in]  p_disp_config    Pointer to the SDM Display configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
ret_code_t ant_sdm_disp_init(ant_sdm_profile_t           * p_profile,
                             ant_channel_config_t const  * p_channel_config,
                             ant_sdm_disp_config_t const * p_disp_config);

/**@brief Function for initializing the ANT SDM TX profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 * @param[in]  p_sens_config    Pointer to the SDM Sensor configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
ret_code_t ant_sdm_sens_init(ant_sdm_profile_t           * p_profile,
                             ant_channel_config_t const  * p_channel_config,
                             ant_sdm_sens_config_t const * p_sens_config);

/**@brief Function for opening the profile instance channel for ANT SDM Display.
 *
 * Before calling this function, pages should be configured.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @retval     NRF_SUCCESS      If the channel was successfully opened. Otherwise, an error code is returned.
 */
ret_code_t ant_sdm_disp_open(ant_sdm_profile_t * p_profile);

/**@brief Function for opening the profile instance channel for ANT SDM Sensor.
 *
 * Before calling this function, pages should be configured.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @retval     NRF_SUCCESS      If the channel was successfully opened. Otherwise, an error code is returned.
 */
ret_code_t ant_sdm_sens_open(ant_sdm_profile_t * p_profile);

/**@brief Function for sending a data page request.
 *
 * This function can be called only on the display side.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_page_70        Pointer to the prepared page 70.
 *
 * @retval     NRF_SUCCESS      If the request has been sent. Otherwise, an error code is returned.
 */
ret_code_t ant_sdm_page_request(ant_sdm_profile_t * p_profile, ant_common_page70_data_t * p_page_70);

/**@brief Function for handling the Sensor ANT events.
 *
 * @details This function handles all events from the ANT stack that are of interest to the SDM Sensor profile.
 *
 * @param[in]   p_ant_evt     Event received from the ANT stack.
 * @param[in]   p_context       Pointer to the profile instance.
 */
void ant_sdm_sens_evt_handler(ant_evt_t * p_ant_evt, void * p_context);

/**@brief Function for handling the Display ANT events.
 *
 * @details This function handles all events from the ANT stack that are of interest to the SDM Display profile.
 *
 * @param[in]   p_ant_evt     Event received from the ANT stack.
 * @param[in]   p_context       Pointer to the profile instance.
 */
void ant_sdm_disp_evt_handler(ant_evt_t * p_ant_evt, void * p_context);


#ifdef __cplusplus
}
#endif

#endif // ANT_SDM_H__
/** @} */
