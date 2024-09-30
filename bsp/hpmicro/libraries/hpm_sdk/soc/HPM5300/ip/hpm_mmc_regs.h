/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_MMC_H
#define HPM_MMC_H

typedef struct {
    __RW uint32_t CR;                          /* 0x0: Control Register */
    __RW uint32_t STA;                         /* 0x4: Status Register */
    __RW uint32_t INT_EN;                      /* 0x8: Interrupt Enable Register */
    __RW uint32_t SYSCLK_FREQ;                 /* 0xC: System Clock Frequency Register */
    __RW uint32_t SYSCLK_PERIOD;               /* 0x10: System Clock Period Register */
    __RW uint32_t OOSYNC_THETA_THR;            /* 0x14: Position Out-Of-Sync Threshold Regster */
    __RW uint32_t DISCRETECFG0;                /* 0x18: Discrete Mode Configuration 0 Register */
    __RW uint32_t DISCRETECFG1;                /* 0x1C: Discrete Mode Configuration 1 Register */
    __RW uint32_t CONTCFG0;                    /* 0x20: Continuous Mode Configuration 0 Register */
    __RW uint32_t INI_POS_TIME;                /* 0x24: The destined timestamp register for position initialization */
    __RW uint32_t INI_POS;                     /* 0x28: The destined position register for position initialization */
    __RW uint32_t INI_REV;                     /* 0x2C: The destined revolution register for position initialization */
    __RW uint32_t INI_SPEED;                   /* 0x30: The destined speed register for position initialization */
    __RW uint32_t INI_ACCEL;                   /* 0x34: The destined accelerator register for position initialization */
    __RW uint32_t INI_COEF_TIME;               /* 0x38: The destined timestamp register for coefficients initialization */
    __RW uint32_t INI_PCOEF;                   /* 0x3C: The destined coefficient P register for coefficients initialization */
    __RW uint32_t INI_ICOEF;                   /* 0x40: The destined coefficient I register for coefficients initialization */
    __RW uint32_t INI_ACOEF;                   /* 0x44: The destined coefficient A register for coefficients initialization */
    __R  uint32_t ESTM_TIM;                    /* 0x48: The timestamp register for internal estimation */
    __R  uint32_t ESTM_POS;                    /* 0x4C: The position register for the internal  estimation */
    __R  uint32_t ESTM_REV;                    /* 0x50: The revolution register for the internal  estimation */
    __R  uint32_t ESTM_SPEED;                  /* 0x54: The speed register for the internal estimation */
    __R  uint32_t ESTM_ACCEL;                  /* 0x58: The accelerator register for theinternal estimation */
    __R  uint32_t CUR_PCOEF;                   /* 0x5C: The coefficient P register for the internal estimation */
    __R  uint32_t CUR_ICOEF;                   /* 0x60: The coefficient I register for the internal estimation */
    __R  uint32_t CUR_ACOEF;                   /* 0x64: The coefficient A register for the internal estimation */
    __RW uint32_t INI_DELTA_POS_TIME;          /* 0x68: The destined timestamp register for delta position initialization */
    __RW uint32_t INI_DELTA_POS;               /* 0x6C: The destined delta position register for delta position initialization */
    __RW uint32_t INI_DELTA_REV;               /* 0x70: The destined delta revolution register for delta position initialization */
    __RW uint32_t INI_DELTA_SPEED;             /* 0x74: The destined delta speed register for delta position initialization */
    __RW uint32_t INI_DELTA_ACCEL;             /* 0x78: The destined delta accelerator register for delta position initialization */
    __R  uint8_t  RESERVED0[4];                /* 0x7C - 0x7F: Reserved */
    __RW uint32_t POS_TRG_CFG;                 /* 0x80: Tracking Configuration pos trigger cfg */
    __RW uint32_t POS_TRG_POS_THR;             /* 0x84: Tracking Configuration position threshold */
    __RW uint32_t POS_TRG_REV_THR;             /* 0x88: Tracking Configuration revolution threshold */
    __RW uint32_t SPEED_TRG_CFG;               /* 0x8C: Tracking Configuration speed trigger cfg */
    __RW uint32_t SPEED_TRG_THR;               /* 0x90: Tracking Configuration speed threshold */
    __R  uint8_t  RESERVED1[12];               /* 0x94 - 0x9F: Reserved */
    struct {
        __RW uint32_t ERR_THR;                 /* 0xA0: Tracking Configuration coef trigger cfg */
        __RW uint32_t P;                       /* 0xA4: Tracking Configuration coef trigger cfg P */
        __RW uint32_t I;                       /* 0xA8: Tracking Configuration coef trigger cfg I */
        __RW uint32_t A;                       /* 0xAC: Tracking Configuration coef trigger cfg A */
        __RW uint32_t TIME;                    /* 0xB0: Tracking Configuration coef trigger cfg time */
    } COEF_TRG_CFG[3];
    __R  uint8_t  RESERVED2[36];               /* 0xDC - 0xFF: Reserved */
    struct {
        __RW uint32_t BR_CTRL;                 /* 0x100: Prediction Control Register */
        __RW uint32_t BR_TIMEOFF;              /* 0x104: Prediction Timing Offset Register */
        __RW uint32_t BR_TRG_PERIOD;           /* 0x108: Prediction Triggering Period Offset Register */
        __RW uint32_t BR_TRG_F_TIME;           /* 0x10C: Prediction Triggering First Offset Register */
        __RW uint32_t BR_ST;                   /* 0x110: Prediction Status Register */
        __R  uint8_t  RESERVED0[44];           /* 0x114 - 0x13F: Reserved */
        __RW uint32_t BR_TRG_POS_CFG;          /* 0x140: Prediction Configuration postion trigger cfg */
        __RW uint32_t BR_TRG_POS_THR;          /* 0x144: Prediction Configuration postion threshold */
        __RW uint32_t BR_TRG_REV_THR;          /* 0x148: Prediction Configuration revolutiom threshold */
        __RW uint32_t BR_TRG_SPEED_CFG;        /* 0x14C: Prediction Configuration speed trigger cfg */
        __RW uint32_t BR_TRG_SPEED_THR;        /* 0x150: Prediction Configuration speed threshold */
        __R  uint8_t  RESERVED1[108];          /* 0x154 - 0x1BF: Reserved */
        __RW uint32_t BR_INI_POS_TIME;         /* 0x1C0: Initialization timestamp for open-loop mode */
        __RW uint32_t BR_INI_POS;              /* 0x1C4: Initialization position for open-loop mode */
        __RW uint32_t BR_INI_REV;              /* 0x1C8: Initialization revolution for open-loop mode */
        __RW uint32_t BR_INI_SPEED;            /* 0x1CC: Initialization speed for open-loop mode */
        __RW uint32_t BR_INI_ACCEL;            /* 0x1D0: Initialization acceleration for open-loop mode */
        __RW uint32_t BR_INI_DELTA_POS_TIME;   /* 0x1D4: Initialization timestamp for delta mode in prediction mode */
        __RW uint32_t BR_INI_DELTA_POS;        /* 0x1D8: Initialization delta position for delta mode in prediction mode */
        __RW uint32_t BR_INI_DELTA_REV;        /* 0x1DC: Initialization delta revolution for delta mode in prediction mode */
        __RW uint32_t BR_INI_DELTA_SPEED;      /* 0x1E0: Initialization delta speed for delta mode in prediction mode */
        __RW uint32_t BR_INI_DELTA_ACCEL;      /* 0x1E4: Initialization delta acceleration for delta mode in prediction mode */
        __R  uint8_t  RESERVED2[4];            /* 0x1E8 - 0x1EB: Reserved */
        __R  uint32_t BR_CUR_POS_TIME;         /* 0x1EC: Monitor of the output timestamp */
        __R  uint32_t BR_CUR_POS;              /* 0x1F0: Monitor of the output position */
        __R  uint32_t BR_CUR_REV;              /* 0x1F4: Monitor of the output revolution */
        __R  uint32_t BR_CUR_SPEED;            /* 0x1F8: Monitor of the output speed */
        __R  uint32_t BR_CUR_ACCEL;            /* 0x1FC: Monitor of the output acceleration */
    } BR[2];
    __R  uint32_t BK0_TIMESTAMP;               /* 0x300: Monitor of the just received input timestamp for tracing logic */
    __R  uint32_t BK0_POSITION;                /* 0x304: Monitor of the just received input position for tracing logic */
    __R  uint32_t BK0_REVOLUTION;              /* 0x308: Monitor of the just received input revolution for tracing logic */
    __R  uint32_t BK0_SPEED;                   /* 0x30C: Monitor of the just received input speed for tracing logic */
    __R  uint32_t BK0_ACCELERATOR;             /* 0x310: Monitor of the just received input acceleration for tracing logic */
    __R  uint8_t  RESERVED3[12];               /* 0x314 - 0x31F: Reserved */
    __R  uint32_t BK1_TIMESTAMP;               /* 0x320: Monitor of the previous received input timestamp for tracing logic */
    __R  uint32_t BK1_POSITION;                /* 0x324: Monitor of the previous received input position for tracing logic */
    __R  uint32_t BK1_REVOLUTION;              /* 0x328: Monitor of the previous received input revolution for tracing logic */
    __R  uint32_t BK1_SPEED;                   /* 0x32C: Monitor of the previous received input speed for tracing logic */
    __R  uint32_t BK1_ACCELERATOR;             /* 0x330: Monitor of the previous received input acceleration for tracing logic */
} MMC_Type;


/* Bitfield definition for register: CR */
/*
 * SFTRST (RW)
 *
 * Software reset, high active. When write 1 ,all internal logical will be reset.
 * 0b - No action
 * 1b - All MMC internal registers are forced into their reset state. Interface registers are not affected.
 */
#define MMC_CR_SFTRST_MASK (0x80000000UL)
#define MMC_CR_SFTRST_SHIFT (31U)
#define MMC_CR_SFTRST_SET(x) (((uint32_t)(x) << MMC_CR_SFTRST_SHIFT) & MMC_CR_SFTRST_MASK)
#define MMC_CR_SFTRST_GET(x) (((uint32_t)(x) & MMC_CR_SFTRST_MASK) >> MMC_CR_SFTRST_SHIFT)

/*
 * INI_BR0_POS_REQ (RW)
 *
 * Auto clear. Only effective in open_loop mode.
 */
#define MMC_CR_INI_BR0_POS_REQ_MASK (0x20000000UL)
#define MMC_CR_INI_BR0_POS_REQ_SHIFT (29U)
#define MMC_CR_INI_BR0_POS_REQ_SET(x) (((uint32_t)(x) << MMC_CR_INI_BR0_POS_REQ_SHIFT) & MMC_CR_INI_BR0_POS_REQ_MASK)
#define MMC_CR_INI_BR0_POS_REQ_GET(x) (((uint32_t)(x) & MMC_CR_INI_BR0_POS_REQ_MASK) >> MMC_CR_INI_BR0_POS_REQ_SHIFT)

/*
 * INI_BR1_POS_REQ (RW)
 *
 * Auto clear. Only effective in open_loop mode.
 */
#define MMC_CR_INI_BR1_POS_REQ_MASK (0x10000000UL)
#define MMC_CR_INI_BR1_POS_REQ_SHIFT (28U)
#define MMC_CR_INI_BR1_POS_REQ_SET(x) (((uint32_t)(x) << MMC_CR_INI_BR1_POS_REQ_SHIFT) & MMC_CR_INI_BR1_POS_REQ_MASK)
#define MMC_CR_INI_BR1_POS_REQ_GET(x) (((uint32_t)(x) & MMC_CR_INI_BR1_POS_REQ_MASK) >> MMC_CR_INI_BR1_POS_REQ_SHIFT)

/*
 * FRCACCELZERO (RW)
 *
 * Zeroise the accelerator calculation.
 */
#define MMC_CR_FRCACCELZERO_MASK (0x8000000UL)
#define MMC_CR_FRCACCELZERO_SHIFT (27U)
#define MMC_CR_FRCACCELZERO_SET(x) (((uint32_t)(x) << MMC_CR_FRCACCELZERO_SHIFT) & MMC_CR_FRCACCELZERO_MASK)
#define MMC_CR_FRCACCELZERO_GET(x) (((uint32_t)(x) & MMC_CR_FRCACCELZERO_MASK) >> MMC_CR_FRCACCELZERO_SHIFT)

/*
 * MS_COEF_EN (RW)
 *
 * Multiple Coefficients Enable
 */
#define MMC_CR_MS_COEF_EN_MASK (0x4000000UL)
#define MMC_CR_MS_COEF_EN_SHIFT (26U)
#define MMC_CR_MS_COEF_EN_SET(x) (((uint32_t)(x) << MMC_CR_MS_COEF_EN_SHIFT) & MMC_CR_MS_COEF_EN_MASK)
#define MMC_CR_MS_COEF_EN_GET(x) (((uint32_t)(x) & MMC_CR_MS_COEF_EN_MASK) >> MMC_CR_MS_COEF_EN_SHIFT)

