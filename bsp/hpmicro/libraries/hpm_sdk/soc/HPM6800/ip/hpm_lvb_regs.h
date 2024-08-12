/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_LVB_H
#define HPM_LVB_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0: control register */
    __R  uint8_t  RESERVED0[12];               /* 0x4 - 0xF: Reserved */
    __R  uint32_t PHY_STAT;                    /* 0x10: LVDS TX PHY Status register */
    __RW uint32_t PHY_POW_CTRL[2];             /* 0x14 - 0x18: LVDS0 PHY power control register */
    struct {
        __RW uint32_t CTL0;                    /* 0x1C: TX PHY Setting */
        __RW uint32_t CTL1;                    /* 0x20: TX_PHY Setting */
    } TX_PHY[10];
} LVB_Type;


/* Bitfield definition for register: CTRL */
/*
 * SPLIT_CH_REVERSE (RW)
 *
 * Just for split mode, reverse two channel data
 */
#define LVB_CTRL_SPLIT_CH_REVERSE_MASK (0x8000000UL)
#define LVB_CTRL_SPLIT_CH_REVERSE_SHIFT (27U)
#define LVB_CTRL_SPLIT_CH_REVERSE_SET(x) (((uint32_t)(x) << LVB_CTRL_SPLIT_CH_REVERSE_SHIFT) & LVB_CTRL_SPLIT_CH_REVERSE_MASK)
#define LVB_CTRL_SPLIT_CH_REVERSE_GET(x) (((uint32_t)(x) & LVB_CTRL_SPLIT_CH_REVERSE_MASK) >> LVB_CTRL_SPLIT_CH_REVERSE_SHIFT)

/*
 * SPLIT_CH_MODE (RW)
 *
 * Just for split mode
 * 1: two channel pixel data are not aligned
 * 0: two channel pixel data are  aligned
 */
#define LVB_CTRL_SPLIT_CH_MODE_MASK (0x4000000UL)
#define LVB_CTRL_SPLIT_CH_MODE_SHIFT (26U)
#define LVB_CTRL_SPLIT_CH_MODE_SET(x) (((uint32_t)(x) << LVB_CTRL_SPLIT_CH_MODE_SHIFT) & LVB_CTRL_SPLIT_CH_MODE_MASK)
#define LVB_CTRL_SPLIT_CH_MODE_GET(x) (((uint32_t)(x) & LVB_CTRL_SPLIT_CH_MODE_MASK) >> LVB_CTRL_SPLIT_CH_MODE_SHIFT)

/*
 * SPLIT_HSWHBP_WIDTH (RW)
 *
 * Just for split mode, the sum of HSW and HBP width is even
 * 1: yes
 * 0: no
 */
#define LVB_CTRL_SPLIT_HSWHBP_WIDTH_MASK (0x2000000UL)
#define LVB_CTRL_SPLIT_HSWHBP_WIDTH_SHIFT (25U)
#define LVB_CTRL_SPLIT_HSWHBP_WIDTH_SET(x) (((uint32_t)(x) << LVB_CTRL_SPLIT_HSWHBP_WIDTH_SHIFT) & LVB_CTRL_SPLIT_HSWHBP_WIDTH_MASK)
#define LVB_CTRL_SPLIT_HSWHBP_WIDTH_GET(x) (((uint32_t)(x) & LVB_CTRL_SPLIT_HSWHBP_WIDTH_MASK) >> LVB_CTRL_SPLIT_HSWHBP_WIDTH_SHIFT)

/*
 * SPLIT_MODE_EN (RW)
 *
 * Split mode enable:
 * 1: enable
 * 0: disable
 * Note: when using split mode, ch0/1 should be enabled, and should select same DI
 */
#define LVB_CTRL_SPLIT_MODE_EN_MASK (0x1000000UL)
#define LVB_CTRL_SPLIT_MODE_EN_SHIFT (24U)
#define LVB_CTRL_SPLIT_MODE_EN_SET(x) (((uint32_t)(x) << LVB_CTRL_SPLIT_MODE_EN_SHIFT) & LVB_CTRL_SPLIT_MODE_EN_MASK)
#define LVB_CTRL_SPLIT_MODE_EN_GET(x) (((uint32_t)(x) & LVB_CTRL_SPLIT_MODE_EN_MASK) >> LVB_CTRL_SPLIT_MODE_EN_SHIFT)

