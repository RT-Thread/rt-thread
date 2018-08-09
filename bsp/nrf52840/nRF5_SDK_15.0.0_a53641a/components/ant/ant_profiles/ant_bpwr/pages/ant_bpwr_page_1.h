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
#ifndef ANT_BPWR_PAGE_1_H__
#define ANT_BPWR_PAGE_1_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_bpwr_page1 Bicycle Power profile page 1
 * @{
 * @ingroup ant_sdk_profiles_bpwr_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief BPWR Calibration ID.
 */
typedef enum
{
    ANT_BPWR_CALIB_ID_NONE                  = 0x00,
    ANT_BPWR_CALIB_ID_MANUAL                = 0xAA, ///< Calibration Request: Manual Zero.
    ANT_BPWR_CALIB_ID_AUTO                  = 0xAB, ///< Calibration Request: Auto Zero Configuration.
    ANT_BPWR_CALIB_ID_MANUAL_SUCCESS        = 0xAC, ///< Calibration Response: Manual Zero Successful.
    ANT_BPWR_CALIB_ID_FAILED                = 0xAF, ///< Calibration Response: Failed.
    ANT_BPWR_CALIB_ID_CTF                   = 0x10, ///< Crank Torque Frequency (CTF) Power sensor Defined Message.
    ANT_BPWR_CALIB_ID_AUTO_SUPPORT          = 0x12, ///< Auto Zero Support.
    ANT_BPWR_CALIB_ID_CUSTOM_REQ            = 0xBA, ///< Custom Calibration Parameter Request.
    ANT_BPWR_CALIB_ID_CUSTOM_REQ_SUCCESS    = 0xBB, ///< Custom Calibration Parameter Response.
    ANT_BPWR_CALIB_ID_CUSTOM_UPDATE         = 0xBC, ///< Custom Calibration Parameter Update.
    ANT_BPWR_CALIB_ID_CUSTOM_UPDATE_SUCCESS = 0xBD, ///< Custom Calibration Parameter Update Response.
} ant_bpwr_calib_id_t;

/**@brief BPWR Calibration Auto Zero Status.
 */
typedef enum
{
    ANT_BPWR_AUTO_ZERO_NOT_SUPPORTED = 0xFF, ///< Auto Zero Not Supported.
    ANT_BPWR_AUTO_ZERO_OFF           = 0x00, ///< Auto Zero OFF.
    ANT_BPWR_AUTO_ZERO_ON            = 0x01, ///< Auto Zero ON.
} ant_bpwr_auto_zero_status_t;

/**@brief Data structure for Bicycle Power data page 1.
 */
typedef struct
{
    ant_bpwr_calib_id_t         calibration_id;   ///< Calibration request type.
    ant_bpwr_auto_zero_status_t auto_zero_status; ///< Status of automatic zero feature of power sensor.
    union
    {
        int16_t general_calib;
        uint8_t custom_calib[6];
    } data;
} ant_bpwr_page1_data_t;

/**@brief Initialize page 1.
 */
#define DEFAULT_ANT_BPWR_PAGE1()                                \
    (ant_bpwr_page1_data_t)                                     \
    {                                                           \
        .calibration_id     = ANT_BPWR_CALIB_ID_NONE,           \
        .auto_zero_status   = ANT_BPWR_AUTO_ZERO_NOT_SUPPORTED, \
        .data.general_calib = 0x00,                             \
    }

/**@brief Initialize page 1 with the general request.
 */
#define ANT_BPWR_GENERAL_CALIB_REQUEST()            \
    (ant_bpwr_page1_data_t)                         \
    {                                               \
        .calibration_id = ANT_BPWR_CALIB_ID_MANUAL, \
    }

/**@brief Function for encoding page 1.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_bpwr_page_1_encode(uint8_t                     * p_page_buffer,
                            ant_bpwr_page1_data_t const * p_page_data);

/**@brief Function for decoding page 1.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_bpwr_page_1_decode(uint8_t const         * p_page_buffer,
                            ant_bpwr_page1_data_t * p_page_data);



#ifdef __cplusplus
}
#endif

#endif // ANT_BPWR_PAGE_1_H__
/** @} */
