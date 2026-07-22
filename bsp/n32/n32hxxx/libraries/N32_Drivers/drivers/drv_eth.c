/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-06-24     ox-horse         first version
 */

#include "drv_config.h"
#include "drv_eth.h"
#include <netif/ethernetif.h>
#include <lwipopts.h>

/* debug option */
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP
//#define DRV_DEBUG
#define LOG_TAG "drv.eth"
#include <drv_log.h>

#define MAX_ADDR_LEN 6

/* ======================= Device Structure ======================= */

struct rt_n32_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;
#ifndef PHY_USING_INTERRUPT_MODE
    rt_timer_t poll_link_timer;
#endif

    /* interface address info, hw address */
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
    /* ETH_Speed */
    rt_uint32_t ETH_Speed;
    /* ETH_Duplex_Mode */
    rt_uint32_t ETH_Mode;
    /* PHY address */
    rt_uint8_t phy_addr;
};

static ETH_DMADescType    *DMARxDscrTab, *DMATxDscrTab;
static rt_uint8_t         *Rx_Buff, *Tx_Buff;
static ETH_InfoType        sEthInfo;
static ETH_InitType        sETH_InitParam;
static struct rt_n32_eth   n32_eth_device;
static struct rt_semaphore tx_sem;
static volatile rt_bool_t  tx_is_waiting = RT_FALSE;

/* ======================= Debug Helper ======================= */

#if defined(ETH_RX_DUMP) || defined(ETH_TX_DUMP)
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char *)ptr;
    int            i, j;

    for (i = 0; i < buflen; i += 16)
    {
        rt_kprintf("%08X: ", i);

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%02X ", buf[i + j]);
            else
                rt_kprintf("   ");
        rt_kprintf(" ");

        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                rt_kprintf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
        rt_kprintf("\n");
    }
}
#endif

/* ======================= External PHY Reset ======================= */

extern void phy_reset(void);

/* ======================= ETH Initialization ======================= */

static rt_err_t rt_n32_eth_init(rt_device_t dev)
{
    struct rt_n32_eth *eth = (struct rt_n32_eth *)dev;
    EthFuncStatusType  status;

    /* Enable or disable PWR Clock */
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_PWR, ENABLE);
    /* Enable or disable the power domain of the ETH */
    PWR_MoudlePowerEnable(ETH_PWR_CTRL, ENABLE);
    /* Enable or disable ETH Clock */
    ETH_RCC_ENABLE_AHB_PERIPHEN_CLK(ETH_RCC_AHB_PERIPHEN, ENABLE);

    phy_reset();

    /* Clear the sEthInfo structure variable */
    memset(&sEthInfo, 0, sizeof(ETH_InfoType));

    /* Set ETH operation-related information via sEthInfo */
    sEthInfo.MDCClockMode   = ETH_MDCCLK_NORMAL;
    sEthInfo.MediaInterface = ETH_MEDIA_INTERFACE;
    sEthInfo.pMACAddr       = (rt_uint8_t *)&eth->dev_addr[0];
    sEthInfo.pRxDesc        = DMARxDscrTab;
    sEthInfo.pTxDesc        = DMATxDscrTab;
    sEthInfo.RxBuffLen      = ETH_MAX_PACKET_SIZE;

    /* PHY register information */
    sEthInfo.PHYInfo.bcRegAddr    = PHY_BASIC_CONTROL_REG;
    sEthInfo.PHYInfo.bsRegAddr    = PHY_BASIC_STATUS_REG;
    sEthInfo.PHYInfo.phyReset     = PHY_RESET_MASK;
    sEthInfo.PHYInfo.phyAutoNeg   = PHY_AUTO_NEGOTIATION_MASK;
    sEthInfo.PHYInfo.phyAutoNegOK = PHY_AUTONEGO_COMPLETE_MASK;
    sEthInfo.PHYInfo.phyLinkOK    = PHY_LINKED_STATUS_MASK;
    sEthInfo.PHYInfo.phyAddr      = eth->phy_addr;

    /* DeInitializes the ETH peripheral */
    ETH_DeInit(ETH);

    /* Set ETH initialization parameters by default */
    ETH_StructInit(ETH, &sETH_InitParam);

    /* Modify ETH initialization parameters (only override StructInit defaults) */
    /* MAC Configuration */
    sETH_InitParam.AutoPadCRCStrip      = ((uint32_t)ENABLE << 20);
    sETH_InitParam.CRCStripTypePacket   = ((uint32_t)ENABLE << 21);
    sETH_InitParam.ProgramWatchdog      = ((uint32_t)ENABLE << 8);
    sETH_InitParam.GiantPacketSizeLimit = (0x618U);

    /* Duplex and Speed (updated after PHY auto-negotiation) */
    sETH_InitParam.Duplex      = (EthDuplexType)eth->ETH_Mode;
    sETH_InitParam.SpeedSelect = (EthSpeedType)eth->ETH_Speed;

    /* MTL Configuration */
    sETH_InitParam.TxQueueOperateMode = ETH_TXQUEUE_OPERATE_THRESHOLD_64;
    sETH_InitParam.RxQueueOperateMode = ETH_RXQUEUE_OPERATE_THRESHOLD_64;

    /* Checksum offload */