/*
 * DI1_VSYNC_POLARITY (RW)
 *
 * DI 1 vsync polarity:
 * 1: active low
 * 0: active high
 */
#define LVB_CTRL_DI1_VSYNC_POLARITY_MASK (0x20000UL)
#define LVB_CTRL_DI1_VSYNC_POLARITY_SHIFT (17U)
#define LVB_CTRL_DI1_VSYNC_POLARITY_SET(x) (((uint32_t)(x) << LVB_CTRL_DI1_VSYNC_POLARITY_SHIFT) & LVB_CTRL_DI1_VSYNC_POLARITY_MASK)
#define LVB_CTRL_DI1_VSYNC_POLARITY_GET(x) (((uint32_t)(x) & LVB_CTRL_DI1_VSYNC_POLARITY_MASK) >> LVB_CTRL_DI1_VSYNC_POLARITY_SHIFT)

/*
 * DI0_VSYNC_POLARITY (RW)
 *
 * DI 0 vsync polarity:
 * 1: active low
 * 0: active high
 */
#define LVB_CTRL_DI0_VSYNC_POLARITY_MASK (0x10000UL)
#define LVB_CTRL_DI0_VSYNC_POLARITY_SHIFT (16U)
#define LVB_CTRL_DI0_VSYNC_POLARITY_SET(x) (((uint32_t)(x) << LVB_CTRL_DI0_VSYNC_POLARITY_SHIFT) & LVB_CTRL_DI0_VSYNC_POLARITY_MASK)
#define LVB_CTRL_DI0_VSYNC_POLARITY_GET(x) (((uint32_t)(x) & LVB_CTRL_DI0_VSYNC_POLARITY_MASK) >> LVB_CTRL_DI0_VSYNC_POLARITY_SHIFT)

/*
 * LVDS_TXCLK_SHIFT (RW)
 *
 * Shift the LVDS TX PHY clock  in relation to the data.
 * 000: txck is 7'b1100011
 * 001: txck is 7‘b1110001
 * 010: txck is 7‘b1111000
 * 011: txck is 7‘b1000111
 * 100: txck is 7‘b0001111
 * 101: txck is 7‘b0011110
 * 110: txck is 7‘b0111100
 * 111: txck is 7‘b1100011
 */
#define LVB_CTRL_LVDS_TXCLK_SHIFT_MASK (0x700U)
#define LVB_CTRL_LVDS_TXCLK_SHIFT_SHIFT (8U)
#define LVB_CTRL_LVDS_TXCLK_SHIFT_SET(x) (((uint32_t)(x) << LVB_CTRL_LVDS_TXCLK_SHIFT_SHIFT) & LVB_CTRL_LVDS_TXCLK_SHIFT_MASK)
#define LVB_CTRL_LVDS_TXCLK_SHIFT_GET(x) (((uint32_t)(x) & LVB_CTRL_LVDS_TXCLK_SHIFT_MASK) >> LVB_CTRL_LVDS_TXCLK_SHIFT_SHIFT)

/*
 * CH1_BIT_MAPPING (RW)
 *
 * Channel 1 data protocol:
 * 1: JEIDA standard
 * 0: SPWG standard
 */
#define LVB_CTRL_CH1_BIT_MAPPING_MASK (0x80U)
#define LVB_CTRL_CH1_BIT_MAPPING_SHIFT (7U)
#define LVB_CTRL_CH1_BIT_MAPPING_SET(x) (((uint32_t)(x) << LVB_CTRL_CH1_BIT_MAPPING_SHIFT) & LVB_CTRL_CH1_BIT_MAPPING_MASK)
#define LVB_CTRL_CH1_BIT_MAPPING_GET(x) (((uint32_t)(x) & LVB_CTRL_CH1_BIT_MAPPING_MASK) >> LVB_CTRL_CH1_BIT_MAPPING_SHIFT)

/*
 * CH0_BIT_MAPPING (RW)
 *
 * Channel 0 data protocol:
 * 1: JEIDA standard
 * 0: SPWG standard
 */
