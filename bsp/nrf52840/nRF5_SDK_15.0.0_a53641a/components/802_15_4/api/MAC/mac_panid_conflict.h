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
#ifndef MAC_PANID_CONFLICT_H_INCLUDED
#define MAC_PANID_CONFLICT_H_INCLUDED

#if (CONFIG_PANID_CONFLICT_ENABLED == 1)

#include "mac_common.h"

/** @file
 * @defgroup mac_pan_id PAN ID Conflict API
 * @ingroup mac_15_4
 * @{
 * @brief Module for handling PAN ID conflicts.
 */

/**
 * @brief A callback function used to notify Pan ID conflict detection algorithm about
 *  a new beacon frame.
 *
 * @param p_beacon - pointer to beacon descriptor struct.
 */
void mac_panid_conflict_beacon_notify_ind(const mac_beacon_ind_t * p_beacon);

#if (CONFIG_PANID_CONFLICT_RESOLUTION_ENABLED == 1)
/**@brief   Callback function which handles end of Pan ID conflict cmd TX,
 *           called by FP
 * @param[in]   status  Confirmation status to be raised
 */
void mac_panid_conflict_cb(mac_status_t status);
#endif

/**@brief Indicates whether the pan id conflict was detected
 *
 * @return Result of pan id conflict detection
 */
bool mac_panid_conflict_detected(void);

/** @} */

#endif

#endif /* MAC_PANID_CONFLICT_H_INCLUDED */
