/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_GPIOM_H
#define HPM_GPIOM_H

typedef struct {
    struct {
        __RW uint32_t PIN[32];                 /* 0x0 - 0x7C: GPIO mananger */
    } ASSIGN[16];
} GPIOM_Type;


/* Bitfield definition for register of struct array ASSIGN: PIN00 */
/*
 * LOCK (RW)
 *
 * lock fields in this register, lock can only be cleared by soc reset
 * 0: fields can be changed
 * 1: fields locked to current value, not changeable
 */
#define GPIOM_ASSIGN_PIN_LOCK_MASK (0x80000000UL)
#define GPIOM_ASSIGN_PIN_LOCK_SHIFT (31U)
#define GPIOM_ASSIGN_PIN_LOCK_SET(x) (((uint32_t)(x) << GPIOM_ASSIGN_PIN_LOCK_SHIFT) & GPIOM_ASSIGN_PIN_LOCK_MASK)
#define GPIOM_ASSIGN_PIN_LOCK_GET(x) (((uint32_t)(x) & GPIOM_ASSIGN_PIN_LOCK_MASK) >> GPIOM_ASSIGN_PIN_LOCK_SHIFT)

/*
 * HIDE (RW)
 *
 * pin value visibility to gpios,
 * bit0: 1, invisible to soc gpio0; 0: visible to soc gpio0
 * bit1: 1, invisible to cpu0 fast gpio; 0: visible to cpu0 fast gpio
 */
#define GPIOM_ASSIGN_PIN_HIDE_MASK (0x300U)
#define GPIOM_ASSIGN_PIN_HIDE_SHIFT (8U)
#define GPIOM_ASSIGN_PIN_HIDE_SET(x) (((uint32_t)(x) << GPIOM_ASSIGN_PIN_HIDE_SHIFT) & GPIOM_ASSIGN_PIN_HIDE_MASK)
#define GPIOM_ASSIGN_PIN_HIDE_GET(x) (((uint32_t)(x) & GPIOM_ASSIGN_PIN_HIDE_MASK) >> GPIOM_ASSIGN_PIN_HIDE_SHIFT)

/*
 * SELECT (RW)
 *
 * select which gpio controls chip pin,
 * 0: soc gpio0;
 * 2: cpu0 fastgpio
 */
#define GPIOM_ASSIGN_PIN_SELECT_MASK (0x3U)
#define GPIOM_ASSIGN_PIN_SELECT_SHIFT (0U)
#define GPIOM_ASSIGN_PIN_SELECT_SET(x) (((uint32_t)(x) << GPIOM_ASSIGN_PIN_SELECT_SHIFT) & GPIOM_ASSIGN_PIN_SELECT_MASK)
#define GPIOM_ASSIGN_PIN_SELECT_GET(x) (((uint32_t)(x) & GPIOM_ASSIGN_PIN_SELECT_MASK) >> GPIOM_ASSIGN_PIN_SELECT_SHIFT)



/* PIN register group index macro definition */
#define GPIOM_ASSIGN_PIN_PIN00 (0UL)
#define GPIOM_ASSIGN_PIN_PIN01 (1UL)
#define GPIOM_ASSIGN_PIN_PIN02 (2UL)
#define GPIOM_ASSIGN_PIN_PIN03 (3UL)
#define GPIOM_ASSIGN_PIN_PIN04 (4UL)
#define GPIOM_ASSIGN_PIN_PIN05 (5UL)
#define GPIOM_ASSIGN_PIN_PIN06 (6UL)
#define GPIOM_ASSIGN_PIN_PIN07 (7UL)
#define GPIOM_ASSIGN_PIN_PIN08 (8UL)
#define GPIOM_ASSIGN_PIN_PIN09 (9UL)
#define GPIOM_ASSIGN_PIN_PIN10 (10UL)
#define GPIOM_ASSIGN_PIN_PIN11 (11UL)
#define GPIOM_ASSIGN_PIN_PIN12 (12UL)
#define GPIOM_ASSIGN_PIN_PIN13 (13UL)
#define GPIOM_ASSIGN_PIN_PIN14 (14UL)
#define GPIOM_ASSIGN_PIN_PIN15 (15UL)
#define GPIOM_ASSIGN_PIN_PIN16 (16UL)
#define GPIOM_ASSIGN_PIN_PIN17 (17UL)
#define GPIOM_ASSIGN_PIN_PIN18 (18UL)
#define GPIOM_ASSIGN_PIN_PIN19 (19UL)
#define GPIOM_ASSIGN_PIN_PIN20 (20UL)
#define GPIOM_ASSIGN_PIN_PIN21 (21UL)
#define GPIOM_ASSIGN_PIN_PIN22 (22UL)
#define GPIOM_ASSIGN_PIN_PIN23 (23UL)
#define GPIOM_ASSIGN_PIN_PIN24 (24UL)
#define GPIOM_ASSIGN_PIN_PIN25 (25UL)
#define GPIOM_ASSIGN_PIN_PIN26 (26UL)
#define GPIOM_ASSIGN_PIN_PIN27 (27UL)
#define GPIOM_ASSIGN_PIN_PIN28 (28UL)
#define GPIOM_ASSIGN_PIN_PIN29 (29UL)
#define GPIOM_ASSIGN_PIN_PIN30 (30UL)
#define GPIOM_ASSIGN_PIN_PIN31 (31UL)

/* ASSIGN register group index macro definition */
#define GPIOM_ASSIGN_GPIOA (0UL)
#define GPIOM_ASSIGN_GPIOB (1UL)
#define GPIOM_ASSIGN_GPIOC (2UL)
#define GPIOM_ASSIGN_GPIOD (3UL)
#define GPIOM_ASSIGN_GPIOE (4UL)
#define GPIOM_ASSIGN_GPIOF (5UL)
#define GPIOM_ASSIGN_GPIOX (13UL)
#define GPIOM_ASSIGN_GPIOY (14UL)
#define GPIOM_ASSIGN_GPIOZ (15UL)


#endif /* HPM_GPIOM_H */
