/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_QEO_H
#define HPM_QEO_H

typedef struct {
    struct {
        __RW uint32_t MODE;                    /* 0x0: analog waves mode */
        __RW uint32_t RESOLUTION;              /* 0x4: resolution of wave0/1/2 */
        __RW uint32_t PHASE_SHIFT[3];          /* 0x8 - 0x10: wave0 phase shifter */
        __RW uint32_t VD_VQ_INJECT[3];         /* 0x14 - 0x1C: wave0 vd vq inject value */
        __W  uint32_t VD_VQ_LOAD;              /* 0x20: load wave0/1/2 vd vq value */
        __RW uint32_t AMPLITUDE[3];            /* 0x24 - 0x2C: wave0 amplitude */
        __RW uint32_t MID_POINT[3];            /* 0x30 - 0x38: wave0 output middle point offset */
        struct {
            __RW uint32_t MIN;                 /* 0x3C: wave0 low area limit value */
            __RW uint32_t MAX;                 /* 0x40: wave0 high area limit value */
        } LIMIT[3];
        __RW uint32_t DEADZONE_SHIFT[3];       /* 0x54 - 0x5C: deadzone_shifter_wave0 */
    } WAVE;
    struct {
        __RW uint32_t MODE;                    /* 0x60: wave_a/b/z output mode */
        __RW uint32_t RESOLUTION;              /* 0x64: resolution of wave_a/b/z */
        __RW uint32_t PHASE_SHIFT[3];          /* 0x68 - 0x70: wave_a phase shifter */
        __RW uint32_t LINE_WIDTH;              /* 0x74: Two-phase orthogonality wave 1/4 period */
        __RW uint32_t WDOG_WIDTH;              /* 0x78: wdog width of qeo */
        __W  uint32_t POSTION_SYNC;            /* 0x7C: sync abz owned postion */
    } ABZ;
    struct {
        __RW uint32_t MODE;                    /* 0x80: pwm mode */
        __RW uint32_t RESOLUTION;              /* 0x84: resolution of pwm */
        __RW uint32_t PHASE_SHIFT[4];          /* 0x88 - 0x94: pwm_a phase shifter */
        __RW uint32_t PHASE_TABLE[24];         /* 0x98 - 0xF4: pwm_phase_table 0 */
    } PWM;
    __RW uint32_t POSTION_SOFTWARE;            /* 0xF8: softwave inject postion */
    __RW uint32_t POSTION_SEL;                 /* 0xFC: select softwave inject postion */
    __R  uint32_t STATUS;                      /* 0x100: qeo status */
    __R  uint32_t DEBUG0;                      /* 0x104: qeo debug 0 */
    __R  uint32_t DEBUG1;                      /* 0x108: qeo debug 1 */
    __R  uint32_t DEBUG2;                      /* 0x10C: qeo debug 2 */
    __R  uint32_t DEBUG3;                      /* 0x110: qeo debug 3 */
} QEO_Type;


/* Bitfield definition for register of struct WAVE: MODE */
/*
 * WAVE2_ABOVE_MAX_LIMIT (RW)
 *
 * wave2 above max limit mode.
 * 0: output 0xffff.
 * 1: output 0x0.
 * 2: output as level_max_limit2.level0_max_limit
 */
#define QEO_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_MASK (0xC0000000UL)
#define QEO_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_SHIFT (30U)
#define QEO_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE2_ABOVE_MAX_LIMIT_SHIFT)

/*
 * WAVE2_HIGH_AREA1_LIMIT (RW)
 *
 * wave2 high area1 limit mode.
 * 0: output 0xffff.
 * 1: output as level_max_limit2.level0_max_limit
 */
#define QEO_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_MASK (0x20000000UL)
#define QEO_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_SHIFT (29U)
#define QEO_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE2_HIGH_AREA1_LIMIT_SHIFT)

/*
 * WAVE2_HIGH_AREA0_LIMIT (RW)
 *
 * wave2 high area0 limit mode.
 * 0: output 0xffff.
 * 1: output as level_max_limit2.level0_max_limit
 */
#define QEO_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_MASK (0x10000000UL)
#define QEO_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_SHIFT (28U)
#define QEO_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE2_HIGH_AREA0_LIMIT_SHIFT)

/*
 * WAVE2_LOW_AREA1_LIMIT (RW)
 *
 * wave2 low area1 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit2.level1_min_limit
 */
#define QEO_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_MASK (0x8000000UL)
#define QEO_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_SHIFT (27U)
#define QEO_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE2_LOW_AREA1_LIMIT_SHIFT)

/*
 * WAVE2_LOW_AREA0_LIMIT (RW)
 *
 * wave2 low area0 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit2.level1_min_limit
 */
#define QEO_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_MASK (0x4000000UL)
#define QEO_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_SHIFT (26U)
#define QEO_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE2_LOW_AREA0_LIMIT_SHIFT)

/*
 * WAVE2_BELOW_MIN_LIMIT (RW)
 *
 * wave2 below min limit mode.
 * 0: output 0.
 * 1: output 0xffff.
 * 2: output as level_min_limit2.level1_min_limit
 */
#define QEO_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_MASK (0x3000000UL)
#define QEO_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_SHIFT (24U)
#define QEO_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE2_BELOW_MIN_LIMIT_SHIFT)

/*
 * WAVE1_ABOVE_MAX_LIMIT (RW)
 *
 * wave1 above max limit mode.
 * 0: output 0xffff.
 * 1: output 0x0.
 * 2: output as level_max_limit1.level0_max_limit
 */
#define QEO_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_MASK (0xC00000UL)
#define QEO_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_SHIFT (22U)
#define QEO_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE1_ABOVE_MAX_LIMIT_SHIFT)

/*
 * WAVE1_HIGH_AREA1_LIMIT (RW)
 *
 * wave1 high area1 limit mode.
 * 0: output 0xffff.
 * 1: output as level_max_limit1.level0_max_limit
 */
#define QEO_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_MASK (0x200000UL)
#define QEO_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_SHIFT (21U)
#define QEO_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE1_HIGH_AREA1_LIMIT_SHIFT)

/*
 * WAVE1_HIGH_AREA0_LIMIT (RW)
 *
 * wave1 high area0 limit mode.
 * 0: output 0xffff.
 * 1: output as level_max_limit1.level0_max_limit
 */
#define QEO_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_MASK (0x100000UL)
#define QEO_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_SHIFT (20U)
#define QEO_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE1_HIGH_AREA0_LIMIT_SHIFT)

/*
 * WAVE1_LOW_AREA1_LIMIT (RW)
 *
 * wave1 low area1 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit1.level1_min_limit
 */
#define QEO_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_MASK (0x80000UL)
#define QEO_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_SHIFT (19U)
#define QEO_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE1_LOW_AREA1_LIMIT_SHIFT)

/*
 * WAVE1_LOW_AREA0_LIMIT (RW)
 *
 * wave1 low area0 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit1.level1_min_limit
 */
#define QEO_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_MASK (0x40000UL)
#define QEO_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_SHIFT (18U)
#define QEO_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE1_LOW_AREA0_LIMIT_SHIFT)

/*
 * WAVE1_BELOW_MIN_LIMIT (RW)
 *
 * wave1 below min limit mode.
 * 0: output 0.
 * 1: output 0xffff.
 * 2: output as level_min_limit1.level1_min_limit
 */
#define QEO_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_MASK (0x30000UL)
#define QEO_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_SHIFT (16U)
#define QEO_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE1_BELOW_MIN_LIMIT_SHIFT)

/*
 * WAVE0_ABOVE_MAX_LIMIT (RW)
 *
 * wave0 above max limit mode.
 * 0: output 0xffff.
 * 1: output 0x0.
 * 2: output as level_max_limit0.level0_max_limit
 */
#define QEO_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_MASK (0xC000U)
#define QEO_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_SHIFT (14U)
#define QEO_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE0_ABOVE_MAX_LIMIT_SHIFT)

