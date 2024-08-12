/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DAO_H
#define HPM_DAO_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0: Control Register */
    __R  uint8_t  RESERVED0[4];                /* 0x4 - 0x7: Reserved */
    __RW uint32_t CMD;                         /* 0x8: Command Register */
    __RW uint32_t RX_CFGR;                     /* 0xC: Configuration Register */
    __RW uint32_t RXSLT;                       /* 0x10: RX Slot Control Register */
    __RW uint32_t HPF_MA;                      /* 0x14: HPF A Coef Register */
    __RW uint32_t HPF_B;                       /* 0x18: HPF B Coef Register */
} DAO_Type;


/* Bitfield definition for register: CTRL */
/*
 * HPF_EN (RW)
 *
 * Whether HPF is enabled. This HPF is used to filter out the DC part.
 */
#define DAO_CTRL_HPF_EN_MASK (0x20000UL)
#define DAO_CTRL_HPF_EN_SHIFT (17U)
#define DAO_CTRL_HPF_EN_SET(x) (((uint32_t)(x) << DAO_CTRL_HPF_EN_SHIFT) & DAO_CTRL_HPF_EN_MASK)
#define DAO_CTRL_HPF_EN_GET(x) (((uint32_t)(x) & DAO_CTRL_HPF_EN_MASK) >> DAO_CTRL_HPF_EN_SHIFT)

/*
 * MONO (RW)
 *
 * Asserted to let the left and right channel output the same value.
 */
#define DAO_CTRL_MONO_MASK (0x80U)
#define DAO_CTRL_MONO_SHIFT (7U)
#define DAO_CTRL_MONO_SET(x) (((uint32_t)(x) << DAO_CTRL_MONO_SHIFT) & DAO_CTRL_MONO_MASK)
#define DAO_CTRL_MONO_GET(x) (((uint32_t)(x) & DAO_CTRL_MONO_MASK) >> DAO_CTRL_MONO_SHIFT)

/*
 * RIGHT_EN (RW)
 *
 * Asserted to enable the right channel
 */
#define DAO_CTRL_RIGHT_EN_MASK (0x40U)
#define DAO_CTRL_RIGHT_EN_SHIFT (6U)
#define DAO_CTRL_RIGHT_EN_SET(x) (((uint32_t)(x) << DAO_CTRL_RIGHT_EN_SHIFT) & DAO_CTRL_RIGHT_EN_MASK)
#define DAO_CTRL_RIGHT_EN_GET(x) (((uint32_t)(x) & DAO_CTRL_RIGHT_EN_MASK) >> DAO_CTRL_RIGHT_EN_SHIFT)

/*
 * LEFT_EN (RW)
 *
 * Asserted to enable the left channel
 */
#define DAO_CTRL_LEFT_EN_MASK (0x20U)
#define DAO_CTRL_LEFT_EN_SHIFT (5U)
#define DAO_CTRL_LEFT_EN_SET(x) (((uint32_t)(x) << DAO_CTRL_LEFT_EN_SHIFT) & DAO_CTRL_LEFT_EN_MASK)
#define DAO_CTRL_LEFT_EN_GET(x) (((uint32_t)(x) & DAO_CTRL_LEFT_EN_MASK) >> DAO_CTRL_LEFT_EN_SHIFT)

/*
 * REMAP (RW)
 *
 * 1: Use remap pwm version. The remap version is a version that one pwm output is tied to zero when the input pcm signal is positive or negative
 * 0: Don't use remap pwm version
 */
#define DAO_CTRL_REMAP_MASK (0x10U)
#define DAO_CTRL_REMAP_SHIFT (4U)
#define DAO_CTRL_REMAP_SET(x) (((uint32_t)(x) << DAO_CTRL_REMAP_SHIFT) & DAO_CTRL_REMAP_MASK)
#define DAO_CTRL_REMAP_GET(x) (((uint32_t)(x) & DAO_CTRL_REMAP_MASK) >> DAO_CTRL_REMAP_SHIFT)

/*
 * INVERT (RW)
 *
 * all the outputs are inverted before sending to pad
 */
#define DAO_CTRL_INVERT_MASK (0x8U)
#define DAO_CTRL_INVERT_SHIFT (3U)
#define DAO_CTRL_INVERT_SET(x) (((uint32_t)(x) << DAO_CTRL_INVERT_SHIFT) & DAO_CTRL_INVERT_MASK)
#define DAO_CTRL_INVERT_GET(x) (((uint32_t)(x) & DAO_CTRL_INVERT_MASK) >> DAO_CTRL_INVERT_SHIFT)

/*
 * FALSE_LEVEL (RW)
 *
 * the pad output in False run mode, or when the module is disabled
 * 0: all low
 * 1: all high
 * 2: P-high, N-low
 * 3. output is not enabled
 */
