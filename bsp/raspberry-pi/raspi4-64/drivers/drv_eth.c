
/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-10-30     bigmagic       first version
 * 2023-03-28     WangXiaoyao    Modify pbuf_alloc
 */

#include <rthw.h>
#include <stdint.h>
#include <rtthread.h>
#include <lwip/sys.h>
#include <netif/ethernetif.h>

#include "mbox.h"
#include "raspi4.h"
#include "drv_eth.h"

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG                "drv.eth"

static int link_speed = 0;
static int link_flag = 0;

#define DMA_DISC_ADDR_SIZE          (4 * 1024 *1024)

#define RX_DESC_BASE            (mac_reg_base_addr + GENET_RX_OFF)
#define TX_DESC_BASE            (mac_reg_base_addr + GENET_TX_OFF)

#define MAX_ADDR_LEN            (6)

#define upper_32_bits(n)        ((rt_uint32_t)(((n) >> 16) >> 16))
#define lower_32_bits(n)        ((rt_uint32_t)(n))

#define BIT(nr)                 (1UL << (nr))

static rt_thread_t link_thread_tid = RT_NULL;
#define LINK_THREAD_STACK_SIZE   (8192)
#define LINK_THREAD_PRIORITY     (20)
#define LINK_THREAD_TIMESLICE    (10)

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
static struct rt_semaphore link_ack;

static inline rt_uint32_t read32(void *addr)
{
    return (*((volatile unsigned int*)(addr)));
}

static inline void write32(void *addr, rt_uint32_t value)
{
    (*((volatile unsigned int*)(addr))) = value;
}

static void eth_rx_irq(int irq, void *param)
{
    rt_uint32_t val = 0;
    val = read32(mac_reg_base_addr + GENET_INTRL2_CPU_STAT);
    val &= ~read32(mac_reg_base_addr + GENET_INTRL2_CPU_STAT_MASK);

    write32(mac_reg_base_addr + GENET_INTRL2_CPU_CLEAR, val);

    if (val & GENET_IRQ_RXDMA_DONE)
    {
        eth_device_ready(&eth_dev.parent);
    }

    if (val & GENET_IRQ_TXDMA_DONE)
    {
        //todo
    }
}

/* We only support RGMII (as used on the RPi4). */
static int bcmgenet_interface_set(void)
{
    int phy_mode = PHY_INTERFACE_MODE_RGMII;
    switch (phy_mode)
    {
    case PHY_INTERFACE_MODE_RGMII:
    case PHY_INTERFACE_MODE_RGMII_RXID:
        write32(mac_reg_base_addr + SYS_PORT_CTRL, PORT_MODE_EXT_GPHY);
        break;

    default:
        rt_kprintf("unknown phy mode: %d\n", mac_reg_base_addr);
        return -1;
    }
    return 0;
}

static void bcmgenet_umac_reset(void)
{
    rt_uint32_t reg;
    reg = read32(mac_reg_base_addr + SYS_RBUF_FLUSH_CTRL);
    reg |= BIT(1);
    write32((mac_reg_base_addr + SYS_RBUF_FLUSH_CTRL), reg);

    reg &= ~BIT(1);
    write32((mac_reg_base_addr + SYS_RBUF_FLUSH_CTRL), reg);

    DELAY_MICROS(10);

    write32((mac_reg_base_addr + SYS_RBUF_FLUSH_CTRL), 0);
    DELAY_MICROS(10);

    write32(mac_reg_base_addr + UMAC_CMD, 0);
    write32(mac_reg_base_addr + UMAC_CMD, (CMD_SW_RESET | CMD_LCL_LOOP_EN));
    DELAY_MICROS(2);

    write32(mac_reg_base_addr + UMAC_CMD, 0);
    /* clear tx/rx counter */
    write32(mac_reg_base_addr + UMAC_MIB_CTRL, MIB_RESET_RX | MIB_RESET_TX | MIB_RESET_RUNT);
    write32(mac_reg_base_addr + UMAC_MIB_CTRL, 0);
    write32(mac_reg_base_addr + UMAC_MAX_FRAME_LEN, ENET_MAX_MTU_SIZE);

    /* init rx registers, enable ip header optimization */
    reg = read32(mac_reg_base_addr + RBUF_CTRL);
    reg |= RBUF_ALIGN_2B;
    write32(mac_reg_base_addr + RBUF_CTRL, reg);
    write32(mac_reg_base_addr + RBUF_TBUF_SIZE_CTRL, 1);
}

