/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_RTL8211_REGS_H
#define HPM_RTL8211_REGS_H

typedef enum {
    RTL8211_BMCR                        = 0,   /* 0x0: Basic Mode Control Register */
    RTL8211_BMSR                        = 1,   /* 0x1: (Basic Mode Status Register */
    RTL8211_PHYID1                      = 2,   /* 0x2: PHY Identifier Register 1 */
    RTL8211_PHYID2                      = 3,   /* 0x3: PHY Identifier Register 2 */
    RTL8211_PHYSR                       = 17,  /* 0x11: PHY Specific Status Register */
} RTL8211_REG_Type;


/* Bitfield definition for register: BMCR */
/*
 * RESET (RW/SC)
 *
 * Reset.
 * 1: PHY reset
 * 0: Normal operation
 * Register 0 (BMCR) and register 1 (BMSR) will return to default
 * values after a software reset (set Bit15 to 1).
 * This action may change the internal PHY state and the state of the
 * physical link associated with the PHY.
 */
#define RTL8211_BMCR_RESET_MASK (0x8000U)
#define RTL8211_BMCR_RESET_SHIFT (15U)
#define RTL8211_BMCR_RESET_SET(x) (((uint16_t)(x) << RTL8211_BMCR_RESET_SHIFT) & RTL8211_BMCR_RESET_MASK)
#define RTL8211_BMCR_RESET_GET(x) (((uint16_t)(x) & RTL8211_BMCR_RESET_MASK) >> RTL8211_BMCR_RESET_SHIFT)

/*
 * LOOPBACK (RW)
 *
 * Loopback Mode.
 * 1: Enable PCS loopback mode
 * 0: Disable PCS loopback mode
 */
#define RTL8211_BMCR_LOOPBACK_MASK (0x4000U)
#define RTL8211_BMCR_LOOPBACK_SHIFT (14U)
#define RTL8211_BMCR_LOOPBACK_SET(x) (((uint16_t)(x) << RTL8211_BMCR_LOOPBACK_SHIFT) & RTL8211_BMCR_LOOPBACK_MASK)
#define RTL8211_BMCR_LOOPBACK_GET(x) (((uint16_t)(x) & RTL8211_BMCR_LOOPBACK_MASK) >> RTL8211_BMCR_LOOPBACK_SHIFT)

/*
 * SPEED0 (RW)
 *
 * Speed Select (Bits 6, 13):
 * When auto-negotiation is disabled writing to this bit allows the port
 * speed to be selected.
 * 11 = Reserved
 * 10 = Reserved
 * 1 = 100 Mbps
 * 0 = 10 Mbps
 */
#define RTL8211_BMCR_SPEED0_MASK (0x2000U)
#define RTL8211_BMCR_SPEED0_SHIFT (13U)
#define RTL8211_BMCR_SPEED0_SET(x) (((uint16_t)(x) << RTL8211_BMCR_SPEED0_SHIFT) & RTL8211_BMCR_SPEED0_MASK)
#define RTL8211_BMCR_SPEED0_GET(x) (((uint16_t)(x) & RTL8211_BMCR_SPEED0_MASK) >> RTL8211_BMCR_SPEED0_SHIFT)

/*
 * ANE (RW)
 *
 * Auto-Negotiation Enable.
 * 1: Enable Auto-Negotiation
 * 0: Disable Auto-Negotiation
 */
#define RTL8211_BMCR_ANE_MASK (0x1000U)
#define RTL8211_BMCR_ANE_SHIFT (12U)
#define RTL8211_BMCR_ANE_SET(x) (((uint16_t)(x) << RTL8211_BMCR_ANE_SHIFT) & RTL8211_BMCR_ANE_MASK)
#define RTL8211_BMCR_ANE_GET(x) (((uint16_t)(x) & RTL8211_BMCR_ANE_MASK) >> RTL8211_BMCR_ANE_SHIFT)

/*
 * PWD (RW)
 *
 * Power Down.
 * 1: Power down (only Management Interface and logic are active; link
 * is down)
 * 0: Normal operation
 */
#define RTL8211_BMCR_PWD_MASK (0x800U)
#define RTL8211_BMCR_PWD_SHIFT (11U)
#define RTL8211_BMCR_PWD_SET(x) (((uint16_t)(x) << RTL8211_BMCR_PWD_SHIFT) & RTL8211_BMCR_PWD_MASK)
#define RTL8211_BMCR_PWD_GET(x) (((uint16_t)(x) & RTL8211_BMCR_PWD_MASK) >> RTL8211_BMCR_PWD_SHIFT)

