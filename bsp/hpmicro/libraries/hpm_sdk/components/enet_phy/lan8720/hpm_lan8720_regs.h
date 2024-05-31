/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_LAN8720_REGS_H
#define HPM_LAN8720_REGS_H

typedef enum {
    LAN8720_BMCR                        = 0,   /* 0x0: Basic Mode Control Register */
    LAN8720_BMSR                        = 1,   /* 0x1: Basic Mode Status Register */
    LAN8720_PHYID1                      = 2,   /* 0x2: PHY Identifier Register 1 */
    LAN8720_PHYID2                      = 3,   /* 0x3: PHY Identifier Register 2 */
    LAN8720_SMR                         = 18,  /* 0x12: Special Modes Register */
    LAN8720_SECR                        = 26,  /* 0x1A: Symbol Error Counter Register */
    LAN8720_ISFR                        = 29,  /* 0x1D: Interrupt Source Flag Register */
    LAN8720_IMR                         = 30,  /* 0x1E: Interrupt Mask Register */
    LAN8720_PSCSR                       = 31,  /* 0x1F: PHY Special Control/Status Register */
} LAN8720_REG_Type;


/* Bitfield definition for register: BMCR */
/*
 * RESET (RW/SC)
 *
 * 1 = software reset. Bit is self-clearing. When setting this bit do not set other
 * bits in this register. The configuration is set from the register bit values, and not
 * from the mode pins.
 */
#define LAN8720_BMCR_RESET_MASK (0x8000U)
#define LAN8720_BMCR_RESET_SHIFT (15U)
#define LAN8720_BMCR_RESET_SET(x) (((uint16_t)(x) << LAN8720_BMCR_RESET_SHIFT) & LAN8720_BMCR_RESET_MASK)
#define LAN8720_BMCR_RESET_GET(x) (((uint16_t)(x) & LAN8720_BMCR_RESET_MASK) >> LAN8720_BMCR_RESET_SHIFT)

/*
 * LOOPBACK (RW)
 *
 * 0 = normal operation
 * 1 = loopback mode
 */
#define LAN8720_BMCR_LOOPBACK_MASK (0x4000U)
#define LAN8720_BMCR_LOOPBACK_SHIFT (14U)
#define LAN8720_BMCR_LOOPBACK_SET(x) (((uint16_t)(x) << LAN8720_BMCR_LOOPBACK_SHIFT) & LAN8720_BMCR_LOOPBACK_MASK)
#define LAN8720_BMCR_LOOPBACK_GET(x) (((uint16_t)(x) & LAN8720_BMCR_LOOPBACK_MASK) >> LAN8720_BMCR_LOOPBACK_SHIFT)

/*
 * SPEED (RW)
 *
 * 0 = 10Mbps
 * 1 = 100Mbps
 * Ignored if Auto-negotiation is enabled (0.12 = 1).
 */
#define LAN8720_BMCR_SPEED_MASK (0x2000U)
#define LAN8720_BMCR_SPEED_SHIFT (13U)
#define LAN8720_BMCR_SPEED_SET(x) (((uint16_t)(x) << LAN8720_BMCR_SPEED_SHIFT) & LAN8720_BMCR_SPEED_MASK)
#define LAN8720_BMCR_SPEED_GET(x) (((uint16_t)(x) & LAN8720_BMCR_SPEED_MASK) >> LAN8720_BMCR_SPEED_SHIFT)

/*
 * ANE (RW)
 *
 * Auto-Negotiation Enable
 * 0 = disable auto-negotiate process
 * 1 = enable auto-negotiate process (overrides 0.13 and 0.8)
 */
#define LAN8720_BMCR_ANE_MASK (0x1000U)
#define LAN8720_BMCR_ANE_SHIFT (12U)
#define LAN8720_BMCR_ANE_SET(x) (((uint16_t)(x) << LAN8720_BMCR_ANE_SHIFT) & LAN8720_BMCR_ANE_MASK)
#define LAN8720_BMCR_ANE_GET(x) (((uint16_t)(x) & LAN8720_BMCR_ANE_MASK) >> LAN8720_BMCR_ANE_SHIFT)

/*
 * PWD (RW)
 *
 * 0 = normal operation
 * 1 = General power down mode
 * The Auto-Negotiation Enable must be cleared before setting the Power
 * Down.
 */
