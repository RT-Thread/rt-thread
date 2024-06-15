/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SYSCTL_H
#define HPM_SYSCTL_H

typedef struct {
    __RW uint32_t RESOURCE[350];               /* 0x0 - 0x574: Resource control register for cpu0 */
    __R  uint8_t  RESERVED0[648];              /* 0x578 - 0x7FF: Reserved */
    struct {
        __RW uint32_t VALUE;                   /* 0x800: Goup setting */
        __RW uint32_t SET;                     /* 0x804: Goup setting */
        __RW uint32_t CLEAR;                   /* 0x808: Goup setting */
        __RW uint32_t TOGGLE;                  /* 0x80C: Goup setting */
    } GROUP0[3];
    __R  uint8_t  RESERVED1[16];               /* 0x830 - 0x83F: Reserved */
    struct {
        __RW uint32_t VALUE;                   /* 0x840: Goup setting */
        __RW uint32_t SET;                     /* 0x844: Goup setting */
        __RW uint32_t CLEAR;                   /* 0x848: Goup setting */
        __RW uint32_t TOGGLE;                  /* 0x84C: Goup setting */
    } GROUP1[3];
    __R  uint8_t  RESERVED2[144];              /* 0x870 - 0x8FF: Reserved */
    struct {
        __RW uint32_t VALUE;                   /* 0x900: Affiliate of Group */
        __RW uint32_t SET;                     /* 0x904: Affiliate of Group */
        __RW uint32_t CLEAR;                   /* 0x908: Affiliate of Group */
        __RW uint32_t TOGGLE;                  /* 0x90C: Affiliate of Group */
    } AFFILIATE[2];
    struct {
        __RW uint32_t VALUE;                   /* 0x920: Retention Control */
        __RW uint32_t SET;                     /* 0x924: Retention Control */
        __RW uint32_t CLEAR;                   /* 0x928: Retention Control */
        __RW uint32_t TOGGLE;                  /* 0x92C: Retention Control */
    } RETENTION[2];
    __R  uint8_t  RESERVED3[1728];             /* 0x940 - 0xFFF: Reserved */
    struct {
        __RW uint32_t STATUS;                  /* 0x1000: Power Setting */
        __RW uint32_t LF_WAIT;                 /* 0x1004: Power Setting */
        __R  uint8_t  RESERVED0[4];            /* 0x1008 - 0x100B: Reserved */
        __RW uint32_t OFF_WAIT;                /* 0x100C: Power Setting */
    } POWER[4];
    __R  uint8_t  RESERVED4[960];              /* 0x1040 - 0x13FF: Reserved */
    struct {
        __RW uint32_t CONTROL;                 /* 0x1400: Reset Setting */
        __RW uint32_t CONFIG;                  /* 0x1404: Reset Setting */
        __R  uint8_t  RESERVED0[4];            /* 0x1408 - 0x140B: Reserved */
        __RW uint32_t COUNTER;                 /* 0x140C: Reset Setting */
    } RESET[5];
    __R  uint8_t  RESERVED5[944];              /* 0x1450 - 0x17FF: Reserved */
    __RW uint32_t CLOCK[67];                   /* 0x1800 - 0x1908: Clock setting */
    __R  uint8_t  RESERVED6[756];              /* 0x190C - 0x1BFF: Reserved */
    __RW uint32_t ADCCLK[4];                   /* 0x1C00 - 0x1C0C: Clock setting */
    __RW uint32_t I2SCLK[4];                   /* 0x1C10 - 0x1C1C: Clock setting */
    __R  uint8_t  RESERVED7[992];              /* 0x1C20 - 0x1FFF: Reserved */
    __RW uint32_t GLOBAL00;                    /* 0x2000: Clock senario */
    __R  uint8_t  RESERVED8[1020];             /* 0x2004 - 0x23FF: Reserved */
    struct {
        __RW uint32_t CONTROL;                 /* 0x2400: Clock measure and monitor control */
        __R  uint32_t CURRENT;                 /* 0x2404: Clock measure result */
        __RW uint32_t LOW_LIMIT;               /* 0x2408: Clock lower limit */
        __RW uint32_t HIGH_LIMIT;              /* 0x240C: Clock upper limit */
        __R  uint8_t  RESERVED0[16];           /* 0x2410 - 0x241F: Reserved */
    } MONITOR[4];
    __R  uint8_t  RESERVED9[896];              /* 0x2480 - 0x27FF: Reserved */
    struct {
        __RW uint32_t LP;                      /* 0x2800:  */
        __RW uint32_t LOCK;                    /* 0x2804:  */
        __RW uint32_t GPR[14];                 /* 0x2808 - 0x283C:  */
        __R  uint32_t WAKEUP_STATUS[8];        /* 0x2840 - 0x285C:  */
        __R  uint8_t  RESERVED0[32];           /* 0x2860 - 0x287F: Reserved */
        __RW uint32_t WAKEUP_ENABLE[8];        /* 0x2880 - 0x289C:  */
        __R  uint8_t  RESERVED1[864];          /* 0x28A0 - 0x2BFF: Reserved */
    } CPU[2];
} SYSCTL_Type;


/* Bitfield definition for register array: RESOURCE */
/*
 * GLB_BUSY (RO)
 *
 * global busy
 * 0: no changes pending to any nodes
 * 1: any of nodes is changing status
 */
#define SYSCTL_RESOURCE_GLB_BUSY_MASK (0x80000000UL)
#define SYSCTL_RESOURCE_GLB_BUSY_SHIFT (31U)
#define SYSCTL_RESOURCE_GLB_BUSY_GET(x) (((uint32_t)(x) & SYSCTL_RESOURCE_GLB_BUSY_MASK) >> SYSCTL_RESOURCE_GLB_BUSY_SHIFT)

/*
 * LOC_BUSY (RO)
 *
 * local busy
 * 0: no change is pending for current node
 * 1: current node is changing status
 */
#define SYSCTL_RESOURCE_LOC_BUSY_MASK (0x40000000UL)
#define SYSCTL_RESOURCE_LOC_BUSY_SHIFT (30U)
#define SYSCTL_RESOURCE_LOC_BUSY_GET(x) (((uint32_t)(x) & SYSCTL_RESOURCE_LOC_BUSY_MASK) >> SYSCTL_RESOURCE_LOC_BUSY_SHIFT)

/*
 * MODE (RW)
 *
 * resource work mode
 * 0:auto turn on and off as system required(recommended)
 * 1:always on
 * 2:always off
 * 3:reserved
 */
#define SYSCTL_RESOURCE_MODE_MASK (0x3U)
#define SYSCTL_RESOURCE_MODE_SHIFT (0U)
#define SYSCTL_RESOURCE_MODE_SET(x) (((uint32_t)(x) << SYSCTL_RESOURCE_MODE_SHIFT) & SYSCTL_RESOURCE_MODE_MASK)
#define SYSCTL_RESOURCE_MODE_GET(x) (((uint32_t)(x) & SYSCTL_RESOURCE_MODE_MASK) >> SYSCTL_RESOURCE_MODE_SHIFT)

/* Bitfield definition for register of struct array GROUP0: VALUE */
/*
 * LINK (RW)
 *
 * denpendency on peripherals, index count from resource ahbp(0x400),each bit represents a peripheral
 * 0: peripheral is not needed
 * 1: periphera is needed
 */
#define SYSCTL_GROUP0_VALUE_LINK_MASK (0xFFFFFFFFUL)
#define SYSCTL_GROUP0_VALUE_LINK_SHIFT (0U)
#define SYSCTL_GROUP0_VALUE_LINK_SET(x) (((uint32_t)(x) << SYSCTL_GROUP0_VALUE_LINK_SHIFT) & SYSCTL_GROUP0_VALUE_LINK_MASK)
#define SYSCTL_GROUP0_VALUE_LINK_GET(x) (((uint32_t)(x) & SYSCTL_GROUP0_VALUE_LINK_MASK) >> SYSCTL_GROUP0_VALUE_LINK_SHIFT)

/* Bitfield definition for register of struct array GROUP0: SET */
/*
 * LINK (RW)
 *
 * denpendency on peripherals, index count from resource ahbp(0x400),each bit represents a peripheral
 * 0: peripheral is not needed
 * 1: periphera is needed
 */
#define SYSCTL_GROUP0_SET_LINK_MASK (0xFFFFFFFFUL)
#define SYSCTL_GROUP0_SET_LINK_SHIFT (0U)
#define SYSCTL_GROUP0_SET_LINK_SET(x) (((uint32_t)(x) << SYSCTL_GROUP0_SET_LINK_SHIFT) & SYSCTL_GROUP0_SET_LINK_MASK)
#define SYSCTL_GROUP0_SET_LINK_GET(x) (((uint32_t)(x) & SYSCTL_GROUP0_SET_LINK_MASK) >> SYSCTL_GROUP0_SET_LINK_SHIFT)

/* Bitfield definition for register of struct array GROUP0: CLEAR */
/*
 * LINK (RW)
 *
 * denpendency on peripherals, index count from resource ahbp(0x400),each bit represents a peripheral
 * 0: peripheral is not needed
 * 1: periphera is needed
 */
#define SYSCTL_GROUP0_CLEAR_LINK_MASK (0xFFFFFFFFUL)
#define SYSCTL_GROUP0_CLEAR_LINK_SHIFT (0U)
#define SYSCTL_GROUP0_CLEAR_LINK_SET(x) (((uint32_t)(x) << SYSCTL_GROUP0_CLEAR_LINK_SHIFT) & SYSCTL_GROUP0_CLEAR_LINK_MASK)
#define SYSCTL_GROUP0_CLEAR_LINK_GET(x) (((uint32_t)(x) & SYSCTL_GROUP0_CLEAR_LINK_MASK) >> SYSCTL_GROUP0_CLEAR_LINK_SHIFT)

/* Bitfield definition for register of struct array GROUP0: TOGGLE */
/*
 * LINK (RW)
 *
 * denpendency on peripherals, index count from resource ahbp(0x400),each bit represents a peripheral
 * 0: peripheral is not needed
 * 1: periphera is needed
 */
#define SYSCTL_GROUP0_TOGGLE_LINK_MASK (0xFFFFFFFFUL)
#define SYSCTL_GROUP0_TOGGLE_LINK_SHIFT (0U)
#define SYSCTL_GROUP0_TOGGLE_LINK_SET(x) (((uint32_t)(x) << SYSCTL_GROUP0_TOGGLE_LINK_SHIFT) & SYSCTL_GROUP0_TOGGLE_LINK_MASK)
#define SYSCTL_GROUP0_TOGGLE_LINK_GET(x) (((uint32_t)(x) & SYSCTL_GROUP0_TOGGLE_LINK_MASK) >> SYSCTL_GROUP0_TOGGLE_LINK_SHIFT)

