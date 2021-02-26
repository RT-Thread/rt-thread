/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/mutex.h"
#include "pico/time.h"

#if !PICO_NO_HARDWARE
static_assert(sizeof(mutex_t) == 8, "");
#endif

void mutex_init(mutex_t *mtx) {
    lock_init(&mtx->core, next_striped_spin_lock_num());
    __mem_fence_release();
}

void __time_critical_func(mutex_enter_blocking)(mutex_t *mtx) {
    assert(mtx->core.spin_lock);
    bool block = true;
    do {
        uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
        if (!mtx->owned) {
            mtx->owned = true;
            mtx->owner = get_core_num();
            block = false;
        }
        spin_unlock(mtx->core.spin_lock, save);
        if (block) {
            __wfe();
        }
    } while (block);
}

bool __time_critical_func(mutex_try_enter)(mutex_t *mtx, uint32_t *owner_out) {
    bool entered;
    uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
    if (!mtx->owned) {
        mtx->owned = true;
        mtx->owner = get_core_num();
        entered = true;
    } else {
        if (owner_out) *owner_out = mtx->owner;
        entered = false;
    }
    spin_unlock(mtx->core.spin_lock, save);
    return entered;
}

bool __time_critical_func(mutex_enter_timeout_ms)(mutex_t *mtx, uint32_t timeout_ms) {
    return mutex_enter_block_until(mtx, make_timeout_time_ms(timeout_ms));
}

bool __time_critical_func(mutex_enter_block_until)(mutex_t *mtx, absolute_time_t until) {
    assert(mtx->core.spin_lock);
    bool block = true;
    do {
        uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
        if (!mtx->owned) {
            mtx->owned = true;
            mtx->owner = get_core_num();
            block = false;
        }
        spin_unlock(mtx->core.spin_lock, save);
        if (block) {
            if (best_effort_wfe_or_timeout(until)) {
                return false;
            }
        }
    } while (block);
    return true;
}

void __time_critical_func(mutex_exit)(mutex_t *mtx) {
    uint32_t save = spin_lock_blocking(mtx->core.spin_lock);
    assert(mtx->owned);
    mtx->owned = 0;
#ifndef NDEBUG
    mtx->owner = -1;
#endif
    __sev();
    spin_unlock(mtx->core.spin_lock, save);
}
