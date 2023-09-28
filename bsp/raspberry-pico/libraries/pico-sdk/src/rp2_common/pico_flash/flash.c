/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/flash.h"
#include "hardware/exception.h"
#include "hardware/sync.h"
#if PICO_FLASH_SAFE_EXECUTE_PICO_SUPPORT_MULTICORE_LOCKOUT
#include "pico/multicore.h"
#endif
#if PICO_FLASH_SAFE_EXECUTE_SUPPORT_FREERTOS_SMP
#include "FreeRTOS.h"
#include "task.h"
// now we have FreeRTOS header we can check core count... we can only use FreeRTOS SMP mechanism
// with two cores
#if configNUM_CORES == 2
#if configUSE_CORE_AFFINITY
#define PICO_FLASH_SAFE_EXECUTE_USE_FREERTOS_SMP 1
#else
#error configUSE_CORE_AFFINITY is required for PICO_FLASH_SAFE_EXECUTE_SUPPORT_FREERTOS_SMP
#endif
#endif
#endif

// There are multiple scenarios:
//
// 1. No use of core 1 - we just want to disable IRQs and not wait on core 1 to acquiesce
// 2. Regular pico_multicore - we need to use multicore lockout.
// 3. FreeRTOS on core 0, no use of core 1 - we just want to disable IRQs
// 4. FreeRTOS SMP on both cores - we need to schedule a high priority task on the other core to disable IRQs.
// 5. FreeRTOS on one core, but application is using the other core. ** WE CANNOT SUPPORT THIS TODAY ** without
//    the equivalent PICO_FLASH_ASSUME_COREx_SAFE (i.e. the user mkaing sure the other core is fine)

static bool default_core_init_deinit(bool init);
static int default_enter_safe_zone_timeout_ms(uint32_t timeout_ms);
static int default_exit_safe_zone_timeout_ms(uint32_t timeout_ms);

// note the default methods are combined, rather than having a separate helper for
// FreeRTOS, as we may support mixed multicore and non SMP FreeRTOS in the future

static flash_safety_helper_t default_flash_safety_helper = {
        .core_init_deinit = default_core_init_deinit,
        .enter_safe_zone_timeout_ms = default_enter_safe_zone_timeout_ms,
        .exit_safe_zone_timeout_ms = default_exit_safe_zone_timeout_ms
};

#if PICO_FLASH_SAFE_EXECUTE_USE_FREERTOS_SMP
enum {
    FREERTOS_LOCKOUT_NONE = 0,
    FREERTOS_LOCKOUT_LOCKER_WAITING,
    FREERTOS_LOCKOUT_LOCKEE_READY,
    FREERTOS_LOCKOUT_LOCKER_DONE,
    FREERTOS_LOCKOUT_LOCKEE_DONE,
};
// state for the lockout operation launched from the corresponding core
static volatile uint8_t lockout_state[NUM_CORES];
#endif

__attribute__((weak)) flash_safety_helper_t *get_flash_safety_helper(void) {
    return &default_flash_safety_helper;
}

bool flash_safe_execute_core_init(void) {
    flash_safety_helper_t *helper = get_flash_safety_helper();
    return helper ? helper->core_init_deinit(true) : false;
}

bool flash_safe_execute_core_deinit(void) {
    flash_safety_helper_t *helper = get_flash_safety_helper();
    return helper ? helper->core_init_deinit(false) : false;
}

int flash_safe_execute(void (*func)(void *), void *param, uint32_t enter_exit_timeout_ms) {
    flash_safety_helper_t *helper = get_flash_safety_helper();
    if (!helper) return PICO_ERROR_NOT_PERMITTED;
    int rc = helper->enter_safe_zone_timeout_ms(enter_exit_timeout_ms);
    if (!rc) {
        func(param);
        rc = helper->exit_safe_zone_timeout_ms(enter_exit_timeout_ms);
    }
    return rc;
}

static bool default_core_init_deinit(__unused bool init) {
#if PICO_FLASH_ASSUME_CORE0_SAFE
    if (!get_core_num()) return true;
#endif
#if PICO_FLASH_ASSUME_CORE1_SAFE
    if (get_core_num()) return true;
#endif
#if PICO_FLASH_SAFE_EXECUTE_USE_FREERTOS_SMP
    return true;
#endif
#if PICO_FLASH_SAFE_EXECUTE_PICO_SUPPORT_MULTICORE_LOCKOUT
    if (!init) {
        return false;
    }
    multicore_lockout_victim_init();
#endif
    return true;
}

// irq_state for the lockout operation launched from the corresponding core
static uint32_t irq_state[NUM_CORES];

static bool use_irq_only(void) {
#if PICO_FLASH_ASSUME_CORE0_SAFE
    if (get_core_num()) return true;
#endif
#if PICO_FLASH_ASSUME_CORE1_SAFE
    if (!get_core_num()) return true;
#endif
    return false;
}

