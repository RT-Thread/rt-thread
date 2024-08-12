/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_VSC_H
#define HPM_VSC_H

typedef struct {
    __RW uint32_t ABC_MODE;                    /* 0x0: abc mode */
    __RW uint32_t ADC_CHAN_ASSIGN;             /* 0x4: assign adc_chan for value_a/b/c */
    __RW uint32_t VALUE_A_DATA_OPT;            /* 0x8: value_a data operation mode */
    __R  uint8_t  RESERVED0[4];                /* 0xC - 0xF: Reserved */
    __RW uint32_t VALUE_B_DATA_OPT;            /* 0x10: value_b data operation mode */
    __R  uint8_t  RESERVED1[4];                /* 0x14 - 0x17: Reserved */
    __RW uint32_t VALUE_C_DATA_OPT;            /* 0x18: value_c data operation mode */
    __R  uint8_t  RESERVED2[4];                /* 0x1C - 0x1F: Reserved */
    __RW uint32_t VALUE_A_OFFSET;              /* 0x20: value_a offset */
    __RW uint32_t VALUE_B_OFFSET;              /* 0x24: value_b_offset */
    __RW uint32_t VALUE_C_OFFSET;              /* 0x28: value_c offset */
    __RW uint32_t IRQ_STATUS;                  /* 0x2C: irq status */
    __RW uint32_t VALUE_A_SW;                  /* 0x30: value_a software inject value */
    __RW uint32_t VALUE_B_SW;                  /* 0x34: value_b software inject value */
    __RW uint32_t VALUE_C_SW;                  /* 0x38: value_c software inject value */
    __W  uint32_t VALUE_SW_READY;              /* 0x3C: software inject value_a/value_b/value_c ready */
    __W  uint32_t TRIGGER_SW;                  /* 0x40: software trigger event */
    __RW uint32_t TIMELOCK;                    /* 0x44: timestamp mode and postion capture ctrl */
    __RW uint32_t POSITION_SW;                 /* 0x48: position software inject value */
    __RW uint32_t ADC_WAIT_CYCLE;              /* 0x4C: adc wait cycle after trigger adc capture event */
    __RW uint32_t POS_WAIT_CYCLE;              /* 0x50: pos wait cycle after trigger adc capture event */
    __RW uint32_t IRQ_ENABLE;                  /* 0x54: irq bit enable */
    __RW uint32_t ADC_PHASE_TOLERATE;          /* 0x58: adc phase tolerate */
    __RW uint32_t POS_POLE;                    /* 0x5C: position pole num */
    __R  uint8_t  RESERVED3[160];              /* 0x60 - 0xFF: Reserved */
    __R  uint32_t ID_POSEDGE;                  /* 0x100: posedge order Id value */
    __R  uint32_t IQ_POSEDGE;                  /* 0x104: posedge order Iq value */
    __R  uint32_t ID_NEGEDGE;                  /* 0x108: negedge order Id value */
    __R  uint32_t IQ_NEGEDGE;                  /* 0x10C: negedge order Iq value */
    __R  uint32_t ALPHA_POSEDGE;               /* 0x110: posedge order alpha value */
    __R  uint32_t BETA_POSEDGE;                /* 0x114: posedge order beta value */
    __R  uint32_t ALPHA_NEGEDGE;               /* 0x118: negedge order alpha value */
    __R  uint32_t BETA_NEGEDGE;                /* 0x11C: negedge order beta value */
    __R  uint32_t TIMESTAMP_LOCKED;            /* 0x120: timestamp_locked */
    __R  uint32_t DEBUG_STATUS0;               /* 0x124: debug_status0 */
} VSC_Type;


/* Bitfield definition for register: ABC_MODE */
/*
 * PHASE_ABSENT_MODE (RW)
 *
 * whether using value_a and value_b instead of three phase
 */
#define VSC_ABC_MODE_PHASE_ABSENT_MODE_MASK (0x80000000UL)
#define VSC_ABC_MODE_PHASE_ABSENT_MODE_SHIFT (31U)
#define VSC_ABC_MODE_PHASE_ABSENT_MODE_SET(x) (((uint32_t)(x) << VSC_ABC_MODE_PHASE_ABSENT_MODE_SHIFT) & VSC_ABC_MODE_PHASE_ABSENT_MODE_MASK)
#define VSC_ABC_MODE_PHASE_ABSENT_MODE_GET(x) (((uint32_t)(x) & VSC_ABC_MODE_PHASE_ABSENT_MODE_MASK) >> VSC_ABC_MODE_PHASE_ABSENT_MODE_SHIFT)

/*
 * VALUE_C_WIDTH (RW)
 *
 * numbers of value_c for each convert
 */
#define VSC_ABC_MODE_VALUE_C_WIDTH_MASK (0xF000000UL)
#define VSC_ABC_MODE_VALUE_C_WIDTH_SHIFT (24U)
#define VSC_ABC_MODE_VALUE_C_WIDTH_SET(x) (((uint32_t)(x) << VSC_ABC_MODE_VALUE_C_WIDTH_SHIFT) & VSC_ABC_MODE_VALUE_C_WIDTH_MASK)
#define VSC_ABC_MODE_VALUE_C_WIDTH_GET(x) (((uint32_t)(x) & VSC_ABC_MODE_VALUE_C_WIDTH_MASK) >> VSC_ABC_MODE_VALUE_C_WIDTH_SHIFT)

/*
 * VALUE_B_WIDTH (RW)
 *
 * numbers of value_b for each convert
 */
#define VSC_ABC_MODE_VALUE_B_WIDTH_MASK (0xF00000UL)
#define VSC_ABC_MODE_VALUE_B_WIDTH_SHIFT (20U)
#define VSC_ABC_MODE_VALUE_B_WIDTH_SET(x) (((uint32_t)(x) << VSC_ABC_MODE_VALUE_B_WIDTH_SHIFT) & VSC_ABC_MODE_VALUE_B_WIDTH_MASK)
#define VSC_ABC_MODE_VALUE_B_WIDTH_GET(x) (((uint32_t)(x) & VSC_ABC_MODE_VALUE_B_WIDTH_MASK) >> VSC_ABC_MODE_VALUE_B_WIDTH_SHIFT)

