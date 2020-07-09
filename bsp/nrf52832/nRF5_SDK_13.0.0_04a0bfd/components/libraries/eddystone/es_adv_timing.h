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
#ifndef ES_ADV_TIMING_H__
#define ES_ADV_TIMING_H__

#include <stdint.h>

/**
 * @file
 * @defgroup eddystone_adv_timing Timing
 * @brief Events and functions for advertisement timing.
 * @ingroup eddystone_adv
 * @{
 */

/**@brief Eddystone advertisement timing event types. */
typedef enum
{
    ES_ADV_TIMING_EVT_ADV_SLOT, //!< Advertising non-eTLM slot.
    ES_ADV_TIMING_EVT_ADV_ETLM  //!< Advertising eTLM slot.
} es_adv_timing_evt_id_t;

/**@brief Eddystone advertisement timing event. */
typedef struct
{
    es_adv_timing_evt_id_t evt_id;  //!< Event type ID.
    uint8_t                slot_no; /**< @brief Slot number.
                                     * @details For non-eTLM events: The slot number to advertise.
                                     *
                                     * For eTLM events: The slot number of the corresponding EID slot. */
} es_adv_timing_evt_t;

/**@brief Eddystone advertisement timing event callback.
 *
 * @param[in]   p_evt       Pointer to the Eddystone advertisement timing event.
 */
typedef void (*es_adv_timing_callback_t)(const es_adv_timing_evt_t * p_evt);

/**@brief Function for starting Eddystone advertisement timing event generation. */
void es_adv_timing_start(uint16_t adv_interval);


/**@brief Function for stopping Eddystone advertisement timing event generation. */
void es_adv_timing_stop(void);

/**@brief Function for initializing the Eddystone advertisement timers. 
 */
void es_adv_timing_timers_init(void);

/**@brief Function for initializing the Eddystone advertisement timing module.
 *
 * @param[in]   handler     Eddystone advertisement timing event handler to register.
 */
void es_adv_timing_init(es_adv_timing_callback_t handler);

/**
 * @}
 */

#endif // ES_ADV_TIMING_H__