/*
 * INI_DELTA_POS_TRG_TYPE (RW)
 *
 * 0: Time Stamp in the configuration
 * 1: Risedge of In Trg[0]
 * 2: Risedge of In Trg[1]
 * 3: Risedge of out trg[0]
 * 4: Risedge of out trg[1]
 * 5: triggered by self position trigger
 * 6: triggered by self speed trigger
 * Otherser: no function
 */
#define MMC_CR_INI_DELTA_POS_TRG_TYPE_MASK (0x3800000UL)
#define MMC_CR_INI_DELTA_POS_TRG_TYPE_SHIFT (23U)
#define MMC_CR_INI_DELTA_POS_TRG_TYPE_SET(x) (((uint32_t)(x) << MMC_CR_INI_DELTA_POS_TRG_TYPE_SHIFT) & MMC_CR_INI_DELTA_POS_TRG_TYPE_MASK)
#define MMC_CR_INI_DELTA_POS_TRG_TYPE_GET(x) (((uint32_t)(x) & MMC_CR_INI_DELTA_POS_TRG_TYPE_MASK) >> MMC_CR_INI_DELTA_POS_TRG_TYPE_SHIFT)

/*
 * INI_POS_TRG_TYPE (RW)
 *
 * 0: Time Stamp in the configuration
 * 1: Risedge of In Trg[0]
 * 2: Risedge of In Trg[1]
 * 3: Risedge of out trg[0]
 * 4: Risedge of out trg[1]
 * 5: triggered by self position trigger
 * 6: triggered by self speed trigger
 * Otherser: no function
 */
#define MMC_CR_INI_POS_TRG_TYPE_MASK (0x700000UL)
#define MMC_CR_INI_POS_TRG_TYPE_SHIFT (20U)
#define MMC_CR_INI_POS_TRG_TYPE_SET(x) (((uint32_t)(x) << MMC_CR_INI_POS_TRG_TYPE_SHIFT) & MMC_CR_INI_POS_TRG_TYPE_MASK)
#define MMC_CR_INI_POS_TRG_TYPE_GET(x) (((uint32_t)(x) & MMC_CR_INI_POS_TRG_TYPE_MASK) >> MMC_CR_INI_POS_TRG_TYPE_SHIFT)

/*
 * INI_DELTA_POS_CMD_MSK (RW)
 *
 * 1: change
 * 0: won't change
 * bit 3: for delta accel
 * bit 2: for delta speed
 * bit 1: for delta revolution
 * bit 0: for delta position
 */
#define MMC_CR_INI_DELTA_POS_CMD_MSK_MASK (0xF0000UL)
#define MMC_CR_INI_DELTA_POS_CMD_MSK_SHIFT (16U)
#define MMC_CR_INI_DELTA_POS_CMD_MSK_SET(x) (((uint32_t)(x) << MMC_CR_INI_DELTA_POS_CMD_MSK_SHIFT) & MMC_CR_INI_DELTA_POS_CMD_MSK_MASK)
#define MMC_CR_INI_DELTA_POS_CMD_MSK_GET(x) (((uint32_t)(x) & MMC_CR_INI_DELTA_POS_CMD_MSK_MASK) >> MMC_CR_INI_DELTA_POS_CMD_MSK_SHIFT)

/*
 * INI_DELTA_POS_REQ (RW)
 *
 * 1: Command to reload the delta pos. Auto clear
 * 0:
 */
#define MMC_CR_INI_DELTA_POS_REQ_MASK (0x8000U)
#define MMC_CR_INI_DELTA_POS_REQ_SHIFT (15U)
#define MMC_CR_INI_DELTA_POS_REQ_SET(x) (((uint32_t)(x) << MMC_CR_INI_DELTA_POS_REQ_SHIFT) & MMC_CR_INI_DELTA_POS_REQ_MASK)
#define MMC_CR_INI_DELTA_POS_REQ_GET(x) (((uint32_t)(x) & MMC_CR_INI_DELTA_POS_REQ_MASK) >> MMC_CR_INI_DELTA_POS_REQ_SHIFT)

/*
 * OPEN_LOOP_MODE (RW)
 *
 * 1: in open loop mode
 * 0: not in open loop mode
 */
#define MMC_CR_OPEN_LOOP_MODE_MASK (0x4000U)
#define MMC_CR_OPEN_LOOP_MODE_SHIFT (14U)
#define MMC_CR_OPEN_LOOP_MODE_SET(x) (((uint32_t)(x) << MMC_CR_OPEN_LOOP_MODE_SHIFT) & MMC_CR_OPEN_LOOP_MODE_MASK)
#define MMC_CR_OPEN_LOOP_MODE_GET(x) (((uint32_t)(x) & MMC_CR_OPEN_LOOP_MODE_MASK) >> MMC_CR_OPEN_LOOP_MODE_SHIFT)

/*
 * POS_TYPE (RW)
 *
 * 1: 32-bit for rev+pos, with each element occupying 16 bits
 * 0: 32-bit for rev, and 32 bit for pos
 * When CR[MANUAL_IO]==1,
 * 1: means that the INI_POS is acting as INI_POS cmds
 * 0: means that the INI_POS is simulating the input of iposition and itimestamp
 */
#define MMC_CR_POS_TYPE_MASK (0x2000U)
#define MMC_CR_POS_TYPE_SHIFT (13U)
#define MMC_CR_POS_TYPE_SET(x) (((uint32_t)(x) << MMC_CR_POS_TYPE_SHIFT) & MMC_CR_POS_TYPE_MASK)
#define MMC_CR_POS_TYPE_GET(x) (((uint32_t)(x) & MMC_CR_POS_TYPE_MASK) >> MMC_CR_POS_TYPE_SHIFT)

/*
 * INI_POS_CMD_MSK (RW)
 *
 * 1: change
 * 0: won't change
 * bit 3: for accel
 * bit 2: for speed
 * bit 1: for revolution
 * bit 0: for position
 */
#define MMC_CR_INI_POS_CMD_MSK_MASK (0x1E00U)
#define MMC_CR_INI_POS_CMD_MSK_SHIFT (9U)
#define MMC_CR_INI_POS_CMD_MSK_SET(x) (((uint32_t)(x) << MMC_CR_INI_POS_CMD_MSK_SHIFT) & MMC_CR_INI_POS_CMD_MSK_MASK)
#define MMC_CR_INI_POS_CMD_MSK_GET(x) (((uint32_t)(x) & MMC_CR_INI_POS_CMD_MSK_MASK) >> MMC_CR_INI_POS_CMD_MSK_SHIFT)

/*
 * INI_POS_REQ (RW)
 *
 * 1: Command to reload the positions. Auto clear
 * 0:
 */
#define MMC_CR_INI_POS_REQ_MASK (0x100U)
#define MMC_CR_INI_POS_REQ_SHIFT (8U)
#define MMC_CR_INI_POS_REQ_SET(x) (((uint32_t)(x) << MMC_CR_INI_POS_REQ_SHIFT) & MMC_CR_INI_POS_REQ_MASK)
#define MMC_CR_INI_POS_REQ_GET(x) (((uint32_t)(x) & MMC_CR_INI_POS_REQ_MASK) >> MMC_CR_INI_POS_REQ_SHIFT)

/*
 * INI_COEFS_CMD_MSK (RW)
 *
 * 1: change
 * 0: won't change
 * bit 2: for ACOEF
 * bit 1: for ICOEF
 * bit 0: for PCOEF
 */
#define MMC_CR_INI_COEFS_CMD_MSK_MASK (0xE0U)
#define MMC_CR_INI_COEFS_CMD_MSK_SHIFT (5U)
#define MMC_CR_INI_COEFS_CMD_MSK_SET(x) (((uint32_t)(x) << MMC_CR_INI_COEFS_CMD_MSK_SHIFT) & MMC_CR_INI_COEFS_CMD_MSK_MASK)
#define MMC_CR_INI_COEFS_CMD_MSK_GET(x) (((uint32_t)(x) & MMC_CR_INI_COEFS_CMD_MSK_MASK) >> MMC_CR_INI_COEFS_CMD_MSK_SHIFT)

/*
 * INI_COEFS_CMD (RW)
 *
 * 1: Command to reload the coefs. Auto clear
 * 0:
 */
#define MMC_CR_INI_COEFS_CMD_MASK (0x10U)
#define MMC_CR_INI_COEFS_CMD_SHIFT (4U)
#define MMC_CR_INI_COEFS_CMD_SET(x) (((uint32_t)(x) << MMC_CR_INI_COEFS_CMD_SHIFT) & MMC_CR_INI_COEFS_CMD_MASK)
#define MMC_CR_INI_COEFS_CMD_GET(x) (((uint32_t)(x) & MMC_CR_INI_COEFS_CMD_MASK) >> MMC_CR_INI_COEFS_CMD_SHIFT)

/*
 * SHADOW_RD_REQ (RW)
 *
 * 1: Shadow Request for read of tracking parameters. Auto clear
 * 0:
 */
#define MMC_CR_SHADOW_RD_REQ_MASK (0x8U)
#define MMC_CR_SHADOW_RD_REQ_SHIFT (3U)
#define MMC_CR_SHADOW_RD_REQ_SET(x) (((uint32_t)(x) << MMC_CR_SHADOW_RD_REQ_SHIFT) & MMC_CR_SHADOW_RD_REQ_MASK)
#define MMC_CR_SHADOW_RD_REQ_GET(x) (((uint32_t)(x) & MMC_CR_SHADOW_RD_REQ_MASK) >> MMC_CR_SHADOW_RD_REQ_SHIFT)

/*
 * ADJOP (RW)
 *
 * 1: use the input iposition whenever a new iposition comes, and force the predicted output stop at the boundaries.
 * 0: Continuous tracking mode, without any boundary check
 */
#define MMC_CR_ADJOP_MASK (0x4U)
#define MMC_CR_ADJOP_SHIFT (2U)
#define MMC_CR_ADJOP_SET(x) (((uint32_t)(x) << MMC_CR_ADJOP_SHIFT) & MMC_CR_ADJOP_MASK)
#define MMC_CR_ADJOP_GET(x) (((uint32_t)(x) & MMC_CR_ADJOP_MASK) >> MMC_CR_ADJOP_SHIFT)

/*
 * DISCRETETRC (RW)
 *
 * 1: Discrete position input
 * 0: Continuous position input
 */
#define MMC_CR_DISCRETETRC_MASK (0x2U)
#define MMC_CR_DISCRETETRC_SHIFT (1U)
#define MMC_CR_DISCRETETRC_SET(x) (((uint32_t)(x) << MMC_CR_DISCRETETRC_SHIFT) & MMC_CR_DISCRETETRC_MASK)
#define MMC_CR_DISCRETETRC_GET(x) (((uint32_t)(x) & MMC_CR_DISCRETETRC_MASK) >> MMC_CR_DISCRETETRC_SHIFT)

/*
 * MOD_EN (RW)
 *
 * Module Enable
 */
#define MMC_CR_MOD_EN_MASK (0x1U)
#define MMC_CR_MOD_EN_SHIFT (0U)
#define MMC_CR_MOD_EN_SET(x) (((uint32_t)(x) << MMC_CR_MOD_EN_SHIFT) & MMC_CR_MOD_EN_MASK)
#define MMC_CR_MOD_EN_GET(x) (((uint32_t)(x) & MMC_CR_MOD_EN_MASK) >> MMC_CR_MOD_EN_SHIFT)

/* Bitfield definition for register: STA */
/*
 * ERR_ID (RO)
 *
 * Tracking ERR_ID
 */
#define MMC_STA_ERR_ID_MASK (0xF0000000UL)
#define MMC_STA_ERR_ID_SHIFT (28U)
#define MMC_STA_ERR_ID_GET(x) (((uint32_t)(x) & MMC_STA_ERR_ID_MASK) >> MMC_STA_ERR_ID_SHIFT)

/*
 * SPEED_TRG_VALID (W1C)
 *
 * W1C
 */
#define MMC_STA_SPEED_TRG_VALID_MASK (0x400U)
#define MMC_STA_SPEED_TRG_VALID_SHIFT (10U)
#define MMC_STA_SPEED_TRG_VALID_SET(x) (((uint32_t)(x) << MMC_STA_SPEED_TRG_VALID_SHIFT) & MMC_STA_SPEED_TRG_VALID_MASK)
#define MMC_STA_SPEED_TRG_VALID_GET(x) (((uint32_t)(x) & MMC_STA_SPEED_TRG_VALID_MASK) >> MMC_STA_SPEED_TRG_VALID_SHIFT)

/*
 * POS_TRG_VALID (W1C)
 *
 * W1C
 */
#define MMC_STA_POS_TRG_VALID_MASK (0x200U)
#define MMC_STA_POS_TRG_VALID_SHIFT (9U)
#define MMC_STA_POS_TRG_VALID_SET(x) (((uint32_t)(x) << MMC_STA_POS_TRG_VALID_SHIFT) & MMC_STA_POS_TRG_VALID_MASK)
#define MMC_STA_POS_TRG_VALID_GET(x) (((uint32_t)(x) & MMC_STA_POS_TRG_VALID_MASK) >> MMC_STA_POS_TRG_VALID_SHIFT)

