/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "drv_eth.h"

#if defined(BSP_USING_ETH)

#include <netif/ethernetif.h>
#include <lwipopts.h>
#include "drv_irq.h"
#include "board_config.h"

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
//#define DRV_DEBUG
#define LOG_TAG                         "drv.eth"
#include <drv_log.h>

#define MAX_ADDR_LEN                    6

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
struct hc32_eth
{
    /* inherit from ethernet device */
    struct eth_device       parent;
#if !(defined(PHY_USING_INTERRUPT_MODE) && defined(ETH_USING_INTERFACE_RMII))
    rt_timer_t              poll_link_timer;
#endif
    /* interface address info, hw address */
    rt_uint8_t              dev_addr[MAX_ADDR_LEN];
    /* ETH_Speed */
    rt_uint32_t             eth_speed;
    /* ETH_Duplex_Mode */
    rt_uint32_t             eth_mode;
    /* eth irq */
    struct hc32_irq_config  irq_config;
    func_ptr_t              irq_callback;
};

/* eth phy status */
enum
{
    ETH_PHY_LINK        = 0x01U,
    ETH_PHY_100M        = 0x02U,
    ETH_PHY_FULL_DUPLEX = 0x04U,
};

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern rt_err_t rt_hw_eth_board_init(CM_ETH_TypeDef *CM_ETHx);
extern rt_err_t rt_hw_eth_phy_reset(CM_ETH_TypeDef *CM_ETHx);

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void eth_global_irq_handle(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static stc_eth_handle_t EthHandle;
/* Ethernet Tx,Rx DMA Descriptor */
static stc_eth_dma_desc_t *EthDmaTxDscrTab, *EthDmaRxDscrTab;
/* Ethernet Transmit,Receive Buffer */
static rt_uint8_t *EthTxBuff, *EthRxBuff;
static struct hc32_eth hc32_eth_device =
{
    .irq_config     = ETH_IRQ_CONFIG,
    .irq_callback   = eth_global_irq_handle,
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
static rt_err_t rt_hc32_eth_init(rt_device_t dev)
{
    stc_eth_init_t stcEthInit;
    uint16_t u16RegVal;

    /* Enable ETH clock */
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_ETHMAC, ENABLE);
    /* Init Ethernet GPIO */
    rt_hw_eth_phy_reset(CM_ETH);
    rt_hw_eth_board_init(CM_ETH);
    /* Reset ETHERNET */
    (void)ETH_DeInit();
    /* Configure structure initialization */
    (void)ETH_CommStructInit(&EthHandle.stcCommInit);
    (void)ETH_StructInit(&stcEthInit);
    EthHandle.stcCommInit.u16AutoNego   = ETH_AUTO_NEGO_DISABLE;
    EthHandle.stcCommInit.au8MacAddr[0] = hc32_eth_device.dev_addr[0];
    EthHandle.stcCommInit.au8MacAddr[1] = hc32_eth_device.dev_addr[1];
    EthHandle.stcCommInit.au8MacAddr[2] = hc32_eth_device.dev_addr[2];
    EthHandle.stcCommInit.au8MacAddr[3] = hc32_eth_device.dev_addr[3];
    EthHandle.stcCommInit.au8MacAddr[4] = hc32_eth_device.dev_addr[4];
    EthHandle.stcCommInit.au8MacAddr[5] = hc32_eth_device.dev_addr[5];
#ifdef ETH_USING_INTERFACE_RMII
    EthHandle.stcCommInit.u32Interface  = ETH_MAC_IF_RMII;
#else
    EthHandle.stcCommInit.u32Interface  = ETH_MAC_IF_MII;
#endif
    EthHandle.stcCommInit.u32ReceiveMode = ETH_RX_MD_INT;
#ifdef RT_LWIP_USING_HW_CHECKSUM
    EthHandle.stcCommInit.u32ChecksumMode = ETH_MAC_CHECKSUM_MD_HW;
#else
    EthHandle.stcCommInit.u32ChecksumMode = ETH_MAC_CHECKSUM_MD_SW;
#endif
    /* Configure ethernet peripheral */
    if (LL_OK != ETH_Init(&EthHandle, &stcEthInit))
    {
        LOG_E("eth hardware init failed");
    }
    else
    {
        LOG_D("eth hardware init success");
    }

    /* Initialize Tx Descriptors list: Chain Mode */
    (void)ETH_DMA_TxDescListInit(&EthHandle, EthDmaTxDscrTab, EthTxBuff, ETH_TX_BUF_NUM);
    /* Initialize Rx Descriptors list: Chain Mode  */
    (void)ETH_DMA_RxDescListInit(&EthHandle, EthDmaRxDscrTab, EthRxBuff, ETH_RX_BUF_NUM);
    /* Enable ETH interrupt */
    NVIC_EnableIRQ(hc32_eth_device.irq_config.irq_num);

    /* Enable MAC and DMA transmission and reception */
    if (LL_OK == ETH_Start())
    {
        LOG_D("eth hardware start");
    }
    else
    {
        LOG_E("eth hardware start faild");
        return -RT_ERROR;
    }

    /* Configure PHY LED mode */
    u16RegVal = PHY_PAGE_ADDR_7;
    (void)ETH_PHY_WriteReg(&EthHandle, PHY_PSR, u16RegVal);
    (void)ETH_PHY_ReadReg(&EthHandle, PHY_P7_IWLFR, &u16RegVal);
    MODIFY_REG16(u16RegVal, PHY_LED_SELECT, PHY_LED_SELECT_10);
    (void)ETH_PHY_WriteReg(&EthHandle, PHY_P7_IWLFR, u16RegVal);
    u16RegVal = PHY_PAGE_ADDR_0;
    (void)ETH_PHY_WriteReg(&EthHandle, PHY_PSR, u16RegVal);
#ifdef ETH_USING_INTERFACE_RMII
    /* Disable Power Saving Mode */
    (void)ETH_PHY_ReadReg(&EthHandle, PHY_PSMR, &u16RegVal);
    CLR_REG16_BIT(u16RegVal, PHY_EN_PWR_SAVE);
    (void)ETH_PHY_WriteReg(&EthHandle, PHY_PSMR, u16RegVal);
#endif

    return RT_EOK;
}

static rt_err_t rt_hc32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("eth open");
    return RT_EOK;
}

