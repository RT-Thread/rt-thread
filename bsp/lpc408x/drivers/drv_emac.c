/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-19     Bernard      porting from LPC17xx drivers.
 */

#include <rtthread.h>
#include "lwipopts.h"
#include <netif/ethernetif.h>
#include <board.h>

#include "lpc_pinsel.h"
#include "drv_emac.h"

#define EMAC_PHY_AUTO       0
#define EMAC_PHY_10MBIT     1
#define EMAC_PHY_100MBIT    2

#define MAX_ADDR_LEN 6

/* EMAC_RAM_BASE is defined in board.h and the size is 16KB */
#define RX_DESC_BASE        ETH_RAM_BASE
#define RX_STAT_BASE        (RX_DESC_BASE + NUM_RX_FRAG*8)
#define TX_DESC_BASE        (RX_STAT_BASE + NUM_RX_FRAG*8)
#define TX_STAT_BASE        (TX_DESC_BASE + NUM_TX_FRAG*8)
#define RX_BUF_BASE         (TX_STAT_BASE + NUM_TX_FRAG*4)
#define TX_BUF_BASE         (RX_BUF_BASE  + NUM_RX_FRAG*ETH_FRAG_SIZE)

/* RX and TX descriptor and status definitions. */
#define RX_DESC_PACKET(i)   (*(unsigned int *)(RX_DESC_BASE   + 8*i))
#define RX_DESC_CTRL(i)     (*(unsigned int *)(RX_DESC_BASE+4 + 8*i))
#define RX_STAT_INFO(i)     (*(unsigned int *)(RX_STAT_BASE   + 8*i))
#define RX_STAT_HASHCRC(i)  (*(unsigned int *)(RX_STAT_BASE+4 + 8*i))
#define TX_DESC_PACKET(i)   (*(unsigned int *)(TX_DESC_BASE   + 8*i))
#define TX_DESC_CTRL(i)     (*(unsigned int *)(TX_DESC_BASE+4 + 8*i))
#define TX_STAT_INFO(i)     (*(unsigned int *)(TX_STAT_BASE   + 4*i))
#define RX_BUF(i)           (RX_BUF_BASE + ETH_FRAG_SIZE*i)
#define TX_BUF(i)           (TX_BUF_BASE + ETH_FRAG_SIZE*i)

struct lpc_emac
{
    /* inherit from ethernet device */
    struct eth_device parent;

    rt_uint8_t phy_mode;

    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];     /* hw address   */
};
static struct lpc_emac lpc_emac_device;
static struct rt_semaphore sem_lock;
static struct rt_event tx_event;

/* Local Function Prototypes */
static void write_PHY(rt_uint32_t PhyReg, rt_uint32_t Value);
static rt_uint16_t read_PHY(rt_uint8_t PhyReg) ;

void ENET_IRQHandler(void)
{
    rt_uint32_t status;

    /* enter interrupt */
    rt_interrupt_enter();

    status = LPC_EMAC->IntStatus;

    if (status & INT_RX_DONE)
    {
        /* Disable EMAC RxDone interrupts. */
        LPC_EMAC->IntEnable = INT_TX_DONE;

        /* a frame has been received */
        eth_device_ready(&(lpc_emac_device.parent));
    }
    else if (status & INT_TX_DONE)
    {
        /* set event */
        rt_event_send(&tx_event, 0x01);
    }

    if (status & INT_RX_OVERRUN)
    {
        rt_kprintf("rx overrun\n");
    }

    if (status & INT_TX_UNDERRUN)
    {
        rt_kprintf("tx underrun\n");
    }

    /* Clear the interrupt. */
    LPC_EMAC->IntClear = status;

    /* leave interrupt */
    rt_interrupt_leave();
}

/* phy write */
static void write_PHY(rt_uint32_t PhyReg, rt_uint32_t Value)
{
    unsigned int tout;

    LPC_EMAC->MADR = DP83848C_DEF_ADR | PhyReg;
    LPC_EMAC->MWTD = Value;

    /* Wait utill operation completed */
    tout = 0;
    for (tout = 0; tout < MII_WR_TOUT; tout++)
    {
        if ((LPC_EMAC->MIND & MIND_BUSY) == 0)
        {
            break;
        }
    }
}

/* phy read */
static rt_uint16_t read_PHY(rt_uint8_t PhyReg)
{
    rt_uint32_t tout;

    LPC_EMAC->MADR = DP83848C_DEF_ADR | PhyReg;
    LPC_EMAC->MCMD = MCMD_READ;

    /* Wait until operation completed */
    tout = 0;
    for (tout = 0; tout < MII_RD_TOUT; tout++)
    {
        if ((LPC_EMAC->MIND & MIND_BUSY) == 0)
        {
            break;
        }
    }
    LPC_EMAC->MCMD = 0;
    return (LPC_EMAC->MRDD);
}

