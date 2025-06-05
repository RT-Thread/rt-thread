/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-19     SummerGift   first version
 * 2018-12-25     zylx         fix some bugs
 * 2019-06-10     SummerGift   optimize PHY state detection process
 * 2019-09-03     xiaofan      optimize link change detection process
 * 2020-07-17     wanghaijing  support h7
 * 2020-11-30     wanghaijing  add phy reset
 */

#include<rtthread.h>
#include<rtdevice.h>
#include "board.h"
#include "drv_config.h"

#ifdef BSP_USING_ETH

#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "drv_eth.h"

/*
* Emac driver uses CubeMX tool to generate emac and phy's configuration,
* the configuration files can be found in CubeMX_Config folder.
*/

/* debug option */
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP
//#define DRV_DEBUG
#define LOG_TAG             "drv_eth.c"
#include <drv_log.h>

#define MAX_ADDR_LEN            (6)



struct rt_stm32_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;
#ifndef PHY_USING_INTERRUPT_MODE
    rt_timer_t poll_link_timer;
#endif

    /* interface address info, hw address */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];
    /* ETH_Speed */
    uint32_t    ETH_Speed;
    /* ETH_Duplex_Mode */
    uint32_t    ETH_Mode;
};

typedef struct
{
  struct pbuf pbuf;
  uint8_t buff[ETH_RX_BUFFER_SIZE];
} RxBuff_t;

static ETH_HandleTypeDef EthHandle = {0};
static ETH_TxPacketConfig TxConfig;
static struct rt_stm32_eth stm32_eth_device;
static uint8_t PHY_ADDR = BSP_ETH_PHY_ADDR;
static rt_uint32_t reset_pin = 0;

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma location=0x24020000
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
#pragma location=0x24020100
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */
#pragma location=0x24020200
uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE]; /* Ethernet Receive Buffers */

#elif defined ( __CC_ARM )  /* MDK ARM Compiler */
__attribute__((at(0x24020000))) ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
__attribute__((at(0x24020100))) ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */
__attribute__((at(0x24020200))) uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE]; /* Ethernet Receive Buffer */

#elif defined ( __GNUC__ ) /* GNU Compiler */
ETH_DMADescTypeDef DMARxDscrTab[ETH_RX_DESC_CNT] __attribute__((section(".RxDecripSection"))); /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef DMATxDscrTab[ETH_TX_DESC_CNT] __attribute__((section(".TxDecripSection")));   /* Ethernet Tx DMA Descriptors */
RxBuff_t Rx_Buff[ETH_RX_DESC_CNT] __attribute__((section(".RxArraySection")))__attribute__((aligned(32))); /* Ethernet Receive Buffers */
#endif

#if defined(ETH_RX_DUMP) || defined(ETH_TX_DUMP)
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char *)ptr;
    int i, j;

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

static void phy_reset(void)
{
    rt_pin_write(reset_pin, PIN_LOW);
    rt_thread_mdelay(50);
    rt_pin_write(reset_pin, PIN_HIGH);
}


