/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_QEOV2_H
#define HPM_QEOV2_H

typedef struct {
    struct {
        __RW uint32_t MODE;                    /* 0x0: analog waves mode */
        __RW uint32_t RESOLUTION;              /* 0x4: resolution of wave0/1/2 */
        __RW uint32_t PHASE_SHIFT[3];          /* 0x8 - 0x10: wave0 phase shifter */
        __RW uint32_t VD_INJECT;               /* 0x14: wave vd inject value */
        __R  uint8_t  RESERVED0[8];            /* 0x18 - 0x1F: Reserved */
        __RW uint32_t VQ_INJECT;               /* 0x20: wave vq inject value */
        __R  uint8_t  RESERVED1[8];            /* 0x24 - 0x2B: Reserved */
        __W  uint32_t VD_VQ_LOAD;              /* 0x2C: load wave0/1/2 vd vq value */
        __RW uint32_t AMPLITUDE[3];            /* 0x30 - 0x38: wave0 amplitude */
        __RW uint32_t MID_POINT[3];            /* 0x3C - 0x44: wave0 output middle point offset */
        struct {
            __RW uint32_t MIN_LEVEL0;          /* 0x48: wave0 low area limit value */
            __RW uint32_t MAX_LEVEL0;          /* 0x4C: wave0 high area limit value */
        } LIMIT0[3];
        struct {
            __RW uint32_t MIN_LEVEL1;          /* 0x60: wave0 low area limit value level1 */
            __RW uint32_t MAX_LEVEL1;          /* 0x64: wave0 high area limit value level1 */
        } LIMIT1[3];
        __RW uint32_t DEADZONE_SHIFT[3];       /* 0x78 - 0x80: deadzone_shifter_wave0 */
        __RW uint32_t PWM_CYCLE;               /* 0x84: pwm_cycle */
    } WAVE;
    __R  uint8_t  RESERVED0[120];              /* 0x88 - 0xFF: Reserved */
    struct {
        __RW uint32_t MODE;                    /* 0x100: wave_a/b/z output mode */
        __RW uint32_t RESOLUTION;              /* 0x104: resolution of wave_a/b/z */
        __RW uint32_t PHASE_SHIFT[3];          /* 0x108 - 0x110: wave_a phase shifter */
        __RW uint32_t LINE_WIDTH;              /* 0x114: Two-phase orthogonality wave 1/4 period */
        __RW uint32_t WDOG_WIDTH;              /* 0x118: wdog width of qeo */
        __W  uint32_t POSTION_SYNC;            /* 0x11C: sync abz owned postion */
        __RW uint32_t OVERALL_OFFSET;          /* 0x120: abz overall position offset */
        __RW uint32_t Z_START;                 /* 0x124: zero phase start line num */
        __RW uint32_t Z_END;                   /* 0x128: zero phase end line num */
        __RW uint32_t Z_OFFSET;                /* 0x12C: zero phase start and end 1/4 line num */
        __RW uint32_t Z_PULSE_WIDTH;           /* 0x130: zero pulse witdth */
    } ABZ;
    __R  uint8_t  RESERVED1[12];               /* 0x134 - 0x13F: Reserved */
    struct {
        __RW uint32_t MODE;                    /* 0x140: pwm mode */
        __RW uint32_t RESOLUTION;              /* 0x144: resolution of pwm */
        __RW uint32_t PHASE_SHIFT[4];          /* 0x148 - 0x154: pwm_a phase shifter */
        __RW uint32_t PHASE_TABLE[24];         /* 0x158 - 0x1B4: pwm_phase_table 0 */
    } PWM;
    __R  uint8_t  RESERVED2[64];               /* 0x1B8 - 0x1F7: Reserved */
    __RW uint32_t POSTION_SOFTWARE;            /* 0x1F8: softwave inject postion */
    __RW uint32_t POSTION_SEL;                 /* 0x1FC: select softwave inject postion */
    __R  uint32_t STATUS;                      /* 0x200: qeo status */
    __R  uint32_t DEBUG0;                      /* 0x204: qeo debug 0 */
    __R  uint32_t DEBUG1;                      /* 0x208: qeo debug 1 */
    __R  uint32_t DEBUG2;                      /* 0x20C: qeo debug 2 */
    __R  uint32_t DEBUG3;                      /* 0x210: qeo debug 3 */
    __R  uint32_t DEBUG4;                      /* 0x214: qeo debug 4 */
    __R  uint32_t DEBUG5;                      /* 0x218: qeo debug 5 */
} QEOV2_Type;


/* Bitfield definition for register of struct WAVE: MODE */
/*
 * WAVE2_ABOVE_MAX_LIMIT (RW)
 *
 * wave2 above max limit mode.
 * 0: output all bits are 1.
 * 1: output 0x0.
 * 2: output as level_max_limit2.level0_max_limit
 */
#define QEOV2_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_MASK (0xC0000000UL)
#define QEOV2_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_SHIFT (30U)
#define QEOV2_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_SHIFT)

/*
 * WAVE2_HIGH_AREA1_LIMIT (RW)
 *
 * wave2 high area1 limit mode.
 * 0: output all bits are 1.
 * 1: output as level_max_limit2.level0_max_limit
 */
#define QEOV2_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_MASK (0x20000000UL)
#define QEOV2_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_SHIFT (29U)
#define QEOV2_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_SHIFT)

/*
 * WAVE2_HIGH_AREA0_LIMIT (RW)
 *
 * wave2 high area0 limit mode.
 * 0: output all bits are 1.
 * 1: output as level_max_limit2.level0_max_limit
 */
#define QEOV2_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_MASK (0x10000000UL)
#define QEOV2_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_SHIFT (28U)
#define QEOV2_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_SHIFT)

/*
 * WAVE2_LOW_AREA1_LIMIT (RW)
 *
 * wave2 low area1 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit2.level1_min_limit
 */
#define QEOV2_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_MASK (0x8000000UL)
#define QEOV2_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_SHIFT (27U)
#define QEOV2_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_SHIFT)

/*
 * WAVE2_LOW_AREA0_LIMIT (RW)
 *
 * wave2 low area0 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit2.level1_min_limit
 */
#define QEOV2_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_MASK (0x4000000UL)
#define QEOV2_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_SHIFT (26U)
#define QEOV2_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_SHIFT)

/*
 * WAVE2_BELOW_MIN_LIMIT (RW)
 *
 * wave2 below min limit mode.
 * 0: output 0.
 * 1: output all bits are 1.
 * 2: output as level_min_limit2.level1_min_limit
 */
#define QEOV2_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_MASK (0x3000000UL)
#define QEOV2_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_SHIFT (24U)
#define QEOV2_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_SHIFT)

/*
 * WAVE1_ABOVE_MAX_LIMIT (RW)
 *
 * wave1 above max limit mode.
 * 0: output all bits are 1.
 * 1: output 0x0.
 * 2: output as level_max_limit1.level0_max_limit
 */
#define QEOV2_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_MASK (0xC00000UL)
#define QEOV2_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_SHIFT (22U)
#define QEOV2_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_SHIFT)

/*
 * WAVE1_HIGH_AREA1_LIMIT (RW)
 *
 * wave1 high area1 limit mode.
 * 0: output all bits are 1.
 * 1: output as level_max_limit1.level0_max_limit
 */
#define QEOV2_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_MASK (0x200000UL)
#define QEOV2_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_SHIFT (21U)
#define QEOV2_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_SHIFT)

/*
 * WAVE1_HIGH_AREA0_LIMIT (RW)
 *
 * wave1 high area0 limit mode.
 * 0: output all bits are 1.
 * 1: output as level_max_limit1.level0_max_limit
 */
#define QEOV2_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_MASK (0x100000UL)
#define QEOV2_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_SHIFT (20U)
#define QEOV2_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_SHIFT)

/*
 * WAVE1_LOW_AREA1_LIMIT (RW)
 *
 * wave1 low area1 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit1.level1_min_limit
 */
#define QEOV2_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_MASK (0x80000UL)
#define QEOV2_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_SHIFT (19U)
#define QEOV2_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_SHIFT)

/*
 * WAVE1_LOW_AREA0_LIMIT (RW)
 *
 * wave1 low area0 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit1.level1_min_limit
 */
#define QEOV2_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_MASK (0x40000UL)
#define QEOV2_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_SHIFT (18U)
#define QEOV2_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_SHIFT)

/*
 * WAVE1_BELOW_MIN_LIMIT (RW)
 *
 * wave1 below min limit mode.
 * 0: output 0.
 * 1: output all bits are 1.
 * 2: output as level_min_limit1.level1_min_limit
 */
#define QEOV2_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_MASK (0x30000UL)
#define QEOV2_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_SHIFT (16U)
#define QEOV2_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_SHIFT)

/*
 * WAVE0_ABOVE_MAX_LIMIT (RW)
 *
 * wave0 above max limit mode.
 * 0: output all bits are 1.
 * 1: output 0x0.
 * 2: output as level_max_limit0.level0_max_limit
 */
#define QEOV2_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_MASK (0xC000U)
#define QEOV2_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_SHIFT (14U)
#define QEOV2_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_SHIFT)

/*
 * WAVE0_HIGH_AREA1_LIMIT (RW)
 *
 * wave0 high area1 limit mode.
 * 0: output all bits are 1.
 * 1: output as level_max_limit0.level0_max_limit
 */
#define QEOV2_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_MASK (0x2000U)
#define QEOV2_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_SHIFT (13U)
#define QEOV2_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_SHIFT)

/*
 * WAVE0_HIGH_AREA0_LIMIT (RW)
 *
 * wave0 high area0 limit mode.
 * 0: output all bits are 1.
 * 1: output as level_max_limit0.level0_max_limit
 */
