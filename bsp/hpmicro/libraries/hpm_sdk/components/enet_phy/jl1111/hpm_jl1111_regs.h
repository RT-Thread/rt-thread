/*
 * Copyright (c) 2021-2024 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_JL1111_REGS_H
#define HPM_JL1111_REGS_H

typedef enum {
    JL1111_BMCR                         = 0,   /* 0x0: Basic Mode Control Register */
    JL1111_BMSR                         = 1,   /* 0x1: Basic Mode Status Register */
    JL1111_PHYID1                       = 2,   /* 0x2: PHY Identifier Register 1 */
    JL1111_PHYID2                       = 3,   /* 0x3: PHY Identifier Register 2 */
    JL1111_ANAR                         = 4,   /* 0x4: Auto-Negotiation Advertisement Register */
    JL1111_ANLPAR                       = 5,   /* 0x5: Auto-Negotiation Link Partner Ability Register */
    JL1111_MMDAC                        = 19,  /* 0x13: MMD Access Control Register */
    JL1111_MMDAAD                       = 20,  /* 0x14: MMD Access Address Data Register */
    JL1111_RMSR_P7                      = 22,  /* 0x16: RMII Mode Setting Register */
    JL1111_INTSQI                       = 48,  /* 0x30: Interrupt Indicators and Signal Quality Indicator Register */
    JL1111_PAGESEL                      = 49,  /* 0x31: Page Select Register */
} JL1111_REG_Type;


/* Bitfield definition for register: BMCR */
/*
 * RESET (RW/SC)
 *
 * 1: PHY reset
 * 0: normal operation
 * After software reset, need to delay 10ms de-assert time for chip steady.
 */
#define JL1111_BMCR_RESET_MASK (0x8000U)
#define JL1111_BMCR_RESET_SHIFT (15U)
#define JL1111_BMCR_RESET_SET(x) (((uint16_t)(x) << JL1111_BMCR_RESET_SHIFT) & JL1111_BMCR_RESET_MASK)
#define JL1111_BMCR_RESET_GET(x) (((uint16_t)(x) & JL1111_BMCR_RESET_MASK) >> JL1111_BMCR_RESET_SHIFT)

/*
 * LOOPBACK (RW)
 *
 * This bit enables loopback of transmit data nibbles TXD3:0 to the
 * receive data path.
 * 1: Enable loopback  0: Normal operation
 */
#define JL1111_BMCR_LOOPBACK_MASK (0x4000U)
#define JL1111_BMCR_LOOPBACK_SHIFT (14U)
#define JL1111_BMCR_LOOPBACK_SET(x) (((uint16_t)(x) << JL1111_BMCR_LOOPBACK_SHIFT) & JL1111_BMCR_LOOPBACK_MASK)
#define JL1111_BMCR_LOOPBACK_GET(x) (((uint16_t)(x) & JL1111_BMCR_LOOPBACK_MASK) >> JL1111_BMCR_LOOPBACK_SHIFT)

/*
 * SPEED0 (RW)
 *
 * This bit sets the network speed.
 * 1: 100Mbps  0: 10Mbps
 */
#define JL1111_BMCR_SPEED0_MASK (0x2000U)
#define JL1111_BMCR_SPEED0_SHIFT (13U)
#define JL1111_BMCR_SPEED0_SET(x) (((uint16_t)(x) << JL1111_BMCR_SPEED0_SHIFT) & JL1111_BMCR_SPEED0_MASK)
#define JL1111_BMCR_SPEED0_GET(x) (((uint16_t)(x) & JL1111_BMCR_SPEED0_MASK) >> JL1111_BMCR_SPEED0_SHIFT)

/*
 * ANE (RW)
 *
 * This bit enables/disables the NWay auto-negotiation function.
 * 1: Enable auto-negotiation; bits 0:13 and 0:8 will be ignored
 * 0: Disable auto-negotiation; bits 0:13 and 0:8 will determine the
 * link speed and the data transfer mode
 */
#define JL1111_BMCR_ANE_MASK (0x1000U)
#define JL1111_BMCR_ANE_SHIFT (12U)
#define JL1111_BMCR_ANE_SET(x) (((uint16_t)(x) << JL1111_BMCR_ANE_SHIFT) & JL1111_BMCR_ANE_MASK)
#define JL1111_BMCR_ANE_GET(x) (((uint16_t)(x) & JL1111_BMCR_ANE_MASK) >> JL1111_BMCR_ANE_SHIFT)

/*
 * PWD (RW)
 *
 * This bit turns down the power of the PHY chip
 * The MDC, MDIO is still alive for accessing the MAC.
 * 1: Power down  0: Normal operation
 */
#define JL1111_BMCR_PWD_MASK (0x800U)
#define JL1111_BMCR_PWD_SHIFT (11U)
#define JL1111_BMCR_PWD_SET(x) (((uint16_t)(x) << JL1111_BMCR_PWD_SHIFT) & JL1111_BMCR_PWD_MASK)
#define JL1111_BMCR_PWD_GET(x) (((uint16_t)(x) & JL1111_BMCR_PWD_MASK) >> JL1111_BMCR_PWD_SHIFT)

/*
 * ISOLATE (RW)
 *
 * 1: Electrically isolate the PHY from MII/RMII
 * PHY is still able to respond to MDC/MDIO.
 * 0: Normal operation
 */
#define JL1111_BMCR_ISOLATE_MASK (0x400U)
#define JL1111_BMCR_ISOLATE_SHIFT (10U)
#define JL1111_BMCR_ISOLATE_SET(x) (((uint16_t)(x) << JL1111_BMCR_ISOLATE_SHIFT) & JL1111_BMCR_ISOLATE_MASK)
#define JL1111_BMCR_ISOLATE_GET(x) (((uint16_t)(x) & JL1111_BMCR_ISOLATE_MASK) >> JL1111_BMCR_ISOLATE_SHIFT)