#define LAN8720_BMCR_PWD_MASK (0x800U)
#define LAN8720_BMCR_PWD_SHIFT (11U)
#define LAN8720_BMCR_PWD_SET(x) (((uint16_t)(x) << LAN8720_BMCR_PWD_SHIFT) & LAN8720_BMCR_PWD_MASK)
#define LAN8720_BMCR_PWD_GET(x) (((uint16_t)(x) & LAN8720_BMCR_PWD_MASK) >> LAN8720_BMCR_PWD_SHIFT)

/*
 * ISOLATE (RW)
 *
 * 0 = normal operation
 * 1 = electrical isolation of PHY from the RMII
 */
#define LAN8720_BMCR_ISOLATE_MASK (0x400U)
#define LAN8720_BMCR_ISOLATE_SHIFT (10U)
#define LAN8720_BMCR_ISOLATE_SET(x) (((uint16_t)(x) << LAN8720_BMCR_ISOLATE_SHIFT) & LAN8720_BMCR_ISOLATE_MASK)
#define LAN8720_BMCR_ISOLATE_GET(x) (((uint16_t)(x) & LAN8720_BMCR_ISOLATE_MASK) >> LAN8720_BMCR_ISOLATE_SHIFT)

/*
 * RESTART_AN (RW/SC)
 *
 * 0 = normal operation
 * 1 = restart auto-negotiate process
 * Bit is self-clearing.
 */
#define LAN8720_BMCR_RESTART_AN_MASK (0x200U)
#define LAN8720_BMCR_RESTART_AN_SHIFT (9U)
#define LAN8720_BMCR_RESTART_AN_SET(x) (((uint16_t)(x) << LAN8720_BMCR_RESTART_AN_SHIFT) & LAN8720_BMCR_RESTART_AN_MASK)
#define LAN8720_BMCR_RESTART_AN_GET(x) (((uint16_t)(x) & LAN8720_BMCR_RESTART_AN_MASK) >> LAN8720_BMCR_RESTART_AN_SHIFT)

/*
 * DUPLEX (RW)
 *
 * 0 = half duplex
 * 1 = full duplex
 * Ignored if Auto-Negotiation is enabled (0.12 = 1).
 */
#define LAN8720_BMCR_DUPLEX_MASK (0x100U)
#define LAN8720_BMCR_DUPLEX_SHIFT (8U)
#define LAN8720_BMCR_DUPLEX_SET(x) (((uint16_t)(x) << LAN8720_BMCR_DUPLEX_SHIFT) & LAN8720_BMCR_DUPLEX_MASK)
#define LAN8720_BMCR_DUPLEX_GET(x) (((uint16_t)(x) & LAN8720_BMCR_DUPLEX_MASK) >> LAN8720_BMCR_DUPLEX_SHIFT)

/* Bitfield definition for register: BMSR */
/*
 * 100BASE_T4 (RO)
 *
 * 0 = no T4 ability
 * 1 = T4 able
 */
#define LAN8720_BMSR_100BASE_T4_MASK (0x8000U)
#define LAN8720_BMSR_100BASE_T4_SHIFT (15U)
#define LAN8720_BMSR_100BASE_T4_GET(x) (((uint16_t)(x) & LAN8720_BMSR_100BASE_T4_MASK) >> LAN8720_BMSR_100BASE_T4_SHIFT)

/*
 * 100BASE_TX_FULL (RO)
 *
 * 0 = no TX full duplex ability
 * 1 = TX with full duplex
 */
#define LAN8720_BMSR_100BASE_TX_FULL_MASK (0x4000U)
#define LAN8720_BMSR_100BASE_TX_FULL_SHIFT (14U)
#define LAN8720_BMSR_100BASE_TX_FULL_GET(x) (((uint16_t)(x) & LAN8720_BMSR_100BASE_TX_FULL_MASK) >> LAN8720_BMSR_100BASE_TX_FULL_SHIFT)

/*
 * 100BASE_TX_HALF (RO)
 *
 * 0 = no TX half duplex ability
 * 1 = TX with half duplex
 */
