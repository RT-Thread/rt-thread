/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_I2S_H
#define HPM_I2S_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0: Control Register */
    __R  uint32_t RFIFO_FILLINGS;              /* 0x4: Rx FIFO  Filling Level */
    __R  uint32_t TFIFO_FILLINGS;              /* 0x8: Tx FIFO  Filling Level */
    __RW uint32_t FIFO_THRESH;                 /* 0xC: TX/RX FIFO Threshold setting. */
    __RW uint32_t STA;                         /* 0x10: Status Registers */
    __R  uint8_t  RESERVED0[12];               /* 0x14 - 0x1F: Reserved */
    __R  uint32_t RXD[4];                      /* 0x20 - 0x2C: Rx Data0 */
    __W  uint32_t TXD[4];                      /* 0x30 - 0x3C: Tx Data0 */
    __R  uint8_t  RESERVED1[16];               /* 0x40 - 0x4F: Reserved */
    __RW uint32_t CFGR;                        /* 0x50: Configruation Regsiters */
    __R  uint8_t  RESERVED2[4];                /* 0x54 - 0x57: Reserved */
    __RW uint32_t MISC_CFGR;                   /* 0x58: Misc configuration Registers */
    __R  uint8_t  RESERVED3[4];                /* 0x5C - 0x5F: Reserved */
    __RW uint32_t RXDSLOT[4];                  /* 0x60 - 0x6C: Rx Slots Enable for Rx Data0 */
    __RW uint32_t TXDSLOT[4];                  /* 0x70 - 0x7C: Tx Slots Enable for Tx Data0. */
} I2S_Type;


/* Bitfield definition for register: CTRL */
/*
 * SFTRST_RX (RW)
 *
 * software reset the RX module if asserted to be 1'b1. Self-clear.
 */
#define I2S_CTRL_SFTRST_RX_MASK (0x40000UL)
#define I2S_CTRL_SFTRST_RX_SHIFT (18U)
#define I2S_CTRL_SFTRST_RX_SET(x) (((uint32_t)(x) << I2S_CTRL_SFTRST_RX_SHIFT) & I2S_CTRL_SFTRST_RX_MASK)
#define I2S_CTRL_SFTRST_RX_GET(x) (((uint32_t)(x) & I2S_CTRL_SFTRST_RX_MASK) >> I2S_CTRL_SFTRST_RX_SHIFT)

/*
 * SFTRST_TX (RW)
 *
 * software reset the TX module if asserted to be 1'b1. Self-clear.
 */
#define I2S_CTRL_SFTRST_TX_MASK (0x20000UL)
#define I2S_CTRL_SFTRST_TX_SHIFT (17U)
#define I2S_CTRL_SFTRST_TX_SET(x) (((uint32_t)(x) << I2S_CTRL_SFTRST_TX_SHIFT) & I2S_CTRL_SFTRST_TX_MASK)
#define I2S_CTRL_SFTRST_TX_GET(x) (((uint32_t)(x) & I2S_CTRL_SFTRST_TX_MASK) >> I2S_CTRL_SFTRST_TX_SHIFT)

/*
 * SFTRST_CLKGEN (RW)
 *
 * software reset the CLK GEN module if asserted to be 1'b1.  Self-clear.
 */
#define I2S_CTRL_SFTRST_CLKGEN_MASK (0x10000UL)
#define I2S_CTRL_SFTRST_CLKGEN_SHIFT (16U)
#define I2S_CTRL_SFTRST_CLKGEN_SET(x) (((uint32_t)(x) << I2S_CTRL_SFTRST_CLKGEN_SHIFT) & I2S_CTRL_SFTRST_CLKGEN_MASK)
#define I2S_CTRL_SFTRST_CLKGEN_GET(x) (((uint32_t)(x) & I2S_CTRL_SFTRST_CLKGEN_MASK) >> I2S_CTRL_SFTRST_CLKGEN_SHIFT)

/*
 * TXDNIE (RW)
 *
 * TX buffer data needed interrupt enable
 * 0: TXE interrupt masked
 * 1: TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.
 */
#define I2S_CTRL_TXDNIE_MASK (0x8000U)
#define I2S_CTRL_TXDNIE_SHIFT (15U)
#define I2S_CTRL_TXDNIE_SET(x) (((uint32_t)(x) << I2S_CTRL_TXDNIE_SHIFT) & I2S_CTRL_TXDNIE_MASK)
#define I2S_CTRL_TXDNIE_GET(x) (((uint32_t)(x) & I2S_CTRL_TXDNIE_MASK) >> I2S_CTRL_TXDNIE_SHIFT)

