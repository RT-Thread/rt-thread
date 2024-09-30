/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_FFA_H
#define HPM_FFA_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0:  */
    __RW uint32_t STATUS;                      /* 0x4:  */
    __RW uint32_t INT_EN;                      /* 0x8:  */
    __R  uint8_t  RESERVED0[20];               /* 0xC - 0x1F: Reserved */
    __RW uint32_t OP_CTRL;                     /* 0x20:  */
    __RW uint32_t OP_CMD;                      /* 0x24:  */
    union {
        __RW uint32_t OP_REG0;                 /* 0x28:  */
        __RW uint32_t OP_FIR_MISC;             /* 0x28:  */
        __RW uint32_t OP_FFT_MISC;             /* 0x28:  */
    };
    union {
        __RW uint32_t OP_REG1;                 /* 0x2C:  */
        __RW uint32_t OP_FIR_MISC1;            /* 0x2C:  */
    };
    union {
        __RW uint32_t OP_REG2;                 /* 0x30:  */
        __RW uint32_t OP_FFT_INRBUF;           /* 0x30:  */
    };
    union {
        __RW uint32_t OP_REG3;                 /* 0x34:  */
        __RW uint32_t OP_FIR_INBUF;            /* 0x34:  */
    };
    union {
        __RW uint32_t OP_REG4;                 /* 0x38:  */
        __RW uint32_t OP_FIR_COEFBUF;          /* 0x38:  */
        __RW uint32_t OP_FFT_OUTRBUF;          /* 0x38:  */
    };
    union {
        __RW uint32_t OP_REG5;                 /* 0x3C:  */
        __RW uint32_t OP_FIR_OUTBUF;           /* 0x3C:  */
    };
    __RW uint32_t OP_REG6;                     /* 0x40:  */
    __RW uint32_t OP_REG7;                     /* 0x44:  */
} FFA_Type;


/* Bitfield definition for register: CTRL */
/*
 * SFTRST (RW)
 *
 * software reset the module if asserted to be 1.
 * EN is only active after this bit is zero.
 */
#define FFA_CTRL_SFTRST_MASK (0x80000000UL)
#define FFA_CTRL_SFTRST_SHIFT (31U)
#define FFA_CTRL_SFTRST_SET(x) (((uint32_t)(x) << FFA_CTRL_SFTRST_SHIFT) & FFA_CTRL_SFTRST_MASK)
#define FFA_CTRL_SFTRST_GET(x) (((uint32_t)(x) & FFA_CTRL_SFTRST_MASK) >> FFA_CTRL_SFTRST_SHIFT)

/*
 * EN (RW)
 *
 * Asserted to enable the module
 */
#define FFA_CTRL_EN_MASK (0x1U)
#define FFA_CTRL_EN_SHIFT (0U)
#define FFA_CTRL_EN_SET(x) (((uint32_t)(x) << FFA_CTRL_EN_SHIFT) & FFA_CTRL_EN_MASK)
#define FFA_CTRL_EN_GET(x) (((uint32_t)(x) & FFA_CTRL_EN_MASK) >> FFA_CTRL_EN_SHIFT)

/* Bitfield definition for register: STATUS */
/*
 * FIR_OV (W1C)
 *
 * FIR Overflow err
 */
#define FFA_STATUS_FIR_OV_MASK (0x80U)
#define FFA_STATUS_FIR_OV_SHIFT (7U)
#define FFA_STATUS_FIR_OV_SET(x) (((uint32_t)(x) << FFA_STATUS_FIR_OV_SHIFT) & FFA_STATUS_FIR_OV_MASK)
#define FFA_STATUS_FIR_OV_GET(x) (((uint32_t)(x) & FFA_STATUS_FIR_OV_MASK) >> FFA_STATUS_FIR_OV_SHIFT)

/*
 * FFT_OV (W1C)
 *
 * FFT Overflow Err
 */
#define FFA_STATUS_FFT_OV_MASK (0x40U)
#define FFA_STATUS_FFT_OV_SHIFT (6U)
#define FFA_STATUS_FFT_OV_SET(x) (((uint32_t)(x) << FFA_STATUS_FFT_OV_SHIFT) & FFA_STATUS_FFT_OV_MASK)
#define FFA_STATUS_FFT_OV_GET(x) (((uint32_t)(x) & FFA_STATUS_FFT_OV_MASK) >> FFA_STATUS_FFT_OV_SHIFT)

/*
 * WR_ERR (W1C)
 *
 * AXI Data Write Error
 */