#define QEOV2_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_MASK (0x1000U)
#define QEOV2_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_SHIFT (12U)
#define QEOV2_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_SHIFT)

/*
 * WAVE0_LOW_AREA1_LIMIT (RW)
 *
 * wave0 low area1 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit0.level1_min_limit
 */
#define QEOV2_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_MASK (0x800U)
#define QEOV2_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_SHIFT (11U)
#define QEOV2_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_SHIFT)

/*
 * WAVE0_LOW_AREA0_LIMIT (RW)
 *
 * wave0 low area0 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit0.level1_min_limit
 */
#define QEOV2_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_MASK (0x400U)
#define QEOV2_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_SHIFT (10U)
#define QEOV2_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_SHIFT)

/*
 * WAVE0_BELOW_MIN_LIMIT (RW)
 *
 * wave0 below min limit mode.
 * 0: output 0.
 * 1: output all bits are 1.
 * 2: output as level_min_limit0.level1_min_limit
 */
#define QEOV2_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_MASK (0x300U)
#define QEOV2_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_SHIFT (8U)
#define QEOV2_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_SHIFT) & QEOV2_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_MASK)
#define QEOV2_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_MASK) >> QEOV2_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_SHIFT)

/*
 * SADDLE_TYPE (RW)
 *
 * saddle type seclect;
 * 0:standard saddle.
 * 1: triple-cos saddle.
 */
#define QEOV2_WAVE_MODE_SADDLE_TYPE_MASK (0x80U)
#define QEOV2_WAVE_MODE_SADDLE_TYPE_SHIFT (7U)
#define QEOV2_WAVE_MODE_SADDLE_TYPE_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_SADDLE_TYPE_SHIFT) & QEOV2_WAVE_MODE_SADDLE_TYPE_MASK)
#define QEOV2_WAVE_MODE_SADDLE_TYPE_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_SADDLE_TYPE_MASK) >> QEOV2_WAVE_MODE_SADDLE_TYPE_SHIFT)

/*
 * ENABLE_DQ_VALID (RW)
 *
 * enable vd or vq valid to trigger analog wave calcuation
 * 0: disable.
 * 1: enable.
 */
#define QEOV2_WAVE_MODE_ENABLE_DQ_VALID_MASK (0x40U)
#define QEOV2_WAVE_MODE_ENABLE_DQ_VALID_SHIFT (6U)
#define QEOV2_WAVE_MODE_ENABLE_DQ_VALID_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_ENABLE_DQ_VALID_SHIFT) & QEOV2_WAVE_MODE_ENABLE_DQ_VALID_MASK)
#define QEOV2_WAVE_MODE_ENABLE_DQ_VALID_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_ENABLE_DQ_VALID_MASK) >> QEOV2_WAVE_MODE_ENABLE_DQ_VALID_SHIFT)

/*
 * ENABLE_POS_VALID (RW)
 *
 * enable position valid to trigger analog wave calcuation
 * 0: disable.
 * 1: enable.
 */
#define QEOV2_WAVE_MODE_ENABLE_POS_VALID_MASK (0x20U)
#define QEOV2_WAVE_MODE_ENABLE_POS_VALID_SHIFT (5U)
#define QEOV2_WAVE_MODE_ENABLE_POS_VALID_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_ENABLE_POS_VALID_SHIFT) & QEOV2_WAVE_MODE_ENABLE_POS_VALID_MASK)
#define QEOV2_WAVE_MODE_ENABLE_POS_VALID_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_ENABLE_POS_VALID_MASK) >> QEOV2_WAVE_MODE_ENABLE_POS_VALID_SHIFT)

/*
 * EN_WAVE_VD_VQ_INJECT (RW)
 *
 * wave VdVq inject enable.
 * 0: disable VdVq inject.
 * 1: enable VdVq inject.
 */
#define QEOV2_WAVE_MODE_EN_WAVE_VD_VQ_INJECT_MASK (0x10U)
#define QEOV2_WAVE_MODE_EN_WAVE_VD_VQ_INJECT_SHIFT (4U)
#define QEOV2_WAVE_MODE_EN_WAVE_VD_VQ_INJECT_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_EN_WAVE_VD_VQ_INJECT_SHIFT) & QEOV2_WAVE_MODE_EN_WAVE_VD_VQ_INJECT_MASK)
#define QEOV2_WAVE_MODE_EN_WAVE_VD_VQ_INJECT_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_EN_WAVE_VD_VQ_INJECT_MASK) >> QEOV2_WAVE_MODE_EN_WAVE_VD_VQ_INJECT_SHIFT)

/*
 * VD_VQ_SEL (RW)
 *
 * vd_vq sel ctrl:
 * 0: from CLC.
 * 1: from software.
 */
#define QEOV2_WAVE_MODE_VD_VQ_SEL_MASK (0x4U)
#define QEOV2_WAVE_MODE_VD_VQ_SEL_SHIFT (2U)
#define QEOV2_WAVE_MODE_VD_VQ_SEL_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_VD_VQ_SEL_SHIFT) & QEOV2_WAVE_MODE_VD_VQ_SEL_MASK)
#define QEOV2_WAVE_MODE_VD_VQ_SEL_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_VD_VQ_SEL_MASK) >> QEOV2_WAVE_MODE_VD_VQ_SEL_SHIFT)

/*
 * WAVES_OUTPUT_TYPE (RW)
 *
 * wave0/1/2 output mode.
 * 0: cosine wave.
 * 1: saddle wave.
 * 2. abs cosine wave.
 * 3. saw wave
 */
#define QEOV2_WAVE_MODE_WAVES_OUTPUT_TYPE_MASK (0x3U)
#define QEOV2_WAVE_MODE_WAVES_OUTPUT_TYPE_SHIFT (0U)
#define QEOV2_WAVE_MODE_WAVES_OUTPUT_TYPE_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MODE_WAVES_OUTPUT_TYPE_SHIFT) & QEOV2_WAVE_MODE_WAVES_OUTPUT_TYPE_MASK)
#define QEOV2_WAVE_MODE_WAVES_OUTPUT_TYPE_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MODE_WAVES_OUTPUT_TYPE_MASK) >> QEOV2_WAVE_MODE_WAVES_OUTPUT_TYPE_SHIFT)

/* Bitfield definition for register of struct WAVE: RESOLUTION */
/*
 * LINES (RW)
 *
 * wave0/1/2 resolution
 */
#define QEOV2_WAVE_RESOLUTION_LINES_MASK (0xFFFFFFFFUL)
#define QEOV2_WAVE_RESOLUTION_LINES_SHIFT (0U)
#define QEOV2_WAVE_RESOLUTION_LINES_SET(x) (((uint32_t)(x) << QEOV2_WAVE_RESOLUTION_LINES_SHIFT) & QEOV2_WAVE_RESOLUTION_LINES_MASK)
#define QEOV2_WAVE_RESOLUTION_LINES_GET(x) (((uint32_t)(x) & QEOV2_WAVE_RESOLUTION_LINES_MASK) >> QEOV2_WAVE_RESOLUTION_LINES_SHIFT)

/* Bitfield definition for register of struct WAVE: WAVE0 */
/*
 * VAL (RW)
 *
 * wave0 phase shifter value, default is 0x0. write other value will shift phase early as (cfg_value/2^32) period
 */
#define QEOV2_WAVE_PHASE_SHIFT_VAL_MASK (0xFFFFFFFFUL)
#define QEOV2_WAVE_PHASE_SHIFT_VAL_SHIFT (0U)
#define QEOV2_WAVE_PHASE_SHIFT_VAL_SET(x) (((uint32_t)(x) << QEOV2_WAVE_PHASE_SHIFT_VAL_SHIFT) & QEOV2_WAVE_PHASE_SHIFT_VAL_MASK)
#define QEOV2_WAVE_PHASE_SHIFT_VAL_GET(x) (((uint32_t)(x) & QEOV2_WAVE_PHASE_SHIFT_VAL_MASK) >> QEOV2_WAVE_PHASE_SHIFT_VAL_SHIFT)

/* Bitfield definition for register of struct WAVE: VD_INJECT */
/*
 * VD_VAL (RW)
 *
 * Vd inject value
 */
#define QEOV2_WAVE_VD_INJECT_VD_VAL_MASK (0xFFFFFFFFUL)
#define QEOV2_WAVE_VD_INJECT_VD_VAL_SHIFT (0U)
#define QEOV2_WAVE_VD_INJECT_VD_VAL_SET(x) (((uint32_t)(x) << QEOV2_WAVE_VD_INJECT_VD_VAL_SHIFT) & QEOV2_WAVE_VD_INJECT_VD_VAL_MASK)
#define QEOV2_WAVE_VD_INJECT_VD_VAL_GET(x) (((uint32_t)(x) & QEOV2_WAVE_VD_INJECT_VD_VAL_MASK) >> QEOV2_WAVE_VD_INJECT_VD_VAL_SHIFT)

/* Bitfield definition for register of struct WAVE: VQ_INJECT */
/*
 * VQ_VAL (RW)
 *
 * Vq inject value
 */
#define QEOV2_WAVE_VQ_INJECT_VQ_VAL_MASK (0xFFFFFFFFUL)
#define QEOV2_WAVE_VQ_INJECT_VQ_VAL_SHIFT (0U)
#define QEOV2_WAVE_VQ_INJECT_VQ_VAL_SET(x) (((uint32_t)(x) << QEOV2_WAVE_VQ_INJECT_VQ_VAL_SHIFT) & QEOV2_WAVE_VQ_INJECT_VQ_VAL_MASK)
#define QEOV2_WAVE_VQ_INJECT_VQ_VAL_GET(x) (((uint32_t)(x) & QEOV2_WAVE_VQ_INJECT_VQ_VAL_MASK) >> QEOV2_WAVE_VQ_INJECT_VQ_VAL_SHIFT)

