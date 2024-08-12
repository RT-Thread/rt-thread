/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_LOBS_H
#define HPM_LOBS_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0: Control Register */
    __R  uint8_t  RESERVED0[8];                /* 0x4 - 0xB: Reserved */
    __RW uint32_t STREAMCTRL;                  /* 0xC: Stream Control Register */
    __RW uint32_t PTACTION;                    /* 0x10: Pre-trigger Action Register */
    __RW uint32_t STARTADDR;                   /* 0x14: Start Address Register */
    __RW uint32_t ENDADDR;                     /* 0x18: End Address Register */
    __R  uint8_t  RESERVED1[4];                /* 0x1C - 0x1F: Reserved */
    __R  uint32_t CTSR;                        /* 0x20: Current Trigger State Register */
    __R  uint32_t CCVR;                        /* 0x24: Current Counter Value Register */
    __R  uint32_t CAVR;                        /* 0x28: Current Action Value Register */
    __R  uint8_t  RESERVED2[4];                /* 0x2C - 0x2F: Reserved */
    __R  uint32_t FIFOSTATE;                   /* 0x30: Fifo State Register */
    __RW uint32_t FINALADDR;                   /* 0x34: Final Address Register */
    __R  uint8_t  RESERVED3[24];               /* 0x38 - 0x4F: Reserved */
    __RW uint32_t GRPSELA;                     /* 0x50: Group Select Register */
    __RW uint32_t GRPENA;                      /* 0x54: Group Enable Register */
    __RW uint32_t SIGSELA1;                    /* 0x58: Signal Select1 Register */
    __R  uint8_t  RESERVED4[4];                /* 0x5C - 0x5F: Reserved */
    __RW uint32_t SIGSELA2;                    /* 0x60: Signal Select2 Register */
    __R  uint8_t  RESERVED5[52];               /* 0x64 - 0x97: Reserved */
    __RW uint32_t SIGENA;                      /* 0x98: Signal Enable Register */
    __R  uint8_t  RESERVED6[100];              /* 0x9C - 0xFF: Reserved */
    struct {
        __RW uint32_t SIGSEL;                  /* 0x100: Signal Select Register */
        __RW uint32_t TRIGCTRL;                /* 0x104: Trigger Control Register */
        __RW uint32_t NEXTSTATE;               /* 0x108: Next State Register */
        __RW uint32_t ACTION;                  /* 0x10C: Action Register */
        __R  uint8_t  RESERVED0[16];           /* 0x110 - 0x11F: Reserved */
        __RW uint32_t COUNTCOMP;               /* 0x120: Counter Compare Register */
        __R  uint8_t  RESERVED1[12];           /* 0x124 - 0x12F: Reserved */
        __RW uint32_t EXTMASK;                 /* 0x130: External Mask Register */
        __RW uint32_t EXTCOMP;                 /* 0x134: External Compare Register */
        __R  uint8_t  RESERVED2[8];            /* 0x138 - 0x13F: Reserved */
        __RW uint32_t SIGMASK;                 /* 0x140: Signal Mask Register */
        __RW uint32_t COMPEN;                  /* 0x144: Compare Enable register */
        __R  uint8_t  RESERVED3[56];           /* 0x148 - 0x17F: Reserved */
        __RW uint32_t SIGCOMP0;                /* 0x180: Signal Compare Register0 */
        __RW uint32_t SIGCOMP1;                /* 0x184: Signal Compare Register1 */
        __RW uint32_t SIGCOMP2;                /* 0x188: Signal Compare Register2 */
        __RW uint32_t SIGCOMP3;                /* 0x18C: Signal Compare Register3 */
        __R  uint8_t  RESERVED4[112];          /* 0x190 - 0x1FF: Reserved */
    } STATE[5];
    __R  uint8_t  RESERVED7[2480];             /* 0x600 - 0xFAF: Reserved */
    __RW uint32_t LAR;                         /* 0xFB0: Lock Access Register */
} LOBS_Type;


/* Bitfield definition for register: CTRL */
/*
 * RUN (RW)
 *
 * Run control.
 * 0 LOBS disabled. Register programming permitted.
 * 1 LOBS enabled
 */
#define LOBS_CTRL_RUN_MASK (0x1U)
#define LOBS_CTRL_RUN_SHIFT (0U)
#define LOBS_CTRL_RUN_SET(x) (((uint32_t)(x) << LOBS_CTRL_RUN_SHIFT) & LOBS_CTRL_RUN_MASK)
#define LOBS_CTRL_RUN_GET(x) (((uint32_t)(x) & LOBS_CTRL_RUN_MASK) >> LOBS_CTRL_RUN_SHIFT)

/* Bitfield definition for register: STREAMCTRL */
/*
 * SEL (RW)
 *
 * Signal Group Select
 * 0 128bit from one group
 * 1 from 2 groups, 4bit in each group
 */
