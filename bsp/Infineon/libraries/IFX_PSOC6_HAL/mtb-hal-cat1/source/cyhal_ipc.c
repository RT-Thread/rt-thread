/***************************************************************************//**
* \file cyhal_ipc.c
*
* \brief
* Provides a high level interface for interacting with the Infineon Inter Processor Communication.
* This interface abstracts out the chip specific details. If any chip specific
* functionality is necessary, or performance is critical the low level functions
* can be used directly.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_ipc_drv.h"
#include "cy_ipc_pipe.h"
#include "cy_ipc_sema.h"
#include "cyhal_ipc.h"
#include "cyhal_ipc_impl.h"
#include "cyhal_system.h"
#include "cyhal_irq_impl.h"
#if (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0)
#include "cyabs_rtos.h"
#endif /* (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0) */

#include <string.h>

#if (CYHAL_DRIVER_AVAILABLE_IPC)

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_hal_impl_ipc IPC (Inter-Processor Communication)
* \ingroup group_hal_impl
* \{
* \section section_hal_impl_ipc_preemtable_sema Preemtable Semaphore parameter
* If preemptable parameter is enabled (true) for semaphore, the user must ensure that there are no deadlocks in the
* system, which can be caused by an interrupt that occurs after the IPC channel is locked. Unless the user is ready to
* handle IPC channel locks correctly at the application level, set preemptable to false.
*
* \section section_hal_impl_ipc_interrupts_priorities IPC interrupts implementation and priorities
* In current HAL IPC implementation, each core has its "own" IPC INTR structure, which services all possible HAL IPC
* channels. Due to that, callbacks (interrupts) priorities are not flexible in configuration, which means that
* priority, set by \ref cyhal_ipc_queue_enable_event function, will only be applied, if it is lower,
* than the one, which is currently applied for the source (IPC INTR structure), that services interrupts for current
* core. Priority is being applied core-wide, for all channels and queue numbers.
*
* \section section_hal_impl_ipc_queue_operation_isr IPC queues operations in ISR context
* In current HAL IPC implementation, due to multi-core interrupts synchronization specifics, IPC queue put/get operations
* cannot be performed in callbacks (ISR context). Such operations will end with \ref CYHAL_IPC_RSLT_ERR_CANT_OPERATE_IN_ISR
* error code generation.
*
* \section section_hal_impl_ipc_last_sema_occupied Last available IPC semaphore is occupied by HAL IPC
* Last available IPC semaphore (_CYHAL_IPC_PDL_SEMA_COUNT - 1) is occupied by multi-core interrupt synchronization mechanism
* and is not available for user.
*
* \section section_hal_impl_ipc_semaphores_initialization On some devices (currently, CAT1C and CAT1D devices), startup
* code does not initialize IPC PDL driver semaphores, so it is done by cyhal_ipc_semaphore_init() function, which
* requires one device core call cyhal_ipc_semaphore_init() prior to other cores. By default, for CAT1C, CM7_0 should
* call this function before other cores, while on CAT1D - CM55 core. This can be changed by user by defining
* `CYHAL_IPC_INIT_CORE` with required core name. For example, definition of CYHAL_IPC_INIT_CORE to be equal
* CORE_NAME_CM7_1 will make cyhal_ipc_semaphore_init() on CAT1C device initialize IPC PDL semaphores on CM7_1 core.
* Note: Defines `CORE_NAME_*` are being generated for each device by corresponding recipe-make-* asset.
*
* \} group_hal_impl_ipc
*/

typedef struct
{
    uint8_t *isr_enable_sync;
    uint8_t *isr_clear_sync;
    cyhal_ipc_queue_t *queues_ll_pointer;
} _cyhal_ipc_sevice_data_t;

_cyhal_ipc_sevice_data_t *_cyhal_ipc_service_data = NULL;

/* Step in us between IPC semaphore unsuccessful takes when performing
*  internal IPC service tasks. */
#define _CYHAL_IPC_SERVICE_SEMA_STEP_US         (100)
/* IPC semaphore timeout when performing internal IPC service tasks */
#define _CYHAL_IPC_SERVICE_SEMA_TIMEOUT_US      (2000)
/* IPC semaphore acquire / give  tries */
#define _CYHAL_IPC_SERVICE_SEMA_TRIES           (100)

#if (CYHAL_IPC_USR_CHANNELS <= 8)
    #define _CYHAL_IPC_FIX_CHAN_NUM(channel)                    (channel - CYHAL_IPC_CHAN_0)
    #define _CYHAL_IPC_BIT_ENABLE(variable, channel, core)      variable[core] |= (1 << _CYHAL_IPC_FIX_CHAN_NUM(channel))
    #define _CYHAL_IPC_BIT_DISABLE(variable, channel, core)     variable[core] &= ~(1 << _CYHAL_IPC_FIX_CHAN_NUM(channel))
    #define _CYHAL_IPC_CHECK_BIT(variable, channel, core)       ((variable[core] & (1 << _CYHAL_IPC_FIX_CHAN_NUM(channel))) != 0)
    #define _CYHAL_IPC_CHECK_BIT_NOT(variable, channel, core)   ((variable[core] & (1 << _CYHAL_IPC_FIX_CHAN_NUM(channel))) == 0)

    /* Set ISR Enabled */
    #define _CYHAL_IPC_SIE(channel, core)       _CYHAL_IPC_BIT_ENABLE(_cyhal_ipc_service_data->isr_enable_sync, channel, core)
    /* Set ISR Disabled */
    #define _CYHAL_IPC_SID(channel, core)       _CYHAL_IPC_BIT_DISABLE(_cyhal_ipc_service_data->isr_enable_sync, channel, core)
    /* Is ISR Enabled */
    #define _CYHAL_IPC_IIE(channel, core)       _CYHAL_IPC_CHECK_BIT(_cyhal_ipc_service_data->isr_enable_sync, channel, core)
    /* Set ISR (ISR is expected) */
    #define _CYHAL_IPC_SI(channel, core)        _CYHAL_IPC_BIT_ENABLE(_cyhal_ipc_service_data->isr_clear_sync, channel, core)
    /* Clear ISR (ISR is handled and cleared) */
    #define _CYHAL_IPC_CI(channel, core)        _CYHAL_IPC_BIT_DISABLE(_cyhal_ipc_service_data->isr_clear_sync, channel, core)
    /* Is ISR Serviced */
    #define _CYHAL_IPC_IIS(channel, core)       _CYHAL_IPC_CHECK_BIT_NOT(_cyhal_ipc_service_data->isr_clear_sync, channel, core)
#else
    #error "Unhandled number of IPC channels"
#endif /* CYHAL_IPC_USR_CHANNELS <= 8 or other */

#if defined(COMPONENT_CAT1A)
/* Number of cores being serviced by the driver */
#define _CYHAL_IPC_CORE_NUM                         (2)
#define _CYHAL_IPC_CM0P_IDX                         (0)
#define _CYHAL_IPC_CM4_IDX                          (1)

/* IPC INTR of HAL IPC CHAN 0 is used to service interrupts on CM0p, IPC_CHAN 1 is used for CM4 */
#define _CYHAL_IPC_TRIGGER_ISR_MASK                 ((1UL << CYHAL_IPC_CHAN_0) | (1UL << CYHAL_IPC_CHAN_1))
#if (CY_CPU_CORTEX_M0P)
#define _CYHAL_IPC_CURRENT_CORE_IPC_INTR_CHAN       (CYHAL_IPC_CHAN_0)
#define _CYHAL_IPC_CUR_CORE_IDX                     (_CYHAL_IPC_CM0P_IDX)
#define _CYHAL_IPC_OTHER_CORE_IDX                   (_CYHAL_IPC_CM4_IDX)
#else /* CY_CPU_CORTEX_M4 */
#define _CYHAL_IPC_CURRENT_CORE_IPC_INTR_CHAN       (CYHAL_IPC_CHAN_1)
#define _CYHAL_IPC_CUR_CORE_IDX                     (_CYHAL_IPC_CM4_IDX)
#define _CYHAL_IPC_OTHER_CORE_IDX                   (_CYHAL_IPC_CM0P_IDX)
#endif /* CY_CPU_CORTEX_M0P or CY_CPU_CORTEX_M4 */

#elif defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
/* Number of cores being serviced by the driver */
#define _CYHAL_IPC_CORE_NUM                         (3)

#if defined(COMPONENT_CAT1C)
#define _CYHAL_IPC_CM0P_IDX                         (0)
#define _CYHAL_IPC_CM7_0_IDX                        (1)
#define _CYHAL_IPC_CM7_1_IDX                        (2)