/* Bitfield definition for register of struct array GROUP1: VALUE */
/*
 * LINK (RW)
 *
 * denpendency on peripherals, index count from resource ahbp(0x400),each bit represents a peripheral
 * 0: peripheral is not needed
 * 1: periphera is needed
 */
#define SYSCTL_GROUP1_VALUE_LINK_MASK (0xFFFFFFFFUL)
#define SYSCTL_GROUP1_VALUE_LINK_SHIFT (0U)
#define SYSCTL_GROUP1_VALUE_LINK_SET(x) (((uint32_t)(x) << SYSCTL_GROUP1_VALUE_LINK_SHIFT) & SYSCTL_GROUP1_VALUE_LINK_MASK)
#define SYSCTL_GROUP1_VALUE_LINK_GET(x) (((uint32_t)(x) & SYSCTL_GROUP1_VALUE_LINK_MASK) >> SYSCTL_GROUP1_VALUE_LINK_SHIFT)

/* Bitfield definition for register of struct array GROUP1: SET */
/*
 * LINK (RW)
 *
 * denpendency on peripherals, index count from resource ahbp(0x400),each bit represents a peripheral
 * 0: peripheral is not needed
 * 1: periphera is needed
 */
#define SYSCTL_GROUP1_SET_LINK_MASK (0xFFFFFFFFUL)
#define SYSCTL_GROUP1_SET_LINK_SHIFT (0U)
#define SYSCTL_GROUP1_SET_LINK_SET(x) (((uint32_t)(x) << SYSCTL_GROUP1_SET_LINK_SHIFT) & SYSCTL_GROUP1_SET_LINK_MASK)
#define SYSCTL_GROUP1_SET_LINK_GET(x) (((uint32_t)(x) & SYSCTL_GROUP1_SET_LINK_MASK) >> SYSCTL_GROUP1_SET_LINK_SHIFT)

/* Bitfield definition for register of struct array GROUP1: CLEAR */
/*
 * LINK (RW)
 *
 * denpendency on peripherals, index count from resource ahbp(0x400),each bit represents a peripheral
 * 0: peripheral is not needed
 * 1: periphera is needed
 */
#define SYSCTL_GROUP1_CLEAR_LINK_MASK (0xFFFFFFFFUL)
#define SYSCTL_GROUP1_CLEAR_LINK_SHIFT (0U)
#define SYSCTL_GROUP1_CLEAR_LINK_SET(x) (((uint32_t)(x) << SYSCTL_GROUP1_CLEAR_LINK_SHIFT) & SYSCTL_GROUP1_CLEAR_LINK_MASK)
#define SYSCTL_GROUP1_CLEAR_LINK_GET(x) (((uint32_t)(x) & SYSCTL_GROUP1_CLEAR_LINK_MASK) >> SYSCTL_GROUP1_CLEAR_LINK_SHIFT)

/* Bitfield definition for register of struct array GROUP1: TOGGLE */
/*
 * LINK (RW)
 *
 * denpendency on peripherals, index count from resource ahbp(0x400),each bit represents a peripheral
 * 0: peripheral is not needed
 * 1: periphera is needed
 */
#define SYSCTL_GROUP1_TOGGLE_LINK_MASK (0xFFFFFFFFUL)
#define SYSCTL_GROUP1_TOGGLE_LINK_SHIFT (0U)
#define SYSCTL_GROUP1_TOGGLE_LINK_SET(x) (((uint32_t)(x) << SYSCTL_GROUP1_TOGGLE_LINK_SHIFT) & SYSCTL_GROUP1_TOGGLE_LINK_MASK)
#define SYSCTL_GROUP1_TOGGLE_LINK_GET(x) (((uint32_t)(x) & SYSCTL_GROUP1_TOGGLE_LINK_MASK) >> SYSCTL_GROUP1_TOGGLE_LINK_SHIFT)

/* Bitfield definition for register of struct array AFFILIATE: VALUE */
/*
 * LINK (RW)
 *
 * Affiliate groups of cpu0
 * bit0: cpu0 depends on logic node0
 * bit1: cpu0 depends on logic node1
 * bit2: cpu0 depends on logic node2
 * bit3: cpu0 depends on logic node3
 */
#define SYSCTL_AFFILIATE_VALUE_LINK_MASK (0xFU)
#define SYSCTL_AFFILIATE_VALUE_LINK_SHIFT (0U)
#define SYSCTL_AFFILIATE_VALUE_LINK_SET(x) (((uint32_t)(x) << SYSCTL_AFFILIATE_VALUE_LINK_SHIFT) & SYSCTL_AFFILIATE_VALUE_LINK_MASK)
#define SYSCTL_AFFILIATE_VALUE_LINK_GET(x) (((uint32_t)(x) & SYSCTL_AFFILIATE_VALUE_LINK_MASK) >> SYSCTL_AFFILIATE_VALUE_LINK_SHIFT)

/* Bitfield definition for register of struct array AFFILIATE: SET */
/*
 * LINK (RW)
 *
 * Affiliate groups of cpu0
 * bit0: cpu0 depends on logic node0
 * bit1: cpu0 depends on logic node1
 * bit2: cpu0 depends on logic node2
 * bit3: cpu0 depends on logic node3
 */
#define SYSCTL_AFFILIATE_SET_LINK_MASK (0xFU)
#define SYSCTL_AFFILIATE_SET_LINK_SHIFT (0U)
#define SYSCTL_AFFILIATE_SET_LINK_SET(x) (((uint32_t)(x) << SYSCTL_AFFILIATE_SET_LINK_SHIFT) & SYSCTL_AFFILIATE_SET_LINK_MASK)
#define SYSCTL_AFFILIATE_SET_LINK_GET(x) (((uint32_t)(x) & SYSCTL_AFFILIATE_SET_LINK_MASK) >> SYSCTL_AFFILIATE_SET_LINK_SHIFT)

/* Bitfield definition for register of struct array AFFILIATE: CLEAR */
/*
 * LINK (RW)
 *
 * Affiliate groups of cpu0
 * bit0: cpu0 depends on logic node0
 * bit1: cpu0 depends on logic node1
 * bit2: cpu0 depends on logic node2
 * bit3: cpu0 depends on logic node3
 */
#define SYSCTL_AFFILIATE_CLEAR_LINK_MASK (0xFU)
#define SYSCTL_AFFILIATE_CLEAR_LINK_SHIFT (0U)
#define SYSCTL_AFFILIATE_CLEAR_LINK_SET(x) (((uint32_t)(x) << SYSCTL_AFFILIATE_CLEAR_LINK_SHIFT) & SYSCTL_AFFILIATE_CLEAR_LINK_MASK)
#define SYSCTL_AFFILIATE_CLEAR_LINK_GET(x) (((uint32_t)(x) & SYSCTL_AFFILIATE_CLEAR_LINK_MASK) >> SYSCTL_AFFILIATE_CLEAR_LINK_SHIFT)

/* Bitfield definition for register of struct array AFFILIATE: TOGGLE */
/*
 * LINK (RW)
 *
 * Affiliate groups of cpu0
 * bit0: cpu0 depends on logic node0
 * bit1: cpu0 depends on logic node1
 * bit2: cpu0 depends on logic node2
 * bit3: cpu0 depends on logic node3
 */
#define SYSCTL_AFFILIATE_TOGGLE_LINK_MASK (0xFU)
#define SYSCTL_AFFILIATE_TOGGLE_LINK_SHIFT (0U)
#define SYSCTL_AFFILIATE_TOGGLE_LINK_SET(x) (((uint32_t)(x) << SYSCTL_AFFILIATE_TOGGLE_LINK_SHIFT) & SYSCTL_AFFILIATE_TOGGLE_LINK_MASK)
#define SYSCTL_AFFILIATE_TOGGLE_LINK_GET(x) (((uint32_t)(x) & SYSCTL_AFFILIATE_TOGGLE_LINK_MASK) >> SYSCTL_AFFILIATE_TOGGLE_LINK_SHIFT)

/* Bitfield definition for register of struct array RETENTION: VALUE */
/*
 * LINK (RW)
 *
 * retention setting while system sleep, each bit represents a resource
 * bit0: soc_pow
 * bit1: soc_rst
 * bit2: cpu0_pow
 * bit3: cpu0_rst
 * bit4: cpu1_pow
 * bit5: cpu1_rst
 * bit6: con_pow
 * bit7: con_rst
 * bit8: vis_pow
 * bit9: vis_rst
 * bit10: xtal
 * bit11: pll0
 * bit12: pll1
 * bit13: pll2
 * bit14: pll3
 * bit15: pll4
 */
#define SYSCTL_RETENTION_VALUE_LINK_MASK (0x3FFFFUL)
#define SYSCTL_RETENTION_VALUE_LINK_SHIFT (0U)
#define SYSCTL_RETENTION_VALUE_LINK_SET(x) (((uint32_t)(x) << SYSCTL_RETENTION_VALUE_LINK_SHIFT) & SYSCTL_RETENTION_VALUE_LINK_MASK)
#define SYSCTL_RETENTION_VALUE_LINK_GET(x) (((uint32_t)(x) & SYSCTL_RETENTION_VALUE_LINK_MASK) >> SYSCTL_RETENTION_VALUE_LINK_SHIFT)

/* Bitfield definition for register of struct array RETENTION: SET */
/*
 * LINK (RW)
 *
 * retention setting while system sleep
 */
#define SYSCTL_RETENTION_SET_LINK_MASK (0x3FFFFUL)
#define SYSCTL_RETENTION_SET_LINK_SHIFT (0U)
#define SYSCTL_RETENTION_SET_LINK_SET(x) (((uint32_t)(x) << SYSCTL_RETENTION_SET_LINK_SHIFT) & SYSCTL_RETENTION_SET_LINK_MASK)
#define SYSCTL_RETENTION_SET_LINK_GET(x) (((uint32_t)(x) & SYSCTL_RETENTION_SET_LINK_MASK) >> SYSCTL_RETENTION_SET_LINK_SHIFT)

/* Bitfield definition for register of struct array RETENTION: CLEAR */
/*
 * LINK (RW)
 *
 * retention setting while system  sleep
 */
