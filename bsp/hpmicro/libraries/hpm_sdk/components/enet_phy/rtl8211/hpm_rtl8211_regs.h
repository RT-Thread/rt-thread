/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_RTL8211_REGS_H
#define HPM_RTL8211_REGS_H

 /* RTL Register Definitions */
#define RTL8211_REG_BMCR    (0U)  /* Basic Mode Control Register */
#define RTL8211_REG_BMSR    (1U)  /* Basic Mode Status Register */
#define RTL8211_REG_PHYID1  (2U)  /* PHY Identifier Register 1 */
#define RTL8211_REG_PHYID2  (3U)  /* PHY Identifier Register 2 */
#define RTL8211_REG_ANAR    (4U)  /* Auto-Negotiation Advertising Register */
#define RTL8211_REG_ANLPAR  (5U)  /* Auto-Negotiation Link Partner Ability Register */
#define RTL8211_REG_ANER    (6U)  /* Auto-Negotiation Expansion Register */
#define RTL8211_REG_ANNPTR  (7U)  /* Auto-Negotiation Next Page Transmit Register */
#define RTL8211_REG_ANNPRR  (8U)  /* Auto-Negotiation Next Page Receive Register */
#define RTL8211_REG_GBCR    (9U)  /* 1000Base-T Control Register */
#define RTL8211_REG_GBSR    (10U) /* 1000Base-T Status Register */

#define RTL8211_REG_MACR    (13U) /* MMD Access Control Register */
#define RTL8211_REG_MAADR   (14U) /* MMD Access Address Data Register */
#define RTL8211_REG_GBESR   (15U) /* 1000Base-T Extended Status Register */
#define RTL8211_REG_PHYCR   (16U) /* PHY Specific Control Register */
#define RTL8211_REG_PHYSR   (17U) /* PHY Specific Status Register */
#define RTL8211_REG_INER    (18U) /* Interrupt Enable Register */
#define RTL8211_REG_INSR    (19U) /* Interrupt Status Register */
#define RTL8211_REG_RXERC   (24U) /* Receive Error Counter */
#define RTL8211_REG_PAGSEL  (31U) /* Page Select Register */

/* RTL MMD Register Definitions */
#define RTL8211_MMD_REG_PC1R    (0U)  /* PCS Control 1 Register */
#define RTL8211_MMD_REG_PS1R    (1U)  /* PCS Status 1 Register */
#define RTL8211_MMD_REG_EEECR   (20U) /* EEE Capability Register */
#define RTL8211_MMD_REG_EEEWER  (22U) /* EEE Wake Error Register */
#define RTL8211_MMD_REG_EEEAR   (60U) /* EEE Advertisement Register */
#define RTL8211_MMD_REG_EEELPAR (61U) /* EEE Link Partner Ability Register */

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
#define RTL8211_BMCR_RESET_MASK  (0x8000U)
#define RTL8211_BMCR_RESET_SHIFT (15U)
#define RTL8211_BMCR_RESET_SET(x) (((uint32_t)(x) << RTL8211_BMCR_RESET_SHIFT) & RTL8211_BMCR_RESET_MASK)
#define RTL8211_BMCR_RESET_GET(x) (((uint32_t)(x) & RTL8211_BMCR_RESET_MASK) >> RTL8211_BMCR_RESET_SHIFT)

/*
 * Loopback (RW)
 *
 * Loopback Mode.
 * 1: Enable PCS loopback mode
 * 0: Disable PCS loopback mode
 */
#define RTL8211_BMCR_LOOPBACK_MASK  (0x4000U)
#define RTL8211_BMCR_LOOPBACK_SHIFT (14U)
#define RTL8211_BMCR_LOOPBACK_SET(x) (((uint32_t)(x) << RTL8211_BMCR_LOOPBACK_SHIFT) & RTL8211_BMCR_LOOPBACK_MASK)
#define RTL8211_BMCR_LOOPBACK_GET(x) (((uint32_t)(x) & RTL8211_BMCR_LOOPBACK_MASK) >> RTL8211_BMCR_LOOPBACK_SHIFT)

/*
 * Speed[0] (RW)
 *
 * Speed Select Bit 0.
 * In forced mode, i.e., when Auto-Negotiation is disabled, bits 6 and 13
 * determine device speed selection.
 */
#define RTL8211_BMCR_SPEED0_MASK  (0x2000U)
#define RTL8211_BMCR_SPEED0_SHIFT (13U)
#define RTL8211_BMCR_SPEED0_SET(x) (((uint32_t)(x) << RTL8211_BMCR_SPEED0_SHIFT) & RTL8211_BMCR_SPEED0_MASK)
#define RTL8211_BMCR_SPEED0_GET(x) (((uint32_t)(x) & RTL8211_BMCR_SPEED0_MASK) >> RTL8211_BMCR_SPEED0_SHIFT)

/*
 * ANE (RW)
 *
 * Auto-Negotiation Enable.
 * 1: Enable Auto-Negotiation
 * 0: Disable Auto-Negotiation
 */
#define RTL8211_BMCR_ANE_MASK  (0x1000U)
#define RTL8211_BMCR_ANE_SHIFT (12U)
#define RTL8211_BMCR_ANE_SET(x) (((uint32_t)(x) << RTL8211_BMCR_ANE_SHIFT) & RTL8211_BMCR_ANE_MASK)
#define RTL8211_BMCR_ANE_GET(x) (((uint32_t)(x) & RTL8211_BMCR_ANE_MASK) >> RTL8211_BMCR_ANE_SHIFT)

