/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-10     Tanek        the first version
 * 2019-5-10      misonyo      add DMA TX and RX function
 * 2020-10-14     wangqiang    use phy device in phy monitor thread
 * 2022-08-29     xjy198903    add 1170 rgmii support
 */

#include <rtthread.h>
#include "board.h"
#include <rtdevice.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include "fsl_enet.h"
#include "fsl_gpio.h"
#include "fsl_cache.h"
#include "fsl_iomuxc.h"
#include "fsl_common.h"

#ifdef RT_USING_LWIP

#include <netif/ethernetif.h>
#include "lwipopts.h"


#define ENET_RXBD_NUM (5)
#define ENET_TXBD_NUM (3)

#define ENET_RXBUFF_SIZE (ENET_FRAME_MAX_FRAMELEN)
#define ENET_TXBUFF_SIZE (ENET_FRAME_MAX_FRAMELEN)

/* debug option */
#define ETH_RX_DUMP
#undef ETH_RX_DUMP
#define ETH_TX_DUMP
#undef ETH_TX_DUMP

#define DBG_ENABLE
#define DBG_SECTION_NAME "[ETH]"
#define DBG_COLOR
#define DBG_LEVEL DBG_INFO
#include <rtdbg.h>

#define RING_ID 0
#define ENET_RING_NUM 1U
#define MAX_ADDR_LEN 6

//#ifdef SOC_IMXRT1170_SERIES

typedef uint8_t rx_buffer_t[RT_ALIGN(ENET_TXBUFF_SIZE, ENET_BUFF_ALIGNMENT)];
typedef uint8_t tx_buffer_t[RT_ALIGN(ENET_TXBUFF_SIZE, ENET_BUFF_ALIGNMENT)];

#ifndef ENET_RXBUFF_NUM
#define ENET_RXBUFF_NUM (ENET_RXBD_NUM * 2)
#endif
//#endif

//#ifdef SOC_IMXRT1170_SERIES
typedef void (*pbuf_free_custom_fn)(struct pbuf *p);

/** A custom pbuf: like a pbuf, but following a function pointer to free it. */
struct pbuf_custom
{
    /** The actual pbuf */
    struct pbuf pbuf;
    /** This function is called when pbuf_free deallocates this pbuf(_custom) */
    pbuf_free_custom_fn custom_free_function;
};

typedef struct rx_pbuf_wrapper
{
    struct pbuf_custom p;      /*!< Pbuf wrapper. Has to be first. */
    void *buffer;              /*!< Original buffer wrapped by p. */
    volatile bool buffer_used; /*!< Wrapped buffer is used by ENET */
} rx_pbuf_wrapper_t;

//#endif
struct rt_imxrt_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;

    enet_handle_t enet_handle;
    ENET_Type *enet_base;
    enet_data_error_stats_t error_statistic;
    rt_uint8_t dev_addr[MAX_ADDR_LEN]; /* hw address   */

    rt_bool_t tx_is_waiting;
    struct rt_semaphore tx_wait;
    struct rt_semaphore buff_wait;

    enet_mii_speed_t speed;
    enet_mii_duplex_t duplex;

//#ifdef SOC_IMXRT1170_SERIES
    enet_rx_bd_struct_t *RxBuffDescrip;
    enet_tx_bd_struct_t *TxBuffDescrip;
    rx_buffer_t *RxDataBuff;
    tx_buffer_t *TxDataBuff;
    rx_pbuf_wrapper_t RxPbufs[ENET_RXBUFF_NUM];
//#endif
};

//#if defined(__ICCARM__) /* IAR Workbench */
//#pragma location = "enet_mem_section"
//ALIGN(ENET_BUFF_ALIGNMENT)
//static enet_tx_bd_struct_t g_txBuffDescrip[ENET_TXBD_NUM];
//
//ALIGN(ENET_BUFF_ALIGNMENT)
//rt_uint8_t g_txDataBuff[ENET_TXBD_NUM][RT_ALIGN(ENET_TXBUFF_SIZE, ENET_BUFF_ALIGNMENT)];
//
//#pragma location = "enet_mem_section"
//ALIGN(ENET_BUFF_ALIGNMENT)
//static enet_rx_bd_struct_t g_rxBuffDescrip[ENET_RXBD_NUM];
//
//ALIGN(ENET_BUFF_ALIGNMENT)
//rt_uint8_t g_rxDataBuff[ENET_RXBD_NUM][RT_ALIGN(ENET_RXBUFF_SIZE, ENET_BUFF_ALIGNMENT)];
//
//#else
AT_NONCACHEABLE_SECTION_ALIGN(static enet_tx_bd_struct_t g_txBuffDescrip[ENET_TXBD_NUM], ENET_BUFF_ALIGNMENT);

rt_align(ENET_BUFF_ALIGNMENT)
rt_uint8_t g_txDataBuff[ENET_TXBD_NUM][RT_ALIGN(ENET_TXBUFF_SIZE, ENET_BUFF_ALIGNMENT)];

AT_NONCACHEABLE_SECTION_ALIGN(static enet_rx_bd_struct_t g_rxBuffDescrip[ENET_RXBD_NUM], ENET_BUFF_ALIGNMENT);
rt_align(ENET_BUFF_ALIGNMENT)
rt_uint8_t g_rxDataBuff[ENET_RXBD_NUM][RT_ALIGN(ENET_RXBUFF_SIZE, ENET_BUFF_ALIGNMENT)];
//#endif


static struct rt_imxrt_eth imxrt_eth_device;

void _enet_rx_callback(struct rt_imxrt_eth *eth)
{
    rt_err_t result;

    ENET_DisableInterrupts(eth->enet_base, kENET_RxFrameInterrupt);

    result = eth_device_ready(&(eth->parent));
    if (result != RT_EOK)
        rt_kprintf("RX err =%d\n", result);
}

void _enet_tx_callback(struct rt_imxrt_eth *eth)
{
    dbg_log(DBG_LOG, "_enet_tx_callback\n");
    if (eth->tx_is_waiting == RT_TRUE)
    {
        eth->tx_is_waiting = RT_FALSE;
        rt_sem_release(&eth->tx_wait);
    }
}

