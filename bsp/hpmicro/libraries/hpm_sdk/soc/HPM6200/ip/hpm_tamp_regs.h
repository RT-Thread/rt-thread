/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_TAMP_H
#define HPM_TAMP_H

typedef struct {
    struct {
        __RW uint32_t CONTROL;                 /* 0x0: Tamper n control */
        __RW uint32_t POLY;                    /* 0x4: Tamper n Polynomial of LFSR */
        __W  uint32_t LFSR;                    /* 0x8: Tamper n LFSR shift register */
        __R  uint8_t  RESERVED0[4];            /* 0xC - 0xF: Reserved */
    } TAMP[4];
    __R  uint8_t  RESERVED0[64];               /* 0x40 - 0x7F: Reserved */
    __RW uint32_t TAMP_FLAG;                   /* 0x80: Tamper flag */
    __RW uint32_t IRQ_EN;                      /* 0x84: Tamper interrupt enable */
} TAMP_Type;


/* Bitfield definition for register of struct array TAMP: CONTROL */
/*
 * LOCK (RW)
 *
 * lock tamper setting
 * 0: tamper setting can be changed
 * 1: tamper setting will last to next battery domain power cycle
 */
#define TAMP_TAMP_CONTROL_LOCK_MASK (0x80000000UL)
#define TAMP_TAMP_CONTROL_LOCK_SHIFT (31U)
#define TAMP_TAMP_CONTROL_LOCK_SET(x) (((uint32_t)(x) << TAMP_TAMP_CONTROL_LOCK_SHIFT) & TAMP_TAMP_CONTROL_LOCK_MASK)
#define TAMP_TAMP_CONTROL_LOCK_GET(x) (((uint32_t)(x) & TAMP_TAMP_CONTROL_LOCK_MASK) >> TAMP_TAMP_CONTROL_LOCK_SHIFT)

/*
 * BYPASS (RW)
 *
 * bypass tamper violation filter
 * 0: filter applied
 * 1: filter not used
 */
#define TAMP_TAMP_CONTROL_BYPASS_MASK (0x100000UL)
#define TAMP_TAMP_CONTROL_BYPASS_SHIFT (20U)
#define TAMP_TAMP_CONTROL_BYPASS_SET(x) (((uint32_t)(x) << TAMP_TAMP_CONTROL_BYPASS_SHIFT) & TAMP_TAMP_CONTROL_BYPASS_MASK)
#define TAMP_TAMP_CONTROL_BYPASS_GET(x) (((uint32_t)(x) & TAMP_TAMP_CONTROL_BYPASS_MASK) >> TAMP_TAMP_CONTROL_BYPASS_SHIFT)

/*
 * FILTER (RW)
 *
 * filter length
 * 0: 1 cycle
 * 1: 2 cycle
 * 15: 65526 cycle
 */
#define TAMP_TAMP_CONTROL_FILTER_MASK (0xF0000UL)
#define TAMP_TAMP_CONTROL_FILTER_SHIFT (16U)
#define TAMP_TAMP_CONTROL_FILTER_SET(x) (((uint32_t)(x) << TAMP_TAMP_CONTROL_FILTER_SHIFT) & TAMP_TAMP_CONTROL_FILTER_MASK)
#define TAMP_TAMP_CONTROL_FILTER_GET(x) (((uint32_t)(x) & TAMP_TAMP_CONTROL_FILTER_MASK) >> TAMP_TAMP_CONTROL_FILTER_SHIFT)

/*
 * VALUE (RW)
 *
 * pin value for passive tamper
 */
#define TAMP_TAMP_CONTROL_VALUE_MASK (0x300U)
#define TAMP_TAMP_CONTROL_VALUE_SHIFT (8U)
#define TAMP_TAMP_CONTROL_VALUE_SET(x) (((uint32_t)(x) << TAMP_TAMP_CONTROL_VALUE_SHIFT) & TAMP_TAMP_CONTROL_VALUE_MASK)
#define TAMP_TAMP_CONTROL_VALUE_GET(x) (((uint32_t)(x) & TAMP_TAMP_CONTROL_VALUE_MASK) >> TAMP_TAMP_CONTROL_VALUE_SHIFT)