/*
 * RXDAIE (RW)
 *
 * RX buffer data available interrupt enable
 * 0: RXNE interrupt masked
 * 1: RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is set.
 */
#define I2S_CTRL_RXDAIE_MASK (0x4000U)
#define I2S_CTRL_RXDAIE_SHIFT (14U)
#define I2S_CTRL_RXDAIE_SET(x) (((uint32_t)(x) << I2S_CTRL_RXDAIE_SHIFT) & I2S_CTRL_RXDAIE_MASK)
#define I2S_CTRL_RXDAIE_GET(x) (((uint32_t)(x) & I2S_CTRL_RXDAIE_MASK) >> I2S_CTRL_RXDAIE_SHIFT)

/*
 * ERRIE (RW)
 *
 * Error interrupt enable
 * This bit controls the generation of an interrupt when an error condition  (UD, OV) occurs.
 * 0: Error interrupt is masked
 * 1: Error interrupt is enabled
 */
#define I2S_CTRL_ERRIE_MASK (0x2000U)
#define I2S_CTRL_ERRIE_SHIFT (13U)
#define I2S_CTRL_ERRIE_SET(x) (((uint32_t)(x) << I2S_CTRL_ERRIE_SHIFT) & I2S_CTRL_ERRIE_MASK)
#define I2S_CTRL_ERRIE_GET(x) (((uint32_t)(x) & I2S_CTRL_ERRIE_MASK) >> I2S_CTRL_ERRIE_SHIFT)

/*
 * TX_DMA_EN (RW)
 *
 * Asserted to use DMA, else to use interrupt
 */
#define I2S_CTRL_TX_DMA_EN_MASK (0x1000U)
#define I2S_CTRL_TX_DMA_EN_SHIFT (12U)
#define I2S_CTRL_TX_DMA_EN_SET(x) (((uint32_t)(x) << I2S_CTRL_TX_DMA_EN_SHIFT) & I2S_CTRL_TX_DMA_EN_MASK)
#define I2S_CTRL_TX_DMA_EN_GET(x) (((uint32_t)(x) & I2S_CTRL_TX_DMA_EN_MASK) >> I2S_CTRL_TX_DMA_EN_SHIFT)

/*
 * RX_DMA_EN (RW)
 *
 * Asserted to use DMA, else to use interrupt
 */
#define I2S_CTRL_RX_DMA_EN_MASK (0x800U)
#define I2S_CTRL_RX_DMA_EN_SHIFT (11U)
#define I2S_CTRL_RX_DMA_EN_SET(x) (((uint32_t)(x) << I2S_CTRL_RX_DMA_EN_SHIFT) & I2S_CTRL_RX_DMA_EN_MASK)
#define I2S_CTRL_RX_DMA_EN_GET(x) (((uint32_t)(x) & I2S_CTRL_RX_DMA_EN_MASK) >> I2S_CTRL_RX_DMA_EN_SHIFT)

/*
 * TXFIFOCLR (RW)
 *
 * Self-clear
 */
#define I2S_CTRL_TXFIFOCLR_MASK (0x400U)
#define I2S_CTRL_TXFIFOCLR_SHIFT (10U)
#define I2S_CTRL_TXFIFOCLR_SET(x) (((uint32_t)(x) << I2S_CTRL_TXFIFOCLR_SHIFT) & I2S_CTRL_TXFIFOCLR_MASK)
#define I2S_CTRL_TXFIFOCLR_GET(x) (((uint32_t)(x) & I2S_CTRL_TXFIFOCLR_MASK) >> I2S_CTRL_TXFIFOCLR_SHIFT)

/*
 * RXFIFOCLR (RW)
 *
 * Self-clear
 */
#define I2S_CTRL_RXFIFOCLR_MASK (0x200U)
#define I2S_CTRL_RXFIFOCLR_SHIFT (9U)
#define I2S_CTRL_RXFIFOCLR_SET(x) (((uint32_t)(x) << I2S_CTRL_RXFIFOCLR_SHIFT) & I2S_CTRL_RXFIFOCLR_MASK)
#define I2S_CTRL_RXFIFOCLR_GET(x) (((uint32_t)(x) & I2S_CTRL_RXFIFOCLR_MASK) >> I2S_CTRL_RXFIFOCLR_SHIFT)

/*
 * TX_EN (RW)
 *
 * enable for each TX data pad
 */
#define I2S_CTRL_TX_EN_MASK (0x1E0U)
#define I2S_CTRL_TX_EN_SHIFT (5U)
#define I2S_CTRL_TX_EN_SET(x) (((uint32_t)(x) << I2S_CTRL_TX_EN_SHIFT) & I2S_CTRL_TX_EN_MASK)
#define I2S_CTRL_TX_EN_GET(x) (((uint32_t)(x) & I2S_CTRL_TX_EN_MASK) >> I2S_CTRL_TX_EN_SHIFT)