#if (CY_CPU_CORTEX_M0P)
#define _CYHAL_IPC_CURRENT_CORE_IPC_INTR_CHAN       (CYHAL_IPC_CHAN_0)
#define _CYHAL_IPC_CUR_CORE_IDX                     (_CYHAL_IPC_CM0P_IDX)
#define _CYHAL_IPC_OTHER_CORE_0_IDX                 (_CYHAL_IPC_CM7_0_IDX)
#define _CYHAL_IPC_OTHER_CORE_1_IDX                 (_CYHAL_IPC_CM7_1_IDX)
#elif (CY_CPU_CORTEX_M7)
#if (CORE_NAME_CM7_0)
#define _CYHAL_IPC_CURRENT_CORE_IPC_INTR_CHAN       (CYHAL_IPC_CHAN_1)
#define _CYHAL_IPC_CUR_CORE_IDX                     (_CYHAL_IPC_CM7_0_IDX)
#define _CYHAL_IPC_OTHER_CORE_0_IDX                 (_CYHAL_IPC_CM0P_IDX)
#define _CYHAL_IPC_OTHER_CORE_1_IDX                 (_CYHAL_IPC_CM7_1_IDX)
#elif (CORE_NAME_CM7_1)
#define _CYHAL_IPC_CURRENT_CORE_IPC_INTR_CHAN       (CYHAL_IPC_CHAN_2)
#define _CYHAL_IPC_CUR_CORE_IDX                     (_CYHAL_IPC_CM7_1_IDX)
#define _CYHAL_IPC_OTHER_CORE_0_IDX                 (_CYHAL_IPC_CM0P_IDX)
#define _CYHAL_IPC_OTHER_CORE_1_IDX                 (_CYHAL_IPC_CM7_0_IDX)
#else
#error "Unable to determine CM7 core index"
#endif /* defined (ACTIVE_CORE_CM7_0) or defined (ACTIVE_CORE_CM7_0) or error */
#endif /* CY_CPU_CORTEX_M0P or CY_CPU_CORTEX_M7 */
#else
#define _CYHAL_IPC_CM33_IDX                         (0)
#define _CYHAL_IPC_CM55_IDX                         (1)
#define _CYHAL_IPC_CU55_IDX                         (2)
#if (CY_CPU_CORTEX_M33)
#define _CYHAL_IPC_CURRENT_CORE_IPC_INTR_CHAN       (CYHAL_IPC_CHAN_0)
#define _CYHAL_IPC_CUR_CORE_IDX                     (_CYHAL_IPC_CM33_IDX)
#define _CYHAL_IPC_OTHER_CORE_0_IDX                 (_CYHAL_IPC_CM55_IDX)
#define _CYHAL_IPC_OTHER_CORE_1_IDX                 (_CYHAL_IPC_CU55_IDX)
#elif (CY_CPU_CORTEX_M55)
#define _CYHAL_IPC_CURRENT_CORE_IPC_INTR_CHAN       (CYHAL_IPC_CHAN_1)
#define _CYHAL_IPC_CUR_CORE_IDX                     (_CYHAL_IPC_CM55_IDX)
#define _CYHAL_IPC_OTHER_CORE_0_IDX                 (_CYHAL_IPC_CM33_IDX)
#define _CYHAL_IPC_OTHER_CORE_1_IDX                 (_CYHAL_IPC_CU55_IDX)
#else
#define _CYHAL_IPC_CURRENT_CORE_IPC_INTR_CHAN       (CYHAL_IPC_CHAN_2)
#define _CYHAL_IPC_CUR_CORE_IDX                     (_CYHAL_IPC_CU55_IDX)
#define _CYHAL_IPC_OTHER_CORE_0_IDX                 (_CYHAL_IPC_CM33_IDX)
#define _CYHAL_IPC_OTHER_CORE_1_IDX                 (_CYHAL_IPC_CM55_IDX)
#endif /* CY_CPU_CORTEX_M33 or CY_CPU_CORTEX_M55 or other */
#endif /* defined(COMPONENT_CAT1C) or other */

#define _CYHAL_IPC_TRIGGER_ISR_MASK                 ((1UL << CYHAL_IPC_CHAN_0) | (1UL << CYHAL_IPC_CHAN_1) | (1UL << CYHAL_IPC_CHAN_2))
#else /* !defined(COMPONENT_CAT1A) */
    #error "Unhandled device"
#endif /* defined(COMPONENT_CAT1A) */

#define _CYHAL_IPC_CURRENT_CORE_IPC_INTR_SRC        ((_cyhal_system_irq_t)(cpuss_interrupts_ipc_0_IRQn + _CYHAL_IPC_CURRENT_CORE_IPC_INTR_CHAN))

/*
*  Macro to work with triggered events and their signatures.
*  Such operations are being performed by IPC queue functions, that can provoke interrupts.
*  Signatures are the bits in corresponding bitfields, that are being inverted each
*  time new event is being generated. They are needed to make IPC irq handler be able
*  to understand whether a certain event was already passed to a user's callback or not. This mechanism works
*  in the following way:
*   - Queue modification function sets the triggered event and swaps the inverse bit
*   - irq handler compares the current signature with that previously passed to the user. If they differ, pass the event to the user. If not, then
*   ignore the event; Store the processed signature.
*
*/

/* How many bits are used to store events / their signatures */
#define _CYHAL_IPC_EVENTS_SIGNATURES_BITS           (16UL)
#define _CYHAL_IPC_EVENTS_MASK                      ((1UL << _CYHAL_IPC_EVENTS_SIGNATURES_BITS) - 1)
#define _CYHAL_IPC_SIGNATURES_MASK                  (_CYHAL_IPC_EVENTS_MASK << _CYHAL_IPC_EVENTS_SIGNATURES_BITS)
/* Add event into triggered events list and change signature */
#define _CYHAL_IPC_ADD_TRIGGERED_EVENT(var, event)  var |= event; var ^= (event << _CYHAL_IPC_EVENTS_SIGNATURES_BITS)
/* Get triggered events w/o signatures */
#define _CYHAL_IPC_GET_TRIGGERED_EVENT(var)         (var & _CYHAL_IPC_EVENTS_MASK)
/* Get signatures w/o triggered events */
#define _CYHAL_IPC_GET_SIGNATURES(var)              (((var) & _CYHAL_IPC_SIGNATURES_MASK) >> _CYHAL_IPC_EVENTS_SIGNATURES_BITS)
/* Remove triggered events (not signatures touched) */
#define _CYHAL_IPC_RMV_TRIGGERED_EVENT(var, event)  var &= ~event
/* Clear triggered events, but not signatures */
#define _CYHAL_IPC_CLR_TRIGGERED_EVENT(var)         var &= _CYHAL_IPC_SIGNATURES_MASK

cyhal_ipc_t *_ipc_objects[CYHAL_IPC_USR_CHANNELS];
bool interrupts_initialized = false;
bool semas_initialized = false;

/* As _ipc_objects stores only info about user-accessible IPC channels, we need to apply offset when accessing the array */
#define _CYHAL_IPC_OBJ_ARR_EL(channel_num)  (_ipc_objects[(channel_num - CYHAL_IPC_CHAN_0)])

#if (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0)
#if defined(CY_IPC_INTR_SPARE)
#define _CYHAL_IPC_SEMA_INTR_STR_NUM                (CY_IPC_INTR_SPARE)
#elif defined(CY_IPC_INTR_USER) && (CY_IPC_INTR_USER < CY_IPC_CHAN_USER)
#define _CYHAL_IPC_SEMA_INTR_STR_NUM                (CY_IPC_INTR_USER)
#else
#error "Cannot determine IPC INTR struct for semaphores"
#endif /* defined(CY_IPC_INTR_SPARE) or defined(CY_IPC_CHAN_USER) or other */

#if (_CYHAL_IPC_SEMA_INTR_STR_NUM >= CYHAL_IPC_CHAN_0)
#error "Cannot proceed with overlapping SEMA and QUEUE interrupts"
#endif /* (CY_IPC_INTR_SPARE >= CYHAL_IPC_CHAN_0) */

typedef struct
{
    cy_semaphore_t semaphore;
    uint32_t sema_num;
    bool initialized;
} _cyhal_ipc_rtos_sema_t;

static _cyhal_ipc_rtos_sema_t _cyhal_ipc_rtos_semaphores[CYHAL_IPC_RTOS_SEMA_NUM] = { 0 };
#endif /* (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0) */

/*************************************** INTERNAL FUNCTIONS PROTOTYPES *************************************************/

static void _cyhal_ipc_irq_handler(void);
static cy_rslt_t _cyhal_ipc_sema_take(cyhal_ipc_t *obj, uint32_t *timeout_us, uint32_t step_us);
static void _cyhal_ipc_wait_step(uint32_t *timeout_us, uint32_t polling_interval_us);