#define FFA_STATUS_WR_ERR_MASK (0x20U)
#define FFA_STATUS_WR_ERR_SHIFT (5U)
#define FFA_STATUS_WR_ERR_SET(x) (((uint32_t)(x) << FFA_STATUS_WR_ERR_SHIFT) & FFA_STATUS_WR_ERR_MASK)
#define FFA_STATUS_WR_ERR_GET(x) (((uint32_t)(x) & FFA_STATUS_WR_ERR_MASK) >> FFA_STATUS_WR_ERR_SHIFT)

/*
 * RD_NXT_ERR (W1C)
 *
 * AXI Read Bus Error for NXT DATA
 */
#define FFA_STATUS_RD_NXT_ERR_MASK (0x10U)
#define FFA_STATUS_RD_NXT_ERR_SHIFT (4U)
#define FFA_STATUS_RD_NXT_ERR_SET(x) (((uint32_t)(x) << FFA_STATUS_RD_NXT_ERR_SHIFT) & FFA_STATUS_RD_NXT_ERR_MASK)
#define FFA_STATUS_RD_NXT_ERR_GET(x) (((uint32_t)(x) & FFA_STATUS_RD_NXT_ERR_MASK) >> FFA_STATUS_RD_NXT_ERR_SHIFT)

/*
 * RD_ERR (W1C)
 *
 * AXI Data Read Error
 */
#define FFA_STATUS_RD_ERR_MASK (0x8U)
#define FFA_STATUS_RD_ERR_SHIFT (3U)
#define FFA_STATUS_RD_ERR_SET(x) (((uint32_t)(x) << FFA_STATUS_RD_ERR_SHIFT) & FFA_STATUS_RD_ERR_MASK)
#define FFA_STATUS_RD_ERR_GET(x) (((uint32_t)(x) & FFA_STATUS_RD_ERR_MASK) >> FFA_STATUS_RD_ERR_SHIFT)

/*
 * NXT_CMD_RD_DONE (W1C)
 *
 * Indicate that next command sequence is already read into the module.
 */
#define FFA_STATUS_NXT_CMD_RD_DONE_MASK (0x2U)
#define FFA_STATUS_NXT_CMD_RD_DONE_SHIFT (1U)
#define FFA_STATUS_NXT_CMD_RD_DONE_SET(x) (((uint32_t)(x) << FFA_STATUS_NXT_CMD_RD_DONE_SHIFT) & FFA_STATUS_NXT_CMD_RD_DONE_MASK)
#define FFA_STATUS_NXT_CMD_RD_DONE_GET(x) (((uint32_t)(x) & FFA_STATUS_NXT_CMD_RD_DONE_MASK) >> FFA_STATUS_NXT_CMD_RD_DONE_SHIFT)

/*
 * OP_CMD_DONE (W1C)
 *
 * Indicate that operation cmd is done, and data are available in system memory.
 */
#define FFA_STATUS_OP_CMD_DONE_MASK (0x1U)
#define FFA_STATUS_OP_CMD_DONE_SHIFT (0U)
#define FFA_STATUS_OP_CMD_DONE_SET(x) (((uint32_t)(x) << FFA_STATUS_OP_CMD_DONE_SHIFT) & FFA_STATUS_OP_CMD_DONE_MASK)
#define FFA_STATUS_OP_CMD_DONE_GET(x) (((uint32_t)(x) & FFA_STATUS_OP_CMD_DONE_MASK) >> FFA_STATUS_OP_CMD_DONE_SHIFT)

/* Bitfield definition for register: INT_EN */
/*
 * WRSV1 (RW)
 *
 * Reserved
 */
#define FFA_INT_EN_WRSV1_MASK (0xFFFFFF00UL)
#define FFA_INT_EN_WRSV1_SHIFT (8U)
#define FFA_INT_EN_WRSV1_SET(x) (((uint32_t)(x) << FFA_INT_EN_WRSV1_SHIFT) & FFA_INT_EN_WRSV1_MASK)
#define FFA_INT_EN_WRSV1_GET(x) (((uint32_t)(x) & FFA_INT_EN_WRSV1_MASK) >> FFA_INT_EN_WRSV1_SHIFT)

/*
 * FIR_OV (RW)
 *
 * FIR Overflow err
 */
#define FFA_INT_EN_FIR_OV_MASK (0x80U)
#define FFA_INT_EN_FIR_OV_SHIFT (7U)
#define FFA_INT_EN_FIR_OV_SET(x) (((uint32_t)(x) << FFA_INT_EN_FIR_OV_SHIFT) & FFA_INT_EN_FIR_OV_MASK)
#define FFA_INT_EN_FIR_OV_GET(x) (((uint32_t)(x) & FFA_INT_EN_FIR_OV_MASK) >> FFA_INT_EN_FIR_OV_SHIFT)

/*
 * FFT_OV (RW)
 *
 * FFT Overflow Err
 */
