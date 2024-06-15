/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DP83848_REGS_H
#define HPM_DP83848_REGS_H

typedef enum {
    DP83848_BMCR                        = 0,   /* 0x0: Basic Mode Control Register */
    DP83848_BMSR                        = 1,   /* 0x1: Basic Mode Status Register */
    DP83848_PHYIDR1                     = 2,   /* 0x2: PHY Identifier Register #1 */
    DP83848_PHYIDR2                     = 3,   /* 0x3: PHY Identifier Register #2 */
    DP83848_ANAR                        = 4,   /* 0x4: Auto-Negotiation Advertisement Register */
    DP83848_ANLPAR_BP                   = 5,   /* 0x5: Auto-Negotiation Link Partner Ability Register */
    DP83848_ANER                        = 6,   /* 0x6: Auto-Negotiate Expansion Register */
    DP83848_ANNPTR                      = 7,   /* 0x7: Auto-Negotiation Next Page Transmit Register */
    DP83848_PHYSTS                      = 16,  /* 0x10: PHY Status Register */
    DP83848_FCSCR                       = 20,  /* 0x14: False Carrier Sense Counter Register */
    DP83848_RECR                        = 21,  /* 0x15: Receiver Error Counter Register */
    DP83848_PCSR                        = 22,  /* 0x16: 100 Mb/s PCS Configuration and Status Register */
    DP83848_RBR                         = 23,  /* 0x17: RMII and Bypass Register */
    DP83848_LEDCR                       = 24,  /* 0x18: LED Direct Control Register */
    DP83848_PHYCR                       = 25,  /* 0x19: PHY Control Register */
    DP83848_10BTSCR                     = 26,  /* 0x1A: 10BASE-T Status/Control Register */
    DP83848_CDCTRL1                     = 27,  /* 0x1B: CD Test and BIST Extensions Register */
    DP83848_EDCR                        = 29,  /* 0x1D: Energy Detect Control */
} DP83848_REG_Type;


/* Bitfield definition for register: BMCR */
/*
 * RESET (RW/SC)
 *
 * Reset:
 * 1 = Initiate software Reset / Reset in Process.
 * 0 = Normal operation.
 * This bit, which is self-clearing, returns a value of one until the reset process is complete. The
 * configuration is re-strapped.
 */
#define DP83848_BMCR_RESET_MASK (0x8000U)
#define DP83848_BMCR_RESET_SHIFT (15U)
#define DP83848_BMCR_RESET_SET(x) (((uint16_t)(x) << DP83848_BMCR_RESET_SHIFT) & DP83848_BMCR_RESET_MASK)
#define DP83848_BMCR_RESET_GET(x) (((uint16_t)(x) & DP83848_BMCR_RESET_MASK) >> DP83848_BMCR_RESET_SHIFT)

/*
 * LOOPBACK (RW)
 *
 * Loopback:
 * 1 = Loopback enabled.
 * 0 = Normal operation.
 * The loopback function enables MII transmit data to be routed to the MII receive data path.
 * Setting this bit may cause the descrambler to lose synchronization and produce a 500 µs “dead
 * time” before any valid data will appear at the MII receive outputs.
 */
#define DP83848_BMCR_LOOPBACK_MASK (0x4000U)
#define DP83848_BMCR_LOOPBACK_SHIFT (14U)
#define DP83848_BMCR_LOOPBACK_SET(x) (((uint16_t)(x) << DP83848_BMCR_LOOPBACK_SHIFT) & DP83848_BMCR_LOOPBACK_MASK)
#define DP83848_BMCR_LOOPBACK_GET(x) (((uint16_t)(x) & DP83848_BMCR_LOOPBACK_MASK) >> DP83848_BMCR_LOOPBACK_SHIFT)

/*
 * SPEED0 (RW)
 *
 * Speed Select:
 * When auto-negotiation is disabled writing to this bit allows the port speed to be selected.
 * 1 = 100 Mb/s.
 * 0 = 10 Mb/s.
 */
#define DP83848_BMCR_SPEED0_MASK (0x2000U)
#define DP83848_BMCR_SPEED0_SHIFT (13U)
#define DP83848_BMCR_SPEED0_SET(x) (((uint16_t)(x) << DP83848_BMCR_SPEED0_SHIFT) & DP83848_BMCR_SPEED0_MASK)
#define DP83848_BMCR_SPEED0_GET(x) (((uint16_t)(x) & DP83848_BMCR_SPEED0_MASK) >> DP83848_BMCR_SPEED0_SHIFT)

/*
 * ANE (RW)
 *
 * Auto-Negotiation Enable:
 * Strap controls initial value at reset.
 * 1 = Auto-Negotiation Enabled - bits 8 and 13 of this register are ignored when this bit is set.
 * 0 = Auto-Negotiation Disabled - bits 8 and 13 determine the port speed and duplex mode.
 */
#define DP83848_BMCR_ANE_MASK (0x1000U)
#define DP83848_BMCR_ANE_SHIFT (12U)
#define DP83848_BMCR_ANE_SET(x) (((uint16_t)(x) << DP83848_BMCR_ANE_SHIFT) & DP83848_BMCR_ANE_MASK)
#define DP83848_BMCR_ANE_GET(x) (((uint16_t)(x) & DP83848_BMCR_ANE_MASK) >> DP83848_BMCR_ANE_SHIFT)

/*
 * PWD (RW)
 *
 * Power Down:
 * 1 = Power down.
 * 0 = Normal operation.
 * Setting this bit powers down the PHY. Only the register block is enabled during a power-down
 * condition.
 */
#define DP83848_BMCR_PWD_MASK (0x800U)
#define DP83848_BMCR_PWD_SHIFT (11U)
#define DP83848_BMCR_PWD_SET(x) (((uint16_t)(x) << DP83848_BMCR_PWD_SHIFT) & DP83848_BMCR_PWD_MASK)
#define DP83848_BMCR_PWD_GET(x) (((uint16_t)(x) & DP83848_BMCR_PWD_MASK) >> DP83848_BMCR_PWD_SHIFT)

/*
 * ISOLATE (RW)
 *
 * Isolate:
 * 1 = Isolates the Port from the MII with the exception of the serial management.
 * 0 = Normal operation.
 */
#define DP83848_BMCR_ISOLATE_MASK (0x400U)
#define DP83848_BMCR_ISOLATE_SHIFT (10U)
#define DP83848_BMCR_ISOLATE_SET(x) (((uint16_t)(x) << DP83848_BMCR_ISOLATE_SHIFT) & DP83848_BMCR_ISOLATE_MASK)
#define DP83848_BMCR_ISOLATE_GET(x) (((uint16_t)(x) & DP83848_BMCR_ISOLATE_MASK) >> DP83848_BMCR_ISOLATE_SHIFT)

/*
 * RESTART_AN (RW/SC)
 *
 * Restart Auto-Negotiation:
 * 1 = Restart Auto-Negotiation. Re-initiates the Auto-Negotiation process. If Auto-Negotiation is
 * disabled (bit 12 = 0), this bit is ignored. This bit is self-clearing and will return a value of 1 until
 * Auto-Negotiation is initiated, whereupon it will self-clear. Operation of the Auto-Negotiation
 * process is not affected by the management entity clearing this bit.
 * 0 = Normal operation.
 */
#define DP83848_BMCR_RESTART_AN_MASK (0x200U)
#define DP83848_BMCR_RESTART_AN_SHIFT (9U)
#define DP83848_BMCR_RESTART_AN_SET(x) (((uint16_t)(x) << DP83848_BMCR_RESTART_AN_SHIFT) & DP83848_BMCR_RESTART_AN_MASK)
#define DP83848_BMCR_RESTART_AN_GET(x) (((uint16_t)(x) & DP83848_BMCR_RESTART_AN_MASK) >> DP83848_BMCR_RESTART_AN_SHIFT)

/*
 * DUPLEX (RW)
 *
 * Duplex Mode:
 * When auto-negotiation is disabled writing to this bit allows the port Duplex capability to be
 * selected.
 * 1 = Full Duplex operation.
 * 0 = Half Duplex operation.
 */
#define DP83848_BMCR_DUPLEX_MASK (0x100U)
#define DP83848_BMCR_DUPLEX_SHIFT (8U)
#define DP83848_BMCR_DUPLEX_SET(x) (((uint16_t)(x) << DP83848_BMCR_DUPLEX_SHIFT) & DP83848_BMCR_DUPLEX_MASK)
#define DP83848_BMCR_DUPLEX_GET(x) (((uint16_t)(x) & DP83848_BMCR_DUPLEX_MASK) >> DP83848_BMCR_DUPLEX_SHIFT)

/*
 * COLLISION_TEST (RW)
 *
 * Collision Test:
 * 1 = Collision test enabled.
 * 0 = Normal operation.
 * When set, this bit will cause the COL signal to be asserted in response to the assertion of
 * TX_EN within 512-bit times. The COL signal will be deasserted within 4-bit times in response to
 * the deassertion of TX_EN.
 */
#define DP83848_BMCR_COLLISION_TEST_MASK (0x80U)
#define DP83848_BMCR_COLLISION_TEST_SHIFT (7U)
#define DP83848_BMCR_COLLISION_TEST_SET(x) (((uint16_t)(x) << DP83848_BMCR_COLLISION_TEST_SHIFT) & DP83848_BMCR_COLLISION_TEST_MASK)
#define DP83848_BMCR_COLLISION_TEST_GET(x) (((uint16_t)(x) & DP83848_BMCR_COLLISION_TEST_MASK) >> DP83848_BMCR_COLLISION_TEST_SHIFT)

/* Bitfield definition for register: BMSR */
/*
 * 100BASE_TX_FULL_DUPLEX (RO)
 *
 * 100BASE-TX Full Duplex Capable:
 * 1 = Device able to perform 100BASE-TX in full duplex mode.
 */
#define DP83848_BMSR_100BASE_TX_FULL_DUPLEX_MASK (0x4000U)
#define DP83848_BMSR_100BASE_TX_FULL_DUPLEX_SHIFT (14U)
#define DP83848_BMSR_100BASE_TX_FULL_DUPLEX_GET(x) (((uint16_t)(x) & DP83848_BMSR_100BASE_TX_FULL_DUPLEX_MASK) >> DP83848_BMSR_100BASE_TX_FULL_DUPLEX_SHIFT)

/*
 * 100BASE_TX_HALF (RO)
 *
 * 100BASE-TX Half Duplex Capable:
 * 1 = Device able to perform 100BASE-TX in half duplex mode.
 */
#define DP83848_BMSR_100BASE_TX_HALF_MASK (0x2000U)
#define DP83848_BMSR_100BASE_TX_HALF_SHIFT (13U)
#define DP83848_BMSR_100BASE_TX_HALF_GET(x) (((uint16_t)(x) & DP83848_BMSR_100BASE_TX_HALF_MASK) >> DP83848_BMSR_100BASE_TX_HALF_SHIFT)

/*
 * 10BASE_T_FULL_DUPLEX (RO)
 *
 * 10BASE-T Full Duplex Capable:
 * 1 = Device able to perform 10BASE-T in full duplex mode.
 */
#define DP83848_BMSR_10BASE_T_FULL_DUPLEX_MASK (0x1000U)
#define DP83848_BMSR_10BASE_T_FULL_DUPLEX_SHIFT (12U)
#define DP83848_BMSR_10BASE_T_FULL_DUPLEX_GET(x) (((uint16_t)(x) & DP83848_BMSR_10BASE_T_FULL_DUPLEX_MASK) >> DP83848_BMSR_10BASE_T_FULL_DUPLEX_SHIFT)

