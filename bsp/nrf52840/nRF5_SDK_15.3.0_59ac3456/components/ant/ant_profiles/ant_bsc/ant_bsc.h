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
 * @defgroup ant_bsc Bicycle Speed and Cadence profile
 * @{
 * @ingroup ant_sdk_profiles
 * @brief This module implements the Bicycle Speed and Cadence profile.
 *
 */

#ifndef ANT_BSC_H__
#define ANT_BSC_H__

#include <stdint.h>
#include <stdbool.h>
#include "sdk_errors.h"
#include "ant_parameters.h"
#include "nrf_sdh_ant.h"
#include "ant_channel_config.h"
#include "ant_bsc_pages.h"

#define BSC_ANTPLUS_RF_FREQ      0x39u                      ///< Frequency, decimal 57 (2457 MHz).

#define BSC_SPEED_DEVICE_TYPE    0x7B                       ///< Device type reserved for ANT+ bike speed sensor.
#define BSC_CADENCE_DEVICE_TYPE  0x7A                       ///< Device type reserved for ANT+ bike cadence sensor.
#define BSC_COMBINED_DEVICE_TYPE 0x79                       ///< Device type reserved for ANT+ bike combined speed and cadence sensor.

#define BSC_MSG_PERIOD_4Hz       1u                         ///< Message period, 4 Hz (in basic period counts, where basic period time = 0.25 s).
#define BSC_MSG_PERIOD_2Hz       2u                         ///< Message period, 2 Hz (in basic period counts).
#define BSC_MSG_PERIOD_1Hz       4u                         ///< Message period, 1 Hz (in basic period counts).
#define BSC_MSG_PERIOD_SPEED     0x1FB6u                    ///< Message period in ticks, decimal 8118 (4.04 Hz).
#define BSC_MSG_PERIOD_CADENCE   0x1FA6u                    ///< Message period in ticks, decimal 8102 (4.04 Hz).
#define BSC_MSG_PERIOD_COMBINED  0x1F96u                    ///< Message period in ticks, decimal 8086 (4.05 Hz).

#define BSC_EXT_ASSIGN           0x00                       ///< ANT ext assign (see Ext. Assign Channel Parameters in ant_parameters.h: @ref ant_parameters).
#define BSC_DISP_CHANNEL_TYPE    CHANNEL_TYPE_SLAVE_RX_ONLY ///< Display BSC channel type.
#define BSC_SENS_CHANNEL_TYPE    CHANNEL_TYPE_MASTER        ///< Sensor BSC channel type.

/**@brief Select the basic ANT channel period (in ticks) for the BSC profile depending on the device type.
 *
 * @param[in]  DEVICE_TYPE          Type of device. Supported types: @ref BSC_SPEED_DEVICE_TYPE, @ref BSC_CADENCE_DEVICE_TYPE,
 *                                  @ref BSC_COMBINED_DEVICE_TYPE.
 */
#define BSC_DEVICE_TICKS(DEVICE_TYPE)                                                   \
        ((DEVICE_TYPE) == (BSC_SPEED_DEVICE_TYPE) ? (BSC_MSG_PERIOD_SPEED) :            \
        ((DEVICE_TYPE) == (BSC_CADENCE_DEVICE_TYPE) ? (BSC_MSG_PERIOD_CADENCE) :        \
        ((DEVICE_TYPE) == (BSC_COMBINED_DEVICE_TYPE) ? (BSC_MSG_PERIOD_COMBINED) : 0u)))

/**@brief Calculate the channel period (in ticks) depending on the device type and the chosen message frequency.
 *
 * @param[in]  DEVICE_TYPE          Type of device. Supported types: @ref BSC_SPEED_DEVICE_TYPE, @ref BSC_CADENCE_DEVICE_TYPE,
 *                                  @ref BSC_COMBINED_DEVICE_TYPE.
 * @param[in]  BSC_MSG_PERIOD       Channel data period. The BSC profile supports only the following periods:
 *                                  @ref BSC_MSG_PERIOD_4Hz, @ref BSC_MSG_PERIOD_2Hz, @ref BSC_MSG_PERIOD_1Hz.
 */
#define BSC_PERIOD_TICKS(DEVICE_TYPE, BSC_MSG_PERIOD)       \
        ((BSC_DEVICE_TICKS(DEVICE_TYPE)) * (BSC_MSG_PERIOD))

/**@brief Initialize an ANT channel configuration structure for the BSC profile (Display).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  CHANNEL_NUMBER       Number of the channel assigned to the profile instance.
 * @param[in]  TRANSMISSION_TYPE    Type of transmission assigned to the profile instance.
 * @param[in]  DEVICE_TYPE          Type of device. Supported types: @ref BSC_SPEED_DEVICE_TYPE, @ref BSC_CADENCE_DEVICE_TYPE,
 *                                  @ref BSC_COMBINED_DEVICE_TYPE.
 * @param[in]  DEVICE_NUMBER        Number of the device assigned to the profile instance.
 * @param[in]  NETWORK_NUMBER       Number of the network assigned to the profile instance.
 * @param[in]  BSC_MSG_PERIOD       Channel data frequency in Hz. The BSC profile supports only the following frequencies:
 *                                  @ref BSC_MSG_PERIOD_4Hz, @ref BSC_MSG_PERIOD_2Hz, @ref BSC_MSG_PERIOD_1Hz.
 */
#define BSC_DISP_CHANNEL_CONFIG_DEF(NAME,                                       \
                                    CHANNEL_NUMBER,                             \
                                    TRANSMISSION_TYPE,                          \
                                    DEVICE_TYPE,                                \
                                    DEVICE_NUMBER,                              \
                                    NETWORK_NUMBER,                             \
                                    BSC_MSG_PERIOD)                             \
