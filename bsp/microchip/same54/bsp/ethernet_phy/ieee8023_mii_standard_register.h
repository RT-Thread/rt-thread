/**
 * \file
 *
 * \brief IEEE802.3 MII Management Standard Register Set
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifndef ETHERNET_MII_REGISTER_H_INCLUDED
#define ETHERNET_MII_REGISTER_H_INCLUDED

/* IEEE 802.3 Clause22.2.4 defined Standard Registers.
 * The MII basic register set consists of two registers referred to as the
 * Control register (Register 0) and the Status register (Register 1). All
 * PHYs that provide an MII shall incorporate the basic register set. All PHYs
 * that provide a GMII shall incorporate an extended basic register set
 * consisting of the Control register (Register 0), Status register
 * (Register 1), and Extended Status register (Register 15). The status and
 * control functions defined here are considered basic and fundamental to
 * 100 Mb/s and 1000 Mb/s PHYs. Registers 2 through 14 are part of the
 * extended register set. The format of Registers 4 through 10 are defined for
 * the specific Auto-Negotiation protocol used (Clause 28 or Clause 37). The
 * format of these registers is selected by the bit settings of Registers 1
 * and 15.
 **/
#define MDIO_REG0_BMCR 0x00    /*  Basic Control */
#define MDIO_REG1_BMSR 0x01    /*  Basic Status */
#define MDIO_REG2_PHYID1 0x02  /*  PHY Idendifier 1 */
#define MDIO_REG3_PHYID2 0x03  /*  PHY Idendifier 2 */
#define MDIO_REG4_ANA 0x04     /*  Auto_Negotiation Advertisement */
#define MDIO_REG5_ANLPA 0x05   /*  Auto_negotiation Link Partner Base Page Ability */
#define MDIO_REG6_ANE 0x06     /*  Auto-negotiation Expansion */
#define MDIO_REG7_ANNPT 0x07   /*  Auto-negotiation Next Page Transmit */
#define MDIO_REG8_ANLPRNP 0x08 /*  Auto-Negotiation Link Partner Received Next Page */
#define MDIO_REG9_MSC 0x09     /*  MASTER-SLAVE Control Register */
#define MDIO_REG10_MSS 0x0A    /*  MASTER-SLAVE Status Register */
#define MDIO_REG11_PSEC 0x0B   /*  PSE Control Register */
#define MDIO_REG12_PSES 0x0C   /*  PSE Status Register */
#define MDIO_REG13_MMDAC 0x0D  /*  MMD Access Control Register */
#define MDIO_REG14_MMDAAD 0x0E /*  MMD Access Address Data Register */
#define MDIO_REG15_EXTS 0x0F   /*  Extended Status */
/* Register 16 to 31 are Reserved for Vendor Specific */

/* Bit definitions: MDIO_REG0_BMCR 0x00 Basic Control */
#define MDIO_REG0_BIT_RESET (1 << 15)            /*  1 = Software Reset; 0 = Normal Operation */
#define MDIO_REG0_BIT_LOOPBACK (1 << 14)         /*  1 = loopback Enabled; 0 = Normal Operation */
#define MDIO_REG0_BIT_SPEED_SELECT_LSB (1 << 13) /*  1 = 100Mbps; 0=10Mbps */
#define MDIO_REG0_BIT_AUTONEG (1 << 12)          /*  1 = Auto-negotiation Enable */
#define MDIO_REG0_BIT_POWER_DOWN (1 << 11)       /*  1 = Power down 0=Normal operation */
#define MDIO_REG0_BIT_ISOLATE (1 << 10)          /*  1 = Isolates 0 = Normal operation */
#define MDIO_REG0_BIT_RESTART_AUTONEG (1 << 9)   /*  1 = Restart auto-negotiation 0 = Normal operation */
#define MDIO_REG0_BIT_DUPLEX_MODE (1 << 8)       /*  1 = Full duplex operation 0 = Normal operation */
#define MDIO_REG0_BIT_COLLISION_TEST (1 << 7)    /*  1 = Enable COL test; 0 = Disable COL test */
#define MDIO_REG0_BIT_SPEED_SELECT_MSB (1 << 6)  /*  1 with LSB0 = 1000Mbps */
#define MDIO_REG0_BIT_UNIDIR_ENABLE (1 << 5)     /*  Unidirectional Enable */
/* Reserved                     4 to 0       Read as 0, ignore on write */

