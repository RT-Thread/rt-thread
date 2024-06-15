/*
* Copyright (C) Cvitek Co., Ltd. 2019-2020. All rights reserved.
*/

#ifndef __MII_H__
#define __MII_H__

/* Basic mode control register. */
#define CVI_BMCR_RESV           (0x003f)
#define CVI_BMCR_SPEED1000      (0x0040)
#define CVI_BMCR_CTST           (0x0080)
#define CVI_BMCR_FULLDPLX       (0x0100)
#define CVI_BMCR_ANRESTART      (0x0200)
#define CVI_BMCR_ISOLATE        (0x0400)
#define CVI_BMCR_PDOWN          (0x0800)
#define CVI_BMCR_ANENABLE       (0x1000)
#define CVI_BMCR_SPEED100       (0x2000)
#define CVI_BMCR_LOOPBACK       (0x4000)
#define CVI_BMCR_RESET          (0x8000)

/* Basic mode status register. */
#define CVI_BMSR_ERCAP          (0x0001)
#define CVI_BMSR_JCD            (0x0002)
#define CVI_BMSR_LSTATUS        (0x0004)
#define CVI_BMSR_ANEGCAPABLE    (0x0008)
#define CVI_BMSR_RFAULT         (0x0010)
#define CVI_BMSR_ANEGCOMPLETE   (0x0020)
#define CVI_BMSR_RESV           (0x00c0)
#define CVI_BMSR_ESTATEN        (0x0100)
#define CVI_BMSR_100HALF2       (0x0200)
#define CVI_BMSR_100FULL2       (0x0400)
#define CVI_BMSR_10HALF         (0x0800)
#define CVI_BMSR_10FULL         (0x1000)
#define CVI_BMSR_100HALF        (0x2000)
#define CVI_BMSR_100FULL        (0x4000)
#define CVI_BMSR_100BASE4       (0x8000)

/* Advertisement control register. */
#define CVI_ADVERTISE_CSMA            (0x0001)
#define CVI_ADVERTISE_SLCT            (0x001f)
#define CVI_ADVERTISE_10HALF          (0x0020)
#define CVI_ADVERTISE_1000XFULL       (0x0020)
#define CVI_ADVERTISE_10FULL          (0x0040)
#define CVI_ADVERTISE_1000XHALF       (0x0040)
#define CVI_ADVERTISE_100HALF         (0x0080)
#define CVI_ADVERTISE_1000XPAUSE      (0x0080)
#define CVI_ADVERTISE_100FULL         (0x0100)
#define CVI_ADVERTISE_1000XPSE_ASYM   (0x0100)
#define CVI_ADVERTISE_100BASE4        (0x0200)
#define CVI_ADVERTISE_PAUSE_CAP       (0x0400)
#define CVI_ADVERTISE_PAUSE_ASYM      (0x0800)
#define CVI_ADVERTISE_RESV            (0x1000)
#define CVI_ADVERTISE_RFAULT          (0x2000)
#define CVI_ADVERTISE_LPACK           (0x4000)
#define CVI_ADVERTISE_NPAGE           (0x8000)

/* Generic MII registers. */

#define CVI_MII_BMCR            (0x00)
#define CVI_MII_BMSR            (0x01)
#define CVI_MII_PHYSID1         (0x02)
#define CVI_MII_PHYSID2         (0x03)
#define CVI_MII_ADVERTISE       (0x04)
#define CVI_MII_LPA             (0x05)
#define CVI_MII_EXPANSION       (0x06)
#define CVI_MII_CTRL1000        (0x09)
#define CVI_MII_STAT1000        (0x0a)
#define CVI_MII_ESTATUS         (0x0f)
#define CVI_MII_DCOUNTER        (0x12)
#define CVI_MII_FCSCOUNTER      (0x13)
#define CVI_MII_NWAYTEST        (0x14)
#define CVI_MII_RERRCOUNTER     (0x15)
#define CVI_MII_SREVISION       (0x16)
#define CVI_MII_RESV1           (0x17)
#define CVI_MII_LBRERROR        (0x18)
#define CVI_MII_PHYADDR         (0x19)
#define CVI_MII_RESV2           (0x1a)
#define CVI_MII_TPISTATUS       (0x1b)
#define CVI_MII_NCONFIG         (0x1c)

#define CVI_ADVERTISE_FULL (CVI_ADVERTISE_100FULL | CVI_ADVERTISE_10FULL | \
            CVI_ADVERTISE_CSMA)
#define CVI_ADVERTISE_ALL (CVI_ADVERTISE_10HALF | CVI_ADVERTISE_10FULL | \
               CVI_ADVERTISE_100HALF | CVI_ADVERTISE_100FULL)

