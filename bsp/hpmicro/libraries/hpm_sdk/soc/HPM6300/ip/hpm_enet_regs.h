/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_ENET_H
#define HPM_ENET_H

typedef struct {
    __RW uint32_t MACCFG;                      /* 0x0: MAC Configuration Register */
    __RW uint32_t MACFF;                       /* 0x4: MAC Frame Filter */
    __RW uint32_t HASH_H;                      /* 0x8: Hash Table High Register */
    __RW uint32_t HASH_L;                      /* 0xC: Hash Table Low Register */
    __RW uint32_t GMII_ADDR;                   /* 0x10: GMII Address Register */
    __RW uint32_t GMII_DATA;                   /* 0x14: GMII Data Register */
    __RW uint32_t FLOWCTRL;                    /* 0x18: Flow Control Register */
    __RW uint32_t VLAN_TAG;                    /* 0x1C: VLAN Tag Register */
    __R  uint8_t  RESERVED0[8];                /* 0x20 - 0x27: Reserved */
    __RW uint32_t RWKFRMFILT;                  /* 0x28: Remote Wake-Up Frame Filter Register */
    __RW uint32_t PMT_CSR;                     /* 0x2C: PMT Control and Status Register */
    __RW uint32_t LPI_CSR;                     /* 0x30: LPI Control and Status Register */
    __RW uint32_t LPI_TCR;                     /* 0x34: LPI Timers Control Register */
    __R  uint32_t INTR_STATUS;                 /* 0x38: Interrupt Status Register */
    __RW uint32_t INTR_MASK;                   /* 0x3C: Interrupt Mask Register */
    __RW uint32_t MAC_ADDR_0_HIGH;             /* 0x40: MAC Address 0 High Register */
    __RW uint32_t MAC_ADDR_0_LOW;              /* 0x44: MAC Address 0 Low Register */
    struct {
        __RW uint32_t HIGH;                    /* 0x48: MAC Address High Register */
        __RW uint32_t LOW;                     /* 0x4C: MAC Address Low Register */
    } MAC_ADDR[4];
    __R  uint8_t  RESERVED1[112];              /* 0x68 - 0xD7: Reserved */
    __RW uint32_t XMII_CSR;                    /* 0xD8: SGMII/RGMII/SMII Control and Status Register */
    __RW uint32_t WDOG_WTO;                    /* 0xDC: Watchdog Timeout Register */
    __R  uint8_t  RESERVED2[32];               /* 0xE0 - 0xFF: Reserved */
    __RW uint32_t MMC_CNTRL;                   /* 0x100: MMC Control establishes the operating mode of MMC. */
    __RW uint32_t MMC_INTR_RX;                 /* 0x104: MMC Receive Interrupt */
    __RW uint32_t MMC_INTR_TX;                 /* 0x108: MMC Transmit Interrupt */
    __RW uint32_t MMC_INTR_MASK_RX;            /* 0x10C: MMC Receive Interrupt mask */
    __RW uint32_t MMC_INTR_MASK_TX;            /* 0x110: MMC Transmit Interrupt Mask */
    __R  uint8_t  RESERVED3[16];               /* 0x114 - 0x123: Reserved */
    __RW uint32_t TX64OCTETS_GB;               /* 0x124: Number of good and bad frames transmitted with length 64 bytes,
exclusive of preamble and retried frames. */
    __RW uint32_t TX65TO127OCTETS_GB;          /* 0x128: Number of good and bad frames transmitted with length between
65 and 127 (inclusive) bytes, exclusive of preamble and retried
frames. */
    __RW uint32_t TX128TO255OCTETS_GB;         /* 0x12C: Number of good and bad frames transmitted with length between
128 and 255 (inclusive) bytes, exclusive of preamble and retried
frames. */
    __RW uint32_t TX256TO511OCTETS_GB;         /* 0x130: Number of good and bad frames transmitted with length between
256 and 511 (inclusive) bytes, exclusive of preamble and retried
frames. */
    __RW uint32_t TX512TO1023OCTETS_GB;        /* 0x134: Number of good and bad frames transmitted with length between
512 and 1,023 (inclusive) bytes, exclusive of preamble and retried
frames. */
    __RW uint32_t TX1024TOMAXOCTETS_GB;        /* 0x138: Number of good and bad frames transmitted with length between
1,024 and maxsize (inclusive) bytes, exclusive of preamble and
retried frames. */
    __R  uint8_t  RESERVED4[68];               /* 0x13C - 0x17F: Reserved */
    __RW uint32_t RXFRAMECOUNT_GB;             /* 0x180: Number of good and bad frames received */
    __R  uint8_t  RESERVED5[124];              /* 0x184 - 0x1FF: Reserved */
    __RW uint32_t MMC_IPC_INTR_MASK_RX;        /* 0x200: MMC IPC Receive Checksum Offload Interrupt Mask maintains
the mask for the interrupt generated from the receive IPC statistic
counters. */
    __R  uint8_t  RESERVED6[4];                /* 0x204 - 0x207: Reserved */
    __RW uint32_t MMC_IPC_INTR_RX;             /* 0x208: MMC Receive Checksum Offload Interrupt maintains the interrupt
that the receive IPC statistic counters generate. See Table 4-25
for further detail. */
    __R  uint8_t  RESERVED7[4];                /* 0x20C - 0x20F: Reserved */
    __RW uint32_t RXIPV4_GD_FMS;               /* 0x210: Number of good IPv4 datagrams received with the TCP, UDP, or
ICMP payload */
    __R  uint8_t  RESERVED8[492];              /* 0x214 - 0x3FF: Reserved */
    struct {
        __RW uint32_t L3_L4_CTRL;              /* 0x400: Layer 3 and Layer 4 Control Register */
        __RW uint32_t L4_ADDR;                 /* 0x404: Layer 4 Address Register */
        __R  uint8_t  RESERVED0[8];            /* 0x408 - 0x40F: Reserved */
        __RW uint32_t L3_ADDR_0;               /* 0x410: Layer 3 Address 0 Register */
        __RW uint32_t L3_ADDR_1;               /* 0x414: Layer 3 Address 1 Register */
        __RW uint32_t L3_ADDR_2;               /* 0x418: Layer 3 Address 2 Register */
        __RW uint32_t L3_ADDR_3;               /* 0x41C: Layer 3 Address 3 Register */
    } L3_L4_CFG[1];
    __R  uint8_t  RESERVED9[356];              /* 0x420 - 0x583: Reserved */
    __RW uint32_t VLAN_TAG_INC_RPL;            /* 0x584: VLAN Tag Inclusion or Replacement Register */
    __RW uint32_t VLAN_HASH;                   /* 0x588: VLAN Hash Table Register */
    __R  uint8_t  RESERVED10[372];             /* 0x58C - 0x6FF: Reserved */
    __RW uint32_t TS_CTRL;                     /* 0x700: Timestamp Control Register */
    __RW uint32_t SUB_SEC_INCR;                /* 0x704: Sub-Second Increment Register */
    __R  uint32_t SYST_SEC;                    /* 0x708: System Time - Seconds Register */
    __R  uint32_t SYST_NSEC;                   /* 0x70C: System Time - Nanoseconds Register */
    __RW uint32_t SYST_SEC_UPD;                /* 0x710: System Time - Seconds Update Register */
    __RW uint32_t SYST_NSEC_UPD;               /* 0x714: System Time - Nanoseconds Update Register */
    __RW uint32_t TS_ADDEND;                   /* 0x718: Timestamp Addend Register */
    __RW uint32_t TGTTM_SEC;                   /* 0x71C: Target Time Seconds Register */
    __RW uint32_t TGTTM_NSEC;                  /* 0x720: Target Time Nanoseconds Register */
    __RW uint32_t SYSTM_H_SEC;                 /* 0x724: System Time - Higher Word Seconds Register */
    __R  uint32_t TS_STATUS;                   /* 0x728: Timestamp Status Register */
    __RW uint32_t PPS_CTRL;                    /* 0x72C: PPS Control Register */
    __R  uint32_t AUX_TS_NSEC;                 /* 0x730: Auxiliary Timestamp - Nanoseconds Register */
    __R  uint32_t AUX_TS_SEC;                  /* 0x734: Auxiliary Timestamp - Seconds Register */
    __R  uint8_t  RESERVED11[40];              /* 0x738 - 0x75F: Reserved */
    __RW uint32_t PPS0_INTERVAL;               /* 0x760: PPS Interval Register */
    __RW uint32_t PPS0_WIDTH;                  /* 0x764: PPS Width Register */
    __R  uint8_t  RESERVED12[24];              /* 0x768 - 0x77F: Reserved */
    struct {
        __RW uint32_t TGTTM_SEC;               /* 0x780: PPS Target Time Seconds Register */
        __RW uint32_t TGTTM_NSEC;              /* 0x784: PPS Target Time Nanoseconds Register */
        __RW uint32_t INTERVAL;                /* 0x788: PPS Interval Register */
        __RW uint32_t WIDTH;                   /* 0x78C: PPS Width Register */
        __R  uint8_t  RESERVED0[16];           /* 0x790 - 0x79F: Reserved */
    } PPS[3];
    __R  uint8_t  RESERVED13[2080];            /* 0x7E0 - 0xFFF: Reserved */
    __RW uint32_t DMA_BUS_MODE;                /* 0x1000: Bus Mode Register */
    __RW uint32_t DMA_TX_POLL_DEMAND;          /* 0x1004: Transmit Poll Demand Register */
    __RW uint32_t DMA_RX_POLL_DEMAND;          /* 0x1008: Receive Poll Demand Register */
    __RW uint32_t DMA_RX_DESC_LIST_ADDR;       /* 0x100C: Receive Descriptor List Address Register */
    __RW uint32_t DMA_TX_DESC_LIST_ADDR;       /* 0x1010: Transmit Descriptor List Address Register */
    __RW uint32_t DMA_STATUS;                  /* 0x1014: Status Register */
    __RW uint32_t DMA_OP_MODE;                 /* 0x1018: Operation Mode Register */
    __RW uint32_t DMA_INTR_EN;                 /* 0x101C: Interrupt Enable Register */
    __RW uint32_t DMA_MISS_OVF_CNT;            /* 0x1020: Missed Frame And Buffer Overflow Counter Register */
    __RW uint32_t DMA_RX_INTR_WDOG;            /* 0x1024: Receive Interrupt Watchdog Timer Register */
    __RW uint32_t DMA_AXI_MODE;                /* 0x1028: AXI Bus Mode Register */
    __RW uint32_t DMA_BUS_STATUS;              /* 0x102C: AHB or AXI Status Register */
    __R  uint8_t  RESERVED14[24];              /* 0x1030 - 0x1047: Reserved */
    __RW uint32_t DMA_CURR_HOST_TX_DESC;       /* 0x1048: Current Host Transmit Descriptor Register */
    __RW uint32_t DMA_CURR_HOST_RX_DESC;       /* 0x104C: Current Host Receive Descriptor Register */
    __RW uint32_t DMA_CURR_HOST_TX_BUF;        /* 0x1050: Current Host Transmit Buffer Address Register */
    __RW uint32_t DMA_CURR_HOST_RX_BUF;        /* 0x1054: Current Host Receive Buffer Address Register */
    __R  uint8_t  RESERVED15[8112];            /* 0x1058 - 0x3007: Reserved */
    __RW uint32_t CTRL2;                       /* 0x3008: Control  Register 1 */
    __R  uint8_t  RESERVED16[28];              /* 0x300C - 0x3027: Reserved */
} ENET_Type;


/* Bitfield definition for register: MACCFG */
/*
 * SARC (RW)
 *
 * Source Address Insertion or Replacement Control
 *  This field controls the source address insertion or replacement for all transmitted frames.
 * Bit 30 specifies which MAC Address register (0 or 1) is used for source address insertion or replacement based on the values of Bits [29:28]:
 * - 2'b0x: The input signals mti_sa_ctrl_i and ati_sa_ctrl_i control the SA field generation.
 * - 2'b10: - If Bit 30 is set to 0, the MAC inserts the content of the MAC Address 0 registers (registers 16 and 17) in the SA field of all transmitted frames.
 *              - If Bit 30 is set to 1 and the Enable MAC Address Register 1 option is selected during core configuration,
 *                 the MAC inserts the content of the MAC Address 1 registers (registers 18 and 19) in the SA field of all transmitted frames.
 * - 2'b11: - If Bit 30 is set to 0, the MAC replaces the content of the MAC Address 0 registers (registers 16 and 17) in the SA field of all transmitted frames.
 *              - If Bit 30 is set to 1 and the Enable MAC Address Register 1 option is selected during core configuration,
 *                 the MAC replaces the content of the MAC Address 1 registers (registers 18 and 19) in the SA field of all transmitted frames.
 * Note: - Changes to this field take effect only on the start of a frame.
 * If you write this register field when a frame is being transmitted, only the subsequent frame can use the updated value,
 * that is, the current frame does not use the updated value.
 * - These bits are reserved and RO when the Enable SA, VLAN, and CRC Insertion on TX feature is not selected during core configuration.
 */
#define ENET_MACCFG_SARC_MASK (0x70000000UL)
#define ENET_MACCFG_SARC_SHIFT (28U)
#define ENET_MACCFG_SARC_SET(x) (((uint32_t)(x) << ENET_MACCFG_SARC_SHIFT) & ENET_MACCFG_SARC_MASK)
#define ENET_MACCFG_SARC_GET(x) (((uint32_t)(x) & ENET_MACCFG_SARC_MASK) >> ENET_MACCFG_SARC_SHIFT)

/*
 * TWOKPE (RW)
 *
 * IEEE 802.3as Support for 2K Packets
 *  When set, the MAC considers all frames, with up to 2,000 bytes length, as normal packets.
 * When Bit 20 (JE) is not set, the MAC considers all received frames of size more than 2K bytes as Giant frames.
 * When this bit is reset and Bit 20 (JE) is not set, the MAC considers all received frames of size more than 1,518 bytes (1,522 bytes for tagged) as Giant frames.
 * When Bit 20 is set, setting this bit has no effect on Giant Frame status.
 */
#define ENET_MACCFG_TWOKPE_MASK (0x8000000UL)
#define ENET_MACCFG_TWOKPE_SHIFT (27U)
#define ENET_MACCFG_TWOKPE_SET(x) (((uint32_t)(x) << ENET_MACCFG_TWOKPE_SHIFT) & ENET_MACCFG_TWOKPE_MASK)
#define ENET_MACCFG_TWOKPE_GET(x) (((uint32_t)(x) & ENET_MACCFG_TWOKPE_MASK) >> ENET_MACCFG_TWOKPE_SHIFT)

/*
 * SFTERR (RW)
 *
 * SMII Force Transmit Error
 *  When set, this bit indicates to the PHY to force a transmit error in the SMII frame being transmitted. This bit is reserved if the SMII PHY port is not selected during core configuration.
 */
#define ENET_MACCFG_SFTERR_MASK (0x4000000UL)
#define ENET_MACCFG_SFTERR_SHIFT (26U)
#define ENET_MACCFG_SFTERR_SET(x) (((uint32_t)(x) << ENET_MACCFG_SFTERR_SHIFT) & ENET_MACCFG_SFTERR_MASK)
#define ENET_MACCFG_SFTERR_GET(x) (((uint32_t)(x) & ENET_MACCFG_SFTERR_MASK) >> ENET_MACCFG_SFTERR_SHIFT)

/*
 * CST (RW)
 *
 * CRC Stripping for Type Frames
 *  When this bit is set, the last 4 bytes (FCS) of all frames of Ether type (Length/Type field greater than or equal to 1,536) are stripped and dropped before forwarding the frame to the application.
 * This function is not valid when the IP Checksum Engine (Type 1) is enabled in the MAC receiver. This function is valid when Type 2 Checksum Offload Engine is enabled.
 */
#define ENET_MACCFG_CST_MASK (0x2000000UL)
#define ENET_MACCFG_CST_SHIFT (25U)
#define ENET_MACCFG_CST_SET(x) (((uint32_t)(x) << ENET_MACCFG_CST_SHIFT) & ENET_MACCFG_CST_MASK)
#define ENET_MACCFG_CST_GET(x) (((uint32_t)(x) & ENET_MACCFG_CST_MASK) >> ENET_MACCFG_CST_SHIFT)

/*
 * TC (RW)
 *
 * Transmit Configuration in RGMII, SGMII, or SMII
 *  When set, this bit enables the transmission of duplex mode, link speed, and link up or down information to the PHY in the RGMII, SMII,
 *  or SGMII port. When this bit is reset, no such information is driven to the PHY.
 * This bit is reserved (and RO) if the RGMII, SMII, or SGMII PHY port is not selected during core configuration.
 */
#define ENET_MACCFG_TC_MASK (0x1000000UL)
#define ENET_MACCFG_TC_SHIFT (24U)
#define ENET_MACCFG_TC_SET(x) (((uint32_t)(x) << ENET_MACCFG_TC_SHIFT) & ENET_MACCFG_TC_MASK)
#define ENET_MACCFG_TC_GET(x) (((uint32_t)(x) & ENET_MACCFG_TC_MASK) >> ENET_MACCFG_TC_SHIFT)

/*
 * WD (RW)
 *
 * Watchdog Disable
 *  When this bit is set, the MAC disables the watchdog timer on the receiver. The MAC can receive frames of up to 16,383 bytes.
 */
#define ENET_MACCFG_WD_MASK (0x800000UL)
#define ENET_MACCFG_WD_SHIFT (23U)
#define ENET_MACCFG_WD_SET(x) (((uint32_t)(x) << ENET_MACCFG_WD_SHIFT) & ENET_MACCFG_WD_MASK)
#define ENET_MACCFG_WD_GET(x) (((uint32_t)(x) & ENET_MACCFG_WD_MASK) >> ENET_MACCFG_WD_SHIFT)

/*
 * JD (RW)
 *
 * Jabber Disable
 *  When this bit is set, the MAC disables the jabber timer on the transmitter. The MAC can transfer frames of up to 16,383 bytes.
 * When this bit is reset, the MAC cuts off the transmitter if the application sends out more than 2,048 bytes of data (10,240 if JE is set high) during transmission.
 */
#define ENET_MACCFG_JD_MASK (0x400000UL)
#define ENET_MACCFG_JD_SHIFT (22U)
#define ENET_MACCFG_JD_SET(x) (((uint32_t)(x) << ENET_MACCFG_JD_SHIFT) & ENET_MACCFG_JD_MASK)
#define ENET_MACCFG_JD_GET(x) (((uint32_t)(x) & ENET_MACCFG_JD_MASK) >> ENET_MACCFG_JD_SHIFT)

/*
 * BE (RW)
 *
 * Frame Burst Enable
 *  When this bit is set, the MAC allows frame bursting during transmission in the GMII half-duplex mode. This bit is reserved (and RO) in the 10/100 Mbps only or full-duplex-only configurations.
 */
#define ENET_MACCFG_BE_MASK (0x200000UL)
#define ENET_MACCFG_BE_SHIFT (21U)
#define ENET_MACCFG_BE_SET(x) (((uint32_t)(x) << ENET_MACCFG_BE_SHIFT) & ENET_MACCFG_BE_MASK)
#define ENET_MACCFG_BE_GET(x) (((uint32_t)(x) & ENET_MACCFG_BE_MASK) >> ENET_MACCFG_BE_SHIFT)

/*
 * JE (RW)
 *
 * Jumbo Frame Enable
 *  When this bit is set, the MAC allows Jumbo frames of 9,018 bytes (9,022 bytes for VLAN tagged frames) without reporting a giant frame error in the receive frame status.
 */
#define ENET_MACCFG_JE_MASK (0x100000UL)
#define ENET_MACCFG_JE_SHIFT (20U)
#define ENET_MACCFG_JE_SET(x) (((uint32_t)(x) << ENET_MACCFG_JE_SHIFT) & ENET_MACCFG_JE_MASK)
#define ENET_MACCFG_JE_GET(x) (((uint32_t)(x) & ENET_MACCFG_JE_MASK) >> ENET_MACCFG_JE_SHIFT)

/*
 * IFG (RW)
 *
 * Inter-Frame Gap
 *  These bits control the minimum IFG between frames during transmission.
 * - 000: 96 bit times
 * - 001: 88 bit times
 * - 010: 80 bit times - ...
 * - 111: 40 bit times In the half-duplex mode, the minimum IFG can be configured only for 64 bit times (IFG = 100).
 * Lower values are not considered.
 * In the 1000-Mbps mode, the minimum IFG supported is 64 bit times (and above) in the GMAC-CORE configuration and 80 bit times (and above) in other configurations.
 *  When a JAM pattern is being transmitted because of backpressure activation, the MAC does not consider the minimum IFG.
 */
#define ENET_MACCFG_IFG_MASK (0xE0000UL)
#define ENET_MACCFG_IFG_SHIFT (17U)
#define ENET_MACCFG_IFG_SET(x) (((uint32_t)(x) << ENET_MACCFG_IFG_SHIFT) & ENET_MACCFG_IFG_MASK)
#define ENET_MACCFG_IFG_GET(x) (((uint32_t)(x) & ENET_MACCFG_IFG_MASK) >> ENET_MACCFG_IFG_SHIFT)

/*
 * DCRS (RW)
 *
 * Disable Carrier Sense During Transmission
 *  When set high, this bit makes the MAC transmitter ignore the (G)MII CRS signal during frame transmission in the half-duplex mode.
 *  This request results in no errors generated because of Loss of Carrier or No Carrier during such transmission.
 * When this bit is low, the MAC transmitter generates such errors because of Carrier Sense and can even abort the transmissions.
 */
#define ENET_MACCFG_DCRS_MASK (0x10000UL)
#define ENET_MACCFG_DCRS_SHIFT (16U)
#define ENET_MACCFG_DCRS_SET(x) (((uint32_t)(x) << ENET_MACCFG_DCRS_SHIFT) & ENET_MACCFG_DCRS_MASK)
#define ENET_MACCFG_DCRS_GET(x) (((uint32_t)(x) & ENET_MACCFG_DCRS_MASK) >> ENET_MACCFG_DCRS_SHIFT)

/*
 * PS (RW)
 *
 * Port Select
 *  This bit selects the Ethernet line speed.
 * - 0: For 1000 Mbps operations
 * - 1: For 10 or 100 Mbps operations In 10 or 100 Mbps operations, this bit, along with FES bit, selects the exact line speed.
 * In the 10/100 Mbps-only (always 1) or 1000 Mbps-only (always 0) configurations, this bit is read-only with the appropriate value. In default 10/100/1000 Mbps configuration,
 * this bit is R_W. The mac_portselect_o or mac_speed_o[1] signal reflects the value of this bit.
 */
#define ENET_MACCFG_PS_MASK (0x8000U)
#define ENET_MACCFG_PS_SHIFT (15U)
#define ENET_MACCFG_PS_SET(x) (((uint32_t)(x) << ENET_MACCFG_PS_SHIFT) & ENET_MACCFG_PS_MASK)
#define ENET_MACCFG_PS_GET(x) (((uint32_t)(x) & ENET_MACCFG_PS_MASK) >> ENET_MACCFG_PS_SHIFT)

/*
 * FES (RW)
 *
 * Speed
 *  This bit selects the speed in the MII, RMII, SMII, RGMII, SGMII, or RevMII interface:
 * - 0: 10 Mbps
 * - 1: 100 Mbps This bit is reserved (RO) by default and is enabled only when the parameter SPEED_SELECT = Enabled.
 * This bit generates link speed encoding when Bit 24 (TC) is set in the RGMII, SMII, or SGMII mode.
 * This bit is always enabled for RGMII, SGMII, SMII, or RevMII interface.
 * In configurations with RGMII, SGMII, SMII, or RevMII interface, this bit is driven as an output signal (mac_speed_o[0]) to reflect the value of this bit in the mac_speed_o signal.
 * In configurations with RMII, MII, or GMII interface, you can optionally drive this bit as an output signal (mac_speed_o[0]) to reflect its value in the mac_speed_o signal.
 */
#define ENET_MACCFG_FES_MASK (0x4000U)
#define ENET_MACCFG_FES_SHIFT (14U)
#define ENET_MACCFG_FES_SET(x) (((uint32_t)(x) << ENET_MACCFG_FES_SHIFT) & ENET_MACCFG_FES_MASK)
#define ENET_MACCFG_FES_GET(x) (((uint32_t)(x) & ENET_MACCFG_FES_MASK) >> ENET_MACCFG_FES_SHIFT)

/*
 * DO (RW)
 *
 * Disable Receive Own
 *  When this bit is set, the MAC disables the reception of frames when the phy_txen_o is asserted in the half-duplex mode.
 * When this bit is reset, the MAC receives all packets that are given by the PHY while transmitting.
 * This bit is not applicable if the MAC is operating in the full-duplex mode. This bit is reserved (RO with default value) if the MAC is configured for the full-duplex-only operation.
 */
#define ENET_MACCFG_DO_MASK (0x2000U)
#define ENET_MACCFG_DO_SHIFT (13U)
#define ENET_MACCFG_DO_SET(x) (((uint32_t)(x) << ENET_MACCFG_DO_SHIFT) & ENET_MACCFG_DO_MASK)
#define ENET_MACCFG_DO_GET(x) (((uint32_t)(x) & ENET_MACCFG_DO_MASK) >> ENET_MACCFG_DO_SHIFT)

/*
 * LM (RW)
 *
 * Loopback Mode
 *  When this bit is set, the MAC operates in the loopback mode at GMII or MII.
 * The (G)MII Receive clock input (clk_rx_i) is required for the loopback to work properly, because the Transmit clock is not looped-back internally.
 */
#define ENET_MACCFG_LM_MASK (0x1000U)
#define ENET_MACCFG_LM_SHIFT (12U)
#define ENET_MACCFG_LM_SET(x) (((uint32_t)(x) << ENET_MACCFG_LM_SHIFT) & ENET_MACCFG_LM_MASK)
#define ENET_MACCFG_LM_GET(x) (((uint32_t)(x) & ENET_MACCFG_LM_MASK) >> ENET_MACCFG_LM_SHIFT)

/*
 * DM (RW)
 *
 * Duplex Mode
 *  When this bit is set, the MAC operates in the full-duplex mode where it can transmit and receive simultaneously.
 */
#define ENET_MACCFG_DM_MASK (0x800U)
#define ENET_MACCFG_DM_SHIFT (11U)
#define ENET_MACCFG_DM_SET(x) (((uint32_t)(x) << ENET_MACCFG_DM_SHIFT) & ENET_MACCFG_DM_MASK)
#define ENET_MACCFG_DM_GET(x) (((uint32_t)(x) & ENET_MACCFG_DM_MASK) >> ENET_MACCFG_DM_SHIFT)

/*
 * IPC (RW)
 *
 * Checksum Offload
 * When this bit is set, the MAC calculates the 16-bit one’s complement of the one’s complement sum of all received Ethernet frame payloads.
 * It also checks whether the IPv4 Header checksum (assumed to be bytes 25–26 or 29–30 (VLAN-tagged)
 * of the received Ethernet frame) is correct for the received frame and gives the status in the receive status word.
 * The MAC also appends the 16-bit checksum calculated for the IP header datagram payload (bytes after the IPv4 header)
 * and appends it to the Ethernet frame transferred to the application (when Type 2 COE is deselected).
 * When this bit is reset, this function is disabled.
 * When Type 2 COE is selected, this bit, when set, enables the IPv4 header checksum checking and IPv4 or IPv6 TCP, UDP, or ICMP payload checksum checking.
 */
#define ENET_MACCFG_IPC_MASK (0x400U)
#define ENET_MACCFG_IPC_SHIFT (10U)
#define ENET_MACCFG_IPC_SET(x) (((uint32_t)(x) << ENET_MACCFG_IPC_SHIFT) & ENET_MACCFG_IPC_MASK)
#define ENET_MACCFG_IPC_GET(x) (((uint32_t)(x) & ENET_MACCFG_IPC_MASK) >> ENET_MACCFG_IPC_SHIFT)

/*
 * DR (RW)
 *
 * Disable Retry
 * When this bit is set, the MAC attempts only one transmission.
 * When a collision occurs on the GMII or MII interface,
 * the MAC ignores the current frame transmission and reports a Frame Abort with excessive collision error in the transmit frame status.
 * When this bit is reset, the MAC attempts retries based on the settings of the BL field (Bits [6:5]).
 */
#define ENET_MACCFG_DR_MASK (0x200U)
#define ENET_MACCFG_DR_SHIFT (9U)
#define ENET_MACCFG_DR_SET(x) (((uint32_t)(x) << ENET_MACCFG_DR_SHIFT) & ENET_MACCFG_DR_MASK)
#define ENET_MACCFG_DR_GET(x) (((uint32_t)(x) & ENET_MACCFG_DR_MASK) >> ENET_MACCFG_DR_SHIFT)

/*
 * LUD (RW)
 *
 * Link Up or Down
 *  This bit indicates whether the link is up or down during the transmission of configuration in the RGMII, SGMII, or SMII interface:
 * - 0: Link Down
 * - 1: Link Up
 */
#define ENET_MACCFG_LUD_MASK (0x100U)
#define ENET_MACCFG_LUD_SHIFT (8U)
#define ENET_MACCFG_LUD_SET(x) (((uint32_t)(x) << ENET_MACCFG_LUD_SHIFT) & ENET_MACCFG_LUD_MASK)
#define ENET_MACCFG_LUD_GET(x) (((uint32_t)(x) & ENET_MACCFG_LUD_MASK) >> ENET_MACCFG_LUD_SHIFT)

/*
 * ACS (RW)
 *
 * Automatic Pad or CRC Stripping
 *  When this bit is set, the MAC strips the Pad or FCS field on the incoming frames only if the value of the length field is less than 1,536 bytes.
 * All received frames with length field greater than or equal to 1,536 bytes are passed to the application without stripping the Pad or FCS field.
 * When this bit is reset, the MAC passes all incoming frames, without modifying them, to the Host.
 */
#define ENET_MACCFG_ACS_MASK (0x80U)
#define ENET_MACCFG_ACS_SHIFT (7U)
#define ENET_MACCFG_ACS_SET(x) (((uint32_t)(x) << ENET_MACCFG_ACS_SHIFT) & ENET_MACCFG_ACS_MASK)
#define ENET_MACCFG_ACS_GET(x) (((uint32_t)(x) & ENET_MACCFG_ACS_MASK) >> ENET_MACCFG_ACS_SHIFT)

/*
 * BL (RW)
 *
 * Back-Off Limit
 *  The Back-Off limit determines the random integer number (r) of slot time delays
 *  (4,096 bit times for 1000 Mbps and 512 bit times for 10/100 Mbps) for which the MAC waits before rescheduling a transmission attempt during retries after a collision.
 * This bit is applicable only in the half-duplex mode and is reserved (RO) in the full-duplex-only configuration.
 * - 00: k= min (n, 10)
 * - 01: k = min (n, 8)
 * - 10: k = min (n, 4)
 * - 11: k = min (n, 1) where n = retransmission attempt. The random integer r takes the value in the range 0 ≤ r < 2k
 */
#define ENET_MACCFG_BL_MASK (0x60U)
#define ENET_MACCFG_BL_SHIFT (5U)
#define ENET_MACCFG_BL_SET(x) (((uint32_t)(x) << ENET_MACCFG_BL_SHIFT) & ENET_MACCFG_BL_MASK)
#define ENET_MACCFG_BL_GET(x) (((uint32_t)(x) & ENET_MACCFG_BL_MASK) >> ENET_MACCFG_BL_SHIFT)

/*
 * DC (RW)
 *
 * Deferral Check
 *  When this bit is set, the deferral check function is enabled in the MAC.
 * The MAC issues a Frame Abort status, along with the excessive deferral error bit set in the transmit frame status,
 * when the transmit state machine is deferred for more than 24,288 bit times in the 10 or 100 Mbps mode.
 *  If the MAC is configured for 1000 Mbps operation or if the Jumbo frame mode is enabled in the 10 or 100 Mbps mode,
 *  the threshold for deferral is 155,680 bits times. Deferral begins when the transmitter is ready to transmit,
 * but it is prevented because of an active carrier sense signal (CRS) on GMII or MII. The defer time is not cumulative.
 * For example, if the transmitter defers for 10,000 bit times because the CRS signal is active and then the CRS signal becomes inactive,
 * the transmitter transmits and collision happens.
 * Because of collision, the transmitter needs to back off and then defer again after back off completion.
 * In such a scenario, the deferral timer is reset to 0 and it is restarted.
 */
#define ENET_MACCFG_DC_MASK (0x10U)
#define ENET_MACCFG_DC_SHIFT (4U)
#define ENET_MACCFG_DC_SET(x) (((uint32_t)(x) << ENET_MACCFG_DC_SHIFT) & ENET_MACCFG_DC_MASK)
#define ENET_MACCFG_DC_GET(x) (((uint32_t)(x) & ENET_MACCFG_DC_MASK) >> ENET_MACCFG_DC_SHIFT)

/*
 * TE (RW)
 *
 * Transmitter Enable
 *  When this bit is set, the transmit state machine of the MAC is enabled for transmission on the GMII or MII. When this bit is reset,
 *  the MAC transmit state machine is disabled after the completion of the transmission of the current frame, and does not transmit any further frames.
 */
#define ENET_MACCFG_TE_MASK (0x8U)
#define ENET_MACCFG_TE_SHIFT (3U)
#define ENET_MACCFG_TE_SET(x) (((uint32_t)(x) << ENET_MACCFG_TE_SHIFT) & ENET_MACCFG_TE_MASK)
#define ENET_MACCFG_TE_GET(x) (((uint32_t)(x) & ENET_MACCFG_TE_MASK) >> ENET_MACCFG_TE_SHIFT)

/*
 * RE (RW)
 *
 * Receiver Enable
 *  When this bit is set, the receiver state machine of the MAC is enabled for receiving frames from the GMII or MII. When this bit is reset,
 * the MAC receive state machine is disabled after the completion of the reception of the current frame, and does not receive any further frames from the GMII or MII.
 */
#define ENET_MACCFG_RE_MASK (0x4U)
#define ENET_MACCFG_RE_SHIFT (2U)
#define ENET_MACCFG_RE_SET(x) (((uint32_t)(x) << ENET_MACCFG_RE_SHIFT) & ENET_MACCFG_RE_MASK)
#define ENET_MACCFG_RE_GET(x) (((uint32_t)(x) & ENET_MACCFG_RE_MASK) >> ENET_MACCFG_RE_SHIFT)

/*
 * PRELEN (RW)
 *
 * Preamble Length for Transmit frames
 *  These bits control the number of preamble bytes that are added to the beginning of every Transmit frame.
 *  The preamble reduction occurs only when the MAC is operating in the full-duplex mode.
 * - 2'b00: 7 bytes of preamble
 * - 2'b01: 5 bytes of preamble
 * - 2'b10: 3 bytes of preamble
 * - 2'b11: Reserved
 */
#define ENET_MACCFG_PRELEN_MASK (0x3U)
#define ENET_MACCFG_PRELEN_SHIFT (0U)
#define ENET_MACCFG_PRELEN_SET(x) (((uint32_t)(x) << ENET_MACCFG_PRELEN_SHIFT) & ENET_MACCFG_PRELEN_MASK)
#define ENET_MACCFG_PRELEN_GET(x) (((uint32_t)(x) & ENET_MACCFG_PRELEN_MASK) >> ENET_MACCFG_PRELEN_SHIFT)

/* Bitfield definition for register: MACFF */
/*
 * RA (RW)
 *
 * Receive All
 *  When this bit is set, the MAC Receiver module passes all received frames, irrespective of whether they pass the address filter or not, to the Application.
 * The result of the SA or DA filtering is updated (pass or fail) in the corresponding bits in the Receive Status Word. When this bit is reset,
 * the Receiver module passes only those frames to the Application that pass the SA or DA address filter.
 */
#define ENET_MACFF_RA_MASK (0x80000000UL)
#define ENET_MACFF_RA_SHIFT (31U)
#define ENET_MACFF_RA_SET(x) (((uint32_t)(x) << ENET_MACFF_RA_SHIFT) & ENET_MACFF_RA_MASK)
#define ENET_MACFF_RA_GET(x) (((uint32_t)(x) & ENET_MACFF_RA_MASK) >> ENET_MACFF_RA_SHIFT)

/*
 * DNTU (RW)
 *
 * Drop non-TCP/UDP over IP Frames
 *  When set, this bit enables the MAC to drop the non-TCP or UDP over IP frames. The MAC forward only those frames that are processed by the Layer 4 filter.
 * When reset, this bit enables the MAC to forward all non-TCP or UDP over IP frames.
 */
#define ENET_MACFF_DNTU_MASK (0x200000UL)
#define ENET_MACFF_DNTU_SHIFT (21U)
#define ENET_MACFF_DNTU_SET(x) (((uint32_t)(x) << ENET_MACFF_DNTU_SHIFT) & ENET_MACFF_DNTU_MASK)
#define ENET_MACFF_DNTU_GET(x) (((uint32_t)(x) & ENET_MACFF_DNTU_MASK) >> ENET_MACFF_DNTU_SHIFT)

/*
 * IPFE (RW)
 *
 * Layer 3 and Layer 4 Filter Enable
 *  When set, this bit enables the MAC to drop frames that do not match the enabled Layer 3 and Layer 4 filters. If Layer 3 or Layer 4 filters are not enabled for matching,
 * this bit does not have any effect. When reset, the MAC forwards all frames irrespective of the match status of the Layer 3 and Layer 4 fields.
 */
#define ENET_MACFF_IPFE_MASK (0x100000UL)
#define ENET_MACFF_IPFE_SHIFT (20U)
#define ENET_MACFF_IPFE_SET(x) (((uint32_t)(x) << ENET_MACFF_IPFE_SHIFT) & ENET_MACFF_IPFE_MASK)
#define ENET_MACFF_IPFE_GET(x) (((uint32_t)(x) & ENET_MACFF_IPFE_MASK) >> ENET_MACFF_IPFE_SHIFT)

/*
 * VTFE (RW)
 *
 * VLAN Tag Filter Enable
 *  When set, this bit enables the MAC to drop VLAN tagged frames that do not match the VLAN Tag comparison.
 * When reset, the MAC forwards all frames irrespective of the match status of the VLAN Tag.
 */
#define ENET_MACFF_VTFE_MASK (0x8000U)
#define ENET_MACFF_VTFE_SHIFT (15U)
#define ENET_MACFF_VTFE_SET(x) (((uint32_t)(x) << ENET_MACFF_VTFE_SHIFT) & ENET_MACFF_VTFE_MASK)
#define ENET_MACFF_VTFE_GET(x) (((uint32_t)(x) & ENET_MACFF_VTFE_MASK) >> ENET_MACFF_VTFE_SHIFT)

/*
 * HPF (RW)
 *
 * Hash or Perfect Filter
 *  When this bit is set, it configures the address filter to pass a frame if it matches either the perfect filtering or the hash filtering as set by the HMC or HUC bits.
 * When this bit is low and the HUC or HMC bit is set, the frame is passed only if it matches the Hash filter.
 */
#define ENET_MACFF_HPF_MASK (0x400U)
#define ENET_MACFF_HPF_SHIFT (10U)
#define ENET_MACFF_HPF_SET(x) (((uint32_t)(x) << ENET_MACFF_HPF_SHIFT) & ENET_MACFF_HPF_MASK)
#define ENET_MACFF_HPF_GET(x) (((uint32_t)(x) & ENET_MACFF_HPF_MASK) >> ENET_MACFF_HPF_SHIFT)

/*
 * SAF (RW)
 *
 * Source Address Filter Enable
 *  When this bit is set, the MAC compares the SA field of the received frames with the values programmed in the enabled SA registers. If the comparison fails,
 *  the MAC drops the frame. When this bit is reset, the MAC forwards the received frame to the application with updated SAF bit of the Rx Status depending on the SA address comparison.
 */
#define ENET_MACFF_SAF_MASK (0x200U)
#define ENET_MACFF_SAF_SHIFT (9U)
#define ENET_MACFF_SAF_SET(x) (((uint32_t)(x) << ENET_MACFF_SAF_SHIFT) & ENET_MACFF_SAF_MASK)
#define ENET_MACFF_SAF_GET(x) (((uint32_t)(x) & ENET_MACFF_SAF_MASK) >> ENET_MACFF_SAF_SHIFT)

/*
 * SAIF (RW)
 *
 * SA Inverse Filtering
 * When this bit is set, the Address Check block operates in inverse filtering mode for the SA address comparison. The frames whose SA matches the SA registers are marked as failing the SA Address filter.
 * When this bit is reset, frames whose SA does not match the SA registers are marked as failing the SA Address filter.
 */
#define ENET_MACFF_SAIF_MASK (0x100U)
#define ENET_MACFF_SAIF_SHIFT (8U)
#define ENET_MACFF_SAIF_SET(x) (((uint32_t)(x) << ENET_MACFF_SAIF_SHIFT) & ENET_MACFF_SAIF_MASK)
#define ENET_MACFF_SAIF_GET(x) (((uint32_t)(x) & ENET_MACFF_SAIF_MASK) >> ENET_MACFF_SAIF_SHIFT)

/*
 * PCF (RW)
 *
 * Pass Control Frames
 *  These bits control the forwarding of all control frames (including unicast and multicast Pause frames).
 * - 00: MAC filters all control frames from reaching the application.
 * - 01: MAC forwards all control frames except Pause frames to application even if they fail the Address filter.
 * - 10: MAC forwards all control frames to application even if they fail the Address Filter.
 * - 11: MAC forwards control frames that pass the Address Filter.
 * The following conditions should be true for the Pause frames processing:
 * - Condition 1: The MAC is in the full-duplex mode and flow control is enabled by setting Bit 2 (RFE) of Register 6 (Flow Control Register) to 1.
 * - Condition 2: The destination address (DA) of the received frame matches the special multicast address or the MAC Address 0 when Bit 3 (UP) of the Register 6 (Flow Control Register) is set.
 * - Condition 3: The Type field of the received frame is 0x8808 and the OPCODE field is 0x0001.
 * Note: This field should be set to 01 only when the Condition 1 is true,
 * that is, the MAC is programmed to operate in the full-duplex mode and the RFE bit is enabled.
 * Otherwise, the Pause frame filtering may be inconsistent.
 * When Condition 1 is false, the Pause frames are considered as generic control frames.
 * Therefore, to pass all control frames (including Pause frames) when the full-duplex mode and flow control is not enabled,
 * you should set the PCF field to 10 or 11 (as required by the application).
 */
#define ENET_MACFF_PCF_MASK (0xC0U)
#define ENET_MACFF_PCF_SHIFT (6U)
#define ENET_MACFF_PCF_SET(x) (((uint32_t)(x) << ENET_MACFF_PCF_SHIFT) & ENET_MACFF_PCF_MASK)
#define ENET_MACFF_PCF_GET(x) (((uint32_t)(x) & ENET_MACFF_PCF_MASK) >> ENET_MACFF_PCF_SHIFT)

/*
 * DBF (RW)
 *
 * Disable Broadcast Frames
 *  When this bit is set, the AFM module blocks all incoming broadcast frames. In addition, it overrides all other filter settings.
 * When this bit is reset, the AFM module passes all received broadcast frames.
 */
#define ENET_MACFF_DBF_MASK (0x20U)
#define ENET_MACFF_DBF_SHIFT (5U)
#define ENET_MACFF_DBF_SET(x) (((uint32_t)(x) << ENET_MACFF_DBF_SHIFT) & ENET_MACFF_DBF_MASK)
#define ENET_MACFF_DBF_GET(x) (((uint32_t)(x) & ENET_MACFF_DBF_MASK) >> ENET_MACFF_DBF_SHIFT)

/*
 * PM (RW)
 *
 * Pass All Multicast
 * When set, this bit indicates that all received frames with a multicast destination address (first bit in the destination address field is '1') are passed.
 * When reset, filtering of multicast frame depends on HMC bit.
 */
#define ENET_MACFF_PM_MASK (0x10U)
#define ENET_MACFF_PM_SHIFT (4U)
#define ENET_MACFF_PM_SET(x) (((uint32_t)(x) << ENET_MACFF_PM_SHIFT) & ENET_MACFF_PM_MASK)
#define ENET_MACFF_PM_GET(x) (((uint32_t)(x) & ENET_MACFF_PM_MASK) >> ENET_MACFF_PM_SHIFT)

/*
 * DAIF (RW)
 *
 * DA Inverse Filtering
 *  When this bit is set, the Address Check block operates in inverse filtering mode for the DA address comparison for both unicast and multicast frames.
 * When reset, normal filtering of frames is performed.
 */
#define ENET_MACFF_DAIF_MASK (0x8U)
#define ENET_MACFF_DAIF_SHIFT (3U)
#define ENET_MACFF_DAIF_SET(x) (((uint32_t)(x) << ENET_MACFF_DAIF_SHIFT) & ENET_MACFF_DAIF_MASK)
#define ENET_MACFF_DAIF_GET(x) (((uint32_t)(x) & ENET_MACFF_DAIF_MASK) >> ENET_MACFF_DAIF_SHIFT)

/*
 * HMC (RW)
 *
 * Hash Multicast
 * When set, the MAC performs destination address filtering of received multicast frames according to the hash table. When reset,
 * the MAC performs a perfect destination address filtering for multicast frames, that is, it compares the DA field with the values programmed in DA registers.
 */
#define ENET_MACFF_HMC_MASK (0x4U)
#define ENET_MACFF_HMC_SHIFT (2U)
#define ENET_MACFF_HMC_SET(x) (((uint32_t)(x) << ENET_MACFF_HMC_SHIFT) & ENET_MACFF_HMC_MASK)
#define ENET_MACFF_HMC_GET(x) (((uint32_t)(x) & ENET_MACFF_HMC_MASK) >> ENET_MACFF_HMC_SHIFT)

/*
 * HUC (RW)
 *
 * Hash Unicast
 *  When set, the MAC performs destination address filtering of unicast frames according to the hash table.
 * When reset, the MAC performs a perfect destination address filtering for unicast frames, that is, it compares the DA field with the values programmed in DA registers.
 */
#define ENET_MACFF_HUC_MASK (0x2U)
#define ENET_MACFF_HUC_SHIFT (1U)
#define ENET_MACFF_HUC_SET(x) (((uint32_t)(x) << ENET_MACFF_HUC_SHIFT) & ENET_MACFF_HUC_MASK)
#define ENET_MACFF_HUC_GET(x) (((uint32_t)(x) & ENET_MACFF_HUC_MASK) >> ENET_MACFF_HUC_SHIFT)

/*
 * PR (RW)
 *
 * Promiscuous Mode
 * When this bit is set, the Address Filter module passes all incoming frames irrespective of the destination or source address.
 *  The SA or DA Filter Fails status bits of the Receive Status Word are always cleared when PR is set.
 */
#define ENET_MACFF_PR_MASK (0x1U)
#define ENET_MACFF_PR_SHIFT (0U)
#define ENET_MACFF_PR_SET(x) (((uint32_t)(x) << ENET_MACFF_PR_SHIFT) & ENET_MACFF_PR_MASK)
#define ENET_MACFF_PR_GET(x) (((uint32_t)(x) & ENET_MACFF_PR_MASK) >> ENET_MACFF_PR_SHIFT)

/* Bitfield definition for register: HASH_H */
/*
 * HTH (RW)
 *
 * Hash Table High
 *  This field contains the upper 32 bits of the Hash table.
 */
#define ENET_HASH_H_HTH_MASK (0xFFFFFFFFUL)
#define ENET_HASH_H_HTH_SHIFT (0U)
#define ENET_HASH_H_HTH_SET(x) (((uint32_t)(x) << ENET_HASH_H_HTH_SHIFT) & ENET_HASH_H_HTH_MASK)
#define ENET_HASH_H_HTH_GET(x) (((uint32_t)(x) & ENET_HASH_H_HTH_MASK) >> ENET_HASH_H_HTH_SHIFT)

/* Bitfield definition for register: HASH_L */
/*
 * HTL (RW)
 *
 * Hash Table Low
 *  This field contains the lower 32 bits of the Hash table.
 */
#define ENET_HASH_L_HTL_MASK (0xFFFFFFFFUL)
#define ENET_HASH_L_HTL_SHIFT (0U)
#define ENET_HASH_L_HTL_SET(x) (((uint32_t)(x) << ENET_HASH_L_HTL_SHIFT) & ENET_HASH_L_HTL_MASK)
#define ENET_HASH_L_HTL_GET(x) (((uint32_t)(x) & ENET_HASH_L_HTL_MASK) >> ENET_HASH_L_HTL_SHIFT)

/* Bitfield definition for register: GMII_ADDR */
/*
 * PA (RW)
 *
 * Physical Layer Address
 *  This field indicates which of the 32 possible PHY devices are being accessed. For RevMII, this field gives the PHY Address of the RevMII module.
 */
#define ENET_GMII_ADDR_PA_MASK (0xF800U)
#define ENET_GMII_ADDR_PA_SHIFT (11U)
#define ENET_GMII_ADDR_PA_SET(x) (((uint32_t)(x) << ENET_GMII_ADDR_PA_SHIFT) & ENET_GMII_ADDR_PA_MASK)
#define ENET_GMII_ADDR_PA_GET(x) (((uint32_t)(x) & ENET_GMII_ADDR_PA_MASK) >> ENET_GMII_ADDR_PA_SHIFT)

/*
 * GR (RW)
 *
 * GMII Register
 *  These bits select the desired GMII register in the selected PHY device. For RevMII, these bits select the desired CSR register in the RevMII Registers set.
 */
#define ENET_GMII_ADDR_GR_MASK (0x7C0U)
#define ENET_GMII_ADDR_GR_SHIFT (6U)
#define ENET_GMII_ADDR_GR_SET(x) (((uint32_t)(x) << ENET_GMII_ADDR_GR_SHIFT) & ENET_GMII_ADDR_GR_MASK)
#define ENET_GMII_ADDR_GR_GET(x) (((uint32_t)(x) & ENET_GMII_ADDR_GR_MASK) >> ENET_GMII_ADDR_GR_SHIFT)

/*
 * CR (RW)
 *
 * CSR Clock Range
 *  The CSR Clock Range selection determines the frequency of the MDC clock according to the CSR clock frequency used in your design.
 * The CSR clock corresponding to different GMAC configurations is given in Table 9-2 on page 564.
 * The suggested range of CSR clock frequency applicable for each value (when Bit[5] = 0)
 * ensures that the MDC clock is approximately between the frequency range 1.0 MHz–2.5 MHz.
 * - 0000: The CSR clock frequency is 60–100 MHz and the MDC clock frequency is CSR clock/42.
 * - 0001: The CSR clock frequency is 100–150 MHz and the MDC clock frequency is CSR clock/62.
 * - 0010: The CSR clock frequency is 20–35 MHz and the MDC clock frequency is CSR clock/16.
 * - 0011: The CSR clock frequency is 35–60 MHz and the MDC clock frequency is CSR clock/26.
 * - 0100: The CSR clock frequency is 150–250 MHz and the MDC clock frequency is CSR clock/102.
 * - 0101: The CSR clock frequency is 250–300 MHz and the MDC clock is CSR clock/124.
 * - 0110, 0111: Reserved
 * When Bit 5 is set, you can achieve higher frequency of the MDC clock than the frequency limit of 2.5 MHz (specified in the IEEE Std 802.3) and program a clock divider of lower value.
 * For example,
 * when CSR clock is of 100 MHz frequency and you program these bits as 1010,
 * then the resultant MDC clock is of 12.5 MHz which is outside the limit of IEEE 802.3 specified range.
 * Program the following values only if the interfacing chips support faster MDC clocks.
 * - 1000: CSR clock/4
 * - 1001: CSR clock/6
 * - 1010: CSR clock/8
 * - 1011: CSR clock/10
 * - 1100: CSR clock/12
 * - 1101: CSR clock/14
 * - 1110: CSR clock/16
 * - 1111: CSR clock/18 These bits are not used for accessing RevMII. These bits are read-only if the RevMII interface is selected as single PHY interface.
 */
#define ENET_GMII_ADDR_CR_MASK (0x3CU)
#define ENET_GMII_ADDR_CR_SHIFT (2U)
#define ENET_GMII_ADDR_CR_SET(x) (((uint32_t)(x) << ENET_GMII_ADDR_CR_SHIFT) & ENET_GMII_ADDR_CR_MASK)
#define ENET_GMII_ADDR_CR_GET(x) (((uint32_t)(x) & ENET_GMII_ADDR_CR_MASK) >> ENET_GMII_ADDR_CR_SHIFT)

/*
 * GW (RW)
 *
 * GMII Write
 *  When set, this bit indicates to the PHY or RevMII that this is a Write operation using the GMII Data register. If this bit is not set,
 * it indicates that this is a Read operation, that is, placing the data in the GMII Data register.
 */
#define ENET_GMII_ADDR_GW_MASK (0x2U)
#define ENET_GMII_ADDR_GW_SHIFT (1U)
#define ENET_GMII_ADDR_GW_SET(x) (((uint32_t)(x) << ENET_GMII_ADDR_GW_SHIFT) & ENET_GMII_ADDR_GW_MASK)
#define ENET_GMII_ADDR_GW_GET(x) (((uint32_t)(x) & ENET_GMII_ADDR_GW_MASK) >> ENET_GMII_ADDR_GW_SHIFT)

/*
 * GB (RW)
 *
 * GMII Busy
 *  This bit should read logic 0 before writing to Register 4 and Register 5.
 * During a PHY or RevMII register access, the software sets this bit to 1’b1 to indicate that a Read or Write access is in progress.
 *  Register 5 is invalid until this bit is cleared by the MAC.
 * Therefore, Register 5 (GMII Data) should be kept valid until the MAC clears this bit during a PHY Write operation.
 * Similarly for a read operation, the contents of Register 5 are not valid until this bit is cleared.
 * The subsequent read or write operation should happen only after the previous operation is complete.
 * Because there is no acknowledgment from the PHY to MAC after a read or write operation is completed,
 * there is no change in the functionality of this bit even when the PHY is not present.
 */
#define ENET_GMII_ADDR_GB_MASK (0x1U)
#define ENET_GMII_ADDR_GB_SHIFT (0U)
#define ENET_GMII_ADDR_GB_SET(x) (((uint32_t)(x) << ENET_GMII_ADDR_GB_SHIFT) & ENET_GMII_ADDR_GB_MASK)
#define ENET_GMII_ADDR_GB_GET(x) (((uint32_t)(x) & ENET_GMII_ADDR_GB_MASK) >> ENET_GMII_ADDR_GB_SHIFT)

/* Bitfield definition for register: GMII_DATA */
/*
 * GD (RW)
 *
 * GMII Data
 *  This field contains the 16-bit data value read from the PHY or RevMII after a Management Read operation
 * or the 16-bit data value to be written to the PHY or RevMII before a Management Write operation.
 */
#define ENET_GMII_DATA_GD_MASK (0xFFFFU)
#define ENET_GMII_DATA_GD_SHIFT (0U)
#define ENET_GMII_DATA_GD_SET(x) (((uint32_t)(x) << ENET_GMII_DATA_GD_SHIFT) & ENET_GMII_DATA_GD_MASK)
#define ENET_GMII_DATA_GD_GET(x) (((uint32_t)(x) & ENET_GMII_DATA_GD_MASK) >> ENET_GMII_DATA_GD_SHIFT)

/* Bitfield definition for register: FLOWCTRL */
/*
 * PT (RW)
 *
 * Pause Time
 *  This field holds the value to be used in the Pause Time field in the transmit control frame.
 * If the Pause Time bits is configured to be double-synchronized to the (G)MII clock domain,
 *  then consecutive writes to this register should be performed only after at least four clock cycles in the destination clock domain.
 */
#define ENET_FLOWCTRL_PT_MASK (0xFFFF0000UL)
#define ENET_FLOWCTRL_PT_SHIFT (16U)
#define ENET_FLOWCTRL_PT_SET(x) (((uint32_t)(x) << ENET_FLOWCTRL_PT_SHIFT) & ENET_FLOWCTRL_PT_MASK)
#define ENET_FLOWCTRL_PT_GET(x) (((uint32_t)(x) & ENET_FLOWCTRL_PT_MASK) >> ENET_FLOWCTRL_PT_SHIFT)

/*
 * DZPQ (RW)
 *
 * Disable Zero-Quanta Pause
 *  When this bit is set, it disables the automatic generation of the Zero-Quanta Pause frames on the de-assertion of
 * the flow-control signal from the FIFO layer (MTL or external sideband flow control signal sbd_flowctrl_i/mti_flowctrl_i).
 * When this bit is reset, normal operation with automatic Zero-Quanta Pause frame generation is enabled.
 */
#define ENET_FLOWCTRL_DZPQ_MASK (0x80U)
#define ENET_FLOWCTRL_DZPQ_SHIFT (7U)
#define ENET_FLOWCTRL_DZPQ_SET(x) (((uint32_t)(x) << ENET_FLOWCTRL_DZPQ_SHIFT) & ENET_FLOWCTRL_DZPQ_MASK)
#define ENET_FLOWCTRL_DZPQ_GET(x) (((uint32_t)(x) & ENET_FLOWCTRL_DZPQ_MASK) >> ENET_FLOWCTRL_DZPQ_SHIFT)

/*
 * PLT (RW)
 *
 * Pause Low Threshold
 *  This field configures the threshold of the Pause timer at which the input flow control signal mti_flowctrl_i (or sbd_flowctrl_i) is checked for automatic retransmission of the Pause frame.
 * The threshold values should be always less than the Pause Time configured in Bits[31:16].
 *  For example, if PT = 100H (256 slot-times), and PLT = 01,
 * then a second Pause frame is automatically transmitted if the mti_flowctrl_i signal is asserted at 228 (256 – 28) slot times after the first Pause frame is transmitted.
 * The following list provides the threshold values for different values:
 * - 00: The threshold is Pause time minus 4 slot times (PT – 4 slot times).
 * - 01: The threshold is Pause time minus 28 slot times (PT – 28 slot times).
 * - 10: The threshold is Pause time minus 144 slot times (PT – 144 slot times).
 * - 11: The threshold is Pause time minus 256 slot times (PT – 256 slot times). The slot time is defined as the time taken to transmit 512 bits (64 bytes) on the GMII or MII interface.
 */
#define ENET_FLOWCTRL_PLT_MASK (0x30U)
#define ENET_FLOWCTRL_PLT_SHIFT (4U)
#define ENET_FLOWCTRL_PLT_SET(x) (((uint32_t)(x) << ENET_FLOWCTRL_PLT_SHIFT) & ENET_FLOWCTRL_PLT_MASK)
#define ENET_FLOWCTRL_PLT_GET(x) (((uint32_t)(x) & ENET_FLOWCTRL_PLT_MASK) >> ENET_FLOWCTRL_PLT_SHIFT)

/*
 * UP (RW)
 *
 * Unicast Pause Frame Detect A pause frame is processed when it has the unique multicast address specified in the IEEE Std 802.3.
 * When this bit is set, the MAC can also detect Pause frames with unicast address of the station.
 * This unicast address should be as specified in the MAC Address0 High Register and MAC Address0 Low Register.
 * When this bit is reset, the MAC only detects Pause frames with unique multicast address.
 */
#define ENET_FLOWCTRL_UP_MASK (0x8U)
#define ENET_FLOWCTRL_UP_SHIFT (3U)
#define ENET_FLOWCTRL_UP_SET(x) (((uint32_t)(x) << ENET_FLOWCTRL_UP_SHIFT) & ENET_FLOWCTRL_UP_MASK)
#define ENET_FLOWCTRL_UP_GET(x) (((uint32_t)(x) & ENET_FLOWCTRL_UP_MASK) >> ENET_FLOWCTRL_UP_SHIFT)

/*
 * RFE (RW)
 *
 * Receive Flow Control Enable
 *  When this bit is set, the MAC decodes the received Pause frame and disables its transmitter for a specified (Pause) time. When this bit is reset, the decode function of the Pause frame is disabled.
 */
#define ENET_FLOWCTRL_RFE_MASK (0x4U)
#define ENET_FLOWCTRL_RFE_SHIFT (2U)
#define ENET_FLOWCTRL_RFE_SET(x) (((uint32_t)(x) << ENET_FLOWCTRL_RFE_SHIFT) & ENET_FLOWCTRL_RFE_MASK)
#define ENET_FLOWCTRL_RFE_GET(x) (((uint32_t)(x) & ENET_FLOWCTRL_RFE_MASK) >> ENET_FLOWCTRL_RFE_SHIFT)

/*
 * TFE (RW)
 *
 * Transmit Flow Control Enable
 * In the full-duplex mode, when this bit is set, the MAC enables the flow control operation to transmit Pause frames.
 * When this bit is reset, the flow control operation in the MAC is disabled, and the MAC does not transmit any Pause frames.
 * In the half-duplex mode, when this bit is set, the MAC enables the backpressure operation. When this bit is reset, the backpressure feature is disabled.
 */
#define ENET_FLOWCTRL_TFE_MASK (0x2U)
#define ENET_FLOWCTRL_TFE_SHIFT (1U)
#define ENET_FLOWCTRL_TFE_SET(x) (((uint32_t)(x) << ENET_FLOWCTRL_TFE_SHIFT) & ENET_FLOWCTRL_TFE_MASK)
#define ENET_FLOWCTRL_TFE_GET(x) (((uint32_t)(x) & ENET_FLOWCTRL_TFE_MASK) >> ENET_FLOWCTRL_TFE_SHIFT)

/*
 * FCB_BPA (RW)
 *
 * Flow Control Busy or Backpressure Activate
 *  This bit initiates a Pause frame in the full-duplex mode and activates the backpressure function in the half-duplex mode if the TFE bit is set.
 * In the full-duplex mode, this bit should be read as 1'b0 before writing to the Flow Control register.
 *  To initiate a Pause frame, the Application must set this bit to 1'b1.
 * During a transfer of the Control Frame, this bit continues to be set to signify that a frame transmission is in progress.
 * After the completion of Pause frame transmission, the MAC resets this bit to 1'b0.
 * The Flow Control register should not be written to until this bit is cleared. In the half-duplex mode,
 * when this bit is set (and TFE is set), then backpressure is asserted by the MAC.
 * During backpressure, when the MAC receives a new frame, the transmitter starts sending a JAM pattern resulting in a collision.
 * This control register bit is logically ORed with the mti_flowctrl_i input signal for the backpressure function.
 * When the MAC is configured for the full-duplex mode, the BPA is automatically disabled.
 */
#define ENET_FLOWCTRL_FCB_BPA_MASK (0x1U)
#define ENET_FLOWCTRL_FCB_BPA_SHIFT (0U)
#define ENET_FLOWCTRL_FCB_BPA_SET(x) (((uint32_t)(x) << ENET_FLOWCTRL_FCB_BPA_SHIFT) & ENET_FLOWCTRL_FCB_BPA_MASK)
#define ENET_FLOWCTRL_FCB_BPA_GET(x) (((uint32_t)(x) & ENET_FLOWCTRL_FCB_BPA_MASK) >> ENET_FLOWCTRL_FCB_BPA_SHIFT)

/* Bitfield definition for register: VLAN_TAG */
/*
 * VTHM (RW)
 *
 * VLAN Tag Hash Table Match Enable
 *  When set, the most significant four bits of the VLAN tag’s CRC are used to index the content of Register 354 (VLAN Hash Table Register).
 * A value of 1 in the VLAN Hash Table register, corresponding to the index, indicates that the frame matched the VLAN hash table.
 * When Bit 16 (ETV) is set, the CRC of the 12-bit VLAN Identifier (VID) is used for comparison whereas when ETV is reset,
 * the CRC of the 16-bit VLAN tag is used for comparison. When reset, the VLAN Hash Match operation is not performed.
 */
#define ENET_VLAN_TAG_VTHM_MASK (0x80000UL)
#define ENET_VLAN_TAG_VTHM_SHIFT (19U)
#define ENET_VLAN_TAG_VTHM_SET(x) (((uint32_t)(x) << ENET_VLAN_TAG_VTHM_SHIFT) & ENET_VLAN_TAG_VTHM_MASK)
#define ENET_VLAN_TAG_VTHM_GET(x) (((uint32_t)(x) & ENET_VLAN_TAG_VTHM_MASK) >> ENET_VLAN_TAG_VTHM_SHIFT)

/*
 * ESVL (RW)
 *
 * Enable S-VLAN
 *  When this bit is set, the MAC transmitter and receiver also consider the S-VLAN (Type = 0x88A8) frames as valid VLAN tagged frames.
 */
#define ENET_VLAN_TAG_ESVL_MASK (0x40000UL)
#define ENET_VLAN_TAG_ESVL_SHIFT (18U)
#define ENET_VLAN_TAG_ESVL_SET(x) (((uint32_t)(x) << ENET_VLAN_TAG_ESVL_SHIFT) & ENET_VLAN_TAG_ESVL_MASK)
#define ENET_VLAN_TAG_ESVL_GET(x) (((uint32_t)(x) & ENET_VLAN_TAG_ESVL_MASK) >> ENET_VLAN_TAG_ESVL_SHIFT)

/*
 * VTIM (RW)
 *
 * VLAN Tag Inverse Match Enable
 * When set, this bit enables the VLAN Tag inverse matching. The frames that do not have matching VLAN Tag are marked as matched. When reset, this bit enables the VLAN Tag perfect matching.
 *  The frames with matched VLAN Tag are marked as matched.
 */
#define ENET_VLAN_TAG_VTIM_MASK (0x20000UL)
#define ENET_VLAN_TAG_VTIM_SHIFT (17U)
#define ENET_VLAN_TAG_VTIM_SET(x) (((uint32_t)(x) << ENET_VLAN_TAG_VTIM_SHIFT) & ENET_VLAN_TAG_VTIM_MASK)
#define ENET_VLAN_TAG_VTIM_GET(x) (((uint32_t)(x) & ENET_VLAN_TAG_VTIM_MASK) >> ENET_VLAN_TAG_VTIM_SHIFT)

/*
 * ETV (RW)
 *
 * Enable 12-Bit VLAN Tag Comparison
 *  When this bit is set, a 12-bit VLAN identifier is used for comparing and filtering instead of the complete 16-bit VLAN tag.
 *  Bits [11:0] of VLAN tag are compared with the corresponding field in the received VLAN-tagged frame. Similarly, when enabled,
 * only 12 bits of the VLAN tag in the received frame are used for hash-based VLAN filtering.
 * When this bit is reset, all 16 bits of the 15th and 16th bytes of the received VLAN frame are used for comparison and VLAN hash filtering.
 */
#define ENET_VLAN_TAG_ETV_MASK (0x10000UL)
#define ENET_VLAN_TAG_ETV_SHIFT (16U)
#define ENET_VLAN_TAG_ETV_SET(x) (((uint32_t)(x) << ENET_VLAN_TAG_ETV_SHIFT) & ENET_VLAN_TAG_ETV_MASK)
#define ENET_VLAN_TAG_ETV_GET(x) (((uint32_t)(x) & ENET_VLAN_TAG_ETV_MASK) >> ENET_VLAN_TAG_ETV_SHIFT)

/*
 * VL (RW)
 *
 * VLAN Tag Identifier for Receive Frames
 *  This field contains the 802.1Q VLAN tag to identify the VLAN frames and is compared to the 15th and 16th bytes of the frames being received for VLAN frames.
 * The following list describes the bits of this field:
 *  - Bits [15:13]: User Priority
 * - Bit 12: Canonical Format Indicator (CFI) or Drop Eligible Indicator (DEI)
 * - Bits[11:0]: VLAN tag’s VLAN Identifier (VID) field When the ETV bit is set, only the VID (Bits[11:0]) is used for comparison.
 *    If VL (VL[11:0] if ETV is set) is all zeros, the MAC does not check the fifteenth and 16th bytes for VLAN tag comparison,
 *   and declares all frames with a Type field value of 0x8100 or 0x88a8 as VLAN frames.
 */
#define ENET_VLAN_TAG_VL_MASK (0xFFFFU)
#define ENET_VLAN_TAG_VL_SHIFT (0U)
#define ENET_VLAN_TAG_VL_SET(x) (((uint32_t)(x) << ENET_VLAN_TAG_VL_SHIFT) & ENET_VLAN_TAG_VL_MASK)
#define ENET_VLAN_TAG_VL_GET(x) (((uint32_t)(x) & ENET_VLAN_TAG_VL_MASK) >> ENET_VLAN_TAG_VL_SHIFT)

/* Bitfield definition for register: RWKFRMFILT */
/*
 * WKUPFRMFILT (RW)
 *
 * This is the address through which the application writes or reads the remote wake-up frame filter registers (wkupfmfilter_reg).
 * The wkupfmfilter_reg register is a pointer to eight wkupfmfilter_reg registers.
 * The wkupfmfilter_reg register is loaded by sequentially loading the eight register values.
 * Eight sequential writes to this address (0x0028) write all wkupfmfilter_reg registers.
 *  Similarly, eight sequential reads from this address (0x0028) read all wkupfmfilter_reg registers
 */
#define ENET_RWKFRMFILT_WKUPFRMFILT_MASK (0xFFFFFFFFUL)
#define ENET_RWKFRMFILT_WKUPFRMFILT_SHIFT (0U)
#define ENET_RWKFRMFILT_WKUPFRMFILT_SET(x) (((uint32_t)(x) << ENET_RWKFRMFILT_WKUPFRMFILT_SHIFT) & ENET_RWKFRMFILT_WKUPFRMFILT_MASK)
#define ENET_RWKFRMFILT_WKUPFRMFILT_GET(x) (((uint32_t)(x) & ENET_RWKFRMFILT_WKUPFRMFILT_MASK) >> ENET_RWKFRMFILT_WKUPFRMFILT_SHIFT)

/* Bitfield definition for register: PMT_CSR */
/*
 * RWKFILTRST (RW)
 *
 * Remote Wake-Up Frame Filter Register Pointer Reset
 * When this bit is set, it resets the remote wake-up frame filter register pointer to 3’b000. It is automatically cleared after 1 clock cycle.
 */
#define ENET_PMT_CSR_RWKFILTRST_MASK (0x80000000UL)
#define ENET_PMT_CSR_RWKFILTRST_SHIFT (31U)
#define ENET_PMT_CSR_RWKFILTRST_SET(x) (((uint32_t)(x) << ENET_PMT_CSR_RWKFILTRST_SHIFT) & ENET_PMT_CSR_RWKFILTRST_MASK)
#define ENET_PMT_CSR_RWKFILTRST_GET(x) (((uint32_t)(x) & ENET_PMT_CSR_RWKFILTRST_MASK) >> ENET_PMT_CSR_RWKFILTRST_SHIFT)

/*
 * RWKPTR (RW)
 *
 * Remote Wake-up FIFO Pointer
 * This field gives the current value (0 to 31) of the Remote Wake-up Frame filter register pointer. When the value of this pointer is equal to 7, 15, 23 or 31,
 * the contents of the Remote Wake-up Frame Filter Register are transferred to the clk_rx_i domain when a write occurs to that register.
 *  The maximum value of the pointer is 7, 15, 23 and 31 respectively depending on the number of Remote Wakeup Filters selected during configuration.
 */
#define ENET_PMT_CSR_RWKPTR_MASK (0x1F000000UL)
#define ENET_PMT_CSR_RWKPTR_SHIFT (24U)
#define ENET_PMT_CSR_RWKPTR_SET(x) (((uint32_t)(x) << ENET_PMT_CSR_RWKPTR_SHIFT) & ENET_PMT_CSR_RWKPTR_MASK)
#define ENET_PMT_CSR_RWKPTR_GET(x) (((uint32_t)(x) & ENET_PMT_CSR_RWKPTR_MASK) >> ENET_PMT_CSR_RWKPTR_SHIFT)

/*
 * GLBLUCAST (RW)
 *
 * Global Unicast
 * When set, enables any unicast packet filtered by the MAC (DAF) address recognition to be a remote wake-up frame.
 */
#define ENET_PMT_CSR_GLBLUCAST_MASK (0x200U)
#define ENET_PMT_CSR_GLBLUCAST_SHIFT (9U)
#define ENET_PMT_CSR_GLBLUCAST_SET(x) (((uint32_t)(x) << ENET_PMT_CSR_GLBLUCAST_SHIFT) & ENET_PMT_CSR_GLBLUCAST_MASK)
#define ENET_PMT_CSR_GLBLUCAST_GET(x) (((uint32_t)(x) & ENET_PMT_CSR_GLBLUCAST_MASK) >> ENET_PMT_CSR_GLBLUCAST_SHIFT)

/*
 * RWKPRCVD (RW)
 *
 * Remote Wake-Up Frame Received
 * When set, this bit indicates the power management event is generated because of the reception of a remote wake-up frame. This bit is cleared by a Read into this register.
 */
#define ENET_PMT_CSR_RWKPRCVD_MASK (0x40U)
#define ENET_PMT_CSR_RWKPRCVD_SHIFT (6U)
#define ENET_PMT_CSR_RWKPRCVD_SET(x) (((uint32_t)(x) << ENET_PMT_CSR_RWKPRCVD_SHIFT) & ENET_PMT_CSR_RWKPRCVD_MASK)
#define ENET_PMT_CSR_RWKPRCVD_GET(x) (((uint32_t)(x) & ENET_PMT_CSR_RWKPRCVD_MASK) >> ENET_PMT_CSR_RWKPRCVD_SHIFT)

/*
 * MGKPRCVD (RW)
 *
 * Magic Packet Received
 * When set, this bit indicates that the power management event is generated because of the reception of a magic packet. This bit is cleared by a Read into this register.
 */
#define ENET_PMT_CSR_MGKPRCVD_MASK (0x20U)
#define ENET_PMT_CSR_MGKPRCVD_SHIFT (5U)
#define ENET_PMT_CSR_MGKPRCVD_SET(x) (((uint32_t)(x) << ENET_PMT_CSR_MGKPRCVD_SHIFT) & ENET_PMT_CSR_MGKPRCVD_MASK)
#define ENET_PMT_CSR_MGKPRCVD_GET(x) (((uint32_t)(x) & ENET_PMT_CSR_MGKPRCVD_MASK) >> ENET_PMT_CSR_MGKPRCVD_SHIFT)

/*
 * RWKPKTEN (RW)
 *
 * Remote Wake-Up Frame Enable
 * When set, enables generation of a power management event because of remote wake-up frame reception.
 */
#define ENET_PMT_CSR_RWKPKTEN_MASK (0x4U)
#define ENET_PMT_CSR_RWKPKTEN_SHIFT (2U)
#define ENET_PMT_CSR_RWKPKTEN_SET(x) (((uint32_t)(x) << ENET_PMT_CSR_RWKPKTEN_SHIFT) & ENET_PMT_CSR_RWKPKTEN_MASK)
#define ENET_PMT_CSR_RWKPKTEN_GET(x) (((uint32_t)(x) & ENET_PMT_CSR_RWKPKTEN_MASK) >> ENET_PMT_CSR_RWKPKTEN_SHIFT)

/*
 * MGKPKTEN (RW)
 *
 * Magic Packet Enable
 * When set, enables generation of a power management event because of magic packet reception.
 */
#define ENET_PMT_CSR_MGKPKTEN_MASK (0x2U)
#define ENET_PMT_CSR_MGKPKTEN_SHIFT (1U)
#define ENET_PMT_CSR_MGKPKTEN_SET(x) (((uint32_t)(x) << ENET_PMT_CSR_MGKPKTEN_SHIFT) & ENET_PMT_CSR_MGKPKTEN_MASK)
#define ENET_PMT_CSR_MGKPKTEN_GET(x) (((uint32_t)(x) & ENET_PMT_CSR_MGKPKTEN_MASK) >> ENET_PMT_CSR_MGKPKTEN_SHIFT)

/*
 * PWRDWN (RW)
 *
 * Power Down
 * When set, the MAC receiver drops all received frames until it receives the expected magic packet or remote wake-up frame.
 * This bit is then self-cleared and the power-down mode is disabled.
 * The Software can also clear this bit before the expected magic packet or remote wake-up frame is received.
 * The frames, received by the MAC after this bit is cleared, are forwarded to the application.
 * This bit must only be set when the Magic Packet Enable, Global Unicast, or Remote Wake-Upr Fame Enable bit is set high.
 * Note: You can gate-off the CSR clock during the power-down mode.
 * However, when the CSR clock is gated-off, you cannot perform any read or write operations on this register. Therefore, the Software cannot clear this bit.
 */
#define ENET_PMT_CSR_PWRDWN_MASK (0x1U)
#define ENET_PMT_CSR_PWRDWN_SHIFT (0U)
#define ENET_PMT_CSR_PWRDWN_SET(x) (((uint32_t)(x) << ENET_PMT_CSR_PWRDWN_SHIFT) & ENET_PMT_CSR_PWRDWN_MASK)
#define ENET_PMT_CSR_PWRDWN_GET(x) (((uint32_t)(x) & ENET_PMT_CSR_PWRDWN_MASK) >> ENET_PMT_CSR_PWRDWN_SHIFT)

/* Bitfield definition for register: LPI_CSR */
/*
 * LPITXA (RW)
 *
 * LPI TX Automate
 * This bit controls the behavior of the MAC when it is entering or coming out of the LPI mode on the transmit side.
 * This bit is not functional in the GMAC-CORE configuration in which the Tx clock gating is done during the LPI mode. If the LPITXA and LPIEN bits are set to 1,
 * the MAC enters the LPI mode only after all outstanding frames (in the core) and pending frames (in the application interface) have been transmitted.
 * The MAC comes out of the LPI mode when the application sends any frame for transmission or the application issues a TX FIFO Flush command.
 *  In addition, the MAC automatically clears the LPIEN bit when it exits the LPI state.
 * If TX FIFO Flush is set in Bit 20 of Register 6 (Operation Mode Register),
 * when the MAC is in the LPI mode, the MAC exits the LPI mode.
 * When this bit is 0, the LPIEN bit directly controls behavior of the MAC when it is entering or coming out of the LPI mode.
 */
#define ENET_LPI_CSR_LPITXA_MASK (0x80000UL)
#define ENET_LPI_CSR_LPITXA_SHIFT (19U)
#define ENET_LPI_CSR_LPITXA_SET(x) (((uint32_t)(x) << ENET_LPI_CSR_LPITXA_SHIFT) & ENET_LPI_CSR_LPITXA_MASK)
#define ENET_LPI_CSR_LPITXA_GET(x) (((uint32_t)(x) & ENET_LPI_CSR_LPITXA_MASK) >> ENET_LPI_CSR_LPITXA_SHIFT)

/*
 * PLSEN (RW)
 *
 * PHY Link Status Enable
 * This bit enables the link status received on the RGMII, SGMII, or SMII receive paths to be used for activating the LPI LS TIMER.
 * When set, the MAC uses the link-status bits of Register 54 (SGMII/RGMII/SMII Control and Status Register) and Bit 17 (PLS) for the LPI LS Timer trigger.
 *  When cleared, the MAC ignores the link-status bits of Register 54 and takes only the PLS bit. This bit is RO and reserved if you have not selected the RGMII, SGMII, or SMII PHY interface.
 */
#define ENET_LPI_CSR_PLSEN_MASK (0x40000UL)
#define ENET_LPI_CSR_PLSEN_SHIFT (18U)
#define ENET_LPI_CSR_PLSEN_SET(x) (((uint32_t)(x) << ENET_LPI_CSR_PLSEN_SHIFT) & ENET_LPI_CSR_PLSEN_MASK)
#define ENET_LPI_CSR_PLSEN_GET(x) (((uint32_t)(x) & ENET_LPI_CSR_PLSEN_MASK) >> ENET_LPI_CSR_PLSEN_SHIFT)

/*
 * PLS (RW)
 *
 * PHY Link Status
 * This bit indicates the link status of the PHY. The MAC Transmitter asserts the LPI pattern only when the link status is up (okay) at least for the time indicated by the LPI LS TIMER.
 * When set, the link is considered to be okay (up) and when reset, the link is considered to be down.
 */
#define ENET_LPI_CSR_PLS_MASK (0x20000UL)
#define ENET_LPI_CSR_PLS_SHIFT (17U)
#define ENET_LPI_CSR_PLS_SET(x) (((uint32_t)(x) << ENET_LPI_CSR_PLS_SHIFT) & ENET_LPI_CSR_PLS_MASK)
#define ENET_LPI_CSR_PLS_GET(x) (((uint32_t)(x) & ENET_LPI_CSR_PLS_MASK) >> ENET_LPI_CSR_PLS_SHIFT)

/*
 * LPIEN (RW)
 *
 * LPI Enable
 * When set, this bit instructs the MAC Transmitter to enter the LPI state. When reset, this bit instructs the MAC to exit the LPI state and resume normal transmission.
 * This bit is cleared when the LPITXA bit is set and the MAC exits the LPI state because of the arrival of a new packet for transmission.
 */
#define ENET_LPI_CSR_LPIEN_MASK (0x10000UL)
#define ENET_LPI_CSR_LPIEN_SHIFT (16U)
#define ENET_LPI_CSR_LPIEN_SET(x) (((uint32_t)(x) << ENET_LPI_CSR_LPIEN_SHIFT) & ENET_LPI_CSR_LPIEN_MASK)
#define ENET_LPI_CSR_LPIEN_GET(x) (((uint32_t)(x) & ENET_LPI_CSR_LPIEN_MASK) >> ENET_LPI_CSR_LPIEN_SHIFT)

/*
 * RLPIST (RW)
 *
 * Receive LPI State
 * When set, this bit indicates that the MAC is receiving the LPI pattern on the GMII or MII interface.
 */
#define ENET_LPI_CSR_RLPIST_MASK (0x200U)
#define ENET_LPI_CSR_RLPIST_SHIFT (9U)
#define ENET_LPI_CSR_RLPIST_SET(x) (((uint32_t)(x) << ENET_LPI_CSR_RLPIST_SHIFT) & ENET_LPI_CSR_RLPIST_MASK)
#define ENET_LPI_CSR_RLPIST_GET(x) (((uint32_t)(x) & ENET_LPI_CSR_RLPIST_MASK) >> ENET_LPI_CSR_RLPIST_SHIFT)

/*
 * TLPIST (RW)
 *
 * Transmit LPI State
 * When set, this bit indicates that the MAC is transmitting the LPI pattern on the GMII or MII interface.
 */
#define ENET_LPI_CSR_TLPIST_MASK (0x100U)
#define ENET_LPI_CSR_TLPIST_SHIFT (8U)
#define ENET_LPI_CSR_TLPIST_SET(x) (((uint32_t)(x) << ENET_LPI_CSR_TLPIST_SHIFT) & ENET_LPI_CSR_TLPIST_MASK)
#define ENET_LPI_CSR_TLPIST_GET(x) (((uint32_t)(x) & ENET_LPI_CSR_TLPIST_MASK) >> ENET_LPI_CSR_TLPIST_SHIFT)

/*
 * RLPIEX (RW)
 *
 * Receive LPI Exit
 * When set, this bit indicates that the MAC Receiver has stopped receiving the LPI pattern on the GMII or MII interface, exited the LPI state, and resumed the normal reception.
 * This bit is cleared by a read into this register.
 * Note: This bit may not get set if the MAC stops receiving the LPI pattern for a very short duration, such as, less than 3 clock cycles of CSR clock.
 */
#define ENET_LPI_CSR_RLPIEX_MASK (0x8U)
#define ENET_LPI_CSR_RLPIEX_SHIFT (3U)
#define ENET_LPI_CSR_RLPIEX_SET(x) (((uint32_t)(x) << ENET_LPI_CSR_RLPIEX_SHIFT) & ENET_LPI_CSR_RLPIEX_MASK)
#define ENET_LPI_CSR_RLPIEX_GET(x) (((uint32_t)(x) & ENET_LPI_CSR_RLPIEX_MASK) >> ENET_LPI_CSR_RLPIEX_SHIFT)

/*
 * RLPIEN (RW)
 *
 * Receive LPI Entry
 * When set, this bit indicates that the MAC Receiver has received an LPI pattern and entered the LPI state. This bit is cleared by a read into this register.
 * Note: This bit may not get set if the MAC stops receiving the LPI pattern for a very short duration, such as, less than 3 clock cycles of CSR clock.
 */
#define ENET_LPI_CSR_RLPIEN_MASK (0x4U)
#define ENET_LPI_CSR_RLPIEN_SHIFT (2U)
#define ENET_LPI_CSR_RLPIEN_SET(x) (((uint32_t)(x) << ENET_LPI_CSR_RLPIEN_SHIFT) & ENET_LPI_CSR_RLPIEN_MASK)
#define ENET_LPI_CSR_RLPIEN_GET(x) (((uint32_t)(x) & ENET_LPI_CSR_RLPIEN_MASK) >> ENET_LPI_CSR_RLPIEN_SHIFT)

/*
 * TLPIEX (RW)
 *
 * Transmit LPI Exit
 * When set, this bit indicates that the MAC transmitter has exited the LPI state after the user has cleared the LPIEN bit and the LPI TW Timer has expired. This bit is cleared by a read into this register.
 */
#define ENET_LPI_CSR_TLPIEX_MASK (0x2U)
#define ENET_LPI_CSR_TLPIEX_SHIFT (1U)
#define ENET_LPI_CSR_TLPIEX_SET(x) (((uint32_t)(x) << ENET_LPI_CSR_TLPIEX_SHIFT) & ENET_LPI_CSR_TLPIEX_MASK)
#define ENET_LPI_CSR_TLPIEX_GET(x) (((uint32_t)(x) & ENET_LPI_CSR_TLPIEX_MASK) >> ENET_LPI_CSR_TLPIEX_SHIFT)

/*
 * TLPIEN (RW)
 *
 * Transmit LPI Entry
 *  When set, this bit indicates that the MAC Transmitter has entered the LPI state because of the setting of the LPIEN bit. This bit is cleared by a read into this register.
 */
#define ENET_LPI_CSR_TLPIEN_MASK (0x1U)
#define ENET_LPI_CSR_TLPIEN_SHIFT (0U)
#define ENET_LPI_CSR_TLPIEN_SET(x) (((uint32_t)(x) << ENET_LPI_CSR_TLPIEN_SHIFT) & ENET_LPI_CSR_TLPIEN_MASK)
#define ENET_LPI_CSR_TLPIEN_GET(x) (((uint32_t)(x) & ENET_LPI_CSR_TLPIEN_MASK) >> ENET_LPI_CSR_TLPIEN_SHIFT)

/* Bitfield definition for register: LPI_TCR */
/*
 * LST (RW)
 *
 * LPI LS TIMER
 * This field specifies the minimum time (in milliseconds) for which the link status from the PHY should be up (OKAY) before the LPI pattern can be transmitted to the PHY.
 *  The MAC does not transmit the LPI pattern even when the LPIEN bit is set unless the LPI LS Timer reaches the programmed terminal count.
 * The default value of the LPI LS Timer is 1000 (1 sec) as defined in the IEEE standard.
 */
#define ENET_LPI_TCR_LST_MASK (0x3FF0000UL)
#define ENET_LPI_TCR_LST_SHIFT (16U)
#define ENET_LPI_TCR_LST_SET(x) (((uint32_t)(x) << ENET_LPI_TCR_LST_SHIFT) & ENET_LPI_TCR_LST_MASK)
#define ENET_LPI_TCR_LST_GET(x) (((uint32_t)(x) & ENET_LPI_TCR_LST_MASK) >> ENET_LPI_TCR_LST_SHIFT)

/*
 * TWT (RW)
 *
 * LPI TW TIMER
 * This field specifies the minimum time (in microseconds) for which the MAC waits after it stops transmitting
 *  the LPI pattern to the PHY and before it resumes the normal transmission.
 * The TLPIEX status bit is set after the expiry of this timer.
 */
#define ENET_LPI_TCR_TWT_MASK (0xFFFFU)
#define ENET_LPI_TCR_TWT_SHIFT (0U)
#define ENET_LPI_TCR_TWT_SET(x) (((uint32_t)(x) << ENET_LPI_TCR_TWT_SHIFT) & ENET_LPI_TCR_TWT_MASK)
#define ENET_LPI_TCR_TWT_GET(x) (((uint32_t)(x) & ENET_LPI_TCR_TWT_MASK) >> ENET_LPI_TCR_TWT_SHIFT)

/* Bitfield definition for register: INTR_STATUS */
/*
 * GPIIS (RO)
 *
 * GPI Interrupt Status
 * When the GPIO feature is enabled, this bit is set when any active event (LL or LH) occurs on the GPIS field (Bits [3:0])
 *  of Register 56 (General Purpose IO Register) and the corresponding GPIE bit is enabled.
 * This bit is cleared on reading lane 0 (GPIS) of Register 56 (General Purpose IO Register).
 *  When the GPIO feature is not enabled, this bit is reserved.
 */
#define ENET_INTR_STATUS_GPIIS_MASK (0x800U)
#define ENET_INTR_STATUS_GPIIS_SHIFT (11U)
#define ENET_INTR_STATUS_GPIIS_GET(x) (((uint32_t)(x) & ENET_INTR_STATUS_GPIIS_MASK) >> ENET_INTR_STATUS_GPIIS_SHIFT)

/*
 * LPIIS (RO)
 *
 * LPI Interrupt Status
 * When the Energy Efficient Ethernet feature is enabled, this bit is set for any LPI state entry or exit in the MAC Transmitter or Receiver.
 * This bit is cleared on reading Bit 0 of Register 12 (LPI Control and Status Register). In all other modes, this bit is reserved.
 */
#define ENET_INTR_STATUS_LPIIS_MASK (0x400U)
#define ENET_INTR_STATUS_LPIIS_SHIFT (10U)
#define ENET_INTR_STATUS_LPIIS_GET(x) (((uint32_t)(x) & ENET_INTR_STATUS_LPIIS_MASK) >> ENET_INTR_STATUS_LPIIS_SHIFT)

/*
 * TSIS (RO)
 *
 * Timestamp Interrupt Status
 * When the Advanced Timestamp feature is enabled, this bit is set when any of the following conditions is true:
 * - The system time value equals or exceeds the value specified in the Target Time High and Low registers.
 * - There is an overflow in the seconds register.
 *  - The Auxiliary snapshot trigger is asserted. This bit is cleared on reading Bit 0 of Register 458 (Timestamp Status Register).
 */
#define ENET_INTR_STATUS_TSIS_MASK (0x200U)
#define ENET_INTR_STATUS_TSIS_SHIFT (9U)
#define ENET_INTR_STATUS_TSIS_GET(x) (((uint32_t)(x) & ENET_INTR_STATUS_TSIS_MASK) >> ENET_INTR_STATUS_TSIS_SHIFT)

/*
 * MMCRXIPIS (RO)
 *
 * MMC Receive Checksum Offload Interrupt Status
 * This bit is set high when an interrupt is generated in the MMC Receive Checksum Offload Interrupt Register. This bit is cleared when all the bits in this interrupt register are cleared.
 */
#define ENET_INTR_STATUS_MMCRXIPIS_MASK (0x80U)
#define ENET_INTR_STATUS_MMCRXIPIS_SHIFT (7U)
#define ENET_INTR_STATUS_MMCRXIPIS_GET(x) (((uint32_t)(x) & ENET_INTR_STATUS_MMCRXIPIS_MASK) >> ENET_INTR_STATUS_MMCRXIPIS_SHIFT)

/*
 * MMCTXIS (RO)
 *
 * MMC Transmit Interrupt Status
 * This bit is set high when an interrupt is generated in the MMC Transmit Interrupt Register. This bit is cleared when all the bits in this interrupt register are cleared.
 */
#define ENET_INTR_STATUS_MMCTXIS_MASK (0x40U)
#define ENET_INTR_STATUS_MMCTXIS_SHIFT (6U)
#define ENET_INTR_STATUS_MMCTXIS_GET(x) (((uint32_t)(x) & ENET_INTR_STATUS_MMCTXIS_MASK) >> ENET_INTR_STATUS_MMCTXIS_SHIFT)

/*
 * MMCRXIS (RO)
 *
 * MMC Receive Interrupt Status
 * This bit is set high when an interrupt is generated in the MMC Receive Interrupt Register. This bit is cleared when all the bits in this interrupt register are cleared.
 */
#define ENET_INTR_STATUS_MMCRXIS_MASK (0x20U)
#define ENET_INTR_STATUS_MMCRXIS_SHIFT (5U)
#define ENET_INTR_STATUS_MMCRXIS_GET(x) (((uint32_t)(x) & ENET_INTR_STATUS_MMCRXIS_MASK) >> ENET_INTR_STATUS_MMCRXIS_SHIFT)

/*
 * MMCIS (RO)
 *
 * MMC Interrupt Status
 * This bit is set high when any of the Bits [7:5] is set high and cleared only when all of these bits are low.
 */
#define ENET_INTR_STATUS_MMCIS_MASK (0x10U)
#define ENET_INTR_STATUS_MMCIS_SHIFT (4U)
#define ENET_INTR_STATUS_MMCIS_GET(x) (((uint32_t)(x) & ENET_INTR_STATUS_MMCIS_MASK) >> ENET_INTR_STATUS_MMCIS_SHIFT)

/*
 * PMTIS (RO)
 *
 * PMT Interrupt Status
 * This bit is set when a magic packet or remote wake-up frame is received in the power-down mode (see Bits 5 and 6 in the PMT Control and Status Register).
 * This bit is cleared when both Bits[6:5] are cleared because of a read operation to the PMT Control and Status register.
 */
#define ENET_INTR_STATUS_PMTIS_MASK (0x8U)
#define ENET_INTR_STATUS_PMTIS_SHIFT (3U)
#define ENET_INTR_STATUS_PMTIS_GET(x) (((uint32_t)(x) & ENET_INTR_STATUS_PMTIS_MASK) >> ENET_INTR_STATUS_PMTIS_SHIFT)

/*
 * PCSANCIS (RO)
 *
 * PCS Auto-Negotiation Complete
 * This bit is set when the Auto-negotiation is completed in the TBI, RTBI, or SGMII PHY interface (Bit 5 in Register 49 (AN Status Register)).
 * This bit is cleared when you perform a read operation to the AN Status register.
 */
#define ENET_INTR_STATUS_PCSANCIS_MASK (0x4U)
#define ENET_INTR_STATUS_PCSANCIS_SHIFT (2U)
#define ENET_INTR_STATUS_PCSANCIS_GET(x) (((uint32_t)(x) & ENET_INTR_STATUS_PCSANCIS_MASK) >> ENET_INTR_STATUS_PCSANCIS_SHIFT)

/*
 * PCSLCHGIS (RO)
 *
 * PCS Link Status Changed
 * This bit is set because of any change in Link Status in the TBI, RTBI, or SGMII PHY interface (Bit 2 in Register 49 (AN Status Register)).
 * This bit is cleared when you perform a read operation on the AN Status register.
 */
#define ENET_INTR_STATUS_PCSLCHGIS_MASK (0x2U)
#define ENET_INTR_STATUS_PCSLCHGIS_SHIFT (1U)
#define ENET_INTR_STATUS_PCSLCHGIS_GET(x) (((uint32_t)(x) & ENET_INTR_STATUS_PCSLCHGIS_MASK) >> ENET_INTR_STATUS_PCSLCHGIS_SHIFT)

/*
 * RGSMIIIS (RO)
 *
 * RGMII or SMII Interrupt Status
 * This bit is set because of any change in value of the Link Status of RGMII or SMII interface (Bit 3 in Register 54 (SGMII/RGMII/SMII Control and Status Register)).
 * This bit is cleared when you perform a read operation on the SGMII/RGMII/SMII Control and Status Register.
 */
#define ENET_INTR_STATUS_RGSMIIIS_MASK (0x1U)
#define ENET_INTR_STATUS_RGSMIIIS_SHIFT (0U)
#define ENET_INTR_STATUS_RGSMIIIS_GET(x) (((uint32_t)(x) & ENET_INTR_STATUS_RGSMIIIS_MASK) >> ENET_INTR_STATUS_RGSMIIIS_SHIFT)

/* Bitfield definition for register: INTR_MASK */
/*
 * LPIIM (RW)
 *
 * LPI Interrupt Mask
 * When set, this bit disables the assertion of the interrupt signal because of the setting of the LPI Interrupt Status bit in Register 14 (Interrupt Status Register).
 */
#define ENET_INTR_MASK_LPIIM_MASK (0x400U)
#define ENET_INTR_MASK_LPIIM_SHIFT (10U)
#define ENET_INTR_MASK_LPIIM_SET(x) (((uint32_t)(x) << ENET_INTR_MASK_LPIIM_SHIFT) & ENET_INTR_MASK_LPIIM_MASK)
#define ENET_INTR_MASK_LPIIM_GET(x) (((uint32_t)(x) & ENET_INTR_MASK_LPIIM_MASK) >> ENET_INTR_MASK_LPIIM_SHIFT)

/*
 * TSIM (RW)
 *
 * Timestamp Interrupt Mask
 *  When set, this bit disables the assertion of the interrupt signal because of the setting of Timestamp Interrupt Status bit in Register 14 (Interrupt Status Register).
 */
#define ENET_INTR_MASK_TSIM_MASK (0x200U)
#define ENET_INTR_MASK_TSIM_SHIFT (9U)
#define ENET_INTR_MASK_TSIM_SET(x) (((uint32_t)(x) << ENET_INTR_MASK_TSIM_SHIFT) & ENET_INTR_MASK_TSIM_MASK)
#define ENET_INTR_MASK_TSIM_GET(x) (((uint32_t)(x) & ENET_INTR_MASK_TSIM_MASK) >> ENET_INTR_MASK_TSIM_SHIFT)

/*
 * PMTIM (RW)
 *
 * PMT Interrupt Mask
 *  When set, this bit disables the assertion of the interrupt signal because of the setting of PMT Interrupt Status bit in Register 14 (Interrupt Status Register).
 */
#define ENET_INTR_MASK_PMTIM_MASK (0x8U)
#define ENET_INTR_MASK_PMTIM_SHIFT (3U)
#define ENET_INTR_MASK_PMTIM_SET(x) (((uint32_t)(x) << ENET_INTR_MASK_PMTIM_SHIFT) & ENET_INTR_MASK_PMTIM_MASK)
#define ENET_INTR_MASK_PMTIM_GET(x) (((uint32_t)(x) & ENET_INTR_MASK_PMTIM_MASK) >> ENET_INTR_MASK_PMTIM_SHIFT)

/*
 * PCSANCIM (RW)
 *
 * PCS AN Completion Interrupt Mask
 * When set, this bit disables the assertion of the interrupt signal because of the setting of PCS Auto-negotiation complete bit in Register 14 (Interrupt Status Register).
 */
#define ENET_INTR_MASK_PCSANCIM_MASK (0x4U)
#define ENET_INTR_MASK_PCSANCIM_SHIFT (2U)
#define ENET_INTR_MASK_PCSANCIM_SET(x) (((uint32_t)(x) << ENET_INTR_MASK_PCSANCIM_SHIFT) & ENET_INTR_MASK_PCSANCIM_MASK)
#define ENET_INTR_MASK_PCSANCIM_GET(x) (((uint32_t)(x) & ENET_INTR_MASK_PCSANCIM_MASK) >> ENET_INTR_MASK_PCSANCIM_SHIFT)

/*
 * PCSLCHGIM (RW)
 *
 * PCS Link Status Interrupt Mask
 * When set, this bit disables the assertion of the interrupt signal because of the setting of the PCS Link-status changed bit in Register 14 (Interrupt Status Register).
 */
#define ENET_INTR_MASK_PCSLCHGIM_MASK (0x2U)
#define ENET_INTR_MASK_PCSLCHGIM_SHIFT (1U)
#define ENET_INTR_MASK_PCSLCHGIM_SET(x) (((uint32_t)(x) << ENET_INTR_MASK_PCSLCHGIM_SHIFT) & ENET_INTR_MASK_PCSLCHGIM_MASK)
#define ENET_INTR_MASK_PCSLCHGIM_GET(x) (((uint32_t)(x) & ENET_INTR_MASK_PCSLCHGIM_MASK) >> ENET_INTR_MASK_PCSLCHGIM_SHIFT)

/*
 * RGSMIIIM (RW)
 *
 * RGMII or SMII Interrupt Mask
 * When set, this bit disables the assertion of the interrupt signal because of the setting of the RGMII or SMII Interrupt Status bit in Register 14 (Interrupt Status Register).
 */
#define ENET_INTR_MASK_RGSMIIIM_MASK (0x1U)
#define ENET_INTR_MASK_RGSMIIIM_SHIFT (0U)
#define ENET_INTR_MASK_RGSMIIIM_SET(x) (((uint32_t)(x) << ENET_INTR_MASK_RGSMIIIM_SHIFT) & ENET_INTR_MASK_RGSMIIIM_MASK)
#define ENET_INTR_MASK_RGSMIIIM_GET(x) (((uint32_t)(x) & ENET_INTR_MASK_RGSMIIIM_MASK) >> ENET_INTR_MASK_RGSMIIIM_SHIFT)

/* Bitfield definition for register: MAC_ADDR_0_HIGH */
/*
 * AE (RO)
 *
 * Address Enable
 *  This bit is RO. The bit value is fixed at 1.
 */
#define ENET_MAC_ADDR_0_HIGH_AE_MASK (0x80000000UL)
#define ENET_MAC_ADDR_0_HIGH_AE_SHIFT (31U)
#define ENET_MAC_ADDR_0_HIGH_AE_GET(x) (((uint32_t)(x) & ENET_MAC_ADDR_0_HIGH_AE_MASK) >> ENET_MAC_ADDR_0_HIGH_AE_SHIFT)

/*
 * ADDRHI (RW)
 *
 * MAC Address0 [47:32]
 *  This field contains the upper 16 bits (47:32) of the first 6-byte MAC address. The MAC uses this field for filtering the received frames and inserting the MAC address in the Transmit Flow Control (Pause) Frames.
 */
#define ENET_MAC_ADDR_0_HIGH_ADDRHI_MASK (0xFFFFU)
#define ENET_MAC_ADDR_0_HIGH_ADDRHI_SHIFT (0U)
#define ENET_MAC_ADDR_0_HIGH_ADDRHI_SET(x) (((uint32_t)(x) << ENET_MAC_ADDR_0_HIGH_ADDRHI_SHIFT) & ENET_MAC_ADDR_0_HIGH_ADDRHI_MASK)
#define ENET_MAC_ADDR_0_HIGH_ADDRHI_GET(x) (((uint32_t)(x) & ENET_MAC_ADDR_0_HIGH_ADDRHI_MASK) >> ENET_MAC_ADDR_0_HIGH_ADDRHI_SHIFT)

/* Bitfield definition for register: MAC_ADDR_0_LOW */
/*
 * ADDRLO (RW)
 *
 * MAC Address0 [31:0]
 *  This field contains the lower 32 bits of the first 6-byte MAC address. This is used by the MAC for filtering the received frames and inserting the MAC address in the Transmit Flow Control (Pause) Frames.
 */
#define ENET_MAC_ADDR_0_LOW_ADDRLO_MASK (0xFFFFFFFFUL)
#define ENET_MAC_ADDR_0_LOW_ADDRLO_SHIFT (0U)
#define ENET_MAC_ADDR_0_LOW_ADDRLO_SET(x) (((uint32_t)(x) << ENET_MAC_ADDR_0_LOW_ADDRLO_SHIFT) & ENET_MAC_ADDR_0_LOW_ADDRLO_MASK)
#define ENET_MAC_ADDR_0_LOW_ADDRLO_GET(x) (((uint32_t)(x) & ENET_MAC_ADDR_0_LOW_ADDRLO_MASK) >> ENET_MAC_ADDR_0_LOW_ADDRLO_SHIFT)

/* Bitfield definition for register of struct array MAC_ADDR: HIGH */
/*
 * AE (RW)
 *
 * Address Enable
 * When this bit is set, the address filter module uses the second MAC address for perfect filtering. When this bit is reset, the address filter module ignores the address for filtering.
 */
#define ENET_MAC_ADDR_HIGH_AE_MASK (0x80000000UL)
#define ENET_MAC_ADDR_HIGH_AE_SHIFT (31U)
#define ENET_MAC_ADDR_HIGH_AE_SET(x) (((uint32_t)(x) << ENET_MAC_ADDR_HIGH_AE_SHIFT) & ENET_MAC_ADDR_HIGH_AE_MASK)
#define ENET_MAC_ADDR_HIGH_AE_GET(x) (((uint32_t)(x) & ENET_MAC_ADDR_HIGH_AE_MASK) >> ENET_MAC_ADDR_HIGH_AE_SHIFT)

/*
 * SA (RW)
 *
 * Source Address
 * When this bit is set, the MAC Address1[47:0] is used to compare with the SA fields of the received frame. When this bit is reset, the MAC Address1[47:0] is used to compare with the DA fields of the received frame.
 */
#define ENET_MAC_ADDR_HIGH_SA_MASK (0x40000000UL)
#define ENET_MAC_ADDR_HIGH_SA_SHIFT (30U)
#define ENET_MAC_ADDR_HIGH_SA_SET(x) (((uint32_t)(x) << ENET_MAC_ADDR_HIGH_SA_SHIFT) & ENET_MAC_ADDR_HIGH_SA_MASK)
#define ENET_MAC_ADDR_HIGH_SA_GET(x) (((uint32_t)(x) & ENET_MAC_ADDR_HIGH_SA_MASK) >> ENET_MAC_ADDR_HIGH_SA_SHIFT)

/*
 * MBC (RW)
 *
 * Mask Byte Control
 * These bits are mask control bits for comparison of each of the MAC Address bytes.
 * When set high, the MAC does not compare the corresponding byte of received DA or SA with the contents of MAC Address1 registers.
 * Each bit controls the masking of the bytes as follows:
 * - Bit 29: Register 18[15:8]
 * - Bit 28: Register 18[7:0]
 * - Bit 27: Register 19[31:24] -
 * ...
 * - Bit 24: Register 19[7:0]
 * You can filter a group of addresses (known as group address filtering) by masking one or more bytes of the address.
 */
#define ENET_MAC_ADDR_HIGH_MBC_MASK (0x3F000000UL)
#define ENET_MAC_ADDR_HIGH_MBC_SHIFT (24U)
#define ENET_MAC_ADDR_HIGH_MBC_SET(x) (((uint32_t)(x) << ENET_MAC_ADDR_HIGH_MBC_SHIFT) & ENET_MAC_ADDR_HIGH_MBC_MASK)
#define ENET_MAC_ADDR_HIGH_MBC_GET(x) (((uint32_t)(x) & ENET_MAC_ADDR_HIGH_MBC_MASK) >> ENET_MAC_ADDR_HIGH_MBC_SHIFT)

/*
 * ADDRHI (RW)
 *
 * MAC Address1 [47:32]
 * This field contains the upper 16 bits (47:32) of the second 6-byte MAC address.
 */
#define ENET_MAC_ADDR_HIGH_ADDRHI_MASK (0xFFFFU)
#define ENET_MAC_ADDR_HIGH_ADDRHI_SHIFT (0U)
#define ENET_MAC_ADDR_HIGH_ADDRHI_SET(x) (((uint32_t)(x) << ENET_MAC_ADDR_HIGH_ADDRHI_SHIFT) & ENET_MAC_ADDR_HIGH_ADDRHI_MASK)
#define ENET_MAC_ADDR_HIGH_ADDRHI_GET(x) (((uint32_t)(x) & ENET_MAC_ADDR_HIGH_ADDRHI_MASK) >> ENET_MAC_ADDR_HIGH_ADDRHI_SHIFT)

/* Bitfield definition for register of struct array MAC_ADDR: LOW */
/*
 * ADDRLO (RW)
 *
 * MAC Address1 [31:0]
 * This field contains the lower 32 bits of the second 6-byte MAC address. The content of this field is undefined until loaded by the Application after the initialization process.
 */
#define ENET_MAC_ADDR_LOW_ADDRLO_MASK (0xFFFFFFFFUL)
#define ENET_MAC_ADDR_LOW_ADDRLO_SHIFT (0U)
#define ENET_MAC_ADDR_LOW_ADDRLO_SET(x) (((uint32_t)(x) << ENET_MAC_ADDR_LOW_ADDRLO_SHIFT) & ENET_MAC_ADDR_LOW_ADDRLO_MASK)
#define ENET_MAC_ADDR_LOW_ADDRLO_GET(x) (((uint32_t)(x) & ENET_MAC_ADDR_LOW_ADDRLO_MASK) >> ENET_MAC_ADDR_LOW_ADDRLO_SHIFT)

/* Bitfield definition for register: XMII_CSR */
/*
 * FALSCARDET (RW)
 *
 * False Carrier Detected
 *  This bit indicates whether the SMII PHY detected false carrier (1'b1). This bit is reserved when the MAC is configured for the SGMII or RGMII PHY interface.
 */
#define ENET_XMII_CSR_FALSCARDET_MASK (0x20U)
#define ENET_XMII_CSR_FALSCARDET_SHIFT (5U)
#define ENET_XMII_CSR_FALSCARDET_SET(x) (((uint32_t)(x) << ENET_XMII_CSR_FALSCARDET_SHIFT) & ENET_XMII_CSR_FALSCARDET_MASK)
#define ENET_XMII_CSR_FALSCARDET_GET(x) (((uint32_t)(x) & ENET_XMII_CSR_FALSCARDET_MASK) >> ENET_XMII_CSR_FALSCARDET_SHIFT)

/*
 * JABTO (RW)
 *
 * Jabber Timeout
 *  This bit indicates whether there is jabber timeout error (1'b1) in the received frame. This bit is reserved when the MAC is configured for the SGMII or RGMII PHY interface.
 */
#define ENET_XMII_CSR_JABTO_MASK (0x10U)
#define ENET_XMII_CSR_JABTO_SHIFT (4U)
#define ENET_XMII_CSR_JABTO_SET(x) (((uint32_t)(x) << ENET_XMII_CSR_JABTO_SHIFT) & ENET_XMII_CSR_JABTO_MASK)
#define ENET_XMII_CSR_JABTO_GET(x) (((uint32_t)(x) & ENET_XMII_CSR_JABTO_MASK) >> ENET_XMII_CSR_JABTO_SHIFT)

/*
 * LNKSTS (RW)
 *
 * Link Status
 *  This bit indicates whether the link between the local PHY and the remote PHY is up or down.
 * It gives the status of the link between the SGMII of MAC and the SGMII of the local PHY.
 * The status bits are received from the local PHY during ANEG betweent he MAC and PHY on the SGMII link.
 */
#define ENET_XMII_CSR_LNKSTS_MASK (0x8U)
#define ENET_XMII_CSR_LNKSTS_SHIFT (3U)
#define ENET_XMII_CSR_LNKSTS_SET(x) (((uint32_t)(x) << ENET_XMII_CSR_LNKSTS_SHIFT) & ENET_XMII_CSR_LNKSTS_MASK)
#define ENET_XMII_CSR_LNKSTS_GET(x) (((uint32_t)(x) & ENET_XMII_CSR_LNKSTS_MASK) >> ENET_XMII_CSR_LNKSTS_SHIFT)

/*
 * LNKSPEED (RW)
 *
 * Link Speed
 *  This bit indicates the current speed of the link:
 * - 00: 2.5 MHz
 * - 01: 25 MHz
 * - 10: 125 MHz Bit 2 is reserved when the MAC is configured for the SMII PHY interface.
 */
#define ENET_XMII_CSR_LNKSPEED_MASK (0x6U)
#define ENET_XMII_CSR_LNKSPEED_SHIFT (1U)
#define ENET_XMII_CSR_LNKSPEED_SET(x) (((uint32_t)(x) << ENET_XMII_CSR_LNKSPEED_SHIFT) & ENET_XMII_CSR_LNKSPEED_MASK)
#define ENET_XMII_CSR_LNKSPEED_GET(x) (((uint32_t)(x) & ENET_XMII_CSR_LNKSPEED_MASK) >> ENET_XMII_CSR_LNKSPEED_SHIFT)

/*
 * LNKMOD (RW)
 *
 * Link Mode
 *  This bit indicates the current mode of operation of the link:
 * - 1’b0: Half-duplex mode
 * - 1’b1: Full-duplex mode
 */
#define ENET_XMII_CSR_LNKMOD_MASK (0x1U)
#define ENET_XMII_CSR_LNKMOD_SHIFT (0U)
#define ENET_XMII_CSR_LNKMOD_SET(x) (((uint32_t)(x) << ENET_XMII_CSR_LNKMOD_SHIFT) & ENET_XMII_CSR_LNKMOD_MASK)
#define ENET_XMII_CSR_LNKMOD_GET(x) (((uint32_t)(x) & ENET_XMII_CSR_LNKMOD_MASK) >> ENET_XMII_CSR_LNKMOD_SHIFT)

/* Bitfield definition for register: WDOG_WTO */
/*
 * PWE (RW)
 *
 * Programmable Watchdog Enable
 *  When this bit is set and Bit 23 (WD) of Register 0 (MAC Configuration Register) is reset,
 * the WTO field (Bits[13:0]) is used as watchdog timeout for a received frame.
 * When this bit is cleared, the watchdog timeout for a received frame is controlled by the setting of Bit 23 (WD) and Bit 20 (JE) in Register 0 (MAC Configuration Register).
 */
#define ENET_WDOG_WTO_PWE_MASK (0x10000UL)
#define ENET_WDOG_WTO_PWE_SHIFT (16U)
#define ENET_WDOG_WTO_PWE_SET(x) (((uint32_t)(x) << ENET_WDOG_WTO_PWE_SHIFT) & ENET_WDOG_WTO_PWE_MASK)
#define ENET_WDOG_WTO_PWE_GET(x) (((uint32_t)(x) & ENET_WDOG_WTO_PWE_MASK) >> ENET_WDOG_WTO_PWE_SHIFT)

/*
 * WTO (RW)
 *
 * Watchdog Timeout
 * When Bit 16 (PWE) is set and Bit 23 (WD) of Register 0 (MAC Configuration Register) is reset,
 * this field is used as watchdog timeout for a received frame.
 *  If the length of a received frame exceeds the value of this field, such frame is terminated and declared as an error frame.
 * Note: When Bit 16 (PWE) is set, the value in this field should be more than 1,522 (0x05F2).
 * Otherwise, the IEEE Std 802.3-specified valid tagged frames are declared as error frames and are dropped.
 */
#define ENET_WDOG_WTO_WTO_MASK (0x3FFFU)
#define ENET_WDOG_WTO_WTO_SHIFT (0U)
#define ENET_WDOG_WTO_WTO_SET(x) (((uint32_t)(x) << ENET_WDOG_WTO_WTO_SHIFT) & ENET_WDOG_WTO_WTO_MASK)
#define ENET_WDOG_WTO_WTO_GET(x) (((uint32_t)(x) & ENET_WDOG_WTO_WTO_MASK) >> ENET_WDOG_WTO_WTO_SHIFT)

/* Bitfield definition for register: MMC_CNTRL */
/*
 * UCDBC (RW)
 *
 * Update MMC Counters for Dropped Broadcast Frames
 * When set, the MAC updates all related MMC Counters for Broadcast frames that are dropped because of the setting of Bit 5 (DBF) of Register 1 (MAC Frame Filter).
 *  When reset, the MMC Counters are not updated for dropped Broadcast frames.
 */
#define ENET_MMC_CNTRL_UCDBC_MASK (0x100U)
#define ENET_MMC_CNTRL_UCDBC_SHIFT (8U)
#define ENET_MMC_CNTRL_UCDBC_SET(x) (((uint32_t)(x) << ENET_MMC_CNTRL_UCDBC_SHIFT) & ENET_MMC_CNTRL_UCDBC_MASK)
#define ENET_MMC_CNTRL_UCDBC_GET(x) (((uint32_t)(x) & ENET_MMC_CNTRL_UCDBC_MASK) >> ENET_MMC_CNTRL_UCDBC_SHIFT)

/*
 * CNTPRSTLVL (RW)
 *
 * Full-Half Preset
 * When this bit is low and Bit 4 is set, all MMC counters get preset to almost-half value. All octet counters get preset to 0x7FFF_F800 (half
 * - 2KBytes) and all frame-counters gets preset to 0x7FFF_FFF0 (half
 * - 16). When this bit is high and Bit 4 is set, all MMC counters get preset to almost-full value. All octet counters get preset to 0xFFFF_F800 (full
 * - 2KBytes) and all frame-counters gets preset to 0xFFFF_FFF0 (full
 * - 16). For 16-bit counters, the almost-half preset values are 0x7800 and 0x7FF0 for the respective octet and frame counters. Similarly, the almost-full preset values for the 16-bit counters are 0xF800 and 0xFFF0.
 */
#define ENET_MMC_CNTRL_CNTPRSTLVL_MASK (0x20U)
#define ENET_MMC_CNTRL_CNTPRSTLVL_SHIFT (5U)
#define ENET_MMC_CNTRL_CNTPRSTLVL_SET(x) (((uint32_t)(x) << ENET_MMC_CNTRL_CNTPRSTLVL_SHIFT) & ENET_MMC_CNTRL_CNTPRSTLVL_MASK)
#define ENET_MMC_CNTRL_CNTPRSTLVL_GET(x) (((uint32_t)(x) & ENET_MMC_CNTRL_CNTPRSTLVL_MASK) >> ENET_MMC_CNTRL_CNTPRSTLVL_SHIFT)

/*
 * CNTPRST (RW)
 *
 * Counters Preset
 * When this bit is set, all counters are initialized or preset to almost full or almost half according to Bit 5. This bit is cleared automatically after 1 clock cycle.
 * This bit, along with Bit 5, is useful for debugging and testing the assertion of interrupts because of MMC counter becoming half-full or full.
 */
#define ENET_MMC_CNTRL_CNTPRST_MASK (0x10U)
#define ENET_MMC_CNTRL_CNTPRST_SHIFT (4U)
#define ENET_MMC_CNTRL_CNTPRST_SET(x) (((uint32_t)(x) << ENET_MMC_CNTRL_CNTPRST_SHIFT) & ENET_MMC_CNTRL_CNTPRST_MASK)
#define ENET_MMC_CNTRL_CNTPRST_GET(x) (((uint32_t)(x) & ENET_MMC_CNTRL_CNTPRST_MASK) >> ENET_MMC_CNTRL_CNTPRST_SHIFT)

/*
 * CNTFREEZ (RW)
 *
 * MMC Counter Freeze
 * When this bit is set, it freezes all MMC counters to their current value.
 * Until this bit is reset to 0, no MMC counter is updated because of any transmitted or received frame.
 *  If any MMC counter is read with the Reset on Read bit set, then that counter is also cleared in this mode.
 */
#define ENET_MMC_CNTRL_CNTFREEZ_MASK (0x8U)
#define ENET_MMC_CNTRL_CNTFREEZ_SHIFT (3U)
#define ENET_MMC_CNTRL_CNTFREEZ_SET(x) (((uint32_t)(x) << ENET_MMC_CNTRL_CNTFREEZ_SHIFT) & ENET_MMC_CNTRL_CNTFREEZ_MASK)
#define ENET_MMC_CNTRL_CNTFREEZ_GET(x) (((uint32_t)(x) & ENET_MMC_CNTRL_CNTFREEZ_MASK) >> ENET_MMC_CNTRL_CNTFREEZ_SHIFT)

/*
 * RSTONRD (RW)
 *
 * Reset on Read
 * When this bit is set, the MMC counters are reset to zero after Read (self-clearing after reset). The counters are cleared when the least significant byte lane (Bits[7:0]) is read.
 */
#define ENET_MMC_CNTRL_RSTONRD_MASK (0x4U)
#define ENET_MMC_CNTRL_RSTONRD_SHIFT (2U)
#define ENET_MMC_CNTRL_RSTONRD_SET(x) (((uint32_t)(x) << ENET_MMC_CNTRL_RSTONRD_SHIFT) & ENET_MMC_CNTRL_RSTONRD_MASK)
#define ENET_MMC_CNTRL_RSTONRD_GET(x) (((uint32_t)(x) & ENET_MMC_CNTRL_RSTONRD_MASK) >> ENET_MMC_CNTRL_RSTONRD_SHIFT)

/*
 * CNTSTOPRO (RW)
 *
 * Counter Stop Rollover
 * When this bit is set, the counter does not roll over to zero after reaching the maximum value.
 */
#define ENET_MMC_CNTRL_CNTSTOPRO_MASK (0x2U)
#define ENET_MMC_CNTRL_CNTSTOPRO_SHIFT (1U)
#define ENET_MMC_CNTRL_CNTSTOPRO_SET(x) (((uint32_t)(x) << ENET_MMC_CNTRL_CNTSTOPRO_SHIFT) & ENET_MMC_CNTRL_CNTSTOPRO_MASK)
#define ENET_MMC_CNTRL_CNTSTOPRO_GET(x) (((uint32_t)(x) & ENET_MMC_CNTRL_CNTSTOPRO_MASK) >> ENET_MMC_CNTRL_CNTSTOPRO_SHIFT)

/*
 * CNTRST (RW)
 *
 * Counters Reset
 * When this bit is set, all counters are reset. This bit is cleared automatically after 1 clock cycle
 */
#define ENET_MMC_CNTRL_CNTRST_MASK (0x1U)
#define ENET_MMC_CNTRL_CNTRST_SHIFT (0U)
#define ENET_MMC_CNTRL_CNTRST_SET(x) (((uint32_t)(x) << ENET_MMC_CNTRL_CNTRST_SHIFT) & ENET_MMC_CNTRL_CNTRST_MASK)
#define ENET_MMC_CNTRL_CNTRST_GET(x) (((uint32_t)(x) & ENET_MMC_CNTRL_CNTRST_MASK) >> ENET_MMC_CNTRL_CNTRST_SHIFT)

/* Bitfield definition for register: MMC_INTR_RX */
/*
 * RXCTRLFIS (RW)
 *
 * MMC Receive Control Frame Counter Interrupt Status
 * This bit is set when the rxctrlframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXCTRLFIS_MASK (0x2000000UL)
#define ENET_MMC_INTR_RX_RXCTRLFIS_SHIFT (25U)
#define ENET_MMC_INTR_RX_RXCTRLFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXCTRLFIS_SHIFT) & ENET_MMC_INTR_RX_RXCTRLFIS_MASK)
#define ENET_MMC_INTR_RX_RXCTRLFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXCTRLFIS_MASK) >> ENET_MMC_INTR_RX_RXCTRLFIS_SHIFT)

/*
 * RXRCVERRFIS (RW)
 *
 * MMC Receive Error Frame Counter Interrupt Status
 * This bit is set when the rxrcverror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXRCVERRFIS_MASK (0x1000000UL)
#define ENET_MMC_INTR_RX_RXRCVERRFIS_SHIFT (24U)
#define ENET_MMC_INTR_RX_RXRCVERRFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXRCVERRFIS_SHIFT) & ENET_MMC_INTR_RX_RXRCVERRFIS_MASK)
#define ENET_MMC_INTR_RX_RXRCVERRFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXRCVERRFIS_MASK) >> ENET_MMC_INTR_RX_RXRCVERRFIS_SHIFT)

/*
 * RXWDOGFIS (RW)
 *
 * MMC Receive Watchdog Error Frame Counter Interrupt Status
 * This bit is set when the rxwatchdog error counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXWDOGFIS_MASK (0x800000UL)
#define ENET_MMC_INTR_RX_RXWDOGFIS_SHIFT (23U)
#define ENET_MMC_INTR_RX_RXWDOGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXWDOGFIS_SHIFT) & ENET_MMC_INTR_RX_RXWDOGFIS_MASK)
#define ENET_MMC_INTR_RX_RXWDOGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXWDOGFIS_MASK) >> ENET_MMC_INTR_RX_RXWDOGFIS_SHIFT)

/*
 * RXVLANGBFIS (RW)
 *
 * MMC Receive VLAN Good Bad Frame Counter Interrupt Status
 * This bit is set when the rxvlanframes_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXVLANGBFIS_MASK (0x400000UL)
#define ENET_MMC_INTR_RX_RXVLANGBFIS_SHIFT (22U)
#define ENET_MMC_INTR_RX_RXVLANGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXVLANGBFIS_SHIFT) & ENET_MMC_INTR_RX_RXVLANGBFIS_MASK)
#define ENET_MMC_INTR_RX_RXVLANGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXVLANGBFIS_MASK) >> ENET_MMC_INTR_RX_RXVLANGBFIS_SHIFT)

/*
 * RXFOVFIS (RW)
 *
 * MMC Receive FIFO Overflow Frame Counter Interrupt Status
 * This bit is set when the rxfifooverflow counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXFOVFIS_MASK (0x200000UL)
#define ENET_MMC_INTR_RX_RXFOVFIS_SHIFT (21U)
#define ENET_MMC_INTR_RX_RXFOVFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXFOVFIS_SHIFT) & ENET_MMC_INTR_RX_RXFOVFIS_MASK)
#define ENET_MMC_INTR_RX_RXFOVFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXFOVFIS_MASK) >> ENET_MMC_INTR_RX_RXFOVFIS_SHIFT)

/*
 * RXPAUSFIS (RW)
 *
 * MMC Receive Pause Frame Counter Interrupt Status
 * This bit is set when the rxpauseframes counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXPAUSFIS_MASK (0x100000UL)
#define ENET_MMC_INTR_RX_RXPAUSFIS_SHIFT (20U)
#define ENET_MMC_INTR_RX_RXPAUSFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXPAUSFIS_SHIFT) & ENET_MMC_INTR_RX_RXPAUSFIS_MASK)
#define ENET_MMC_INTR_RX_RXPAUSFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXPAUSFIS_MASK) >> ENET_MMC_INTR_RX_RXPAUSFIS_SHIFT)

/*
 * RXORANGEFIS (RW)
 *
 * MMC Receive Out Of Range Error Frame Counter Interrupt Status.
 * This bit is set when the rxoutofrangetype counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXORANGEFIS_MASK (0x80000UL)
#define ENET_MMC_INTR_RX_RXORANGEFIS_SHIFT (19U)
#define ENET_MMC_INTR_RX_RXORANGEFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXORANGEFIS_SHIFT) & ENET_MMC_INTR_RX_RXORANGEFIS_MASK)
#define ENET_MMC_INTR_RX_RXORANGEFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXORANGEFIS_MASK) >> ENET_MMC_INTR_RX_RXORANGEFIS_SHIFT)

/*
 * RXLENERFIS (RW)
 *
 * MMC Receive Length Error Frame Counter Interrupt Status
 * This bit is set when the rxlengtherror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXLENERFIS_MASK (0x40000UL)
#define ENET_MMC_INTR_RX_RXLENERFIS_SHIFT (18U)
#define ENET_MMC_INTR_RX_RXLENERFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXLENERFIS_SHIFT) & ENET_MMC_INTR_RX_RXLENERFIS_MASK)
#define ENET_MMC_INTR_RX_RXLENERFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXLENERFIS_MASK) >> ENET_MMC_INTR_RX_RXLENERFIS_SHIFT)

/*
 * RXUCGFIS (RW)
 *
 * MMC Receive Unicast Good Frame Counter Interrupt Status
 * This bit is set when the rxunicastframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXUCGFIS_MASK (0x20000UL)
#define ENET_MMC_INTR_RX_RXUCGFIS_SHIFT (17U)
#define ENET_MMC_INTR_RX_RXUCGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXUCGFIS_SHIFT) & ENET_MMC_INTR_RX_RXUCGFIS_MASK)
#define ENET_MMC_INTR_RX_RXUCGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXUCGFIS_MASK) >> ENET_MMC_INTR_RX_RXUCGFIS_SHIFT)

/*
 * RX1024TMAXOCTGBFIS (RW)
 *
 * MMC Receive 1024 to Maximum Octet Good Bad Frame Counter Interrupt Status.
 * This bit is set when the rx1024tomaxoctets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RX1024TMAXOCTGBFIS_MASK (0x10000UL)
#define ENET_MMC_INTR_RX_RX1024TMAXOCTGBFIS_SHIFT (16U)
#define ENET_MMC_INTR_RX_RX1024TMAXOCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RX1024TMAXOCTGBFIS_SHIFT) & ENET_MMC_INTR_RX_RX1024TMAXOCTGBFIS_MASK)
#define ENET_MMC_INTR_RX_RX1024TMAXOCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RX1024TMAXOCTGBFIS_MASK) >> ENET_MMC_INTR_RX_RX1024TMAXOCTGBFIS_SHIFT)

/*
 * RX512T1023OCTGBFIS (RW)
 *
 * MMC Receive 512 to 1023 Octet Good Bad Frame Counter Interrupt Status
 * This bit is set when the rx512to1023octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RX512T1023OCTGBFIS_MASK (0x8000U)
#define ENET_MMC_INTR_RX_RX512T1023OCTGBFIS_SHIFT (15U)
#define ENET_MMC_INTR_RX_RX512T1023OCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RX512T1023OCTGBFIS_SHIFT) & ENET_MMC_INTR_RX_RX512T1023OCTGBFIS_MASK)
#define ENET_MMC_INTR_RX_RX512T1023OCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RX512T1023OCTGBFIS_MASK) >> ENET_MMC_INTR_RX_RX512T1023OCTGBFIS_SHIFT)

/*
 * RX256T511OCTGBFIS (RW)
 *
 * MMC Receive 256 to 511 Octet Good Bad Frame Counter Interrupt Status
 * This bit is set when the rx256to511octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RX256T511OCTGBFIS_MASK (0x4000U)
#define ENET_MMC_INTR_RX_RX256T511OCTGBFIS_SHIFT (14U)
#define ENET_MMC_INTR_RX_RX256T511OCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RX256T511OCTGBFIS_SHIFT) & ENET_MMC_INTR_RX_RX256T511OCTGBFIS_MASK)
#define ENET_MMC_INTR_RX_RX256T511OCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RX256T511OCTGBFIS_MASK) >> ENET_MMC_INTR_RX_RX256T511OCTGBFIS_SHIFT)

/*
 * RX128T255OCTGBFIS (RW)
 *
 * MMC Receive 128 to 255 Octet Good Bad Frame Counter Interrupt Status
 * This bit is set when the rx128to255octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RX128T255OCTGBFIS_MASK (0x2000U)
#define ENET_MMC_INTR_RX_RX128T255OCTGBFIS_SHIFT (13U)
#define ENET_MMC_INTR_RX_RX128T255OCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RX128T255OCTGBFIS_SHIFT) & ENET_MMC_INTR_RX_RX128T255OCTGBFIS_MASK)
#define ENET_MMC_INTR_RX_RX128T255OCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RX128T255OCTGBFIS_MASK) >> ENET_MMC_INTR_RX_RX128T255OCTGBFIS_SHIFT)

/*
 * RX65T127OCTGBFIS (RW)
 *
 * MMC Receive 65 to 127 Octet Good Bad Frame Counter Interrupt Status
 * This bit is set when the rx65to127octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RX65T127OCTGBFIS_MASK (0x1000U)
#define ENET_MMC_INTR_RX_RX65T127OCTGBFIS_SHIFT (12U)
#define ENET_MMC_INTR_RX_RX65T127OCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RX65T127OCTGBFIS_SHIFT) & ENET_MMC_INTR_RX_RX65T127OCTGBFIS_MASK)
#define ENET_MMC_INTR_RX_RX65T127OCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RX65T127OCTGBFIS_MASK) >> ENET_MMC_INTR_RX_RX65T127OCTGBFIS_SHIFT)

/*
 * RX64OCTGBFIS (RW)
 *
 * MMC Receive 64 Octet Good Bad Frame Counter Interrupt Status
 * This bit is set when the rx64octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RX64OCTGBFIS_MASK (0x800U)
#define ENET_MMC_INTR_RX_RX64OCTGBFIS_SHIFT (11U)
#define ENET_MMC_INTR_RX_RX64OCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RX64OCTGBFIS_SHIFT) & ENET_MMC_INTR_RX_RX64OCTGBFIS_MASK)
#define ENET_MMC_INTR_RX_RX64OCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RX64OCTGBFIS_MASK) >> ENET_MMC_INTR_RX_RX64OCTGBFIS_SHIFT)

/*
 * RXOSIZEGFIS (RW)
 *
 * MMC Receive Oversize Good Frame Counter Interrupt Status
 * This bit is set when the rxoversize_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXOSIZEGFIS_MASK (0x400U)
#define ENET_MMC_INTR_RX_RXOSIZEGFIS_SHIFT (10U)
#define ENET_MMC_INTR_RX_RXOSIZEGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXOSIZEGFIS_SHIFT) & ENET_MMC_INTR_RX_RXOSIZEGFIS_MASK)
#define ENET_MMC_INTR_RX_RXOSIZEGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXOSIZEGFIS_MASK) >> ENET_MMC_INTR_RX_RXOSIZEGFIS_SHIFT)

/*
 * RXUSIZEGFIS (RW)
 *
 * MMC Receive Undersize Good Frame Counter Interrupt Status
 * This bit is set when the rxundersize_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXUSIZEGFIS_MASK (0x200U)
#define ENET_MMC_INTR_RX_RXUSIZEGFIS_SHIFT (9U)
#define ENET_MMC_INTR_RX_RXUSIZEGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXUSIZEGFIS_SHIFT) & ENET_MMC_INTR_RX_RXUSIZEGFIS_MASK)
#define ENET_MMC_INTR_RX_RXUSIZEGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXUSIZEGFIS_MASK) >> ENET_MMC_INTR_RX_RXUSIZEGFIS_SHIFT)

/*
 * RXJABERFIS (RW)
 *
 * MMC Receive Jabber Error Frame Counter Interrupt Status
 * This bit is set when the rxjabbererror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXJABERFIS_MASK (0x100U)
#define ENET_MMC_INTR_RX_RXJABERFIS_SHIFT (8U)
#define ENET_MMC_INTR_RX_RXJABERFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXJABERFIS_SHIFT) & ENET_MMC_INTR_RX_RXJABERFIS_MASK)
#define ENET_MMC_INTR_RX_RXJABERFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXJABERFIS_MASK) >> ENET_MMC_INTR_RX_RXJABERFIS_SHIFT)

/*
 * RXRUNTFIS (RW)
 *
 * MMC Receive Runt Frame Counter Interrupt Status
 * This bit is set when the rxrunterror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXRUNTFIS_MASK (0x80U)
#define ENET_MMC_INTR_RX_RXRUNTFIS_SHIFT (7U)
#define ENET_MMC_INTR_RX_RXRUNTFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXRUNTFIS_SHIFT) & ENET_MMC_INTR_RX_RXRUNTFIS_MASK)
#define ENET_MMC_INTR_RX_RXRUNTFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXRUNTFIS_MASK) >> ENET_MMC_INTR_RX_RXRUNTFIS_SHIFT)

/*
 * RXALGNERFIS (RW)
 *
 * MMC Receive Alignment Error Frame Counter Interrupt Status
 * This bit is set when the rxalignmenterror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXALGNERFIS_MASK (0x40U)
#define ENET_MMC_INTR_RX_RXALGNERFIS_SHIFT (6U)
#define ENET_MMC_INTR_RX_RXALGNERFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXALGNERFIS_SHIFT) & ENET_MMC_INTR_RX_RXALGNERFIS_MASK)
#define ENET_MMC_INTR_RX_RXALGNERFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXALGNERFIS_MASK) >> ENET_MMC_INTR_RX_RXALGNERFIS_SHIFT)

/*
 * RXCRCERFIS (RW)
 *
 * MMC Receive CRC Error Frame Counter Interrupt Status
 * This bit is set when the rxcrcerror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXCRCERFIS_MASK (0x20U)
#define ENET_MMC_INTR_RX_RXCRCERFIS_SHIFT (5U)
#define ENET_MMC_INTR_RX_RXCRCERFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXCRCERFIS_SHIFT) & ENET_MMC_INTR_RX_RXCRCERFIS_MASK)
#define ENET_MMC_INTR_RX_RXCRCERFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXCRCERFIS_MASK) >> ENET_MMC_INTR_RX_RXCRCERFIS_SHIFT)

/*
 * RXMCGFIS (RW)
 *
 * MMC Receive Multicast Good Frame Counter Interrupt Status
 * This bit is set when the rxmulticastframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXMCGFIS_MASK (0x10U)
#define ENET_MMC_INTR_RX_RXMCGFIS_SHIFT (4U)
#define ENET_MMC_INTR_RX_RXMCGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXMCGFIS_SHIFT) & ENET_MMC_INTR_RX_RXMCGFIS_MASK)
#define ENET_MMC_INTR_RX_RXMCGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXMCGFIS_MASK) >> ENET_MMC_INTR_RX_RXMCGFIS_SHIFT)

/*
 * RXBCGFIS (RW)
 *
 * MMC Receive Broadcast Good Frame Counter Interrupt Status
 * This bit is set when the rxbroadcastframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXBCGFIS_MASK (0x8U)
#define ENET_MMC_INTR_RX_RXBCGFIS_SHIFT (3U)
#define ENET_MMC_INTR_RX_RXBCGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXBCGFIS_SHIFT) & ENET_MMC_INTR_RX_RXBCGFIS_MASK)
#define ENET_MMC_INTR_RX_RXBCGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXBCGFIS_MASK) >> ENET_MMC_INTR_RX_RXBCGFIS_SHIFT)

/*
 * RXGOCTIS (RW)
 *
 * MMC Receive Good Octet Counter Interrupt Status
 * This bit is set when the rxoctetcount_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXGOCTIS_MASK (0x4U)
#define ENET_MMC_INTR_RX_RXGOCTIS_SHIFT (2U)
#define ENET_MMC_INTR_RX_RXGOCTIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXGOCTIS_SHIFT) & ENET_MMC_INTR_RX_RXGOCTIS_MASK)
#define ENET_MMC_INTR_RX_RXGOCTIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXGOCTIS_MASK) >> ENET_MMC_INTR_RX_RXGOCTIS_SHIFT)

/*
 * RXGBOCTIS (RW)
 *
 * MMC Receive Good Bad Octet Counter Interrupt Status
 * This bit is set when the rxoctetcount_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXGBOCTIS_MASK (0x2U)
#define ENET_MMC_INTR_RX_RXGBOCTIS_SHIFT (1U)
#define ENET_MMC_INTR_RX_RXGBOCTIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXGBOCTIS_SHIFT) & ENET_MMC_INTR_RX_RXGBOCTIS_MASK)
#define ENET_MMC_INTR_RX_RXGBOCTIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXGBOCTIS_MASK) >> ENET_MMC_INTR_RX_RXGBOCTIS_SHIFT)

/*
 * RXGBFRMIS (RW)
 *
 * MMC Receive Good Bad Frame Counter Interrupt Status
 * This bit is set when the rxframecount_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_RX_RXGBFRMIS_MASK (0x1U)
#define ENET_MMC_INTR_RX_RXGBFRMIS_SHIFT (0U)
#define ENET_MMC_INTR_RX_RXGBFRMIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_RX_RXGBFRMIS_SHIFT) & ENET_MMC_INTR_RX_RXGBFRMIS_MASK)
#define ENET_MMC_INTR_RX_RXGBFRMIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_RX_RXGBFRMIS_MASK) >> ENET_MMC_INTR_RX_RXGBFRMIS_SHIFT)

/* Bitfield definition for register: MMC_INTR_TX */
/*
 * TXOSIZEGFIS (RW)
 *
 * MMC Transmit Oversize Good Frame Counter Interrupt Status
 * This bit is set when the txoversize_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXOSIZEGFIS_MASK (0x2000000UL)
#define ENET_MMC_INTR_TX_TXOSIZEGFIS_SHIFT (25U)
#define ENET_MMC_INTR_TX_TXOSIZEGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXOSIZEGFIS_SHIFT) & ENET_MMC_INTR_TX_TXOSIZEGFIS_MASK)
#define ENET_MMC_INTR_TX_TXOSIZEGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXOSIZEGFIS_MASK) >> ENET_MMC_INTR_TX_TXOSIZEGFIS_SHIFT)

/*
 * TXVLANGFIS (RW)
 *
 * MMC Transmit VLAN Good Frame Counter Interrupt Status
 * This bit is set when the txvlanframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXVLANGFIS_MASK (0x1000000UL)
#define ENET_MMC_INTR_TX_TXVLANGFIS_SHIFT (24U)
#define ENET_MMC_INTR_TX_TXVLANGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXVLANGFIS_SHIFT) & ENET_MMC_INTR_TX_TXVLANGFIS_MASK)
#define ENET_MMC_INTR_TX_TXVLANGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXVLANGFIS_MASK) >> ENET_MMC_INTR_TX_TXVLANGFIS_SHIFT)

/*
 * TXPAUSFIS (RW)
 *
 * MMC Transmit Pause Frame Counter Interrupt Status
 * This bit is set when the txpauseframeserror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXPAUSFIS_MASK (0x800000UL)
#define ENET_MMC_INTR_TX_TXPAUSFIS_SHIFT (23U)
#define ENET_MMC_INTR_TX_TXPAUSFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXPAUSFIS_SHIFT) & ENET_MMC_INTR_TX_TXPAUSFIS_MASK)
#define ENET_MMC_INTR_TX_TXPAUSFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXPAUSFIS_MASK) >> ENET_MMC_INTR_TX_TXPAUSFIS_SHIFT)

/*
 * TXEXDEFFIS (RW)
 *
 * MMC Transmit Excessive Deferral Frame Counter Interrupt Status
 * This bit is set when the txexcessdef counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXEXDEFFIS_MASK (0x400000UL)
#define ENET_MMC_INTR_TX_TXEXDEFFIS_SHIFT (22U)
#define ENET_MMC_INTR_TX_TXEXDEFFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXEXDEFFIS_SHIFT) & ENET_MMC_INTR_TX_TXEXDEFFIS_MASK)
#define ENET_MMC_INTR_TX_TXEXDEFFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXEXDEFFIS_MASK) >> ENET_MMC_INTR_TX_TXEXDEFFIS_SHIFT)

/*
 * TXGFRMIS (RW)
 *
 * MMC Transmit Good Frame Counter Interrupt Status
 * This bit is set when the txframecount_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXGFRMIS_MASK (0x200000UL)
#define ENET_MMC_INTR_TX_TXGFRMIS_SHIFT (21U)
#define ENET_MMC_INTR_TX_TXGFRMIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXGFRMIS_SHIFT) & ENET_MMC_INTR_TX_TXGFRMIS_MASK)
#define ENET_MMC_INTR_TX_TXGFRMIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXGFRMIS_MASK) >> ENET_MMC_INTR_TX_TXGFRMIS_SHIFT)

/*
 * TXGOCTIS (RW)
 *
 * MMC Transmit Good Octet Counter Interrupt Status
 * This bit is set when the txoctetcount_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXGOCTIS_MASK (0x100000UL)
#define ENET_MMC_INTR_TX_TXGOCTIS_SHIFT (20U)
#define ENET_MMC_INTR_TX_TXGOCTIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXGOCTIS_SHIFT) & ENET_MMC_INTR_TX_TXGOCTIS_MASK)
#define ENET_MMC_INTR_TX_TXGOCTIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXGOCTIS_MASK) >> ENET_MMC_INTR_TX_TXGOCTIS_SHIFT)

/*
 * TXCARERFIS (RW)
 *
 * MMC Transmit Carrier Error Frame Counter Interrupt Status
 * This bit is set when the txcarriererror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXCARERFIS_MASK (0x80000UL)
#define ENET_MMC_INTR_TX_TXCARERFIS_SHIFT (19U)
#define ENET_MMC_INTR_TX_TXCARERFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXCARERFIS_SHIFT) & ENET_MMC_INTR_TX_TXCARERFIS_MASK)
#define ENET_MMC_INTR_TX_TXCARERFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXCARERFIS_MASK) >> ENET_MMC_INTR_TX_TXCARERFIS_SHIFT)

/*
 * TXEXCOLFIS (RW)
 *
 * MMC Transmit Excessive Collision Frame Counter Interrupt Status
 * This bit is set when the txexesscol counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXEXCOLFIS_MASK (0x40000UL)
#define ENET_MMC_INTR_TX_TXEXCOLFIS_SHIFT (18U)
#define ENET_MMC_INTR_TX_TXEXCOLFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXEXCOLFIS_SHIFT) & ENET_MMC_INTR_TX_TXEXCOLFIS_MASK)
#define ENET_MMC_INTR_TX_TXEXCOLFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXEXCOLFIS_MASK) >> ENET_MMC_INTR_TX_TXEXCOLFIS_SHIFT)

/*
 * TXLATCOLFIS (RW)
 *
 * MMC Transmit Late Collision Frame Counter Interrupt Status
 * This bit is set when the txlatecol counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXLATCOLFIS_MASK (0x20000UL)
#define ENET_MMC_INTR_TX_TXLATCOLFIS_SHIFT (17U)
#define ENET_MMC_INTR_TX_TXLATCOLFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXLATCOLFIS_SHIFT) & ENET_MMC_INTR_TX_TXLATCOLFIS_MASK)
#define ENET_MMC_INTR_TX_TXLATCOLFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXLATCOLFIS_MASK) >> ENET_MMC_INTR_TX_TXLATCOLFIS_SHIFT)

/*
 * TXDEFFIS (RW)
 *
 * MMC Transmit Deferred Frame Counter Interrupt Status
 * This bit is set when the txdeferred counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXDEFFIS_MASK (0x10000UL)
#define ENET_MMC_INTR_TX_TXDEFFIS_SHIFT (16U)
#define ENET_MMC_INTR_TX_TXDEFFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXDEFFIS_SHIFT) & ENET_MMC_INTR_TX_TXDEFFIS_MASK)
#define ENET_MMC_INTR_TX_TXDEFFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXDEFFIS_MASK) >> ENET_MMC_INTR_TX_TXDEFFIS_SHIFT)

/*
 * TXMCOLGFIS (RW)
 *
 * MMC Transmit Multiple Collision Good Frame Counter Interrupt Status
 * This bit is set when the txmulticol_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXMCOLGFIS_MASK (0x8000U)
#define ENET_MMC_INTR_TX_TXMCOLGFIS_SHIFT (15U)
#define ENET_MMC_INTR_TX_TXMCOLGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXMCOLGFIS_SHIFT) & ENET_MMC_INTR_TX_TXMCOLGFIS_MASK)
#define ENET_MMC_INTR_TX_TXMCOLGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXMCOLGFIS_MASK) >> ENET_MMC_INTR_TX_TXMCOLGFIS_SHIFT)

/*
 * TXSCOLGFIS (RW)
 *
 * MMC Transmit Single Collision Good Frame Counter Interrupt Status
 * This bit is set when the txsinglecol_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXSCOLGFIS_MASK (0x4000U)
#define ENET_MMC_INTR_TX_TXSCOLGFIS_SHIFT (14U)
#define ENET_MMC_INTR_TX_TXSCOLGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXSCOLGFIS_SHIFT) & ENET_MMC_INTR_TX_TXSCOLGFIS_MASK)
#define ENET_MMC_INTR_TX_TXSCOLGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXSCOLGFIS_MASK) >> ENET_MMC_INTR_TX_TXSCOLGFIS_SHIFT)

/*
 * TXUFLOWERFIS (RW)
 *
 * MMC Transmit Underflow Error Frame Counter Interrupt Status
 * This bit is set when the txunderflowerror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXUFLOWERFIS_MASK (0x2000U)
#define ENET_MMC_INTR_TX_TXUFLOWERFIS_SHIFT (13U)
#define ENET_MMC_INTR_TX_TXUFLOWERFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXUFLOWERFIS_SHIFT) & ENET_MMC_INTR_TX_TXUFLOWERFIS_MASK)
#define ENET_MMC_INTR_TX_TXUFLOWERFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXUFLOWERFIS_MASK) >> ENET_MMC_INTR_TX_TXUFLOWERFIS_SHIFT)

/*
 * TXBCGBFIS (RW)
 *
 * MMC Transmit Broadcast Good Bad Frame Counter Interrupt Status
 * This bit is set when the txbroadcastframes_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXBCGBFIS_MASK (0x1000U)
#define ENET_MMC_INTR_TX_TXBCGBFIS_SHIFT (12U)
#define ENET_MMC_INTR_TX_TXBCGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXBCGBFIS_SHIFT) & ENET_MMC_INTR_TX_TXBCGBFIS_MASK)
#define ENET_MMC_INTR_TX_TXBCGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXBCGBFIS_MASK) >> ENET_MMC_INTR_TX_TXBCGBFIS_SHIFT)

/*
 * TXMCGBFIS (RW)
 *
 * MMC Transmit Multicast Good Bad Frame Counter Interrupt Status
 * The bit is set when the txmulticastframes_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXMCGBFIS_MASK (0x800U)
#define ENET_MMC_INTR_TX_TXMCGBFIS_SHIFT (11U)
#define ENET_MMC_INTR_TX_TXMCGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXMCGBFIS_SHIFT) & ENET_MMC_INTR_TX_TXMCGBFIS_MASK)
#define ENET_MMC_INTR_TX_TXMCGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXMCGBFIS_MASK) >> ENET_MMC_INTR_TX_TXMCGBFIS_SHIFT)

/*
 * TXUCGBFIS (RW)
 *
 * MMC Transmit Unicast Good Bad Frame Counter Interrupt Status
 * This bit is set when the txunicastframes_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXUCGBFIS_MASK (0x400U)
#define ENET_MMC_INTR_TX_TXUCGBFIS_SHIFT (10U)
#define ENET_MMC_INTR_TX_TXUCGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXUCGBFIS_SHIFT) & ENET_MMC_INTR_TX_TXUCGBFIS_MASK)
#define ENET_MMC_INTR_TX_TXUCGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXUCGBFIS_MASK) >> ENET_MMC_INTR_TX_TXUCGBFIS_SHIFT)

/*
 * TX1024TMAXOCTGBFIS (RW)
 *
 * MMC Transmit 1024 to Maximum Octet Good Bad Frame Counter Interrupt Status
 * This bit is set when the tx1024tomaxoctets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TX1024TMAXOCTGBFIS_MASK (0x200U)
#define ENET_MMC_INTR_TX_TX1024TMAXOCTGBFIS_SHIFT (9U)
#define ENET_MMC_INTR_TX_TX1024TMAXOCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TX1024TMAXOCTGBFIS_SHIFT) & ENET_MMC_INTR_TX_TX1024TMAXOCTGBFIS_MASK)
#define ENET_MMC_INTR_TX_TX1024TMAXOCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TX1024TMAXOCTGBFIS_MASK) >> ENET_MMC_INTR_TX_TX1024TMAXOCTGBFIS_SHIFT)

/*
 * TX512T1023OCTGBFIS (RW)
 *
 * MMC Transmit 512 to 1023 Octet Good Bad Frame Counter Interrupt Status
 * This bit is set when the tx512to1023octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TX512T1023OCTGBFIS_MASK (0x100U)
#define ENET_MMC_INTR_TX_TX512T1023OCTGBFIS_SHIFT (8U)
#define ENET_MMC_INTR_TX_TX512T1023OCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TX512T1023OCTGBFIS_SHIFT) & ENET_MMC_INTR_TX_TX512T1023OCTGBFIS_MASK)
#define ENET_MMC_INTR_TX_TX512T1023OCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TX512T1023OCTGBFIS_MASK) >> ENET_MMC_INTR_TX_TX512T1023OCTGBFIS_SHIFT)

/*
 * TX256T511OCTGBFIS (RW)
 *
 * MMC Transmit 256 to 511 Octet Good Bad Frame Counter Interrupt Status
 * This bit is set when the tx256to511octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TX256T511OCTGBFIS_MASK (0x80U)
#define ENET_MMC_INTR_TX_TX256T511OCTGBFIS_SHIFT (7U)
#define ENET_MMC_INTR_TX_TX256T511OCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TX256T511OCTGBFIS_SHIFT) & ENET_MMC_INTR_TX_TX256T511OCTGBFIS_MASK)
#define ENET_MMC_INTR_TX_TX256T511OCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TX256T511OCTGBFIS_MASK) >> ENET_MMC_INTR_TX_TX256T511OCTGBFIS_SHIFT)

/*
 * TX128T255OCTGBFIS (RW)
 *
 * MMC Transmit 128 to 255 Octet Good Bad Frame Counter Interrupt Status
 * This bit is set when the tx128to255octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TX128T255OCTGBFIS_MASK (0x40U)
#define ENET_MMC_INTR_TX_TX128T255OCTGBFIS_SHIFT (6U)
#define ENET_MMC_INTR_TX_TX128T255OCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TX128T255OCTGBFIS_SHIFT) & ENET_MMC_INTR_TX_TX128T255OCTGBFIS_MASK)
#define ENET_MMC_INTR_TX_TX128T255OCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TX128T255OCTGBFIS_MASK) >> ENET_MMC_INTR_TX_TX128T255OCTGBFIS_SHIFT)

/*
 * TX65T127OCTGBFIS (RW)
 *
 * MMC Transmit 65 to 127 Octet Good Bad Frame Counter Interrupt Status
 * This bit is set when the tx65to127octets_gb counter reaches half the maximum value, and also when it reaches the maximum value.
 */
#define ENET_MMC_INTR_TX_TX65T127OCTGBFIS_MASK (0x20U)
#define ENET_MMC_INTR_TX_TX65T127OCTGBFIS_SHIFT (5U)
#define ENET_MMC_INTR_TX_TX65T127OCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TX65T127OCTGBFIS_SHIFT) & ENET_MMC_INTR_TX_TX65T127OCTGBFIS_MASK)
#define ENET_MMC_INTR_TX_TX65T127OCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TX65T127OCTGBFIS_MASK) >> ENET_MMC_INTR_TX_TX65T127OCTGBFIS_SHIFT)

/*
 * TX64OCTGBFIS (RW)
 *
 * MMC Transmit 64 Octet Good Bad Frame Counter Interrupt Status
 * This bit is set when the tx64octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TX64OCTGBFIS_MASK (0x10U)
#define ENET_MMC_INTR_TX_TX64OCTGBFIS_SHIFT (4U)
#define ENET_MMC_INTR_TX_TX64OCTGBFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TX64OCTGBFIS_SHIFT) & ENET_MMC_INTR_TX_TX64OCTGBFIS_MASK)
#define ENET_MMC_INTR_TX_TX64OCTGBFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TX64OCTGBFIS_MASK) >> ENET_MMC_INTR_TX_TX64OCTGBFIS_SHIFT)

/*
 * TXMCGFIS (RW)
 *
 * MMC Transmit Multicast Good Frame Counter Interrupt Status
 * This bit is set when the txmulticastframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXMCGFIS_MASK (0x8U)
#define ENET_MMC_INTR_TX_TXMCGFIS_SHIFT (3U)
#define ENET_MMC_INTR_TX_TXMCGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXMCGFIS_SHIFT) & ENET_MMC_INTR_TX_TXMCGFIS_MASK)
#define ENET_MMC_INTR_TX_TXMCGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXMCGFIS_MASK) >> ENET_MMC_INTR_TX_TXMCGFIS_SHIFT)

/*
 * TXBCGFIS (RW)
 *
 * MMC Transmit Broadcast Good Frame Counter Interrupt Status
 * This bit is set when the txbroadcastframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXBCGFIS_MASK (0x4U)
#define ENET_MMC_INTR_TX_TXBCGFIS_SHIFT (2U)
#define ENET_MMC_INTR_TX_TXBCGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXBCGFIS_SHIFT) & ENET_MMC_INTR_TX_TXBCGFIS_MASK)
#define ENET_MMC_INTR_TX_TXBCGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXBCGFIS_MASK) >> ENET_MMC_INTR_TX_TXBCGFIS_SHIFT)

/*
 * TXGBFRMIS (RW)
 *
 * MMC Transmit Good Bad Frame Counter Interrupt Status
 * This bit is set when the txframecount_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXGBFRMIS_MASK (0x2U)
#define ENET_MMC_INTR_TX_TXGBFRMIS_SHIFT (1U)
#define ENET_MMC_INTR_TX_TXGBFRMIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXGBFRMIS_SHIFT) & ENET_MMC_INTR_TX_TXGBFRMIS_MASK)
#define ENET_MMC_INTR_TX_TXGBFRMIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXGBFRMIS_MASK) >> ENET_MMC_INTR_TX_TXGBFRMIS_SHIFT)

/*
 * TXGBOCTIS (RW)
 *
 * MMC Transmit Good Bad Octet Counter Interrupt Status
 * This bit is set when the txoctetcount_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_TX_TXGBOCTIS_MASK (0x1U)
#define ENET_MMC_INTR_TX_TXGBOCTIS_SHIFT (0U)
#define ENET_MMC_INTR_TX_TXGBOCTIS_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_TX_TXGBOCTIS_SHIFT) & ENET_MMC_INTR_TX_TXGBOCTIS_MASK)
#define ENET_MMC_INTR_TX_TXGBOCTIS_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_TX_TXGBOCTIS_MASK) >> ENET_MMC_INTR_TX_TXGBOCTIS_SHIFT)

/* Bitfield definition for register: MMC_INTR_MASK_RX */
/*
 * RXCTRLFIM (RW)
 *
 * MMC Receive Control Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxctrlframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXCTRLFIM_MASK (0x2000000UL)
#define ENET_MMC_INTR_MASK_RX_RXCTRLFIM_SHIFT (25U)
#define ENET_MMC_INTR_MASK_RX_RXCTRLFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXCTRLFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXCTRLFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXCTRLFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXCTRLFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXCTRLFIM_SHIFT)

/*
 * RXRCVERRFIM (RW)
 *
 * MMC Receive Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxrcverror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXRCVERRFIM_MASK (0x1000000UL)
#define ENET_MMC_INTR_MASK_RX_RXRCVERRFIM_SHIFT (24U)
#define ENET_MMC_INTR_MASK_RX_RXRCVERRFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXRCVERRFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXRCVERRFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXRCVERRFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXRCVERRFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXRCVERRFIM_SHIFT)

/*
 * RXWDOGFIM (RW)
 *
 * MMC Receive Watchdog Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxwatchdog counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXWDOGFIM_MASK (0x800000UL)
#define ENET_MMC_INTR_MASK_RX_RXWDOGFIM_SHIFT (23U)
#define ENET_MMC_INTR_MASK_RX_RXWDOGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXWDOGFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXWDOGFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXWDOGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXWDOGFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXWDOGFIM_SHIFT)

/*
 * RXVLANGBFIM (RW)
 *
 * MMC Receive VLAN Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxvlanframes_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXVLANGBFIM_MASK (0x400000UL)
#define ENET_MMC_INTR_MASK_RX_RXVLANGBFIM_SHIFT (22U)
#define ENET_MMC_INTR_MASK_RX_RXVLANGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXVLANGBFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXVLANGBFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXVLANGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXVLANGBFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXVLANGBFIM_SHIFT)

/*
 * RXFOVFIM (RW)
 *
 * MMC Receive FIFO Overflow Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxfifooverflow counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXFOVFIM_MASK (0x200000UL)
#define ENET_MMC_INTR_MASK_RX_RXFOVFIM_SHIFT (21U)
#define ENET_MMC_INTR_MASK_RX_RXFOVFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXFOVFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXFOVFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXFOVFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXFOVFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXFOVFIM_SHIFT)

/*
 * RXPAUSFIM (RW)
 *
 * MMC Receive Pause Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxpauseframes counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXPAUSFIM_MASK (0x100000UL)
#define ENET_MMC_INTR_MASK_RX_RXPAUSFIM_SHIFT (20U)
#define ENET_MMC_INTR_MASK_RX_RXPAUSFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXPAUSFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXPAUSFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXPAUSFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXPAUSFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXPAUSFIM_SHIFT)

/*
 * RXORANGEFIM (RW)
 *
 * MMC Receive Out Of Range Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxoutofrangetype counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXORANGEFIM_MASK (0x80000UL)
#define ENET_MMC_INTR_MASK_RX_RXORANGEFIM_SHIFT (19U)
#define ENET_MMC_INTR_MASK_RX_RXORANGEFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXORANGEFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXORANGEFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXORANGEFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXORANGEFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXORANGEFIM_SHIFT)

/*
 * RXLENERFIM (RW)
 *
 * MMC Receive Length Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxlengtherror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXLENERFIM_MASK (0x40000UL)
#define ENET_MMC_INTR_MASK_RX_RXLENERFIM_SHIFT (18U)
#define ENET_MMC_INTR_MASK_RX_RXLENERFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXLENERFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXLENERFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXLENERFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXLENERFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXLENERFIM_SHIFT)

/*
 * RXUCGFIM (RW)
 *
 * MMC Receive Unicast Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxunicastframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXUCGFIM_MASK (0x20000UL)
#define ENET_MMC_INTR_MASK_RX_RXUCGFIM_SHIFT (17U)
#define ENET_MMC_INTR_MASK_RX_RXUCGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXUCGFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXUCGFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXUCGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXUCGFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXUCGFIM_SHIFT)

/*
 * RX1024TMAXOCTGBFIM (RW)
 *
 * MMC Receive 1024 to Maximum Octet Good Bad Frame Counter Interrupt Mask.
 * Setting this bit masks the interrupt when the rx1024tomaxoctets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RX1024TMAXOCTGBFIM_MASK (0x10000UL)
#define ENET_MMC_INTR_MASK_RX_RX1024TMAXOCTGBFIM_SHIFT (16U)
#define ENET_MMC_INTR_MASK_RX_RX1024TMAXOCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RX1024TMAXOCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RX1024TMAXOCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RX1024TMAXOCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RX1024TMAXOCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RX1024TMAXOCTGBFIM_SHIFT)

/*
 * RX512T1023OCTGBFIM (RW)
 *
 * MMC Receive 512 to 1023 Octet Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rx512to1023octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RX512T1023OCTGBFIM_MASK (0x8000U)
#define ENET_MMC_INTR_MASK_RX_RX512T1023OCTGBFIM_SHIFT (15U)
#define ENET_MMC_INTR_MASK_RX_RX512T1023OCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RX512T1023OCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RX512T1023OCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RX512T1023OCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RX512T1023OCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RX512T1023OCTGBFIM_SHIFT)

/*
 * RX256T511OCTGBFIM (RW)
 *
 * MMC Receive 256 to 511 Octet Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rx256to511octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RX256T511OCTGBFIM_MASK (0x4000U)
#define ENET_MMC_INTR_MASK_RX_RX256T511OCTGBFIM_SHIFT (14U)
#define ENET_MMC_INTR_MASK_RX_RX256T511OCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RX256T511OCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RX256T511OCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RX256T511OCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RX256T511OCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RX256T511OCTGBFIM_SHIFT)

/*
 * RX128T255OCTGBFIM (RW)
 *
 * MMC Receive 128 to 255 Octet Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rx128to255octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RX128T255OCTGBFIM_MASK (0x2000U)
#define ENET_MMC_INTR_MASK_RX_RX128T255OCTGBFIM_SHIFT (13U)
#define ENET_MMC_INTR_MASK_RX_RX128T255OCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RX128T255OCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RX128T255OCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RX128T255OCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RX128T255OCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RX128T255OCTGBFIM_SHIFT)

/*
 * RX65T127OCTGBFIM (RW)
 *
 * MMC Receive 65 to 127 Octet Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rx65to127octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RX65T127OCTGBFIM_MASK (0x1000U)
#define ENET_MMC_INTR_MASK_RX_RX65T127OCTGBFIM_SHIFT (12U)
#define ENET_MMC_INTR_MASK_RX_RX65T127OCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RX65T127OCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RX65T127OCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RX65T127OCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RX65T127OCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RX65T127OCTGBFIM_SHIFT)

/*
 * RX64OCTGBFIM (RW)
 *
 * MMC Receive 64 Octet Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rx64octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RX64OCTGBFIM_MASK (0x800U)
#define ENET_MMC_INTR_MASK_RX_RX64OCTGBFIM_SHIFT (11U)
#define ENET_MMC_INTR_MASK_RX_RX64OCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RX64OCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RX64OCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RX64OCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RX64OCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RX64OCTGBFIM_SHIFT)

/*
 * RXOSIZEGFIM (RW)
 *
 * MMC Receive Oversize Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxoversize_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXOSIZEGFIM_MASK (0x400U)
#define ENET_MMC_INTR_MASK_RX_RXOSIZEGFIM_SHIFT (10U)
#define ENET_MMC_INTR_MASK_RX_RXOSIZEGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXOSIZEGFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXOSIZEGFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXOSIZEGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXOSIZEGFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXOSIZEGFIM_SHIFT)

/*
 * RXUSIZEGFIM (RW)
 *
 * MMC Receive Undersize Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxundersize_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXUSIZEGFIM_MASK (0x200U)
#define ENET_MMC_INTR_MASK_RX_RXUSIZEGFIM_SHIFT (9U)
#define ENET_MMC_INTR_MASK_RX_RXUSIZEGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXUSIZEGFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXUSIZEGFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXUSIZEGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXUSIZEGFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXUSIZEGFIM_SHIFT)

/*
 * RXJABERFIM (RW)
 *
 * MMC Receive Jabber Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxjabbererror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXJABERFIM_MASK (0x100U)
#define ENET_MMC_INTR_MASK_RX_RXJABERFIM_SHIFT (8U)
#define ENET_MMC_INTR_MASK_RX_RXJABERFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXJABERFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXJABERFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXJABERFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXJABERFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXJABERFIM_SHIFT)

/*
 * RXRUNTFIM (RW)
 *
 * MMC Receive Runt Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxrunterror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXRUNTFIM_MASK (0x80U)
#define ENET_MMC_INTR_MASK_RX_RXRUNTFIM_SHIFT (7U)
#define ENET_MMC_INTR_MASK_RX_RXRUNTFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXRUNTFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXRUNTFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXRUNTFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXRUNTFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXRUNTFIM_SHIFT)

/*
 * RXALGNERFIM (RW)
 *
 * MMC Receive Alignment Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxalignmenterror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXALGNERFIM_MASK (0x40U)
#define ENET_MMC_INTR_MASK_RX_RXALGNERFIM_SHIFT (6U)
#define ENET_MMC_INTR_MASK_RX_RXALGNERFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXALGNERFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXALGNERFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXALGNERFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXALGNERFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXALGNERFIM_SHIFT)

/*
 * RXCRCERFIM (RW)
 *
 * MMC Receive CRC Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxcrcerror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXCRCERFIM_MASK (0x20U)
#define ENET_MMC_INTR_MASK_RX_RXCRCERFIM_SHIFT (5U)
#define ENET_MMC_INTR_MASK_RX_RXCRCERFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXCRCERFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXCRCERFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXCRCERFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXCRCERFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXCRCERFIM_SHIFT)

/*
 * RXMCGFIM (RW)
 *
 * MMC Receive Multicast Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxmulticastframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXMCGFIM_MASK (0x10U)
#define ENET_MMC_INTR_MASK_RX_RXMCGFIM_SHIFT (4U)
#define ENET_MMC_INTR_MASK_RX_RXMCGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXMCGFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXMCGFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXMCGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXMCGFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXMCGFIM_SHIFT)

/*
 * RXBCGFIM (RW)
 *
 * MMC Receive Broadcast Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxbroadcastframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXBCGFIM_MASK (0x8U)
#define ENET_MMC_INTR_MASK_RX_RXBCGFIM_SHIFT (3U)
#define ENET_MMC_INTR_MASK_RX_RXBCGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXBCGFIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXBCGFIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXBCGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXBCGFIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXBCGFIM_SHIFT)

/*
 * RXGOCTIM (RW)
 *
 * MMC Receive Good Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxoctetcount_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXGOCTIM_MASK (0x4U)
#define ENET_MMC_INTR_MASK_RX_RXGOCTIM_SHIFT (2U)
#define ENET_MMC_INTR_MASK_RX_RXGOCTIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXGOCTIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXGOCTIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXGOCTIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXGOCTIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXGOCTIM_SHIFT)

/*
 * RXGBOCTIM (RW)
 *
 * MMC Receive Good Bad Octet Counter Interrupt Mask.
 * Setting this bit masks the interrupt when the rxoctetcount_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_RX_RXGBOCTIM_MASK (0x2U)
#define ENET_MMC_INTR_MASK_RX_RXGBOCTIM_SHIFT (1U)
#define ENET_MMC_INTR_MASK_RX_RXGBOCTIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_RX_RXGBOCTIM_SHIFT) & ENET_MMC_INTR_MASK_RX_RXGBOCTIM_MASK)
#define ENET_MMC_INTR_MASK_RX_RXGBOCTIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_RX_RXGBOCTIM_MASK) >> ENET_MMC_INTR_MASK_RX_RXGBOCTIM_SHIFT)

/* Bitfield definition for register: MMC_INTR_MASK_TX */
/*
 * TXOSIZEGFIM (RW)
 *
 * MMC Transmit Oversize Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txoversize_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXOSIZEGFIM_MASK (0x2000000UL)
#define ENET_MMC_INTR_MASK_TX_TXOSIZEGFIM_SHIFT (25U)
#define ENET_MMC_INTR_MASK_TX_TXOSIZEGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXOSIZEGFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXOSIZEGFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXOSIZEGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXOSIZEGFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXOSIZEGFIM_SHIFT)

/*
 * TXVLANGFIM (RW)
 *
 * MMC Transmit VLAN Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txvlanframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXVLANGFIM_MASK (0x1000000UL)
#define ENET_MMC_INTR_MASK_TX_TXVLANGFIM_SHIFT (24U)
#define ENET_MMC_INTR_MASK_TX_TXVLANGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXVLANGFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXVLANGFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXVLANGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXVLANGFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXVLANGFIM_SHIFT)

/*
 * TXPAUSFIM (RW)
 *
 * MMC Transmit Pause Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txpauseframes counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXPAUSFIM_MASK (0x800000UL)
#define ENET_MMC_INTR_MASK_TX_TXPAUSFIM_SHIFT (23U)
#define ENET_MMC_INTR_MASK_TX_TXPAUSFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXPAUSFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXPAUSFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXPAUSFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXPAUSFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXPAUSFIM_SHIFT)

/*
 * TXEXDEFFIM (RW)
 *
 * MMC Transmit Excessive Deferral Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txexcessdef counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXEXDEFFIM_MASK (0x400000UL)
#define ENET_MMC_INTR_MASK_TX_TXEXDEFFIM_SHIFT (22U)
#define ENET_MMC_INTR_MASK_TX_TXEXDEFFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXEXDEFFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXEXDEFFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXEXDEFFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXEXDEFFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXEXDEFFIM_SHIFT)

/*
 * TXGFRMIM (RW)
 *
 * MMC Transmit Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txframecount_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXGFRMIM_MASK (0x200000UL)
#define ENET_MMC_INTR_MASK_TX_TXGFRMIM_SHIFT (21U)
#define ENET_MMC_INTR_MASK_TX_TXGFRMIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXGFRMIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXGFRMIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXGFRMIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXGFRMIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXGFRMIM_SHIFT)

/*
 * TXGOCTIM (RW)
 *
 * MMC Transmit Good Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txoctetcount_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXGOCTIM_MASK (0x100000UL)
#define ENET_MMC_INTR_MASK_TX_TXGOCTIM_SHIFT (20U)
#define ENET_MMC_INTR_MASK_TX_TXGOCTIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXGOCTIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXGOCTIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXGOCTIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXGOCTIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXGOCTIM_SHIFT)

/*
 * TXCARERFIM (RW)
 *
 * MMC Transmit Carrier Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txcarriererror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXCARERFIM_MASK (0x80000UL)
#define ENET_MMC_INTR_MASK_TX_TXCARERFIM_SHIFT (19U)
#define ENET_MMC_INTR_MASK_TX_TXCARERFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXCARERFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXCARERFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXCARERFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXCARERFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXCARERFIM_SHIFT)

/*
 * TXEXCOLFIM (RW)
 *
 * MMC Transmit Excessive Collision Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txexcesscol counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXEXCOLFIM_MASK (0x40000UL)
#define ENET_MMC_INTR_MASK_TX_TXEXCOLFIM_SHIFT (18U)
#define ENET_MMC_INTR_MASK_TX_TXEXCOLFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXEXCOLFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXEXCOLFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXEXCOLFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXEXCOLFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXEXCOLFIM_SHIFT)

/*
 * TXLATCOLFIM (RW)
 *
 * MMC Transmit Late Collision Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txlatecol counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXLATCOLFIM_MASK (0x20000UL)
#define ENET_MMC_INTR_MASK_TX_TXLATCOLFIM_SHIFT (17U)
#define ENET_MMC_INTR_MASK_TX_TXLATCOLFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXLATCOLFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXLATCOLFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXLATCOLFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXLATCOLFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXLATCOLFIM_SHIFT)

/*
 * TXDEFFIM (RW)
 *
 * MMC Transmit Deferred Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txdeferred counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXDEFFIM_MASK (0x10000UL)
#define ENET_MMC_INTR_MASK_TX_TXDEFFIM_SHIFT (16U)
#define ENET_MMC_INTR_MASK_TX_TXDEFFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXDEFFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXDEFFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXDEFFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXDEFFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXDEFFIM_SHIFT)

/*
 * TXMCOLGFIM (RW)
 *
 * MMC Transmit Multiple Collision Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txmulticol_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXMCOLGFIM_MASK (0x8000U)
#define ENET_MMC_INTR_MASK_TX_TXMCOLGFIM_SHIFT (15U)
#define ENET_MMC_INTR_MASK_TX_TXMCOLGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXMCOLGFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXMCOLGFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXMCOLGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXMCOLGFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXMCOLGFIM_SHIFT)

/*
 * TXSCOLGFIM (RW)
 *
 * MMC Transmit Single Collision Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txsinglecol_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXSCOLGFIM_MASK (0x4000U)
#define ENET_MMC_INTR_MASK_TX_TXSCOLGFIM_SHIFT (14U)
#define ENET_MMC_INTR_MASK_TX_TXSCOLGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXSCOLGFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXSCOLGFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXSCOLGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXSCOLGFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXSCOLGFIM_SHIFT)

/*
 * TXUFLOWERFIM (RW)
 *
 * MMC Transmit Underflow Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txunderflowerror counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXUFLOWERFIM_MASK (0x2000U)
#define ENET_MMC_INTR_MASK_TX_TXUFLOWERFIM_SHIFT (13U)
#define ENET_MMC_INTR_MASK_TX_TXUFLOWERFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXUFLOWERFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXUFLOWERFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXUFLOWERFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXUFLOWERFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXUFLOWERFIM_SHIFT)

/*
 * TXBCGBFIM (RW)
 *
 * MMC Transmit Broadcast Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txbroadcastframes_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXBCGBFIM_MASK (0x1000U)
#define ENET_MMC_INTR_MASK_TX_TXBCGBFIM_SHIFT (12U)
#define ENET_MMC_INTR_MASK_TX_TXBCGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXBCGBFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXBCGBFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXBCGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXBCGBFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXBCGBFIM_SHIFT)

/*
 * TXMCGBFIM (RW)
 *
 * MMC Transmit Multicast Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txmulticastframes_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXMCGBFIM_MASK (0x800U)
#define ENET_MMC_INTR_MASK_TX_TXMCGBFIM_SHIFT (11U)
#define ENET_MMC_INTR_MASK_TX_TXMCGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXMCGBFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXMCGBFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXMCGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXMCGBFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXMCGBFIM_SHIFT)

/*
 * TXUCGBFIM (RW)
 *
 * MMC Transmit Unicast Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txunicastframes_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXUCGBFIM_MASK (0x400U)
#define ENET_MMC_INTR_MASK_TX_TXUCGBFIM_SHIFT (10U)
#define ENET_MMC_INTR_MASK_TX_TXUCGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXUCGBFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXUCGBFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXUCGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXUCGBFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXUCGBFIM_SHIFT)

/*
 * TX1024TMAXOCTGBFIM (RW)
 *
 * MMC Transmit 1024 to Maximum Octet Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the tx1024tomaxoctets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TX1024TMAXOCTGBFIM_MASK (0x200U)
#define ENET_MMC_INTR_MASK_TX_TX1024TMAXOCTGBFIM_SHIFT (9U)
#define ENET_MMC_INTR_MASK_TX_TX1024TMAXOCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TX1024TMAXOCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TX1024TMAXOCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TX1024TMAXOCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TX1024TMAXOCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TX1024TMAXOCTGBFIM_SHIFT)

/*
 * TX512T1023OCTGBFIM (RW)
 *
 * MMC Transmit 512 to 1023 Octet Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the tx512to1023octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TX512T1023OCTGBFIM_MASK (0x100U)
#define ENET_MMC_INTR_MASK_TX_TX512T1023OCTGBFIM_SHIFT (8U)
#define ENET_MMC_INTR_MASK_TX_TX512T1023OCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TX512T1023OCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TX512T1023OCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TX512T1023OCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TX512T1023OCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TX512T1023OCTGBFIM_SHIFT)

/*
 * TX256T511OCTGBFIM (RW)
 *
 * MMC Transmit 256 to 511 Octet Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the tx256to511octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TX256T511OCTGBFIM_MASK (0x80U)
#define ENET_MMC_INTR_MASK_TX_TX256T511OCTGBFIM_SHIFT (7U)
#define ENET_MMC_INTR_MASK_TX_TX256T511OCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TX256T511OCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TX256T511OCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TX256T511OCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TX256T511OCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TX256T511OCTGBFIM_SHIFT)

/*
 * TX128T255OCTGBFIM (RW)
 *
 * MMC Transmit 128 to 255 Octet Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the tx128to255octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TX128T255OCTGBFIM_MASK (0x40U)
#define ENET_MMC_INTR_MASK_TX_TX128T255OCTGBFIM_SHIFT (6U)
#define ENET_MMC_INTR_MASK_TX_TX128T255OCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TX128T255OCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TX128T255OCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TX128T255OCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TX128T255OCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TX128T255OCTGBFIM_SHIFT)

/*
 * TX65T127OCTGBFIM (RW)
 *
 * MMC Transmit 65 to 127 Octet Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the tx65to127octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TX65T127OCTGBFIM_MASK (0x20U)
#define ENET_MMC_INTR_MASK_TX_TX65T127OCTGBFIM_SHIFT (5U)
#define ENET_MMC_INTR_MASK_TX_TX65T127OCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TX65T127OCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TX65T127OCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TX65T127OCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TX65T127OCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TX65T127OCTGBFIM_SHIFT)

/*
 * TX64OCTGBFIM (RW)
 *
 * MMC Transmit 64 Octet Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the tx64octets_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TX64OCTGBFIM_MASK (0x10U)
#define ENET_MMC_INTR_MASK_TX_TX64OCTGBFIM_SHIFT (4U)
#define ENET_MMC_INTR_MASK_TX_TX64OCTGBFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TX64OCTGBFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TX64OCTGBFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TX64OCTGBFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TX64OCTGBFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TX64OCTGBFIM_SHIFT)

/*
 * TXMCGFIM (RW)
 *
 * MMC Transmit Multicast Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txmulticastframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXMCGFIM_MASK (0x8U)
#define ENET_MMC_INTR_MASK_TX_TXMCGFIM_SHIFT (3U)
#define ENET_MMC_INTR_MASK_TX_TXMCGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXMCGFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXMCGFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXMCGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXMCGFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXMCGFIM_SHIFT)

/*
 * TXBCGFIM (RW)
 *
 * MMC Transmit Broadcast Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txbroadcastframes_g counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXBCGFIM_MASK (0x4U)
#define ENET_MMC_INTR_MASK_TX_TXBCGFIM_SHIFT (2U)
#define ENET_MMC_INTR_MASK_TX_TXBCGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXBCGFIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXBCGFIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXBCGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXBCGFIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXBCGFIM_SHIFT)

/*
 * TXGBFRMIM (RW)
 *
 * MMC Transmit Good Bad Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txframecount_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXGBFRMIM_MASK (0x2U)
#define ENET_MMC_INTR_MASK_TX_TXGBFRMIM_SHIFT (1U)
#define ENET_MMC_INTR_MASK_TX_TXGBFRMIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXGBFRMIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXGBFRMIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXGBFRMIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXGBFRMIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXGBFRMIM_SHIFT)

/*
 * TXGBOCTIM (RW)
 *
 * MMC Transmit Good Bad Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the txoctetcount_gb counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_INTR_MASK_TX_TXGBOCTIM_MASK (0x1U)
#define ENET_MMC_INTR_MASK_TX_TXGBOCTIM_SHIFT (0U)
#define ENET_MMC_INTR_MASK_TX_TXGBOCTIM_SET(x) (((uint32_t)(x) << ENET_MMC_INTR_MASK_TX_TXGBOCTIM_SHIFT) & ENET_MMC_INTR_MASK_TX_TXGBOCTIM_MASK)
#define ENET_MMC_INTR_MASK_TX_TXGBOCTIM_GET(x) (((uint32_t)(x) & ENET_MMC_INTR_MASK_TX_TXGBOCTIM_MASK) >> ENET_MMC_INTR_MASK_TX_TXGBOCTIM_SHIFT)

/* Bitfield definition for register: TX64OCTETS_GB */
/*
 * FRMCNT (RW)
 *
 * Number of good and bad frames transmitted with length 64 bytes, exclusive of preamble and retried frames.
 */
#define ENET_TX64OCTETS_GB_FRMCNT_MASK (0xFFFFFFFFUL)
#define ENET_TX64OCTETS_GB_FRMCNT_SHIFT (0U)
#define ENET_TX64OCTETS_GB_FRMCNT_SET(x) (((uint32_t)(x) << ENET_TX64OCTETS_GB_FRMCNT_SHIFT) & ENET_TX64OCTETS_GB_FRMCNT_MASK)
#define ENET_TX64OCTETS_GB_FRMCNT_GET(x) (((uint32_t)(x) & ENET_TX64OCTETS_GB_FRMCNT_MASK) >> ENET_TX64OCTETS_GB_FRMCNT_SHIFT)

/* Bitfield definition for register: TX65TO127OCTETS_GB */
/*
 * FRMCNT (RW)
 *
 * Number of good and bad frames transmitted with length between 65 and 127 (inclusive) bytes, exclusive of preamble and retried frames.
 */
#define ENET_TX65TO127OCTETS_GB_FRMCNT_MASK (0xFFFFFFFFUL)
#define ENET_TX65TO127OCTETS_GB_FRMCNT_SHIFT (0U)
#define ENET_TX65TO127OCTETS_GB_FRMCNT_SET(x) (((uint32_t)(x) << ENET_TX65TO127OCTETS_GB_FRMCNT_SHIFT) & ENET_TX65TO127OCTETS_GB_FRMCNT_MASK)
#define ENET_TX65TO127OCTETS_GB_FRMCNT_GET(x) (((uint32_t)(x) & ENET_TX65TO127OCTETS_GB_FRMCNT_MASK) >> ENET_TX65TO127OCTETS_GB_FRMCNT_SHIFT)

/* Bitfield definition for register: TX128TO255OCTETS_GB */
/*
 * FRMCNT (RW)
 *
 * Number of good and bad frames transmitted with length between 128 and 255 (inclusive) bytes, exclusive of preamble and retried frames.
 */
#define ENET_TX128TO255OCTETS_GB_FRMCNT_MASK (0xFFFFFFFFUL)
#define ENET_TX128TO255OCTETS_GB_FRMCNT_SHIFT (0U)
#define ENET_TX128TO255OCTETS_GB_FRMCNT_SET(x) (((uint32_t)(x) << ENET_TX128TO255OCTETS_GB_FRMCNT_SHIFT) & ENET_TX128TO255OCTETS_GB_FRMCNT_MASK)
#define ENET_TX128TO255OCTETS_GB_FRMCNT_GET(x) (((uint32_t)(x) & ENET_TX128TO255OCTETS_GB_FRMCNT_MASK) >> ENET_TX128TO255OCTETS_GB_FRMCNT_SHIFT)

/* Bitfield definition for register: TX256TO511OCTETS_GB */
/*
 * FRMCNT (RW)
 *
 * Number of good and bad frames transmitted with length between 256 and 511 (inclusive) bytes, exclusive of preamble and retried frames.
 */
#define ENET_TX256TO511OCTETS_GB_FRMCNT_MASK (0xFFFFFFFFUL)
#define ENET_TX256TO511OCTETS_GB_FRMCNT_SHIFT (0U)
#define ENET_TX256TO511OCTETS_GB_FRMCNT_SET(x) (((uint32_t)(x) << ENET_TX256TO511OCTETS_GB_FRMCNT_SHIFT) & ENET_TX256TO511OCTETS_GB_FRMCNT_MASK)
#define ENET_TX256TO511OCTETS_GB_FRMCNT_GET(x) (((uint32_t)(x) & ENET_TX256TO511OCTETS_GB_FRMCNT_MASK) >> ENET_TX256TO511OCTETS_GB_FRMCNT_SHIFT)

/* Bitfield definition for register: TX512TO1023OCTETS_GB */
/*
 * FRMCNT (RW)
 *
 * Number of good and bad frames transmitted with length between 512 and 1,023 (inclusive) bytes, exclusive of preamble and retried frames.
 */
#define ENET_TX512TO1023OCTETS_GB_FRMCNT_MASK (0xFFFFFFFFUL)
#define ENET_TX512TO1023OCTETS_GB_FRMCNT_SHIFT (0U)
#define ENET_TX512TO1023OCTETS_GB_FRMCNT_SET(x) (((uint32_t)(x) << ENET_TX512TO1023OCTETS_GB_FRMCNT_SHIFT) & ENET_TX512TO1023OCTETS_GB_FRMCNT_MASK)
#define ENET_TX512TO1023OCTETS_GB_FRMCNT_GET(x) (((uint32_t)(x) & ENET_TX512TO1023OCTETS_GB_FRMCNT_MASK) >> ENET_TX512TO1023OCTETS_GB_FRMCNT_SHIFT)

/* Bitfield definition for register: TX1024TOMAXOCTETS_GB */
/*
 * FRMCNT (RW)
 *
 * Number of good and bad frames transmitted with length between 1,024 and maxsize (inclusive) bytes, exclusive of preamble and retried frames.
 */
#define ENET_TX1024TOMAXOCTETS_GB_FRMCNT_MASK (0xFFFFFFFFUL)
#define ENET_TX1024TOMAXOCTETS_GB_FRMCNT_SHIFT (0U)
#define ENET_TX1024TOMAXOCTETS_GB_FRMCNT_SET(x) (((uint32_t)(x) << ENET_TX1024TOMAXOCTETS_GB_FRMCNT_SHIFT) & ENET_TX1024TOMAXOCTETS_GB_FRMCNT_MASK)
#define ENET_TX1024TOMAXOCTETS_GB_FRMCNT_GET(x) (((uint32_t)(x) & ENET_TX1024TOMAXOCTETS_GB_FRMCNT_MASK) >> ENET_TX1024TOMAXOCTETS_GB_FRMCNT_SHIFT)

/* Bitfield definition for register: RXFRAMECOUNT_GB */
/*
 * FRMCNT (RW)
 *
 * Number of good and bad frames received.
 */
#define ENET_RXFRAMECOUNT_GB_FRMCNT_MASK (0xFFFFFFFFUL)
#define ENET_RXFRAMECOUNT_GB_FRMCNT_SHIFT (0U)
#define ENET_RXFRAMECOUNT_GB_FRMCNT_SET(x) (((uint32_t)(x) << ENET_RXFRAMECOUNT_GB_FRMCNT_SHIFT) & ENET_RXFRAMECOUNT_GB_FRMCNT_MASK)
#define ENET_RXFRAMECOUNT_GB_FRMCNT_GET(x) (((uint32_t)(x) & ENET_RXFRAMECOUNT_GB_FRMCNT_MASK) >> ENET_RXFRAMECOUNT_GB_FRMCNT_SHIFT)

/* Bitfield definition for register: MMC_IPC_INTR_MASK_RX */
/*
 * RXICMPEROIM (RW)
 *
 * MMC Receive ICMP Error Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxicmp_err_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPEROIM_MASK (0x20000000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPEROIM_SHIFT (29U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPEROIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXICMPEROIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXICMPEROIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPEROIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXICMPEROIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXICMPEROIM_SHIFT)

/*
 * RXICMPGOIM (RW)
 *
 * MMC Receive ICMP Good Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxicmp_gd_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPGOIM_MASK (0x10000000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPGOIM_SHIFT (28U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPGOIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXICMPGOIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXICMPGOIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPGOIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXICMPGOIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXICMPGOIM_SHIFT)

/*
 * RXTCPEROIM (RW)
 *
 * MMC Receive TCP Error Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxtcp_err_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPEROIM_MASK (0x8000000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPEROIM_SHIFT (27U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPEROIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXTCPEROIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXTCPEROIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPEROIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXTCPEROIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXTCPEROIM_SHIFT)

/*
 * RXTCPGOIM (RW)
 *
 * MMC Receive TCP Good Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxtcp_gd_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPGOIM_MASK (0x4000000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPGOIM_SHIFT (26U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPGOIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXTCPGOIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXTCPGOIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPGOIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXTCPGOIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXTCPGOIM_SHIFT)

/*
 * RXUDPEROIM (RW)
 *
 * MMC Receive UDP Good Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxudp_err_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPEROIM_MASK (0x2000000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPEROIM_SHIFT (25U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPEROIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXUDPEROIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXUDPEROIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPEROIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXUDPEROIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXUDPEROIM_SHIFT)

/*
 * RXUDPGOIM (RW)
 *
 * MMC Receive IPV6 No Payload Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxudp_gd_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPGOIM_MASK (0x1000000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPGOIM_SHIFT (24U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPGOIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXUDPGOIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXUDPGOIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPGOIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXUDPGOIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXUDPGOIM_SHIFT)

/*
 * RXIPV6NOPAYOIM (RW)
 *
 * MMC Receive IPV6 Header Error Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv6_nopay_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYOIM_MASK (0x800000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYOIM_SHIFT (23U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYOIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYOIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYOIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYOIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYOIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYOIM_SHIFT)

/*
 * RXIPV6HEROIM (RW)
 *
 * MMC Receive IPV6 Good Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv6_hdrerr_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HEROIM_MASK (0x400000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HEROIM_SHIFT (22U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HEROIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HEROIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HEROIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HEROIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HEROIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HEROIM_SHIFT)

/*
 * RXIPV6GOIM (RW)
 *
 * MMC Receive IPV6 Good Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv6_gd_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GOIM_MASK (0x200000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GOIM_SHIFT (21U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GOIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GOIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GOIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GOIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GOIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GOIM_SHIFT)

/*
 * RXIPV4UDSBLOIM (RW)
 *
 * MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv4_udsbl_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLOIM_MASK (0x100000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLOIM_SHIFT (20U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLOIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLOIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLOIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLOIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLOIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLOIM_SHIFT)

/*
 * RXIPV4FRAGOIM (RW)
 *
 * MMC Receive IPV4 Fragmented Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv4_frag_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGOIM_MASK (0x80000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGOIM_SHIFT (19U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGOIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGOIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGOIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGOIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGOIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGOIM_SHIFT)

/*
 * RXIPV4NOPAYOIM (RW)
 *
 * MMC Receive IPV4 No Payload Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv4_nopay_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYOIM_MASK (0x40000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYOIM_SHIFT (18U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYOIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYOIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYOIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYOIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYOIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYOIM_SHIFT)

/*
 * RXIPV4HEROIM (RW)
 *
 * MMC Receive IPV4 Header Error Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv4_hdrerr_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HEROIM_MASK (0x20000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HEROIM_SHIFT (17U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HEROIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HEROIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HEROIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HEROIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HEROIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HEROIM_SHIFT)

/*
 * RXIPV4GOIM (RW)
 *
 * MMC Receive IPV4 Good Octet Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv4_gd_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GOIM_MASK (0x10000UL)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GOIM_SHIFT (16U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GOIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GOIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GOIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GOIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GOIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GOIM_SHIFT)

/*
 * RXICMPERFIM (RW)
 *
 * MMC Receive ICMP Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxicmp_err_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPERFIM_MASK (0x2000U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPERFIM_SHIFT (13U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPERFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXICMPERFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXICMPERFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPERFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXICMPERFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXICMPERFIM_SHIFT)

/*
 * RXICMPGFIM (RW)
 *
 * MMC Receive ICMP Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxicmp_gd_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPGFIM_MASK (0x1000U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPGFIM_SHIFT (12U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXICMPGFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXICMPGFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXICMPGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXICMPGFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXICMPGFIM_SHIFT)

/*
 * RXTCPERFIM (RW)
 *
 * MMC Receive TCP Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxtcp_err_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPERFIM_MASK (0x800U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPERFIM_SHIFT (11U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPERFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXTCPERFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXTCPERFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPERFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXTCPERFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXTCPERFIM_SHIFT)

/*
 * RXTCPGFIM (RW)
 *
 * MMC Receive TCP Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxtcp_gd_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPGFIM_MASK (0x400U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPGFIM_SHIFT (10U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXTCPGFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXTCPGFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXTCPGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXTCPGFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXTCPGFIM_SHIFT)

/*
 * RXUDPERFIM (RW)
 *
 * MMC Receive UDP Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxudp_err_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPERFIM_MASK (0x200U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPERFIM_SHIFT (9U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPERFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXUDPERFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXUDPERFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPERFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXUDPERFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXUDPERFIM_SHIFT)

/*
 * RXUDPGFIM (RW)
 *
 * MMC Receive UDP Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxudp_gd_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPGFIM_MASK (0x100U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPGFIM_SHIFT (8U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXUDPGFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXUDPGFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXUDPGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXUDPGFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXUDPGFIM_SHIFT)

/*
 * RXIPV6NOPAYFIM (RW)
 *
 * MMC Receive IPV6 No Payload Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv6_nopay_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYFIM_MASK (0x80U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYFIM_SHIFT (7U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV6NOPAYFIM_SHIFT)

/*
 * RXIPV6HERFIM (RW)
 *
 * MMC Receive IPV6 Header Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv6_hdrerr_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HERFIM_MASK (0x40U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HERFIM_SHIFT (6U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HERFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HERFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HERFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HERFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HERFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV6HERFIM_SHIFT)

/*
 * RXIPV6GFIM (RW)
 *
 * MMC Receive IPV6 Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv6_gd_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GFIM_MASK (0x20U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GFIM_SHIFT (5U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV6GFIM_SHIFT)

/*
 * RXIPV4UDSBLFIM (RW)
 *
 * MMC Receive IPV4 UDP Checksum Disabled Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv4_udsbl_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLFIM_MASK (0x10U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLFIM_SHIFT (4U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV4UDSBLFIM_SHIFT)

/*
 * RXIPV4FRAGFIM (RW)
 *
 * MMC Receive IPV4 Fragmented Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv4_frag_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGFIM_MASK (0x8U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGFIM_SHIFT (3U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV4FRAGFIM_SHIFT)

/*
 * RXIPV4NOPAYFIM (RW)
 *
 * MMC Receive IPV4 No Payload Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv4_nopay_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYFIM_MASK (0x4U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYFIM_SHIFT (2U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV4NOPAYFIM_SHIFT)

/*
 * RXIPV4HERFIM (RW)
 *
 * MMC Receive IPV4 Header Error Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv4_hdrerr_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HERFIM_MASK (0x2U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HERFIM_SHIFT (1U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HERFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HERFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HERFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HERFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HERFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV4HERFIM_SHIFT)

/*
 * RXIPV4GFIM (RW)
 *
 * MMC Receive IPV4 Good Frame Counter Interrupt Mask
 * Setting this bit masks the interrupt when the rxipv4_gd_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GFIM_MASK (0x1U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GFIM_SHIFT (0U)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GFIM_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GFIM_SHIFT) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GFIM_MASK)
#define ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GFIM_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GFIM_MASK) >> ENET_MMC_IPC_INTR_MASK_RX_RXIPV4GFIM_SHIFT)

/* Bitfield definition for register: MMC_IPC_INTR_RX */
/*
 * RXICMPEROIS (RW)
 *
 * MMC Receive ICMP Error Octet Counter Interrupt Status
 * This bit is set when the rxicmp_err_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXICMPEROIS_MASK (0x20000000UL)
#define ENET_MMC_IPC_INTR_RX_RXICMPEROIS_SHIFT (29U)
#define ENET_MMC_IPC_INTR_RX_RXICMPEROIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXICMPEROIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXICMPEROIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXICMPEROIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXICMPEROIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXICMPEROIS_SHIFT)

/*
 * RXICMPGOIS (RW)
 *
 * MMC Receive ICMP Good Octet Counter Interrupt Status
 * This bit is set when the rxicmp_gd_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXICMPGOIS_MASK (0x10000000UL)
#define ENET_MMC_IPC_INTR_RX_RXICMPGOIS_SHIFT (28U)
#define ENET_MMC_IPC_INTR_RX_RXICMPGOIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXICMPGOIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXICMPGOIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXICMPGOIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXICMPGOIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXICMPGOIS_SHIFT)

/*
 * RXTCPEROIS (RW)
 *
 * MMC Receive TCP Error Octet Counter Interrupt Status
 * This bit is set when the rxtcp_err_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXTCPEROIS_MASK (0x8000000UL)
#define ENET_MMC_IPC_INTR_RX_RXTCPEROIS_SHIFT (27U)
#define ENET_MMC_IPC_INTR_RX_RXTCPEROIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXTCPEROIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXTCPEROIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXTCPEROIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXTCPEROIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXTCPEROIS_SHIFT)

/*
 * RXTCPGOIS (RW)
 *
 * MMC Receive TCP Good Octet Counter Interrupt Status
 * This bit is set when the rxtcp_gd_octets counter reaches half of the maximum value or the maximum value
 */
#define ENET_MMC_IPC_INTR_RX_RXTCPGOIS_MASK (0x4000000UL)
#define ENET_MMC_IPC_INTR_RX_RXTCPGOIS_SHIFT (26U)
#define ENET_MMC_IPC_INTR_RX_RXTCPGOIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXTCPGOIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXTCPGOIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXTCPGOIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXTCPGOIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXTCPGOIS_SHIFT)

/*
 * RXUDPEROIS (RW)
 *
 * MMC Receive UDP Error Octet Counter Interrupt Status
 * This bit is set when the rxudp_err_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXUDPEROIS_MASK (0x2000000UL)
#define ENET_MMC_IPC_INTR_RX_RXUDPEROIS_SHIFT (25U)
#define ENET_MMC_IPC_INTR_RX_RXUDPEROIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXUDPEROIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXUDPEROIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXUDPEROIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXUDPEROIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXUDPEROIS_SHIFT)

/*
 * RXUDPGOIS (RW)
 *
 * MMC Receive UDP Good Octet Counter Interrupt Status
 * This bit is set when the rxudp_gd_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXUDPGOIS_MASK (0x1000000UL)
#define ENET_MMC_IPC_INTR_RX_RXUDPGOIS_SHIFT (24U)
#define ENET_MMC_IPC_INTR_RX_RXUDPGOIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXUDPGOIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXUDPGOIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXUDPGOIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXUDPGOIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXUDPGOIS_SHIFT)

/*
 * RXIPV6NOPAYOIS (RW)
 *
 * MMC Receive IPV6 No Payload Octet Counter Interrupt Status
 * This bit is set when the rxipv6_nopay_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYOIS_MASK (0x800000UL)
#define ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYOIS_SHIFT (23U)
#define ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYOIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYOIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYOIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYOIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYOIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYOIS_SHIFT)

/*
 * RXIPV6HEROIS (RW)
 *
 * MMC Receive IPV6 Header Error Octet Counter Interrupt Status
 * This bit is set when the rxipv6_hdrerr_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV6HEROIS_MASK (0x400000UL)
#define ENET_MMC_IPC_INTR_RX_RXIPV6HEROIS_SHIFT (22U)
#define ENET_MMC_IPC_INTR_RX_RXIPV6HEROIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV6HEROIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV6HEROIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV6HEROIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV6HEROIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV6HEROIS_SHIFT)

/*
 * RXIPV6GOIS (RW)
 *
 * MMC Receive IPV6 Good Octet Counter Interrupt Status
 * This bit is set when the rxipv6_gd_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV6GOIS_MASK (0x200000UL)
#define ENET_MMC_IPC_INTR_RX_RXIPV6GOIS_SHIFT (21U)
#define ENET_MMC_IPC_INTR_RX_RXIPV6GOIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV6GOIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV6GOIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV6GOIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV6GOIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV6GOIS_SHIFT)

/*
 * RXIPV4UDSBLOIS (RW)
 *
 * MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Status
 * This bit is set when the rxipv4_udsbl_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLOIS_MASK (0x100000UL)
#define ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLOIS_SHIFT (20U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLOIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLOIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLOIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLOIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLOIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLOIS_SHIFT)

/*
 * RXIPV4FRAGOIS (RW)
 *
 * MMC Receive IPV4 Fragmented Octet Counter Interrupt Status
 * This bit is set when the rxipv4_frag_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV4FRAGOIS_MASK (0x80000UL)
#define ENET_MMC_IPC_INTR_RX_RXIPV4FRAGOIS_SHIFT (19U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4FRAGOIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV4FRAGOIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV4FRAGOIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV4FRAGOIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV4FRAGOIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV4FRAGOIS_SHIFT)

/*
 * RXIPV4NOPAYOIS (RW)
 *
 * MMC Receive IPV4 No Payload Octet Counter Interrupt Status
 * This bit is set when the rxipv4_nopay_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYOIS_MASK (0x40000UL)
#define ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYOIS_SHIFT (18U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYOIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYOIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYOIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYOIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYOIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYOIS_SHIFT)

/*
 * RXIPV4HEROIS (RW)
 *
 * MMC Receive IPV4 Header Error Octet Counter Interrupt Status
 * This bit is set when the rxipv4_hdrerr_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV4HEROIS_MASK (0x20000UL)
#define ENET_MMC_IPC_INTR_RX_RXIPV4HEROIS_SHIFT (17U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4HEROIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV4HEROIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV4HEROIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV4HEROIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV4HEROIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV4HEROIS_SHIFT)

/*
 * RXIPV4GOIS (RW)
 *
 * MMC Receive IPV4 Good Octet Counter Interrupt Status
 * This bit is set when the rxipv4_gd_octets counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV4GOIS_MASK (0x10000UL)
#define ENET_MMC_IPC_INTR_RX_RXIPV4GOIS_SHIFT (16U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4GOIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV4GOIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV4GOIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV4GOIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV4GOIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV4GOIS_SHIFT)

/*
 * RXICMPERFIS (RW)
 *
 * MMC Receive ICMP Error Frame Counter Interrupt Status
 * This bit is set when the rxicmp_err_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXICMPERFIS_MASK (0x2000U)
#define ENET_MMC_IPC_INTR_RX_RXICMPERFIS_SHIFT (13U)
#define ENET_MMC_IPC_INTR_RX_RXICMPERFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXICMPERFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXICMPERFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXICMPERFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXICMPERFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXICMPERFIS_SHIFT)

/*
 * RXICMPGFIS (RW)
 *
 * MMC Receive ICMP Good Frame Counter Interrupt Status
 * This bit is set when the rxicmp_gd_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXICMPGFIS_MASK (0x1000U)
#define ENET_MMC_IPC_INTR_RX_RXICMPGFIS_SHIFT (12U)
#define ENET_MMC_IPC_INTR_RX_RXICMPGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXICMPGFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXICMPGFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXICMPGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXICMPGFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXICMPGFIS_SHIFT)

/*
 * RXTCPERFIS (RW)
 *
 * MMC Receive TCP Error Frame Counter Interrupt Status
 * This bit is set when the rxtcp_err_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXTCPERFIS_MASK (0x800U)
#define ENET_MMC_IPC_INTR_RX_RXTCPERFIS_SHIFT (11U)
#define ENET_MMC_IPC_INTR_RX_RXTCPERFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXTCPERFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXTCPERFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXTCPERFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXTCPERFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXTCPERFIS_SHIFT)

/*
 * RXTCPGFIS (RW)
 *
 * MMC Receive TCP Good Frame Counter Interrupt Status
 * This bit is set when the rxtcp_gd_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXTCPGFIS_MASK (0x400U)
#define ENET_MMC_IPC_INTR_RX_RXTCPGFIS_SHIFT (10U)
#define ENET_MMC_IPC_INTR_RX_RXTCPGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXTCPGFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXTCPGFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXTCPGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXTCPGFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXTCPGFIS_SHIFT)

/*
 * RXUDPERFIS (RW)
 *
 * MMC Receive UDP Error Frame Counter Interrupt Status
 * This bit is set when the rxudp_err_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXUDPERFIS_MASK (0x200U)
#define ENET_MMC_IPC_INTR_RX_RXUDPERFIS_SHIFT (9U)
#define ENET_MMC_IPC_INTR_RX_RXUDPERFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXUDPERFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXUDPERFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXUDPERFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXUDPERFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXUDPERFIS_SHIFT)

/*
 * RXUDPGFIS (RW)
 *
 * MMC Receive UDP Good Frame Counter Interrupt Status
 * This bit is set when the rxudp_gd_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXUDPGFIS_MASK (0x100U)
#define ENET_MMC_IPC_INTR_RX_RXUDPGFIS_SHIFT (8U)
#define ENET_MMC_IPC_INTR_RX_RXUDPGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXUDPGFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXUDPGFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXUDPGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXUDPGFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXUDPGFIS_SHIFT)

/*
 * RXIPV6NOPAYFIS (RW)
 *
 * MMC Receive IPV6 No Payload Frame Counter Interrupt Status
 * This bit is set when the rxipv6_nopay_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYFIS_MASK (0x80U)
#define ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYFIS_SHIFT (7U)
#define ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV6NOPAYFIS_SHIFT)

/*
 * RXIPV6HERFIS (RW)
 *
 * MMC Receive IPV6 Header Error Frame Counter Interrupt Status
 * This bit is set when the rxipv6_hdrerr_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV6HERFIS_MASK (0x40U)
#define ENET_MMC_IPC_INTR_RX_RXIPV6HERFIS_SHIFT (6U)
#define ENET_MMC_IPC_INTR_RX_RXIPV6HERFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV6HERFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV6HERFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV6HERFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV6HERFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV6HERFIS_SHIFT)

/*
 * RXIPV6GFIS (RW)
 *
 * MMC Receive IPV6 Good Frame Counter Interrupt Status
 * This bit is set when the rxipv6_gd_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV6GFIS_MASK (0x20U)
#define ENET_MMC_IPC_INTR_RX_RXIPV6GFIS_SHIFT (5U)
#define ENET_MMC_IPC_INTR_RX_RXIPV6GFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV6GFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV6GFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV6GFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV6GFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV6GFIS_SHIFT)

/*
 * RXIPV4UDSBLFIS (RW)
 *
 * MMC Receive IPV4 UDP Checksum Disabled Frame Counter Interrupt Status
 * This bit is set when the rxipv4_udsbl_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLFIS_MASK (0x10U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLFIS_SHIFT (4U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV4UDSBLFIS_SHIFT)

/*
 * RXIPV4FRAGFIS (RW)
 *
 * MMC Receive IPV4 Fragmented Frame Counter Interrupt Status
 * This bit is set when the rxipv4_frag_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV4FRAGFIS_MASK (0x8U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4FRAGFIS_SHIFT (3U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4FRAGFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV4FRAGFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV4FRAGFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV4FRAGFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV4FRAGFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV4FRAGFIS_SHIFT)

/*
 * RXIPV4NOPAYFIS (RW)
 *
 * MMC Receive IPV4 No Payload Frame Counter Interrupt Status
 * This bit is set when the rxipv4_nopay_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYFIS_MASK (0x4U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYFIS_SHIFT (2U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV4NOPAYFIS_SHIFT)

/*
 * RXIPV4HERFIS (RW)
 *
 * MMC Receive IPV4 Header Error Frame Counter Interrupt Status
 * This bit is set when the rxipv4_hdrerr_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV4HERFIS_MASK (0x2U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4HERFIS_SHIFT (1U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4HERFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV4HERFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV4HERFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV4HERFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV4HERFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV4HERFIS_SHIFT)

/*
 * RXIPV4GFIS (RW)
 *
 * MMC Receive IPV4 Good Frame Counter Interrupt Status
 * This bit is set when the rxipv4_gd_frms counter reaches half of the maximum value or the maximum value.
 */
#define ENET_MMC_IPC_INTR_RX_RXIPV4GFIS_MASK (0x1U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4GFIS_SHIFT (0U)
#define ENET_MMC_IPC_INTR_RX_RXIPV4GFIS_SET(x) (((uint32_t)(x) << ENET_MMC_IPC_INTR_RX_RXIPV4GFIS_SHIFT) & ENET_MMC_IPC_INTR_RX_RXIPV4GFIS_MASK)
#define ENET_MMC_IPC_INTR_RX_RXIPV4GFIS_GET(x) (((uint32_t)(x) & ENET_MMC_IPC_INTR_RX_RXIPV4GFIS_MASK) >> ENET_MMC_IPC_INTR_RX_RXIPV4GFIS_SHIFT)

/* Bitfield definition for register: RXIPV4_GD_FMS */
/*
 * FRMCNT (RW)
 *
 * Number of good IPv4 datagrams received with the TCP, UDP, or ICMP payload
 */
#define ENET_RXIPV4_GD_FMS_FRMCNT_MASK (0xFFFFFFFFUL)
#define ENET_RXIPV4_GD_FMS_FRMCNT_SHIFT (0U)
#define ENET_RXIPV4_GD_FMS_FRMCNT_SET(x) (((uint32_t)(x) << ENET_RXIPV4_GD_FMS_FRMCNT_SHIFT) & ENET_RXIPV4_GD_FMS_FRMCNT_MASK)
#define ENET_RXIPV4_GD_FMS_FRMCNT_GET(x) (((uint32_t)(x) & ENET_RXIPV4_GD_FMS_FRMCNT_MASK) >> ENET_RXIPV4_GD_FMS_FRMCNT_SHIFT)

/* Bitfield definition for register of struct array L3_L4_CFG: L3_L4_CTRL */
/*
 * L4DPIM0 (RW)
 *
 * Layer 4 Destination Port Inverse Match Enable
 *  When set, this bit indicates that the Layer 4 Destination Port number field is enabled for inverse matching.
 * When reset, this bit indicates that the Layer 4 Destination Port number field is enabled for perfect matching.
 *  This bit is valid and applicable only when Bit 20 (L4DPM0) is set high.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4DPIM0_MASK (0x200000UL)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4DPIM0_SHIFT (21U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4DPIM0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L4DPIM0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L4DPIM0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4DPIM0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L4DPIM0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L4DPIM0_SHIFT)

/*
 * L4DPM0 (RW)
 *
 * Layer 4 Destination Port Match Enable
 *  When set, this bit indicates that the Layer 4 Destination Port number field is enabled for matching.
 * When reset, the MAC ignores the Layer 4 Destination Port number field for matching.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4DPM0_MASK (0x100000UL)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4DPM0_SHIFT (20U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4DPM0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L4DPM0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L4DPM0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4DPM0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L4DPM0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L4DPM0_SHIFT)

/*
 * L4SPIM0 (RW)
 *
 * Layer 4 Source Port Inverse Match Enable
 * When set, this bit indicates that the Layer 4 Source Port number field is enabled for inverse matching.
 * When reset, this bit indicates that the Layer 4 Source Port number field is enabled for perfect matching.
 * This bit is valid and applicable only when Bit 18 (L4SPM0) is set high.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4SPIM0_MASK (0x80000UL)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4SPIM0_SHIFT (19U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4SPIM0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L4SPIM0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L4SPIM0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4SPIM0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L4SPIM0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L4SPIM0_SHIFT)

/*
 * L4SPM0 (RW)
 *
 * Layer 4 Source Port Match Enable
 * When set, this bit indicates that the Layer 4 Source Port number field is enabled for matching. When reset, the MAC ignores the Layer 4 Source Port number field for matching.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4SPM0_MASK (0x40000UL)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4SPM0_SHIFT (18U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4SPM0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L4SPM0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L4SPM0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4SPM0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L4SPM0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L4SPM0_SHIFT)

/*
 * L4PEN0 (RW)
 *
 * Layer 4 Protocol Enable
 * When set, this bit indicates that the Source and Destination Port number fields for UDP frames are used for matching.
 * When reset, this bit indicates that the Source and Destination Port number fields for TCP frames are used for matching.
 * The Layer 4 matching is done only when either L4SPM0 or L4DPM0 bit is set high.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4PEN0_MASK (0x10000UL)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4PEN0_SHIFT (16U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4PEN0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L4PEN0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L4PEN0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L4PEN0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L4PEN0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L4PEN0_SHIFT)

/*
 * L3HDBM0 (RW)
 *
 * Layer 3 IP DA Higher Bits Match
 *  IPv4 Frames: This field contains the number of higher bits of IP Destination Address that are matched in the IPv4 frames. The following list describes the values of this field:
 * - 0: No bits are masked.
 * - 1: LSb[0] is masked.
 * - 2: Two LSbs [1:0] are masked. - ...
 * - 31: All bits except MSb are masked. IPv6 Frames: Bits [12:11] of this field correspond to Bits [6:5] of L3HSBM0,
 * which indicate the number of lower bits of IP Source or Destination Address that are masked in the IPv6 frames.
 * The following list describes the concatenated values of the L3HDBM0[1:0] and L3HSBM0 bits:
 * - 0: No bits are masked.
 * - 1: LSb[0] is masked.
 * - 2: Two LSbs [1:0] are masked. - …
 * - 127: All bits except MSb are masked. This field is valid and applicable only if L3DAM0 or L3SAM0 is set high.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3HDBM0_MASK (0xF800U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3HDBM0_SHIFT (11U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3HDBM0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L3HDBM0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L3HDBM0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3HDBM0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L3HDBM0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L3HDBM0_SHIFT)

/*
 * L3HSBM0 (RW)
 *
 * Layer 3 IP SA Higher Bits Match
 *  IPv4 Frames: This field contains the number of lower bits of IP Source Address that are masked for matching in the IPv4 frames. The following list describes the values of this field:
 * - 0: No bits are masked.
 * - 1: LSb[0] is masked.
 * - 2: Two LSbs [1:0] are masked. - ...
 * - 31: All bits except MSb are masked. IPv6 Frames: This field contains Bits [4:0] of the field that indicates the number of higher bits of IP Source or Destination Address matched in the IPv6 frames.
 * This field is valid and applicable only if L3DAM0 or L3SAM0 is set high.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3HSBM0_MASK (0x7C0U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3HSBM0_SHIFT (6U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3HSBM0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L3HSBM0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L3HSBM0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3HSBM0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L3HSBM0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L3HSBM0_SHIFT)

/*
 * L3DAIM0 (RW)
 *
 * Layer 3 IP DA Inverse Match Enable
 * When set, this bit indicates that the Layer 3 IP Destination Address field is enabled for inverse matching.
 * When reset, this bit indicates that the Layer 3 IP Destination Address field is enabled for perfect matching. This bit is valid and applicable only when Bit 4 (L3DAM0) is set high.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3DAIM0_MASK (0x20U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3DAIM0_SHIFT (5U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3DAIM0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L3DAIM0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L3DAIM0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3DAIM0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L3DAIM0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L3DAIM0_SHIFT)

/*
 * L3DAM0 (RW)
 *
 * Layer 3 IP DA Match Enable
 * When set, this bit indicates that Layer 3 IP Destination Address field is enabled for matching. When reset, the MAC ignores the Layer 3 IP Destination Address field for matching.
 * Note: When Bit 0 (L3PEN0) is set, you should set either this bit or Bit 2 (L3SAM0) because either IPv6 DA or SA can be checked for filtering.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3DAM0_MASK (0x10U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3DAM0_SHIFT (4U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3DAM0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L3DAM0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L3DAM0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3DAM0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L3DAM0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L3DAM0_SHIFT)

/*
 * L3SAIM0 (RW)
 *
 * Layer 3 IP SA Inverse Match Enable
 * When set, this bit indicates that the Layer 3 IP Source Address field is enabled for inverse matching. When reset, this bit indicates that the Layer 3 IP Source Address field is enabled for perfect matching.
 * This bit is valid and applicable only when Bit 2 (L3SAM0) is set high.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3SAIM0_MASK (0x8U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3SAIM0_SHIFT (3U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3SAIM0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L3SAIM0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L3SAIM0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3SAIM0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L3SAIM0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L3SAIM0_SHIFT)

/*
 * L3SAM0 (RW)
 *
 * Layer 3 IP SA Match Enable
 * When set, this bit indicates that the Layer 3 IP Source Address field is enabled for matching. When reset, the MAC ignores the Layer 3 IP Source Address field for matching.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3SAM0_MASK (0x4U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3SAM0_SHIFT (2U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3SAM0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L3SAM0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L3SAM0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3SAM0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L3SAM0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L3SAM0_SHIFT)

/*
 * L3PEN0 (RW)
 *
 * Layer 3 Protocol Enable
 *  When set, this bit indicates that the Layer 3 IP Source or Destination Address matching is enabled for the IPv6 frames.
 * When reset, this bit indicates that the Layer 3 IP Source or Destination Address matching is enabled for the IPv4 frames.
 * The Layer 3 matching is done only when either L3SAM0 or L3DAM0 bit is set high.
 */
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3PEN0_MASK (0x1U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3PEN0_SHIFT (0U)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3PEN0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_L4_CTRL_L3PEN0_SHIFT) & ENET_L3_L4_CFG_L3_L4_CTRL_L3PEN0_MASK)
#define ENET_L3_L4_CFG_L3_L4_CTRL_L3PEN0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_L4_CTRL_L3PEN0_MASK) >> ENET_L3_L4_CFG_L3_L4_CTRL_L3PEN0_SHIFT)

/* Bitfield definition for register of struct array L3_L4_CFG: L4_ADDR */
/*
 * L4DP0 (RW)
 *
 * Layer 4 Destination Port Number Field
 * When Bit 16 (L4PEN0) is reset and Bit 20 (L4DPM0) is set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains the value to be matched with the TCP Destination Port Number field in the IPv4 or IPv6 frames.
 * When Bit 16 (L4PEN0) and Bit 20 (L4DPM0) are set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains the value to be matched with the UDP Destination Port Number field in the IPv4 or IPv6 frames.
 */
#define ENET_L3_L4_CFG_L4_ADDR_L4DP0_MASK (0xFFFF0000UL)
#define ENET_L3_L4_CFG_L4_ADDR_L4DP0_SHIFT (16U)
#define ENET_L3_L4_CFG_L4_ADDR_L4DP0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L4_ADDR_L4DP0_SHIFT) & ENET_L3_L4_CFG_L4_ADDR_L4DP0_MASK)
#define ENET_L3_L4_CFG_L4_ADDR_L4DP0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L4_ADDR_L4DP0_MASK) >> ENET_L3_L4_CFG_L4_ADDR_L4DP0_SHIFT)

/*
 * L4SP0 (RW)
 *
 * Layer 4 Source Port Number Field
 *  When Bit 16 (L4PEN0) is reset and Bit 20 (L4DPM0) is set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 *  this field contains the value to be matched with the TCP Source Port Number field in the IPv4 or IPv6 frames.
 * When Bit 16 (L4PEN0) and Bit 20 (L4DPM0) are set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains the value to be matched with the UDP Source Port Number field in the IPv4 or IPv6 frames.
 */
#define ENET_L3_L4_CFG_L4_ADDR_L4SP0_MASK (0xFFFFU)
#define ENET_L3_L4_CFG_L4_ADDR_L4SP0_SHIFT (0U)
#define ENET_L3_L4_CFG_L4_ADDR_L4SP0_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L4_ADDR_L4SP0_SHIFT) & ENET_L3_L4_CFG_L4_ADDR_L4SP0_MASK)
#define ENET_L3_L4_CFG_L4_ADDR_L4SP0_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L4_ADDR_L4SP0_MASK) >> ENET_L3_L4_CFG_L4_ADDR_L4SP0_SHIFT)

/* Bitfield definition for register of struct array L3_L4_CFG: L3_ADDR_0 */
/*
 * L3A00 (RW)
 *
 * Layer 3 Address 0 Field
 *  When Bit 0 (L3PEN0) and Bit 2 (L3SAM0) are set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains the value to be matched with Bits [31:0] of the IP Source Address field in the IPv6 frames.
 * When Bit 0 (L3PEN0) and Bit 4 (L3DAM0) are set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains the value to be matched with Bits [31:0] of the IP Destination Address field in the IPv6 frames.
 * When Bit 0 (L3PEN0) is reset and Bit 2 (L3SAM0) is set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains the value to be matched with the IP Source Address field in the IPv4 frames.
 */
#define ENET_L3_L4_CFG_L3_ADDR_0_L3A00_MASK (0xFFFFFFFFUL)
#define ENET_L3_L4_CFG_L3_ADDR_0_L3A00_SHIFT (0U)
#define ENET_L3_L4_CFG_L3_ADDR_0_L3A00_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_ADDR_0_L3A00_SHIFT) & ENET_L3_L4_CFG_L3_ADDR_0_L3A00_MASK)
#define ENET_L3_L4_CFG_L3_ADDR_0_L3A00_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_ADDR_0_L3A00_MASK) >> ENET_L3_L4_CFG_L3_ADDR_0_L3A00_SHIFT)

/* Bitfield definition for register of struct array L3_L4_CFG: L3_ADDR_1 */
/*
 * L3A10 (RW)
 *
 * Layer 3 Address 1 Field
 *  When Bit 0 (L3PEN0) and Bit 2 (L3SAM0) are set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains the value to be matched with Bits [63:32] of the IP Source Address field in the IPv6 frames.
 * When Bit 0 (L3PEN0) and Bit 4 (L3DAM0) are set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains the value to be matched with Bits [63:32] of the IP Destination Address field in the IPv6 frames.
 * When Bit 0 (L3PEN0) is reset and Bit 4 (L3DAM0) is set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 *  this field contains the value to be matched with the IP Destination Address field in the IPv4 frames.
 */
#define ENET_L3_L4_CFG_L3_ADDR_1_L3A10_MASK (0xFFFFFFFFUL)
#define ENET_L3_L4_CFG_L3_ADDR_1_L3A10_SHIFT (0U)
#define ENET_L3_L4_CFG_L3_ADDR_1_L3A10_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_ADDR_1_L3A10_SHIFT) & ENET_L3_L4_CFG_L3_ADDR_1_L3A10_MASK)
#define ENET_L3_L4_CFG_L3_ADDR_1_L3A10_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_ADDR_1_L3A10_MASK) >> ENET_L3_L4_CFG_L3_ADDR_1_L3A10_SHIFT)

/* Bitfield definition for register of struct array L3_L4_CFG: L3_ADDR_2 */
/*
 * L3A20 (RW)
 *
 * Layer 3 Address 2 Field
 *  When Bit 0 (L3PEN0) and Bit 2 (L3SAM0) are set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains the value to be matched with Bits [95:64] of the IP Source Address field in the IPv6 frames.
 * When Bit 0 (L3PEN0) and Bit 4 (L3DAM0) are set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains value to be matched with Bits [95:64] of the IP Destination Address field in the IPv6 frames.
 * When Bit 0 (L3PEN0) is reset in Register 256 (Layer 3 and Layer 4 Control Register 0), this register is not used.
 */
#define ENET_L3_L4_CFG_L3_ADDR_2_L3A20_MASK (0xFFFFFFFFUL)
#define ENET_L3_L4_CFG_L3_ADDR_2_L3A20_SHIFT (0U)
#define ENET_L3_L4_CFG_L3_ADDR_2_L3A20_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_ADDR_2_L3A20_SHIFT) & ENET_L3_L4_CFG_L3_ADDR_2_L3A20_MASK)
#define ENET_L3_L4_CFG_L3_ADDR_2_L3A20_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_ADDR_2_L3A20_MASK) >> ENET_L3_L4_CFG_L3_ADDR_2_L3A20_SHIFT)

/* Bitfield definition for register of struct array L3_L4_CFG: L3_ADDR_3 */
/*
 * L3A30 (RW)
 *
 * Layer 3 Address 3 Field When Bit 0 (L3PEN0) and Bit 2 (L3SAM0) are set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains the value to be matched with Bits [127:96] of the IP Source Address field in the IPv6 frames.
 *  When Bit 0 (L3PEN0) and Bit 4 (L3DAM0) are set in Register 256 (Layer 3 and Layer 4 Control Register 0),
 * this field contains the value to be matched with Bits [127:96] of the IP Destination Address field in the IPv6 frames.
 * When Bit 0 (L3PEN0) is reset in Register 256 (Layer 3 and Layer 4 Control Register 0), this register is not used.
 */
#define ENET_L3_L4_CFG_L3_ADDR_3_L3A30_MASK (0xFFFFFFFFUL)
#define ENET_L3_L4_CFG_L3_ADDR_3_L3A30_SHIFT (0U)
#define ENET_L3_L4_CFG_L3_ADDR_3_L3A30_SET(x) (((uint32_t)(x) << ENET_L3_L4_CFG_L3_ADDR_3_L3A30_SHIFT) & ENET_L3_L4_CFG_L3_ADDR_3_L3A30_MASK)
#define ENET_L3_L4_CFG_L3_ADDR_3_L3A30_GET(x) (((uint32_t)(x) & ENET_L3_L4_CFG_L3_ADDR_3_L3A30_MASK) >> ENET_L3_L4_CFG_L3_ADDR_3_L3A30_SHIFT)

/* Bitfield definition for register: VLAN_TAG_INC_RPL */
/*
 * CSVL (RW)
 *
 * C-VLAN or S-VLAN
 *  When this bit is set, S-VLAN type (0x88A8) is inserted or replaced in the 13th and 14th bytes of transmitted frames. When this bit is reset, C-VLAN type (0x8100) is inserted or replaced in the transmitted frames.
 */
#define ENET_VLAN_TAG_INC_RPL_CSVL_MASK (0x80000UL)
#define ENET_VLAN_TAG_INC_RPL_CSVL_SHIFT (19U)
#define ENET_VLAN_TAG_INC_RPL_CSVL_SET(x) (((uint32_t)(x) << ENET_VLAN_TAG_INC_RPL_CSVL_SHIFT) & ENET_VLAN_TAG_INC_RPL_CSVL_MASK)
#define ENET_VLAN_TAG_INC_RPL_CSVL_GET(x) (((uint32_t)(x) & ENET_VLAN_TAG_INC_RPL_CSVL_MASK) >> ENET_VLAN_TAG_INC_RPL_CSVL_SHIFT)

/*
 * VLP (RW)
 *
 * VLAN Priority Control
 * When this bit is set, the control Bits [17:16] are used for VLAN deletion, insertion, or replacement. When this bit is reset, the mti_vlan_ctrl_i control input is used, and Bits [17:16] are ignored.
 */
#define ENET_VLAN_TAG_INC_RPL_VLP_MASK (0x40000UL)
#define ENET_VLAN_TAG_INC_RPL_VLP_SHIFT (18U)
#define ENET_VLAN_TAG_INC_RPL_VLP_SET(x) (((uint32_t)(x) << ENET_VLAN_TAG_INC_RPL_VLP_SHIFT) & ENET_VLAN_TAG_INC_RPL_VLP_MASK)
#define ENET_VLAN_TAG_INC_RPL_VLP_GET(x) (((uint32_t)(x) & ENET_VLAN_TAG_INC_RPL_VLP_MASK) >> ENET_VLAN_TAG_INC_RPL_VLP_SHIFT)

/*
 * VLC (RW)
 *
 * VLAN Tag Control in Transmit Frames
 * - 2’b00: No VLAN tag deletion, insertion, or replacement
 * - 2’b01: VLAN tag deletion The MAC removes the VLAN type (bytes 13 and 14) and VLAN tag (bytes 15 and 16) of all transmitted frames with VLAN tags.
 * - 2’b10: VLAN tag insertion The MAC inserts VLT in bytes 15 and 16 of the frame after inserting the Type value (0x8100/0x88a8) in bytes 13 and 14.
 * This operation is performed on all transmitted frames, irrespective of whether they already have a VLAN tag.
 * - 2’b11: VLAN tag replacement The MAC replaces VLT in bytes 15 and 16 of all VLAN-type transmitted frames (Bytes 13 and 14 are 0x8100/0x88a8).
 * Note: Changes to this field take effect only on the start of a frame.
 * If you write this register field when a frame is being transmitted, only the subsequent frame can use the updated value, that is, the current frame does not use the updated value.
 */
#define ENET_VLAN_TAG_INC_RPL_VLC_MASK (0x30000UL)
#define ENET_VLAN_TAG_INC_RPL_VLC_SHIFT (16U)
#define ENET_VLAN_TAG_INC_RPL_VLC_SET(x) (((uint32_t)(x) << ENET_VLAN_TAG_INC_RPL_VLC_SHIFT) & ENET_VLAN_TAG_INC_RPL_VLC_MASK)
#define ENET_VLAN_TAG_INC_RPL_VLC_GET(x) (((uint32_t)(x) & ENET_VLAN_TAG_INC_RPL_VLC_MASK) >> ENET_VLAN_TAG_INC_RPL_VLC_SHIFT)

/*
 * VLT (RW)
 *
 * VLAN Tag for Transmit Frames
 *  This field contains the value of the VLAN tag to be inserted or replaced. The value must only be changed when the transmit lines are inactive or during the initialization phase.
 *  Bits[15:13] are the User Priority, Bit 12 is the CFI/DEI, and Bits[11:0] are the VLAN tag’s VID field.
 */
#define ENET_VLAN_TAG_INC_RPL_VLT_MASK (0xFFFFU)
#define ENET_VLAN_TAG_INC_RPL_VLT_SHIFT (0U)
#define ENET_VLAN_TAG_INC_RPL_VLT_SET(x) (((uint32_t)(x) << ENET_VLAN_TAG_INC_RPL_VLT_SHIFT) & ENET_VLAN_TAG_INC_RPL_VLT_MASK)
#define ENET_VLAN_TAG_INC_RPL_VLT_GET(x) (((uint32_t)(x) & ENET_VLAN_TAG_INC_RPL_VLT_MASK) >> ENET_VLAN_TAG_INC_RPL_VLT_SHIFT)

/* Bitfield definition for register: VLAN_HASH */
/*
 * VLHT (RW)
 *
 * VLAN Hash Table
 *  This field contains the 16-bit VLAN Hash Table.
 */
#define ENET_VLAN_HASH_VLHT_MASK (0xFFFFU)
#define ENET_VLAN_HASH_VLHT_SHIFT (0U)
#define ENET_VLAN_HASH_VLHT_SET(x) (((uint32_t)(x) << ENET_VLAN_HASH_VLHT_SHIFT) & ENET_VLAN_HASH_VLHT_MASK)
#define ENET_VLAN_HASH_VLHT_GET(x) (((uint32_t)(x) & ENET_VLAN_HASH_VLHT_MASK) >> ENET_VLAN_HASH_VLHT_SHIFT)

/* Bitfield definition for register: TS_CTRL */
/*
 * ATSEN3 (RW)
 *
 * Auxiliary Snapshot 3 Enable
 * This field controls capturing the Auxiliary Snapshot Trigger 3. When this bit is set, the Auxiliary snapshot of event on ptp_aux_trig_i[3] input is enabled. When this bit is reset, the events on this input are ignored.
 * This bit is reserved when the Add IEEE 1588 Auxiliary Snapshot option is not selected during core configuration or the selected number in the Number of IEEE 1588 Auxiliary Snapshot Inputs option is less than four.
 */
#define ENET_TS_CTRL_ATSEN3_MASK (0x10000000UL)
#define ENET_TS_CTRL_ATSEN3_SHIFT (28U)
#define ENET_TS_CTRL_ATSEN3_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_ATSEN3_SHIFT) & ENET_TS_CTRL_ATSEN3_MASK)
#define ENET_TS_CTRL_ATSEN3_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_ATSEN3_MASK) >> ENET_TS_CTRL_ATSEN3_SHIFT)

/*
 * ATSEN2 (RW)
 *
 * Auxiliary Snapshot 2 Enable
 * This field controls capturing the Auxiliary Snapshot Trigger 2. When this bit is set, the Auxiliary snapshot of event on ptp_aux_trig_i[2] input is enabled. When this bit is reset, the events on this input are ignored.
 * This bit is reserved when the Add IEEE 1588 Auxiliary Snapshot option is not selected during core configuration or the selected number in the Number of IEEE 1588 Auxiliary Snapshot Inputs option is less than three.
 */
#define ENET_TS_CTRL_ATSEN2_MASK (0x8000000UL)
#define ENET_TS_CTRL_ATSEN2_SHIFT (27U)
#define ENET_TS_CTRL_ATSEN2_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_ATSEN2_SHIFT) & ENET_TS_CTRL_ATSEN2_MASK)
#define ENET_TS_CTRL_ATSEN2_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_ATSEN2_MASK) >> ENET_TS_CTRL_ATSEN2_SHIFT)

/*
 * ATSEN1 (RW)
 *
 * Auxiliary Snapshot 1 Enable
 * This field controls capturing the Auxiliary Snapshot Trigger 1. When this bit is set, the Auxiliary snapshot of event on ptp_aux_trig_i[1] input is enabled. When this bit is reset, the events on this input are ignored.
 * This bit is reserved when the Add IEEE 1588 Auxiliary Snapshot option is not selected during core configuration or the selected number in the Number of IEEE 1588 Auxiliary Snapshot Inputs option is less than two.
 */
#define ENET_TS_CTRL_ATSEN1_MASK (0x4000000UL)
#define ENET_TS_CTRL_ATSEN1_SHIFT (26U)
#define ENET_TS_CTRL_ATSEN1_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_ATSEN1_SHIFT) & ENET_TS_CTRL_ATSEN1_MASK)
#define ENET_TS_CTRL_ATSEN1_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_ATSEN1_MASK) >> ENET_TS_CTRL_ATSEN1_SHIFT)

/*
 * ATSEN0 (RW)
 *
 * Auxiliary Snapshot 0 Enable
 * This field controls capturing the Auxiliary Snapshot Trigger 0. When this bit is set, the Auxiliary snapshot of event on ptp_aux_trig_i[0] input is enabled. When this bit is reset, the events on this input are ignored.
 */
#define ENET_TS_CTRL_ATSEN0_MASK (0x2000000UL)
#define ENET_TS_CTRL_ATSEN0_SHIFT (25U)
#define ENET_TS_CTRL_ATSEN0_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_ATSEN0_SHIFT) & ENET_TS_CTRL_ATSEN0_MASK)
#define ENET_TS_CTRL_ATSEN0_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_ATSEN0_MASK) >> ENET_TS_CTRL_ATSEN0_SHIFT)

/*
 * ATSFC (RW)
 *
 * Auxiliary Snapshot FIFO Clear
 * When set, it resets the pointers of the Auxiliary Snapshot FIFO. This bit is cleared when the pointers are reset and the FIFO is empty. When this bit is high, auxiliary snapshots get stored in the FIFO.
 * This bit is reserved when the Add IEEE 1588 Auxiliary Snapshot option is not selected during core configuration.
 */
#define ENET_TS_CTRL_ATSFC_MASK (0x1000000UL)
#define ENET_TS_CTRL_ATSFC_SHIFT (24U)
#define ENET_TS_CTRL_ATSFC_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_ATSFC_SHIFT) & ENET_TS_CTRL_ATSFC_MASK)
#define ENET_TS_CTRL_ATSFC_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_ATSFC_MASK) >> ENET_TS_CTRL_ATSFC_SHIFT)

/*
 * TSENMACADDR (RW)
 *
 * Enable MAC address for PTP Frame Filtering
 * When set, the DA MAC address (that matches any MAC Address register) is used to filter the PTP frames when PTP is directly sent over Ethernet.
 */
#define ENET_TS_CTRL_TSENMACADDR_MASK (0x40000UL)
#define ENET_TS_CTRL_TSENMACADDR_SHIFT (18U)
#define ENET_TS_CTRL_TSENMACADDR_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSENMACADDR_SHIFT) & ENET_TS_CTRL_TSENMACADDR_MASK)
#define ENET_TS_CTRL_TSENMACADDR_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSENMACADDR_MASK) >> ENET_TS_CTRL_TSENMACADDR_SHIFT)

/*
 * SNAPTYPSEL (RW)
 *
 * Select PTP packets for Taking Snapshots
 *  These bits along with Bits 15 and 14 decide the set of PTP packet types for which snapshot needs to be taken.
 */
#define ENET_TS_CTRL_SNAPTYPSEL_MASK (0x30000UL)
#define ENET_TS_CTRL_SNAPTYPSEL_SHIFT (16U)
#define ENET_TS_CTRL_SNAPTYPSEL_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_SNAPTYPSEL_SHIFT) & ENET_TS_CTRL_SNAPTYPSEL_MASK)
#define ENET_TS_CTRL_SNAPTYPSEL_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_SNAPTYPSEL_MASK) >> ENET_TS_CTRL_SNAPTYPSEL_SHIFT)

/*
 * TSMSTRENA (RW)
 *
 * Enable Snapshot for Messages Relevant to Master
 * When set, the snapshot is taken only for the messages relevant to the master node. Otherwise, the snapshot is taken for the messages relevant to the slave node.
 */
#define ENET_TS_CTRL_TSMSTRENA_MASK (0x8000U)
#define ENET_TS_CTRL_TSMSTRENA_SHIFT (15U)
#define ENET_TS_CTRL_TSMSTRENA_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSMSTRENA_SHIFT) & ENET_TS_CTRL_TSMSTRENA_MASK)
#define ENET_TS_CTRL_TSMSTRENA_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSMSTRENA_MASK) >> ENET_TS_CTRL_TSMSTRENA_SHIFT)

/*
 * TSEVNTENA (RW)
 *
 * Enable Timestamp Snapshot for Event Messages
 * When set, the timestamp snapshot is taken only for event messages (SYNC, Delay_Req, Pdelay_Req, or Pdelay_Resp). When reset, the snapshot is taken for all messages except Announce, Management, and Signaling.
 */
#define ENET_TS_CTRL_TSEVNTENA_MASK (0x4000U)
#define ENET_TS_CTRL_TSEVNTENA_SHIFT (14U)
#define ENET_TS_CTRL_TSEVNTENA_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSEVNTENA_SHIFT) & ENET_TS_CTRL_TSEVNTENA_MASK)
#define ENET_TS_CTRL_TSEVNTENA_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSEVNTENA_MASK) >> ENET_TS_CTRL_TSEVNTENA_SHIFT)

/*
 * TSIPV4ENA (RW)
 *
 * Enable Processing of PTP Frames Sent over IPv4-UDP
 *  When set, the MAC receiver processes the PTP packets encapsulated in UDP over IPv4 packets. When this bit is clear, the MAC ignores the PTP transported over UDP-IPv4 packets. This bit is set by default.
 */
#define ENET_TS_CTRL_TSIPV4ENA_MASK (0x2000U)
#define ENET_TS_CTRL_TSIPV4ENA_SHIFT (13U)
#define ENET_TS_CTRL_TSIPV4ENA_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSIPV4ENA_SHIFT) & ENET_TS_CTRL_TSIPV4ENA_MASK)
#define ENET_TS_CTRL_TSIPV4ENA_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSIPV4ENA_MASK) >> ENET_TS_CTRL_TSIPV4ENA_SHIFT)

/*
 * TSIPV6ENA (RW)
 *
 * Enable Processing of PTP Frames Sent over IPv6-UDP
 * When set, the MAC receiver processes PTP packets encapsulated in UDP over IPv6 packets. When this bit is clear, the MAC ignores the PTP transported over UDP-IPv6 packets.
 */
#define ENET_TS_CTRL_TSIPV6ENA_MASK (0x1000U)
#define ENET_TS_CTRL_TSIPV6ENA_SHIFT (12U)
#define ENET_TS_CTRL_TSIPV6ENA_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSIPV6ENA_SHIFT) & ENET_TS_CTRL_TSIPV6ENA_MASK)
#define ENET_TS_CTRL_TSIPV6ENA_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSIPV6ENA_MASK) >> ENET_TS_CTRL_TSIPV6ENA_SHIFT)

/*
 * TSIPENA (RW)
 *
 * Enable Processing of PTP over Ethernet Frames
 * When set, the MAC receiver processes the PTP packets encapsulated directly in the Ethernet frames. When this bit is clear, the MAC ignores the PTP over Ethernet packets
 */
#define ENET_TS_CTRL_TSIPENA_MASK (0x800U)
#define ENET_TS_CTRL_TSIPENA_SHIFT (11U)
#define ENET_TS_CTRL_TSIPENA_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSIPENA_SHIFT) & ENET_TS_CTRL_TSIPENA_MASK)
#define ENET_TS_CTRL_TSIPENA_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSIPENA_MASK) >> ENET_TS_CTRL_TSIPENA_SHIFT)

/*
 * TSVER2ENA (RW)
 *
 * Enable PTP packet Processing for Version 2 Format
 * When set, the PTP packets are processed using the 1588 version 2 format. Otherwise, the PTP packets are processed using the version 1 format.
 */
#define ENET_TS_CTRL_TSVER2ENA_MASK (0x400U)
#define ENET_TS_CTRL_TSVER2ENA_SHIFT (10U)
#define ENET_TS_CTRL_TSVER2ENA_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSVER2ENA_SHIFT) & ENET_TS_CTRL_TSVER2ENA_MASK)
#define ENET_TS_CTRL_TSVER2ENA_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSVER2ENA_MASK) >> ENET_TS_CTRL_TSVER2ENA_SHIFT)

/*
 * TSCTRLSSR (RW)
 *
 * Timestamp Digital or Binary Rollover Control
 * When set, the Timestamp Low register rolls over after 0x3B9A_C9FF value (that is, 1 nanosecond accuracy) and increments the timestamp (High) seconds.
 *  When reset, the rollover value of sub-second register is 0x7FFF_FFFF.
 * The sub-second increment has to be programmed correctly depending on the PTP reference clock frequency and the value of this bit.
 */
#define ENET_TS_CTRL_TSCTRLSSR_MASK (0x200U)
#define ENET_TS_CTRL_TSCTRLSSR_SHIFT (9U)
#define ENET_TS_CTRL_TSCTRLSSR_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSCTRLSSR_SHIFT) & ENET_TS_CTRL_TSCTRLSSR_MASK)
#define ENET_TS_CTRL_TSCTRLSSR_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSCTRLSSR_MASK) >> ENET_TS_CTRL_TSCTRLSSR_SHIFT)

/*
 * TSENALL (RW)
 *
 * Enable Timestamp for All Frames
 * When set, the timestamp snapshot is enabled for all frames received by the MAC.
 */
#define ENET_TS_CTRL_TSENALL_MASK (0x100U)
#define ENET_TS_CTRL_TSENALL_SHIFT (8U)
#define ENET_TS_CTRL_TSENALL_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSENALL_SHIFT) & ENET_TS_CTRL_TSENALL_MASK)
#define ENET_TS_CTRL_TSENALL_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSENALL_MASK) >> ENET_TS_CTRL_TSENALL_SHIFT)

/*
 * TSADDREG (RW)
 *
 * Addend Reg Update
 * When set, the content of the Timestamp Addend register is updated in the PTP block for fine correction. This is cleared when the update is completed.
 * This register bit should be zero before setting it.
 */
#define ENET_TS_CTRL_TSADDREG_MASK (0x20U)
#define ENET_TS_CTRL_TSADDREG_SHIFT (5U)
#define ENET_TS_CTRL_TSADDREG_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSADDREG_SHIFT) & ENET_TS_CTRL_TSADDREG_MASK)
#define ENET_TS_CTRL_TSADDREG_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSADDREG_MASK) >> ENET_TS_CTRL_TSADDREG_SHIFT)

/*
 * TSTRIG (RW)
 *
 * Timestamp Interrupt Trigger Enable
 * When set, the timestamp interrupt is generated when the System Time becomes greater than the value written in the Target Time register.
 * This bit is reset after the generation of the Timestamp Trigger Interrupt.
 */
#define ENET_TS_CTRL_TSTRIG_MASK (0x10U)
#define ENET_TS_CTRL_TSTRIG_SHIFT (4U)
#define ENET_TS_CTRL_TSTRIG_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSTRIG_SHIFT) & ENET_TS_CTRL_TSTRIG_MASK)
#define ENET_TS_CTRL_TSTRIG_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSTRIG_MASK) >> ENET_TS_CTRL_TSTRIG_SHIFT)

/*
 * TSUPDT (RW)
 *
 * Timestamp Update
 * When set, the system time is updated (added or subtracted) with the value specified in Register 452 (System Time – Seconds Update Register)
 * and Register 453 (System Time – Nanoseconds Update Register). This bit should be read zero before updating it.
 * This bit is reset when the update is completed in hardware. The “Timestamp Higher Word” register (if enabled during core configuration) is not updated.
 */
#define ENET_TS_CTRL_TSUPDT_MASK (0x8U)
#define ENET_TS_CTRL_TSUPDT_SHIFT (3U)
#define ENET_TS_CTRL_TSUPDT_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSUPDT_SHIFT) & ENET_TS_CTRL_TSUPDT_MASK)
#define ENET_TS_CTRL_TSUPDT_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSUPDT_MASK) >> ENET_TS_CTRL_TSUPDT_SHIFT)

/*
 * TSINIT (RW)
 *
 * Timestamp Initialize
 * When set, the system time is initialized (overwritten) with the value specified in the Register 452 (System Time – Seconds Update Register)
 * and Register 453 (System Time – Nanoseconds Update Register). This bit should be read zero before updating it.
 * This bit is reset when the initialization is complete.
 * The “Timestamp Higher Word” register (if enabled during core configuration) can only be initialized.
 */
#define ENET_TS_CTRL_TSINIT_MASK (0x4U)
#define ENET_TS_CTRL_TSINIT_SHIFT (2U)
#define ENET_TS_CTRL_TSINIT_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSINIT_SHIFT) & ENET_TS_CTRL_TSINIT_MASK)
#define ENET_TS_CTRL_TSINIT_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSINIT_MASK) >> ENET_TS_CTRL_TSINIT_SHIFT)

/*
 * TSCFUPDT (RW)
 *
 * Timestamp Fine or Coarse Update
 * When set, this bit indicates that the system times update should be done using the fine update method. When reset, it indicates the system timestamp update should be done using the Coarse method.
 */
#define ENET_TS_CTRL_TSCFUPDT_MASK (0x2U)
#define ENET_TS_CTRL_TSCFUPDT_SHIFT (1U)
#define ENET_TS_CTRL_TSCFUPDT_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSCFUPDT_SHIFT) & ENET_TS_CTRL_TSCFUPDT_MASK)
#define ENET_TS_CTRL_TSCFUPDT_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSCFUPDT_MASK) >> ENET_TS_CTRL_TSCFUPDT_SHIFT)

/*
 * TSENA (RW)
 *
 * Timestamp Enable
 * When set, the timestamp is added for the transmit and receive frames. When disabled, timestamp is not added for the transmit and receive frames and the Timestamp Generator is also suspended.
 * You need to initialize the Timestamp (system time) after enabling this mode. On the receive side, the MAC processes the 1588 frames only if this bit is set.
 */
#define ENET_TS_CTRL_TSENA_MASK (0x1U)
#define ENET_TS_CTRL_TSENA_SHIFT (0U)
#define ENET_TS_CTRL_TSENA_SET(x) (((uint32_t)(x) << ENET_TS_CTRL_TSENA_SHIFT) & ENET_TS_CTRL_TSENA_MASK)
#define ENET_TS_CTRL_TSENA_GET(x) (((uint32_t)(x) & ENET_TS_CTRL_TSENA_MASK) >> ENET_TS_CTRL_TSENA_SHIFT)

/* Bitfield definition for register: SUB_SEC_INCR */
/*
 * SSINC (RW)
 *
 * Sub-second Increment Value
 * The value programmed in this field is accumulated every clock cycle (of clk_ptp_i) with the contents of the sub-second register.
 * For example, when PTP clock is 50 MHz (period is 20 ns), you should program 20 (0x14)
 * when the System Time- Nanoseconds register has an accuracy of 1 ns [Bit 9 (TSCTRLSSR) is set in Register 448 (Timestamp Control Register)].
 * When TSCTRLSSR is clear, the Nanoseconds register has a resolution of ~0.465ns.
 * In this case, you should program a value of 43 (0x2B) that is derived by 20ns/0.465.
 */
#define ENET_SUB_SEC_INCR_SSINC_MASK (0xFFU)
#define ENET_SUB_SEC_INCR_SSINC_SHIFT (0U)
#define ENET_SUB_SEC_INCR_SSINC_SET(x) (((uint32_t)(x) << ENET_SUB_SEC_INCR_SSINC_SHIFT) & ENET_SUB_SEC_INCR_SSINC_MASK)
#define ENET_SUB_SEC_INCR_SSINC_GET(x) (((uint32_t)(x) & ENET_SUB_SEC_INCR_SSINC_MASK) >> ENET_SUB_SEC_INCR_SSINC_SHIFT)

/* Bitfield definition for register: SYST_SEC */
/*
 * TSS (RO)
 *
 * Timestamp Second
 *  The value in this field indicates the current value in seconds of the System Time maintained by the MAC.
 */
#define ENET_SYST_SEC_TSS_MASK (0xFFFFFFFFUL)
#define ENET_SYST_SEC_TSS_SHIFT (0U)
#define ENET_SYST_SEC_TSS_GET(x) (((uint32_t)(x) & ENET_SYST_SEC_TSS_MASK) >> ENET_SYST_SEC_TSS_SHIFT)

/* Bitfield definition for register: SYST_NSEC */
/*
 * TSSS (RO)
 *
 * Timestamp Sub Seconds
 *  The value in this field has the sub second representation of time, with an accuracy of 0.46 ns.
 * When Bit 9 (TSCTRLSSR) is set in Register 448 (Timestamp Control Register), each bit represents 1 ns and the maximum value is 0x3B9A_C9FF, after which it rolls-over to zero.
 */
#define ENET_SYST_NSEC_TSSS_MASK (0x7FFFFFFFUL)
#define ENET_SYST_NSEC_TSSS_SHIFT (0U)
#define ENET_SYST_NSEC_TSSS_GET(x) (((uint32_t)(x) & ENET_SYST_NSEC_TSSS_MASK) >> ENET_SYST_NSEC_TSSS_SHIFT)

/* Bitfield definition for register: SYST_SEC_UPD */
/*
 * TSS (RW)
 *
 * Timestamp Second
 *  The value in this field indicates the time in seconds to be initialized or added to the system time.
 */
#define ENET_SYST_SEC_UPD_TSS_MASK (0xFFFFFFFFUL)
#define ENET_SYST_SEC_UPD_TSS_SHIFT (0U)
#define ENET_SYST_SEC_UPD_TSS_SET(x) (((uint32_t)(x) << ENET_SYST_SEC_UPD_TSS_SHIFT) & ENET_SYST_SEC_UPD_TSS_MASK)
#define ENET_SYST_SEC_UPD_TSS_GET(x) (((uint32_t)(x) & ENET_SYST_SEC_UPD_TSS_MASK) >> ENET_SYST_SEC_UPD_TSS_SHIFT)

/* Bitfield definition for register: SYST_NSEC_UPD */
/*
 * ADDSUB (RW)
 *
 * Add or Subtract Time
 *  When this bit is set, the time value is subtracted with the contents of the update register. When this bit is reset, the time value is added with the contents of the update register.
 */
#define ENET_SYST_NSEC_UPD_ADDSUB_MASK (0x80000000UL)
#define ENET_SYST_NSEC_UPD_ADDSUB_SHIFT (31U)
#define ENET_SYST_NSEC_UPD_ADDSUB_SET(x) (((uint32_t)(x) << ENET_SYST_NSEC_UPD_ADDSUB_SHIFT) & ENET_SYST_NSEC_UPD_ADDSUB_MASK)
#define ENET_SYST_NSEC_UPD_ADDSUB_GET(x) (((uint32_t)(x) & ENET_SYST_NSEC_UPD_ADDSUB_MASK) >> ENET_SYST_NSEC_UPD_ADDSUB_SHIFT)

/*
 * TSSS (RW)
 *
 * Timestamp Sub Seconds
 * The value in this field has the sub second representation of time, with an accuracy of 0.46 ns.
 * When Bit 9 (TSCTRLSSR) is set in Register 448 (Timestamp Control Register), each bit represents 1 ns and the programmed value should not exceed 0x3B9A_C9FF.
 */
#define ENET_SYST_NSEC_UPD_TSSS_MASK (0x7FFFFFFFUL)
#define ENET_SYST_NSEC_UPD_TSSS_SHIFT (0U)
#define ENET_SYST_NSEC_UPD_TSSS_SET(x) (((uint32_t)(x) << ENET_SYST_NSEC_UPD_TSSS_SHIFT) & ENET_SYST_NSEC_UPD_TSSS_MASK)
#define ENET_SYST_NSEC_UPD_TSSS_GET(x) (((uint32_t)(x) & ENET_SYST_NSEC_UPD_TSSS_MASK) >> ENET_SYST_NSEC_UPD_TSSS_SHIFT)

/* Bitfield definition for register: TS_ADDEND */
/*
 * TSAR (RW)
 *
 * Timestamp Addend Register
 * This field indicates the 32-bit time value to be added to the Accumulator register to achieve time synchronization.
 */
#define ENET_TS_ADDEND_TSAR_MASK (0xFFFFFFFFUL)
#define ENET_TS_ADDEND_TSAR_SHIFT (0U)
#define ENET_TS_ADDEND_TSAR_SET(x) (((uint32_t)(x) << ENET_TS_ADDEND_TSAR_SHIFT) & ENET_TS_ADDEND_TSAR_MASK)
#define ENET_TS_ADDEND_TSAR_GET(x) (((uint32_t)(x) & ENET_TS_ADDEND_TSAR_MASK) >> ENET_TS_ADDEND_TSAR_SHIFT)

/* Bitfield definition for register: TGTTM_SEC */
/*
 * TSTR (RW)
 *
 * Target Time Seconds Register
 *  This register stores the time in seconds.
 * When the timestamp value matches or exceeds both Target Timestamp registers,
 * then based on Bits [6:5] of Register 459 (PPS Control Register), the MAC starts or stops the PPS signal output and generates an interrupt (if enabled).
 */
#define ENET_TGTTM_SEC_TSTR_MASK (0xFFFFFFFFUL)
#define ENET_TGTTM_SEC_TSTR_SHIFT (0U)
#define ENET_TGTTM_SEC_TSTR_SET(x) (((uint32_t)(x) << ENET_TGTTM_SEC_TSTR_SHIFT) & ENET_TGTTM_SEC_TSTR_MASK)
#define ENET_TGTTM_SEC_TSTR_GET(x) (((uint32_t)(x) & ENET_TGTTM_SEC_TSTR_MASK) >> ENET_TGTTM_SEC_TSTR_SHIFT)

/* Bitfield definition for register: TGTTM_NSEC */
/*
 * TRGTBUSY (RW)
 *
 * Target Time Register Busy
 *  The MAC sets this bit when the PPSCMD field (Bit [3:0]) in Register 459 (PPS Control Register) is programmed to 010 or 011.
 * Programming the PPSCMD field to 010 or 011, instructs the MAC to synchronize the Target Time Registers to the PTP clock domain.
 * The MAC clears this bit after synchronizing the Target Time Registers to the PTP clock domain
 * The application must not update the Target Time Registers when this bit is read as 1.
 * Otherwise, the synchronization of the previous programmed time gets corrupted. This bit is reserved when the Enable Flexible Pulse-Per-Second Output feature is not selected.
 */
#define ENET_TGTTM_NSEC_TRGTBUSY_MASK (0x80000000UL)
#define ENET_TGTTM_NSEC_TRGTBUSY_SHIFT (31U)
#define ENET_TGTTM_NSEC_TRGTBUSY_SET(x) (((uint32_t)(x) << ENET_TGTTM_NSEC_TRGTBUSY_SHIFT) & ENET_TGTTM_NSEC_TRGTBUSY_MASK)
#define ENET_TGTTM_NSEC_TRGTBUSY_GET(x) (((uint32_t)(x) & ENET_TGTTM_NSEC_TRGTBUSY_MASK) >> ENET_TGTTM_NSEC_TRGTBUSY_SHIFT)

/*
 * TTSLO (RW)
 *
 * Target Timestamp Low Register
 * This register stores the time in (signed) nanoseconds.
 * When the value of the timestamp matches the both Target Timestamp registers,
 * then based on the TRGTMODSEL0 field (Bits [6:5]) in Register 459 (PPS Control Register),
 * the MAC starts or stops the PPS signal output and generates an interrupt (if enabled).
 * This value should not exceed 0x3B9A_C9FF when Bit 9 (TSCTRLSSR) is set in Register 448 (Timestamp Control Register).
 * The actual start or stop time of the PPS signal output may have an error margin up to one unit of sub-second increment value.
 */
#define ENET_TGTTM_NSEC_TTSLO_MASK (0x7FFFFFFFUL)
#define ENET_TGTTM_NSEC_TTSLO_SHIFT (0U)
#define ENET_TGTTM_NSEC_TTSLO_SET(x) (((uint32_t)(x) << ENET_TGTTM_NSEC_TTSLO_SHIFT) & ENET_TGTTM_NSEC_TTSLO_MASK)
#define ENET_TGTTM_NSEC_TTSLO_GET(x) (((uint32_t)(x) & ENET_TGTTM_NSEC_TTSLO_MASK) >> ENET_TGTTM_NSEC_TTSLO_SHIFT)

/* Bitfield definition for register: SYSTM_H_SEC */
/*
 * TSHWR (RW)
 *
 * Timestamp Higher Word Register
 * This field contains the most significant 16-bits of the timestamp seconds value. This register is optional and can be selected using the Enable IEEE 1588 Higher Word Register option during core configuration.
 * The register is directly written to initialize the value. This register is incremented when there is an overflow from the 32-bits of the System Time - Seconds register.
 */
#define ENET_SYSTM_H_SEC_TSHWR_MASK (0xFFFFU)
#define ENET_SYSTM_H_SEC_TSHWR_SHIFT (0U)
#define ENET_SYSTM_H_SEC_TSHWR_SET(x) (((uint32_t)(x) << ENET_SYSTM_H_SEC_TSHWR_SHIFT) & ENET_SYSTM_H_SEC_TSHWR_MASK)
#define ENET_SYSTM_H_SEC_TSHWR_GET(x) (((uint32_t)(x) & ENET_SYSTM_H_SEC_TSHWR_MASK) >> ENET_SYSTM_H_SEC_TSHWR_SHIFT)

/* Bitfield definition for register: TS_STATUS */
/*
 * ATSNS (RO)
 *
 * Number of Auxiliary Timestamp Snapshots
 * This field indicates the number of Snapshots available in the FIFO. A value equal to the selected depth of FIFO (4, 8, or 16) indicates that the Auxiliary Snapshot FIFO is full.
 * These bits are cleared (to 00000) when the Auxiliary snapshot FIFO clear bit is set.
 * This bit is valid only if the Add IEEE 1588 Auxiliary Snapshot option is selected during core configuration.
 */
#define ENET_TS_STATUS_ATSNS_MASK (0x3E000000UL)
#define ENET_TS_STATUS_ATSNS_SHIFT (25U)
#define ENET_TS_STATUS_ATSNS_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_ATSNS_MASK) >> ENET_TS_STATUS_ATSNS_SHIFT)

/*
 * ATSSTM (RO)
 *
 * Auxiliary Timestamp Snapshot Trigger Missed
 *  This bit is set when the Auxiliary timestamp snapshot FIFO is full and external trigger was set.
 * This indicates that the latest snapshot is not stored in the FIFO. This bit is valid only if the Add IEEE 1588 Auxiliary Snapshot option is selected during core configuration.
 */
#define ENET_TS_STATUS_ATSSTM_MASK (0x1000000UL)
#define ENET_TS_STATUS_ATSSTM_SHIFT (24U)
#define ENET_TS_STATUS_ATSSTM_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_ATSSTM_MASK) >> ENET_TS_STATUS_ATSSTM_SHIFT)

/*
 * ATSSTN (RO)
 *
 * Auxiliary Timestamp Snapshot Trigger Identifier
 * These bits identify the Auxiliary trigger inputs for which the timestamp available in the Auxiliary Snapshot Register is applicable.
 * When more than one bit is set at the same time, it means that corresponding auxiliary triggers were sampled at the same clock.
 * These bits are applicable only if the number of Auxiliary snapshots is more than one.
 * One bit is assigned for each trigger as shown in the following list:
 * - Bit 16: Auxiliary trigger 0
 * - Bit 17: Auxiliary trigger 1
 * - Bit 18: Auxiliary trigger 2
 * - Bit 19: Auxiliary trigger 3
 *  The software can read this register to find the triggers that are set when the timestamp is taken.
 */
#define ENET_TS_STATUS_ATSSTN_MASK (0xF0000UL)
#define ENET_TS_STATUS_ATSSTN_SHIFT (16U)
#define ENET_TS_STATUS_ATSSTN_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_ATSSTN_MASK) >> ENET_TS_STATUS_ATSSTN_SHIFT)

/*
 * TSTRGTERR3 (RO)
 *
 * Timestamp Target Time Error
 * This bit is set when the target time, being programmed in Register 496 and Register 497, is already elapsed. This bit is cleared when read by the application.
 */
#define ENET_TS_STATUS_TSTRGTERR3_MASK (0x200U)
#define ENET_TS_STATUS_TSTRGTERR3_SHIFT (9U)
#define ENET_TS_STATUS_TSTRGTERR3_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_TSTRGTERR3_MASK) >> ENET_TS_STATUS_TSTRGTERR3_SHIFT)

/*
 * TSTARGT3 (RO)
 *
 * Timestamp Target Time Reached for Target Time PPS3
 * When set, this bit indicates that the value of system time is greater than or equal to the value specified in Register 496 (PPS3 Target Time High Register) and Register 497 (PPS3 Target Time Low Register).
 */
#define ENET_TS_STATUS_TSTARGT3_MASK (0x100U)
#define ENET_TS_STATUS_TSTARGT3_SHIFT (8U)
#define ENET_TS_STATUS_TSTARGT3_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_TSTARGT3_MASK) >> ENET_TS_STATUS_TSTARGT3_SHIFT)

/*
 * TSTRGTERR2 (RO)
 *
 */
#define ENET_TS_STATUS_TSTRGTERR2_MASK (0x80U)
#define ENET_TS_STATUS_TSTRGTERR2_SHIFT (7U)
#define ENET_TS_STATUS_TSTRGTERR2_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_TSTRGTERR2_MASK) >> ENET_TS_STATUS_TSTRGTERR2_SHIFT)

/*
 * TSTARGT2 (RO)
 *
 */
#define ENET_TS_STATUS_TSTARGT2_MASK (0x40U)
#define ENET_TS_STATUS_TSTARGT2_SHIFT (6U)
#define ENET_TS_STATUS_TSTARGT2_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_TSTARGT2_MASK) >> ENET_TS_STATUS_TSTARGT2_SHIFT)

/*
 * TSTRGTERR1 (RO)
 *
 */
#define ENET_TS_STATUS_TSTRGTERR1_MASK (0x20U)
#define ENET_TS_STATUS_TSTRGTERR1_SHIFT (5U)
#define ENET_TS_STATUS_TSTRGTERR1_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_TSTRGTERR1_MASK) >> ENET_TS_STATUS_TSTRGTERR1_SHIFT)

/*
 * TSTARGT1 (RO)
 *
 */
#define ENET_TS_STATUS_TSTARGT1_MASK (0x10U)
#define ENET_TS_STATUS_TSTARGT1_SHIFT (4U)
#define ENET_TS_STATUS_TSTARGT1_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_TSTARGT1_MASK) >> ENET_TS_STATUS_TSTARGT1_SHIFT)

/*
 * TSTRGTERR (RO)
 *
 */
#define ENET_TS_STATUS_TSTRGTERR_MASK (0x8U)
#define ENET_TS_STATUS_TSTRGTERR_SHIFT (3U)
#define ENET_TS_STATUS_TSTRGTERR_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_TSTRGTERR_MASK) >> ENET_TS_STATUS_TSTRGTERR_SHIFT)

/*
 * AUXTSTRIG (RO)
 *
 */
#define ENET_TS_STATUS_AUXTSTRIG_MASK (0x4U)
#define ENET_TS_STATUS_AUXTSTRIG_SHIFT (2U)
#define ENET_TS_STATUS_AUXTSTRIG_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_AUXTSTRIG_MASK) >> ENET_TS_STATUS_AUXTSTRIG_SHIFT)

/*
 * TSTARGT (RO)
 *
 */
#define ENET_TS_STATUS_TSTARGT_MASK (0x2U)
#define ENET_TS_STATUS_TSTARGT_SHIFT (1U)
#define ENET_TS_STATUS_TSTARGT_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_TSTARGT_MASK) >> ENET_TS_STATUS_TSTARGT_SHIFT)

/*
 * TSSOVF (RO)
 *
 */
#define ENET_TS_STATUS_TSSOVF_MASK (0x1U)
#define ENET_TS_STATUS_TSSOVF_SHIFT (0U)
#define ENET_TS_STATUS_TSSOVF_GET(x) (((uint32_t)(x) & ENET_TS_STATUS_TSSOVF_MASK) >> ENET_TS_STATUS_TSSOVF_SHIFT)

/* Bitfield definition for register: PPS_CTRL */
/*
 * TRGTMODSEL3 (RW)
 *
 * Target Time Register Mode for PPS3 Output
 * This field indicates the Target Time registers (register 496 and 497) mode for PPS3 output signal. This field is similar to the TRGTMODSEL0 field.
 */
#define ENET_PPS_CTRL_TRGTMODSEL3_MASK (0x60000000UL)
#define ENET_PPS_CTRL_TRGTMODSEL3_SHIFT (29U)
#define ENET_PPS_CTRL_TRGTMODSEL3_SET(x) (((uint32_t)(x) << ENET_PPS_CTRL_TRGTMODSEL3_SHIFT) & ENET_PPS_CTRL_TRGTMODSEL3_MASK)
#define ENET_PPS_CTRL_TRGTMODSEL3_GET(x) (((uint32_t)(x) & ENET_PPS_CTRL_TRGTMODSEL3_MASK) >> ENET_PPS_CTRL_TRGTMODSEL3_SHIFT)

/*
 * PPSCMD3 (WO)
 *
 * Flexible PPS3 Output Control
 * This field controls the flexible PPS3 output (ptp_pps_o[3]) signal. This field is similar to PPSCMD0[2:0] in functionality.
 */
#define ENET_PPS_CTRL_PPSCMD3_MASK (0x7000000UL)
#define ENET_PPS_CTRL_PPSCMD3_SHIFT (24U)
#define ENET_PPS_CTRL_PPSCMD3_SET(x) (((uint32_t)(x) << ENET_PPS_CTRL_PPSCMD3_SHIFT) & ENET_PPS_CTRL_PPSCMD3_MASK)
#define ENET_PPS_CTRL_PPSCMD3_GET(x) (((uint32_t)(x) & ENET_PPS_CTRL_PPSCMD3_MASK) >> ENET_PPS_CTRL_PPSCMD3_SHIFT)

/*
 * TRGTMODSEL2 (RW)
 *
 * Target Time Register Mode for PPS2 Output
 * This field indicates the Target Time registers (register 488 and 489) mode for PPS2 output signal. This field is similar to the TRGTMODSEL0 field.
 */
#define ENET_PPS_CTRL_TRGTMODSEL2_MASK (0x600000UL)
#define ENET_PPS_CTRL_TRGTMODSEL2_SHIFT (21U)
#define ENET_PPS_CTRL_TRGTMODSEL2_SET(x) (((uint32_t)(x) << ENET_PPS_CTRL_TRGTMODSEL2_SHIFT) & ENET_PPS_CTRL_TRGTMODSEL2_MASK)
#define ENET_PPS_CTRL_TRGTMODSEL2_GET(x) (((uint32_t)(x) & ENET_PPS_CTRL_TRGTMODSEL2_MASK) >> ENET_PPS_CTRL_TRGTMODSEL2_SHIFT)

/*
 * PPSCMD2 (WO)
 *
 * Flexible PPS2 Output Control
 * This field controls the flexible PPS2 output (ptp_pps_o[2]) signal. This field is similar to PPSCMD0[2:0] in functionality.
 */
#define ENET_PPS_CTRL_PPSCMD2_MASK (0x70000UL)
#define ENET_PPS_CTRL_PPSCMD2_SHIFT (16U)
#define ENET_PPS_CTRL_PPSCMD2_SET(x) (((uint32_t)(x) << ENET_PPS_CTRL_PPSCMD2_SHIFT) & ENET_PPS_CTRL_PPSCMD2_MASK)
#define ENET_PPS_CTRL_PPSCMD2_GET(x) (((uint32_t)(x) & ENET_PPS_CTRL_PPSCMD2_MASK) >> ENET_PPS_CTRL_PPSCMD2_SHIFT)

/*
 * TRGTMODSEL1 (RW)
 *
 * Target Time Register Mode for PPS1 Output
 * This field indicates the Target Time registers (register 480 and 481) mode for PPS1 output signal. This field is similar to the TRGTMODSEL0 field.
 */
#define ENET_PPS_CTRL_TRGTMODSEL1_MASK (0x6000U)
#define ENET_PPS_CTRL_TRGTMODSEL1_SHIFT (13U)
#define ENET_PPS_CTRL_TRGTMODSEL1_SET(x) (((uint32_t)(x) << ENET_PPS_CTRL_TRGTMODSEL1_SHIFT) & ENET_PPS_CTRL_TRGTMODSEL1_MASK)
#define ENET_PPS_CTRL_TRGTMODSEL1_GET(x) (((uint32_t)(x) & ENET_PPS_CTRL_TRGTMODSEL1_MASK) >> ENET_PPS_CTRL_TRGTMODSEL1_SHIFT)

/*
 * PPSCMD1 (WO)
 *
 * Flexible PPS1 Output Control
 * This field controls the flexible PPS1 output (ptp_pps_o[1]) signal. This field is similar to PPSCMD0[2:0] in functionality.
 */
#define ENET_PPS_CTRL_PPSCMD1_MASK (0x700U)
#define ENET_PPS_CTRL_PPSCMD1_SHIFT (8U)
#define ENET_PPS_CTRL_PPSCMD1_SET(x) (((uint32_t)(x) << ENET_PPS_CTRL_PPSCMD1_SHIFT) & ENET_PPS_CTRL_PPSCMD1_MASK)
#define ENET_PPS_CTRL_PPSCMD1_GET(x) (((uint32_t)(x) & ENET_PPS_CTRL_PPSCMD1_MASK) >> ENET_PPS_CTRL_PPSCMD1_SHIFT)

/*
 * TRGTMODSEL0 (RW)
 *
 * Target Time Register Mode for PPS0 Output
 *  This field indicates the Target Time registers (register 455 and 456) mode for PPS0 output signal:
 * - 00: Indicates that the Target Time registers are programmed only for generating the interrupt event.
 * - 01: Reserved
 * - 10: Indicates that the Target Time registers are programmed for generating the interrupt event and starting or stopping the generation of the PPS0 output signal.
 * - 11: Indicates that the Target Time registers are programmed only for starting or stopping the generation of the PPS0 output signal. No interrupt is asserted.
 */
#define ENET_PPS_CTRL_TRGTMODSEL0_MASK (0x60U)
#define ENET_PPS_CTRL_TRGTMODSEL0_SHIFT (5U)
#define ENET_PPS_CTRL_TRGTMODSEL0_SET(x) (((uint32_t)(x) << ENET_PPS_CTRL_TRGTMODSEL0_SHIFT) & ENET_PPS_CTRL_TRGTMODSEL0_MASK)
#define ENET_PPS_CTRL_TRGTMODSEL0_GET(x) (((uint32_t)(x) & ENET_PPS_CTRL_TRGTMODSEL0_MASK) >> ENET_PPS_CTRL_TRGTMODSEL0_SHIFT)

/*
 * PPSEN0 (RW)
 *
 * Flexible PPS Output Mode Enable
 * When set low, Bits [3:0] function as PPSCTRL (backward compatible). When set high, Bits[3:0] function as PPSCMD.
 */
#define ENET_PPS_CTRL_PPSEN0_MASK (0x10U)
#define ENET_PPS_CTRL_PPSEN0_SHIFT (4U)
#define ENET_PPS_CTRL_PPSEN0_SET(x) (((uint32_t)(x) << ENET_PPS_CTRL_PPSEN0_SHIFT) & ENET_PPS_CTRL_PPSEN0_MASK)
#define ENET_PPS_CTRL_PPSEN0_GET(x) (((uint32_t)(x) & ENET_PPS_CTRL_PPSEN0_MASK) >> ENET_PPS_CTRL_PPSEN0_SHIFT)

/*
 * PPSCTRLCMD0 (RW/WO)
 *
 * PPSCTRL0: PPS0 Output Frequency Control
 * This field controls the frequency of the PPS0 output (ptp_pps_o[0]) signal.
 * The default value of PPSCTRL is 0000, and the PPS output is 1 pulse (of width clk_ptp_i) every second.
 * For other values of PPSCTRL, the PPS output becomes a generated clock of following frequencies:
 * - 0001: The binary rollover is 2 Hz, and the digital rollover is 1 Hz.
 * - 0010: The binary rollover is 4 Hz, and the digital rollover is 2 Hz.
 * - 0011: The binary rollover is 8 Hz, and the digital rollover is 4 Hz.
 * - 0100: The binary rollover is 16 Hz, and the digital rollover is 8 Hz. - ...
 * - 1111: The binary rollover is 32.768 KHz, and the digital rollover is 16.384 KHz.
 * Note: In the binary rollover mode, the PPS output (ptp_pps_o) has a duty cycle of 50 percent with these frequencies.
 * In the digital rollover mode, the PPS output frequency is an average number.
 * The actual clock is of different frequency that gets synchronized every second. For example:
 * - When PPSCTRL = 0001, the PPS (1 Hz) has a low period of 537 ms and a high period of 463 ms
 * - When PPSCTRL = 0010, the PPS (2 Hz) is a sequence of:
 *   - One clock of 50 percent duty cycle and 537 ms period
 *   - Second clock of 463 ms period (268 ms low and 195 ms high)
 * - When PPSCTRL = 0011, the PPS (4 Hz) is a sequence of:
 *   - Three clocks of 50 percent duty cycle and 268 ms period
 *   - Fourth clock of 195 ms period (134 ms low and 61 ms high)
 * PPSCMD0: Flexible PPS0 Output Control
 * 0000: No Command
 * 0001: START Single Pulse
 * This command generates single pulse rising at the start point defined in
 * Target Time Registers and of a duration defined
 * in the PPS0 Width Register.
 * 0010: START Pulse Train
 * This command generates the train of pulses rising at the start point
 * defined in the Target Time Registers and of a duration defined in the
 * PPS0 Width Register and repeated at interval defined in the PPS
 * Interval Register. By default, the PPS pulse train is free-running unless
 * stopped by ‘STOP Pulse train at time’ or ‘STOP Pulse Train
 * immediately’ commands.
 * 0011: Cancel START
 * This command cancels the START Single Pulse and START Pulse Train
 * commands if the system time has not crossed the programmed start
 * time.
 * 0100: STOP Pulse train at time
 * This command stops the train of pulses initiated by the START Pulse
 * Train command (PPSCMD = 0010) after the time programmed in the
 * Target Time registers elapses.
 * 0101: STOP Pulse Train immediately
 * This command immediately stops the train of pulses initiated by the
 * START Pulse Train command (PPSCMD = 0010).
 * 0110: Cancel STOP Pulse train
 * This command cancels the STOP pulse train at time command if the
 * programmed stop time has not elapsed. The PPS pulse train becomes
 * free-running on the successful execution of this command.
 * 0111-1111: Reserved
 * Note: These bits get cleared automatically
 */
#define ENET_PPS_CTRL_PPSCTRLCMD0_MASK (0xFU)
#define ENET_PPS_CTRL_PPSCTRLCMD0_SHIFT (0U)
#define ENET_PPS_CTRL_PPSCTRLCMD0_SET(x) (((uint32_t)(x) << ENET_PPS_CTRL_PPSCTRLCMD0_SHIFT) & ENET_PPS_CTRL_PPSCTRLCMD0_MASK)
#define ENET_PPS_CTRL_PPSCTRLCMD0_GET(x) (((uint32_t)(x) & ENET_PPS_CTRL_PPSCTRLCMD0_MASK) >> ENET_PPS_CTRL_PPSCTRLCMD0_SHIFT)

/* Bitfield definition for register: AUX_TS_NSEC */
/*
 * AUXTSLO (RO)
 *
 * Contains the lower 31 bits (nano-seconds field) of the auxiliary timestamp.
 */
#define ENET_AUX_TS_NSEC_AUXTSLO_MASK (0x7FFFFFFFUL)
#define ENET_AUX_TS_NSEC_AUXTSLO_SHIFT (0U)
#define ENET_AUX_TS_NSEC_AUXTSLO_GET(x) (((uint32_t)(x) & ENET_AUX_TS_NSEC_AUXTSLO_MASK) >> ENET_AUX_TS_NSEC_AUXTSLO_SHIFT)

/* Bitfield definition for register: AUX_TS_SEC */
/*
 * AUXTSHI (RO)
 *
 * Contains the lower 32 bits of the Seconds field of the auxiliary timestamp.
 */
#define ENET_AUX_TS_SEC_AUXTSHI_MASK (0xFFFFFFFFUL)
#define ENET_AUX_TS_SEC_AUXTSHI_SHIFT (0U)
#define ENET_AUX_TS_SEC_AUXTSHI_GET(x) (((uint32_t)(x) & ENET_AUX_TS_SEC_AUXTSHI_MASK) >> ENET_AUX_TS_SEC_AUXTSHI_SHIFT)

/* Bitfield definition for register: PPS0_INTERVAL */
/*
 * PPSINT (RW)
 *
 * PPS0 Output Signal Interval
 * These bits store the interval between the rising edges of PPS0 signal output in terms of units of sub-second increment value.
 * You need to program one value less than the required interval.
 * For example, if the PTP reference clock is 50 MHz (period of 20ns),
 * and desired interval between rising edges of PPS0 signal output is 100ns
 *  (that is, five units of sub-second increment value), then you should program value 4 (5 – 1) in this register.
 */
#define ENET_PPS0_INTERVAL_PPSINT_MASK (0xFFFFFFFFUL)
#define ENET_PPS0_INTERVAL_PPSINT_SHIFT (0U)
#define ENET_PPS0_INTERVAL_PPSINT_SET(x) (((uint32_t)(x) << ENET_PPS0_INTERVAL_PPSINT_SHIFT) & ENET_PPS0_INTERVAL_PPSINT_MASK)
#define ENET_PPS0_INTERVAL_PPSINT_GET(x) (((uint32_t)(x) & ENET_PPS0_INTERVAL_PPSINT_MASK) >> ENET_PPS0_INTERVAL_PPSINT_SHIFT)

/* Bitfield definition for register: PPS0_WIDTH */
/*
 * PPSWIDTH (RW)
 *
 * PPS0 Output Signal Width
 * These bits store the width between the rising edge and corresponding falling edge of the PPS0 signal output in terms of units of sub-second increment value.
 * You need to program one value less than the required interval.
 * For example, if PTP reference clock is 50 MHz (period of 20ns),
 * and desired width between the rising and corresponding falling edges of PPS0 signal output is 80ns
 *  (that is, four units of sub-second increment value), then you should program value 3 (4 – 1) in this register.
 */
#define ENET_PPS0_WIDTH_PPSWIDTH_MASK (0xFFFFFFFFUL)
#define ENET_PPS0_WIDTH_PPSWIDTH_SHIFT (0U)
#define ENET_PPS0_WIDTH_PPSWIDTH_SET(x) (((uint32_t)(x) << ENET_PPS0_WIDTH_PPSWIDTH_SHIFT) & ENET_PPS0_WIDTH_PPSWIDTH_MASK)
#define ENET_PPS0_WIDTH_PPSWIDTH_GET(x) (((uint32_t)(x) & ENET_PPS0_WIDTH_PPSWIDTH_MASK) >> ENET_PPS0_WIDTH_PPSWIDTH_SHIFT)

/* Bitfield definition for register of struct array PPS: TGTTM_SEC */
/*
 * TSTRH1 (RW)
 *
 * PPS1 Target Time Seconds Register
 * This register stores the time in seconds.
 * When the timestamp value matches or exceeds both Target Timestamp registers,
 * then based on Bits [14:13], TRGTMODSEL1, of Register 459 (PPS Control Register),
 * the MAC starts or stops the PPS signal output and generates an interrupt (if enabled).
 */
#define ENET_PPS_TGTTM_SEC_TSTRH1_MASK (0xFFFFFFFFUL)
#define ENET_PPS_TGTTM_SEC_TSTRH1_SHIFT (0U)
#define ENET_PPS_TGTTM_SEC_TSTRH1_SET(x) (((uint32_t)(x) << ENET_PPS_TGTTM_SEC_TSTRH1_SHIFT) & ENET_PPS_TGTTM_SEC_TSTRH1_MASK)
#define ENET_PPS_TGTTM_SEC_TSTRH1_GET(x) (((uint32_t)(x) & ENET_PPS_TGTTM_SEC_TSTRH1_MASK) >> ENET_PPS_TGTTM_SEC_TSTRH1_SHIFT)

/* Bitfield definition for register of struct array PPS: TGTTM_NSEC */
/*
 * TRGTBUSY1 (RW)
 *
 * PPS1 Target Time Register Busy
 * The MAC sets this bit when the PPSCMD1 field (Bits [10:8]) in Register 459 (PPS Control Register) is programmed to 010 or 011.
 * Programming the PPSCMD1 field to 010 or 011 instructs the MAC to synchronize the Target Time Registers to the PTP clock domain.
 * The MAC clears this bit after synchronizing the Target Time Registers to the PTP clock domain
 * The application must not update the Targeers wht Time Registen this bit is read as 1.
 * Otherwise, the synchronization of the previous programmed time gets corrupted.
 */
#define ENET_PPS_TGTTM_NSEC_TRGTBUSY1_MASK (0x80000000UL)
#define ENET_PPS_TGTTM_NSEC_TRGTBUSY1_SHIFT (31U)
#define ENET_PPS_TGTTM_NSEC_TRGTBUSY1_SET(x) (((uint32_t)(x) << ENET_PPS_TGTTM_NSEC_TRGTBUSY1_SHIFT) & ENET_PPS_TGTTM_NSEC_TRGTBUSY1_MASK)
#define ENET_PPS_TGTTM_NSEC_TRGTBUSY1_GET(x) (((uint32_t)(x) & ENET_PPS_TGTTM_NSEC_TRGTBUSY1_MASK) >> ENET_PPS_TGTTM_NSEC_TRGTBUSY1_SHIFT)

/*
 * TTSL1 (RW)
 *
 * Target Time Low for PPS1 Register
 * This register stores the time in (signed) nanoseconds.
 * When the value of the timestamp matches the both Target Timestamp registers,
 * then based on the TRGTMODSEL1 field (Bits [14:13]) in Register 459 (PPS Control Register),
 *  the MAC starts or stops the PPS signal output and generates an interrupt (if enabled).
 *  This value should not exceed 0x3B9A_C9FF when Bit 9 (TSCTRLSSR) is set in Register 448 (Timestamp Control Register).
 * The actual start or stop time of the PPS signal output may have an error margin up to one unit of sub-second increment value.
 */
#define ENET_PPS_TGTTM_NSEC_TTSL1_MASK (0x7FFFFFFFUL)
#define ENET_PPS_TGTTM_NSEC_TTSL1_SHIFT (0U)
#define ENET_PPS_TGTTM_NSEC_TTSL1_SET(x) (((uint32_t)(x) << ENET_PPS_TGTTM_NSEC_TTSL1_SHIFT) & ENET_PPS_TGTTM_NSEC_TTSL1_MASK)
#define ENET_PPS_TGTTM_NSEC_TTSL1_GET(x) (((uint32_t)(x) & ENET_PPS_TGTTM_NSEC_TTSL1_MASK) >> ENET_PPS_TGTTM_NSEC_TTSL1_SHIFT)

/* Bitfield definition for register of struct array PPS: INTERVAL */
/*
 * PPSINT (RW)
 *
 * PPS1 Output Signal Interval
 * These bits store the interval between the rising edges of PPS1 signal output in terms of units of sub-second increment value.
 * You need to program one value less than the required interval. For example, if the PTP reference clock is 50 MHz (period of 20ns),
 *  and desired interval between rising edges of PPS1 signal output is 100ns (that is, five units of sub-second increment value),
 * then you should program value 4 (5 – 1) in this register.
 */
#define ENET_PPS_INTERVAL_PPSINT_MASK (0xFFFFFFFFUL)
#define ENET_PPS_INTERVAL_PPSINT_SHIFT (0U)
#define ENET_PPS_INTERVAL_PPSINT_SET(x) (((uint32_t)(x) << ENET_PPS_INTERVAL_PPSINT_SHIFT) & ENET_PPS_INTERVAL_PPSINT_MASK)
#define ENET_PPS_INTERVAL_PPSINT_GET(x) (((uint32_t)(x) & ENET_PPS_INTERVAL_PPSINT_MASK) >> ENET_PPS_INTERVAL_PPSINT_SHIFT)

/* Bitfield definition for register of struct array PPS: WIDTH */
/*
 * PPSWIDTH (RW)
 *
 * PPS1 Output Signal Width
 * These bits store the width between the rising edge and corresponding falling edge of the PPS1 signal output in terms of units of sub-second increment value.
 * You need to program one value less than the required interval. For example,
 *  if PTP reference clock is 50 MHz (period of 20ns),
 * and desired width between the rising and corresponding falling edges of PPS1 signal output is 80ns (that is, four units of sub-second increment value),
 * then you should program value 3 (4 – 1) in this register.
 */
#define ENET_PPS_WIDTH_PPSWIDTH_MASK (0xFFFFFFFFUL)
#define ENET_PPS_WIDTH_PPSWIDTH_SHIFT (0U)
#define ENET_PPS_WIDTH_PPSWIDTH_SET(x) (((uint32_t)(x) << ENET_PPS_WIDTH_PPSWIDTH_SHIFT) & ENET_PPS_WIDTH_PPSWIDTH_MASK)
#define ENET_PPS_WIDTH_PPSWIDTH_GET(x) (((uint32_t)(x) & ENET_PPS_WIDTH_PPSWIDTH_MASK) >> ENET_PPS_WIDTH_PPSWIDTH_SHIFT)

/* Bitfield definition for register: DMA_BUS_MODE */
/*
 * RIB (RW)
 *
 * Rebuild INCRx Burst
 * When this bit is set high and the AHB master gets an EBT (Retry, Split, or Losing bus grant),
 *  the AHB master interface rebuilds the pending beats of any burst transfer initiated with INCRx.
 * The AHB master interface rebuilds the beats with a combination of specified bursts with INCRx and SINGLE.
 * By default, the AHB master interface rebuilds pending beats of an EBT with an unspecified (INCR) burst.
 */
#define ENET_DMA_BUS_MODE_RIB_MASK (0x80000000UL)
#define ENET_DMA_BUS_MODE_RIB_SHIFT (31U)
#define ENET_DMA_BUS_MODE_RIB_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_RIB_SHIFT) & ENET_DMA_BUS_MODE_RIB_MASK)
#define ENET_DMA_BUS_MODE_RIB_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_RIB_MASK) >> ENET_DMA_BUS_MODE_RIB_SHIFT)

/*
 * PRWG (RW)
 *
 * Channel Priority
 * Weights This field sets the priority weights for Channel 0 during the round-robin arbitration between the DMA channels for the system bus.
 * - 00: The priority weight is 1.
 * - 01: The priority weight is 2.
 * - 10: The priority weight is 3.
 * - 11: The priority weight is 4. This field is present in all DWC_gmac configurations except GMAC-AXI when you select the AV feature. Otherwise, this field is reserved and read-only (RO).
 */
#define ENET_DMA_BUS_MODE_PRWG_MASK (0x30000000UL)
#define ENET_DMA_BUS_MODE_PRWG_SHIFT (28U)
#define ENET_DMA_BUS_MODE_PRWG_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_PRWG_SHIFT) & ENET_DMA_BUS_MODE_PRWG_MASK)
#define ENET_DMA_BUS_MODE_PRWG_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_PRWG_MASK) >> ENET_DMA_BUS_MODE_PRWG_SHIFT)

/*
 * TXPR (RW)
 *
 * Transmit Priority
 * When set, this bit indicates that the transmit DMA has higher priority than the receive DMA during arbitration for the system-side bus. In the GMAC-AXI configuration, this bit is reserved and read-only (RO).
 */
#define ENET_DMA_BUS_MODE_TXPR_MASK (0x8000000UL)
#define ENET_DMA_BUS_MODE_TXPR_SHIFT (27U)
#define ENET_DMA_BUS_MODE_TXPR_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_TXPR_SHIFT) & ENET_DMA_BUS_MODE_TXPR_MASK)
#define ENET_DMA_BUS_MODE_TXPR_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_TXPR_MASK) >> ENET_DMA_BUS_MODE_TXPR_SHIFT)

/*
 * MB (RW)
 *
 * Mixed Burst
 * When this bit is set high and the FB bit is low, the AHB master interface starts all bursts of length more than 16 with INCR (undefined burst),
 * whereas it reverts to fixed burst transfers (INCRx and SINGLE) for burst length of 16 and less.
 */
#define ENET_DMA_BUS_MODE_MB_MASK (0x4000000UL)
#define ENET_DMA_BUS_MODE_MB_SHIFT (26U)
#define ENET_DMA_BUS_MODE_MB_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_MB_SHIFT) & ENET_DMA_BUS_MODE_MB_MASK)
#define ENET_DMA_BUS_MODE_MB_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_MB_MASK) >> ENET_DMA_BUS_MODE_MB_SHIFT)

/*
 * AAL (RW)
 *
 * Address-Aligned Beats
 * When this bit is set high and the FB bit is equal to 1,
 * the AHB or AXI interface generates all bursts aligned to the start address LS bits. If the FB bit is equal to 0,
 *  the first burst (accessing the start address of data buffer) is not aligned, but subsequent bursts are aligned to the address.
 */
#define ENET_DMA_BUS_MODE_AAL_MASK (0x2000000UL)
#define ENET_DMA_BUS_MODE_AAL_SHIFT (25U)
#define ENET_DMA_BUS_MODE_AAL_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_AAL_SHIFT) & ENET_DMA_BUS_MODE_AAL_MASK)
#define ENET_DMA_BUS_MODE_AAL_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_AAL_MASK) >> ENET_DMA_BUS_MODE_AAL_SHIFT)

/*
 * PBLX8 (RW)
 *
 * PBLx8 Mode
 * When set high, this bit multiplies the programmed PBL value (Bits [22:17] and Bits[13:8]) eight times.
 * Therefore, the DMA transfers the data in 8, 16, 32, 64, 128, and 256 beats depending on the PBL value.
 */
#define ENET_DMA_BUS_MODE_PBLX8_MASK (0x1000000UL)
#define ENET_DMA_BUS_MODE_PBLX8_SHIFT (24U)
#define ENET_DMA_BUS_MODE_PBLX8_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_PBLX8_SHIFT) & ENET_DMA_BUS_MODE_PBLX8_MASK)
#define ENET_DMA_BUS_MODE_PBLX8_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_PBLX8_MASK) >> ENET_DMA_BUS_MODE_PBLX8_SHIFT)

/*
 * USP (RW)
 *
 * Use Separate PBL
 * When set high, this bit configures the Rx DMA to use the value configured in Bits [22:17] as PBL.
 * The PBL value in Bits [13:8] is applicable only to the Tx DMA operations.
 * When reset to low, the PBL value in Bits [13:8] is applicable for both DMA engines.
 */
#define ENET_DMA_BUS_MODE_USP_MASK (0x800000UL)
#define ENET_DMA_BUS_MODE_USP_SHIFT (23U)
#define ENET_DMA_BUS_MODE_USP_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_USP_SHIFT) & ENET_DMA_BUS_MODE_USP_MASK)
#define ENET_DMA_BUS_MODE_USP_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_USP_MASK) >> ENET_DMA_BUS_MODE_USP_SHIFT)

/*
 * RPBL (RW)
 *
 * Rx DMA PBL
 * This field indicates the maximum number of beats to be transferred in one Rx DMA transaction.
 * This is the maximum value that is used in a single block Read or Write.
 * The Rx DMA always attempts to burst as specified in the RPBL bit each time it starts a Burst transfer on the host bus.
 *  You can program RPBL with values of 1, 2, 4, 8, 16, and 32. Any other value results in undefined behavior.
 * This field is valid and applicable only when USP is set high.
 */
#define ENET_DMA_BUS_MODE_RPBL_MASK (0x7E0000UL)
#define ENET_DMA_BUS_MODE_RPBL_SHIFT (17U)
#define ENET_DMA_BUS_MODE_RPBL_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_RPBL_SHIFT) & ENET_DMA_BUS_MODE_RPBL_MASK)
#define ENET_DMA_BUS_MODE_RPBL_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_RPBL_MASK) >> ENET_DMA_BUS_MODE_RPBL_SHIFT)

/*
 * FB (RW)
 *
 * Fixed Burst
 *  This bit controls whether the AHB or AXI master interface performs fixed burst transfers or not.
 * When set, the AHB interface uses only SINGLE, INCR4, INCR8, or INCR16 during start of the normal burst transfers.
 * When reset, the AHB or AXI interface uses SINGLE and INCR burst transfer operations.
 */
#define ENET_DMA_BUS_MODE_FB_MASK (0x10000UL)
#define ENET_DMA_BUS_MODE_FB_SHIFT (16U)
#define ENET_DMA_BUS_MODE_FB_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_FB_SHIFT) & ENET_DMA_BUS_MODE_FB_MASK)
#define ENET_DMA_BUS_MODE_FB_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_FB_MASK) >> ENET_DMA_BUS_MODE_FB_SHIFT)

/*
 * PR (RW)
 *
 * Priority Ratio
 *  These bits control the priority ratio in the weighted round-robin arbitration between the Rx DMA and Tx DMA.
 *  These bits are valid only when Bit 1 (DA) is reset. The priority ratio is Rx:Tx or Tx:Rx depending on whether Bit 27 (TXPR) is reset or set.
 * - 00: The Priority Ratio is 1:1.
 * - 01: The Priority Ratio is 2:1.
 * - 10: The Priority Ratio is 3:1.
 * - 11: The Priority Ratio is 4:1.
 */
#define ENET_DMA_BUS_MODE_PR_MASK (0xC000U)
#define ENET_DMA_BUS_MODE_PR_SHIFT (14U)
#define ENET_DMA_BUS_MODE_PR_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_PR_SHIFT) & ENET_DMA_BUS_MODE_PR_MASK)
#define ENET_DMA_BUS_MODE_PR_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_PR_MASK) >> ENET_DMA_BUS_MODE_PR_SHIFT)

/*
 * PBL (RW)
 *
 * Programmable Burst Length
 * These bits indicate the maximum number of beats to be transferred in one DMA transaction.
 * This is the maximum value that is used in a single block Read or Write.
 * The DMA always attempts to burst as specified in PBL each time it starts a Burst transfer on the host bus.
 * PBL can be programmed with permissible values of 1, 2, 4, 8, 16, and 32.
 * Any other value results in undefined behavior. When USP is set high, this PBL value is applicable only for Tx DMA transactions.
 * If the number of beats to be transferred is more than 32, then perform the following steps: 1. Set the PBLx8 mode. 2. Set the PBL.
 */
#define ENET_DMA_BUS_MODE_PBL_MASK (0x3F00U)
#define ENET_DMA_BUS_MODE_PBL_SHIFT (8U)
#define ENET_DMA_BUS_MODE_PBL_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_PBL_SHIFT) & ENET_DMA_BUS_MODE_PBL_MASK)
#define ENET_DMA_BUS_MODE_PBL_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_PBL_MASK) >> ENET_DMA_BUS_MODE_PBL_SHIFT)

/*
 * ATDS (RW)
 *
 * Alternate Descriptor Size
 * When set, the size of the alternate descriptor (described in “Alternate or Enhanced Descriptors” on page 545) increases to 32 bytes (8 DWORDS).
 * This is required when the Advanced Timestamp feature or the IPC Full Checksum Offload Engine (Type 2) is enabled in the receiver.
 * The enhanced descriptor is not required if the Advanced Timestamp and IPC Full Checksum Offload Engine (Type 2) features are not enabled.
 *  In such case, you can use the 16 bytes descriptor to save 4 bytes of memory.
 * This bit is present only when you select the Alternate Descriptor feature and any one of the following features during core configuration:
 * - Advanced Timestamp feature - IPC Full Checksum Offload Engine (Type 2) feature Otherwise, this bit is reserved and is read-only.
 * When reset, the descriptor size reverts back to 4 DWORDs (16 bytes).
 */
#define ENET_DMA_BUS_MODE_ATDS_MASK (0x80U)
#define ENET_DMA_BUS_MODE_ATDS_SHIFT (7U)
#define ENET_DMA_BUS_MODE_ATDS_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_ATDS_SHIFT) & ENET_DMA_BUS_MODE_ATDS_MASK)
#define ENET_DMA_BUS_MODE_ATDS_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_ATDS_MASK) >> ENET_DMA_BUS_MODE_ATDS_SHIFT)

/*
 * DSL (RW)
 *
 * Descriptor Skip Length
 * This bit specifies the number of Word, Dword, or Lword (depending on the 32-bit, 64-bit, or 128-bit bus) to skip between two unchained descriptors.
 * The address skipping starts from the end of current descriptor to the start of next descriptor.
 * When the DSL value is equal to zero, the descriptor table is taken as contiguous by the DMA in Ring mode.
 */
#define ENET_DMA_BUS_MODE_DSL_MASK (0x7CU)
#define ENET_DMA_BUS_MODE_DSL_SHIFT (2U)
#define ENET_DMA_BUS_MODE_DSL_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_DSL_SHIFT) & ENET_DMA_BUS_MODE_DSL_MASK)
#define ENET_DMA_BUS_MODE_DSL_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_DSL_MASK) >> ENET_DMA_BUS_MODE_DSL_SHIFT)

/*
 * DA (RW)
 *
 * DMA Arbitration Scheme
 * This bit specifies the arbitration scheme between the transmit and receive paths of Channel 0.
 * - 0: Weighted round-robin with Rx:Tx or Tx:Rx The priority between the paths is according to the priority specified in Bits [15:14] (PR) and priority weights specified in Bit 27 (TXPR).
 * - 1: Fixed priority The transmit path has priority over receive path when Bit 27 (TXPR) is set. Otherwise, receive path has priority over the transmit path.
 */
#define ENET_DMA_BUS_MODE_DA_MASK (0x2U)
#define ENET_DMA_BUS_MODE_DA_SHIFT (1U)
#define ENET_DMA_BUS_MODE_DA_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_DA_SHIFT) & ENET_DMA_BUS_MODE_DA_MASK)
#define ENET_DMA_BUS_MODE_DA_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_DA_MASK) >> ENET_DMA_BUS_MODE_DA_SHIFT)

/*
 * SWR (RW)
 *
 * Software Reset
 *  When this bit is set, the MAC DMA Controller resets the logic and all internal registers of the MAC.
 * It is cleared automatically after the reset operation is complete in all of the DWC_gmac clock domains.
 * Before reprogramming any register of the DWC_gmac, you should read a zero (0) value in this bit.
 * Note: - The Software reset function is driven only by this bit.
 * Bit 0 of Register 64 (Channel 1 Bus Mode Register) or Register 128 (Channel 2 Bus Mode Register) has no impact on the Software reset function.
 * - The reset operation is completed only when all resets in all active clock domains are de-asserted.
 * Therefore, it is essential that all PHY inputs clocks (applicable for the selected PHY interface) are present for the software reset completion.
 * The time to complete the software reset operation depends on the frequency of the slowest active clock.
 */
#define ENET_DMA_BUS_MODE_SWR_MASK (0x1U)
#define ENET_DMA_BUS_MODE_SWR_SHIFT (0U)
#define ENET_DMA_BUS_MODE_SWR_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_MODE_SWR_SHIFT) & ENET_DMA_BUS_MODE_SWR_MASK)
#define ENET_DMA_BUS_MODE_SWR_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_MODE_SWR_MASK) >> ENET_DMA_BUS_MODE_SWR_SHIFT)

/* Bitfield definition for register: DMA_TX_POLL_DEMAND */
/*
 * TPD (RW)
 *
 * Transmit Poll Demand
 * When these bits are written with any value,
 * the DMA reads the current descriptor to which the Register 18 (Current Host Transmit Descriptor Register) is pointing.
 *  If that descriptor is not available (owned by the Host),
 * the transmission returns to the Suspend state and Bit 2 (TU) of Register 5 (Status Register) is asserted.
 * If the descriptor is available, the transmission resumes.
 */
#define ENET_DMA_TX_POLL_DEMAND_TPD_MASK (0xFFFFFFFFUL)
#define ENET_DMA_TX_POLL_DEMAND_TPD_SHIFT (0U)
#define ENET_DMA_TX_POLL_DEMAND_TPD_SET(x) (((uint32_t)(x) << ENET_DMA_TX_POLL_DEMAND_TPD_SHIFT) & ENET_DMA_TX_POLL_DEMAND_TPD_MASK)
#define ENET_DMA_TX_POLL_DEMAND_TPD_GET(x) (((uint32_t)(x) & ENET_DMA_TX_POLL_DEMAND_TPD_MASK) >> ENET_DMA_TX_POLL_DEMAND_TPD_SHIFT)

/* Bitfield definition for register: DMA_RX_POLL_DEMAND */
/*
 * RPD (RW)
 *
 * Receive Poll Demand
 * When these bits are written with any value,
 * the DMA reads the current descriptor to which the Register 19 (Current Host Receive Descriptor Register) is pointing.
 *  If that descriptor is not available (owned by the Host),
 * the reception returns to the Suspended state and Bit 7 (RU) of Register 5 (Status Register) is asserted.
 * If the descriptor is available, the Rx DMA returns to the active state.
 */
#define ENET_DMA_RX_POLL_DEMAND_RPD_MASK (0xFFFFFFFFUL)
#define ENET_DMA_RX_POLL_DEMAND_RPD_SHIFT (0U)
#define ENET_DMA_RX_POLL_DEMAND_RPD_SET(x) (((uint32_t)(x) << ENET_DMA_RX_POLL_DEMAND_RPD_SHIFT) & ENET_DMA_RX_POLL_DEMAND_RPD_MASK)
#define ENET_DMA_RX_POLL_DEMAND_RPD_GET(x) (((uint32_t)(x) & ENET_DMA_RX_POLL_DEMAND_RPD_MASK) >> ENET_DMA_RX_POLL_DEMAND_RPD_SHIFT)

/* Bitfield definition for register: DMA_RX_DESC_LIST_ADDR */
/*
 * RDESLA (RW)
 *
 * Start of Receive List
 * This field contains the base address of the first descriptor in the Receive Descriptor list.
 * The LSB bits (1:0, 2:0, or 3:0) for 32-bit, 64-bit, or 128-bit bus width are ignored and internally taken as all-zero by the DMA. Therefore, these LSB bits are read-only (RO).
 */
#define ENET_DMA_RX_DESC_LIST_ADDR_RDESLA_MASK (0xFFFFFFFFUL)
#define ENET_DMA_RX_DESC_LIST_ADDR_RDESLA_SHIFT (0U)
#define ENET_DMA_RX_DESC_LIST_ADDR_RDESLA_SET(x) (((uint32_t)(x) << ENET_DMA_RX_DESC_LIST_ADDR_RDESLA_SHIFT) & ENET_DMA_RX_DESC_LIST_ADDR_RDESLA_MASK)
#define ENET_DMA_RX_DESC_LIST_ADDR_RDESLA_GET(x) (((uint32_t)(x) & ENET_DMA_RX_DESC_LIST_ADDR_RDESLA_MASK) >> ENET_DMA_RX_DESC_LIST_ADDR_RDESLA_SHIFT)

/* Bitfield definition for register: DMA_TX_DESC_LIST_ADDR */
/*
 * TDESLA (RW)
 *
 * Start of Transmit List
 * This field contains the base address of the first descriptor in the Transmit Descriptor list.
 * The LSB bits (1:0, 2:0, 3:0) for 32-bit, 64-bit, or 128-bit bus width are ignored and are internally taken as all-zero by the DMA. Therefore, these LSB bits are read-only (RO).
 */
#define ENET_DMA_TX_DESC_LIST_ADDR_TDESLA_MASK (0xFFFFFFFFUL)
#define ENET_DMA_TX_DESC_LIST_ADDR_TDESLA_SHIFT (0U)
#define ENET_DMA_TX_DESC_LIST_ADDR_TDESLA_SET(x) (((uint32_t)(x) << ENET_DMA_TX_DESC_LIST_ADDR_TDESLA_SHIFT) & ENET_DMA_TX_DESC_LIST_ADDR_TDESLA_MASK)
#define ENET_DMA_TX_DESC_LIST_ADDR_TDESLA_GET(x) (((uint32_t)(x) & ENET_DMA_TX_DESC_LIST_ADDR_TDESLA_MASK) >> ENET_DMA_TX_DESC_LIST_ADDR_TDESLA_SHIFT)

/* Bitfield definition for register: DMA_STATUS */
/*
 * GLPII (RW)
 *
 * GLPII: GMAC LPI Interrupt (for Channel 0)
 * This bit indicates an interrupt event in the LPI logic of the MAC.
 * To reset this bit to 1'b0, the software must read the corresponding registers in the DWC_gmac to get the exact cause of the interrupt and clear its source.
 * Note: GLPII status is given only in Channel 0 DMA register and is applicable only when the Energy Efficient Ethernet feature is enabled. Otherwise, this bit is reserved.
 * When this bit is high, the interrupt signal from the MAC (sbd_intr_o) is high.
 * -or- GTMSI: GMAC TMS Interrupt (for Channel 1 and Channel 2) This bit indicates an interrupt event in the traffic manager and scheduler logic of DWC_gmac.
 * To reset this bit, the software must read the corresponding registers (Channel Status Register) to get the exact cause of the interrupt and clear its source.
 * Note: GTMSI status is given only in Channel 1 and Channel 2 DMA register when the AV feature is enabled and corresponding additional transmit channels are present.
 * Otherwise, this bit is reserved. When this bit is high, the interrupt signal from the MAC (sbd_intr_o) is high.
 */
#define ENET_DMA_STATUS_GLPII_MASK (0x40000000UL)
#define ENET_DMA_STATUS_GLPII_SHIFT (30U)
#define ENET_DMA_STATUS_GLPII_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_GLPII_SHIFT) & ENET_DMA_STATUS_GLPII_MASK)
#define ENET_DMA_STATUS_GLPII_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_GLPII_MASK) >> ENET_DMA_STATUS_GLPII_SHIFT)

/*
 * TTI (RW)
 *
 * Timestamp Trigger Interrupt
 * This bit indicates an interrupt event in the Timestamp Generator block of the DWC_gmac.
 * The software must read the corresponding registers in the DWC_gmac to get the exact cause of the interrupt and clear its source to reset this bit to 1'b0.
 *  When this bit is high, the interrupt signal from the DWC_gmac subsystem (sbd_intr_o) is high.
 * This bit is applicable only when the IEEE 1588 Timestamp feature is enabled. Otherwise, this bit is reserved.
 */
#define ENET_DMA_STATUS_TTI_MASK (0x20000000UL)
#define ENET_DMA_STATUS_TTI_SHIFT (29U)
#define ENET_DMA_STATUS_TTI_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_TTI_SHIFT) & ENET_DMA_STATUS_TTI_MASK)
#define ENET_DMA_STATUS_TTI_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_TTI_MASK) >> ENET_DMA_STATUS_TTI_SHIFT)

/*
 * GPI (RW)
 *
 * GMAC PMT Interrupt
 * This bit indicates an interrupt event in the PMT module of the DWC_gmac.
 *  The software must read the PMT Control and Status Register in the MAC to get the exact cause of interrupt and clear its source to reset this bit to 1’b0.
 * The interrupt signal from the DWC_gmac subsystem (sbd_intr_o) is high when this bit is high.
 * This bit is applicable only when the Power Management feature is enabled.
 * Otherwise, this bit is reserved. Note: The GPI and pmt_intr_o interrupts are generated in different clock domains.
 */
#define ENET_DMA_STATUS_GPI_MASK (0x10000000UL)
#define ENET_DMA_STATUS_GPI_SHIFT (28U)
#define ENET_DMA_STATUS_GPI_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_GPI_SHIFT) & ENET_DMA_STATUS_GPI_MASK)
#define ENET_DMA_STATUS_GPI_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_GPI_MASK) >> ENET_DMA_STATUS_GPI_SHIFT)

/*
 * GMI (RW)
 *
 * GMAC MMC Interrupt
 *  This bit reflects an interrupt event in the MMC module of the DWC_gmac.
 * The software must read the corresponding registers in the DWC_gmac
 * to get the exact cause of the interrupt and clear the source of interrupt to make this bit as 1’b0.
 * The interrupt signal from the DWC_gmac subsystem (sbd_intr_o) is high when this bit is high.
 * This bit is applicable only when the MAC Management Counters (MMC) are enabled. Otherwise, this bit is reserved.
 */
#define ENET_DMA_STATUS_GMI_MASK (0x8000000UL)
#define ENET_DMA_STATUS_GMI_SHIFT (27U)
#define ENET_DMA_STATUS_GMI_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_GMI_SHIFT) & ENET_DMA_STATUS_GMI_MASK)
#define ENET_DMA_STATUS_GMI_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_GMI_MASK) >> ENET_DMA_STATUS_GMI_SHIFT)

/*
 * GLI (RW)
 *
 * GMAC Line Interface Interrupt
 * When set, this bit reflects any of the following interrupt events in the DWC_gmac interfaces (if present and enabled in your configuration):
 * - PCS (TBI, RTBI, or SGMII): Link change or auto-negotiation complete event
 * - SMII or RGMII: Link change event - General Purpose Input Status (GPIS):
 *      Any LL or LH event on the gpi_i input ports To identify the exact cause of the interrupt,
 *     the software must first read Bit 11 and Bits[2:0] of Register 14 (Interrupt Status Register) and then to clear the source of interrupt (which also clears the GLI interrupt),
 *      read any of the following corresponding registers:
 * - PCS (TBI, RTBI, or SGMII): Register 49 (AN Status Register)
 * - SMII or RGMII: Register 54 (SGMII/RGMII/SMII Control and Status Register)
 * - General Purpose Input (GPI): Register 56 (General Purpose IO Register) The interrupt signal from the DWC_gmac subsystem (sbd_intr_o) is high when this bit is high.
 */
#define ENET_DMA_STATUS_GLI_MASK (0x4000000UL)
#define ENET_DMA_STATUS_GLI_SHIFT (26U)
#define ENET_DMA_STATUS_GLI_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_GLI_SHIFT) & ENET_DMA_STATUS_GLI_MASK)
#define ENET_DMA_STATUS_GLI_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_GLI_MASK) >> ENET_DMA_STATUS_GLI_SHIFT)

/*
 * EB (RW)
 *
 * Error Bits
 * This field indicates the type of error that caused a Bus Error, for example, error response on the AHB or AXI interface.
 *  This field is valid only when Bit 13 (FBI) is set. This field does not generate an interrupt.
 * - 0 0 0: Error during Rx DMA Write Data Transfer
 * - 0 1 1: Error during Tx DMA Read Data Transfer
 * - 1 0 0: Error during Rx DMA Descriptor Write Access
 * - 1 0 1: Error during Tx DMA Descriptor Write Access
 * - 1 1 0: Error during Rx DMA Descriptor Read Access
 * - 1 1 1: Error during Tx DMA Descriptor Read Access Note: 001 and 010 are reserved.
 */
#define ENET_DMA_STATUS_EB_MASK (0x3800000UL)
#define ENET_DMA_STATUS_EB_SHIFT (23U)
#define ENET_DMA_STATUS_EB_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_EB_SHIFT) & ENET_DMA_STATUS_EB_MASK)
#define ENET_DMA_STATUS_EB_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_EB_MASK) >> ENET_DMA_STATUS_EB_SHIFT)

/*
 * TS (RW)
 *
 * Transmit Process State
 * This field indicates the Transmit DMA FSM state. This field does not generate an interrupt.
 * - 3’b000: Stopped; Reset or Stop Transmit Command issued
 * - 3’b001: Running; Fetching Transmit Transfer Descriptor
 * - 3’b010: Running; Waiting for status
 * - 3’b011: Running; Reading Data from host memory buffer and queuing it to transmit buffer (Tx FIFO)
 * - 3’b100: TIME_STAMP write state
 * - 3’b101: Reserved for future use
 * - 3’b110: Suspended; Transmit Descriptor Unavailable or Transmit Buffer Underflow
 * - 3’b111: Running; Closing Transmit Descriptor
 */
#define ENET_DMA_STATUS_TS_MASK (0x700000UL)
#define ENET_DMA_STATUS_TS_SHIFT (20U)
#define ENET_DMA_STATUS_TS_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_TS_SHIFT) & ENET_DMA_STATUS_TS_MASK)
#define ENET_DMA_STATUS_TS_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_TS_MASK) >> ENET_DMA_STATUS_TS_SHIFT)

/*
 * RS (RW)
 *
 * Receive Process State
 * This field indicates the Receive DMA FSM state. This field does not generate an interrupt.
 * - 3’b000: Stopped: Reset or Stop Receive Command issued
 * - 3’b001: Running: Fetching Receive Transfer Descriptor
 * - 3’b010: Reserved for future use
 * - 3’b011: Running: Waiting for receive packet
 * - 3’b100: Suspended: Receive Descriptor Unavailable
 * - 3’b101: Running: Closing Receive Descriptor
 * - 3’b110: TIME_STAMP write state
 * - 3’b111: Running: Transferring the receive packet data from receive buffer to host memory
 */
#define ENET_DMA_STATUS_RS_MASK (0xE0000UL)
#define ENET_DMA_STATUS_RS_SHIFT (17U)
#define ENET_DMA_STATUS_RS_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_RS_SHIFT) & ENET_DMA_STATUS_RS_MASK)
#define ENET_DMA_STATUS_RS_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_RS_MASK) >> ENET_DMA_STATUS_RS_SHIFT)

/*
 * NIS (RW)
 *
 * Normal Interrupt Summary
 * Normal Interrupt Summary bit value is the logical OR of the following bits when the corresponding interrupt bits are enabled in
 * Register 7 (Interrupt Enable Register):
 * - Register 5[0]: Transmit Interrupt
 * - Register 5[2]: Transmit Buffer Unavailable
 * - Register 5[6]: Receive Interrupt
 * - Register 5[14]: Early Receive Interrupt Only unmasked bits
 *  (interrupts for which interrupt enable is set in Register 7) affect the Normal Interrupt Summary bit.
 *  This is a sticky bit and must be cleared (by writing 1 to this bit) each time a corresponding bit, which causes NIS to be set, is cleared.
 */
#define ENET_DMA_STATUS_NIS_MASK (0x10000UL)
#define ENET_DMA_STATUS_NIS_SHIFT (16U)
#define ENET_DMA_STATUS_NIS_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_NIS_SHIFT) & ENET_DMA_STATUS_NIS_MASK)
#define ENET_DMA_STATUS_NIS_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_NIS_MASK) >> ENET_DMA_STATUS_NIS_SHIFT)

/*
 * AIS (RW)
 *
 * Abnormal Interrupt Summary
 * Abnormal Interrupt Summary bit value is the logical OR of the following
 * when the corresponding interrupt bits are enabled in Register 7 (Interrupt Enable Register):
 * - Register 5[1]: Transmit Process Stopped
 * - Register 5[3]: Transmit Jabber Timeout
 * - Register 5[4]: Receive FIFO Overflow
 * - Register 5[5]: Transmit Underflow
 * - Register 5[7]: Receive Buffer Unavailable
 * - Register 5[8]: Receive Process Stopped
 * - Register 5[9]: Receive Watchdog Timeout
 * - Register 5[10]: Early Transmit Interrupt
 * - Register 5[13]: Fatal Bus Error Only unmasked bits affect the Abnormal Interrupt Summary bit.
 * This is a sticky bit and must be cleared (by writing 1 to this bit) each time a corresponding bit, which causes AIS to be set, is cleared.
 */
#define ENET_DMA_STATUS_AIS_MASK (0x8000U)
#define ENET_DMA_STATUS_AIS_SHIFT (15U)
#define ENET_DMA_STATUS_AIS_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_AIS_SHIFT) & ENET_DMA_STATUS_AIS_MASK)
#define ENET_DMA_STATUS_AIS_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_AIS_MASK) >> ENET_DMA_STATUS_AIS_SHIFT)

/*
 * ERI (RW)
 *
 * Early Receive Interrupt
 * This bit indicates that the DMA filled the first data buffer of the packet. This bit is cleared when the software writes 1 to this bit or Bit 6 (RI) of this register is set (whichever occurs earlier).
 */
#define ENET_DMA_STATUS_ERI_MASK (0x4000U)
#define ENET_DMA_STATUS_ERI_SHIFT (14U)
#define ENET_DMA_STATUS_ERI_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_ERI_SHIFT) & ENET_DMA_STATUS_ERI_MASK)
#define ENET_DMA_STATUS_ERI_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_ERI_MASK) >> ENET_DMA_STATUS_ERI_SHIFT)

/*
 * FBI (RW)
 *
 * Fatal Bus Error Interrupt
 * This bit indicates that a bus error occurred, as described in Bits [25:23]. When this bit is set, the corresponding DMA engine disables all of its bus accesses.
 */
#define ENET_DMA_STATUS_FBI_MASK (0x2000U)
#define ENET_DMA_STATUS_FBI_SHIFT (13U)
#define ENET_DMA_STATUS_FBI_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_FBI_SHIFT) & ENET_DMA_STATUS_FBI_MASK)
#define ENET_DMA_STATUS_FBI_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_FBI_MASK) >> ENET_DMA_STATUS_FBI_SHIFT)

/*
 * ETI (RW)
 *
 * Early Transmit Interrupt
 * This bit indicates that the frame to be transmitted is fully transferred to the MTL Transmit FIFO.
 */
#define ENET_DMA_STATUS_ETI_MASK (0x400U)
#define ENET_DMA_STATUS_ETI_SHIFT (10U)
#define ENET_DMA_STATUS_ETI_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_ETI_SHIFT) & ENET_DMA_STATUS_ETI_MASK)
#define ENET_DMA_STATUS_ETI_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_ETI_MASK) >> ENET_DMA_STATUS_ETI_SHIFT)

/*
 * RWT (RW)
 *
 * Receive Watchdog Timeout
 * When set, this bit indicates that the Receive Watchdog Timer expired while receiving the current frame and the current frame is truncated after the watchdog timeout.
 */
#define ENET_DMA_STATUS_RWT_MASK (0x200U)
#define ENET_DMA_STATUS_RWT_SHIFT (9U)
#define ENET_DMA_STATUS_RWT_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_RWT_SHIFT) & ENET_DMA_STATUS_RWT_MASK)
#define ENET_DMA_STATUS_RWT_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_RWT_MASK) >> ENET_DMA_STATUS_RWT_SHIFT)

/*
 * RPS (RW)
 *
 * Receive Process Stopped
 * This bit is asserted when the Receive Process enters the Stopped state.
 */
#define ENET_DMA_STATUS_RPS_MASK (0x100U)
#define ENET_DMA_STATUS_RPS_SHIFT (8U)
#define ENET_DMA_STATUS_RPS_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_RPS_SHIFT) & ENET_DMA_STATUS_RPS_MASK)
#define ENET_DMA_STATUS_RPS_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_RPS_MASK) >> ENET_DMA_STATUS_RPS_SHIFT)

/*
 * RU (RW)
 *
 * Receive Buffer Unavailable
 * This bit indicates that the host owns the Next Descriptor in the Receive List and the DMA cannot acquire it.
 * The Receive Process is suspended. To resume processing Receive descriptors,
 *  the host should change the ownership of the descriptor and issue a Receive Poll Demand command.
 *  If no Receive Poll Demand is issued, the Receive Process resumes when the next recognized incoming frame is received.
 * This bit is set only when the previous Receive Descriptor is owned by the DMA.
 */
#define ENET_DMA_STATUS_RU_MASK (0x80U)
#define ENET_DMA_STATUS_RU_SHIFT (7U)
#define ENET_DMA_STATUS_RU_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_RU_SHIFT) & ENET_DMA_STATUS_RU_MASK)
#define ENET_DMA_STATUS_RU_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_RU_MASK) >> ENET_DMA_STATUS_RU_SHIFT)

/*
 * RI (RW)
 *
 * Receive Interrupt
 * This bit indicates that the frame reception is complete.
 * When reception is complete, the Bit 31 of RDES1 (Disable Interrupt on Completion) is reset in the last Descriptor,
 * and the specific frame status information is updated in the descriptor.
 * The reception remains in the Running state.
 */
#define ENET_DMA_STATUS_RI_MASK (0x40U)
#define ENET_DMA_STATUS_RI_SHIFT (6U)
#define ENET_DMA_STATUS_RI_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_RI_SHIFT) & ENET_DMA_STATUS_RI_MASK)
#define ENET_DMA_STATUS_RI_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_RI_MASK) >> ENET_DMA_STATUS_RI_SHIFT)

/*
 * UNF (RW)
 *
 * Transmit Underflow
 * This bit indicates that the Transmit Buffer had an Underflow during frame transmission. Transmission is suspended and an Underflow Error TDES0[1] is set.
 */
#define ENET_DMA_STATUS_UNF_MASK (0x20U)
#define ENET_DMA_STATUS_UNF_SHIFT (5U)
#define ENET_DMA_STATUS_UNF_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_UNF_SHIFT) & ENET_DMA_STATUS_UNF_MASK)
#define ENET_DMA_STATUS_UNF_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_UNF_MASK) >> ENET_DMA_STATUS_UNF_SHIFT)

/*
 * OVF (RW)
 *
 * Receive Overflow
 * This bit indicates that the Receive Buffer had an Overflow during frame reception. If the partial frame is transferred to the application, the overflow status is set in RDES0[11].
 */
#define ENET_DMA_STATUS_OVF_MASK (0x10U)
#define ENET_DMA_STATUS_OVF_SHIFT (4U)
#define ENET_DMA_STATUS_OVF_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_OVF_SHIFT) & ENET_DMA_STATUS_OVF_MASK)
#define ENET_DMA_STATUS_OVF_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_OVF_MASK) >> ENET_DMA_STATUS_OVF_SHIFT)

/*
 * TJT (RW)
 *
 * Transmit Jabber Timeout
 * This bit indicates that the Transmit Jabber Timer expired, which happens when the frame size exceeds 2,048 (10,240 bytes when the Jumbo frame is enabled).
 * When the Jabber Timeout occurs, the transmission process is aborted and placed in the Stopped state. This causes the Transmit Jabber Timeout TDES0[14] flag to assert.
 */
#define ENET_DMA_STATUS_TJT_MASK (0x8U)
#define ENET_DMA_STATUS_TJT_SHIFT (3U)
#define ENET_DMA_STATUS_TJT_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_TJT_SHIFT) & ENET_DMA_STATUS_TJT_MASK)
#define ENET_DMA_STATUS_TJT_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_TJT_MASK) >> ENET_DMA_STATUS_TJT_SHIFT)

/*
 * TU (RW)
 *
 * Transmit Buffer Unavailable
 * This bit indicates that the host owns the Next Descriptor in the Transmit List and the DMA cannot acquire it. Transmission is suspended. Bits[22:20] explain the Transmit Process state transitions.
 * To resume processing Transmit descriptors, the host should change the ownership of the descriptor by setting TDES0[31] and then issue a Transmit Poll Demand command.
 */
#define ENET_DMA_STATUS_TU_MASK (0x4U)
#define ENET_DMA_STATUS_TU_SHIFT (2U)
#define ENET_DMA_STATUS_TU_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_TU_SHIFT) & ENET_DMA_STATUS_TU_MASK)
#define ENET_DMA_STATUS_TU_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_TU_MASK) >> ENET_DMA_STATUS_TU_SHIFT)

/*
 * TPS (RW)
 *
 * Transmit Process Stopped
 * This bit is set when the transmission is stopped.
 */
#define ENET_DMA_STATUS_TPS_MASK (0x2U)
#define ENET_DMA_STATUS_TPS_SHIFT (1U)
#define ENET_DMA_STATUS_TPS_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_TPS_SHIFT) & ENET_DMA_STATUS_TPS_MASK)
#define ENET_DMA_STATUS_TPS_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_TPS_MASK) >> ENET_DMA_STATUS_TPS_SHIFT)

/*
 * TI (RW)
 *
 * Transmit Interrupt
 * This bit indicates that the frame transmission is complete. When transmission is complete, Bit 31 (OWN) of TDES0 is reset, and the specific frame status information is updated in the descriptor.
 */
#define ENET_DMA_STATUS_TI_MASK (0x1U)
#define ENET_DMA_STATUS_TI_SHIFT (0U)
#define ENET_DMA_STATUS_TI_SET(x) (((uint32_t)(x) << ENET_DMA_STATUS_TI_SHIFT) & ENET_DMA_STATUS_TI_MASK)
#define ENET_DMA_STATUS_TI_GET(x) (((uint32_t)(x) & ENET_DMA_STATUS_TI_MASK) >> ENET_DMA_STATUS_TI_SHIFT)

/* Bitfield definition for register: DMA_OP_MODE */
/*
 * DT (RW)
 *
 * Disable Dropping of TCP/IP Checksum Error Frames
 * When this bit is set, the MAC does not drop the frames which only have errors detected by the Receive Checksum Offload engine.
 *  Such frames do not have any errors (including FCS error) in the Ethernet frame received by the MAC but have errors only in the encapsulated payload.
 * When this bit is reset, all error frames are dropped if the FEF bit is reset. If the IPC Full Checksum Offload Engine (Type 2) is disabled, this bit is reserved (RO with value 1'b0).
 */
#define ENET_DMA_OP_MODE_DT_MASK (0x10000000UL)
#define ENET_DMA_OP_MODE_DT_SHIFT (28U)
#define ENET_DMA_OP_MODE_DT_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_DT_SHIFT) & ENET_DMA_OP_MODE_DT_MASK)
#define ENET_DMA_OP_MODE_DT_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_DT_MASK) >> ENET_DMA_OP_MODE_DT_SHIFT)

/*
 * RSF (RW)
 *
 * Receive Store and Forward
 * When this bit is set, the MTL reads a frame from the Rx FIFO only after the complete frame has been written to it, ignoring the RTC bits.
 *  When this bit is reset, the Rx FIFO operates in the cut-through mode, subject to the threshold specified by the RTC bits.
 */
#define ENET_DMA_OP_MODE_RSF_MASK (0x2000000UL)
#define ENET_DMA_OP_MODE_RSF_SHIFT (25U)
#define ENET_DMA_OP_MODE_RSF_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_RSF_SHIFT) & ENET_DMA_OP_MODE_RSF_MASK)
#define ENET_DMA_OP_MODE_RSF_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_RSF_MASK) >> ENET_DMA_OP_MODE_RSF_SHIFT)

/*
 * DFF (RW)
 *
 * Disable Flushing of Received Frames
 * When this bit is set, the Rx DMA does not flush any frames because of the unavailability of receive descriptors or buffers as it does normally when this bit is reset. (See “Receive Process Suspended” on page 83.)
 */
#define ENET_DMA_OP_MODE_DFF_MASK (0x1000000UL)
#define ENET_DMA_OP_MODE_DFF_SHIFT (24U)
#define ENET_DMA_OP_MODE_DFF_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_DFF_SHIFT) & ENET_DMA_OP_MODE_DFF_MASK)
#define ENET_DMA_OP_MODE_DFF_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_DFF_MASK) >> ENET_DMA_OP_MODE_DFF_SHIFT)

/*
 * RFA_2 (RW)
 *
 * MSB of Threshold for Activating Flow Control
 * If the DWC_gmac is configured for an Rx FIFO size of 8 KB or more,
 * this bit (when set) provides additional threshold levels for activating the flow control in both half-duplex and full-duplex modes.
 * This bit (as Most Significant Bit), along with the RFA (Bits [10:9]), gives the following thresholds for activating flow control:
 * - 100: Full minus 5 KB, that is, FULL — 5 KB
 * - 101: Full minus 6 KB, that is, FULL — 6 KB
 * - 110: Full minus 7 KB, that is, FULL — 7 KB
 * - 111: Reserved This bit is reserved (and RO) if the Rx FIFO is 4 KB or less deep.
 */
#define ENET_DMA_OP_MODE_RFA_2_MASK (0x800000UL)
#define ENET_DMA_OP_MODE_RFA_2_SHIFT (23U)
#define ENET_DMA_OP_MODE_RFA_2_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_RFA_2_SHIFT) & ENET_DMA_OP_MODE_RFA_2_MASK)
#define ENET_DMA_OP_MODE_RFA_2_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_RFA_2_MASK) >> ENET_DMA_OP_MODE_RFA_2_SHIFT)

/*
 * RFD_2 (RW)
 *
 * MSB of Threshold for Deactivating Flow Control
 * If the DWC_gmac is configured for Rx FIFO size of 8 KB or more,
 *  this bit (when set) provides additional threshold levels for deactivating the flow control in both half-duplex and full-duplex modes.
 *  This bit (as Most Significant Bit) along with the RFD (Bits [12:11]) gives the following thresholds for deactivating flow control:
 * - 100: Full minus 5 KB, that is, FULL — 5 KB
 * - 101: Full minus 6 KB, that is, FULL — 6 KB
 * - 110: Full minus 7 KB, that is, FULL — 7 KB
 * - 111: Reserved This bit is reserved (and RO) if the Rx FIFO is 4 KB or less deep.
 */
#define ENET_DMA_OP_MODE_RFD_2_MASK (0x400000UL)
#define ENET_DMA_OP_MODE_RFD_2_SHIFT (22U)
#define ENET_DMA_OP_MODE_RFD_2_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_RFD_2_SHIFT) & ENET_DMA_OP_MODE_RFD_2_MASK)
#define ENET_DMA_OP_MODE_RFD_2_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_RFD_2_MASK) >> ENET_DMA_OP_MODE_RFD_2_SHIFT)

/*
 * TSF (RW)
 *
 * Transmit Store and Forward
 * When this bit is set, transmission starts when a full frame resides in the MTL Transmit FIFO.
 * When this bit is set, the TTC values specified in Bits [16:14] are ignored.
 * This bit should be changed only when the transmission is stopped.
 */
#define ENET_DMA_OP_MODE_TSF_MASK (0x200000UL)
#define ENET_DMA_OP_MODE_TSF_SHIFT (21U)
#define ENET_DMA_OP_MODE_TSF_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_TSF_SHIFT) & ENET_DMA_OP_MODE_TSF_MASK)
#define ENET_DMA_OP_MODE_TSF_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_TSF_MASK) >> ENET_DMA_OP_MODE_TSF_SHIFT)

/*
 * FTF (RW)
 *
 * Flush Transmit FIFO
 * When this bit is set, the transmit FIFO controller logic is reset to its default values and thus all data in the Tx FIFO is lost or flushed.
 * This bit is cleared internally when the flushing operation is complete.
 * The Operation Mode register should not be written to until this bit is cleared.
 * The data which is already accepted by the MAC transmitter is not flushed.
 * It is scheduled for transmission and results in underflow and runt frame transmission.
 */
#define ENET_DMA_OP_MODE_FTF_MASK (0x100000UL)
#define ENET_DMA_OP_MODE_FTF_SHIFT (20U)
#define ENET_DMA_OP_MODE_FTF_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_FTF_SHIFT) & ENET_DMA_OP_MODE_FTF_MASK)
#define ENET_DMA_OP_MODE_FTF_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_FTF_MASK) >> ENET_DMA_OP_MODE_FTF_SHIFT)

/*
 * TTC (RW)
 *
 * Transmit Threshold Control
 * These bits control the threshold level of the MTL Transmit FIFO.
 *  Transmission starts when the frame size within the MTL Transmit FIFO is larger than the threshold.
 * In addition, full frames with a length less than the threshold are also transmitted.
 *  These bits are used only when Bit 21 (TSF) is reset.
 * - 000: 64
 * - 001: 128
 * - 010: 192
 * - 011: 256
 * - 100: 40
 * - 101: 32
 * - 110: 24
 * - 111: 16
 */
#define ENET_DMA_OP_MODE_TTC_MASK (0x1C000UL)
#define ENET_DMA_OP_MODE_TTC_SHIFT (14U)
#define ENET_DMA_OP_MODE_TTC_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_TTC_SHIFT) & ENET_DMA_OP_MODE_TTC_MASK)
#define ENET_DMA_OP_MODE_TTC_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_TTC_MASK) >> ENET_DMA_OP_MODE_TTC_SHIFT)

/*
 * ST (RW)
 *
 * Start or Stop Transmission Command
 * When this bit is set, transmission is placed in the Running state, and the DMA checks the Transmit List at the current position for a frame to be transmitted.
 * Descriptor acquisition is attempted either from the current position in the list,
 * which is the Transmit List Base Address set by Register 4 (Transmit Descriptor List Address Register),
 * or from the position retained when transmission was stopped previously.
 *  If the DMA does not own the current descriptor,
 * transmission enters the Suspended state and Bit 2 (Transmit Buffer Unavailable) of Register 5 (Status Register) is set.
 * The Start Transmission command is effective only when transmission is stopped.
 * If the command is issued before setting Register 4 (Transmit Descriptor List Address Register),
 *  then the DMA behavior is unpredictable. When this bit is reset,
 * the transmission process is placed in the Stopped state after completing the transmission of the current frame.
 * The Next Descriptor position in the Transmit List is saved,
 * and it becomes the current position when transmission is restarted.
 * To change the list address, you need to program Register 4 (Transmit Descriptor List Address Register) with a new value when this bit is reset.
 * The new value is considered when this bit is set again.
 * The stop transmission command is effective only when the transmission of the current frame is complete or the transmission is in the Suspended state.
 */
#define ENET_DMA_OP_MODE_ST_MASK (0x2000U)
#define ENET_DMA_OP_MODE_ST_SHIFT (13U)
#define ENET_DMA_OP_MODE_ST_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_ST_SHIFT) & ENET_DMA_OP_MODE_ST_MASK)
#define ENET_DMA_OP_MODE_ST_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_ST_MASK) >> ENET_DMA_OP_MODE_ST_SHIFT)

/*
 * RFD (RW)
 *
 * Threshold for Deactivating Flow Control (in half-duplex and full-duplex modes) These bits control the threshold (Fill-level of Rx FIFO) at which the flow control is de-asserted after activation.
 * - 00: Full minus 1 KB, that is, FULL — 1 KB
 * - 01: Full minus 2 KB, that is, FULL — 2 KB
 * - 10: Full minus 3 KB, that is, FULL — 3 KB
 * - 11: Full minus 4 KB, that is, FULL — 4 KB
 * The de-assertion is effective only after flow control is asserted.
 *  If the Rx FIFO is 8 KB or more, an additional Bit (RFD_2) is used for more threshold levels as described in Bit 22.
 * These bits are reserved and read-only when the Rx FIFO depth is less than 4 KB.
 */
#define ENET_DMA_OP_MODE_RFD_MASK (0x1800U)
#define ENET_DMA_OP_MODE_RFD_SHIFT (11U)
#define ENET_DMA_OP_MODE_RFD_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_RFD_SHIFT) & ENET_DMA_OP_MODE_RFD_MASK)
#define ENET_DMA_OP_MODE_RFD_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_RFD_MASK) >> ENET_DMA_OP_MODE_RFD_SHIFT)

/*
 * RFA (RW)
 *
 * Threshold for Activating Flow Control (in half-duplex and full-duplex modes)
 * These bits control the threshold (Fill level of Rx FIFO) at which the flow control is activated.
 * - 00: Full minus 1 KB, that is, FULL—1KB.
 * - 01: Full minus 2 KB, that is, FULL—2KB.
 * - 10: Full minus 3 KB, that is, FULL—3KB.
 * - 11: Full minus 4 KB, that is, FULL—4KB.
 * These values are applicable only to Rx FIFOs of 4 KB or more and when Bit 8 (EFC) is set high. If the Rx FIFO is 8 KB or more,
 * an additional Bit (RFA_2) is used for more threshold levels as described in Bit 23.
 * These bits are reserved and read-only when the depth of Rx FIFO is less than 4 KB.
 * Note: When FIFO size is exactly 4 KB, although the DWC_gmac allows you to program the value of these bits to 11,
 * the software should not program these bits to 2'b11. The value 2'b11 means flow control on FIFO empty condition
 */
#define ENET_DMA_OP_MODE_RFA_MASK (0x600U)
#define ENET_DMA_OP_MODE_RFA_SHIFT (9U)
#define ENET_DMA_OP_MODE_RFA_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_RFA_SHIFT) & ENET_DMA_OP_MODE_RFA_MASK)
#define ENET_DMA_OP_MODE_RFA_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_RFA_MASK) >> ENET_DMA_OP_MODE_RFA_SHIFT)

/*
 * EFC (RW)
 *
 * Enable HW Flow Control
 * When this bit is set, the flow control signal operation based on the fill-level of Rx FIFO is enabled.
 * When reset, the flow control operation is disabled.
 *  This bit is not used (reserved and always reset) when the Rx FIFO is less than 4 KB.
 */
#define ENET_DMA_OP_MODE_EFC_MASK (0x100U)
#define ENET_DMA_OP_MODE_EFC_SHIFT (8U)
#define ENET_DMA_OP_MODE_EFC_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_EFC_SHIFT) & ENET_DMA_OP_MODE_EFC_MASK)
#define ENET_DMA_OP_MODE_EFC_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_EFC_MASK) >> ENET_DMA_OP_MODE_EFC_SHIFT)

/*
 * FEF (RW)
 *
 * Forward Error Frames
 * When this bit is reset, the Rx FIFO drops frames with error status (CRC error, collision error, GMII_ER, giant frame, watchdog timeout, or overflow).
 * However, if the start byte (write) pointer of a frame is already transferred to the read controller side (in Threshold mode),
 * then the frame is not dropped. In the GMAC-MTL configuration in which the Frame Length FIFO is also enabled during core configuration,
 * the Rx FIFO drops the error frames if that frame's start byte is not transferred (output) on the ARI bus.
 * When the FEF bit is set, all frames except runt error frames are forwarded to the DMA.
 * If the Bit 25 (RSF) is set and the Rx FIFO overflows when a partial frame is written,
 * then the frame is dropped irrespective of the FEF bit setting.
 * However, if the Bit 25 (RSF) is reset and the Rx FIFO overflows when a partial frame is written, then a partial frame may be forwarded to the DMA.
 * Note: When FEF bit is reset, the giant frames are dropped if the giant frame status is given in Rx Status (in Table 8-6 or Table 8-23) in the following configurations:
 * - The IP checksum engine (Type 1) and full checksum offload engine (Type 2) are not selected.
 *  - The advanced timestamp feature is not selected but the extended status is selected.
 * The extended status is available with the following features:
 * - L3-L4 filter in GMAC-CORE or GMAC-MTL configurations
 * - Full checksum offload engine (Type 2) with enhanced descriptor format in the GMAC-DMA, GMAC-AHB, or GMAC-AXI configurations.
 */
#define ENET_DMA_OP_MODE_FEF_MASK (0x80U)
#define ENET_DMA_OP_MODE_FEF_SHIFT (7U)
#define ENET_DMA_OP_MODE_FEF_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_FEF_SHIFT) & ENET_DMA_OP_MODE_FEF_MASK)
#define ENET_DMA_OP_MODE_FEF_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_FEF_MASK) >> ENET_DMA_OP_MODE_FEF_SHIFT)

/*
 * FUF (RW)
 *
 * Forward Undersized Good Frames
 * When set, the Rx FIFO forwards Undersized frames (that is, frames with no Error and length less than 64 bytes) including pad-bytes and CRC
 * When reset, the Rx FIFO drops all frames of less than 64 bytes, unless a frame is already transferred because of the lower value of Receive Threshold, for example, RTC = 01.
 */
#define ENET_DMA_OP_MODE_FUF_MASK (0x40U)
#define ENET_DMA_OP_MODE_FUF_SHIFT (6U)
#define ENET_DMA_OP_MODE_FUF_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_FUF_SHIFT) & ENET_DMA_OP_MODE_FUF_MASK)
#define ENET_DMA_OP_MODE_FUF_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_FUF_MASK) >> ENET_DMA_OP_MODE_FUF_SHIFT)

/*
 * DGF (RW)
 *
 * Drop Giant Frames
 * When set, the MAC drops the received giant frames in the Rx FIFO,
 * that is, frames that are larger than the computed giant frame limit.
 * When reset, the MAC does not drop the giant frames in the Rx FIFO.
 * Note: This bit is available in the following configurations in which the giant frame status is not provided in Rx status and giant frames are not dropped by default:
 * - Configurations in which IP Checksum Offload (Type 1) is selected in Rx
 * - Configurations in which the IPC Full Checksum Offload Engine (Type 2) is selected in Rx with normal descriptor format
 * - Configurations in which the Advanced Timestamp feature is selected In all other configurations, this bit is not used (reserved and always reset).
 */
#define ENET_DMA_OP_MODE_DGF_MASK (0x20U)
#define ENET_DMA_OP_MODE_DGF_SHIFT (5U)
#define ENET_DMA_OP_MODE_DGF_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_DGF_SHIFT) & ENET_DMA_OP_MODE_DGF_MASK)
#define ENET_DMA_OP_MODE_DGF_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_DGF_MASK) >> ENET_DMA_OP_MODE_DGF_SHIFT)

/*
 * RTC (RW)
 *
 * Receive Threshold Control
 * These two bits control the threshold level of the MTL Receive FIFO.
 * Transfer (request) to DMA starts when the frame size within the MTL Receive FIFO is larger than the threshold.
 * In addition, full frames with length less than the threshold are automatically transferred.
 * The value of 11 is not applicable if the configured Receive FIFO size is 128 bytes.
 * These bits are valid only when the RSF bit is zero, and are ignored when the RSF bit is set to 1.
 * - 00: 64
 * - 01: 32
 * - 10: 96
 * - 11: 128
 */
#define ENET_DMA_OP_MODE_RTC_MASK (0x18U)
#define ENET_DMA_OP_MODE_RTC_SHIFT (3U)
#define ENET_DMA_OP_MODE_RTC_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_RTC_SHIFT) & ENET_DMA_OP_MODE_RTC_MASK)
#define ENET_DMA_OP_MODE_RTC_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_RTC_MASK) >> ENET_DMA_OP_MODE_RTC_SHIFT)

/*
 * OSF (RW)
 *
 * Operate on Second Frame
 * When this bit is set, it instructs the DMA to process the second frame of the Transmit data even before the status for the first frame is obtained.
 */
#define ENET_DMA_OP_MODE_OSF_MASK (0x4U)
#define ENET_DMA_OP_MODE_OSF_SHIFT (2U)
#define ENET_DMA_OP_MODE_OSF_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_OSF_SHIFT) & ENET_DMA_OP_MODE_OSF_MASK)
#define ENET_DMA_OP_MODE_OSF_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_OSF_MASK) >> ENET_DMA_OP_MODE_OSF_SHIFT)

/*
 * SR (RW)
 *
 * Start or Stop Receive
 * When this bit is set, the Receive process is placed in the Running state.
 * The DMA attempts to acquire the descriptor from the Receive list and processes the incoming frames.
 * The descriptor acquisition is attempted from the current position in the list,
 * which is the address set by the Register 3 (Receive Descriptor List Address Register) or the position retained when the Receive process was previously stopped.
 * If the DMA does not own the descriptor, reception is suspended and Bit 7 (Receive Buffer Unavailable) of Register 5 (Status Register) is set.
 * The Start Receive command is effective only when the reception has stopped.
 *  If the command is issued before setting Register 3 (Receive Descriptor List Address Register), the DMA behavior is unpredictable.
 * When this bit is cleared, the Rx DMA operation is stopped after the transfer of the current frame.
 * The next descriptor position in the Receive list is saved and becomes the current position after the Receive process is restarted.
 * The Stop Receive command is effective only when the Receive process is in either the Running (waiting for receive packet) or in the Suspended state.
 */
#define ENET_DMA_OP_MODE_SR_MASK (0x2U)
#define ENET_DMA_OP_MODE_SR_SHIFT (1U)
#define ENET_DMA_OP_MODE_SR_SET(x) (((uint32_t)(x) << ENET_DMA_OP_MODE_SR_SHIFT) & ENET_DMA_OP_MODE_SR_MASK)
#define ENET_DMA_OP_MODE_SR_GET(x) (((uint32_t)(x) & ENET_DMA_OP_MODE_SR_MASK) >> ENET_DMA_OP_MODE_SR_SHIFT)

/* Bitfield definition for register: DMA_INTR_EN */
/*
 * NIE (RW)
 *
 * Normal Interrupt Summary Enable
 * When this bit is set, normal interrupt summary is enabled.
 * When this bit is reset, normal interrupt summary is disabled.
 * This bit enables the following interrupts in Register 5 (Status Register):
 *  - Register 5[0]: Transmit Interrupt
 * - Register 5[2]: Transmit Buffer Unavailable
 * - Register 5[6]: Receive Interrupt
 *  - Register 5[14]: Early Receive Interrupt
 */
#define ENET_DMA_INTR_EN_NIE_MASK (0x10000UL)
#define ENET_DMA_INTR_EN_NIE_SHIFT (16U)
#define ENET_DMA_INTR_EN_NIE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_NIE_SHIFT) & ENET_DMA_INTR_EN_NIE_MASK)
#define ENET_DMA_INTR_EN_NIE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_NIE_MASK) >> ENET_DMA_INTR_EN_NIE_SHIFT)

/*
 * AIE (RW)
 *
 * Abnormal Interrupt Summary Enable
 * When this bit is set, abnormal interrupt summary is enabled.
 * When this bit is reset, the abnormal interrupt summary is disabled.
 * This bit enables the following interrupts in Register 5 (Status Register):
 * - Register 5[1]: Transmit Process Stopped
 * - Register 5[3]: Transmit Jabber Timeout
 * - Register 5[4]: Receive Overflow
 * - Register 5[5]: Transmit Underflow
 * - Register 5[7]: Receive Buffer Unavailable
 * - Register 5[8]: Receive Process Stopped
 * - Register 5[9]: Receive Watchdog Timeout
 * - Register 5[10]: Early Transmit Interrupt
 *  - Register 5[13]: Fatal Bus Error
 */
#define ENET_DMA_INTR_EN_AIE_MASK (0x8000U)
#define ENET_DMA_INTR_EN_AIE_SHIFT (15U)
#define ENET_DMA_INTR_EN_AIE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_AIE_SHIFT) & ENET_DMA_INTR_EN_AIE_MASK)
#define ENET_DMA_INTR_EN_AIE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_AIE_MASK) >> ENET_DMA_INTR_EN_AIE_SHIFT)

/*
 * ERE (RW)
 *
 * Early Receive Interrupt Enable
 * When this bit is set with Normal Interrupt Summary Enable (Bit 16), the Early Receive Interrupt is enabled. When this bit is reset, the Early Receive Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_ERE_MASK (0x4000U)
#define ENET_DMA_INTR_EN_ERE_SHIFT (14U)
#define ENET_DMA_INTR_EN_ERE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_ERE_SHIFT) & ENET_DMA_INTR_EN_ERE_MASK)
#define ENET_DMA_INTR_EN_ERE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_ERE_MASK) >> ENET_DMA_INTR_EN_ERE_SHIFT)

/*
 * FBE (RW)
 *
 * Fatal Bus Error Enable
 * When this bit is set with Abnormal Interrupt Summary Enable (Bit 15), the Fatal Bus Error Interrupt is enabled. When this bit is reset, the Fatal Bus Error Enable Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_FBE_MASK (0x2000U)
#define ENET_DMA_INTR_EN_FBE_SHIFT (13U)
#define ENET_DMA_INTR_EN_FBE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_FBE_SHIFT) & ENET_DMA_INTR_EN_FBE_MASK)
#define ENET_DMA_INTR_EN_FBE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_FBE_MASK) >> ENET_DMA_INTR_EN_FBE_SHIFT)

/*
 * ETE (RW)
 *
 * Early Transmit Interrupt Enable
 * When this bit is set with an Abnormal Interrupt Summary Enable (Bit 15), the Early Transmit Interrupt is enabled. When this bit is reset, the Early Transmit Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_ETE_MASK (0x400U)
#define ENET_DMA_INTR_EN_ETE_SHIFT (10U)
#define ENET_DMA_INTR_EN_ETE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_ETE_SHIFT) & ENET_DMA_INTR_EN_ETE_MASK)
#define ENET_DMA_INTR_EN_ETE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_ETE_MASK) >> ENET_DMA_INTR_EN_ETE_SHIFT)

/*
 * RWE (RW)
 *
 * Receive Watchdog Timeout Enable
 * When this bit is set with Abnormal Interrupt Summary Enable (Bit 15), the Receive Watchdog Timeout Interrupt is enabled. When this bit is reset, the Receive Watchdog Timeout Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_RWE_MASK (0x200U)
#define ENET_DMA_INTR_EN_RWE_SHIFT (9U)
#define ENET_DMA_INTR_EN_RWE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_RWE_SHIFT) & ENET_DMA_INTR_EN_RWE_MASK)
#define ENET_DMA_INTR_EN_RWE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_RWE_MASK) >> ENET_DMA_INTR_EN_RWE_SHIFT)

/*
 * RSE (RW)
 *
 * Receive Stopped Enable
 * When this bit is set with Abnormal Interrupt Summary Enable (Bit 15), the Receive Stopped Interrupt is enabled. When this bit is reset, the Receive Stopped Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_RSE_MASK (0x100U)
#define ENET_DMA_INTR_EN_RSE_SHIFT (8U)
#define ENET_DMA_INTR_EN_RSE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_RSE_SHIFT) & ENET_DMA_INTR_EN_RSE_MASK)
#define ENET_DMA_INTR_EN_RSE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_RSE_MASK) >> ENET_DMA_INTR_EN_RSE_SHIFT)

/*
 * RUE (RW)
 *
 * Receive Buffer Unavailable Enable
 * When this bit is set with Abnormal Interrupt Summary Enable (Bit 15), the Receive Buffer Unavailable Interrupt is enabled. When this bit is reset, the Receive Buffer Unavailable Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_RUE_MASK (0x80U)
#define ENET_DMA_INTR_EN_RUE_SHIFT (7U)
#define ENET_DMA_INTR_EN_RUE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_RUE_SHIFT) & ENET_DMA_INTR_EN_RUE_MASK)
#define ENET_DMA_INTR_EN_RUE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_RUE_MASK) >> ENET_DMA_INTR_EN_RUE_SHIFT)

/*
 * RIE (RW)
 *
 * Receive Interrupt Enable
 * When this bit is set with Normal Interrupt Summary Enable (Bit 16), the Receive Interrupt is enabled. When this bit is reset, the Receive Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_RIE_MASK (0x40U)
#define ENET_DMA_INTR_EN_RIE_SHIFT (6U)
#define ENET_DMA_INTR_EN_RIE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_RIE_SHIFT) & ENET_DMA_INTR_EN_RIE_MASK)
#define ENET_DMA_INTR_EN_RIE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_RIE_MASK) >> ENET_DMA_INTR_EN_RIE_SHIFT)

/*
 * UNE (RW)
 *
 * Underflow Interrupt Enable
 * When this bit is set with Abnormal Interrupt Summary Enable (Bit 15), the Transmit Underflow Interrupt is enabled. When this bit is reset, the Underflow Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_UNE_MASK (0x20U)
#define ENET_DMA_INTR_EN_UNE_SHIFT (5U)
#define ENET_DMA_INTR_EN_UNE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_UNE_SHIFT) & ENET_DMA_INTR_EN_UNE_MASK)
#define ENET_DMA_INTR_EN_UNE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_UNE_MASK) >> ENET_DMA_INTR_EN_UNE_SHIFT)

/*
 * OVE (RW)
 *
 * Overflow Interrupt Enable
 * When this bit is set with Abnormal Interrupt Summary Enable (Bit 15), the Receive Overflow Interrupt is enabled. When this bit is reset, the Overflow Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_OVE_MASK (0x10U)
#define ENET_DMA_INTR_EN_OVE_SHIFT (4U)
#define ENET_DMA_INTR_EN_OVE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_OVE_SHIFT) & ENET_DMA_INTR_EN_OVE_MASK)
#define ENET_DMA_INTR_EN_OVE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_OVE_MASK) >> ENET_DMA_INTR_EN_OVE_SHIFT)

/*
 * TJE (RW)
 *
 * Transmit Jabber Timeout Enable
 * When this bit is set with Abnormal Interrupt Summary Enable (Bit 15), the Transmit Jabber Timeout Interrupt is enabled. When this bit is reset, the Transmit Jabber Timeout Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_TJE_MASK (0x8U)
#define ENET_DMA_INTR_EN_TJE_SHIFT (3U)
#define ENET_DMA_INTR_EN_TJE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_TJE_SHIFT) & ENET_DMA_INTR_EN_TJE_MASK)
#define ENET_DMA_INTR_EN_TJE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_TJE_MASK) >> ENET_DMA_INTR_EN_TJE_SHIFT)

/*
 * TUE (RW)
 *
 * Transmit Buffer Unavailable Enable
 * When this bit is set with Normal Interrupt Summary Enable (Bit 16), the Transmit Buffer Unavailable Interrupt is enabled. When this bit is reset, the Transmit Buffer Unavailable Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_TUE_MASK (0x4U)
#define ENET_DMA_INTR_EN_TUE_SHIFT (2U)
#define ENET_DMA_INTR_EN_TUE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_TUE_SHIFT) & ENET_DMA_INTR_EN_TUE_MASK)
#define ENET_DMA_INTR_EN_TUE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_TUE_MASK) >> ENET_DMA_INTR_EN_TUE_SHIFT)

/*
 * TSE (RW)
 *
 * Transmit Stopped Enable
 * When this bit is set with Abnormal Interrupt Summary Enable (Bit 15), the Transmission Stopped Interrupt is enabled. When this bit is reset, the Transmission Stopped Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_TSE_MASK (0x2U)
#define ENET_DMA_INTR_EN_TSE_SHIFT (1U)
#define ENET_DMA_INTR_EN_TSE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_TSE_SHIFT) & ENET_DMA_INTR_EN_TSE_MASK)
#define ENET_DMA_INTR_EN_TSE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_TSE_MASK) >> ENET_DMA_INTR_EN_TSE_SHIFT)

/*
 * TIE (RW)
 *
 * Transmit Interrupt Enable
 * When this bit is set with Normal Interrupt Summary Enable (Bit 16), the Transmit Interrupt is enabled. When this bit is reset, the Transmit Interrupt is disabled.
 */
#define ENET_DMA_INTR_EN_TIE_MASK (0x1U)
#define ENET_DMA_INTR_EN_TIE_SHIFT (0U)
#define ENET_DMA_INTR_EN_TIE_SET(x) (((uint32_t)(x) << ENET_DMA_INTR_EN_TIE_SHIFT) & ENET_DMA_INTR_EN_TIE_MASK)
#define ENET_DMA_INTR_EN_TIE_GET(x) (((uint32_t)(x) & ENET_DMA_INTR_EN_TIE_MASK) >> ENET_DMA_INTR_EN_TIE_SHIFT)

/* Bitfield definition for register: DMA_MISS_OVF_CNT */
/*
 * ONFCNTOVF (RW)
 *
 * Overflow Bit for FIFO Overflow Counter
 * This bit is set every time the Overflow Frame Counter (Bits[27:17]) overflows,
 * that is, the Rx FIFO overflows with the overflow frame counter at maximum value.
 * In such a scenario, the overflow frame counter is reset to all-zeros and this bit indicates that the rollover happened.
 */
#define ENET_DMA_MISS_OVF_CNT_ONFCNTOVF_MASK (0x10000000UL)
#define ENET_DMA_MISS_OVF_CNT_ONFCNTOVF_SHIFT (28U)
#define ENET_DMA_MISS_OVF_CNT_ONFCNTOVF_SET(x) (((uint32_t)(x) << ENET_DMA_MISS_OVF_CNT_ONFCNTOVF_SHIFT) & ENET_DMA_MISS_OVF_CNT_ONFCNTOVF_MASK)
#define ENET_DMA_MISS_OVF_CNT_ONFCNTOVF_GET(x) (((uint32_t)(x) & ENET_DMA_MISS_OVF_CNT_ONFCNTOVF_MASK) >> ENET_DMA_MISS_OVF_CNT_ONFCNTOVF_SHIFT)

/*
 * OVFFRMCNT (RW)
 *
 * Overflow Frame Counter
 * This field indicates the number of frames missed by the application. This counter is incremented each time the MTL FIFO overflows. The counter is cleared when this register is read with mci_be_i[2] at 1’b1.
 */
#define ENET_DMA_MISS_OVF_CNT_OVFFRMCNT_MASK (0xFFE0000UL)
#define ENET_DMA_MISS_OVF_CNT_OVFFRMCNT_SHIFT (17U)
#define ENET_DMA_MISS_OVF_CNT_OVFFRMCNT_SET(x) (((uint32_t)(x) << ENET_DMA_MISS_OVF_CNT_OVFFRMCNT_SHIFT) & ENET_DMA_MISS_OVF_CNT_OVFFRMCNT_MASK)
#define ENET_DMA_MISS_OVF_CNT_OVFFRMCNT_GET(x) (((uint32_t)(x) & ENET_DMA_MISS_OVF_CNT_OVFFRMCNT_MASK) >> ENET_DMA_MISS_OVF_CNT_OVFFRMCNT_SHIFT)

/*
 * MISCNTOVF (RW)
 *
 * Overflow Bit for Missed Frame Counter
 * This bit is set every time Missed Frame Counter (Bits[15:0]) overflows,
 * that is, the DMA discards an incoming frame because of the Host Receive Buffer being unavailable with the missed frame counter at maximum value. In such a scenario,
 *  the Missed frame counter is reset to all-zeros and this bit indicates that the rollover happened.
 */
#define ENET_DMA_MISS_OVF_CNT_MISCNTOVF_MASK (0x10000UL)
#define ENET_DMA_MISS_OVF_CNT_MISCNTOVF_SHIFT (16U)
#define ENET_DMA_MISS_OVF_CNT_MISCNTOVF_SET(x) (((uint32_t)(x) << ENET_DMA_MISS_OVF_CNT_MISCNTOVF_SHIFT) & ENET_DMA_MISS_OVF_CNT_MISCNTOVF_MASK)
#define ENET_DMA_MISS_OVF_CNT_MISCNTOVF_GET(x) (((uint32_t)(x) & ENET_DMA_MISS_OVF_CNT_MISCNTOVF_MASK) >> ENET_DMA_MISS_OVF_CNT_MISCNTOVF_SHIFT)

/*
 * MISFRMCNT (RW)
 *
 * Missed Frame Counter
 * This field indicates the number of frames missed by the controller because of the Host Receive Buffer being unavailable.
 * This counter is incremented each time the DMA discards an incoming frame. The counter is cleared when this register is read with mci_be_i[0] at 1’b1.
 */
#define ENET_DMA_MISS_OVF_CNT_MISFRMCNT_MASK (0xFFFFU)
#define ENET_DMA_MISS_OVF_CNT_MISFRMCNT_SHIFT (0U)
#define ENET_DMA_MISS_OVF_CNT_MISFRMCNT_SET(x) (((uint32_t)(x) << ENET_DMA_MISS_OVF_CNT_MISFRMCNT_SHIFT) & ENET_DMA_MISS_OVF_CNT_MISFRMCNT_MASK)
#define ENET_DMA_MISS_OVF_CNT_MISFRMCNT_GET(x) (((uint32_t)(x) & ENET_DMA_MISS_OVF_CNT_MISFRMCNT_MASK) >> ENET_DMA_MISS_OVF_CNT_MISFRMCNT_SHIFT)

/* Bitfield definition for register: DMA_RX_INTR_WDOG */
/*
 * RIWT (RW)
 *
 * RI Watchdog Timer Count
 * This bit indicates the number of system clock cycles multiplied by 256 for which the watchdog timer is set.
 * The watchdog timer gets triggered with the programmed value after the Rx DMA completes the transfer
 * of a frame for which the RI status bit is not set because of the setting in the corresponding descriptor RDES1[31].
 * When the watchdog timer runs out, the RI bit is set and the timer is stopped.
 * The watchdog timer is reset when the RI bit is set high because of automatic setting of RI as per RDES1[31] of any received frame.
 */
#define ENET_DMA_RX_INTR_WDOG_RIWT_MASK (0xFFU)
#define ENET_DMA_RX_INTR_WDOG_RIWT_SHIFT (0U)
#define ENET_DMA_RX_INTR_WDOG_RIWT_SET(x) (((uint32_t)(x) << ENET_DMA_RX_INTR_WDOG_RIWT_SHIFT) & ENET_DMA_RX_INTR_WDOG_RIWT_MASK)
#define ENET_DMA_RX_INTR_WDOG_RIWT_GET(x) (((uint32_t)(x) & ENET_DMA_RX_INTR_WDOG_RIWT_MASK) >> ENET_DMA_RX_INTR_WDOG_RIWT_SHIFT)

/* Bitfield definition for register: DMA_AXI_MODE */
/*
 * EN_LPI (RW)
 *
 * Enable Low Power Interface (LPI)
 * When set to 1, this bit enables the LPI mode supported by the GMAC-AXI configuration and accepts the LPI request from the AXI System Clock controller.
 * When set to 0, this bit disables the LPI mode and always denies the LPI request from the AXI System Clock controller.
 */
#define ENET_DMA_AXI_MODE_EN_LPI_MASK (0x80000000UL)
#define ENET_DMA_AXI_MODE_EN_LPI_SHIFT (31U)
#define ENET_DMA_AXI_MODE_EN_LPI_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_EN_LPI_SHIFT) & ENET_DMA_AXI_MODE_EN_LPI_MASK)
#define ENET_DMA_AXI_MODE_EN_LPI_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_EN_LPI_MASK) >> ENET_DMA_AXI_MODE_EN_LPI_SHIFT)

/*
 * LPI_XIT_FRM (RW)
 *
 * Unlock on Magic Packet or Remote Wake-Up Frame
 * When set to 1, this bit enables the GMAC-AXI to come out of the LPI mode only when the magic packet or remote wake-up frame is received.
 * When set to 0, this bit enables the GMAC-AXI to come out of LPI mode when any frame is received.
 */
#define ENET_DMA_AXI_MODE_LPI_XIT_FRM_MASK (0x40000000UL)
#define ENET_DMA_AXI_MODE_LPI_XIT_FRM_SHIFT (30U)
#define ENET_DMA_AXI_MODE_LPI_XIT_FRM_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_LPI_XIT_FRM_SHIFT) & ENET_DMA_AXI_MODE_LPI_XIT_FRM_MASK)
#define ENET_DMA_AXI_MODE_LPI_XIT_FRM_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_LPI_XIT_FRM_MASK) >> ENET_DMA_AXI_MODE_LPI_XIT_FRM_SHIFT)

/*
 * WR_OSR_LMT (RW)
 *
 * AXI Maximum Write Outstanding Request Limit
 * This value limits the maximum outstanding request on the AXI write interface.
 * Maximum outstanding requests = WR_OSR_LMT+1 Note: - Bit 22 is reserved if AXI_GM_MAX_WR_REQUESTS = 4. - Bit 23 bit is reserved if AXI_GM_MAX_WR_REQUESTS != 16.
 */
#define ENET_DMA_AXI_MODE_WR_OSR_LMT_MASK (0xF00000UL)
#define ENET_DMA_AXI_MODE_WR_OSR_LMT_SHIFT (20U)
#define ENET_DMA_AXI_MODE_WR_OSR_LMT_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_WR_OSR_LMT_SHIFT) & ENET_DMA_AXI_MODE_WR_OSR_LMT_MASK)
#define ENET_DMA_AXI_MODE_WR_OSR_LMT_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_WR_OSR_LMT_MASK) >> ENET_DMA_AXI_MODE_WR_OSR_LMT_SHIFT)

/*
 * RD_OSR_LMT (RW)
 *
 * AXI Maximum Read Outstanding Request Limit
 * This value limits the maximum outstanding request on the AXI read interface.
 * Maximum outstanding requests = RD_OSR_LMT+1 Note: - Bit 18 is reserved if AXI_GM_MAX_RD_REQUESTS = 4. - Bit 19 is reserved if AXI_GM_MAX_RD_REQUESTS != 16.
 */
#define ENET_DMA_AXI_MODE_RD_OSR_LMT_MASK (0xF0000UL)
#define ENET_DMA_AXI_MODE_RD_OSR_LMT_SHIFT (16U)
#define ENET_DMA_AXI_MODE_RD_OSR_LMT_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_RD_OSR_LMT_SHIFT) & ENET_DMA_AXI_MODE_RD_OSR_LMT_MASK)
#define ENET_DMA_AXI_MODE_RD_OSR_LMT_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_RD_OSR_LMT_MASK) >> ENET_DMA_AXI_MODE_RD_OSR_LMT_SHIFT)

/*
 * ONEKBBE (RW)
 *
 * 1 KB Boundary Crossing Enable for the GMAC-AXI Master
 * When set, the GMAC-AXI master performs burst transfers that do not cross 1 KB boundary.
 * When reset, the GMAC-AXI master performs burst transfers that do not cross 4 KB boundary.
 */
#define ENET_DMA_AXI_MODE_ONEKBBE_MASK (0x2000U)
#define ENET_DMA_AXI_MODE_ONEKBBE_SHIFT (13U)
#define ENET_DMA_AXI_MODE_ONEKBBE_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_ONEKBBE_SHIFT) & ENET_DMA_AXI_MODE_ONEKBBE_MASK)
#define ENET_DMA_AXI_MODE_ONEKBBE_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_ONEKBBE_MASK) >> ENET_DMA_AXI_MODE_ONEKBBE_SHIFT)

/*
 * AXI_AAL (RW)
 *
 * Address-Aligned Beats
 * This bit is read-only bit and reflects the Bit 25 (AAL) of Register 0 (Bus Mode Register).
 * When this bit is set to 1, the GMAC-AXI performs address-aligned burst transfers on both read and write channels.
 */
#define ENET_DMA_AXI_MODE_AXI_AAL_MASK (0x1000U)
#define ENET_DMA_AXI_MODE_AXI_AAL_SHIFT (12U)
#define ENET_DMA_AXI_MODE_AXI_AAL_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_AXI_AAL_SHIFT) & ENET_DMA_AXI_MODE_AXI_AAL_MASK)
#define ENET_DMA_AXI_MODE_AXI_AAL_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_AXI_AAL_MASK) >> ENET_DMA_AXI_MODE_AXI_AAL_SHIFT)

/*
 * BLEN256 (RW)
 *
 * AXI Burst Length 256
 * When this bit is set to 1, the GMAC-AXI is allowed to select a burst length of 256 on the AXI master interface.
 * This bit is present only when the configuration parameter AXI_BL is set to 256. Otherwise, this bit is reserved and is read-only (RO).
 */
#define ENET_DMA_AXI_MODE_BLEN256_MASK (0x80U)
#define ENET_DMA_AXI_MODE_BLEN256_SHIFT (7U)
#define ENET_DMA_AXI_MODE_BLEN256_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_BLEN256_SHIFT) & ENET_DMA_AXI_MODE_BLEN256_MASK)
#define ENET_DMA_AXI_MODE_BLEN256_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_BLEN256_MASK) >> ENET_DMA_AXI_MODE_BLEN256_SHIFT)

/*
 * BLEN128 (RW)
 *
 * AXI Burst Length 128
 * When this bit is set to 1, the GMAC-AXI is allowed to select a burst length of 128 on the AXI master interface.
 * This bit is present only when the configuration parameter AXI_BL is set to 128 or more. Otherwise, this bit is reserved and is read-only (RO).
 */
#define ENET_DMA_AXI_MODE_BLEN128_MASK (0x40U)
#define ENET_DMA_AXI_MODE_BLEN128_SHIFT (6U)
#define ENET_DMA_AXI_MODE_BLEN128_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_BLEN128_SHIFT) & ENET_DMA_AXI_MODE_BLEN128_MASK)
#define ENET_DMA_AXI_MODE_BLEN128_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_BLEN128_MASK) >> ENET_DMA_AXI_MODE_BLEN128_SHIFT)

/*
 * BLEN64 (RW)
 *
 * AXI Burst Length 64
 * When this bit is set to 1, the GMAC-AXI is allowed to select a burst length of 64 on the AXI master interface.
 * This bit is present only when the configuration parameter AXI_BL is set to 64 or more. Otherwise, this bit is reserved and is read-only (RO).
 */
#define ENET_DMA_AXI_MODE_BLEN64_MASK (0x20U)
#define ENET_DMA_AXI_MODE_BLEN64_SHIFT (5U)
#define ENET_DMA_AXI_MODE_BLEN64_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_BLEN64_SHIFT) & ENET_DMA_AXI_MODE_BLEN64_MASK)
#define ENET_DMA_AXI_MODE_BLEN64_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_BLEN64_MASK) >> ENET_DMA_AXI_MODE_BLEN64_SHIFT)

/*
 * BLEN32 (RW)
 *
 * AXI Burst Length 32
 * When this bit is set to 1, the GMAC-AXI is allowed to select a burst length of 32 on the AXI master interface.
 * This bit is present only when the configuration parameter AXI_BL is set to 32 or more. Otherwise, this bit is reserved and is read-only (RO).
 */
#define ENET_DMA_AXI_MODE_BLEN32_MASK (0x10U)
#define ENET_DMA_AXI_MODE_BLEN32_SHIFT (4U)
#define ENET_DMA_AXI_MODE_BLEN32_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_BLEN32_SHIFT) & ENET_DMA_AXI_MODE_BLEN32_MASK)
#define ENET_DMA_AXI_MODE_BLEN32_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_BLEN32_MASK) >> ENET_DMA_AXI_MODE_BLEN32_SHIFT)

/*
 * BLEN16 (RW)
 *
 * AXI Burst Length 16
 * When this bit is set to 1 or UNDEF is set to 1, the GMAC-AXI is allowed to select a burst length of 16 on the AXI master interface.
 */
#define ENET_DMA_AXI_MODE_BLEN16_MASK (0x8U)
#define ENET_DMA_AXI_MODE_BLEN16_SHIFT (3U)
#define ENET_DMA_AXI_MODE_BLEN16_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_BLEN16_SHIFT) & ENET_DMA_AXI_MODE_BLEN16_MASK)
#define ENET_DMA_AXI_MODE_BLEN16_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_BLEN16_MASK) >> ENET_DMA_AXI_MODE_BLEN16_SHIFT)

/*
 * BLEN8 (RW)
 *
 * AXI Burst Length 8
 * When this bit is set to 1, the GMAC-AXI is allowed to select a burst length of 8 on the AXI master interface.
 * Setting this bit has no effect when UNDEF is set to 1.
 */
#define ENET_DMA_AXI_MODE_BLEN8_MASK (0x4U)
#define ENET_DMA_AXI_MODE_BLEN8_SHIFT (2U)
#define ENET_DMA_AXI_MODE_BLEN8_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_BLEN8_SHIFT) & ENET_DMA_AXI_MODE_BLEN8_MASK)
#define ENET_DMA_AXI_MODE_BLEN8_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_BLEN8_MASK) >> ENET_DMA_AXI_MODE_BLEN8_SHIFT)

/*
 * BLEN4 (RW)
 *
 * AXI Burst Length 4
 * When this bit is set to 1, the GMAC-AXI is allowed to select a burst length of 4 on the AXI master interface.
 * Setting this bit has no effect when UNDEF is set to 1.
 */
#define ENET_DMA_AXI_MODE_BLEN4_MASK (0x2U)
#define ENET_DMA_AXI_MODE_BLEN4_SHIFT (1U)
#define ENET_DMA_AXI_MODE_BLEN4_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_BLEN4_SHIFT) & ENET_DMA_AXI_MODE_BLEN4_MASK)
#define ENET_DMA_AXI_MODE_BLEN4_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_BLEN4_MASK) >> ENET_DMA_AXI_MODE_BLEN4_SHIFT)

/*
 * UNDEF (RW)
 *
 * AXI Undefined Burst Length
 * This bit is read-only bit and indicates the complement (invert) value of Bit 16 (FB) in Register 0 (Bus Mode Register).
 * - When this bit is set to 1, the GMAC-AXI is allowed to perform any burst length equal to or below the maximum allowed burst length programmed in Bits[7:3].
 * - When this bit is set to 0, the GMAC-AXI is allowed to perform only fixed burst lengths as indicated by BLEN256, BLEN128, BLEN64, BLEN32, BLEN16, BLEN8, or BLEN4, or a burst length of 1.
 * If UNDEF is set and none of the BLEN bits is set, then GMAC-AXI is allowed to perform a burst length of 16.
 */
#define ENET_DMA_AXI_MODE_UNDEF_MASK (0x1U)
#define ENET_DMA_AXI_MODE_UNDEF_SHIFT (0U)
#define ENET_DMA_AXI_MODE_UNDEF_SET(x) (((uint32_t)(x) << ENET_DMA_AXI_MODE_UNDEF_SHIFT) & ENET_DMA_AXI_MODE_UNDEF_MASK)
#define ENET_DMA_AXI_MODE_UNDEF_GET(x) (((uint32_t)(x) & ENET_DMA_AXI_MODE_UNDEF_MASK) >> ENET_DMA_AXI_MODE_UNDEF_SHIFT)

/* Bitfield definition for register: DMA_BUS_STATUS */
/*
 * AXIRDSTS (RW)
 *
 * AXI Master Read Channel Status
 * When high, it indicates that AXI master's read channel is active and transferring data.
 */
#define ENET_DMA_BUS_STATUS_AXIRDSTS_MASK (0x2U)
#define ENET_DMA_BUS_STATUS_AXIRDSTS_SHIFT (1U)
#define ENET_DMA_BUS_STATUS_AXIRDSTS_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_STATUS_AXIRDSTS_SHIFT) & ENET_DMA_BUS_STATUS_AXIRDSTS_MASK)
#define ENET_DMA_BUS_STATUS_AXIRDSTS_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_STATUS_AXIRDSTS_MASK) >> ENET_DMA_BUS_STATUS_AXIRDSTS_SHIFT)

/*
 * AXWHSTS (RW)
 *
 * AXI Master Write Channel or AHB Master Status
 * When high, it indicates that AXI master's write channel is active and transferring data in the GMAC-AXI configuration. In the GMAC-AHB configuration,
 *  it indicates that the AHB master interface FSMs are in the non-idle state.
 */
#define ENET_DMA_BUS_STATUS_AXWHSTS_MASK (0x1U)
#define ENET_DMA_BUS_STATUS_AXWHSTS_SHIFT (0U)
#define ENET_DMA_BUS_STATUS_AXWHSTS_SET(x) (((uint32_t)(x) << ENET_DMA_BUS_STATUS_AXWHSTS_SHIFT) & ENET_DMA_BUS_STATUS_AXWHSTS_MASK)
#define ENET_DMA_BUS_STATUS_AXWHSTS_GET(x) (((uint32_t)(x) & ENET_DMA_BUS_STATUS_AXWHSTS_MASK) >> ENET_DMA_BUS_STATUS_AXWHSTS_SHIFT)

/* Bitfield definition for register: DMA_CURR_HOST_TX_DESC */
/*
 * CURTDESAPTR (RW)
 *
 * Host Transmit Descriptor Address Pointer
 * Cleared on Reset. Pointer updated by the DMA during operation.
 */
#define ENET_DMA_CURR_HOST_TX_DESC_CURTDESAPTR_MASK (0xFFFFFFFFUL)
#define ENET_DMA_CURR_HOST_TX_DESC_CURTDESAPTR_SHIFT (0U)
#define ENET_DMA_CURR_HOST_TX_DESC_CURTDESAPTR_SET(x) (((uint32_t)(x) << ENET_DMA_CURR_HOST_TX_DESC_CURTDESAPTR_SHIFT) & ENET_DMA_CURR_HOST_TX_DESC_CURTDESAPTR_MASK)
#define ENET_DMA_CURR_HOST_TX_DESC_CURTDESAPTR_GET(x) (((uint32_t)(x) & ENET_DMA_CURR_HOST_TX_DESC_CURTDESAPTR_MASK) >> ENET_DMA_CURR_HOST_TX_DESC_CURTDESAPTR_SHIFT)

/* Bitfield definition for register: DMA_CURR_HOST_RX_DESC */
/*
 * CURRDESAPTR (RW)
 *
 * Host Receive Descriptor Address Pointer
 * Cleared on Reset. Pointer updated by the DMA during operation.
 */
#define ENET_DMA_CURR_HOST_RX_DESC_CURRDESAPTR_MASK (0xFFFFFFFFUL)
#define ENET_DMA_CURR_HOST_RX_DESC_CURRDESAPTR_SHIFT (0U)
#define ENET_DMA_CURR_HOST_RX_DESC_CURRDESAPTR_SET(x) (((uint32_t)(x) << ENET_DMA_CURR_HOST_RX_DESC_CURRDESAPTR_SHIFT) & ENET_DMA_CURR_HOST_RX_DESC_CURRDESAPTR_MASK)
#define ENET_DMA_CURR_HOST_RX_DESC_CURRDESAPTR_GET(x) (((uint32_t)(x) & ENET_DMA_CURR_HOST_RX_DESC_CURRDESAPTR_MASK) >> ENET_DMA_CURR_HOST_RX_DESC_CURRDESAPTR_SHIFT)

/* Bitfield definition for register: DMA_CURR_HOST_TX_BUF */
/*
 * CURTBUFAPTR (RW)
 *
 * Host Transmit Buffer Address Pointer
 * Cleared on Reset. Pointer updated by the DMA during operation.
 */
#define ENET_DMA_CURR_HOST_TX_BUF_CURTBUFAPTR_MASK (0xFFFFFFFFUL)
#define ENET_DMA_CURR_HOST_TX_BUF_CURTBUFAPTR_SHIFT (0U)
#define ENET_DMA_CURR_HOST_TX_BUF_CURTBUFAPTR_SET(x) (((uint32_t)(x) << ENET_DMA_CURR_HOST_TX_BUF_CURTBUFAPTR_SHIFT) & ENET_DMA_CURR_HOST_TX_BUF_CURTBUFAPTR_MASK)
#define ENET_DMA_CURR_HOST_TX_BUF_CURTBUFAPTR_GET(x) (((uint32_t)(x) & ENET_DMA_CURR_HOST_TX_BUF_CURTBUFAPTR_MASK) >> ENET_DMA_CURR_HOST_TX_BUF_CURTBUFAPTR_SHIFT)

/* Bitfield definition for register: DMA_CURR_HOST_RX_BUF */
/*
 * CURRBUFAPTR (RW)
 *
 * Host Receive Buffer Address Pointer
 * Cleared on Reset. Pointer updated by the DMA during operation.
 */
#define ENET_DMA_CURR_HOST_RX_BUF_CURRBUFAPTR_MASK (0xFFFFFFFFUL)
#define ENET_DMA_CURR_HOST_RX_BUF_CURRBUFAPTR_SHIFT (0U)
#define ENET_DMA_CURR_HOST_RX_BUF_CURRBUFAPTR_SET(x) (((uint32_t)(x) << ENET_DMA_CURR_HOST_RX_BUF_CURRBUFAPTR_SHIFT) & ENET_DMA_CURR_HOST_RX_BUF_CURRBUFAPTR_MASK)
#define ENET_DMA_CURR_HOST_RX_BUF_CURRBUFAPTR_GET(x) (((uint32_t)(x) & ENET_DMA_CURR_HOST_RX_BUF_CURRBUFAPTR_MASK) >> ENET_DMA_CURR_HOST_RX_BUF_CURRBUFAPTR_SHIFT)

/* Bitfield definition for register: CTRL2 */
/*
 * ENET0_LPI_IRQ_EN (RW)
 *
 * lowpower interrupt enable, for internal use only, user should use core registers for enable/disable interrupt
 */
#define ENET_CTRL2_ENET0_LPI_IRQ_EN_MASK (0x20000000UL)
#define ENET_CTRL2_ENET0_LPI_IRQ_EN_SHIFT (29U)
#define ENET_CTRL2_ENET0_LPI_IRQ_EN_SET(x) (((uint32_t)(x) << ENET_CTRL2_ENET0_LPI_IRQ_EN_SHIFT) & ENET_CTRL2_ENET0_LPI_IRQ_EN_MASK)
#define ENET_CTRL2_ENET0_LPI_IRQ_EN_GET(x) (((uint32_t)(x) & ENET_CTRL2_ENET0_LPI_IRQ_EN_MASK) >> ENET_CTRL2_ENET0_LPI_IRQ_EN_SHIFT)

/*
 * ENET0_REFCLK_OE (RW)
 *
 * set to enable output 50MHz clock to rmii phy.
 * User should set it if use soc internal clock as refclk
 */
#define ENET_CTRL2_ENET0_REFCLK_OE_MASK (0x80000UL)
#define ENET_CTRL2_ENET0_REFCLK_OE_SHIFT (19U)
#define ENET_CTRL2_ENET0_REFCLK_OE_SET(x) (((uint32_t)(x) << ENET_CTRL2_ENET0_REFCLK_OE_SHIFT) & ENET_CTRL2_ENET0_REFCLK_OE_MASK)
#define ENET_CTRL2_ENET0_REFCLK_OE_GET(x) (((uint32_t)(x) & ENET_CTRL2_ENET0_REFCLK_OE_MASK) >> ENET_CTRL2_ENET0_REFCLK_OE_SHIFT)

/*
 * ENET0_PHY_INF_SEL (RW)
 *
 * PHY mode select
 * 001RGMII; 100RMII;
 * should be set before config IOMUX, otherwise may cause glitch for RGMII
 */
#define ENET_CTRL2_ENET0_PHY_INF_SEL_MASK (0xE000U)
#define ENET_CTRL2_ENET0_PHY_INF_SEL_SHIFT (13U)
#define ENET_CTRL2_ENET0_PHY_INF_SEL_SET(x) (((uint32_t)(x) << ENET_CTRL2_ENET0_PHY_INF_SEL_SHIFT) & ENET_CTRL2_ENET0_PHY_INF_SEL_MASK)
#define ENET_CTRL2_ENET0_PHY_INF_SEL_GET(x) (((uint32_t)(x) & ENET_CTRL2_ENET0_PHY_INF_SEL_MASK) >> ENET_CTRL2_ENET0_PHY_INF_SEL_SHIFT)

/*
 * ENET0_FLOWCTRL (RW)
 *
 * flow control request
 */
#define ENET_CTRL2_ENET0_FLOWCTRL_MASK (0x1000U)
#define ENET_CTRL2_ENET0_FLOWCTRL_SHIFT (12U)
#define ENET_CTRL2_ENET0_FLOWCTRL_SET(x) (((uint32_t)(x) << ENET_CTRL2_ENET0_FLOWCTRL_SHIFT) & ENET_CTRL2_ENET0_FLOWCTRL_MASK)
#define ENET_CTRL2_ENET0_FLOWCTRL_GET(x) (((uint32_t)(x) & ENET_CTRL2_ENET0_FLOWCTRL_MASK) >> ENET_CTRL2_ENET0_FLOWCTRL_SHIFT)

/*
 * ENET0_RMII_TXCLK_SEL (RW)
 *
 * RMII mode output clock pad select
 * set to use refclk from pad;
 * Note: refclk is always from pad, can use external clock from pad, or use internal clock output to pad then loopback.
 */
#define ENET_CTRL2_ENET0_RMII_TXCLK_SEL_MASK (0x400U)
#define ENET_CTRL2_ENET0_RMII_TXCLK_SEL_SHIFT (10U)
#define ENET_CTRL2_ENET0_RMII_TXCLK_SEL_SET(x) (((uint32_t)(x) << ENET_CTRL2_ENET0_RMII_TXCLK_SEL_SHIFT) & ENET_CTRL2_ENET0_RMII_TXCLK_SEL_MASK)
#define ENET_CTRL2_ENET0_RMII_TXCLK_SEL_GET(x) (((uint32_t)(x) & ENET_CTRL2_ENET0_RMII_TXCLK_SEL_MASK) >> ENET_CTRL2_ENET0_RMII_TXCLK_SEL_SHIFT)



/* MAC_ADDR register group index macro definition */
#define ENET_MAC_ADDR_1 (0UL)
#define ENET_MAC_ADDR_2 (1UL)
#define ENET_MAC_ADDR_3 (2UL)
#define ENET_MAC_ADDR_4 (3UL)

/* L3_L4_CFG register group index macro definition */
#define ENET_L3_L4_CFG_0 (0UL)

/* PPS register group index macro definition */
#define ENET_PPS_1 (0UL)
#define ENET_PPS_2 (1UL)
#define ENET_PPS_3 (2UL)


#endif /* HPM_ENET_H */