/*
 * INI_DELTA_POS_REQ_CMD_DONE (W1C)
 *
 * W1C
 */
#define MMC_STA_INI_DELTA_POS_REQ_CMD_DONE_MASK (0x100U)
#define MMC_STA_INI_DELTA_POS_REQ_CMD_DONE_SHIFT (8U)
#define MMC_STA_INI_DELTA_POS_REQ_CMD_DONE_SET(x) (((uint32_t)(x) << MMC_STA_INI_DELTA_POS_REQ_CMD_DONE_SHIFT) & MMC_STA_INI_DELTA_POS_REQ_CMD_DONE_MASK)
#define MMC_STA_INI_DELTA_POS_REQ_CMD_DONE_GET(x) (((uint32_t)(x) & MMC_STA_INI_DELTA_POS_REQ_CMD_DONE_MASK) >> MMC_STA_INI_DELTA_POS_REQ_CMD_DONE_SHIFT)

/*
 * INI_BR0_POS_REQ_CMD_DONE (W1C)
 *
 * W1C
 */
#define MMC_STA_INI_BR0_POS_REQ_CMD_DONE_MASK (0x80U)
#define MMC_STA_INI_BR0_POS_REQ_CMD_DONE_SHIFT (7U)
#define MMC_STA_INI_BR0_POS_REQ_CMD_DONE_SET(x) (((uint32_t)(x) << MMC_STA_INI_BR0_POS_REQ_CMD_DONE_SHIFT) & MMC_STA_INI_BR0_POS_REQ_CMD_DONE_MASK)
#define MMC_STA_INI_BR0_POS_REQ_CMD_DONE_GET(x) (((uint32_t)(x) & MMC_STA_INI_BR0_POS_REQ_CMD_DONE_MASK) >> MMC_STA_INI_BR0_POS_REQ_CMD_DONE_SHIFT)

/*
 * INI_BR1_POS_REQ_CMD_DONE (W1C)
 *
 * W1C
 */
#define MMC_STA_INI_BR1_POS_REQ_CMD_DONE_MASK (0x40U)
#define MMC_STA_INI_BR1_POS_REQ_CMD_DONE_SHIFT (6U)
#define MMC_STA_INI_BR1_POS_REQ_CMD_DONE_SET(x) (((uint32_t)(x) << MMC_STA_INI_BR1_POS_REQ_CMD_DONE_SHIFT) & MMC_STA_INI_BR1_POS_REQ_CMD_DONE_MASK)
#define MMC_STA_INI_BR1_POS_REQ_CMD_DONE_GET(x) (((uint32_t)(x) & MMC_STA_INI_BR1_POS_REQ_CMD_DONE_MASK) >> MMC_STA_INI_BR1_POS_REQ_CMD_DONE_SHIFT)

/*
 * IDLE (RO)
 *
 * Tracking Module in Idle status
 */
#define MMC_STA_IDLE_MASK (0x20U)
#define MMC_STA_IDLE_SHIFT (5U)
#define MMC_STA_IDLE_GET(x) (((uint32_t)(x) & MMC_STA_IDLE_MASK) >> MMC_STA_IDLE_SHIFT)

/*
 * OOSYNC (W1C)
 *
 * Tracking module out-of sync. W1C
 */
#define MMC_STA_OOSYNC_MASK (0x10U)
#define MMC_STA_OOSYNC_SHIFT (4U)
#define MMC_STA_OOSYNC_SET(x) (((uint32_t)(x) << MMC_STA_OOSYNC_SHIFT) & MMC_STA_OOSYNC_MASK)
#define MMC_STA_OOSYNC_GET(x) (((uint32_t)(x) & MMC_STA_OOSYNC_MASK) >> MMC_STA_OOSYNC_SHIFT)

/*
 * INI_POS_REQ_CMD_DONE (W1C)
 *
 * W1C
 */
#define MMC_STA_INI_POS_REQ_CMD_DONE_MASK (0x4U)
#define MMC_STA_INI_POS_REQ_CMD_DONE_SHIFT (2U)
#define MMC_STA_INI_POS_REQ_CMD_DONE_SET(x) (((uint32_t)(x) << MMC_STA_INI_POS_REQ_CMD_DONE_SHIFT) & MMC_STA_INI_POS_REQ_CMD_DONE_MASK)
#define MMC_STA_INI_POS_REQ_CMD_DONE_GET(x) (((uint32_t)(x) & MMC_STA_INI_POS_REQ_CMD_DONE_MASK) >> MMC_STA_INI_POS_REQ_CMD_DONE_SHIFT)

/*
 * INI_COEFS_CMD_DONE (W1C)
 *
 * W1C
 */
#define MMC_STA_INI_COEFS_CMD_DONE_MASK (0x2U)
#define MMC_STA_INI_COEFS_CMD_DONE_SHIFT (1U)
#define MMC_STA_INI_COEFS_CMD_DONE_SET(x) (((uint32_t)(x) << MMC_STA_INI_COEFS_CMD_DONE_SHIFT) & MMC_STA_INI_COEFS_CMD_DONE_MASK)
#define MMC_STA_INI_COEFS_CMD_DONE_GET(x) (((uint32_t)(x) & MMC_STA_INI_COEFS_CMD_DONE_MASK) >> MMC_STA_INI_COEFS_CMD_DONE_SHIFT)

/*
 * SHADOW_RD_DONE (RO)
 *
 * Shadow ready for read. Auto cleared by setting CR[SHADOW_RD_REQ] as 1
 */
#define MMC_STA_SHADOW_RD_DONE_MASK (0x1U)
#define MMC_STA_SHADOW_RD_DONE_SHIFT (0U)
#define MMC_STA_SHADOW_RD_DONE_GET(x) (((uint32_t)(x) & MMC_STA_SHADOW_RD_DONE_MASK) >> MMC_STA_SHADOW_RD_DONE_SHIFT)

/* Bitfield definition for register: INT_EN */
/*
 * SPEED_TRG_VLD_IE (RW)
 *
 * Interrupt Enable for SPEED_TRG_VALID
 */
#define MMC_INT_EN_SPEED_TRG_VLD_IE_MASK (0x400U)
#define MMC_INT_EN_SPEED_TRG_VLD_IE_SHIFT (10U)
#define MMC_INT_EN_SPEED_TRG_VLD_IE_SET(x) (((uint32_t)(x) << MMC_INT_EN_SPEED_TRG_VLD_IE_SHIFT) & MMC_INT_EN_SPEED_TRG_VLD_IE_MASK)
#define MMC_INT_EN_SPEED_TRG_VLD_IE_GET(x) (((uint32_t)(x) & MMC_INT_EN_SPEED_TRG_VLD_IE_MASK) >> MMC_INT_EN_SPEED_TRG_VLD_IE_SHIFT)

/*
 * POS_TRG_VLD_IE (RW)
 *
 * Interrupt Enable for POS_TRG_VALID
 */
#define MMC_INT_EN_POS_TRG_VLD_IE_MASK (0x200U)
#define MMC_INT_EN_POS_TRG_VLD_IE_SHIFT (9U)
#define MMC_INT_EN_POS_TRG_VLD_IE_SET(x) (((uint32_t)(x) << MMC_INT_EN_POS_TRG_VLD_IE_SHIFT) & MMC_INT_EN_POS_TRG_VLD_IE_MASK)
#define MMC_INT_EN_POS_TRG_VLD_IE_GET(x) (((uint32_t)(x) & MMC_INT_EN_POS_TRG_VLD_IE_MASK) >> MMC_INT_EN_POS_TRG_VLD_IE_SHIFT)

/*
 * INI_DELTA_POS_REQ_CMD_DONE_IE (RW)
 *
 * Interrupt Enable for INI_DELTA_POS_REQ_CMD_DONE
 */
#define MMC_INT_EN_INI_DELTA_POS_REQ_CMD_DONE_IE_MASK (0x100U)
#define MMC_INT_EN_INI_DELTA_POS_REQ_CMD_DONE_IE_SHIFT (8U)
#define MMC_INT_EN_INI_DELTA_POS_REQ_CMD_DONE_IE_SET(x) (((uint32_t)(x) << MMC_INT_EN_INI_DELTA_POS_REQ_CMD_DONE_IE_SHIFT) & MMC_INT_EN_INI_DELTA_POS_REQ_CMD_DONE_IE_MASK)
#define MMC_INT_EN_INI_DELTA_POS_REQ_CMD_DONE_IE_GET(x) (((uint32_t)(x) & MMC_INT_EN_INI_DELTA_POS_REQ_CMD_DONE_IE_MASK) >> MMC_INT_EN_INI_DELTA_POS_REQ_CMD_DONE_IE_SHIFT)

/*
 * INI_BR0_POS_REQ_CMD_DONE_IE (RW)
 *
 * Interrupt Enable for INI_BR0_POS_REQ_CMD_DONE
 */
#define MMC_INT_EN_INI_BR0_POS_REQ_CMD_DONE_IE_MASK (0x80U)
#define MMC_INT_EN_INI_BR0_POS_REQ_CMD_DONE_IE_SHIFT (7U)
#define MMC_INT_EN_INI_BR0_POS_REQ_CMD_DONE_IE_SET(x) (((uint32_t)(x) << MMC_INT_EN_INI_BR0_POS_REQ_CMD_DONE_IE_SHIFT) & MMC_INT_EN_INI_BR0_POS_REQ_CMD_DONE_IE_MASK)
#define MMC_INT_EN_INI_BR0_POS_REQ_CMD_DONE_IE_GET(x) (((uint32_t)(x) & MMC_INT_EN_INI_BR0_POS_REQ_CMD_DONE_IE_MASK) >> MMC_INT_EN_INI_BR0_POS_REQ_CMD_DONE_IE_SHIFT)

/*
 * INI_BR1_POS_REQ_CMD_DONE_IE (RW)
 *
 * Interrupt Enable for INI_BR1_POS_REQ_CMD_DONE
 */
#define MMC_INT_EN_INI_BR1_POS_REQ_CMD_DONE_IE_MASK (0x40U)
#define MMC_INT_EN_INI_BR1_POS_REQ_CMD_DONE_IE_SHIFT (6U)
#define MMC_INT_EN_INI_BR1_POS_REQ_CMD_DONE_IE_SET(x) (((uint32_t)(x) << MMC_INT_EN_INI_BR1_POS_REQ_CMD_DONE_IE_SHIFT) & MMC_INT_EN_INI_BR1_POS_REQ_CMD_DONE_IE_MASK)
#define MMC_INT_EN_INI_BR1_POS_REQ_CMD_DONE_IE_GET(x) (((uint32_t)(x) & MMC_INT_EN_INI_BR1_POS_REQ_CMD_DONE_IE_MASK) >> MMC_INT_EN_INI_BR1_POS_REQ_CMD_DONE_IE_SHIFT)

/*
 * OOSYNC_IE (RW)
 *
 * Interrupt Enable for OOSYNC
 */
#define MMC_INT_EN_OOSYNC_IE_MASK (0x10U)
#define MMC_INT_EN_OOSYNC_IE_SHIFT (4U)
#define MMC_INT_EN_OOSYNC_IE_SET(x) (((uint32_t)(x) << MMC_INT_EN_OOSYNC_IE_SHIFT) & MMC_INT_EN_OOSYNC_IE_MASK)
#define MMC_INT_EN_OOSYNC_IE_GET(x) (((uint32_t)(x) & MMC_INT_EN_OOSYNC_IE_MASK) >> MMC_INT_EN_OOSYNC_IE_SHIFT)

/*
 * INI_POS_REQ_CMD_DONE_IE (RW)
 *
 * Interrupt Enable for INI_POS_REQ_CMD_DONE
 */
#define MMC_INT_EN_INI_POS_REQ_CMD_DONE_IE_MASK (0x4U)
#define MMC_INT_EN_INI_POS_REQ_CMD_DONE_IE_SHIFT (2U)
#define MMC_INT_EN_INI_POS_REQ_CMD_DONE_IE_SET(x) (((uint32_t)(x) << MMC_INT_EN_INI_POS_REQ_CMD_DONE_IE_SHIFT) & MMC_INT_EN_INI_POS_REQ_CMD_DONE_IE_MASK)
#define MMC_INT_EN_INI_POS_REQ_CMD_DONE_IE_GET(x) (((uint32_t)(x) & MMC_INT_EN_INI_POS_REQ_CMD_DONE_IE_MASK) >> MMC_INT_EN_INI_POS_REQ_CMD_DONE_IE_SHIFT)

/*
 * INI_COEFS_CMD_DONE_IE (RW)
 *
 * Interrupt Enable for INI_COEFS_CMD_DONE
 */