/* Bitfield definition for register of struct WAVE: VD_VQ_LOAD */
/*
 * LOAD (WO)
 *
 * load wave0/1/2 vd vq value.  always read 0
 * 0: vd vq keep previous value.
 * 1: load wave0/1/2 vd vq value at sametime.
 */
#define QEOV2_WAVE_VD_VQ_LOAD_LOAD_MASK (0x1U)
#define QEOV2_WAVE_VD_VQ_LOAD_LOAD_SHIFT (0U)
#define QEOV2_WAVE_VD_VQ_LOAD_LOAD_SET(x) (((uint32_t)(x) << QEOV2_WAVE_VD_VQ_LOAD_LOAD_SHIFT) & QEOV2_WAVE_VD_VQ_LOAD_LOAD_MASK)
#define QEOV2_WAVE_VD_VQ_LOAD_LOAD_GET(x) (((uint32_t)(x) & QEOV2_WAVE_VD_VQ_LOAD_LOAD_MASK) >> QEOV2_WAVE_VD_VQ_LOAD_LOAD_SHIFT)

/* Bitfield definition for register of struct WAVE: WAVE0 */
/*
 * EN_SCAL (RW)
 *
 * enable wave amplitude scaling. 0: disable; 1: enable
 */
#define QEOV2_WAVE_AMPLITUDE_EN_SCAL_MASK (0x10000UL)
#define QEOV2_WAVE_AMPLITUDE_EN_SCAL_SHIFT (16U)
#define QEOV2_WAVE_AMPLITUDE_EN_SCAL_SET(x) (((uint32_t)(x) << QEOV2_WAVE_AMPLITUDE_EN_SCAL_SHIFT) & QEOV2_WAVE_AMPLITUDE_EN_SCAL_MASK)
#define QEOV2_WAVE_AMPLITUDE_EN_SCAL_GET(x) (((uint32_t)(x) & QEOV2_WAVE_AMPLITUDE_EN_SCAL_MASK) >> QEOV2_WAVE_AMPLITUDE_EN_SCAL_SHIFT)

/*
 * AMP_VAL (RW)
 *
 * amplitude scaling value. bit15-12 are integer part value. bit11-0 are fraction value.
 */
#define QEOV2_WAVE_AMPLITUDE_AMP_VAL_MASK (0xFFFFU)
#define QEOV2_WAVE_AMPLITUDE_AMP_VAL_SHIFT (0U)
#define QEOV2_WAVE_AMPLITUDE_AMP_VAL_SET(x) (((uint32_t)(x) << QEOV2_WAVE_AMPLITUDE_AMP_VAL_SHIFT) & QEOV2_WAVE_AMPLITUDE_AMP_VAL_MASK)
#define QEOV2_WAVE_AMPLITUDE_AMP_VAL_GET(x) (((uint32_t)(x) & QEOV2_WAVE_AMPLITUDE_AMP_VAL_MASK) >> QEOV2_WAVE_AMPLITUDE_AMP_VAL_SHIFT)

/* Bitfield definition for register of struct WAVE: WAVE0 */
/*
 * VAL (RW)
 *
 * wave0 output middle point, use this value as 32 bit signed value. bit 31 is signed bit. bit30-27 is integer part value. bit26-0 is fraction value.
 */
#define QEOV2_WAVE_MID_POINT_VAL_MASK (0xFFFFFFFFUL)
#define QEOV2_WAVE_MID_POINT_VAL_SHIFT (0U)
#define QEOV2_WAVE_MID_POINT_VAL_SET(x) (((uint32_t)(x) << QEOV2_WAVE_MID_POINT_VAL_SHIFT) & QEOV2_WAVE_MID_POINT_VAL_MASK)
#define QEOV2_WAVE_MID_POINT_VAL_GET(x) (((uint32_t)(x) & QEOV2_WAVE_MID_POINT_VAL_MASK) >> QEOV2_WAVE_MID_POINT_VAL_SHIFT)

/* Bitfield definition for register of struct WAVE: MIN_LEVEL0 */
/*
 * LIMIT_LEVEL0 (RW)
 *
 * low area limit level0
 */
#define QEOV2_WAVE_LIMIT0_MIN_LEVEL0_LIMIT_LEVEL0_MASK (0xFFFFFFFFUL)
#define QEOV2_WAVE_LIMIT0_MIN_LEVEL0_LIMIT_LEVEL0_SHIFT (0U)
#define QEOV2_WAVE_LIMIT0_MIN_LEVEL0_LIMIT_LEVEL0_SET(x) (((uint32_t)(x) << QEOV2_WAVE_LIMIT0_MIN_LEVEL0_LIMIT_LEVEL0_SHIFT) & QEOV2_WAVE_LIMIT0_MIN_LEVEL0_LIMIT_LEVEL0_MASK)
#define QEOV2_WAVE_LIMIT0_MIN_LEVEL0_LIMIT_LEVEL0_GET(x) (((uint32_t)(x) & QEOV2_WAVE_LIMIT0_MIN_LEVEL0_LIMIT_LEVEL0_MASK) >> QEOV2_WAVE_LIMIT0_MIN_LEVEL0_LIMIT_LEVEL0_SHIFT)

/* Bitfield definition for register of struct WAVE: MAX_LEVEL0 */
/*
 * LIMIT_LEVEL0 (RW)
 *
 * high area limit level0
 */
#define QEOV2_WAVE_LIMIT0_MAX_LEVEL0_LIMIT_LEVEL0_MASK (0xFFFFFFFFUL)
#define QEOV2_WAVE_LIMIT0_MAX_LEVEL0_LIMIT_LEVEL0_SHIFT (0U)
#define QEOV2_WAVE_LIMIT0_MAX_LEVEL0_LIMIT_LEVEL0_SET(x) (((uint32_t)(x) << QEOV2_WAVE_LIMIT0_MAX_LEVEL0_LIMIT_LEVEL0_SHIFT) & QEOV2_WAVE_LIMIT0_MAX_LEVEL0_LIMIT_LEVEL0_MASK)
#define QEOV2_WAVE_LIMIT0_MAX_LEVEL0_LIMIT_LEVEL0_GET(x) (((uint32_t)(x) & QEOV2_WAVE_LIMIT0_MAX_LEVEL0_LIMIT_LEVEL0_MASK) >> QEOV2_WAVE_LIMIT0_MAX_LEVEL0_LIMIT_LEVEL0_SHIFT)

/* Bitfield definition for register of struct WAVE: MIN_LEVEL1 */
/*
 * LIMIT_LEVEL1 (RW)
 *
 * low area limit level1
 */
#define QEOV2_WAVE_LIMIT1_MIN_LEVEL1_LIMIT_LEVEL1_MASK (0xFFFFFFFFUL)
#define QEOV2_WAVE_LIMIT1_MIN_LEVEL1_LIMIT_LEVEL1_SHIFT (0U)
#define QEOV2_WAVE_LIMIT1_MIN_LEVEL1_LIMIT_LEVEL1_SET(x) (((uint32_t)(x) << QEOV2_WAVE_LIMIT1_MIN_LEVEL1_LIMIT_LEVEL1_SHIFT) & QEOV2_WAVE_LIMIT1_MIN_LEVEL1_LIMIT_LEVEL1_MASK)
#define QEOV2_WAVE_LIMIT1_MIN_LEVEL1_LIMIT_LEVEL1_GET(x) (((uint32_t)(x) & QEOV2_WAVE_LIMIT1_MIN_LEVEL1_LIMIT_LEVEL1_MASK) >> QEOV2_WAVE_LIMIT1_MIN_LEVEL1_LIMIT_LEVEL1_SHIFT)

/* Bitfield definition for register of struct WAVE: MAX_LEVEL1 */
/*
 * LIMIT_LEVEL1 (RW)
 *
 * high area limit level1
 */
#define QEOV2_WAVE_LIMIT1_MAX_LEVEL1_LIMIT_LEVEL1_MASK (0xFFFFFFFFUL)
#define QEOV2_WAVE_LIMIT1_MAX_LEVEL1_LIMIT_LEVEL1_SHIFT (0U)
#define QEOV2_WAVE_LIMIT1_MAX_LEVEL1_LIMIT_LEVEL1_SET(x) (((uint32_t)(x) << QEOV2_WAVE_LIMIT1_MAX_LEVEL1_LIMIT_LEVEL1_SHIFT) & QEOV2_WAVE_LIMIT1_MAX_LEVEL1_LIMIT_LEVEL1_MASK)
#define QEOV2_WAVE_LIMIT1_MAX_LEVEL1_LIMIT_LEVEL1_GET(x) (((uint32_t)(x) & QEOV2_WAVE_LIMIT1_MAX_LEVEL1_LIMIT_LEVEL1_MASK) >> QEOV2_WAVE_LIMIT1_MAX_LEVEL1_LIMIT_LEVEL1_SHIFT)

/* Bitfield definition for register of struct WAVE: WAVE0 */
/*
 * VAL (RW)
 *
 * wave0 deadzone shifter value
 */
#define QEOV2_WAVE_DEADZONE_SHIFT_VAL_MASK (0xFFFFFFFFUL)
#define QEOV2_WAVE_DEADZONE_SHIFT_VAL_SHIFT (0U)
#define QEOV2_WAVE_DEADZONE_SHIFT_VAL_SET(x) (((uint32_t)(x) << QEOV2_WAVE_DEADZONE_SHIFT_VAL_SHIFT) & QEOV2_WAVE_DEADZONE_SHIFT_VAL_MASK)
#define QEOV2_WAVE_DEADZONE_SHIFT_VAL_GET(x) (((uint32_t)(x) & QEOV2_WAVE_DEADZONE_SHIFT_VAL_MASK) >> QEOV2_WAVE_DEADZONE_SHIFT_VAL_SHIFT)

