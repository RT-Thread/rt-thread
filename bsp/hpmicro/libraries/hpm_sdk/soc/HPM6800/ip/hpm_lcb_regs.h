/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_LCB_H
#define HPM_LCB_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0: control register */
    __R  uint8_t  RESERVED0[96];               /* 0x4 - 0x63: Reserved */
    __R  uint32_t PHY_STAT;                    /* 0x64: LVDS RX PHY Status register */
    __RW uint32_t PHY_POW_CTRL[2];             /* 0x68 - 0x6C: LVDS0 PHY power control register */
    __RW uint32_t PHY_D_CTRL[4];               /* 0x70 - 0x7C: LVDS0 PHY Data Channel RX0 Setting */
    __RW uint32_t PHY_CK_CTRL[2];              /* 0x80 - 0x84: LVDS0 PHY CK Channel Setting */
    __RW uint32_t PHY_ADJ_CTRL[2];             /* 0x88 - 0x8C: LVDS0 PHY ADJ Setting */
    __RW uint32_t PHY_SU_CTRL[2];              /* 0x90 - 0x94: LVDS0 PHY SU CTRL */
} LCB_Type;


/* Bitfield definition for register: CTRL */
/*
 * LVDS_RXCK_SEL (RW)
 *
 * just for LVDS Display mode and CAM LINK mode,  clock selection:
 * 1: LVDS1 RXCK
 * 0: LVDS0 RXCK
 */
#define LCB_CTRL_LVDS_RXCK_SEL_MASK (0x100U)
#define LCB_CTRL_LVDS_RXCK_SEL_SHIFT (8U)
#define LCB_CTRL_LVDS_RXCK_SEL_SET(x) (((uint32_t)(x) << LCB_CTRL_LVDS_RXCK_SEL_SHIFT) & LCB_CTRL_LVDS_RXCK_SEL_MASK)
#define LCB_CTRL_LVDS_RXCK_SEL_GET(x) (((uint32_t)(x) & LCB_CTRL_LVDS_RXCK_SEL_MASK) >> LCB_CTRL_LVDS_RXCK_SEL_SHIFT)

/*
 * CAM_LINK_WIDTH (RW)
 *
 * just for CAM LINK mode,  data width:
 * 00: 24bit
 * 01: 30bit
 * 10: 36bit
 * 11: reserved
 */
#define LCB_CTRL_CAM_LINK_WIDTH_MASK (0xC0U)
#define LCB_CTRL_CAM_LINK_WIDTH_SHIFT (6U)
#define LCB_CTRL_CAM_LINK_WIDTH_SET(x) (((uint32_t)(x) << LCB_CTRL_CAM_LINK_WIDTH_SHIFT) & LCB_CTRL_CAM_LINK_WIDTH_MASK)
#define LCB_CTRL_CAM_LINK_WIDTH_GET(x) (((uint32_t)(x) & LCB_CTRL_CAM_LINK_WIDTH_MASK) >> LCB_CTRL_CAM_LINK_WIDTH_SHIFT)

/*
 * BIT_MAPPING (RW)
 *
 * just for LVDS Display mode,  data protocol:
 * 1: JEIDA standard
 * 0: SPWG standard
 */
#define LCB_CTRL_BIT_MAPPING_MASK (0x20U)
#define LCB_CTRL_BIT_MAPPING_SHIFT (5U)
#define LCB_CTRL_BIT_MAPPING_SET(x) (((uint32_t)(x) << LCB_CTRL_BIT_MAPPING_SHIFT) & LCB_CTRL_BIT_MAPPING_MASK)
#define LCB_CTRL_BIT_MAPPING_GET(x) (((uint32_t)(x) & LCB_CTRL_BIT_MAPPING_MASK) >> LCB_CTRL_BIT_MAPPING_SHIFT)

/*
 * DATA_WIDTH (RW)
 *
 * just for LVDS Display mode,  data width:
 * 1: 24bit
 * 0: 18bit(3line)
 */
#define LCB_CTRL_DATA_WIDTH_MASK (0x10U)
#define LCB_CTRL_DATA_WIDTH_SHIFT (4U)
#define LCB_CTRL_DATA_WIDTH_SET(x) (((uint32_t)(x) << LCB_CTRL_DATA_WIDTH_SHIFT) & LCB_CTRL_DATA_WIDTH_MASK)
#define LCB_CTRL_DATA_WIDTH_GET(x) (((uint32_t)(x) & LCB_CTRL_DATA_WIDTH_MASK) >> LCB_CTRL_DATA_WIDTH_SHIFT)

