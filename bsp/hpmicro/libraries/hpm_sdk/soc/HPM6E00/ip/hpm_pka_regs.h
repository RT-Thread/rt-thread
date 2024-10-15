/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PKA_H
#define HPM_PKA_H

typedef struct {
    __R  uint8_t  RESERVED0[49152];            /* 0x0 - 0xBFFF: Reserved */
    __RW uint32_t CTRL;                        /* 0xC000: Control Register */
    __R  uint32_t STA;                         /* 0xC004: Status Register */
    __RW uint32_t INT_EN_REG;                  /* 0xC008: Interrupt Enable Register */
    __R  uint8_t  RESERVED1[52];               /* 0xC00C - 0xC03F: Reserved */
    union {
        __RW uint32_t OP_CTRL0;                /* 0xC040: Operation Control Register 0 */
        __RW uint32_t RSA_OP_CTRL;             /* 0xC040: RSA Operation Control Register */
        __RW uint32_t ECC_OP_CTRL;             /* 0xC040: ECC Operation Control Register */
    };
    union {
        __RW uint32_t OP_CTRL1;                /* 0xC044: Operation Control Register 1 */
        __RW uint32_t RSA_KEY_SIZE;            /* 0xC044: RSA Private Key Size Register */
        __RW uint32_t ECC_NP0_ORDER_N;         /* 0xC044: ECC Montgomery Parameter NP0 for Order N Register */
    };
    union {
        __RW uint32_t OP_CTRL2;                /* 0xC048: Operation Control Register 2 */
        __RW uint32_t RSA_MONT_N_SIZE;         /* 0xC048: RSA Parameter N Size Register */
        __RW uint32_t ECC_P_SIZE;              /* 0xC048: ECC Parameter P Size Register */
    };
    union {
        __RW uint32_t OP_CTRL3;                /* 0xC04C: Operation Control Register 3 */
        __R  uint32_t RSA_MONT_R_SIZE;         /* 0xC04C: RSA Montgomery Parameter R Size Register */
        __RW uint32_t ECC_MONT_R_SIZE;         /* 0xC04C: ECC Montgomery Parameter R Size Register */
    };
    union {
        __RW uint32_t OP_CTRL4;                /* 0xC050: Operation Control Register 4 */
        __R  uint32_t RSA_MONT_NP0;            /* 0xC050: RSA Montgomery Parameter NP0 Register */
        __RW uint32_t ECC_MONT_NP0;            /* 0xC050: ECC Montgomery Parameter NP0 Register */
    };
    union {
        __RW uint32_t OP_CTRL5;                /* 0xC054: Operation Control Register 5 */
        __RW uint32_t RSA_MONT_R2_MOD_N_PTR;   /* 0xC054: RSA Montgomery Parameter R2N Register */
        __RW uint32_t ECC_MONT_R2_MOD_P_PTR;   /* 0xC054: ECC Montgomery Parameter R2P Register */
    };
    union {
        __RW uint32_t OP_CTRL6;                /* 0xC058: Operation Control Register 6 */
        __RW uint32_t RSA_BIG_PRIME_PROD;      /* 0xC058: RSA Public Parameter N Register */
        __RW uint32_t ECC_A;                   /* 0xC058: ECC Public Parameter A Register */
    };
    union {
        __RW uint32_t OP_CTRL7;                /* 0xC05C: Operation Control Register 7 */
        __RW uint32_t RSA_PUB_KEY;             /* 0xC05C: RSA Public Key Register */
        __RW uint32_t ECC_B;                   /* 0xC05C: ECC Public Parameter B Register */
    };
    union {
        __RW uint32_t OP_CTRL8;                /* 0xC060: Operation Control Register 8 */
        __RW uint32_t ECC_P;                   /* 0xC060: ECC Public Parameter P Register */
    };
    union {
        __RW uint32_t OP_CTRL9;                /* 0xC064: Operation Control Register 9 */
        __RW uint32_t RSA_M;                   /* 0xC064: RSA M Register */
        __RW uint32_t ECC_GEN_X;               /* 0xC064: ECC Public Parameter GX Register */
    };
    union {
        __RW uint32_t OP_CTRLA;                /* 0xC068: Operation Control Register A */
        __RW uint32_t RSA_TM0;                 /* 0xC068: RSA TM0 Register */
        __RW uint32_t ECC_GEN_Y;               /* 0xC068: ECC Public Parameter GY Register */
    };
    union {
        __RW uint32_t OP_CTRLB;                /* 0xC06C: Operation Control Register B */
        __RW uint32_t RSA_TM1;                 /* 0xC06C: RSA TM1 Register */
        __RW uint32_t ECC_PUB_X;               /* 0xC06C: ECC Public Parameter PX Register */
    };
    union {
        __RW uint32_t OP_CTRLC;                /* 0xC070: Operation Control Register C */
        __RW uint32_t RSA_O;                   /* 0xC070: RSA O Register */
        __RW uint32_t ECC_PUB_Y;               /* 0xC070: ECC Public Parameter PY Register */
    };
    union {
        __RW uint32_t OP_CTRLD;                /* 0xC074: Operation Control Register D */
        __RW uint32_t RSA_PRIV_KEY;            /* 0xC074: RSA Private Parameter d Register */
        __RW uint32_t ECC_PRIV_K;              /* 0xC074: ECC Private Parameter K Register */
    };
    union {
        __RW uint32_t OP_CTRLE;                /* 0xC078: Operation Control Register E */
        __RW uint32_t ECC_GENORD_N;            /* 0xC078: ECC Public Parameter Order N Register */
    };
    union {
        __RW uint32_t OP_CTRLF;                /* 0xC07C: Operation Control Register F */
        __RW uint32_t ECC_R2N_ORDER_N;         /* 0xC07C: ECC Montgomery Parameter R2N Register */
    };
} PKA_Type;


/* Bitfield definition for register: CTRL */
/*
 * DIS_CIPHER (RW)
 *
 * Sticky at 1.
 * 1: Disable Cipher Operation. When Disabled, clear all memory contents, and run in infinite loop. Only module reset can recover the module.
 */
#define PKA_CTRL_DIS_CIPHER_MASK (0x80000000UL)
#define PKA_CTRL_DIS_CIPHER_SHIFT (31U)
#define PKA_CTRL_DIS_CIPHER_SET(x) (((uint32_t)(x) << PKA_CTRL_DIS_CIPHER_SHIFT) & PKA_CTRL_DIS_CIPHER_MASK)
#define PKA_CTRL_DIS_CIPHER_GET(x) (((uint32_t)(x) & PKA_CTRL_DIS_CIPHER_MASK) >> PKA_CTRL_DIS_CIPHER_SHIFT)

/*
 * PRIM_OP (RW)
 *
 * 1: Run primitive operations.
 * 0: Run composite operations
 */
#define PKA_CTRL_PRIM_OP_MASK (0x40000000UL)
#define PKA_CTRL_PRIM_OP_SHIFT (30U)
#define PKA_CTRL_PRIM_OP_SET(x) (((uint32_t)(x) << PKA_CTRL_PRIM_OP_SHIFT) & PKA_CTRL_PRIM_OP_MASK)
#define PKA_CTRL_PRIM_OP_GET(x) (((uint32_t)(x) & PKA_CTRL_PRIM_OP_MASK) >> PKA_CTRL_PRIM_OP_SHIFT)