/*
 * ISOLATE (RW)
 *
 * Isolate.
 * 1: RGMII/GMII interface is isolated; the serial management interface
 * (MDC, MDIO) is still active. When this bit is asserted, the
 * RTL8211E-VB(VL)/RTL8211EG-VB ignores TXD[7:0], and TXCLT
 * inputs, and presents a high impedance on TXC, RXC, RXCLT,
 * RXD[7:0].
 * 0: Normal operation
 */
#define RTL8211_BMCR_ISOLATE_MASK (0x400U)
#define RTL8211_BMCR_ISOLATE_SHIFT (10U)
#define RTL8211_BMCR_ISOLATE_SET(x) (((uint16_t)(x) << RTL8211_BMCR_ISOLATE_SHIFT) & RTL8211_BMCR_ISOLATE_MASK)
#define RTL8211_BMCR_ISOLATE_GET(x) (((uint16_t)(x) & RTL8211_BMCR_ISOLATE_MASK) >> RTL8211_BMCR_ISOLATE_SHIFT)

/*
 * RESTART_AN (RW/SC)
 *
 * Restart Auto-Negotiation.
 * 1: Restart Auto-Negotiation
 * 0: Normal operation
 */
#define RTL8211_BMCR_RESTART_AN_MASK (0x200U)
#define RTL8211_BMCR_RESTART_AN_SHIFT (9U)
#define RTL8211_BMCR_RESTART_AN_SET(x) (((uint16_t)(x) << RTL8211_BMCR_RESTART_AN_SHIFT) & RTL8211_BMCR_RESTART_AN_MASK)
#define RTL8211_BMCR_RESTART_AN_GET(x) (((uint16_t)(x) & RTL8211_BMCR_RESTART_AN_MASK) >> RTL8211_BMCR_RESTART_AN_SHIFT)

/*
 * DUPLEX (RW)
 *
 * Duplex Mode.
 * 1: Full Duplex operation
 * 0: Half Duplex operation
 * This bit is valid only in force mode, i.e., NWay is disabled.
 */
#define RTL8211_BMCR_DUPLEX_MASK (0x100U)
#define RTL8211_BMCR_DUPLEX_SHIFT (8U)
#define RTL8211_BMCR_DUPLEX_SET(x) (((uint16_t)(x) << RTL8211_BMCR_DUPLEX_SHIFT) & RTL8211_BMCR_DUPLEX_MASK)
#define RTL8211_BMCR_DUPLEX_GET(x) (((uint16_t)(x) & RTL8211_BMCR_DUPLEX_MASK) >> RTL8211_BMCR_DUPLEX_SHIFT)

/*
 * COLLISION_TEST (RW)
 *
 * Collision Test.
 * 1: Collision test enabled
 * 0: Normal operation
 */
#define RTL8211_BMCR_COLLISION_TEST_MASK (0x80U)
#define RTL8211_BMCR_COLLISION_TEST_SHIFT (7U)
#define RTL8211_BMCR_COLLISION_TEST_SET(x) (((uint16_t)(x) << RTL8211_BMCR_COLLISION_TEST_SHIFT) & RTL8211_BMCR_COLLISION_TEST_MASK)
#define RTL8211_BMCR_COLLISION_TEST_GET(x) (((uint16_t)(x) & RTL8211_BMCR_COLLISION_TEST_MASK) >> RTL8211_BMCR_COLLISION_TEST_SHIFT)

/*
 * SPEED1 (RW)
 *
 * Speed Select Bit 1.
 * Refer to bit 13.
 */
#define RTL8211_BMCR_SPEED1_MASK (0x40U)
#define RTL8211_BMCR_SPEED1_SHIFT (6U)
#define RTL8211_BMCR_SPEED1_SET(x) (((uint16_t)(x) << RTL8211_BMCR_SPEED1_SHIFT) & RTL8211_BMCR_SPEED1_MASK)
#define RTL8211_BMCR_SPEED1_GET(x) (((uint16_t)(x) & RTL8211_BMCR_SPEED1_MASK) >> RTL8211_BMCR_SPEED1_SHIFT)