/********************************************* SEMAPHORE HELPERS *******************************************************/

#if (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0)

/* Is any of RTOS semaphores was initialized previously? */
bool _cyhal_ipc_rtos_is_any_sema_initialized()
{
    for (size_t sema_idx = 0; sema_idx < CYHAL_IPC_RTOS_SEMA_NUM; ++sema_idx)
    {
        if (_cyhal_ipc_rtos_semaphores[sema_idx].initialized)
        {
            return true;
        }
    }
    return false;
}

size_t _cyhal_ipc_rtos_get_rtos_sema_index(void *sema_address)
{
    for (size_t sema_idx = 0; sema_idx < CYHAL_IPC_RTOS_SEMA_NUM; ++sema_idx)
    {
        if ((void *)&_cyhal_ipc_rtos_semaphores[sema_idx] == sema_address)
        {
            return sema_idx;
        }
    }
    CY_ASSERT(false);
    return 0;
}

#endif /* (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0) */

static cy_rslt_t _cyhal_ipc_sema_init(cyhal_ipc_t *obj, uint32_t semaphore_num, bool preemptable)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    /* On CAT1C and CAT1D devices, unlike CAT1A devices, startup code does not initialized IPC PDL semaphore and
    *  does not allocate shared memory for them. */
    #if defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D)
    if (false == semas_initialized)
    {
        #if (CYHAL_IPC_INIT_CORE)
        CY_SECTION_SHAREDMEM
        static uint32_t ipc_sema_array[_CYHAL_IPC_PDL_SEMA_COUNT / CY_IPC_SEMA_PER_WORD]
        #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
        CY_ALIGN(__SCB_DCACHE_LINE_SIZE)
        #endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
        ;
        result = (cy_rslt_t)Cy_IPC_Sema_Init(CY_IPC_CHAN_SEMA, _CYHAL_IPC_PDL_SEMA_COUNT, ipc_sema_array);
        #else
        result = (cy_rslt_t)Cy_IPC_Sema_Init(CY_IPC_CHAN_SEMA, 0, NULL);
        #endif /* CYHAL_IPC_INIT_CORE or other */
        if (CY_RSLT_SUCCESS == result)
        {
            semas_initialized = true;
        }
    }
    #endif /* defined(COMPONENT_CAT1C) || defined(COMPONENT_CAT1D) */

    if (CY_RSLT_SUCCESS == result)
    {
        obj->sema_preemptable = preemptable;
        obj->sema_number = semaphore_num;
        #if (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0)
        obj->rtos_sema = NULL;
        #endif /* (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0) */
    }

    return result;
}

/*
    step_us - for how long to wait between unsuccessful IPC sema takes
    use_rtos_sema - whether RTOS semaphores should be used in RTOS environment
*/
static cy_rslt_t _cyhal_ipc_sema_take(cyhal_ipc_t *obj, uint32_t *timeout_us, uint32_t step_us)
{
    cy_rslt_t result = ~CY_RSLT_SUCCESS;
    bool is_never_timeout = (*timeout_us == CYHAL_IPC_NEVER_TIMEOUT);

    #if (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0)
    cy_rslt_t rtos_sema_result = CY_RSLT_SUCCESS;
    if (NULL != obj->rtos_sema)
    {
        /* Using RTOS semaphore as mechanism to most effectively wait for IPC semaphore to be free. */

        /* When using an RTOS if a cyhal_ipc_semaphore_take api is called from and ISR in
        * in certain RTOSes cy_rtos_get_semaphore returns immediately without blocking. So we can
        * either busy wait around the semaphore being set in the ISR or use the normal polling method
        * we use in the non-RTOS case. For simplicity and to avoid the calling ISR from depending on
        * the IPC ISR priority we use the normal polling method.
        */
        bool in_isr = (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0;
        if (((*timeout_us >= 1000) || is_never_timeout) && (false == in_isr))
        {
            while ((result = (cy_rslt_t)Cy_IPC_Sema_Set(obj->sema_number, obj->sema_preemptable)) == (cy_rslt_t)CY_IPC_SEMA_LOCKED)
            {
                _cyhal_ipc_wait_step(is_never_timeout ? NULL : timeout_us, step_us);
            }
            if ((cy_rslt_t)CY_IPC_SEMA_LOCKED != result)
            {
                bool sema_not_yet_available = ((cy_rslt_t)CY_IPC_SEMA_NOT_ACQUIRED == result);
                if (sema_not_yet_available)
                {
                    _cyhal_irq_enable((_cyhal_system_irq_t)(cpuss_interrupts_ipc_0_IRQn + _CYHAL_IPC_SEMA_INTR_STR_NUM));

                    if (is_never_timeout)
                    {
                        while (CY_RSLT_SUCCESS != result)
                        {
                            uint32_t timeout_ms = CYHAL_IPC_POLLING_INTERVAL_uS / 1000;
                            if (timeout_ms == 0)
                            {
                                ++timeout_ms;
                            }
                            /* cy_rtos_get_semaphore works here as advanced delay mechanism, which in RTOS environment
                            *  helps utilize CPU in most efficient way while we are waiting for IPC Semaphore to be given.
                            *  Only unexpected return codes (expected are CY_RSLT_SUCCESS and CY_RTOS_TIMEOUT) will
                            *  be reported to user in case of unsuccessful semaphore take. */
                            rtos_sema_result = cy_rtos_get_semaphore(
                                        &(((_cyhal_ipc_rtos_sema_t *)obj->rtos_sema)->semaphore), timeout_ms, false);
                            result = (cy_rslt_t)Cy_IPC_Sema_Set(obj->sema_number, obj->sema_preemptable);
                        }
                    }
                    else
                    {
                        uint32_t timeout_ms = *timeout_us / 1000;
                        /* cy_rtos_get_semaphore works here as advanced delay mechanism, which in RTOS environment
                        *  helps utilize CPU in most efficient way while we are waiting for IPC Semaphore to be given.
                        *  Only unexpected return codes (expected are CY_RSLT_SUCCESS and CY_RTOS_TIMEOUT) will
                        *  be reported to user in case of unsuccessful semaphore take. */
                        rtos_sema_result = cy_rtos_get_semaphore(
                                    &(((_cyhal_ipc_rtos_sema_t *)obj->rtos_sema)->semaphore), timeout_ms, false);
                        result = (cy_rslt_t)Cy_IPC_Sema_Set(obj->sema_number, obj->sema_preemptable);
                        *timeout_us = 0;
                    }

                    _cyhal_irq_disable((_cyhal_system_irq_t)(cpuss_interrupts_ipc_0_IRQn + _CYHAL_IPC_SEMA_INTR_STR_NUM));
                }
                else
                {
                    result = CY_RSLT_SUCCESS;
                }
            }
        }
    }
    #endif /* (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0) */

    if (CY_RSLT_SUCCESS != result)
    {
        while(
            ((result = (cy_rslt_t)Cy_IPC_Sema_Set(obj->sema_number, obj->sema_preemptable)) != CY_RSLT_SUCCESS) &&
            ((*timeout_us != 0) || is_never_timeout)
        )
        {
            _cyhal_ipc_wait_step(is_never_timeout ? NULL : timeout_us, step_us);
        }
    }

    #if (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0)
    if (obj->sema_number < _CYHAL_IPC_RELEASE_INTR_BITS)
    {
        IPC_INTR_STRUCT_Type *ipc_intr_base = Cy_IPC_Drv_GetIntrBaseAddr(_CYHAL_IPC_SEMA_INTR_STR_NUM);
        uint32_t intr_status_masked = _FLD2VAL(IPC_INTR_STRUCT_INTR_MASKED_RELEASE, Cy_IPC_Drv_GetInterruptStatusMasked(ipc_intr_base));
        uint32_t current_sema_intr_mask = 1 << obj->sema_number;
        if ((CY_RSLT_SUCCESS == result) && (intr_status_masked & current_sema_intr_mask))
        {
            /* If semaphore get was successful and interrupt was not cleared by IRQ handler (e.g. interrupts are disabled),
            *   clear pending interrupt, that is related to this semaphore number */
            Cy_IPC_Drv_ClearInterrupt(ipc_intr_base, current_sema_intr_mask, 0);
        }
    }
    /* If IPC semaphore was not successfully got and unexpected result was returned by cy_rtos_get_semaphore,
    *  forward the RTOS result to the user. */
    if ((CY_RSLT_SUCCESS != result) && ((CY_RSLT_SUCCESS != rtos_sema_result) && (CY_RTOS_TIMEOUT != rtos_sema_result)))
    {
        result = rtos_sema_result;
    }
    #endif /* (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0) */

    return result;
}


/********************************************** QUEUES HELPERS ********************************************************/

static cy_rslt_t _cyhal_ipc_acquire_core_sync_sema(cyhal_ipc_t *obj, uint32_t *timeout_us)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != timeout_us);

    return _cyhal_ipc_sema_take(obj, timeout_us, _CYHAL_IPC_SERVICE_SEMA_STEP_US);
}

