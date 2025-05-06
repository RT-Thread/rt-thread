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
#include <mmu.h>

#include "dw_eth_mac.h"
#include "cache.h"
#include "string.h"
#include "drv_ioremap.h"


#define roundup(x, y) (                 \
{                           \
    const typeof(y) __y = y;            \
    (((x) + (__y - 1)) / __y) * __y;        \
}                           \
)

#define CONFIG_GMAC_NUM 2

static gmac_dev_t gmac_instance[CONFIG_GMAC_NUM];

static int32_t designware_read_hwaddr(eth_mac_handle_t handle)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_mac_regs *mac_reg = mac_dev->priv->mac_regs_p;
    uint32_t macid_lo, macid_hi;
    uint8_t mac_id[6] = {0};

    macid_hi = mac_reg->macaddr0hi;
    macid_lo = mac_reg->macaddr0lo;

    mac_id[0] = macid_lo & 0xff;
    mac_id[1] = (macid_lo >> 8) & 0xff;
    mac_id[2] = (macid_lo >> 16) & 0xff;
    mac_id[3] = (macid_lo >> 24) & 0xff;
    mac_id[4] = macid_hi & 0xff;
    mac_id[5] = (macid_hi >> 8) & 0xff;

    memcpy(mac_dev->mac_addr, mac_id, sizeof(mac_id));

    return 0;
}

static int32_t designware_write_hwaddr(eth_mac_handle_t handle)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_mac_regs *mac_reg = mac_dev->priv->mac_regs_p;

    uint32_t macid_lo, macid_hi;
    uint8_t *mac_id = mac_dev->mac_addr;

    macid_lo = mac_id[0] + (mac_id[1] << 8) + (mac_id[2] << 16) +
           (mac_id[3] << 24);
    macid_hi = mac_id[4] + (mac_id[5] << 8);

    mac_reg->macaddr0hi = macid_hi;
    mac_reg->macaddr0lo = macid_lo;

    return 0;
}

static void tx_descs_init(eth_mac_handle_t handle)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_priv *priv = mac_dev->priv;
    struct dw_gmac_dma_regs *dma_reg = priv->dma_regs_p;
    struct dmamacdescr *desc_table_p = &priv->tx_mac_descrtable[0];
    char *txbuffs = &priv->txbuffs[0];
    struct dmamacdescr *desc_p;
    uint32_t idx;

    for (idx = 0; idx < CVI_CONFIG_TX_DESCR_NUM; idx ++) {
        desc_p = &desc_table_p[idx];
#ifdef RT_USING_SMART
        desc_p->dmamac_addr = (unsigned long)rt_kmem_v2p((void *)&txbuffs[idx * CVI_CONFIG_ETH_BUFSIZE]);
        desc_p->dmamac_next = (unsigned long)rt_kmem_v2p((void *)&desc_table_p[idx + 1]);
#else
        desc_p->dmamac_addr = (unsigned long)&txbuffs[idx * CVI_CONFIG_ETH_BUFSIZE];
        desc_p->dmamac_next = (unsigned long)&desc_table_p[idx + 1];
#endif

#if defined(CONFIG_DW_ALTDESCRIPTOR)
        desc_p->txrx_status &= ~(CVI_DESC_TXSTS_TXINT | CVI_DESC_TXSTS_TXLAST |
                CVI_DESC_TXSTS_TXFIRST | CVI_DESC_TXSTS_TXCRCDIS |
                CVI_DESC_TXSTS_TXCHECKINSCTRL |
                CVI_DESC_TXSTS_TXRINGEND | CVI_DESC_TXSTS_TXPADDIS);

        desc_p->txrx_status |= CVI_DESC_TXSTS_TXCHAIN;
        desc_p->dmamac_cntl = 0;
        desc_p->txrx_status &= ~(CVI_DESC_TXSTS_MSK | CVI_DESC_TXSTS_OWNBYDMA);
#else
        desc_p->dmamac_cntl = CVI_DESC_TXCTRL_TXCHAIN;
        desc_p->txrx_status = 0;
#endif
    }

    /* Correcting the last pointer of the chain */
    #ifdef RT_USING_SMART
    desc_p->dmamac_next = (unsigned long)rt_kmem_v2p((void *)&desc_table_p[0]);
    #else
    desc_p->dmamac_next = (unsigned long)&desc_table_p[0];
    #endif

    /* Flush all Tx buffer descriptors at once */
    rt_hw_cpu_dcache_clean((void *)priv->tx_mac_descrtable, sizeof(priv->tx_mac_descrtable));

