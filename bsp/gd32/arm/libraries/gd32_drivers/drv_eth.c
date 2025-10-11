/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-25     MaiHuanyi    first version
 */

#include "drv_eth.h"
#include <netif/ethernetif.h>
#include <lwipopts.h>

/* debug option */
//#define ETH_RX_DUMP
//#define ETH_TX_DUMP
//#define DRV_DEBUG
#define LOG_TAG             "drv.emac"
#include <drv_log.h>

#define MAX_ADDR_LEN 6

#undef PHY_FULL_DUPLEX
#define PHY_LINK         (1 << 0)
#define PHY_100M         (1 << 1)
#define PHY_FULL_DUPLEX  (1 << 2)

struct rt_gd32_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;
    rt_timer_t poll_link_timer;
    /* interface address info, hw address */
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
    /* eth_speed */
    rt_uint32_t eth_speed;
    /* ETH_Duplex_Mode */
    rt_uint32_t eth_mode;
    rt_uint8_t phy_addr;
};

static struct rt_gd32_eth gd32_eth_device;

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

static void gd32_eth_gpio_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOG);

    gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_8);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_8);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_8);
    
    /* enable SYSCFG clock */
    rcu_periph_clock_enable(RCU_SYSCFG);

    /* choose DIV2 to get 50MHz from 200MHz on CKOUT0 pin (PA8) to clock the PHY */
    rcu_ckout0_config(RCU_CKOUT0SRC_PLLP, RCU_CKOUT0_DIV4);
    syscfg_enet_phy_interface_config(SYSCFG_ENET_PHY_RMII);

    /* PA1: ETH_RMII_REF_CLK */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_1);

    /* PA2: ETH_MDIO */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_2);

    /* PA7: ETH_RMII_CRS_DV */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_7);

    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_1);
    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_2);
    gpio_af_set(GPIOA, GPIO_AF_11, GPIO_PIN_7);

    /* PG11: ETH_RMII_TX_EN */
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_11);

    /* PG13: ETH_RMII_TXD0 */
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_13);

    /* PG14: ETH_RMII_TXD1 */
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_14);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_14);

    gpio_af_set(GPIOG, GPIO_AF_11, GPIO_PIN_11);
    gpio_af_set(GPIOG, GPIO_AF_11, GPIO_PIN_13);
    gpio_af_set(GPIOG, GPIO_AF_11, GPIO_PIN_14);

    /* PC1: ETH_MDC */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_1);

    /* PC4: ETH_RMII_RXD0 */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_4);

    /* PC5: ETH_RMII_RXD1 */
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MAX, GPIO_PIN_5);

    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_1);
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_4);
    gpio_af_set(GPIOC, GPIO_AF_11, GPIO_PIN_5);
}

/* EMAC initialization function */
static rt_err_t rt_gd32_eth_init(rt_device_t dev)
{
    ErrStatus status = ERROR;

    /* check till phy detected */
    while(gd32_eth_device.phy_addr == 0xFF)
    {
        rt_thread_mdelay(1000);
    }

    /* reset ethernet on AHB bus */
    enet_deinit();

    status = enet_software_reset();
    if(ERROR == status) {
        LOG_E("enet software reset failed!");
        while (1);
    }

    status = enet_init(ENET_AUTO_NEGOTIATION, ENET_NO_AUTOCHECKSUM, ENET_BROADCAST_FRAMES_PASS);
    if (status != SUCCESS)
    {
        LOG_D("enet init failed!");
        goto exit;
    }

    /* ETH interrupt Init */
    enet_interrupt_enable(ENET_DMA_INT_NIE);
    enet_interrupt_enable(ENET_DMA_INT_RIE);

    /* initialize MAC address in ethernet MAC */
    enet_mac_address_set(ENET_MAC_ADDRESS0, gd32_eth_device.dev_addr);

    enet_descriptors_chain_init(ENET_DMA_TX);
    enet_descriptors_chain_init(ENET_DMA_RX);

    /* ENET RxDMA/TxDMA descriptor */
    extern enet_descriptors_struct  rxdesc_tab[ENET_RXBUF_NUM], txdesc_tab[ENET_TXBUF_NUM];

    /* enable ethernet Rx interrrupt */
    for (int i = 0; i < ENET_RXBUF_NUM; i++)
    {
        enet_rx_desc_immediate_receive_complete_interrupt(&rxdesc_tab[i]);
    }

    /* initialize descriptors list: chain/ring mode */
    for (int i = 0; i < ENET_TXBUF_NUM; i++)
    {
        enet_transmit_checksum_config(&txdesc_tab[i], ENET_CHECKSUM_TCPUDPICMP_FULL);
    }

    nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
    nvic_irq_enable(ENET_IRQn, 7, 0);

    /* enable MAC and DMA transmission and reception */
    enet_enable();

exit:
    if (status == SUCCESS)
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

static rt_err_t rt_gd32_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("emac open");
    return RT_EOK;
}