#define FFA_INT_EN_FFT_OV_MASK (0x40U)
#define FFA_INT_EN_FFT_OV_SHIFT (6U)
#define FFA_INT_EN_FFT_OV_SET(x) (((uint32_t)(x) << FFA_INT_EN_FFT_OV_SHIFT) & FFA_INT_EN_FFT_OV_MASK)
#define FFA_INT_EN_FFT_OV_GET(x) (((uint32_t)(x) & FFA_INT_EN_FFT_OV_MASK) >> FFA_INT_EN_FFT_OV_SHIFT)

/*
 * WR_ERR (RW)
 *
 * Enable Data Write Error interrupt
 */
#define FFA_INT_EN_WR_ERR_MASK (0x20U)
#define FFA_INT_EN_WR_ERR_SHIFT (5U)
#define FFA_INT_EN_WR_ERR_SET(x) (((uint32_t)(x) << FFA_INT_EN_WR_ERR_SHIFT) & FFA_INT_EN_WR_ERR_MASK)
#define FFA_INT_EN_WR_ERR_GET(x) (((uint32_t)(x) & FFA_INT_EN_WR_ERR_MASK) >> FFA_INT_EN_WR_ERR_SHIFT)

/*
 * RD_NXT_ERR (RW)
 *
 * Enable Read Bus Error for NXT DATA interrupt
 */
#define FFA_INT_EN_RD_NXT_ERR_MASK (0x10U)
#define FFA_INT_EN_RD_NXT_ERR_SHIFT (4U)
#define FFA_INT_EN_RD_NXT_ERR_SET(x) (((uint32_t)(x) << FFA_INT_EN_RD_NXT_ERR_SHIFT) & FFA_INT_EN_RD_NXT_ERR_MASK)
#define FFA_INT_EN_RD_NXT_ERR_GET(x) (((uint32_t)(x) & FFA_INT_EN_RD_NXT_ERR_MASK) >> FFA_INT_EN_RD_NXT_ERR_SHIFT)

/*
 * RD_ERR (RW)
 *
 * Enable Data Read Error interrupt
 */
#define FFA_INT_EN_RD_ERR_MASK (0x8U)
#define FFA_INT_EN_RD_ERR_SHIFT (3U)
#define FFA_INT_EN_RD_ERR_SET(x) (((uint32_t)(x) << FFA_INT_EN_RD_ERR_SHIFT) & FFA_INT_EN_RD_ERR_MASK)
#define FFA_INT_EN_RD_ERR_GET(x) (((uint32_t)(x) & FFA_INT_EN_RD_ERR_MASK) >> FFA_INT_EN_RD_ERR_SHIFT)

/*
 * NXT_CMD_RD_DONE (RW)
 *
 * Indicate that next command sequence is already read into the module.
 */
#define FFA_INT_EN_NXT_CMD_RD_DONE_MASK (0x2U)
#define FFA_INT_EN_NXT_CMD_RD_DONE_SHIFT (1U)
#define FFA_INT_EN_NXT_CMD_RD_DONE_SET(x) (((uint32_t)(x) << FFA_INT_EN_NXT_CMD_RD_DONE_SHIFT) & FFA_INT_EN_NXT_CMD_RD_DONE_MASK)
#define FFA_INT_EN_NXT_CMD_RD_DONE_GET(x) (((uint32_t)(x) & FFA_INT_EN_NXT_CMD_RD_DONE_MASK) >> FFA_INT_EN_NXT_CMD_RD_DONE_SHIFT)

/*
 * OP_CMD_DONE (RW)
 *
 * Indicate that operation cmd is done, and data are available in system memory.
 */
#define FFA_INT_EN_OP_CMD_DONE_MASK (0x1U)
#define FFA_INT_EN_OP_CMD_DONE_SHIFT (0U)
#define FFA_INT_EN_OP_CMD_DONE_SET(x) (((uint32_t)(x) << FFA_INT_EN_OP_CMD_DONE_SHIFT) & FFA_INT_EN_OP_CMD_DONE_MASK)
#define FFA_INT_EN_OP_CMD_DONE_GET(x) (((uint32_t)(x) & FFA_INT_EN_OP_CMD_DONE_MASK) >> FFA_INT_EN_OP_CMD_DONE_SHIFT)

/* Bitfield definition for register: OP_CTRL */
/*
 * NXT_ADDR (RW)
 *
 * The address for the next command.
 * It will be processed after CUR_CMD is executed and done..
 */
#define FFA_OP_CTRL_NXT_ADDR_MASK (0xFFFFFFFCUL)
#define FFA_OP_CTRL_NXT_ADDR_SHIFT (2U)
#define FFA_OP_CTRL_NXT_ADDR_SET(x) (((uint32_t)(x) << FFA_OP_CTRL_NXT_ADDR_SHIFT) & FFA_OP_CTRL_NXT_ADDR_MASK)
#define FFA_OP_CTRL_NXT_ADDR_GET(x) (((uint32_t)(x) & FFA_OP_CTRL_NXT_ADDR_MASK) >> FFA_OP_CTRL_NXT_ADDR_SHIFT)

