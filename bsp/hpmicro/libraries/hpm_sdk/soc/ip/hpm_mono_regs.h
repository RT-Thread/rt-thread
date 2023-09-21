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


/* Bitfield definition for register: MONOL */
/*
 * COUNTER (RW)
 *
 * low part of monotonica counter, write to this counter will cause counter increase by 1
 */
#define MONO_MONOL_COUNTER_MASK (0xFFFFFFFFUL)
#define MONO_MONOL_COUNTER_SHIFT (0U)
#define MONO_MONOL_COUNTER_SET(x) (((uint32_t)(x) << MONO_MONOL_COUNTER_SHIFT) & MONO_MONOL_COUNTER_MASK)
#define MONO_MONOL_COUNTER_GET(x) (((uint32_t)(x) & MONO_MONOL_COUNTER_MASK) >> MONO_MONOL_COUNTER_SHIFT)

/* Bitfield definition for register: MONOH */
/*
 * EPOCH (RW)
 *
 * Fuse value for high part of monotonica
 */
#define MONO_MONOH_EPOCH_MASK (0xFFFF0000UL)
#define MONO_MONOH_EPOCH_SHIFT (16U)
#define MONO_MONOH_EPOCH_SET(x) (((uint32_t)(x) << MONO_MONOH_EPOCH_SHIFT) & MONO_MONOH_EPOCH_MASK)
#define MONO_MONOH_EPOCH_GET(x) (((uint32_t)(x) & MONO_MONOH_EPOCH_MASK) >> MONO_MONOH_EPOCH_SHIFT)

/*
 * COUNTER (RW)
 *
 * high part of monotonica counter, write to this counter will cause counter increase by 1 if low part overflow
 */
#define MONO_MONOH_COUNTER_MASK (0xFFFFU)
#define MONO_MONOH_COUNTER_SHIFT (0U)
#define MONO_MONOH_COUNTER_SET(x) (((uint32_t)(x) << MONO_MONOH_COUNTER_SHIFT) & MONO_MONOH_COUNTER_MASK)
#define MONO_MONOH_COUNTER_GET(x) (((uint32_t)(x) & MONO_MONOH_COUNTER_MASK) >> MONO_MONOH_COUNTER_SHIFT)




#endif /* HPM_MONO_H */
