/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_MIPI_DSI_PHY_H
#define HPM_MIPI_DSI_PHY_H

typedef struct {
    __RW uint32_t CLANE_PARA0;                 /* 0x0: timer counter about clock lane parameter */
    __RW uint32_t CLANE_PARA1;                 /* 0x4: timer counter about clock lane parameter */
    __RW uint32_t CLANE_PARA2;                 /* 0x8: timer counter about clock lane parameter */
    __RW uint32_t CLANE_PARA3;                 /* 0xC: timer counter about clock lane parameter */
    __RW uint32_t DLANE0_PARA0;                /* 0x10: timer counter about datalane0 parameter */
    __RW uint32_t DLANE0_PARA1;                /* 0x14: timer counter about datalane0 parameter */
    __RW uint32_t DLANE0_PARA2;                /* 0x18: timer counter about datalane0 parameter */
    __RW uint32_t DLANE0_PARA3;                /* 0x1C: timer counter about datalane0 parameter */
    __RW uint32_t DLANE0_PARA4;                /* 0x20: timer counter about datalane0 parameter */
    __RW uint32_t DLANE1_PARA0;                /* 0x24: timer counter about datalane1 parameter */
    __RW uint32_t DLANE1_PARA1;                /* 0x28: timer counter about datalane1 parameter */
    __RW uint32_t DLANE1_PARA2;                /* 0x2C: timer counter about datalane1 parameter */
    __RW uint32_t DLANE1_PARA3;                /* 0x30: timer counter about datalane1 parameter */
    __RW uint32_t DLANE2_PARA0;                /* 0x34: timer counter about datalane2 parameter */
    __RW uint32_t DLANE2_PARA1;                /* 0x38: timer counter about datalane2 parameter */
    __RW uint32_t DLANE2_PARA2;                /* 0x3C: timer counter about datalane2 parameter */
    __RW uint32_t DLANE2_PARA3;                /* 0x40: timer counter about datalane2 parameter */
    __RW uint32_t DLANE3_PARA0;                /* 0x44: timer counter about datalane3 parameter */
    __RW uint32_t DLANE3_PARA1;                /* 0x48: timer counter about datalane3 parameter */
    __RW uint32_t DLANE3_PARA2;                /* 0x4C: timer counter about datalane3 parameter */
    __RW uint32_t DLANE3_PARA3;                /* 0x50: timer counter about datalane3 parameter */
    __RW uint32_t COMMON_PARA0;                /* 0x54: timing parameter for all lanes */
    __RW uint32_t CTRL_PARA0;                  /* 0x58: dphy control parameter */
    __RW uint32_t PLL_CTRL_PARA0;              /* 0x5C: dphy pll control parameter */
    __R  uint8_t  RESERVED0[4];                /* 0x60 - 0x63: Reserved */
    __RW uint32_t RCAL_CTRL;                   /* 0x64: dphy calibration control parameter */
    __RW uint32_t TRIM_PARA;                   /* 0x68: dphy trimming parameter */
    __RW uint32_t TEST_PARA0;                  /* 0x6C: dphy test control parameter */
    __RW uint32_t TEST_PARA1;                  /* 0x70: dphy bist test control parameter */
    __RW uint32_t MISC_PARA;                   /* 0x74: dphy control parameter */
    __RW uint32_t CLANE_PARA4;                 /* 0x78: dphy clock lane control parameter */
    __RW uint32_t INTERFACE_PARA;              /* 0x7C: dphy clock lane control parameter */
    __RW uint32_t PCS_RESERVED_PIN_PARA;       /* 0x80: reserved the pins for pcs */
    __R  uint8_t  RESERVED1[8];                /* 0x84 - 0x8B: Reserved */
    __RW uint32_t CLANE_DATA_PARA;             /* 0x8C: parallel data about clock lane parameter */
    __RW uint32_t PMA_LANE_SEL_PARA;           /* 0x90: pma about clock lane select parameter */
} MIPI_DSI_PHY_Type;


/* Bitfield definition for register: CLANE_PARA0 */
/*
 * T_RST2ENLPTX_C (RW)
 *
 * the soft reset of clk_cfg domain
 */
#define MIPI_DSI_PHY_CLANE_PARA0_T_RST2ENLPTX_C_MASK (0xFFFFU)
#define MIPI_DSI_PHY_CLANE_PARA0_T_RST2ENLPTX_C_SHIFT (0U)
#define MIPI_DSI_PHY_CLANE_PARA0_T_RST2ENLPTX_C_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CLANE_PARA0_T_RST2ENLPTX_C_SHIFT) & MIPI_DSI_PHY_CLANE_PARA0_T_RST2ENLPTX_C_MASK)
#define MIPI_DSI_PHY_CLANE_PARA0_T_RST2ENLPTX_C_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CLANE_PARA0_T_RST2ENLPTX_C_MASK) >> MIPI_DSI_PHY_CLANE_PARA0_T_RST2ENLPTX_C_SHIFT)

/* Bitfield definition for register: CLANE_PARA1 */
/*
 * T_INITTIME_C (RW)
 *
 * the number of byteclk cycles that clklane drive LP-11 during initialization period
 */
#define MIPI_DSI_PHY_CLANE_PARA1_T_INITTIME_C_MASK (0xFFFFFFFFUL)
#define MIPI_DSI_PHY_CLANE_PARA1_T_INITTIME_C_SHIFT (0U)
#define MIPI_DSI_PHY_CLANE_PARA1_T_INITTIME_C_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CLANE_PARA1_T_INITTIME_C_SHIFT) & MIPI_DSI_PHY_CLANE_PARA1_T_INITTIME_C_MASK)
#define MIPI_DSI_PHY_CLANE_PARA1_T_INITTIME_C_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CLANE_PARA1_T_INITTIME_C_MASK) >> MIPI_DSI_PHY_CLANE_PARA1_T_INITTIME_C_SHIFT)

/* Bitfield definition for register: CLANE_PARA2 */
/*
 * T_CLKPREPARE_C (RW)
 *
 * the number of byteclk cycles that clock lane clkp/n lines are at the hs prepare state lp-00 during a hs clock transmission
 */
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKPREPARE_C_MASK (0xFF0000UL)
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKPREPARE_C_SHIFT (16U)
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKPREPARE_C_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CLANE_PARA2_T_CLKPREPARE_C_SHIFT) & MIPI_DSI_PHY_CLANE_PARA2_T_CLKPREPARE_C_MASK)
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKPREPARE_C_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CLANE_PARA2_T_CLKPREPARE_C_MASK) >> MIPI_DSI_PHY_CLANE_PARA2_T_CLKPREPARE_C_SHIFT)

/*
 * T_CLKZERO_C (RW)
 *
 * the number of byteclk cycles that clock lane clkp/n lines are at the hs-zero state hs-0 during a hs clock transmission
 */
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKZERO_C_MASK (0xFF00U)
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKZERO_C_SHIFT (8U)
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKZERO_C_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CLANE_PARA2_T_CLKZERO_C_SHIFT) & MIPI_DSI_PHY_CLANE_PARA2_T_CLKZERO_C_MASK)
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKZERO_C_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CLANE_PARA2_T_CLKZERO_C_MASK) >> MIPI_DSI_PHY_CLANE_PARA2_T_CLKZERO_C_SHIFT)

/*
 * T_CLKPRE_C (RW)
 *
 * the number of byteclk cycles that hs clock shall be driven prior to data lane beginning the transition from lp to hs mode
 */
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKPRE_C_MASK (0xFFU)
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKPRE_C_SHIFT (0U)
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKPRE_C_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CLANE_PARA2_T_CLKPRE_C_SHIFT) & MIPI_DSI_PHY_CLANE_PARA2_T_CLKPRE_C_MASK)
#define MIPI_DSI_PHY_CLANE_PARA2_T_CLKPRE_C_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CLANE_PARA2_T_CLKPRE_C_MASK) >> MIPI_DSI_PHY_CLANE_PARA2_T_CLKPRE_C_SHIFT)

/* Bitfield definition for register: CLANE_PARA3 */
/*
 * T_CLKPOST_C (RW)
 *
 * the number of byteclk cycles that the clock lane should keep sending the hs-clock after the last associated data lane has transitioned to LP mode.
 */
#define MIPI_DSI_PHY_CLANE_PARA3_T_CLKPOST_C_MASK (0xFF0000UL)
#define MIPI_DSI_PHY_CLANE_PARA3_T_CLKPOST_C_SHIFT (16U)
#define MIPI_DSI_PHY_CLANE_PARA3_T_CLKPOST_C_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CLANE_PARA3_T_CLKPOST_C_SHIFT) & MIPI_DSI_PHY_CLANE_PARA3_T_CLKPOST_C_MASK)
#define MIPI_DSI_PHY_CLANE_PARA3_T_CLKPOST_C_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CLANE_PARA3_T_CLKPOST_C_MASK) >> MIPI_DSI_PHY_CLANE_PARA3_T_CLKPOST_C_SHIFT)

