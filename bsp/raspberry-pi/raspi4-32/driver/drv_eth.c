
/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-10-30     bigmagic       first version
 */

#include <rthw.h>
#include <stdint.h>
#include <rtthread.h>
#include <lwip/sys.h>
#include <netif/ethernetif.h>

#include "mbox.h"
#include "raspi4.h"
#include "drv_eth.h"

#define RECV_CACHE_BUF          (1024)
#define SEND_DATA_NO_CACHE      (0x08200000)
#define RECV_DATA_NO_CACHE      (0x08400000)
#define DMA_DISC_ADDR_SIZE      (4 * 1024 *1024)

#define RX_DESC_BASE            (MAC_REG + GENET_RX_OFF)
#define TX_DESC_BASE            (MAC_REG + GENET_TX_OFF)

#define MAX_ADDR_LEN            (6)

#define upper_32_bits(n)        ((rt_uint32_t)(((n) >> 16) >> 16))
#define lower_32_bits(n)        ((rt_uint32_t)(n))

#define BIT(nr)                 (1UL << (nr))

static rt_uint32_t tx_index = 0;
static rt_uint32_t rx_index = 0;
static rt_uint32_t index_flag = 0;

static rt_uint32_t send_cache_pbuf[RECV_CACHE_BUF];

struct rt_eth_dev
{
    struct eth_device parent;
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
    char *name;
    void *iobase;
    int state;
    int index;
    struct rt_timer link_timer;
    struct rt_timer rx_poll_timer;
    void *priv;
};
static struct rt_eth_dev eth_dev;
static struct rt_semaphore sem_lock;

static inline rt_uint32_t read32(void *addr)
{
    return (*((volatile unsigned int*)(addr)));
}

static inline void write32(void *addr, rt_uint32_t value)
{
    (*((volatile unsigned int*)(addr))) = value;
}

void eth_rx_irq(void *param)
{
    eth_device_ready(&eth_dev.parent);
}

/* We only support RGMII (as used on the RPi4). */
static int bcmgenet_interface_set(void)
{
    int phy_mode = PHY_INTERFACE_MODE_RGMII;
    switch (phy_mode) {
    case PHY_INTERFACE_MODE_RGMII:
    case PHY_INTERFACE_MODE_RGMII_RXID:
        write32(MAC_REG + SYS_PORT_CTRL,PORT_MODE_EXT_GPHY);
        break;
    default:
        rt_kprintf("unknown phy mode: %d\n", MAC_REG);
        return -1;
    }
    return 0;
}

static void bcmgenet_umac_reset(void)
{
    rt_uint32_t reg;
    reg = read32(MAC_REG + SYS_RBUF_FLUSH_CTRL);
    reg |= BIT(1);
    write32((MAC_REG + SYS_RBUF_FLUSH_CTRL), reg);

    reg &= ~BIT(1);
    write32((MAC_REG + SYS_RBUF_FLUSH_CTRL),reg);

    DELAY_MICROS(10);
    write32((MAC_REG + SYS_RBUF_FLUSH_CTRL),0);
    DELAY_MICROS(10);
    write32(MAC_REG + UMAC_CMD, 0);
    write32(MAC_REG + UMAC_CMD, (CMD_SW_RESET | CMD_LCL_LOOP_EN));
    DELAY_MICROS(2);
    write32(MAC_REG + UMAC_CMD, 0);
    /* clear tx/rx counter */
    write32(MAC_REG + UMAC_MIB_CTRL, MIB_RESET_RX | MIB_RESET_TX | MIB_RESET_RUNT);
    write32(MAC_REG + UMAC_MIB_CTRL, 0);
    write32(MAC_REG + UMAC_MAX_FRAME_LEN, ENET_MAX_MTU_SIZE);
    /* init rx registers, enable ip header optimization */
    reg = read32(MAC_REG + RBUF_CTRL);
    reg |= RBUF_ALIGN_2B;
    write32(MAC_REG + RBUF_CTRL, reg);
    write32(MAC_REG + RBUF_TBUF_SIZE_CTRL, 1);
}

