/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//#include <common.h>
#include <typedef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <hal_thread.h>
#include <sunxi_hal_common.h>
#include <sunxi_hal_miiphy.h>
#include <sunxi_hal_phy.h>

//#include <asm/types.h>
//#include <list.h>
#include <hal_mem.h>
//#include <net.h>

/* local debug macro */
#undef MII_DEBUG

#undef debug
#ifdef MII_DEBUG
#define debug(fmt, args...) printf(fmt, ##args)
#else
#define debug(fmt, args...)
#endif /* MII_DEBUG */

static struct list_head mii_devs;
static struct mii_dev *current_mii;

/*
 * Lookup the mii_dev struct by the registered device name.
 */
struct mii_dev *miiphy_get_dev_by_name(const char *devname)
{
    struct list_head *entry;
    struct mii_dev *dev;

    if (!devname) {
        printf("NULL device name!\n");
        return NULL;
    }

    list_for_each(entry, &mii_devs) {
        dev = list_entry(entry, struct mii_dev, link);
        if (strcmp(dev->name, devname) == 0)
            return dev;
    }

    return NULL;
}

/*****************************************************************************
 *
 * Initialize global data. Need to be called before any other miiphy routine.
 */
void miiphy_init(void)
{
    INIT_LIST_HEAD(&mii_devs);
    current_mii = NULL;
}

static int legacy_miiphy_read(struct mii_dev *bus, int addr, int devad, int reg)
{
    unsigned short val;
    int ret;
    struct legacy_mii_dev *ldev = bus->priv;

    ret = ldev->read(bus->name, addr, reg, &val);

    return ret ? -1 : (int)val;
}

static int legacy_miiphy_write(struct mii_dev *bus, int addr, int devad,
                int reg, uint16_t val)
{
    struct legacy_mii_dev *ldev = bus->priv;

    return ldev->write(bus->name, addr, reg, val);
}

/*****************************************************************************
 *
 * Register read and write MII access routines for the device <name>.
 * This API is now deprecated. Please use mdio_alloc and mdio_register, instead.
 */
void miiphy_register(const char *name,
              int (*read)(const char *devname, unsigned char addr,
                   unsigned char reg, unsigned short *value),
              int (*write)(const char *devname, unsigned char addr,
                    unsigned char reg, unsigned short value))
{
    struct mii_dev *new_dev;
    struct legacy_mii_dev *ldev;

    BUG_ON(strlen(name) >= MDIO_NAME_LEN);

    /* check if we have unique name */
    new_dev = miiphy_get_dev_by_name(name);
    if (new_dev) {
        printf("miiphy_register: non unique device name '%s'\n", name);
        return;
    }

    /* allocate memory */
    new_dev = mdio_alloc();
    ldev = malloc(sizeof(*ldev));

    if (new_dev == NULL || ldev == NULL) {
        printf("miiphy_register: cannot allocate memory for '%s'\n",
            name);
        return;
    }

    /* initalize mii_dev struct fields */
    new_dev->read = legacy_miiphy_read;
    new_dev->write = legacy_miiphy_write;
    strncpy(new_dev->name, name, MDIO_NAME_LEN);
    new_dev->name[MDIO_NAME_LEN - 1] = 0;
    ldev->read = read;
    ldev->write = write;
    new_dev->priv = ldev;

    printf("miiphy_register: added '%s', read=0x%08lx, write=0x%08lx\n",
           new_dev->name, ldev->read, ldev->write);

    /* add it to the list */
    list_add_tail(&new_dev->link, &mii_devs);

    if (!current_mii)
        current_mii = new_dev;
}

struct mii_dev *mdio_alloc(void)
{
    struct mii_dev *bus;

    bus = malloc(sizeof(*bus));
    if (!bus)
        return bus;

    memset(bus, 0, sizeof(*bus));

    /* initalize mii_dev struct fields */
    INIT_LIST_HEAD(&bus->link);

    return bus;
}

