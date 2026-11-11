/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-25     seteiro      USART1 at the default pins: TX PD5, RX PD6
 *
 * A char device, not the serial framework. 16KB flash cannot hold dev_serial.
 */

#include "board.h"
#include <rtthread.h>

#ifdef BSP_USING_UART

#define RX_SIZE 16

static struct rt_device _uart;
static rt_uint8_t _rx[RX_SIZE];
static rt_uint8_t _rx_get;
static rt_uint8_t _rx_put;
static volatile rt_uint32_t _rx_count;
static volatile rt_uint8_t _need_wake;

static void _hw_init(void)
{
    GPIO_InitTypeDef gpio;
    USART_InitTypeDef uart;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    gpio.GPIO_Pin = GPIO_Pin_5;
    gpio.GPIO_Speed = GPIO_Speed_30MHz;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &gpio);

    gpio.GPIO_Pin = GPIO_Pin_6;
    gpio.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOD, &gpio);

    USART_StructInit(&uart);
    uart.USART_BaudRate = 115200;
    USART_Init(USART1, &uart);
    USART_Cmd(USART1, ENABLE);
}

static rt_err_t _init(rt_device_t dev)
{
    RT_UNUSED(dev);
    _hw_init();
    return RT_EOK;
}

static void _push(rt_uint8_t ch)
{
    rt_uint8_t next;

    next = (_rx_put + 1) % RX_SIZE;
    if (next == _rx_get)
    {
        return;
    }
    _rx[_rx_put] = ch;
    _rx_put = next;
    _need_wake = 1;
}

static void _wake(void)
{
    if (!_need_wake)
    {
        return;
    }
    _need_wake = 0;
    if (_uart.rx_indicate)
    {
        _uart.rx_indicate(&_uart, 1);
    }
}

static rt_err_t _open(rt_device_t dev, rt_uint16_t oflag)
{
    RT_UNUSED(dev);
    RT_UNUSED(oflag);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    NVIC_SetPriority(USART1_IRQn, 0x80);
    NVIC_EnableIRQ(USART1_IRQn);
    return RT_EOK;
}

static rt_err_t _close(rt_device_t dev)
{
    RT_UNUSED(dev);
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    NVIC_DisableIRQ(USART1_IRQn);
    return RT_EOK;
}

static rt_ssize_t _read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_uint8_t *dst = buffer;
    rt_size_t i = 0;
    rt_base_t level;

    RT_UNUSED(dev);
    RT_UNUSED(pos);
    while (i < size)
    {
        level = rt_hw_interrupt_disable();
        if (_rx_get == _rx_put)
        {
            rt_hw_interrupt_enable(level);
            break;
        }
        dst[i] = _rx[_rx_get];
        _rx_get = (_rx_get + 1) % RX_SIZE;
        rt_hw_interrupt_enable(level);
        i++;
    }
    return (rt_ssize_t)i;
}

static rt_ssize_t _write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    const rt_uint8_t *src = buffer;
    rt_size_t i;

    RT_UNUSED(dev);
    RT_UNUSED(pos);
    for (i = 0; i < size; i++)
    {
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, src[i]);
    }
    return (rt_ssize_t)size;
}

int rt_hw_usart_init(void)
{
    _uart.type = RT_Device_Class_Char;
    _uart.init = _init;
    _uart.open = _open;
    _uart.close = _close;
    _uart.read = _read;
    _uart.write = _write;
    rt_thread_idle_sethook(_wake);
    return rt_device_register(&_uart, "uart1",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM);
}

void rt_hw_usart_rx_poll(void)
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
    {
        return;
    }
    _rx_count++;
    _push((rt_uint8_t)USART_ReceiveData(USART1));
}

rt_uint32_t rt_hw_usart_rx_count(void)
{
    return _rx_count;
}

void USART1_IRQHandler(void) __attribute__((interrupt()));
void USART1_IRQHandler(void)
{
    GET_INT_SP();
    rt_interrupt_enter();
    rt_hw_usart_rx_poll();
    rt_interrupt_leave();
    FREE_INT_SP();
}

#endif