#ifdef RT_LWIP_USING_HW_CHECKSUM
    sETH_InitParam.ChecksumOffload = ((uint32_t)ENABLE << 27);
#endif

    /* DMA System Bus Mode Configuration */
    sETH_InitParam.BurstMode        = ETH_BURST_MODE_FIXED;
    sETH_InitParam.AddrAlignedBeats = ((uint32_t)ENABLE << 12);

    /* DMA Channel Configuration */
    sETH_InitParam.DescriptorSkipLen = ETH_DESC_SKIP_LEN_64BIT;

    /* DMA Channel Transmit Configuration */
    sETH_InitParam.TxBurstLength = ETH_TX_PROGRAM_BURST_LEN_32;

    /* DMA Channel Receive Configuration */
    sETH_InitParam.RxBurstLength = ETH_RX_PROGRAM_BURST_LEN_32;

    /* 125M clock source must be configured when GMII (only ETH1 supports GMII) */
#if defined(BSP_USING_ETH1)
    if (sEthInfo.MediaInterface == ETH_GMII_MODE)
    {
        /* The clock comes from GPIO (provided by external PHY) */
        RCC_ConfigETH1GMIITXClk(RCC_ETH1GMIITXCLK_SRC_IOM);
    }
#endif

    /* Configure ethernet peripheral (MAC, DMA) */
    status = ETH_Init(ETH, &sEthInfo, &sETH_InitParam);
    if (status != ETH_SUCCESS)
    {
        LOG_E("eth hardware init failed, status=%d", status);
        return -RT_ERROR;
    }
    else
    {
        LOG_D("eth hardware init success");
    }

    /* Assign transmit buffer address for each TX descriptor.
     * DESC0 is the buffer address register read by DMA during transmission.
     * Buf1Addr is the CPU-side backup for use in SMEMCPY during tx. */
    for (rt_size_t i = 0; i < ETH_TX_DESC_NUMBER; i++)
    {
        sEthInfo.pTxDesc[i].DESC0    = (uint32_t)&Tx_Buff[i * ETH_MAX_PACKET_SIZE];
        sEthInfo.pTxDesc[i].Buf1Addr = (uint32_t)&Tx_Buff[i * ETH_MAX_PACKET_SIZE];
    }

    /* Assign memory for each RX descriptor.
     * Equivalent to ETH_RxDescAssignMemory(&sEthInfo, i, buf, NULL):
     *   - Write buffer address to DESC0 (DMA writes received data here)
     *   - Backup to Buf1Addr (CPU-side reference)
     *   - Set BUF1V in DESC3 (tell DMA buffer1 is valid)
     *   - Set OWN in DESC3 (give descriptor to DMA for reception)
     * Unlike TX, OWN is set immediately so DMA can start filling RX buffers. */
    for (rt_size_t i = 0; i < ETH_RX_DESC_NUMBER; i++)
    {
        // ETH_RxDescAssignMemory(&sEthInfo, i, (uint8_t *)&Rx_Buff[i * ETH_MAX_PACKET_SIZE], NULL);
        sEthInfo.pRxDesc[i].DESC0     = (uint32_t)&Rx_Buff[i * ETH_MAX_PACKET_SIZE];
        sEthInfo.pRxDesc[i].Buf1Addr  = (uint32_t)&Rx_Buff[i * ETH_MAX_PACKET_SIZE];
        sEthInfo.pRxDesc[i].DESC3    |= ETH_DMARXND3RF_BUF1V | ETH_DMARXND3RF_OWN;
    }

    /* ETH interrupt Init */
    NVIC_SetPriority(ETH_GLOBAL_IRQ, 0x05);
    NVIC_EnableIRQ(ETH_GLOBAL_IRQ);

    /* Enable MAC and DMA transmission and reception (interrupt mode) */
    ETH_StartIT(ETH, &sEthInfo);

    return RT_EOK;
}

/* ======================= RT-Thread Device Ops ======================= */

static rt_err_t rt_n32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("emac open");
    return RT_EOK;
}

static rt_err_t rt_n32_eth_close(rt_device_t dev)
{
    LOG_D("emac close");
    return RT_EOK;
}

static rt_ssize_t rt_n32_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("emac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_n32_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("emac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_n32_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args)
        {
            SMEMCPY(args, n32_eth_device.dev_addr, 6);
        }
        else
        {
            return -RT_ERROR;
        }
        break;

    default:
        break;
    }

    return RT_EOK;
}