static cy_rslt_t _cyhal_ipc_give_core_sync_sema(cyhal_ipc_t *obj, uint32_t *timeout_us)
{
    cy_rslt_t result;
    bool is_never_timeout = (*timeout_us == CYHAL_IPC_NEVER_TIMEOUT);
    while ((CY_RSLT_SUCCESS != (result = cyhal_ipc_semaphore_give(obj))) && (is_never_timeout || (*timeout_us != 0)))
    {
        if (is_never_timeout || (*timeout_us > _CYHAL_IPC_SERVICE_SEMA_STEP_US))
        {
            cyhal_system_delay_us(_CYHAL_IPC_SERVICE_SEMA_STEP_US);
            if (false == is_never_timeout)
            {
                *timeout_us -= _CYHAL_IPC_SERVICE_SEMA_STEP_US;
            }
        }
        else
        {
            cyhal_system_delay_us(*timeout_us);
            *timeout_us = 0;
        }
    }
    return result;
}

static cy_rslt_t _cyhal_ipc_clear_interrupt(cyhal_ipc_t *obj, uint32_t isr_source_chan, uint32_t isr_chan)
{
    CY_ASSERT(NULL != obj);

    cy_rslt_t result;
    IPC_INTR_STRUCT_Type *ipc_intr_base = Cy_IPC_Drv_GetIntrBaseAddr(isr_source_chan);
    uint32_t timeout_acq = _CYHAL_IPC_SERVICE_SEMA_TIMEOUT_US;
    uint32_t timeout_give = _CYHAL_IPC_SERVICE_SEMA_TIMEOUT_US;
    /* We cannot allow interrupt to happen between _cyhal_ipc_acquire_core_sync_sema and successful
    *   _cyhal_ipc_give_core_sync_sema, as interrupt will also attempt to acquire semaphore (which
    *   will obviously fail) */
    uint32_t intr_status = cyhal_system_critical_section_enter();
    if (CY_RSLT_SUCCESS == (result = _cyhal_ipc_acquire_core_sync_sema(obj, &timeout_acq)))
    {
        Cy_IPC_Drv_ClearInterrupt(ipc_intr_base, (1UL << isr_chan), 0);
        _CYHAL_IPC_CI(isr_chan, _CYHAL_IPC_CUR_CORE_IDX);
        result = _cyhal_ipc_give_core_sync_sema(obj, &timeout_give);
    }
    cyhal_system_critical_section_exit(intr_status);
    return result;
}

static bool _cyhal_ipc_check_isr_handled(cyhal_ipc_t *obj, uint32_t channel, uint32_t *timeout)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != timeout);

    bool handled = false;
    /* We cannot allow interrupt to happen between _cyhal_ipc_acquire_core_sync_sema and successful
    *   _cyhal_ipc_give_core_sync_sema, as interrupt will also attempt to acquire semaphore (which
    *   will obviously fail) */
    uint32_t intr_status = cyhal_system_critical_section_enter();
    if (CY_RSLT_SUCCESS == _cyhal_ipc_acquire_core_sync_sema(obj, timeout))
    {
        /* interrupt is disabled for specific channel and core
        *   or (if enabled) interrupt is serviced */
        handled =   (((false == _CYHAL_IPC_IIE(channel, _CYHAL_IPC_CUR_CORE_IDX))
                        || _CYHAL_IPC_IIS(channel, _CYHAL_IPC_CUR_CORE_IDX)) &&
        #if (_CYHAL_IPC_CORE_NUM == 2)
                    ((false == _CYHAL_IPC_IIE(channel, _CYHAL_IPC_OTHER_CORE_IDX))
                        || _CYHAL_IPC_IIS(channel, _CYHAL_IPC_OTHER_CORE_IDX)));
        #elif (_CYHAL_IPC_CORE_NUM == 3)
                    ((false == _CYHAL_IPC_IIE(channel, _CYHAL_IPC_OTHER_CORE_0_IDX))
                        || _CYHAL_IPC_IIS(channel, _CYHAL_IPC_OTHER_CORE_0_IDX)) &&
                    ((false == _CYHAL_IPC_IIE(channel, _CYHAL_IPC_OTHER_CORE_1_IDX))
                        || _CYHAL_IPC_IIS(channel, _CYHAL_IPC_OTHER_CORE_1_IDX)));
        #endif /* (_CYHAL_IPC_CORE_NUM == 2) or (_CYHAL_IPC_CORE_NUM == 3) */
        (void)_cyhal_ipc_give_core_sync_sema(obj, timeout);
    }
    cyhal_system_critical_section_exit(intr_status);
    return handled;
}

static cy_rslt_t _cyhal_ipc_set_isr_expected(cyhal_ipc_t *obj, uint32_t channel)
{
    cy_rslt_t result;
    uint32_t timeout_acq = _CYHAL_IPC_SERVICE_SEMA_TIMEOUT_US;
    uint32_t timeout_give = _CYHAL_IPC_SERVICE_SEMA_TIMEOUT_US;
    /* We cannot allow interrupt to happen between _cyhal_ipc_acquire_core_sync_sema and successful
    *   _cyhal_ipc_give_core_sync_sema, as interrupt will also attempt to acquire semaphore (which
    *   will obviously fail) */
    uint32_t intr_status = cyhal_system_critical_section_enter();
    if (CY_RSLT_SUCCESS == (result = _cyhal_ipc_acquire_core_sync_sema(obj, &timeout_acq)))
    {
        _CYHAL_IPC_SI(channel, _CYHAL_IPC_CUR_CORE_IDX);
        #if (_CYHAL_IPC_CORE_NUM == 2)
        _CYHAL_IPC_SI(channel, _CYHAL_IPC_OTHER_CORE_IDX);
        #elif (_CYHAL_IPC_CORE_NUM == 3)
        _CYHAL_IPC_SI(channel, _CYHAL_IPC_OTHER_CORE_0_IDX);
        _CYHAL_IPC_SI(channel, _CYHAL_IPC_OTHER_CORE_1_IDX);
        #endif /* (_CYHAL_IPC_CORE_NUM == 2) or (_CYHAL_IPC_CORE_NUM == 3) */
        result = _cyhal_ipc_give_core_sync_sema(obj, &timeout_give);
    }
    cyhal_system_critical_section_exit(intr_status);
    return result;
}

static cy_rslt_t _cyhal_ipc_enable_interrupt(cyhal_ipc_t *obj, uint32_t channel, bool enable)
{
    CY_ASSERT(NULL != obj);

    cy_rslt_t result;
    IPC_INTR_STRUCT_Type *ipc_intr_base = Cy_IPC_Drv_GetIntrBaseAddr(_CYHAL_IPC_CURRENT_CORE_IPC_INTR_CHAN);
    uint32_t current_ipc_interrupt_mask = Cy_IPC_Drv_GetInterruptMask(ipc_intr_base);
    uint32_t channel_intr_mask = (1UL << channel);
    uint32_t timeout_acq = _CYHAL_IPC_SERVICE_SEMA_TIMEOUT_US;
    uint32_t timeout_give = _CYHAL_IPC_SERVICE_SEMA_TIMEOUT_US;

    /* We cannot allow interrupt to happen between _cyhal_ipc_acquire_core_sync_sema and successful
    *   _cyhal_ipc_give_core_sync_sema, as interrupt will also attempt to acquire semaphore (which
    *   will obviously fail) */
    uint32_t intr_status = cyhal_system_critical_section_enter();
    if (CY_RSLT_SUCCESS == (result = _cyhal_ipc_acquire_core_sync_sema(obj, &timeout_acq)))
    {
        if (enable)
        {
            Cy_IPC_Drv_ClearInterrupt(ipc_intr_base, channel_intr_mask, 0);
            Cy_IPC_Drv_SetInterruptMask(ipc_intr_base, current_ipc_interrupt_mask | channel_intr_mask, 0);
            _CYHAL_IPC_SIE(channel, _CYHAL_IPC_CUR_CORE_IDX);
        }
        else
        {
            Cy_IPC_Drv_SetInterruptMask(ipc_intr_base, current_ipc_interrupt_mask & ~channel_intr_mask, 0);
            _CYHAL_IPC_SID(channel, _CYHAL_IPC_CUR_CORE_IDX);
        }
        result = _cyhal_ipc_give_core_sync_sema(obj, &timeout_give);
    }
    cyhal_system_critical_section_exit(intr_status);
    return result;
}

