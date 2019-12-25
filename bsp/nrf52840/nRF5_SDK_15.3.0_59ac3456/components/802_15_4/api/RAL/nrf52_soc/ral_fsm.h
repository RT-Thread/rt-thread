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
#ifndef RAL_FSM_H_INCLUDED
#define RAL_FSM_H_INCLUDED

#include "sys_fsm.h"

/**
 * @defgroup ral_api_fsm RAL FSM API
 * @ingroup ral_api
 * @{
 */

// list of possible events
typedef enum
{
    E_RESET,
    E_TRX_END,      /**< Radio signals that TX or RX is complete.*/
    E_TX_REQ,       /**< Initiates upload of a frame into radio memory and
                         transmission of it into air.*/
    E_TRX_OFF,
    E_TX_ON,
    E_FORCE_TX_ON,
    E_RX_ON,
} ral_fsm_events_t;

// states
typedef enum
{
/* State symbol for short FSM debug mode */
/* I */    S_TRX_OFF,
/* J */    S_TX_ON,
/*   */    S_BUSY_TX,
/* G */    S_RX_ON,
/* B */    S_BUSY_RX,
} ral_fsm_states_t;

/**@brief  Reads current state of RAL state machine.
 *
 * @return Current state.
 */
ral_fsm_states_t ral_fsm_current_state_get(void);

/**@brief  Initializes finite state machine of radio chip.*/
void ral_fsm_init(void);

/**@brief  Sends new event to radio FSM. This function is used for
 * changing radio state.
 *
 * @param event - event id for FSM.
 * @param p_data - pointer to event specific data (expects pointer to ral_mem_t).
 */
void ral_fsm_event_post(ral_fsm_events_t event, void * p_data);

/** @} */

#endif /* RAL_FSM_H_INCLUDED */
