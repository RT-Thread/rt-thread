/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-05     Tim        First version for i.MXRT1180 NETC EP0
 * 2026-06-09     Tim        Add Switch support
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include "board.h"

#ifdef RT_USING_LWIP

#include <lwip/pbuf.h>
#include <netif/ethernetif.h>

#ifndef NETC_RX_ZERO_COPY
#define NETC_RX_ZERO_COPY 1
#endif

#ifndef NETC_USE_SWT
#define NETC_USE_SWT 0
#endif

#if NETC_RX_ZERO_COPY && !LWIP_SUPPORT_CUSTOM_PBUF
#error "NETC RX zero-copy requires LWIP_SUPPORT_CUSTOM_PBUF=1 in lwipopts.h"
#endif

#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_netc_soc.h"
#include "fsl_netc_endpoint.h"
#if NETC_USE_SWT
#if defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH
#error "NETC_USE_SWT requires NETC switch hardware support"
#endif
#include "fsl_netc_switch.h"
#endif
#if defined(FSL_FEATURE_NETC_HAS_SWITCH_TAG) && FSL_FEATURE_NETC_HAS_SWITCH_TAG
#include "fsl_netc_tag.h"
#endif
#include "fsl_netc_mdio.h"
#include "fsl_msgintr.h"

#define LOG_TAG "drv.netc"
#include "drv_log.h"

#define NETC_RING_ID            0U
#define NETC_RXBD_NUM           8U
#define NETC_TXBD_NUM           8U
#define NETC_CMDBD_NUM          8U
#define NETC_RXBUFF_SIZE        1536U
#define NETC_BUFF_ALIGNMENT     64U
#define NETC_FRAME_MAX_FRAMELEN 1518U
#define NETC_RXBUFF_ALIGNED_SIZE \
    (((NETC_RXBUFF_SIZE + NETC_BUFF_ALIGNMENT - 1U) / NETC_BUFF_ALIGNMENT) * NETC_BUFF_ALIGNMENT)
#define NETC_MAX_BUFFERS_PER_FRAME \
    ((NETC_FRAME_MAX_FRAMELEN + NETC_RXBUFF_ALIGNED_SIZE - 1U) / NETC_RXBUFF_ALIGNED_SIZE)
#define NETC_PHY_STATUS_REG      0x01U
#define NETC_PHY_LINK_UP_MASK    0x0004U
#define NETC_PHY_POLL_DELAY_TICK (RT_TICK_PER_SECOND)
#define NETC_TX_TIMEOUT_TICK     (RT_TICK_PER_SECOND)

#if NETC_RXBD_NUM < NETC_MAX_BUFFERS_PER_FRAME
#error "NETC_RXBD_NUM < NETC_MAX_BUFFERS_PER_FRAME"
#endif

#ifndef NETC_RXBUFF_NUM
#define NETC_RXBUFF_NUM (NETC_RXBD_NUM + 5U)
#endif

#if NETC_RX_ZERO_COPY && (NETC_RXBUFF_NUM < (NETC_RXBD_NUM + NETC_MAX_BUFFERS_PER_FRAME))
#error "NETC_RXBUFF_NUM < (NETC_RXBD_NUM + NETC_MAX_BUFFERS_PER_FRAME)"
#endif

#if NETC_RX_ZERO_COPY
#define NETC_RXBUFF_TOTAL_NUM NETC_RXBUFF_NUM
#else
#define NETC_RXBUFF_TOTAL_NUM NETC_RXBD_NUM
#endif

#define NETC_MII_MODE    kNETC_RmiiMode
#define NETC_LINK_SPEED  kNETC_MiiSpeed100M
#define NETC_LINK_DUPLEX kNETC_MiiFullDuplex

#if NETC_USE_SWT
#define NETC_PSI kNETC_ENETC1PSI0
#ifndef NETC_PHY_ADDR
#define NETC_PHY_ADDR BOARD_SWT_PORT0_PHY_ADDR
#endif
#ifndef NETC_SWT_MAX_PORT_NUM
#define NETC_SWT_MAX_PORT_NUM 4U
#endif
#ifndef NETC_SWT_USED_PORT_BITMAP
#define NETC_SWT_USED_PORT_BITMAP 0x5U
#endif
#ifndef NETC_SWT_PSEUDO_PORT
#define NETC_SWT_PSEUDO_PORT 0x4U
#endif
#ifndef NETC_SWT_TX_PORT
#define NETC_SWT_TX_PORT kNETC_SWITCH0Port0
#endif
#else
#define NETC_PSI kNETC_ENETC0PSI0
#ifndef NETC_PHY_ADDR
#define NETC_PHY_ADDR BOARD_EP0_PHY_ADDR
#endif
#endif

#define NETC_MSGINTR     MSGINTR1
#define NETC_MSGINTR_IRQ MSGINTR1_IRQn

#define NETC_MSIX_ENTRY_NUM   2U
#define TX_MSIX_ENTRY_IDX     0U
#define RX_MSIX_ENTRY_IDX     1U
#define SI_COM_MSIX_ENTRY_IDX 2U
#define TX_INTR_MSG_DATA      1U
#define RX_INTR_MSG_DATA      2U
#define SI_COM_INTR_MSG_DATA  3U

#define NETC_DEFAULT_MAC0 0x54U
#define NETC_DEFAULT_MAC1 0x27U
#define NETC_DEFAULT_MAC2 0x8DU
#define NETC_DEFAULT_MAC3 0x11U
#define NETC_DEFAULT_MAC4 0x80U
#define NETC_DEFAULT_MAC5 0x00U

#ifndef RT_NTCP_THREAD_STACK_SIZE
#define RT_NTCP_THREAD_STACK_SIZE 4096
#endif