/*
 * RESTART_AN (RW/SC)
 *
 * This bit allows the NWay auto-negotiation function to be reset.
 * 1: Re-start auto-negotiation  0: Normal operation
 */
#define JL1111_BMCR_RESTART_AN_MASK (0x200U)
#define JL1111_BMCR_RESTART_AN_SHIFT (9U)
#define JL1111_BMCR_RESTART_AN_SET(x) (((uint16_t)(x) << JL1111_BMCR_RESTART_AN_SHIFT) & JL1111_BMCR_RESTART_AN_MASK)
#define JL1111_BMCR_RESTART_AN_GET(x) (((uint16_t)(x) & JL1111_BMCR_RESTART_AN_MASK) >> JL1111_BMCR_RESTART_AN_SHIFT)

/*
 * DUPLEX (RW)
 *
 * This bit sets the duplex mode if auto-negotiation is disabled (bit
 * 0:12=0).
 * 1: Full duplex  0: Half duplex
 */
#define JL1111_BMCR_DUPLEX_MASK (0x100U)
#define JL1111_BMCR_DUPLEX_SHIFT (8U)
#define JL1111_BMCR_DUPLEX_SET(x) (((uint16_t)(x) << JL1111_BMCR_DUPLEX_SHIFT) & JL1111_BMCR_DUPLEX_MASK)
#define JL1111_BMCR_DUPLEX_GET(x) (((uint16_t)(x) & JL1111_BMCR_DUPLEX_MASK) >> JL1111_BMCR_DUPLEX_SHIFT)

/*
 * COLLISION_TEST (RW)
 *
 * Collision Test.
 * 1: Collision test enabled
 * 0: Normal operation
 * When set, this bit will cause the COL signal to be asserted in
 * response to the TXEN assertion within 512-bit times. The COL
 * signal will be de-asserted within 4-bit times in response to the
 * TXEN de-assertion.
 */
#define JL1111_BMCR_COLLISION_TEST_MASK (0x80U)
#define JL1111_BMCR_COLLISION_TEST_SHIFT (7U)
#define JL1111_BMCR_COLLISION_TEST_SET(x) (((uint16_t)(x) << JL1111_BMCR_COLLISION_TEST_SHIFT) & JL1111_BMCR_COLLISION_TEST_MASK)
#define JL1111_BMCR_COLLISION_TEST_GET(x) (((uint16_t)(x) & JL1111_BMCR_COLLISION_TEST_MASK) >> JL1111_BMCR_COLLISION_TEST_SHIFT)

/*
 * SPEED1 (RW)
 *
 * Speed Select Bit 1.
 * Refer to bit 13.
 */
#define JL1111_BMCR_SPEED1_MASK (0x40U)
#define JL1111_BMCR_SPEED1_SHIFT (6U)
#define JL1111_BMCR_SPEED1_SET(x) (((uint16_t)(x) << JL1111_BMCR_SPEED1_SHIFT) & JL1111_BMCR_SPEED1_MASK)
#define JL1111_BMCR_SPEED1_GET(x) (((uint16_t)(x) & JL1111_BMCR_SPEED1_MASK) >> JL1111_BMCR_SPEED1_SHIFT)

/* Bitfield definition for register: BMSR */
/*
 * BASE100_T4_1 (RO)
 *
 * 1: Enable 100Base-T4 support
 * 0: Suppress 100Base-T4 support
 */
#define JL1111_BMSR_BASE100_T4_1_MASK (0x8000U)
#define JL1111_BMSR_BASE100_T4_1_SHIFT (15U)
#define JL1111_BMSR_BASE100_T4_1_GET(x) (((uint16_t)(x) & JL1111_BMSR_BASE100_T4_1_MASK) >> JL1111_BMSR_BASE100_T4_1_SHIFT)

/*
 * BASE100_TX_FD_1 (RO)
 *
 * 1: Enable 100Base-TX full duplex support
 * 0: Suppress 100Base-TX full duplex support
 */
#define JL1111_BMSR_BASE100_TX_FD_1_MASK (0x4000U)
#define JL1111_BMSR_BASE100_TX_FD_1_SHIFT (14U)
#define JL1111_BMSR_BASE100_TX_FD_1_GET(x) (((uint16_t)(x) & JL1111_BMSR_BASE100_TX_FD_1_MASK) >> JL1111_BMSR_BASE100_TX_FD_1_SHIFT)

/*
 * BASE100_TX_HD_1 (RO)
 *
 * 1: Enable 100Base-TX half duplex support
 * 0: Suppress 100Base-TX half duplex support
 */
#define JL1111_BMSR_BASE100_TX_HD_1_MASK (0x2000U)
#define JL1111_BMSR_BASE100_TX_HD_1_SHIFT (13U)
#define JL1111_BMSR_BASE100_TX_HD_1_GET(x) (((uint16_t)(x) & JL1111_BMSR_BASE100_TX_HD_1_MASK) >> JL1111_BMSR_BASE100_TX_HD_1_SHIFT)

/*
 * BASE10_TX_FD (RO)
 *
 * 1: Enable 10Base-T full duplex support
 * 0: Suppress 10Base-T full duplex support
 */
#define JL1111_BMSR_BASE10_TX_FD_MASK (0x1000U)
#define JL1111_BMSR_BASE10_TX_FD_SHIFT (12U)
#define JL1111_BMSR_BASE10_TX_FD_GET(x) (((uint16_t)(x) & JL1111_BMSR_BASE10_TX_FD_MASK) >> JL1111_BMSR_BASE10_TX_FD_SHIFT)

/*
 * BASE10_TX_HD (RO)
 *
 * 1: Enable 10Base-T half duplex support
 * 0: Suppress 10Base-T half duplex support
 */
#define JL1111_BMSR_BASE10_TX_HD_MASK (0x800U)
#define JL1111_BMSR_BASE10_TX_HD_SHIFT (11U)
#define JL1111_BMSR_BASE10_TX_HD_GET(x) (((uint16_t)(x) & JL1111_BMSR_BASE10_TX_HD_MASK) >> JL1111_BMSR_BASE10_TX_HD_SHIFT)

