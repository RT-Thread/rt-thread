/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-27     wangqiang   first version
 * 2024-10-08     zhujiale    add phy v2.0
 */
#include <stddef.h>
#include <rthw.h>
#include <rtdevice.h>
#define DBG_TAG "rtdm.phy"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_PHY

static rt_ssize_t phy_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t count)
{
    struct rt_phy_device *phy = (struct rt_phy_device *)dev->user_data;
    struct rt_phy_msg *msg = (struct rt_phy_msg *)buffer;
    return phy->bus->ops->read(phy->bus, phy->addr, msg->reg, &(msg->value), 4);
}
static rt_ssize_t phy_device_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t count)
{
    struct rt_phy_device *phy = (struct rt_phy_device *)dev->user_data;
    struct rt_phy_msg *msg = (struct rt_phy_msg *)buffer;
    return phy->bus->ops->write(phy->bus, phy->addr, msg->reg, &(msg->value), 4);
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops phy_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    phy_device_read,
    phy_device_write,
    RT_NULL,
};
#endif

/*
* phy device register
*/
rt_err_t rt_hw_phy_register(struct rt_phy_device *phy, const char *name)
{
    rt_err_t ret;
    struct rt_device *device;

    device = &(phy->parent);

    device->type = RT_Device_Class_PHY;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops = &phy_ops;
#else
    device->init = NULL;
    device->open = NULL;
    device->close = NULL;
    device->read = phy_device_read;
    device->write = phy_device_write;
    device->control = NULL;
#endif
    device->user_data = phy;

    /* register a character device */
    ret = rt_device_register(device, name, RT_DEVICE_FLAG_RDWR);

    return ret;
}
#endif

#ifdef RT_USING_PHY_V2
int rt_phy_set_supported(struct rt_phy_device *phydev, rt_uint32_t max_speed)
{
    phydev->supported &= RT_PHY_DEFAULT_FEATURES;

    switch (max_speed)
    {
    default:
        return -ENOTSUP;
    case SPEED_1000:
        phydev->supported |= RT_PHY_1000BT_FEATURES;
    case SPEED_100:
        phydev->supported |= RT_PHY_100BT_FEATURES;
    case SPEED_10:
        phydev->supported |= RT_PHY_10BT_FEATURES;
    }

    return 0;
}

int rt_phy_read(struct rt_phy_device *phydev, int devad, int regnum)
{
    struct mii_bus *bus = phydev->bus;
    if(phydev->is_c45)
    {
        if(bus->read_c45)
            return bus->read_c45(bus, phydev->addr, devad, regnum);
    }

    if( bus && bus->read )
        return bus->read(bus, phydev->addr, devad, regnum);

    LOG_D("no read function\n");
    return -1;
}

int rt_phy_write(struct rt_phy_device *phydev, int devad, int regnum, rt_uint16_t val)
{
    struct mii_bus *bus = phydev->bus;
    if(phydev->is_c45)
    {
        if(bus->write_c45)
            return bus->write_c45(bus, phydev->addr, devad, regnum, val);
    }
    if( bus && bus->write )
        return bus->write(bus, phydev->addr, devad, regnum, val);

    LOG_D("no write function\n");
    return -1;
}

int rt_phy_startup(struct rt_phy_device *phydev)
{
    if(!phydev->drv)
    {
        LOG_D("PHY device hace no driver\n");
        return -1;
    }

    if (phydev->drv->startup)
        return phydev->drv->startup(phydev);

    LOG_D("phy startup err\n");
    return -1;
}

int rt_phy_config(struct rt_phy_device *phydev)
{
    if(!phydev->drv)
    {
        LOG_D("PHY device hace no driver\n");
        return -1;
    }

    if (phydev->drv->config)
        return phydev->drv->config(phydev);

    LOG_D("no config function\n");
    return -1;
}

int rt_phy_shutdown(struct rt_phy_device *phydev)
{
    if(!phydev->drv)
    {
        LOG_D("PHY device hace no driver\n");
        return -1;
    }

    if (phydev->drv->shutdown)
        phydev->drv->shutdown(phydev);

    LOG_D("no shutdown function\n");
    return -1;
}