/*
 * VALUE_A_WIDTH (RW)
 *
 * numbers of value_a for each convert
 */
#define VSC_ABC_MODE_VALUE_A_WIDTH_MASK (0xF0000UL)
#define VSC_ABC_MODE_VALUE_A_WIDTH_SHIFT (16U)
#define VSC_ABC_MODE_VALUE_A_WIDTH_SET(x) (((uint32_t)(x) << VSC_ABC_MODE_VALUE_A_WIDTH_SHIFT) & VSC_ABC_MODE_VALUE_A_WIDTH_MASK)
#define VSC_ABC_MODE_VALUE_A_WIDTH_GET(x) (((uint32_t)(x) & VSC_ABC_MODE_VALUE_A_WIDTH_MASK) >> VSC_ABC_MODE_VALUE_A_WIDTH_SHIFT)

/*
 * VALUE_C_LOC (RW)
 *
 * the adc index of value_c:
 * 2'b:00: resevered;
 * 2'b:01: from adc0;
 * 2'b:10: from adc1;
 * 2'b:11: from adc2;
 */
#define VSC_ABC_MODE_VALUE_C_LOC_MASK (0x3000U)
#define VSC_ABC_MODE_VALUE_C_LOC_SHIFT (12U)
#define VSC_ABC_MODE_VALUE_C_LOC_SET(x) (((uint32_t)(x) << VSC_ABC_MODE_VALUE_C_LOC_SHIFT) & VSC_ABC_MODE_VALUE_C_LOC_MASK)
#define VSC_ABC_MODE_VALUE_C_LOC_GET(x) (((uint32_t)(x) & VSC_ABC_MODE_VALUE_C_LOC_MASK) >> VSC_ABC_MODE_VALUE_C_LOC_SHIFT)

/*
 * VALUE_B_LOC (RW)
 *
 * the adc index of value_b:
 * 2'b:00: resevered;
 * 2'b:01: from adc0;
 * 2'b:10: from adc1;
 * 2'b:11: from adc2;
 */
#define VSC_ABC_MODE_VALUE_B_LOC_MASK (0x300U)
#define VSC_ABC_MODE_VALUE_B_LOC_SHIFT (8U)
#define VSC_ABC_MODE_VALUE_B_LOC_SET(x) (((uint32_t)(x) << VSC_ABC_MODE_VALUE_B_LOC_SHIFT) & VSC_ABC_MODE_VALUE_B_LOC_MASK)
#define VSC_ABC_MODE_VALUE_B_LOC_GET(x) (((uint32_t)(x) & VSC_ABC_MODE_VALUE_B_LOC_MASK) >> VSC_ABC_MODE_VALUE_B_LOC_SHIFT)

/*
 * VALUE_A_LOC (RW)
 *
 * the adc index of value_a:
 * 2'b:00: resevered;
 * 2'b:01: from adc0;
 * 2'b:10: from adc1;
 * 2'b:11: from adc2;
 */
#define VSC_ABC_MODE_VALUE_A_LOC_MASK (0x30U)
#define VSC_ABC_MODE_VALUE_A_LOC_SHIFT (4U)
#define VSC_ABC_MODE_VALUE_A_LOC_SET(x) (((uint32_t)(x) << VSC_ABC_MODE_VALUE_A_LOC_SHIFT) & VSC_ABC_MODE_VALUE_A_LOC_MASK)
#define VSC_ABC_MODE_VALUE_A_LOC_GET(x) (((uint32_t)(x) & VSC_ABC_MODE_VALUE_A_LOC_MASK) >> VSC_ABC_MODE_VALUE_A_LOC_SHIFT)

/*
 * ENABLE_VSC (RW)
 *
 * enable vsc convert:
 * 0: disable vsc convert
 * 1: enable vsc convert
 */
#define VSC_ABC_MODE_ENABLE_VSC_MASK (0x8U)
#define VSC_ABC_MODE_ENABLE_VSC_SHIFT (3U)
#define VSC_ABC_MODE_ENABLE_VSC_SET(x) (((uint32_t)(x) << VSC_ABC_MODE_ENABLE_VSC_SHIFT) & VSC_ABC_MODE_ENABLE_VSC_MASK)
#define VSC_ABC_MODE_ENABLE_VSC_GET(x) (((uint32_t)(x) & VSC_ABC_MODE_ENABLE_VSC_MASK) >> VSC_ABC_MODE_ENABLE_VSC_SHIFT)

/* Bitfield definition for register: ADC_CHAN_ASSIGN */
/*
 * VALUE_C_CHAN (RW)
 *
 * value_c's adc chan
 */
#define VSC_ADC_CHAN_ASSIGN_VALUE_C_CHAN_MASK (0x1F0000UL)
#define VSC_ADC_CHAN_ASSIGN_VALUE_C_CHAN_SHIFT (16U)
#define VSC_ADC_CHAN_ASSIGN_VALUE_C_CHAN_SET(x) (((uint32_t)(x) << VSC_ADC_CHAN_ASSIGN_VALUE_C_CHAN_SHIFT) & VSC_ADC_CHAN_ASSIGN_VALUE_C_CHAN_MASK)
#define VSC_ADC_CHAN_ASSIGN_VALUE_C_CHAN_GET(x) (((uint32_t)(x) & VSC_ADC_CHAN_ASSIGN_VALUE_C_CHAN_MASK) >> VSC_ADC_CHAN_ASSIGN_VALUE_C_CHAN_SHIFT)

/*
 * VALUE_B_CHAN (RW)
 *
 * value_b's adc chan
 */
#define VSC_ADC_CHAN_ASSIGN_VALUE_B_CHAN_MASK (0x1F00U)
#define VSC_ADC_CHAN_ASSIGN_VALUE_B_CHAN_SHIFT (8U)
#define VSC_ADC_CHAN_ASSIGN_VALUE_B_CHAN_SET(x) (((uint32_t)(x) << VSC_ADC_CHAN_ASSIGN_VALUE_B_CHAN_SHIFT) & VSC_ADC_CHAN_ASSIGN_VALUE_B_CHAN_MASK)
#define VSC_ADC_CHAN_ASSIGN_VALUE_B_CHAN_GET(x) (((uint32_t)(x) & VSC_ADC_CHAN_ASSIGN_VALUE_B_CHAN_MASK) >> VSC_ADC_CHAN_ASSIGN_VALUE_B_CHAN_SHIFT)