/*
 * SFTRST (RW)
 *
 * Software reset
 */
#define PKA_CTRL_SFTRST_MASK (0x400U)
#define PKA_CTRL_SFTRST_SHIFT (10U)
#define PKA_CTRL_SFTRST_SET(x) (((uint32_t)(x) << PKA_CTRL_SFTRST_SHIFT) & PKA_CTRL_SFTRST_MASK)
#define PKA_CTRL_SFTRST_GET(x) (((uint32_t)(x) & PKA_CTRL_SFTRST_MASK) >> PKA_CTRL_SFTRST_SHIFT)

/*
 * CRYPTO_OP (RW)
 *
 * When CTRL[PRIM_OP]=1,
 * 0: Modulus MULT
 * 0x1: Modulus ADD
 * 0x2: Modulus MINUS
 * 0x3: GCD
 * 0x4: memory copy (address range should not overlap, no check of this)
 * 0x5: asr1
 * 0x6: sr1
 * 0x7: bn_len
 * 0x8: DeProj
 * 0x9: disable memory copy
 * 0xA. Find BN modulus
 * 0xC. KEY2SDP (copy key from internal to sdp interface)
 * 0xD. ECCPointAdd
 * 0xE. SCL_MOD (cal h*k mod n, GFp domain)
 * When CTRL[PRIM_OP]=0,
 * 0x0: ini the PKA parameters.  This is to store the config parameters that are assigned in interface regs, and do norm2mont transfers to the related ECC A/B/GX/GY.
 * 0x2: For ECC, do scalar multiplication. For RSA, do power modulus. So this mode can be used to generate the public key.
 *     For RSA, Before entering key generation, whole mem rd is  blocked. --> During key generation. Np is p, pub_key is q, --> prod is p*q, encrpt_msg is phi, Np and pub_key is cleared --> then priv_key is priv_key, --> then pub_key is cal --> encrpt_msg is cleaed --> mem blockage removed.
 *     For ECC, Before entering key generation, whole mem rd is  blocked. --> check A/B/P are valid values --> randomly choose GX --> search for GY --> cal order N, stored in NP --> if N is great enough, randomly choose private K -->  cal PX, PY --> NP is cleaed --> mem blockage removed.
 * 0x5: SM2 DSA gen (must use internal stored ECC parameters)
 * 0xC: SM2 DSA verify (must use internal stored ECC parameters, with PAX, PAY not in mont type yet)
 * 0x1C: SM2 DSA verify (with PAX, PAY already in mont type)
 */
#define PKA_CTRL_CRYPTO_OP_MASK (0xF8U)
#define PKA_CTRL_CRYPTO_OP_SHIFT (3U)
#define PKA_CTRL_CRYPTO_OP_SET(x) (((uint32_t)(x) << PKA_CTRL_CRYPTO_OP_SHIFT) & PKA_CTRL_CRYPTO_OP_MASK)
#define PKA_CTRL_CRYPTO_OP_GET(x) (((uint32_t)(x) & PKA_CTRL_CRYPTO_OP_MASK) >> PKA_CTRL_CRYPTO_OP_SHIFT)

/*
 * OP_ACTIVE (RW)
 *
 * 1: operation active. Self clear
 * 0: operation not active
 */
#define PKA_CTRL_OP_ACTIVE_MASK (0x4U)
#define PKA_CTRL_OP_ACTIVE_SHIFT (2U)
#define PKA_CTRL_OP_ACTIVE_SET(x) (((uint32_t)(x) << PKA_CTRL_OP_ACTIVE_SHIFT) & PKA_CTRL_OP_ACTIVE_MASK)
#define PKA_CTRL_OP_ACTIVE_GET(x) (((uint32_t)(x) & PKA_CTRL_OP_ACTIVE_MASK) >> PKA_CTRL_OP_ACTIVE_SHIFT)

/*
 * ECC1_RSA0 (RW)
 *
 * crypto_op
 */
#define PKA_CTRL_ECC1_RSA0_MASK (0x2U)
#define PKA_CTRL_ECC1_RSA0_SHIFT (1U)
#define PKA_CTRL_ECC1_RSA0_SET(x) (((uint32_t)(x) << PKA_CTRL_ECC1_RSA0_SHIFT) & PKA_CTRL_ECC1_RSA0_MASK)
#define PKA_CTRL_ECC1_RSA0_GET(x) (((uint32_t)(x) & PKA_CTRL_ECC1_RSA0_MASK) >> PKA_CTRL_ECC1_RSA0_SHIFT)

/*
 * PKA_EN (RW)
 *
 * 1b-Enabled
 */
#define PKA_CTRL_PKA_EN_MASK (0x1U)
#define PKA_CTRL_PKA_EN_SHIFT (0U)
#define PKA_CTRL_PKA_EN_SET(x) (((uint32_t)(x) << PKA_CTRL_PKA_EN_SHIFT) & PKA_CTRL_PKA_EN_MASK)
#define PKA_CTRL_PKA_EN_GET(x) (((uint32_t)(x) & PKA_CTRL_PKA_EN_MASK) >> PKA_CTRL_PKA_EN_SHIFT)

/* Bitfield definition for register: STA */
/*
 * OSTA (RO)
 *
 * Multiplexed STA. This is the STA from internal firmware.
 */
#define PKA_STA_OSTA_MASK (0xFFFF0000UL)
#define PKA_STA_OSTA_SHIFT (16U)
#define PKA_STA_OSTA_GET(x) (((uint32_t)(x) & PKA_STA_OSTA_MASK) >> PKA_STA_OSTA_SHIFT)

/*
 * INI_DONE (RO)
 *
 * 1: Initialization Done.
 * 0: Initialization not done.
 */
#define PKA_STA_INI_DONE_MASK (0x10U)
#define PKA_STA_INI_DONE_SHIFT (4U)
#define PKA_STA_INI_DONE_GET(x) (((uint32_t)(x) & PKA_STA_INI_DONE_MASK) >> PKA_STA_INI_DONE_SHIFT)

/*
 * OP_DONE (RO)
 *
 * Operation Done
 */
#define PKA_STA_OP_DONE_MASK (0x1U)
#define PKA_STA_OP_DONE_SHIFT (0U)
#define PKA_STA_OP_DONE_GET(x) (((uint32_t)(x) & PKA_STA_OP_DONE_MASK) >> PKA_STA_OP_DONE_SHIFT)

/* Bitfield definition for register: INT_EN_REG */
/*
 * OSTA_IE (RW)
 *
 * interrupt enale for Multiplexed STA bits.
 */
#define PKA_INT_EN_REG_OSTA_IE_MASK (0xFFFF0000UL)
#define PKA_INT_EN_REG_OSTA_IE_SHIFT (16U)
#define PKA_INT_EN_REG_OSTA_IE_SET(x) (((uint32_t)(x) << PKA_INT_EN_REG_OSTA_IE_SHIFT) & PKA_INT_EN_REG_OSTA_IE_MASK)
#define PKA_INT_EN_REG_OSTA_IE_GET(x) (((uint32_t)(x) & PKA_INT_EN_REG_OSTA_IE_MASK) >> PKA_INT_EN_REG_OSTA_IE_SHIFT)

