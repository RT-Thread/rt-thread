/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_RNG_H
#define HPM_RNG_H

typedef struct {
    __RW uint32_t CMD;                         /* 0x0: Command Register */
    __RW uint32_t CTRL;                        /* 0x4: Control Register */
    __R  uint32_t STA;                         /* 0x8: Status Register */
    __R  uint32_t ERR;                         /* 0xC: Error Registers */
    __R  uint32_t FO2B;                        /* 0x10: FIFO out to bus/cpu */
    __R  uint8_t  RESERVED0[12];               /* 0x14 - 0x1F: Reserved */
    __R  uint32_t R2SK[8];                     /* 0x20 - 0x3C: FIFO out to SDP as AES engine key */
} RNG_Type;


/* Bitfield definition for register: CMD */
/*
 * SFTRST (RW)
 *
 * Soft Reset, Perform a software reset of the RNG This bit is self-clearing.
 * 0 Do not perform a software reset.
 * 1 Software reset
 */
#define RNG_CMD_SFTRST_MASK (0x40U)
#define RNG_CMD_SFTRST_SHIFT (6U)
#define RNG_CMD_SFTRST_SET(x) (((uint32_t)(x) << RNG_CMD_SFTRST_SHIFT) & RNG_CMD_SFTRST_MASK)
#define RNG_CMD_SFTRST_GET(x) (((uint32_t)(x) & RNG_CMD_SFTRST_MASK) >> RNG_CMD_SFTRST_SHIFT)

/*
 * CLRERR (RW)
 *
 * Clear the Error, clear the errors in the ESR register and the RNG interrupt. This bit is self-clearing.
 * 0 Do not clear the errors and the interrupt.
 * 1 Clear the errors and the interrupt.
 */
#define RNG_CMD_CLRERR_MASK (0x20U)
#define RNG_CMD_CLRERR_SHIFT (5U)
#define RNG_CMD_CLRERR_SET(x) (((uint32_t)(x) << RNG_CMD_CLRERR_SHIFT) & RNG_CMD_CLRERR_MASK)
#define RNG_CMD_CLRERR_GET(x) (((uint32_t)(x) & RNG_CMD_CLRERR_MASK) >> RNG_CMD_CLRERR_SHIFT)

/*
 * CLRINT (RW)
 *
 * Clear the Interrupt, clear the RNG interrupt if an error is not present. This bit is self-clearing.
 * 0 Do not clear the interrupt.
 * 1 Clear the interrupt
 */
#define RNG_CMD_CLRINT_MASK (0x10U)
#define RNG_CMD_CLRINT_SHIFT (4U)
#define RNG_CMD_CLRINT_SET(x) (((uint32_t)(x) << RNG_CMD_CLRINT_SHIFT) & RNG_CMD_CLRINT_MASK)
#define RNG_CMD_CLRINT_GET(x) (((uint32_t)(x) & RNG_CMD_CLRINT_MASK) >> RNG_CMD_CLRINT_SHIFT)

/*
 * GENSD (RW)
 *
 * Generate Seed, when both ST and GS triggered, ST first and GS next.
 */
#define RNG_CMD_GENSD_MASK (0x2U)
#define RNG_CMD_GENSD_SHIFT (1U)
#define RNG_CMD_GENSD_SET(x) (((uint32_t)(x) << RNG_CMD_GENSD_SHIFT) & RNG_CMD_GENSD_MASK)
#define RNG_CMD_GENSD_GET(x) (((uint32_t)(x) & RNG_CMD_GENSD_MASK) >> RNG_CMD_GENSD_SHIFT)

/*
 * SLFCHK (RW)
 *
 * Self Test, when both ST and GS triggered, ST first and GS next.
 */
#define RNG_CMD_SLFCHK_MASK (0x1U)
#define RNG_CMD_SLFCHK_SHIFT (0U)
#define RNG_CMD_SLFCHK_SET(x) (((uint32_t)(x) << RNG_CMD_SLFCHK_SHIFT) & RNG_CMD_SLFCHK_MASK)
#define RNG_CMD_SLFCHK_GET(x) (((uint32_t)(x) & RNG_CMD_SLFCHK_MASK) >> RNG_CMD_SLFCHK_SHIFT)

/* Bitfield definition for register: CTRL */
/*
 * MIRQERR (RW)
 *
 * Mask Interrupt Request for Error
 */
#define RNG_CTRL_MIRQERR_MASK (0x40U)
#define RNG_CTRL_MIRQERR_SHIFT (6U)
#define RNG_CTRL_MIRQERR_SET(x) (((uint32_t)(x) << RNG_CTRL_MIRQERR_SHIFT) & RNG_CTRL_MIRQERR_MASK)
#define RNG_CTRL_MIRQERR_GET(x) (((uint32_t)(x) & RNG_CTRL_MIRQERR_MASK) >> RNG_CTRL_MIRQERR_SHIFT)