/*
 * NXT_EN (RW)
 *
 * Whether NXT_CMD is enabled.
 * Asserted to enable the NXT_CMD when CUR_CMD is done, or CUR_CMD is not enabled..
 */
#define FFA_OP_CTRL_NXT_EN_MASK (0x2U)
#define FFA_OP_CTRL_NXT_EN_SHIFT (1U)
#define FFA_OP_CTRL_NXT_EN_SET(x) (((uint32_t)(x) << FFA_OP_CTRL_NXT_EN_SHIFT) & FFA_OP_CTRL_NXT_EN_MASK)
#define FFA_OP_CTRL_NXT_EN_GET(x) (((uint32_t)(x) & FFA_OP_CTRL_NXT_EN_MASK) >> FFA_OP_CTRL_NXT_EN_SHIFT)

/*
 * EN (RW)
 *
 * Whether CUR_CMD is enabled.
 * Asserted to enable the CUR_CMD
 */
#define FFA_OP_CTRL_EN_MASK (0x1U)
#define FFA_OP_CTRL_EN_SHIFT (0U)
#define FFA_OP_CTRL_EN_SET(x) (((uint32_t)(x) << FFA_OP_CTRL_EN_SHIFT) & FFA_OP_CTRL_EN_MASK)
#define FFA_OP_CTRL_EN_GET(x) (((uint32_t)(x) & FFA_OP_CTRL_EN_MASK) >> FFA_OP_CTRL_EN_SHIFT)

/* Bitfield definition for register: OP_CMD */
/*
 * CONJ_C (RW)
 *
 * asserted to have conjuate value for coefs in computation
 */
#define FFA_OP_CMD_CONJ_C_MASK (0x1000000UL)
#define FFA_OP_CMD_CONJ_C_SHIFT (24U)
#define FFA_OP_CMD_CONJ_C_SET(x) (((uint32_t)(x) << FFA_OP_CMD_CONJ_C_SHIFT) & FFA_OP_CMD_CONJ_C_MASK)
#define FFA_OP_CMD_CONJ_C_GET(x) (((uint32_t)(x) & FFA_OP_CMD_CONJ_C_MASK) >> FFA_OP_CMD_CONJ_C_SHIFT)

/*
 * CMD (RW)
 *
 * The Command Used:
 * 0: FIR
 * 2: FFT
 * Others: Reserved
 */
#define FFA_OP_CMD_CMD_MASK (0xFC0000UL)
#define FFA_OP_CMD_CMD_SHIFT (18U)
#define FFA_OP_CMD_CMD_SET(x) (((uint32_t)(x) << FFA_OP_CMD_CMD_SHIFT) & FFA_OP_CMD_CMD_MASK)
#define FFA_OP_CMD_CMD_GET(x) (((uint32_t)(x) & FFA_OP_CMD_CMD_MASK) >> FFA_OP_CMD_CMD_SHIFT)

/*
 * OUTD_TYPE (RW)
 *
 * Output data type:
 * 0:Real Q31, 1:Real Q15, 2:Complex Q31, 3:Complex Q15
 * 4:complex sp float 5: real sp float
 */
#define FFA_OP_CMD_OUTD_TYPE_MASK (0x38000UL)
#define FFA_OP_CMD_OUTD_TYPE_SHIFT (15U)
#define FFA_OP_CMD_OUTD_TYPE_SET(x) (((uint32_t)(x) << FFA_OP_CMD_OUTD_TYPE_SHIFT) & FFA_OP_CMD_OUTD_TYPE_MASK)
#define FFA_OP_CMD_OUTD_TYPE_GET(x) (((uint32_t)(x) & FFA_OP_CMD_OUTD_TYPE_MASK) >> FFA_OP_CMD_OUTD_TYPE_SHIFT)

/*
 * COEF_TYPE (RW)
 *
 * Coef data type (used for FIR):
 * 0:Real Q31, 1:Real Q15, 2:Complex Q31, 3:Complex Q15
 * 4:complex sp float 5: real sp float
 */
#define FFA_OP_CMD_COEF_TYPE_MASK (0x7000U)
#define FFA_OP_CMD_COEF_TYPE_SHIFT (12U)
#define FFA_OP_CMD_COEF_TYPE_SET(x) (((uint32_t)(x) << FFA_OP_CMD_COEF_TYPE_SHIFT) & FFA_OP_CMD_COEF_TYPE_MASK)
#define FFA_OP_CMD_COEF_TYPE_GET(x) (((uint32_t)(x) & FFA_OP_CMD_COEF_TYPE_MASK) >> FFA_OP_CMD_COEF_TYPE_SHIFT)