static rt_err_t rt_hc32_eth_close(rt_device_t dev)
{
    LOG_D("eth close");
    return RT_EOK;
}

static rt_ssize_t rt_hc32_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("eth read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_hc32_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("eth write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_hc32_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args)
        {
            SMEMCPY(args, hc32_eth_device.dev_addr, 6);
        }
        else
        {
            return -RT_ERROR;
        }
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* ethernet device interface */
/* transmit data*/
rt_err_t rt_hc32_eth_tx(rt_device_t dev, struct pbuf *p)
{
    rt_err_t errval = RT_ERROR;
    struct pbuf *q;
    uint8_t *txBuffer;
    __IO stc_eth_dma_desc_t *DmaTxDesc;
    uint32_t byteCnt;
    uint32_t frameLength = 0UL;
    uint32_t bufferOffset;
    uint32_t payloadOffset;

    DmaTxDesc = EthHandle.stcTxDesc;
    txBuffer = (uint8_t *)((EthHandle.stcTxDesc)->u32Buf1Addr);
    bufferOffset = 0UL;
    /* Copy frame from pbufs to driver buffers */
    for (q = p; q != NULL; q = q->next)
    {
        /* If this buffer isn't available, goto error */
        if (0UL != (DmaTxDesc->u32ControlStatus & ETH_DMA_TXDESC_OWN))
        {
            LOG_D("buffer not valid");
            errval = (err_t)ERR_USE;
            goto error;
        }

        /* Get bytes in current lwIP buffer */
        byteCnt = q->len;
        payloadOffset = 0UL;
        /* Check if the length of data to copy is bigger than Tx buffer size */
        while ((byteCnt + bufferOffset) > ETH_TX_BUF_SIZE)
        {
            /* Copy data to Tx buffer*/
            SMEMCPY((uint8_t *) & (txBuffer[bufferOffset]), (uint8_t *) & (((uint8_t *)q->payload)[payloadOffset]), (ETH_TX_BUF_SIZE - bufferOffset));
            /* Point to next descriptor */
            DmaTxDesc = (stc_eth_dma_desc_t *)(DmaTxDesc->u32Buf2NextDescAddr);
            /* Check if the buffer is available */
            if (0UL != (DmaTxDesc->u32ControlStatus & ETH_DMA_TXDESC_OWN))
            {
                errval = (err_t)ERR_USE;
                goto error;
            }

            txBuffer = (uint8_t *)(DmaTxDesc->u32Buf1Addr);
            byteCnt = byteCnt - (ETH_TX_BUF_SIZE - bufferOffset);
            payloadOffset = payloadOffset + (ETH_TX_BUF_SIZE - bufferOffset);
            frameLength = frameLength + (ETH_TX_BUF_SIZE - bufferOffset);
            bufferOffset = 0UL;
        }
        /* Copy the remaining bytes */
        SMEMCPY((uint8_t *) & (txBuffer[bufferOffset]), (uint8_t *) & (((uint8_t *)q->payload)[payloadOffset]), byteCnt);
        bufferOffset = bufferOffset + byteCnt;
        frameLength = frameLength + byteCnt;
    }
    LOG_D("transmit frame length :%d", framelength);
    /* Prepare transmit descriptors to give to DMA */
    (void)ETH_DMA_SetTransFrame(&EthHandle, frameLength);
    errval = (err_t)ERR_OK;

error:
    /* When Transmit Underflow flag is set, clear it and issue a Transmit Poll Demand to resume transmission */
    if (RESET != ETH_DMA_GetStatus(ETH_DMA_FLAG_UNS))
    {
        /* Clear DMA UNS flag */
        ETH_DMA_ClearStatus(ETH_DMA_FLAG_UNS);
        /* Resume DMA transmission */
        WRITE_REG32(CM_ETH->DMA_TXPOLLR, 0UL);
    }

    return errval;
}

