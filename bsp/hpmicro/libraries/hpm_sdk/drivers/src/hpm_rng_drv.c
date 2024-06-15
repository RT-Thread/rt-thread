/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_rng_drv.h"

hpm_stat_t rng_run_selftest(RNG_Type *ptr)
{
    uint32_t status;

    ptr->CMD |= RNG_CMD_SLFCHK_MASK;
    do {
        status = ptr->STA;
    } while (!(status & (RNG_STA_FUNCERR_MASK | RNG_STA_SCDN_MASK)));

    if ((status & (RNG_STA_SCPF_MASK | RNG_STA_FUNCERR_MASK))) {
        return status;
    }

    return status_success;
}

hpm_stat_t rng_feed_rand_to_sdp(RNG_Type *ptr)
{
    uint32_t i = 0;
    uint32_t status;
    uint32_t fifo_level;
    hpm_stat_t stat = status_success;

    for (i = 0; i < ARRAY_SIZE(ptr->R2SK); i++) {
        status = ptr->STA;
        if (status & RNG_STA_FUNCERR_MASK) {
            stat = status_fail;
            break;
        }

        do {
            fifo_level = (ptr->STA & RNG_STA_FRNNU_MASK) >> RNG_STA_FRNNU_SHIFT;
        } while (!fifo_level);

        __asm volatile ("" : : "r" (ptr->R2SK[i]));
    }
    return stat;
}

static hpm_stat_t rng_rand(RNG_Type *ptr, void *buf, uint32_t count_in_byte, bool wait)
{
    uint32_t i;
    uint32_t status;
    volatile uint32_t fifo_level;
    hpm_stat_t stat = status_success;

    if (count_in_byte < 4) {
        return status_invalid_argument;
    }

    for (i = 0; i < (count_in_byte / 4); i++) {
        status = ptr->STA;
        if (status & RNG_STA_FUNCERR_MASK) {
            stat = status_fail;
            break;
        }

        do {
            fifo_level = (ptr->STA & RNG_STA_FRNNU_MASK) >> RNG_STA_FRNNU_SHIFT;
        } while (!fifo_level && wait);

        if (fifo_level) {
            *(uint32_t *)((uint32_t)buf + i * sizeof(uint32_t)) = ptr->FO2B;
        } else {
            stat = status_rng_not_available;
            break;
        }
    }

    return stat;
}

hpm_stat_t rng_rand_wait(RNG_Type *ptr, void *buf, uint32_t count_in_byte)
{
    return rng_rand(ptr, buf, count_in_byte, true);
}

hpm_stat_t rng_rand_no_wait(RNG_Type *ptr, void *buf, uint32_t count_in_byte)
{
    return rng_rand(ptr, buf, count_in_byte, false);
}

hpm_stat_t rng_init(RNG_Type *ptr)
{
    hpm_stat_t stat = status_success;

    /* clear interrupt and error */
    ptr->CMD |= RNG_CMD_CLRERR_MASK;

    /* generating seed */
    ptr->CMD |= RNG_CMD_GENSD_MASK;
    while (!(ptr->STA & RNG_STA_FSDDN_MASK)) {
        if (ptr->STA & RNG_STA_FUNCERR_MASK) {
            stat = status_fail;
            break;
        }
    }
    if (stat != status_success) {
        return stat;
    }

    /* enable auto seeding */
    ptr->CTRL |= RNG_CTRL_AUTRSD_MASK;

    return stat;
}

