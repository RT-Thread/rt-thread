/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-28     Tanek        the first version
 */
#include <rtthread.h>
#include "usart.h"

#ifdef RT_USING_UART

#include "HAL_device.h"

#ifdef RT_USING_DEVICE
#include <rtdevice.h>
#endif

#define UART_RX_BUFSZ 8

/* mm32f103 uart driver */
struct mm32_uart
{
    struct rt_device parent;
    struct rt_ringbuffer rx_rb;
    UART_TypeDef * uart_base;
    IRQn_Type uart_irq;
    rt_uint8_t rx_buffer[UART_RX_BUFSZ];
};


#ifdef RT_USING_UART1
struct mm32_uart uart1_device;
#endif

#ifdef RT_USING_UART2
struct mm32_uart uart2_device;
#endif

#ifdef RT_USING_UART3
struct mm32_uart uart3_device;
#endif

void uart_irq_handler(struct mm32_uart* uart)
{    
    /* enter interrupt */
    rt_interrupt_enter();
    
    if(UART_GetITStatus(uart->uart_base, UART_IT_RXIEN))    // RXIRQ
    {
        UART_ClearITPendingBit(uart->uart_base,UART_IT_RXIEN);
        rt_ringbuffer_putchar_force(&(uart->rx_rb), (rt_uint8_t)UART_ReceiveData(uart->uart_base));
        /* invoke callback */
        if(uart->parent.rx_indicate != RT_NULL)
        {
            uart->parent.rx_indicate(&uart->parent, rt_ringbuffer_data_len(&uart->rx_rb));
        }    
    }
    
    /* leave interrupt */
    rt_interrupt_leave();
}


#ifdef RT_USING_UART1
void UART1_IRQHandler(void)
{
    uart_irq_handler(&uart1_device);
}
#endif

#ifdef RT_USING_UART2
void UART2_IRQHandler(void)
{
    uart_irq_handler(&uart2_device);
}
#endif

#ifdef RT_USING_UART3
void UART3_IRQHandler(void)
{
    uart_irq_handler(&uart3_device);
}
#endif

static rt_err_t rt_uart_init (rt_device_t dev)
{
    struct mm32_uart* uart;
	UART_InitTypeDef UART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
    
    RT_ASSERT(dev != RT_NULL);
    uart = (struct mm32_uart *)dev;

	if(uart->uart_base == UART1)
	{
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);
	}
	else if(uart->uart_base == UART2)
	{
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
    }
	else if(uart->uart_base == UART3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART3, ENABLE);
	}
	
    UART_InitStructure.UART_BaudRate =  115200; //波特率115200
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;//数据位
    UART_InitStructure.UART_StopBits = UART_StopBits_1;//停止位
    UART_InitStructure.UART_Parity = UART_Parity_No ;
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;//输入输出模式
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None; 	
    UART_Init(uart->uart_base, &UART_InitStructure);
    UART_ITConfig(uart->uart_base, UART_IT_RXIEN, ENABLE);//开启串口接受中断
    UART_Cmd(uart->uart_base, ENABLE);  //UART 模块使能
    
    if(uart->uart_base == UART1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;   //uart1_tx  pa9
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;  //uart1_rx  pa10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入   
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }	
 
    if(uart->uart_base == UART2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;   //uart1_tx  pa2
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;  //uart1_rx  pa3
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入   
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }	

    if(uart->uart_base == UART3)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;   //uart3_tx  pc10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;  //uart3_rx  pc11
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入   
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }	

    return RT_EOK;
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct mm32_uart* uart;
    RT_ASSERT(dev != RT_NULL);
    uart = (struct mm32_uart *)dev;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Enable the UART Interrupt */
        NVIC_EnableIRQ(uart->uart_irq);
    }

    return RT_EOK;
}

static rt_err_t rt_uart_close(rt_device_t dev)
{
    struct mm32_uart* uart;
    RT_ASSERT(dev != RT_NULL);
    uart = (struct mm32_uart *)dev;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Disable the UART Interrupt */
        NVIC_DisableIRQ(uart->uart_irq);
    }

    return RT_EOK;
}

