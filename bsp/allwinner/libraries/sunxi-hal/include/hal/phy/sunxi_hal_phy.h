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

#ifndef __SUNXI_HAL_PHY_H__
#define __SUNXI_HAL_PHY_H__

#include <stdint.h>
#include <sunxi_hal_mii.h>
#include <sunxi_hal_mdio.h>
#include <aw_list.h>

#define PHY_MAX_ADDR 32

/* Indicates what features are supported by the interface. */
#define SUPPORTED_10baseT_Half      (1 << 0)
#define SUPPORTED_10baseT_Full      (1 << 1)
#define SUPPORTED_100baseT_Half     (1 << 2)
#define SUPPORTED_100baseT_Full     (1 << 3)
#define SUPPORTED_1000baseT_Half    (1 << 4)
#define SUPPORTED_1000baseT_Full    (1 << 5)
#define SUPPORTED_Autoneg       (1 << 6)
#define SUPPORTED_TP            (1 << 7)
#define SUPPORTED_AUI           (1 << 8)
#define SUPPORTED_MII           (1 << 9)
#define SUPPORTED_FIBRE         (1 << 10)
#define SUPPORTED_BNC           (1 << 11)
#define SUPPORTED_10000baseT_Full   (1 << 12)
#define SUPPORTED_Pause         (1 << 13)
#define SUPPORTED_Asym_Pause        (1 << 14)
#define SUPPORTED_2500baseX_Full    (1 << 15)
#define SUPPORTED_Backplane     (1 << 16)
#define SUPPORTED_1000baseKX_Full   (1 << 17)
#define SUPPORTED_10000baseKX4_Full (1 << 18)
#define SUPPORTED_10000baseKR_Full  (1 << 19)
#define SUPPORTED_10000baseR_FEC    (1 << 20)
#define SUPPORTED_1000baseX_Half    (1 << 21)
#define SUPPORTED_1000baseX_Full    (1 << 22)

/* Indicates what features are advertised by the interface. */
#define ADVERTISED_10baseT_Half     (1 << 0)
#define ADVERTISED_10baseT_Full     (1 << 1)
#define ADVERTISED_100baseT_Half    (1 << 2)
#define ADVERTISED_100baseT_Full    (1 << 3)
#define ADVERTISED_1000baseT_Half   (1 << 4)
#define ADVERTISED_1000baseT_Full   (1 << 5)
#define ADVERTISED_Autoneg      (1 << 6)
#define ADVERTISED_TP           (1 << 7)
#define ADVERTISED_AUI          (1 << 8)
#define ADVERTISED_MII          (1 << 9)
#define ADVERTISED_FIBRE        (1 << 10)
#define ADVERTISED_BNC          (1 << 11)
#define ADVERTISED_10000baseT_Full  (1 << 12)
#define ADVERTISED_Pause        (1 << 13)
#define ADVERTISED_Asym_Pause       (1 << 14)
#define ADVERTISED_2500baseX_Full   (1 << 15)
#define ADVERTISED_Backplane        (1 << 16)
#define ADVERTISED_1000baseKX_Full  (1 << 17)
#define ADVERTISED_10000baseKX4_Full    (1 << 18)
#define ADVERTISED_10000baseKR_Full (1 << 19)
#define ADVERTISED_10000baseR_FEC   (1 << 20)
#define ADVERTISED_1000baseX_Half   (1 << 21)
#define ADVERTISED_1000baseX_Full   (1 << 22)

/* The following are all involved in forcing a particular link
 * mode for the device for setting things.  When getting the
 * devices settings, these indicate the current mode and whether
 * it was foced up into this mode or autonegotiated.
 */

/* The forced speed, 10Mb, 100Mb, gigabit, 2.5Gb, 10GbE. */
#define SPEED_10        10
#define SPEED_100       100
#define SPEED_1000      1000
#define SPEED_2500      2500
#define SPEED_10000     10000

/* Duplex, half or full. */
#define DUPLEX_HALF     0x00
#define DUPLEX_FULL     0x01

/* Which connector port. */
#define PORT_TP         0x00
#define PORT_AUI        0x01
#define PORT_MII        0x02
#define PORT_FIBRE      0x03
#define PORT_BNC        0x04
#define PORT_DA         0x05
#define PORT_NONE       0xef
#define PORT_OTHER      0xff