/* EMAC initialization function */
static rt_err_t rt_stm32_eth_init(rt_device_t dev)
{
    ETH_MACConfigTypeDef MACConf;
    uint32_t regvalue = 0;
    uint8_t  status = RT_EOK;


    /* ETHERNET Configuration */
    EthHandle.Instance = ETH;
    EthHandle.Init.MACAddr = (rt_uint8_t *)&stm32_eth_device.dev_addr[0];
    EthHandle.Init.MediaInterface = HAL_ETH_RMII_MODE;
    EthHandle.Init.TxDesc = DMATxDscrTab;
    EthHandle.Init.RxDesc = DMARxDscrTab;
    EthHandle.Init.RxBuffLen = ETH_MAX_PACKET_SIZE;

    SCB_InvalidateDCache();

    HAL_ETH_DeInit(&EthHandle);

    /* configure ethernet peripheral (GPIOs, clocks, MAC, DMA) */
    if (HAL_ETH_Init(&EthHandle) != HAL_OK)
    {
        LOG_E("eth hardware init failed");
    }
    else
    {
        LOG_D("eth hardware init success");
    }

    phy_reset();

    rt_memset(&TxConfig, 0, sizeof(ETH_TxPacketConfig));
    TxConfig.Attributes   = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
    TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
    TxConfig.CRCPadCtrl   = ETH_CRC_PAD_INSERT;

    HAL_ETH_SetMDIOClockRange(&EthHandle);

    PHY_ADDR = BSP_ETH_PHY_ADDR;

    /* soft reset */
     if(HAL_ETH_WritePHYRegister(&EthHandle, PHY_ADDR, PHY_BASIC_CONTROL_REG, PHY_RESET_MASK) == HAL_OK)
     {
         HAL_ETH_ReadPHYRegister(&EthHandle, PHY_ADDR, PHY_BASIC_CONTROL_REG, &regvalue);

         uint32_t tickstart = rt_tick_get();

         /* wait until software reset is done or timeout occured  */
         while(regvalue & PHY_RESET_MASK)
         {
           if((rt_tick_get() - tickstart) <= 500)
           {
             if(HAL_ETH_ReadPHYRegister(&EthHandle, PHY_ADDR, PHY_BASIC_CONTROL_REG, &regvalue) != HAL_OK)
             {
               status = RT_ERROR;
               break;
             }
           }
           else
           {
             status = RT_ETIMEOUT;
           }
         }
     }

    rt_thread_delay(2000);

    /* Enable automatic negotiation */
     if(HAL_ETH_ReadPHYRegister(&EthHandle, PHY_ADDR, PHY_BASIC_CONTROL_REG, &regvalue) == HAL_OK)
     {
         regvalue |= PHY_AUTO_NEGOTIATION_MASK;
         HAL_ETH_WritePHYRegister(&EthHandle, PHY_ADDR, PHY_BASIC_CONTROL_REG, regvalue);

         eth_device_linkchange(&stm32_eth_device.parent, RT_TRUE);
         HAL_ETH_GetMACConfig(&EthHandle, &MACConf);
         MACConf.DuplexMode = ETH_FULLDUPLEX_MODE;
         MACConf.Speed = ETH_SPEED_100M;
         HAL_ETH_SetMACConfig(&EthHandle, &MACConf);

         HAL_ETH_Start_IT(&EthHandle);
         SCB_CleanInvalidateDCache_by_Addr(&DMARxDscrTab, ETH_RX_DESC_CNT * sizeof(ETH_DMADescTypeDef));
     }
     else
     {
         status = RT_ERROR;
     }

    return status;
}

static rt_err_t rt_stm32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("emac open");
    return RT_EOK;
}

static rt_err_t rt_stm32_eth_close(rt_device_t dev)
{
    LOG_D("emac close");
    return RT_EOK;
}