static cyhal_ipc_queue_t *_cyhal_ipc_find_last_element(cyhal_ipc_queue_t *queue_handle)
{
    CY_ASSERT(NULL != queue_handle);

    cyhal_ipc_queue_t *retval = queue_handle;
    while ((retval->next_queue_obj) != NULL) { retval = retval->next_queue_obj; }
    return retval;
}

static bool _cyhal_ipc_check_queue_number_used(const cyhal_ipc_queue_t *queue_to_be_added)
{
    CY_ASSERT(NULL != queue_to_be_added);

    if ((NULL != _cyhal_ipc_service_data) && (NULL != _cyhal_ipc_service_data->queues_ll_pointer))
    {
        cyhal_ipc_queue_t *queue_handle = _cyhal_ipc_service_data->queues_ll_pointer;
        do
        {
            if ((queue_handle->channel_num == queue_to_be_added->channel_num) &&
                (queue_handle->queue_num == queue_to_be_added->queue_num))
            {
                return true;
            }
        }
        while ((queue_handle = queue_handle->next_queue_obj) != NULL);
    }
    return false;
}

static void _cyhal_ipc_add_queue_element(cyhal_ipc_t *obj, cyhal_ipc_queue_t *queue_handle_to_add)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != queue_handle_to_add);
    CY_ASSERT(NULL != _cyhal_ipc_service_data);

    cyhal_ipc_queue_t *queue_handle = obj->queue_obj;

    /* Fill in service data */
    queue_handle_to_add->curr_items = 0;
    queue_handle_to_add->queue_head = (void *)&(((uint8_t *)(queue_handle_to_add->queue_pool))[0]);
    queue_handle_to_add->queue_tail = (void *)&(((uint8_t *)(queue_handle_to_add->queue_pool))[0]);
    queue_handle_to_add->next_queue_obj = NULL;
    queue_handle_to_add->triggered_events = 0;

    if (NULL != queue_handle)
    {
        cyhal_ipc_queue_t *last_queue_handle = _cyhal_ipc_find_last_element(queue_handle);
        last_queue_handle->next_queue_obj = queue_handle_to_add;
    }
    else
    {
        /* First queue in current cyhal_ipc_t object */
        obj->queue_obj = (void *)queue_handle_to_add;
        if (NULL != _cyhal_ipc_service_data->queues_ll_pointer)
        {
            cyhal_ipc_queue_t *last_queue_handle = _cyhal_ipc_find_last_element(_cyhal_ipc_service_data->queues_ll_pointer);
            last_queue_handle->next_queue_obj = obj->queue_obj;
        }
    }

    if (NULL == _cyhal_ipc_service_data->queues_ll_pointer)
    {
        _cyhal_ipc_service_data->queues_ll_pointer = queue_handle_to_add;
    }
}

static void _cyhal_ipc_wait_step(uint32_t *timeout_us, uint32_t polling_interval_us)
{
    uint32_t us_wait_step = polling_interval_us % 1000;
    uint32_t ms_wait_step = (polling_interval_us - us_wait_step) / 1000;

    if (NULL == timeout_us)
    {
        if (ms_wait_step != 0)
        {
            cyhal_system_delay_ms(ms_wait_step);
        }
        if (us_wait_step != 0)
        {
            cyhal_system_delay_us(us_wait_step);
        }
    }
    else
    {
        if (us_wait_step + (ms_wait_step * 1000) <= *timeout_us)
        {
            if (ms_wait_step != 0)
            {
                cyhal_system_delay_ms(ms_wait_step);
                *timeout_us -= (ms_wait_step * 1000);
            }
            if (us_wait_step != 0)
            {
                cyhal_system_delay_us(us_wait_step);
                *timeout_us -= us_wait_step;
            }
        }
        else if (*timeout_us != 0)
        {
            cyhal_system_delay_us(*timeout_us);
            *timeout_us = 0;
        }
    }
}

static cy_rslt_t _cyhal_ipc_wait_lock_acquire(IPC_STRUCT_Type *ipc_base, uint32_t *timeout_us, bool wait_forever)
{
    CY_ASSERT(NULL != ipc_base);
    cy_rslt_t result;

    while (((result = (cy_rslt_t)Cy_IPC_Drv_LockAcquire(ipc_base)) != CY_RSLT_SUCCESS) &&
            (wait_forever || ((NULL != timeout_us) && (*timeout_us != 0))))
    {
        _cyhal_ipc_wait_step(wait_forever ? NULL : timeout_us, CYHAL_IPC_POLLING_INTERVAL_uS);
    }

    return result;
}

static cy_rslt_t _cyhal_ipc_queue_put_get(cyhal_ipc_t *obj, void *msg, uint32_t timeout_us, bool put)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != msg);
    CY_ASSERT(NULL != obj->queue_obj);

    if ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0)
    {
        return CYHAL_IPC_RSLT_ERR_CANT_OPERATE_IN_ISR;
    }

    bool is_never_timeout = (timeout_us == CYHAL_IPC_NEVER_TIMEOUT);

    cyhal_ipc_queue_t *queue_handle = obj->queue_obj;
    uint32_t channel = obj->queue_obj->channel_num;
    IPC_STRUCT_Type *ipc_base = Cy_IPC_Drv_GetIpcBaseAddress(channel);

    uint32_t timeout_us_left = timeout_us;
    cy_rslt_t result = CY_RSLT_SUCCESS;

    /* Used to perform last loop when timeout from non-zero become zero */
    bool last_loop;
    do
    {
        bool is_prev_isr_handled;
        while ((false == (is_prev_isr_handled = _cyhal_ipc_check_isr_handled(obj, channel, &timeout_us_left)))
                && (is_never_timeout || (timeout_us_left != 0)))
        {
            if (is_never_timeout || (timeout_us_left > _CYHAL_IPC_SERVICE_SEMA_STEP_US))
            {
                cyhal_system_delay_us(_CYHAL_IPC_SERVICE_SEMA_STEP_US);
                if (false == is_never_timeout)
                {
                    timeout_us_left -= _CYHAL_IPC_SERVICE_SEMA_STEP_US;
                }
            }
            else
            {
                cyhal_system_delay_us(timeout_us_left);
                timeout_us_left = 0;
            }
        }

        if (false == is_prev_isr_handled)
        {
            /* One or more cores didn't handle previous operation that caused interrupt */
            return CYHAL_IPC_RSLT_ERR_ISR_WAS_NOT_HANDLED;
        }

        last_loop = false;
        result = _cyhal_ipc_wait_lock_acquire(ipc_base, &timeout_us_left, is_never_timeout);

        uint16_t triggered_events = 0;
        if (CY_RSLT_SUCCESS == result)
        {
            _CYHAL_IPC_CLR_TRIGGERED_EVENT(queue_handle->triggered_events);

            if (put)
            {
                if (queue_handle->curr_items < queue_handle->num_items)
                {
                    memcpy(queue_handle->queue_head, msg, queue_handle->item_size);
                    ++queue_handle->curr_items;
                    /* Checking the position of queue_head in roundary buffer. If it is at the end of buffer, moving head to the start */
                    if (((uint32_t)queue_handle->queue_head - (uint32_t)queue_handle->queue_pool) ==
                        (uint32_t)((queue_handle->num_items - 1) * queue_handle->item_size))
                    {
                        queue_handle->queue_head = queue_handle->queue_pool;
                    }
                    else
                    {
                        queue_handle->queue_head = (void *)((uint8_t *)(queue_handle->queue_head) + queue_handle->item_size);
                    }

                    triggered_events = CYHAL_IPC_QUEUE_WRITE;
                    if (queue_handle->curr_items == queue_handle->num_items)
                    {
                        triggered_events |= CYHAL_IPC_QUEUE_FULL;
                    }

                    result = CY_RSLT_SUCCESS;
                }
                else
                {
                    result = CYHAL_IPC_RSLT_ERR_QUEUE_FULL;
                }
            }
            else
            {
                if (queue_handle->curr_items > 0)
                {
                    memcpy(msg, queue_handle->queue_tail, queue_handle->item_size);
                    --queue_handle->curr_items;
                    /* Checking the position of queue_tail in roundary buffer. If it is at the end of buffer, moving tail to the start */
                    if (((uint32_t)(queue_handle->queue_tail) - (uint32_t)(queue_handle->queue_pool)) == (uint32_t)((queue_handle->num_items - 1) * queue_handle->item_size))
                    {
                        queue_handle->queue_tail = queue_handle->queue_pool;
                    }
                    else
                    {
                        queue_handle->queue_tail = (void *)((uint8_t *)(queue_handle->queue_tail) + queue_handle->item_size);
                    }

                    triggered_events = CYHAL_IPC_QUEUE_READ;
                    if (queue_handle->curr_items == 0)
                    {
                        triggered_events |= CYHAL_IPC_QUEUE_EMPTY;
                    }

                    result = CY_RSLT_SUCCESS;
                }
                else
                {
                    result = CYHAL_IPC_RSLT_ERR_QUEUE_EMPTY;
                }
            }

            bool inform_ipcs_via_interrupt = false;
            if ((uint16_t)CYHAL_IPC_NO_INTR != triggered_events)
            {
                inform_ipcs_via_interrupt = true;
                _CYHAL_IPC_ADD_TRIGGERED_EVENT(queue_handle->triggered_events, triggered_events);
                result = _cyhal_ipc_set_isr_expected(obj, channel);
            }

            /* No reason to check the return value, as this function can return either:
            * - CY_IPC_DRV_SUCCESS - if lock was successfully released, or
            * - CY_IPC_DRV_ERROR - if IPC channel was not acquired before the function call, which is impossible in this
            * situation */
            /* No reason to generate interrupt if no events were triggered by performed operation */
            (void)Cy_IPC_Drv_LockRelease(ipc_base, inform_ipcs_via_interrupt ? _CYHAL_IPC_TRIGGER_ISR_MASK : 0u);
        }

        if ((CY_RSLT_SUCCESS != result) && (is_never_timeout || (timeout_us_left != 0)))
        {
            _cyhal_ipc_wait_step(is_never_timeout ? NULL : &timeout_us_left, CYHAL_IPC_POLLING_INTERVAL_uS);
            if ((false == is_never_timeout) && (timeout_us_left == 0))
            {
                last_loop = true;
            }
        }

    } while ((CY_RSLT_SUCCESS != result) && (is_never_timeout || (timeout_us_left != 0) || last_loop));

    return result;
}