#if PICO_FLASH_SAFE_EXECUTE_USE_FREERTOS_SMP
static void __not_in_flash_func(flash_lockout_task)(__unused void *vother_core_num) {
    uint other_core_num = (uintptr_t)vother_core_num;
    while (lockout_state[other_core_num] != FREERTOS_LOCKOUT_LOCKER_WAITING) {
        __wfe(); // we don't bother to try to let lower priority tasks run
    }
    uint32_t save = save_and_disable_interrupts();
    lockout_state[other_core_num] = FREERTOS_LOCKOUT_LOCKEE_READY;
    __sev();
    while (lockout_state[other_core_num] == FREERTOS_LOCKOUT_LOCKEE_READY) {
        __wfe(); // we don't bother to try to let lower priority tasks run
    }
    restore_interrupts(save);
    lockout_state[other_core_num] = FREERTOS_LOCKOUT_LOCKEE_DONE;
    __sev();
    // bye bye
    vTaskDelete(NULL);
}
#endif

static int default_enter_safe_zone_timeout_ms(__unused uint32_t timeout_ms) {
    int rc = PICO_OK;
    if (!use_irq_only()) {
#if PICO_FLASH_SAFE_EXECUTE_USE_FREERTOS_SMP
        // Note that whilst taskENTER_CRITICAL sounds promising (and on non SMP it disabled IRQs), on SMP
        // it only prevents the other core from also entering a critical section.
        // Therefore, we must do our own handshake which starts a task on the other core and have it disable interrupts
        uint core_num = get_core_num();
        // create at low priority
        TaskHandle_t task_handle;
        if (pdPASS != xTaskCreate(flash_lockout_task, "flash lockout", configMINIMAL_STACK_SIZE, (void *)core_num, 0, &task_handle)) {
            return PICO_ERROR_INSUFFICIENT_RESOURCES;
        }
        lockout_state[core_num] = FREERTOS_LOCKOUT_LOCKER_WAITING;
        __sev();
        // bind to other core
        vTaskCoreAffinitySet(task_handle, 1u << (core_num ^ 1));
        // and make it super high priority
        vTaskPrioritySet(task_handle, configMAX_PRIORITIES -1);
        absolute_time_t until = make_timeout_time_ms(timeout_ms);
        while (lockout_state[core_num] != FREERTOS_LOCKOUT_LOCKEE_READY && !time_reached(until)) {
            __wfe(); // we don't bother to try to let lower priority tasks run
        }
        if (lockout_state[core_num] != FREERTOS_LOCKOUT_LOCKEE_READY) {
            lockout_state[core_num] = FREERTOS_LOCKOUT_LOCKER_DONE;
            rc = PICO_ERROR_TIMEOUT;
        }
        // todo we may get preempted here, but I think that is OK unless what is pre-empts requires
        //      the other core to be running.
#elif PICO_FLASH_SAFE_EXECUTE_PICO_SUPPORT_MULTICORE_LOCKOUT
        // we cannot mix multicore_lockout and FreeRTOS as they both use the multicore FIFO...
        // the user, will have to roll their own mechanism in this case.
#if LIB_FREERTOS_KERNEL
#if PICO_FLASH_ASSERT_ON_UNSAFE
        assert(false); // we expect the other core to have been initialized via flash_safe_execute_core_init()
                       // unless PICO_FLASH_ASSUME_COREX_SAFE is set
#endif
        rc = PICO_ERROR_NOT_PERMITTED;
#else // !LIB_FREERTOS_KERNEL
        if (multicore_lockout_victim_is_initialized(get_core_num()^1)) {
            if (!multicore_lockout_start_timeout_us(timeout_ms * 1000ull)) {
                rc = PICO_ERROR_TIMEOUT;
            }
        } else {
#if PICO_FLASH_ASSERT_ON_UNSAFE
            assert(false); // we expect the other core to have been initialized via flash_safe_execute_core_init()
                           // unless PICO_FLASH_ASSUME_COREX_SAFE is set
#endif
            rc = PICO_ERROR_NOT_PERMITTED;
        }
#endif // !LIB_FREERTOS_KERNEL
#else
        // no support for making other core safe provided, so fall through to irq
        // note this is the case for a regular single core program
#endif
    }
    if (rc == PICO_OK) {
        // we always want to disable IRQs on our core
        irq_state[get_core_num()] = save_and_disable_interrupts();
    }
    return rc;
}

static int default_exit_safe_zone_timeout_ms(__unused uint32_t timeout_ms) {
    // assume if we're exiting we're called then entry happened successfully
    restore_interrupts(irq_state[get_core_num()]);
    if (!use_irq_only()) {
#if PICO_FLASH_SAFE_EXECUTE_USE_FREERTOS_SMP
        uint core_num = get_core_num();
        lockout_state[core_num] = FREERTOS_LOCKOUT_LOCKER_DONE;
        __sev();
        absolute_time_t until = make_timeout_time_ms(timeout_ms);
        while (lockout_state[core_num] != FREERTOS_LOCKOUT_LOCKEE_DONE && !time_reached(until)) {
            __wfe(); // we don't bother to try to let lower priority tasks run
        }
        if (lockout_state[core_num] != FREERTOS_LOCKOUT_LOCKEE_DONE) {
            return PICO_ERROR_TIMEOUT;
        }
#elif PICO_FLASH_SAFE_EXECUTE_PICO_SUPPORT_MULTICORE_LOCKOUT
        return multicore_lockout_end_timeout_us(timeout_ms * 1000ull) ? PICO_OK : PICO_ERROR_TIMEOUT;
#endif
    }
    return PICO_OK;
}