
/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-10-30     bigmagic       first version
 */

#include <rtdef.h>
#include <rthw.h>
#include <stdint.h>
#include <rtthread.h>

#ifdef BSP_USING_ETH

#include <lwip/sys.h>
#include <netif/ethernetif.h>
#include <mmu.h>

#include "mbox.h"
#include "raspi4.h"
#include "drv_eth.h"

#define DBG_LEVEL               DBG_LOG
#include <rtdbg.h>
#define LOG_TAG                 "drv.eth"

#define RECV_CACHE_BUF          (2048)
#define SEND_CACHE_BUF          (2048)
#define DMA_DISC_ADDR_SIZE      (2 * 1024 *1024)

#define RX_DESC_BASE            (MAC_REG_BASE_ADDR + GENET_RX_OFF)
#define TX_DESC_BASE            (MAC_REG_BASE_ADDR + GENET_TX_OFF)

#define MAX_ADDR_LEN            (6)

#define upper_32_bits(n)        ((rt_uint32_t)(((n) >> 16) >> 16))
#define lower_32_bits(n)        ((rt_uint32_t)(n))

#define BIT(nr)                 (1UL << (nr))

#define LINK_THREAD_STACK_SIZE  (2048)
#define LINK_THREAD_PRIORITY    (20)
#define LINK_THREAD_TIMESLICE   (10)

static int link_speed = 0;
static int link_flag = 0;

static rt_thread_t link_thread_tid = RT_NULL;

static rt_uint32_t tx_index = 0;
static rt_uint32_t rx_index = 0;
static rt_uint32_t index_flag = 0;


struct rt_eth_dev
{
    struct eth_device parent;
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
    char *name;
    void *iobase;
    int state;
    int index;
    struct rt_timer link_timer;
    void *priv;
};
static struct rt_eth_dev eth_dev;

static struct rt_semaphore send_finsh_sem_lock;

static struct rt_semaphore link_ack;

rt_inline rt_uint32_t read32(void *addr)
{
    return (*((volatile unsigned int *)(addr)));
}

rt_inline void write32(void *addr, rt_uint32_t value)
{
    (*((volatile unsigned int *)(addr))) = value;
}

static void eth_rx_irq(int irq, void *param)
{
    rt_uint32_t val = 0;

    val = read32(MAC_REG_BASE_ADDR + GENET_INTRL2_CPU_STAT);
    val &= ~read32(MAC_REG_BASE_ADDR + GENET_INTRL2_CPU_STAT_MASK);

    write32(MAC_REG_BASE_ADDR + GENET_INTRL2_CPU_CLEAR, val);

    if (val & GENET_IRQ_RXDMA_DONE)
    {
        eth_device_ready(&eth_dev.parent);
    }

    if (val & GENET_IRQ_TXDMA_DONE)
    {
        rt_sem_release(&send_finsh_sem_lock);
    }
}

/* we only support RGMII (as used on the RPi4) */
static int bcmgenet_interface_set(void)
{
    int phy_mode = PHY_INTERFACE_MODE_RGMII;

    switch (phy_mode)
    {
    case PHY_INTERFACE_MODE_RGMII:
    case PHY_INTERFACE_MODE_RGMII_RXID:
        write32(MAC_REG_BASE_ADDR + SYS_PORT_CTRL, PORT_MODE_EXT_GPHY);
        break;
    default:
        rt_kprintf("unknown phy mode: %d\n", MAC_REG_BASE_ADDR);
        return -1;
    }

    return 0;
}

