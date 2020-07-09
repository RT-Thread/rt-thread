/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
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
#ifndef MAC_MLME_SCAN_H_INCLUDED
#define MAC_MLME_SCAN_H_INCLUDED

#include <stdint.h>
#include "mac_common.h"
#include "mac_mlme_beacon_notify.h"
#include "mac_task_scheduler.h"

/** @file
 * The MAC MLME Scan module declares the MAC Scan primitives and necessary types
 * according to the MAC specification.
 *
 * @defgroup mac_scan MAC MLME Scan API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MLME Scan API.
 * @details The MAC Scan module declares MLME Scan primitives and necessary types according to
 * the MAC specification. More specifically, MLME Scan request aka mlme_scan_req(), and MLME
 * Scan confirm callback typedef aka mlme_scan_conf_cb_t primitives are declared.
 */

/**@brief Type of scan. */
typedef enum
{
    ED_SCAN = 0,                                        /**< Energy detection scan. */
    ACTIVE_SCAN,                                        /**< Active scan. */
    PASSIVE_SCAN,                                       /**< Passive scan. */
    ORPHAN_SCAN                                         /**< Orphan scan. */
} mac_scan_type_t;

/**
 * @brief MLME-SCAN.confirm
 *
 * @details The MLME-SCAN.confirm reports the result of the channel scan request.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.11.2
 */
typedef struct
{
    mac_status_t            status;                     /**< Status of operation. */
    mac_scan_type_t         scan_type;                  /**< Scan type. */
#ifdef CONFIG_SUB_GHZ
    uint8_t                 channel_page;               /**< Channel page. */
#endif
    uint32_t                unscanned_channels;         /**< Unscanned channels. */
    uint8_t                 result_list_size;           /**< Result list size. */
    uint8_t               * energy_detect_list;         /**< Energy detection list. */
    mac_pan_descriptor_t  * pan_descriptor_list;        /**< PAN descriptor list. */
} mlme_scan_conf_t;

/**
 * @brief MLME-SCAN.request
 *
 * @details The MLME-SCAN.request primitive is used to initiate a channel
 * scan over a given list of channels.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.11.1
 */
typedef struct
{
    /** Do not edit this field. */
    mac_abstract_req_t      service;

    /** Confirm to this request. */
    mlme_scan_conf_t        confirm;

    mac_scan_type_t         scan_type;                  /**< Scan type. */
    uint32_t                scan_channels;              /**< Scan channels. */
    uint8_t                 scan_duration;              /**< Scan duration. */

    uint8_t                 pan_descriptors_buf_size;   /**< PAN descriptor buffer size. */
    mac_pan_descriptor_t  * pan_descriptors_buf;        /**< PAN descriptor buffer. */

    uint8_t                 energy_detect_buf_size;     /**< Energy detection buffer size. */
    uint8_t               * energy_detect_buf;          /**< Energy detection buffer. */

#ifdef CONFIG_SUB_GHZ
    uint8_t                 channel_page;               /**< Channel page. */
#endif
#if (CONFIG_SECURE == 1)
    uint8_t                 security_level;             /**< Security level. */
    uint8_t                 key_id_mode;                /**< Key ID mode. */
    uint64_t                key_source;                 /**< Key source. */
    uint8_t                 key_index;                  /**< Key index. */
#endif
} mlme_scan_req_t;


/**
 * @brief User callback to scan request.
 *
 * @details The MLME-SCAN.confirm primitive is generated by the MLME and issued to
 * its next higher layer when the channel scan initiated with
 * the MLME-SCAN.request primitive has completed.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.11.2
 */
typedef void (* mlme_scan_conf_cb_t)(mlme_scan_conf_t *);


/**
 * @brief   MLME-SCAN request
 *
 * @details The MLME-SCAN.request primitive is generated by the next higher layer and
 * issued to its MLME to initiate a channel scan to search for activity within the POS
 * of the device. This primitive can be used to perform an ED scan to determine channel
 * usage, an active or passive scan to locate beacon frames containing any PAN identifier,
 * or an orphan scan to locate a PAN to which the device is currently associated.
 *
 * @param[in] req  MLME-SCAN request structure.
 * @param[in] conf_cb pointer to user callback.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.11.1
 */
void mlme_scan_req(mlme_scan_req_t * req, mlme_scan_conf_cb_t conf_cb);

/** @} */

#endif // MAC_MLME_SCAN_H_INCLUDED
