/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SEI_H
#define HPM_SEI_H

typedef struct {
    struct {
        struct {
            __RW uint32_t CTRL;                /* 0x0: Engine control register */
            __RW uint32_t PTR_CFG;             /* 0x4: Pointer configuration register */
            __RW uint32_t WDG_CFG;             /* 0x8: Watch dog configuration register */
            __R  uint8_t  RESERVED0[4];        /* 0xC - 0xF: Reserved */
            __R  uint32_t EXE_STA;             /* 0x10: Execution status */
            __R  uint32_t EXE_PTR;             /* 0x14: Execution pointer */
            __R  uint32_t EXE_INST;            /* 0x18: Execution instruction */
            __R  uint32_t WDG_STA;             /* 0x1C: Watch dog status */
        } ENGINE;
        struct {
            __RW uint32_t CTRL;                /* 0x20: Transceiver control register */
            __RW uint32_t TYPE_CFG;            /* 0x24: Transceiver configuration register */
            __RW uint32_t BAUD_CFG;            /* 0x28: Transceiver baud rate register */
            __RW uint32_t DATA_CFG;            /* 0x2C: Transceiver data timing configuration */
            __RW uint32_t CLK_CFG;             /* 0x30: Transceiver clock timing configuration */
            __R  uint8_t  RESERVED0[4];        /* 0x34 - 0x37: Reserved */
            __R  uint32_t PIN;                 /* 0x38: Transceiver pin status */
            __R  uint32_t STATE;               /* 0x3C: FSM of asynchronous */
        } XCVR;
        struct {
            __RW uint32_t IN_CFG;              /* 0x40: Trigger input configuration */
            __W  uint32_t SW;                  /* 0x44: Software trigger */
            __RW uint32_t PRD_CFG;             /* 0x48: Period trigger configuration */
            __RW uint32_t PRD;                 /* 0x4C: Trigger period */
            __RW uint32_t OUT_CFG;             /* 0x50: Trigger output configuration */
            __R  uint8_t  RESERVED0[12];       /* 0x54 - 0x5F: Reserved */
            __R  uint32_t PRD_STS;             /* 0x60: Period trigger status */
            __R  uint32_t PRD_CNT;             /* 0x64: Period trigger counter */
            __R  uint8_t  RESERVED1[24];       /* 0x68 - 0x7F: Reserved */
        } TRG;
        struct {
            __RW uint32_t CMD[4];              /* 0x80 - 0x8C: Trigger command */
            __R  uint8_t  RESERVED0[16];       /* 0x90 - 0x9F: Reserved */
            __R  uint32_t TIME[4];             /* 0xA0 - 0xAC: Trigger Time */
            __R  uint8_t  RESERVED1[16];       /* 0xB0 - 0xBF: Reserved */
        } TRG_TABLE;
        struct {
            __RW uint32_t MODE;                /* 0xC0: command register mode */
            __RW uint32_t IDX;                 /* 0xC4: command register configuration */
            __R  uint8_t  RESERVED0[24];       /* 0xC8 - 0xDF: Reserved */
            __RW uint32_t CMD;                 /* 0xE0: command */
            __RW uint32_t SET;                 /* 0xE4: command bit set register */
            __RW uint32_t CLR;                 /* 0xE8: command bit clear register */
            __RW uint32_t INV;                 /* 0xEC: command bit invert register */
            __R  uint32_t IN;                  /* 0xF0: Commad input */
            __R  uint32_t OUT;                 /* 0xF4: Command output */
            __RW uint32_t STS;                 /* 0xF8: Command status */
            __R  uint8_t  RESERVED1[4];        /* 0xFC - 0xFF: Reserved */
        } CMD;
        struct {
            __RW uint32_t MIN;                 /* 0x100: command start value */
            __RW uint32_t MAX;                 /* 0x104: command end value */
            __RW uint32_t MSK;                 /* 0x108: command compare bit enable */
            __R  uint8_t  RESERVED0[4];        /* 0x10C - 0x10F: Reserved */
            __RW uint32_t PTA;                 /* 0x110: command pointer 0 - 3 */
            __RW uint32_t PTB;                 /* 0x114: command pointer 4 - 7 */
            __R  uint8_t  RESERVED1[8];        /* 0x118 - 0x11F: Reserved */
        } CMD_TABLE[8];
        struct {
            __RW uint32_t TRAN[4];             /* 0x200 - 0x20C: Latch state transition configuration */
            __RW uint32_t CFG;                 /* 0x210: Latch configuration */
            __R  uint8_t  RESERVED0[4];        /* 0x214 - 0x217: Reserved */
            __R  uint32_t TIME;                /* 0x218: Latch time */
            __R  uint32_t STS;                 /* 0x21C: Latch status */
        } LATCH[4];
        struct {
            __RW uint32_t SMP_EN;              /* 0x280: Sample selection register */
            __RW uint32_t SMP_CFG;             /* 0x284: Sample configuration */
            __RW uint32_t SMP_DAT;             /* 0x288: Sample data */
            __R  uint8_t  RESERVED0[4];        /* 0x28C - 0x28F: Reserved */
            __RW uint32_t SMP_POS;             /* 0x290: Sample override position */
            __RW uint32_t SMP_REV;             /* 0x294: Sample override revolution */
            __RW uint32_t SMP_SPD;             /* 0x298: Sample override speed */
            __RW uint32_t SMP_ACC;             /* 0x29C: Sample override accelerate */
            __RW uint32_t UPD_EN;              /* 0x2A0: Update configuration */
            __RW uint32_t UPD_CFG;             /* 0x2A4: Update configuration */
            __RW uint32_t UPD_DAT;             /* 0x2A8: Update data */
            __RW uint32_t UPD_TIME;            /* 0x2AC: Update overide time */
            __RW uint32_t UPD_POS;             /* 0x2B0: Update override position */
            __RW uint32_t UPD_REV;             /* 0x2B4: Update override revolution */
            __RW uint32_t UPD_SPD;             /* 0x2B8: Update override speed */
            __RW uint32_t UPD_ACC;             /* 0x2BC: Update override accelerate */
            __R  uint32_t SMP_VAL;             /* 0x2C0: Sample valid */
            __R  uint32_t SMP_STS;             /* 0x2C4: Sample status */
            __R  uint8_t  RESERVED1[4];        /* 0x2C8 - 0x2CB: Reserved */
            __R  uint32_t TIME_IN;             /* 0x2CC: input time */
            __R  uint32_t POS_IN;              /* 0x2D0: Input position */
            __R  uint32_t REV_IN;              /* 0x2D4: Input revolution */
            __R  uint32_t SPD_IN;              /* 0x2D8: Input speed */
            __R  uint32_t ACC_IN;              /* 0x2DC: Input accelerate */
            __R  uint8_t  RESERVED2[4];        /* 0x2E0 - 0x2E3: Reserved */
            __R  uint32_t UPD_STS;             /* 0x2E4: Update status */
            __R  uint8_t  RESERVED3[24];       /* 0x2E8 - 0x2FF: Reserved */
        } POS;
        struct {
            __RW uint32_t INT_EN;              /* 0x300: Interrupt Enable */
            __W  uint32_t INT_FLAG;            /* 0x304: Interrupt flag */
            __R  uint32_t INT_STS;             /* 0x308: Interrupt status */
            __R  uint8_t  RESERVED0[4];        /* 0x30C - 0x30F: Reserved */
            __RW uint32_t POINTER0;            /* 0x310: Match pointer 0 */
            __RW uint32_t POINTER1;            /* 0x314: Match pointer 1 */
            __RW uint32_t INSTR0;              /* 0x318: Match instruction 0 */
            __RW uint32_t INSTR1;              /* 0x31C: Match instruction 1 */
        } IRQ;
        __R  uint8_t  RESERVED0[224];          /* 0x320 - 0x3FF: Reserved */
    } CTRL[2];
    __R  uint8_t  RESERVED0[11264];            /* 0x800 - 0x33FF: Reserved */
    __RW uint32_t INSTR[64];                   /* 0x3400 - 0x34FC: Instructions */
    __R  uint8_t  RESERVED1[768];              /* 0x3500 - 0x37FF: Reserved */
    struct {
        __RW uint32_t MODE;                    /* 0x3800:  */
        __RW uint32_t IDX;                     /* 0x3804: Data register bit index */
        __RW uint32_t GOLD;                    /* 0x3808: Gold data for data check */
        __RW uint32_t CRCINIT;                 /* 0x380C: CRC calculation initial vector */
        __RW uint32_t CRCPOLY;                 /* 0x3810: CRC calculation polynomial */
        __R  uint8_t  RESERVED0[12];           /* 0x3814 - 0x381F: Reserved */
        __RW uint32_t DATA;                    /* 0x3820: Data value */
        __RW uint32_t SET;                     /* 0x3824: Data bit set */
        __RW uint32_t CLR;                     /* 0x3828: Data bit clear */
        __RW uint32_t INV;                     /* 0x382C: Data bit invert */
        __R  uint32_t IN;                      /* 0x3830: Data input */
        __R  uint32_t OUT;                     /* 0x3834: Data output */
        __RW uint32_t STS;                     /* 0x3838: Data status */
        __R  uint8_t  RESERVED1[4];            /* 0x383C - 0x383F: Reserved */
    } DAT[10];
} SEI_Type;


/* Bitfield definition for register of struct array CTRL: CTRL */
/*
 * WATCH (RW)
 *
 * Enable watch dog
 * 0: Watch dog disabled
 * 1: Watch dog enabled
 */
#define SEI_CTRL_ENGINE_CTRL_WATCH_MASK (0x1000000UL)
#define SEI_CTRL_ENGINE_CTRL_WATCH_SHIFT (24U)
#define SEI_CTRL_ENGINE_CTRL_WATCH_SET(x) (((uint32_t)(x) << SEI_CTRL_ENGINE_CTRL_WATCH_SHIFT) & SEI_CTRL_ENGINE_CTRL_WATCH_MASK)
#define SEI_CTRL_ENGINE_CTRL_WATCH_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_CTRL_WATCH_MASK) >> SEI_CTRL_ENGINE_CTRL_WATCH_SHIFT)

/*
 * ARMING (RW)
 *
 * Wait for trigger before excuting
 * 0: Execute on enable
 * 1: Wait trigger before exection after enabled
 */
#define SEI_CTRL_ENGINE_CTRL_ARMING_MASK (0x10000UL)
#define SEI_CTRL_ENGINE_CTRL_ARMING_SHIFT (16U)
#define SEI_CTRL_ENGINE_CTRL_ARMING_SET(x) (((uint32_t)(x) << SEI_CTRL_ENGINE_CTRL_ARMING_SHIFT) & SEI_CTRL_ENGINE_CTRL_ARMING_MASK)
#define SEI_CTRL_ENGINE_CTRL_ARMING_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_CTRL_ARMING_MASK) >> SEI_CTRL_ENGINE_CTRL_ARMING_SHIFT)

/*
 * EXCEPT (RW)
 *
 * Explain timout as exception
 * 0: when timeout, pointer move to next instruction
 * 1: when timeout, pointer jump to timeout vector
 */
#define SEI_CTRL_ENGINE_CTRL_EXCEPT_MASK (0x100U)
#define SEI_CTRL_ENGINE_CTRL_EXCEPT_SHIFT (8U)
#define SEI_CTRL_ENGINE_CTRL_EXCEPT_SET(x) (((uint32_t)(x) << SEI_CTRL_ENGINE_CTRL_EXCEPT_SHIFT) & SEI_CTRL_ENGINE_CTRL_EXCEPT_MASK)
#define SEI_CTRL_ENGINE_CTRL_EXCEPT_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_CTRL_EXCEPT_MASK) >> SEI_CTRL_ENGINE_CTRL_EXCEPT_SHIFT)

/*
 * REWIND (RW)
 *
 * Rewind execution pointer
 * 0: run
 * 1: clean status and rewind
 */
#define SEI_CTRL_ENGINE_CTRL_REWIND_MASK (0x10U)
#define SEI_CTRL_ENGINE_CTRL_REWIND_SHIFT (4U)
#define SEI_CTRL_ENGINE_CTRL_REWIND_SET(x) (((uint32_t)(x) << SEI_CTRL_ENGINE_CTRL_REWIND_SHIFT) & SEI_CTRL_ENGINE_CTRL_REWIND_MASK)
#define SEI_CTRL_ENGINE_CTRL_REWIND_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_CTRL_REWIND_MASK) >> SEI_CTRL_ENGINE_CTRL_REWIND_SHIFT)

/*
 * ENABLE (RW)
 *
 * Enable
 * 0: disable
 * 1: enable
 */
#define SEI_CTRL_ENGINE_CTRL_ENABLE_MASK (0x1U)
#define SEI_CTRL_ENGINE_CTRL_ENABLE_SHIFT (0U)
#define SEI_CTRL_ENGINE_CTRL_ENABLE_SET(x) (((uint32_t)(x) << SEI_CTRL_ENGINE_CTRL_ENABLE_SHIFT) & SEI_CTRL_ENGINE_CTRL_ENABLE_MASK)
#define SEI_CTRL_ENGINE_CTRL_ENABLE_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_CTRL_ENABLE_MASK) >> SEI_CTRL_ENGINE_CTRL_ENABLE_SHIFT)

/* Bitfield definition for register of struct array CTRL: PTR_CFG */
/*
 * DAT_CDM (RW)
 *
 * Select DATA register to receive CDM bit in BiSSC slave mode
 * 0: ignore
 * 1: command
 * 2: data register 2
 * 3: data register 3
 * ...
 * 29:data register 29
 * 30: value 0 when send, ignore in receive
 * 31: value1 when send, ignore in receive
 */
#define SEI_CTRL_ENGINE_PTR_CFG_DAT_CDM_MASK (0x1F000000UL)
#define SEI_CTRL_ENGINE_PTR_CFG_DAT_CDM_SHIFT (24U)
#define SEI_CTRL_ENGINE_PTR_CFG_DAT_CDM_SET(x) (((uint32_t)(x) << SEI_CTRL_ENGINE_PTR_CFG_DAT_CDM_SHIFT) & SEI_CTRL_ENGINE_PTR_CFG_DAT_CDM_MASK)
#define SEI_CTRL_ENGINE_PTR_CFG_DAT_CDM_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_PTR_CFG_DAT_CDM_MASK) >> SEI_CTRL_ENGINE_PTR_CFG_DAT_CDM_SHIFT)

/*
 * DAT_BASE (RW)
 *
 * Bias for data register access, if calculated index bigger than 32, index will wrap around
 * 0: real data index
 * 1: access index is 1 greater than instruction address
 * 2: access index is 2 greater than instruction address
 * ...
 * 31: access index is 31 greater than instruction address
 */
#define SEI_CTRL_ENGINE_PTR_CFG_DAT_BASE_MASK (0x1F0000UL)
#define SEI_CTRL_ENGINE_PTR_CFG_DAT_BASE_SHIFT (16U)
#define SEI_CTRL_ENGINE_PTR_CFG_DAT_BASE_SET(x) (((uint32_t)(x) << SEI_CTRL_ENGINE_PTR_CFG_DAT_BASE_SHIFT) & SEI_CTRL_ENGINE_PTR_CFG_DAT_BASE_MASK)
#define SEI_CTRL_ENGINE_PTR_CFG_DAT_BASE_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_PTR_CFG_DAT_BASE_MASK) >> SEI_CTRL_ENGINE_PTR_CFG_DAT_BASE_SHIFT)

/*
 * POINTER_WDOG (RW)
 *
 * Pointer to the instruction that the program starts executing after the instruction timeout. The timeout is WDOG_TIME
 */
#define SEI_CTRL_ENGINE_PTR_CFG_POINTER_WDOG_MASK (0xFF00U)
#define SEI_CTRL_ENGINE_PTR_CFG_POINTER_WDOG_SHIFT (8U)
#define SEI_CTRL_ENGINE_PTR_CFG_POINTER_WDOG_SET(x) (((uint32_t)(x) << SEI_CTRL_ENGINE_PTR_CFG_POINTER_WDOG_SHIFT) & SEI_CTRL_ENGINE_PTR_CFG_POINTER_WDOG_MASK)
#define SEI_CTRL_ENGINE_PTR_CFG_POINTER_WDOG_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_PTR_CFG_POINTER_WDOG_MASK) >> SEI_CTRL_ENGINE_PTR_CFG_POINTER_WDOG_SHIFT)

/*
 * POINTER_INIT (RW)
 *
 * Initial execute pointer
 */
#define SEI_CTRL_ENGINE_PTR_CFG_POINTER_INIT_MASK (0xFFU)
#define SEI_CTRL_ENGINE_PTR_CFG_POINTER_INIT_SHIFT (0U)
#define SEI_CTRL_ENGINE_PTR_CFG_POINTER_INIT_SET(x) (((uint32_t)(x) << SEI_CTRL_ENGINE_PTR_CFG_POINTER_INIT_SHIFT) & SEI_CTRL_ENGINE_PTR_CFG_POINTER_INIT_MASK)
#define SEI_CTRL_ENGINE_PTR_CFG_POINTER_INIT_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_PTR_CFG_POINTER_INIT_MASK) >> SEI_CTRL_ENGINE_PTR_CFG_POINTER_INIT_SHIFT)

/* Bitfield definition for register of struct array CTRL: WDG_CFG */
/*
 * WDOG_TIME (RW)
 *
 * Time out count for each instruction, counter in bit time.
 */
#define SEI_CTRL_ENGINE_WDG_CFG_WDOG_TIME_MASK (0xFFFFU)
#define SEI_CTRL_ENGINE_WDG_CFG_WDOG_TIME_SHIFT (0U)
#define SEI_CTRL_ENGINE_WDG_CFG_WDOG_TIME_SET(x) (((uint32_t)(x) << SEI_CTRL_ENGINE_WDG_CFG_WDOG_TIME_SHIFT) & SEI_CTRL_ENGINE_WDG_CFG_WDOG_TIME_MASK)
#define SEI_CTRL_ENGINE_WDG_CFG_WDOG_TIME_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_WDG_CFG_WDOG_TIME_MASK) >> SEI_CTRL_ENGINE_WDG_CFG_WDOG_TIME_SHIFT)

/* Bitfield definition for register of struct array CTRL: EXE_STA */
/*
 * TRIGERED (RO)
 *
 * Execution has been triggered
 * 0: Execution not triggered
 * 1: Execution triggered
 */
#define SEI_CTRL_ENGINE_EXE_STA_TRIGERED_MASK (0x100000UL)
#define SEI_CTRL_ENGINE_EXE_STA_TRIGERED_SHIFT (20U)
#define SEI_CTRL_ENGINE_EXE_STA_TRIGERED_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_EXE_STA_TRIGERED_MASK) >> SEI_CTRL_ENGINE_EXE_STA_TRIGERED_SHIFT)

/*
 * ARMED (RO)
 *
 * Waiting for trigger for execution
 * 0: Not in waiting status
 * 1: In waiting status
 */
#define SEI_CTRL_ENGINE_EXE_STA_ARMED_MASK (0x10000UL)
#define SEI_CTRL_ENGINE_EXE_STA_ARMED_SHIFT (16U)
#define SEI_CTRL_ENGINE_EXE_STA_ARMED_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_EXE_STA_ARMED_MASK) >> SEI_CTRL_ENGINE_EXE_STA_ARMED_SHIFT)

/*
 * EXPIRE (RO)
 *
 * Watchdog timer expired
 * 0: Not expired
 * 1: Expired
 */
#define SEI_CTRL_ENGINE_EXE_STA_EXPIRE_MASK (0x100U)
#define SEI_CTRL_ENGINE_EXE_STA_EXPIRE_SHIFT (8U)
#define SEI_CTRL_ENGINE_EXE_STA_EXPIRE_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_EXE_STA_EXPIRE_MASK) >> SEI_CTRL_ENGINE_EXE_STA_EXPIRE_SHIFT)

/*
 * STALL (RO)
 *
 * Program finished
 * 0: Program is executing
 * 1: Program finished
 */
#define SEI_CTRL_ENGINE_EXE_STA_STALL_MASK (0x1U)
#define SEI_CTRL_ENGINE_EXE_STA_STALL_SHIFT (0U)
#define SEI_CTRL_ENGINE_EXE_STA_STALL_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_EXE_STA_STALL_MASK) >> SEI_CTRL_ENGINE_EXE_STA_STALL_SHIFT)

/* Bitfield definition for register of struct array CTRL: EXE_PTR */
/*
 * HALT_CNT (RO)
 *
 * Halt count in halt instrution
 */
#define SEI_CTRL_ENGINE_EXE_PTR_HALT_CNT_MASK (0x1F000000UL)
#define SEI_CTRL_ENGINE_EXE_PTR_HALT_CNT_SHIFT (24U)
#define SEI_CTRL_ENGINE_EXE_PTR_HALT_CNT_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_EXE_PTR_HALT_CNT_MASK) >> SEI_CTRL_ENGINE_EXE_PTR_HALT_CNT_SHIFT)

/*
 * BIT_CNT (RO)
 *
 * Bit count in send and receive instruction execution
 */
#define SEI_CTRL_ENGINE_EXE_PTR_BIT_CNT_MASK (0x1F0000UL)
#define SEI_CTRL_ENGINE_EXE_PTR_BIT_CNT_SHIFT (16U)
#define SEI_CTRL_ENGINE_EXE_PTR_BIT_CNT_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_EXE_PTR_BIT_CNT_MASK) >> SEI_CTRL_ENGINE_EXE_PTR_BIT_CNT_SHIFT)

/*
 * POINTER (RO)
 *
 * Current program pointer
 */
#define SEI_CTRL_ENGINE_EXE_PTR_POINTER_MASK (0xFFU)
#define SEI_CTRL_ENGINE_EXE_PTR_POINTER_SHIFT (0U)
#define SEI_CTRL_ENGINE_EXE_PTR_POINTER_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_EXE_PTR_POINTER_MASK) >> SEI_CTRL_ENGINE_EXE_PTR_POINTER_SHIFT)

/* Bitfield definition for register of struct array CTRL: EXE_INST */
/*
 * INST (RO)
 *
 * Current instruction
 */
#define SEI_CTRL_ENGINE_EXE_INST_INST_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_ENGINE_EXE_INST_INST_SHIFT (0U)
#define SEI_CTRL_ENGINE_EXE_INST_INST_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_EXE_INST_INST_MASK) >> SEI_CTRL_ENGINE_EXE_INST_INST_SHIFT)

/* Bitfield definition for register of struct array CTRL: WDG_STA */
/*
 * WDOG_CNT (RO)
 *
 * Current watch dog counter value
 */
#define SEI_CTRL_ENGINE_WDG_STA_WDOG_CNT_MASK (0xFFFFU)
#define SEI_CTRL_ENGINE_WDG_STA_WDOG_CNT_SHIFT (0U)
#define SEI_CTRL_ENGINE_WDG_STA_WDOG_CNT_GET(x) (((uint32_t)(x) & SEI_CTRL_ENGINE_WDG_STA_WDOG_CNT_MASK) >> SEI_CTRL_ENGINE_WDG_STA_WDOG_CNT_SHIFT)

