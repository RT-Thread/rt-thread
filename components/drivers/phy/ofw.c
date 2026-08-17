/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-25     zhujiale    the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <stdio.h>
#define DBG_TAG "rtdm.phy"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include "mdio.h"
#include "ofw.h"

static const char* const rt_phy_modes[] =
{
    [RT_PHY_INTERFACE_MODE_NA]         = "",
    [RT_PHY_INTERFACE_MODE_INTERNAL]   = "internal",
    [RT_PHY_INTERFACE_MODE_MII]        = "mii",
    [RT_PHY_INTERFACE_MODE_GMII]       = "gmii",
    [RT_PHY_INTERFACE_MODE_SGMII]      = "sgmii",
    [RT_PHY_INTERFACE_MODE_TBI]        = "tbi",
    [RT_PHY_INTERFACE_MODE_REVMII]     = "rev-mii",
    [RT_PHY_INTERFACE_MODE_RMII]       = "rmii",
    [RT_PHY_INTERFACE_MODE_REVRMII]    = "rev-rmii",
    [RT_PHY_INTERFACE_MODE_RGMII]      = "rgmii",
    [RT_PHY_INTERFACE_MODE_RGMII_ID]   = "rgmii-id",
    [RT_PHY_INTERFACE_MODE_RGMII_RXID] = "rgmii-rxid",
    [RT_PHY_INTERFACE_MODE_RGMII_TXID] = "rgmii-txid",
    [RT_PHY_INTERFACE_MODE_RTBI]       = "rtbi",
    [RT_PHY_INTERFACE_MODE_SMII]       = "smii",
    [RT_PHY_INTERFACE_MODE_XGMII]      = "xgmii",
    [RT_PHY_INTERFACE_MODE_XLGMII]     = "xlgmii",
    [RT_PHY_INTERFACE_MODE_MOCA]       = "moca",
    [RT_PHY_INTERFACE_MODE_PSGMII]     = "psgmii",
    [RT_PHY_INTERFACE_MODE_QSGMII]     = "qsgmii",
    [RT_PHY_INTERFACE_MODE_TRGMII]     = "trgmii",
    [RT_PHY_INTERFACE_MODE_1000BASEX]  = "1000base-x",
    [RT_PHY_INTERFACE_MODE_1000BASEKX] = "1000base-kx",
    [RT_PHY_INTERFACE_MODE_2500BASEX]  = "2500base-x",
    [RT_PHY_INTERFACE_MODE_5GBASER]    = "5gbase-r",
    [RT_PHY_INTERFACE_MODE_RXAUI]      = "rxaui",
    [RT_PHY_INTERFACE_MODE_XAUI]       = "xaui",
    [RT_PHY_INTERFACE_MODE_10GBASER]   = "10gbase-r",
    [RT_PHY_INTERFACE_MODE_25GBASER]   = "25gbase-r",
    [RT_PHY_INTERFACE_MODE_USXGMII]    = "usxgmii",
    [RT_PHY_INTERFACE_MODE_10GKR]      = "10gbase-kr",
    [RT_PHY_INTERFACE_MODE_100BASEX]   = "100base-x",
    [RT_PHY_INTERFACE_MODE_QUSGMII]    = "qusgmii",
    [RT_PHY_INTERFACE_MODE_MAX]        = "",
};

static rt_err_t _get_interface_by_name(const char *name, rt_phy_interface *interface)
{
    for (int i = 0; i < RT_PHY_INTERFACE_MODE_MAX; i++)
    {
        if (!strcmp(name, rt_phy_modes[i]))
        {
            *interface = i;
            return RT_EOK;
        }
    }
    return -RT_ERROR;
}

rt_err_t rt_ofw_get_interface(struct rt_ofw_node *np, rt_phy_interface *interface)
{
    const char *phy_mode = RT_NULL;

    if (rt_ofw_prop_read_string(np, "phy-mode", &phy_mode))
        rt_ofw_prop_read_string(np, "phy-connection-type", &phy_mode);
    if (!phy_mode)
        return -RT_ERROR;

    return _get_interface_by_name(phy_mode, interface);
}

