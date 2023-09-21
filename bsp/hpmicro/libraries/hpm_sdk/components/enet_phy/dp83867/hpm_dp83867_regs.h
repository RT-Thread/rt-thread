/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DP83867_REGS_H
#define HPM_DP83867_REGS_H

typedef enum {
    DP83867_BMCR                        = 0,   /* 0x0: Basic Mode Control Register */
    DP83867_BMSR                        = 1,   /* 0x1: Basic Mode Status Register */
    DP83867_PHYIDR1                     = 2,   /* 0x2: PHY Identifier Register #1 */
    DP83867_PHYIDR2                     = 3,   /* 0x3: PHY Identifier Register #2 */
    DP83867_ANAR                        = 4,   /* 0x4: MII Interrupt Control Register */
    DP83867_ANLPAR                      = 5,   /* 0x5: Auto-Negotiation Link Partner Ability Register */
    DP83867_ANER                        = 6,   /* 0x6: Auto-Negotiate Expansion Register */
    DP83867_ANNPTR                      = 7,   /* 0x7: Auto-Negotiation Next Page Transmit Register */
    DP83867_ANNPRR                      = 8,   /* 0x8: Auto-Negotiation Next Page Receive Register */
    DP83867_CFG1                        = 9,   /* 0x9: Configuration Register 1 */
    DP83867_STS1                        = 10,  /* 0xA: Status Register 1 */
    DP83867_REGCR                       = 13,  /* 0xD: Register Control Register */
    DP83867_ADDAR                       = 14,  /* 0xE: Address or Data Register */
    DP83867_1KSCR                       = 15,  /* 0xF: 1000BASE-T Status Register */
    DP83867_PHYCR                       = 16,  /* 0x10: PHY Control Register */
    DP83867_PHYSTS                      = 17,  /* 0x11: PHY Status Register */
    DP83867_MICR                        = 18,  /* 0x12: MII Interrupt Control Register */
    DP83867_ISR                         = 19,  /* 0x13: Interrupt Status Register */
    DP83867_CRG2                        = 20,  /* 0x14: Configuration Register 2 */
    DP83867_RECR                        = 21,  /* 0x15: Receiver Error Counter Register */
    DP83867_STS2                        = 23,  /* 0x17: Status Register 2 */
    DP83867_LEDCR1                      = 24,  /* 0x18: LED Configuration Register 1 */
    DP83867_LEDCR2                      = 25,  /* 0x19: LED Configuration Register 2 */
    DP83867_LEDCR3                      = 26,  /* 0x1A: LED Configuration Register 3 */
    DP83867_CFG3                        = 30,  /* 0x1E: Configuration Register 3 */
    DP83867_CTRL                        = 31,  /* 0x1F: Control Register */
    DP83867_RGMIIDCTL                   = 134, /* 0x86: RGMII Delay Control Register */
} DP83867_REG_Type;


/* Bitfield definition for register: BMCR */
/*
 * RESET (RW/SC)
 *
 * Reset:
 * 1 = Initiate software Reset / Reset in Process.
 * 0 = Normal operation.
 * This bit, which is self-clearing, returns a value of one until the reset
 * process is complete. The configuration is restrapped.
 */
#define DP83867_BMCR_RESET_MASK (0x8000U)
#define DP83867_BMCR_RESET_SHIFT (15U)
#define DP83867_BMCR_RESET_SET(x) (((uint16_t)(x) << DP83867_BMCR_RESET_SHIFT) & DP83867_BMCR_RESET_MASK)
#define DP83867_BMCR_RESET_GET(x) (((uint16_t)(x) & DP83867_BMCR_RESET_MASK) >> DP83867_BMCR_RESET_SHIFT)

/*
 * LOOPBACK (RW)
 *
 * Loopback:
 * 1 = Loopback enabled.
 * 0 = Normal operation.
 * The loopback function enables MAC transmit data to be routed to
 * the MAC receive data path.
 * Setting this bit may cause the descrambler to lose synchronization
 * and produce a 500-µs dead time before any valid data will appear at
 * the MII receive outputs.
 */
#define DP83867_BMCR_LOOPBACK_MASK (0x4000U)
#define DP83867_BMCR_LOOPBACK_SHIFT (14U)
#define DP83867_BMCR_LOOPBACK_SET(x) (((uint16_t)(x) << DP83867_BMCR_LOOPBACK_SHIFT) & DP83867_BMCR_LOOPBACK_MASK)
#define DP83867_BMCR_LOOPBACK_GET(x) (((uint16_t)(x) & DP83867_BMCR_LOOPBACK_MASK) >> DP83867_BMCR_LOOPBACK_SHIFT)

/*
 * SPEED0 (RW)
 *
 * Speed Select (Bits 6, 13):
 * When auto-negotiation is disabled writing to this bit allows the port
 * speed to be selected.
 * 11 = Reserved
 * 10 = 1000 Mbps
 * 1 = 100 Mbps
 * 0 = 10 Mbps
 */
#define DP83867_BMCR_SPEED0_MASK (0x2000U)
#define DP83867_BMCR_SPEED0_SHIFT (13U)
#define DP83867_BMCR_SPEED0_SET(x) (((uint16_t)(x) << DP83867_BMCR_SPEED0_SHIFT) & DP83867_BMCR_SPEED0_MASK)
#define DP83867_BMCR_SPEED0_GET(x) (((uint16_t)(x) & DP83867_BMCR_SPEED0_MASK) >> DP83867_BMCR_SPEED0_SHIFT)

/*
 * ANE (STRAP, RW)
 *
 * Auto-Negotiation Enable:
 * Strap controls initial value at reset.
 * 1 = Auto-Negotiation Enabled - bits 8 and 13 of this register are
 * ignored when this bit is set.
 * 0 = Auto-Negotiation Disabled - bits 8 and 13 determine the port
 * speed and duplex mode.
 */
#define DP83867_BMCR_ANE_MASK (0x1000U)
#define DP83867_BMCR_ANE_SHIFT (12U)
#define DP83867_BMCR_ANE_SET(x) (((uint16_t)(x) << DP83867_BMCR_ANE_SHIFT) & DP83867_BMCR_ANE_MASK)
#define DP83867_BMCR_ANE_GET(x) (((uint16_t)(x) & DP83867_BMCR_ANE_MASK) >> DP83867_BMCR_ANE_SHIFT)

/*
 * PWD (RW)
 *
 * Power Down:
 * 1 = Power down.
 * 0 = Normal operation.
 * Setting this bit powers down the PHY. Only the register block is
 * enabled during a power down condition. This bit is ORd with the
 * input from the PWRDOWN_INT pin. When the active low
 * PWRDOWN_INT pin is asserted, this bit will be set.
 */
#define DP83867_BMCR_PWD_MASK (0x800U)
#define DP83867_BMCR_PWD_SHIFT (11U)
#define DP83867_BMCR_PWD_SET(x) (((uint16_t)(x) << DP83867_BMCR_PWD_SHIFT) & DP83867_BMCR_PWD_MASK)
#define DP83867_BMCR_PWD_GET(x) (((uint16_t)(x) & DP83867_BMCR_PWD_MASK) >> DP83867_BMCR_PWD_SHIFT)

/*
 * ISOLATE (RW)
 *
 * Isolate:
 * 1 = Isolates the Port from the MII with the exception of the serial
 * management.
 * 0 = Normal operation.
 */
#define DP83867_BMCR_ISOLATE_MASK (0x400U)
#define DP83867_BMCR_ISOLATE_SHIFT (10U)
#define DP83867_BMCR_ISOLATE_SET(x) (((uint16_t)(x) << DP83867_BMCR_ISOLATE_SHIFT) & DP83867_BMCR_ISOLATE_MASK)
#define DP83867_BMCR_ISOLATE_GET(x) (((uint16_t)(x) & DP83867_BMCR_ISOLATE_MASK) >> DP83867_BMCR_ISOLATE_SHIFT)

/*
 * RESTART_AN (RW/SC)
 *
 * Restart Auto-Negotiation:
 * 1 = Restart Auto-Negotiation. Reinitiates the Auto-Negotiation
 * process. If Auto-Negotiation is disabled (bit 12 = 0), this bit is
 * ignored. This bit is self-clearing and will return a value of 1 until
 * Auto-Negotiation is initiated, whereupon it will self-clear. Operation of
 * the Auto-Negotiation process is not affected by the management
 * entity clearing this bit.
 * 0 = Normal operation.
 */
#define DP83867_BMCR_RESTART_AN_MASK (0x200U)
#define DP83867_BMCR_RESTART_AN_SHIFT (9U)
#define DP83867_BMCR_RESTART_AN_SET(x) (((uint16_t)(x) << DP83867_BMCR_RESTART_AN_SHIFT) & DP83867_BMCR_RESTART_AN_MASK)
#define DP83867_BMCR_RESTART_AN_GET(x) (((uint16_t)(x) & DP83867_BMCR_RESTART_AN_MASK) >> DP83867_BMCR_RESTART_AN_SHIFT)

/*
 * DUPLEX (STRAP, RW)
 *
 * Duplex Mode:
 * When auto-negotiation is disabled writing to this bit allows the port
 * Duplex capability to be selected.
 * 1 = Full Duplex operation.
 * 0 = Half Duplex operation.
 */
#define DP83867_BMCR_DUPLEX_MASK (0x100U)
#define DP83867_BMCR_DUPLEX_SHIFT (8U)
#define DP83867_BMCR_DUPLEX_SET(x) (((uint16_t)(x) << DP83867_BMCR_DUPLEX_SHIFT) & DP83867_BMCR_DUPLEX_MASK)
#define DP83867_BMCR_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_BMCR_DUPLEX_MASK) >> DP83867_BMCR_DUPLEX_SHIFT)

/*
 * COLLISION_TEST (RW)
 *
 * Collision Test:
 * 1 = Collision test enabled.
 * 0 = Normal operation.
 * When set, this bit will cause the COL signal to be asserted in
 * response to the assertion of TX_EN within 512-bit times. The COL
 * signal will be deasserted within 4-bit times in response to the
 * deassertion of TX_EN.
 */
#define DP83867_BMCR_COLLISION_TEST_MASK (0x80U)
#define DP83867_BMCR_COLLISION_TEST_SHIFT (7U)
#define DP83867_BMCR_COLLISION_TEST_SET(x) (((uint16_t)(x) << DP83867_BMCR_COLLISION_TEST_SHIFT) & DP83867_BMCR_COLLISION_TEST_MASK)
#define DP83867_BMCR_COLLISION_TEST_GET(x) (((uint16_t)(x) & DP83867_BMCR_COLLISION_TEST_MASK) >> DP83867_BMCR_COLLISION_TEST_SHIFT)

/*
 * SPEED1 (RW)
 *
 * Speed Select: See description for bit 13.
 */
#define DP83867_BMCR_SPEED1_MASK (0x40U)
#define DP83867_BMCR_SPEED1_SHIFT (6U)
#define DP83867_BMCR_SPEED1_SET(x) (((uint16_t)(x) << DP83867_BMCR_SPEED1_SHIFT) & DP83867_BMCR_SPEED1_MASK)
#define DP83867_BMCR_SPEED1_GET(x) (((uint16_t)(x) & DP83867_BMCR_SPEED1_MASK) >> DP83867_BMCR_SPEED1_SHIFT)

/* Bitfield definition for register: BMSR */
/*
 * 100BASE_T4 (RO/P)
 *
 * 100BASE-T4 Capable:
 * 0 = Device not able to perform 100BASE-T4 mode.
 */
#define DP83867_BMSR_100BASE_T4_MASK (0x8000U)
#define DP83867_BMSR_100BASE_T4_SHIFT (15U)
#define DP83867_BMSR_100BASE_T4_GET(x) (((uint16_t)(x) & DP83867_BMSR_100BASE_T4_MASK) >> DP83867_BMSR_100BASE_T4_SHIFT)

/*
 * 100BASE_TX_FULL_DUPLEX (RO/P)
 *
 * 100BASE-TX Full Duplex Capable:
 * 1 = Device able to perform 100BASE-TX in full duplex mode.
 */
#define DP83867_BMSR_100BASE_TX_FULL_DUPLEX_MASK (0x4000U)
#define DP83867_BMSR_100BASE_TX_FULL_DUPLEX_SHIFT (14U)
#define DP83867_BMSR_100BASE_TX_FULL_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_BMSR_100BASE_TX_FULL_DUPLEX_MASK) >> DP83867_BMSR_100BASE_TX_FULL_DUPLEX_SHIFT)

/*
 * 100BASE_TX_HALF_DUPLEX (RO/P)
 *
 * 100BASE-TX Half Duplex Capable:
 * 1 = Device able to perform 100BASE-TX in half duplex mode.
 */
#define DP83867_BMSR_100BASE_TX_HALF_DUPLEX_MASK (0x2000U)
#define DP83867_BMSR_100BASE_TX_HALF_DUPLEX_SHIFT (13U)
#define DP83867_BMSR_100BASE_TX_HALF_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_BMSR_100BASE_TX_HALF_DUPLEX_MASK) >> DP83867_BMSR_100BASE_TX_HALF_DUPLEX_SHIFT)

/*
 * 10BASE_TE_FULL_DUPLEX (RO/P)
 *
 * 10BASE-Te Full Duplex Capable:
 * 1 = Device able to perform 10BASE-Te in full duplex mode.
 */
#define DP83867_BMSR_10BASE_TE_FULL_DUPLEX_MASK (0x1000U)
#define DP83867_BMSR_10BASE_TE_FULL_DUPLEX_SHIFT (12U)
#define DP83867_BMSR_10BASE_TE_FULL_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_BMSR_10BASE_TE_FULL_DUPLEX_MASK) >> DP83867_BMSR_10BASE_TE_FULL_DUPLEX_SHIFT)

/*
 * 10BASE_TE_HALF_DUPLEX (RO/P)
 *
 * 10BASE-Te Half Duplex Capable:
 * 1 = Device able to perform 10BASE-Te in half duplex mode.
 */
#define DP83867_BMSR_10BASE_TE_HALF_DUPLEX_MASK (0x800U)
#define DP83867_BMSR_10BASE_TE_HALF_DUPLEX_SHIFT (11U)
#define DP83867_BMSR_10BASE_TE_HALF_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_BMSR_10BASE_TE_HALF_DUPLEX_MASK) >> DP83867_BMSR_10BASE_TE_HALF_DUPLEX_SHIFT)

/*
 * 100BASE_T2_FULL_DUPLEX (RO/P)
 *
 * 100BASE-T2 Full Duplex Capable:
 * 0 = Device not able to perform 100BASE-T2 in full duplex mode.
 */
#define DP83867_BMSR_100BASE_T2_FULL_DUPLEX_MASK (0x400U)
#define DP83867_BMSR_100BASE_T2_FULL_DUPLEX_SHIFT (10U)
#define DP83867_BMSR_100BASE_T2_FULL_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_BMSR_100BASE_T2_FULL_DUPLEX_MASK) >> DP83867_BMSR_100BASE_T2_FULL_DUPLEX_SHIFT)

/*
 * 100BASE_T2_HALF_DUPLEX (RO/P)
 *
 * 100BASE-T2 Half Duplex Capable:
 * 0 = Device not able to perform 100BASE-T2 in half duplex mode.
 */
#define DP83867_BMSR_100BASE_T2_HALF_DUPLEX_MASK (0x200U)
#define DP83867_BMSR_100BASE_T2_HALF_DUPLEX_SHIFT (9U)
#define DP83867_BMSR_100BASE_T2_HALF_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_BMSR_100BASE_T2_HALF_DUPLEX_MASK) >> DP83867_BMSR_100BASE_T2_HALF_DUPLEX_SHIFT)

/*
 * EXTENDED_STATUS (RO/P)
 *
 * 1000BASE-T Extended Status Register:
 * 1 = Device supports Extended Status Register 0x0F.
 */
#define DP83867_BMSR_EXTENDED_STATUS_MASK (0x100U)
#define DP83867_BMSR_EXTENDED_STATUS_SHIFT (8U)
#define DP83867_BMSR_EXTENDED_STATUS_GET(x) (((uint16_t)(x) & DP83867_BMSR_EXTENDED_STATUS_MASK) >> DP83867_BMSR_EXTENDED_STATUS_SHIFT)

/*
 * MF_PREAMBLE_SUPPRESSION (RO/P)
 *
 * Preamble Suppression Capable:
 * 1 = Device able to perform management transaction with preamble
 * suppressed, 32-bits of preamble needed only once after reset,
 * invalid opcode or invalid turnaround.
 * 0 = Normal management operation.
 */
#define DP83867_BMSR_MF_PREAMBLE_SUPPRESSION_MASK (0x40U)
#define DP83867_BMSR_MF_PREAMBLE_SUPPRESSION_SHIFT (6U)
#define DP83867_BMSR_MF_PREAMBLE_SUPPRESSION_GET(x) (((uint16_t)(x) & DP83867_BMSR_MF_PREAMBLE_SUPPRESSION_MASK) >> DP83867_BMSR_MF_PREAMBLE_SUPPRESSION_SHIFT)

/*
 * AUTO_NEGOTIATION_COMPLETE (RO)
 *
 * Auto-Negotiation Complete:
 * 1 = Auto-Negotiation process complete.
 * 0 = Auto-Negotiation process not complete.
 */
#define DP83867_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK (0x20U)
#define DP83867_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT (5U)
#define DP83867_BMSR_AUTO_NEGOTIATION_COMPLETE_GET(x) (((uint16_t)(x) & DP83867_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK) >> DP83867_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT)

/*
 * REMOTE_FAULT (RO/LH)
 *
 * Remote Fault:
 * 1 = Remote Fault condition detected (cleared on read or by reset).
 * Fault criteria: Far-End Fault Indication or notification from Link
 * Partner of Remote Fault.
 * 0 = No remote fault condition detected.
 */
#define DP83867_BMSR_REMOTE_FAULT_MASK (0x10U)
#define DP83867_BMSR_REMOTE_FAULT_SHIFT (4U)
#define DP83867_BMSR_REMOTE_FAULT_GET(x) (((uint16_t)(x) & DP83867_BMSR_REMOTE_FAULT_MASK) >> DP83867_BMSR_REMOTE_FAULT_SHIFT)

/*
 * AUTO_NEGOTIATION_ABILITY ( RO/P )
 *
 * Auto Negotiation Ability:
 * 1 = Device is able to perform Auto-Negotiation.
 * 0 = Device is not able to perform Auto-Negotiation.
 */
#define DP83867_BMSR_AUTO_NEGOTIATION_ABILITY_MASK (0x8U)
#define DP83867_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT (3U)
#define DP83867_BMSR_AUTO_NEGOTIATION_ABILITY_GET(x) (((uint16_t)(x) & DP83867_BMSR_AUTO_NEGOTIATION_ABILITY_MASK) >> DP83867_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT)

