/*
 * File      : emac.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2021, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-08-29     aozima       first implementation
 */

#include <rtthread.h>
#include <netif/ethernetif.h>
#include "lwipopts.h"

#include "board.h"

#include "app_phy.h"

/* debug option */
#define ETH_DEBUG
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP

#ifdef ETH_DEBUG
#define CME_ETH_PRINTF          rt_kprintf
#else
#define CME_ETH_PRINTF(...)
#endif

#define MAX_ADDR_LEN 6
struct rt_cme_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;

    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];         /* hw address   */

    uint32_t    ETH_Speed;
    uint32_t    ETH_Mode;

    struct rt_semaphore tx_buf_free;
    struct rt_mutex     lock;
};
static struct rt_cme_eth cme_eth_device;

#if defined(ETH_RX_DUMP) ||  defined(ETH_TX_DUMP)
static void packet_dump(const char * msg, const struct pbuf* p)
{
    const struct pbuf* q;
    rt_uint32_t i,j;
    rt_uint8_t *ptr;

    rt_kprintf("%s %d byte\n", msg, p->tot_len);

    i=0;
    for(q=p; q != RT_NULL; q= q->next)
    {
        ptr = q->payload;

        for(j=0; j<q->len; j++)
        {
            if( (i%8) == 0 )
            {
                rt_kprintf("  ");
            }
            if( (i%16) == 0 )
            {
                rt_kprintf("\r\n");
            }
            rt_kprintf("%02x ",*ptr);

            i++;
            ptr++;
        }
    }

    rt_kprintf("\n\n");
}
#else
#define packet_dump(...)
#endif /* dump */

/////////////////////////////////////////////////////////////////
uint32_t rxTotalMemory = 0x2000;
uint32_t rxDescNum = 3;
uint32_t rxBufSize = 0x400;
uint32_t rxBaseAddr = 0x2000C000;// C000-48K
uint32_t txBaseAddr = 0x2000E000;// E000-56K
uint32_t txTotalMemory = 0x2000;
BOOL isRxNoBuf = FALSE;

#define ETH_MAX_PACKET_SIZE    1520    /* ETH_HEADER + ETH_EXTRA + MAX_ETH_PAYLOAD + ETH_CRC */
#define ETH_RXBUFNB         4
#define ETH_TXBUFNB         2

struct eth_rx_buffer
{
    ETH_RX_DESC desc;
    uint32_t buffer[ETH_MAX_PACKET_SIZE/4];
};

struct eth_tx_buffer
{
    ETH_TX_DESC desc;
    uint32_t buffer[ETH_MAX_PACKET_SIZE/4];
};

static struct eth_rx_buffer rx_buffer[ETH_RXBUFNB];
static struct eth_tx_buffer tx_buffer[ETH_TXBUFNB];

static void RxDescChainInit(void)
{
    uint32_t i;

    // initialize rx descriptor
    ETH_RX_DESC *desc = &rx_buffer[0].desc;

    for (i = 0; i < ETH_RXBUFNB; i++)
    {
        desc->RX_1.RX1_b.SIZE = ETH_MAX_PACKET_SIZE;
        desc->bufAddr = (uint32_t)rx_buffer[i].buffer;

        if((i+1) == ETH_RXBUFNB)
            desc->nextDescAddr = (uint32_t)&rx_buffer[0].desc;
        else
            desc->nextDescAddr = (uint32_t)&rx_buffer[i+1].desc;

        desc = (ETH_RX_DESC *)desc->nextDescAddr;
    }

    ETH_SetRxDescRing(&rx_buffer[0].desc);
}

static void TxDescChainInit(void)
{
    uint32_t i;

    // initialize tx descriptor
    ETH_TX_DESC *desc = &tx_buffer[0].desc;

    for (i = 0; i < ETH_TXBUFNB; i++)
    {
        desc->TX_1.TX1_b.SIZE = ETH_MAX_PACKET_SIZE;
        desc->bufAddr = (uint32_t)tx_buffer[i].buffer;

        if((i+1) == ETH_TXBUFNB)
            desc->nextDescAddr = (uint32_t)&tx_buffer[0].desc;
        else
            desc->nextDescAddr = (uint32_t)&tx_buffer[i+1].desc;

        desc = (ETH_TX_DESC *)desc->nextDescAddr;
    }

    ETH_SetTxDescRing(&tx_buffer[0].desc);
}

/////////////////////////////////////////////////////////////////

