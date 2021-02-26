/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/claim.h"

uint32_t hw_claim_lock() {
    return spin_lock_blocking(spin_lock_instance(PICO_SPINLOCK_ID_HARDWARE_CLAIM));
}

void hw_claim_unlock(uint32_t save) {
    spin_unlock(spin_lock_instance(PICO_SPINLOCK_ID_HARDWARE_CLAIM), save);
}

bool hw_is_claimed(uint8_t *bits, uint bit_index) {
    bool rc;
    uint32_t save = hw_claim_lock();
    if (bits[bit_index >> 3u] & (1u << (bit_index & 7u))) {
        rc = false;
    } else {
        bits[bit_index >> 3u] |= (1u << (bit_index & 7u));
        rc = true;
    }
    hw_claim_unlock(save);
    return rc;
}

void hw_claim_or_assert(uint8_t *bits, uint bit_index, const char *message) {
    uint32_t save = hw_claim_lock();
    if (bits[bit_index >> 3u] & (1u << (bit_index & 7u))) {
        panic(message, bit_index);
    } else {
        bits[bit_index >> 3u] |= (1u << (bit_index & 7u));
    }
    hw_claim_unlock(save);
}

int hw_claim_unused_from_range(uint8_t *bits, bool required, uint bit_lsb, uint bit_msb, const char *message) {
    // don't bother check lsb / msb order as if wrong, then it'll fail anyway
    uint32_t save = hw_claim_lock();
    int found_bit = -1;
    for(uint bit=bit_lsb; bit <= bit_msb; bit++) {
        if (!(bits[bit >> 3u] & (1u << (bit & 7u)))) {
            bits[bit >> 3u] |= (1u << (bit & 7u));
            found_bit = bit;
            break;
        }
    }
    hw_claim_unlock(save);
    if (found_bit < 0 && required) {
        panic(message);
    }
    return found_bit;
}

void hw_claim_clear(uint8_t *bits, uint bit_index) {
    uint32_t save = hw_claim_lock();
    assert(bits[bit_index >> 3u] & (1u << (bit_index & 7u)));
    bits[bit_index >> 3u] &= ~(1u << (bit_index & 7u));
    hw_claim_unlock(save);
}