#define MMC_INT_EN_INI_COEFS_CMD_DONE_IE_MASK (0x2U)
#define MMC_INT_EN_INI_COEFS_CMD_DONE_IE_SHIFT (1U)
#define MMC_INT_EN_INI_COEFS_CMD_DONE_IE_SET(x) (((uint32_t)(x) << MMC_INT_EN_INI_COEFS_CMD_DONE_IE_SHIFT) & MMC_INT_EN_INI_COEFS_CMD_DONE_IE_MASK)
#define MMC_INT_EN_INI_COEFS_CMD_DONE_IE_GET(x) (((uint32_t)(x) & MMC_INT_EN_INI_COEFS_CMD_DONE_IE_MASK) >> MMC_INT_EN_INI_COEFS_CMD_DONE_IE_SHIFT)

/*
 * SHADOW_RD_DONE_IE (RW)
 *
 * Interrupt Enable for SHADOW_RD_DONE
 */
#define MMC_INT_EN_SHADOW_RD_DONE_IE_MASK (0x1U)
#define MMC_INT_EN_SHADOW_RD_DONE_IE_SHIFT (0U)
#define MMC_INT_EN_SHADOW_RD_DONE_IE_SET(x) (((uint32_t)(x) << MMC_INT_EN_SHADOW_RD_DONE_IE_SHIFT) & MMC_INT_EN_SHADOW_RD_DONE_IE_MASK)
#define MMC_INT_EN_SHADOW_RD_DONE_IE_GET(x) (((uint32_t)(x) & MMC_INT_EN_SHADOW_RD_DONE_IE_MASK) >> MMC_INT_EN_SHADOW_RD_DONE_IE_SHIFT)

/* Bitfield definition for register: SYSCLK_FREQ */
/*
 * VAL (RW)
 *
 * system clock frequency, ufix<32, 0>
 */
#define MMC_SYSCLK_FREQ_VAL_MASK (0xFFFFFFFFUL)
#define MMC_SYSCLK_FREQ_VAL_SHIFT (0U)
#define MMC_SYSCLK_FREQ_VAL_SET(x) (((uint32_t)(x) << MMC_SYSCLK_FREQ_VAL_SHIFT) & MMC_SYSCLK_FREQ_VAL_MASK)
#define MMC_SYSCLK_FREQ_VAL_GET(x) (((uint32_t)(x) & MMC_SYSCLK_FREQ_VAL_MASK) >> MMC_SYSCLK_FREQ_VAL_SHIFT)

/* Bitfield definition for register: SYSCLK_PERIOD */
/*
 * VAL (RW)
 *
 * round( the value of clock period * (2^24)*(2^20) ), ufix<32, 0>
 */
#define MMC_SYSCLK_PERIOD_VAL_MASK (0xFFFFFFFFUL)
#define MMC_SYSCLK_PERIOD_VAL_SHIFT (0U)
#define MMC_SYSCLK_PERIOD_VAL_SET(x) (((uint32_t)(x) << MMC_SYSCLK_PERIOD_VAL_SHIFT) & MMC_SYSCLK_PERIOD_VAL_MASK)
#define MMC_SYSCLK_PERIOD_VAL_GET(x) (((uint32_t)(x) & MMC_SYSCLK_PERIOD_VAL_MASK) >> MMC_SYSCLK_PERIOD_VAL_SHIFT)

/* Bitfield definition for register: OOSYNC_THETA_THR */
/*
 * VAL (RW)
 *
 * the threshold of theta difference between actual and prediction for out-of-sync determination，ufix<32, 32>
 */
#define MMC_OOSYNC_THETA_THR_VAL_MASK (0xFFFFFFFFUL)
#define MMC_OOSYNC_THETA_THR_VAL_SHIFT (0U)
#define MMC_OOSYNC_THETA_THR_VAL_SET(x) (((uint32_t)(x) << MMC_OOSYNC_THETA_THR_VAL_SHIFT) & MMC_OOSYNC_THETA_THR_VAL_MASK)
#define MMC_OOSYNC_THETA_THR_VAL_GET(x) (((uint32_t)(x) & MMC_OOSYNC_THETA_THR_VAL_MASK) >> MMC_OOSYNC_THETA_THR_VAL_SHIFT)

/* Bitfield definition for register: DISCRETECFG0 */
/*
 * POSMAX (RW)
 *
 * Max ID Of Lines. For example-1, for 512 lines, it is 511. ufix<32, 0>
 */
#define MMC_DISCRETECFG0_POSMAX_MASK (0xFFFFFUL)
#define MMC_DISCRETECFG0_POSMAX_SHIFT (0U)
#define MMC_DISCRETECFG0_POSMAX_SET(x) (((uint32_t)(x) << MMC_DISCRETECFG0_POSMAX_SHIFT) & MMC_DISCRETECFG0_POSMAX_MASK)
#define MMC_DISCRETECFG0_POSMAX_GET(x) (((uint32_t)(x) & MMC_DISCRETECFG0_POSMAX_MASK) >> MMC_DISCRETECFG0_POSMAX_SHIFT)

/* Bitfield definition for register: DISCRETECFG1 */
/*
 * INV_POSMAX (RW)
 *
 * discrete mode: ufix<32, 0> of 1/(Number Of Lines)
 * continuous mode: the max delta for tracking from the last received position, ufix<32, 32>
 */
#define MMC_DISCRETECFG1_INV_POSMAX_MASK (0xFFFFFFFFUL)
#define MMC_DISCRETECFG1_INV_POSMAX_SHIFT (0U)
#define MMC_DISCRETECFG1_INV_POSMAX_SET(x) (((uint32_t)(x) << MMC_DISCRETECFG1_INV_POSMAX_SHIFT) & MMC_DISCRETECFG1_INV_POSMAX_MASK)
#define MMC_DISCRETECFG1_INV_POSMAX_GET(x) (((uint32_t)(x) & MMC_DISCRETECFG1_INV_POSMAX_MASK) >> MMC_DISCRETECFG1_INV_POSMAX_SHIFT)

/* Bitfield definition for register: CONTCFG0 */
/*
 * HALF_CIRC_THETA (RW)
 *
 * the theta for cal the clockwise or anticlockwise rotation between two adjacent inputs, ufix<32, 32>
 */
#define MMC_CONTCFG0_HALF_CIRC_THETA_MASK (0xFFFFFFFFUL)
#define MMC_CONTCFG0_HALF_CIRC_THETA_SHIFT (0U)
#define MMC_CONTCFG0_HALF_CIRC_THETA_SET(x) (((uint32_t)(x) << MMC_CONTCFG0_HALF_CIRC_THETA_SHIFT) & MMC_CONTCFG0_HALF_CIRC_THETA_MASK)
#define MMC_CONTCFG0_HALF_CIRC_THETA_GET(x) (((uint32_t)(x) & MMC_CONTCFG0_HALF_CIRC_THETA_MASK) >> MMC_CONTCFG0_HALF_CIRC_THETA_SHIFT)

/* Bitfield definition for register: INI_POS_TIME */
/*
 * VAL (RW)
 *
 * indicate the time to change the values.
 * 0: instant change
 */
#define MMC_INI_POS_TIME_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_POS_TIME_VAL_SHIFT (0U)
#define MMC_INI_POS_TIME_VAL_SET(x) (((uint32_t)(x) << MMC_INI_POS_TIME_VAL_SHIFT) & MMC_INI_POS_TIME_VAL_MASK)
#define MMC_INI_POS_TIME_VAL_GET(x) (((uint32_t)(x) & MMC_INI_POS_TIME_VAL_MASK) >> MMC_INI_POS_TIME_VAL_SHIFT)

/* Bitfield definition for register: INI_POS */
/*
 * VAL (RW)
 *
 * the value；
 * continuous mode: ufix<32, 32>
 */
#define MMC_INI_POS_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_POS_VAL_SHIFT (0U)
#define MMC_INI_POS_VAL_SET(x) (((uint32_t)(x) << MMC_INI_POS_VAL_SHIFT) & MMC_INI_POS_VAL_MASK)
#define MMC_INI_POS_VAL_GET(x) (((uint32_t)(x) & MMC_INI_POS_VAL_MASK) >> MMC_INI_POS_VAL_SHIFT)

/* Bitfield definition for register: INI_REV */
/*
 * VAL (RW)
 *
 * the value；
 * continuous mode: ufix<32, 0>
 */
#define MMC_INI_REV_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_REV_VAL_SHIFT (0U)
#define MMC_INI_REV_VAL_SET(x) (((uint32_t)(x) << MMC_INI_REV_VAL_SHIFT) & MMC_INI_REV_VAL_MASK)
#define MMC_INI_REV_VAL_GET(x) (((uint32_t)(x) & MMC_INI_REV_VAL_MASK) >> MMC_INI_REV_VAL_SHIFT)

/* Bitfield definition for register: INI_SPEED */
/*
 * VAL (RW)
 *
 * the value;
 * continuous mode: fix<32, 19>
 */
#define MMC_INI_SPEED_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_SPEED_VAL_SHIFT (0U)
#define MMC_INI_SPEED_VAL_SET(x) (((uint32_t)(x) << MMC_INI_SPEED_VAL_SHIFT) & MMC_INI_SPEED_VAL_MASK)
#define MMC_INI_SPEED_VAL_GET(x) (((uint32_t)(x) & MMC_INI_SPEED_VAL_MASK) >> MMC_INI_SPEED_VAL_SHIFT)

/* Bitfield definition for register: INI_ACCEL */
/*
 * VAL (RW)
 *
 * the value
 * continuous mode: fix<32, 19>
 */
#define MMC_INI_ACCEL_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_ACCEL_VAL_SHIFT (0U)
#define MMC_INI_ACCEL_VAL_SET(x) (((uint32_t)(x) << MMC_INI_ACCEL_VAL_SHIFT) & MMC_INI_ACCEL_VAL_MASK)
#define MMC_INI_ACCEL_VAL_GET(x) (((uint32_t)(x) & MMC_INI_ACCEL_VAL_MASK) >> MMC_INI_ACCEL_VAL_SHIFT)

/* Bitfield definition for register: INI_COEF_TIME */
/*
 * VAL (RW)
 *
 * indicate the time to change the values.
 * 0: instant change
 */
#define MMC_INI_COEF_TIME_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_COEF_TIME_VAL_SHIFT (0U)
#define MMC_INI_COEF_TIME_VAL_SET(x) (((uint32_t)(x) << MMC_INI_COEF_TIME_VAL_SHIFT) & MMC_INI_COEF_TIME_VAL_MASK)
#define MMC_INI_COEF_TIME_VAL_GET(x) (((uint32_t)(x) & MMC_INI_COEF_TIME_VAL_MASK) >> MMC_INI_COEF_TIME_VAL_SHIFT)

/* Bitfield definition for register: INI_PCOEF */
/*
 * VAL (RW)
 *
 * the value, fix<32, 15>
 */
#define MMC_INI_PCOEF_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_PCOEF_VAL_SHIFT (0U)
#define MMC_INI_PCOEF_VAL_SET(x) (((uint32_t)(x) << MMC_INI_PCOEF_VAL_SHIFT) & MMC_INI_PCOEF_VAL_MASK)
#define MMC_INI_PCOEF_VAL_GET(x) (((uint32_t)(x) & MMC_INI_PCOEF_VAL_MASK) >> MMC_INI_PCOEF_VAL_SHIFT)

/* Bitfield definition for register: INI_ICOEF */
/*
 * VAL (RW)
 *
 * the value, fix<32, 21>
 */
#define MMC_INI_ICOEF_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_ICOEF_VAL_SHIFT (0U)
#define MMC_INI_ICOEF_VAL_SET(x) (((uint32_t)(x) << MMC_INI_ICOEF_VAL_SHIFT) & MMC_INI_ICOEF_VAL_MASK)
#define MMC_INI_ICOEF_VAL_GET(x) (((uint32_t)(x) & MMC_INI_ICOEF_VAL_MASK) >> MMC_INI_ICOEF_VAL_SHIFT)

/* Bitfield definition for register: INI_ACOEF */
/*
 * VAL (RW)
 *
 * the value, fix<32, 19>
 */
#define MMC_INI_ACOEF_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_ACOEF_VAL_SHIFT (0U)
#define MMC_INI_ACOEF_VAL_SET(x) (((uint32_t)(x) << MMC_INI_ACOEF_VAL_SHIFT) & MMC_INI_ACOEF_VAL_MASK)
#define MMC_INI_ACOEF_VAL_GET(x) (((uint32_t)(x) & MMC_INI_ACOEF_VAL_MASK) >> MMC_INI_ACOEF_VAL_SHIFT)

/* Bitfield definition for register: ESTM_TIM */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_ESTM_TIM_VAL_MASK (0xFFFFFFFFUL)
#define MMC_ESTM_TIM_VAL_SHIFT (0U)
#define MMC_ESTM_TIM_VAL_GET(x) (((uint32_t)(x) & MMC_ESTM_TIM_VAL_MASK) >> MMC_ESTM_TIM_VAL_SHIFT)

/* Bitfield definition for register: ESTM_POS */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_ESTM_POS_VAL_MASK (0xFFFFFFFFUL)
#define MMC_ESTM_POS_VAL_SHIFT (0U)
#define MMC_ESTM_POS_VAL_GET(x) (((uint32_t)(x) & MMC_ESTM_POS_VAL_MASK) >> MMC_ESTM_POS_VAL_SHIFT)

