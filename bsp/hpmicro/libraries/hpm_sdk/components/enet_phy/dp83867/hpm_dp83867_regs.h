/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_DP83867_REGS_H
#define HPM_DP83867_REGS_H

 /* Register Definitions */
#define DP83867_REG_BMCR    (0U)  /* Basic Mode Control Register */
#define DP83867_REG_BMSR    (1U)  /* Basic Mode Status Register */
#define DP83867_REG_PHYID1  (2U)  /* PHY Identifier Register 1 */
#define DP83867_REG_PHYID2  (3U)  /* PHY Identifier Register 2 */
#define DP83867_REG_ANAR    (4U)  /* Auto-Negotiation Advertising Register */
#define DP83867_REG_ANLPAR  (5U)  /* Auto-Negotiation Link Partner Ability Register */
#define DP83867_REG_ANER    (6U)  /* Auto-Negotiation Expansion Register */
#define DP83867_REG_ANNPTR  (7U)  /* Auto-Negotiation Next Page Transmit Register */
#define DP83867_REG_ANNPRR  (8U)  /* Auto-Negotiation Next Page Receive Register */
#define DP83867_REG_GBCR    (9U)  /* 1000Base-T Control Register */
#define DP83867_REG_STATUS  (10U) /* Status Register */

#define DP83867_REG_MACR    (13U) /* MMD Access Control Register */
#define DP83867_REG_MAADR   (14U) /* MMD Access Address Data Register */
#define DP83867_REG_GBESR   (15U) /* 1000Base-T Extended Status Register */
#define DP83867_REG_PHYCR   (16U) /* PHY Specific Control Register */
#define DP83867_REG_PHYSR   (17U) /* PHY Specific Status Register */
#define DP83867_REG_INER    (18U) /* Interrupt Enable Register */
#define DP83867_REG_INSR    (19U) /* Interrupt Status Register */
#define DP83867_REG_RXERC   (24U) /* Receive Error Counter */
#define DP83867_REG_PAGSEL  (31U) /* Page Select Register */

/* RTL MMD Register Definitions */
#define DP83867_MMD_REG_PC1R    (0U)  /* PCS Control 1 Register */
#define DP83867_MMD_REG_PS1R    (1U)  /* PCS Status 1 Register */
#define DP83867_MMD_REG_EEECR   (20U) /* EEE Capability Register */
#define DP83867_MMD_REG_EEEWER  (22U) /* EEE Wake Error Register */
#define DP83867_MMD_REG_EEEAR   (60U) /* EEE Advertisement Register */
#define DP83867_MMD_REG_EEELPAR (61U) /* EEE Link Partner Ability Register */

/* DP83867 */

/* DP83867 Extended Registers */
#define DP83867_EXT_REG_REGCR     (0x000DU)  /* Register Control Register */
#define DP83867_EXT_REG_ADDAR     (0x000EU)  /* Address or Data Register */
#define DP83867_EXT_REG_BISCR     (0x0016U)  /* BIST Control Register */
#define DP83867_EXT_REG_CTRL      (0x001fU)  /* Control Register */
#define DP83867_EXT_REG_RGMIICTL  (0x0032U)  /* RGMII Control Register */
#define DP83867_EXT_REG_LOOPCR    (0x00FEU)  /* Loopback Configuration Register */
#define DP83867_EXT_REG_RXFCFG    (0x0134U)  /* Recevie Configuration Register */

/* DP83867 extended registers */
#define DP83867_EXT_REG_RGMIIDCTL (0x0086U) /* RGMII Delay Control */


#define DP83867_REGCR_FUNCTION_ADDR  (0 << 14)
#define DP83867_REGCR_FUNCTION_DATA  (1 << 14)
#define DP83867_REGCR_DEVAD          (0x1f)

/* Bitfield definition for register: BMCR */
/*
 * Reset (RW)
 *
 * 1: PHY reset
 * 0: Normal operation
 * Register 0 (BMCR) and register 1 (BMSR) will return to default
 * values after a software reset (set Bit15 to 1).
 * This action may change the internal PHY state and the state of the
 * physical link associated with the PHY.
 */
#define DP83867_BMCR_RESET_MASK  (0x8000U)
#define DP83867_BMCR_RESET_SHIFT (15U)
#define DP83867_BMCR_RESET_SET(x) (((uint32_t)(x) << DP83867_BMCR_RESET_SHIFT) & DP83867_BMCR_RESET_MASK)
#define DP83867_BMCR_RESET_GET(x) (((uint32_t)(x) & DP83867_BMCR_RESET_MASK) >> DP83867_BMCR_RESET_SHIFT)

/*
 * Loopback (RW)
 *
 * Loopback Mode.
 * 1: Enable PCS loopback mode
 * 0: Disable PCS loopback mode
 */
