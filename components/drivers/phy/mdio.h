/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-08     zhujiale    the first version
 */
#ifndef __PHY_MDIO_H__
#define __PHY_MDIO_H__
#include <rtthread.h>
#include <rtdevice.h>

#define RT_MDIO_DEVAD_NONE          (-1)
#define RT_MDIO_MMD_PMAPMD  1   /* Physical Medium Attachment/
                     * Physical Medium Dependent */
#define RT_MDIO_MMD_WIS     2   /* WAN Interface Sublayer */
#define RT_MDIO_MMD_PCS     3   /* Physical Coding Sublayer */
#define RT_MDIO_MMD_PHYXS   4   /* PHY Extender Sublayer */
#define RT_MDIO_MMD_DTEXS   5   /* DTE Extender Sublayer */
#define RT_MDIO_MMD_TC      6   /* Transmission Convergence */
#define RT_MDIO_MMD_AN      7   /* Auto-Negotiation */
#define RT_MDIO_MMD_C22EXT  29  /* Clause 22 extension */
#define RT_MDIO_MMD_VEND1   30  /* Vendor specific 1 */
#define RT_MDIO_MMD_VEND2   31  /* Vendor specific 2 */

#define RT_MII_BMCR         0x00    /* Basic mode control register */
#define RT_MII_BMSR         0x01    /* Basic mode status register  */
#define RT_MII_PHYSID1      0x02    /* PHYS ID 1                   */
#define RT_MII_PHYSID2      0x03    /* PHYS ID 2                   */
#define RT_MII_ADVERTISE    0x04    /* Advertisement control reg   */
#define RT_MII_LPA          0x05    /* Link partner ability reg    */
#define RT_MII_EXPANSION    0x06    /* Expansion register          */
#define RT_MII_CTRL1000     0x09    /* 1000BASE-T control          */
#define RT_MII_STAT1000     0x0a    /* 1000BASE-T status           */
#define RT_MII_MMD_CTRL     0x0d    /* MMD Access Control Register */
#define RT_MII_MMD_DATA     0x0e    /* MMD Access Data Register */
#define RT_MII_ESTATUS      0x0f    /* Extended Status             */
#define RT_MII_DCOUNTER     0x12    /* Disconnect counter          */
#define RT_MII_FCSCOUNTER   0x13    /* False carrier counter       */
#define RT_MII_NWAYTEST     0x14    /* N-way auto-neg test reg     */
#define RT_MII_RERRCOUNTER  0x15    /* Receive error counter       */
#define RT_MII_SREVISION    0x16    /* Silicon revision            */
#define RT_MII_RESV1        0x17    /* Reserved...                 */
#define RT_MII_LBRERROR     0x18    /* Lpback, rx, bypass error    */
#define RT_MII_PHYADDR      0x19    /* PHY address                 */
#define RT_MII_RESV2        0x1a    /* Reserved...                 */
#define RT_MII_TPISTATUS    0x1b    /* TPI status for 10mbps       */
#define RT_MII_NCONFIG      0x1c    /* Network interface config    */

/* Basic mode control register. */
#define RT_BMCR_RESV            0x003f  /* Unused...                   */
#define RT_BMCR_SPEED1000       0x0040  /* MSB of Speed (1000)         */
#define RT_BMCR_CTST            0x0080  /* Collision test              */
#define RT_BMCR_FULLDPLX        0x0100  /* Full duplex                 */
#define RT_BMCR_ANRESTART       0x0200  /* Auto negotiation restart    */
#define RT_BMCR_ISOLATE         0x0400  /* Isolate data paths from MII */
#define RT_BMCR_PDOWN           0x0800  /* Enable low power state      */
#define RT_BMCR_ANENABLE        0x1000  /* Enable auto negotiation     */
#define RT_BMCR_SPEED100        0x2000  /* Select 100Mbps              */
#define RT_BMCR_LOOPBACK        0x4000  /* TXD loopback bits           */
#define RT_BMCR_RESET           0x8000  /* Reset to default state      */
#define RT_BMCR_SPEED10         0x0000  /* Select 10Mbps               */

#define RT_MII_MMD_CTRL_DEVAD_MASK  0x1f    /* Mask MMD DEVAD*/
#define RT_MII_MMD_CTRL_ADDR        0x0000  /* Address */
#define RT_MII_MMD_CTRL_NOINCR      0x4000  /* no post increment */
#define RT_MII_MMD_CTRL_INCR_RDWT   0x8000  /* post increment on reads & writes */
#define RT_MII_MMD_CTRL_INCR_ON_WT  0xC000  /* post increment on writes only */


#define RT_PHY_MAX 32

struct mii_bus
{
    struct rt_list_node node;
    char name[RT_NAME_MAX];
    void* priv;
    int (*read)(struct mii_bus* bus, int addr, int devad, int reg);
    int (*write)(struct mii_bus* bus, int addr, int devad, int reg, rt_uint16_t val);
    /** @read_c45: Perform a C45 read transfer on the bus */
    int (*read_c45)(struct mii_bus* bus, int addr, int devad, int reg);
    /** @write_c45: Perform a C45 write transfer on the bus */
    int (*write_c45)(struct mii_bus* bus, int addr, int devad, int reg, rt_uint16_t val);
    int (*reset)(struct mii_bus* bus);
    struct rt_phy_device* phymap[RT_PHY_MAX];
    rt_uint32_t phy_mask;
    int reset_delay_us;
    int reset_post_delay_us;
};

rt_err_t rt_mdio_register(struct mii_bus* bus);
rt_err_t rt_mdio_unregister(struct mii_bus* bus);

struct mii_bus* rt_mdio_get_bus_by_name(const char* busname);
struct mii_bus* rt_mdio_alloc(void);
#endif