/* receive data*/
struct pbuf *rt_hc32_eth_rx(rt_device_t dev)
{
    struct pbuf *p = NULL;
    struct pbuf *q;
    uint32_t len;
    uint8_t *rxBuffer;
    __IO stc_eth_dma_desc_t *DmaRxDesc;
    uint32_t byteCnt;
    uint32_t bufferOffset;
    uint32_t payloadOffset;
    uint32_t i;

    /* Get received frame */
    if (LL_OK != ETH_DMA_GetReceiveFrame_Int(&EthHandle))
    {
        LOG_D("receive frame faild");
        return NULL;
    }

    /* Obtain the size of the packet */
    len = (EthHandle.stcRxFrame).u32Len;
    rxBuffer = (uint8_t *)(EthHandle.stcRxFrame).u32Buf;
    LOG_D("receive frame len : %d", len);
    if (len > 0UL)
    {
        /* Allocate a pbuf chain of pbufs from the Lwip buffer pool */
        p = pbuf_alloc(PBUF_RAW, (uint16_t)len, PBUF_POOL);
    }
    if (p != NULL)
    {
        DmaRxDesc = (EthHandle.stcRxFrame).pstcFSDesc;
        bufferOffset = 0UL;
        for (q = p; q != NULL; q = q->next)
        {
            byteCnt = q->len;
            payloadOffset = 0UL;
            /* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size */
            while ((byteCnt + bufferOffset) > ETH_RX_BUF_SIZE)
            {
                /* Copy data to pbuf */
                SMEMCPY((uint8_t *) & (((uint8_t *)q->payload)[payloadOffset]), (uint8_t *) & (rxBuffer[bufferOffset]), (ETH_RX_BUF_SIZE - bufferOffset));
                /* Point to next descriptor */
                DmaRxDesc = (stc_eth_dma_desc_t *)(DmaRxDesc->u32Buf2NextDescAddr);
                rxBuffer = (uint8_t *)(DmaRxDesc->u32Buf1Addr);
                byteCnt = byteCnt - (ETH_RX_BUF_SIZE - bufferOffset);
                payloadOffset = payloadOffset + (ETH_RX_BUF_SIZE - bufferOffset);
                bufferOffset = 0UL;
            }
            /* Copy remaining data in pbuf */
            SMEMCPY((uint8_t *) & (((uint8_t *)q->payload)[payloadOffset]), (uint8_t *) & (rxBuffer[bufferOffset]), byteCnt);
            bufferOffset = bufferOffset + byteCnt;
        }
    }
    /* Release descriptors to DMA */
    DmaRxDesc = (EthHandle.stcRxFrame).pstcFSDesc;
    for (i = 0UL; i < (EthHandle.stcRxFrame).u32SegCount; i++)
    {
        DmaRxDesc->u32ControlStatus |= ETH_DMA_RXDESC_OWN;
        DmaRxDesc = (stc_eth_dma_desc_t *)(DmaRxDesc->u32Buf2NextDescAddr);
    }
    /* Clear Segment_Count */
    (EthHandle.stcRxFrame).u32SegCount = 0UL;

