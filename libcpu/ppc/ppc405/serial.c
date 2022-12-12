#include <rthw.h>
#include <rtthread.h>

#include "io.h"
#include <asm/ppc4xx-intvec.h>

#define UART0_BASE      0xef600300
#define UART1_BASE      0xef600400
#define UCR0_MASK       0x0000007f
#define UCR1_MASK       0x00007f00
#define UCR0_UDIV_POS   0
#define UCR1_UDIV_POS   8
#define UDIV_MAX        127

#define UART_RBR        0x00
#define UART_THR        0x00
#define UART_IER        0x01
#define UART_IIR        0x02
#define UART_FCR        0x02
#define UART_LCR        0x03
#define UART_MCR        0x04
#define UART_LSR        0x05
#define UART_MSR        0x06
#define UART_SCR        0x07
#define UART_DLL        0x00
#define UART_DLM        0x01

/*-----------------------------------------------------------------------------+
  | Line Status Register.
  +-----------------------------------------------------------------------------*/
#define asyncLSRDataReady1            0x01
#define asyncLSROverrunError1         0x02
#define asyncLSRParityError1          0x04
#define asyncLSRFramingError1         0x08
#define asyncLSRBreakInterrupt1       0x10
#define asyncLSRTxHoldEmpty1          0x20
#define asyncLSRTxShiftEmpty1         0x40
#define asyncLSRRxFifoError1          0x80

/* PPC405 serial device */
struct rt_ppc405_serial
{
    /* inherit from device */
    struct rt_device parent;

    rt_uint32_t hw_base;
    rt_uint32_t irqno;
    rt_uint32_t baudrate;

    /* reception field */
    rt_uint16_t save_index, read_index;
    rt_uint8_t  rx_buffer[RT_UART_RX_BUFFER_SIZE];
};
struct rt_ppc405_serial ppc405_serial;

/* serial character device */
static rt_err_t rt_serial_init (rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_serial_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct rt_ppc405_serial* device;
    device = (struct rt_ppc405_serial*) dev;

    RT_ASSERT(device != RT_NULL);
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Enable "RX Data Available" Interrupt on UART */
        out_8((rt_uint8_t*)device->hw_base + UART_IER, 0x01);
        /* Setup UART FIFO: RX trigger level: 1 byte, Enable FIFO */
        out_8((rt_uint8_t*)device->hw_base + UART_FCR, 1);

        /* init UART rx interrupt */
        rt_hw_interrupt_unmask(device->irqno);
    }

    return RT_EOK;
}

static rt_err_t rt_serial_close(rt_device_t dev)
{
    struct rt_ppc405_serial* device;
    device = (struct rt_ppc405_serial*) dev;

    RT_ASSERT(device != RT_NULL);
    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* mask UART rx interrupt */
        rt_hw_interrupt_mask(device->irqno);
    }

    return RT_EOK;
}

static rt_err_t rt_serial_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

static rt_size_t rt_serial_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    rt_uint8_t* ptr;
    struct rt_ppc405_serial* device;

    device = (struct rt_ppc405_serial*) dev;
    RT_ASSERT(device != RT_NULL);

    /* point to buffer */
    ptr = (rt_uint8_t*) buffer;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        while (size)
        {
            /* interrupt receive */
            rt_base_t level;

            /* disable interrupt */
            level = rt_hw_interrupt_disable();
            if (device->read_index != device->save_index)
            {
                *ptr = device->rx_buffer[device->read_index];

                device->read_index ++;
                if (device->read_index >= RT_UART_RX_BUFFER_SIZE)
                    device->read_index = 0;
            }
            else
            {
                /* no data in rx buffer */

                /* enable interrupt */
                rt_hw_interrupt_enable(level);
                break;
            }

            /* enable interrupt */
            rt_hw_interrupt_enable(level);

            ptr ++; size --;
        }

        return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
    }
    else if (dev->flag & RT_DEVICE_FLAG_DMA_RX)
    {
        /* not support right now */
        RT_ASSERT(0);
    }

    /* polling mode */
    RT_ASSERT(0);

    return (rt_size_t)ptr - (rt_size_t)buffer;
}

static rt_size_t rt_serial_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    char *ptr;
    struct rt_ppc405_serial* device;

    device = (struct rt_ppc405_serial*) dev;
    RT_ASSERT(device != RT_NULL);

    if (dev->flag & RT_DEVICE_FLAG_INT_TX)
    {
        /* not support */
        RT_ASSERT(0);
    }
    else if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
    {
        /* not support */
        RT_ASSERT(0);
    }

    /* polling write */
    ptr = (char *)buffer;

    if (dev->flag & RT_DEVICE_FLAG_STREAM)
    {
        /* stream mode */
        while (size)
        {
            if (*ptr == '\n')
            {
                while ((in_8((rt_uint8_t*)device->hw_base + UART_LSR) & 0x20) != 0x20);
                out_8((rt_uint8_t*)device->hw_base + UART_THR, '\r');
            }

            while ((in_8((rt_uint8_t*)device->hw_base + UART_LSR) & 0x20) != 0x20);
            out_8((rt_uint8_t*)device->hw_base + UART_THR, *ptr);

            ptr ++;
            size --;
        }
    }
    else
    {
        while (size)
        {
            while ((in_8((rt_uint8_t*)device->hw_base + UART_LSR) & 0x20) != 0x20);
            out_8((rt_uint8_t*)device->hw_base + UART_THR, *ptr);

            ptr ++;
            size --;
        }
    }

    return (rt_size_t) ptr - (rt_size_t) buffer;
}