static rt_err_t rt_gd32_eth_close(rt_device_t dev)
{
    LOG_D("emac close");
    return RT_EOK;
}

static rt_ssize_t rt_gd32_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    LOG_D("emac read");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t rt_gd32_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    LOG_D("emac write");
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t rt_gd32_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args)
        {
            SMEMCPY(args, gd32_eth_device.dev_addr, 6);
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
rt_err_t rt_gd32_eth_tx(rt_device_t dev, struct pbuf *p)
{
    rt_err_t ret = -RT_ERROR;
    struct pbuf *q;
    int framelength = 0;
    uint32_t bufferoffset = 0;
    uint32_t byteslefttocopy = 0;
    uint32_t payloadoffset = 0;

    /* global transmit and receive descriptors pointers */
    extern enet_descriptors_struct *dma_current_txdesc;
    enet_descriptors_struct *dma_txdesc = dma_current_txdesc;

    uint8_t *buffer = (uint8_t *)(dma_txdesc->buffer1_addr);

    /* copy frame from pbufs to driver buffers */
    for (q = p; q != NULL; q = q->next)
    {
        /* Is this buffer available? If not, goto error */
        if ((dma_txdesc->status & ENET_TDES0_DAV) != (uint32_t)RESET)
        {
            ret = RT_EOK;
            goto _error;
        }

        /* Get bytes in current lwIP buffer */
        byteslefttocopy = q->len;
        payloadoffset = 0;

        /* Check if the length of data to copy is bigger than Tx buffer size */
        while ((byteslefttocopy + bufferoffset) > ENET_TXBUF_SIZE)
        {
            /* Copy data to Tx buffer*/
            SMEMCPY((uint8_t *)((uint8_t *)buffer + bufferoffset), (uint8_t *)((uint8_t *)q->payload + payloadoffset), (ENET_TXBUF_SIZE - bufferoffset));

            /* Point to next descriptor */
            dma_txdesc = (enet_descriptors_struct *)(dma_txdesc->buffer2_next_desc_addr);

            /* Check if the buffer is available */
            if ((dma_txdesc->status & ENET_TDES0_DAV) != (uint32_t)RESET)
            {
                ret = RT_EOK;
                goto _error;
            }

            buffer = (uint8_t *)(dma_txdesc->buffer1_addr);

            byteslefttocopy = byteslefttocopy - (ENET_TXBUF_SIZE - bufferoffset);
            payloadoffset = payloadoffset + (ENET_TXBUF_SIZE - bufferoffset);
            framelength = framelength + (ENET_TXBUF_SIZE - bufferoffset);
            bufferoffset = 0;
        }

        /* Copy the remaining bytes */
        SMEMCPY((uint8_t *)((uint8_t *)buffer + bufferoffset), (uint8_t *)((uint8_t *)q->payload + payloadoffset), byteslefttocopy);
        framelength = framelength + byteslefttocopy;
    }

    /* transmit descriptors to give to DMA */
    ENET_NOCOPY_FRAME_TRANSMIT(framelength);

#ifdef ETH_TX_DUMP
    dump_hex(buffer, p->tot_len);
#endif

    ret = RT_EOK;

_error:
    return ret;
}

/* receive data*/
struct pbuf *rt_gd32_eth_rx(rt_device_t dev)
{
    struct pbuf *p, *q;
    uint16_t len;
    uint8_t *buffer;
    uint32_t bufferoffset = 0;
    uint32_t payloadoffset = 0;
    uint32_t byteslefttocopy = 0;

    extern enet_descriptors_struct *dma_current_rxdesc;
    enet_descriptors_struct *dma_rxdesc = dma_current_rxdesc;

    p = NULL;

    /* obtain the size of the packet and put it into the "len" variable. */
    len = enet_desc_information_get(dma_rxdesc, RXDESC_FRAME_LENGTH);
    buffer = (uint8_t *)(dma_rxdesc->buffer1_addr);

    if (len > 0)
    {
        /* we allocate a pbuf chain of pbufs from the Lwip buffer pool */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    }

#ifdef ETH_RX_DUMP
    dump_hex(buffer, p->tot_len);
#endif

    if (p != NULL)
    {
        bufferoffset = 0;
        for (q = p; q != NULL; q = q->next)
        {
            byteslefttocopy = q->len;
            payloadoffset = 0;

            /* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size */
            while ((byteslefttocopy + bufferoffset) > ENET_RXBUF_SIZE)
            {
                /* Copy data to pbuf */
                SMEMCPY((uint8_t *)((uint8_t *)q->payload + payloadoffset), (uint8_t *)((uint8_t *)buffer + bufferoffset), (ENET_RXBUF_SIZE - bufferoffset));

                /* Point to next descriptor */
                dma_rxdesc = (enet_descriptors_struct *)(dma_rxdesc->buffer2_next_desc_addr);
                buffer = (uint8_t *)(dma_rxdesc->buffer1_addr);

                byteslefttocopy = byteslefttocopy - (ENET_RXBUF_SIZE - bufferoffset);
                payloadoffset = payloadoffset + (ENET_RXBUF_SIZE - bufferoffset);
                bufferoffset = 0;
            }
            /* Copy remaining data in pbuf */
            SMEMCPY((uint8_t *)((uint8_t *)q->payload + payloadoffset), (uint8_t *)((uint8_t *)buffer + bufferoffset), byteslefttocopy);
            bufferoffset = bufferoffset + byteslefttocopy;
        }
    }

    ENET_NOCOPY_FRAME_RECEIVE();

    return p;
}

/* interrupt service routine */
void ENET_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (enet_interrupt_flag_get(ENET_DMA_INT_FLAG_RS))
    {
        enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_RS_CLR);
        eth_device_ready(&(gd32_eth_device.parent));
    }

    if (enet_interrupt_flag_get(ENET_DMA_INT_FLAG_TS))
    {
        enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_TS_CLR);
    }

    /* clear normal interrupt */
    enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_NI_CLR);

    if (enet_interrupt_flag_get(ENET_DMA_INT_FLAG_AI))
    {
        if (enet_interrupt_flag_get(ENET_DMA_INT_FLAG_RBU))
        {
            enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_RBU_CLR);
        }

        if (enet_interrupt_flag_get(ENET_DMA_INT_FLAG_RO))
        {
            enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_RO_CLR);
        }

        enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_AI_CLR);
    }

    /* leave interrupt */
    rt_interrupt_leave();
}

