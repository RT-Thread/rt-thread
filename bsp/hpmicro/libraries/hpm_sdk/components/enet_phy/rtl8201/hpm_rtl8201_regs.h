/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_RTL8201_REGS_H
#define HPM_RTL8201_REGS_H

typedef enum {
    RTL8201_BMCR                        = 0,   /* 0x0: Basic Mode Control Register */
    RTL8201_BMSR                        = 1,   /* 0x1: (Basic Mode Status Register */
    RTL8201_PHYID1                      = 2,   /* 0x2: PHY Identifier Register 1 */
    RTL8201_PHYID2                      = 3,   /* 0x3: PHY Identifier Register 2 */
    RTL8201_RMSR_P7                     = 16,  /* 0x10: RMII Mode Setting Register */
    RTL8201_PAGESEL                     = 31,  /* 0x1F: Page Select Register */
} RTL8201_REG_Type;


/* Bitfield definition for register: BMCR */
/*
 * RESET (RW/SC)
 *
 * This bit sets the status and control registers of the PHY in the
 * default state. This bit is self-clearing.
 * 1: Software reset  0: Normal operation
 * Register 0 and register 1 will return to default values after a
 * software reset (set Bit15 to 1).
 * This action may change the internal PHY state and the state of the
 * physical link associated with the PHY.
 */
#define RTL8201_BMCR_RESET_MASK (0x8000U)
#define RTL8201_BMCR_RESET_SHIFT (15U)
#define RTL8201_BMCR_RESET_SET(x) (((uint16_t)(x) << RTL8201_BMCR_RESET_SHIFT) & RTL8201_BMCR_RESET_MASK)
#define RTL8201_BMCR_RESET_GET(x) (((uint16_t)(x) & RTL8201_BMCR_RESET_MASK) >> RTL8201_BMCR_RESET_SHIFT)

/*
 * LOOPBACK (RW)
 *
 * This bit enables loopback of transmit data nibbles TXD3:0 to the
 * receive data path.
 * 1: Enable loopback  0: Normal operation
 */
#define RTL8201_BMCR_LOOPBACK_MASK (0x4000U)
#define RTL8201_BMCR_LOOPBACK_SHIFT (14U)
#define RTL8201_BMCR_LOOPBACK_SET(x) (((uint16_t)(x) << RTL8201_BMCR_LOOPBACK_SHIFT) & RTL8201_BMCR_LOOPBACK_MASK)
#define RTL8201_BMCR_LOOPBACK_GET(x) (((uint16_t)(x) & RTL8201_BMCR_LOOPBACK_MASK) >> RTL8201_BMCR_LOOPBACK_SHIFT)

/*
 * SPEED0 (RW)
 *
 * This bit sets the network speed.
 * 1: 100Mbps  0: 10Mbps
 * After completing auto negotiation, this bit will reflect the speed
 * status.
 * 1: 100Base-T  0: 10Base-T
 * When 100Base-FX mode is enabled, this bit=1 and is read only.
 */
#define RTL8201_BMCR_SPEED0_MASK (0x2000U)
#define RTL8201_BMCR_SPEED0_SHIFT (13U)
#define RTL8201_BMCR_SPEED0_SET(x) (((uint16_t)(x) << RTL8201_BMCR_SPEED0_SHIFT) & RTL8201_BMCR_SPEED0_MASK)
#define RTL8201_BMCR_SPEED0_GET(x) (((uint16_t)(x) & RTL8201_BMCR_SPEED0_MASK) >> RTL8201_BMCR_SPEED0_SHIFT)

/*
 * ANE (RW)
 *
 * This bit enables/disables the NWay auto-negotiation function.
 * 1: Enable auto-negotiation; bits 0:13 and 0:8 will be ignored
 * 0: Disable auto-negotiation; bits 0:13 and 0:8 will determine the
 * link speed and the data transfer mode, respectively
 * When 100Base-FX mode is enabled, this bit=0 and is read only.
 */
