/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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

#ifdef BSP_USING_ETH_ARTPI

#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "drv_eth.h"

/*
* Emac driver uses CubeMX tool to generate emac and phy's configuration,
* the configuration files can be found in CubeMX_Config folder.
*/

/* debug option */
#define LOG_TAG             "drv.emac"
#include <drv_log.h>

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
    /* ETH_Speed */
    uint32_t    ETH_Speed;
    /* ETH_Duplex_Mode */
    uint32_t    ETH_Mode;
};

static ETH_HandleTypeDef EthHandle;
static ETH_TxPacketConfig TxConfig;
static struct rt_stm32_eth stm32_eth_device;
static uint8_t PHY_ADDR = 0x1F;
static rt_uint32_t reset_pin = 0;

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma location=0x30040000
    ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
    #pragma location=0x30040060
    ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */
    #pragma location=0x30040200
    uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE]; /* Ethernet Receive Buffers */

#elif defined ( __CC_ARM )  /* MDK ARM Compiler */
    __attribute__((at(0x30040000))) ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
    __attribute__((at(0x30040060))) ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */
    __attribute__((at(0x30040200))) uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE]; /* Ethernet Receive Buffer */

#elif defined ( __GNUC__ ) /* GNU Compiler */
    ETH_DMADescTypeDef DMARxDscrTab[ETH_RX_DESC_CNT] __attribute__((section(".RxDecripSection"))); /* Ethernet Rx DMA Descriptors */
    ETH_DMADescTypeDef DMATxDscrTab[ETH_TX_DESC_CNT] __attribute__((section(".TxDecripSection")));   /* Ethernet Tx DMA Descriptors */
    uint8_t Rx_Buff[ETH_RX_DESC_CNT][ETH_MAX_PACKET_SIZE] __attribute__((section(".RxArraySection"))); /* Ethernet Receive Buffers */
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

    __HAL_RCC_D2SRAM3_CLK_ENABLE();

    phy_reset();

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

    rt_memset(&TxConfig, 0, sizeof(ETH_TxPacketConfig));
    TxConfig.Attributes   = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
    TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
    TxConfig.CRCPadCtrl   = ETH_CRC_PAD_INSERT;

    for (int idx = 0; idx < ETH_RX_DESC_CNT; idx++)
    {
        HAL_ETH_DescAssignMemory(&EthHandle, idx, &Rx_Buff[idx][0], NULL);
    }

    HAL_ETH_SetMDIOClockRange(&EthHandle);

    for(int i = 0; i <= PHY_ADDR; i ++)
    {
        if(HAL_ETH_ReadPHYRegister(&EthHandle, i, PHY_SPECIAL_MODES_REG, &regvalue) != HAL_OK)
        {
            status = RT_ERROR;
            /* Can't read from this device address continue with next address */
            continue;
        }

        if((regvalue & PHY_BASIC_STATUS_REG) == i)
        {
            PHY_ADDR = i;
            status = RT_EOK;
            LOG_D("Found a phy, address:0x%02X", PHY_ADDR);
            break;
        }
    }

    if(HAL_ETH_WritePHYRegister(&EthHandle, PHY_ADDR, PHY_BASIC_CONTROL_REG, PHY_RESET_MASK) == HAL_OK)
    {
        HAL_ETH_ReadPHYRegister(&EthHandle, PHY_ADDR, PHY_SPECIAL_MODES_REG, &regvalue);

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

static rt_size_t rt_stm32_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("emac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t rt_stm32_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
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
    ETH_BufferTypeDef Txbuffer[ETH_TX_DESC_CNT];

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

    ret = ERR_OK;

    return ret;
}

/* receive data*/
struct pbuf *rt_stm32_eth_rx(rt_device_t dev)
{
    uint32_t framelength = 0;
    rt_uint16_t l;
    struct pbuf *p = RT_NULL, *q;
    ETH_BufferTypeDef RxBuff;
    uint32_t alignedAddr;

    if(HAL_ETH_GetRxDataBuffer(&EthHandle, &RxBuff) == HAL_OK)
    {
        HAL_ETH_GetRxDataLength(&EthHandle, &framelength);

        /* Build Rx descriptor to be ready for next data reception */
        HAL_ETH_BuildRxDescriptors(&EthHandle);

        /* Invalidate data cache for ETH Rx Buffers */
        alignedAddr = (uint32_t)RxBuff.buffer & ~0x1F;
        SCB_InvalidateDCache_by_Addr((uint32_t *)alignedAddr, (uint32_t)RxBuff.buffer - alignedAddr + framelength);

        p = pbuf_alloc(PBUF_RAW, framelength, PBUF_RAM);

        if (p != NULL)
        {
            for (q = p, l = 0; q != NULL; q = q->next)
            {
                memcpy((rt_uint8_t *)q->payload, (rt_uint8_t *)&RxBuff.buffer[l], q->len);
                l = l + q->len;
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

void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
    rt_err_t result;
    result = eth_device_ready(&(stm32_eth_device.parent));

    if (result != RT_EOK)
        LOG_I("RxCpltCallback err = %d", result);
}

void HAL_ETH_ErrorCallback(ETH_HandleTypeDef *heth)
{
    LOG_E("eth err");
}

enum
{
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

    if (status & (PHY_AUTONEGO_COMPLETE_MASK | PHY_LINKED_STATUS_MASK))
    {
        rt_uint32_t SR = 0;

        phy_speed_new |= PHY_LINK;

        HAL_ETH_ReadPHYRegister(&EthHandle, PHY_ADDR, PHY_Status_REG, (uint32_t *)&SR);
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

#endif /* BSP_USING_ETH_ARTPI */