/*
 * SPEED (RW)
 *
 * tamper speed selection, (2^SPEED) changes per second
 * 0: 1 shift per second
 * 1: 2 shifts per second
 * . . .
 * 15: 32768 shifts per second
 */
#define TAMP_TAMP_CONTROL_SPEED_MASK (0xF0U)
#define TAMP_TAMP_CONTROL_SPEED_SHIFT (4U)
#define TAMP_TAMP_CONTROL_SPEED_SET(x) (((uint32_t)(x) << TAMP_TAMP_CONTROL_SPEED_SHIFT) & TAMP_TAMP_CONTROL_SPEED_MASK)
#define TAMP_TAMP_CONTROL_SPEED_GET(x) (((uint32_t)(x) & TAMP_TAMP_CONTROL_SPEED_MASK) >> TAMP_TAMP_CONTROL_SPEED_SHIFT)

/*
 * RECOVER (RW)
 *
 * tamper will recover itself if tamper LFSR goes wrong
 * 0: tamper will not recover
 * 1: tamper will recover
 */
#define TAMP_TAMP_CONTROL_RECOVER_MASK (0x4U)
#define TAMP_TAMP_CONTROL_RECOVER_SHIFT (2U)
#define TAMP_TAMP_CONTROL_RECOVER_SET(x) (((uint32_t)(x) << TAMP_TAMP_CONTROL_RECOVER_SHIFT) & TAMP_TAMP_CONTROL_RECOVER_MASK)
#define TAMP_TAMP_CONTROL_RECOVER_GET(x) (((uint32_t)(x) & TAMP_TAMP_CONTROL_RECOVER_MASK) >> TAMP_TAMP_CONTROL_RECOVER_SHIFT)

/*
 * ACTIVE (RW)
 *
 * select active or passive tamper
 * 0: passive tamper
 * 1: active tamper
 */
#define TAMP_TAMP_CONTROL_ACTIVE_MASK (0x2U)
#define TAMP_TAMP_CONTROL_ACTIVE_SHIFT (1U)
#define TAMP_TAMP_CONTROL_ACTIVE_SET(x) (((uint32_t)(x) << TAMP_TAMP_CONTROL_ACTIVE_SHIFT) & TAMP_TAMP_CONTROL_ACTIVE_MASK)
#define TAMP_TAMP_CONTROL_ACTIVE_GET(x) (((uint32_t)(x) & TAMP_TAMP_CONTROL_ACTIVE_MASK) >> TAMP_TAMP_CONTROL_ACTIVE_SHIFT)

/*
 * ENABLE (RW)
 *
 * enable tamper
 * 0: tamper disableed
 * 1: tamper enabled
 */
#define TAMP_TAMP_CONTROL_ENABLE_MASK (0x1U)
#define TAMP_TAMP_CONTROL_ENABLE_SHIFT (0U)
#define TAMP_TAMP_CONTROL_ENABLE_SET(x) (((uint32_t)(x) << TAMP_TAMP_CONTROL_ENABLE_SHIFT) & TAMP_TAMP_CONTROL_ENABLE_MASK)
#define TAMP_TAMP_CONTROL_ENABLE_GET(x) (((uint32_t)(x) & TAMP_TAMP_CONTROL_ENABLE_MASK) >> TAMP_TAMP_CONTROL_ENABLE_SHIFT)

/* Bitfield definition for register of struct array TAMP: POLY */
/*
 * POLY (RW)
 *
 * tamper LFSR polyminal, this is a write once register, once write content is locked, and readout value is "1"
 */