#define LOBS_STREAMCTRL_SEL_MASK (0x100U)
#define LOBS_STREAMCTRL_SEL_SHIFT (8U)
#define LOBS_STREAMCTRL_SEL_SET(x) (((uint32_t)(x) << LOBS_STREAMCTRL_SEL_SHIFT) & LOBS_STREAMCTRL_SEL_MASK)
#define LOBS_STREAMCTRL_SEL_GET(x) (((uint32_t)(x) & LOBS_STREAMCTRL_SEL_MASK) >> LOBS_STREAMCTRL_SEL_SHIFT)

/*
 * FULL_CLEAR (RW)
 *
 * FIFO Overflow Clear
 */
#define LOBS_STREAMCTRL_FULL_CLEAR_MASK (0x80U)
#define LOBS_STREAMCTRL_FULL_CLEAR_SHIFT (7U)
#define LOBS_STREAMCTRL_FULL_CLEAR_SET(x) (((uint32_t)(x) << LOBS_STREAMCTRL_FULL_CLEAR_SHIFT) & LOBS_STREAMCTRL_FULL_CLEAR_MASK)
#define LOBS_STREAMCTRL_FULL_CLEAR_GET(x) (((uint32_t)(x) & LOBS_STREAMCTRL_FULL_CLEAR_MASK) >> LOBS_STREAMCTRL_FULL_CLEAR_SHIFT)

/*
 * SAMPLE (RW)
 *
 * Sample Rate
 * 4 take one every 5
 * 5 take one every 6
 * 6 take one every 7
 */
#define LOBS_STREAMCTRL_SAMPLE_MASK (0x78U)
#define LOBS_STREAMCTRL_SAMPLE_SHIFT (3U)
#define LOBS_STREAMCTRL_SAMPLE_SET(x) (((uint32_t)(x) << LOBS_STREAMCTRL_SAMPLE_SHIFT) & LOBS_STREAMCTRL_SAMPLE_MASK)
#define LOBS_STREAMCTRL_SAMPLE_GET(x) (((uint32_t)(x) & LOBS_STREAMCTRL_SAMPLE_MASK) >> LOBS_STREAMCTRL_SAMPLE_SHIFT)

/*
 * BURST (RW)
 *
 * Burst Cfg
 * 3b011 Incr4
 * 3b101 Incr8
 * 3b111 Incr16
 */
#define LOBS_STREAMCTRL_BURST_MASK (0x7U)
#define LOBS_STREAMCTRL_BURST_SHIFT (0U)
#define LOBS_STREAMCTRL_BURST_SET(x) (((uint32_t)(x) << LOBS_STREAMCTRL_BURST_SHIFT) & LOBS_STREAMCTRL_BURST_MASK)
#define LOBS_STREAMCTRL_BURST_GET(x) (((uint32_t)(x) & LOBS_STREAMCTRL_BURST_MASK) >> LOBS_STREAMCTRL_BURST_SHIFT)

/* Bitfield definition for register: PTACTION */
/*
 * TRACE (RW)
 *
 * Enables trace
 */
#define LOBS_PTACTION_TRACE_MASK (0x8U)
#define LOBS_PTACTION_TRACE_SHIFT (3U)
#define LOBS_PTACTION_TRACE_SET(x) (((uint32_t)(x) << LOBS_PTACTION_TRACE_SHIFT) & LOBS_PTACTION_TRACE_MASK)
#define LOBS_PTACTION_TRACE_GET(x) (((uint32_t)(x) & LOBS_PTACTION_TRACE_MASK) >> LOBS_PTACTION_TRACE_SHIFT)

/* Bitfield definition for register: STARTADDR */
/*
 * ADDR (RW)
 *
 * Start address
 */
#define LOBS_STARTADDR_ADDR_MASK (0xFFFFFFFFUL)
#define LOBS_STARTADDR_ADDR_SHIFT (0U)
#define LOBS_STARTADDR_ADDR_SET(x) (((uint32_t)(x) << LOBS_STARTADDR_ADDR_SHIFT) & LOBS_STARTADDR_ADDR_MASK)
#define LOBS_STARTADDR_ADDR_GET(x) (((uint32_t)(x) & LOBS_STARTADDR_ADDR_MASK) >> LOBS_STARTADDR_ADDR_SHIFT)

/* Bitfield definition for register: ENDADDR */
/*
 * ADDR (RW)
 *
 * End address
 */
#define LOBS_ENDADDR_ADDR_MASK (0xFFFFFFFFUL)
#define LOBS_ENDADDR_ADDR_SHIFT (0U)
#define LOBS_ENDADDR_ADDR_SET(x) (((uint32_t)(x) << LOBS_ENDADDR_ADDR_SHIFT) & LOBS_ENDADDR_ADDR_MASK)
#define LOBS_ENDADDR_ADDR_GET(x) (((uint32_t)(x) & LOBS_ENDADDR_ADDR_MASK) >> LOBS_ENDADDR_ADDR_SHIFT)

/* Bitfield definition for register: CTSR */
/*
 * FINALSTATE (RO)
 *
 * 0 LOBS is still tracing.
 * 1 Indicates that the LOBS has stopped advancing Trigger States and stopped trace.
 * FINALSTATE can be set by TRIGCTRL.COUNTBRK reaching the final loop count, or by programming NEXTSTATEto zero
 */
