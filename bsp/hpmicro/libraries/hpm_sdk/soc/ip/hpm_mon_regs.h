/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_MON_H
#define HPM_MON_H

typedef struct {
    struct {
        __RW uint32_t CONTROL;                 /* 0x0: Glitch and clock monitor control */
        __RW uint32_t STATUS;                  /* 0x4: Glitch and clock monitor status */
    } MONITOR[4];
    __RW uint32_t TEST_MODE;                   /* 0x20:  */
    __R  uint8_t  RESERVED0[28];               /* 0x24 - 0x3F: Reserved */
    __RW uint32_t IRQ_FLAG;                    /* 0x40:  */
    __RW uint32_t IRQ_ENABLE;                  /* 0x44:  */
} MON_Type;


/* Bitfield definition for register of struct array MONITOR: CONTROL */
/*
 * ACTIVE (RW)
 *
 * select glitch works in active mode or passve mode.
 * 0: passive mode, depends on power glitch destory DFF value
 * 1: active mode, check glitch by DFF chain
 */
#define MON_MONITOR_CONTROL_ACTIVE_MASK (0x10U)
#define MON_MONITOR_CONTROL_ACTIVE_SHIFT (4U)
#define MON_MONITOR_CONTROL_ACTIVE_SET(x) (((uint32_t)(x) << MON_MONITOR_CONTROL_ACTIVE_SHIFT) & MON_MONITOR_CONTROL_ACTIVE_MASK)
#define MON_MONITOR_CONTROL_ACTIVE_GET(x) (((uint32_t)(x) & MON_MONITOR_CONTROL_ACTIVE_MASK) >> MON_MONITOR_CONTROL_ACTIVE_SHIFT)

/*
 * ENABLE (RW)
 *
 * enable glitch detector
 * 0: detector disabled
 * 1: detector enabled
 */
#define MON_MONITOR_CONTROL_ENABLE_MASK (0x1U)
#define MON_MONITOR_CONTROL_ENABLE_SHIFT (0U)
#define MON_MONITOR_CONTROL_ENABLE_SET(x) (((uint32_t)(x) << MON_MONITOR_CONTROL_ENABLE_SHIFT) & MON_MONITOR_CONTROL_ENABLE_MASK)
#define MON_MONITOR_CONTROL_ENABLE_GET(x) (((uint32_t)(x) & MON_MONITOR_CONTROL_ENABLE_MASK) >> MON_MONITOR_CONTROL_ENABLE_SHIFT)

/* Bitfield definition for register of struct array MONITOR: STATUS */
/*
 * FLAG (RW)
 *
 * flag for glitch detected, write 1 to clear this flag
 * 0: glitch not detected
 * 1: glitch detected
 */
#define MON_MONITOR_STATUS_FLAG_MASK (0x1U)
#define MON_MONITOR_STATUS_FLAG_SHIFT (0U)
#define MON_MONITOR_STATUS_FLAG_SET(x) (((uint32_t)(x) << MON_MONITOR_STATUS_FLAG_SHIFT) & MON_MONITOR_STATUS_FLAG_MASK)
#define MON_MONITOR_STATUS_FLAG_GET(x) (((uint32_t)(x) & MON_MONITOR_STATUS_FLAG_MASK) >> MON_MONITOR_STATUS_FLAG_SHIFT)

/* Bitfield definition for register: TEST_MODE */
/*
 * DISABLE (RW)
 *
 * disable test mode entry, any non-zero value written to this register causes disable bit set
 * 0: test mode enabled
 * 1: test mode disabled
 * Note: This register only available in BATT domain
 */
#define MON_TEST_MODE_DISABLE_MASK (0xFFFFFFFFUL)
#define MON_TEST_MODE_DISABLE_SHIFT (0U)
#define MON_TEST_MODE_DISABLE_SET(x) (((uint32_t)(x) << MON_TEST_MODE_DISABLE_SHIFT) & MON_TEST_MODE_DISABLE_MASK)
#define MON_TEST_MODE_DISABLE_GET(x) (((uint32_t)(x) & MON_TEST_MODE_DISABLE_MASK) >> MON_TEST_MODE_DISABLE_SHIFT)

/* Bitfield definition for register: IRQ_FLAG */
/*
 * FLAG (RW)
 *
 * interrupt flag, each bit represents for one monitor, write 1 to clear interrupt flag
 * 0: no monitor interrupt 
 * 1: monitor interrupt happened
 * Note: This register only available in PMIC domain
 */
#define MON_IRQ_FLAG_FLAG_MASK (0xFU)
#define MON_IRQ_FLAG_FLAG_SHIFT (0U)
#define MON_IRQ_FLAG_FLAG_SET(x) (((uint32_t)(x) << MON_IRQ_FLAG_FLAG_SHIFT) & MON_IRQ_FLAG_FLAG_MASK)
#define MON_IRQ_FLAG_FLAG_GET(x) (((uint32_t)(x) & MON_IRQ_FLAG_FLAG_MASK) >> MON_IRQ_FLAG_FLAG_SHIFT)

/* Bitfield definition for register: IRQ_ENABLE */
/*
 * ENABLE (RW)
 *
 * interrupt enable, each bit represents for one monitor
 * 0: monitor interrupt disabled
 * 1: monitor interrupt enabled
 * Note: This register only available in PMIC domain
 */
#define MON_IRQ_ENABLE_ENABLE_MASK (0xFU)
#define MON_IRQ_ENABLE_ENABLE_SHIFT (0U)
#define MON_IRQ_ENABLE_ENABLE_SET(x) (((uint32_t)(x) << MON_IRQ_ENABLE_ENABLE_SHIFT) & MON_IRQ_ENABLE_ENABLE_MASK)
#define MON_IRQ_ENABLE_ENABLE_GET(x) (((uint32_t)(x) & MON_IRQ_ENABLE_ENABLE_MASK) >> MON_IRQ_ENABLE_ENABLE_SHIFT)



/* MONITOR register group index macro definition */
#define MON_MONITOR_GLITCH0 (0UL)
#define MON_MONITOR_GLITCH1 (1UL)
#define MON_MONITOR_CLOCK0 (2UL)
#define MON_MONITOR_CLOCK1 (3UL)


#endif /* HPM_MON_H */
