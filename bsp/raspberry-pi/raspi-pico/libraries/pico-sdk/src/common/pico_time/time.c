/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "pico.h"
#include "pico/time.h"
#include "pico/util/pheap.h"
#include "hardware/sync.h"
#include "hardware/gpio.h"

CU_REGISTER_DEBUG_PINS(core)
CU_SELECT_DEBUG_PINS(core)

const absolute_time_t ABSOLUTE_TIME_INITIALIZED_VAR(nil_time, 0);
// use LONG_MAX not ULONG_MAX so we don't have sign overflow in time diffs
const absolute_time_t ABSOLUTE_TIME_INITIALIZED_VAR(at_the_end_of_time, ULONG_MAX);

typedef struct alarm_pool_entry {
    absolute_time_t target;
    alarm_callback_t callback;
    void *user_data;
} alarm_pool_entry_t;

typedef struct alarm_pool {
    pheap_t *heap;
    spin_lock_t *lock;
    alarm_pool_entry_t *entries;
    // one byte per entry, used to provide more longevity to public IDs than heap node ids do
    // (this is increment every time the heap node id is re-used)
    uint8_t *entry_ids_high;
    alarm_id_t alarm_in_progress; // this is set during a callback from the IRQ handler... it can be cleared by alarm_cancel to prevent repeats
    uint8_t hardware_alarm_num;
} alarm_pool_t;

#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
static alarm_pool_t *default_alarm_pool;
#endif
static alarm_pool_t *pools[NUM_TIMERS];

void alarm_pool_init_default() {
#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
    // allow multiple calls for ease of use from host tests
    if (!default_alarm_pool) {
        default_alarm_pool = alarm_pool_create(PICO_TIME_DEFAULT_ALARM_POOL_HARDWARE_ALARM_NUM,
                                               PICO_TIME_DEFAULT_ALARM_POOL_MAX_TIMERS);
    }
#endif
}

#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
alarm_pool_t *alarm_pool_get_default() {
    assert(default_alarm_pool);
    return default_alarm_pool;
}
#endif

static inline alarm_pool_entry_t *get_entry(alarm_pool_t *pool, pheap_node_id_t id) {
    assert(id && id <= pool->heap->max_nodes);
    return pool->entries + id - 1;
}

static inline uint8_t *get_entry_id_high(alarm_pool_t *pool, pheap_node_id_t id) {
    assert(id && id <= pool->heap->max_nodes);
    return pool->entry_ids_high + id - 1;
}

bool timer_pool_entry_comparator(void *user_data, pheap_node_id_t a, pheap_node_id_t b) {
    alarm_pool_t *pool = (alarm_pool_t *)user_data;
    return to_us_since_boot(get_entry(pool, a)->target) < to_us_since_boot(get_entry(pool, b)->target);
}

static inline alarm_id_t make_public_id(uint8_t id_high, pheap_node_id_t id) {
    return ((uint)id_high << 8u * sizeof(id)) | id;
}

static alarm_id_t add_alarm_under_lock(alarm_pool_t *pool, absolute_time_t time, alarm_callback_t callback,
                                       void *user_data, alarm_id_t reuse_id, bool create_if_past, bool *missed) {
    alarm_id_t id;
    if (reuse_id) {
        assert(!ph_contains(pool->heap, reuse_id));
        id = reuse_id;
    } else {
        id = ph_new_node(pool->heap);
    }
    if (id) {
        alarm_pool_entry_t *entry = get_entry(pool, id);
        entry->target = time;
        entry->callback = callback;
        entry->user_data = user_data;
        DEBUG_PINS_SET(core, 1);
        if (id == ph_insert(pool->heap, id)) {
            bool is_missed = hardware_alarm_set_target(pool->hardware_alarm_num, time);
            if (is_missed && !create_if_past) {
                ph_delete(pool->heap, id);
            }
            if (missed) *missed = is_missed;
        }
    }
    return id;
}