/* Bitfield definition for register of struct WAVE: PWM_CYCLE */
/*
 * VAL (RW)
 *
 * pwm_cycle
 */
#define QEOV2_WAVE_PWM_CYCLE_VAL_MASK (0xFFFFFFFFUL)
#define QEOV2_WAVE_PWM_CYCLE_VAL_SHIFT (0U)
#define QEOV2_WAVE_PWM_CYCLE_VAL_SET(x) (((uint32_t)(x) << QEOV2_WAVE_PWM_CYCLE_VAL_SHIFT) & QEOV2_WAVE_PWM_CYCLE_VAL_MASK)
#define QEOV2_WAVE_PWM_CYCLE_VAL_GET(x) (((uint32_t)(x) & QEOV2_WAVE_PWM_CYCLE_VAL_MASK) >> QEOV2_WAVE_PWM_CYCLE_VAL_SHIFT)

/* Bitfield definition for register of struct ABZ: MODE */
/*
 * ABZ_OUTPUT_ENABLE (RW)
 *
 * abz output enable：
 * 0：abz output disable, all keep 0
 * 1：abz output enable.
 */
#define QEOV2_ABZ_MODE_ABZ_OUTPUT_ENABLE_MASK (0x80000000UL)
#define QEOV2_ABZ_MODE_ABZ_OUTPUT_ENABLE_SHIFT (31U)
#define QEOV2_ABZ_MODE_ABZ_OUTPUT_ENABLE_SET(x) (((uint32_t)(x) << QEOV2_ABZ_MODE_ABZ_OUTPUT_ENABLE_SHIFT) & QEOV2_ABZ_MODE_ABZ_OUTPUT_ENABLE_MASK)
#define QEOV2_ABZ_MODE_ABZ_OUTPUT_ENABLE_GET(x) (((uint32_t)(x) & QEOV2_ABZ_MODE_ABZ_OUTPUT_ENABLE_MASK) >> QEOV2_ABZ_MODE_ABZ_OUTPUT_ENABLE_SHIFT)

/*
 * REVERSE_EDGE_TYPE (RW)
 *
 * pulse reverse wave，reverse edge point:
 * 0: between pulse's posedge and negedge, min period dedicated by the num line_width
 * 1: edge change point flow pulse's negedge.
 */
#define QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_MASK (0x10000000UL)
#define QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_SHIFT (28U)
#define QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_SET(x) (((uint32_t)(x) << QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_SHIFT) & QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_MASK)
#define QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_GET(x) (((uint32_t)(x) & QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_MASK) >> QEOV2_ABZ_MODE_REVERSE_EDGE_TYPE_SHIFT)

/*
 * POSITION_SYNC_MODE (RW)
 *
 * position sync mode:
 * 0: only sync integer line part into qeo own position.
 * 1: sync integer and fraction part into qeo own position.
 */
#define QEOV2_ABZ_MODE_POSITION_SYNC_MODE_MASK (0x8000000UL)
#define QEOV2_ABZ_MODE_POSITION_SYNC_MODE_SHIFT (27U)
#define QEOV2_ABZ_MODE_POSITION_SYNC_MODE_SET(x) (((uint32_t)(x) << QEOV2_ABZ_MODE_POSITION_SYNC_MODE_SHIFT) & QEOV2_ABZ_MODE_POSITION_SYNC_MODE_MASK)
#define QEOV2_ABZ_MODE_POSITION_SYNC_MODE_GET(x) (((uint32_t)(x) & QEOV2_ABZ_MODE_POSITION_SYNC_MODE_MASK) >> QEOV2_ABZ_MODE_POSITION_SYNC_MODE_SHIFT)

/*
 * EN_WDOG (RW)
 *
 * enable abz wdog:
 * 0: disable abz wdog.
 * 1: enable abz wdog.
 */
#define QEOV2_ABZ_MODE_EN_WDOG_MASK (0x1000000UL)
#define QEOV2_ABZ_MODE_EN_WDOG_SHIFT (24U)
#define QEOV2_ABZ_MODE_EN_WDOG_SET(x) (((uint32_t)(x) << QEOV2_ABZ_MODE_EN_WDOG_SHIFT) & QEOV2_ABZ_MODE_EN_WDOG_MASK)
#define QEOV2_ABZ_MODE_EN_WDOG_GET(x) (((uint32_t)(x) & QEOV2_ABZ_MODE_EN_WDOG_MASK) >> QEOV2_ABZ_MODE_EN_WDOG_SHIFT)

/*
 * Z_POLARITY (RW)
 *
 * wave_z polarity.
 * 0: normal output.
 * 1: invert normal output
 */
#define QEOV2_ABZ_MODE_Z_POLARITY_MASK (0x100000UL)
#define QEOV2_ABZ_MODE_Z_POLARITY_SHIFT (20U)
#define QEOV2_ABZ_MODE_Z_POLARITY_SET(x) (((uint32_t)(x) << QEOV2_ABZ_MODE_Z_POLARITY_SHIFT) & QEOV2_ABZ_MODE_Z_POLARITY_MASK)
#define QEOV2_ABZ_MODE_Z_POLARITY_GET(x) (((uint32_t)(x) & QEOV2_ABZ_MODE_Z_POLARITY_MASK) >> QEOV2_ABZ_MODE_Z_POLARITY_SHIFT)

/*
 * B_POLARITY (RW)
 *
 * wave_b polarity.
 * 0: normal output.
 * 1: invert normal output
 */
#define QEOV2_ABZ_MODE_B_POLARITY_MASK (0x10000UL)
#define QEOV2_ABZ_MODE_B_POLARITY_SHIFT (16U)
#define QEOV2_ABZ_MODE_B_POLARITY_SET(x) (((uint32_t)(x) << QEOV2_ABZ_MODE_B_POLARITY_SHIFT) & QEOV2_ABZ_MODE_B_POLARITY_MASK)
#define QEOV2_ABZ_MODE_B_POLARITY_GET(x) (((uint32_t)(x) & QEOV2_ABZ_MODE_B_POLARITY_MASK) >> QEOV2_ABZ_MODE_B_POLARITY_SHIFT)

/*
 * A_POLARITY (RW)
 *
 * wave_a polarity.
 * 0: normal output.
 * 1: invert normal output
 */
#define QEOV2_ABZ_MODE_A_POLARITY_MASK (0x1000U)
#define QEOV2_ABZ_MODE_A_POLARITY_SHIFT (12U)
#define QEOV2_ABZ_MODE_A_POLARITY_SET(x) (((uint32_t)(x) << QEOV2_ABZ_MODE_A_POLARITY_SHIFT) & QEOV2_ABZ_MODE_A_POLARITY_MASK)
#define QEOV2_ABZ_MODE_A_POLARITY_GET(x) (((uint32_t)(x) & QEOV2_ABZ_MODE_A_POLARITY_MASK) >> QEOV2_ABZ_MODE_A_POLARITY_SHIFT)

/*
 * Z_TYPE (RW)
 *
 * wave_z type:
 * 0: zero pulse type, start and end line number decided by z_start、z_end and z_offset.
 * 1: zero pulse type, z output start to high when position= z_start, and mantain numbers of 1/4 line cfg in z_pulse_width register
 * 2: reserved
 * 3: wave_z output as tree-phase wave same as wave_a/wave_b
 */
#define QEOV2_ABZ_MODE_Z_TYPE_MASK (0x300U)
#define QEOV2_ABZ_MODE_Z_TYPE_SHIFT (8U)
#define QEOV2_ABZ_MODE_Z_TYPE_SET(x) (((uint32_t)(x) << QEOV2_ABZ_MODE_Z_TYPE_SHIFT) & QEOV2_ABZ_MODE_Z_TYPE_MASK)
#define QEOV2_ABZ_MODE_Z_TYPE_GET(x) (((uint32_t)(x) & QEOV2_ABZ_MODE_Z_TYPE_MASK) >> QEOV2_ABZ_MODE_Z_TYPE_SHIFT)

/*
 * B_TYPE (RW)
 *
 * wave_b type:
 * 0: Two-phase orthogonality wave_b.
 * 1: reverse wave of pulse/reverse type.
 * 2: down wave of up/down type.
 * 3: Three-phase orthogonality wave_b.
 */
#define QEOV2_ABZ_MODE_B_TYPE_MASK (0x30U)
#define QEOV2_ABZ_MODE_B_TYPE_SHIFT (4U)
#define QEOV2_ABZ_MODE_B_TYPE_SET(x) (((uint32_t)(x) << QEOV2_ABZ_MODE_B_TYPE_SHIFT) & QEOV2_ABZ_MODE_B_TYPE_MASK)
#define QEOV2_ABZ_MODE_B_TYPE_GET(x) (((uint32_t)(x) & QEOV2_ABZ_MODE_B_TYPE_MASK) >> QEOV2_ABZ_MODE_B_TYPE_SHIFT)

/*
 * A_TYPE (RW)
 *
 * wave_a type:
 * 0: Two-phase orthogonality wave_a.
 * 1: pulse wave of pulse/reverse type.
 * 2: up wave of up/down type.
 * 3: Three-phase orthogonality wave_a.
 */
#define QEOV2_ABZ_MODE_A_TYPE_MASK (0x3U)
#define QEOV2_ABZ_MODE_A_TYPE_SHIFT (0U)
#define QEOV2_ABZ_MODE_A_TYPE_SET(x) (((uint32_t)(x) << QEOV2_ABZ_MODE_A_TYPE_SHIFT) & QEOV2_ABZ_MODE_A_TYPE_MASK)
#define QEOV2_ABZ_MODE_A_TYPE_GET(x) (((uint32_t)(x) & QEOV2_ABZ_MODE_A_TYPE_MASK) >> QEOV2_ABZ_MODE_A_TYPE_SHIFT)