uint16_t _cyhal_ipc_decode_triggered_events(cyhal_ipc_t *obj)
{
    CY_ASSERT(NULL != obj);
    /* Check what events signatures are changed and combine with triggered events */
    uint16_t retval = _CYHAL_IPC_GET_SIGNATURES(obj->queue_obj->triggered_events ^ obj->processed_events) &
        _CYHAL_IPC_GET_TRIGGERED_EVENT(obj->queue_obj->triggered_events);
    obj->processed_events = obj->queue_obj->triggered_events;
    return retval;
}

/********************************* SEMAPHORES / QUEUES IPC INTERRUPT HANDLER********************************************/

static void _cyhal_ipc_irq_handler(void)
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    uint32_t isr_channel = irqn - cpuss_interrupts_ipc_0_IRQn;
    IPC_INTR_STRUCT_Type *ipc_intr_base = Cy_IPC_Drv_GetIntrBaseAddr(isr_channel);
    /* We are interested only in Release events */
    uint32_t interrupt_status_masked =
            _FLD2VAL(IPC_INTR_STRUCT_INTR_MASKED_RELEASE, Cy_IPC_Drv_GetInterruptStatusMasked(ipc_intr_base));

    #if (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0)
    if (_CYHAL_IPC_SEMA_INTR_STR_NUM == isr_channel)
    {
        if (interrupt_status_masked != 0)
        {
            for (size_t sema_idx = 0; sema_idx < CYHAL_IPC_RTOS_SEMA_NUM; sema_idx++)
            {
                uint32_t current_sema_mask = 1 << _cyhal_ipc_rtos_semaphores[sema_idx].sema_num;
                if (_cyhal_ipc_rtos_semaphores[sema_idx].initialized && (interrupt_status_masked & current_sema_mask))
                {
                    (void)cy_rtos_set_semaphore(&_cyhal_ipc_rtos_semaphores[sema_idx].semaphore, true);
                    Cy_IPC_Drv_ClearInterrupt(ipc_intr_base, current_sema_mask, 0);
                    break;
                }
            }
        }
    }
    else
    #endif /* (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0) */
    if (isr_channel >= CYHAL_IPC_CHAN_0)
    {
        uint32_t channel = CYHAL_IPC_CHAN_0;
        while (interrupt_status_masked != 0)
        {
            uint32_t channel_mask = 1UL << channel;
            if ((interrupt_status_masked & (channel_mask)) != 0)
            {
                interrupt_status_masked &= ~channel_mask;
                cyhal_ipc_t *obj = _CYHAL_IPC_OBJ_ARR_EL(channel);
                if (CY_RSLT_SUCCESS == _cyhal_ipc_clear_interrupt(obj, isr_channel, channel))
                {
                    /* Going through all known cyhal_ipc_t objects, that are tied to the IPC channel, that provoked interrupt */
                    while (obj != NULL)
                    {
                        /* User enabled callback for certain events */
                        if ((obj->user_events != CYHAL_IPC_NO_INTR) && (obj->callback_data.callback != NULL))
                        {
                            /* Check triggered events and (by checking signatures) filter only those events,
                            *   that were not yet processed */
                            uint16_t queue_events = _cyhal_ipc_decode_triggered_events(obj);
                            /* Checking if last operation for certain queue provoked one of the activated by user events */
                            uint16_t activated_occurred_events = obj->user_events & queue_events;
                            if (activated_occurred_events)
                            {
                                cyhal_ipc_event_callback_t callback = (cyhal_ipc_event_callback_t)obj->callback_data.callback;
                                callback(obj->callback_data.callback_arg, (cyhal_ipc_event_t)activated_occurred_events);
                            }
                        }
                        obj = obj->prev_object;
                    }
                }
            }
            channel++;
        }
    }
}

/**************************************** SEMAPHORE PUBLIC FUNCTIONS **************************************************/

cy_rslt_t cyhal_ipc_semaphore_init(cyhal_ipc_t *obj, uint32_t semaphore_num, bool preemptable)
{
    CY_ASSERT(NULL != obj);

    /* Last semaphore is used for internal IPC queues functionality */
    if (semaphore_num >= (_CYHAL_IPC_PDL_SEMA_COUNT - 1))
    {
        /* Semaphore index exceeds the number of allowed Semaphores */
        return CYHAL_IPC_RSLT_ERR_INVALID_PARAMETER;
    }

    cy_rslt_t result = _cyhal_ipc_sema_init(obj, semaphore_num, preemptable);

    #if (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0)
    if ((CY_RSLT_SUCCESS == result) && (semaphore_num < _CYHAL_IPC_RELEASE_INTR_BITS))
    {
        /* Looking for free RTOS semaphore from the pre-allocated pool */
        for (size_t rtos_sema_idx = 0; rtos_sema_idx < CYHAL_IPC_RTOS_SEMA_NUM; ++rtos_sema_idx)
        {
            if (false == _cyhal_ipc_rtos_semaphores[rtos_sema_idx].initialized)
            {
                result = cy_rtos_init_semaphore(&(_cyhal_ipc_rtos_semaphores[rtos_sema_idx].semaphore), 1, 0);
                if (CY_RSLT_SUCCESS == result)
                {
                    obj->rtos_sema = (void *)&_cyhal_ipc_rtos_semaphores[rtos_sema_idx];
                    _cyhal_ipc_rtos_semaphores[rtos_sema_idx].initialized = true;
                    _cyhal_ipc_rtos_semaphores[rtos_sema_idx].sema_num = semaphore_num;
                    break;
                }
            }
        }
        if ((CY_RSLT_SUCCESS == result) && (NULL != obj->rtos_sema))
        {
            IPC_INTR_STRUCT_Type *ipc_intr_base = Cy_IPC_Drv_GetIntrBaseAddr(_CYHAL_IPC_SEMA_INTR_STR_NUM);
            /* Enable all possible interrupt bits for sema interrupt */
            Cy_IPC_Drv_SetInterruptMask(ipc_intr_base, (1 << _CYHAL_IPC_RELEASE_INTR_BITS) - 1, 0);
            _cyhal_irq_register((_cyhal_system_irq_t)(cpuss_interrupts_ipc_0_IRQn + _CYHAL_IPC_SEMA_INTR_STR_NUM), CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_ipc_irq_handler);
            /* No IRQ enable, as it will be done before each time interrupt is needed */
        }
    }
    #endif /* (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0) */

    return result;
}

void cyhal_ipc_semaphore_free(cyhal_ipc_t *obj)
{
    #if (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0)
    if (NULL != obj->rtos_sema)
    {
        (void)cy_rtos_deinit_semaphore(&((_cyhal_ipc_rtos_sema_t *)obj->rtos_sema)->semaphore);
        ((_cyhal_ipc_rtos_sema_t *)obj->rtos_sema)->initialized = false;
        ((_cyhal_ipc_rtos_sema_t *)obj->rtos_sema)->sema_num = 0;
        obj->rtos_sema = NULL;
    }
    #else
    CY_UNUSED_PARAMETER(obj);
    #endif /* (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0) or other */
}

