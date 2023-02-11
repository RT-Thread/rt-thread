/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-07-23      Wayne            First version
*
******************************************************************************/

#include "rtconfig.h"

#if defined(BSP_USING_EMAC)

#include <rtthread.h>
#include <rtdevice.h>
#include "lwipopts.h"
#include <netif/ethernetif.h>
#include <netif/etharp.h>
#include <lwip/sys.h>
#include <lwip/icmp.h>
#include <lwip/pbuf.h>
#include "NuMicro.h"

#include "synopGMAC_Host.h"

/* Private define ---------------------------------------------------------------*/

//#define NU_EMAC_DEBUG
#if defined(NU_EMAC_DEBUG)
    //#define NU_EMAC_RX_DUMP
    //#define NU_EMAC_TX_DUMP
    #define NU_EMAC_TRACE         rt_kprintf
#else
    #define NU_EMAC_TRACE(...)
#endif

enum
{
    EMAC_START = -1,
    EMAC0_IDX,
    EMAC_CNT
};

/* Private typedef --------------------------------------------------------------*/

struct nu_gmac_lwip_pbuf
{
    struct pbuf_custom p;  // lwip pbuf
    PKT_FRAME_T *psPktFrameDataBuf; // gmac descriptor
    synopGMACdevice *gmacdev;
    const struct memp_desc *pool;
};

typedef struct nu_gmac_lwip_pbuf *nu_gmac_lwip_pbuf_t;

struct nu_gmac
{
    struct eth_device   eth;
    char               *name;
    EMAC_T             *base;
    IRQn_Type           irqn;
    rt_timer_t          link_timer;
    rt_uint8_t          mac_addr[8];
    synopGMACNetworkAdapter *adapter;
    const struct memp_desc *memp_rx_pool;
};
typedef struct nu_gmac *nu_gmac_t;

/* Private variables ------------------------------------------------------------*/
LWIP_MEMPOOL_DECLARE(gmac0_rx, RECEIVE_DESC_SIZE, sizeof(struct nu_gmac_lwip_pbuf), "GMAC0 RX PBUF pool");

static struct nu_gmac nu_gmac_arr[] =
{
    {
        .name            =  "e0",
        .base            =  EMAC,
        .irqn         =  EMAC0_TXRX_IRQn,
        .memp_rx_pool    =  &memp_gmac0_rx
    },
};

void nu_gmac_pkt_dump(const char *msg, const struct pbuf *p)
{
    rt_uint32_t i;
    rt_uint8_t *ptr = p->payload;

    NU_EMAC_TRACE("%s %d byte\n", msg, p->tot_len);

    for (i = 0; i < p->tot_len; i++)
    {
        if ((i % 8) == 0)
        {
            NU_EMAC_TRACE("  ");
        }
        if ((i % 16) == 0)
        {
            NU_EMAC_TRACE("\r\n");
        }
        NU_EMAC_TRACE("%02x ", *ptr);
        ptr++;
    }
    NU_EMAC_TRACE("\n\n");
}

static int nu_gmac_mdio_read(void *adapter, int addr, int reg)
{
    synopGMACdevice *gmacdev = ((synopGMACNetworkAdapter *)adapter)->m_gmacdev;
    u16 data;
    synopGMAC_read_phy_reg(gmacdev->MacBase, addr, reg, &data);
    return data;
}

static void nu_gmac_mdio_write(void *adapter, int addr, int reg, int data)
{
    synopGMACdevice *gmacdev = ((synopGMACNetworkAdapter *)adapter)->m_gmacdev;
    synopGMAC_write_phy_reg(gmacdev->MacBase, addr, reg, data);
}

