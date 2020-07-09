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
#ifndef MAC_MLME_ASSOCIATE_H_INCLUDED
#define MAC_MLME_ASSOCIATE_H_INCLUDED

#include <stdint.h>
#include "mac_common.h"
#include "mac_task_scheduler.h"

/** @file
 * The MAC Association module declares the MAC Association routines and necessary types/macros
 * according to the MAC specification.
 *
 * @defgroup mac_assoc MAC MLME Association API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MLME Association API.
 * @details The MLME Association module declares Association MAC routines and necessary macros/types according
 * to the MAC specification. More specifically, MLME Association request aka mlme_associate_req(),
 * MLME Association confirm callback typedef aka mlme_associate_conf_cb_t, MLME Association indication
 * as mlme_associate_ind(), and MLME Response aka mlme_associate_resp() primitives are declared.
 */

/**
 * @brief Capability information field.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.3.1.2.
 */
#define ALTERNATE_PAN_COORDINATOR_BIT     (0)
#define DEVICE_TYPE_BIT                   (1)
#define POWER_SOURCE_BIT                  (2)
#define RECEIVER_ON_WHEN_IDLE_BIT         (3)
#define SECURITY_CAPABILITY_BIT           (6)
#define ALLOCATE_ADDRESS_BIT              (7)


/**
 * @brief Capability information field.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.3.1.2.
 */
typedef struct
{
    uint8_t   alternate_pan_coordinator  : 1;
    uint8_t   device_type                : 1;
    uint8_t   power_source               : 1;
    uint8_t   rx_on_when_idle            : 1;
    uint8_t   reserved                   : 2;
    uint8_t   security_capability        : 1;
    uint8_t   allocate_address           : 1;
} mac_capability_t;

/**@brief The Alternate PAN Coordinator subfield of the Capability Information field. */
typedef enum
{
    MAC_CAP_CANNOT_BE_PAN_COORD = 0,  /**< Device is not capable of becoming
                                           the PAN coordinator.*/
    MAC_CAP_CAN_BE_PAN_COORD          /**< Device is capable of becoming
                                           the PAN coordinator.*/
} mac_cap_alt_pan_coord_t;

/**@brief The Device Type subfield of the Capability Information field. */
typedef enum
{
    MAC_CAP_RFD_DEVICE = 0,           /**< Device is an RFD.*/
    MAC_CAP_FFD_DEVICE                /**< Device is an FFD.*/
} mac_cap_device_type_t;

/**@brief The Power Source subfield of the Capability Information field. */
typedef enum
{
    MAC_CAP_BATTERY_POWERED = 0,      /**< Device is not AC-powered.*/
    MAC_CAP_MAINS_POWERED             /**< Device is receiving power from the
                                           alternating current mains.*/
} mac_cap_power_source_t;

/**@brief The Receiver On When Idle subfield of the Capability Information field. */
typedef enum
{
    MAC_CAP_RX_OFF_WHEN_IDLE = 0,     /**< Device conserves power during idle.*/
    MAC_CAP_RX_ON_WHEN_IDLE           /**< Device does not disable its receiver
                                           to conserve power during idle periods.*/
} mac_cap_rx_when_idle_t;

/**@brief The Security Capability subfield of the Capability Information field. */
typedef enum
{
    MAC_CAP_CANNOT_SECURE = 0,        /**< Device does not support securing.*/
    MAC_CAP_CAN_SECURE                /**< Device is capable of sending and receiving
                                           cryptographically protected MAC frames.*/
} mac_cap_secure_t;

/**@brief The Allocate Address subfield of the Capability Information field. */
typedef enum
{
    MAC_CAP_SHORT_ADDR_NOT_REQ = 0,   /**< The coordinator will not allocate a
                                           16-bit short address as a result of
                                           the association procedure.*/
    MAC_CAP_SHORT_ADDR_REQ            /**< The coordinator will allocate a
                                           16-bit short address as a result of
                                           the association procedure.*/
} mac_cap_allocate_addr_t;

#if (CONFIG_ASSOCIATE_REQ_ENABLED == 1)

/**
 * @brief   MLME-ASSOCIATE.confirm
 *
 * The MLME-ASSOCIATE.confirm primitive is generated by the initiating MLME and
 * issued to its next higher layer in response to an MLME-ASSOCIATE.request primitive.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.3.4.
 */
typedef struct
{
    uint16_t                assoc_short_address;       /**< Association short 16-bit address. */
    mac_status_t            status;                    /**< Status of operation. */
#if (CONFIG_SECURE == 1)
    uint8_t                 security_level;            /**< Security level. */
    uint8_t                 key_id_mode;               /**< Key ID mode. */
    uint64_t                key_source;                /**< Key source. */
    uint8_t                 key_index;                 /**< Key index. */
#endif
} mlme_associate_conf_t;


/**
 * @brief   MLME-ASSOCIATE.request.
 *
 * @details Allows a device to request an association with a coordinator.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.3.1.
 */
