/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_MCAN_H
#define HPM_MCAN_H

typedef struct {
    __R  uint8_t  RESERVED0[4];                /* 0x0 - 0x3: Reserved */
    __R  uint32_t ENDN;                        /* 0x4: endian register */
    __R  uint8_t  RESERVED1[4];                /* 0x8 - 0xB: Reserved */
    __RW uint32_t DBTP;                        /* 0xC: data bit timing and prescaler, writeable when CCCR.CCE and CCCR.INT are set */
    __RW uint32_t TEST;                        /* 0x10: test register */
    __RW uint32_t RWD;                         /* 0x14: ram watchdog */
    __RW uint32_t CCCR;                        /* 0x18: CC control register */
    __RW uint32_t NBTP;                        /* 0x1C: nominal bit timing and prescaler register */
    __RW uint32_t TSCC;                        /* 0x20: timestamp counter configuration */
    __R  uint32_t TSCV;                        /* 0x24: timestamp counter value */
    __RW uint32_t TOCC;                        /* 0x28: timeout counter configuration */
    __R  uint32_t TOCV;                        /* 0x2C: timeout counter value */
    __R  uint8_t  RESERVED2[16];               /* 0x30 - 0x3F: Reserved */
    __R  uint32_t ECR;                         /* 0x40: error counter register */
    __R  uint32_t PSR;                         /* 0x44: protocol status register */
    __RW uint32_t TDCR;                        /* 0x48: transmitter delay compensation */
    __R  uint8_t  RESERVED3[4];                /* 0x4C - 0x4F: Reserved */
    __RW uint32_t IR;                          /* 0x50: interrupt register */
    __RW uint32_t IE;                          /* 0x54: interrupt enable */
    __RW uint32_t ILS;                         /* 0x58: interrupt line select */
    __RW uint32_t ILE;                         /* 0x5C: interrupt line enable */
    __R  uint8_t  RESERVED4[32];               /* 0x60 - 0x7F: Reserved */
    __RW uint32_t GFC;                         /* 0x80: global filter configuration */
    __RW uint32_t SIDFC;                       /* 0x84: standard ID filter configuration */
    __RW uint32_t XIDFC;                       /* 0x88: extended ID filter configuration */
    __R  uint8_t  RESERVED5[4];                /* 0x8C - 0x8F: Reserved */
    __RW uint32_t XIDAM;                       /* 0x90: extended id and mask */
    __R  uint32_t HPMS;                        /* 0x94: high priority message status */
    __RW uint32_t NDAT1;                       /* 0x98: new data1 */
    __RW uint32_t NDAT2;                       /* 0x9C: new data2 */
    __RW uint32_t RXF0C;                       /* 0xA0: rx fifo 0 configuration */
    __R  uint32_t RXF0S;                       /* 0xA4: rx fifo 0 status */
    __RW uint32_t RXF0A;                       /* 0xA8: rx fifo0 acknowledge */
    __RW uint32_t RXBC;                        /* 0xAC: rx buffer configuration */
    __RW uint32_t RXF1C;                       /* 0xB0: rx fifo1 configuration */
    __R  uint32_t RXF1S;                       /* 0xB4: rx fifo1 status */
    __RW uint32_t RXF1A;                       /* 0xB8: rx fifo 1 acknowledge */
    __RW uint32_t RXESC;                       /* 0xBC: rx buffer/fifo element size configuration */
    __RW uint32_t TXBC;                        /* 0xC0: tx buffer configuration */
    __R  uint32_t TXFQS;                       /* 0xC4: tx fifo/queue status */
    __RW uint32_t TXESC;                       /* 0xC8: tx buffer element size configuration */
    __R  uint32_t TXBRP;                       /* 0xCC: tx buffer request pending */
    __RW uint32_t TXBAR;                       /* 0xD0: tx buffer add request */
    __RW uint32_t TXBCR;                       /* 0xD4: tx buffer cancellation request */
    __R  uint32_t TXBTO;                       /* 0xD8: tx buffer transmission occurred */
    __R  uint32_t TXBCF;                       /* 0xDC: tx buffer cancellation finished */
    __RW uint32_t TXBTIE;                      /* 0xE0: tx buffer transmission interrupt enable */
    __RW uint32_t TXBCIE;                      /* 0xE4: tx buffer cancellation finished interrupt enable */
    __R  uint8_t  RESERVED6[8];                /* 0xE8 - 0xEF: Reserved */
    __RW uint32_t TXEFC;                       /* 0xF0: tx event fifo configuration */
    __R  uint32_t TXEFS;                       /* 0xF4: tx event fifo status */
    __RW uint32_t TXEFA;                       /* 0xF8: tx event fifo acknowledge */
    __R  uint8_t  RESERVED7[260];              /* 0xFC - 0x1FF: Reserved */
    __R  uint32_t TS_SEL[16];                  /* 0x200 - 0x23C: timestamp 0 */
    __R  uint32_t CREL;                        /* 0x240: core release register */
    __RW uint32_t TSCFG;                       /* 0x244: timestamp configuration */
    __R  uint32_t TSS1;                        /* 0x248: timestamp status1 */
    __R  uint32_t TSS2;                        /* 0x24C: timestamp status2 */
    __R  uint32_t ATB;                         /* 0x250: actual timebase */
    __R  uint32_t ATBH;                        /* 0x254: actual timebase high */
    __R  uint8_t  RESERVED8[424];              /* 0x258 - 0x3FF: Reserved */
    __RW uint32_t GLB_CTL;                     /* 0x400: global control */
    __R  uint32_t GLB_STATUS;                  /* 0x404: global status */
    __R  uint8_t  RESERVED9[4];                /* 0x408 - 0x40B: Reserved */
} MCAN_Type;


/* Bitfield definition for register: ENDN */
/*
 * EVT (R)
 *
 * Endianness Test Value
 * The endianness test value is 0x87654321.
 */
#define MCAN_ENDN_EVT_MASK (0xFFFFFFFFUL)
#define MCAN_ENDN_EVT_SHIFT (0U)
#define MCAN_ENDN_EVT_GET(x) (((uint32_t)(x) & MCAN_ENDN_EVT_MASK) >> MCAN_ENDN_EVT_SHIFT)

/* Bitfield definition for register: DBTP */
/*
 * TDC (RW)
 *
 * transmitter delay compensation enable
 * 0= Transmitter Delay Compensation disabled
 * 1= Transmitter Delay Compensation enabled
 */
#define MCAN_DBTP_TDC_MASK (0x800000UL)
#define MCAN_DBTP_TDC_SHIFT (23U)
#define MCAN_DBTP_TDC_SET(x) (((uint32_t)(x) << MCAN_DBTP_TDC_SHIFT) & MCAN_DBTP_TDC_MASK)
#define MCAN_DBTP_TDC_GET(x) (((uint32_t)(x) & MCAN_DBTP_TDC_MASK) >> MCAN_DBTP_TDC_SHIFT)

/*
 * DBRP (RW)
 *
 * Data Bit Rate Prescaler
 * The value by which the oscillator frequency is divided for generating the bit time quanta. The bit time is built up from a multiple of this quanta. Valid values for the Bit Rate Prescaler are 0 to 31.
 * When TDC = ‘1’, the range is limited to 0,1. The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
 */
#define MCAN_DBTP_DBRP_MASK (0x1F0000UL)
#define MCAN_DBTP_DBRP_SHIFT (16U)
#define MCAN_DBTP_DBRP_SET(x) (((uint32_t)(x) << MCAN_DBTP_DBRP_SHIFT) & MCAN_DBTP_DBRP_MASK)
#define MCAN_DBTP_DBRP_GET(x) (((uint32_t)(x) & MCAN_DBTP_DBRP_MASK) >> MCAN_DBTP_DBRP_SHIFT)

/*
 * DTSEG1 (RW)
 *
 * Data time segment before sample point
 * Valid values are 0 to 31. The actual interpretation by the hardware of this value is such that one more than the programmed value is used.
 */
#define MCAN_DBTP_DTSEG1_MASK (0x1F00U)
#define MCAN_DBTP_DTSEG1_SHIFT (8U)
#define MCAN_DBTP_DTSEG1_SET(x) (((uint32_t)(x) << MCAN_DBTP_DTSEG1_SHIFT) & MCAN_DBTP_DTSEG1_MASK)
#define MCAN_DBTP_DTSEG1_GET(x) (((uint32_t)(x) & MCAN_DBTP_DTSEG1_MASK) >> MCAN_DBTP_DTSEG1_SHIFT)

/*
 * DTSEG2 (RW)
 *
 * Data time segment after sample point
 * Valid values are 0 to 15. The actual interpretation by the hardware of this value is such that one more than the programmed value is used.
 */
#define MCAN_DBTP_DTSEG2_MASK (0xF0U)
#define MCAN_DBTP_DTSEG2_SHIFT (4U)
#define MCAN_DBTP_DTSEG2_SET(x) (((uint32_t)(x) << MCAN_DBTP_DTSEG2_SHIFT) & MCAN_DBTP_DTSEG2_MASK)
#define MCAN_DBTP_DTSEG2_GET(x) (((uint32_t)(x) & MCAN_DBTP_DTSEG2_MASK) >> MCAN_DBTP_DTSEG2_SHIFT)

/*
 * DSJW (RW)
 *
 * Data (Re)Synchronization Jump Width
 * Valid values are 0 to 15. The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
 */
#define MCAN_DBTP_DSJW_MASK (0xFU)
#define MCAN_DBTP_DSJW_SHIFT (0U)
#define MCAN_DBTP_DSJW_SET(x) (((uint32_t)(x) << MCAN_DBTP_DSJW_SHIFT) & MCAN_DBTP_DSJW_MASK)
#define MCAN_DBTP_DSJW_GET(x) (((uint32_t)(x) & MCAN_DBTP_DSJW_MASK) >> MCAN_DBTP_DSJW_SHIFT)

/* Bitfield definition for register: TEST */
/*
 * SVAL (R)
 *
 * Started Valid
 * 0= Value of TXBNS not valid
 * 1= Value of TXBNS valid
 */
#define MCAN_TEST_SVAL_MASK (0x200000UL)
#define MCAN_TEST_SVAL_SHIFT (21U)
#define MCAN_TEST_SVAL_GET(x) (((uint32_t)(x) & MCAN_TEST_SVAL_MASK) >> MCAN_TEST_SVAL_SHIFT)

/*
 * TXBNS (R)
 *
 * Tx Buffer Number Started
 * Tx Buffer number of message whose transmission was started last. Valid when SVAL is set. Valid values are 0 to 31.
 */
#define MCAN_TEST_TXBNS_MASK (0x1F0000UL)
#define MCAN_TEST_TXBNS_SHIFT (16U)
#define MCAN_TEST_TXBNS_GET(x) (((uint32_t)(x) & MCAN_TEST_TXBNS_MASK) >> MCAN_TEST_TXBNS_SHIFT)

/*
 * PVAL (R)
 *
 * Prepared Valid
 * 0= Value of TXBNP not valid
 * 1= Value of TXBNP valid
 */
#define MCAN_TEST_PVAL_MASK (0x2000U)
#define MCAN_TEST_PVAL_SHIFT (13U)
#define MCAN_TEST_PVAL_GET(x) (((uint32_t)(x) & MCAN_TEST_PVAL_MASK) >> MCAN_TEST_PVAL_SHIFT)

/*
 * TXBNP (R)
 *
 * Tx Buffer Number Prepared
 * Tx Buffer number of message that is ready for transmission. Valid when PVAL is set.Valid values are 0 to 31.
 */
#define MCAN_TEST_TXBNP_MASK (0x1F00U)
#define MCAN_TEST_TXBNP_SHIFT (8U)
#define MCAN_TEST_TXBNP_GET(x) (((uint32_t)(x) & MCAN_TEST_TXBNP_MASK) >> MCAN_TEST_TXBNP_SHIFT)

/*
 * RX (R)
 *
 * Receive Pin
 * Monitors the actual value of pin m_can_rx
 * 0= The CAN bus is dominant (m_can_rx = ‘0’)
 * 1= The CAN bus is recessive (m_can_rx = ‘1’)
 */
#define MCAN_TEST_RX_MASK (0x80U)
#define MCAN_TEST_RX_SHIFT (7U)
#define MCAN_TEST_RX_GET(x) (((uint32_t)(x) & MCAN_TEST_RX_MASK) >> MCAN_TEST_RX_SHIFT)

/*
 * TX (RW)
 *
 * Control of Transmit Pin
 * 00 Reset value, m_can_tx controlled by the CAN Core, updated at the end of the CAN bit time
 * 01 Sample Point can be monitored at pin m_can_tx
 * 10 Dominant (‘0’) level at pin m_can_tx
 * 11 Recessive (‘1’) at pin m_can_tx
 */
#define MCAN_TEST_TX_MASK (0x60U)
#define MCAN_TEST_TX_SHIFT (5U)
#define MCAN_TEST_TX_SET(x) (((uint32_t)(x) << MCAN_TEST_TX_SHIFT) & MCAN_TEST_TX_MASK)
#define MCAN_TEST_TX_GET(x) (((uint32_t)(x) & MCAN_TEST_TX_MASK) >> MCAN_TEST_TX_SHIFT)

/*
 * LBCK (RW)
 *
 * Loop Back Mode
 * 0= Reset value, Loop Back Mode is disabled
 * 1= Loop Back Mode is enabled
 */
#define MCAN_TEST_LBCK_MASK (0x10U)
#define MCAN_TEST_LBCK_SHIFT (4U)
#define MCAN_TEST_LBCK_SET(x) (((uint32_t)(x) << MCAN_TEST_LBCK_SHIFT) & MCAN_TEST_LBCK_MASK)
#define MCAN_TEST_LBCK_GET(x) (((uint32_t)(x) & MCAN_TEST_LBCK_MASK) >> MCAN_TEST_LBCK_SHIFT)

/* Bitfield definition for register: RWD */
/*
 * WDV (R)
 *
 * Watchdog Value
 * Actual Message RAM Watchdog Counter Value.
 */
#define MCAN_RWD_WDV_MASK (0xFF00U)
#define MCAN_RWD_WDV_SHIFT (8U)
#define MCAN_RWD_WDV_GET(x) (((uint32_t)(x) & MCAN_RWD_WDV_MASK) >> MCAN_RWD_WDV_SHIFT)

/*
 * WDC (RW)
 *
 * Watchdog Configuration
 * Start value of the Message RAM Watchdog Counter. With the reset value of “00” the counter is disabled.
 */
#define MCAN_RWD_WDC_MASK (0xFFU)
#define MCAN_RWD_WDC_SHIFT (0U)
#define MCAN_RWD_WDC_SET(x) (((uint32_t)(x) << MCAN_RWD_WDC_SHIFT) & MCAN_RWD_WDC_MASK)
#define MCAN_RWD_WDC_GET(x) (((uint32_t)(x) & MCAN_RWD_WDC_MASK) >> MCAN_RWD_WDC_SHIFT)

/* Bitfield definition for register: CCCR */
/*
 * NISO (RW)
 *
 * Non ISO Operation
 * If this bit is set, the M_CAN uses the CAN FD frame format as specified by the Bosch CAN FD
 * Specification V1.0.
 * 0= CAN FD frame format according to ISO 11898-1:2015
 * 1= CAN FD frame format according to Bosch CAN FD Specification V1.0
 * Note: When the generic parameter iso_only_g is set to ‘1’ in hardware synthesis, this bit becomes reserved and is read as ‘0’. The M_CAN always operates with the CAN FD frame format according to ISO 11898-1:2015.
 */
#define MCAN_CCCR_NISO_MASK (0x8000U)
#define MCAN_CCCR_NISO_SHIFT (15U)
#define MCAN_CCCR_NISO_SET(x) (((uint32_t)(x) << MCAN_CCCR_NISO_SHIFT) & MCAN_CCCR_NISO_MASK)
#define MCAN_CCCR_NISO_GET(x) (((uint32_t)(x) & MCAN_CCCR_NISO_MASK) >> MCAN_CCCR_NISO_SHIFT)

/*
 * TXP (RW)
 *
 * Transmit Pause
 * If this bit is set, the M_CAN pauses for two CAN bit times before starting the next transmission after
 * itself has successfully transmitted a frame (see Section 3.5).
 * 0= Transmit pause disabled
 * 1= Transmit pause enabled
 */
#define MCAN_CCCR_TXP_MASK (0x4000U)
#define MCAN_CCCR_TXP_SHIFT (14U)
#define MCAN_CCCR_TXP_SET(x) (((uint32_t)(x) << MCAN_CCCR_TXP_SHIFT) & MCAN_CCCR_TXP_MASK)
#define MCAN_CCCR_TXP_GET(x) (((uint32_t)(x) & MCAN_CCCR_TXP_MASK) >> MCAN_CCCR_TXP_SHIFT)

/*
 * EFBI (RW)
 *
 * Edge Filtering during Bus Integration
 * 0= Edge filtering disabled
 * 1= Two consecutive dominant tq required to detect an edge for hard synchronization
 */
#define MCAN_CCCR_EFBI_MASK (0x2000U)
#define MCAN_CCCR_EFBI_SHIFT (13U)
#define MCAN_CCCR_EFBI_SET(x) (((uint32_t)(x) << MCAN_CCCR_EFBI_SHIFT) & MCAN_CCCR_EFBI_MASK)
#define MCAN_CCCR_EFBI_GET(x) (((uint32_t)(x) & MCAN_CCCR_EFBI_MASK) >> MCAN_CCCR_EFBI_SHIFT)

/*
 * PXHD (RW)
 *
 * Protocol Exception Handling Disable
 * 0= Protocol exception handling enabled
 * 1= Protocol exception handling disabled
 * Note: When protocol exception handling is disabled, the M_CAN will transmit an error frame when it detects a protocol exception condition.
 */
#define MCAN_CCCR_PXHD_MASK (0x1000U)
#define MCAN_CCCR_PXHD_SHIFT (12U)
#define MCAN_CCCR_PXHD_SET(x) (((uint32_t)(x) << MCAN_CCCR_PXHD_SHIFT) & MCAN_CCCR_PXHD_MASK)
#define MCAN_CCCR_PXHD_GET(x) (((uint32_t)(x) & MCAN_CCCR_PXHD_MASK) >> MCAN_CCCR_PXHD_SHIFT)

/*
 * WMM (RW)
 *
 * Wide Message Marker
 * Enables the use of 16-bit Wide Message Markers. When 16-bit Wide Message Markers are used (WMM = ‘1’), 16-bit internal timestamping is disabled for the Tx Event FIFO.
 * 0= 8-bit Message Marker used
 * 1= 16-bit Message Marker used, replacing 16-bit timestamps in Tx Event FIFO
 */
#define MCAN_CCCR_WMM_MASK (0x800U)
#define MCAN_CCCR_WMM_SHIFT (11U)
#define MCAN_CCCR_WMM_SET(x) (((uint32_t)(x) << MCAN_CCCR_WMM_SHIFT) & MCAN_CCCR_WMM_MASK)
#define MCAN_CCCR_WMM_GET(x) (((uint32_t)(x) & MCAN_CCCR_WMM_MASK) >> MCAN_CCCR_WMM_SHIFT)

/*
 * UTSU (RW)
 *
 * Use Timestamping Unit
 * When UTSU is set, 16-bit Wide Message Markers are also enabled regardless of the value of WMM.
 * 0= Internal time stamping
 * 1= External time stamping by TSU
 * Note: When generic parameter connected_tsu_g = ‘0’, there is no TSU connected to the M_CAN.
 * In this case bit UTSU is fixed to zero by synthesis.
 */
#define MCAN_CCCR_UTSU_MASK (0x400U)
#define MCAN_CCCR_UTSU_SHIFT (10U)
#define MCAN_CCCR_UTSU_SET(x) (((uint32_t)(x) << MCAN_CCCR_UTSU_SHIFT) & MCAN_CCCR_UTSU_MASK)
#define MCAN_CCCR_UTSU_GET(x) (((uint32_t)(x) & MCAN_CCCR_UTSU_MASK) >> MCAN_CCCR_UTSU_SHIFT)

/*
 * BRSE (RW)
 *
 * Bit Rate Switch Enable
 * 0= Bit rate switching for transmissions disabled
 * 1= Bit rate switching for transmissions enabled
 * Note: When CAN FD operation is disabled FDOE = ‘0’, BRSE is not evaluated.
 */
#define MCAN_CCCR_BRSE_MASK (0x200U)
#define MCAN_CCCR_BRSE_SHIFT (9U)
#define MCAN_CCCR_BRSE_SET(x) (((uint32_t)(x) << MCAN_CCCR_BRSE_SHIFT) & MCAN_CCCR_BRSE_MASK)
#define MCAN_CCCR_BRSE_GET(x) (((uint32_t)(x) & MCAN_CCCR_BRSE_MASK) >> MCAN_CCCR_BRSE_SHIFT)

/*
 * FDOE (RW)
 *
 * FD Operation Enable
 * 0= FD operation disabled
 * 1= FD operation enabled
 */
#define MCAN_CCCR_FDOE_MASK (0x100U)
#define MCAN_CCCR_FDOE_SHIFT (8U)
#define MCAN_CCCR_FDOE_SET(x) (((uint32_t)(x) << MCAN_CCCR_FDOE_SHIFT) & MCAN_CCCR_FDOE_MASK)
#define MCAN_CCCR_FDOE_GET(x) (((uint32_t)(x) & MCAN_CCCR_FDOE_MASK) >> MCAN_CCCR_FDOE_SHIFT)

