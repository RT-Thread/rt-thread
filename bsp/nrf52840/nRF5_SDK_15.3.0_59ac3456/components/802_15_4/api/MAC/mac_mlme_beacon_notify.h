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
#ifndef MAC_MLME_BEACON_NOTIFY_H_INCLUDED
#define MAC_MLME_BEACON_NOTIFY_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include "mac_common.h"
#include "mac_time.h"

/** @file
 * The MAC Beacon notify module declares the MAC beacon notification routine and necessary
 * types/macros according to the MAC specification.
 *
 * @defgroup mac_beacon_notify MAC MLME Beacon Notify API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MLME Beacon Notify API.
 * @details The MAC Beacon Notify module declares Beacon Notify MLME routines and necessary macros/types
 * according to the MAC specification. MAC MLME Beacon notify indication is declared as
 * mlme_beacon_notify_ind().
 */

/**@brief   This constant is defined in 7.2.2.1.7 Address List field
 *
 * @details The maximum number of addresses pending shall be limited to seven and may comprise
 *          both short and extended addresses.
 */
#define MAC_PENDING_ADDR_MAX    7

/*@brief    The maximum length of GTS fields inside beacon in octets.
 *
 * @details This definition is used to allocate memory for outgoing beacon.
 */
#define MAC_MAX_GTS_FIELD_LEN   23

/**@brief Superframe specification structure.*/
typedef struct
{
    uint16_t     beacon_order           : 4;
    uint16_t     superframe_order       : 4;
    uint16_t     final_cap_slot         : 4;
    uint16_t     battery_life_extension : 1;
    uint16_t     reserved               : 1;
    uint16_t     pan_coordinator        : 1;
    uint16_t     association_permit     : 1;
} mac_superframe_spec_t;


/** @brief List of pending addresses
 *  Short addresses are at the top of the table.
 */
typedef struct
{
    mac_addr_t              addr_list[MAC_PENDING_ADDR_MAX];
                                                    /**< Addresses array. */
    uint8_t                 short_addr_number;      /**< Number of short addresses in the array. */
    uint8_t                 ext_addr_number;        /**< Number of long addresses in the array. */
} mac_pending_addr_list_t;

/**@brief   PAN Descriptor structure.
 *
 * @details See Table 55-Elements of PANDescriptor.
 */
typedef struct
{
    mac_addr_mode_t         coord_addr_mode;        /**< Coordinator addressing mode. */
    uint16_t                coord_pan_id;           /**< Coordinator PAN ID. */
    mac_addr_t              coord_address;          /**< Coordinator address. */
    uint8_t                 logical_channel;        /**< Logical channel. */
#ifdef CONFIG_SUB_GHZ
    uint8_t                 channel_page;           /**< Channel page. */
#endif
    mac_superframe_spec_t   superframe_spec;        /**< Superframe specification. */
    bool                    gts_permit;             /**< Is GTS permitted? */
    uint8_t                 link_quality;           /**< Link quality. */
    mac_timestamp_t         timestamp;              /**< Timestamp. */
#if (CONFIG_SECURE == 1)
    uint8_t                 security_failure;       /**< Security failure. */
    uint8_t                 security_level;         /**< Security level. */
    uint8_t                 key_id_mode;            /**< Key ID mode. */
    uint64_t                key_source;             /**< Key source. */
    uint8_t                 key_index;              /**< Key index. */
#endif
} mac_pan_descriptor_t;


/**@brief   Pending Address Specification
 *
 * @details See Figure 51-Format of the Pending Address Specification field.
 */
typedef struct
{
    uint8_t     pending_short     : 3;
    uint8_t                       : 1;
    uint8_t     pending_extended  : 3;
    uint8_t                       : 1;
} mac_pend_addr_spec_t;


/**@brief   MLME-BEACON-NOTIFY.indication parameters
 *
 * @details See 7.1.5.1 MLME-BEACON-NOTIFY.indication
 */
typedef struct
{
    uint8_t                   bsn;                  /**< Beacon sequence number. */
    mac_pan_descriptor_t      pan_descriptor;       /**< PAN descriptor. */
    mac_pend_addr_spec_t      pend_addr_spec;       /**< Pending address specification. */
    mac_addr_t                addr_list[MAC_PENDING_ADDR_MAX];
                                                    /**< Addresses array. */
    uint8_t                   sdu_length;           /**< SDU length. */
    mac_payload_descriptor_t  sdu;                  /**< SDU. */
#if (CONFIG_SECURE == 1)
    uint8_t                   security_level;       /**< Security level. */
    uint8_t                   key_id_mode;          /**< Key ID mode. */
    uint64_t                  key_source;           /**< Key source. */
    uint8_t                   key_index;            /**< Key index. */
#endif
} mlme_beacon_notify_ind_t;


/**@brief   User implemented function, which handles MLME-BEACON-NOTIFY.indication.
 *
 * @details The MLME-BEACON-NOTIFY.indication primitive is used to send parameters contained
 *          within a beacon frame received by the MAC sublayer to the next higher layer.
 *          The primitive also sends a measure of the LQI and the time the beacon frame 
 *          was received. See 7.1.5.1 MLME-BEACON-NOTIFY.indication.
 *
 * @param  ind     MLME-BEACON-NOTIFY.indication parameters. See @ref mlme_beacon_notify_ind_t.
 */
extern void mlme_beacon_notify_ind(mlme_beacon_notify_ind_t * ind);

/** @} */

#endif // MAC_MLME_BEACON_NOTIFY_H_INCLUDED