typedef struct
{
    /** Do not edit this field. */
    mac_abstract_req_t      service;

    /** Confirmation to this request. */
    mlme_associate_conf_t   confirm;

    /**
     * A total of 27 channels numbered 0 to 26.
     * are available per channel page (section 6.1.2.1).
     */
    uint8_t                 logical_channel;

    /**
     * A total of 32 channel pages are available
     * with channel pages 3 to 31 being reserved
     * for future use (section 6.1.2.2).
     */
#ifdef CONFIG_SUB_GHZ
    uint8_t                 channel_page;              /**< Channel page. */
#endif
    mac_addr_mode_t         coord_addr_mode;           /**< Coordinator address mode. */
    uint16_t                coord_pan_id;              /**< Coordinator PAN ID. */
    mac_addr_t              coord_address;             /**< Coordinator address. */
    mac_capability_t        capability_information;    /**< Capability information. */
#if (CONFIG_SECURE == 1)
    uint8_t                 security_level;            /**< Security level. */
    uint8_t                 key_id_mode;               /**< Key ID mode. */
    uint64_t                key_source;                /**< Key source. */
    uint8_t                 key_index;                 /**< Key index. */
#endif
} mlme_associate_req_t;


#if (CONFIG_ASSOCIATE_IND_ENABLED == 1)
/**
 * @brief   MLME-ASSOCIATE.indication.
 *
 * @details The MLME-ASSOCIATE.indication primitive is generated by the MLME of
 * the coordinator and issued to its next higher layer to indicate the reception
 * of an association request command.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.3.2.
 */
typedef struct
{
    uint64_t                device_address;            /**< 64-bit IEEE address. */
    uint8_t                 capability_information;    /**< Capability information. */
#if (CONFIG_SECURE == 1)
    uint8_t                 security_level;            /**< Security level. */
    uint8_t                 key_id_mode;               /**< Key ID mode. */
    uint64_t                key_source;                /**< Key source. */
    uint8_t                 key_index;                 /**< Key index. */
#endif
} mlme_associate_ind_t;


/**
 * @brief   MLME-ASSOCIATE.response.
 *
 * @details Generated by the next higher layer of a coordinator and issued
 * to its MLME in order to respond to the MLME-ASSOCIATE.indication primitive.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.3.3.
 */
typedef struct
{
    uint64_t                device_address;            /**< 64-bit IEEE address. */
    uint16_t                assoc_short_address;       /**< Association short 16-bit address. */
    mac_status_t            status;                    /**< Status of operation. */
#if (CONFIG_SECURE == 1)
    uint8_t                 security_level;            /**< Security level. */
    uint8_t                 key_id_mode;               /**< Key ID mode. */
    uint64_t                key_source;                /**< Key source. */
    uint8_t                 key_index;                 /**< Key index. */
#endif
} mlme_associate_resp_t;

#endif // (CONFIG_ASSOCIATE_IND_ENABLED == 1)

/**
 * @brief Confirmation function.
 *
 * @details The MLME-ASSOCIATE.confirm primitive is generated by the
 * initiating MLME and issued to its next higher layer in response to
 * an MLME-ASSOCIATE.request primitive. If the request was successful,
 * the status parameter will indicate a successful association, as
 * contained in the Status field of the association response command.
 * Otherwise, the status parameter indicates either an error code from
 * the received association response command or the appropriate error
 * code from Table 50.
 * The status values are fully described in 7.1.3.1.3 and subclauses referenced by 7.1.3.1.3.
 *
 * @param Pointer to confirmation primitive.
 */
typedef void (* mlme_associate_conf_cb_t)(mlme_associate_conf_t *);


/**
 * @brief   MLME-ASSOCIATE request.
 *
 * @details Requests an association with a PAN through a coordinator
 * After request completion, user callback will be issued with
 * valid data stored in structure mlme_set_conf_t.
 *
 * @param req  MLME_ASSOCIATE request structure.
 * @param conf_cb Pointer to user callback.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.3.5
 */
void mlme_associate_req(mlme_associate_req_t * req, mlme_associate_conf_cb_t conf_cb);


#if (CONFIG_ASSOCIATE_IND_ENABLED == 1)

/**
 * @brief   MLME-ASSOCIATE indication handler.
 *
 * @details Indicates an association with a PAN through a coordinator
 * next higher layer of a coordinator receives the MLME-ASSOCIATE.indication
 * primitive to determine whether to accept or reject the unassociated device
 * using an algorithm outside the scope of standard.
 *
 * @param ind  MLME ASSOCIATE indication structure.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.3.5.
 */
extern void mlme_associate_ind(mlme_associate_ind_t * ind);


/**
 * @brief   MLME-ASSOCIATE response.
 *
 * @details Respond to an association with a PAN and issue to its MLME in order to
 * respond to the MLME-ASSOCIATE.indication.
 * Response structure passed as a parameter to this function must be retained
 * in memory until the related MLME-COMM-STATUS.indication is received.
 *
 * @param resp  MLME_ASSOCIATE response structure.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.3.5.
 */
void mlme_associate_resp(mlme_associate_resp_t * resp);

#endif // (CONFIG_ASSOCIATE_IND_ENABLED == 1)

#endif // (CONFIG_ASSOCIATE_REQ_ENABLED == 1)

/** @} */

#endif // MAC_MLME_ASSOCIATE_H_INCLUDED