static void bcmgenet_umac_reset(void)
{
    rt_uint32_t reg;

    reg = read32(MAC_REG_BASE_ADDR + SYS_RBUF_FLUSH_CTRL);
    reg |= BIT(1);
    write32((MAC_REG_BASE_ADDR + SYS_RBUF_FLUSH_CTRL), reg);

    reg &= ~BIT(1);
    write32((MAC_REG_BASE_ADDR + SYS_RBUF_FLUSH_CTRL), reg);

    DELAY_MICROS(10);

    write32((MAC_REG_BASE_ADDR + SYS_RBUF_FLUSH_CTRL), 0);
    DELAY_MICROS(10);

    write32(MAC_REG_BASE_ADDR + UMAC_CMD, 0);
    write32(MAC_REG_BASE_ADDR + UMAC_CMD, (CMD_SW_RESET | CMD_LCL_LOOP_EN));
    DELAY_MICROS(2);

    write32(MAC_REG_BASE_ADDR + UMAC_CMD, 0);
    /* clear tx/rx counter */
    write32(MAC_REG_BASE_ADDR + UMAC_MIB_CTRL, MIB_RESET_RX | MIB_RESET_TX | MIB_RESET_RUNT);
    write32(MAC_REG_BASE_ADDR + UMAC_MIB_CTRL, 0);
    write32(MAC_REG_BASE_ADDR + UMAC_MAX_FRAME_LEN, ENET_MAX_MTU_SIZE);

    /* init rx registers, enable ip header optimization */
    reg = read32(MAC_REG_BASE_ADDR + RBUF_CTRL);
    reg |= RBUF_ALIGN_2B;
    write32(MAC_REG_BASE_ADDR + RBUF_CTRL, reg);
    write32(MAC_REG_BASE_ADDR + RBUF_TBUF_SIZE_CTRL, 1);
}

static void bcmgenet_disable_dma(void)
{
    rt_uint32_t tdma_reg = 0, rdma_reg = 0;

    tdma_reg = read32(MAC_REG_BASE_ADDR + TDMA_REG_BASE + DMA_CTRL);
    tdma_reg &= ~(1UL << DMA_EN);
    write32(MAC_REG_BASE_ADDR + TDMA_REG_BASE + DMA_CTRL, tdma_reg);
    rdma_reg = read32(MAC_REG_BASE_ADDR + RDMA_REG_BASE + DMA_CTRL);
    rdma_reg &= ~(1UL << DMA_EN);
    write32(MAC_REG_BASE_ADDR + RDMA_REG_BASE + DMA_CTRL, rdma_reg);
    write32(MAC_REG_BASE_ADDR + UMAC_TX_FLUSH, 1);
    DELAY_MICROS(100);
    write32(MAC_REG_BASE_ADDR + UMAC_TX_FLUSH, 0);
}

static void bcmgenet_enable_dma(void)
{
    rt_uint32_t reg = 0;
    rt_uint32_t dma_ctrl = 0;

    dma_ctrl = (1 << (DEFAULT_Q + DMA_RING_BUF_EN_SHIFT)) | DMA_EN;
    write32(MAC_REG_BASE_ADDR + TDMA_REG_BASE + DMA_CTRL, dma_ctrl);

    reg = read32(MAC_REG_BASE_ADDR + RDMA_REG_BASE + DMA_CTRL);
    write32(MAC_REG_BASE_ADDR + RDMA_REG_BASE + DMA_CTRL, dma_ctrl | reg);
}

static int bcmgenet_mdio_write(rt_uint32_t addr, rt_uint32_t reg, rt_uint32_t value)
{
    int count = 10000;
    rt_uint32_t val;
    rt_uint32_t reg_val;

    val = MDIO_WR | (addr << MDIO_PMD_SHIFT) | (reg << MDIO_REG_SHIFT) | (0xffff & value);
    write32(MAC_REG_BASE_ADDR + MDIO_CMD, val);

    reg_val = read32(MAC_REG_BASE_ADDR + MDIO_CMD);
    reg_val = reg_val | MDIO_START_BUSY;
    write32(MAC_REG_BASE_ADDR + MDIO_CMD, reg_val);

    while ((read32(MAC_REG_BASE_ADDR + MDIO_CMD) & MDIO_START_BUSY) && (--count))
    {
        DELAY_MICROS(1);
    }

    reg_val = read32(MAC_REG_BASE_ADDR + MDIO_CMD);

    return reg_val & 0xffff;
}

static int bcmgenet_mdio_read(rt_uint32_t addr, rt_uint32_t reg)
{
    int count = 10000;
    rt_uint32_t val = 0;
    rt_uint32_t reg_val = 0;

    val = MDIO_RD | (addr << MDIO_PMD_SHIFT) | (reg << MDIO_REG_SHIFT);
    write32(MAC_REG_BASE_ADDR + MDIO_CMD, val);

    reg_val = read32(MAC_REG_BASE_ADDR + MDIO_CMD);
    reg_val = reg_val | MDIO_START_BUSY;
    write32(MAC_REG_BASE_ADDR + MDIO_CMD, reg_val);

    while ((read32(MAC_REG_BASE_ADDR + MDIO_CMD) & MDIO_START_BUSY) && (--count))
    {
        DELAY_MICROS(1);
    }

    reg_val = read32(MAC_REG_BASE_ADDR + MDIO_CMD);

    return reg_val & 0xffff;
}