#define DAO_CTRL_FALSE_LEVEL_MASK (0x6U)
#define DAO_CTRL_FALSE_LEVEL_SHIFT (1U)
#define DAO_CTRL_FALSE_LEVEL_SET(x) (((uint32_t)(x) << DAO_CTRL_FALSE_LEVEL_SHIFT) & DAO_CTRL_FALSE_LEVEL_MASK)
#define DAO_CTRL_FALSE_LEVEL_GET(x) (((uint32_t)(x) & DAO_CTRL_FALSE_LEVEL_MASK) >> DAO_CTRL_FALSE_LEVEL_SHIFT)

/*
 * FALSE_RUN (RW)
 *
 * the module continues to consume data, but all the pads are constant, thus no audio out
 */
#define DAO_CTRL_FALSE_RUN_MASK (0x1U)
#define DAO_CTRL_FALSE_RUN_SHIFT (0U)
#define DAO_CTRL_FALSE_RUN_SET(x) (((uint32_t)(x) << DAO_CTRL_FALSE_RUN_SHIFT) & DAO_CTRL_FALSE_RUN_MASK)
#define DAO_CTRL_FALSE_RUN_GET(x) (((uint32_t)(x) & DAO_CTRL_FALSE_RUN_MASK) >> DAO_CTRL_FALSE_RUN_SHIFT)

/* Bitfield definition for register: CMD */
/*
 * SFTRST (RW)
 *
 * Self-clear
 */
#define DAO_CMD_SFTRST_MASK (0x2U)
#define DAO_CMD_SFTRST_SHIFT (1U)
#define DAO_CMD_SFTRST_SET(x) (((uint32_t)(x) << DAO_CMD_SFTRST_SHIFT) & DAO_CMD_SFTRST_MASK)
#define DAO_CMD_SFTRST_GET(x) (((uint32_t)(x) & DAO_CMD_SFTRST_MASK) >> DAO_CMD_SFTRST_SHIFT)

/*
 * RUN (RW)
 *
 * Enable this module to run.
 */
#define DAO_CMD_RUN_MASK (0x1U)
#define DAO_CMD_RUN_SHIFT (0U)
#define DAO_CMD_RUN_SET(x) (((uint32_t)(x) << DAO_CMD_RUN_SHIFT) & DAO_CMD_RUN_MASK)
#define DAO_CMD_RUN_GET(x) (((uint32_t)(x) & DAO_CMD_RUN_MASK) >> DAO_CMD_RUN_SHIFT)

/* Bitfield definition for register: RX_CFGR */
/*
 * FRAME_EDGE (RW)
 *
 * The start edge of a frame
 * 0: Falling edge indicates a new frame (Just like standard I2S Philips standard)
 * 1: Rising edge indicates a new frame
 */
#define DAO_RX_CFGR_FRAME_EDGE_MASK (0x800U)
#define DAO_RX_CFGR_FRAME_EDGE_SHIFT (11U)
#define DAO_RX_CFGR_FRAME_EDGE_SET(x) (((uint32_t)(x) << DAO_RX_CFGR_FRAME_EDGE_SHIFT) & DAO_RX_CFGR_FRAME_EDGE_MASK)
#define DAO_RX_CFGR_FRAME_EDGE_GET(x) (((uint32_t)(x) & DAO_RX_CFGR_FRAME_EDGE_MASK) >> DAO_RX_CFGR_FRAME_EDGE_SHIFT)

/*
 * CH_MAX (RW)
 *
 * CH_MAX[3:0] is the number if channels supported in TDM mode. When not in TDM mode, it must be set as 2.
 * It must be an even number, so CH_MAX[0] is always 0.
 * 4'h2: 2 channels
 * 4'h4: 4 channels
 * etc
 */
#define DAO_RX_CFGR_CH_MAX_MASK (0x7C0U)
#define DAO_RX_CFGR_CH_MAX_SHIFT (6U)
#define DAO_RX_CFGR_CH_MAX_SET(x) (((uint32_t)(x) << DAO_RX_CFGR_CH_MAX_SHIFT) & DAO_RX_CFGR_CH_MAX_MASK)
#define DAO_RX_CFGR_CH_MAX_GET(x) (((uint32_t)(x) & DAO_RX_CFGR_CH_MAX_MASK) >> DAO_RX_CFGR_CH_MAX_SHIFT)

/*
 * TDM_EN (RW)
 *
 * TDM mode
 * 0: not TDM mode
 * 1: TDM mode
 */
#define DAO_RX_CFGR_TDM_EN_MASK (0x20U)
#define DAO_RX_CFGR_TDM_EN_SHIFT (5U)
#define DAO_RX_CFGR_TDM_EN_SET(x) (((uint32_t)(x) << DAO_RX_CFGR_TDM_EN_SHIFT) & DAO_RX_CFGR_TDM_EN_MASK)
#define DAO_RX_CFGR_TDM_EN_GET(x) (((uint32_t)(x) & DAO_RX_CFGR_TDM_EN_MASK) >> DAO_RX_CFGR_TDM_EN_SHIFT)

