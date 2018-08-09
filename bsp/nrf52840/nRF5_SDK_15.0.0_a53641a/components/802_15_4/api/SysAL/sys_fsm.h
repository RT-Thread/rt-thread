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
#ifndef SYS_FSM_H_INCLUDED
#define SYS_FSM_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

/** @file
 * This file contains declarations of the Finite State Machine (FSM) primitives and necessary types.
 *
 * @defgroup sys_fsm Finite State Machine API
 * @ingroup sys_15_4
 * @{
 * @brief Module to declare Finite State Machine API
 * @details The FSM module implements the Finite State Machine abstraction. The user is intended to implement a transition
 * table of states with guards and actions in order to represent some event-driven subject. When a table is
 * implemented, call sys_fsm_init() to initialize the FSM. After that, the only routine to
 * work with FSM is sys_fsm_event_post().
 */

/**@brief   Fixed-size type for FSM state ID.
 */
typedef uint8_t sys_fsm_state_id_t;


/**@brief   Fixed-size type for FSM event ID.
 */
typedef uint8_t sys_fsm_event_id_t;


/**@brief   Fixed-size type for FSM guard condition ID.
 */
typedef uint8_t sys_fsm_guard_id_t;


/**@brief   Fixed-size type for FSM action ID.
 */
typedef uint8_t sys_fsm_action_id_t;


/**@brief   FSM transition description (item of FSM transition table).
 *
 * @details When an event with given event_id occurs, the guard condition with guard_id
 *          is checked, and if it returns true, the action with action_id is performed,
 *          and state machine is switched to the state with new_state_id.
 */
typedef struct
{
    sys_fsm_event_id_t	event_id;        /**< FSM event ID. */
    sys_fsm_guard_id_t	guard_id;        /**< FSM guard ID. */
    sys_fsm_action_id_t	action_id;       /**< FSM action ID. */
    sys_fsm_state_id_t	new_state_id;    /**< New state ID. */
#if defined(CONFIG_FSM_DEBUG)
    const char * debug_string;
#endif
} sys_fsm_transition_t;


/**@brief   FSM transition declaration (item of FSM transition table).
 */
