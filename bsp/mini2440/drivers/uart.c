/*
 * File      : uart.c
 * Drivers for s3c2440 uarts.
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-09     Jonne        Code refactoring for new bsp
 */

#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#define ULCON_OFS				0x00
#define UCON_OFS				0x04
#define UFCON_OFS				0x08
#define UMCON_OFS				0x0c
#define UTRSTAT_OFS				0x10
#define UERSTAT_OFS				0x14
#define UFSTAT_OFS				0x18
#define UMSTAT_OFS				0x1c
#define UTXH_OFS				0x20
#define URXH_OFS				0x24
#define UBRDIV_OFS				0x28

#define readl(addr)             (*(volatile unsigned long *)(addr))
#define writel(addr, value)     (*(volatile unsigned long *)(addr) = value)  

#define PCLK_HZ                 50000000

struct hw_uart_device
{
    rt_uint32_t hw_base;
    rt_uint32_t irqno;
};

static rt_err_t s3c2440_serial_configure(struct rt_serial_device *serial, struct serial_configure *cfg) 
{
    struct hw_uart_device* uart = serial->parent.user_data;

    writel(uart->hw_base + UBRDIV_OFS, PCLK_HZ / (cfg->baud_rate * 16));

    writel(uart->hw_base + ULCON_OFS, 0x03);// 8bit data, 1bit stop, No parity
    writel(uart->hw_base + UCON_OFS, 0x05);
    writel(uart->hw_base + UFCON_OFS, 0x00);
    writel(uart->hw_base + UMCON_OFS, 0x00);

	return RT_EOK;
}

static rt_err_t s3c2440_serial_control(struct rt_serial_device *serial, int cmd, void *arg)
{
	struct hw_uart_device *uart;
    int mask;

    RT_ASSERT(serial != RT_NULL); 
    uart = (struct hw_uart_device *)serial->parent.user_data;

    if(uart->irqno == INTUART0)
    {
        mask = BIT_SUB_RXD0;
    }
    else if(uart->irqno == INTUART1)
    {
        mask = BIT_SUB_RXD1;
    }
    else
    {
        mask = BIT_SUB_RXD2;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        INTSUBMSK |= mask;
		
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        INTSUBMSK &= ~mask;
        break;
    }

    return RT_EOK;
}
static int s3c2440_putc(struct rt_serial_device *serial, char c)
{
    struct hw_uart_device* uart = serial->parent.user_data;

    while(!(readl(uart->hw_base + UTRSTAT_OFS) & (1<<2))) 
    {
    }

    writel(uart->hw_base + UTXH_OFS, c);
    
    return 0;

     
}
static int s3c2440_getc(struct rt_serial_device *serial)
{
    struct hw_uart_device* uart = serial->parent.user_data;
    int ch = -1;

    if(readl(uart->hw_base + UTRSTAT_OFS) & (1<<0)) 
    {
        ch = readl(uart->hw_base + URXH_OFS) & 0x000000FF;
    }
    
    return ch;
}

static void rt_hw_uart_isr(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    
    /*clear SUBSRCPND*/ 
    if(irqno == INTUART0) 
    {
        SUBSRCPND = BIT_SUB_RXD0;
    } 
    else if(irqno == INTUART1) 
    {
        SUBSRCPND = BIT_SUB_RXD1;
    }
    else 
    {
        SUBSRCPND = BIT_SUB_RXD2;
    }
}

static struct rt_uart_ops s3c2440_uart_ops = {
		.configure = s3c2440_serial_configure,
		.control = s3c2440_serial_control,
		.putc = s3c2440_putc,
		.getc = s3c2440_getc
};


static struct rt_serial_device _serial0 = {
	.ops = &s3c2440_uart_ops,
	.config = RT_SERIAL_CONFIG_DEFAULT,
	.serial_rx = NULL,
	.serial_tx = NULL
};
static struct hw_uart_device _hwserial0 = {
	.hw_base = 0x50000000,
	.irqno = INTUART0
};

static struct rt_serial_device _serial1 = {
	.ops = &s3c2440_uart_ops,
	.config = RT_SERIAL_CONFIG_DEFAULT,
	.serial_rx = NULL,
	.serial_tx = NULL
};
static struct hw_uart_device _hwserial1 = {
	.hw_base = 0x50004000,
	.irqno = INTUART1
};

static struct rt_serial_device _serial2 = {
	.ops = &s3c2440_uart_ops,
	.config = RT_SERIAL_CONFIG_DEFAULT,
	.serial_rx = NULL,
	.serial_tx = NULL
};
static struct hw_uart_device _hwserial2 = {
	.hw_base = 0x50008000,
	.irqno = INTUART2
};


int rt_hw_uart_init(void)
{
    /* UART0  UART1 UART2 port configure */
    GPHCON |= 0xAAAA;
    /* PULLUP is disable */
    GPHUP |= 0xFFF;

    /* register UART0 device */
    rt_hw_serial_register(&_serial0, "uart0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, &_hwserial0);
    rt_hw_interrupt_install(_hwserial0.irqno, rt_hw_uart_isr, &_serial0, "uart0");
    rt_hw_interrupt_umask(INTUART0);
	
    /* register UART1 device */
    rt_hw_serial_register(&_serial1, "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, &_hwserial1);
    rt_hw_interrupt_install(_hwserial1.irqno, rt_hw_uart_isr, &_serial1, "uart1");
    rt_hw_interrupt_umask(INTUART1);

    /* register UART2 device */
    rt_hw_serial_register(&_serial2, "uart2", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, &_hwserial2);
    rt_hw_interrupt_install(_hwserial2.irqno, rt_hw_uart_isr, &_serial2, "uart2");
    rt_hw_interrupt_umask(INTUART2);

    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_uart_init);