/*
 * 10BASE_T_HALF_DUPLEX (RO)
 *
 * 10BASE-T Half Duplex Capable:
 * 1 = Device able to perform 10BASE-T in half duplex mode.
 */
#define DP83848_BMSR_10BASE_T_HALF_DUPLEX_MASK (0x800U)
#define DP83848_BMSR_10BASE_T_HALF_DUPLEX_SHIFT (11U)
#define DP83848_BMSR_10BASE_T_HALF_DUPLEX_GET(x) (((uint16_t)(x) & DP83848_BMSR_10BASE_T_HALF_DUPLEX_MASK) >> DP83848_BMSR_10BASE_T_HALF_DUPLEX_SHIFT)

/*
 * MF_PREAMBLE_SUPPRESSION (RO)
 *
 * Preamble suppression Capable:
 * 1 = Device able to perform management transaction with preamble suppressed, 32-bits of
 * preamble needed only once after reset, invalid opcode or invalid turnaround.
 * 0 = Normal management operation.
 */
#define DP83848_BMSR_MF_PREAMBLE_SUPPRESSION_MASK (0x40U)
#define DP83848_BMSR_MF_PREAMBLE_SUPPRESSION_SHIFT (6U)
#define DP83848_BMSR_MF_PREAMBLE_SUPPRESSION_GET(x) (((uint16_t)(x) & DP83848_BMSR_MF_PREAMBLE_SUPPRESSION_MASK) >> DP83848_BMSR_MF_PREAMBLE_SUPPRESSION_SHIFT)

/*
 * AUTO_NEGOTIATION_COMPLETE (RO)
 *
 * Auto-Negotiation Complete:
 * 1 = Auto-Negotiation process complete.
 * 0 = Auto-Negotiation process not complete.
 */
#define DP83848_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK (0x20U)
#define DP83848_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT (5U)
#define DP83848_BMSR_AUTO_NEGOTIATION_COMPLETE_GET(x) (((uint16_t)(x) & DP83848_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK) >> DP83848_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT)

/*
 * REMOTE_FAULT (RO)
 *
 * Remote Fault:
 * 1 = Remote Fault condition detected (cleared on read or by reset). Fault criteria: Notification from
 * Link Partner of Remote Fault.
 * 0 = No remote fault condition detected.
 */
#define DP83848_BMSR_REMOTE_FAULT_MASK (0x10U)
#define DP83848_BMSR_REMOTE_FAULT_SHIFT (4U)
#define DP83848_BMSR_REMOTE_FAULT_GET(x) (((uint16_t)(x) & DP83848_BMSR_REMOTE_FAULT_MASK) >> DP83848_BMSR_REMOTE_FAULT_SHIFT)

/*
 * AUTO_NEGOTIATION_ABILITY (RO)
 *
 * Auto Negotiation Ability:
 * 1 = Device is able to perform Auto-Negotiation.
 * 0 = Device is not able to perform Auto-Negotiation.
 */
#define DP83848_BMSR_AUTO_NEGOTIATION_ABILITY_MASK (0x8U)
#define DP83848_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT (3U)
#define DP83848_BMSR_AUTO_NEGOTIATION_ABILITY_GET(x) (((uint16_t)(x) & DP83848_BMSR_AUTO_NEGOTIATION_ABILITY_MASK) >> DP83848_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT)

/*
 * LINK_STATUS (RO)
 *
 * Link Status:
 * 1 = Valid link established (for either 10 or 100 Mb/s operation).
 * 0 = Link not established.
 * The criteria for link validity is implementation specific. The occurrence of a link failure condition
 * will causes the Link Status bit to clear. Once cleared, this bit may only be set by establishing a
 * good link condition and a read through the management interface.
 */
#define DP83848_BMSR_LINK_STATUS_MASK (0x4U)
#define DP83848_BMSR_LINK_STATUS_SHIFT (2U)
#define DP83848_BMSR_LINK_STATUS_GET(x) (((uint16_t)(x) & DP83848_BMSR_LINK_STATUS_MASK) >> DP83848_BMSR_LINK_STATUS_SHIFT)

/*
 * JABBER_DETECT (RO)
 *
 * Jabber Detect: This bit only has meaning in 10 Mb/s mode.
 * 1 = Jabber condition detected.
 * 0 = No Jabber.
 * This bit is implemented with a latching function, such that the occurrence of a jabber condition
 * causes it to set until it is cleared by a read to this register by the management interface or by a
 * reset.
 */
#define DP83848_BMSR_JABBER_DETECT_MASK (0x2U)
#define DP83848_BMSR_JABBER_DETECT_SHIFT (1U)
#define DP83848_BMSR_JABBER_DETECT_GET(x) (((uint16_t)(x) & DP83848_BMSR_JABBER_DETECT_MASK) >> DP83848_BMSR_JABBER_DETECT_SHIFT)

/*
 * EXTENDED_CAPABILITY (RO)
 *
 * Extended Capability:
 * 1 = Extended register capabilities.
 * 0 = Basic register set capabilities only.
 */
#define DP83848_BMSR_EXTENDED_CAPABILITY_MASK (0x1U)
#define DP83848_BMSR_EXTENDED_CAPABILITY_SHIFT (0U)
#define DP83848_BMSR_EXTENDED_CAPABILITY_GET(x) (((uint16_t)(x) & DP83848_BMSR_EXTENDED_CAPABILITY_MASK) >> DP83848_BMSR_EXTENDED_CAPABILITY_SHIFT)

/* Bitfield definition for register: PHYIDR1 */
/*
 * OUI_MSB (RO)
 *
 * OUI Most Significant Bits:
 * Bits 3 to 18 of the OUI (080017h) are stored in bits 15 to 0 of this register. The most
 * significant two bits of the OUI are ignored (the IEEE standard refers to these as bits 1 and
 * 2).
 */
#define DP83848_PHYIDR1_OUI_MSB_MASK (0xFFFFU)
#define DP83848_PHYIDR1_OUI_MSB_SHIFT (0U)
#define DP83848_PHYIDR1_OUI_MSB_GET(x) (((uint16_t)(x) & DP83848_PHYIDR1_OUI_MSB_MASK) >> DP83848_PHYIDR1_OUI_MSB_SHIFT)

/* Bitfield definition for register: PHYIDR2 */
/*
 * OUI_LSB (RO)
 *
 * OUI Least Significant Bits:
 * Bits 19 to 24 of the OUI (080017h) are mapped from bits 15 to 10 of this register
 * respectively.
 */
#define DP83848_PHYIDR2_OUI_LSB_MASK (0xFC00U)
#define DP83848_PHYIDR2_OUI_LSB_SHIFT (10U)
#define DP83848_PHYIDR2_OUI_LSB_GET(x) (((uint16_t)(x) & DP83848_PHYIDR2_OUI_LSB_MASK) >> DP83848_PHYIDR2_OUI_LSB_SHIFT)

/*
 * VNDR_MDL (RO)
 *
 * Vendor Model Number:
 * The six bits of vendor model number are mapped from bits 9 to 4 (most significant bit to bit
 * 9).
 */
#define DP83848_PHYIDR2_VNDR_MDL_MASK (0x3F0U)
#define DP83848_PHYIDR2_VNDR_MDL_SHIFT (4U)
#define DP83848_PHYIDR2_VNDR_MDL_GET(x) (((uint16_t)(x) & DP83848_PHYIDR2_VNDR_MDL_MASK) >> DP83848_PHYIDR2_VNDR_MDL_SHIFT)

/*
 * MDL_REV (RO)
 *
 * Model Revision Number:
 * Four bits of the vendor model revision number are mapped from bits 3 to 0 (most significant
 * bit to bit 3). This field will be incremented for all major device changes.
 */
#define DP83848_PHYIDR2_MDL_REV_MASK (0xFU)
#define DP83848_PHYIDR2_MDL_REV_SHIFT (0U)
#define DP83848_PHYIDR2_MDL_REV_GET(x) (((uint16_t)(x) & DP83848_PHYIDR2_MDL_REV_MASK) >> DP83848_PHYIDR2_MDL_REV_SHIFT)

/* Bitfield definition for register: ANAR */
/*
 * NP (RW)
 *
 * Next Page Indication:
 * 0 = Next Page Transfer not desired.
 * 1 = Next Page Transfer desired.
 */
#define DP83848_ANAR_NP_MASK (0x8000U)
#define DP83848_ANAR_NP_SHIFT (15U)
#define DP83848_ANAR_NP_SET(x) (((uint16_t)(x) << DP83848_ANAR_NP_SHIFT) & DP83848_ANAR_NP_MASK)
#define DP83848_ANAR_NP_GET(x) (((uint16_t)(x) & DP83848_ANAR_NP_MASK) >> DP83848_ANAR_NP_SHIFT)

/*
 * RF (RW)
 *
 * Remote Fault:
 * 1 = Advertises that this device has detected a Remote Fault.
 * 0 = No Remote Fault detected.
 */
#define DP83848_ANAR_RF_MASK (0x2000U)
#define DP83848_ANAR_RF_SHIFT (13U)
#define DP83848_ANAR_RF_SET(x) (((uint16_t)(x) << DP83848_ANAR_RF_SHIFT) & DP83848_ANAR_RF_MASK)
#define DP83848_ANAR_RF_GET(x) (((uint16_t)(x) & DP83848_ANAR_RF_MASK) >> DP83848_ANAR_RF_SHIFT)

/*
 * ASM_DIR (RW)
 *
 * Asymmetric PAUSE Support for Full Duplex Links:
 * The ASM_DIR bit indicates that asymmetric PAUSE is supported.
 * Encoding and resolution of PAUSE bits is defined in IEEE 802.3 Annex 28B, Tables 28B-2 and
 * 28B-3, respectively. Pause resolution status is reported in PHYCR[13:12].
 * 1 = Advertise that the DTE (MAC) has implemented both the optional MAC control sublayer
 * and the pause function as specified in clause 31 and annex 31B of 802.3.
 * 0= No MAC based full duplex flow control.
 */
#define DP83848_ANAR_ASM_DIR_MASK (0x800U)
#define DP83848_ANAR_ASM_DIR_SHIFT (11U)
#define DP83848_ANAR_ASM_DIR_SET(x) (((uint16_t)(x) << DP83848_ANAR_ASM_DIR_SHIFT) & DP83848_ANAR_ASM_DIR_MASK)
#define DP83848_ANAR_ASM_DIR_GET(x) (((uint16_t)(x) & DP83848_ANAR_ASM_DIR_MASK) >> DP83848_ANAR_ASM_DIR_SHIFT)

/*
 * PAUSE (RW)
 *
 * PAUSE Support for Full Duplex Links:
 * The PAUSE bit indicates that the device is capable of providing the symmetric PAUSE
 * functions as defined in Annex 31B.
 * Encoding and resolution of PAUSE bits is defined in IEEE 802.3 Annex 28B, Tables 28B-2 and
 * 28B-3, respectively. Pause resolution status is reported in PHYCR[13:12].
 * 1 = Advertise that the DTE (MAC) has implemented both the optional MAC control sublayer
 * and the pause function as specified in clause 31 and annex 31B of 802.3.
 * 0= No MAC based full duplex flow control.
 */
#define DP83848_ANAR_PAUSE_MASK (0x400U)
#define DP83848_ANAR_PAUSE_SHIFT (10U)
#define DP83848_ANAR_PAUSE_SET(x) (((uint16_t)(x) << DP83848_ANAR_PAUSE_SHIFT) & DP83848_ANAR_PAUSE_MASK)
#define DP83848_ANAR_PAUSE_GET(x) (((uint16_t)(x) & DP83848_ANAR_PAUSE_MASK) >> DP83848_ANAR_PAUSE_SHIFT)

