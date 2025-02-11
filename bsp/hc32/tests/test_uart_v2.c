/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
 * 程序清单：这是一个串口设备
 * 例程导出了 uart_sample_v2 命令到控制终端
 * 程序功能：通过串口输出字符串 "hello RT-Thread!"，并通过串口输出接收到的数据，然后打印接收到的数据。
 *
 * 中断方式，rtconfig.h修改如下
 * #define BSP_USING_GPIO
 * #define BSP_USING_UART
 * #define BSP_USING_UART1
 * //#define BSP_UART1_RX_USING_DMA
 * //#define BSP_UART1_TX_USING_DMA
 * #define BSP_UART1_RX_BUFSIZE 256
 * #define BSP_UART1_TX_BUFSIZE 256
 * #define BSP_USING_UART2
 * #define BSP_UART2_RX_USING_DMA
 * #define BSP_UART2_TX_USING_DMA
 * #define BSP_UART2_RX_BUFSIZE 256
 * #define BSP_UART2_TX_BUFSIZE 0
 * #define BSP_USING_UART5
 * //#define BSP_UART5_RX_USING_DMA
 * //#define BSP_UART5_TX_USING_DMA
 * #define BSP_UART5_RX_BUFSIZE 256
 * #define BSP_UART5_TX_BUFSIZE 256
 *
 * DMA方式，rtconfig.h修改如下
 * #define BSP_USING_GPIO
 * #define BSP_USING_UART
 * #define BSP_USING_UART1
 * #define BSP_UART1_RX_USING_DMA
 * #define BSP_UART1_TX_USING_DMA
 * #define BSP_UART1_RX_BUFSIZE 256
 * #define BSP_UART1_TX_BUFSIZE 256
 * #define BSP_USING_UART2
 * #define BSP_UART2_RX_USING_DMA
 * #define BSP_UART2_TX_USING_DMA
 * #define BSP_UART2_RX_BUFSIZE 256
 * #define BSP_UART2_TX_BUFSIZE 0
 * #define BSP_USING_UART5
 * #define BSP_UART5_RX_USING_DMA
 * #define BSP_UART5_TX_USING_DMA
 * #define BSP_UART5_RX_BUFSIZE 256
 * #define BSP_UART5_TX_BUFSIZE 256
 *
 * 命令调用格式：
 * uart1 中断，命令调用格式：uart_sample_v2 uart1 int
 * uart1 DMA，命令调用格式：uart_sample_v2 uart1 dma
 */

#include <rtthread.h>
#include <rtdevice.h>

#if defined(HC32F460) && defined(BSP_USING_UART2)
    #define SAMPLE_DEFAULT_UART_NAME       "uart2"
#elif defined(HC32F4A0) && defined (BSP_USING_UART6)
    #define SAMPLE_DEFAULT_UART_NAME       "uart6"
#elif defined(HC32F448) && defined (BSP_USING_UART1)
    #define SAMPLE_DEFAULT_UART_NAME       "uart1"
#elif defined(HC32F472) && defined (BSP_USING_UART1)
    #define SAMPLE_DEFAULT_UART_NAME       "uart1"
#endif

#if defined(SAMPLE_DEFAULT_UART_NAME)

/* 串口接收消息结构 */
struct rx_msg
{
    rt_device_t dev;
    rt_size_t size;
};
/* 串口设备句柄 */
static rt_device_t serial;
/* 消息队列控制块 */
static struct rt_messagequeue rx_mq;

/* 用于接收消息的信号量 */
static struct rt_semaphore rx_sem;

static rt_device_t serial;
static struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

/* DMA接收数据回调函数 */
static rt_err_t uart_input_dma(rt_device_t dev, rt_size_t size)
{
    struct rx_msg msg;
    rt_err_t result;
    msg.dev = dev;
    msg.size = size;

    result = rt_mq_send(&rx_mq, &msg, sizeof(msg));
    if (result == -RT_EFULL)
    {
        /* 消息队列满 */
        rt_kprintf("message queue full!\n");
    }
    return result;
}