/*
 * IND_TYPE (RW)
 *
 * Input data type:
 * 0:Real Q31, 1:Real Q15, 2:Complex Q31, 3:Complex Q15
 * 4:complex sp float 5: real sp float
 */
#define FFA_OP_CMD_IND_TYPE_MASK (0xE00U)
#define FFA_OP_CMD_IND_TYPE_SHIFT (9U)
#define FFA_OP_CMD_IND_TYPE_SET(x) (((uint32_t)(x) << FFA_OP_CMD_IND_TYPE_SHIFT) & FFA_OP_CMD_IND_TYPE_MASK)
#define FFA_OP_CMD_IND_TYPE_GET(x) (((uint32_t)(x) & FFA_OP_CMD_IND_TYPE_MASK) >> FFA_OP_CMD_IND_TYPE_SHIFT)

/*
 * NXT_CMD_LEN (RW)
 *
 * The length of nxt commands in 32-bit words
 */
#define FFA_OP_CMD_NXT_CMD_LEN_MASK (0xFFU)
#define FFA_OP_CMD_NXT_CMD_LEN_SHIFT (0U)
#define FFA_OP_CMD_NXT_CMD_LEN_SET(x) (((uint32_t)(x) << FFA_OP_CMD_NXT_CMD_LEN_SHIFT) & FFA_OP_CMD_NXT_CMD_LEN_MASK)
#define FFA_OP_CMD_NXT_CMD_LEN_GET(x) (((uint32_t)(x) & FFA_OP_CMD_NXT_CMD_LEN_MASK) >> FFA_OP_CMD_NXT_CMD_LEN_SHIFT)

/* Bitfield definition for register: OP_REG0 */
/*
 * CT (RW)
 *
 * Contents
 */
#define FFA_OP_REG0_CT_MASK (0xFFFFFFFFUL)
#define FFA_OP_REG0_CT_SHIFT (0U)
#define FFA_OP_REG0_CT_SET(x) (((uint32_t)(x) << FFA_OP_REG0_CT_SHIFT) & FFA_OP_REG0_CT_MASK)
#define FFA_OP_REG0_CT_GET(x) (((uint32_t)(x) & FFA_OP_REG0_CT_MASK) >> FFA_OP_REG0_CT_SHIFT)

/* Bitfield definition for register: OP_FIR_MISC */
/*
 * FIR_COEF_TAPS (RW)
 *
 * Length of FIR coefs （max 256）
 */
#define FFA_OP_FIR_MISC_FIR_COEF_TAPS_MASK (0x3FFFU)
#define FFA_OP_FIR_MISC_FIR_COEF_TAPS_SHIFT (0U)
#define FFA_OP_FIR_MISC_FIR_COEF_TAPS_SET(x) (((uint32_t)(x) << FFA_OP_FIR_MISC_FIR_COEF_TAPS_SHIFT) & FFA_OP_FIR_MISC_FIR_COEF_TAPS_MASK)
#define FFA_OP_FIR_MISC_FIR_COEF_TAPS_GET(x) (((uint32_t)(x) & FFA_OP_FIR_MISC_FIR_COEF_TAPS_MASK) >> FFA_OP_FIR_MISC_FIR_COEF_TAPS_SHIFT)

/* Bitfield definition for register: OP_FFT_MISC */
/*
 * FFT_LEN (RW)
 *
 * FFT length
 * 0:8,
 * ...,
 * n:2^(3+n)
 */
#define FFA_OP_FFT_MISC_FFT_LEN_MASK (0x780U)
#define FFA_OP_FFT_MISC_FFT_LEN_SHIFT (7U)
#define FFA_OP_FFT_MISC_FFT_LEN_SET(x) (((uint32_t)(x) << FFA_OP_FFT_MISC_FFT_LEN_SHIFT) & FFA_OP_FFT_MISC_FFT_LEN_MASK)
#define FFA_OP_FFT_MISC_FFT_LEN_GET(x) (((uint32_t)(x) & FFA_OP_FFT_MISC_FFT_LEN_MASK) >> FFA_OP_FFT_MISC_FFT_LEN_SHIFT)

/*
 * IFFT (RW)
 *
 * Asserted to indicate IFFT
 */