static const ant_channel_config_t   CONCAT_2(NAME, _channel_bsc_disp_config) =  \
    {                                                                           \
        .channel_number     = (CHANNEL_NUMBER),                                 \
        .channel_type       = BSC_DISP_CHANNEL_TYPE,                            \
        .ext_assign         = BSC_EXT_ASSIGN,                                   \
        .rf_freq            = BSC_ANTPLUS_RF_FREQ,                              \
        .transmission_type  = (TRANSMISSION_TYPE),                              \
        .device_type        = (DEVICE_TYPE),                                    \
        .device_number      = (DEVICE_NUMBER),                                  \
        .channel_period     = BSC_PERIOD_TICKS(DEVICE_TYPE, BSC_MSG_PERIOD),    \
        .network_number     = (NETWORK_NUMBER),                                 \
    }
#define BSC_DISP_CHANNEL_CONFIG(NAME) &CONCAT_2(NAME, _channel_bsc_disp_config)

/**@brief Initialize an ANT channel configuration structure for the BSC profile (Transmitter).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  CHANNEL_NUMBER       Number of the channel assigned to the profile instance.
 * @param[in]  TRANSMISSION_TYPE    Type of transmission assigned to the profile instance.
 * @param[in]  DEVICE_TYPE          Type of device. Supported types: @ref BSC_SPEED_DEVICE_TYPE, @ref BSC_CADENCE_DEVICE_TYPE,
 *                                  @ref BSC_COMBINED_DEVICE_TYPE.
 * @param[in]  DEVICE_NUMBER        Number of the device assigned to the profile instance.
 * @param[in]  NETWORK_NUMBER       Number of the network assigned to the profile instance.
 */
#define BSC_SENS_CHANNEL_CONFIG_DEF(NAME,                                           \
                                    CHANNEL_NUMBER,                                 \
                                    TRANSMISSION_TYPE,                              \
                                    DEVICE_TYPE,                                    \
                                    DEVICE_NUMBER,                                  \
                                    NETWORK_NUMBER)                                 \
static const ant_channel_config_t   NAME##_channel_bsc_sens_config =                \
    {                                                                               \
        .channel_number     = (CHANNEL_NUMBER),                                     \
        .channel_type       = BSC_SENS_CHANNEL_TYPE,                                \
        .ext_assign         = BSC_EXT_ASSIGN,                                       \
        .rf_freq            = BSC_ANTPLUS_RF_FREQ,                                  \
        .transmission_type  = (TRANSMISSION_TYPE),                                  \
        .device_type        = (DEVICE_TYPE),                                        \
        .device_number      = (DEVICE_NUMBER),                                      \
        .channel_period     = BSC_PERIOD_TICKS(DEVICE_TYPE, BSC_MSG_PERIOD_4Hz),    \
        .network_number     = (NETWORK_NUMBER),                                     \
    }
#define BSC_SENS_CHANNEL_CONFIG(NAME) &NAME##_channel_bsc_sens_config

/**@brief Initialize an ANT profile configuration structure for the BSC profile (Display).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  EVT_HANDLER          Event handler to be called for handling events in the BSC profile.
 */
#define BSC_DISP_PROFILE_CONFIG_DEF(NAME,                                       \
                                    EVT_HANDLER)                                \
static ant_bsc_disp_cb_t            CONCAT_2(NAME, _bsc_disp_cb);               \
static const ant_bsc_disp_config_t  CONCAT_2(NAME, _profile_bsc_disp_config) =  \
    {                                                                           \
        .p_cb               = &CONCAT_2(NAME, _bsc_disp_cb),                    \
        .evt_handler        = (EVT_HANDLER),                                    \
    }
#define BSC_DISP_PROFILE_CONFIG(NAME) &CONCAT_2(NAME, _profile_bsc_disp_config)


