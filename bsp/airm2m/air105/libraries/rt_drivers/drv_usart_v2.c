/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */


#include "board.h"
#include "drv_usart_v2.h"

#ifdef RT_USING_SERIAL_V2

//#define DRV_DEBUG
#define DBG_TAG              "drv.usart"
#ifdef DRV_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

static struct air_uart_config uart_config[] =
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

enum
{
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

static struct air_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static void air_uart_get_config(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    uart_obj[UART0_INDEX].serial.config = config;
    uart_obj[UART0_INDEX].serial.config.rx_bufsz = BSP_UART0_RX_BUFSIZE;
    uart_obj[UART0_INDEX].serial.config.tx_bufsz = BSP_UART0_TX_BUFSIZE;
#endif
#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].serial.config = config;
    uart_obj[UART1_INDEX].serial.config.rx_bufsz = BSP_UART1_RX_BUFSIZE;
    uart_obj[UART1_INDEX].serial.config.tx_bufsz = BSP_UART1_TX_BUFSIZE;
#endif
#ifdef BSP_USING_UART2
    uart_obj[UART2_INDEX].serial.config = config;
    uart_obj[UART2_INDEX].serial.config.rx_bufsz = BSP_UART2_RX_BUFSIZE;
    uart_obj[UART2_INDEX].serial.config.tx_bufsz = BSP_UART2_TX_BUFSIZE;
#endif
#ifdef BSP_USING_UART3
    uart_obj[UART3_INDEX].serial.config = config;
    uart_obj[UART3_INDEX].serial.config.rx_bufsz = BSP_UART3_RX_BUFSIZE;
    uart_obj[UART3_INDEX].serial.config.tx_bufsz = BSP_UART3_TX_BUFSIZE;
#endif
}

static int air105_uart_irq(void *pData, void *pParam)
{
    rt_uint32_t uartid = (rt_uint32_t)pData;
    rt_uint32_t State = (rt_uint32_t)pParam;
    uint8_t temp[32];
    rt_uint32_t len;
    struct rt_serial_device *serial = NULL;

    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct air_uart);
    for (int i = 0; i < obj_num; i++)
    {
        if (uart_obj[i].config->id == uartid)
            serial = &(uart_obj[i].serial);
    }
    struct rt_serial_rx_fifo *rx_fifo;

    switch (State){
        case UART_CB_TX_BUFFER_DONE:
            break;
        case DMA_CB_DONE:
            DMA_ClearStreamFlag(DBG_UART_TX_DMA_STREAM);
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
            break;
        case UART_CB_TX_ALL_DONE:
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
            break;
        case UART_CB_RX_BUFFER_FULL:
            break;
        case UART_CB_RX_TIMEOUT:
        case UART_CB_RX_NEW:
            rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;
            len = Uart_FifoRead(uartid, temp);
            if (len)
            {
                rt_ringbuffer_put(&(rx_fifo->rb), temp, len);
                rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
            }
            break;
        case UART_CB_ERROR:
            break;
        case DMA_CB_ERROR:
            break;
    }
}

static rt_err_t air105_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    rt_uint32_t uart_id = serial->parent.user_data;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        cfg->stop_bits = UART_STOP_BIT1;
        break;
    case STOP_BITS_2:
        cfg->stop_bits = UART_STOP_BIT2;
        break;
    default:
        cfg->stop_bits = UART_STOP_BIT1_5;
        break;
    }

    Uart_BaseInit(uart_id, cfg->baud_rate, 0, cfg->data_bits, cfg->parity, cfg->stop_bits, air105_uart_irq);
    switch (uart_id){
    case UART_ID0:
        GPIO_Iomux(GPIOA_01, 0);
        GPIO_Iomux(GPIOA_00, 0);
        break;
    case UART_ID1:
        GPIO_Iomux(GPIOC_01, 3);
        GPIO_Iomux(GPIOC_00, 3);
        break;
    case UART_ID2:
        GPIO_Iomux(GPIOD_13, 0);
        GPIO_Iomux(GPIOD_12, 0);
        break;
    case UART_ID3:
        GPIO_Iomux(GPIOE_08, 2);
        GPIO_Iomux(GPIOE_09, 2);
        break;
    default:
        break;
    }
    return RT_EOK;
}