/*
 * LINK_STATUS ( RO/LL)
 *
 * Link Status:
 * 1 = Valid link established.
 * 0 = Link not established.
 * The criteria for link validity is implementation specific. The
 * occurrence of a link failure condition will causes the Link Status bit
 * to clear. Once cleared, this bit may only be set by establishing a
 * good link condition and a read through the management interface.
 */
#define DP83867_BMSR_LINK_STATUS_MASK (0x4U)
#define DP83867_BMSR_LINK_STATUS_SHIFT (2U)
#define DP83867_BMSR_LINK_STATUS_GET(x) (((uint16_t)(x) & DP83867_BMSR_LINK_STATUS_MASK) >> DP83867_BMSR_LINK_STATUS_SHIFT)

/*
 * JABBER_DETECT ( RO/LH)
 *
 * Jabber Detect: This bit only has meaning in 10-Mbps mode.
 * 1 = Jabber condition detected.
 * 0 = No Jabber.
 * This bit is implemented with a latching function, such that the
 * occurrence of a jabber condition causes it to set until it is cleared by
 * a read to this register by the management interface or by a reset.
 */
#define DP83867_BMSR_JABBER_DETECT_MASK (0x2U)
#define DP83867_BMSR_JABBER_DETECT_SHIFT (1U)
#define DP83867_BMSR_JABBER_DETECT_GET(x) (((uint16_t)(x) & DP83867_BMSR_JABBER_DETECT_MASK) >> DP83867_BMSR_JABBER_DETECT_SHIFT)

/*
 * EXTENDED_CAPABILITY (RO/P)
 *
 * Extended Capability:
 * 1 = Extended register capabilities.
 * 0 = Basic register set capabilities only.
 */
#define DP83867_BMSR_EXTENDED_CAPABILITY_MASK (0x1U)
#define DP83867_BMSR_EXTENDED_CAPABILITY_SHIFT (0U)
#define DP83867_BMSR_EXTENDED_CAPABILITY_GET(x) (((uint16_t)(x) & DP83867_BMSR_EXTENDED_CAPABILITY_MASK) >> DP83867_BMSR_EXTENDED_CAPABILITY_SHIFT)

/* Bitfield definition for register: PHYIDR1 */
/*
 * OUI_MSB (RO/P)
 *
 * OUI Most Significant Bits: Bits 3 to 18 of the OUI (080028h,) are
 * stored in bits 15 to 0 of this register. The most significant two bits of
 * the OUI are ignored (the IEEE standard refers to these as bits 1 and
 * 2).
 */
#define DP83867_PHYIDR1_OUI_MSB_MASK (0xFFFFU)
#define DP83867_PHYIDR1_OUI_MSB_SHIFT (0U)
#define DP83867_PHYIDR1_OUI_MSB_GET(x) (((uint16_t)(x) & DP83867_PHYIDR1_OUI_MSB_MASK) >> DP83867_PHYIDR1_OUI_MSB_SHIFT)

/* Bitfield definition for register: PHYIDR2 */
/*
 * OUI_LSB (RO/P)
 *
 * OUI Least Significant Bits:
 * Bits 19 to 24 of the OUI (080028h) are mapped from bits 15 to 10 of
 * this register respectively.
 */
#define DP83867_PHYIDR2_OUI_LSB_MASK (0xFC00U)
#define DP83867_PHYIDR2_OUI_LSB_SHIFT (10U)
#define DP83867_PHYIDR2_OUI_LSB_GET(x) (((uint16_t)(x) & DP83867_PHYIDR2_OUI_LSB_MASK) >> DP83867_PHYIDR2_OUI_LSB_SHIFT)

/*
 * VNDR_MDL (RO/P)
 *
 * Vendor Model Number:
 * The six bits of vendor model number are mapped from bits 9 to 4
 * (most significant bit to bit 9).
 */
#define DP83867_PHYIDR2_VNDR_MDL_MASK (0x3F0U)
#define DP83867_PHYIDR2_VNDR_MDL_SHIFT (4U)
#define DP83867_PHYIDR2_VNDR_MDL_GET(x) (((uint16_t)(x) & DP83867_PHYIDR2_VNDR_MDL_MASK) >> DP83867_PHYIDR2_VNDR_MDL_SHIFT)

/*
 * MDL_REV (RO/P)
 *
 * Model Revision Number:
 * Four bits of the vendor model revision number are mapped from bits
 * 3 to 0 (most significant bit to bit 3). This field will be incremented for
 * all major device changes.
 */
#define DP83867_PHYIDR2_MDL_REV_MASK (0xFU)
#define DP83867_PHYIDR2_MDL_REV_SHIFT (0U)
#define DP83867_PHYIDR2_MDL_REV_GET(x) (((uint16_t)(x) & DP83867_PHYIDR2_MDL_REV_MASK) >> DP83867_PHYIDR2_MDL_REV_SHIFT)

/* Bitfield definition for register: ANAR */
/*
 * NP (RW)
 *
 * Next Page Indication:
 * 0 = Next Page Transfer not desired.
 * 1 = Next Page Transfer desired.
 */
#define DP83867_ANAR_NP_MASK (0x8000U)
#define DP83867_ANAR_NP_SHIFT (15U)
#define DP83867_ANAR_NP_SET(x) (((uint16_t)(x) << DP83867_ANAR_NP_SHIFT) & DP83867_ANAR_NP_MASK)
#define DP83867_ANAR_NP_GET(x) (((uint16_t)(x) & DP83867_ANAR_NP_MASK) >> DP83867_ANAR_NP_SHIFT)

/*
 * RF (RW)
 *
 * Remote Fault:
 * 1 = Advertises that this device has detected a Remote Fault.
 * 0 = No Remote Fault detected.
 */
#define DP83867_ANAR_RF_MASK (0x2000U)
#define DP83867_ANAR_RF_SHIFT (13U)
#define DP83867_ANAR_RF_SET(x) (((uint16_t)(x) << DP83867_ANAR_RF_SHIFT) & DP83867_ANAR_RF_MASK)
#define DP83867_ANAR_RF_GET(x) (((uint16_t)(x) & DP83867_ANAR_RF_MASK) >> DP83867_ANAR_RF_SHIFT)

/*
 * ASM_DIR (RW)
 *
 * Asymmetric PAUSE Support for Full Duplex Links:
 * The ASM_DIR bit indicates that asymmetric PAUSE is supported.
 * Encoding and resolution of PAUSE bits is defined in IEEE 802.3
 * Annex 28B, Tables 28B-2 and 28B-3, respectively. Pause resolution
 * status is reported in PHYCR[13:12].
 * 1 = Advertise that the DTE (MAC) has implemented both the
 * optional MAC control sublayer and the pause function as specified
 * in clause 31 and annex 31B of 802.3u.
 * 0 = No MAC based full duplex flow control.
 */
#define DP83867_ANAR_ASM_DIR_MASK (0x800U)
#define DP83867_ANAR_ASM_DIR_SHIFT (11U)
#define DP83867_ANAR_ASM_DIR_SET(x) (((uint16_t)(x) << DP83867_ANAR_ASM_DIR_SHIFT) & DP83867_ANAR_ASM_DIR_MASK)
#define DP83867_ANAR_ASM_DIR_GET(x) (((uint16_t)(x) & DP83867_ANAR_ASM_DIR_MASK) >> DP83867_ANAR_ASM_DIR_SHIFT)

/*
 * PAUSE (RW)
 *
 * PAUSE Support for Full Duplex Links:
 * The PAUSE bit indicates that the device is capable of providing the
 * symmetric PAUSE functions as defined in Annex 31B.
 * Encoding and resolution of PAUSE bits is defined in IEEE 802.3
 * Annex 28B, Tables 28B-2 and 28B-3, respectively. Pause resolution
 * status is reported in PHYCR[13:12].
 * 1 = Advertise that the DTE (MAC) has implemented both the
 * optional MAC control sublayer and the pause function as specified
 * in clause 31 and annex 31B of 802.3u.
 * 0 = No MAC based full duplex flow control.
 */
#define DP83867_ANAR_PAUSE_MASK (0x400U)
#define DP83867_ANAR_PAUSE_SHIFT (10U)
#define DP83867_ANAR_PAUSE_SET(x) (((uint16_t)(x) << DP83867_ANAR_PAUSE_SHIFT) & DP83867_ANAR_PAUSE_MASK)
#define DP83867_ANAR_PAUSE_GET(x) (((uint16_t)(x) & DP83867_ANAR_PAUSE_MASK) >> DP83867_ANAR_PAUSE_SHIFT)

/*
 * T4 (RO/P)
 *
 * 100BASE-T4 Support:
 * 1 = 100BASE-T4 is supported by the local device.
 * 0 = 100BASE-T4 not supported.
 */
#define DP83867_ANAR_T4_MASK (0x200U)
#define DP83867_ANAR_T4_SHIFT (9U)
#define DP83867_ANAR_T4_GET(x) (((uint16_t)(x) & DP83867_ANAR_T4_MASK) >> DP83867_ANAR_T4_SHIFT)

/*
 * TX_FD (STRAP, RW)
 *
 * 100BASE-TX Full Duplex Support:
 * 1 = 100BASE-TX Full Duplex is supported by the local device.
 * 0 = 100BASE-TX Full Duplex not supported.
 */
#define DP83867_ANAR_TX_FD_MASK (0x100U)
#define DP83867_ANAR_TX_FD_SHIFT (8U)
#define DP83867_ANAR_TX_FD_SET(x) (((uint16_t)(x) << DP83867_ANAR_TX_FD_SHIFT) & DP83867_ANAR_TX_FD_MASK)
#define DP83867_ANAR_TX_FD_GET(x) (((uint16_t)(x) & DP83867_ANAR_TX_FD_MASK) >> DP83867_ANAR_TX_FD_SHIFT)

/*
 * TX (STRAP, RW)
 *
 * 100BASE-TX Support:
 * 1 = 100BASE-TX is supported by the local device.
 * 0 = 100BASE-TX not supported.
 */
#define DP83867_ANAR_TX_MASK (0x80U)
#define DP83867_ANAR_TX_SHIFT (7U)
#define DP83867_ANAR_TX_SET(x) (((uint16_t)(x) << DP83867_ANAR_TX_SHIFT) & DP83867_ANAR_TX_MASK)
#define DP83867_ANAR_TX_GET(x) (((uint16_t)(x) & DP83867_ANAR_TX_MASK) >> DP83867_ANAR_TX_SHIFT)

/*
 * 10_FD (STRAP, RW)
 *
 * 10BASE-Te Full Duplex Support:
 * 1 = 10BASE-Te Full Duplex is supported by the local device.
 * 0 = 10BASE-Te Full Duplex not supported.
 */
#define DP83867_ANAR_10_FD_MASK (0x40U)
#define DP83867_ANAR_10_FD_SHIFT (6U)
#define DP83867_ANAR_10_FD_SET(x) (((uint16_t)(x) << DP83867_ANAR_10_FD_SHIFT) & DP83867_ANAR_10_FD_MASK)
#define DP83867_ANAR_10_FD_GET(x) (((uint16_t)(x) & DP83867_ANAR_10_FD_MASK) >> DP83867_ANAR_10_FD_SHIFT)

/*
 * 10BASETE_EN (STRAP, RW)
 *
 * 10BASE-Te Support:
 * 1 = 10BASE-Te is supported by the local device.
 * 0 = 10BASE-Te not supported.
 */
#define DP83867_ANAR_10BASETE_EN_MASK (0x20U)
#define DP83867_ANAR_10BASETE_EN_SHIFT (5U)
#define DP83867_ANAR_10BASETE_EN_SET(x) (((uint16_t)(x) << DP83867_ANAR_10BASETE_EN_SHIFT) & DP83867_ANAR_10BASETE_EN_MASK)
#define DP83867_ANAR_10BASETE_EN_GET(x) (((uint16_t)(x) & DP83867_ANAR_10BASETE_EN_MASK) >> DP83867_ANAR_10BASETE_EN_SHIFT)

/*
 * SELECTOR (RW)
 *
 * Protocol Selection Bits:
 * These bits contain the binary encoded protocol selector supported
 * by this port. <00001> indicates that this device supports IEEE
 * 802.3u.
 */
#define DP83867_ANAR_SELECTOR_MASK (0x1FU)
#define DP83867_ANAR_SELECTOR_SHIFT (0U)
#define DP83867_ANAR_SELECTOR_SET(x) (((uint16_t)(x) << DP83867_ANAR_SELECTOR_SHIFT) & DP83867_ANAR_SELECTOR_MASK)
#define DP83867_ANAR_SELECTOR_GET(x) (((uint16_t)(x) & DP83867_ANAR_SELECTOR_MASK) >> DP83867_ANAR_SELECTOR_SHIFT)

/* Bitfield definition for register: ANLPAR */
/*
 * NP (RO)
 *
 * Next Page Indication:
 * 0 = Link Partner does not desire Next Page Transfer.
 * 1 = Link Partner desires Next Page Transfer.
 */
#define DP83867_ANLPAR_NP_MASK (0x8000U)
#define DP83867_ANLPAR_NP_SHIFT (15U)
#define DP83867_ANLPAR_NP_GET(x) (((uint16_t)(x) & DP83867_ANLPAR_NP_MASK) >> DP83867_ANLPAR_NP_SHIFT)

/*
 * ACK (RO)
 *
 * Acknowledge:
 * 1 = Link Partner acknowledges reception of the ability data word.
 * 0 = Not acknowledged.
 * The Auto-Negotiation state machine will automatically control this bit
 * based on the incoming FLP bursts.
 */
#define DP83867_ANLPAR_ACK_MASK (0x4000U)
#define DP83867_ANLPAR_ACK_SHIFT (14U)
#define DP83867_ANLPAR_ACK_GET(x) (((uint16_t)(x) & DP83867_ANLPAR_ACK_MASK) >> DP83867_ANLPAR_ACK_SHIFT)

/*
 * RF (RO)
 *
 * Remote Fault:
 * 1 = Remote Fault indicated by Link Partner.
 * 0 = No Remote Fault indicated by Link Partner.
 */
#define DP83867_ANLPAR_RF_MASK (0x2000U)
#define DP83867_ANLPAR_RF_SHIFT (13U)
#define DP83867_ANLPAR_RF_GET(x) (((uint16_t)(x) & DP83867_ANLPAR_RF_MASK) >> DP83867_ANLPAR_RF_SHIFT)

/*
 * ASM_DIR (RO)
 *
 * ASYMMETRIC PAUSE:
 * 1 = Asymmetric pause is supported by the Link Partner.
 * 0 = Asymmetric pause is not supported by the Link Partner.
 */
#define DP83867_ANLPAR_ASM_DIR_MASK (0x800U)
#define DP83867_ANLPAR_ASM_DIR_SHIFT (11U)
#define DP83867_ANLPAR_ASM_DIR_GET(x) (((uint16_t)(x) & DP83867_ANLPAR_ASM_DIR_MASK) >> DP83867_ANLPAR_ASM_DIR_SHIFT)

/*
 * PAUSE (RO)
 *
 * PAUSE:
 * 1 = Pause function is supported by the Link Partner.
 * 0 = Pause function is not supported by the Link Partner.
 */
#define DP83867_ANLPAR_PAUSE_MASK (0x400U)
#define DP83867_ANLPAR_PAUSE_SHIFT (10U)
#define DP83867_ANLPAR_PAUSE_GET(x) (((uint16_t)(x) & DP83867_ANLPAR_PAUSE_MASK) >> DP83867_ANLPAR_PAUSE_SHIFT)

/*
 * T4 (RO)
 *
 * 100BASE-T4 Support:
 * 1 = 100BASE-T4 is supported by the Link Partner.
 * 0 = 100BASE-T4 not supported by the Link Partner.
 */
#define DP83867_ANLPAR_T4_MASK (0x200U)
#define DP83867_ANLPAR_T4_SHIFT (9U)
#define DP83867_ANLPAR_T4_GET(x) (((uint16_t)(x) & DP83867_ANLPAR_T4_MASK) >> DP83867_ANLPAR_T4_SHIFT)

/*
 * TX_FD (RO)
 *
 * 100BASE-TX Full Duplex Support:
 * 1 = 100BASE-TX Full Duplex is supported by the Link Partner.
 * 0 = 100BASE-TX Full Duplex not supported by the Link Partner.
 */
#define DP83867_ANLPAR_TX_FD_MASK (0x100U)
#define DP83867_ANLPAR_TX_FD_SHIFT (8U)
#define DP83867_ANLPAR_TX_FD_GET(x) (((uint16_t)(x) & DP83867_ANLPAR_TX_FD_MASK) >> DP83867_ANLPAR_TX_FD_SHIFT)

/*
 * TX (RO)
 *
 * 100BASE-TX Support:
 * 1 = 100BASE-TX is supported by the Link Partner.
 * 0 = 100BASE-TX not supported by the Link Partner.
 */
#define DP83867_ANLPAR_TX_MASK (0x80U)
#define DP83867_ANLPAR_TX_SHIFT (7U)
#define DP83867_ANLPAR_TX_GET(x) (((uint16_t)(x) & DP83867_ANLPAR_TX_MASK) >> DP83867_ANLPAR_TX_SHIFT)

/*
 * 10_FD (RO)
 *
 * 10BASE-Te Full Duplex Support:
 * 1 = 10BASE-Te Full Duplex is supported by the Link Partner.
 * 0 = 10BASE-Te Full Duplex not supported by the Link Partner.
 */
#define DP83867_ANLPAR_10_FD_MASK (0x40U)
#define DP83867_ANLPAR_10_FD_SHIFT (6U)
#define DP83867_ANLPAR_10_FD_GET(x) (((uint16_t)(x) & DP83867_ANLPAR_10_FD_MASK) >> DP83867_ANLPAR_10_FD_SHIFT)

/*
 * 10 (RO)
 *
 * 10BASE-Te Support:
 * 1 = 10BASE-Te is supported by the Link Partner.
 * 0 = 10BASE-Te not supported by the Link Partner.
 */
#define DP83867_ANLPAR_10_MASK (0x20U)
#define DP83867_ANLPAR_10_SHIFT (5U)
#define DP83867_ANLPAR_10_GET(x) (((uint16_t)(x) & DP83867_ANLPAR_10_MASK) >> DP83867_ANLPAR_10_SHIFT)

/*
 * SELECTOR (RO)
 *
 * Protocol Selection Bits:
 * Link Partner's binary encoded protocol selector.
 */
#define DP83867_ANLPAR_SELECTOR_MASK (0x1FU)
#define DP83867_ANLPAR_SELECTOR_SHIFT (0U)
#define DP83867_ANLPAR_SELECTOR_GET(x) (((uint16_t)(x) & DP83867_ANLPAR_SELECTOR_MASK) >> DP83867_ANLPAR_SELECTOR_SHIFT)