#define DP83867_BMCR_LOOPBACK_MASK  (0x4000U)
#define DP83867_BMCR_LOOPBACK_SHIFT (14U)
#define DP83867_BMCR_LOOPBACK_SET(x) (((uint32_t)(x) << DP83867_BMCR_LOOPBACK_SHIFT) & DP83867_BMCR_LOOPBACK_MASK)
#define DP83867_BMCR_LOOPBACK_GET(x) (((uint32_t)(x) & DP83867_BMCR_LOOPBACK_MASK) >> DP83867_BMCR_LOOPBACK_SHIFT)

/*
 * Speed[0] (RW)
 *
 * Speed Select Bit 0.
 * In forced mode, i.e., when Auto-Negotiation is disabled, bits 6 and 13
 * determine device speed selection.
 */
#define DP83867_BMCR_SPEED0_MASK  (0x2000U)
#define DP83867_BMCR_SPEED0_SHIFT (13U)
#define DP83867_BMCR_SPEED0_SET(x) (((uint32_t)(x) << DP83867_BMCR_SPEED0_SHIFT) & DP83867_BMCR_SPEED0_MASK)
#define DP83867_BMCR_SPEED0_GET(x) (((uint32_t)(x) & DP83867_BMCR_SPEED0_MASK) >> DP83867_BMCR_SPEED0_SHIFT)

/*
 * ANE (RW)
 *
 * Auto-Negotiation Enable.
 * 1: Enable Auto-Negotiation
 * 0: Disable Auto-Negotiation
 */
#define DP83867_BMCR_ANE_MASK  (0x1000U)
#define DP83867_BMCR_ANE_SHIFT (12U)
#define DP83867_BMCR_ANE_SET(x) (((uint32_t)(x) << DP83867_BMCR_ANE_SHIFT) & DP83867_BMCR_ANE_MASK)
#define DP83867_BMCR_ANE_GET(x) (((uint32_t)(x) & DP83867_BMCR_ANE_MASK) >> DP83867_BMCR_ANE_SHIFT)

/*
 * PWD (RW)
 *
 * Power Down.
 * 1: Power down (only Management Interface and logic are active; link
 * is down)
 * 0: Normal operation
 */
#define DP83867_BMCR_PWD_MASK  (0x0800U)
#define DP83867_BMCR_PWD_SHIFT (11U)
#define DP83867_BMCR_PWD_SET(x) (((uint32_t)(x) << DP83867_BMCR_PWD_SHIFT) & DP83867_BMCR_PWD_MASK)
#define DP83867_BMCR_PWD_GET(x) (((uint32_t)(x) & DP83867_BMCR_PWD_MASK) >> DP83867_BMCR_PWD_SHIFT)

/*
 * Isolate (RW)
 *
 * Isolate.
 * 1: RGMII/GMII interface is isolated; the serial management interface
 * (MDC, MDIO) is still active. When this bit is asserted, the
 * RTL8211E/RTL8211EG ignores TXD[7:0], and TXCLT inputs, and
 * presents a high impedance on TXC, RXC, RXCLT, RXD[7:0].
 * 0: Normal operation
 */
#define DP83867_BMCR_ISOLATE_MASK  (0x0400U)
#define DP83867_BMCR_ISOLATE_SHIFT (10U)
#define DP83867_BMCR_ISOLATE_SET(x) (((uint32_t)(x) << DP83867_BMCR_ISOLATE_SHIFT) & DP83867_BMCR_ISOLATE_MASK)
#define DP83867_BMCR_ISOLATE_GET(x) (((uint32_t)(x) & DP83867_BMCR_ISOLATE_MASK) >> DP83867_BMCR_ISOLATE_SHIFT)

/*
 * Restart_AN (RW)
 *
 * Restart Auto-Negotiation.
 * 1: Restart Auto-Negotiation
 * 0: Normal operation
 */
#define DP83867_BMCR_RESTART_AN_MASK  (0x0200U)
#define DP83867_BMCR_RESTART_AN_SHIFT (9U)
#define DP83867_BMCR_RESTART_AN_SET(x) (((uint32_t)(x) << DP83867_BMCR_RESTART_AN_SHIFT) & DP83867_BMCR_RESTART_AN_MASK)
#define DP83867_BMCR_RESTART_AN_GET(x) (((uint32_t)(x) & DP83867_BMCR_RESTART_AN_MASK) >> DP83867_BMCR_RESTART_AN_SHIFT)

/*
 * Duplex (RW)
 *
 * Duplex Mode.
 * 1: Full Duplex operation
 * 0: Half Duplex operation
 * This bit is valid only in force mode, i.e., NWay is disabled.
 */