#define LOBS_CTSR_FINALSTATE_MASK (0x80000000UL)
#define LOBS_CTSR_FINALSTATE_SHIFT (31U)
#define LOBS_CTSR_FINALSTATE_GET(x) (((uint32_t)(x) & LOBS_CTSR_FINALSTATE_MASK) >> LOBS_CTSR_FINALSTATE_SHIFT)

/*
 * CTSR (RO)
 *
 * Reads current Trigger State. This is a one-hot encoded field.
 * When CTRL.RUN:
 * 0 RAZ.
 * 1 Returns current Trigger State.
 * If FINALSTATE is 1, then the CTSR field gives the Trigger State when FINALSTATE became 1
 */
#define LOBS_CTSR_CTSR_MASK (0x1FU)
#define LOBS_CTSR_CTSR_SHIFT (0U)
#define LOBS_CTSR_CTSR_GET(x) (((uint32_t)(x) & LOBS_CTSR_CTSR_MASK) >> LOBS_CTSR_CTSR_SHIFT)

/* Bitfield definition for register: CCVR */
/*
 * CCVR (RO)
 *
 * Returns the counter value when the CTSR was last read. If the CTSR has never been read, then the value in the CCVR is undefined
 */
#define LOBS_CCVR_CCVR_MASK (0xFFFFFFFFUL)
#define LOBS_CCVR_CCVR_SHIFT (0U)
#define LOBS_CCVR_CCVR_GET(x) (((uint32_t)(x) & LOBS_CCVR_CCVR_MASK) >> LOBS_CCVR_CCVR_SHIFT)

/* Bitfield definition for register: CAVR */
/*
 * TRACE (RO)
 *
 * Trace active.
 * 0b0 Trace is not active.
 * 0b1 Trace is active.
 */
#define LOBS_CAVR_TRACE_MASK (0x8U)
#define LOBS_CAVR_TRACE_SHIFT (3U)
#define LOBS_CAVR_TRACE_GET(x) (((uint32_t)(x) & LOBS_CAVR_TRACE_MASK) >> LOBS_CAVR_TRACE_SHIFT)

/* Bitfield definition for register: FIFOSTATE */
/*
 * FULL (RO)
 *
 * FIFO full
 */
#define LOBS_FIFOSTATE_FULL_MASK (0x2U)
#define LOBS_FIFOSTATE_FULL_SHIFT (1U)
#define LOBS_FIFOSTATE_FULL_GET(x) (((uint32_t)(x) & LOBS_FIFOSTATE_FULL_MASK) >> LOBS_FIFOSTATE_FULL_SHIFT)

/*
 * EMPTY (RO)
 *
 * FIFO empty
 */
#define LOBS_FIFOSTATE_EMPTY_MASK (0x1U)
#define LOBS_FIFOSTATE_EMPTY_SHIFT (0U)
#define LOBS_FIFOSTATE_EMPTY_GET(x) (((uint32_t)(x) & LOBS_FIFOSTATE_EMPTY_MASK) >> LOBS_FIFOSTATE_EMPTY_SHIFT)

/* Bitfield definition for register: FINALADDR */
/*
 * ADDR (RW)
 *
 * Final address
 */
#define LOBS_FINALADDR_ADDR_MASK (0xFFFFFFFFUL)
#define LOBS_FINALADDR_ADDR_SHIFT (0U)
#define LOBS_FINALADDR_ADDR_SET(x) (((uint32_t)(x) << LOBS_FINALADDR_ADDR_SHIFT) & LOBS_FINALADDR_ADDR_MASK)
#define LOBS_FINALADDR_ADDR_GET(x) (((uint32_t)(x) & LOBS_FINALADDR_ADDR_MASK) >> LOBS_FINALADDR_ADDR_SHIFT)

/* Bitfield definition for register: GRPSELA */
/*
 * NUM2 (RW)
 *
 * Select sample group number2
 */
#define LOBS_GRPSELA_NUM2_MASK (0xF0U)
#define LOBS_GRPSELA_NUM2_SHIFT (4U)
#define LOBS_GRPSELA_NUM2_SET(x) (((uint32_t)(x) << LOBS_GRPSELA_NUM2_SHIFT) & LOBS_GRPSELA_NUM2_MASK)
#define LOBS_GRPSELA_NUM2_GET(x) (((uint32_t)(x) & LOBS_GRPSELA_NUM2_MASK) >> LOBS_GRPSELA_NUM2_SHIFT)

/*
 * NUM1 (RW)
 *
 * Select sample group number1
 */
#define LOBS_GRPSELA_NUM1_MASK (0xFU)
#define LOBS_GRPSELA_NUM1_SHIFT (0U)
#define LOBS_GRPSELA_NUM1_SET(x) (((uint32_t)(x) << LOBS_GRPSELA_NUM1_SHIFT) & LOBS_GRPSELA_NUM1_MASK)
#define LOBS_GRPSELA_NUM1_GET(x) (((uint32_t)(x) & LOBS_GRPSELA_NUM1_MASK) >> LOBS_GRPSELA_NUM1_SHIFT)