    /* When Rx Buffer unavailable flag is set, clear it and resume reception */
    if (RESET != ETH_DMA_GetStatus(ETH_DMA_FLAG_RUS))
    {
        /* Clear DMA RUS flag */
        ETH_DMA_ClearStatus(ETH_DMA_FLAG_RUS);
        /* Resume DMA reception */
        WRITE_REG32(CM_ETH->DMA_RXPOLLR, 0UL);
    }

    return p;
}

static void hc32_eth_irq_handle(stc_eth_handle_t *eth_handle)
{
    rt_err_t result;

    (void)eth_handle;
    /* Frame received */
    if (RESET != ETH_DMA_GetStatus(ETH_DMA_FLAG_RIS))
    {
        result = eth_device_ready(&(hc32_eth_device.parent));
        if (result != RT_EOK)
        {
            LOG_I("eth rx complete callback err = %d", result);
        }
        /* Clear the Eth DMA Rx IT pending bits */
        ETH_DMA_ClearStatus(ETH_DMA_FLAG_RIS | ETH_DMA_FLAG_NIS);
    }
}

/* interrupt service routine */
static void eth_global_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_eth_irq_handle(&EthHandle);
    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_phy_link_change(void)
{
    static rt_uint8_t phy_status = 0;
    rt_uint8_t phy_status_new = 0;
    uint16_t u16RegVal = 0U;
    uint16_t u16Page = 0U;

    /* Switch page */
    (void)ETH_PHY_ReadReg(&EthHandle, PHY_PSR, &u16Page);
    if (u16Page != PHY_PAGE_ADDR_0)
    {
        u16RegVal = PHY_PAGE_ADDR_0;
        (void)ETH_PHY_WriteReg(&EthHandle, PHY_PSR, u16RegVal);
    }
    /* Read PHY_BSR */
    (void)ETH_PHY_ReadReg(&EthHandle, PHY_BASIC_STATUS_REG, &u16RegVal);
    LOG_D("phy basic status reg is 0x%X", u16RegVal);
    if ((0x0000U != u16RegVal) && (0xFFFFU != u16RegVal))
    {
        if (u16RegVal & (PHY_AUTONEGO_COMPLETE_MASK | PHY_LINKED_STATUS_MASK))
        {
            phy_status_new |= ETH_PHY_LINK;
            if (0U != (u16RegVal & (PHY_100BASE_TX_FD | PHY_10BASE_T_FD)))
            {
                phy_status_new |= ETH_PHY_FULL_DUPLEX;
            }
            if (0U != (u16RegVal & (PHY_100BASE_TX_FD | PHY_100BASE_TX_HD)))
            {
                phy_status_new |= ETH_PHY_100M;
            }
        }
    }
    /* Restore page */
    if (u16Page != PHY_PAGE_ADDR_0)
    {
        (void)ETH_PHY_WriteReg(&EthHandle, PHY_PSR, u16Page);
    }

    if (phy_status != phy_status_new)
    {
        phy_status = phy_status_new;
        if (phy_status & ETH_PHY_LINK)
        {
            if (phy_status & ETH_PHY_FULL_DUPLEX)
            {
                hc32_eth_device.eth_mode = ETH_MAC_DUPLEX_MD_FULL;
            }
            else
            {
                hc32_eth_device.eth_mode = ETH_MAC_DUPLEX_MD_HALF;
            }
            if (phy_status & ETH_PHY_100M)
            {
                hc32_eth_device.eth_speed = ETH_MAC_SPEED_100M;
            }
            else
            {
                hc32_eth_device.eth_speed = ETH_MAC_SPEED_10M;
            }
            LOG_D("link up");
            eth_device_linkchange(&hc32_eth_device.parent, RT_TRUE);
        }
        else
        {
            LOG_I("link down");
            eth_device_linkchange(&hc32_eth_device.parent, RT_FALSE);
        }
    }
}

