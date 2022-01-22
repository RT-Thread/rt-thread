/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <netif/ethernetif.h>

#include "dm9161.h"
#include <sep4020.h>
#include "mii.h"

#define SPEED_10    10
#define SPEED_100   100
#define SPEED_1000  1000
/* Duplex, half or full. */
#define DUPLEX_HALF     0x00
#define DUPLEX_FULL     0x01

/*
 * Davicom dm9161EP driver
 *
 * IRQ_LAN connects to EINT7(GPF7)
 * nLAN_CS connects to nGCS4
 */

/* #define dm9161_DEBUG     1 */
#if DM9161_DEBUG
#define DM9161_TRACE    rt_kprintf
#else
#define DM9161_TRACE(...)
#endif

/*
 * dm9161 interrupt line is connected to PF7
 */
//--------------------------------------------------------

#define DM9161_PHY          0x40    /* PHY address 0x01 */

#define MAX_ADDR_LEN 6
enum DM9161_PHY_mode
{
    DM9161_10MHD = 0, DM9161_100MHD = 1,
    DM9161_10MFD = 4, DM9161_100MFD = 5,
    DM9161_AUTO  = 8, DM9161_1M_HPNA = 0x10
};

enum DM9161_TYPE
{
    TYPE_DM9161,
};

struct rt_dm9161_eth
{
    /* inherit from ethernet device */
    struct eth_device parent;

    enum DM9161_TYPE type;
    enum DM9161_PHY_mode mode;

    rt_uint8_t imr_all;
    rt_uint8_t phy_addr;

    rt_uint32_t tx_index;

    rt_uint8_t packet_cnt;                  /* packet I or II */
    rt_uint16_t queue_packet_len;           /* queued packet (packet II) */

    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];     /* hw address   */
};
static struct rt_dm9161_eth dm9161_device;
static struct rt_semaphore sem_ack, sem_lock;

void rt_dm9161_isr(int irqno, void *param);

static void udelay(unsigned long ns)
{
    unsigned long i;

    while (ns--)
    {
        i = 100;
        while (i--);
    }
}

static __inline unsigned long sep_emac_read(unsigned int reg)
{
    void __iomem *emac_base = (void __iomem *)reg;

    return read_reg(emac_base);
}

/*
* Write to a EMAC register.
*/
static __inline void sep_emac_write(unsigned int reg, unsigned long value)
{
    void __iomem *emac_base = (void __iomem *)reg;

    write_reg(emac_base,value);
}


/* ........................... PHY INTERFACE ........................... */
/*         CAN DO MAC CONFIGRATION
* Enable the MDIO bit in MAC control register
* When not called from an interrupt-handler, access to the PHY must be
*  protected by a spinlock.
*/
static void enable_mdi(void)           //need think more
{
    unsigned long ctl;

    ctl = sep_emac_read(MAC_CTRL);
    sep_emac_write(MAC_CTRL, ctl&(~0x3));    /* enable management port */

    return;
}

/*          CANNOT DO MAC CONFIGRATION
* Disable the MDIO bit in the MAC control register
*/
static void disable_mdi(void)
{
    unsigned long ctl;

    ctl = sep_emac_read(MAC_CTRL);
    sep_emac_write(MAC_CTRL, ctl|(0x3));    /* disable management port */

    return;
}

/*
* Wait until the PHY operation is complete.
*/
static __inline void sep_phy_wait(void)
{
    unsigned long timeout = 2;

    while ((sep_emac_read(MAC_MII_STATUS) & 0x2))
    {
        timeout--;
        if (!timeout)
        {
            EOUT("sep_ether: MDIO timeout\n");
            break;
        }
    }

    return;
}

/*
* Write value to the a PHY register
* Note: MDI interface is assumed to already have been enabled.
*/
static void write_phy(unsigned char phy_addr, unsigned char address, unsigned int value)
{
    unsigned short mii_txdata;

    mii_txdata = value;
    sep_emac_write(MAC_MII_ADDRESS,(unsigned long)(address<<8) | phy_addr);
    sep_emac_write(MAC_MII_TXDATA ,mii_txdata);
    sep_emac_write(MAC_MII_CMD ,0x4);
    udelay(40);

    sep_phy_wait();

    return;
}

