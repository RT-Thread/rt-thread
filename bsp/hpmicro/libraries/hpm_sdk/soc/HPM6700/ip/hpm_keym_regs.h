/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_KEYM_H
#define HPM_KEYM_H

typedef struct {
    __RW uint32_t SOFTMKEY[8];                 /* 0x0 - 0x1C: software set symmetric key */
    __RW uint32_t SOFTPKEY[8];                 /* 0x20 - 0x3C: system asymmetric key */
    __RW uint32_t SEC_KEY_CTL;                 /* 0x40: secure key generation */
    __RW uint32_t NSC_KEY_CTL;                 /* 0x44: non-secure key generation */
    __RW uint32_t RNG;                         /* 0x48: Random number interface behavior */
    __RW uint32_t READ_CONTROL;                /* 0x4C: key read out control */
} KEYM_Type;


/* Bitfield definition for register array: SOFTMKEY */
/*
 * KEY (RW)
 *
 * software symmetric key
 * key will be scambled to 4 variants for software to use, and replicable on same chip.
 * scramble keys are chip different, and not replicable on different chip
 * must be write sequencely from 0 - 7, otherwise key value will be treated as all 0
 */
#define KEYM_SOFTMKEY_KEY_MASK (0xFFFFFFFFUL)
#define KEYM_SOFTMKEY_KEY_SHIFT (0U)
#define KEYM_SOFTMKEY_KEY_SET(x) (((uint32_t)(x) << KEYM_SOFTMKEY_KEY_SHIFT) & KEYM_SOFTMKEY_KEY_MASK)
#define KEYM_SOFTMKEY_KEY_GET(x) (((uint32_t)(x) & KEYM_SOFTMKEY_KEY_MASK) >> KEYM_SOFTMKEY_KEY_SHIFT)

/* Bitfield definition for register array: SOFTPKEY */
/*
 * KEY (RW)
 *
 * software asymmetric key
 * key is derived from scrambles of fuse private key, software input key, SRK, and system security status.
 * This key os read once, sencondary read will read out 0
 */
#define KEYM_SOFTPKEY_KEY_MASK (0xFFFFFFFFUL)
#define KEYM_SOFTPKEY_KEY_SHIFT (0U)
#define KEYM_SOFTPKEY_KEY_SET(x) (((uint32_t)(x) << KEYM_SOFTPKEY_KEY_SHIFT) & KEYM_SOFTPKEY_KEY_MASK)
#define KEYM_SOFTPKEY_KEY_GET(x) (((uint32_t)(x) & KEYM_SOFTPKEY_KEY_MASK) >> KEYM_SOFTPKEY_KEY_SHIFT)

/* Bitfield definition for register: SEC_KEY_CTL */
/*
 * LOCK_SEC_CTL (RW)
 *
 * block secure state key setting being changed
 */
#define KEYM_SEC_KEY_CTL_LOCK_SEC_CTL_MASK (0x80000000UL)
#define KEYM_SEC_KEY_CTL_LOCK_SEC_CTL_SHIFT (31U)
#define KEYM_SEC_KEY_CTL_LOCK_SEC_CTL_SET(x) (((uint32_t)(x) << KEYM_SEC_KEY_CTL_LOCK_SEC_CTL_SHIFT) & KEYM_SEC_KEY_CTL_LOCK_SEC_CTL_MASK)
#define KEYM_SEC_KEY_CTL_LOCK_SEC_CTL_GET(x) (((uint32_t)(x) & KEYM_SEC_KEY_CTL_LOCK_SEC_CTL_MASK) >> KEYM_SEC_KEY_CTL_LOCK_SEC_CTL_SHIFT)

/*
 * SK_VAL (RO)
 *
 * session key valid
 * 0: session key is all 0's and not usable
 * 1: session key is valid
 */
#define KEYM_SEC_KEY_CTL_SK_VAL_MASK (0x10000UL)
#define KEYM_SEC_KEY_CTL_SK_VAL_SHIFT (16U)
#define KEYM_SEC_KEY_CTL_SK_VAL_GET(x) (((uint32_t)(x) & KEYM_SEC_KEY_CTL_SK_VAL_MASK) >> KEYM_SEC_KEY_CTL_SK_VAL_SHIFT)

/*
 * SMK_SEL (RW)
 *
 * software symmetric key selection
 * 0: use origin value in software symmetric key
 * 1: use scramble version of software symmetric key
 */
