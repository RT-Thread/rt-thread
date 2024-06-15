/*
 * SPDX-FileCopyrightText: 2020 Amazon.com, Inc. or its affiliates
 *
 * SPDX-License-Identifier: MIT
 *
 * SPDX-FileContributor: 2016-2022 Espressif Systems (Shanghai) CO LTD
 */
/*
 * FreeRTOS Kernel V10.4.3
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifndef __ASSEMBLER__

#include "sdkconfig.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "spinlock.h"
#include "soc/interrupt_core0_reg.h"
#include "esp_macros.h"
#include "esp_attr.h"
#include "esp_cpu.h"
#include "esp_rom_sys.h"
#include "esp_heap_caps.h"
#include "esp_system.h"             /* required by esp_get_...() functions in portable.h. [refactor-todo] Update portable.h */
#include "esp_newlib.h"
#include "rtthread.h"

/* [refactor-todo] These includes are not directly used in this file. They are kept into to prevent a breaking change. Remove these. */
#include <limits.h>

/* [refactor-todo] introduce a port wrapper function to avoid including esp_timer.h into the public header */
#if CONFIG_FREERTOS_RUN_TIME_STATS_USING_ESP_TIMER
#include "esp_timer.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------- Port Types ------------------------------------------------------
 * - Port specific types.
 * - The settings in this file configure FreeRTOS correctly for the given hardware and compiler.
 * - These settings should not be altered.
 * - The port types must come first as they are used further down in this file
 * ------------------------------------------------------------------------------------------------------------------ */

#define portCHAR char
#define portFLOAT float
#define portDOUBLE double
#define portLONG long
#define portSHORT short
#define portSTACK_TYPE rt_ubase_t
#define portBASE_TYPE rt_base_t

typedef portSTACK_TYPE StackType_t;
typedef rt_base_t BaseType_t;
typedef rt_ubase_t UBaseType_t;
typedef rt_tick_t TickType_t;
#define portMAX_DELAY (TickType_t) RT_TICK_MAX

struct rt_semaphore_wrapper
{
    struct rt_semaphore sem;
    rt_uint16_t max_value;
};


/* ----------------------------------------------- Port Configurations -------------------------------------------------
 * - Configurations values supplied by each port
 * - Required by FreeRTOS
 * ------------------------------------------------------------------------------------------------------------------ */

#define portTICK_PERIOD_MS              ((TickType_t) (1000 / configTICK_RATE_HZ))
#define portBYTE_ALIGNMENT              RT_ALIGN_SIZE
#define portNOP() __asm volatile        (" nop ")


/* ---------------------------------------------- Forward Declarations -------------------------------------------------
 * - Forward declarations of all the port functions and macros need to implement the FreeRTOS porting interface
 * - These must come before definition/declaration of the FreeRTOS porting interface
 * ------------------------------------------------------------------------------------------------------------------ */

// --------------------- Interrupts ------------------------

/**
 * @brief Checks if the current core is in an ISR context
 *
 * - ISR context consist of Low/Mid priority ISR, or time tick ISR
 * - High priority ISRs aren't detected here, but they normally cannot call C code, so that should not be an issue anyway.
 *
 * @note [refactor-todo] Check if this should be inlined
 * @return
 *  - pdTRUE if in ISR
 *  - pdFALSE otherwise
 */
BaseType_t xPortInIsrContext(void);

/**
 * @brief Check if in ISR context from High priority ISRs
 *
 * - Called from High priority ISR
 * - Checks if the previous context (before high priority interrupt) was in ISR context (meaning low/med priority)
 *
 * @note [refactor-todo] Check if this should be inlined
 * @return
 *  - pdTRUE if in previous in ISR context
 *  - pdFALSE otherwise
 */
BaseType_t xPortInterruptedFromISRContext(void);

/* ---------------------- Spinlocks ------------------------
 - Spinlocks added to match API with SMP FreeRTOS. Single core RISC-V does not need spin locks
 - Because single core does not have a primitive spinlock data type, we have to implement one here
 * @note [refactor-todo] Refactor critical section API so that this is no longer required
 * ------------------------------------------------------ */