/* Bitfield definition for register of struct ABZ: RESOLUTION */
/*
 * LINES (RW)
 *
 * wave_a/b/z resolution
 */
#define QEOV2_ABZ_RESOLUTION_LINES_MASK (0xFFFFFFFFUL)
#define QEOV2_ABZ_RESOLUTION_LINES_SHIFT (0U)
#define QEOV2_ABZ_RESOLUTION_LINES_SET(x) (((uint32_t)(x) << QEOV2_ABZ_RESOLUTION_LINES_SHIFT) & QEOV2_ABZ_RESOLUTION_LINES_MASK)
#define QEOV2_ABZ_RESOLUTION_LINES_GET(x) (((uint32_t)(x) & QEOV2_ABZ_RESOLUTION_LINES_MASK) >> QEOV2_ABZ_RESOLUTION_LINES_SHIFT)

/* Bitfield definition for register of struct ABZ: A */
/*
 * VAL (RW)
 *
 * wave_a phase shifter value, default is 0x0. write other value will shift phase early as (cfg_value/2^32) period.
 */
#define QEOV2_ABZ_PHASE_SHIFT_VAL_MASK (0xFFFFFFFFUL)
#define QEOV2_ABZ_PHASE_SHIFT_VAL_SHIFT (0U)
#define QEOV2_ABZ_PHASE_SHIFT_VAL_SET(x) (((uint32_t)(x) << QEOV2_ABZ_PHASE_SHIFT_VAL_SHIFT) & QEOV2_ABZ_PHASE_SHIFT_VAL_MASK)
#define QEOV2_ABZ_PHASE_SHIFT_VAL_GET(x) (((uint32_t)(x) & QEOV2_ABZ_PHASE_SHIFT_VAL_MASK) >> QEOV2_ABZ_PHASE_SHIFT_VAL_SHIFT)

/* Bitfield definition for register of struct ABZ: LINE_WIDTH */
/*
 * LINE (RW)
 *
 * the num of system clk by 1/4 period when using as Two-phase orthogonality.
 */
#define QEOV2_ABZ_LINE_WIDTH_LINE_MASK (0xFFFFFFFFUL)
#define QEOV2_ABZ_LINE_WIDTH_LINE_SHIFT (0U)
#define QEOV2_ABZ_LINE_WIDTH_LINE_SET(x) (((uint32_t)(x) << QEOV2_ABZ_LINE_WIDTH_LINE_SHIFT) & QEOV2_ABZ_LINE_WIDTH_LINE_MASK)
#define QEOV2_ABZ_LINE_WIDTH_LINE_GET(x) (((uint32_t)(x) & QEOV2_ABZ_LINE_WIDTH_LINE_MASK) >> QEOV2_ABZ_LINE_WIDTH_LINE_SHIFT)

/* Bitfield definition for register of struct ABZ: WDOG_WIDTH */
/*
 * WIDTH (RW)
 *
 * wave will step 1/4 line to reminder user QEO still in controlled if QEO has no any toggle after the num of wdog_width sys clk.
 */
#define QEOV2_ABZ_WDOG_WIDTH_WIDTH_MASK (0xFFFFFFFFUL)
#define QEOV2_ABZ_WDOG_WIDTH_WIDTH_SHIFT (0U)
#define QEOV2_ABZ_WDOG_WIDTH_WIDTH_SET(x) (((uint32_t)(x) << QEOV2_ABZ_WDOG_WIDTH_WIDTH_SHIFT) & QEOV2_ABZ_WDOG_WIDTH_WIDTH_MASK)
#define QEOV2_ABZ_WDOG_WIDTH_WIDTH_GET(x) (((uint32_t)(x) & QEOV2_ABZ_WDOG_WIDTH_WIDTH_MASK) >> QEOV2_ABZ_WDOG_WIDTH_WIDTH_SHIFT)

/* Bitfield definition for register of struct ABZ: POSTION_SYNC */
/*
 * POSTION (WO)
 *
 * load next valid postion into  abz owned postion.  always read 0
 * 0: sync abz owned postion with next valid postion.
 * 1: not sync.
 */
#define QEOV2_ABZ_POSTION_SYNC_POSTION_MASK (0x1U)
#define QEOV2_ABZ_POSTION_SYNC_POSTION_SHIFT (0U)
#define QEOV2_ABZ_POSTION_SYNC_POSTION_SET(x) (((uint32_t)(x) << QEOV2_ABZ_POSTION_SYNC_POSTION_SHIFT) & QEOV2_ABZ_POSTION_SYNC_POSTION_MASK)
#define QEOV2_ABZ_POSTION_SYNC_POSTION_GET(x) (((uint32_t)(x) & QEOV2_ABZ_POSTION_SYNC_POSTION_MASK) >> QEOV2_ABZ_POSTION_SYNC_POSTION_SHIFT)

/* Bitfield definition for register of struct ABZ: OVERALL_OFFSET */
/*
 * VAL (RW)
 *
 * abz position overall offset, it affects abz position before resolution convert
 */
#define QEOV2_ABZ_OVERALL_OFFSET_VAL_MASK (0xFFFFFFFFUL)
#define QEOV2_ABZ_OVERALL_OFFSET_VAL_SHIFT (0U)
#define QEOV2_ABZ_OVERALL_OFFSET_VAL_SET(x) (((uint32_t)(x) << QEOV2_ABZ_OVERALL_OFFSET_VAL_SHIFT) & QEOV2_ABZ_OVERALL_OFFSET_VAL_MASK)
#define QEOV2_ABZ_OVERALL_OFFSET_VAL_GET(x) (((uint32_t)(x) & QEOV2_ABZ_OVERALL_OFFSET_VAL_MASK) >> QEOV2_ABZ_OVERALL_OFFSET_VAL_SHIFT)

/* Bitfield definition for register of struct ABZ: Z_START */
/*
 * Z_START (RW)
 *
 * number of Z start line
 */
#define QEOV2_ABZ_Z_START_Z_START_MASK (0xFFFFFFFFUL)
#define QEOV2_ABZ_Z_START_Z_START_SHIFT (0U)
#define QEOV2_ABZ_Z_START_Z_START_SET(x) (((uint32_t)(x) << QEOV2_ABZ_Z_START_Z_START_SHIFT) & QEOV2_ABZ_Z_START_Z_START_MASK)
#define QEOV2_ABZ_Z_START_Z_START_GET(x) (((uint32_t)(x) & QEOV2_ABZ_Z_START_Z_START_MASK) >> QEOV2_ABZ_Z_START_Z_START_SHIFT)

/* Bitfield definition for register of struct ABZ: Z_END */
/*
 * Z_END (RW)
 *
 * number of Z end line
 */
#define QEOV2_ABZ_Z_END_Z_END_MASK (0xFFFFFFFFUL)
#define QEOV2_ABZ_Z_END_Z_END_SHIFT (0U)
#define QEOV2_ABZ_Z_END_Z_END_SET(x) (((uint32_t)(x) << QEOV2_ABZ_Z_END_Z_END_SHIFT) & QEOV2_ABZ_Z_END_Z_END_MASK)
#define QEOV2_ABZ_Z_END_Z_END_GET(x) (((uint32_t)(x) & QEOV2_ABZ_Z_END_Z_END_MASK) >> QEOV2_ABZ_Z_END_Z_END_SHIFT)

/* Bitfield definition for register of struct ABZ: Z_OFFSET */
/*
 * Z_END_OFFSET (RW)
 *
 * number of Z end 1/4 line
 */
#define QEOV2_ABZ_Z_OFFSET_Z_END_OFFSET_MASK (0x300U)
#define QEOV2_ABZ_Z_OFFSET_Z_END_OFFSET_SHIFT (8U)
#define QEOV2_ABZ_Z_OFFSET_Z_END_OFFSET_SET(x) (((uint32_t)(x) << QEOV2_ABZ_Z_OFFSET_Z_END_OFFSET_SHIFT) & QEOV2_ABZ_Z_OFFSET_Z_END_OFFSET_MASK)
#define QEOV2_ABZ_Z_OFFSET_Z_END_OFFSET_GET(x) (((uint32_t)(x) & QEOV2_ABZ_Z_OFFSET_Z_END_OFFSET_MASK) >> QEOV2_ABZ_Z_OFFSET_Z_END_OFFSET_SHIFT)

/*
 * Z_START_OFFSET (RW)
 *
 * number of Z start 1/4 line
 */
#define QEOV2_ABZ_Z_OFFSET_Z_START_OFFSET_MASK (0x30U)
#define QEOV2_ABZ_Z_OFFSET_Z_START_OFFSET_SHIFT (4U)
#define QEOV2_ABZ_Z_OFFSET_Z_START_OFFSET_SET(x) (((uint32_t)(x) << QEOV2_ABZ_Z_OFFSET_Z_START_OFFSET_SHIFT) & QEOV2_ABZ_Z_OFFSET_Z_START_OFFSET_MASK)
#define QEOV2_ABZ_Z_OFFSET_Z_START_OFFSET_GET(x) (((uint32_t)(x) & QEOV2_ABZ_Z_OFFSET_Z_START_OFFSET_MASK) >> QEOV2_ABZ_Z_OFFSET_Z_START_OFFSET_SHIFT)

/* Bitfield definition for register of struct ABZ: Z_PULSE_WIDTH */
/*
 * VAL (RW)
 *
 * number of z_pulse_width
 */