static void bcmgenet_disable_dma(void)
{
    rt_uint32_t tdma_reg = 0, rdma_reg = 0;

    tdma_reg = read32(MAC_REG + TDMA_REG_BASE + DMA_CTRL);
    tdma_reg &= ~(1UL << DMA_EN);
    write32(MAC_REG + TDMA_REG_BASE + DMA_CTRL, tdma_reg);
    rdma_reg = read32(MAC_REG + RDMA_REG_BASE + DMA_CTRL);
    rdma_reg &= ~(1UL << DMA_EN);
    write32(MAC_REG + RDMA_REG_BASE + DMA_CTRL, rdma_reg);
    write32(MAC_REG + UMAC_TX_FLUSH, 1);
    DELAY_MICROS(100);
    write32(MAC_REG + UMAC_TX_FLUSH, 0);
}

static void bcmgenet_enable_dma(void)
{
    rt_uint32_t reg = 0;
    rt_uint32_t dma_ctrl = 0;

    dma_ctrl = (1 << (DEFAULT_Q + DMA_RING_BUF_EN_SHIFT)) | DMA_EN;
    write32(MAC_REG + TDMA_REG_BASE + DMA_CTRL, dma_ctrl);

    reg = read32(MAC_REG + RDMA_REG_BASE + DMA_CTRL);
    write32(MAC_REG + RDMA_REG_BASE + DMA_CTRL, dma_ctrl | reg);
}

static int bcmgenet_mdio_write(rt_uint32_t addr, rt_uint32_t reg, rt_uint32_t value)
{
    int count = 10000;
    rt_uint32_t val;
    val = MDIO_WR | (addr << MDIO_PMD_SHIFT) |(reg << MDIO_REG_SHIFT) | (0xffff & value);
    write32(MAC_REG + MDIO_CMD, val);

    rt_uint32_t reg_val = read32(MAC_REG + MDIO_CMD);
    reg_val = reg_val | MDIO_START_BUSY;
    write32(MAC_REG + MDIO_CMD, reg_val);

    while ((read32(MAC_REG + MDIO_CMD) & MDIO_START_BUSY) && (--count))
        DELAY_MICROS(1);

    reg_val = read32(MAC_REG + MDIO_CMD);

    return reg_val & 0xffff;
    
}

static int bcmgenet_mdio_read(rt_uint32_t addr, rt_uint32_t reg)
{
    int count = 10000;
    rt_uint32_t val = 0;
    rt_uint32_t reg_val = 0;

    val = MDIO_RD | (addr << MDIO_PMD_SHIFT) | (reg << MDIO_REG_SHIFT);
    write32(MAC_REG + MDIO_CMD, val);

    reg_val = read32(MAC_REG + MDIO_CMD);
    reg_val = reg_val | MDIO_START_BUSY;
    write32(MAC_REG + MDIO_CMD, reg_val);

    while ((read32(MAC_REG + MDIO_CMD) & MDIO_START_BUSY) && (--count))
        DELAY_MICROS(1);

    reg_val = read32(MAC_REG + MDIO_CMD);

    return reg_val & 0xffff;    
}

static int bcmgenet_gmac_write_hwaddr(void)
{
    //{0xdc,0xa6,0x32,0x28,0x22,0x50};
    rt_uint8_t addr[6];
    rt_uint32_t reg;
    bcm271x_mbox_hardware_get_mac_address(&addr[0]);

    reg = addr[0] << 24 | addr[1] << 16 | addr[2] << 8 | addr[3];
    write32(MAC_REG + UMAC_MAC0, reg);

    reg = addr[4] << 8 | addr[5];
    write32(MAC_REG + UMAC_MAC1, reg);
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

    if(BCM54213PE_VERSION_B1 == uid)
    {
        rt_kprintf("version is B1\n");
    }
    return uid;
}

static void bcmgenet_mdio_init(void)
{
    rt_uint32_t ret = 0;
    /*get ethernet uid*/
    ret = get_ethernet_uid();
    if(ret == 0)
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
    bcmgenet_mdio_write(1,BCM54213PE_MII_CONTROL,(MII_CONTROL_AUTO_NEGOTIATION_ENABLED | MII_CONTROL_AUTO_NEGOTIATION_RESTART| MII_CONTROL_PHY_FULL_DUPLEX| MII_CONTROL_SPEED_SELECTION));
}