static void bcmgenet_disable_dma(void)
{
    rt_uint32_t tdma_reg = 0, rdma_reg = 0;

    tdma_reg = read32(mac_reg_base_addr + TDMA_REG_BASE + DMA_CTRL);
    tdma_reg &= ~(1UL << DMA_EN);
    write32(mac_reg_base_addr + TDMA_REG_BASE + DMA_CTRL, tdma_reg);
    rdma_reg = read32(mac_reg_base_addr + RDMA_REG_BASE + DMA_CTRL);
    rdma_reg &= ~(1UL << DMA_EN);
    write32(mac_reg_base_addr + RDMA_REG_BASE + DMA_CTRL, rdma_reg);
    write32(mac_reg_base_addr + UMAC_TX_FLUSH, 1);
    DELAY_MICROS(100);
    write32(mac_reg_base_addr + UMAC_TX_FLUSH, 0);
}

static void bcmgenet_enable_dma(void)
{
    rt_uint32_t reg = 0;
    rt_uint32_t dma_ctrl = 0;

    dma_ctrl = (1 << (DEFAULT_Q + DMA_RING_BUF_EN_SHIFT)) | DMA_EN;
    write32(mac_reg_base_addr + TDMA_REG_BASE + DMA_CTRL, dma_ctrl);

    reg = read32(mac_reg_base_addr + RDMA_REG_BASE + DMA_CTRL);
    write32(mac_reg_base_addr + RDMA_REG_BASE + DMA_CTRL, dma_ctrl | reg);
}

static int bcmgenet_mdio_write(rt_uint32_t addr, rt_uint32_t reg, rt_uint32_t value)
{
    int count = 10000;
    rt_uint32_t val;
    val = MDIO_WR | (addr << MDIO_PMD_SHIFT) | (reg << MDIO_REG_SHIFT) | (0xffff & value);
    write32(mac_reg_base_addr + MDIO_CMD, val);

    rt_uint32_t reg_val = read32(mac_reg_base_addr + MDIO_CMD);
    reg_val = reg_val | MDIO_START_BUSY;
    write32(mac_reg_base_addr + MDIO_CMD, reg_val);

    while ((read32(mac_reg_base_addr + MDIO_CMD) & MDIO_START_BUSY) && (--count))
        DELAY_MICROS(1);

    reg_val = read32(mac_reg_base_addr + MDIO_CMD);

    return reg_val & 0xffff;
}

static int bcmgenet_mdio_read(rt_uint32_t addr, rt_uint32_t reg)
{
    int count = 10000;
    rt_uint32_t val = 0;
    rt_uint32_t reg_val = 0;

    val = MDIO_RD | (addr << MDIO_PMD_SHIFT) | (reg << MDIO_REG_SHIFT);
    write32(mac_reg_base_addr + MDIO_CMD, val);

    reg_val = read32(mac_reg_base_addr + MDIO_CMD);
    reg_val = reg_val | MDIO_START_BUSY;
    write32(mac_reg_base_addr + MDIO_CMD, reg_val);

    while ((read32(mac_reg_base_addr + MDIO_CMD) & MDIO_START_BUSY) && (--count))
        DELAY_MICROS(1);

    reg_val = read32(mac_reg_base_addr + MDIO_CMD);

    return reg_val & 0xffff;
}

