/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/sem.h"
#include "pico/time.h"

void sem_init(semaphore_t *sem, int16_t initial_permits, int16_t max_permits) {
    lock_init(&sem->core, next_striped_spin_lock_num());
    sem->permits = initial_permits;
    sem->max_permits = max_permits;
    __mem_fence_release();
}

int __time_critical_func(sem_available)(semaphore_t *sem) {
    return *(volatile typeof(sem->permits) *) &sem->permits;
}

void __time_critical_func(sem_acquire_blocking)(semaphore_t *sem) {
    bool block = true;
    do {
        uint32_t save = spin_lock_blocking(sem->core.spin_lock);
        if (sem->permits > 0) {
            sem->permits--;
            __sev();
            block = false;
        }
        spin_unlock(sem->core.spin_lock, save);
        if (block) {
            __wfe();
        }
    } while (block);
}

bool __time_critical_func(sem_acquire_timeout_ms)(semaphore_t *sem, uint32_t timeout_ms) {
    bool block = true;
    absolute_time_t target = nil_time;
    do {
        uint32_t save = spin_lock_blocking(sem->core.spin_lock);
        if (sem->permits > 0) {
            sem->permits--;
            __sev();
            block = false;
        }
        spin_unlock(sem->core.spin_lock, save);
        if (block) {
            if (is_nil_time(target)) {
                target = make_timeout_time_ms(timeout_ms);
            }
            if (best_effort_wfe_or_timeout(target)) {
                return false;
            }
        }
    } while (block);
    return true;
}

// todo this should really have a blocking variant for when permits are maxed out
bool __time_critical_func(sem_release)(semaphore_t *sem) {
    bool rc;
    uint32_t save = spin_lock_blocking(sem->core.spin_lock);
    int32_t count = sem->permits;
    if (count < sem->max_permits) {
        sem->permits = count + 1;
        __sev();
        rc = true;
    } else {
        rc = false;
    }
    spin_unlock(sem->core.spin_lock, save);
    return rc;
}

void __time_critical_func(sem_reset)(semaphore_t *sem, int16_t permits) {
    assert(permits >= 0 && permits <= sem->max_permits);
    uint32_t save = spin_lock_blocking(sem->core.spin_lock);
    if (permits > sem->permits) __sev();
    sem->permits = permits;
    spin_unlock(sem->core.spin_lock, save);
}