/*
 * MODE (RW)
 *
 * mode selection：
 * 00: lvds display(4 line), two LVDS RX PHY must be LVDS display mode
 * 01: cam link(4 line), two LVDS RX PHY must be LVDS display mode
 * 10: sync code(2 line), LVDS RX PHY must be LVDS cameral mode
 * 11: sync code(1line), LVDS RX PHY must be LVDS cameral mode
 */
#define LCB_CTRL_MODE_MASK (0x3U)
#define LCB_CTRL_MODE_SHIFT (0U)
#define LCB_CTRL_MODE_SET(x) (((uint32_t)(x) << LCB_CTRL_MODE_SHIFT) & LCB_CTRL_MODE_MASK)
#define LCB_CTRL_MODE_GET(x) (((uint32_t)(x) & LCB_CTRL_MODE_MASK) >> LCB_CTRL_MODE_SHIFT)

/* Bitfield definition for register: PHY_STAT */
/*
 * LVDS1_RX_PHY_DLL_LOCK (RO)
 *
 * LVDS1 RX PHY DLL Lock indication Signal, 1 means dll already locked
 */
#define LCB_PHY_STAT_LVDS1_RX_PHY_DLL_LOCK_MASK (0x2U)
#define LCB_PHY_STAT_LVDS1_RX_PHY_DLL_LOCK_SHIFT (1U)
#define LCB_PHY_STAT_LVDS1_RX_PHY_DLL_LOCK_GET(x) (((uint32_t)(x) & LCB_PHY_STAT_LVDS1_RX_PHY_DLL_LOCK_MASK) >> LCB_PHY_STAT_LVDS1_RX_PHY_DLL_LOCK_SHIFT)

/*
 * LVDS0_RX_PHY_DLL_LOCK (RO)
 *
 * LVDS0 RX PHY DLL Lock indication Signal, 1 means dll already locked
 */
#define LCB_PHY_STAT_LVDS0_RX_PHY_DLL_LOCK_MASK (0x1U)
#define LCB_PHY_STAT_LVDS0_RX_PHY_DLL_LOCK_SHIFT (0U)
#define LCB_PHY_STAT_LVDS0_RX_PHY_DLL_LOCK_GET(x) (((uint32_t)(x) & LCB_PHY_STAT_LVDS0_RX_PHY_DLL_LOCK_MASK) >> LCB_PHY_STAT_LVDS0_RX_PHY_DLL_LOCK_SHIFT)

/* Bitfield definition for register array: PHY_POW_CTRL */
/*
 * IDDQ_EN (RW)
 *
 * Power down control signal of channel rxck/rx1/rx0
 * 0: Normal operation
 * 1: Power down channel
 */
#define LCB_PHY_POW_CTRL_IDDQ_EN_MASK (0x8U)
#define LCB_PHY_POW_CTRL_IDDQ_EN_SHIFT (3U)
#define LCB_PHY_POW_CTRL_IDDQ_EN_SET(x) (((uint32_t)(x) << LCB_PHY_POW_CTRL_IDDQ_EN_SHIFT) & LCB_PHY_POW_CTRL_IDDQ_EN_MASK)
#define LCB_PHY_POW_CTRL_IDDQ_EN_GET(x) (((uint32_t)(x) & LCB_PHY_POW_CTRL_IDDQ_EN_MASK) >> LCB_PHY_POW_CTRL_IDDQ_EN_SHIFT)

/*
 * RXCK_PD (RW)
 *
 * Power down control signal of channel rxck
 * 0: Normal operation
 * 1: Power down channel
 */
#define LCB_PHY_POW_CTRL_RXCK_PD_MASK (0x4U)
#define LCB_PHY_POW_CTRL_RXCK_PD_SHIFT (2U)
#define LCB_PHY_POW_CTRL_RXCK_PD_SET(x) (((uint32_t)(x) << LCB_PHY_POW_CTRL_RXCK_PD_SHIFT) & LCB_PHY_POW_CTRL_RXCK_PD_MASK)
#define LCB_PHY_POW_CTRL_RXCK_PD_GET(x) (((uint32_t)(x) & LCB_PHY_POW_CTRL_RXCK_PD_MASK) >> LCB_PHY_POW_CTRL_RXCK_PD_SHIFT)