#define FFA_OP_FFT_MISC_IFFT_MASK (0x40U)
#define FFA_OP_FFT_MISC_IFFT_SHIFT (6U)
#define FFA_OP_FFT_MISC_IFFT_SET(x) (((uint32_t)(x) << FFA_OP_FFT_MISC_IFFT_SHIFT) & FFA_OP_FFT_MISC_IFFT_MASK)
#define FFA_OP_FFT_MISC_IFFT_GET(x) (((uint32_t)(x) & FFA_OP_FFT_MISC_IFFT_MASK) >> FFA_OP_FFT_MISC_IFFT_SHIFT)

/*
 * TMP_BLK (RW)
 *
 * Memory block for indata. Should be assigned as 1
 */
#define FFA_OP_FFT_MISC_TMP_BLK_MASK (0xCU)
#define FFA_OP_FFT_MISC_TMP_BLK_SHIFT (2U)
#define FFA_OP_FFT_MISC_TMP_BLK_SET(x) (((uint32_t)(x) << FFA_OP_FFT_MISC_TMP_BLK_SHIFT) & FFA_OP_FFT_MISC_TMP_BLK_MASK)
#define FFA_OP_FFT_MISC_TMP_BLK_GET(x) (((uint32_t)(x) & FFA_OP_FFT_MISC_TMP_BLK_MASK) >> FFA_OP_FFT_MISC_TMP_BLK_SHIFT)

/*
 * IND_BLK (RW)
 *
 * Memory block for indata. Should be assigned as 0
 */
#define FFA_OP_FFT_MISC_IND_BLK_MASK (0x3U)
#define FFA_OP_FFT_MISC_IND_BLK_SHIFT (0U)
#define FFA_OP_FFT_MISC_IND_BLK_SET(x) (((uint32_t)(x) << FFA_OP_FFT_MISC_IND_BLK_SHIFT) & FFA_OP_FFT_MISC_IND_BLK_MASK)
#define FFA_OP_FFT_MISC_IND_BLK_GET(x) (((uint32_t)(x) & FFA_OP_FFT_MISC_IND_BLK_MASK) >> FFA_OP_FFT_MISC_IND_BLK_SHIFT)

/* Bitfield definition for register: OP_REG1 */
/*
 * CT (RW)
 *
 * Contents
 */
#define FFA_OP_REG1_CT_MASK (0xFFFFFFFFUL)
#define FFA_OP_REG1_CT_SHIFT (0U)
#define FFA_OP_REG1_CT_SET(x) (((uint32_t)(x) << FFA_OP_REG1_CT_SHIFT) & FFA_OP_REG1_CT_MASK)
#define FFA_OP_REG1_CT_GET(x) (((uint32_t)(x) & FFA_OP_REG1_CT_MASK) >> FFA_OP_REG1_CT_SHIFT)

/* Bitfield definition for register: OP_FIR_MISC1 */
/*
 * OUTD_MEM_BLK (RW)
 *
 * Should be assigned as 0
 */
#define FFA_OP_FIR_MISC1_OUTD_MEM_BLK_MASK (0x300000UL)
#define FFA_OP_FIR_MISC1_OUTD_MEM_BLK_SHIFT (20U)
#define FFA_OP_FIR_MISC1_OUTD_MEM_BLK_SET(x) (((uint32_t)(x) << FFA_OP_FIR_MISC1_OUTD_MEM_BLK_SHIFT) & FFA_OP_FIR_MISC1_OUTD_MEM_BLK_MASK)
#define FFA_OP_FIR_MISC1_OUTD_MEM_BLK_GET(x) (((uint32_t)(x) & FFA_OP_FIR_MISC1_OUTD_MEM_BLK_MASK) >> FFA_OP_FIR_MISC1_OUTD_MEM_BLK_SHIFT)

/*
 * COEF_MEM_BLK (RW)
 *
 * Should be assigned as 1
 */
#define FFA_OP_FIR_MISC1_COEF_MEM_BLK_MASK (0xC0000UL)
#define FFA_OP_FIR_MISC1_COEF_MEM_BLK_SHIFT (18U)
#define FFA_OP_FIR_MISC1_COEF_MEM_BLK_SET(x) (((uint32_t)(x) << FFA_OP_FIR_MISC1_COEF_MEM_BLK_SHIFT) & FFA_OP_FIR_MISC1_COEF_MEM_BLK_MASK)
#define FFA_OP_FIR_MISC1_COEF_MEM_BLK_GET(x) (((uint32_t)(x) & FFA_OP_FIR_MISC1_COEF_MEM_BLK_MASK) >> FFA_OP_FIR_MISC1_COEF_MEM_BLK_SHIFT)

/*
 * IND_MEM_BLK (RW)
 *
 * Should be assigned as 2
 */