/*
 * VALUE_A_CHAN (RW)
 *
 * value_a's adc chan
 */
#define VSC_ADC_CHAN_ASSIGN_VALUE_A_CHAN_MASK (0x1FU)
#define VSC_ADC_CHAN_ASSIGN_VALUE_A_CHAN_SHIFT (0U)
#define VSC_ADC_CHAN_ASSIGN_VALUE_A_CHAN_SET(x) (((uint32_t)(x) << VSC_ADC_CHAN_ASSIGN_VALUE_A_CHAN_SHIFT) & VSC_ADC_CHAN_ASSIGN_VALUE_A_CHAN_MASK)
#define VSC_ADC_CHAN_ASSIGN_VALUE_A_CHAN_GET(x) (((uint32_t)(x) & VSC_ADC_CHAN_ASSIGN_VALUE_A_CHAN_MASK) >> VSC_ADC_CHAN_ASSIGN_VALUE_A_CHAN_SHIFT)

/* Bitfield definition for register: VALUE_A_DATA_OPT */
/*
 * OPT_3 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_A_DATA_OPT_OPT_3_MASK (0xF000U)
#define VSC_VALUE_A_DATA_OPT_OPT_3_SHIFT (12U)
#define VSC_VALUE_A_DATA_OPT_OPT_3_SET(x) (((uint32_t)(x) << VSC_VALUE_A_DATA_OPT_OPT_3_SHIFT) & VSC_VALUE_A_DATA_OPT_OPT_3_MASK)
#define VSC_VALUE_A_DATA_OPT_OPT_3_GET(x) (((uint32_t)(x) & VSC_VALUE_A_DATA_OPT_OPT_3_MASK) >> VSC_VALUE_A_DATA_OPT_OPT_3_SHIFT)

/*
 * OPT_2 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_A_DATA_OPT_OPT_2_MASK (0xF00U)
#define VSC_VALUE_A_DATA_OPT_OPT_2_SHIFT (8U)
#define VSC_VALUE_A_DATA_OPT_OPT_2_SET(x) (((uint32_t)(x) << VSC_VALUE_A_DATA_OPT_OPT_2_SHIFT) & VSC_VALUE_A_DATA_OPT_OPT_2_MASK)
#define VSC_VALUE_A_DATA_OPT_OPT_2_GET(x) (((uint32_t)(x) & VSC_VALUE_A_DATA_OPT_OPT_2_MASK) >> VSC_VALUE_A_DATA_OPT_OPT_2_SHIFT)

/*
 * OPT_1 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_A_DATA_OPT_OPT_1_MASK (0xF0U)
#define VSC_VALUE_A_DATA_OPT_OPT_1_SHIFT (4U)
#define VSC_VALUE_A_DATA_OPT_OPT_1_SET(x) (((uint32_t)(x) << VSC_VALUE_A_DATA_OPT_OPT_1_SHIFT) & VSC_VALUE_A_DATA_OPT_OPT_1_MASK)
#define VSC_VALUE_A_DATA_OPT_OPT_1_GET(x) (((uint32_t)(x) & VSC_VALUE_A_DATA_OPT_OPT_1_MASK) >> VSC_VALUE_A_DATA_OPT_OPT_1_SHIFT)

/*
 * OPT_0 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_A_DATA_OPT_OPT_0_MASK (0xFU)
#define VSC_VALUE_A_DATA_OPT_OPT_0_SHIFT (0U)
#define VSC_VALUE_A_DATA_OPT_OPT_0_SET(x) (((uint32_t)(x) << VSC_VALUE_A_DATA_OPT_OPT_0_SHIFT) & VSC_VALUE_A_DATA_OPT_OPT_0_MASK)
#define VSC_VALUE_A_DATA_OPT_OPT_0_GET(x) (((uint32_t)(x) & VSC_VALUE_A_DATA_OPT_OPT_0_MASK) >> VSC_VALUE_A_DATA_OPT_OPT_0_SHIFT)

/* Bitfield definition for register: VALUE_B_DATA_OPT */
/*
 * OPT_3 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_B_DATA_OPT_OPT_3_MASK (0xF000U)
#define VSC_VALUE_B_DATA_OPT_OPT_3_SHIFT (12U)
#define VSC_VALUE_B_DATA_OPT_OPT_3_SET(x) (((uint32_t)(x) << VSC_VALUE_B_DATA_OPT_OPT_3_SHIFT) & VSC_VALUE_B_DATA_OPT_OPT_3_MASK)
#define VSC_VALUE_B_DATA_OPT_OPT_3_GET(x) (((uint32_t)(x) & VSC_VALUE_B_DATA_OPT_OPT_3_MASK) >> VSC_VALUE_B_DATA_OPT_OPT_3_SHIFT)

/*
 * OPT_2 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_B_DATA_OPT_OPT_2_MASK (0xF00U)
#define VSC_VALUE_B_DATA_OPT_OPT_2_SHIFT (8U)
#define VSC_VALUE_B_DATA_OPT_OPT_2_SET(x) (((uint32_t)(x) << VSC_VALUE_B_DATA_OPT_OPT_2_SHIFT) & VSC_VALUE_B_DATA_OPT_OPT_2_MASK)
#define VSC_VALUE_B_DATA_OPT_OPT_2_GET(x) (((uint32_t)(x) & VSC_VALUE_B_DATA_OPT_OPT_2_MASK) >> VSC_VALUE_B_DATA_OPT_OPT_2_SHIFT)

/*
 * OPT_1 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_B_DATA_OPT_OPT_1_MASK (0xF0U)
#define VSC_VALUE_B_DATA_OPT_OPT_1_SHIFT (4U)
#define VSC_VALUE_B_DATA_OPT_OPT_1_SET(x) (((uint32_t)(x) << VSC_VALUE_B_DATA_OPT_OPT_1_SHIFT) & VSC_VALUE_B_DATA_OPT_OPT_1_MASK)
#define VSC_VALUE_B_DATA_OPT_OPT_1_GET(x) (((uint32_t)(x) & VSC_VALUE_B_DATA_OPT_OPT_1_MASK) >> VSC_VALUE_B_DATA_OPT_OPT_1_SHIFT)

/*
 * OPT_0 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_B_DATA_OPT_OPT_0_MASK (0xFU)
#define VSC_VALUE_B_DATA_OPT_OPT_0_SHIFT (0U)
#define VSC_VALUE_B_DATA_OPT_OPT_0_SET(x) (((uint32_t)(x) << VSC_VALUE_B_DATA_OPT_OPT_0_SHIFT) & VSC_VALUE_B_DATA_OPT_OPT_0_MASK)
#define VSC_VALUE_B_DATA_OPT_OPT_0_GET(x) (((uint32_t)(x) & VSC_VALUE_B_DATA_OPT_OPT_0_MASK) >> VSC_VALUE_B_DATA_OPT_OPT_0_SHIFT)

/* Bitfield definition for register: VALUE_C_DATA_OPT */
/*
 * OPT_3 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_C_DATA_OPT_OPT_3_MASK (0xF000U)
#define VSC_VALUE_C_DATA_OPT_OPT_3_SHIFT (12U)
#define VSC_VALUE_C_DATA_OPT_OPT_3_SET(x) (((uint32_t)(x) << VSC_VALUE_C_DATA_OPT_OPT_3_SHIFT) & VSC_VALUE_C_DATA_OPT_OPT_3_MASK)
#define VSC_VALUE_C_DATA_OPT_OPT_3_GET(x) (((uint32_t)(x) & VSC_VALUE_C_DATA_OPT_OPT_3_MASK) >> VSC_VALUE_C_DATA_OPT_OPT_3_SHIFT)

/*
 * OPT_2 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_C_DATA_OPT_OPT_2_MASK (0xF00U)
#define VSC_VALUE_C_DATA_OPT_OPT_2_SHIFT (8U)
#define VSC_VALUE_C_DATA_OPT_OPT_2_SET(x) (((uint32_t)(x) << VSC_VALUE_C_DATA_OPT_OPT_2_SHIFT) & VSC_VALUE_C_DATA_OPT_OPT_2_MASK)
#define VSC_VALUE_C_DATA_OPT_OPT_2_GET(x) (((uint32_t)(x) & VSC_VALUE_C_DATA_OPT_OPT_2_MASK) >> VSC_VALUE_C_DATA_OPT_OPT_2_SHIFT)

/*
 * OPT_1 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_C_DATA_OPT_OPT_1_MASK (0xF0U)
#define VSC_VALUE_C_DATA_OPT_OPT_1_SHIFT (4U)
#define VSC_VALUE_C_DATA_OPT_OPT_1_SET(x) (((uint32_t)(x) << VSC_VALUE_C_DATA_OPT_OPT_1_SHIFT) & VSC_VALUE_C_DATA_OPT_OPT_1_MASK)
#define VSC_VALUE_C_DATA_OPT_OPT_1_GET(x) (((uint32_t)(x) & VSC_VALUE_C_DATA_OPT_OPT_1_MASK) >> VSC_VALUE_C_DATA_OPT_OPT_1_SHIFT)

/*
 * OPT_0 (RW)
 *
 * 0: PLUS_MUL_1
 * 1: PLUS_MUL_2
 * 5: PLUS_DIV_2
 * 6: PLUS_DIV_3
 * 7: PLUS_DIV_4
 * 8: MINUS MUL 1
 * 9: MINUS MUL 2
 * 13: MINUS DIV 2
 * 14: MINUS DIV 3
 * 15: MINUS DIV 4
 */