/* Bitfield definition for register: ESTM_REV */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_ESTM_REV_VAL_MASK (0xFFFFFFFFUL)
#define MMC_ESTM_REV_VAL_SHIFT (0U)
#define MMC_ESTM_REV_VAL_GET(x) (((uint32_t)(x) & MMC_ESTM_REV_VAL_MASK) >> MMC_ESTM_REV_VAL_SHIFT)

/* Bitfield definition for register: ESTM_SPEED */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_ESTM_SPEED_VAL_MASK (0xFFFFFFFFUL)
#define MMC_ESTM_SPEED_VAL_SHIFT (0U)
#define MMC_ESTM_SPEED_VAL_GET(x) (((uint32_t)(x) & MMC_ESTM_SPEED_VAL_MASK) >> MMC_ESTM_SPEED_VAL_SHIFT)

/* Bitfield definition for register: ESTM_ACCEL */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_ESTM_ACCEL_VAL_MASK (0xFFFFFFFFUL)
#define MMC_ESTM_ACCEL_VAL_SHIFT (0U)
#define MMC_ESTM_ACCEL_VAL_GET(x) (((uint32_t)(x) & MMC_ESTM_ACCEL_VAL_MASK) >> MMC_ESTM_ACCEL_VAL_SHIFT)

/* Bitfield definition for register: CUR_PCOEF */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_CUR_PCOEF_VAL_MASK (0xFFFFFFFFUL)
#define MMC_CUR_PCOEF_VAL_SHIFT (0U)
#define MMC_CUR_PCOEF_VAL_GET(x) (((uint32_t)(x) & MMC_CUR_PCOEF_VAL_MASK) >> MMC_CUR_PCOEF_VAL_SHIFT)

/* Bitfield definition for register: CUR_ICOEF */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_CUR_ICOEF_VAL_MASK (0xFFFFFFFFUL)
#define MMC_CUR_ICOEF_VAL_SHIFT (0U)
#define MMC_CUR_ICOEF_VAL_GET(x) (((uint32_t)(x) & MMC_CUR_ICOEF_VAL_MASK) >> MMC_CUR_ICOEF_VAL_SHIFT)

/* Bitfield definition for register: CUR_ACOEF */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_CUR_ACOEF_VAL_MASK (0xFFFFFFFFUL)
#define MMC_CUR_ACOEF_VAL_SHIFT (0U)
#define MMC_CUR_ACOEF_VAL_GET(x) (((uint32_t)(x) & MMC_CUR_ACOEF_VAL_MASK) >> MMC_CUR_ACOEF_VAL_SHIFT)

/* Bitfield definition for register: INI_DELTA_POS_TIME */
/*
 * VAL (RW)
 *
 * indicate the time to change the values.
 * 0: instant change
 */
#define MMC_INI_DELTA_POS_TIME_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_DELTA_POS_TIME_VAL_SHIFT (0U)
#define MMC_INI_DELTA_POS_TIME_VAL_SET(x) (((uint32_t)(x) << MMC_INI_DELTA_POS_TIME_VAL_SHIFT) & MMC_INI_DELTA_POS_TIME_VAL_MASK)
#define MMC_INI_DELTA_POS_TIME_VAL_GET(x) (((uint32_t)(x) & MMC_INI_DELTA_POS_TIME_VAL_MASK) >> MMC_INI_DELTA_POS_TIME_VAL_SHIFT)

/* Bitfield definition for register: INI_DELTA_POS */
/*
 * VAL (RW)
 *
 * the value
 * continuous mode: ufix <32, 32>
 */
#define MMC_INI_DELTA_POS_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_DELTA_POS_VAL_SHIFT (0U)
#define MMC_INI_DELTA_POS_VAL_SET(x) (((uint32_t)(x) << MMC_INI_DELTA_POS_VAL_SHIFT) & MMC_INI_DELTA_POS_VAL_MASK)
#define MMC_INI_DELTA_POS_VAL_GET(x) (((uint32_t)(x) & MMC_INI_DELTA_POS_VAL_MASK) >> MMC_INI_DELTA_POS_VAL_SHIFT)

/* Bitfield definition for register: INI_DELTA_REV */
/*
 * VAL (RW)
 *
 * the value
 * continuous mode: fix<32, 0>
 */
#define MMC_INI_DELTA_REV_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_DELTA_REV_VAL_SHIFT (0U)
#define MMC_INI_DELTA_REV_VAL_SET(x) (((uint32_t)(x) << MMC_INI_DELTA_REV_VAL_SHIFT) & MMC_INI_DELTA_REV_VAL_MASK)
#define MMC_INI_DELTA_REV_VAL_GET(x) (((uint32_t)(x) & MMC_INI_DELTA_REV_VAL_MASK) >> MMC_INI_DELTA_REV_VAL_SHIFT)

/* Bitfield definition for register: INI_DELTA_SPEED */
/*
 * VAL (RW)
 *
 * the value；
 * continuous mode: fix<32, 19>
 */
#define MMC_INI_DELTA_SPEED_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_DELTA_SPEED_VAL_SHIFT (0U)
#define MMC_INI_DELTA_SPEED_VAL_SET(x) (((uint32_t)(x) << MMC_INI_DELTA_SPEED_VAL_SHIFT) & MMC_INI_DELTA_SPEED_VAL_MASK)
#define MMC_INI_DELTA_SPEED_VAL_GET(x) (((uint32_t)(x) & MMC_INI_DELTA_SPEED_VAL_MASK) >> MMC_INI_DELTA_SPEED_VAL_SHIFT)

/* Bitfield definition for register: INI_DELTA_ACCEL */
/*
 * VAL (RW)
 *
 * the value
 * continuous mode: fix<32, 19>
 */
#define MMC_INI_DELTA_ACCEL_VAL_MASK (0xFFFFFFFFUL)
#define MMC_INI_DELTA_ACCEL_VAL_SHIFT (0U)
#define MMC_INI_DELTA_ACCEL_VAL_SET(x) (((uint32_t)(x) << MMC_INI_DELTA_ACCEL_VAL_SHIFT) & MMC_INI_DELTA_ACCEL_VAL_MASK)
#define MMC_INI_DELTA_ACCEL_VAL_GET(x) (((uint32_t)(x) & MMC_INI_DELTA_ACCEL_VAL_MASK) >> MMC_INI_DELTA_ACCEL_VAL_SHIFT)

/* Bitfield definition for register: POS_TRG_CFG */
/*
 * EDGE (RW)
 *
 * 0: (rising edge) pos inc greater than, 1: (falling edge)  pos dec less than
 */
#define MMC_POS_TRG_CFG_EDGE_MASK (0x2U)
#define MMC_POS_TRG_CFG_EDGE_SHIFT (1U)
#define MMC_POS_TRG_CFG_EDGE_SET(x) (((uint32_t)(x) << MMC_POS_TRG_CFG_EDGE_SHIFT) & MMC_POS_TRG_CFG_EDGE_MASK)
#define MMC_POS_TRG_CFG_EDGE_GET(x) (((uint32_t)(x) & MMC_POS_TRG_CFG_EDGE_MASK) >> MMC_POS_TRG_CFG_EDGE_SHIFT)

/*
 * EN (RW)
 *
 * 1-trigger valid; 0-Trigger not valid"
 */
#define MMC_POS_TRG_CFG_EN_MASK (0x1U)
#define MMC_POS_TRG_CFG_EN_SHIFT (0U)
#define MMC_POS_TRG_CFG_EN_SET(x) (((uint32_t)(x) << MMC_POS_TRG_CFG_EN_SHIFT) & MMC_POS_TRG_CFG_EN_MASK)
#define MMC_POS_TRG_CFG_EN_GET(x) (((uint32_t)(x) & MMC_POS_TRG_CFG_EN_MASK) >> MMC_POS_TRG_CFG_EN_SHIFT)

/* Bitfield definition for register: POS_TRG_POS_THR */
/*
 * VAL (RW)
 *
 * For pos out trigger (pos).
 * ufix<32, 32>
 */
#define MMC_POS_TRG_POS_THR_VAL_MASK (0xFFFFFFFFUL)
#define MMC_POS_TRG_POS_THR_VAL_SHIFT (0U)
#define MMC_POS_TRG_POS_THR_VAL_SET(x) (((uint32_t)(x) << MMC_POS_TRG_POS_THR_VAL_SHIFT) & MMC_POS_TRG_POS_THR_VAL_MASK)
#define MMC_POS_TRG_POS_THR_VAL_GET(x) (((uint32_t)(x) & MMC_POS_TRG_POS_THR_VAL_MASK) >> MMC_POS_TRG_POS_THR_VAL_SHIFT)

/* Bitfield definition for register: POS_TRG_REV_THR */
/*
 * VAL (RW)
 *
 * For pos out trigger (rev)
 * fix<32, 0>
 */
#define MMC_POS_TRG_REV_THR_VAL_MASK (0xFFFFFFFFUL)
#define MMC_POS_TRG_REV_THR_VAL_SHIFT (0U)
#define MMC_POS_TRG_REV_THR_VAL_SET(x) (((uint32_t)(x) << MMC_POS_TRG_REV_THR_VAL_SHIFT) & MMC_POS_TRG_REV_THR_VAL_MASK)
#define MMC_POS_TRG_REV_THR_VAL_GET(x) (((uint32_t)(x) & MMC_POS_TRG_REV_THR_VAL_MASK) >> MMC_POS_TRG_REV_THR_VAL_SHIFT)

/* Bitfield definition for register: SPEED_TRG_CFG */
/*
 * COMP_TYPE (RW)
 *
 * 1: Use abs value for comparion. 0: Use the speed with direction info (so not the abs value)
 */
#define MMC_SPEED_TRG_CFG_COMP_TYPE_MASK (0x4U)
#define MMC_SPEED_TRG_CFG_COMP_TYPE_SHIFT (2U)
#define MMC_SPEED_TRG_CFG_COMP_TYPE_SET(x) (((uint32_t)(x) << MMC_SPEED_TRG_CFG_COMP_TYPE_SHIFT) & MMC_SPEED_TRG_CFG_COMP_TYPE_MASK)
#define MMC_SPEED_TRG_CFG_COMP_TYPE_GET(x) (((uint32_t)(x) & MMC_SPEED_TRG_CFG_COMP_TYPE_MASK) >> MMC_SPEED_TRG_CFG_COMP_TYPE_SHIFT)

/*
 * EDGE (RW)
 *
 * 0: (rising edge) speed inc greater than, 1: (falling edge)  speed dec less than
 */
#define MMC_SPEED_TRG_CFG_EDGE_MASK (0x2U)
#define MMC_SPEED_TRG_CFG_EDGE_SHIFT (1U)
#define MMC_SPEED_TRG_CFG_EDGE_SET(x) (((uint32_t)(x) << MMC_SPEED_TRG_CFG_EDGE_SHIFT) & MMC_SPEED_TRG_CFG_EDGE_MASK)
#define MMC_SPEED_TRG_CFG_EDGE_GET(x) (((uint32_t)(x) & MMC_SPEED_TRG_CFG_EDGE_MASK) >> MMC_SPEED_TRG_CFG_EDGE_SHIFT)

/*
 * EN (RW)
 *
 * 1-trigger valid; 0-Trigger not valid
 * Normally it means either the max pos speed, or the min negative speed.
 */
#define MMC_SPEED_TRG_CFG_EN_MASK (0x1U)
#define MMC_SPEED_TRG_CFG_EN_SHIFT (0U)
#define MMC_SPEED_TRG_CFG_EN_SET(x) (((uint32_t)(x) << MMC_SPEED_TRG_CFG_EN_SHIFT) & MMC_SPEED_TRG_CFG_EN_MASK)
#define MMC_SPEED_TRG_CFG_EN_GET(x) (((uint32_t)(x) & MMC_SPEED_TRG_CFG_EN_MASK) >> MMC_SPEED_TRG_CFG_EN_SHIFT)

/* Bitfield definition for register: SPEED_TRG_THR */
/*
 * VAL (RW)
 *
 * For speed trigger.
 * continuous mode: fix<32, 19>
 */
#define MMC_SPEED_TRG_THR_VAL_MASK (0xFFFFFFFFUL)
#define MMC_SPEED_TRG_THR_VAL_SHIFT (0U)
#define MMC_SPEED_TRG_THR_VAL_SET(x) (((uint32_t)(x) << MMC_SPEED_TRG_THR_VAL_SHIFT) & MMC_SPEED_TRG_THR_VAL_MASK)
#define MMC_SPEED_TRG_THR_VAL_GET(x) (((uint32_t)(x) & MMC_SPEED_TRG_THR_VAL_MASK) >> MMC_SPEED_TRG_THR_VAL_SHIFT)

/* Bitfield definition for register of struct array COEF_TRG_CFG: ERR_THR */
/*
 * VAL (RW)
 *
 * ErrThr0: Error Threshold 0, (abs(tracking error)>= will choose the coefs as below)
 * Note: ErrThr0>ErrThr1>ErrThr2
 * ufix<31, 28>
 */