static void _enet_callback(ENET_Type *base,
                           enet_handle_t *handle,
#if FSL_FEATURE_ENET_QUEUE > 1
                           uint32_t ringId,
#endif /* FSL_FEATURE_ENET_QUEUE */
                           enet_event_t event,
                           enet_frame_info_t *frameInfo,
                           void *userData)
{
    switch (event)
    {
    case kENET_RxEvent:

        _enet_rx_callback((struct rt_imxrt_eth *)userData);
        break;

    case kENET_TxEvent:

        _enet_tx_callback((struct rt_imxrt_eth *)userData);
        break;

    case kENET_ErrEvent:
        dbg_log(DBG_LOG, "kENET_ErrEvent\n");
        break;

    case kENET_WakeUpEvent:
        dbg_log(DBG_LOG, "kENET_WakeUpEvent\n");
        break;

    case kENET_TimeStampEvent:
        dbg_log(DBG_LOG, "kENET_TimeStampEvent\n");
        break;

    case kENET_TimeStampAvailEvent:
        dbg_log(DBG_LOG, "kENET_TimeStampAvailEvent \n");
        break;

    default:
        dbg_log(DBG_LOG, "unknow error\n");
        break;
    }
}

static void _enet_clk_init(void)
{

#ifdef SOC_IMXRT1170_SERIES
#ifdef PHY_USING_RTL8211F
    const clock_sys_pll1_config_t sysPll1Config = {
        .pllDiv2En = true,
    };
    CLOCK_InitSysPll1(&sysPll1Config);

    clock_root_config_t rootCfg = {.mux = 4, .div = 4}; /* Generate 125M root clock. */
    CLOCK_SetRootClock(kCLOCK_Root_Enet2, &rootCfg);
    IOMUXC_GPR->GPR5 |= IOMUXC_GPR_GPR5_ENET1G_RGMII_EN_MASK; /* bit1:iomuxc_gpr_enet_clk_dir
                                                                 bit0:GPR_ENET_TX_CLK_SEL(internal or OSC) */
#else
    const clock_sys_pll1_config_t sysPll1Config = {
        .pllDiv2En = true,
    };
    CLOCK_InitSysPll1(&sysPll1Config);
    clock_root_config_t rootCfg = {.mux = 4, .div = 10}; /* Generate 50M root clock. */
    CLOCK_SetRootClock(kCLOCK_Root_Enet1, &rootCfg);

    /* Select syspll2pfd3, 528*18/24 = 396M */
    CLOCK_InitPfd(kCLOCK_PllSys2, kCLOCK_Pfd3, 24);
    rootCfg.mux = 7;
    rootCfg.div = 2;
    CLOCK_SetRootClock(kCLOCK_Root_Bus, &rootCfg); /* Generate 198M bus clock. */
    IOMUXC_GPR->GPR4 |= 0x3;
#endif
#else
//    const clock_enet_pll_config_t config = {.enableClkOutput = true, .enableClkOutput25M = false, .loopDivider = 1};
//    CLOCK_InitEnetPll(&config);
//
//    IOMUXC_EnableMode(IOMUXC_GPR, kIOMUXC_GPR_ENET1TxClkOutputDir, true);
//    IOMUXC_GPR->GPR1 |= 1 << 23;
        /* Set 50MHz output clock required by PHY. */
    const clock_enet_pll_config_t config = {.enableClkOutput = true, .loopDivider = 1};
#if defined(SOC_IMXRT1020_SERIES)
    const clock_enet_pll_config_t config = {.enableClkOutput = true, .enableClkOutput500M = true, .loopDivider = 1};
#endif
    CLOCK_InitEnetPll(&config);

    /* Output 50M clock to PHY. */
    IOMUXC_EnableMode(IOMUXC_GPR, kIOMUXC_GPR_ENET1TxClkOutputDir, true);
#endif
}

//#ifdef SOC_IMXRT1170_SERIES
static void *_enet_rx_alloc(ENET_Type *base, void *userData, uint8_t ringId)
{
    void *buffer = NULL;
    int i;

    // dbg_log(DBG_LOG, "get buff_wait sem in %d\r\n", __LINE__);
    rt_sem_take(&imxrt_eth_device.buff_wait, RT_WAITING_FOREVER);

    for (i = 0; i < ENET_RXBUFF_NUM; i++)
    {
        if (!imxrt_eth_device.RxPbufs[i].buffer_used)
        {
            imxrt_eth_device.RxPbufs[i].buffer_used = true;
            buffer = &imxrt_eth_device.RxDataBuff[i];
            break;
        }
    }

    rt_sem_release(&imxrt_eth_device.buff_wait);
    // dbg_log(DBG_LOG, "release buff_wait sem in %d\r\n", __LINE__);

    return buffer;
}

static void _enet_rx_free(ENET_Type *base, void *buffer, void *userData, uint8_t ringId)
{
    int idx = ((rx_buffer_t *)buffer) - imxrt_eth_device.RxDataBuff;
    if (!((idx >= 0) && (idx < ENET_RXBUFF_NUM)))
    {
        LOG_E("Freed buffer out of range\r\n");
    }

    // dbg_log(DBG_LOG, "get buff_wait sem in %d\r\n", __LINE__);
    rt_sem_take(&imxrt_eth_device.buff_wait, RT_WAITING_FOREVER);
    if (!(imxrt_eth_device.RxPbufs[idx].buffer_used))
    {
        LOG_E("_enet_rx_free: freeing unallocated buffer\r\n");
    }
    imxrt_eth_device.RxPbufs[idx].buffer_used = false;
    rt_sem_release(&imxrt_eth_device.buff_wait);
    // dbg_log(DBG_LOG, "release buff_wait sem in %d\r\n", __LINE__);
}

/**
 * Reclaims RX buffer held by the p after p is no longer used
 * by the application / lwIP.
 */
static void _enet_rx_release(struct pbuf *p)
{
    rx_pbuf_wrapper_t *wrapper = (rx_pbuf_wrapper_t *)p;
    _enet_rx_free(imxrt_eth_device.enet_base, wrapper->buffer, &imxrt_eth_device, 0);
}
//#endif