/*
 * RX_EN (RW)
 *
 * enable for each RX data pad
 */
#define I2S_CTRL_RX_EN_MASK (0x1EU)
#define I2S_CTRL_RX_EN_SHIFT (1U)
#define I2S_CTRL_RX_EN_SET(x) (((uint32_t)(x) << I2S_CTRL_RX_EN_SHIFT) & I2S_CTRL_RX_EN_MASK)
#define I2S_CTRL_RX_EN_GET(x) (((uint32_t)(x) & I2S_CTRL_RX_EN_MASK) >> I2S_CTRL_RX_EN_SHIFT)

/*
 * I2S_EN (RW)
 *
 * enable for the module
 */
#define I2S_CTRL_I2S_EN_MASK (0x1U)
#define I2S_CTRL_I2S_EN_SHIFT (0U)
#define I2S_CTRL_I2S_EN_SET(x) (((uint32_t)(x) << I2S_CTRL_I2S_EN_SHIFT) & I2S_CTRL_I2S_EN_MASK)
#define I2S_CTRL_I2S_EN_GET(x) (((uint32_t)(x) & I2S_CTRL_I2S_EN_MASK) >> I2S_CTRL_I2S_EN_SHIFT)

/* Bitfield definition for register: RFIFO_FILLINGS */
/*
 * RX3 (RO)
 *
 * RX3 fifo fillings
 */
#define I2S_RFIFO_FILLINGS_RX3_MASK (0xFF000000UL)
#define I2S_RFIFO_FILLINGS_RX3_SHIFT (24U)
#define I2S_RFIFO_FILLINGS_RX3_GET(x) (((uint32_t)(x) & I2S_RFIFO_FILLINGS_RX3_MASK) >> I2S_RFIFO_FILLINGS_RX3_SHIFT)

/*
 * RX2 (RO)
 *
 * RX2 fifo fillings
 */
#define I2S_RFIFO_FILLINGS_RX2_MASK (0xFF0000UL)
#define I2S_RFIFO_FILLINGS_RX2_SHIFT (16U)
#define I2S_RFIFO_FILLINGS_RX2_GET(x) (((uint32_t)(x) & I2S_RFIFO_FILLINGS_RX2_MASK) >> I2S_RFIFO_FILLINGS_RX2_SHIFT)

/*
 * RX1 (RO)
 *
 * RX1 fifo fillings
 */
#define I2S_RFIFO_FILLINGS_RX1_MASK (0xFF00U)
#define I2S_RFIFO_FILLINGS_RX1_SHIFT (8U)
#define I2S_RFIFO_FILLINGS_RX1_GET(x) (((uint32_t)(x) & I2S_RFIFO_FILLINGS_RX1_MASK) >> I2S_RFIFO_FILLINGS_RX1_SHIFT)

/*
 * RX0 (RO)
 *
 * RX0 fifo fillings
 */
#define I2S_RFIFO_FILLINGS_RX0_MASK (0xFFU)
#define I2S_RFIFO_FILLINGS_RX0_SHIFT (0U)
#define I2S_RFIFO_FILLINGS_RX0_GET(x) (((uint32_t)(x) & I2S_RFIFO_FILLINGS_RX0_MASK) >> I2S_RFIFO_FILLINGS_RX0_SHIFT)

/* Bitfield definition for register: TFIFO_FILLINGS */
/*
 * TX3 (RO)
 *
 * TX3 fifo fillings
 */
#define I2S_TFIFO_FILLINGS_TX3_MASK (0xFF000000UL)
#define I2S_TFIFO_FILLINGS_TX3_SHIFT (24U)
#define I2S_TFIFO_FILLINGS_TX3_GET(x) (((uint32_t)(x) & I2S_TFIFO_FILLINGS_TX3_MASK) >> I2S_TFIFO_FILLINGS_TX3_SHIFT)

/*
 * TX2 (RO)
 *
 * TX2 fifo fillings
 */
#define I2S_TFIFO_FILLINGS_TX2_MASK (0xFF0000UL)
#define I2S_TFIFO_FILLINGS_TX2_SHIFT (16U)
#define I2S_TFIFO_FILLINGS_TX2_GET(x) (((uint32_t)(x) & I2S_TFIFO_FILLINGS_TX2_MASK) >> I2S_TFIFO_FILLINGS_TX2_SHIFT)

/*
 * TX1 (RO)
 *
 * TX1 fifo fillings
 */