/*
 * WAVE0_HIGH_AREA1_LIMIT (RW)
 *
 * wave0 high area1 limit mode.
 * 0: output 0xffff.
 * 1: output as level_max_limit0.level0_max_limit
 */
#define QEO_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_MASK (0x2000U)
#define QEO_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_SHIFT (13U)
#define QEO_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE0_HIGH_AREA1_LIMIT_SHIFT)

/*
 * WAVE0_HIGH_AREA0_LIMIT (RW)
 *
 * wave0 high area0 limit mode.
 * 0: output 0xffff.
 * 1: output as level_max_limit0.level0_max_limit
 */
#define QEO_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_MASK (0x1000U)
#define QEO_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_SHIFT (12U)
#define QEO_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE0_HIGH_AREA0_LIMIT_SHIFT)

/*
 * WAVE0_LOW_AREA1_LIMIT (RW)
 *
 * wave0 low area1 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit0.level1_min_limit
 */
#define QEO_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_MASK (0x800U)
#define QEO_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_SHIFT (11U)
#define QEO_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE0_LOW_AREA1_LIMIT_SHIFT)

/*
 * WAVE0_LOW_AREA0_LIMIT (RW)
 *
 * wave0 low area0 limit mode.
 * 0: output 0.
 * 1: output as level_min_limit0.level1_min_limit
 */
#define QEO_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_MASK (0x400U)
#define QEO_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_SHIFT (10U)
#define QEO_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE0_LOW_AREA0_LIMIT_SHIFT)

/*
 * WAVE0_BELOW_MIN_LIMIT (RW)
 *
 * wave0 below min limit mode.
 * 0: output 0.
 * 1: output 0xffff.
 * 2: output as level_min_limit0.level1_min_limit
 */
#define QEO_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_MASK (0x300U)
#define QEO_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_SHIFT (8U)
#define QEO_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_SHIFT) & QEO_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_MASK)
#define QEO_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_MASK) >> QEO_WAVE_MODE_WAVE0_BELOW_MIN_LIMIT_SHIFT)

/*
 * SADDLE_TYPE (RW)
 *
 * saddle type seclect;
 * 0:standard saddle.
 * 1: triple-cos saddle.
 */
#define QEO_WAVE_MODE_SADDLE_TYPE_MASK (0x80U)
#define QEO_WAVE_MODE_SADDLE_TYPE_SHIFT (7U)
#define QEO_WAVE_MODE_SADDLE_TYPE_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_SADDLE_TYPE_SHIFT) & QEO_WAVE_MODE_SADDLE_TYPE_MASK)
#define QEO_WAVE_MODE_SADDLE_TYPE_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_SADDLE_TYPE_MASK) >> QEO_WAVE_MODE_SADDLE_TYPE_SHIFT)

/*
 * EN_WAVE2_VD_VQ_INJECT (RW)
 *
 * wave2 VdVq inject enable.
 * 0: disable VdVq inject.
 * 1: enable VdVq inject.
 */
#define QEO_WAVE_MODE_EN_WAVE2_VD_VQ_INJECT_MASK (0x40U)
#define QEO_WAVE_MODE_EN_WAVE2_VD_VQ_INJECT_SHIFT (6U)
#define QEO_WAVE_MODE_EN_WAVE2_VD_VQ_INJECT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_EN_WAVE2_VD_VQ_INJECT_SHIFT) & QEO_WAVE_MODE_EN_WAVE2_VD_VQ_INJECT_MASK)
#define QEO_WAVE_MODE_EN_WAVE2_VD_VQ_INJECT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_EN_WAVE2_VD_VQ_INJECT_MASK) >> QEO_WAVE_MODE_EN_WAVE2_VD_VQ_INJECT_SHIFT)

/*
 * EN_WAVE1_VD_VQ_INJECT (RW)
 *
 * wave1 VdVq inject enable.
 * 0: disable VdVq inject.
 * 1: enable VdVq inject.
 */
#define QEO_WAVE_MODE_EN_WAVE1_VD_VQ_INJECT_MASK (0x20U)
#define QEO_WAVE_MODE_EN_WAVE1_VD_VQ_INJECT_SHIFT (5U)
#define QEO_WAVE_MODE_EN_WAVE1_VD_VQ_INJECT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_EN_WAVE1_VD_VQ_INJECT_SHIFT) & QEO_WAVE_MODE_EN_WAVE1_VD_VQ_INJECT_MASK)
#define QEO_WAVE_MODE_EN_WAVE1_VD_VQ_INJECT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_EN_WAVE1_VD_VQ_INJECT_MASK) >> QEO_WAVE_MODE_EN_WAVE1_VD_VQ_INJECT_SHIFT)

/*
 * EN_WAVE0_VD_VQ_INJECT (RW)
 *
 * wave0 VdVq inject enable.
 * 0: disable VdVq inject.
 * 1: enable VdVq inject.
 */
#define QEO_WAVE_MODE_EN_WAVE0_VD_VQ_INJECT_MASK (0x10U)
#define QEO_WAVE_MODE_EN_WAVE0_VD_VQ_INJECT_SHIFT (4U)
#define QEO_WAVE_MODE_EN_WAVE0_VD_VQ_INJECT_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_EN_WAVE0_VD_VQ_INJECT_SHIFT) & QEO_WAVE_MODE_EN_WAVE0_VD_VQ_INJECT_MASK)
#define QEO_WAVE_MODE_EN_WAVE0_VD_VQ_INJECT_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_EN_WAVE0_VD_VQ_INJECT_MASK) >> QEO_WAVE_MODE_EN_WAVE0_VD_VQ_INJECT_SHIFT)

/*
 * WAVES_OUTPUT_TYPE (RW)
 *
 * wave0/1/2 output mode.
 * 0: cosine wave.
 * 1: saddle wave.
 * 2. abs cosine wave.
 * 3. saw wave
 */
#define QEO_WAVE_MODE_WAVES_OUTPUT_TYPE_MASK (0x3U)
#define QEO_WAVE_MODE_WAVES_OUTPUT_TYPE_SHIFT (0U)
#define QEO_WAVE_MODE_WAVES_OUTPUT_TYPE_SET(x) (((uint32_t)(x) << QEO_WAVE_MODE_WAVES_OUTPUT_TYPE_SHIFT) & QEO_WAVE_MODE_WAVES_OUTPUT_TYPE_MASK)
#define QEO_WAVE_MODE_WAVES_OUTPUT_TYPE_GET(x) (((uint32_t)(x) & QEO_WAVE_MODE_WAVES_OUTPUT_TYPE_MASK) >> QEO_WAVE_MODE_WAVES_OUTPUT_TYPE_SHIFT)

/* Bitfield definition for register of struct WAVE: RESOLUTION */
/*
 * LINES (RW)
 *
 * wave0/1/2 resolution
 */
#define QEO_WAVE_RESOLUTION_LINES_MASK (0xFFFFFFFFUL)
#define QEO_WAVE_RESOLUTION_LINES_SHIFT (0U)
#define QEO_WAVE_RESOLUTION_LINES_SET(x) (((uint32_t)(x) << QEO_WAVE_RESOLUTION_LINES_SHIFT) & QEO_WAVE_RESOLUTION_LINES_MASK)
#define QEO_WAVE_RESOLUTION_LINES_GET(x) (((uint32_t)(x) & QEO_WAVE_RESOLUTION_LINES_MASK) >> QEO_WAVE_RESOLUTION_LINES_SHIFT)

/* Bitfield definition for register of struct WAVE: WAVE0 */
/*
 * VAL (RW)
 *
 * wave0 phase shifter value, default is 0x0. write other value will shift phase early as (cfg_value/2^16) period
 */
#define QEO_WAVE_PHASE_SHIFT_VAL_MASK (0xFFFFU)
#define QEO_WAVE_PHASE_SHIFT_VAL_SHIFT (0U)
#define QEO_WAVE_PHASE_SHIFT_VAL_SET(x) (((uint32_t)(x) << QEO_WAVE_PHASE_SHIFT_VAL_SHIFT) & QEO_WAVE_PHASE_SHIFT_VAL_MASK)
#define QEO_WAVE_PHASE_SHIFT_VAL_GET(x) (((uint32_t)(x) & QEO_WAVE_PHASE_SHIFT_VAL_MASK) >> QEO_WAVE_PHASE_SHIFT_VAL_SHIFT)