/*
 * T4 (RO)
 *
 * 100BASE-T4 Support:
 * 1= 100BASE-T4 is supported by the local device.
 * 0 = 100BASE-T4 not supported.
 */
#define DP83848_ANAR_T4_MASK (0x200U)
#define DP83848_ANAR_T4_SHIFT (9U)
#define DP83848_ANAR_T4_GET(x) (((uint16_t)(x) & DP83848_ANAR_T4_MASK) >> DP83848_ANAR_T4_SHIFT)

/*
 * TX_FD (RW)
 *
 * 100BASE-TX Full Duplex Support:
 * 1 = 100BASE-TX Full Duplex is supported by the local device.
 * 0 = 100BASE-TX Full Duplex not supported.
 */
#define DP83848_ANAR_TX_FD_MASK (0x100U)
#define DP83848_ANAR_TX_FD_SHIFT (8U)
#define DP83848_ANAR_TX_FD_SET(x) (((uint16_t)(x) << DP83848_ANAR_TX_FD_SHIFT) & DP83848_ANAR_TX_FD_MASK)
#define DP83848_ANAR_TX_FD_GET(x) (((uint16_t)(x) & DP83848_ANAR_TX_FD_MASK) >> DP83848_ANAR_TX_FD_SHIFT)

/*
 * TX (RW)
 *
 * 100BASE-TX Support:
 * 1 = 100BASE-TX is supported by the local device.
 * 0 = 100BASE-TX not supported.
 */
#define DP83848_ANAR_TX_MASK (0x80U)
#define DP83848_ANAR_TX_SHIFT (7U)
#define DP83848_ANAR_TX_SET(x) (((uint16_t)(x) << DP83848_ANAR_TX_SHIFT) & DP83848_ANAR_TX_MASK)
#define DP83848_ANAR_TX_GET(x) (((uint16_t)(x) & DP83848_ANAR_TX_MASK) >> DP83848_ANAR_TX_SHIFT)

/*
 * 10_FD (RW)
 *
 * 10BASE-T Full Duplex Support:
 * 1 = 10BASE-T Full Duplex is supported by the local device.
 * 0 = 10BASE-T Full Duplex not supported.
 */
#define DP83848_ANAR_10_FD_MASK (0x40U)
#define DP83848_ANAR_10_FD_SHIFT (6U)
#define DP83848_ANAR_10_FD_SET(x) (((uint16_t)(x) << DP83848_ANAR_10_FD_SHIFT) & DP83848_ANAR_10_FD_MASK)
#define DP83848_ANAR_10_FD_GET(x) (((uint16_t)(x) & DP83848_ANAR_10_FD_MASK) >> DP83848_ANAR_10_FD_SHIFT)

/*
 * 10 (RW)
 *
 * 10BASE-T Support:
 * 1 = 10BASE-T is supported by the local device.
 * 0 = 10BASE-T not supported.
 */
#define DP83848_ANAR_10_MASK (0x20U)
#define DP83848_ANAR_10_SHIFT (5U)
#define DP83848_ANAR_10_SET(x) (((uint16_t)(x) << DP83848_ANAR_10_SHIFT) & DP83848_ANAR_10_MASK)
#define DP83848_ANAR_10_GET(x) (((uint16_t)(x) & DP83848_ANAR_10_MASK) >> DP83848_ANAR_10_SHIFT)

/*
 * SELECTOR (RW)
 *
 * Protocol Selection Bits:
 * These bits contain the binary encoded protocol selector supported by this port. <00001>
 * indicates that this device supports IEEE 802.3.
 */
#define DP83848_ANAR_SELECTOR_MASK (0x1FU)
#define DP83848_ANAR_SELECTOR_SHIFT (0U)
#define DP83848_ANAR_SELECTOR_SET(x) (((uint16_t)(x) << DP83848_ANAR_SELECTOR_SHIFT) & DP83848_ANAR_SELECTOR_MASK)
#define DP83848_ANAR_SELECTOR_GET(x) (((uint16_t)(x) & DP83848_ANAR_SELECTOR_MASK) >> DP83848_ANAR_SELECTOR_SHIFT)

/* Bitfield definition for register: ANLPAR_BP */
/*
 * NP (RO)
 *
 * Next Page Indication:
 * 0 = Link Partner does not desire Next Page Transfer.
 * 1 = Link Partner desires Next Page Transfer.
 */
#define DP83848_ANLPAR_BP_NP_MASK (0x8000U)
#define DP83848_ANLPAR_BP_NP_SHIFT (15U)
#define DP83848_ANLPAR_BP_NP_GET(x) (((uint16_t)(x) & DP83848_ANLPAR_BP_NP_MASK) >> DP83848_ANLPAR_BP_NP_SHIFT)

/*
 * ACK (RO)
 *
 * Acknowledge:
 * 1 = Link Partner acknowledges reception of the ability data word.
 * 0 = Not acknowledged.
 * The Auto-Negotiation state machine will automatically control the this bit based on the incoming
 * FLP bursts.
 */
#define DP83848_ANLPAR_BP_ACK_MASK (0x4000U)
#define DP83848_ANLPAR_BP_ACK_SHIFT (14U)
#define DP83848_ANLPAR_BP_ACK_GET(x) (((uint16_t)(x) & DP83848_ANLPAR_BP_ACK_MASK) >> DP83848_ANLPAR_BP_ACK_SHIFT)

/*
 * RF (RO)
 *
 * Remote Fault:
 * 1 = Remote Fault indicated by Link Partner.
 * 0 = No Remote Fault indicated by Link Partner.
 */
#define DP83848_ANLPAR_BP_RF_MASK (0x2000U)
#define DP83848_ANLPAR_BP_RF_SHIFT (13U)
#define DP83848_ANLPAR_BP_RF_GET(x) (((uint16_t)(x) & DP83848_ANLPAR_BP_RF_MASK) >> DP83848_ANLPAR_BP_RF_SHIFT)

/*
 * ASM_DIR (RO)
 *
 * ASYMMETRIC PAUSE:
 * 1 = Asymmetric pause is supported by the Link Partner.
 * 0 = Asymmetric pause is not supported by the Link Partner.
 */
#define DP83848_ANLPAR_BP_ASM_DIR_MASK (0x800U)
#define DP83848_ANLPAR_BP_ASM_DIR_SHIFT (11U)
#define DP83848_ANLPAR_BP_ASM_DIR_GET(x) (((uint16_t)(x) & DP83848_ANLPAR_BP_ASM_DIR_MASK) >> DP83848_ANLPAR_BP_ASM_DIR_SHIFT)

/*
 * PAUSE (RO)
 *
 * PAUSE:
 * 1 = Pause function is supported by the Link Partner.
 * 0 = Pause function is not supported by the Link Partner.
 */
#define DP83848_ANLPAR_BP_PAUSE_MASK (0x400U)
#define DP83848_ANLPAR_BP_PAUSE_SHIFT (10U)
#define DP83848_ANLPAR_BP_PAUSE_GET(x) (((uint16_t)(x) & DP83848_ANLPAR_BP_PAUSE_MASK) >> DP83848_ANLPAR_BP_PAUSE_SHIFT)

/*
 * T4 (RO)
 *
 * 100BASE-T4 Support:
 * 1 = 100BASE-T4 is supported by the Link Partner.
 * 0 = 100BASE-T4 not supported by the Link Partner.
 */
#define DP83848_ANLPAR_BP_T4_MASK (0x200U)
#define DP83848_ANLPAR_BP_T4_SHIFT (9U)
#define DP83848_ANLPAR_BP_T4_GET(x) (((uint16_t)(x) & DP83848_ANLPAR_BP_T4_MASK) >> DP83848_ANLPAR_BP_T4_SHIFT)

/*
 * TX_FD (RO)
 *
 * 100BASE-TX Full Duplex Support:
 * 1 = 100BASE-TX Full Duplex is supported by the Link Partner.
 * 0 = 100BASE-TX Full Duplex not supported by the Link Partner.
 */
#define DP83848_ANLPAR_BP_TX_FD_MASK (0x100U)
#define DP83848_ANLPAR_BP_TX_FD_SHIFT (8U)
#define DP83848_ANLPAR_BP_TX_FD_GET(x) (((uint16_t)(x) & DP83848_ANLPAR_BP_TX_FD_MASK) >> DP83848_ANLPAR_BP_TX_FD_SHIFT)

/*
 * TX (RO)
 *
 * 100BASE-TX Support:
 * 1 = 100BASE-TX is supported by the Link Partner.
 * 0 = 100BASE-TX not supported by the Link Partner.
 */
#define DP83848_ANLPAR_BP_TX_MASK (0x80U)
#define DP83848_ANLPAR_BP_TX_SHIFT (7U)
#define DP83848_ANLPAR_BP_TX_GET(x) (((uint16_t)(x) & DP83848_ANLPAR_BP_TX_MASK) >> DP83848_ANLPAR_BP_TX_SHIFT)

/*
 * 10_FD (RO)
 *
 * 10BASE-T Full Duplex Support:
 * 1 = 10BASE-T Full Duplex is supported by the Link Partner.
 * 0 = 10BASE-T Full Duplex not supported by the Link Partner.
 */
#define DP83848_ANLPAR_BP_10_FD_MASK (0x40U)
#define DP83848_ANLPAR_BP_10_FD_SHIFT (6U)
#define DP83848_ANLPAR_BP_10_FD_GET(x) (((uint16_t)(x) & DP83848_ANLPAR_BP_10_FD_MASK) >> DP83848_ANLPAR_BP_10_FD_SHIFT)

/*
 * 10 (RO)
 *
 * 10BASE-T Support:
 * 1 = 10BASE-T is supported by the Link Partner.
 * 0 = 10BASE-T not supported by the Link Partner.
 */
#define DP83848_ANLPAR_BP_10_MASK (0x20U)
#define DP83848_ANLPAR_BP_10_SHIFT (5U)
#define DP83848_ANLPAR_BP_10_GET(x) (((uint16_t)(x) & DP83848_ANLPAR_BP_10_MASK) >> DP83848_ANLPAR_BP_10_SHIFT)

/*
 * SELECTOR (RO)
 *
 * Protocol Selection Bits:
 * Link Partner’s binary encoded protocol selector.
 */
#define DP83848_ANLPAR_BP_SELECTOR_MASK (0x1FU)
#define DP83848_ANLPAR_BP_SELECTOR_SHIFT (0U)
#define DP83848_ANLPAR_BP_SELECTOR_GET(x) (((uint16_t)(x) & DP83848_ANLPAR_BP_SELECTOR_MASK) >> DP83848_ANLPAR_BP_SELECTOR_SHIFT)

/* Bitfield definition for register: ANER */
/*
 * PDF (RO)
 *
 * Parallel Detection Fault:
 * 1 = A fault has been detected through the Parallel Detection function.
 * 0 = A fault has not been detected.
 */
#define DP83848_ANER_PDF_MASK (0x10U)
#define DP83848_ANER_PDF_SHIFT (4U)
#define DP83848_ANER_PDF_GET(x) (((uint16_t)(x) & DP83848_ANER_PDF_MASK) >> DP83848_ANER_PDF_SHIFT)

/*
 * LP_NP_ABLE (RO)
 *
 * Link Partner Next Page Able:
 * 1 = Link Partner does support Next Page.
 * 0 = Link Partner does not support Next Page.
 */