#ifndef RT_NTCP_THREAD_PRIORITY
#define RT_NTCP_THREAD_PRIORITY 15
#endif

struct rt_imxrt_netc
{
    struct eth_device parent;

    ep_handle_t ep_handle;
#if NETC_USE_SWT
    swt_handle_t swt_handle;
#endif
    netc_mdio_handle_t mdio_handle;

    struct rt_mutex lock;
    struct rt_semaphore tx_isr_sem;

    rt_bool_t hw_inited;
    rt_bool_t mdio_inited;
    rt_bool_t link_up;
#if NETC_USE_SWT
    rt_bool_t swt_inited;
#endif

    rt_uint8_t dev_addr[6];
};

#if NETC_RX_ZERO_COPY
typedef struct netc_rx_pbuf_wrapper
{
    struct pbuf_custom custom;
    void *buffer;
    volatile rt_bool_t buffer_used;
#if NETC_USE_SWT
    swt_handle_t *handle;
#else
    ep_handle_t *handle;
#endif
    rt_uint8_t ring;
} netc_rx_pbuf_wrapper_t;
#endif

AT_NONCACHEABLE_SECTION_ALIGN(static netc_rx_bd_t g_netc_rx_bd[NETC_RXBD_NUM], 128);
AT_NONCACHEABLE_SECTION_ALIGN(static netc_tx_bd_t g_netc_tx_bd[NETC_TXBD_NUM], 128);
AT_NONCACHEABLE_SECTION_ALIGN(static netc_cmd_bd_t g_netc_cmd_bd[NETC_CMDBD_NUM], 128);
#if NETC_USE_SWT
AT_NONCACHEABLE_SECTION_ALIGN(static netc_cmd_bd_t g_netc_swt_cmd_bd[NETC_CMDBD_NUM], 128);
#endif
AT_NONCACHEABLE_SECTION_ALIGN(static rt_uint8_t g_netc_rx_buf[NETC_RXBUFF_TOTAL_NUM][NETC_RXBUFF_SIZE],
                              NETC_BUFF_ALIGNMENT);

static uint64_t g_netc_rx_buf_addr[NETC_RXBD_NUM];
static netc_tx_frame_info_t g_netc_tx_dirty[NETC_TXBD_NUM];
static netc_msix_entry_t g_netc_msix_entry[NETC_MSIX_ENTRY_NUM];

#if NETC_USE_SWT
static swt_config_t g_netc_swt_config;
static swt_transfer_config_t g_netc_swt_transfer_config;
#endif

#if NETC_RX_ZERO_COPY
static netc_rx_pbuf_wrapper_t g_netc_rx_pbufs[NETC_RXBUFF_TOTAL_NUM];
#endif

static struct rt_imxrt_netc imxrt_netc_device;

#if NETC_RX_ZERO_COPY
#if NETC_USE_SWT
static void *_netc_rx_buff_alloc(swt_handle_t *handle, uint32_t length, void *userData)
#else
static void *_netc_rx_buff_alloc(ep_handle_t *handle, uint8_t ring, uint32_t length, void *userData)
#endif
{
    netc_rx_pbuf_wrapper_t *rx_pbufs = (netc_rx_pbuf_wrapper_t *)userData;
    void *buffer = RT_NULL;
    rt_base_t level;
    rt_uint32_t i;

    RT_UNUSED(handle);
#if !NETC_USE_SWT
    RT_UNUSED(ring);
#endif

    if ((rx_pbufs == RT_NULL) || (length > NETC_RXBUFF_SIZE))
    {
        return RT_NULL;
    }

    level = rt_hw_interrupt_disable();
    for (i = 0; i < NETC_RXBUFF_TOTAL_NUM; i++)
    {
        if (!rx_pbufs[i].buffer_used)
        {
            rx_pbufs[i].buffer_used = RT_TRUE;
            buffer = rx_pbufs[i].buffer;
            break;
        }
    }
    rt_hw_interrupt_enable(level);

    return buffer;
}

#if NETC_USE_SWT
static void _netc_rx_buff_free(swt_handle_t *handle, void *address, void *userData)
#else
static void _netc_rx_buff_free(ep_handle_t *handle, uint8_t ring, void *address, void *userData)
#endif
{
    netc_rx_pbuf_wrapper_t *rx_pbufs = (netc_rx_pbuf_wrapper_t *)userData;
    rt_base_t level;
    rt_uint32_t i;

#if !NETC_USE_SWT
    RT_UNUSED(ring);
#endif

    if ((rx_pbufs == RT_NULL) && (handle != RT_NULL))
    {
        rx_pbufs = (netc_rx_pbuf_wrapper_t *)handle->cfg.userData;
    }

    if ((rx_pbufs == RT_NULL) || (address == RT_NULL))
    {
        return;
    }

    level = rt_hw_interrupt_disable();
    for (i = 0; i < NETC_RXBUFF_TOTAL_NUM; i++)
    {
        if (rx_pbufs[i].buffer == address)
        {
            rx_pbufs[i].buffer_used = RT_FALSE;
            break;
        }
    }
    rt_hw_interrupt_enable(level);

    if (i >= NETC_RXBUFF_TOTAL_NUM)
    {
        LOG_W("unknown NETC Rx zero-copy buffer: %p", address);
    }
}

static void _netc_rx_pbuf_free(struct pbuf *p)
{
    netc_rx_pbuf_wrapper_t *rx_pbuf = (netc_rx_pbuf_wrapper_t *)p;

#if NETC_USE_SWT
    _netc_rx_buff_free(rx_pbuf->handle, rx_pbuf->buffer, RT_NULL);
#else
    _netc_rx_buff_free(rx_pbuf->handle, rx_pbuf->ring, rx_pbuf->buffer, RT_NULL);
#endif
}