#ifdef RT_USING_SMART
    dma_reg->txdesclistaddr = (rt_ubase_t)rt_kmem_v2p((void *)&desc_table_p[0]);
#else
    dma_reg->txdesclistaddr = (reg_type)&desc_table_p[0];
#endif

    priv->tx_currdescnum = 0;
}

static void rx_descs_init(eth_mac_handle_t handle)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_priv *priv = mac_dev->priv;
    struct dw_gmac_dma_regs *dma_reg = priv->dma_regs_p;
    struct dmamacdescr *desc_table_p = &priv->rx_mac_descrtable[0];
    char *rxbuffs = &priv->rxbuffs[0];
    struct dmamacdescr *desc_p;
    uint32_t idx;

    /* Before passing buffers to GMAC we need to make sure zeros
     * written there right after "priv" structure allocation were
     * flushed into RAM.
     * Otherwise there's a chance to get some of them flushed in RAM when
     * GMAC is already pushing data to RAM via DMA. This way incoming from
     * GMAC data will be corrupted. */
    rt_hw_cpu_dcache_clean((void *)rxbuffs, CVI_RX_TOTAL_BUFSIZE);

    for (idx = 0; idx < CVI_CONFIG_RX_DESCR_NUM; idx++) {
        desc_p = &desc_table_p[idx];
#ifdef RT_USING_SMART
        desc_p->dmamac_addr = (unsigned long)rt_kmem_v2p((void *)&rxbuffs[idx * CVI_CONFIG_ETH_BUFSIZE]);
        desc_p->dmamac_next = (unsigned long)rt_kmem_v2p((void *)&desc_table_p[idx + 1]);
#else
        desc_p->dmamac_addr = (unsigned long)&rxbuffs[idx * CVI_CONFIG_ETH_BUFSIZE];
        desc_p->dmamac_next = (unsigned long)&desc_table_p[idx + 1];
#endif

        desc_p->dmamac_cntl = (CVI_MAC_MAX_FRAME_SZ & CVI_DESC_RXCTRL_SIZE1MASK) | CVI_DESC_RXCTRL_RXCHAIN;

        desc_p->txrx_status = CVI_DESC_RXSTS_OWNBYDMA;
    }

    /* Correcting the last pointer of the chain */
#ifdef RT_USING_SMART
    desc_p->dmamac_next = (unsigned long)rt_kmem_v2p((void *)&desc_table_p[0]);
#else
    desc_p->dmamac_next = (unsigned long)&desc_table_p[0];
#endif

    /* Flush all Rx buffer descriptors at once */
    rt_hw_cpu_dcache_clean((void *)priv->rx_mac_descrtable, sizeof(priv->rx_mac_descrtable));

#ifdef RT_USING_SMART
    dma_reg->rxdesclistaddr = (rt_ubase_t)rt_kmem_v2p((void *)&desc_table_p[0]);
#else
    dma_reg->rxdesclistaddr = (reg_type)&desc_table_p[0];
#endif

    priv->rx_currdescnum = 0;
}