/* Bitfield definition for register: ANER */
/*
 * RX_NEXT_PAGE_LOC_ABLE (RO)
 *
 * Receive Next Page Location Able:
 * 1 = Received Next Page storage location is specified by bit 6.5.
 * 0 = Received Next Page storage location is not specified by bit 6.5.
 */
#define DP83867_ANER_RX_NEXT_PAGE_LOC_ABLE_MASK (0x40U)
#define DP83867_ANER_RX_NEXT_PAGE_LOC_ABLE_SHIFT (6U)
#define DP83867_ANER_RX_NEXT_PAGE_LOC_ABLE_GET(x) (((uint16_t)(x) & DP83867_ANER_RX_NEXT_PAGE_LOC_ABLE_MASK) >> DP83867_ANER_RX_NEXT_PAGE_LOC_ABLE_SHIFT)

/*
 * RX_NEXT_PAGE_STOR_LOC (RO)
 *
 * Receive Next Page Storage Location:
 * 1 = Link Partner Next Pages are stored in register 8.
 * 0 = Link Partner Next Pages are stored in register 5.
 */
#define DP83867_ANER_RX_NEXT_PAGE_STOR_LOC_MASK (0x20U)
#define DP83867_ANER_RX_NEXT_PAGE_STOR_LOC_SHIFT (5U)
#define DP83867_ANER_RX_NEXT_PAGE_STOR_LOC_GET(x) (((uint16_t)(x) & DP83867_ANER_RX_NEXT_PAGE_STOR_LOC_MASK) >> DP83867_ANER_RX_NEXT_PAGE_STOR_LOC_SHIFT)

/*
 * PDF (RO)
 *
 * Parallel Detection Fault:
 * 1 = A fault has been detected via the Parallel Detection function.
 * 0 = A fault has not been detected.
 */
#define DP83867_ANER_PDF_MASK (0x10U)
#define DP83867_ANER_PDF_SHIFT (4U)
#define DP83867_ANER_PDF_GET(x) (((uint16_t)(x) & DP83867_ANER_PDF_MASK) >> DP83867_ANER_PDF_SHIFT)

/*
 * LP_NP_ABLE (RO)
 *
 * Link Partner Next Page Able:
 * 1 = Link Partner does support Next Page.
 * 0 = Link Partner does not support Next Page.
 */
#define DP83867_ANER_LP_NP_ABLE_MASK (0x8U)
#define DP83867_ANER_LP_NP_ABLE_SHIFT (3U)
#define DP83867_ANER_LP_NP_ABLE_GET(x) (((uint16_t)(x) & DP83867_ANER_LP_NP_ABLE_MASK) >> DP83867_ANER_LP_NP_ABLE_SHIFT)

/*
 * NP_ABLE (RO/P)
 *
 * Next Page Able:
 * 1 = Indicates local device is able to send additional Next Pages.
 */
#define DP83867_ANER_NP_ABLE_MASK (0x4U)
#define DP83867_ANER_NP_ABLE_SHIFT (2U)
#define DP83867_ANER_NP_ABLE_GET(x) (((uint16_t)(x) & DP83867_ANER_NP_ABLE_MASK) >> DP83867_ANER_NP_ABLE_SHIFT)

/*
 * PAGE_RX (RO/COR)
 *
 * Link Code Word Page Received:
 * 1 = Link Code Word has been received, cleared on a read.
 * 0 = Link Code Word has not been received.
 */
#define DP83867_ANER_PAGE_RX_MASK (0x2U)
#define DP83867_ANER_PAGE_RX_SHIFT (1U)
#define DP83867_ANER_PAGE_RX_GET(x) (((uint16_t)(x) & DP83867_ANER_PAGE_RX_MASK) >> DP83867_ANER_PAGE_RX_SHIFT)

/*
 * LP_AN_ABLE (RO)
 *
 * Link Partner Auto-Negotiation Able:
 * 1 = Indicates that the Link Partner supports Auto-Negotiation.
 * 0 = Indicates that the Link Partner does not support Auto-
 * Negotiation.
 */
#define DP83867_ANER_LP_AN_ABLE_MASK (0x1U)
#define DP83867_ANER_LP_AN_ABLE_SHIFT (0U)
#define DP83867_ANER_LP_AN_ABLE_GET(x) (((uint16_t)(x) & DP83867_ANER_LP_AN_ABLE_MASK) >> DP83867_ANER_LP_AN_ABLE_SHIFT)

/* Bitfield definition for register: ANNPTR */
/*
 * NP (RW)
 *
 * Next Page Indication:
 * 0 = No other Next Page Transfer desired.
 * 1 = Another Next Page desired.
 */
#define DP83867_ANNPTR_NP_MASK (0x8000U)
#define DP83867_ANNPTR_NP_SHIFT (15U)
#define DP83867_ANNPTR_NP_SET(x) (((uint16_t)(x) << DP83867_ANNPTR_NP_SHIFT) & DP83867_ANNPTR_NP_MASK)
#define DP83867_ANNPTR_NP_GET(x) (((uint16_t)(x) & DP83867_ANNPTR_NP_MASK) >> DP83867_ANNPTR_NP_SHIFT)

/*
 * ACK (RO)
 *
 * Acknowledge:
 * 1 = Acknowledge reception of link code word
 * 0 = Do not acknowledge of link code word.
 */
#define DP83867_ANNPTR_ACK_MASK (0x4000U)
#define DP83867_ANNPTR_ACK_SHIFT (14U)
#define DP83867_ANNPTR_ACK_GET(x) (((uint16_t)(x) & DP83867_ANNPTR_ACK_MASK) >> DP83867_ANNPTR_ACK_SHIFT)

/*
 * MP (RW)
 *
 * Message Page:
 * 1 = Current page is a Message Page.
 * 0 = Current page is an Unformatted Page.
 */
#define DP83867_ANNPTR_MP_MASK (0x2000U)
#define DP83867_ANNPTR_MP_SHIFT (13U)
#define DP83867_ANNPTR_MP_SET(x) (((uint16_t)(x) << DP83867_ANNPTR_MP_SHIFT) & DP83867_ANNPTR_MP_MASK)
#define DP83867_ANNPTR_MP_GET(x) (((uint16_t)(x) & DP83867_ANNPTR_MP_MASK) >> DP83867_ANNPTR_MP_SHIFT)

/*
 * ACK2 (RW)
 *
 * Acknowledge2:
 * 1 = Will comply with message.
 * 0 = Cannot comply with message.
 * Acknowledge2 is used by the next page function to indicate that
 * Local Device has the ability to comply with the message received.
 */
#define DP83867_ANNPTR_ACK2_MASK (0x1000U)
#define DP83867_ANNPTR_ACK2_SHIFT (12U)
#define DP83867_ANNPTR_ACK2_SET(x) (((uint16_t)(x) << DP83867_ANNPTR_ACK2_SHIFT) & DP83867_ANNPTR_ACK2_MASK)
#define DP83867_ANNPTR_ACK2_GET(x) (((uint16_t)(x) & DP83867_ANNPTR_ACK2_MASK) >> DP83867_ANNPTR_ACK2_SHIFT)

/*
 * TOG_TX (RO)
 *
 * Toggle:
 * 1 = Value of toggle bit in previously transmitted Link Code Word
 * was 0.
 * 0 = Value of toggle bit in previously transmitted Link Code Word
 * was 1.
 * Toggle is used by the Arbitration function within Auto-Negotiation to
 * ensure synchronization with the Link Partner during Next Page
 * exchange. This bit shall always take the opposite value of the
 * Toggle bit in the previously exchanged Link Code Word.
 */
#define DP83867_ANNPTR_TOG_TX_MASK (0x800U)
#define DP83867_ANNPTR_TOG_TX_SHIFT (11U)
#define DP83867_ANNPTR_TOG_TX_GET(x) (((uint16_t)(x) & DP83867_ANNPTR_TOG_TX_MASK) >> DP83867_ANNPTR_TOG_TX_SHIFT)

/*
 * CODE (RW)
 *
 * Code:
 * This field represents the code field of the next page transmission. If
 * the MP bit is set (bit 13 of this register), then the code shall be
 * interpreted as a "Message Page”, as defined in Annex 28C of IEEE
 * 802.3u. Otherwise, the code shall be interpreted as an "Unformatted
 * Page”, and the interpretation is application specific.
 * The default value of the CODE represents a Null Page as defined in
 * Annex 28C of IEEE 802.3u.
 */
#define DP83867_ANNPTR_CODE_MASK (0x7FFU)
#define DP83867_ANNPTR_CODE_SHIFT (0U)
#define DP83867_ANNPTR_CODE_SET(x) (((uint16_t)(x) << DP83867_ANNPTR_CODE_SHIFT) & DP83867_ANNPTR_CODE_MASK)
#define DP83867_ANNPTR_CODE_GET(x) (((uint16_t)(x) & DP83867_ANNPTR_CODE_MASK) >> DP83867_ANNPTR_CODE_SHIFT)

/* Bitfield definition for register: ANNPRR */
/*
 * NP (RW)
 *
 * Next Page Indication:
 * 0 = No other Next Page Transfer desired by the link partner.
 * 1 = Another Next Page desired by the link partner.
 */
#define DP83867_ANNPRR_NP_MASK (0x8000U)
#define DP83867_ANNPRR_NP_SHIFT (15U)
#define DP83867_ANNPRR_NP_SET(x) (((uint16_t)(x) << DP83867_ANNPRR_NP_SHIFT) & DP83867_ANNPRR_NP_MASK)
#define DP83867_ANNPRR_NP_GET(x) (((uint16_t)(x) & DP83867_ANNPRR_NP_MASK) >> DP83867_ANNPRR_NP_SHIFT)

/*
 * ACK (RO)
 *
 * Acknowledge:
 * 1 = Acknowledge reception of link code word by the link partner.
 * 0 = Link partner does not acknowledge reception of link code word.
 */
#define DP83867_ANNPRR_ACK_MASK (0x4000U)
#define DP83867_ANNPRR_ACK_SHIFT (14U)
#define DP83867_ANNPRR_ACK_GET(x) (((uint16_t)(x) & DP83867_ANNPRR_ACK_MASK) >> DP83867_ANNPRR_ACK_SHIFT)

/*
 * MP (RW)
 *
 * Message Page:
 * 1 = Received page is a Message Page.
 * 0 = Received page is an Unformatted Page.
 */
#define DP83867_ANNPRR_MP_MASK (0x2000U)
#define DP83867_ANNPRR_MP_SHIFT (13U)
#define DP83867_ANNPRR_MP_SET(x) (((uint16_t)(x) << DP83867_ANNPRR_MP_SHIFT) & DP83867_ANNPRR_MP_MASK)
#define DP83867_ANNPRR_MP_GET(x) (((uint16_t)(x) & DP83867_ANNPRR_MP_MASK) >> DP83867_ANNPRR_MP_SHIFT)

/*
 * ACK2 (RW)
 *
 * Acknowledge2:
 * 1 = Link partner sets the ACK2 bit.
 * 0 = Link partner coes not set the ACK2 bit.
 * Acknowledge2 is used by the next page function to indicate that link
 * partner has the ability to comply with the message received.
 */
#define DP83867_ANNPRR_ACK2_MASK (0x1000U)
#define DP83867_ANNPRR_ACK2_SHIFT (12U)
#define DP83867_ANNPRR_ACK2_SET(x) (((uint16_t)(x) << DP83867_ANNPRR_ACK2_SHIFT) & DP83867_ANNPRR_ACK2_MASK)
#define DP83867_ANNPRR_ACK2_GET(x) (((uint16_t)(x) & DP83867_ANNPRR_ACK2_MASK) >> DP83867_ANNPRR_ACK2_SHIFT)

/*
 * TOG_TX (RO)
 *
 * Toggle:
 * 1 = Value of toggle bit in previously transmitted Link Code Word
 * was 0.
 * 0 = Value of toggle bit in previously transmitted Link Code Word
 * was 1.
 * Toggle is used by the Arbitration function within Auto-Negotiation to
 * ensure synchronization with the Link Partner during Next Page
 * exchange. This bit shall always take the opposite value of the
 * Toggle bit in the previously exchanged Link Code Word.
 */
#define DP83867_ANNPRR_TOG_TX_MASK (0x800U)
#define DP83867_ANNPRR_TOG_TX_SHIFT (11U)
#define DP83867_ANNPRR_TOG_TX_GET(x) (((uint16_t)(x) & DP83867_ANNPRR_TOG_TX_MASK) >> DP83867_ANNPRR_TOG_TX_SHIFT)

/*
 * CODE (RW)
 *
 * Code:
 * This field represents the code field of the next page transmission. If
 * the MP bit is set (bit 13 of this register), then the code shall be
 * interpreted as a "Message Page”, as defined in Annex 28C of IEEE
 * 802.3u. Otherwise, the code shall be interpreted as an "Unformatted
 * Page”, and the interpretation is application specific.
 * The default value of the CODE represents a Null Page as defined in
 * Annex 28C of IEEE 802.3u.
 */
#define DP83867_ANNPRR_CODE_MASK (0x7FFU)
#define DP83867_ANNPRR_CODE_SHIFT (0U)
#define DP83867_ANNPRR_CODE_SET(x) (((uint16_t)(x) << DP83867_ANNPRR_CODE_SHIFT) & DP83867_ANNPRR_CODE_MASK)
#define DP83867_ANNPRR_CODE_GET(x) (((uint16_t)(x) & DP83867_ANNPRR_CODE_MASK) >> DP83867_ANNPRR_CODE_SHIFT)

/* Bitfield definition for register: CFG1 */
/*
 * TEST_MODE (RW)
 *
 * Test Mode Select:
 * 111 = Test Mode 7 - Repetitive {Pulse, 63 zeros}
 * 110 = Test Mode 6 - Repetitive 0001 sequence
 * 101 = Test Mode 5 - Scrambled MLT3 Idles
 * 100 = Test Mode 4 - Transmit Distortion Test
 * 011 = Test Mode 3 - Transmit Jitter Test (Slave Mode)
 * 010 = Test Mode 2 - Transmit Jitter Test (Master Mode)
 * 001 = Test Mode 1 - Transmit Waveform Test
 * 000 = Normal Mode
 */
#define DP83867_CFG1_TEST_MODE_MASK (0xE000U)
#define DP83867_CFG1_TEST_MODE_SHIFT (13U)
#define DP83867_CFG1_TEST_MODE_SET(x) (((uint16_t)(x) << DP83867_CFG1_TEST_MODE_SHIFT) & DP83867_CFG1_TEST_MODE_MASK)
#define DP83867_CFG1_TEST_MODE_GET(x) (((uint16_t)(x) & DP83867_CFG1_TEST_MODE_MASK) >> DP83867_CFG1_TEST_MODE_SHIFT)

/*
 * MASTER_SLAVE_MANUAL_CONFIGURATION (RW)
 *
 * Enable Manual Master / Slave Configuration:
 * 1 = Enable Manual Master/Slave Configuration control.
 * 0 = Disable Manual Master/Slave Configuration control.
 * Using the manual configuration feature may prevent the PHY from
 * establishing link in 1000Base-T mode if a conflict with the link
 * partner’s setting exists.
 */
#define DP83867_CFG1_MASTER_SLAVE_MANUAL_CONFIGURATION_MASK (0x1000U)
#define DP83867_CFG1_MASTER_SLAVE_MANUAL_CONFIGURATION_SHIFT (12U)
#define DP83867_CFG1_MASTER_SLAVE_MANUAL_CONFIGURATION_SET(x) (((uint16_t)(x) << DP83867_CFG1_MASTER_SLAVE_MANUAL_CONFIGURATION_SHIFT) & DP83867_CFG1_MASTER_SLAVE_MANUAL_CONFIGURATION_MASK)
#define DP83867_CFG1_MASTER_SLAVE_MANUAL_CONFIGURATION_GET(x) (((uint16_t)(x) & DP83867_CFG1_MASTER_SLAVE_MANUAL_CONFIGURATION_MASK) >> DP83867_CFG1_MASTER_SLAVE_MANUAL_CONFIGURATION_SHIFT)

/*
 * MASTER_SLAVE_CONFIGURATION_VALUE (RW)
 *
 * Manual Master / Slave Configuration Value:
 * 1 = Set PHY as MASTER when register 09h bit 12 = 1.
 * 0 = Set PHY as SLAVE when register 09h bit 12 = 1.
 * Using the manual configuration feature may prevent the PHY from
 * establishing link in 1000Base-T mode if a conflict with the link
 * partner’s setting exists.
 */
#define DP83867_CFG1_MASTER_SLAVE_CONFIGURATION_VALUE_MASK (0x800U)
#define DP83867_CFG1_MASTER_SLAVE_CONFIGURATION_VALUE_SHIFT (11U)
#define DP83867_CFG1_MASTER_SLAVE_CONFIGURATION_VALUE_SET(x) (((uint16_t)(x) << DP83867_CFG1_MASTER_SLAVE_CONFIGURATION_VALUE_SHIFT) & DP83867_CFG1_MASTER_SLAVE_CONFIGURATION_VALUE_MASK)
#define DP83867_CFG1_MASTER_SLAVE_CONFIGURATION_VALUE_GET(x) (((uint16_t)(x) & DP83867_CFG1_MASTER_SLAVE_CONFIGURATION_VALUE_MASK) >> DP83867_CFG1_MASTER_SLAVE_CONFIGURATION_VALUE_SHIFT)

/*
 * PORT_TYPE (RW)
 *
 * Advertise Device Type: Multi or single port:
 * 1 = Multi-port device.
 * 0 = Single-port device.
 */
#define DP83867_CFG1_PORT_TYPE_MASK (0x400U)
#define DP83867_CFG1_PORT_TYPE_SHIFT (10U)
#define DP83867_CFG1_PORT_TYPE_SET(x) (((uint16_t)(x) << DP83867_CFG1_PORT_TYPE_SHIFT) & DP83867_CFG1_PORT_TYPE_MASK)
#define DP83867_CFG1_PORT_TYPE_GET(x) (((uint16_t)(x) & DP83867_CFG1_PORT_TYPE_MASK) >> DP83867_CFG1_PORT_TYPE_SHIFT)

/*
 * 1000BASE_T_FULL_DUPLEX (RW)
 *
 * Advertise 1000BASE-T Full Duplex Capable:
 * 1 = Advertise 1000Base-T Full Duplex ability.
 * 0 = Do not advertise 1000Base-T Full Duplex ability.
 */
#define DP83867_CFG1_1000BASE_T_FULL_DUPLEX_MASK (0x200U)
#define DP83867_CFG1_1000BASE_T_FULL_DUPLEX_SHIFT (9U)
#define DP83867_CFG1_1000BASE_T_FULL_DUPLEX_SET(x) (((uint16_t)(x) << DP83867_CFG1_1000BASE_T_FULL_DUPLEX_SHIFT) & DP83867_CFG1_1000BASE_T_FULL_DUPLEX_MASK)
#define DP83867_CFG1_1000BASE_T_FULL_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_CFG1_1000BASE_T_FULL_DUPLEX_MASK) >> DP83867_CFG1_1000BASE_T_FULL_DUPLEX_SHIFT)