void rt_phy_mmd_start_indirect(struct rt_phy_device *phydev, int devad, int regnum)
{
    /* Write the desired MMD Devad */
    rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, RT_MII_MMD_CTRL, devad);

    /* Write the desired MMD register address */
    rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, RT_MII_MMD_DATA, regnum);

    /* Select the Function : DATA with no post increment */
    rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, RT_MII_MMD_CTRL,
          (devad | RT_MII_MMD_CTRL_NOINCR));
}

int rt_phy_read_mmd(struct rt_phy_device *phydev, int devad, int regnum)
{
    struct rt_phy_driver *drv = phydev->drv;

    if (regnum > (rt_uint16_t)~0 || devad > 32 || !drv)
        return -EINVAL;

    if (drv->read_mmd)
        return drv->read_mmd(phydev, devad, regnum);

    if ((drv->features & RT_PHY_10G_FEATURES) == RT_PHY_10G_FEATURES ||
        devad == RT_MDIO_DEVAD_NONE || !devad)
        return rt_phy_read(phydev, devad, regnum);

    rt_phy_mmd_start_indirect(phydev, devad, regnum);

    return rt_phy_read(phydev, RT_MDIO_DEVAD_NONE, RT_MII_MMD_DATA);
}

int rt_phy_write_mmd(struct rt_phy_device *phydev, int devad, int regnum, rt_uint16_t val)
{
    struct rt_phy_driver *drv = phydev->drv;

    if (regnum > (rt_uint16_t)~0 || devad > 32 || !drv)
        return -EINVAL;

    if (drv->write_mmd)
        return drv->write_mmd(phydev, devad, regnum, val);

    if ((drv->features & RT_PHY_10G_FEATURES) == RT_PHY_10G_FEATURES ||
        devad == RT_MDIO_DEVAD_NONE || !devad)
        return rt_phy_write(phydev, devad, regnum, val);

    rt_phy_mmd_start_indirect(phydev, devad, regnum);

    return rt_phy_write(phydev, RT_MDIO_DEVAD_NONE, RT_MII_MMD_DATA, val);
}

int rt_phy_reset(struct rt_phy_device *phydev)
{
    int reg;
    int timeout = 500;
    int devad = RT_MDIO_DEVAD_NONE;

    if (phydev->flags & RT_PHY_FLAG_BROKEN_RESET)
        return 0;

    if (rt_phy_write(phydev, devad, RT_MII_BMCR, RT_BMCR_RESET) < 0)
    {
        LOG_D("PHY reset failed\n");
        return -1;
    }

    reg = rt_phy_read(phydev, devad, RT_MII_BMCR);
    while ((reg & RT_BMCR_RESET) && timeout--)
    {
        reg = rt_phy_read(phydev, devad, RT_MII_BMCR);

        if (reg < 0)
        {
            LOG_D("PHY status read failed\n");
            return -1;
        }
        rt_thread_mdelay(1);
    }

    if (reg & RT_BMCR_RESET)
    {
        LOG_D("PHY reset timed out\n");
        return -1;
    }

    return 0;
}

static struct rt_bus rt_phy_bus;

/**
 * @brief create a phy device
 *
 * Creates a new PHY device based on the given bus, address, PHY ID, and whether Clause 45 is supported.
 *
 * @param bus the pointer to the bus
 * @param addr PHY device address
 * @param phy_id PHY device id
 * @param is_c45 if suport Clause 45
 *
 * @return if create success return the phy device pointer,else return RT_NULL
 */
struct rt_phy_device *rt_phy_device_create(struct mii_bus *bus, int addr,
                     rt_uint32_t phy_id, rt_bool_t is_c45)
{
    struct rt_phy_device *dev = rt_malloc(sizeof(struct rt_phy_device));

    if (!dev)
    {
        LOG_E("Failed to allocate PHY device for %s:%d\n",
               bus ? bus->name : "(null bus)", addr);
        return RT_NULL;
    }

    memset(dev, 0, sizeof(*dev));

    dev->duplex = -1;
    dev->link = 0;
    dev->interface = RT_PHY_INTERFACE_MODE_NA;
#ifdef RT_USING_OFW
    dev->node = RT_NULL;
#endif
    dev->autoneg = RT_TRUE;

    dev->addr = addr;
    dev->phy_id = phy_id;
    dev->is_c45 = is_c45;
    dev->bus = bus;

    if(rt_phy_device_register(dev))
    {
        LOG_D("register phy device filed")
    }

    if (addr >= 0 && addr < RT_PHY_MAX && phy_id != RT_PHY_FIXED_ID &&
        phy_id != RT_PHY_NCSI_ID)
        bus->phymap[addr] = dev;

    return dev;
}