#define SYSCTL_RETENTION_CLEAR_LINK_MASK (0x3FFFFUL)
#define SYSCTL_RETENTION_CLEAR_LINK_SHIFT (0U)
#define SYSCTL_RETENTION_CLEAR_LINK_SET(x) (((uint32_t)(x) << SYSCTL_RETENTION_CLEAR_LINK_SHIFT) & SYSCTL_RETENTION_CLEAR_LINK_MASK)
#define SYSCTL_RETENTION_CLEAR_LINK_GET(x) (((uint32_t)(x) & SYSCTL_RETENTION_CLEAR_LINK_MASK) >> SYSCTL_RETENTION_CLEAR_LINK_SHIFT)

/* Bitfield definition for register of struct array RETENTION: TOGGLE */
/*
 * LINK (RW)
 *
 * retention setting while system  sleep
 */
#define SYSCTL_RETENTION_TOGGLE_LINK_MASK (0x3FFFFUL)
#define SYSCTL_RETENTION_TOGGLE_LINK_SHIFT (0U)
#define SYSCTL_RETENTION_TOGGLE_LINK_SET(x) (((uint32_t)(x) << SYSCTL_RETENTION_TOGGLE_LINK_SHIFT) & SYSCTL_RETENTION_TOGGLE_LINK_MASK)
#define SYSCTL_RETENTION_TOGGLE_LINK_GET(x) (((uint32_t)(x) & SYSCTL_RETENTION_TOGGLE_LINK_MASK) >> SYSCTL_RETENTION_TOGGLE_LINK_SHIFT)

/* Bitfield definition for register of struct array POWER: STATUS */
/*
 * FLAG (RW)
 *
 * flag represents power cycle happened from last clear of this bit
 * 0: power domain did not edurance power cycle since last clear of this bit
 * 1: power domain enduranced power cycle since last clear of this bit
 */
#define SYSCTL_POWER_STATUS_FLAG_MASK (0x80000000UL)
#define SYSCTL_POWER_STATUS_FLAG_SHIFT (31U)
#define SYSCTL_POWER_STATUS_FLAG_SET(x) (((uint32_t)(x) << SYSCTL_POWER_STATUS_FLAG_SHIFT) & SYSCTL_POWER_STATUS_FLAG_MASK)
#define SYSCTL_POWER_STATUS_FLAG_GET(x) (((uint32_t)(x) & SYSCTL_POWER_STATUS_FLAG_MASK) >> SYSCTL_POWER_STATUS_FLAG_SHIFT)

/*
 * FLAG_WAKE (RW)
 *
 * flag represents wakeup power cycle happened from last clear of this bit
 * 0: power domain did not edurance wakeup power cycle since last clear of this bit
 * 1: power domain enduranced wakeup power cycle since last clear of this bit
 */
#define SYSCTL_POWER_STATUS_FLAG_WAKE_MASK (0x40000000UL)
#define SYSCTL_POWER_STATUS_FLAG_WAKE_SHIFT (30U)
#define SYSCTL_POWER_STATUS_FLAG_WAKE_SET(x) (((uint32_t)(x) << SYSCTL_POWER_STATUS_FLAG_WAKE_SHIFT) & SYSCTL_POWER_STATUS_FLAG_WAKE_MASK)
#define SYSCTL_POWER_STATUS_FLAG_WAKE_GET(x) (((uint32_t)(x) & SYSCTL_POWER_STATUS_FLAG_WAKE_MASK) >> SYSCTL_POWER_STATUS_FLAG_WAKE_SHIFT)

/*
 * LF_DISABLE (RO)
 *
 * low fanout power switch disable
 * 0: low fanout power switches are turned on
 * 1: low fanout power switches are truned off
 */
#define SYSCTL_POWER_STATUS_LF_DISABLE_MASK (0x1000U)
#define SYSCTL_POWER_STATUS_LF_DISABLE_SHIFT (12U)
#define SYSCTL_POWER_STATUS_LF_DISABLE_GET(x) (((uint32_t)(x) & SYSCTL_POWER_STATUS_LF_DISABLE_MASK) >> SYSCTL_POWER_STATUS_LF_DISABLE_SHIFT)

/*
 * LF_ACK (RO)
 *
 * low fanout power switch feedback
 * 0: low fanout power switches are turned on
 * 1: low fanout power switches are truned off
 */
#define SYSCTL_POWER_STATUS_LF_ACK_MASK (0x100U)
#define SYSCTL_POWER_STATUS_LF_ACK_SHIFT (8U)
#define SYSCTL_POWER_STATUS_LF_ACK_GET(x) (((uint32_t)(x) & SYSCTL_POWER_STATUS_LF_ACK_MASK) >> SYSCTL_POWER_STATUS_LF_ACK_SHIFT)

/* Bitfield definition for register of struct array POWER: LF_WAIT */
/*
 * WAIT (RW)
 *
 * wait time for low fan out power switch turn on, default value is 255
 * 0: 0 clock cycle
 * 1: 1 clock cycles
 * . . .
 * clock cycles count on 24MHz
 */
#define SYSCTL_POWER_LF_WAIT_WAIT_MASK (0xFFFFFUL)
#define SYSCTL_POWER_LF_WAIT_WAIT_SHIFT (0U)
#define SYSCTL_POWER_LF_WAIT_WAIT_SET(x) (((uint32_t)(x) << SYSCTL_POWER_LF_WAIT_WAIT_SHIFT) & SYSCTL_POWER_LF_WAIT_WAIT_MASK)
#define SYSCTL_POWER_LF_WAIT_WAIT_GET(x) (((uint32_t)(x) & SYSCTL_POWER_LF_WAIT_WAIT_MASK) >> SYSCTL_POWER_LF_WAIT_WAIT_SHIFT)

/* Bitfield definition for register of struct array POWER: OFF_WAIT */
/*
 * WAIT (RW)
 *
 * wait time for power switch turn off, default value is 15
 * 0: 0 clock cycle
 * 1: 1 clock cycles
 * . . .
 * clock cycles count on 24MHz
 */
#define SYSCTL_POWER_OFF_WAIT_WAIT_MASK (0xFFFFFUL)
#define SYSCTL_POWER_OFF_WAIT_WAIT_SHIFT (0U)
#define SYSCTL_POWER_OFF_WAIT_WAIT_SET(x) (((uint32_t)(x) << SYSCTL_POWER_OFF_WAIT_WAIT_SHIFT) & SYSCTL_POWER_OFF_WAIT_WAIT_MASK)
#define SYSCTL_POWER_OFF_WAIT_WAIT_GET(x) (((uint32_t)(x) & SYSCTL_POWER_OFF_WAIT_WAIT_MASK) >> SYSCTL_POWER_OFF_WAIT_WAIT_SHIFT)

/* Bitfield definition for register of struct array RESET: CONTROL */
/*
 * FLAG (RW)
 *
 * flag represents reset happened from last clear of this bit
 * 0: domain did not edurance reset cycle since last clear of this bit
 * 1:  domain enduranced reset cycle since last clear of this bit
 */
#define SYSCTL_RESET_CONTROL_FLAG_MASK (0x80000000UL)
#define SYSCTL_RESET_CONTROL_FLAG_SHIFT (31U)
#define SYSCTL_RESET_CONTROL_FLAG_SET(x) (((uint32_t)(x) << SYSCTL_RESET_CONTROL_FLAG_SHIFT) & SYSCTL_RESET_CONTROL_FLAG_MASK)
#define SYSCTL_RESET_CONTROL_FLAG_GET(x) (((uint32_t)(x) & SYSCTL_RESET_CONTROL_FLAG_MASK) >> SYSCTL_RESET_CONTROL_FLAG_SHIFT)

/*
 * FLAG_WAKE (RW)
 *
 * flag represents wakeup reset happened from last clear of this bit
 * 0: domain did not edurance wakeup reset cycle since last clear of this bit
 * 1:  domain enduranced wakeup reset cycle since last clear of this bit
 */
#define SYSCTL_RESET_CONTROL_FLAG_WAKE_MASK (0x40000000UL)
#define SYSCTL_RESET_CONTROL_FLAG_WAKE_SHIFT (30U)
#define SYSCTL_RESET_CONTROL_FLAG_WAKE_SET(x) (((uint32_t)(x) << SYSCTL_RESET_CONTROL_FLAG_WAKE_SHIFT) & SYSCTL_RESET_CONTROL_FLAG_WAKE_MASK)
#define SYSCTL_RESET_CONTROL_FLAG_WAKE_GET(x) (((uint32_t)(x) & SYSCTL_RESET_CONTROL_FLAG_WAKE_MASK) >> SYSCTL_RESET_CONTROL_FLAG_WAKE_SHIFT)

/*
 * HOLD (RW)
 *
 * perform reset and hold in reset, until ths bit cleared by software
 * 0: reset is released for function
 * 1: reset is assert and hold
 */
#define SYSCTL_RESET_CONTROL_HOLD_MASK (0x10U)
#define SYSCTL_RESET_CONTROL_HOLD_SHIFT (4U)
#define SYSCTL_RESET_CONTROL_HOLD_SET(x) (((uint32_t)(x) << SYSCTL_RESET_CONTROL_HOLD_SHIFT) & SYSCTL_RESET_CONTROL_HOLD_MASK)
#define SYSCTL_RESET_CONTROL_HOLD_GET(x) (((uint32_t)(x) & SYSCTL_RESET_CONTROL_HOLD_MASK) >> SYSCTL_RESET_CONTROL_HOLD_SHIFT)

/*
 * RESET (RW)
 *
 * perform reset and release imediately
 * 0: reset is released
 * 1 reset is asserted and will release automatically
 */
#define SYSCTL_RESET_CONTROL_RESET_MASK (0x1U)
#define SYSCTL_RESET_CONTROL_RESET_SHIFT (0U)
#define SYSCTL_RESET_CONTROL_RESET_SET(x) (((uint32_t)(x) << SYSCTL_RESET_CONTROL_RESET_SHIFT) & SYSCTL_RESET_CONTROL_RESET_MASK)
#define SYSCTL_RESET_CONTROL_RESET_GET(x) (((uint32_t)(x) & SYSCTL_RESET_CONTROL_RESET_MASK) >> SYSCTL_RESET_CONTROL_RESET_SHIFT)

/* Bitfield definition for register of struct array RESET: CONFIG */
/*
 * PRE_WAIT (RW)
 *
 * wait cycle numbers before assert reset
 * 0: wait 0 cycle
 * 1: wait 1 cycles
 * . . .
 * Note, clock cycle is base on 24M
 */