/* initialize the interface */
static rt_err_t rt_cme_eth_init(rt_device_t dev)
{
    struct rt_cme_eth * cme_eth = (struct rt_cme_eth *)dev;

    ETH_InitTypeDef init;
    ETH_FrameFilter flt;

    init.ETH_Speed = phy_GetSpeed();
    init.ETH_Duplex = phy_GetDuplex();
    init.ETH_LinkUp = phy_IsLink();
    init.ETH_RxEn = TRUE;
    init.ETH_TxEn = TRUE;
    init.ETH_ChecksumOffload = FALSE;
    init.ETH_JumboFrame = FALSE;

    memcpy(init.ETH_MacAddr, cme_eth->dev_addr, sizeof(init.ETH_MacAddr));

    // Disable broadcast;
    // TODO: why?
    memset(&flt, 0, sizeof(ETH_FrameFilter));
    flt.ETH_BroadcastFilterEnable = FALSE;
    flt.ETH_OwnFilterEnable = FALSE;
    flt.ETH_SelfDrop = FALSE;
    flt.ETH_SourceFilterEnable = FALSE;
    flt.ETH_SourceDrop = FALSE;

    init.ETH_Filter = &flt;

    if (!phy_Init())
    {
        rt_kprintf("phy_Init failed!\n");
        while (1);
    }

    if (!ETH_Init(&init))
    {
        rt_kprintf("ETH_Init failed!\n");
        while (1);
    }

    RxDescChainInit();
    TxDescChainInit();

    ETH_ITConfig(ETH_INT_BUS_FATAL_ERROR, TRUE);

    ETH_ITConfig(ETH_INT_RX_COMPLETE_FRAME, TRUE);
    ETH_ITConfig(ETH_INT_RX_BUF_UNAVAI, TRUE);
    ETH_ITConfig(ETH_INT_RX_STOP, TRUE);
    ETH_StartRx();

    ETH_ITConfig(ETH_INT_TX_COMPLETE_FRAME, TRUE);
    ETH_StartTx();

    return RT_EOK;
}

