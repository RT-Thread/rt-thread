/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_FLASH_H
#define _PICO_FLASH_H

#include "pico.h"

#include "hardware/flash.h"
#include "pico/time.h"

/** \file pico/flash.h
 *  \defgroup pico_flash pico_flash
 *
 * High level flash API
 *
 * Flash cannot be erased or written to when in XIP mode. However the system cannot directly access memory in the flash
 * address space when not in XIP mode.
 *
 * It is therefore critical that no code or data is being read from flash while flash is been written or erased.
 *
 * If only one core is being used, then the problem is simple - just disable interrupts; however if code is running on
 * the other core, then it has to be asked, nicely, to avoid flash for a bit. This is hard to do if you don't have
 * complete control of the code running on that core at all times.
 *
 * This library provides a \ref flash_safe_execute method which calls a function back having sucessfully gotten
 * into a state where interrupts are disabled, and the other core is not executing or reading from flash.
 *
 * How it does this is dependent on the supported environment (Free RTOS SMP or pico_multicore). Additionally
 * the user can provide their own mechanism by providing a strong definition of \ref get_flash_safety_helper().
 *
 * Using the default settings, flash_safe_execute will only call the callback function if the state is safe
 * otherwise returning an error (or an assert depending on \ref PICO_FLASH_ASSERT_ON_UNSAFE).
 *
 * There are conditions where safety would not be guaranteed:
 *
 * 1. FreeRTOS smp with `configNUM_CORES=1` - FreeRTOS still uses pico_multicore in this case, so \ref flash_safe_execute
 * cannot know what the other core is doing, and there is no way to force code execution between a FreeRTOS core
 * and a non FreeRTOS core.
 * 2. FreeRTOS non SMP with pico_multicore - Again, there is no way to force code execution between a FreeRTOS core and
 * a non FreeRTOS core.
 * 3. pico_multicore without \ref flash_safe_execute_core_init() having been called on the other core - The
 * \ref flash_safe_execute method does not know if code is executing on the other core, so it has to assume it is. Either
 * way, it is not able to intervene if \ref flash_safe_execute_core_init() has not been called on the other core.
 *
 * Fortunately, all is not lost in this situation, you may:
 *
 * * Set \ref PICO_FLASH_ASSUME_CORE0_SAFE=1 to explicitly say that core 0 is never using flash.
 * * Set \ref PICO_FLASH_ASSUME_CORE1_SAFE=1 to explicitly say that core 1 is never using flash.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize a core such that the other core can lock it out during \ref flash_safe_execute.
 * \ingroup pico_flash
 *
 * \note This is not necessary for FreeRTOS SMP, but should be used when launching via \ref multicore_launch_core1
 * \return true on success; there is no need to call \ref flash_safe_execute_core_deinit() on failure.
 */
bool flash_safe_execute_core_init(void);

/**
 * De-initialize work done by \ref flash_safe_execute_core_init
 * \ingroup pico_flash
 * \return true on success
 */
bool flash_safe_execute_core_deinit(void);

/**
 * Execute a function with IRQs disabled and with the other core also not executing/reading flash
 * \ingroup pico_flash
 *
 * \param func the function to call
 * \param param the parameter to pass to the function
 * \param enter_exit_timeout_ms the timeout for each of the enter/exit phases when coordinating with the other core
 *
 * \return PICO_OK on success (the function will have been called).
 *         PICO_TIMEOUT on timeout (the function may have been called).
 *         PICO_ERROR_NOT_PERMITTED if safe execution is not possible (the function will not have been called).
 *         PICO_ERROR_INSUFFICIENT_RESOURCES if the method fails due to dynamic resource exhaustion (the function will not have been called)
 * \note if \ref PICO_FLASH_ASSERT_ON_UNSAFE is 1, this function will assert in debug mode vs returning
 *       PICO_ERROR_NOT_PERMITTED
 */
int flash_safe_execute(void (*func)(void *), void *param, uint32_t enter_exit_timeout_ms);

// PICO_CONFIG: PICO_FLASH_ASSERT_ON_UNSAFE, Assert in debug mode rather than returning an error if flash_safe_execute cannot guarantee safety to catch bugs early, type=bool, default=1, group=pico_flash
#ifndef PICO_FLASH_ASSERT_ON_UNSAFE
#define PICO_FLASH_ASSERT_ON_UNSAFE 1
#endif

// PICO_CONFIG: PICO_FLASH_ASSUME_CORE0_SAFE, Assume that core 0 will never be accessing flash and so doesn't need to be considered during flash_safe_execute, type=bool, default=0, group=pico_flash
#ifndef PICO_FLASH_ASSUME_CORE0_SAFE
#define PICO_FLASH_ASSUME_CORE0_SAFE 0
#endif

// PICO_CONFIG: PICO_FLASH_ASSUME_CORE1_SAFE, Assume that core 1 will never be accessing flash and so doesn't need to be considered during flash_safe_execute, type=bool, default=0, group=pico_flash
#ifndef PICO_FLASH_ASSUME_CORE1_SAFE
#define PICO_FLASH_ASSUME_CORE1_SAFE 0
#endif

// PICO_CONFIG: PICO_FLASH_SAFE_EXECUTE_SUPPORT_FREERTOS_SMP, Support using FreeRTOS SMP to make the other core safe during flash_safe_execute, type=bool, default=1 when using FreeRTOS SMP, group=pico_flash
#ifndef PICO_FLASH_SAFE_EXECUTE_SUPPORT_FREERTOS_SMP
#if LIB_FREERTOS_KERNEL && FREE_RTOS_KERNEL_SMP // set by RP2040 SMP port
#define PICO_FLASH_SAFE_EXECUTE_SUPPORT_FREERTOS_SMP 1
#endif
#endif

// PICO_CONFIG: PICO_FLASH_SAFE_EXECUTE_PICO_SUPPORT_MULTICORE_LOCKOUT, Support using multicore_lockout functions to make the other core safe during flash_safe_execute, type=bool, default=1 when using pico_multicore, group=pico_flash
#ifndef PICO_FLASH_SAFE_EXECUTE_PICO_SUPPORT_MULTICORE_LOCKOUT
#if LIB_PICO_MULTICORE
#define PICO_FLASH_SAFE_EXECUTE_PICO_SUPPORT_MULTICORE_LOCKOUT 1
#endif
#endif

typedef struct {
    bool (*core_init_deinit)(bool init);
    int (*enter_safe_zone_timeout_ms)(uint32_t timeout_ms);
    int (*exit_safe_zone_timeout_ms)(uint32_t timeout_ms);
} flash_safety_helper_t;

/**
 * Internal method to return the flash safety helper implementation.
 * \ingroup pico_flash
 *
 * Advanced users can provide their own implementation of this function to perform
 * different inter-core coordination before disabling XIP mode.
 *
 * @return the \ref flash_safety_helper_t
 */
flash_safety_helper_t *get_flash_safety_helper(void);

#ifdef __cplusplus
}
#endif

#endif
