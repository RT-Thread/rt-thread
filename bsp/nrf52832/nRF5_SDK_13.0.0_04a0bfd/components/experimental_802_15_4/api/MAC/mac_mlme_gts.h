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
#ifndef MAC_MLME_GTS_H_INCLUDED
#define MAC_MLME_GTS_H_INCLUDED

#if (CONFIG_GTS_ENABLED == 1)

#include <stdint.h>
#include "mac_common.h"
#include "mac_task_scheduler.h"

/** @file
 * The MAC MLME GTS module declares the MAC Guaranteed time slots routines and
 * necessary types/macros according to the MAC specification.
 *
 * @defgroup mac_gts MAC MLME GTS API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MLME GTS API.
 * @details The MAC GTS module declares MAC Guaranteed Time Slots routines and necessary types according to
 * the MAC specification. More specifically, MLME GTS request aka mlme_gts_req(), MLME GTS indicaton
 * aka mlme_gts_ind(), and MLME GTS confirm callback typedef aka mlme_gts_conf_cb_t primitives are
 * declared.
 */

/**@brief   GTS directions, from device side. */
typedef enum
{
    MAC_GTS_DIR_TXONLY = 0,                /**< TX only direction. */
    MAC_GTS_DIR_RXONLY = 1                 /**< RX only direction. */
} mac_gts_direction_t;


/**@brief   GTS characteristics type. */
typedef enum
{
    MAC_GTS_DEALLOC = 0,                   /**< GTS Dealloc. */
    MAC_GTS_ALLOC   = 1                    /**< GTS Alloc. */
} mac_gts_characteristics_type_t;


/**@brief   MAC GTS characteristics (not packed)
 *
 * @details See Section 7.3.9.2
 */
typedef union
{
    struct
    {
        uint8_t gts_length                 : 4;
        uint8_t gts_direction              : 1;
        uint8_t characterictics_type       : 1;
        uint8_t                            : 2;
    } bit;
    uint8_t all;
} mac_gts_characteristics_t;

/**
 * @brief   MLME-GTS.confirm
 *
 * @details The MLME-GTS.confirm primitive reports the results of a
 * request to allocate a new GTS or deallocate an existing GTS.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.7.2
 */
typedef struct
{
    mac_gts_characteristics_t     gts_characteristics;  /**< GTS characteristics. */
    mac_status_t                  status;               /**< Status of operation. */
} mlme_gts_conf_t;


/**
 * @brief   MLME-GTS.request
 *
 * @details The MLME-GTS.request primitive allows a device to send a request
 * to the PAN coordinator to allocate a new GTS or to deallocate an existing GTS.
 * This primitive is also used by the PAN coordinator to initiate a GTS deallocation.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.7.1
 */
typedef struct
{
    /** Do not edit this field. */
    mac_abstract_req_t            service;

    /** Confirm to this request. */
    mlme_gts_conf_t               confirm;

    mac_gts_characteristics_t     gts_characteristics;  /**< GTS characteristics. */
#if (CONFIG_SECURE == 1)
    uint8_t                       security_level;       /**< Security level. */
    uint8_t                       key_id_mode;          /**< Key ID mode. */
    uint64_t                      key_source;           /**< Key source. */
    uint8_t                       key_index;            /**< Key index. */
#endif
} mlme_gts_req_t;


/**
 * @brief   MLME-GTS.indication
 *
 * @details The MLME-GTS.indication primitive indicates that a
 * GTS has been allocated or that a previously allocated GTS
 * has been deallocated.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.7.3
 */
typedef struct
{
    uint16_t                      device_address;       /**< Device address. */
    mac_gts_characteristics_t     gts_characteristics;  /**< GTS characteristics. */
#if (CONFIG_SECURE == 1)
    uint8_t                       security_level;       /**< Security level. */
    uint8_t                       key_id_mode;          /**< Key ID mode. */
    uint64_t                      key_source;           /**< Key source. */
    uint8_t                       key_index;            /**< Key index. */
#endif
} mlme_gts_ind_t;


/**
 * @brief   MLME-GTS confirm callback
 *
 * @details The MLME-GTS.confirm primitive is generated by the MLME and
 * issued to its next higher layer in response to a previously
 * issued MLME-GTS.request primitive.
 *
 * @param MLME_GTS callback structure.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.7.4
 */
typedef void (* mlme_gts_conf_cb_t)(mlme_gts_conf_t *);


/**
 * @brief   MLME-GTS request
 *
 * @details The MLME-GTS.request primitive is generated by the next higher
 * layer of a device and issued to its MLME to request the allocation of a
 * new GTS or to request the deallocation of an existing GTS. It is also
 * generated by the next higher layer of the PAN coordinator and issued to
 * its MLME to request the deallocation of an existing GTS.
 *
 * @param req  MLME_GTS request structure.
 * @param conf_cb pointer to user callback.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.7.4
 */
void mlme_gts_req(mlme_gts_req_t * req, mlme_gts_conf_cb_t conf_cb);


/**
 * @brief   MLME-GTS indication handler
 *
 * @details The MLME-GTS.indication primitive is generated by the MLME of
 * the PAN coordinator to its next higher layer whenever a GTS is allocated
 * or deallocated following the reception of a GTS request command (see 7.3.9)
 * by the MLME. The MLME of the PAN coordinator also generates this primitive when a GTS
 * deallocation is initiated by the PAN coordinator itself.
 *
 * @param ind MLME_GTS indication structure.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.7.4
 */
extern void mlme_gts_ind(mlme_gts_ind_t * ind);

/** @} */

#endif // (CONFIG_GTS_ENABLED == 1)

#endif // MAC_MLME_GTS_H_INCLUDED