#define QEOV2_ABZ_Z_PULSE_WIDTH_VAL_MASK (0xFFFFFFFFUL)
#define QEOV2_ABZ_Z_PULSE_WIDTH_VAL_SHIFT (0U)
#define QEOV2_ABZ_Z_PULSE_WIDTH_VAL_SET(x) (((uint32_t)(x) << QEOV2_ABZ_Z_PULSE_WIDTH_VAL_SHIFT) & QEOV2_ABZ_Z_PULSE_WIDTH_VAL_MASK)
#define QEOV2_ABZ_Z_PULSE_WIDTH_VAL_GET(x) (((uint32_t)(x) & QEOV2_ABZ_Z_PULSE_WIDTH_VAL_MASK) >> QEOV2_ABZ_Z_PULSE_WIDTH_VAL_SHIFT)

/* Bitfield definition for register of struct PWM: MODE */
/*
 * PWM7_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEOV2_PWM_MODE_PWM7_SAFETY_MASK (0xC0000000UL)
#define QEOV2_PWM_MODE_PWM7_SAFETY_SHIFT (30U)
#define QEOV2_PWM_MODE_PWM7_SAFETY_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_PWM7_SAFETY_SHIFT) & QEOV2_PWM_MODE_PWM7_SAFETY_MASK)
#define QEOV2_PWM_MODE_PWM7_SAFETY_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_PWM7_SAFETY_MASK) >> QEOV2_PWM_MODE_PWM7_SAFETY_SHIFT)

/*
 * PWM6_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEOV2_PWM_MODE_PWM6_SAFETY_MASK (0x30000000UL)
#define QEOV2_PWM_MODE_PWM6_SAFETY_SHIFT (28U)
#define QEOV2_PWM_MODE_PWM6_SAFETY_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_PWM6_SAFETY_SHIFT) & QEOV2_PWM_MODE_PWM6_SAFETY_MASK)
#define QEOV2_PWM_MODE_PWM6_SAFETY_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_PWM6_SAFETY_MASK) >> QEOV2_PWM_MODE_PWM6_SAFETY_SHIFT)

/*
 * PWM5_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEOV2_PWM_MODE_PWM5_SAFETY_MASK (0xC000000UL)
#define QEOV2_PWM_MODE_PWM5_SAFETY_SHIFT (26U)
#define QEOV2_PWM_MODE_PWM5_SAFETY_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_PWM5_SAFETY_SHIFT) & QEOV2_PWM_MODE_PWM5_SAFETY_MASK)
#define QEOV2_PWM_MODE_PWM5_SAFETY_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_PWM5_SAFETY_MASK) >> QEOV2_PWM_MODE_PWM5_SAFETY_SHIFT)

/*
 * PWM4_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEOV2_PWM_MODE_PWM4_SAFETY_MASK (0x3000000UL)
#define QEOV2_PWM_MODE_PWM4_SAFETY_SHIFT (24U)
#define QEOV2_PWM_MODE_PWM4_SAFETY_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_PWM4_SAFETY_SHIFT) & QEOV2_PWM_MODE_PWM4_SAFETY_MASK)
#define QEOV2_PWM_MODE_PWM4_SAFETY_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_PWM4_SAFETY_MASK) >> QEOV2_PWM_MODE_PWM4_SAFETY_SHIFT)

/*
 * PWM3_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEOV2_PWM_MODE_PWM3_SAFETY_MASK (0xC00000UL)
#define QEOV2_PWM_MODE_PWM3_SAFETY_SHIFT (22U)
#define QEOV2_PWM_MODE_PWM3_SAFETY_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_PWM3_SAFETY_SHIFT) & QEOV2_PWM_MODE_PWM3_SAFETY_MASK)
#define QEOV2_PWM_MODE_PWM3_SAFETY_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_PWM3_SAFETY_MASK) >> QEOV2_PWM_MODE_PWM3_SAFETY_SHIFT)

/*
 * PWM2_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEOV2_PWM_MODE_PWM2_SAFETY_MASK (0x300000UL)
#define QEOV2_PWM_MODE_PWM2_SAFETY_SHIFT (20U)
#define QEOV2_PWM_MODE_PWM2_SAFETY_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_PWM2_SAFETY_SHIFT) & QEOV2_PWM_MODE_PWM2_SAFETY_MASK)
#define QEOV2_PWM_MODE_PWM2_SAFETY_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_PWM2_SAFETY_MASK) >> QEOV2_PWM_MODE_PWM2_SAFETY_SHIFT)

/*
 * PWM1_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEOV2_PWM_MODE_PWM1_SAFETY_MASK (0xC0000UL)
#define QEOV2_PWM_MODE_PWM1_SAFETY_SHIFT (18U)
#define QEOV2_PWM_MODE_PWM1_SAFETY_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_PWM1_SAFETY_SHIFT) & QEOV2_PWM_MODE_PWM1_SAFETY_MASK)
#define QEOV2_PWM_MODE_PWM1_SAFETY_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_PWM1_SAFETY_MASK) >> QEOV2_PWM_MODE_PWM1_SAFETY_SHIFT)

/*
 * PWM0_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEOV2_PWM_MODE_PWM0_SAFETY_MASK (0x30000UL)
#define QEOV2_PWM_MODE_PWM0_SAFETY_SHIFT (16U)
#define QEOV2_PWM_MODE_PWM0_SAFETY_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_PWM0_SAFETY_SHIFT) & QEOV2_PWM_MODE_PWM0_SAFETY_MASK)
#define QEOV2_PWM_MODE_PWM0_SAFETY_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_PWM0_SAFETY_MASK) >> QEOV2_PWM_MODE_PWM0_SAFETY_SHIFT)

/*
 * ENABLE_PWM (RW)
 *
 * enable PWM force output
 * 0: disable
 * 1: enable
 */
#define QEOV2_PWM_MODE_ENABLE_PWM_MASK (0x8000U)
#define QEOV2_PWM_MODE_ENABLE_PWM_SHIFT (15U)
#define QEOV2_PWM_MODE_ENABLE_PWM_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_ENABLE_PWM_SHIFT) & QEOV2_PWM_MODE_ENABLE_PWM_MASK)
#define QEOV2_PWM_MODE_ENABLE_PWM_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_ENABLE_PWM_MASK) >> QEOV2_PWM_MODE_ENABLE_PWM_SHIFT)

/*
 * PWM_ENTER_SAFETY_MODE (RW)
 *
 * PWM  enter safety mode
 * 0: not enter
 * 1: enter
 */
#define QEOV2_PWM_MODE_PWM_ENTER_SAFETY_MODE_MASK (0x200U)
#define QEOV2_PWM_MODE_PWM_ENTER_SAFETY_MODE_SHIFT (9U)
#define QEOV2_PWM_MODE_PWM_ENTER_SAFETY_MODE_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_PWM_ENTER_SAFETY_MODE_SHIFT) & QEOV2_PWM_MODE_PWM_ENTER_SAFETY_MODE_MASK)
#define QEOV2_PWM_MODE_PWM_ENTER_SAFETY_MODE_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_PWM_ENTER_SAFETY_MODE_MASK) >> QEOV2_PWM_MODE_PWM_ENTER_SAFETY_MODE_SHIFT)

/*
 * PWM_SAFETY_BYPASS (RW)
 *
 * PWM safety mode bypass
 * 0: not bypass
 * 1: bypass
 */
#define QEOV2_PWM_MODE_PWM_SAFETY_BYPASS_MASK (0x100U)
#define QEOV2_PWM_MODE_PWM_SAFETY_BYPASS_SHIFT (8U)
#define QEOV2_PWM_MODE_PWM_SAFETY_BYPASS_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_PWM_SAFETY_BYPASS_SHIFT) & QEOV2_PWM_MODE_PWM_SAFETY_BYPASS_MASK)
#define QEOV2_PWM_MODE_PWM_SAFETY_BYPASS_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_PWM_SAFETY_BYPASS_MASK) >> QEOV2_PWM_MODE_PWM_SAFETY_BYPASS_SHIFT)

/*
 * REVISE_UP_DN (RW)
 *
 * exchange PWM pairs’ output
 * 0: not exchange.
 * 1: exchange.
 */
#define QEOV2_PWM_MODE_REVISE_UP_DN_MASK (0x10U)
#define QEOV2_PWM_MODE_REVISE_UP_DN_SHIFT (4U)
#define QEOV2_PWM_MODE_REVISE_UP_DN_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_REVISE_UP_DN_SHIFT) & QEOV2_PWM_MODE_REVISE_UP_DN_MASK)
#define QEOV2_PWM_MODE_REVISE_UP_DN_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_REVISE_UP_DN_MASK) >> QEOV2_PWM_MODE_REVISE_UP_DN_SHIFT)

/*
 * PHASE_NUM (RW)
 *
 * pwm force phase number.
 */
#define QEOV2_PWM_MODE_PHASE_NUM_MASK (0xFU)
#define QEOV2_PWM_MODE_PHASE_NUM_SHIFT (0U)
#define QEOV2_PWM_MODE_PHASE_NUM_SET(x) (((uint32_t)(x) << QEOV2_PWM_MODE_PHASE_NUM_SHIFT) & QEOV2_PWM_MODE_PHASE_NUM_MASK)
#define QEOV2_PWM_MODE_PHASE_NUM_GET(x) (((uint32_t)(x) & QEOV2_PWM_MODE_PHASE_NUM_MASK) >> QEOV2_PWM_MODE_PHASE_NUM_SHIFT)

/* Bitfield definition for register of struct PWM: RESOLUTION */
/*
 * LINES (RW)
 *
 * pwm resolution
 */