/* Bitfield definition for register: GRPENA */
/*
 * EN2 (RW)
 *
 * Enable sample group number2
 */
#define LOBS_GRPENA_EN2_MASK (0x2U)
#define LOBS_GRPENA_EN2_SHIFT (1U)
#define LOBS_GRPENA_EN2_SET(x) (((uint32_t)(x) << LOBS_GRPENA_EN2_SHIFT) & LOBS_GRPENA_EN2_MASK)
#define LOBS_GRPENA_EN2_GET(x) (((uint32_t)(x) & LOBS_GRPENA_EN2_MASK) >> LOBS_GRPENA_EN2_SHIFT)

/*
 * EN1 (RW)
 *
 * Enable sample group number1
 */
#define LOBS_GRPENA_EN1_MASK (0x1U)
#define LOBS_GRPENA_EN1_SHIFT (0U)
#define LOBS_GRPENA_EN1_SET(x) (((uint32_t)(x) << LOBS_GRPENA_EN1_SHIFT) & LOBS_GRPENA_EN1_MASK)
#define LOBS_GRPENA_EN1_GET(x) (((uint32_t)(x) & LOBS_GRPENA_EN1_MASK) >> LOBS_GRPENA_EN1_SHIFT)

/* Bitfield definition for register: SIGSELA1 */
/*
 * NUM4 (RW)
 *
 * Select sample signal bit number4 in first group
 */
#define LOBS_SIGSELA1_NUM4_MASK (0xFF000000UL)
#define LOBS_SIGSELA1_NUM4_SHIFT (24U)
#define LOBS_SIGSELA1_NUM4_SET(x) (((uint32_t)(x) << LOBS_SIGSELA1_NUM4_SHIFT) & LOBS_SIGSELA1_NUM4_MASK)
#define LOBS_SIGSELA1_NUM4_GET(x) (((uint32_t)(x) & LOBS_SIGSELA1_NUM4_MASK) >> LOBS_SIGSELA1_NUM4_SHIFT)

/*
 * NUM3 (RW)
 *
 * Select sample signal bit number3 in first group
 */
#define LOBS_SIGSELA1_NUM3_MASK (0xFF0000UL)
#define LOBS_SIGSELA1_NUM3_SHIFT (16U)
#define LOBS_SIGSELA1_NUM3_SET(x) (((uint32_t)(x) << LOBS_SIGSELA1_NUM3_SHIFT) & LOBS_SIGSELA1_NUM3_MASK)
#define LOBS_SIGSELA1_NUM3_GET(x) (((uint32_t)(x) & LOBS_SIGSELA1_NUM3_MASK) >> LOBS_SIGSELA1_NUM3_SHIFT)

/*
 * NUM2 (RW)
 *
 * Select sample signal bit number2 in first group
 */
#define LOBS_SIGSELA1_NUM2_MASK (0xFF00U)
#define LOBS_SIGSELA1_NUM2_SHIFT (8U)
#define LOBS_SIGSELA1_NUM2_SET(x) (((uint32_t)(x) << LOBS_SIGSELA1_NUM2_SHIFT) & LOBS_SIGSELA1_NUM2_MASK)
#define LOBS_SIGSELA1_NUM2_GET(x) (((uint32_t)(x) & LOBS_SIGSELA1_NUM2_MASK) >> LOBS_SIGSELA1_NUM2_SHIFT)

/*
 * NUM1 (RW)
 *
 * Select sample signal bit number1 in first group
 */
#define LOBS_SIGSELA1_NUM1_MASK (0xFFU)
#define LOBS_SIGSELA1_NUM1_SHIFT (0U)
#define LOBS_SIGSELA1_NUM1_SET(x) (((uint32_t)(x) << LOBS_SIGSELA1_NUM1_SHIFT) & LOBS_SIGSELA1_NUM1_MASK)
#define LOBS_SIGSELA1_NUM1_GET(x) (((uint32_t)(x) & LOBS_SIGSELA1_NUM1_MASK) >> LOBS_SIGSELA1_NUM1_SHIFT)

/* Bitfield definition for register: SIGSELA2 */
/*
 * NUM4 (RW)
 *
 * Select sample signal bit number4 in second group
 */
#define LOBS_SIGSELA2_NUM4_MASK (0xFF000000UL)
#define LOBS_SIGSELA2_NUM4_SHIFT (24U)
#define LOBS_SIGSELA2_NUM4_SET(x) (((uint32_t)(x) << LOBS_SIGSELA2_NUM4_SHIFT) & LOBS_SIGSELA2_NUM4_MASK)
#define LOBS_SIGSELA2_NUM4_GET(x) (((uint32_t)(x) & LOBS_SIGSELA2_NUM4_MASK) >> LOBS_SIGSELA2_NUM4_SHIFT)

/*
 * NUM3 (RW)
 *
 * Select sample signal bit number3 in second group
 */