#define I2S_TFIFO_FILLINGS_TX1_MASK (0xFF00U)
#define I2S_TFIFO_FILLINGS_TX1_SHIFT (8U)
#define I2S_TFIFO_FILLINGS_TX1_GET(x) (((uint32_t)(x) & I2S_TFIFO_FILLINGS_TX1_MASK) >> I2S_TFIFO_FILLINGS_TX1_SHIFT)

/*
 * TX0 (RO)
 *
 * TX0 fifo fillings
 */
#define I2S_TFIFO_FILLINGS_TX0_MASK (0xFFU)
#define I2S_TFIFO_FILLINGS_TX0_SHIFT (0U)
#define I2S_TFIFO_FILLINGS_TX0_GET(x) (((uint32_t)(x) & I2S_TFIFO_FILLINGS_TX0_MASK) >> I2S_TFIFO_FILLINGS_TX0_SHIFT)

/* Bitfield definition for register: FIFO_THRESH */
/*
 * TX (RW)
 *
 * TX fifo threshold to trigger STA[tx_dn]. When tx fifo filling is smaller than or equal to the threshold, assert the tx_dn flag.
 */
#define I2S_FIFO_THRESH_TX_MASK (0xFF00U)
#define I2S_FIFO_THRESH_TX_SHIFT (8U)
#define I2S_FIFO_THRESH_TX_SET(x) (((uint32_t)(x) << I2S_FIFO_THRESH_TX_SHIFT) & I2S_FIFO_THRESH_TX_MASK)
#define I2S_FIFO_THRESH_TX_GET(x) (((uint32_t)(x) & I2S_FIFO_THRESH_TX_MASK) >> I2S_FIFO_THRESH_TX_SHIFT)

/*
 * RX (RW)
 *
 * RX fifo threshold to trigger STA[rx_da].  When rx fifo filling is greater than or equal to the threshold, assert the rx_da flag.
 */
#define I2S_FIFO_THRESH_RX_MASK (0xFFU)
#define I2S_FIFO_THRESH_RX_SHIFT (0U)
#define I2S_FIFO_THRESH_RX_SET(x) (((uint32_t)(x) << I2S_FIFO_THRESH_RX_SHIFT) & I2S_FIFO_THRESH_RX_MASK)
#define I2S_FIFO_THRESH_RX_GET(x) (((uint32_t)(x) & I2S_FIFO_THRESH_RX_MASK) >> I2S_FIFO_THRESH_RX_SHIFT)

/* Bitfield definition for register: STA */
/*
 * TX_UD (W1C)
 *
 * Asserted when tx fifo is underflow. Should be ANDed with CTRL[tx_en] the for correct value. Write 1 to any of these 4 bits will clear the underflow error.
 */
#define I2S_STA_TX_UD_MASK (0x1E000UL)
#define I2S_STA_TX_UD_SHIFT (13U)
#define I2S_STA_TX_UD_SET(x) (((uint32_t)(x) << I2S_STA_TX_UD_SHIFT) & I2S_STA_TX_UD_MASK)
#define I2S_STA_TX_UD_GET(x) (((uint32_t)(x) & I2S_STA_TX_UD_MASK) >> I2S_STA_TX_UD_SHIFT)

/*
 * RX_OV (W1C)
 *
 * Asserted when rx fifo is overflow. Write 1 to any of these 4 bits will clear the overflow error.
 */
#define I2S_STA_RX_OV_MASK (0x1E00U)
#define I2S_STA_RX_OV_SHIFT (9U)
#define I2S_STA_RX_OV_SET(x) (((uint32_t)(x) << I2S_STA_RX_OV_SHIFT) & I2S_STA_RX_OV_MASK)
#define I2S_STA_RX_OV_GET(x) (((uint32_t)(x) & I2S_STA_RX_OV_MASK) >> I2S_STA_RX_OV_SHIFT)

/*
 * TX_DN (RO)
 *
 * Asserted when tx fifo data are needed.
 */
#define I2S_STA_TX_DN_MASK (0x1E0U)
#define I2S_STA_TX_DN_SHIFT (5U)
#define I2S_STA_TX_DN_GET(x) (((uint32_t)(x) & I2S_STA_TX_DN_MASK) >> I2S_STA_TX_DN_SHIFT)

/*
 * RX_DA (RO)
 *
 * Asserted when rx fifo data are available.
 */
#define I2S_STA_RX_DA_MASK (0x1EU)
#define I2S_STA_RX_DA_SHIFT (1U)
#define I2S_STA_RX_DA_GET(x) (((uint32_t)(x) & I2S_STA_RX_DA_MASK) >> I2S_STA_RX_DA_SHIFT)