/*
 * 1000BASE_T_HALF_DUPLEX (RW)
 *
 * Advertise 1000BASE-T Half Duplex Capable:
 * 1 = Advertise 1000Base-T Half Duplex ability.
 * 0 = Do not advertise 1000Base-T Half Duplex ability.
 */
#define DP83867_CFG1_1000BASE_T_HALF_DUPLEX_MASK (0x100U)
#define DP83867_CFG1_1000BASE_T_HALF_DUPLEX_SHIFT (8U)
#define DP83867_CFG1_1000BASE_T_HALF_DUPLEX_SET(x) (((uint16_t)(x) << DP83867_CFG1_1000BASE_T_HALF_DUPLEX_SHIFT) & DP83867_CFG1_1000BASE_T_HALF_DUPLEX_MASK)
#define DP83867_CFG1_1000BASE_T_HALF_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_CFG1_1000BASE_T_HALF_DUPLEX_MASK) >> DP83867_CFG1_1000BASE_T_HALF_DUPLEX_SHIFT)

/*
 * TDR_AUTO_RUN (RW)
 *
 * Automatic TDR on Link Down:
 * 1 = Enable execution of TDR procedure after link down event.
 * 0 = Disable automatic execution of TDR.
 */
#define DP83867_CFG1_TDR_AUTO_RUN_MASK (0x80U)
#define DP83867_CFG1_TDR_AUTO_RUN_SHIFT (7U)
#define DP83867_CFG1_TDR_AUTO_RUN_SET(x) (((uint16_t)(x) << DP83867_CFG1_TDR_AUTO_RUN_SHIFT) & DP83867_CFG1_TDR_AUTO_RUN_MASK)
#define DP83867_CFG1_TDR_AUTO_RUN_GET(x) (((uint16_t)(x) & DP83867_CFG1_TDR_AUTO_RUN_MASK) >> DP83867_CFG1_TDR_AUTO_RUN_SHIFT)

/* Bitfield definition for register: STS1 */
/*
 * MASTER_SLAVE_CONFIGURATION_FAULT (RO, LH, COR)
 *
 * Master / Slave Manual Configuration Fault Detected:
 * 1 = Manual Master/Slave Configuration fault detected.
 * 0 = No Manual Master/Slave Configuration fault detected.
 */
#define DP83867_STS1_MASTER_SLAVE_CONFIGURATION_FAULT_MASK (0x8000U)
#define DP83867_STS1_MASTER_SLAVE_CONFIGURATION_FAULT_SHIFT (15U)
#define DP83867_STS1_MASTER_SLAVE_CONFIGURATION_FAULT_GET(x) (((uint16_t)(x) & DP83867_STS1_MASTER_SLAVE_CONFIGURATION_FAULT_MASK) >> DP83867_STS1_MASTER_SLAVE_CONFIGURATION_FAULT_SHIFT)

/*
 * MASTER_SLAVE_CONFIGURATION_RESOLUTION (RO)
 *
 * Master / Slave Configuration Results:
 * 1 = Configuration resolved to MASTER.
 * 0 = Configuration resolved to SLAVE.
 */
#define DP83867_STS1_MASTER_SLAVE_CONFIGURATION_RESOLUTION_MASK (0x4000U)
#define DP83867_STS1_MASTER_SLAVE_CONFIGURATION_RESOLUTION_SHIFT (14U)
#define DP83867_STS1_MASTER_SLAVE_CONFIGURATION_RESOLUTION_GET(x) (((uint16_t)(x) & DP83867_STS1_MASTER_SLAVE_CONFIGURATION_RESOLUTION_MASK) >> DP83867_STS1_MASTER_SLAVE_CONFIGURATION_RESOLUTION_SHIFT)

/*
 * LOCAL_RECEIVER_STATUS (RO)
 *
 * Local Receiver Status:
 * 1 = Local receiver is OK.
 * 0 = Local receiver is not OK.
 */
#define DP83867_STS1_LOCAL_RECEIVER_STATUS_MASK (0x2000U)
#define DP83867_STS1_LOCAL_RECEIVER_STATUS_SHIFT (13U)
#define DP83867_STS1_LOCAL_RECEIVER_STATUS_GET(x) (((uint16_t)(x) & DP83867_STS1_LOCAL_RECEIVER_STATUS_MASK) >> DP83867_STS1_LOCAL_RECEIVER_STATUS_SHIFT)

/*
 * REMOTE_RECEIVER_STATUS (RO)
 *
 * Remote Receiver Status:
 * 1 = Remote receiver is OK.
 * 0 = Remote receiver is not OK.
 */
#define DP83867_STS1_REMOTE_RECEIVER_STATUS_MASK (0x1000U)
#define DP83867_STS1_REMOTE_RECEIVER_STATUS_SHIFT (12U)
#define DP83867_STS1_REMOTE_RECEIVER_STATUS_GET(x) (((uint16_t)(x) & DP83867_STS1_REMOTE_RECEIVER_STATUS_MASK) >> DP83867_STS1_REMOTE_RECEIVER_STATUS_SHIFT)

/*
 * 1000BASE_T_FULL_DUPLEX (RO)
 *
 * Link Partner 1000BASE-T Full Duplex Capable:
 * 1 = Link Partner capable of 1000Base-T Full Duplex.
 * 0 = Link partner not capable of 1000Base-T Full Duplex.
 */
#define DP83867_STS1_1000BASE_T_FULL_DUPLEX_MASK (0x800U)
#define DP83867_STS1_1000BASE_T_FULL_DUPLEX_SHIFT (11U)
#define DP83867_STS1_1000BASE_T_FULL_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_STS1_1000BASE_T_FULL_DUPLEX_MASK) >> DP83867_STS1_1000BASE_T_FULL_DUPLEX_SHIFT)

/*
 * 1000BASE_T_HALF_DUPLEX (RO)
 *
 * Link Partner 1000BASE-T Half Duplex Capable:
 * 1 = Link Partner capable of 1000Base-T Half Duplex.
 * 0 = Link partner not capable of 1000Base-T Half Duplex.
 */
#define DP83867_STS1_1000BASE_T_HALF_DUPLEX_MASK (0x400U)
#define DP83867_STS1_1000BASE_T_HALF_DUPLEX_SHIFT (10U)
#define DP83867_STS1_1000BASE_T_HALF_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_STS1_1000BASE_T_HALF_DUPLEX_MASK) >> DP83867_STS1_1000BASE_T_HALF_DUPLEX_SHIFT)

/*
 * IDLE_ERROR_COUNTER (RO,COR)
 *
 * 1000BASE-T Idle Error Counter
 */
#define DP83867_STS1_IDLE_ERROR_COUNTER_MASK (0xFFU)
#define DP83867_STS1_IDLE_ERROR_COUNTER_SHIFT (0U)
#define DP83867_STS1_IDLE_ERROR_COUNTER_GET(x) (((uint16_t)(x) & DP83867_STS1_IDLE_ERROR_COUNTER_MASK) >> DP83867_STS1_IDLE_ERROR_COUNTER_SHIFT)

/* Bitfield definition for register: REGCR */
/*
 * FUNCTION (RW)
 *
 * 00 = Address
 * 01 = Data, no post increment
 * 10 = Data, post increment on read and write
 * 11 = Data, post increment on write only
 */
#define DP83867_REGCR_FUNCTION_MASK (0xC000U)
#define DP83867_REGCR_FUNCTION_SHIFT (14U)
#define DP83867_REGCR_FUNCTION_SET(x) (((uint16_t)(x) << DP83867_REGCR_FUNCTION_SHIFT) & DP83867_REGCR_FUNCTION_MASK)
#define DP83867_REGCR_FUNCTION_GET(x) (((uint16_t)(x) & DP83867_REGCR_FUNCTION_MASK) >> DP83867_REGCR_FUNCTION_SHIFT)

/*
 * DEVAD (RW)
 *
 * Device Address: In general, these bits [4:0] are the device address
 * DEVAD that directs any accesses of ADDAR register (0x000E) to
 * the appropriate MMD. Specifically, the DP83867 uses the vendor
 * specific DEVAD [4:0] = 11111 for accesses. All accesses through
 * registers REGCR and ADDAR should use this DEVAD.
 * Transactions with other DEVAD are ignored.
 */
#define DP83867_REGCR_DEVAD_MASK (0x1FU)
#define DP83867_REGCR_DEVAD_SHIFT (0U)
#define DP83867_REGCR_DEVAD_SET(x) (((uint16_t)(x) << DP83867_REGCR_DEVAD_SHIFT) & DP83867_REGCR_DEVAD_MASK)
#define DP83867_REGCR_DEVAD_GET(x) (((uint16_t)(x) & DP83867_REGCR_DEVAD_MASK) >> DP83867_REGCR_DEVAD_SHIFT)

/* Bitfield definition for register: ADDAR */
/*
 * ADDRESS_OR_DATA_REGISTER (RW)
 *
 * If REGCR register 15:14 = 00, holds the MMD DEVAD's address
 * register, otherwise holds the MMD DEVAD's data register
 */
#define DP83867_ADDAR_ADDRESS_OR_DATA_REGISTER_MASK (0xFFFFU)
#define DP83867_ADDAR_ADDRESS_OR_DATA_REGISTER_SHIFT (0U)
#define DP83867_ADDAR_ADDRESS_OR_DATA_REGISTER_SET(x) (((uint16_t)(x) << DP83867_ADDAR_ADDRESS_OR_DATA_REGISTER_SHIFT) & DP83867_ADDAR_ADDRESS_OR_DATA_REGISTER_MASK)
#define DP83867_ADDAR_ADDRESS_OR_DATA_REGISTER_GET(x) (((uint16_t)(x) & DP83867_ADDAR_ADDRESS_OR_DATA_REGISTER_MASK) >> DP83867_ADDAR_ADDRESS_OR_DATA_REGISTER_SHIFT)

/* Bitfield definition for register: 1KSCR */
/*
 * 1000BASE_X_FULL_DUPLEX (RO/P)
 *
 * 1000BASE-X Full Duplex Support:
 * 1 = 1000BASE-X Full Duplex is supported by the local device.
 * 0 = 1000BASE-X Full Duplex is not supported by the local device.
 */
#define DP83867_1KSCR_1000BASE_X_FULL_DUPLEX_MASK (0x8000U)
#define DP83867_1KSCR_1000BASE_X_FULL_DUPLEX_SHIFT (15U)
#define DP83867_1KSCR_1000BASE_X_FULL_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_1KSCR_1000BASE_X_FULL_DUPLEX_MASK) >> DP83867_1KSCR_1000BASE_X_FULL_DUPLEX_SHIFT)

/*
 * 1000BASE_X_HALF_DUPLEX (RO/P)
 *
 * 1000BASE-X Half Duplex Support:
 * 1 = 1000BASE-X Half Duplex is supported by the local device.
 * 0 = 1000BASE-X Half Duplex is not supported by the local device.
 */
#define DP83867_1KSCR_1000BASE_X_HALF_DUPLEX_MASK (0x4000U)
#define DP83867_1KSCR_1000BASE_X_HALF_DUPLEX_SHIFT (14U)
#define DP83867_1KSCR_1000BASE_X_HALF_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_1KSCR_1000BASE_X_HALF_DUPLEX_MASK) >> DP83867_1KSCR_1000BASE_X_HALF_DUPLEX_SHIFT)

/*
 * 1000BASE_T_FULL_DUPLEX (RO/P)
 *
 * 1000BASE-T Full Duplex Support:
 * 1 = 1000BASE-T Full Duplex is supported by the local device.
 * 0 = 1000BASE-T Full Duplex is not supported by the local device.
 */
#define DP83867_1KSCR_1000BASE_T_FULL_DUPLEX_MASK (0x2000U)
#define DP83867_1KSCR_1000BASE_T_FULL_DUPLEX_SHIFT (13U)
#define DP83867_1KSCR_1000BASE_T_FULL_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_1KSCR_1000BASE_T_FULL_DUPLEX_MASK) >> DP83867_1KSCR_1000BASE_T_FULL_DUPLEX_SHIFT)

/*
 * 1000BASE_T_HALF_DUPLEX (RO/P)
 *
 * 1000BASE-T Half Duplex Support:
 * 1 = 1000BASE-T Half Duplex is supported by the local device.
 * 0 = 1000BASE-T Half Duplex is not supported by the local device.
 */
#define DP83867_1KSCR_1000BASE_T_HALF_DUPLEX_MASK (0x1000U)
#define DP83867_1KSCR_1000BASE_T_HALF_DUPLEX_SHIFT (12U)
#define DP83867_1KSCR_1000BASE_T_HALF_DUPLEX_GET(x) (((uint16_t)(x) & DP83867_1KSCR_1000BASE_T_HALF_DUPLEX_MASK) >> DP83867_1KSCR_1000BASE_T_HALF_DUPLEX_SHIFT)

/* Bitfield definition for register: PHYCR */
/*
 * TX_FIFO_DEPTH (RW)
 *
 * TX FIFO Depth:
 * 11 = 8 bytes/nibbles (1000Mbps/Other Speeds)
 * 10 = 6 bytes/nibbles (1000Mbps/Other Speeds)
 * 01 = 4 bytes/nibbles (1000Mbps/Other Speeds)
 * 00 = 3 bytes/nibbles (1000Mbps/Other Speeds)
 * Note: FIFO is enabled only in the following modes:
 * 1000BaseT + GMII
 * 10BaseT/100BaseTX/1000BaseT + SGMII
 */
#define DP83867_PHYCR_TX_FIFO_DEPTH_MASK (0xC000U)
#define DP83867_PHYCR_TX_FIFO_DEPTH_SHIFT (14U)
#define DP83867_PHYCR_TX_FIFO_DEPTH_SET(x) (((uint16_t)(x) << DP83867_PHYCR_TX_FIFO_DEPTH_SHIFT) & DP83867_PHYCR_TX_FIFO_DEPTH_MASK)
#define DP83867_PHYCR_TX_FIFO_DEPTH_GET(x) (((uint16_t)(x) & DP83867_PHYCR_TX_FIFO_DEPTH_MASK) >> DP83867_PHYCR_TX_FIFO_DEPTH_SHIFT)

/*
 * RX_FIFO_DEPTH (RW)
 *
 * RX FIFO Depth:
 * 11 = 8 bytes/nibbles (1000 Mbps/Other Speeds)
 * 10 = 6 bytes/nibbles (1000 Mbps/Other Speeds)
 * 01 = 4 bytes/nibbles (1000 Mbps/Other Speeds)
 * 00 = 3 bytes/nibbles (1000 Mbps/Other Speeds)
 * Note: FIFO is enabled only in SGMII
 */
#define DP83867_PHYCR_RX_FIFO_DEPTH_MASK (0x3000U)
#define DP83867_PHYCR_RX_FIFO_DEPTH_SHIFT (12U)
#define DP83867_PHYCR_RX_FIFO_DEPTH_SET(x) (((uint16_t)(x) << DP83867_PHYCR_RX_FIFO_DEPTH_SHIFT) & DP83867_PHYCR_RX_FIFO_DEPTH_MASK)
#define DP83867_PHYCR_RX_FIFO_DEPTH_GET(x) (((uint16_t)(x) & DP83867_PHYCR_RX_FIFO_DEPTH_MASK) >> DP83867_PHYCR_RX_FIFO_DEPTH_SHIFT)

/*
 * SGMII_EN (RW)
 *
 * SGMII Enable:
 * 1 = Enable SGMII
 * 0 = Disable SGMII
 */
#define DP83867_PHYCR_SGMII_EN_MASK (0x800U)
#define DP83867_PHYCR_SGMII_EN_SHIFT (11U)
#define DP83867_PHYCR_SGMII_EN_SET(x) (((uint16_t)(x) << DP83867_PHYCR_SGMII_EN_SHIFT) & DP83867_PHYCR_SGMII_EN_MASK)
#define DP83867_PHYCR_SGMII_EN_GET(x) (((uint16_t)(x) & DP83867_PHYCR_SGMII_EN_MASK) >> DP83867_PHYCR_SGMII_EN_SHIFT)

/*
 * FORCE_LINK_GOOD (RW)
 *
 * Force Link Good:
 * 1 = Force link good according to the selected speed.
 * 0 = Normal operation
 */
#define DP83867_PHYCR_FORCE_LINK_GOOD_MASK (0x400U)
#define DP83867_PHYCR_FORCE_LINK_GOOD_SHIFT (10U)
#define DP83867_PHYCR_FORCE_LINK_GOOD_SET(x) (((uint16_t)(x) << DP83867_PHYCR_FORCE_LINK_GOOD_SHIFT) & DP83867_PHYCR_FORCE_LINK_GOOD_MASK)
#define DP83867_PHYCR_FORCE_LINK_GOOD_GET(x) (((uint16_t)(x) & DP83867_PHYCR_FORCE_LINK_GOOD_MASK) >> DP83867_PHYCR_FORCE_LINK_GOOD_SHIFT)

/*
 * POWER_SAVE_MODE (RW)
 *
 * Power-Saving Modes:
 * 11 = Passive Sleep mode: Power down all digital and analog
 * blocks.
 * 10 =Active Sleep mode: Power down all digital and analog blocks.
 * Automatic power-up is performed when link partner is detected. Link
 * pulses are transmitted approximately once per 1.4 Sec in this mode
 * to wake up any potential link partner.
 * 01 = IEEE mode: power down all digital and analog blocks.
 * Note: If DISABLE_CLK_125 (bit [4]of this register) is set to zero, the
 * PLL is also powered down.
 * 00 = Normal mode
 */
#define DP83867_PHYCR_POWER_SAVE_MODE_MASK (0x300U)
#define DP83867_PHYCR_POWER_SAVE_MODE_SHIFT (8U)
#define DP83867_PHYCR_POWER_SAVE_MODE_SET(x) (((uint16_t)(x) << DP83867_PHYCR_POWER_SAVE_MODE_SHIFT) & DP83867_PHYCR_POWER_SAVE_MODE_MASK)
#define DP83867_PHYCR_POWER_SAVE_MODE_GET(x) (((uint16_t)(x) & DP83867_PHYCR_POWER_SAVE_MODE_MASK) >> DP83867_PHYCR_POWER_SAVE_MODE_SHIFT)

/*
 * DEEP_POWER_DOWN_EN (RW)
 *
 * Deep power-down mode enable
 * 1 = When power down is initiated through assertion of the external
 * power-down pin or through the POWER_DOWN bit in the BMCR,
 * the device enters a deep power-down mode.
 * 0 = Normal operation.
 */
