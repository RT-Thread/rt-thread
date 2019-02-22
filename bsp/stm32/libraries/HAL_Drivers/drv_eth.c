/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-19     SummerGift   first version
 * 2018-12-25     zylx         fix some bugs
 */

#include "board.h"
#include "drv_config.h"
#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "drv_eth.h"

/*
* Emac driver uses CubeMX tool to generate emac and phy's configuration,
* the configuration files can be found in CubeMX_Config floder.
*/

/* debug option */
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP
//#define DRV_DEBUG
#define LOG_TAG             "drv.emac"
#include <drv_log.h>

#define MAX_ADDR_LEN 6

struct rt_stm32_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;

    /* interface address info, hw address */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];
    /* ETH_Speed */
    uint32_t    ETH_Speed;
    /* ETH_Duplex_Mode */
    uint32_t    ETH_Mode;
};

static ETH_DMADescTypeDef *DMARxDscrTab, *DMATxDscrTab;
static rt_uint8_t *Rx_Buff, *Tx_Buff;
static rt_bool_t tx_is_waiting = RT_FALSE;
static  ETH_HandleTypeDef EthHandle;
static struct rt_stm32_eth stm32_eth_device;
static struct rt_semaphore tx_wait;

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

extern void phy_reset(void);
/* EMAC initialization function */
static rt_err_t rt_stm32_eth_init(rt_device_t dev)
{
    __HAL_RCC_ETH_CLK_ENABLE();

    phy_reset();

    /* ETHERNET Configuration */
    EthHandle.Instance = ETH;
    EthHandle.Init.MACAddr = (rt_uint8_t *)&stm32_eth_device.dev_addr[0];
    EthHandle.Init.AutoNegotiation = ETH_AUTONEGOTIATION_DISABLE;
    EthHandle.Init.Speed = ETH_SPEED_100M;
    EthHandle.Init.DuplexMode = ETH_MODE_FULLDUPLEX;
    EthHandle.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;
    EthHandle.Init.RxMode = ETH_RXINTERRUPT_MODE;
    EthHandle.Init.ChecksumMode = ETH_CHECKSUM_BY_SOFTWARE;

    HAL_ETH_DeInit(&EthHandle);

    /* configure ethernet peripheral (GPIOs, clocks, MAC, DMA) */
    if (HAL_ETH_Init(&EthHandle) != HAL_OK)
    {
        LOG_E("eth hardware init failed");
        return -RT_ERROR;
    }
    else
    {
        LOG_D("eth hardware init success");
    }

    /* Initialize Tx Descriptors list: Chain Mode */
    HAL_ETH_DMATxDescListInit(&EthHandle, DMATxDscrTab, Tx_Buff, ETH_TXBUFNB);

    /* Initialize Rx Descriptors list: Chain Mode  */
    HAL_ETH_DMARxDescListInit(&EthHandle, DMARxDscrTab, Rx_Buff, ETH_RXBUFNB);

    /* ETH interrupt Init */
    HAL_NVIC_SetPriority(ETH_IRQn, 0x07, 0);
    HAL_NVIC_EnableIRQ(ETH_IRQn);

    /* Enable MAC and DMA transmission and reception */
    if (HAL_ETH_Start(&EthHandle) == HAL_OK)
    {
        LOG_D("emac hardware start");
    }
    else
    {
        LOG_E("emac hardware start faild");
        return -RT_ERROR;
    }

    return RT_EOK;
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
    struct pbuf *q;
    uint8_t *buffer = (uint8_t *)(EthHandle.TxDesc->Buffer1Addr);
    __IO ETH_DMADescTypeDef *DmaTxDesc;
    uint32_t framelength = 0;
    uint32_t bufferoffset = 0;
    uint32_t byteslefttocopy = 0;
    uint32_t payloadoffset = 0;

    DmaTxDesc = EthHandle.TxDesc;
    bufferoffset = 0;

    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    while ((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
    {
        rt_err_t result;
        rt_uint32_t level;

        level = rt_hw_interrupt_disable();
        tx_is_waiting = RT_TRUE;
        rt_hw_interrupt_enable(level);

        /* it's own bit set, wait it */
        result = rt_sem_take(&tx_wait, RT_WAITING_FOREVER);
        if (result == RT_EOK) break;
        if (result == -RT_ERROR) return -RT_ERROR;
    }

    /* copy frame from pbufs to driver buffers */
    for (q = p; q != NULL; q = q->next)
    {
        /* Is this buffer available? If not, goto error */
        if ((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
        {
            LOG_E("buffer not valid");
            ret = ERR_USE;
            goto error;
        }

        /* Get bytes in current lwIP buffer */
        byteslefttocopy = q->len;
        payloadoffset = 0;

        /* Check if the length of data to copy is bigger than Tx buffer size*/
        while ((byteslefttocopy + bufferoffset) > ETH_TX_BUF_SIZE)
        {
            /* Copy data to Tx buffer*/
            memcpy((uint8_t *)((uint8_t *)buffer + bufferoffset), (uint8_t *)((uint8_t *)q->payload + payloadoffset), (ETH_TX_BUF_SIZE - bufferoffset));

            /* Point to next descriptor */
            DmaTxDesc = (ETH_DMADescTypeDef *)(DmaTxDesc->Buffer2NextDescAddr);

            /* Check if the buffer is available */
            if ((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET)
            {
                LOG_E("dma tx desc buffer is not valid");
                ret = ERR_USE;
                goto error;
            }

            buffer = (uint8_t *)(DmaTxDesc->Buffer1Addr);

            byteslefttocopy = byteslefttocopy - (ETH_TX_BUF_SIZE - bufferoffset);
            payloadoffset = payloadoffset + (ETH_TX_BUF_SIZE - bufferoffset);
            framelength = framelength + (ETH_TX_BUF_SIZE - bufferoffset);
            bufferoffset = 0;
        }

        /* Copy the remaining bytes */
        memcpy((uint8_t *)((uint8_t *)buffer + bufferoffset), (uint8_t *)((uint8_t *)q->payload + payloadoffset), byteslefttocopy);
        bufferoffset = bufferoffset + byteslefttocopy;
        framelength = framelength + byteslefttocopy;
    }

#ifdef ETH_TX_DUMP
    dump_hex(buffer, p->tot_len);
#endif

    /* Prepare transmit descriptors to give to DMA */
    /* TODO Optimize data send speed*/
    LOG_D("transmit frame lenth :%d", framelength);

    /* wait for unlocked */
    while (EthHandle.Lock == HAL_LOCKED);

    state = HAL_ETH_TransmitFrame(&EthHandle, framelength);
    if (state != HAL_OK)
    {
        LOG_E("eth transmit frame faild: %d", state);
    }

    ret = ERR_OK;

error:

    /* When Transmit Underflow flag is set, clear it and issue a Transmit Poll Demand to resume transmission */
    if ((EthHandle.Instance->DMASR & ETH_DMASR_TUS) != (uint32_t)RESET)
    {
        /* Clear TUS ETHERNET DMA flag */
        EthHandle.Instance->DMASR = ETH_DMASR_TUS;

        /* Resume DMA transmission*/
        EthHandle.Instance->DMATPDR = 0;
    }

    return ret;
}

/* receive data*/
struct pbuf *rt_stm32_eth_rx(rt_device_t dev)
{

    struct pbuf *p = NULL;
    struct pbuf *q = NULL;
    HAL_StatusTypeDef state;
    uint16_t len = 0;
    uint8_t *buffer;
    __IO ETH_DMADescTypeDef *dmarxdesc;
    uint32_t bufferoffset = 0;
    uint32_t payloadoffset = 0;
    uint32_t byteslefttocopy = 0;
    uint32_t i = 0;

    /* Get received frame */
    state = HAL_ETH_GetReceivedFrame_IT(&EthHandle);
    if (state != HAL_OK)
    {
        LOG_D("receive frame faild");
        return NULL;
    }

    /* Obtain the size of the packet and put it into the "len" variable. */
    len = EthHandle.RxFrameInfos.length;
    buffer = (uint8_t *)EthHandle.RxFrameInfos.buffer;

    LOG_D("receive frame len : %d", len);

    if (len > 0)
    {
        /* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    }

#ifdef ETH_RX_DUMP
    dump_hex(buffer, p->tot_len);
#endif

    if (p != NULL)
    {
        dmarxdesc = EthHandle.RxFrameInfos.FSRxDesc;
        bufferoffset = 0;
        for (q = p; q != NULL; q = q->next)
        {
            byteslefttocopy = q->len;
            payloadoffset = 0;

            /* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size*/
            while ((byteslefttocopy + bufferoffset) > ETH_RX_BUF_SIZE)
            {
                /* Copy data to pbuf */
                memcpy((uint8_t *)((uint8_t *)q->payload + payloadoffset), (uint8_t *)((uint8_t *)buffer + bufferoffset), (ETH_RX_BUF_SIZE - bufferoffset));

                /* Point to next descriptor */
                dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
                buffer = (uint8_t *)(dmarxdesc->Buffer1Addr);

                byteslefttocopy = byteslefttocopy - (ETH_RX_BUF_SIZE - bufferoffset);
                payloadoffset = payloadoffset + (ETH_RX_BUF_SIZE - bufferoffset);
                bufferoffset = 0;
            }
            /* Copy remaining data in pbuf */
            memcpy((uint8_t *)((uint8_t *)q->payload + payloadoffset), (uint8_t *)((uint8_t *)buffer + bufferoffset), byteslefttocopy);
            bufferoffset = bufferoffset + byteslefttocopy;
        }
    }

    /* Release descriptors to DMA */
    /* Point to first descriptor */
    dmarxdesc = EthHandle.RxFrameInfos.FSRxDesc;
    /* Set Own bit in Rx descriptors: gives the buffers back to DMA */
    for (i = 0; i < EthHandle.RxFrameInfos.SegCount; i++)
    {
        dmarxdesc->Status |= ETH_DMARXDESC_OWN;
        dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
    }

    /* Clear Segment_Count */
    EthHandle.RxFrameInfos.SegCount = 0;

    /* When Rx Buffer unavailable flag is set: clear it and resume reception */
    if ((EthHandle.Instance->DMASR & ETH_DMASR_RBUS) != (uint32_t)RESET)
    {
        /* Clear RBUS ETHERNET DMA flag */
        EthHandle.Instance->DMASR = ETH_DMASR_RBUS;
        /* Resume DMA reception */
        EthHandle.Instance->DMARPDR = 0;
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

void HAL_ETH_TxCpltCallback(ETH_HandleTypeDef *heth)
{
    if (tx_is_waiting == RT_TRUE)
    {
        tx_is_waiting = RT_FALSE;
        rt_sem_release(&tx_wait);
    }
}

void HAL_ETH_RxCpltCallback(ETH_HandleTypeDef *heth)
{
    rt_err_t result;
    result = eth_device_ready(&(stm32_eth_device.parent));
    if (result != RT_EOK)
        LOG_E("RX err = %d", result);
}

void HAL_ETH_ErrorCallback(ETH_HandleTypeDef *heth)
{
    LOG_E("eth err");
}

#ifdef PHY_USING_INTERRUPT_MODE
static void eth_phy_isr(void *args)
{
    rt_uint32_t status = 0;
    static rt_uint8_t link_status = 1;

    HAL_ETH_ReadPHYRegister(&EthHandle, PHY_INTERRUPT_FLAG_REG, (uint32_t *)&status);
    LOG_D("phy interrupt status reg is 0x%X", status);
    HAL_ETH_ReadPHYRegister(&EthHandle, PHY_BASIC_STATUS_REG, (uint32_t *)&status);
    LOG_D("phy basic status reg is 0x%X", status);

    if (status & PHY_LINKED_STATUS_MASK)
    {
        if (link_status == 0)
        {
            link_status = 1;
            LOG_D("link up");
            /* send link up. */
            eth_device_linkchange(&stm32_eth_device.parent, RT_TRUE);
        }
    }
    else
    {
        if (link_status == 1)
        {
            link_status = 0;
            LOG_I("link down");
            /* send link down. */
            eth_device_linkchange(&stm32_eth_device.parent, RT_FALSE);
        }
    }
}
#endif /* PHY_USING_INTERRUPT_MODE */

static uint8_t phy_speed = 0;
#define PHY_LINK_MASK       (1<<0)
static void phy_monitor_thread_entry(void *parameter)
{
    uint8_t phy_addr = 0xFF;
    uint8_t phy_speed_new = 0;
    rt_uint32_t status = 0;

    /* phy search */
    rt_uint32_t i, temp;
    for (i = 0; i <= 0x1F; i++)
    {
        EthHandle.Init.PhyAddress = i;

        HAL_ETH_ReadPHYRegister(&EthHandle, PHY_ID1_REG, (uint32_t *)&temp);

        if (temp != 0xFFFF && temp != 0x00)
        {
            phy_addr = i;
            break;
        }
    }

    if (phy_addr == 0xFF)
    {
        LOG_E("phy not probe!");
        return;
    }
    else
    {
        LOG_D("found a phy, address:0x%02X", phy_addr);
    }

    /* RESET PHY */
    LOG_D("RESET PHY!");
    HAL_ETH_WritePHYRegister(&EthHandle, PHY_BASIC_CONTROL_REG, PHY_RESET_MASK);
    rt_thread_mdelay(2000);
    HAL_ETH_WritePHYRegister(&EthHandle, PHY_BASIC_CONTROL_REG, PHY_AUTO_NEGOTIATION_MASK);

    while (1)
    {
        HAL_ETH_ReadPHYRegister(&EthHandle, PHY_BASIC_STATUS_REG, (uint32_t *)&status);
        LOG_D("PHY BASIC STATUS REG:0x%04X", status);

        phy_speed_new = 0;

        if (status & (PHY_AUTONEGO_COMPLETE_MASK | PHY_LINKED_STATUS_MASK))
        {
            rt_uint32_t SR;

            phy_speed_new = PHY_LINK_MASK;

            SR = HAL_ETH_ReadPHYRegister(&EthHandle, PHY_Status_REG, (uint32_t *)&SR);
            LOG_D("PHY Control/Status REG:0x%04X ", SR);

            if (SR & PHY_100M_MASK)
            {
                phy_speed_new |= PHY_100M_MASK;
            }
            else if (SR & PHY_10M_MASK)
            {
                phy_speed_new |= PHY_10M_MASK;
            }

            if (SR & PHY_FULL_DUPLEX_MASK)
            {
                phy_speed_new |= PHY_FULL_DUPLEX_MASK;
            }
        }

        /* linkchange */
        if (phy_speed_new != phy_speed)
        {
            if (phy_speed_new & PHY_LINK_MASK)
            {
                LOG_D("link up ");

                if (phy_speed_new & PHY_100M_MASK)
                {
                    LOG_D("100Mbps");
                    stm32_eth_device.ETH_Speed = ETH_SPEED_100M;
                }
                else
                {
                    stm32_eth_device.ETH_Speed = ETH_SPEED_10M;
                    LOG_D("10Mbps");
                }

                if (phy_speed_new & PHY_FULL_DUPLEX_MASK)
                {
                    LOG_D("full-duplex");
                    stm32_eth_device.ETH_Mode = ETH_MODE_FULLDUPLEX;
                }
                else
                {
                    LOG_D("half-duplex");
                    stm32_eth_device.ETH_Mode = ETH_MODE_HALFDUPLEX;
                }

                /* send link up. */
                eth_device_linkchange(&stm32_eth_device.parent, RT_TRUE);

#ifdef PHY_USING_INTERRUPT_MODE
                /* configuration intterrupt pin */
                rt_pin_mode(PHY_INT_PIN, PIN_MODE_INPUT_PULLUP);
                rt_pin_attach_irq(PHY_INT_PIN, PIN_IRQ_MODE_FALLING, eth_phy_isr, (void *)"callbackargs");
                rt_pin_irq_enable(PHY_INT_PIN, PIN_IRQ_ENABLE);

                /* enable phy interrupt */
                HAL_ETH_WritePHYRegister(&EthHandle, PHY_INTERRUPT_MSAK_REG, PHY_INT_MASK);

                break;
#endif
            } /* link up. */
            else
            {
                LOG_I("link down");
                /* send link down. */
                eth_device_linkchange(&stm32_eth_device.parent, RT_FALSE);
            }
            phy_speed = phy_speed_new;
        }

        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

/* Register the EMAC device */
static int rt_hw_stm32_eth_init(void)
{
    rt_err_t state = RT_EOK;

    /* Prepare receive and send buffers */
    Rx_Buff = (rt_uint8_t *)rt_calloc(ETH_RXBUFNB, ETH_MAX_PACKET_SIZE);
    if (Rx_Buff == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }

    Tx_Buff = (rt_uint8_t *)rt_calloc(ETH_TXBUFNB, ETH_MAX_PACKET_SIZE);
    if (Rx_Buff == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }

    DMARxDscrTab = (ETH_DMADescTypeDef *)rt_calloc(ETH_RXBUFNB, sizeof(ETH_DMADescTypeDef));
    if (DMARxDscrTab == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }

    DMATxDscrTab = (ETH_DMADescTypeDef *)rt_calloc(ETH_TXBUFNB, sizeof(ETH_DMADescTypeDef));
    if (DMATxDscrTab == RT_NULL)
    {
        LOG_E("No memory");
        state = -RT_ENOMEM;
        goto __exit;
    }

    stm32_eth_device.ETH_Speed = ETH_SPEED_100M;
    stm32_eth_device.ETH_Mode  = ETH_MODE_FULLDUPLEX;

    /* OUI 00-80-E1 STMICROELECTRONICS. */
    stm32_eth_device.dev_addr[0] = 0x00;
    stm32_eth_device.dev_addr[1] = 0x80;
    stm32_eth_device.dev_addr[2] = 0xE1;
    /* generate MAC addr from 96bit unique ID (only for test). */
    stm32_eth_device.dev_addr[3] = *(rt_uint8_t *)(UID_BASE + 4);
    stm32_eth_device.dev_addr[4] = *(rt_uint8_t *)(UID_BASE + 2);
    stm32_eth_device.dev_addr[5] = *(rt_uint8_t *)(UID_BASE + 0);

    stm32_eth_device.parent.parent.init       = rt_stm32_eth_init;
    stm32_eth_device.parent.parent.open       = rt_stm32_eth_open;
    stm32_eth_device.parent.parent.close      = rt_stm32_eth_close;
    stm32_eth_device.parent.parent.read       = rt_stm32_eth_read;
    stm32_eth_device.parent.parent.write      = rt_stm32_eth_write;
    stm32_eth_device.parent.parent.control    = rt_stm32_eth_control;
    stm32_eth_device.parent.parent.user_data  = RT_NULL;

    stm32_eth_device.parent.eth_rx     = rt_stm32_eth_rx;
    stm32_eth_device.parent.eth_tx     = rt_stm32_eth_tx;

    /* init tx semaphore */
    rt_sem_init(&tx_wait, "tx_wait", 0, RT_IPC_FLAG_FIFO);
    LOG_D("initialize tx wait semaphore");

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
        goto __exit;
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
__exit:
    if (state != RT_EOK)
    {
        if (Rx_Buff)
        {
            rt_free(Rx_Buff);
        }

        if (Tx_Buff)
        {
            rt_free(Tx_Buff);
        }

        if (DMARxDscrTab)
        {
            rt_free(DMARxDscrTab);
        }

        if (DMATxDscrTab)
        {
            rt_free(DMATxDscrTab);
        }
    }

    return state;
}
INIT_APP_EXPORT(rt_hw_stm32_eth_init);
