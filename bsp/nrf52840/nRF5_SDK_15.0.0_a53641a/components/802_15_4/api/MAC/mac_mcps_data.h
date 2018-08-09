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
#ifndef MAC_MCPS_DATA_H_INCLUDED
#define MAC_MCPS_DATA_H_INCLUDED

#include <stdint.h>
#include "mac_common.h"
#include "mac_task_scheduler.h"

/** @file
 * The MAC Data module declares the MAC Data transmittion routines and necessary types
 * according to the MAC specification.
 *
 * @defgroup mac_data MAC MCPS Data API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MCPS Data API.
 * @details The MAC MCPS Data module declares the MAC Data transmission routines and necessary types according
 * to the MAC specification. More specifically, MAC data request mcps_data_req(), and MAC Data
 * indication mcps_data_ind() primitives are declared. The confirmation callback typedef is
 * declared as mcps_data_conf_cb_t.
 */

/**
 * @brief TX options bit fields.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.1.1.
 */
#define TX_ACKNOWLEDGED_BIT    (0)
#define TX_GTS_BIT             (1)
#define TX_INDIRECT_BIT        (2)


/**
 * @brief   TX options for MAC data transmission.
 *
 * @details The three bits (b0, b1, b2) indicate the transmission options for this MSDU.
 * For b0, 1 = acknowledged transmission, 0 = unacknowledged transmission.
 * For b1, 1 = GTS transmission, 0 = CAP transmission for a beacon-enabled PAN.
 * For b2, 1 = indirect transmission, 0 = direct transmission.
 * For a nonbeacon-enabled PAN, bit b1 should always be set to 0.
 */
typedef struct
{
    uint8_t   ack      : 1;
    uint8_t   gts      : 1;
    uint8_t   indirect : 1;
    uint8_t            : 5;
} mac_tx_options_t;


/**
 * @brief   MCPS-DATA.confirm.
 *
 * @details The MCPS-DATA.confirm primitive reports the results of a request to transfer
 * a data SPDU (MSDU) from a local SSCS entity to a single peer SSCS entity.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.1.2.
 */
typedef struct
{
    /** The handle associated with the MSDU being confirmed. */
    uint8_t                 msdu_handle;

    /** The status of the last MSDU transmission. */
    mac_status_t            status;

    /**
     * Optional. The time, in symbols, at which the data was transmitted (see 7.5.4.1).
     *
     * The value of this parameter will be considered valid only if the value of the
     * status parameter is SUCCESS; if the status parameter is not equal to
     * SUCCESS, the value of the Timestamp parameter will not be used for any other
     * purpose. The symbol boundary is described by macSyncSymbolOffset (see Table 86 in 7.4.1).
     *
     * This is a 24-bit value, and the precision of this value will be a minimum of 20 bits,
     * with the lowest 4 bits being the least significant.
     */
    uint32_t                timestamp;
} mcps_data_conf_t;


/**
 * @brief   MCPS-DATA.request.
 *
 * @details The MCPS-DATA.request primitive requests the transfer of
 * a data SPDU (i.e., MSDU) from a local SSCS entity to a single peer SSCS entity.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.1.1.
 */
typedef struct
{
    /** Do not edit this field. */
    mac_abstract_req_t      service;

    /** Confirm to this request. */
    mcps_data_conf_t        confirm;

    /**
     * The source addressing mode for this primitive and
     * subsequent MPDU. This value can take one of the following values:
     * @ref mac_addr_mode_t
     * 0x00 = no address (addressing fields omitted, see 7.2.1.1.8).
     * 0x01 = reserved.
     * 0x02 = 16-bit short address.
     * 0x03 = 64-bit extended address.
     */
    mac_addr_mode_t         src_addr_mode;

    /**
     * The destination addressing mode for this primitive
     * and subsequent MPDU.
     * According to 7.1.1.1.1, Table 41.
     */
    mac_addr_mode_t         dst_addr_mode;

    /** The 16-bit PAN identifier of the entity to which the MSDU is being transferred. */
    uint16_t                dst_pan_id;

    /** The individual device address of the entity to which the MSDU is being transferred. */
    mac_addr_t              dst_addr;

    /** The number of octets contained in the MSDU to be transmitted by
     * the MAC sublayer entity.
     */
    uint8_t                 msdu_length;

    /**
     * The pointer to the set of octets forming the MSDU
     * to be transmitted by the MAC sublayer entity.
     *
     * Caller must provide enough space for MAC and PHY header before this pointer.
     */
    uint8_t               * msdu;

    /** The handle associated with the MSDU to be transmitted by the MAC sublayer entity. */
    uint8_t                 msdu_handle;

    /**
     * The  bits (b0, b1, b2) indicate the transmission options for this MSDU.
     * For b0, 1 = acknowledged transmission, 0 = unacknowledged transmission.
     * For b1, 1 = GTS transmission, 0 = CAP transmission for a beacon-enabled PAN.
     * For b2, 1 = indirect transmission, 0 = direct transmission.
     * For a nonbeacon-enabled PAN, bit b1 should always be set to 0.
     */
    mac_tx_options_t        tx_options;
#if (CONFIG_SECURE == 1)
    uint8_t                 security_level;            /**< Security level. */
    uint8_t                 key_id_mode;               /**< Key ID node. */
    uint64_t                key_source;                /**< Key source. */
    uint8_t                 key_index;                 /**< Key index. */
#endif
} mcps_data_req_t;