/* Bitfield definition for register: BMSR */
/*
 * 100BASE_T4 (RO)
 *
 * 100Base-T4 Capability.
 * The RTL8211E-VB(VL)/RTL8211EG-VB does not support
 * 100Base-T4 mode. This bit should always be 0.
 */
#define RTL8211_BMSR_100BASE_T4_MASK (0x8000U)
#define RTL8211_BMSR_100BASE_T4_SHIFT (15U)
#define RTL8211_BMSR_100BASE_T4_GET(x) (((uint16_t)(x) & RTL8211_BMSR_100BASE_T4_MASK) >> RTL8211_BMSR_100BASE_T4_SHIFT)

/*
 * 100BASE_TX_FULL (RO)
 *
 * 100Base-TX Full Duplex Capability.
 * 1: Device is able to perform 100Base-TX in full duplex mode
 * 0: Device is not able to perform 100Base-TX in full duplex mode
 */
#define RTL8211_BMSR_100BASE_TX_FULL_MASK (0x4000U)
#define RTL8211_BMSR_100BASE_TX_FULL_SHIFT (14U)
#define RTL8211_BMSR_100BASE_TX_FULL_GET(x) (((uint16_t)(x) & RTL8211_BMSR_100BASE_TX_FULL_MASK) >> RTL8211_BMSR_100BASE_TX_FULL_SHIFT)

/*
 * 100BASE_TX_HALF (RO)
 *
 * 100Base-TX Half Duplex Capability.
 * 1: Device is able to perform 100Base-TX in half duplex mode
 * 0: Device is not able to perform 100Base-TX in half duplex mode
 */
#define RTL8211_BMSR_100BASE_TX_HALF_MASK (0x2000U)
#define RTL8211_BMSR_100BASE_TX_HALF_SHIFT (13U)
#define RTL8211_BMSR_100BASE_TX_HALF_GET(x) (((uint16_t)(x) & RTL8211_BMSR_100BASE_TX_HALF_MASK) >> RTL8211_BMSR_100BASE_TX_HALF_SHIFT)

/*
 * 10BASE_T_FULL (RO)
 *
 * 10Base-T Full Duplex Capability.
 * 1: Device is able to perform 10Base-T in full duplex mode.
 * 0: Device is not able to perform 10Base-T in full duplex mode.
 */
#define RTL8211_BMSR_10BASE_T_FULL_MASK (0x1000U)
#define RTL8211_BMSR_10BASE_T_FULL_SHIFT (12U)
#define RTL8211_BMSR_10BASE_T_FULL_GET(x) (((uint16_t)(x) & RTL8211_BMSR_10BASE_T_FULL_MASK) >> RTL8211_BMSR_10BASE_T_FULL_SHIFT)

/*
 * 10BASE_T_HALF (RO)
 *
 * 10Base-T Half Duplex Capability.
 * 1: Device is able to perform 10Base-T in half duplex mode
 * 0: Device is not able to perform 10Base-T in half duplex mode
 */
#define RTL8211_BMSR_10BASE_T_HALF_MASK (0x800U)
#define RTL8211_BMSR_10BASE_T_HALF_SHIFT (11U)
#define RTL8211_BMSR_10BASE_T_HALF_GET(x) (((uint16_t)(x) & RTL8211_BMSR_10BASE_T_HALF_MASK) >> RTL8211_BMSR_10BASE_T_HALF_SHIFT)

/*
 * 10BASE_T2_FULL (RO)
 *
 * 10Base-T2 Full Duplex Capability.
 * The RTL8211E-VB(VL)/RTL8211EG-VB does not support
 * 10Base-T2 mode and this bit should always be 0.
 */
#define RTL8211_BMSR_10BASE_T2_FULL_MASK (0x400U)
#define RTL8211_BMSR_10BASE_T2_FULL_SHIFT (10U)
#define RTL8211_BMSR_10BASE_T2_FULL_GET(x) (((uint16_t)(x) & RTL8211_BMSR_10BASE_T2_FULL_MASK) >> RTL8211_BMSR_10BASE_T2_FULL_SHIFT)

/*
 * 10BASE_T2_HALF (RO)
 *
 * 10Base-T2 Half Duplex Capability.
 * The RTL8211E-VB(VL)/RTL8211EG-VB does not support
 * 10Base-T2 mode. This bit should always be 0.
 */