#define QEOV2_PWM_RESOLUTION_LINES_MASK (0xFFFFFFFFUL)
#define QEOV2_PWM_RESOLUTION_LINES_SHIFT (0U)
#define QEOV2_PWM_RESOLUTION_LINES_SET(x) (((uint32_t)(x) << QEOV2_PWM_RESOLUTION_LINES_SHIFT) & QEOV2_PWM_RESOLUTION_LINES_MASK)
#define QEOV2_PWM_RESOLUTION_LINES_GET(x) (((uint32_t)(x) & QEOV2_PWM_RESOLUTION_LINES_MASK) >> QEOV2_PWM_RESOLUTION_LINES_SHIFT)

/* Bitfield definition for register of struct PWM: A */
/*
 * VAL (RW)
 *
 * pwm_a phase shifter value, default is 0x0. write other value will shift phase early as (cfg_value/2^32) period
 */
#define QEOV2_PWM_PHASE_SHIFT_VAL_MASK (0xFFFFFFFFUL)
#define QEOV2_PWM_PHASE_SHIFT_VAL_SHIFT (0U)
#define QEOV2_PWM_PHASE_SHIFT_VAL_SET(x) (((uint32_t)(x) << QEOV2_PWM_PHASE_SHIFT_VAL_SHIFT) & QEOV2_PWM_PHASE_SHIFT_VAL_MASK)
#define QEOV2_PWM_PHASE_SHIFT_VAL_GET(x) (((uint32_t)(x) & QEOV2_PWM_PHASE_SHIFT_VAL_MASK) >> QEOV2_PWM_PHASE_SHIFT_VAL_SHIFT)

/* Bitfield definition for register of struct PWM: POSEDGE0 */
/*
 * PWM7 (RW)
 *
 * pwm phase table value
 */
#define QEOV2_PWM_PHASE_TABLE_PWM7_MASK (0xC000U)
#define QEOV2_PWM_PHASE_TABLE_PWM7_SHIFT (14U)
#define QEOV2_PWM_PHASE_TABLE_PWM7_SET(x) (((uint32_t)(x) << QEOV2_PWM_PHASE_TABLE_PWM7_SHIFT) & QEOV2_PWM_PHASE_TABLE_PWM7_MASK)
#define QEOV2_PWM_PHASE_TABLE_PWM7_GET(x) (((uint32_t)(x) & QEOV2_PWM_PHASE_TABLE_PWM7_MASK) >> QEOV2_PWM_PHASE_TABLE_PWM7_SHIFT)

/*
 * PWM6 (RW)
 *
 * pwm phase table value
 */
#define QEOV2_PWM_PHASE_TABLE_PWM6_MASK (0x3000U)
#define QEOV2_PWM_PHASE_TABLE_PWM6_SHIFT (12U)
#define QEOV2_PWM_PHASE_TABLE_PWM6_SET(x) (((uint32_t)(x) << QEOV2_PWM_PHASE_TABLE_PWM6_SHIFT) & QEOV2_PWM_PHASE_TABLE_PWM6_MASK)
#define QEOV2_PWM_PHASE_TABLE_PWM6_GET(x) (((uint32_t)(x) & QEOV2_PWM_PHASE_TABLE_PWM6_MASK) >> QEOV2_PWM_PHASE_TABLE_PWM6_SHIFT)

/*
 * PWM5 (RW)
 *
 * pwm phase table value
 */
#define QEOV2_PWM_PHASE_TABLE_PWM5_MASK (0xC00U)
#define QEOV2_PWM_PHASE_TABLE_PWM5_SHIFT (10U)
#define QEOV2_PWM_PHASE_TABLE_PWM5_SET(x) (((uint32_t)(x) << QEOV2_PWM_PHASE_TABLE_PWM5_SHIFT) & QEOV2_PWM_PHASE_TABLE_PWM5_MASK)
#define QEOV2_PWM_PHASE_TABLE_PWM5_GET(x) (((uint32_t)(x) & QEOV2_PWM_PHASE_TABLE_PWM5_MASK) >> QEOV2_PWM_PHASE_TABLE_PWM5_SHIFT)

/*
 * PWM4 (RW)
 *
 * pwm phase table value
 */
#define QEOV2_PWM_PHASE_TABLE_PWM4_MASK (0x300U)
#define QEOV2_PWM_PHASE_TABLE_PWM4_SHIFT (8U)
#define QEOV2_PWM_PHASE_TABLE_PWM4_SET(x) (((uint32_t)(x) << QEOV2_PWM_PHASE_TABLE_PWM4_SHIFT) & QEOV2_PWM_PHASE_TABLE_PWM4_MASK)
#define QEOV2_PWM_PHASE_TABLE_PWM4_GET(x) (((uint32_t)(x) & QEOV2_PWM_PHASE_TABLE_PWM4_MASK) >> QEOV2_PWM_PHASE_TABLE_PWM4_SHIFT)

/*
 * PWM3 (RW)
 *
 * pwm phase table value
 */
#define QEOV2_PWM_PHASE_TABLE_PWM3_MASK (0xC0U)
#define QEOV2_PWM_PHASE_TABLE_PWM3_SHIFT (6U)
#define QEOV2_PWM_PHASE_TABLE_PWM3_SET(x) (((uint32_t)(x) << QEOV2_PWM_PHASE_TABLE_PWM3_SHIFT) & QEOV2_PWM_PHASE_TABLE_PWM3_MASK)
#define QEOV2_PWM_PHASE_TABLE_PWM3_GET(x) (((uint32_t)(x) & QEOV2_PWM_PHASE_TABLE_PWM3_MASK) >> QEOV2_PWM_PHASE_TABLE_PWM3_SHIFT)

/*
 * PWM2 (RW)
 *
 * pwm phase table value
 */
#define QEOV2_PWM_PHASE_TABLE_PWM2_MASK (0x30U)
#define QEOV2_PWM_PHASE_TABLE_PWM2_SHIFT (4U)
#define QEOV2_PWM_PHASE_TABLE_PWM2_SET(x) (((uint32_t)(x) << QEOV2_PWM_PHASE_TABLE_PWM2_SHIFT) & QEOV2_PWM_PHASE_TABLE_PWM2_MASK)
#define QEOV2_PWM_PHASE_TABLE_PWM2_GET(x) (((uint32_t)(x) & QEOV2_PWM_PHASE_TABLE_PWM2_MASK) >> QEOV2_PWM_PHASE_TABLE_PWM2_SHIFT)

/*
 * PWM1 (RW)
 *
 * pwm phase table value
 */
#define QEOV2_PWM_PHASE_TABLE_PWM1_MASK (0xCU)
#define QEOV2_PWM_PHASE_TABLE_PWM1_SHIFT (2U)
#define QEOV2_PWM_PHASE_TABLE_PWM1_SET(x) (((uint32_t)(x) << QEOV2_PWM_PHASE_TABLE_PWM1_SHIFT) & QEOV2_PWM_PHASE_TABLE_PWM1_MASK)
#define QEOV2_PWM_PHASE_TABLE_PWM1_GET(x) (((uint32_t)(x) & QEOV2_PWM_PHASE_TABLE_PWM1_MASK) >> QEOV2_PWM_PHASE_TABLE_PWM1_SHIFT)

/*
 * PWM0 (RW)
 *
 * pwm phase table value
 */
#define QEOV2_PWM_PHASE_TABLE_PWM0_MASK (0x3U)
#define QEOV2_PWM_PHASE_TABLE_PWM0_SHIFT (0U)
#define QEOV2_PWM_PHASE_TABLE_PWM0_SET(x) (((uint32_t)(x) << QEOV2_PWM_PHASE_TABLE_PWM0_SHIFT) & QEOV2_PWM_PHASE_TABLE_PWM0_MASK)
#define QEOV2_PWM_PHASE_TABLE_PWM0_GET(x) (((uint32_t)(x) & QEOV2_PWM_PHASE_TABLE_PWM0_MASK) >> QEOV2_PWM_PHASE_TABLE_PWM0_SHIFT)

/* Bitfield definition for register: POSTION_SOFTWARE */
/*
 * POSTION_SOFTWAVE (RW)
 *
 * softwave inject postion
 */
#define QEOV2_POSTION_SOFTWARE_POSTION_SOFTWAVE_MASK (0xFFFFFFFFUL)
#define QEOV2_POSTION_SOFTWARE_POSTION_SOFTWAVE_SHIFT (0U)
#define QEOV2_POSTION_SOFTWARE_POSTION_SOFTWAVE_SET(x) (((uint32_t)(x) << QEOV2_POSTION_SOFTWARE_POSTION_SOFTWAVE_SHIFT) & QEOV2_POSTION_SOFTWARE_POSTION_SOFTWAVE_MASK)
#define QEOV2_POSTION_SOFTWARE_POSTION_SOFTWAVE_GET(x) (((uint32_t)(x) & QEOV2_POSTION_SOFTWARE_POSTION_SOFTWAVE_MASK) >> QEOV2_POSTION_SOFTWARE_POSTION_SOFTWAVE_SHIFT)

/* Bitfield definition for register: POSTION_SEL */
/*
 * POSTION_SEL (RW)
 *
 * enable softwave inject postion.
 * 0: disable.
 * 1: enable.
 */
#define QEOV2_POSTION_SEL_POSTION_SEL_MASK (0x1U)
#define QEOV2_POSTION_SEL_POSTION_SEL_SHIFT (0U)
#define QEOV2_POSTION_SEL_POSTION_SEL_SET(x) (((uint32_t)(x) << QEOV2_POSTION_SEL_POSTION_SEL_SHIFT) & QEOV2_POSTION_SEL_POSTION_SEL_MASK)
#define QEOV2_POSTION_SEL_POSTION_SEL_GET(x) (((uint32_t)(x) & QEOV2_POSTION_SEL_POSTION_SEL_MASK) >> QEOV2_POSTION_SEL_POSTION_SEL_SHIFT)