/* Bitfield definition for register of struct WAVE: WAVE0 */
/*
 * VQ_VAL (RW)
 *
 * Vq inject value
 */
#define QEO_WAVE_VD_VQ_INJECT_VQ_VAL_MASK (0xFFFF0000UL)
#define QEO_WAVE_VD_VQ_INJECT_VQ_VAL_SHIFT (16U)
#define QEO_WAVE_VD_VQ_INJECT_VQ_VAL_SET(x) (((uint32_t)(x) << QEO_WAVE_VD_VQ_INJECT_VQ_VAL_SHIFT) & QEO_WAVE_VD_VQ_INJECT_VQ_VAL_MASK)
#define QEO_WAVE_VD_VQ_INJECT_VQ_VAL_GET(x) (((uint32_t)(x) & QEO_WAVE_VD_VQ_INJECT_VQ_VAL_MASK) >> QEO_WAVE_VD_VQ_INJECT_VQ_VAL_SHIFT)

/*
 * VD_VAL (RW)
 *
 * Vd inject value
 */
#define QEO_WAVE_VD_VQ_INJECT_VD_VAL_MASK (0xFFFFU)
#define QEO_WAVE_VD_VQ_INJECT_VD_VAL_SHIFT (0U)
#define QEO_WAVE_VD_VQ_INJECT_VD_VAL_SET(x) (((uint32_t)(x) << QEO_WAVE_VD_VQ_INJECT_VD_VAL_SHIFT) & QEO_WAVE_VD_VQ_INJECT_VD_VAL_MASK)
#define QEO_WAVE_VD_VQ_INJECT_VD_VAL_GET(x) (((uint32_t)(x) & QEO_WAVE_VD_VQ_INJECT_VD_VAL_MASK) >> QEO_WAVE_VD_VQ_INJECT_VD_VAL_SHIFT)

/* Bitfield definition for register of struct WAVE: VD_VQ_LOAD */
/*
 * LOAD (WO)
 *
 * load wave0/1/2 vd vq value.  always read 0
 * 0: vd vq keep previous value.
 * 1: load wave0/1/2 vd vq value at sametime.
 */
#define QEO_WAVE_VD_VQ_LOAD_LOAD_MASK (0x1U)
#define QEO_WAVE_VD_VQ_LOAD_LOAD_SHIFT (0U)
#define QEO_WAVE_VD_VQ_LOAD_LOAD_SET(x) (((uint32_t)(x) << QEO_WAVE_VD_VQ_LOAD_LOAD_SHIFT) & QEO_WAVE_VD_VQ_LOAD_LOAD_MASK)
#define QEO_WAVE_VD_VQ_LOAD_LOAD_GET(x) (((uint32_t)(x) & QEO_WAVE_VD_VQ_LOAD_LOAD_MASK) >> QEO_WAVE_VD_VQ_LOAD_LOAD_SHIFT)

/* Bitfield definition for register of struct WAVE: WAVE0 */
/*
 * EN_SCAL (RW)
 *
 * enable wave amplitude scaling. 0: disable; 1: enable
 */
#define QEO_WAVE_AMPLITUDE_EN_SCAL_MASK (0x10000UL)
#define QEO_WAVE_AMPLITUDE_EN_SCAL_SHIFT (16U)
#define QEO_WAVE_AMPLITUDE_EN_SCAL_SET(x) (((uint32_t)(x) << QEO_WAVE_AMPLITUDE_EN_SCAL_SHIFT) & QEO_WAVE_AMPLITUDE_EN_SCAL_MASK)
#define QEO_WAVE_AMPLITUDE_EN_SCAL_GET(x) (((uint32_t)(x) & QEO_WAVE_AMPLITUDE_EN_SCAL_MASK) >> QEO_WAVE_AMPLITUDE_EN_SCAL_SHIFT)

/*
 * AMP_VAL (RW)
 *
 * amplitude scaling value. bit15-12 are integer part value. bit11-0 are fraction value.
 */
#define QEO_WAVE_AMPLITUDE_AMP_VAL_MASK (0xFFFFU)
#define QEO_WAVE_AMPLITUDE_AMP_VAL_SHIFT (0U)
#define QEO_WAVE_AMPLITUDE_AMP_VAL_SET(x) (((uint32_t)(x) << QEO_WAVE_AMPLITUDE_AMP_VAL_SHIFT) & QEO_WAVE_AMPLITUDE_AMP_VAL_MASK)
#define QEO_WAVE_AMPLITUDE_AMP_VAL_GET(x) (((uint32_t)(x) & QEO_WAVE_AMPLITUDE_AMP_VAL_MASK) >> QEO_WAVE_AMPLITUDE_AMP_VAL_SHIFT)

/* Bitfield definition for register of struct WAVE: WAVE0 */
/*
 * VAL (RW)
 *
 * wave0 output middle point, use this value as 32 bit signed value. bit 31 is signed bit. bit30-27 is integer part value. bit26-0 is fraction value.
 */
#define QEO_WAVE_MID_POINT_VAL_MASK (0xFFFFFFFFUL)
#define QEO_WAVE_MID_POINT_VAL_SHIFT (0U)
#define QEO_WAVE_MID_POINT_VAL_SET(x) (((uint32_t)(x) << QEO_WAVE_MID_POINT_VAL_SHIFT) & QEO_WAVE_MID_POINT_VAL_MASK)
#define QEO_WAVE_MID_POINT_VAL_GET(x) (((uint32_t)(x) & QEO_WAVE_MID_POINT_VAL_MASK) >> QEO_WAVE_MID_POINT_VAL_SHIFT)

/* Bitfield definition for register of struct WAVE: MIN */
/*
 * LIMIT1 (RW)
 *
 * low area limit level1
 */
#define QEO_WAVE_LIMIT_MIN_LIMIT1_MASK (0xFFFF0000UL)
#define QEO_WAVE_LIMIT_MIN_LIMIT1_SHIFT (16U)
#define QEO_WAVE_LIMIT_MIN_LIMIT1_SET(x) (((uint32_t)(x) << QEO_WAVE_LIMIT_MIN_LIMIT1_SHIFT) & QEO_WAVE_LIMIT_MIN_LIMIT1_MASK)
#define QEO_WAVE_LIMIT_MIN_LIMIT1_GET(x) (((uint32_t)(x) & QEO_WAVE_LIMIT_MIN_LIMIT1_MASK) >> QEO_WAVE_LIMIT_MIN_LIMIT1_SHIFT)

/*
 * LIMIT0 (RW)
 *
 * low area limit level0
 */
#define QEO_WAVE_LIMIT_MIN_LIMIT0_MASK (0xFFFFU)
#define QEO_WAVE_LIMIT_MIN_LIMIT0_SHIFT (0U)
#define QEO_WAVE_LIMIT_MIN_LIMIT0_SET(x) (((uint32_t)(x) << QEO_WAVE_LIMIT_MIN_LIMIT0_SHIFT) & QEO_WAVE_LIMIT_MIN_LIMIT0_MASK)
#define QEO_WAVE_LIMIT_MIN_LIMIT0_GET(x) (((uint32_t)(x) & QEO_WAVE_LIMIT_MIN_LIMIT0_MASK) >> QEO_WAVE_LIMIT_MIN_LIMIT0_SHIFT)

/* Bitfield definition for register of struct WAVE: MAX */
/*
 * LIMIT1 (RW)
 *
 * high area limit level1
 */
#define QEO_WAVE_LIMIT_MAX_LIMIT1_MASK (0xFFFF0000UL)
#define QEO_WAVE_LIMIT_MAX_LIMIT1_SHIFT (16U)
#define QEO_WAVE_LIMIT_MAX_LIMIT1_SET(x) (((uint32_t)(x) << QEO_WAVE_LIMIT_MAX_LIMIT1_SHIFT) & QEO_WAVE_LIMIT_MAX_LIMIT1_MASK)
#define QEO_WAVE_LIMIT_MAX_LIMIT1_GET(x) (((uint32_t)(x) & QEO_WAVE_LIMIT_MAX_LIMIT1_MASK) >> QEO_WAVE_LIMIT_MAX_LIMIT1_SHIFT)