#define RTL8211_BMSR_10BASE_T2_HALF_MASK (0x200U)
#define RTL8211_BMSR_10BASE_T2_HALF_SHIFT (9U)
#define RTL8211_BMSR_10BASE_T2_HALF_GET(x) (((uint16_t)(x) & RTL8211_BMSR_10BASE_T2_HALF_MASK) >> RTL8211_BMSR_10BASE_T2_HALF_SHIFT)

/*
 * 1000BASE_T_EXTENDED_STATUS (RO)
 *
 * 1000Base-T Extended Status Register.
 * 1: Device supports Extended Status Register 0x0F (15)
 * 0: Device does not support Extended Status Register 0x0F
 * This register is read-only and is always set to 1.
 */
#define RTL8211_BMSR_1000BASE_T_EXTENDED_STATUS_MASK (0x100U)
#define RTL8211_BMSR_1000BASE_T_EXTENDED_STATUS_SHIFT (8U)
#define RTL8211_BMSR_1000BASE_T_EXTENDED_STATUS_GET(x) (((uint16_t)(x) & RTL8211_BMSR_1000BASE_T_EXTENDED_STATUS_MASK) >> RTL8211_BMSR_1000BASE_T_EXTENDED_STATUS_SHIFT)

/*
 * PREAMBLE_SUPPRESSION (RO)
 *
 * Preamble Suppression Capability (Permanently On).
 * The RTL8211E-VB(VL)/RTL8211EG-VB always accepts
 * transactions with preamble suppressed.
 */
#define RTL8211_BMSR_PREAMBLE_SUPPRESSION_MASK (0x40U)
#define RTL8211_BMSR_PREAMBLE_SUPPRESSION_SHIFT (6U)
#define RTL8211_BMSR_PREAMBLE_SUPPRESSION_GET(x) (((uint16_t)(x) & RTL8211_BMSR_PREAMBLE_SUPPRESSION_MASK) >> RTL8211_BMSR_PREAMBLE_SUPPRESSION_SHIFT)

/*
 * AUTO_NEGOTIATION_COMPLETE (RO)
 *
 * Auto-Negotiation Complete.
 * 1: Auto-Negotiation process complete, and contents of registers
 * 5, 6, 8, and 10 are valid
 * 0: Auto-Negotiation process not complete
 */
#define RTL8211_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK (0x20U)
#define RTL8211_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT (5U)
#define RTL8211_BMSR_AUTO_NEGOTIATION_COMPLETE_GET(x) (((uint16_t)(x) & RTL8211_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK) >> RTL8211_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT)

/*
 * REMOTE_FAULT (RC)
 *
 * Remote Fault.
 * 1: Remote fault condition detected (cleared on read or by reset).
 * Indication or notification of remote fault from Link Partner
 * 0: No remote fault condition detected
 */
#define RTL8211_BMSR_REMOTE_FAULT_MASK (0x10U)
#define RTL8211_BMSR_REMOTE_FAULT_SHIFT (4U)
#define RTL8211_BMSR_REMOTE_FAULT_GET(x) (((uint16_t)(x) & RTL8211_BMSR_REMOTE_FAULT_MASK) >> RTL8211_BMSR_REMOTE_FAULT_SHIFT)

/*
 * AUTO_NEGOTIATION_ABILITY (RO)
 *
 * Auto Configured Link.
 * 1: Device is able to perform Auto-Negotiation
 * 0: Device is not able to perform Auto-Negotiation
 */
#define RTL8211_BMSR_AUTO_NEGOTIATION_ABILITY_MASK (0x8U)
#define RTL8211_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT (3U)
#define RTL8211_BMSR_AUTO_NEGOTIATION_ABILITY_GET(x) (((uint16_t)(x) & RTL8211_BMSR_AUTO_NEGOTIATION_ABILITY_MASK) >> RTL8211_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT)

/*
 * LINK_STATUS (RO)
 *
 * Link Status.
 * 1: Linked
 * 0: Not Linked
 * This register indicates whether the link was lost since the last read.
 * For the current link status, either read this register twice or read
 * register bit 17.10 Link Real Time.
 */