#define RTL8201_BMCR_ANE_MASK (0x1000U)
#define RTL8201_BMCR_ANE_SHIFT (12U)
#define RTL8201_BMCR_ANE_SET(x) (((uint16_t)(x) << RTL8201_BMCR_ANE_SHIFT) & RTL8201_BMCR_ANE_MASK)
#define RTL8201_BMCR_ANE_GET(x) (((uint16_t)(x) & RTL8201_BMCR_ANE_MASK) >> RTL8201_BMCR_ANE_SHIFT)

/*
 * PWD (RW)
 *
 * This bit turns down the power of the PHY chip, including the
 * internal crystal oscillator circuit.
 * The MDC, MDIO is still alive for accessing the MAC.
 * 1: Power down  0: Normal operation
 */
#define RTL8201_BMCR_PWD_MASK (0x800U)
#define RTL8201_BMCR_PWD_SHIFT (11U)
#define RTL8201_BMCR_PWD_SET(x) (((uint16_t)(x) << RTL8201_BMCR_PWD_SHIFT) & RTL8201_BMCR_PWD_MASK)
#define RTL8201_BMCR_PWD_GET(x) (((uint16_t)(x) & RTL8201_BMCR_PWD_MASK) >> RTL8201_BMCR_PWD_SHIFT)

/*
 * ISOLATE (RW)
 *
 * 1: Electrically isolate the PHY from MII/GMII/RGMII/RSGMII.
 * PHY is still able to respond to MDC/MDIO.
 * 0: Normal operation
 */
#define RTL8201_BMCR_ISOLATE_MASK (0x400U)
#define RTL8201_BMCR_ISOLATE_SHIFT (10U)
#define RTL8201_BMCR_ISOLATE_SET(x) (((uint16_t)(x) << RTL8201_BMCR_ISOLATE_SHIFT) & RTL8201_BMCR_ISOLATE_MASK)
#define RTL8201_BMCR_ISOLATE_GET(x) (((uint16_t)(x) & RTL8201_BMCR_ISOLATE_MASK) >> RTL8201_BMCR_ISOLATE_SHIFT)

/*
 * RESTART_AN (RW/SC)
 *
 * This bit allows the NWay auto-negotiation function to be reset.
 * 1: Re-start auto-negotiation  0: Normal operation
 */
#define RTL8201_BMCR_RESTART_AN_MASK (0x200U)
#define RTL8201_BMCR_RESTART_AN_SHIFT (9U)
#define RTL8201_BMCR_RESTART_AN_SET(x) (((uint16_t)(x) << RTL8201_BMCR_RESTART_AN_SHIFT) & RTL8201_BMCR_RESTART_AN_MASK)
#define RTL8201_BMCR_RESTART_AN_GET(x) (((uint16_t)(x) & RTL8201_BMCR_RESTART_AN_MASK) >> RTL8201_BMCR_RESTART_AN_SHIFT)

/*
 * DUPLEX (RW)
 *
 * This bit sets the duplex mode if auto-negotiation is disabled (bit
 * 0:12=0).
 * 1: Full duplex  0: Half duplex
 * After completing auto-negotiation, this bit will reflect the duplex
 * status.
 * 1: Full duplex  0: Half duplex
 */
#define RTL8201_BMCR_DUPLEX_MASK (0x100U)
#define RTL8201_BMCR_DUPLEX_SHIFT (8U)
#define RTL8201_BMCR_DUPLEX_SET(x) (((uint16_t)(x) << RTL8201_BMCR_DUPLEX_SHIFT) & RTL8201_BMCR_DUPLEX_MASK)
#define RTL8201_BMCR_DUPLEX_GET(x) (((uint16_t)(x) & RTL8201_BMCR_DUPLEX_MASK) >> RTL8201_BMCR_DUPLEX_SHIFT)

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
#define RTL8201_BMCR_COLLISION_TEST_MASK (0x80U)
#define RTL8201_BMCR_COLLISION_TEST_SHIFT (7U)
#define RTL8201_BMCR_COLLISION_TEST_SET(x) (((uint16_t)(x) << RTL8201_BMCR_COLLISION_TEST_SHIFT) & RTL8201_BMCR_COLLISION_TEST_MASK)
#define RTL8201_BMCR_COLLISION_TEST_GET(x) (((uint16_t)(x) & RTL8201_BMCR_COLLISION_TEST_MASK) >> RTL8201_BMCR_COLLISION_TEST_SHIFT)