static void _enet_config(void)
{
    enet_config_t config;
    uint32_t sysClock;

/* prepare the buffer configuration. */
//#ifndef SOC_IMXRT1170_SERIES
//    enet_buffer_config_t buffConfig[] =
//        {
//            ENET_RXBD_NUM,
//            ENET_TXBD_NUM,
//            SDK_SIZEALIGN(ENET_RXBUFF_SIZE, ENET_BUFF_ALIGNMENT),
//            SDK_SIZEALIGN(ENET_TXBUFF_SIZE, ENET_BUFF_ALIGNMENT),
//            &g_rxBuffDescrip[0],
//            &g_txBuffDescrip[0],
//            &g_rxDataBuff[0][0],
//            &g_txDataBuff[0][0],
//        };
//    /* Get default configuration. */
//    /*
//     * config.miiMode = kENET_RmiiMode;
//     * config.miiSpeed = kENET_MiiSpeed100M;
//     * config.miiDuplex = kENET_MiiFullDuplex;
//     * config.rxMaxFrameLen = ENET_FRAME_MAX_FRAMELEN;
//     */
//
//    ENET_GetDefaultConfig(&config);
//    config.ringNum = ENET_RING_NUM;
//    config.miiSpeed = imxrt_eth_device.speed;
//    config.miiDuplex = imxrt_eth_device.duplex;
//
////#ifdef PHY_USING_RTL8211F
////    config.miiMode = kENET_RgmiiMode;
////    EnableIRQ(ENET_1G_MAC0_Tx_Rx_1_IRQn);
////    EnableIRQ(ENET_1G_MAC0_Tx_Rx_2_IRQn);
////#else
////    config.miiMode = kENET_RmiiMode;
////#endif
//
//
//    config.interrupt |= kENET_TxFrameInterrupt | kENET_RxFrameInterrupt;
//    config.callback = _enet_callback;
//
////    ENET_GetDefaultConfig(&config);
//    config.ringNum = ENET_RING_NUM;
////    config.interrupt = kENET_TxFrameInterrupt | kENET_RxFrameInterrupt;
//    config.miiSpeed = imxrt_eth_device.speed;
//    config.miiDuplex = imxrt_eth_device.duplex;
//
//    /* Set SMI to get PHY link status. */
//    sysClock = CLOCK_GetFreq(kCLOCK_IpgClk);
//
//    dbg_log(DBG_LOG, "deinit\n");
//    ENET_Deinit(imxrt_eth_device.enet_base);
//    dbg_log(DBG_LOG, "init\n");
//    ENET_Init(imxrt_eth_device.enet_base, &imxrt_eth_device.enet_handle, &config, &buffConfig[0], &imxrt_eth_device.dev_addr[0], sysClock);
////    dbg_log(DBG_LOG, "set call back\n");
////    ENET_SetCallback(&imxrt_eth_device.enet_handle, _enet_callback, &imxrt_eth_device);
//    dbg_log(DBG_LOG, "active read\n");
//    ENET_ActiveRead(imxrt_eth_device.enet_base);
//#else
    int i;
    enet_buffer_config_t buffConfig[ENET_RING_NUM];
    imxrt_eth_device.RxBuffDescrip = &g_rxBuffDescrip[0];
    imxrt_eth_device.TxBuffDescrip = &g_txBuffDescrip[0];
    imxrt_eth_device.RxDataBuff = &g_rxDataBuff[0];
    imxrt_eth_device.TxDataBuff = &g_txDataBuff[0];
    buffConfig[0].rxBdNumber = ENET_RXBD_NUM;            /* Receive buffer descriptor number. */
    buffConfig[0].txBdNumber = ENET_TXBD_NUM;            /* Transmit buffer descriptor number. */
    buffConfig[0].rxBuffSizeAlign = sizeof(rx_buffer_t); /* Aligned receive data buffer size. */
    buffConfig[0].txBuffSizeAlign = sizeof(tx_buffer_t); /* Aligned transmit data buffer size. */
    buffConfig[0].rxBdStartAddrAlign =
        &(imxrt_eth_device.RxBuffDescrip[0]); /* Aligned receive buffer descriptor start address. */
    buffConfig[0].txBdStartAddrAlign =
        &(imxrt_eth_device.TxBuffDescrip[0]); /* Aligned transmit buffer descriptor start address. */
    buffConfig[0].rxBufferAlign =
        NULL;                                                           /* Receive data buffer start address. NULL when buffers are allocated by callback for RX zero-copy. */
    buffConfig[0].txBufferAlign = &(imxrt_eth_device.TxDataBuff[0][0]); /* Transmit data buffer start address. */
    buffConfig[0].txFrameInfo = NULL;                                   /* Transmit frame information start address. Set only if using zero-copy transmit. */
    buffConfig[0].rxMaintainEnable = true;                              /* Receive buffer cache maintain. */
    buffConfig[0].txMaintainEnable = true;                              /* Transmit buffer cache maintain. */

    /* Get default configuration. */
    /*
     * config.miiMode = kENET_RmiiMode;
     * config.miiSpeed = kENET_MiiSpeed100M;
     * config.miiDuplex = kENET_MiiFullDuplex;
     * config.rxMaxFrameLen = ENET_FRAME_MAX_FRAMELEN;
     */
    ENET_GetDefaultConfig(&config);
    config.ringNum = ENET_RING_NUM;
    config.miiSpeed = imxrt_eth_device.speed;
    config.miiDuplex = imxrt_eth_device.duplex;
#ifdef PHY_USING_RTL8211F
    config.miiMode = kENET_RgmiiMode;
    EnableIRQ(ENET_1G_MAC0_Tx_Rx_1_IRQn);
    EnableIRQ(ENET_1G_MAC0_Tx_Rx_2_IRQn);
#else
    config.miiMode = kENET_RmiiMode;
#endif
    config.rxBuffAlloc = _enet_rx_alloc;
    config.rxBuffFree = _enet_rx_free;
    config.userData = &imxrt_eth_device;
#ifdef SOC_IMXRT1170_SERIES
    /* Set SMI to get PHY link status. */
    sysClock = CLOCK_GetRootClockFreq(kCLOCK_Root_Bus);
#else
   sysClock =  CLOCK_GetFreq(kCLOCK_IpgClk);
#endif
    config.interrupt |= kENET_TxFrameInterrupt | kENET_RxFrameInterrupt | kENET_TxBufferInterrupt | kENET_LateCollisionInterrupt;
    config.callback = _enet_callback;

    for (i = 0; i < ENET_RXBUFF_NUM; i++)
    {
        imxrt_eth_device.RxPbufs[i].p.custom_free_function = _enet_rx_release;
        imxrt_eth_device.RxPbufs[i].buffer = &(imxrt_eth_device.RxDataBuff[i][0]);
        imxrt_eth_device.RxPbufs[i].buffer_used = false;
    }

    // dbg_log(DBG_LOG, "deinit\n");
    // ENET_Deinit(imxrt_eth_device.enet_base);
    dbg_log(DBG_LOG, "init\n");
    ENET_Init(imxrt_eth_device.enet_base, &imxrt_eth_device.enet_handle, &config, &buffConfig[0], &imxrt_eth_device.dev_addr[0], sysClock);
    // dbg_log(DBG_LOG, "set call back\n");
    // ENET_SetCallback(&imxrt_eth_device.enet_handle, _enet_callback, &imxrt_eth_device);
    dbg_log(DBG_LOG, "active read\n");
    ENET_ActiveRead(imxrt_eth_device.enet_base);
//#endif
}