#define VSC_VALUE_C_DATA_OPT_OPT_0_MASK (0xFU)
#define VSC_VALUE_C_DATA_OPT_OPT_0_SHIFT (0U)
#define VSC_VALUE_C_DATA_OPT_OPT_0_SET(x) (((uint32_t)(x) << VSC_VALUE_C_DATA_OPT_OPT_0_SHIFT) & VSC_VALUE_C_DATA_OPT_OPT_0_MASK)
#define VSC_VALUE_C_DATA_OPT_OPT_0_GET(x) (((uint32_t)(x) & VSC_VALUE_C_DATA_OPT_OPT_0_MASK) >> VSC_VALUE_C_DATA_OPT_OPT_0_SHIFT)

/* Bitfield definition for register: VALUE_A_OFFSET */
/*
 * VALUE_A_OFFSET (RW)
 *
 * value_a offset
 */
#define VSC_VALUE_A_OFFSET_VALUE_A_OFFSET_MASK (0xFFFFFFFFUL)
#define VSC_VALUE_A_OFFSET_VALUE_A_OFFSET_SHIFT (0U)
#define VSC_VALUE_A_OFFSET_VALUE_A_OFFSET_SET(x) (((uint32_t)(x) << VSC_VALUE_A_OFFSET_VALUE_A_OFFSET_SHIFT) & VSC_VALUE_A_OFFSET_VALUE_A_OFFSET_MASK)
#define VSC_VALUE_A_OFFSET_VALUE_A_OFFSET_GET(x) (((uint32_t)(x) & VSC_VALUE_A_OFFSET_VALUE_A_OFFSET_MASK) >> VSC_VALUE_A_OFFSET_VALUE_A_OFFSET_SHIFT)

/* Bitfield definition for register: VALUE_B_OFFSET */
/*
 * VALUE_B_OFFSET (RW)
 *
 * value_b_offset
 */
#define VSC_VALUE_B_OFFSET_VALUE_B_OFFSET_MASK (0xFFFFFFFFUL)
#define VSC_VALUE_B_OFFSET_VALUE_B_OFFSET_SHIFT (0U)
#define VSC_VALUE_B_OFFSET_VALUE_B_OFFSET_SET(x) (((uint32_t)(x) << VSC_VALUE_B_OFFSET_VALUE_B_OFFSET_SHIFT) & VSC_VALUE_B_OFFSET_VALUE_B_OFFSET_MASK)
#define VSC_VALUE_B_OFFSET_VALUE_B_OFFSET_GET(x) (((uint32_t)(x) & VSC_VALUE_B_OFFSET_VALUE_B_OFFSET_MASK) >> VSC_VALUE_B_OFFSET_VALUE_B_OFFSET_SHIFT)