#define LAN8720_BMSR_100BASE_TX_HALF_MASK (0x2000U)
#define LAN8720_BMSR_100BASE_TX_HALF_SHIFT (13U)
#define LAN8720_BMSR_100BASE_TX_HALF_GET(x) (((uint16_t)(x) & LAN8720_BMSR_100BASE_TX_HALF_MASK) >> LAN8720_BMSR_100BASE_TX_HALF_SHIFT)

/*
 * 10BASE_T_FULL (RO)
 *
 * 0 = no 10Mbps with full duplex ability
 * 1 = 10Mbps with full duplex
 */
#define LAN8720_BMSR_10BASE_T_FULL_MASK (0x1000U)
#define LAN8720_BMSR_10BASE_T_FULL_SHIFT (12U)
#define LAN8720_BMSR_10BASE_T_FULL_GET(x) (((uint16_t)(x) & LAN8720_BMSR_10BASE_T_FULL_MASK) >> LAN8720_BMSR_10BASE_T_FULL_SHIFT)

/*
 * 10BASE_T_HALF (RO)
 *
 * 0 = no 10Mbps with half duplex ability
 * 1 = 10Mbps with half duplex
 */
#define LAN8720_BMSR_10BASE_T_HALF_MASK (0x800U)
#define LAN8720_BMSR_10BASE_T_HALF_SHIFT (11U)
#define LAN8720_BMSR_10BASE_T_HALF_GET(x) (((uint16_t)(x) & LAN8720_BMSR_10BASE_T_HALF_MASK) >> LAN8720_BMSR_10BASE_T_HALF_SHIFT)

/*
 * 100BASE_T2_FULL (RO)
 *
 * 0 = PHY not able to perform full duplex 100BASE-T2
 * 1 = PHY able to perform full duplex 100BASE-T2
 */
#define LAN8720_BMSR_100BASE_T2_FULL_MASK (0x400U)
#define LAN8720_BMSR_100BASE_T2_FULL_SHIFT (10U)
#define LAN8720_BMSR_100BASE_T2_FULL_GET(x) (((uint16_t)(x) & LAN8720_BMSR_100BASE_T2_FULL_MASK) >> LAN8720_BMSR_100BASE_T2_FULL_SHIFT)

/*
 * 100BASE_T2_HALF (RO)
 *
 * 0 = PHY not able to perform half duplex 100BASE-T2
 * 1 = PHY able to perform half duplex 100BASE-T2
 */
#define LAN8720_BMSR_100BASE_T2_HALF_MASK (0x200U)
#define LAN8720_BMSR_100BASE_T2_HALF_SHIFT (9U)
#define LAN8720_BMSR_100BASE_T2_HALF_GET(x) (((uint16_t)(x) & LAN8720_BMSR_100BASE_T2_HALF_MASK) >> LAN8720_BMSR_100BASE_T2_HALF_SHIFT)

/*
 * EXTENDED_STATUS (RO)
 *
 * 0 = no extended status information in register 15
 * 1 = extended status information in register 15
 */
#define LAN8720_BMSR_EXTENDED_STATUS_MASK (0x100U)
#define LAN8720_BMSR_EXTENDED_STATUS_SHIFT (8U)
#define LAN8720_BMSR_EXTENDED_STATUS_GET(x) (((uint16_t)(x) & LAN8720_BMSR_EXTENDED_STATUS_MASK) >> LAN8720_BMSR_EXTENDED_STATUS_SHIFT)

/*
 * AUTO_NEGOTIATION_COMPLETE (RO)
 *
 * 0 = auto-negotiate process not completed
 * 1 = auto-negotiate process completed
 */
#define LAN8720_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK (0x20U)
#define LAN8720_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT (5U)
#define LAN8720_BMSR_AUTO_NEGOTIATION_COMPLETE_GET(x) (((uint16_t)(x) & LAN8720_BMSR_AUTO_NEGOTIATION_COMPLETE_MASK) >> LAN8720_BMSR_AUTO_NEGOTIATION_COMPLETE_SHIFT)

/*
 * REMOTE_FAULT (RC)
 *
 * 1 = remote fault condition detected
 * 0 = no remote fault
 */