/* Which transceiver to use. */
#define XCVR_INTERNAL       0x00
#define XCVR_EXTERNAL       0x01
#define XCVR_DUMMY1     0x02
#define XCVR_DUMMY2     0x03
#define XCVR_DUMMY3     0x04

/* Enable or disable autonegotiation.  If this is set to enable,
 * the forced link modes above are completely ignored.
 */
#define AUTONEG_DISABLE     0x00
#define AUTONEG_ENABLE      0x01

#define PHY_BASIC_FEATURES  (SUPPORTED_10baseT_Half | \
                 SUPPORTED_10baseT_Full | \
                 SUPPORTED_100baseT_Half | \
                 SUPPORTED_100baseT_Full | \
                 SUPPORTED_Autoneg | \
                 SUPPORTED_TP | \
                 SUPPORTED_MII)

#define PHY_GBIT_FEATURES   (PHY_BASIC_FEATURES | \
                 SUPPORTED_1000baseT_Half | \
                 SUPPORTED_1000baseT_Full)

#define PHY_10G_FEATURES    (PHY_GBIT_FEATURES | \
                SUPPORTED_10000baseT_Full)

#define PHY_ANEG_TIMEOUT    4000


typedef enum {
    PHY_INTERFACE_MODE_MII,
    PHY_INTERFACE_MODE_GMII,
    PHY_INTERFACE_MODE_SGMII,
    PHY_INTERFACE_MODE_QSGMII,
    PHY_INTERFACE_MODE_TBI,
    PHY_INTERFACE_MODE_RMII,
    PHY_INTERFACE_MODE_RGMII,
    PHY_INTERFACE_MODE_RGMII_ID,
    PHY_INTERFACE_MODE_RGMII_RXID,
    PHY_INTERFACE_MODE_RGMII_TXID,
    PHY_INTERFACE_MODE_RTBI,
    PHY_INTERFACE_MODE_XGMII,
    PHY_INTERFACE_MODE_NONE /* Must be last */
} phy_interface_t;

static const char *phy_interface_strings[] = {
    [PHY_INTERFACE_MODE_MII]        = "mii",
    [PHY_INTERFACE_MODE_GMII]       = "gmii",
    [PHY_INTERFACE_MODE_SGMII]      = "sgmii",
    [PHY_INTERFACE_MODE_QSGMII]     = "qsgmii",
    [PHY_INTERFACE_MODE_TBI]        = "tbi",
    [PHY_INTERFACE_MODE_RMII]       = "rmii",
    [PHY_INTERFACE_MODE_RGMII]      = "rgmii",
    [PHY_INTERFACE_MODE_RGMII_ID]       = "rgmii-id",
    [PHY_INTERFACE_MODE_RGMII_RXID]     = "rgmii-rxid",
    [PHY_INTERFACE_MODE_RGMII_TXID]     = "rgmii-txid",
    [PHY_INTERFACE_MODE_RTBI]       = "rtbi",
    [PHY_INTERFACE_MODE_XGMII]      = "xgmii",
    [PHY_INTERFACE_MODE_NONE]       = "",
};

static inline const char *phy_string_for_interface(phy_interface_t i)
{
    /* Default to unknown */
    if (i > PHY_INTERFACE_MODE_NONE)
        i = PHY_INTERFACE_MODE_NONE;

    return phy_interface_strings[i];
}


struct phy_device;

#define MDIO_NAME_LEN 32

struct mii_dev {
    struct list_head link;
    char name[MDIO_NAME_LEN];
    void *priv;
    int (*read)(struct mii_dev *bus, int addr, int devad, int reg);
    int (*write)(struct mii_dev *bus, int addr, int devad, int reg,
            uint16_t val);
    int (*reset)(struct mii_dev *bus);
    struct phy_device *phymap[PHY_MAX_ADDR];
    uint32_t phy_mask;
};

/* struct phy_driver: a structure which defines PHY behavior
 *
 * uid will contain a number which represents the PHY.  During
 * startup, the driver will poll the PHY to find out what its
 * UID--as defined by registers 2 and 3--is.  The 32-bit result
 * gotten from the PHY will be masked to
 * discard any bits which may change based on revision numbers
 * unimportant to functionality
 *
 */