#define LVB_CTRL_CH0_BIT_MAPPING_MASK (0x20U)
#define LVB_CTRL_CH0_BIT_MAPPING_SHIFT (5U)
#define LVB_CTRL_CH0_BIT_MAPPING_SET(x) (((uint32_t)(x) << LVB_CTRL_CH0_BIT_MAPPING_SHIFT) & LVB_CTRL_CH0_BIT_MAPPING_MASK)
#define LVB_CTRL_CH0_BIT_MAPPING_GET(x) (((uint32_t)(x) & LVB_CTRL_CH0_BIT_MAPPING_MASK) >> LVB_CTRL_CH0_BIT_MAPPING_SHIFT)

/*
 * CH1_SEL (RW)
 *
 * Channel 1 select:
 * 1: select DI 1
 * 0: select DI 0
 */
#define LVB_CTRL_CH1_SEL_MASK (0x8U)
#define LVB_CTRL_CH1_SEL_SHIFT (3U)
#define LVB_CTRL_CH1_SEL_SET(x) (((uint32_t)(x) << LVB_CTRL_CH1_SEL_SHIFT) & LVB_CTRL_CH1_SEL_MASK)
#define LVB_CTRL_CH1_SEL_GET(x) (((uint32_t)(x) & LVB_CTRL_CH1_SEL_MASK) >> LVB_CTRL_CH1_SEL_SHIFT)

/*
 * CH1_EN (RW)
 *
 * Channel 1 enable:
 * 1: enable
 * 0: disable
 */
#define LVB_CTRL_CH1_EN_MASK (0x4U)
#define LVB_CTRL_CH1_EN_SHIFT (2U)
#define LVB_CTRL_CH1_EN_SET(x) (((uint32_t)(x) << LVB_CTRL_CH1_EN_SHIFT) & LVB_CTRL_CH1_EN_MASK)
#define LVB_CTRL_CH1_EN_GET(x) (((uint32_t)(x) & LVB_CTRL_CH1_EN_MASK) >> LVB_CTRL_CH1_EN_SHIFT)

/*
 * CH0_SEL (RW)
 *
 * Channel 0 select:
 * 1: select DI 1
 * 0: select DI 0
 */
#define LVB_CTRL_CH0_SEL_MASK (0x2U)
#define LVB_CTRL_CH0_SEL_SHIFT (1U)
#define LVB_CTRL_CH0_SEL_SET(x) (((uint32_t)(x) << LVB_CTRL_CH0_SEL_SHIFT) & LVB_CTRL_CH0_SEL_MASK)
#define LVB_CTRL_CH0_SEL_GET(x) (((uint32_t)(x) & LVB_CTRL_CH0_SEL_MASK) >> LVB_CTRL_CH0_SEL_SHIFT)

/*
 * CH0_EN (RW)
 *
 * Channel 0 enable:
 * 1: enable
 * 0: disable
 */
#define LVB_CTRL_CH0_EN_MASK (0x1U)
#define LVB_CTRL_CH0_EN_SHIFT (0U)
#define LVB_CTRL_CH0_EN_SET(x) (((uint32_t)(x) << LVB_CTRL_CH0_EN_SHIFT) & LVB_CTRL_CH0_EN_MASK)
#define LVB_CTRL_CH0_EN_GET(x) (((uint32_t)(x) & LVB_CTRL_CH0_EN_MASK) >> LVB_CTRL_CH0_EN_SHIFT)

/* Bitfield definition for register: PHY_STAT */
/*
 * LVDS1_TX_PHY_PLL_LOCK (RO)
 *
 * LVDS1 TX PHY PLL Lock indication Signal, 1 means pll already locked
 */
#define LVB_PHY_STAT_LVDS1_TX_PHY_PLL_LOCK_MASK (0x2U)
#define LVB_PHY_STAT_LVDS1_TX_PHY_PLL_LOCK_SHIFT (1U)
#define LVB_PHY_STAT_LVDS1_TX_PHY_PLL_LOCK_GET(x) (((uint32_t)(x) & LVB_PHY_STAT_LVDS1_TX_PHY_PLL_LOCK_MASK) >> LVB_PHY_STAT_LVDS1_TX_PHY_PLL_LOCK_SHIFT)

/*
 * LVDS0_TX_PHY_PLL_LOCK (RO)
 *
 * LVDS0 TX PHY PLL Lock indication Signal, 1 means pll already locked
 */