#define LOBS_SIGSELA2_NUM3_MASK (0xFF0000UL)
#define LOBS_SIGSELA2_NUM3_SHIFT (16U)
#define LOBS_SIGSELA2_NUM3_SET(x) (((uint32_t)(x) << LOBS_SIGSELA2_NUM3_SHIFT) & LOBS_SIGSELA2_NUM3_MASK)
#define LOBS_SIGSELA2_NUM3_GET(x) (((uint32_t)(x) & LOBS_SIGSELA2_NUM3_MASK) >> LOBS_SIGSELA2_NUM3_SHIFT)

/*
 * NUM2 (RW)
 *
 * Select sample signal bit number2 in second group
 */
#define LOBS_SIGSELA2_NUM2_MASK (0xFF00U)
#define LOBS_SIGSELA2_NUM2_SHIFT (8U)
#define LOBS_SIGSELA2_NUM2_SET(x) (((uint32_t)(x) << LOBS_SIGSELA2_NUM2_SHIFT) & LOBS_SIGSELA2_NUM2_MASK)
#define LOBS_SIGSELA2_NUM2_GET(x) (((uint32_t)(x) & LOBS_SIGSELA2_NUM2_MASK) >> LOBS_SIGSELA2_NUM2_SHIFT)

/*
 * NUM1 (RW)
 *
 * Select sample signal bit number1 in second group
 */
#define LOBS_SIGSELA2_NUM1_MASK (0xFFU)
#define LOBS_SIGSELA2_NUM1_SHIFT (0U)
#define LOBS_SIGSELA2_NUM1_SET(x) (((uint32_t)(x) << LOBS_SIGSELA2_NUM1_SHIFT) & LOBS_SIGSELA2_NUM1_MASK)
#define LOBS_SIGSELA2_NUM1_GET(x) (((uint32_t)(x) & LOBS_SIGSELA2_NUM1_MASK) >> LOBS_SIGSELA2_NUM1_SHIFT)

/* Bitfield definition for register: SIGENA */
/*
 * EN2 (RW)
 *
 * Enable sample signal number2
 */
#define LOBS_SIGENA_EN2_MASK (0xF0U)
#define LOBS_SIGENA_EN2_SHIFT (4U)
#define LOBS_SIGENA_EN2_SET(x) (((uint32_t)(x) << LOBS_SIGENA_EN2_SHIFT) & LOBS_SIGENA_EN2_MASK)
#define LOBS_SIGENA_EN2_GET(x) (((uint32_t)(x) & LOBS_SIGENA_EN2_MASK) >> LOBS_SIGENA_EN2_SHIFT)

/*
 * EN1 (RW)
 *
 * Enable sample signal number1
 */
#define LOBS_SIGENA_EN1_MASK (0xFU)
#define LOBS_SIGENA_EN1_SHIFT (0U)
#define LOBS_SIGENA_EN1_SET(x) (((uint32_t)(x) << LOBS_SIGENA_EN1_SHIFT) & LOBS_SIGENA_EN1_MASK)
#define LOBS_SIGENA_EN1_GET(x) (((uint32_t)(x) & LOBS_SIGENA_EN1_MASK) >> LOBS_SIGENA_EN1_SHIFT)

/* Bitfield definition for register of struct array STATE: SIGSEL */
/*
 * EN (RW)
 *
 * Selects Signal Group.
 * 0x1 Selects Signal Group 0.
 * 0x2 Selects Signal Group 1.
 * 0x4 Selects Signal Group 2.
 * 0x8 Selects Signal Group 3.
 * 0x10 Selects Signal Group 4.
 * 0x20 Selects Signal Group 5.
 * 0x40 Selects Signal Group 6.
 * 0x80 Selects Signal Group 7.
 * 0x100 Selects Signal Group 8.
 * 0x200 Selects Signal Group 9.
 * 0x400 Selects Signal Group 10.
 * 0x800 Selects Signal Group 11.
 */
#define LOBS_STATE_SIGSEL_EN_MASK (0xFFFU)
#define LOBS_STATE_SIGSEL_EN_SHIFT (0U)
#define LOBS_STATE_SIGSEL_EN_SET(x) (((uint32_t)(x) << LOBS_STATE_SIGSEL_EN_SHIFT) & LOBS_STATE_SIGSEL_EN_MASK)
#define LOBS_STATE_SIGSEL_EN_GET(x) (((uint32_t)(x) & LOBS_STATE_SIGSEL_EN_MASK) >> LOBS_STATE_SIGSEL_EN_SHIFT)

/* Bitfield definition for register of struct array STATE: TRIGCTRL */
/*
 * TRACE (RW)
 *
 * Trace capture control.
 * 0b10 Trace is captured every ELACLK cycle.
 * others Reserved.
 */
#define LOBS_STATE_TRIGCTRL_TRACE_MASK (0xC0U)
#define LOBS_STATE_TRIGCTRL_TRACE_SHIFT (6U)
#define LOBS_STATE_TRIGCTRL_TRACE_SET(x) (((uint32_t)(x) << LOBS_STATE_TRIGCTRL_TRACE_SHIFT) & LOBS_STATE_TRIGCTRL_TRACE_MASK)
#define LOBS_STATE_TRIGCTRL_TRACE_GET(x) (((uint32_t)(x) & LOBS_STATE_TRIGCTRL_TRACE_MASK) >> LOBS_STATE_TRIGCTRL_TRACE_SHIFT)