#if defined(ETH_RX_DUMP) || defined(ETH_TX_DUMP)
static void packet_dump(const char *msg, const struct pbuf *p)
{
    const struct pbuf *q;
    rt_uint32_t i, j;
    rt_uint8_t *ptr;

    rt_kprintf("%s %d byte\n", msg, p->tot_len);

    i = 0;
    for (q = p; q != RT_NULL; q = q->next)
    {
        ptr = q->payload;

        for (j = 0; j < q->len; j++)
        {
            if ((i % 8) == 0)
            {
                rt_kprintf("  ");
            }
            if ((i % 16) == 0)
            {
                rt_kprintf("\r\n");
            }
            rt_kprintf("%02x ", *ptr);

            i++;
            ptr++;
        }
    }

    rt_kprintf("\n\n");
}
#else
#define packet_dump(...)
#endif /* dump */

/* initialize the interface */
static rt_err_t rt_imxrt_eth_init(rt_device_t dev)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_init...\n");
    _enet_config();

    return RT_EOK;
}

static rt_err_t rt_imxrt_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_open...\n");
    return RT_EOK;
}

static rt_err_t rt_imxrt_eth_close(rt_device_t dev)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_close...\n");
    return RT_EOK;
}

static rt_ssize_t rt_imxrt_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_read...\n");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_imxrt_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_write...\n");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_imxrt_eth_control(rt_device_t dev, int cmd, void *args)
{
    dbg_log(DBG_LOG, "rt_imxrt_eth_control...\n");
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args)
            rt_memcpy(args, imxrt_eth_device.dev_addr, 6);
        else
            return -RT_ERROR;
        break;

    default:
        break;
    }

    return RT_EOK;
}

static bool _ENET_TxDirtyRingAvailable(enet_tx_dirty_ring_t *txDirtyRing)
{
    return !txDirtyRing->isFull;
}

static uint16_t _ENET_IncreaseIndex(uint16_t index, uint16_t max)
{
    assert(index < max);

    /* Increase the index. */
    index++;
    if (index >= max)
    {
        index = 0;
    }
    return index;
}

static void _ENET_ActiveSendRing(ENET_Type *base, uint8_t ringId)
{
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_INSTANCE_QUEUEn(base));

    volatile uint32_t *txDesActive = NULL;

    /* Ensure previous data update is completed with Data Synchronization Barrier before activing Tx BD. */
    __DSB();

    switch (ringId)
    {
    case 0:
        txDesActive = &(base->TDAR);
        break;
#if FSL_FEATURE_ENET_QUEUE > 1
    case 1:
        txDesActive = &(base->TDAR1);
        break;
    case 2:
        txDesActive = &(base->TDAR2);
        break;
#endif /* FSL_FEATURE_ENET_QUEUE > 1 */
    default:
        txDesActive = &(base->TDAR);
        break;
    }

#if defined(FSL_FEATURE_ENET_HAS_ERRATA_007885) && FSL_FEATURE_ENET_HAS_ERRATA_007885
    /* There is a TDAR race condition for mutliQ when the software sets TDAR
     * and the UDMA clears TDAR simultaneously or in a small window (2-4 cycles).
     * This will cause the udma_tx and udma_tx_arbiter state machines to hang.
     * Software workaround: introduces a delay by reading the relevant ENET_TDARn_TDAR 4 times
     */
    for (uint8_t i = 0; i < 4U; i++)
    {
        if (*txDesActive == 0U)
        {
            break;
        }
    }
#endif

    /* Write to active tx descriptor */
    *txDesActive = 0;
}

