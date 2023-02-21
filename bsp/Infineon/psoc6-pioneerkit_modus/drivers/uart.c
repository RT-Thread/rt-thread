#include <rtthread.h>
#include "uart.h"
#include "cycfg_peripherals.h"
/**
 * @addtogroup
 */
/*@{*/

/* RT-Thread Device Interface */
/**
 * This function initializes uart
 */
static rt_err_t rt_uart_init (rt_device_t dev)
{
    struct uart_device* uart = (struct uart_device*) dev->user_data;

    if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
    {
        if (dev->flag & RT_DEVICE_FLAG_INT_RX)
        {
            rt_memset(uart->int_rx->rx_buffer, 0,
                      sizeof(uart->int_rx->rx_buffer));
            uart->int_rx->read_index = uart->int_rx->save_index = 0;
        }

        if (dev->flag & RT_DEVICE_FLAG_INT_TX)
        {
            rt_memset(uart->int_tx->tx_buffer, 0,
                      sizeof(uart->int_tx->tx_buffer));
            uart->int_tx->write_index = uart->int_tx->save_index = 0;
        }

        dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
    }

    return RT_EOK;
}

/* save a char to uart buffer */
static void rt_uart_savechar(struct uart_device* uart, char ch)
{
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    uart->int_rx->rx_buffer[uart->int_rx->save_index] = ch;
    uart->int_rx->save_index ++;
    if (uart->int_rx->save_index >= UART_RX_BUFFER_SIZE)
        uart->int_rx->save_index = 0;

    /* if the next position is read index, discard this 'read char' */
    if (uart->int_rx->save_index == uart->int_rx->read_index)
    {
        uart->int_rx->read_index ++;
        if (uart->int_rx->read_index >= UART_RX_BUFFER_SIZE)
            uart->int_rx->read_index = 0;
    }

    /* enable interrupt */
    rt_hw_interrupt_enable(level);
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct uart_device* uart;
    oflag = oflag;

    RT_ASSERT(dev != RT_NULL);
    uart = (struct uart_device*) dev->user_data;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* enable interrupt */
        UART_ENABLE_IRQ(uart->rx_irq);
    }

    return RT_EOK;
}

static rt_err_t rt_uart_close(rt_device_t dev)
{
    struct uart_device* uart;

    RT_ASSERT(dev != RT_NULL);
    uart = (struct uart_device*) dev->user_data;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* disable interrupt */
        UART_DISABLE_IRQ(uart->rx_irq);
    }

    return RT_EOK;
}

static rt_ssize_t rt_uart_read (rt_device_t dev, rt_off_t pos, void* buffer,
                                 rt_size_t size)
{
    rt_uint8_t* ptr;
    rt_err_t err_code;
    struct uart_device* uart;
    pos = pos;

    ptr = buffer;
    err_code = RT_EOK;
    uart = (struct uart_device*)dev->user_data;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        rt_base_t level;

        /* interrupt mode Rx */
        while (size)
        {
            if (uart->int_rx->read_index != uart->int_rx->save_index)
            {
                *ptr++ = uart->int_rx->rx_buffer[uart->int_rx->read_index];
                size --;

                /* disable interrupt */
                level = rt_hw_interrupt_disable();

                uart->int_rx->read_index ++;
                if (uart->int_rx->read_index >= UART_RX_BUFFER_SIZE)
                    uart->int_rx->read_index = 0;

                /* enable interrupt */
                rt_hw_interrupt_enable(level);
            }
            else
            {
                /* set error code */
                err_code = -RT_EEMPTY;
                break;
            }
        }
    }
    else
    {
        /* polling mode */
        while ((rt_uint32_t)ptr - (rt_uint32_t)buffer < size)
        {
            while (0UL != Cy_SCB_UART_GetNumInRxFifo(uart->scb_device))
            {
                *ptr = Cy_SCB_UART_Get(uart->scb_device);
                ptr ++;
            }
        }
    }

    /* set error code */
    rt_set_errno(err_code);
    return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_ssize_t rt_uart_write (rt_device_t dev, rt_off_t pos,
                                const void* buffer, rt_size_t size)
{
    rt_uint8_t* ptr;
    rt_err_t err_code;
    struct uart_device* uart;
    pos = pos;

    err_code = RT_EOK;
    ptr = (rt_uint8_t*)buffer;
    uart = (struct uart_device*)dev->user_data;

    if (dev->flag & RT_DEVICE_FLAG_INT_TX)
    {
        /* interrupt mode Tx */
        while (uart->int_tx->save_index != uart->int_tx->write_index)
        {
            /* save on tx buffer */
            uart->int_tx->tx_buffer[uart->int_tx->save_index] = *ptr++;

            -- size;

            /* move to next position */
            uart->int_tx->save_index ++;

            /* wrap save index */
            if (uart->int_tx->save_index >= UART_TX_BUFFER_SIZE)
                uart->int_tx->save_index = 0;
        }

        /* set error code */
        if (size > 0)
            err_code = -RT_EFULL;
    }
    else
    {
        /* polling mode */
        while (size)
        {
            /*
             * to be polite with serial console add a line feed
             * to the carriage return character
             */
            if (*ptr == '\n' && (dev->flag & RT_DEVICE_FLAG_STREAM))
            {
                while(0 == Cy_SCB_UART_Put(uart->scb_device, '\r'));
            }
            while(0 == Cy_SCB_UART_Put(uart->scb_device, (*ptr & 0x1FF)));

            ++ptr;
            --size;
        }
    }

    /* set error code */
    rt_set_errno(err_code);

    return (rt_uint32_t)ptr - (rt_uint32_t)buffer;
}