/* init rx descriptor */
rt_inline void rx_descr_init(void)
{
    rt_uint32_t i;

    for (i = 0; i < NUM_RX_FRAG; i++)
    {
        RX_DESC_PACKET(i)  = RX_BUF(i);
        RX_DESC_CTRL(i)    = RCTRL_INT | (ETH_FRAG_SIZE - 1);
        RX_STAT_INFO(i)    = 0;
        RX_STAT_HASHCRC(i) = 0;
    }

    /* Set EMAC Receive Descriptor Registers. */
    LPC_EMAC->RxDescriptor    = RX_DESC_BASE;
    LPC_EMAC->RxStatus        = RX_STAT_BASE;
    LPC_EMAC->RxDescriptorNumber = NUM_RX_FRAG - 1;

    /* Rx Descriptors Point to 0 */
    LPC_EMAC->RxConsumeIndex  = 0;
}

/* init tx descriptor */
rt_inline void tx_descr_init(void)
{
    rt_uint32_t i;

    for (i = 0; i < NUM_TX_FRAG; i++)
    {
        TX_DESC_PACKET(i) = TX_BUF(i);
        TX_DESC_CTRL(i)   = (1ul << 31) | (1ul << 30) | (1ul << 29) | (1ul << 28) | (1ul << 26) | (ETH_FRAG_SIZE - 1);
        TX_STAT_INFO(i)   = 0;
    }

    /* Set EMAC Transmit Descriptor Registers. */
    LPC_EMAC->TxDescriptor    = TX_DESC_BASE;
    LPC_EMAC->TxStatus        = TX_STAT_BASE;
    LPC_EMAC->TxDescriptorNumber = NUM_TX_FRAG - 1;

    /* Tx Descriptors Point to 0 */
    LPC_EMAC->TxProduceIndex  = 0;
}