static int bcmgenet_gmac_write_hwaddr(void)
{
    rt_uint8_t addr[6];
    rt_uint32_t reg;

    bcm271x_mbox_hardware_get_mac_address(&addr[0]);

    reg = addr[0] << 24 | addr[1] << 16 | addr[2] << 8 | addr[3];
    write32(MAC_REG_BASE_ADDR + UMAC_MAC0, reg);

    reg = addr[4] << 8 | addr[5];
    write32(MAC_REG_BASE_ADDR + UMAC_MAC1, reg);

    return 0;
}

static int get_ethernet_uid(void)
{
    rt_uint32_t uid_high = 0;
    rt_uint32_t uid_low = 0;
    rt_uint32_t uid = 0;

    uid_high = bcmgenet_mdio_read(1, BCM54213PE_PHY_IDENTIFIER_HIGH);
    uid_low = bcmgenet_mdio_read(1, BCM54213PE_PHY_IDENTIFIER_LOW);
    uid = (uid_high << 16 | uid_low);

    if (BCM54213PE_VERSION_B1 == uid)
    {
        LOG_I("version is B1\n");
    }

    return uid;
}

static void bcmgenet_mdio_init(void)
{
    /* get ethernet uid */
    if (get_ethernet_uid() == 0)
    {
        return;
    }

    /* reset phy */
    bcmgenet_mdio_write(1, BCM54213PE_MII_CONTROL, MII_CONTROL_PHY_RESET);
    /* read control reg */
    bcmgenet_mdio_read(1, BCM54213PE_MII_CONTROL);
    /* reset phy again */
    bcmgenet_mdio_write(1, BCM54213PE_MII_CONTROL, MII_CONTROL_PHY_RESET);
    /* read control reg */
    bcmgenet_mdio_read(1, BCM54213PE_MII_CONTROL);
    /* read status reg */
    bcmgenet_mdio_read(1, BCM54213PE_MII_STATUS);
    /* read status reg */
    bcmgenet_mdio_read(1, BCM54213PE_IEEE_EXTENDED_STATUS);
    bcmgenet_mdio_read(1, BCM54213PE_AUTO_NEGOTIATION_ADV);

    bcmgenet_mdio_read(1, BCM54213PE_MII_STATUS);
    bcmgenet_mdio_read(1, BCM54213PE_CONTROL);
    /* half full duplex capability */
    bcmgenet_mdio_write(1, BCM54213PE_CONTROL, (CONTROL_HALF_DUPLEX_CAPABILITY | CONTROL_FULL_DUPLEX_CAPABILITY));
    bcmgenet_mdio_read(1, BCM54213PE_MII_CONTROL);

    /* set mii control */
    bcmgenet_mdio_write(1, BCM54213PE_MII_CONTROL, (MII_CONTROL_AUTO_NEGOTIATION_ENABLED | MII_CONTROL_AUTO_NEGOTIATION_RESTART | MII_CONTROL_PHY_FULL_DUPLEX | MII_CONTROL_SPEED_SELECTION));
}

static void rx_ring_init(void)
{
    write32(MAC_REG_BASE_ADDR + RDMA_REG_BASE + DMA_SCB_BURST_SIZE, DMA_MAX_BURST_LENGTH);
    write32(MAC_REG_BASE_ADDR + RDMA_RING_REG_BASE + DMA_START_ADDR, 0x0);
    write32(MAC_REG_BASE_ADDR + RDMA_READ_PTR, 0x0);
    write32(MAC_REG_BASE_ADDR + RDMA_WRITE_PTR, 0x0);
    write32(MAC_REG_BASE_ADDR + RDMA_RING_REG_BASE + DMA_END_ADDR, RX_DESCS * DMA_DESC_SIZE / 4 - 1);

    write32(MAC_REG_BASE_ADDR + RDMA_PROD_INDEX, 0x0);
    write32(MAC_REG_BASE_ADDR + RDMA_CONS_INDEX, 0x0);
    write32(MAC_REG_BASE_ADDR + RDMA_RING_REG_BASE + DMA_RING_BUF_SIZE, (RX_DESCS << DMA_RING_SIZE_SHIFT) | RX_BUF_LENGTH);
    write32(MAC_REG_BASE_ADDR + RDMA_XON_XOFF_THRESH, DMA_FC_THRESH_VALUE);
    write32(MAC_REG_BASE_ADDR + RDMA_REG_BASE + DMA_RING_CFG, 1 << DEFAULT_Q);
}