/*
 * PWD (RW)
 *
 * Power Down.
 * 1: Power down (only Management Interface and logic are active; link
 * is down)
 * 0: Normal operation
 */
#define RTL8211_BMCR_PWD_MASK  (0x0800U)
#define RTL8211_BMCR_PWD_SHIFT (11U)
#define RTL8211_BMCR_PWD_SET(x) (((uint32_t)(x) << RTL8211_BMCR_PWD_SHIFT) & RTL8211_BMCR_PWD_MASK)
#define RTL8211_BMCR_PWD_GET(x) (((uint32_t)(x) & RTL8211_BMCR_PWD_MASK) >> RTL8211_BMCR_PWD_SHIFT)

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
#define RTL8211_BMCR_ISOLATE_MASK  (0x0400U)
#define RTL8211_BMCR_ISOLATE_SHIFT (10U)
#define RTL8211_BMCR_ISOLATE_SET(x) (((uint32_t)(x) << RTL8211_BMCR_ISOLATE_SHIFT) & RTL8211_BMCR_ISOLATE_MASK)
#define RTL8211_BMCR_ISOLATE_GET(x) (((uint32_t)(x) & RTL8211_BMCR_ISOLATE_MASK) >> RTL8211_BMCR_ISOLATE_SHIFT)

/*
 * Restart_AN (RW)
 *
 * Restart Auto-Negotiation.
 * 1: Restart Auto-Negotiation
 * 0: Normal operation
 */
#define RTL8211_BMCR_RESTART_AN_MASK  (0x0200U)
#define RTL8211_BMCR_RESTART_AN_SHIFT (9U)
#define RTL8211_BMCR_RESTART_AN_SET(x) (((uint32_t)(x) << RTL8211_BMCR_RESTART_AN_SHIFT) & RTL8211_BMCR_RESTART_AN_MASK)
#define RTL8211_BMCR_RESTART_AN_GET(x) (((uint32_t)(x) & RTL8211_BMCR_RESTART_AN_MASK) >> RTL8211_BMCR_RESTART_AN_SHIFT)

/*
 * Duplex (RW)
 *
 * Duplex Mode.
 * 1: Full Duplex operation
 * 0: Half Duplex operation
 * This bit is valid only in force mode, i.e., NWay is disabled.
 */
#define RTL8211_BMCR_DUPLEX_MASK  (0x0100U)
#define RTL8211_BMCR_DUPLEX_SHIFT (8U)
#define RTL8211_BMCR_DUPLEX_SET(x) (((uint32_t)(x) << RTL8211_BMCR_DUPLEX_SHIFT) & RTL8211_BMCR_DUPLEX_MASK)
#define RTL8211_BMCR_DUPLEX_GET(x) (((uint32_t)(x) & RTL8211_BMCR_DUPLEX_MASK) >> RTL8211_BMCR_DUPLEX_SHIFT)

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
#define RTL8211_BMCR_COLLISION_TEST_MASK  (0x0080U)
#define RTL8211_BMCR_COLLISION_TEST_SHIFT (7U)
#define RTL8211_BMCR_COLLISION_TEST_SET(x) (((uint32_t)(x) << RTL8211_BMCR_COLLISION_TEST_SHIFT) & RTL8211_BMCR_COLLISION_TEST_MASK)
#define RTL8211_BMCR_COLLISION_TEST_GET(x) (((uint32_t)(x) & RTL8211_BMCR_COLLISION_TEST_MASK) >> RTL8211_BMCR_COLLISION_TEST_SHIFT)

/*
 * Speed[1] (RW)
 *
 * Speed Select Bit 1.
 * Refer to bit 0.13.
 */
#define RTL8211_BMCR_SPEED1_MASK  (0x0040U)
#define RTL8211_BMCR_SPEED1_SHIFT (6U)
#define RTL8211_BMCR_SPEED1_SET(x) (((uint32_t)(x) << RTL8211_BMCR_SPEED1_SHIFT) & RTL8211_BMCR_SPEED1_MASK)
#define RTL8211_BMCR_SPEED1_GET(x) (((uint32_t)(x) & RTL8211_BMCR_SPEED1_MASK) >> RTL8211_BMCR_SPEED1_SHIFT)

/* Bitfield definition for register: PHYID1 */
/*
 * OUI_MSB (RO)
 *
 * Organizationally Unique Identifier Bit 3:18.
 * Always 0000000000011100.
 */
#define RTL8211_PHYID1_OUI_MSB_MASK  (0xFFFFU)
#define RTL8211_PHYID1_OUI_MSB_SHIFT (0U)
#define RTL8211_PHYID1_OUI_MSB_GET(x) (((uint32_t)(x) & RTL8211_PHYID1_OUI_MSB_MASK) >> RTL8211_PHYID1_OUI_MSB_SHIFT)

/* Bitfield definition for register: PHYID2 */
/*
 * OUI_LSB (RO)
 *
 * Organizationally Unique Identifier Bit 19:24.
 * Always 110010.
 */
#define RTL8211_PHYID2_OUI_MSB_MASK  (0xFC00U)
#define RTL8211_PHYID2_OUI_MSB_SHIFT (10U)
#define RTL8211_PHYID2_OUI_MSB_GET(x) (((uint32_t)(x) & RTL8211_PHYID2_OUI_MSB_MASK) >> RTL8211_PHYID2_OUI_MSB_SHIFT)

#endif /* HPM_RTL8211_REGS_H */