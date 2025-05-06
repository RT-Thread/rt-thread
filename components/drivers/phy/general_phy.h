
/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-08     zhujiale    the first version
 */
#ifndef __PHY_GENERAL_H__
#define __PHY_GENERAL_H__
/* The forced speed, 10Mb, 100Mb, gigabit, 2.5Gb, 10GbE. */
#define SPEED_10        10
#define SPEED_100       100
#define SPEED_1000      1000
#define SPEED_2500      2500
#define SPEED_10000     10000
/* Advertisement control register. */
#define RT_ADVERTISE_SLCT       0x001f  /* Selector bits               */
#define RT_ADVERTISE_CSMA       0x0001  /* Only selector supported     */
#define RT_ADVERTISE_10HALF     0x0020  /* Try for 10mbps half-duplex  */
#define RT_ADVERTISE_1000XFULL  0x0020  /* Try for 1000BASE-X full-duplex */
#define RT_ADVERTISE_10FULL     0x0040  /* Try for 10mbps full-duplex  */
#define RT_ADVERTISE_1000XHALF  0x0040  /* Try for 1000BASE-X half-duplex */
#define RT_ADVERTISE_100HALF    0x0080  /* Try for 100mbps half-duplex */
#define RT_ADVERTISE_1000XPAUSE 0x0080  /* Try for 1000BASE-X pause    */
#define RT_ADVERTISE_100FULL    0x0100  /* Try for 100mbps full-duplex */
#define RT_ADVERTISE_1000XPSE_ASYM  0x0100  /* Try for 1000BASE-X asym pause */
#define RT_ADVERTISE_100BASE4   0x0200  /* Try for 100mbps 4k packets  */
#define RT_ADVERTISE_PAUSE_CAP  0x0400  /* Try for pause               */
#define RT_ADVERTISE_PAUSE_ASYM 0x0800  /* Try for asymetric pause     */
#define RT_ADVERTISE_RESV       0x1000  /* Unused...                   */
#define RT_ADVERTISE_RFAULT     0x2000  /* Say we can detect faults    */
#define RT_ADVERTISE_LPACK      0x4000  /* Ack link partners response  */
#define RT_ADVERTISE_NPAGE      0x8000  /* Next page bit               */

#define RT_ADVERTISE_FULL       (RT_ADVERTISE_100FULL | RT_ADVERTISE_10FULL | \
                 RT_ADVERTISE_CSMA)
#define RT_ADVERTISE_ALL        (RT_ADVERTISE_10HALF | RT_ADVERTISE_10FULL | \
                 RT_ADVERTISE_100HALF | RT_ADVERTISE_100FULL)

/* Indicates what features are advertised by the interface. */
#define RT_ADVERTISED__10baseT_Half     (1 << 0)
#define RT_ADVERTISED__10baseT_Full     (1 << 1)
#define RT_ADVERTISED__100baseT_Half    (1 << 2)
#define RT_ADVERTISED__100baseT_Full    (1 << 3)
#define RT_ADVERTISED__1000baseT_Half   (1 << 4)
#define RT_ADVERTISED__1000baseT_Full   (1 << 5)
#define RT_ADVERTISED__Autoneg          (1 << 6)
#define RT_ADVERTISED__TP               (1 << 7)
#define RT_ADVERTISED__AUI              (1 << 8)
#define RT_ADVERTISED__MII              (1 << 9)
#define RT_ADVERTISED__FIBRE            (1 << 10)
#define RT_ADVERTISED__BNC              (1 << 11)
#define RT_ADVERTISED__10000baseT_Full  (1 << 12)
#define RT_ADVERTISED__Pause            (1 << 13)
#define RT_ADVERTISED__Asym_Pause       (1 << 14)
#define RT_ADVERTISED__2500baseX_Full   (1 << 15)
#define RT_ADVERTISED__Backplane        (1 << 16)
#define RT_ADVERTISED__1000baseKX_Full  (1 << 17)
#define RT_ADVERTISED__10000baseKX4_Full    (1 << 18)
#define RT_ADVERTISED__10000baseKR_Full (1 << 19)
#define RT_ADVERTISED__10000baseR_FEC   (1 << 20)
#define RT_ADVERTISED__1000baseX_Half   (1 << 21)
#define RT_ADVERTISED__1000baseX_Full   (1 << 22)

