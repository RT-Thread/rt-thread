/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_BGPR_H
#define HPM_BGPR_H

typedef struct {
    __RW uint32_t GPR[16];                     /* 0x0 - 0x3C: Generic control */
} BGPR_Type;


/* Bitfield definition for register array: GPR */
/*
 * DATA (RW)
 *
 * Generic control
 */
#define BGPR_GPR_DATA_MASK (0xFFFFFFFFUL)
#define BGPR_GPR_DATA_SHIFT (0U)
#define BGPR_GPR_DATA_SET(x) (((uint32_t)(x) << BGPR_GPR_DATA_SHIFT) & BGPR_GPR_DATA_MASK)
#define BGPR_GPR_DATA_GET(x) (((uint32_t)(x) & BGPR_GPR_DATA_MASK) >> BGPR_GPR_DATA_SHIFT)



/* GPR register group index macro definition */
#define BGPR_GPR_0 (0UL)
#define BGPR_GPR_1 (1UL)
#define BGPR_GPR_2 (2UL)
#define BGPR_GPR_3 (3UL)
#define BGPR_GPR_4 (4UL)
#define BGPR_GPR_5 (5UL)
#define BGPR_GPR_6 (6UL)
#define BGPR_GPR_7 (7UL)
#define BGPR_GPR_8 (8UL)
#define BGPR_GPR_9 (9UL)
#define BGPR_GPR_10 (10UL)
#define BGPR_GPR_11 (11UL)
#define BGPR_GPR_12 (12UL)
#define BGPR_GPR_13 (13UL)
#define BGPR_GPR_14 (14UL)
#define BGPR_GPR_15 (15UL)


#endif /* HPM_BGPR_H */