/* Bitfield definition for register: VALUE_C_OFFSET */
/*
 * VALUE_C_OFFSET (RW)
 *
 * value_c offset
 */
#define VSC_VALUE_C_OFFSET_VALUE_C_OFFSET_MASK (0xFFFFFFFFUL)
#define VSC_VALUE_C_OFFSET_VALUE_C_OFFSET_SHIFT (0U)
#define VSC_VALUE_C_OFFSET_VALUE_C_OFFSET_SET(x) (((uint32_t)(x) << VSC_VALUE_C_OFFSET_VALUE_C_OFFSET_SHIFT) & VSC_VALUE_C_OFFSET_VALUE_C_OFFSET_MASK)
#define VSC_VALUE_C_OFFSET_VALUE_C_OFFSET_GET(x) (((uint32_t)(x) & VSC_VALUE_C_OFFSET_VALUE_C_OFFSET_MASK) >> VSC_VALUE_C_OFFSET_VALUE_C_OFFSET_SHIFT)

/* Bitfield definition for register: IRQ_STATUS */
/*
 * IRQ_STATUS (RW)
 *
 * irq status bit:
 * bit0: vsc convert done irq.
 * bit1: in adc three-phase mode, if ABS(value_a+value_b+value_c) > adc_phase_tolerate, will trigger irq.
 * bit2: value_c overflow during capture process.
 * bit3: value_b_overflow during capture process.
 * bit4: value_a_overflow during capture process.
 * bit5: adc2 chan not capture enough adc value.
 * bit6: adc1 chan not capture enough adc value.
 * bit7: adc0 chan not capture enough adc value.
 * bit8: position not got valid before pos_wait_cycle timeout.
 * bit9: adc2 wait cycle timeout.
 * bit10: adc1 wait cycle timeout.
 * bit11: adc0 wait cycle timeout.
 * bit12: trigger_in break vsc convert even if adc or position is ready.
 */
#define VSC_IRQ_STATUS_IRQ_STATUS_MASK (0xFFFFFFFFUL)
#define VSC_IRQ_STATUS_IRQ_STATUS_SHIFT (0U)
#define VSC_IRQ_STATUS_IRQ_STATUS_SET(x) (((uint32_t)(x) << VSC_IRQ_STATUS_IRQ_STATUS_SHIFT) & VSC_IRQ_STATUS_IRQ_STATUS_MASK)
#define VSC_IRQ_STATUS_IRQ_STATUS_GET(x) (((uint32_t)(x) & VSC_IRQ_STATUS_IRQ_STATUS_MASK) >> VSC_IRQ_STATUS_IRQ_STATUS_SHIFT)

/* Bitfield definition for register: VALUE_A_SW */
/*
 * VALUE_A_SW (RW)
 *
 * value_a_sw
 */
#define VSC_VALUE_A_SW_VALUE_A_SW_MASK (0xFFFFFFFFUL)
#define VSC_VALUE_A_SW_VALUE_A_SW_SHIFT (0U)
#define VSC_VALUE_A_SW_VALUE_A_SW_SET(x) (((uint32_t)(x) << VSC_VALUE_A_SW_VALUE_A_SW_SHIFT) & VSC_VALUE_A_SW_VALUE_A_SW_MASK)
#define VSC_VALUE_A_SW_VALUE_A_SW_GET(x) (((uint32_t)(x) & VSC_VALUE_A_SW_VALUE_A_SW_MASK) >> VSC_VALUE_A_SW_VALUE_A_SW_SHIFT)

/* Bitfield definition for register: VALUE_B_SW */
/*
 * VALUE_B_SW (RW)
 *
 * value_b_sw
 */
#define VSC_VALUE_B_SW_VALUE_B_SW_MASK (0xFFFFFFFFUL)
#define VSC_VALUE_B_SW_VALUE_B_SW_SHIFT (0U)
#define VSC_VALUE_B_SW_VALUE_B_SW_SET(x) (((uint32_t)(x) << VSC_VALUE_B_SW_VALUE_B_SW_SHIFT) & VSC_VALUE_B_SW_VALUE_B_SW_MASK)
#define VSC_VALUE_B_SW_VALUE_B_SW_GET(x) (((uint32_t)(x) & VSC_VALUE_B_SW_VALUE_B_SW_MASK) >> VSC_VALUE_B_SW_VALUE_B_SW_SHIFT)

/* Bitfield definition for register: VALUE_C_SW */
/*
 * VALUE_C_SW (RW)
 *
 * value_c_sw
 */
#define VSC_VALUE_C_SW_VALUE_C_SW_MASK (0xFFFFFFFFUL)
#define VSC_VALUE_C_SW_VALUE_C_SW_SHIFT (0U)
#define VSC_VALUE_C_SW_VALUE_C_SW_SET(x) (((uint32_t)(x) << VSC_VALUE_C_SW_VALUE_C_SW_SHIFT) & VSC_VALUE_C_SW_VALUE_C_SW_MASK)
#define VSC_VALUE_C_SW_VALUE_C_SW_GET(x) (((uint32_t)(x) & VSC_VALUE_C_SW_VALUE_C_SW_MASK) >> VSC_VALUE_C_SW_VALUE_C_SW_SHIFT)

/* Bitfield definition for register: VALUE_SW_READY */
/*
 * VALUE_SW_READY (W1C)
 *
 * software inject value_a/value_b/value_c ready
 */
#define VSC_VALUE_SW_READY_VALUE_SW_READY_MASK (0x1U)
#define VSC_VALUE_SW_READY_VALUE_SW_READY_SHIFT (0U)
#define VSC_VALUE_SW_READY_VALUE_SW_READY_SET(x) (((uint32_t)(x) << VSC_VALUE_SW_READY_VALUE_SW_READY_SHIFT) & VSC_VALUE_SW_READY_VALUE_SW_READY_MASK)
#define VSC_VALUE_SW_READY_VALUE_SW_READY_GET(x) (((uint32_t)(x) & VSC_VALUE_SW_READY_VALUE_SW_READY_MASK) >> VSC_VALUE_SW_READY_VALUE_SW_READY_SHIFT)