static netc_rx_pbuf_wrapper_t *_netc_find_rx_pbuf(void *buffer)
{
    rt_uint32_t i;

    for (i = 0; i < NETC_RXBUFF_TOTAL_NUM; i++)
    {
        if (g_netc_rx_pbufs[i].buffer == buffer)
        {
            return &g_netc_rx_pbufs[i];
        }
    }

    return RT_NULL;
}

static void _netc_rx_release_frame_buffers(struct rt_imxrt_netc *netc,
                                           netc_frame_struct_t *frame,
                                           rt_uint16_t start)
{
    rt_uint16_t i;

    for (i = start; i < frame->length; i++)
    {
        if (frame->buffArray[i].buffer != RT_NULL)
        {
#if NETC_USE_SWT
            _netc_rx_buff_free(&netc->swt_handle,
                               frame->buffArray[i].buffer,
                               netc->swt_handle.cfg.userData);
#else
            _netc_rx_buff_free(&netc->ep_handle,
                               NETC_RING_ID,
                               frame->buffArray[i].buffer,
                               netc->ep_handle.cfg.userData);
#endif
        }
    }
}

static struct pbuf *_netc_rx_frame_to_pbufs(struct rt_imxrt_netc *netc, netc_frame_struct_t *frame)
{
    struct pbuf *p_root = RT_NULL;
    struct pbuf *p;
    rt_uint16_t i;

    for (i = 0; i < frame->length; i++)
    {
        netc_buffer_struct_t *buff = &frame->buffArray[i];
        netc_rx_pbuf_wrapper_t *rx_pbuf = _netc_find_rx_pbuf(buff->buffer);

        if (rx_pbuf == RT_NULL)
        {
            LOG_W("NETC Rx buffer is not in zero-copy pool");
            _netc_rx_release_frame_buffers(netc, frame, i);
            if (p_root != RT_NULL)
            {
                pbuf_free(p_root);
            }
            return RT_NULL;
        }

        p = pbuf_alloced_custom(PBUF_RAW,
                                buff->length,
                                PBUF_REF,
                                &rx_pbuf->custom,
                                buff->buffer,
                                NETC_RXBUFF_SIZE);
        if (p == RT_NULL)
        {
            LOG_W("pbuf_alloced_custom failed");
            _netc_rx_release_frame_buffers(netc, frame, i);
            if (p_root != RT_NULL)
            {
                pbuf_free(p_root);
            }
            return RT_NULL;
        }

        if (p_root == RT_NULL)
        {
            p_root = p;
        }
        else
        {
            pbuf_cat(p_root, p);
        }
    }

    return p_root;
}
#endif

static status_t _netc_tx_reclaim_callback(ep_handle_t *handle,
                                          uint8_t ring,
                                          netc_tx_frame_info_t *frameInfo,
                                          void *userData)
{
    RT_UNUSED(handle);
    RT_UNUSED(ring);
    RT_UNUSED(userData);

    if ((frameInfo != RT_NULL) && (frameInfo->context != RT_NULL))
    {
        rt_free(frameInfo->context);
        frameInfo->context = RT_NULL;
    }

    return kStatus_Success;
}

#if NETC_USE_SWT
static status_t _netc_swt_reclaim_callback(swt_handle_t *handle,
                                           netc_tx_frame_info_t *frameInfo,
                                           void *userData)
{
    RT_UNUSED(handle);
    RT_UNUSED(userData);

    if ((frameInfo != RT_NULL) && (frameInfo->context != RT_NULL))
    {
        rt_free(frameInfo->context);
        frameInfo->context = RT_NULL;
    }

    return kStatus_Success;
}

static status_t _netc_swt_add_table_entry(swt_handle_t *swt_handle)
{
    netc_tb_ipf_config_t ipf_entry_config;
    status_t result = kStatus_Success;
    uint32_t entry_id;
    rt_uint32_t i;

    rt_memset(&ipf_entry_config, 0, sizeof(ipf_entry_config));
    ipf_entry_config.keye.srcPortMask = NETC_SWT_USED_PORT_BITMAP;
    ipf_entry_config.cfge.hr = kNETC_SoftwareDefHR0;
    ipf_entry_config.cfge.fltfa = kNETC_IPFRedirectToMgmtPort;

    for (i = 0; i < NETC_SWT_MAX_PORT_NUM; i++)
    {
        if (((1U << i) & NETC_SWT_USED_PORT_BITMAP) == 0U)
        {
            continue;
        }

        entry_id = 0xFFFFFFFFU;
        ipf_entry_config.keye.srcPort = i;
        result = SWT_RxIPFAddTableEntry(swt_handle, &ipf_entry_config, &entry_id);
        if ((result != kStatus_Success) && (entry_id != 0xFFFFFFFFU))
        {
            LOG_E("SWT_RxIPFAddTableEntry failed: %d, entry %u", result, entry_id);
            return result;
        }
    }

    return result;
}

