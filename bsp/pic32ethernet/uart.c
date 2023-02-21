#include <GenericTypeDefs.h>
#include <plib.h>

#include <rtthread.h>

#include "uart.h"

#define	GetSystemClock() 			(80000000ul)
#define	GetPeripheralClock()		(GetSystemClock()/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()		(GetSystemClock())

struct rt_uart_pic32
{
    struct rt_device parent;

    int uart; /* UART Module ID. */

    /* buffer for reception */
    rt_uint8_t read_index, save_index;
    rt_uint8_t rx_buffer[RT_UART_RX_BUFFER_SIZE];
};

#ifdef RT_USING_UART1
static struct rt_uart_pic32 uart1_device;
#endif

#ifdef RT_USING_UART2
static struct rt_uart_pic32 uart2_device;
#endif

static rt_err_t rt_uart_init (rt_device_t dev)
{
    struct rt_uart_pic32 *uart_device = (struct rt_uart_pic32*)dev;

    UARTConfigure(uart_device->uart, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(uart_device->uart, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(uart_device->uart, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(uart_device->uart, GetPeripheralClock(), 115200);
    UARTEnable(uart_device->uart, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

    // Configure UART RX Interrupt
    INTEnable(INT_SOURCE_UART_RX(uart_device->uart), INT_ENABLED);
    INTSetVectorPriority(INT_VECTOR_UART(uart_device->uart), INT_PRIORITY_LEVEL_2);
    INTSetVectorSubPriority(INT_VECTOR_UART(uart_device->uart), INT_SUB_PRIORITY_LEVEL_0);

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
    rt_uint8_t* ptr;
    struct rt_uart_pic32 *uart_device = (struct rt_uart_pic32*)dev;
    RT_ASSERT(uart_device != RT_NULL);

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
            if (uart_device->read_index != uart_device->save_index)
            {
                *ptr = uart_device->rx_buffer[uart_device->read_index];

                uart_device->read_index ++;
                if (uart_device->read_index >= RT_UART_RX_BUFFER_SIZE)
                    uart_device->read_index = 0;
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

            ptr ++;
            size --;
        }

        return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
    }

    return 0;
}

static rt_ssize_t rt_uart_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    struct rt_uart_pic32 *uart_device = (struct rt_uart_pic32*)dev;
    char *ptr;
    ptr = (char*)buffer;

    if (dev->flag & RT_DEVICE_FLAG_STREAM)
    {
        /* stream mode */
        while (size)
        {
            if (*ptr == '\n')
            {
                while(!UARTTransmitterIsReady(uart_device->uart));
                UARTSendDataByte(uart_device->uart,'\r' );
                while(!UARTTransmissionHasCompleted(uart_device->uart));
            }
            while(!UARTTransmitterIsReady(uart_device->uart));
            UARTSendDataByte(uart_device->uart, *ptr);
            while(!UARTTransmissionHasCompleted(uart_device->uart));

            ptr ++;
            size --;
        }
    }
    else
    {
        while ( size != 0 )
        {
            while(!UARTTransmitterIsReady(uart_device->uart));
            UARTSendDataByte(uart_device->uart, *ptr);
            while(!UARTTransmissionHasCompleted(uart_device->uart));

            ptr++;
            size--;
        }
    }

    return (rt_size_t) ptr - (rt_size_t) buffer;
}


#ifdef RT_USING_UART1
// UART 1 interrupt handler
// it is set at priority level 2
void __ISR(_UART1_VECTOR, ipl2) IntUART1Handler(void)
{
    struct rt_uart_pic32 *uart_device = &uart1_device;

    // Is this an RX interrupt?
    if(INTGetFlag(INT_SOURCE_UART_RX(uart_device->uart)))
    {
        while( U1STAbits.URXDA )
        {
            /* Receive Data Available */
            uart_device->rx_buffer[uart_device->save_index] = UARTGetDataByte(uart_device->uart);//UARTGetDataByte(UART1);
            uart_device->save_index ++;
            if (uart_device->save_index >= RT_UART_RX_BUFFER_SIZE)
            {
                uart_device->save_index = 0;
            }
        }

        /* invoke callback */
        if(uart_device->parent.rx_indicate != RT_NULL)
        {
            rt_size_t length;
            if (uart_device->read_index > uart_device->save_index)
            {
                length = RT_UART_RX_BUFFER_SIZE - uart_device->read_index + uart_device->save_index;
            }
            else
            {
                length = uart_device->save_index - uart_device->read_index;
            }

            if( length )
            {
                uart_device->parent.rx_indicate(&uart_device->parent, length);
            }
        }

        // Clear the RX interrupt Flag
        INTClearFlag(INT_SOURCE_UART_RX(uart_device->uart));
    } // Is this an RX interrupt?

    // We don't care about TX interrupt
    if ( INTGetFlag(INT_SOURCE_UART_TX(uart_device->uart)) )
    {
        INTClearFlag(INT_SOURCE_UART_TX(uart_device->uart));
    }
}
#endif

#ifdef RT_USING_UART2
// UART 2 interrupt handler
// it is set at priority level 2
void __ISR(_UART2_VECTOR, ipl2) IntUART2Handler(void)
{
    struct rt_uart_pic32 *uart_device = &uart2_device;

    // Is this an RX interrupt?
    if(INTGetFlag(INT_SOURCE_UART_RX(uart_device->uart)))
    {
        while( U2STAbits.URXDA )
        {
            /* Receive Data Available */
            uart_device->rx_buffer[uart_device->save_index] = UARTGetDataByte(uart_device->uart);//UARTGetDataByte(UART1);
            uart_device->save_index ++;
            if (uart_device->save_index >= RT_UART_RX_BUFFER_SIZE)
            {
                uart_device->save_index = 0;
            }
        }

        /* invoke callback */
        if(uart_device->parent.rx_indicate != RT_NULL)
        {
            rt_size_t length;
            if (uart_device->read_index > uart_device->save_index)
            {
                length = RT_UART_RX_BUFFER_SIZE - uart_device->read_index + uart_device->save_index;
            }
            else
            {
                length = uart_device->save_index - uart_device->read_index;
            }

            if( length )
            {
                uart_device->parent.rx_indicate(&uart_device->parent, length);
            }
        }

        // Clear the RX interrupt Flag
        INTClearFlag(INT_SOURCE_UART_RX(uart_device->uart));
    } // Is this an RX interrupt?

    // We don't care about TX interrupt
    if ( INTGetFlag(INT_SOURCE_UART_TX(uart_device->uart)) )
    {
        INTClearFlag(INT_SOURCE_UART_TX(uart_device->uart));
    }
}
#endif

void rt_hw_usart_init(void)
{
    struct rt_uart_pic32 *uart_device;

#ifdef RT_USING_UART1
    /* device initialization */
    uart_device  = &uart1_device;
    rt_memset(uart_device,0,sizeof(struct rt_uart_pic32));
    uart_device->uart = UART1;
    uart_device->parent.type = RT_Device_Class_Char;

    /* device interface */
    uart_device->parent.init 	    = rt_uart_init;
    uart_device->parent.open 	    = rt_uart_open;
    uart_device->parent.close       = rt_uart_close;
    uart_device->parent.read 	    = rt_uart_read;
    uart_device->parent.write       = rt_uart_write;
    uart_device->parent.control     = RT_NULL;
    uart_device->parent.user_data   = RT_NULL;

    rt_device_register(&uart_device->parent,
                       "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_RX);
#endif

#ifdef RT_USING_UART2
    /* device initialization */
    uart_device  = &uart2_device;
    rt_memset(uart_device,0,sizeof(struct rt_uart_pic32));
    uart_device->uart = UART2;
    uart_device->parent.type = RT_Device_Class_Char;

    /* device interface */
    uart_device->parent.init 	    = rt_uart_init;
    uart_device->parent.open 	    = rt_uart_open;
    uart_device->parent.close       = rt_uart_close;
    uart_device->parent.read 	    = rt_uart_read;
    uart_device->parent.write       = rt_uart_write;
    uart_device->parent.control     = RT_NULL;
    uart_device->parent.user_data   = RT_NULL;

    rt_device_register(&uart_device->parent,
                       "uart2", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_INT_RX);
#endif
}