#define DP83848_ANER_LP_NP_ABLE_MASK (0x8U)
#define DP83848_ANER_LP_NP_ABLE_SHIFT (3U)
#define DP83848_ANER_LP_NP_ABLE_GET(x) (((uint16_t)(x) & DP83848_ANER_LP_NP_ABLE_MASK) >> DP83848_ANER_LP_NP_ABLE_SHIFT)

/*
 * NP_ABLE (RO)
 *
 * Next Page Able:
 * 1 = Indicates local device is able to send additional “Next Pages”.
 */
#define DP83848_ANER_NP_ABLE_MASK (0x4U)
#define DP83848_ANER_NP_ABLE_SHIFT (2U)
#define DP83848_ANER_NP_ABLE_GET(x) (((uint16_t)(x) & DP83848_ANER_NP_ABLE_MASK) >> DP83848_ANER_NP_ABLE_SHIFT)

/*
 * PAGE_RX (RO)
 *
 * Link Code Word Page Received:
 * 1 = Link Code Word has been received, cleared on a read.
 * 0 = Link Code Word has not been received.
 */
#define DP83848_ANER_PAGE_RX_MASK (0x2U)
#define DP83848_ANER_PAGE_RX_SHIFT (1U)
#define DP83848_ANER_PAGE_RX_GET(x) (((uint16_t)(x) & DP83848_ANER_PAGE_RX_MASK) >> DP83848_ANER_PAGE_RX_SHIFT)

/*
 * LP_AN_ABLE (RO)
 *
 * Link Partner Auto-Negotiation Able:
 * 1 = indicates that the Link Partner supports Auto-Negotiation.
 * 0 = indicates that the Link Partner does not support Auto-Negotiation.
 */
#define DP83848_ANER_LP_AN_ABLE_MASK (0x1U)
#define DP83848_ANER_LP_AN_ABLE_SHIFT (0U)
#define DP83848_ANER_LP_AN_ABLE_GET(x) (((uint16_t)(x) & DP83848_ANER_LP_AN_ABLE_MASK) >> DP83848_ANER_LP_AN_ABLE_SHIFT)

/* Bitfield definition for register: ANNPTR */
/*
 * NP (RW)
 *
 * Next Page Indication:
 * 0 = No other Next Page Transfer desired.
 * 1 = Another Next Page desired.
 */
#define DP83848_ANNPTR_NP_MASK (0x8000U)
#define DP83848_ANNPTR_NP_SHIFT (15U)
#define DP83848_ANNPTR_NP_SET(x) (((uint16_t)(x) << DP83848_ANNPTR_NP_SHIFT) & DP83848_ANNPTR_NP_MASK)
#define DP83848_ANNPTR_NP_GET(x) (((uint16_t)(x) & DP83848_ANNPTR_NP_MASK) >> DP83848_ANNPTR_NP_SHIFT)

/*
 * MP (RW)
 *
 * Message Page:
 * 1 = Message Page.
 * 0 = Unformatted Page.
 */
#define DP83848_ANNPTR_MP_MASK (0x2000U)
#define DP83848_ANNPTR_MP_SHIFT (13U)
#define DP83848_ANNPTR_MP_SET(x) (((uint16_t)(x) << DP83848_ANNPTR_MP_SHIFT) & DP83848_ANNPTR_MP_MASK)
#define DP83848_ANNPTR_MP_GET(x) (((uint16_t)(x) & DP83848_ANNPTR_MP_MASK) >> DP83848_ANNPTR_MP_SHIFT)

/*
 * ACK2 (RW)
 *
 * Acknowledge2:
 * 1 = Will comply with message.
 * 0 = Cannot comply with message.
 * Acknowledge2 is used by the next page function to indicate that Local Device has the ability
 * to comply with the message received.
 */
#define DP83848_ANNPTR_ACK2_MASK (0x1000U)
#define DP83848_ANNPTR_ACK2_SHIFT (12U)
#define DP83848_ANNPTR_ACK2_SET(x) (((uint16_t)(x) << DP83848_ANNPTR_ACK2_SHIFT) & DP83848_ANNPTR_ACK2_MASK)
#define DP83848_ANNPTR_ACK2_GET(x) (((uint16_t)(x) & DP83848_ANNPTR_ACK2_MASK) >> DP83848_ANNPTR_ACK2_SHIFT)

/*
 * TOG_TX (RW)
 *
 * Toggle:
 * 1 = Value of toggle bit in previously transmitted Link Code Word was 0.
 * 0 = Value of toggle bit in previously transmitted Link Code Word was 1.
 * Toggle is used by the Arbitration function within Auto-Negotiation to ensure synchronization
 * with the Link Partner during Next Page exchange. This bit shall always take the opposite
 * value of the Toggle bit in the previously exchanged Link Code Word.
 */
#define DP83848_ANNPTR_TOG_TX_MASK (0x800U)
#define DP83848_ANNPTR_TOG_TX_SHIFT (11U)
#define DP83848_ANNPTR_TOG_TX_SET(x) (((uint16_t)(x) << DP83848_ANNPTR_TOG_TX_SHIFT) & DP83848_ANNPTR_TOG_TX_MASK)
#define DP83848_ANNPTR_TOG_TX_GET(x) (((uint16_t)(x) & DP83848_ANNPTR_TOG_TX_MASK) >> DP83848_ANNPTR_TOG_TX_SHIFT)

/*
 * CODE (RW)
 *
 * This field represents the code field of the next page transmission. If the MP bit is set (bit 13
 * of this register), then the code shall be interpreted as a "Message Page”, as defined in annex
 * 28C of IEEE 802.3. Otherwise, the code shall be interpreted as an "Unformatted Page”, and
 * the interpretation is application specific.
 * The default value of the CODE represents a Null Page as defined in Annex 28C of IEEE
 * 802.3.
 */
#define DP83848_ANNPTR_CODE_MASK (0x400U)
#define DP83848_ANNPTR_CODE_SHIFT (10U)
#define DP83848_ANNPTR_CODE_SET(x) (((uint16_t)(x) << DP83848_ANNPTR_CODE_SHIFT) & DP83848_ANNPTR_CODE_MASK)
#define DP83848_ANNPTR_CODE_GET(x) (((uint16_t)(x) & DP83848_ANNPTR_CODE_MASK) >> DP83848_ANNPTR_CODE_SHIFT)

/* Bitfield definition for register: PHYSTS */
/*
 * MDI_X_MODE (RO)
 *
 * MDI-X mode as reported by the Auto-Negotiation logic:
 * This bit will be affected by the settings of the MDIX_EN and FORCE_MDIX bits in the
 * PHYCR register. When MDIX is enabled, but not forced, this bit will update dynamically as
 * the Auto-MDIX algorithm swaps between MDI and MDI-X configurations.
 * 1 = MDI pairs swapped (Receive on TPTD pair, Transmit on TPRD pair)
 * 0 = MDI pairs normal (Receive on TRD pair, Transmit on TPTD pair)
 */
#define DP83848_PHYSTS_MDI_X_MODE_MASK (0x4000U)
#define DP83848_PHYSTS_MDI_X_MODE_SHIFT (14U)
#define DP83848_PHYSTS_MDI_X_MODE_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_MDI_X_MODE_MASK) >> DP83848_PHYSTS_MDI_X_MODE_SHIFT)

/*
 * RECEIVE_ERRORLATCH (RO)
 *
 * Receive Error Latch:
 * This bit will be cleared upon a read of the RECR register.
 * 1 = Receive error event has occurred since last read of RXERCNT (address 0x15, Page 0).
 * 0 = No receive error event has occurred.
 */
#define DP83848_PHYSTS_RECEIVE_ERRORLATCH_MASK (0x2000U)
#define DP83848_PHYSTS_RECEIVE_ERRORLATCH_SHIFT (13U)
#define DP83848_PHYSTS_RECEIVE_ERRORLATCH_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_RECEIVE_ERRORLATCH_MASK) >> DP83848_PHYSTS_RECEIVE_ERRORLATCH_SHIFT)

/*
 * POLARITY_STATUS (RO)
 *
 * Polarity Status:
 * This bit is a duplication of bit 4 in the 10BTSCR register. This bit will be cleared upon a read
 * of the 10BTSCR register, but not upon a read of the PHYSTS register.
 * 1 = Inverted Polarity detected.
 * 0 = Correct Polarity detected.
 */
#define DP83848_PHYSTS_POLARITY_STATUS_MASK (0x1000U)
#define DP83848_PHYSTS_POLARITY_STATUS_SHIFT (12U)
#define DP83848_PHYSTS_POLARITY_STATUS_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_POLARITY_STATUS_MASK) >> DP83848_PHYSTS_POLARITY_STATUS_SHIFT)

/*
 * FALSE_CARRIER_SENSE_LATCH (RO)
 *
 * False Carrier Sense Latch:
 * This bit will be cleared upon a read of the FCSR register.
 * 1 = False Carrier event has occurred since last read of FCSCR (address 0x14).
 * 0 = No False Carrier event has occurred.
 */
#define DP83848_PHYSTS_FALSE_CARRIER_SENSE_LATCH_MASK (0x800U)
#define DP83848_PHYSTS_FALSE_CARRIER_SENSE_LATCH_SHIFT (11U)
#define DP83848_PHYSTS_FALSE_CARRIER_SENSE_LATCH_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_FALSE_CARRIER_SENSE_LATCH_MASK) >> DP83848_PHYSTS_FALSE_CARRIER_SENSE_LATCH_SHIFT)

/*
 * SIGNAL_DETECT (RO)
 *
 * 100Base-TX unconditional Signal Detect from PMD.
 */
#define DP83848_PHYSTS_SIGNAL_DETECT_MASK (0x400U)
#define DP83848_PHYSTS_SIGNAL_DETECT_SHIFT (10U)
#define DP83848_PHYSTS_SIGNAL_DETECT_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_SIGNAL_DETECT_MASK) >> DP83848_PHYSTS_SIGNAL_DETECT_SHIFT)

/*
 * DESCRAMBLER_LOCK (RO)
 *
 * 100Base-TX Descrambler Lock from PMD.
 */
#define DP83848_PHYSTS_DESCRAMBLER_LOCK_MASK (0x200U)
#define DP83848_PHYSTS_DESCRAMBLER_LOCK_SHIFT (9U)
#define DP83848_PHYSTS_DESCRAMBLER_LOCK_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_DESCRAMBLER_LOCK_MASK) >> DP83848_PHYSTS_DESCRAMBLER_LOCK_SHIFT)

/*
 * PAGE_RECEIVED (RO)
 *
 * Link Code Word Page Received:
 * This is a duplicate of the Page Received bit in the ANER register, but this bit will not be
 * cleared upon a read of the PHYSTS register.
 * 1 = A new Link Code Word Page has been received. Cleared on read of the ANER (address
 * 0x06, bit 1).
 * 0 = Link Code Word Page has not been received.
 */
#define DP83848_PHYSTS_PAGE_RECEIVED_MASK (0x100U)
#define DP83848_PHYSTS_PAGE_RECEIVED_SHIFT (8U)
#define DP83848_PHYSTS_PAGE_RECEIVED_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_PAGE_RECEIVED_MASK) >> DP83848_PHYSTS_PAGE_RECEIVED_SHIFT)

/*
 * REMOTE_FAULT (RO)
 *
 * Remote Fault:
 * 1 = Remote Fault condition detected (cleared on read of BMSR (address 01h) register or by
 * reset). Fault criteria: notification from Link Partner of Remote Fault through Auto-Negotiation.
 * 0 = No remote fault condition detected.
 */
#define DP83848_PHYSTS_REMOTE_FAULT_MASK (0x40U)
#define DP83848_PHYSTS_REMOTE_FAULT_SHIFT (6U)
#define DP83848_PHYSTS_REMOTE_FAULT_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_REMOTE_FAULT_MASK) >> DP83848_PHYSTS_REMOTE_FAULT_SHIFT)