/*
 * RX1_PD (RW)
 *
 * Power down control signal of channel rx1
 * 0: Normal operation
 * 1: Power down channel
 */
#define LCB_PHY_POW_CTRL_RX1_PD_MASK (0x2U)
#define LCB_PHY_POW_CTRL_RX1_PD_SHIFT (1U)
#define LCB_PHY_POW_CTRL_RX1_PD_SET(x) (((uint32_t)(x) << LCB_PHY_POW_CTRL_RX1_PD_SHIFT) & LCB_PHY_POW_CTRL_RX1_PD_MASK)
#define LCB_PHY_POW_CTRL_RX1_PD_GET(x) (((uint32_t)(x) & LCB_PHY_POW_CTRL_RX1_PD_MASK) >> LCB_PHY_POW_CTRL_RX1_PD_SHIFT)

/*
 * RX0_PD (RW)
 *
 * Power down control signal of channel rx0
 * 0: Normal operation
 * 1: Power down channel
 */
#define LCB_PHY_POW_CTRL_RX0_PD_MASK (0x1U)
#define LCB_PHY_POW_CTRL_RX0_PD_SHIFT (0U)
#define LCB_PHY_POW_CTRL_RX0_PD_SET(x) (((uint32_t)(x) << LCB_PHY_POW_CTRL_RX0_PD_SHIFT) & LCB_PHY_POW_CTRL_RX0_PD_MASK)
#define LCB_PHY_POW_CTRL_RX0_PD_GET(x) (((uint32_t)(x) & LCB_PHY_POW_CTRL_RX0_PD_MASK) >> LCB_PHY_POW_CTRL_RX0_PD_SHIFT)

/* Bitfield definition for register array: PHY_D_CTRL */
/*
 * RX_VCOM (RW)
 *
 * bit 1: Receiver hysteresis enable signal. 0: enable; 1: disable
 * bit 0: Terminal impedance common mode selection control signal. 0: floating; 1: Ground
 */
#define LCB_PHY_D_CTRL_RX_VCOM_MASK (0x300000UL)
#define LCB_PHY_D_CTRL_RX_VCOM_SHIFT (20U)
#define LCB_PHY_D_CTRL_RX_VCOM_SET(x) (((uint32_t)(x) << LCB_PHY_D_CTRL_RX_VCOM_SHIFT) & LCB_PHY_D_CTRL_RX_VCOM_MASK)
#define LCB_PHY_D_CTRL_RX_VCOM_GET(x) (((uint32_t)(x) & LCB_PHY_D_CTRL_RX_VCOM_MASK) >> LCB_PHY_D_CTRL_RX_VCOM_SHIFT)

/*
 * RX_RTERM (RW)
 *
 * Terminal impedance regulation control signal
 * 0000: hi-z;
 * 0001: 150ohm;
 * 1000:100ohm;
 * 1111:75ohm
 */
#define LCB_PHY_D_CTRL_RX_RTERM_MASK (0xF0000UL)
#define LCB_PHY_D_CTRL_RX_RTERM_SHIFT (16U)
#define LCB_PHY_D_CTRL_RX_RTERM_SET(x) (((uint32_t)(x) << LCB_PHY_D_CTRL_RX_RTERM_SHIFT) & LCB_PHY_D_CTRL_RX_RTERM_MASK)
#define LCB_PHY_D_CTRL_RX_RTERM_GET(x) (((uint32_t)(x) & LCB_PHY_D_CTRL_RX_RTERM_MASK) >> LCB_PHY_D_CTRL_RX_RTERM_SHIFT)

/*
 * RX_CTL (RW)
 *
 * bit 0 :  Lane N Data MSB first enable signal. 0: LSB ; 1: MSB
 * bit 1 :  Lane N Data Polarity signal. 0: Not inverting; 1: Inverting
 * bit [4:2] : Phase difference between the output first bit data (rxN[6:0]) and the input clock (RCKP/N) in LVDS Display Mode.
 * bit 5 : Reserved
 * bit 6 : Output data sampling clock control signal
 * 0: Sampling using the rising edge of the clock pck.
 * 1: Sampling using the falling edge of the clock pck.
 * bit 7 : Reserved
 * bit 8 : Data Lane N Skew adjust enable in LVDS Camera Mode.
 * bit [12:9] : Data Lane N Skew adjust; 0000: min; 0111: default; 1111: max.
 * bit [15:13] : Reserved
 */