/* Bitfield definition for register: TRIGGER_SW */
/*
 * TRIGGER_SW (W1C)
 *
 * software trigger to start waiting adc capture value, same as hardwire trigger_in
 */
#define VSC_TRIGGER_SW_TRIGGER_SW_MASK (0x1U)
#define VSC_TRIGGER_SW_TRIGGER_SW_SHIFT (0U)
#define VSC_TRIGGER_SW_TRIGGER_SW_SET(x) (((uint32_t)(x) << VSC_TRIGGER_SW_TRIGGER_SW_SHIFT) & VSC_TRIGGER_SW_TRIGGER_SW_MASK)
#define VSC_TRIGGER_SW_TRIGGER_SW_GET(x) (((uint32_t)(x) & VSC_TRIGGER_SW_TRIGGER_SW_MASK) >> VSC_TRIGGER_SW_TRIGGER_SW_SHIFT)

/* Bitfield definition for register: TIMELOCK */
/*
 * POSITION_CAPTURE_MODE (RW)
 *
 * postion capture mode:
 * 00: position use last valid data when adc value capture finish
 * 01: position use frist valid data after adc value capture
 * 10: position use last valid data before adc value capture
 * other: reserved
 */
#define VSC_TIMELOCK_POSITION_CAPTURE_MODE_MASK (0x3000U)
#define VSC_TIMELOCK_POSITION_CAPTURE_MODE_SHIFT (12U)
#define VSC_TIMELOCK_POSITION_CAPTURE_MODE_SET(x) (((uint32_t)(x) << VSC_TIMELOCK_POSITION_CAPTURE_MODE_SHIFT) & VSC_TIMELOCK_POSITION_CAPTURE_MODE_MASK)
#define VSC_TIMELOCK_POSITION_CAPTURE_MODE_GET(x) (((uint32_t)(x) & VSC_TIMELOCK_POSITION_CAPTURE_MODE_MASK) >> VSC_TIMELOCK_POSITION_CAPTURE_MODE_SHIFT)

/*
 * ADC_TIMESTAMP_SEL (RW)
 *
 * adc timestamp select：
 * 0：reserved;
 * 1: from value_a;
 * 2: from value_b;
 * 3: from value_c;
 */
#define VSC_TIMELOCK_ADC_TIMESTAMP_SEL_MASK (0x30U)
#define VSC_TIMELOCK_ADC_TIMESTAMP_SEL_SHIFT (4U)
#define VSC_TIMELOCK_ADC_TIMESTAMP_SEL_SET(x) (((uint32_t)(x) << VSC_TIMELOCK_ADC_TIMESTAMP_SEL_SHIFT) & VSC_TIMELOCK_ADC_TIMESTAMP_SEL_MASK)
#define VSC_TIMELOCK_ADC_TIMESTAMP_SEL_GET(x) (((uint32_t)(x) & VSC_TIMELOCK_ADC_TIMESTAMP_SEL_MASK) >> VSC_TIMELOCK_ADC_TIMESTAMP_SEL_SHIFT)

/*
 * VALUE_COUNTER_SEL (RW)
 *
 * adc timestamp use which number index of adc_timestamp_sel used.
 */
#define VSC_TIMELOCK_VALUE_COUNTER_SEL_MASK (0xFU)
#define VSC_TIMELOCK_VALUE_COUNTER_SEL_SHIFT (0U)
#define VSC_TIMELOCK_VALUE_COUNTER_SEL_SET(x) (((uint32_t)(x) << VSC_TIMELOCK_VALUE_COUNTER_SEL_SHIFT) & VSC_TIMELOCK_VALUE_COUNTER_SEL_MASK)
#define VSC_TIMELOCK_VALUE_COUNTER_SEL_GET(x) (((uint32_t)(x) & VSC_TIMELOCK_VALUE_COUNTER_SEL_MASK) >> VSC_TIMELOCK_VALUE_COUNTER_SEL_SHIFT)

/* Bitfield definition for register: POSITION_SW */
/*
 * POSITION_SW (RW)
 *
 * position_sw
 */
#define VSC_POSITION_SW_POSITION_SW_MASK (0xFFFFFFFFUL)
#define VSC_POSITION_SW_POSITION_SW_SHIFT (0U)
#define VSC_POSITION_SW_POSITION_SW_SET(x) (((uint32_t)(x) << VSC_POSITION_SW_POSITION_SW_SHIFT) & VSC_POSITION_SW_POSITION_SW_MASK)
#define VSC_POSITION_SW_POSITION_SW_GET(x) (((uint32_t)(x) & VSC_POSITION_SW_POSITION_SW_MASK) >> VSC_POSITION_SW_POSITION_SW_SHIFT)

/* Bitfield definition for register: ADC_WAIT_CYCLE */
/*
 * ADC_WAIT_CYCLE (RW)
 *
 * adc wait cycle after trigger adc capture event
 */
#define VSC_ADC_WAIT_CYCLE_ADC_WAIT_CYCLE_MASK (0xFFFFFFFFUL)
#define VSC_ADC_WAIT_CYCLE_ADC_WAIT_CYCLE_SHIFT (0U)
#define VSC_ADC_WAIT_CYCLE_ADC_WAIT_CYCLE_SET(x) (((uint32_t)(x) << VSC_ADC_WAIT_CYCLE_ADC_WAIT_CYCLE_SHIFT) & VSC_ADC_WAIT_CYCLE_ADC_WAIT_CYCLE_MASK)
#define VSC_ADC_WAIT_CYCLE_ADC_WAIT_CYCLE_GET(x) (((uint32_t)(x) & VSC_ADC_WAIT_CYCLE_ADC_WAIT_CYCLE_MASK) >> VSC_ADC_WAIT_CYCLE_ADC_WAIT_CYCLE_SHIFT)

/* Bitfield definition for register: POS_WAIT_CYCLE */
/*
 * POS_WAIT_CYCLE (RW)
 *
 * position wait cycle after trigger adc capture event
 */