cy_rslt_t cyhal_ipc_semaphore_take(cyhal_ipc_t *obj, uint32_t timeout_us)
{
    CY_ASSERT(NULL != obj);
    return _cyhal_ipc_sema_take(obj, &timeout_us, CYHAL_IPC_POLLING_INTERVAL_uS);
}

cy_rslt_t cyhal_ipc_semaphore_give(cyhal_ipc_t *obj)
{
    CY_ASSERT(NULL != obj);
    cy_en_ipcsema_status_t ipc_sema_result = Cy_IPC_Sema_Clear(obj->sema_number, obj->sema_preemptable);
    cy_rslt_t result = ((CY_IPC_SEMA_SUCCESS == ipc_sema_result) || (CY_IPC_SEMA_NOT_ACQUIRED == ipc_sema_result)) ?
            CY_RSLT_SUCCESS : (cy_rslt_t)ipc_sema_result;
    #if (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0)
    if ((obj->sema_number < _CYHAL_IPC_RELEASE_INTR_BITS) && (CY_IPC_SEMA_SUCCESS == ipc_sema_result))
    {
        IPC_INTR_STRUCT_Type *ipc_intr_base = Cy_IPC_Drv_GetIntrBaseAddr(_CYHAL_IPC_SEMA_INTR_STR_NUM);
        Cy_IPC_Drv_SetInterrupt(ipc_intr_base, 1 << obj->sema_number, 0);
    }
    #endif /* (defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)) && (CYHAL_IPC_RTOS_SEMA_NUM > 0) */
    return result;
}

/***************************************** QUEUES PUBLIC FUNCTIONS ****************************************************/

cy_rslt_t cyhal_ipc_queue_init(cyhal_ipc_t *obj, cyhal_ipc_queue_t *queue_handle)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != queue_handle);
    CY_ASSERT(NULL != queue_handle->queue_pool);

    cy_rslt_t result = CY_RSLT_SUCCESS;

    /* Queue IPC channel number and number of items check */
    if ((false == _CYHAL_IPC_CHAN_IDX_CORRECT(queue_handle->channel_num)) || (queue_handle->num_items == 0) ||
            (queue_handle->item_size == 0))
    {
        return CYHAL_IPC_RSLT_ERR_INVALID_PARAMETER;
    }

    uint32_t channel = queue_handle->channel_num;
    if (false == _cyhal_ipc_check_queue_number_used(queue_handle))
    {
        memset(obj, 0, sizeof(cyhal_ipc_t));

        result = _cyhal_ipc_sema_init(obj, _CYHAL_IPC_PDL_SEMA_COUNT - 1, false);
        if (CY_RSLT_SUCCESS == result)
        {
            /* If this is first IPC object being initialized,
            *  we need to clear isr_clear_sync and isr_enable_sync flags, as the are
            *  located in shared memory, which is not being cleared upon initialization.
            *
            *  In addition, clear all IPC HAL user - available IPC channels' data to prevent
            *  cyhal_queue_get_handle calls read random value and treat it as _cyhal_ipc_sevice_data_t struct pointer
            */
            if (NULL == _cyhal_ipc_service_data)
            {
                CY_SECTION_SHAREDMEM
                static uint8_t isr_clear_sync[_CYHAL_IPC_CORE_NUM]
                #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
                CY_ALIGN(__SCB_DCACHE_LINE_SIZE)
                #endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
                ;
                CY_SECTION_SHAREDMEM
                static uint8_t isr_enable_sync[_CYHAL_IPC_CORE_NUM]
                #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
                CY_ALIGN(__SCB_DCACHE_LINE_SIZE)
                #endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
                ;
                CY_SECTION_SHAREDMEM
                static _cyhal_ipc_sevice_data_t ipc_service_data
                #if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
                CY_ALIGN(__SCB_DCACHE_LINE_SIZE)
                #endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */
                ;

                memset(isr_clear_sync, 0, sizeof(isr_clear_sync));
                memset(isr_enable_sync, 0, sizeof(isr_enable_sync));

                ipc_service_data.isr_clear_sync = isr_clear_sync;
                ipc_service_data.isr_enable_sync = isr_enable_sync;
                ipc_service_data.queues_ll_pointer = NULL;
                _cyhal_ipc_service_data = &ipc_service_data;

                for (uint32_t chan_idx = CYHAL_IPC_CHAN_0; chan_idx < CYHAL_IPC_CHAN_0 + CYHAL_IPC_USR_CHANNELS; ++chan_idx)
                {
                    IPC_STRUCT_Type *cur_chan_ipc_base = Cy_IPC_Drv_GetIpcBaseAddress(chan_idx);
                    Cy_IPC_Drv_WriteDataValue(cur_chan_ipc_base, 0);
                }

                for (uint8_t obj_idx = 0; obj_idx < CYHAL_IPC_USR_CHANNELS; ++obj_idx)
                {
                    _ipc_objects[obj_idx] = NULL;
                }
            }

            _cyhal_ipc_add_queue_element(obj, queue_handle);

            obj->callback_data.callback = NULL;
            obj->callback_data.callback_arg = NULL;
            obj->user_events = CYHAL_IPC_NO_INTR;
            obj->processed_events = CYHAL_IPC_NO_INTR;

            IPC_STRUCT_Type *ipc_base = Cy_IPC_Drv_GetIpcBaseAddress(channel);
            Cy_IPC_Drv_WriteDataValue(ipc_base, (uint32_t)_cyhal_ipc_service_data);

            if (false == interrupts_initialized)
            {
                _cyhal_irq_register(_CYHAL_IPC_CURRENT_CORE_IPC_INTR_SRC, CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_ipc_irq_handler);
                _cyhal_irq_enable(_CYHAL_IPC_CURRENT_CORE_IPC_INTR_SRC);
                interrupts_initialized = true;
            }

            obj->prev_object = _CYHAL_IPC_OBJ_ARR_EL(channel);
            _CYHAL_IPC_OBJ_ARR_EL(channel) = obj;
        }
    }
    else
    {
        return CYHAL_IPC_RSLT_ERR_QUEUE_NUM_IN_USE;
    }
    return result;
}

void cyhal_ipc_queue_free(cyhal_ipc_t *obj)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->queue_obj);

    uint32_t channel = obj->queue_obj->channel_num;

    if (NULL != _cyhal_ipc_service_data->queues_ll_pointer)
    {
        cyhal_ipc_queue_t *current_queue_obj = _cyhal_ipc_service_data->queues_ll_pointer;

        /* Queue element to be deleted is the first one in the linked list */
        if (_cyhal_ipc_service_data->queues_ll_pointer == obj->queue_obj)
        {
            uint32_t timeout = _CYHAL_IPC_SERVICE_SEMA_TIMEOUT_US;
            while (CY_RSLT_SUCCESS != _cyhal_ipc_sema_take(obj, &timeout, _CYHAL_IPC_SERVICE_SEMA_STEP_US))
            {
                timeout = _CYHAL_IPC_SERVICE_SEMA_TIMEOUT_US;;
            }
            _cyhal_ipc_service_data->queues_ll_pointer = obj->queue_obj->next_queue_obj;
            while (CY_RSLT_SUCCESS != cyhal_ipc_semaphore_give(obj)) { cyhal_system_delay_us(_CYHAL_IPC_SERVICE_SEMA_STEP_US); }
        }
        else
        {
            while (NULL != current_queue_obj)
            {
                if (current_queue_obj->next_queue_obj == obj->queue_obj)
                {
                    IPC_STRUCT_Type *ipc_base = Cy_IPC_Drv_GetIpcBaseAddress(current_queue_obj->next_queue_obj->channel_num);
                    /* Locking IPC channel before modifying one of its queues */
                    _cyhal_ipc_wait_lock_acquire(ipc_base, NULL, true);
                    current_queue_obj->next_queue_obj = current_queue_obj->next_queue_obj->next_queue_obj;
                    (void)Cy_IPC_Drv_LockRelease(ipc_base, 0);
                    break;
                }
                current_queue_obj = current_queue_obj->next_queue_obj;
            }
        }
    }

    cyhal_ipc_t *curr_ipc_obj = _CYHAL_IPC_OBJ_ARR_EL(channel);
    if (curr_ipc_obj == obj)
    {
        _CYHAL_IPC_OBJ_ARR_EL(channel) = obj->prev_object;
    }
    else
    {
        while (NULL != curr_ipc_obj)
        {
            if (curr_ipc_obj->prev_object == obj)
            {
                curr_ipc_obj->prev_object = curr_ipc_obj->prev_object->prev_object;
                break;
            }
            curr_ipc_obj = curr_ipc_obj->prev_object;
        }
    }

    cyhal_ipc_semaphore_free(obj);
    memset(obj, 0, sizeof(cyhal_ipc_t));
}