/*
 * TEST (RW)
 *
 * Test Mode Enable
 * 0= Normal operation, register TEST holds reset values
 * 1= Test Mode, write access to register TEST enabled
 */
#define MCAN_CCCR_TEST_MASK (0x80U)
#define MCAN_CCCR_TEST_SHIFT (7U)
#define MCAN_CCCR_TEST_SET(x) (((uint32_t)(x) << MCAN_CCCR_TEST_SHIFT) & MCAN_CCCR_TEST_MASK)
#define MCAN_CCCR_TEST_GET(x) (((uint32_t)(x) & MCAN_CCCR_TEST_MASK) >> MCAN_CCCR_TEST_SHIFT)

/*
 * DAR (RW)
 *
 * Disable Automatic Retransmission
 * 0= Automatic retransmission of messages not transmitted successfully enabled
 * 1= Automatic retransmission disabled
 */
#define MCAN_CCCR_DAR_MASK (0x40U)
#define MCAN_CCCR_DAR_SHIFT (6U)
#define MCAN_CCCR_DAR_SET(x) (((uint32_t)(x) << MCAN_CCCR_DAR_SHIFT) & MCAN_CCCR_DAR_MASK)
#define MCAN_CCCR_DAR_GET(x) (((uint32_t)(x) & MCAN_CCCR_DAR_MASK) >> MCAN_CCCR_DAR_SHIFT)

/*
 * MON (RW)
 *
 * Bus Monitoring Mode
 * Bit MON can only be set by the Host when both CCE and INIT are set to ‘1’. The bit can be reset by the Host at any time.
 * 0= Bus Monitoring Mode is disabled
 * 1= Bus Monitoring Mode is enabled
 */
#define MCAN_CCCR_MON_MASK (0x20U)
#define MCAN_CCCR_MON_SHIFT (5U)
#define MCAN_CCCR_MON_SET(x) (((uint32_t)(x) << MCAN_CCCR_MON_SHIFT) & MCAN_CCCR_MON_MASK)
#define MCAN_CCCR_MON_GET(x) (((uint32_t)(x) & MCAN_CCCR_MON_MASK) >> MCAN_CCCR_MON_SHIFT)

/*
 * CSR (RW)
 *
 * Clock Stop Request
 * 0= No clock stop is requested
 * 1= Clock stop requested. When clock stop is requested, first INIT and then CSA will be set after all pending transfer requests have been completed and the CAN bus reached idle.
 */
#define MCAN_CCCR_CSR_MASK (0x10U)
#define MCAN_CCCR_CSR_SHIFT (4U)
#define MCAN_CCCR_CSR_SET(x) (((uint32_t)(x) << MCAN_CCCR_CSR_SHIFT) & MCAN_CCCR_CSR_MASK)
#define MCAN_CCCR_CSR_GET(x) (((uint32_t)(x) & MCAN_CCCR_CSR_MASK) >> MCAN_CCCR_CSR_SHIFT)

/*
 * CSA (R)
 *
 * Clock Stop Acknowledge
 * 0= No clock stop acknowledged
 * 1= M_CAN may be set in power down by stopping m_can_hclk and m_can_cclk
 */
#define MCAN_CCCR_CSA_MASK (0x8U)
#define MCAN_CCCR_CSA_SHIFT (3U)
#define MCAN_CCCR_CSA_GET(x) (((uint32_t)(x) & MCAN_CCCR_CSA_MASK) >> MCAN_CCCR_CSA_SHIFT)

/*
 * ASM (RW)
 *
 * Restricted Operation Mode
 * Bit ASM can only be set by the Host when both CCE and INIT are set to ‘1’. The bit can be reset by the Host at any time. For a description of the Restricted Operation Mode see Section 3.1.5.
 * 0= Normal CAN operation
 * 1= Restricted Operation Mode active
 */
#define MCAN_CCCR_ASM_MASK (0x4U)
#define MCAN_CCCR_ASM_SHIFT (2U)
#define MCAN_CCCR_ASM_SET(x) (((uint32_t)(x) << MCAN_CCCR_ASM_SHIFT) & MCAN_CCCR_ASM_MASK)
#define MCAN_CCCR_ASM_GET(x) (((uint32_t)(x) & MCAN_CCCR_ASM_MASK) >> MCAN_CCCR_ASM_SHIFT)

/*
 * CCE (RW)
 *
 * Configuration Change Enable
 * 0= The CPU has no write access to the protected configuration registers
 * 1= The CPU has write access to the protected configuration registers (while CCCR.INIT = ‘1’)
 */
#define MCAN_CCCR_CCE_MASK (0x2U)
#define MCAN_CCCR_CCE_SHIFT (1U)
#define MCAN_CCCR_CCE_SET(x) (((uint32_t)(x) << MCAN_CCCR_CCE_SHIFT) & MCAN_CCCR_CCE_MASK)
#define MCAN_CCCR_CCE_GET(x) (((uint32_t)(x) & MCAN_CCCR_CCE_MASK) >> MCAN_CCCR_CCE_SHIFT)

/*
 * INIT (RW)
 *
 * Initialization
 * 0= Normal Operation
 * 1= Initialization is started
 */
#define MCAN_CCCR_INIT_MASK (0x1U)
#define MCAN_CCCR_INIT_SHIFT (0U)
#define MCAN_CCCR_INIT_SET(x) (((uint32_t)(x) << MCAN_CCCR_INIT_SHIFT) & MCAN_CCCR_INIT_MASK)
#define MCAN_CCCR_INIT_GET(x) (((uint32_t)(x) & MCAN_CCCR_INIT_MASK) >> MCAN_CCCR_INIT_SHIFT)

/* Bitfield definition for register: NBTP */
/*
 * NSJW (RW)
 *
 * Nominal (Re)Synchronization Jump Width
 * Valid values are 0 to 127. The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
 */
#define MCAN_NBTP_NSJW_MASK (0xFE000000UL)
#define MCAN_NBTP_NSJW_SHIFT (25U)
#define MCAN_NBTP_NSJW_SET(x) (((uint32_t)(x) << MCAN_NBTP_NSJW_SHIFT) & MCAN_NBTP_NSJW_MASK)
#define MCAN_NBTP_NSJW_GET(x) (((uint32_t)(x) & MCAN_NBTP_NSJW_MASK) >> MCAN_NBTP_NSJW_SHIFT)

/*
 * NBRP (RW)
 *
 * Nominal Bit Rate Prescaler
 * The value by which the oscillator frequency is divided for generating the bit time quanta. The bit time is built up from a multiple of this quanta. Valid values for the Bit Rate Prescaler are 0 to 511. The actual interpretation by the hardware of this value is
 * such that one more than the value programmed here is used.
 */
#define MCAN_NBTP_NBRP_MASK (0x1FF0000UL)
#define MCAN_NBTP_NBRP_SHIFT (16U)
#define MCAN_NBTP_NBRP_SET(x) (((uint32_t)(x) << MCAN_NBTP_NBRP_SHIFT) & MCAN_NBTP_NBRP_MASK)
#define MCAN_NBTP_NBRP_GET(x) (((uint32_t)(x) & MCAN_NBTP_NBRP_MASK) >> MCAN_NBTP_NBRP_SHIFT)

/*
 * NTSEG1 (RW)
 *
 * Nominal Time segment before sample point
 * Valid values are 1 to 255. The actual interpretation by the hardware of this value is such that one more than the programmed value is used.
 */
#define MCAN_NBTP_NTSEG1_MASK (0xFF00U)
#define MCAN_NBTP_NTSEG1_SHIFT (8U)
#define MCAN_NBTP_NTSEG1_SET(x) (((uint32_t)(x) << MCAN_NBTP_NTSEG1_SHIFT) & MCAN_NBTP_NTSEG1_MASK)
#define MCAN_NBTP_NTSEG1_GET(x) (((uint32_t)(x) & MCAN_NBTP_NTSEG1_MASK) >> MCAN_NBTP_NTSEG1_SHIFT)

/*
 * NTSEG2 (RW)
 *
 * Nominal Time segment after sample point
 * Valid values are 1 to 127. The actual interpretation by the hardware of this value is such that one more than the programmed value is used.
 */
#define MCAN_NBTP_NTSEG2_MASK (0x7FU)
#define MCAN_NBTP_NTSEG2_SHIFT (0U)
#define MCAN_NBTP_NTSEG2_SET(x) (((uint32_t)(x) << MCAN_NBTP_NTSEG2_SHIFT) & MCAN_NBTP_NTSEG2_MASK)
#define MCAN_NBTP_NTSEG2_GET(x) (((uint32_t)(x) & MCAN_NBTP_NTSEG2_MASK) >> MCAN_NBTP_NTSEG2_SHIFT)

/* Bitfield definition for register: TSCC */
/*
 * TCP (RW)
 *
 * Timestamp Counter Prescaler
 * Configures the timestamp and timeout counters time unit in multiples of CAN bit times [1…16]. The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
 */
#define MCAN_TSCC_TCP_MASK (0xF0000UL)
#define MCAN_TSCC_TCP_SHIFT (16U)
#define MCAN_TSCC_TCP_SET(x) (((uint32_t)(x) << MCAN_TSCC_TCP_SHIFT) & MCAN_TSCC_TCP_MASK)
#define MCAN_TSCC_TCP_GET(x) (((uint32_t)(x) & MCAN_TSCC_TCP_MASK) >> MCAN_TSCC_TCP_SHIFT)

/*
 * TSS (RW)
 *
 * timestamp Select
 * 00= Timestamp counter value always 0x0000
 * 01= Timestamp counter value incremented according to TCP
 * 10= External timestamp counter value used
 * 11= Same as “00”
 */
#define MCAN_TSCC_TSS_MASK (0x3U)
#define MCAN_TSCC_TSS_SHIFT (0U)
#define MCAN_TSCC_TSS_SET(x) (((uint32_t)(x) << MCAN_TSCC_TSS_SHIFT) & MCAN_TSCC_TSS_MASK)
#define MCAN_TSCC_TSS_GET(x) (((uint32_t)(x) & MCAN_TSCC_TSS_MASK) >> MCAN_TSCC_TSS_SHIFT)

/* Bitfield definition for register: TSCV */
/*
 * TSC (RC)
 *
 * Timestamp Counter
 * The internal/external Timestamp Counter value is captured on start of frame (both Rx and Tx).When TSCC.TSS = “01”, the Timestamp Counter is incremented in multiples of CAN bit times [1…16] depending on the configuration of TSCC.TCP.
 * A wrap around sets interrupt flag IR.TSW. Write access resets the counter to zero. When TSCC.TSS = “10”, TSC reflects the external Timestamp Counter value. A write access has no impact.
 */
#define MCAN_TSCV_TSC_MASK (0xFFFFU)
#define MCAN_TSCV_TSC_SHIFT (0U)
#define MCAN_TSCV_TSC_GET(x) (((uint32_t)(x) & MCAN_TSCV_TSC_MASK) >> MCAN_TSCV_TSC_SHIFT)

/* Bitfield definition for register: TOCC */
/*
 * TOP (RW)
 *
 * Timeout Period
 * Start value of the Timeout Counter (down-counter). Configures the Timeout Period.
 */
#define MCAN_TOCC_TOP_MASK (0xFFFF0000UL)
#define MCAN_TOCC_TOP_SHIFT (16U)
#define MCAN_TOCC_TOP_SET(x) (((uint32_t)(x) << MCAN_TOCC_TOP_SHIFT) & MCAN_TOCC_TOP_MASK)
#define MCAN_TOCC_TOP_GET(x) (((uint32_t)(x) & MCAN_TOCC_TOP_MASK) >> MCAN_TOCC_TOP_SHIFT)

/*
 * TOS (RW)
 *
 * Timeout Select
 * When operating in Continuous mode, a write to TOCV presets the counter to the value configured by TOCC.TOP and continues down-counting.
 * When the Timeout Counter is controlled by one of the FIFOs, an empty FIFO presets the counter to the value configured by TOCC.TOP. Down-counting is started when the first FIFO element is stored.
 * 00= Continuous operation
 * 01= Timeout controlled by Tx Event FIFO
 * 10= Timeout controlled by Rx FIFO 0
 * 11= Timeout controlled by Rx FIFO 1
 */
#define MCAN_TOCC_TOS_MASK (0x6U)
#define MCAN_TOCC_TOS_SHIFT (1U)
#define MCAN_TOCC_TOS_SET(x) (((uint32_t)(x) << MCAN_TOCC_TOS_SHIFT) & MCAN_TOCC_TOS_MASK)
#define MCAN_TOCC_TOS_GET(x) (((uint32_t)(x) & MCAN_TOCC_TOS_MASK) >> MCAN_TOCC_TOS_SHIFT)

/*
 * RP (RW)
 *
 * Enable Timeout Counter
 * 0= Timeout Counter disabled
 * 1= Timeout Counter enabled
 */
#define MCAN_TOCC_RP_MASK (0x1U)
#define MCAN_TOCC_RP_SHIFT (0U)
#define MCAN_TOCC_RP_SET(x) (((uint32_t)(x) << MCAN_TOCC_RP_SHIFT) & MCAN_TOCC_RP_MASK)
#define MCAN_TOCC_RP_GET(x) (((uint32_t)(x) & MCAN_TOCC_RP_MASK) >> MCAN_TOCC_RP_SHIFT)

/* Bitfield definition for register: TOCV */
/*
 * TOC (RC)
 *
 * Timeout Counter
 * The Timeout Counter is decremented in multiples of CAN bit times [1…16] depending on the configuration of TSCC.TCP.
 * When decremented to zero, interrupt flag IR.TOO is set and the Timeout Counter is stopped. Start and reset/restart conditions are configured via TOCC.TOS.
 * Note: Byte access: when TOCC.TOS = “00，writing one of the register bytes 3/2/1/0 will preset the Timeout Counter.
 */
#define MCAN_TOCV_TOC_MASK (0xFFFFU)
#define MCAN_TOCV_TOC_SHIFT (0U)
#define MCAN_TOCV_TOC_GET(x) (((uint32_t)(x) & MCAN_TOCV_TOC_MASK) >> MCAN_TOCV_TOC_SHIFT)

/* Bitfield definition for register: ECR */
/*
 * CEL (X)
 *
 * CAN Error Logging
 * The counter is incremented each time when a CAN protocol error causes the 8-bit Transmit Error Counter TEC or the 7-bit Receive Error Counter REC to be incremented.
 * The counter is also incremented when the Bus_Off limit is reached. It is not incremented when only RP is set without changing REC. The increment of CEL follows after the increment of REC or TEC.
 * The counter is reset by read access to CEL. The counter stops at 0xFF; the next increment of TEC or REC sets interrupt flag IR.ELO.
 * Note: Byte access: Reading byte 2 will reset CEL to zero, reading bytes 3/1/0 has no impact.
 */
#define MCAN_ECR_CEL_MASK (0xFF0000UL)
#define MCAN_ECR_CEL_SHIFT (16U)
#define MCAN_ECR_CEL_GET(x) (((uint32_t)(x) & MCAN_ECR_CEL_MASK) >> MCAN_ECR_CEL_SHIFT)

/*
 * RP (R)
 *
 * Receive Error Passive
 * 0= The Receive Error Counter is below the error passive level of 128
 * 1= The Receive Error Counter has reached the error passive level of 128
 */
#define MCAN_ECR_RP_MASK (0x8000U)
#define MCAN_ECR_RP_SHIFT (15U)
#define MCAN_ECR_RP_GET(x) (((uint32_t)(x) & MCAN_ECR_RP_MASK) >> MCAN_ECR_RP_SHIFT)

/*
 * REC (R)
 *
 * Receive Error Counter
 * Actual state of the Receive Error Counter, values between 0 and 127
 */
#define MCAN_ECR_REC_MASK (0x7F00U)
#define MCAN_ECR_REC_SHIFT (8U)
#define MCAN_ECR_REC_GET(x) (((uint32_t)(x) & MCAN_ECR_REC_MASK) >> MCAN_ECR_REC_SHIFT)

/*
 * TEC (R)
 *
 * Transmit Error Counter
 * Actual state of the Transmit Error Counter, values between 0 and 255
 * Note: When CCCR.ASM is set, the CAN protocol controller does not increment TEC and REC when a CAN protocol error is detected, but CEL is still incremented.
 */
#define MCAN_ECR_TEC_MASK (0xFFU)
#define MCAN_ECR_TEC_SHIFT (0U)
#define MCAN_ECR_TEC_GET(x) (((uint32_t)(x) & MCAN_ECR_TEC_MASK) >> MCAN_ECR_TEC_SHIFT)

/* Bitfield definition for register: PSR */
/*
 * TDCV (R)
 *
 * Transmitter Delay Compensation Value
 * Position of the secondary sample point, defined by the sum of the measured delay from m_can_tx to m_can_rx and TDCR.TDCO.
 * The SSP position is, in the data phase, the number of mtq between the start of the transmitted bit and the secondary sample point. Valid values are 0 to 127 mtq.
 */
#define MCAN_PSR_TDCV_MASK (0x7F0000UL)
#define MCAN_PSR_TDCV_SHIFT (16U)
#define MCAN_PSR_TDCV_GET(x) (((uint32_t)(x) & MCAN_PSR_TDCV_MASK) >> MCAN_PSR_TDCV_SHIFT)

/*
 * PXE (X)
 *
 * Protocol Exception Event
 * 0= No protocol exception event occurred since last read access
 * 1= Protocol exception event occurred
 * Note: Byte access: Reading byte 0 will reset PXE, reading bytes 3/2/1 has no impact.
 */
#define MCAN_PSR_PXE_MASK (0x4000U)
#define MCAN_PSR_PXE_SHIFT (14U)
#define MCAN_PSR_PXE_GET(x) (((uint32_t)(x) & MCAN_PSR_PXE_MASK) >> MCAN_PSR_PXE_SHIFT)

/*
 * RFDF (X)
 *
 * Received a CAN FD Message
 * This bit is set independent of acceptance filtering.
 * 0= Since this bit was reset by the CPU, no CAN FD message has been received
 * 1= Message in CAN FD format with FDF flag set has been received
 * Note: Byte access: Reading byte 0 will reset RFDF, reading bytes 3/2/1 has no impact.
 */
#define MCAN_PSR_RFDF_MASK (0x2000U)
#define MCAN_PSR_RFDF_SHIFT (13U)
#define MCAN_PSR_RFDF_GET(x) (((uint32_t)(x) & MCAN_PSR_RFDF_MASK) >> MCAN_PSR_RFDF_SHIFT)

/*
 * RBRS (X)
 *
 * BRS flag of last received CAN FD Message
 * This bit is set together with RFDF, independent of acceptance filtering.
 * 0= Last received CAN FD message did not have its BRS flag set
 * 1= Last received CAN FD message had its BRS flag set
 * Note: Byte access: Reading byte 0 will reset RBRS, reading bytes 3/2/1 has no impact.
 */
#define MCAN_PSR_RBRS_MASK (0x1000U)
#define MCAN_PSR_RBRS_SHIFT (12U)
#define MCAN_PSR_RBRS_GET(x) (((uint32_t)(x) & MCAN_PSR_RBRS_MASK) >> MCAN_PSR_RBRS_SHIFT)

/*
 * RESI (X)
 *
 * ESI flag of last received CAN FD Message
 * This bit is set together with RFDF, independent of acceptance filtering.
 * 0= Last received CAN FD message did not have its ESI flag set
 * 1= Last received CAN FD message had its ESI flag set
 * Note: Byte access: Reading byte 0 will reset RESI, reading bytes 3/2/1 has no impact.
 */
#define MCAN_PSR_RESI_MASK (0x800U)
#define MCAN_PSR_RESI_SHIFT (11U)
#define MCAN_PSR_RESI_GET(x) (((uint32_t)(x) & MCAN_PSR_RESI_MASK) >> MCAN_PSR_RESI_SHIFT)

/*
 * DLEC (S)
 *
 * Data Phase Last Error Code
 * Type of last error that occurred in the data phase of a CAN FD format frame with its BRS flag set.Coding is the same as for LEC. This field will be cleared to zero when a CAN FD format frame with
 * its BRS flag set has been transferred (reception or transmission) without error.
 * Note: Byte access: Reading byte 0 will set DLEC to “111”, reading bytes 3/2/1 has no impact.
 */
#define MCAN_PSR_DLEC_MASK (0x700U)
#define MCAN_PSR_DLEC_SHIFT (8U)
#define MCAN_PSR_DLEC_GET(x) (((uint32_t)(x) & MCAN_PSR_DLEC_MASK) >> MCAN_PSR_DLEC_SHIFT)

/*
 * BO (R)
 *
 * Bus_Off Status
 * 0= The M_CAN is not Bus_Off
 * 1= The M_CAN is in Bus_Off state
 */
#define MCAN_PSR_BO_MASK (0x80U)
#define MCAN_PSR_BO_SHIFT (7U)
#define MCAN_PSR_BO_GET(x) (((uint32_t)(x) & MCAN_PSR_BO_MASK) >> MCAN_PSR_BO_SHIFT)

/*
 * EW (R)
 *
 * Warning Status
 * 0= Both error counters are below the Error_Warning limit of 96
 * 1= At least one of error counter has reached the Error_Warning limit of 96
 */