#define SYSCTL_RESET_CONFIG_PRE_WAIT_MASK (0xFF0000UL)
#define SYSCTL_RESET_CONFIG_PRE_WAIT_SHIFT (16U)
#define SYSCTL_RESET_CONFIG_PRE_WAIT_SET(x) (((uint32_t)(x) << SYSCTL_RESET_CONFIG_PRE_WAIT_SHIFT) & SYSCTL_RESET_CONFIG_PRE_WAIT_MASK)
#define SYSCTL_RESET_CONFIG_PRE_WAIT_GET(x) (((uint32_t)(x) & SYSCTL_RESET_CONFIG_PRE_WAIT_MASK) >> SYSCTL_RESET_CONFIG_PRE_WAIT_SHIFT)

/*
 * RSTCLK_NUM (RW)
 *
 * reset clock number(must be even number)
 * 0: 0 cycle
 * 1: 0 cycles
 * 2: 2 cycles
 * 3: 2 cycles
 * . . .
 * Note, clock cycle is base on 24M
 */
#define SYSCTL_RESET_CONFIG_RSTCLK_NUM_MASK (0xFF00U)
#define SYSCTL_RESET_CONFIG_RSTCLK_NUM_SHIFT (8U)
#define SYSCTL_RESET_CONFIG_RSTCLK_NUM_SET(x) (((uint32_t)(x) << SYSCTL_RESET_CONFIG_RSTCLK_NUM_SHIFT) & SYSCTL_RESET_CONFIG_RSTCLK_NUM_MASK)
#define SYSCTL_RESET_CONFIG_RSTCLK_NUM_GET(x) (((uint32_t)(x) & SYSCTL_RESET_CONFIG_RSTCLK_NUM_MASK) >> SYSCTL_RESET_CONFIG_RSTCLK_NUM_SHIFT)

/*
 * POST_WAIT (RW)
 *
 * time guard band for  reset release
 * 0: wait 0 cycle
 * 1: wait 1 cycles
 * . . .
 * Note, clock cycle is base on 24M
 */
#define SYSCTL_RESET_CONFIG_POST_WAIT_MASK (0xFFU)
#define SYSCTL_RESET_CONFIG_POST_WAIT_SHIFT (0U)
#define SYSCTL_RESET_CONFIG_POST_WAIT_SET(x) (((uint32_t)(x) << SYSCTL_RESET_CONFIG_POST_WAIT_SHIFT) & SYSCTL_RESET_CONFIG_POST_WAIT_MASK)
#define SYSCTL_RESET_CONFIG_POST_WAIT_GET(x) (((uint32_t)(x) & SYSCTL_RESET_CONFIG_POST_WAIT_MASK) >> SYSCTL_RESET_CONFIG_POST_WAIT_SHIFT)

/* Bitfield definition for register of struct array RESET: COUNTER */
/*
 * COUNTER (RW)
 *
 * self clear trigger counter, reset triggered when counter value is 1, write 0 will cancel reset
 * 0: wait 0 cycle
 * 1: wait 1 cycles
 * . . .
 * Note, clock cycle is base on 24M
 */
#define SYSCTL_RESET_COUNTER_COUNTER_MASK (0xFFFFFUL)
#define SYSCTL_RESET_COUNTER_COUNTER_SHIFT (0U)
#define SYSCTL_RESET_COUNTER_COUNTER_SET(x) (((uint32_t)(x) << SYSCTL_RESET_COUNTER_COUNTER_SHIFT) & SYSCTL_RESET_COUNTER_COUNTER_MASK)
#define SYSCTL_RESET_COUNTER_COUNTER_GET(x) (((uint32_t)(x) & SYSCTL_RESET_COUNTER_COUNTER_MASK) >> SYSCTL_RESET_COUNTER_COUNTER_SHIFT)

/* Bitfield definition for register array: CLOCK */
/*
 * GLB_BUSY (RO)
 *
 * global busy
 * 0: no changes pending to any clock
 * 1: any of nodes is changing status
 */
#define SYSCTL_CLOCK_GLB_BUSY_MASK (0x80000000UL)
#define SYSCTL_CLOCK_GLB_BUSY_SHIFT (31U)
#define SYSCTL_CLOCK_GLB_BUSY_GET(x) (((uint32_t)(x) & SYSCTL_CLOCK_GLB_BUSY_MASK) >> SYSCTL_CLOCK_GLB_BUSY_SHIFT)

/*
 * LOC_BUSY (RO)
 *
 * local busy
 * 0: a change is pending for current node
 * 1: current node is changing status
 */
#define SYSCTL_CLOCK_LOC_BUSY_MASK (0x40000000UL)
#define SYSCTL_CLOCK_LOC_BUSY_SHIFT (30U)
#define SYSCTL_CLOCK_LOC_BUSY_GET(x) (((uint32_t)(x) & SYSCTL_CLOCK_LOC_BUSY_MASK) >> SYSCTL_CLOCK_LOC_BUSY_SHIFT)

/*
 * MUX (RW)
 *
 * clock source selection
 * 0:osc0_clk0
 * 1:pll0_clk0
 * 2:pll1_clk0
 * 3:pll1_clk1
 * 4:pll2_clk0
 * 5:pll2_clk1
 * 6:pll3_clk0
 * 7:pll4_clk0
 */
#define SYSCTL_CLOCK_MUX_MASK (0xF00U)
#define SYSCTL_CLOCK_MUX_SHIFT (8U)
#define SYSCTL_CLOCK_MUX_SET(x) (((uint32_t)(x) << SYSCTL_CLOCK_MUX_SHIFT) & SYSCTL_CLOCK_MUX_MASK)
#define SYSCTL_CLOCK_MUX_GET(x) (((uint32_t)(x) & SYSCTL_CLOCK_MUX_MASK) >> SYSCTL_CLOCK_MUX_SHIFT)

/*
 * DIV (RW)
 *
 * clock divider
 * 0: divider by1
 * 1: divider by 2
 * 2 divider by 3
 * . . .
 * 255: divider by 256
 */
#define SYSCTL_CLOCK_DIV_MASK (0xFFU)
#define SYSCTL_CLOCK_DIV_SHIFT (0U)
#define SYSCTL_CLOCK_DIV_SET(x) (((uint32_t)(x) << SYSCTL_CLOCK_DIV_SHIFT) & SYSCTL_CLOCK_DIV_MASK)
#define SYSCTL_CLOCK_DIV_GET(x) (((uint32_t)(x) & SYSCTL_CLOCK_DIV_MASK) >> SYSCTL_CLOCK_DIV_SHIFT)

/* Bitfield definition for register array: ADCCLK */
/*
 * GLB_BUSY (RO)
 *
 * global busy
 * 0: no changes pending to any clock
 * 1: any of nodes is changing status
 */
#define SYSCTL_ADCCLK_GLB_BUSY_MASK (0x80000000UL)
#define SYSCTL_ADCCLK_GLB_BUSY_SHIFT (31U)
#define SYSCTL_ADCCLK_GLB_BUSY_GET(x) (((uint32_t)(x) & SYSCTL_ADCCLK_GLB_BUSY_MASK) >> SYSCTL_ADCCLK_GLB_BUSY_SHIFT)

/*
 * LOC_BUSY (RO)
 *
 * local busy
 * 0: a change is pending for current node
 * 1: current node is changing status
 */
#define SYSCTL_ADCCLK_LOC_BUSY_MASK (0x40000000UL)
#define SYSCTL_ADCCLK_LOC_BUSY_SHIFT (30U)
#define SYSCTL_ADCCLK_LOC_BUSY_GET(x) (((uint32_t)(x) & SYSCTL_ADCCLK_LOC_BUSY_MASK) >> SYSCTL_ADCCLK_LOC_BUSY_SHIFT)

/*
 * MUX (RW)
 *
 * clock source selection
 * 0: ahb clock
 * 1: adc clock 0
 * 2: adc clock 1
 * 3: adc clock 2
 */
#define SYSCTL_ADCCLK_MUX_MASK (0x700U)
#define SYSCTL_ADCCLK_MUX_SHIFT (8U)
#define SYSCTL_ADCCLK_MUX_SET(x) (((uint32_t)(x) << SYSCTL_ADCCLK_MUX_SHIFT) & SYSCTL_ADCCLK_MUX_MASK)
#define SYSCTL_ADCCLK_MUX_GET(x) (((uint32_t)(x) & SYSCTL_ADCCLK_MUX_MASK) >> SYSCTL_ADCCLK_MUX_SHIFT)

/* Bitfield definition for register array: I2SCLK */
/*
 * GLB_BUSY (RO)
 *
 * global busy
 * 0: no changes pending to any clock
 * 1: any of nodes is changing status
 */
#define SYSCTL_I2SCLK_GLB_BUSY_MASK (0x80000000UL)
#define SYSCTL_I2SCLK_GLB_BUSY_SHIFT (31U)
#define SYSCTL_I2SCLK_GLB_BUSY_GET(x) (((uint32_t)(x) & SYSCTL_I2SCLK_GLB_BUSY_MASK) >> SYSCTL_I2SCLK_GLB_BUSY_SHIFT)

/*
 * LOC_BUSY (RO)
 *
 * local busy
 * 0: a change is pending for current node
 * 1: current node is changing status
 */
#define SYSCTL_I2SCLK_LOC_BUSY_MASK (0x40000000UL)
#define SYSCTL_I2SCLK_LOC_BUSY_SHIFT (30U)
#define SYSCTL_I2SCLK_LOC_BUSY_GET(x) (((uint32_t)(x) & SYSCTL_I2SCLK_LOC_BUSY_MASK) >> SYSCTL_I2SCLK_LOC_BUSY_SHIFT)

/*
 * MUX (RW)
 *
 * clock source selection
 * 0: ahb clock
 * 1: i2s clock 0
 * 2: i2s clock 1
 * 3: i2s clock 2
 */
#define SYSCTL_I2SCLK_MUX_MASK (0x700U)
#define SYSCTL_I2SCLK_MUX_SHIFT (8U)
#define SYSCTL_I2SCLK_MUX_SET(x) (((uint32_t)(x) << SYSCTL_I2SCLK_MUX_SHIFT) & SYSCTL_I2SCLK_MUX_MASK)
#define SYSCTL_I2SCLK_MUX_GET(x) (((uint32_t)(x) & SYSCTL_I2SCLK_MUX_MASK) >> SYSCTL_I2SCLK_MUX_SHIFT)

/* Bitfield definition for register: GLOBAL00 */
/*
 * PRESET (RW)
 *
 * global clock override request
 * bit0: override to preset0
 * bit1: override to preset1
 * bit2: override to preset2
 * bit3: override to preset3
 */