/*
 * MIRQDN (RW)
 *
 * Mask Interrupt Request for Done Event, asks the interrupts generated upon the completion of the seed and self-test modes. The status of these jobs can be viewed by:
 * • Reading the STA and viewing the seed done and the self-test done bits (STA[SDN, STDN]).
 * • Viewing the RNG_CMD for the generate-seed or the self-test bits (CMD[GS,ST]) being set, indicating that the operation is still taking place.
 */
#define RNG_CTRL_MIRQDN_MASK (0x20U)
#define RNG_CTRL_MIRQDN_SHIFT (5U)
#define RNG_CTRL_MIRQDN_SET(x) (((uint32_t)(x) << RNG_CTRL_MIRQDN_SHIFT) & RNG_CTRL_MIRQDN_MASK)
#define RNG_CTRL_MIRQDN_GET(x) (((uint32_t)(x) & RNG_CTRL_MIRQDN_MASK) >> RNG_CTRL_MIRQDN_SHIFT)

/*
 * AUTRSD (RW)
 *
 * Auto Reseed
 */
#define RNG_CTRL_AUTRSD_MASK (0x10U)
#define RNG_CTRL_AUTRSD_SHIFT (4U)
#define RNG_CTRL_AUTRSD_SET(x) (((uint32_t)(x) << RNG_CTRL_AUTRSD_SHIFT) & RNG_CTRL_AUTRSD_MASK)
#define RNG_CTRL_AUTRSD_GET(x) (((uint32_t)(x) & RNG_CTRL_AUTRSD_MASK) >> RNG_CTRL_AUTRSD_SHIFT)

/*
 * FUFMOD (RW)
 *
 * FIFO underflow response mode
 * 00 Return all zeros and set the ESR[FUFE].
 * 01 Return all zeros and set the ESR[FUFE].
 * 10 Generate the bus transfer error
 * 11 Generate the interrupt and return all zeros (overrides the CTRL[MASKERR]).
 */
#define RNG_CTRL_FUFMOD_MASK (0x3U)
#define RNG_CTRL_FUFMOD_SHIFT (0U)
#define RNG_CTRL_FUFMOD_SET(x) (((uint32_t)(x) << RNG_CTRL_FUFMOD_SHIFT) & RNG_CTRL_FUFMOD_MASK)
#define RNG_CTRL_FUFMOD_GET(x) (((uint32_t)(x) & RNG_CTRL_FUFMOD_MASK) >> RNG_CTRL_FUFMOD_SHIFT)

/* Bitfield definition for register: STA */
/*
 * SCPF (RO)
 *
 * Self Check Pass Fail
 */
#define RNG_STA_SCPF_MASK (0xE00000UL)
#define RNG_STA_SCPF_SHIFT (21U)
#define RNG_STA_SCPF_GET(x) (((uint32_t)(x) & RNG_STA_SCPF_MASK) >> RNG_STA_SCPF_SHIFT)

/*
 * FUNCERR (RO)
 *
 * Error was detected, check ESR register for details
 */
#define RNG_STA_FUNCERR_MASK (0x10000UL)
#define RNG_STA_FUNCERR_SHIFT (16U)
#define RNG_STA_FUNCERR_GET(x) (((uint32_t)(x) & RNG_STA_FUNCERR_MASK) >> RNG_STA_FUNCERR_SHIFT)

/*
 * FSIZE (RO)
 *
 * Fifo Size, it is 5 in this design.
 */
#define RNG_STA_FSIZE_MASK (0xF000U)
#define RNG_STA_FSIZE_SHIFT (12U)
#define RNG_STA_FSIZE_GET(x) (((uint32_t)(x) & RNG_STA_FSIZE_MASK) >> RNG_STA_FSIZE_SHIFT)

/*
 * FRNNU (RO)
 *
 * Fifo Level, Indicates the number of random words currently in the output FIFO
 */
#define RNG_STA_FRNNU_MASK (0xF00U)
#define RNG_STA_FRNNU_SHIFT (8U)
#define RNG_STA_FRNNU_GET(x) (((uint32_t)(x) & RNG_STA_FRNNU_MASK) >> RNG_STA_FRNNU_SHIFT)

/*
 * NSDDN (RO)
 *
 * New seed done.
 */
#define RNG_STA_NSDDN_MASK (0x40U)
#define RNG_STA_NSDDN_SHIFT (6U)
#define RNG_STA_NSDDN_GET(x) (((uint32_t)(x) & RNG_STA_NSDDN_MASK) >> RNG_STA_NSDDN_SHIFT)

/*
 * FSDDN (RO)
 *
 * 1st Seed done
 * When "1", Indicates that the RNG generated the first seed.
 */
