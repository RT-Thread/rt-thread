/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_KEYMAN_H
#define HPM_KEYMAN_H

typedef struct {
    __RW uint32_t SOFTMKEY[8];                 /* 0x0 - 0x1C: software set symmetric key */
    __RW uint32_t SOFTPKEY[8];                 /* 0x20 - 0x3C: system asymmetric key */
    __RW uint32_t SEC_KEY_CTL;                 /* 0x40: Random number interface behavior */
    __RW uint32_t NSC_KEY_CTL;                 /* 0x44: Random number interface behavior */
    __RW uint32_t RNG;                         /* 0x48: Random number interface behavior */
    __RW uint32_t READ_CONTROL;                /* 0x4C: symmetric and asymmetric key read out control */
} KEYMAN_Type;


/* Bitfield definition for register array: SOFTMKEY */
/*
 * KEY (RW)
 *
 * software symmetric key
 * key will be scambled to 4 variants for software to use, and replicable on same chip.
 * scramble keys are chip different, and not replicable on different chip
 * must be write sequencely from 0 - 7, otherwise key value will be treated as all 0
 */
#define KEYMAN_SOFTMKEY_KEY_MASK (0xFFFFFFFFUL)
#define KEYMAN_SOFTMKEY_KEY_SHIFT (0U)
#define KEYMAN_SOFTMKEY_KEY_SET(x) (((uint32_t)(x) << KEYMAN_SOFTMKEY_KEY_SHIFT) & KEYMAN_SOFTMKEY_KEY_MASK)
#define KEYMAN_SOFTMKEY_KEY_GET(x) (((uint32_t)(x) & KEYMAN_SOFTMKEY_KEY_MASK) >> KEYMAN_SOFTMKEY_KEY_SHIFT)

/* Bitfield definition for register array: SOFTPKEY */
/*
 * KEY (RW)
 *
 * software asymmetric key
 * key is XOR version of scrambles of fuse private key, software input key, SRK, and system security status.
 * This key os read once, sencondary read will read out 0
 */
#define KEYMAN_SOFTPKEY_KEY_MASK (0xFFFFFFFFUL)
#define KEYMAN_SOFTPKEY_KEY_SHIFT (0U)
#define KEYMAN_SOFTPKEY_KEY_SET(x) (((uint32_t)(x) << KEYMAN_SOFTPKEY_KEY_SHIFT) & KEYMAN_SOFTPKEY_KEY_MASK)
#define KEYMAN_SOFTPKEY_KEY_GET(x) (((uint32_t)(x) & KEYMAN_SOFTPKEY_KEY_MASK) >> KEYMAN_SOFTPKEY_KEY_SHIFT)

/* Bitfield definition for register: SEC_KEY_CTL */
/*
 * LOCK_SEC_CTL (RW)
 *
 * block secure state key setting being changed
 */
#define KEYMAN_SEC_KEY_CTL_LOCK_SEC_CTL_MASK (0x80000000UL)
#define KEYMAN_SEC_KEY_CTL_LOCK_SEC_CTL_SHIFT (31U)
#define KEYMAN_SEC_KEY_CTL_LOCK_SEC_CTL_SET(x) (((uint32_t)(x) << KEYMAN_SEC_KEY_CTL_LOCK_SEC_CTL_SHIFT) & KEYMAN_SEC_KEY_CTL_LOCK_SEC_CTL_MASK)
#define KEYMAN_SEC_KEY_CTL_LOCK_SEC_CTL_GET(x) (((uint32_t)(x) & KEYMAN_SEC_KEY_CTL_LOCK_SEC_CTL_MASK) >> KEYMAN_SEC_KEY_CTL_LOCK_SEC_CTL_SHIFT)

/*
 * SK_VAL (RO)
 *
 * session key valid
 * 0: session key is all 0's and not usable
 * 1: session key is valid
 */
#define KEYMAN_SEC_KEY_CTL_SK_VAL_MASK (0x10000UL)
#define KEYMAN_SEC_KEY_CTL_SK_VAL_SHIFT (16U)
#define KEYMAN_SEC_KEY_CTL_SK_VAL_GET(x) (((uint32_t)(x) & KEYMAN_SEC_KEY_CTL_SK_VAL_MASK) >> KEYMAN_SEC_KEY_CTL_SK_VAL_SHIFT)

/*
 * SMK_SEL (RW)
 *
 * software symmetric key selection
 * 0: use scramble version of software symmetric key
 * 1: use origin value in software symmetric key
 */