static void tx_ring_init(void)
{
    write32(MAC_REG_BASE_ADDR + TDMA_REG_BASE + DMA_SCB_BURST_SIZE, DMA_MAX_BURST_LENGTH);
    write32(MAC_REG_BASE_ADDR + TDMA_RING_REG_BASE + DMA_START_ADDR, 0x0);
    write32(MAC_REG_BASE_ADDR + TDMA_READ_PTR, 0x0);
    write32(MAC_REG_BASE_ADDR + TDMA_READ_PTR, 0x0);
    write32(MAC_REG_BASE_ADDR + TDMA_READ_PTR, 0x0);
    write32(MAC_REG_BASE_ADDR + TDMA_WRITE_PTR, 0x0);
    write32(MAC_REG_BASE_ADDR + TDMA_RING_REG_BASE + DMA_END_ADDR, TX_DESCS * DMA_DESC_SIZE / 4 - 1);
    write32(MAC_REG_BASE_ADDR + TDMA_PROD_INDEX, 0x0);
    write32(MAC_REG_BASE_ADDR + TDMA_CONS_INDEX, 0x0);
    write32(MAC_REG_BASE_ADDR + TDMA_RING_REG_BASE + DMA_MBUF_DONE_THRESH, 0x1);
    write32(MAC_REG_BASE_ADDR + TDMA_FLOW_PERIOD, 0x0);
    write32(MAC_REG_BASE_ADDR + TDMA_RING_REG_BASE + DMA_RING_BUF_SIZE, (TX_DESCS << DMA_RING_SIZE_SHIFT) | RX_BUF_LENGTH);
    write32(MAC_REG_BASE_ADDR + TDMA_REG_BASE + DMA_RING_CFG, 1 << DEFAULT_Q);
}

static void rx_descs_init(void)
{
    char *rxbuffs = (char *)RECV_DATA_NO_CACHE;
    rt_uint32_t len_stat, i;
    void *desc_base = (void *)RX_DESC_BASE;

    len_stat = (RX_BUF_LENGTH << DMA_BUFLENGTH_SHIFT) | DMA_OWN;
    for (i = 0; i < RX_DESCS; i++)
    {
        write32((desc_base + i * DMA_DESC_SIZE + DMA_DESC_ADDRESS_LO), lower_32_bits((uintptr_t)&rxbuffs[i * RX_BUF_LENGTH]));
        write32((desc_base + i * DMA_DESC_SIZE + DMA_DESC_ADDRESS_HI), upper_32_bits((uintptr_t)&rxbuffs[i * RX_BUF_LENGTH]));
        write32((desc_base + i * DMA_DESC_SIZE + DMA_DESC_LENGTH_STATUS), len_stat);
    }
}

static int bcmgenet_adjust_link(void)
{
    rt_uint32_t speed;
    rt_uint32_t phy_dev_speed = link_speed;
    rt_uint32_t reg1;

    switch (phy_dev_speed)
    {
    case SPEED_1000:
        speed = UMAC_SPEED_1000;
        break;
    case SPEED_100:
        speed = UMAC_SPEED_100;
        break;
    case SPEED_10:
        speed = UMAC_SPEED_10;
        break;
    default:
        rt_kprintf("bcmgenet: Unsupported PHY speed: %d\n", phy_dev_speed);
        return -1;
    }

    reg1 = read32(MAC_REG_BASE_ADDR + EXT_RGMII_OOB_CTRL);
    reg1 |= (RGMII_LINK | RGMII_MODE_EN | ID_MODE_DIS);
    write32(MAC_REG_BASE_ADDR + EXT_RGMII_OOB_CTRL, reg1);
    DELAY_MICROS(1000);
    write32(MAC_REG_BASE_ADDR + UMAC_CMD, speed << CMD_SPEED_SHIFT);

    return 0;
}