static int32_t designware_adjust_link(eth_mac_handle_t handle)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_priv *priv = mac_dev->priv;
    struct dw_gmac_mac_regs *mac_reg = priv->mac_regs_p;
    eth_link_info_t *link_info = &mac_dev->phy_dev->priv->link_info;
    eth_link_state_t link_state = mac_dev->phy_dev->link_state;

    uint32_t conf = mac_reg->conf | CVI_FRAMEBURSTENABLE | CVI_DISABLERXOWN;

    if (!link_state) {
        rt_kprintf("eth No link.\n");
        return 0;
    }

    if (link_info->speed != CSI_ETH_SPEED_1G)
        conf |= CVI_MII_PORTSELECT;
    else
        conf &= ~CVI_MII_PORTSELECT;

    if (link_info->speed == CSI_ETH_SPEED_100M)
        conf |= CVI_FES_100;

    if (link_info->duplex)
        conf |= CVI_FULLDPLXMODE;

    mac_reg->conf = conf;

    rt_kprintf("Speed: %s, duplex: %s\n",
            (link_info->speed) ? "100M" : "10M",
           (link_info->duplex) ? "full" : "half");

    return 0;
}

static int32_t designware_eth_init(eth_mac_handle_t handle)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_mac_regs *mac_reg = mac_dev->priv->mac_regs_p;
    struct dw_gmac_dma_regs *dma_reg = mac_dev->priv->dma_regs_p;

    uint32_t start;

    dma_reg->busmode |= CVI_DMAMAC_SRST;

    start = rt_tick_get_millisecond();
    while (dma_reg->busmode & CVI_DMAMAC_SRST) {
        if ((rt_tick_get_millisecond() - start) >= CVI_CONFIG_MACRESET_TIMEOUT) {
            rt_kprintf("DMA reset timeout\n");
            return -ETIMEDOUT;
        }

        rt_thread_mdelay(100);
    };

    /*
     * Soft reset above clears HW address registers.
     * So we have to set it here once again.
     */
    // designware_read_hwaddr(handle);
    // designware_write_hwaddr(handle);

    rx_descs_init(handle);
    tx_descs_init(handle);

    dma_reg->busmode = (CVI_FIXEDBURST | CVI_PRIORXTX_41 | CVI_DMA_PBL);

    // mac_reg->framefilt = 0x10;
    // mac_reg->flowcontrol = 0x8;
    // dma_reg->wdtforri = 0xff;
    // dma_reg->axibus = 0x0012100F;

#ifndef CONFIG_DW_MAC_FORCE_THRESHOLD_MODE
    dma_reg->opmode |= (CVI_FLUSHTXFIFO | CVI_STOREFORWARD);
#else
    dma_reg->opmode |= CVI_FLUSHTXFIFO;
#endif

    dma_reg->opmode |= (CVI_RXSTART | CVI_TXSTART);
    dma_reg->opmode = 0x2202906;
    dma_reg->busmode = 0x3900800;
    mac_reg->conf = 0x41cc00;
    dma_reg->intenable = 0x10040;

#ifdef CONFIG_DW_AXI_BURST_LEN
    dma_reg->axibus = (CONFIG_DW_AXI_BURST_LEN & 0x1FF >> 1);
#endif

    /* Start up the PHY */
    /* adjust link */
    return 0;
}

static int32_t designware_eth_enable(eth_mac_handle_t handle, int32_t control)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_mac_regs *mac_reg = mac_dev->priv->mac_regs_p;
    eth_link_state_t link_state = mac_dev->phy_dev->link_state;

    // if (link_state == ETH_LINK_DOWN)
    //     return -1;

    switch (control) {
    case CSI_ETH_MAC_CONTROL_TX:
        mac_reg->conf |= CVI_TXENABLE;
        break;
    case CSI_ETH_MAC_CONTROL_RX:
        mac_reg->conf |= CVI_RXENABLE;
        break;
    default:
        break;
    }

    return 0;
}
static int32_t designware_eth_disable(eth_mac_handle_t handle, int32_t arg)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_mac_regs *mac_reg = mac_dev->priv->mac_regs_p;

    switch (arg) {
    case CSI_ETH_MAC_CONTROL_TX:
        mac_reg->conf &= ~CVI_TXENABLE;
        break;
    case CSI_ETH_MAC_CONTROL_RX:
        mac_reg->conf &= ~CVI_RXENABLE;
        break;
    default:
        break;
    }

    return 0;
}