#define RTL8211_BMSR_LINK_STATUS_MASK (0x4U)
#define RTL8211_BMSR_LINK_STATUS_SHIFT (2U)
#define RTL8211_BMSR_LINK_STATUS_GET(x) (((uint16_t)(x) & RTL8211_BMSR_LINK_STATUS_MASK) >> RTL8211_BMSR_LINK_STATUS_SHIFT)

/*
 * JABBER_DETECT (RC)
 *
 * Jabber Detect.
 * 1: Jabber condition detected
 * 0: No Jabber occurred
 */
#define RTL8211_BMSR_JABBER_DETECT_MASK (0x2U)
#define RTL8211_BMSR_JABBER_DETECT_SHIFT (1U)
#define RTL8211_BMSR_JABBER_DETECT_GET(x) (((uint16_t)(x) & RTL8211_BMSR_JABBER_DETECT_MASK) >> RTL8211_BMSR_JABBER_DETECT_SHIFT)

/*
 * EXTENDED_CAPABILITY (RO)
 *
 * 1: Extended register capabilities, always 1
 */
#define RTL8211_BMSR_EXTENDED_CAPABILITY_MASK (0x1U)
#define RTL8211_BMSR_EXTENDED_CAPABILITY_SHIFT (0U)
#define RTL8211_BMSR_EXTENDED_CAPABILITY_GET(x) (((uint16_t)(x) & RTL8211_BMSR_EXTENDED_CAPABILITY_MASK) >> RTL8211_BMSR_EXTENDED_CAPABILITY_SHIFT)

/* Bitfield definition for register: PHYID1 */
/*
 * OUI_MSB (RO)
 *
 * Organizationally Unique Identifier Bit 3:18.
 * Always 0000000000011100.
 */
#define RTL8211_PHYID1_OUI_MSB_MASK (0xFFFFU)
#define RTL8211_PHYID1_OUI_MSB_SHIFT (0U)
#define RTL8211_PHYID1_OUI_MSB_GET(x) (((uint16_t)(x) & RTL8211_PHYID1_OUI_MSB_MASK) >> RTL8211_PHYID1_OUI_MSB_SHIFT)

/* Bitfield definition for register: PHYID2 */
/*
 * OUI_LSB (RO)
 *
 * Organizationally Unique Identifier Bit 19:24.
 * Always 110010.
 */
#define RTL8211_PHYID2_OUI_LSB_MASK (0xFC00U)
#define RTL8211_PHYID2_OUI_LSB_SHIFT (10U)
#define RTL8211_PHYID2_OUI_LSB_GET(x) (((uint16_t)(x) & RTL8211_PHYID2_OUI_LSB_MASK) >> RTL8211_PHYID2_OUI_LSB_SHIFT)

/*
 * MODEL_NUMBER (RO)
 *
 * Manufacture’s Model Number
 */
#define RTL8211_PHYID2_MODEL_NUMBER_MASK (0x3F0U)
#define RTL8211_PHYID2_MODEL_NUMBER_SHIFT (4U)
#define RTL8211_PHYID2_MODEL_NUMBER_GET(x) (((uint16_t)(x) & RTL8211_PHYID2_MODEL_NUMBER_MASK) >> RTL8211_PHYID2_MODEL_NUMBER_SHIFT)

/*
 * REVISION_NUMBER (RO)
 *
 * Revision Number
 */
#define RTL8211_PHYID2_REVISION_NUMBER_MASK (0xFU)
#define RTL8211_PHYID2_REVISION_NUMBER_SHIFT (0U)
#define RTL8211_PHYID2_REVISION_NUMBER_GET(x) (((uint16_t)(x) & RTL8211_PHYID2_REVISION_NUMBER_MASK) >> RTL8211_PHYID2_REVISION_NUMBER_SHIFT)

/* Bitfield definition for register: PHYSR */
/*
 * SPEED (RO)
 *
 * Link Speed.
 * 11: Reserved  10: 1000Mbps
 * 01: 100Mbps  00: 10Mbps
 */
#define RTL8211_PHYSR_SPEED_MASK (0xC000U)
#define RTL8211_PHYSR_SPEED_SHIFT (14U)
#define RTL8211_PHYSR_SPEED_GET(x) (((uint16_t)(x) & RTL8211_PHYSR_SPEED_MASK) >> RTL8211_PHYSR_SPEED_SHIFT)

/*
 * DUPLEX (RO)
 *
 * Full/Half Duplex Mode.
 * 1: Full duplex  0: Half duplex
 */