/*
 * OP_DONE_IE (RW)
 *
 * interrupt enale
 */
#define PKA_INT_EN_REG_OP_DONE_IE_MASK (0x1U)
#define PKA_INT_EN_REG_OP_DONE_IE_SHIFT (0U)
#define PKA_INT_EN_REG_OP_DONE_IE_SET(x) (((uint32_t)(x) << PKA_INT_EN_REG_OP_DONE_IE_SHIFT) & PKA_INT_EN_REG_OP_DONE_IE_MASK)
#define PKA_INT_EN_REG_OP_DONE_IE_GET(x) (((uint32_t)(x) & PKA_INT_EN_REG_OP_DONE_IE_MASK) >> PKA_INT_EN_REG_OP_DONE_IE_SHIFT)

/* Bitfield definition for register: OP_CTRL0 */
/*
 * INFO_BLK_IDX (RW)
 *
 * The loc index of related information for storage or retrieve
 * bit 1:0 -- the memory location
 * bit 4:2 -- the info idx
 */
#define PKA_OP_CTRL0_INFO_BLK_IDX_MASK (0xF8000000UL)
#define PKA_OP_CTRL0_INFO_BLK_IDX_SHIFT (27U)
#define PKA_OP_CTRL0_INFO_BLK_IDX_SET(x) (((uint32_t)(x) << PKA_OP_CTRL0_INFO_BLK_IDX_SHIFT) & PKA_OP_CTRL0_INFO_BLK_IDX_MASK)
#define PKA_OP_CTRL0_INFO_BLK_IDX_GET(x) (((uint32_t)(x) & PKA_OP_CTRL0_INFO_BLK_IDX_MASK) >> PKA_OP_CTRL0_INFO_BLK_IDX_SHIFT)

/*
 * INFO_OP (RW)
 *
 * 1: Storage. The following info will be stored into the internal memory. Some Mont transform will be done. So some stored info will be in Mont format.
 * 0: Retrieve. The stored info will be used instead of the following configurations.
 */
#define PKA_OP_CTRL0_INFO_OP_MASK (0x4000000UL)
#define PKA_OP_CTRL0_INFO_OP_SHIFT (26U)
#define PKA_OP_CTRL0_INFO_OP_SET(x) (((uint32_t)(x) << PKA_OP_CTRL0_INFO_OP_SHIFT) & PKA_OP_CTRL0_INFO_OP_MASK)
#define PKA_OP_CTRL0_INFO_OP_GET(x) (((uint32_t)(x) & PKA_OP_CTRL0_INFO_OP_MASK) >> PKA_OP_CTRL0_INFO_OP_SHIFT)

/* Bitfield definition for register: RSA_OP_CTRL */
/*
 * INFO_BLK_IDX (RW)
 *
 * The loc index of related information for storage or retrieve
 * bit 1:0 -- the memory location
 * bit 4:2 -- the info idx
 */
#define PKA_RSA_OP_CTRL_INFO_BLK_IDX_MASK (0xF8000000UL)
#define PKA_RSA_OP_CTRL_INFO_BLK_IDX_SHIFT (27U)
#define PKA_RSA_OP_CTRL_INFO_BLK_IDX_SET(x) (((uint32_t)(x) << PKA_RSA_OP_CTRL_INFO_BLK_IDX_SHIFT) & PKA_RSA_OP_CTRL_INFO_BLK_IDX_MASK)
#define PKA_RSA_OP_CTRL_INFO_BLK_IDX_GET(x) (((uint32_t)(x) & PKA_RSA_OP_CTRL_INFO_BLK_IDX_MASK) >> PKA_RSA_OP_CTRL_INFO_BLK_IDX_SHIFT)

/*
 * INFO_OP (RW)
 *
 * 1: Storage. The following info will be stored into the internal memory. Some Mont transform will be done. So some stored info will be in Mont format.
 * 0: Retrieve. The stored info will be used instead of the following configurations.
 */
#define PKA_RSA_OP_CTRL_INFO_OP_MASK (0x4000000UL)
#define PKA_RSA_OP_CTRL_INFO_OP_SHIFT (26U)
#define PKA_RSA_OP_CTRL_INFO_OP_SET(x) (((uint32_t)(x) << PKA_RSA_OP_CTRL_INFO_OP_SHIFT) & PKA_RSA_OP_CTRL_INFO_OP_MASK)
#define PKA_RSA_OP_CTRL_INFO_OP_GET(x) (((uint32_t)(x) & PKA_RSA_OP_CTRL_INFO_OP_MASK) >> PKA_RSA_OP_CTRL_INFO_OP_SHIFT)

/*
 * EQUALIZED_CTRL (RW)
 *
 * the prcessing will be in equalized state. Can only be used for PKA[RSA_BIG_PRIME_PROD] with a size smaller than or equal to 2048.
 */
#define PKA_RSA_OP_CTRL_EQUALIZED_CTRL_MASK (0x2U)
#define PKA_RSA_OP_CTRL_EQUALIZED_CTRL_SHIFT (1U)
#define PKA_RSA_OP_CTRL_EQUALIZED_CTRL_SET(x) (((uint32_t)(x) << PKA_RSA_OP_CTRL_EQUALIZED_CTRL_SHIFT) & PKA_RSA_OP_CTRL_EQUALIZED_CTRL_MASK)
#define PKA_RSA_OP_CTRL_EQUALIZED_CTRL_GET(x) (((uint32_t)(x) & PKA_RSA_OP_CTRL_EQUALIZED_CTRL_MASK) >> PKA_RSA_OP_CTRL_EQUALIZED_CTRL_SHIFT)

/*
 * ECC1_RSA0 (RW)
 *
 * Should be 0 to select RSA
 */
#define PKA_RSA_OP_CTRL_ECC1_RSA0_MASK (0x1U)
#define PKA_RSA_OP_CTRL_ECC1_RSA0_SHIFT (0U)
#define PKA_RSA_OP_CTRL_ECC1_RSA0_SET(x) (((uint32_t)(x) << PKA_RSA_OP_CTRL_ECC1_RSA0_SHIFT) & PKA_RSA_OP_CTRL_ECC1_RSA0_MASK)
#define PKA_RSA_OP_CTRL_ECC1_RSA0_GET(x) (((uint32_t)(x) & PKA_RSA_OP_CTRL_ECC1_RSA0_MASK) >> PKA_RSA_OP_CTRL_ECC1_RSA0_SHIFT)

/* Bitfield definition for register: ECC_OP_CTRL */
/*
 * INFO_BLK_IDX (RW)
 *
 * The loc index of related information for storage or retrieve
 * bit 1:0 -- the memory location
 * bit 4:2 -- the info idx
 */
