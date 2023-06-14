//*****************************************************************************
//
// luminaryif.c - Ethernet Interface File for lwIP TCP/IP Stack
//
//*****************************************************************************

#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_ints.h>
#include <inc/hw_ethernet.h>
#include <driverlib/ethernet.h>
#include <driverlib/interrupt.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/flash.h>
#include <lwip/stats.h>

#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "luminaryif.h"

#define MAX_ADDR_LEN 6

struct net_device
{
    /* inherit from ethernet device */
    struct eth_device parent;

    /* interface address info. */
    rt_uint8_t dev_addr[MAX_ADDR_LEN]; /* hw address	*/
};

static struct net_device luminaryif_dev_entry;
static struct net_device *luminaryif_dev = &luminaryif_dev_entry;
static struct rt_semaphore tx_sem;

//*****************************************************************************
//
// Sanity Check:  This module will NOT work if the following defines
// are incorrect.
//
//*****************************************************************************
#if (PBUF_LINK_HLEN != 16)
#error "Incorrect PBUF_LINK_HLEN specified!"
#endif
#if (ETH_PAD_SIZE != 2)
#error "Incorrect ETH_PAD_SIZE specified!"
#endif
#if (PBUF_POOL_BUFSIZE % 4)
#error "PBUF_POOL_BUFSIZE must be modulo 4!"
#endif

/* RT-Thread Device Interface */

/* initialize the interface */
//*****************************************************************************
//
// Low-Level initialization function for the Ethernet Controller.
//
//*****************************************************************************
rt_err_t luminaryif_init(rt_device_t dev)
{
    unsigned long ulTemp;

    //
    // Disable all Ethernet Interrupts.
    //
    EthernetIntDisable(ETH_BASE, (ETH_INT_PHY | ETH_INT_MDIO | ETH_INT_RXER |
                                  ETH_INT_RXOF | ETH_INT_TX | ETH_INT_TXER |
                                  ETH_INT_RX));
    ulTemp = EthernetIntStatus(ETH_BASE, false);
    EthernetIntClear(ETH_BASE, ulTemp);

    //
    // Initialize the Ethernet Controller.
    //
    EthernetInitExpClk(ETH_BASE, SysCtlClockGet());

    //
    // Configure the Ethernet Controller for normal operation.
    // - Enable TX Duplex Mode
    // - Enable TX Padding
    // - Enable TX CRC Generation
    // - Enable reception of multicast packets
    //
    EthernetConfigSet(ETH_BASE, (ETH_CFG_TX_DPLXEN |
                                 ETH_CFG_TX_CRCEN | ETH_CFG_TX_PADEN | ETH_CFG_RX_AMULEN));

    //
    // Enable the Ethernet Controller transmitter and receiver.
    //
    EthernetEnable(ETH_BASE);

    //
    // Enable the Ethernet Interrupt handler.
    //
    IntEnable(INT_ETH);

    //
    // Enable Ethernet TX and RX Packet Interrupts.
    //
    EthernetIntEnable(ETH_BASE, ETH_INT_RX | ETH_INT_TX);

    return RT_EOK;
}

void luminaryif_isr(void)
{
    unsigned long ulTemp;

    //
    // Read and Clear the interrupt.
    //
    ulTemp = EthernetIntStatus(ETH_BASE, false);
    EthernetIntClear(ETH_BASE, ulTemp);

    //
    // Check to see if an RX Interrupt has occured.
    //
    if (ulTemp & ETH_INT_RX)
    {
        //
        // Indicate that a packet has been received.
        //
        rt_err_t result;

        /* a frame has been received */
        result = eth_device_ready((struct eth_device *)&(luminaryif_dev->parent));

        if (result != RT_EOK)
            rt_set_errno(-RT_ERROR);

        //
        // Disable Ethernet RX Interrupt.
        //
        EthernetIntDisable(ETH_BASE, ETH_INT_RX);
    }
    if (ulTemp & ETH_INT_TX)
    {
        /* A frame has been transmitted. */
        rt_sem_release(&tx_sem);
    }
}

/* control the interface */
rt_err_t luminaryif_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args)
            rt_memcpy(args, luminaryif_dev_entry.dev_addr, 6);
        else
            return -RT_ERROR;
        break;

    default:
        break;
    }

    return RT_EOK;
}

/* Open the ethernet interface */
rt_err_t luminaryif_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

/* Close the interface */
rt_err_t luminaryif_close(rt_device_t dev)
{
    return RT_EOK;
}

/* Read */
rt_size_t luminaryif_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

/* Write */
rt_size_t luminaryif_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