#define MMC_COEF_TRG_CFG_ERR_THR_VAL_MASK (0xFFFFFFFFUL)
#define MMC_COEF_TRG_CFG_ERR_THR_VAL_SHIFT (0U)
#define MMC_COEF_TRG_CFG_ERR_THR_VAL_SET(x) (((uint32_t)(x) << MMC_COEF_TRG_CFG_ERR_THR_VAL_SHIFT) & MMC_COEF_TRG_CFG_ERR_THR_VAL_MASK)
#define MMC_COEF_TRG_CFG_ERR_THR_VAL_GET(x) (((uint32_t)(x) & MMC_COEF_TRG_CFG_ERR_THR_VAL_MASK) >> MMC_COEF_TRG_CFG_ERR_THR_VAL_SHIFT)

/* Bitfield definition for register of struct array COEF_TRG_CFG: P */
/*
 * VAL (RW)
 *
 * P0_Coef, fix<32, 15>
 */
#define MMC_COEF_TRG_CFG_P_VAL_MASK (0xFFFFFFFFUL)
#define MMC_COEF_TRG_CFG_P_VAL_SHIFT (0U)
#define MMC_COEF_TRG_CFG_P_VAL_SET(x) (((uint32_t)(x) << MMC_COEF_TRG_CFG_P_VAL_SHIFT) & MMC_COEF_TRG_CFG_P_VAL_MASK)
#define MMC_COEF_TRG_CFG_P_VAL_GET(x) (((uint32_t)(x) & MMC_COEF_TRG_CFG_P_VAL_MASK) >> MMC_COEF_TRG_CFG_P_VAL_SHIFT)

/* Bitfield definition for register of struct array COEF_TRG_CFG: I */
/*
 * VAL (RW)
 *
 * I0_Coef, fix<32, 21>
 */
#define MMC_COEF_TRG_CFG_I_VAL_MASK (0xFFFFFFFFUL)
#define MMC_COEF_TRG_CFG_I_VAL_SHIFT (0U)
#define MMC_COEF_TRG_CFG_I_VAL_SET(x) (((uint32_t)(x) << MMC_COEF_TRG_CFG_I_VAL_SHIFT) & MMC_COEF_TRG_CFG_I_VAL_MASK)
#define MMC_COEF_TRG_CFG_I_VAL_GET(x) (((uint32_t)(x) & MMC_COEF_TRG_CFG_I_VAL_MASK) >> MMC_COEF_TRG_CFG_I_VAL_SHIFT)

/* Bitfield definition for register of struct array COEF_TRG_CFG: A */
/*
 * VAL (RW)
 *
 * A0_Coef，fix<32, 19>
 */
#define MMC_COEF_TRG_CFG_A_VAL_MASK (0xFFFFFFFFUL)
#define MMC_COEF_TRG_CFG_A_VAL_SHIFT (0U)
#define MMC_COEF_TRG_CFG_A_VAL_SET(x) (((uint32_t)(x) << MMC_COEF_TRG_CFG_A_VAL_SHIFT) & MMC_COEF_TRG_CFG_A_VAL_MASK)
#define MMC_COEF_TRG_CFG_A_VAL_GET(x) (((uint32_t)(x) & MMC_COEF_TRG_CFG_A_VAL_MASK) >> MMC_COEF_TRG_CFG_A_VAL_SHIFT)

/* Bitfield definition for register of struct array COEF_TRG_CFG: TIME */
/*
 * VAL (RW)
 *
 * CoefTime0: Time Stayed using this coefs (counted in input samples). Ideal value of tracing cycles should +1. ufix<32,0>
 */
#define MMC_COEF_TRG_CFG_TIME_VAL_MASK (0xFFFFFFFFUL)
#define MMC_COEF_TRG_CFG_TIME_VAL_SHIFT (0U)
#define MMC_COEF_TRG_CFG_TIME_VAL_SET(x) (((uint32_t)(x) << MMC_COEF_TRG_CFG_TIME_VAL_SHIFT) & MMC_COEF_TRG_CFG_TIME_VAL_MASK)
#define MMC_COEF_TRG_CFG_TIME_VAL_GET(x) (((uint32_t)(x) & MMC_COEF_TRG_CFG_TIME_VAL_MASK) >> MMC_COEF_TRG_CFG_TIME_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_CTRL */
/*
 * SPEED_TRG_VALID_IE (RW)
 *
 * Interrupt Enable for SPEED_TRG_VALID
 */
#define MMC_BR_BR_CTRL_SPEED_TRG_VALID_IE_MASK (0x40000000UL)
#define MMC_BR_BR_CTRL_SPEED_TRG_VALID_IE_SHIFT (30U)
#define MMC_BR_BR_CTRL_SPEED_TRG_VALID_IE_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_SPEED_TRG_VALID_IE_SHIFT) & MMC_BR_BR_CTRL_SPEED_TRG_VALID_IE_MASK)
#define MMC_BR_BR_CTRL_SPEED_TRG_VALID_IE_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_SPEED_TRG_VALID_IE_MASK) >> MMC_BR_BR_CTRL_SPEED_TRG_VALID_IE_SHIFT)

/*
 * POS_TRG_VALID_IE (RW)
 *
 * Interrupt Enable for POS_TRG_VALID
 */
#define MMC_BR_BR_CTRL_POS_TRG_VALID_IE_MASK (0x20000000UL)
#define MMC_BR_BR_CTRL_POS_TRG_VALID_IE_SHIFT (29U)
#define MMC_BR_BR_CTRL_POS_TRG_VALID_IE_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_POS_TRG_VALID_IE_SHIFT) & MMC_BR_BR_CTRL_POS_TRG_VALID_IE_MASK)
#define MMC_BR_BR_CTRL_POS_TRG_VALID_IE_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_POS_TRG_VALID_IE_MASK) >> MMC_BR_BR_CTRL_POS_TRG_VALID_IE_SHIFT)

/*
 * INI_POS_TRG_TYPE (RW)
 *
 * 0: Time Stamp in the configuration
 * 1: Risedge of In Trg[0]
 * 2: Risedge of In Trg[1]
 * 3: Risedge of out trg[0]
 * 4: Risedge of out trg[1]
 * 5: Risedge of self pos trigger
 * 6: Risedge of self speed trigger
 * Others: no function
 */
#define MMC_BR_BR_CTRL_INI_POS_TRG_TYPE_MASK (0x3800000UL)
#define MMC_BR_BR_CTRL_INI_POS_TRG_TYPE_SHIFT (23U)
#define MMC_BR_BR_CTRL_INI_POS_TRG_TYPE_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_INI_POS_TRG_TYPE_SHIFT) & MMC_BR_BR_CTRL_INI_POS_TRG_TYPE_MASK)
#define MMC_BR_BR_CTRL_INI_POS_TRG_TYPE_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_INI_POS_TRG_TYPE_MASK) >> MMC_BR_BR_CTRL_INI_POS_TRG_TYPE_SHIFT)

/*
 * INI_POS_CMD_MSK (RW)
 *
 * 1: change
 * 0: won't change
 * bit 3: for accel
 * bit 2: for speed
 * bit 1: for revolution
 * bit 0: for position
 */
#define MMC_BR_BR_CTRL_INI_POS_CMD_MSK_MASK (0x3C0000UL)
#define MMC_BR_BR_CTRL_INI_POS_CMD_MSK_SHIFT (18U)
#define MMC_BR_BR_CTRL_INI_POS_CMD_MSK_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_INI_POS_CMD_MSK_SHIFT) & MMC_BR_BR_CTRL_INI_POS_CMD_MSK_MASK)
#define MMC_BR_BR_CTRL_INI_POS_CMD_MSK_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_INI_POS_CMD_MSK_MASK) >> MMC_BR_BR_CTRL_INI_POS_CMD_MSK_SHIFT)

/*
 * INI_DELTA_POS_TRG_TYPE (RW)
 *
 * 0: Time Stamp in the configuration
 * 1: Risedge of In Trg[0]
 * 2: Risedge of In Trg[1]
 * 3: Risedge of out trg[0]
 * 4: Risedge of out trg[1]
 * 5: Risedge of self pos trigger
 * 6: Risedge of self speed trigger
 * Others: no function
 */
#define MMC_BR_BR_CTRL_INI_DELTA_POS_TRG_TYPE_MASK (0x1C000UL)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_TRG_TYPE_SHIFT (14U)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_TRG_TYPE_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_INI_DELTA_POS_TRG_TYPE_SHIFT) & MMC_BR_BR_CTRL_INI_DELTA_POS_TRG_TYPE_MASK)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_TRG_TYPE_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_INI_DELTA_POS_TRG_TYPE_MASK) >> MMC_BR_BR_CTRL_INI_DELTA_POS_TRG_TYPE_SHIFT)

/*
 * INI_DELTA_POS_DONE_IE (RW)
 *
 * Interrupt Enable for INI_DELTA_POS_DONE
 */
#define MMC_BR_BR_CTRL_INI_DELTA_POS_DONE_IE_MASK (0x2000U)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_DONE_IE_SHIFT (13U)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_DONE_IE_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_INI_DELTA_POS_DONE_IE_SHIFT) & MMC_BR_BR_CTRL_INI_DELTA_POS_DONE_IE_MASK)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_DONE_IE_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_INI_DELTA_POS_DONE_IE_MASK) >> MMC_BR_BR_CTRL_INI_DELTA_POS_DONE_IE_SHIFT)

/*
 * INI_DELTA_POS_CMD_MSK (RW)
 *
 * 1: change
 * 0: won't change
 * bit 3: for delta accel
 * bit 2: for delta speed
 * bit 1: for delta revolution
 * bit 0: for delta position
 */
#define MMC_BR_BR_CTRL_INI_DELTA_POS_CMD_MSK_MASK (0x1E00U)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_CMD_MSK_SHIFT (9U)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_CMD_MSK_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_INI_DELTA_POS_CMD_MSK_SHIFT) & MMC_BR_BR_CTRL_INI_DELTA_POS_CMD_MSK_MASK)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_CMD_MSK_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_INI_DELTA_POS_CMD_MSK_MASK) >> MMC_BR_BR_CTRL_INI_DELTA_POS_CMD_MSK_SHIFT)

/*
 * INI_DELTA_POS_REQ (RW)
 *
 * 1: Command to reload the delta pos. Auto clear
 * 0:
 */
#define MMC_BR_BR_CTRL_INI_DELTA_POS_REQ_MASK (0x100U)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_REQ_SHIFT (8U)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_REQ_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_INI_DELTA_POS_REQ_SHIFT) & MMC_BR_BR_CTRL_INI_DELTA_POS_REQ_MASK)
#define MMC_BR_BR_CTRL_INI_DELTA_POS_REQ_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_INI_DELTA_POS_REQ_MASK) >> MMC_BR_BR_CTRL_INI_DELTA_POS_REQ_SHIFT)

/*
 * OPEN_LOOP_MODE (RW)
 *
 * 1: in open loop mode
 * 0: not in open loop mode
 */
#define MMC_BR_BR_CTRL_OPEN_LOOP_MODE_MASK (0x80U)
#define MMC_BR_BR_CTRL_OPEN_LOOP_MODE_SHIFT (7U)
#define MMC_BR_BR_CTRL_OPEN_LOOP_MODE_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_OPEN_LOOP_MODE_SHIFT) & MMC_BR_BR_CTRL_OPEN_LOOP_MODE_MASK)
#define MMC_BR_BR_CTRL_OPEN_LOOP_MODE_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_OPEN_LOOP_MODE_MASK) >> MMC_BR_BR_CTRL_OPEN_LOOP_MODE_SHIFT)

/*
 * PRED_MODE (RW)
 *
 * 1:continuously repeat pred,
 * 0:cal the pred based on a definite time-stamp offset,
 * 2:programed one-shot prediction mode
 */
#define MMC_BR_BR_CTRL_PRED_MODE_MASK (0x30U)
#define MMC_BR_BR_CTRL_PRED_MODE_SHIFT (4U)
#define MMC_BR_BR_CTRL_PRED_MODE_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_PRED_MODE_SHIFT) & MMC_BR_BR_CTRL_PRED_MODE_MASK)
#define MMC_BR_BR_CTRL_PRED_MODE_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_PRED_MODE_MASK) >> MMC_BR_BR_CTRL_PRED_MODE_SHIFT)

/*
 * NF_TRG_TYPE (RW)
 *
 * 1. Each non-first trigger by external trigger pin
 * 0. Each non-first trigger by the timer
 */
#define MMC_BR_BR_CTRL_NF_TRG_TYPE_MASK (0x4U)
#define MMC_BR_BR_CTRL_NF_TRG_TYPE_SHIFT (2U)
#define MMC_BR_BR_CTRL_NF_TRG_TYPE_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_NF_TRG_TYPE_SHIFT) & MMC_BR_BR_CTRL_NF_TRG_TYPE_MASK)
#define MMC_BR_BR_CTRL_NF_TRG_TYPE_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_NF_TRG_TYPE_MASK) >> MMC_BR_BR_CTRL_NF_TRG_TYPE_SHIFT)

