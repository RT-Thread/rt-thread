/*
 *  TAP-ASNET -- A kernel driver to provide virtual tap device functionality
 *               on PCIE on qemu
 *  Author: parai@foxmail.com
 *  Date: 2017-10-25
 */
#ifdef USE_PCI
#include <pci_core.h>
#include <rtthread.h>
#include <netif/ethernetif.h>
#include <lwip/inet.h>

#define MAX_ADDR_LEN 6

#define IFNAME0 't'
#define IFNAME1 'p'

enum {
	FLG_RX = 0x01,
	FLG_TX = 0x02,
};

enum{
	REG_MACL      = 0x00,
	REG_MACH      = 0x04,
	REG_MTU       = 0x08,
	REG_DATA      = 0x0C,
	REG_LENGTH    = 0x10,
	REG_NETSTATUS = 0x14,
	REG_GW        = 0x18,
	REG_NETMASK   = 0x1C,
	REG_CMD       = 0x20,
};

static pci_dev *pdev = NULL;
static void* __iobase= NULL;
static char pkbuf[1514];
/************************************************************************/
/* RT-Thread Network Interface                                          */
/************************************************************************/
struct tap_netif
{
	/* inherit from ethernet device */
	struct eth_device parent;

	/* interface address info. */
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];		/* hw address	*/
};

static struct tap_netif tap_netif_device;
static struct rt_semaphore sem_lock;

static void tap_asnet_thread_entry(void* param)
{
	struct eth_device* eth;
	uint32 flag;
	eth = (struct eth_device*) &tap_netif_device;

	rt_kprintf("tap eth server on-line\n");

	for(;;)
	{
		if (RT_NULL == __iobase) {
			rt_kprintf("tap eth server exit\n");
			rt_thread_exit();
		}

		flag = readl(__iobase+REG_NETSTATUS);
		if(flag&FLG_RX)
		{
			/* notify eth rx thread to receive packet */
			eth_device_ready(eth);
		}

		rt_thread_delay(1);
	}
}

static void Eth_Isr(void)
{
	/* empty as not supported by asnet */
}

static rt_err_t tap_netif_init(rt_device_t dev)
{
	rt_thread_t tid;
	uint32 val;
	uint32 mtu;
	pdev = find_pci_dev_from_id(0xcaac,0x0002);
	if(RT_NULL == pdev)
	{
		rt_kprintf("tap: Could not open 'asnet'\n");
		return -RT_ERROR;
	}
	
	__iobase = (void*)(pdev->mem_addr[1]);
	enable_pci_resource(pdev);
#ifdef __X86__
	pci_register_irq(pdev->irq_num,Eth_Isr);
#else
	pci_bus_write_config_byte(pdev,0x3c,0x44);
	pci_register_irq(32+31,Eth_Isr);
#endif
	enable_pci_interrupt(pdev);

	writel(__iobase+REG_GW, inet_addr("192.168.1.30"));
	writel(__iobase+REG_NETMASK, inet_addr("255.255.255.0"));
	writel(__iobase+REG_CMD, 0);

	mtu = readl(__iobase+REG_MTU);
	val = readl(__iobase+REG_MACL);
	tap_netif_device.dev_addr[0] = (val>>0)&0xFF;
	tap_netif_device.dev_addr[1] = (val>>8)&0xFF;
	tap_netif_device.dev_addr[2] = (val>>16)&0xFF;
	tap_netif_device.dev_addr[3] = (val>>24)&0xFF;
	val = readl(__iobase+REG_MACH);
	tap_netif_device.dev_addr[4] = (val>>0)&0xFF;
	tap_netif_device.dev_addr[5] = (val>>8)&0xFF;

	/* create recv thread */
	tid = rt_thread_create("tap", tap_asnet_thread_entry, RT_NULL, 
		2048, RT_THREAD_PRIORITY_MAX - 1, 10);
	if (tid != RT_NULL)
	{
		rt_thread_startup(tid);
	}

	rt_kprintf("hwaddr is %02X:%02X:%02X:%02X:%02X:%02X, mtu=%d\n",
		tap_netif_device.dev_addr[0],tap_netif_device.dev_addr[1],
		tap_netif_device.dev_addr[2],tap_netif_device.dev_addr[3],
		tap_netif_device.dev_addr[4],tap_netif_device.dev_addr[4],
		mtu);
	return RT_EOK;
}

static rt_err_t tap_netif_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t tap_netif_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t tap_netif_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_size_t tap_netif_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_err_t tap_netif_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	switch (cmd)
	{
	case NIOCTL_GADDR:
		/* get mac address */
		if (args) rt_memcpy(args, tap_netif_device.dev_addr, 6);
		else return -RT_ERROR;
		break;

	default :
		break;
	}

	return RT_EOK;
}

rt_err_t tap_netif_tx( rt_device_t dev, struct pbuf* p)
{
	struct pbuf *q;
	static char buffer[2048];
	int length;
	int pos = 0;
	unsigned char* ptr;

	/* lock EMAC device */
	rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

	/* copy data to tx buffer */
	q = p;
	ptr = (rt_uint8_t*)buffer;
	while (q)
	{
		memcpy(ptr, q->payload, q->len);
		ptr += q->len;
		q = q->next;
	}
	length = p->tot_len;

	/* signal that packet should be sent(); */
	writel(__iobase+REG_LENGTH,p->tot_len);
	while(length > 0)
	{
		writel(__iobase+REG_DATA,*((uint8*)&buffer[pos]));
		pos += 1;
		length -= 1;
	}
	writel(__iobase+REG_CMD, 1);

	/* unlock EMAC device */
	rt_sem_release(&sem_lock);

	return RT_EOK;
}

struct pbuf *tap_netif_rx(rt_device_t dev)
{
	struct pbuf* p = RT_NULL;
	int size;
	u16_t len,pos;

	if(RT_NULL == __iobase) return RT_NULL;

	size = len = readl(__iobase+REG_LENGTH);
	if(size > 0)
	{
		pos = 0;
		while(len > 0)
		{
			pkbuf[pos] = readl(__iobase+REG_DATA);
			pos ++;
			len --;
		}
	}

	if (size > 0) {
		p = pbuf_alloc(PBUF_LINK, size, PBUF_RAM);
		pbuf_take(p, pkbuf, size);
	}

	return p;
}

void tap_netif_hw_init(void)
{
	rt_sem_init(&sem_lock, "eth_lock", 1, RT_IPC_FLAG_FIFO);

	tap_netif_device.dev_addr[0] = 0x00;
	tap_netif_device.dev_addr[1] = 0x60;
	tap_netif_device.dev_addr[2] = 0x37;
	/* set mac address: (only for test) */
	tap_netif_device.dev_addr[3] = 0x12;
	tap_netif_device.dev_addr[4] = 0x34;
	tap_netif_device.dev_addr[5] = 0x56;

	tap_netif_device.parent.parent.init		= tap_netif_init;
	tap_netif_device.parent.parent.open		= tap_netif_open;
	tap_netif_device.parent.parent.close	= tap_netif_close;
	tap_netif_device.parent.parent.read		= tap_netif_read;
	tap_netif_device.parent.parent.write	= tap_netif_write;
	tap_netif_device.parent.parent.control	= tap_netif_control;
	tap_netif_device.parent.parent.user_data= RT_NULL;

	tap_netif_device.parent.eth_rx			= tap_netif_rx;
	tap_netif_device.parent.eth_tx			= tap_netif_tx;

	eth_device_init(&(tap_netif_device.parent), "e0");
}
#endif /* USE_PCI */