#define VSC_POS_WAIT_CYCLE_POS_WAIT_CYCLE_MASK (0xFFFFFFFFUL)
#define VSC_POS_WAIT_CYCLE_POS_WAIT_CYCLE_SHIFT (0U)
#define VSC_POS_WAIT_CYCLE_POS_WAIT_CYCLE_SET(x) (((uint32_t)(x) << VSC_POS_WAIT_CYCLE_POS_WAIT_CYCLE_SHIFT) & VSC_POS_WAIT_CYCLE_POS_WAIT_CYCLE_MASK)
#define VSC_POS_WAIT_CYCLE_POS_WAIT_CYCLE_GET(x) (((uint32_t)(x) & VSC_POS_WAIT_CYCLE_POS_WAIT_CYCLE_MASK) >> VSC_POS_WAIT_CYCLE_POS_WAIT_CYCLE_SHIFT)

/* Bitfield definition for register: IRQ_ENABLE */
/*
 * IRQ_ENABLE (RW)
 *
 * irq enable bit:
 * bit0: vsc convert done irq.
 * bit1: in adc three-phase mode, if ABS(value_a+value_b+value_c) > adc_phase_tolerate, will trigger irq.
 * bit2: value_c overflow during capture process.
 * bit3: value_b_overflow during capture process.
 * bit4: value_a_overflow during capture process.
 * bit5: adc2 chan not capture enough adc value.
 * bit6: adc1 chan not capture enough adc value.
 * bit7: adc0 chan not capture enough adc value.
 * bit8: position not got valid before pos_wait_cycle timeout.
 * bit9: adc2 wait cycle timeout.
 * bit10: adc1 wait cycle timeout.
 * bit11: adc0 wait cycle timeout.
 * bit12: trigger_in break vsc convert even if adc or position is ready.
 */
#define VSC_IRQ_ENABLE_IRQ_ENABLE_MASK (0xFFFFFFFFUL)
#define VSC_IRQ_ENABLE_IRQ_ENABLE_SHIFT (0U)
#define VSC_IRQ_ENABLE_IRQ_ENABLE_SET(x) (((uint32_t)(x) << VSC_IRQ_ENABLE_IRQ_ENABLE_SHIFT) & VSC_IRQ_ENABLE_IRQ_ENABLE_MASK)
#define VSC_IRQ_ENABLE_IRQ_ENABLE_GET(x) (((uint32_t)(x) & VSC_IRQ_ENABLE_IRQ_ENABLE_MASK) >> VSC_IRQ_ENABLE_IRQ_ENABLE_SHIFT)

/* Bitfield definition for register: ADC_PHASE_TOLERATE */
/*
 * ADC_PHASE_TOLERATE (RW)
 *
 * in adc three-phase mode, if ABS(value_a+value_b+value_c) > adc_phase_tolerate, will trigger irq.
 */
#define VSC_ADC_PHASE_TOLERATE_ADC_PHASE_TOLERATE_MASK (0xFFFFFFFFUL)
#define VSC_ADC_PHASE_TOLERATE_ADC_PHASE_TOLERATE_SHIFT (0U)
#define VSC_ADC_PHASE_TOLERATE_ADC_PHASE_TOLERATE_SET(x) (((uint32_t)(x) << VSC_ADC_PHASE_TOLERATE_ADC_PHASE_TOLERATE_SHIFT) & VSC_ADC_PHASE_TOLERATE_ADC_PHASE_TOLERATE_MASK)
#define VSC_ADC_PHASE_TOLERATE_ADC_PHASE_TOLERATE_GET(x) (((uint32_t)(x) & VSC_ADC_PHASE_TOLERATE_ADC_PHASE_TOLERATE_MASK) >> VSC_ADC_PHASE_TOLERATE_ADC_PHASE_TOLERATE_SHIFT)

/* Bitfield definition for register: POS_POLE */
/*
 * POS_POLE (RW)
 *
 * pole number
 */
#define VSC_POS_POLE_POS_POLE_MASK (0xFFFFU)
#define VSC_POS_POLE_POS_POLE_SHIFT (0U)
#define VSC_POS_POLE_POS_POLE_SET(x) (((uint32_t)(x) << VSC_POS_POLE_POS_POLE_SHIFT) & VSC_POS_POLE_POS_POLE_MASK)
#define VSC_POS_POLE_POS_POLE_GET(x) (((uint32_t)(x) & VSC_POS_POLE_POS_POLE_MASK) >> VSC_POS_POLE_POS_POLE_SHIFT)

/* Bitfield definition for register: ID_POSEDGE */
/*
 * ID_POSEDGE (RO)
 *
 * posedge order Id value
 */
#define VSC_ID_POSEDGE_ID_POSEDGE_MASK (0xFFFFFFFFUL)
#define VSC_ID_POSEDGE_ID_POSEDGE_SHIFT (0U)
#define VSC_ID_POSEDGE_ID_POSEDGE_GET(x) (((uint32_t)(x) & VSC_ID_POSEDGE_ID_POSEDGE_MASK) >> VSC_ID_POSEDGE_ID_POSEDGE_SHIFT)

/* Bitfield definition for register: IQ_POSEDGE */
/*
 * IQ_POSEDGE (RO)
 *
 * posedge order Iq value
 */
#define VSC_IQ_POSEDGE_IQ_POSEDGE_MASK (0xFFFFFFFFUL)
#define VSC_IQ_POSEDGE_IQ_POSEDGE_SHIFT (0U)
#define VSC_IQ_POSEDGE_IQ_POSEDGE_GET(x) (((uint32_t)(x) & VSC_IQ_POSEDGE_IQ_POSEDGE_MASK) >> VSC_IQ_POSEDGE_IQ_POSEDGE_SHIFT)

/* Bitfield definition for register: ID_NEGEDGE */
/*
 * ID_NEGEDGE (RO)
 *
 * negedge order Id value
 */
#define VSC_ID_NEGEDGE_ID_NEGEDGE_MASK (0xFFFFFFFFUL)
#define VSC_ID_NEGEDGE_ID_NEGEDGE_SHIFT (0U)
#define VSC_ID_NEGEDGE_ID_NEGEDGE_GET(x) (((uint32_t)(x) & VSC_ID_NEGEDGE_ID_NEGEDGE_MASK) >> VSC_ID_NEGEDGE_ID_NEGEDGE_SHIFT)