//****************************************************************************
//
// Low-Level transmit routine.  Should do the actual transmission of the
// packet. The packet is contained in the pbuf that is passed to the function.
// This pbuf might be chained.
//
//****************************************************************************
rt_err_t luminaryif_tx(rt_device_t dev, struct pbuf *p)
{
    int iBuf;
    unsigned char *pucBuf;
    unsigned long *pulBuf;
    struct pbuf *q;
    int iGather;
    unsigned long ulGather;
    unsigned char *pucGather;
    unsigned long ulTemp;

    /* lock tx operation */
    rt_sem_take(&tx_sem, RT_WAITING_FOREVER);

    //
    // Wait for space available in the TX FIFO.
    //
    while (!EthernetSpaceAvail(ETH_BASE))
    {
    }

    //
    // Fill in the first two bytes of the payload data (configured as padding
    // with ETH_PAD_SIZE = 2) with the total length of the payload data
    // (minus the Ethernet MAC layer header).
    //
    *((unsigned short *)(p->payload)) = p->tot_len - 16;

    //
    // Initialize the gather register.
    //
    iGather = 0;
    pucGather = (unsigned char *)&ulGather;
    ulGather = 0;

    //
    // Copy data from the pbuf(s) into the TX Fifo.
    //
    for (q = p; q != NULL; q = q->next)
    {
        //
        // Intialize a char pointer and index to the pbuf payload data.
        //
        pucBuf = (unsigned char *)q->payload;
        iBuf = 0;

        //
        // If the gather buffer has leftover data from a previous pbuf
        // in the chain, fill it up and write it to the Tx FIFO.
        //
        while ((iBuf < q->len) && (iGather != 0))
        {
            //
            // Copy a byte from the pbuf into the gather buffer.
            //
            pucGather[iGather] = pucBuf[iBuf++];

            //
            // Increment the gather buffer index modulo 4.
            //
            iGather = ((iGather + 1) % 4);
        }

        //
        // If the gather index is 0 and the pbuf index is non-zero,
        // we have a gather buffer to write into the Tx FIFO.
        //
        if ((iGather == 0) && (iBuf != 0))
        {
            HWREG(ETH_BASE + MAC_O_DATA) = ulGather;
            ulGather = 0;
        }

        //
        // Copy words of pbuf data into the Tx FIFO, but don't go past
        // the end of the pbuf.
        //
        if ((iBuf % 4) != 0)
        {
            while ((iBuf + 4) <= q->len)
            {
                ulTemp = (pucBuf[iBuf++] << 0);
                ulTemp |= (pucBuf[iBuf++] << 8);
                ulTemp |= (pucBuf[iBuf++] << 16);
                ulTemp |= (pucBuf[iBuf++] << 24);
                HWREG(ETH_BASE + MAC_O_DATA) = ulTemp;
            }
        }
        else
        {
            //
            // Initialze a long pointer into the pbuf for 32-bit access.
            //
            pulBuf = (unsigned long *)&pucBuf[iBuf];

            while ((iBuf + 4) <= q->len)
            {
                HWREG(ETH_BASE + MAC_O_DATA) = *pulBuf++;
                iBuf += 4;
            }
        }
        //
        // Check if leftover data in the pbuf and save it in the gather
        // buffer for the next time.
        //
        while (iBuf < q->len)
        {
            //
            // Copy a byte from the pbuf into the gather buffer.
            //
            pucGather[iGather] = pucBuf[iBuf++];

            //
            // Increment the gather buffer index modulo 4.
            //
            iGather = ((iGather + 1) % 4);
        }
    }

    //
    // Send any leftover data to the FIFO.
    //
    HWREG(ETH_BASE + MAC_O_DATA) = ulGather;

    //
    // Wakeup the transmitter.
    //
    HWREG(ETH_BASE + MAC_O_TR) = MAC_TR_NEWTX;

#if LINK_STATS
    lwip_stats.link.xmit++;
#endif

    return (ERR_OK);
}

//*****************************************************************************
//
// Low-Level receive routine.  Should allocate a pbuf and transfer the bytes
// of the incoming packet from the interface into the pbuf.
//
//*****************************************************************************
struct pbuf *luminaryif_rx(rt_device_t dev)
{
    struct pbuf *p, *q;
    u16_t len;
    unsigned long ulTemp;
    int i;
    unsigned long *ptr;

    if (!EthernetPacketAvail(ETH_BASE))
    {
        //
        // Enable Ethernet RX Interrupt.
        //
        EthernetIntEnable(ETH_BASE, ETH_INT_RX);

        return (NULL);
    }

