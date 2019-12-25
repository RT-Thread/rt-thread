/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
#ifndef BLE_ANCS_ATTR_PARSER_H__
#define BLE_ANCS_ATTR_PARSER_H__

#include "nrf_ble_ancs_c.h"

/** @file
 *
 * @addtogroup ble_ancs_c
 * @{
 */

/**@brief Function for parsing notification or app attribute response data.
 *
 * @details The data that comes from the Notification Provider can be much longer than what
 *          would fit in a single GATTC notification. Therefore, this function relies on a
 *          state-oriented switch case.
 *          UID and command ID will be received only once at the beginning of the first
 *          GATTC notification of a new attribute request for a given iOS notification.
 *          After this, we can loop several ATTR_ID > LENGTH > DATA > ATTR_ID > LENGTH > DATA until
 *          we have received all attributes we wanted as a Notification Consumer.
 *          The Notification Provider can also simply stop sending attributes.
 *
 * 1 byte  |  4 bytes    |1 byte |2 bytes |... X bytes ... |1 bytes| 2 bytes| ... X bytes ...
 * --------|-------------|-------|--------|----------------|-------|--------|----------------
 * CMD_ID  |  NOTIF_UID  |ATTR_ID| LENGTH |    DATA        |ATTR_ID| LENGTH |    DATA
 *
 * @param[in] p_ancs       Pointer to an ANCS instance to which the event belongs.
 * @param[in] p_data_src   Pointer to data that was received from the Notification Provider.
 * @param[in] hvx_data_len Length of the data that was received from the Notification Provider.
 */
void ancs_parse_get_attrs_response(ble_ancs_c_t  * p_ancs,
                                   const uint8_t * p_data_src,
                                   const uint16_t  hvx_data_len);

/** @} */

#endif // BLE_ANCS_ATTR_PARSER_H__

