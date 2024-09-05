/*
 * Copyright (C) Cvitek Co., Ltd. 2019-2020. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <rtthread.h>

#include "cvi_eth_phy.h"

#define CSI_ETH_AUTONEG_DISABLE         (0)     ///< Disable auto-negotiation
#define CSI_ETH_AUTONEG_ENABLE          (1)     ///< Enable auto-negotiation

#define CONFIG_ETH_PHY_NUM 2

eth_phy_priv_t  phy_priv_list[CONFIG_ETH_PHY_NUM];

extern eth_phy_dev_t cv181x_device;

/* registered phy devices */
static eth_phy_dev_t *const eth_phy_devices[] = {
    &cv181x_device,
    NULL /* Must be the last item */
};

int32_t eth_phy_read(eth_phy_priv_t *priv, uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
{
    RT_ASSERT(priv);
    RT_ASSERT(priv->phy_read);
    return priv->phy_read(phy_addr, reg_addr, data);
}

int32_t eth_phy_write(eth_phy_priv_t *priv, uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
{
    RT_ASSERT(priv);
    RT_ASSERT(priv->phy_write);
    return priv->phy_write(phy_addr, reg_addr, data);
}

static eth_phy_dev_t *eth_get_phy_device(eth_phy_priv_t *priv, uint8_t phy_addr, uint32_t phy_id)
{
    eth_phy_dev_t *p = eth_phy_devices[0];
    int32_t i = 0;

    while (p != NULL)
    {
        if ((p->phy_id & p->mask) == (phy_id & p->mask))
        {
            p->phy_addr = phy_addr;
            p->advertising = p->supported = p->features;
            return p;
        }

        i ++;
        p = eth_phy_devices[i];
    }

    return NULL;
}

static int32_t eth_read_phy_id(eth_phy_priv_t *priv, uint8_t phy_addr, uint32_t *phy_id)
{
    int32_t ret;
    uint16_t data;
    uint32_t id;

    ret = eth_phy_read(priv, phy_addr, CVI_MII_PHYSID1, &data);

    if (ret != 0)
    {
        return ret;
    }

    id = data;
    id = (id & 0xffff) << 16;

    ret = eth_phy_read(priv, phy_addr, CVI_MII_PHYSID2, &data);

    if (ret != 0)
    {
        return ret;
    }

    id |= (data & 0xffff);

    if (phy_id != NULL)
    {
        *phy_id = id;
    }

    return 0;
}

/*
 * ffs: find first bit set. This is defined the same way as
 * the libc and compiler builtin ffs routines, therefore
 * differs in spirit from the above ffz (man ffs).
 */
static inline int32_t ffs(int32_t x)
{
    int32_t r = 1;

    if (!x)
        return 0;

    if (!(x & 0xffff))
    {
        x >>= 16;
        r += 16;
    }

    if (!(x & 0xff))
    {
        x >>= 8;
        r += 8;
    }

    if (!(x & 0xf))
    {
        x >>= 4;
        r += 4;
    }

    if (!(x & 3))
    {
        x >>= 2;
        r += 2;
    }

    if (!(x & 1))
    {
        x >>= 1;
        r += 1;
    }

    return r;
}

static eth_phy_dev_t * eth_get_phy_by_mask(eth_phy_priv_t *priv, uint32_t phy_mask, phy_if_mode_t interface)
{
    uint32_t phy_id = 0xffffffff;

    while (phy_mask)
    {
        int32_t addr = ffs(phy_mask) - 1;
        int32_t r = eth_read_phy_id(priv, addr, &phy_id);

        /* If the PHY ID is mostly f's, we didn't find anything */
        if (r == 0 && (phy_id & 0x1fffffff) != 0x1fffffff)
            return eth_get_phy_device(priv, addr, phy_id);

        phy_mask &= ~(1 << addr);
    }
    return NULL;
}

static void eth_config(void)
{
    unsigned int val;

    val = mmio_read_32(ETH_PHY_BASE) & ETH_PHY_INIT_MASK;
    mmio_write_32(ETH_PHY_BASE, (val | ETH_PHY_SHUTDOWN) & ETH_PHY_RESET);
    rt_thread_mdelay(1);
    mmio_write_32(ETH_PHY_BASE, val & ETH_PHY_POWERUP & ETH_PHY_RESET);
    rt_thread_mdelay(20);
    mmio_write_32(ETH_PHY_BASE, (val & ETH_PHY_POWERUP) | ETH_PHY_RESET_N);
    rt_thread_mdelay(1);
}

static eth_phy_dev_t *eth_connect_phy(eth_phy_priv_t *priv, uint32_t phy_mask, phy_if_mode_t interface)
{
    int32_t i;
    eth_phy_dev_t *phydev = NULL;

    /* config eth internal phy on ASIC board */
    eth_config();

#ifdef CONFIG_PHY_ADDR
    phy_mask = 1 << CONFIG_PHY_ADDR;
#endif

    for (i = 0; i < 5; i++)
    {
        phydev = eth_get_phy_by_mask(priv, phy_mask, interface);
        if (phydev)
            return phydev;
    }

    rt_kprintf("\n PHY: ");
    while (phy_mask)
    {
        int32_t addr = ffs(phy_mask) - 1;
        rt_kprintf("%d ", addr);
        phy_mask &= ~(1 << addr);
    }
    rt_kprintf("not found\n");

    return NULL;
}

int32_t eth_phy_reset(eth_phy_handle_t handle)
{
    RT_ASSERT(handle);
    eth_phy_dev_t *dev = (eth_phy_dev_t *)handle;
    RT_ASSERT(dev->priv);

    uint16_t data;
    int32_t ret;
    int32_t timeout = 600;                                  /* in ms */
    eth_phy_priv_t *priv = dev->priv;
    uint32_t phy_addr = dev->phy_addr;

    /* Soft reset */
    ret = eth_phy_read(priv, phy_addr, CVI_MII_BMCR, &data);
    if (ret != 0)
    {
        rt_kprintf("eth phy read failed\n");
        return ret;
    }

    ret = eth_phy_write(priv, phy_addr, CVI_MII_BMCR, data | CVI_BMCR_RESET);
    if (ret != 0)
    {
        rt_kprintf("eth phy write failed\n");
        return ret;
    }

#ifdef CONFIG_PHY_RESET_DELAY
    rt_hw_us_delay(CONFIG_PHY_RESET_DELAY); /* Intel LXT971A needs this */
#endif
    /*
     * Wait up to 0.6s for the reset sequence to finish. According to
     * IEEE 802.3, Section 2, Subsection 22.2.4.1.1 a PHY reset may take
     * up to 0.5 s.
     */
    ret = eth_phy_read(priv, phy_addr, CVI_MII_BMCR, &data);
    while ((data & CVI_BMCR_RESET) && timeout--)
    {
        ret = eth_phy_read(priv, phy_addr, CVI_MII_BMCR, &data);

        if (ret != 0) {
            return ret;
        }

        rt_thread_mdelay(1);
    }

    if (data & CVI_BMCR_RESET)
    {
        rt_kprintf("eth phy reset timed out\n");
        return -1;
    }

    return 0;
}

int32_t eth_phy_config(eth_phy_handle_t handle)
{
    RT_ASSERT(handle);
    eth_phy_dev_t *dev = (eth_phy_dev_t *)handle;

    if (dev->config)
    {
        return dev->config(handle);
    }

    return 0;
}

int32_t eth_phy_start(eth_phy_handle_t handle)
{
    RT_ASSERT(handle);
    eth_phy_dev_t *dev = (eth_phy_dev_t *)handle;

    if (dev->start)
    {
        return dev->start(handle);
    }

    return 0;
}

int32_t eth_phy_stop(eth_phy_handle_t handle)
{
    RT_ASSERT(handle);
    eth_phy_dev_t *dev = (eth_phy_dev_t *)handle;

    if (dev->start) {
        return dev->stop(handle);
    }

    return 0;
}

int32_t cvi_eth_phy_power_control(eth_phy_handle_t handle, eth_power_state_t state)
{
    if (state == CSI_ETH_POWER_FULL)
    {
        return eth_phy_start(handle);
    }
    else if (state == CSI_ETH_POWER_OFF)
    {
        return eth_phy_stop(handle);
    }

    return 0;
}

int32_t genphy_update_link(eth_phy_dev_t *phy_dev)
{
    uint8_t phy_addr = phy_dev->phy_addr;
    uint16_t mii_reg;
    int32_t ret;

    /*
     * Wait if the link is up, and autonegotiation is in progress
     * (ie - we're capable and it's not done)
     */
    ret = eth_phy_read(phy_dev->priv, phy_addr, CVI_MII_BMSR, &mii_reg);

    if (ret != 0) {
        return ret;
    }

    /*
     * If we already saw the link up, and it hasn't gone down, then
     * we don't need to wait for autoneg again
     */
    if (phy_dev->link_state && mii_reg & CVI_BMSR_LSTATUS)
        return 0;

    if ((phy_dev->priv->link_info.autoneg == CSI_ETH_AUTONEG_ENABLE) &&
        !(mii_reg & CVI_BMSR_ANEGCOMPLETE)) {

        phy_dev->link_state = ETH_LINK_DOWN;
        return -1;
    } else {

        /* Read the link a second time to clear the latched state */
        ret = eth_phy_read(phy_dev->priv, phy_addr, CVI_MII_BMSR, &mii_reg);

        if (ret != 0) {
            return ret;
        }

        if (mii_reg & CVI_BMSR_LSTATUS)
            phy_dev->link_state = ETH_LINK_UP;
        else
            phy_dev->link_state = ETH_LINK_DOWN;
    }

    return 0;
}

int32_t eth_phy_update_link(eth_phy_handle_t handle)
{
    RT_ASSERT(handle);
    eth_phy_dev_t *dev = (eth_phy_dev_t *)handle;

    if (dev->update_link) {
        return dev->update_link(handle);
    } else {
        return genphy_update_link(dev);
    }
}

static int32_t genphy_config_advert(eth_phy_dev_t *phy_dev)
{
    RT_ASSERT(phy_dev->priv);

    eth_phy_priv_t *priv = phy_dev->priv;
    uint8_t phy_addr = phy_dev->phy_addr;
    uint32_t advertise;
    uint16_t oldadv, adv, bmsr;
    int32_t changed = 0;
    int32_t ret;

    /* Only allow advertising what this PHY supports */
    phy_dev->advertising &= phy_dev->supported;
    advertise = phy_dev->advertising;

    /* Setup standard advertisement */
    ret = eth_phy_read(priv, phy_addr, CVI_MII_ADVERTISE, &adv);
    if (ret != 0) {
        return ret;
    }
    oldadv = adv;

    if (adv < 0)
        return adv;

    adv &= ~(CVI_ADVERTISE_ALL | CVI_ADVERTISE_100BASE4 | CVI_ADVERTISE_PAUSE_CAP |
         CVI_ADVERTISE_PAUSE_ASYM);
    if (advertise & CVI_ADVERTISED_10baseT_Half)
        adv |= CVI_ADVERTISE_10HALF;
    if (advertise & CVI_ADVERTISED_10baseT_Full)
        adv |= CVI_ADVERTISE_10FULL;
    if (advertise & CVI_ADVERTISED_100baseT_Half)
        adv |= CVI_ADVERTISE_100HALF;
    if (advertise & CVI_ADVERTISED_100baseT_Full)
        adv |= CVI_ADVERTISE_100FULL;
    if (advertise & CVI_ADVERTISED_Pause)
        adv |= CVI_ADVERTISE_PAUSE_CAP;
    if (advertise & CVI_ADVERTISED_Asym_Pause)
        adv |= CVI_ADVERTISE_PAUSE_ASYM;
    if (advertise & CVI_ADVERTISED_1000baseX_Half)
        adv |= CVI_ADVERTISE_1000XHALF;
    if (advertise & CVI_ADVERTISED_1000baseX_Full)
        adv |= CVI_ADVERTISE_1000XFULL;

    if (adv != oldadv) {
        ret = eth_phy_write(priv, phy_addr, CVI_MII_ADVERTISE, adv);

        if (ret != 0) {
            return ret;
        }
        changed = 1;
    }

    ret = eth_phy_read(priv, phy_addr, CVI_MII_BMSR, &bmsr);

    if (ret != 0 || bmsr < 0) {
        return ret;
    }

    /* Per 802.3-2008, Section 22.2.4.2.16 Extended status all
     * 1000Mbits/sec capable PHYs shall have the CVI_BMSR_ESTATEN bit set to a
     * logical 1.
     */
    if (!(bmsr & CVI_BMSR_ESTATEN))
        return changed;

    /* Configure gigabit if it's supported */
    ret = eth_phy_read(priv, phy_addr, CVI_MII_CTRL1000, &adv);

    if (ret != 0 || adv < 0) {
        return ret;
    }

    oldadv = adv;

    adv &= ~(CVI_ADVERTISE_1000FULL | CVI_ADVERTISE_1000HALF);

    if (phy_dev->supported & (CVI_SUPPORTED_1000baseT_Half |
                CVI_SUPPORTED_1000baseT_Full)) {
        if (advertise & CVI_SUPPORTED_1000baseT_Half)
            adv |= CVI_ADVERTISE_1000HALF;
        if (advertise & CVI_SUPPORTED_1000baseT_Full)
            adv |= CVI_ADVERTISE_1000FULL;
    }

    if (adv != oldadv)
        changed = 1;

    ret = eth_phy_write(priv, phy_addr, CVI_MII_CTRL1000, adv);

    if (ret != 0) {
        return ret;
    }

    return changed;
}

static int32_t genphy_setup_forced(eth_phy_dev_t *phy_dev)
{
    RT_ASSERT(phy_dev->priv);

    eth_phy_priv_t *priv = phy_dev->priv;
    uint8_t phy_addr = phy_dev->phy_addr;
    int32_t ctl = CVI_BMCR_ANRESTART;
    int32_t ret;

    if (CSI_ETH_SPEED_1G == priv->link_info.speed)
        ctl |= CVI_BMCR_SPEED1000;
    else if (CSI_ETH_SPEED_100M == priv->link_info.speed)
        ctl |= CVI_BMCR_SPEED100;
    else//CSI_ETH_SPEED_10M == priv->link_info.speed
        ctl |= CVI_BMCR_SPEED100;

    if (CSI_ETH_DUPLEX_FULL == priv->link_info.duplex)
        ctl |= CVI_BMCR_FULLDPLX;

    ret = eth_phy_write(priv, phy_addr, CVI_MII_BMCR, ctl);

    return ret;
}

int genphy_restart_aneg(eth_phy_dev_t *phy_dev)
{
    int32_t ret;
    uint16_t ctl;
    ret = eth_phy_read(phy_dev->priv, phy_dev->phy_addr, CVI_MII_BMCR, &ctl);

    if (ret != 0 || ctl < 0)
        return ret;

    ctl |= (CVI_BMCR_ANENABLE | CVI_BMCR_ANRESTART);

    /* Don't isolate the PHY if we're negotiating */
    ctl &= ~(CVI_BMCR_ISOLATE);

    ret = eth_phy_write(phy_dev->priv, phy_dev->phy_addr, CVI_MII_BMCR, ctl);

    return ret;
}

int32_t genphy_config_aneg(eth_phy_dev_t *phy_dev)
{
    RT_ASSERT(phy_dev->priv);

    eth_phy_priv_t *priv = phy_dev->priv;
    uint8_t phy_addr = phy_dev->phy_addr;
    int32_t result;
    uint16_t ctl;
    int32_t ret;

    if (CSI_ETH_AUTONEG_ENABLE != priv->link_info.autoneg)
        return genphy_setup_forced(phy_dev);

    result = genphy_config_advert(phy_dev);

    if (result < 0) /* error */
        return result;

    if (result == 0) {
        /* Advertisment hasn't changed, but maybe aneg was never on to
         * begin with?  Or maybe phy was isolated? */
        ret = eth_phy_read(priv, phy_addr, CVI_MII_BMCR, &ctl);
        if (ret != 0 || ctl < 0)
            return ret;

        if (!(ctl & CVI_BMCR_ANENABLE) || (ctl & CVI_BMCR_ISOLATE))
            result = 1; /* do restart aneg */
    }

    /* Only restart aneg if we are advertising something different
     * than we were before.  */
    if (result > 0)
        result = genphy_restart_aneg(phy_dev);

    return result;
}

int32_t genphy_config(eth_phy_dev_t *phy_dev)
{
    RT_ASSERT(phy_dev->priv);

    eth_phy_priv_t *priv = phy_dev->priv;
    uint8_t phy_addr = phy_dev->phy_addr;
    int32_t ret;
    uint16_t val;
    uint32_t features;

    features = (CVI_SUPPORTED_TP | CVI_SUPPORTED_MII
            | CVI_SUPPORTED_AUI | CVI_SUPPORTED_FIBRE |
            CVI_SUPPORTED_BNC);

    /* Do we support autonegotiation? */
    ret = eth_phy_read(priv, phy_addr, CVI_MII_BMSR, &val);
    if (ret != 0 || val < 0)
        return ret;

    if (val & CVI_BMSR_ANEGCAPABLE)
        features |= CVI_SUPPORTED_Autoneg;

    if (val & CVI_BMSR_100FULL)
        features |= CVI_SUPPORTED_100baseT_Full;
    if (val & CVI_BMSR_100HALF)
        features |= CVI_SUPPORTED_100baseT_Half;
    if (val & CVI_BMSR_10FULL)
        features |= CVI_SUPPORTED_10baseT_Full;
    if (val & CVI_BMSR_10HALF)
        features |= CVI_SUPPORTED_10baseT_Half;

    if (val & CVI_BMSR_ESTATEN) {
        ret = eth_phy_read(priv, phy_addr, CVI_MII_ESTATUS, &val);
        if (ret != 0 || val < 0)
            return val;

        if (val & CVI_ESTATUS_1000_TFULL)
            features |= CVI_SUPPORTED_1000baseT_Full;
        if (val & CVI_ESTATUS_1000_THALF)
            features |= CVI_SUPPORTED_1000baseT_Half;
        if (val & CVI_ESTATUS_1000_XFULL)
            features |= CVI_SUPPORTED_1000baseX_Full;
        if (val & CVI_ESTATUS_1000_XHALF)
            features |= CVI_SUPPORTED_1000baseX_Half;
    }

    phy_dev->supported &= features;
    phy_dev->advertising &= features;

    genphy_config_aneg(phy_dev);

    return 0;
}

eth_phy_handle_t cvi_eth_phy_init(csi_eth_phy_read_t  fn_read, csi_eth_phy_write_t fn_write)
{
    eth_phy_dev_t *phy_dev;
    eth_phy_priv_t *priv;
    uint32_t phy_mask = 0xffffffff;
    phy_if_mode_t interface = 0;

    RT_ASSERT(fn_read != RT_NULL);
    RT_ASSERT(fn_write != RT_NULL);

    priv = &phy_priv_list[0];

    priv->phy_read = fn_read;
    priv->phy_write = fn_write;
    priv->link_info.autoneg = CSI_ETH_AUTONEG_ENABLE;

    phy_dev = eth_connect_phy(priv, phy_mask, interface);
    if (phy_dev == NULL) {
        rt_kprintf("No phy device found!\n");
        return NULL;
    }
    rt_kprintf("connect phy id: 0x%X\n", phy_dev->phy_id);

    phy_dev->priv = priv;

    /* Reset PHY */
    eth_phy_reset(phy_dev);

    /* Config PHY */
    eth_phy_config(phy_dev);

    return phy_dev;
}