    //
    // Obtain the size of the packet and put it into the "len" variable.
    // Note:  The length returned in the FIFO length position includes the
    // two bytes for the length + the 4 bytes for the FCS.
    //
    ulTemp = HWREG(ETH_BASE + MAC_O_DATA);
    len = ulTemp & 0xFFFF;

    //
    // We allocate a pbuf chain of pbufs from the pool.
    //
    p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);

    if (p != NULL)
    {
        //
        // Place the first word into the first pbuf location.
        //
        *(unsigned long *)p->payload = ulTemp;
        p->payload = (char *)(p->payload) + 4;
        p->len -= 4;

        //
        // Process all but the last buffer in the pbuf chain.
        //
        q = p;
        while (q != NULL)
        {
            //
            // Setup a byte pointer into the payload section of the pbuf.
            //
            ptr = q->payload;

            //
            // Read data from FIFO into the current pbuf
            // (assume pbuf length is modulo 4)
            //
            for (i = 0; i < q->len; i += 4)
            {
                *ptr++ = HWREG(ETH_BASE + MAC_O_DATA);
            }

            //
            // Link in the next pbuf in the chain.
            //
            q = q->next;
        }

        //
        // Restore the first pbuf parameters to their original values.
        //
        p->payload = (char *)(p->payload) - 4;
        p->len += 4;

#if LINK_STATS
        lwip_stats.link.recv++;
#endif
    }
    else
    {
        //
        // Just read all of the remaining data from the FIFO and dump it.
        //
        for (i = 4; i < len; i += 4)
        {
            ulTemp = HWREG(ETH_BASE + MAC_O_DATA);
        }

#if LINK_STATS
        lwip_stats.link.memerr++;
        lwip_stats.link.drop++;
#endif
        //
        // Enable Ethernet RX Interrupt.
        //
        EthernetIntEnable(ETH_BASE, ETH_INT_RX);
    }

    return (p);
}

int rt_hw_luminaryif_init(void)
{
    rt_err_t result;
    unsigned long ulUser0, ulUser1;

    /* Enable and Reset the Ethernet Controller. */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ETH);
    SysCtlPeripheralReset(SYSCTL_PERIPH_ETH);

    /*
    Enable Port F for Ethernet LEDs.
    LED0        Bit 3   Output
    LED1        Bit 2   Output
    */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3, GPIO_DIR_MODE_HW);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);

    FlashUserSet(0x12345678, 0x12345678);
    /* Configure the hardware MAC address */
    FlashUserGet(&ulUser0, &ulUser1);
    if ((ulUser0 == 0xffffffff) || (ulUser1 == 0xffffffff))
    {
        rt_kprintf("Fatal error in geting MAC address\n");
    }

    /* init rt-thread device interface */
    luminaryif_dev_entry.parent.parent.init = luminaryif_init;
    luminaryif_dev_entry.parent.parent.open = luminaryif_open;
    luminaryif_dev_entry.parent.parent.close = luminaryif_close;
    luminaryif_dev_entry.parent.parent.read = luminaryif_read;
    luminaryif_dev_entry.parent.parent.write = luminaryif_write;
    luminaryif_dev_entry.parent.parent.control = luminaryif_control;
    luminaryif_dev_entry.parent.eth_rx = luminaryif_rx;
    luminaryif_dev_entry.parent.eth_tx = luminaryif_tx;

    /*
    Convert the 24/24 split MAC address from NV ram into a 32/16 split MAC
    address needed to program the hardware registers, then program the MAC
    address into the Ethernet Controller registers.
    */
    luminaryif_dev_entry.dev_addr[0] = ((ulUser0 >> 0) & 0xff);
    luminaryif_dev_entry.dev_addr[1] = ((ulUser0 >> 8) & 0xff);
    luminaryif_dev_entry.dev_addr[2] = ((ulUser0 >> 16) & 0xff);
    luminaryif_dev_entry.dev_addr[3] = ((ulUser1 >> 0) & 0xff);
    luminaryif_dev_entry.dev_addr[4] = ((ulUser1 >> 8) & 0xff);
    luminaryif_dev_entry.dev_addr[5] = ((ulUser1 >> 16) & 0xff);

    /* Program the hardware with it's MAC address (for filtering). */
    EthernetMACAddrSet(ETH_BASE, luminaryif_dev_entry.dev_addr);

    rt_sem_init(&tx_sem, "emac", 1, RT_IPC_FLAG_FIFO);

    result = eth_device_init(&(luminaryif_dev->parent), "E0");

    return result;
}
