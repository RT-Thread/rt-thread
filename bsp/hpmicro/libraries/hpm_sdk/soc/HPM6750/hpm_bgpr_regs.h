/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_BGPR_H
#define HPM_BGPR_H

typedef struct {
    __RW uint32_t BATT_GPR0;                   /* 0x0: Generic control */
    __RW uint32_t BATT_GPR1;                   /* 0x4: Generic control */
    __RW uint32_t BATT_GPR2;                   /* 0x8: Generic control */
    __RW uint32_t BATT_GPR3;                   /* 0xC: Generic control */
    __RW uint32_t BATT_GPR4;                   /* 0x10: Generic control */
    __RW uint32_t BATT_GPR5;                   /* 0x14: Generic control */
    __RW uint32_t BATT_GPR6;                   /* 0x18: Generic control */
    __RW uint32_t BATT_GPR7;                   /* 0x1C: Generic control */
} BGPR_Type;


/* Bitfield definition for register: BATT_GPR0 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define BGPR_BATT_GPR0_GPR_MASK (0xFFFFFFFFUL)
#define BGPR_BATT_GPR0_GPR_SHIFT (0U)
#define BGPR_BATT_GPR0_GPR_SET(x) (((uint32_t)(x) << BGPR_BATT_GPR0_GPR_SHIFT) & BGPR_BATT_GPR0_GPR_MASK)
#define BGPR_BATT_GPR0_GPR_GET(x) (((uint32_t)(x) & BGPR_BATT_GPR0_GPR_MASK) >> BGPR_BATT_GPR0_GPR_SHIFT)

/* Bitfield definition for register: BATT_GPR1 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define BGPR_BATT_GPR1_GPR_MASK (0xFFFFFFFFUL)
#define BGPR_BATT_GPR1_GPR_SHIFT (0U)
#define BGPR_BATT_GPR1_GPR_SET(x) (((uint32_t)(x) << BGPR_BATT_GPR1_GPR_SHIFT) & BGPR_BATT_GPR1_GPR_MASK)
#define BGPR_BATT_GPR1_GPR_GET(x) (((uint32_t)(x) & BGPR_BATT_GPR1_GPR_MASK) >> BGPR_BATT_GPR1_GPR_SHIFT)

/* Bitfield definition for register: BATT_GPR2 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define BGPR_BATT_GPR2_GPR_MASK (0xFFFFFFFFUL)
#define BGPR_BATT_GPR2_GPR_SHIFT (0U)
#define BGPR_BATT_GPR2_GPR_SET(x) (((uint32_t)(x) << BGPR_BATT_GPR2_GPR_SHIFT) & BGPR_BATT_GPR2_GPR_MASK)
#define BGPR_BATT_GPR2_GPR_GET(x) (((uint32_t)(x) & BGPR_BATT_GPR2_GPR_MASK) >> BGPR_BATT_GPR2_GPR_SHIFT)

/* Bitfield definition for register: BATT_GPR3 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define BGPR_BATT_GPR3_GPR_MASK (0xFFFFFFFFUL)
#define BGPR_BATT_GPR3_GPR_SHIFT (0U)
#define BGPR_BATT_GPR3_GPR_SET(x) (((uint32_t)(x) << BGPR_BATT_GPR3_GPR_SHIFT) & BGPR_BATT_GPR3_GPR_MASK)
#define BGPR_BATT_GPR3_GPR_GET(x) (((uint32_t)(x) & BGPR_BATT_GPR3_GPR_MASK) >> BGPR_BATT_GPR3_GPR_SHIFT)

/* Bitfield definition for register: BATT_GPR4 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define BGPR_BATT_GPR4_GPR_MASK (0xFFFFFFFFUL)
#define BGPR_BATT_GPR4_GPR_SHIFT (0U)
#define BGPR_BATT_GPR4_GPR_SET(x) (((uint32_t)(x) << BGPR_BATT_GPR4_GPR_SHIFT) & BGPR_BATT_GPR4_GPR_MASK)
#define BGPR_BATT_GPR4_GPR_GET(x) (((uint32_t)(x) & BGPR_BATT_GPR4_GPR_MASK) >> BGPR_BATT_GPR4_GPR_SHIFT)

/* Bitfield definition for register: BATT_GPR5 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define BGPR_BATT_GPR5_GPR_MASK (0xFFFFFFFFUL)
#define BGPR_BATT_GPR5_GPR_SHIFT (0U)
#define BGPR_BATT_GPR5_GPR_SET(x) (((uint32_t)(x) << BGPR_BATT_GPR5_GPR_SHIFT) & BGPR_BATT_GPR5_GPR_MASK)
#define BGPR_BATT_GPR5_GPR_GET(x) (((uint32_t)(x) & BGPR_BATT_GPR5_GPR_MASK) >> BGPR_BATT_GPR5_GPR_SHIFT)

/* Bitfield definition for register: BATT_GPR6 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define BGPR_BATT_GPR6_GPR_MASK (0xFFFFFFFFUL)
#define BGPR_BATT_GPR6_GPR_SHIFT (0U)
#define BGPR_BATT_GPR6_GPR_SET(x) (((uint32_t)(x) << BGPR_BATT_GPR6_GPR_SHIFT) & BGPR_BATT_GPR6_GPR_MASK)
#define BGPR_BATT_GPR6_GPR_GET(x) (((uint32_t)(x) & BGPR_BATT_GPR6_GPR_MASK) >> BGPR_BATT_GPR6_GPR_SHIFT)

/* Bitfield definition for register: BATT_GPR7 */
/*
 * GPR (RW)
 *
 * Generic control
 */
#define BGPR_BATT_GPR7_GPR_MASK (0xFFFFFFFFUL)
#define BGPR_BATT_GPR7_GPR_SHIFT (0U)
#define BGPR_BATT_GPR7_GPR_SET(x) (((uint32_t)(x) << BGPR_BATT_GPR7_GPR_SHIFT) & BGPR_BATT_GPR7_GPR_MASK)
#define BGPR_BATT_GPR7_GPR_GET(x) (((uint32_t)(x) & BGPR_BATT_GPR7_GPR_MASK) >> BGPR_BATT_GPR7_GPR_SHIFT)




#endif /* HPM_BGPR_H */