/* INT接收数据回调函数 */
static rt_err_t uart_input_int(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

/* 发送完成回调函数 */
static rt_err_t uart_ouput(rt_device_t dev, void *buffer)
{
    return RT_EOK;
}

static void serial_thread_entry_dma(void *parameter)
{
    struct rx_msg msg;
    rt_err_t result;
    rt_uint32_t rx_length;
    static char rx_buffer[256];
    static rt_uint32_t buf_size = sizeof(rx_buffer);
    static rt_uint32_t put_index = 0;

    while (1)
    {
        rt_memset(&msg, 0, sizeof(msg));
        /* 从消息队列中读取消息 */
        result = rt_mq_recv(&rx_mq, &msg, sizeof(msg), RT_WAITING_FOREVER);
        if (result > 0UL)
        {
            while (msg.size)
            {
                if (msg.size > (buf_size - put_index))
                {
                    rx_length = rt_device_read(msg.dev, 0, rx_buffer + put_index, buf_size - put_index);
                    msg.size -= rx_length;
                }
                else
                {
                    rx_length = rt_device_read(msg.dev, 0, rx_buffer + put_index, msg.size);
                    msg.size = 0UL;
                }
                rt_device_write(serial, 0, rx_buffer + put_index, rx_length);
                put_index += rx_length;
                put_index %= sizeof(rx_buffer);
            }
        }
    }
}

static void serial_thread_entry_int(void *parameter)
{
    char ch;

    while (1)
    {
        /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {
            /* 阻塞等待接收信号量，等到信号量后再次读取数据 */
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        }
        /* 读取到的数据通过串口错位输出 */
        rt_device_write(serial, 0, &ch, 1);
    }
}

int uart_sample_v2(int argc, char *argv[])
{
    rt_thread_t thread;
    rt_err_t ret = RT_EOK;
    rt_size_t n;
    rt_err_t open_flag = 0UL;
    static char uart_name[RT_NAME_MAX];
    static char comm_mode[RT_NAME_MAX];
    const static char comm_mode_int[] = "int";
    const static char comm_mode_dma[] = "dma";
    const static char comm_info_dma[] = "\r\n drv_version: drv_usart_v2 \r\n communication: using DMA \r\n uart_ch: ";
    const static char comm_info_int[] = "\r\n drv_version: drv_usart_v2 \r\n communication: using interrupt \r\n uart_ch: ";
    static char comm_info[150];

    rt_memset(uart_name, 0, sizeof(uart_name));
    rt_memset(comm_mode, 0, sizeof(comm_mode));

    if (argc == 1)
    {
        rt_strncpy(uart_name, SAMPLE_DEFAULT_UART_NAME, RT_NAME_MAX);
        rt_strncpy(comm_mode, comm_mode_int, sizeof(comm_mode_int));
    }
    else if (argc == 2)
    {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
        rt_strncpy(comm_mode, comm_mode_int, sizeof(comm_mode_int));
    }
    else if (argc == 3)
    {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
        rt_strncpy(comm_mode, argv[2], RT_NAME_MAX);
    }
    else
    {
        rt_kprintf("argc error!\n");
        return -RT_ERROR;
    }

    /* 查找串口设备 */
    serial = rt_device_find(uart_name);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", uart_name);
        return -RT_ERROR;
    }

    /* modify configure */
    config.baud_rate = BAUD_RATE_115200;      //baudrate 115200
    config.data_bits = DATA_BITS_8;           //data bit 8
    config.stop_bits = STOP_BITS_1;           //stop bit 1
    config.parity    = PARITY_NONE;
    rt_device_control(serial, RT_DEVICE_CTRL_CONFIG, &config);

    if (0 == rt_strncmp(comm_mode, comm_mode_dma, 3))
    {
        static char msg_pool[256U];
        /* 初始化消息队列 */
        rt_mq_init(&rx_mq, "rx_mq",
                   msg_pool,                 /* 存放消息的缓冲区 */
                   sizeof(struct rx_msg),    /* 一条消息的最大长度 */
                   sizeof(msg_pool),         /* 存放消息的缓冲区大小 */
                   RT_IPC_FLAG_FIFO);        /* 如果有多个线程等待，按照先来先得到的方法分配消息 */

        /* 以DMA接收和发送模式打开串口设备 */
        open_flag |= RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX;
        rt_device_open(serial, open_flag);

        /* 设置回调函数 */
        rt_device_set_rx_indicate(serial, uart_input_dma);
        rt_device_set_tx_complete(serial, uart_ouput);

        /* 发送字符串 */
        n = rt_strlen(comm_info_dma);
        rt_strncpy(comm_info, comm_info_dma, n);
        rt_strncpy(comm_info + n, uart_name, rt_strlen(uart_name));
        rt_device_write(serial, 0, comm_info, rt_strlen(comm_info));

        /* 创建 serial 线程 */
        thread = rt_thread_create("serial", serial_thread_entry_dma, RT_NULL, 1024, 25, 10);
    }
    else if (0 == rt_strncmp(comm_mode, comm_mode_int, 3))
    {
        /* 以中断模式打开串口设备 */
        open_flag = RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX;
        rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);

        rt_device_open(serial, open_flag);

        /* 设置回调函数 */
        rt_device_set_rx_indicate(serial, uart_input_int);
        rt_device_set_tx_complete(serial, uart_ouput);

        /* 发送字符串 */
        n = rt_strlen(comm_info_int);
        rt_strncpy(comm_info, comm_info_int, n);
        rt_strncpy(comm_info + n, uart_name, rt_strlen(uart_name));
        rt_device_write(serial, 0, comm_info, rt_strlen(comm_info));

        /* 创建 serial 线程 */
        thread = rt_thread_create("serial", serial_thread_entry_int, RT_NULL, 1024, 25, 10);
    }
    else
    {
        rt_kprintf("communication mode error, please input cmd: uart_sample_v2 %s int or uart_sample_v1 uartx dma!\n", uart_name);
        return -RT_ERROR;
    }

    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = -RT_ERROR;
    }

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(uart_sample_v2, uart device sample);

#endif
