/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/timer.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "hardware/claim.h"

check_hw_layout(timer_hw_t, ints, TIMER_INTS_OFFSET);

static hardware_alarm_callback_t alarm_callbacks[NUM_TIMERS];
static uint32_t target_hi[NUM_TIMERS];
static uint8_t timer_callbacks_pending;

static_assert(NUM_TIMERS <= 4, "");
static uint8_t claimed;

void hardware_alarm_claim(uint alarm_num) {
    check_hardware_alarm_num_param(alarm_num);
    hw_claim_or_assert(&claimed, alarm_num, "Hardware alarm %d already claimed");
}

void hardware_alarm_unclaim(uint alarm_num) {
    check_hardware_alarm_num_param(alarm_num);
    hw_claim_clear(&claimed, alarm_num);
}

/// tag::time_us_64[]
uint64_t time_us_64() {
    // Need to make sure that the upper 32 bits of the timer
    // don't change, so read that first
    uint32_t hi = timer_hw->timerawh;
    uint32_t lo;
    do {
        // Read the lower 32 bits
        lo = timer_hw->timerawl;
        // Now read the upper 32 bits again and
        // check that it hasn't incremented. If it has loop around
        // and read the lower 32 bits again to get an accurate value
        uint32_t next_hi = timer_hw->timerawh;
        if (hi == next_hi) break;
        hi = next_hi;
    } while (true);
    return ((uint64_t) hi << 32u) | lo;
}
/// end::time_us_64[]

/// \tag::busy_wait[]
void busy_wait_us_32(uint32_t delay_us) {
    if (0 <= (int32_t)delay_us) {
        // we only allow 31 bits, otherwise we could have a race in the loop below with
        // values very close to 2^32
        uint32_t start = timer_hw->timerawl;
        while (timer_hw->timerawl - start < delay_us) {
            tight_loop_contents();
        }
    } else {
        busy_wait_us(delay_us);
    }
}

void busy_wait_us(uint64_t delay_us) {
    uint64_t base = time_us_64();
    uint64_t target = base + delay_us;
    if (target < base) {
        target = (uint64_t)-1;
    }
    absolute_time_t t;
    update_us_since_boot(&t, target);
    busy_wait_until(t);
}

void busy_wait_until(absolute_time_t t) {
    uint64_t target = to_us_since_boot(t);
    uint32_t hi_target = target >> 32u;
    uint32_t hi = timer_hw->timerawh;
    while (hi < hi_target) {
        hi = timer_hw->timerawh;
        tight_loop_contents();
    }
    while (hi == hi_target && timer_hw->timerawl < (uint32_t) target) {
        hi = timer_hw->timerawh;
        tight_loop_contents();
    }
}
/// \end::busy_wait[]

static inline uint harware_alarm_irq_number(uint alarm_num) {
    return TIMER_IRQ_0 + alarm_num;
}

static void hardware_alarm_irq_handler() {
    // Determine which timer this IRQ is for
    uint32_t ipsr;
    __asm volatile ("mrs %0, ipsr" : "=r" (ipsr)::);
    uint alarm_num = (ipsr & 0x3fu) - 16 - TIMER_IRQ_0;
    check_hardware_alarm_num_param(alarm_num);

    hardware_alarm_callback_t callback = NULL;

    spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_TIMER);
    uint32_t save = spin_lock_blocking(lock);
    // Clear the timer IRQ (inside lock, because we check whether we have handled the IRQ yet in alarm_set by looking at the interrupt status
    timer_hw->intr = 1u << alarm_num;

    // make sure the IRQ is still valid
    if (timer_callbacks_pending & (1u << alarm_num)) {
        // Now check whether we have a timer event to handle that isn't already obsolete (this could happen if we
        // were already in the IRQ handler before someone else changed the timer setup
        if (timer_hw->timerawh >= target_hi[alarm_num]) {
            // we have reached the right high word as well as low word value
            callback = alarm_callbacks[alarm_num];
            timer_callbacks_pending &= ~(1u << alarm_num);
        } else {
            // try again in 2^32 us
            timer_hw->alarm[alarm_num] = timer_hw->alarm[alarm_num]; // re-arm the timer
        }
    }

    spin_unlock(lock, save);

    if (callback) {
        callback(alarm_num);
    }
}

void hardware_alarm_set_callback(uint alarm_num, hardware_alarm_callback_t callback) {
    // todo check current core owner
    //  note this should probably be subsumed by irq_set_exclusive_handler anyway, since that
    //  should disallow IRQ handlers on both cores
    check_hardware_alarm_num_param(alarm_num);
    uint irq_num = harware_alarm_irq_number(alarm_num);
    spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_TIMER);
    uint32_t save = spin_lock_blocking(lock);
    if (callback) {
        if (hardware_alarm_irq_handler != irq_get_vtable_handler(irq_num)) {
            // note that set_exclusive will silently allow you to set the handler to the same thing
            // since it is idempotent, which means we don't need to worry about locking ourselves
            irq_set_exclusive_handler(irq_num, hardware_alarm_irq_handler);
            irq_set_enabled(irq_num, true);
            // Enable interrupt in block and at processor
            hw_set_bits(&timer_hw->inte, 1u << alarm_num);
        }
        alarm_callbacks[alarm_num] = callback;
    } else {
        alarm_callbacks[alarm_num] = NULL;
        timer_callbacks_pending &= ~(1u << alarm_num);
        irq_remove_handler(irq_num, hardware_alarm_irq_handler);
        irq_set_enabled(irq_num, false);
    }
    spin_unlock(lock, save);
}

bool hardware_alarm_set_target(uint alarm_num, absolute_time_t target) {
    bool missed;
    uint64_t now = time_us_64();
    uint64_t t = to_us_since_boot(target);
    if (now >= t) {
        missed = true;
    } else {
        missed = false;

        // 1) actually set the hardware timer
        spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_TIMER);
        uint32_t save = spin_lock_blocking(lock);
        timer_hw->intr = 1u << alarm_num;
        timer_callbacks_pending |= 1u << alarm_num;
        timer_hw->alarm[alarm_num] = (uint32_t) t;
        // Set the alarm. Writing time should arm it
        target_hi[alarm_num] = t >> 32u;

        // 2) check for races
        if (!(timer_hw->armed & 1u << alarm_num)) {
            // not armed, so has already fired .. IRQ must be pending (we are still under lock)
            assert(timer_hw->ints & 1u << alarm_num);
        } else {
            if (time_us_64() >= t) {
                // ok well it is time now; the irq isn't being handled yet because of the spin lock
                // however the other core might be in the IRQ handler itself about to do a callback
                // we do the firing ourselves (and indicate to the IRQ handler if any that it shouldn't
                missed = true;
                // disarm the timer
                timer_hw->armed = 1u << alarm_num;
                timer_hw->intr = 1u << alarm_num; // clear the IRQ too
                // and set flag in case we're already in the IRQ handler waiting on the spinlock (on the other core)
                timer_callbacks_pending &= ~(1u << alarm_num);
            }
        }
        spin_unlock(lock, save);
    }
    return missed;
}

void hardware_alarm_cancel(uint alarm_num) {
    check_hardware_alarm_num_param(alarm_num);

    spin_lock_t *lock = spin_lock_instance(PICO_SPINLOCK_ID_TIMER);
    uint32_t save = spin_lock_blocking(lock);
    timer_hw->armed = 1u << alarm_num;
    timer_callbacks_pending &= ~(1u << alarm_num);
    spin_unlock(lock, save);
}