/* Bitfield definition for register of struct array CTRL: CTRL */
/*
 * TRISMP (RW)
 *
 * Tipple sampe
 * 0: sample 1 time for data transition
 * 1: sample 3 times in receive and result in 2oo3
 */
#define SEI_CTRL_XCVR_CTRL_TRISMP_MASK (0x1000U)
#define SEI_CTRL_XCVR_CTRL_TRISMP_SHIFT (12U)
#define SEI_CTRL_XCVR_CTRL_TRISMP_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_CTRL_TRISMP_SHIFT) & SEI_CTRL_XCVR_CTRL_TRISMP_MASK)
#define SEI_CTRL_XCVR_CTRL_TRISMP_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_CTRL_TRISMP_MASK) >> SEI_CTRL_XCVR_CTRL_TRISMP_SHIFT)

/*
 * PAR_CLR (WC)
 *
 * Clear parity error, this is a self clear bit
 * 0: no effect
 * 1: clear parity error
 */
#define SEI_CTRL_XCVR_CTRL_PAR_CLR_MASK (0x100U)
#define SEI_CTRL_XCVR_CTRL_PAR_CLR_SHIFT (8U)
#define SEI_CTRL_XCVR_CTRL_PAR_CLR_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_CTRL_PAR_CLR_SHIFT) & SEI_CTRL_XCVR_CTRL_PAR_CLR_MASK)
#define SEI_CTRL_XCVR_CTRL_PAR_CLR_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_CTRL_PAR_CLR_MASK) >> SEI_CTRL_XCVR_CTRL_PAR_CLR_SHIFT)

/*
 * RESTART (WC)
 *
 * Restart tranceiver, this is a self clear bit
 * 0: no effect
 * 1: reset tranceiver
 */
#define SEI_CTRL_XCVR_CTRL_RESTART_MASK (0x10U)
#define SEI_CTRL_XCVR_CTRL_RESTART_SHIFT (4U)
#define SEI_CTRL_XCVR_CTRL_RESTART_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_CTRL_RESTART_SHIFT) & SEI_CTRL_XCVR_CTRL_RESTART_MASK)
#define SEI_CTRL_XCVR_CTRL_RESTART_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_CTRL_RESTART_MASK) >> SEI_CTRL_XCVR_CTRL_RESTART_SHIFT)

/*
 * MODE (RW)
 *
 * Tranceiver mode
 * 0: synchronous maaster
 * 1: synchronous slave
 * 2: asynchronous mode
 * 3: asynchronous mode
 */
#define SEI_CTRL_XCVR_CTRL_MODE_MASK (0x3U)
#define SEI_CTRL_XCVR_CTRL_MODE_SHIFT (0U)
#define SEI_CTRL_XCVR_CTRL_MODE_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_CTRL_MODE_SHIFT) & SEI_CTRL_XCVR_CTRL_MODE_MASK)
#define SEI_CTRL_XCVR_CTRL_MODE_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_CTRL_MODE_MASK) >> SEI_CTRL_XCVR_CTRL_MODE_SHIFT)

/* Bitfield definition for register of struct array CTRL: TYPE_CFG */
/*
 * WAIT_LEN (RW)
 *
 * Number of extra stop bit for asynchronous mode
 * 0: 1 bit
 * 1: 2 bit
 * ...
 * 255: 256 bit
 */
#define SEI_CTRL_XCVR_TYPE_CFG_WAIT_LEN_MASK (0xFF000000UL)
#define SEI_CTRL_XCVR_TYPE_CFG_WAIT_LEN_SHIFT (24U)
#define SEI_CTRL_XCVR_TYPE_CFG_WAIT_LEN_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_TYPE_CFG_WAIT_LEN_SHIFT) & SEI_CTRL_XCVR_TYPE_CFG_WAIT_LEN_MASK)
#define SEI_CTRL_XCVR_TYPE_CFG_WAIT_LEN_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_TYPE_CFG_WAIT_LEN_MASK) >> SEI_CTRL_XCVR_TYPE_CFG_WAIT_LEN_SHIFT)

/*
 * DATA_LEN (RW)
 *
 * Number of data bit for asynchronous mode
 * 0: 1 bit
 * 1: 2 bit
 * ...
 * 31: 32 bit
 */
#define SEI_CTRL_XCVR_TYPE_CFG_DATA_LEN_MASK (0x1F0000UL)
#define SEI_CTRL_XCVR_TYPE_CFG_DATA_LEN_SHIFT (16U)
#define SEI_CTRL_XCVR_TYPE_CFG_DATA_LEN_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_TYPE_CFG_DATA_LEN_SHIFT) & SEI_CTRL_XCVR_TYPE_CFG_DATA_LEN_MASK)
#define SEI_CTRL_XCVR_TYPE_CFG_DATA_LEN_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_TYPE_CFG_DATA_LEN_MASK) >> SEI_CTRL_XCVR_TYPE_CFG_DATA_LEN_SHIFT)

/*
 * PAR_POL (RW)
 *
 * Polarity of parity for asynchronous mode
 * 0: even
 * 1: odd
 */
#define SEI_CTRL_XCVR_TYPE_CFG_PAR_POL_MASK (0x200U)
#define SEI_CTRL_XCVR_TYPE_CFG_PAR_POL_SHIFT (9U)
#define SEI_CTRL_XCVR_TYPE_CFG_PAR_POL_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_TYPE_CFG_PAR_POL_SHIFT) & SEI_CTRL_XCVR_TYPE_CFG_PAR_POL_MASK)
#define SEI_CTRL_XCVR_TYPE_CFG_PAR_POL_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_TYPE_CFG_PAR_POL_MASK) >> SEI_CTRL_XCVR_TYPE_CFG_PAR_POL_SHIFT)

/*
 * PAR_EN (RW)
 *
 * enable parity check for asynchronous mode
 * 0: disable
 * 1: enable
 */
#define SEI_CTRL_XCVR_TYPE_CFG_PAR_EN_MASK (0x100U)
#define SEI_CTRL_XCVR_TYPE_CFG_PAR_EN_SHIFT (8U)
#define SEI_CTRL_XCVR_TYPE_CFG_PAR_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_TYPE_CFG_PAR_EN_SHIFT) & SEI_CTRL_XCVR_TYPE_CFG_PAR_EN_MASK)
#define SEI_CTRL_XCVR_TYPE_CFG_PAR_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_TYPE_CFG_PAR_EN_MASK) >> SEI_CTRL_XCVR_TYPE_CFG_PAR_EN_SHIFT)

/*
 * DA_IDLEZ (RW)
 *
 * Idle state driver of data line
 * 0: output
 * 1: high-Z
 */
#define SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEZ_MASK (0x8U)
#define SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEZ_SHIFT (3U)
#define SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEZ_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEZ_SHIFT) & SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEZ_MASK)
#define SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEZ_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEZ_MASK) >> SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEZ_SHIFT)

/*
 * CK_IDLEZ (RW)
 *
 * Idle state driver of clock line
 * 0: output
 * 1: high-Z
 */
#define SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEZ_MASK (0x4U)
#define SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEZ_SHIFT (2U)
#define SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEZ_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEZ_SHIFT) & SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEZ_MASK)
#define SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEZ_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEZ_MASK) >> SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEZ_SHIFT)

/*
 * DA_IDLEV (RW)
 *
 * Idle state value of data line
 * 0: data'0'
 * 1: data'1'
 */
#define SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEV_MASK (0x2U)
#define SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEV_SHIFT (1U)
#define SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEV_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEV_SHIFT) & SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEV_MASK)
#define SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEV_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEV_MASK) >> SEI_CTRL_XCVR_TYPE_CFG_DA_IDLEV_SHIFT)

/*
 * CK_IDLEV (RW)
 *
 * Idle state value of clock line
 * 0: data'0'
 * 1: data'1'
 */
#define SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEV_MASK (0x1U)
#define SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEV_SHIFT (0U)
#define SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEV_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEV_SHIFT) & SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEV_MASK)
#define SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEV_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEV_MASK) >> SEI_CTRL_XCVR_TYPE_CFG_CK_IDLEV_SHIFT)

/* Bitfield definition for register of struct array CTRL: BAUD_CFG */
/*
 * SYNC_POINT (RW)
 *
 * Baud synchronous time, minmum bit time
 */
#define SEI_CTRL_XCVR_BAUD_CFG_SYNC_POINT_MASK (0xFFFF0000UL)
#define SEI_CTRL_XCVR_BAUD_CFG_SYNC_POINT_SHIFT (16U)
#define SEI_CTRL_XCVR_BAUD_CFG_SYNC_POINT_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_BAUD_CFG_SYNC_POINT_SHIFT) & SEI_CTRL_XCVR_BAUD_CFG_SYNC_POINT_MASK)
#define SEI_CTRL_XCVR_BAUD_CFG_SYNC_POINT_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_BAUD_CFG_SYNC_POINT_MASK) >> SEI_CTRL_XCVR_BAUD_CFG_SYNC_POINT_SHIFT)

/*
 * BAUD_DIV (RW)
 *
 * Baud rate, bit time in system clock cycle
 */
#define SEI_CTRL_XCVR_BAUD_CFG_BAUD_DIV_MASK (0xFFFFU)
#define SEI_CTRL_XCVR_BAUD_CFG_BAUD_DIV_SHIFT (0U)
#define SEI_CTRL_XCVR_BAUD_CFG_BAUD_DIV_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_BAUD_CFG_BAUD_DIV_SHIFT) & SEI_CTRL_XCVR_BAUD_CFG_BAUD_DIV_MASK)
#define SEI_CTRL_XCVR_BAUD_CFG_BAUD_DIV_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_BAUD_CFG_BAUD_DIV_MASK) >> SEI_CTRL_XCVR_BAUD_CFG_BAUD_DIV_SHIFT)

/* Bitfield definition for register of struct array CTRL: DATA_CFG */
/*
 * TXD_POINT (RW)
 *
 * data transmit point  in system clcok cycle
 */
#define SEI_CTRL_XCVR_DATA_CFG_TXD_POINT_MASK (0xFFFF0000UL)
#define SEI_CTRL_XCVR_DATA_CFG_TXD_POINT_SHIFT (16U)
#define SEI_CTRL_XCVR_DATA_CFG_TXD_POINT_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_DATA_CFG_TXD_POINT_SHIFT) & SEI_CTRL_XCVR_DATA_CFG_TXD_POINT_MASK)
#define SEI_CTRL_XCVR_DATA_CFG_TXD_POINT_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_DATA_CFG_TXD_POINT_MASK) >> SEI_CTRL_XCVR_DATA_CFG_TXD_POINT_SHIFT)

/*
 * RXD_POINT (RW)
 *
 * data receive point in system clcok cycle
 */
#define SEI_CTRL_XCVR_DATA_CFG_RXD_POINT_MASK (0xFFFFU)
#define SEI_CTRL_XCVR_DATA_CFG_RXD_POINT_SHIFT (0U)
#define SEI_CTRL_XCVR_DATA_CFG_RXD_POINT_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_DATA_CFG_RXD_POINT_SHIFT) & SEI_CTRL_XCVR_DATA_CFG_RXD_POINT_MASK)
#define SEI_CTRL_XCVR_DATA_CFG_RXD_POINT_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_DATA_CFG_RXD_POINT_MASK) >> SEI_CTRL_XCVR_DATA_CFG_RXD_POINT_SHIFT)

/* Bitfield definition for register of struct array CTRL: CLK_CFG */
/*
 * CK1_POINT (RW)
 *
 * clock point 1 in system clcok cycle
 */
#define SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_MASK (0xFFFF0000UL)
#define SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_SHIFT (16U)
#define SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_SHIFT) & SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_MASK)
#define SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_MASK) >> SEI_CTRL_XCVR_CLK_CFG_CK1_POINT_SHIFT)

/*
 * CK0_POINT (RW)
 *
 * clock point 0 in system clcok cycle
 */
#define SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_MASK (0xFFFFU)
#define SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_SHIFT (0U)
#define SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_SET(x) (((uint32_t)(x) << SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_SHIFT) & SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_MASK)
#define SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_MASK) >> SEI_CTRL_XCVR_CLK_CFG_CK0_POINT_SHIFT)

/* Bitfield definition for register of struct array CTRL: PIN */
/*
 * OE_CK (RO)
 *
 * CK drive state
 * 0: input
 * 1: output
 */
#define SEI_CTRL_XCVR_PIN_OE_CK_MASK (0x4000000UL)
#define SEI_CTRL_XCVR_PIN_OE_CK_SHIFT (26U)
#define SEI_CTRL_XCVR_PIN_OE_CK_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_OE_CK_MASK) >> SEI_CTRL_XCVR_PIN_OE_CK_SHIFT)

/*
 * DI_CK (RO)
 *
 * CK state
 * 0: data 0
 * 1: data 1
 */
#define SEI_CTRL_XCVR_PIN_DI_CK_MASK (0x2000000UL)
#define SEI_CTRL_XCVR_PIN_DI_CK_SHIFT (25U)
#define SEI_CTRL_XCVR_PIN_DI_CK_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_DI_CK_MASK) >> SEI_CTRL_XCVR_PIN_DI_CK_SHIFT)

/*
 * DO_CK (RO)
 *
 * CK output
 * 0: data 0
 * 1: data 1
 */
#define SEI_CTRL_XCVR_PIN_DO_CK_MASK (0x1000000UL)
#define SEI_CTRL_XCVR_PIN_DO_CK_SHIFT (24U)
#define SEI_CTRL_XCVR_PIN_DO_CK_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_DO_CK_MASK) >> SEI_CTRL_XCVR_PIN_DO_CK_SHIFT)

/*
 * OE_RX (RO)
 *
 * RX drive state
 * 0: input
 * 1: output
 */
#define SEI_CTRL_XCVR_PIN_OE_RX_MASK (0x40000UL)
#define SEI_CTRL_XCVR_PIN_OE_RX_SHIFT (18U)
#define SEI_CTRL_XCVR_PIN_OE_RX_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_OE_RX_MASK) >> SEI_CTRL_XCVR_PIN_OE_RX_SHIFT)

/*
 * DI_RX (RO)
 *
 * RX state
 * 0: data 0
 * 1: data 1
 */
#define SEI_CTRL_XCVR_PIN_DI_RX_MASK (0x20000UL)
#define SEI_CTRL_XCVR_PIN_DI_RX_SHIFT (17U)
#define SEI_CTRL_XCVR_PIN_DI_RX_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_DI_RX_MASK) >> SEI_CTRL_XCVR_PIN_DI_RX_SHIFT)

/*
 * DO_RX (RO)
 *
 * RX output
 * 0: data 0
 * 1: data 1
 */
#define SEI_CTRL_XCVR_PIN_DO_RX_MASK (0x10000UL)
#define SEI_CTRL_XCVR_PIN_DO_RX_SHIFT (16U)
#define SEI_CTRL_XCVR_PIN_DO_RX_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_DO_RX_MASK) >> SEI_CTRL_XCVR_PIN_DO_RX_SHIFT)

/*
 * OE_DE (RO)
 *
 * DE drive state
 * 0: input
 * 1: output
 */
#define SEI_CTRL_XCVR_PIN_OE_DE_MASK (0x400U)
#define SEI_CTRL_XCVR_PIN_OE_DE_SHIFT (10U)
#define SEI_CTRL_XCVR_PIN_OE_DE_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_OE_DE_MASK) >> SEI_CTRL_XCVR_PIN_OE_DE_SHIFT)

/*
 * DI_DE (RO)
 *
 * DE state
 * 0: data 0
 * 1: data 1
 */
#define SEI_CTRL_XCVR_PIN_DI_DE_MASK (0x200U)
#define SEI_CTRL_XCVR_PIN_DI_DE_SHIFT (9U)
#define SEI_CTRL_XCVR_PIN_DI_DE_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_DI_DE_MASK) >> SEI_CTRL_XCVR_PIN_DI_DE_SHIFT)

/*
 * DO_DE (RO)
 *
 * DE output
 * 0: data 0
 * 1: data 1
 */
#define SEI_CTRL_XCVR_PIN_DO_DE_MASK (0x100U)
#define SEI_CTRL_XCVR_PIN_DO_DE_SHIFT (8U)
#define SEI_CTRL_XCVR_PIN_DO_DE_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_DO_DE_MASK) >> SEI_CTRL_XCVR_PIN_DO_DE_SHIFT)

/*
 * OE_TX (RO)
 *
 * TX drive state
 * 0: input
 * 1: output
 */
#define SEI_CTRL_XCVR_PIN_OE_TX_MASK (0x4U)
#define SEI_CTRL_XCVR_PIN_OE_TX_SHIFT (2U)
#define SEI_CTRL_XCVR_PIN_OE_TX_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_OE_TX_MASK) >> SEI_CTRL_XCVR_PIN_OE_TX_SHIFT)

/*
 * DI_TX (RO)
 *
 * TX state
 * 0: data 0
 * 1: data 1
 */
#define SEI_CTRL_XCVR_PIN_DI_TX_MASK (0x2U)
#define SEI_CTRL_XCVR_PIN_DI_TX_SHIFT (1U)
#define SEI_CTRL_XCVR_PIN_DI_TX_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_DI_TX_MASK) >> SEI_CTRL_XCVR_PIN_DI_TX_SHIFT)

/*
 * DO_TX (RO)
 *
 * TX output
 * 0: data 0
 * 1: data 1
 */
#define SEI_CTRL_XCVR_PIN_DO_TX_MASK (0x1U)
#define SEI_CTRL_XCVR_PIN_DO_TX_SHIFT (0U)
#define SEI_CTRL_XCVR_PIN_DO_TX_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_PIN_DO_TX_MASK) >> SEI_CTRL_XCVR_PIN_DO_TX_SHIFT)

/* Bitfield definition for register of struct array CTRL: STATE */
/*
 * RECV_STATE (RO)
 *
 * FSM of asynchronous receive
 */
#define SEI_CTRL_XCVR_STATE_RECV_STATE_MASK (0x7000000UL)
#define SEI_CTRL_XCVR_STATE_RECV_STATE_SHIFT (24U)
#define SEI_CTRL_XCVR_STATE_RECV_STATE_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_STATE_RECV_STATE_MASK) >> SEI_CTRL_XCVR_STATE_RECV_STATE_SHIFT)

/*
 * SEND_STATE (RO)
 *
 * FSM of asynchronous transmit
 */
#define SEI_CTRL_XCVR_STATE_SEND_STATE_MASK (0x70000UL)
#define SEI_CTRL_XCVR_STATE_SEND_STATE_SHIFT (16U)
#define SEI_CTRL_XCVR_STATE_SEND_STATE_GET(x) (((uint32_t)(x) & SEI_CTRL_XCVR_STATE_SEND_STATE_MASK) >> SEI_CTRL_XCVR_STATE_SEND_STATE_SHIFT)

/* Bitfield definition for register of struct array CTRL: IN_CFG */
/*
 * PRD_EN (RW)
 *
 * Enable period trigger (tigger 2)
 * 0: periodical trigger disabled
 * 1: periodical trigger enabled
 */
#define SEI_CTRL_TRG_IN_CFG_PRD_EN_MASK (0x800000UL)
#define SEI_CTRL_TRG_IN_CFG_PRD_EN_SHIFT (23U)
#define SEI_CTRL_TRG_IN_CFG_PRD_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_IN_CFG_PRD_EN_SHIFT) & SEI_CTRL_TRG_IN_CFG_PRD_EN_MASK)
#define SEI_CTRL_TRG_IN_CFG_PRD_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_IN_CFG_PRD_EN_MASK) >> SEI_CTRL_TRG_IN_CFG_PRD_EN_SHIFT)

/*
 * SYNC_SEL (RW)
 *
 * Synchronize sigal selection (tigger 2)
 * 0: trigger in 0
 * 1: trigger in 1
 * ...
 * 7: trigger in 7
 */
#define SEI_CTRL_TRG_IN_CFG_SYNC_SEL_MASK (0x70000UL)
#define SEI_CTRL_TRG_IN_CFG_SYNC_SEL_SHIFT (16U)
#define SEI_CTRL_TRG_IN_CFG_SYNC_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_IN_CFG_SYNC_SEL_SHIFT) & SEI_CTRL_TRG_IN_CFG_SYNC_SEL_MASK)
#define SEI_CTRL_TRG_IN_CFG_SYNC_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_IN_CFG_SYNC_SEL_MASK) >> SEI_CTRL_TRG_IN_CFG_SYNC_SEL_SHIFT)

/*
 * IN1_EN (RW)
 *
 * Enable trigger 1
 * 0: disable trigger 1
 * 1: enable trigger 1
 */
#define SEI_CTRL_TRG_IN_CFG_IN1_EN_MASK (0x8000U)
#define SEI_CTRL_TRG_IN_CFG_IN1_EN_SHIFT (15U)
#define SEI_CTRL_TRG_IN_CFG_IN1_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_IN_CFG_IN1_EN_SHIFT) & SEI_CTRL_TRG_IN_CFG_IN1_EN_MASK)
#define SEI_CTRL_TRG_IN_CFG_IN1_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_IN_CFG_IN1_EN_MASK) >> SEI_CTRL_TRG_IN_CFG_IN1_EN_SHIFT)

/*
 * IN1_SEL (RW)
 *
 * Trigger 1 sigal selection
 * 0: trigger in 0
 * 1: trigger in 1
 * ...
 * 7: trigger in 7
 */
#define SEI_CTRL_TRG_IN_CFG_IN1_SEL_MASK (0x700U)
#define SEI_CTRL_TRG_IN_CFG_IN1_SEL_SHIFT (8U)
#define SEI_CTRL_TRG_IN_CFG_IN1_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_IN_CFG_IN1_SEL_SHIFT) & SEI_CTRL_TRG_IN_CFG_IN1_SEL_MASK)
#define SEI_CTRL_TRG_IN_CFG_IN1_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_IN_CFG_IN1_SEL_MASK) >> SEI_CTRL_TRG_IN_CFG_IN1_SEL_SHIFT)

/*
 * IN0_EN (RW)
 *
 * Enable trigger 0
 * 0: disable trigger 1
 * 1: enable trigger 1
 */
#define SEI_CTRL_TRG_IN_CFG_IN0_EN_MASK (0x80U)
#define SEI_CTRL_TRG_IN_CFG_IN0_EN_SHIFT (7U)
#define SEI_CTRL_TRG_IN_CFG_IN0_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_IN_CFG_IN0_EN_SHIFT) & SEI_CTRL_TRG_IN_CFG_IN0_EN_MASK)
#define SEI_CTRL_TRG_IN_CFG_IN0_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_IN_CFG_IN0_EN_MASK) >> SEI_CTRL_TRG_IN_CFG_IN0_EN_SHIFT)

/*
 * IN0_SEL (RW)
 *
 * Trigger 0 sigal selection
 * 0: trigger in 0
 * 1: trigger in 1
 * ...
 * 7: trigger in 7
 */
#define SEI_CTRL_TRG_IN_CFG_IN0_SEL_MASK (0x7U)
#define SEI_CTRL_TRG_IN_CFG_IN0_SEL_SHIFT (0U)
#define SEI_CTRL_TRG_IN_CFG_IN0_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_IN_CFG_IN0_SEL_SHIFT) & SEI_CTRL_TRG_IN_CFG_IN0_SEL_MASK)
#define SEI_CTRL_TRG_IN_CFG_IN0_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_IN_CFG_IN0_SEL_MASK) >> SEI_CTRL_TRG_IN_CFG_IN0_SEL_SHIFT)

