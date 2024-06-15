/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
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
#include <rtdevice.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#include "fsl_enet.h"

#ifdef RT_USING_LWIP

#include <netif/ethernetif.h>
#include "lwipopts.h"

#define DBG_TAG "drv.eth"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>


/* The PHY ID one register */
#define PHY_ID1_REG                 0x02U
/* The PHY ID two register */
#define PHY_ID2_REG                 0x03U
/* The PHY auto-negotiate advertise register */
#define PHY_AUTONEG_ADVERTISE_REG   0x04U

/* The PHY basic control register */
#define PHY_BASIC_CONTROL_REG       0x00U
#define PHY_RESET_MASK              (1<<15)
#define PHY_AUTO_NEGOTIATION_MASK   (1<<12)

#define PHY_LINK         (1 << 0)
#define PHY_100M         (1 << 1)
#define PHY_FULL_DUPLEX  (1 << 2)



/* The PHY basic status register */
#define PHY_BASIC_STATUS_REG        0x01U
#define PHY_LINKED_STATUS_MASK      (1<<2)
#define PHY_AUTONEGO_COMPLETE_MASK  (1<<5)


/*  The PHY status register. */
#define PHY_Status_REG              0x1FU

#define PHY_100M_MASK               (1<<3)
#define PHY_FULL_DUPLEX_MASK        (1<<4)
#define PHY_Status_SPEED_100M(sr)   ((sr) & PHY_100M_MASK)
#define PHY_Status_FULL_DUPLEX(sr)  ((sr) & PHY_FULL_DUPLEX_MASK)


//extern phy_lan8741_resource_t g_phy_resource;
#define EXAMPLE_ENET_BASE    ENET0
#define EXAMPLE_PHY_ADDRESS  0x00U
#define ENET_EXAMPLE_IRQ     ETHERNET_IRQn
#define EXAMPLE_CLOCK_FREQ   (50000000U)
#define ENET_RXBD_NUM               (4)
#define ENET_TXBD_NUM               (4)
#define ENET_RXBUFF_SIZE            (ENET_FRAME_MAX_FRAMELEN)
#define ENET_BuffSizeAlign(n)       ENET_ALIGN(n, ENET_BUFF_ALIGNMENT)
#define ENET_ALIGN(x, align)        ((unsigned int)((x) + ((align)-1)) & (unsigned int)(~(unsigned int)((align)-1)))


rt_align(4) enet_rx_bd_struct_t g_rxBuffDescrip[ENET_RXBD_NUM];
rt_align(4) enet_tx_bd_struct_t g_txBuffDescrip[ENET_RXBD_NUM];

static enet_tx_reclaim_info_t g_txDirty[ENET_TXBD_NUM];



#define MAX_ADDR_LEN 6


struct rt_stm32_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;
#ifndef PHY_USING_INTERRUPT_MODE
    rt_timer_t poll_link_timer;
#endif

    /* interface address info, hw address */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];
    enet_handle_t g_handle;
    rt_uint32_t    rx_channel;
};

static struct rt_stm32_eth stm32_eth_device;



static void ENET_IntCallback(ENET_Type *base, enet_handle_t *handle, enet_event_t event, uint8_t channel, enet_tx_reclaim_info_t *txReclaimInfo, void *param)
{
    rt_err_t result;

    switch (event)
    {
        case kENET_TxIntEvent:
            /* Get frame info after whole frame transmits out */
//            if (txReclaimInfo != NULL)
//            {
//                rt_free((*txReclaimInfo).context);
//            }
            break;
        case kENET_RxIntEvent:
            stm32_eth_device.rx_channel = channel;
            result = eth_device_ready(&(stm32_eth_device.parent));
            if (result != RT_EOK)
            {
                LOG_I("_enet_rx_data err = %d", result);
            }
        default:
            break;
    }
}