/**@brief Initialize an ANT profile configuration structure for the BSC profile (Sensor).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  PAGE_1_PRESENT       Determines whether page 1 is included.
 * @param[in]  PAGE_4_PRESENT       Determines whether page 4 is included.
 * @param[in]  MAIN_PAGE_NUMBER     Determines the main data page (@ref ANT_BSC_PAGE_0 or @ref ANT_BSC_PAGE_5 or @ref ANT_BSC_COMB_PAGE_0).
 * @param[in]  EVT_HANDLER          Event handler to be called for handling events in the BSC profile.
 */
#define BSC_SENS_PROFILE_CONFIG_DEF(NAME,                                       \
                                    PAGE_1_PRESENT,                             \
                                    PAGE_4_PRESENT,                             \
                                    MAIN_PAGE_NUMBER,                           \
                                    EVT_HANDLER)                                \
static ant_bsc_sens_cb_t            CONCAT_2(NAME, _bsc_sens_cb);               \
static const ant_bsc_sens_config_t  CONCAT_2(NAME, _profile_bsc_sens_config) =  \
    {                                                                           \
        .page_1_present     = (PAGE_1_PRESENT),                                 \
        .page_4_present     = (PAGE_4_PRESENT),                                 \
        .main_page_number   = (MAIN_PAGE_NUMBER),                               \
        .p_cb               = &CONCAT_2(NAME, _bsc_sens_cb),                    \
        .evt_handler        = (EVT_HANDLER),                                    \
    }
#define BSC_SENS_PROFILE_CONFIG(NAME) &CONCAT_2(NAME, _profile_bsc_sens_config)


/**@brief BSC page number type. */
typedef enum{
    ANT_BSC_PAGE_0,                         ///< Main data page number 0.
    ANT_BSC_PAGE_1,                         ///< Background data page number 1. This page is optional.
    ANT_BSC_PAGE_2,                         ///< Background data page number 2.
    ANT_BSC_PAGE_3,                         ///< Background data page number 3.
    ANT_BSC_PAGE_4,                         ///< Background data page number 4. This page is optional.
    ANT_BSC_PAGE_5,                         ///< Main data page number 5. This page is optional.
    ANT_BSC_COMB_PAGE_0                     ///< Main data page number 0 for combined speed and cadence sensor.
} ant_bsc_page_t;

/**@brief BSC profile event type. */
typedef enum{
    ANT_BSC_PAGE_0_UPDATED      = ANT_BSC_PAGE_0,       ///< Data page 0 has been updated (Display) or sent (Sensor).
    ANT_BSC_PAGE_1_UPDATED      = ANT_BSC_PAGE_1,       ///< Data page 0 and page 1 have been updated (Display) or sent (Sensor).
    ANT_BSC_PAGE_2_UPDATED      = ANT_BSC_PAGE_2,       ///< Data page 0 and page 2 have been updated (Display) or sent (Sensor).
    ANT_BSC_PAGE_3_UPDATED      = ANT_BSC_PAGE_3,       ///< Data page 0 and page 3 have been updated (Display) or sent (Sensor).
    ANT_BSC_PAGE_4_UPDATED      = ANT_BSC_PAGE_4,       ///< Data page 0 and page 4 have been updated (Display) or sent (Sensor).
    ANT_BSC_PAGE_5_UPDATED      = ANT_BSC_PAGE_5,       ///< Data page 0 and page 5 have been updated (Display) or sent (Sensor).
    ANT_BSC_COMB_PAGE_0_UPDATED = ANT_BSC_COMB_PAGE_0,  ///< Combined Speed and cadence data page has been updated (Display) or sent (Sensor).
} ant_bsc_evt_t;

// Forward declaration of the ant_bsc_profile_t type.
typedef struct ant_bsc_profile_s ant_bsc_profile_t;

/**@brief BSC event handler type. */
typedef void (* ant_bsc_evt_handler_t) (ant_bsc_profile_t *, ant_bsc_evt_t);

#include "ant_bsc_local.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief BSC Display configuration structure. */
typedef struct
{
    ant_bsc_disp_cb_t     * p_cb;               ///< Pointer to the data buffer for internal use.
    ant_bsc_evt_handler_t   evt_handler;        ///< Event handler to be called for handling events in the BSC profile.
} ant_bsc_disp_config_t;

/**@brief BSC Sensor configuration structure. */
typedef struct
{
    bool                    page_1_present;     ///< Determines whether page 1 is included.
    bool                    page_4_present;     ///< Determines whether page 4 is included.
    ant_bsc_page_t          main_page_number;   ///< Determines the main data page (@ref ANT_BSC_PAGE_0 or @ref ANT_BSC_PAGE_5 or @ref ANT_BSC_COMB_PAGE_0).
    ant_bsc_sens_cb_t     * p_cb;               ///< Pointer to the data buffer for internal use.
    ant_bsc_evt_handler_t   evt_handler;        ///< Event handler to be called for handling events in the BSC profile.
} ant_bsc_sens_config_t;