static int bcmgenet_gmac_write_hwaddr(void)
{
    rt_uint8_t addr[6];
    rt_uint32_t reg;
    bcm271x_mbox_hardware_get_mac_address(&addr[0]);

    reg = addr[0] << 24 | addr[1] << 16 | addr[2] << 8 | addr[3];
    write32(mac_reg_base_addr + UMAC_MAC0, reg);

    reg = addr[4] << 8 | addr[5];
    write32(mac_reg_base_addr + UMAC_MAC1, reg);
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
    rt_uint32_t ret = 0;
    /*get ethernet uid*/
    ret = get_ethernet_uid();
    if (ret == 0) return;

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
    write32(mac_reg_base_addr + RDMA_REG_BASE + DMA_SCB_BURST_SIZE, DMA_MAX_BURST_LENGTH);
    write32(mac_reg_base_addr + RDMA_RING_REG_BASE + DMA_START_ADDR, 0x0);
    write32(mac_reg_base_addr + RDMA_READ_PTR, 0x0);
    write32(mac_reg_base_addr + RDMA_WRITE_PTR, 0x0);
    write32(mac_reg_base_addr + RDMA_RING_REG_BASE + DMA_END_ADDR, RX_DESCS * DMA_DESC_SIZE / 4 - 1);

    write32(mac_reg_base_addr + RDMA_PROD_INDEX, 0x0);
    write32(mac_reg_base_addr + RDMA_CONS_INDEX, 0x0);
    write32(mac_reg_base_addr + RDMA_RING_REG_BASE + DMA_RING_BUF_SIZE, (RX_DESCS << DMA_RING_SIZE_SHIFT) | RX_BUF_LENGTH);
    write32(mac_reg_base_addr + RDMA_XON_XOFF_THRESH, DMA_FC_THRESH_VALUE);
    write32(mac_reg_base_addr + RDMA_REG_BASE + DMA_RING_CFG, 1 << DEFAULT_Q);
}