/* ======================= Ethernet Transmit ======================= */

rt_err_t rt_n32_eth_tx(rt_device_t dev, struct pbuf *p)
{
    struct pbuf     *q;
    rt_uint32_t      framelen  = 0;
    rt_uint32_t      offset    = 0;
    rt_uint32_t      remaining = 0;
    rt_uint32_t      copysize  = 0;
    uint8_t         *src;
    uint8_t         *buffer;
    rt_uint32_t      node_idx = 0;
    rt_uint32_t      desc_idx;
    ETH_BufferType   TxBufNodes[ETH_TX_DESC_NUMBER];
    ETH_TxPacketType TxPacket;

    /* Wait for descriptor to become available (interrupt-driven, no busy-poll) */
    if ((sEthInfo.pTxDesc->DESC3 & ETH_DMATXND3RF_OWN) != (uint32_t)RESET)
    {
        rt_err_t sem_ret;

        tx_is_waiting = RT_TRUE;
        sem_ret       = rt_sem_take(&tx_sem, RT_TICK_PER_SECOND);
        tx_is_waiting = RT_FALSE;

        if (sem_ret != RT_EOK)
        {
            LOG_E("tx sem timeout");
            return ERR_USE;
        }

        /* Re-check after wake-up */
        if ((sEthInfo.pTxDesc->DESC3 & ETH_DMATXND3RF_OWN) != (uint32_t)RESET)
        {
            LOG_E("tx desc still busy after wake");
            return ERR_IF;
        }
    }

    /* First buffer from current descriptor */
    buffer              = (uint8_t *)(sEthInfo.pTxDesc->Buf1Addr);
    TxBufNodes[0].pBuf  = buffer;
    TxBufNodes[0].Len   = 0;
    TxBufNodes[0].pNext = NULL;

    /* Copy pbuf chain into TX buffer pool, splitting at ETH_MAX_PACKET_SIZE boundaries */
    for (q = p; q != NULL; q = q->next)
    {
        remaining = q->len;
        src       = (uint8_t *)q->payload;

        while (remaining > 0)
        {
            if (offset >= ETH_MAX_PACKET_SIZE)
            {
                /* Current buffer full: finalize this node, move to next buffer */
                TxBufNodes[node_idx].Len = ETH_MAX_PACKET_SIZE;

                node_idx++;
                if (node_idx >= ETH_TX_DESC_NUMBER)
                {
                    LOG_E("tx frame exceeds available descriptors");
                    return ERR_USE;
                }

                /* Link previous node to this one */
                TxBufNodes[node_idx - 1].pNext = &TxBufNodes[node_idx];

                /* Get next buffer from contiguous pool (wrap around descriptor ring) */
                desc_idx = (sEthInfo.TxDescList.CurTxDesc + node_idx) % ETH_TX_DESC_NUMBER;
                buffer   = &Tx_Buff[desc_idx * ETH_MAX_PACKET_SIZE];

                /* Check this descriptor is available */
                if ((sEthInfo.pTxDesc[desc_idx].DESC3 & ETH_DMATXND3RF_OWN) != (uint32_t)RESET)
                {
                    LOG_E("tx next desc not available");
                    return ERR_USE;
                }

                TxBufNodes[node_idx].pBuf  = buffer;
                TxBufNodes[node_idx].Len   = 0;
                TxBufNodes[node_idx].pNext = NULL;
                offset                     = 0;
            }

            copysize = remaining;
            if (copysize > (ETH_MAX_PACKET_SIZE - offset))
            {
                copysize = ETH_MAX_PACKET_SIZE - offset;
            }

            SMEMCPY(buffer + offset, src, copysize);
            src       += copysize;
            offset    += copysize;
            framelen  += copysize;
            remaining -= copysize;
        }
    }

    /* Set length of last used node */
    TxBufNodes[node_idx].Len = offset;

#ifdef ETH_TX_DUMP
    dump_hex((uint8_t *)(TxBufNodes[0].pBuf), framelen);
#endif

    LOG_D("transmit frame length :%d, segments:%d", framelen, node_idx + 1);

    /* Build TX packet: linked list of buffer segments */
    memset(&TxPacket, 0, sizeof(ETH_TxPacketType));
    TxPacket.pTxBuffer  = &TxBufNodes[0];
    TxPacket.Length     = framelen;
    TxPacket.Attributes = ETH_TX_PACKETS_FEATURES_CRCPAD;
    TxPacket.CRCPadCtrl = ETH_CRC_PAD_INSERT;
#ifdef RT_LWIP_USING_HW_CHECKSUM
    TxPacket.Attributes   |= ETH_TX_PACKETS_FEATURES_CSUM;
    TxPacket.ChecksumCtrl  = ETH_CHECKSUM_INSERT_IPHDR_PAYLOAD_PHDR_CALC;
#endif

    /* Transmit via SDK: handles descriptor setup, multi-descriptor FD/LD,
     * OWN bits, CurTxDesc advancement, and DMA kick. */
    if (ETH_TransmitIT(ETH, &sEthInfo, &TxPacket) != ETH_SUCCESS)
    {
        LOG_E("eth transmit failed");
        if (ETH_GetDMACh0FlagStatus(ETH, ETH_DMACH0_INT_FLAG_TBU) != RESET)
        {
            ETH_ClearDMACh0Flag(ETH, ETH_DMACH0_INT_FLAG_TBU);
            ETH_ResumeDMATransmission(ETH);
        }
        /* Sync pTxDesc even on failure — SDK may have updated CurTxDesc inside */
        sEthInfo.pTxDesc = (ETH_DMADescType *)(sEthInfo.TxDescList.TxDesc[sEthInfo.TxDescList.CurTxDesc]);
        return ERR_IF;
    }

    /* Sync pTxDesc with CurTxDesc (updated by ETH_TransmitIT) */
    sEthInfo.pTxDesc = (ETH_DMADescType *)(sEthInfo.TxDescList.TxDesc[sEthInfo.TxDescList.CurTxDesc]);

    return ERR_OK;
}