/*
 * T_CLKTRIAL_C (RW)
 *
 * the number of byteclk cycles that the clock lane clkp/n lines are at state hs-tail sate hs-0 during a hs clock transmission
 */
#define MIPI_DSI_PHY_CLANE_PARA3_T_CLKTRIAL_C_MASK (0xFF00U)
#define MIPI_DSI_PHY_CLANE_PARA3_T_CLKTRIAL_C_SHIFT (8U)
#define MIPI_DSI_PHY_CLANE_PARA3_T_CLKTRIAL_C_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CLANE_PARA3_T_CLKTRIAL_C_SHIFT) & MIPI_DSI_PHY_CLANE_PARA3_T_CLKTRIAL_C_MASK)
#define MIPI_DSI_PHY_CLANE_PARA3_T_CLKTRIAL_C_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CLANE_PARA3_T_CLKTRIAL_C_MASK) >> MIPI_DSI_PHY_CLANE_PARA3_T_CLKTRIAL_C_SHIFT)

/*
 * T_HSEXIT_C (RW)
 *
 * the number of byteclk cycles that the clock lane clkp/n lines are at hs-exit state after a hs clock transmission
 */
#define MIPI_DSI_PHY_CLANE_PARA3_T_HSEXIT_C_MASK (0xFFU)
#define MIPI_DSI_PHY_CLANE_PARA3_T_HSEXIT_C_SHIFT (0U)
#define MIPI_DSI_PHY_CLANE_PARA3_T_HSEXIT_C_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CLANE_PARA3_T_HSEXIT_C_SHIFT) & MIPI_DSI_PHY_CLANE_PARA3_T_HSEXIT_C_MASK)
#define MIPI_DSI_PHY_CLANE_PARA3_T_HSEXIT_C_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CLANE_PARA3_T_HSEXIT_C_MASK) >> MIPI_DSI_PHY_CLANE_PARA3_T_HSEXIT_C_SHIFT)

/* Bitfield definition for register: DLANE0_PARA0 */
/*
 * T_RST2ENLPTX_D0 (RW)
 *
 * the number of byteclk cycles that datalane0 wait to enable lptx_en after reset release
 */
#define MIPI_DSI_PHY_DLANE0_PARA0_T_RST2ENLPTX_D0_MASK (0xFFFFU)
#define MIPI_DSI_PHY_DLANE0_PARA0_T_RST2ENLPTX_D0_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE0_PARA0_T_RST2ENLPTX_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE0_PARA0_T_RST2ENLPTX_D0_SHIFT) & MIPI_DSI_PHY_DLANE0_PARA0_T_RST2ENLPTX_D0_MASK)
#define MIPI_DSI_PHY_DLANE0_PARA0_T_RST2ENLPTX_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE0_PARA0_T_RST2ENLPTX_D0_MASK) >> MIPI_DSI_PHY_DLANE0_PARA0_T_RST2ENLPTX_D0_SHIFT)

/* Bitfield definition for register: DLANE0_PARA1 */
/*
 * T_INITTIME_D0 (RW)
 *
 * the number of byteclk cycles that datalane0 drive lp-11 during initiaalization period
 */
#define MIPI_DSI_PHY_DLANE0_PARA1_T_INITTIME_D0_MASK (0xFFFFFFFFUL)
#define MIPI_DSI_PHY_DLANE0_PARA1_T_INITTIME_D0_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE0_PARA1_T_INITTIME_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE0_PARA1_T_INITTIME_D0_SHIFT) & MIPI_DSI_PHY_DLANE0_PARA1_T_INITTIME_D0_MASK)
#define MIPI_DSI_PHY_DLANE0_PARA1_T_INITTIME_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE0_PARA1_T_INITTIME_D0_MASK) >> MIPI_DSI_PHY_DLANE0_PARA1_T_INITTIME_D0_SHIFT)

/* Bitfield definition for register: DLANE0_PARA2 */
/*
 * T_HSPREPARE_D0 (RW)
 *
 * the number of byteclk cycles that the datalane0 stay at hs prepare state lp-00 during a hs transmission
 */
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSPREPARE_D0_MASK (0xFF000000UL)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSPREPARE_D0_SHIFT (24U)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSPREPARE_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE0_PARA2_T_HSPREPARE_D0_SHIFT) & MIPI_DSI_PHY_DLANE0_PARA2_T_HSPREPARE_D0_MASK)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSPREPARE_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE0_PARA2_T_HSPREPARE_D0_MASK) >> MIPI_DSI_PHY_DLANE0_PARA2_T_HSPREPARE_D0_SHIFT)

/*
 * T_HSZERO_D0 (RW)
 *
 * the number of byteclk cycles that the datalane0 stay at hs-zero sate during a hs transmission
 */
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSZERO_D0_MASK (0xFF0000UL)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSZERO_D0_SHIFT (16U)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSZERO_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE0_PARA2_T_HSZERO_D0_SHIFT) & MIPI_DSI_PHY_DLANE0_PARA2_T_HSZERO_D0_MASK)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSZERO_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE0_PARA2_T_HSZERO_D0_MASK) >> MIPI_DSI_PHY_DLANE0_PARA2_T_HSZERO_D0_SHIFT)

/*
 * T_HSTRAIL_D0 (RW)
 *
 * the number of byteclk cycles that the datalane0 stay at hs-trail state during a hs clock transmission
 */
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSTRAIL_D0_MASK (0xFF00U)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSTRAIL_D0_SHIFT (8U)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSTRAIL_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE0_PARA2_T_HSTRAIL_D0_SHIFT) & MIPI_DSI_PHY_DLANE0_PARA2_T_HSTRAIL_D0_MASK)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSTRAIL_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE0_PARA2_T_HSTRAIL_D0_MASK) >> MIPI_DSI_PHY_DLANE0_PARA2_T_HSTRAIL_D0_SHIFT)

/*
 * T_HSEXIT_D0 (RW)
 *
 * the number of byteclk cycles that the datalane0 stay at state hs-exit sate after a hs clock transmission
 */
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSEXIT_D0_MASK (0xFFU)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSEXIT_D0_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSEXIT_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE0_PARA2_T_HSEXIT_D0_SHIFT) & MIPI_DSI_PHY_DLANE0_PARA2_T_HSEXIT_D0_MASK)
#define MIPI_DSI_PHY_DLANE0_PARA2_T_HSEXIT_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE0_PARA2_T_HSEXIT_D0_MASK) >> MIPI_DSI_PHY_DLANE0_PARA2_T_HSEXIT_D0_SHIFT)

/* Bitfield definition for register: DLANE0_PARA3 */
/*
 * T_WAKEUP_D0 (RW)
 *
 * the number of byteclk cycles from exiting ultra low power sate to enabling the low-power driver
 */
#define MIPI_DSI_PHY_DLANE0_PARA3_T_WAKEUP_D0_MASK (0xFFFFFFFFUL)
#define MIPI_DSI_PHY_DLANE0_PARA3_T_WAKEUP_D0_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE0_PARA3_T_WAKEUP_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE0_PARA3_T_WAKEUP_D0_SHIFT) & MIPI_DSI_PHY_DLANE0_PARA3_T_WAKEUP_D0_MASK)
#define MIPI_DSI_PHY_DLANE0_PARA3_T_WAKEUP_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE0_PARA3_T_WAKEUP_D0_MASK) >> MIPI_DSI_PHY_DLANE0_PARA3_T_WAKEUP_D0_SHIFT)

/* Bitfield definition for register: DLANE0_PARA4 */
/*
 * T_TAGO_D0 (RW)
 *
 * the number of byteclk cycles that the tx drives the bridge state during a turnaroud procedure
 */
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TAGO_D0_MASK (0xFF0000UL)
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TAGO_D0_SHIFT (16U)
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TAGO_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE0_PARA4_T_TAGO_D0_SHIFT) & MIPI_DSI_PHY_DLANE0_PARA4_T_TAGO_D0_MASK)
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TAGO_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE0_PARA4_T_TAGO_D0_MASK) >> MIPI_DSI_PHY_DLANE0_PARA4_T_TAGO_D0_SHIFT)

/*
 * T_TASURE_D0 (RW)
 *
 * the number of byteclk cycles that the rx waits after a bridge state has been detected during a turnaround procedure
 */
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TASURE_D0_MASK (0xFF00U)
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TASURE_D0_SHIFT (8U)
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TASURE_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE0_PARA4_T_TASURE_D0_SHIFT) & MIPI_DSI_PHY_DLANE0_PARA4_T_TASURE_D0_MASK)
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TASURE_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE0_PARA4_T_TASURE_D0_MASK) >> MIPI_DSI_PHY_DLANE0_PARA4_T_TASURE_D0_SHIFT)