/*
 * LIMIT0 (RW)
 *
 * high area limit level0
 */
#define QEO_WAVE_LIMIT_MAX_LIMIT0_MASK (0xFFFFU)
#define QEO_WAVE_LIMIT_MAX_LIMIT0_SHIFT (0U)
#define QEO_WAVE_LIMIT_MAX_LIMIT0_SET(x) (((uint32_t)(x) << QEO_WAVE_LIMIT_MAX_LIMIT0_SHIFT) & QEO_WAVE_LIMIT_MAX_LIMIT0_MASK)
#define QEO_WAVE_LIMIT_MAX_LIMIT0_GET(x) (((uint32_t)(x) & QEO_WAVE_LIMIT_MAX_LIMIT0_MASK) >> QEO_WAVE_LIMIT_MAX_LIMIT0_SHIFT)

/* Bitfield definition for register of struct WAVE: WAVE0 */
/*
 * VAL (RW)
 *
 * wave0 deadzone shifter value
 */
#define QEO_WAVE_DEADZONE_SHIFT_VAL_MASK (0xFFFFU)
#define QEO_WAVE_DEADZONE_SHIFT_VAL_SHIFT (0U)
#define QEO_WAVE_DEADZONE_SHIFT_VAL_SET(x) (((uint32_t)(x) << QEO_WAVE_DEADZONE_SHIFT_VAL_SHIFT) & QEO_WAVE_DEADZONE_SHIFT_VAL_MASK)
#define QEO_WAVE_DEADZONE_SHIFT_VAL_GET(x) (((uint32_t)(x) & QEO_WAVE_DEADZONE_SHIFT_VAL_MASK) >> QEO_WAVE_DEADZONE_SHIFT_VAL_SHIFT)

/* Bitfield definition for register of struct ABZ: MODE */
/*
 * REVERSE_EDGE_TYPE (RW)
 *
 * pulse reverse wave，reverse edge point:
 * 0: between pulse's posedge and negedge, min period dedicated by the num line_width
 * 1: edge change point flow pulse's negedge.
 */
#define QEO_ABZ_MODE_REVERSE_EDGE_TYPE_MASK (0x10000000UL)
#define QEO_ABZ_MODE_REVERSE_EDGE_TYPE_SHIFT (28U)
#define QEO_ABZ_MODE_REVERSE_EDGE_TYPE_SET(x) (((uint32_t)(x) << QEO_ABZ_MODE_REVERSE_EDGE_TYPE_SHIFT) & QEO_ABZ_MODE_REVERSE_EDGE_TYPE_MASK)
#define QEO_ABZ_MODE_REVERSE_EDGE_TYPE_GET(x) (((uint32_t)(x) & QEO_ABZ_MODE_REVERSE_EDGE_TYPE_MASK) >> QEO_ABZ_MODE_REVERSE_EDGE_TYPE_SHIFT)

/*
 * EN_WDOG (RW)
 *
 * enable abz wdog:
 * 0: disable abz wdog.
 * 1: enable abz wdog.
 */
#define QEO_ABZ_MODE_EN_WDOG_MASK (0x1000000UL)
#define QEO_ABZ_MODE_EN_WDOG_SHIFT (24U)
#define QEO_ABZ_MODE_EN_WDOG_SET(x) (((uint32_t)(x) << QEO_ABZ_MODE_EN_WDOG_SHIFT) & QEO_ABZ_MODE_EN_WDOG_MASK)
#define QEO_ABZ_MODE_EN_WDOG_GET(x) (((uint32_t)(x) & QEO_ABZ_MODE_EN_WDOG_MASK) >> QEO_ABZ_MODE_EN_WDOG_SHIFT)

/*
 * Z_POLARITY (RW)
 *
 * wave_z polarity.
 * 0: normal output.
 * 1: invert normal output
 */
#define QEO_ABZ_MODE_Z_POLARITY_MASK (0x100000UL)
#define QEO_ABZ_MODE_Z_POLARITY_SHIFT (20U)
#define QEO_ABZ_MODE_Z_POLARITY_SET(x) (((uint32_t)(x) << QEO_ABZ_MODE_Z_POLARITY_SHIFT) & QEO_ABZ_MODE_Z_POLARITY_MASK)
#define QEO_ABZ_MODE_Z_POLARITY_GET(x) (((uint32_t)(x) & QEO_ABZ_MODE_Z_POLARITY_MASK) >> QEO_ABZ_MODE_Z_POLARITY_SHIFT)

/*
 * B_POLARITY (RW)
 *
 * wave_b polarity.
 * 0: normal output.
 * 1: invert normal output
 */
#define QEO_ABZ_MODE_B_POLARITY_MASK (0x10000UL)
#define QEO_ABZ_MODE_B_POLARITY_SHIFT (16U)
#define QEO_ABZ_MODE_B_POLARITY_SET(x) (((uint32_t)(x) << QEO_ABZ_MODE_B_POLARITY_SHIFT) & QEO_ABZ_MODE_B_POLARITY_MASK)
#define QEO_ABZ_MODE_B_POLARITY_GET(x) (((uint32_t)(x) & QEO_ABZ_MODE_B_POLARITY_MASK) >> QEO_ABZ_MODE_B_POLARITY_SHIFT)

/*
 * A_POLARITY (RW)
 *
 * wave_a polarity.
 * 0: normal output.
 * 1: invert normal output
 */
#define QEO_ABZ_MODE_A_POLARITY_MASK (0x1000U)
#define QEO_ABZ_MODE_A_POLARITY_SHIFT (12U)
#define QEO_ABZ_MODE_A_POLARITY_SET(x) (((uint32_t)(x) << QEO_ABZ_MODE_A_POLARITY_SHIFT) & QEO_ABZ_MODE_A_POLARITY_MASK)
#define QEO_ABZ_MODE_A_POLARITY_GET(x) (((uint32_t)(x) & QEO_ABZ_MODE_A_POLARITY_MASK) >> QEO_ABZ_MODE_A_POLARITY_SHIFT)

/*
 * Z_TYPE (RW)
 *
 * wave_z type:
 * 0: zero pulse and output high at both wave_a and wave_b are high. mantain about 25% period.
 * 1: zero pulse output high about 75% period. start from 0 to 75% period.
 * 2: zero pulse output high about 100% period.
 * 3: wave_z output as tree-phase wave same as wave_a/wave_b
 */
#define QEO_ABZ_MODE_Z_TYPE_MASK (0x300U)
#define QEO_ABZ_MODE_Z_TYPE_SHIFT (8U)
#define QEO_ABZ_MODE_Z_TYPE_SET(x) (((uint32_t)(x) << QEO_ABZ_MODE_Z_TYPE_SHIFT) & QEO_ABZ_MODE_Z_TYPE_MASK)
#define QEO_ABZ_MODE_Z_TYPE_GET(x) (((uint32_t)(x) & QEO_ABZ_MODE_Z_TYPE_MASK) >> QEO_ABZ_MODE_Z_TYPE_SHIFT)

/*
 * B_TYPE (RW)
 *
 * wave_b type:
 * 0: Two-phase orthogonality wave_b.
 * 1: reverse wave of pulse/reverse type.
 * 2: down wave of up/down type.
 * 3: Three-phase orthogonality wave_b.
 */
#define QEO_ABZ_MODE_B_TYPE_MASK (0x30U)
#define QEO_ABZ_MODE_B_TYPE_SHIFT (4U)
#define QEO_ABZ_MODE_B_TYPE_SET(x) (((uint32_t)(x) << QEO_ABZ_MODE_B_TYPE_SHIFT) & QEO_ABZ_MODE_B_TYPE_MASK)
#define QEO_ABZ_MODE_B_TYPE_GET(x) (((uint32_t)(x) & QEO_ABZ_MODE_B_TYPE_MASK) >> QEO_ABZ_MODE_B_TYPE_SHIFT)