/* Bitfield definition for register of struct array CTRL: SW */
/*
 * SOFT (WC)
 *
 * Software trigger (tigger 3). this bit is self-clear
 * 0: trigger source disabled
 * 1: trigger source enabled
 */
#define SEI_CTRL_TRG_SW_SOFT_MASK (0x1U)
#define SEI_CTRL_TRG_SW_SOFT_SHIFT (0U)
#define SEI_CTRL_TRG_SW_SOFT_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_SW_SOFT_SHIFT) & SEI_CTRL_TRG_SW_SOFT_MASK)
#define SEI_CTRL_TRG_SW_SOFT_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_SW_SOFT_MASK) >> SEI_CTRL_TRG_SW_SOFT_SHIFT)

/* Bitfield definition for register of struct array CTRL: PRD_CFG */
/*
 * ARMING (RW)
 *
 * Wait for trigger synchronous before trigger
 * 0: Trigger directly
 * 1: Wait trigger source before period trigger
 */
#define SEI_CTRL_TRG_PRD_CFG_ARMING_MASK (0x10000UL)
#define SEI_CTRL_TRG_PRD_CFG_ARMING_SHIFT (16U)
#define SEI_CTRL_TRG_PRD_CFG_ARMING_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_PRD_CFG_ARMING_SHIFT) & SEI_CTRL_TRG_PRD_CFG_ARMING_MASK)
#define SEI_CTRL_TRG_PRD_CFG_ARMING_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_PRD_CFG_ARMING_MASK) >> SEI_CTRL_TRG_PRD_CFG_ARMING_SHIFT)

/*
 * SYNC (RW)
 *
 * Synchronous
 * 0: Not synchronous
 * 1: Synchronous every trigger source
 */
#define SEI_CTRL_TRG_PRD_CFG_SYNC_MASK (0x1U)
#define SEI_CTRL_TRG_PRD_CFG_SYNC_SHIFT (0U)
#define SEI_CTRL_TRG_PRD_CFG_SYNC_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_PRD_CFG_SYNC_SHIFT) & SEI_CTRL_TRG_PRD_CFG_SYNC_MASK)
#define SEI_CTRL_TRG_PRD_CFG_SYNC_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_PRD_CFG_SYNC_MASK) >> SEI_CTRL_TRG_PRD_CFG_SYNC_SHIFT)

/* Bitfield definition for register of struct array CTRL: PRD */
/*
 * PERIOD (RW)
 *
 * Trigger period
 */
#define SEI_CTRL_TRG_PRD_PERIOD_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_TRG_PRD_PERIOD_SHIFT (0U)
#define SEI_CTRL_TRG_PRD_PERIOD_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_PRD_PERIOD_SHIFT) & SEI_CTRL_TRG_PRD_PERIOD_MASK)
#define SEI_CTRL_TRG_PRD_PERIOD_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_PRD_PERIOD_MASK) >> SEI_CTRL_TRG_PRD_PERIOD_SHIFT)

/* Bitfield definition for register of struct array CTRL: OUT_CFG */
/*
 * OUT3_EN (RW)
 *
 * Enable trigger 3
 * 0: disable trigger 3
 * 1: enable trigger 3
 */
#define SEI_CTRL_TRG_OUT_CFG_OUT3_EN_MASK (0x80000000UL)
#define SEI_CTRL_TRG_OUT_CFG_OUT3_EN_SHIFT (31U)
#define SEI_CTRL_TRG_OUT_CFG_OUT3_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_OUT_CFG_OUT3_EN_SHIFT) & SEI_CTRL_TRG_OUT_CFG_OUT3_EN_MASK)
#define SEI_CTRL_TRG_OUT_CFG_OUT3_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_OUT_CFG_OUT3_EN_MASK) >> SEI_CTRL_TRG_OUT_CFG_OUT3_EN_SHIFT)

/*
 * OUT3_SEL (RW)
 *
 * Trigger 3 sigal selection
 * 0: trigger out 0
 * 1: trigger out 1
 * ...
 * 7: trigger out 7
 */
#define SEI_CTRL_TRG_OUT_CFG_OUT3_SEL_MASK (0x7000000UL)
#define SEI_CTRL_TRG_OUT_CFG_OUT3_SEL_SHIFT (24U)
#define SEI_CTRL_TRG_OUT_CFG_OUT3_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_OUT_CFG_OUT3_SEL_SHIFT) & SEI_CTRL_TRG_OUT_CFG_OUT3_SEL_MASK)
#define SEI_CTRL_TRG_OUT_CFG_OUT3_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_OUT_CFG_OUT3_SEL_MASK) >> SEI_CTRL_TRG_OUT_CFG_OUT3_SEL_SHIFT)

/*
 * OUT2_EN (RW)
 *
 * Enable trigger 2
 * 0: disable trigger 2
 * 1: enable trigger 2
 */
#define SEI_CTRL_TRG_OUT_CFG_OUT2_EN_MASK (0x800000UL)
#define SEI_CTRL_TRG_OUT_CFG_OUT2_EN_SHIFT (23U)
#define SEI_CTRL_TRG_OUT_CFG_OUT2_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_OUT_CFG_OUT2_EN_SHIFT) & SEI_CTRL_TRG_OUT_CFG_OUT2_EN_MASK)
#define SEI_CTRL_TRG_OUT_CFG_OUT2_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_OUT_CFG_OUT2_EN_MASK) >> SEI_CTRL_TRG_OUT_CFG_OUT2_EN_SHIFT)

/*
 * OUT2_SEL (RW)
 *
 * Trigger 2 sigal selection
 * 0: trigger out 0
 * 1: trigger out 1
 * ...
 * 7: trigger out 7
 */
#define SEI_CTRL_TRG_OUT_CFG_OUT2_SEL_MASK (0x70000UL)
#define SEI_CTRL_TRG_OUT_CFG_OUT2_SEL_SHIFT (16U)
#define SEI_CTRL_TRG_OUT_CFG_OUT2_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_OUT_CFG_OUT2_SEL_SHIFT) & SEI_CTRL_TRG_OUT_CFG_OUT2_SEL_MASK)
#define SEI_CTRL_TRG_OUT_CFG_OUT2_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_OUT_CFG_OUT2_SEL_MASK) >> SEI_CTRL_TRG_OUT_CFG_OUT2_SEL_SHIFT)

/*
 * OUT1_EN (RW)
 *
 * Enable trigger 1
 * 0: disable trigger 1
 * 1: enable trigger 1
 */
#define SEI_CTRL_TRG_OUT_CFG_OUT1_EN_MASK (0x8000U)
#define SEI_CTRL_TRG_OUT_CFG_OUT1_EN_SHIFT (15U)
#define SEI_CTRL_TRG_OUT_CFG_OUT1_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_OUT_CFG_OUT1_EN_SHIFT) & SEI_CTRL_TRG_OUT_CFG_OUT1_EN_MASK)
#define SEI_CTRL_TRG_OUT_CFG_OUT1_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_OUT_CFG_OUT1_EN_MASK) >> SEI_CTRL_TRG_OUT_CFG_OUT1_EN_SHIFT)

/*
 * OUT1_SEL (RW)
 *
 * Trigger 1 sigal selection
 * 0: trigger out 0
 * 1: trigger out 1
 * ...
 * 7: trigger out 7
 */
#define SEI_CTRL_TRG_OUT_CFG_OUT1_SEL_MASK (0x700U)
#define SEI_CTRL_TRG_OUT_CFG_OUT1_SEL_SHIFT (8U)
#define SEI_CTRL_TRG_OUT_CFG_OUT1_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_OUT_CFG_OUT1_SEL_SHIFT) & SEI_CTRL_TRG_OUT_CFG_OUT1_SEL_MASK)
#define SEI_CTRL_TRG_OUT_CFG_OUT1_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_OUT_CFG_OUT1_SEL_MASK) >> SEI_CTRL_TRG_OUT_CFG_OUT1_SEL_SHIFT)

/*
 * OUT0_EN (RW)
 *
 * Enable trigger 0
 * 0: disable trigger 1
 * 1: enable trigger 1
 */
#define SEI_CTRL_TRG_OUT_CFG_OUT0_EN_MASK (0x80U)
#define SEI_CTRL_TRG_OUT_CFG_OUT0_EN_SHIFT (7U)
#define SEI_CTRL_TRG_OUT_CFG_OUT0_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_OUT_CFG_OUT0_EN_SHIFT) & SEI_CTRL_TRG_OUT_CFG_OUT0_EN_MASK)
#define SEI_CTRL_TRG_OUT_CFG_OUT0_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_OUT_CFG_OUT0_EN_MASK) >> SEI_CTRL_TRG_OUT_CFG_OUT0_EN_SHIFT)

/*
 * OUT0_SEL (RW)
 *
 * Trigger 0 sigal selection
 * 0: trigger out 0
 * 1: trigger out 1
 * ...
 * 7: trigger out 7
 */
#define SEI_CTRL_TRG_OUT_CFG_OUT0_SEL_MASK (0x7U)
#define SEI_CTRL_TRG_OUT_CFG_OUT0_SEL_SHIFT (0U)
#define SEI_CTRL_TRG_OUT_CFG_OUT0_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_OUT_CFG_OUT0_SEL_SHIFT) & SEI_CTRL_TRG_OUT_CFG_OUT0_SEL_MASK)
#define SEI_CTRL_TRG_OUT_CFG_OUT0_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_OUT_CFG_OUT0_SEL_MASK) >> SEI_CTRL_TRG_OUT_CFG_OUT0_SEL_SHIFT)

/* Bitfield definition for register of struct array CTRL: PRD_STS */
/*
 * TRIGERED (RO)
 *
 * Period has been triggered
 * 0: Not triggered
 * 1: Triggered
 */
#define SEI_CTRL_TRG_PRD_STS_TRIGERED_MASK (0x100000UL)
#define SEI_CTRL_TRG_PRD_STS_TRIGERED_SHIFT (20U)
#define SEI_CTRL_TRG_PRD_STS_TRIGERED_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_PRD_STS_TRIGERED_MASK) >> SEI_CTRL_TRG_PRD_STS_TRIGERED_SHIFT)

/*
 * ARMED (RO)
 *
 * Waiting for trigger
 * 0: Not in waiting status
 * 1: In waiting status
 */
#define SEI_CTRL_TRG_PRD_STS_ARMED_MASK (0x10000UL)
#define SEI_CTRL_TRG_PRD_STS_ARMED_SHIFT (16U)
#define SEI_CTRL_TRG_PRD_STS_ARMED_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_PRD_STS_ARMED_MASK) >> SEI_CTRL_TRG_PRD_STS_ARMED_SHIFT)

/* Bitfield definition for register of struct array CTRL: PRD_CNT */
/*
 * PERIOD_CNT (RO)
 *
 * Trigger period counter
 */
#define SEI_CTRL_TRG_PRD_CNT_PERIOD_CNT_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_TRG_PRD_CNT_PERIOD_CNT_SHIFT (0U)
#define SEI_CTRL_TRG_PRD_CNT_PERIOD_CNT_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_PRD_CNT_PERIOD_CNT_MASK) >> SEI_CTRL_TRG_PRD_CNT_PERIOD_CNT_SHIFT)

/* Bitfield definition for register of struct array CTRL: 0 */
/*
 * CMD_TRIGGER0 (RW)
 *
 * Trigger command
 */
#define SEI_CTRL_TRG_TABLE_CMD_CMD_TRIGGER0_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_TRG_TABLE_CMD_CMD_TRIGGER0_SHIFT (0U)
#define SEI_CTRL_TRG_TABLE_CMD_CMD_TRIGGER0_SET(x) (((uint32_t)(x) << SEI_CTRL_TRG_TABLE_CMD_CMD_TRIGGER0_SHIFT) & SEI_CTRL_TRG_TABLE_CMD_CMD_TRIGGER0_MASK)
#define SEI_CTRL_TRG_TABLE_CMD_CMD_TRIGGER0_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_TABLE_CMD_CMD_TRIGGER0_MASK) >> SEI_CTRL_TRG_TABLE_CMD_CMD_TRIGGER0_SHIFT)

/* Bitfield definition for register of struct array CTRL: 0 */
/*
 * TRIGGER0_TIME (RO)
 *
 * Trigger time
 */
#define SEI_CTRL_TRG_TABLE_TIME_TRIGGER0_TIME_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_TRG_TABLE_TIME_TRIGGER0_TIME_SHIFT (0U)
#define SEI_CTRL_TRG_TABLE_TIME_TRIGGER0_TIME_GET(x) (((uint32_t)(x) & SEI_CTRL_TRG_TABLE_TIME_TRIGGER0_TIME_MASK) >> SEI_CTRL_TRG_TABLE_TIME_TRIGGER0_TIME_SHIFT)

/* Bitfield definition for register of struct array CTRL: MODE */
/*
 * WLEN (RW)
 *
 * word length
 * 0: 1 bit
 * 1: 2 bit
 * ...
 * 31: 32 bit
 */
#define SEI_CTRL_CMD_MODE_WLEN_MASK (0x1F0000UL)
#define SEI_CTRL_CMD_MODE_WLEN_SHIFT (16U)
#define SEI_CTRL_CMD_MODE_WLEN_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_MODE_WLEN_SHIFT) & SEI_CTRL_CMD_MODE_WLEN_MASK)
#define SEI_CTRL_CMD_MODE_WLEN_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_MODE_WLEN_MASK) >> SEI_CTRL_CMD_MODE_WLEN_SHIFT)

/*
 * WORDER (RW)
 *
 * word order
 * 0: sample as bit order
 * 1: different from bit order
 */
#define SEI_CTRL_CMD_MODE_WORDER_MASK (0x800U)
#define SEI_CTRL_CMD_MODE_WORDER_SHIFT (11U)
#define SEI_CTRL_CMD_MODE_WORDER_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_MODE_WORDER_SHIFT) & SEI_CTRL_CMD_MODE_WORDER_MASK)
#define SEI_CTRL_CMD_MODE_WORDER_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_MODE_WORDER_MASK) >> SEI_CTRL_CMD_MODE_WORDER_SHIFT)

/*
 * BORDER (RW)
 *
 * bit order
 * 0: LSB first
 * 1: MSB first
 */
#define SEI_CTRL_CMD_MODE_BORDER_MASK (0x400U)
#define SEI_CTRL_CMD_MODE_BORDER_SHIFT (10U)
#define SEI_CTRL_CMD_MODE_BORDER_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_MODE_BORDER_SHIFT) & SEI_CTRL_CMD_MODE_BORDER_MASK)
#define SEI_CTRL_CMD_MODE_BORDER_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_MODE_BORDER_MASK) >> SEI_CTRL_CMD_MODE_BORDER_SHIFT)

/*
 * SIGNED (RW)
 *
 * Signed
 * 0: unsigned value
 * 1: signed value
 */
#define SEI_CTRL_CMD_MODE_SIGNED_MASK (0x200U)
#define SEI_CTRL_CMD_MODE_SIGNED_SHIFT (9U)
#define SEI_CTRL_CMD_MODE_SIGNED_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_MODE_SIGNED_SHIFT) & SEI_CTRL_CMD_MODE_SIGNED_MASK)
#define SEI_CTRL_CMD_MODE_SIGNED_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_MODE_SIGNED_MASK) >> SEI_CTRL_CMD_MODE_SIGNED_SHIFT)

/*
 * REWIND (WC)
 *
 * Write 1 to rewind read/write pointer, this is a self clear bit
 */
#define SEI_CTRL_CMD_MODE_REWIND_MASK (0x100U)
#define SEI_CTRL_CMD_MODE_REWIND_SHIFT (8U)
#define SEI_CTRL_CMD_MODE_REWIND_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_MODE_REWIND_SHIFT) & SEI_CTRL_CMD_MODE_REWIND_MASK)
#define SEI_CTRL_CMD_MODE_REWIND_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_MODE_REWIND_MASK) >> SEI_CTRL_CMD_MODE_REWIND_SHIFT)

/*
 * MODE (RW)
 *
 * Data mode(CMD register only support data mode)
 * 0: data mode
 * 1: check mode
 * 2: CRC mode
 */
#define SEI_CTRL_CMD_MODE_MODE_MASK (0x3U)
#define SEI_CTRL_CMD_MODE_MODE_SHIFT (0U)
#define SEI_CTRL_CMD_MODE_MODE_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_MODE_MODE_SHIFT) & SEI_CTRL_CMD_MODE_MODE_MASK)
#define SEI_CTRL_CMD_MODE_MODE_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_MODE_MODE_MASK) >> SEI_CTRL_CMD_MODE_MODE_SHIFT)

/* Bitfield definition for register of struct array CTRL: IDX */
/*
 * LAST_BIT (RW)
 *
 * Last bit index for tranceive
 */
#define SEI_CTRL_CMD_IDX_LAST_BIT_MASK (0x1F000000UL)
#define SEI_CTRL_CMD_IDX_LAST_BIT_SHIFT (24U)
#define SEI_CTRL_CMD_IDX_LAST_BIT_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_IDX_LAST_BIT_SHIFT) & SEI_CTRL_CMD_IDX_LAST_BIT_MASK)
#define SEI_CTRL_CMD_IDX_LAST_BIT_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_IDX_LAST_BIT_MASK) >> SEI_CTRL_CMD_IDX_LAST_BIT_SHIFT)

/*
 * FIRST_BIT (RW)
 *
 * First bit index for tranceive
 */
#define SEI_CTRL_CMD_IDX_FIRST_BIT_MASK (0x1F0000UL)
#define SEI_CTRL_CMD_IDX_FIRST_BIT_SHIFT (16U)
#define SEI_CTRL_CMD_IDX_FIRST_BIT_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_IDX_FIRST_BIT_SHIFT) & SEI_CTRL_CMD_IDX_FIRST_BIT_MASK)
#define SEI_CTRL_CMD_IDX_FIRST_BIT_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_IDX_FIRST_BIT_MASK) >> SEI_CTRL_CMD_IDX_FIRST_BIT_SHIFT)

/*
 * MAX_BIT (RW)
 *
 * Highest bit index
 */
#define SEI_CTRL_CMD_IDX_MAX_BIT_MASK (0x1F00U)
#define SEI_CTRL_CMD_IDX_MAX_BIT_SHIFT (8U)
#define SEI_CTRL_CMD_IDX_MAX_BIT_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_IDX_MAX_BIT_SHIFT) & SEI_CTRL_CMD_IDX_MAX_BIT_MASK)
#define SEI_CTRL_CMD_IDX_MAX_BIT_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_IDX_MAX_BIT_MASK) >> SEI_CTRL_CMD_IDX_MAX_BIT_SHIFT)

/*
 * MIN_BIT (RW)
 *
 * Lowest bit index
 */
#define SEI_CTRL_CMD_IDX_MIN_BIT_MASK (0x1FU)
#define SEI_CTRL_CMD_IDX_MIN_BIT_SHIFT (0U)
#define SEI_CTRL_CMD_IDX_MIN_BIT_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_IDX_MIN_BIT_SHIFT) & SEI_CTRL_CMD_IDX_MIN_BIT_MASK)
#define SEI_CTRL_CMD_IDX_MIN_BIT_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_IDX_MIN_BIT_MASK) >> SEI_CTRL_CMD_IDX_MIN_BIT_SHIFT)

/* Bitfield definition for register of struct array CTRL: CMD */
/*
 * DATA (RW)
 *
 * DATA
 */
#define SEI_CTRL_CMD_CMD_DATA_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_CMD_CMD_DATA_SHIFT (0U)
#define SEI_CTRL_CMD_CMD_DATA_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_CMD_DATA_SHIFT) & SEI_CTRL_CMD_CMD_DATA_MASK)
#define SEI_CTRL_CMD_CMD_DATA_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_CMD_DATA_MASK) >> SEI_CTRL_CMD_CMD_DATA_SHIFT)

/* Bitfield definition for register of struct array CTRL: SET */
/*
 * DATA_SET (RW)
 *
 * DATA bit set
 */
#define SEI_CTRL_CMD_SET_DATA_SET_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_CMD_SET_DATA_SET_SHIFT (0U)
#define SEI_CTRL_CMD_SET_DATA_SET_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_SET_DATA_SET_SHIFT) & SEI_CTRL_CMD_SET_DATA_SET_MASK)
#define SEI_CTRL_CMD_SET_DATA_SET_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_SET_DATA_SET_MASK) >> SEI_CTRL_CMD_SET_DATA_SET_SHIFT)

/* Bitfield definition for register of struct array CTRL: CLR */
/*
 * DATA_CLR (RW)
 *
 * DATA bit clear
 */
#define SEI_CTRL_CMD_CLR_DATA_CLR_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_CMD_CLR_DATA_CLR_SHIFT (0U)
#define SEI_CTRL_CMD_CLR_DATA_CLR_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_CLR_DATA_CLR_SHIFT) & SEI_CTRL_CMD_CLR_DATA_CLR_MASK)
#define SEI_CTRL_CMD_CLR_DATA_CLR_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_CLR_DATA_CLR_MASK) >> SEI_CTRL_CMD_CLR_DATA_CLR_SHIFT)

/* Bitfield definition for register of struct array CTRL: INV */
/*
 * DATA_TGL (RW)
 *
 * DATA bit toggle
 */
#define SEI_CTRL_CMD_INV_DATA_TGL_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_CMD_INV_DATA_TGL_SHIFT (0U)
#define SEI_CTRL_CMD_INV_DATA_TGL_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_INV_DATA_TGL_SHIFT) & SEI_CTRL_CMD_INV_DATA_TGL_MASK)
#define SEI_CTRL_CMD_INV_DATA_TGL_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_INV_DATA_TGL_MASK) >> SEI_CTRL_CMD_INV_DATA_TGL_SHIFT)

/* Bitfield definition for register of struct array CTRL: IN */
/*
 * DATA_IN (RO)
 *
 * Commad input
 */
#define SEI_CTRL_CMD_IN_DATA_IN_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_CMD_IN_DATA_IN_SHIFT (0U)
#define SEI_CTRL_CMD_IN_DATA_IN_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_IN_DATA_IN_MASK) >> SEI_CTRL_CMD_IN_DATA_IN_SHIFT)

/* Bitfield definition for register of struct array CTRL: OUT */
/*
 * DATA_OUT (RO)
 *
 * Command output
 */
#define SEI_CTRL_CMD_OUT_DATA_OUT_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_CMD_OUT_DATA_OUT_SHIFT (0U)
#define SEI_CTRL_CMD_OUT_DATA_OUT_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_OUT_DATA_OUT_MASK) >> SEI_CTRL_CMD_OUT_DATA_OUT_SHIFT)

/* Bitfield definition for register of struct array CTRL: STS */
/*
 * WORD_IDX (RO)
 *
 * Word index
 */