static void rx_ring_init(void)
{
    write32(MAC_REG + RDMA_REG_BASE + DMA_SCB_BURST_SIZE, DMA_MAX_BURST_LENGTH);
    write32(MAC_REG + RDMA_RING_REG_BASE + DMA_START_ADDR,0x0 );
    write32(MAC_REG + RDMA_READ_PTR, 0x0);
    write32(MAC_REG + RDMA_WRITE_PTR, 0x0);
    write32(MAC_REG + RDMA_RING_REG_BASE + DMA_END_ADDR, RX_DESCS * DMA_DESC_SIZE / 4 - 1);

    write32(MAC_REG + RDMA_PROD_INDEX, 0x0);
    write32(MAC_REG + RDMA_CONS_INDEX, 0x0);
    write32(MAC_REG + RDMA_RING_REG_BASE + DMA_RING_BUF_SIZE, (RX_DESCS << DMA_RING_SIZE_SHIFT) | RX_BUF_LENGTH);
    write32(MAC_REG + RDMA_XON_XOFF_THRESH, DMA_FC_THRESH_VALUE);
    write32(MAC_REG + RDMA_REG_BASE + DMA_RING_CFG,1 << DEFAULT_Q);
}

static void tx_ring_init(void)
{
    write32(MAC_REG + TDMA_REG_BASE + DMA_SCB_BURST_SIZE, DMA_MAX_BURST_LENGTH);
    write32(MAC_REG + TDMA_RING_REG_BASE + DMA_START_ADDR, 0x0);
    write32(MAC_REG + TDMA_READ_PTR, 0x0);
    write32(MAC_REG + TDMA_READ_PTR, 0x0);
    write32(MAC_REG + TDMA_READ_PTR, 0x0);
    write32(MAC_REG + TDMA_WRITE_PTR, 0x0);
    write32(MAC_REG + TDMA_RING_REG_BASE + DMA_END_ADDR,TX_DESCS * DMA_DESC_SIZE / 4 - 1);
    write32(MAC_REG + TDMA_PROD_INDEX, 0x0);
    write32(MAC_REG + TDMA_CONS_INDEX, 0x0);
    write32(MAC_REG + TDMA_RING_REG_BASE + DMA_MBUF_DONE_THRESH,0x1);
    write32(MAC_REG + TDMA_FLOW_PERIOD,0x0);
    write32(MAC_REG + TDMA_RING_REG_BASE + DMA_RING_BUF_SIZE, (TX_DESCS << DMA_RING_SIZE_SHIFT) | RX_BUF_LENGTH);
    write32(MAC_REG + TDMA_REG_BASE + DMA_RING_CFG,1 << DEFAULT_Q);
}

static void rx_descs_init(void)
{
    char *rxbuffs = (char *)RECV_DATA_NO_CACHE;
    rt_uint32_t len_stat, i;
    void *desc_base = (void *)RX_DESC_BASE;

    len_stat = (RX_BUF_LENGTH << DMA_BUFLENGTH_SHIFT) | DMA_OWN;
    for (i = 0; i < RX_DESCS; i++) {
        write32((desc_base + i * DMA_DESC_SIZE + DMA_DESC_ADDRESS_LO), lower_32_bits((uintptr_t)&rxbuffs[i * RX_BUF_LENGTH]));
        write32((desc_base + i * DMA_DESC_SIZE + DMA_DESC_ADDRESS_HI),upper_32_bits((uintptr_t)&rxbuffs[i * RX_BUF_LENGTH]));
        write32((desc_base + i * DMA_DESC_SIZE + DMA_DESC_LENGTH_STATUS),len_stat);
    }
}

static int phy_startup(void)
{
    int count = 1000000;
    while ((bcmgenet_mdio_read(1, BCM54213PE_MII_STATUS) & MII_STATUS_LINK_UP) && (--count))
    DELAY_MICROS(1);
    if(count > 0)
    {
        rt_kprintf("bcmgenet: PHY startup ok!\n");
    }
    else
    {
        rt_kprintf("bcmgenet: PHY startup err!\n");
        return 1;
    }

    if(bcmgenet_mdio_read(1, BCM54213PE_STATUS) == 0)
    {
        //todo
    }
    else
    {
        rt_kprintf("bcmgenet: BCM54213PE_STATUS err!\n");
    }

    if(bcmgenet_mdio_read(1, BCM54213PE_CONTROL) == (CONTROL_FULL_DUPLEX_CAPABILITY| CONTROL_HALF_DUPLEX_CAPABILITY))
    {
        //todo
    }
    else
    {
        rt_kprintf("bcmgenet: BCM54213PE_CONTROL err!\n");
    }

    return 0;
}

