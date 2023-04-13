#include <rthw.h>
#include <rtthread.h>


#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "system.h"
#include "sys/alt_irq.h"
#include "altera_avalon_uart_regs.h"

extern int alt_irq_register (alt_u32 id,
                             void*   context,
                             void (*alt_isr_func)(void* isr_context, alt_u32 id) );

static void set_baudrate(unsigned int baudrate)
{
    IOWR_ALTERA_AVALON_UART_DIVISOR(RS232_BASE,
                                    (unsigned int)(ALT_CPU_FREQ/baudrate+0.5) );
}

/********* rt-thread *********/
#include <rtthread.h>

struct rt_device   uart_device;
uint8_t     rx_buf[100];
uint32_t    rx_put_index;
uint32_t    rx_get_index;

static rt_err_t rt_uart_init (rt_device_t dev)
{
    set_baudrate(115200);

    IOWR_ALTERA_AVALON_UART_CONTROL(RS232_BASE, 0x80);//接收中断使能
    IOWR_ALTERA_AVALON_UART_STATUS(RS232_BASE, 0x0); // clean status

    rx_put_index = 0;
    rx_get_index = 0;

    return RT_EOK;
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_uart_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_uart_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    if( rx_get_index )
    {
        *(uint8_t *)buffer = rx_buf[0];
        rx_get_index--;
        return size;
    }
    return 0;
}

static rt_ssize_t rt_uart_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    const char * write_point = buffer;
    while(size--)
    {
        if(*write_point == '\n')
        {
            IOWR_ALTERA_AVALON_UART_TXDATA(RS232_BASE,'\r');
            while( !(IORD_ALTERA_AVALON_UART_STATUS(RS232_BASE)&(1<<6)) ); // status bit6 : TRDY
        }
        IOWR_ALTERA_AVALON_UART_TXDATA(RS232_BASE,*write_point);
        write_point++;
        while( !(IORD_ALTERA_AVALON_UART_STATUS(RS232_BASE)&(1<<6)) ); // status bit6 : TRDY
    }

    return size;
}

static rt_err_t rt_uart_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

static void uart_isr(void * context,alt_u32 id)
{
    rx_buf[rx_get_index] = IORD_ALTERA_AVALON_UART_RXDATA(RS232_BASE);
    rx_get_index++;
    if (uart_device.rx_indicate != RT_NULL)
    {
        uart_device.rx_indicate(&uart_device, 1);
    }
}

void rt_hw_uart_init(void)
{
    // init uart
    set_baudrate(115200);
    IOWR_ALTERA_AVALON_UART_CONTROL(RS232_BASE, 0x80);//接收中断使能
    IOWR_ALTERA_AVALON_UART_STATUS(RS232_BASE, 0x0); // clean status
    alt_irq_register(RS232_IRQ, NULL, uart_isr);

    // register device
    uart_device.type = RT_Device_Class_Char;
    /* device interface */
    uart_device.init        = rt_uart_init;
    uart_device.open        = rt_uart_open;
    uart_device.close       = rt_uart_close;
    uart_device.read        = rt_uart_read;
    uart_device.write       = rt_uart_write;
    uart_device.control     = rt_uart_control;

    uart_device.user_data   = RT_NULL;
    uart_device.rx_indicate = RT_NULL;
    uart_device.tx_complete = RT_NULL;

    rt_device_register(&uart_device,
                       "uart", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_RX);
}