#define SEI_CTRL_CMD_STS_WORD_IDX_MASK (0x1F0000UL)
#define SEI_CTRL_CMD_STS_WORD_IDX_SHIFT (16U)
#define SEI_CTRL_CMD_STS_WORD_IDX_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_STS_WORD_IDX_MASK) >> SEI_CTRL_CMD_STS_WORD_IDX_SHIFT)

/*
 * WORD_CNT (RO)
 *
 * Word counter
 */
#define SEI_CTRL_CMD_STS_WORD_CNT_MASK (0x1F00U)
#define SEI_CTRL_CMD_STS_WORD_CNT_SHIFT (8U)
#define SEI_CTRL_CMD_STS_WORD_CNT_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_STS_WORD_CNT_MASK) >> SEI_CTRL_CMD_STS_WORD_CNT_SHIFT)

/*
 * BIT_IDX (RO)
 *
 * Bit index
 */
#define SEI_CTRL_CMD_STS_BIT_IDX_MASK (0x1FU)
#define SEI_CTRL_CMD_STS_BIT_IDX_SHIFT (0U)
#define SEI_CTRL_CMD_STS_BIT_IDX_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_STS_BIT_IDX_MASK) >> SEI_CTRL_CMD_STS_BIT_IDX_SHIFT)

/* Bitfield definition for register of struct array CTRL: MIN */
/*
 * CMD_MIN (RW)
 *
 * minimum command value
 */
#define SEI_CTRL_CMD_TABLE_MIN_CMD_MIN_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_CMD_TABLE_MIN_CMD_MIN_SHIFT (0U)
#define SEI_CTRL_CMD_TABLE_MIN_CMD_MIN_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_TABLE_MIN_CMD_MIN_SHIFT) & SEI_CTRL_CMD_TABLE_MIN_CMD_MIN_MASK)
#define SEI_CTRL_CMD_TABLE_MIN_CMD_MIN_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_TABLE_MIN_CMD_MIN_MASK) >> SEI_CTRL_CMD_TABLE_MIN_CMD_MIN_SHIFT)

/* Bitfield definition for register of struct array CTRL: MAX */
/*
 * CMD_MAX (RW)
 *
 * maximum command value
 */
#define SEI_CTRL_CMD_TABLE_MAX_CMD_MAX_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_CMD_TABLE_MAX_CMD_MAX_SHIFT (0U)
#define SEI_CTRL_CMD_TABLE_MAX_CMD_MAX_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_TABLE_MAX_CMD_MAX_SHIFT) & SEI_CTRL_CMD_TABLE_MAX_CMD_MAX_MASK)
#define SEI_CTRL_CMD_TABLE_MAX_CMD_MAX_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_TABLE_MAX_CMD_MAX_MASK) >> SEI_CTRL_CMD_TABLE_MAX_CMD_MAX_SHIFT)

/* Bitfield definition for register of struct array CTRL: MSK */
/*
 * CMD_MASK (RW)
 *
 * compare mask
 */
#define SEI_CTRL_CMD_TABLE_MSK_CMD_MASK_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_CMD_TABLE_MSK_CMD_MASK_SHIFT (0U)
#define SEI_CTRL_CMD_TABLE_MSK_CMD_MASK_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_TABLE_MSK_CMD_MASK_SHIFT) & SEI_CTRL_CMD_TABLE_MSK_CMD_MASK_MASK)
#define SEI_CTRL_CMD_TABLE_MSK_CMD_MASK_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_TABLE_MSK_CMD_MASK_MASK) >> SEI_CTRL_CMD_TABLE_MSK_CMD_MASK_SHIFT)

/* Bitfield definition for register of struct array CTRL: PTA */
/*
 * PTR3 (RW)
 *
 * pointer3
 */
#define SEI_CTRL_CMD_TABLE_PTA_PTR3_MASK (0xFF000000UL)
#define SEI_CTRL_CMD_TABLE_PTA_PTR3_SHIFT (24U)
#define SEI_CTRL_CMD_TABLE_PTA_PTR3_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_TABLE_PTA_PTR3_SHIFT) & SEI_CTRL_CMD_TABLE_PTA_PTR3_MASK)
#define SEI_CTRL_CMD_TABLE_PTA_PTR3_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_TABLE_PTA_PTR3_MASK) >> SEI_CTRL_CMD_TABLE_PTA_PTR3_SHIFT)

/*
 * PTR2 (RW)
 *
 * pointer2
 */
#define SEI_CTRL_CMD_TABLE_PTA_PTR2_MASK (0xFF0000UL)
#define SEI_CTRL_CMD_TABLE_PTA_PTR2_SHIFT (16U)
#define SEI_CTRL_CMD_TABLE_PTA_PTR2_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_TABLE_PTA_PTR2_SHIFT) & SEI_CTRL_CMD_TABLE_PTA_PTR2_MASK)
#define SEI_CTRL_CMD_TABLE_PTA_PTR2_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_TABLE_PTA_PTR2_MASK) >> SEI_CTRL_CMD_TABLE_PTA_PTR2_SHIFT)

/*
 * PTR1 (RW)
 *
 * pointer1
 */
#define SEI_CTRL_CMD_TABLE_PTA_PTR1_MASK (0xFF00U)
#define SEI_CTRL_CMD_TABLE_PTA_PTR1_SHIFT (8U)
#define SEI_CTRL_CMD_TABLE_PTA_PTR1_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_TABLE_PTA_PTR1_SHIFT) & SEI_CTRL_CMD_TABLE_PTA_PTR1_MASK)
#define SEI_CTRL_CMD_TABLE_PTA_PTR1_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_TABLE_PTA_PTR1_MASK) >> SEI_CTRL_CMD_TABLE_PTA_PTR1_SHIFT)

/*
 * PTR0 (RW)
 *
 * pointer0
 */
#define SEI_CTRL_CMD_TABLE_PTA_PTR0_MASK (0xFFU)
#define SEI_CTRL_CMD_TABLE_PTA_PTR0_SHIFT (0U)
#define SEI_CTRL_CMD_TABLE_PTA_PTR0_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_TABLE_PTA_PTR0_SHIFT) & SEI_CTRL_CMD_TABLE_PTA_PTR0_MASK)
#define SEI_CTRL_CMD_TABLE_PTA_PTR0_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_TABLE_PTA_PTR0_MASK) >> SEI_CTRL_CMD_TABLE_PTA_PTR0_SHIFT)

/* Bitfield definition for register of struct array CTRL: PTB */
/*
 * PTR7 (RW)
 *
 * pointer7
 */
#define SEI_CTRL_CMD_TABLE_PTB_PTR7_MASK (0xFF000000UL)
#define SEI_CTRL_CMD_TABLE_PTB_PTR7_SHIFT (24U)
#define SEI_CTRL_CMD_TABLE_PTB_PTR7_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_TABLE_PTB_PTR7_SHIFT) & SEI_CTRL_CMD_TABLE_PTB_PTR7_MASK)
#define SEI_CTRL_CMD_TABLE_PTB_PTR7_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_TABLE_PTB_PTR7_MASK) >> SEI_CTRL_CMD_TABLE_PTB_PTR7_SHIFT)

/*
 * PTR6 (RW)
 *
 * pointer6
 */
#define SEI_CTRL_CMD_TABLE_PTB_PTR6_MASK (0xFF0000UL)
#define SEI_CTRL_CMD_TABLE_PTB_PTR6_SHIFT (16U)
#define SEI_CTRL_CMD_TABLE_PTB_PTR6_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_TABLE_PTB_PTR6_SHIFT) & SEI_CTRL_CMD_TABLE_PTB_PTR6_MASK)
#define SEI_CTRL_CMD_TABLE_PTB_PTR6_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_TABLE_PTB_PTR6_MASK) >> SEI_CTRL_CMD_TABLE_PTB_PTR6_SHIFT)

/*
 * PTR5 (RW)
 *
 * pointer5
 */
#define SEI_CTRL_CMD_TABLE_PTB_PTR5_MASK (0xFF00U)
#define SEI_CTRL_CMD_TABLE_PTB_PTR5_SHIFT (8U)
#define SEI_CTRL_CMD_TABLE_PTB_PTR5_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_TABLE_PTB_PTR5_SHIFT) & SEI_CTRL_CMD_TABLE_PTB_PTR5_MASK)
#define SEI_CTRL_CMD_TABLE_PTB_PTR5_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_TABLE_PTB_PTR5_MASK) >> SEI_CTRL_CMD_TABLE_PTB_PTR5_SHIFT)

/*
 * PTR4 (RW)
 *
 * pointer4
 */
#define SEI_CTRL_CMD_TABLE_PTB_PTR4_MASK (0xFFU)
#define SEI_CTRL_CMD_TABLE_PTB_PTR4_SHIFT (0U)
#define SEI_CTRL_CMD_TABLE_PTB_PTR4_SET(x) (((uint32_t)(x) << SEI_CTRL_CMD_TABLE_PTB_PTR4_SHIFT) & SEI_CTRL_CMD_TABLE_PTB_PTR4_MASK)
#define SEI_CTRL_CMD_TABLE_PTB_PTR4_GET(x) (((uint32_t)(x) & SEI_CTRL_CMD_TABLE_PTB_PTR4_MASK) >> SEI_CTRL_CMD_TABLE_PTB_PTR4_SHIFT)

/* Bitfield definition for register of struct array CTRL: 0_1 */
/*
 * POINTER (RW)
 *
 * pointer
 */
#define SEI_CTRL_LATCH_TRAN_POINTER_MASK (0xFF000000UL)
#define SEI_CTRL_LATCH_TRAN_POINTER_SHIFT (24U)
#define SEI_CTRL_LATCH_TRAN_POINTER_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_TRAN_POINTER_SHIFT) & SEI_CTRL_LATCH_TRAN_POINTER_MASK)
#define SEI_CTRL_LATCH_TRAN_POINTER_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_TRAN_POINTER_MASK) >> SEI_CTRL_LATCH_TRAN_POINTER_SHIFT)

/*
 * CFG_TM (RW)
 *
 * timeout
 * 0: high
 * 1: low
 * 2: rise
 * 3: fall
 */
#define SEI_CTRL_LATCH_TRAN_CFG_TM_MASK (0x30000UL)
#define SEI_CTRL_LATCH_TRAN_CFG_TM_SHIFT (16U)
#define SEI_CTRL_LATCH_TRAN_CFG_TM_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_TRAN_CFG_TM_SHIFT) & SEI_CTRL_LATCH_TRAN_CFG_TM_MASK)
#define SEI_CTRL_LATCH_TRAN_CFG_TM_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_TRAN_CFG_TM_MASK) >> SEI_CTRL_LATCH_TRAN_CFG_TM_SHIFT)

/*
 * CFG_TXD (RW)
 *
 * data send
 * 0: high
 * 1: low
 * 2: rise
 * 3: fall
 */
#define SEI_CTRL_LATCH_TRAN_CFG_TXD_MASK (0x3000U)
#define SEI_CTRL_LATCH_TRAN_CFG_TXD_SHIFT (12U)
#define SEI_CTRL_LATCH_TRAN_CFG_TXD_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_TRAN_CFG_TXD_SHIFT) & SEI_CTRL_LATCH_TRAN_CFG_TXD_MASK)
#define SEI_CTRL_LATCH_TRAN_CFG_TXD_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_TRAN_CFG_TXD_MASK) >> SEI_CTRL_LATCH_TRAN_CFG_TXD_SHIFT)

/*
 * CFG_CLK (RW)
 *
 * clock(only support master mode)
 * 0: high
 * 1: low
 * 2: rise
 * 3: fall
 */
#define SEI_CTRL_LATCH_TRAN_CFG_CLK_MASK (0xC00U)
#define SEI_CTRL_LATCH_TRAN_CFG_CLK_SHIFT (10U)
#define SEI_CTRL_LATCH_TRAN_CFG_CLK_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_TRAN_CFG_CLK_SHIFT) & SEI_CTRL_LATCH_TRAN_CFG_CLK_MASK)
#define SEI_CTRL_LATCH_TRAN_CFG_CLK_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_TRAN_CFG_CLK_MASK) >> SEI_CTRL_LATCH_TRAN_CFG_CLK_SHIFT)

/*
 * CFG_PTR (RW)
 *
 * pointer
 * 0: match
 * 1: not match
 * 2:entry
 * 3:leave
 */
#define SEI_CTRL_LATCH_TRAN_CFG_PTR_MASK (0x300U)
#define SEI_CTRL_LATCH_TRAN_CFG_PTR_SHIFT (8U)
#define SEI_CTRL_LATCH_TRAN_CFG_PTR_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_TRAN_CFG_PTR_SHIFT) & SEI_CTRL_LATCH_TRAN_CFG_PTR_MASK)
#define SEI_CTRL_LATCH_TRAN_CFG_PTR_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_TRAN_CFG_PTR_MASK) >> SEI_CTRL_LATCH_TRAN_CFG_PTR_SHIFT)

/*
 * OV_TM (RW)
 *
 * override timeout check
 */
#define SEI_CTRL_LATCH_TRAN_OV_TM_MASK (0x10U)
#define SEI_CTRL_LATCH_TRAN_OV_TM_SHIFT (4U)
#define SEI_CTRL_LATCH_TRAN_OV_TM_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_TRAN_OV_TM_SHIFT) & SEI_CTRL_LATCH_TRAN_OV_TM_MASK)
#define SEI_CTRL_LATCH_TRAN_OV_TM_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_TRAN_OV_TM_MASK) >> SEI_CTRL_LATCH_TRAN_OV_TM_SHIFT)

/*
 * OV_TXD (RW)
 *
 * override TX data check
 */
#define SEI_CTRL_LATCH_TRAN_OV_TXD_MASK (0x4U)
#define SEI_CTRL_LATCH_TRAN_OV_TXD_SHIFT (2U)
#define SEI_CTRL_LATCH_TRAN_OV_TXD_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_TRAN_OV_TXD_SHIFT) & SEI_CTRL_LATCH_TRAN_OV_TXD_MASK)
#define SEI_CTRL_LATCH_TRAN_OV_TXD_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_TRAN_OV_TXD_MASK) >> SEI_CTRL_LATCH_TRAN_OV_TXD_SHIFT)

/*
 * OV_CLK (RW)
 *
 * override clock check
 */
#define SEI_CTRL_LATCH_TRAN_OV_CLK_MASK (0x2U)
#define SEI_CTRL_LATCH_TRAN_OV_CLK_SHIFT (1U)
#define SEI_CTRL_LATCH_TRAN_OV_CLK_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_TRAN_OV_CLK_SHIFT) & SEI_CTRL_LATCH_TRAN_OV_CLK_MASK)
#define SEI_CTRL_LATCH_TRAN_OV_CLK_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_TRAN_OV_CLK_MASK) >> SEI_CTRL_LATCH_TRAN_OV_CLK_SHIFT)

/*
 * OV_PTR (RW)
 *
 * override pointer check
 */
#define SEI_CTRL_LATCH_TRAN_OV_PTR_MASK (0x1U)
#define SEI_CTRL_LATCH_TRAN_OV_PTR_SHIFT (0U)
#define SEI_CTRL_LATCH_TRAN_OV_PTR_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_TRAN_OV_PTR_SHIFT) & SEI_CTRL_LATCH_TRAN_OV_PTR_MASK)
#define SEI_CTRL_LATCH_TRAN_OV_PTR_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_TRAN_OV_PTR_MASK) >> SEI_CTRL_LATCH_TRAN_OV_PTR_SHIFT)

/* Bitfield definition for register of struct array CTRL: CFG */
/*
 * EN (RW)
 *
 * Enable latch
 * 0: disable
 * 1: enable
 */
#define SEI_CTRL_LATCH_CFG_EN_MASK (0x80000000UL)
#define SEI_CTRL_LATCH_CFG_EN_SHIFT (31U)
#define SEI_CTRL_LATCH_CFG_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_CFG_EN_SHIFT) & SEI_CTRL_LATCH_CFG_EN_MASK)
#define SEI_CTRL_LATCH_CFG_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_CFG_EN_MASK) >> SEI_CTRL_LATCH_CFG_EN_SHIFT)

/*
 * SELECT (RW)
 *
 * Output select
 * 0: state0-state1
 * 1: state1-state2
 * 2: state2-state3
 * 3: state3-state0
 */
#define SEI_CTRL_LATCH_CFG_SELECT_MASK (0x7000000UL)
#define SEI_CTRL_LATCH_CFG_SELECT_SHIFT (24U)
#define SEI_CTRL_LATCH_CFG_SELECT_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_CFG_SELECT_SHIFT) & SEI_CTRL_LATCH_CFG_SELECT_MASK)
#define SEI_CTRL_LATCH_CFG_SELECT_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_CFG_SELECT_MASK) >> SEI_CTRL_LATCH_CFG_SELECT_SHIFT)

/*
 * DELAY (RW)
 *
 * Delay in system clock cycle, for state transition
 */
#define SEI_CTRL_LATCH_CFG_DELAY_MASK (0xFFFFU)
#define SEI_CTRL_LATCH_CFG_DELAY_SHIFT (0U)
#define SEI_CTRL_LATCH_CFG_DELAY_SET(x) (((uint32_t)(x) << SEI_CTRL_LATCH_CFG_DELAY_SHIFT) & SEI_CTRL_LATCH_CFG_DELAY_MASK)
#define SEI_CTRL_LATCH_CFG_DELAY_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_CFG_DELAY_MASK) >> SEI_CTRL_LATCH_CFG_DELAY_SHIFT)

/* Bitfield definition for register of struct array CTRL: TIME */
/*
 * LAT_TIME (RO)
 *
 * Latch time
 */
#define SEI_CTRL_LATCH_TIME_LAT_TIME_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_LATCH_TIME_LAT_TIME_SHIFT (0U)
#define SEI_CTRL_LATCH_TIME_LAT_TIME_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_TIME_LAT_TIME_MASK) >> SEI_CTRL_LATCH_TIME_LAT_TIME_SHIFT)

/* Bitfield definition for register of struct array CTRL: STS */
/*
 * STATE (RO)
 *
 * State
 */
#define SEI_CTRL_LATCH_STS_STATE_MASK (0x7000000UL)
#define SEI_CTRL_LATCH_STS_STATE_SHIFT (24U)
#define SEI_CTRL_LATCH_STS_STATE_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_STS_STATE_MASK) >> SEI_CTRL_LATCH_STS_STATE_SHIFT)

/*
 * LAT_CNT (RO)
 *
 * Latch counter
 */
#define SEI_CTRL_LATCH_STS_LAT_CNT_MASK (0xFFFFU)
#define SEI_CTRL_LATCH_STS_LAT_CNT_SHIFT (0U)
#define SEI_CTRL_LATCH_STS_LAT_CNT_GET(x) (((uint32_t)(x) & SEI_CTRL_LATCH_STS_LAT_CNT_MASK) >> SEI_CTRL_LATCH_STS_LAT_CNT_SHIFT)

/* Bitfield definition for register of struct array CTRL: SMP_EN */
/*
 * ACC_EN (RW)
 *
 * Position include acceleration
 * 0: use acceleration from sample override acceleration register
 * 1: use acceleration from motor group
 */
#define SEI_CTRL_POS_SMP_EN_ACC_EN_MASK (0x80000000UL)
#define SEI_CTRL_POS_SMP_EN_ACC_EN_SHIFT (31U)
#define SEI_CTRL_POS_SMP_EN_ACC_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_EN_ACC_EN_SHIFT) & SEI_CTRL_POS_SMP_EN_ACC_EN_MASK)
#define SEI_CTRL_POS_SMP_EN_ACC_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_EN_ACC_EN_MASK) >> SEI_CTRL_POS_SMP_EN_ACC_EN_SHIFT)

/*
 * ACC_SEL (RW)
 *
 * Data register for acceleration transfer
 */
#define SEI_CTRL_POS_SMP_EN_ACC_SEL_MASK (0x1F000000UL)
#define SEI_CTRL_POS_SMP_EN_ACC_SEL_SHIFT (24U)
#define SEI_CTRL_POS_SMP_EN_ACC_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_EN_ACC_SEL_SHIFT) & SEI_CTRL_POS_SMP_EN_ACC_SEL_MASK)
#define SEI_CTRL_POS_SMP_EN_ACC_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_EN_ACC_SEL_MASK) >> SEI_CTRL_POS_SMP_EN_ACC_SEL_SHIFT)

/*
 * SPD_EN (RW)
 *
 * Position include speed
 * 0: use speed from sample override speed register
 * 1: use speed from motor group
 */
#define SEI_CTRL_POS_SMP_EN_SPD_EN_MASK (0x800000UL)
#define SEI_CTRL_POS_SMP_EN_SPD_EN_SHIFT (23U)
#define SEI_CTRL_POS_SMP_EN_SPD_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_EN_SPD_EN_SHIFT) & SEI_CTRL_POS_SMP_EN_SPD_EN_MASK)
#define SEI_CTRL_POS_SMP_EN_SPD_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_EN_SPD_EN_MASK) >> SEI_CTRL_POS_SMP_EN_SPD_EN_SHIFT)

/*
 * SPD_SEL (RW)
 *
 * Data register for speed transfer
 */
#define SEI_CTRL_POS_SMP_EN_SPD_SEL_MASK (0x1F0000UL)
#define SEI_CTRL_POS_SMP_EN_SPD_SEL_SHIFT (16U)
#define SEI_CTRL_POS_SMP_EN_SPD_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_EN_SPD_SEL_SHIFT) & SEI_CTRL_POS_SMP_EN_SPD_SEL_MASK)
#define SEI_CTRL_POS_SMP_EN_SPD_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_EN_SPD_SEL_MASK) >> SEI_CTRL_POS_SMP_EN_SPD_SEL_SHIFT)

/*
 * REV_EN (RW)
 *
 * Position include revolution
 * 0: use revolution from sample override revolution register
 * 1: use revolution  from motor group
 */
#define SEI_CTRL_POS_SMP_EN_REV_EN_MASK (0x8000U)
#define SEI_CTRL_POS_SMP_EN_REV_EN_SHIFT (15U)
#define SEI_CTRL_POS_SMP_EN_REV_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_EN_REV_EN_SHIFT) & SEI_CTRL_POS_SMP_EN_REV_EN_MASK)
#define SEI_CTRL_POS_SMP_EN_REV_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_EN_REV_EN_MASK) >> SEI_CTRL_POS_SMP_EN_REV_EN_SHIFT)

/*
 * REV_SEL (RW)
 *
 * Data register for revolution transfer
 */
#define SEI_CTRL_POS_SMP_EN_REV_SEL_MASK (0x1F00U)
#define SEI_CTRL_POS_SMP_EN_REV_SEL_SHIFT (8U)
#define SEI_CTRL_POS_SMP_EN_REV_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_EN_REV_SEL_SHIFT) & SEI_CTRL_POS_SMP_EN_REV_SEL_MASK)
#define SEI_CTRL_POS_SMP_EN_REV_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_EN_REV_SEL_MASK) >> SEI_CTRL_POS_SMP_EN_REV_SEL_SHIFT)

/*
 * POS_EN (RW)
 *
 * Position include position
 * 0: use position from sample override position register
 * 1: use position from motor group
 */