/*
 * JABBER_DETECT (RO)
 *
 * Jabber Detect: This bit only has meaning in 10 Mb/s mode
 * This bit is a duplicate of the Jabber Detect bit in the BMSR register, except that it is not
 * cleared upon a read of the PHYSTS register.
 * 1 = Jabber condition detected.
 * 0 = No Jabber.
 */
#define DP83848_PHYSTS_JABBER_DETECT_MASK (0x20U)
#define DP83848_PHYSTS_JABBER_DETECT_SHIFT (5U)
#define DP83848_PHYSTS_JABBER_DETECT_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_JABBER_DETECT_MASK) >> DP83848_PHYSTS_JABBER_DETECT_SHIFT)

/*
 * AUTO_NEG_COMPLETE (RO)
 *
 * Auto-Negotiation Complete:
 * 1 = Auto-Negotiation complete.
 * 0 = Auto-Negotiation not complete.
 */
#define DP83848_PHYSTS_AUTO_NEG_COMPLETE_MASK (0x10U)
#define DP83848_PHYSTS_AUTO_NEG_COMPLETE_SHIFT (4U)
#define DP83848_PHYSTS_AUTO_NEG_COMPLETE_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_AUTO_NEG_COMPLETE_MASK) >> DP83848_PHYSTS_AUTO_NEG_COMPLETE_SHIFT)

/*
 * LOOPBACK_STATUS (RO)
 *
 * Loopback:
 * 1 = Loopback enabled.
 * 0 = Normal operation.
 */
#define DP83848_PHYSTS_LOOPBACK_STATUS_MASK (0x8U)
#define DP83848_PHYSTS_LOOPBACK_STATUS_SHIFT (3U)
#define DP83848_PHYSTS_LOOPBACK_STATUS_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_LOOPBACK_STATUS_MASK) >> DP83848_PHYSTS_LOOPBACK_STATUS_SHIFT)

/*
 * DUPLEX_STATUS (RO)
 *
 * Duplex:
 * This bit indicates duplex status and is determined from Auto-Negotiation or Forced Modes.
 * 1 = Full duplex mode.
 * 0 = Half duplex mode.
 * Note: This bit is only valid if Auto-Negotiation is enabled and complete and there is a valid
 * link or if Auto-Negotiation is disabled and there is a valid link.
 */
#define DP83848_PHYSTS_DUPLEX_STATUS_MASK (0x4U)
#define DP83848_PHYSTS_DUPLEX_STATUS_SHIFT (2U)
#define DP83848_PHYSTS_DUPLEX_STATUS_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_DUPLEX_STATUS_MASK) >> DP83848_PHYSTS_DUPLEX_STATUS_SHIFT)

/*
 * SPEED_STATUS (RO)
 *
 * Speed10:
 * This bit indicates the status of the speed and is determined from Auto-Negotiation or Forced
 * Modes.
 * 1 = 10 Mb/s mode.
 * 0 = 100 Mb/s mode.
 * Note: This bit is only valid if Auto-Negotiation is enabled and complete and there is a valid
 * link or if Auto-Negotiation is disabled and there is a valid link.
 */
#define DP83848_PHYSTS_SPEED_STATUS_MASK (0x2U)
#define DP83848_PHYSTS_SPEED_STATUS_SHIFT (1U)
#define DP83848_PHYSTS_SPEED_STATUS_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_SPEED_STATUS_MASK) >> DP83848_PHYSTS_SPEED_STATUS_SHIFT)

/*
 * LINK_STATUS (RO)
 *
 * Link Status:
 * This bit is a duplicate of the Link Status bit in the BMSR register, except that it will not be
 * cleared upon a read of the PHYSTS register.
 * 1 = Valid link established (for either 10 or 100 Mb/s operation)
 * 0 = Link not established.
 */
#define DP83848_PHYSTS_LINK_STATUS_MASK (0x1U)
#define DP83848_PHYSTS_LINK_STATUS_SHIFT (0U)
#define DP83848_PHYSTS_LINK_STATUS_GET(x) (((uint16_t)(x) & DP83848_PHYSTS_LINK_STATUS_MASK) >> DP83848_PHYSTS_LINK_STATUS_SHIFT)

/* Bitfield definition for register: FCSCR */
/*
 * FCSCNT_7_0 (RO)
 *
 * False Carrier Event Counter:
 * This 8-bit counter increments on every false carrier event. This counter sticks when it
 * reaches its max count (FFh).
 */
#define DP83848_FCSCR_FCSCNT_7_0_MASK (0xFFU)
#define DP83848_FCSCR_FCSCNT_7_0_SHIFT (0U)
#define DP83848_FCSCR_FCSCNT_7_0_GET(x) (((uint16_t)(x) & DP83848_FCSCR_FCSCNT_7_0_MASK) >> DP83848_FCSCR_FCSCNT_7_0_SHIFT)

/* Bitfield definition for register: RECR */
/*
 * RXERCNT_7_0 (RO)
 *
 * RX_ER Counter:
 * When a valid carrier is present and there is at least one occurrence of an invalid data
 * symbol, this 8-bit counter increments for each receive error detected. This event can
 * increment only once per valid carrier event. If a collision is present, the attribute will not
 * increment. The counter sticks when it reaches its max count.
 */
#define DP83848_RECR_RXERCNT_7_0_MASK (0xFFU)
#define DP83848_RECR_RXERCNT_7_0_SHIFT (0U)
#define DP83848_RECR_RXERCNT_7_0_GET(x) (((uint16_t)(x) & DP83848_RECR_RXERCNT_7_0_MASK) >> DP83848_RECR_RXERCNT_7_0_SHIFT)

/* Bitfield definition for register: PCSR */
/*
 * TQ_EN (RW)
 *
 * 100Mbs True Quiet Mode Enable:
 * 1 = Transmit True Quiet Mode.
 * 0 = Normal Transmit Mode.
 */
#define DP83848_PCSR_TQ_EN_MASK (0x400U)
#define DP83848_PCSR_TQ_EN_SHIFT (10U)
#define DP83848_PCSR_TQ_EN_SET(x) (((uint16_t)(x) << DP83848_PCSR_TQ_EN_SHIFT) & DP83848_PCSR_TQ_EN_MASK)
#define DP83848_PCSR_TQ_EN_GET(x) (((uint16_t)(x) & DP83848_PCSR_TQ_EN_MASK) >> DP83848_PCSR_TQ_EN_SHIFT)

/*
 * SD_FORCE_PMA (RW)
 *
 * Signal Detect Force PMA:
 * 1 = Forces Signal Detection in PMA.
 * 0 = Normal SD operation.
 */
#define DP83848_PCSR_SD_FORCE_PMA_MASK (0x200U)
#define DP83848_PCSR_SD_FORCE_PMA_SHIFT (9U)
#define DP83848_PCSR_SD_FORCE_PMA_SET(x) (((uint16_t)(x) << DP83848_PCSR_SD_FORCE_PMA_SHIFT) & DP83848_PCSR_SD_FORCE_PMA_MASK)
#define DP83848_PCSR_SD_FORCE_PMA_GET(x) (((uint16_t)(x) & DP83848_PCSR_SD_FORCE_PMA_MASK) >> DP83848_PCSR_SD_FORCE_PMA_SHIFT)

/*
 * SD_OPTION (RW)
 *
 * Signal Detect Option:
 * 1 = Enhanced signal detect algorithm.
 * 0 = Reduced signal detect algorithm.
 */
#define DP83848_PCSR_SD_OPTION_MASK (0x100U)
#define DP83848_PCSR_SD_OPTION_SHIFT (8U)
#define DP83848_PCSR_SD_OPTION_SET(x) (((uint16_t)(x) << DP83848_PCSR_SD_OPTION_SHIFT) & DP83848_PCSR_SD_OPTION_MASK)
#define DP83848_PCSR_SD_OPTION_GET(x) (((uint16_t)(x) & DP83848_PCSR_SD_OPTION_MASK) >> DP83848_PCSR_SD_OPTION_SHIFT)

/*
 * DESC_TIME (RW)
 *
 * Descrambler Timeout:
 * Increase the descrambler timeout. When set this should allow the device to receive larger
 * packets (>9k bytes) without loss of synchronization.
 * 1 = 2ms
 * 0 = 722us (per ANSI X3.263: 1995 (TP-PMD) 7.2.3.3e)
 */
#define DP83848_PCSR_DESC_TIME_MASK (0x80U)
#define DP83848_PCSR_DESC_TIME_SHIFT (7U)
#define DP83848_PCSR_DESC_TIME_SET(x) (((uint16_t)(x) << DP83848_PCSR_DESC_TIME_SHIFT) & DP83848_PCSR_DESC_TIME_MASK)
#define DP83848_PCSR_DESC_TIME_GET(x) (((uint16_t)(x) & DP83848_PCSR_DESC_TIME_MASK) >> DP83848_PCSR_DESC_TIME_SHIFT)

/*
 * FORCE_100_OK (RW)
 *
 * Force 100Mb/s Good Link:
 * 1 = Forces 100Mb/s Good Link.
 * 0 = Normal 100Mb/s operation.
 */
#define DP83848_PCSR_FORCE_100_OK_MASK (0x20U)
#define DP83848_PCSR_FORCE_100_OK_SHIFT (5U)
#define DP83848_PCSR_FORCE_100_OK_SET(x) (((uint16_t)(x) << DP83848_PCSR_FORCE_100_OK_SHIFT) & DP83848_PCSR_FORCE_100_OK_MASK)
#define DP83848_PCSR_FORCE_100_OK_GET(x) (((uint16_t)(x) & DP83848_PCSR_FORCE_100_OK_MASK) >> DP83848_PCSR_FORCE_100_OK_SHIFT)

/*
 * NRZI_BYPASS (RW)
 *
 * NRZI Bypass Enable:
 * 1 = NRZI Bypass Enabled.
 * 0 = NRZI Bypass Disabled.
 */
#define DP83848_PCSR_NRZI_BYPASS_MASK (0x4U)
#define DP83848_PCSR_NRZI_BYPASS_SHIFT (2U)
#define DP83848_PCSR_NRZI_BYPASS_SET(x) (((uint16_t)(x) << DP83848_PCSR_NRZI_BYPASS_SHIFT) & DP83848_PCSR_NRZI_BYPASS_MASK)
#define DP83848_PCSR_NRZI_BYPASS_GET(x) (((uint16_t)(x) & DP83848_PCSR_NRZI_BYPASS_MASK) >> DP83848_PCSR_NRZI_BYPASS_SHIFT)

/* Bitfield definition for register: RBR */
/*
 * RMII_MODE (RW)
 *
 * Reduced MII Mode:
 * 0 = Standard MII Mode
 * 1 = Reduced MII Mode
 */
#define DP83848_RBR_RMII_MODE_MASK (0x20U)
#define DP83848_RBR_RMII_MODE_SHIFT (5U)
#define DP83848_RBR_RMII_MODE_SET(x) (((uint16_t)(x) << DP83848_RBR_RMII_MODE_SHIFT) & DP83848_RBR_RMII_MODE_MASK)
#define DP83848_RBR_RMII_MODE_GET(x) (((uint16_t)(x) & DP83848_RBR_RMII_MODE_MASK) >> DP83848_RBR_RMII_MODE_SHIFT)

/*
 * RMII_REV1_0 (RW)
 *
 * Reduce MII Revision 1.0:
 * 0 = (RMII revision 1.2) CRS_DV will toggle at the end of a packet to indicate deassertion of
 * CRS.
 * 1 = (RMII revision 1.0) CRS_DV will remain asserted until final data is transferred. CRS_DV
 * will not toggle at the end of a packet.
 */