#define KEYMAN_SEC_KEY_CTL_SMK_SEL_MASK (0x1000U)
#define KEYMAN_SEC_KEY_CTL_SMK_SEL_SHIFT (12U)
#define KEYMAN_SEC_KEY_CTL_SMK_SEL_SET(x) (((uint32_t)(x) << KEYMAN_SEC_KEY_CTL_SMK_SEL_SHIFT) & KEYMAN_SEC_KEY_CTL_SMK_SEL_MASK)
#define KEYMAN_SEC_KEY_CTL_SMK_SEL_GET(x) (((uint32_t)(x) & KEYMAN_SEC_KEY_CTL_SMK_SEL_MASK) >> KEYMAN_SEC_KEY_CTL_SMK_SEL_SHIFT)

/*
 * ZMK_SEL (RW)
 *
 * software symmetric key selection
 * 0: use scramble version of software symmetric key
 * 1: use origin value in software symmetric key
 */
#define KEYMAN_SEC_KEY_CTL_ZMK_SEL_MASK (0x100U)
#define KEYMAN_SEC_KEY_CTL_ZMK_SEL_SHIFT (8U)
#define KEYMAN_SEC_KEY_CTL_ZMK_SEL_SET(x) (((uint32_t)(x) << KEYMAN_SEC_KEY_CTL_ZMK_SEL_SHIFT) & KEYMAN_SEC_KEY_CTL_ZMK_SEL_MASK)
#define KEYMAN_SEC_KEY_CTL_ZMK_SEL_GET(x) (((uint32_t)(x) & KEYMAN_SEC_KEY_CTL_ZMK_SEL_MASK) >> KEYMAN_SEC_KEY_CTL_ZMK_SEL_SHIFT)

/*
 * FMK_SEL (RW)
 *
 * fuse symmetric key selection
 * 0: use scramble version of fuse symmetric key
 * 1: use origin value in fuse symmetric key
 */
#define KEYMAN_SEC_KEY_CTL_FMK_SEL_MASK (0x10U)
#define KEYMAN_SEC_KEY_CTL_FMK_SEL_SHIFT (4U)
#define KEYMAN_SEC_KEY_CTL_FMK_SEL_SET(x) (((uint32_t)(x) << KEYMAN_SEC_KEY_CTL_FMK_SEL_SHIFT) & KEYMAN_SEC_KEY_CTL_FMK_SEL_MASK)
#define KEYMAN_SEC_KEY_CTL_FMK_SEL_GET(x) (((uint32_t)(x) & KEYMAN_SEC_KEY_CTL_FMK_SEL_MASK) >> KEYMAN_SEC_KEY_CTL_FMK_SEL_SHIFT)

/*
 * KEY_SEL (RW)
 *
 * secure symmtric key synthesize setting, key is a XOR of followings
 * bit0: fuse mk, 0: not selected, 1:selected
 * bit1: zmk from batt, 0: not selected, 1:selected
 * bit2: software key 0: not selected, 1:selected
 */
#define KEYMAN_SEC_KEY_CTL_KEY_SEL_MASK (0x7U)
#define KEYMAN_SEC_KEY_CTL_KEY_SEL_SHIFT (0U)
#define KEYMAN_SEC_KEY_CTL_KEY_SEL_SET(x) (((uint32_t)(x) << KEYMAN_SEC_KEY_CTL_KEY_SEL_SHIFT) & KEYMAN_SEC_KEY_CTL_KEY_SEL_MASK)
#define KEYMAN_SEC_KEY_CTL_KEY_SEL_GET(x) (((uint32_t)(x) & KEYMAN_SEC_KEY_CTL_KEY_SEL_MASK) >> KEYMAN_SEC_KEY_CTL_KEY_SEL_SHIFT)

/* Bitfield definition for register: NSC_KEY_CTL */
/*
 * LOCK_NSC_CTL (RW)
 *
 * block non-secure state key setting being changed
 */
#define KEYMAN_NSC_KEY_CTL_LOCK_NSC_CTL_MASK (0x80000000UL)
#define KEYMAN_NSC_KEY_CTL_LOCK_NSC_CTL_SHIFT (31U)
#define KEYMAN_NSC_KEY_CTL_LOCK_NSC_CTL_SET(x) (((uint32_t)(x) << KEYMAN_NSC_KEY_CTL_LOCK_NSC_CTL_SHIFT) & KEYMAN_NSC_KEY_CTL_LOCK_NSC_CTL_MASK)
#define KEYMAN_NSC_KEY_CTL_LOCK_NSC_CTL_GET(x) (((uint32_t)(x) & KEYMAN_NSC_KEY_CTL_LOCK_NSC_CTL_MASK) >> KEYMAN_NSC_KEY_CTL_LOCK_NSC_CTL_SHIFT)

/*
 * SK_VAL (RO)
 *
 * session key valid
 * 0: session key is all 0's and not usable
 * 1: session key is valid
 */