#define SEI_CTRL_POS_SMP_EN_POS_EN_MASK (0x80U)
#define SEI_CTRL_POS_SMP_EN_POS_EN_SHIFT (7U)
#define SEI_CTRL_POS_SMP_EN_POS_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_EN_POS_EN_SHIFT) & SEI_CTRL_POS_SMP_EN_POS_EN_MASK)
#define SEI_CTRL_POS_SMP_EN_POS_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_EN_POS_EN_MASK) >> SEI_CTRL_POS_SMP_EN_POS_EN_SHIFT)

/*
 * POS_SEL (RW)
 *
 * Data register for position transfer
 */
#define SEI_CTRL_POS_SMP_EN_POS_SEL_MASK (0x1FU)
#define SEI_CTRL_POS_SMP_EN_POS_SEL_SHIFT (0U)
#define SEI_CTRL_POS_SMP_EN_POS_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_EN_POS_SEL_SHIFT) & SEI_CTRL_POS_SMP_EN_POS_SEL_MASK)
#define SEI_CTRL_POS_SMP_EN_POS_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_EN_POS_SEL_MASK) >> SEI_CTRL_POS_SMP_EN_POS_SEL_SHIFT)

/* Bitfield definition for register of struct array CTRL: SMP_CFG */
/*
 * ONCE (RW)
 *
 * Sample one time
 * 0: Sample during windows time
 * 1: Close sample window after first sample
 */
#define SEI_CTRL_POS_SMP_CFG_ONCE_MASK (0x1000000UL)
#define SEI_CTRL_POS_SMP_CFG_ONCE_SHIFT (24U)
#define SEI_CTRL_POS_SMP_CFG_ONCE_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_CFG_ONCE_SHIFT) & SEI_CTRL_POS_SMP_CFG_ONCE_MASK)
#define SEI_CTRL_POS_SMP_CFG_ONCE_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_CFG_ONCE_MASK) >> SEI_CTRL_POS_SMP_CFG_ONCE_SHIFT)

/*
 * LAT_SEL (RW)
 *
 * Latch selection
 * 0: latch 0
 * 1: latch 1
 * 2: latch 2
 * 3: latch 3
 */
#define SEI_CTRL_POS_SMP_CFG_LAT_SEL_MASK (0x30000UL)
#define SEI_CTRL_POS_SMP_CFG_LAT_SEL_SHIFT (16U)
#define SEI_CTRL_POS_SMP_CFG_LAT_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_CFG_LAT_SEL_SHIFT) & SEI_CTRL_POS_SMP_CFG_LAT_SEL_MASK)
#define SEI_CTRL_POS_SMP_CFG_LAT_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_CFG_LAT_SEL_MASK) >> SEI_CTRL_POS_SMP_CFG_LAT_SEL_SHIFT)

/*
 * WINDOW (RW)
 *
 * Sample window, in clock cycle
 */
#define SEI_CTRL_POS_SMP_CFG_WINDOW_MASK (0xFFFFU)
#define SEI_CTRL_POS_SMP_CFG_WINDOW_SHIFT (0U)
#define SEI_CTRL_POS_SMP_CFG_WINDOW_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_CFG_WINDOW_SHIFT) & SEI_CTRL_POS_SMP_CFG_WINDOW_MASK)
#define SEI_CTRL_POS_SMP_CFG_WINDOW_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_CFG_WINDOW_MASK) >> SEI_CTRL_POS_SMP_CFG_WINDOW_SHIFT)

/* Bitfield definition for register of struct array CTRL: SMP_DAT */
/*
 * DAT_SEL (RW)
 *
 * Data register sampled, each bit represent a data register
 */
#define SEI_CTRL_POS_SMP_DAT_DAT_SEL_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_SMP_DAT_DAT_SEL_SHIFT (0U)
#define SEI_CTRL_POS_SMP_DAT_DAT_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_DAT_DAT_SEL_SHIFT) & SEI_CTRL_POS_SMP_DAT_DAT_SEL_MASK)
#define SEI_CTRL_POS_SMP_DAT_DAT_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_DAT_DAT_SEL_MASK) >> SEI_CTRL_POS_SMP_DAT_DAT_SEL_SHIFT)

/* Bitfield definition for register of struct array CTRL: SMP_POS */
/*
 * POS (RW)
 *
 * Sample override position
 */
#define SEI_CTRL_POS_SMP_POS_POS_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_SMP_POS_POS_SHIFT (0U)
#define SEI_CTRL_POS_SMP_POS_POS_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_POS_POS_SHIFT) & SEI_CTRL_POS_SMP_POS_POS_MASK)
#define SEI_CTRL_POS_SMP_POS_POS_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_POS_POS_MASK) >> SEI_CTRL_POS_SMP_POS_POS_SHIFT)

/* Bitfield definition for register of struct array CTRL: SMP_REV */
/*
 * REV (RW)
 *
 * Sample override revolution
 */
#define SEI_CTRL_POS_SMP_REV_REV_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_SMP_REV_REV_SHIFT (0U)
#define SEI_CTRL_POS_SMP_REV_REV_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_REV_REV_SHIFT) & SEI_CTRL_POS_SMP_REV_REV_MASK)
#define SEI_CTRL_POS_SMP_REV_REV_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_REV_REV_MASK) >> SEI_CTRL_POS_SMP_REV_REV_SHIFT)

/* Bitfield definition for register of struct array CTRL: SMP_SPD */
/*
 * SPD (RW)
 *
 * Sample override speed
 */
#define SEI_CTRL_POS_SMP_SPD_SPD_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_SMP_SPD_SPD_SHIFT (0U)
#define SEI_CTRL_POS_SMP_SPD_SPD_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_SPD_SPD_SHIFT) & SEI_CTRL_POS_SMP_SPD_SPD_MASK)
#define SEI_CTRL_POS_SMP_SPD_SPD_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_SPD_SPD_MASK) >> SEI_CTRL_POS_SMP_SPD_SPD_SHIFT)

/* Bitfield definition for register of struct array CTRL: SMP_ACC */
/*
 * ACC (RW)
 *
 * Sample override accelerate
 */
#define SEI_CTRL_POS_SMP_ACC_ACC_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_SMP_ACC_ACC_SHIFT (0U)
#define SEI_CTRL_POS_SMP_ACC_ACC_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_SMP_ACC_ACC_SHIFT) & SEI_CTRL_POS_SMP_ACC_ACC_MASK)
#define SEI_CTRL_POS_SMP_ACC_ACC_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_ACC_ACC_MASK) >> SEI_CTRL_POS_SMP_ACC_ACC_SHIFT)

/* Bitfield definition for register of struct array CTRL: UPD_EN */
/*
 * ACC_EN (RW)
 *
 * Position include acceleration
 * 0: use acceleration from update override acceleration register
 * 1: use acceleration from data register
 */
#define SEI_CTRL_POS_UPD_EN_ACC_EN_MASK (0x80000000UL)
#define SEI_CTRL_POS_UPD_EN_ACC_EN_SHIFT (31U)
#define SEI_CTRL_POS_UPD_EN_ACC_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_EN_ACC_EN_SHIFT) & SEI_CTRL_POS_UPD_EN_ACC_EN_MASK)
#define SEI_CTRL_POS_UPD_EN_ACC_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_EN_ACC_EN_MASK) >> SEI_CTRL_POS_UPD_EN_ACC_EN_SHIFT)

/*
 * ACC_SEL (RW)
 *
 * Data register for acceleration transfer
 */
#define SEI_CTRL_POS_UPD_EN_ACC_SEL_MASK (0x1F000000UL)
#define SEI_CTRL_POS_UPD_EN_ACC_SEL_SHIFT (24U)
#define SEI_CTRL_POS_UPD_EN_ACC_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_EN_ACC_SEL_SHIFT) & SEI_CTRL_POS_UPD_EN_ACC_SEL_MASK)
#define SEI_CTRL_POS_UPD_EN_ACC_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_EN_ACC_SEL_MASK) >> SEI_CTRL_POS_UPD_EN_ACC_SEL_SHIFT)

/*
 * SPD_EN (RW)
 *
 * Position include speed
 * 0: use speed from update override speed register
 * 1: use speed from data register
 */
#define SEI_CTRL_POS_UPD_EN_SPD_EN_MASK (0x800000UL)
#define SEI_CTRL_POS_UPD_EN_SPD_EN_SHIFT (23U)
#define SEI_CTRL_POS_UPD_EN_SPD_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_EN_SPD_EN_SHIFT) & SEI_CTRL_POS_UPD_EN_SPD_EN_MASK)
#define SEI_CTRL_POS_UPD_EN_SPD_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_EN_SPD_EN_MASK) >> SEI_CTRL_POS_UPD_EN_SPD_EN_SHIFT)

/*
 * SPD_SEL (RW)
 *
 * Data register for speed transfer
 */
#define SEI_CTRL_POS_UPD_EN_SPD_SEL_MASK (0x1F0000UL)
#define SEI_CTRL_POS_UPD_EN_SPD_SEL_SHIFT (16U)
#define SEI_CTRL_POS_UPD_EN_SPD_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_EN_SPD_SEL_SHIFT) & SEI_CTRL_POS_UPD_EN_SPD_SEL_MASK)
#define SEI_CTRL_POS_UPD_EN_SPD_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_EN_SPD_SEL_MASK) >> SEI_CTRL_POS_UPD_EN_SPD_SEL_SHIFT)

/*
 * REV_EN (RW)
 *
 * Position include revolution
 * 0: use revolution from update override revolution register
 * 1: use revolution from data register
 */
#define SEI_CTRL_POS_UPD_EN_REV_EN_MASK (0x8000U)
#define SEI_CTRL_POS_UPD_EN_REV_EN_SHIFT (15U)
#define SEI_CTRL_POS_UPD_EN_REV_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_EN_REV_EN_SHIFT) & SEI_CTRL_POS_UPD_EN_REV_EN_MASK)
#define SEI_CTRL_POS_UPD_EN_REV_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_EN_REV_EN_MASK) >> SEI_CTRL_POS_UPD_EN_REV_EN_SHIFT)

/*
 * REV_SEL (RW)
 *
 * Data register for revolution transfer
 */
#define SEI_CTRL_POS_UPD_EN_REV_SEL_MASK (0x1F00U)
#define SEI_CTRL_POS_UPD_EN_REV_SEL_SHIFT (8U)
#define SEI_CTRL_POS_UPD_EN_REV_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_EN_REV_SEL_SHIFT) & SEI_CTRL_POS_UPD_EN_REV_SEL_MASK)
#define SEI_CTRL_POS_UPD_EN_REV_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_EN_REV_SEL_MASK) >> SEI_CTRL_POS_UPD_EN_REV_SEL_SHIFT)

/*
 * POS_EN (RW)
 *
 * Position include position
 * 0: use position from update override position register
 * 1: use position from data register
 */
#define SEI_CTRL_POS_UPD_EN_POS_EN_MASK (0x80U)
#define SEI_CTRL_POS_UPD_EN_POS_EN_SHIFT (7U)
#define SEI_CTRL_POS_UPD_EN_POS_EN_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_EN_POS_EN_SHIFT) & SEI_CTRL_POS_UPD_EN_POS_EN_MASK)
#define SEI_CTRL_POS_UPD_EN_POS_EN_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_EN_POS_EN_MASK) >> SEI_CTRL_POS_UPD_EN_POS_EN_SHIFT)

/*
 * POS_SEL (RW)
 *
 * Data register for position transfer
 */
#define SEI_CTRL_POS_UPD_EN_POS_SEL_MASK (0x1FU)
#define SEI_CTRL_POS_UPD_EN_POS_SEL_SHIFT (0U)
#define SEI_CTRL_POS_UPD_EN_POS_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_EN_POS_SEL_SHIFT) & SEI_CTRL_POS_UPD_EN_POS_SEL_MASK)
#define SEI_CTRL_POS_UPD_EN_POS_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_EN_POS_SEL_MASK) >> SEI_CTRL_POS_UPD_EN_POS_SEL_SHIFT)

/* Bitfield definition for register of struct array CTRL: UPD_CFG */
/*
 * TIME_OVRD (RW)
 *
 * Use override time
 * 0: use time sample from motor group
 * 1: use override time
 */
#define SEI_CTRL_POS_UPD_CFG_TIME_OVRD_MASK (0x80000000UL)
#define SEI_CTRL_POS_UPD_CFG_TIME_OVRD_SHIFT (31U)
#define SEI_CTRL_POS_UPD_CFG_TIME_OVRD_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_CFG_TIME_OVRD_SHIFT) & SEI_CTRL_POS_UPD_CFG_TIME_OVRD_MASK)
#define SEI_CTRL_POS_UPD_CFG_TIME_OVRD_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_CFG_TIME_OVRD_MASK) >> SEI_CTRL_POS_UPD_CFG_TIME_OVRD_SHIFT)

/*
 * ONERR (RW)
 *
 * Sample one time
 * 0: Sample during windows time
 * 1: Close sample window after first sample
 */
#define SEI_CTRL_POS_UPD_CFG_ONERR_MASK (0x1000000UL)
#define SEI_CTRL_POS_UPD_CFG_ONERR_SHIFT (24U)
#define SEI_CTRL_POS_UPD_CFG_ONERR_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_CFG_ONERR_SHIFT) & SEI_CTRL_POS_UPD_CFG_ONERR_MASK)
#define SEI_CTRL_POS_UPD_CFG_ONERR_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_CFG_ONERR_MASK) >> SEI_CTRL_POS_UPD_CFG_ONERR_SHIFT)

/*
 * LAT_SEL (RW)
 *
 * Latch selection
 * 0: latch 0
 * 1: latch 1
 * 2: latch 2
 * 3: latch 3
 */
#define SEI_CTRL_POS_UPD_CFG_LAT_SEL_MASK (0x30000UL)
#define SEI_CTRL_POS_UPD_CFG_LAT_SEL_SHIFT (16U)
#define SEI_CTRL_POS_UPD_CFG_LAT_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_CFG_LAT_SEL_SHIFT) & SEI_CTRL_POS_UPD_CFG_LAT_SEL_MASK)
#define SEI_CTRL_POS_UPD_CFG_LAT_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_CFG_LAT_SEL_MASK) >> SEI_CTRL_POS_UPD_CFG_LAT_SEL_SHIFT)

/* Bitfield definition for register of struct array CTRL: UPD_DAT */
/*
 * DAT_SEL (RW)
 *
 * Data register sampled, each bit represent a data register
 */
#define SEI_CTRL_POS_UPD_DAT_DAT_SEL_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_UPD_DAT_DAT_SEL_SHIFT (0U)
#define SEI_CTRL_POS_UPD_DAT_DAT_SEL_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_DAT_DAT_SEL_SHIFT) & SEI_CTRL_POS_UPD_DAT_DAT_SEL_MASK)
#define SEI_CTRL_POS_UPD_DAT_DAT_SEL_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_DAT_DAT_SEL_MASK) >> SEI_CTRL_POS_UPD_DAT_DAT_SEL_SHIFT)

/* Bitfield definition for register of struct array CTRL: UPD_TIME */
/*
 * TIME (RW)
 *
 * Update override time
 */
#define SEI_CTRL_POS_UPD_TIME_TIME_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_UPD_TIME_TIME_SHIFT (0U)
#define SEI_CTRL_POS_UPD_TIME_TIME_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_TIME_TIME_SHIFT) & SEI_CTRL_POS_UPD_TIME_TIME_MASK)
#define SEI_CTRL_POS_UPD_TIME_TIME_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_TIME_TIME_MASK) >> SEI_CTRL_POS_UPD_TIME_TIME_SHIFT)

/* Bitfield definition for register of struct array CTRL: UPD_POS */
/*
 * POS (RW)
 *
 * Update override position
 */
#define SEI_CTRL_POS_UPD_POS_POS_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_UPD_POS_POS_SHIFT (0U)
#define SEI_CTRL_POS_UPD_POS_POS_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_POS_POS_SHIFT) & SEI_CTRL_POS_UPD_POS_POS_MASK)
#define SEI_CTRL_POS_UPD_POS_POS_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_POS_POS_MASK) >> SEI_CTRL_POS_UPD_POS_POS_SHIFT)

/* Bitfield definition for register of struct array CTRL: UPD_REV */
/*
 * REV (RW)
 *
 * Update override revolution
 */
#define SEI_CTRL_POS_UPD_REV_REV_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_UPD_REV_REV_SHIFT (0U)
#define SEI_CTRL_POS_UPD_REV_REV_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_REV_REV_SHIFT) & SEI_CTRL_POS_UPD_REV_REV_MASK)
#define SEI_CTRL_POS_UPD_REV_REV_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_REV_REV_MASK) >> SEI_CTRL_POS_UPD_REV_REV_SHIFT)

/* Bitfield definition for register of struct array CTRL: UPD_SPD */
/*
 * SPD (RW)
 *
 * Update override speed
 */
#define SEI_CTRL_POS_UPD_SPD_SPD_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_UPD_SPD_SPD_SHIFT (0U)
#define SEI_CTRL_POS_UPD_SPD_SPD_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_SPD_SPD_SHIFT) & SEI_CTRL_POS_UPD_SPD_SPD_MASK)
#define SEI_CTRL_POS_UPD_SPD_SPD_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_SPD_SPD_MASK) >> SEI_CTRL_POS_UPD_SPD_SPD_SHIFT)

/* Bitfield definition for register of struct array CTRL: UPD_ACC */
/*
 * ACC (RW)
 *
 * Update override accelerate
 */
#define SEI_CTRL_POS_UPD_ACC_ACC_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_UPD_ACC_ACC_SHIFT (0U)
#define SEI_CTRL_POS_UPD_ACC_ACC_SET(x) (((uint32_t)(x) << SEI_CTRL_POS_UPD_ACC_ACC_SHIFT) & SEI_CTRL_POS_UPD_ACC_ACC_MASK)
#define SEI_CTRL_POS_UPD_ACC_ACC_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_ACC_ACC_MASK) >> SEI_CTRL_POS_UPD_ACC_ACC_SHIFT)

/* Bitfield definition for register of struct array CTRL: SMP_VAL */
/*
 * ACC (RO)
 *
 * Position include acceleration
 */
#define SEI_CTRL_POS_SMP_VAL_ACC_MASK (0x80000000UL)
#define SEI_CTRL_POS_SMP_VAL_ACC_SHIFT (31U)
#define SEI_CTRL_POS_SMP_VAL_ACC_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_VAL_ACC_MASK) >> SEI_CTRL_POS_SMP_VAL_ACC_SHIFT)

/*
 * SPD (RO)
 *
 * Position include speed
 */
#define SEI_CTRL_POS_SMP_VAL_SPD_MASK (0x800000UL)
#define SEI_CTRL_POS_SMP_VAL_SPD_SHIFT (23U)
#define SEI_CTRL_POS_SMP_VAL_SPD_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_VAL_SPD_MASK) >> SEI_CTRL_POS_SMP_VAL_SPD_SHIFT)

/*
 * REV (RO)
 *
 * Position include revolution
 */
#define SEI_CTRL_POS_SMP_VAL_REV_MASK (0x8000U)
#define SEI_CTRL_POS_SMP_VAL_REV_SHIFT (15U)
#define SEI_CTRL_POS_SMP_VAL_REV_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_VAL_REV_MASK) >> SEI_CTRL_POS_SMP_VAL_REV_SHIFT)

/*
 * POS (RO)
 *
 * Position include position
 */
#define SEI_CTRL_POS_SMP_VAL_POS_MASK (0x80U)
#define SEI_CTRL_POS_SMP_VAL_POS_SHIFT (7U)
#define SEI_CTRL_POS_SMP_VAL_POS_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_VAL_POS_MASK) >> SEI_CTRL_POS_SMP_VAL_POS_SHIFT)

/* Bitfield definition for register of struct array CTRL: SMP_STS */
/*
 * OCCUR (RO)
 *
 * Sample occured
 * 0: Sample not happened
 * 1: Sample occured
 */
#define SEI_CTRL_POS_SMP_STS_OCCUR_MASK (0x1000000UL)
#define SEI_CTRL_POS_SMP_STS_OCCUR_SHIFT (24U)
#define SEI_CTRL_POS_SMP_STS_OCCUR_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_STS_OCCUR_MASK) >> SEI_CTRL_POS_SMP_STS_OCCUR_SHIFT)

/*
 * WIN_CNT (RO)
 *
 * Sample window counter
 */
#define SEI_CTRL_POS_SMP_STS_WIN_CNT_MASK (0xFFFFU)
#define SEI_CTRL_POS_SMP_STS_WIN_CNT_SHIFT (0U)
#define SEI_CTRL_POS_SMP_STS_WIN_CNT_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SMP_STS_WIN_CNT_MASK) >> SEI_CTRL_POS_SMP_STS_WIN_CNT_SHIFT)

/* Bitfield definition for register of struct array CTRL: TIME_IN */
/*
 * TIME (RO)
 *
 * input time
 */
#define SEI_CTRL_POS_TIME_IN_TIME_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_TIME_IN_TIME_SHIFT (0U)
#define SEI_CTRL_POS_TIME_IN_TIME_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_TIME_IN_TIME_MASK) >> SEI_CTRL_POS_TIME_IN_TIME_SHIFT)

/* Bitfield definition for register of struct array CTRL: POS_IN */
/*
 * POS (RO)
 *
 * Input position
 */
#define SEI_CTRL_POS_POS_IN_POS_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_POS_IN_POS_SHIFT (0U)
#define SEI_CTRL_POS_POS_IN_POS_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_POS_IN_POS_MASK) >> SEI_CTRL_POS_POS_IN_POS_SHIFT)

/* Bitfield definition for register of struct array CTRL: REV_IN */
/*
 * REV (RO)
 *
 * Input revolution
 */
#define SEI_CTRL_POS_REV_IN_REV_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_REV_IN_REV_SHIFT (0U)
#define SEI_CTRL_POS_REV_IN_REV_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_REV_IN_REV_MASK) >> SEI_CTRL_POS_REV_IN_REV_SHIFT)

/* Bitfield definition for register of struct array CTRL: SPD_IN */
/*
 * SPD (RO)
 *
 * Input speed
 */
#define SEI_CTRL_POS_SPD_IN_SPD_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_SPD_IN_SPD_SHIFT (0U)
#define SEI_CTRL_POS_SPD_IN_SPD_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_SPD_IN_SPD_MASK) >> SEI_CTRL_POS_SPD_IN_SPD_SHIFT)

/* Bitfield definition for register of struct array CTRL: ACC_IN */
/*
 * ACC (RO)
 *
 * Input accelerate
 */
#define SEI_CTRL_POS_ACC_IN_ACC_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_POS_ACC_IN_ACC_SHIFT (0U)
#define SEI_CTRL_POS_ACC_IN_ACC_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_ACC_IN_ACC_MASK) >> SEI_CTRL_POS_ACC_IN_ACC_SHIFT)

/* Bitfield definition for register of struct array CTRL: UPD_STS */
/*
 * UPD_ERR (RO)
 *
 * Update  error
 * 0: data receive normally
 * 1: data receive error
 */