int mdio_register(struct mii_dev *bus)
{
    if (!bus || !bus->name || !bus->read || !bus->write)
        return -1;

    /* check if we have unique name */
    if (miiphy_get_dev_by_name(bus->name)) {
        printf("mdio_register: non unique device name '%s'\n",
            bus->name);
        return -1;
    }

    /* add it to the list */
    list_add_tail(&bus->link, &mii_devs);

    if (!current_mii)
        current_mii = bus;

    return 0;
}

void mdio_list_devices(void)
{
    struct list_head *entry;

    list_for_each(entry, &mii_devs) {
        int i;
        struct mii_dev *bus = list_entry(entry, struct mii_dev, link);

        printf("%s:\n", bus->name);

        for (i = 0; i < PHY_MAX_ADDR; i++) {
            struct phy_device *phydev = bus->phymap[i];

            if (phydev) {
                printf("%d - %s", i, phydev->drv->name);

                if (phydev->dev)
                    printf(" <--> %s\n", "eth0");
                else
                    printf("\n");
            }
        }
    }
}

int miiphy_set_current_dev(const char *devname)
{
    struct mii_dev *dev;

    dev = miiphy_get_dev_by_name(devname);
    if (dev) {
        current_mii = dev;
        return 0;
    }

    printf("No such device: %s\n", devname);

    return 1;
}

struct mii_dev *mdio_get_current_dev(void)
{
    return current_mii;
}

struct phy_device *mdio_phydev_for_ethname(const char *ethname)
{
    struct list_head *entry;
    struct mii_dev *bus;

    list_for_each(entry, &mii_devs) {
        int i;
        bus = list_entry(entry, struct mii_dev, link);

        for (i = 0; i < PHY_MAX_ADDR; i++) {
            if (!bus->phymap[i] || !bus->phymap[i]->dev)
                continue;

            /*if (strcmp(bus->phymap[i]->dev->name, ethname) == 0)
                return bus->phymap[i];*/
        }
    }

    printf("%s is not a known ethernet\n", ethname);
    return NULL;
}

const char *miiphy_get_current_dev(void)
{
    if (current_mii)
        return current_mii->name;

    return NULL;
}

static struct mii_dev *miiphy_get_active_dev(const char *devname)
{
    /* If the current mii is the one we want, return it */
    if (current_mii)
        if (strcmp(current_mii->name, devname) == 0)
            return current_mii;

    /* Otherwise, set the active one to the one we want */
    if (miiphy_set_current_dev(devname))
        return NULL;
    else
        return current_mii;
}

/*****************************************************************************
 *
 * Read to variable <value> from the PHY attached to device <devname>,
 * use PHY address <addr> and register <reg>.
 *
 * This API is deprecated. Use phy_read on a phy_device found via phy_connect
 *
 * Returns:
 *   0 on success
 */
int miiphy_read(const char *devname, unsigned char addr, unsigned char reg,
         unsigned short *value)
{
    struct mii_dev *bus;
    int ret;

    bus = miiphy_get_active_dev(devname);
    if (!bus)
        return 1;

    ret = bus->read(bus, addr, MDIO_DEVAD_NONE, reg);
    if (ret < 0)
        return 1;

    *value = (unsigned short)ret;
    return 0;
}

/*****************************************************************************
 *
 * Write <value> to the PHY attached to device <devname>,
 * use PHY address <addr> and register <reg>.
 *
 * This API is deprecated. Use phy_write on a phy_device found by phy_connect
 *
 * Returns:
 *   0 on success
 */
int miiphy_write(const char *devname, unsigned char addr, unsigned char reg,
          unsigned short value)
{
    struct mii_dev *bus;

    bus = miiphy_get_active_dev(devname);
    if (bus)
        return bus->write(bus, addr, MDIO_DEVAD_NONE, reg, value);

    return 1;
}

/*****************************************************************************
 *
 * Print out list of registered MII capable devices.
 */
void miiphy_listdev(void)
{
    struct list_head *entry;
    struct mii_dev *dev;

    puts("MII devices: ");
    list_for_each(entry, &mii_devs) {
        dev = list_entry(entry, struct mii_dev, link);
        printf("'%s' ", dev->name);
    }
    puts("\n");

    if (current_mii)
        printf("Current device: '%s'\n", current_mii->name);
}

