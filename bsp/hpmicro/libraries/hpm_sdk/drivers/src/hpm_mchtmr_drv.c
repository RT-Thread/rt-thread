/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_mchtmr_drv.h"

void mchtmr_init_counter(MCHTMR_Type *ptr, uint64_t v)
{
    volatile uint32_t *p = (volatile uint32_t *) &ptr->MTIME;
    /*
     * When [31:29] == 7, low 32 bits need to be set to 0 first,
     * then set high 32 bits and low 32 bits; otherwise,
     * low 32 bit can be set firstly then high 32 bits.
     */
    if ((v & 0xE0000000) == 0xE0000000) {
        *p = 0;
        *(p + 1) = v >> 32;
        *p = v & 0xFFFFFFFF;
    } else {
        *p = v & 0xFFFFFFFF;
        *(p + 1) = v >> 32;
    }
}