static rt_err_t rt_stm32_eth_init(rt_device_t dev)
{
    uint32_t count = 0;
    bool link      = false;
    bool autonego  = false;
    status_t status;
    enet_config_t config;
    int i;
    uint32_t rxbuffer[ENET_RXBD_NUM];

    struct rt_stm32_eth *eth = (struct rt_stm32_eth*)dev->user_data;

    for (i = 0; i < ENET_RXBD_NUM; i++)
    {
        /* This is for rx buffers, static alloc and dynamic alloc both ok. use as your wish. */
        rxbuffer[i] = (uint32_t)rt_malloc(ENET_RXBUFF_SIZE);
    }

    /* prepare the buffer configuration. */
    enet_buffer_config_t buffConfig[1] = {{
        ENET_RXBD_NUM,
        ENET_TXBD_NUM,
        &g_txBuffDescrip[0],
        &g_txBuffDescrip[0],
        &g_txDirty[0],
        &g_rxBuffDescrip[0],
        &g_rxBuffDescrip[ENET_RXBD_NUM],
        &rxbuffer[0],
        ENET_BuffSizeAlign(ENET_RXBUFF_SIZE),
    }};


    CLOCK_AttachClk(kNONE_to_ENETRMII);
    CLOCK_EnableClock(kCLOCK_Enet);

    ENET_SetSMI(EXAMPLE_ENET_BASE, CLOCK_GetCoreSysClkFreq());
    ENET_GetDefaultConfig(&config);

    /* Use the actual speed and duplex when phy success to finish the autonegotiation. */
    config.miiSpeed  = kENET_MiiSpeed100M;
    config.miiDuplex = kENET_MiiFullDuplex;
    config.interrupt = (kENET_DmaRx) | (kENET_DmaTx);

    ENET_Init(EXAMPLE_ENET_BASE, &config, &stm32_eth_device.dev_addr[0], EXAMPLE_CLOCK_FREQ);
    ENET_DescriptorInit(EXAMPLE_ENET_BASE, &config, &buffConfig[0]);
    ENET_CreateHandler(EXAMPLE_ENET_BASE, &eth->g_handle, &config, &buffConfig[0], ENET_IntCallback, NULL);
    ENET_StartRxTx(EXAMPLE_ENET_BASE, 1, 1);

    return RT_EOK;
}