#define LVB_PHY_STAT_LVDS0_TX_PHY_PLL_LOCK_MASK (0x1U)
#define LVB_PHY_STAT_LVDS0_TX_PHY_PLL_LOCK_SHIFT (0U)
#define LVB_PHY_STAT_LVDS0_TX_PHY_PLL_LOCK_GET(x) (((uint32_t)(x) & LVB_PHY_STAT_LVDS0_TX_PHY_PLL_LOCK_MASK) >> LVB_PHY_STAT_LVDS0_TX_PHY_PLL_LOCK_SHIFT)

/* Bitfield definition for register array: PHY_POW_CTRL */
/*
 * PWON_PLL (RW)
 *
 * pll power on
 */
#define LVB_PHY_POW_CTRL_PWON_PLL_MASK (0x20U)
#define LVB_PHY_POW_CTRL_PWON_PLL_SHIFT (5U)
#define LVB_PHY_POW_CTRL_PWON_PLL_SET(x) (((uint32_t)(x) << LVB_PHY_POW_CTRL_PWON_PLL_SHIFT) & LVB_PHY_POW_CTRL_PWON_PLL_MASK)
#define LVB_PHY_POW_CTRL_PWON_PLL_GET(x) (((uint32_t)(x) & LVB_PHY_POW_CTRL_PWON_PLL_MASK) >> LVB_PHY_POW_CTRL_PWON_PLL_SHIFT)

/*
 * TXCK_PD (RW)
 *
 * Power down control signal of channel txck
 * 0: Normal operation
 * 1: Power down channel
 */
#define LVB_PHY_POW_CTRL_TXCK_PD_MASK (0x10U)
#define LVB_PHY_POW_CTRL_TXCK_PD_SHIFT (4U)
#define LVB_PHY_POW_CTRL_TXCK_PD_SET(x) (((uint32_t)(x) << LVB_PHY_POW_CTRL_TXCK_PD_SHIFT) & LVB_PHY_POW_CTRL_TXCK_PD_MASK)
#define LVB_PHY_POW_CTRL_TXCK_PD_GET(x) (((uint32_t)(x) & LVB_PHY_POW_CTRL_TXCK_PD_MASK) >> LVB_PHY_POW_CTRL_TXCK_PD_SHIFT)

/*
 * TX3_PD (RW)
 *
 * Power down control signal of channel tx3
 * 0: Normal operation
 * 1: Power down channel
 */
#define LVB_PHY_POW_CTRL_TX3_PD_MASK (0x8U)
#define LVB_PHY_POW_CTRL_TX3_PD_SHIFT (3U)
#define LVB_PHY_POW_CTRL_TX3_PD_SET(x) (((uint32_t)(x) << LVB_PHY_POW_CTRL_TX3_PD_SHIFT) & LVB_PHY_POW_CTRL_TX3_PD_MASK)
#define LVB_PHY_POW_CTRL_TX3_PD_GET(x) (((uint32_t)(x) & LVB_PHY_POW_CTRL_TX3_PD_MASK) >> LVB_PHY_POW_CTRL_TX3_PD_SHIFT)

/*
 * TX2_PD (RW)
 *
 * Power down control signal of channel tx2
 * 0: Normal operation
 * 1: Power down channel
 */
#define LVB_PHY_POW_CTRL_TX2_PD_MASK (0x4U)
#define LVB_PHY_POW_CTRL_TX2_PD_SHIFT (2U)
#define LVB_PHY_POW_CTRL_TX2_PD_SET(x) (((uint32_t)(x) << LVB_PHY_POW_CTRL_TX2_PD_SHIFT) & LVB_PHY_POW_CTRL_TX2_PD_MASK)
#define LVB_PHY_POW_CTRL_TX2_PD_GET(x) (((uint32_t)(x) & LVB_PHY_POW_CTRL_TX2_PD_MASK) >> LVB_PHY_POW_CTRL_TX2_PD_SHIFT)

/*
 * TX1_PD (RW)
 *
 * Power down control signal of channel tx1
 * 0: Normal operation
 * 1: Power down channel
 */