void link_irq(void *param)
{
    if ((bcmgenet_mdio_read(1, BCM54213PE_MII_STATUS) & MII_STATUS_LINK_UP) != 0)
    {
        rt_sem_release(&link_ack);
    }
}

static int bcmgenet_gmac_eth_start(void)
{
    rt_uint32_t ret;
    rt_uint32_t count = 10000;

    bcmgenet_umac_reset();

    bcmgenet_gmac_write_hwaddr();
    /* disable RX/TX DMA and flush TX queues */
    bcmgenet_disable_dma();
    rx_ring_init();
    rx_descs_init();
    tx_ring_init();

    /* enable RX/TX DMA */
    bcmgenet_enable_dma();

    /* ppdate MAC registers based on PHY property */
    ret = bcmgenet_adjust_link();
    if (ret)
    {
        rt_kprintf("bcmgenet: adjust PHY link failed: %d\n", ret);
        return ret;
    }

    /* wait tx index clear */
    while ((read32(MAC_REG_BASE_ADDR + TDMA_CONS_INDEX) != 0) && (--count))
    {
        DELAY_MICROS(1);
    }

    tx_index = read32(MAC_REG_BASE_ADDR + TDMA_CONS_INDEX);
    write32(MAC_REG_BASE_ADDR + TDMA_PROD_INDEX, tx_index);

    index_flag = read32(MAC_REG_BASE_ADDR + RDMA_PROD_INDEX);

    rx_index = index_flag % RX_DESCS;

    write32(MAC_REG_BASE_ADDR + RDMA_CONS_INDEX, index_flag);
    write32(MAC_REG_BASE_ADDR + RDMA_PROD_INDEX, index_flag);

    /* enable Rx/Tx */
    rt_uint32_t rx_tx_en;
    rx_tx_en = read32(MAC_REG_BASE_ADDR + UMAC_CMD);
    rx_tx_en |= (CMD_TX_EN | CMD_RX_EN);

    write32(MAC_REG_BASE_ADDR + UMAC_CMD, rx_tx_en);

    /* eanble IRQ for TxDMA done and RxDMA done */
    write32(MAC_REG_BASE_ADDR + GENET_INTRL2_CPU_CLEAR_MASK, GENET_IRQ_TXDMA_DONE | GENET_IRQ_RXDMA_DONE);

    return 0;
}

static rt_uint32_t prev_recv_cnt = 0;
static rt_uint32_t cur_recv_cnt = 0;
static rt_uint32_t bcmgenet_gmac_eth_recv(rt_uint8_t **packetp)
{
    void *desc_base;
    rt_uint32_t length = 0, addr = 0;
    rt_uint32_t prod_index = read32(MAC_REG_BASE_ADDR + RDMA_PROD_INDEX);

    /* no buff */
    if (prod_index == index_flag)
    {
        cur_recv_cnt = index_flag;
        index_flag = 0x7fffffff;

        return 0;
    }
    else
    {
        /* no new buff */
        if (prev_recv_cnt == (prod_index & 0xffff))
        {
            return 0;
        }

        desc_base = RX_DESC_BASE + rx_index * DMA_DESC_SIZE;
        length = read32(desc_base + DMA_DESC_LENGTH_STATUS);
        length = (length >> DMA_BUFLENGTH_SHIFT) & DMA_BUFLENGTH_MASK;
        addr = read32(desc_base + DMA_DESC_ADDRESS_LO);
        /*
         * to cater for the IP headepr alignment the hardware does.
         * This would actually not be needed if we don't program
         * RBUF_ALIGN_2B
         */

        /* convert to memory address */
        addr = addr + RECV_DATA_NO_CACHE - RECV_DATA_NO_CACHE;
        rt_hw_dcache_invalidate_range(addr, length);

        *packetp = (rt_uint8_t *)(unsigned long)(addr + RX_BUF_OFFSET);

        rx_index = rx_index + 1;
        if (rx_index >= RX_DESCS)
        {
            rx_index = 0;
        }

        write32(MAC_REG_BASE_ADDR + RDMA_CONS_INDEX, cur_recv_cnt);

        cur_recv_cnt = cur_recv_cnt + 1;

        if (cur_recv_cnt > 0xffff)
        {
            cur_recv_cnt = 0;
        }
        prev_recv_cnt = cur_recv_cnt;

        return length - RX_BUF_OFFSET;
    }
}