static int32_t designware_eth_start(eth_mac_handle_t handle)
{
    int32_t ret;

    ret = designware_eth_init(handle);
    if (ret)
        return ret;

    return 0;
}

void designware_eth_stop(eth_mac_handle_t handle)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_mac_regs *mac_reg = mac_dev->priv->mac_regs_p;
    struct dw_gmac_dma_regs *dma_reg = mac_dev->priv->dma_regs_p;

    mac_reg->conf &= ~(CVI_RXENABLE | CVI_TXENABLE);
    dma_reg->opmode &= ~(CVI_RXSTART | CVI_TXSTART);

    //phy_shutdown(priv->phydev);
}

static int32_t designware_eth_send(eth_mac_handle_t handle, const uint8_t *frame, uint32_t length)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_priv *priv = mac_dev->priv;
    struct dw_gmac_dma_regs *dma_reg = mac_dev->priv->dma_regs_p;
    uint32_t desc_num = priv->tx_currdescnum;
    struct dmamacdescr *desc_p = &priv->tx_mac_descrtable[desc_num];
    uint64_t desc_start = (uint64_t)desc_p;
    uint64_t desc_end = desc_start + roundup(sizeof(*desc_p), DW_GMAC_DMA_ALIGN);
    uint64_t data_start = (uint64_t)DRV_IOREMAP((void *)desc_p->dmamac_addr, 0x1000);
    uint64_t data_end = data_start + roundup(length, DW_GMAC_DMA_ALIGN);
    uint32_t count = 0;

    /*
     * Strictly we only need to invalidate the "txrx_status" field
     * for the following check, but on some platforms we cannot
     * invalidate only 4 bytes, so we flush the entire descriptor,
     * which is 16 bytes in total. This is safe because the
     * individual descriptors in the array are each aligned to
     * DW_GMAC_DMA_ALIGN and padded appropriately.
     */

    /* Check if the descriptor is owned by CPU */
    while (1)
    {
        rt_hw_cpu_dcache_invalidate((void *)desc_start, desc_end - desc_start);
        if (!(desc_p->txrx_status & CVI_DESC_TXSTS_OWNBYDMA))
        {
            break;
        }

        if (count > 1000)
        {
            rt_kprintf("desc onwer is DMA\n");
            return -1;
        }
        count ++;
        rt_thread_mdelay(1);
    }

    memcpy((void *)data_start, frame, length);

    /* Flush data to be sent */
    rt_hw_cpu_dcache_clean((void *)data_start, data_end - data_start);

#if defined(CONFIG_DW_ALTDESCRIPTOR)
    desc_p->txrx_status |= CVI_DESC_TXSTS_TXFIRST | CVI_DESC_TXSTS_TXLAST;
    desc_p->dmamac_cntl &= ~CVI_DESC_TXCTRL_SIZE1MASK;
    desc_p->dmamac_cntl |= (length << CVI_DESC_TXCTRL_SIZE1SHFT) &
                   CVI_DESC_TXCTRL_SIZE1MASK;

    desc_p->txrx_status &= ~(CVI_DESC_TXSTS_MSK);
    desc_p->txrx_status |= CVI_DESC_TXSTS_OWNBYDMA;
#else
    desc_p->dmamac_cntl &= ~CVI_DESC_TXCTRL_SIZE1MASK;
    desc_p->dmamac_cntl |= ((length << CVI_DESC_TXCTRL_SIZE1SHFT) &
                   CVI_DESC_TXCTRL_SIZE1MASK) | CVI_DESC_TXCTRL_TXLAST |
                   CVI_DESC_TXCTRL_TXFIRST;

    desc_p->txrx_status = CVI_DESC_TXSTS_OWNBYDMA;