/*
 * T_TAGET_D0 (RW)
 *
 * the number of byteclk cycles that the new transmitter drivers the bridge state after accepting control during bta
 */
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TAGET_D0_MASK (0xFFU)
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TAGET_D0_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TAGET_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE0_PARA4_T_TAGET_D0_SHIFT) & MIPI_DSI_PHY_DLANE0_PARA4_T_TAGET_D0_MASK)
#define MIPI_DSI_PHY_DLANE0_PARA4_T_TAGET_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE0_PARA4_T_TAGET_D0_MASK) >> MIPI_DSI_PHY_DLANE0_PARA4_T_TAGET_D0_SHIFT)

/* Bitfield definition for register: DLANE1_PARA0 */
/*
 * T_RST2ENLPTX_D1 (RW)
 *
 * the number of byteclk cycles that datalane1 wait to enable lptx_en after reset release
 */
#define MIPI_DSI_PHY_DLANE1_PARA0_T_RST2ENLPTX_D1_MASK (0xFFFFU)
#define MIPI_DSI_PHY_DLANE1_PARA0_T_RST2ENLPTX_D1_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE1_PARA0_T_RST2ENLPTX_D1_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE1_PARA0_T_RST2ENLPTX_D1_SHIFT) & MIPI_DSI_PHY_DLANE1_PARA0_T_RST2ENLPTX_D1_MASK)
#define MIPI_DSI_PHY_DLANE1_PARA0_T_RST2ENLPTX_D1_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE1_PARA0_T_RST2ENLPTX_D1_MASK) >> MIPI_DSI_PHY_DLANE1_PARA0_T_RST2ENLPTX_D1_SHIFT)

/* Bitfield definition for register: DLANE1_PARA1 */
/*
 * T_INITTIME_D1 (RW)
 *
 * the number of byteclk cycles that datalane1 drive lp-11 during initiaalization period
 */
#define MIPI_DSI_PHY_DLANE1_PARA1_T_INITTIME_D1_MASK (0xFFFFFFFFUL)
#define MIPI_DSI_PHY_DLANE1_PARA1_T_INITTIME_D1_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE1_PARA1_T_INITTIME_D1_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE1_PARA1_T_INITTIME_D1_SHIFT) & MIPI_DSI_PHY_DLANE1_PARA1_T_INITTIME_D1_MASK)
#define MIPI_DSI_PHY_DLANE1_PARA1_T_INITTIME_D1_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE1_PARA1_T_INITTIME_D1_MASK) >> MIPI_DSI_PHY_DLANE1_PARA1_T_INITTIME_D1_SHIFT)

/* Bitfield definition for register: DLANE1_PARA2 */
/*
 * T_HSPREPARE_D1 (RW)
 *
 * the number of byteclk cycles that the datalane1 stay at hs prepare state lp-00 during a hs transmission
 */
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSPREPARE_D1_MASK (0xFF000000UL)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSPREPARE_D1_SHIFT (24U)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSPREPARE_D1_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE1_PARA2_T_HSPREPARE_D1_SHIFT) & MIPI_DSI_PHY_DLANE1_PARA2_T_HSPREPARE_D1_MASK)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSPREPARE_D1_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE1_PARA2_T_HSPREPARE_D1_MASK) >> MIPI_DSI_PHY_DLANE1_PARA2_T_HSPREPARE_D1_SHIFT)

/*
 * T_HSZERO_D1 (RW)
 *
 * the number of byteclk cycles that the datalane1 stay at hs-zero sate during a hs transmission
 */
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSZERO_D1_MASK (0xFF0000UL)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSZERO_D1_SHIFT (16U)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSZERO_D1_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE1_PARA2_T_HSZERO_D1_SHIFT) & MIPI_DSI_PHY_DLANE1_PARA2_T_HSZERO_D1_MASK)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSZERO_D1_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE1_PARA2_T_HSZERO_D1_MASK) >> MIPI_DSI_PHY_DLANE1_PARA2_T_HSZERO_D1_SHIFT)

/*
 * T_HSTRAIL_D1 (RW)
 *
 * the number of byteclk cycles that the datalane1 stay at hs-trail state during a hs clock transmission
 */
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSTRAIL_D1_MASK (0xFF00U)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSTRAIL_D1_SHIFT (8U)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSTRAIL_D1_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE1_PARA2_T_HSTRAIL_D1_SHIFT) & MIPI_DSI_PHY_DLANE1_PARA2_T_HSTRAIL_D1_MASK)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSTRAIL_D1_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE1_PARA2_T_HSTRAIL_D1_MASK) >> MIPI_DSI_PHY_DLANE1_PARA2_T_HSTRAIL_D1_SHIFT)

/*
 * T_HSEXIT_D1 (RW)
 *
 * the number of byteclk cycles that the datalane1 stay at state hs-exit sate after a hs clock transmission
 */
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSEXIT_D1_MASK (0xFFU)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSEXIT_D1_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSEXIT_D1_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE1_PARA2_T_HSEXIT_D1_SHIFT) & MIPI_DSI_PHY_DLANE1_PARA2_T_HSEXIT_D1_MASK)
#define MIPI_DSI_PHY_DLANE1_PARA2_T_HSEXIT_D1_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE1_PARA2_T_HSEXIT_D1_MASK) >> MIPI_DSI_PHY_DLANE1_PARA2_T_HSEXIT_D1_SHIFT)

/* Bitfield definition for register: DLANE1_PARA3 */
/*
 * T_WAKEUP_D1 (RW)
 *
 * the number of byteclk cycles from exiting ultra low power sate to enabling the low-power driver
 */
#define MIPI_DSI_PHY_DLANE1_PARA3_T_WAKEUP_D1_MASK (0xFFFFFFFFUL)
#define MIPI_DSI_PHY_DLANE1_PARA3_T_WAKEUP_D1_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE1_PARA3_T_WAKEUP_D1_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE1_PARA3_T_WAKEUP_D1_SHIFT) & MIPI_DSI_PHY_DLANE1_PARA3_T_WAKEUP_D1_MASK)
#define MIPI_DSI_PHY_DLANE1_PARA3_T_WAKEUP_D1_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE1_PARA3_T_WAKEUP_D1_MASK) >> MIPI_DSI_PHY_DLANE1_PARA3_T_WAKEUP_D1_SHIFT)

/* Bitfield definition for register: DLANE2_PARA0 */
/*
 * T_RST2ENLPTX_D2 (RW)
 *
 * the number of byteclk cycles that datalane2 wait to enable lptx_en after reset release
 */
#define MIPI_DSI_PHY_DLANE2_PARA0_T_RST2ENLPTX_D2_MASK (0xFFFFU)
#define MIPI_DSI_PHY_DLANE2_PARA0_T_RST2ENLPTX_D2_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE2_PARA0_T_RST2ENLPTX_D2_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE2_PARA0_T_RST2ENLPTX_D2_SHIFT) & MIPI_DSI_PHY_DLANE2_PARA0_T_RST2ENLPTX_D2_MASK)
#define MIPI_DSI_PHY_DLANE2_PARA0_T_RST2ENLPTX_D2_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE2_PARA0_T_RST2ENLPTX_D2_MASK) >> MIPI_DSI_PHY_DLANE2_PARA0_T_RST2ENLPTX_D2_SHIFT)

/* Bitfield definition for register: DLANE2_PARA1 */
/*
 * T_INITTIME_D2 (RW)
 *
 * the number of byteclk cycles that datalane2 drive lp-11 during initiaalization period
 */
#define MIPI_DSI_PHY_DLANE2_PARA1_T_INITTIME_D2_MASK (0xFFFFFFFFUL)
#define MIPI_DSI_PHY_DLANE2_PARA1_T_INITTIME_D2_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE2_PARA1_T_INITTIME_D2_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE2_PARA1_T_INITTIME_D2_SHIFT) & MIPI_DSI_PHY_DLANE2_PARA1_T_INITTIME_D2_MASK)
#define MIPI_DSI_PHY_DLANE2_PARA1_T_INITTIME_D2_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE2_PARA1_T_INITTIME_D2_MASK) >> MIPI_DSI_PHY_DLANE2_PARA1_T_INITTIME_D2_SHIFT)