#define LVB_PHY_POW_CTRL_TX1_PD_MASK (0x2U)
#define LVB_PHY_POW_CTRL_TX1_PD_SHIFT (1U)
#define LVB_PHY_POW_CTRL_TX1_PD_SET(x) (((uint32_t)(x) << LVB_PHY_POW_CTRL_TX1_PD_SHIFT) & LVB_PHY_POW_CTRL_TX1_PD_MASK)
#define LVB_PHY_POW_CTRL_TX1_PD_GET(x) (((uint32_t)(x) & LVB_PHY_POW_CTRL_TX1_PD_MASK) >> LVB_PHY_POW_CTRL_TX1_PD_SHIFT)

/*
 * TX0_PD (RW)
 *
 * Power down control signal of channel tx0
 * 0: Normal operation
 * 1: Power down channel
 */
#define LVB_PHY_POW_CTRL_TX0_PD_MASK (0x1U)
#define LVB_PHY_POW_CTRL_TX0_PD_SHIFT (0U)
#define LVB_PHY_POW_CTRL_TX0_PD_SET(x) (((uint32_t)(x) << LVB_PHY_POW_CTRL_TX0_PD_SHIFT) & LVB_PHY_POW_CTRL_TX0_PD_MASK)
#define LVB_PHY_POW_CTRL_TX0_PD_GET(x) (((uint32_t)(x) & LVB_PHY_POW_CTRL_TX0_PD_MASK) >> LVB_PHY_POW_CTRL_TX0_PD_SHIFT)

/* Bitfield definition for register of struct array TX_PHY: CTL0 */
/*
 * TX_IDLE (RW)
 *
 * Force the high-speed differential signal to common mode.
 * This signal can be set during IP power up stage to prevent unexpected leakage current in TXP/TXN
 * 0: Normal operation
 * 1: Force TXPN /TXMN to common mode
 */
#define LVB_TX_PHY_CTL0_TX_IDLE_MASK (0x100000UL)
#define LVB_TX_PHY_CTL0_TX_IDLE_SHIFT (20U)
#define LVB_TX_PHY_CTL0_TX_IDLE_SET(x) (((uint32_t)(x) << LVB_TX_PHY_CTL0_TX_IDLE_SHIFT) & LVB_TX_PHY_CTL0_TX_IDLE_MASK)
#define LVB_TX_PHY_CTL0_TX_IDLE_GET(x) (((uint32_t)(x) & LVB_TX_PHY_CTL0_TX_IDLE_MASK) >> LVB_TX_PHY_CTL0_TX_IDLE_SHIFT)

/*
 * TX_RTERM_EN (RW)
 *
 * Inner Terminal Resistance enable
 * 0: Disable rterm 2000ohm
 * 1: Enable rterm 100ohm
 */
#define LVB_TX_PHY_CTL0_TX_RTERM_EN_MASK (0x80000UL)
#define LVB_TX_PHY_CTL0_TX_RTERM_EN_SHIFT (19U)
#define LVB_TX_PHY_CTL0_TX_RTERM_EN_SET(x) (((uint32_t)(x) << LVB_TX_PHY_CTL0_TX_RTERM_EN_SHIFT) & LVB_TX_PHY_CTL0_TX_RTERM_EN_MASK)
#define LVB_TX_PHY_CTL0_TX_RTERM_EN_GET(x) (((uint32_t)(x) & LVB_TX_PHY_CTL0_TX_RTERM_EN_MASK) >> LVB_TX_PHY_CTL0_TX_RTERM_EN_SHIFT)

/*
 * TX_BUS_WIDTH (RW)
 *
 * Parallel data bus width select：
 * 000: 4-bit mode, txN_data[3:0] are valid, txN_data[11:4] can be arbitrary state.
 * 001: 6-bit mode, txN_data[5:0] are valid, txN_data[11:6] can be arbitrary state.
 * 010: 7-bit mode. txN_data[6:0] are valid, txN_data[11:7] can be arbitrary state.
 * 011: 8-bit mode. txN_data[7:0] are valid, txN_data[11:8] can be arbitrary state.
 * 100: 9-bit mode. txN_data[8:0] are valid, txN_data[11:9] can be arbitrary state.
 * 101: 10-bit mode. txN_data[9:0] are valid, txN_data[11:10] can be arbitrary state.
 * 110: 11-bit mode. txN_data[10:0] are valid, txN_data[11] can be arbitrary state.
 * 111: 12-bit mode. txN_data[11:0] are valid
 */