#define LAN8720_BMSR_REMOTE_FAULT_MASK (0x10U)
#define LAN8720_BMSR_REMOTE_FAULT_SHIFT (4U)
#define LAN8720_BMSR_REMOTE_FAULT_GET(x) (((uint16_t)(x) & LAN8720_BMSR_REMOTE_FAULT_MASK) >> LAN8720_BMSR_REMOTE_FAULT_SHIFT)

/*
 * AUTO_NEGOTIATION_ABILITY (RO)
 *
 * 0 = unable to perform auto-negotiation function
 * 1 = able to perform auto-negotiation function
 */
#define LAN8720_BMSR_AUTO_NEGOTIATION_ABILITY_MASK (0x8U)
#define LAN8720_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT (3U)
#define LAN8720_BMSR_AUTO_NEGOTIATION_ABILITY_GET(x) (((uint16_t)(x) & LAN8720_BMSR_AUTO_NEGOTIATION_ABILITY_MASK) >> LAN8720_BMSR_AUTO_NEGOTIATION_ABILITY_SHIFT)

/*
 * LINK_STATUS (RO)
 *
 * 0 = link is down
 * 1 = link is up
 */
#define LAN8720_BMSR_LINK_STATUS_MASK (0x4U)
#define LAN8720_BMSR_LINK_STATUS_SHIFT (2U)
#define LAN8720_BMSR_LINK_STATUS_GET(x) (((uint16_t)(x) & LAN8720_BMSR_LINK_STATUS_MASK) >> LAN8720_BMSR_LINK_STATUS_SHIFT)

/*
 * JABBER_DETECT (RO)
 *
 * 0 = no jabber condition detected
 * 1 = jabber condition detected
 */
#define LAN8720_BMSR_JABBER_DETECT_MASK (0x2U)
#define LAN8720_BMSR_JABBER_DETECT_SHIFT (1U)
#define LAN8720_BMSR_JABBER_DETECT_GET(x) (((uint16_t)(x) & LAN8720_BMSR_JABBER_DETECT_MASK) >> LAN8720_BMSR_JABBER_DETECT_SHIFT)

/*
 * EXTENDED_CAPABILITY (RO)
 *
 * 0 = does not support extended capabilities registers
 * 1 = supports extended capabilities registers
 */
#define LAN8720_BMSR_EXTENDED_CAPABILITY_MASK (0x1U)
#define LAN8720_BMSR_EXTENDED_CAPABILITY_SHIFT (0U)
#define LAN8720_BMSR_EXTENDED_CAPABILITY_GET(x) (((uint16_t)(x) & LAN8720_BMSR_EXTENDED_CAPABILITY_MASK) >> LAN8720_BMSR_EXTENDED_CAPABILITY_SHIFT)

/* Bitfield definition for register: PHYID1 */
/*
 * OUI_MSB (RO)
 *
 * Assigned to the 3rd through 18th bits of the Organizationally Unique Identifier
 * (OUI), respectively.
 */
#define LAN8720_PHYID1_OUI_MSB_MASK (0xFFFFU)
#define LAN8720_PHYID1_OUI_MSB_SHIFT (0U)
#define LAN8720_PHYID1_OUI_MSB_GET(x) (((uint16_t)(x) & LAN8720_PHYID1_OUI_MSB_MASK) >> LAN8720_PHYID1_OUI_MSB_SHIFT)

/* Bitfield definition for register: PHYID2 */
/*
 * OUI_LSB (RO)
 *
 * Assigned to the 19th through 24th bits of the OUI.
 */
#define LAN8720_PHYID2_OUI_LSB_MASK (0xFC00U)
#define LAN8720_PHYID2_OUI_LSB_SHIFT (10U)
#define LAN8720_PHYID2_OUI_LSB_GET(x) (((uint16_t)(x) & LAN8720_PHYID2_OUI_LSB_MASK) >> LAN8720_PHYID2_OUI_LSB_SHIFT)

/*
 * MODEL_NUMBER (RO)
 *
 * Six-bit manufacturer’s model number.
 */
#define LAN8720_PHYID2_MODEL_NUMBER_MASK (0x3F0U)
#define LAN8720_PHYID2_MODEL_NUMBER_SHIFT (4U)
#define LAN8720_PHYID2_MODEL_NUMBER_GET(x) (((uint16_t)(x) & LAN8720_PHYID2_MODEL_NUMBER_MASK) >> LAN8720_PHYID2_MODEL_NUMBER_SHIFT)

