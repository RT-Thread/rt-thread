/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
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
#ifndef MAC_MLME_RX_ENABLE_H_INCLUDED
#define MAC_MLME_RX_ENABLE_H_INCLUDED

#if (CONFIG_RXE_ENABLED == 1)

#include <stdint.h>
#include <stdbool.h>
#include "mac_common.h"
#include "mac_task_scheduler.h"

/** @file
 * The MAC MLME RX-Enable module declares the MAC RX-Enable primitives and necessary types
 * according to the MAC specification.
 *
 * @defgroup mac_rx_enable MAC MLME RX-Enable API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MLME RX-Enable API.
 * @details The MAC RX-Enable module declares MLME RX-Enable primitives and necessary types according to
 * the MAC specification. More specifically, MLME RX-Enable request aka mlme_rx_enable_req(),
 * and MLME RX-Enable confirm callback typedef aka mlme_rx_enable_conf_cb_t primitives are
 * declared. One additional primitive not covered by the standard is declared. This is
 * mlme_rx_enable() which is synchronous (i.e. does not require confirmation) version of
 * mlme_rx_enable_req().
 */

/**
 * @brief  MLME-RX-ENABLE.confirm
 *
 * @details The MLME-RX-ENABLE.confirm primitive reports the results of an attempt
 * to enable or disable the receiver.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.10.2
 */
typedef struct
{
    mac_status_t   status;               /**< Status of operation. */
} mlme_rx_enable_conf_t;


/**
 * @brief   MLME-RX-ENABLE.request
 *
 * @details The MLME-RX-ENABLE.request primitive allows the next higher layer
 * to request that the receiver is either enabled for a finite period of time or disabled.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.10.1
 */
typedef struct
{
    /** Do not edit this field. */
    mac_abstract_req_t      service;

    /** Confirm to this request. */
    mlme_rx_enable_conf_t   confirm;

    /**
     * @details
     * TRUE if the requested operation can be deferred until the next superframe
     * if the requested time has already passed.
     * FALSE if the requested operation is only to be attempted in the current superframe.
     *
     * If the issuing device is the PAN coordinator, the term superframe refers to its own
     * superframe. Otherwise, the term refers to the superframe of the coordinator through
     * which the issuing device is associated.
     *
     * @note This parameter is ignored for nonbeacon-enabled PANs.
     */
    bool           defer_permit;

    /**
     * @details
     * The number of symbols measured from the start of the superframe before the receiver is
     * to be enabled or disabled.
     * This is a 24-bit value, and the precision of this value shall be a minimum of 20 bits,
     * with the lowest 4 bits being the least significant.
     *
     * If the issuing device is the PAN coordinator, the term superframe refers to its own
     * superframe. Otherwise, the term refers to the superframe of the coordinator through
     * which the issuing device is associated.
     *
     * @note This parameter is ignored for nonbeacon-enabled PANs.
     */
    uint32_t       rx_on_time;

    /**
     * The number of symbols the receiver is to be enabled for.
     *
     * If this parameter is equal to 0x000000, the receiver is to be disabled.
     */
    uint32_t       rx_on_duration;
} mlme_rx_enable_req_t;


/**
 * @brief   Customer's function of confirmation.
 *
 * @details The MLME-RX-ENABLE.confirm primitive is generated by the MLME and issued to
 * its next higher layer in response to an MLME-RX-ENABLE.request primitive.
 *
 * @param pointer to a confirmation primitive.
 */
typedef void (* mlme_rx_enable_conf_cb_t)(mlme_rx_enable_conf_t *);

/**
 * @brief   MLME-RX-ENABLE.request service
 *
 * @details The MLME-RX-ENABLE.request primitive is generated by the next higher layer and
 * issued to the MLME to enable the receiver for a fixed duration, at a time relative to the
 * start of the current or next superframe on a beacon-enabled PAN or immediately on a
 * nonbeacon-enabled PAN. This primitive may also be generated to cancel a previously generated
 * request to enable the receiver. After request completion, user callback will be issued with
 * valid data stored in structure mlme_rx_enable_conf_t.
 *
 * @note The receiver is enabled or disabled exactly once per primitive request.
 *
 * @param[in] req  pointer to MLME-RX-ENABLE request structure.
 * @param[in] conf_cb - pointer to confirm function (user callback).
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.10.1
 */
void mlme_rx_enable_req(mlme_rx_enable_req_t * req, mlme_rx_enable_conf_cb_t conf_cb);


/**
 * @brief   Enables permission for receiving.
 *
 * @details Optional. Not covered by a standard.
 *
 * @param[in] req  pointer to MLME-RX-ENABLE request structure.
 *
 * @return status of operation.
 */
mac_status_t mlme_rx_enable(mlme_rx_enable_req_t * req);

/** @} */

#endif // (CONFIG_RXE_ENABLED == 1)

#endif // MAC_MLME_RX_ENABLE_H_INCLUDED
