/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_OS_ABSTRACTION_MQX_H__)
#define __FSL_OS_ABSTRACTION_MQX_H__


#if defined ( __IAR_SYSTEMS_ICC__ )
/**
 * Workaround to disable MISRA C message suppress warnings for IAR compiler.
 * Will be removed when MQX RTOS gets MISRA C compliant.
 * http://supp.iar.com/Support/?note=24725
 */
#define MISRAC_DISABLE _Pragma ("diag_suppress=                       \
    Pm001,Pm002,Pm003,Pm004,Pm005,Pm006,Pm007,Pm008,Pm009,Pm010,Pm011,\
    Pm012,Pm013,Pm014,Pm015,Pm016,Pm017,Pm018,Pm019,Pm020,Pm021,Pm022,\
    Pm023,Pm024,Pm025,Pm026,Pm027,Pm028,Pm029,Pm030,Pm031,Pm032,Pm033,\
    Pm034,Pm035,Pm036,Pm037,Pm038,Pm039,Pm040,Pm041,Pm042,Pm043,Pm044,\
    Pm045,Pm046,Pm047,Pm048,Pm049,Pm050,Pm051,Pm052,Pm053,Pm054,Pm055,\
    Pm056,Pm057,Pm058,Pm059,Pm060,Pm061,Pm062,Pm063,Pm064,Pm065,Pm066,\
    Pm067,Pm068,Pm069,Pm070,Pm071,Pm072,Pm073,Pm074,Pm075,Pm076,Pm077,\
    Pm078,Pm079,Pm080,Pm081,Pm082,Pm083,Pm084,Pm085,Pm086,Pm087,Pm088,\
    Pm089,Pm090,Pm091,Pm092,Pm093,Pm094,Pm095,Pm096,Pm097,Pm098,Pm099,\
    Pm100,Pm101,Pm102,Pm103,Pm104,Pm105,Pm106,Pm107,Pm108,Pm109,Pm110,\
    Pm111,Pm112,Pm113,Pm114,Pm115,Pm116,Pm117,Pm118,Pm119,Pm120,Pm121,\
    Pm122,Pm123,Pm124,Pm125,Pm126,Pm127,Pm128,Pm129,Pm130,Pm131,Pm132,\
    Pm133,Pm134,Pm135,Pm136,Pm137,Pm138,Pm139,Pm140,Pm141,Pm142,Pm143,\
    Pm144,Pm145,Pm146,Pm147,Pm148,Pm149,Pm150,Pm151,Pm152,Pm153,Pm154,\
    Pm155")

#define MISRAC_ENABLE _Pragma ("diag_default=                         \
    Pm001,Pm002,Pm003,Pm004,Pm005,Pm006,Pm007,Pm008,Pm009,Pm010,Pm011,\
    Pm012,Pm013,Pm014,Pm015,Pm016,Pm017,Pm018,Pm019,Pm020,Pm021,Pm022,\
    Pm023,Pm024,Pm025,Pm026,Pm027,Pm028,Pm029,Pm030,Pm031,Pm032,Pm033,\
    Pm034,Pm035,Pm036,Pm037,Pm038,Pm039,Pm040,Pm041,Pm042,Pm043,Pm044,\
    Pm045,Pm046,Pm047,Pm048,Pm049,Pm050,Pm051,Pm052,Pm053,Pm054,Pm055,\
    Pm056,Pm057,Pm058,Pm059,Pm060,Pm061,Pm062,Pm063,Pm064,Pm065,Pm066,\
    Pm067,Pm068,Pm069,Pm070,Pm071,Pm072,Pm073,Pm074,Pm075,Pm076,Pm077,\
    Pm078,Pm079,Pm080,Pm081,Pm082,Pm083,Pm084,Pm085,Pm086,Pm087,Pm088,\
    Pm089,Pm090,Pm091,Pm092,Pm093,Pm094,Pm095,Pm096,Pm097,Pm098,Pm099,\
    Pm100,Pm101,Pm102,Pm103,Pm104,Pm105,Pm106,Pm107,Pm108,Pm109,Pm110,\
    Pm111,Pm112,Pm113,Pm114,Pm115,Pm116,Pm117,Pm118,Pm119,Pm120,Pm121,\
    Pm122,Pm123,Pm124,Pm125,Pm126,Pm127,Pm128,Pm129,Pm130,Pm131,Pm132,\
    Pm133,Pm134,Pm135,Pm136,Pm137,Pm138,Pm139,Pm140,Pm141,Pm142,Pm143,\
    Pm144,Pm145,Pm146,Pm147,Pm148,Pm149,Pm150,Pm151,Pm152,Pm153,Pm154,\
    Pm155")
#else
/* Empty MISRA C macros for other toolchains. */
#define MISRAC_DISABLE
#define MISRAC_ENABLE
#endif