#define PKA_ECC_OP_CTRL_INFO_BLK_IDX_MASK (0xF8000000UL)
#define PKA_ECC_OP_CTRL_INFO_BLK_IDX_SHIFT (27U)
#define PKA_ECC_OP_CTRL_INFO_BLK_IDX_SET(x) (((uint32_t)(x) << PKA_ECC_OP_CTRL_INFO_BLK_IDX_SHIFT) & PKA_ECC_OP_CTRL_INFO_BLK_IDX_MASK)
#define PKA_ECC_OP_CTRL_INFO_BLK_IDX_GET(x) (((uint32_t)(x) & PKA_ECC_OP_CTRL_INFO_BLK_IDX_MASK) >> PKA_ECC_OP_CTRL_INFO_BLK_IDX_SHIFT)

/*
 * INFO_OP (RW)
 *
 * 1: Storage. The following info will be stored into the internal memory. Some Mont transform will be done. So some stored info will be in Mont format.
 * 0: Retrieve. The stored info will be used instead of the following configurations.
 */
#define PKA_ECC_OP_CTRL_INFO_OP_MASK (0x4000000UL)
#define PKA_ECC_OP_CTRL_INFO_OP_SHIFT (26U)
#define PKA_ECC_OP_CTRL_INFO_OP_SET(x) (((uint32_t)(x) << PKA_ECC_OP_CTRL_INFO_OP_SHIFT) & PKA_ECC_OP_CTRL_INFO_OP_MASK)
#define PKA_ECC_OP_CTRL_INFO_OP_GET(x) (((uint32_t)(x) & PKA_ECC_OP_CTRL_INFO_OP_MASK) >> PKA_ECC_OP_CTRL_INFO_OP_SHIFT)

/*
 * GF_OPT (RW)
 *
 * 1: GF2m
 * 0: GFp
 */
#define PKA_ECC_OP_CTRL_GF_OPT_MASK (0x4U)
#define PKA_ECC_OP_CTRL_GF_OPT_SHIFT (2U)
#define PKA_ECC_OP_CTRL_GF_OPT_SET(x) (((uint32_t)(x) << PKA_ECC_OP_CTRL_GF_OPT_SHIFT) & PKA_ECC_OP_CTRL_GF_OPT_MASK)
#define PKA_ECC_OP_CTRL_GF_OPT_GET(x) (((uint32_t)(x) & PKA_ECC_OP_CTRL_GF_OPT_MASK) >> PKA_ECC_OP_CTRL_GF_OPT_SHIFT)

/*
 * EQUALIZED_CTRL (RW)
 *
 * the prcessing will be in equalized state
 */
#define PKA_ECC_OP_CTRL_EQUALIZED_CTRL_MASK (0x2U)
#define PKA_ECC_OP_CTRL_EQUALIZED_CTRL_SHIFT (1U)
#define PKA_ECC_OP_CTRL_EQUALIZED_CTRL_SET(x) (((uint32_t)(x) << PKA_ECC_OP_CTRL_EQUALIZED_CTRL_SHIFT) & PKA_ECC_OP_CTRL_EQUALIZED_CTRL_MASK)
#define PKA_ECC_OP_CTRL_EQUALIZED_CTRL_GET(x) (((uint32_t)(x) & PKA_ECC_OP_CTRL_EQUALIZED_CTRL_MASK) >> PKA_ECC_OP_CTRL_EQUALIZED_CTRL_SHIFT)

/*
 * ECC1_RSA0 (RW)
 *
 * Should be 1 to select ECC
 */
#define PKA_ECC_OP_CTRL_ECC1_RSA0_MASK (0x1U)
#define PKA_ECC_OP_CTRL_ECC1_RSA0_SHIFT (0U)
#define PKA_ECC_OP_CTRL_ECC1_RSA0_SET(x) (((uint32_t)(x) << PKA_ECC_OP_CTRL_ECC1_RSA0_SHIFT) & PKA_ECC_OP_CTRL_ECC1_RSA0_MASK)
#define PKA_ECC_OP_CTRL_ECC1_RSA0_GET(x) (((uint32_t)(x) & PKA_ECC_OP_CTRL_ECC1_RSA0_MASK) >> PKA_ECC_OP_CTRL_ECC1_RSA0_SHIFT)

/* Bitfield definition for register: OP_CTRL1 */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRL1_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRL1_VAL_SHIFT (0U)
#define PKA_OP_CTRL1_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRL1_VAL_SHIFT) & PKA_OP_CTRL1_VAL_MASK)
#define PKA_OP_CTRL1_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRL1_VAL_MASK) >> PKA_OP_CTRL1_VAL_SHIFT)

/* Bitfield definition for register: RSA_KEY_SIZE */
/*
 * VAL (RW)
 *
 * The bit length-1 of RSA key (max 4096-1)
 */
#define PKA_RSA_KEY_SIZE_VAL_MASK (0x1FFFU)
#define PKA_RSA_KEY_SIZE_VAL_SHIFT (0U)
#define PKA_RSA_KEY_SIZE_VAL_SET(x) (((uint32_t)(x) << PKA_RSA_KEY_SIZE_VAL_SHIFT) & PKA_RSA_KEY_SIZE_VAL_MASK)
#define PKA_RSA_KEY_SIZE_VAL_GET(x) (((uint32_t)(x) & PKA_RSA_KEY_SIZE_VAL_MASK) >> PKA_RSA_KEY_SIZE_VAL_SHIFT)

/* Bitfield definition for register: ECC_NP0_ORDER_N */
/*
 * VAL (RW)
 *
 * The NP0 parameter for Montegomery transform of ECC order N
 */
#define PKA_ECC_NP0_ORDER_N_VAL_MASK (0xFFFFFFFFUL)
#define PKA_ECC_NP0_ORDER_N_VAL_SHIFT (0U)
#define PKA_ECC_NP0_ORDER_N_VAL_SET(x) (((uint32_t)(x) << PKA_ECC_NP0_ORDER_N_VAL_SHIFT) & PKA_ECC_NP0_ORDER_N_VAL_MASK)
#define PKA_ECC_NP0_ORDER_N_VAL_GET(x) (((uint32_t)(x) & PKA_ECC_NP0_ORDER_N_VAL_MASK) >> PKA_ECC_NP0_ORDER_N_VAL_SHIFT)

/* Bitfield definition for register: OP_CTRL2 */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRL2_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRL2_VAL_SHIFT (0U)
#define PKA_OP_CTRL2_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRL2_VAL_SHIFT) & PKA_OP_CTRL2_VAL_MASK)
#define PKA_OP_CTRL2_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRL2_VAL_MASK) >> PKA_OP_CTRL2_VAL_SHIFT)

/* Bitfield definition for register: RSA_MONT_N_SIZE */
/*
 * VAL (RW)
 *
 * The bit length of RSA N parameter
 */
#define PKA_RSA_MONT_N_SIZE_VAL_MASK (0x1FFFU)
#define PKA_RSA_MONT_N_SIZE_VAL_SHIFT (0U)
#define PKA_RSA_MONT_N_SIZE_VAL_SET(x) (((uint32_t)(x) << PKA_RSA_MONT_N_SIZE_VAL_SHIFT) & PKA_RSA_MONT_N_SIZE_VAL_MASK)
#define PKA_RSA_MONT_N_SIZE_VAL_GET(x) (((uint32_t)(x) & PKA_RSA_MONT_N_SIZE_VAL_MASK) >> PKA_RSA_MONT_N_SIZE_VAL_SHIFT)