/*
 * MDIO_MFPS (RO)
 *
 */
#define JL1111_BMSR_MDIO_MFPS_MASK (0x40U)
#define JL1111_BMSR_MDIO_MFPS_SHIFT (6U)
#define JL1111_BMSR_MDIO_MFPS_GET(x) (((uint16_t)(x) & JL1111_BMSR_MDIO_MFPS_MASK) >> JL1111_BMSR_MDIO_MFPS_SHIFT)

/*
 * AUTO_NEGOTIATION_COMPLETE (RO)
 *
 * 1: Auto-negotiation process completed
 * 0: Auto-negotiation process not completed
 */
#define JL1111_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK (0x20U)
#define JL1111_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT (5U)
#define JL1111_BMSR_AUTO_NEGOTIATION_COMPLETE_GET(x) (((uint16_t)(x) & JL1111_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK) >> JL1111_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT)

/*
 * REMOTE_FAULT (RC)
 *
 * 1: Remote fault condition detected (cleared on read)
 * 0: No remote fault condition detected
 */
#define JL1111_BMSR_REMOTE_FAULT_MASK (0x10U)
#define JL1111_BMSR_REMOTE_FAULT_SHIFT (4U)
#define JL1111_BMSR_REMOTE_FAULT_GET(x) (((uint16_t)(x) & JL1111_BMSR_REMOTE_FAULT_MASK) >> JL1111_BMSR_REMOTE_FAULT_SHIFT)

/*
 * AUTO_NEGOTIATION_ABILITY (RO)
 *
 * 1: PHY is able to perform auto-negotiation
 * 0: PHY is not able to perform auto-negotiation
 */
#define JL1111_BMSR_AUTO_NEGOTIATION_ABILITY_MASK (0x8U)
#define JL1111_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT (3U)
#define JL1111_BMSR_AUTO_NEGOTIATION_ABILITY_GET(x) (((uint16_t)(x) & JL1111_BMSR_AUTO_NEGOTIATION_ABILITY_MASK) >> JL1111_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT)

/*
 * LINK_STATUS (RO)
 *
 * 1: Valid link established
 * 0: No valid link established
 */
#define JL1111_BMSR_LINK_STATUS_MASK (0x4U)
#define JL1111_BMSR_LINK_STATUS_SHIFT (2U)
#define JL1111_BMSR_LINK_STATUS_GET(x) (((uint16_t)(x) & JL1111_BMSR_LINK_STATUS_MASK) >> JL1111_BMSR_LINK_STATUS_SHIFT)

/*
 * JABBER_DETECT (RO)
 *
 * 1: Jabber condition detected
 * 0: No jabber condition detected
 */
#define JL1111_BMSR_JABBER_DETECT_MASK (0x2U)
#define JL1111_BMSR_JABBER_DETECT_SHIFT (1U)
#define JL1111_BMSR_JABBER_DETECT_GET(x) (((uint16_t)(x) & JL1111_BMSR_JABBER_DETECT_MASK) >> JL1111_BMSR_JABBER_DETECT_SHIFT)

/*
 * EXTENDED_CAPABILITY (RO)
 *
 * 1: Extended register capable (permanently=1)
 * 0: Not extended register capable
 */
#define JL1111_BMSR_EXTENDED_CAPABILITY_MASK (0x1U)
#define JL1111_BMSR_EXTENDED_CAPABILITY_SHIFT (0U)
#define JL1111_BMSR_EXTENDED_CAPABILITY_GET(x) (((uint16_t)(x) & JL1111_BMSR_EXTENDED_CAPABILITY_MASK) >> JL1111_BMSR_EXTENDED_CAPABILITY_SHIFT)

/* Bitfield definition for register: PHYID1 */
/*
 * OUI_MSB (RO)
 *
 * JLSemi OUI is 0x24DF10
 * 0010 0100 1101 1111 0001 0000
 * BIT1.......................................................BIT24
 * Register 2.[15:0] show bit3 to 18 of OUI
 * 1001 0011 0111 1100
 * BIT3................................BIT18
 */
#define JL1111_PHYID1_OUI_MSB_MASK (0xFFFFU)
#define JL1111_PHYID1_OUI_MSB_SHIFT (0U)
#define JL1111_PHYID1_OUI_MSB_GET(x) (((uint16_t)(x) & JL1111_PHYID1_OUI_MSB_MASK) >> JL1111_PHYID1_OUI_MSB_SHIFT)

/* Bitfield definition for register: PHYID2 */
/*
 * OUI_LSB (RO)
 *
 * Organizationally Unique Identifier bits 19:24
 * 01 0000
 * bit19....bit24
 */
#define JL1111_PHYID2_OUI_LSB_MASK (0xFC00U)
#define JL1111_PHYID2_OUI_LSB_SHIFT (10U)
#define JL1111_PHYID2_OUI_LSB_GET(x) (((uint16_t)(x) & JL1111_PHYID2_OUI_LSB_MASK) >> JL1111_PHYID2_OUI_LSB_SHIFT)

/*
 * MODEL_NUMBER (RO)
 *
 * Model Number
 */
#define JL1111_PHYID2_MODEL_NUMBER_MASK (0x3F0U)
#define JL1111_PHYID2_MODEL_NUMBER_SHIFT (4U)
#define JL1111_PHYID2_MODEL_NUMBER_GET(x) (((uint16_t)(x) & JL1111_PHYID2_MODEL_NUMBER_MASK) >> JL1111_PHYID2_MODEL_NUMBER_SHIFT)

/*
 * REVISION_NUMBER (RO)
 *
 * Contact JLSemi FAEs for information on the device revision number
 */