/*
 * F_TRG_TYPE (RW)
 *
 * 1. First trigger by external trigger pin
 * 0. First trigger by the timer
 * When in CR[MANUAL_IO]=1 mode, it is the prediction trigger
 */
#define MMC_BR_BR_CTRL_F_TRG_TYPE_MASK (0x2U)
#define MMC_BR_BR_CTRL_F_TRG_TYPE_SHIFT (1U)
#define MMC_BR_BR_CTRL_F_TRG_TYPE_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_F_TRG_TYPE_SHIFT) & MMC_BR_BR_CTRL_F_TRG_TYPE_MASK)
#define MMC_BR_BR_CTRL_F_TRG_TYPE_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_F_TRG_TYPE_MASK) >> MMC_BR_BR_CTRL_F_TRG_TYPE_SHIFT)

/*
 * BR_EN (RW)
 *
 * Branch Enable
 */
#define MMC_BR_BR_CTRL_BR_EN_MASK (0x1U)
#define MMC_BR_BR_CTRL_BR_EN_SHIFT (0U)
#define MMC_BR_BR_CTRL_BR_EN_SET(x) (((uint32_t)(x) << MMC_BR_BR_CTRL_BR_EN_SHIFT) & MMC_BR_BR_CTRL_BR_EN_MASK)
#define MMC_BR_BR_CTRL_BR_EN_GET(x) (((uint32_t)(x) & MMC_BR_BR_CTRL_BR_EN_MASK) >> MMC_BR_BR_CTRL_BR_EN_SHIFT)

/* Bitfield definition for register of struct array BR: BR_TIMEOFF */
/*
 * VAL (RW)
 *
 * ufix<32, 0> time offset incycles from the trigger time
 */
#define MMC_BR_BR_TIMEOFF_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_TIMEOFF_VAL_SHIFT (0U)
#define MMC_BR_BR_TIMEOFF_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_TIMEOFF_VAL_SHIFT) & MMC_BR_BR_TIMEOFF_VAL_MASK)
#define MMC_BR_BR_TIMEOFF_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_TIMEOFF_VAL_MASK) >> MMC_BR_BR_TIMEOFF_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_TRG_PERIOD */
/*
 * VAL (RW)
 *
 * uifx<32, 0>, time offset incycles between each trigger time
 */
#define MMC_BR_BR_TRG_PERIOD_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_TRG_PERIOD_VAL_SHIFT (0U)
#define MMC_BR_BR_TRG_PERIOD_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_TRG_PERIOD_VAL_SHIFT) & MMC_BR_BR_TRG_PERIOD_VAL_MASK)
#define MMC_BR_BR_TRG_PERIOD_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_TRG_PERIOD_VAL_MASK) >> MMC_BR_BR_TRG_PERIOD_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_TRG_F_TIME */
/*
 * VAL (RW)
 *
 * uifx<32, 0> the time for the first trigger
 */
#define MMC_BR_BR_TRG_F_TIME_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_TRG_F_TIME_VAL_SHIFT (0U)
#define MMC_BR_BR_TRG_F_TIME_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_TRG_F_TIME_VAL_SHIFT) & MMC_BR_BR_TRG_F_TIME_VAL_MASK)
#define MMC_BR_BR_TRG_F_TIME_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_TRG_F_TIME_VAL_MASK) >> MMC_BR_BR_TRG_F_TIME_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_ST */
/*
 * OPEN_LOOP_ST (RO)
 *
 * 1：in open loop mode
 * 0：in closed loop mode
 */
#define MMC_BR_BR_ST_OPEN_LOOP_ST_MASK (0x400U)
#define MMC_BR_BR_ST_OPEN_LOOP_ST_SHIFT (10U)
#define MMC_BR_BR_ST_OPEN_LOOP_ST_GET(x) (((uint32_t)(x) & MMC_BR_BR_ST_OPEN_LOOP_ST_MASK) >> MMC_BR_BR_ST_OPEN_LOOP_ST_SHIFT)

/*
 * SPEED_TRG_VLD (W1C)
 *
 * 1：self speed trigger event found
 * 0：self speed trigger event not found yet
 */
#define MMC_BR_BR_ST_SPEED_TRG_VLD_MASK (0x200U)
#define MMC_BR_BR_ST_SPEED_TRG_VLD_SHIFT (9U)
#define MMC_BR_BR_ST_SPEED_TRG_VLD_SET(x) (((uint32_t)(x) << MMC_BR_BR_ST_SPEED_TRG_VLD_SHIFT) & MMC_BR_BR_ST_SPEED_TRG_VLD_MASK)
#define MMC_BR_BR_ST_SPEED_TRG_VLD_GET(x) (((uint32_t)(x) & MMC_BR_BR_ST_SPEED_TRG_VLD_MASK) >> MMC_BR_BR_ST_SPEED_TRG_VLD_SHIFT)

/*
 * POS_TRG_VLD (W1C)
 *
 * 1：self position trigger event found
 * 0：self position trigger event not found yet
 */
#define MMC_BR_BR_ST_POS_TRG_VLD_MASK (0x100U)
#define MMC_BR_BR_ST_POS_TRG_VLD_SHIFT (8U)
#define MMC_BR_BR_ST_POS_TRG_VLD_SET(x) (((uint32_t)(x) << MMC_BR_BR_ST_POS_TRG_VLD_SHIFT) & MMC_BR_BR_ST_POS_TRG_VLD_MASK)
#define MMC_BR_BR_ST_POS_TRG_VLD_GET(x) (((uint32_t)(x) & MMC_BR_BR_ST_POS_TRG_VLD_MASK) >> MMC_BR_BR_ST_POS_TRG_VLD_SHIFT)

/*
 * INI_DELTA_POS_DONE (W1C)
 *
 * 1: the initialization of delta position command is done
 * 0: the initialization of delta position command is not done
 */
#define MMC_BR_BR_ST_INI_DELTA_POS_DONE_MASK (0x40U)
#define MMC_BR_BR_ST_INI_DELTA_POS_DONE_SHIFT (6U)
#define MMC_BR_BR_ST_INI_DELTA_POS_DONE_SET(x) (((uint32_t)(x) << MMC_BR_BR_ST_INI_DELTA_POS_DONE_SHIFT) & MMC_BR_BR_ST_INI_DELTA_POS_DONE_MASK)
#define MMC_BR_BR_ST_INI_DELTA_POS_DONE_GET(x) (((uint32_t)(x) & MMC_BR_BR_ST_INI_DELTA_POS_DONE_MASK) >> MMC_BR_BR_ST_INI_DELTA_POS_DONE_SHIFT)

/*
 * IDLE (RO)
 *
 * 1: The prediction module is idle.
 * 0: The prediction module is not idle.
 */
#define MMC_BR_BR_ST_IDLE_MASK (0x20U)
#define MMC_BR_BR_ST_IDLE_SHIFT (5U)
#define MMC_BR_BR_ST_IDLE_GET(x) (((uint32_t)(x) & MMC_BR_BR_ST_IDLE_MASK) >> MMC_BR_BR_ST_IDLE_SHIFT)

/*
 * ERR_ID (RO)
 *
 * The module's error ID output
 */
#define MMC_BR_BR_ST_ERR_ID_MASK (0xFU)
#define MMC_BR_BR_ST_ERR_ID_SHIFT (0U)
#define MMC_BR_BR_ST_ERR_ID_GET(x) (((uint32_t)(x) & MMC_BR_BR_ST_ERR_ID_MASK) >> MMC_BR_BR_ST_ERR_ID_SHIFT)

/* Bitfield definition for register of struct array BR: BR_TRG_POS_CFG */
/*
 * EDGE (RW)
 *
 * bit1: 0: (rising edge) pos inc greater than, 1: (falling edge)  pos dec less than
 */
#define MMC_BR_BR_TRG_POS_CFG_EDGE_MASK (0x2U)
#define MMC_BR_BR_TRG_POS_CFG_EDGE_SHIFT (1U)
#define MMC_BR_BR_TRG_POS_CFG_EDGE_SET(x) (((uint32_t)(x) << MMC_BR_BR_TRG_POS_CFG_EDGE_SHIFT) & MMC_BR_BR_TRG_POS_CFG_EDGE_MASK)
#define MMC_BR_BR_TRG_POS_CFG_EDGE_GET(x) (((uint32_t)(x) & MMC_BR_BR_TRG_POS_CFG_EDGE_MASK) >> MMC_BR_BR_TRG_POS_CFG_EDGE_SHIFT)

/*
 * EN (RW)
 *
 * 1-trigger valid; 0-Trigger not valid
 */
#define MMC_BR_BR_TRG_POS_CFG_EN_MASK (0x1U)
#define MMC_BR_BR_TRG_POS_CFG_EN_SHIFT (0U)
#define MMC_BR_BR_TRG_POS_CFG_EN_SET(x) (((uint32_t)(x) << MMC_BR_BR_TRG_POS_CFG_EN_SHIFT) & MMC_BR_BR_TRG_POS_CFG_EN_MASK)
#define MMC_BR_BR_TRG_POS_CFG_EN_GET(x) (((uint32_t)(x) & MMC_BR_BR_TRG_POS_CFG_EN_MASK) >> MMC_BR_BR_TRG_POS_CFG_EN_SHIFT)

/* Bitfield definition for register of struct array BR: BR_TRG_POS_THR */
/*
 * VAL (RW)
 *
 * For pos out trigger (pos).
 * ufix<32, 32>
 */
#define MMC_BR_BR_TRG_POS_THR_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_TRG_POS_THR_VAL_SHIFT (0U)
#define MMC_BR_BR_TRG_POS_THR_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_TRG_POS_THR_VAL_SHIFT) & MMC_BR_BR_TRG_POS_THR_VAL_MASK)
#define MMC_BR_BR_TRG_POS_THR_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_TRG_POS_THR_VAL_MASK) >> MMC_BR_BR_TRG_POS_THR_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_TRG_REV_THR */
/*
 * VAL (RW)
 *
 * For pos out trigger (rev)
 * ufix<32, 0>
 */
#define MMC_BR_BR_TRG_REV_THR_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_TRG_REV_THR_VAL_SHIFT (0U)
#define MMC_BR_BR_TRG_REV_THR_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_TRG_REV_THR_VAL_SHIFT) & MMC_BR_BR_TRG_REV_THR_VAL_MASK)
#define MMC_BR_BR_TRG_REV_THR_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_TRG_REV_THR_VAL_MASK) >> MMC_BR_BR_TRG_REV_THR_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_TRG_SPEED_CFG */
/*
 * COMP_TYPE (RW)
 *
 * Use abs value for comparion. 0: Use the speed with direction info (so not the abs value)
 */
#define MMC_BR_BR_TRG_SPEED_CFG_COMP_TYPE_MASK (0x4U)
#define MMC_BR_BR_TRG_SPEED_CFG_COMP_TYPE_SHIFT (2U)
#define MMC_BR_BR_TRG_SPEED_CFG_COMP_TYPE_SET(x) (((uint32_t)(x) << MMC_BR_BR_TRG_SPEED_CFG_COMP_TYPE_SHIFT) & MMC_BR_BR_TRG_SPEED_CFG_COMP_TYPE_MASK)
#define MMC_BR_BR_TRG_SPEED_CFG_COMP_TYPE_GET(x) (((uint32_t)(x) & MMC_BR_BR_TRG_SPEED_CFG_COMP_TYPE_MASK) >> MMC_BR_BR_TRG_SPEED_CFG_COMP_TYPE_SHIFT)

/*
 * EDGE_SEL (RW)
 *
 * 0: (rising edge) speed inc greater than, 1: (falling edge)  speed dec less than
 */
#define MMC_BR_BR_TRG_SPEED_CFG_EDGE_SEL_MASK (0x2U)
#define MMC_BR_BR_TRG_SPEED_CFG_EDGE_SEL_SHIFT (1U)
#define MMC_BR_BR_TRG_SPEED_CFG_EDGE_SEL_SET(x) (((uint32_t)(x) << MMC_BR_BR_TRG_SPEED_CFG_EDGE_SEL_SHIFT) & MMC_BR_BR_TRG_SPEED_CFG_EDGE_SEL_MASK)
#define MMC_BR_BR_TRG_SPEED_CFG_EDGE_SEL_GET(x) (((uint32_t)(x) & MMC_BR_BR_TRG_SPEED_CFG_EDGE_SEL_MASK) >> MMC_BR_BR_TRG_SPEED_CFG_EDGE_SEL_SHIFT)

/*
 * EN (RW)
 *
 * 1-trigger valid; 0-Trigger not valid
 * Normally it means either the max pos speed, or the min negative speed.
 */