/*
TX_EN     P1_4
TXD0      P1_0
TXD1      P1_1

RXD0      P1_9
RXD1      P1_10
RX_ER     P1_14
CRS_DV    P1_8

MDC       P1_16
MDIO      P1_17

REF_CLK   P1_15
*/
static rt_err_t lpc_emac_init(rt_device_t dev)
{
    /* Initialize the EMAC ethernet controller. */
    rt_uint32_t regv, tout;

    /* Power Up the EMAC controller. */
    LPC_SC->PCONP |= (1UL << 30);

    /* Enable P1 Ethernet Pins. */
    PINSEL_ConfigPin(1, 0, 1);  /**< P1_0  ENET_TXD0 */
    PINSEL_ConfigPin(1, 1, 1);  /**< P1_1  ENET_TXD1 */
    PINSEL_ConfigPin(1, 4, 1);  /**< P1_4  ENET_TX_EN */
    PINSEL_ConfigPin(1, 8, 1);  /**< P1_8  ENET_CRS_DV */
    PINSEL_ConfigPin(1, 9, 1);  /**< P1_9  ENET_RXD0 */
    PINSEL_ConfigPin(1, 10, 1); /**< P1_10 ENET_RXD1 */
    PINSEL_ConfigPin(1, 14, 1); /**< P1_14 ENET_RX_ER */
    PINSEL_ConfigPin(1, 15, 1); /**< P1_15 ENET_REF_CLK */
    PINSEL_ConfigPin(1, 16, 1); /**< P1_16 ENET_MDC */
    PINSEL_ConfigPin(1, 17, 1); /**< P1_17 ENET_MDIO */

    /* Reset all EMAC internal modules. */
    LPC_EMAC->MAC1 = MAC1_RES_TX | MAC1_RES_MCS_TX | MAC1_RES_RX | MAC1_RES_MCS_RX |
                     MAC1_SIM_RES | MAC1_SOFT_RES;
    LPC_EMAC->Command = CR_REG_RES | CR_TX_RES | CR_RX_RES;

    /* A short delay after reset. */
    for (tout = 100; tout; tout--);

    /* Initialize MAC control registers. */
    LPC_EMAC->MAC1 = MAC1_PASS_ALL;
    LPC_EMAC->MAC2 = MAC2_CRC_EN | MAC2_PAD_EN;
    LPC_EMAC->MAXF = ETH_MAX_FLEN;
    LPC_EMAC->CLRT = CLRT_DEF;
    LPC_EMAC->IPGR = IPGR_DEF;

    /* PCLK=18MHz, clock select=6, MDC=18/6=3MHz */
    /* Enable Reduced MII interface. */
    LPC_EMAC->MCFG = MCFG_CLK_DIV20 | MCFG_RES_MII;
    for (tout = 100; tout; tout--);
    LPC_EMAC->MCFG = MCFG_CLK_DIV20;

    /* Enable Reduced MII interface. */
    LPC_EMAC->Command = CR_RMII | CR_PASS_RUNT_FRM | CR_PASS_RX_FILT;

    /* Reset Reduced MII Logic. */
    LPC_EMAC->SUPP = SUPP_RES_RMII | SUPP_SPEED;
    for (tout = 100; tout; tout--);
    LPC_EMAC->SUPP = SUPP_SPEED;

    /* Put the PHY in reset mode */
    write_PHY(PHY_REG_BMCR, 0x8000);
    for (tout = 1000; tout; tout--);

    /* Configure the PHY device */
    /* Configure the PHY device */
    switch (lpc_emac_device.phy_mode)
    {
    case EMAC_PHY_AUTO:
        /* Use autonegotiation about the link speed. */
        write_PHY(PHY_REG_BMCR, PHY_AUTO_NEG);
        break;
    case EMAC_PHY_10MBIT:
        /* Connect at 10MBit */
        write_PHY(PHY_REG_BMCR, PHY_FULLD_10M);
        break;
    case EMAC_PHY_100MBIT:
        /* Connect at 100MBit */
        write_PHY(PHY_REG_BMCR, PHY_FULLD_100M);
        break;
    }
    if (tout >= 0x100000) return -RT_ERROR; // auto_neg failed

    regv = 0x0004;
    /* Configure Full/Half Duplex mode. */
    if (regv & 0x0004)
    {
        /* Full duplex is enabled. */
        LPC_EMAC->MAC2    |= MAC2_FULL_DUP;
        LPC_EMAC->Command |= CR_FULL_DUP;
        LPC_EMAC->IPGT     = IPGT_FULL_DUP;
    }
    else
    {
        /* Half duplex mode. */
        LPC_EMAC->IPGT = IPGT_HALF_DUP;
    }

    /* Configure 100MBit/10MBit mode. */
    if (regv & 0x0002)
    {
        /* 10MBit mode. */
        LPC_EMAC->SUPP = 0;
    }
    else
    {
        /* 100MBit mode. */
        LPC_EMAC->SUPP = SUPP_SPEED;
    }

    /* Set the Ethernet MAC Address registers */
    LPC_EMAC->SA0 = (lpc_emac_device.dev_addr[1] << 8) | lpc_emac_device.dev_addr[0];
    LPC_EMAC->SA1 = (lpc_emac_device.dev_addr[3] << 8) | lpc_emac_device.dev_addr[2];
    LPC_EMAC->SA2 = (lpc_emac_device.dev_addr[5] << 8) | lpc_emac_device.dev_addr[4];

    /* Initialize Tx and Rx DMA Descriptors */
    rx_descr_init();
    tx_descr_init();

    /* Receive Broadcast and Perfect Match Packets */
    LPC_EMAC->RxFilterCtrl = RFC_BCAST_EN | RFC_PERFECT_EN;

    /* Reset all interrupts */
    LPC_EMAC->IntClear  = 0xFFFF;

    /* Enable EMAC interrupts. */
    LPC_EMAC->IntEnable = INT_RX_DONE | INT_TX_DONE;

    /* Enable receive and transmit mode of MAC Ethernet core */
    LPC_EMAC->Command  |= (CR_RX_EN | CR_TX_EN);
    LPC_EMAC->MAC1     |= MAC1_REC_EN;

    /* Enable the ENET Interrupt */
    NVIC_EnableIRQ(ENET_IRQn);

    return RT_EOK;
}