#define SYSCTL_GLOBAL00_PRESET_MASK (0xFU)
#define SYSCTL_GLOBAL00_PRESET_SHIFT (0U)
#define SYSCTL_GLOBAL00_PRESET_SET(x) (((uint32_t)(x) << SYSCTL_GLOBAL00_PRESET_SHIFT) & SYSCTL_GLOBAL00_PRESET_MASK)
#define SYSCTL_GLOBAL00_PRESET_GET(x) (((uint32_t)(x) & SYSCTL_GLOBAL00_PRESET_MASK) >> SYSCTL_GLOBAL00_PRESET_SHIFT)

/* Bitfield definition for register of struct array MONITOR: CONTROL */
/*
 * VALID (RW)
 *
 * result is ready for read
 * 0: not ready
 * 1: result is ready
 */
#define SYSCTL_MONITOR_CONTROL_VALID_MASK (0x80000000UL)
#define SYSCTL_MONITOR_CONTROL_VALID_SHIFT (31U)
#define SYSCTL_MONITOR_CONTROL_VALID_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_CONTROL_VALID_SHIFT) & SYSCTL_MONITOR_CONTROL_VALID_MASK)
#define SYSCTL_MONITOR_CONTROL_VALID_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CONTROL_VALID_MASK) >> SYSCTL_MONITOR_CONTROL_VALID_SHIFT)

/*
 * DIV_BUSY (RO)
 *
 * divider is applying new setting
 */
#define SYSCTL_MONITOR_CONTROL_DIV_BUSY_MASK (0x8000000UL)
#define SYSCTL_MONITOR_CONTROL_DIV_BUSY_SHIFT (27U)
#define SYSCTL_MONITOR_CONTROL_DIV_BUSY_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CONTROL_DIV_BUSY_MASK) >> SYSCTL_MONITOR_CONTROL_DIV_BUSY_SHIFT)

/*
 * OUTEN (RW)
 *
 * enable clock output
 */
#define SYSCTL_MONITOR_CONTROL_OUTEN_MASK (0x1000000UL)
#define SYSCTL_MONITOR_CONTROL_OUTEN_SHIFT (24U)
#define SYSCTL_MONITOR_CONTROL_OUTEN_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_CONTROL_OUTEN_SHIFT) & SYSCTL_MONITOR_CONTROL_OUTEN_MASK)
#define SYSCTL_MONITOR_CONTROL_OUTEN_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CONTROL_OUTEN_MASK) >> SYSCTL_MONITOR_CONTROL_OUTEN_SHIFT)

/*
 * DIV (RW)
 *
 * output divider
 */
#define SYSCTL_MONITOR_CONTROL_DIV_MASK (0xFF0000UL)
#define SYSCTL_MONITOR_CONTROL_DIV_SHIFT (16U)
#define SYSCTL_MONITOR_CONTROL_DIV_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_CONTROL_DIV_SHIFT) & SYSCTL_MONITOR_CONTROL_DIV_MASK)
#define SYSCTL_MONITOR_CONTROL_DIV_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CONTROL_DIV_MASK) >> SYSCTL_MONITOR_CONTROL_DIV_SHIFT)

/*
 * HIGH (RW)
 *
 * clock frequency higher than upper limit
 */
#define SYSCTL_MONITOR_CONTROL_HIGH_MASK (0x8000U)
#define SYSCTL_MONITOR_CONTROL_HIGH_SHIFT (15U)
#define SYSCTL_MONITOR_CONTROL_HIGH_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_CONTROL_HIGH_SHIFT) & SYSCTL_MONITOR_CONTROL_HIGH_MASK)
#define SYSCTL_MONITOR_CONTROL_HIGH_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CONTROL_HIGH_MASK) >> SYSCTL_MONITOR_CONTROL_HIGH_SHIFT)

/*
 * LOW (RW)
 *
 * clock frequency lower than lower limit
 */
#define SYSCTL_MONITOR_CONTROL_LOW_MASK (0x4000U)
#define SYSCTL_MONITOR_CONTROL_LOW_SHIFT (14U)
#define SYSCTL_MONITOR_CONTROL_LOW_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_CONTROL_LOW_SHIFT) & SYSCTL_MONITOR_CONTROL_LOW_MASK)
#define SYSCTL_MONITOR_CONTROL_LOW_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CONTROL_LOW_MASK) >> SYSCTL_MONITOR_CONTROL_LOW_SHIFT)

/*
 * START (RW)
 *
 * start measurement
 */
#define SYSCTL_MONITOR_CONTROL_START_MASK (0x1000U)
#define SYSCTL_MONITOR_CONTROL_START_SHIFT (12U)
#define SYSCTL_MONITOR_CONTROL_START_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_CONTROL_START_SHIFT) & SYSCTL_MONITOR_CONTROL_START_MASK)
#define SYSCTL_MONITOR_CONTROL_START_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CONTROL_START_MASK) >> SYSCTL_MONITOR_CONTROL_START_SHIFT)

/*
 * MODE (RW)
 *
 * work mode,
 * 0: register value will be compared to measurement
 * 1: upper and lower value will be recordered in register
 */
#define SYSCTL_MONITOR_CONTROL_MODE_MASK (0x400U)
#define SYSCTL_MONITOR_CONTROL_MODE_SHIFT (10U)
#define SYSCTL_MONITOR_CONTROL_MODE_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_CONTROL_MODE_SHIFT) & SYSCTL_MONITOR_CONTROL_MODE_MASK)
#define SYSCTL_MONITOR_CONTROL_MODE_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CONTROL_MODE_MASK) >> SYSCTL_MONITOR_CONTROL_MODE_SHIFT)

/*
 * ACCURACY (RW)
 *
 * measurement accuracy,
 * 0: resolution is 1kHz
 * 1: resolution is 1Hz
 */
#define SYSCTL_MONITOR_CONTROL_ACCURACY_MASK (0x200U)
#define SYSCTL_MONITOR_CONTROL_ACCURACY_SHIFT (9U)
#define SYSCTL_MONITOR_CONTROL_ACCURACY_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_CONTROL_ACCURACY_SHIFT) & SYSCTL_MONITOR_CONTROL_ACCURACY_MASK)
#define SYSCTL_MONITOR_CONTROL_ACCURACY_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CONTROL_ACCURACY_MASK) >> SYSCTL_MONITOR_CONTROL_ACCURACY_SHIFT)

/*
 * REFERENCE (RW)
 *
 * reference clock selection,
 * 0: 32k
 * 1: 24M
 */
#define SYSCTL_MONITOR_CONTROL_REFERENCE_MASK (0x100U)
#define SYSCTL_MONITOR_CONTROL_REFERENCE_SHIFT (8U)
#define SYSCTL_MONITOR_CONTROL_REFERENCE_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_CONTROL_REFERENCE_SHIFT) & SYSCTL_MONITOR_CONTROL_REFERENCE_MASK)
#define SYSCTL_MONITOR_CONTROL_REFERENCE_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CONTROL_REFERENCE_MASK) >> SYSCTL_MONITOR_CONTROL_REFERENCE_SHIFT)

/*
 * SELECTION (RW)
 *
 * clock measurement selection
 */
#define SYSCTL_MONITOR_CONTROL_SELECTION_MASK (0xFFU)
#define SYSCTL_MONITOR_CONTROL_SELECTION_SHIFT (0U)
#define SYSCTL_MONITOR_CONTROL_SELECTION_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_CONTROL_SELECTION_SHIFT) & SYSCTL_MONITOR_CONTROL_SELECTION_MASK)
#define SYSCTL_MONITOR_CONTROL_SELECTION_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CONTROL_SELECTION_MASK) >> SYSCTL_MONITOR_CONTROL_SELECTION_SHIFT)

/* Bitfield definition for register of struct array MONITOR: CURRENT */
/*
 * FREQUENCY (RO)
 *
 * self updating measure result
 */
#define SYSCTL_MONITOR_CURRENT_FREQUENCY_MASK (0xFFFFFFFFUL)
#define SYSCTL_MONITOR_CURRENT_FREQUENCY_SHIFT (0U)
#define SYSCTL_MONITOR_CURRENT_FREQUENCY_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_CURRENT_FREQUENCY_MASK) >> SYSCTL_MONITOR_CURRENT_FREQUENCY_SHIFT)

/* Bitfield definition for register of struct array MONITOR: LOW_LIMIT */
/*
 * FREQUENCY (RW)
 *
 * lower frequency
 */
#define SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_MASK (0xFFFFFFFFUL)
#define SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_SHIFT (0U)
#define SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_SHIFT) & SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_MASK)
#define SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_MASK) >> SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_SHIFT)

/* Bitfield definition for register of struct array MONITOR: HIGH_LIMIT */
/*
 * FREQUENCY (RW)
 *
 * upper frequency
 */
#define SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_MASK (0xFFFFFFFFUL)
#define SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_SHIFT (0U)
#define SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_SET(x) (((uint32_t)(x) << SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_SHIFT) & SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_MASK)
#define SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_GET(x) (((uint32_t)(x) & SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_MASK) >> SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_SHIFT)

/* Bitfield definition for register of struct array CPU: LP */
/*
 * WAKE_CNT (RW)
 *
 * CPU0 wake up counter, counter saturated at 255, write 0x00 to clear
 */
#define SYSCTL_CPU_LP_WAKE_CNT_MASK (0xFF000000UL)
#define SYSCTL_CPU_LP_WAKE_CNT_SHIFT (24U)
#define SYSCTL_CPU_LP_WAKE_CNT_SET(x) (((uint32_t)(x) << SYSCTL_CPU_LP_WAKE_CNT_SHIFT) & SYSCTL_CPU_LP_WAKE_CNT_MASK)
#define SYSCTL_CPU_LP_WAKE_CNT_GET(x) (((uint32_t)(x) & SYSCTL_CPU_LP_WAKE_CNT_MASK) >> SYSCTL_CPU_LP_WAKE_CNT_SHIFT)

/*
 * HALT (RW)
 *
 * halt request for CPU0,
 * 0: CPU0 will start to execute after reset or receive wakeup request
 * 1: CPU0 will not start after reset, or wakeup after WFI
 */
#define SYSCTL_CPU_LP_HALT_MASK (0x10000UL)
#define SYSCTL_CPU_LP_HALT_SHIFT (16U)
#define SYSCTL_CPU_LP_HALT_SET(x) (((uint32_t)(x) << SYSCTL_CPU_LP_HALT_SHIFT) & SYSCTL_CPU_LP_HALT_MASK)
#define SYSCTL_CPU_LP_HALT_GET(x) (((uint32_t)(x) & SYSCTL_CPU_LP_HALT_MASK) >> SYSCTL_CPU_LP_HALT_SHIFT)

/*
 * WAKE (RO)
 *
 * CPU0 is waking up
 * 0: CPU0 wake up not asserted
 * 1: CPU0 wake up asserted
 */