/* Bitfield definition for register: DLANE2_PARA2 */
/*
 * T_HSPREPARE_D2 (RW)
 *
 * the number of byteclk cycles that the datalane2 stay at hs prepare state lp-00 during a hs transmission
 */
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSPREPARE_D2_MASK (0xFF000000UL)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSPREPARE_D2_SHIFT (24U)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSPREPARE_D2_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE2_PARA2_T_HSPREPARE_D2_SHIFT) & MIPI_DSI_PHY_DLANE2_PARA2_T_HSPREPARE_D2_MASK)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSPREPARE_D2_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE2_PARA2_T_HSPREPARE_D2_MASK) >> MIPI_DSI_PHY_DLANE2_PARA2_T_HSPREPARE_D2_SHIFT)

/*
 * T_HSZERO_D2 (RW)
 *
 * the number of byteclk cycles that the datalane2 stay at hs-zero sate during a hs transmission
 */
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSZERO_D2_MASK (0xFF0000UL)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSZERO_D2_SHIFT (16U)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSZERO_D2_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE2_PARA2_T_HSZERO_D2_SHIFT) & MIPI_DSI_PHY_DLANE2_PARA2_T_HSZERO_D2_MASK)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSZERO_D2_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE2_PARA2_T_HSZERO_D2_MASK) >> MIPI_DSI_PHY_DLANE2_PARA2_T_HSZERO_D2_SHIFT)

/*
 * T_HSTRAIL_D2 (RW)
 *
 * the number of byteclk cycles that the datalane2 stay at hs-trail state during a hs clock transmission
 */
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSTRAIL_D2_MASK (0xFF00U)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSTRAIL_D2_SHIFT (8U)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSTRAIL_D2_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE2_PARA2_T_HSTRAIL_D2_SHIFT) & MIPI_DSI_PHY_DLANE2_PARA2_T_HSTRAIL_D2_MASK)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSTRAIL_D2_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE2_PARA2_T_HSTRAIL_D2_MASK) >> MIPI_DSI_PHY_DLANE2_PARA2_T_HSTRAIL_D2_SHIFT)

/*
 * T_HSEXIT_D2 (RW)
 *
 * the number of byteclk cycles that the datalane2 stay at state hs-exit sate after a hs clock transmission
 */
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSEXIT_D2_MASK (0xFFU)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSEXIT_D2_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSEXIT_D2_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE2_PARA2_T_HSEXIT_D2_SHIFT) & MIPI_DSI_PHY_DLANE2_PARA2_T_HSEXIT_D2_MASK)
#define MIPI_DSI_PHY_DLANE2_PARA2_T_HSEXIT_D2_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE2_PARA2_T_HSEXIT_D2_MASK) >> MIPI_DSI_PHY_DLANE2_PARA2_T_HSEXIT_D2_SHIFT)

/* Bitfield definition for register: DLANE2_PARA3 */
/*
 * T_WAKEUP_D2 (RW)
 *
 * the number of byteclk cycles from exiting ultra low power sate to enabling the low-power driver
 */
#define MIPI_DSI_PHY_DLANE2_PARA3_T_WAKEUP_D2_MASK (0xFFFFFFFFUL)
#define MIPI_DSI_PHY_DLANE2_PARA3_T_WAKEUP_D2_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE2_PARA3_T_WAKEUP_D2_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE2_PARA3_T_WAKEUP_D2_SHIFT) & MIPI_DSI_PHY_DLANE2_PARA3_T_WAKEUP_D2_MASK)
#define MIPI_DSI_PHY_DLANE2_PARA3_T_WAKEUP_D2_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE2_PARA3_T_WAKEUP_D2_MASK) >> MIPI_DSI_PHY_DLANE2_PARA3_T_WAKEUP_D2_SHIFT)

/* Bitfield definition for register: DLANE3_PARA0 */
/*
 * T_RST2ENLPTX_D3 (RW)
 *
 * the number of byteclk cycles that datalane3 wait to enable lptx_en after reset release
 */
#define MIPI_DSI_PHY_DLANE3_PARA0_T_RST2ENLPTX_D3_MASK (0xFFFFU)
#define MIPI_DSI_PHY_DLANE3_PARA0_T_RST2ENLPTX_D3_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE3_PARA0_T_RST2ENLPTX_D3_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE3_PARA0_T_RST2ENLPTX_D3_SHIFT) & MIPI_DSI_PHY_DLANE3_PARA0_T_RST2ENLPTX_D3_MASK)
#define MIPI_DSI_PHY_DLANE3_PARA0_T_RST2ENLPTX_D3_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE3_PARA0_T_RST2ENLPTX_D3_MASK) >> MIPI_DSI_PHY_DLANE3_PARA0_T_RST2ENLPTX_D3_SHIFT)

/* Bitfield definition for register: DLANE3_PARA1 */
/*
 * T_INITTIME_D3 (RW)
 *
 * the number of byteclk cycles that datalane3 drive lp-11 during initiaalization period
 */
#define MIPI_DSI_PHY_DLANE3_PARA1_T_INITTIME_D3_MASK (0xFFFFFFFFUL)
#define MIPI_DSI_PHY_DLANE3_PARA1_T_INITTIME_D3_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE3_PARA1_T_INITTIME_D3_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE3_PARA1_T_INITTIME_D3_SHIFT) & MIPI_DSI_PHY_DLANE3_PARA1_T_INITTIME_D3_MASK)
#define MIPI_DSI_PHY_DLANE3_PARA1_T_INITTIME_D3_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE3_PARA1_T_INITTIME_D3_MASK) >> MIPI_DSI_PHY_DLANE3_PARA1_T_INITTIME_D3_SHIFT)

/* Bitfield definition for register: DLANE3_PARA2 */
/*
 * T_HSPREPARE_D3 (RW)
 *
 * the number of byteclk cycles that the datalane3 stay at hs prepare state lp-00 during a hs transmission
 */
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSPREPARE_D3_MASK (0xFF000000UL)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSPREPARE_D3_SHIFT (24U)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSPREPARE_D3_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE3_PARA2_T_HSPREPARE_D3_SHIFT) & MIPI_DSI_PHY_DLANE3_PARA2_T_HSPREPARE_D3_MASK)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSPREPARE_D3_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE3_PARA2_T_HSPREPARE_D3_MASK) >> MIPI_DSI_PHY_DLANE3_PARA2_T_HSPREPARE_D3_SHIFT)

/*
 * T_HSZERO_D3 (RW)
 *
 * the number of byteclk cycles that the datalane3 stay at hs-zero sate during a hs transmission
 */
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSZERO_D3_MASK (0xFF0000UL)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSZERO_D3_SHIFT (16U)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSZERO_D3_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE3_PARA2_T_HSZERO_D3_SHIFT) & MIPI_DSI_PHY_DLANE3_PARA2_T_HSZERO_D3_MASK)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSZERO_D3_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE3_PARA2_T_HSZERO_D3_MASK) >> MIPI_DSI_PHY_DLANE3_PARA2_T_HSZERO_D3_SHIFT)

/*
 * T_HSTRAIL_D3 (RW)
 *
 * the number of byteclk cycles that the datalane3 stay at hs-trail state during a hs clock transmission
 */
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSTRAIL_D3_MASK (0xFF00U)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSTRAIL_D3_SHIFT (8U)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSTRAIL_D3_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE3_PARA2_T_HSTRAIL_D3_SHIFT) & MIPI_DSI_PHY_DLANE3_PARA2_T_HSTRAIL_D3_MASK)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSTRAIL_D3_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE3_PARA2_T_HSTRAIL_D3_MASK) >> MIPI_DSI_PHY_DLANE3_PARA2_T_HSTRAIL_D3_SHIFT)

/*
 * T_HSEXIT_D3 (RW)
 *
 * the number of byteclk cycles that the datalane3 stay at state hs-exit sate after a hs clock transmission
 */
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSEXIT_D3_MASK (0xFFU)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSEXIT_D3_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSEXIT_D3_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE3_PARA2_T_HSEXIT_D3_SHIFT) & MIPI_DSI_PHY_DLANE3_PARA2_T_HSEXIT_D3_MASK)
#define MIPI_DSI_PHY_DLANE3_PARA2_T_HSEXIT_D3_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE3_PARA2_T_HSEXIT_D3_MASK) >> MIPI_DSI_PHY_DLANE3_PARA2_T_HSEXIT_D3_SHIFT)

/* Bitfield definition for register: DLANE3_PARA3 */
/*
 * T_WAKEUP_D3 (RW)
 *
 * the number of byteclk cycles from exiting ultra low power sate to enabling the low-power driver
 */