/**
 * @brief get phy id
 *
 * get phy id by read the register 2 and 3 of PHY device,
 * Register of the MII management interface stipulates that
 * register 2 contains thehigh 16 bits of the PHY’s identifier
 * the register 3 contains the low 16 bits of the PHY’s identifier
 *
 * @param bus MII bus pointer
 * @param addr  PHY device address
 * @param devad  dev addr if be set to zero it means c22 mode,else it means c45 mode
 * @param phy_id the phy id which will be read
 *
 * @return if read success return 0,else return -RT_EIO
 */
static int get_phy_id(struct mii_bus *bus, int addr, int devad, rt_uint32_t *phy_id)
{
    int phy_reg;

    phy_reg = bus->read(bus, addr, devad, RT_MII_PHYSID1);

    if (phy_reg < 0)
        return -RT_EIO;

    *phy_id = (phy_reg & 0xffff) << 16;

    phy_reg = bus->read(bus, addr, devad, RT_MII_PHYSID2);

    if (phy_reg < 0)
        return -RT_EIO;

    *phy_id |= (phy_reg & 0xffff);

    return 0;
}

/**
 * @brief create phy device by mask
 *
 * @param bus MII bus pointer
 * @param phy_mask the mask which phy addr corresponding will be set 1
 * @param devad dev addr if be set to zero it means c22 mode,else it means c45 mode
 *
 * @return if create success return the phy device pointer,if create fail return NULL
 */
static struct rt_phy_device *create_phy_by_mask(struct mii_bus *bus, unsigned int phy_mask,int devad)
{
    rt_uint32_t id = 0xffffffff;
    rt_bool_t is_c45;

    while (phy_mask)
    {
        int addr = __rt_ffs(phy_mask) - 1;
        int r = get_phy_id(bus, addr, devad, &id);

        if (r == 0 && id == 0)
        {
            phy_mask &= ~(1 << addr);
            continue;
        }

        if (r == 0 && (id & 0x1fffffff) != 0x1fffffff)
        {
            is_c45 = (devad == RT_MDIO_DEVAD_NONE) ? RT_FALSE : RT_TRUE;
            return rt_phy_device_create(bus, addr, id, is_c45);
        }

    }
    return RT_NULL;
}

/**
 * @brief create phy device by mask
 *
 * it will create phy device by c22 mode or c45 mode
 *
 * @param bus mii bus pointer
 * @param phy_mask PHY mask it depend on the phy addr, the phy addr corresponding will be set 1
 *
 * @return if create success return the phy device pointer,if create fail return NULL
 */
static struct rt_phy_device *rt_phydev_create_by_mask(struct mii_bus *bus, unsigned int phy_mask)
{
    struct rt_phy_device *phy;
    /*
     *The bit of devad is dev addr which is the new features in c45
     *so if devad equal to zero it means it is c22 mode ,and if not
     *equal to zero it means it is c45 mode,which include PMD/PMA ,
     *WIS ,PCS,PHY XS,PHY XS ....
    */
    int devad[] = {
        /* Clause-22 */
        RT_MDIO_DEVAD_NONE,
        /* Clause-45 */
        RT_MDIO_MMD_PMAPMD,
        RT_MDIO_MMD_WIS,
        RT_MDIO_MMD_PCS,
        RT_MDIO_MMD_PHYXS,
        RT_MDIO_MMD_VEND1,
    };

    for (int i = 0; i < sizeof(devad)/sizeof(devad[0]); i++)
    {
        phy = create_phy_by_mask(bus, phy_mask, devad[i]);
        if(phy)
            return phy;
    }

    return RT_NULL;
}

struct rt_phy_device *rt_phy_find_by_mask(struct mii_bus *bus, unsigned int phy_mask)
{
    struct rt_phy_device *phy;
    unsigned int mask = phy_mask;
    unsigned int addr;
    if (bus->reset)
    {
        bus->reset(bus);

        rt_thread_mdelay(15);
    }