#define MCAN_PSR_EW_MASK (0x40U)
#define MCAN_PSR_EW_SHIFT (6U)
#define MCAN_PSR_EW_GET(x) (((uint32_t)(x) & MCAN_PSR_EW_MASK) >> MCAN_PSR_EW_SHIFT)

/*
 * EP (R)
 *
 * Error Passive
 * 0= The M_CAN is in the Error_Active state. It normally takes part in bus communication and sends an active error flag when an error has been detected
 * 1= The M_CAN is in the Error_Passive state
 */
#define MCAN_PSR_EP_MASK (0x20U)
#define MCAN_PSR_EP_SHIFT (5U)
#define MCAN_PSR_EP_GET(x) (((uint32_t)(x) & MCAN_PSR_EP_MASK) >> MCAN_PSR_EP_SHIFT)

/*
 * ACT (R)
 *
 * Activity
 * Monitors the module’s CAN communication state.
 * 00= Synchronizing - node is synchronizing on CAN communication
 * 01= Idle - node is neither receiver nor transmitter
 * 10= Receiver - node is operating as receiver
 * 11= Transmitter - node is operating as transmitter
 * Note: ACT is set to “00” by a Protocol Exception Event.
 */
#define MCAN_PSR_ACT_MASK (0x18U)
#define MCAN_PSR_ACT_SHIFT (3U)
#define MCAN_PSR_ACT_GET(x) (((uint32_t)(x) & MCAN_PSR_ACT_MASK) >> MCAN_PSR_ACT_SHIFT)

/*
 * LEC (S)
 *
 * Last Error Code
 * The LEC indicates the type of the last error to occur on the CAN bus. This field will be cleared to ‘0’when a message has been transferred (reception or transmission) without error.
 * 0= No Error: No error occurred since LEC has been reset by successful reception or transmission.
 * 1= Stuff Error: More than 5 equal bits in a sequence have occurred in a part of a received message where this is not allowed.
 * 2= Form Error: A fixed format part of a received frame has the wrong format.
 * 3= AckError: The message transmitted by the M_CAN was not acknowledged by another node.
 * 4= Bit1Error: During the transmission of a message (with the exception of the arbitration field),
 * the device wanted to send a recessive level (bit of logical value ‘1’), but the monitored bus
 * value was dominant.
 * 5= Bit0Error: During the transmission of a message (or acknowledge bit, or active error flag, or overload flag), the device wanted to send a dominant level (data or identifier bit logical value‘0’), but the monitored bus value was recessive.
 *  During Bus_Off recovery this status is set each time a sequence of 11 recessive bits has been monitored. This enables the CPU to monitor the proceeding of the Bus_Off recovery sequence (indicating the bus is not stuck at
 * dominant or continuously disturbed).
 * 6= CRCError: The CRC check sum of a received message was incorrect. The CRC of an incoming message does not match with the CRC calculated from the received data.
 * 7= NoChange: Any read access to the Protocol Status Register re-initializes the LEC to ‘7’. When the LEC shows the value ‘7’, no CAN bus event was detected since the last CPU read access to the Protocol Status Register.
 * Note: When a frame in CAN FD format has reached the data phase with BRS flag set, the next CAN event (error or valid frame) will be shown in DLEC instead of LEC. An error in a fixed stuff bit of a CAN FD CRC sequence will be shown as a Form Error, not Stuff Error.
 * Note: The Bus_Off recovery sequence (see ISO 11898-1:2015) cannot be shortened by setting or resetting CCCR.INIT. If the device goes Bus_Off, it will set CCCR.INIT of its own accord,stopping all bus activities.
 *  Once CCCR.INIT has been cleared by the CPU, the device will then wait for 129 occurrences of Bus Idle (129 * 11 consecutive recessive bits) before resuming normal operation.
 * At the end of the Bus_Off recovery sequence, the Error Management Counters will be reset. During the waiting time after the resetting of CCCR.INIT, each time a sequence of 11 recessive bits has been monitored, a Bit0Error code is written to PSR.LEC,
 * enabling the CPU to readily check up whether the CAN bus is stuck at dominant or continuously disturbed and to monitor the Bus_Off recovery sequence. ECR.REC is used to count these sequences.
 * Note: Byte access: Reading byte 0 will set LEC to “111”, reading bytes 3/2/1 has no impact.
 */
#define MCAN_PSR_LEC_MASK (0x7U)
#define MCAN_PSR_LEC_SHIFT (0U)
#define MCAN_PSR_LEC_GET(x) (((uint32_t)(x) & MCAN_PSR_LEC_MASK) >> MCAN_PSR_LEC_SHIFT)

/* Bitfield definition for register: TDCR */
/*
 * TDCO (RW)
 *
 * Transmitter Delay Compensation SSP Offset
 * Offset value defining the distance between the measured delay from m_can_tx to m_can_rx and the secondary sample point. Valid values are 0 to 127 mtq.
 */
#define MCAN_TDCR_TDCO_MASK (0x7F00U)
#define MCAN_TDCR_TDCO_SHIFT (8U)
#define MCAN_TDCR_TDCO_SET(x) (((uint32_t)(x) << MCAN_TDCR_TDCO_SHIFT) & MCAN_TDCR_TDCO_MASK)
#define MCAN_TDCR_TDCO_GET(x) (((uint32_t)(x) & MCAN_TDCR_TDCO_MASK) >> MCAN_TDCR_TDCO_SHIFT)

/*
 * TDCF (RW)
 *
 * Transmitter Delay Compensation Filter Window Length
 * Defines the minimum value for the SSP position, dominant edges on m_can_rx that would result in an earlier SSP position are ignored for transmitter delay measurement.
 * The feature is enabled when TDCF is configured to a value greater than TDCO. Valid values are 0 to 127 mtq.
 */
#define MCAN_TDCR_TDCF_MASK (0x7FU)
#define MCAN_TDCR_TDCF_SHIFT (0U)
#define MCAN_TDCR_TDCF_SET(x) (((uint32_t)(x) << MCAN_TDCR_TDCF_SHIFT) & MCAN_TDCR_TDCF_MASK)
#define MCAN_TDCR_TDCF_GET(x) (((uint32_t)(x) & MCAN_TDCR_TDCF_MASK) >> MCAN_TDCR_TDCF_SHIFT)

/* Bitfield definition for register: IR */
/*
 * ARA (RW)
 *
 * Access to Reserved Address
 * 0= No access to reserved address occurred
 * 1= Access to reserved address occurred
 */
#define MCAN_IR_ARA_MASK (0x20000000UL)
#define MCAN_IR_ARA_SHIFT (29U)
#define MCAN_IR_ARA_SET(x) (((uint32_t)(x) << MCAN_IR_ARA_SHIFT) & MCAN_IR_ARA_MASK)
#define MCAN_IR_ARA_GET(x) (((uint32_t)(x) & MCAN_IR_ARA_MASK) >> MCAN_IR_ARA_SHIFT)

/*
 * PED (RW)
 *
 * Protocol Error in Data Phase (Data Bit Time is used)
 * 0= No protocol error in data phase
 * 1= Protocol error in data phase detected (PSR.DLEC ≠ 0,7)
 */
#define MCAN_IR_PED_MASK (0x10000000UL)
#define MCAN_IR_PED_SHIFT (28U)
#define MCAN_IR_PED_SET(x) (((uint32_t)(x) << MCAN_IR_PED_SHIFT) & MCAN_IR_PED_MASK)
#define MCAN_IR_PED_GET(x) (((uint32_t)(x) & MCAN_IR_PED_MASK) >> MCAN_IR_PED_SHIFT)

/*
 * PEA (RW)
 *
 * Protocol Error in Arbitration Phase (Nominal Bit Time is used)
 * 0= No protocol error in arbitration phase
 * 1= Protocol error in arbitration phase detected (PSR.LEC ≠ 0,7)
 */
#define MCAN_IR_PEA_MASK (0x8000000UL)
#define MCAN_IR_PEA_SHIFT (27U)
#define MCAN_IR_PEA_SET(x) (((uint32_t)(x) << MCAN_IR_PEA_SHIFT) & MCAN_IR_PEA_MASK)
#define MCAN_IR_PEA_GET(x) (((uint32_t)(x) & MCAN_IR_PEA_MASK) >> MCAN_IR_PEA_SHIFT)

/*
 * WDI (RW)
 *
 * Watchdog Interrupt
 * 0= No Message RAM Watchdog event occurred
 * 1= Message RAM Watchdog event due to missing READY
 */
#define MCAN_IR_WDI_MASK (0x4000000UL)
#define MCAN_IR_WDI_SHIFT (26U)
#define MCAN_IR_WDI_SET(x) (((uint32_t)(x) << MCAN_IR_WDI_SHIFT) & MCAN_IR_WDI_MASK)
#define MCAN_IR_WDI_GET(x) (((uint32_t)(x) & MCAN_IR_WDI_MASK) >> MCAN_IR_WDI_SHIFT)

/*
 * BO (RW)
 *
 * Bus_Off Status
 * 0= Bus_Off status unchanged
 * 1= Bus_Off status changed
 */
#define MCAN_IR_BO_MASK (0x2000000UL)
#define MCAN_IR_BO_SHIFT (25U)
#define MCAN_IR_BO_SET(x) (((uint32_t)(x) << MCAN_IR_BO_SHIFT) & MCAN_IR_BO_MASK)
#define MCAN_IR_BO_GET(x) (((uint32_t)(x) & MCAN_IR_BO_MASK) >> MCAN_IR_BO_SHIFT)

/*
 * EW (RW)
 *
 * Warning Status
 * 0= Error_Warning status unchanged
 * 1= Error_Warning status changed
 */
#define MCAN_IR_EW_MASK (0x1000000UL)
#define MCAN_IR_EW_SHIFT (24U)
#define MCAN_IR_EW_SET(x) (((uint32_t)(x) << MCAN_IR_EW_SHIFT) & MCAN_IR_EW_MASK)
#define MCAN_IR_EW_GET(x) (((uint32_t)(x) & MCAN_IR_EW_MASK) >> MCAN_IR_EW_SHIFT)

/*
 * EP (RW)
 *
 * Error Passive
 * 0= Error_Passive status unchanged
 * 1= Error_Passive status changed
 */
#define MCAN_IR_EP_MASK (0x800000UL)
#define MCAN_IR_EP_SHIFT (23U)
#define MCAN_IR_EP_SET(x) (((uint32_t)(x) << MCAN_IR_EP_SHIFT) & MCAN_IR_EP_MASK)
#define MCAN_IR_EP_GET(x) (((uint32_t)(x) & MCAN_IR_EP_MASK) >> MCAN_IR_EP_SHIFT)

/*
 * ELO (RW)
 *
 * Error Logging Overflow
 * 0= CAN Error Logging Counter did not overflow
 * 1= Overflow of CAN Error Logging Counter occurred
 */
#define MCAN_IR_ELO_MASK (0x400000UL)
#define MCAN_IR_ELO_SHIFT (22U)
#define MCAN_IR_ELO_SET(x) (((uint32_t)(x) << MCAN_IR_ELO_SHIFT) & MCAN_IR_ELO_MASK)
#define MCAN_IR_ELO_GET(x) (((uint32_t)(x) & MCAN_IR_ELO_MASK) >> MCAN_IR_ELO_SHIFT)

/*
 * BEU (RW)
 *
 * Bit Error Uncorrected
 * Message RAM bit error detected, uncorrected. Controlled by input signal m_can_aeim_berr[1] generated by an optional external parity / ECC logic attached to the Message RAM.
 * An uncorrected Message RAM bit error sets CCCR.INIT to ‘1’. This is done to avoid transmission of corrupted data.
 * 0= No bit error detected when reading from Message RAM
 * 1= Bit error detected, uncorrected (e.g. parity logic)
 */
#define MCAN_IR_BEU_MASK (0x200000UL)
#define MCAN_IR_BEU_SHIFT (21U)
#define MCAN_IR_BEU_SET(x) (((uint32_t)(x) << MCAN_IR_BEU_SHIFT) & MCAN_IR_BEU_MASK)
#define MCAN_IR_BEU_GET(x) (((uint32_t)(x) & MCAN_IR_BEU_MASK) >> MCAN_IR_BEU_SHIFT)

/*
 * BEC (RW)
 *
 * Bit Error Corrected
 * Message RAM bit error detected and corrected. Controlled by input signal m_can_aeim_berr[0] generated by an optional external parity / ECC logic attached to the Message RAM.
 * 0= No bit error detected when reading from Message RAM
 * 1= Bit error detected and corrected (e.g. ECC)
 */
#define MCAN_IR_BEC_MASK (0x100000UL)
#define MCAN_IR_BEC_SHIFT (20U)
#define MCAN_IR_BEC_SET(x) (((uint32_t)(x) << MCAN_IR_BEC_SHIFT) & MCAN_IR_BEC_MASK)
#define MCAN_IR_BEC_GET(x) (((uint32_t)(x) & MCAN_IR_BEC_MASK) >> MCAN_IR_BEC_SHIFT)

/*
 * DRX (RW)
 *
 * Message stored to Dedicated Rx Buffer
 * The flag is set whenever a received message has been stored into a dedicated Rx Buffer.
 * 0= No Rx Buffer updated
 * 1= At least one received message stored into an Rx Buffer
 */
#define MCAN_IR_DRX_MASK (0x80000UL)
#define MCAN_IR_DRX_SHIFT (19U)
#define MCAN_IR_DRX_SET(x) (((uint32_t)(x) << MCAN_IR_DRX_SHIFT) & MCAN_IR_DRX_MASK)
#define MCAN_IR_DRX_GET(x) (((uint32_t)(x) & MCAN_IR_DRX_MASK) >> MCAN_IR_DRX_SHIFT)

/*
 * TOO (RW)
 *
 * Timeout Occurred
 * 0= No timeout
 * 1= Timeout reached
 */
#define MCAN_IR_TOO_MASK (0x40000UL)
#define MCAN_IR_TOO_SHIFT (18U)
#define MCAN_IR_TOO_SET(x) (((uint32_t)(x) << MCAN_IR_TOO_SHIFT) & MCAN_IR_TOO_MASK)
#define MCAN_IR_TOO_GET(x) (((uint32_t)(x) & MCAN_IR_TOO_MASK) >> MCAN_IR_TOO_SHIFT)

/*
 * MRAF (RW)
 *
 * Message RAM Access Failure
 * The flag is set, when the Rx Handler
 * .has not completed acceptance filtering or storage of an accepted message until the arbitration field of the following message has been received. In this case acceptance filtering or message
 * storage is aborted and the Rx Handler starts processing of the following message.
 * .was not able to write a message to the Message RAM. In this case message storage is aborted.
 * In both cases the FIFO put index is not updated resp. the New Data flag for a dedicated Rx Buffer is not set, a partly stored message is overwritten when the next message is stored to this location.
 * The flag is also set when the Tx Handler was not able to read a message from the Message RAM in time. In this case message transmission is aborted. In case of a Tx Handler access failure the
 * M_CAN is switched into Restricted Operation Mode (see Section 3.1.5). To leave Restricted Operation Mode, the Host CPU has to reset CCCR.ASM.
 * 0= No Message RAM access failure occurred
 * 1= Message RAM access failure occurred
 */
#define MCAN_IR_MRAF_MASK (0x20000UL)
#define MCAN_IR_MRAF_SHIFT (17U)
#define MCAN_IR_MRAF_SET(x) (((uint32_t)(x) << MCAN_IR_MRAF_SHIFT) & MCAN_IR_MRAF_MASK)
#define MCAN_IR_MRAF_GET(x) (((uint32_t)(x) & MCAN_IR_MRAF_MASK) >> MCAN_IR_MRAF_SHIFT)

/*
 * TSW (RW)
 *
 * Timestamp Wraparound
 * 0= No timestamp counter wrap-around
 * 1= Timestamp counter wrapped around
 */
#define MCAN_IR_TSW_MASK (0x10000UL)
#define MCAN_IR_TSW_SHIFT (16U)
#define MCAN_IR_TSW_SET(x) (((uint32_t)(x) << MCAN_IR_TSW_SHIFT) & MCAN_IR_TSW_MASK)
#define MCAN_IR_TSW_GET(x) (((uint32_t)(x) & MCAN_IR_TSW_MASK) >> MCAN_IR_TSW_SHIFT)

/*
 * TEFL (RW)
 *
 * Tx Event FIFO Element Lost
 * 0= No Tx Event FIFO element lost
 * 1= Tx Event FIFO element lost, also set after write attempt to Tx Event FIFO of size zero
 */
#define MCAN_IR_TEFL_MASK (0x8000U)
#define MCAN_IR_TEFL_SHIFT (15U)
#define MCAN_IR_TEFL_SET(x) (((uint32_t)(x) << MCAN_IR_TEFL_SHIFT) & MCAN_IR_TEFL_MASK)
#define MCAN_IR_TEFL_GET(x) (((uint32_t)(x) & MCAN_IR_TEFL_MASK) >> MCAN_IR_TEFL_SHIFT)

/*
 * TEFF (RW)
 *
 * Tx Event FIFO Full
 * 0= Tx Event FIFO not full
 * 1= Tx Event FIFO full
 */
#define MCAN_IR_TEFF_MASK (0x4000U)
#define MCAN_IR_TEFF_SHIFT (14U)
#define MCAN_IR_TEFF_SET(x) (((uint32_t)(x) << MCAN_IR_TEFF_SHIFT) & MCAN_IR_TEFF_MASK)
#define MCAN_IR_TEFF_GET(x) (((uint32_t)(x) & MCAN_IR_TEFF_MASK) >> MCAN_IR_TEFF_SHIFT)

/*
 * TEFW (RW)
 *
 * Tx Event FIFO Watermark Reached
 * 0= Tx Event FIFO fill level below watermark
 * 1= Tx Event FIFO fill level reached watermark
 */
#define MCAN_IR_TEFW_MASK (0x2000U)
#define MCAN_IR_TEFW_SHIFT (13U)
#define MCAN_IR_TEFW_SET(x) (((uint32_t)(x) << MCAN_IR_TEFW_SHIFT) & MCAN_IR_TEFW_MASK)
#define MCAN_IR_TEFW_GET(x) (((uint32_t)(x) & MCAN_IR_TEFW_MASK) >> MCAN_IR_TEFW_SHIFT)

/*
 * TEFN (RW)
 *
 * Tx Event FIFO New Entry
 * 0= Tx Event FIFO unchanged
 * 1= Tx Handler wrote Tx Event FIFO element
 */
#define MCAN_IR_TEFN_MASK (0x1000U)
#define MCAN_IR_TEFN_SHIFT (12U)
#define MCAN_IR_TEFN_SET(x) (((uint32_t)(x) << MCAN_IR_TEFN_SHIFT) & MCAN_IR_TEFN_MASK)
#define MCAN_IR_TEFN_GET(x) (((uint32_t)(x) & MCAN_IR_TEFN_MASK) >> MCAN_IR_TEFN_SHIFT)

/*
 * TFE (RW)
 *
 * Tx FIFO Empty
 * 0= Tx FIFO non-empty
 * 1= Tx FIFO empty
 */
#define MCAN_IR_TFE_MASK (0x800U)
#define MCAN_IR_TFE_SHIFT (11U)
#define MCAN_IR_TFE_SET(x) (((uint32_t)(x) << MCAN_IR_TFE_SHIFT) & MCAN_IR_TFE_MASK)
#define MCAN_IR_TFE_GET(x) (((uint32_t)(x) & MCAN_IR_TFE_MASK) >> MCAN_IR_TFE_SHIFT)

/*
 * TCF (RW)
 *
 * Transmission Cancellation Finished
 * 0= No transmission cancellation finished
 * 1= Transmission cancellation finished
 */
#define MCAN_IR_TCF_MASK (0x400U)
#define MCAN_IR_TCF_SHIFT (10U)
#define MCAN_IR_TCF_SET(x) (((uint32_t)(x) << MCAN_IR_TCF_SHIFT) & MCAN_IR_TCF_MASK)
#define MCAN_IR_TCF_GET(x) (((uint32_t)(x) & MCAN_IR_TCF_MASK) >> MCAN_IR_TCF_SHIFT)

/*
 * TC (RW)
 *
 * Transmission Completed
 * 0= No transmission completed
 * 1= Transmission completed
 */
#define MCAN_IR_TC_MASK (0x200U)
#define MCAN_IR_TC_SHIFT (9U)
#define MCAN_IR_TC_SET(x) (((uint32_t)(x) << MCAN_IR_TC_SHIFT) & MCAN_IR_TC_MASK)
#define MCAN_IR_TC_GET(x) (((uint32_t)(x) & MCAN_IR_TC_MASK) >> MCAN_IR_TC_SHIFT)

/*
 * HPM (RW)
 *
 * High Priority Message
 * 0= No high priority message received
 * 1= High priority message received
 */
#define MCAN_IR_HPM_MASK (0x100U)
#define MCAN_IR_HPM_SHIFT (8U)
#define MCAN_IR_HPM_SET(x) (((uint32_t)(x) << MCAN_IR_HPM_SHIFT) & MCAN_IR_HPM_MASK)
#define MCAN_IR_HPM_GET(x) (((uint32_t)(x) & MCAN_IR_HPM_MASK) >> MCAN_IR_HPM_SHIFT)

/*
 * RF1L (RW)
 *
 * Rx FIFO 1 Message Lost
 * 0= No Rx FIFO 1 message lost
 * 1= Rx FIFO 1 message lost, also set after write attempt to Rx FIFO 1 of size zero
 */