#define LVB_TX_PHY_CTL0_TX_BUS_WIDTH_MASK (0x70000UL)
#define LVB_TX_PHY_CTL0_TX_BUS_WIDTH_SHIFT (16U)
#define LVB_TX_PHY_CTL0_TX_BUS_WIDTH_SET(x) (((uint32_t)(x) << LVB_TX_PHY_CTL0_TX_BUS_WIDTH_SHIFT) & LVB_TX_PHY_CTL0_TX_BUS_WIDTH_MASK)
#define LVB_TX_PHY_CTL0_TX_BUS_WIDTH_GET(x) (((uint32_t)(x) & LVB_TX_PHY_CTL0_TX_BUS_WIDTH_MASK) >> LVB_TX_PHY_CTL0_TX_BUS_WIDTH_SHIFT)

/*
 * TX_PHASE_SEL (RW)
 *
 * data/clock lane output phase adjustment:
 * 0000: 0
 * 0001: data lane is 1/32, clock lane is 1/16
 * 0010: data lane is 2/32, clock lane is 2/16
 * 0011: data lane is 3/32, clock lane is 3/16
 * 0100: data lane is 4/32, clock lane is 4/16
 * 0101: data lane is 5/32, clock lane is 5/16
 * 0110: data lane is 6/32, clock lane is 6/16
 * 0111: data lane is 7/32, clock lane is 7/16
 * 1000: data lane is 8/32, clock lane is 8/16
 * 1001: data lane is 9/32, clock lane is 9/16
 * 1010: data lane is 10/32, clock lane is 10/16
 * 1011: data lane is 11/32, clock lane is 11/16
 * 1100: data lane is 12/32, clock lane is 12/16
 * 1101: data lane is 13/32, clock lane is 13/16
 * 1110: data lane is 14/32, clock lane is 14/16
 * 1111: data lane is 15/32, clock lane is 15/16
 */
#define LVB_TX_PHY_CTL0_TX_PHASE_SEL_MASK (0xF000U)
#define LVB_TX_PHY_CTL0_TX_PHASE_SEL_SHIFT (12U)
#define LVB_TX_PHY_CTL0_TX_PHASE_SEL_SET(x) (((uint32_t)(x) << LVB_TX_PHY_CTL0_TX_PHASE_SEL_SHIFT) & LVB_TX_PHY_CTL0_TX_PHASE_SEL_MASK)
#define LVB_TX_PHY_CTL0_TX_PHASE_SEL_GET(x) (((uint32_t)(x) & LVB_TX_PHY_CTL0_TX_PHASE_SEL_MASK) >> LVB_TX_PHY_CTL0_TX_PHASE_SEL_SHIFT)

/*
 * TX_VCOM (RW)
 *
 * output Common Mode Voltage adjustment(Unit: V).
 * 0000: 0.7
 * 0001: 0.8
 * 0010: 0.9
 * 0011: 1.0
 * 0100: 1.1
 * 0101: 1.2
 * 0110: 1.3
 * 0111: 1.4
 * 1000~1111: 1.5
 */
#define LVB_TX_PHY_CTL0_TX_VCOM_MASK (0xF00U)
#define LVB_TX_PHY_CTL0_TX_VCOM_SHIFT (8U)
#define LVB_TX_PHY_CTL0_TX_VCOM_SET(x) (((uint32_t)(x) << LVB_TX_PHY_CTL0_TX_VCOM_SHIFT) & LVB_TX_PHY_CTL0_TX_VCOM_MASK)
#define LVB_TX_PHY_CTL0_TX_VCOM_GET(x) (((uint32_t)(x) & LVB_TX_PHY_CTL0_TX_VCOM_MASK) >> LVB_TX_PHY_CTL0_TX_VCOM_SHIFT)

/*
 * TX_AMP (RW)
 *
 * Output voltage Adjustment(Unit: mV).
 * 0000 : 50
 * 0001: 100
 * 0010: 150
 * 0011: 200
 * 0100: 250
 * 0101: 300
 * 0110: 350
 * 0111: 400
 * 1000: 450
 * 1001: 500
 * 1010: 550
 * 1011~1111: 600
 */