#define KEYMAN_NSC_KEY_CTL_SK_VAL_MASK (0x10000UL)
#define KEYMAN_NSC_KEY_CTL_SK_VAL_SHIFT (16U)
#define KEYMAN_NSC_KEY_CTL_SK_VAL_GET(x) (((uint32_t)(x) & KEYMAN_NSC_KEY_CTL_SK_VAL_MASK) >> KEYMAN_NSC_KEY_CTL_SK_VAL_SHIFT)

/*
 * SMK_SEL (RW)
 *
 * software symmetric key selection
 * 0: use scramble version of software symmetric key
 * 1: use origin value in software symmetric key
 */
#define KEYMAN_NSC_KEY_CTL_SMK_SEL_MASK (0x1000U)
#define KEYMAN_NSC_KEY_CTL_SMK_SEL_SHIFT (12U)
#define KEYMAN_NSC_KEY_CTL_SMK_SEL_SET(x) (((uint32_t)(x) << KEYMAN_NSC_KEY_CTL_SMK_SEL_SHIFT) & KEYMAN_NSC_KEY_CTL_SMK_SEL_MASK)
#define KEYMAN_NSC_KEY_CTL_SMK_SEL_GET(x) (((uint32_t)(x) & KEYMAN_NSC_KEY_CTL_SMK_SEL_MASK) >> KEYMAN_NSC_KEY_CTL_SMK_SEL_SHIFT)

/*
 * ZMK_SEL (RW)
 *
 * software symmetric key selection
 * 0: use scramble version of software symmetric key
 * 1: use origin value in software symmetric key
 */
#define KEYMAN_NSC_KEY_CTL_ZMK_SEL_MASK (0x100U)
#define KEYMAN_NSC_KEY_CTL_ZMK_SEL_SHIFT (8U)
#define KEYMAN_NSC_KEY_CTL_ZMK_SEL_SET(x) (((uint32_t)(x) << KEYMAN_NSC_KEY_CTL_ZMK_SEL_SHIFT) & KEYMAN_NSC_KEY_CTL_ZMK_SEL_MASK)
#define KEYMAN_NSC_KEY_CTL_ZMK_SEL_GET(x) (((uint32_t)(x) & KEYMAN_NSC_KEY_CTL_ZMK_SEL_MASK) >> KEYMAN_NSC_KEY_CTL_ZMK_SEL_SHIFT)

/*
 * FMK_SEL (RW)
 *
 * fuse symmetric key selection
 * 0: use scramble version of fuse symmetric key
 * 1: use origin value in fuse symmetric key
 */
#define KEYMAN_NSC_KEY_CTL_FMK_SEL_MASK (0x10U)
#define KEYMAN_NSC_KEY_CTL_FMK_SEL_SHIFT (4U)
#define KEYMAN_NSC_KEY_CTL_FMK_SEL_SET(x) (((uint32_t)(x) << KEYMAN_NSC_KEY_CTL_FMK_SEL_SHIFT) & KEYMAN_NSC_KEY_CTL_FMK_SEL_MASK)
#define KEYMAN_NSC_KEY_CTL_FMK_SEL_GET(x) (((uint32_t)(x) & KEYMAN_NSC_KEY_CTL_FMK_SEL_MASK) >> KEYMAN_NSC_KEY_CTL_FMK_SEL_SHIFT)

/*
 * KEY_SEL (RW)
 *
 * non-secure symmtric key synthesize setting, key is a XOR of followings
 * bit0: fuse mk, 0: not selected, 1:selected
 * bit1: zmk from batt, 0: not selected, 1:selected
 * bit2: software key 0: not selected, 1:selected
 */
#define KEYMAN_NSC_KEY_CTL_KEY_SEL_MASK (0x7U)
#define KEYMAN_NSC_KEY_CTL_KEY_SEL_SHIFT (0U)
#define KEYMAN_NSC_KEY_CTL_KEY_SEL_SET(x) (((uint32_t)(x) << KEYMAN_NSC_KEY_CTL_KEY_SEL_SHIFT) & KEYMAN_NSC_KEY_CTL_KEY_SEL_MASK)
#define KEYMAN_NSC_KEY_CTL_KEY_SEL_GET(x) (((uint32_t)(x) & KEYMAN_NSC_KEY_CTL_KEY_SEL_MASK) >> KEYMAN_NSC_KEY_CTL_KEY_SEL_SHIFT)

/* Bitfield definition for register: RNG */
/*
 * BLOCK_RNG_XOR (RW)
 *
 * block RNG_XOR bit from changing, if this bit is written to 1, it will hold 1 until next reset
 * 0: RNG_XOR can be changed by software
 * 1: RNG_XOR ignore software change from software
 */