static rt_err_t _netc_swt_configure_link(struct rt_imxrt_netc *netc)
{
    status_t result;
    rt_uint32_t i;

    for (i = 0; i < NETC_SWT_MAX_PORT_NUM; i++)
    {
        if (((1U << i) & NETC_SWT_USED_PORT_BITMAP) == 0U)
        {
            continue;
        }

        result = SWT_SetEthPortMII(&netc->swt_handle, (uint8_t)i, NETC_LINK_SPEED, NETC_LINK_DUPLEX);
        if (result != kStatus_Success)
        {
            LOG_E("SWT_SetEthPortMII port %u failed: %d", i, result);
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}

static rt_err_t _netc_swt_init(struct rt_imxrt_netc *netc)
{
    status_t result;
    rt_uint32_t i;

    if (netc->swt_inited)
    {
        return _netc_swt_configure_link(netc);
    }

    result = SWT_GetDefaultConfig(&g_netc_swt_config);
    if (result != kStatus_Success)
    {
        LOG_E("SWT_GetDefaultConfig failed: %d", result);
        return -RT_ERROR;
    }

    for (i = 0; i < NETC_SWT_MAX_PORT_NUM; i++)
    {
        if (((1U << i) & NETC_SWT_USED_PORT_BITMAP) == 0U)
        {
            continue;
        }

        g_netc_swt_config.ports[i].ethMac.miiMode = NETC_MII_MODE;
        g_netc_swt_config.ports[i].ethMac.miiSpeed = NETC_LINK_SPEED;
        g_netc_swt_config.ports[i].ethMac.miiDuplex = NETC_LINK_DUPLEX;
        g_netc_swt_config.ports[i].ethMac.rxMaxFrameSize = NETC_FRAME_MAX_FRAMELEN;
        g_netc_swt_config.ports[i].commonCfg.ipfCfg.enIPFTable = true;
    }

    g_netc_swt_config.bridgeCfg.dVFCfg.portMembership =
        (1U << NETC_SWT_PSEUDO_PORT) | NETC_SWT_USED_PORT_BITMAP;
    g_netc_swt_config.cmdRingUse = 1U;
    g_netc_swt_config.cmdBdrCfg[0].bdBase = g_netc_swt_cmd_bd;
    g_netc_swt_config.cmdBdrCfg[0].bdLength = NETC_CMDBD_NUM;

    result = SWT_Init(&netc->swt_handle, &g_netc_swt_config);
    if (result != kStatus_Success)
    {
        LOG_E("SWT_Init failed: %d", result);
        return -RT_ERROR;
    }

    rt_memset(&g_netc_swt_transfer_config, 0, sizeof(g_netc_swt_transfer_config));
    g_netc_swt_transfer_config.enUseMgmtRxBdRing = false;
    g_netc_swt_transfer_config.enUseMgmtTxBdRing = true;
    g_netc_swt_transfer_config.mgmtTxBdrConfig.bdArray = g_netc_tx_bd;
    g_netc_swt_transfer_config.mgmtTxBdrConfig.len = NETC_TXBD_NUM;
    g_netc_swt_transfer_config.mgmtTxBdrConfig.dirtyArray = g_netc_tx_dirty;
    g_netc_swt_transfer_config.mgmtTxBdrConfig.msixEntryIdx = TX_MSIX_ENTRY_IDX;
    g_netc_swt_transfer_config.mgmtTxBdrConfig.enIntr = true;
    g_netc_swt_transfer_config.reclaimCallback = _netc_swt_reclaim_callback;
#if NETC_RX_ZERO_COPY
    g_netc_swt_transfer_config.rxZeroCopy = true;
    g_netc_swt_transfer_config.rxBuffAlloc = _netc_rx_buff_alloc;
    g_netc_swt_transfer_config.rxBuffFree = _netc_rx_buff_free;
    g_netc_swt_transfer_config.userData = g_netc_rx_pbufs;
#else
    g_netc_swt_transfer_config.rxZeroCopy = false;
    g_netc_swt_transfer_config.rxBuffAlloc = RT_NULL;
    g_netc_swt_transfer_config.rxBuffFree = RT_NULL;
    g_netc_swt_transfer_config.userData = netc;
#endif
    g_netc_swt_transfer_config.rxCacheMaintain = true;
    g_netc_swt_transfer_config.txCacheMaintain = true;


    result = SWT_ManagementTxRxConfig(&netc->swt_handle, &netc->ep_handle, &g_netc_swt_transfer_config);
    if (result != kStatus_Success)
    {
        LOG_E("SWT_ManagementTxRxConfig failed: %d", result);
        return -RT_ERROR;
    }

    result = _netc_swt_add_table_entry(&netc->swt_handle);
    if (result != kStatus_Success)
    {
        return -RT_ERROR;
    }

    netc->swt_inited = RT_TRUE;

    return RT_EOK;
}
#endif

static rt_bool_t _netc_phy_get_link(struct rt_imxrt_netc *netc)
{
    uint16_t phy_status = 0;

    if (!netc->mdio_inited)
    {
        return RT_TRUE;
    }

    /* BMSR is latch-low on many PHYs, so read twice. */
    if (NETC_MDIORead(&netc->mdio_handle, NETC_PHY_ADDR, NETC_PHY_STATUS_REG, &phy_status) != kStatus_Success)
    {
        return netc->link_up;
    }

    if (NETC_MDIORead(&netc->mdio_handle, NETC_PHY_ADDR, NETC_PHY_STATUS_REG, &phy_status) != kStatus_Success)
    {
        return netc->link_up;
    }

    return ((phy_status & NETC_PHY_LINK_UP_MASK) != 0U) ? RT_TRUE : RT_FALSE;
}

static void _netc_msgintr_callback(MSGINTR_Type *base, uint8_t channel, uint32_t pendingIntr)
{
    RT_UNUSED(base);

    if (channel != 0)
    {
        return;
    }

    rt_interrupt_enter();

    if ((pendingIntr & (1U << TX_INTR_MSG_DATA)) != 0U)
    {
        EP_CleanTxIntrFlags(&imxrt_netc_device.ep_handle, 1, 0);
        rt_sem_release(&imxrt_netc_device.tx_isr_sem);
    }

    if ((pendingIntr & (1U << RX_INTR_MSG_DATA)) != 0U)
    {
        EP_CleanRxIntrFlags(&imxrt_netc_device.ep_handle, 1);
        (void)eth_device_ready(&imxrt_netc_device.parent);
    }

    rt_interrupt_leave();
}

static rt_err_t _netc_wait_tx_complete(struct rt_imxrt_netc *netc)
{
    if (rt_sem_take(&netc->tx_isr_sem, NETC_TX_TIMEOUT_TICK) != RT_EOK)
    {
        LOG_E("NETC Tx wait timeout");
        return -RT_ETIMEOUT;
    }

    rt_mutex_take(&netc->lock, RT_WAITING_FOREVER);
#if NETC_USE_SWT
#if defined(FSL_FEATURE_NETC_HAS_SWITCH_TAG) && FSL_FEATURE_NETC_HAS_SWITCH_TAG
    SWT_ReclaimTxDescriptor(&netc->swt_handle, NETC_RING_ID);
#else
    SWT_ReclaimTxDescriptor(&netc->swt_handle, false, NETC_RING_ID);
#endif
#else
    EP_ReclaimTxDescriptor(&netc->ep_handle, NETC_RING_ID);
#endif
    rt_mutex_release(&netc->lock);

    return RT_EOK;
}

static rt_err_t _netc_hw_init(struct rt_imxrt_netc *netc)
{
    ep_config_t ep_config;
    netc_bdr_config_t bdr_config;
    netc_rx_bdr_config_t rx_bdr_config[1];
    netc_tx_bdr_config_t tx_bdr_config[1];
    netc_mdio_config_t mdio_config;
    status_t result;
    rt_uint32_t i;

    if (netc->hw_inited)
    {
        return RT_EOK;
    }

    CLOCK_EnableClock(kCLOCK_Netc);

    /* RT1180 NETC access needs TRDC permissions and board-side NETC strap setup. */
    //BOARD_CommonSetting();
    PHY_Reset();
    BOARD_NETC_Init();

    for (i = 0; i < NETC_RXBD_NUM; i++)
    {
        g_netc_rx_buf_addr[i] = (uint64_t)(uintptr_t)&g_netc_rx_buf[i][0];
    }

#if NETC_RX_ZERO_COPY
    for (i = 0; i < NETC_RXBUFF_TOTAL_NUM; i++)
    {
        g_netc_rx_pbufs[i].custom.custom_free_function = _netc_rx_pbuf_free;
        g_netc_rx_pbufs[i].buffer = &g_netc_rx_buf[i][0];
#if NETC_USE_SWT
        g_netc_rx_pbufs[i].buffer_used = (i < NETC_RXBD_NUM) ? RT_TRUE : RT_FALSE;
        g_netc_rx_pbufs[i].handle = &netc->swt_handle;
#else
        g_netc_rx_pbufs[i].buffer_used = RT_FALSE;
        g_netc_rx_pbufs[i].handle = &netc->ep_handle;
#endif
        g_netc_rx_pbufs[i].ring = NETC_RING_ID;
    }
#endif

    rt_memset(g_netc_rx_bd, 0, sizeof(g_netc_rx_bd));
    rt_memset(g_netc_tx_bd, 0, sizeof(g_netc_tx_bd));
    rt_memset(g_netc_cmd_bd, 0, sizeof(g_netc_cmd_bd));
#if NETC_USE_SWT
    rt_memset(g_netc_swt_cmd_bd, 0, sizeof(g_netc_swt_cmd_bd));
#endif
    rt_memset(g_netc_tx_dirty, 0, sizeof(g_netc_tx_dirty));
    rt_memset(&ep_config, 0, sizeof(ep_config));
    rt_memset(&bdr_config, 0, sizeof(bdr_config));
    rt_memset(rx_bdr_config, 0, sizeof(rx_bdr_config));
    rt_memset(tx_bdr_config, 0, sizeof(tx_bdr_config));
    rt_memset(&mdio_config, 0, sizeof(mdio_config));

    /* MSIX and interrupt configuration. */
    MSGINTR_Init(NETC_MSGINTR, &_netc_msgintr_callback);
    uint32_t msgAddr = MSGINTR_GetIntrSelectAddr(NETC_MSGINTR, 0);
    g_netc_msix_entry[0].control = kNETC_MsixIntrMaskBit;
    g_netc_msix_entry[0].msgAddr = msgAddr;
    g_netc_msix_entry[0].msgData = TX_INTR_MSG_DATA;
    g_netc_msix_entry[1].control = kNETC_MsixIntrMaskBit;
    g_netc_msix_entry[1].msgAddr = msgAddr;
    g_netc_msix_entry[1].msgData = RX_INTR_MSG_DATA;

    result = EP_GetDefaultConfig(&ep_config);
    if (result != kStatus_Success)
    {
        LOG_E("EP_GetDefaultConfig failed: %d", result);
        return -RT_ERROR;
    }

    ep_config.si = NETC_PSI;
    ep_config.siConfig.rxRingUse = 1U;
    ep_config.siConfig.txRingUse = 1U;
    ep_config.siConfig.rxBdrGroupNum = 0U;
    ep_config.siConfig.ringPerBdrGroup = 1U;
    ep_config.siConfig.defaultRxBdrGroup = kNETC_SiBDRGroupOne;
    ep_config.entryNum = 2U;
    ep_config.msixEntry = &g_netc_msix_entry[0];
    ep_config.cmdBdEntryIdx = 0U;
    ep_config.siComEntryIdx = 0U;
    ep_config.timerSyncEntryIdx = 0U;
    ep_config.reclaimCallback = _netc_tx_reclaim_callback;
#if NETC_RX_ZERO_COPY
    ep_config.userData = g_netc_rx_pbufs;
#else
    ep_config.userData = netc;
#endif
    ep_config.rxCacheMaintain = false;
#if defined(FSL_ETH_ENABLE_CACHE_CONTROL)
    ep_config.txCacheMaintain = true;
#else
    ep_config.txCacheMaintain = false;
#endif
#if NETC_RX_ZERO_COPY && !NETC_USE_SWT
    ep_config.rxZeroCopy = true;
    ep_config.rxBuffAlloc = _netc_rx_buff_alloc;
    ep_config.rxBuffFree = _netc_rx_buff_free;
#else
    ep_config.rxZeroCopy = false;
    ep_config.rxBuffAlloc = RT_NULL;
    ep_config.rxBuffFree = RT_NULL;
#endif
    ep_config.cmdBdrConfig.bdBase = g_netc_cmd_bd;
    ep_config.cmdBdrConfig.bdLength = NETC_CMDBD_NUM;
    ep_config.cmdBdrConfig.enCompInt = false;

    ep_config.port.ethMac.miiMode = NETC_MII_MODE;
    ep_config.port.ethMac.miiSpeed = NETC_LINK_SPEED;
    ep_config.port.ethMac.miiDuplex = NETC_LINK_DUPLEX;
    ep_config.port.ethMac.rxMaxFrameSize = NETC_FRAME_MAX_FRAMELEN;

    rx_bdr_config[0].extendDescEn = false;
    rx_bdr_config[0].bdArray = g_netc_rx_bd;
    rx_bdr_config[0].len = NETC_RXBD_NUM;
    rx_bdr_config[0].buffAddrArray = g_netc_rx_buf_addr;
    rx_bdr_config[0].buffSize = NETC_RXBUFF_SIZE;
    rx_bdr_config[0].enThresIntr = true;
    rx_bdr_config[0].enCoalIntr = true;
    rx_bdr_config[0].intrThreshold = 1U;
    rx_bdr_config[0].intrTimerThres = 0U;
    rx_bdr_config[0].msixEntryIdx = RX_MSIX_ENTRY_IDX;
    rx_bdr_config[0].disVlanPresent = false;
    rx_bdr_config[0].enVlanExtract = false;
    rx_bdr_config[0].isKeepCRC = false;
    rx_bdr_config[0].congestionMode = false;
    rx_bdr_config[0].enHeaderAlign = false;

    tx_bdr_config[0].len = NETC_TXBD_NUM;
    tx_bdr_config[0].bdArray = g_netc_tx_bd;
    tx_bdr_config[0].dirtyArray = g_netc_tx_dirty;
    tx_bdr_config[0].enIntr = true;
    tx_bdr_config[0].enThresIntr = false;
    tx_bdr_config[0].enCoalIntr = false;
    tx_bdr_config[0].intrThreshold = 0U;
    tx_bdr_config[0].intrTimerThres = 0U;
    tx_bdr_config[0].msixEntryIdx = TX_MSIX_ENTRY_IDX;
    tx_bdr_config[0].isVlanInsert = false;
    tx_bdr_config[0].isUserCRC = false;
    tx_bdr_config[0].wrrWeight = 1U;
    tx_bdr_config[0].priority = 0U;

    bdr_config.rxBdrConfig = rx_bdr_config;
    bdr_config.txBdrConfig = tx_bdr_config;

    result = EP_Init(&netc->ep_handle, netc->dev_addr, &ep_config, &bdr_config);
    if (result != kStatus_Success)
    {
        LOG_E("EP_Init failed: %d", result);
        return -RT_ERROR;
    }

    mdio_config.mdio.type = kNETC_EMdio;
    mdio_config.srcClockHz = CLOCK_GetRootClockFreq(kCLOCK_Root_Netc);
    mdio_config.isNegativeDriven = false;
    mdio_config.isPreambleDisable = false;

    result = NETC_MDIOInit(&netc->mdio_handle, &mdio_config);
    if (result == kStatus_Success)
    {
        netc->mdio_inited = RT_TRUE;
    }
    else
    {
        netc->mdio_inited = RT_FALSE;
        LOG_W("NETC_MDIOInit failed: %d, continue with fixed MAC configuration", result);
    }

    result = EP_Up(&netc->ep_handle, NETC_LINK_SPEED, NETC_LINK_DUPLEX);
    if (result != kStatus_Success)
    {
        LOG_E("EP_Up failed: %d", result);
        return -RT_ERROR;
    }

#if NETC_USE_SWT
    if (_netc_swt_init(netc) != RT_EOK)
    {
        return -RT_ERROR;
    }
#endif

    netc->link_up = _netc_phy_get_link(netc);
    if (!netc->link_up)
    {
#if !NETC_USE_SWT
        (void)EP_Down(&netc->ep_handle);
#endif
    }

    netc->hw_inited = RT_TRUE;

    EP_MsixSetEntryMask(&netc->ep_handle, TX_MSIX_ENTRY_IDX, false);
    EP_MsixSetEntryMask(&netc->ep_handle, RX_MSIX_ENTRY_IDX, false);

#if NETC_USE_SWT
    LOG_I("NETC ENETC1 initialized, MAC %02x:%02x:%02x:%02x:%02x:%02x",
          netc->dev_addr[0], netc->dev_addr[1], netc->dev_addr[2],
          netc->dev_addr[3], netc->dev_addr[4], netc->dev_addr[5]);
#else
    LOG_I("NETC ENETC0 initialized, MAC %02x:%02x:%02x:%02x:%02x:%02x",
          netc->dev_addr[0], netc->dev_addr[1], netc->dev_addr[2],
          netc->dev_addr[3], netc->dev_addr[4], netc->dev_addr[5]);
#endif

    return RT_EOK;
}

static void _netc_poll_thread_entry(void *parameter)
{
    struct rt_imxrt_netc *netc = (struct rt_imxrt_netc *)parameter;

    while (1)
    {
        rt_bool_t link_now;

        if (!netc->hw_inited)
        {
            rt_thread_delay(NETC_PHY_POLL_DELAY_TICK);
            continue;
        }

        link_now = _netc_phy_get_link(netc);
        if (link_now != netc->link_up)
        {
            rt_mutex_take(&netc->lock, RT_WAITING_FOREVER);
            if (link_now)
            {
                (void)EP_Up(&netc->ep_handle, NETC_LINK_SPEED, NETC_LINK_DUPLEX);
#if NETC_USE_SWT
                (void)_netc_swt_init(netc);
#endif
            }
            else
            {
#if !NETC_USE_SWT
                (void)EP_Down(&netc->ep_handle);
#endif
            }
            netc->link_up = link_now;
            rt_mutex_release(&netc->lock);

            eth_device_linkchange(&netc->parent, netc->link_up);
        }

        rt_thread_delay(NETC_PHY_POLL_DELAY_TICK);
    }
}

static rt_err_t rt_imxrt_netc_init(rt_device_t dev)
{
    RT_UNUSED(dev);
    return _netc_hw_init(&imxrt_netc_device);
}

static rt_err_t rt_imxrt_netc_open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_UNUSED(dev);
    RT_UNUSED(oflag);
    return RT_EOK;
}

static rt_err_t rt_imxrt_netc_close(rt_device_t dev)
{
    RT_UNUSED(dev);
    return RT_EOK;
}

static rt_ssize_t rt_imxrt_netc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_UNUSED(dev);
    RT_UNUSED(pos);
    RT_UNUSED(buffer);
    RT_UNUSED(size);
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_imxrt_netc_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    RT_UNUSED(dev);
    RT_UNUSED(pos);
    RT_UNUSED(buffer);
    RT_UNUSED(size);
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_imxrt_netc_control(rt_device_t dev, int cmd, void *args)
{
    RT_UNUSED(dev);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args == RT_NULL)
        {
            return -RT_ERROR;
        }

        rt_memcpy(args, imxrt_netc_device.dev_addr, sizeof(imxrt_netc_device.dev_addr));
        break;

    default:
        break;
    }

    return RT_EOK;
}