    while (mask)
    {
        /*
         *Whichever bit of the mask is the 1,
         *which bit is the addr as the array subscript to search
         *such as mask = 1110 ,this loop will search for subscript
         *1,2,3,if the array subscript is not null then return it,
         *if the array subscript is null then continue to search
        */
        addr = __rt_ffs(mask) - 1;

        if (bus->phymap[addr])
            return bus->phymap[addr];

        mask &= ~(1U << addr);
    }
    /*ifcan't find phy device, create a new phy device*/
    phy = rt_phydev_create_by_mask(bus, phy_mask);

    return phy;

}

/**
 * @brief get phy device by given mii bus, node and address
 * @param bus MII bus pointer
 * @param np the dtb node of device which need to get phy device
 * @param addr address of phy device
 * @param interface interface of phy device
 *
 * @return phy device pointer or NULL if not found
 */
struct rt_phy_device *rt_phy_get_device(struct mii_bus *bus,struct rt_ofw_node *np, int addr,rt_phy_interface interface)
{
    struct rt_phy_device *phy = RT_NULL;
    unsigned int phy_mask = addr? 1 << addr:0xffffffff;

#ifdef RT_USING_OFW
    if(np)
        phy = rt_ofw_create_phy(bus,np,addr);
#endif
    if(!phy)
        phy = rt_phy_find_by_mask(bus,phy_mask);

    if(phy)
    {
        rt_phy_reset(phy);
        phy->interface = interface;
        return phy;
    }

    LOG_D("PHY device get failed");
    return RT_NULL;
}

static struct rt_phy_driver genphy = {
    .uid        = 0xffffffff,
    .mask       = 0xffffffff,
    .name       = "Generic PHY",
    .features   = RT_PHY_GBIT_FEATURES | RT_SUPPORTED_MII |
              RT_SUPPORTED_AUI | RT_SUPPORTED_FIBRE |
              RT_SUPPORTED_BNC,
    .config     = rt_genphy_config,
    .startup    = rt_genphy_startup,
};
RT_PHY_DRIVER_REGISTER(genphy);

rt_err_t rt_phy_device_register(struct rt_phy_device *pdev)
{
    rt_err_t err;
    RT_ASSERT(pdev != RT_NULL);
    err = rt_bus_add_device(&rt_phy_bus, &pdev->parent);
    if (err)
    {
        return err;
    }
    if(!pdev->drv)
        pdev->drv = &genphy;

    return RT_EOK;
}

rt_err_t rt_phy_driver_register(struct rt_phy_driver *pdrv)
{
    RT_ASSERT(pdrv != RT_NULL);

    pdrv->parent.bus = &rt_phy_bus;
#if RT_NAME_MAX > 0
    rt_strcpy(pdrv->parent.parent.name, pdrv->name);
#else
    pdrv->parent.parent.name = pdrv->name;
#endif

    return rt_driver_register(&pdrv->parent);
}

static rt_bool_t phy_match(rt_driver_t drv, rt_device_t dev)
{
    struct rt_phy_device *pdev = rt_container_of(dev, struct rt_phy_device, parent);
    struct rt_phy_driver *pdrv = rt_container_of(drv, struct rt_phy_driver, parent);
    if ((pdrv->uid & pdrv->mask) == (pdev->phy_id & pdrv->mask))
        return RT_TRUE;

    return RT_FALSE;

}

static rt_err_t phy_probe(rt_device_t dev)
{
    rt_err_t err = RT_EOK;
    struct rt_phy_driver *pdrv = rt_container_of(dev->drv, struct rt_phy_driver, parent);
    struct rt_phy_device *pdev = rt_container_of(dev, struct rt_phy_device, parent);
    pdev->drv = pdrv;
    pdev->advertising = pdev->drv->features;
    pdev->supported = pdev->drv->features;

    pdev->mmds = pdev->drv->mmds;
    if(pdrv->probe)
        err = pdrv->probe(pdev);

    return err;
}

static struct rt_bus rt_phy_bus =
{
    .name = "phy",
    .match = phy_match,
    .probe = phy_probe,
};

static int rt_phy_bus_init(void)
{
    rt_bus_register(&rt_phy_bus);

    return 0;
}
INIT_CORE_EXPORT(rt_phy_bus_init);
#endif