#define KEYMAN_RNG_BLOCK_RNG_XOR_MASK (0x10000UL)
#define KEYMAN_RNG_BLOCK_RNG_XOR_SHIFT (16U)
#define KEYMAN_RNG_BLOCK_RNG_XOR_SET(x) (((uint32_t)(x) << KEYMAN_RNG_BLOCK_RNG_XOR_SHIFT) & KEYMAN_RNG_BLOCK_RNG_XOR_MASK)
#define KEYMAN_RNG_BLOCK_RNG_XOR_GET(x) (((uint32_t)(x) & KEYMAN_RNG_BLOCK_RNG_XOR_MASK) >> KEYMAN_RNG_BLOCK_RNG_XOR_SHIFT)

/*
 * RNG_XOR (RW)
 *
 * control how SFK is accepted from random number generator
 * 0: SFK value replaced by random number input
 * 1: SFK value exclusive or with random number input,this help generate random number using 2 rings inside RNG
 */
#define KEYMAN_RNG_RNG_XOR_MASK (0x1U)
#define KEYMAN_RNG_RNG_XOR_SHIFT (0U)
#define KEYMAN_RNG_RNG_XOR_SET(x) (((uint32_t)(x) << KEYMAN_RNG_RNG_XOR_SHIFT) & KEYMAN_RNG_RNG_XOR_MASK)
#define KEYMAN_RNG_RNG_XOR_GET(x) (((uint32_t)(x) & KEYMAN_RNG_RNG_XOR_MASK) >> KEYMAN_RNG_RNG_XOR_SHIFT)

/* Bitfield definition for register: READ_CONTROL */
/*
 * BLOCK_PK_READ (RW)
 *
 * asymmetric key readout control, if this bit is written to 1, it will hold 1 until next reset
 * 0: key can be read out
 * 1: key cannot be read out
 */
#define KEYMAN_READ_CONTROL_BLOCK_PK_READ_MASK (0x10000UL)
#define KEYMAN_READ_CONTROL_BLOCK_PK_READ_SHIFT (16U)
#define KEYMAN_READ_CONTROL_BLOCK_PK_READ_SET(x) (((uint32_t)(x) << KEYMAN_READ_CONTROL_BLOCK_PK_READ_SHIFT) & KEYMAN_READ_CONTROL_BLOCK_PK_READ_MASK)
#define KEYMAN_READ_CONTROL_BLOCK_PK_READ_GET(x) (((uint32_t)(x) & KEYMAN_READ_CONTROL_BLOCK_PK_READ_MASK) >> KEYMAN_READ_CONTROL_BLOCK_PK_READ_SHIFT)

/*
 * BLOCK_SMK_READ (RW)
 *
 * symmetric key readout control, if this bit is written to 1, it will hold 1 until next reset
 * 0: key can be read out
 * 1: key cannot be read out
 */
#define KEYMAN_READ_CONTROL_BLOCK_SMK_READ_MASK (0x1U)
#define KEYMAN_READ_CONTROL_BLOCK_SMK_READ_SHIFT (0U)
#define KEYMAN_READ_CONTROL_BLOCK_SMK_READ_SET(x) (((uint32_t)(x) << KEYMAN_READ_CONTROL_BLOCK_SMK_READ_SHIFT) & KEYMAN_READ_CONTROL_BLOCK_SMK_READ_MASK)
#define KEYMAN_READ_CONTROL_BLOCK_SMK_READ_GET(x) (((uint32_t)(x) & KEYMAN_READ_CONTROL_BLOCK_SMK_READ_MASK) >> KEYMAN_READ_CONTROL_BLOCK_SMK_READ_SHIFT)



/* SOFTMKEY register group index macro definition */
#define KEYMAN_SOFTMKEY_SFK0 (0UL)
#define KEYMAN_SOFTMKEY_SFK1 (1UL)
#define KEYMAN_SOFTMKEY_SFK2 (2UL)
#define KEYMAN_SOFTMKEY_SFK3 (3UL)
#define KEYMAN_SOFTMKEY_SFK4 (4UL)
#define KEYMAN_SOFTMKEY_SFK5 (5UL)
#define KEYMAN_SOFTMKEY_SFK6 (6UL)
#define KEYMAN_SOFTMKEY_SFK7 (7UL)

/* SOFTPKEY register group index macro definition */
#define KEYMAN_SOFTPKEY_SPK0 (0UL)
#define KEYMAN_SOFTPKEY_SPK1 (1UL)
#define KEYMAN_SOFTPKEY_SPK2 (2UL)
#define KEYMAN_SOFTPKEY_SPK3 (3UL)
#define KEYMAN_SOFTPKEY_SPK4 (4UL)
#define KEYMAN_SOFTPKEY_SPK5 (5UL)
#define KEYMAN_SOFTPKEY_SPK6 (6UL)
#define KEYMAN_SOFTPKEY_SPK7 (7UL)


#endif /* HPM_KEYMAN_H */