s32 synopGMAC_check_phy_init(synopGMACNetworkAdapter *adapter)
{
    struct ethtool_cmd cmd;
    synopGMACdevice *gmacdev = adapter->m_gmacdev;

    if (!mii_link_ok(&adapter->m_mii))
    {
        gmacdev->DuplexMode = FULLDUPLEX;
        gmacdev->Speed      =   SPEED100;
        return 0;
    }
    else
    {
        mii_ethtool_gset(&adapter->m_mii, &cmd);
        gmacdev->DuplexMode = (cmd.duplex == DUPLEX_FULL)  ? FULLDUPLEX : HALFDUPLEX ;
        if (cmd.speed == SPEED_1000)
            gmacdev->Speed = SPEED1000;
        else if (cmd.speed == SPEED_100)
            gmacdev->Speed = SPEED100;
        else
            gmacdev->Speed = SPEED10;
    }

    return gmacdev->Speed | (gmacdev->DuplexMode << 4);
}

static void nu_gmac_isr(int irqno, void *param)
{
    nu_gmac_t psNuGMAC = (nu_gmac_t)param;

    synopGMACNetworkAdapter *adapter = psNuGMAC->adapter;
    synopGMACdevice *gmacdev = (synopGMACdevice *)adapter->m_gmacdev;

    u32 interrupt, dma_status_reg;
    s32 status;
    u32 u32GmacIntSts;
    u32 u32GmacDmaIE = DmaIntEnable;

    // Check GMAC interrupt
    u32GmacIntSts = synopGMACReadReg(gmacdev->MacBase, GmacInterruptStatus);
    if (u32GmacIntSts & GmacTSIntSts)
    {
        gmacdev->synopGMACNetStats.ts_int = 1;
        status = synopGMACReadReg(gmacdev->MacBase, GmacTSStatus);
        if (!(status & (1 << 1)))
            NU_EMAC_TRACE("TS alarm flag not set??\n");
        else
            NU_EMAC_TRACE("TS alarm!!!!!!!!!!!!!!!!\n");

    }

    synopGMACWriteReg(gmacdev->MacBase, GmacInterruptStatus, u32GmacIntSts);

    dma_status_reg = synopGMACReadReg(gmacdev->DmaBase, DmaStatus);
    if (dma_status_reg == 0)
    {
        NU_EMAC_TRACE("dma_status ==0 \n");
        return;
    }

    if (dma_status_reg & GmacPmtIntr)
    {
        rt_kprintf("%s:: Interrupt due to PMT module\n", __FUNCTION__);
        synopGMAC_powerup_mac(gmacdev);
    }

    if (dma_status_reg & GmacLineIntfIntr)
    {
        rt_kprintf("%s:: Interrupt due to GMAC LINE module\n", __FUNCTION__);
    }

    interrupt = synopGMAC_get_interrupt_type(gmacdev);
    NU_EMAC_TRACE("%s:Interrupts to be handled: 0x%08x  %08x\n", __func__, interrupt, synopGMAC_get_ie(gmacdev));

    if (interrupt & synopGMACDmaError)
    {
        rt_kprintf("%s::Fatal Bus Error Inetrrupt Seen\n", __FUNCTION__);
        synopGMAC_disable_dma_tx(gmacdev);
        synopGMAC_disable_dma_rx(gmacdev);

        synopGMAC_take_desc_ownership_tx(gmacdev);
        synopGMAC_take_desc_ownership_rx(gmacdev);

        synopGMAC_init_tx_rx_desc_queue(gmacdev);

        synopGMAC_reset(gmacdev);

        synopGMAC_set_mac_addr(gmacdev, GmacAddr0High, GmacAddr0Low, &psNuGMAC->mac_addr[0]);
        synopGMAC_dma_bus_mode_init(gmacdev, DmaBurstLength32 | DmaDescriptorSkip0/*DmaDescriptorSkip2*/ | DmaDescriptor8Words);
        synopGMAC_dma_control_init(gmacdev, DmaStoreAndForward | DmaTxSecondFrame | DmaRxThreshCtrl128);
        synopGMAC_init_rx_desc_base(gmacdev);
        synopGMAC_init_tx_desc_base(gmacdev);
        synopGMAC_mac_init(gmacdev);
        synopGMAC_enable_dma_rx(gmacdev);
        synopGMAC_enable_dma_tx(gmacdev);

    }

    if ((interrupt & synopGMACDmaRxNormal) ||
            (interrupt & synopGMACDmaRxAbnormal))
    {
        if (interrupt & synopGMACDmaRxNormal)
        {
            NU_EMAC_TRACE("%s:: Rx Normal \n", __FUNCTION__);
            u32GmacDmaIE &= ~DmaIntRxNormMask;

        }
        if (interrupt & synopGMACDmaRxAbnormal)
        {
            rt_kprintf("%s::Abnormal Rx Interrupt Seen %08x\n", __FUNCTION__, dma_status_reg);

            if (gmacdev->GMAC_Power_down == 0)
            {
                gmacdev->synopGMACNetStats.rx_over_errors++;
                u32GmacDmaIE &= ~DmaIntRxAbnMask;
                //synopGMAC_resume_dma_rx(gmacdev);
            }
        }
        eth_device_ready(&psNuGMAC->eth);
    }

    if (interrupt & synopGMACDmaRxStopped)
    {
        rt_kprintf("%s::Receiver stopped seeing Rx interrupts\n", __FUNCTION__); //Receiver gone in to stopped state
        if (gmacdev->GMAC_Power_down == 0)   // If Mac is not in powerdown
        {
            gmacdev->synopGMACNetStats.rx_over_errors++;
            synopGMAC_enable_dma_rx(gmacdev);
        }
    }

    if (interrupt & synopGMACDmaTxNormal)
    {
        NU_EMAC_TRACE("%s::Finished Normal Transmission \n", __FUNCTION__);
        synop_handle_transmit_over(gmacdev);//Do whatever you want after the transmission is over
    }

    if (interrupt & synopGMACDmaTxAbnormal)
    {
        rt_kprintf("%s::Abnormal Tx Interrupt Seen\n", __FUNCTION__);
        if (gmacdev->GMAC_Power_down == 0)   // If Mac is not in powerdown
        {
            synop_handle_transmit_over(gmacdev);
        }
    }

    if (interrupt & synopGMACDmaTxStopped)
    {
        rt_kprintf("%s::Transmitter stopped sending the packets\n", __FUNCTION__);
        if (gmacdev->GMAC_Power_down == 0)    // If Mac is not in powerdown
        {
            synopGMAC_disable_dma_tx(gmacdev);
            synopGMAC_take_desc_ownership_tx(gmacdev);
            synopGMAC_enable_dma_tx(gmacdev);
            NU_EMAC_TRACE("%s::Transmission Resumed\n", __FUNCTION__);
        }
    }

    /* Enable the interrrupt before returning from ISR*/
    synopGMAC_enable_interrupt(gmacdev, u32GmacDmaIE);
}

