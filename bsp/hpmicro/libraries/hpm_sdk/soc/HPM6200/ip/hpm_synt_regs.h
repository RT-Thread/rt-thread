/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SYNT_H
#define HPM_SYNT_H

typedef struct {
    __RW uint32_t GCR;                         /* 0x0: Global control register */
    __RW uint32_t RLD;                         /* 0x4: Counter reload register */
    __R  uint8_t  RESERVED0[4];                /* 0x8 - 0xB: Reserved */
    __R  uint32_t CNT;                         /* 0xC: Counter */
    __R  uint8_t  RESERVED1[16];               /* 0x10 - 0x1F: Reserved */
    __RW uint32_t CMP[4];                      /* 0x20 - 0x2C: Comparator */
} SYNT_Type;


/* Bitfield definition for register: GCR */
/*
 * CRST (RW)
 *
 * 1- Reset counter
 */
#define SYNT_GCR_CRST_MASK (0x2U)
#define SYNT_GCR_CRST_SHIFT (1U)
#define SYNT_GCR_CRST_SET(x) (((uint32_t)(x) << SYNT_GCR_CRST_SHIFT) & SYNT_GCR_CRST_MASK)
#define SYNT_GCR_CRST_GET(x) (((uint32_t)(x) & SYNT_GCR_CRST_MASK) >> SYNT_GCR_CRST_SHIFT)

/*
 * CEN (RW)
 *
 * 1- Enable counter
 */
#define SYNT_GCR_CEN_MASK (0x1U)
#define SYNT_GCR_CEN_SHIFT (0U)
#define SYNT_GCR_CEN_SET(x) (((uint32_t)(x) << SYNT_GCR_CEN_SHIFT) & SYNT_GCR_CEN_MASK)
#define SYNT_GCR_CEN_GET(x) (((uint32_t)(x) & SYNT_GCR_CEN_MASK) >> SYNT_GCR_CEN_SHIFT)

/* Bitfield definition for register: RLD */
/*
 * RLD (RW)
 *
 * counter reload value
 */
#define SYNT_RLD_RLD_MASK (0xFFFFFFFFUL)
#define SYNT_RLD_RLD_SHIFT (0U)
#define SYNT_RLD_RLD_SET(x) (((uint32_t)(x) << SYNT_RLD_RLD_SHIFT) & SYNT_RLD_RLD_MASK)
#define SYNT_RLD_RLD_GET(x) (((uint32_t)(x) & SYNT_RLD_RLD_MASK) >> SYNT_RLD_RLD_SHIFT)

/* Bitfield definition for register: CNT */
/*
 * CNT (RO)
 *
 * counter
 */
#define SYNT_CNT_CNT_MASK (0xFFFFFFFFUL)
#define SYNT_CNT_CNT_SHIFT (0U)
#define SYNT_CNT_CNT_GET(x) (((uint32_t)(x) & SYNT_CNT_CNT_MASK) >> SYNT_CNT_CNT_SHIFT)

/* Bitfield definition for register array: CMP */
/*
 * CMP (RW)
 *
 * comparator value, the output will assert when counter count to this value
 */
#define SYNT_CMP_CMP_MASK (0xFFFFFFFFUL)
#define SYNT_CMP_CMP_SHIFT (0U)
#define SYNT_CMP_CMP_SET(x) (((uint32_t)(x) << SYNT_CMP_CMP_SHIFT) & SYNT_CMP_CMP_MASK)
#define SYNT_CMP_CMP_GET(x) (((uint32_t)(x) & SYNT_CMP_CMP_MASK) >> SYNT_CMP_CMP_SHIFT)



/* CMP register group index macro definition */
#define SYNT_CMP_0 (0UL)
#define SYNT_CMP_1 (1UL)
#define SYNT_CMP_2 (2UL)
#define SYNT_CMP_3 (3UL)


#endif /* HPM_SYNT_H */
