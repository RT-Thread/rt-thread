/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PLIC_SW_H
#define HPM_PLIC_SW_H

typedef struct {
    __R  uint8_t  RESERVED0[4096];             /* 0x0 - 0xFFF: Reserved */
    __RW uint32_t PENDING;                     /* 0x1000: Pending status */
    __R  uint8_t  RESERVED1[4092];             /* 0x1004 - 0x1FFF: Reserved */
    __RW uint32_t INTEN;                       /* 0x2000: Interrupt enable */
    __R  uint8_t  RESERVED2[2088960];          /* 0x2004 - 0x200003: Reserved */
    __RW uint32_t CLAIM;                       /* 0x200004: Claim and complete. */
} PLIC_SW_Type;


/* Bitfield definition for register: PENDING */
/*
 * INTERRUPT (RW)
 *
 * writing 1 to trigger software interrupt
 */
#define PLIC_SW_PENDING_INTERRUPT_MASK (0x2U)
#define PLIC_SW_PENDING_INTERRUPT_SHIFT (1U)
#define PLIC_SW_PENDING_INTERRUPT_SET(x) (((uint32_t)(x) << PLIC_SW_PENDING_INTERRUPT_SHIFT) & PLIC_SW_PENDING_INTERRUPT_MASK)
#define PLIC_SW_PENDING_INTERRUPT_GET(x) (((uint32_t)(x) & PLIC_SW_PENDING_INTERRUPT_MASK) >> PLIC_SW_PENDING_INTERRUPT_SHIFT)

/* Bitfield definition for register: INTEN */
/*
 * INTERRUPT (RW)
 *
 * enable software interrupt
 */
#define PLIC_SW_INTEN_INTERRUPT_MASK (0x1U)
#define PLIC_SW_INTEN_INTERRUPT_SHIFT (0U)
#define PLIC_SW_INTEN_INTERRUPT_SET(x) (((uint32_t)(x) << PLIC_SW_INTEN_INTERRUPT_SHIFT) & PLIC_SW_INTEN_INTERRUPT_MASK)
#define PLIC_SW_INTEN_INTERRUPT_GET(x) (((uint32_t)(x) & PLIC_SW_INTEN_INTERRUPT_MASK) >> PLIC_SW_INTEN_INTERRUPT_SHIFT)

/* Bitfield definition for register: CLAIM */
/*
 * INTERRUPT_ID (RW)
 *
 * On reads, indicating the interrupt source that has being claimed. On writes, indicating the interrupt source that has been handled (completed).
 */
#define PLIC_SW_CLAIM_INTERRUPT_ID_MASK (0x1U)
#define PLIC_SW_CLAIM_INTERRUPT_ID_SHIFT (0U)
#define PLIC_SW_CLAIM_INTERRUPT_ID_SET(x) (((uint32_t)(x) << PLIC_SW_CLAIM_INTERRUPT_ID_SHIFT) & PLIC_SW_CLAIM_INTERRUPT_ID_MASK)
#define PLIC_SW_CLAIM_INTERRUPT_ID_GET(x) (((uint32_t)(x) & PLIC_SW_CLAIM_INTERRUPT_ID_MASK) >> PLIC_SW_CLAIM_INTERRUPT_ID_SHIFT)




#endif /* HPM_PLIC_SW_H */