#define DP83848_RBR_RMII_REV1_0_MASK (0x10U)
#define DP83848_RBR_RMII_REV1_0_SHIFT (4U)
#define DP83848_RBR_RMII_REV1_0_SET(x) (((uint16_t)(x) << DP83848_RBR_RMII_REV1_0_SHIFT) & DP83848_RBR_RMII_REV1_0_MASK)
#define DP83848_RBR_RMII_REV1_0_GET(x) (((uint16_t)(x) & DP83848_RBR_RMII_REV1_0_MASK) >> DP83848_RBR_RMII_REV1_0_SHIFT)

/*
 * RX_OVF_STS (RO)
 *
 * RX FIFO Over Flow Status:
 * 0 = Normal
 * 1 = Overflow detected
 */
#define DP83848_RBR_RX_OVF_STS_MASK (0x8U)
#define DP83848_RBR_RX_OVF_STS_SHIFT (3U)
#define DP83848_RBR_RX_OVF_STS_GET(x) (((uint16_t)(x) & DP83848_RBR_RX_OVF_STS_MASK) >> DP83848_RBR_RX_OVF_STS_SHIFT)

/*
 * RX_UNF_STS (RO)
 *
 * RX FIFO Under Flow Status:
 * 0 = Normal
 * 1 = Underflow detected
 */
#define DP83848_RBR_RX_UNF_STS_MASK (0x4U)
#define DP83848_RBR_RX_UNF_STS_SHIFT (2U)
#define DP83848_RBR_RX_UNF_STS_GET(x) (((uint16_t)(x) & DP83848_RBR_RX_UNF_STS_MASK) >> DP83848_RBR_RX_UNF_STS_SHIFT)

/*
 * ELAST_BUF_1_0 (RW)
 *
 * Receive Elasticity Buffer. This field controls the Receive Elasticity Buffer which allows for
 * frequency variation tolerance between the 50-MHz RMII clock and the recovered data. The
 * following value indicate the tolerance in bits for a single packet. The minimum setting allows
 * for standard Ethernet frame sizes at ±50 ppm accuracy for both RMII and Receive clocks. For
 * greater frequency tolerance the packet lengths may be scaled (that is, for ±100 ppm, the
 * packet lengths need to be divided by 2).
 * 00 = 14 bit tolerance (up to 16800 byte packets)
 * 01 = 2 bit tolerance (up to 2400 byte packets)
 * 10 = 6 bit tolerance (up to 7200 byte packets)
 * 11 = 10 bit tolerance (up to 12000 byte packets)
 */
#define DP83848_RBR_ELAST_BUF_1_0_MASK (0x3U)
#define DP83848_RBR_ELAST_BUF_1_0_SHIFT (0U)
#define DP83848_RBR_ELAST_BUF_1_0_SET(x) (((uint16_t)(x) << DP83848_RBR_ELAST_BUF_1_0_SHIFT) & DP83848_RBR_ELAST_BUF_1_0_MASK)
#define DP83848_RBR_ELAST_BUF_1_0_GET(x) (((uint16_t)(x) & DP83848_RBR_ELAST_BUF_1_0_MASK) >> DP83848_RBR_ELAST_BUF_1_0_SHIFT)

/* Bitfield definition for register: LEDCR */
/*
 * DRV_SPDLED (RW)
 *
 * 1 = Drive value of SPDLED bit onto LED_SPEED output
 * 0 = Normal operation
 */
#define DP83848_LEDCR_DRV_SPDLED_MASK (0x20U)
#define DP83848_LEDCR_DRV_SPDLED_SHIFT (5U)
#define DP83848_LEDCR_DRV_SPDLED_SET(x) (((uint16_t)(x) << DP83848_LEDCR_DRV_SPDLED_SHIFT) & DP83848_LEDCR_DRV_SPDLED_MASK)
#define DP83848_LEDCR_DRV_SPDLED_GET(x) (((uint16_t)(x) & DP83848_LEDCR_DRV_SPDLED_MASK) >> DP83848_LEDCR_DRV_SPDLED_SHIFT)

/*
 * DRV_LNKLED (RW)
 *
 * 1 = Drive value of LNKLED bit onto LED_LINK output
 * 0 = Normal operation
 */
#define DP83848_LEDCR_DRV_LNKLED_MASK (0x10U)
#define DP83848_LEDCR_DRV_LNKLED_SHIFT (4U)
#define DP83848_LEDCR_DRV_LNKLED_SET(x) (((uint16_t)(x) << DP83848_LEDCR_DRV_LNKLED_SHIFT) & DP83848_LEDCR_DRV_LNKLED_MASK)
#define DP83848_LEDCR_DRV_LNKLED_GET(x) (((uint16_t)(x) & DP83848_LEDCR_DRV_LNKLED_MASK) >> DP83848_LEDCR_DRV_LNKLED_SHIFT)

/*
 * SPDLED (RW)
 *
 * Value to force on LED_SPEED output
 */
#define DP83848_LEDCR_SPDLED_MASK (0x4U)
#define DP83848_LEDCR_SPDLED_SHIFT (2U)
#define DP83848_LEDCR_SPDLED_SET(x) (((uint16_t)(x) << DP83848_LEDCR_SPDLED_SHIFT) & DP83848_LEDCR_SPDLED_MASK)
#define DP83848_LEDCR_SPDLED_GET(x) (((uint16_t)(x) & DP83848_LEDCR_SPDLED_MASK) >> DP83848_LEDCR_SPDLED_SHIFT)

/*
 * LNKLED (RW)
 *
 * Value to force on LED_LINK output
 */
#define DP83848_LEDCR_LNKLED_MASK (0x2U)
#define DP83848_LEDCR_LNKLED_SHIFT (1U)
#define DP83848_LEDCR_LNKLED_SET(x) (((uint16_t)(x) << DP83848_LEDCR_LNKLED_SHIFT) & DP83848_LEDCR_LNKLED_MASK)
#define DP83848_LEDCR_LNKLED_GET(x) (((uint16_t)(x) & DP83848_LEDCR_LNKLED_MASK) >> DP83848_LEDCR_LNKLED_SHIFT)

/* Bitfield definition for register: PHYCR */
/*
 * MDIX_EN (RW)
 *
 * Auto-MDIX Enable:
 * 1 = Enable Auto-neg Auto-MDIX capability.
 * 0 = Disable Auto-neg Auto-MDIX capability.
 * The Auto-MDIX algorithm requires that the Auto-Negotiation Enable bit in the BMCR register
 * to be set. If Auto-Negotiation is not enabled, Auto-MDIX should be disabled as well.
 */
#define DP83848_PHYCR_MDIX_EN_MASK (0x8000U)
#define DP83848_PHYCR_MDIX_EN_SHIFT (15U)
#define DP83848_PHYCR_MDIX_EN_SET(x) (((uint16_t)(x) << DP83848_PHYCR_MDIX_EN_SHIFT) & DP83848_PHYCR_MDIX_EN_MASK)
#define DP83848_PHYCR_MDIX_EN_GET(x) (((uint16_t)(x) & DP83848_PHYCR_MDIX_EN_MASK) >> DP83848_PHYCR_MDIX_EN_SHIFT)

/*
 * FORCE_MDIX (RW)
 *
 * Force MDIX:
 * 1 = Force MDI pairs to cross. (Receive on TPTD pair, Transmit on TPRD pair)
 * 0 = Normal operation.
 */
#define DP83848_PHYCR_FORCE_MDIX_MASK (0x4000U)
#define DP83848_PHYCR_FORCE_MDIX_SHIFT (14U)
#define DP83848_PHYCR_FORCE_MDIX_SET(x) (((uint16_t)(x) << DP83848_PHYCR_FORCE_MDIX_SHIFT) & DP83848_PHYCR_FORCE_MDIX_MASK)
#define DP83848_PHYCR_FORCE_MDIX_GET(x) (((uint16_t)(x) & DP83848_PHYCR_FORCE_MDIX_MASK) >> DP83848_PHYCR_FORCE_MDIX_SHIFT)

/*
 * PAUSE_RX (RO)
 *
 * Pause Receive Negotiated:
 * Indicates that pause receive should be enabled in the MAC. Based on ANAR[11:10] and
 * ANLPAR[11:10] settings.
 * This function shall be enabled according to IEEE 802.3 Annex 28B Table 28B-3, “Pause
 * Resolution”, only if the Auto-Negotiated Highest Common Denominator is a full duplex
 * technology.
 */
#define DP83848_PHYCR_PAUSE_RX_MASK (0x2000U)
#define DP83848_PHYCR_PAUSE_RX_SHIFT (13U)
#define DP83848_PHYCR_PAUSE_RX_GET(x) (((uint16_t)(x) & DP83848_PHYCR_PAUSE_RX_MASK) >> DP83848_PHYCR_PAUSE_RX_SHIFT)

/*
 * PAUSE_TX (RO)
 *
 * Pause Transmit Negotiated:
 * Indicates that pause transmit should be enabled in the MAC. Based on ANAR[11:10] and
 * ANLPAR[11:10] settings.
 * This function shall be enabled according to IEEE 802.3 Annex 28B Table 28B-3, “Pause
 * Resolution”, only if the Auto-Negotiated Highest Common Denominator is a full duplex
 * technology.
 */
#define DP83848_PHYCR_PAUSE_TX_MASK (0x1000U)
#define DP83848_PHYCR_PAUSE_TX_SHIFT (12U)
#define DP83848_PHYCR_PAUSE_TX_GET(x) (((uint16_t)(x) & DP83848_PHYCR_PAUSE_TX_MASK) >> DP83848_PHYCR_PAUSE_TX_SHIFT)

/*
 * BIST_FE (RW)
 *
 * BIST Force Error:
 * 1 = Force BIST Error.
 * 0 = Normal operation.
 * This bit forces a single error, and is self clearing.
 */
#define DP83848_PHYCR_BIST_FE_MASK (0x800U)
#define DP83848_PHYCR_BIST_FE_SHIFT (11U)
#define DP83848_PHYCR_BIST_FE_SET(x) (((uint16_t)(x) << DP83848_PHYCR_BIST_FE_SHIFT) & DP83848_PHYCR_BIST_FE_MASK)
#define DP83848_PHYCR_BIST_FE_GET(x) (((uint16_t)(x) & DP83848_PHYCR_BIST_FE_MASK) >> DP83848_PHYCR_BIST_FE_SHIFT)

/*
 * PSR_15 (RW)
 *
 * BIST Sequence select:
 * 1 = PSR15 selected.
 * 0 = PSR9 selected.
 */
#define DP83848_PHYCR_PSR_15_MASK (0x400U)
#define DP83848_PHYCR_PSR_15_SHIFT (10U)
#define DP83848_PHYCR_PSR_15_SET(x) (((uint16_t)(x) << DP83848_PHYCR_PSR_15_SHIFT) & DP83848_PHYCR_PSR_15_MASK)
#define DP83848_PHYCR_PSR_15_GET(x) (((uint16_t)(x) & DP83848_PHYCR_PSR_15_MASK) >> DP83848_PHYCR_PSR_15_SHIFT)

/*
 * BIST_STATUS (RO)
 *
 * BIST Test Status:
 * 1 = BIST pass.
 * 0 = BIST fail. Latched, cleared when BIST is stopped.
 * For a count number of BIST errors, see the BIST Error Count in the CDCTRL1 register.
 */
