
#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "hw_ints.h"
#include "sysctl.h"
#include "gpio.h"
#include "pin_map.h"
#include "interrupt.h"
#include "rom_map.h"
#include "uart.h"

#include "drv_uart.h"
#include "uart_config.h"
#include "tm4c123_config.h"

#ifdef RT_USING_SERIAL

#define   LOG_TAG  "drv.uart"
#include <drv_log.h>

#if !defined(BSP_USING_UART0)&&!defined(BSP_USING_UART1)&&!defined(BSP_USING_UART2)&&!defined(BSP_USING_UART3)
    #error "Please define at least one BSP_USING_UARTx"
#endif

enum {
	
#ifdef BSP_USING_UART0
	UART0_INDEX,
#endif
	
#ifdef BSP_USING_UART1
	UART1_INDEX,
#endif

#ifdef BSP_USING_UART2
	UART2_INDEX,
#endif
	
#ifdef BSP_USING_UART3
	UART3_INDEX,
#endif	
};

uint32_t  uart_intbase[]=
{
#ifdef BSP_USING_UART0
	  INT_UART0,
#endif
	
#ifdef BSP_USING_UART1
	  INT_UART1,
#endif

#ifdef BSP_USING_UART2
	  INT_UART2,
#endif
	
#ifdef BSP_USING_UART3
	  INT_UART3
#endif		 
};

static struct tm4c123_uart_config uart_config[] =
{
#ifdef BSP_USING_UART0
    UART0_CONFIG,
#endif
	
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif

#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif
	
#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif	
};

static struct tm4c123_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};


//struct serial_configure
//{
//    rt_uint32_t baud_rate;            /* ??? */
//    rt_uint32_t data_bits    :4;      /* ??? */
//    rt_uint32_t stop_bits    :2;      /* ??? */
//    rt_uint32_t parity       :2;      /* ????? */
//    rt_uint32_t bit_order    :1;      /* ?????????? */
//    rt_uint32_t invert       :1;      /* ?? */
//    rt_uint32_t bufsz        :16;     /* ????????? */
//    rt_uint32_t reserved     :4;      /* ??? */
//};

//rtservice.h
//#define  rt_container_of(ptr, type, member)   ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

static rt_err_t tm4c123_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct tm4c123_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct tm4c123_uart, serial);
	  
	
	  UARTFIFOLevelSet(uart->config->uartbase, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
		
    UARTConfigSetExpClk(uart->config->uartbase, SysCtlClockGet(), uart->config->baudrate,
                            uart->config->mode);	
		
    return RT_EOK;
}


static rt_err_t  tm4c123_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct tm4c123_uart  *uart;
#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct tm4c123_uart, serial);
	
    switch (cmd)
    {
        /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        IntDisable(uart->uartintbase);
        /* disable interrupt */
        //UARTIntDisable(UART0_BASE, UART_INT_RX | UART_INT_RT);
		    UARTIntDisable(uart->config->uartbase, UART_INT_RX);
        break;
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        IntEnable(uart->uartintbase);
        //UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
	    	UARTIntEnable(uart->config->uartbase, UART_INT_RX);
        break;

#ifdef RT_SERIAL_USING_DMA
    case RT_DEVICE_CTRL_CONFIG:
        break;
#endif
    }
    return RT_EOK;
}

static int tm4c123_putc(struct rt_serial_device *serial, char c)
{
    struct tm4c123_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct tm4c123_uart, serial);
	
	  UARTCharPut(uart->config->uartbase, c);	
    return 1;
}

static int tm4c123_getc(struct rt_serial_device *serial)
{
    int ch;
    struct tm4c123_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct tm4c123_uart, serial);
    ch = -1;
    ch = UARTCharGetNonBlocking(uart->config->uartbase);
    return ch;
}

static rt_size_t tm4c123_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    struct tm4c123_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct tm4c123_uart, serial);
    
    if (size == 0)
    {
        return 0;
    }
    
//    if (RT_SERIAL_DMA_TX == direction)
//    {
//        if (HAL_UART_Transmit_DMA(&uart->handle, buf, size) == HAL_OK)
//        {
//            return size;
//        }
//        else
//        {
//            return 0;
//        }
//    }
		
    return 0;
}

static const struct rt_uart_ops tm4c123_uart_ops =
{
    .configure = tm4c123_configure,
    .control = tm4c123_control,
    .putc = tm4c123_putc,
    .getc = tm4c123_getc,
    .dma_transmit = tm4c123_dma_transmit
};

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */

static void uart_isr(struct rt_serial_device *serial)
{
    struct tm4c123_uart *uart;
	  uint32_t ui32Ints;
	
#ifdef RT_SERIAL_USING_DMA
    rt_size_t recv_total_index, recv_len;
    rt_base_t level;
#endif

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct tm4c123_uart, serial);

		ui32Ints = UARTIntStatus(uart->config->uartbase, true);
	  UARTIntClear(uart->config->uartbase, ui32Ints);

    /* UART in mode Receiver -------------------------------------------------*/
	  if(ui32Ints & (UART_INT_RX | UART_INT_RT))
    {

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

}

#if defined(BSP_USING_UART0)
void UART0IntHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART0_INDEX].serial));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif


#if defined(BSP_USING_UART1)
void UART1IntHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART1_INDEX].serial));
    /* leave interrupt */
    rt_interrupt_leave();
}


//#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA)
//void UART1_DMA_RX_IRQHandler(void)
//{
//    /* enter interrupt */
//    rt_interrupt_enter();

//    HAL_DMA_IRQHandler(&uart_obj[UART1_INDEX].dma_rx.handle);

//    /* leave interrupt */
//    rt_interrupt_leave();
//}
//#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_RX_USING_DMA) */

//#if defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA)
//void UART1_DMA_TX_IRQHandler(void)
//{
//    /* enter interrupt */
//    rt_interrupt_enter();

//    HAL_DMA_IRQHandler(&uart_obj[UART1_INDEX].dma_tx.handle);

//    /* leave interrupt */
//    rt_interrupt_leave();
//}
//#endif /* defined(RT_SERIAL_USING_DMA) && defined(BSP_UART1_TX_USING_DMA) */
#endif /* BSP_USING_UART1 */


static void tm4c123_uart_get_dma_config(void)
{
#ifdef BSP_USING_UART1

#endif

}

int rt_hw_usart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct tm4c123_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    //tm4c123_uart_get_dma_config();
    uart_hw_config();
	
	
    for (int i = 0; i < obj_num; i++)
    {
        uart_obj[i].config = &uart_config[i];
			  uart_obj[i].uartintbase = uart_intbase[i];
        uart_obj[i].serial.ops    = &tm4c123_uart_ops;
        uart_obj[i].serial.config = config;
        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
                                       | uart_obj[i].uart_dma_flag
                                       , NULL);
        RT_ASSERT(result == RT_EOK);
    }
    return result;
}



#endif /* RT_USING_SERIAL */