/*
 * COMPSEL (RW)
 *
 * Comparison mode. Acts as both a counter enable and a select for the comparison mode.
 * 0b0 Disable counters and select Trigger Signal Comparison mode.
 * 0b1 Enable counters and select Trigger Counter Comparison mode.
 */
#define LOBS_STATE_TRIGCTRL_COMPSEL_MASK (0x8U)
#define LOBS_STATE_TRIGCTRL_COMPSEL_SHIFT (3U)
#define LOBS_STATE_TRIGCTRL_COMPSEL_SET(x) (((uint32_t)(x) << LOBS_STATE_TRIGCTRL_COMPSEL_SHIFT) & LOBS_STATE_TRIGCTRL_COMPSEL_MASK)
#define LOBS_STATE_TRIGCTRL_COMPSEL_GET(x) (((uint32_t)(x) & LOBS_STATE_TRIGCTRL_COMPSEL_MASK) >> LOBS_STATE_TRIGCTRL_COMPSEL_SHIFT)

/*
 * COMP (RW)
 *
 * Trigger Signal Comparison type select.
 * 0b000 Trigger Signal Comparisons disabled. The enabled counters count clocks immediately after the Trigger State has been entered and generate a programmable Output Action and transition to the next Trigger State when the Counter Compare Register count is reached, that is when a Trigger Counter Comparison match occurs.
 * 0b001 Compare type is equal (==).
 * 0b010 Compare type is greater than (>).
 * 0b011 Compare type is greater than or equal (>=).
 * 0b101 Compare type is not equal (!=).
 * 0b110 Compare type is less than (<).
 * 0b111 Compare type is less than or equal (<=).
 */
#define LOBS_STATE_TRIGCTRL_COMP_MASK (0x7U)
#define LOBS_STATE_TRIGCTRL_COMP_SHIFT (0U)
#define LOBS_STATE_TRIGCTRL_COMP_SET(x) (((uint32_t)(x) << LOBS_STATE_TRIGCTRL_COMP_SHIFT) & LOBS_STATE_TRIGCTRL_COMP_MASK)
#define LOBS_STATE_TRIGCTRL_COMP_GET(x) (((uint32_t)(x) & LOBS_STATE_TRIGCTRL_COMP_MASK) >> LOBS_STATE_TRIGCTRL_COMP_SHIFT)

/* Bitfield definition for register of struct array STATE: NEXTSTATE */
/*
 * NEXTSTATE (RW)
 *
 * Selects the next state to move to after the Trigger Condition has been met in the current state.
 * 0x0 Do not change state. This is the final Trigger State.
 * 0x1 Selects Trigger State 0.
 * 0x2 Selects Trigger State 1.
 * 0x4 Selects Trigger State 2.
 * 0x8 Selects Trigger State 3.
 * 0x10 Selects Trigger State 4.
 */
#define LOBS_STATE_NEXTSTATE_NEXTSTATE_MASK (0x1FU)
#define LOBS_STATE_NEXTSTATE_NEXTSTATE_SHIFT (0U)
#define LOBS_STATE_NEXTSTATE_NEXTSTATE_SET(x) (((uint32_t)(x) << LOBS_STATE_NEXTSTATE_NEXTSTATE_SHIFT) & LOBS_STATE_NEXTSTATE_NEXTSTATE_MASK)
#define LOBS_STATE_NEXTSTATE_NEXTSTATE_GET(x) (((uint32_t)(x) & LOBS_STATE_NEXTSTATE_NEXTSTATE_MASK) >> LOBS_STATE_NEXTSTATE_NEXTSTATE_SHIFT)

/* Bitfield definition for register of struct array STATE: ACTION */
/*
 * TRACE (RW)
 *
 * Trace active.
 * 0b0 Trace disable.
 * 0b1 Trace enable.
 */
#define LOBS_STATE_ACTION_TRACE_MASK (0x8U)
#define LOBS_STATE_ACTION_TRACE_SHIFT (3U)
#define LOBS_STATE_ACTION_TRACE_SET(x) (((uint32_t)(x) << LOBS_STATE_ACTION_TRACE_SHIFT) & LOBS_STATE_ACTION_TRACE_MASK)
#define LOBS_STATE_ACTION_TRACE_GET(x) (((uint32_t)(x) & LOBS_STATE_ACTION_TRACE_MASK) >> LOBS_STATE_ACTION_TRACE_SHIFT)

/* Bitfield definition for register of struct array STATE: COUNTCOMP */
/*
 * VALUE (RW)
 *
 * A value that, when reached in the associated up-counter for this Trigger State, causes a Trigger Counter Comparison match to occur.
 */
#define LOBS_STATE_COUNTCOMP_VALUE_MASK (0xFFFFFFFFUL)
#define LOBS_STATE_COUNTCOMP_VALUE_SHIFT (0U)
#define LOBS_STATE_COUNTCOMP_VALUE_SET(x) (((uint32_t)(x) << LOBS_STATE_COUNTCOMP_VALUE_SHIFT) & LOBS_STATE_COUNTCOMP_VALUE_MASK)
#define LOBS_STATE_COUNTCOMP_VALUE_GET(x) (((uint32_t)(x) & LOBS_STATE_COUNTCOMP_VALUE_MASK) >> LOBS_STATE_COUNTCOMP_VALUE_SHIFT)