#define DP83848_PHYCR_BIST_STATUS_MASK (0x200U)
#define DP83848_PHYCR_BIST_STATUS_SHIFT (9U)
#define DP83848_PHYCR_BIST_STATUS_GET(x) (((uint16_t)(x) & DP83848_PHYCR_BIST_STATUS_MASK) >> DP83848_PHYCR_BIST_STATUS_SHIFT)

/*
 * BIST_START (RW)
 *
 * BIST Start:
 * 1 = BIST start.
 * 0 = BIST stop.
 */
#define DP83848_PHYCR_BIST_START_MASK (0x100U)
#define DP83848_PHYCR_BIST_START_SHIFT (8U)
#define DP83848_PHYCR_BIST_START_SET(x) (((uint16_t)(x) << DP83848_PHYCR_BIST_START_SHIFT) & DP83848_PHYCR_BIST_START_MASK)
#define DP83848_PHYCR_BIST_START_GET(x) (((uint16_t)(x) & DP83848_PHYCR_BIST_START_MASK) >> DP83848_PHYCR_BIST_START_SHIFT)

/*
 * BP_STRETCH (RW)
 *
 * Bypass LED Stretching:
 * This will bypass the LED stretching and the LEDs will reflect the internal value.
 * 1 = Bypass LED stretching.
 * 0 = Normal operation.
 */
#define DP83848_PHYCR_BP_STRETCH_MASK (0x80U)
#define DP83848_PHYCR_BP_STRETCH_SHIFT (7U)
#define DP83848_PHYCR_BP_STRETCH_SET(x) (((uint16_t)(x) << DP83848_PHYCR_BP_STRETCH_SHIFT) & DP83848_PHYCR_BP_STRETCH_MASK)
#define DP83848_PHYCR_BP_STRETCH_GET(x) (((uint16_t)(x) & DP83848_PHYCR_BP_STRETCH_MASK) >> DP83848_PHYCR_BP_STRETCH_SHIFT)

/*
 * LED_CNFG_0 (RW)
 *
 * LED Configuration
 * LED_ CNFG[0] Mode Description
 * 1 Mode 1
 * 0 Mode2
 * In Mode 1, LEDs are configured as follows: LED_LINK = ON for Good Link, OFF for No Link
 * LED_SPEED = ON in 100Mb/s, OFF in 10Mb/s
 * In Mode 2, LEDs are configured as follows: LED_LINK = ON for good Link, BLINK for Activity
 * LED_SPEED = ON in 100Mb/s, OFF in 10Mb/s
 */
#define DP83848_PHYCR_LED_CNFG_0_MASK (0x20U)
#define DP83848_PHYCR_LED_CNFG_0_SHIFT (5U)
#define DP83848_PHYCR_LED_CNFG_0_SET(x) (((uint16_t)(x) << DP83848_PHYCR_LED_CNFG_0_SHIFT) & DP83848_PHYCR_LED_CNFG_0_MASK)
#define DP83848_PHYCR_LED_CNFG_0_GET(x) (((uint16_t)(x) & DP83848_PHYCR_LED_CNFG_0_MASK) >> DP83848_PHYCR_LED_CNFG_0_SHIFT)

/*
 * PHYADDR_4_0 (RW)
 *
 * PHY Address: PHY address for port.
 */
#define DP83848_PHYCR_PHYADDR_4_0_MASK (0x1FU)
#define DP83848_PHYCR_PHYADDR_4_0_SHIFT (0U)
#define DP83848_PHYCR_PHYADDR_4_0_SET(x) (((uint16_t)(x) << DP83848_PHYCR_PHYADDR_4_0_SHIFT) & DP83848_PHYCR_PHYADDR_4_0_MASK)
#define DP83848_PHYCR_PHYADDR_4_0_GET(x) (((uint16_t)(x) & DP83848_PHYCR_PHYADDR_4_0_MASK) >> DP83848_PHYCR_PHYADDR_4_0_SHIFT)

/* Bitfield definition for register: 10BTSCR */
/*
 * SQUELCH (RW)
 *
 * Squelch Configuration:
 * Used to set the Squelch ‘ON’ threshold for the receiver.
 * Default Squelch ON is 330-mV peak.
 */
#define DP83848_10BTSCR_SQUELCH_MASK (0xE00U)
#define DP83848_10BTSCR_SQUELCH_SHIFT (9U)
#define DP83848_10BTSCR_SQUELCH_SET(x) (((uint16_t)(x) << DP83848_10BTSCR_SQUELCH_SHIFT) & DP83848_10BTSCR_SQUELCH_MASK)
#define DP83848_10BTSCR_SQUELCH_GET(x) (((uint16_t)(x) & DP83848_10BTSCR_SQUELCH_MASK) >> DP83848_10BTSCR_SQUELCH_SHIFT)

/*
 * LOOPBACK_10_DIS (RW)
 *
 * In half-duplex mode, default 10BASE-T operation loops Transmit data to the Receive data
 * in addition to transmitting the data on the physical medium. This is for consistency with
 * earlier 10BASE2 and 10BASE5 implementations which used a shared medium. Setting
 * this bit disables the loopback function.
 * This bit does not affect loopback due to setting BMCR[14].
 */
#define DP83848_10BTSCR_LOOPBACK_10_DIS_MASK (0x100U)
#define DP83848_10BTSCR_LOOPBACK_10_DIS_SHIFT (8U)
#define DP83848_10BTSCR_LOOPBACK_10_DIS_SET(x) (((uint16_t)(x) << DP83848_10BTSCR_LOOPBACK_10_DIS_SHIFT) & DP83848_10BTSCR_LOOPBACK_10_DIS_MASK)
#define DP83848_10BTSCR_LOOPBACK_10_DIS_GET(x) (((uint16_t)(x) & DP83848_10BTSCR_LOOPBACK_10_DIS_MASK) >> DP83848_10BTSCR_LOOPBACK_10_DIS_SHIFT)

/*
 * LP_DIS (RW)
 *
 * Normal Link Pulse Disable:
 * 1 = Transmission of NLPs is disabled.
 * 0 = Transmission of NLPs is enabled.
 */
#define DP83848_10BTSCR_LP_DIS_MASK (0x80U)
#define DP83848_10BTSCR_LP_DIS_SHIFT (7U)
#define DP83848_10BTSCR_LP_DIS_SET(x) (((uint16_t)(x) << DP83848_10BTSCR_LP_DIS_SHIFT) & DP83848_10BTSCR_LP_DIS_MASK)
#define DP83848_10BTSCR_LP_DIS_GET(x) (((uint16_t)(x) & DP83848_10BTSCR_LP_DIS_MASK) >> DP83848_10BTSCR_LP_DIS_SHIFT)

/*
 * FORCE_LINK_10 (RW)
 *
 * Force 10Mb Good Link:
 * 1 = Forced Good 10 Mb Link.
 * 0 = Normal Link Status.
 */
#define DP83848_10BTSCR_FORCE_LINK_10_MASK (0x40U)
#define DP83848_10BTSCR_FORCE_LINK_10_SHIFT (6U)
#define DP83848_10BTSCR_FORCE_LINK_10_SET(x) (((uint16_t)(x) << DP83848_10BTSCR_FORCE_LINK_10_SHIFT) & DP83848_10BTSCR_FORCE_LINK_10_MASK)
#define DP83848_10BTSCR_FORCE_LINK_10_GET(x) (((uint16_t)(x) & DP83848_10BTSCR_FORCE_LINK_10_MASK) >> DP83848_10BTSCR_FORCE_LINK_10_SHIFT)

/*
 * POLARITY (RO)
 *
 * 10Mb Polarity Status:
 * This bit is a duplication of bit 12 in the PHYSTS register. Both bits will be cleared upon a
 * read of 10BTSCR register, but not upon a read of the PHYSTS register.
 * 1 = Inverted Polarity detected.
 * 0 = Correct Polarity detected.
 */
#define DP83848_10BTSCR_POLARITY_MASK (0x10U)
#define DP83848_10BTSCR_POLARITY_SHIFT (4U)
#define DP83848_10BTSCR_POLARITY_GET(x) (((uint16_t)(x) & DP83848_10BTSCR_POLARITY_MASK) >> DP83848_10BTSCR_POLARITY_SHIFT)

/*
 * HEARTBEAT_DIS (RW)
 *
 * Heartbeat Disable: This bit only has influence in half-duplex 10Mb mode.
 * 1 = Heartbeat function disabled.
 * 0 = Heartbeat function enabled.
 * When the device is operating at 100 Mb or configured for full duplex operation, this
 * bit will be ignored - the heartbeat function is disabled.
 */
#define DP83848_10BTSCR_HEARTBEAT_DIS_MASK (0x2U)
#define DP83848_10BTSCR_HEARTBEAT_DIS_SHIFT (1U)
#define DP83848_10BTSCR_HEARTBEAT_DIS_SET(x) (((uint16_t)(x) << DP83848_10BTSCR_HEARTBEAT_DIS_SHIFT) & DP83848_10BTSCR_HEARTBEAT_DIS_MASK)
#define DP83848_10BTSCR_HEARTBEAT_DIS_GET(x) (((uint16_t)(x) & DP83848_10BTSCR_HEARTBEAT_DIS_MASK) >> DP83848_10BTSCR_HEARTBEAT_DIS_SHIFT)

/*
 * JABBER_DIS (RW)
 *
 * Jabber Disable:
 * Applicable only in 10BASE-T.
 * 1 = Jabber function disabled.
 * 0 = Jabber function enabled.
 */
#define DP83848_10BTSCR_JABBER_DIS_MASK (0x1U)
#define DP83848_10BTSCR_JABBER_DIS_SHIFT (0U)
#define DP83848_10BTSCR_JABBER_DIS_SET(x) (((uint16_t)(x) << DP83848_10BTSCR_JABBER_DIS_SHIFT) & DP83848_10BTSCR_JABBER_DIS_MASK)
#define DP83848_10BTSCR_JABBER_DIS_GET(x) (((uint16_t)(x) & DP83848_10BTSCR_JABBER_DIS_MASK) >> DP83848_10BTSCR_JABBER_DIS_SHIFT)

/* Bitfield definition for register: CDCTRL1 */
/*
 * BIST_ERROR_COUNT (RO)
 *
 * BIST ERROR Counter:
 * Counts number of errored data nibbles during Packet BIST. This value will reset when
 * Packet BIST is restarted. The counter sticks when it reaches its max count.
 */
#define DP83848_CDCTRL1_BIST_ERROR_COUNT_MASK (0xFF00U)
#define DP83848_CDCTRL1_BIST_ERROR_COUNT_SHIFT (8U)
#define DP83848_CDCTRL1_BIST_ERROR_COUNT_GET(x) (((uint16_t)(x) & DP83848_CDCTRL1_BIST_ERROR_COUNT_MASK) >> DP83848_CDCTRL1_BIST_ERROR_COUNT_SHIFT)

/*
 * BIST_CONT_MODE (RW)
 *
 * Packet BIST Continuous Mode:
 * Allows continuous pseudo random data transmission without any break in transmission. This
 * can be used for transmit VOD testing. This is used in conjunction with the BIST controls in
 * the PHYCR Register (0x19h). For 10 Mb operation, jabber function must be disabled, bit 0 of
 * the 10BTSCR (0x1Ah), JABBER_DIS = 1.
 */