/*
* Read value stored in a PHY register.
* Note: MDI interface is assumed to already have been enabled.
*/
static void read_phy(unsigned char phy_addr, unsigned char address, unsigned int *value)
{
    unsigned short mii_rxdata;
//  unsigned long mii_status;

    sep_emac_write(MAC_MII_ADDRESS,(unsigned long)(address<<8) | phy_addr);
    sep_emac_write(MAC_MII_CMD ,0x2);
    udelay(40);
    sep_phy_wait();

    mii_rxdata = sep_emac_read(MAC_MII_RXDATA);
    *value =  mii_rxdata;

    return;
}

/* interrupt service routine */
void rt_dm9161_isr(int irqno, void *param)
{
    unsigned long intstatus;
    rt_uint32_t address;

    mask_irq(INTSRC_MAC);
    intstatus = sep_emac_read(MAC_INTSRC);

    sep_emac_write(MAC_INTSRC,intstatus);

    /*Receive complete*/
    if(intstatus & 0x04)
    {
        eth_device_ready(&(dm9161_device.parent));
    }
    /*Receive error*/
    else if(intstatus & 0x08)
    {
        rt_kprintf("Receive error\n");
    }
    /*Transmit complete*/
    else if(intstatus & 0x03)
    {
            if(dm9161_device.tx_index == 0)
                address = (MAC_TX_BD +(MAX_TX_DESCR-2)*8);
            else if(dm9161_device.tx_index == 1)
                address = (MAC_TX_BD +(MAX_TX_DESCR-1)*8);
            else
                address = (MAC_TX_BD + dm9161_device.tx_index*8-16);
            //printk("free tx skb 0x%x in inter!!\n",lp->txBuffIndex);
            sep_emac_write(address,0x0);
    }
    else if (intstatus & 0x10)
    {
        rt_kprintf("ROVER ERROR\n");
    }

    while(intstatus)
    {
        sep_emac_write(MAC_INTSRC,intstatus);
        intstatus = sep_emac_read(MAC_INTSRC);
    }

    unmask_irq(INTSRC_MAC);
}

static rt_err_t update_mac_address()
{
    rt_uint32_t lo,hi;
    hi = sep_emac_read(MAC_ADDR1);
    lo = sep_emac_read(MAC_ADDR0);
    DBOUT("Before MAC: hi=%x lo=%x\n",hi,lo);

    sep_emac_write(MAC_ADDR0,(dm9161_device.dev_addr[2] << 24) | (dm9161_device.dev_addr[3] << 16) | (dm9161_device.dev_addr[4] << 8) | (dm9161_device.dev_addr[5]));
    sep_emac_write(MAC_ADDR1,dm9161_device.dev_addr[1]|(dm9161_device.dev_addr[0]<<8));

    hi = sep_emac_read(MAC_ADDR1);
    lo = sep_emac_read(MAC_ADDR0);
    DBOUT("After MAC: hi=%x lo=%x\n",hi,lo);

    return RT_EOK;
}

static int mii_link_ok(unsigned long phy_id)
{
    /* first, a dummy read, needed to latch some MII phys */
    unsigned int value;

    read_phy(phy_id, MII_BMSR,&value);
    if (value & BMSR_LSTATUS)
        return 1;

    return 0;
}

static void update_link_speed(unsigned short phy_addr)
{
    unsigned int bmsr, bmcr, lpa, mac_cfg;
    unsigned int speed, duplex;

    if (!mii_link_ok(phy_addr))
    {
        EOUT("Link Down\n");
        //goto result;
    }

    read_phy(phy_addr,MII_BMSR,&bmsr);
    read_phy(phy_addr,MII_BMCR,&bmcr);

    if (bmcr & BMCR_ANENABLE)                /* AutoNegotiation is enabled */
    {
        if (!(bmsr & BMSR_ANEGCOMPLETE))              /* Do nothing - another interrupt generated when negotiation complete */
            goto result;

        read_phy(phy_addr, MII_LPA, &lpa);

        if ((lpa & LPA_100FULL) || (lpa & LPA_100HALF))
            speed = SPEED_100;
        else
            speed = SPEED_10;

        if ((lpa & LPA_100FULL) || (lpa & LPA_10FULL))
            duplex = DUPLEX_FULL;
        else
            duplex = DUPLEX_HALF;
    }
    else
    {
        speed = (bmcr & BMCR_SPEED100) ? SPEED_100 : SPEED_10;
        duplex = (bmcr & BMCR_FULLDPLX) ? DUPLEX_FULL : DUPLEX_HALF;
    }

    /* Update the MAC */
    mac_cfg = sep_emac_read(MAC_CTRL);
    if (speed == SPEED_100)
    {
        mac_cfg |= 0x800;           /* set speed 100 M */
        //bmcr &=(~0x2000);
        //write_phy(lp->phy_address, MII_BMCR, bmcr); //将dm9161的速度设为10M
        if (duplex == DUPLEX_FULL)              /* 100 Full Duplex */
            mac_cfg |= 0x400;
        else                                    /* 100 Half Duplex */
            mac_cfg &= (~0x400);
    }
    else
    {
        mac_cfg &= (~0x800);             /* set speed 10 M */

        if (duplex == DUPLEX_FULL)              /* 10 Full Duplex */
            mac_cfg |= 0x400;
        else                                /* 10 Half Duplex */
            mac_cfg &= (~0x400);
    }

    sep_emac_write(MAC_CTRL, mac_cfg);
    rt_kprintf("Link now %i M-%s\n",  speed, (duplex == DUPLEX_FULL) ? "FullDuplex" : "HalfDuplex");

result:
    mac_cfg = sep_emac_read(MAC_CTRL);
    DBOUT("After mac_cfg=%d\n",mac_cfg);

    return;
}