#define MCAN_IR_RF1L_MASK (0x80U)
#define MCAN_IR_RF1L_SHIFT (7U)
#define MCAN_IR_RF1L_SET(x) (((uint32_t)(x) << MCAN_IR_RF1L_SHIFT) & MCAN_IR_RF1L_MASK)
#define MCAN_IR_RF1L_GET(x) (((uint32_t)(x) & MCAN_IR_RF1L_MASK) >> MCAN_IR_RF1L_SHIFT)

/*
 * RF1F (RW)
 *
 * Rx FIFO 1 Full
 * 0= Rx FIFO 1 not full
 * 1= Rx FIFO 1 full
 */
#define MCAN_IR_RF1F_MASK (0x40U)
#define MCAN_IR_RF1F_SHIFT (6U)
#define MCAN_IR_RF1F_SET(x) (((uint32_t)(x) << MCAN_IR_RF1F_SHIFT) & MCAN_IR_RF1F_MASK)
#define MCAN_IR_RF1F_GET(x) (((uint32_t)(x) & MCAN_IR_RF1F_MASK) >> MCAN_IR_RF1F_SHIFT)

/*
 * RF1W (RW)
 *
 * Rx FIFO 1 Watermark Reached
 * 0= Rx FIFO 1 fill level below watermark
 * 1= Rx FIFO 1 fill level reached watermark
 */
#define MCAN_IR_RF1W_MASK (0x20U)
#define MCAN_IR_RF1W_SHIFT (5U)
#define MCAN_IR_RF1W_SET(x) (((uint32_t)(x) << MCAN_IR_RF1W_SHIFT) & MCAN_IR_RF1W_MASK)
#define MCAN_IR_RF1W_GET(x) (((uint32_t)(x) & MCAN_IR_RF1W_MASK) >> MCAN_IR_RF1W_SHIFT)

/*
 * RF1N (RW)
 *
 * Rx FIFO 1 New Message
 * 0= No new message written to Rx FIFO 1
 * 1= New message written to Rx FIFO 1
 */
#define MCAN_IR_RF1N_MASK (0x10U)
#define MCAN_IR_RF1N_SHIFT (4U)
#define MCAN_IR_RF1N_SET(x) (((uint32_t)(x) << MCAN_IR_RF1N_SHIFT) & MCAN_IR_RF1N_MASK)
#define MCAN_IR_RF1N_GET(x) (((uint32_t)(x) & MCAN_IR_RF1N_MASK) >> MCAN_IR_RF1N_SHIFT)

/*
 * RF0L (RW)
 *
 * Rx FIFO 0 Message Lost
 * 0= No Rx FIFO 0 message lost
 * 1= Rx FIFO 0 message lost, also set after write attempt to Rx FIFO 0 of size zero
 */
#define MCAN_IR_RF0L_MASK (0x8U)
#define MCAN_IR_RF0L_SHIFT (3U)
#define MCAN_IR_RF0L_SET(x) (((uint32_t)(x) << MCAN_IR_RF0L_SHIFT) & MCAN_IR_RF0L_MASK)
#define MCAN_IR_RF0L_GET(x) (((uint32_t)(x) & MCAN_IR_RF0L_MASK) >> MCAN_IR_RF0L_SHIFT)

/*
 * RF0F (RW)
 *
 * Rx FIFO 0 Full
 * 0= Rx FIFO 0 not full
 * 1= Rx FIFO 0 full
 */
#define MCAN_IR_RF0F_MASK (0x4U)
#define MCAN_IR_RF0F_SHIFT (2U)
#define MCAN_IR_RF0F_SET(x) (((uint32_t)(x) << MCAN_IR_RF0F_SHIFT) & MCAN_IR_RF0F_MASK)
#define MCAN_IR_RF0F_GET(x) (((uint32_t)(x) & MCAN_IR_RF0F_MASK) >> MCAN_IR_RF0F_SHIFT)

/*
 * RF0W (RW)
 *
 * Rx FIFO 0 Watermark Reached
 * 0= Rx FIFO 0 fill level below watermark
 * 1= Rx FIFO 0 fill level reached watermark
 */
#define MCAN_IR_RF0W_MASK (0x2U)
#define MCAN_IR_RF0W_SHIFT (1U)
#define MCAN_IR_RF0W_SET(x) (((uint32_t)(x) << MCAN_IR_RF0W_SHIFT) & MCAN_IR_RF0W_MASK)
#define MCAN_IR_RF0W_GET(x) (((uint32_t)(x) & MCAN_IR_RF0W_MASK) >> MCAN_IR_RF0W_SHIFT)

/*
 * RF0N (RW)
 *
 * Rx FIFO 0 New Message
 * 0= No new message written to Rx FIFO 0
 * 1= New message written to Rx FIFO 0
 */
#define MCAN_IR_RF0N_MASK (0x1U)
#define MCAN_IR_RF0N_SHIFT (0U)
#define MCAN_IR_RF0N_SET(x) (((uint32_t)(x) << MCAN_IR_RF0N_SHIFT) & MCAN_IR_RF0N_MASK)
#define MCAN_IR_RF0N_GET(x) (((uint32_t)(x) & MCAN_IR_RF0N_MASK) >> MCAN_IR_RF0N_SHIFT)

/* Bitfield definition for register: IE */
/*
 * ARAE (RW)
 *
 * Access to Reserved Address Enable
 */
#define MCAN_IE_ARAE_MASK (0x20000000UL)
#define MCAN_IE_ARAE_SHIFT (29U)
#define MCAN_IE_ARAE_SET(x) (((uint32_t)(x) << MCAN_IE_ARAE_SHIFT) & MCAN_IE_ARAE_MASK)
#define MCAN_IE_ARAE_GET(x) (((uint32_t)(x) & MCAN_IE_ARAE_MASK) >> MCAN_IE_ARAE_SHIFT)

/*
 * PEDE (RW)
 *
 * Protocol Error in Data Phase Enable
 */
#define MCAN_IE_PEDE_MASK (0x10000000UL)
#define MCAN_IE_PEDE_SHIFT (28U)
#define MCAN_IE_PEDE_SET(x) (((uint32_t)(x) << MCAN_IE_PEDE_SHIFT) & MCAN_IE_PEDE_MASK)
#define MCAN_IE_PEDE_GET(x) (((uint32_t)(x) & MCAN_IE_PEDE_MASK) >> MCAN_IE_PEDE_SHIFT)

/*
 * PEAE (RW)
 *
 * Protocol Error in Arbitration Phase Enable
 */
#define MCAN_IE_PEAE_MASK (0x8000000UL)
#define MCAN_IE_PEAE_SHIFT (27U)
#define MCAN_IE_PEAE_SET(x) (((uint32_t)(x) << MCAN_IE_PEAE_SHIFT) & MCAN_IE_PEAE_MASK)
#define MCAN_IE_PEAE_GET(x) (((uint32_t)(x) & MCAN_IE_PEAE_MASK) >> MCAN_IE_PEAE_SHIFT)

/*
 * WDIE (RW)
 *
 * Watchdog Interrupt Enable
 */
#define MCAN_IE_WDIE_MASK (0x4000000UL)
#define MCAN_IE_WDIE_SHIFT (26U)
#define MCAN_IE_WDIE_SET(x) (((uint32_t)(x) << MCAN_IE_WDIE_SHIFT) & MCAN_IE_WDIE_MASK)
#define MCAN_IE_WDIE_GET(x) (((uint32_t)(x) & MCAN_IE_WDIE_MASK) >> MCAN_IE_WDIE_SHIFT)

/*
 * BOE (RW)
 *
 * Bus_Off Status Interrupt Enable
 */
#define MCAN_IE_BOE_MASK (0x2000000UL)
#define MCAN_IE_BOE_SHIFT (25U)
#define MCAN_IE_BOE_SET(x) (((uint32_t)(x) << MCAN_IE_BOE_SHIFT) & MCAN_IE_BOE_MASK)
#define MCAN_IE_BOE_GET(x) (((uint32_t)(x) & MCAN_IE_BOE_MASK) >> MCAN_IE_BOE_SHIFT)

/*
 * EWE (RW)
 *
 * Warning Status Interrupt Enable
 */
#define MCAN_IE_EWE_MASK (0x1000000UL)
#define MCAN_IE_EWE_SHIFT (24U)
#define MCAN_IE_EWE_SET(x) (((uint32_t)(x) << MCAN_IE_EWE_SHIFT) & MCAN_IE_EWE_MASK)
#define MCAN_IE_EWE_GET(x) (((uint32_t)(x) & MCAN_IE_EWE_MASK) >> MCAN_IE_EWE_SHIFT)

/*
 * EPE (RW)
 *
 * Error Passive Interrupt Enable
 */
#define MCAN_IE_EPE_MASK (0x800000UL)
#define MCAN_IE_EPE_SHIFT (23U)
#define MCAN_IE_EPE_SET(x) (((uint32_t)(x) << MCAN_IE_EPE_SHIFT) & MCAN_IE_EPE_MASK)
#define MCAN_IE_EPE_GET(x) (((uint32_t)(x) & MCAN_IE_EPE_MASK) >> MCAN_IE_EPE_SHIFT)

/*
 * ELOE (RW)
 *
 * Error Logging Overflow Interrupt Enable
 */
#define MCAN_IE_ELOE_MASK (0x400000UL)
#define MCAN_IE_ELOE_SHIFT (22U)
#define MCAN_IE_ELOE_SET(x) (((uint32_t)(x) << MCAN_IE_ELOE_SHIFT) & MCAN_IE_ELOE_MASK)
#define MCAN_IE_ELOE_GET(x) (((uint32_t)(x) & MCAN_IE_ELOE_MASK) >> MCAN_IE_ELOE_SHIFT)

/*
 * BEUE (RW)
 *
 * Bit Error Uncorrected Interrupt Enable
 */
#define MCAN_IE_BEUE_MASK (0x200000UL)
#define MCAN_IE_BEUE_SHIFT (21U)
#define MCAN_IE_BEUE_SET(x) (((uint32_t)(x) << MCAN_IE_BEUE_SHIFT) & MCAN_IE_BEUE_MASK)
#define MCAN_IE_BEUE_GET(x) (((uint32_t)(x) & MCAN_IE_BEUE_MASK) >> MCAN_IE_BEUE_SHIFT)

/*
 * BECE (RW)
 *
 * Bit Error Corrected Interrupt Enable
 */
#define MCAN_IE_BECE_MASK (0x100000UL)
#define MCAN_IE_BECE_SHIFT (20U)
#define MCAN_IE_BECE_SET(x) (((uint32_t)(x) << MCAN_IE_BECE_SHIFT) & MCAN_IE_BECE_MASK)
#define MCAN_IE_BECE_GET(x) (((uint32_t)(x) & MCAN_IE_BECE_MASK) >> MCAN_IE_BECE_SHIFT)

/*
 * DRXE (RW)
 *
 * Message stored to Dedicated Rx Buffer Interrupt Enable
 */
#define MCAN_IE_DRXE_MASK (0x80000UL)
#define MCAN_IE_DRXE_SHIFT (19U)
#define MCAN_IE_DRXE_SET(x) (((uint32_t)(x) << MCAN_IE_DRXE_SHIFT) & MCAN_IE_DRXE_MASK)
#define MCAN_IE_DRXE_GET(x) (((uint32_t)(x) & MCAN_IE_DRXE_MASK) >> MCAN_IE_DRXE_SHIFT)

/*
 * TOOE (RW)
 *
 * Timeout Occurred Interrupt Enable
 */
#define MCAN_IE_TOOE_MASK (0x40000UL)
#define MCAN_IE_TOOE_SHIFT (18U)
#define MCAN_IE_TOOE_SET(x) (((uint32_t)(x) << MCAN_IE_TOOE_SHIFT) & MCAN_IE_TOOE_MASK)
#define MCAN_IE_TOOE_GET(x) (((uint32_t)(x) & MCAN_IE_TOOE_MASK) >> MCAN_IE_TOOE_SHIFT)

/*
 * MRAFE (RW)
 *
 * Message RAM Access Failure Interrupt Enable
 */
#define MCAN_IE_MRAFE_MASK (0x20000UL)
#define MCAN_IE_MRAFE_SHIFT (17U)
#define MCAN_IE_MRAFE_SET(x) (((uint32_t)(x) << MCAN_IE_MRAFE_SHIFT) & MCAN_IE_MRAFE_MASK)
#define MCAN_IE_MRAFE_GET(x) (((uint32_t)(x) & MCAN_IE_MRAFE_MASK) >> MCAN_IE_MRAFE_SHIFT)

/*
 * TSWE (RW)
 *
 * Timestamp Wraparound Interrupt Enable
 */
#define MCAN_IE_TSWE_MASK (0x10000UL)
#define MCAN_IE_TSWE_SHIFT (16U)
#define MCAN_IE_TSWE_SET(x) (((uint32_t)(x) << MCAN_IE_TSWE_SHIFT) & MCAN_IE_TSWE_MASK)
#define MCAN_IE_TSWE_GET(x) (((uint32_t)(x) & MCAN_IE_TSWE_MASK) >> MCAN_IE_TSWE_SHIFT)

/*
 * TEFLE (RW)
 *
 * Tx Event FIFO Event Lost Interrupt Enable
 */
#define MCAN_IE_TEFLE_MASK (0x8000U)
#define MCAN_IE_TEFLE_SHIFT (15U)
#define MCAN_IE_TEFLE_SET(x) (((uint32_t)(x) << MCAN_IE_TEFLE_SHIFT) & MCAN_IE_TEFLE_MASK)
#define MCAN_IE_TEFLE_GET(x) (((uint32_t)(x) & MCAN_IE_TEFLE_MASK) >> MCAN_IE_TEFLE_SHIFT)

/*
 * TEFFE (RW)
 *
 * Tx Event FIFO Full Interrupt Enable
 */
#define MCAN_IE_TEFFE_MASK (0x4000U)
#define MCAN_IE_TEFFE_SHIFT (14U)
#define MCAN_IE_TEFFE_SET(x) (((uint32_t)(x) << MCAN_IE_TEFFE_SHIFT) & MCAN_IE_TEFFE_MASK)
#define MCAN_IE_TEFFE_GET(x) (((uint32_t)(x) & MCAN_IE_TEFFE_MASK) >> MCAN_IE_TEFFE_SHIFT)

/*
 * TEFWE (RW)
 *
 * Tx Event FIFO Watermark Reached Interrupt Enable
 */
#define MCAN_IE_TEFWE_MASK (0x2000U)
#define MCAN_IE_TEFWE_SHIFT (13U)
#define MCAN_IE_TEFWE_SET(x) (((uint32_t)(x) << MCAN_IE_TEFWE_SHIFT) & MCAN_IE_TEFWE_MASK)
#define MCAN_IE_TEFWE_GET(x) (((uint32_t)(x) & MCAN_IE_TEFWE_MASK) >> MCAN_IE_TEFWE_SHIFT)

/*
 * TEFNE (RW)
 *
 * Tx Event FIFO New Entry Interrupt Enable
 */
#define MCAN_IE_TEFNE_MASK (0x1000U)
#define MCAN_IE_TEFNE_SHIFT (12U)
#define MCAN_IE_TEFNE_SET(x) (((uint32_t)(x) << MCAN_IE_TEFNE_SHIFT) & MCAN_IE_TEFNE_MASK)
#define MCAN_IE_TEFNE_GET(x) (((uint32_t)(x) & MCAN_IE_TEFNE_MASK) >> MCAN_IE_TEFNE_SHIFT)

/*
 * TFEE (RW)
 *
 * Tx FIFO Empty Interrupt Enable
 */
#define MCAN_IE_TFEE_MASK (0x800U)
#define MCAN_IE_TFEE_SHIFT (11U)
#define MCAN_IE_TFEE_SET(x) (((uint32_t)(x) << MCAN_IE_TFEE_SHIFT) & MCAN_IE_TFEE_MASK)
#define MCAN_IE_TFEE_GET(x) (((uint32_t)(x) & MCAN_IE_TFEE_MASK) >> MCAN_IE_TFEE_SHIFT)

/*
 * TCFE (RW)
 *
 * Transmission Cancellation Finished Interrupt Enable
 */
#define MCAN_IE_TCFE_MASK (0x400U)
#define MCAN_IE_TCFE_SHIFT (10U)
#define MCAN_IE_TCFE_SET(x) (((uint32_t)(x) << MCAN_IE_TCFE_SHIFT) & MCAN_IE_TCFE_MASK)
#define MCAN_IE_TCFE_GET(x) (((uint32_t)(x) & MCAN_IE_TCFE_MASK) >> MCAN_IE_TCFE_SHIFT)

/*
 * TCE (RW)
 *
 * Transmission Completed Interrupt Enable
 */
#define MCAN_IE_TCE_MASK (0x200U)
#define MCAN_IE_TCE_SHIFT (9U)
#define MCAN_IE_TCE_SET(x) (((uint32_t)(x) << MCAN_IE_TCE_SHIFT) & MCAN_IE_TCE_MASK)
#define MCAN_IE_TCE_GET(x) (((uint32_t)(x) & MCAN_IE_TCE_MASK) >> MCAN_IE_TCE_SHIFT)

/*
 * HPME (RW)
 *
 * High Priority Message Interrupt Enable
 */
#define MCAN_IE_HPME_MASK (0x100U)
#define MCAN_IE_HPME_SHIFT (8U)
#define MCAN_IE_HPME_SET(x) (((uint32_t)(x) << MCAN_IE_HPME_SHIFT) & MCAN_IE_HPME_MASK)
#define MCAN_IE_HPME_GET(x) (((uint32_t)(x) & MCAN_IE_HPME_MASK) >> MCAN_IE_HPME_SHIFT)

/*
 * RF1LE (RW)
 *
 * Rx FIFO 1 Message Lost Interrupt Enable
 */
#define MCAN_IE_RF1LE_MASK (0x80U)
#define MCAN_IE_RF1LE_SHIFT (7U)
#define MCAN_IE_RF1LE_SET(x) (((uint32_t)(x) << MCAN_IE_RF1LE_SHIFT) & MCAN_IE_RF1LE_MASK)
#define MCAN_IE_RF1LE_GET(x) (((uint32_t)(x) & MCAN_IE_RF1LE_MASK) >> MCAN_IE_RF1LE_SHIFT)

/*
 * RF1FE (RW)
 *
 * Rx FIFO 1 Full Interrupt Enable
 */
#define MCAN_IE_RF1FE_MASK (0x40U)
#define MCAN_IE_RF1FE_SHIFT (6U)
#define MCAN_IE_RF1FE_SET(x) (((uint32_t)(x) << MCAN_IE_RF1FE_SHIFT) & MCAN_IE_RF1FE_MASK)
#define MCAN_IE_RF1FE_GET(x) (((uint32_t)(x) & MCAN_IE_RF1FE_MASK) >> MCAN_IE_RF1FE_SHIFT)

/*
 * RF1WE (RW)
 *
 * Rx FIFO 1 Watermark Reached Interrupt Enable
 */
#define MCAN_IE_RF1WE_MASK (0x20U)
#define MCAN_IE_RF1WE_SHIFT (5U)
#define MCAN_IE_RF1WE_SET(x) (((uint32_t)(x) << MCAN_IE_RF1WE_SHIFT) & MCAN_IE_RF1WE_MASK)
#define MCAN_IE_RF1WE_GET(x) (((uint32_t)(x) & MCAN_IE_RF1WE_MASK) >> MCAN_IE_RF1WE_SHIFT)

/*
 * RF1NE (RW)
 *
 * Rx FIFO 1 New Message Interrupt Enable
 */
#define MCAN_IE_RF1NE_MASK (0x10U)
#define MCAN_IE_RF1NE_SHIFT (4U)
#define MCAN_IE_RF1NE_SET(x) (((uint32_t)(x) << MCAN_IE_RF1NE_SHIFT) & MCAN_IE_RF1NE_MASK)
#define MCAN_IE_RF1NE_GET(x) (((uint32_t)(x) & MCAN_IE_RF1NE_MASK) >> MCAN_IE_RF1NE_SHIFT)

/*
 * RF0LE (RW)
 *
 * Rx FIFO 0 Message Lost Interrupt Enable
 */
#define MCAN_IE_RF0LE_MASK (0x8U)
#define MCAN_IE_RF0LE_SHIFT (3U)
#define MCAN_IE_RF0LE_SET(x) (((uint32_t)(x) << MCAN_IE_RF0LE_SHIFT) & MCAN_IE_RF0LE_MASK)
#define MCAN_IE_RF0LE_GET(x) (((uint32_t)(x) & MCAN_IE_RF0LE_MASK) >> MCAN_IE_RF0LE_SHIFT)

/*
 * RF0FE (RW)
 *
 * Rx FIFO 0 Full Interrupt Enable
 */
#define MCAN_IE_RF0FE_MASK (0x4U)
#define MCAN_IE_RF0FE_SHIFT (2U)
#define MCAN_IE_RF0FE_SET(x) (((uint32_t)(x) << MCAN_IE_RF0FE_SHIFT) & MCAN_IE_RF0FE_MASK)
#define MCAN_IE_RF0FE_GET(x) (((uint32_t)(x) & MCAN_IE_RF0FE_MASK) >> MCAN_IE_RF0FE_SHIFT)

/*
 * RF0WE (RW)
 *
 * Rx FIFO 0 Watermark Reached Interrupt Enable
 */