/*
 * REVISION_NUMBER (RO)
 *
 * Four-bit manufacturer’s revision number.
 */
#define LAN8720_PHYID2_REVISION_NUMBER_MASK (0xFU)
#define LAN8720_PHYID2_REVISION_NUMBER_SHIFT (0U)
#define LAN8720_PHYID2_REVISION_NUMBER_GET(x) (((uint16_t)(x) & LAN8720_PHYID2_REVISION_NUMBER_MASK) >> LAN8720_PHYID2_REVISION_NUMBER_SHIFT)

/* Bitfield definition for register: SMR */
/*
 * MODE (R/W)
 *
 * Transceiver mode of operation
 */
#define LAN8720_SMR_MODE_MASK (0xE0U)
#define LAN8720_SMR_MODE_SHIFT (5U)
#define LAN8720_SMR_MODE_SET(x) (((uint16_t)(x) << LAN8720_SMR_MODE_SHIFT) & LAN8720_SMR_MODE_MASK)
#define LAN8720_SMR_MODE_GET(x) (((uint16_t)(x) & LAN8720_SMR_MODE_MASK) >> LAN8720_SMR_MODE_SHIFT)

/*
 * PHYAD (R/W)
 *
 * PHY Address. The PHY Address is used for the SMI address and for initial-
 * ization of the Cipher (Scrambler) key.
 */
#define LAN8720_SMR_PHYAD_MASK (0x1FU)
#define LAN8720_SMR_PHYAD_SHIFT (0U)
#define LAN8720_SMR_PHYAD_SET(x) (((uint16_t)(x) << LAN8720_SMR_PHYAD_SHIFT) & LAN8720_SMR_PHYAD_MASK)
#define LAN8720_SMR_PHYAD_GET(x) (((uint16_t)(x) & LAN8720_SMR_PHYAD_MASK) >> LAN8720_SMR_PHYAD_SHIFT)

/* Bitfield definition for register: SECR */
/*
 * SYM_ERR_CNT (RO)
 *
 * The symbol error counter increments whenever an invalid code symbol is
 * received (including IDLE symbols) in 100BASE-TX mode. The counter is
 * incremented only once per packet, even when the received packet contains
 * more than one symbol error. This counter increments up to 65,536 (2^16) and
 * rolls over to 0 after reaching the maximum value.
 * Note: This register is cleared on reset, but is not cleared by reading the
 * register. This register does not increment in 10BASE-T mode.
 */
#define LAN8720_SECR_SYM_ERR_CNT_MASK (0xFFFFU)
#define LAN8720_SECR_SYM_ERR_CNT_SHIFT (0U)
#define LAN8720_SECR_SYM_ERR_CNT_GET(x) (((uint16_t)(x) & LAN8720_SECR_SYM_ERR_CNT_MASK) >> LAN8720_SECR_SYM_ERR_CNT_SHIFT)

/* Bitfield definition for register: ISFR */
/*
 * INT7 (RO)
 *
 * 0 = not source of interrupt
 * 1 = ENERGYON generated
 */
#define LAN8720_ISFR_INT7_MASK (0x80U)
#define LAN8720_ISFR_INT7_SHIFT (7U)
#define LAN8720_ISFR_INT7_GET(x) (((uint16_t)(x) & LAN8720_ISFR_INT7_MASK) >> LAN8720_ISFR_INT7_SHIFT)

/*
 * INT6 (RO)
 *
 * 0 = not source of interrupt
 * 1 = Auto-Negotiation complete
 */
#define LAN8720_ISFR_INT6_MASK (0x40U)
#define LAN8720_ISFR_INT6_SHIFT (6U)
#define LAN8720_ISFR_INT6_GET(x) (((uint16_t)(x) & LAN8720_ISFR_INT6_MASK) >> LAN8720_ISFR_INT6_SHIFT)

/*
 * INT5 (RO)
 *
 * 0 = not source of interrupt
 * 1 = Remote Fault Detected
 */
#define LAN8720_ISFR_INT5_MASK (0x20U)
#define LAN8720_ISFR_INT5_SHIFT (5U)
#define LAN8720_ISFR_INT5_GET(x) (((uint16_t)(x) & LAN8720_ISFR_INT5_MASK) >> LAN8720_ISFR_INT5_SHIFT)