/*
 * A_TYPE (RW)
 *
 * wave_a type:
 * 0: Two-phase orthogonality wave_a.
 * 1: pulse wave of pulse/reverse type.
 * 2: up wave of up/down type.
 * 3: Three-phase orthogonality wave_a.
 */
#define QEO_ABZ_MODE_A_TYPE_MASK (0x3U)
#define QEO_ABZ_MODE_A_TYPE_SHIFT (0U)
#define QEO_ABZ_MODE_A_TYPE_SET(x) (((uint32_t)(x) << QEO_ABZ_MODE_A_TYPE_SHIFT) & QEO_ABZ_MODE_A_TYPE_MASK)
#define QEO_ABZ_MODE_A_TYPE_GET(x) (((uint32_t)(x) & QEO_ABZ_MODE_A_TYPE_MASK) >> QEO_ABZ_MODE_A_TYPE_SHIFT)

/* Bitfield definition for register of struct ABZ: RESOLUTION */
/*
 * LINES (RW)
 *
 * wave_a/b/z resolution
 */
#define QEO_ABZ_RESOLUTION_LINES_MASK (0xFFFFFFFFUL)
#define QEO_ABZ_RESOLUTION_LINES_SHIFT (0U)
#define QEO_ABZ_RESOLUTION_LINES_SET(x) (((uint32_t)(x) << QEO_ABZ_RESOLUTION_LINES_SHIFT) & QEO_ABZ_RESOLUTION_LINES_MASK)
#define QEO_ABZ_RESOLUTION_LINES_GET(x) (((uint32_t)(x) & QEO_ABZ_RESOLUTION_LINES_MASK) >> QEO_ABZ_RESOLUTION_LINES_SHIFT)

/* Bitfield definition for register of struct ABZ: A */
/*
 * VAL (RW)
 *
 * wave_a phase shifter value, default is 0x0. write other value will shift phase early as (cfg_value/2^16) period.
 */
#define QEO_ABZ_PHASE_SHIFT_VAL_MASK (0xFFFFU)
#define QEO_ABZ_PHASE_SHIFT_VAL_SHIFT (0U)
#define QEO_ABZ_PHASE_SHIFT_VAL_SET(x) (((uint32_t)(x) << QEO_ABZ_PHASE_SHIFT_VAL_SHIFT) & QEO_ABZ_PHASE_SHIFT_VAL_MASK)
#define QEO_ABZ_PHASE_SHIFT_VAL_GET(x) (((uint32_t)(x) & QEO_ABZ_PHASE_SHIFT_VAL_MASK) >> QEO_ABZ_PHASE_SHIFT_VAL_SHIFT)

/* Bitfield definition for register of struct ABZ: LINE_WIDTH */
/*
 * LINE (RW)
 *
 * the num of system clk by 1/4 period when using as Two-phase orthogonality.
 */
#define QEO_ABZ_LINE_WIDTH_LINE_MASK (0xFFFFFFFFUL)
#define QEO_ABZ_LINE_WIDTH_LINE_SHIFT (0U)
#define QEO_ABZ_LINE_WIDTH_LINE_SET(x) (((uint32_t)(x) << QEO_ABZ_LINE_WIDTH_LINE_SHIFT) & QEO_ABZ_LINE_WIDTH_LINE_MASK)
#define QEO_ABZ_LINE_WIDTH_LINE_GET(x) (((uint32_t)(x) & QEO_ABZ_LINE_WIDTH_LINE_MASK) >> QEO_ABZ_LINE_WIDTH_LINE_SHIFT)

/* Bitfield definition for register of struct ABZ: WDOG_WIDTH */
/*
 * WIDTH (RW)
 *
 * wave will step 1/4 line to reminder user QEO still in controlled if QEO has no any toggle after the num of wdog_width sys clk.
 */
#define QEO_ABZ_WDOG_WIDTH_WIDTH_MASK (0xFFFFFFFFUL)
#define QEO_ABZ_WDOG_WIDTH_WIDTH_SHIFT (0U)
#define QEO_ABZ_WDOG_WIDTH_WIDTH_SET(x) (((uint32_t)(x) << QEO_ABZ_WDOG_WIDTH_WIDTH_SHIFT) & QEO_ABZ_WDOG_WIDTH_WIDTH_MASK)
#define QEO_ABZ_WDOG_WIDTH_WIDTH_GET(x) (((uint32_t)(x) & QEO_ABZ_WDOG_WIDTH_WIDTH_MASK) >> QEO_ABZ_WDOG_WIDTH_WIDTH_SHIFT)

/* Bitfield definition for register of struct ABZ: POSTION_SYNC */
/*
 * POSTION (WO)
 *
 * load next valid postion into  abz owned postion.  always read 0
 * 0: sync abz owned postion with next valid postion.
 * 1: not sync.
 */
#define QEO_ABZ_POSTION_SYNC_POSTION_MASK (0x1U)
#define QEO_ABZ_POSTION_SYNC_POSTION_SHIFT (0U)
#define QEO_ABZ_POSTION_SYNC_POSTION_SET(x) (((uint32_t)(x) << QEO_ABZ_POSTION_SYNC_POSTION_SHIFT) & QEO_ABZ_POSTION_SYNC_POSTION_MASK)
#define QEO_ABZ_POSTION_SYNC_POSTION_GET(x) (((uint32_t)(x) & QEO_ABZ_POSTION_SYNC_POSTION_MASK) >> QEO_ABZ_POSTION_SYNC_POSTION_SHIFT)

/* Bitfield definition for register of struct PWM: MODE */
/*
 * PWM7_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEO_PWM_MODE_PWM7_SAFETY_MASK (0xC0000000UL)
#define QEO_PWM_MODE_PWM7_SAFETY_SHIFT (30U)
#define QEO_PWM_MODE_PWM7_SAFETY_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_PWM7_SAFETY_SHIFT) & QEO_PWM_MODE_PWM7_SAFETY_MASK)
#define QEO_PWM_MODE_PWM7_SAFETY_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_PWM7_SAFETY_MASK) >> QEO_PWM_MODE_PWM7_SAFETY_SHIFT)

/*
 * PWM6_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEO_PWM_MODE_PWM6_SAFETY_MASK (0x30000000UL)
#define QEO_PWM_MODE_PWM6_SAFETY_SHIFT (28U)
#define QEO_PWM_MODE_PWM6_SAFETY_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_PWM6_SAFETY_SHIFT) & QEO_PWM_MODE_PWM6_SAFETY_MASK)
#define QEO_PWM_MODE_PWM6_SAFETY_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_PWM6_SAFETY_MASK) >> QEO_PWM_MODE_PWM6_SAFETY_SHIFT)

/*
 * PWM5_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEO_PWM_MODE_PWM5_SAFETY_MASK (0xC000000UL)
#define QEO_PWM_MODE_PWM5_SAFETY_SHIFT (26U)
#define QEO_PWM_MODE_PWM5_SAFETY_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_PWM5_SAFETY_SHIFT) & QEO_PWM_MODE_PWM5_SAFETY_MASK)
#define QEO_PWM_MODE_PWM5_SAFETY_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_PWM5_SAFETY_MASK) >> QEO_PWM_MODE_PWM5_SAFETY_SHIFT)

/*
 * PWM4_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEO_PWM_MODE_PWM4_SAFETY_MASK (0x3000000UL)
#define QEO_PWM_MODE_PWM4_SAFETY_SHIFT (24U)
#define QEO_PWM_MODE_PWM4_SAFETY_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_PWM4_SAFETY_SHIFT) & QEO_PWM_MODE_PWM4_SAFETY_MASK)
#define QEO_PWM_MODE_PWM4_SAFETY_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_PWM4_SAFETY_MASK) >> QEO_PWM_MODE_PWM4_SAFETY_SHIFT)

/*
 * PWM3_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEO_PWM_MODE_PWM3_SAFETY_MASK (0xC00000UL)
#define QEO_PWM_MODE_PWM3_SAFETY_SHIFT (22U)
#define QEO_PWM_MODE_PWM3_SAFETY_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_PWM3_SAFETY_SHIFT) & QEO_PWM_MODE_PWM3_SAFETY_MASK)
#define QEO_PWM_MODE_PWM3_SAFETY_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_PWM3_SAFETY_MASK) >> QEO_PWM_MODE_PWM3_SAFETY_SHIFT)

/*
 * PWM2_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEO_PWM_MODE_PWM2_SAFETY_MASK (0x300000UL)
#define QEO_PWM_MODE_PWM2_SAFETY_SHIFT (20U)
#define QEO_PWM_MODE_PWM2_SAFETY_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_PWM2_SAFETY_SHIFT) & QEO_PWM_MODE_PWM2_SAFETY_MASK)
#define QEO_PWM_MODE_PWM2_SAFETY_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_PWM2_SAFETY_MASK) >> QEO_PWM_MODE_PWM2_SAFETY_SHIFT)

/*
 * PWM1_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEO_PWM_MODE_PWM1_SAFETY_MASK (0xC0000UL)
#define QEO_PWM_MODE_PWM1_SAFETY_SHIFT (18U)
#define QEO_PWM_MODE_PWM1_SAFETY_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_PWM1_SAFETY_SHIFT) & QEO_PWM_MODE_PWM1_SAFETY_MASK)
#define QEO_PWM_MODE_PWM1_SAFETY_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_PWM1_SAFETY_MASK) >> QEO_PWM_MODE_PWM1_SAFETY_SHIFT)

/*
 * PWM0_SAFETY (RW)
 *
 * PWM safety mode phase table
 */