static int bcmgenet_gmac_eth_send(rt_uint32_t packet, int length, struct pbuf *p)
{
    void *desc_base = (TX_DESC_BASE + tx_index * DMA_DESC_SIZE);
    pbuf_copy_partial(p, (void *)(unsigned long)(packet + tx_index * SEND_CACHE_BUF), p->tot_len, 0);
    rt_uint32_t len_stat = length << DMA_BUFLENGTH_SHIFT;
    len_stat |= 0x3F << DMA_TX_QTAG_SHIFT;
    len_stat |= DMA_TX_APPEND_CRC | DMA_SOP | DMA_EOP;
    rt_hw_dcache_flush_range(packet + tx_index * SEND_CACHE_BUF, length);

    rt_uint32_t prod_index;

    prod_index = read32(MAC_REG_BASE_ADDR + TDMA_PROD_INDEX);

    write32((desc_base + DMA_DESC_ADDRESS_LO), SEND_DATA_NO_CACHE + tx_index * SEND_CACHE_BUF);
    write32((desc_base + DMA_DESC_ADDRESS_HI), 0);
    write32((desc_base + DMA_DESC_LENGTH_STATUS), len_stat);

    tx_index++;
    if (tx_index >= TX_DESCS)
    {
        tx_index = 0;
    }
    prod_index = prod_index + 1;

    if (prod_index > 0xffff)
    {
        prod_index = 0;
    }

    /* start Transmisson */
    write32(MAC_REG_BASE_ADDR + TDMA_PROD_INDEX, prod_index);
    return 0;
}

static void link_task_entry(void *param)
{
    struct eth_device *eth_device = (struct eth_device *)param;
    RT_ASSERT(eth_device != RT_NULL);
    struct rt_eth_dev *dev = &eth_dev;

    /* start mdio */
    bcmgenet_mdio_init();

    /* start timer link */
    rt_timer_init(&dev->link_timer, "link_timer",
                  link_irq,
                  NULL,
                  100,
                  RT_TIMER_FLAG_PERIODIC);
    rt_timer_start(&dev->link_timer);

    /* link wait forever */
    rt_sem_take(&link_ack, RT_WAITING_FOREVER);
    /* link up */
    eth_device_linkchange(&eth_dev.parent, RT_TRUE);
    rt_timer_stop(&dev->link_timer);

    /* set mac */
    bcmgenet_gmac_write_hwaddr();

    /* check link speed */
    if ((bcmgenet_mdio_read(1, BCM54213PE_STATUS) & (1 << 10)) || (bcmgenet_mdio_read(1, BCM54213PE_STATUS) & (1 << 11)))
    {
        link_speed = 1000;
        rt_kprintf("Support link mode Speed 1000M\n");
    }
    else if ((bcmgenet_mdio_read(1, 0x05) & (1 << 7)) || (bcmgenet_mdio_read(1, 0x05) & (1 << 8)) || (bcmgenet_mdio_read(1, 0x05) & (1 << 9)))
    {
        link_speed = 100;
        rt_kprintf("Support link mode Speed 100M\n");
    }
    else
    {
        link_speed = 10;
        rt_kprintf("Support link mode Speed 10M\n");
    }

    /* convert to memory address */
    bcmgenet_gmac_eth_start();

    rt_hw_interrupt_install(ETH_IRQ, eth_rx_irq, NULL, "eth_irq");
    rt_hw_interrupt_umask(ETH_IRQ);

    link_flag = 1;
}