static rt_err_t rt_dm9161_open(rt_device_t dev, rt_uint16_t oflag);
/* RT-Thread Device Interface */
/* initialize the interface */
static rt_err_t rt_dm9161_init(rt_device_t dev)
{
    unsigned int phyid1, phyid2;
    int detected = -1;
    unsigned long phy_id;
    unsigned short phy_address = 0;

    while ((detected != 0) && (phy_address < 32))
    {
        /* Read the PHY ID registers */
        enable_mdi();
        read_phy(phy_address, MII_PHYSID1, &phyid1);
        read_phy(phy_address, MII_PHYSID2, &phyid2);

        disable_mdi();

        phy_id = (phyid1 << 16) | (phyid2 & 0xfff0);
        switch (phy_id)
        {
            case MII_DM9161_ID:     /* Davicom 9161: PHY_ID1 = 0x181, PHY_ID2 = B881 */
            case MII_DM9161A_ID:        /* Davicom 9161A: PHY_ID1 = 0x181, PHY_ID2 = B8A0 */
            case MII_RTL8201_ID:        /* Realtek RTL8201: PHY_ID1 = 0, PHY_ID2 = 0x8201 */
            case MII_BCM5221_ID:        /* Broadcom BCM5221: PHY_ID1 = 0x40, PHY_ID2 = 0x61e0 */
            case MII_DP83847_ID:        /* National Semiconductor DP83847:  */
            case MII_AC101L_ID:     /* Altima AC101L: PHY_ID1 = 0x22, PHY_ID2 = 0x5520 */
            case MII_KS8721_ID:     /* Micrel KS8721: PHY_ID1 = 0x22, PHY_ID2 = 0x1610 */
            {
                enable_mdi();
                #warning SHOULD SET MAC ADDR
                //get_mac_address(dev);     /* Get ethernet address and store it in dev->dev_addr */
                update_mac_address();   /* Program ethernet address into MAC */

                //用哈希寄存器比较当前群播地址，全双工，添加CRC校验，短数据帧进行填充
                sep_emac_write(MAC_CTRL, 0xa413);
                #warning SHOULD DETERMIN LINK SPEED
                update_link_speed(phy_address);
                dm9161_device.phy_addr = phy_address;
                disable_mdi();
                break;
            }

        }

        phy_address++;
    }

    rt_dm9161_open(dev,0);

    return RT_EOK;
}

/* ................................ MAC ................................ */

/*
 * Initialize and start the Receiver and Transmit subsystems
 */