static rt_err_t lpc_emac_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t lpc_emac_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t lpc_emac_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_size_t lpc_emac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t lpc_emac_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args) rt_memcpy(args, lpc_emac_device.dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

/* EtherNet Device Interface */
/* transmit packet. */
rt_err_t lpc_emac_tx(rt_device_t dev, struct pbuf *p)
{
    rt_uint32_t Index, IndexNext;
    rt_uint8_t *ptr;

    /* calculate next index */
    IndexNext = LPC_EMAC->TxProduceIndex + 1;
    if (IndexNext > LPC_EMAC->TxDescriptorNumber) IndexNext = 0;

    /* check whether block is full */
    while (IndexNext == LPC_EMAC->TxConsumeIndex)
    {
        rt_err_t result;
        rt_uint32_t recved;

        /* there is no block yet, wait a flag */
        result = rt_event_recv(&tx_event, 0x01,
                               RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, &recved);

        RT_ASSERT(result == RT_EOK);
    }

    /* lock EMAC device */
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

    /* get produce index */
    Index = LPC_EMAC->TxProduceIndex;

    /* calculate next index */
    IndexNext = LPC_EMAC->TxProduceIndex + 1;
    if (IndexNext > LPC_EMAC->TxDescriptorNumber)
        IndexNext = 0;

    /* copy data to tx buffer */
    ptr = (rt_uint8_t *)TX_BUF(Index);
    pbuf_copy_partial(p, ptr, p->tot_len, 0);

    TX_DESC_CTRL(Index) &= ~0x7ff;
    TX_DESC_CTRL(Index) |= (p->tot_len - 1) & 0x7ff;

    /* change index to the next */
    LPC_EMAC->TxProduceIndex = IndexNext;

    /* unlock EMAC device */
    rt_sem_release(&sem_lock);

    return RT_EOK;
}

/* reception packet. */
struct pbuf *lpc_emac_rx(rt_device_t dev)
{
    struct pbuf *p;
    rt_uint32_t size;
    rt_uint32_t Index;

    /* init p pointer */
    p = RT_NULL;

    /* lock EMAC device */
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

    Index = LPC_EMAC->RxConsumeIndex;
    if (Index != LPC_EMAC->RxProduceIndex)
    {
        size = (RX_STAT_INFO(Index) & 0x7ff) + 1;
        if (size > ETH_FRAG_SIZE) size = ETH_FRAG_SIZE;

        /* allocate buffer */
        p = pbuf_alloc(PBUF_LINK, size, PBUF_RAM);
        if (p != RT_NULL)
        {
            pbuf_take(p, (rt_uint8_t *)RX_BUF(Index), size);
        }

        /* move Index to the next */
        if (++Index > LPC_EMAC->RxDescriptorNumber)
            Index = 0;

        /* set consume index */
        LPC_EMAC->RxConsumeIndex = Index;
    }
    else
    {
        /* Enable RxDone interrupt */
        LPC_EMAC->IntEnable = INT_RX_DONE | INT_TX_DONE;
    }

    /* unlock EMAC device */
    rt_sem_release(&sem_lock);

    return p;
}

int rt_hw_emac_init(void)
{
    rt_event_init(&tx_event, "tx_event", RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_lock, "eth_lock", 1, RT_IPC_FLAG_FIFO);

    /* set autonegotiation mode */
    lpc_emac_device.phy_mode = EMAC_PHY_AUTO;

    // OUI 00-60-37 NXP Semiconductors
    lpc_emac_device.dev_addr[0] = 0x00;
    lpc_emac_device.dev_addr[1] = 0x60;
    lpc_emac_device.dev_addr[2] = 0x37;
    /* set mac address: (only for test) */
    lpc_emac_device.dev_addr[3] = 0x12;
    lpc_emac_device.dev_addr[4] = 0x34;
    lpc_emac_device.dev_addr[5] = 0x56;

    lpc_emac_device.parent.parent.init      = lpc_emac_init;
    lpc_emac_device.parent.parent.open      = lpc_emac_open;
    lpc_emac_device.parent.parent.close     = lpc_emac_close;
    lpc_emac_device.parent.parent.read      = lpc_emac_read;
    lpc_emac_device.parent.parent.write     = lpc_emac_write;
    lpc_emac_device.parent.parent.control   = lpc_emac_control;
    lpc_emac_device.parent.parent.user_data = RT_NULL;

    lpc_emac_device.parent.eth_rx           = lpc_emac_rx;
    lpc_emac_device.parent.eth_tx           = lpc_emac_tx;

    eth_device_init(&(lpc_emac_device.parent), "e0");
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_emac_init);

#ifdef RT_USING_FINSH
#include <finsh.h>
void emac_dump()
{
    rt_kprintf("Command  : %08x\n", LPC_EMAC->Command);
    rt_kprintf("Status   : %08x\n", LPC_EMAC->Status);
    rt_kprintf("RxStatus : %08x\n", LPC_EMAC->RxStatus);
    rt_kprintf("TxStatus : %08x\n", LPC_EMAC->TxStatus);
    rt_kprintf("IntEnable: %08x\n", LPC_EMAC->IntEnable);
    rt_kprintf("IntStatus: %08x\n", LPC_EMAC->IntStatus);
}
FINSH_FUNCTION_EXPORT(emac_dump, dump emac register);
#endif