#define MIPI_DSI_PHY_DLANE3_PARA3_T_WAKEUP_D3_MASK (0xFFFFFFFFUL)
#define MIPI_DSI_PHY_DLANE3_PARA3_T_WAKEUP_D3_SHIFT (0U)
#define MIPI_DSI_PHY_DLANE3_PARA3_T_WAKEUP_D3_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_DLANE3_PARA3_T_WAKEUP_D3_SHIFT) & MIPI_DSI_PHY_DLANE3_PARA3_T_WAKEUP_D3_MASK)
#define MIPI_DSI_PHY_DLANE3_PARA3_T_WAKEUP_D3_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_DLANE3_PARA3_T_WAKEUP_D3_MASK) >> MIPI_DSI_PHY_DLANE3_PARA3_T_WAKEUP_D3_SHIFT)

/* Bitfield definition for register: COMMON_PARA0 */
/*
 * T_LPX (RW)
 *
 * the number of byteclk cycles of transmitted length of any low-power state period
 */
#define MIPI_DSI_PHY_COMMON_PARA0_T_LPX_MASK (0xFFU)
#define MIPI_DSI_PHY_COMMON_PARA0_T_LPX_SHIFT (0U)
#define MIPI_DSI_PHY_COMMON_PARA0_T_LPX_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_COMMON_PARA0_T_LPX_SHIFT) & MIPI_DSI_PHY_COMMON_PARA0_T_LPX_MASK)
#define MIPI_DSI_PHY_COMMON_PARA0_T_LPX_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_COMMON_PARA0_T_LPX_MASK) >> MIPI_DSI_PHY_COMMON_PARA0_T_LPX_SHIFT)

/* Bitfield definition for register: CTRL_PARA0 */
/*
 * VBG_RDY (RO)
 *
 * the indicator signal of reference generator is ready
 */
#define MIPI_DSI_PHY_CTRL_PARA0_VBG_RDY_MASK (0x80U)
#define MIPI_DSI_PHY_CTRL_PARA0_VBG_RDY_SHIFT (7U)
#define MIPI_DSI_PHY_CTRL_PARA0_VBG_RDY_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CTRL_PARA0_VBG_RDY_MASK) >> MIPI_DSI_PHY_CTRL_PARA0_VBG_RDY_SHIFT)

/*
 * EN_ULPRX_D0 (RW)
 *
 * ulp-rx enable for lane0
 */
#define MIPI_DSI_PHY_CTRL_PARA0_EN_ULPRX_D0_MASK (0x40U)
#define MIPI_DSI_PHY_CTRL_PARA0_EN_ULPRX_D0_SHIFT (6U)
#define MIPI_DSI_PHY_CTRL_PARA0_EN_ULPRX_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CTRL_PARA0_EN_ULPRX_D0_SHIFT) & MIPI_DSI_PHY_CTRL_PARA0_EN_ULPRX_D0_MASK)
#define MIPI_DSI_PHY_CTRL_PARA0_EN_ULPRX_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CTRL_PARA0_EN_ULPRX_D0_MASK) >> MIPI_DSI_PHY_CTRL_PARA0_EN_ULPRX_D0_SHIFT)

/*
 * EN_LPRX_D0 (RW)
 *
 * lp-rx enable for lane0
 */
#define MIPI_DSI_PHY_CTRL_PARA0_EN_LPRX_D0_MASK (0x20U)
#define MIPI_DSI_PHY_CTRL_PARA0_EN_LPRX_D0_SHIFT (5U)
#define MIPI_DSI_PHY_CTRL_PARA0_EN_LPRX_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CTRL_PARA0_EN_LPRX_D0_SHIFT) & MIPI_DSI_PHY_CTRL_PARA0_EN_LPRX_D0_MASK)
#define MIPI_DSI_PHY_CTRL_PARA0_EN_LPRX_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CTRL_PARA0_EN_LPRX_D0_MASK) >> MIPI_DSI_PHY_CTRL_PARA0_EN_LPRX_D0_SHIFT)

/*
 * EN_LPCD_D0 (RW)
 *
 * lp-cd enable for lane0
 */
#define MIPI_DSI_PHY_CTRL_PARA0_EN_LPCD_D0_MASK (0x10U)
#define MIPI_DSI_PHY_CTRL_PARA0_EN_LPCD_D0_SHIFT (4U)
#define MIPI_DSI_PHY_CTRL_PARA0_EN_LPCD_D0_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CTRL_PARA0_EN_LPCD_D0_SHIFT) & MIPI_DSI_PHY_CTRL_PARA0_EN_LPCD_D0_MASK)
#define MIPI_DSI_PHY_CTRL_PARA0_EN_LPCD_D0_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CTRL_PARA0_EN_LPCD_D0_MASK) >> MIPI_DSI_PHY_CTRL_PARA0_EN_LPCD_D0_SHIFT)

/*
 * PWON_SEL (RW)
 *
 * select the cource of PMA power on control signals
 */
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_SEL_MASK (0x8U)
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_SEL_SHIFT (3U)
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_SEL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CTRL_PARA0_PWON_SEL_SHIFT) & MIPI_DSI_PHY_CTRL_PARA0_PWON_SEL_MASK)
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_SEL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CTRL_PARA0_PWON_SEL_MASK) >> MIPI_DSI_PHY_CTRL_PARA0_PWON_SEL_SHIFT)

/*
 * PWON_PLL (RW)
 *
 * power on pll high active
 */
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_PLL_MASK (0x4U)
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_PLL_SHIFT (2U)
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_PLL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CTRL_PARA0_PWON_PLL_SHIFT) & MIPI_DSI_PHY_CTRL_PARA0_PWON_PLL_MASK)
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_PLL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CTRL_PARA0_PWON_PLL_MASK) >> MIPI_DSI_PHY_CTRL_PARA0_PWON_PLL_SHIFT)

/*
 * PWON_DSI (RW)
 *
 * power on all dsi lane
 */
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_DSI_MASK (0x2U)
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_DSI_SHIFT (1U)
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_DSI_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CTRL_PARA0_PWON_DSI_SHIFT) & MIPI_DSI_PHY_CTRL_PARA0_PWON_DSI_MASK)
#define MIPI_DSI_PHY_CTRL_PARA0_PWON_DSI_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CTRL_PARA0_PWON_DSI_MASK) >> MIPI_DSI_PHY_CTRL_PARA0_PWON_DSI_SHIFT)

/*
 * SU_IDDQ_EN (RW)
 *
 * power down all modules inside su includes ivref, r-calibration and pll, high effective
 */
#define MIPI_DSI_PHY_CTRL_PARA0_SU_IDDQ_EN_MASK (0x1U)
#define MIPI_DSI_PHY_CTRL_PARA0_SU_IDDQ_EN_SHIFT (0U)
#define MIPI_DSI_PHY_CTRL_PARA0_SU_IDDQ_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CTRL_PARA0_SU_IDDQ_EN_SHIFT) & MIPI_DSI_PHY_CTRL_PARA0_SU_IDDQ_EN_MASK)
#define MIPI_DSI_PHY_CTRL_PARA0_SU_IDDQ_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CTRL_PARA0_SU_IDDQ_EN_MASK) >> MIPI_DSI_PHY_CTRL_PARA0_SU_IDDQ_EN_SHIFT)

/* Bitfield definition for register: PLL_CTRL_PARA0 */
/*
 * PLL_LOCK (RO)
 *
 * pll lock indication
 */
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_LOCK_MASK (0x8000000UL)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_LOCK_SHIFT (27U)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_LOCK_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_LOCK_MASK) >> MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_LOCK_SHIFT)

/*
 * RATE (RW)
 *
 * data reate control signal
 */
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_RATE_MASK (0x7000000UL)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_RATE_SHIFT (24U)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_RATE_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PLL_CTRL_PARA0_RATE_SHIFT) & MIPI_DSI_PHY_PLL_CTRL_PARA0_RATE_MASK)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_RATE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PLL_CTRL_PARA0_RATE_MASK) >> MIPI_DSI_PHY_PLL_CTRL_PARA0_RATE_SHIFT)

/*
 * REFCLK_DIV (RW)
 *
 * input reference clock divider ratio control
 */
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_REFCLK_DIV_MASK (0xF80000UL)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_REFCLK_DIV_SHIFT (19U)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_REFCLK_DIV_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PLL_CTRL_PARA0_REFCLK_DIV_SHIFT) & MIPI_DSI_PHY_PLL_CTRL_PARA0_REFCLK_DIV_MASK)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_REFCLK_DIV_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PLL_CTRL_PARA0_REFCLK_DIV_MASK) >> MIPI_DSI_PHY_PLL_CTRL_PARA0_REFCLK_DIV_SHIFT)

/*
 * PLL_DIV (RW)
 *
 * pll loop divider ratio control
 */
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_DIV_MASK (0x7FFF0UL)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_DIV_SHIFT (4U)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_DIV_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_DIV_SHIFT) & MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_DIV_MASK)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_DIV_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_DIV_MASK) >> MIPI_DSI_PHY_PLL_CTRL_PARA0_PLL_DIV_SHIFT)