#define QEO_PWM_MODE_PWM0_SAFETY_MASK (0x30000UL)
#define QEO_PWM_MODE_PWM0_SAFETY_SHIFT (16U)
#define QEO_PWM_MODE_PWM0_SAFETY_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_PWM0_SAFETY_SHIFT) & QEO_PWM_MODE_PWM0_SAFETY_MASK)
#define QEO_PWM_MODE_PWM0_SAFETY_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_PWM0_SAFETY_MASK) >> QEO_PWM_MODE_PWM0_SAFETY_SHIFT)

/*
 * PWM_ENTER_SAFETY_MODE (RW)
 *
 * PWM  enter safety mode
 * 0: not enter
 * 1: enter
 */
#define QEO_PWM_MODE_PWM_ENTER_SAFETY_MODE_MASK (0x200U)
#define QEO_PWM_MODE_PWM_ENTER_SAFETY_MODE_SHIFT (9U)
#define QEO_PWM_MODE_PWM_ENTER_SAFETY_MODE_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_PWM_ENTER_SAFETY_MODE_SHIFT) & QEO_PWM_MODE_PWM_ENTER_SAFETY_MODE_MASK)
#define QEO_PWM_MODE_PWM_ENTER_SAFETY_MODE_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_PWM_ENTER_SAFETY_MODE_MASK) >> QEO_PWM_MODE_PWM_ENTER_SAFETY_MODE_SHIFT)

/*
 * PWM_SAFETY_BYPASS (RW)
 *
 * PWM safety mode bypass
 * 0: not bypass
 * 1: bypass
 */
#define QEO_PWM_MODE_PWM_SAFETY_BYPASS_MASK (0x100U)
#define QEO_PWM_MODE_PWM_SAFETY_BYPASS_SHIFT (8U)
#define QEO_PWM_MODE_PWM_SAFETY_BYPASS_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_PWM_SAFETY_BYPASS_SHIFT) & QEO_PWM_MODE_PWM_SAFETY_BYPASS_MASK)
#define QEO_PWM_MODE_PWM_SAFETY_BYPASS_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_PWM_SAFETY_BYPASS_MASK) >> QEO_PWM_MODE_PWM_SAFETY_BYPASS_SHIFT)

/*
 * REVISE_UP_DN (RW)
 *
 * exchange PWM pairs’ output
 * 0: not exchange.
 * 1: exchange.
 */
#define QEO_PWM_MODE_REVISE_UP_DN_MASK (0x10U)
#define QEO_PWM_MODE_REVISE_UP_DN_SHIFT (4U)
#define QEO_PWM_MODE_REVISE_UP_DN_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_REVISE_UP_DN_SHIFT) & QEO_PWM_MODE_REVISE_UP_DN_MASK)
#define QEO_PWM_MODE_REVISE_UP_DN_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_REVISE_UP_DN_MASK) >> QEO_PWM_MODE_REVISE_UP_DN_SHIFT)

/*
 * PHASE_NUM (RW)
 *
 * pwm force phase number.
 */
#define QEO_PWM_MODE_PHASE_NUM_MASK (0xFU)
#define QEO_PWM_MODE_PHASE_NUM_SHIFT (0U)
#define QEO_PWM_MODE_PHASE_NUM_SET(x) (((uint32_t)(x) << QEO_PWM_MODE_PHASE_NUM_SHIFT) & QEO_PWM_MODE_PHASE_NUM_MASK)
#define QEO_PWM_MODE_PHASE_NUM_GET(x) (((uint32_t)(x) & QEO_PWM_MODE_PHASE_NUM_MASK) >> QEO_PWM_MODE_PHASE_NUM_SHIFT)

/* Bitfield definition for register of struct PWM: RESOLUTION */
/*
 * LINES (RW)
 *
 * pwm resolution
 */
#define QEO_PWM_RESOLUTION_LINES_MASK (0xFFFFFFFFUL)
#define QEO_PWM_RESOLUTION_LINES_SHIFT (0U)
#define QEO_PWM_RESOLUTION_LINES_SET(x) (((uint32_t)(x) << QEO_PWM_RESOLUTION_LINES_SHIFT) & QEO_PWM_RESOLUTION_LINES_MASK)
#define QEO_PWM_RESOLUTION_LINES_GET(x) (((uint32_t)(x) & QEO_PWM_RESOLUTION_LINES_MASK) >> QEO_PWM_RESOLUTION_LINES_SHIFT)

/* Bitfield definition for register of struct PWM: A */
/*
 * VAL (RW)
 *
 * pwm_a phase shifter value, default is 0x0. write other value will shift phase early as (cfg_value/2^16) period
 */
#define QEO_PWM_PHASE_SHIFT_VAL_MASK (0xFFFFU)
#define QEO_PWM_PHASE_SHIFT_VAL_SHIFT (0U)
#define QEO_PWM_PHASE_SHIFT_VAL_SET(x) (((uint32_t)(x) << QEO_PWM_PHASE_SHIFT_VAL_SHIFT) & QEO_PWM_PHASE_SHIFT_VAL_MASK)
#define QEO_PWM_PHASE_SHIFT_VAL_GET(x) (((uint32_t)(x) & QEO_PWM_PHASE_SHIFT_VAL_MASK) >> QEO_PWM_PHASE_SHIFT_VAL_SHIFT)

/* Bitfield definition for register of struct PWM: POSEDGE0 */
/*
 * PWM7 (RW)
 *
 * pwm phase table value
 */
#define QEO_PWM_PHASE_TABLE_PWM7_MASK (0xC000U)
#define QEO_PWM_PHASE_TABLE_PWM7_SHIFT (14U)
#define QEO_PWM_PHASE_TABLE_PWM7_SET(x) (((uint32_t)(x) << QEO_PWM_PHASE_TABLE_PWM7_SHIFT) & QEO_PWM_PHASE_TABLE_PWM7_MASK)
#define QEO_PWM_PHASE_TABLE_PWM7_GET(x) (((uint32_t)(x) & QEO_PWM_PHASE_TABLE_PWM7_MASK) >> QEO_PWM_PHASE_TABLE_PWM7_SHIFT)

/*
 * PWM6 (RW)
 *
 * pwm phase table value
 */