static void alarm_pool_alarm_callback(uint alarm_num) {
    // note this is called from timer IRQ handler
    alarm_pool_t *pool = pools[alarm_num];
    bool again;
    do {
        absolute_time_t now = get_absolute_time();
        alarm_callback_t callback = NULL;
        absolute_time_t target = nil_time;
        void *user_data = NULL;
        uint8_t id_high;
        again = false;
        uint32_t save = spin_lock_blocking(pool->lock);
        pheap_node_id_t next_id = ph_peek_head(pool->heap);
        if (next_id) {
            alarm_pool_entry_t *entry = get_entry(pool, next_id);
            if (absolute_time_diff_us(now, entry->target) <= 0) {
                // we reserve the id in case we need to re-add the timer
                pheap_node_id_t __unused removed_id = ph_remove_head_reserve(pool->heap, true);
                assert(removed_id == next_id); // will be true under lock
                target = entry->target;
                callback = entry->callback;
                user_data = entry->user_data;
                assert(callback);
                id_high = *get_entry_id_high(pool, next_id);
                pool->alarm_in_progress = make_public_id(id_high, removed_id);
            } else {
                if (hardware_alarm_set_target(alarm_num, entry->target)) {
                    again = true;
                }
            }
        }
        spin_unlock(pool->lock, save);
        if (callback) {
            DEBUG_PINS_SET(core, 4);
            DEBUG_PINS_CLR(core, 1);
            DEBUG_PINS_CLR(core, 4);
            int64_t repeat = callback(make_public_id(id_high, next_id), user_data);
            save = spin_lock_blocking(pool->lock);
            // todo think more about whether we want to keep calling
            if (repeat < 0 && pool->alarm_in_progress) {
                assert(pool->alarm_in_progress == make_public_id(id_high, next_id));
                add_alarm_under_lock(pool, delayed_by_us(target, -repeat), callback, user_data, next_id, true, NULL);
            } else if (repeat > 0 && pool->alarm_in_progress) {
                assert(pool->alarm_in_progress == make_public_id(id_high, next_id));
                add_alarm_under_lock(pool, delayed_by_us(get_absolute_time(), repeat), callback, user_data, next_id,
                                     true, NULL);
            } else {
                // need to return the id to the heap
                ph_add_to_free_list(pool->heap, next_id);
                (*get_entry_id_high(pool, next_id))++; // we bump it for next use of id
            }
            pool->alarm_in_progress = 0;
            spin_unlock(pool->lock, save);
            again = true;
        }
    } while (again);
}

// note the timer is create with IRQs on this core
alarm_pool_t *alarm_pool_create(uint hardware_alarm_num, uint max_timers) {
    hardware_alarm_claim(hardware_alarm_num);
    hardware_alarm_cancel(hardware_alarm_num);
    hardware_alarm_set_callback(hardware_alarm_num, alarm_pool_alarm_callback);
    alarm_pool_t *pool = (alarm_pool_t *)malloc(sizeof(alarm_pool_t));
    pool->lock = spin_lock_instance(next_striped_spin_lock_num());
    pool->heap = ph_create(max_timers, timer_pool_entry_comparator, pool);
    pool->entries = (alarm_pool_entry_t *)calloc(max_timers, sizeof(alarm_pool_entry_t));
    pool->entry_ids_high = (uint8_t *)calloc(max_timers, sizeof(uint8_t));
    pool->hardware_alarm_num = hardware_alarm_num;
    pools[hardware_alarm_num] = pool;
    return pool;
}

void alarm_pool_destroy(alarm_pool_t *pool) {
    assert(pools[pool->hardware_alarm_num] == pool);
    pools[pool->hardware_alarm_num] = NULL;
    // todo clear out timers
    ph_destroy(pool->heap);
    hardware_alarm_set_callback(pool->hardware_alarm_num, NULL);
    hardware_alarm_unclaim(pool->hardware_alarm_num);
    free(pool->entry_ids_high);
    free(pool->entries);
    free(pool);
}

alarm_id_t alarm_pool_add_alarm_at(alarm_pool_t *pool, absolute_time_t time, alarm_callback_t callback,
                                   void *user_data, bool fire_if_past) {
    bool missed = false;

    uint public_id;
    do {
        uint8_t id_high = 0;
        uint32_t save = spin_lock_blocking(pool->lock);
        pheap_node_id_t id = add_alarm_under_lock(pool, time, callback, user_data, 0, false, &missed);
        if (id) id_high = *get_entry_id_high(pool, id);

        spin_unlock(pool->lock, save);

        if (!id) {
            return -1;
        }

        public_id = missed ? 0 : make_public_id(id_high, id);
        if (missed && fire_if_past) {
            int64_t repeat = callback(public_id, user_data);
            if (!repeat) {
                public_id = 0;
                break;
            } else if (repeat < 0) {
                time = delayed_by_us(time, -repeat);
            } else {
                time = delayed_by_us(get_absolute_time(), repeat);
            }
        } else {
            break;
        }
    } while (true);
    return public_id;
}