/* Bitfield definition for register array: RXD */
/*
 * D (RO)
 *
 */
#define I2S_RXD_D_MASK (0xFFFFFFFFUL)
#define I2S_RXD_D_SHIFT (0U)
#define I2S_RXD_D_GET(x) (((uint32_t)(x) & I2S_RXD_D_MASK) >> I2S_RXD_D_SHIFT)

/* Bitfield definition for register array: TXD */
/*
 * D (WO)
 *
 */
#define I2S_TXD_D_MASK (0xFFFFFFFFUL)
#define I2S_TXD_D_SHIFT (0U)
#define I2S_TXD_D_SET(x) (((uint32_t)(x) << I2S_TXD_D_SHIFT) & I2S_TXD_D_MASK)
#define I2S_TXD_D_GET(x) (((uint32_t)(x) & I2S_TXD_D_MASK) >> I2S_TXD_D_SHIFT)

/* Bitfield definition for register: CFGR */
/*
 * BCLK_GATEOFF (RW)
 *
 * Gate off the bclk. Asserted to gate-off the BCLK.
 */
#define I2S_CFGR_BCLK_GATEOFF_MASK (0x40000000UL)
#define I2S_CFGR_BCLK_GATEOFF_SHIFT (30U)
#define I2S_CFGR_BCLK_GATEOFF_SET(x) (((uint32_t)(x) << I2S_CFGR_BCLK_GATEOFF_SHIFT) & I2S_CFGR_BCLK_GATEOFF_MASK)
#define I2S_CFGR_BCLK_GATEOFF_GET(x) (((uint32_t)(x) & I2S_CFGR_BCLK_GATEOFF_MASK) >> I2S_CFGR_BCLK_GATEOFF_SHIFT)

/*
 * BCLK_DIV (RW)
 *
 * Linear prescaler to generate BCLK from MCLK.
 * BCLK_DIV [8:0] = 0: BCLK=No CLK.
 * BCLK_DIV [8:0] = 1: BCLK=MCLK/1
 * BCLK_DIV [8:0] = n: BCLK=MCLK/(n).
 * Note: These bits should be configured when the I2S is disabled. It is used only when the I2S is in master mode.
 */
#define I2S_CFGR_BCLK_DIV_MASK (0x3FE00000UL)
#define I2S_CFGR_BCLK_DIV_SHIFT (21U)
#define I2S_CFGR_BCLK_DIV_SET(x) (((uint32_t)(x) << I2S_CFGR_BCLK_DIV_SHIFT) & I2S_CFGR_BCLK_DIV_MASK)
#define I2S_CFGR_BCLK_DIV_GET(x) (((uint32_t)(x) & I2S_CFGR_BCLK_DIV_MASK) >> I2S_CFGR_BCLK_DIV_SHIFT)

/*
 * INV_BCLK_OUT (RW)
 *
 * Invert the BCLK before sending it out to pad. Only valid in BCLK master mode
 */
#define I2S_CFGR_INV_BCLK_OUT_MASK (0x100000UL)
#define I2S_CFGR_INV_BCLK_OUT_SHIFT (20U)
#define I2S_CFGR_INV_BCLK_OUT_SET(x) (((uint32_t)(x) << I2S_CFGR_INV_BCLK_OUT_SHIFT) & I2S_CFGR_INV_BCLK_OUT_MASK)
#define I2S_CFGR_INV_BCLK_OUT_GET(x) (((uint32_t)(x) & I2S_CFGR_INV_BCLK_OUT_MASK) >> I2S_CFGR_INV_BCLK_OUT_SHIFT)

/*
 * INV_BCLK_IN (RW)
 *
 * Invert the BCLK pad input before using it internally. Only valid in BCLK slave mode
 */
#define I2S_CFGR_INV_BCLK_IN_MASK (0x80000UL)
#define I2S_CFGR_INV_BCLK_IN_SHIFT (19U)
#define I2S_CFGR_INV_BCLK_IN_SET(x) (((uint32_t)(x) << I2S_CFGR_INV_BCLK_IN_SHIFT) & I2S_CFGR_INV_BCLK_IN_MASK)
#define I2S_CFGR_INV_BCLK_IN_GET(x) (((uint32_t)(x) & I2S_CFGR_INV_BCLK_IN_MASK) >> I2S_CFGR_INV_BCLK_IN_SHIFT)

/*
 * INV_FCLK_OUT (RW)
 *
 * Invert the FCLK before sending it out to pad. Only valid in FCLK master mode
 */