cy_rslt_t cyhal_ipc_queue_get_handle(cyhal_ipc_t *obj, uint32_t channel_num, uint32_t queue_num)
{
    CY_ASSERT(NULL != obj);

    cy_rslt_t result = CY_RSLT_SUCCESS;

    /* Queue IPC channel number check */
    if (false == _CYHAL_IPC_CHAN_IDX_CORRECT(channel_num))
    {
        return CYHAL_IPC_RSLT_ERR_INVALID_PARAMETER;
    }

    if (NULL == _cyhal_ipc_service_data)
    {
        /* Getting shared memory memory pointer to the first element of queues linked list */
        IPC_STRUCT_Type *ipc_base = Cy_IPC_Drv_GetIpcBaseAddress(channel_num);
        _cyhal_ipc_service_data = (_cyhal_ipc_sevice_data_t *)Cy_IPC_Drv_ReadDataValue(ipc_base);
        if ((NULL == _cyhal_ipc_service_data) || (NULL == _cyhal_ipc_service_data->queues_ll_pointer))
        {
            return CYHAL_IPC_RSLT_ERR_QUEUE_NOT_FOUND;
        }
        for (uint8_t obj_idx = 0; obj_idx < CYHAL_IPC_USR_CHANNELS; ++obj_idx)
        {
            _ipc_objects[obj_idx] = NULL;
        }
    }

    if (NULL != _cyhal_ipc_service_data->queues_ll_pointer)
    {
        bool queue_obj_found = false;
        cyhal_ipc_queue_t *queue_ptr = _cyhal_ipc_service_data->queues_ll_pointer;

        while (queue_ptr != NULL)
        {
            if ((queue_ptr->channel_num == channel_num) && (queue_ptr->queue_num == queue_num))
            {
                queue_obj_found = true;
                break;
            }
            queue_ptr = queue_ptr->next_queue_obj;
        }

        if (queue_obj_found)
        {
            memset(obj, 0, sizeof(cyhal_ipc_t));
            obj->callback_data.callback = NULL;
            obj->callback_data.callback_arg = NULL;
            obj->user_events = CYHAL_IPC_NO_INTR;
            obj->processed_events = CYHAL_IPC_NO_INTR;
            obj->queue_obj = queue_ptr;
            obj->prev_object = _CYHAL_IPC_OBJ_ARR_EL(channel_num);
            _CYHAL_IPC_OBJ_ARR_EL(channel_num) = obj;

            result = _cyhal_ipc_sema_init(obj, _CYHAL_IPC_PDL_SEMA_COUNT - 1, false);

            if ((CY_RSLT_SUCCESS == result) && (false == interrupts_initialized))
            {
                _cyhal_irq_register(_CYHAL_IPC_CURRENT_CORE_IPC_INTR_SRC, CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_ipc_irq_handler);
                _cyhal_irq_enable(_CYHAL_IPC_CURRENT_CORE_IPC_INTR_SRC);
                interrupts_initialized = true;
            }
        }
        else
        {
            result = CYHAL_IPC_RSLT_ERR_QUEUE_NOT_FOUND;
        }
    }
    return result;
}

void cyhal_ipc_queue_register_callback(cyhal_ipc_t *obj, cyhal_ipc_event_callback_t callback, void *callback_arg)
{
    CY_ASSERT(NULL != obj);
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
}

void cyhal_ipc_queue_enable_event(cyhal_ipc_t *obj, cyhal_ipc_event_t event, uint8_t intr_priority, bool enable)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->queue_obj);

    uint32_t channel = obj->queue_obj->channel_num;
    IPC_INTR_STRUCT_Type *ipc_intr_base = Cy_IPC_Drv_GetIntrBaseAddr(_CYHAL_IPC_CURRENT_CORE_IPC_INTR_CHAN);

    if (enable)
    {
        IPC_STRUCT_Type *ipc_base = Cy_IPC_Drv_GetIpcBaseAddress(channel);
        _cyhal_ipc_wait_lock_acquire(ipc_base, NULL, true);
        uint32_t event_and_sign_mask = (event << _CYHAL_IPC_EVENTS_SIGNATURES_BITS) | event;
        /* Extract event in question and its signature from current queue triggered events and copy such bits into
        *  obj->processed_events, so callback will not be called for currently pending (but being now activated) events. */
        obj->processed_events =
                (obj->processed_events & ~event_and_sign_mask) | (obj->queue_obj->triggered_events & event_and_sign_mask);
        (void)Cy_IPC_Drv_LockRelease(ipc_base, 0);

        obj->user_events |= event;
    }
    else
    {
        obj->user_events &= ~event;
    }

    _cyhal_system_irq_t irqn = _CYHAL_IPC_CURRENT_CORE_IPC_INTR_SRC;
    /* As one IPC INTR structure service all IPC channels on certain core, we can't change interrupt priority
    *  for all channels as requested, we can only make it higher. */
    if (intr_priority < _cyhal_irq_get_priority(irqn))
    {
        _cyhal_irq_set_priority(irqn, intr_priority);
    }

    uint32_t current_ipc_interrupt_mask = Cy_IPC_Drv_GetInterruptMask(ipc_intr_base);
    uint32_t channel_intr_mask = (1UL << channel);
    if (CYHAL_IPC_NO_INTR != obj->user_events)
    {
        if ((current_ipc_interrupt_mask & channel_intr_mask) == 0)
        {
            /* This interrupt was not yet enabled before */
            (void)_cyhal_ipc_enable_interrupt(obj, channel, true);
        }
    }
    else
    {
        /* Go through all queues, which tied to current channel and check they have no events activated either */
        uint32_t all_queues_events = CYHAL_IPC_NO_INTR;
        cyhal_ipc_t *obj_to_check = _CYHAL_IPC_OBJ_ARR_EL(channel);

        while (NULL != obj_to_check)
        {
            all_queues_events |= obj_to_check->user_events;
            /* When at least one obj has events enabled, no reason to continue and waste CPU cycles */
            if (CYHAL_IPC_NO_INTR != all_queues_events)
            {
                break;
            }
            obj_to_check = obj_to_check->prev_object;
        }

        /* All channel-related queues have no events enabled, disabling interrupt */
        if (CYHAL_IPC_NO_INTR == all_queues_events)
        {
            (void)_cyhal_ipc_enable_interrupt(obj, channel, false);
        }
    }
}

cy_rslt_t cyhal_ipc_queue_put(cyhal_ipc_t *obj, void *msg, uint32_t timeout_us)
{
    return _cyhal_ipc_queue_put_get(obj, msg, timeout_us, true);
}

cy_rslt_t cyhal_ipc_queue_get(cyhal_ipc_t *obj, void *msg, uint32_t timeout_us)
{
    return _cyhal_ipc_queue_put_get(obj, msg, timeout_us, false);
}

uint32_t cyhal_ipc_queue_count(cyhal_ipc_t *obj)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->queue_obj);
    uint32_t channel = obj->queue_obj->channel_num;
    IPC_STRUCT_Type *ipc_base = Cy_IPC_Drv_GetIpcBaseAddress(channel);
    (void)_cyhal_ipc_wait_lock_acquire(ipc_base, NULL, true);
    uint32_t curr_items = obj->queue_obj->curr_items;
    (void)Cy_IPC_Drv_LockRelease(ipc_base, 0);
    return curr_items;
}

cy_rslt_t cyhal_ipc_queue_reset(cyhal_ipc_t *obj)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->queue_obj);

    cyhal_ipc_queue_t *queue_handle = obj->queue_obj;
    uint32_t channel = obj->queue_obj->channel_num;
    IPC_STRUCT_Type *ipc_base = Cy_IPC_Drv_GetIpcBaseAddress(channel);

    cy_rslt_t result = _cyhal_ipc_wait_lock_acquire(ipc_base, NULL, true);

    if (CY_RSLT_SUCCESS == result)
    {
        queue_handle->curr_items = 0;
        queue_handle->queue_head = queue_handle->queue_pool;
        queue_handle->queue_tail = queue_handle->queue_pool;
        _CYHAL_IPC_ADD_TRIGGERED_EVENT(queue_handle->triggered_events, CYHAL_IPC_QUEUE_RESET);
        (void)Cy_IPC_Drv_LockRelease(ipc_base, _CYHAL_IPC_TRIGGER_ISR_MASK);
    }

    return result;
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_IPC */