#define RTL8211_PHYSR_DUPLEX_MASK (0x2000U)
#define RTL8211_PHYSR_DUPLEX_SHIFT (13U)
#define RTL8211_PHYSR_DUPLEX_GET(x) (((uint16_t)(x) & RTL8211_PHYSR_DUPLEX_MASK) >> RTL8211_PHYSR_DUPLEX_SHIFT)

/*
 * PAGE_RECEIVED (RC)
 *
 * New Page Received.
 * 1: Page received  0: Page not received
 */
#define RTL8211_PHYSR_PAGE_RECEIVED_MASK (0x1000U)
#define RTL8211_PHYSR_PAGE_RECEIVED_SHIFT (12U)
#define RTL8211_PHYSR_PAGE_RECEIVED_GET(x) (((uint16_t)(x) & RTL8211_PHYSR_PAGE_RECEIVED_MASK) >> RTL8211_PHYSR_PAGE_RECEIVED_SHIFT)

/*
 * SPEED_AND_DUPLEX_RESOLVED (RO)
 *
 * Speed and Duplex Mode Resolved.
 * 1: Resolved  0: Not resolved
 */
#define RTL8211_PHYSR_SPEED_AND_DUPLEX_RESOLVED_MASK (0x800U)
#define RTL8211_PHYSR_SPEED_AND_DUPLEX_RESOLVED_SHIFT (11U)
#define RTL8211_PHYSR_SPEED_AND_DUPLEX_RESOLVED_GET(x) (((uint16_t)(x) & RTL8211_PHYSR_SPEED_AND_DUPLEX_RESOLVED_MASK) >> RTL8211_PHYSR_SPEED_AND_DUPLEX_RESOLVED_SHIFT)

/*
 * LINK_REAL_TIME (RO)
 *
 * Real Time Link Status.
 * 1: Link OK  0: Link not OK
 */
#define RTL8211_PHYSR_LINK_REAL_TIME_MASK (0x400U)
#define RTL8211_PHYSR_LINK_REAL_TIME_SHIFT (10U)
#define RTL8211_PHYSR_LINK_REAL_TIME_GET(x) (((uint16_t)(x) & RTL8211_PHYSR_LINK_REAL_TIME_MASK) >> RTL8211_PHYSR_LINK_REAL_TIME_SHIFT)

/*
 * MDI_CROSSOVER_STATUS (RO)
 *
 * MDI/MDI Crossover Status.
 * 1: MDI Crossover  0: MDI
 */
#define RTL8211_PHYSR_MDI_CROSSOVER_STATUS_MASK (0x40U)
#define RTL8211_PHYSR_MDI_CROSSOVER_STATUS_SHIFT (6U)
#define RTL8211_PHYSR_MDI_CROSSOVER_STATUS_GET(x) (((uint16_t)(x) & RTL8211_PHYSR_MDI_CROSSOVER_STATUS_MASK) >> RTL8211_PHYSR_MDI_CROSSOVER_STATUS_SHIFT)

/*
 * PRE_LINKOK (RO)
 *
 * Reflects Local Receiver is OK.
 * 0: Receiver is not OK
 * 1: Receiver is OK
 */
#define RTL8211_PHYSR_PRE_LINKOK_MASK (0x2U)
#define RTL8211_PHYSR_PRE_LINKOK_SHIFT (1U)
#define RTL8211_PHYSR_PRE_LINKOK_GET(x) (((uint16_t)(x) & RTL8211_PHYSR_PRE_LINKOK_MASK) >> RTL8211_PHYSR_PRE_LINKOK_SHIFT)

/*
 * JABBER_REAL_TIME (RO)
 *
 * Real Time Jabber Indication.
 * 1: Jabber Indication  0: No jabber Indication
 */
#define RTL8211_PHYSR_JABBER_REAL_TIME_MASK (0x1U)
#define RTL8211_PHYSR_JABBER_REAL_TIME_SHIFT (0U)
#define RTL8211_PHYSR_JABBER_REAL_TIME_GET(x) (((uint16_t)(x) & RTL8211_PHYSR_JABBER_REAL_TIME_MASK) >> RTL8211_PHYSR_JABBER_REAL_TIME_SHIFT)




#endif /* HPM_RTL8211_REGS_H */