/* Expansion register for auto-negotiation. */
#define CVI_EXPANSION_NWAY            (0x0001)
#define CVI_EXPANSION_LCWP            (0x0002)
#define CVI_EXPANSION_ENABLENPAGE     (0x0004)
#define CVI_EXPANSION_NPCAPABLE       (0x0008)
#define CVI_EXPANSION_MFAULTS         (0x0010)
#define CVI_ESTATUS_1000_THALF        (0x1000)
#define CVI_ESTATUS_1000_TFULL        (0x2000)
#define CVI_ESTATUS_1000_XHALF        (0x4000)
#define CVI_ESTATUS_1000_XFULL        (0x8000)
#define CVI_EXPANSION_RESV            (0xffe0)

/* Link partner ability register. */
#define CVI_LPA_SLCT                 (0x001f)
#define CVI_LPA_10HALF               (0x0020)
#define CVI_LPA_1000XFULL            (0x0020)
#define CVI_LPA_10FULL               (0x0040)
#define CVI_LPA_1000XHALF            (0x0040)
#define CVI_LPA_100HALF              (0x0080)
#define CVI_LPA_1000XPAUSE           (0x0080)
#define CVI_LPA_100FULL              (0x0100)
#define CVI_LPA_1000XPAUSE_ASYM      (0x0100)
#define CVI_LPA_100BASE4             (0x0200)
#define CVI_LPA_PAUSE_CAP            (0x0400)
#define CVI_LPA_PAUSE_ASYM           (0x0800)
#define CVI_LPA_RESV                 (0x1000)
#define CVI_LPA_RFAULT               (0x2000)
#define CVI_LPA_LPACK                (0x4000)
#define CVI_LPA_NPAGE                (0x8000)

#define CVI_LPA_DUPLEX      (CVI_LPA_10FULL | CVI_LPA_100FULL)
#define CVI_LPA_100         (CVI_LPA_100FULL | CVI_LPA_100HALF | CVI_LPA_100BASE4)
/* N-way test register. */
#define CVI_NWAYTEST_RESV1      (0x00ff)
#define CVI_NWAYTEST_LOOPBACK   (0x0100)
#define CVI_NWAYTEST_RESV2      (0xfe00)

/* 1000BASE-T Control register */
#define CVI_ADVERTISE_1000FULL  0x0200
#define CVI_ADVERTISE_1000HALF  0x0100

/* 1000BASE-T Status register */
#define CVI_LPA_1000LOCALRXOK   0x2000
#define CVI_LPA_1000REMRXOK     0x1000
#define CVI_LPA_1000FULL        0x0800
#define CVI_LPA_1000HALF        0x0400

/* Flow control flags */
#define CVI_FLOW_CTRL_TX        0x01
#define CVI_FLOW_CTRL_RX        0x02

/**
 * mii_nway_result
 * @negotiated: value of MII ANAR and'd with ANLPAR
 *
 * Given a set of MII abilities, check each bit and returns the
 * currently supported media, in the priority order defined by
 * IEEE 802.3u.  We use LPA_xxx constants but note this is not the
 * value of LPA solely, as described above.
 *
 * The one exception to IEEE 802.3u is that 100baseT4 is placed
 * between 100T-full and 100T-half.  If your phy does not support
 * 100T4 this is fine. If your phy places 100T4 elsewhere in the
 * priority order, you will need to roll your own function.
 */
static inline unsigned int mii_nway_result (unsigned int negotiated)
{
    unsigned int ret;

    if (negotiated & CVI_LPA_100FULL)
        ret = CVI_LPA_100FULL;
    else if (negotiated & CVI_LPA_100BASE4)
        ret = CVI_LPA_100BASE4;
    else if (negotiated & CVI_LPA_100HALF)
        ret = CVI_LPA_100HALF;
    else if (negotiated & CVI_LPA_10FULL)
        ret = CVI_LPA_10FULL;
    else
        ret = CVI_LPA_10HALF;

    return ret;
}

/**
 * mii_duplex
 * @duplex_lock: Non-zero if duplex is locked at full
 * @negotiated: value of MII ANAR and'd with ANLPAR
 *
 * A small helper function for a common case.  Returns one
 * if the media is operating or locked at full duplex, and
 * returns zero otherwise.
 */
static inline unsigned int mii_duplex (unsigned int duplex_lock,
                       unsigned int negotiated)
{
    if (duplex_lock)
        return 1;
    if (mii_nway_result(negotiated) & CVI_LPA_DUPLEX)
        return 1;
    return 0;
}

#endif /* __LINUX_MII_H__ */