#define FFA_OP_FIR_MISC1_IND_MEM_BLK_MASK (0x30000UL)
#define FFA_OP_FIR_MISC1_IND_MEM_BLK_SHIFT (16U)
#define FFA_OP_FIR_MISC1_IND_MEM_BLK_SET(x) (((uint32_t)(x) << FFA_OP_FIR_MISC1_IND_MEM_BLK_SHIFT) & FFA_OP_FIR_MISC1_IND_MEM_BLK_MASK)
#define FFA_OP_FIR_MISC1_IND_MEM_BLK_GET(x) (((uint32_t)(x) & FFA_OP_FIR_MISC1_IND_MEM_BLK_MASK) >> FFA_OP_FIR_MISC1_IND_MEM_BLK_SHIFT)

/*
 * FIR_DATA_TAPS (RW)
 *
 * The input data data length
 */
#define FFA_OP_FIR_MISC1_FIR_DATA_TAPS_MASK (0xFFFFU)
#define FFA_OP_FIR_MISC1_FIR_DATA_TAPS_SHIFT (0U)
#define FFA_OP_FIR_MISC1_FIR_DATA_TAPS_SET(x) (((uint32_t)(x) << FFA_OP_FIR_MISC1_FIR_DATA_TAPS_SHIFT) & FFA_OP_FIR_MISC1_FIR_DATA_TAPS_MASK)
#define FFA_OP_FIR_MISC1_FIR_DATA_TAPS_GET(x) (((uint32_t)(x) & FFA_OP_FIR_MISC1_FIR_DATA_TAPS_MASK) >> FFA_OP_FIR_MISC1_FIR_DATA_TAPS_SHIFT)

/* Bitfield definition for register: OP_REG2 */
/*
 * CT (RW)
 *
 * Contents
 */
#define FFA_OP_REG2_CT_MASK (0xFFFFFFFFUL)
#define FFA_OP_REG2_CT_SHIFT (0U)
#define FFA_OP_REG2_CT_SET(x) (((uint32_t)(x) << FFA_OP_REG2_CT_SHIFT) & FFA_OP_REG2_CT_MASK)
#define FFA_OP_REG2_CT_GET(x) (((uint32_t)(x) & FFA_OP_REG2_CT_MASK) >> FFA_OP_REG2_CT_SHIFT)

/* Bitfield definition for register: OP_FFT_INRBUF */
/*
 * LOC (RW)
 *
 * The input (real) data buffer pointer
 */
#define FFA_OP_FFT_INRBUF_LOC_MASK (0xFFFFFFFFUL)
#define FFA_OP_FFT_INRBUF_LOC_SHIFT (0U)
#define FFA_OP_FFT_INRBUF_LOC_SET(x) (((uint32_t)(x) << FFA_OP_FFT_INRBUF_LOC_SHIFT) & FFA_OP_FFT_INRBUF_LOC_MASK)
#define FFA_OP_FFT_INRBUF_LOC_GET(x) (((uint32_t)(x) & FFA_OP_FFT_INRBUF_LOC_MASK) >> FFA_OP_FFT_INRBUF_LOC_SHIFT)

/* Bitfield definition for register: OP_REG3 */
/*
 * CT (RW)
 *
 * Contents
 */
#define FFA_OP_REG3_CT_MASK (0xFFFFFFFFUL)
#define FFA_OP_REG3_CT_SHIFT (0U)
#define FFA_OP_REG3_CT_SET(x) (((uint32_t)(x) << FFA_OP_REG3_CT_SHIFT) & FFA_OP_REG3_CT_MASK)
#define FFA_OP_REG3_CT_GET(x) (((uint32_t)(x) & FFA_OP_REG3_CT_MASK) >> FFA_OP_REG3_CT_SHIFT)

/* Bitfield definition for register: OP_FIR_INBUF */
/*
 * LOC (RW)
 *
 * The input data buffer pointer
 */
#define FFA_OP_FIR_INBUF_LOC_MASK (0xFFFFFFFFUL)
#define FFA_OP_FIR_INBUF_LOC_SHIFT (0U)
#define FFA_OP_FIR_INBUF_LOC_SET(x) (((uint32_t)(x) << FFA_OP_FIR_INBUF_LOC_SHIFT) & FFA_OP_FIR_INBUF_LOC_MASK)
#define FFA_OP_FIR_INBUF_LOC_GET(x) (((uint32_t)(x) & FFA_OP_FIR_INBUF_LOC_MASK) >> FFA_OP_FIR_INBUF_LOC_SHIFT)

/* Bitfield definition for register: OP_REG4 */
/*
 * CT (RW)
 *
 * Contents
 */
#define FFA_OP_REG4_CT_MASK (0xFFFFFFFFUL)
#define FFA_OP_REG4_CT_SHIFT (0U)
#define FFA_OP_REG4_CT_SET(x) (((uint32_t)(x) << FFA_OP_REG4_CT_SHIFT) & FFA_OP_REG4_CT_MASK)
#define FFA_OP_REG4_CT_GET(x) (((uint32_t)(x) & FFA_OP_REG4_CT_MASK) >> FFA_OP_REG4_CT_SHIFT)