#define I2S_CFGR_INV_FCLK_OUT_MASK (0x40000UL)
#define I2S_CFGR_INV_FCLK_OUT_SHIFT (18U)
#define I2S_CFGR_INV_FCLK_OUT_SET(x) (((uint32_t)(x) << I2S_CFGR_INV_FCLK_OUT_SHIFT) & I2S_CFGR_INV_FCLK_OUT_MASK)
#define I2S_CFGR_INV_FCLK_OUT_GET(x) (((uint32_t)(x) & I2S_CFGR_INV_FCLK_OUT_MASK) >> I2S_CFGR_INV_FCLK_OUT_SHIFT)

/*
 * INV_FCLK_IN (RW)
 *
 * Invert the FCLK pad input before using it internally. Only valid in FCLK slave mode
 */
#define I2S_CFGR_INV_FCLK_IN_MASK (0x20000UL)
#define I2S_CFGR_INV_FCLK_IN_SHIFT (17U)
#define I2S_CFGR_INV_FCLK_IN_SET(x) (((uint32_t)(x) << I2S_CFGR_INV_FCLK_IN_SHIFT) & I2S_CFGR_INV_FCLK_IN_MASK)
#define I2S_CFGR_INV_FCLK_IN_GET(x) (((uint32_t)(x) & I2S_CFGR_INV_FCLK_IN_MASK) >> I2S_CFGR_INV_FCLK_IN_SHIFT)

/*
 * INV_MCLK_OUT (RW)
 *
 * Invert the MCLK before sending it out to pad. Only valid in MCLK master mode
 */
#define I2S_CFGR_INV_MCLK_OUT_MASK (0x10000UL)
#define I2S_CFGR_INV_MCLK_OUT_SHIFT (16U)
#define I2S_CFGR_INV_MCLK_OUT_SET(x) (((uint32_t)(x) << I2S_CFGR_INV_MCLK_OUT_SHIFT) & I2S_CFGR_INV_MCLK_OUT_MASK)
#define I2S_CFGR_INV_MCLK_OUT_GET(x) (((uint32_t)(x) & I2S_CFGR_INV_MCLK_OUT_MASK) >> I2S_CFGR_INV_MCLK_OUT_SHIFT)

/*
 * INV_MCLK_IN (RW)
 *
 * Invert the MCLK pad input before using it internally. Only valid in MCLK slave mode
 */
#define I2S_CFGR_INV_MCLK_IN_MASK (0x8000U)
#define I2S_CFGR_INV_MCLK_IN_SHIFT (15U)
#define I2S_CFGR_INV_MCLK_IN_SET(x) (((uint32_t)(x) << I2S_CFGR_INV_MCLK_IN_SHIFT) & I2S_CFGR_INV_MCLK_IN_MASK)
#define I2S_CFGR_INV_MCLK_IN_GET(x) (((uint32_t)(x) & I2S_CFGR_INV_MCLK_IN_MASK) >> I2S_CFGR_INV_MCLK_IN_SHIFT)

/*
 * BCLK_SEL_OP (RW)
 *
 * asserted to use external clk source
 */
#define I2S_CFGR_BCLK_SEL_OP_MASK (0x4000U)
#define I2S_CFGR_BCLK_SEL_OP_SHIFT (14U)
#define I2S_CFGR_BCLK_SEL_OP_SET(x) (((uint32_t)(x) << I2S_CFGR_BCLK_SEL_OP_SHIFT) & I2S_CFGR_BCLK_SEL_OP_MASK)
#define I2S_CFGR_BCLK_SEL_OP_GET(x) (((uint32_t)(x) & I2S_CFGR_BCLK_SEL_OP_MASK) >> I2S_CFGR_BCLK_SEL_OP_SHIFT)

/*
 * FCLK_SEL_OP (RW)
 *
 * asserted to use external clk source
 */
#define I2S_CFGR_FCLK_SEL_OP_MASK (0x2000U)
#define I2S_CFGR_FCLK_SEL_OP_SHIFT (13U)
#define I2S_CFGR_FCLK_SEL_OP_SET(x) (((uint32_t)(x) << I2S_CFGR_FCLK_SEL_OP_SHIFT) & I2S_CFGR_FCLK_SEL_OP_MASK)
#define I2S_CFGR_FCLK_SEL_OP_GET(x) (((uint32_t)(x) & I2S_CFGR_FCLK_SEL_OP_MASK) >> I2S_CFGR_FCLK_SEL_OP_SHIFT)

/*
 * MCK_SEL_OP (RW)
 *
 * asserted to use external clk source
 */