#define DP83867_PHYCR_DEEP_POWER_DOWN_EN_MASK (0x80U)
#define DP83867_PHYCR_DEEP_POWER_DOWN_EN_SHIFT (7U)
#define DP83867_PHYCR_DEEP_POWER_DOWN_EN_SET(x) (((uint16_t)(x) << DP83867_PHYCR_DEEP_POWER_DOWN_EN_SHIFT) & DP83867_PHYCR_DEEP_POWER_DOWN_EN_MASK)
#define DP83867_PHYCR_DEEP_POWER_DOWN_EN_GET(x) (((uint16_t)(x) & DP83867_PHYCR_DEEP_POWER_DOWN_EN_MASK) >> DP83867_PHYCR_DEEP_POWER_DOWN_EN_SHIFT)

/*
 * MDI_CROSSOVER (RW)
 *
 * MDI Crosssover Mode:
 * 1x = Enable automatic crossover
 * 01 = Manual MDI-X configuration
 * 00 = Manual MDI configuration
 */
#define DP83867_PHYCR_MDI_CROSSOVER_MASK (0x60U)
#define DP83867_PHYCR_MDI_CROSSOVER_SHIFT (5U)
#define DP83867_PHYCR_MDI_CROSSOVER_SET(x) (((uint16_t)(x) << DP83867_PHYCR_MDI_CROSSOVER_SHIFT) & DP83867_PHYCR_MDI_CROSSOVER_MASK)
#define DP83867_PHYCR_MDI_CROSSOVER_GET(x) (((uint16_t)(x) & DP83867_PHYCR_MDI_CROSSOVER_MASK) >> DP83867_PHYCR_MDI_CROSSOVER_SHIFT)

/*
 * DISABLE_CLK_125 (RW)
 *
 * Disable 125MHz Clock:
 * This bit may be used in conjunction with POWER_SAVE_MODE
 * (bits 9:8 of this register).
 * 1 = Disable CLK125.
 * 0 = Enable CLK125.
 */
#define DP83867_PHYCR_DISABLE_CLK_125_MASK (0x10U)
#define DP83867_PHYCR_DISABLE_CLK_125_SHIFT (4U)
#define DP83867_PHYCR_DISABLE_CLK_125_SET(x) (((uint16_t)(x) << DP83867_PHYCR_DISABLE_CLK_125_SHIFT) & DP83867_PHYCR_DISABLE_CLK_125_MASK)
#define DP83867_PHYCR_DISABLE_CLK_125_GET(x) (((uint16_t)(x) & DP83867_PHYCR_DISABLE_CLK_125_MASK) >> DP83867_PHYCR_DISABLE_CLK_125_SHIFT)

/*
 * STANDBY_MODE (RW)
 *
 * Standby Mode:
 * 1 = Enable standby mode. Digital and analog circuitry are powered
 * up, but no link can be established.
 * 0 = Normal operation.
 */
#define DP83867_PHYCR_STANDBY_MODE_MASK (0x4U)
#define DP83867_PHYCR_STANDBY_MODE_SHIFT (2U)
#define DP83867_PHYCR_STANDBY_MODE_SET(x) (((uint16_t)(x) << DP83867_PHYCR_STANDBY_MODE_SHIFT) & DP83867_PHYCR_STANDBY_MODE_MASK)
#define DP83867_PHYCR_STANDBY_MODE_GET(x) (((uint16_t)(x) & DP83867_PHYCR_STANDBY_MODE_MASK) >> DP83867_PHYCR_STANDBY_MODE_SHIFT)

/*
 * LINE_DRIVER_INV_EN (RW)
 *
 * Line Driver Inversion Enable:
 * 1 = Invert Line Driver Transmission.
 * 0 = Normal operation.
 */
#define DP83867_PHYCR_LINE_DRIVER_INV_EN_MASK (0x2U)
#define DP83867_PHYCR_LINE_DRIVER_INV_EN_SHIFT (1U)
#define DP83867_PHYCR_LINE_DRIVER_INV_EN_SET(x) (((uint16_t)(x) << DP83867_PHYCR_LINE_DRIVER_INV_EN_SHIFT) & DP83867_PHYCR_LINE_DRIVER_INV_EN_MASK)
#define DP83867_PHYCR_LINE_DRIVER_INV_EN_GET(x) (((uint16_t)(x) & DP83867_PHYCR_LINE_DRIVER_INV_EN_MASK) >> DP83867_PHYCR_LINE_DRIVER_INV_EN_SHIFT)

/*
 * DISABLE_JABBER (RW)
 *
 * Disable Jabber
 * 1 = Disable Jabber function.
 * 0 = Enable Jabber function.
 */
#define DP83867_PHYCR_DISABLE_JABBER_MASK (0x1U)
#define DP83867_PHYCR_DISABLE_JABBER_SHIFT (0U)
#define DP83867_PHYCR_DISABLE_JABBER_SET(x) (((uint16_t)(x) << DP83867_PHYCR_DISABLE_JABBER_SHIFT) & DP83867_PHYCR_DISABLE_JABBER_MASK)
#define DP83867_PHYCR_DISABLE_JABBER_GET(x) (((uint16_t)(x) & DP83867_PHYCR_DISABLE_JABBER_MASK) >> DP83867_PHYCR_DISABLE_JABBER_SHIFT)

/* Bitfield definition for register: PHYSTS */
/*
 * SPEED_SELECTION (RO)
 *
 * Speed Select Status:
 * These two bits indicate the speed of operation as determined by
 * Auto-Negotiation or as set by manual configuration.
 * 11 = Reserved
 * 10 = 1000 Mbps
 * 01 = 100 Mbps
 * 00 = 10 Mbps
 */
#define DP83867_PHYSTS_SPEED_SELECTION_MASK (0xC000U)
#define DP83867_PHYSTS_SPEED_SELECTION_SHIFT (14U)
#define DP83867_PHYSTS_SPEED_SELECTION_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_SPEED_SELECTION_MASK) >> DP83867_PHYSTS_SPEED_SELECTION_SHIFT)

/*
 * DUPLEX_MODE (RO)
 *
 * Duplex Mode Status:
 * 1 = Full Duplex
 * 0 = Half Duplex.
 */
#define DP83867_PHYSTS_DUPLEX_MODE_MASK (0x2000U)
#define DP83867_PHYSTS_DUPLEX_MODE_SHIFT (13U)
#define DP83867_PHYSTS_DUPLEX_MODE_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_DUPLEX_MODE_MASK) >> DP83867_PHYSTS_DUPLEX_MODE_SHIFT)

/*
 * PAGE_RECEIVED ( RO, LH, COR)
 *
 * Page Received:
 * This bit is latched high and will be cleared upon a read.
 * 1 = Page received.
 * 0 = No page received.
 */
#define DP83867_PHYSTS_PAGE_RECEIVED_MASK (0x1000U)
#define DP83867_PHYSTS_PAGE_RECEIVED_SHIFT (12U)
#define DP83867_PHYSTS_PAGE_RECEIVED_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_PAGE_RECEIVED_MASK) >> DP83867_PHYSTS_PAGE_RECEIVED_SHIFT)

/*
 * SPEED_DUPLEX_RESOLVED (RO)
 *
 * Speed Duplex Resolution Status:
 * 1 = Auto-Negotiation has completed or is disabled.
 * 0 = Auto-Negotiation is enabled and has not completed.
 */
#define DP83867_PHYSTS_SPEED_DUPLEX_RESOLVED_MASK (0x800U)
#define DP83867_PHYSTS_SPEED_DUPLEX_RESOLVED_SHIFT (11U)
#define DP83867_PHYSTS_SPEED_DUPLEX_RESOLVED_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_SPEED_DUPLEX_RESOLVED_MASK) >> DP83867_PHYSTS_SPEED_DUPLEX_RESOLVED_SHIFT)

/*
 * LINK_STATUS (RO)
 *
 * Link Status:
 * 1 = Link is up.
 * 0 = Link is down.
 */
#define DP83867_PHYSTS_LINK_STATUS_MASK (0x400U)
#define DP83867_PHYSTS_LINK_STATUS_SHIFT (10U)
#define DP83867_PHYSTS_LINK_STATUS_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_LINK_STATUS_MASK) >> DP83867_PHYSTS_LINK_STATUS_SHIFT)

/*
 * MDI_X_MODE_CD (RO)
 *
 * MDI/MDIX Resolution Status for C and D Line Driver Pairs:
 * 1 = Resolved as MDIX
 * 0 = Resolved as MDI.
 */
#define DP83867_PHYSTS_MDI_X_MODE_CD_MASK (0x200U)
#define DP83867_PHYSTS_MDI_X_MODE_CD_SHIFT (9U)
#define DP83867_PHYSTS_MDI_X_MODE_CD_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_MDI_X_MODE_CD_MASK) >> DP83867_PHYSTS_MDI_X_MODE_CD_SHIFT)

/*
 * MDI_X_MODE_AB (RO)
 *
 * MDI/MDIX Resolution Status for A and B Line Driver Pairs:
 * 1 = Resolved as MDIX
 * 0 = Resolved as MDI.
 */
#define DP83867_PHYSTS_MDI_X_MODE_AB_MASK (0x100U)
#define DP83867_PHYSTS_MDI_X_MODE_AB_SHIFT (8U)
#define DP83867_PHYSTS_MDI_X_MODE_AB_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_MDI_X_MODE_AB_MASK) >> DP83867_PHYSTS_MDI_X_MODE_AB_SHIFT)

/*
 * SPEED_OPT_STATUS (RO)
 *
 * Speed Optimization Status:
 * 1 = Auto-Negotiation is currently being performed with Speed
 * Optimization masking 1000BaseT abilities (Valid only during Auto-
 * Negotiation).
 * 0 = Auto-Negotiation is currently being performed without Speed
 * Optimization.
 */
#define DP83867_PHYSTS_SPEED_OPT_STATUS_MASK (0x80U)
#define DP83867_PHYSTS_SPEED_OPT_STATUS_SHIFT (7U)
#define DP83867_PHYSTS_SPEED_OPT_STATUS_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_SPEED_OPT_STATUS_MASK) >> DP83867_PHYSTS_SPEED_OPT_STATUS_SHIFT)

/*
 * SLEEP_MODE (RO)
 *
 * Sleep Mode Status:
 * 1 = Device currently in sleep mode.
 * 0 = Device currently in active mode.
 */
#define DP83867_PHYSTS_SLEEP_MODE_MASK (0x40U)
#define DP83867_PHYSTS_SLEEP_MODE_SHIFT (6U)
#define DP83867_PHYSTS_SLEEP_MODE_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_SLEEP_MODE_MASK) >> DP83867_PHYSTS_SLEEP_MODE_SHIFT)

/*
 * WIRE_CROSS (RO)
 *
 * Crossed Wire Indication:
 * Indicates channel polarity in 1000BASE-T linked status. Bits [5:2]
 * correspond to channels [D,C,B,A], respectively.
 * 1 = Channel polarity is reversed.
 * 0 = Channel polarity is normal.
 */
#define DP83867_PHYSTS_WIRE_CROSS_MASK (0x3CU)
#define DP83867_PHYSTS_WIRE_CROSS_SHIFT (2U)
#define DP83867_PHYSTS_WIRE_CROSS_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_WIRE_CROSS_MASK) >> DP83867_PHYSTS_WIRE_CROSS_SHIFT)

/*
 * POLARITY_STATUS (RO)
 *
 * 10BASE-Te Polarity Status:
 * 1 = Correct Polarity detected.
 * 0 = Inverted Polarity detected.
 */
#define DP83867_PHYSTS_POLARITY_STATUS_MASK (0x2U)
#define DP83867_PHYSTS_POLARITY_STATUS_SHIFT (1U)
#define DP83867_PHYSTS_POLARITY_STATUS_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_POLARITY_STATUS_MASK) >> DP83867_PHYSTS_POLARITY_STATUS_SHIFT)

/*
 * JABBER_DETECT (RO)
 *
 * Jabber Detect: This bit only has meaning in 10 Mbps mode.
 * This bit is a duplicate of the Jabber Detect bit in the BMSR register,
 * except that it is not cleared upon a read of the PHYSTS register.
 * 1 = Jabber condition detected.
 * 0 = No Jabber.
 */
#define DP83867_PHYSTS_JABBER_DETECT_MASK (0x1U)
#define DP83867_PHYSTS_JABBER_DETECT_SHIFT (0U)
#define DP83867_PHYSTS_JABBER_DETECT_GET(x) (((uint16_t)(x) & DP83867_PHYSTS_JABBER_DETECT_MASK) >> DP83867_PHYSTS_JABBER_DETECT_SHIFT)

/* Bitfield definition for register: MICR */
/*
 * AUTONEG_ERR_INT_EN (RW)
 *
 * Enable Auto-Negotiation Error Interrupt:
 * 1 = Enable Auto-Negotiation Error interrupt.
 * 0 = Disable Auto-Negotiation Error interrupt.
 */
#define DP83867_MICR_AUTONEG_ERR_INT_EN_MASK (0x8000U)
#define DP83867_MICR_AUTONEG_ERR_INT_EN_SHIFT (15U)
#define DP83867_MICR_AUTONEG_ERR_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_AUTONEG_ERR_INT_EN_SHIFT) & DP83867_MICR_AUTONEG_ERR_INT_EN_MASK)
#define DP83867_MICR_AUTONEG_ERR_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_AUTONEG_ERR_INT_EN_MASK) >> DP83867_MICR_AUTONEG_ERR_INT_EN_SHIFT)

/*
 * SPEED_CHNG_INT_EN (RW)
 *
 * Enable Speed Change Interrupt:
 * 1 = Enable Speed Change interrupt.
 * 0 = Disable Speed Change interrupt.
 */
#define DP83867_MICR_SPEED_CHNG_INT_EN_MASK (0x4000U)
#define DP83867_MICR_SPEED_CHNG_INT_EN_SHIFT (14U)
#define DP83867_MICR_SPEED_CHNG_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_SPEED_CHNG_INT_EN_SHIFT) & DP83867_MICR_SPEED_CHNG_INT_EN_MASK)
#define DP83867_MICR_SPEED_CHNG_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_SPEED_CHNG_INT_EN_MASK) >> DP83867_MICR_SPEED_CHNG_INT_EN_SHIFT)

/*
 * DUPLEX_MODE_CHNG_INT_EN (RW)
 *
 * Enable Duplex Mode Change Interrupt:
 * 1 = Enable Duplex Mode Change interrupt.
 * 0 = Disable Duplex Mode Change interrupt.
 */
#define DP83867_MICR_DUPLEX_MODE_CHNG_INT_EN_MASK (0x2000U)
#define DP83867_MICR_DUPLEX_MODE_CHNG_INT_EN_SHIFT (13U)
#define DP83867_MICR_DUPLEX_MODE_CHNG_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_DUPLEX_MODE_CHNG_INT_EN_SHIFT) & DP83867_MICR_DUPLEX_MODE_CHNG_INT_EN_MASK)
#define DP83867_MICR_DUPLEX_MODE_CHNG_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_DUPLEX_MODE_CHNG_INT_EN_MASK) >> DP83867_MICR_DUPLEX_MODE_CHNG_INT_EN_SHIFT)

/*
 * PAGE_RECEIVED_INT_EN (RW)
 *
 * Enable Page Received Interrupt:
 * 1 = Enable Page Received Interrupt.
 * 0 = Disable Page Received Interrupt.
 */
#define DP83867_MICR_PAGE_RECEIVED_INT_EN_MASK (0x1000U)
#define DP83867_MICR_PAGE_RECEIVED_INT_EN_SHIFT (12U)
#define DP83867_MICR_PAGE_RECEIVED_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_PAGE_RECEIVED_INT_EN_SHIFT) & DP83867_MICR_PAGE_RECEIVED_INT_EN_MASK)
#define DP83867_MICR_PAGE_RECEIVED_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_PAGE_RECEIVED_INT_EN_MASK) >> DP83867_MICR_PAGE_RECEIVED_INT_EN_SHIFT)

/*
 * AUTONEG_COMP_INT_EN (RW)
 *
 * Enable Auto-Negotiation Complete Interrupt:
 * 1 = Enable Auto-Negotiation Complete Interrupt.
 * 0 = Disable Auto-Negotiation Complete Interrupt.
 */
#define DP83867_MICR_AUTONEG_COMP_INT_EN_MASK (0x800U)
#define DP83867_MICR_AUTONEG_COMP_INT_EN_SHIFT (11U)
#define DP83867_MICR_AUTONEG_COMP_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_AUTONEG_COMP_INT_EN_SHIFT) & DP83867_MICR_AUTONEG_COMP_INT_EN_MASK)
#define DP83867_MICR_AUTONEG_COMP_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_AUTONEG_COMP_INT_EN_MASK) >> DP83867_MICR_AUTONEG_COMP_INT_EN_SHIFT)

/*
 * LINK_STATUS_CHNG_INT_EN (RW)
 *
 * Enable Link Status Change Interrupt:
 * 1 = Enable Link Status Change interrupt.
 * 0 = Disable Link Status Change interrupt.
 */
#define DP83867_MICR_LINK_STATUS_CHNG_INT_EN_MASK (0x400U)
#define DP83867_MICR_LINK_STATUS_CHNG_INT_EN_SHIFT (10U)
#define DP83867_MICR_LINK_STATUS_CHNG_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_LINK_STATUS_CHNG_INT_EN_SHIFT) & DP83867_MICR_LINK_STATUS_CHNG_INT_EN_MASK)
#define DP83867_MICR_LINK_STATUS_CHNG_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_LINK_STATUS_CHNG_INT_EN_MASK) >> DP83867_MICR_LINK_STATUS_CHNG_INT_EN_SHIFT)

/*
 * FALSE_CARRIER_INT_EN (RW)
 *
 * Enable False Carrier Interrupt:
 * 1 = Enable False Carrier interrupt.
 * 0 = Disable False Carrier interrupt.
 */
#define DP83867_MICR_FALSE_CARRIER_INT_EN_MASK (0x100U)
#define DP83867_MICR_FALSE_CARRIER_INT_EN_SHIFT (8U)
#define DP83867_MICR_FALSE_CARRIER_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_FALSE_CARRIER_INT_EN_SHIFT) & DP83867_MICR_FALSE_CARRIER_INT_EN_MASK)
#define DP83867_MICR_FALSE_CARRIER_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_FALSE_CARRIER_INT_EN_MASK) >> DP83867_MICR_FALSE_CARRIER_INT_EN_SHIFT)

/*
 * MDI_CROSSOVER_CHNG_INT_EN (RW)
 *
 * Enable MDI Crossover Change Interrupt:
 * 1 = Enable MDI Crossover Change interrupt.
 * 0 = Disable MDI Crossover Change interrupt.
 */