#define MCAN_IE_RF0WE_MASK (0x2U)
#define MCAN_IE_RF0WE_SHIFT (1U)
#define MCAN_IE_RF0WE_SET(x) (((uint32_t)(x) << MCAN_IE_RF0WE_SHIFT) & MCAN_IE_RF0WE_MASK)
#define MCAN_IE_RF0WE_GET(x) (((uint32_t)(x) & MCAN_IE_RF0WE_MASK) >> MCAN_IE_RF0WE_SHIFT)

/*
 * RF0NE (RW)
 *
 * Rx FIFO 0 New Message Interrupt Enable
 */
#define MCAN_IE_RF0NE_MASK (0x1U)
#define MCAN_IE_RF0NE_SHIFT (0U)
#define MCAN_IE_RF0NE_SET(x) (((uint32_t)(x) << MCAN_IE_RF0NE_SHIFT) & MCAN_IE_RF0NE_MASK)
#define MCAN_IE_RF0NE_GET(x) (((uint32_t)(x) & MCAN_IE_RF0NE_MASK) >> MCAN_IE_RF0NE_SHIFT)

/* Bitfield definition for register: ILS */
/*
 * ARAL (RW)
 *
 * Access to Reserved Address Line
 */
#define MCAN_ILS_ARAL_MASK (0x20000000UL)
#define MCAN_ILS_ARAL_SHIFT (29U)
#define MCAN_ILS_ARAL_SET(x) (((uint32_t)(x) << MCAN_ILS_ARAL_SHIFT) & MCAN_ILS_ARAL_MASK)
#define MCAN_ILS_ARAL_GET(x) (((uint32_t)(x) & MCAN_ILS_ARAL_MASK) >> MCAN_ILS_ARAL_SHIFT)

/*
 * PEDL (RW)
 *
 * Protocol Error in Data Phase Line
 */
#define MCAN_ILS_PEDL_MASK (0x10000000UL)
#define MCAN_ILS_PEDL_SHIFT (28U)
#define MCAN_ILS_PEDL_SET(x) (((uint32_t)(x) << MCAN_ILS_PEDL_SHIFT) & MCAN_ILS_PEDL_MASK)
#define MCAN_ILS_PEDL_GET(x) (((uint32_t)(x) & MCAN_ILS_PEDL_MASK) >> MCAN_ILS_PEDL_SHIFT)

/*
 * PEAL (RW)
 *
 * Protocol Error in Arbitration Phase Line
 */
#define MCAN_ILS_PEAL_MASK (0x8000000UL)
#define MCAN_ILS_PEAL_SHIFT (27U)
#define MCAN_ILS_PEAL_SET(x) (((uint32_t)(x) << MCAN_ILS_PEAL_SHIFT) & MCAN_ILS_PEAL_MASK)
#define MCAN_ILS_PEAL_GET(x) (((uint32_t)(x) & MCAN_ILS_PEAL_MASK) >> MCAN_ILS_PEAL_SHIFT)

/*
 * WDIL (RW)
 *
 * Watchdog Interrupt Line
 */
#define MCAN_ILS_WDIL_MASK (0x4000000UL)
#define MCAN_ILS_WDIL_SHIFT (26U)
#define MCAN_ILS_WDIL_SET(x) (((uint32_t)(x) << MCAN_ILS_WDIL_SHIFT) & MCAN_ILS_WDIL_MASK)
#define MCAN_ILS_WDIL_GET(x) (((uint32_t)(x) & MCAN_ILS_WDIL_MASK) >> MCAN_ILS_WDIL_SHIFT)

/*
 * BOL (RW)
 *
 * Bus_Off Status Interrupt Line
 */
#define MCAN_ILS_BOL_MASK (0x2000000UL)
#define MCAN_ILS_BOL_SHIFT (25U)
#define MCAN_ILS_BOL_SET(x) (((uint32_t)(x) << MCAN_ILS_BOL_SHIFT) & MCAN_ILS_BOL_MASK)
#define MCAN_ILS_BOL_GET(x) (((uint32_t)(x) & MCAN_ILS_BOL_MASK) >> MCAN_ILS_BOL_SHIFT)

/*
 * EWL (RW)
 *
 * Warning Status Interrupt Line
 */
#define MCAN_ILS_EWL_MASK (0x1000000UL)
#define MCAN_ILS_EWL_SHIFT (24U)
#define MCAN_ILS_EWL_SET(x) (((uint32_t)(x) << MCAN_ILS_EWL_SHIFT) & MCAN_ILS_EWL_MASK)
#define MCAN_ILS_EWL_GET(x) (((uint32_t)(x) & MCAN_ILS_EWL_MASK) >> MCAN_ILS_EWL_SHIFT)

/*
 * EPL (RW)
 *
 * Error Passive Interrupt Line
 */
#define MCAN_ILS_EPL_MASK (0x800000UL)
#define MCAN_ILS_EPL_SHIFT (23U)
#define MCAN_ILS_EPL_SET(x) (((uint32_t)(x) << MCAN_ILS_EPL_SHIFT) & MCAN_ILS_EPL_MASK)
#define MCAN_ILS_EPL_GET(x) (((uint32_t)(x) & MCAN_ILS_EPL_MASK) >> MCAN_ILS_EPL_SHIFT)

/*
 * ELOL (RW)
 *
 * Error Logging Overflow Interrupt Line
 */
#define MCAN_ILS_ELOL_MASK (0x400000UL)
#define MCAN_ILS_ELOL_SHIFT (22U)
#define MCAN_ILS_ELOL_SET(x) (((uint32_t)(x) << MCAN_ILS_ELOL_SHIFT) & MCAN_ILS_ELOL_MASK)
#define MCAN_ILS_ELOL_GET(x) (((uint32_t)(x) & MCAN_ILS_ELOL_MASK) >> MCAN_ILS_ELOL_SHIFT)

/*
 * BEUL (RW)
 *
 * Bit Error Uncorrected Interrupt Line
 */
#define MCAN_ILS_BEUL_MASK (0x200000UL)
#define MCAN_ILS_BEUL_SHIFT (21U)
#define MCAN_ILS_BEUL_SET(x) (((uint32_t)(x) << MCAN_ILS_BEUL_SHIFT) & MCAN_ILS_BEUL_MASK)
#define MCAN_ILS_BEUL_GET(x) (((uint32_t)(x) & MCAN_ILS_BEUL_MASK) >> MCAN_ILS_BEUL_SHIFT)

/*
 * BECL (RW)
 *
 * Bit Error Corrected Interrupt Line
 */
#define MCAN_ILS_BECL_MASK (0x100000UL)
#define MCAN_ILS_BECL_SHIFT (20U)
#define MCAN_ILS_BECL_SET(x) (((uint32_t)(x) << MCAN_ILS_BECL_SHIFT) & MCAN_ILS_BECL_MASK)
#define MCAN_ILS_BECL_GET(x) (((uint32_t)(x) & MCAN_ILS_BECL_MASK) >> MCAN_ILS_BECL_SHIFT)

/*
 * DRXL (RW)
 *
 * Message stored to Dedicated Rx Buffer Interrupt Line
 */
#define MCAN_ILS_DRXL_MASK (0x80000UL)
#define MCAN_ILS_DRXL_SHIFT (19U)
#define MCAN_ILS_DRXL_SET(x) (((uint32_t)(x) << MCAN_ILS_DRXL_SHIFT) & MCAN_ILS_DRXL_MASK)
#define MCAN_ILS_DRXL_GET(x) (((uint32_t)(x) & MCAN_ILS_DRXL_MASK) >> MCAN_ILS_DRXL_SHIFT)

/*
 * TOOL (RW)
 *
 * Timeout Occurred Interrupt Line
 */
#define MCAN_ILS_TOOL_MASK (0x40000UL)
#define MCAN_ILS_TOOL_SHIFT (18U)
#define MCAN_ILS_TOOL_SET(x) (((uint32_t)(x) << MCAN_ILS_TOOL_SHIFT) & MCAN_ILS_TOOL_MASK)
#define MCAN_ILS_TOOL_GET(x) (((uint32_t)(x) & MCAN_ILS_TOOL_MASK) >> MCAN_ILS_TOOL_SHIFT)

/*
 * MRAFL (RW)
 *
 * Message RAM Access Failure Interrupt Line
 */
#define MCAN_ILS_MRAFL_MASK (0x20000UL)
#define MCAN_ILS_MRAFL_SHIFT (17U)
#define MCAN_ILS_MRAFL_SET(x) (((uint32_t)(x) << MCAN_ILS_MRAFL_SHIFT) & MCAN_ILS_MRAFL_MASK)
#define MCAN_ILS_MRAFL_GET(x) (((uint32_t)(x) & MCAN_ILS_MRAFL_MASK) >> MCAN_ILS_MRAFL_SHIFT)

/*
 * TSWL (RW)
 *
 * Timestamp Wraparound Interrupt Line
 */
#define MCAN_ILS_TSWL_MASK (0x10000UL)
#define MCAN_ILS_TSWL_SHIFT (16U)
#define MCAN_ILS_TSWL_SET(x) (((uint32_t)(x) << MCAN_ILS_TSWL_SHIFT) & MCAN_ILS_TSWL_MASK)
#define MCAN_ILS_TSWL_GET(x) (((uint32_t)(x) & MCAN_ILS_TSWL_MASK) >> MCAN_ILS_TSWL_SHIFT)

/*
 * TEFLL (RW)
 *
 * Tx Event FIFO Event Lost Interrupt Line
 */
#define MCAN_ILS_TEFLL_MASK (0x8000U)
#define MCAN_ILS_TEFLL_SHIFT (15U)
#define MCAN_ILS_TEFLL_SET(x) (((uint32_t)(x) << MCAN_ILS_TEFLL_SHIFT) & MCAN_ILS_TEFLL_MASK)
#define MCAN_ILS_TEFLL_GET(x) (((uint32_t)(x) & MCAN_ILS_TEFLL_MASK) >> MCAN_ILS_TEFLL_SHIFT)

/*
 * TEFFL (RW)
 *
 * Tx Event FIFO Full Interrupt Line
 */
#define MCAN_ILS_TEFFL_MASK (0x4000U)
#define MCAN_ILS_TEFFL_SHIFT (14U)
#define MCAN_ILS_TEFFL_SET(x) (((uint32_t)(x) << MCAN_ILS_TEFFL_SHIFT) & MCAN_ILS_TEFFL_MASK)
#define MCAN_ILS_TEFFL_GET(x) (((uint32_t)(x) & MCAN_ILS_TEFFL_MASK) >> MCAN_ILS_TEFFL_SHIFT)

/*
 * TEFWL (RW)
 *
 * Tx Event FIFO Watermark Reached Interrupt Line
 */
#define MCAN_ILS_TEFWL_MASK (0x2000U)
#define MCAN_ILS_TEFWL_SHIFT (13U)
#define MCAN_ILS_TEFWL_SET(x) (((uint32_t)(x) << MCAN_ILS_TEFWL_SHIFT) & MCAN_ILS_TEFWL_MASK)
#define MCAN_ILS_TEFWL_GET(x) (((uint32_t)(x) & MCAN_ILS_TEFWL_MASK) >> MCAN_ILS_TEFWL_SHIFT)

/*
 * TEFNL (RW)
 *
 * Tx Event FIFO New Entry Interrupt Line
 */
#define MCAN_ILS_TEFNL_MASK (0x1000U)
#define MCAN_ILS_TEFNL_SHIFT (12U)
#define MCAN_ILS_TEFNL_SET(x) (((uint32_t)(x) << MCAN_ILS_TEFNL_SHIFT) & MCAN_ILS_TEFNL_MASK)
#define MCAN_ILS_TEFNL_GET(x) (((uint32_t)(x) & MCAN_ILS_TEFNL_MASK) >> MCAN_ILS_TEFNL_SHIFT)

/*
 * TFEL (RW)
 *
 * Tx FIFO Empty Interrupt Line
 */
#define MCAN_ILS_TFEL_MASK (0x800U)
#define MCAN_ILS_TFEL_SHIFT (11U)
#define MCAN_ILS_TFEL_SET(x) (((uint32_t)(x) << MCAN_ILS_TFEL_SHIFT) & MCAN_ILS_TFEL_MASK)
#define MCAN_ILS_TFEL_GET(x) (((uint32_t)(x) & MCAN_ILS_TFEL_MASK) >> MCAN_ILS_TFEL_SHIFT)

/*
 * TCFL (RW)
 *
 * Transmission Cancellation Finished Interrupt Line
 */
#define MCAN_ILS_TCFL_MASK (0x400U)
#define MCAN_ILS_TCFL_SHIFT (10U)
#define MCAN_ILS_TCFL_SET(x) (((uint32_t)(x) << MCAN_ILS_TCFL_SHIFT) & MCAN_ILS_TCFL_MASK)
#define MCAN_ILS_TCFL_GET(x) (((uint32_t)(x) & MCAN_ILS_TCFL_MASK) >> MCAN_ILS_TCFL_SHIFT)

/*
 * TCL (RW)
 *
 * Transmission Completed Interrupt Line
 */
#define MCAN_ILS_TCL_MASK (0x200U)
#define MCAN_ILS_TCL_SHIFT (9U)
#define MCAN_ILS_TCL_SET(x) (((uint32_t)(x) << MCAN_ILS_TCL_SHIFT) & MCAN_ILS_TCL_MASK)
#define MCAN_ILS_TCL_GET(x) (((uint32_t)(x) & MCAN_ILS_TCL_MASK) >> MCAN_ILS_TCL_SHIFT)

/*
 * HPML (RW)
 *
 * High Priority Message Interrupt Line
 */
#define MCAN_ILS_HPML_MASK (0x100U)
#define MCAN_ILS_HPML_SHIFT (8U)
#define MCAN_ILS_HPML_SET(x) (((uint32_t)(x) << MCAN_ILS_HPML_SHIFT) & MCAN_ILS_HPML_MASK)
#define MCAN_ILS_HPML_GET(x) (((uint32_t)(x) & MCAN_ILS_HPML_MASK) >> MCAN_ILS_HPML_SHIFT)

/*
 * RF1LL (RW)
 *
 * Rx FIFO 1 Message Lost Interrupt Line
 */
#define MCAN_ILS_RF1LL_MASK (0x80U)
#define MCAN_ILS_RF1LL_SHIFT (7U)
#define MCAN_ILS_RF1LL_SET(x) (((uint32_t)(x) << MCAN_ILS_RF1LL_SHIFT) & MCAN_ILS_RF1LL_MASK)
#define MCAN_ILS_RF1LL_GET(x) (((uint32_t)(x) & MCAN_ILS_RF1LL_MASK) >> MCAN_ILS_RF1LL_SHIFT)

/*
 * RF1FL (RW)
 *
 * Rx FIFO 1 Full Interrupt Line
 */
#define MCAN_ILS_RF1FL_MASK (0x40U)
#define MCAN_ILS_RF1FL_SHIFT (6U)
#define MCAN_ILS_RF1FL_SET(x) (((uint32_t)(x) << MCAN_ILS_RF1FL_SHIFT) & MCAN_ILS_RF1FL_MASK)
#define MCAN_ILS_RF1FL_GET(x) (((uint32_t)(x) & MCAN_ILS_RF1FL_MASK) >> MCAN_ILS_RF1FL_SHIFT)

/*
 * RF1WL (RW)
 *
 * Rx FIFO 1 Watermark Reached Interrupt Line
 */
#define MCAN_ILS_RF1WL_MASK (0x20U)
#define MCAN_ILS_RF1WL_SHIFT (5U)
#define MCAN_ILS_RF1WL_SET(x) (((uint32_t)(x) << MCAN_ILS_RF1WL_SHIFT) & MCAN_ILS_RF1WL_MASK)
#define MCAN_ILS_RF1WL_GET(x) (((uint32_t)(x) & MCAN_ILS_RF1WL_MASK) >> MCAN_ILS_RF1WL_SHIFT)

/*
 * RF1NL (RW)
 *
 * Rx FIFO 1 New Message Interrupt Line
 */
#define MCAN_ILS_RF1NL_MASK (0x10U)
#define MCAN_ILS_RF1NL_SHIFT (4U)
#define MCAN_ILS_RF1NL_SET(x) (((uint32_t)(x) << MCAN_ILS_RF1NL_SHIFT) & MCAN_ILS_RF1NL_MASK)
#define MCAN_ILS_RF1NL_GET(x) (((uint32_t)(x) & MCAN_ILS_RF1NL_MASK) >> MCAN_ILS_RF1NL_SHIFT)

/*
 * RF0LL (RW)
 *
 * Rx FIFO 0 Message Lost Interrupt Line
 */
#define MCAN_ILS_RF0LL_MASK (0x8U)
#define MCAN_ILS_RF0LL_SHIFT (3U)
#define MCAN_ILS_RF0LL_SET(x) (((uint32_t)(x) << MCAN_ILS_RF0LL_SHIFT) & MCAN_ILS_RF0LL_MASK)
#define MCAN_ILS_RF0LL_GET(x) (((uint32_t)(x) & MCAN_ILS_RF0LL_MASK) >> MCAN_ILS_RF0LL_SHIFT)

/*
 * RF0FL (RW)
 *
 * Rx FIFO 0 Full Interrupt Line
 */
#define MCAN_ILS_RF0FL_MASK (0x4U)
#define MCAN_ILS_RF0FL_SHIFT (2U)
#define MCAN_ILS_RF0FL_SET(x) (((uint32_t)(x) << MCAN_ILS_RF0FL_SHIFT) & MCAN_ILS_RF0FL_MASK)
#define MCAN_ILS_RF0FL_GET(x) (((uint32_t)(x) & MCAN_ILS_RF0FL_MASK) >> MCAN_ILS_RF0FL_SHIFT)

/*
 * RF0WL (RW)
 *
 * Rx FIFO 0 Watermark Reached Interrupt Line
 */
#define MCAN_ILS_RF0WL_MASK (0x2U)
#define MCAN_ILS_RF0WL_SHIFT (1U)
#define MCAN_ILS_RF0WL_SET(x) (((uint32_t)(x) << MCAN_ILS_RF0WL_SHIFT) & MCAN_ILS_RF0WL_MASK)
#define MCAN_ILS_RF0WL_GET(x) (((uint32_t)(x) & MCAN_ILS_RF0WL_MASK) >> MCAN_ILS_RF0WL_SHIFT)

/*
 * RF0NL (RW)
 *
 * Rx FIFO 0 New Message Interrupt Line
 */
#define MCAN_ILS_RF0NL_MASK (0x1U)
#define MCAN_ILS_RF0NL_SHIFT (0U)
#define MCAN_ILS_RF0NL_SET(x) (((uint32_t)(x) << MCAN_ILS_RF0NL_SHIFT) & MCAN_ILS_RF0NL_MASK)
#define MCAN_ILS_RF0NL_GET(x) (((uint32_t)(x) & MCAN_ILS_RF0NL_MASK) >> MCAN_ILS_RF0NL_SHIFT)

/* Bitfield definition for register: ILE */
/*
 * EINT1 (RW)
 *
 * Enable Interrupt Line 1
 * 0= Interrupt line m_can_int1 disabled
 * 1= Interrupt line m_can_int1 enabled
 */
#define MCAN_ILE_EINT1_MASK (0x2U)
#define MCAN_ILE_EINT1_SHIFT (1U)
#define MCAN_ILE_EINT1_SET(x) (((uint32_t)(x) << MCAN_ILE_EINT1_SHIFT) & MCAN_ILE_EINT1_MASK)
#define MCAN_ILE_EINT1_GET(x) (((uint32_t)(x) & MCAN_ILE_EINT1_MASK) >> MCAN_ILE_EINT1_SHIFT)

/*
 * EINT0 (RW)
 *
 * Enable Interrupt Line 0
 * 0= Interrupt line m_can_int0 disabled
 * 1= Interrupt line m_can_int0 enabled
 */
#define MCAN_ILE_EINT0_MASK (0x1U)
#define MCAN_ILE_EINT0_SHIFT (0U)
#define MCAN_ILE_EINT0_SET(x) (((uint32_t)(x) << MCAN_ILE_EINT0_SHIFT) & MCAN_ILE_EINT0_MASK)
#define MCAN_ILE_EINT0_GET(x) (((uint32_t)(x) & MCAN_ILE_EINT0_MASK) >> MCAN_ILE_EINT0_SHIFT)

/* Bitfield definition for register: GFC */
/*
 * ANFS (RW)
 *
 * Accept Non-matching Frames Standard
 * Defines how received messages with 11-bit IDs that do not match any element of the filter list are treated.
 * 00= Accept in Rx FIFO 0
 * 01= Accept in Rx FIFO 1
 * 10= Reject
 * 11= Reject
 */
#define MCAN_GFC_ANFS_MASK (0x30U)
#define MCAN_GFC_ANFS_SHIFT (4U)
#define MCAN_GFC_ANFS_SET(x) (((uint32_t)(x) << MCAN_GFC_ANFS_SHIFT) & MCAN_GFC_ANFS_MASK)
#define MCAN_GFC_ANFS_GET(x) (((uint32_t)(x) & MCAN_GFC_ANFS_MASK) >> MCAN_GFC_ANFS_SHIFT)

