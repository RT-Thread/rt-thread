/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-08     zhujiale    the first version
 */
#ifndef __NET_PHY_H__
#define __NET_PHY_H__
#include <rtthread.h>
#include <mdio.h>
#include <general_phy.h>
#include <ofw.h>
#include <drivers/core/dm.h>
#include <drivers/core/driver.h>

#define RT_PHY_FIXED_ID 0xa5a55a5a
#define RT_PHY_NCSI_ID  0xbeefcafe


/* Indicates what features are supported by the interface. */
#define RT_SUPPORTED_10baseT_Half      (1 << 0)
#define RT_SUPPORTED_10baseT_Full      (1 << 1)
#define RT_SUPPORTED_100baseT_Half     (1 << 2)
#define RT_SUPPORTED_100baseT_Full     (1 << 3)
#define RT_SUPPORTED_1000baseT_Half    (1 << 4)
#define RT_SUPPORTED_1000baseT_Full    (1 << 5)
#define RT_SUPPORTED_Autoneg           (1 << 6)
#define RT_SUPPORTED_TP                (1 << 7)
#define RT_SUPPORTED_AUI               (1 << 8)
#define RT_SUPPORTED_MII               (1 << 9)
#define RT_SUPPORTED_FIBRE             (1 << 10)
#define RT_SUPPORTED_BNC               (1 << 11)
#define RT_SUPPORTED_10000baseT_Full   (1 << 12)
#define RT_SUPPORTED_Pause             (1 << 13)
#define RT_SUPPORTED_Asym_Pause        (1 << 14)
#define RT_SUPPORTED_2500baseX_Full    (1 << 15)
#define RT_SUPPORTED_Backplane         (1 << 16)
#define RT_SUPPORTED_1000baseKX_Full   (1 << 17)
#define RT_SUPPORTED_10000baseKX4_Full (1 << 18)
#define RT_SUPPORTED_10000baseKR_Full  (1 << 19)
#define RT_SUPPORTED_10000baseR_FEC    (1 << 20)
#define RT_SUPPORTED_1000baseX_Half    (1 << 21)
#define RT_SUPPORTED_1000baseX_Full    (1 << 22)

#define RT_PHY_FLAG_BROKEN_RESET (1 << 0) /* soft reset not supported */
#define RT_PHY_DEFAULT_FEATURES  (RT_SUPPORTED_Autoneg | RT_SUPPORTED_TP | RT_SUPPORTED_MII)

#define RT_PHY_10BT_FEATURES (RT_SUPPORTED_10baseT_Half | RT_SUPPORTED_10baseT_Full)

#define RT_PHY_100BT_FEATURES (RT_SUPPORTED_100baseT_Half | RT_SUPPORTED_100baseT_Full)

#define RT_PHY_1000BT_FEATURES (RT_SUPPORTED_1000baseT_Half | RT_SUPPORTED_1000baseT_Full)

#define RT_PHY_BASIC_FEATURES (RT_PHY_10BT_FEATURES | RT_PHY_100BT_FEATURES | RT_PHY_DEFAULT_FEATURES)

#define RT_PHY_GBIT_FEATURES (RT_PHY_BASIC_FEATURES | RT_PHY_1000BT_FEATURES)

#define RT_PHY_10G_FEATURES (RT_PHY_GBIT_FEATURES | RT_SUPPORTED_10000baseT_Full)
struct rt_phy_device
{
    struct rt_device      parent;
    struct mii_bus       *bus;
    struct rt_phy_driver *drv;
    rt_uint32_t           phy_id;
    rt_uint32_t           mmds;
    int                   speed;
    int                   duplex;
    int                   link;
    int                   port;
    rt_uint32_t           advertising;
    rt_uint32_t           supported;
    rt_bool_t             autoneg;
    int                   pause;
    rt_ubase_t            addr;
    rt_bool_t             is_c45;
    rt_uint32_t           flags;
    rt_phy_interface      interface;

#ifdef RT_USING_OFW
    struct rt_ofw_node *node;
#endif
    void *priv;
};

struct rt_phy_driver
{
    struct rt_driver parent;
    char             name[RT_NAME_MAX];
    rt_uint64_t      uid;
    rt_uint64_t      mask;
    rt_uint64_t      mmds;
    rt_uint32_t      features;

    int (*probe)(struct rt_phy_device *phydev);
    int (*config)(struct rt_phy_device *phydev);
    int (*startup)(struct rt_phy_device *phydev);
    int (*shutdown)(struct rt_phy_device *phydev);
    int (*read)(struct rt_phy_device *phydev, int addr, int devad, int reg);
    int (*write)(struct rt_phy_device *phydev, int addr, int devad, int reg,
                 rt_uint16_t val);
    int (*read_mmd)(struct rt_phy_device *phydev, int devad, int reg);
    int (*write_mmd)(struct rt_phy_device *phydev, int devad, int reg,
                     rt_uint16_t val);

    /* driver private data */
    void *data;
};

int rt_phy_read(struct rt_phy_device *phydev, int devad, int regnum);
int rt_phy_write(struct rt_phy_device *phydev, int devad, int regnum, rt_uint16_t val);
int rt_phy_read_mmd(struct rt_phy_device *phydev, int devad, int regnum);
int rt_phy_write_mmd(struct rt_phy_device *phydev, int devad, int regnum, rt_uint16_t val);
int rt_phy_reset(struct rt_phy_device *phydev);
int rt_phy_startup(struct rt_phy_device *phydev);
int rt_phy_config(struct rt_phy_device *phydev);
int rt_phy_shutdown(struct rt_phy_device *phydev);
int rt_phy_read_mmd(struct rt_phy_device *phydev, int devad, int regnum);
int rt_phy_set_supported(struct rt_phy_device *phydev, rt_uint32_t max_speed);

void rt_phy_mmd_start_indirect(struct rt_phy_device *phydev, int devad, int regnum);

rt_err_t rt_phy_device_register(struct rt_phy_device *pdev);
rt_err_t rt_phy_driver_register(struct rt_phy_driver *pdrv);
rt_err_t rt_ofw_get_phyid(struct rt_ofw_node *np, rt_uint16_t *vendor, rt_uint16_t *device);

struct rt_phy_device *rt_phy_device_create(struct mii_bus *bus, int addr, rt_uint32_t phy_id, rt_bool_t is_c45);
struct rt_phy_device *rt_phy_find_by_mask(struct mii_bus *bus, unsigned int phy_mask);
struct rt_phy_device *rt_ofw_create_phy(struct mii_bus *bus, struct rt_ofw_node *np, int phyaddr);
struct rt_phy_device *rt_phy_get_device(struct mii_bus *bus, struct rt_ofw_node *np, int addr, rt_phy_interface interface);

#define RT_PHY_DEVICE_REGISTER(phy_dev)      \
static int rt_##phy_dev##_register(void)     \
{                                            \
    rt_phy_device_register(&phy_dev);        \
    return 0;                                \
}                                            \
INIT_PREV_EXPORT(rt_##phy_dev##_register);

#define RT_PHY_DRIVER_REGISTER(phy_drv)      \
static int rt_##phy_drv##_register(void)     \
{                                            \
    rt_phy_driver_register(&phy_drv);        \
    return 0;                                \
}                                            \
INIT_PREV_EXPORT(rt_##phy_drv##_register);

#endif