#endif

    /* Flush modified buffer descriptor */
    rt_hw_cpu_dcache_clean((void *)desc_start, desc_end - desc_start);

    /* Test the wrap-around condition. */
    if (++desc_num >= CVI_CONFIG_TX_DESCR_NUM)
        desc_num = 0;

    priv->tx_currdescnum = desc_num;

    /* Start the transmission */
    dma_reg->txpolldemand = CVI_POLL_DATA;

    return 0;
}

static int32_t designware_eth_recv(eth_mac_handle_t handle, uint8_t **packetp)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_priv *priv = mac_dev->priv;
    uint32_t status, desc_num = priv->rx_currdescnum;
    struct dmamacdescr *desc_p = &priv->rx_mac_descrtable[desc_num];
    int32_t length = -1;
    uint64_t desc_start = (uint64_t)desc_p;
    uint64_t desc_end = desc_start + roundup(sizeof(*desc_p), DW_GMAC_DMA_ALIGN);
    uint64_t data_start = (uint64_t)DRV_IOREMAP((void *)desc_p->dmamac_addr, 0x1000);
    uint64_t data_end;

    /* Invalidate entire buffer descriptor */
    rt_hw_cpu_dcache_invalidate((void *)desc_start, desc_end - desc_start);
    status = desc_p->txrx_status;
    /* Check  if the owner is the CPU */
    if (!(status & CVI_DESC_RXSTS_OWNBYDMA))
    {
        length = (status & CVI_DESC_RXSTS_FRMLENMSK) >> CVI_DESC_RXSTS_FRMLENSHFT;

        /* Invalidate received data */
        data_end = data_start + roundup(length, DW_GMAC_DMA_ALIGN);

        rt_hw_cpu_dcache_invalidate((void *)data_start, data_end - data_start);
        *packetp = (uint8_t *)data_start;
    }

    return length;
}

static int32_t designware_free_pkt(eth_mac_handle_t handle)
{
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_priv *priv = mac_dev->priv;
    uint32_t desc_num = priv->rx_currdescnum;
    struct dmamacdescr *desc_p = &priv->rx_mac_descrtable[desc_num];
    uint64_t desc_start = (uint64_t)desc_p;
    uint64_t desc_end = desc_start + roundup(sizeof(*desc_p), DW_GMAC_DMA_ALIGN);

    /*
     * Make the current descriptor valid again and go to
     * the next one
     */
    desc_p->txrx_status |= CVI_DESC_RXSTS_OWNBYDMA;

    /* Flush only status field - others weren't changed */
    rt_hw_cpu_dcache_clean((void *)desc_start, desc_end - desc_start);

    /* Test the wrap-around condition. */
    if (++desc_num >= CVI_CONFIG_RX_DESCR_NUM)
        desc_num = 0;
    priv->rx_currdescnum = desc_num;

    return 0;
}

/**
  \brief       Connect phy device to mac device.
  \param[in]   handle_mac  mac handle
  \param[in]   handle_phy  phy handle
*/
void dw_eth_mac_connect_phy(eth_mac_handle_t handle_mac, eth_phy_handle_t handle_phy)
{
    RT_ASSERT(handle_mac);
    RT_ASSERT(handle_phy);
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle_mac;
    eth_phy_dev_t *phy_dev = (eth_phy_dev_t *)handle_phy;

    mac_dev->phy_dev = phy_dev;
}

/**
  \brief       Read Ethernet PHY Register through Management Interface.
  \param[in]   handle  ethernet handle
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[out]  data      Pointer where the result is written to
  \return      error code
*/
int32_t dw_eth_mac_phy_read(eth_mac_handle_t handle, uint8_t phy_addr, uint8_t reg_addr, uint16_t *data)
{
    RT_ASSERT(handle);
    RT_ASSERT(data);
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_priv *priv = mac_dev->priv;
    struct dw_gmac_mac_regs *mac_reg = priv->mac_regs_p;
    uint16_t miiaddr;
    int32_t start;

    miiaddr = ((phy_addr << CVI_MIIADDRSHIFT) & CVI_MII_ADDRMSK) | ((reg_addr << CVI_MIIREGSHIFT) & CVI_MII_REGMSK);

    mac_reg->miiaddr = (miiaddr | CVI_MII_CLKRANGE_150_250M | CVI_MII_BUSY);

    start = rt_tick_get_millisecond();
    while ((rt_tick_get_millisecond() - start) < CVI_CONFIG_MDIO_TIMEOUT)
    {
        if (!(mac_reg->miiaddr & CVI_MII_BUSY))
        {
            *data = mac_reg->miidata;
            return 0;
        }
        rt_hw_us_delay(10);
    };

    return -1;
}