#define DP83867_MICR_MDI_CROSSOVER_CHNG_INT_EN_MASK (0x40U)
#define DP83867_MICR_MDI_CROSSOVER_CHNG_INT_EN_SHIFT (6U)
#define DP83867_MICR_MDI_CROSSOVER_CHNG_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_MDI_CROSSOVER_CHNG_INT_EN_SHIFT) & DP83867_MICR_MDI_CROSSOVER_CHNG_INT_EN_MASK)
#define DP83867_MICR_MDI_CROSSOVER_CHNG_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_MDI_CROSSOVER_CHNG_INT_EN_MASK) >> DP83867_MICR_MDI_CROSSOVER_CHNG_INT_EN_SHIFT)

/*
 * SPEED_OPT_EVENT_INT_EN (RW)
 *
 * Enable Speed Optimization Event Interrupt:
 * 1 = Enable Speed Optimization Event Interrupt.
 * 0 = Disable Speed Optimization Event Interrupt.
 */
#define DP83867_MICR_SPEED_OPT_EVENT_INT_EN_MASK (0x20U)
#define DP83867_MICR_SPEED_OPT_EVENT_INT_EN_SHIFT (5U)
#define DP83867_MICR_SPEED_OPT_EVENT_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_SPEED_OPT_EVENT_INT_EN_SHIFT) & DP83867_MICR_SPEED_OPT_EVENT_INT_EN_MASK)
#define DP83867_MICR_SPEED_OPT_EVENT_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_SPEED_OPT_EVENT_INT_EN_MASK) >> DP83867_MICR_SPEED_OPT_EVENT_INT_EN_SHIFT)

/*
 * SLEEP_MODE_CHNG_INT_EN (RW)
 *
 * Enable Sleep Mode Change Interrupt:
 * 1 = Enable Sleep Mode Change Interrupt.
 * 0 = Disable Sleep Mode Change Interrupt.
 */
#define DP83867_MICR_SLEEP_MODE_CHNG_INT_EN_MASK (0x10U)
#define DP83867_MICR_SLEEP_MODE_CHNG_INT_EN_SHIFT (4U)
#define DP83867_MICR_SLEEP_MODE_CHNG_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_SLEEP_MODE_CHNG_INT_EN_SHIFT) & DP83867_MICR_SLEEP_MODE_CHNG_INT_EN_MASK)
#define DP83867_MICR_SLEEP_MODE_CHNG_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_SLEEP_MODE_CHNG_INT_EN_MASK) >> DP83867_MICR_SLEEP_MODE_CHNG_INT_EN_SHIFT)

/*
 * WOL_INT_EN (RW)
 *
 * Enable Wake-on-LAN Interrupt:
 * 1 = Enable Wake-on-LAN Interrupt.
 * 0 = Disable Wake-on-LAN Interrupt.
 */
#define DP83867_MICR_WOL_INT_EN_MASK (0x8U)
#define DP83867_MICR_WOL_INT_EN_SHIFT (3U)
#define DP83867_MICR_WOL_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_WOL_INT_EN_SHIFT) & DP83867_MICR_WOL_INT_EN_MASK)
#define DP83867_MICR_WOL_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_WOL_INT_EN_MASK) >> DP83867_MICR_WOL_INT_EN_SHIFT)

/*
 * XGMII_ERR_INT_EN (RW)
 *
 * Enable xGMII Error Interrupt:
 * 1 = Enable xGMII Error Interrupt.
 * 0 = Disable xGMII Error Interrupt.
 */
#define DP83867_MICR_XGMII_ERR_INT_EN_MASK (0x4U)
#define DP83867_MICR_XGMII_ERR_INT_EN_SHIFT (2U)
#define DP83867_MICR_XGMII_ERR_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_XGMII_ERR_INT_EN_SHIFT) & DP83867_MICR_XGMII_ERR_INT_EN_MASK)
#define DP83867_MICR_XGMII_ERR_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_XGMII_ERR_INT_EN_MASK) >> DP83867_MICR_XGMII_ERR_INT_EN_SHIFT)

/*
 * POLARITY_CHNG_INT_EN (RW)
 *
 * Enable Polarity Change Interrupt:
 * 1 = Enable Polarity Change interrupt.
 * 0 = Disable Polarity Change interrupt.
 */
#define DP83867_MICR_POLARITY_CHNG_INT_EN_MASK (0x2U)
#define DP83867_MICR_POLARITY_CHNG_INT_EN_SHIFT (1U)
#define DP83867_MICR_POLARITY_CHNG_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_POLARITY_CHNG_INT_EN_SHIFT) & DP83867_MICR_POLARITY_CHNG_INT_EN_MASK)
#define DP83867_MICR_POLARITY_CHNG_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_POLARITY_CHNG_INT_EN_MASK) >> DP83867_MICR_POLARITY_CHNG_INT_EN_SHIFT)

/*
 * JABBER_INT_EN (RW)
 *
 * Enable Jabber Interrupt:
 * 1 = Enable Jabber interrupt.
 * 0 = Disable Jabber interrupt.
 */
#define DP83867_MICR_JABBER_INT_EN_MASK (0x1U)
#define DP83867_MICR_JABBER_INT_EN_SHIFT (0U)
#define DP83867_MICR_JABBER_INT_EN_SET(x) (((uint16_t)(x) << DP83867_MICR_JABBER_INT_EN_SHIFT) & DP83867_MICR_JABBER_INT_EN_MASK)
#define DP83867_MICR_JABBER_INT_EN_GET(x) (((uint16_t)(x) & DP83867_MICR_JABBER_INT_EN_MASK) >> DP83867_MICR_JABBER_INT_EN_SHIFT)

/* Bitfield definition for register: ISR */
/*
 * AUTONEG_ERR_INT (RO, LH, COR)
 *
 * Auto-Negotiation Error Interrupt:
 * 1 = Auto-Negotiation Error interrupt is pending and is cleared by the
 * current read.
 * 0 = No Auto-Negotiation Error interrupt.
 */
#define DP83867_ISR_AUTONEG_ERR_INT_MASK (0x8000U)
#define DP83867_ISR_AUTONEG_ERR_INT_SHIFT (15U)
#define DP83867_ISR_AUTONEG_ERR_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_AUTONEG_ERR_INT_MASK) >> DP83867_ISR_AUTONEG_ERR_INT_SHIFT)

/*
 * SPEED_CHNG_INT (RO, LH, COR)
 *
 * Speed Change Interrupt:
 * 1 = Speed Change interrupt is pending and is cleared by the current
 * read.
 * 0 = No Speed Change interrupt.
 */
#define DP83867_ISR_SPEED_CHNG_INT_MASK (0x4000U)
#define DP83867_ISR_SPEED_CHNG_INT_SHIFT (14U)
#define DP83867_ISR_SPEED_CHNG_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_SPEED_CHNG_INT_MASK) >> DP83867_ISR_SPEED_CHNG_INT_SHIFT)

/*
 * DUPLEX_MODE_CHNG_INT (RO, LH, COR)
 *
 * Duplex Mode Change Interrupt:
 * 1 = Duplex Mode Change interrupt is pending and is cleared by the
 * current read.
 * 0 = No Duplex Mode Change interrupt.
 */
#define DP83867_ISR_DUPLEX_MODE_CHNG_INT_MASK (0x2000U)
#define DP83867_ISR_DUPLEX_MODE_CHNG_INT_SHIFT (13U)
#define DP83867_ISR_DUPLEX_MODE_CHNG_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_DUPLEX_MODE_CHNG_INT_MASK) >> DP83867_ISR_DUPLEX_MODE_CHNG_INT_SHIFT)

/*
 * PAGE_RECEIVED_INT (RO, LH, COR)
 *
 * Page Received Interrupt:
 * 1 = Page Received Interrupt is pending and is cleared by the
 * current read.
 * 0 = No Page Received Interrupt is pending.
 */
#define DP83867_ISR_PAGE_RECEIVED_INT_MASK (0x1000U)
#define DP83867_ISR_PAGE_RECEIVED_INT_SHIFT (12U)
#define DP83867_ISR_PAGE_RECEIVED_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_PAGE_RECEIVED_INT_MASK) >> DP83867_ISR_PAGE_RECEIVED_INT_SHIFT)

/*
 * AUTONEG_COMP_INT (RO, LH, COR)
 *
 * Auto-Negotiation Complete Interrupt:
 * 1 = Auto-Negotiation Complete Interrupt is pending and is cleared
 * by the current read.
 * 0 = No Auto-Negotiation Complete Interrupt is pending.
 */
#define DP83867_ISR_AUTONEG_COMP_INT_MASK (0x800U)
#define DP83867_ISR_AUTONEG_COMP_INT_SHIFT (11U)
#define DP83867_ISR_AUTONEG_COMP_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_AUTONEG_COMP_INT_MASK) >> DP83867_ISR_AUTONEG_COMP_INT_SHIFT)

/*
 * LINK_STATUS_CHNG_INT (RO, LH, COR)
 *
 * Link Status Change Interrupt:
 * 1 = Link Status Change interrupt is pending and is cleared by the
 * current read.
 * 0 = No Link Status Change interrupt is pending.
 */
#define DP83867_ISR_LINK_STATUS_CHNG_INT_MASK (0x400U)
#define DP83867_ISR_LINK_STATUS_CHNG_INT_SHIFT (10U)
#define DP83867_ISR_LINK_STATUS_CHNG_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_LINK_STATUS_CHNG_INT_MASK) >> DP83867_ISR_LINK_STATUS_CHNG_INT_SHIFT)

/*
 * FALSE_CARRIER_INT ( RO, LH, COR)
 *
 * False Carrier Interrupt:
 * 1 = False Carrier interrupt is pending and is cleared by the current
 * read.
 * 0 = No False Carrier interrupt is pending.
 */
#define DP83867_ISR_FALSE_CARRIER_INT_MASK (0x100U)
#define DP83867_ISR_FALSE_CARRIER_INT_SHIFT (8U)
#define DP83867_ISR_FALSE_CARRIER_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_FALSE_CARRIER_INT_MASK) >> DP83867_ISR_FALSE_CARRIER_INT_SHIFT)

/*
 * MDI_CROSSOVER_CHNG_INT (RO, LH, COR)
 *
 * MDI Crossover Change Interrupt:
 * 1 = MDI Crossover Change interrupt is pending and is cleared by
 * the current read.
 * 0 = No MDI Crossover Change interrupt is pending.
 */
#define DP83867_ISR_MDI_CROSSOVER_CHNG_INT_MASK (0x40U)
#define DP83867_ISR_MDI_CROSSOVER_CHNG_INT_SHIFT (6U)
#define DP83867_ISR_MDI_CROSSOVER_CHNG_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_MDI_CROSSOVER_CHNG_INT_MASK) >> DP83867_ISR_MDI_CROSSOVER_CHNG_INT_SHIFT)

/*
 * SPEED_OPT_EVENT_INT (RO, LH, COR)
 *
 * Speed Optimization Event Interrupt:
 * 1 = Speed Optimization Event Interrupt is pending and is cleared by
 * the current read.
 * 0 = No Speed Optimization Event Interrupt is pending.
 */
#define DP83867_ISR_SPEED_OPT_EVENT_INT_MASK (0x20U)
#define DP83867_ISR_SPEED_OPT_EVENT_INT_SHIFT (5U)
#define DP83867_ISR_SPEED_OPT_EVENT_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_SPEED_OPT_EVENT_INT_MASK) >> DP83867_ISR_SPEED_OPT_EVENT_INT_SHIFT)

/*
 * SLEEP_MODE_CHNG_INT (RO, LH, COR)
 *
 * Sleep Mode Change Interrupt:
 * 1 = Sleep Mode Change Interrupt is pending and is cleared by the
 * current read.
 * 0 = No Sleep Mode Change Interrupt is pending.
 */
#define DP83867_ISR_SLEEP_MODE_CHNG_INT_MASK (0x10U)
#define DP83867_ISR_SLEEP_MODE_CHNG_INT_SHIFT (4U)
#define DP83867_ISR_SLEEP_MODE_CHNG_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_SLEEP_MODE_CHNG_INT_MASK) >> DP83867_ISR_SLEEP_MODE_CHNG_INT_SHIFT)

/*
 * WOL_INT (RO, LH, COR)
 *
 * Wake-on-LAN Interrupt:
 * 1 = Wake-on-LAN Interrupt is pending.
 * 0 = No Wake-on-LAN Interrupt is pending.
 */
#define DP83867_ISR_WOL_INT_MASK (0x8U)
#define DP83867_ISR_WOL_INT_SHIFT (3U)
#define DP83867_ISR_WOL_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_WOL_INT_MASK) >> DP83867_ISR_WOL_INT_SHIFT)

/*
 * XGMII_ERR_INT (RO, LH, COR)
 *
 * xGMII Error Interrupt:
 * 1 = xGMII Error Interrupt is pending and is cleared by the current
 * read.
 * 0 = No xGMII Error Interrupt is pending.
 */
#define DP83867_ISR_XGMII_ERR_INT_MASK (0x4U)
#define DP83867_ISR_XGMII_ERR_INT_SHIFT (2U)
#define DP83867_ISR_XGMII_ERR_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_XGMII_ERR_INT_MASK) >> DP83867_ISR_XGMII_ERR_INT_SHIFT)

/*
 * POLARITY_CHNG_INT (RO, LH, COR)
 *
 * Polarity Change Interrupt:
 * 1 = Polarity Change interrupt is pending and is cleared by the
 * current read.
 * 0 = No Polarity Change interrupt is pending.
 */
#define DP83867_ISR_POLARITY_CHNG_INT_MASK (0x2U)
#define DP83867_ISR_POLARITY_CHNG_INT_SHIFT (1U)
#define DP83867_ISR_POLARITY_CHNG_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_POLARITY_CHNG_INT_MASK) >> DP83867_ISR_POLARITY_CHNG_INT_SHIFT)

/*
 * JABBER_INT (RO, LH, COR)
 *
 * Jabber Interrupt:
 * 1 = Jabber interrupt is pending and is cleared by the current read.
 * 0 = No Jabber interrupt is pending.
 */
#define DP83867_ISR_JABBER_INT_MASK (0x1U)
#define DP83867_ISR_JABBER_INT_SHIFT (0U)
#define DP83867_ISR_JABBER_INT_GET(x) (((uint16_t)(x) & DP83867_ISR_JABBER_INT_MASK) >> DP83867_ISR_JABBER_INT_SHIFT)

/* Bitfield definition for register: CRG2 */
/*
 * INTERRUPT_POLARITY (RW)
 *
 * Configure Interrupt Polarity:
 * 1 = Interrupt pin is active low.
 * 0 = Interrupt pin is active high.
 */
#define DP83867_CRG2_INTERRUPT_POLARITY_MASK (0x2000U)
#define DP83867_CRG2_INTERRUPT_POLARITY_SHIFT (13U)
#define DP83867_CRG2_INTERRUPT_POLARITY_SET(x) (((uint16_t)(x) << DP83867_CRG2_INTERRUPT_POLARITY_SHIFT) & DP83867_CRG2_INTERRUPT_POLARITY_MASK)
#define DP83867_CRG2_INTERRUPT_POLARITY_GET(x) (((uint16_t)(x) & DP83867_CRG2_INTERRUPT_POLARITY_MASK) >> DP83867_CRG2_INTERRUPT_POLARITY_SHIFT)

/*
 * SPEED_OPT_ATTEMPT_CNT (RO)
 *
 * Speed Optimization Attempt Count:
 * Selects the number of 1000BASE-T link establishment attempt
 * failures prior to performing Speed Optimization.
 * 11 = 8
 * 10 = 4
 * 01 = 2
 * 00 = 1
 */
#define DP83867_CRG2_SPEED_OPT_ATTEMPT_CNT_MASK (0xC00U)
#define DP83867_CRG2_SPEED_OPT_ATTEMPT_CNT_SHIFT (10U)
#define DP83867_CRG2_SPEED_OPT_ATTEMPT_CNT_GET(x) (((uint16_t)(x) & DP83867_CRG2_SPEED_OPT_ATTEMPT_CNT_MASK) >> DP83867_CRG2_SPEED_OPT_ATTEMPT_CNT_SHIFT)

/*
 * SPEED_OPT_EN (RW)
 *
 * Speed Optimization Enable:
 * 1 = Enable Speed Optimization.
 * 0 = Disable Speed Optimization.
 */
#define DP83867_CRG2_SPEED_OPT_EN_MASK (0x200U)
#define DP83867_CRG2_SPEED_OPT_EN_SHIFT (9U)
#define DP83867_CRG2_SPEED_OPT_EN_SET(x) (((uint16_t)(x) << DP83867_CRG2_SPEED_OPT_EN_SHIFT) & DP83867_CRG2_SPEED_OPT_EN_MASK)
#define DP83867_CRG2_SPEED_OPT_EN_GET(x) (((uint16_t)(x) & DP83867_CRG2_SPEED_OPT_EN_MASK) >> DP83867_CRG2_SPEED_OPT_EN_SHIFT)

/*
 * SPEED_OPT_ENHANCED_EN (RW)
 *
 * Speed Optimization Enhanced Mode Enable:
 * In enhanced mode, speed is optimized if energy is not detected in
 * channels C and D.
 * 1 = Enable Speed Optimization enhanced mode.
 * 0 = Disable Speed Optimization enhanced mode.
 */
#define DP83867_CRG2_SPEED_OPT_ENHANCED_EN_MASK (0x100U)
#define DP83867_CRG2_SPEED_OPT_ENHANCED_EN_SHIFT (8U)
#define DP83867_CRG2_SPEED_OPT_ENHANCED_EN_SET(x) (((uint16_t)(x) << DP83867_CRG2_SPEED_OPT_ENHANCED_EN_SHIFT) & DP83867_CRG2_SPEED_OPT_ENHANCED_EN_MASK)
#define DP83867_CRG2_SPEED_OPT_ENHANCED_EN_GET(x) (((uint16_t)(x) & DP83867_CRG2_SPEED_OPT_ENHANCED_EN_MASK) >> DP83867_CRG2_SPEED_OPT_ENHANCED_EN_SHIFT)

/*
 * SGMII_AUTONEG_EN (RW)
 *
 * SGMII Auto-Negotiation Enable:
 * 1 = Enable SGMII Auto-Negotaition.
 * 0 = Disable SGMII Auto-Negotaition.
 */
#define DP83867_CRG2_SGMII_AUTONEG_EN_MASK (0x80U)
#define DP83867_CRG2_SGMII_AUTONEG_EN_SHIFT (7U)
#define DP83867_CRG2_SGMII_AUTONEG_EN_SET(x) (((uint16_t)(x) << DP83867_CRG2_SGMII_AUTONEG_EN_SHIFT) & DP83867_CRG2_SGMII_AUTONEG_EN_MASK)
#define DP83867_CRG2_SGMII_AUTONEG_EN_GET(x) (((uint16_t)(x) & DP83867_CRG2_SGMII_AUTONEG_EN_MASK) >> DP83867_CRG2_SGMII_AUTONEG_EN_SHIFT)