#define LCB_PHY_D_CTRL_RX_CTL_MASK (0xFFFFU)
#define LCB_PHY_D_CTRL_RX_CTL_SHIFT (0U)
#define LCB_PHY_D_CTRL_RX_CTL_SET(x) (((uint32_t)(x) << LCB_PHY_D_CTRL_RX_CTL_SHIFT) & LCB_PHY_D_CTRL_RX_CTL_MASK)
#define LCB_PHY_D_CTRL_RX_CTL_GET(x) (((uint32_t)(x) & LCB_PHY_D_CTRL_RX_CTL_MASK) >> LCB_PHY_D_CTRL_RX_CTL_SHIFT)

/* Bitfield definition for register array: PHY_CK_CTRL */
/*
 * RX_VCOM (RW)
 *
 * bit 1: Receiver hysteresis enable signal. 0: enable; 1: disable
 * bit 0: Terminal impedance common mode selection control signal. 0: floating; 1: Ground
 */
#define LCB_PHY_CK_CTRL_RX_VCOM_MASK (0x300000UL)
#define LCB_PHY_CK_CTRL_RX_VCOM_SHIFT (20U)
#define LCB_PHY_CK_CTRL_RX_VCOM_SET(x) (((uint32_t)(x) << LCB_PHY_CK_CTRL_RX_VCOM_SHIFT) & LCB_PHY_CK_CTRL_RX_VCOM_MASK)
#define LCB_PHY_CK_CTRL_RX_VCOM_GET(x) (((uint32_t)(x) & LCB_PHY_CK_CTRL_RX_VCOM_MASK) >> LCB_PHY_CK_CTRL_RX_VCOM_SHIFT)

/*
 * RX_RTERM (RW)
 *
 * Terminal impedance regulation control signal
 * 0000: hi-z;
 * 0001: 150ohm;
 * 1000:100ohm;
 * 1111:75ohm
 */
#define LCB_PHY_CK_CTRL_RX_RTERM_MASK (0xF0000UL)
#define LCB_PHY_CK_CTRL_RX_RTERM_SHIFT (16U)
#define LCB_PHY_CK_CTRL_RX_RTERM_SET(x) (((uint32_t)(x) << LCB_PHY_CK_CTRL_RX_RTERM_SHIFT) & LCB_PHY_CK_CTRL_RX_RTERM_MASK)
#define LCB_PHY_CK_CTRL_RX_RTERM_GET(x) (((uint32_t)(x) & LCB_PHY_CK_CTRL_RX_RTERM_MASK) >> LCB_PHY_CK_CTRL_RX_RTERM_SHIFT)

/*
 * RX_CTL (RW)
 *
 * bit 0 : DLL loop delay adjustment minimum control signal
 * 0: used for RCKP/RCKN’s frequency is 40Mhz~70Mhz
 * 1:used for RCKP/RCKN’s frequency is 70Mhz~110Mhz
 * bit [2:1] : DLL loop delay adjustment current regulation control signal. 00: min; 11: max
 * bit 3 : Reserved
 * bit 4 : Clock Lane Skew adjust enable in LVDS Camera Mode.
 * bit [7:5] : Bus width selection in LVDS Camera Mode
 * 000: 4bit; 001:6bit; 010:7bit; 011:8bit; 100:9bit; 101:10bit; 110:11bit; 111:12bit.
 * bit [10:8] : DDR Clock duty cycle adjust in LVDS Camera Mode.
 * bit [15:11] : Reserved
 */
#define LCB_PHY_CK_CTRL_RX_CTL_MASK (0xFFFFU)
#define LCB_PHY_CK_CTRL_RX_CTL_SHIFT (0U)
#define LCB_PHY_CK_CTRL_RX_CTL_SET(x) (((uint32_t)(x) << LCB_PHY_CK_CTRL_RX_CTL_SHIFT) & LCB_PHY_CK_CTRL_RX_CTL_MASK)
#define LCB_PHY_CK_CTRL_RX_CTL_GET(x) (((uint32_t)(x) & LCB_PHY_CK_CTRL_RX_CTL_MASK) >> LCB_PHY_CK_CTRL_RX_CTL_SHIFT)