#if defined(PHY_USING_INTERRUPT_MODE) && defined(ETH_USING_INTERFACE_RMII)
static void eth_phy_irq_handler(void *args)
{
    rt_uint16_t status = 0;

    ETH_PHY_ReadReg(&EthHandle, PHY_IISDR, &status);
    LOG_D("phy interrupt status reg is 0x%X", status);
    hc32_phy_link_change();
}
#endif

static void hc32_phy_monitor_thread(void *parameter)
{
    uint8_t phy_addr = 0xFF;
    uint8_t detected_count = 0;

    /* phy search */
    while (phy_addr == 0xFF)
    {
        rt_uint16_t i, temp;

        for (i = 0; i <= 0x1F; i++)
        {
            EthHandle.stcCommInit.u16PhyAddr = i;
            ETH_PHY_ReadReg(&EthHandle, PHY_ID1_REG, &temp);
            if (temp != 0xFFFF && temp != 0x00)
            {
                phy_addr = i;
                break;
            }
        }
        detected_count++;
        rt_thread_mdelay(1000);
        if (detected_count > 10)
        {
            LOG_E("No PHY device was detected!");
        }
    }
    LOG_D("Found a phy, address:0x%02X", phy_addr);

    /* Reset PHY */
    ETH_PHY_WriteReg(&EthHandle, PHY_BASIC_CONTROL_REG, PHY_RESET_MASK);
    rt_thread_mdelay(2000);
    ETH_PHY_WriteReg(&EthHandle, PHY_BASIC_CONTROL_REG, PHY_AUTO_NEGOTIATION_MASK);
    hc32_phy_link_change();
#if defined(PHY_USING_INTERRUPT_MODE) && defined(ETH_USING_INTERFACE_RMII)
    /* configuration intterrupt pin */
    rt_pin_mode(ETH_PHY_INT_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(ETH_PHY_INT_PIN, PIN_IRQ_MODE_FALLING, eth_phy_irq_handler, (void *)"callbackargs");
    rt_pin_irq_enable(ETH_PHY_INT_PIN, PIN_IRQ_ENABLE);

    uint16_t u16RegVal;
    /* Configure PHY to generate an interrupt when Eth Link state changes */
    u16RegVal = PHY_PAGE_ADDR_7;
    (void)ETH_PHY_WriteReg(&EthHandle, PHY_PSR, u16RegVal);
    /* Enable Interrupt on change of link status */
    (void)ETH_PHY_ReadReg(&EthHandle, PHY_P7_IWLFR, &u16RegVal);
    SET_REG16_BIT(u16RegVal, PHY_INT_LINK_CHANGE);
    (void)ETH_PHY_WriteReg(&EthHandle, PHY_P7_IWLFR, u16RegVal);
    u16RegVal = PHY_PAGE_ADDR_0;
    (void)ETH_PHY_WriteReg(&EthHandle, PHY_PSR, u16RegVal);
#else
    hc32_eth_device.poll_link_timer = rt_timer_create("eth_phy_link", (void (*)(void *))hc32_phy_link_change,
                                      NULL, RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC);
    if (!hc32_eth_device.poll_link_timer || rt_timer_start(hc32_eth_device.poll_link_timer) != RT_EOK)
    {
        LOG_E("Start eth phy link change detection timer failed");
    }
#endif
}

/* Register the eth device */
static int rt_hw_hc32_eth_init(void)
{
    rt_err_t state = RT_EOK;

    /* register eth handler */
    hc32_install_irq_handler(&hc32_eth_device.irq_config, hc32_eth_device.irq_callback, RT_FALSE);
    /* Prepare receive and send buffers */
    EthRxBuff = (rt_uint8_t *)rt_calloc(ETH_RX_BUF_NUM, ETH_MAX_PACKET_SIZE);
    if (EthRxBuff == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }
    EthTxBuff = (rt_uint8_t *)rt_calloc(ETH_TX_BUF_NUM, ETH_MAX_PACKET_SIZE);
    if (EthTxBuff == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }
    EthDmaRxDscrTab = (stc_eth_dma_desc_t *)rt_calloc(ETH_RX_BUF_NUM, sizeof(stc_eth_dma_desc_t));
    if (EthDmaRxDscrTab == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }
    EthDmaTxDscrTab = (stc_eth_dma_desc_t *)rt_calloc(ETH_TX_BUF_NUM, sizeof(stc_eth_dma_desc_t));
    if (EthDmaTxDscrTab == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }

    hc32_eth_device.eth_speed = ETH_MAC_SPEED_100M;
    hc32_eth_device.eth_mode  = ETH_MAC_DUPLEX_MD_FULL;
    /* 00-80 uid */
    hc32_eth_device.dev_addr[0] = 0x02;
    hc32_eth_device.dev_addr[1] = 0x80;
    hc32_eth_device.dev_addr[2] = 0x00;
    /* generate MAC addr from unique ID */
    hc32_eth_device.dev_addr[3] = (rt_uint8_t)READ_REG32(CM_EFM->UQID0);
    hc32_eth_device.dev_addr[4] = (rt_uint8_t)READ_REG32(CM_EFM->UQID1);
    hc32_eth_device.dev_addr[5] = (rt_uint8_t)READ_REG32(CM_EFM->UQID2);

    hc32_eth_device.parent.parent.init      = rt_hc32_eth_init;
    hc32_eth_device.parent.parent.open      = rt_hc32_eth_open;
    hc32_eth_device.parent.parent.close     = rt_hc32_eth_close;
    hc32_eth_device.parent.parent.read      = rt_hc32_eth_read;
    hc32_eth_device.parent.parent.write     = rt_hc32_eth_write;
    hc32_eth_device.parent.parent.control   = rt_hc32_eth_control;
    hc32_eth_device.parent.parent.user_data = RT_NULL;
    hc32_eth_device.parent.eth_rx           = rt_hc32_eth_rx;
    hc32_eth_device.parent.eth_tx           = rt_hc32_eth_tx;
    /* register eth device */
    state = eth_device_init(&(hc32_eth_device.parent), "e0");
    if (RT_EOK == state)
    {
        LOG_D("eth device init success");
    }
    else
    {
        LOG_E("eth device init faild: %d", state);
        state = -RT_ERROR;
        goto __exit;
    }

    /* start phy monitor */
    rt_thread_t tid;
    tid = rt_thread_create("phy_monitor", hc32_phy_monitor_thread, RT_NULL, 1024, 12, 5);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        state = -RT_ERROR;
    }

__exit:
    if (state != RT_EOK)
    {
        if (EthRxBuff)
        {
            rt_free(EthRxBuff);
        }
        if (EthTxBuff)
        {
            rt_free(EthTxBuff);
        }
        if (EthDmaRxDscrTab)
        {
            rt_free(EthDmaRxDscrTab);
        }
        if (EthDmaTxDscrTab)
        {
            rt_free(EthDmaTxDscrTab);
        }
    }

    return state;
}
INIT_DEVICE_EXPORT(rt_hw_hc32_eth_init);

#endif