static int bcmgenet_adjust_link(void)
{
    rt_uint32_t speed;
    rt_uint32_t phy_dev_speed = SPEED_100;
    
    switch (phy_dev_speed) {
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

    rt_uint32_t reg1 = read32(MAC_REG + EXT_RGMII_OOB_CTRL);
    //reg1 &= ~(1UL << OOB_DISABLE);

    //rt_kprintf("OOB_DISABLE is %d\n", OOB_DISABLE);
    reg1 |= (RGMII_LINK | RGMII_MODE_EN | ID_MODE_DIS);
    write32(MAC_REG + EXT_RGMII_OOB_CTRL, reg1);
    DELAY_MICROS(1000);
    write32(MAC_REG + UMAC_CMD, speed << CMD_SPEED_SHIFT);
    return 0;
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

    /* read PHY properties over the wire from generic PHY set-up */
    ret = phy_startup();
    if (ret) {
        rt_kprintf("bcmgenet: PHY startup failed: %d\n", ret);
        return ret;
    }

    /* Update MAC registers based on PHY property */
    ret = bcmgenet_adjust_link();
    if (ret) {
        rt_kprintf("bcmgenet: adjust PHY link failed: %d\n", ret);
        return ret;
    }

    /* wait tx index clear */
    while ((read32(MAC_REG + TDMA_CONS_INDEX) != 0) && (--count))
    DELAY_MICROS(1);

    tx_index = read32(MAC_REG + TDMA_CONS_INDEX);
    write32(MAC_REG + TDMA_PROD_INDEX, tx_index);

    index_flag = read32(MAC_REG + RDMA_PROD_INDEX);

    rx_index = index_flag % 256;

    write32(MAC_REG + RDMA_CONS_INDEX, index_flag);
    write32(MAC_REG + RDMA_PROD_INDEX, index_flag);

    /* Enable Rx/Tx */
    rt_uint32_t rx_tx_en;
    rx_tx_en = read32(MAC_REG + UMAC_CMD);

    rx_tx_en |= (CMD_TX_EN | CMD_RX_EN);

    write32(MAC_REG + UMAC_CMD, rx_tx_en);
    return 0;
}

static rt_uint32_t prev_recv_cnt = 0;
static rt_uint32_t cur_recv_cnt = 0;
static rt_uint32_t bcmgenet_gmac_eth_recv(rt_uint8_t **packetp)
{
    void* desc_base;
    rt_uint32_t length = 0, addr = 0;
    rt_uint32_t prod_index = read32(MAC_REG + RDMA_PROD_INDEX);
    //get next
    if(prod_index == index_flag)
    {
        cur_recv_cnt = index_flag;
        //no buff
        return 0;
    }
    else
    {
        if(prev_recv_cnt == prod_index)
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
        write32(MAC_REG + RDMA_CONS_INDEX, cur_recv_cnt);

        cur_recv_cnt = cur_recv_cnt + 1;
        prev_recv_cnt = cur_recv_cnt;

        return length;
    }
}

static int bcmgenet_gmac_eth_send(void *packet, int length)
{
    void* desc_base = (TX_DESC_BASE + tx_index * DMA_DESC_SIZE);
    rt_uint32_t len_stat = length << DMA_BUFLENGTH_SHIFT;

    rt_uint32_t prod_index, cons;
    rt_uint32_t tries = 100;
    
    prod_index = read32(MAC_REG + TDMA_PROD_INDEX);

    len_stat |= 0x3F << DMA_TX_QTAG_SHIFT;
    len_stat |= DMA_TX_APPEND_CRC | DMA_SOP | DMA_EOP;

    write32((desc_base + DMA_DESC_ADDRESS_LO),SEND_DATA_NO_CACHE);
    write32((desc_base + DMA_DESC_ADDRESS_HI),0);
    write32((desc_base + DMA_DESC_LENGTH_STATUS),len_stat);

    if(++tx_index>= TX_DESCS)
    {
        tx_index = 0;
    }
    prod_index++;
    /* Start Transmisson */
    write32(MAC_REG + TDMA_PROD_INDEX,prod_index);

    do {
        cons = read32(MAC_REG + TDMA_CONS_INDEX);
    } while ((cons & 0xffff) < prod_index && --tries);
    if (!tries)
    {
        return -1;
    }
    return 0;
}

static rt_err_t bcmgenet_eth_init(rt_device_t device)
{
    struct eth_device *eth_device = (struct eth_device *)device;
    RT_ASSERT(eth_device != RT_NULL);
    rt_uint32_t ret = 0;
    rt_uint32_t hw_reg = 0;
    struct rt_eth_dev *dev = &eth_dev;
    
    /* Read GENET HW version */
    rt_uint8_t major = 0;
    hw_reg = read32(MAC_REG + SYS_REV_CTRL);
    major = (hw_reg >> 24) & 0x0f;
    if (major != 6) {
        if (major == 5)
            major = 4;
        else if (major == 0)
            major = 1;

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
    write32(MAC_REG + SYS_RBUF_FLUSH_CTRL, 0);

    /* disable MAC while updating its registers */
    write32(MAC_REG + UMAC_CMD, 0);
    /* issue soft reset with (rg)mii loopback to ensure a stable rxclk */
    write32(MAC_REG + UMAC_CMD, CMD_SW_RESET | CMD_LCL_LOOP_EN);

    bcmgenet_mdio_init();

    bcmgenet_gmac_write_hwaddr();
    bcmgenet_gmac_write_hwaddr();

    bcmgenet_gmac_eth_start();

    //irq or poll
    rt_timer_init(&dev->rx_poll_timer, "rx_poll_timer",
                  eth_rx_irq,
                  NULL,
                  1,
                  RT_TIMER_FLAG_PERIODIC);

    rt_timer_start(&dev->rx_poll_timer);

    return RT_EOK;
}

static rt_err_t bcmgenet_eth_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args) rt_memcpy(args, eth_dev.dev_addr, 6);
        else return -RT_ERROR;
        break;
    default :
        break;
    }
    return RT_EOK;
}

