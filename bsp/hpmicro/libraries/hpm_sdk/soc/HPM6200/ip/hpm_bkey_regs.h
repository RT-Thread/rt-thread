/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_BKEY_H
#define HPM_BKEY_H

typedef struct {
    struct {
        __RW uint32_t DATA[8];                 /* 0x0 - 0x1C: Key data */
    } KEY[2];
    __RW uint32_t ECC[2];                      /* 0x40 - 0x44: Key ECC and access control */
    __RW uint32_t SELECT;                      /* 0x48: Key selection */
} BKEY_Type;


/* Bitfield definition for register of struct array KEY: 0 */
/*
 * DATA (RW)
 *
 * security key data
 */
#define BKEY_KEY_DATA_DATA_MASK (0xFFFFFFFFUL)
#define BKEY_KEY_DATA_DATA_SHIFT (0U)
#define BKEY_KEY_DATA_DATA_SET(x) (((uint32_t)(x) << BKEY_KEY_DATA_DATA_SHIFT) & BKEY_KEY_DATA_DATA_MASK)
#define BKEY_KEY_DATA_DATA_GET(x) (((uint32_t)(x) & BKEY_KEY_DATA_DATA_MASK) >> BKEY_KEY_DATA_DATA_SHIFT)

/* Bitfield definition for register array: ECC */
/*
 * WLOCK (RW)
 *
 * write lock to key0
 * 0: write enable
 * 1: write ignored
 */
#define BKEY_ECC_WLOCK_MASK (0x80000000UL)
#define BKEY_ECC_WLOCK_SHIFT (31U)
#define BKEY_ECC_WLOCK_SET(x) (((uint32_t)(x) << BKEY_ECC_WLOCK_SHIFT) & BKEY_ECC_WLOCK_MASK)
#define BKEY_ECC_WLOCK_GET(x) (((uint32_t)(x) & BKEY_ECC_WLOCK_MASK) >> BKEY_ECC_WLOCK_SHIFT)

/*
 * RLOCK (RW)
 *
 * read lock to key0
 * 0: key read enable
 * 1: key always read as 0
 */
#define BKEY_ECC_RLOCK_MASK (0x40000000UL)
#define BKEY_ECC_RLOCK_SHIFT (30U)
#define BKEY_ECC_RLOCK_SET(x) (((uint32_t)(x) << BKEY_ECC_RLOCK_SHIFT) & BKEY_ECC_RLOCK_MASK)
#define BKEY_ECC_RLOCK_GET(x) (((uint32_t)(x) & BKEY_ECC_RLOCK_MASK) >> BKEY_ECC_RLOCK_SHIFT)

/*
 * ECC (RW)
 *
 * Parity check bits for key0
 */
#define BKEY_ECC_ECC_MASK (0xFFFFU)
#define BKEY_ECC_ECC_SHIFT (0U)
#define BKEY_ECC_ECC_SET(x) (((uint32_t)(x) << BKEY_ECC_ECC_SHIFT) & BKEY_ECC_ECC_MASK)
#define BKEY_ECC_ECC_GET(x) (((uint32_t)(x) & BKEY_ECC_ECC_MASK) >> BKEY_ECC_ECC_SHIFT)

/* Bitfield definition for register: SELECT */
/*
 * SELECT (RW)
 *
 * select key, key0 treated as secure key, in non-scure mode, only key1 can be selected
 * 0: select key0 in secure mode, key1 in non-secure mode
 * 1: select key1 in secure or nonsecure mode
 */
#define BKEY_SELECT_SELECT_MASK (0x1U)
#define BKEY_SELECT_SELECT_SHIFT (0U)
#define BKEY_SELECT_SELECT_SET(x) (((uint32_t)(x) << BKEY_SELECT_SELECT_SHIFT) & BKEY_SELECT_SELECT_MASK)
#define BKEY_SELECT_SELECT_GET(x) (((uint32_t)(x) & BKEY_SELECT_SELECT_MASK) >> BKEY_SELECT_SELECT_SHIFT)



/* DATA register group index macro definition */
#define BKEY_KEY_DATA_0 (0UL)
#define BKEY_KEY_DATA_1 (1UL)
#define BKEY_KEY_DATA_2 (2UL)
#define BKEY_KEY_DATA_3 (3UL)
#define BKEY_KEY_DATA_4 (4UL)
#define BKEY_KEY_DATA_5 (5UL)
#define BKEY_KEY_DATA_6 (6UL)
#define BKEY_KEY_DATA_7 (7UL)

/* KEY register group index macro definition */
#define BKEY_KEY_0 (0UL)
#define BKEY_KEY_1 (1UL)

/* ECC register group index macro definition */
#define BKEY_ECC_KEY0 (0UL)
#define BKEY_ECC_KEY1 (1UL)


#endif /* HPM_BKEY_H */