/* Bitfield definition for register: ECC_P_SIZE */
/*
 * H_VAL (RW)
 *
 * Cofactor value
 */
#define PKA_ECC_P_SIZE_H_VAL_MASK (0xFFFF0000UL)
#define PKA_ECC_P_SIZE_H_VAL_SHIFT (16U)
#define PKA_ECC_P_SIZE_H_VAL_SET(x) (((uint32_t)(x) << PKA_ECC_P_SIZE_H_VAL_SHIFT) & PKA_ECC_P_SIZE_H_VAL_MASK)
#define PKA_ECC_P_SIZE_H_VAL_GET(x) (((uint32_t)(x) & PKA_ECC_P_SIZE_H_VAL_MASK) >> PKA_ECC_P_SIZE_H_VAL_SHIFT)

/*
 * VAL (RW)
 *
 * The bit length of ECC P parameter
 */
#define PKA_ECC_P_SIZE_VAL_MASK (0x1FFFU)
#define PKA_ECC_P_SIZE_VAL_SHIFT (0U)
#define PKA_ECC_P_SIZE_VAL_SET(x) (((uint32_t)(x) << PKA_ECC_P_SIZE_VAL_SHIFT) & PKA_ECC_P_SIZE_VAL_MASK)
#define PKA_ECC_P_SIZE_VAL_GET(x) (((uint32_t)(x) & PKA_ECC_P_SIZE_VAL_MASK) >> PKA_ECC_P_SIZE_VAL_SHIFT)

/* Bitfield definition for register: OP_CTRL3 */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRL3_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRL3_VAL_SHIFT (0U)
#define PKA_OP_CTRL3_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRL3_VAL_SHIFT) & PKA_OP_CTRL3_VAL_MASK)
#define PKA_OP_CTRL3_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRL3_VAL_MASK) >> PKA_OP_CTRL3_VAL_SHIFT)

/* Bitfield definition for register: RSA_MONT_R_SIZE */
/*
 * VAL (RE)
 *
 * The bit length of RSA R parameter for Montegomery transform. Should be equal to 32*n+1
 */
#define PKA_RSA_MONT_R_SIZE_VAL_MASK (0x1FFFU)
#define PKA_RSA_MONT_R_SIZE_VAL_SHIFT (0U)
#define PKA_RSA_MONT_R_SIZE_VAL_GET(x) (((uint32_t)(x) & PKA_RSA_MONT_R_SIZE_VAL_MASK) >> PKA_RSA_MONT_R_SIZE_VAL_SHIFT)

/* Bitfield definition for register: ECC_MONT_R_SIZE */
/*
 * KEY_SIZE (RW)
 *
 * The bit length-1 of ECC key
 */
#define PKA_ECC_MONT_R_SIZE_KEY_SIZE_MASK (0xFFFF0000UL)
#define PKA_ECC_MONT_R_SIZE_KEY_SIZE_SHIFT (16U)
#define PKA_ECC_MONT_R_SIZE_KEY_SIZE_SET(x) (((uint32_t)(x) << PKA_ECC_MONT_R_SIZE_KEY_SIZE_SHIFT) & PKA_ECC_MONT_R_SIZE_KEY_SIZE_MASK)
#define PKA_ECC_MONT_R_SIZE_KEY_SIZE_GET(x) (((uint32_t)(x) & PKA_ECC_MONT_R_SIZE_KEY_SIZE_MASK) >> PKA_ECC_MONT_R_SIZE_KEY_SIZE_SHIFT)

/*
 * VAL (RW)
 *
 * The bit length of ECC R parameter for Montegomery transform. Should be equal to 32*n+1
 */
#define PKA_ECC_MONT_R_SIZE_VAL_MASK (0x1FFFU)
#define PKA_ECC_MONT_R_SIZE_VAL_SHIFT (0U)
#define PKA_ECC_MONT_R_SIZE_VAL_SET(x) (((uint32_t)(x) << PKA_ECC_MONT_R_SIZE_VAL_SHIFT) & PKA_ECC_MONT_R_SIZE_VAL_MASK)
#define PKA_ECC_MONT_R_SIZE_VAL_GET(x) (((uint32_t)(x) & PKA_ECC_MONT_R_SIZE_VAL_MASK) >> PKA_ECC_MONT_R_SIZE_VAL_SHIFT)

/* Bitfield definition for register: OP_CTRL4 */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRL4_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRL4_VAL_SHIFT (0U)
#define PKA_OP_CTRL4_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRL4_VAL_SHIFT) & PKA_OP_CTRL4_VAL_MASK)
#define PKA_OP_CTRL4_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRL4_VAL_MASK) >> PKA_OP_CTRL4_VAL_SHIFT)

/* Bitfield definition for register: RSA_MONT_NP0 */
/*
 * VAL (RE)
 *
 * The NP0 parameter for Montegomery transform of RSA
 */
#define PKA_RSA_MONT_NP0_VAL_MASK (0xFFFFFFFFUL)
#define PKA_RSA_MONT_NP0_VAL_SHIFT (0U)
#define PKA_RSA_MONT_NP0_VAL_GET(x) (((uint32_t)(x) & PKA_RSA_MONT_NP0_VAL_MASK) >> PKA_RSA_MONT_NP0_VAL_SHIFT)

/* Bitfield definition for register: ECC_MONT_NP0 */
/*
 * VAL (RW)
 *
 * The NP0 parameter for ECC P-based Montegomery transform of ECC
 */
#define PKA_ECC_MONT_NP0_VAL_MASK (0xFFFFFFFFUL)
#define PKA_ECC_MONT_NP0_VAL_SHIFT (0U)
#define PKA_ECC_MONT_NP0_VAL_SET(x) (((uint32_t)(x) << PKA_ECC_MONT_NP0_VAL_SHIFT) & PKA_ECC_MONT_NP0_VAL_MASK)
#define PKA_ECC_MONT_NP0_VAL_GET(x) (((uint32_t)(x) & PKA_ECC_MONT_NP0_VAL_MASK) >> PKA_ECC_MONT_NP0_VAL_SHIFT)

/* Bitfield definition for register: OP_CTRL5 */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRL5_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRL5_VAL_SHIFT (0U)
#define PKA_OP_CTRL5_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRL5_VAL_SHIFT) & PKA_OP_CTRL5_VAL_MASK)
#define PKA_OP_CTRL5_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRL5_VAL_MASK) >> PKA_OP_CTRL5_VAL_SHIFT)

/* Bitfield definition for register: RSA_MONT_R2_MOD_N_PTR */
/*
 * VAL (RW)
 *
 * The address pointer value for holding the value of mod(R*R, N) for Montegomery transform
 */
#define PKA_RSA_MONT_R2_MOD_N_PTR_VAL_MASK (0x1FFFU)
#define PKA_RSA_MONT_R2_MOD_N_PTR_VAL_SHIFT (0U)
#define PKA_RSA_MONT_R2_MOD_N_PTR_VAL_SET(x) (((uint32_t)(x) << PKA_RSA_MONT_R2_MOD_N_PTR_VAL_SHIFT) & PKA_RSA_MONT_R2_MOD_N_PTR_VAL_MASK)
#define PKA_RSA_MONT_R2_MOD_N_PTR_VAL_GET(x) (((uint32_t)(x) & PKA_RSA_MONT_R2_MOD_N_PTR_VAL_MASK) >> PKA_RSA_MONT_R2_MOD_N_PTR_VAL_SHIFT)