#define JL1111_PHYID2_REVISION_NUMBER_MASK (0xFU)
#define JL1111_PHYID2_REVISION_NUMBER_SHIFT (0U)
#define JL1111_PHYID2_REVISION_NUMBER_GET(x) (((uint16_t)(x) & JL1111_PHYID2_REVISION_NUMBER_MASK) >> JL1111_PHYID2_REVISION_NUMBER_SHIFT)

/* Bitfield definition for register: ANAR */
/*
 * NEXT_PAGE (RW)
 *
 * Next Page Bit.
 * 0: Transmitting the primary capability data page
 * 1: Transmitting the protocol specific data page
 */
#define JL1111_ANAR_NEXT_PAGE_MASK (0x8000U)
#define JL1111_ANAR_NEXT_PAGE_SHIFT (15U)
#define JL1111_ANAR_NEXT_PAGE_SET(x) (((uint16_t)(x) << JL1111_ANAR_NEXT_PAGE_SHIFT) & JL1111_ANAR_NEXT_PAGE_MASK)
#define JL1111_ANAR_NEXT_PAGE_GET(x) (((uint16_t)(x) & JL1111_ANAR_NEXT_PAGE_MASK) >> JL1111_ANAR_NEXT_PAGE_SHIFT)

/*
 * ACKNOWLEDGE (RO)
 *
 * 1: Acknowledge reception of link partner capability data world
 * 0: Do not acknowledge reception
 */
#define JL1111_ANAR_ACKNOWLEDGE_MASK (0x4000U)
#define JL1111_ANAR_ACKNOWLEDGE_SHIFT (14U)
#define JL1111_ANAR_ACKNOWLEDGE_GET(x) (((uint16_t)(x) & JL1111_ANAR_ACKNOWLEDGE_MASK) >> JL1111_ANAR_ACKNOWLEDGE_SHIFT)

/*
 * REMOTE_FAULT (RO)
 *
 * 1: Advertise remote fault detection capability
 * 0: Do not advertise remote fault detection capability
 */
#define JL1111_ANAR_REMOTE_FAULT_MASK (0x2000U)
#define JL1111_ANAR_REMOTE_FAULT_SHIFT (13U)
#define JL1111_ANAR_REMOTE_FAULT_GET(x) (((uint16_t)(x) & JL1111_ANAR_REMOTE_FAULT_MASK) >> JL1111_ANAR_REMOTE_FAULT_SHIFT)

/*
 * ASYMMETRIC_PAUSE (RW)
 *
 * Asymmetric Pause Support For Full-Duplex Links
 * 1: Advertise asymmetric pause ability
 * 0: Do not advertise asymmetric pause ability
 */
#define JL1111_ANAR_ASYMMETRIC_PAUSE_MASK (0x800U)
#define JL1111_ANAR_ASYMMETRIC_PAUSE_SHIFT (11U)
#define JL1111_ANAR_ASYMMETRIC_PAUSE_SET(x) (((uint16_t)(x) << JL1111_ANAR_ASYMMETRIC_PAUSE_SHIFT) & JL1111_ANAR_ASYMMETRIC_PAUSE_MASK)
#define JL1111_ANAR_ASYMMETRIC_PAUSE_GET(x) (((uint16_t)(x) & JL1111_ANAR_ASYMMETRIC_PAUSE_MASK) >> JL1111_ANAR_ASYMMETRIC_PAUSE_SHIFT)

/*
 * PAUSE (RW)
 *
 * Pause Support For Full-Duplex Links
 * 1: Advertise pause ability
 * 0: Do not advertise pause ability
 */
#define JL1111_ANAR_PAUSE_MASK (0x400U)
#define JL1111_ANAR_PAUSE_SHIFT (10U)
#define JL1111_ANAR_PAUSE_SET(x) (((uint16_t)(x) << JL1111_ANAR_PAUSE_SHIFT) & JL1111_ANAR_PAUSE_MASK)
#define JL1111_ANAR_PAUSE_GET(x) (((uint16_t)(x) & JL1111_ANAR_PAUSE_MASK) >> JL1111_ANAR_PAUSE_SHIFT)

/*
 * 100BASE_T4 (RO)
 *
 * 1: 100Base-T4 is supported by local node
 * 0: 100Base-T4 not supported by local node
 */
#define JL1111_ANAR_100BASE_T4_MASK (0x200U)
#define JL1111_ANAR_100BASE_T4_SHIFT (9U)
#define JL1111_ANAR_100BASE_T4_GET(x) (((uint16_t)(x) & JL1111_ANAR_100BASE_T4_MASK) >> JL1111_ANAR_100BASE_T4_SHIFT)

/*
 * 100BASE_TX_FD (RW)
 *
 * 1: 100Base-TX full duplex is supported by local node
 * 0: 100Base-TX full duplex not supported by local node
 */
#define JL1111_ANAR_100BASE_TX_FD_MASK (0x100U)
#define JL1111_ANAR_100BASE_TX_FD_SHIFT (8U)
#define JL1111_ANAR_100BASE_TX_FD_SET(x) (((uint16_t)(x) << JL1111_ANAR_100BASE_TX_FD_SHIFT) & JL1111_ANAR_100BASE_TX_FD_MASK)
#define JL1111_ANAR_100BASE_TX_FD_GET(x) (((uint16_t)(x) & JL1111_ANAR_100BASE_TX_FD_MASK) >> JL1111_ANAR_100BASE_TX_FD_SHIFT)

/*
 * 100BASE_TX (RW)
 *
 * 1: 100Base-TX is supported by local node
 * 0: 100Base-TX not supported by local node
 */
#define JL1111_ANAR_100BASE_TX_MASK (0x80U)
#define JL1111_ANAR_100BASE_TX_SHIFT (7U)
#define JL1111_ANAR_100BASE_TX_SET(x) (((uint16_t)(x) << JL1111_ANAR_100BASE_TX_SHIFT) & JL1111_ANAR_100BASE_TX_MASK)
#define JL1111_ANAR_100BASE_TX_GET(x) (((uint16_t)(x) & JL1111_ANAR_100BASE_TX_MASK) >> JL1111_ANAR_100BASE_TX_SHIFT)