/* Bitfield definition for register: IQ_NEGEDGE */
/*
 * IQ_NEGEDGE (RO)
 *
 * negedge order Iq value
 */
#define VSC_IQ_NEGEDGE_IQ_NEGEDGE_MASK (0xFFFFFFFFUL)
#define VSC_IQ_NEGEDGE_IQ_NEGEDGE_SHIFT (0U)
#define VSC_IQ_NEGEDGE_IQ_NEGEDGE_GET(x) (((uint32_t)(x) & VSC_IQ_NEGEDGE_IQ_NEGEDGE_MASK) >> VSC_IQ_NEGEDGE_IQ_NEGEDGE_SHIFT)

/* Bitfield definition for register: ALPHA_POSEDGE */
/*
 * ALPHA_POSEDGE (RO)
 *
 * posedge order alpha value
 */
#define VSC_ALPHA_POSEDGE_ALPHA_POSEDGE_MASK (0xFFFFFFFFUL)
#define VSC_ALPHA_POSEDGE_ALPHA_POSEDGE_SHIFT (0U)
#define VSC_ALPHA_POSEDGE_ALPHA_POSEDGE_GET(x) (((uint32_t)(x) & VSC_ALPHA_POSEDGE_ALPHA_POSEDGE_MASK) >> VSC_ALPHA_POSEDGE_ALPHA_POSEDGE_SHIFT)

/* Bitfield definition for register: BETA_POSEDGE */
/*
 * BETA_POSEDGE (RO)
 *
 * posedge order beta value
 */
#define VSC_BETA_POSEDGE_BETA_POSEDGE_MASK (0xFFFFFFFFUL)
#define VSC_BETA_POSEDGE_BETA_POSEDGE_SHIFT (0U)
#define VSC_BETA_POSEDGE_BETA_POSEDGE_GET(x) (((uint32_t)(x) & VSC_BETA_POSEDGE_BETA_POSEDGE_MASK) >> VSC_BETA_POSEDGE_BETA_POSEDGE_SHIFT)

/* Bitfield definition for register: ALPHA_NEGEDGE */
/*
 * ALPHA_NEGEDGE (RO)
 *
 * negedge order alpha value
 */
#define VSC_ALPHA_NEGEDGE_ALPHA_NEGEDGE_MASK (0xFFFFFFFFUL)
#define VSC_ALPHA_NEGEDGE_ALPHA_NEGEDGE_SHIFT (0U)
#define VSC_ALPHA_NEGEDGE_ALPHA_NEGEDGE_GET(x) (((uint32_t)(x) & VSC_ALPHA_NEGEDGE_ALPHA_NEGEDGE_MASK) >> VSC_ALPHA_NEGEDGE_ALPHA_NEGEDGE_SHIFT)

/* Bitfield definition for register: BETA_NEGEDGE */
/*
 * BETA_NEGEDGE (RO)
 *
 * negedge order beta value
 */
#define VSC_BETA_NEGEDGE_BETA_NEGEDGE_MASK (0xFFFFFFFFUL)
#define VSC_BETA_NEGEDGE_BETA_NEGEDGE_SHIFT (0U)
#define VSC_BETA_NEGEDGE_BETA_NEGEDGE_GET(x) (((uint32_t)(x) & VSC_BETA_NEGEDGE_BETA_NEGEDGE_MASK) >> VSC_BETA_NEGEDGE_BETA_NEGEDGE_SHIFT)

/* Bitfield definition for register: TIMESTAMP_LOCKED */
/*
 * TIMESTAMP_LOCKED (RO)
 *
 * timestamp_locked
 */
#define VSC_TIMESTAMP_LOCKED_TIMESTAMP_LOCKED_MASK (0xFFFFFFFFUL)
#define VSC_TIMESTAMP_LOCKED_TIMESTAMP_LOCKED_SHIFT (0U)
#define VSC_TIMESTAMP_LOCKED_TIMESTAMP_LOCKED_GET(x) (((uint32_t)(x) & VSC_TIMESTAMP_LOCKED_TIMESTAMP_LOCKED_MASK) >> VSC_TIMESTAMP_LOCKED_TIMESTAMP_LOCKED_SHIFT)

/* Bitfield definition for register: DEBUG_STATUS0 */
/*
 * VALUE_A_COUNTER (RO)
 *
 * value_a_counter
 */
#define VSC_DEBUG_STATUS0_VALUE_A_COUNTER_MASK (0xF00U)
#define VSC_DEBUG_STATUS0_VALUE_A_COUNTER_SHIFT (8U)
#define VSC_DEBUG_STATUS0_VALUE_A_COUNTER_GET(x) (((uint32_t)(x) & VSC_DEBUG_STATUS0_VALUE_A_COUNTER_MASK) >> VSC_DEBUG_STATUS0_VALUE_A_COUNTER_SHIFT)

/*
 * VALUE_B_COUNTER (RO)
 *
 * value_b_counter
 */
#define VSC_DEBUG_STATUS0_VALUE_B_COUNTER_MASK (0xF0U)
#define VSC_DEBUG_STATUS0_VALUE_B_COUNTER_SHIFT (4U)
#define VSC_DEBUG_STATUS0_VALUE_B_COUNTER_GET(x) (((uint32_t)(x) & VSC_DEBUG_STATUS0_VALUE_B_COUNTER_MASK) >> VSC_DEBUG_STATUS0_VALUE_B_COUNTER_SHIFT)

/*
 * VALUE_C_COUNTER (RO)
 *
 * value_c_counter
 */
#define VSC_DEBUG_STATUS0_VALUE_C_COUNTER_MASK (0xFU)
#define VSC_DEBUG_STATUS0_VALUE_C_COUNTER_SHIFT (0U)
#define VSC_DEBUG_STATUS0_VALUE_C_COUNTER_GET(x) (((uint32_t)(x) & VSC_DEBUG_STATUS0_VALUE_C_COUNTER_MASK) >> VSC_DEBUG_STATUS0_VALUE_C_COUNTER_SHIFT)




#endif /* HPM_VSC_H */