/* Bitfield definition for register: ECC_MONT_R2_MOD_P_PTR */
/*
 * VAL (RW)
 *
 * The address pointer value for holding the value of mod(R*R, P) for Montegomery transform
 */
#define PKA_ECC_MONT_R2_MOD_P_PTR_VAL_MASK (0x1FFFU)
#define PKA_ECC_MONT_R2_MOD_P_PTR_VAL_SHIFT (0U)
#define PKA_ECC_MONT_R2_MOD_P_PTR_VAL_SET(x) (((uint32_t)(x) << PKA_ECC_MONT_R2_MOD_P_PTR_VAL_SHIFT) & PKA_ECC_MONT_R2_MOD_P_PTR_VAL_MASK)
#define PKA_ECC_MONT_R2_MOD_P_PTR_VAL_GET(x) (((uint32_t)(x) & PKA_ECC_MONT_R2_MOD_P_PTR_VAL_MASK) >> PKA_ECC_MONT_R2_MOD_P_PTR_VAL_SHIFT)

/* Bitfield definition for register: OP_CTRL6 */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRL6_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRL6_VAL_SHIFT (0U)
#define PKA_OP_CTRL6_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRL6_VAL_SHIFT) & PKA_OP_CTRL6_VAL_MASK)
#define PKA_OP_CTRL6_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRL6_VAL_MASK) >> PKA_OP_CTRL6_VAL_SHIFT)

/* Bitfield definition for register: RSA_BIG_PRIME_PROD */
/*
 * ADDR (RW)
 *
 * The starting location of RSA big prime production inside the local 256-bits blocks
 */
#define PKA_RSA_BIG_PRIME_PROD_ADDR_MASK (0x1FFFU)
#define PKA_RSA_BIG_PRIME_PROD_ADDR_SHIFT (0U)
#define PKA_RSA_BIG_PRIME_PROD_ADDR_SET(x) (((uint32_t)(x) << PKA_RSA_BIG_PRIME_PROD_ADDR_SHIFT) & PKA_RSA_BIG_PRIME_PROD_ADDR_MASK)
#define PKA_RSA_BIG_PRIME_PROD_ADDR_GET(x) (((uint32_t)(x) & PKA_RSA_BIG_PRIME_PROD_ADDR_MASK) >> PKA_RSA_BIG_PRIME_PROD_ADDR_SHIFT)

/* Bitfield definition for register: ECC_A */
/*
 * ADDR (RW)
 *
 * The address of the ECC Curve parameter A inside the local 256-bits blocks
 */
#define PKA_ECC_A_ADDR_MASK (0x1FFFU)
#define PKA_ECC_A_ADDR_SHIFT (0U)
#define PKA_ECC_A_ADDR_SET(x) (((uint32_t)(x) << PKA_ECC_A_ADDR_SHIFT) & PKA_ECC_A_ADDR_MASK)
#define PKA_ECC_A_ADDR_GET(x) (((uint32_t)(x) & PKA_ECC_A_ADDR_MASK) >> PKA_ECC_A_ADDR_SHIFT)

/* Bitfield definition for register: OP_CTRL7 */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRL7_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRL7_VAL_SHIFT (0U)
#define PKA_OP_CTRL7_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRL7_VAL_SHIFT) & PKA_OP_CTRL7_VAL_MASK)
#define PKA_OP_CTRL7_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRL7_VAL_MASK) >> PKA_OP_CTRL7_VAL_SHIFT)

/* Bitfield definition for register: RSA_PUB_KEY */
/*
 * ADDR (RW)
 *
 * The starting location of RSA public key inside the local 256-bits blocks
 */
#define PKA_RSA_PUB_KEY_ADDR_MASK (0x1FFFU)
#define PKA_RSA_PUB_KEY_ADDR_SHIFT (0U)
#define PKA_RSA_PUB_KEY_ADDR_SET(x) (((uint32_t)(x) << PKA_RSA_PUB_KEY_ADDR_SHIFT) & PKA_RSA_PUB_KEY_ADDR_MASK)
#define PKA_RSA_PUB_KEY_ADDR_GET(x) (((uint32_t)(x) & PKA_RSA_PUB_KEY_ADDR_MASK) >> PKA_RSA_PUB_KEY_ADDR_SHIFT)

/* Bitfield definition for register: ECC_B */
/*
 * ADDR (RW)
 *
 * The address of the ECC Curve parameter B inside the local 256-bits blocks
 */
#define PKA_ECC_B_ADDR_MASK (0x1FFFU)
#define PKA_ECC_B_ADDR_SHIFT (0U)
#define PKA_ECC_B_ADDR_SET(x) (((uint32_t)(x) << PKA_ECC_B_ADDR_SHIFT) & PKA_ECC_B_ADDR_MASK)
#define PKA_ECC_B_ADDR_GET(x) (((uint32_t)(x) & PKA_ECC_B_ADDR_MASK) >> PKA_ECC_B_ADDR_SHIFT)

/* Bitfield definition for register: OP_CTRL8 */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRL8_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRL8_VAL_SHIFT (0U)
#define PKA_OP_CTRL8_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRL8_VAL_SHIFT) & PKA_OP_CTRL8_VAL_MASK)
#define PKA_OP_CTRL8_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRL8_VAL_MASK) >> PKA_OP_CTRL8_VAL_SHIFT)

/* Bitfield definition for register: ECC_P */
/*
 * ADDR (RW)
 *
 * The address of the ECC parameter P inside the local 256-bits blocks
 */
#define PKA_ECC_P_ADDR_MASK (0x1FFFU)
#define PKA_ECC_P_ADDR_SHIFT (0U)
#define PKA_ECC_P_ADDR_SET(x) (((uint32_t)(x) << PKA_ECC_P_ADDR_SHIFT) & PKA_ECC_P_ADDR_MASK)
#define PKA_ECC_P_ADDR_GET(x) (((uint32_t)(x) & PKA_ECC_P_ADDR_MASK) >> PKA_ECC_P_ADDR_SHIFT)

/* Bitfield definition for register: OP_CTRL9 */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRL9_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRL9_VAL_SHIFT (0U)
#define PKA_OP_CTRL9_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRL9_VAL_SHIFT) & PKA_OP_CTRL9_VAL_MASK)
#define PKA_OP_CTRL9_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRL9_VAL_MASK) >> PKA_OP_CTRL9_VAL_SHIFT)

/* Bitfield definition for register: RSA_M */
/*
 * ADDR (RW)
 *
 * The starting location of RSA buffer M inside the local 256-bits blocks
 */
#define PKA_RSA_M_ADDR_MASK (0x1FFFU)
#define PKA_RSA_M_ADDR_SHIFT (0U)
#define PKA_RSA_M_ADDR_SET(x) (((uint32_t)(x) << PKA_RSA_M_ADDR_SHIFT) & PKA_RSA_M_ADDR_MASK)
#define PKA_RSA_M_ADDR_GET(x) (((uint32_t)(x) & PKA_RSA_M_ADDR_MASK) >> PKA_RSA_M_ADDR_SHIFT)