/*
 * DSI_PIXELCLK_DIV (RW)
 *
 * pixell clock divided from pll output
 */
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_DSI_PIXELCLK_DIV_MASK (0xFU)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_DSI_PIXELCLK_DIV_SHIFT (0U)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_DSI_PIXELCLK_DIV_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PLL_CTRL_PARA0_DSI_PIXELCLK_DIV_SHIFT) & MIPI_DSI_PHY_PLL_CTRL_PARA0_DSI_PIXELCLK_DIV_MASK)
#define MIPI_DSI_PHY_PLL_CTRL_PARA0_DSI_PIXELCLK_DIV_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PLL_CTRL_PARA0_DSI_PIXELCLK_DIV_MASK) >> MIPI_DSI_PHY_PLL_CTRL_PARA0_DSI_PIXELCLK_DIV_SHIFT)

/* Bitfield definition for register: RCAL_CTRL */
/*
 * RCAL_EN (RW)
 *
 * enable hs-tx output impedance trimming
 */
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_EN_MASK (0x2000U)
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_EN_SHIFT (13U)
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_RCAL_CTRL_RCAL_EN_SHIFT) & MIPI_DSI_PHY_RCAL_CTRL_RCAL_EN_MASK)
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_RCAL_CTRL_RCAL_EN_MASK) >> MIPI_DSI_PHY_RCAL_CTRL_RCAL_EN_SHIFT)

/*
 * RCAL_TRIM (RW)
 *
 * default value of hs-tx output resistance configure
 */
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_TRIM_MASK (0x1E00U)
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_TRIM_SHIFT (9U)
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_TRIM_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_RCAL_CTRL_RCAL_TRIM_SHIFT) & MIPI_DSI_PHY_RCAL_CTRL_RCAL_TRIM_MASK)
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_TRIM_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_RCAL_CTRL_RCAL_TRIM_MASK) >> MIPI_DSI_PHY_RCAL_CTRL_RCAL_TRIM_SHIFT)

/*
 * RCAL_CTRL (RW)
 *
 * resistor calibration control, reserved for test
 */
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_CTRL_MASK (0x1FEU)
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_CTRL_SHIFT (1U)
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_CTRL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_RCAL_CTRL_RCAL_CTRL_SHIFT) & MIPI_DSI_PHY_RCAL_CTRL_RCAL_CTRL_MASK)
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_CTRL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_RCAL_CTRL_RCAL_CTRL_MASK) >> MIPI_DSI_PHY_RCAL_CTRL_RCAL_CTRL_SHIFT)

/*
 * RCAL_DONE (RO)
 *
 * hs-tx output impedance trimming done indicator signal
 */
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_DONE_MASK (0x1U)
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_DONE_SHIFT (0U)
#define MIPI_DSI_PHY_RCAL_CTRL_RCAL_DONE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_RCAL_CTRL_RCAL_DONE_MASK) >> MIPI_DSI_PHY_RCAL_CTRL_RCAL_DONE_SHIFT)

/* Bitfield definition for register: TRIM_PARA */
/*
 * HSTX_AMP_TRIM (RW)
 *
 * hs-tx output vod trimming for lane-0~4
 */
#define MIPI_DSI_PHY_TRIM_PARA_HSTX_AMP_TRIM_MASK (0x3800U)
#define MIPI_DSI_PHY_TRIM_PARA_HSTX_AMP_TRIM_SHIFT (11U)
#define MIPI_DSI_PHY_TRIM_PARA_HSTX_AMP_TRIM_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TRIM_PARA_HSTX_AMP_TRIM_SHIFT) & MIPI_DSI_PHY_TRIM_PARA_HSTX_AMP_TRIM_MASK)
#define MIPI_DSI_PHY_TRIM_PARA_HSTX_AMP_TRIM_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TRIM_PARA_HSTX_AMP_TRIM_MASK) >> MIPI_DSI_PHY_TRIM_PARA_HSTX_AMP_TRIM_SHIFT)

/*
 * LPTX_SR_TRIM (RW)
 *
 * lp-tx output slew-rate trimming for lane0~4
 */
#define MIPI_DSI_PHY_TRIM_PARA_LPTX_SR_TRIM_MASK (0x700U)
#define MIPI_DSI_PHY_TRIM_PARA_LPTX_SR_TRIM_SHIFT (8U)
#define MIPI_DSI_PHY_TRIM_PARA_LPTX_SR_TRIM_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TRIM_PARA_LPTX_SR_TRIM_SHIFT) & MIPI_DSI_PHY_TRIM_PARA_LPTX_SR_TRIM_MASK)
#define MIPI_DSI_PHY_TRIM_PARA_LPTX_SR_TRIM_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TRIM_PARA_LPTX_SR_TRIM_MASK) >> MIPI_DSI_PHY_TRIM_PARA_LPTX_SR_TRIM_SHIFT)

/*
 * LPRX_VREF_TRIM (RW)
 *
 * lp-rx input threshold voltage trimming for lane0
 */
#define MIPI_DSI_PHY_TRIM_PARA_LPRX_VREF_TRIM_MASK (0xF0U)
#define MIPI_DSI_PHY_TRIM_PARA_LPRX_VREF_TRIM_SHIFT (4U)
#define MIPI_DSI_PHY_TRIM_PARA_LPRX_VREF_TRIM_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TRIM_PARA_LPRX_VREF_TRIM_SHIFT) & MIPI_DSI_PHY_TRIM_PARA_LPRX_VREF_TRIM_MASK)
#define MIPI_DSI_PHY_TRIM_PARA_LPRX_VREF_TRIM_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TRIM_PARA_LPRX_VREF_TRIM_MASK) >> MIPI_DSI_PHY_TRIM_PARA_LPRX_VREF_TRIM_SHIFT)

/*
 * LPCD_VREF_TRIM (RW)
 *
 * lp-cd input threshold voltage trimming for lane0
 */
#define MIPI_DSI_PHY_TRIM_PARA_LPCD_VREF_TRIM_MASK (0xFU)
#define MIPI_DSI_PHY_TRIM_PARA_LPCD_VREF_TRIM_SHIFT (0U)
#define MIPI_DSI_PHY_TRIM_PARA_LPCD_VREF_TRIM_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TRIM_PARA_LPCD_VREF_TRIM_SHIFT) & MIPI_DSI_PHY_TRIM_PARA_LPCD_VREF_TRIM_MASK)
#define MIPI_DSI_PHY_TRIM_PARA_LPCD_VREF_TRIM_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TRIM_PARA_LPCD_VREF_TRIM_MASK) >> MIPI_DSI_PHY_TRIM_PARA_LPCD_VREF_TRIM_SHIFT)

/* Bitfield definition for register: TEST_PARA0 */
/*
 * ERROR_NUM (RO)
 *
 * the byte num of mismatch data of lane in bist mode
 */
#define MIPI_DSI_PHY_TEST_PARA0_ERROR_NUM_MASK (0x7E0000UL)
#define MIPI_DSI_PHY_TEST_PARA0_ERROR_NUM_SHIFT (17U)
#define MIPI_DSI_PHY_TEST_PARA0_ERROR_NUM_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA0_ERROR_NUM_MASK) >> MIPI_DSI_PHY_TEST_PARA0_ERROR_NUM_SHIFT)

/*
 * BIST_N_DONE (RO)
 *
 * indicate prbs7 bist test is done
 */
#define MIPI_DSI_PHY_TEST_PARA0_BIST_N_DONE_MASK (0x1F000UL)
#define MIPI_DSI_PHY_TEST_PARA0_BIST_N_DONE_SHIFT (12U)
#define MIPI_DSI_PHY_TEST_PARA0_BIST_N_DONE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA0_BIST_N_DONE_MASK) >> MIPI_DSI_PHY_TEST_PARA0_BIST_N_DONE_SHIFT)

/*
 * BIST_N_OK (RO)
 *
 * indicate prbs7 bist test is ok
 */
#define MIPI_DSI_PHY_TEST_PARA0_BIST_N_OK_MASK (0xF80U)
#define MIPI_DSI_PHY_TEST_PARA0_BIST_N_OK_SHIFT (7U)
#define MIPI_DSI_PHY_TEST_PARA0_BIST_N_OK_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA0_BIST_N_OK_MASK) >> MIPI_DSI_PHY_TEST_PARA0_BIST_N_OK_SHIFT)

/*
 * ATEST_EN (RW)
 *
 * analog test signal enable
 */