static void sepether_start(void)
{
    int i;
    unsigned int tempaddr;

    sep_emac_write(MAC_TXBD_NUM,MAX_TX_DESCR);

    //初始化发送和接收描述符
    for (i = 0; i < MAX_TX_DESCR; i++)
    {
        tempaddr=(MAC_TX_BD+i*8);
        sep_emac_write(tempaddr,0);
        tempaddr=(MAC_TX_BD+i*8+4);
        sep_emac_write(tempaddr,0);
    }
    for (i = 0; i < MAX_RX_DESCR; i++)
    {
        tempaddr=(MAC_TX_BD + MAX_TX_DESCR*8+i*8);
        sep_emac_write(tempaddr,0);
        tempaddr=(MAC_TX_BD + MAX_TX_DESCR*8+i*8+4);
        sep_emac_write(tempaddr,0);
    }

    for (i = 0; i < MAX_RX_DESCR; i++)
    {
        tempaddr=(MAC_TX_BD + MAX_TX_DESCR*8+i*8);
        sep_emac_write(tempaddr,0xc000);
        tempaddr=(MAC_TX_BD + MAX_TX_DESCR*8+i*8+4);
        sep_emac_write(tempaddr,ESRAM_BASE+ MAX_TX_DESCR*0x600+i*0x600);
    }

    /* Set the Wrap bit on the last descriptor */
    tempaddr=(MAC_TX_BD + MAX_TX_DESCR*8+i*8-8);
    sep_emac_write(tempaddr,0xe000);

    for (i = 0; i < MAX_TX_DESCR; i++)
    {
        tempaddr=(MAC_TX_BD+i*8);
        sep_emac_write(tempaddr,0x0);
        tempaddr=(MAC_TX_BD+i*8+4);
        sep_emac_write(tempaddr,ESRAM_BASE+i*0x600);
    }

    return;
}

static rt_err_t rt_dm9161_open(rt_device_t dev, rt_uint16_t oflag)
{
    unsigned int dsintr;

    enable_mdi();
    mask_irq(28);

    sep_emac_write(MAC_INTMASK,0x0);  //首先屏蔽中断

    sepether_start();

    /* Enable PHY interrupt */
    *(volatile unsigned long*)GPIO_PORTA_DIR |= 0x0080 ;          //1 stands for in
    *(volatile unsigned long*)GPIO_PORTA_SEL |= 0x0080 ;       //for common use
    *(volatile unsigned long*)GPIO_PORTA_INCTL |= 0x0080;      //中断输入方式
    *(volatile unsigned long*)GPIO_PORTA_INTRCTL |= (0x3UL<<14);    //中断类型为低电平解发
    *(volatile unsigned long*)GPIO_PORTA_INTRCLR |= 0x0080;    //清除中断
    *(volatile unsigned long*)GPIO_PORTA_INTRCLR = 0x0000;          //清除中断

    rt_hw_interrupt_install(INTSRC_MAC, rt_dm9161_isr, RT_NULL, "EMAC");
    enable_irq(INTSRC_EXINT7);


    read_phy(dm9161_device.phy_addr, MII_DSINTR_REG, &dsintr);
    dsintr = dsintr & ~0xf00;       /* clear bits 8..11 */
    write_phy(dm9161_device.phy_addr, MII_DSINTR_REG, dsintr);

    update_link_speed(dm9161_device.phy_addr);


    /************************************************************************************/
    /* Enable MAC interrupts */
    sep_emac_write(MAC_INTMASK,0xff);  //open中断
    sep_emac_write(MAC_INTSRC,0xff);   //clear all mac irq
    unmask_irq(28);
    disable_mdi();

    rt_kprintf("SEP4020 ethernet interface open!\n\r");

    return RT_EOK;
}

static rt_err_t rt_dm9161_close(rt_device_t dev)
{
    rt_kprintf("SEP4020 ethernet interface close!\n\r");

    /* Disable Receiver and Transmitter */
    disable_mdi();
    #warning disable ether;

//  INT_ENABLE(28);
    /* Disable PHY interrupt */
//  disable_phyirq(dev);

    /* Disable MAC interrupts */
    sep_emac_write(MAC_INTMASK,0);  //屏蔽中断

//  INT_DISABLE(28);

    return RT_EOK;
}

static rt_size_t rt_dm9161_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);

    return 0;
}

static rt_size_t rt_dm9161_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);

    return 0;
}