/* Bitfield definition for register: ECC_GEN_X */
/*
 * ADDR (RW)
 *
 * The address of the ECC generator X location inside the local 256-bits blocks
 */
#define PKA_ECC_GEN_X_ADDR_MASK (0x1FFFU)
#define PKA_ECC_GEN_X_ADDR_SHIFT (0U)
#define PKA_ECC_GEN_X_ADDR_SET(x) (((uint32_t)(x) << PKA_ECC_GEN_X_ADDR_SHIFT) & PKA_ECC_GEN_X_ADDR_MASK)
#define PKA_ECC_GEN_X_ADDR_GET(x) (((uint32_t)(x) & PKA_ECC_GEN_X_ADDR_MASK) >> PKA_ECC_GEN_X_ADDR_SHIFT)

/* Bitfield definition for register: OP_CTRLA */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRLA_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRLA_VAL_SHIFT (0U)
#define PKA_OP_CTRLA_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRLA_VAL_SHIFT) & PKA_OP_CTRLA_VAL_MASK)
#define PKA_OP_CTRLA_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRLA_VAL_MASK) >> PKA_OP_CTRLA_VAL_SHIFT)

/* Bitfield definition for register: RSA_TM0 */
/*
 * ADDR (RW)
 *
 * The starting location of RSA buffer TM0 inside the local 256-bits blocks
 */
#define PKA_RSA_TM0_ADDR_MASK (0x1FFFU)
#define PKA_RSA_TM0_ADDR_SHIFT (0U)
#define PKA_RSA_TM0_ADDR_SET(x) (((uint32_t)(x) << PKA_RSA_TM0_ADDR_SHIFT) & PKA_RSA_TM0_ADDR_MASK)
#define PKA_RSA_TM0_ADDR_GET(x) (((uint32_t)(x) & PKA_RSA_TM0_ADDR_MASK) >> PKA_RSA_TM0_ADDR_SHIFT)

/* Bitfield definition for register: ECC_GEN_Y */
/*
 * ADDR (RW)
 *
 * The address of the ECC generator Y location inside the local 256-bits blocks
 */
#define PKA_ECC_GEN_Y_ADDR_MASK (0x1FFFU)
#define PKA_ECC_GEN_Y_ADDR_SHIFT (0U)
#define PKA_ECC_GEN_Y_ADDR_SET(x) (((uint32_t)(x) << PKA_ECC_GEN_Y_ADDR_SHIFT) & PKA_ECC_GEN_Y_ADDR_MASK)
#define PKA_ECC_GEN_Y_ADDR_GET(x) (((uint32_t)(x) & PKA_ECC_GEN_Y_ADDR_MASK) >> PKA_ECC_GEN_Y_ADDR_SHIFT)

/* Bitfield definition for register: OP_CTRLB */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRLB_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRLB_VAL_SHIFT (0U)
#define PKA_OP_CTRLB_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRLB_VAL_SHIFT) & PKA_OP_CTRLB_VAL_MASK)
#define PKA_OP_CTRLB_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRLB_VAL_MASK) >> PKA_OP_CTRLB_VAL_SHIFT)

/* Bitfield definition for register: RSA_TM1 */
/*
 * ADDR (RW)
 *
 * The starting location of RSA buffer TM1 inside the local 256-bits blocks
 */
#define PKA_RSA_TM1_ADDR_MASK (0x1FFFU)
#define PKA_RSA_TM1_ADDR_SHIFT (0U)
#define PKA_RSA_TM1_ADDR_SET(x) (((uint32_t)(x) << PKA_RSA_TM1_ADDR_SHIFT) & PKA_RSA_TM1_ADDR_MASK)
#define PKA_RSA_TM1_ADDR_GET(x) (((uint32_t)(x) & PKA_RSA_TM1_ADDR_MASK) >> PKA_RSA_TM1_ADDR_SHIFT)

/* Bitfield definition for register: ECC_PUB_X */
/*
 * ADDR (RW)
 *
 * The address of the ECC public key X location inside the local 256-bits blocks
 */
#define PKA_ECC_PUB_X_ADDR_MASK (0x1FFFU)
#define PKA_ECC_PUB_X_ADDR_SHIFT (0U)
#define PKA_ECC_PUB_X_ADDR_SET(x) (((uint32_t)(x) << PKA_ECC_PUB_X_ADDR_SHIFT) & PKA_ECC_PUB_X_ADDR_MASK)
#define PKA_ECC_PUB_X_ADDR_GET(x) (((uint32_t)(x) & PKA_ECC_PUB_X_ADDR_MASK) >> PKA_ECC_PUB_X_ADDR_SHIFT)

/* Bitfield definition for register: OP_CTRLC */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRLC_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRLC_VAL_SHIFT (0U)
#define PKA_OP_CTRLC_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRLC_VAL_SHIFT) & PKA_OP_CTRLC_VAL_MASK)
#define PKA_OP_CTRLC_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRLC_VAL_MASK) >> PKA_OP_CTRLC_VAL_SHIFT)

/* Bitfield definition for register: RSA_O */
/*
 * ADDR (RW)
 *
 * The starting location of RSA buffer O inside the local 256-bits blocks
 */
#define PKA_RSA_O_ADDR_MASK (0x1FFFU)
#define PKA_RSA_O_ADDR_SHIFT (0U)
#define PKA_RSA_O_ADDR_SET(x) (((uint32_t)(x) << PKA_RSA_O_ADDR_SHIFT) & PKA_RSA_O_ADDR_MASK)
#define PKA_RSA_O_ADDR_GET(x) (((uint32_t)(x) & PKA_RSA_O_ADDR_MASK) >> PKA_RSA_O_ADDR_SHIFT)

/* Bitfield definition for register: ECC_PUB_Y */
/*
 * ADDR (RW)
 *
 * The address of the ECC public key Y location inside the local 256-bits blocks
 */
#define PKA_ECC_PUB_Y_ADDR_MASK (0x1FFFU)
#define PKA_ECC_PUB_Y_ADDR_SHIFT (0U)
#define PKA_ECC_PUB_Y_ADDR_SET(x) (((uint32_t)(x) << PKA_ECC_PUB_Y_ADDR_SHIFT) & PKA_ECC_PUB_Y_ADDR_MASK)
#define PKA_ECC_PUB_Y_ADDR_GET(x) (((uint32_t)(x) & PKA_ECC_PUB_Y_ADDR_MASK) >> PKA_ECC_PUB_Y_ADDR_SHIFT)

/* Bitfield definition for register: OP_CTRLD */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRLD_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRLD_VAL_SHIFT (0U)
#define PKA_OP_CTRLD_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRLD_VAL_SHIFT) & PKA_OP_CTRLD_VAL_MASK)
#define PKA_OP_CTRLD_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRLD_VAL_MASK) >> PKA_OP_CTRLD_VAL_SHIFT)

/* Bitfield definition for register: RSA_PRIV_KEY */
/*
 * SRC_CHOICE (RW)
 *
 * Key Choice
 * 0: key inside memory. The below ADDR is the src storage loc.
 * 1: key from efuse
 * 2: key from rng,
 */