/* Bitfield definition for register array: PHY_ADJ_CTRL */
/*
 * LVDS_RX0_DLINE_ADJ (RW)
 *
 * LVDS RX PHY RX0 line:
 * bit [7:0] : Lane N skew adjustment control signal between data and clock
 * 0000000: max; 1111111: min
 * bit 8 : Reserved
 */
#define LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_MASK (0xFF000000UL)
#define LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_SHIFT (24U)
#define LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_SET(x) (((uint32_t)(x) << LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_SHIFT) & LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_MASK)
#define LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_GET(x) (((uint32_t)(x) & LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_MASK) >> LCB_PHY_ADJ_CTRL_LVDS_RX0_DLINE_ADJ_SHIFT)

/*
 * LVDS_RX1_DLINE_ADJ (RW)
 *
 * LVDS RX PHY RX1 line:
 * bit [7:0] : Lane N skew adjustment control signal between data and clock
 * 0000000: max; 1111111: min
 * bit 8 : Reserved
 */
#define LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_MASK (0xFF0000UL)
#define LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_SHIFT (16U)
#define LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_SET(x) (((uint32_t)(x) << LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_SHIFT) & LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_MASK)
#define LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_GET(x) (((uint32_t)(x) & LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_MASK) >> LCB_PHY_ADJ_CTRL_LVDS_RX1_DLINE_ADJ_SHIFT)

/*
 * LVDS_DLL_TUNING_INT (RW)
 *
 * LVDS RX PHY RXCK line:
 * DLL loop delay coarse adjustment initial signal
 * 00000000: min ; 11111111: max
 */
#define LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_MASK (0x1FFU)
#define LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_SHIFT (0U)
#define LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_SET(x) (((uint32_t)(x) << LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_SHIFT) & LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_MASK)
#define LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_GET(x) (((uint32_t)(x) & LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_MASK) >> LCB_PHY_ADJ_CTRL_LVDS_DLL_TUNING_INT_SHIFT)

/* Bitfield definition for register array: PHY_SU_CTRL */
/*
 * SU_CTRL (RW)
 *
 * bit [2:0] : Reference voltage/current adjustment control signal. 000: min; 111: max
 * bit [3] : Internal bias circuit selection signal. 0: from Bandgap Mode; 1: from self-bias mode
 * bit [7:4] : Reserved
 */
#define LCB_PHY_SU_CTRL_SU_CTRL_MASK (0xFFU)
#define LCB_PHY_SU_CTRL_SU_CTRL_SHIFT (0U)
#define LCB_PHY_SU_CTRL_SU_CTRL_SET(x) (((uint32_t)(x) << LCB_PHY_SU_CTRL_SU_CTRL_SHIFT) & LCB_PHY_SU_CTRL_SU_CTRL_MASK)
#define LCB_PHY_SU_CTRL_SU_CTRL_GET(x) (((uint32_t)(x) & LCB_PHY_SU_CTRL_SU_CTRL_MASK) >> LCB_PHY_SU_CTRL_SU_CTRL_SHIFT)



/* PHY_POW_CTRL register group index macro definition */
#define LCB_PHY_POW_CTRL_LVDS0 (0UL)
#define LCB_PHY_POW_CTRL_LVDS1 (1UL)

/* PHY_D_CTRL register group index macro definition */
#define LCB_PHY_D_CTRL_LVDS0_RX0 (0UL)
#define LCB_PHY_D_CTRL_LVDS0_RX1 (1UL)
#define LCB_PHY_D_CTRL_LVDS1_RX0 (2UL)
#define LCB_PHY_D_CTRL_LVDS1_RX1 (3UL)

/* PHY_CK_CTRL register group index macro definition */
#define LCB_PHY_CK_CTRL_LVDS0_RXCK (0UL)
#define LCB_PHY_CK_CTRL_LVDS1_RXCK (1UL)

/* PHY_ADJ_CTRL register group index macro definition */
#define LCB_PHY_ADJ_CTRL_LVDS0 (0UL)
#define LCB_PHY_ADJ_CTRL_LVDS1 (1UL)

/* PHY_SU_CTRL register group index macro definition */
#define LCB_PHY_SU_CTRL_LVDS0 (0UL)
#define LCB_PHY_SU_CTRL_LVDS1 (1UL)


#endif /* HPM_LCB_H */
