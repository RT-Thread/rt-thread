/**
 * Copyright (c) 2016 - 2018 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
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
#ifndef MAC_MLME_START_H_INCLUDED
#define MAC_MLME_START_H_INCLUDED

#if (CONFIG_START_ENABLED == 1)

#include <stdint.h>
#include "mac_common.h"
#include "sys_utils.h"
#include "mac_task_scheduler.h"

/** @file
 * The MAC MLME Start module declares the MAC Start primitives and necessary types
 * according to the MAC specification.
 *
 * @defgroup mac_start MAC MLME Start API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MLME Start API.
 * @details The MAC Start module declares MLME Start primitives and necessary types according to
 * the MAC specification. More specifically, MLME Start request aka mlme_start_req(), and MLME
 * Start confirm callback typedef aka mlme_start_conf_cb_t primitives are declared.
 */

/**@brief   MLME-Start.confirm
 *
 * @details The MLME-Start.confirm primitive reports the results of a request
 * to start the device.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.14.1.2
 */
typedef struct
{
    mac_status_t    status;                               /**< Status of operation. */
} mlme_start_conf_t;

/**
 * @brief MLME-START.request
 *
 * @details The MLME-START.request primitive allows the PAN coordinator
 * to initiate a new PAN or to start using a new superframe configuration.
 * This primitive may also be used by a device already associated with an
 * existing PAN to start using a new superframe configuration.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.14.1.1
 */
typedef struct
{
    /** Do not edit this field. */
    mac_abstract_req_t      service;

    /** Confirm to this request. */
    mlme_start_conf_t       confirm;

    uint16_t                pan_id;                       /**< PAN ID. */
    uint8_t                 logical_channel;              /**< Logical channel. */
#ifdef CONFIG_SUB_GHZ
    uint8_t                 channel_page;                 /**< Channel page. */
#endif
    uint32_t                start_time;                   /**< Start time. */
    uint8_t                 beacon_order;                 /**< Beacon order. */
    uint8_t                 superframe_order;             /**< Superframe order. */
    bool                    pan_coordinator;              /**< Is PAN Coordinator? */
    bool                    battery_life_extension;       /**< Is battery life long? */
    bool                    coord_realignment;            /**< Is coordinator realignment? */
#if (CONFIG_SECURE == 1)
    /* The security parameters for the coordinator realignment are declared below. */
    uint8_t                 coord_realign_security_level; /**< Security level. */
    uint8_t                 coord_realign_key_id_mode;    /**< Key ID mode. */
    uint64_t                coord_realign_key_source;     /**< Key source. */
    uint8_t                 coord_realign_key_index;      /**< Key index. */

    /* The security parameters for the beacon are declared below. */
    uint8_t                 beacon_security_level;        /**< Security level. */
    uint8_t                 beacon_key_id_mode;           /**< Key ID mode. */
    uint64_t                beacon_key_source;            /**< Key source. */
    uint8_t                 beacon_key_index;             /**< Key index. */
#endif
} mlme_start_req_t;


/**
 * @brief Callback to the next higher layer.
 *
 * @details After request completion, passed callback
 * will be issued with status provided as a parameter.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.14.2.2
 */
typedef void (* mlme_start_conf_cb_t)(mlme_start_conf_t *);


/**
 * @brief   MLME-START request.
 *
 * @details Generated by the next higher layer and issued to its MLME to
 * request that a device starts using a new superframe configuration.
 *
 * @param[in] req  MLME-START request structure.
 * @param[in] conf_cb pointer to user callback.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.14.1.2
 */
void mlme_start_req(mlme_start_req_t * req, mlme_start_conf_cb_t conf_cb);

/** @} */

#endif // (CONFIG_START_ENABLED == 1)

#endif  // MAC_MLME_START_H_INCLUDED
