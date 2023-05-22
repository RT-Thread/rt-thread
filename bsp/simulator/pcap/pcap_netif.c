/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-05     Bernard      the first version
 * 2012-11-13     Bernard      merge prife's patch for exclusive
 *                             access pcap driver.
 */

#ifdef _TIME_T_DEFINED
#undef _TIME_T_DEFINED
#endif

#ifdef _MSC_VER
/*
 * we do not want the warnings about the old deprecated and unsecure CRT functions
 * since these examples can be compiled under *nix as well
 */
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <pcap.h>

#include <rtthread.h>
#include <netif/ethernetif.h>

#define DBG_TAG    "pcap.netif"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define MAX_ADDR_LEN 6

#define NETIF_DEVICE(netif) ((struct pcap_netif*)(netif))
#define NETIF_PCAP(netif)   (NETIF_DEVICE(netif)->tap)

struct pcap_netif
{
    /* inherit from ethernet device */
    struct eth_device parent;

    pcap_t *tap;
    /* interface address info. */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];     /* hw address   */
};
static struct pcap_netif pcap_netif_device;
static struct rt_semaphore sem_lock;
static rt_mailbox_t packet_mb = RT_NULL;

static void pcap_thread_entry(void* parameter)
{
    pcap_if_t *netif;
    pcap_t *tap;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr *header;
    const u_char *pkt_data;
    int res;

    netif = (pcap_if_t *) parameter;

    /* Open the adapter */
    if ((tap = pcap_open_live(netif->name,
        65536, // portion of the packet to capture.
        1,     // promiscuous mode (nonzero means promiscuous)
        1,     // read timeout, 0 blocked, -1 no timeout
        errbuf )) == NULL)
    {
        rt_kprintf("Unable to open the adapter. %s is not supported by WinPcap\n", netif->name);
        return;
    }

    NETIF_PCAP(&pcap_netif_device) = tap;

    /* Read the packets */
    while (1)
    {
        struct eth_device* eth;
        struct pbuf *p;

        rt_enter_critical();
        res = pcap_next_ex(tap, &header, &pkt_data);
        rt_exit_critical();

        if (res == 0) continue;

        eth = (struct eth_device*) &pcap_netif_device;

        p = pbuf_alloc(PBUF_LINK, header->len, PBUF_RAM);
        pbuf_take(p, pkt_data, header->len);

        /* send to packet mailbox */
        rt_mb_send_wait(packet_mb, (rt_uint32_t)p, RT_WAITING_FOREVER);
        /* notify eth rx thread to receive packet */
        eth_device_ready(eth);
    }
}

static rt_err_t pcap_netif_init(rt_device_t dev)
{
    rt_thread_t tid;
    pcap_if_t *alldevs;
    pcap_if_t *d;
    pcap_t *tap;
    int inum, i=0;
    char errbuf[PCAP_ERRBUF_SIZE];

    /* Retrieve the device list */
    if(pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        rt_kprintf("Error in pcap_findalldevs: %s\n", errbuf);
        return -RT_ERROR;
    }

    /* Print the list */
    for(d = alldevs; d; d = d->next)
    {
        rt_kprintf("%d. %s", ++i, d->name);
        if (d->description)
            rt_kprintf(" (%s)\n", d->description);
        else
            rt_kprintf(" (No description available)\n");
    }
    if(i == 0)
    {
        rt_kprintf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return -RT_ERROR;
    }

    inum = 1;
    /* Jump to the selected adapter */
    for(d = alldevs, i = 0; i < inum-1 ;d = d->next, i++);

    {
        rt_kprintf("Select (%s) as network interface\n", d->description);
        packet_mb = rt_mb_create("pcap", 64, RT_IPC_FLAG_FIFO);
        tid = rt_thread_create("pcap", pcap_thread_entry, d,
            2048, RT_THREAD_PRIORITY_MAX - 1, 10);
        if (tid != RT_NULL)
        {
            rt_thread_startup(tid);
        }

        rt_thread_delay(100);
    }

    pcap_freealldevs(alldevs);

    return RT_EOK;
}