struct phy_driver {
    char *name;
    unsigned int uid;
    unsigned int mask;
    unsigned int mmds;

    uint32_t features;

    /* Called to do any driver startup necessities */
    /* Will be called during phy_connect */
    int (*probe)(struct phy_device *phydev);

    /* Called to configure the PHY, and modify the controller
     * based on the results.  Should be called after phy_connect */
    int (*config)(struct phy_device *phydev);

    /* Called when starting up the controller */
    int (*startup)(struct phy_device *phydev);

    /* Called when bringing down the controller */
    int (*shutdown)(struct phy_device *phydev);

    int (*readext)(struct phy_device *phydev, int addr, int devad, int reg);
    int (*writeext)(struct phy_device *phydev, int addr, int devad, int reg,
            uint16_t val);
    struct list_head list;
};

struct phy_device {
    /* Information about the PHY type */
    /* And management functions */
    struct mii_dev *bus;
    struct phy_driver *drv;
    void *priv;

    struct eth_device *dev;

    /* forced speed & duplex (no autoneg)
     * partner speed & duplex & pause (autoneg)
     */
    int speed;
    int duplex;

    /* The most recently read link state */
    int link;
    int port;
    phy_interface_t interface;

    uint32_t advertising;
    uint32_t supported;
    uint32_t mmds;

    int autoneg;
    int addr;
    int pause;
    int asym_pause;
    uint32_t phy_id;
    uint32_t flags;
};

struct fixed_link {
    int phy_id;
    int duplex;
    int link_speed;
    int pause;
    int asym_pause;
};

static inline int phy_read(struct phy_device *phydev, int devad, int regnum)
{
    struct mii_dev *bus = phydev->bus;

    return bus->read(bus, phydev->addr, devad, regnum);
}

static inline int phy_write(struct phy_device *phydev, int devad, int regnum,
            uint32_t val)
{
    struct mii_dev *bus = phydev->bus;

    return bus->write(bus, phydev->addr, devad, regnum, val);
}

#ifdef CONFIG_PHYLIB_10G
extern struct phy_driver gen10g_driver;

/* For now, XGMII is the only 10G interface */
static inline int is_10g_interface(phy_interface_t interface)
{
    return interface == PHY_INTERFACE_MODE_XGMII;
}

#endif

int phy_init(void);
int phy_reset(struct phy_device *phydev);
struct phy_device *phy_find_by_mask(struct mii_dev *bus, unsigned phy_mask,
        phy_interface_t interface);
void phy_connect_dev(struct phy_device *phydev, struct eth_device *dev);
struct phy_device *phy_connect(struct mii_dev *bus, int addr,
                struct eth_device *dev,
                phy_interface_t interface);
int phy_startup(struct phy_device *phydev);
int phy_config(struct phy_device *phydev);
int phy_shutdown(struct phy_device *phydev);
int phy_register(struct phy_driver *drv);
int genphy_config_aneg(struct phy_device *phydev);
int genphy_restart_aneg(struct phy_device *phydev);
int genphy_update_link(struct phy_device *phydev);
int genphy_parse_link(struct phy_device *phydev);
int genphy_config(struct phy_device *phydev);
int genphy_startup(struct phy_device *phydev);
int genphy_shutdown(struct phy_device *phydev);
int gen10g_config(struct phy_device *phydev);
int gen10g_startup(struct phy_device *phydev);
int gen10g_shutdown(struct phy_device *phydev);
int gen10g_discover_mmds(struct phy_device *phydev);

int phy_atheros_init(void);
int phy_broadcom_init(void);
int phy_davicom_init(void);
int phy_et1011c_init(void);
int phy_lxt_init(void);
int phy_marvell_init(void);
int phy_micrel_init(void);
int phy_natsemi_init(void);
int phy_realtek_init(void);
int phy_smsc_init(void);
int phy_teranetics_init(void);
int phy_vitesse_init(void);

int board_phy_config(struct phy_device *phydev);

/* PHY UIDs for various PHYs that are referenced in external code */
#define PHY_UID_TN2020  0x00a19410

#endif /* __SUNXI_HAL_PHY_H__ */