#define DP83848_CDCTRL1_BIST_CONT_MODE_MASK (0x20U)
#define DP83848_CDCTRL1_BIST_CONT_MODE_SHIFT (5U)
#define DP83848_CDCTRL1_BIST_CONT_MODE_SET(x) (((uint16_t)(x) << DP83848_CDCTRL1_BIST_CONT_MODE_SHIFT) & DP83848_CDCTRL1_BIST_CONT_MODE_MASK)
#define DP83848_CDCTRL1_BIST_CONT_MODE_GET(x) (((uint16_t)(x) & DP83848_CDCTRL1_BIST_CONT_MODE_MASK) >> DP83848_CDCTRL1_BIST_CONT_MODE_SHIFT)

/*
 * CDPATTEN_10 (RW)
 *
 * CD Pattern Enable for 10Mb:
 * 1 = Enabled.
 * 0 = Disabled.
 */
#define DP83848_CDCTRL1_CDPATTEN_10_MASK (0x10U)
#define DP83848_CDCTRL1_CDPATTEN_10_SHIFT (4U)
#define DP83848_CDCTRL1_CDPATTEN_10_SET(x) (((uint16_t)(x) << DP83848_CDCTRL1_CDPATTEN_10_SHIFT) & DP83848_CDCTRL1_CDPATTEN_10_MASK)
#define DP83848_CDCTRL1_CDPATTEN_10_GET(x) (((uint16_t)(x) & DP83848_CDCTRL1_CDPATTEN_10_MASK) >> DP83848_CDCTRL1_CDPATTEN_10_SHIFT)

/*
 * 10MEG_PATT_GAP ( RW)
 *
 * Defines gap between data or NLP test sequences:
 * 1 = 15 µs.
 * 0 = 10 µs.
 */
#define DP83848_CDCTRL1_10MEG_PATT_GAP_MASK (0x4U)
#define DP83848_CDCTRL1_10MEG_PATT_GAP_SHIFT (2U)
#define DP83848_CDCTRL1_10MEG_PATT_GAP_SET(x) (((uint16_t)(x) << DP83848_CDCTRL1_10MEG_PATT_GAP_SHIFT) & DP83848_CDCTRL1_10MEG_PATT_GAP_MASK)
#define DP83848_CDCTRL1_10MEG_PATT_GAP_GET(x) (((uint16_t)(x) & DP83848_CDCTRL1_10MEG_PATT_GAP_MASK) >> DP83848_CDCTRL1_10MEG_PATT_GAP_SHIFT)

/*
 * CDPATTSEL_1_0 (RW)
 *
 * CD Pattern Select[1:0]:
 * If CDPATTEN_10 = 1:
 * 00 = Data, EOP0 sequence
 * 01 = Data, EOP1 sequence
 * 10 = NLPs
 * 11 = Constant Manchester 1 s (10-MHz sine wave) for harmonic distortion testing.
 */
#define DP83848_CDCTRL1_CDPATTSEL_1_0_MASK (0x3U)
#define DP83848_CDCTRL1_CDPATTSEL_1_0_SHIFT (0U)
#define DP83848_CDCTRL1_CDPATTSEL_1_0_SET(x) (((uint16_t)(x) << DP83848_CDCTRL1_CDPATTSEL_1_0_SHIFT) & DP83848_CDCTRL1_CDPATTSEL_1_0_MASK)
#define DP83848_CDCTRL1_CDPATTSEL_1_0_GET(x) (((uint16_t)(x) & DP83848_CDCTRL1_CDPATTSEL_1_0_MASK) >> DP83848_CDCTRL1_CDPATTSEL_1_0_SHIFT)

/* Bitfield definition for register: EDCR */
/*
 * ED_EN (RW)
 *
 * Energy Detect Enable:
 * Allow Energy Detect Mode.
 * When Energy Detect is enabled and Auto-Negotiation is disabled through the BMCR
 * register, Auto-MDIX should be disabled through the PHYCR register.
 */
#define DP83848_EDCR_ED_EN_MASK (0x8000U)
#define DP83848_EDCR_ED_EN_SHIFT (15U)
#define DP83848_EDCR_ED_EN_SET(x) (((uint16_t)(x) << DP83848_EDCR_ED_EN_SHIFT) & DP83848_EDCR_ED_EN_MASK)
#define DP83848_EDCR_ED_EN_GET(x) (((uint16_t)(x) & DP83848_EDCR_ED_EN_MASK) >> DP83848_EDCR_ED_EN_SHIFT)

/*
 * ED_AUTO_UP (RW)
 *
 * Energy Detect Automatic Power Up:
 * Automatically begin power-up sequence when Energy Detect Data Threshold value
 * (EDCR[3:0]) is reached. Alternatively, device could be powered up manually using the
 * ED_MAN bit (ECDR[12]).
 */
#define DP83848_EDCR_ED_AUTO_UP_MASK (0x4000U)
#define DP83848_EDCR_ED_AUTO_UP_SHIFT (14U)
#define DP83848_EDCR_ED_AUTO_UP_SET(x) (((uint16_t)(x) << DP83848_EDCR_ED_AUTO_UP_SHIFT) & DP83848_EDCR_ED_AUTO_UP_MASK)
#define DP83848_EDCR_ED_AUTO_UP_GET(x) (((uint16_t)(x) & DP83848_EDCR_ED_AUTO_UP_MASK) >> DP83848_EDCR_ED_AUTO_UP_SHIFT)

/*
 * ED_AUTO_DOWN (RW)
 *
 * Energy Detect Automatic Power Down:
 * Automatically begin power-down sequence when no energy is detected. Alternatively,
 * device could be powered down using the ED_MAN bit (EDCR[12]).
 */
#define DP83848_EDCR_ED_AUTO_DOWN_MASK (0x2000U)
#define DP83848_EDCR_ED_AUTO_DOWN_SHIFT (13U)
#define DP83848_EDCR_ED_AUTO_DOWN_SET(x) (((uint16_t)(x) << DP83848_EDCR_ED_AUTO_DOWN_SHIFT) & DP83848_EDCR_ED_AUTO_DOWN_MASK)
#define DP83848_EDCR_ED_AUTO_DOWN_GET(x) (((uint16_t)(x) & DP83848_EDCR_ED_AUTO_DOWN_MASK) >> DP83848_EDCR_ED_AUTO_DOWN_SHIFT)

/*
 * ED_MAN (RW)
 *
 * Energy Detect Manual Power Up/Down:
 * Begin power-up/down sequence when this bit is asserted. When set, the Energy Detect
 * algorithm will initiate a change of Energy Detect state regardless of threshold (error or
 * data) and timer values.
 */
#define DP83848_EDCR_ED_MAN_MASK (0x1000U)
#define DP83848_EDCR_ED_MAN_SHIFT (12U)
#define DP83848_EDCR_ED_MAN_SET(x) (((uint16_t)(x) << DP83848_EDCR_ED_MAN_SHIFT) & DP83848_EDCR_ED_MAN_MASK)
#define DP83848_EDCR_ED_MAN_GET(x) (((uint16_t)(x) & DP83848_EDCR_ED_MAN_MASK) >> DP83848_EDCR_ED_MAN_SHIFT)

/*
 * ED_BURST_DIS (RW)
 *
 * Energy Detect Bust Disable:
 * Disable bursting of energy detect data pulses. By default, Energy Detect (ED) transmits
 * a burst of 4 ED data pulses each time the CD is powered up. When bursting is
 * disabled, only a single ED data pulse will be send each time the CD is powered up.
 */
#define DP83848_EDCR_ED_BURST_DIS_MASK (0x800U)
#define DP83848_EDCR_ED_BURST_DIS_SHIFT (11U)
#define DP83848_EDCR_ED_BURST_DIS_SET(x) (((uint16_t)(x) << DP83848_EDCR_ED_BURST_DIS_SHIFT) & DP83848_EDCR_ED_BURST_DIS_MASK)
#define DP83848_EDCR_ED_BURST_DIS_GET(x) (((uint16_t)(x) & DP83848_EDCR_ED_BURST_DIS_MASK) >> DP83848_EDCR_ED_BURST_DIS_SHIFT)

/*
 * ED_PWR_STATE (RO)
 *
 * Energy Detect Power State:
 * Indicates current Energy Detect Power state. When set, Energy Detect is in the
 * powered up state. When cleared, Energy Detect is in the powered down state. This bit
 * is invalid when Energy Detect is not enabled.
 */
#define DP83848_EDCR_ED_PWR_STATE_MASK (0x400U)
#define DP83848_EDCR_ED_PWR_STATE_SHIFT (10U)
#define DP83848_EDCR_ED_PWR_STATE_GET(x) (((uint16_t)(x) & DP83848_EDCR_ED_PWR_STATE_MASK) >> DP83848_EDCR_ED_PWR_STATE_SHIFT)

/*
 * ED_ERR_MET (RO)
 *
 * Energy Detect Error Threshold Met:
 * No action is automatically taken upon receipt of error events. This bit is informational
 * only and would be cleared on a read.
 */
#define DP83848_EDCR_ED_ERR_MET_MASK (0x200U)
#define DP83848_EDCR_ED_ERR_MET_SHIFT (9U)
#define DP83848_EDCR_ED_ERR_MET_GET(x) (((uint16_t)(x) & DP83848_EDCR_ED_ERR_MET_MASK) >> DP83848_EDCR_ED_ERR_MET_SHIFT)

/*
 * ED_DATA_MET (RO)
 *
 * Energy Detect Data Threshold Met:
 * The number of data events that occurred met or surpassed the Energy Detect Data
 * Threshold. This bit is cleared on a read.
 */
#define DP83848_EDCR_ED_DATA_MET_MASK (0x100U)
#define DP83848_EDCR_ED_DATA_MET_SHIFT (8U)
#define DP83848_EDCR_ED_DATA_MET_GET(x) (((uint16_t)(x) & DP83848_EDCR_ED_DATA_MET_MASK) >> DP83848_EDCR_ED_DATA_MET_SHIFT)

/*
 * ED_ERR_COUNT (RW)
 *
 * Energy Detect Error Threshold:
 * Threshold to determine the number of energy detect error events that should cause the
 * device to take action. Intended to allow averaging of noise that may be on the line.
 * Counter will reset after approximately 2 seconds without any energy detect data
 * events.
 */
#define DP83848_EDCR_ED_ERR_COUNT_MASK (0xF0U)
#define DP83848_EDCR_ED_ERR_COUNT_SHIFT (4U)
#define DP83848_EDCR_ED_ERR_COUNT_SET(x) (((uint16_t)(x) << DP83848_EDCR_ED_ERR_COUNT_SHIFT) & DP83848_EDCR_ED_ERR_COUNT_MASK)
#define DP83848_EDCR_ED_ERR_COUNT_GET(x) (((uint16_t)(x) & DP83848_EDCR_ED_ERR_COUNT_MASK) >> DP83848_EDCR_ED_ERR_COUNT_SHIFT)

/*
 * ED_DATA_COUNT (RW)
 *
 * Energy Detect Data Threshold:
 * Threshold to determine the number of energy detect events that should cause the
 * device to take actions. Intended to allow averaging of noise that may be on the line.
 * Counter will reset after approximately 2 seconds without any energy detect data
 * events.
 */
#define DP83848_EDCR_ED_DATA_COUNT_MASK (0xFU)
#define DP83848_EDCR_ED_DATA_COUNT_SHIFT (0U)
#define DP83848_EDCR_ED_DATA_COUNT_SET(x) (((uint16_t)(x) << DP83848_EDCR_ED_DATA_COUNT_SHIFT) & DP83848_EDCR_ED_DATA_COUNT_MASK)
#define DP83848_EDCR_ED_DATA_COUNT_GET(x) (((uint16_t)(x) & DP83848_EDCR_ED_DATA_COUNT_MASK) >> DP83848_EDCR_ED_DATA_COUNT_SHIFT)




#endif /* HPM_DP83848_REGS_H */