static void phy_linkchange(void)
{
    static rt_uint8_t phy_speed = 0;
    rt_uint8_t phy_speed_new = 0;
    rt_uint16_t status;

    enet_phy_write_read(ENET_PHY_READ, PHY_ADDRESS, PHY_REG_BSR, &status);
    LOG_D("phy basic status reg is 0x%X", status);

    if (status & (PHY_AUTONEGO_COMPLETE | PHY_LINKED_STATUS))
    {
        rt_uint16_t SR = 0;

        phy_speed_new |= PHY_LINK;

        enet_phy_write_read(ENET_PHY_READ, PHY_ADDRESS, PHY_SR, &SR);
        LOG_D("phy control status reg is 0x%X", SR);

        if ((uint16_t)RESET == (SR & PHY_SPEED_STATUS))
        {
            phy_speed_new |= PHY_100M;
        }

        if ((uint16_t)RESET != (SR & PHY_DUPLEX_STATUS))
        {
            phy_speed_new |= PHY_FULL_DUPLEX;
        }
    }

    if (phy_speed != phy_speed_new)
    {
        phy_speed = phy_speed_new;
        if (phy_speed & PHY_LINK)
        {
            if (phy_speed & PHY_100M)
            {
                LOG_D("100Mbps");
                gd32_eth_device.eth_speed = ENET_SPEEDMODE_100M;
            }
            else
            {
                gd32_eth_device.eth_speed = ENET_SPEEDMODE_10M;
                LOG_D("10Mbps");
            }

            if (phy_speed & PHY_FULL_DUPLEX)
            {
                LOG_D("full-duplex");
                gd32_eth_device.eth_mode = ENET_MODE_FULLDUPLEX;
            }
            else
            {
                LOG_D("half-duplex");
                gd32_eth_device.eth_mode = ENET_MODE_HALFDUPLEX;
            }

            /* send link up. */
            LOG_D("link up");
            eth_device_linkchange(&gd32_eth_device.parent, RT_TRUE);
        }
        else
        {
            LOG_I("link down");
            eth_device_linkchange(&gd32_eth_device.parent, RT_FALSE);
        }
    }
}