/*****************************************************************************
 *
 * Read the OUI, manufacture's model number, and revision number.
 *
 * OUI:     22 bits (unsigned int)
 * Model:    6 bits (unsigned char)
 * Revision: 4 bits (unsigned char)
 *
 * This API is deprecated.
 *
 * Returns:
 *   0 on success
 */
int miiphy_info(const char *devname, unsigned char addr, unsigned int *oui,
         unsigned char *model, unsigned char *rev)
{
    unsigned int reg = 0;
    unsigned short tmp;

    if (miiphy_read(devname, addr, MII_PHYSID2, &tmp) != 0) {
        printf("PHY ID register 2 read failed\n");
        return -1;
    }
    reg = tmp;

    printf("MII_PHYSID2 @ 0x%x = 0x%04x\n", addr, reg);

    if (reg == 0xFFFF) {
        /* No physical device present at this address */
        return -1;
    }

    if (miiphy_read(devname, addr, MII_PHYSID1, &tmp) != 0) {
        printf("PHY ID register 1 read failed\n");
        return -1;
    }
    reg |= tmp << 16;
    printf("PHY_PHYIDR[1,2] @ 0x%x = 0x%08x\n", addr, reg);

    *oui = (reg >> 10);
    *model = (unsigned char)((reg >> 4) & 0x0000003F);
    *rev = (unsigned char)(reg & 0x0000000F);
    return 0;
}

#ifndef CONFIG_PHYLIB
/*****************************************************************************
 *
 * Reset the PHY.
 *
 * This API is deprecated. Use PHYLIB.
 *
 * Returns:
 *   0 on success
 */
#if 0
int miiphy_reset(const char *devname, unsigned char addr)
{
    unsigned short reg;
    int timeout = 500;

    if (miiphy_read(devname, addr, MII_BMCR, &reg) != 0) {
        printf("PHY status read failed\n");
        return -1;
    }
    if (miiphy_write(devname, addr, MII_BMCR, reg | BMCR_RESET) != 0) {
        printf("PHY reset failed\n");
        return -1;
    }
#ifdef CONFIG_PHY_RESET_DELAY
    udelay(CONFIG_PHY_RESET_DELAY); /* Intel LXT971A needs this */
#endif
    /*
     * Poll the control register for the reset bit to go to 0 (it is
     * auto-clearing).  This should happen within 0.5 seconds per the
     * IEEE spec.
     */
    reg = 0x8000;
    while (((reg & 0x8000) != 0) && timeout--) {
        if (miiphy_read(devname, addr, MII_BMCR, &reg) != 0) {
            printf("PHY status read failed\n");
            return -1;
        }
        udelay(1000);
    }
    if ((reg & 0x8000) == 0) {
        return 0;
    } else {
        printf("PHY reset timed out\n");
        return -1;
    }
    return 0;
}
#endif
#endif /* !PHYLIB */

/*****************************************************************************
 *
 * Determine the ethernet speed (10/100/1000).  Return 10 on error.
 */
int miiphy_speed(const char *devname, unsigned char addr)
{
    uint16_t bmcr, anlpar;

#if defined(CONFIG_PHY_GIGE)
    uint16_t btsr;

    /*
     * Check for 1000BASE-X.  If it is supported, then assume that the speed
     * is 1000.
     */
    if (miiphy_is_1000base_x(devname, addr))
        return _1000BASET;

    /*
     * No 1000BASE-X, so assume 1000BASE-T/100BASE-TX/10BASE-T register set.
     */
    /* Check for 1000BASE-T. */
    if (miiphy_read(devname, addr, MII_STAT1000, &btsr)) {
        printf("PHY 1000BT status");
        goto miiphy_read_failed;
    }
    if (btsr != 0xFFFF &&
            (btsr & (PHY_1000BTSR_1000FD | PHY_1000BTSR_1000HD)))
        return _1000BASET;
#endif /* CONFIG_PHY_GIGE */

    /* Check Basic Management Control Register first. */
    if (miiphy_read(devname, addr, MII_BMCR, &bmcr)) {
        printf("PHY speed");
        goto miiphy_read_failed;
    }
    /* Check if auto-negotiation is on. */
    if (bmcr & BMCR_ANENABLE) {
        /* Get auto-negotiation results. */
        if (miiphy_read(devname, addr, MII_LPA, &anlpar)) {
            printf("PHY AN speed");
            goto miiphy_read_failed;
        }
        return (anlpar & LPA_100) ? _100BASET : _10BASET;
    }
    /* Get speed from basic control settings. */
    return (bmcr & BMCR_SPEED100) ? _100BASET : _10BASET;

miiphy_read_failed:
    printf(" read failed, assuming 10BASE-T\n");
    return _10BASET;
}