/*
 * 10BASE_T_FD (RW)
 *
 * 1: 10Base-T full duplex supported by local node
 * 0: 10Base-T full duplex not supported by local node
 */
#define JL1111_ANAR_10BASE_T_FD_MASK (0x40U)
#define JL1111_ANAR_10BASE_T_FD_SHIFT (6U)
#define JL1111_ANAR_10BASE_T_FD_SET(x) (((uint16_t)(x) << JL1111_ANAR_10BASE_T_FD_SHIFT) & JL1111_ANAR_10BASE_T_FD_MASK)
#define JL1111_ANAR_10BASE_T_FD_GET(x) (((uint16_t)(x) & JL1111_ANAR_10BASE_T_FD_MASK) >> JL1111_ANAR_10BASE_T_FD_SHIFT)

/*
 * 10BASE_T (RW)
 *
 * 1: 10Base-T is supported by local node
 * 0: 10Base-T not supported by local node
 */
#define JL1111_ANAR_10BASE_T_MASK (0x20U)
#define JL1111_ANAR_10BASE_T_SHIFT (5U)
#define JL1111_ANAR_10BASE_T_SET(x) (((uint16_t)(x) << JL1111_ANAR_10BASE_T_SHIFT) & JL1111_ANAR_10BASE_T_MASK)
#define JL1111_ANAR_10BASE_T_GET(x) (((uint16_t)(x) & JL1111_ANAR_10BASE_T_MASK) >> JL1111_ANAR_10BASE_T_SHIFT)

/*
 * SELECTOR_FIELD (RO)
 *
 * Binary Encoded Selector Supported by This Node. Currently only CSMA/CD 00001 is specified. No other protocols are supported.
 */
#define JL1111_ANAR_SELECTOR_FIELD_MASK (0x1FU)
#define JL1111_ANAR_SELECTOR_FIELD_SHIFT (0U)
#define JL1111_ANAR_SELECTOR_FIELD_GET(x) (((uint16_t)(x) & JL1111_ANAR_SELECTOR_FIELD_MASK) >> JL1111_ANAR_SELECTOR_FIELD_SHIFT)

/* Bitfield definition for register: ANLPAR */
/*
 * NEXT_PAGE (RO)
 *
 * Next Page Bit.
 * 0: Transmitting the primary capability data page
 * 1: Transmitting the protocol specific data page
 */
#define JL1111_ANLPAR_NEXT_PAGE_MASK (0x8000U)
#define JL1111_ANLPAR_NEXT_PAGE_SHIFT (15U)
#define JL1111_ANLPAR_NEXT_PAGE_GET(x) (((uint16_t)(x) & JL1111_ANLPAR_NEXT_PAGE_MASK) >> JL1111_ANLPAR_NEXT_PAGE_SHIFT)

/*
 * ACKNOWLEDGE (RO)
 *
 * 1: Link partner acknowledges reception of local node's capability data word
 * 0: No acknowledgement
 */
#define JL1111_ANLPAR_ACKNOWLEDGE_MASK (0x4000U)
#define JL1111_ANLPAR_ACKNOWLEDGE_SHIFT (14U)
#define JL1111_ANLPAR_ACKNOWLEDGE_GET(x) (((uint16_t)(x) & JL1111_ANLPAR_ACKNOWLEDGE_MASK) >> JL1111_ANLPAR_ACKNOWLEDGE_SHIFT)

/*
 * REMOTE_FAULT (RO)
 *
 * 1: Link partner is indicating a remote fault
 * 0: Link partner is not indicating a remote fault
 */
#define JL1111_ANLPAR_REMOTE_FAULT_MASK (0x2000U)
#define JL1111_ANLPAR_REMOTE_FAULT_SHIFT (13U)
#define JL1111_ANLPAR_REMOTE_FAULT_GET(x) (((uint16_t)(x) & JL1111_ANLPAR_REMOTE_FAULT_MASK) >> JL1111_ANLPAR_REMOTE_FAULT_SHIFT)

/*
 * ASYMMETRIC_PAUSE (RO)
 *
 * Asymmetric Pause Support For Full-Duplex Links
 * 1: Advertise asymmetric pause ability
 * 0: Do not advertise asymmetric puase ability
 */
#define JL1111_ANLPAR_ASYMMETRIC_PAUSE_MASK (0x800U)
#define JL1111_ANLPAR_ASYMMETRIC_PAUSE_SHIFT (11U)
#define JL1111_ANLPAR_ASYMMETRIC_PAUSE_GET(x) (((uint16_t)(x) & JL1111_ANLPAR_ASYMMETRIC_PAUSE_MASK) >> JL1111_ANLPAR_ASYMMETRIC_PAUSE_SHIFT)

/*
 * PAUSE (RO)
 *
 * Pause Support For Full-Duplex Links
 * 1: Advertise pause ability
 * 0: Do not advertise pause ability
 */
#define JL1111_ANLPAR_PAUSE_MASK (0x400U)
#define JL1111_ANLPAR_PAUSE_SHIFT (10U)
#define JL1111_ANLPAR_PAUSE_GET(x) (((uint16_t)(x) & JL1111_ANLPAR_PAUSE_MASK) >> JL1111_ANLPAR_PAUSE_SHIFT)

/*
 * 100BASE_T4 (RO)
 *
 * 1: 100Base-T4 is supported by link partner
 * 0: 100Base-T4 not supported by link partner
 */
#define JL1111_ANLPAR_100BASE_T4_MASK (0x200U)
#define JL1111_ANLPAR_100BASE_T4_SHIFT (9U)
#define JL1111_ANLPAR_100BASE_T4_GET(x) (((uint16_t)(x) & JL1111_ANLPAR_100BASE_T4_MASK) >> JL1111_ANLPAR_100BASE_T4_SHIFT)

/*
 * 100BASE_TX_FD (RO)
 *
 * 1: 100Base-TX full duplex is supported by link partner
 * 0: 100Base-TX full duplex not supported by link partner
 */