/**
  \brief       Write Ethernet PHY Register through Management Interface.
  \param[in]   handle  ethernet handle
  \param[in]   phy_addr  5-bit device address
  \param[in]   reg_addr  5-bit register address
  \param[in]   data      16-bit data to write
  \return      error code
*/
int32_t dw_eth_mac_phy_write(eth_mac_handle_t handle, uint8_t phy_addr, uint8_t reg_addr, uint16_t data)
{
    RT_ASSERT(handle);
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    struct dw_gmac_priv *priv = mac_dev->priv;
    struct dw_gmac_mac_regs *mac_reg = priv->mac_regs_p;
    uint16_t miiaddr;
    int32_t start;

    mac_reg->miidata = data;
    miiaddr = ((phy_addr << CVI_MIIADDRSHIFT) & CVI_MII_ADDRMSK) |
          ((reg_addr << CVI_MIIREGSHIFT) & CVI_MII_REGMSK) | CVI_MII_WRITE;

    mac_reg->miiaddr = (miiaddr | CVI_MII_CLKRANGE_150_250M | CVI_MII_BUSY);

    start = rt_tick_get_millisecond();
    while ((rt_tick_get_millisecond() - start) < CVI_CONFIG_MDIO_TIMEOUT) {
        if (!(mac_reg->miiaddr & CVI_MII_BUSY)) {
            return 0;
        }
        rt_hw_us_delay(10);
    };

    return -1;
}

/**
  \brief       Control Ethernet Interface.
  \param[in]   handle  ethernet handle
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \return      error code
*/
int32_t cvi_eth_mac_control(eth_mac_handle_t handle, uint32_t control, uint32_t arg)
{
    RT_ASSERT(handle);

    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    int32_t ret = 0;

    RT_ASSERT(mac_dev->phy_dev);

    switch (control) {
        case CSI_ETH_MAC_CONFIGURE:
            if (arg) {
                /* startup mac */
                ret = designware_eth_start(handle);
            } else {
                /* stop mac */
                designware_eth_stop(handle);
            }
            break;

        case DRV_ETH_MAC_ADJUST_LINK:
            ret = designware_adjust_link(handle);
            break;

        case CSI_ETH_MAC_CONTROL_TX:
            if (arg) {
                /* enable TX */
                ret = designware_eth_enable(handle, CSI_ETH_MAC_CONTROL_TX);
            } else {
                /* disable TX */
                ret = designware_eth_disable(handle, CSI_ETH_MAC_CONTROL_TX);
            }
            break;

        case CSI_ETH_MAC_CONTROL_RX:
            if (arg) {
                /* enable RX */
                ret = designware_eth_enable(handle, CSI_ETH_MAC_CONTROL_RX);
            } else {
                /* disable RX */
                ret = designware_eth_disable(handle, CSI_ETH_MAC_CONTROL_RX);
            }
            break;

        case DRV_ETH_MAC_CONTROL_IRQ:
            if (arg) {
                /* enable interrupt */
            } else {
                /* disable interrupt */
            }
            break;

        default:
            break;
    };

    return ret;
}

/**
  \brief       Get Ethernet MAC Address.
  \param[in]   handle  ethernet handle
  \param[in]   mac  Pointer to address
  \return      error code
*/
int32_t cvi_eth_mac_get_macaddr(eth_mac_handle_t handle, eth_mac_addr_t *mac)
{
    RT_ASSERT(handle);
    RT_ASSERT(mac);

    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;

    designware_read_hwaddr(handle);

    memcpy(mac->b, mac_dev->mac_addr, sizeof(mac_dev->mac_addr));

    return 0;
}