#define I2S_CFGR_MCK_SEL_OP_MASK (0x1000U)
#define I2S_CFGR_MCK_SEL_OP_SHIFT (12U)
#define I2S_CFGR_MCK_SEL_OP_SET(x) (((uint32_t)(x) << I2S_CFGR_MCK_SEL_OP_SHIFT) & I2S_CFGR_MCK_SEL_OP_MASK)
#define I2S_CFGR_MCK_SEL_OP_GET(x) (((uint32_t)(x) & I2S_CFGR_MCK_SEL_OP_MASK) >> I2S_CFGR_MCK_SEL_OP_SHIFT)

/*
 * FRAME_EDGE (RW)
 *
 * The start edge of a frame
 * 0: Falling edge indicates a new frame (Just like standard I2S Philips standard)
 * 1: Rising edge indicates a new frame
 */
#define I2S_CFGR_FRAME_EDGE_MASK (0x800U)
#define I2S_CFGR_FRAME_EDGE_SHIFT (11U)
#define I2S_CFGR_FRAME_EDGE_SET(x) (((uint32_t)(x) << I2S_CFGR_FRAME_EDGE_SHIFT) & I2S_CFGR_FRAME_EDGE_MASK)
#define I2S_CFGR_FRAME_EDGE_GET(x) (((uint32_t)(x) & I2S_CFGR_FRAME_EDGE_MASK) >> I2S_CFGR_FRAME_EDGE_SHIFT)

/*
 * CH_MAX (RW)
 *
 * CH_MAX[4:0] s the number of channels supported in TDM mode. When not in TDM mode, it must be set as 2.
 * It must be an even number, so CH_MAX[0] is always 0.
 * 5'h2: 2 channels
 * 5'h4: 4 channels
 * ...
 * 5‘h10: 16 channels (max)
 */
#define I2S_CFGR_CH_MAX_MASK (0x7C0U)
#define I2S_CFGR_CH_MAX_SHIFT (6U)
#define I2S_CFGR_CH_MAX_SET(x) (((uint32_t)(x) << I2S_CFGR_CH_MAX_SHIFT) & I2S_CFGR_CH_MAX_MASK)
#define I2S_CFGR_CH_MAX_GET(x) (((uint32_t)(x) & I2S_CFGR_CH_MAX_MASK) >> I2S_CFGR_CH_MAX_SHIFT)

/*
 * TDM_EN (RW)
 *
 * TDM mode
 * 0: not TDM mode
 * 1: TDM mode
 */
#define I2S_CFGR_TDM_EN_MASK (0x20U)
#define I2S_CFGR_TDM_EN_SHIFT (5U)
#define I2S_CFGR_TDM_EN_SET(x) (((uint32_t)(x) << I2S_CFGR_TDM_EN_SHIFT) & I2S_CFGR_TDM_EN_MASK)
#define I2S_CFGR_TDM_EN_GET(x) (((uint32_t)(x) & I2S_CFGR_TDM_EN_MASK) >> I2S_CFGR_TDM_EN_SHIFT)

/*
 * STD (RW)
 *
 * I2S standard selection
 * 00: I2S Philips standard.
 * 01: MSB justified standard (left justified)
 * 10: LSB justified standard (right justified)
 * 11: PCM standard
 * Note: For correct operation, these bits should be configured when the I2S is disabled.
 */
#define I2S_CFGR_STD_MASK (0x18U)
#define I2S_CFGR_STD_SHIFT (3U)
#define I2S_CFGR_STD_SET(x) (((uint32_t)(x) << I2S_CFGR_STD_SHIFT) & I2S_CFGR_STD_MASK)
#define I2S_CFGR_STD_GET(x) (((uint32_t)(x) & I2S_CFGR_STD_MASK) >> I2S_CFGR_STD_SHIFT)

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
#define I2S_CFGR_DATSIZ_MASK (0x6U)
#define I2S_CFGR_DATSIZ_SHIFT (1U)
#define I2S_CFGR_DATSIZ_SET(x) (((uint32_t)(x) << I2S_CFGR_DATSIZ_SHIFT) & I2S_CFGR_DATSIZ_MASK)
#define I2S_CFGR_DATSIZ_GET(x) (((uint32_t)(x) & I2S_CFGR_DATSIZ_MASK) >> I2S_CFGR_DATSIZ_SHIFT)

/*
 * CHSIZ (RW)
 *
 * Channel length (number of bits per audio channel)
 * 0: 16-bit wide
 * 1: 32-bit wide
 * The bit write operation has a meaning only if DATLEN = 00 otherwise the channel length is fixed to 32-bit by hardware whatever the value filled in.
 * Note: For correct operation, this bit should be configured when the I2S is disabled.
 */
