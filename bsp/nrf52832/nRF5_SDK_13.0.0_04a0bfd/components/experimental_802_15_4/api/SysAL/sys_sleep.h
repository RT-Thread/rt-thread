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
#ifndef SYS_SLEEP_H_INCLUDED
#define SYS_SLEEP_H_INCLUDED

#include <stdint.h>
#include "sys_events.h"
#include "hal_sleep.h"


/** @file
 *
 * @defgroup sys_sleep Falling Asleep API
 * @ingroup sys_15_4
 * @{
 * @brief Module for declaring the Falling Asleep API.
 * @details Because additional preparation may be required to be done by user modules,
 * prior to putting hardware into the sleep mode, a notification and approval mechanism
 * is provided to the user.
 * Each module that wants to be notified about the "falling asleep" event, has to subscribe
 * to the HAL_EVENT_FALLING_ASLEEP event, using sys_sleep_approver_register(), and to
 * get the unique approver's ID value.
 * In the handler of the HAL_EVENT_FALLING_ASLEEP event, the module is able to perform
 * the required preparation before falling asleep, and to approve the falling asleep request,
 * using the module unique approver ID, after all preparation to sleep is finished.
 * The hardware will fall asleep only after all the registered approvers
 * approve the fall asleep request.
 */

/**@brief   Approver ID typedef.
 */
typedef uint8_t sys_sleep_approver_id_t;


/*  Sanity check for CONFIG_MAX_SLEEP_APPROVERS
 */
#if (!defined(CONFIG_MAX_SLEEP_APPROVERS))
#   error "CONFIG_MAX_SLEEP_APPROVERS must be defined in config file"  
#elif (CONFIG_MAX_SLEEP_APPROVERS >= 256)
#   error "CONFIG_MAX_SLEEP_APPROVERS must be less than 256"
#endif


/**@brief   Function for initializing the system sleep module.
 *
 * @details This function must be called before any usage of the System Sleep module.
 */
void sys_sleep_init(void);


/**@brief   Function for registering the approver of the system sleep request.
 *
 * @details After the sleep approver is registered with this function, the hardware will
 *          not fall asleep without its approval. 
 *
 * @param[in]   p_event_falling_asleep  Event descriptor, which will handle
 *                                      the SYS_EVENT_FALLING_ASLEEP event.
 * @param[in]   p_event_wake_up         Event descriptor, which will handle
 *                                      the SYS_EVENT_WAKE_UP event.
 *
 * @retval  The unique approver ID, reserved for this newly-registered approver.
 *          This ID will be required to approve system sleep requests by this approver module.
 */
sys_sleep_approver_id_t sys_sleep_approver_register(
            sys_event_desc_t * p_event_falling_asleep,
            sys_event_desc_t * p_event_wake_up);


/**@brief   Function for unregistering the approver of the system sleep request.
 *
 * @details After the approver is unregistered, its approval will not be
 *          required to put the system into sleep mode.
 *
 * @param[in]   approver_id             The unique approver ID to be unregistered.
 * @param[in]   p_event_falling_asleep  Event descriptor to unsubscribe from
 *                                      the SYS_EVENT_FALLING_ASLEEP event.
 * @param[in]   p_event_wake_up         Event descriptor to unsubscribe from
 *                                      the SYS_EVENT_WAKE_UP event.
 */
void sys_sleep_approver_unregister(
            sys_sleep_approver_id_t   approver_id,
            sys_event_desc_t        * p_event_falling_asleep,
            sys_event_desc_t        * p_event_wake_up);


/**@brief   Function for approving the system sleep request.
 *
 * @details This function is to be called by the registered approver
 *          in order to approve putting the system into the sleep mode.
 *
 * @param[in]   approver_id    The unique approver ID.
 */
void sys_sleep_approve(sys_sleep_approver_id_t approver_id);


/**@brief   Function for requesting the system to safely enter into sleep mode.
 *
 * @details This function notifies all the registered sleep approvers with the 
 *          HAL_EVENT_FALLING_ASLEEP event, allowing them to perform all the needed preparation
 *          before the hardware falls asleep. The hardware will enter sleep mode only after
 *          all registered approvers approve the fall asleep request.
 *
 * @param[in]   sleep_time_ms    Defines sleep time in ms.
 */
void sys_sleep_request_ms(uint32_t sleep_time_ms);


/**@brief   Function for getting information about the wakeup reason.
 *
 * @retval  hal_wakeup_reason  Interrupt source which was the wakeup reason.
 */
hal_wakeup_reason_t sys_sleep_wakeup_reason(void);

/** @} */

#endif // SYS_SLEEP_H_INCLUDED