/*
 * ANFE (RW)
 *
 * Accept Non-matching Frames Extended
 * Defines how received messages with 29-bit IDs that do not match any element of the filter list are treated.
 * 00= Accept in Rx FIFO 0
 * 01= Accept in Rx FIFO 1
 * 10= Reject
 * 11= Reject
 */
#define MCAN_GFC_ANFE_MASK (0xCU)
#define MCAN_GFC_ANFE_SHIFT (2U)
#define MCAN_GFC_ANFE_SET(x) (((uint32_t)(x) << MCAN_GFC_ANFE_SHIFT) & MCAN_GFC_ANFE_MASK)
#define MCAN_GFC_ANFE_GET(x) (((uint32_t)(x) & MCAN_GFC_ANFE_MASK) >> MCAN_GFC_ANFE_SHIFT)

/*
 * RRFS (RW)
 *
 * Reject Remote Frames Standard
 * 0= Filter remote frames with 11-bit standard IDs
 * 1= Reject all remote frames with 11-bit standard IDs
 */
#define MCAN_GFC_RRFS_MASK (0x2U)
#define MCAN_GFC_RRFS_SHIFT (1U)
#define MCAN_GFC_RRFS_SET(x) (((uint32_t)(x) << MCAN_GFC_RRFS_SHIFT) & MCAN_GFC_RRFS_MASK)
#define MCAN_GFC_RRFS_GET(x) (((uint32_t)(x) & MCAN_GFC_RRFS_MASK) >> MCAN_GFC_RRFS_SHIFT)

/*
 * RRFE (RW)
 *
 * Reject Remote Frames Extended
 * 0= Filter remote frames with 29-bit extended IDs
 * 1= Reject all remote frames with 29-bit extended IDs
 */
#define MCAN_GFC_RRFE_MASK (0x1U)
#define MCAN_GFC_RRFE_SHIFT (0U)
#define MCAN_GFC_RRFE_SET(x) (((uint32_t)(x) << MCAN_GFC_RRFE_SHIFT) & MCAN_GFC_RRFE_MASK)
#define MCAN_GFC_RRFE_GET(x) (((uint32_t)(x) & MCAN_GFC_RRFE_MASK) >> MCAN_GFC_RRFE_SHIFT)

/* Bitfield definition for register: SIDFC */
/*
 * LSS (RW)
 *
 * List Size Standard
 * 0= No standard Message ID filter
 * 1-128= Number of standard Message ID filter elements
 * >128= Values greater than 128 are interpreted as 128
 */
#define MCAN_SIDFC_LSS_MASK (0xFF0000UL)
#define MCAN_SIDFC_LSS_SHIFT (16U)
#define MCAN_SIDFC_LSS_SET(x) (((uint32_t)(x) << MCAN_SIDFC_LSS_SHIFT) & MCAN_SIDFC_LSS_MASK)
#define MCAN_SIDFC_LSS_GET(x) (((uint32_t)(x) & MCAN_SIDFC_LSS_MASK) >> MCAN_SIDFC_LSS_SHIFT)

/*
 * FLSSA (RW)
 *
 * Filter List Standard Start Address
 * Start address of standard Message ID filter list (32-bit word address)
 */
#define MCAN_SIDFC_FLSSA_MASK (0xFFFCU)
#define MCAN_SIDFC_FLSSA_SHIFT (2U)
#define MCAN_SIDFC_FLSSA_SET(x) (((uint32_t)(x) << MCAN_SIDFC_FLSSA_SHIFT) & MCAN_SIDFC_FLSSA_MASK)
#define MCAN_SIDFC_FLSSA_GET(x) (((uint32_t)(x) & MCAN_SIDFC_FLSSA_MASK) >> MCAN_SIDFC_FLSSA_SHIFT)

/* Bitfield definition for register: XIDFC */
/*
 * LSE (RW)
 *
 * List Size Extended
 * 0= No extended Message ID filter
 * 1-64= Number of extended Message ID filter elements
 * >64= Values greater than 64 are interpreted as 64
 */
#define MCAN_XIDFC_LSE_MASK (0x7F0000UL)
#define MCAN_XIDFC_LSE_SHIFT (16U)
#define MCAN_XIDFC_LSE_SET(x) (((uint32_t)(x) << MCAN_XIDFC_LSE_SHIFT) & MCAN_XIDFC_LSE_MASK)
#define MCAN_XIDFC_LSE_GET(x) (((uint32_t)(x) & MCAN_XIDFC_LSE_MASK) >> MCAN_XIDFC_LSE_SHIFT)

/*
 * FLESA (RW)
 *
 * Filter List Extended Start Address
 * Start address of extended Message ID filter list (32-bit word address).
 */
#define MCAN_XIDFC_FLESA_MASK (0xFFFCU)
#define MCAN_XIDFC_FLESA_SHIFT (2U)
#define MCAN_XIDFC_FLESA_SET(x) (((uint32_t)(x) << MCAN_XIDFC_FLESA_SHIFT) & MCAN_XIDFC_FLESA_MASK)
#define MCAN_XIDFC_FLESA_GET(x) (((uint32_t)(x) & MCAN_XIDFC_FLESA_MASK) >> MCAN_XIDFC_FLESA_SHIFT)

/* Bitfield definition for register: XIDAM */
/*
 * EIDM (RW)
 *
 * Extended ID Mask
 * For acceptance filtering of extended frames the Extended ID AND Mask is ANDed with the Message ID of a received frame.
 *  Intended for masking of 29-bit IDs in SAE J1939. With the reset value of all bits set to one the mask is not active.
 */
#define MCAN_XIDAM_EIDM_MASK (0x1FFFFFFFUL)
#define MCAN_XIDAM_EIDM_SHIFT (0U)
#define MCAN_XIDAM_EIDM_SET(x) (((uint32_t)(x) << MCAN_XIDAM_EIDM_SHIFT) & MCAN_XIDAM_EIDM_MASK)
#define MCAN_XIDAM_EIDM_GET(x) (((uint32_t)(x) & MCAN_XIDAM_EIDM_MASK) >> MCAN_XIDAM_EIDM_SHIFT)

/* Bitfield definition for register: HPMS */
/*
 * FLST (R)
 *
 * Filter List
 * Indicates the filter list of the matching filter element.
 * 0= Standard Filter List
 * 1= Extended Filter List
 */
#define MCAN_HPMS_FLST_MASK (0x8000U)
#define MCAN_HPMS_FLST_SHIFT (15U)
#define MCAN_HPMS_FLST_GET(x) (((uint32_t)(x) & MCAN_HPMS_FLST_MASK) >> MCAN_HPMS_FLST_SHIFT)

/*
 * FIDX (R)
 *
 * Filter Index
 * Index of matching filter element. Range is 0 to SIDFC.LSS - 1 resp. XIDFC.LSE - 1.
 */
#define MCAN_HPMS_FIDX_MASK (0x7F00U)
#define MCAN_HPMS_FIDX_SHIFT (8U)
#define MCAN_HPMS_FIDX_GET(x) (((uint32_t)(x) & MCAN_HPMS_FIDX_MASK) >> MCAN_HPMS_FIDX_SHIFT)

/*
 * MSI (R)
 *
 * Message Storage Indicator
 * 00= No FIFO selected
 * 01= FIFO message lost
 * 10= Message stored in FIFO 0
 * 11= Message stored in FIFO 1
 */
#define MCAN_HPMS_MSI_MASK (0xC0U)
#define MCAN_HPMS_MSI_SHIFT (6U)
#define MCAN_HPMS_MSI_GET(x) (((uint32_t)(x) & MCAN_HPMS_MSI_MASK) >> MCAN_HPMS_MSI_SHIFT)

/*
 * BIDX (R)
 *
 * Buffer Index
 * Index of Rx FIFO element to which the message was stored. Only valid when MSI[1] = ‘1’.
 */
#define MCAN_HPMS_BIDX_MASK (0x3FU)
#define MCAN_HPMS_BIDX_SHIFT (0U)
#define MCAN_HPMS_BIDX_GET(x) (((uint32_t)(x) & MCAN_HPMS_BIDX_MASK) >> MCAN_HPMS_BIDX_SHIFT)

/* Bitfield definition for register: NDAT1 */
/*
 * ND1 (RW)
 *
 * New Data[31:0]
 * The register holds the New Data flags of Rx Buffers 0 to 31. The flags are set when the respective Rx Buffer has been updated from a received frame.
 * The flags remain set until the Host clears them.A flag is cleared by writing a ’1’ to the corresponding bit position. Writing a ’0’ has no effect. A hard reset will clear the register.
 * 0= Rx Buffer not updated
 * 1= Rx Buffer updated from new message
 */
#define MCAN_NDAT1_ND1_MASK (0xFFFFFFFFUL)
#define MCAN_NDAT1_ND1_SHIFT (0U)
#define MCAN_NDAT1_ND1_SET(x) (((uint32_t)(x) << MCAN_NDAT1_ND1_SHIFT) & MCAN_NDAT1_ND1_MASK)
#define MCAN_NDAT1_ND1_GET(x) (((uint32_t)(x) & MCAN_NDAT1_ND1_MASK) >> MCAN_NDAT1_ND1_SHIFT)

/* Bitfield definition for register: NDAT2 */
/*
 * ND2 (RW)
 *
 * New Data[63:32]
 * The register holds the New Data flags of Rx Buffers 32 to 63. The flags are set when the respective Rx Buffer has been updated from a received frame.
 * The flags remain set until the Host clears them. A flag is cleared by writing a ’1’ to the corresponding bit position. Writing a ’0’ has no effect. A hard reset will clear the register.
 * 0= Rx Buffer not updated
 * 1= Rx Buffer updated from new message
 */
#define MCAN_NDAT2_ND2_MASK (0xFFFFFFFFUL)
#define MCAN_NDAT2_ND2_SHIFT (0U)
#define MCAN_NDAT2_ND2_SET(x) (((uint32_t)(x) << MCAN_NDAT2_ND2_SHIFT) & MCAN_NDAT2_ND2_MASK)
#define MCAN_NDAT2_ND2_GET(x) (((uint32_t)(x) & MCAN_NDAT2_ND2_MASK) >> MCAN_NDAT2_ND2_SHIFT)

/* Bitfield definition for register: RXF0C */
/*
 * F0OM (RW)
 *
 * FIFO 0 Operation Mode
 * FIFO 0 can be operated in blocking or in overwrite mode (see Section 3.4.2).
 * 0= FIFO 0 blocking mode
 * 1= FIFO 0 overwrite mode
 */
#define MCAN_RXF0C_F0OM_MASK (0x80000000UL)
#define MCAN_RXF0C_F0OM_SHIFT (31U)
#define MCAN_RXF0C_F0OM_SET(x) (((uint32_t)(x) << MCAN_RXF0C_F0OM_SHIFT) & MCAN_RXF0C_F0OM_MASK)
#define MCAN_RXF0C_F0OM_GET(x) (((uint32_t)(x) & MCAN_RXF0C_F0OM_MASK) >> MCAN_RXF0C_F0OM_SHIFT)

/*
 * F0WM (RW)
 *
 * Rx FIFO 0 Watermark
 * 0= Watermark interrupt disabled
 * 1-64= Level for Rx FIFO 0 watermark interrupt (IR.RF0W)
 * >64= Watermark interrupt disabled
 */
#define MCAN_RXF0C_F0WM_MASK (0x7F000000UL)
#define MCAN_RXF0C_F0WM_SHIFT (24U)
#define MCAN_RXF0C_F0WM_SET(x) (((uint32_t)(x) << MCAN_RXF0C_F0WM_SHIFT) & MCAN_RXF0C_F0WM_MASK)
#define MCAN_RXF0C_F0WM_GET(x) (((uint32_t)(x) & MCAN_RXF0C_F0WM_MASK) >> MCAN_RXF0C_F0WM_SHIFT)

/*
 * F0S (RW)
 *
 * Rx FIFO 0 Size
 * 0= No Rx FIFO 0
 * 1-64= Number of Rx FIFO 0 elements
 * >64= Values greater than 64 are interpreted as 64
 * The Rx FIFO 0 elements are indexed from 0 to F0S-1
 */
#define MCAN_RXF0C_F0S_MASK (0x7F0000UL)
#define MCAN_RXF0C_F0S_SHIFT (16U)
#define MCAN_RXF0C_F0S_SET(x) (((uint32_t)(x) << MCAN_RXF0C_F0S_SHIFT) & MCAN_RXF0C_F0S_MASK)
#define MCAN_RXF0C_F0S_GET(x) (((uint32_t)(x) & MCAN_RXF0C_F0S_MASK) >> MCAN_RXF0C_F0S_SHIFT)

/*
 * F0SA (RW)
 *
 * Rx FIFO 0 Start Address
 * Start address of Rx FIFO 0 in Message RAM (32-bit word address)
 */
#define MCAN_RXF0C_F0SA_MASK (0xFFFCU)
#define MCAN_RXF0C_F0SA_SHIFT (2U)
#define MCAN_RXF0C_F0SA_SET(x) (((uint32_t)(x) << MCAN_RXF0C_F0SA_SHIFT) & MCAN_RXF0C_F0SA_MASK)
#define MCAN_RXF0C_F0SA_GET(x) (((uint32_t)(x) & MCAN_RXF0C_F0SA_MASK) >> MCAN_RXF0C_F0SA_SHIFT)

/* Bitfield definition for register: RXF0S */
/*
 * RF0L (R)
 *
 * Rx FIFO 0 Message Lost
 * This bit is a copy of interrupt flag IR.RF0L. When IR.RF0L is reset, this bit is also reset.
 * 0= No Rx FIFO 0 message lost
 * 1= Rx FIFO 0 message lost, also set after write attempt to Rx FIFO 0 of size zero
 * Note: Overwriting the oldest message when RXF0C.F0OM = ‘1’ will not set this flag.
 */
#define MCAN_RXF0S_RF0L_MASK (0x2000000UL)
#define MCAN_RXF0S_RF0L_SHIFT (25U)
#define MCAN_RXF0S_RF0L_GET(x) (((uint32_t)(x) & MCAN_RXF0S_RF0L_MASK) >> MCAN_RXF0S_RF0L_SHIFT)

/*
 * F0F (R)
 *
 * Rx FIFO 0 Full
 * 0= Rx FIFO 0 not full
 * 1= Rx FIFO 0 full
 */
#define MCAN_RXF0S_F0F_MASK (0x1000000UL)
#define MCAN_RXF0S_F0F_SHIFT (24U)
#define MCAN_RXF0S_F0F_GET(x) (((uint32_t)(x) & MCAN_RXF0S_F0F_MASK) >> MCAN_RXF0S_F0F_SHIFT)

/*
 * F0PI (R)
 *
 * Rx FIFO 0 Put Index
 * Rx FIFO 0 write index pointer, range 0 to 63.
 */
#define MCAN_RXF0S_F0PI_MASK (0x3F0000UL)
#define MCAN_RXF0S_F0PI_SHIFT (16U)
#define MCAN_RXF0S_F0PI_GET(x) (((uint32_t)(x) & MCAN_RXF0S_F0PI_MASK) >> MCAN_RXF0S_F0PI_SHIFT)

/*
 * F0GI (R)
 *
 * Rx FIFO 0 Get Index
 * Rx FIFO 0 read index pointer, range 0 to 63.
 */
#define MCAN_RXF0S_F0GI_MASK (0x3F00U)
#define MCAN_RXF0S_F0GI_SHIFT (8U)
#define MCAN_RXF0S_F0GI_GET(x) (((uint32_t)(x) & MCAN_RXF0S_F0GI_MASK) >> MCAN_RXF0S_F0GI_SHIFT)

/*
 * F0FL (R)
 *
 * Rx FIFO 0 Fill Level
 * Number of elements stored in Rx FIFO 0, range 0 to 64.
 */
#define MCAN_RXF0S_F0FL_MASK (0x7FU)
#define MCAN_RXF0S_F0FL_SHIFT (0U)
#define MCAN_RXF0S_F0FL_GET(x) (((uint32_t)(x) & MCAN_RXF0S_F0FL_MASK) >> MCAN_RXF0S_F0FL_SHIFT)

/* Bitfield definition for register: RXF0A */
/*
 * F0AI (RW)
 *
 * Rx FIFO 0 Acknowledge Index
 * After the Host has read a message or a sequence of messages from Rx FIFO 0 it has to write the buffer index of the last element read from Rx FIFO 0 to F0AI.
 * This will set the Rx FIFO 0 Get Index RXF0S.F0GI to F0AI + 1 and update the FIFO 0 Fill Level RXF0S.F0FL.
 */
#define MCAN_RXF0A_F0AI_MASK (0x3FU)
#define MCAN_RXF0A_F0AI_SHIFT (0U)
#define MCAN_RXF0A_F0AI_SET(x) (((uint32_t)(x) << MCAN_RXF0A_F0AI_SHIFT) & MCAN_RXF0A_F0AI_MASK)
#define MCAN_RXF0A_F0AI_GET(x) (((uint32_t)(x) & MCAN_RXF0A_F0AI_MASK) >> MCAN_RXF0A_F0AI_SHIFT)

/* Bitfield definition for register: RXBC */
/*
 * RBSA (RW)
 *
 * Rx Buffer Start Address
 * Configures the start address of the Rx Buffers section in the Message RAM (32-bit word address).Also used to reference debug messages A,B,C.
 */
#define MCAN_RXBC_RBSA_MASK (0xFFFCU)
#define MCAN_RXBC_RBSA_SHIFT (2U)
#define MCAN_RXBC_RBSA_SET(x) (((uint32_t)(x) << MCAN_RXBC_RBSA_SHIFT) & MCAN_RXBC_RBSA_MASK)
#define MCAN_RXBC_RBSA_GET(x) (((uint32_t)(x) & MCAN_RXBC_RBSA_MASK) >> MCAN_RXBC_RBSA_SHIFT)

/* Bitfield definition for register: RXF1C */
/*
 * F1OM (RW)
 *
 * FIFO 1 Operation Mode
 * FIFO 1 can be operated in blocking or in overwrite mode (see Section 3.4.2).
 * 0= FIFO 1 blocking mode
 * 1= FIFO 1 overwrite mode
 */
#define MCAN_RXF1C_F1OM_MASK (0x80000000UL)
#define MCAN_RXF1C_F1OM_SHIFT (31U)
#define MCAN_RXF1C_F1OM_SET(x) (((uint32_t)(x) << MCAN_RXF1C_F1OM_SHIFT) & MCAN_RXF1C_F1OM_MASK)
#define MCAN_RXF1C_F1OM_GET(x) (((uint32_t)(x) & MCAN_RXF1C_F1OM_MASK) >> MCAN_RXF1C_F1OM_SHIFT)

/*
 * F1WM (RW)
 *
 * Rx FIFO 1 Watermark
 * 0= Watermark interrupt disabled
 * 1-64= Level for Rx FIFO 1 watermark interrupt (IR.RF1W)
 * >64= Watermark interrupt disabled
 */
#define MCAN_RXF1C_F1WM_MASK (0x7F000000UL)
#define MCAN_RXF1C_F1WM_SHIFT (24U)
#define MCAN_RXF1C_F1WM_SET(x) (((uint32_t)(x) << MCAN_RXF1C_F1WM_SHIFT) & MCAN_RXF1C_F1WM_MASK)
#define MCAN_RXF1C_F1WM_GET(x) (((uint32_t)(x) & MCAN_RXF1C_F1WM_MASK) >> MCAN_RXF1C_F1WM_SHIFT)

/*
 * F1S (RW)
 *
 * Rx FIFO 1 Size
 * 0= No Rx FIFO 1
 * 1-64= Number of Rx FIFO 1 elements
 * >64= Values greater than 64 are interpreted as 64
 * The Rx FIFO 1 elements are indexed from 0 to F1S - 1
 */
#define MCAN_RXF1C_F1S_MASK (0x7F0000UL)
#define MCAN_RXF1C_F1S_SHIFT (16U)
#define MCAN_RXF1C_F1S_SET(x) (((uint32_t)(x) << MCAN_RXF1C_F1S_SHIFT) & MCAN_RXF1C_F1S_MASK)
#define MCAN_RXF1C_F1S_GET(x) (((uint32_t)(x) & MCAN_RXF1C_F1S_MASK) >> MCAN_RXF1C_F1S_SHIFT)

/*
 * F1SA (RW)
 *
 * Rx FIFO 1 Start Address
 * Start address of Rx FIFO 1 in Message RAM (32-bit word address)
 */
#define MCAN_RXF1C_F1SA_MASK (0xFFFCU)
#define MCAN_RXF1C_F1SA_SHIFT (2U)
#define MCAN_RXF1C_F1SA_SET(x) (((uint32_t)(x) << MCAN_RXF1C_F1SA_SHIFT) & MCAN_RXF1C_F1SA_MASK)
#define MCAN_RXF1C_F1SA_GET(x) (((uint32_t)(x) & MCAN_RXF1C_F1SA_MASK) >> MCAN_RXF1C_F1SA_SHIFT)

/* Bitfield definition for register: RXF1S */
/*
 * DMS (R)
 *
 * Debug Message Status
 * 00= Idle state, wait for reception of debug messages, DMA request is cleared
 * 01= Debug message A received
 * 10= Debug messages A, B received
 * 11= Debug messages A, B, C received, DMA request is set
 */
#define MCAN_RXF1S_DMS_MASK (0xC0000000UL)
#define MCAN_RXF1S_DMS_SHIFT (30U)
#define MCAN_RXF1S_DMS_GET(x) (((uint32_t)(x) & MCAN_RXF1S_DMS_MASK) >> MCAN_RXF1S_DMS_SHIFT)

