/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_BMON_H
#define HPM_BMON_H

typedef struct {
    struct {
        __RW uint32_t CONTROL;                 /* 0x0: Glitch and clock monitor control */
        __RW uint32_t STATUS;                  /* 0x4: Glitch and clock monitor status */
        __R  uint8_t  RESERVED0[8];            /* 0x8 - 0xF: Reserved */
    } MONITOR[2];
} BMON_Type;


/* Bitfield definition for register of struct array MONITOR: CONTROL */
/*
 * ACTIVE (RW)
 *
 * select glitch works in active mode or passve mode.
 * 0: passive mode, depends on power glitch destroy DFF value
 * 1: active mode, check glitch by DFF chain
 */
#define BMON_MONITOR_CONTROL_ACTIVE_MASK (0x10U)
#define BMON_MONITOR_CONTROL_ACTIVE_SHIFT (4U)
#define BMON_MONITOR_CONTROL_ACTIVE_SET(x) (((uint32_t)(x) << BMON_MONITOR_CONTROL_ACTIVE_SHIFT) & BMON_MONITOR_CONTROL_ACTIVE_MASK)
#define BMON_MONITOR_CONTROL_ACTIVE_GET(x) (((uint32_t)(x) & BMON_MONITOR_CONTROL_ACTIVE_MASK) >> BMON_MONITOR_CONTROL_ACTIVE_SHIFT)

/*
 * ENABLE (RW)
 *
 * enable glitch detector
 * 0: detector disabled
 * 1: detector enabled
 */
#define BMON_MONITOR_CONTROL_ENABLE_MASK (0x1U)
#define BMON_MONITOR_CONTROL_ENABLE_SHIFT (0U)
#define BMON_MONITOR_CONTROL_ENABLE_SET(x) (((uint32_t)(x) << BMON_MONITOR_CONTROL_ENABLE_SHIFT) & BMON_MONITOR_CONTROL_ENABLE_MASK)
#define BMON_MONITOR_CONTROL_ENABLE_GET(x) (((uint32_t)(x) & BMON_MONITOR_CONTROL_ENABLE_MASK) >> BMON_MONITOR_CONTROL_ENABLE_SHIFT)

/* Bitfield definition for register of struct array MONITOR: STATUS */
/*
 * FLAG (RW)
 *
 * flag for glitch detected, write 1 to clear this flag
 * 0: glitch not detected
 * 1: glitch detected
 */
#define BMON_MONITOR_STATUS_FLAG_MASK (0x1U)
#define BMON_MONITOR_STATUS_FLAG_SHIFT (0U)
#define BMON_MONITOR_STATUS_FLAG_SET(x) (((uint32_t)(x) << BMON_MONITOR_STATUS_FLAG_SHIFT) & BMON_MONITOR_STATUS_FLAG_MASK)
#define BMON_MONITOR_STATUS_FLAG_GET(x) (((uint32_t)(x) & BMON_MONITOR_STATUS_FLAG_MASK) >> BMON_MONITOR_STATUS_FLAG_SHIFT)



/* MONITOR register group index macro definition */
#define BMON_MONITOR_GLITCH0 (0UL)
#define BMON_MONITOR_CLOCK0 (1UL)


#endif /* HPM_BMON_H */