#define QEO_PWM_PHASE_TABLE_PWM6_MASK (0x3000U)
#define QEO_PWM_PHASE_TABLE_PWM6_SHIFT (12U)
#define QEO_PWM_PHASE_TABLE_PWM6_SET(x) (((uint32_t)(x) << QEO_PWM_PHASE_TABLE_PWM6_SHIFT) & QEO_PWM_PHASE_TABLE_PWM6_MASK)
#define QEO_PWM_PHASE_TABLE_PWM6_GET(x) (((uint32_t)(x) & QEO_PWM_PHASE_TABLE_PWM6_MASK) >> QEO_PWM_PHASE_TABLE_PWM6_SHIFT)

/*
 * PWM5 (RW)
 *
 * pwm phase table value
 */
#define QEO_PWM_PHASE_TABLE_PWM5_MASK (0xC00U)
#define QEO_PWM_PHASE_TABLE_PWM5_SHIFT (10U)
#define QEO_PWM_PHASE_TABLE_PWM5_SET(x) (((uint32_t)(x) << QEO_PWM_PHASE_TABLE_PWM5_SHIFT) & QEO_PWM_PHASE_TABLE_PWM5_MASK)
#define QEO_PWM_PHASE_TABLE_PWM5_GET(x) (((uint32_t)(x) & QEO_PWM_PHASE_TABLE_PWM5_MASK) >> QEO_PWM_PHASE_TABLE_PWM5_SHIFT)

/*
 * PWM4 (RW)
 *
 * pwm phase table value
 */
#define QEO_PWM_PHASE_TABLE_PWM4_MASK (0x300U)
#define QEO_PWM_PHASE_TABLE_PWM4_SHIFT (8U)
#define QEO_PWM_PHASE_TABLE_PWM4_SET(x) (((uint32_t)(x) << QEO_PWM_PHASE_TABLE_PWM4_SHIFT) & QEO_PWM_PHASE_TABLE_PWM4_MASK)
#define QEO_PWM_PHASE_TABLE_PWM4_GET(x) (((uint32_t)(x) & QEO_PWM_PHASE_TABLE_PWM4_MASK) >> QEO_PWM_PHASE_TABLE_PWM4_SHIFT)

/*
 * PWM3 (RW)
 *
 * pwm phase table value
 */
#define QEO_PWM_PHASE_TABLE_PWM3_MASK (0xC0U)
#define QEO_PWM_PHASE_TABLE_PWM3_SHIFT (6U)
#define QEO_PWM_PHASE_TABLE_PWM3_SET(x) (((uint32_t)(x) << QEO_PWM_PHASE_TABLE_PWM3_SHIFT) & QEO_PWM_PHASE_TABLE_PWM3_MASK)
#define QEO_PWM_PHASE_TABLE_PWM3_GET(x) (((uint32_t)(x) & QEO_PWM_PHASE_TABLE_PWM3_MASK) >> QEO_PWM_PHASE_TABLE_PWM3_SHIFT)

/*
 * PWM2 (RW)
 *
 * pwm phase table value
 */
#define QEO_PWM_PHASE_TABLE_PWM2_MASK (0x30U)
#define QEO_PWM_PHASE_TABLE_PWM2_SHIFT (4U)
#define QEO_PWM_PHASE_TABLE_PWM2_SET(x) (((uint32_t)(x) << QEO_PWM_PHASE_TABLE_PWM2_SHIFT) & QEO_PWM_PHASE_TABLE_PWM2_MASK)
#define QEO_PWM_PHASE_TABLE_PWM2_GET(x) (((uint32_t)(x) & QEO_PWM_PHASE_TABLE_PWM2_MASK) >> QEO_PWM_PHASE_TABLE_PWM2_SHIFT)

/*
 * PWM1 (RW)
 *
 * pwm phase table value
 */
#define QEO_PWM_PHASE_TABLE_PWM1_MASK (0xCU)
#define QEO_PWM_PHASE_TABLE_PWM1_SHIFT (2U)
#define QEO_PWM_PHASE_TABLE_PWM1_SET(x) (((uint32_t)(x) << QEO_PWM_PHASE_TABLE_PWM1_SHIFT) & QEO_PWM_PHASE_TABLE_PWM1_MASK)
#define QEO_PWM_PHASE_TABLE_PWM1_GET(x) (((uint32_t)(x) & QEO_PWM_PHASE_TABLE_PWM1_MASK) >> QEO_PWM_PHASE_TABLE_PWM1_SHIFT)

/*
 * PWM0 (RW)
 *
 * pwm phase table value
 */
#define QEO_PWM_PHASE_TABLE_PWM0_MASK (0x3U)
#define QEO_PWM_PHASE_TABLE_PWM0_SHIFT (0U)
#define QEO_PWM_PHASE_TABLE_PWM0_SET(x) (((uint32_t)(x) << QEO_PWM_PHASE_TABLE_PWM0_SHIFT) & QEO_PWM_PHASE_TABLE_PWM0_MASK)
#define QEO_PWM_PHASE_TABLE_PWM0_GET(x) (((uint32_t)(x) & QEO_PWM_PHASE_TABLE_PWM0_MASK) >> QEO_PWM_PHASE_TABLE_PWM0_SHIFT)

/* Bitfield definition for register: POSTION_SOFTWARE */
/*
 * POSTION_SOFTWAVE (RW)
 *
 * softwave inject postion
 */
#define QEO_POSTION_SOFTWARE_POSTION_SOFTWAVE_MASK (0xFFFFFFFFUL)
#define QEO_POSTION_SOFTWARE_POSTION_SOFTWAVE_SHIFT (0U)
#define QEO_POSTION_SOFTWARE_POSTION_SOFTWAVE_SET(x) (((uint32_t)(x) << QEO_POSTION_SOFTWARE_POSTION_SOFTWAVE_SHIFT) & QEO_POSTION_SOFTWARE_POSTION_SOFTWAVE_MASK)
#define QEO_POSTION_SOFTWARE_POSTION_SOFTWAVE_GET(x) (((uint32_t)(x) & QEO_POSTION_SOFTWARE_POSTION_SOFTWAVE_MASK) >> QEO_POSTION_SOFTWARE_POSTION_SOFTWAVE_SHIFT)

/* Bitfield definition for register: POSTION_SEL */
/*
 * POSTION_SEL (RW)
 *
 * enable softwave inject postion.
 * 0: disable.
 * 1: enable.
 */
#define QEO_POSTION_SEL_POSTION_SEL_MASK (0x1U)
#define QEO_POSTION_SEL_POSTION_SEL_SHIFT (0U)
#define QEO_POSTION_SEL_POSTION_SEL_SET(x) (((uint32_t)(x) << QEO_POSTION_SEL_POSTION_SEL_SHIFT) & QEO_POSTION_SEL_POSTION_SEL_MASK)
#define QEO_POSTION_SEL_POSTION_SEL_GET(x) (((uint32_t)(x) & QEO_POSTION_SEL_POSTION_SEL_MASK) >> QEO_POSTION_SEL_POSTION_SEL_SHIFT)

/* Bitfield definition for register: STATUS */
/*
 * PWM_FOURCE (RO)
 *
 * qeo_pwm_force observe
 */
#define QEO_STATUS_PWM_FOURCE_MASK (0xFFFF0000UL)
#define QEO_STATUS_PWM_FOURCE_SHIFT (16U)
#define QEO_STATUS_PWM_FOURCE_GET(x) (((uint32_t)(x) & QEO_STATUS_PWM_FOURCE_MASK) >> QEO_STATUS_PWM_FOURCE_SHIFT)

/*
 * PWM_SAFETY (RO)
 *
 * pwm_fault status
 */
#define QEO_STATUS_PWM_SAFETY_MASK (0x1U)
#define QEO_STATUS_PWM_SAFETY_SHIFT (0U)
#define QEO_STATUS_PWM_SAFETY_GET(x) (((uint32_t)(x) & QEO_STATUS_PWM_SAFETY_MASK) >> QEO_STATUS_PWM_SAFETY_SHIFT)

/* Bitfield definition for register: DEBUG0 */
/*
 * WAVE1 (RO)
 *
 * wave1 observe
 */