#include <stdint.h>
/* Include MQX RTOS API */
MISRAC_DISABLE
#include "mqx_cnfg.h"
#include "mqx.h"
#include "psp.h"
#include "lwevent.h"
#include "lwsem.h"
#include "lwmsgq.h"
#include "task.h"
MISRAC_ENABLE

/*!
* @addtogroup os_abstraction_mqx
* @{
*/


/*******************************************************************************
 * Declarations
 ******************************************************************************/

/*! @brief Type for MQX RTOS mutex. */

/*! @brief Type for a semaphore. */
typedef LWSEM_STRUCT semaphore_t;

/*! @brief Type for a mutex. */
typedef struct mutex_mqx
{
    LWSEM_STRUCT sema;  /*!< The lwsem structure.       */
    _task_id owner;     /*!< Task who locks this mutex. */
} mutex_t;

/*! @brief Type for an event group object. */
typedef LWEVENT_STRUCT event_t;

/*! @brief Type for an event flags group, bit 32 is reserved. */
typedef _mqx_uint event_flags_t;

/*! @brief Type for a task pointer. */
typedef TASK_FPTR task_t;

/*! @brief Type for a task handler, returned by the OSA_TaskCreate function. */
typedef _task_id task_handler_t;

/*! @brief Type for a task handler, returned by the task_create function. */
typedef uint32_t task_param_t;

/*! @brief Type for a task stack. */
typedef uint32_t task_stack_t;

/*! @brief Type for a message queue. */
typedef _mqx_max_type msg_queue_t;

/*! @brief Type for a message queue handler. */
typedef void *msg_queue_handler_t;

/*! @brief Constant to pass as timeout value in order to wait indefinitely. */
#define OSA_WAIT_FOREVER 0xFFFFFFFFU

/*! @brief OSA's time range in millisecond, OSA time wraps if exceeds this value. */
#define FSL_OSA_TIME_RANGE 0xFFFFFFFFU

/*! @brief The default interrupt handler installed in vector table. */
#define OSA_DEFAULT_INT_HANDLER  (OSA_DefaultIntHandler())

/*! @brief The default interrupt handler installed in vector table.
 * @return Default ISR.
*/
static inline osa_int_handler_t OSA_DefaultIntHandler(void)
{
#if defined ( __IAR_SYSTEMS_ICC__ )
_Pragma ("diag_suppress = Pm138")
#endif
    return (osa_int_handler_t)_int_default_isr;
#if defined ( __IAR_SYSTEMS_ICC__ )
_Pragma ("diag_remark = PM138")
#endif
}

/*! @brief The priority of MQX RTOS Main_Task. */
/*
 * OSA provides priority 0~15, these priorities are converted to MQX RTOS priority
 * by adding 7. MQX RTOS Main_Task should have the lowest priority(except idle),
 * so that other tasks could be created dynamically.
 */
#define MQX_MAIN_TASK_PRIORITY (7+16)

/*!
* @name Thread management
* @{
*/

/*!
 * @brief Defines a task.
 *
 * This macro defines resources for a task statically. Then, the OSA_TaskCreate
 * creates the task based-on these resources.
 *
 * @param task The task function.
 * @param stackSize The stack size this task needs in bytes.
 */
#define OSA_TASK_DEFINE(task, stackSize) \
    task_stack_t task##_stack[MQX_REQUIRED_STACK_SIZE(stackSize)/sizeof(task_stack_t)+1]; \
    task_handler_t task##_task_handler;

/*!
 * @brief To provide unified task priority for upper layer, OSA layer makes a conversion.
 * MQX RTOS highest 7 priorities are special priorities.
 */
#define PRIORITY_OSA_TO_RTOS(osa_prio)   ((osa_prio)+7U)
#define PRIORITY_RTOS_TO_OSA(rtos_prio)  ((rtos_prio)-7U)
/* @} */

/*!
* @name Message queues
* @{
*/

/* Internal macro that computes the number of _mqx_max_type elements needed to cover size bytes. */
#define SIZE_IN_MMT_UNITS(size) ((size + sizeof(_mqx_max_type) - 1) / sizeof(_mqx_max_type))

/*!
 * @brief This macro statically reserves the memory required for the queue.
 *
 * @param name Identifier for the memory region.
 * @param number Number of elements in the queue.
 * @param size Size of element in 4 B units.
 */

#define MSG_QUEUE_DECLARE(name, number, size) \
    _mqx_max_type name[SIZE_IN_MMT_UNITS(sizeof(LWMSGQ_STRUCT)) + SIZE_IN_MMT_UNITS(size * 4) * number]

/*@}*/


/*! @}*/

#endif /* __FSL_OS_ABSTRACTION_MQX_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