/*****************************************************************************
 *
 * Determine full/half duplex.  Return half on error.
 */
int miiphy_duplex(const char *devname, unsigned char addr)
{
    uint16_t bmcr, anlpar;

#if defined(CONFIG_PHY_GIGE)
    uint16_t btsr;

    /* Check for 1000BASE-X. */
    if (miiphy_is_1000base_x(devname, addr)) {
        /* 1000BASE-X */
        if (miiphy_read(devname, addr, MII_LPA, &anlpar)) {
            printf("1000BASE-X PHY AN duplex");
            goto miiphy_read_failed;
        }
    }
    /*
     * No 1000BASE-X, so assume 1000BASE-T/100BASE-TX/10BASE-T register set.
     */
    /* Check for 1000BASE-T. */
    if (miiphy_read(devname, addr, MII_STAT1000, &btsr)) {
        printf("PHY 1000BT status");
        goto miiphy_read_failed;
    }
    if (btsr != 0xFFFF) {
        if (btsr & PHY_1000BTSR_1000FD) {
            return FULL;
        } else if (btsr & PHY_1000BTSR_1000HD) {
            return HALF;
        }
    }
#endif /* CONFIG_PHY_GIGE */

    /* Check Basic Management Control Register first. */
    if (miiphy_read(devname, addr, MII_BMCR, &bmcr)) {
        printf("PHY duplex");
        goto miiphy_read_failed;
    }
    /* Check if auto-negotiation is on. */
    if (bmcr & BMCR_ANENABLE) {
        /* Get auto-negotiation results. */
        if (miiphy_read(devname, addr, MII_LPA, &anlpar)) {
            printf("PHY AN duplex");
            goto miiphy_read_failed;
        }
        return (anlpar & (LPA_10FULL | LPA_100FULL)) ?
            FULL : HALF;
    }
    /* Get speed from basic control settings. */
    return (bmcr & BMCR_FULLDPLX) ? FULL : HALF;

miiphy_read_failed:
    printf(" read failed, assuming half duplex\n");
    return HALF;
}

/*****************************************************************************
 *
 * Return 1 if PHY supports 1000BASE-X, 0 if PHY supports 10BASE-T/100BASE-TX/
 * 1000BASE-T, or on error.
 */
int miiphy_is_1000base_x(const char *devname, unsigned char addr)
{
#if defined(CONFIG_PHY_GIGE)
    uint16_t exsr;

    if (miiphy_read(devname, addr, MII_ESTATUS, &exsr)) {
        printf("PHY extended status read failed, assuming no "
            "1000BASE-X\n");
        return 0;
    }
    return 0 != (exsr & (ESTATUS_1000XF | ESTATUS_1000XH));
#else
    return 0;
#endif
}

#ifdef CONFIG_SYS_FAULT_ECHO_LINK_DOWN
/*****************************************************************************
 *
 * Determine link status
 */
int miiphy_link(const char *devname, unsigned char addr)
{
    unsigned short reg;

    /* dummy read; needed to latch some phys */
    (void)miiphy_read(devname, addr, MII_BMSR, &reg);
    if (miiphy_read(devname, addr, MII_BMSR, &reg)) {
        printf("MII_BMSR read failed, assuming no link\n");
        return 0;
    }

    /* Determine if a link is active */
    if ((reg & BMSR_LSTATUS) != 0) {
        return 1;
    } else {
        return 0;
    }
}
#endif