/*
 * SPEED1 (RW)
 *
 * Speed Select Bit 1.
 * Refer to bit 13.
 */
#define RTL8201_BMCR_SPEED1_MASK (0x40U)
#define RTL8201_BMCR_SPEED1_SHIFT (6U)
#define RTL8201_BMCR_SPEED1_SET(x) (((uint16_t)(x) << RTL8201_BMCR_SPEED1_SHIFT) & RTL8201_BMCR_SPEED1_MASK)
#define RTL8201_BMCR_SPEED1_GET(x) (((uint16_t)(x) & RTL8201_BMCR_SPEED1_MASK) >> RTL8201_BMCR_SPEED1_SHIFT)

/* Bitfield definition for register: BMSR */
/*
 * 100BASE_T4 (RO)
 *
 * 1: Enable 100Base-T4 support
 * 0: Suppress 100Base-T4 support
 */
#define RTL8201_BMSR_100BASE_T4_MASK (0x8000U)
#define RTL8201_BMSR_100BASE_T4_SHIFT (15U)
#define RTL8201_BMSR_100BASE_T4_GET(x) (((uint16_t)(x) & RTL8201_BMSR_100BASE_T4_MASK) >> RTL8201_BMSR_100BASE_T4_SHIFT)

/*
 * 100BASE_TX_FULL (RO)
 *
 * 1: Enable 100Base-TX full duplex support
 * 0: Suppress 100Base-TX full duplex support
 */
#define RTL8201_BMSR_100BASE_TX_FULL_MASK (0x4000U)
#define RTL8201_BMSR_100BASE_TX_FULL_SHIFT (14U)
#define RTL8201_BMSR_100BASE_TX_FULL_GET(x) (((uint16_t)(x) & RTL8201_BMSR_100BASE_TX_FULL_MASK) >> RTL8201_BMSR_100BASE_TX_FULL_SHIFT)

/*
 * 100BASE_TX_HALF (RO)
 *
 * 1: Enable 100Base-TX half duplex support
 * 0: Suppress 100Base-TX half duplex support
 */
#define RTL8201_BMSR_100BASE_TX_HALF_MASK (0x2000U)
#define RTL8201_BMSR_100BASE_TX_HALF_SHIFT (13U)
#define RTL8201_BMSR_100BASE_TX_HALF_GET(x) (((uint16_t)(x) & RTL8201_BMSR_100BASE_TX_HALF_MASK) >> RTL8201_BMSR_100BASE_TX_HALF_SHIFT)

/*
 * 10BASE_T_FULL (RO)
 *
 * 1: Enable 10Base-T full duplex support
 * 0: Suppress 10Base-T full duplex support
 */
#define RTL8201_BMSR_10BASE_T_FULL_MASK (0x1000U)
#define RTL8201_BMSR_10BASE_T_FULL_SHIFT (12U)
#define RTL8201_BMSR_10BASE_T_FULL_GET(x) (((uint16_t)(x) & RTL8201_BMSR_10BASE_T_FULL_MASK) >> RTL8201_BMSR_10BASE_T_FULL_SHIFT)

/*
 * 10BASE_T_HALF (RO)
 *
 * 1: Enable 10Base-T half duplex support
 * 0: Suppress 10Base-T half duplex support
 */
#define RTL8201_BMSR_10BASE_T_HALF_MASK (0x800U)
#define RTL8201_BMSR_10BASE_T_HALF_SHIFT (11U)
#define RTL8201_BMSR_10BASE_T_HALF_GET(x) (((uint16_t)(x) & RTL8201_BMSR_10BASE_T_HALF_MASK) >> RTL8201_BMSR_10BASE_T_HALF_SHIFT)

/*
 * PREAMBLE_SUPPRESSION (RO)
 *
 * The RTL8201F/FL/FN will accept management frames
 * with preamble suppressed.
 * A minimum of 32 preamble bits are required for the first
 * management interface read/write transaction after reset.
 * One idle bit is required between any two management
 * transactions as per IEEE 802.3u specifications.
 */