#define TAMP_TAMP_POLY_POLY_MASK (0xFFFFFFFFUL)
#define TAMP_TAMP_POLY_POLY_SHIFT (0U)
#define TAMP_TAMP_POLY_POLY_SET(x) (((uint32_t)(x) << TAMP_TAMP_POLY_POLY_SHIFT) & TAMP_TAMP_POLY_POLY_MASK)
#define TAMP_TAMP_POLY_POLY_GET(x) (((uint32_t)(x) & TAMP_TAMP_POLY_POLY_MASK) >> TAMP_TAMP_POLY_POLY_SHIFT)

/* Bitfield definition for register of struct array TAMP: LFSR */
/*
 * LFSR (WO)
 *
 * LFSR for active tamper, write only register, always read 0
 */
#define TAMP_TAMP_LFSR_LFSR_MASK (0xFFFFFFFFUL)
#define TAMP_TAMP_LFSR_LFSR_SHIFT (0U)
#define TAMP_TAMP_LFSR_LFSR_SET(x) (((uint32_t)(x) << TAMP_TAMP_LFSR_LFSR_SHIFT) & TAMP_TAMP_LFSR_LFSR_MASK)
#define TAMP_TAMP_LFSR_LFSR_GET(x) (((uint32_t)(x) & TAMP_TAMP_LFSR_LFSR_MASK) >> TAMP_TAMP_LFSR_LFSR_SHIFT)

/* Bitfield definition for register: TAMP_FLAG */
/*
 * FLAG (RW)
 *
 * tamper flag, each bit represents one tamper pin, write 1 to clear the flag
 * Note, clear can only be cleared when tamper disappeared
 */
#define TAMP_TAMP_FLAG_FLAG_MASK (0xFFFU)
#define TAMP_TAMP_FLAG_FLAG_SHIFT (0U)
#define TAMP_TAMP_FLAG_FLAG_SET(x) (((uint32_t)(x) << TAMP_TAMP_FLAG_FLAG_SHIFT) & TAMP_TAMP_FLAG_FLAG_MASK)
#define TAMP_TAMP_FLAG_FLAG_GET(x) (((uint32_t)(x) & TAMP_TAMP_FLAG_FLAG_MASK) >> TAMP_TAMP_FLAG_FLAG_SHIFT)

/* Bitfield definition for register: IRQ_EN */
/*
 * LOCK (RW)
 *
 * lock bit for IRQ enable
 * 0: enable bits can be changed
 * 1: enable bits hold until next battery domain power cycle
 */
#define TAMP_IRQ_EN_LOCK_MASK (0x80000000UL)
#define TAMP_IRQ_EN_LOCK_SHIFT (31U)
#define TAMP_IRQ_EN_LOCK_SET(x) (((uint32_t)(x) << TAMP_IRQ_EN_LOCK_SHIFT) & TAMP_IRQ_EN_LOCK_MASK)
#define TAMP_IRQ_EN_LOCK_GET(x) (((uint32_t)(x) & TAMP_IRQ_EN_LOCK_MASK) >> TAMP_IRQ_EN_LOCK_SHIFT)

/*
 * IRQ_EN (RW)
 *
 * interrupt enable, each bit represents one tamper pin
 * 0: interrupt disabled
 * 1: interrupt enabled
 */
#define TAMP_IRQ_EN_IRQ_EN_MASK (0xFFFU)
#define TAMP_IRQ_EN_IRQ_EN_SHIFT (0U)
#define TAMP_IRQ_EN_IRQ_EN_SET(x) (((uint32_t)(x) << TAMP_IRQ_EN_IRQ_EN_SHIFT) & TAMP_IRQ_EN_IRQ_EN_MASK)
#define TAMP_IRQ_EN_IRQ_EN_GET(x) (((uint32_t)(x) & TAMP_IRQ_EN_IRQ_EN_MASK) >> TAMP_IRQ_EN_IRQ_EN_SHIFT)



/* TAMP register group index macro definition */
#define TAMP_TAMP_TAMP0 (0UL)
#define TAMP_TAMP_TAMP1 (1UL)
#define TAMP_TAMP_TAMP2 (2UL)
#define TAMP_TAMP_TAMP3 (3UL)


#endif /* HPM_TAMP_H */