/**
 * @brief Spinlock object
 * Owner:
 *  - Set to 0 if uninitialized
 *  - Set to portMUX_FREE_VAL when free
 *  - Set to CORE_ID_REGVAL_PRO or CORE_ID_REGVAL_AP when locked
 *  - Any other value indicates corruption
 * Count:
 *  - 0 if unlocked
 *  - Recursive count if locked
 *
 * @note Not a true spinlock as single core RISC-V does not have atomic compare and set instruction
 * @note Keep portMUX_INITIALIZER_UNLOCKED in sync with this struct
 */
typedef struct {
    uint32_t owner;
    uint32_t count;
} portMUX_TYPE;
/**< Spinlock initializer */
#define portMUX_INITIALIZER_UNLOCKED {                      \
            .owner = portMUX_FREE_VAL,                      \
            .count = 0,                                     \
        }
#define portMUX_FREE_VAL                    SPINLOCK_FREE           /**< Spinlock is free. [refactor-todo] check if this is still required */
#define portMUX_NO_TIMEOUT                  SPINLOCK_WAIT_FOREVER   /**< When passed for 'timeout_cycles', spin forever if necessary. [refactor-todo] check if this is still required */
#define portMUX_TRY_LOCK                    SPINLOCK_NO_WAIT        /**< Try to acquire the spinlock a single time only. [refactor-todo] check if this is still required */
#define portMUX_INITIALIZE(mux)    ({ \
    (mux)->owner = portMUX_FREE_VAL; \
    (mux)->count = 0; \
})

// ------------------ Critical Sections --------------------

/**
 * @brief Enter a critical section
 *
 * - Simply disable interrupts
 * - Can be nested
 */
void vPortEnterCritical(void);

/**
 * @brief Exit a critical section
 *
 * - Reenables interrupts
 * - Can be nested
 */
void vPortExitCritical(void);

// ---------------------- Yielding -------------------------

/**
 * @brief Perform a context switch from a task
 *
 * @note [refactor-todo] The rest of ESP-IDF should call taskYield() instead
 */
#define vPortYield(void)    rt_thread_yield()

/**
 * @brief Checks if the current core can yield
 *
 * - A core cannot yield if its in an ISR or in a critical section
 *
 * @note [refactor-todo] See if this can be separated from port macro
 * @note [refactor-todo] Check if this function should be renamed (due to bool return type)
 * @return true Core can yield
 * @return false Core cannot yield
 */
FORCE_INLINE_ATTR bool xPortCanYield(void);

// ----------------------- System --------------------------

/**
 * @brief Get the tick rate per second
 *
 * @note [refactor-todo] make this inline
 * @note [refactor-todo] Check if this function should be renamed (due to uint return type)
 * @return uint32_t Tick rate in Hz
 */
uint32_t xPortGetTickRateHz(void);

/**
 * @brief Set a watchpoint to watch the last 32 bytes of the stack
 *
 * Callback to set a watchpoint on the end of the stack. Called every context switch to change the stack watchpoint
 * around.
 *
 * @param pxStackStart Pointer to the start of the stack
 */
void vPortSetStackWatchpoint(void *pxStackStart);

/**
 * @brief Get the current core's ID
 *
 * @note Added to be compatible with SMP API
 * @note [refactor-todo] IDF should call a FreeRTOS like macro instead of port function directly
 * @return BaseType_t Core ID
 */
FORCE_INLINE_ATTR BaseType_t xPortGetCoreID(void)
{
    return (BaseType_t) esp_cpu_get_core_id();
}



/* ------------------------------------------- FreeRTOS Porting Interface ----------------------------------------------
 * - Contains all the mappings of the macros required by FreeRTOS
 * - Most come after forward declare as porting macros map to declared functions
 * - Maps to forward declared functions
 * ------------------------------------------------------------------------------------------------------------------ */

// --------------------- Interrupts ------------------------

#define portDISABLE_INTERRUPTS()            vPortEnterCritical()
#define portENABLE_INTERRUPTS()             vPortExitCritical()
#define portSET_INTERRUPT_MASK_FROM_ISR()                       rt_hw_interrupt_disable()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(uxSavedStatusValue)   rt_hw_interrupt_enable(uxSavedStatusValue)

// ------------------ Critical Sections --------------------

