/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_MCHTMR_H
#define HPM_MCHTMR_H

typedef struct {
    __RW uint64_t MTIME;                       /* 0x0: Machine Time */
    __RW uint64_t MTIMECMP;                    /* 0x8: Machine Time Compare */
} MCHTMR_Type;


/* Bitfield definition for register: MTIME */
/*
 * MTIME (RW)
 *
 * Machine time
 */
#define MCHTMR_MTIME_MTIME_MASK (0xFFFFFFFFFFFFFFFFULL)
#define MCHTMR_MTIME_MTIME_SHIFT (0U)
#define MCHTMR_MTIME_MTIME_SET(x) (((uint64_t)(x) << MCHTMR_MTIME_MTIME_SHIFT) & MCHTMR_MTIME_MTIME_MASK)
#define MCHTMR_MTIME_MTIME_GET(x) (((uint64_t)(x) & MCHTMR_MTIME_MTIME_MASK) >> MCHTMR_MTIME_MTIME_SHIFT)

/* Bitfield definition for register: MTIMECMP */
/*
 * MTIMECMP (RW)
 *
 * Machine time compare
 */
#define MCHTMR_MTIMECMP_MTIMECMP_MASK (0xFFFFFFFFFFFFFFFFULL)
#define MCHTMR_MTIMECMP_MTIMECMP_SHIFT (0U)
#define MCHTMR_MTIMECMP_MTIMECMP_SET(x) (((uint64_t)(x) << MCHTMR_MTIMECMP_MTIMECMP_SHIFT) & MCHTMR_MTIMECMP_MTIMECMP_MASK)
#define MCHTMR_MTIMECMP_MTIMECMP_GET(x) (((uint64_t)(x) & MCHTMR_MTIMECMP_MTIMECMP_MASK) >> MCHTMR_MTIMECMP_MTIMECMP_SHIFT)




#endif /* HPM_MCHTMR_H */