#define SYSCTL_CPU_LP_WAKE_MASK (0x2000U)
#define SYSCTL_CPU_LP_WAKE_SHIFT (13U)
#define SYSCTL_CPU_LP_WAKE_GET(x) (((uint32_t)(x) & SYSCTL_CPU_LP_WAKE_MASK) >> SYSCTL_CPU_LP_WAKE_SHIFT)

/*
 * EXEC (RO)
 *
 * CPU0 is executing
 * 0: CPU0 is not executing
 * 1: CPU0 is executing
 */
#define SYSCTL_CPU_LP_EXEC_MASK (0x1000U)
#define SYSCTL_CPU_LP_EXEC_SHIFT (12U)
#define SYSCTL_CPU_LP_EXEC_GET(x) (((uint32_t)(x) & SYSCTL_CPU_LP_EXEC_MASK) >> SYSCTL_CPU_LP_EXEC_SHIFT)

/*
 * WAKE_FLAG (RW)
 *
 * CPU0 wakeup flag, indicate a wakeup event got active, write 1 to clear this bit
 * 0: CPU0 wakeup not happened
 * 1: CPU0 wakeup happened
 */
#define SYSCTL_CPU_LP_WAKE_FLAG_MASK (0x400U)
#define SYSCTL_CPU_LP_WAKE_FLAG_SHIFT (10U)
#define SYSCTL_CPU_LP_WAKE_FLAG_SET(x) (((uint32_t)(x) << SYSCTL_CPU_LP_WAKE_FLAG_SHIFT) & SYSCTL_CPU_LP_WAKE_FLAG_MASK)
#define SYSCTL_CPU_LP_WAKE_FLAG_GET(x) (((uint32_t)(x) & SYSCTL_CPU_LP_WAKE_FLAG_MASK) >> SYSCTL_CPU_LP_WAKE_FLAG_SHIFT)

/*
 * SLEEP_FLAG (RW)
 *
 * CPU0 sleep flag, indicate a sleep event got active, write 1 to clear this bit
 * 0: CPU0 sleep not happened
 * 1: CPU0 sleep happened
 */
#define SYSCTL_CPU_LP_SLEEP_FLAG_MASK (0x200U)
#define SYSCTL_CPU_LP_SLEEP_FLAG_SHIFT (9U)
#define SYSCTL_CPU_LP_SLEEP_FLAG_SET(x) (((uint32_t)(x) << SYSCTL_CPU_LP_SLEEP_FLAG_SHIFT) & SYSCTL_CPU_LP_SLEEP_FLAG_MASK)
#define SYSCTL_CPU_LP_SLEEP_FLAG_GET(x) (((uint32_t)(x) & SYSCTL_CPU_LP_SLEEP_FLAG_MASK) >> SYSCTL_CPU_LP_SLEEP_FLAG_SHIFT)

/*
 * RESET_FLAG (RW)
 *
 * CPU0 reset flag, indicate a reset event got active, write 1 to clear this bit
 * 0: CPU0 sleep not happened
 * 1: CPU0 sleep happened
 */
#define SYSCTL_CPU_LP_RESET_FLAG_MASK (0x100U)
#define SYSCTL_CPU_LP_RESET_FLAG_SHIFT (8U)
#define SYSCTL_CPU_LP_RESET_FLAG_SET(x) (((uint32_t)(x) << SYSCTL_CPU_LP_RESET_FLAG_SHIFT) & SYSCTL_CPU_LP_RESET_FLAG_MASK)
#define SYSCTL_CPU_LP_RESET_FLAG_GET(x) (((uint32_t)(x) & SYSCTL_CPU_LP_RESET_FLAG_MASK) >> SYSCTL_CPU_LP_RESET_FLAG_SHIFT)

/*
 * MODE (RW)
 *
 * Low power mode, system behavior after WFI
 * 00: CPU clock stop after WFI
 * 01: System enter low power mode after WFI
 * 10: Keep running after WFI
 * 11: reserved
 */
#define SYSCTL_CPU_LP_MODE_MASK (0x3U)
#define SYSCTL_CPU_LP_MODE_SHIFT (0U)
#define SYSCTL_CPU_LP_MODE_SET(x) (((uint32_t)(x) << SYSCTL_CPU_LP_MODE_SHIFT) & SYSCTL_CPU_LP_MODE_MASK)
#define SYSCTL_CPU_LP_MODE_GET(x) (((uint32_t)(x) & SYSCTL_CPU_LP_MODE_MASK) >> SYSCTL_CPU_LP_MODE_SHIFT)

/* Bitfield definition for register of struct array CPU: LOCK */
/*
 * GPR (RW)
 *
 * Lock bit for CPU_DATA0 to CPU_DATA13, once set, this bit will not clear untile next reset
 */
#define SYSCTL_CPU_LOCK_GPR_MASK (0xFFFCU)
#define SYSCTL_CPU_LOCK_GPR_SHIFT (2U)
#define SYSCTL_CPU_LOCK_GPR_SET(x) (((uint32_t)(x) << SYSCTL_CPU_LOCK_GPR_SHIFT) & SYSCTL_CPU_LOCK_GPR_MASK)
#define SYSCTL_CPU_LOCK_GPR_GET(x) (((uint32_t)(x) & SYSCTL_CPU_LOCK_GPR_MASK) >> SYSCTL_CPU_LOCK_GPR_SHIFT)

/*
 * LOCK (RW)
 *
 * Lock bit for CPU_LOCK
 */
#define SYSCTL_CPU_LOCK_LOCK_MASK (0x2U)
#define SYSCTL_CPU_LOCK_LOCK_SHIFT (1U)
#define SYSCTL_CPU_LOCK_LOCK_SET(x) (((uint32_t)(x) << SYSCTL_CPU_LOCK_LOCK_SHIFT) & SYSCTL_CPU_LOCK_LOCK_MASK)
#define SYSCTL_CPU_LOCK_LOCK_GET(x) (((uint32_t)(x) & SYSCTL_CPU_LOCK_LOCK_MASK) >> SYSCTL_CPU_LOCK_LOCK_SHIFT)

/* Bitfield definition for register of struct array CPU: GPR0 */
/*
 * GPR (RW)
 *
 * register for software to handle resume, can save resume address or status
 */
#define SYSCTL_CPU_GPR_GPR_MASK (0xFFFFFFFFUL)
#define SYSCTL_CPU_GPR_GPR_SHIFT (0U)
#define SYSCTL_CPU_GPR_GPR_SET(x) (((uint32_t)(x) << SYSCTL_CPU_GPR_GPR_SHIFT) & SYSCTL_CPU_GPR_GPR_MASK)
#define SYSCTL_CPU_GPR_GPR_GET(x) (((uint32_t)(x) & SYSCTL_CPU_GPR_GPR_MASK) >> SYSCTL_CPU_GPR_GPR_SHIFT)

/* Bitfield definition for register of struct array CPU: STATUS0 */
/*
 * STATUS (RO)
 *
 * IRQ values
 */
#define SYSCTL_CPU_WAKEUP_STATUS_STATUS_MASK (0xFFFFFFFFUL)
#define SYSCTL_CPU_WAKEUP_STATUS_STATUS_SHIFT (0U)
#define SYSCTL_CPU_WAKEUP_STATUS_STATUS_GET(x) (((uint32_t)(x) & SYSCTL_CPU_WAKEUP_STATUS_STATUS_MASK) >> SYSCTL_CPU_WAKEUP_STATUS_STATUS_SHIFT)

/* Bitfield definition for register of struct array CPU: ENABLE0 */
/*
 * ENABLE (RW)
 *
 * IRQ wakeup enable
 */
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE_MASK (0xFFFFFFFFUL)
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE_SHIFT (0U)
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE_SET(x) (((uint32_t)(x) << SYSCTL_CPU_WAKEUP_ENABLE_ENABLE_SHIFT) & SYSCTL_CPU_WAKEUP_ENABLE_ENABLE_MASK)
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE_GET(x) (((uint32_t)(x) & SYSCTL_CPU_WAKEUP_ENABLE_ENABLE_MASK) >> SYSCTL_CPU_WAKEUP_ENABLE_ENABLE_SHIFT)