/*
 * SPEED_OPT_10M_EN (RW)
 *
 * Enable Speed Optimization to 10BASE-Te:
 * 1 = Enable speed optimization to 10BASE-Te if link establishment
 * fails in 1000BASE-T and 100BASE-TX .
 * 0 = Disable speed optimization to 10BASE-Te.
 */
#define DP83867_CRG2_SPEED_OPT_10M_EN_MASK (0x40U)
#define DP83867_CRG2_SPEED_OPT_10M_EN_SHIFT (6U)
#define DP83867_CRG2_SPEED_OPT_10M_EN_SET(x) (((uint16_t)(x) << DP83867_CRG2_SPEED_OPT_10M_EN_SHIFT) & DP83867_CRG2_SPEED_OPT_10M_EN_MASK)
#define DP83867_CRG2_SPEED_OPT_10M_EN_GET(x) (((uint16_t)(x) & DP83867_CRG2_SPEED_OPT_10M_EN_MASK) >> DP83867_CRG2_SPEED_OPT_10M_EN_SHIFT)

/* Bitfield definition for register: RECR */
/*
 * RXERCNT_15_0 (RO, WSC)
 *
 * RX_ER Counter:
 * Receive error counter. This register saturates at the maximum value
 * of 0xFFFF. It is cleared by dummy write to this register.
 */
#define DP83867_RECR_RXERCNT_15_0_MASK (0xFFFFU)
#define DP83867_RECR_RXERCNT_15_0_SHIFT (0U)
#define DP83867_RECR_RXERCNT_15_0_SET(x) (((uint16_t)(x) << DP83867_RECR_RXERCNT_15_0_SHIFT) & DP83867_RECR_RXERCNT_15_0_MASK)
#define DP83867_RECR_RXERCNT_15_0_GET(x) (((uint16_t)(x) & DP83867_RECR_RXERCNT_15_0_MASK) >> DP83867_RECR_RXERCNT_15_0_SHIFT)

/* Bitfield definition for register: STS2 */
/*
 * PRBS_LOCK (RO)
 *
 * PRBS Lock Status:
 * 1 = PRBS checker is locked to the received byte stream.
 * 0 = PRBS checker is not locked.
 */
#define DP83867_STS2_PRBS_LOCK_MASK (0x800U)
#define DP83867_STS2_PRBS_LOCK_SHIFT (11U)
#define DP83867_STS2_PRBS_LOCK_GET(x) (((uint16_t)(x) & DP83867_STS2_PRBS_LOCK_MASK) >> DP83867_STS2_PRBS_LOCK_SHIFT)

/*
 * PRBS_LOCK_LOST (RO, LH, COR)
 *
 * PRBS Lock Lost:
 * 1 = PRBS checker has lost lock.
 * 0 = PRBS checker has not lost lock.
 */
#define DP83867_STS2_PRBS_LOCK_LOST_MASK (0x400U)
#define DP83867_STS2_PRBS_LOCK_LOST_SHIFT (10U)
#define DP83867_STS2_PRBS_LOCK_LOST_GET(x) (((uint16_t)(x) & DP83867_STS2_PRBS_LOCK_LOST_MASK) >> DP83867_STS2_PRBS_LOCK_LOST_SHIFT)

/*
 * PKT_GEN_BUSY (RO)
 *
 * Packet Generator Busy:
 * 1 = Packet generation is in process.
 * 0 = Packet generation is not in process.
 */
#define DP83867_STS2_PKT_GEN_BUSY_MASK (0x200U)
#define DP83867_STS2_PKT_GEN_BUSY_SHIFT (9U)
#define DP83867_STS2_PKT_GEN_BUSY_GET(x) (((uint16_t)(x) & DP83867_STS2_PKT_GEN_BUSY_MASK) >> DP83867_STS2_PKT_GEN_BUSY_SHIFT)

/*
 * SCR_MODE_MASTER_1G (RO)
 *
 * Gigabit Master Scramble Mode:
 * 1 = 1G PCS (master) is in legacy encoding mode.
 * 0 = 1G PCS (master) is in normal encoding mode..
 */
#define DP83867_STS2_SCR_MODE_MASTER_1G_MASK (0x100U)
#define DP83867_STS2_SCR_MODE_MASTER_1G_SHIFT (8U)
#define DP83867_STS2_SCR_MODE_MASTER_1G_GET(x) (((uint16_t)(x) & DP83867_STS2_SCR_MODE_MASTER_1G_MASK) >> DP83867_STS2_SCR_MODE_MASTER_1G_SHIFT)

/*
 * SCR_MODE_SLAVE_1G (RO)
 *
 * Gigabit Slave Scramble Mode:
 * 1 = 1G PCS (slave) is in legacy encoding mode.
 * 0 = 1G PCS (slave) is in normal encoding mode..
 */
#define DP83867_STS2_SCR_MODE_SLAVE_1G_MASK (0x80U)
#define DP83867_STS2_SCR_MODE_SLAVE_1G_SHIFT (7U)
#define DP83867_STS2_SCR_MODE_SLAVE_1G_GET(x) (((uint16_t)(x) & DP83867_STS2_SCR_MODE_SLAVE_1G_MASK) >> DP83867_STS2_SCR_MODE_SLAVE_1G_SHIFT)

/*
 * CORE_PWR_MODE (RO)
 *
 * Core Power Mode:
 * 1 = Core is in normal power mode.
 * 0 = Core is power-down mode or in sleep mode.
 */
#define DP83867_STS2_CORE_PWR_MODE_MASK (0x40U)
#define DP83867_STS2_CORE_PWR_MODE_SHIFT (6U)
#define DP83867_STS2_CORE_PWR_MODE_GET(x) (((uint16_t)(x) & DP83867_STS2_CORE_PWR_MODE_MASK) >> DP83867_STS2_CORE_PWR_MODE_SHIFT)

/* Bitfield definition for register: LEDCR1 */
/*
 * LED_GPIO_SEL (RW)
 *
 * Source of the GPIO LED_3:
 * 1111: Reserved
 * 1110: Receive Error
 * 1101: Receive Error or Transmit Error
 * 1100: RESERVED
 * 1011: Link established, blink for transmit or receive activity
 * 1010: Full duplex
 * 1001: 100/1000BT link established
 * 1000: 10/100BT link established
 * 0111: 10BT link established
 * 0110: 100 BTX link established
 * 0101: 1000BT link established
 * 0100: Collision detected
 * 0011: Receive activity
 * 0010: Transmit activity
 * 0001: Receive or Transmit activity
 * 0000: Link established
 */
#define DP83867_LEDCR1_LED_GPIO_SEL_MASK (0xF000U)
#define DP83867_LEDCR1_LED_GPIO_SEL_SHIFT (12U)
#define DP83867_LEDCR1_LED_GPIO_SEL_SET(x) (((uint16_t)(x) << DP83867_LEDCR1_LED_GPIO_SEL_SHIFT) & DP83867_LEDCR1_LED_GPIO_SEL_MASK)
#define DP83867_LEDCR1_LED_GPIO_SEL_GET(x) (((uint16_t)(x) & DP83867_LEDCR1_LED_GPIO_SEL_MASK) >> DP83867_LEDCR1_LED_GPIO_SEL_SHIFT)

/*
 * LED_2_SEL (RW)
 *
 * Source of LED_2:
 * 1111: Reserved
 * 1110: Receive Error
 * 1101: Receive Error or Transmit Error
 * 1100: RESERVED
 * 1011: Link established, blink for transmit or receive activity
 * 1010: Full duplex
 * 1001: 100/1000BT link established
 * 1000: 10/100BT link established
 * 0111: 10BT link established
 * 0110: 100 BTX link established
 * 0101: 1000BT link established
 * 0100: Collision detected
 * 0011: Receive activity
 * 0010: Transmit activity
 * 0001: Receive or Transmit activity
 * 0000: Link established
 */
#define DP83867_LEDCR1_LED_2_SEL_MASK (0xF00U)
#define DP83867_LEDCR1_LED_2_SEL_SHIFT (8U)
#define DP83867_LEDCR1_LED_2_SEL_SET(x) (((uint16_t)(x) << DP83867_LEDCR1_LED_2_SEL_SHIFT) & DP83867_LEDCR1_LED_2_SEL_MASK)
#define DP83867_LEDCR1_LED_2_SEL_GET(x) (((uint16_t)(x) & DP83867_LEDCR1_LED_2_SEL_MASK) >> DP83867_LEDCR1_LED_2_SEL_SHIFT)

/*
 * LED_1_SEL (RW)
 *
 * Source of LED_1:
 * 1111: Reserved
 * 1110: Receive Error
 * 1101: Receive Error or Transmit Error
 * 1100: RESERVED
 * 1011: Link established, blink for transmit or receive activity
 * 1010: Full duplex
 * 1001: 100/1000BT link established
 * 1000: 10/100BT link established
 * 0111: 10BT link established
 * 0110: 100 BTX link established
 * 0101: 1000BT link established
 * 0100: Collision detected
 * 0011: Receive activity
 * 0010: Transmit activity
 * 0001: Receive or Transmit activity
 * 0000: Link established
 */
#define DP83867_LEDCR1_LED_1_SEL_MASK (0xF0U)
#define DP83867_LEDCR1_LED_1_SEL_SHIFT (4U)
#define DP83867_LEDCR1_LED_1_SEL_SET(x) (((uint16_t)(x) << DP83867_LEDCR1_LED_1_SEL_SHIFT) & DP83867_LEDCR1_LED_1_SEL_MASK)
#define DP83867_LEDCR1_LED_1_SEL_GET(x) (((uint16_t)(x) & DP83867_LEDCR1_LED_1_SEL_MASK) >> DP83867_LEDCR1_LED_1_SEL_SHIFT)

/*
 * LED_0_SEL (RW)
 *
 * Source of LED_0:
 * 1111: Reserved
 * 1110: Receive Error
 * 1101: Receive Error or Transmit Error
 * 1100: RESERVED
 * 1011: Link established, blink for transmit or receive activity
 * 1010: Full duplex
 * 1001: 100/1000BT link established
 * 1000: 10/100BT link established
 * 0111: 10BT link established
 * 0110: 100 BTX link established
 * 0101: 1000BT link established
 * 0100: Collision detected
 * 0011: Receive activity
 * 0010: Transmit activity
 * 0001: Receive or Transmit activity
 * 0000: Link established
 */
#define DP83867_LEDCR1_LED_0_SEL_MASK (0xFU)
#define DP83867_LEDCR1_LED_0_SEL_SHIFT (0U)
#define DP83867_LEDCR1_LED_0_SEL_SET(x) (((uint16_t)(x) << DP83867_LEDCR1_LED_0_SEL_SHIFT) & DP83867_LEDCR1_LED_0_SEL_MASK)
#define DP83867_LEDCR1_LED_0_SEL_GET(x) (((uint16_t)(x) & DP83867_LEDCR1_LED_0_SEL_MASK) >> DP83867_LEDCR1_LED_0_SEL_SHIFT)

/* Bitfield definition for register: LEDCR2 */
/*
 * LED_GPIO_POLARITY (RW)
 *
 * GPIO LED Polarity:
 * 1 = Active high
 * 0 = Active low
 */
#define DP83867_LEDCR2_LED_GPIO_POLARITY_MASK (0x4000U)
#define DP83867_LEDCR2_LED_GPIO_POLARITY_SHIFT (14U)
#define DP83867_LEDCR2_LED_GPIO_POLARITY_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_GPIO_POLARITY_SHIFT) & DP83867_LEDCR2_LED_GPIO_POLARITY_MASK)
#define DP83867_LEDCR2_LED_GPIO_POLARITY_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_GPIO_POLARITY_MASK) >> DP83867_LEDCR2_LED_GPIO_POLARITY_SHIFT)

/*
 * LED_GPIO_DRV_VAL (RW)
 *
 * GPIO LED Drive Value:
 * Value to force on GPIO LED
 * This bit is only valid if enabled through LED_GPIO_DRV_EN.
 */
#define DP83867_LEDCR2_LED_GPIO_DRV_VAL_MASK (0x2000U)
#define DP83867_LEDCR2_LED_GPIO_DRV_VAL_SHIFT (13U)
#define DP83867_LEDCR2_LED_GPIO_DRV_VAL_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_GPIO_DRV_VAL_SHIFT) & DP83867_LEDCR2_LED_GPIO_DRV_VAL_MASK)
#define DP83867_LEDCR2_LED_GPIO_DRV_VAL_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_GPIO_DRV_VAL_MASK) >> DP83867_LEDCR2_LED_GPIO_DRV_VAL_SHIFT)

/*
 * LED_GPIO_DRV_EN (RW)
 *
 * GPIO LED Drive Enable:
 * 1 = Force the value of the LED_GPIO_DRV_VAL bit onto the GPIO
 * LED.
 * 0 = Normal operation
 */
#define DP83867_LEDCR2_LED_GPIO_DRV_EN_MASK (0x1000U)
#define DP83867_LEDCR2_LED_GPIO_DRV_EN_SHIFT (12U)
#define DP83867_LEDCR2_LED_GPIO_DRV_EN_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_GPIO_DRV_EN_SHIFT) & DP83867_LEDCR2_LED_GPIO_DRV_EN_MASK)
#define DP83867_LEDCR2_LED_GPIO_DRV_EN_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_GPIO_DRV_EN_MASK) >> DP83867_LEDCR2_LED_GPIO_DRV_EN_SHIFT)

/*
 * LED_2_POLARITY (RW)
 *
 * LED_2 Polarity:
 * 1 = Active high
 * 0 = Active low
 */
#define DP83867_LEDCR2_LED_2_POLARITY_MASK (0x400U)
#define DP83867_LEDCR2_LED_2_POLARITY_SHIFT (10U)
#define DP83867_LEDCR2_LED_2_POLARITY_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_2_POLARITY_SHIFT) & DP83867_LEDCR2_LED_2_POLARITY_MASK)
#define DP83867_LEDCR2_LED_2_POLARITY_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_2_POLARITY_MASK) >> DP83867_LEDCR2_LED_2_POLARITY_SHIFT)

/*
 * LED_2_DRV_VAL (RW)
 *
 * LED_2 Drive Value:
 * Value to force on LED_2
 * This bit is only valid if enabled through LED_2_DRV_EN.
 */
#define DP83867_LEDCR2_LED_2_DRV_VAL_MASK (0x200U)
#define DP83867_LEDCR2_LED_2_DRV_VAL_SHIFT (9U)
#define DP83867_LEDCR2_LED_2_DRV_VAL_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_2_DRV_VAL_SHIFT) & DP83867_LEDCR2_LED_2_DRV_VAL_MASK)
#define DP83867_LEDCR2_LED_2_DRV_VAL_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_2_DRV_VAL_MASK) >> DP83867_LEDCR2_LED_2_DRV_VAL_SHIFT)

/*
 * LED_2_DRV_EN (RW)
 *
 * LED_2 Drive Enable:
 * 1 = Force the value of the LED_2_DRV_VAL bit onto LED_2.
 * 0 = Normal operation
 */
#define DP83867_LEDCR2_LED_2_DRV_EN_MASK (0x100U)
#define DP83867_LEDCR2_LED_2_DRV_EN_SHIFT (8U)
#define DP83867_LEDCR2_LED_2_DRV_EN_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_2_DRV_EN_SHIFT) & DP83867_LEDCR2_LED_2_DRV_EN_MASK)
#define DP83867_LEDCR2_LED_2_DRV_EN_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_2_DRV_EN_MASK) >> DP83867_LEDCR2_LED_2_DRV_EN_SHIFT)

/*
 * LED_1_POLARITY (RW)
 *
 * LED_1 Polarity:
 * 1 = Active high
 * 0 = Active low
 */
#define DP83867_LEDCR2_LED_1_POLARITY_MASK (0x40U)
#define DP83867_LEDCR2_LED_1_POLARITY_SHIFT (6U)
#define DP83867_LEDCR2_LED_1_POLARITY_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_1_POLARITY_SHIFT) & DP83867_LEDCR2_LED_1_POLARITY_MASK)
#define DP83867_LEDCR2_LED_1_POLARITY_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_1_POLARITY_MASK) >> DP83867_LEDCR2_LED_1_POLARITY_SHIFT)

/*
 * LED_1_DRV_VAL (RW)
 *
 * LED_1 Drive Value:
 * Value to force on LED_1
 * This bit is only valid if enabled through LED_1_DRV_EN.
 */
#define DP83867_LEDCR2_LED_1_DRV_VAL_MASK (0x20U)
#define DP83867_LEDCR2_LED_1_DRV_VAL_SHIFT (5U)
#define DP83867_LEDCR2_LED_1_DRV_VAL_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_1_DRV_VAL_SHIFT) & DP83867_LEDCR2_LED_1_DRV_VAL_MASK)
#define DP83867_LEDCR2_LED_1_DRV_VAL_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_1_DRV_VAL_MASK) >> DP83867_LEDCR2_LED_1_DRV_VAL_SHIFT)

/*
 * LED_1_DRV_EN (RW)
 *
 * LED_1 Drive Enable:
 * 1 = Force the value of the LED_1_DRV_VAL bit onto LED_1.
 * 0 = Normal operation
 */
#define DP83867_LEDCR2_LED_1_DRV_EN_MASK (0x10U)
#define DP83867_LEDCR2_LED_1_DRV_EN_SHIFT (4U)
#define DP83867_LEDCR2_LED_1_DRV_EN_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_1_DRV_EN_SHIFT) & DP83867_LEDCR2_LED_1_DRV_EN_MASK)
#define DP83867_LEDCR2_LED_1_DRV_EN_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_1_DRV_EN_MASK) >> DP83867_LEDCR2_LED_1_DRV_EN_SHIFT)

/*
 * LED_0_POLARITY (RW)
 *
 * LED_0 Polarity:
 * 1 = Active high
 * 0 = Active low
 */
#define DP83867_LEDCR2_LED_0_POLARITY_MASK (0x4U)
#define DP83867_LEDCR2_LED_0_POLARITY_SHIFT (2U)
#define DP83867_LEDCR2_LED_0_POLARITY_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_0_POLARITY_SHIFT) & DP83867_LEDCR2_LED_0_POLARITY_MASK)
#define DP83867_LEDCR2_LED_0_POLARITY_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_0_POLARITY_MASK) >> DP83867_LEDCR2_LED_0_POLARITY_SHIFT)

/*
 * LED_0_DRV_VAL (RW)
 *
 * LED_0 Drive Value:
 * Value to force on LED_0
 * This bit is only valid if enabled through LED_0_DRV_EN.
 */