static rt_err_t pcap_netif_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t pcap_netif_close(rt_device_t dev)
{
    pcap_t *tap;

    tap = NETIF_PCAP(dev);

    pcap_close(tap);
    return RT_EOK;
}

static rt_ssize_t pcap_netif_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_ssize_t pcap_netif_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    rt_set_errno(-RT_ENOSYS);
    return 0;
}

static rt_err_t pcap_netif_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get mac address */
        if (args) rt_memcpy(args, pcap_netif_device.dev_addr, 6);
        else return -RT_ERROR;
        break;

    default :
        break;
    }

    return RT_EOK;
}

rt_err_t pcap_netif_tx( rt_device_t dev, struct pbuf* p)
{
    struct pbuf *q;
    rt_uint8_t *ptr;
    rt_uint8_t buf[2048];
    rt_err_t result = RT_EOK;
    pcap_t *tap;
    int res;

    tap = NETIF_PCAP(dev);

    /* lock EMAC device */
    rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

    /* check if the total length of pbuf exceeds the size of buf */
    if(p->tot_len > 2048)
    {
        LOG_E("Sending the packet: send data exceed max len 2048!");
        rt_sem_release(&sem_lock);
        return -RT_ERROR;
    }

    /* copy data to tx buffer */
    q = p;
    ptr = (rt_uint8_t*)buf;
    while (q)
    {
        memcpy(ptr, q->payload, q->len);
        ptr += q->len;
        q = q->next;
    }

    rt_enter_critical();
    res = pcap_sendpacket(tap, buf, p->tot_len);
    rt_exit_critical();

    if (res != 0)
    {
        LOG_E("Sending the packet: %s", pcap_geterr(tap));
        result = -RT_ERROR;
    }

    /* unlock EMAC device */
    rt_sem_release(&sem_lock);

    return result;
}

struct pbuf *pcap_netif_rx(rt_device_t dev)
{
    struct pbuf* p = RT_NULL;

    rt_mb_recv(packet_mb, (rt_uint32_t*)&p, 0);

    return p;
}

void pcap_netif_hw_init(void)
{
    rt_sem_init(&sem_lock, "eth_lock", 1, RT_IPC_FLAG_FIFO);

    pcap_netif_device.dev_addr[0] = 0x00;
    pcap_netif_device.dev_addr[1] = 0x60;
    pcap_netif_device.dev_addr[2] = 0x37;
    /* set mac address: (only for test) */
    pcap_netif_device.dev_addr[3] = 0x12;
    pcap_netif_device.dev_addr[4] = 0x34;
    pcap_netif_device.dev_addr[5] = 0x56;

    pcap_netif_device.parent.parent.init        = pcap_netif_init;
    pcap_netif_device.parent.parent.open        = pcap_netif_open;
    pcap_netif_device.parent.parent.close       = pcap_netif_close;
    pcap_netif_device.parent.parent.read        = pcap_netif_read;
    pcap_netif_device.parent.parent.write       = pcap_netif_write;
    pcap_netif_device.parent.parent.control     = pcap_netif_control;
    pcap_netif_device.parent.parent.user_data   = RT_NULL;

    pcap_netif_device.parent.eth_rx         = pcap_netif_rx;
    pcap_netif_device.parent.eth_tx         = pcap_netif_tx;

    eth_device_init(&(pcap_netif_device.parent), "e0");
}

#include <finsh.h>
void list_pcap(void)
{
    int i=0;
    pcap_if_t *alldevs;
    pcap_if_t *d;
    char errbuf[PCAP_ERRBUF_SIZE];

    /* Retrieve the device list */
    if(pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        rt_kprintf("Error in pcap_findalldevs: %s\n", errbuf);
        return -RT_ERROR;
    }

    /* Print the list */
    for(d = alldevs; d; d = d->next)
    {
        rt_kprintf("%d. %s", ++i, d->name);
        if (d->description)
            rt_kprintf(" (%s)\n", d->description);
        else
            rt_kprintf(" (No description available)\n");
    }
    if(i == 0)
    {
        rt_kprintf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return -RT_ERROR;
    }

    pcap_freealldevs(alldevs);

    return ;
}
FINSH_FUNCTION_EXPORT(list_pcap, show host netif adapter);
