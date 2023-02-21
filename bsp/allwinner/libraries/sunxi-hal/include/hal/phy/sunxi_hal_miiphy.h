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

#ifndef __SUNXI_HAL_MIIPHY_H__
#define __SUNXI_HAL_MIIPHY_H__

//#include <common.h>
#include <sunxi_hal_mii.h>
//#include <sunxi_drv_list.h>
//#include <net.h>
#include <sunxi_hal_phy.h>

struct legacy_mii_dev {
    int (*read)(const char *devname, unsigned char addr,
             unsigned char reg, unsigned short *value);
    int (*write)(const char *devname, unsigned char addr,
              unsigned char reg, unsigned short value);
};

int miiphy_read(const char *devname, unsigned char addr, unsigned char reg,
         unsigned short *value);
int miiphy_write(const char *devname, unsigned char addr, unsigned char reg,
          unsigned short value);
int miiphy_info(const char *devname, unsigned char addr, unsigned int *oui,
         unsigned char *model, unsigned char *rev);
int miiphy_reset(const char *devname, unsigned char addr);
int miiphy_speed(const char *devname, unsigned char addr);
int miiphy_duplex(const char *devname, unsigned char addr);
int miiphy_is_1000base_x(const char *devname, unsigned char addr);
#ifdef CONFIG_SYS_FAULT_ECHO_LINK_DOWN
int miiphy_link(const char *devname, unsigned char addr);
#endif

void miiphy_init(void);

void miiphy_register(const char *devname,
              int (*read)(const char *devname, unsigned char addr,
                   unsigned char reg, unsigned short *value),
              int (*write)(const char *devname, unsigned char addr,
                    unsigned char reg, unsigned short value));

int miiphy_set_current_dev(const char *devname);
const char *miiphy_get_current_dev(void);
struct mii_dev *mdio_get_current_dev(void);
struct mii_dev *miiphy_get_dev_by_name(const char *devname);
struct phy_device *mdio_phydev_for_ethname(const char *devname);

void miiphy_listdev(void);

struct mii_dev *mdio_alloc(void);
int mdio_register(struct mii_dev *bus);
void mdio_list_devices(void);

#ifdef CONFIG_BITBANGMII

#define BB_MII_DEVNAME  "bb_miiphy"

struct bb_miiphy_bus {
    char name[16];
    int (*init)(struct bb_miiphy_bus *bus);
    int (*mdio_active)(struct bb_miiphy_bus *bus);
    int (*mdio_tristate)(struct bb_miiphy_bus *bus);
    int (*set_mdio)(struct bb_miiphy_bus *bus, int v);
    int (*get_mdio)(struct bb_miiphy_bus *bus, int *v);
    int (*set_mdc)(struct bb_miiphy_bus *bus, int v);
    int (*delay)(struct bb_miiphy_bus *bus);
#ifdef CONFIG_BITBANGMII_MULTI
    void *priv;
#endif
};

extern struct bb_miiphy_bus bb_miiphy_buses[];
extern int bb_miiphy_buses_num;

void bb_miiphy_init(void);
int bb_miiphy_read(const char *devname, unsigned char addr,
            unsigned char reg, unsigned short *value);
int bb_miiphy_write(const char *devname, unsigned char addr,
             unsigned char reg, unsigned short value);
#endif

/* phy seed setup */
#define AUTO            99
#define _1000BASET      1000
#define _100BASET       100
#define _10BASET        10
#define HALF            22
#define FULL            44

/* phy register offsets */
#define MII_MIPSCR      0x11

/* MII_LPA */
#define PHY_ANLPAR_PSB_802_3    0x0001
#define PHY_ANLPAR_PSB_802_9    0x0002

/* MII_CTRL1000 masks */
#define PHY_1000BTCR_1000FD 0x0200
#define PHY_1000BTCR_1000HD 0x0100

/* MII_STAT1000 masks */
#define PHY_1000BTSR_MSCF   0x8000
#define PHY_1000BTSR_MSCR   0x4000
#define PHY_1000BTSR_LRS    0x2000
#define PHY_1000BTSR_RRS    0x1000
#define PHY_1000BTSR_1000FD 0x0800
#define PHY_1000BTSR_1000HD 0x0400

/* phy EXSR */
#define ESTATUS_1000XF      0x8000
#define ESTATUS_1000XH      0x4000

#endif /* __SUNXI_HAL_MIIPHY_H__ */