/* Bitfield definition for register of struct array STATE: EXTMASK */
/*
 * VALUE (RW)
 *
 * External Mask
 */
#define LOBS_STATE_EXTMASK_VALUE_MASK (0xFFFFFFFFUL)
#define LOBS_STATE_EXTMASK_VALUE_SHIFT (0U)
#define LOBS_STATE_EXTMASK_VALUE_SET(x) (((uint32_t)(x) << LOBS_STATE_EXTMASK_VALUE_SHIFT) & LOBS_STATE_EXTMASK_VALUE_MASK)
#define LOBS_STATE_EXTMASK_VALUE_GET(x) (((uint32_t)(x) & LOBS_STATE_EXTMASK_VALUE_MASK) >> LOBS_STATE_EXTMASK_VALUE_SHIFT)

/* Bitfield definition for register of struct array STATE: EXTCOMP */
/*
 * VALUE (RW)
 *
 * External Compare
 */
#define LOBS_STATE_EXTCOMP_VALUE_MASK (0xFFFFFFFFUL)
#define LOBS_STATE_EXTCOMP_VALUE_SHIFT (0U)
#define LOBS_STATE_EXTCOMP_VALUE_SET(x) (((uint32_t)(x) << LOBS_STATE_EXTCOMP_VALUE_SHIFT) & LOBS_STATE_EXTCOMP_VALUE_MASK)
#define LOBS_STATE_EXTCOMP_VALUE_GET(x) (((uint32_t)(x) & LOBS_STATE_EXTCOMP_VALUE_MASK) >> LOBS_STATE_EXTCOMP_VALUE_SHIFT)

/* Bitfield definition for register of struct array STATE: SIGMASK */
/*
 * NUM3 (RW)
 *
 * Select compare signal number3
 */
#define LOBS_STATE_SIGMASK_NUM3_MASK (0xFF000000UL)
#define LOBS_STATE_SIGMASK_NUM3_SHIFT (24U)
#define LOBS_STATE_SIGMASK_NUM3_SET(x) (((uint32_t)(x) << LOBS_STATE_SIGMASK_NUM3_SHIFT) & LOBS_STATE_SIGMASK_NUM3_MASK)
#define LOBS_STATE_SIGMASK_NUM3_GET(x) (((uint32_t)(x) & LOBS_STATE_SIGMASK_NUM3_MASK) >> LOBS_STATE_SIGMASK_NUM3_SHIFT)

/*
 * NUM2 (RW)
 *
 * Select compare signal number2
 */
#define LOBS_STATE_SIGMASK_NUM2_MASK (0xFF0000UL)
#define LOBS_STATE_SIGMASK_NUM2_SHIFT (16U)
#define LOBS_STATE_SIGMASK_NUM2_SET(x) (((uint32_t)(x) << LOBS_STATE_SIGMASK_NUM2_SHIFT) & LOBS_STATE_SIGMASK_NUM2_MASK)
#define LOBS_STATE_SIGMASK_NUM2_GET(x) (((uint32_t)(x) & LOBS_STATE_SIGMASK_NUM2_MASK) >> LOBS_STATE_SIGMASK_NUM2_SHIFT)

/*
 * NUM1 (RW)
 *
 * Select compare signal number1
 */
#define LOBS_STATE_SIGMASK_NUM1_MASK (0xFF00U)
#define LOBS_STATE_SIGMASK_NUM1_SHIFT (8U)
#define LOBS_STATE_SIGMASK_NUM1_SET(x) (((uint32_t)(x) << LOBS_STATE_SIGMASK_NUM1_SHIFT) & LOBS_STATE_SIGMASK_NUM1_MASK)
#define LOBS_STATE_SIGMASK_NUM1_GET(x) (((uint32_t)(x) & LOBS_STATE_SIGMASK_NUM1_MASK) >> LOBS_STATE_SIGMASK_NUM1_SHIFT)

/*
 * NUM0 (RW)
 *
 * Select compare signal number0
 */
#define LOBS_STATE_SIGMASK_NUM0_MASK (0xFFU)
#define LOBS_STATE_SIGMASK_NUM0_SHIFT (0U)
#define LOBS_STATE_SIGMASK_NUM0_SET(x) (((uint32_t)(x) << LOBS_STATE_SIGMASK_NUM0_SHIFT) & LOBS_STATE_SIGMASK_NUM0_MASK)
#define LOBS_STATE_SIGMASK_NUM0_GET(x) (((uint32_t)(x) & LOBS_STATE_SIGMASK_NUM0_MASK) >> LOBS_STATE_SIGMASK_NUM0_SHIFT)

/* Bitfield definition for register of struct array STATE: COMPEN */
/*
 * EN (RW)
 *
 * Select compare signal number0-3
 */