static rt_ssize_t rt_stm32_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("emac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_stm32_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("emac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_stm32_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args) rt_memcpy(args, stm32_eth_device.dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* ethernet device interface */
/* transmit data*/
rt_err_t rt_stm32_eth_tx(rt_device_t dev, struct pbuf *p)
{
    rt_err_t ret = RT_ERROR;
    HAL_StatusTypeDef state;
    uint32_t i = 0, framelen = 0;
    struct pbuf *q;
    ETH_BufferTypeDef Txbuffer[ETH_TX_DESC_CNT] = {0};

    rt_memset(Txbuffer, 0, ETH_TX_DESC_CNT * sizeof(ETH_BufferTypeDef));

    for (q = p; q != NULL; q = q->next)
    {
        if (i >= ETH_TX_DESC_CNT)
            return ERR_IF;

        Txbuffer[i].buffer = q->payload;
        Txbuffer[i].len = q->len;
        framelen += q->len;

        if (i > 0)
        {
            Txbuffer[i - 1].next = &Txbuffer[i];
        }

        if (q->next == NULL)
        {
            Txbuffer[i].next = NULL;
        }

        i++;
    }

    TxConfig.Length = framelen;
    TxConfig.TxBuffer = Txbuffer;
    TxConfig.pData = p;

#ifdef ETH_TX_DUMP
    rt_kprintf("Tx dump, len= %d\r\n", framelen);
    dump_hex(&Txbuffer[0]);
#endif

    if (stm32_eth_device.parent.link_status)
    {
        SCB_CleanInvalidateDCache();
        state = HAL_ETH_Transmit(&EthHandle, &TxConfig, 1000);
        if (state != HAL_OK)
        {
            LOG_W("eth transmit frame faild: %d", EthHandle.ErrorCode);
            EthHandle.ErrorCode = HAL_ETH_STATE_READY;
            EthHandle.gState = HAL_ETH_STATE_READY;
        }
    }
    else
    {
        LOG_E("eth transmit frame faild, netif not up");
    }
    HAL_ETH_ReleaseTxPacket(&EthHandle);
    ret = ERR_OK;

    return ret;
}

/* receive data*/
struct pbuf *rt_stm32_eth_rx(rt_device_t dev)
{
    uint32_t framelength = 0;
    rt_uint16_t l;
    struct pbuf *p = RT_NULL;
    uint32_t alignedAddr;
    RxBuff_t *pStart = RT_NULL, *q;

    SCB_CleanInvalidateDCache_by_Addr(&DMARxDscrTab, ETH_RX_DESC_CNT * sizeof(ETH_DMADescTypeDef));
    /* Here, pStart actually points to the address of RxBuff_t */
    if(HAL_ETH_ReadData(&EthHandle, (void**)&pStart) == HAL_OK)
    {
        SCB_CleanInvalidateDCache_by_Addr(&DMARxDscrTab, ETH_RX_DESC_CNT * sizeof(ETH_DMADescTypeDef));
        framelength = EthHandle.RxDescList.RxDataLength;
        /* Invalidate data cache for ETH Rx Buffers */
        /* The Rx_Buff pointed to by pStart was already 32 aligned when defined */
        SCB_InvalidateDCache_by_Addr((uint32_t *)pStart->buff, framelength);

        p = pbuf_alloc(PBUF_RAW, framelength, PBUF_RAM);
        if (p != NULL)
        {
            for (q = pStart, l = 0; q != NULL; q = (RxBuff_t *)q->pbuf.next)
            {
                
                rt_memcpy(&(((rt_uint8_t*)(p->payload))[l]), q->buff, q->pbuf.len);
                l = l + q->pbuf.len;
            }
        }
    }

    return p;
}

/* interrupt service routine */
void ETH_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_ETH_IRQHandler(&EthHandle);

    /* leave interrupt */
    rt_interrupt_leave();
}

void HAL_ETH_TxFreeCallback(uint32_t * buff)
{
/* USER CODE BEGIN HAL ETH TxFreeCallback */

  pbuf_free((struct pbuf *)buff);

/* USER CODE END HAL ETH TxFreeCallback */
}

void HAL_ETH_RxLinkCallback(void **pStart, void **pEnd, uint8_t *buff, uint16_t Length)
{
    /* *
     *  ppstart is a member of pRxStart in the descriptor list, here
     *  The address defined as pbuf is also the address of RxBuff_t, and buff is
     *  The address saved by the Ethernet frame. This function is mainly to link the relevant
     *  All the pbuf of * are connected.
     */
    struct pbuf **ppStart = (struct pbuf **)pStart;
    struct pbuf **ppEnd = (struct pbuf **)pEnd;
    struct pbuf *p = NULL;

    /* Get the struct pbuf from the buff address. */
    p = (struct pbuf *)(buff - offsetof(RxBuff_t, buff));
    p->next = NULL;
    p->tot_len = 0;
    p->len = Length;

    /* Chain the buffer. */
    /* Normally, the first time you enter a new package, pstart should be empty */
    if (!*ppStart)
    {
        /* The first buffer sets pstart. */
        *ppStart = p;
    }
    else
    {
        /* Here, "pEnd" points to the "pbuf" that entered the HAL_ETH_RxLinkCallback
         last time, which is also "RX_BUFF_T" */
        (*ppEnd)->next = p;
    }
    /* Set pEnd to the current pbuf */
    *ppEnd  = p;

    /* Update the total length of all the buffers of the chain. Each pbuf in the chain should have its tot_len
    * set to its own length, plus the length of all the following pbufs in the chain. */
    for (p = *ppStart; p != NULL; p = p->next)
    {
        p->tot_len += Length;
    }

    /* Invalidate data cache because Rx DMA's writing to physical memory makes it stale. */
    SCB_InvalidateDCache_by_Addr((uint32_t *)buff, Length);

}