static void phy_monitor_thread_entry(void *parameter)
{
    uint8_t phy_addr = 0xFF;
    uint8_t detected_count = 0;
    uint16_t phy_value;

    while(phy_addr == 0xFF)
    {
        /* phy search */
        rt_uint16_t i, temp;
        for (i = 0; i <= 0x1F; i++)
        {
            enet_phy_write_read(ENET_PHY_READ, i, PHY_ID1_REG, (uint16_t *)&temp);

#ifdef PHY_USING_YT8512C
            if (temp != 0xFFFF)
#else
            if (temp != 0xFFFF && temp != 0x00)
#endif /* PHY_USING_YT8512C */
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
    if (phy_addr != PHY_ADDRESS)
    {
        LOG_E("Please rewrite PHY_ADDRESS marco in the gd32f527_enet.h");
        return;
    }

    /* RESET PHY */
    LOG_D("RESET PHY!");
    phy_value = PHY_RESET;
    enet_phy_write_read(ENET_PHY_WRITE, PHY_ADDRESS, PHY_REG_BCR, &phy_value);

    rt_thread_mdelay(1000);

    phy_value = PHY_AUTONEGOTIATION;
    enet_phy_write_read(ENET_PHY_WRITE, PHY_ADDRESS, PHY_REG_BCR, &phy_value);

    gd32_eth_device.phy_addr = phy_addr;
}

/**
  * @brief phy clock config
  */
static void phy_clock_config(void)
{
    uint32_t ahbclk;
    uint32_t reg;

    /* clear the previous MDC clock */
    reg = ENET_MAC_PHY_CTL;
    reg &= ~ENET_MAC_PHY_CTL_CLR;

    /* get the HCLK frequency */
    ahbclk = rcu_clock_freq_get(CK_AHB);

    /* configure MDC clock according to HCLK frequency range */
    if(ENET_RANGE(ahbclk, 20000000U, 35000000U)) {
        reg |= ENET_MDC_HCLK_DIV16;
    } else if(ENET_RANGE(ahbclk, 35000000U, 60000000U)) {
        reg |= ENET_MDC_HCLK_DIV26;
    } else if(ENET_RANGE(ahbclk, 60000000U, 100000000U)) {
        reg |= ENET_MDC_HCLK_DIV42;
    } else if(ENET_RANGE(ahbclk, 100000000U, 150000000U)) {
        reg |= ENET_MDC_HCLK_DIV62;
    } else if((ENET_RANGE(ahbclk, 150000000U, 200000000U)) || (200000000U == ahbclk)) {
        reg |= ENET_MDC_HCLK_DIV102;
    } else {
        LOG_E("ERROR: phy clock configure failed!");
        return;
    }
    ENET_MAC_PHY_CTL = reg;
}

/* Register the EMAC device */
static int rt_hw_gd32_eth_init(void)
{
    rt_err_t state = RT_EOK;

    /* phy clock */
    phy_clock_config();

    /* enable ethernet clock  */
    rcu_periph_clock_enable(RCU_ENET);
    rcu_periph_clock_enable(RCU_ENETTX);
    rcu_periph_clock_enable(RCU_ENETRX);

    gd32_eth_gpio_init();

    gd32_eth_device.eth_speed = ENET_SPEEDMODE_100M;
    gd32_eth_device.eth_mode  = ENET_MODE_FULLDUPLEX;
    gd32_eth_device.phy_addr = 0xFF;

    /* OUI 00-80-E1 STMICROELECTRONICS. */
    gd32_eth_device.dev_addr[0] = 0x00;
    gd32_eth_device.dev_addr[1] = 0x80;
    gd32_eth_device.dev_addr[2] = 0x5A;
    /* generate MAC addr from 96bit unique ID (only for test). */
    gd32_eth_device.dev_addr[3] = *(rt_uint8_t *)(0x1FFF7A10 + 4);
    gd32_eth_device.dev_addr[4] = *(rt_uint8_t *)(0x1FFF7A10 + 2);
    gd32_eth_device.dev_addr[5] = *(rt_uint8_t *)(0x1FFF7A10);

    gd32_eth_device.parent.parent.init       = rt_gd32_eth_init;
    gd32_eth_device.parent.parent.open       = rt_gd32_eth_open;
    gd32_eth_device.parent.parent.close      = rt_gd32_eth_close;
    gd32_eth_device.parent.parent.read       = rt_gd32_eth_read;
    gd32_eth_device.parent.parent.write      = rt_gd32_eth_write;
    gd32_eth_device.parent.parent.control    = rt_gd32_eth_control;
    gd32_eth_device.parent.parent.user_data  = RT_NULL;

    gd32_eth_device.parent.eth_rx     = rt_gd32_eth_rx;
    gd32_eth_device.parent.eth_tx     = rt_gd32_eth_tx;

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

    /* register eth device */
    state = eth_device_init(&(gd32_eth_device.parent), "e0");
    if (state == RT_EOK)
    {
        LOG_D("emac device init success");
    }
    else
    {
        LOG_E("emac device init faild: %d", state);
        state = -RT_ERROR;
        goto __exit;
    }

    gd32_eth_device.poll_link_timer = rt_timer_create("phylnk", (void (*)(void*))phy_linkchange,
                                        NULL, RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC);
    if (!gd32_eth_device.poll_link_timer || rt_timer_start(gd32_eth_device.poll_link_timer) != RT_EOK)
    {
        LOG_E("Start link change detection timer failed");
    }

__exit:
    return state;
}
INIT_DEVICE_EXPORT(rt_hw_gd32_eth_init);