#define KEYM_SEC_KEY_CTL_SMK_SEL_MASK (0x1000U)
#define KEYM_SEC_KEY_CTL_SMK_SEL_SHIFT (12U)
#define KEYM_SEC_KEY_CTL_SMK_SEL_SET(x) (((uint32_t)(x) << KEYM_SEC_KEY_CTL_SMK_SEL_SHIFT) & KEYM_SEC_KEY_CTL_SMK_SEL_MASK)
#define KEYM_SEC_KEY_CTL_SMK_SEL_GET(x) (((uint32_t)(x) & KEYM_SEC_KEY_CTL_SMK_SEL_MASK) >> KEYM_SEC_KEY_CTL_SMK_SEL_SHIFT)

/*
 * ZMK_SEL (RW)
 *
 * batt symmetric key selection
 * 0: use scramble version of software symmetric key
 * 1: use origin value in software symmetric key
 */
#define KEYM_SEC_KEY_CTL_ZMK_SEL_MASK (0x100U)
#define KEYM_SEC_KEY_CTL_ZMK_SEL_SHIFT (8U)
#define KEYM_SEC_KEY_CTL_ZMK_SEL_SET(x) (((uint32_t)(x) << KEYM_SEC_KEY_CTL_ZMK_SEL_SHIFT) & KEYM_SEC_KEY_CTL_ZMK_SEL_MASK)
#define KEYM_SEC_KEY_CTL_ZMK_SEL_GET(x) (((uint32_t)(x) & KEYM_SEC_KEY_CTL_ZMK_SEL_MASK) >> KEYM_SEC_KEY_CTL_ZMK_SEL_SHIFT)

/*
 * FMK_SEL (RW)
 *
 * fuse symmetric key selection
 * 0: use scramble version of fuse symmetric key
 * 1: use alnertave scramble of fuse symmetric key
 */
#define KEYM_SEC_KEY_CTL_FMK_SEL_MASK (0x10U)
#define KEYM_SEC_KEY_CTL_FMK_SEL_SHIFT (4U)
#define KEYM_SEC_KEY_CTL_FMK_SEL_SET(x) (((uint32_t)(x) << KEYM_SEC_KEY_CTL_FMK_SEL_SHIFT) & KEYM_SEC_KEY_CTL_FMK_SEL_MASK)
#define KEYM_SEC_KEY_CTL_FMK_SEL_GET(x) (((uint32_t)(x) & KEYM_SEC_KEY_CTL_FMK_SEL_MASK) >> KEYM_SEC_KEY_CTL_FMK_SEL_SHIFT)

/*
 * KEY_SEL (RW)
 *
 * secure symmtric key synthesize setting, key is a XOR of following
 * bit0: fuse mk, 0: not selected, 1:selected
 * bit1: zmk from batt, 0: not selected, 1:selected
 * bit2: software key 0: not selected, 1:selected
 */
#define KEYM_SEC_KEY_CTL_KEY_SEL_MASK (0x7U)
#define KEYM_SEC_KEY_CTL_KEY_SEL_SHIFT (0U)
#define KEYM_SEC_KEY_CTL_KEY_SEL_SET(x) (((uint32_t)(x) << KEYM_SEC_KEY_CTL_KEY_SEL_SHIFT) & KEYM_SEC_KEY_CTL_KEY_SEL_MASK)
#define KEYM_SEC_KEY_CTL_KEY_SEL_GET(x) (((uint32_t)(x) & KEYM_SEC_KEY_CTL_KEY_SEL_MASK) >> KEYM_SEC_KEY_CTL_KEY_SEL_SHIFT)

/* Bitfield definition for register: NSC_KEY_CTL */
/*
 * LOCK_NSC_CTL (RW)
 *
 * block non-secure state key setting being changed
 */
#define KEYM_NSC_KEY_CTL_LOCK_NSC_CTL_MASK (0x80000000UL)
#define KEYM_NSC_KEY_CTL_LOCK_NSC_CTL_SHIFT (31U)
#define KEYM_NSC_KEY_CTL_LOCK_NSC_CTL_SET(x) (((uint32_t)(x) << KEYM_NSC_KEY_CTL_LOCK_NSC_CTL_SHIFT) & KEYM_NSC_KEY_CTL_LOCK_NSC_CTL_MASK)
#define KEYM_NSC_KEY_CTL_LOCK_NSC_CTL_GET(x) (((uint32_t)(x) & KEYM_NSC_KEY_CTL_LOCK_NSC_CTL_MASK) >> KEYM_NSC_KEY_CTL_LOCK_NSC_CTL_SHIFT)

/*
 * SK_VAL (RO)
 *
 * session key valid
 * 0: session key is all 0's and not usable
 * 1: session key is valid
 */