/* ======================= Ethernet Receive ======================= */

struct pbuf *rt_n32_eth_rx(rt_device_t dev)
{
    struct pbuf    *p = NULL;
    struct pbuf    *q;
    rt_uint16_t     len;
    rt_uint32_t     src_offset;
    rt_uint32_t     dst_offset;
    rt_uint32_t     remaining;
    rt_uint32_t     copysize;
    ETH_BufferType *src_node;
    ETH_BufferType  RxBufNodes[ETH_RX_DESC_NUMBER];

    /* Check if a complete frame has been received.
     * SDK internally scans descriptors, validates FD/LD, updates
     * AppDescNbr / FirstAppDesc / CurRxDesc. */
    if (!ETH_IsRxDataAvailable(&sEthInfo))
    {
        return NULL;
    }

    /* Get frame length (CRC already stripped by MAC with ACS=ENABLE) */
    len = ETH_GetRxDataLength(&sEthInfo);
    if (len == 0U)
    {
        ETH_BuildRxDescriptors(ETH, &sEthInfo);
        return NULL;
    }

    LOG_D("receive frame len : %d", len);

    /* Build buffer chain from received descriptors via SDK */
    memset(RxBufNodes, 0, sizeof(RxBufNodes));
    if (ETH_GetRxDataBuffer(&sEthInfo, RxBufNodes) != ETH_SUCCESS)
    {
        ETH_BuildRxDescriptors(ETH, &sEthInfo);
        return NULL;
    }

    /* Allocate pbuf chain */
    p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    if (p == NULL)
    {
        ETH_BuildRxDescriptors(ETH, &sEthInfo);
        return NULL;
    }

#ifdef ETH_RX_DUMP
    dump_hex((uint8_t *)(RxBufNodes[0].pBuf), len);
#endif

    /* Copy from Rx buffer chain to pbuf chain.
     *
     * Two linked lists with independent segment boundaries:
     *   RxBufNodes: SDK-built chain, each node = one descriptor's buffer
     *   pbuf:       lwIP-allocated chain, segment sizes depend on pool config
     *
     * Walk both chains simultaneously, copying data across segment boundaries.
     * Tracking variables:
     *   src_node  — current source node in RxBufNodes chain
     *   src_offset — bytes already consumed from current src_node
     *   remaining — bytes still needed to fill current pbuf segment
     *   dst_offset — bytes already written into current pbuf segment */
    src_node   = RxBufNodes;
    src_offset = 0;

    for (q = p; q != NULL; q = q->next)
    {
        remaining  = q->len;
        dst_offset = 0;

        while (remaining > 0 && src_node != NULL)
        {
            /* Switch to next source node when current one is exhausted */
            if (src_offset >= src_node->Len)
            {
                src_node   = src_node->pNext;
                src_offset = 0;
                continue;
            }

            /* Copy as much as possible: bounded by both
             * target remaining and source available */
            copysize = remaining;
            if (copysize > (src_node->Len - src_offset))
            {
                copysize = src_node->Len - src_offset;
            }

            SMEMCPY((uint8_t *)q->payload + dst_offset,
                    (uint8_t *)src_node->pBuf + src_offset,
                    copysize);
            src_offset += copysize;
            dst_offset += copysize;
            remaining  -= copysize;
        }
    }

    /* Return descriptors to DMA for next reception */
    ETH_BuildRxDescriptors(ETH, &sEthInfo);

    /* When Rx Buffer Unavailable flag is set, clear it and resume reception */
    if (ETH_GetDMACh0FlagStatus(ETH, ETH_DMACH0_INT_FLAG_RBU) != RESET)
    {
        ETH_ClearDMACh0Flag(ETH, ETH_DMACH0_INT_FLAG_RBU);
        ETH_ResumeDMAReception(ETH);
    }