#define JL1111_ANLPAR_100BASE_TX_FD_MASK (0x100U)
#define JL1111_ANLPAR_100BASE_TX_FD_SHIFT (8U)
#define JL1111_ANLPAR_100BASE_TX_FD_GET(x) (((uint16_t)(x) & JL1111_ANLPAR_100BASE_TX_FD_MASK) >> JL1111_ANLPAR_100BASE_TX_FD_SHIFT)

/*
 * 100BASE_TX (RO)
 *
 * 1: 100Base-TX is supported by link partner
 * 0: 100Base-TX not supported by link partner
 */
#define JL1111_ANLPAR_100BASE_TX_MASK (0x80U)
#define JL1111_ANLPAR_100BASE_TX_SHIFT (7U)
#define JL1111_ANLPAR_100BASE_TX_GET(x) (((uint16_t)(x) & JL1111_ANLPAR_100BASE_TX_MASK) >> JL1111_ANLPAR_100BASE_TX_SHIFT)

/*
 * 10BASE_T_FD (RO)
 *
 * 1: 10Base-T full duplex is supported by link partner
 * 0: 10Base-T full duplex not supported by link partner
 */
#define JL1111_ANLPAR_10BASE_T_FD_MASK (0x40U)
#define JL1111_ANLPAR_10BASE_T_FD_SHIFT (6U)
#define JL1111_ANLPAR_10BASE_T_FD_GET(x) (((uint16_t)(x) & JL1111_ANLPAR_10BASE_T_FD_MASK) >> JL1111_ANLPAR_10BASE_T_FD_SHIFT)

/*
 * 10BASE_T (RO)
 *
 * 1: 10Base-T is supported by link partner
 * 0: 10Base-T not supported by link partner
 */
#define JL1111_ANLPAR_10BASE_T_MASK (0x20U)
#define JL1111_ANLPAR_10BASE_T_SHIFT (5U)
#define JL1111_ANLPAR_10BASE_T_GET(x) (((uint16_t)(x) & JL1111_ANLPAR_10BASE_T_MASK) >> JL1111_ANLPAR_10BASE_T_SHIFT)

/*
 * SELECTOR_FIELD (RO)
 *
 * Link Partner's Binary Encoded Node Selector.
 * Currently only CSMA/CD 00001 is specified.
 */
#define JL1111_ANLPAR_SELECTOR_FIELD_MASK (0x1FU)
#define JL1111_ANLPAR_SELECTOR_FIELD_SHIFT (0U)
#define JL1111_ANLPAR_SELECTOR_FIELD_GET(x) (((uint16_t)(x) & JL1111_ANLPAR_SELECTOR_FIELD_MASK) >> JL1111_ANLPAR_SELECTOR_FIELD_SHIFT)

/* Bitfield definition for register: MMDAC */
/*
 * MMD_FUNCTION (RW)
 *
 * 00: address
 * 01: data, no post increment
 * 10: data, post increment on reads and writes
 * 11: data, post increment on writes only
 */
#define JL1111_MMDAC_MMD_FUNCTION_MASK (0xC000U)
#define JL1111_MMDAC_MMD_FUNCTION_SHIFT (14U)
#define JL1111_MMDAC_MMD_FUNCTION_SET(x) (((uint16_t)(x) << JL1111_MMDAC_MMD_FUNCTION_SHIFT) & JL1111_MMDAC_MMD_FUNCTION_MASK)
#define JL1111_MMDAC_MMD_FUNCTION_GET(x) (((uint16_t)(x) & JL1111_MMDAC_MMD_FUNCTION_MASK) >> JL1111_MMDAC_MMD_FUNCTION_SHIFT)

/*
 * RESERVERD (RW)
 *
 * Write as 0, ignore on read
 */
#define JL1111_MMDAC_RESERVERD_MASK (0x3FE0U)
#define JL1111_MMDAC_RESERVERD_SHIFT (5U)
#define JL1111_MMDAC_RESERVERD_SET(x) (((uint16_t)(x) << JL1111_MMDAC_RESERVERD_SHIFT) & JL1111_MMDAC_RESERVERD_MASK)
#define JL1111_MMDAC_RESERVERD_GET(x) (((uint16_t)(x) & JL1111_MMDAC_RESERVERD_MASK) >> JL1111_MMDAC_RESERVERD_SHIFT)

/*
 * MMD_DEVAD (RW)
 *
 * Device address
 */
#define JL1111_MMDAC_MMD_DEVAD_MASK (0x1FU)
#define JL1111_MMDAC_MMD_DEVAD_SHIFT (0U)
#define JL1111_MMDAC_MMD_DEVAD_SET(x) (((uint16_t)(x) << JL1111_MMDAC_MMD_DEVAD_SHIFT) & JL1111_MMDAC_MMD_DEVAD_MASK)
#define JL1111_MMDAC_MMD_DEVAD_GET(x) (((uint16_t)(x) & JL1111_MMDAC_MMD_DEVAD_MASK) >> JL1111_MMDAC_MMD_DEVAD_SHIFT)

/* Bitfield definition for register: MMDAAD */
/*
 * MMD_ADDRESS_DATA (RW)
 *
 * If MMDAC[15:14]=00, MMD DEVAD's address register. Otherwise, MMD DEVAD's data register as indicated by the contents of its address register
 */
#define JL1111_MMDAAD_MMD_ADDRESS_DATA_MASK (0xFFFFU)
#define JL1111_MMDAAD_MMD_ADDRESS_DATA_SHIFT (0U)
#define JL1111_MMDAAD_MMD_ADDRESS_DATA_SET(x) (((uint16_t)(x) << JL1111_MMDAAD_MMD_ADDRESS_DATA_SHIFT) & JL1111_MMDAAD_MMD_ADDRESS_DATA_MASK)
#define JL1111_MMDAAD_MMD_ADDRESS_DATA_GET(x) (((uint16_t)(x) & JL1111_MMDAAD_MMD_ADDRESS_DATA_MASK) >> JL1111_MMDAAD_MMD_ADDRESS_DATA_SHIFT)