static void tx_ring_init(void)
{
    write32(mac_reg_base_addr + TDMA_REG_BASE + DMA_SCB_BURST_SIZE, DMA_MAX_BURST_LENGTH);
    write32(mac_reg_base_addr + TDMA_RING_REG_BASE + DMA_START_ADDR, 0x0);
    write32(mac_reg_base_addr + TDMA_READ_PTR, 0x0);
    write32(mac_reg_base_addr + TDMA_READ_PTR, 0x0);
    write32(mac_reg_base_addr + TDMA_READ_PTR, 0x0);
    write32(mac_reg_base_addr + TDMA_WRITE_PTR, 0x0);
    write32(mac_reg_base_addr + TDMA_RING_REG_BASE + DMA_END_ADDR, TX_DESCS * DMA_DESC_SIZE / 4 - 1);
    write32(mac_reg_base_addr + TDMA_PROD_INDEX, 0x0);
    write32(mac_reg_base_addr + TDMA_CONS_INDEX, 0x0);
    write32(mac_reg_base_addr + TDMA_RING_REG_BASE + DMA_MBUF_DONE_THRESH, 0x1);
    write32(mac_reg_base_addr + TDMA_FLOW_PERIOD, 0x0);
    write32(mac_reg_base_addr + TDMA_RING_REG_BASE + DMA_RING_BUF_SIZE, (TX_DESCS << DMA_RING_SIZE_SHIFT) | RX_BUF_LENGTH);
    write32(mac_reg_base_addr + TDMA_REG_BASE + DMA_RING_CFG, 1 << DEFAULT_Q);
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

    rt_uint32_t reg1 = read32(mac_reg_base_addr + EXT_RGMII_OOB_CTRL);
    //reg1 &= ~(1UL << OOB_DISABLE);

    //rt_kprintf("OOB_DISABLE is %d\n", OOB_DISABLE);
    reg1 |= (RGMII_LINK | RGMII_MODE_EN | ID_MODE_DIS);
    write32(mac_reg_base_addr + EXT_RGMII_OOB_CTRL, reg1);
    DELAY_MICROS(1000);
    write32(mac_reg_base_addr + UMAC_CMD, speed << CMD_SPEED_SHIFT);
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
    /* Disable RX/TX DMA and flush TX queues */
    bcmgenet_disable_dma();
    rx_ring_init();
    rx_descs_init();
    tx_ring_init();

    /* Enable RX/TX DMA */
    bcmgenet_enable_dma();

    /* Update MAC registers based on PHY property */
    ret = bcmgenet_adjust_link();
    if(ret)
    {
        rt_kprintf("bcmgenet: adjust PHY link failed: %d\n", ret);
        return ret;
    }

    /* wait tx index clear */
    while ((read32(mac_reg_base_addr + TDMA_CONS_INDEX) != 0) && (--count))
        DELAY_MICROS(1);

    tx_index = read32(mac_reg_base_addr + TDMA_CONS_INDEX);
    write32(mac_reg_base_addr + TDMA_PROD_INDEX, tx_index);

    index_flag = read32(mac_reg_base_addr + RDMA_PROD_INDEX);

    rx_index = index_flag % 256;

    write32(mac_reg_base_addr + RDMA_CONS_INDEX, index_flag);
    write32(mac_reg_base_addr + RDMA_PROD_INDEX, index_flag);

    /* Enable Rx/Tx */
    rt_uint32_t rx_tx_en;
    rx_tx_en = read32(mac_reg_base_addr + UMAC_CMD);
    rx_tx_en |= (CMD_TX_EN | CMD_RX_EN);

    write32(mac_reg_base_addr + UMAC_CMD, rx_tx_en);

    // eanble IRQ for TxDMA done and RxDMA done
    write32(mac_reg_base_addr + GENET_INTRL2_CPU_CLEAR_MASK, GENET_IRQ_TXDMA_DONE | GENET_IRQ_RXDMA_DONE);
    return 0;
}

static rt_uint32_t prev_recv_cnt = 0;
static rt_uint32_t cur_recv_cnt = 0;
static rt_uint32_t bcmgenet_gmac_eth_recv(rt_uint8_t **packetp)
{
    void* desc_base;
    rt_uint32_t length = 0;
    size_t addr = 0;
    rt_uint32_t prod_index = read32(mac_reg_base_addr + RDMA_PROD_INDEX);
    //get next
    if(prod_index == index_flag)
    {
        cur_recv_cnt = index_flag;
        index_flag = 0x7fffffff;
        //no buff
        return 0;
    }
    else
    {
        if(prev_recv_cnt == (prod_index & 0xffffUL))
        {
            return 0;
        }

        desc_base = RX_DESC_BASE + rx_index * DMA_DESC_SIZE;
        length = read32(desc_base + DMA_DESC_LENGTH_STATUS);
        length = (length >> DMA_BUFLENGTH_SHIFT) & DMA_BUFLENGTH_MASK;
        addr = read32(desc_base + DMA_DESC_ADDRESS_LO);
        /* To cater for the IP headepr alignment the hardware does.
        * This would actually not be needed if we don't program
        * RBUF_ALIGN_2B
        */
        *packetp = (rt_uint8_t *)(addr + RX_BUF_OFFSET);

        rx_index = rx_index + 1;
        if(rx_index >= 256)
        {
            rx_index = 0;
        }
        write32(mac_reg_base_addr + RDMA_CONS_INDEX, cur_recv_cnt);

        cur_recv_cnt = cur_recv_cnt + 1;

        if(cur_recv_cnt > 0xffff)
        {
            cur_recv_cnt = 0;
        }
        prev_recv_cnt = cur_recv_cnt;

        return length;
    }
}