static status_t _ENET_SendFrame(ENET_Type *base,
                                enet_handle_t *handle,
                                const uint8_t *data,
                                uint32_t length,
                                uint8_t ringId,
                                bool tsFlag,
                                void *context)
{
    assert(handle != NULL);
    assert(data != NULL);
    assert(FSL_FEATURE_ENET_INSTANCE_QUEUEn(base) != -1);
    assert(ringId < (uint8_t)FSL_FEATURE_ENET_INSTANCE_QUEUEn(base));

    volatile enet_tx_bd_struct_t *curBuffDescrip;
    enet_tx_bd_ring_t *txBdRing = &handle->txBdRing[ringId];
    enet_tx_dirty_ring_t *txDirtyRing = &handle->txDirtyRing[ringId];
    enet_frame_info_t *txDirty = NULL;
    uint32_t len = 0;
    uint32_t sizeleft = 0;
    uint32_t address;
    status_t result = kStatus_Success;
    uint32_t src;
    uint32_t configVal;
    bool isReturn = false;
    uint32_t primask;

    /* Check the frame length. */
    if (length > ENET_FRAME_TX_LEN_LIMITATION(base))
    {
        result = kStatus_ENET_TxFrameOverLen;
    }
    else
    {
        /* Check if the transmit buffer is ready. */
        curBuffDescrip = txBdRing->txBdBase + txBdRing->txGenIdx;
        if (0U != (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_TX_READY_MASK))
        {
            result = kStatus_ENET_TxFrameBusy;
        }
        /* Check txDirtyRing if need frameinfo in tx interrupt callback. */
        else if ((handle->txReclaimEnable[ringId]) && !_ENET_TxDirtyRingAvailable(txDirtyRing))
        {
            result = kStatus_ENET_TxFrameBusy;
        }
        else
        {
            /* One transmit buffer is enough for one frame. */
            if (handle->txBuffSizeAlign[ringId] >= length)
            {
                /* Copy data to the buffer for uDMA transfer. */
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                address = MEMORY_ConvertMemoryMapAddress((uint32_t)curBuffDescrip->buffer, kMEMORY_DMA2Local);
#else
                address = (uint32_t)curBuffDescrip->buffer;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                pbuf_copy_partial((const struct pbuf *)data, (void *)address, length, 0);
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
                if (handle->txMaintainEnable[ringId])
                {
                    DCACHE_CleanByRange(address, length);
                }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */
                /* Set data length. */
                curBuffDescrip->length = (uint16_t)length;
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
                /* For enable the timestamp. */
                if (tsFlag)
                {
                    curBuffDescrip->controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK;
                }
                else
                {
                    curBuffDescrip->controlExtend1 &= (uint16_t)(~ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK);
                }

#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */
                curBuffDescrip->control |= (ENET_BUFFDESCRIPTOR_TX_READY_MASK | ENET_BUFFDESCRIPTOR_TX_LAST_MASK);

                /* Increase the buffer descriptor address. */
                txBdRing->txGenIdx = _ENET_IncreaseIndex(txBdRing->txGenIdx, txBdRing->txRingLen);

                /* Add context to frame info ring */
                if (handle->txReclaimEnable[ringId])
                {
                    txDirty = txDirtyRing->txDirtyBase + txDirtyRing->txGenIdx;
                    txDirty->context = context;
                    txDirtyRing->txGenIdx = _ENET_IncreaseIndex(txDirtyRing->txGenIdx, txDirtyRing->txRingLen);
                    if (txDirtyRing->txGenIdx == txDirtyRing->txConsumIdx)
                    {
                        txDirtyRing->isFull = true;
                    }
                    primask = DisableGlobalIRQ();
                    txBdRing->txDescUsed++;
                    EnableGlobalIRQ(primask);
                }

                /* Active the transmit buffer descriptor. */
                _ENET_ActiveSendRing(base, ringId);
            }
            else
            {
                /* One frame requires more than one transmit buffers. */
                do
                {
#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
                    /* For enable the timestamp. */
                    if (tsFlag)
                    {
                        curBuffDescrip->controlExtend1 |= ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK;
                    }
                    else
                    {
                        curBuffDescrip->controlExtend1 &= (uint16_t)(~ENET_BUFFDESCRIPTOR_TX_TIMESTAMP_MASK);
                    }
#endif /* ENET_ENHANCEDBUFFERDESCRIPTOR_MODE */

                    /* Update the size left to be transmit. */
                    sizeleft = length - len;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
                    address = MEMORY_ConvertMemoryMapAddress((uint32_t)curBuffDescrip->buffer, kMEMORY_DMA2Local);
#else
                    address = (uint32_t)curBuffDescrip->buffer;
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
                    src = (uint32_t)data + len;

                    /* Increase the current software index of BD */
                    txBdRing->txGenIdx = _ENET_IncreaseIndex(txBdRing->txGenIdx, txBdRing->txRingLen);

                    if (sizeleft > handle->txBuffSizeAlign[ringId])
                    {
                        /* Data copy. */
                        (void)memcpy((void *)(uint32_t *)address, (void *)(uint32_t *)src,
                                     handle->txBuffSizeAlign[ringId]);
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
                        if (handle->txMaintainEnable[ringId])
                        {
                            /* Add the cache clean maintain. */
                            DCACHE_CleanByRange(address, handle->txBuffSizeAlign[ringId]);
                        }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */
                        /* Data length update. */
                        curBuffDescrip->length = handle->txBuffSizeAlign[ringId];
                        len += handle->txBuffSizeAlign[ringId];
                        /* Sets the control flag. */
                        configVal = (uint32_t)curBuffDescrip->control;
                        configVal &= ~ENET_BUFFDESCRIPTOR_TX_LAST_MASK;
                        configVal |= ENET_BUFFDESCRIPTOR_TX_READY_MASK;
                        curBuffDescrip->control = (uint16_t)configVal;

                        if (handle->txReclaimEnable[ringId])
                        {
                            primask = DisableGlobalIRQ();
                            txBdRing->txDescUsed++;
                            EnableGlobalIRQ(primask);
                        }

                        /* Active the transmit buffer descriptor*/
                        _ENET_ActiveSendRing(base, ringId);
                    }
                    else
                    {
                        (void)memcpy((void *)(uint32_t *)address, (void *)(uint32_t *)src, sizeleft);
#if defined(FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL) && FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL
                        if (handle->txMaintainEnable[ringId])
                        {
                            /* Add the cache clean maintain. */
                            DCACHE_CleanByRange(address, sizeleft);
                        }
#endif /* FSL_SDK_ENABLE_DRIVER_CACHE_CONTROL */
                        curBuffDescrip->length = (uint16_t)sizeleft;
                        /* Set Last buffer wrap flag. */
                        curBuffDescrip->control |= ENET_BUFFDESCRIPTOR_TX_READY_MASK | ENET_BUFFDESCRIPTOR_TX_LAST_MASK;

                        if (handle->txReclaimEnable[ringId])
                        {
                            /* Add context to frame info ring */
                            txDirty = txDirtyRing->txDirtyBase + txDirtyRing->txGenIdx;
                            txDirty->context = context;
                            txDirtyRing->txGenIdx = _ENET_IncreaseIndex(txDirtyRing->txGenIdx, txDirtyRing->txRingLen);
                            if (txDirtyRing->txGenIdx == txDirtyRing->txConsumIdx)
                            {
                                txDirtyRing->isFull = true;
                            }
                            primask = DisableGlobalIRQ();
                            txBdRing->txDescUsed++;
                            EnableGlobalIRQ(primask);
                        }

                        /* Active the transmit buffer descriptor. */
                        _ENET_ActiveSendRing(base, ringId);
                        isReturn = true;
                        break;
                    }
                    /* Update the buffer descriptor address. */
                    curBuffDescrip = txBdRing->txBdBase + txBdRing->txGenIdx;
                } while (0U == (curBuffDescrip->control & ENET_BUFFDESCRIPTOR_TX_READY_MASK));

                if (isReturn == false)
                {
                    result = kStatus_ENET_TxFrameBusy;
                }
            }
        }
    }
    return result;
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_imxrt_eth_tx(rt_device_t dev, struct pbuf *p)
{
    rt_err_t result = RT_EOK;
    enet_handle_t *enet_handle = &imxrt_eth_device.enet_handle;

    RT_ASSERT(p != NULL);
    RT_ASSERT(enet_handle != RT_NULL);

    dbg_log(DBG_LOG, "rt_imxrt_eth_tx: %d\n", p->len);

#ifdef ETH_TX_DUMP
    packet_dump("send", p);
#endif

    do
    {
        result = _ENET_SendFrame(imxrt_eth_device.enet_base, enet_handle, (const uint8_t *)p, p->tot_len, RING_ID, false, NULL);

        if (result == kStatus_ENET_TxFrameBusy)
        {
            imxrt_eth_device.tx_is_waiting = RT_TRUE;
            rt_sem_take(&imxrt_eth_device.tx_wait, RT_WAITING_FOREVER);
        }

    } while (result == kStatus_ENET_TxFrameBusy);

    return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_imxrt_eth_rx(rt_device_t dev)
{
    uint32_t length = 0;
    status_t status;

    struct pbuf *p = RT_NULL;
    enet_handle_t *enet_handle = &imxrt_eth_device.enet_handle;
    ENET_Type *enet_base = imxrt_eth_device.enet_base;
    enet_data_error_stats_t *error_statistic = &imxrt_eth_device.error_statistic;

/* Get the Frame size */
    status = ENET_GetRxFrameSize(enet_handle, &length, RING_ID);

    /* Call ENET_ReadFrame when there is a received frame. */
    if (length != 0)
    {
        /* Received valid frame. Deliver the rx buffer with the size equal to length. */
        p = pbuf_alloc(PBUF_RAW, length, PBUF_POOL);

        if (p != NULL)
        {
            status = ENET_ReadFrame(enet_base, enet_handle, p->payload, length, RING_ID, NULL);

            if (status == kStatus_Success)
            {
#ifdef ETH_RX_DUMP
                packet_dump("recv", p);
#endif
                return p;
            }
            else
            {
                dbg_log(DBG_LOG, " A frame read failed\n");
                pbuf_free(p);
            }
        }
        else
        {
            dbg_log(DBG_LOG, " pbuf_alloc faild\n");
        }
    }
    else if (status == kStatus_ENET_RxFrameError)
    {
        dbg_log(DBG_WARNING, "ENET_GetRxFrameSize: kStatus_ENET_RxFrameError\n");
        /* Update the received buffer when error happened. */

        /* Get the error information of the received g_frame. */
        ENET_GetRxErrBeforeReadFrame(enet_handle, error_statistic, RING_ID);
        /* update the receive buffer. */
        ENET_ReadFrame(enet_base, enet_handle, NULL, 0, RING_ID, NULL);
    }

    ENET_EnableInterrupts(enet_base, kENET_RxFrameInterrupt);
    return NULL;
}

#ifdef BSP_USING_PHY
static struct rt_phy_device *phy_dev = RT_NULL;
static void phy_monitor_thread_entry(void *parameter)
{
    rt_uint32_t speed;
    rt_uint32_t duplex;
    rt_bool_t link = RT_FALSE;

#ifdef SOC_IMXRT1170_SERIES
#ifdef PHY_USING_RTL8211F
    phy_dev = (struct rt_phy_device *)rt_device_find("rtl8211f");
    if ((RT_NULL == phy_dev) || (RT_NULL == phy_dev->ops))
    {
        // TODO print warning information
        LOG_E("Can not find phy device called \"rtl8211f\"");
        return;
    }
#else
    phy_dev = (struct rt_phy_device *)rt_device_find("ksz8081");
    if ((RT_NULL == phy_dev) || (RT_NULL == phy_dev->ops))
    {
        // TODO print warning information
        LOG_E("Can not find phy device called \"ksz8081\"");
        return;
    }
#endif
#else
    phy_dev = (struct rt_phy_device *)rt_device_find("ksz8081");
    if ((RT_NULL == phy_dev) || (RT_NULL == phy_dev->ops))
    {
        // TODO print warning information
        LOG_E("Can not find phy device called \"rtt-phy\"");
        return;
    }
#endif

    if (RT_NULL == phy_dev->ops->init)
    {
        LOG_E("phy driver error!");
        return;
    }
#ifdef SOC_IMXRT1170_SERIES
#ifdef PHY_USING_RTL8211F
    rt_phy_status status = phy_dev->ops->init(imxrt_eth_device.enet_base, PHY_RTL8211F_ADDRESS, CLOCK_GetRootClockFreq(kCLOCK_Root_Bus));
#else
    rt_phy_status status = phy_dev->ops->init(imxrt_eth_device.enet_base, PHY_KSZ8081_ADDRESS, CLOCK_GetRootClockFreq(kCLOCK_Root_Bus));
#endif
#else
    rt_phy_status status = phy_dev->ops->init(imxrt_eth_device.enet_base, PHY_KSZ8081_ADDRESS, CLOCK_GetFreq(kCLOCK_IpgClk));
#endif
    if (PHY_STATUS_OK != status)
    {
        LOG_E("Phy device initialize unsuccessful!\n");
        return;
    }
    LOG_I("Phy device initialize successfully!\n");
    while (1)
    {
        rt_bool_t new_link = RT_FALSE;
        rt_phy_status status = phy_dev->ops->get_link_status(&new_link);

        if ((PHY_STATUS_OK == status) && (link != new_link))
        {
            link = new_link;

            if (link) // link up
            {
                phy_dev->ops->get_link_speed_duplex(&speed, &duplex);

                if (PHY_SPEED_10M == speed)
                {
                    dbg_log(DBG_LOG, "10M\n");
                }
                else if (PHY_SPEED_100M == speed)
                {
                    dbg_log(DBG_LOG, "100M\n");
                }
                else
                {
                    dbg_log(DBG_LOG, "1000M\n");
                }

                if (PHY_HALF_DUPLEX == duplex)
                {
                    dbg_log(DBG_LOG, "half dumplex\n");
                }
                else
                {
                    dbg_log(DBG_LOG, "full dumplex\n");
                }

                if ((imxrt_eth_device.speed != (enet_mii_speed_t)speed) || (imxrt_eth_device.duplex != (enet_mii_duplex_t)duplex))
                {
                    imxrt_eth_device.speed = (enet_mii_speed_t)speed;
                    imxrt_eth_device.duplex = (enet_mii_duplex_t)duplex;

                    dbg_log(DBG_LOG, "link up, and update eth mode.\n");
                    rt_imxrt_eth_init((rt_device_t)&imxrt_eth_device);
                }
                else
                {
                    dbg_log(DBG_LOG, "link up, eth not need re-config.\n");
                }
                dbg_log(DBG_LOG, "link up.\n");
                eth_device_linkchange(&imxrt_eth_device.parent, RT_TRUE);
            }
            else
            {
                dbg_log(DBG_LOG, "link down.\n");
                eth_device_linkchange(&imxrt_eth_device.parent, RT_FALSE);
            }
        }

        rt_thread_delay(RT_TICK_PER_SECOND * 2);
//        rt_thread_mdelay(300);
    }
}
#endif

static int rt_hw_imxrt_eth_init(void)
{
    rt_err_t state;

    _enet_clk_init();

#ifdef PHY_USING_RTL8211F
    /* NXP (Freescale) MAC OUI */
    imxrt_eth_device.dev_addr[0] = 0x54;
    imxrt_eth_device.dev_addr[1] = 0x27;
    imxrt_eth_device.dev_addr[2] = 0x8d;
    /* generate MAC addr from 96bit unique ID (only for test). */
    imxrt_eth_device.dev_addr[3] = 0x11;
    imxrt_eth_device.dev_addr[4] = 0x22;
    imxrt_eth_device.dev_addr[5] = 0x33;

    imxrt_eth_device.speed = kENET_MiiSpeed100M;//Ҫ֧��ǧ�ף�ֱ�ӽ���ֵ��ΪkENET_MiiSpeed1000M
    imxrt_eth_device.duplex = kENET_MiiFullDuplex;

    imxrt_eth_device.enet_base = ENET_1G;
#else
    /* NXP (Freescale) MAC OUI */
    imxrt_eth_device.dev_addr[0] = 0x54;
    imxrt_eth_device.dev_addr[1] = 0x27;
    imxrt_eth_device.dev_addr[2] = 0x8d;
    /* generate MAC addr from 96bit unique ID (only for test). */
    imxrt_eth_device.dev_addr[3] = 0x00;
    imxrt_eth_device.dev_addr[4] = 0x00;
    imxrt_eth_device.dev_addr[5] = 0x00;

    imxrt_eth_device.speed = kENET_MiiSpeed100M;
    imxrt_eth_device.duplex = kENET_MiiFullDuplex;

    imxrt_eth_device.enet_base = ENET;
#endif
    imxrt_eth_device.parent.parent.init = rt_imxrt_eth_init;
    imxrt_eth_device.parent.parent.open = rt_imxrt_eth_open;
    imxrt_eth_device.parent.parent.close = rt_imxrt_eth_close;
    imxrt_eth_device.parent.parent.read = rt_imxrt_eth_read;
    imxrt_eth_device.parent.parent.write = rt_imxrt_eth_write;
    imxrt_eth_device.parent.parent.control = rt_imxrt_eth_control;
    imxrt_eth_device.parent.parent.user_data = RT_NULL;

    imxrt_eth_device.parent.eth_rx = rt_imxrt_eth_rx;
    imxrt_eth_device.parent.eth_tx = rt_imxrt_eth_tx;

    dbg_log(DBG_LOG, "sem init: tx_wait\r\n");
    /* init tx semaphore */
    rt_sem_init(&imxrt_eth_device.tx_wait, "tx_wait", 0, RT_IPC_FLAG_FIFO);

    dbg_log(DBG_LOG, "sem init: buff_wait\r\n");
    /* init tx semaphore */
    rt_sem_init(&imxrt_eth_device.buff_wait, "buff_wait", 1, RT_IPC_FLAG_FIFO);

    /* register eth device */
    dbg_log(DBG_LOG, "eth_device_init start\r\n");
    state = eth_device_init(&(imxrt_eth_device.parent), "e0");
    if (RT_EOK == state)
    {
        dbg_log(DBG_LOG, "eth_device_init success\r\n");
    }
    else
    {
        dbg_log(DBG_LOG, "eth_device_init faild: %d\r\n", state);
    }

    eth_device_linkchange(&imxrt_eth_device.parent, RT_FALSE);

    /* start phy monitor */
    {
#ifdef BSP_USING_PHY
        rt_thread_t tid;
        tid = rt_thread_create("phy",
                               phy_monitor_thread_entry,
                               RT_NULL,
                               4096,
                               /*RT_THREAD_PRIORITY_MAX - 2,*/
                               15,
                               2);
        if (tid != RT_NULL)
            rt_thread_startup(tid);
#endif
    }

    return state;
}
INIT_DEVICE_EXPORT(rt_hw_imxrt_eth_init);
#endif

#if defined(RT_USING_FINSH) && defined(RT_USING_PHY)
#include <finsh.h>

void phy_read(rt_uint32_t phy_reg)
{
    rt_uint32_t data;

    rt_phy_status status = phy_dev->ops->read(phy_reg, &data);
    if (PHY_STATUS_OK == status)
    {
        rt_kprintf("PHY_Read: %02X --> %08X", phy_reg, data);
    }
    else
    {
        rt_kprintf("PHY_Read: %02X --> faild", phy_reg);
    }
}

void phy_write(rt_uint32_t phy_reg, rt_uint32_t data)
{
    rt_phy_status status = phy_dev->ops->write(phy_reg, data);
    if (PHY_STATUS_OK == status)
    {
        rt_kprintf("PHY_Write: %02X --> %08X\n", phy_reg, data);
    }
    else
    {
        rt_kprintf("PHY_Write: %02X --> faild\n", phy_reg);
    }
}

void phy_dump(void)
{
    rt_uint32_t data;
    rt_phy_status status;

    int i;
    for (i = 0; i < 32; i++)
    {
        status = phy_dev->ops->read(i, &data);
        if (PHY_STATUS_OK != status)
        {
            rt_kprintf("phy_dump: %02X --> faild", i);
            break;
        }

        if (i % 8 == 7)
        {
            rt_kprintf("%02X --> %08X ", i, data);
        }
        else
        {
            rt_kprintf("%02X --> %08X\n", i, data);
        }
    }
}
#endif

#if defined(RT_USING_FINSH) && defined(RT_USING_LWIP)
void enet_reg_dump(void)
{
    ENET_Type *enet_base = imxrt_eth_device.enet_base;

#define DUMP_REG(__REG) \
    rt_kprintf("%s(%08X): %08X\n", #__REG, (uint32_t)&enet_base->__REG, enet_base->__REG)

    DUMP_REG(EIR);
    DUMP_REG(EIMR);
    DUMP_REG(RDAR);
    DUMP_REG(TDAR);
    DUMP_REG(ECR);
    DUMP_REG(MMFR);
    DUMP_REG(MSCR);
    DUMP_REG(MIBC);
    DUMP_REG(RCR);
    DUMP_REG(TCR);
    DUMP_REG(PALR);
    DUMP_REG(PAUR);
    DUMP_REG(OPD);
    DUMP_REG(TXIC);
    DUMP_REG(RXIC);
    DUMP_REG(IAUR);
    DUMP_REG(IALR);
    DUMP_REG(GAUR);
    DUMP_REG(GALR);
    DUMP_REG(TFWR);
    DUMP_REG(RDSR);
    DUMP_REG(TDSR);
    DUMP_REG(MRBR);
    DUMP_REG(RSFL);
    DUMP_REG(RSEM);
    DUMP_REG(RAEM);
    DUMP_REG(RAFL);
    DUMP_REG(TSEM);
    DUMP_REG(TAEM);
    DUMP_REG(TAFL);
    DUMP_REG(TIPG);
    DUMP_REG(FTRL);
    DUMP_REG(TACC);
    DUMP_REG(RACC);
    // DUMP_REG(RMON_T_DROP);
    DUMP_REG(RMON_T_PACKETS);
    DUMP_REG(RMON_T_BC_PKT);
    DUMP_REG(RMON_T_MC_PKT);
    DUMP_REG(RMON_T_CRC_ALIGN);
    DUMP_REG(RMON_T_UNDERSIZE);
    DUMP_REG(RMON_T_OVERSIZE);
    DUMP_REG(RMON_T_FRAG);
    DUMP_REG(RMON_T_JAB);
    DUMP_REG(RMON_T_COL);
    DUMP_REG(RMON_T_P64);
    DUMP_REG(RMON_T_P65TO127);
    DUMP_REG(RMON_T_P128TO255);
    DUMP_REG(RMON_T_P256TO511);
    DUMP_REG(RMON_T_P512TO1023);
    DUMP_REG(RMON_T_P1024TO2047);
    DUMP_REG(RMON_T_P_GTE2048);
    DUMP_REG(RMON_T_OCTETS);
//    DUMP_REG(IEEE_T_DROP);
    DUMP_REG(IEEE_T_FRAME_OK);
    DUMP_REG(IEEE_T_1COL);
    DUMP_REG(IEEE_T_MCOL);
    DUMP_REG(IEEE_T_DEF);
    DUMP_REG(IEEE_T_LCOL);
    DUMP_REG(IEEE_T_EXCOL);
    DUMP_REG(IEEE_T_MACERR);
    DUMP_REG(IEEE_T_CSERR);
    DUMP_REG(IEEE_T_SQE);
    DUMP_REG(IEEE_T_FDXFC);
    DUMP_REG(IEEE_T_OCTETS_OK);
    DUMP_REG(RMON_R_PACKETS);
    DUMP_REG(RMON_R_BC_PKT);
    DUMP_REG(RMON_R_MC_PKT);
    DUMP_REG(RMON_R_CRC_ALIGN);
    DUMP_REG(RMON_R_UNDERSIZE);
    DUMP_REG(RMON_R_OVERSIZE);
    DUMP_REG(RMON_R_FRAG);
    DUMP_REG(RMON_R_JAB);
    // DUMP_REG(RMON_R_RESVD_0);
    DUMP_REG(RMON_R_P64);
    DUMP_REG(RMON_R_P65TO127);
    DUMP_REG(RMON_R_P128TO255);
    DUMP_REG(RMON_R_P256TO511);
    DUMP_REG(RMON_R_P512TO1023);
    DUMP_REG(RMON_R_P1024TO2047);
    DUMP_REG(RMON_R_P_GTE2048);
    DUMP_REG(RMON_R_OCTETS);
    DUMP_REG(IEEE_R_DROP);
    DUMP_REG(IEEE_R_FRAME_OK);
    DUMP_REG(IEEE_R_CRC);
    DUMP_REG(IEEE_R_ALIGN);
    DUMP_REG(IEEE_R_MACERR);
    DUMP_REG(IEEE_R_FDXFC);
    DUMP_REG(IEEE_R_OCTETS_OK);
    DUMP_REG(ATCR);
    DUMP_REG(ATVR);
    DUMP_REG(ATOFF);
    DUMP_REG(ATPER);
    DUMP_REG(ATCOR);
    DUMP_REG(ATINC);
    DUMP_REG(ATSTMP);
    DUMP_REG(TGSR);
}

void enet_nvic_tog(void)
{
    NVIC_SetPendingIRQ(ENET_IRQn);
}

void enet_rx_stat(void)
{
    enet_data_error_stats_t *error_statistic = &imxrt_eth_device.error_statistic;

#define DUMP_STAT(__VAR) \
    rt_kprintf("%-25s: %08X\n", #__VAR, error_statistic->__VAR);

    DUMP_STAT(statsRxLenGreaterErr);
    DUMP_STAT(statsRxAlignErr);
    DUMP_STAT(statsRxFcsErr);
    DUMP_STAT(statsRxOverRunErr);
    DUMP_STAT(statsRxTruncateErr);

#ifdef ENET_ENHANCEDBUFFERDESCRIPTOR_MODE
    DUMP_STAT(statsRxProtocolChecksumErr);
    DUMP_STAT(statsRxIpHeadChecksumErr);
    DUMP_STAT(statsRxMacErr);
    DUMP_STAT(statsRxPhyErr);
    DUMP_STAT(statsRxCollisionErr);
    DUMP_STAT(statsTxErr);
    DUMP_STAT(statsTxFrameErr);
    DUMP_STAT(statsTxOverFlowErr);
    DUMP_STAT(statsTxLateCollisionErr);
    DUMP_STAT(statsTxExcessCollisionErr);
    DUMP_STAT(statsTxUnderFlowErr);
    DUMP_STAT(statsTxTsErr);
#endif
}

void enet_buf_info(void)
{
    int i = 0;
    for (i = 0; i < ENET_RXBD_NUM; i++)
    {
        rt_kprintf("%d: length: %-8d, control: %04X, buffer:%p\n",
                   i,
                   g_rxBuffDescrip[i].length,
                   g_rxBuffDescrip[i].control,
                   g_rxBuffDescrip[i].buffer);
    }

    for (i = 0; i < ENET_TXBD_NUM; i++)
    {
        rt_kprintf("%d: length: %-8d, control: %04X, buffer:%p\n",
                   i,
                   g_txBuffDescrip[i].length,
                   g_txBuffDescrip[i].control,
                   g_txBuffDescrip[i].buffer);
    }
}

FINSH_FUNCTION_EXPORT(phy_read, read phy register);
FINSH_FUNCTION_EXPORT(phy_write, write phy register);
FINSH_FUNCTION_EXPORT(phy_dump, dump phy registers);
FINSH_FUNCTION_EXPORT(enet_reg_dump, dump enet registers);
FINSH_FUNCTION_EXPORT(enet_nvic_tog, toggle enet nvic pendding bit);
FINSH_FUNCTION_EXPORT(enet_rx_stat, dump enet rx statistic);
FINSH_FUNCTION_EXPORT(enet_buf_info, dump enet tx and tx buffer descripter);

#endif