#define DP83867_BMCR_DUPLEX_MASK  (0x0100U)
#define DP83867_BMCR_DUPLEX_SHIFT (8U)
#define DP83867_BMCR_DUPLEX_SET(x) (((uint32_t)(x) << DP83867_BMCR_DUPLEX_SHIFT) & DP83867_BMCR_DUPLEX_MASK)
#define DP83867_BMCR_DUPLEX_GET(x) (((uint32_t)(x) & DP83867_BMCR_DUPLEX_MASK) >> DP83867_BMCR_DUPLEX_SHIFT)

/*
 * Collision Test (RW)
 *
 * Collision Test.
 * 1: Collision test enabled
 * 0: Normal operation
 * When set, this bit will cause the COL signal to be asserted in response
 * to the assertion of TXEN within 512-bit times. The COL signal will be
 * de-asserted within 4-bit times in response to the de-assertion of
 * TXEN.
 */
#define DP83867_BMCR_COLLISION_TEST_MASK  (0x0080U)
#define DP83867_BMCR_COLLISION_TEST_SHIFT (7U)
#define DP83867_BMCR_COLLISION_TEST_SET(x) (((uint32_t)(x) << DP83867_BMCR_COLLISION_TEST_SHIFT) & DP83867_BMCR_COLLISION_TEST_MASK)
#define DP83867_BMCR_COLLISION_TEST_GET(x) (((uint32_t)(x) & DP83867_BMCR_COLLISION_TEST_MASK) >> DP83867_BMCR_COLLISION_TEST_SHIFT)

/*
 * Speed[1] (RW)
 *
 * Speed Select Bit 1.
 * Refer to bit 0.13.
 */
#define DP83867_BMCR_SPEED1_MASK  (0x0040U)
#define DP83867_BMCR_SPEED1_SHIFT (6U)
#define DP83867_BMCR_SPEED1_SET(x) (((uint32_t)(x) << DP83867_BMCR_SPEED1_SHIFT) & DP83867_BMCR_SPEED1_MASK)
#define DP83867_BMCR_SPEED1_GET(x) (((uint32_t)(x) & DP83867_BMCR_SPEED1_MASK) >> DP83867_BMCR_SPEED1_SHIFT)

/* Bitfield definition for register: BMSR */

/*
 * Link Status:
 * 1 = Valid link established.
 * 0 = Link not established.
 * The criteria for link validity is implementation specific. The
 * occurrence of a link failure condition will causes the Link Status bit
 * to clear. Once cleared, this bit may only be set by establishing a
 * good link condition and a read through the management interface.
*/
#define DP83867_BMSR_LINK_STATUS_MASK  (0x0004U)
#define DP83867_BMSR_LINK_STATUS_SHIFT (2U)
#define DP83867_BMSR_LINK_STATUS_GET(x) (((uint32_t)(x) & DP83867_BMSR_LINK_STATUS_MASK) >> DP83867_BMSR_LINK_STATUS_SHIFT)



/* Bitfield definition for register: PHYID1 */
/*
 * OUI_MSB (RO)
 *
 * Organizationally Unique Identifier Bit 3:18.
 * Always 0000000000011100.
 */
#define DP83867_PHYID1_OUI_MSB_MASK  (0xFFFFU)
#define DP83867_PHYID1_OUI_MSB_SHIFT (0U)
#define DP83867_PHYID1_OUI_MSB_GET(x) (((uint32_t)(x) & DP83867_PHYID1_OUI_MSB_MASK) >> DP83867_PHYID1_OUI_MSB_SHIFT)

/* Bitfield definition for register: PHYID2 */
/*
 * OUI_LSB (RO)
 *
 * Organizationally Unique Identifier Bit 19:24.
 * Always 110010.
 */
#define DP83867_PHYID2_OUI_MSB_MASK  (0xFC00U)
#define DP83867_PHYID2_OUI_MSB_SHIFT (10U)
#define DP83867_PHYID2_OUI_MSB_GET(x) (((uint32_t)(x) & DP83867_PHYID2_OUI_MSB_MASK) >> DP83867_PHYID2_OUI_MSB_SHIFT)

/* Bitfield definition for register: RGMIICTL */
/*
 * RGMII_EN (RW)
 *
 * RGMII Enable:
 * 1 = Enable RGMII interface.
 * 0 = Disable RGMII interface
 */
#define DP83867_RGMIICTL_RGMII_EN_MASK   (0x80)
#define DP83867_RGMIICTL_RGMII_EN_SHIFT  (7U)
#define DP83867_RGMIICTL_RGMII_EN_SET(x) (((uint32_t)(x) << DP83867_RGMIICTL_RGMII_EN_SHIFT) & DP83867_RGMIICTL_RGMII_EN_MASK)
#define DP83867_RGMIICTL_RGMII_EN_GET(x) (((uint32_t)(x) & DP83867_RGMIICTL_RGMII_EN_SHIFT) >> DP83867_RGMIICTL_RGMII_EN_MASK)
#endif /* HPM_DP83867_REGS_H */