/*
 * STD (RW)
 *
 * I2S standard selection
 * 00: I2S Philips standard.
 * 01: MSB justified standard (left justified)
 * 10: LSB justified standard (right justified)
 * 11: PCM standard
 * For more details on I2S standards.
 * Note: For correct operation, these bits should be configured when the I2S is disabled.
 */
#define DAO_RX_CFGR_STD_MASK (0x18U)
#define DAO_RX_CFGR_STD_SHIFT (3U)
#define DAO_RX_CFGR_STD_SET(x) (((uint32_t)(x) << DAO_RX_CFGR_STD_SHIFT) & DAO_RX_CFGR_STD_MASK)
#define DAO_RX_CFGR_STD_GET(x) (((uint32_t)(x) & DAO_RX_CFGR_STD_MASK) >> DAO_RX_CFGR_STD_SHIFT)

/*
 * DATSIZ (RW)
 *
 * Data length to be transferred
 * 00: 16-bit data length
 * 01: 24-bit data length
 * 10: 32-bit data length
 * 11: Not allowed
 * Note: For correct operation, these bits should be configured when the I2S is disabled.
 */
#define DAO_RX_CFGR_DATSIZ_MASK (0x6U)
#define DAO_RX_CFGR_DATSIZ_SHIFT (1U)
#define DAO_RX_CFGR_DATSIZ_SET(x) (((uint32_t)(x) << DAO_RX_CFGR_DATSIZ_SHIFT) & DAO_RX_CFGR_DATSIZ_MASK)
#define DAO_RX_CFGR_DATSIZ_GET(x) (((uint32_t)(x) & DAO_RX_CFGR_DATSIZ_MASK) >> DAO_RX_CFGR_DATSIZ_SHIFT)

/*
 * CHSIZ (RW)
 *
 * Channel length (number of bits per audio channel)
 * 0: 16-bit wide
 * 1: 32-bit wide
 * The bit write operation has a meaning only if DATLEN = 00 otherwise the channel length is fixed to 32-bit by hardware whatever the value filled in.
 * Note: For correct operation, this bit should be configured when the I2S is disabled.
 */
#define DAO_RX_CFGR_CHSIZ_MASK (0x1U)
#define DAO_RX_CFGR_CHSIZ_SHIFT (0U)
#define DAO_RX_CFGR_CHSIZ_SET(x) (((uint32_t)(x) << DAO_RX_CFGR_CHSIZ_SHIFT) & DAO_RX_CFGR_CHSIZ_MASK)
#define DAO_RX_CFGR_CHSIZ_GET(x) (((uint32_t)(x) & DAO_RX_CFGR_CHSIZ_MASK) >> DAO_RX_CFGR_CHSIZ_SHIFT)

/* Bitfield definition for register: RXSLT */
/*
 * EN (RW)
 *
 * Slot enable for the channels.
 */
#define DAO_RXSLT_EN_MASK (0xFFFFFFFFUL)
#define DAO_RXSLT_EN_SHIFT (0U)
#define DAO_RXSLT_EN_SET(x) (((uint32_t)(x) << DAO_RXSLT_EN_SHIFT) & DAO_RXSLT_EN_MASK)
#define DAO_RXSLT_EN_GET(x) (((uint32_t)(x) & DAO_RXSLT_EN_MASK) >> DAO_RXSLT_EN_SHIFT)

/* Bitfield definition for register: HPF_MA */
/*
 * COEF (RW)
 *
 * Composite value of  coef A of the Order-1 HPF
 */
#define DAO_HPF_MA_COEF_MASK (0xFFFFFFFFUL)
#define DAO_HPF_MA_COEF_SHIFT (0U)
#define DAO_HPF_MA_COEF_SET(x) (((uint32_t)(x) << DAO_HPF_MA_COEF_SHIFT) & DAO_HPF_MA_COEF_MASK)
#define DAO_HPF_MA_COEF_GET(x) (((uint32_t)(x) & DAO_HPF_MA_COEF_MASK) >> DAO_HPF_MA_COEF_SHIFT)

/* Bitfield definition for register: HPF_B */
/*
 * COEF (RW)
 *
 * coef B of the Order-1 HPF
 */
#define DAO_HPF_B_COEF_MASK (0xFFFFFFFFUL)
#define DAO_HPF_B_COEF_SHIFT (0U)
#define DAO_HPF_B_COEF_SET(x) (((uint32_t)(x) << DAO_HPF_B_COEF_SHIFT) & DAO_HPF_B_COEF_MASK)
#define DAO_HPF_B_COEF_GET(x) (((uint32_t)(x) & DAO_HPF_B_COEF_MASK) >> DAO_HPF_B_COEF_SHIFT)




#endif /* HPM_DAO_H */