static rt_err_t rt_dm9161_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_dm9161_tx( rt_device_t dev, struct pbuf* p)
{
    rt_uint8_t i;
    rt_uint32_t length = 0;
    struct pbuf *q;
    unsigned long  address;
    unsigned long tmp_tx_bd;

    /* lock DM9000 device */
//  rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

    /* disable dm9000a interrupt */
    #warning SHOULD DISABLE INTEERUPT?

    /*Search for available BD*/
    for (i = 0;i<MAX_TX_DESCR;)
    {
        address = MAC_TX_BD + i*8;
        tmp_tx_bd = sep_emac_read(address);
        if (!(tmp_tx_bd & 0x8000))
        {
            if (i == (MAX_TX_DESCR-1))
                i = 0;
            else
                i = i+1;
            break;
        }
        if (i == MAX_TX_DESCR-1)
            i = 0;
        else
            i++;
    }

    q = p;
    while (q)
    {
        rt_memcpy((u8_t*)(ESRAM_BASE + i*0x600 + length),(u8_t*)q->payload,q->len);
        length += q->len;
        q = q->next;
    }

    #warning SHOULD NOTICE IT'S LENGTH

    length = length << 16;

    if (i == MAX_TX_DESCR - 1)
        length |= 0xb800;
    else
        length |= 0x9800;

    address = (MAC_TX_BD + i*8);
    dm9161_device.tx_index = i;
    sep_emac_write(address,length);

    //wait for tranfer complete
    while(!(sep_emac_read(address)&0x8000));

    /* unlock DM9000 device */
//    rt_sem_release(&sem_lock);

    /* wait ack */
//    rt_sem_take(&sem_ack, RT_WAITING_FOREVER);

    return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_dm9161_rx(rt_device_t dev)
{
    unsigned int temp_rx_bd,address;
    rt_uint32_t i = 0;
    rt_uint32_t length;
    unsigned char *p_recv;
    struct pbuf* p = RT_NULL;

    /* lock DM9000 device */
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

    while (1)
    {

        address = MAC_TX_BD +  (MAX_TX_DESCR + i) * 8;
        temp_rx_bd = sep_emac_read(address);

        if (!(temp_rx_bd & 0x8000))
        {
            length = temp_rx_bd;
            length = length >> 16;

            p_recv = (unsigned char *)(ESRAM_BASE + (MAX_TX_DESCR + i) * 0x600);
            p = pbuf_alloc(PBUF_LINK,length,PBUF_RAM);
            if (p != RT_NULL)
            {
                struct pbuf *q;
                rt_int32_t len;

                for (q = p; q != RT_NULL; q = q->next)
                {
                    rt_memcpy((rt_uint8_t *)(q->payload),p_recv,q->len);
                }
            }
            else
            {
                 rt_kprintf("Droping %d packet \n",length);
            }

            if(i == (MAX_RX_DESCR-1))
            {
                sep_emac_write(address,0xe000);
                i = 0;
            }
            else
            {
                sep_emac_write(address,0xc000);
                i++;
            }
        }
        else
            break;
    }

    rt_sem_release(&sem_lock);

    return p;
}

void rt_hw_dm9161_init()
{
    rt_sem_init(&sem_ack, "tx_ack", 1, RT_IPC_FLAG_FIFO);
    rt_sem_init(&sem_lock, "eth_lock", 1, RT_IPC_FLAG_FIFO);

    dm9161_device.type  = TYPE_DM9161;
    dm9161_device.mode  = DM9161_AUTO;
    dm9161_device.packet_cnt = 0;
    dm9161_device.queue_packet_len = 0;

    /*
     * SRAM Tx/Rx pointer automatically return to start address,
     * Packet Transmitted, Packet Received
     */
    #warning NOTICE:
    //dm9161_device.imr_all = IMR_PAR | IMR_PTM | IMR_PRM;

    dm9161_device.dev_addr[0] = 0x01;
    dm9161_device.dev_addr[1] = 0x60;
    dm9161_device.dev_addr[2] = 0x6E;
    dm9161_device.dev_addr[3] = 0x11;
    dm9161_device.dev_addr[4] = 0x02;
    dm9161_device.dev_addr[5] = 0x0F;

    dm9161_device.parent.parent.init       = rt_dm9161_init;
    dm9161_device.parent.parent.open       = rt_dm9161_open;
    dm9161_device.parent.parent.close      = rt_dm9161_close;
    dm9161_device.parent.parent.read       = rt_dm9161_read;
    dm9161_device.parent.parent.write      = rt_dm9161_write;
    dm9161_device.parent.parent.control    = rt_dm9161_control;
    dm9161_device.parent.parent.user_data  = RT_NULL;

    dm9161_device.parent.eth_rx     = rt_dm9161_rx;
    dm9161_device.parent.eth_tx     = rt_dm9161_tx;

    eth_device_init(&(dm9161_device.parent), "e0");

    /* instal interrupt */
    #warning TODO
    //rt_hw_interrupt_install(INTEINT4_7, rt_dm9161_isr, RT_NULL);
    //rt_hw_interrupt_umask(INTEINT4_7);
}

void dm9161a(void)
{
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(dm9161a, dm9161a register dump);
#endif