/* Bit definitions: MDIO_BMSR 0x01 Basic Status */
#define MDIO_REG1_BIT_100BASE_T4 (1 << 15)     /*  100BASE-T4 Capable */
#define MDIO_REG1_BIT_100BASE_TX_FD (1 << 14)  /*  100BASE-TX Full Duplex Capable */
#define MDIO_REG1_BIT_100BASE_TX_HD (1 << 13)  /*  100BASE-TX Half Duplex Capable */
#define MDIO_REG1_BIT_10BASE_T_FD (1 << 12)    /*  10BASE-T Full Duplex Capable */
#define MDIO_REG1_BIT_10BASE_T_HD (1 << 11)    /*  10BASE-T Half Duplex Capable */
#define MDIO_REG1_BIT_100BASE_T2_FD (1 << 10)  /*  1000BASE-T2 Full Duplex Capable */
#define MDIO_REG1_BIT_100BASE_T2_HD (1 << 9)   /*  1000BASE-T2 Half Duplex Capable */
#define MDIO_REG1_BIT_EXTEND_STATUS (1 << 8)   /*  1 = Extend Status Information In Reg 15 */
#define MDIO_REG1_BIT_UNIDIR_ABILITY (1 << 7)  /*  Unidirectional ability */
#define MDIO_REG1_BIT_MF_PREAMB_SUPPR (1 << 6) /*  MII Frame Preamble Suppression */
#define MDIO_REG1_BIT_AUTONEG_COMP (1 << 5)    /*  Auto-negotiation Complete */
#define MDIO_REG1_BIT_REMOTE_FAULT (1 << 4)    /*  Remote Fault */
#define MDIO_REG1_BIT_AUTONEG_ABILITY (1 << 3) /*  Auto Configuration Ability */
#define MDIO_REG1_BIT_LINK_STATUS (1 << 2)     /*  Link Status */
#define MDIO_REG1_BIT_JABBER_DETECT (1 << 1)   /*  Jabber Detect */
#define MDIO_REG1_BIT_EXTEND_CAPAB (1 << 0)    /*  Extended Capability */

/*  Bit definitions: MDIO_PHYID1 0x02 PHY Idendifier 1 */
/*  Bit definitions: MDIO_PHYID2 0x03 PHY Idendifier 2 */
#define MDIO_LSB_MASK 0x3F
#define MDIO_OUI_MSB 0x0022
#define MDIO_OUI_LSB 0x1572

/* Bit definitions: MDIO_REG4_ANA 0x04 Auto-Negotiation advertisement */
#define MDIO_REG4_BIT_NEXTPAGE (15 << 0)     /* Next Page */
#define MDIO_REG4_BIT_REMOTE_FAULT (13 << 0) /* Remote Fault */
#define MDIO_REG4_BIT_EXT_NEXTPAGE (12 << 0) /* Extended Next Page */

/*  Bit definitions: MDIO_ANAR   0x04 Auto_Negotiation Advertisement */
/*  Bit definitions: MDIO_ANLPAR 0x05 Auto_negotiation Link Partner Ability */
#define MDIO_NP (1 << 15)         /*  Next page Indication */
#define MDIO_RF (1 << 13)         /*  Remote Fault */
#define MDIO_PAUSE_MASK (3 << 10) /*  0,0 = No Pause 1,0 = Asymmetric Pause(link partner) */
                                  /*  0,1 = Symmetric Pause 1,1 = Symmetric&Asymmetric Pause(local device) */
#define MDIO_100T4 (1 << 9)       /*  100BASE-T4 Support */
#define MDIO_100TX_FDX (1 << 8)   /*  100BASE-TX Full Duplex Support */
#define MDIO_100TX_HDX (1 << 7)   /*  100BASE-TX Half Duplex Support */
#define MDIO_10_FDX (1 << 6)      /*  10BASE-T Full Duplex Support */
#define MDIO_10_HDX (1 << 5)      /*  10BASE-T Half Duplex Support */
#define MDIO_AN_IEEE_802_3 0x0001 /*  [00001] = IEEE 802.3 */

/* Bit definitions: MDIO_ANER 0x06 Auto-negotiation Expansion */
#define MDIO_PDF (1 << 4)        /*  Local Device Parallel Detection Fault */
#define MDIO_LP_NP_ABLE (1 << 3) /*  Link Partner Next Page Able */
#define MDIO_NP_ABLE (1 << 2)    /*  Local Device Next Page Able */
#define MDIO_PAGE_RX (1 << 1)    /*  New Page Received */
#define MDIO_LP_AN_ABLE (1 << 0) /*  Link Partner Auto-negotiation Able */

/* Bit definitions: MDIO_PCR1 0x1E PHY Control 1 */
#define MDIO_OMI_10BASE_T_HD 0x0001
#define MDIO_OMI_100BASE_TX_HD 0x0002
#define MDIO_OMI_10BASE_T_FD 0x0005

#endif /* #ifndef ETHERNET_MII_REGISTER_H_INCLUDED */