static rt_err_t rt_imxrt_netc_tx(rt_device_t dev, struct pbuf *p)
{
    struct rt_imxrt_netc *netc = &imxrt_netc_device;
    netc_buffer_struct_t tx_buff;
    netc_frame_struct_t frame;
#if NETC_USE_SWT
    swt_tx_opt tx_opt;
#else
    ep_tx_opt tx_opt;
#endif
    void *tx_data;
    status_t result;

    RT_UNUSED(dev);
    RT_ASSERT(p != RT_NULL);

    if (!netc->hw_inited)
    {
        return -RT_ERROR;
    }

    if (!netc->link_up)
    {
        return -RT_ERROR;
    }

    if (p->tot_len == 0U)
    {
        return -RT_ERROR;
    }

    while (rt_sem_take(&netc->tx_isr_sem, 0) == RT_EOK)
    {
    }

    tx_data = rt_malloc(p->tot_len);
    if (tx_data == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    (void)pbuf_copy_partial(p, tx_data, p->tot_len, 0);

    tx_buff.buffer = tx_data;
    tx_buff.length = (uint16_t)p->tot_len;
    frame.buffArray = &tx_buff;
    frame.length = 1U;
    rt_memset(&tx_opt, 0, sizeof(tx_opt));

    do
    {
        rt_mutex_take(&netc->lock, RT_WAITING_FOREVER);
#if NETC_USE_SWT
#if defined(FSL_FEATURE_NETC_HAS_SWITCH_TAG) && FSL_FEATURE_NETC_HAS_SWITCH_TAG
        result = SWT_SendFrame(&netc->swt_handle, &frame, tx_data, &tx_opt);
#else
        {
            swt_mgmt_tx_arg_t tx_arg = { .ring = NETC_RING_ID };

            result = SWT_SendFrame(&netc->swt_handle,
                                   tx_arg,
                                   NETC_SWT_TX_PORT,
                                   false,
                                   &frame,
                                   tx_data,
                                   &tx_opt);
        }
#endif
#else
        result = EP_SendFrame(&netc->ep_handle, NETC_RING_ID, &frame, tx_data, &tx_opt);
#endif
        rt_mutex_release(&netc->lock);

        if (result == kStatus_Busy)
        {
            rt_thread_mdelay(1);
        }
    } while (result == kStatus_Busy);

    if (result != kStatus_Success)
    {
        rt_free(tx_data);
#if NETC_USE_SWT
        LOG_E("SWT_SendFrame failed: %d", result);
#else
        LOG_E("EP_SendFrame failed: %d", result);
#endif
        return -RT_ERROR;
    }
    if (result == kStatus_Success)
    {
        return _netc_wait_tx_complete(netc);
    }

    return RT_EOK;
}

static struct pbuf *rt_imxrt_netc_rx(rt_device_t dev)
{
    struct rt_imxrt_netc *netc = &imxrt_netc_device;
    struct pbuf *p = RT_NULL;
#if NETC_RX_ZERO_COPY
    netc_buffer_struct_t rx_buffers[NETC_MAX_BUFFERS_PER_FRAME];
    netc_frame_struct_t frame;
    status_t result;
#else
    uint32_t length = 0U;
    status_t result;
#endif

    RT_UNUSED(dev);

    if (!netc->hw_inited)
    {
        return RT_NULL;
    }

    rt_mutex_take(&netc->lock, RT_WAITING_FOREVER);

#if NETC_RX_ZERO_COPY
    frame.buffArray = rx_buffers;
    frame.length = NETC_MAX_BUFFERS_PER_FRAME;

#if NETC_USE_SWT
    result = SWT_ReceiveFrame(&netc->swt_handle, &frame, RT_NULL);
#else
    result = EP_ReceiveFrame(&netc->ep_handle, NETC_RING_ID, &frame, RT_NULL);
#endif
    if (result == kStatus_Success)
    {
        p = _netc_rx_frame_to_pbufs(netc, &frame);
    }
#if NETC_USE_SWT
    else if ((result == kStatus_NETC_RxFrameError) ||
             (result == kStatus_NETC_RxTsrResp))
    {
        (void)SWT_ReceiveFrameCopy(&netc->swt_handle, RT_NULL, 0U, RT_NULL);
    }
    else if ((result != kStatus_NETC_RxFrameEmpty) &&
             (result != kStatus_NETC_LackOfResource) &&
             (result != kStatus_NETC_RxHRZeroFrame))
    {
        LOG_W("SWT_ReceiveFrame failed: %d", result);
    }
#else
    else if ((result == kStatus_NETC_RxHRNotZeroFrame) ||
             (result == kStatus_NETC_RxTsrResp))
    {
        EP_DropFrame(&netc->ep_handle, &netc->ep_handle.rxBdRing[NETC_RING_ID], NETC_RING_ID);
    }
    else if ((result != kStatus_NETC_RxFrameEmpty) &&
             (result != kStatus_NETC_LackOfResource) &&
             (result != kStatus_NETC_RxFrameError))
    {
        LOG_W("EP_ReceiveFrame failed: %d", result);
    }
#endif
#else
#if NETC_USE_SWT
    result = SWT_GetRxFrameSize(&netc->swt_handle, &length);
#else
    result = EP_GetRxFrameSize(&netc->ep_handle, NETC_RING_ID, &length);
#endif
    if ((result == kStatus_Success) && (length != 0U))
    {
        p = pbuf_alloc(PBUF_RAW, (u16_t)length, PBUF_RAM);
        if (p == RT_NULL)
        {
#if NETC_USE_SWT
            (void)SWT_ReceiveFrameCopy(&netc->swt_handle, RT_NULL, 0U, RT_NULL);
#else
            (void)EP_ReceiveFrameCopy(&netc->ep_handle, NETC_RING_ID, RT_NULL, 0U, RT_NULL);
#endif
            rt_mutex_release(&netc->lock);
            return RT_NULL;
        }

#if NETC_USE_SWT
        result = SWT_ReceiveFrameCopy(&netc->swt_handle, p->payload, length, RT_NULL);
#else
        result = EP_ReceiveFrameCopy(&netc->ep_handle, NETC_RING_ID, p->payload, length, RT_NULL);
#endif
        if (result != kStatus_Success)
        {
            pbuf_free(p);
            p = RT_NULL;
#if NETC_USE_SWT
            LOG_W("SWT_ReceiveFrameCopy failed: %d", result);
#else
            LOG_W("EP_ReceiveFrameCopy failed: %d", result);
#endif
        }
    }
#if NETC_USE_SWT
    else if ((result == kStatus_NETC_RxFrameError) ||
             (result == kStatus_NETC_RxTsrResp))
    {
        (void)SWT_ReceiveFrameCopy(&netc->swt_handle, RT_NULL, 0U, RT_NULL);
    }
#else
    else if ((result == kStatus_NETC_RxFrameError) ||
             (result == kStatus_NETC_RxHRNotZeroFrame) ||
             (result == kStatus_NETC_RxTsrResp))
    {
        (void)EP_ReceiveFrameCopy(&netc->ep_handle, NETC_RING_ID, RT_NULL, 0U, RT_NULL);
    }
#endif
#endif

    rt_mutex_release(&netc->lock);

    return p;
}

static int rt_hw_imxrt_netc_init(void)
{
    rt_err_t state;
    rt_thread_t tid;

    imxrt_netc_device.dev_addr[0] = NETC_DEFAULT_MAC0;
    imxrt_netc_device.dev_addr[1] = NETC_DEFAULT_MAC1;
    imxrt_netc_device.dev_addr[2] = NETC_DEFAULT_MAC2;
    imxrt_netc_device.dev_addr[3] = NETC_DEFAULT_MAC3;
    imxrt_netc_device.dev_addr[4] = NETC_DEFAULT_MAC4;
    imxrt_netc_device.dev_addr[5] = NETC_DEFAULT_MAC5;

    rt_mutex_init(&imxrt_netc_device.lock, "netc", RT_IPC_FLAG_FIFO);
    rt_sem_init(&imxrt_netc_device.tx_isr_sem, "ntx", 0, RT_IPC_FLAG_FIFO);

    imxrt_netc_device.parent.parent.init = rt_imxrt_netc_init;
    imxrt_netc_device.parent.parent.open = rt_imxrt_netc_open;
    imxrt_netc_device.parent.parent.close = rt_imxrt_netc_close;
    imxrt_netc_device.parent.parent.read = rt_imxrt_netc_read;
    imxrt_netc_device.parent.parent.write = rt_imxrt_netc_write;
    imxrt_netc_device.parent.parent.control = rt_imxrt_netc_control;
    imxrt_netc_device.parent.parent.user_data = &imxrt_netc_device;

    imxrt_netc_device.parent.eth_rx = rt_imxrt_netc_rx;
    imxrt_netc_device.parent.eth_tx = rt_imxrt_netc_tx;

    state = _netc_hw_init(&imxrt_netc_device);
    if (state != RT_EOK)
    {
        return state;
    }

    state = eth_device_init(&imxrt_netc_device.parent, "e0");
    if (state != RT_EOK)
    {
        LOG_E("eth_device_init failed: %d", state);
        return state;
    }

    eth_device_linkchange(&imxrt_netc_device.parent, imxrt_netc_device.link_up);

    tid = rt_thread_create("netc",
                           _netc_poll_thread_entry,
                           &imxrt_netc_device,
                           RT_NTCP_THREAD_STACK_SIZE,
                           RT_NTCP_THREAD_PRIORITY,
                           10);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        LOG_W("failed to create NETC poll thread");
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_imxrt_netc_init);

#endif /* RT_USING_LWIP */