static rt_err_t bcmgenet_eth_init(rt_device_t device)
{
    rt_uint32_t ret = 0;
    rt_uint32_t hw_reg = 0;

    /* read GENET HW version */
    rt_uint8_t major = 0;
    hw_reg = read32(MAC_REG_BASE_ADDR + SYS_REV_CTRL);
    major = (hw_reg >> 24) & 0x0f;

    if (major != 6)
    {
        if (major == 5)
        {
            major = 4;
        }
        else if (major == 0)
        {
            major = 1;
        }

        rt_kprintf("Uns upported GENETv%d.%d\n", major, (hw_reg >> 16) & 0x0f);

        return RT_ERROR;
    }

    /* set interface */
    ret = bcmgenet_interface_set();
    if (ret)
    {
        return ret;
    }

    /* rbuf clear */
    write32(MAC_REG_BASE_ADDR + SYS_RBUF_FLUSH_CTRL, 0);

    /* disable MAC while updating its registers */
    write32(MAC_REG_BASE_ADDR + UMAC_CMD, 0);
    /* issue soft reset with (rg)mii loopback to ensure a stable rxclk */
    write32(MAC_REG_BASE_ADDR + UMAC_CMD, CMD_SW_RESET | CMD_LCL_LOOP_EN);

    link_thread_tid = rt_thread_create("link", link_task_entry, (void *)device,
                                       LINK_THREAD_STACK_SIZE,
                                       LINK_THREAD_PRIORITY, LINK_THREAD_TIMESLICE);
    if (link_thread_tid != RT_NULL)
    {
        rt_thread_startup(link_thread_tid);
    }

    return RT_EOK;
}

static rt_err_t bcmgenet_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args)
        {
            rt_memcpy(args, eth_dev.dev_addr, 6);
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

rt_err_t rt_eth_tx(rt_device_t device, struct pbuf *p)
{
    if (link_flag == 1)
    {
        bcmgenet_gmac_eth_send((rt_uint32_t)SEND_DATA_NO_CACHE, p->tot_len, p);
        rt_sem_take(&send_finsh_sem_lock, RT_WAITING_FOREVER);
    }

    return RT_EOK;
}

struct pbuf *rt_eth_rx(rt_device_t device)
{
    int recv_len = 0;
    rt_uint8_t *addr_point = RT_NULL;
    struct pbuf *pbuf = RT_NULL;

    if (link_flag == 1)
    {
        recv_len = bcmgenet_gmac_eth_recv(&addr_point);
        if (recv_len > 0)
        {
            pbuf = pbuf_alloc(PBUF_LINK, recv_len, PBUF_RAM);
            if (pbuf)
            {
                rt_memcpy(pbuf->payload, addr_point, recv_len);
            }
        }
    }

    return pbuf;
}

int rt_hw_eth_init(void)
{
    rt_uint8_t mac_addr[6];
    rt_sem_init(&send_finsh_sem_lock, "send_finsh_sem_lock", TX_DESCS, RT_IPC_FLAG_FIFO);
    rt_sem_init(&link_ack, "link_ack", 0, RT_IPC_FLAG_FIFO);
    memset(&eth_dev, 0, sizeof(eth_dev));
    memset((void *)SEND_DATA_NO_CACHE, 0, DMA_DISC_ADDR_SIZE);
    memset((void *)RECV_DATA_NO_CACHE, 0, DMA_DISC_ADDR_SIZE);
    bcm271x_mbox_hardware_get_mac_address(&mac_addr[0]);

    eth_dev.iobase = MAC_REG_BASE_ADDR;
    eth_dev.name = "e0";
    eth_dev.dev_addr[0] = mac_addr[0];
    eth_dev.dev_addr[1] = mac_addr[1];
    eth_dev.dev_addr[2] = mac_addr[2];
    eth_dev.dev_addr[3] = mac_addr[3];
    eth_dev.dev_addr[4] = mac_addr[4];
    eth_dev.dev_addr[5] = mac_addr[5];

    eth_dev.parent.parent.type       = RT_Device_Class_NetIf;
    eth_dev.parent.parent.init       = bcmgenet_eth_init;
    eth_dev.parent.parent.open       = RT_NULL;
    eth_dev.parent.parent.close      = RT_NULL;
    eth_dev.parent.parent.read       = RT_NULL;
    eth_dev.parent.parent.write      = RT_NULL;
    eth_dev.parent.parent.control    = bcmgenet_eth_control;
    eth_dev.parent.parent.user_data  = RT_NULL;

    eth_dev.parent.eth_tx            = rt_eth_tx;
    eth_dev.parent.eth_rx            = rt_eth_rx;

    eth_device_init(&(eth_dev.parent), "e0");
    /* link down */
    eth_device_linkchange(&eth_dev.parent, RT_FALSE);

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_eth_init);

#endif /* BSP_USING_ETH */