#define SEI_CTRL_POS_UPD_STS_UPD_ERR_MASK (0x1000000UL)
#define SEI_CTRL_POS_UPD_STS_UPD_ERR_SHIFT (24U)
#define SEI_CTRL_POS_UPD_STS_UPD_ERR_GET(x) (((uint32_t)(x) & SEI_CTRL_POS_UPD_STS_UPD_ERR_MASK) >> SEI_CTRL_POS_UPD_STS_UPD_ERR_SHIFT)

/* Bitfield definition for register of struct array CTRL: INT_EN */
/*
 * TRG_ERR3 (RW)
 *
 * Trigger3 failed
 */
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR3_MASK (0x80000000UL)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR3_SHIFT (31U)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR3_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_TRG_ERR3_SHIFT) & SEI_CTRL_IRQ_INT_EN_TRG_ERR3_MASK)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR3_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_TRG_ERR3_MASK) >> SEI_CTRL_IRQ_INT_EN_TRG_ERR3_SHIFT)

/*
 * TRG_ERR2 (RW)
 *
 * Trigger2 failed
 */
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR2_MASK (0x40000000UL)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR2_SHIFT (30U)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR2_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_TRG_ERR2_SHIFT) & SEI_CTRL_IRQ_INT_EN_TRG_ERR2_MASK)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR2_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_TRG_ERR2_MASK) >> SEI_CTRL_IRQ_INT_EN_TRG_ERR2_SHIFT)

/*
 * TRG_ERR1 (RW)
 *
 * Trigger1 failed
 */
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR1_MASK (0x20000000UL)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR1_SHIFT (29U)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR1_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_TRG_ERR1_SHIFT) & SEI_CTRL_IRQ_INT_EN_TRG_ERR1_MASK)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR1_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_TRG_ERR1_MASK) >> SEI_CTRL_IRQ_INT_EN_TRG_ERR1_SHIFT)

/*
 * TRG_ERR0 (RW)
 *
 * Trigger0 failed
 */
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR0_MASK (0x10000000UL)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR0_SHIFT (28U)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR0_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_TRG_ERR0_SHIFT) & SEI_CTRL_IRQ_INT_EN_TRG_ERR0_MASK)
#define SEI_CTRL_IRQ_INT_EN_TRG_ERR0_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_TRG_ERR0_MASK) >> SEI_CTRL_IRQ_INT_EN_TRG_ERR0_SHIFT)

/*
 * TRIGER3 (RW)
 *
 * Trigger3
 */
#define SEI_CTRL_IRQ_INT_EN_TRIGER3_MASK (0x8000000UL)
#define SEI_CTRL_IRQ_INT_EN_TRIGER3_SHIFT (27U)
#define SEI_CTRL_IRQ_INT_EN_TRIGER3_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_TRIGER3_SHIFT) & SEI_CTRL_IRQ_INT_EN_TRIGER3_MASK)
#define SEI_CTRL_IRQ_INT_EN_TRIGER3_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_TRIGER3_MASK) >> SEI_CTRL_IRQ_INT_EN_TRIGER3_SHIFT)

/*
 * TRIGER2 (RW)
 *
 * Trigger2
 */
#define SEI_CTRL_IRQ_INT_EN_TRIGER2_MASK (0x4000000UL)
#define SEI_CTRL_IRQ_INT_EN_TRIGER2_SHIFT (26U)
#define SEI_CTRL_IRQ_INT_EN_TRIGER2_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_TRIGER2_SHIFT) & SEI_CTRL_IRQ_INT_EN_TRIGER2_MASK)
#define SEI_CTRL_IRQ_INT_EN_TRIGER2_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_TRIGER2_MASK) >> SEI_CTRL_IRQ_INT_EN_TRIGER2_SHIFT)

/*
 * TRIGER1 (RW)
 *
 * Trigger1
 */
#define SEI_CTRL_IRQ_INT_EN_TRIGER1_MASK (0x2000000UL)
#define SEI_CTRL_IRQ_INT_EN_TRIGER1_SHIFT (25U)
#define SEI_CTRL_IRQ_INT_EN_TRIGER1_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_TRIGER1_SHIFT) & SEI_CTRL_IRQ_INT_EN_TRIGER1_MASK)
#define SEI_CTRL_IRQ_INT_EN_TRIGER1_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_TRIGER1_MASK) >> SEI_CTRL_IRQ_INT_EN_TRIGER1_SHIFT)

/*
 * TRIGER0 (RW)
 *
 * Trigger0
 */
#define SEI_CTRL_IRQ_INT_EN_TRIGER0_MASK (0x1000000UL)
#define SEI_CTRL_IRQ_INT_EN_TRIGER0_SHIFT (24U)
#define SEI_CTRL_IRQ_INT_EN_TRIGER0_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_TRIGER0_SHIFT) & SEI_CTRL_IRQ_INT_EN_TRIGER0_MASK)
#define SEI_CTRL_IRQ_INT_EN_TRIGER0_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_TRIGER0_MASK) >> SEI_CTRL_IRQ_INT_EN_TRIGER0_SHIFT)

/*
 * SMP_ERR (RW)
 *
 * Sample error
 */
#define SEI_CTRL_IRQ_INT_EN_SMP_ERR_MASK (0x100000UL)
#define SEI_CTRL_IRQ_INT_EN_SMP_ERR_SHIFT (20U)
#define SEI_CTRL_IRQ_INT_EN_SMP_ERR_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_SMP_ERR_SHIFT) & SEI_CTRL_IRQ_INT_EN_SMP_ERR_MASK)
#define SEI_CTRL_IRQ_INT_EN_SMP_ERR_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_SMP_ERR_MASK) >> SEI_CTRL_IRQ_INT_EN_SMP_ERR_SHIFT)

/*
 * LATCH3 (RW)
 *
 * Latch3
 */
#define SEI_CTRL_IRQ_INT_EN_LATCH3_MASK (0x80000UL)
#define SEI_CTRL_IRQ_INT_EN_LATCH3_SHIFT (19U)
#define SEI_CTRL_IRQ_INT_EN_LATCH3_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_LATCH3_SHIFT) & SEI_CTRL_IRQ_INT_EN_LATCH3_MASK)
#define SEI_CTRL_IRQ_INT_EN_LATCH3_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_LATCH3_MASK) >> SEI_CTRL_IRQ_INT_EN_LATCH3_SHIFT)

/*
 * LATCH2 (RW)
 *
 * Latch2
 */
#define SEI_CTRL_IRQ_INT_EN_LATCH2_MASK (0x40000UL)
#define SEI_CTRL_IRQ_INT_EN_LATCH2_SHIFT (18U)
#define SEI_CTRL_IRQ_INT_EN_LATCH2_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_LATCH2_SHIFT) & SEI_CTRL_IRQ_INT_EN_LATCH2_MASK)
#define SEI_CTRL_IRQ_INT_EN_LATCH2_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_LATCH2_MASK) >> SEI_CTRL_IRQ_INT_EN_LATCH2_SHIFT)

/*
 * LATCH1 (RW)
 *
 * Latch1
 */
#define SEI_CTRL_IRQ_INT_EN_LATCH1_MASK (0x20000UL)
#define SEI_CTRL_IRQ_INT_EN_LATCH1_SHIFT (17U)
#define SEI_CTRL_IRQ_INT_EN_LATCH1_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_LATCH1_SHIFT) & SEI_CTRL_IRQ_INT_EN_LATCH1_MASK)
#define SEI_CTRL_IRQ_INT_EN_LATCH1_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_LATCH1_MASK) >> SEI_CTRL_IRQ_INT_EN_LATCH1_SHIFT)

/*
 * LATCH0 (RW)
 *
 * Latch0
 */
#define SEI_CTRL_IRQ_INT_EN_LATCH0_MASK (0x10000UL)
#define SEI_CTRL_IRQ_INT_EN_LATCH0_SHIFT (16U)
#define SEI_CTRL_IRQ_INT_EN_LATCH0_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_LATCH0_SHIFT) & SEI_CTRL_IRQ_INT_EN_LATCH0_MASK)
#define SEI_CTRL_IRQ_INT_EN_LATCH0_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_LATCH0_MASK) >> SEI_CTRL_IRQ_INT_EN_LATCH0_SHIFT)

/*
 * TIMEOUT (RW)
 *
 * Timeout
 */
#define SEI_CTRL_IRQ_INT_EN_TIMEOUT_MASK (0x2000U)
#define SEI_CTRL_IRQ_INT_EN_TIMEOUT_SHIFT (13U)
#define SEI_CTRL_IRQ_INT_EN_TIMEOUT_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_TIMEOUT_SHIFT) & SEI_CTRL_IRQ_INT_EN_TIMEOUT_MASK)
#define SEI_CTRL_IRQ_INT_EN_TIMEOUT_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_TIMEOUT_MASK) >> SEI_CTRL_IRQ_INT_EN_TIMEOUT_SHIFT)

/*
 * TRX_ERR (RW)
 *
 * Transfer error
 */
#define SEI_CTRL_IRQ_INT_EN_TRX_ERR_MASK (0x1000U)
#define SEI_CTRL_IRQ_INT_EN_TRX_ERR_SHIFT (12U)
#define SEI_CTRL_IRQ_INT_EN_TRX_ERR_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_TRX_ERR_SHIFT) & SEI_CTRL_IRQ_INT_EN_TRX_ERR_MASK)
#define SEI_CTRL_IRQ_INT_EN_TRX_ERR_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_TRX_ERR_MASK) >> SEI_CTRL_IRQ_INT_EN_TRX_ERR_SHIFT)

/*
 * INSTR1_END (RW)
 *
 * Instruction 1 end
 */
#define SEI_CTRL_IRQ_INT_EN_INSTR1_END_MASK (0x800U)
#define SEI_CTRL_IRQ_INT_EN_INSTR1_END_SHIFT (11U)
#define SEI_CTRL_IRQ_INT_EN_INSTR1_END_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_INSTR1_END_SHIFT) & SEI_CTRL_IRQ_INT_EN_INSTR1_END_MASK)
#define SEI_CTRL_IRQ_INT_EN_INSTR1_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_INSTR1_END_MASK) >> SEI_CTRL_IRQ_INT_EN_INSTR1_END_SHIFT)

/*
 * INSTR0_END (RW)
 *
 * Instruction 0 end
 */
#define SEI_CTRL_IRQ_INT_EN_INSTR0_END_MASK (0x400U)
#define SEI_CTRL_IRQ_INT_EN_INSTR0_END_SHIFT (10U)
#define SEI_CTRL_IRQ_INT_EN_INSTR0_END_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_INSTR0_END_SHIFT) & SEI_CTRL_IRQ_INT_EN_INSTR0_END_MASK)
#define SEI_CTRL_IRQ_INT_EN_INSTR0_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_INSTR0_END_MASK) >> SEI_CTRL_IRQ_INT_EN_INSTR0_END_SHIFT)

/*
 * PTR1_END (RW)
 *
 * Pointer 1 end
 */
#define SEI_CTRL_IRQ_INT_EN_PTR1_END_MASK (0x200U)
#define SEI_CTRL_IRQ_INT_EN_PTR1_END_SHIFT (9U)
#define SEI_CTRL_IRQ_INT_EN_PTR1_END_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_PTR1_END_SHIFT) & SEI_CTRL_IRQ_INT_EN_PTR1_END_MASK)
#define SEI_CTRL_IRQ_INT_EN_PTR1_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_PTR1_END_MASK) >> SEI_CTRL_IRQ_INT_EN_PTR1_END_SHIFT)

/*
 * PTR0_END (RW)
 *
 * Pointer 0 end
 */
#define SEI_CTRL_IRQ_INT_EN_PTR0_END_MASK (0x100U)
#define SEI_CTRL_IRQ_INT_EN_PTR0_END_SHIFT (8U)
#define SEI_CTRL_IRQ_INT_EN_PTR0_END_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_PTR0_END_SHIFT) & SEI_CTRL_IRQ_INT_EN_PTR0_END_MASK)
#define SEI_CTRL_IRQ_INT_EN_PTR0_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_PTR0_END_MASK) >> SEI_CTRL_IRQ_INT_EN_PTR0_END_SHIFT)

/*
 * INSTR1_ST (RW)
 *
 * Instruction 1 start
 */
#define SEI_CTRL_IRQ_INT_EN_INSTR1_ST_MASK (0x80U)
#define SEI_CTRL_IRQ_INT_EN_INSTR1_ST_SHIFT (7U)
#define SEI_CTRL_IRQ_INT_EN_INSTR1_ST_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_INSTR1_ST_SHIFT) & SEI_CTRL_IRQ_INT_EN_INSTR1_ST_MASK)
#define SEI_CTRL_IRQ_INT_EN_INSTR1_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_INSTR1_ST_MASK) >> SEI_CTRL_IRQ_INT_EN_INSTR1_ST_SHIFT)

/*
 * INSTR0_ST (RW)
 *
 * Instruction 0 start
 */
#define SEI_CTRL_IRQ_INT_EN_INSTR0_ST_MASK (0x40U)
#define SEI_CTRL_IRQ_INT_EN_INSTR0_ST_SHIFT (6U)
#define SEI_CTRL_IRQ_INT_EN_INSTR0_ST_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_INSTR0_ST_SHIFT) & SEI_CTRL_IRQ_INT_EN_INSTR0_ST_MASK)
#define SEI_CTRL_IRQ_INT_EN_INSTR0_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_INSTR0_ST_MASK) >> SEI_CTRL_IRQ_INT_EN_INSTR0_ST_SHIFT)

/*
 * PTR1_ST (RW)
 *
 * Pointer 1 start
 */
#define SEI_CTRL_IRQ_INT_EN_PTR1_ST_MASK (0x20U)
#define SEI_CTRL_IRQ_INT_EN_PTR1_ST_SHIFT (5U)
#define SEI_CTRL_IRQ_INT_EN_PTR1_ST_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_PTR1_ST_SHIFT) & SEI_CTRL_IRQ_INT_EN_PTR1_ST_MASK)
#define SEI_CTRL_IRQ_INT_EN_PTR1_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_PTR1_ST_MASK) >> SEI_CTRL_IRQ_INT_EN_PTR1_ST_SHIFT)

/*
 * PTR0_ST (RW)
 *
 * Pointer 0 start
 */
#define SEI_CTRL_IRQ_INT_EN_PTR0_ST_MASK (0x10U)
#define SEI_CTRL_IRQ_INT_EN_PTR0_ST_SHIFT (4U)
#define SEI_CTRL_IRQ_INT_EN_PTR0_ST_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_PTR0_ST_SHIFT) & SEI_CTRL_IRQ_INT_EN_PTR0_ST_MASK)
#define SEI_CTRL_IRQ_INT_EN_PTR0_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_PTR0_ST_MASK) >> SEI_CTRL_IRQ_INT_EN_PTR0_ST_SHIFT)

/*
 * WDOG (RW)
 *
 * Watch dog
 */
#define SEI_CTRL_IRQ_INT_EN_WDOG_MASK (0x4U)
#define SEI_CTRL_IRQ_INT_EN_WDOG_SHIFT (2U)
#define SEI_CTRL_IRQ_INT_EN_WDOG_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_WDOG_SHIFT) & SEI_CTRL_IRQ_INT_EN_WDOG_MASK)
#define SEI_CTRL_IRQ_INT_EN_WDOG_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_WDOG_MASK) >> SEI_CTRL_IRQ_INT_EN_WDOG_SHIFT)

/*
 * EXCEPT (RW)
 *
 * Exception
 */
#define SEI_CTRL_IRQ_INT_EN_EXCEPT_MASK (0x2U)
#define SEI_CTRL_IRQ_INT_EN_EXCEPT_SHIFT (1U)
#define SEI_CTRL_IRQ_INT_EN_EXCEPT_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_EXCEPT_SHIFT) & SEI_CTRL_IRQ_INT_EN_EXCEPT_MASK)
#define SEI_CTRL_IRQ_INT_EN_EXCEPT_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_EXCEPT_MASK) >> SEI_CTRL_IRQ_INT_EN_EXCEPT_SHIFT)

/*
 * STALL (RW)
 *
 * Stall
 */
#define SEI_CTRL_IRQ_INT_EN_STALL_MASK (0x1U)
#define SEI_CTRL_IRQ_INT_EN_STALL_SHIFT (0U)
#define SEI_CTRL_IRQ_INT_EN_STALL_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_EN_STALL_SHIFT) & SEI_CTRL_IRQ_INT_EN_STALL_MASK)
#define SEI_CTRL_IRQ_INT_EN_STALL_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_EN_STALL_MASK) >> SEI_CTRL_IRQ_INT_EN_STALL_SHIFT)

/* Bitfield definition for register of struct array CTRL: INT_FLAG */
/*
 * TRG_ERR3 (W1C)
 *
 * Trigger3 failed
 */
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR3_MASK (0x80000000UL)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR3_SHIFT (31U)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR3_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_TRG_ERR3_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_TRG_ERR3_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR3_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_TRG_ERR3_MASK) >> SEI_CTRL_IRQ_INT_FLAG_TRG_ERR3_SHIFT)

/*
 * TRG_ERR2 (W1C)
 *
 * Trigger2 failed
 */
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR2_MASK (0x40000000UL)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR2_SHIFT (30U)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR2_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_TRG_ERR2_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_TRG_ERR2_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR2_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_TRG_ERR2_MASK) >> SEI_CTRL_IRQ_INT_FLAG_TRG_ERR2_SHIFT)

/*
 * TRG_ERR1 (W1C)
 *
 * Trigger1 failed
 */
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR1_MASK (0x20000000UL)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR1_SHIFT (29U)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR1_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_TRG_ERR1_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_TRG_ERR1_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR1_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_TRG_ERR1_MASK) >> SEI_CTRL_IRQ_INT_FLAG_TRG_ERR1_SHIFT)

/*
 * TRG_ERR0 (W1C)
 *
 * Trigger0 failed
 */
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR0_MASK (0x10000000UL)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR0_SHIFT (28U)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR0_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_TRG_ERR0_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_TRG_ERR0_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_TRG_ERR0_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_TRG_ERR0_MASK) >> SEI_CTRL_IRQ_INT_FLAG_TRG_ERR0_SHIFT)

/*
 * TRIGER3 (W1C)
 *
 * Trigger3
 */
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER3_MASK (0x8000000UL)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER3_SHIFT (27U)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER3_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_TRIGER3_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_TRIGER3_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER3_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_TRIGER3_MASK) >> SEI_CTRL_IRQ_INT_FLAG_TRIGER3_SHIFT)

/*
 * TRIGER2 (W1C)
 *
 * Trigger2
 */
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER2_MASK (0x4000000UL)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER2_SHIFT (26U)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER2_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_TRIGER2_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_TRIGER2_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER2_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_TRIGER2_MASK) >> SEI_CTRL_IRQ_INT_FLAG_TRIGER2_SHIFT)

/*
 * TRIGER1 (W1C)
 *
 * Trigger1
 */
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER1_MASK (0x2000000UL)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER1_SHIFT (25U)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER1_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_TRIGER1_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_TRIGER1_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER1_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_TRIGER1_MASK) >> SEI_CTRL_IRQ_INT_FLAG_TRIGER1_SHIFT)

/*
 * TRIGER0 (W1C)
 *
 * Trigger0
 */
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER0_MASK (0x1000000UL)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER0_SHIFT (24U)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER0_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_TRIGER0_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_TRIGER0_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_TRIGER0_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_TRIGER0_MASK) >> SEI_CTRL_IRQ_INT_FLAG_TRIGER0_SHIFT)

/*
 * SMP_ERR (W1C)
 *
 * Sample error
 */
#define SEI_CTRL_IRQ_INT_FLAG_SMP_ERR_MASK (0x100000UL)
#define SEI_CTRL_IRQ_INT_FLAG_SMP_ERR_SHIFT (20U)
#define SEI_CTRL_IRQ_INT_FLAG_SMP_ERR_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_SMP_ERR_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_SMP_ERR_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_SMP_ERR_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_SMP_ERR_MASK) >> SEI_CTRL_IRQ_INT_FLAG_SMP_ERR_SHIFT)

/*
 * LATCH3 (W1C)
 *
 * Latch3
 */
#define SEI_CTRL_IRQ_INT_FLAG_LATCH3_MASK (0x80000UL)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH3_SHIFT (19U)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH3_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_LATCH3_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_LATCH3_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH3_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_LATCH3_MASK) >> SEI_CTRL_IRQ_INT_FLAG_LATCH3_SHIFT)

/*
 * LATCH2 (W1C)
 *
 * Latch2
 */
#define SEI_CTRL_IRQ_INT_FLAG_LATCH2_MASK (0x40000UL)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH2_SHIFT (18U)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH2_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_LATCH2_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_LATCH2_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH2_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_LATCH2_MASK) >> SEI_CTRL_IRQ_INT_FLAG_LATCH2_SHIFT)

/*
 * LATCH1 (W1C)
 *
 * Latch1
 */
#define SEI_CTRL_IRQ_INT_FLAG_LATCH1_MASK (0x20000UL)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH1_SHIFT (17U)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH1_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_LATCH1_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_LATCH1_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH1_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_LATCH1_MASK) >> SEI_CTRL_IRQ_INT_FLAG_LATCH1_SHIFT)

/*
 * LATCH0 (W1C)
 *
 * Latch0
 */
#define SEI_CTRL_IRQ_INT_FLAG_LATCH0_MASK (0x10000UL)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH0_SHIFT (16U)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH0_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_LATCH0_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_LATCH0_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_LATCH0_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_LATCH0_MASK) >> SEI_CTRL_IRQ_INT_FLAG_LATCH0_SHIFT)

/*
 * TIMEOUT (W1C)
 *
 * Timeout
 */
#define SEI_CTRL_IRQ_INT_FLAG_TIMEOUT_MASK (0x2000U)
#define SEI_CTRL_IRQ_INT_FLAG_TIMEOUT_SHIFT (13U)
#define SEI_CTRL_IRQ_INT_FLAG_TIMEOUT_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_TIMEOUT_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_TIMEOUT_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_TIMEOUT_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_TIMEOUT_MASK) >> SEI_CTRL_IRQ_INT_FLAG_TIMEOUT_SHIFT)

/*
 * TRX_ERR (W1C)
 *
 * Transfer error
 */
#define SEI_CTRL_IRQ_INT_FLAG_TRX_ERR_MASK (0x1000U)
#define SEI_CTRL_IRQ_INT_FLAG_TRX_ERR_SHIFT (12U)
#define SEI_CTRL_IRQ_INT_FLAG_TRX_ERR_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_TRX_ERR_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_TRX_ERR_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_TRX_ERR_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_TRX_ERR_MASK) >> SEI_CTRL_IRQ_INT_FLAG_TRX_ERR_SHIFT)

/*
 * INSTR1_END (W1C)
 *
 * Instruction 1 end
 */
#define SEI_CTRL_IRQ_INT_FLAG_INSTR1_END_MASK (0x800U)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR1_END_SHIFT (11U)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR1_END_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_INSTR1_END_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_INSTR1_END_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR1_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_INSTR1_END_MASK) >> SEI_CTRL_IRQ_INT_FLAG_INSTR1_END_SHIFT)

/*
 * INSTR0_END (W1C)
 *
 * Instruction 0 end
 */