#define portENTER_CRITICAL(mux)                 {(void)mux;  vPortEnterCritical();}
#define portEXIT_CRITICAL(mux)                  {(void)mux;  vPortExitCritical();}
#define portTRY_ENTER_CRITICAL(mux, timeout)    ({  \
    (void)mux; (void)timeout;                       \
    vPortEnterCritical();                           \
    BaseType_t ret = pdPASS;                        \
    ret;                                            \
})
//In single-core RISC-V, we can use the same critical section API
#define portENTER_CRITICAL_ISR(mux)                 portENTER_CRITICAL(mux)
#define portEXIT_CRITICAL_ISR(mux)                  portEXIT_CRITICAL(mux)
#define portTRY_ENTER_CRITICAL_ISR(mux, timeout)    portTRY_ENTER_CRITICAL(mux, timeout)

/* [refactor-todo] on RISC-V, both ISR and non-ISR cases result in the same call. We can redefine this macro */
#define portENTER_CRITICAL_SAFE(mux)    ({  \
    if (xPortInIsrContext()) {              \
        portENTER_CRITICAL_ISR(mux);        \
    } else {                                \
        portENTER_CRITICAL(mux);            \
    }                                       \
})
#define portEXIT_CRITICAL_SAFE(mux)     ({  \
    if (xPortInIsrContext()) {              \
        portEXIT_CRITICAL_ISR(mux);         \
    } else {                                \
        portEXIT_CRITICAL(mux);             \
    }                                       \
})
#define portTRY_ENTER_CRITICAL_SAFE(mux, timeout)   portENTER_CRITICAL_SAFE(mux, timeout)

// ---------------------- Yielding -------------------------

#define portYIELD() rt_thread_yield()
#define portYIELD_FROM_ISR_NO_ARG() rt_thread_yield()
#define portYIELD_FROM_ISR_ARG(xHigherPriorityTaskWoken) ({ \
    if (xHigherPriorityTaskWoken == pdTRUE) { \
        rt_thread_yield(); \
    } \
})
/**
 * @note    The macro below could be used when passing a single argument, or without any argument,
 *          it was developed to support both usages of portYIELD inside of an ISR. Any other usage form
 *          might result in undesired behavior
 */
#if defined(__cplusplus) && (__cplusplus >  201703L)
#define portYIELD_FROM_ISR(...) CHOOSE_MACRO_VA_ARG(portYIELD_FROM_ISR_ARG, portYIELD_FROM_ISR_NO_ARG __VA_OPT__(,) __VA_ARGS__)(__VA_ARGS__)
#else
#define portYIELD_FROM_ISR(...) CHOOSE_MACRO_VA_ARG(portYIELD_FROM_ISR_ARG, portYIELD_FROM_ISR_NO_ARG, ##__VA_ARGS__)(__VA_ARGS__)
#endif



/* --------------------------------------------- Inline Implementations ------------------------------------------------
 * - Implementation of inline functions of the forward declares
 * - Should come after forward declare and FreeRTOS Porting interface, as implementation may use both.
 * - For implementation of non-inlined functions, see port.c, port_common.c, or other assembly files
 * ------------------------------------------------------------------------------------------------------------------ */

// --------------------- Interrupts ------------------------

// ---------------------- Yielding -------------------------

FORCE_INLINE_ATTR bool xPortCanYield(void)
{
    rt_base_t level = rt_interrupt_get_nest();
    return (level == 0);
}

#define FREERTOS_PRIORITY_TO_RTTHREAD(priority)    ( configMAX_PRIORITIES - 1 - ( priority ) )
#define RTTHREAD_PRIORITY_TO_FREERTOS(priority)    ( RT_THREAD_PRIORITY_MAX - 1 - ( priority ) )
/* Use this macro to calculate the buffer size when allocating a queue statically
 * To ensure the buffer can fit the desired number of messages
 */
#define QUEUE_BUFFER_SIZE( uxQueueLength, uxItemSize )  ( ( RT_ALIGN( uxItemSize, RT_ALIGN_SIZE ) + sizeof( void * ) ) * uxQueueLength )

BaseType_t rt_err_to_freertos(rt_err_t rt_err);

#if CONFIG_APPTRACE_SV_ENABLE
extern int xPortSwitchFlag;
#define os_task_switch_is_pended(_cpu_) (xPortSwitchFlag)
#else
#define os_task_switch_is_pended(_cpu_) (false)
#endif

#ifdef __cplusplus
}
#endif

#endif //__ASSEMBLER__

#endif /* PORTMACRO_H */