/* Bitfield definition for register: OP_FIR_COEFBUF */
/*
 * LOC (RW)
 *
 * The coef buf pointer
 */
#define FFA_OP_FIR_COEFBUF_LOC_MASK (0xFFFFFFFFUL)
#define FFA_OP_FIR_COEFBUF_LOC_SHIFT (0U)
#define FFA_OP_FIR_COEFBUF_LOC_SET(x) (((uint32_t)(x) << FFA_OP_FIR_COEFBUF_LOC_SHIFT) & FFA_OP_FIR_COEFBUF_LOC_MASK)
#define FFA_OP_FIR_COEFBUF_LOC_GET(x) (((uint32_t)(x) & FFA_OP_FIR_COEFBUF_LOC_MASK) >> FFA_OP_FIR_COEFBUF_LOC_SHIFT)

/* Bitfield definition for register: OP_FFT_OUTRBUF */
/*
 * LOC (RW)
 *
 * The output (real) data buffer pointer
 */
#define FFA_OP_FFT_OUTRBUF_LOC_MASK (0xFFFFFFFFUL)
#define FFA_OP_FFT_OUTRBUF_LOC_SHIFT (0U)
#define FFA_OP_FFT_OUTRBUF_LOC_SET(x) (((uint32_t)(x) << FFA_OP_FFT_OUTRBUF_LOC_SHIFT) & FFA_OP_FFT_OUTRBUF_LOC_MASK)
#define FFA_OP_FFT_OUTRBUF_LOC_GET(x) (((uint32_t)(x) & FFA_OP_FFT_OUTRBUF_LOC_MASK) >> FFA_OP_FFT_OUTRBUF_LOC_SHIFT)

/* Bitfield definition for register: OP_REG5 */
/*
 * CT (RW)
 *
 * Contents
 */
#define FFA_OP_REG5_CT_MASK (0xFFFFFFFFUL)
#define FFA_OP_REG5_CT_SHIFT (0U)
#define FFA_OP_REG5_CT_SET(x) (((uint32_t)(x) << FFA_OP_REG5_CT_SHIFT) & FFA_OP_REG5_CT_MASK)
#define FFA_OP_REG5_CT_GET(x) (((uint32_t)(x) & FFA_OP_REG5_CT_MASK) >> FFA_OP_REG5_CT_SHIFT)

/* Bitfield definition for register: OP_FIR_OUTBUF */
/*
 * LOC (RW)
 *
 * The output data buffer pointer. The length of the output buffer should be （FIR_DATA_TAPS - FIR_COEF_TAPS + 1）
 */
#define FFA_OP_FIR_OUTBUF_LOC_MASK (0xFFFFFFFFUL)
#define FFA_OP_FIR_OUTBUF_LOC_SHIFT (0U)
#define FFA_OP_FIR_OUTBUF_LOC_SET(x) (((uint32_t)(x) << FFA_OP_FIR_OUTBUF_LOC_SHIFT) & FFA_OP_FIR_OUTBUF_LOC_MASK)
#define FFA_OP_FIR_OUTBUF_LOC_GET(x) (((uint32_t)(x) & FFA_OP_FIR_OUTBUF_LOC_MASK) >> FFA_OP_FIR_OUTBUF_LOC_SHIFT)

/* Bitfield definition for register: OP_REG6 */
/*
 * CT (RW)
 *
 * Contents
 */
#define FFA_OP_REG6_CT_MASK (0xFFFFFFFFUL)
#define FFA_OP_REG6_CT_SHIFT (0U)
#define FFA_OP_REG6_CT_SET(x) (((uint32_t)(x) << FFA_OP_REG6_CT_SHIFT) & FFA_OP_REG6_CT_MASK)
#define FFA_OP_REG6_CT_GET(x) (((uint32_t)(x) & FFA_OP_REG6_CT_MASK) >> FFA_OP_REG6_CT_SHIFT)

/* Bitfield definition for register: OP_REG7 */
/*
 * CT (RW)
 *
 * Contents
 */
#define FFA_OP_REG7_CT_MASK (0xFFFFFFFFUL)
#define FFA_OP_REG7_CT_SHIFT (0U)
#define FFA_OP_REG7_CT_SET(x) (((uint32_t)(x) << FFA_OP_REG7_CT_SHIFT) & FFA_OP_REG7_CT_MASK)
#define FFA_OP_REG7_CT_GET(x) (((uint32_t)(x) & FFA_OP_REG7_CT_MASK) >> FFA_OP_REG7_CT_SHIFT)




#endif /* HPM_FFA_H */