void rt_serial_set_baudrate(struct rt_ppc405_serial* device)
{
    rt_uint32_t bdiv;

    bdiv = 115200;
    out_8((rt_uint8_t *)device->hw_base + UART_DLL, bdiv);      /* set baudrate divisor */
    out_8((rt_uint8_t *)device->hw_base + UART_DLM, bdiv >> 8); /* set baudrate divisor */
}

void rt_serial_isr(int irqno, void* param)
{
    unsigned char status;
    struct rt_ppc405_serial *device;

    device = (struct rt_ppc405_serial*) param;
    status = in_8((rt_uint8_t *)device->hw_base + UART_LSR);

    if (status & 0x01)
    {
        rt_base_t level;

        while (status & 0x01)
        {
            /* disable interrupt */
            level = rt_hw_interrupt_disable();

            /* read character */
            device->rx_buffer[device->save_index] = (0xff & (int) in_8((rt_uint8_t *)device->hw_base));
            device->save_index ++;
            if (device->save_index >= RT_UART_RX_BUFFER_SIZE)
                device->save_index = 0;

            /* if the next position is read index, discard this 'read char' */
            if (device->save_index == device->read_index)
            {
                device->read_index ++;
                if (device->read_index >= RT_UART_RX_BUFFER_SIZE)
                    device->read_index = 0;
            }

            /* enable interrupt */
            rt_hw_interrupt_enable(level);

            /* check error */
            if ((status & ( asyncLSRFramingError1 |
                    asyncLSROverrunError1 |
                    asyncLSRParityError1  |
                    asyncLSRBreakInterrupt1 )) != 0)
            {
                out_8((rt_uint8_t *)device->hw_base + UART_LSR,
                      asyncLSRFramingError1 |
                      asyncLSROverrunError1 |
                      asyncLSRParityError1  |
                      asyncLSRBreakInterrupt1);
            }

            status = in_8((rt_uint8_t *)device->hw_base + UART_LSR);
        }

        /* invoke callback */
        if(device->parent.rx_indicate != RT_NULL)
        {
          device->parent.rx_indicate(&device->parent, 1);
        }
    }
}

void rt_hw_serial_init(void)
{
    volatile rt_uint8_t val;
    struct rt_ppc405_serial* device;

    device = (struct rt_ppc405_serial*) &ppc405_serial;
    device->parent.type = RT_Device_Class_Char;

    device->hw_base = UART0_BASE;
    device->baudrate = 115200;
    device->irqno = VECNUM_U0;
    rt_hw_interrupt_install(device->irqno, rt_serial_isr, device, "serial"); /* install isr */

    rt_memset(device->rx_buffer, 0, sizeof(device->rx_buffer));
    device->read_index = device->save_index = 0;

    out_8((rt_uint8_t *)device->hw_base + UART_LCR, 0x80);  /* set DLAB bit */
    /* setup baudrate */
    rt_serial_set_baudrate(device);
    out_8((rt_uint8_t *)device->hw_base + UART_LCR, 0x03);  /* clear DLAB; set 8 bits, no parity */
    out_8((rt_uint8_t *)device->hw_base + UART_FCR, 0x00);  /* disable FIFO */
    out_8((rt_uint8_t *)device->hw_base + UART_MCR, 0x00);  /* no modem control DTR RTS */
    val = in_8((rt_uint8_t *)device->hw_base + UART_LSR);   /* clear line status */
    val = in_8((rt_uint8_t *)device->hw_base + UART_RBR);   /* read receive buffer */
    out_8((rt_uint8_t *)device->hw_base + UART_SCR, 0x00);  /* set scratchpad */
    out_8((rt_uint8_t *)device->hw_base + UART_IER, 0x00);  /* set interrupt enable reg */

    device->parent.type     = RT_Device_Class_Char;
    device->parent.init     = rt_serial_init;
    device->parent.open     = rt_serial_open;
    device->parent.close    = rt_serial_close;
    device->parent.read     = rt_serial_read;
    device->parent.write    = rt_serial_write;
    device->parent.control  = rt_serial_control;
    device->parent.user_data  = RT_NULL;

    rt_device_register(&device->parent,
        "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM);
}