static int bcmgenet_gmac_eth_send(void *packet, int length)
{
    rt_ubase_t level;
    void *desc_base = (TX_DESC_BASE + tx_index * DMA_DESC_SIZE);
    rt_uint32_t len_stat = length << DMA_BUFLENGTH_SHIFT;

    rt_uint32_t prod_index, cons;
    rt_uint32_t tries = 100;

    prod_index = read32(mac_reg_base_addr + TDMA_PROD_INDEX);

    len_stat |= 0x3F << DMA_TX_QTAG_SHIFT;
    len_stat |= DMA_TX_APPEND_CRC | DMA_SOP | DMA_EOP;

    write32((desc_base + DMA_DESC_ADDRESS_LO), SEND_DATA_NO_CACHE);
    write32((desc_base + DMA_DESC_ADDRESS_HI), 0);
    write32((desc_base + DMA_DESC_LENGTH_STATUS), len_stat);

    tx_index = tx_index == 255? 0 : tx_index + 1;
    prod_index = prod_index + 1;

    if (prod_index == 0xe000)
    {
        write32(mac_reg_base_addr + TDMA_PROD_INDEX, 0);
        prod_index = 0;
    }

    /* Start Transmisson */
    write32(mac_reg_base_addr + TDMA_PROD_INDEX, prod_index);

    level = rt_hw_interrupt_disable();
    do
    {
        cons = read32(mac_reg_base_addr + TDMA_CONS_INDEX);
    } while ((cons & 0xffff) < prod_index && --tries);
    rt_hw_interrupt_enable(level);

    if (!tries)
    {
        rt_kprintf("send err! tries is %d\n", tries);
        return -1;
    }

    return 0;
}

static void link_task_entry(void *param)
{
    struct eth_device *eth_device = (struct eth_device *)param;
    RT_ASSERT(eth_device != RT_NULL);
    struct rt_eth_dev *dev = &eth_dev;

    //start mdio
    bcmgenet_mdio_init();

    //start timer link
    rt_timer_init(&dev->link_timer, "link_timer",
                  link_irq,
                  NULL,
                  100,
                  RT_TIMER_FLAG_PERIODIC);
    rt_timer_start(&dev->link_timer);

    //link wait forever
    rt_sem_take(&link_ack, RT_WAITING_FOREVER);
    eth_device_linkchange(&eth_dev.parent, RT_TRUE); //link up
    rt_timer_stop(&dev->link_timer);

    //set mac
    // bcmgenet_gmac_write_hwaddr();
    bcmgenet_gmac_write_hwaddr();

    //check link speed
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

    bcmgenet_gmac_eth_start();

    rt_hw_interrupt_install(ETH_IRQ, eth_rx_irq, NULL, "eth_irq");
    rt_hw_interrupt_umask(ETH_IRQ);

    link_flag = 1;
}

static rt_err_t bcmgenet_eth_init(rt_device_t device)
{
    rt_uint32_t ret = 0;
    rt_uint32_t hw_reg = 0;

    /* Read GENET HW version */
    rt_uint8_t major = 0;
    hw_reg = read32(mac_reg_base_addr + SYS_REV_CTRL);
    major = (hw_reg >> 24) & 0x0f;
    if (major != 6)
    {
        if (major == 5)
            major = 4;
        else if (major == 0)
            major = 1;

        rt_kprintf("Uns upported GENETv%d.%d\n", major, (hw_reg >> 16) & 0x0f);
        return -RT_ERROR;
    }
    /* set interface */
    ret = bcmgenet_interface_set();
    if (ret)
    {
        return ret;
    }

    /* rbuf clear */
    write32(mac_reg_base_addr + SYS_RBUF_FLUSH_CTRL, 0);

    /* disable MAC while updating its registers */
    write32(mac_reg_base_addr + UMAC_CMD, 0);
    /* issue soft reset with (rg)mii loopback to ensure a stable rxclk */
    write32(mac_reg_base_addr + UMAC_CMD, CMD_SW_RESET | CMD_LCL_LOOP_EN);

    link_thread_tid = rt_thread_create("link", link_task_entry, (void *)device,
                                       LINK_THREAD_STACK_SIZE,
                                       LINK_THREAD_PRIORITY, LINK_THREAD_TIMESLICE);
    if (link_thread_tid != RT_NULL)
        rt_thread_startup(link_thread_tid);

    return RT_EOK;
}