/*
 * RF1L (R)
 *
 * Rx FIFO 1 Message Lost
 * This bit is a copy of interrupt flag IR.RF1L. When IR.RF1L is reset, this bit is also reset.
 * 0= No Rx FIFO 1 message lost
 * 1= Rx FIFO 1 message lost, also set after write attempt to Rx FIFO 1 of size zero
 * Note: Overwriting the oldest message when RXF1C.F1OM = ‘1’ will not set this flag.
 */
#define MCAN_RXF1S_RF1L_MASK (0x2000000UL)
#define MCAN_RXF1S_RF1L_SHIFT (25U)
#define MCAN_RXF1S_RF1L_GET(x) (((uint32_t)(x) & MCAN_RXF1S_RF1L_MASK) >> MCAN_RXF1S_RF1L_SHIFT)

/*
 * F1F (R)
 *
 * Rx FIFO 1 Full
 * 0= Rx FIFO 1 not full
 * 1= Rx FIFO 1 full
 */
#define MCAN_RXF1S_F1F_MASK (0x1000000UL)
#define MCAN_RXF1S_F1F_SHIFT (24U)
#define MCAN_RXF1S_F1F_GET(x) (((uint32_t)(x) & MCAN_RXF1S_F1F_MASK) >> MCAN_RXF1S_F1F_SHIFT)

/*
 * F1PI (R)
 *
 * Rx FIFO 1 Put Index
 * Rx FIFO 1 write index pointer, range 0 to 63.
 */
#define MCAN_RXF1S_F1PI_MASK (0x3F0000UL)
#define MCAN_RXF1S_F1PI_SHIFT (16U)
#define MCAN_RXF1S_F1PI_GET(x) (((uint32_t)(x) & MCAN_RXF1S_F1PI_MASK) >> MCAN_RXF1S_F1PI_SHIFT)

/*
 * F1GI (R)
 *
 * Rx FIFO 1 Get Index
 * Rx FIFO 1 read index pointer, range 0 to 63.
 */
#define MCAN_RXF1S_F1GI_MASK (0x3F00U)
#define MCAN_RXF1S_F1GI_SHIFT (8U)
#define MCAN_RXF1S_F1GI_GET(x) (((uint32_t)(x) & MCAN_RXF1S_F1GI_MASK) >> MCAN_RXF1S_F1GI_SHIFT)

/*
 * F1FL (R)
 *
 * Rx FIFO 1 Fill Level
 * Number of elements stored in Rx FIFO 1, range 0 to 64.
 */
#define MCAN_RXF1S_F1FL_MASK (0x7FU)
#define MCAN_RXF1S_F1FL_SHIFT (0U)
#define MCAN_RXF1S_F1FL_GET(x) (((uint32_t)(x) & MCAN_RXF1S_F1FL_MASK) >> MCAN_RXF1S_F1FL_SHIFT)

/* Bitfield definition for register: RXF1A */
/*
 * F1AI (RW)
 *
 * Rx FIFO 1 Acknowledge Index
 * After the Host has read a message or a sequence of messages from Rx FIFO 1 it has to write the buffer index of the last element read from Rx FIFO 1 to F1AI.
 * This will set the Rx FIFO 1 Get Index RXF1S.F1GI to F1AI + 1 and update the FIFO 1 Fill Level RXF1S.F1FL.
 */
#define MCAN_RXF1A_F1AI_MASK (0x3FU)
#define MCAN_RXF1A_F1AI_SHIFT (0U)
#define MCAN_RXF1A_F1AI_SET(x) (((uint32_t)(x) << MCAN_RXF1A_F1AI_SHIFT) & MCAN_RXF1A_F1AI_MASK)
#define MCAN_RXF1A_F1AI_GET(x) (((uint32_t)(x) & MCAN_RXF1A_F1AI_MASK) >> MCAN_RXF1A_F1AI_SHIFT)

/* Bitfield definition for register: RXESC */
/*
 * RBDS (RW)
 *
 * Rx Buffer Data Field Size
 * 000= 8 byte data field
 * 001= 12 byte data field
 * 010= 16 byte data field
 * 011= 20 byte data field
 * 100= 24 byte data field
 * 101= 32 byte data field
 * 110= 48 byte data field
 * 111= 64 byte data field
 */
#define MCAN_RXESC_RBDS_MASK (0x700U)
#define MCAN_RXESC_RBDS_SHIFT (8U)
#define MCAN_RXESC_RBDS_SET(x) (((uint32_t)(x) << MCAN_RXESC_RBDS_SHIFT) & MCAN_RXESC_RBDS_MASK)
#define MCAN_RXESC_RBDS_GET(x) (((uint32_t)(x) & MCAN_RXESC_RBDS_MASK) >> MCAN_RXESC_RBDS_SHIFT)

/*
 * F1DS (RW)
 *
 * Rx FIFO 1 Data Field Size
 * 000= 8 byte data field
 * 001= 12 byte data field
 * 010= 16 byte data field
 * 011= 20 byte data field
 * 100= 24 byte data field
 * 101= 32 byte data field
 * 110= 48 byte data field
 * 111= 64 byte data field
 */
#define MCAN_RXESC_F1DS_MASK (0x70U)
#define MCAN_RXESC_F1DS_SHIFT (4U)
#define MCAN_RXESC_F1DS_SET(x) (((uint32_t)(x) << MCAN_RXESC_F1DS_SHIFT) & MCAN_RXESC_F1DS_MASK)
#define MCAN_RXESC_F1DS_GET(x) (((uint32_t)(x) & MCAN_RXESC_F1DS_MASK) >> MCAN_RXESC_F1DS_SHIFT)

/*
 * F0DS (RW)
 *
 * Rx FIFO 0 Data Field Size
 * 000= 8 byte data field
 * 001= 12 byte data field
 * 010= 16 byte data field
 * 011= 20 byte data field
 * 100= 24 byte data field
 * 101= 32 byte data field
 * 110= 48 byte data field
 * 111= 64 byte data field
 * Note: In case the data field size of an accepted CAN frame exceeds the data field size configured for the matching Rx Buffer or Rx FIFO,
 * only the number of bytes as configured by RXESC are stored to the Rx Buffer resp. Rx FIFO element. The rest of the frame’s data field is ignored.
 */
#define MCAN_RXESC_F0DS_MASK (0x7U)
#define MCAN_RXESC_F0DS_SHIFT (0U)
#define MCAN_RXESC_F0DS_SET(x) (((uint32_t)(x) << MCAN_RXESC_F0DS_SHIFT) & MCAN_RXESC_F0DS_MASK)
#define MCAN_RXESC_F0DS_GET(x) (((uint32_t)(x) & MCAN_RXESC_F0DS_MASK) >> MCAN_RXESC_F0DS_SHIFT)

/* Bitfield definition for register: TXBC */
/*
 * TFQM (RW)
 *
 * Tx FIFO/Queue Mode
 * 0= Tx FIFO operation
 * 1= Tx Queue operation
 */
#define MCAN_TXBC_TFQM_MASK (0x40000000UL)
#define MCAN_TXBC_TFQM_SHIFT (30U)
#define MCAN_TXBC_TFQM_SET(x) (((uint32_t)(x) << MCAN_TXBC_TFQM_SHIFT) & MCAN_TXBC_TFQM_MASK)
#define MCAN_TXBC_TFQM_GET(x) (((uint32_t)(x) & MCAN_TXBC_TFQM_MASK) >> MCAN_TXBC_TFQM_SHIFT)

/*
 * TFQS (RW)
 *
 * Transmit FIFO/Queue Size
 * 0= No Tx FIFO/Queue
 * 1-32= Number of Tx Buffers used for Tx FIFO/Queue
 * >32= Values greater than 32 are interpreted as 32
 */
#define MCAN_TXBC_TFQS_MASK (0x3F000000UL)
#define MCAN_TXBC_TFQS_SHIFT (24U)
#define MCAN_TXBC_TFQS_SET(x) (((uint32_t)(x) << MCAN_TXBC_TFQS_SHIFT) & MCAN_TXBC_TFQS_MASK)
#define MCAN_TXBC_TFQS_GET(x) (((uint32_t)(x) & MCAN_TXBC_TFQS_MASK) >> MCAN_TXBC_TFQS_SHIFT)

/*
 * NDTB (RW)
 *
 * Number of Dedicated Transmit Buffers
 * 0= No Dedicated Tx Buffers
 * 1-32= Number of Dedicated Tx Buffers
 * >32= Values greater than 32 are interpreted as 32
 */
#define MCAN_TXBC_NDTB_MASK (0x3F0000UL)
#define MCAN_TXBC_NDTB_SHIFT (16U)
#define MCAN_TXBC_NDTB_SET(x) (((uint32_t)(x) << MCAN_TXBC_NDTB_SHIFT) & MCAN_TXBC_NDTB_MASK)
#define MCAN_TXBC_NDTB_GET(x) (((uint32_t)(x) & MCAN_TXBC_NDTB_MASK) >> MCAN_TXBC_NDTB_SHIFT)

/*
 * TBSA (RW)
 *
 * Tx Buffers Start Address
 * Start address of Tx Buffers section in Message RAM (32-bit word address, see Figure 2).
 * Note: Be aware that the sum of TFQS and NDTB may be not greater than 32. There is no check for erroneous configurations. The Tx Buffers section in the Message RAM starts with the dedicated Tx Buffers.
 */
#define MCAN_TXBC_TBSA_MASK (0xFFFCU)
#define MCAN_TXBC_TBSA_SHIFT (2U)
#define MCAN_TXBC_TBSA_SET(x) (((uint32_t)(x) << MCAN_TXBC_TBSA_SHIFT) & MCAN_TXBC_TBSA_MASK)
#define MCAN_TXBC_TBSA_GET(x) (((uint32_t)(x) & MCAN_TXBC_TBSA_MASK) >> MCAN_TXBC_TBSA_SHIFT)

/* Bitfield definition for register: TXFQS */
/*
 * TFQF (R)
 *
 * Tx FIFO/Queue Full
 * 0= Tx FIFO/Queue not full
 * 1= Tx FIFO/Queue full
 */
#define MCAN_TXFQS_TFQF_MASK (0x200000UL)
#define MCAN_TXFQS_TFQF_SHIFT (21U)
#define MCAN_TXFQS_TFQF_GET(x) (((uint32_t)(x) & MCAN_TXFQS_TFQF_MASK) >> MCAN_TXFQS_TFQF_SHIFT)

/*
 * TFQPI (R)
 *
 * Tx FIFO/Queue Put Index
 * Tx FIFO/Queue write index pointer, range 0 to 31.
 */
#define MCAN_TXFQS_TFQPI_MASK (0x1F0000UL)
#define MCAN_TXFQS_TFQPI_SHIFT (16U)
#define MCAN_TXFQS_TFQPI_GET(x) (((uint32_t)(x) & MCAN_TXFQS_TFQPI_MASK) >> MCAN_TXFQS_TFQPI_SHIFT)

/*
 * TFGI (R)
 *
 * Tx FIFO Get Index
 * Tx FIFO read index pointer, range 0 to 31. Read as zero when Tx Queue operation is configured
 * (TXBC.TFQM = ‘1’).
 */
#define MCAN_TXFQS_TFGI_MASK (0x1F00U)
#define MCAN_TXFQS_TFGI_SHIFT (8U)
#define MCAN_TXFQS_TFGI_GET(x) (((uint32_t)(x) & MCAN_TXFQS_TFGI_MASK) >> MCAN_TXFQS_TFGI_SHIFT)

/*
 * TFFL (R)
 *
 * Tx FIFO Free Level
 * Number of consecutive free Tx FIFO elements starting from TFGI, range 0 to 32. Read as zero when Tx Queue operation is configured (TXBC.TFQM = ‘1’)
 * Note: In case of mixed configurations where dedicated Tx Buffers are combined with a Tx FIFO or a Tx Queue, the Put and Get Indices indicate the number of the Tx Buffer starting with
 * the first dedicated Tx Buffers.
 * Example: For a configuration of 12 dedicated Tx Buffers and a Tx FIFO of 20 Buffers a Put Index of 15 points to the fourth buffer of the Tx FIFO.
 */
#define MCAN_TXFQS_TFFL_MASK (0x3FU)
#define MCAN_TXFQS_TFFL_SHIFT (0U)
#define MCAN_TXFQS_TFFL_GET(x) (((uint32_t)(x) & MCAN_TXFQS_TFFL_MASK) >> MCAN_TXFQS_TFFL_SHIFT)

/* Bitfield definition for register: TXESC */
/*
 * TBDS (RW)
 *
 * Tx Buffer Data Field Size
 * 000= 8 byte data field
 * 001= 12 byte data field
 * 010= 16 byte data field
 * 011= 20 byte data field
 * 100= 24 byte data field
 * 101= 32 byte data field
 * 110= 48 byte data field
 * 111= 64 byte data field
 * Note: In case the data length code DLC of a Tx Buffer element is configured to a value higher than the Tx Buffer data field size TXESC.TBDS, the bytes not defined by the Tx Buffer are transmitted as “0xCC” (padding bytes).
 */
#define MCAN_TXESC_TBDS_MASK (0x7U)
#define MCAN_TXESC_TBDS_SHIFT (0U)
#define MCAN_TXESC_TBDS_SET(x) (((uint32_t)(x) << MCAN_TXESC_TBDS_SHIFT) & MCAN_TXESC_TBDS_MASK)
#define MCAN_TXESC_TBDS_GET(x) (((uint32_t)(x) & MCAN_TXESC_TBDS_MASK) >> MCAN_TXESC_TBDS_SHIFT)

/* Bitfield definition for register: TXBRP */
/*
 * TRP (R)
 *
 * Transmission Request Pending
 * Each Tx Buffer has its own Transmission Request Pending bit. The bits are set via register TXBAR.The bits are reset after a requested transmission has completed or has been cancelled via register
 * TXBCR.
 * TXBRP bits are set only for those Tx Buffers configured via TXBC. After a TXBRP bit has been set, a Tx scan (see Section 3.5, Tx Handling) is started to check for the pending Tx request with the
 * highest priority (Tx Buffer with lowest Message ID).
 * A cancellation request resets the corresponding transmission request pending bit of register TXBRP. In case a transmission has already been started when a cancellation is requested,
 * this is done at the end of the transmission, regardless whether the transmission was successful or not. The cancellation request bits are reset directly after the corresponding TXBRP bit has been reset.
 * After a cancellation has been requested, a finished cancellation is signalled via TXBCF
 * ? after successful transmission together with the corresponding TXBTO bit
 * ? when the transmission has not yet been started at the point of cancellation
 * ? when the transmission has been aborted due to lost arbitration
 * ? when an error occurred during frame transmission
 * In DAR mode all transmissions are automatically cancelled if they are not successful. The corresponding TXBCF bit is set for all unsuccessful transmissions.
 * 0= No transmission request pending
 * 1= Transmission request pending
 * Note: TXBRP bits which are set while a Tx scan is in progress are not considered during this particular Tx scan. In case a cancellation is requested for such a Tx Buffer, this Add Request is cancelled immediately, the corresponding TXBRP bit is reset.
 */
#define MCAN_TXBRP_TRP_MASK (0xFFFFFFFFUL)
#define MCAN_TXBRP_TRP_SHIFT (0U)
#define MCAN_TXBRP_TRP_GET(x) (((uint32_t)(x) & MCAN_TXBRP_TRP_MASK) >> MCAN_TXBRP_TRP_SHIFT)

/* Bitfield definition for register: TXBAR */
/*
 * AR (RW)
 *
 * Add Request
 * Each Tx Buffer has its own Add Request bit. Writing a ‘1’ will set the corresponding Add Request bit; writing a ‘0’ has no impact. This enables the Host to set transmission requests for multiple Tx
 * Buffers with one write to TXBAR. TXBAR bits are set only for those Tx Buffers configured via TXBC.
 * When no Tx scan is running, the bits are reset immediately, else the bits remain set until the Tx scan process has completed.
 * 0= No transmission request added
 * 1= Transmission requested added
 * Note: If an add request is applied for a Tx Buffer with pending transmission request (corresponding TXBRP bit already set), this add request is ignored.
 */
#define MCAN_TXBAR_AR_MASK (0xFFFFFFFFUL)
#define MCAN_TXBAR_AR_SHIFT (0U)
#define MCAN_TXBAR_AR_SET(x) (((uint32_t)(x) << MCAN_TXBAR_AR_SHIFT) & MCAN_TXBAR_AR_MASK)
#define MCAN_TXBAR_AR_GET(x) (((uint32_t)(x) & MCAN_TXBAR_AR_MASK) >> MCAN_TXBAR_AR_SHIFT)

/* Bitfield definition for register: TXBCR */
/*
 * CR (RW)
 *
 * Cancellation Request
 * Each Tx Buffer has its own Cancellation Request bit. Writing a ‘1’ will set the corresponding Cancellation Request bit; writing a ‘0’ has no impact.
 * This enables the Host to set cancellation requests for multiple Tx Buffers with one write to TXBCR. TXBCR bits are set only for those Tx Buffers configured via TXBC. The bits remain set until the corresponding bit of TXBRP is reset.
 * 0= No cancellation pending
 * 1= Cancellation pending
 */
#define MCAN_TXBCR_CR_MASK (0xFFFFFFFFUL)
#define MCAN_TXBCR_CR_SHIFT (0U)
#define MCAN_TXBCR_CR_SET(x) (((uint32_t)(x) << MCAN_TXBCR_CR_SHIFT) & MCAN_TXBCR_CR_MASK)
#define MCAN_TXBCR_CR_GET(x) (((uint32_t)(x) & MCAN_TXBCR_CR_MASK) >> MCAN_TXBCR_CR_SHIFT)

/* Bitfield definition for register: TXBTO */
/*
 * TO (R)
 *
 * Transmission Occurred
 * Each Tx Buffer has its own Transmission Occurred bit. The bits are set when the corresponding TXBRP bit is cleared after a successful transmission. The bits are reset when a new transmission is requested by writing a ‘1’ to the corresponding bit of register TXBAR.
 * 0= No transmission occurred
 * 1= Transmission occurred
 */
#define MCAN_TXBTO_TO_MASK (0xFFFFFFFFUL)
#define MCAN_TXBTO_TO_SHIFT (0U)
#define MCAN_TXBTO_TO_GET(x) (((uint32_t)(x) & MCAN_TXBTO_TO_MASK) >> MCAN_TXBTO_TO_SHIFT)

/* Bitfield definition for register: TXBCF */
/*
 * CF (R)
 *
 * Cancellation Finished
 * Each Tx Buffer has its own Cancellation Finished bit. The bits are set when the corresponding TXBRP bit is cleared after a cancellation was requested via TXBCR.
 * In case the corresponding TXBRP bit was not set at the point of cancellation, CF is set immediately. The bits are reset when a new transmission is requested by writing a ‘1’ to the corresponding bit of register TXBAR.
 * 0= No transmit buffer cancellation
 * 1= Transmit buffer cancellation finished
 */
#define MCAN_TXBCF_CF_MASK (0xFFFFFFFFUL)
#define MCAN_TXBCF_CF_SHIFT (0U)
#define MCAN_TXBCF_CF_GET(x) (((uint32_t)(x) & MCAN_TXBCF_CF_MASK) >> MCAN_TXBCF_CF_SHIFT)

/* Bitfield definition for register: TXBTIE */
/*
 * TIE (RW)
 *
 * Transmission Interrupt Enable
 * Each Tx Buffer has its own Transmission Interrupt Enable bit.
 * 0= Transmission interrupt disabled
 * 1= Transmission interrupt enable
 */
#define MCAN_TXBTIE_TIE_MASK (0xFFFFFFFFUL)
#define MCAN_TXBTIE_TIE_SHIFT (0U)
#define MCAN_TXBTIE_TIE_SET(x) (((uint32_t)(x) << MCAN_TXBTIE_TIE_SHIFT) & MCAN_TXBTIE_TIE_MASK)
#define MCAN_TXBTIE_TIE_GET(x) (((uint32_t)(x) & MCAN_TXBTIE_TIE_MASK) >> MCAN_TXBTIE_TIE_SHIFT)

/* Bitfield definition for register: TXBCIE */
/*
 * CFIE (RW)
 *
 * Cancellation Finished Interrupt Enable
 * Each Tx Buffer has its own Cancellation Finished Interrupt Enable bit.
 * 0= Cancellation finished interrupt disabled
 * 1= Cancellation finished interrupt enabled
 */
#define MCAN_TXBCIE_CFIE_MASK (0xFFFFFFFFUL)
#define MCAN_TXBCIE_CFIE_SHIFT (0U)
#define MCAN_TXBCIE_CFIE_SET(x) (((uint32_t)(x) << MCAN_TXBCIE_CFIE_SHIFT) & MCAN_TXBCIE_CFIE_MASK)
#define MCAN_TXBCIE_CFIE_GET(x) (((uint32_t)(x) & MCAN_TXBCIE_CFIE_MASK) >> MCAN_TXBCIE_CFIE_SHIFT)

/* Bitfield definition for register: TXEFC */
/*
 * EFWM (RW)
 *
 * Event FIFO Watermark
 * 0= Watermark interrupt disabled
 * 1-32= Level for Tx Event FIFO watermark interrupt (IR.TEFW)
 * >32= Watermark interrupt disabled
 */
