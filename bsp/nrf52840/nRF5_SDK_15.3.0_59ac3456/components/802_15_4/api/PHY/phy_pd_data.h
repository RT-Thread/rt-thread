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
#ifndef PHY_PD_DATA_H_INCLUDED
#define PHY_PD_DATA_H_INCLUDED


#include <stdint.h>
#include <stdbool.h>
#include "sys_utils.h"
#include "sys_time.h"
#include "phy_common.h"
#include "mac_time.h"
#include "sys_queue.h"

/** @file
 * This file contains declarations of PHY Data transmission routines and necessary types.
 *
 * @defgroup phy_data PHY Data API
 * @ingroup phy_15_4
 * @{
 * @brief Module to declare PHY Data API
 * @details The PHY Data module declares the PHY Data transmission routines and necessary types according to
 * the PHY specification. More specifically, PHY data request pd_data_req(), PHY data confirm 
 * pd_data_conf(), and PHY Data indication pd_data_ind() primitives are declared.
 */

/**@brief   PD-DATA.request parameters.
 *
 * @details See 6.2.1.1 PD-DATA.request.
 *          See Table 6 - PD-DATA.request parameters.
 */
typedef struct
{
    /** The set of octets forming the PSDU to be transmitted by the PHY entity. */
    uint8_t * psdu;

    /** The number of octets contained in the PSDU to be transmitted by the PHY entity.
        Valid range: less or equal to @ref PHY_MAX_PACKET_SIZE. */
    uint8_t   psdu_length;
} pd_data_req_t;

/**@brief Private information which is passed with PD-DATA.confirm.
 *        Not covered by standard.
 */
typedef struct
{
    /** pending value to store pending bit value if frame was acknowledged. */
    bool  pending;
} pd_data_conf_private_t;

/**@brief   PD-DATA.confirm parameters.
 *
 * @details See 6.2.1.2 PD-DATA.confirm.
 *          See Table 7 - PD-DATA.confirm parameters.
 */
typedef struct
{
    /** Service field. */
    pd_data_conf_private_t  service;

    /** The result of the request to transmit a packet.
     *  Valid range: PHY_SUCCESS, PHY_RX_ON, PHY_TRX_OFF, PHY_BUSY_TX.
     *  See @ref phy_enum_t.
     *
     *  When radio chip successfully transmits data, but cannot receive
     *  ACK in FAST_ACK mode, the result is PHY_TX_ON.
     */
    phy_enum_t              status;
} pd_data_conf_t;

/**@brief Private information which is passed with PD-DATA.indication.
 *        Not covered by standard.
 */
typedef struct
{
    /** RSSI value, which corresponds to packet that caused this indication. */
    int8_t                  rssi;

    /** Buffer to store incoming frame. */
    uint8_t                 frame_buffer[PHY_MAX_PACKET_SIZE + PHY_MAX_HEADER_SIZE];

    /** Timestamp of the moment when PHY header octet reception has been started. */
    mac_timestamp_t         timestamp;

    /** This field allows storing instances of this structure in a queue. */
    sys_queue_item_t        queue_item;
#ifdef CONFIG_PHY_CERT_CRC_HOOK
    bool                    crc_status;
#endif
} pd_data_ind_private_t;

/**@brief   PD-DATA.indication parameters.
 *
 * @details See 6.2.1.3 PD-DATA.indication.
 *          See Table 8 - PD-DATA.indication parameters.
 */
typedef struct
{
    /** Service field. */
    pd_data_ind_private_t   service;

    /** The set of octets forming the PSDU received by the PHY entity. */
    uint8_t               * psdu;

    /** The number of octets contained in the PSDU received by the PHY entity.
        Valid range: less or equal to @ref PHY_MAX_PACKET_SIZE. */
    uint8_t                 psdu_length;

    /** Link quality (LQI) value measured during reception of the PPDU (see 6.9.8).
        Valid range: 0x00 - 0xFF. */
    uint8_t                 ppdu_link_quality;
} pd_data_ind_t;

/**@brief   PD-DATA.request primitive.
 *
 * @details The PD-DATA.request primitive requests the transfer of an MPDU (i.e., PSDU) 
 *          from the MAC sublayer to the local PHY entity.
 *          See 6.2.1.1 PD-DATA.request.
 *
 * @param[in]   req         Pointer to PD-DATA.request parameters. See @ref pd_data_req_t.
 */
void pd_data_req(pd_data_req_t * req);

/**@brief   PD-DATA.confirm primitive.
 *
 * @details Callback function, implemented by the next higher layer, 
 *          which handles the PD-DATA.confirm primitive.
 *          See 6.2.1.2 PD-DATA.confirm.
 *
 * @param[out]  conf      Pointer to PD-DATA.confirm parameters. See @ref pd_data_conf_t.
 */
void pd_data_conf(pd_data_conf_t * conf);

/**@brief   PD-DATA.indication primitive.
 *
 * @details The PD-DATA.indication primitive indicates the transfer of an MPDU (i.e., PSDU) 
 *          from the PHY to the local MAC sublayer entity.
 *          See 6.2.1.3 PD-DATA.indication.
 *          This function must be implemented by the next higher layer.
 *
 * @param[out]  ind     Pointer to PD-DATA.indication parameters. See @ref pd_data_ind_t.
 *                      Data are valid until next fully received packet.
 */
void pd_data_ind(pd_data_ind_t * ind);

/** @} */

#endif // PHY_PD_DATA_H_INCLUDED