static rt_err_t bcmgenet_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args)
            rt_memcpy(args, eth_dev.dev_addr, 6);
        else
            return -RT_ERROR;
        break;
    default:
        break;
    }
    return RT_EOK;
}

rt_err_t rt_eth_tx(rt_device_t device, struct pbuf *p)
{
    int copy_len = 0;

    /* lock eth device */
    if (link_flag != 1)
    {
        rt_kprintf("link disconnected\n");
        return -RT_ERROR;
    }

    copy_len = pbuf_copy_partial(p, eth_send_no_cache, p->tot_len, 0);
    if (copy_len == 0)
    {

        rt_kprintf("copy len is zero\n");
        return -RT_ERROR;
    }
    bcmgenet_gmac_eth_send((void *)eth_send_no_cache, p->tot_len);

    return RT_EOK;
}

struct pbuf *rt_eth_rx(rt_device_t device)
{
    int recv_len = 0;
    size_t addr_point;
    struct pbuf *pbuf = RT_NULL;
    if (link_flag != 1)
    {
        return RT_NULL;
    }

    recv_len = bcmgenet_gmac_eth_recv((rt_uint8_t **)&addr_point);
    if (recv_len > 0)
    {
        pbuf = pbuf_alloc(PBUF_LINK, ENET_FRAME_MAX_FRAMELEN, PBUF_POOL);
        if (pbuf != RT_NULL)
        {
            //calc offset
            addr_point= (size_t)(addr_point+ (eth_recv_no_cache - RECV_DATA_NO_CACHE));
            rt_memcpy(pbuf->payload, (char *)addr_point, recv_len);
        }
    }

    return pbuf;
}

int rt_hw_eth_init(void)
{
    rt_uint8_t mac_addr[6];

    rt_sem_init(&link_ack, "link_ack", 0, RT_IPC_FLAG_FIFO);

    memset(&eth_dev, 0, sizeof(eth_dev));
    memset((void *)eth_send_no_cache, 0, sizeof(DMA_DISC_ADDR_SIZE));
    memset((void *)eth_recv_no_cache, 0, sizeof(DMA_DISC_ADDR_SIZE));
    bcm271x_mbox_hardware_get_mac_address(&mac_addr[0]);

    eth_dev.iobase = mac_reg_base_addr;
    eth_dev.name = "e0";
    eth_dev.dev_addr[0] = mac_addr[0];
    eth_dev.dev_addr[1] = mac_addr[1];
    eth_dev.dev_addr[2] = mac_addr[2];
    eth_dev.dev_addr[3] = mac_addr[3];
    eth_dev.dev_addr[4] = mac_addr[4];
    eth_dev.dev_addr[5] = mac_addr[5];

    eth_dev.parent.parent.type          = RT_Device_Class_NetIf;
    eth_dev.parent.parent.init          = bcmgenet_eth_init;
    eth_dev.parent.parent.open          = RT_NULL;
    eth_dev.parent.parent.close         = RT_NULL;
    eth_dev.parent.parent.read          = RT_NULL;
    eth_dev.parent.parent.write         = RT_NULL;
    eth_dev.parent.parent.control       = bcmgenet_eth_control;
    eth_dev.parent.parent.user_data     = RT_NULL;

    eth_dev.parent.eth_tx            = rt_eth_tx;
    eth_dev.parent.eth_rx            = rt_eth_rx;

    eth_device_init(&(eth_dev.parent), "e0");
    eth_device_linkchange(&eth_dev.parent, RT_FALSE);   //link down
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_eth_init);