#define MIPI_DSI_PHY_TEST_PARA0_ATEST_EN_MASK (0x40U)
#define MIPI_DSI_PHY_TEST_PARA0_ATEST_EN_SHIFT (6U)
#define MIPI_DSI_PHY_TEST_PARA0_ATEST_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TEST_PARA0_ATEST_EN_SHIFT) & MIPI_DSI_PHY_TEST_PARA0_ATEST_EN_MASK)
#define MIPI_DSI_PHY_TEST_PARA0_ATEST_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA0_ATEST_EN_MASK) >> MIPI_DSI_PHY_TEST_PARA0_ATEST_EN_SHIFT)

/*
 * ATEST_SEL (RW)
 *
 * analog test signal select
 */
#define MIPI_DSI_PHY_TEST_PARA0_ATEST_SEL_MASK (0x30U)
#define MIPI_DSI_PHY_TEST_PARA0_ATEST_SEL_SHIFT (4U)
#define MIPI_DSI_PHY_TEST_PARA0_ATEST_SEL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TEST_PARA0_ATEST_SEL_SHIFT) & MIPI_DSI_PHY_TEST_PARA0_ATEST_SEL_MASK)
#define MIPI_DSI_PHY_TEST_PARA0_ATEST_SEL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA0_ATEST_SEL_MASK) >> MIPI_DSI_PHY_TEST_PARA0_ATEST_SEL_SHIFT)

/*
 * FSET_EN (RW)
 *
 * enable fast transmission between lp-tx and hs-tx
 */
#define MIPI_DSI_PHY_TEST_PARA0_FSET_EN_MASK (0x8U)
#define MIPI_DSI_PHY_TEST_PARA0_FSET_EN_SHIFT (3U)
#define MIPI_DSI_PHY_TEST_PARA0_FSET_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TEST_PARA0_FSET_EN_SHIFT) & MIPI_DSI_PHY_TEST_PARA0_FSET_EN_MASK)
#define MIPI_DSI_PHY_TEST_PARA0_FSET_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA0_FSET_EN_MASK) >> MIPI_DSI_PHY_TEST_PARA0_FSET_EN_SHIFT)

/*
 * FT_SEL (RW)
 *
 * pt/ft test mode select
 */
#define MIPI_DSI_PHY_TEST_PARA0_FT_SEL_MASK (0x7U)
#define MIPI_DSI_PHY_TEST_PARA0_FT_SEL_SHIFT (0U)
#define MIPI_DSI_PHY_TEST_PARA0_FT_SEL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TEST_PARA0_FT_SEL_SHIFT) & MIPI_DSI_PHY_TEST_PARA0_FT_SEL_MASK)
#define MIPI_DSI_PHY_TEST_PARA0_FT_SEL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA0_FT_SEL_MASK) >> MIPI_DSI_PHY_TEST_PARA0_FT_SEL_SHIFT)

/* Bitfield definition for register: TEST_PARA1 */
/*
 * CHECK_NUM (RW)
 *
 * the byte num of prbs bist check num
 */
#define MIPI_DSI_PHY_TEST_PARA1_CHECK_NUM_MASK (0xFFFFFC00UL)
#define MIPI_DSI_PHY_TEST_PARA1_CHECK_NUM_SHIFT (10U)
#define MIPI_DSI_PHY_TEST_PARA1_CHECK_NUM_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TEST_PARA1_CHECK_NUM_SHIFT) & MIPI_DSI_PHY_TEST_PARA1_CHECK_NUM_MASK)
#define MIPI_DSI_PHY_TEST_PARA1_CHECK_NUM_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA1_CHECK_NUM_MASK) >> MIPI_DSI_PHY_TEST_PARA1_CHECK_NUM_SHIFT)

/*
 * ERR_THRESHOLD (RW)
 *
 * the threshold of prbs bit error
 */
#define MIPI_DSI_PHY_TEST_PARA1_ERR_THRESHOLD_MASK (0x3C0U)
#define MIPI_DSI_PHY_TEST_PARA1_ERR_THRESHOLD_SHIFT (6U)
#define MIPI_DSI_PHY_TEST_PARA1_ERR_THRESHOLD_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TEST_PARA1_ERR_THRESHOLD_SHIFT) & MIPI_DSI_PHY_TEST_PARA1_ERR_THRESHOLD_MASK)
#define MIPI_DSI_PHY_TEST_PARA1_ERR_THRESHOLD_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA1_ERR_THRESHOLD_MASK) >> MIPI_DSI_PHY_TEST_PARA1_ERR_THRESHOLD_SHIFT)

/*
 * BIST_BIT_ERROR (RW)
 *
 * enable insert error in bist test pattern
 */
#define MIPI_DSI_PHY_TEST_PARA1_BIST_BIT_ERROR_MASK (0x20U)
#define MIPI_DSI_PHY_TEST_PARA1_BIST_BIT_ERROR_SHIFT (5U)
#define MIPI_DSI_PHY_TEST_PARA1_BIST_BIT_ERROR_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TEST_PARA1_BIST_BIT_ERROR_SHIFT) & MIPI_DSI_PHY_TEST_PARA1_BIST_BIT_ERROR_MASK)
#define MIPI_DSI_PHY_TEST_PARA1_BIST_BIT_ERROR_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA1_BIST_BIT_ERROR_MASK) >> MIPI_DSI_PHY_TEST_PARA1_BIST_BIT_ERROR_SHIFT)

/*
 * BIST_EN (RW)
 *
 * bist enable
 */
#define MIPI_DSI_PHY_TEST_PARA1_BIST_EN_MASK (0x18U)
#define MIPI_DSI_PHY_TEST_PARA1_BIST_EN_SHIFT (3U)
#define MIPI_DSI_PHY_TEST_PARA1_BIST_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TEST_PARA1_BIST_EN_SHIFT) & MIPI_DSI_PHY_TEST_PARA1_BIST_EN_MASK)
#define MIPI_DSI_PHY_TEST_PARA1_BIST_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA1_BIST_EN_MASK) >> MIPI_DSI_PHY_TEST_PARA1_BIST_EN_SHIFT)

/*
 * BIST_SEL (RW)
 *
 * bist mode select
 */
#define MIPI_DSI_PHY_TEST_PARA1_BIST_SEL_MASK (0x4U)
#define MIPI_DSI_PHY_TEST_PARA1_BIST_SEL_SHIFT (2U)
#define MIPI_DSI_PHY_TEST_PARA1_BIST_SEL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TEST_PARA1_BIST_SEL_SHIFT) & MIPI_DSI_PHY_TEST_PARA1_BIST_SEL_MASK)
#define MIPI_DSI_PHY_TEST_PARA1_BIST_SEL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA1_BIST_SEL_MASK) >> MIPI_DSI_PHY_TEST_PARA1_BIST_SEL_SHIFT)

/*
 * PRBS_SEL (RW)
 *
 * prbs generator and checker pattern select signal
 */
#define MIPI_DSI_PHY_TEST_PARA1_PRBS_SEL_MASK (0x3U)
#define MIPI_DSI_PHY_TEST_PARA1_PRBS_SEL_SHIFT (0U)
#define MIPI_DSI_PHY_TEST_PARA1_PRBS_SEL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TEST_PARA1_PRBS_SEL_SHIFT) & MIPI_DSI_PHY_TEST_PARA1_PRBS_SEL_MASK)
#define MIPI_DSI_PHY_TEST_PARA1_PRBS_SEL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TEST_PARA1_PRBS_SEL_MASK) >> MIPI_DSI_PHY_TEST_PARA1_PRBS_SEL_SHIFT)

/* Bitfield definition for register: MISC_PARA */
/*
 * DLL_SEL (RW)
 *
 * the phase select of clk_rxesc
 */
#define MIPI_DSI_PHY_MISC_PARA_DLL_SEL_MASK (0x780U)
#define MIPI_DSI_PHY_MISC_PARA_DLL_SEL_SHIFT (7U)
#define MIPI_DSI_PHY_MISC_PARA_DLL_SEL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_MISC_PARA_DLL_SEL_SHIFT) & MIPI_DSI_PHY_MISC_PARA_DLL_SEL_MASK)
#define MIPI_DSI_PHY_MISC_PARA_DLL_SEL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_MISC_PARA_DLL_SEL_MASK) >> MIPI_DSI_PHY_MISC_PARA_DLL_SEL_SHIFT)

/*
 * LANE_NUM (RW)
 *
 * the number of active data lanes
 */
#define MIPI_DSI_PHY_MISC_PARA_LANE_NUM_MASK (0x60U)
#define MIPI_DSI_PHY_MISC_PARA_LANE_NUM_SHIFT (5U)
#define MIPI_DSI_PHY_MISC_PARA_LANE_NUM_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_MISC_PARA_LANE_NUM_SHIFT) & MIPI_DSI_PHY_MISC_PARA_LANE_NUM_MASK)
#define MIPI_DSI_PHY_MISC_PARA_LANE_NUM_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_MISC_PARA_LANE_NUM_MASK) >> MIPI_DSI_PHY_MISC_PARA_LANE_NUM_SHIFT)