/**
  \brief       Set Ethernet MAC Address.
  \param[in]   handle  ethernet handle
  \param[in]   mac  Pointer to address
  \return      error code
*/
int32_t cvi_eth_mac_set_macaddr(eth_mac_handle_t handle, const eth_mac_addr_t *mac)
{
    RT_ASSERT(handle);
    RT_ASSERT(mac);

    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;
    memcpy(mac_dev->mac_addr, mac->b, sizeof(mac->b));

    designware_write_hwaddr(handle);

    return 0;
}

/**
  \brief       Send Ethernet frame.
  \param[in]   handle  ethernet handle
  \param[in]   frame  Pointer to frame buffer with data to send
  \param[in]   len    Frame buffer length in bytes
  \return      error code
*/
int32_t cvi_eth_mac_send_frame(eth_mac_handle_t handle, const uint8_t *frame, uint32_t len)
{
    RT_ASSERT(handle);
    RT_ASSERT(frame);

    return designware_eth_send(handle, frame, len);
}

/**
  \brief       Read data of received Ethernet frame.
  \param[in]   handle  ethernet handle
  \param[in]   frame  Pointer to frame buffer for data to read into
  \param[in]   len    Frame buffer length in bytes
  \return      number of data bytes read or execution status
                 - value >= 0: number of data bytes read
                 - value < 0: error occurred, value is execution status as defined with execution_status
*/
int32_t cvi_eth_mac_read_frame(eth_mac_handle_t handle, uint8_t *frame, uint32_t len)
{
    RT_ASSERT(handle);
    RT_ASSERT(frame);

    uint8_t *packet = NULL;
    int32_t actual_length;

    actual_length = designware_eth_recv(handle, &packet);

    if (actual_length < 0) {
        return -1;
    }

    /* process received packet */
    actual_length = (actual_length > len) ? len : actual_length;

    if (packet != NULL) {
        memcpy(frame, packet, actual_length);
    }

    designware_free_pkt(handle);

    return actual_length;
}


/**
  \brief       This function is used to initialize Ethernet device and register an event callback.
  \param[in]   idx device id
  \param[in]   cb  callback to handle ethernet event
  \return      return ethernet handle if success
 */
eth_mac_handle_t cvi_eth_mac_init(rt_ubase_t base)
{
    gmac_dev_t *mac_dev = &gmac_instance[0];
    struct dw_gmac_priv *priv, *priv_unalign;

    mac_dev->base = base;

    priv = memalign(DW_GMAC_DMA_ALIGN, sizeof(struct dw_gmac_priv), (void **)&priv_unalign);
    if (!priv)
    {
        rt_kprintf("malloc fail\n");
        return NULL;
    }

    memset(priv_unalign, 0, sizeof(struct dw_gmac_priv) + DW_GMAC_DMA_ALIGN);

    priv->mac_regs_p = (struct dw_gmac_mac_regs *)mac_dev->base;
    priv->dma_regs_p = (struct dw_gmac_dma_regs *)(mac_dev->base + CVI_DW_DMA_BASE_OFFSET);

    mac_dev->priv_unalign = priv_unalign;
    mac_dev->priv = priv;

    return (eth_mac_handle_t)mac_dev;
}

/**
  \brief       This function is used to de-initialize Ethernet device.
  \param[in]   handle  ethernet handle
  \return      error code
 */
void de_eth_gmac_deinit(eth_mac_handle_t handle)
{
    RT_ASSERT(handle);
    gmac_dev_t *mac_dev = (gmac_dev_t *)handle;

    if (mac_dev->priv_unalign)
    {
        rt_free(mac_dev->priv_unalign);
        mac_dev->priv_unalign = RT_NULL;
    }
}