#define SEI_CTRL_IRQ_INT_FLAG_INSTR0_END_MASK (0x400U)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR0_END_SHIFT (10U)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR0_END_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_INSTR0_END_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_INSTR0_END_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR0_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_INSTR0_END_MASK) >> SEI_CTRL_IRQ_INT_FLAG_INSTR0_END_SHIFT)

/*
 * PTR1_END (W1C)
 *
 * Pointer 1 end
 */
#define SEI_CTRL_IRQ_INT_FLAG_PTR1_END_MASK (0x200U)
#define SEI_CTRL_IRQ_INT_FLAG_PTR1_END_SHIFT (9U)
#define SEI_CTRL_IRQ_INT_FLAG_PTR1_END_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_PTR1_END_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_PTR1_END_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_PTR1_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_PTR1_END_MASK) >> SEI_CTRL_IRQ_INT_FLAG_PTR1_END_SHIFT)

/*
 * PTR0_END (W1C)
 *
 * Pointer 0 end
 */
#define SEI_CTRL_IRQ_INT_FLAG_PTR0_END_MASK (0x100U)
#define SEI_CTRL_IRQ_INT_FLAG_PTR0_END_SHIFT (8U)
#define SEI_CTRL_IRQ_INT_FLAG_PTR0_END_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_PTR0_END_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_PTR0_END_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_PTR0_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_PTR0_END_MASK) >> SEI_CTRL_IRQ_INT_FLAG_PTR0_END_SHIFT)

/*
 * INSTR1_ST (W1C)
 *
 * Instruction 1 start
 */
#define SEI_CTRL_IRQ_INT_FLAG_INSTR1_ST_MASK (0x80U)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR1_ST_SHIFT (7U)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR1_ST_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_INSTR1_ST_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_INSTR1_ST_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR1_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_INSTR1_ST_MASK) >> SEI_CTRL_IRQ_INT_FLAG_INSTR1_ST_SHIFT)

/*
 * INSTR0_ST (W1C)
 *
 * Instruction 0 start
 */
#define SEI_CTRL_IRQ_INT_FLAG_INSTR0_ST_MASK (0x40U)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR0_ST_SHIFT (6U)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR0_ST_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_INSTR0_ST_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_INSTR0_ST_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_INSTR0_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_INSTR0_ST_MASK) >> SEI_CTRL_IRQ_INT_FLAG_INSTR0_ST_SHIFT)

/*
 * PTR1_ST (W1C)
 *
 * Pointer 1 start
 */
#define SEI_CTRL_IRQ_INT_FLAG_PTR1_ST_MASK (0x20U)
#define SEI_CTRL_IRQ_INT_FLAG_PTR1_ST_SHIFT (5U)
#define SEI_CTRL_IRQ_INT_FLAG_PTR1_ST_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_PTR1_ST_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_PTR1_ST_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_PTR1_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_PTR1_ST_MASK) >> SEI_CTRL_IRQ_INT_FLAG_PTR1_ST_SHIFT)

/*
 * PTR0_ST (W1C)
 *
 * Pointer 0 start
 */
#define SEI_CTRL_IRQ_INT_FLAG_PTR0_ST_MASK (0x10U)
#define SEI_CTRL_IRQ_INT_FLAG_PTR0_ST_SHIFT (4U)
#define SEI_CTRL_IRQ_INT_FLAG_PTR0_ST_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_PTR0_ST_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_PTR0_ST_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_PTR0_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_PTR0_ST_MASK) >> SEI_CTRL_IRQ_INT_FLAG_PTR0_ST_SHIFT)

/*
 * WDOG (W1C)
 *
 * Watch dog
 */
#define SEI_CTRL_IRQ_INT_FLAG_WDOG_MASK (0x4U)
#define SEI_CTRL_IRQ_INT_FLAG_WDOG_SHIFT (2U)
#define SEI_CTRL_IRQ_INT_FLAG_WDOG_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_WDOG_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_WDOG_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_WDOG_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_WDOG_MASK) >> SEI_CTRL_IRQ_INT_FLAG_WDOG_SHIFT)

/*
 * EXCEPT (W1C)
 *
 * Exception
 */
#define SEI_CTRL_IRQ_INT_FLAG_EXCEPT_MASK (0x2U)
#define SEI_CTRL_IRQ_INT_FLAG_EXCEPT_SHIFT (1U)
#define SEI_CTRL_IRQ_INT_FLAG_EXCEPT_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_EXCEPT_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_EXCEPT_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_EXCEPT_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_EXCEPT_MASK) >> SEI_CTRL_IRQ_INT_FLAG_EXCEPT_SHIFT)

/*
 * STALL (W1C)
 *
 * Stall
 */
#define SEI_CTRL_IRQ_INT_FLAG_STALL_MASK (0x1U)
#define SEI_CTRL_IRQ_INT_FLAG_STALL_SHIFT (0U)
#define SEI_CTRL_IRQ_INT_FLAG_STALL_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INT_FLAG_STALL_SHIFT) & SEI_CTRL_IRQ_INT_FLAG_STALL_MASK)
#define SEI_CTRL_IRQ_INT_FLAG_STALL_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_FLAG_STALL_MASK) >> SEI_CTRL_IRQ_INT_FLAG_STALL_SHIFT)

/* Bitfield definition for register of struct array CTRL: INT_STS */
/*
 * TRG_ERR3 (RO)
 *
 * Trigger3 failed
 */
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR3_MASK (0x80000000UL)
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR3_SHIFT (31U)
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR3_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_TRG_ERR3_MASK) >> SEI_CTRL_IRQ_INT_STS_TRG_ERR3_SHIFT)

/*
 * TRG_ERR2 (RO)
 *
 * Trigger2 failed
 */
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR2_MASK (0x40000000UL)
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR2_SHIFT (30U)
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR2_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_TRG_ERR2_MASK) >> SEI_CTRL_IRQ_INT_STS_TRG_ERR2_SHIFT)

/*
 * TRG_ERR1 (RO)
 *
 * Trigger1 failed
 */
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR1_MASK (0x20000000UL)
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR1_SHIFT (29U)
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR1_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_TRG_ERR1_MASK) >> SEI_CTRL_IRQ_INT_STS_TRG_ERR1_SHIFT)

/*
 * TRG_ERR0 (RO)
 *
 * Trigger0 failed
 */
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR0_MASK (0x10000000UL)
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR0_SHIFT (28U)
#define SEI_CTRL_IRQ_INT_STS_TRG_ERR0_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_TRG_ERR0_MASK) >> SEI_CTRL_IRQ_INT_STS_TRG_ERR0_SHIFT)

/*
 * TRIGER3 (RO)
 *
 * Trigger3
 */
#define SEI_CTRL_IRQ_INT_STS_TRIGER3_MASK (0x8000000UL)
#define SEI_CTRL_IRQ_INT_STS_TRIGER3_SHIFT (27U)
#define SEI_CTRL_IRQ_INT_STS_TRIGER3_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_TRIGER3_MASK) >> SEI_CTRL_IRQ_INT_STS_TRIGER3_SHIFT)

/*
 * TRIGER2 (RO)
 *
 * Trigger2
 */
#define SEI_CTRL_IRQ_INT_STS_TRIGER2_MASK (0x4000000UL)
#define SEI_CTRL_IRQ_INT_STS_TRIGER2_SHIFT (26U)
#define SEI_CTRL_IRQ_INT_STS_TRIGER2_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_TRIGER2_MASK) >> SEI_CTRL_IRQ_INT_STS_TRIGER2_SHIFT)

/*
 * TRIGER1 (RO)
 *
 * Trigger1
 */
#define SEI_CTRL_IRQ_INT_STS_TRIGER1_MASK (0x2000000UL)
#define SEI_CTRL_IRQ_INT_STS_TRIGER1_SHIFT (25U)
#define SEI_CTRL_IRQ_INT_STS_TRIGER1_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_TRIGER1_MASK) >> SEI_CTRL_IRQ_INT_STS_TRIGER1_SHIFT)

/*
 * TRIGER0 (RO)
 *
 * Trigger0
 */
#define SEI_CTRL_IRQ_INT_STS_TRIGER0_MASK (0x1000000UL)
#define SEI_CTRL_IRQ_INT_STS_TRIGER0_SHIFT (24U)
#define SEI_CTRL_IRQ_INT_STS_TRIGER0_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_TRIGER0_MASK) >> SEI_CTRL_IRQ_INT_STS_TRIGER0_SHIFT)

/*
 * SMP_ERR (RO)
 *
 * Sample error
 */
#define SEI_CTRL_IRQ_INT_STS_SMP_ERR_MASK (0x100000UL)
#define SEI_CTRL_IRQ_INT_STS_SMP_ERR_SHIFT (20U)
#define SEI_CTRL_IRQ_INT_STS_SMP_ERR_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_SMP_ERR_MASK) >> SEI_CTRL_IRQ_INT_STS_SMP_ERR_SHIFT)

/*
 * LATCH3 (RO)
 *
 * Latch3
 */
#define SEI_CTRL_IRQ_INT_STS_LATCH3_MASK (0x80000UL)
#define SEI_CTRL_IRQ_INT_STS_LATCH3_SHIFT (19U)
#define SEI_CTRL_IRQ_INT_STS_LATCH3_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_LATCH3_MASK) >> SEI_CTRL_IRQ_INT_STS_LATCH3_SHIFT)

/*
 * LATCH2 (RO)
 *
 * Latch2
 */
#define SEI_CTRL_IRQ_INT_STS_LATCH2_MASK (0x40000UL)
#define SEI_CTRL_IRQ_INT_STS_LATCH2_SHIFT (18U)
#define SEI_CTRL_IRQ_INT_STS_LATCH2_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_LATCH2_MASK) >> SEI_CTRL_IRQ_INT_STS_LATCH2_SHIFT)

/*
 * LATCH1 (RO)
 *
 * Latch1
 */
#define SEI_CTRL_IRQ_INT_STS_LATCH1_MASK (0x20000UL)
#define SEI_CTRL_IRQ_INT_STS_LATCH1_SHIFT (17U)
#define SEI_CTRL_IRQ_INT_STS_LATCH1_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_LATCH1_MASK) >> SEI_CTRL_IRQ_INT_STS_LATCH1_SHIFT)

/*
 * LATCH0 (RO)
 *
 * Latch0
 */
#define SEI_CTRL_IRQ_INT_STS_LATCH0_MASK (0x10000UL)
#define SEI_CTRL_IRQ_INT_STS_LATCH0_SHIFT (16U)
#define SEI_CTRL_IRQ_INT_STS_LATCH0_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_LATCH0_MASK) >> SEI_CTRL_IRQ_INT_STS_LATCH0_SHIFT)

/*
 * TIMEOUT (RO)
 *
 * Timeout
 */
#define SEI_CTRL_IRQ_INT_STS_TIMEOUT_MASK (0x2000U)
#define SEI_CTRL_IRQ_INT_STS_TIMEOUT_SHIFT (13U)
#define SEI_CTRL_IRQ_INT_STS_TIMEOUT_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_TIMEOUT_MASK) >> SEI_CTRL_IRQ_INT_STS_TIMEOUT_SHIFT)

/*
 * TRX_ERR (RO)
 *
 * Transfer error
 */
#define SEI_CTRL_IRQ_INT_STS_TRX_ERR_MASK (0x1000U)
#define SEI_CTRL_IRQ_INT_STS_TRX_ERR_SHIFT (12U)
#define SEI_CTRL_IRQ_INT_STS_TRX_ERR_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_TRX_ERR_MASK) >> SEI_CTRL_IRQ_INT_STS_TRX_ERR_SHIFT)

/*
 * INSTR1_END (RO)
 *
 * Instruction 1 end
 */
#define SEI_CTRL_IRQ_INT_STS_INSTR1_END_MASK (0x800U)
#define SEI_CTRL_IRQ_INT_STS_INSTR1_END_SHIFT (11U)
#define SEI_CTRL_IRQ_INT_STS_INSTR1_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_INSTR1_END_MASK) >> SEI_CTRL_IRQ_INT_STS_INSTR1_END_SHIFT)

/*
 * INSTR0_END (RO)
 *
 * Instruction 0 end
 */
#define SEI_CTRL_IRQ_INT_STS_INSTR0_END_MASK (0x400U)
#define SEI_CTRL_IRQ_INT_STS_INSTR0_END_SHIFT (10U)
#define SEI_CTRL_IRQ_INT_STS_INSTR0_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_INSTR0_END_MASK) >> SEI_CTRL_IRQ_INT_STS_INSTR0_END_SHIFT)

/*
 * PTR1_END (RO)
 *
 * Pointer 1 end
 */
#define SEI_CTRL_IRQ_INT_STS_PTR1_END_MASK (0x200U)
#define SEI_CTRL_IRQ_INT_STS_PTR1_END_SHIFT (9U)
#define SEI_CTRL_IRQ_INT_STS_PTR1_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_PTR1_END_MASK) >> SEI_CTRL_IRQ_INT_STS_PTR1_END_SHIFT)

/*
 * PTR0_END (RO)
 *
 * Pointer 0 end
 */
#define SEI_CTRL_IRQ_INT_STS_PTR0_END_MASK (0x100U)
#define SEI_CTRL_IRQ_INT_STS_PTR0_END_SHIFT (8U)
#define SEI_CTRL_IRQ_INT_STS_PTR0_END_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_PTR0_END_MASK) >> SEI_CTRL_IRQ_INT_STS_PTR0_END_SHIFT)

/*
 * INSTR1_ST (RO)
 *
 * Instruction 1 start
 */
#define SEI_CTRL_IRQ_INT_STS_INSTR1_ST_MASK (0x80U)
#define SEI_CTRL_IRQ_INT_STS_INSTR1_ST_SHIFT (7U)
#define SEI_CTRL_IRQ_INT_STS_INSTR1_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_INSTR1_ST_MASK) >> SEI_CTRL_IRQ_INT_STS_INSTR1_ST_SHIFT)

/*
 * INSTR0_ST (RO)
 *
 * Instruction 0 start
 */
#define SEI_CTRL_IRQ_INT_STS_INSTR0_ST_MASK (0x40U)
#define SEI_CTRL_IRQ_INT_STS_INSTR0_ST_SHIFT (6U)
#define SEI_CTRL_IRQ_INT_STS_INSTR0_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_INSTR0_ST_MASK) >> SEI_CTRL_IRQ_INT_STS_INSTR0_ST_SHIFT)

/*
 * PTR1_ST (RO)
 *
 * Pointer 1 start
 */
#define SEI_CTRL_IRQ_INT_STS_PTR1_ST_MASK (0x20U)
#define SEI_CTRL_IRQ_INT_STS_PTR1_ST_SHIFT (5U)
#define SEI_CTRL_IRQ_INT_STS_PTR1_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_PTR1_ST_MASK) >> SEI_CTRL_IRQ_INT_STS_PTR1_ST_SHIFT)

/*
 * PTR0_ST (RO)
 *
 * Pointer 0 start
 */
#define SEI_CTRL_IRQ_INT_STS_PTR0_ST_MASK (0x10U)
#define SEI_CTRL_IRQ_INT_STS_PTR0_ST_SHIFT (4U)
#define SEI_CTRL_IRQ_INT_STS_PTR0_ST_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_PTR0_ST_MASK) >> SEI_CTRL_IRQ_INT_STS_PTR0_ST_SHIFT)

/*
 * WDOG (RO)
 *
 * Watch dog
 */
#define SEI_CTRL_IRQ_INT_STS_WDOG_MASK (0x4U)
#define SEI_CTRL_IRQ_INT_STS_WDOG_SHIFT (2U)
#define SEI_CTRL_IRQ_INT_STS_WDOG_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_WDOG_MASK) >> SEI_CTRL_IRQ_INT_STS_WDOG_SHIFT)

/*
 * EXCEPT (RO)
 *
 * Exception
 */
#define SEI_CTRL_IRQ_INT_STS_EXCEPT_MASK (0x2U)
#define SEI_CTRL_IRQ_INT_STS_EXCEPT_SHIFT (1U)
#define SEI_CTRL_IRQ_INT_STS_EXCEPT_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_EXCEPT_MASK) >> SEI_CTRL_IRQ_INT_STS_EXCEPT_SHIFT)

/*
 * STALL (RO)
 *
 * Stall
 */
#define SEI_CTRL_IRQ_INT_STS_STALL_MASK (0x1U)
#define SEI_CTRL_IRQ_INT_STS_STALL_SHIFT (0U)
#define SEI_CTRL_IRQ_INT_STS_STALL_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INT_STS_STALL_MASK) >> SEI_CTRL_IRQ_INT_STS_STALL_SHIFT)

/* Bitfield definition for register of struct array CTRL: POINTER0 */
/*
 * POINTER (RW)
 *
 * Match pointer 0
 */
#define SEI_CTRL_IRQ_POINTER0_POINTER_MASK (0xFFU)
#define SEI_CTRL_IRQ_POINTER0_POINTER_SHIFT (0U)
#define SEI_CTRL_IRQ_POINTER0_POINTER_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_POINTER0_POINTER_SHIFT) & SEI_CTRL_IRQ_POINTER0_POINTER_MASK)
#define SEI_CTRL_IRQ_POINTER0_POINTER_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_POINTER0_POINTER_MASK) >> SEI_CTRL_IRQ_POINTER0_POINTER_SHIFT)

/* Bitfield definition for register of struct array CTRL: POINTER1 */
/*
 * POINTER (RW)
 *
 * Match pointer 1
 */
#define SEI_CTRL_IRQ_POINTER1_POINTER_MASK (0xFFU)
#define SEI_CTRL_IRQ_POINTER1_POINTER_SHIFT (0U)
#define SEI_CTRL_IRQ_POINTER1_POINTER_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_POINTER1_POINTER_SHIFT) & SEI_CTRL_IRQ_POINTER1_POINTER_MASK)
#define SEI_CTRL_IRQ_POINTER1_POINTER_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_POINTER1_POINTER_MASK) >> SEI_CTRL_IRQ_POINTER1_POINTER_SHIFT)

/* Bitfield definition for register of struct array CTRL: INSTR0 */
/*
 * INSTR (RW)
 *
 * Match instruction 0
 */
#define SEI_CTRL_IRQ_INSTR0_INSTR_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_IRQ_INSTR0_INSTR_SHIFT (0U)
#define SEI_CTRL_IRQ_INSTR0_INSTR_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INSTR0_INSTR_SHIFT) & SEI_CTRL_IRQ_INSTR0_INSTR_MASK)
#define SEI_CTRL_IRQ_INSTR0_INSTR_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INSTR0_INSTR_MASK) >> SEI_CTRL_IRQ_INSTR0_INSTR_SHIFT)

/* Bitfield definition for register of struct array CTRL: INSTR1 */
/*
 * INSTR (RW)
 *
 * Match instruction 1
 */
#define SEI_CTRL_IRQ_INSTR1_INSTR_MASK (0xFFFFFFFFUL)
#define SEI_CTRL_IRQ_INSTR1_INSTR_SHIFT (0U)
#define SEI_CTRL_IRQ_INSTR1_INSTR_SET(x) (((uint32_t)(x) << SEI_CTRL_IRQ_INSTR1_INSTR_SHIFT) & SEI_CTRL_IRQ_INSTR1_INSTR_MASK)
#define SEI_CTRL_IRQ_INSTR1_INSTR_GET(x) (((uint32_t)(x) & SEI_CTRL_IRQ_INSTR1_INSTR_MASK) >> SEI_CTRL_IRQ_INSTR1_INSTR_SHIFT)

/* Bitfield definition for register array: INSTR */
/*
 * OP (RW)
 *
 * operation
 * 0: halt
 * 1: jump
 * 2: send with timeout check
 * 3: send without timout check
 * 4: wait with timeout check
 * 5: wait without timout check
 * 6: receive with timeout check
 * 7: receive without timout check
 */
#define SEI_INSTR_OP_MASK (0x1C000000UL)
#define SEI_INSTR_OP_SHIFT (26U)
#define SEI_INSTR_OP_SET(x) (((uint32_t)(x) << SEI_INSTR_OP_SHIFT) & SEI_INSTR_OP_MASK)
#define SEI_INSTR_OP_GET(x) (((uint32_t)(x) & SEI_INSTR_OP_MASK) >> SEI_INSTR_OP_SHIFT)

/*
 * CK (RW)
 *
 * clock
 * 0: low
 * 1: rise-fall
 * 2: fall-rise
 * 3: high
 */
#define SEI_INSTR_CK_MASK (0x3000000UL)
#define SEI_INSTR_CK_SHIFT (24U)
#define SEI_INSTR_CK_SET(x) (((uint32_t)(x) << SEI_INSTR_CK_SHIFT) & SEI_INSTR_CK_MASK)
#define SEI_INSTR_CK_GET(x) (((uint32_t)(x) & SEI_INSTR_CK_MASK) >> SEI_INSTR_CK_SHIFT)

/*
 * CRC (RW)
 *
 * CRC register
 * 0: don't calculate CRC
 * 1: do not set this value
 * 2: data register 2
 * 3: data register 3
 * ...
 * 29: data register 29
 * 30: value 0 when send, wait 0 in receive
 * 31: value1 when send,  wait 1 in receive
 */
#define SEI_INSTR_CRC_MASK (0x1F0000UL)
#define SEI_INSTR_CRC_SHIFT (16U)
#define SEI_INSTR_CRC_SET(x) (((uint32_t)(x) << SEI_INSTR_CRC_SHIFT) & SEI_INSTR_CRC_MASK)
#define SEI_INSTR_CRC_GET(x) (((uint32_t)(x) & SEI_INSTR_CRC_MASK) >> SEI_INSTR_CRC_SHIFT)

/*
 * DAT (RW)
 *
 * DATA register
 * 0: ignore data
 * 1: command
 * 2: data register 2
 * 3: data register 3
 * ...
 * 29: data register 29
 * 30: value 0 when send, wait 0 in receive
 * 31: value1 when send,  wait 1 in receive
 */
#define SEI_INSTR_DAT_MASK (0x1F00U)
#define SEI_INSTR_DAT_SHIFT (8U)
#define SEI_INSTR_DAT_SET(x) (((uint32_t)(x) << SEI_INSTR_DAT_SHIFT) & SEI_INSTR_DAT_MASK)
#define SEI_INSTR_DAT_GET(x) (((uint32_t)(x) & SEI_INSTR_DAT_MASK) >> SEI_INSTR_DAT_SHIFT)

/*
 * OPR (RW)
 *
 * [1] When OP is 0, this area is the halt time in baudrate, 0 represents infinite time.
 * [2] When OP is 1, this area is the the pointer to the command table.
 * OPR[4]=1, OPR[3:0] value is CMD_TABLE instruct pointer;
 * OPR[4]=0, OPR[3:0]=0 is INIT_POINTER;
 * OPR[4]=0, OPR[3:0]=1 is WDG_POINTER.
 * [3] When OP is 2-7, this area is the data length as fellow:
 * 0: 1 bit
 * 1: 2 bit
 *  ...
 * 31: 32 bit
 */