bool alarm_pool_cancel_alarm(alarm_pool_t *pool, alarm_id_t alarm_id) {
    bool rc = false;
    uint32_t save = spin_lock_blocking(pool->lock);
    pheap_node_id_t id = (pheap_node_id_t) alarm_id;
    if (ph_contains(pool->heap, id)) {
        assert(alarm_id != pool->alarm_in_progress); // it shouldn't be in the heap if it is in progress
        // check we have the right high value
        uint8_t id_high = (uint8_t)((uint)alarm_id >> 8u * sizeof(pheap_node_id_t));
        if (id_high == *get_entry_id_high(pool, id)) {
            rc = ph_delete(pool->heap, id);
            // note we don't bother to remove the actual hardware alarm timeout...
            // it will either do callbacks or not depending on other alarms, and reset the next timeout itself
            assert(rc);
        }
    } else {
        if (alarm_id == pool->alarm_in_progress) {
            // make sure the alarm doesn't repeat
            pool->alarm_in_progress = 0;
        }
    }
    spin_unlock(pool->lock, save);
    return rc;
}

uint alarm_pool_hardware_alarm_num(alarm_pool_t *pool) {
    return pool->hardware_alarm_num;
}

static void alarm_pool_dump_key(pheap_node_id_t id, void *user_data) {
    alarm_pool_t *pool = (alarm_pool_t *)user_data;
#if PICO_ON_DEVICE
    printf("%lld (hi %02x)", to_us_since_boot(get_entry(pool, id)->target), *get_entry_id_high(pool, id));
#else
    printf("%ld", to_us_since_boot(get_entry(pool, id)->target));
#endif
}

static int64_t repeating_timer_callback(alarm_id_t id, void *user_data) {
    repeating_timer_t *rt = (repeating_timer_t *)user_data;
    if (rt->callback(rt)) {
        return rt->delay_us;
    } else {
        rt->alarm_id = 0;
        return 0;
    }
}

bool alarm_pool_add_repeating_timer_us(alarm_pool_t *pool, int64_t delay_us, repeating_timer_callback_t callback, void *user_data, repeating_timer_t *out) {
    if (!delay_us) delay_us = 1;
    out->pool = pool;
    out->callback = callback;
    out->delay_us = delay_us;
    out->user_data = user_data;
    out->alarm_id = alarm_pool_add_alarm_at(pool, make_timeout_time_us(delay_us >= 0 ? delay_us : -delay_us), repeating_timer_callback, out, true);
    return out->alarm_id > 0;
}

bool cancel_repeating_timer(repeating_timer_t *timer) {
    bool rc = false;
    if (timer->alarm_id) {
        rc = alarm_pool_cancel_alarm(timer->pool, timer->alarm_id);
        timer->alarm_id = 0;
    }
    return rc;
}

void alarm_pool_dump(alarm_pool_t *pool) {
    uint32_t save = spin_lock_blocking(pool->lock);
    ph_dump(pool->heap, alarm_pool_dump_key, pool);
    spin_unlock(pool->lock, save);
}

#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
static int64_t sev_callback(alarm_id_t id, void *user_data) {
    __sev();
    return 0;
}
#endif

void sleep_until(absolute_time_t t) {
#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
    uint64_t t_us = to_us_since_boot(t);
    uint64_t t_before_us = t_us - PICO_TIME_SLEEP_OVERHEAD_ADJUST_US;
    // needs to work in the first PICO_TIME_SLEEP_OVERHEAD_ADJUST_US of boot
    if (t_before_us > t_us) t_before_us = 0;
    absolute_time_t t_before;
    update_us_since_boot(&t_before, t_before_us);
    if (absolute_time_diff_us(get_absolute_time(), t_before) > 0) {
        if (add_alarm_at(t_before, sev_callback, NULL, false) >= 0) {
            // able to add alarm for just before the time
            while (!time_reached(t_before)) {
                __wfe();
            }
        }
    }
#endif
    // now wait until the exact time
    busy_wait_until(t);
}

void sleep_us(uint64_t us) {
#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
    sleep_until(make_timeout_time_us(us));
#else
    if (us >> 32u) {
        busy_wait_until(make_timeout_time_us(us));
    } else {
        busy_wait_us_32(us);
    }
#endif

}

void sleep_ms(uint32_t ms) {
    sleep_us(ms * 1000ull);
}

bool best_effort_wfe_or_timeout(absolute_time_t timeout_timestamp) {
#if !PICO_TIME_DEFAULT_ALARM_POOL_DISABLED
    alarm_id_t id;
    id = add_alarm_at(timeout_timestamp, sev_callback, NULL, false);
    if (id <= 0) {
        tight_loop_contents();
        return time_reached(timeout_timestamp);
    } else {
        __wfe();
        // we need to clean up if it wasn't us that caused the wfe; if it was this will be a noop.
        cancel_alarm(id);
        return time_reached(timeout_timestamp);
    }
#else
    tight_loop_contents();
    return time_reached(timeout_timestamp);
#endif
}
