/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef ES_ADV_H__
#define ES_ADV_H__

#include "nrf_ble_escs.h"

/**
 * @file
 * @defgroup eddystone_adv Eddystone advertising module
 * @brief Types and functions for handling advertising in Eddystone beacons.
 * @ingroup eddystone
 * @{
 */

/** @brief Eddystone Advertiser events. */
typedef enum
{
    ES_ADV_EVT_NON_CONN_ADV,
    ES_ADV_EVT_CONNECTABLE_ADV_STARTED,
} es_adv_evt_t;

/** @brief Eddystone Advertiser event handler. */
typedef void (*es_adv_evt_handler_t)(es_adv_evt_t evt);

/** @brief Function for initializing the module.
 *
 * @param[in] ecs_uuid_type         ECS UUID type used for advertising the Eddystone Configuration Service UUID.
 * @param[in] adv_event_handler     Eddystone advertiser event handler.
 * @param[in] adv_interval          Advertisement interval to use.
 * @param[in] remain_connectable    Flag that specifies if advertisements should remain connectable.
 */
void es_adv_init(uint8_t                     ecs_uuid_type,
                 es_adv_evt_handler_t        adv_event_handler,
                 nrf_ble_escs_adv_interval_t adv_interval,
                 bool                        remain_connectable);

/** @brief Function for passing BLE events to this module.
 *
 * @param[in] p_ble_evt     Pointer to the BLE evt.
 */
void es_adv_on_ble_evt(ble_evt_t * p_ble_evt);

/** @brief Function for starting the advertisements.
 */
void es_adv_start_non_connctable_adv(void);

/** @brief Function for specifying if the beacon should remain connectable.
 *
 * @param[in] remain_connectable     Value to be set.
 */
void es_adv_remain_connectable_set(bool remain_connectable);

/** @brief Function for starting connectable advertisements.
 */
void es_adv_start_connectable_adv(void);

/** @brief Function for setting the base advertisement interval for non-connectable advertisements.
 *
 * The minimum allowed advertisement interval is calculated based on the configured minimum advertisement
 * frame spacings and the number of configured slots. If eTLM slots are configured a separate minimum
 * advertisement frame spacing is used for those. If @p interval is outside of range, the closest valid value
 * is set.
 *
 * @param interval The new advertisement interval.
 */
void es_adv_interval_set(nrf_ble_escs_adv_interval_t interval);

/** @brief Function for getting a pointer to the current advertisement interval.
 *
 * @retval Pointer to the current advertisement interval.
 */
nrf_ble_escs_adv_interval_t es_adv_interval_get(void);

/** @brief Function for getting the value of the 'remain_connectable' field.
 *
 * @retval Value of 'remain_connectable'.
 */
bool es_adv_remain_connectable_get(void);

/** @brief Function for initializing the Eddystone advertisement timers. 
 */
void es_adv_timers_init(void);

/**
 * @}
 */

#endif // ES_ADV_H__