#define PKA_RSA_PRIV_KEY_SRC_CHOICE_MASK (0x60000000UL)
#define PKA_RSA_PRIV_KEY_SRC_CHOICE_SHIFT (29U)
#define PKA_RSA_PRIV_KEY_SRC_CHOICE_SET(x) (((uint32_t)(x) << PKA_RSA_PRIV_KEY_SRC_CHOICE_SHIFT) & PKA_RSA_PRIV_KEY_SRC_CHOICE_MASK)
#define PKA_RSA_PRIV_KEY_SRC_CHOICE_GET(x) (((uint32_t)(x) & PKA_RSA_PRIV_KEY_SRC_CHOICE_MASK) >> PKA_RSA_PRIV_KEY_SRC_CHOICE_SHIFT)

/*
 * STR_CHOICE (RW)
 *
 * Key Store Choice: only active when key is not inside memory
 * 0: don't copy key from key management
 * 1: copy key to internal memory indicated by the ADDR field in this config register. Then clear this bit and SRC_CHOICE bits stored in internal memory.
 */
#define PKA_RSA_PRIV_KEY_STR_CHOICE_MASK (0x10000000UL)
#define PKA_RSA_PRIV_KEY_STR_CHOICE_SHIFT (28U)
#define PKA_RSA_PRIV_KEY_STR_CHOICE_SET(x) (((uint32_t)(x) << PKA_RSA_PRIV_KEY_STR_CHOICE_SHIFT) & PKA_RSA_PRIV_KEY_STR_CHOICE_MASK)
#define PKA_RSA_PRIV_KEY_STR_CHOICE_GET(x) (((uint32_t)(x) & PKA_RSA_PRIV_KEY_STR_CHOICE_MASK) >> PKA_RSA_PRIV_KEY_STR_CHOICE_SHIFT)

/*
 * ADDR (RW)
 *
 * The starting location of RSA private key inside the local 256-bits blocks
 */
#define PKA_RSA_PRIV_KEY_ADDR_MASK (0x1FFFU)
#define PKA_RSA_PRIV_KEY_ADDR_SHIFT (0U)
#define PKA_RSA_PRIV_KEY_ADDR_SET(x) (((uint32_t)(x) << PKA_RSA_PRIV_KEY_ADDR_SHIFT) & PKA_RSA_PRIV_KEY_ADDR_MASK)
#define PKA_RSA_PRIV_KEY_ADDR_GET(x) (((uint32_t)(x) & PKA_RSA_PRIV_KEY_ADDR_MASK) >> PKA_RSA_PRIV_KEY_ADDR_SHIFT)

/* Bitfield definition for register: ECC_PRIV_K */
/*
 * SRC_CHOICE (RW)
 *
 * Key Choice
 * 0: key inside memory. The below ADDR is the src storage loc.
 * 1: key from efuse
 * 2: key from rng,
 */
#define PKA_ECC_PRIV_K_SRC_CHOICE_MASK (0x60000000UL)
#define PKA_ECC_PRIV_K_SRC_CHOICE_SHIFT (29U)
#define PKA_ECC_PRIV_K_SRC_CHOICE_SET(x) (((uint32_t)(x) << PKA_ECC_PRIV_K_SRC_CHOICE_SHIFT) & PKA_ECC_PRIV_K_SRC_CHOICE_MASK)
#define PKA_ECC_PRIV_K_SRC_CHOICE_GET(x) (((uint32_t)(x) & PKA_ECC_PRIV_K_SRC_CHOICE_MASK) >> PKA_ECC_PRIV_K_SRC_CHOICE_SHIFT)

/*
 * ADDR (RW)
 *
 * The address of the ECC private key K location  inside the local 256-bits blocks
 */
#define PKA_ECC_PRIV_K_ADDR_MASK (0x1FFFU)
#define PKA_ECC_PRIV_K_ADDR_SHIFT (0U)
#define PKA_ECC_PRIV_K_ADDR_SET(x) (((uint32_t)(x) << PKA_ECC_PRIV_K_ADDR_SHIFT) & PKA_ECC_PRIV_K_ADDR_MASK)
#define PKA_ECC_PRIV_K_ADDR_GET(x) (((uint32_t)(x) & PKA_ECC_PRIV_K_ADDR_MASK) >> PKA_ECC_PRIV_K_ADDR_SHIFT)

/* Bitfield definition for register: OP_CTRLE */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRLE_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRLE_VAL_SHIFT (0U)
#define PKA_OP_CTRLE_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRLE_VAL_SHIFT) & PKA_OP_CTRLE_VAL_MASK)
#define PKA_OP_CTRLE_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRLE_VAL_MASK) >> PKA_OP_CTRLE_VAL_SHIFT)

/* Bitfield definition for register: ECC_GENORD_N */
/*
 * ADDR (RW)
 *
 * The address of the order N of ECC generator inside the local 256-bits blocks
 */
#define PKA_ECC_GENORD_N_ADDR_MASK (0x1FFFU)
#define PKA_ECC_GENORD_N_ADDR_SHIFT (0U)
#define PKA_ECC_GENORD_N_ADDR_SET(x) (((uint32_t)(x) << PKA_ECC_GENORD_N_ADDR_SHIFT) & PKA_ECC_GENORD_N_ADDR_MASK)
#define PKA_ECC_GENORD_N_ADDR_GET(x) (((uint32_t)(x) & PKA_ECC_GENORD_N_ADDR_MASK) >> PKA_ECC_GENORD_N_ADDR_SHIFT)

/* Bitfield definition for register: OP_CTRLF */
/*
 * VAL (RW)
 *
 * The config words contents
 */
#define PKA_OP_CTRLF_VAL_MASK (0xFFFFFFFFUL)
#define PKA_OP_CTRLF_VAL_SHIFT (0U)
#define PKA_OP_CTRLF_VAL_SET(x) (((uint32_t)(x) << PKA_OP_CTRLF_VAL_SHIFT) & PKA_OP_CTRLF_VAL_MASK)
#define PKA_OP_CTRLF_VAL_GET(x) (((uint32_t)(x) & PKA_OP_CTRLF_VAL_MASK) >> PKA_OP_CTRLF_VAL_SHIFT)

/* Bitfield definition for register: ECC_R2N_ORDER_N */
/*
 * ADDR (RW)
 *
 * The address of mod(R*R, N) for the order N of ECC generators inside the local 256-bits blocks
 */
#define PKA_ECC_R2N_ORDER_N_ADDR_MASK (0x1FFFU)
#define PKA_ECC_R2N_ORDER_N_ADDR_SHIFT (0U)
#define PKA_ECC_R2N_ORDER_N_ADDR_SET(x) (((uint32_t)(x) << PKA_ECC_R2N_ORDER_N_ADDR_SHIFT) & PKA_ECC_R2N_ORDER_N_ADDR_MASK)
#define PKA_ECC_R2N_ORDER_N_ADDR_GET(x) (((uint32_t)(x) & PKA_ECC_R2N_ORDER_N_ADDR_MASK) >> PKA_ECC_R2N_ORDER_N_ADDR_SHIFT)




#endif /* HPM_PKA_H */