#define KEYM_NSC_KEY_CTL_SK_VAL_MASK (0x10000UL)
#define KEYM_NSC_KEY_CTL_SK_VAL_SHIFT (16U)
#define KEYM_NSC_KEY_CTL_SK_VAL_GET(x) (((uint32_t)(x) & KEYM_NSC_KEY_CTL_SK_VAL_MASK) >> KEYM_NSC_KEY_CTL_SK_VAL_SHIFT)

/*
 * SMK_SEL (RW)
 *
 * software symmetric key selection
 * 0: use scramble version of software symmetric key
 * 1: use origin value in software symmetric key
 */
#define KEYM_NSC_KEY_CTL_SMK_SEL_MASK (0x1000U)
#define KEYM_NSC_KEY_CTL_SMK_SEL_SHIFT (12U)
#define KEYM_NSC_KEY_CTL_SMK_SEL_SET(x) (((uint32_t)(x) << KEYM_NSC_KEY_CTL_SMK_SEL_SHIFT) & KEYM_NSC_KEY_CTL_SMK_SEL_MASK)
#define KEYM_NSC_KEY_CTL_SMK_SEL_GET(x) (((uint32_t)(x) & KEYM_NSC_KEY_CTL_SMK_SEL_MASK) >> KEYM_NSC_KEY_CTL_SMK_SEL_SHIFT)

/*
 * ZMK_SEL (RW)
 *
 * batt symmetric key selection
 * 0: use scramble version of software symmetric key
 * 1: use origin value in software symmetric key
 */
#define KEYM_NSC_KEY_CTL_ZMK_SEL_MASK (0x100U)
#define KEYM_NSC_KEY_CTL_ZMK_SEL_SHIFT (8U)
#define KEYM_NSC_KEY_CTL_ZMK_SEL_SET(x) (((uint32_t)(x) << KEYM_NSC_KEY_CTL_ZMK_SEL_SHIFT) & KEYM_NSC_KEY_CTL_ZMK_SEL_MASK)
#define KEYM_NSC_KEY_CTL_ZMK_SEL_GET(x) (((uint32_t)(x) & KEYM_NSC_KEY_CTL_ZMK_SEL_MASK) >> KEYM_NSC_KEY_CTL_ZMK_SEL_SHIFT)

/*
 * FMK_SEL (RW)
 *
 * fuse symmetric key selection
 * 0: use scramble version of fuse symmetric key
 * 1: use origin value in fuse symmetric key
 */
#define KEYM_NSC_KEY_CTL_FMK_SEL_MASK (0x10U)
#define KEYM_NSC_KEY_CTL_FMK_SEL_SHIFT (4U)
#define KEYM_NSC_KEY_CTL_FMK_SEL_SET(x) (((uint32_t)(x) << KEYM_NSC_KEY_CTL_FMK_SEL_SHIFT) & KEYM_NSC_KEY_CTL_FMK_SEL_MASK)
#define KEYM_NSC_KEY_CTL_FMK_SEL_GET(x) (((uint32_t)(x) & KEYM_NSC_KEY_CTL_FMK_SEL_MASK) >> KEYM_NSC_KEY_CTL_FMK_SEL_SHIFT)

/*
 * KEY_SEL (RW)
 *
 * non-secure symmtric key synthesize setting, key is a XOR of following
 * bit0: fuse mk, 0: not selected, 1:selected
 * bit1: zmk from batt, 0: not selected, 1:selected
 * bit2: software key 0: not selected, 1:selected
 */
#define KEYM_NSC_KEY_CTL_KEY_SEL_MASK (0x7U)
#define KEYM_NSC_KEY_CTL_KEY_SEL_SHIFT (0U)
#define KEYM_NSC_KEY_CTL_KEY_SEL_SET(x) (((uint32_t)(x) << KEYM_NSC_KEY_CTL_KEY_SEL_SHIFT) & KEYM_NSC_KEY_CTL_KEY_SEL_MASK)
#define KEYM_NSC_KEY_CTL_KEY_SEL_GET(x) (((uint32_t)(x) & KEYM_NSC_KEY_CTL_KEY_SEL_MASK) >> KEYM_NSC_KEY_CTL_KEY_SEL_SHIFT)

/* Bitfield definition for register: RNG */
/*
 * BLOCK_RNG_XOR (RW)
 *
 * block RNG_XOR bit from changing, if this bit is written to 1, it will hold 1 until next reset
 * 0: RNG_XOR can be changed by software
 * 1: RNG_XOR ignore software change from software
 */