#define DP83867_LEDCR2_LED_0_DRV_VAL_MASK (0x2U)
#define DP83867_LEDCR2_LED_0_DRV_VAL_SHIFT (1U)
#define DP83867_LEDCR2_LED_0_DRV_VAL_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_0_DRV_VAL_SHIFT) & DP83867_LEDCR2_LED_0_DRV_VAL_MASK)
#define DP83867_LEDCR2_LED_0_DRV_VAL_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_0_DRV_VAL_MASK) >> DP83867_LEDCR2_LED_0_DRV_VAL_SHIFT)

/*
 * LED_0_DRV_EN (RW)
 *
 * LED_0 Drive Enable:
 * 1 = Force the value of the LED_0_DRV_VAL bit onto LED_0.
 * 0 = Normal operation
 */
#define DP83867_LEDCR2_LED_0_DRV_EN_MASK (0x1U)
#define DP83867_LEDCR2_LED_0_DRV_EN_SHIFT (0U)
#define DP83867_LEDCR2_LED_0_DRV_EN_SET(x) (((uint16_t)(x) << DP83867_LEDCR2_LED_0_DRV_EN_SHIFT) & DP83867_LEDCR2_LED_0_DRV_EN_MASK)
#define DP83867_LEDCR2_LED_0_DRV_EN_GET(x) (((uint16_t)(x) & DP83867_LEDCR2_LED_0_DRV_EN_MASK) >> DP83867_LEDCR2_LED_0_DRV_EN_SHIFT)

/* Bitfield definition for register: LEDCR3 */
/*
 * LEDS_BYPASS_STRETCHING (RW)
 *
 * Bypass LED Stretching:
 * 1 = Bypass LED Stretching
 * 0 = Normal operation
 */
#define DP83867_LEDCR3_LEDS_BYPASS_STRETCHING_MASK (0x4U)
#define DP83867_LEDCR3_LEDS_BYPASS_STRETCHING_SHIFT (2U)
#define DP83867_LEDCR3_LEDS_BYPASS_STRETCHING_SET(x) (((uint16_t)(x) << DP83867_LEDCR3_LEDS_BYPASS_STRETCHING_SHIFT) & DP83867_LEDCR3_LEDS_BYPASS_STRETCHING_MASK)
#define DP83867_LEDCR3_LEDS_BYPASS_STRETCHING_GET(x) (((uint16_t)(x) & DP83867_LEDCR3_LEDS_BYPASS_STRETCHING_MASK) >> DP83867_LEDCR3_LEDS_BYPASS_STRETCHING_SHIFT)

/*
 * LEDS_BLINK_RATE (RW)
 *
 * LED Blink Rate:
 * 11: 2 Hz (500 ms)
 * 10: 5 Hz (200 ms)
 * 01: 10 Hz (100 ms)
 * 00 = 20 Hz (50 ms)
 */
#define DP83867_LEDCR3_LEDS_BLINK_RATE_MASK (0x3U)
#define DP83867_LEDCR3_LEDS_BLINK_RATE_SHIFT (0U)
#define DP83867_LEDCR3_LEDS_BLINK_RATE_SET(x) (((uint16_t)(x) << DP83867_LEDCR3_LEDS_BLINK_RATE_SHIFT) & DP83867_LEDCR3_LEDS_BLINK_RATE_MASK)
#define DP83867_LEDCR3_LEDS_BLINK_RATE_GET(x) (((uint16_t)(x) & DP83867_LEDCR3_LEDS_BLINK_RATE_MASK) >> DP83867_LEDCR3_LEDS_BLINK_RATE_SHIFT)

/* Bitfield definition for register: CFG3 */
/*
 * FAST_LINK_UP_IN_PARALLEL_DETECT (RW)
 *
 * Fast Link-Up in Parallel Detect Mode:
 * 1 = Enable Fast Link-Up time During Parallel Detection
 * 0 = Normal Parallel Detection link establishment
 * In Fast Auto MDI-X this bit is automatically set.
 */
#define DP83867_CFG3_FAST_LINK_UP_IN_PARALLEL_DETECT_MASK (0x8000U)
#define DP83867_CFG3_FAST_LINK_UP_IN_PARALLEL_DETECT_SHIFT (15U)
#define DP83867_CFG3_FAST_LINK_UP_IN_PARALLEL_DETECT_SET(x) (((uint16_t)(x) << DP83867_CFG3_FAST_LINK_UP_IN_PARALLEL_DETECT_SHIFT) & DP83867_CFG3_FAST_LINK_UP_IN_PARALLEL_DETECT_MASK)
#define DP83867_CFG3_FAST_LINK_UP_IN_PARALLEL_DETECT_GET(x) (((uint16_t)(x) & DP83867_CFG3_FAST_LINK_UP_IN_PARALLEL_DETECT_MASK) >> DP83867_CFG3_FAST_LINK_UP_IN_PARALLEL_DETECT_SHIFT)

/*
 * FAST_AN_ENABLE (RW)
 *
 * Fast Auto-Negotiation Enable:
 * 1 = Enable Fast Auto-Negotiation mode – The PHY auto-
 * negotiates using Timer setting according to Fast AN Sel bits
 * 0 = Disable Fast Auto-Negotiation mode – The PHY auto-
 * negotiates using normal Timer setting
 * Adjusting these bits reduces the time it takes to Auto-negotiate
 * between two PHYs. Note: When using this option care must be
 * taken to maintain proper operation of the system. While shortening
 * these timer intervals may not cause problems in normal operation,
 * there are certain situations where this may lead to problems.
 */
#define DP83867_CFG3_FAST_AN_ENABLE_MASK (0x4000U)
#define DP83867_CFG3_FAST_AN_ENABLE_SHIFT (14U)
#define DP83867_CFG3_FAST_AN_ENABLE_SET(x) (((uint16_t)(x) << DP83867_CFG3_FAST_AN_ENABLE_SHIFT) & DP83867_CFG3_FAST_AN_ENABLE_MASK)
#define DP83867_CFG3_FAST_AN_ENABLE_GET(x) (((uint16_t)(x) & DP83867_CFG3_FAST_AN_ENABLE_MASK) >> DP83867_CFG3_FAST_AN_ENABLE_SHIFT)

/*
 * FAST_AN_SEL (RW)
 *
 * Fast Auto-Negotiation Select bits:
 * Fast AN Select  Break Link Timer(ms)    Link Fail Inhibit TImer(ms)   Auto-Neg Wait Timer(ms)
 * <00>            80                      50                            35
 * <01>            120                     75                            50
 * <10>            240                     150                           100
 * <11>            NA                      NA                            NA
 * Adjusting these bits reduces the time it takes to auto-negotiate
 * between two PHYs. In Fast AN mode, both PHYs should be
 * configured to the same configuration. These 2 bits define the
 * duration for each state of the Auto-Negotiation process according
 * to the table above. The new duration time must be enabled by
 * setting Fast AN En - bit 4 of this register. Note: Using this mode in
 * cases where both link partners are not configured to the same
 * Fast Auto-Negotiation configuration might produce scenarios with
 * unexpected behavior.
 */
#define DP83867_CFG3_FAST_AN_SEL_MASK (0x3000U)
#define DP83867_CFG3_FAST_AN_SEL_SHIFT (12U)
#define DP83867_CFG3_FAST_AN_SEL_SET(x) (((uint16_t)(x) << DP83867_CFG3_FAST_AN_SEL_SHIFT) & DP83867_CFG3_FAST_AN_SEL_MASK)
#define DP83867_CFG3_FAST_AN_SEL_GET(x) (((uint16_t)(x) & DP83867_CFG3_FAST_AN_SEL_MASK) >> DP83867_CFG3_FAST_AN_SEL_SHIFT)

/*
 * EXTENDED_FD_ABILITY (RW)
 *
 * Extended Full-Duplex Ability:
 * 1 = Force Full-Duplex while working with link partner in forced
 * 100B-TX. When the PHY is set to Auto-Negotiation or Force 100B-
 * TX and the link partner is operated in Force 100B-TX, the link is
 * always Full Duplex
 * 0 = Disable Extended Full Duplex Ability. Decision to work in Full
 * Duplex or Half Duplex mode follows IEEE specification.
 */
#define DP83867_CFG3_EXTENDED_FD_ABILITY_MASK (0x800U)
#define DP83867_CFG3_EXTENDED_FD_ABILITY_SHIFT (11U)
#define DP83867_CFG3_EXTENDED_FD_ABILITY_SET(x) (((uint16_t)(x) << DP83867_CFG3_EXTENDED_FD_ABILITY_SHIFT) & DP83867_CFG3_EXTENDED_FD_ABILITY_MASK)
#define DP83867_CFG3_EXTENDED_FD_ABILITY_GET(x) (((uint16_t)(x) & DP83867_CFG3_EXTENDED_FD_ABILITY_MASK) >> DP83867_CFG3_EXTENDED_FD_ABILITY_SHIFT)

/*
 * ROBUST_AUTO_MDIX (RW)
 *
 * Robust Auto-MDIX:
 * 1 =Enable Robust Auto MDI/MDIX resolution
 * 0 = Normal Auto MDI/MDIX mode
 * If link partners are configured to operational modes that are not
 * supported by normal Auto MDI/MDIX mode (like Auto-Neg versus
 * Force 100Base-TX or Force 100Base-TX versus Force 100Base-
 * TX), this Robust Auto MDI/MDIX mode allows MDI/MDIX
 * resolution and prevents deadlock.
 */
#define DP83867_CFG3_ROBUST_AUTO_MDIX_MASK (0x200U)
#define DP83867_CFG3_ROBUST_AUTO_MDIX_SHIFT (9U)
#define DP83867_CFG3_ROBUST_AUTO_MDIX_SET(x) (((uint16_t)(x) << DP83867_CFG3_ROBUST_AUTO_MDIX_SHIFT) & DP83867_CFG3_ROBUST_AUTO_MDIX_MASK)
#define DP83867_CFG3_ROBUST_AUTO_MDIX_GET(x) (((uint16_t)(x) & DP83867_CFG3_ROBUST_AUTO_MDIX_MASK) >> DP83867_CFG3_ROBUST_AUTO_MDIX_SHIFT)

/*
 * FAST_AUTO_MDIX (RW)
 *
 * Fast Auto MDI/MDIX:
 * 1 = Enable Fast Auto MDI/MDIX mode
 * 0 = Normal Auto MDI/MDIX mode
 * If both link partners are configured to work in Force 100Base-TX
 * mode (Auto-Negotiation is disabled), this mode enables Automatic
 * MDI/MDIX resolution in a short time.
 */
#define DP83867_CFG3_FAST_AUTO_MDIX_MASK (0x100U)
#define DP83867_CFG3_FAST_AUTO_MDIX_SHIFT (8U)
#define DP83867_CFG3_FAST_AUTO_MDIX_SET(x) (((uint16_t)(x) << DP83867_CFG3_FAST_AUTO_MDIX_SHIFT) & DP83867_CFG3_FAST_AUTO_MDIX_MASK)
#define DP83867_CFG3_FAST_AUTO_MDIX_GET(x) (((uint16_t)(x) & DP83867_CFG3_FAST_AUTO_MDIX_MASK) >> DP83867_CFG3_FAST_AUTO_MDIX_SHIFT)

/*
 * INT_OE (RW)
 *
 * Interrupt Output Enable:
 * 1 = INTN/PWDNN Pad is an Interrupt Output.
 * 0 = INTN/PWDNN Pad in a Power-Down Input.
 */
#define DP83867_CFG3_INT_OE_MASK (0x80U)
#define DP83867_CFG3_INT_OE_SHIFT (7U)
#define DP83867_CFG3_INT_OE_SET(x) (((uint16_t)(x) << DP83867_CFG3_INT_OE_SHIFT) & DP83867_CFG3_INT_OE_MASK)
#define DP83867_CFG3_INT_OE_GET(x) (((uint16_t)(x) & DP83867_CFG3_INT_OE_MASK) >> DP83867_CFG3_INT_OE_SHIFT)

/*
 * FORCE_INTERRUPT (RW)
 *
 * Force Interrupt:
 * 1 = Assert interrupt pin.
 * 0 = Normal interrupt mode.
 */
#define DP83867_CFG3_FORCE_INTERRUPT_MASK (0x40U)
#define DP83867_CFG3_FORCE_INTERRUPT_SHIFT (6U)
#define DP83867_CFG3_FORCE_INTERRUPT_SET(x) (((uint16_t)(x) << DP83867_CFG3_FORCE_INTERRUPT_SHIFT) & DP83867_CFG3_FORCE_INTERRUPT_MASK)
#define DP83867_CFG3_FORCE_INTERRUPT_GET(x) (((uint16_t)(x) & DP83867_CFG3_FORCE_INTERRUPT_MASK) >> DP83867_CFG3_FORCE_INTERRUPT_SHIFT)

/*
 * TDR_FAIL (RO)
 *
 * TDR Failure:
 * 1 = TDR failed.
 * 0 = Normal TDR operation.
 */
#define DP83867_CFG3_TDR_FAIL_MASK (0x4U)
#define DP83867_CFG3_TDR_FAIL_SHIFT (2U)
#define DP83867_CFG3_TDR_FAIL_GET(x) (((uint16_t)(x) & DP83867_CFG3_TDR_FAIL_MASK) >> DP83867_CFG3_TDR_FAIL_SHIFT)

/*
 * TDR_DONE (RO)
 *
 * TDR Done:
 * 1 = TDR has completed.
 * 0 = TDR has not completed.
 */
#define DP83867_CFG3_TDR_DONE_MASK (0x2U)
#define DP83867_CFG3_TDR_DONE_SHIFT (1U)
#define DP83867_CFG3_TDR_DONE_GET(x) (((uint16_t)(x) & DP83867_CFG3_TDR_DONE_MASK) >> DP83867_CFG3_TDR_DONE_SHIFT)

/*
 * TDR_START (RW)
 *
 * TDR Start:
 * 1 = Start TDR.
 * 0 = Normal operation
 */
#define DP83867_CFG3_TDR_START_MASK (0x1U)
#define DP83867_CFG3_TDR_START_SHIFT (0U)
#define DP83867_CFG3_TDR_START_SET(x) (((uint16_t)(x) << DP83867_CFG3_TDR_START_SHIFT) & DP83867_CFG3_TDR_START_MASK)
#define DP83867_CFG3_TDR_START_GET(x) (((uint16_t)(x) & DP83867_CFG3_TDR_START_MASK) >> DP83867_CFG3_TDR_START_SHIFT)

/* Bitfield definition for register: CTRL */
/*
 * SW_RESET (RW,SC)
 *
 * Software Reset:
 * 1 = Perform a full reset, including registers.
 * 0 = Normal operation.
 */
#define DP83867_CTRL_SW_RESET_MASK (0x8000U)
#define DP83867_CTRL_SW_RESET_SHIFT (15U)
#define DP83867_CTRL_SW_RESET_SET(x) (((uint16_t)(x) << DP83867_CTRL_SW_RESET_SHIFT) & DP83867_CTRL_SW_RESET_MASK)
#define DP83867_CTRL_SW_RESET_GET(x) (((uint16_t)(x) & DP83867_CTRL_SW_RESET_MASK) >> DP83867_CTRL_SW_RESET_SHIFT)

/*
 * SW_RESTART (RW,SC)
 *
 * Software Restart:
 * 1 = Perform a full reset, not including registers. .
 * 0 = Normal operation.
 */
#define DP83867_CTRL_SW_RESTART_MASK (0x4000U)
#define DP83867_CTRL_SW_RESTART_SHIFT (14U)
#define DP83867_CTRL_SW_RESTART_SET(x) (((uint16_t)(x) << DP83867_CTRL_SW_RESTART_SHIFT) & DP83867_CTRL_SW_RESTART_MASK)
#define DP83867_CTRL_SW_RESTART_GET(x) (((uint16_t)(x) & DP83867_CTRL_SW_RESTART_MASK) >> DP83867_CTRL_SW_RESTART_SHIFT)

/* Bitfield definition for register: RGMIIDCTL */
/*
 * RGMII_TX_DELAY_CTRL (RW)
 *
 * RGMII Transmit Clock Delay:
 * 1111: 4.00 ns
 * 1110: 3.75 ns
 * 1101: 3.50 ns
 * 1100: 3.25 ns
 * 1011: 3.00 ns
 * 1010: 2.75 ns
 * 1001: 2.50 ns
 * 1000: 2.25 ns
 * 0111: 2.00 ns
 * 0110: 1.75 ns
 * 0101: 1.50 ns
 * 0100: 1.25 ns
 * 0011: 1.00 ns
 * 0010: 0.75 ns
 * 0001: 0.50 ns
 * 0000: 0.25 ns
 */
#define DP83867_RGMIIDCTL_RGMII_TX_DELAY_CTRL_MASK (0xF0U)
#define DP83867_RGMIIDCTL_RGMII_TX_DELAY_CTRL_SHIFT (4U)
#define DP83867_RGMIIDCTL_RGMII_TX_DELAY_CTRL_SET(x) (((uint16_t)(x) << DP83867_RGMIIDCTL_RGMII_TX_DELAY_CTRL_SHIFT) & DP83867_RGMIIDCTL_RGMII_TX_DELAY_CTRL_MASK)
#define DP83867_RGMIIDCTL_RGMII_TX_DELAY_CTRL_GET(x) (((uint16_t)(x) & DP83867_RGMIIDCTL_RGMII_TX_DELAY_CTRL_MASK) >> DP83867_RGMIIDCTL_RGMII_TX_DELAY_CTRL_SHIFT)

/*
 * RGMII_RX_DELAY_CTRL (RW)
 *
 * RGMII Receive Clock Delay:
 * 1111: 4.00 ns
 * 1110: 3.75 ns
 * 1101: 3.50 ns
 * 1100: 3.25 ns
 * 1011: 3.00 ns
 * 1010: 2.75 ns
 * 1001: 2.50 ns
 * 1000: 2.25 ns
 * 0111: 2.00 ns
 * 0110: 1.75 ns
 * 0101: 1.50 ns
 * 0100: 1.25 ns
 * 0011: 1.00 ns
 * 0010: 0.75 ns
 * 0001: 0.50 ns
 * 0000: 0.25 ns
 */
#define DP83867_RGMIIDCTL_RGMII_RX_DELAY_CTRL_MASK (0xFU)
#define DP83867_RGMIIDCTL_RGMII_RX_DELAY_CTRL_SHIFT (0U)
#define DP83867_RGMIIDCTL_RGMII_RX_DELAY_CTRL_SET(x) (((uint16_t)(x) << DP83867_RGMIIDCTL_RGMII_RX_DELAY_CTRL_SHIFT) & DP83867_RGMIIDCTL_RGMII_RX_DELAY_CTRL_MASK)
#define DP83867_RGMIIDCTL_RGMII_RX_DELAY_CTRL_GET(x) (((uint16_t)(x) & DP83867_RGMIIDCTL_RGMII_RX_DELAY_CTRL_MASK) >> DP83867_RGMIIDCTL_RGMII_RX_DELAY_CTRL_SHIFT)




#endif /* HPM_DP83867_REGS_H */
