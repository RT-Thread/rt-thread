/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_RNG_DRV_H
#define HPM_RNG_DRV_H
#include "hpm_common.h"
#include "hpm_rng_regs.h"

enum {
    status_rng_busy = MAKE_STATUS(status_group_rng, 1),
    status_rng_selftest_failed = MAKE_STATUS(status_group_rng, 2),
    status_rng_not_available = MAKE_STATUS(status_group_rng, 3),
};

#ifdef __cplusplus
extern "C" {
#endif

hpm_stat_t rng_init(RNG_Type *ptr);

hpm_stat_t rng_rand_wait(RNG_Type *ptr, void *buf, uint32_t count_in_byte);

hpm_stat_t rng_rand_no_wait(RNG_Type *ptr, void *buf, uint32_t count_in_byte);

hpm_stat_t rng_feed_rand_to_sdp(RNG_Type *ptr);

hpm_stat_t rng_run_selftest(RNG_Type *ptr);

static inline void rng_sw_reset(RNG_Type *ptr)
{
    ptr->CMD |= RNG_CMD_SFTRST_MASK;
}

static inline void rng_clear_interrupt_error(RNG_Type *ptr)
{
    ptr->CMD |= RNG_CMD_CLRERR_MASK;
}

static inline void rng_clear_interrupt(RNG_Type *ptr)
{
    ptr->CMD |= RNG_CMD_CLRINT_MASK;
}

static inline bool rng_is_busy(RNG_Type *ptr)
{
    return ((ptr->STA & RNG_STA_BUSY_MASK) == RNG_STA_BUSY_MASK) ? true : false;
}

static inline bool rng_need_reseed(RNG_Type *ptr)
{
    return ((ptr->STA & RNG_STA_RSDREQ_MASK) == RNG_STA_RSDREQ_MASK) ? true : false;
}

#ifdef __cplusplus
}
#endif
#endif /* HPM_RNG_DRV_H */