rt_err_t rt_eth_tx(rt_device_t device, struct pbuf *p)
{
    rt_uint32_t sendbuf = SEND_DATA_NO_CACHE;
    /* lock eth device */
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);
    //struct rt_eth_dev *dev = (struct rt_eth_dev *) device;
    pbuf_copy_partial(p, (void *)&send_cache_pbuf[0], p->tot_len, 0);
    rt_memcpy((void *)sendbuf, send_cache_pbuf, p->tot_len);

    bcmgenet_gmac_eth_send((void *)sendbuf, p->tot_len);
    rt_sem_release(&sem_lock);
    return RT_EOK;
}

char recv_data[RX_BUF_LENGTH];
struct pbuf *rt_eth_rx(rt_device_t device)
{
    int recv_len = 0;
    rt_uint32_t addr_point[8];
    struct pbuf *pbuf = RT_NULL;
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

    recv_len = bcmgenet_gmac_eth_recv((rt_uint8_t **)&addr_point[0]);

    if(recv_len > 0)
    {
        pbuf = pbuf_alloc(PBUF_LINK, recv_len, PBUF_RAM);
        rt_memcpy(pbuf->payload, (char *)addr_point[0], recv_len);
    }
    rt_sem_release(&sem_lock);
    return pbuf;
}

int rt_hw_eth_init(void)
{
    rt_uint8_t mac_addr[6];
    
    rt_sem_init(&sem_lock, "eth_lock", 1, RT_IPC_FLAG_FIFO);

    memset(&eth_dev, 0, sizeof(eth_dev));
    memset((void *)SEND_DATA_NO_CACHE, 0, sizeof(DMA_DISC_ADDR_SIZE));
    memset((void *)RECV_DATA_NO_CACHE, 0, sizeof(DMA_DISC_ADDR_SIZE));

    bcm271x_mbox_hardware_get_mac_address(&mac_addr[0]);

    eth_dev.iobase = MAC_REG;
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
    eth_device_linkchange(&eth_dev.parent, RT_TRUE);   //linkup the e0 for lwip to check
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_eth_init);