#define I2S_CFGR_CHSIZ_MASK (0x1U)
#define I2S_CFGR_CHSIZ_SHIFT (0U)
#define I2S_CFGR_CHSIZ_SET(x) (((uint32_t)(x) << I2S_CFGR_CHSIZ_SHIFT) & I2S_CFGR_CHSIZ_MASK)
#define I2S_CFGR_CHSIZ_GET(x) (((uint32_t)(x) & I2S_CFGR_CHSIZ_MASK) >> I2S_CFGR_CHSIZ_SHIFT)

/* Bitfield definition for register: MISC_CFGR */
/*
 * MCLK_GATEOFF (RW)
 *
 * Gate off the mclk. This mclk is the output of a glitch prone mux, so every time to switch the mclk, the gate off clock should be asserted at first. After the clock is switched, de-assert this bit to ungate off the mclk.
 */
#define I2S_MISC_CFGR_MCLK_GATEOFF_MASK (0x2000U)
#define I2S_MISC_CFGR_MCLK_GATEOFF_SHIFT (13U)
#define I2S_MISC_CFGR_MCLK_GATEOFF_SET(x) (((uint32_t)(x) << I2S_MISC_CFGR_MCLK_GATEOFF_SHIFT) & I2S_MISC_CFGR_MCLK_GATEOFF_MASK)
#define I2S_MISC_CFGR_MCLK_GATEOFF_GET(x) (((uint32_t)(x) & I2S_MISC_CFGR_MCLK_GATEOFF_MASK) >> I2S_MISC_CFGR_MCLK_GATEOFF_SHIFT)

/*
 * MCLKOE (RW)
 *
 * Master clock output to pad enable
 * 0: Master clock output is disabled
 * 1: Master clock output is enabled
 * Note: This bit should be configured when the I2S is disabled. It is used only when the I2S is in master mode.
 */
#define I2S_MISC_CFGR_MCLKOE_MASK (0x1U)
#define I2S_MISC_CFGR_MCLKOE_SHIFT (0U)
#define I2S_MISC_CFGR_MCLKOE_SET(x) (((uint32_t)(x) << I2S_MISC_CFGR_MCLKOE_SHIFT) & I2S_MISC_CFGR_MCLKOE_MASK)
#define I2S_MISC_CFGR_MCLKOE_GET(x) (((uint32_t)(x) & I2S_MISC_CFGR_MCLKOE_MASK) >> I2S_MISC_CFGR_MCLKOE_SHIFT)

/* Bitfield definition for register array: RXDSLOT */
/*
 * EN (RW)
 *
 */
#define I2S_RXDSLOT_EN_MASK (0xFFFFU)
#define I2S_RXDSLOT_EN_SHIFT (0U)
#define I2S_RXDSLOT_EN_SET(x) (((uint32_t)(x) << I2S_RXDSLOT_EN_SHIFT) & I2S_RXDSLOT_EN_MASK)
#define I2S_RXDSLOT_EN_GET(x) (((uint32_t)(x) & I2S_RXDSLOT_EN_MASK) >> I2S_RXDSLOT_EN_SHIFT)

/* Bitfield definition for register array: TXDSLOT */
/*
 * EN (RW)
 *
 */
#define I2S_TXDSLOT_EN_MASK (0xFFFFU)
#define I2S_TXDSLOT_EN_SHIFT (0U)
#define I2S_TXDSLOT_EN_SET(x) (((uint32_t)(x) << I2S_TXDSLOT_EN_SHIFT) & I2S_TXDSLOT_EN_MASK)
#define I2S_TXDSLOT_EN_GET(x) (((uint32_t)(x) & I2S_TXDSLOT_EN_MASK) >> I2S_TXDSLOT_EN_SHIFT)



/* RXD register group index macro definition */
#define I2S_RXD_DATA0 (0UL)
#define I2S_RXD_DATA1 (1UL)
#define I2S_RXD_DATA2 (2UL)
#define I2S_RXD_DATA3 (3UL)

/* TXD register group index macro definition */
#define I2S_TXD_DATA0 (0UL)
#define I2S_TXD_DATA1 (1UL)
#define I2S_TXD_DATA2 (2UL)
#define I2S_TXD_DATA3 (3UL)

/* RXDSLOT register group index macro definition */
#define I2S_RXDSLOT_DATA0 (0UL)
#define I2S_RXDSLOT_DATA1 (1UL)
#define I2S_RXDSLOT_DATA2 (2UL)
#define I2S_RXDSLOT_DATA3 (3UL)

/* TXDSLOT register group index macro definition */
#define I2S_TXDSLOT_DATA0 (0UL)
#define I2S_TXDSLOT_DATA1 (1UL)
#define I2S_TXDSLOT_DATA2 (2UL)
#define I2S_TXDSLOT_DATA3 (3UL)


#endif /* HPM_I2S_H */