#define MMC_BR_BR_TRG_SPEED_CFG_EN_MASK (0x1U)
#define MMC_BR_BR_TRG_SPEED_CFG_EN_SHIFT (0U)
#define MMC_BR_BR_TRG_SPEED_CFG_EN_SET(x) (((uint32_t)(x) << MMC_BR_BR_TRG_SPEED_CFG_EN_SHIFT) & MMC_BR_BR_TRG_SPEED_CFG_EN_MASK)
#define MMC_BR_BR_TRG_SPEED_CFG_EN_GET(x) (((uint32_t)(x) & MMC_BR_BR_TRG_SPEED_CFG_EN_MASK) >> MMC_BR_BR_TRG_SPEED_CFG_EN_SHIFT)

/* Bitfield definition for register of struct array BR: BR_TRG_SPEED_THR */
/*
 * VAL (RW)
 *
 * For speed trigger.
 * continuous mode: fix<32, 19>
 */
#define MMC_BR_BR_TRG_SPEED_THR_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_TRG_SPEED_THR_VAL_SHIFT (0U)
#define MMC_BR_BR_TRG_SPEED_THR_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_TRG_SPEED_THR_VAL_SHIFT) & MMC_BR_BR_TRG_SPEED_THR_VAL_MASK)
#define MMC_BR_BR_TRG_SPEED_THR_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_TRG_SPEED_THR_VAL_MASK) >> MMC_BR_BR_TRG_SPEED_THR_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_INI_POS_TIME */
/*
 * VAL (RW)
 *
 * indicate the time to change the values.
 * 0: instant change
 */
#define MMC_BR_BR_INI_POS_TIME_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_INI_POS_TIME_VAL_SHIFT (0U)
#define MMC_BR_BR_INI_POS_TIME_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_INI_POS_TIME_VAL_SHIFT) & MMC_BR_BR_INI_POS_TIME_VAL_MASK)
#define MMC_BR_BR_INI_POS_TIME_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_INI_POS_TIME_VAL_MASK) >> MMC_BR_BR_INI_POS_TIME_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_INI_POS */
/*
 * VAL (RW)
 *
 * the value
 * ufix<32, 32>
 */
#define MMC_BR_BR_INI_POS_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_INI_POS_VAL_SHIFT (0U)
#define MMC_BR_BR_INI_POS_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_INI_POS_VAL_SHIFT) & MMC_BR_BR_INI_POS_VAL_MASK)
#define MMC_BR_BR_INI_POS_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_INI_POS_VAL_MASK) >> MMC_BR_BR_INI_POS_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_INI_REV */
/*
 * VAL (RW)
 *
 * the value
 * ufix<32, 0>
 */
#define MMC_BR_BR_INI_REV_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_INI_REV_VAL_SHIFT (0U)
#define MMC_BR_BR_INI_REV_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_INI_REV_VAL_SHIFT) & MMC_BR_BR_INI_REV_VAL_MASK)
#define MMC_BR_BR_INI_REV_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_INI_REV_VAL_MASK) >> MMC_BR_BR_INI_REV_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_INI_SPEED */
/*
 * VAL (RW)
 *
 * the value
 * fix<32, 19>
 */
#define MMC_BR_BR_INI_SPEED_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_INI_SPEED_VAL_SHIFT (0U)
#define MMC_BR_BR_INI_SPEED_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_INI_SPEED_VAL_SHIFT) & MMC_BR_BR_INI_SPEED_VAL_MASK)
#define MMC_BR_BR_INI_SPEED_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_INI_SPEED_VAL_MASK) >> MMC_BR_BR_INI_SPEED_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_INI_ACCEL */
/*
 * VAL (RW)
 *
 * the value
 * continuous mode: fix<32, 19>
 */
#define MMC_BR_BR_INI_ACCEL_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_INI_ACCEL_VAL_SHIFT (0U)
#define MMC_BR_BR_INI_ACCEL_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_INI_ACCEL_VAL_SHIFT) & MMC_BR_BR_INI_ACCEL_VAL_MASK)
#define MMC_BR_BR_INI_ACCEL_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_INI_ACCEL_VAL_MASK) >> MMC_BR_BR_INI_ACCEL_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_INI_DELTA_POS_TIME */
/*
 * VAL (RW)
 *
 * indicate the time to change the values.
 * 0: instant change
 */
#define MMC_BR_BR_INI_DELTA_POS_TIME_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_INI_DELTA_POS_TIME_VAL_SHIFT (0U)
#define MMC_BR_BR_INI_DELTA_POS_TIME_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_INI_DELTA_POS_TIME_VAL_SHIFT) & MMC_BR_BR_INI_DELTA_POS_TIME_VAL_MASK)
#define MMC_BR_BR_INI_DELTA_POS_TIME_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_INI_DELTA_POS_TIME_VAL_MASK) >> MMC_BR_BR_INI_DELTA_POS_TIME_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_INI_DELTA_POS */
/*
 * VAL (RW)
 *
 * the value
 * continuous mode: ufix<32, 32>
 */
#define MMC_BR_BR_INI_DELTA_POS_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_INI_DELTA_POS_VAL_SHIFT (0U)
#define MMC_BR_BR_INI_DELTA_POS_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_INI_DELTA_POS_VAL_SHIFT) & MMC_BR_BR_INI_DELTA_POS_VAL_MASK)
#define MMC_BR_BR_INI_DELTA_POS_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_INI_DELTA_POS_VAL_MASK) >> MMC_BR_BR_INI_DELTA_POS_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_INI_DELTA_REV */
/*
 * VAL (RW)
 *
 * the value
 * continuous mode: fix<32, 0>
 */
#define MMC_BR_BR_INI_DELTA_REV_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_INI_DELTA_REV_VAL_SHIFT (0U)
#define MMC_BR_BR_INI_DELTA_REV_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_INI_DELTA_REV_VAL_SHIFT) & MMC_BR_BR_INI_DELTA_REV_VAL_MASK)
#define MMC_BR_BR_INI_DELTA_REV_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_INI_DELTA_REV_VAL_MASK) >> MMC_BR_BR_INI_DELTA_REV_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_INI_DELTA_SPEED */
/*
 * VAL (RW)
 *
 * the value
 * continuous mode: fix<32, 19>
 */
#define MMC_BR_BR_INI_DELTA_SPEED_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_INI_DELTA_SPEED_VAL_SHIFT (0U)
#define MMC_BR_BR_INI_DELTA_SPEED_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_INI_DELTA_SPEED_VAL_SHIFT) & MMC_BR_BR_INI_DELTA_SPEED_VAL_MASK)
#define MMC_BR_BR_INI_DELTA_SPEED_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_INI_DELTA_SPEED_VAL_MASK) >> MMC_BR_BR_INI_DELTA_SPEED_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_INI_DELTA_ACCEL */
/*
 * VAL (RW)
 *
 * the value
 * continuous mode: fix<32, 19>
 */
#define MMC_BR_BR_INI_DELTA_ACCEL_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_INI_DELTA_ACCEL_VAL_SHIFT (0U)
#define MMC_BR_BR_INI_DELTA_ACCEL_VAL_SET(x) (((uint32_t)(x) << MMC_BR_BR_INI_DELTA_ACCEL_VAL_SHIFT) & MMC_BR_BR_INI_DELTA_ACCEL_VAL_MASK)
#define MMC_BR_BR_INI_DELTA_ACCEL_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_INI_DELTA_ACCEL_VAL_MASK) >> MMC_BR_BR_INI_DELTA_ACCEL_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_CUR_POS_TIME */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BR_BR_CUR_POS_TIME_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_CUR_POS_TIME_VAL_SHIFT (0U)
#define MMC_BR_BR_CUR_POS_TIME_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_CUR_POS_TIME_VAL_MASK) >> MMC_BR_BR_CUR_POS_TIME_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_CUR_POS */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BR_BR_CUR_POS_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_CUR_POS_VAL_SHIFT (0U)
#define MMC_BR_BR_CUR_POS_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_CUR_POS_VAL_MASK) >> MMC_BR_BR_CUR_POS_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_CUR_REV */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BR_BR_CUR_REV_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_CUR_REV_VAL_SHIFT (0U)
#define MMC_BR_BR_CUR_REV_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_CUR_REV_VAL_MASK) >> MMC_BR_BR_CUR_REV_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_CUR_SPEED */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BR_BR_CUR_SPEED_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_CUR_SPEED_VAL_SHIFT (0U)
#define MMC_BR_BR_CUR_SPEED_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_CUR_SPEED_VAL_MASK) >> MMC_BR_BR_CUR_SPEED_VAL_SHIFT)

/* Bitfield definition for register of struct array BR: BR_CUR_ACCEL */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BR_BR_CUR_ACCEL_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BR_BR_CUR_ACCEL_VAL_SHIFT (0U)
#define MMC_BR_BR_CUR_ACCEL_VAL_GET(x) (((uint32_t)(x) & MMC_BR_BR_CUR_ACCEL_VAL_MASK) >> MMC_BR_BR_CUR_ACCEL_VAL_SHIFT)

/* Bitfield definition for register: BK0_TIMESTAMP */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BK0_TIMESTAMP_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BK0_TIMESTAMP_VAL_SHIFT (0U)
#define MMC_BK0_TIMESTAMP_VAL_GET(x) (((uint32_t)(x) & MMC_BK0_TIMESTAMP_VAL_MASK) >> MMC_BK0_TIMESTAMP_VAL_SHIFT)

/* Bitfield definition for register: BK0_POSITION */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BK0_POSITION_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BK0_POSITION_VAL_SHIFT (0U)
#define MMC_BK0_POSITION_VAL_GET(x) (((uint32_t)(x) & MMC_BK0_POSITION_VAL_MASK) >> MMC_BK0_POSITION_VAL_SHIFT)

/* Bitfield definition for register: BK0_REVOLUTION */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BK0_REVOLUTION_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BK0_REVOLUTION_VAL_SHIFT (0U)
#define MMC_BK0_REVOLUTION_VAL_GET(x) (((uint32_t)(x) & MMC_BK0_REVOLUTION_VAL_MASK) >> MMC_BK0_REVOLUTION_VAL_SHIFT)

/* Bitfield definition for register: BK0_SPEED */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BK0_SPEED_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BK0_SPEED_VAL_SHIFT (0U)
#define MMC_BK0_SPEED_VAL_GET(x) (((uint32_t)(x) & MMC_BK0_SPEED_VAL_MASK) >> MMC_BK0_SPEED_VAL_SHIFT)

/* Bitfield definition for register: BK0_ACCELERATOR */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BK0_ACCELERATOR_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BK0_ACCELERATOR_VAL_SHIFT (0U)
#define MMC_BK0_ACCELERATOR_VAL_GET(x) (((uint32_t)(x) & MMC_BK0_ACCELERATOR_VAL_MASK) >> MMC_BK0_ACCELERATOR_VAL_SHIFT)

/* Bitfield definition for register: BK1_TIMESTAMP */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BK1_TIMESTAMP_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BK1_TIMESTAMP_VAL_SHIFT (0U)
#define MMC_BK1_TIMESTAMP_VAL_GET(x) (((uint32_t)(x) & MMC_BK1_TIMESTAMP_VAL_MASK) >> MMC_BK1_TIMESTAMP_VAL_SHIFT)

/* Bitfield definition for register: BK1_POSITION */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BK1_POSITION_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BK1_POSITION_VAL_SHIFT (0U)
#define MMC_BK1_POSITION_VAL_GET(x) (((uint32_t)(x) & MMC_BK1_POSITION_VAL_MASK) >> MMC_BK1_POSITION_VAL_SHIFT)

/* Bitfield definition for register: BK1_REVOLUTION */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BK1_REVOLUTION_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BK1_REVOLUTION_VAL_SHIFT (0U)
#define MMC_BK1_REVOLUTION_VAL_GET(x) (((uint32_t)(x) & MMC_BK1_REVOLUTION_VAL_MASK) >> MMC_BK1_REVOLUTION_VAL_SHIFT)

/* Bitfield definition for register: BK1_SPEED */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BK1_SPEED_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BK1_SPEED_VAL_SHIFT (0U)
#define MMC_BK1_SPEED_VAL_GET(x) (((uint32_t)(x) & MMC_BK1_SPEED_VAL_MASK) >> MMC_BK1_SPEED_VAL_SHIFT)

/* Bitfield definition for register: BK1_ACCELERATOR */
/*
 * VAL (RO)
 *
 * the value
 */
#define MMC_BK1_ACCELERATOR_VAL_MASK (0xFFFFFFFFUL)
#define MMC_BK1_ACCELERATOR_VAL_SHIFT (0U)
#define MMC_BK1_ACCELERATOR_VAL_GET(x) (((uint32_t)(x) & MMC_BK1_ACCELERATOR_VAL_MASK) >> MMC_BK1_ACCELERATOR_VAL_SHIFT)



/* COEF_TRG_CFG register group index macro definition */
#define MMC_COEF_TRG_CFG_0 (0UL)
#define MMC_COEF_TRG_CFG_1 (1UL)
#define MMC_COEF_TRG_CFG_2 (2UL)

/* BR register group index macro definition */
#define MMC_BR_0 (0UL)
#define MMC_BR_1 (1UL)


#endif /* HPM_MMC_H */