/* Basic mode status register. */
#define RT_BMSR_ERCAP       0x0001  /* Ext-reg capability          */
#define RT_BMSR_JCD         0x0002  /* Jabber detected             */
#define RT_BMSR_LSTATUS     0x0004  /* Link status                 */
#define RT_BMSR_ANEGCAPABLE 0x0008  /* Able to do auto-negotiation */
#define RT_BMSR_RFAULT      0x0010  /* Remote fault detected       */
#define RT_BMSR_ANEGCOMPLETE    0x0020  /* Auto-negotiation complete   */
#define RT_BMSR_RESV        0x00c0  /* Unused...                   */
#define RT_BMSR_ESTATEN     0x0100  /* Extended Status in R15      */
#define RT_BMSR_100HALF2    0x0200  /* Can do 100BASE-T2 HDX       */
#define RT_BMSR_100FULL2    0x0400  /* Can do 100BASE-T2 FDX       */
#define RT_BMSR_10HALF      0x0800  /* Can do 10mbps, half-duplex  */
#define RT_BMSR_10FULL      0x1000  /* Can do 10mbps, full-duplex  */
#define RT_BMSR_100HALF     0x2000  /* Can do 100mbps, half-duplex */
#define RT_BMSR_100FULL     0x4000  /* Can do 100mbps, full-duplex */
#define RT_BMSR_100BASE4    0x8000  /* Can do 100mbps, 4k packets  */
/* 1000BASE-T Control register */
#define RT_ADVERTISE_1000FULL   0x0200  /* Advertise 1000BASE-T full duplex */
#define RT_ADVERTISE_1000HALF   0x0100  /* Advertise 1000BASE-T half duplex */
#define CTL1000_AS_MASTER       0x0800
#define CTL1000_ENABLE_MASTER   0x1000

/* Duplex, half or full. */
#define DUPLEX_HALF     0x00
#define DUPLEX_FULL     0x01

#define AUTONEG_DISABLE         0x00
#define AUTONEG_ENABLE          0x01
#define RT_PHY_1000BTSR_MSCF    0x8000
#define RT_PHY_1000BTSR_MSCR    0x4000
#define RT_PHY_1000BTSR_LRS     0x2000
#define RT_PHY_1000BTSR_RRS     0x1000
#define RT_PHY_1000BTSR_1000FD  0x0800
#define RT_PHY_1000BTSR_1000HD  0x0400

/* Link partner ability register. */
#define RT_LINK_PARTNER__SLCT           0x001f  /* Same as advertise selector  */
#define RT_LINK_PARTNER__10HALF         0x0020  /* Can do 10mbps half-duplex   */
#define RT_LINK_PARTNER__1000XFULL      0x0020  /* Can do 1000BASE-X full-duplex */
#define RT_LINK_PARTNER__10FULL         0x0040  /* Can do 10mbps full-duplex   */
#define RT_LINK_PARTNER__1000XHALF      0x0040  /* Can do 1000BASE-X half-duplex */
#define RT_LINK_PARTNER__100HALF        0x0080  /* Can do 100mbps half-duplex  */
#define RT_LINK_PARTNER__1000XPAUSE     0x0080  /* Can do 1000BASE-X pause     */
#define RT_LINK_PARTNER__100FULL        0x0100  /* Can do 100mbps full-duplex  */
#define RT_LINK_PARTNER__1000XPAUSE_ASYM    0x0100  /* Can do 1000BASE-X pause asym*/
#define RT_LINK_PARTNER__100BASE4       0x0200  /* Can do 100mbps 4k packets   */
#define RT_LINK_PARTNER__PAUSE_CAP      0x0400  /* Can pause                   */
#define RT_LINK_PARTNER__PAUSE_ASYM     0x0800  /* Can pause asymetrically     */
#define RT_LINK_PARTNER__RESV           0x1000  /* Unused...                   */
#define RT_LINK_PARTNER__RFAULT         0x2000  /* Link partner faulted        */
#define RT_LINK_PARTNER__LPACK          0x4000  /* Link partner acked us       */
#define RT_LINK_PARTNER__NPAGE          0x8000  /* Next page bit               */

#define RT_LINK_PARTNER__DUPLEX     (RT_LINK_PARTNER__10FULL | RT_LINK_PARTNER__100FULL)
#define RT_LINK_PARTNER__100            (RT_LINK_PARTNER__100FULL | RT_LINK_PARTNER__100HALF | RT_LINK_PARTNER__100BASE4)
/* Expansion register for auto-negotiation. */
#define RT_EXPANSION_REG_NWAY           0x0001  /* Can do N-way auto-nego      */
#define RT_EXPANSION_REG_LCWP           0x0002  /* Got new RX page code word   */
#define RT_EXPANSION_REG_ENABLENPAGE    0x0004  /* This enables npage words    */
#define RT_EXPANSION_REG_NPCAPABLE      0x0008  /* Link partner supports npage */
#define RT_EXPANSION_REG_MFAULTS        0x0010  /* Multiple faults detected    */
#define RT_EXPANSION_REG_RESV           0xffe0  /* Unused...                   */

#define RT_SUPORT_1000B_XFULL   0x8000  /* Can do 1000BX Full */
#define RT_SUPORT_1000B_XHALF   0x4000  /* Can do 1000BX Half */
#define RT_SUPORT_1000B_TFULL   0x2000  /* Can do 1000BT Full          */
#define RT_SUPORT_1000B_THALF   0x1000  /* Can do 1000BT Half          */
#define RT_PHY_ANEG_TIMEOUT     4000
struct rt_phy_device;

int rt_genphy_parse_link(struct rt_phy_device *phydev);
int rt_genphy_config_aneg(struct rt_phy_device *phydev);
int rt_genphy_update_link(struct rt_phy_device *phydev);
int rt_genphy_startup(struct rt_phy_device *phydev);
int rt_genphy_config(struct rt_phy_device *phydev);
#endif