    /* Sync pRxDesc with CurRxDesc (updated by SDK inside ETH_IsRxDataAvailable) */
    sEthInfo.pRxDesc = (ETH_DMADescType *)(sEthInfo.RxDescList.RxDesc[sEthInfo.RxDescList.CurRxDesc]);

    return p;
}

/* ======================= ETH Interrupt Handler ======================= */

void ETH_GLOBAL_IRQHANDLER(void)
{
    rt_err_t result;

    /* enter interrupt */
    rt_interrupt_enter();

    /* Check for Receive Interrupt */
    if (ETH_GetDMACh0InterruptStatus(ETH, ETH_DMACH0_INT_FLAG_RI) != RESET)
    {
        /* Clear interrupt flag first, so new frames arriving during
         * eth_device_ready() or later RX processing are not lost. */
        ETH_ClearDMACh0InterruptFlag(ETH, (ETH_DMACH0_INT_FLAG_RI | ETH_DMACH0_INT_FLAG_NIS));

        /* Notify lwIP that a frame has been received */
        result = eth_device_ready(&(n32_eth_device.parent));
        if (result != RT_EOK)
        {
            LOG_I("RxCpltCallback err = %d", result);
        }
    }

    /* Check for abnormal interrupts */
    if (ETH_GetDMACh0InterruptStatus(ETH, ETH_DMACH0_INT_FLAG_AIS) != RESET)
    {
        LOG_E("eth abnormal interrupt: DMASTS=0x%08X", ETH->DMACH0STS);

        /* Clear all abnormal interrupt flags */
        if (ETH_GetDMACh0InterruptStatus(ETH, ETH_DMACH0_INT_FLAG_FBE) != RESET)
        {
            LOG_E("Fatal Bus Error");
            ETH_ClearDMACh0InterruptFlag(ETH, ETH_DMACH0_INT_FLAG_FBE);
        }
        if (ETH_GetDMACh0InterruptStatus(ETH, ETH_DMACH0_INT_FLAG_TPS) != RESET)
        {
            LOG_E("Tx Process Stopped");
            ETH_ClearDMACh0InterruptFlag(ETH, ETH_DMACH0_INT_FLAG_TPS);
        }
        if (ETH_GetDMACh0InterruptStatus(ETH, ETH_DMACH0_INT_FLAG_RPS) != RESET)
        {
            LOG_E("Rx Process Stopped");
            ETH_ClearDMACh0InterruptFlag(ETH, ETH_DMACH0_INT_FLAG_RPS);
        }

        ETH_ClearDMACh0InterruptFlag(ETH, ETH_DMACH0_INT_FLAG_AIS);
    }

    /* Check for Tx completion interrupt */
    if (ETH_GetDMACh0InterruptStatus(ETH, ETH_DMACH0_INT_FLAG_TI) != RESET)
    {
        ETH_ClearDMACh0InterruptFlag(ETH, (ETH_DMACH0_INT_FLAG_TI | ETH_DMACH0_INT_FLAG_NIS));

        /* Wake up TX thread if blocked waiting for a free descriptor */
        if (tx_is_waiting)
        {
            rt_sem_release(&tx_sem);
        }
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

/* ======================= PHY Link Status Detection ======================= */

static void phy_linkchange(void)
{
    static rt_uint8_t phy_speed     = 0;
    rt_uint8_t        phy_speed_new = 0;
    rt_uint32_t       status;
    rt_uint8_t        phy_addr = n32_eth_device.phy_addr;

    /* Read PHY Basic Status Register */
    ETH_ReadPHYRegister(ETH, phy_addr, PHY_BASIC_STATUS_REG, &status);
    LOG_D("phy basic status reg is 0x%X", (unsigned int)status);

    /* Both auto-negotiation complete AND link up must be true.
     * Checking only one bit could report fake link-up during negotiation. */
    if ((status & (PHY_AUTONEGO_COMPLETE_MASK | PHY_LINKED_STATUS_MASK)) == (PHY_AUTONEGO_COMPLETE_MASK | PHY_LINKED_STATUS_MASK))
    {
        rt_uint32_t SR = 0;

        phy_speed_new |= PHY_LINK;

#if defined(PHY_USING_DM9119INP)
        /* When using the DM9119INP, must first unlock the high-order register
         * to read the status normally */
        {
            /* Step 1 of Unlock operation */
            ETH_WritePHYRegister(ETH, phy_addr, 0x1F, 0x0168);
            /* Step 2 of Unlock operation */
            ETH_WritePHYRegister(ETH, phy_addr, 0x1E, 0x8040);
        }
        /* DM9119INP: read extended status register (0x11) for speed/duplex */
        ETH_ReadPHYRegister(ETH, phy_addr, PHY_SDSR, &SR);
        LOG_D("DM9119INP status reg is 0x%X", (unsigned int)SR);

        if (PHY_Status_SPEED_1000M(SR))
        {
            phy_speed_new |= PHY_1000M;
        }
        else if (PHY_Status_SPEED_100M(SR))
        {
            phy_speed_new |= PHY_100M;
        }
        else
        {
            phy_speed_new |= PHY_10M;
        }

        if (PHY_Status_FULL_DUPLEX(SR))
        {
            phy_speed_new |= PHY_FULL_DUPLEX;
        }

#elif defined(PHY_USING_RTL8211EG)
        /* RTL8211EG: read PHY specific status register (0x11) for speed/duplex */
        ETH_ReadPHYRegister(ETH, phy_addr, PHY_SDSR, &SR);
        LOG_D("RTL8211EG status reg is 0x%X", (unsigned int)SR);

        if (PHY_Status_SPEED_1000M(SR))
        {
            phy_speed_new |= PHY_1000M;
        }
        else if (PHY_Status_SPEED_100M(SR))
        {
            phy_speed_new |= PHY_100M;
        }
        else
        {
            phy_speed_new |= PHY_10M;
        }

        if (PHY_Status_FULL_DUPLEX(SR))
        {
            phy_speed_new |= PHY_FULL_DUPLEX;
        }

#elif defined(PHY_USING_YT8522H)
        /* YT8522H: read PHY specific status register (0x11) for speed/duplex */
        ETH_ReadPHYRegister(ETH, phy_addr, PHY_SDSR, &SR);
        LOG_D("YT8522H status reg is 0x%X", (unsigned int)SR);

        if (PHY_Status_SPEED_100M(SR))
        {
            phy_speed_new |= PHY_100M;
        }
        else
        {
            phy_speed_new |= PHY_10M;
        }

        if (PHY_Status_FULL_DUPLEX(SR))
        {
            phy_speed_new |= PHY_FULL_DUPLEX;
        }

#else
        /* Generic PHY: read from status register only, no extended info */
        phy_speed_new |= PHY_100M;
        phy_speed_new |= PHY_FULL_DUPLEX;
        LOG_W("Unknown PHY type, assuming 100M Full-Duplex");
#endif
    }

    if (phy_speed != phy_speed_new)
    {
        phy_speed = phy_speed_new;

        if (phy_speed & PHY_LINK)
        {
            LOG_I("link up");

            if (phy_speed & PHY_1000M)
            {
                LOG_D("1000Mbps");
                n32_eth_device.ETH_Speed = ETH_SPEED_1000M;
            }
            else if (phy_speed & PHY_100M)
            {
                LOG_D("100Mbps");
                n32_eth_device.ETH_Speed = ETH_SPEED_100M;
            }
            else
            {
                LOG_D("10Mbps");
                n32_eth_device.ETH_Speed = ETH_SPEED_10M;
            }

            if (phy_speed & PHY_FULL_DUPLEX)
            {
                LOG_D("full-duplex");
                n32_eth_device.ETH_Mode = ETH_FULL_DUPLEX_MODE;
            }
            else
            {
                LOG_D("half-duplex");
                n32_eth_device.ETH_Mode = ETH_HALF_DUPLEX_MODE;
            }

            /* Full restart: stop MAC/DMA/interrupts, update speed/duplex bits
             * in MACCFG (PS[15], FES[14], DM[13]), then restart everything. */
            ETH_StopIT(ETH, &sEthInfo);
            MODIFY_REG(ETH->MACCFG,
                       (ETH_MACCFG_PS | ETH_MACCFG_FES | ETH_MACCFG_DM),
                       (n32_eth_device.ETH_Speed | n32_eth_device.ETH_Mode));
            ETH_StartIT(ETH, &sEthInfo);

            /* Send link up event */
            eth_device_linkchange(&n32_eth_device.parent, RT_TRUE);
        }
        else
        {
            LOG_I("link down");
            eth_device_linkchange(&n32_eth_device.parent, RT_FALSE);
        }
    }
}

/* ======================= PHY Interrupt Mode Handler ======================= */

#ifdef PHY_USING_INTERRUPT_MODE
static void eth_phy_isr(void *args)
{
    rt_uint32_t status = 0;

#if defined(PHY_USING_DM9119INP) || defined(PHY_USING_YT8522H) || defined(PHY_USING_RTL8211EG)
    ETH_ReadPHYRegister(ETH, n32_eth_device.phy_addr, PHY_INTERRUPT_FLAG_REG, &status);
    LOG_D("phy interrupt status reg is 0x%X", (unsigned int)status);
#endif

    phy_linkchange();
}
#endif /* PHY_USING_INTERRUPT_MODE */

/* ======================= PHY Monitor Thread ======================= */

static void phy_monitor_thread_entry(void *parameter)
{
    rt_uint8_t detected_count = 0;
    rt_uint8_t phy_addr       = 0xFF;

    /* PHY auto-detection: scan addresses 0-31 for a valid PHY */
    while (phy_addr == 0xFF)
    {
        rt_uint32_t i, temp;

        for (i = 0; i <= 0x1F; i++)
        {
            ETH_ReadPHYRegister(ETH, i, PHY_ID1_REG, &temp);

#if defined(PHY_USING_YT8522H)
            /* YT8522H responds with 0xFFFF on uninitialized registers, but ID1 read can still work */
            if (temp != 0xFFFF)
#else
            if (temp != 0xFFFF && temp != 0x00)
#endif
            {
                phy_addr = (rt_uint8_t)i;
                break;
            }
        }

        detected_count++;
        rt_thread_mdelay(1000);

        if (detected_count > 10)
        {
            LOG_E("No PHY device was detected, please check hardware!");
            detected_count = 0; /* Reset count, keep trying */
        }
    }

    n32_eth_device.phy_addr = phy_addr;
    LOG_D("Found a phy, address:0x%02X", phy_addr);

    /* Reset PHY */
    LOG_D("RESET PHY!");
    ETH_WritePHYRegister(ETH, phy_addr, PHY_BASIC_CONTROL_REG, PHY_RESET_MASK);
    rt_thread_mdelay(2000);

    /* Enable auto-negotiation */
    {
        rt_uint32_t bcr;
        ETH_ReadPHYRegister(ETH, phy_addr, PHY_BASIC_CONTROL_REG, &bcr);
        bcr |= PHY_AUTO_NEGOTIATION_MASK;
        ETH_WritePHYRegister(ETH, phy_addr, PHY_BASIC_CONTROL_REG, bcr);
    }

    /* Perform initial link status check */
    phy_linkchange();

#ifdef PHY_USING_INTERRUPT_MODE
    /* Configuration interrupt pin */
    rt_pin_mode(PHY_INT_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(PHY_INT_PIN, PIN_IRQ_MODE_FALLING, eth_phy_isr, (void *)"callbackargs");
    rt_pin_irq_enable(PHY_INT_PIN, PIN_IRQ_ENABLE);

    /* Enable PHY interrupt */
#if defined(PHY_USING_DM9119INP) || defined(PHY_USING_YT8522H) || defined(PHY_USING_RTL8211EG)
    ETH_WritePHYRegister(ETH, phy_addr, PHY_INTERRUPT_MASK_REG, PHY_INT_MASK);
#endif
#if defined(PHY_INTERRUPT_CTRL_REG)
    ETH_WritePHYRegister(ETH, phy_addr, PHY_INTERRUPT_CTRL_REG, PHY_INTERRUPT_EN);
#endif

#else /* PHY_USING_INTERRUPT_MODE */
    /* Use polling timer for link status detection */
    n32_eth_device.poll_link_timer = rt_timer_create("phylnk",
                                                     (void (*)(void *))phy_linkchange,
                                                     RT_NULL,
                                                     RT_TICK_PER_SECOND,
                                                     RT_TIMER_FLAG_PERIODIC);
    if (!n32_eth_device.poll_link_timer || rt_timer_start(n32_eth_device.poll_link_timer) != RT_EOK)
    {
        LOG_E("Start link change detection timer failed");
    }
#endif /* PHY_USING_INTERRUPT_MODE */
}

/* ======================= ETH Device Registration ======================= */

static int rt_hw_n32_eth_init(void)
{
    rt_err_t state = RT_EOK;

    /* Allocate receive DMA buffer pool (contiguous) */
    Rx_Buff = (rt_uint8_t *)rt_calloc(1, ETH_RX_BUF_SIZE);
    if (Rx_Buff == RT_NULL)
    {
        LOG_E("No memory for Rx buffers");
        state = -RT_ENOMEM;
        goto __exit;
    }

    /* Allocate transmit DMA buffer pool (contiguous) */
    Tx_Buff = (rt_uint8_t *)rt_calloc(1, ETH_TX_BUF_SIZE);
    if (Tx_Buff == RT_NULL)
    {
        LOG_E("No memory for Tx buffers");
        state = -RT_ENOMEM;
        goto __exit;
    }

    /* Allocate Rx DMA descriptor table */
    DMARxDscrTab = (ETH_DMADescType *)rt_calloc(ETH_RX_DESC_NUMBER, sizeof(ETH_DMADescType));
    if (DMARxDscrTab == RT_NULL)
    {
        LOG_E("No memory for Rx descriptors");
        state = -RT_ENOMEM;
        goto __exit;
    }

    /* Allocate Tx DMA descriptor table */
    DMATxDscrTab = (ETH_DMADescType *)rt_calloc(ETH_TX_DESC_NUMBER, sizeof(ETH_DMADescType));
    if (DMATxDscrTab == RT_NULL)
    {
        LOG_E("No memory for Tx descriptors");
        state = -RT_ENOMEM;
        goto __exit;
    }

    /* Set default speed based on media interface:
     * GMII → 1000M, MII/RMII → 100M. Actual speed is updated after PHY auto-negotiation. */
#if (ETH_MEDIA_INTERFACE == ETH_GMII_MODE)
    n32_eth_device.ETH_Speed = ETH_SPEED_1000M;
#else
    n32_eth_device.ETH_Speed = ETH_SPEED_100M;
#endif
    n32_eth_device.ETH_Mode = ETH_FULL_DUPLEX_MODE;
    n32_eth_device.phy_addr = 0x00;

    /* Set MAC address - should be configured by board/application layer.
     * If all zeros, use a locally administered unicast address as fallback. */
    if ((n32_eth_device.dev_addr[0] == 0x00) && (n32_eth_device.dev_addr[1] == 0x00) &&
        (n32_eth_device.dev_addr[2] == 0x00) && (n32_eth_device.dev_addr[3] == 0x00) &&
        (n32_eth_device.dev_addr[4] == 0x00) && (n32_eth_device.dev_addr[5] == 0x00))
    {
        n32_eth_device.dev_addr[0] = 0x10;
        n32_eth_device.dev_addr[1] = 0x32;
        n32_eth_device.dev_addr[2] = 0x54;
        n32_eth_device.dev_addr[3] = 0x76;
        n32_eth_device.dev_addr[4] = 0x89;
        n32_eth_device.dev_addr[5] = 0xBA;
    }

    /* Init TX semaphore for interrupt-driven TX */
    rt_sem_init(&tx_sem, "tx_sem", 0, RT_IPC_FLAG_FIFO);

    /* Register device operations */
    n32_eth_device.parent.parent.init      = rt_n32_eth_init;
    n32_eth_device.parent.parent.open      = rt_n32_eth_open;
    n32_eth_device.parent.parent.close     = rt_n32_eth_close;
    n32_eth_device.parent.parent.read      = rt_n32_eth_read;
    n32_eth_device.parent.parent.write     = rt_n32_eth_write;
    n32_eth_device.parent.parent.control   = rt_n32_eth_control;
    n32_eth_device.parent.parent.user_data = RT_NULL;

    n32_eth_device.parent.eth_rx = rt_n32_eth_rx;
    n32_eth_device.parent.eth_tx = rt_n32_eth_tx;

    /* Register eth device */
    state = eth_device_init(&(n32_eth_device.parent), "e0");
    if (RT_EOK == state)
    {
        LOG_D("emac device init success");
    }
    else
    {
        LOG_E("emac device init faild: %d", state);
        state = -RT_ERROR;
        goto __exit;
    }

    /* Start PHY monitor thread */
    {
        rt_thread_t tid;
        tid = rt_thread_create("phy",
                               phy_monitor_thread_entry,
                               RT_NULL,
                               1024,
                               RT_THREAD_PRIORITY_MAX - 2,
                               2);
        if (tid != RT_NULL)
        {
            rt_thread_startup(tid);
        }
        else
        {
            LOG_E("create phy monitor thread failed");
            state = -RT_ERROR;
        }
    }

__exit:
    if (state != RT_EOK)
    {
        if (Rx_Buff)
        {
            rt_free(Rx_Buff);
            Rx_Buff = RT_NULL;
        }

        if (Tx_Buff)
        {
            rt_free(Tx_Buff);
            Tx_Buff = RT_NULL;
        }

        if (DMARxDscrTab)
        {
            rt_free(DMARxDscrTab);
            DMARxDscrTab = RT_NULL;
        }

        if (DMATxDscrTab)
        {
            rt_free(DMATxDscrTab);
            DMATxDscrTab = RT_NULL;
        }
    }

    return state;
}
INIT_DEVICE_EXPORT(rt_hw_n32_eth_init);

/* ---- test/monitoring accessors ---- */
#if DO_ETH_TEST
rt_uint32_t n32_eth_get_speed(void)
{
    return n32_eth_device.ETH_Speed;
}

rt_uint32_t n32_eth_get_duplex(void)
{
    return n32_eth_device.ETH_Mode;
}

rt_uint8_t n32_eth_get_phy_addr(void)
{
    return n32_eth_device.phy_addr;
}

void n32_eth_get_mac_addr(rt_uint8_t mac[6])
{
    rt_memcpy(mac, n32_eth_device.dev_addr, 6);
}

const char *n32_eth_get_phy_name(void)
{
#if defined(PHY_USING_DM9119INP)
    return "DM9119INP";
#elif defined(PHY_USING_RTL8211EG)
    return "RTL8211EG";
#elif defined(PHY_USING_YT8522H)
    return "YT8522H";
#else
    return "Unknown";
#endif
}
#endif /* DO_ETH_TEST */