#define QEO_DEBUG0_WAVE1_MASK (0xFFFF0000UL)
#define QEO_DEBUG0_WAVE1_SHIFT (16U)
#define QEO_DEBUG0_WAVE1_GET(x) (((uint32_t)(x) & QEO_DEBUG0_WAVE1_MASK) >> QEO_DEBUG0_WAVE1_SHIFT)

/*
 * WAVE0 (RO)
 *
 * wave0 observe
 */
#define QEO_DEBUG0_WAVE0_MASK (0xFFFFU)
#define QEO_DEBUG0_WAVE0_SHIFT (0U)
#define QEO_DEBUG0_WAVE0_GET(x) (((uint32_t)(x) & QEO_DEBUG0_WAVE0_MASK) >> QEO_DEBUG0_WAVE0_SHIFT)

/* Bitfield definition for register: DEBUG1 */
/*
 * QEO_FINISH (RO)
 *
 * qeo finish observe
 */
#define QEO_DEBUG1_QEO_FINISH_MASK (0x10000000UL)
#define QEO_DEBUG1_QEO_FINISH_SHIFT (28U)
#define QEO_DEBUG1_QEO_FINISH_GET(x) (((uint32_t)(x) & QEO_DEBUG1_QEO_FINISH_MASK) >> QEO_DEBUG1_QEO_FINISH_SHIFT)

/*
 * WAVE_Z (RO)
 *
 * wave_z observe
 */
#define QEO_DEBUG1_WAVE_Z_MASK (0x1000000UL)
#define QEO_DEBUG1_WAVE_Z_SHIFT (24U)
#define QEO_DEBUG1_WAVE_Z_GET(x) (((uint32_t)(x) & QEO_DEBUG1_WAVE_Z_MASK) >> QEO_DEBUG1_WAVE_Z_SHIFT)

/*
 * WAVE_B (RO)
 *
 * wave_b observe
 */
#define QEO_DEBUG1_WAVE_B_MASK (0x100000UL)
#define QEO_DEBUG1_WAVE_B_SHIFT (20U)
#define QEO_DEBUG1_WAVE_B_GET(x) (((uint32_t)(x) & QEO_DEBUG1_WAVE_B_MASK) >> QEO_DEBUG1_WAVE_B_SHIFT)

/*
 * WAVE_A (RO)
 *
 * wave_a observe
 */
#define QEO_DEBUG1_WAVE_A_MASK (0x10000UL)
#define QEO_DEBUG1_WAVE_A_SHIFT (16U)
#define QEO_DEBUG1_WAVE_A_GET(x) (((uint32_t)(x) & QEO_DEBUG1_WAVE_A_MASK) >> QEO_DEBUG1_WAVE_A_SHIFT)

/*
 * WAVE2 (RO)
 *
 * wave2 observe
 */
#define QEO_DEBUG1_WAVE2_MASK (0xFFFFU)
#define QEO_DEBUG1_WAVE2_SHIFT (0U)
#define QEO_DEBUG1_WAVE2_GET(x) (((uint32_t)(x) & QEO_DEBUG1_WAVE2_MASK) >> QEO_DEBUG1_WAVE2_SHIFT)

/* Bitfield definition for register: DEBUG2 */
/*
 * ABZ_OWN_POSTION (RO)
 *
 * abz_own_postion observe
 */
#define QEO_DEBUG2_ABZ_OWN_POSTION_MASK (0xFFFFFFFFUL)
#define QEO_DEBUG2_ABZ_OWN_POSTION_SHIFT (0U)
#define QEO_DEBUG2_ABZ_OWN_POSTION_GET(x) (((uint32_t)(x) & QEO_DEBUG2_ABZ_OWN_POSTION_MASK) >> QEO_DEBUG2_ABZ_OWN_POSTION_SHIFT)

/* Bitfield definition for register: DEBUG3 */
/*
 * ABZ_OWN_POSTION (RO)
 *
 * abz_own_postion observe
 */
#define QEO_DEBUG3_ABZ_OWN_POSTION_MASK (0xFFFFFFFFUL)
#define QEO_DEBUG3_ABZ_OWN_POSTION_SHIFT (0U)
#define QEO_DEBUG3_ABZ_OWN_POSTION_GET(x) (((uint32_t)(x) & QEO_DEBUG3_ABZ_OWN_POSTION_MASK) >> QEO_DEBUG3_ABZ_OWN_POSTION_SHIFT)



/* PHASE_SHIFT register group index macro definition */
#define QEO_WAVE_PHASE_SHIFT_WAVE0 (0UL)
#define QEO_WAVE_PHASE_SHIFT_WAVE1 (1UL)
#define QEO_WAVE_PHASE_SHIFT_WAVE2 (2UL)

/* VD_VQ_INJECT register group index macro definition */
#define QEO_WAVE_VD_VQ_INJECT_WAVE0 (0UL)
#define QEO_WAVE_VD_VQ_INJECT_WAVE1 (1UL)
#define QEO_WAVE_VD_VQ_INJECT_WAVE2 (2UL)

/* AMPLITUDE register group index macro definition */
#define QEO_WAVE_AMPLITUDE_WAVE0 (0UL)
#define QEO_WAVE_AMPLITUDE_WAVE1 (1UL)
#define QEO_WAVE_AMPLITUDE_WAVE2 (2UL)

/* MID_POINT register group index macro definition */
#define QEO_WAVE_MID_POINT_WAVE0 (0UL)
#define QEO_WAVE_MID_POINT_WAVE1 (1UL)
#define QEO_WAVE_MID_POINT_WAVE2 (2UL)

/* LIMIT register group index macro definition */
#define QEO_LIMIT_WAVE0 (0UL)
#define QEO_LIMIT_WAVE1 (1UL)
#define QEO_LIMIT_WAVE2 (2UL)

/* DEADZONE_SHIFT register group index macro definition */
#define QEO_WAVE_DEADZONE_SHIFT_WAVE0 (0UL)
#define QEO_WAVE_DEADZONE_SHIFT_WAVE1 (1UL)
#define QEO_WAVE_DEADZONE_SHIFT_WAVE2 (2UL)

/* PHASE_SHIFT register group index macro definition */
#define QEO_ABZ_PHASE_SHIFT_A (0UL)
#define QEO_ABZ_PHASE_SHIFT_B (1UL)
#define QEO_ABZ_PHASE_SHIFT_Z (2UL)

/* PHASE_SHIFT register group index macro definition */
#define QEO_PWM_PHASE_SHIFT_A (0UL)
#define QEO_PWM_PHASE_SHIFT_B (1UL)
#define QEO_PWM_PHASE_SHIFT_C (2UL)
#define QEO_PWM_PHASE_SHIFT_D (3UL)

/* PHASE_TABLE register group index macro definition */
#define QEO_PWM_PHASE_TABLE_POSEDGE0 (0UL)
#define QEO_PWM_PHASE_TABLE_POSEDGE1 (1UL)
#define QEO_PWM_PHASE_TABLE_POSEDGE2 (2UL)
#define QEO_PWM_PHASE_TABLE_POSEDGE3 (3UL)
#define QEO_PWM_PHASE_TABLE_POSEDGE4 (4UL)
#define QEO_PWM_PHASE_TABLE_POSEDGE5 (5UL)
#define QEO_PWM_PHASE_TABLE_POSEDGE6 (6UL)
#define QEO_PWM_PHASE_TABLE_POSEDGE7 (7UL)
#define QEO_PWM_PHASE_TABLE_POSEDGE8 (8UL)
#define QEO_PWM_PHASE_TABLE_POSEDGE9 (9UL)
#define QEO_PWM_PHASE_TABLE_POSEDGE10 (10UL)
#define QEO_PWM_PHASE_TABLE_POSEDGE11 (11UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE0 (12UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE1 (13UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE2 (14UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE3 (15UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE4 (16UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE5 (17UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE6 (18UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE7 (19UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE8 (20UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE9 (21UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE10 (22UL)
#define QEO_PWM_PHASE_TABLE_NEGEDGE11 (23UL)


#endif /* HPM_QEO_H */