/**@brief BSC profile structure. */
struct ant_bsc_profile_s
{
    uint8_t                         channel_number; ///< Channel number assigned to the profile.
    union {
        ant_bsc_disp_cb_t * p_disp_cb;
        ant_bsc_sens_cb_t * p_sens_cb;
    } _cb;                                          ///< Pointer to internal control block.
    ant_bsc_evt_handler_t           evt_handler;    ///< Event handler to be called for handling events in the BSC profile.
    ant_bsc_page0_data_t            page_0;         ///< Page 0.
    ant_bsc_page1_data_t            page_1;         ///< Page 1.
    ant_bsc_page2_data_t            page_2;         ///< Page 2.
    ant_bsc_page3_data_t            page_3;         ///< Page 3.
    ant_bsc_page4_data_t            page_4;         ///< Page 4.
    ant_bsc_page5_data_t            page_5;         ///< Page 5.
    ant_bsc_combined_page0_data_t   page_comb_0;    ///< Page 0 for combined speed and cadence sensor.
};

/** @name Defines for accessing ant_bsc_profile_t member variables
@{ */
#define BSC_PROFILE_event_time          page_0.event_time
#define BSC_PROFILE_rev_count           page_0.rev_count
#define BSC_PROFILE_operating_time      page_1.operating_time
#define BSC_PROFILE_manuf_id            page_2.manuf_id
#define BSC_PROFILE_serial_num          page_2.serial_num
#define BSC_PROFILE_hw_version          page_3.hw_version
#define BSC_PROFILE_sw_version          page_3.sw_version
#define BSC_PROFILE_model_num           page_3.model_num
#define BSC_PROFILE_fract_bat_volt      page_4.fract_bat_volt
#define BSC_PROFILE_coarse_bat_volt     page_4.coarse_bat_volt
#define BSC_PROFILE_bat_status          page_4.bat_status
#define BSC_PROFILE_stop_indicator      page_5.stop_indicator
#define BSC_PROFILE_cadence_event_time  page_comb_0.cadence_event_time
#define BSC_PROFILE_cadence_rev_count   page_comb_0.cadence_rev_count
#define BSC_PROFILE_speed_event_time    page_comb_0.speed_event_time
#define BSC_PROFILE_speed_rev_count     page_comb_0.speed_rev_count
/** @} */

/**@brief Function for initializing the ANT BSC profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 * @param[in]  p_disp_config    Pointer to the BSC display configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
ret_code_t ant_bsc_disp_init(ant_bsc_profile_t           * p_profile,
                             ant_channel_config_t const  * p_channel_config,
                             ant_bsc_disp_config_t const * p_disp_config);

/**@brief Function for initializing the ANT BSC profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 * @param[in]  p_sens_config    Pointer to the BSC sensor configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
ret_code_t ant_bsc_sens_init(ant_bsc_profile_t           * p_profile,
                             ant_channel_config_t const  * p_channel_config,
                             ant_bsc_sens_config_t const * p_sens_config);

/**@brief Function for opening the profile instance channel for the ANT BSC Display.
 *
 * Before calling this function, pages should be configured.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @retval     NRF_SUCCESS      If the channel was successfully opened. Otherwise, an error code is returned.
 */
ret_code_t ant_bsc_disp_open(ant_bsc_profile_t * p_profile);

/**@brief Function for opening the profile instance channel for the ANT BSC Sensor.
 *
 * Before calling this function, pages should be configured.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @retval     NRF_SUCCESS      If the channel was successfully opened. Otherwise, an error code is returned.
 */
ret_code_t ant_bsc_sens_open(ant_bsc_profile_t * p_profile);

/**@brief Function for handling the Sensor ANT events.
 *
 * @details This function handles all events from the ANT stack that are of interest to the Bicycle Speed and Cadence Sensor profile.
 *
 * @param[in]   p_ant_evt     Event received from the ANT stack.
 * @param[in]   p_context       Pointer to the profile instance.
 */
void ant_bsc_sens_evt_handler(ant_evt_t * p_ant_evt, void * p_context);

/**@brief Function for handling the Display ANT events.
 *
 * @details This function handles all events from the ANT stack that are of interest to the Bicycle Speed and Cadence Display profile.
 *
 * @param[in]   p_ant_evt     Event received from the ANT stack.
 * @param[in]   p_context       Pointer to the profile instance.
 */
void ant_bsc_disp_evt_handler(ant_evt_t * p_ant_evt, void * p_context);


#ifdef __cplusplus
}
#endif

#endif // ANT_BSC_H__
/** @} */

