/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_MONO_H
#define HPM_MONO_H

typedef struct {
    __RW uint32_t MONOL;                       /* 0x0: Low part of monotonic counter */
    __RW uint32_t MONOH;                       /* 0x4: High part of monotonic counter */
} MONO_Type;


/* Bitfield definition for register: MONO */
/*
 * COUNTER (RW)
 *
 * 32 bits of  monotonica counter, write to this counter will cause counter increase by 1
 */
#define MONO_COUNTER_MASK (0xFFFFFFFFUL)
#define MONO_COUNTER_SHIFT (0U)
#define MONO_COUNTER_SET(x) (((uint32_t)(x) << MONO_COUNTER_SHIFT) & MONO_COUNTER_MASK)
#define MONO_COUNTER_GET(x) (((uint32_t)(x) & MONO_COUNTER_MASK) >> MONO_COUNTER_SHIFT)


#endif /* HPM_MONO_H */