#define KEYM_RNG_BLOCK_RNG_XOR_MASK (0x10000UL)
#define KEYM_RNG_BLOCK_RNG_XOR_SHIFT (16U)
#define KEYM_RNG_BLOCK_RNG_XOR_SET(x) (((uint32_t)(x) << KEYM_RNG_BLOCK_RNG_XOR_SHIFT) & KEYM_RNG_BLOCK_RNG_XOR_MASK)
#define KEYM_RNG_BLOCK_RNG_XOR_GET(x) (((uint32_t)(x) & KEYM_RNG_BLOCK_RNG_XOR_MASK) >> KEYM_RNG_BLOCK_RNG_XOR_SHIFT)

/*
 * RNG_XOR (RW)
 *
 * control how SFK is accepted from random number generator
 * 0: SFK value replaced by random number input
 * 1: SFK value exclusive or with random number input,this help generate random number using 2 rings inside RNG
 */
#define KEYM_RNG_RNG_XOR_MASK (0x1U)
#define KEYM_RNG_RNG_XOR_SHIFT (0U)
#define KEYM_RNG_RNG_XOR_SET(x) (((uint32_t)(x) << KEYM_RNG_RNG_XOR_SHIFT) & KEYM_RNG_RNG_XOR_MASK)
#define KEYM_RNG_RNG_XOR_GET(x) (((uint32_t)(x) & KEYM_RNG_RNG_XOR_MASK) >> KEYM_RNG_RNG_XOR_SHIFT)

/* Bitfield definition for register: READ_CONTROL */
/*
 * BLOCK_PK_READ (RW)
 *
 * asymmetric key readout control, if this bit is written to 1, it will hold 1 until next reset
 * 0: key can be read out
 * 1: key cannot be read out
 */
#define KEYM_READ_CONTROL_BLOCK_PK_READ_MASK (0x10000UL)
#define KEYM_READ_CONTROL_BLOCK_PK_READ_SHIFT (16U)
#define KEYM_READ_CONTROL_BLOCK_PK_READ_SET(x) (((uint32_t)(x) << KEYM_READ_CONTROL_BLOCK_PK_READ_SHIFT) & KEYM_READ_CONTROL_BLOCK_PK_READ_MASK)
#define KEYM_READ_CONTROL_BLOCK_PK_READ_GET(x) (((uint32_t)(x) & KEYM_READ_CONTROL_BLOCK_PK_READ_MASK) >> KEYM_READ_CONTROL_BLOCK_PK_READ_SHIFT)

/*
 * BLOCK_SMK_READ (RW)
 *
 * symmetric key readout control, if this bit is written to 1, it will hold 1 until next reset
 * 0: key can be read out
 * 1: key cannot be read out
 */
#define KEYM_READ_CONTROL_BLOCK_SMK_READ_MASK (0x1U)
#define KEYM_READ_CONTROL_BLOCK_SMK_READ_SHIFT (0U)
#define KEYM_READ_CONTROL_BLOCK_SMK_READ_SET(x) (((uint32_t)(x) << KEYM_READ_CONTROL_BLOCK_SMK_READ_SHIFT) & KEYM_READ_CONTROL_BLOCK_SMK_READ_MASK)
#define KEYM_READ_CONTROL_BLOCK_SMK_READ_GET(x) (((uint32_t)(x) & KEYM_READ_CONTROL_BLOCK_SMK_READ_MASK) >> KEYM_READ_CONTROL_BLOCK_SMK_READ_SHIFT)



/* SOFTMKEY register group index macro definition */
#define KEYM_SOFTMKEY_SFK0 (0UL)
#define KEYM_SOFTMKEY_SFK1 (1UL)
#define KEYM_SOFTMKEY_SFK2 (2UL)
#define KEYM_SOFTMKEY_SFK3 (3UL)
#define KEYM_SOFTMKEY_SFK4 (4UL)
#define KEYM_SOFTMKEY_SFK5 (5UL)
#define KEYM_SOFTMKEY_SFK6 (6UL)
#define KEYM_SOFTMKEY_SFK7 (7UL)

/* SOFTPKEY register group index macro definition */
#define KEYM_SOFTPKEY_SPK0 (0UL)
#define KEYM_SOFTPKEY_SPK1 (1UL)
#define KEYM_SOFTPKEY_SPK2 (2UL)
#define KEYM_SOFTPKEY_SPK3 (3UL)
#define KEYM_SOFTPKEY_SPK4 (4UL)
#define KEYM_SOFTPKEY_SPK5 (5UL)
#define KEYM_SOFTPKEY_SPK6 (6UL)
#define KEYM_SOFTPKEY_SPK7 (7UL)


#endif /* HPM_KEYM_H */