/* RESOURCE register group index macro definition */
#define SYSCTL_RESOURCE_CPU0_CORE (0UL)
#define SYSCTL_RESOURCE_CPU0_SUBSYS (1UL)
#define SYSCTL_RESOURCE_CPU1_CORE (8UL)
#define SYSCTL_RESOURCE_CPX1_SUBSYS (9UL)
#define SYSCTL_RESOURCE_POW_CON (21UL)
#define SYSCTL_RESOURCE_POW_VIS (22UL)
#define SYSCTL_RESOURCE_POW_CPU0 (23UL)
#define SYSCTL_RESOURCE_POW_CPU1 (24UL)
#define SYSCTL_RESOURCE_RST_SOC (25UL)
#define SYSCTL_RESOURCE_RST_CON (26UL)
#define SYSCTL_RESOURCE_RST_VIS (27UL)
#define SYSCTL_RESOURCE_RST_CPU0 (28UL)
#define SYSCTL_RESOURCE_RST_CPU1 (29UL)
#define SYSCTL_RESOURCE_CLK_SRC_XTAL (32UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL0 (33UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL0CLK0 (34UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL1 (35UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL1CLK0 (36UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL1CLK1 (37UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL2 (38UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL2CLK0 (39UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL2CLK1 (40UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL3 (41UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL3CLK0 (42UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL4 (43UL)
#define SYSCTL_RESOURCE_CLK_SRC_PLL4CLK0 (44UL)
#define SYSCTL_RESOURCE_CLK_TOP_CPU0 (64UL)
#define SYSCTL_RESOURCE_CLK_TOP_MCHTMR0 (65UL)
#define SYSCTL_RESOURCE_CLK_TOP_CPU1 (66UL)
#define SYSCTL_RESOURCE_CLK_TOP_MCHTMR1 (67UL)
#define SYSCTL_RESOURCE_CLK_TOP_AXI (68UL)
#define SYSCTL_RESOURCE_CLK_TOP_CONN (69UL)
#define SYSCTL_RESOURCE_CLK_TOP_VIS (70UL)
#define SYSCTL_RESOURCE_CLK_TOP_AHB (71UL)
#define SYSCTL_RESOURCE_CLK_TOP_FEMC (72UL)
#define SYSCTL_RESOURCE_CLK_TOP_XPI0 (73UL)
#define SYSCTL_RESOURCE_CLK_TOP_XPI1 (74UL)
#define SYSCTL_RESOURCE_CLK_TOP_GPTMR0 (75UL)
#define SYSCTL_RESOURCE_CLK_TOP_GPTMR1 (76UL)
#define SYSCTL_RESOURCE_CLK_TOP_GPTMR2 (77UL)
#define SYSCTL_RESOURCE_CLK_TOP_GPTMR3 (78UL)
#define SYSCTL_RESOURCE_CLK_TOP_GPTMR4 (79UL)
#define SYSCTL_RESOURCE_CLK_TOP_GPTMR5 (80UL)
#define SYSCTL_RESOURCE_CLK_TOP_GPTMR6 (81UL)
#define SYSCTL_RESOURCE_CLK_TOP_GPTMR7 (82UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART0 (83UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART1 (84UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART2 (85UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART3 (86UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART4 (87UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART5 (88UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART6 (89UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART7 (90UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART8 (91UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART9 (92UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART10 (93UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART11 (94UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART12 (95UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART13 (96UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART14 (97UL)
#define SYSCTL_RESOURCE_CLK_TOP_UART15 (98UL)
#define SYSCTL_RESOURCE_CLK_TOP_I2C0 (99UL)
#define SYSCTL_RESOURCE_CLK_TOP_I2C1 (100UL)
#define SYSCTL_RESOURCE_CLK_TOP_I2C2 (101UL)
#define SYSCTL_RESOURCE_CLK_TOP_I2C3 (102UL)
#define SYSCTL_RESOURCE_CLK_TOP_SPI0 (103UL)
#define SYSCTL_RESOURCE_CLK_TOP_SPI1 (104UL)
#define SYSCTL_RESOURCE_CLK_TOP_SPI2 (105UL)
#define SYSCTL_RESOURCE_CLK_TOP_SPI3 (106UL)
#define SYSCTL_RESOURCE_CLK_TOP_CAN0 (107UL)
#define SYSCTL_RESOURCE_CLK_TOP_CAN1 (108UL)
#define SYSCTL_RESOURCE_CLK_TOP_CAN2 (109UL)
#define SYSCTL_RESOURCE_CLK_TOP_CAN3 (110UL)
#define SYSCTL_RESOURCE_CLK_TOP_PTPC (111UL)
#define SYSCTL_RESOURCE_CLK_TOP_ANA0 (112UL)
#define SYSCTL_RESOURCE_CLK_TOP_ANA1 (113UL)
#define SYSCTL_RESOURCE_CLK_TOP_ANA2 (114UL)
#define SYSCTL_RESOURCE_CLK_TOP_AUD0 (115UL)
#define SYSCTL_RESOURCE_CLK_TOP_AUD1 (116UL)
#define SYSCTL_RESOURCE_CLK_TOP_AUD2 (117UL)
#define SYSCTL_RESOURCE_CLK_TOP_LCDC (118UL)
#define SYSCTL_RESOURCE_CLK_TOP_CAM0 (119UL)
#define SYSCTL_RESOURCE_CLK_TOP_CAM1 (120UL)
#define SYSCTL_RESOURCE_CLK_TOP_ENET0 (121UL)
#define SYSCTL_RESOURCE_CLK_TOP_ENET1 (122UL)
#define SYSCTL_RESOURCE_CLK_TOP_PTP0 (123UL)
#define SYSCTL_RESOURCE_CLK_TOP_PTP1 (124UL)
#define SYSCTL_RESOURCE_CLK_TOP_REF0 (125UL)
#define SYSCTL_RESOURCE_CLK_TOP_REF1 (126UL)
#define SYSCTL_RESOURCE_CLK_TOP_NTMR0 (127UL)
#define SYSCTL_RESOURCE_CLK_TOP_NTMR1 (128UL)
#define SYSCTL_RESOURCE_CLK_TOP_SDXC0 (129UL)
#define SYSCTL_RESOURCE_CLK_TOP_SDXC1 (130UL)
#define SYSCTL_RESOURCE_CLK_TOP_ADC0 (192UL)
#define SYSCTL_RESOURCE_CLK_TOP_ADC1 (193UL)
#define SYSCTL_RESOURCE_CLK_TOP_ADC2 (194UL)
#define SYSCTL_RESOURCE_CLK_TOP_ADC3 (195UL)
#define SYSCTL_RESOURCE_CLK_TOP_I2S0 (196UL)
#define SYSCTL_RESOURCE_CLK_TOP_I2S1 (197UL)
#define SYSCTL_RESOURCE_CLK_TOP_I2S2 (198UL)
#define SYSCTL_RESOURCE_CLK_TOP_I2S3 (199UL)
#define SYSCTL_RESOURCE_AHBAPB_BUS (256UL)
#define SYSCTL_RESOURCE_AXI_BUS (257UL)
#define SYSCTL_RESOURCE_CONN_BUS (258UL)
#define SYSCTL_RESOURCE_VIS_BUS (259UL)
#define SYSCTL_RESOURCE_FEMC (260UL)
#define SYSCTL_RESOURCE_ROM (261UL)
#define SYSCTL_RESOURCE_LMM0 (262UL)
#define SYSCTL_RESOURCE_LMM1 (263UL)
#define SYSCTL_RESOURCE_MCHTMR0 (264UL)
#define SYSCTL_RESOURCE_MCHTMR1 (265UL)
#define SYSCTL_RESOURCE_AXI_SRAM0 (266UL)
#define SYSCTL_RESOURCE_AXI_SRAM1 (267UL)
#define SYSCTL_RESOURCE_XPI0 (268UL)
#define SYSCTL_RESOURCE_XPI1 (269UL)
#define SYSCTL_RESOURCE_SDP (270UL)
#define SYSCTL_RESOURCE_RNG (271UL)
#define SYSCTL_RESOURCE_KEYM (272UL)
#define SYSCTL_RESOURCE_HDMA (273UL)
#define SYSCTL_RESOURCE_XDMA (274UL)
#define SYSCTL_RESOURCE_GPIO (275UL)
#define SYSCTL_RESOURCE_MBX0 (276UL)
#define SYSCTL_RESOURCE_MBX1 (277UL)
#define SYSCTL_RESOURCE_WDG0 (278UL)
#define SYSCTL_RESOURCE_WDG1 (279UL)
#define SYSCTL_RESOURCE_WDG2 (280UL)
#define SYSCTL_RESOURCE_WDG3 (281UL)
#define SYSCTL_RESOURCE_GPTMR0 (282UL)
#define SYSCTL_RESOURCE_GPTMR1 (283UL)
#define SYSCTL_RESOURCE_GPTMR2 (284UL)
#define SYSCTL_RESOURCE_GPTMR3 (285UL)
#define SYSCTL_RESOURCE_GPTMR4 (286UL)
#define SYSCTL_RESOURCE_GPTMR5 (287UL)
#define SYSCTL_RESOURCE_GPTMR6 (288UL)
#define SYSCTL_RESOURCE_GPTMR7 (289UL)
#define SYSCTL_RESOURCE_UART0 (290UL)
#define SYSCTL_RESOURCE_UART1 (291UL)
#define SYSCTL_RESOURCE_UART2 (292UL)
#define SYSCTL_RESOURCE_UART3 (293UL)
#define SYSCTL_RESOURCE_UART4 (294UL)
#define SYSCTL_RESOURCE_UART5 (295UL)
#define SYSCTL_RESOURCE_UART6 (296UL)
#define SYSCTL_RESOURCE_UART7 (297UL)
#define SYSCTL_RESOURCE_UART8 (298UL)
#define SYSCTL_RESOURCE_UART9 (299UL)
#define SYSCTL_RESOURCE_UART10 (300UL)
#define SYSCTL_RESOURCE_UART11 (301UL)
#define SYSCTL_RESOURCE_UART12 (302UL)
#define SYSCTL_RESOURCE_UART13 (303UL)
#define SYSCTL_RESOURCE_UART14 (304UL)
#define SYSCTL_RESOURCE_UART15 (305UL)
#define SYSCTL_RESOURCE_I2C0 (306UL)
#define SYSCTL_RESOURCE_I2C1 (307UL)
#define SYSCTL_RESOURCE_I2C2 (308UL)
#define SYSCTL_RESOURCE_I2C3 (309UL)
#define SYSCTL_RESOURCE_SPI0 (310UL)
#define SYSCTL_RESOURCE_SPI1 (311UL)
#define SYSCTL_RESOURCE_SPI2 (312UL)
#define SYSCTL_RESOURCE_SPI3 (313UL)
#define SYSCTL_RESOURCE_CAN0 (314UL)
#define SYSCTL_RESOURCE_CAN1 (315UL)
#define SYSCTL_RESOURCE_CAN2 (316UL)
#define SYSCTL_RESOURCE_CAN3 (317UL)
#define SYSCTL_RESOURCE_PTPC (318UL)
#define SYSCTL_RESOURCE_ADC0 (319UL)
#define SYSCTL_RESOURCE_ADC1 (320UL)
#define SYSCTL_RESOURCE_ADC2 (321UL)
#define SYSCTL_RESOURCE_ADC3 (322UL)
#define SYSCTL_RESOURCE_ACMP (323UL)
#define SYSCTL_RESOURCE_I2S0 (324UL)
#define SYSCTL_RESOURCE_I2S1 (325UL)
#define SYSCTL_RESOURCE_I2S2 (326UL)
#define SYSCTL_RESOURCE_I2S3 (327UL)
#define SYSCTL_RESOURCE_PDM (328UL)
#define SYSCTL_RESOURCE_DAO (329UL)
#define SYSCTL_RESOURCE_SYNT (330UL)
#define SYSCTL_RESOURCE_MOT0 (331UL)
#define SYSCTL_RESOURCE_MOT1 (332UL)
#define SYSCTL_RESOURCE_MOT2 (333UL)
#define SYSCTL_RESOURCE_MOT3 (334UL)
#define SYSCTL_RESOURCE_LCDC (335UL)
#define SYSCTL_RESOURCE_CAM0 (336UL)
#define SYSCTL_RESOURCE_CAM1 (337UL)
#define SYSCTL_RESOURCE_JPEG (338UL)
#define SYSCTL_RESOURCE_PDMA (339UL)
#define SYSCTL_RESOURCE_ENET0 (340UL)
#define SYSCTL_RESOURCE_ENET1 (341UL)
#define SYSCTL_RESOURCE_NTMR0 (342UL)
#define SYSCTL_RESOURCE_NTMR1 (343UL)
#define SYSCTL_RESOURCE_SDXC0 (344UL)
#define SYSCTL_RESOURCE_SDXC1 (345UL)
#define SYSCTL_RESOURCE_USB0 (346UL)
#define SYSCTL_RESOURCE_USB1 (347UL)
#define SYSCTL_RESOURCE_REF0 (348UL)
#define SYSCTL_RESOURCE_REF1 (349UL)