static rt_err_t rt_uart_control (rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);
    args = args;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SUSPEND:
        /* suspend device */
        dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
        break;

    case RT_DEVICE_CTRL_RESUME:
        /* resume device */
        dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
        break;
    }

    return RT_EOK;
}

/*
 * serial register
 */
rt_err_t rt_hw_uart_register(rt_device_t device, const char* name,
                             rt_uint32_t flag, struct uart_device *serial)
{
    RT_ASSERT(device != RT_NULL);

    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->init        = rt_uart_init;
    device->open        = rt_uart_open;
    device->close       = rt_uart_close;
    device->read        = rt_uart_read;
    device->write       = rt_uart_write;
    device->control     = rt_uart_control;
    device->user_data   = serial;

    /* register a character device */
    return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}

/* ISR for uart interrupt */
void rt_hw_uart_isr(rt_device_t device)
{
    struct uart_device* uart = (struct uart_device*) device->user_data;

    /* interrupt mode receive */
    RT_ASSERT(device->flag & RT_DEVICE_FLAG_INT_RX);

    /* Check for "RX fifo not empty interrupt" */
    if((uart->scb_device->INTR_RX_MASKED & SCB_INTR_RX_MASKED_NOT_EMPTY_Msk ) != 0)
    {
        /* Clear UART "RX fifo not empty interrupt" */
        uart->scb_device->INTR_RX = uart->scb_device->INTR_RX & SCB_INTR_RX_NOT_EMPTY_Msk;
        /* Get the character from terminal */
        rt_uart_savechar(uart, Cy_SCB_UART_Get(uart->scb_device));
    }

    /* invoke callback */
    if (device->rx_indicate != RT_NULL)
    {
        rt_size_t rx_length;

        /* get rx length */
        rx_length = uart->int_rx->read_index > uart->int_rx->save_index ?
                    UART_RX_BUFFER_SIZE - uart->int_rx->read_index + uart->int_rx->save_index :
                    uart->int_rx->save_index - uart->int_rx->read_index;

        device->rx_indicate(device, rx_length);
    }
}

#ifdef RT_USING_UART0
/* UART0 device driver structure */
#define UART0_SCB_IRQ__INTC_NUMBER 46u
cy_stc_scb_uart_context_t UART0_context;
const cy_stc_sysint_t UART0_SCB_IRQ_cfg =
{
    .intrSrc = scb_5_interrupt_IRQn,
    .intrPriority = 3u,
};

/* UART0 device driver structure */
struct uart_int_rx uart0_int_rx;
struct uart_device uart0 =
{
    UART0_HW,
    &UART0_config,
    &UART0_context,
    &UART0_SCB_IRQ_cfg,
    (IRQn_Type)UART0_SCB_IRQ__INTC_NUMBER,
    (IRQn_Type)UART0_SCB_IRQ__INTC_NUMBER,
    &uart0_int_rx,
    RT_NULL
};
struct rt_device uart0_device;
/* UART0 Interrupt Hanlder */
void uart0_isr_callback(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_uart_isr(&uart0_device);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif


void rt_hw_uart_init(void)
{
    /* Start UART operation. */
    if(Cy_SCB_UART_Init(uart0.scb_device, uart0.uart_config, uart0.uart_context) != CY_SCB_UART_SUCCESS)
    {
        rt_assert_handler("UART0 init", __FUNCTION__, __LINE__);
    }
    Cy_SCB_UART_Enable(uart0.scb_device);
    /* Unmasking only the RX fifo not empty interrupt bit */
    uart0.scb_device->INTR_RX_MASK = SCB_INTR_RX_MASK_NOT_EMPTY_Msk;
    /* Interrupt Settings for UART */
    Cy_SysInt_Init(uart0.uart_int, uart0_isr_callback);
    /* Enable the interrupt */
    NVIC_EnableIRQ(uart0.uart_int->intrSrc);
    /* register UART0 device */
    rt_hw_uart_register(&uart0_device,
                          "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          &uart0);

}

/*@}*/