static rt_err_t air105_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    rt_uint32_t uart_id = serial->parent.user_data;

    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
    RT_ASSERT(serial != RT_NULL);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        Uart_IrqOnOff(uart_id, 0);
        if (DBG_UART_ID == uart_id)
        {
            DMA_StopStream(DBG_UART_TX_DMA_STREAM);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        break;

    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_arg & (RT_SERIAL_RX_NON_BLOCKING|RT_SERIAL_RX_BLOCKING))
        {
            Uart_EnableRxIrq(uart_id);
        }
        Uart_IrqOnOff(uart_id, 1);
        break;

    case RT_DEVICE_CHECK_OPTMODE:
        return RT_SERIAL_TX_BLOCKING_NO_BUFFER;

    case RT_DEVICE_CTRL_CLOSE:
        Uart_DeInit(uart_id);
        switch (uart_id){
        case UART_ID0:
            GPIO_Iomux(GPIOA_01, 1);
            GPIO_Iomux(GPIOA_00, 1);
            break;
        case UART_ID1:
            GPIO_Iomux(GPIOC_01, 1);
            GPIO_Iomux(GPIOC_00, 1);
            break;
        case UART_ID2:
            GPIO_Iomux(GPIOD_13, 1);
            GPIO_Iomux(GPIOD_12, 1);
            break;
        case UART_ID3:
            GPIO_Iomux(GPIOE_08, 1);
            GPIO_Iomux(GPIOE_09, 1);
            break;
        default:
            break;
        }
        break;
    default:
        return -RT_EINVAL;

    }
    return RT_EOK;
}

static int air105_putc(struct rt_serial_device *serial, char c)
{
    rt_uint32_t uart_id = serial->parent.user_data;
    RT_ASSERT(serial != RT_NULL);
    Uart_NoBlockTx(uart_id, c);
    return 1;
}


static int air105_getc(struct rt_serial_device *serial)
{
    rt_uint32_t uart_id = serial->parent.user_data;
    RT_ASSERT(serial != RT_NULL);
    uint8_t data;
    if (Uart_ReadByte(uart_id, &data) < 0)
    {
        return -1;
    }
    else
    {
        return data;
    }
}

static rt_ssize_t air105_transmit(struct rt_serial_device     *serial,
                                       rt_uint8_t           *buf,
                                       rt_size_t             size,
                                       rt_uint32_t           tx_flag)
{
    rt_uint32_t uart_id = serial->parent.user_data;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    if (DBG_UART_ID == uart_id)
    {
        Uart_BlockTx(uart_id, buf, size);
    }
    else
    {
        Uart_BufferTx(uart_id, buf, size);
    }
    return size;
}


static const struct rt_uart_ops air105_uart_ops =
{
    .configure = air105_configure,
    .control = air105_control,
    .putc = air105_putc,
    .getc = air105_getc,
    .transmit = air105_transmit
};

int rt_hw_usart_init(void)
{
    rt_err_t result = 0;
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct air_uart);

    air_uart_get_config();
    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].config = &uart_config[i];
        if (uart_obj[i].config->id == DBG_UART_ID)
            uart_obj[i].serial.config.baud_rate = DBG_UART_BR;
        uart_obj[i].serial.ops = &air105_uart_ops;
        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial,uart_obj[i].config->name,
                                        RT_DEVICE_FLAG_RDWR,
                                        i);
        RT_ASSERT(result == RT_EOK);
    }
    return result;
}

#endif /* RT_USING_SERIAL_V2 */