/* GROUP0 register group index macro definition */
#define SYSCTL_GROUP0_0 (0UL)
#define SYSCTL_GROUP0_1 (1UL)
#define SYSCTL_GROUP0_2 (2UL)

/* GROUP1 register group index macro definition */
#define SYSCTL_GROUP1_0 (0UL)
#define SYSCTL_GROUP1_1 (1UL)
#define SYSCTL_GROUP1_2 (2UL)

/* AFFILIATE register group index macro definition */
#define SYSCTL_AFFILIATE_CPU0 (0UL)
#define SYSCTL_AFFILIATE_CPU1 (1UL)

/* RETENTION register group index macro definition */
#define SYSCTL_RETENTION_CPU0 (0UL)
#define SYSCTL_RETENTION_CPU1 (1UL)

/* POWER register group index macro definition */
#define SYSCTL_POWER_CPU0 (0UL)
#define SYSCTL_POWER_CPU1 (1UL)
#define SYSCTL_POWER_CON (2UL)
#define SYSCTL_POWER_VIS (3UL)

/* RESET register group index macro definition */
#define SYSCTL_RESET_SOC (0UL)
#define SYSCTL_RESET_CON (1UL)
#define SYSCTL_RESET_VIS (2UL)
#define SYSCTL_RESET_CPU0 (3UL)
#define SYSCTL_RESET_CPU1 (4UL)

/* CLOCK register group index macro definition */
#define SYSCTL_CLOCK_CLK_TOP_CPU0 (0UL)
#define SYSCTL_CLOCK_CLK_TOP_MCHTMR0 (1UL)
#define SYSCTL_CLOCK_CLK_TOP_CPU1 (2UL)
#define SYSCTL_CLOCK_CLK_TOP_MCHTMR (3UL)
#define SYSCTL_CLOCK_CLK_TOP_AXI (4UL)
#define SYSCTL_CLOCK_CLK_TOP_CONN (5UL)
#define SYSCTL_CLOCK_CLK_TOP_VIS (6UL)
#define SYSCTL_CLOCK_CLK_TOP_AHB (7UL)
#define SYSCTL_CLOCK_CLK_TOP_FEMC (8UL)
#define SYSCTL_CLOCK_CLK_TOP_XPI0 (9UL)
#define SYSCTL_CLOCK_CLK_TOP_XPI1 (10UL)
#define SYSCTL_CLOCK_CLK_TOP_GPTMR0 (11UL)
#define SYSCTL_CLOCK_CLK_TOP_GPTMR1 (12UL)
#define SYSCTL_CLOCK_CLK_TOP_GPTMR2 (13UL)
#define SYSCTL_CLOCK_CLK_TOP_GPTMR3 (14UL)
#define SYSCTL_CLOCK_CLK_TOP_GPTMR4 (15UL)
#define SYSCTL_CLOCK_CLK_TOP_GPTMR5 (16UL)
#define SYSCTL_CLOCK_CLK_TOP_GPTMR6 (17UL)
#define SYSCTL_CLOCK_CLK_TOP_GPTMR7 (18UL)
#define SYSCTL_CLOCK_CLK_TOP_UART0 (19UL)
#define SYSCTL_CLOCK_CLK_TOP_UART1 (20UL)
#define SYSCTL_CLOCK_CLK_TOP_UART2 (21UL)
#define SYSCTL_CLOCK_CLK_TOP_UART3 (22UL)
#define SYSCTL_CLOCK_CLK_TOP_UART4 (23UL)
#define SYSCTL_CLOCK_CLK_TOP_UART5 (24UL)
#define SYSCTL_CLOCK_CLK_TOP_UART6 (25UL)
#define SYSCTL_CLOCK_CLK_TOP_UART7 (26UL)
#define SYSCTL_CLOCK_CLK_TOP_UART8 (27UL)
#define SYSCTL_CLOCK_CLK_TOP_UART9 (28UL)
#define SYSCTL_CLOCK_CLK_TOP_UART10 (29UL)
#define SYSCTL_CLOCK_CLK_TOP_UART11 (30UL)
#define SYSCTL_CLOCK_CLK_TOP_UART12 (31UL)
#define SYSCTL_CLOCK_CLK_TOP_UART13 (32UL)
#define SYSCTL_CLOCK_CLK_TOP_UART14 (33UL)
#define SYSCTL_CLOCK_CLK_TOP_UART15 (34UL)
#define SYSCTL_CLOCK_CLK_TOP_I2C0 (35UL)
#define SYSCTL_CLOCK_CLK_TOP_I2C1 (36UL)
#define SYSCTL_CLOCK_CLK_TOP_I2C2 (37UL)
#define SYSCTL_CLOCK_CLK_TOP_I2C3 (38UL)
#define SYSCTL_CLOCK_CLK_TOP_SPI0 (39UL)
#define SYSCTL_CLOCK_CLK_TOP_SPI1 (40UL)
#define SYSCTL_CLOCK_CLK_TOP_SPI2 (41UL)
#define SYSCTL_CLOCK_CLK_TOP_SPI3 (42UL)
#define SYSCTL_CLOCK_CLK_TOP_CAN0 (43UL)
#define SYSCTL_CLOCK_CLK_TOP_CAN1 (44UL)
#define SYSCTL_CLOCK_CLK_TOP_CAN2 (45UL)
#define SYSCTL_CLOCK_CLK_TOP_CAN3 (46UL)
#define SYSCTL_CLOCK_CLK_TOP_PTPC (47UL)
#define SYSCTL_CLOCK_CLK_TOP_ANA0 (48UL)
#define SYSCTL_CLOCK_CLK_TOP_ANA1 (49UL)
#define SYSCTL_CLOCK_CLK_TOP_ANA2 (50UL)
#define SYSCTL_CLOCK_CLK_TOP_AUD0 (51UL)
#define SYSCTL_CLOCK_CLK_TOP_AUD1 (52UL)
#define SYSCTL_CLOCK_CLK_TOP_AUD2 (53UL)
#define SYSCTL_CLOCK_CLK_TOP_LCDC (54UL)
#define SYSCTL_CLOCK_CLK_TOP_CAM0 (55UL)
#define SYSCTL_CLOCK_CLK_TOP_CAM1 (56UL)
#define SYSCTL_CLOCK_CLK_TOP_ENET0 (57UL)
#define SYSCTL_CLOCK_CLK_TOP_ENET1 (58UL)
#define SYSCTL_CLOCK_CLK_TOP_PTP0 (59UL)
#define SYSCTL_CLOCK_CLK_TOP_PTP1 (60UL)
#define SYSCTL_CLOCK_CLK_TOP_REF0 (61UL)
#define SYSCTL_CLOCK_CLK_TOP_REF1 (62UL)
#define SYSCTL_CLOCK_CLK_TOP_NTMR0 (63UL)
#define SYSCTL_CLOCK_CLK_TOP_NTMR1 (64UL)
#define SYSCTL_CLOCK_CLK_TOP_SDXC0 (65UL)
#define SYSCTL_CLOCK_CLK_TOP_SDXC1 (66UL)

/* ADCCLK register group index macro definition */
#define SYSCTL_ADCCLK_CLK_TOP_ADC0 (0UL)
#define SYSCTL_ADCCLK_CLK_TOP_ADC1 (1UL)
#define SYSCTL_ADCCLK_CLK_TOP_ADC2 (2UL)
#define SYSCTL_ADCCLK_CLK_TOP_ADC3 (3UL)

/* I2SCLK register group index macro definition */
#define SYSCTL_I2SCLK_CLK_TOP_I2S0 (0UL)
#define SYSCTL_I2SCLK_CLK_TOP_I2S1 (1UL)
#define SYSCTL_I2SCLK_CLK_TOP_I2S2 (2UL)
#define SYSCTL_I2SCLK_CLK_TOP_I2S3 (3UL)

/* MONITOR register group index macro definition */
#define SYSCTL_MONITOR_SLICE0 (0UL)
#define SYSCTL_MONITOR_SLICE1 (1UL)
#define SYSCTL_MONITOR_SLICE2 (2UL)
#define SYSCTL_MONITOR_SLICE3 (3UL)

/* GPR register group index macro definition */
#define SYSCTL_CPU_GPR_GPR0 (0UL)
#define SYSCTL_CPU_GPR_GPR1 (1UL)
#define SYSCTL_CPU_GPR_GPR2 (2UL)
#define SYSCTL_CPU_GPR_GPR3 (3UL)
#define SYSCTL_CPU_GPR_GPR4 (4UL)
#define SYSCTL_CPU_GPR_GPR5 (5UL)
#define SYSCTL_CPU_GPR_GPR6 (6UL)
#define SYSCTL_CPU_GPR_GPR7 (7UL)
#define SYSCTL_CPU_GPR_GPR8 (8UL)
#define SYSCTL_CPU_GPR_GPR9 (9UL)
#define SYSCTL_CPU_GPR_GPR10 (10UL)
#define SYSCTL_CPU_GPR_GPR11 (11UL)
#define SYSCTL_CPU_GPR_GPR12 (12UL)
#define SYSCTL_CPU_GPR_GPR13 (13UL)

/* WAKEUP_STATUS register group index macro definition */
#define SYSCTL_CPU_WAKEUP_STATUS_STATUS0 (0UL)
#define SYSCTL_CPU_WAKEUP_STATUS_STATUS1 (1UL)
#define SYSCTL_CPU_WAKEUP_STATUS_STATUS2 (2UL)
#define SYSCTL_CPU_WAKEUP_STATUS_STATUS3 (3UL)
#define SYSCTL_CPU_WAKEUP_STATUS_STATUS4 (4UL)
#define SYSCTL_CPU_WAKEUP_STATUS_STATUS5 (5UL)
#define SYSCTL_CPU_WAKEUP_STATUS_STATUS6 (6UL)
#define SYSCTL_CPU_WAKEUP_STATUS_STATUS7 (7UL)

/* WAKEUP_ENABLE register group index macro definition */
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE0 (0UL)
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE1 (1UL)
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE2 (2UL)
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE3 (3UL)
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE4 (4UL)
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE5 (5UL)
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE6 (6UL)
#define SYSCTL_CPU_WAKEUP_ENABLE_ENABLE7 (7UL)

/* CPU register group index macro definition */
#define SYSCTL_CPU_CPU0 (0UL)
#define SYSCTL_CPU_CPU1 (1UL)


#endif /* HPM_SYSCTL_H */