/* Bitfield definition for register: RMSR_P7 */
/*
 * RMII_TX_LPI_ENABLE (RW)
 *
 * Enable transmition LPI signal of RMII
 * TX_EN=0 and TXD=1 will represent MII LPI
 */
#define JL1111_RMSR_P7_RMII_TX_LPI_ENABLE_MASK (0x8000U)
#define JL1111_RMSR_P7_RMII_TX_LPI_ENABLE_SHIFT (15U)
#define JL1111_RMSR_P7_RMII_TX_LPI_ENABLE_SET(x) (((uint16_t)(x) << JL1111_RMSR_P7_RMII_TX_LPI_ENABLE_SHIFT) & JL1111_RMSR_P7_RMII_TX_LPI_ENABLE_MASK)
#define JL1111_RMSR_P7_RMII_TX_LPI_ENABLE_GET(x) (((uint16_t)(x) & JL1111_RMSR_P7_RMII_TX_LPI_ENABLE_MASK) >> JL1111_RMSR_P7_RMII_TX_LPI_ENABLE_SHIFT)

/*
 * RMII_RX_LPI_ENABLE (RW)
 *
 * Enable reception LPI signal of RMII
 * CRS_DV=0 and RXD=1 will represent MII LPI
 */
#define JL1111_RMSR_P7_RMII_RX_LPI_ENABLE_MASK (0x4000U)
#define JL1111_RMSR_P7_RMII_RX_LPI_ENABLE_SHIFT (14U)
#define JL1111_RMSR_P7_RMII_RX_LPI_ENABLE_SET(x) (((uint16_t)(x) << JL1111_RMSR_P7_RMII_RX_LPI_ENABLE_SHIFT) & JL1111_RMSR_P7_RMII_RX_LPI_ENABLE_MASK)
#define JL1111_RMSR_P7_RMII_RX_LPI_ENABLE_GET(x) (((uint16_t)(x) & JL1111_RMSR_P7_RMII_RX_LPI_ENABLE_MASK) >> JL1111_RMSR_P7_RMII_RX_LPI_ENABLE_SHIFT)

/*
 * RMII_RX_ER_IN_RXD (RW)
 *
 * For Non-Bad-SSD rx_er, RXD will be 1
 */
#define JL1111_RMSR_P7_RMII_RX_ER_IN_RXD_MASK (0x2000U)
#define JL1111_RMSR_P7_RMII_RX_ER_IN_RXD_SHIFT (13U)
#define JL1111_RMSR_P7_RMII_RX_ER_IN_RXD_SET(x) (((uint16_t)(x) << JL1111_RMSR_P7_RMII_RX_ER_IN_RXD_SHIFT) & JL1111_RMSR_P7_RMII_RX_ER_IN_RXD_MASK)
#define JL1111_RMSR_P7_RMII_RX_ER_IN_RXD_GET(x) (((uint16_t)(x) & JL1111_RMSR_P7_RMII_RX_ER_IN_RXD_MASK) >> JL1111_RMSR_P7_RMII_RX_ER_IN_RXD_SHIFT)

/*
 * RMII_CLOCK_DIRECTION (RW)
 *
 * Clock Direction of TX_CLK in RMII Mode.
 * 0: 50MHz Output
 * 1: 50MHz Input
 */
#define JL1111_RMSR_P7_RMII_CLOCK_DIRECTION_MASK (0x1000U)
#define JL1111_RMSR_P7_RMII_CLOCK_DIRECTION_SHIFT (12U)
#define JL1111_RMSR_P7_RMII_CLOCK_DIRECTION_SET(x) (((uint16_t)(x) << JL1111_RMSR_P7_RMII_CLOCK_DIRECTION_SHIFT) & JL1111_RMSR_P7_RMII_CLOCK_DIRECTION_MASK)
#define JL1111_RMSR_P7_RMII_CLOCK_DIRECTION_GET(x) (((uint16_t)(x) & JL1111_RMSR_P7_RMII_CLOCK_DIRECTION_MASK) >> JL1111_RMSR_P7_RMII_CLOCK_DIRECTION_SHIFT)

/*
 * RMII_TX_SKEW (RW)
 *
 * Adjust RMII TX Interface Timing
 */
#define JL1111_RMSR_P7_RMII_TX_SKEW_MASK (0xF00U)
#define JL1111_RMSR_P7_RMII_TX_SKEW_SHIFT (8U)
#define JL1111_RMSR_P7_RMII_TX_SKEW_SET(x) (((uint16_t)(x) << JL1111_RMSR_P7_RMII_TX_SKEW_SHIFT) & JL1111_RMSR_P7_RMII_TX_SKEW_MASK)
#define JL1111_RMSR_P7_RMII_TX_SKEW_GET(x) (((uint16_t)(x) & JL1111_RMSR_P7_RMII_TX_SKEW_MASK) >> JL1111_RMSR_P7_RMII_TX_SKEW_SHIFT)

/*
 * RMII_RX_SKEW (RW)
 *
 * Adjust RMII RX Interface Timing
 */
#define JL1111_RMSR_P7_RMII_RX_SKEW_MASK (0xF0U)
#define JL1111_RMSR_P7_RMII_RX_SKEW_SHIFT (4U)
#define JL1111_RMSR_P7_RMII_RX_SKEW_SET(x) (((uint16_t)(x) << JL1111_RMSR_P7_RMII_RX_SKEW_SHIFT) & JL1111_RMSR_P7_RMII_RX_SKEW_MASK)
#define JL1111_RMSR_P7_RMII_RX_SKEW_GET(x) (((uint16_t)(x) & JL1111_RMSR_P7_RMII_RX_SKEW_MASK) >> JL1111_RMSR_P7_RMII_RX_SKEW_SHIFT)