static rt_size_t rt_uart_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    /* interrupt receive */
    rt_base_t level;

    rt_size_t length;
    struct mm32_uart* uart;
    RT_ASSERT(dev != RT_NULL);
    uart = (struct mm32_uart *)dev;


    RT_ASSERT(uart != RT_NULL);

    /* disable interrupt */
    level = rt_hw_interrupt_disable();
    length = rt_ringbuffer_get(&(uart->rx_rb), buffer, size);
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    return length;
}

static rt_size_t rt_uart_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    char *ptr = (char*) buffer;
    struct mm32_uart* uart;
    RT_ASSERT(dev != RT_NULL);
    uart = (struct mm32_uart *)dev;

    if (dev->open_flag & RT_DEVICE_FLAG_STREAM)
    {
        /* stream mode */
        while (size)
        {
            if (*ptr == '\n')
            {
                while (UART_GetFlagStatus(uart->uart_base, UART_IT_TXIEN) == RESET);
                UART_SendData(uart->uart_base, '\r');
            }

            while (UART_GetFlagStatus(uart->uart_base, UART_IT_TXIEN) == RESET);
            UART_SendData(uart->uart_base, *ptr); 

            ptr ++;
            size --;
        }
    }
    else
    {
        while (size)
        {
            while (UART_GetFlagStatus(uart->uart_base, UART_IT_TXIEN) == RESET);
            UART_SendData(uart->uart_base, *ptr); 

            ptr++;
            size--;
        }
    }

    return (rt_size_t) ptr - (rt_size_t) buffer;
}

int rt_hw_usart_init(void)
{
#ifdef RT_USING_UART1
    {
        struct mm32_uart* uart;

        /* get uart device */
        uart = &uart1_device;

        /* device initialization */
        uart->parent.type = RT_Device_Class_Char;
        uart->uart_base = UART1;
        uart->uart_irq = UART1_IRQn;
        
        rt_ringbuffer_init(&(uart->rx_rb), uart->rx_buffer, sizeof(uart->rx_buffer));

        /* device interface */
        uart->parent.init 	    = rt_uart_init;
        uart->parent.open 	    = rt_uart_open;
        uart->parent.close      = rt_uart_close;
        uart->parent.read 	    = rt_uart_read;
        uart->parent.write      = rt_uart_write;
        uart->parent.control    = RT_NULL;
        uart->parent.user_data  = RT_NULL;

        rt_device_register(&uart->parent, "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    }
#endif

#ifdef RT_USING_UART2
    {
        struct mm32_uart* uart;

        /* get uart device */
        uart = &uart2_device;

        /* device initialization */
        uart->parent.type = RT_Device_Class_Char;
        uart->uart_base = UART2;
        uart->uart_irq = UART2_IRQn;
        rt_ringbuffer_init(&(uart->rx_rb), uart->rx_buffer, sizeof(uart->rx_buffer));

        /* device interface */
        uart->parent.init 	    = rt_uart_init;
        uart->parent.open 	    = rt_uart_open;
        uart->parent.close      = rt_uart_close;
        uart->parent.read 	    = rt_uart_read;
        uart->parent.write      = rt_uart_write;
        uart->parent.control    = RT_NULL;
        uart->parent.user_data  = RT_NULL;

        rt_device_register(&uart->parent, "uart2", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    }
#endif
    
#ifdef RT_USING_UART3
    {
        struct mm32_uart* uart;

        /* get uart device */
        uart = &uart3_device;

        /* device initialization */
        uart->parent.type = RT_Device_Class_Char;
        uart->uart_base = UART3;
        uart->uart_irq = UART3_IRQn;
        
        rt_ringbuffer_init(&(uart->rx_rb), uart->rx_buffer, sizeof(uart->rx_buffer));

        /* device interface */
        uart->parent.init 	    = rt_uart_init;
        uart->parent.open 	    = rt_uart_open;
        uart->parent.close      = rt_uart_close;
        uart->parent.read 	    = rt_uart_read;
        uart->parent.write      = rt_uart_write;
        uart->parent.control    = RT_NULL;
        uart->parent.user_data  = RT_NULL;

        rt_device_register(&uart->parent, "uart3", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    }
#endif
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);

#endif /*RT_USING_UART*/