static rt_err_t rt_cme_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_cme_eth_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_cme_eth_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_cme_eth_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_cme_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch(cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if(args) rt_memcpy(args, cme_eth_device.dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_cme_eth_tx( rt_device_t dev, struct pbuf* p)
{
    rt_err_t result = RT_EOK;
    ETH_TX_DESC *desc;
    struct rt_cme_eth * cme_eth = (struct rt_cme_eth *)dev;

    rt_mutex_take(&cme_eth->lock, RT_WAITING_FOREVER);

#ifdef ETH_TX_DUMP
    packet_dump("TX dump", p);
#endif /* ETH_TX_DUMP */

    /* get free tx buffer */
    {
        rt_err_t result;
        result = rt_sem_take(&cme_eth->tx_buf_free, RT_TICK_PER_SECOND/10);
        if (result != RT_EOK)
        {
            result = -RT_ERROR;
            goto _exit;
        }
    }

    desc = ETH_AcquireFreeTxDesc();
    if(desc == RT_NULL)
    {
        CME_ETH_PRINTF("TxDesc not ready!\n");
        RT_ASSERT(0);
            result = -RT_ERROR;
            goto _exit;
    }

    desc->TX_0.TX0_b.FS = TRUE;
    desc->TX_0.TX0_b.LS = TRUE;
    desc->TX_1.TX1_b.SIZE = p->tot_len;

    pbuf_copy_partial(p, ( void *)(desc->bufAddr), p->tot_len, 0);

    ETH_ReleaseTxDesc(desc);
    ETH_ResumeTx();

_exit:
    rt_mutex_release(&cme_eth->lock);
    return result;
}

/* reception packet. */
struct pbuf *rt_cme_eth_rx(rt_device_t dev)
{
    struct pbuf* p = RT_NULL;
    ETH_RX_DESC *desc;
    uint32_t framelength;
    struct rt_cme_eth * cme_eth = (struct rt_cme_eth *)dev;
    rt_err_t result;

    result = rt_mutex_take(&cme_eth->lock, RT_WAITING_FOREVER);
    if (result == -RT_ETIMEOUT)
    {
        rt_kprintf("Take mutex time out.\n");
        goto _exit;
    }
    else if (result == -RT_ERROR)
    {
        rt_kprintf("Take mutex error.\n");
        goto _exit;
    }

    desc = ETH_AcquireFreeRxDesc();
    if(desc == RT_NULL)
    {
        ETH_ITConfig(ETH_INT_RX_COMPLETE_FRAME, TRUE);
        ETH_ITConfig(ETH_INT_RX_BUF_UNAVAI, TRUE);
        ETH_ResumeRx();
        goto _exit;
    }

    framelength = desc->RX_0.RX0_b.FL;

    /* allocate buffer */
    p = pbuf_alloc(PBUF_LINK, framelength, PBUF_RAM);
    if (p != RT_NULL)
    {
        pbuf_take(p, (const void *)(desc->bufAddr), framelength);
#ifdef ETH_RX_DUMP
        packet_dump("RX dump", p);
#endif /* ETH_RX_DUMP */
    }

    ETH_ReleaseRxDesc(desc);

_exit:
    rt_mutex_release(&cme_eth->lock);
    return p;
}

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = ETH_INT_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = TRUE;
    NVIC_Init(&NVIC_InitStructure);
}

int cme_m7_eth_init(void)
{
//    /* PHY RESET: PA4 */
//    {
//        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
//        rt_thread_delay(2);
//        GPIO_SetBits(GPIOA, GPIO_Pin_4);
//        rt_thread_delay(2);
//    }

//    GPIO_Configuration();
    NVIC_Configuration();

//    cme_eth_device.ETH_Speed = ETH_Speed_100M;
//    cme_eth_device.ETH_Mode  = ETH_Mode_FullDuplex;

    /* OUI 00-80-E1 STMICROELECTRONICS. */
    cme_eth_device.dev_addr[0] = 0x00;
    cme_eth_device.dev_addr[1] = 0x80;
    cme_eth_device.dev_addr[2] = 0xE1;
    /* generate MAC addr from 96bit unique ID (only for test). */
//    cme_eth_device.dev_addr[3] = *(rt_uint8_t*)(0x1FFF7A10+4);
//    cme_eth_device.dev_addr[4] = *(rt_uint8_t*)(0x1FFF7A10+2);
//    cme_eth_device.dev_addr[5] = *(rt_uint8_t*)(0x1FFF7A10+0);
    cme_eth_device.dev_addr[3] = 12;
    cme_eth_device.dev_addr[4] = 34;
    cme_eth_device.dev_addr[5] = 56;

    cme_eth_device.parent.parent.init       = rt_cme_eth_init;
    cme_eth_device.parent.parent.open       = rt_cme_eth_open;
    cme_eth_device.parent.parent.close      = rt_cme_eth_close;
    cme_eth_device.parent.parent.read       = rt_cme_eth_read;
    cme_eth_device.parent.parent.write      = rt_cme_eth_write;
    cme_eth_device.parent.parent.control    = rt_cme_eth_control;
    cme_eth_device.parent.parent.user_data  = RT_NULL;

    cme_eth_device.parent.eth_rx     = rt_cme_eth_rx;
    cme_eth_device.parent.eth_tx     = rt_cme_eth_tx;

    /* init EMAC lock */
    rt_mutex_init(&cme_eth_device.lock, "emac0", RT_IPC_FLAG_PRIO);

    /* init tx buffer free semaphore */
    rt_sem_init(&cme_eth_device.tx_buf_free,
                "tx_buf",
                ETH_TXBUFNB,
                RT_IPC_FLAG_FIFO);

    /* register eth device */
    eth_device_init(&(cme_eth_device.parent), "e0");

    return RT_EOK;
}

void ETH_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (ETH_GetITStatus(ETH_INT_TX_COMPLETE_FRAME))
    {
        rt_sem_release(&cme_eth_device.tx_buf_free);
        ETH_ClearITPendingBit(ETH_INT_TX_COMPLETE_FRAME);
    }

    if (ETH_GetITStatus(ETH_INT_RX_STOP))
    {
        CME_ETH_PRINTF("ETH_INT_RX_STOP\n");
        ETH_ClearITPendingBit(ETH_INT_RX_STOP);
    }

    if ((ETH_GetITStatus(ETH_INT_RX_BUF_UNAVAI)) ||
            (ETH_GetITStatus(ETH_INT_RX_COMPLETE_FRAME)))
    {
        /* a frame has been received */
        eth_device_ready(&(cme_eth_device.parent));

        ETH_ITConfig(ETH_INT_RX_COMPLETE_FRAME, FALSE);
        ETH_ITConfig(ETH_INT_RX_BUF_UNAVAI, FALSE);
        ETH_ClearITPendingBit(ETH_INT_RX_BUF_UNAVAI);
        ETH_ClearITPendingBit(ETH_INT_RX_COMPLETE_FRAME);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