#define RTL8201_BMSR_PREAMBLE_SUPPRESSION_MASK (0x40U)
#define RTL8201_BMSR_PREAMBLE_SUPPRESSION_SHIFT (6U)
#define RTL8201_BMSR_PREAMBLE_SUPPRESSION_GET(x) (((uint16_t)(x) & RTL8201_BMSR_PREAMBLE_SUPPRESSION_MASK) >> RTL8201_BMSR_PREAMBLE_SUPPRESSION_SHIFT)

/*
 * AUTO_NEGOTIATION_COMPLETE (RO)
 *
 * 1: Auto-negotiation process completed
 * 0: Auto-negotiation process not completed
 */
#define RTL8201_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK (0x20U)
#define RTL8201_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT (5U)
#define RTL8201_BMSR_AUTO_NEGOTIATION_COMPLETE_GET(x) (((uint16_t)(x) & RTL8201_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK) >> RTL8201_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT)

/*
 * REMOTE_FAULT (RC)
 *
 * 1: Remote fault condition detected (cleared on read)
 * 0: No remote fault condition detected
 * When in 100Base-FX mode, this bit means an in-band
 * signal Far-End-Fault has been detected (see 8.10 Far End
 * Fault Indication, page 39).
 */
#define RTL8201_BMSR_REMOTE_FAULT_MASK (0x10U)
#define RTL8201_BMSR_REMOTE_FAULT_SHIFT (4U)
#define RTL8201_BMSR_REMOTE_FAULT_GET(x) (((uint16_t)(x) & RTL8201_BMSR_REMOTE_FAULT_MASK) >> RTL8201_BMSR_REMOTE_FAULT_SHIFT)

/*
 * AUTO_NEGOTIATION_ABILITY (RO)
 *
 * 1: PHY is able to perform auto-negotiation
 * 0: PHY is not able to perform auto-negotiation
 */
#define RTL8201_BMSR_AUTO_NEGOTIATION_ABILITY_MASK (0x8U)
#define RTL8201_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT (3U)
#define RTL8201_BMSR_AUTO_NEGOTIATION_ABILITY_GET(x) (((uint16_t)(x) & RTL8201_BMSR_AUTO_NEGOTIATION_ABILITY_MASK) >> RTL8201_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT)

/*
 * LINK_STATUS (RO)
 *
 * 1: Valid link established
 * 0: No valid link established
 * This bit indicates whether the link was lost since the last
 * read. For the current link status, read this register twice.
 */
#define RTL8201_BMSR_LINK_STATUS_MASK (0x4U)
#define RTL8201_BMSR_LINK_STATUS_SHIFT (2U)
#define RTL8201_BMSR_LINK_STATUS_GET(x) (((uint16_t)(x) & RTL8201_BMSR_LINK_STATUS_MASK) >> RTL8201_BMSR_LINK_STATUS_SHIFT)

/*
 * JABBER_DETECT (RO)
 *
 * 1: Jabber condition detected
 * 0: No jabber condition detected
 */
#define RTL8201_BMSR_JABBER_DETECT_MASK (0x2U)
#define RTL8201_BMSR_JABBER_DETECT_SHIFT (1U)
#define RTL8201_BMSR_JABBER_DETECT_GET(x) (((uint16_t)(x) & RTL8201_BMSR_JABBER_DETECT_MASK) >> RTL8201_BMSR_JABBER_DETECT_SHIFT)

/*
 * EXTENDED_CAPABILITY (RO)
 *
 * 1: Extended register capable (permanently=1)
 * 0: Not extended register capable
 */
#define RTL8201_BMSR_EXTENDED_CAPABILITY_MASK (0x1U)
#define RTL8201_BMSR_EXTENDED_CAPABILITY_SHIFT (0U)
#define RTL8201_BMSR_EXTENDED_CAPABILITY_GET(x) (((uint16_t)(x) & RTL8201_BMSR_EXTENDED_CAPABILITY_MASK) >> RTL8201_BMSR_EXTENDED_CAPABILITY_SHIFT)

/* Bitfield definition for register: PHYID1 */
/*
 * OUI_MSB (RO)
 *
 * Composed of the 6 th  to 21 st  bits of the Organizationally Unique
 * Identifier (OUI), respectively.
 */