#define MCAN_TXEFC_EFWM_MASK (0x3F000000UL)
#define MCAN_TXEFC_EFWM_SHIFT (24U)
#define MCAN_TXEFC_EFWM_SET(x) (((uint32_t)(x) << MCAN_TXEFC_EFWM_SHIFT) & MCAN_TXEFC_EFWM_MASK)
#define MCAN_TXEFC_EFWM_GET(x) (((uint32_t)(x) & MCAN_TXEFC_EFWM_MASK) >> MCAN_TXEFC_EFWM_SHIFT)

/*
 * EFS (RW)
 *
 * Event FIFO Size
 * 0= Tx Event FIFO disabled
 * 1-32= Number of Tx Event FIFO elements
 * >32= Values greater than 32 are interpreted as 32
 * The Tx Event FIFO elements are indexed from 0 to EFS - 1
 */
#define MCAN_TXEFC_EFS_MASK (0x3F0000UL)
#define MCAN_TXEFC_EFS_SHIFT (16U)
#define MCAN_TXEFC_EFS_SET(x) (((uint32_t)(x) << MCAN_TXEFC_EFS_SHIFT) & MCAN_TXEFC_EFS_MASK)
#define MCAN_TXEFC_EFS_GET(x) (((uint32_t)(x) & MCAN_TXEFC_EFS_MASK) >> MCAN_TXEFC_EFS_SHIFT)

/*
 * EFSA (RW)
 *
 * Event FIFO Start Address
 * Start address of Tx Event FIFO in Message RAM (32-bit word address)
 */
#define MCAN_TXEFC_EFSA_MASK (0xFFFCU)
#define MCAN_TXEFC_EFSA_SHIFT (2U)
#define MCAN_TXEFC_EFSA_SET(x) (((uint32_t)(x) << MCAN_TXEFC_EFSA_SHIFT) & MCAN_TXEFC_EFSA_MASK)
#define MCAN_TXEFC_EFSA_GET(x) (((uint32_t)(x) & MCAN_TXEFC_EFSA_MASK) >> MCAN_TXEFC_EFSA_SHIFT)

/* Bitfield definition for register: TXEFS */
/*
 * TEFL (R)
 *
 * Tx Event FIFO Element Lost
 * This bit is a copy of interrupt flag IR.TEFL. When IR.TEFL is reset, this bit is also reset.
 * 0= No Tx Event FIFO element lost
 * 1= Tx Event FIFO element lost, also set after write attempt to Tx Event FIFO of size zero.
 */
#define MCAN_TXEFS_TEFL_MASK (0x2000000UL)
#define MCAN_TXEFS_TEFL_SHIFT (25U)
#define MCAN_TXEFS_TEFL_GET(x) (((uint32_t)(x) & MCAN_TXEFS_TEFL_MASK) >> MCAN_TXEFS_TEFL_SHIFT)

/*
 * EFF (R)
 *
 * Event FIFO Full
 * 0= Tx Event FIFO not full
 * 1= Tx Event FIFO full
 */
#define MCAN_TXEFS_EFF_MASK (0x1000000UL)
#define MCAN_TXEFS_EFF_SHIFT (24U)
#define MCAN_TXEFS_EFF_GET(x) (((uint32_t)(x) & MCAN_TXEFS_EFF_MASK) >> MCAN_TXEFS_EFF_SHIFT)

/*
 * EFPI (R)
 *
 * Event FIFO Put Index
 * Tx Event FIFO write index pointer, range 0 to 31.
 */
#define MCAN_TXEFS_EFPI_MASK (0x1F0000UL)
#define MCAN_TXEFS_EFPI_SHIFT (16U)
#define MCAN_TXEFS_EFPI_GET(x) (((uint32_t)(x) & MCAN_TXEFS_EFPI_MASK) >> MCAN_TXEFS_EFPI_SHIFT)

/*
 * EFGI (R)
 *
 * Event FIFO Get Index
 * Tx Event FIFO read index pointer, range 0 to 31.
 */
#define MCAN_TXEFS_EFGI_MASK (0x1F00U)
#define MCAN_TXEFS_EFGI_SHIFT (8U)
#define MCAN_TXEFS_EFGI_GET(x) (((uint32_t)(x) & MCAN_TXEFS_EFGI_MASK) >> MCAN_TXEFS_EFGI_SHIFT)

/*
 * EFFL (R)
 *
 * Event FIFO Fill Level
 * Number of elements stored in Tx Event FIFO, range 0 to 32.
 */
#define MCAN_TXEFS_EFFL_MASK (0x3FU)
#define MCAN_TXEFS_EFFL_SHIFT (0U)
#define MCAN_TXEFS_EFFL_GET(x) (((uint32_t)(x) & MCAN_TXEFS_EFFL_MASK) >> MCAN_TXEFS_EFFL_SHIFT)

/* Bitfield definition for register: TXEFA */
/*
 * EFAI (RW)
 *
 * Event FIFO Acknowledge Index
 * After the Host has read an element or a sequence of elements from the Tx Event FIFO it has to write the index of the last element read from Tx Event FIFO to EFAI. This will set the Tx Event FIFO Get
 * Index TXEFS.EFGI to EFAI + 1 and update the Event FIFO Fill Level TXEFS.EFFL.
 */
#define MCAN_TXEFA_EFAI_MASK (0x1FU)
#define MCAN_TXEFA_EFAI_SHIFT (0U)
#define MCAN_TXEFA_EFAI_SET(x) (((uint32_t)(x) << MCAN_TXEFA_EFAI_SHIFT) & MCAN_TXEFA_EFAI_MASK)
#define MCAN_TXEFA_EFAI_GET(x) (((uint32_t)(x) & MCAN_TXEFA_EFAI_MASK) >> MCAN_TXEFA_EFAI_SHIFT)

/* Bitfield definition for register array: TS_SEL */
/*
 * TS (R)
 *
 * Timestamp Word TS
 * default can save 16 timestamps with 32bit;
 * if ts64_en is set, then work at 64bit mode, can save 8 timestamps with 01/23/45….
 */
#define MCAN_TS_SEL_TS_MASK (0xFFFFFFFFUL)
#define MCAN_TS_SEL_TS_SHIFT (0U)
#define MCAN_TS_SEL_TS_GET(x) (((uint32_t)(x) & MCAN_TS_SEL_TS_MASK) >> MCAN_TS_SEL_TS_SHIFT)

/* Bitfield definition for register: CREL */
/*
 * REL (R)
 *
 * Core Release
 * One digit, BCD-coded
 */
#define MCAN_CREL_REL_MASK (0xF0000000UL)
#define MCAN_CREL_REL_SHIFT (28U)
#define MCAN_CREL_REL_GET(x) (((uint32_t)(x) & MCAN_CREL_REL_MASK) >> MCAN_CREL_REL_SHIFT)

/*
 * STEP (R)
 *
 * Step of Core Release
 * One digit, BCD-coded.
 */
#define MCAN_CREL_STEP_MASK (0xF000000UL)
#define MCAN_CREL_STEP_SHIFT (24U)
#define MCAN_CREL_STEP_GET(x) (((uint32_t)(x) & MCAN_CREL_STEP_MASK) >> MCAN_CREL_STEP_SHIFT)

/*
 * SUBSTEP (R)
 *
 * Sub-step of Core Release
 * One digit, BCD-coded
 */
#define MCAN_CREL_SUBSTEP_MASK (0xF00000UL)
#define MCAN_CREL_SUBSTEP_SHIFT (20U)
#define MCAN_CREL_SUBSTEP_GET(x) (((uint32_t)(x) & MCAN_CREL_SUBSTEP_MASK) >> MCAN_CREL_SUBSTEP_SHIFT)

/*
 * YEAR (R)
 *
 * Timestamp Year
 * One digit, BCD-coded. This field is set by generic parameter on
 * synthesis.
 */
#define MCAN_CREL_YEAR_MASK (0xF0000UL)
#define MCAN_CREL_YEAR_SHIFT (16U)
#define MCAN_CREL_YEAR_GET(x) (((uint32_t)(x) & MCAN_CREL_YEAR_MASK) >> MCAN_CREL_YEAR_SHIFT)

/*
 * MON (R)
 *
 * Timestamp Month
 * Two digits, BCD-coded. This field is set by generic parameter
 * on synthesis.
 */
#define MCAN_CREL_MON_MASK (0xFF00U)
#define MCAN_CREL_MON_SHIFT (8U)
#define MCAN_CREL_MON_GET(x) (((uint32_t)(x) & MCAN_CREL_MON_MASK) >> MCAN_CREL_MON_SHIFT)

/*
 * DAY (R)
 *
 * Timestamp Day
 * Two digits, BCD-coded. This field is set by generic parameter
 * on synthesis.
 */
#define MCAN_CREL_DAY_MASK (0xFFU)
#define MCAN_CREL_DAY_SHIFT (0U)
#define MCAN_CREL_DAY_GET(x) (((uint32_t)(x) & MCAN_CREL_DAY_MASK) >> MCAN_CREL_DAY_SHIFT)

/* Bitfield definition for register: TSCFG */
/*
 * TBPRE (RW)
 *
 * Timebase Prescaler
 * 0x00 to 0xFF
 * The value by which the oscillator frequency is divided for
 * generating the timebase counter clock. Valid values for the
 * Timebase Prescaler are 0 to 255. The actual interpretation by
 * the hardware of this value is such that one more than the value
 * programmed here is used. Affects only the TSU internal
 * timebase. When the internal timebase is excluded by synthesis,
 * TBPRE[7:0] is fixed to 0x00, the Timestamp Prescaler is not
 * used.
 */
#define MCAN_TSCFG_TBPRE_MASK (0xFF00U)
#define MCAN_TSCFG_TBPRE_SHIFT (8U)
#define MCAN_TSCFG_TBPRE_SET(x) (((uint32_t)(x) << MCAN_TSCFG_TBPRE_SHIFT) & MCAN_TSCFG_TBPRE_MASK)
#define MCAN_TSCFG_TBPRE_GET(x) (((uint32_t)(x) & MCAN_TSCFG_TBPRE_MASK) >> MCAN_TSCFG_TBPRE_SHIFT)

/*
 * EN64 (RW)
 *
 * set to use 64bit timestamp.
 * when enabled, tsu can save up to 8 different timestamps, TS(k) and TS(k+1) are used for one 64bit timestamp, k is 0~7.
 * TSP can be used to select different one
 */
#define MCAN_TSCFG_EN64_MASK (0x8U)
#define MCAN_TSCFG_EN64_SHIFT (3U)
#define MCAN_TSCFG_EN64_SET(x) (((uint32_t)(x) << MCAN_TSCFG_EN64_SHIFT) & MCAN_TSCFG_EN64_MASK)
#define MCAN_TSCFG_EN64_GET(x) (((uint32_t)(x) & MCAN_TSCFG_EN64_MASK) >> MCAN_TSCFG_EN64_SHIFT)

/*
 * SCP (RW)
 *
 * Select Capturing Position
 * 0: Capture Timestamp at EOF
 * 1: Capture Timestamp at SOF
 */
#define MCAN_TSCFG_SCP_MASK (0x4U)
#define MCAN_TSCFG_SCP_SHIFT (2U)
#define MCAN_TSCFG_SCP_SET(x) (((uint32_t)(x) << MCAN_TSCFG_SCP_SHIFT) & MCAN_TSCFG_SCP_MASK)
#define MCAN_TSCFG_SCP_GET(x) (((uint32_t)(x) & MCAN_TSCFG_SCP_MASK) >> MCAN_TSCFG_SCP_SHIFT)

/*
 * TBCS (RW)
 *
 * Timebase Counter Select
 * When the internal timebase is excluded by synthesis, TBCS is
 * fixed to ‘1’.
 * 0: Timestamp value captured from internal timebase counter,
 *  ATB.TB[31:0] is the internal timbase counter
 * 1: Timestamp value captured from input tsu_tbin[31:0],ATB.TB[31:0] is tsu_tbin[31:0]
 */
#define MCAN_TSCFG_TBCS_MASK (0x2U)
#define MCAN_TSCFG_TBCS_SHIFT (1U)
#define MCAN_TSCFG_TBCS_SET(x) (((uint32_t)(x) << MCAN_TSCFG_TBCS_SHIFT) & MCAN_TSCFG_TBCS_MASK)
#define MCAN_TSCFG_TBCS_GET(x) (((uint32_t)(x) & MCAN_TSCFG_TBCS_MASK) >> MCAN_TSCFG_TBCS_SHIFT)

/*
 * TSUE (RW)
 *
 * Timestamp Unit Enable
 * 0: TSU disabled
 * 1: TSU enabled
 */
#define MCAN_TSCFG_TSUE_MASK (0x1U)
#define MCAN_TSCFG_TSUE_SHIFT (0U)
#define MCAN_TSCFG_TSUE_SET(x) (((uint32_t)(x) << MCAN_TSCFG_TSUE_SHIFT) & MCAN_TSCFG_TSUE_MASK)
#define MCAN_TSCFG_TSUE_GET(x) (((uint32_t)(x) & MCAN_TSCFG_TSUE_MASK) >> MCAN_TSCFG_TSUE_SHIFT)

/* Bitfield definition for register: TSS1 */
/*
 * TSL (R)
 *
 * Timestamp Lost
 * Each Timestamp register (TS0-TS15) is assigned one bit. The bits are set when the timestamp stored in the related Timestamp register was overwritten before it was read.
 * Reading a Timestamp register resets the related bit.
 */
#define MCAN_TSS1_TSL_MASK (0xFFFF0000UL)
#define MCAN_TSS1_TSL_SHIFT (16U)
#define MCAN_TSS1_TSL_GET(x) (((uint32_t)(x) & MCAN_TSS1_TSL_MASK) >> MCAN_TSS1_TSL_SHIFT)

/*
 * TSN (R)
 *
 * Timestamp New
 * Each Timestamp register (TS0-TS15) is assigned one bit. The bits are set when a timestamp was stored in the related
 * Timestamp register. Reading a Timestamp register resets the related bit.
 */
#define MCAN_TSS1_TSN_MASK (0xFFFFU)
#define MCAN_TSS1_TSN_SHIFT (0U)
#define MCAN_TSS1_TSN_GET(x) (((uint32_t)(x) & MCAN_TSS1_TSN_MASK) >> MCAN_TSS1_TSN_SHIFT)

/* Bitfield definition for register: TSS2 */
/*
 * TSP (R)
 *
 * Timestamp Pointer
 * The Timestamp Pointer is incremented by one each time a timestamp is captured. From its maximum value (3, 7, or 15
 * depending on number_ts_g), it is incremented to 0.
 * Value also signalled on output m_can_tsp[3:0].
 */
#define MCAN_TSS2_TSP_MASK (0xFU)
#define MCAN_TSS2_TSP_SHIFT (0U)
#define MCAN_TSS2_TSP_GET(x) (((uint32_t)(x) & MCAN_TSS2_TSP_MASK) >> MCAN_TSS2_TSP_SHIFT)

/* Bitfield definition for register: ATB */
/*
 * TB (RC)
 *
 * timebase for timestamp generation 31-0
 */
#define MCAN_ATB_TB_MASK (0xFFFFFFFFUL)
#define MCAN_ATB_TB_SHIFT (0U)
#define MCAN_ATB_TB_GET(x) (((uint32_t)(x) & MCAN_ATB_TB_MASK) >> MCAN_ATB_TB_SHIFT)

/* Bitfield definition for register: ATBH */
/*
 * TBH (RC)
 *
 * timebase for timestamp generation 63-32
 */
#define MCAN_ATBH_TBH_MASK (0xFFFFFFFFUL)
#define MCAN_ATBH_TBH_SHIFT (0U)
#define MCAN_ATBH_TBH_GET(x) (((uint32_t)(x) & MCAN_ATBH_TBH_MASK) >> MCAN_ATBH_TBH_SHIFT)

/* Bitfield definition for register: GLB_CTL */
/*
 * M_CAN_STBY (RW)
 *
 * m_can standby control
 */
#define MCAN_GLB_CTL_M_CAN_STBY_MASK (0x80000000UL)
#define MCAN_GLB_CTL_M_CAN_STBY_SHIFT (31U)
#define MCAN_GLB_CTL_M_CAN_STBY_SET(x) (((uint32_t)(x) << MCAN_GLB_CTL_M_CAN_STBY_SHIFT) & MCAN_GLB_CTL_M_CAN_STBY_MASK)
#define MCAN_GLB_CTL_M_CAN_STBY_GET(x) (((uint32_t)(x) & MCAN_GLB_CTL_M_CAN_STBY_MASK) >> MCAN_GLB_CTL_M_CAN_STBY_SHIFT)

/*
 * STBY_CLR_EN (RW)
 *
 * m_can standby clear control
 * 0:controlled by software by standby bit[bit31]
 * 1:auto clear standby by hardware when rx data is  0
 */
#define MCAN_GLB_CTL_STBY_CLR_EN_MASK (0x40000000UL)
#define MCAN_GLB_CTL_STBY_CLR_EN_SHIFT (30U)
#define MCAN_GLB_CTL_STBY_CLR_EN_SET(x) (((uint32_t)(x) << MCAN_GLB_CTL_STBY_CLR_EN_SHIFT) & MCAN_GLB_CTL_STBY_CLR_EN_MASK)
#define MCAN_GLB_CTL_STBY_CLR_EN_GET(x) (((uint32_t)(x) & MCAN_GLB_CTL_STBY_CLR_EN_MASK) >> MCAN_GLB_CTL_STBY_CLR_EN_SHIFT)

/*
 * STBY_POL (RW)
 *
 * standby polarity selection
 */
#define MCAN_GLB_CTL_STBY_POL_MASK (0x20000000UL)
#define MCAN_GLB_CTL_STBY_POL_SHIFT (29U)
#define MCAN_GLB_CTL_STBY_POL_SET(x) (((uint32_t)(x) << MCAN_GLB_CTL_STBY_POL_SHIFT) & MCAN_GLB_CTL_STBY_POL_MASK)
#define MCAN_GLB_CTL_STBY_POL_GET(x) (((uint32_t)(x) & MCAN_GLB_CTL_STBY_POL_MASK) >> MCAN_GLB_CTL_STBY_POL_SHIFT)

/*
 * TSU_TBIN_SEL (RW)
 *
 * external timestamp select. each CAN block has 4 timestamp input, this register is used to select one of them as timestame if TSCFG.TBCS is set to 1
 */
#define MCAN_GLB_CTL_TSU_TBIN_SEL_MASK (0x3U)
#define MCAN_GLB_CTL_TSU_TBIN_SEL_SHIFT (0U)
#define MCAN_GLB_CTL_TSU_TBIN_SEL_SET(x) (((uint32_t)(x) << MCAN_GLB_CTL_TSU_TBIN_SEL_SHIFT) & MCAN_GLB_CTL_TSU_TBIN_SEL_MASK)
#define MCAN_GLB_CTL_TSU_TBIN_SEL_GET(x) (((uint32_t)(x) & MCAN_GLB_CTL_TSU_TBIN_SEL_MASK) >> MCAN_GLB_CTL_TSU_TBIN_SEL_SHIFT)

/* Bitfield definition for register: GLB_STATUS */
/*
 * M_CAN_INT1 (R)
 *
 * m_can interrupt status1
 */
#define MCAN_GLB_STATUS_M_CAN_INT1_MASK (0x8U)
#define MCAN_GLB_STATUS_M_CAN_INT1_SHIFT (3U)
#define MCAN_GLB_STATUS_M_CAN_INT1_GET(x) (((uint32_t)(x) & MCAN_GLB_STATUS_M_CAN_INT1_MASK) >> MCAN_GLB_STATUS_M_CAN_INT1_SHIFT)

/*
 * M_CAN_INT0 (R)
 *
 * m_can interrupt status0
 */
#define MCAN_GLB_STATUS_M_CAN_INT0_MASK (0x4U)
#define MCAN_GLB_STATUS_M_CAN_INT0_SHIFT (2U)
#define MCAN_GLB_STATUS_M_CAN_INT0_GET(x) (((uint32_t)(x) & MCAN_GLB_STATUS_M_CAN_INT0_MASK) >> MCAN_GLB_STATUS_M_CAN_INT0_SHIFT)



/* TS_SEL register group index macro definition */
#define MCAN_TS_SEL_TS_SEL0 (0UL)
#define MCAN_TS_SEL_TS_SEL1 (1UL)
#define MCAN_TS_SEL_TS_SEL2 (2UL)
#define MCAN_TS_SEL_TS_SEL3 (3UL)
#define MCAN_TS_SEL_TS_SEL4 (4UL)
#define MCAN_TS_SEL_TS_SEL5 (5UL)
#define MCAN_TS_SEL_TS_SEL6 (6UL)
#define MCAN_TS_SEL_TS_SEL7 (7UL)
#define MCAN_TS_SEL_TS_SEL8 (8UL)
#define MCAN_TS_SEL_TS_SEL9 (9UL)
#define MCAN_TS_SEL_TS_SEL10 (10UL)
#define MCAN_TS_SEL_TS_SEL11 (11UL)
#define MCAN_TS_SEL_TS_SEL12 (12UL)
#define MCAN_TS_SEL_TS_SEL13 (13UL)
#define MCAN_TS_SEL_TS_SEL14 (14UL)
#define MCAN_TS_SEL_TS_SEL15 (15UL)


#endif /* HPM_MCAN_H */