#define RNG_STA_FSDDN_MASK (0x20U)
#define RNG_STA_FSDDN_SHIFT (5U)
#define RNG_STA_FSDDN_GET(x) (((uint32_t)(x) & RNG_STA_FSDDN_MASK) >> RNG_STA_FSDDN_SHIFT)

/*
 * SCDN (RO)
 *
 * Self Check Done
 * Indicates whether Self Test is done or not. Can be cleared by the hardware reset or a new self test is
 * initiated by setting the CMD[ST].
 * 0 Self test not completed
 * 1 Completed a self test since the last reset.
 */
#define RNG_STA_SCDN_MASK (0x10U)
#define RNG_STA_SCDN_SHIFT (4U)
#define RNG_STA_SCDN_GET(x) (((uint32_t)(x) & RNG_STA_SCDN_MASK) >> RNG_STA_SCDN_SHIFT)

/*
 * RSDREQ (RO)
 *
 * Reseed needed
 * Indicates that the RNG needs to be reseeded. This is done by setting the CMD[GS], or
 * automatically if the CTRL[ARS] is set.
 */
#define RNG_STA_RSDREQ_MASK (0x8U)
#define RNG_STA_RSDREQ_SHIFT (3U)
#define RNG_STA_RSDREQ_GET(x) (((uint32_t)(x) & RNG_STA_RSDREQ_MASK) >> RNG_STA_RSDREQ_SHIFT)

/*
 * IDLE (RO)
 *
 * Idle, the RNG is in the idle mode, and internal clocks are disabled, in this mode, access to the FIFO is allowed. Once the FIFO is empty, the RNGB fills the FIFO and then enters idle mode again.
 */
#define RNG_STA_IDLE_MASK (0x4U)
#define RNG_STA_IDLE_SHIFT (2U)
#define RNG_STA_IDLE_GET(x) (((uint32_t)(x) & RNG_STA_IDLE_MASK) >> RNG_STA_IDLE_SHIFT)

/*
 * BUSY (RO)
 *
 * when 1, means the RNG engine is busy for seeding or random number generation, self test and so on.
 */
#define RNG_STA_BUSY_MASK (0x2U)
#define RNG_STA_BUSY_SHIFT (1U)
#define RNG_STA_BUSY_GET(x) (((uint32_t)(x) & RNG_STA_BUSY_MASK) >> RNG_STA_BUSY_SHIFT)

/* Bitfield definition for register: ERR */
/*
 * FUFE (RO)
 *
 * FIFO access error(underflow)
 */
#define RNG_ERR_FUFE_MASK (0x20U)
#define RNG_ERR_FUFE_SHIFT (5U)
#define RNG_ERR_FUFE_GET(x) (((uint32_t)(x) & RNG_ERR_FUFE_MASK) >> RNG_ERR_FUFE_SHIFT)

/*
 * SCKERR (RO)
 *
 * Self-test error
 * Indicates that the RNG failed the most recent self test. This bit is sticky and can only be reset by a
 * hardware reset or by writing 1 to the CMD[CE]
 */
#define RNG_ERR_SCKERR_MASK (0x8U)
#define RNG_ERR_SCKERR_SHIFT (3U)
#define RNG_ERR_SCKERR_GET(x) (((uint32_t)(x) & RNG_ERR_SCKERR_MASK) >> RNG_ERR_SCKERR_SHIFT)

/* Bitfield definition for register: FO2B */
/*
 * FO2B (RO)
 *
 * SW read the FIFO output.
 */
#define RNG_FO2B_FO2B_MASK (0xFFFFFFFFUL)
#define RNG_FO2B_FO2B_SHIFT (0U)
#define RNG_FO2B_FO2B_GET(x) (((uint32_t)(x) & RNG_FO2B_FO2B_MASK) >> RNG_FO2B_FO2B_SHIFT)

/* Bitfield definition for register array: R2SK */
/*
 * FO2S0 (RO)
 *
 * FIFO out to KMAN, will be SDP engine key.
 */
#define RNG_R2SK_FO2S0_MASK (0xFFFFFFFFUL)
#define RNG_R2SK_FO2S0_SHIFT (0U)
#define RNG_R2SK_FO2S0_GET(x) (((uint32_t)(x) & RNG_R2SK_FO2S0_MASK) >> RNG_R2SK_FO2S0_SHIFT)



/* R2SK register group index macro definition */
#define RNG_R2SK_FO2S0 (0UL)
#define RNG_R2SK_FO2S1 (1UL)
#define RNG_R2SK_FO2S2 (2UL)
#define RNG_R2SK_FO2S3 (3UL)
#define RNG_R2SK_FO2S4 (4UL)
#define RNG_R2SK_FO2S5 (5UL)
#define RNG_R2SK_FO2S6 (6UL)
#define RNG_R2SK_FO2S7 (7UL)


#endif /* HPM_RNG_H */