#if defined(CONFIG_FSM_DEBUG)
#   define SYS_FSM_TRANSITION(event_id, guard_id, action_id, new_state_id)	\
		{(event_id), (guard_id), (action_id), (new_state_id),   \
            "(" #event_id ", " #guard_id ", " #action_id " -> " #new_state_id ")"}
#else
#   define SYS_FSM_TRANSITION(event_id, guard_id, action_id, new_state_id)	\
		{(event_id), (guard_id), (action_id), (new_state_id)}
#endif


/**@brief    FSM state declaration.
 *
 * @details  The state is an aggregator item of the FSM transition table, aggregating
 *           the transitions, declared immediately after this state declaration.
 *           All transition declaration items, following the state declaration item,
 *           will be aggregated in this state, until the next state declaration item,
 *           or the "end of table" item.
 */
#define SYS_FSM_STATE(state_id)    \
            {(state_id) | SYS_FSM_STATE_FLAG, 0, 0, 0}


/**@brief   Empty guard condition ID.
 *
 * @details Special value of the guard_id field. If it is used in transition declaration,
 *          guard check will be omitted.
 */
#define SYS_FSM_NO_GUARD        0xFF


/**@brief   Empty guard condition ID (useful synonym).
 *
 * @details Special value of the guard_id field. If it is used in transition declaration,
 *          guard check will be omitted.
 */
#define SYS_FSM_OTHERWISE       0xFF


/**@brief   Empty guard condition ID (useful synonym).
 *
 * @details Special value of the guard_id field. If it is used in transition declaration,
 *          guard check will be omitted.
 */
#define SYS_FSM_ALWAYS          0xFF


/**@brief   Empty action ID.
 *
 * @details Special value of the action_id field. If it is used in transition declaration,
 *          no action will be performed during the transition.
 */
#define SYS_FSM_NO_ACTION       0xFF


/**@brief   Same state ID.
 *
 * @details Special value of the next_state_id field. If it is used in transition
 *          declaration, the current state will not be changed.
 */
#define SYS_FSM_SAME_STATE      0xFF


/**@brief   Any state ID.
 *
 * @details Special value of the event_id field. If it is used in transition
 *          declaration table, then the transitions listed in this state will be applied
 *          in case they have not been listed in the transition table for the 
 *          current FSM state.
 *          Only one SYS_FSM_STATE(SYS_FSM_ANY_STATE) can be present in the transition table.
 */
#define SYS_FSM_ANY_STATE      0xFF


/**@brief   State declaration flag.
 *
 * @details Special flag of the event_id field. This flag is used to distinguish
 *          between state declaration and transition declaration.
 */
#define SYS_FSM_STATE_FLAG      0x80
   

/**@brief   Prototype of a user-defined FSM guard condition function.
 *
 * @details     You must implement a single FSM guard condition function which will
 *              use an ID of the needed guard check as a parameter.
 *
 * @param[in]   guard_id    Guard condition ID to be checked.
 * @param[in]   p_data      Additional FSM specific data.
 *
 * @retval  true    Transition is allowed, false otherwise.
 */
typedef bool (* sys_fsm_guard_t)(sys_fsm_guard_id_t guard_id, void * p_data);


/**@brief Prototype of a user-defined FSM action function.
 *
 * @details     You must implement a single FSM action function which will
 *              use an ID of the needed action as a parameter.
 *
 * @param[in]   action_id   Action ID to be performed.
 * @param[in]   p_data      Additional FSM specific data.
 */
typedef void (* sys_fsm_action_t)(sys_fsm_action_id_t action_id, void * p_data);


/**@brief   Constant FSM descriptor which can reside in read-only memory.
 */
typedef struct
{
#if defined(CONFIG_FSM_DEBUG)
    const char * debug_fsm_name;
#endif
    /** Pointer to the transition table.
     */
    const sys_fsm_transition_t *  transition_table;

    /** Number of transitions in the transition table.
     */
    uint8_t                       transitions_amount;
    
    /** Initial state ID.
     */
    sys_fsm_state_id_t            initial_state;

    /** Pointer to the guard condition function.
     */
    sys_fsm_guard_t               guard;

    /** Pointer to the action function.
     */
    sys_fsm_action_t              action;
} sys_fsm_const_descriptor_t;


/**@brief   FSM dynamic descriptor, holding the current state of the FSM.
*/
typedef struct 
{
    /** Pointer to the constant FSM descriptor which can reside in read-only memory.
     */
    const sys_fsm_const_descriptor_t * fsm_const_desc;

    /** Index of the "any state transitions" block.
     */
    uint8_t                            any_state_transitions_index;

    /** Current state ID.
     */
    volatile sys_fsm_state_id_t        current_state;

    /** Recursion protection.
     */
    volatile uint8_t                   recursion_protection;
} sys_fsm_t;


#if defined(CONFIG_FSM_DEBUG)
    #define FSM_DEBUG_NAME(name_string)    .debug_fsm_name = name_string,
#else
    #define FSM_DEBUG_NAME(name_string)
#endif


/**@brief   Function for initializing a specific FSM.
 *
 * @param[in]   p_fsm       Pointer to FSM descriptor to initialize.
 * @param[in]   p_fsm_const Pointer to constant FSM descriptor with transition table, etc.
 */
void sys_fsm_init(sys_fsm_t * p_fsm, const sys_fsm_const_descriptor_t * p_fsm_const);


/**@brief   Function for posting an event to FSM.
 *
 * @details This function causes FSM transition from the current state to the new state,
 *          according to the transition table of this FSM. 
 *          The corresponding guard check and action is performed.
 *
 * @param[in]   p_fsm       Pointer to FSM descriptor.
 * @param[in]   event_id    Event ID to post.
 * @param[in]   p_data      Pointer to the FSM-specific data.
 */
void sys_fsm_event_post(sys_fsm_t * p_fsm, sys_fsm_event_id_t event_id, void * p_data);

/** @} */

#endif // SYS_FSM_H_INCLUDED