void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
    rt_err_t result;
    result = eth_device_ready(&(stm32_eth_device.parent));
    if (result != RT_EOK)
        LOG_I("RxCpltCallback err = %d", result);
}

void HAL_ETH_ErrorCallback(ETH_HandleTypeDef *heth)
{
    if ((HAL_ETH_GetDMAError(heth) & ETH_DMACSR_RBU) == ETH_DMACSR_RBU)
    {
        LOG_E("eth err:ETH_DMACSR_RBU");
    }

    if((HAL_ETH_GetDMAError(heth) & ETH_DMACSR_TBU) == ETH_DMACSR_TBU)
    {
        LOG_E("eth err:ETH_DMACSR_TBU");
    }
    LOG_E("eth err");
}

void HAL_ETH_RxAllocateCallback(uint8_t **buff)
{

    /* Use the circular buffer index */
    static uint16_t buf_index = 0;

    /* Check the descriptor ownership before updating the index */
    if((DMARxDscrTab[buf_index].DESC3 & ETH_DMARXNDESCRF_OWN) == 0) {
        *buff = Rx_Buff[buf_index].buff;
        buf_index = (buf_index + 1) % ETH_RX_DESC_CNT;
    } else {
        LOG_W("Buffer %d not released!", buf_index);
        *buff = RT_NULL;
    }
}

enum {
    PHY_LINK        = (1 << 0),
    PHY_100M        = (1 << 1),
    PHY_FULL_DUPLEX = (1 << 2),
};