/*
 * PHYERR_MASK (RW)
 *
 * mask the phy error
 */
#define MIPI_DSI_PHY_MISC_PARA_PHYERR_MASK_MASK (0x1FU)
#define MIPI_DSI_PHY_MISC_PARA_PHYERR_MASK_SHIFT (0U)
#define MIPI_DSI_PHY_MISC_PARA_PHYERR_MASK_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_MISC_PARA_PHYERR_MASK_SHIFT) & MIPI_DSI_PHY_MISC_PARA_PHYERR_MASK_MASK)
#define MIPI_DSI_PHY_MISC_PARA_PHYERR_MASK_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_MISC_PARA_PHYERR_MASK_MASK) >> MIPI_DSI_PHY_MISC_PARA_PHYERR_MASK_SHIFT)

/* Bitfield definition for register: CLANE_PARA4 */
/*
 * T_WAKEUP_C (RW)
 *
 * the number of byteclk cycles from exiting ultra low power state to enabling the low-power driver
 */
#define MIPI_DSI_PHY_CLANE_PARA4_T_WAKEUP_C_MASK (0xFFFFFFFFUL)
#define MIPI_DSI_PHY_CLANE_PARA4_T_WAKEUP_C_SHIFT (0U)
#define MIPI_DSI_PHY_CLANE_PARA4_T_WAKEUP_C_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CLANE_PARA4_T_WAKEUP_C_SHIFT) & MIPI_DSI_PHY_CLANE_PARA4_T_WAKEUP_C_MASK)
#define MIPI_DSI_PHY_CLANE_PARA4_T_WAKEUP_C_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CLANE_PARA4_T_WAKEUP_C_MASK) >> MIPI_DSI_PHY_CLANE_PARA4_T_WAKEUP_C_SHIFT)

/* Bitfield definition for register: INTERFACE_PARA */
/*
 * TXREADYESC_EXTEND_VLD (RW)
 *
 * the extend length of txreadyesc
 */
#define MIPI_DSI_PHY_INTERFACE_PARA_TXREADYESC_EXTEND_VLD_MASK (0xFF00U)
#define MIPI_DSI_PHY_INTERFACE_PARA_TXREADYESC_EXTEND_VLD_SHIFT (8U)
#define MIPI_DSI_PHY_INTERFACE_PARA_TXREADYESC_EXTEND_VLD_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_INTERFACE_PARA_TXREADYESC_EXTEND_VLD_SHIFT) & MIPI_DSI_PHY_INTERFACE_PARA_TXREADYESC_EXTEND_VLD_MASK)
#define MIPI_DSI_PHY_INTERFACE_PARA_TXREADYESC_EXTEND_VLD_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_INTERFACE_PARA_TXREADYESC_EXTEND_VLD_MASK) >> MIPI_DSI_PHY_INTERFACE_PARA_TXREADYESC_EXTEND_VLD_SHIFT)

/*
 * RXVALIDESC_EXTEND_VLD (RW)
 *
 * the extend length of rxvalidesc
 */
#define MIPI_DSI_PHY_INTERFACE_PARA_RXVALIDESC_EXTEND_VLD_MASK (0xFFU)
#define MIPI_DSI_PHY_INTERFACE_PARA_RXVALIDESC_EXTEND_VLD_SHIFT (0U)
#define MIPI_DSI_PHY_INTERFACE_PARA_RXVALIDESC_EXTEND_VLD_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_INTERFACE_PARA_RXVALIDESC_EXTEND_VLD_SHIFT) & MIPI_DSI_PHY_INTERFACE_PARA_RXVALIDESC_EXTEND_VLD_MASK)
#define MIPI_DSI_PHY_INTERFACE_PARA_RXVALIDESC_EXTEND_VLD_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_INTERFACE_PARA_RXVALIDESC_EXTEND_VLD_MASK) >> MIPI_DSI_PHY_INTERFACE_PARA_RXVALIDESC_EXTEND_VLD_SHIFT)

/* Bitfield definition for register: PCS_RESERVED_PIN_PARA */
/*
 * CLK_TXHS_SEL_INNER (RW)
 *
 * select the clock source of clk_txhs in pcs
 */
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_CLK_TXHS_SEL_INNER_MASK (0x10U)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_CLK_TXHS_SEL_INNER_SHIFT (4U)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_CLK_TXHS_SEL_INNER_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_CLK_TXHS_SEL_INNER_SHIFT) & MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_CLK_TXHS_SEL_INNER_MASK)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_CLK_TXHS_SEL_INNER_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_CLK_TXHS_SEL_INNER_MASK) >> MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_CLK_TXHS_SEL_INNER_SHIFT)

/*
 * INV_CLK_TXHS (RW)
 *
 * clk_txhs inverter signal
 */
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXHS_MASK (0x8U)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXHS_SHIFT (3U)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXHS_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXHS_SHIFT) & MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXHS_MASK)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXHS_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXHS_MASK) >> MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXHS_SHIFT)

/*
 * INV_CLK_TXESC (RW)
 *
 * clk_txesc inverter signal
 */
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXESC_MASK (0x4U)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXESC_SHIFT (2U)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXESC_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXESC_SHIFT) & MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXESC_MASK)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXESC_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXESC_MASK) >> MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_CLK_TXESC_SHIFT)

/*
 * INV_PCLK (RW)
 *
 * pclk inverter signal
 */
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_PCLK_MASK (0x2U)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_PCLK_SHIFT (1U)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_PCLK_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_PCLK_SHIFT) & MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_PCLK_MASK)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_PCLK_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_PCLK_MASK) >> MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_PCLK_SHIFT)

/*
 * INV_DSI_RCLK (RW)
 *
 * pma clock dsi_rclk_i inverter signal
 */
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_DSI_RCLK_MASK (0x1U)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_DSI_RCLK_SHIFT (0U)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_DSI_RCLK_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_DSI_RCLK_SHIFT) & MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_DSI_RCLK_MASK)
#define MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_DSI_RCLK_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_DSI_RCLK_MASK) >> MIPI_DSI_PHY_PCS_RESERVED_PIN_PARA_INV_DSI_RCLK_SHIFT)

/* Bitfield definition for register: CLANE_DATA_PARA */
/*
 * CLANE_DATA_SEL (RW)
 *
 * select the data about clock lane
 */
#define MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SEL_MASK (0x100U)
#define MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SEL_SHIFT (8U)
#define MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SEL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SEL_SHIFT) & MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SEL_MASK)
#define MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SEL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SEL_MASK) >> MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SEL_SHIFT)

/*
 * CLANE_DATA (RW)
 *
 * the parallel data about clock lane
 */
#define MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_MASK (0xFFU)
#define MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SHIFT (0U)
#define MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SHIFT) & MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_MASK)
#define MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_MASK) >> MIPI_DSI_PHY_CLANE_DATA_PARA_CLANE_DATA_SHIFT)

/* Bitfield definition for register: PMA_LANE_SEL_PARA */
/*
 * PMA_DLANE4_SEL (RW)
 *
 * select the channel 4 as the data lane
 */
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE4_SEL_MASK (0x8U)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE4_SEL_SHIFT (3U)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE4_SEL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE4_SEL_SHIFT) & MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE4_SEL_MASK)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE4_SEL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE4_SEL_MASK) >> MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE4_SEL_SHIFT)

/*
 * PMA_DLANE3_SEL (RW)
 *
 * select the channel 3 as the data lane
 */
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE3_SEL_MASK (0x4U)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE3_SEL_SHIFT (2U)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE3_SEL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE3_SEL_SHIFT) & MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE3_SEL_MASK)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE3_SEL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE3_SEL_MASK) >> MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE3_SEL_SHIFT)

/*
 * PMA_DLANE2_SEL (RW)
 *
 * select the channel 2 as the data lane
 */
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE2_SEL_MASK (0x2U)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE2_SEL_SHIFT (1U)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE2_SEL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE2_SEL_SHIFT) & MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE2_SEL_MASK)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE2_SEL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE2_SEL_MASK) >> MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE2_SEL_SHIFT)

/*
 * PMA_DLANE1_SEL (RW)
 *
 * select the channel 1 as the data lane
 */
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE1_SEL_MASK (0x1U)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE1_SEL_SHIFT (0U)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE1_SEL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE1_SEL_SHIFT) & MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE1_SEL_MASK)
#define MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE1_SEL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE1_SEL_MASK) >> MIPI_DSI_PHY_PMA_LANE_SEL_PARA_PMA_DLANE1_SEL_SHIFT)




#endif /* HPM_MIPI_DSI_PHY_H */