#define RTL8201_PHYID1_OUI_MSB_MASK (0xFFFFU)
#define RTL8201_PHYID1_OUI_MSB_SHIFT (0U)
#define RTL8201_PHYID1_OUI_MSB_GET(x) (((uint16_t)(x) & RTL8201_PHYID1_OUI_MSB_MASK) >> RTL8201_PHYID1_OUI_MSB_SHIFT)

/* Bitfield definition for register: PHYID2 */
/*
 * OUI_LSB (RO)
 *
 * Assigned to the 0 through 5 th  bits of the OUI.  RO  110010
 */
#define RTL8201_PHYID2_OUI_LSB_MASK (0xFC00U)
#define RTL8201_PHYID2_OUI_LSB_SHIFT (10U)
#define RTL8201_PHYID2_OUI_LSB_GET(x) (((uint16_t)(x) & RTL8201_PHYID2_OUI_LSB_MASK) >> RTL8201_PHYID2_OUI_LSB_SHIFT)

/*
 * MODEL_NUMBER (RO)
 *
 * Model Number
 */
#define RTL8201_PHYID2_MODEL_NUMBER_MASK (0x3F0U)
#define RTL8201_PHYID2_MODEL_NUMBER_SHIFT (4U)
#define RTL8201_PHYID2_MODEL_NUMBER_GET(x) (((uint16_t)(x) & RTL8201_PHYID2_MODEL_NUMBER_MASK) >> RTL8201_PHYID2_MODEL_NUMBER_SHIFT)

/*
 * REVISION_NUMBER (RO)
 *
 * Revision Number
 */
#define RTL8201_PHYID2_REVISION_NUMBER_MASK (0xFU)
#define RTL8201_PHYID2_REVISION_NUMBER_SHIFT (0U)
#define RTL8201_PHYID2_REVISION_NUMBER_GET(x) (((uint16_t)(x) & RTL8201_PHYID2_REVISION_NUMBER_MASK) >> RTL8201_PHYID2_REVISION_NUMBER_SHIFT)

/* Bitfield definition for register: RMSR_P7 */
/*
 * RG_RMII_CLKDIR (RW)
 *
 * This Bit Sets the Type of TXC in RMII Mode.
 * 0: Output
 * 1: Input
 */
#define RTL8201_RMSR_P7_RG_RMII_CLKDIR_MASK (0x1000U)
#define RTL8201_RMSR_P7_RG_RMII_CLKDIR_SHIFT (12U)
#define RTL8201_RMSR_P7_RG_RMII_CLKDIR_SET(x) (((uint16_t)(x) << RTL8201_RMSR_P7_RG_RMII_CLKDIR_SHIFT) & RTL8201_RMSR_P7_RG_RMII_CLKDIR_MASK)
#define RTL8201_RMSR_P7_RG_RMII_CLKDIR_GET(x) (((uint16_t)(x) & RTL8201_RMSR_P7_RG_RMII_CLKDIR_MASK) >> RTL8201_RMSR_P7_RG_RMII_CLKDIR_SHIFT)

/*
 * RG_RMII_TX_OFFSET (RW)
 *
 * Adjust RMII TX Interface Timing.
 */
#define RTL8201_RMSR_P7_RG_RMII_TX_OFFSET_MASK (0xF00U)
#define RTL8201_RMSR_P7_RG_RMII_TX_OFFSET_SHIFT (8U)
#define RTL8201_RMSR_P7_RG_RMII_TX_OFFSET_SET(x) (((uint16_t)(x) << RTL8201_RMSR_P7_RG_RMII_TX_OFFSET_SHIFT) & RTL8201_RMSR_P7_RG_RMII_TX_OFFSET_MASK)
#define RTL8201_RMSR_P7_RG_RMII_TX_OFFSET_GET(x) (((uint16_t)(x) & RTL8201_RMSR_P7_RG_RMII_TX_OFFSET_MASK) >> RTL8201_RMSR_P7_RG_RMII_TX_OFFSET_SHIFT)

/*
 * RG_RMII_RX_OFFSET (RW)
 *
 * Adjust RMII RX Interface Timing.
 */