#define LOBS_STATE_COMPEN_EN_MASK (0xFU)
#define LOBS_STATE_COMPEN_EN_SHIFT (0U)
#define LOBS_STATE_COMPEN_EN_SET(x) (((uint32_t)(x) << LOBS_STATE_COMPEN_EN_SHIFT) & LOBS_STATE_COMPEN_EN_MASK)
#define LOBS_STATE_COMPEN_EN_GET(x) (((uint32_t)(x) & LOBS_STATE_COMPEN_EN_MASK) >> LOBS_STATE_COMPEN_EN_SHIFT)

/* Bitfield definition for register of struct array STATE: SIGCOMP0 */
/*
 * VALUE0 (RW)
 *
 * Compare golden value for Signal Group signals[31:0].
 */
#define LOBS_STATE_SIGCOMP0_VALUE0_MASK (0xFFFFFFFFUL)
#define LOBS_STATE_SIGCOMP0_VALUE0_SHIFT (0U)
#define LOBS_STATE_SIGCOMP0_VALUE0_SET(x) (((uint32_t)(x) << LOBS_STATE_SIGCOMP0_VALUE0_SHIFT) & LOBS_STATE_SIGCOMP0_VALUE0_MASK)
#define LOBS_STATE_SIGCOMP0_VALUE0_GET(x) (((uint32_t)(x) & LOBS_STATE_SIGCOMP0_VALUE0_MASK) >> LOBS_STATE_SIGCOMP0_VALUE0_SHIFT)

/* Bitfield definition for register of struct array STATE: SIGCOMP1 */
/*
 * VALUE1 (RW)
 *
 * Compare golden value for Signal Group signals[63:32].
 */
#define LOBS_STATE_SIGCOMP1_VALUE1_MASK (0xFFFFFFFFUL)
#define LOBS_STATE_SIGCOMP1_VALUE1_SHIFT (0U)
#define LOBS_STATE_SIGCOMP1_VALUE1_SET(x) (((uint32_t)(x) << LOBS_STATE_SIGCOMP1_VALUE1_SHIFT) & LOBS_STATE_SIGCOMP1_VALUE1_MASK)
#define LOBS_STATE_SIGCOMP1_VALUE1_GET(x) (((uint32_t)(x) & LOBS_STATE_SIGCOMP1_VALUE1_MASK) >> LOBS_STATE_SIGCOMP1_VALUE1_SHIFT)

/* Bitfield definition for register of struct array STATE: SIGCOMP2 */
/*
 * VALUE2 (RW)
 *
 * Compare golden value for Signal Group signals[95:64].
 */
#define LOBS_STATE_SIGCOMP2_VALUE2_MASK (0xFFFFFFFFUL)
#define LOBS_STATE_SIGCOMP2_VALUE2_SHIFT (0U)
#define LOBS_STATE_SIGCOMP2_VALUE2_SET(x) (((uint32_t)(x) << LOBS_STATE_SIGCOMP2_VALUE2_SHIFT) & LOBS_STATE_SIGCOMP2_VALUE2_MASK)
#define LOBS_STATE_SIGCOMP2_VALUE2_GET(x) (((uint32_t)(x) & LOBS_STATE_SIGCOMP2_VALUE2_MASK) >> LOBS_STATE_SIGCOMP2_VALUE2_SHIFT)

/* Bitfield definition for register of struct array STATE: SIGCOMP3 */
/*
 * VALUE3 (RW)
 *
 * Compare golden value for Signal Group signals[127:96].
 */
#define LOBS_STATE_SIGCOMP3_VALUE3_MASK (0xFFFFFFFFUL)
#define LOBS_STATE_SIGCOMP3_VALUE3_SHIFT (0U)
#define LOBS_STATE_SIGCOMP3_VALUE3_SET(x) (((uint32_t)(x) << LOBS_STATE_SIGCOMP3_VALUE3_SHIFT) & LOBS_STATE_SIGCOMP3_VALUE3_MASK)
#define LOBS_STATE_SIGCOMP3_VALUE3_GET(x) (((uint32_t)(x) & LOBS_STATE_SIGCOMP3_VALUE3_MASK) >> LOBS_STATE_SIGCOMP3_VALUE3_SHIFT)

/* Bitfield definition for register: LAR */
/*
 * VALUE (RW)
 *
 * Lock Access Value
 */
#define LOBS_LAR_VALUE_MASK (0xFFFFFFFFUL)
#define LOBS_LAR_VALUE_SHIFT (0U)
#define LOBS_LAR_VALUE_SET(x) (((uint32_t)(x) << LOBS_LAR_VALUE_SHIFT) & LOBS_LAR_VALUE_MASK)
#define LOBS_LAR_VALUE_GET(x) (((uint32_t)(x) & LOBS_LAR_VALUE_MASK) >> LOBS_LAR_VALUE_SHIFT)



/* STATE register group index macro definition */
#define LOBS_STATE_0 (0UL)
#define LOBS_STATE_1 (1UL)
#define LOBS_STATE_2 (2UL)
#define LOBS_STATE_3 (3UL)
#define LOBS_STATE_4 (4UL)


#endif /* HPM_LOBS_H */
