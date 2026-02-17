/**
 ****************************************************************************************
 *
 * @file ke_timer.h
 *
 * @brief This file contains the definitions used for timer management
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef _KE_TIMER_H_
#define _KE_TIMER_H_

/**
 ****************************************************************************************
 * @defgroup TIMER BT Time
 * @ingroup KERNEL
 * @brief Timer management module.
 *
 * This module implements the functions used for managing kernel timers.
 *
 ****************************************************************************************
 */

#include "rwip_config.h"          // stack configuration
#include "ke_msg.h"               // messaging definition


/*
 * DEFINITIONS
 ****************************************************************************************
 */

///  Convert timer from second to timer accuracy (10ms)
#define KE_TIME_IN_SEC(_time) (_time * 100)


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Timer Object
struct ke_timer
{
    /// next ke timer
    struct ke_timer *next;
    /// message identifier
    ke_msg_id_t     id;
    /// task identifier
    ke_task_id_t    task;
    /// time value
    uint32_t        time;
};


/*
 * FUNCTION PROTOTYPES
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Initialize Kernel timer module.
 ****************************************************************************************
 */
void ke_timer_init(void);

/**
 ****************************************************************************************
 * @brief Set a timer.
 *
 * The function first cancel the timer if it is already existing, then
 * it creates a new one. The timer can be one-shot or periodic, i.e. it
 * will be automatically set again after each trigger.
 *
 * When the timer expires, a message is sent to the task provided as
 * argument, with the timer id as message id.
 *
 * The timer is programmed in time units (TU is 10ms).
 *
 * @param[in] timer_id      Timer identifier (message identifier type).
 * @param[in] task_id       Task identifier which will be notified
 * @param[in] delay         Delay in time units.
 ****************************************************************************************
 */
void ke_timer_set(ke_msg_id_t const timer_id, ke_task_id_t const task, uint32_t delay);

/**
 ****************************************************************************************
 * @brief Remove an registered timer.
 *
 * This function search for the timer identified by its id and its task id.
 * If found it is stopped and freed, otherwise an error message is returned.
 *
 * @param[in] timer_id  Timer identifier.
 * @param[in] task      Task identifier.
 ****************************************************************************************
 */
void ke_timer_clear(ke_msg_id_t const timerid, ke_task_id_t const task);

/**
 ****************************************************************************************
 * @brief Checks if a requested timer is active.
 *
 * This function pops the first timer from the timer queue and notifies the appropriate
 * task by sending a kernel message. If the timer is periodic, it is set again;
 * if it is one-shot, the timer is freed. The function checks also the next timers
 * and process them if they have expired or are about to expire.
 ****************************************************************************************
 */
bool ke_timer_active(ke_msg_id_t const timer_id, ke_task_id_t const task_id);

/**
 ****************************************************************************************
 * @brief Adjust all kernel timers by specified adjustment delay.
 *
 * This function updates all timers to align to a new SCLK after a system clock adjust.
 ****************************************************************************************
 */
void ke_timer_adjust_all(uint32_t delay);


#if (DEEP_SLEEP)

/**
 ****************************************************************************************
 * @brief Get the first timer target (in Slot) used for deep sleep decision
 *
 * @return Invalid time if nothing programmed; target time else.
 ****************************************************************************************
 */
uint32_t ke_timer_target_get(void);

#endif //DEEP_SLEEP
void ke_timer_clear(ke_msg_id_t const timer_id, ke_task_id_t const task_id);
/// @} TIMER

#endif // _KE_TIMER_H_