#define LVB_TX_PHY_CTL0_TX_AMP_MASK (0xF0U)
#define LVB_TX_PHY_CTL0_TX_AMP_SHIFT (4U)
#define LVB_TX_PHY_CTL0_TX_AMP_SET(x) (((uint32_t)(x) << LVB_TX_PHY_CTL0_TX_AMP_SHIFT) & LVB_TX_PHY_CTL0_TX_AMP_MASK)
#define LVB_TX_PHY_CTL0_TX_AMP_GET(x) (((uint32_t)(x) & LVB_TX_PHY_CTL0_TX_AMP_MASK) >> LVB_TX_PHY_CTL0_TX_AMP_SHIFT)

/*
 * TX_SR (RW)
 *
 * output slew-rate trimming
 * 00: slowest slew-rate;
 * 11: fastest slew-rate
 */
#define LVB_TX_PHY_CTL0_TX_SR_MASK (0xCU)
#define LVB_TX_PHY_CTL0_TX_SR_SHIFT (2U)
#define LVB_TX_PHY_CTL0_TX_SR_SET(x) (((uint32_t)(x) << LVB_TX_PHY_CTL0_TX_SR_SHIFT) & LVB_TX_PHY_CTL0_TX_SR_MASK)
#define LVB_TX_PHY_CTL0_TX_SR_GET(x) (((uint32_t)(x) & LVB_TX_PHY_CTL0_TX_SR_MASK) >> LVB_TX_PHY_CTL0_TX_SR_SHIFT)

/*
 * TX_DEEMP (RW)
 *
 * output de-emphasis level trimming(Unit: dB)
 * 00: 0
 * 01: 2.5
 * 10: 6.0
 * 11: 6.0
 */
#define LVB_TX_PHY_CTL0_TX_DEEMP_MASK (0x3U)
#define LVB_TX_PHY_CTL0_TX_DEEMP_SHIFT (0U)
#define LVB_TX_PHY_CTL0_TX_DEEMP_SET(x) (((uint32_t)(x) << LVB_TX_PHY_CTL0_TX_DEEMP_SHIFT) & LVB_TX_PHY_CTL0_TX_DEEMP_MASK)
#define LVB_TX_PHY_CTL0_TX_DEEMP_GET(x) (((uint32_t)(x) & LVB_TX_PHY_CTL0_TX_DEEMP_MASK) >> LVB_TX_PHY_CTL0_TX_DEEMP_SHIFT)

/* Bitfield definition for register of struct array TX_PHY: CTL1 */
/*
 * TX_CTL (RW)
 *
 */
#define LVB_TX_PHY_CTL1_TX_CTL_MASK (0xFFFFFUL)
#define LVB_TX_PHY_CTL1_TX_CTL_SHIFT (0U)
#define LVB_TX_PHY_CTL1_TX_CTL_SET(x) (((uint32_t)(x) << LVB_TX_PHY_CTL1_TX_CTL_SHIFT) & LVB_TX_PHY_CTL1_TX_CTL_MASK)
#define LVB_TX_PHY_CTL1_TX_CTL_GET(x) (((uint32_t)(x) & LVB_TX_PHY_CTL1_TX_CTL_MASK) >> LVB_TX_PHY_CTL1_TX_CTL_SHIFT)



/* PHY_POW_CTRL register group index macro definition */
#define LVB_PHY_POW_CTRL_LVDS0 (0UL)
#define LVB_PHY_POW_CTRL_LVDS1 (1UL)

/* TX_PHY register group index macro definition */
#define LVB_TX_PHY_LVDS0_TX0 (0UL)
#define LVB_TX_PHY_LVDS0_TX1 (1UL)
#define LVB_TX_PHY_LVDS0_TX2 (1UL)
#define LVB_TX_PHY_LVDS0_TX3 (3UL)
#define LVB_TX_PHY_LVDS0_TXCK (4UL)
#define LVB_TX_PHY_LVDS1_TX0 (5UL)
#define LVB_TX_PHY_LVDS1_TX1 (6UL)
#define LVB_TX_PHY_LVDS1_TX2 (7UL)
#define LVB_TX_PHY_LVDS1_TX3 (8UL)
#define LVB_TX_PHY_LVDS1_TXCK (9UL)


#endif /* HPM_LVB_H */