rt_err_t rt_ofw_get_mac_addr_by_name(struct rt_ofw_node *np, const char *name, rt_uint8_t *addr)
{
    rt_ssize_t  len;
    const void *p;
    p = rt_ofw_prop_read_raw(np, name, &len);
    if (p)
    {
        rt_memcpy(addr, p, len);
        return RT_EOK;
    }

    return -RT_ERROR;
}

rt_err_t rt_ofw_get_mac_addr(struct rt_ofw_node *np, rt_uint8_t *addr)
{
    if (!rt_ofw_get_mac_addr_by_name(np, "mac-address", addr))
        return RT_EOK;

    if (!rt_ofw_get_mac_addr_by_name(np, "local-mac-address", addr))
        return RT_EOK;

    if (!rt_ofw_get_mac_addr_by_name(np, "address", addr))
        return RT_EOK;

    return -RT_ERROR;
}

rt_err_t rt_ofw_get_phyid(struct rt_ofw_node *np,rt_uint32_t *id)
{
    struct rt_ofw_prop *prop;
    const char *phy_id;
    unsigned int upper, lower;

    rt_ofw_foreach_prop_string(np, "compatible", prop, phy_id)
    {
        if (rt_sscanf(phy_id, "ethernet-phy-id%4x.%4x", &upper, &lower) == 2)
        {
            *id = ((upper & 0xffff) << 16) | (lower & 0xffff);
            return RT_EOK;
        }
    }

    return -RT_ERROR;
}

static int ofw_read_phy_id(struct mii_bus *bus, int addr, rt_uint32_t *id)
{
    int reg;

    reg = bus->read(bus, addr, RT_MDIO_DEVAD_NONE, RT_MII_PHYSID1);
    if (reg < 0)
    {
        return -RT_EIO;
    }

    *id = (reg & 0xffff) << 16;

    reg = bus->read(bus, addr, RT_MDIO_DEVAD_NONE, RT_MII_PHYSID2);
    if (reg < 0)
    {
        return -RT_EIO;
    }

    *id |= (reg & 0xffff);

    return RT_EOK;
}

struct rt_phy_device *rt_ofw_create_phy(struct mii_bus *bus,struct rt_ofw_node *np,int phyaddr)
{
    struct rt_phy_device *dev = RT_NULL;
    struct rt_ofw_node *phy_node;
    int ret;
    rt_uint32_t id = 0xffff;

    phy_node = rt_ofw_parse_phandle(np, "phy-handle", 0);
    if (!phy_node)
    {
        LOG_D("Failed to find phy-handle");
        return RT_NULL;
    }

    ret = rt_ofw_get_phyid(phy_node, &id);
    if (ret)
    {
        rt_uint32_t reg = 0;
        int addr;

        if (rt_ofw_prop_read_u32(phy_node, "reg", &reg))
        {
            rt_ofw_node_put(phy_node);
            return RT_NULL;
        }

        addr = (phyaddr >= 0) ? phyaddr : (int)reg;
        id = 0xffffffff;

        if (!ofw_read_phy_id(bus, addr, &id) &&
            (id & 0x1fffffff) != 0x1fffffff)
        {
            LOG_D("PHY id from MDIO: 0x%08x @ addr %d", id, addr);
        }
        else
        {
            id = 0xffffffff;
            LOG_D("MDIO PHY id read failed @ addr %d, use generic PHY", addr);
        }

        dev = rt_phy_device_create(bus, addr, id, RT_FALSE);
        if (dev)
        {
            dev->node = phy_node;
        }
        else
        {
            rt_ofw_node_put(phy_node);
        }

        return dev;
    }

    LOG_D("Found a PHY id: 0x%x", id);

    dev = rt_phy_device_create(bus, phyaddr, id, RT_FALSE);

    if (dev)
    {
        dev->node = phy_node;
    }
    else
    {
        rt_ofw_node_put(phy_node);
    }

    return dev;
}