/* Bitfield definition for register: STATUS */
/*
 * PWM_FOURCE (RO)
 *
 * qeo_pwm_force observe
 */
#define QEOV2_STATUS_PWM_FOURCE_MASK (0xFFFF0000UL)
#define QEOV2_STATUS_PWM_FOURCE_SHIFT (16U)
#define QEOV2_STATUS_PWM_FOURCE_GET(x) (((uint32_t)(x) & QEOV2_STATUS_PWM_FOURCE_MASK) >> QEOV2_STATUS_PWM_FOURCE_SHIFT)

/*
 * PWM_SAFETY (RO)
 *
 * pwm_fault status
 */
#define QEOV2_STATUS_PWM_SAFETY_MASK (0x1U)
#define QEOV2_STATUS_PWM_SAFETY_SHIFT (0U)
#define QEOV2_STATUS_PWM_SAFETY_GET(x) (((uint32_t)(x) & QEOV2_STATUS_PWM_SAFETY_MASK) >> QEOV2_STATUS_PWM_SAFETY_SHIFT)

/* Bitfield definition for register: DEBUG0 */
/*
 * VALUE_DAC0 (RO)
 *
 * wave0
 */
#define QEOV2_DEBUG0_VALUE_DAC0_MASK (0xFFFFFFFFUL)
#define QEOV2_DEBUG0_VALUE_DAC0_SHIFT (0U)
#define QEOV2_DEBUG0_VALUE_DAC0_GET(x) (((uint32_t)(x) & QEOV2_DEBUG0_VALUE_DAC0_MASK) >> QEOV2_DEBUG0_VALUE_DAC0_SHIFT)

/* Bitfield definition for register: DEBUG1 */
/*
 * QEO_FINISH (RO)
 *
 * qeo finish observe
 */
#define QEOV2_DEBUG1_QEO_FINISH_MASK (0x10000000UL)
#define QEOV2_DEBUG1_QEO_FINISH_SHIFT (28U)
#define QEOV2_DEBUG1_QEO_FINISH_GET(x) (((uint32_t)(x) & QEOV2_DEBUG1_QEO_FINISH_MASK) >> QEOV2_DEBUG1_QEO_FINISH_SHIFT)

/*
 * PAD_Z (RO)
 *
 * pad_z observe
 */
#define QEOV2_DEBUG1_PAD_Z_MASK (0x1000000UL)
#define QEOV2_DEBUG1_PAD_Z_SHIFT (24U)
#define QEOV2_DEBUG1_PAD_Z_GET(x) (((uint32_t)(x) & QEOV2_DEBUG1_PAD_Z_MASK) >> QEOV2_DEBUG1_PAD_Z_SHIFT)

/*
 * PAD_B (RO)
 *
 * pad_b observe
 */
#define QEOV2_DEBUG1_PAD_B_MASK (0x100000UL)
#define QEOV2_DEBUG1_PAD_B_SHIFT (20U)
#define QEOV2_DEBUG1_PAD_B_GET(x) (((uint32_t)(x) & QEOV2_DEBUG1_PAD_B_MASK) >> QEOV2_DEBUG1_PAD_B_SHIFT)

/*
 * PAD_A (RO)
 *
 * pad_a observe
 */
#define QEOV2_DEBUG1_PAD_A_MASK (0x10000UL)
#define QEOV2_DEBUG1_PAD_A_SHIFT (16U)
#define QEOV2_DEBUG1_PAD_A_GET(x) (((uint32_t)(x) & QEOV2_DEBUG1_PAD_A_MASK) >> QEOV2_DEBUG1_PAD_A_SHIFT)

/* Bitfield definition for register: DEBUG2 */
/*
 * ABZ_OWN_POSTION (RO)
 *
 * abz_own_postion observe
 */
#define QEOV2_DEBUG2_ABZ_OWN_POSTION_MASK (0xFFFFFFFFUL)
#define QEOV2_DEBUG2_ABZ_OWN_POSTION_SHIFT (0U)
#define QEOV2_DEBUG2_ABZ_OWN_POSTION_GET(x) (((uint32_t)(x) & QEOV2_DEBUG2_ABZ_OWN_POSTION_MASK) >> QEOV2_DEBUG2_ABZ_OWN_POSTION_SHIFT)

/* Bitfield definition for register: DEBUG3 */
/*
 * ABZ_OWN_POSTION (RO)
 *
 * abz_own_postion observe
 */
#define QEOV2_DEBUG3_ABZ_OWN_POSTION_MASK (0xFFFFFFFFUL)
#define QEOV2_DEBUG3_ABZ_OWN_POSTION_SHIFT (0U)
#define QEOV2_DEBUG3_ABZ_OWN_POSTION_GET(x) (((uint32_t)(x) & QEOV2_DEBUG3_ABZ_OWN_POSTION_MASK) >> QEOV2_DEBUG3_ABZ_OWN_POSTION_SHIFT)

/* Bitfield definition for register: DEBUG4 */
/*
 * VALUE_DAC1 (RO)
 *
 * wave1
 */
#define QEOV2_DEBUG4_VALUE_DAC1_MASK (0xFFFFFFFFUL)
#define QEOV2_DEBUG4_VALUE_DAC1_SHIFT (0U)
#define QEOV2_DEBUG4_VALUE_DAC1_GET(x) (((uint32_t)(x) & QEOV2_DEBUG4_VALUE_DAC1_MASK) >> QEOV2_DEBUG4_VALUE_DAC1_SHIFT)

/* Bitfield definition for register: DEBUG5 */
/*
 * VALUE_DAC2 (RO)
 *
 * wave2
 */
#define QEOV2_DEBUG5_VALUE_DAC2_MASK (0xFFFFFFFFUL)
#define QEOV2_DEBUG5_VALUE_DAC2_SHIFT (0U)
#define QEOV2_DEBUG5_VALUE_DAC2_GET(x) (((uint32_t)(x) & QEOV2_DEBUG5_VALUE_DAC2_MASK) >> QEOV2_DEBUG5_VALUE_DAC2_SHIFT)



/* PHASE_SHIFT register group index macro definition */
#define QEOV2_WAVE_PHASE_SHIFT_WAVE0 (0UL)
#define QEOV2_WAVE_PHASE_SHIFT_WAVE1 (1UL)
#define QEOV2_WAVE_PHASE_SHIFT_WAVE2 (2UL)

/* AMPLITUDE register group index macro definition */
#define QEOV2_WAVE_AMPLITUDE_WAVE0 (0UL)
#define QEOV2_WAVE_AMPLITUDE_WAVE1 (1UL)
#define QEOV2_WAVE_AMPLITUDE_WAVE2 (2UL)

/* MID_POINT register group index macro definition */
#define QEOV2_WAVE_MID_POINT_WAVE0 (0UL)
#define QEOV2_WAVE_MID_POINT_WAVE1 (1UL)
#define QEOV2_WAVE_MID_POINT_WAVE2 (2UL)

/* LIMIT0 register group index macro definition */
#define QEOV2_LIMIT0_WAVE0 (0UL)
#define QEOV2_LIMIT0_WAVE1 (1UL)
#define QEOV2_LIMIT0_WAVE2 (2UL)

/* LIMIT1 register group index macro definition */
#define QEOV2_LIMIT1_WAVE0 (0UL)
#define QEOV2_LIMIT1_WAVE1 (1UL)
#define QEOV2_LIMIT1_WAVE2 (2UL)

/* DEADZONE_SHIFT register group index macro definition */
#define QEOV2_WAVE_DEADZONE_SHIFT_WAVE0 (0UL)
#define QEOV2_WAVE_DEADZONE_SHIFT_WAVE1 (1UL)
#define QEOV2_WAVE_DEADZONE_SHIFT_WAVE2 (2UL)

/* PHASE_SHIFT register group index macro definition */
#define QEOV2_ABZ_PHASE_SHIFT_A (0UL)
#define QEOV2_ABZ_PHASE_SHIFT_B (1UL)
#define QEOV2_ABZ_PHASE_SHIFT_Z (2UL)

/* PHASE_SHIFT register group index macro definition */
#define QEOV2_PWM_PHASE_SHIFT_A (0UL)
#define QEOV2_PWM_PHASE_SHIFT_B (1UL)
#define QEOV2_PWM_PHASE_SHIFT_C (2UL)
#define QEOV2_PWM_PHASE_SHIFT_D (3UL)

/* PHASE_TABLE register group index macro definition */
#define QEOV2_PWM_PHASE_TABLE_POSEDGE0 (0UL)
#define QEOV2_PWM_PHASE_TABLE_POSEDGE1 (1UL)
#define QEOV2_PWM_PHASE_TABLE_POSEDGE2 (2UL)
#define QEOV2_PWM_PHASE_TABLE_POSEDGE3 (3UL)
#define QEOV2_PWM_PHASE_TABLE_POSEDGE4 (4UL)
#define QEOV2_PWM_PHASE_TABLE_POSEDGE5 (5UL)
#define QEOV2_PWM_PHASE_TABLE_POSEDGE6 (6UL)
#define QEOV2_PWM_PHASE_TABLE_POSEDGE7 (7UL)
#define QEOV2_PWM_PHASE_TABLE_POSEDGE8 (8UL)
#define QEOV2_PWM_PHASE_TABLE_POSEDGE9 (9UL)
#define QEOV2_PWM_PHASE_TABLE_POSEDGE10 (10UL)
#define QEOV2_PWM_PHASE_TABLE_POSEDGE11 (11UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE0 (12UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE1 (13UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE2 (14UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE3 (15UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE4 (16UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE5 (17UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE6 (18UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE7 (19UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE8 (20UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE9 (21UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE10 (22UL)
#define QEOV2_PWM_PHASE_TABLE_NEGEDGE11 (23UL)


#endif /* HPM_QEOV2_H */