/*
 * MII_RMII_MODE_SELECTION (RW)
 *
 * 0: RMII Mode
 * 1: RMII Mode
 */
#define JL1111_RMSR_P7_MII_RMII_MODE_SELECTION_MASK (0x8U)
#define JL1111_RMSR_P7_MII_RMII_MODE_SELECTION_SHIFT (3U)
#define JL1111_RMSR_P7_MII_RMII_MODE_SELECTION_SET(x) (((uint16_t)(x) << JL1111_RMSR_P7_MII_RMII_MODE_SELECTION_SHIFT) & JL1111_RMSR_P7_MII_RMII_MODE_SELECTION_MASK)
#define JL1111_RMSR_P7_MII_RMII_MODE_SELECTION_GET(x) (((uint16_t)(x) & JL1111_RMSR_P7_MII_RMII_MODE_SELECTION_MASK) >> JL1111_RMSR_P7_MII_RMII_MODE_SELECTION_SHIFT)

/*
 * RMII_CRS_DV_FUNCTIONAL (RW)
 *
 * 0: CRS_DV pin is CRS_DV signal
 * 1: CRS_DV pin is RXDV signal
 */
#define JL1111_RMSR_P7_RMII_CRS_DV_FUNCTIONAL_MASK (0x4U)
#define JL1111_RMSR_P7_RMII_CRS_DV_FUNCTIONAL_SHIFT (2U)
#define JL1111_RMSR_P7_RMII_CRS_DV_FUNCTIONAL_SET(x) (((uint16_t)(x) << JL1111_RMSR_P7_RMII_CRS_DV_FUNCTIONAL_SHIFT) & JL1111_RMSR_P7_RMII_CRS_DV_FUNCTIONAL_MASK)
#define JL1111_RMSR_P7_RMII_CRS_DV_FUNCTIONAL_GET(x) (((uint16_t)(x) & JL1111_RMSR_P7_RMII_CRS_DV_FUNCTIONAL_MASK) >> JL1111_RMSR_P7_RMII_CRS_DV_FUNCTIONAL_SHIFT)

/*
 * RMII_RXD_BAD_SSD_ENABLE (RW)
 *
 * 0: RMII data only
 * 1: RMII data with SSD Error
 */
#define JL1111_RMSR_P7_RMII_RXD_BAD_SSD_ENABLE_MASK (0x2U)
#define JL1111_RMSR_P7_RMII_RXD_BAD_SSD_ENABLE_SHIFT (1U)
#define JL1111_RMSR_P7_RMII_RXD_BAD_SSD_ENABLE_SET(x) (((uint16_t)(x) << JL1111_RMSR_P7_RMII_RXD_BAD_SSD_ENABLE_SHIFT) & JL1111_RMSR_P7_RMII_RXD_BAD_SSD_ENABLE_MASK)
#define JL1111_RMSR_P7_RMII_RXD_BAD_SSD_ENABLE_GET(x) (((uint16_t)(x) & JL1111_RMSR_P7_RMII_RXD_BAD_SSD_ENABLE_MASK) >> JL1111_RMSR_P7_RMII_RXD_BAD_SSD_ENABLE_SHIFT)

/* Bitfield definition for register: INTSQI */
/*
 * AUTONEG_ERROR (RC)
 *
 * Auto-Negotiation Error Interrupt
 */
#define JL1111_INTSQI_AUTONEG_ERROR_MASK (0x8000U)
#define JL1111_INTSQI_AUTONEG_ERROR_SHIFT (15U)
#define JL1111_INTSQI_AUTONEG_ERROR_GET(x) (((uint16_t)(x) & JL1111_INTSQI_AUTONEG_ERROR_MASK) >> JL1111_INTSQI_AUTONEG_ERROR_SHIFT)

/*
 * LINK_STATUS_CHANGE (RC)
 *
 * Link_Status_Change_Interrupt
 * 1: Enable
 * 0: Disable
 */
#define JL1111_INTSQI_LINK_STATUS_CHANGE_MASK (0x800U)
#define JL1111_INTSQI_LINK_STATUS_CHANGE_SHIFT (11U)
#define JL1111_INTSQI_LINK_STATUS_CHANGE_GET(x) (((uint16_t)(x) & JL1111_INTSQI_LINK_STATUS_CHANGE_MASK) >> JL1111_INTSQI_LINK_STATUS_CHANGE_SHIFT)

/*
 * SIGNAL_QUALITY_INDICATOR (RO)
 *
 * Signal Quality Indicator, lower is better. The value is only valid in 100Base-TX mode and its link status is ON
 */
#define JL1111_INTSQI_SIGNAL_QUALITY_INDICATOR_MASK (0x1FU)
#define JL1111_INTSQI_SIGNAL_QUALITY_INDICATOR_SHIFT (0U)
#define JL1111_INTSQI_SIGNAL_QUALITY_INDICATOR_GET(x) (((uint16_t)(x) & JL1111_INTSQI_SIGNAL_QUALITY_INDICATOR_MASK) >> JL1111_INTSQI_SIGNAL_QUALITY_INDICATOR_SHIFT)

/* Bitfield definition for register: PAGESEL */
/*
 * PAGE_SELECTION (RW)
 *
 */
#define JL1111_PAGESEL_PAGE_SELECTION_MASK (0xFFU)
#define JL1111_PAGESEL_PAGE_SELECTION_SHIFT (0U)
#define JL1111_PAGESEL_PAGE_SELECTION_SET(x) (((uint16_t)(x) << JL1111_PAGESEL_PAGE_SELECTION_SHIFT) & JL1111_PAGESEL_PAGE_SELECTION_MASK)
#define JL1111_PAGESEL_PAGE_SELECTION_GET(x) (((uint16_t)(x) & JL1111_PAGESEL_PAGE_SELECTION_MASK) >> JL1111_PAGESEL_PAGE_SELECTION_SHIFT)




#endif /* HPM_JL1111_REGS_H */