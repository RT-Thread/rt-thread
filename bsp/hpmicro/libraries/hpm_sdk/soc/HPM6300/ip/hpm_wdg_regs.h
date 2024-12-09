/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_WDG_H
#define HPM_WDG_H

typedef struct {
    __R  uint8_t  RESERVED0[16];               /* 0x0 - 0xF: Reserved */
    __RW uint32_t CTRL;                        /* 0x10: Control Register */
    __W  uint32_t RESTART;                     /* 0x14: Restart Register */
    __W  uint32_t WREN;                        /* 0x18: Write Protection Register */
    __W  uint32_t ST;                          /* 0x1C: Status Register */
} WDG_Type;


/* Bitfield definition for register: CTRL */
/*
 * RSTTIME (RW)
 *
 * The time interval of the reset stage:
 * 0: Clock period x 2^7
 * 1: Clock period x 2^8
 * 2: Clock period x 2^9
 * 3: Clock period x 2^10
 * 4: Clock period x 2^11
 * 5: Clock period x 2^12
 * 6: Clock period x 2^13
 * 7: Clock period x 2^14
 */
#define WDG_CTRL_RSTTIME_MASK (0x700U)
#define WDG_CTRL_RSTTIME_SHIFT (8U)
#define WDG_CTRL_RSTTIME_SET(x) (((uint32_t)(x) << WDG_CTRL_RSTTIME_SHIFT) & WDG_CTRL_RSTTIME_MASK)
#define WDG_CTRL_RSTTIME_GET(x) (((uint32_t)(x) & WDG_CTRL_RSTTIME_MASK) >> WDG_CTRL_RSTTIME_SHIFT)

/*
 * INTTIME (RW)
 *
 * The timer interval of the interrupt stage:
 * 0: Clock period x 2^6
 * 1: Clock period x 2^8
 * 2: Clock period x 2^10
 * 3: Clock period x 2^11
 * 4: Clock period x 2^12
 * 5: Clock period x 2^13
 * 6: Clock period x 2^14
 * 7: Clock period x 2^15
 * 8: Clock period x 2^17
 * 9: Clock period x 2^19
 * 10: Clock period x 2^21
 * 11: Clock period x 2^23
 * 12: Clock period x 2^25
 * 13: Clock period x 2^27
 * 14: Clock period x 2^29
 * 15: Clock period x 2^31
 */
#define WDG_CTRL_INTTIME_MASK (0xF0U)
#define WDG_CTRL_INTTIME_SHIFT (4U)
#define WDG_CTRL_INTTIME_SET(x) (((uint32_t)(x) << WDG_CTRL_INTTIME_SHIFT) & WDG_CTRL_INTTIME_MASK)
#define WDG_CTRL_INTTIME_GET(x) (((uint32_t)(x) & WDG_CTRL_INTTIME_MASK) >> WDG_CTRL_INTTIME_SHIFT)

/*
 * RSTEN (RW)
 *
 * Enable or disable the watchdog reset
 * 0: Disable
 * 1: Enable
 */
#define WDG_CTRL_RSTEN_MASK (0x8U)
#define WDG_CTRL_RSTEN_SHIFT (3U)
#define WDG_CTRL_RSTEN_SET(x) (((uint32_t)(x) << WDG_CTRL_RSTEN_SHIFT) & WDG_CTRL_RSTEN_MASK)
#define WDG_CTRL_RSTEN_GET(x) (((uint32_t)(x) & WDG_CTRL_RSTEN_MASK) >> WDG_CTRL_RSTEN_SHIFT)

/*
 * INTEN (RW)
 *
 * Enable or disable the watchdog interrupt
 * 0: Disable
 * 1: Enable
 */
#define WDG_CTRL_INTEN_MASK (0x4U)
#define WDG_CTRL_INTEN_SHIFT (2U)
#define WDG_CTRL_INTEN_SET(x) (((uint32_t)(x) << WDG_CTRL_INTEN_SHIFT) & WDG_CTRL_INTEN_MASK)
#define WDG_CTRL_INTEN_GET(x) (((uint32_t)(x) & WDG_CTRL_INTEN_MASK) >> WDG_CTRL_INTEN_SHIFT)

/*
 * CLKSEL (RW)
 *
 * Clock source of timer:
 * 0: EXTCLK
 * 1: PCLK
 */
#define WDG_CTRL_CLKSEL_MASK (0x2U)
#define WDG_CTRL_CLKSEL_SHIFT (1U)
#define WDG_CTRL_CLKSEL_SET(x) (((uint32_t)(x) << WDG_CTRL_CLKSEL_SHIFT) & WDG_CTRL_CLKSEL_MASK)
#define WDG_CTRL_CLKSEL_GET(x) (((uint32_t)(x) & WDG_CTRL_CLKSEL_MASK) >> WDG_CTRL_CLKSEL_SHIFT)

/*
 * EN (RW)
 *
 * Enable or disable the watchdog timer
 * 0: Disable
 * 1: Enable
 */
#define WDG_CTRL_EN_MASK (0x1U)
#define WDG_CTRL_EN_SHIFT (0U)
#define WDG_CTRL_EN_SET(x) (((uint32_t)(x) << WDG_CTRL_EN_SHIFT) & WDG_CTRL_EN_MASK)
#define WDG_CTRL_EN_GET(x) (((uint32_t)(x) & WDG_CTRL_EN_MASK) >> WDG_CTRL_EN_SHIFT)

/* Bitfield definition for register: RESTART */
/*
 * RESTART (WO)
 *
 * Write the magic number
 * ATCWDT200_RESTART_NUM to restart the
 * watchdog timer.
 */
#define WDG_RESTART_RESTART_MASK (0xFFFFU)
#define WDG_RESTART_RESTART_SHIFT (0U)
#define WDG_RESTART_RESTART_SET(x) (((uint32_t)(x) << WDG_RESTART_RESTART_SHIFT) & WDG_RESTART_RESTART_MASK)
#define WDG_RESTART_RESTART_GET(x) (((uint32_t)(x) & WDG_RESTART_RESTART_MASK) >> WDG_RESTART_RESTART_SHIFT)

/* Bitfield definition for register: WREN */
/*
 * WEN (WO)
 *
 * Write the magic code to disable the write
 * protection of the Control Register and the
 * Restart Register.
 */
#define WDG_WREN_WEN_MASK (0xFFFFU)
#define WDG_WREN_WEN_SHIFT (0U)
#define WDG_WREN_WEN_SET(x) (((uint32_t)(x) << WDG_WREN_WEN_SHIFT) & WDG_WREN_WEN_MASK)
#define WDG_WREN_WEN_GET(x) (((uint32_t)(x) & WDG_WREN_WEN_MASK) >> WDG_WREN_WEN_SHIFT)

/* Bitfield definition for register: ST */
/*
 * INTEXPIRED (W1C)
 *
 * The status of the watchdog interrupt timer
 * 0: timer is not expired yet
 * 1: timer is expired
 */
#define WDG_ST_INTEXPIRED_MASK (0x1U)
#define WDG_ST_INTEXPIRED_SHIFT (0U)
#define WDG_ST_INTEXPIRED_SET(x) (((uint32_t)(x) << WDG_ST_INTEXPIRED_SHIFT) & WDG_ST_INTEXPIRED_MASK)
#define WDG_ST_INTEXPIRED_GET(x) (((uint32_t)(x) & WDG_ST_INTEXPIRED_MASK) >> WDG_ST_INTEXPIRED_SHIFT)




#endif /* HPM_WDG_H */