#define SEI_INSTR_OPR_MASK (0x1FU)
#define SEI_INSTR_OPR_SHIFT (0U)
#define SEI_INSTR_OPR_SET(x) (((uint32_t)(x) << SEI_INSTR_OPR_SHIFT) & SEI_INSTR_OPR_MASK)
#define SEI_INSTR_OPR_GET(x) (((uint32_t)(x) & SEI_INSTR_OPR_MASK) >> SEI_INSTR_OPR_SHIFT)

/* Bitfield definition for register of struct array DAT: MODE */
/*
 * CRC_LEN (RW)
 *
 * CRC length
 * 0: 1 bit
 * 1: 2 bit
 * ...
 * 31: 32 bit
 */
#define SEI_DAT_MODE_CRC_LEN_MASK (0x1F000000UL)
#define SEI_DAT_MODE_CRC_LEN_SHIFT (24U)
#define SEI_DAT_MODE_CRC_LEN_SET(x) (((uint32_t)(x) << SEI_DAT_MODE_CRC_LEN_SHIFT) & SEI_DAT_MODE_CRC_LEN_MASK)
#define SEI_DAT_MODE_CRC_LEN_GET(x) (((uint32_t)(x) & SEI_DAT_MODE_CRC_LEN_MASK) >> SEI_DAT_MODE_CRC_LEN_SHIFT)

/*
 * WLEN (RW)
 *
 * word length
 * 0: 1 bit
 * 1: 2 bit
 * ...
 * 31: 32 bit
 */
#define SEI_DAT_MODE_WLEN_MASK (0x1F0000UL)
#define SEI_DAT_MODE_WLEN_SHIFT (16U)
#define SEI_DAT_MODE_WLEN_SET(x) (((uint32_t)(x) << SEI_DAT_MODE_WLEN_SHIFT) & SEI_DAT_MODE_WLEN_MASK)
#define SEI_DAT_MODE_WLEN_GET(x) (((uint32_t)(x) & SEI_DAT_MODE_WLEN_MASK) >> SEI_DAT_MODE_WLEN_SHIFT)

/*
 * CRC_SHIFT (RW)
 *
 * CRC shift mode, this mode is used to perform repeat code check
 * 0: CRC
 * 1: shift mode
 */
#define SEI_DAT_MODE_CRC_SHIFT_MASK (0x2000U)
#define SEI_DAT_MODE_CRC_SHIFT_SHIFT (13U)
#define SEI_DAT_MODE_CRC_SHIFT_SET(x) (((uint32_t)(x) << SEI_DAT_MODE_CRC_SHIFT_SHIFT) & SEI_DAT_MODE_CRC_SHIFT_MASK)
#define SEI_DAT_MODE_CRC_SHIFT_GET(x) (((uint32_t)(x) & SEI_DAT_MODE_CRC_SHIFT_MASK) >> SEI_DAT_MODE_CRC_SHIFT_SHIFT)

/*
 * CRC_INV (RW)
 *
 * CRC invert
 * 0: use CRC
 * 1: use inverted CRC
 */
#define SEI_DAT_MODE_CRC_INV_MASK (0x1000U)
#define SEI_DAT_MODE_CRC_INV_SHIFT (12U)
#define SEI_DAT_MODE_CRC_INV_SET(x) (((uint32_t)(x) << SEI_DAT_MODE_CRC_INV_SHIFT) & SEI_DAT_MODE_CRC_INV_MASK)
#define SEI_DAT_MODE_CRC_INV_GET(x) (((uint32_t)(x) & SEI_DAT_MODE_CRC_INV_MASK) >> SEI_DAT_MODE_CRC_INV_SHIFT)

/*
 * WORDER (RW)
 *
 * word order
 * 0: sample as bit order
 * 1: different from bit order
 */
#define SEI_DAT_MODE_WORDER_MASK (0x800U)
#define SEI_DAT_MODE_WORDER_SHIFT (11U)
#define SEI_DAT_MODE_WORDER_SET(x) (((uint32_t)(x) << SEI_DAT_MODE_WORDER_SHIFT) & SEI_DAT_MODE_WORDER_MASK)
#define SEI_DAT_MODE_WORDER_GET(x) (((uint32_t)(x) & SEI_DAT_MODE_WORDER_MASK) >> SEI_DAT_MODE_WORDER_SHIFT)

/*
 * BORDER (RW)
 *
 * bit order
 * 0: LSB first
 * 1: MSB first
 */
#define SEI_DAT_MODE_BORDER_MASK (0x400U)
#define SEI_DAT_MODE_BORDER_SHIFT (10U)
#define SEI_DAT_MODE_BORDER_SET(x) (((uint32_t)(x) << SEI_DAT_MODE_BORDER_SHIFT) & SEI_DAT_MODE_BORDER_MASK)
#define SEI_DAT_MODE_BORDER_GET(x) (((uint32_t)(x) & SEI_DAT_MODE_BORDER_MASK) >> SEI_DAT_MODE_BORDER_SHIFT)

/*
 * SIGNED (RW)
 *
 * Signed
 * 0: unsigned value
 * 1: signed value
 */
#define SEI_DAT_MODE_SIGNED_MASK (0x200U)
#define SEI_DAT_MODE_SIGNED_SHIFT (9U)
#define SEI_DAT_MODE_SIGNED_SET(x) (((uint32_t)(x) << SEI_DAT_MODE_SIGNED_SHIFT) & SEI_DAT_MODE_SIGNED_MASK)
#define SEI_DAT_MODE_SIGNED_GET(x) (((uint32_t)(x) & SEI_DAT_MODE_SIGNED_MASK) >> SEI_DAT_MODE_SIGNED_SHIFT)

/*
 * REWIND (RW)
 *
 * Write 1 to rewind read/write pointer, this is a self clear bit
 */
#define SEI_DAT_MODE_REWIND_MASK (0x100U)
#define SEI_DAT_MODE_REWIND_SHIFT (8U)
#define SEI_DAT_MODE_REWIND_SET(x) (((uint32_t)(x) << SEI_DAT_MODE_REWIND_SHIFT) & SEI_DAT_MODE_REWIND_MASK)
#define SEI_DAT_MODE_REWIND_GET(x) (((uint32_t)(x) & SEI_DAT_MODE_REWIND_MASK) >> SEI_DAT_MODE_REWIND_SHIFT)

/*
 * MODE (RW)
 *
 * Data mode
 * 0: data mode
 * 1: check mode
 * 2: CRC mode
 */
#define SEI_DAT_MODE_MODE_MASK (0x3U)
#define SEI_DAT_MODE_MODE_SHIFT (0U)
#define SEI_DAT_MODE_MODE_SET(x) (((uint32_t)(x) << SEI_DAT_MODE_MODE_SHIFT) & SEI_DAT_MODE_MODE_MASK)
#define SEI_DAT_MODE_MODE_GET(x) (((uint32_t)(x) & SEI_DAT_MODE_MODE_MASK) >> SEI_DAT_MODE_MODE_SHIFT)

/* Bitfield definition for register of struct array DAT: IDX */
/*
 * LAST_BIT (RW)
 *
 * Last bit index for tranceive
 */
#define SEI_DAT_IDX_LAST_BIT_MASK (0x1F000000UL)
#define SEI_DAT_IDX_LAST_BIT_SHIFT (24U)
#define SEI_DAT_IDX_LAST_BIT_SET(x) (((uint32_t)(x) << SEI_DAT_IDX_LAST_BIT_SHIFT) & SEI_DAT_IDX_LAST_BIT_MASK)
#define SEI_DAT_IDX_LAST_BIT_GET(x) (((uint32_t)(x) & SEI_DAT_IDX_LAST_BIT_MASK) >> SEI_DAT_IDX_LAST_BIT_SHIFT)

/*
 * FIRST_BIT (RW)
 *
 * First bit index for tranceive
 */
#define SEI_DAT_IDX_FIRST_BIT_MASK (0x1F0000UL)
#define SEI_DAT_IDX_FIRST_BIT_SHIFT (16U)
#define SEI_DAT_IDX_FIRST_BIT_SET(x) (((uint32_t)(x) << SEI_DAT_IDX_FIRST_BIT_SHIFT) & SEI_DAT_IDX_FIRST_BIT_MASK)
#define SEI_DAT_IDX_FIRST_BIT_GET(x) (((uint32_t)(x) & SEI_DAT_IDX_FIRST_BIT_MASK) >> SEI_DAT_IDX_FIRST_BIT_SHIFT)

/*
 * MAX_BIT (RW)
 *
 * Highest bit index
 */
#define SEI_DAT_IDX_MAX_BIT_MASK (0x1F00U)
#define SEI_DAT_IDX_MAX_BIT_SHIFT (8U)
#define SEI_DAT_IDX_MAX_BIT_SET(x) (((uint32_t)(x) << SEI_DAT_IDX_MAX_BIT_SHIFT) & SEI_DAT_IDX_MAX_BIT_MASK)
#define SEI_DAT_IDX_MAX_BIT_GET(x) (((uint32_t)(x) & SEI_DAT_IDX_MAX_BIT_MASK) >> SEI_DAT_IDX_MAX_BIT_SHIFT)

/*
 * MIN_BIT (RW)
 *
 * Lowest bit index
 */
#define SEI_DAT_IDX_MIN_BIT_MASK (0x1FU)
#define SEI_DAT_IDX_MIN_BIT_SHIFT (0U)
#define SEI_DAT_IDX_MIN_BIT_SET(x) (((uint32_t)(x) << SEI_DAT_IDX_MIN_BIT_SHIFT) & SEI_DAT_IDX_MIN_BIT_MASK)
#define SEI_DAT_IDX_MIN_BIT_GET(x) (((uint32_t)(x) & SEI_DAT_IDX_MIN_BIT_MASK) >> SEI_DAT_IDX_MIN_BIT_SHIFT)

/* Bitfield definition for register of struct array DAT: GOLD */
/*
 * GOLD_VALUE (RW)
 *
 * Gold value for check mode
 */
#define SEI_DAT_GOLD_GOLD_VALUE_MASK (0xFFFFFFFFUL)
#define SEI_DAT_GOLD_GOLD_VALUE_SHIFT (0U)
#define SEI_DAT_GOLD_GOLD_VALUE_SET(x) (((uint32_t)(x) << SEI_DAT_GOLD_GOLD_VALUE_SHIFT) & SEI_DAT_GOLD_GOLD_VALUE_MASK)
#define SEI_DAT_GOLD_GOLD_VALUE_GET(x) (((uint32_t)(x) & SEI_DAT_GOLD_GOLD_VALUE_MASK) >> SEI_DAT_GOLD_GOLD_VALUE_SHIFT)

/* Bitfield definition for register of struct array DAT: CRCINIT */
/*
 * CRC_INIT (RW)
 *
 * CRC initial value
 */
#define SEI_DAT_CRCINIT_CRC_INIT_MASK (0xFFFFFFFFUL)
#define SEI_DAT_CRCINIT_CRC_INIT_SHIFT (0U)
#define SEI_DAT_CRCINIT_CRC_INIT_SET(x) (((uint32_t)(x) << SEI_DAT_CRCINIT_CRC_INIT_SHIFT) & SEI_DAT_CRCINIT_CRC_INIT_MASK)
#define SEI_DAT_CRCINIT_CRC_INIT_GET(x) (((uint32_t)(x) & SEI_DAT_CRCINIT_CRC_INIT_MASK) >> SEI_DAT_CRCINIT_CRC_INIT_SHIFT)

/* Bitfield definition for register of struct array DAT: CRCPOLY */
/*
 * CRC_POLY (RW)
 *
 * CRC polymonial
 */
#define SEI_DAT_CRCPOLY_CRC_POLY_MASK (0xFFFFFFFFUL)
#define SEI_DAT_CRCPOLY_CRC_POLY_SHIFT (0U)
#define SEI_DAT_CRCPOLY_CRC_POLY_SET(x) (((uint32_t)(x) << SEI_DAT_CRCPOLY_CRC_POLY_SHIFT) & SEI_DAT_CRCPOLY_CRC_POLY_MASK)
#define SEI_DAT_CRCPOLY_CRC_POLY_GET(x) (((uint32_t)(x) & SEI_DAT_CRCPOLY_CRC_POLY_MASK) >> SEI_DAT_CRCPOLY_CRC_POLY_SHIFT)

/* Bitfield definition for register of struct array DAT: DATA */
/*
 * DATA (RW)
 *
 * DATA
 */
#define SEI_DAT_DATA_DATA_MASK (0xFFFFFFFFUL)
#define SEI_DAT_DATA_DATA_SHIFT (0U)
#define SEI_DAT_DATA_DATA_SET(x) (((uint32_t)(x) << SEI_DAT_DATA_DATA_SHIFT) & SEI_DAT_DATA_DATA_MASK)
#define SEI_DAT_DATA_DATA_GET(x) (((uint32_t)(x) & SEI_DAT_DATA_DATA_MASK) >> SEI_DAT_DATA_DATA_SHIFT)

/* Bitfield definition for register of struct array DAT: SET */
/*
 * DATA_SET (RW)
 *
 * DATA bit set
 */
#define SEI_DAT_SET_DATA_SET_MASK (0xFFFFFFFFUL)
#define SEI_DAT_SET_DATA_SET_SHIFT (0U)
#define SEI_DAT_SET_DATA_SET_SET(x) (((uint32_t)(x) << SEI_DAT_SET_DATA_SET_SHIFT) & SEI_DAT_SET_DATA_SET_MASK)
#define SEI_DAT_SET_DATA_SET_GET(x) (((uint32_t)(x) & SEI_DAT_SET_DATA_SET_MASK) >> SEI_DAT_SET_DATA_SET_SHIFT)

/* Bitfield definition for register of struct array DAT: CLR */
/*
 * DATA_CLR (RW)
 *
 * DATA bit clear
 */
#define SEI_DAT_CLR_DATA_CLR_MASK (0xFFFFFFFFUL)
#define SEI_DAT_CLR_DATA_CLR_SHIFT (0U)
#define SEI_DAT_CLR_DATA_CLR_SET(x) (((uint32_t)(x) << SEI_DAT_CLR_DATA_CLR_SHIFT) & SEI_DAT_CLR_DATA_CLR_MASK)
#define SEI_DAT_CLR_DATA_CLR_GET(x) (((uint32_t)(x) & SEI_DAT_CLR_DATA_CLR_MASK) >> SEI_DAT_CLR_DATA_CLR_SHIFT)

/* Bitfield definition for register of struct array DAT: INV */
/*
 * DATA_INV (RW)
 *
 * DATA bit toggle
 */
#define SEI_DAT_INV_DATA_INV_MASK (0xFFFFFFFFUL)
#define SEI_DAT_INV_DATA_INV_SHIFT (0U)
#define SEI_DAT_INV_DATA_INV_SET(x) (((uint32_t)(x) << SEI_DAT_INV_DATA_INV_SHIFT) & SEI_DAT_INV_DATA_INV_MASK)
#define SEI_DAT_INV_DATA_INV_GET(x) (((uint32_t)(x) & SEI_DAT_INV_DATA_INV_MASK) >> SEI_DAT_INV_DATA_INV_SHIFT)

/* Bitfield definition for register of struct array DAT: IN */
/*
 * DATA_IN (RO)
 *
 * Data input
 */
#define SEI_DAT_IN_DATA_IN_MASK (0xFFFFFFFFUL)
#define SEI_DAT_IN_DATA_IN_SHIFT (0U)
#define SEI_DAT_IN_DATA_IN_GET(x) (((uint32_t)(x) & SEI_DAT_IN_DATA_IN_MASK) >> SEI_DAT_IN_DATA_IN_SHIFT)

/* Bitfield definition for register of struct array DAT: OUT */
/*
 * DATA_OUT (RO)
 *
 * Data output
 */
#define SEI_DAT_OUT_DATA_OUT_MASK (0xFFFFFFFFUL)
#define SEI_DAT_OUT_DATA_OUT_SHIFT (0U)
#define SEI_DAT_OUT_DATA_OUT_GET(x) (((uint32_t)(x) & SEI_DAT_OUT_DATA_OUT_MASK) >> SEI_DAT_OUT_DATA_OUT_SHIFT)

/* Bitfield definition for register of struct array DAT: STS */
/*
 * CRC_IDX (RO)
 *
 * CRC index
 */
#define SEI_DAT_STS_CRC_IDX_MASK (0x1F000000UL)
#define SEI_DAT_STS_CRC_IDX_SHIFT (24U)
#define SEI_DAT_STS_CRC_IDX_GET(x) (((uint32_t)(x) & SEI_DAT_STS_CRC_IDX_MASK) >> SEI_DAT_STS_CRC_IDX_SHIFT)

/*
 * WORD_IDX (RO)
 *
 * Word index
 */
#define SEI_DAT_STS_WORD_IDX_MASK (0x1F0000UL)
#define SEI_DAT_STS_WORD_IDX_SHIFT (16U)
#define SEI_DAT_STS_WORD_IDX_GET(x) (((uint32_t)(x) & SEI_DAT_STS_WORD_IDX_MASK) >> SEI_DAT_STS_WORD_IDX_SHIFT)

/*
 * WORD_CNT (RO)
 *
 * Word counter
 */
#define SEI_DAT_STS_WORD_CNT_MASK (0x1F00U)
#define SEI_DAT_STS_WORD_CNT_SHIFT (8U)
#define SEI_DAT_STS_WORD_CNT_GET(x) (((uint32_t)(x) & SEI_DAT_STS_WORD_CNT_MASK) >> SEI_DAT_STS_WORD_CNT_SHIFT)

/*
 * BIT_IDX (RO)
 *
 * Bit index
 */
#define SEI_DAT_STS_BIT_IDX_MASK (0x1FU)
#define SEI_DAT_STS_BIT_IDX_SHIFT (0U)
#define SEI_DAT_STS_BIT_IDX_GET(x) (((uint32_t)(x) & SEI_DAT_STS_BIT_IDX_MASK) >> SEI_DAT_STS_BIT_IDX_SHIFT)



/* CMD register group index macro definition */
#define SEI_CTRL_TRG_TABLE_CMD_0 (0UL)
#define SEI_CTRL_TRG_TABLE_CMD_1 (1UL)
#define SEI_CTRL_TRG_TABLE_CMD_2 (2UL)
#define SEI_CTRL_TRG_TABLE_CMD_3 (3UL)

/* TIME register group index macro definition */
#define SEI_CTRL_TRG_TABLE_TIME_0 (0UL)
#define SEI_CTRL_TRG_TABLE_TIME_1 (1UL)
#define SEI_CTRL_TRG_TABLE_TIME_2 (2UL)
#define SEI_CTRL_TRG_TABLE_TIME_3 (3UL)

/* CMD_TABLE register group index macro definition */
#define SEI_CMD_TABLE_0 (0UL)
#define SEI_CMD_TABLE_1 (1UL)
#define SEI_CMD_TABLE_2 (2UL)
#define SEI_CMD_TABLE_3 (3UL)
#define SEI_CMD_TABLE_4 (4UL)
#define SEI_CMD_TABLE_5 (5UL)
#define SEI_CMD_TABLE_6 (6UL)
#define SEI_CMD_TABLE_7 (7UL)

/* TRAN register group index macro definition */
#define SEI_CTRL_LATCH_TRAN_0_1 (0UL)
#define SEI_CTRL_LATCH_TRAN_1_2 (1UL)
#define SEI_CTRL_LATCH_TRAN_2_3 (2UL)
#define SEI_CTRL_LATCH_TRAN_3_0 (3UL)

/* LATCH register group index macro definition */
#define SEI_LATCH_0 (0UL)
#define SEI_LATCH_1 (1UL)
#define SEI_LATCH_2 (2UL)
#define SEI_LATCH_3 (3UL)

/* CTRL register group index macro definition */
#define SEI_CTRL_0 (0UL)
#define SEI_CTRL_1 (1UL)

/* INSTR register group index macro definition */
#define SEI_INSTR_0 (0UL)
#define SEI_INSTR_1 (1UL)
#define SEI_INSTR_2 (2UL)
#define SEI_INSTR_3 (3UL)
#define SEI_INSTR_4 (4UL)
#define SEI_INSTR_5 (5UL)
#define SEI_INSTR_6 (6UL)
#define SEI_INSTR_7 (7UL)
#define SEI_INSTR_8 (8UL)
#define SEI_INSTR_9 (9UL)
#define SEI_INSTR_10 (10UL)
#define SEI_INSTR_11 (11UL)
#define SEI_INSTR_12 (12UL)
#define SEI_INSTR_13 (13UL)
#define SEI_INSTR_14 (14UL)
#define SEI_INSTR_15 (15UL)
#define SEI_INSTR_16 (16UL)
#define SEI_INSTR_17 (17UL)
#define SEI_INSTR_18 (18UL)
#define SEI_INSTR_19 (19UL)
#define SEI_INSTR_20 (20UL)
#define SEI_INSTR_21 (21UL)
#define SEI_INSTR_22 (22UL)
#define SEI_INSTR_23 (23UL)
#define SEI_INSTR_24 (24UL)
#define SEI_INSTR_25 (25UL)
#define SEI_INSTR_26 (26UL)
#define SEI_INSTR_27 (27UL)
#define SEI_INSTR_28 (28UL)
#define SEI_INSTR_29 (29UL)
#define SEI_INSTR_30 (30UL)
#define SEI_INSTR_31 (31UL)
#define SEI_INSTR_32 (32UL)
#define SEI_INSTR_33 (33UL)
#define SEI_INSTR_34 (34UL)
#define SEI_INSTR_35 (35UL)
#define SEI_INSTR_36 (36UL)
#define SEI_INSTR_37 (37UL)
#define SEI_INSTR_38 (38UL)
#define SEI_INSTR_39 (39UL)
#define SEI_INSTR_40 (40UL)
#define SEI_INSTR_41 (41UL)
#define SEI_INSTR_42 (42UL)
#define SEI_INSTR_43 (43UL)
#define SEI_INSTR_44 (44UL)
#define SEI_INSTR_45 (45UL)
#define SEI_INSTR_46 (46UL)
#define SEI_INSTR_47 (47UL)
#define SEI_INSTR_48 (48UL)
#define SEI_INSTR_49 (49UL)
#define SEI_INSTR_50 (50UL)
#define SEI_INSTR_51 (51UL)
#define SEI_INSTR_52 (52UL)
#define SEI_INSTR_53 (53UL)
#define SEI_INSTR_54 (54UL)
#define SEI_INSTR_55 (55UL)
#define SEI_INSTR_56 (56UL)
#define SEI_INSTR_57 (57UL)
#define SEI_INSTR_58 (58UL)
#define SEI_INSTR_59 (59UL)
#define SEI_INSTR_60 (60UL)
#define SEI_INSTR_61 (61UL)
#define SEI_INSTR_62 (62UL)
#define SEI_INSTR_63 (63UL)

/* DAT register group index macro definition */
#define SEI_DAT_0 (0UL)
#define SEI_DAT_1 (1UL)
#define SEI_DAT_2 (2UL)
#define SEI_DAT_3 (3UL)
#define SEI_DAT_4 (4UL)
#define SEI_DAT_5 (5UL)
#define SEI_DAT_6 (6UL)
#define SEI_DAT_7 (7UL)
#define SEI_DAT_8 (8UL)
#define SEI_DAT_9 (9UL)


#endif /* HPM_SEI_H */