/*
 * INT4 (RO)
 *
 * 0 = not source of interrupt
 * 1 = Link Down (link status negated)
 */
#define LAN8720_ISFR_INT4_MASK (0x10U)
#define LAN8720_ISFR_INT4_SHIFT (4U)
#define LAN8720_ISFR_INT4_GET(x) (((uint16_t)(x) & LAN8720_ISFR_INT4_MASK) >> LAN8720_ISFR_INT4_SHIFT)

/*
 * INT3 (RO)
 *
 * 0 = not source of interrupt
 * 1 = Auto-Negotiation LP Acknowledge
 */
#define LAN8720_ISFR_INT3_MASK (0x8U)
#define LAN8720_ISFR_INT3_SHIFT (3U)
#define LAN8720_ISFR_INT3_GET(x) (((uint16_t)(x) & LAN8720_ISFR_INT3_MASK) >> LAN8720_ISFR_INT3_SHIFT)

/*
 * INT2 (RO)
 *
 * 0 = not source of interrupt
 * 1 = Parallel Detection Fault
 */
#define LAN8720_ISFR_INT2_MASK (0x4U)
#define LAN8720_ISFR_INT2_SHIFT (2U)
#define LAN8720_ISFR_INT2_GET(x) (((uint16_t)(x) & LAN8720_ISFR_INT2_MASK) >> LAN8720_ISFR_INT2_SHIFT)

/*
 * INT1 (RO)
 *
 * 0 = not source of interrupt
 * 1 = Auto-Negotiation Page Received
 */
#define LAN8720_ISFR_INT1_MASK (0x2U)
#define LAN8720_ISFR_INT1_SHIFT (1U)
#define LAN8720_ISFR_INT1_GET(x) (((uint16_t)(x) & LAN8720_ISFR_INT1_MASK) >> LAN8720_ISFR_INT1_SHIFT)

/* Bitfield definition for register: IMR */
/*
 * MASK (R/W)
 *
 * 0 = interrupt source is masked
 * 1 = interrupt source is enabled
 */
#define LAN8720_IMR_MASK_MASK (0xFEU)
#define LAN8720_IMR_MASK_SHIFT (1U)
#define LAN8720_IMR_MASK_SET(x) (((uint16_t)(x) << LAN8720_IMR_MASK_SHIFT) & LAN8720_IMR_MASK_MASK)
#define LAN8720_IMR_MASK_GET(x) (((uint16_t)(x) & LAN8720_IMR_MASK_MASK) >> LAN8720_IMR_MASK_SHIFT)

/* Bitfield definition for register: PSCSR */
/*
 * AUTODONE (RO)
 *
 * 0 = Auto-negotiation is not done or disabled (or not active)
 * 1 = Auto-negotiation is done
 */
#define LAN8720_PSCSR_AUTODONE_MASK (0x1000U)
#define LAN8720_PSCSR_AUTODONE_SHIFT (12U)
#define LAN8720_PSCSR_AUTODONE_GET(x) (((uint16_t)(x) & LAN8720_PSCSR_AUTODONE_MASK) >> LAN8720_PSCSR_AUTODONE_SHIFT)

/*
 * DUPLEX (RO)
 *
 * 0: Half duplex
 * 1: Full duplex
 */
#define LAN8720_PSCSR_DUPLEX_MASK (0x10U)
#define LAN8720_PSCSR_DUPLEX_SHIFT (4U)
#define LAN8720_PSCSR_DUPLEX_GET(x) (((uint16_t)(x) & LAN8720_PSCSR_DUPLEX_MASK) >> LAN8720_PSCSR_DUPLEX_SHIFT)

/*
 * SPEED (RO)
 *
 * HCDSPEED value:
 * 01 = 10BASE-T
 * 10 = 100BASE-TX
 */
#define LAN8720_PSCSR_SPEED_MASK (0xCU)
#define LAN8720_PSCSR_SPEED_SHIFT (2U)
#define LAN8720_PSCSR_SPEED_GET(x) (((uint16_t)(x) & LAN8720_PSCSR_SPEED_MASK) >> LAN8720_PSCSR_SPEED_SHIFT)




#endif /* HPM_LAN8720_REGS_H */