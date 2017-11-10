/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#ifndef __ANT_STATE_INDICATOR_H
#define __ANT_STATE_INDICATOR_H

/** @file
 *
 * @defgroup ant_state_indicator ANT channel state indicator
 * @{
 * @ingroup ant_sdk_utils
 * @brief ANT channel state indicator module.
 *
 * @details This module provides functionality for indicating the ANT channel state.
 */

#include <stdint.h>
#include "ant_stack_handler_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Function for initializing the ANT channel state indicator.
 *
 * @details This function links the signaling procedure with a specific ANT channel.
 *
 * Before calling this function, you must initiate the @ref lib_bsp to be able to use the LEDs.
 *
 * @param[in] channel       ANT channel number.
 * @param[in] channel_type  ANT channel type (see Assign Channel Parameters in ant_parameters.h: @ref ant_parameters).
 */
void ant_state_indicator_init( uint8_t channel, uint8_t channel_type);


/**
 * @brief Function for handling ANT events.
 *
 * @details This function handles all events from the ANT stack that are of interest to the channel state indicator.
 *          This function should always be called when an ANT event occurs.
 *
 * @param[in]   p_ant_evt       Event received from the ANT stack.
 */
void ant_state_indicator_evt_handler(ant_evt_t * p_ant_evt);


/**
 * @brief Function for indicating the channel opening.
 *
 * @details This function should be called after the opening of the channel.
 *
 * @retval      NRF_SUCCESS               If the state was successfully indicated.
 * @retval      NRF_ERROR_NO_MEM          If the internal timer operations queue was full.
 * @retval      NRF_ERROR_INVALID_STATE   If the application timer module has not been initialized
 *                                        or the internal timer has not been created.
 */
uint32_t ant_state_indicator_channel_opened(void);


/**@brief Function for putting the chip into sleep mode.
 *
 * @details This function sets up a wakeup button and puts the chip into deep sleep mode.
 *
 * @note This function will not return.
 */
void ant_state_indicator_sleep_mode_enter(void);



#ifdef __cplusplus
}
#endif

#endif
/** @} */