/**
 * @brief Private information passed with MCPS-DATA.indication.
 *        Not covered by the standard.
 */
typedef struct
{
    /** RSSI value, which corresponds to packet that caused this indication. */
    int8_t              rssi;
    /** Value of a pending bit from MHR. */
    uint8_t             pending_bit;
} mcps_data_ind_private_t;

/**
 * @brief   MCPS-DATA.indication
 *
 * @details The MCPS-DATA.indication primitive indicates the transfer of
 * a data SPDU (i.e., MSDU) from the MAC sublayer to the local SSCS entity.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.1.3
 */
typedef struct
{
    mcps_data_ind_private_t   service;

    /**
     * The source addressing mode for this primitive corresponding to the received MPDU.
     * According to 7.1.1.1.1, Table 43.
     */
    mac_addr_mode_t           src_addr_mode;

    /** The 16-bit PAN identifier of the entity from which the MSDU was received. */
    uint16_t                  src_pan_id;

    /** The individual device address of the entity from which the MSDU was received. */
    mac_addr_t                src_addr;

    /**
     * The destination addressing mode for this primitive corresponding to the received MPDU.
     * According to 7.1.1.1.1, Table 43.
     */
    mac_addr_mode_t           dst_addr_mode;

    /** The 16-bit PAN identifier of the entity to which the MSDU is being transferred. */
    uint16_t                  dst_pan_id;

    /** The individual device address of the entity to which the MSDU is being transferred. */
    mac_addr_t                dst_addr;

    /** The number of octets contained in the MSDU being indicated by the MAC sublayer entity. */
    uint8_t                   msdu_length;

    /**
     * The information that is required for the next higher layer to read incoming message and to
     * free the memory allocated for this message.
     */
    mac_payload_descriptor_t  msdu;

    /**
     * LQI value measured during reception of the MPDU.
     * Lower values represent lower LQI (see 6.9.8).
     */
    uint8_t                   mpdu_link_quality;

    /** The DSN of the received data frame. */
    uint8_t                   dsn;

    /**
     * Optional. The time, in symbols, at which the data was received (see 7.5.4.1).
     * The symbol boundary is described by macSyncSymbolOffset (see Table 86 in 7.4.1).
     *
     * This is a 24-bit value, and the precision of this value shall be a minimum of 20 bits,
     * with the lowest 4 bits being the least significant.
     */
    uint32_t                timestamp;
#if (CONFIG_SECURE == 1)
    uint8_t                 security_level;            /**< Security level. */
    uint8_t                 key_id_mode;               /**< Key ID node. */
    uint64_t                key_source;                /**< Key source. */
    uint8_t                 key_index;                 /**< Key index. */
#endif
} mcps_data_ind_t;


/**
 * @brief Confirmation function.
 *
 * @details The MCPS-DATA.confirm primitive is generated by the MAC sublayer
 * entity in response to an MCPS-DATA. request primitive. The MCPS-DATA.confirm
 * primitive returns a status of either SUCCESS, indicating that the request to
 * transmit was successful, or the appropriate error code.
 * The status values are fully described in 7.1.1.1.3 and subclauses referenced by 7.1.1.1.3.
 *
 * @param Pointer to confirmation primitive.
 */
typedef void (* mcps_data_conf_cb_t)(mcps_data_conf_t *);


/**
 * @brief   MCPS-DATA.request service
 *
 * @details The MCPS-DATA.request primitive is generated by a local SSCS entity
 * when a data SPDU (i.e., MSDU) is to be transferred to a peer SSCS entity.
 * After request completion, user callback will be issued with
 * valid data stored in structure @ref mcps_data_conf_t.
 *
 * @param req     Pointer to MCPS-DATA request structure.
 * @param conf_cb Pointer to confirmation function (user callback).
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.1.2.
 */
void mcps_data_req(mcps_data_req_t * req, mcps_data_conf_cb_t conf_cb);


/**
 * @brief   MCPS-DATA.indication handler.
 *
 * @details The MCPS-DATA.indication primitive is generated by the MAC sublayer and
 * issued to the SSCS on receipt of a data frame at the local MAC sublayer entity
 * that passes the appropriate message filtering operations as described in 7.5.6.2.
 *
 * @param ind MCPS-DATA.indication structure.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.1.3.
 */
extern void mcps_data_ind(mcps_data_ind_t * ind);

/**
 * @brief   Free memory allocated for incoming message.
 *
 * @details The function will be invoked after all manipulations
 * with MSDU are completed. That is necessary to return the memory allocated by MAC
 * into the heap.
 *
 * @param p_payload_descriptor - Pointer to MSDU descriptor.
 */
void mac_mem_msdu_free(mac_payload_descriptor_t * p_payload_descriptor);

/** @} */

#endif // MAC_MCPS_DATA_H_INCLUDED