#define RTL8201_RMSR_P7_RG_RMII_RX_OFFSET_MASK (0xF0U)
#define RTL8201_RMSR_P7_RG_RMII_RX_OFFSET_SHIFT (4U)
#define RTL8201_RMSR_P7_RG_RMII_RX_OFFSET_SET(x) (((uint16_t)(x) << RTL8201_RMSR_P7_RG_RMII_RX_OFFSET_SHIFT) & RTL8201_RMSR_P7_RG_RMII_RX_OFFSET_MASK)
#define RTL8201_RMSR_P7_RG_RMII_RX_OFFSET_GET(x) (((uint16_t)(x) & RTL8201_RMSR_P7_RG_RMII_RX_OFFSET_MASK) >> RTL8201_RMSR_P7_RG_RMII_RX_OFFSET_SHIFT)

/*
 * RMII_MODE (RW)
 *
 * 0: MII Mode
 * 1: RMII Mode
 */
#define RTL8201_RMSR_P7_RMII_MODE_MASK (0x8U)
#define RTL8201_RMSR_P7_RMII_MODE_SHIFT (3U)
#define RTL8201_RMSR_P7_RMII_MODE_SET(x) (((uint16_t)(x) << RTL8201_RMSR_P7_RMII_MODE_SHIFT) & RTL8201_RMSR_P7_RMII_MODE_MASK)
#define RTL8201_RMSR_P7_RMII_MODE_GET(x) (((uint16_t)(x) & RTL8201_RMSR_P7_RMII_MODE_MASK) >> RTL8201_RMSR_P7_RMII_MODE_SHIFT)

/*
 * RG_RMII_RXDV_SEL (RW)
 *
 * 0: CRS/CRS_DV pin is CRS_DV signal
 * 1: CRS/CRS_DV pin is RXDV signal
 */
#define RTL8201_RMSR_P7_RG_RMII_RXDV_SEL_MASK (0x4U)
#define RTL8201_RMSR_P7_RG_RMII_RXDV_SEL_SHIFT (2U)
#define RTL8201_RMSR_P7_RG_RMII_RXDV_SEL_SET(x) (((uint16_t)(x) << RTL8201_RMSR_P7_RG_RMII_RXDV_SEL_SHIFT) & RTL8201_RMSR_P7_RG_RMII_RXDV_SEL_MASK)
#define RTL8201_RMSR_P7_RG_RMII_RXDV_SEL_GET(x) (((uint16_t)(x) & RTL8201_RMSR_P7_RG_RMII_RXDV_SEL_MASK) >> RTL8201_RMSR_P7_RG_RMII_RXDV_SEL_SHIFT)

/*
 * RG_RMII_RXDSEL (RW)
 *
 * 0: RMII data only
 * 1: RMII data with SSD Error
 */
#define RTL8201_RMSR_P7_RG_RMII_RXDSEL_MASK (0x2U)
#define RTL8201_RMSR_P7_RG_RMII_RXDSEL_SHIFT (1U)
#define RTL8201_RMSR_P7_RG_RMII_RXDSEL_SET(x) (((uint16_t)(x) << RTL8201_RMSR_P7_RG_RMII_RXDSEL_SHIFT) & RTL8201_RMSR_P7_RG_RMII_RXDSEL_MASK)
#define RTL8201_RMSR_P7_RG_RMII_RXDSEL_GET(x) (((uint16_t)(x) & RTL8201_RMSR_P7_RG_RMII_RXDSEL_MASK) >> RTL8201_RMSR_P7_RG_RMII_RXDSEL_SHIFT)

/* Bitfield definition for register: PAGESEL */
/*
 * PAGE_SEL (RW)
 *
 * Select Page Address: 00000000~11111111.
 */
#define RTL8201_PAGESEL_PAGE_SEL_MASK (0xFFU)
#define RTL8201_PAGESEL_PAGE_SEL_SHIFT (0U)
#define RTL8201_PAGESEL_PAGE_SEL_SET(x) (((uint16_t)(x) << RTL8201_PAGESEL_PAGE_SEL_SHIFT) & RTL8201_PAGESEL_PAGE_SEL_MASK)
#define RTL8201_PAGESEL_PAGE_SEL_GET(x) (((uint16_t)(x) & RTL8201_PAGESEL_PAGE_SEL_MASK) >> RTL8201_PAGESEL_PAGE_SEL_SHIFT)




#endif /* HPM_RTL8201_REGS_H */