static rt_err_t rt_stm32_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
        case NIOCTL_GADDR:
        /* get mac address */
        if (args)
        {
            SMEMCPY(args, stm32_eth_device.dev_addr, 6);
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


rt_err_t rt_stm32_eth_tx(rt_device_t dev, struct pbuf *p)
{
    struct pbuf *q;
    status_t status;

    struct rt_stm32_eth *eth = (struct rt_stm32_eth*)dev->user_data;
  //  LOG_D("rt_stm32_eth_tx: len: %d, tot_len:%d", p->len, p->tot_len);

    enet_buffer_struct_t txBuff[ENET_TXBD_NUM];
    enet_tx_frame_struct_t txFrame = {0};

    for (q = p; q != NULL; q = q->next)
    {
        txBuff[txFrame.txBuffNum].buffer = q->payload;
        txBuff[txFrame.txBuffNum].length = q->len;
        txFrame.txBuffNum++;
    }

    txFrame.txBuffArray        = txBuff;
    txFrame.txConfig.intEnable = true;
    txFrame.txConfig.tsEnable  = true;
    txFrame.context            = RT_NULL;


    status = ENET_SendFrame(EXAMPLE_ENET_BASE, &eth->g_handle, &txFrame, 0);

    return (status == kStatus_Success);
}

struct pbuf *rt_stm32_eth_rx(rt_device_t dev)
{
    struct pbuf *p = RT_NULL;
    uint32_t len = 0;
    status_t status;

    struct rt_stm32_eth *eth = (struct rt_stm32_eth*)dev->user_data;

    status = ENET_GetRxFrameSize(EXAMPLE_ENET_BASE, &eth->g_handle, &len, eth->rx_channel);

   // LOG_D("rt_stm32_eth_rx: status:%d, length: %d, channel:%d", status, len, eth->rx_channel);

    if (len != 0 && (status == kStatus_Success))
    {
        /* Received valid frame. Deliver the rx buffer with the size equal to length. */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
        if (p != NULL)
        {
            status = ENET_ReadFrame(EXAMPLE_ENET_BASE, &eth->g_handle, p->payload, len, eth->rx_channel, NULL);

            if (status == kStatus_Success)
            {
                return p;
            }
            else
            {
                LOG_D(" A frame read failed\n");
                pbuf_free(p);
            }
        }
        else
        {
            LOG_D(" pbuf_alloc faild\n");
        }
    }
    else if (status == kStatus_ENET_RxFrameError)
    {
        /* update the receive buffer. */
        ENET_ReadFrame(EXAMPLE_ENET_BASE, &eth->g_handle, NULL, 0, eth->rx_channel, NULL);
    }
    return RT_NULL;
}



static void phy_monitor_thread_entry(void *parameter)
{
    uint8_t phy_addr = 0xFF;
    uint8_t detected_count = 0;

    while(phy_addr == 0xFF)
    {
        /* phy search */
        rt_uint16_t i, temp;
        for (i = 0; i <= 0x1F; i++)
        {
           // EthHandle.Init.PhyAddress = i;
            ENET_MDIORead(EXAMPLE_ENET_BASE, i, PHY_ID1_REG, &temp);

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
            LOG_E("No PHY device was detected, please check hardware!");
        }
    }

    LOG_D("Found a phy, address:0x%02X", phy_addr);

    /* RESET PHY */
    LOG_D("RESET PHY!");
    ENET_MDIOWrite(EXAMPLE_ENET_BASE, phy_addr, PHY_BASIC_CONTROL_REG, PHY_RESET_MASK);
    rt_thread_mdelay(2000);
    ENET_MDIOWrite(EXAMPLE_ENET_BASE, phy_addr, PHY_BASIC_CONTROL_REG, PHY_AUTO_NEGOTIATION_MASK);

    while(1)
    {
        static rt_uint8_t phy_speed = 0;
        uint8_t phy_speed_new = 0;
        uint16_t status;

        ENET_MDIORead(EXAMPLE_ENET_BASE, phy_addr, PHY_BASIC_STATUS_REG, &status);
        LOG_D("phy basic status reg is 0x%X", status);

        if (status & (PHY_AUTONEGO_COMPLETE_MASK | PHY_LINKED_STATUS_MASK))
        {
            uint16_t SR = 0;

            phy_speed_new |= PHY_LINK;

            ENET_MDIORead(EXAMPLE_ENET_BASE, phy_addr, PHY_Status_REG, &SR);
            LOG_D("phy control status reg is 0x%X", SR);

            if (PHY_Status_SPEED_100M(SR))
            {
                phy_speed_new |= PHY_100M;
            }

            if (PHY_Status_FULL_DUPLEX(SR))
            {
                phy_speed_new |= PHY_FULL_DUPLEX;
            }
        }

        if (phy_speed != phy_speed_new)
        {
            phy_speed = phy_speed_new;
            if (phy_speed & PHY_LINK)
            {
                LOG_D("link up");
                if (phy_speed & PHY_100M)
                {
                    LOG_D("100Mbps");
                }
                else
                {
                    LOG_D("10Mbps");
                }

                if (phy_speed & PHY_FULL_DUPLEX)
                {
                    LOG_D("full-duplex");
                }
                else
                {
                    LOG_D("half-duplex");
                }

                /* send link up. */
                eth_device_linkchange(&stm32_eth_device.parent, RT_TRUE);
            }
            else
            {
                LOG_I("link down");
                eth_device_linkchange(&stm32_eth_device.parent, RT_FALSE);
            }
        }
        rt_thread_mdelay(1000);
    }
}


static int rt_hw_imxrt_eth_init(void)
{
    rt_err_t state = RT_EOK;

    stm32_eth_device.dev_addr[0] = 0x00;
    stm32_eth_device.dev_addr[1] = 0x80;
    stm32_eth_device.dev_addr[2] = 0xE1;
    stm32_eth_device.dev_addr[3] = 0x01;
    stm32_eth_device.dev_addr[4] = 0x02;
    stm32_eth_device.dev_addr[5] = 0x03;

    stm32_eth_device.parent.parent.init       = rt_stm32_eth_init;
    stm32_eth_device.parent.parent.open       = RT_NULL;
    stm32_eth_device.parent.parent.close      = RT_NULL;
    stm32_eth_device.parent.parent.read       = RT_NULL;
    stm32_eth_device.parent.parent.write      = RT_NULL;
    stm32_eth_device.parent.parent.control    = rt_stm32_eth_control;
    stm32_eth_device.parent.parent.user_data  = &stm32_eth_device;

    stm32_eth_device.parent.eth_rx     = rt_stm32_eth_rx;
    stm32_eth_device.parent.eth_tx     = rt_stm32_eth_tx;

    /* register eth device */
    state = eth_device_init(&(stm32_eth_device.parent), "e0");
    if (RT_EOK != state)
    {
        LOG_E("emac device init faild: %d", state);
        state = -RT_ERROR;
    }

    /* start phy monitor */
    rt_thread_startup(rt_thread_create("phy", phy_monitor_thread_entry, RT_NULL, 1024, RT_THREAD_PRIORITY_MAX - 2, 2));
    return state;

}

INIT_DEVICE_EXPORT(rt_hw_imxrt_eth_init);

#endif