static void phy_linkchange()
{
    static rt_uint8_t phy_speed = 0;
    rt_uint8_t phy_speed_new = 0;
    rt_uint32_t status;

    HAL_ETH_ReadPHYRegister(&EthHandle, PHY_ADDR, PHY_BASIC_STATUS_REG, (uint32_t *)&status);
    LOG_D("phy basic status reg is 0x%X", status);

    /* If the automatic negotiation is completed or the connection is established */
    if (status & (PHY_AUTONEGO_COMPLETE_MASK | PHY_LINKED_STATUS_MASK))
    {
        rt_uint32_t SR = 0;



        /* Read the special status register to check the network speed and duplex status */
        HAL_ETH_ReadPHYRegister(&EthHandle, PHY_ADDR, PHY_Status_REG, (uint32_t *)&SR);
        LOG_D("phy control status reg is 0x%X", SR);

        if(PHY_Status_LINK_UP(SR))
        {
            phy_speed_new |= PHY_LINK;
        }

        if (PHY_Status_SPEED_100M(SR))
        {
            phy_speed_new |= PHY_100M;
        }

        if (PHY_Status_FULL_DUPLEX(SR))
        {
            phy_speed_new |= PHY_FULL_DUPLEX;
        }
    }

    /* If the link is on or 100 megabits, it is in full-duplex mode and ready to be set up */
    if (phy_speed != phy_speed_new)
    {
        phy_speed = phy_speed_new;

        /* Link establishment */
        if (phy_speed & PHY_LINK)
        {
            LOG_D("link up");
            if (phy_speed & PHY_100M)
            {
                LOG_D("100Mbps");
                stm32_eth_device.ETH_Speed = ETH_SPEED_100M;
            }
            else
            {
                stm32_eth_device.ETH_Speed = ETH_SPEED_10M;
                LOG_D("10Mbps");
            }

            if (phy_speed & PHY_FULL_DUPLEX)
            {
                LOG_D("full-duplex");
                stm32_eth_device.ETH_Mode = ETH_FULLDUPLEX_MODE;
            }
            else
            {
                LOG_D("half-duplex");
                stm32_eth_device.ETH_Mode = ETH_HALFDUPLEX_MODE;
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
}

#ifdef PHY_USING_INTERRUPT_MODE
static void eth_phy_isr(void *args)
{
    rt_uint32_t status = 0;

    HAL_ETH_ReadPHYRegister(&EthHandle, PHY_ADDR, PHY_INTERRUPT_FLAG_REG, (uint32_t *)&status);
    LOG_D("phy interrupt status reg is 0x%X", status);

    phy_linkchange();
}
#endif /* PHY_USING_INTERRUPT_MODE */

static void phy_monitor_thread_entry(void *parameter)
{
    phy_linkchange();
#ifdef PHY_USING_INTERRUPT_MODE
    /* configuration intterrupt pin */
    rt_pin_mode(PHY_INT_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(PHY_INT_PIN, PIN_IRQ_MODE_FALLING, eth_phy_isr, (void *)"callbackargs");
    rt_pin_irq_enable(PHY_INT_PIN, PIN_IRQ_ENABLE);

    /* enable phy interrupt */
    HAL_ETH_WritePHYRegister(&EthHandle, PHY_ADDR, PHY_INTERRUPT_MASK_REG, PHY_INT_MASK);
#if defined(PHY_INTERRUPT_CTRL_REG)
    HAL_ETH_WritePHYRegister(&EthHandle, PHY_ADDR, PHY_INTERRUPT_CTRL_REG, PHY_INTERRUPT_EN);
#endif
#else /* PHY_USING_INTERRUPT_MODE */
    stm32_eth_device.poll_link_timer = rt_timer_create("phylnk", (void (*)(void*))phy_linkchange,
                                        NULL, RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC);
    if (!stm32_eth_device.poll_link_timer || rt_timer_start(stm32_eth_device.poll_link_timer) != RT_EOK)
    {
        LOG_E("Start link change detection timer failed");
    }
#endif /* PHY_USING_INTERRUPT_MODE */
}

/* Register the EMAC device */
static int rt_hw_stm32_eth_init(void)
{
    rt_err_t state = RT_EOK;
    reset_pin = rt_pin_get(ETH_RESET_PIN);

    rt_pin_mode(reset_pin, PIN_MODE_OUTPUT);
    rt_pin_write(reset_pin, PIN_HIGH);

    stm32_eth_device.ETH_Speed = ETH_SPEED_100M;
    stm32_eth_device.ETH_Mode = ETH_FULLDUPLEX_MODE;

    /* OUI 00-80-E1 STMICROELECTRONICS. */
    stm32_eth_device.dev_addr[0] = 0x00;
    stm32_eth_device.dev_addr[1] = 0x80;
    stm32_eth_device.dev_addr[2] = 0xE1;
    /* generate MAC addr from 96bit unique ID (only for test). */
    stm32_eth_device.dev_addr[3] = *(rt_uint8_t *)(UID_BASE + 4);
    stm32_eth_device.dev_addr[4] = *(rt_uint8_t *)(UID_BASE + 2);
    stm32_eth_device.dev_addr[5] = *(rt_uint8_t *)(UID_BASE + 0);

    stm32_eth_device.parent.parent.init      = rt_stm32_eth_init;
    stm32_eth_device.parent.parent.open      = rt_stm32_eth_open;
    stm32_eth_device.parent.parent.close     = rt_stm32_eth_close;
    stm32_eth_device.parent.parent.read      = rt_stm32_eth_read;
    stm32_eth_device.parent.parent.write     = rt_stm32_eth_write;
    stm32_eth_device.parent.parent.control   = rt_stm32_eth_control;
    stm32_eth_device.parent.parent.user_data = RT_NULL;

    stm32_eth_device.parent.eth_rx = rt_stm32_eth_rx;
    stm32_eth_device.parent.eth_tx = rt_stm32_eth_tx;

    /* register eth device */
    /* The device name format of netif is rtthread_e0, and the first two characters are taken */
    state = eth_device_init(&(stm32_eth_device.parent), "e0");
    if (RT_EOK == state)
    {
        LOG_D("emac device init success");
    }
    else
    {
        LOG_E("emac device init faild: %d", state);
        state = -RT_ERROR;
    }

    /* start phy monitor */
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
        state = -RT_ERROR;
    }

    return state;
}
INIT_DEVICE_EXPORT(rt_hw_stm32_eth_init);

#endif /* BSP_USING_ETH */