void EMAC0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_gmac_isr(EMAC0_TXRX_IRQn, &nu_gmac_arr[EMAC0_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

void nu_gmac_link_monitor(void *pvData)
{
    s32 data;
    nu_gmac_t psNuGMAC = (nu_gmac_t)pvData;

    synopGMACNetworkAdapter *adapter = psNuGMAC->adapter;
    synopGMACdevice         *gmacdev = adapter->m_gmacdev;
    if (!mii_link_ok(&adapter->m_mii))
    {
        if (gmacdev->LinkState)
        {
            eth_device_linkchange(&psNuGMAC->eth, RT_FALSE);
            rt_kprintf("No Link\r\n");
        }
        gmacdev->DuplexMode = 0;
        gmacdev->Speed = 0;
        gmacdev->LoopBackMode = 0;
        gmacdev->LinkState = 0;
    }
    else
    {
        data = synopGMAC_check_phy_init(adapter);
        if (gmacdev->LinkState != data)
        {
            gmacdev->LinkState = data;
            synopGMAC_mac_init(gmacdev);
            rt_kprintf("Link is up in %s mode\n", (gmacdev->DuplexMode == FULLDUPLEX) ? "FULL DUPLEX" : "HALF DUPLEX");
            if (gmacdev->Speed == SPEED1000)
            {
                rt_kprintf("Link is with 1000M Speed \r\n");
                synopGMAC_set_mode(gmacdev, 0);
            }
            if (gmacdev->Speed == SPEED100)
            {
                rt_kprintf("Link is with 100M Speed \n");
                synopGMAC_set_mode(gmacdev, 1);
            }
            if (gmacdev->Speed == SPEED10)
            {
                rt_kprintf("Link is with 10M Speed \n");
                synopGMAC_set_mode(gmacdev, 2);
            }
            eth_device_linkchange(&psNuGMAC->eth, RT_TRUE);
        }
    }
}

static void nu_memmgr_init(GMAC_MEMMGR_T *psMemMgr)
{
    psMemMgr->u32TxDescSize = TRANSMIT_DESC_SIZE;
    psMemMgr->u32RxDescSize = RECEIVE_DESC_SIZE;

    psMemMgr->psTXDescs = (DmaDesc *) rt_malloc_align(sizeof(DmaDesc) * psMemMgr->u32TxDescSize, 4);
    RT_ASSERT(psMemMgr->psTXDescs != RT_NULL);
    NU_EMAC_TRACE("[%s] First TXDescAddr= %08x\n", __func__, psMemMgr->psTXDescs);

    psMemMgr->psRXDescs = (DmaDesc *) rt_malloc_align(sizeof(DmaDesc) * psMemMgr->u32RxDescSize, 4);
    RT_ASSERT(psMemMgr->psRXDescs != RT_NULL);
    NU_EMAC_TRACE("[%s] First RXDescAddr= %08x\n", __func__, psMemMgr->psRXDescs);

    psMemMgr->psTXFrames = (PKT_FRAME_T *) rt_malloc_align(sizeof(PKT_FRAME_T) * psMemMgr->u32TxDescSize, 4);
    RT_ASSERT(psMemMgr->psTXFrames != RT_NULL);
    NU_EMAC_TRACE("[%s] First TXFrameAddr= %08x\n", __func__, psMemMgr->psTXFrames);

    psMemMgr->psRXFrames = (PKT_FRAME_T *) rt_malloc_align(sizeof(PKT_FRAME_T) * psMemMgr->u32RxDescSize, 4);
    RT_ASSERT(psMemMgr->psRXFrames != RT_NULL);
    NU_EMAC_TRACE("[%s] First RXFrameAddr= %08x\n", __func__, psMemMgr->psRXFrames);
}

static void nu_mii_init(synopGMACNetworkAdapter *adapter)
{
    /* MII setup */
    adapter->m_mii.phy_id_mask   = 0x1F;
    adapter->m_mii.reg_num_mask  = 0x1F;
    adapter->m_mii.adapter       = (void *)adapter;
    adapter->m_mii.mdio_read     = nu_gmac_mdio_read;
    adapter->m_mii.mdio_write    = nu_gmac_mdio_write;
    adapter->m_mii.phy_id        = adapter->m_gmacdev->PhyBase;
    adapter->m_mii.supports_gmii = mii_check_gmii_support(&adapter->m_mii);
}

static rt_err_t nu_gmac_init(rt_device_t device)
{
    rt_err_t ret;
    s32 status = 0;
    int count;

    nu_gmac_t psNuGMAC = (nu_gmac_t)device;
    RT_ASSERT(psNuGMAC != RT_NULL);

    synopGMACNetworkAdapter *adapter = psNuGMAC->adapter;
    synopGMACdevice *gmacdev = (synopGMACdevice *)adapter->m_gmacdev;
    GMAC_MEMMGR_T *psgmacmemmgr = (GMAC_MEMMGR_T *)adapter->m_gmacmemmgr;

    RT_ASSERT(gmacdev != RT_NULL);
    RT_ASSERT(psgmacmemmgr != RT_NULL);

    NU_EMAC_TRACE("[%s] Init %s\n", __func__, psNuGMAC->name);

    synopGMAC_attach(gmacdev, ((uint32_t)psNuGMAC->base + MACBASE), ((uint32_t)psNuGMAC->base + DMABASE), DEFAULT_PHY_BASE, &psNuGMAC->mac_addr[0]);
    nu_mii_init(adapter);

    /* Reset to make RGMII/RMII setting take affect. */
    synopGMAC_reset(gmacdev);
    synopGMAC_read_version(gmacdev);

    /*Check for Phy initialization*/
    synopGMAC_set_mdc_clk_div(gmacdev, GmiiCsrClk2);
    gmacdev->ClockDivMdc = synopGMAC_get_mdc_clk_div(gmacdev);
    status = synopGMAC_check_phy_init(adapter);

    /*Set up the tx and rx descriptor queue/ring*/
    NU_EMAC_TRACE("tx desc_queue\n");
    synopGMAC_setup_tx_desc_queue(gmacdev, &psgmacmemmgr->psTXDescs[0], TRANSMIT_DESC_SIZE, RINGMODE);
    synopGMAC_init_tx_desc_base(gmacdev);
    NU_EMAC_TRACE("DmaTxBaseAddr = %08x\n", synopGMACReadReg(gmacdev->DmaBase, DmaTxBaseAddr));

    NU_EMAC_TRACE("rx desc_queue\n");
    synopGMAC_setup_rx_desc_queue(gmacdev, &psgmacmemmgr->psRXDescs[0], RECEIVE_DESC_SIZE, RINGMODE);
    synopGMAC_init_rx_desc_base(gmacdev);
    NU_EMAC_TRACE("DmaRxBaseAddr = %08x\n", synopGMACReadReg(gmacdev->DmaBase, DmaRxBaseAddr));

    /*Initialize the dma interface*/
    synopGMAC_dma_bus_mode_init(gmacdev, DmaBurstLength32 | DmaDescriptorSkip0/*DmaDescriptorSkip2*/ | DmaDescriptor8Words);
    synopGMAC_dma_control_init(gmacdev, DmaStoreAndForward | DmaTxSecondFrame | DmaRxThreshCtrl128);

    /*Initialize the mac interface*/
    synopGMAC_mac_init(gmacdev);
    //synopGMAC_promisc_enable(gmacdev);

    synopGMAC_pause_control(gmacdev); // This enables the pause control in Full duplex mode of operation

#if defined(RT_LWIP_USING_HW_CHECKSUM)
    /*IPC Checksum offloading is enabled for this driver. Should only be used if Full Ip checksumm offload engine is configured in the hardware*/
    synopGMAC_enable_rx_chksum_offload(gmacdev);    //Enable the offload engine in the receive path
    synopGMAC_rx_tcpip_chksum_drop_enable(gmacdev); // This is default configuration, DMA drops the packets if error in encapsulated ethernet payload
#endif

    /* Set all RX frame buffers. */
    count = 0;
    do
    {
        NU_EMAC_TRACE("[%s] Set %d pkt frame buffer address - 0x%08x, size=%d\n", __func__, count, (u32)(&psgmacmemmgr->psRXFrames[count]), PKT_FRAME_BUF_SIZE);
        status = synopGMAC_set_rx_qptr(gmacdev, (u32)(&psgmacmemmgr->psRXFrames[count]), PKT_FRAME_BUF_SIZE, 0);
        if (status < 0)
        {
            NU_EMAC_TRACE("status < 0!!\n");
            break;
        }
        count++;
    }
    while (count < RECEIVE_DESC_SIZE);

    synopGMAC_clear_interrupt(gmacdev);

    synopGMAC_disable_interrupt_all(gmacdev);
    synopGMAC_enable_interrupt(gmacdev, DmaIntEnable);
    NU_EMAC_TRACE("%s: get_ie: %08x\n", __func__, synopGMAC_get_ie(gmacdev));

    synopGMAC_enable_dma_rx(gmacdev);
    synopGMAC_enable_dma_tx(gmacdev);

    synopGMAC_set_mac_addr(gmacdev, GmacAddr0High, GmacAddr0Low, &psNuGMAC->mac_addr[0]);

    synopGMAC_set_mode(gmacdev, 0);

    NU_EMAC_TRACE("[%s] Create %s link monitor timer. \n", __func__, psNuGMAC->name);
    /* Create timer to monitor link status. */
    psNuGMAC->link_timer = rt_timer_create("link_timer",
                                           nu_gmac_link_monitor,
                                           (void *)psNuGMAC,
                                           RT_TICK_PER_SECOND,
                                           RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(psNuGMAC->link_timer != RT_NULL);

    ret = rt_timer_start(psNuGMAC->link_timer);
    RT_ASSERT(ret == RT_EOK);

    /* Enable NVIC interrupt. */
    NVIC_EnableIRQ(psNuGMAC->irqn);

    NU_EMAC_TRACE("[%s] Init %s done\n", __func__, psNuGMAC->name);

    return RT_EOK;
}

static rt_err_t nu_gmac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t nu_gmac_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t nu_gmac_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t nu_gmac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t nu_gmac_control(rt_device_t device, int cmd, void *args)
{
    nu_gmac_t psNuGMAC = (nu_gmac_t)device;
    RT_ASSERT(device != RT_NULL);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args) rt_memcpy(args, &psNuGMAC->mac_addr[0], 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

rt_err_t nu_gmac_tx(rt_device_t device, struct pbuf *p)
{
    rt_err_t ret = -RT_ERROR;
    s32 status;

    nu_gmac_t psNuGMAC = (nu_gmac_t)device;
    synopGMACNetworkAdapter *adapter;
    synopGMACdevice *gmacdev;
    GMAC_MEMMGR_T *psgmacmemmgr;

    RT_ASSERT(device);

    adapter = (synopGMACNetworkAdapter *) psNuGMAC->adapter;
    RT_ASSERT(adapter);

    gmacdev = (synopGMACdevice *) adapter->m_gmacdev;
    RT_ASSERT(gmacdev);

    psgmacmemmgr = (GMAC_MEMMGR_T *)adapter->m_gmacmemmgr;
    RT_ASSERT(psgmacmemmgr);

    if (!synopGMAC_is_desc_owned_by_dma(gmacdev->TxNextDesc))
    {
        u32 offload_needed;
#if defined(RT_LWIP_USING_HW_CHECKSUM)
        offload_needed = 1;
#else
        offload_needed = 0;
#endif
        u32 index = gmacdev->TxNext;
        u8 *pu8PktData = (u8 *)((u32)&psgmacmemmgr->psTXFrames[index]);
        struct pbuf *q;
        rt_uint32_t offset = 0;

        NU_EMAC_TRACE("%s : Transmitting data(%08x-%d).\n", __func__, (u32)&psgmacmemmgr->psTXFrames[index], p->tot_len);

        /* Copy to TX data buffer. */
        for (q = p; q != NULL; q = q->next)
        {
            rt_uint8_t *ptr = q->payload;
            rt_uint32_t len = q->len;
            rt_memcpy(&pu8PktData[offset], ptr, len);
            offset += len;
        }

        status = synopGMAC_xmit_frames(gmacdev, (u8 *)&psgmacmemmgr->psTXFrames[index], offset, offload_needed, 0);
        if (status != 0)
        {
            NU_EMAC_TRACE("%s No More Free Tx skb\n", __func__);
            ret = -RT_ERROR;
            goto exit_nu_gmac_tx;
        }
    }
    else
    {
        NU_EMAC_TRACE("No avaialbe TX descriptor.\n");
        ret = -RT_ERROR;
        goto exit_nu_gmac_tx;
    }

    ret = RT_EOK;

exit_nu_gmac_tx:

    return ret;
}

void nu_gmac_pbuf_free(struct pbuf *p)
{
    nu_gmac_lwip_pbuf_t my_buf = (nu_gmac_lwip_pbuf_t)p;
    s32 status;

    SYS_ARCH_DECL_PROTECT(old_level);
    SYS_ARCH_PROTECT(old_level);
    status = synopGMAC_set_rx_qptr(my_buf->gmacdev, (u32)my_buf->psPktFrameDataBuf, PKT_FRAME_BUF_SIZE, 0);
    if (status < 0)
    {
        NU_EMAC_TRACE("synopGMAC_set_rx_qptr: status < 0!!\n");
    }
    memp_free_pool(my_buf->pool, my_buf);
    SYS_ARCH_UNPROTECT(old_level);
}

struct pbuf *nu_gmac_rx(rt_device_t device)
{
    nu_gmac_t psNuGMAC = (nu_gmac_t)device;
    synopGMACNetworkAdapter *adapter;
    synopGMACdevice *gmacdev;
    struct pbuf *pbuf = RT_NULL;
    PKT_FRAME_T *psPktFrame;
    s32  s32PktLen;

    RT_ASSERT(device);

    adapter = psNuGMAC->adapter;
    RT_ASSERT(adapter);

    gmacdev = (synopGMACdevice *) adapter->m_gmacdev;
    RT_ASSERT(gmacdev);

    if ((s32PktLen = synop_handle_received_data(gmacdev, &psPktFrame)) > 0)
    {
        nu_gmac_lwip_pbuf_t my_pbuf  = (nu_gmac_lwip_pbuf_t)memp_malloc_pool(psNuGMAC->memp_rx_pool);
        if (my_pbuf != RT_NULL)
        {
            my_pbuf->p.custom_free_function = nu_gmac_pbuf_free;
            my_pbuf->psPktFrameDataBuf      = psPktFrame;
            my_pbuf->gmacdev                = gmacdev;
            my_pbuf->pool                   = psNuGMAC->memp_rx_pool;

            pbuf = pbuf_alloced_custom(PBUF_RAW,
                                       s32PktLen,
                                       PBUF_REF,
                                       &my_pbuf->p,
                                       psPktFrame,
                                       PKT_FRAME_BUF_SIZE);
            if (pbuf == RT_NULL)
                rt_kprintf("%s : failed to alloted %08x\n", __func__, pbuf);

        }
        else
        {
            rt_kprintf("LWIP_MEMPOOL_ALLOC < 0!!\n");
        }
    }
    else
    {
        //rt_kprintf("%s : fail to receive data.\n", __func__);
        synopGMAC_enable_interrupt(gmacdev, DmaIntEnable);
        goto exit_nu_gmac_rx;
    }

exit_nu_gmac_rx:

    return pbuf;
}

static void nu_gmac_assign_macaddr(nu_gmac_t psNuGMAC)
{
    static rt_uint32_t value = 0x94539452;

    /* Assign MAC address */
    psNuGMAC->mac_addr[0] = 0x82;
    psNuGMAC->mac_addr[1] = 0x06;
    psNuGMAC->mac_addr[2] = 0x21;
    psNuGMAC->mac_addr[3] = (value >> 16) & 0xff;
    psNuGMAC->mac_addr[4] = (value >> 8) & 0xff;
    psNuGMAC->mac_addr[5] = (value) & 0xff;

    NU_EMAC_TRACE("MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n", \
                  psNuGMAC->mac_addr[0], \
                  psNuGMAC->mac_addr[1], \
                  psNuGMAC->mac_addr[2], \
                  psNuGMAC->mac_addr[3], \
                  psNuGMAC->mac_addr[4], \
                  psNuGMAC->mac_addr[5]);
    value++;
}

int32_t nu_gmac_adapter_init(nu_gmac_t psNuGMAC)
{
    synopGMACNetworkAdapter *adapter;

    RT_ASSERT(psNuGMAC != RT_NULL);


    /* Allocate net adapter */
    adapter = (synopGMACNetworkAdapter *)rt_malloc_align(sizeof(synopGMACNetworkAdapter), 4);
    RT_ASSERT(adapter != RT_NULL);
    rt_memset((void *)adapter, 0, sizeof(synopGMACNetworkAdapter));

    /* Allocate device */
    adapter->m_gmacdev = (synopGMACdevice *) rt_malloc_align(sizeof(synopGMACdevice), 4);
    RT_ASSERT(adapter->m_gmacdev != RT_NULL);
    rt_memset((char *)adapter->m_gmacdev, 0, sizeof(synopGMACdevice));

    /* Allocate memory management */
    adapter->m_gmacmemmgr = (GMAC_MEMMGR_T *) rt_malloc_align(sizeof(GMAC_MEMMGR_T), 4);
    RT_ASSERT(adapter->m_gmacmemmgr != RT_NULL);
    nu_memmgr_init(adapter->m_gmacmemmgr);

    /* Store adapter to priv */
    psNuGMAC->adapter = adapter;

    return 0;
}

int rt_hw_gmac_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (EMAC_START + 1); i < EMAC_CNT; i++)
    {
        nu_gmac_t psNuGMAC = (nu_gmac_t)&nu_gmac_arr[i];

        /* Register member functions */
        psNuGMAC->eth.parent.type       = RT_Device_Class_NetIf;
        psNuGMAC->eth.parent.init       = nu_gmac_init;
        psNuGMAC->eth.parent.open       = nu_gmac_open;
        psNuGMAC->eth.parent.close      = nu_gmac_close;
        psNuGMAC->eth.parent.read       = nu_gmac_read;
        psNuGMAC->eth.parent.write      = nu_gmac_write;
        psNuGMAC->eth.parent.control    = nu_gmac_control;
        psNuGMAC->eth.parent.user_data  = psNuGMAC;
        psNuGMAC->eth.eth_rx            = nu_gmac_rx;
        psNuGMAC->eth.eth_tx            = nu_gmac_tx;

        /* Set MAC address */
        nu_gmac_assign_macaddr(psNuGMAC);

        /* Initial GMAC adapter */
        nu_gmac_adapter_init(psNuGMAC);

        /* Initial zero_copy rx pool */
        memp_init_pool(psNuGMAC->memp_rx_pool);

        /* Register eth device */
        ret = eth_device_init(&psNuGMAC->eth, psNuGMAC->name);
        RT_ASSERT(ret == RT_EOK);
    }


    return 0;
}
INIT_APP_EXPORT(rt_hw_gmac_init);

#if 0
/*
    Remeber src += lwipiperf_SRCS in components\net\lwip-*\SConscript
*/
#include "lwip/apps/lwiperf.h"

static void
lwiperf_report(void *arg, enum lwiperf_report_type report_type,
               const ip_addr_t *local_addr, u16_t local_port, const ip_addr_t *remote_addr, u16_t remote_port,
               u32_t bytes_transferred, u32_t ms_duration, u32_t bandwidth_kbitpsec)
{
    LWIP_UNUSED_ARG(arg);
    LWIP_UNUSED_ARG(local_addr);
    LWIP_UNUSED_ARG(local_port);

    rt_kprintf("IPERF report: type=%d, remote: %s:%d, total bytes: %"U32_F", duration in ms: %"U32_F", kbits/s: %"U32_F"\n",
               (int)report_type, ipaddr_ntoa(remote_addr), (int)remote_port, bytes_transferred, ms_duration, bandwidth_kbitpsec);
}

void lwiperf_example_init(void)
{
    lwiperf_start_tcp_server_default(lwiperf_report, NULL);
}
MSH_CMD_EXPORT(lwiperf_example_init, start lwip tcp server);
#endif

#endif /* if defined(BSP_USING_GMAC) */
