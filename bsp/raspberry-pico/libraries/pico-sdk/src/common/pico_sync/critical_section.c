/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/critical_section.h"

#if !PICO_NO_HARDWARE
static_assert(sizeof(critical_section_t) == 8, "");
#endif

void critical_section_init(critical_section_t *critsec) {
    critical_section_init_with_lock_num(critsec, spin_lock_claim_unused(true));
}

void critical_section_init_with_lock_num(critical_section_t *critsec, uint lock_num) {
    lock_init(&critsec->core, lock_num);
    __mem_fence_release();
}

void critical_section_deinit(critical_section_t *critsec) {
    spin_lock_unclaim(spin_lock_get_num(critsec->core.spin_lock));
}