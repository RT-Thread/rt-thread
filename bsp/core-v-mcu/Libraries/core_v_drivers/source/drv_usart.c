/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-08     WangShun          the first version
 */

#include "board.h"
#include "rtthread.h"
#include <drv_usart.h>
#include "hal_udma_ctrl_reg_defs.h"
#include "hal_udma_uart_reg_defs.h"
#include "udma_uart_driver.h"
#include <string.h>
#include "core-v-mcu-config.h"

#ifdef RT_USING_SERIAL
//#define DRV_DEBUG
#define LOG_TAG              "drv.uart"
#include <drv_log.h>

#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4) && \
    !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

extern char u1buffer[128], u0buffer[128];
extern  int u1rdptr, u1wrptr, u0rdptr,u0wrptr;
extern UdmaUart_t *puart0 ;
extern UdmaUart_t *puart1 ;

enum
{
    UART1_INDEX,
};

struct corev_uart_config uart_config[1] =
{
   {
     "uart1"
   }
};

struct corev_uart uart_obj[1] = {0};

static rt_err_t corev_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
     return RT_EOK;
}

static rt_err_t corev_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    return RT_EOK;
}

uint16_t rt_writeraw(uint8_t uart_id, uint16_t write_len, uint8_t* write_buffer) {
    UdmaUart_t*             puart = (UdmaUart_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);

    while (puart->status_b.tx_busy) {
    }

    puart->tx_saddr = (uint32_t)write_buffer;
    puart->tx_size = write_len;
    puart->tx_cfg_b.en = 1;

    return 0;
}

static int corev_putc(struct rt_serial_device *serial, char c)
{
    char put_data =c;
    struct corev_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = (struct corev_uart *)serial->parent.user_data;
    rt_writeraw(0, 1,&put_data);

    return 1;
}

static int corev_getc(struct rt_serial_device *serial)
{
    int ch;
    struct corev_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct corev_uart *)serial->parent.user_data;
    ch = -1;

    UdmaUart_t* puart = (UdmaUart_t*)(UDMA_CH_ADDR_UART + 0 * UDMA_CH_SIZE);

    if (puart->valid_b.rx_data_valid == 1) {
        ch = puart->data_b.rx_data & 0xff;
    }

    return ch;
}

rt_size_t corevdma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return RT_EOK;
}

 void uart_isr(struct rt_serial_device *serial)
{
    struct corev_uart *uart = (struct corev_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

static const struct rt_uart_ops corev_uart_ops =
{
    corev_configure,
    corev_control,
    corev_putc,
    corev_getc,
    corevdma_transmit
};

extern int irq_cli_flag;
void uart_rx_isr (void *id){
    rt_interrupt_enter();
    if (id == 6) {
        while (*(int*)0x1a102130) {
            u1buffer[u1wrptr++] = puart1->data_b.rx_data & 0xff;
            u1wrptr &= 0x7f;
        }
    }
    if (id == 2) {//use this uart
        while (puart0->valid) {
            if(irq_cli_flag==1)
            {
                uart_isr(&(uart_obj[UART1_INDEX].serial));
            }
            else if(irq_cli_flag==0)
            {
                u0buffer[u0wrptr++] = puart0->data_b.rx_data & 0xff;
                u0wrptr &= 0x7f;
            }
        }
    }
    rt_interrupt_leave();
}

int rt_hw_usart_init(void)
{
    rt_size_t obj_num = 1;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].config        = &uart_config[i];
        uart_obj[i].serial.ops    = &corev_uart_ops;
        uart_obj[i].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       ,&uart_obj[i]);
        RT_ASSERT(result == RT_EOK);
    }
    return result;
}

#endif /* RT_USING_SERIAL */
