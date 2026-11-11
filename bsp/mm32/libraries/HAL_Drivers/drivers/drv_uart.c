/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtconfig.h>
#include <rthw.h>
#include "board.h"
#include "drv_uart.h"

#ifdef RT_USING_SERIAL

#define LOG_TAG             "drv.uart"
#include <rtdbg.h>

#if defined(SOC_SERIES_MM32F3277)

#include "drv_config.h"

#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && \
    !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8)
#error "Please define at least one BSP_USING_UARTx"
#endif

static struct mm32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif
#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif
#ifdef BSP_USING_UART4
    UART4_CONFIG,
#endif
#ifdef BSP_USING_UART5
    UART5_CONFIG,
#endif
#ifdef BSP_USING_UART6
    UART6_CONFIG,
#endif
#ifdef BSP_USING_UART7
    UART7_CONFIG,
#endif
#ifdef BSP_USING_UART8
    UART8_CONFIG,
#endif
};

static struct mm32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static struct mm32_uart *mm32_uart_get_by_instance(UART_Type *instance)
{
    rt_size_t i;

    for (i = 0; i < sizeof(uart_obj) / sizeof(uart_obj[0]); i++)
    {
        if (uart_obj[i].config->Instance == instance)
        {
            return &uart_obj[i];
        }
    }

    return RT_NULL;
}

static rt_err_t mm32_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct mm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct mm32_uart, serial);
    uart->handle.ClockFreqHz = HAL_Get_APB2_Clock();
    uart->handle.BaudRate = cfg->baud_rate;
    uart->handle.XferMode = UART_XferMode_RxTx;

    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        uart->handle.HwFlowControl = UART_HwFlowControl_RTS_CTS;
        break;
    case RT_SERIAL_FLOWCONTROL_NONE:
    default:
        uart->handle.HwFlowControl = UART_HwFlowControl_None;
        break;
    }

    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        uart->handle.WordLength = UART_WordLength_5b;
        break;
    case DATA_BITS_6:
        uart->handle.WordLength = UART_WordLength_6b;
        break;
    case DATA_BITS_7:
        uart->handle.WordLength = UART_WordLength_7b;
        break;
    case DATA_BITS_8:
    default:
        uart->handle.WordLength = UART_WordLength_8b;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        uart->handle.StopBits = UART_StopBits_2;
        break;
    case STOP_BITS_1:
    default:
        uart->handle.StopBits = UART_StopBits_1;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        uart->handle.Parity = UART_Parity_Odd;
        break;
    case PARITY_EVEN:
        uart->handle.Parity = UART_Parity_Even;
        break;
    case PARITY_NONE:
    default:
        uart->handle.Parity = UART_Parity_None;
        break;
    }

    extern void UART_MspInit(UART_Type *muart);
    UART_MspInit(uart->config->Instance);
    UART_Init(uart->config->Instance, &uart->handle);
    UART_Enable(uart->config->Instance, true);

    return RT_EOK;
}

static rt_err_t mm32_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct mm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct mm32_uart, serial);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        UART_EnableInterrupts(uart->config->Instance, UART_INT_RX_DONE, false);
        NVIC_DisableIRQ(uart->config->irq_type);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        UART_EnableInterrupts(uart->config->Instance, UART_INT_RX_DONE, true);
        NVIC_SetPriority(uart->config->irq_type, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
        NVIC_EnableIRQ(uart->config->irq_type);
        break;
    default:
        break;
    }

    return RT_EOK;
}

static int mm32_uart_putc(struct rt_serial_device *serial, char c)
{
    struct mm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct mm32_uart, serial);
    UART_PutData(uart->config->Instance, (rt_uint8_t)c);

    while ((UART_GetStatus(uart->config->Instance) & UART_STATUS_TX_EMPTY) == 0)
    {
    }

    return 1;
}

static int mm32_uart_getc(struct rt_serial_device *serial)
{
    struct mm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct mm32_uart, serial);

    if ((UART_GetStatus(uart->config->Instance) & UART_STATUS_RX_DONE) != 0)
    {
        return UART_GetData(uart->config->Instance);
    }

    return -1;
}

static void mm32_uart_isr(struct mm32_uart *uart)
{
    RT_ASSERT(uart != RT_NULL);

    if (((UART_GetInterruptStatus(uart->config->Instance) & UART_INT_RX_DONE) != 0) &&
        ((UART_GetStatus(uart->config->Instance) & UART_STATUS_RX_DONE) != 0))
    {
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_IND);
        UART_ClearInterruptStatus(uart->config->Instance, UART_INT_RX_DONE);
    }
}

#define MM32_UART_IRQHandler(n)                         \
void UART##n##_IRQHandler(void)                         \
{                                                       \
    struct mm32_uart *uart;                             \
    rt_interrupt_enter();                               \
    uart = mm32_uart_get_by_instance(UART##n);          \
    if (uart != RT_NULL)                                \
    {                                                   \
        mm32_uart_isr(uart);                            \
    }                                                   \
    rt_interrupt_leave();                               \
}

#ifdef BSP_USING_UART1
MM32_UART_IRQHandler(1)
#endif
#ifdef BSP_USING_UART2
MM32_UART_IRQHandler(2)
#endif
#ifdef BSP_USING_UART3
MM32_UART_IRQHandler(3)
#endif
#ifdef BSP_USING_UART4
MM32_UART_IRQHandler(4)
#endif
#ifdef BSP_USING_UART5
MM32_UART_IRQHandler(5)
#endif
#ifdef BSP_USING_UART6
MM32_UART_IRQHandler(6)
#endif
#ifdef BSP_USING_UART7
MM32_UART_IRQHandler(7)
#endif
#ifdef BSP_USING_UART8
MM32_UART_IRQHandler(8)
#endif

static const struct rt_uart_ops mm32_uart_ops =
{
    .configure = mm32_uart_configure,
    .control = mm32_uart_control,
    .putc = mm32_uart_putc,
    .getc = mm32_uart_getc,
};

int rt_hw_uart_init(void)
{
    rt_size_t i;
    rt_err_t result = RT_EOK;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    for (i = 0; i < sizeof(uart_obj) / sizeof(uart_obj[0]); i++)
    {
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].serial.ops = &mm32_uart_ops;
        uart_obj[i].serial.config = config;

        result = rt_hw_serial_register(&uart_obj[i].serial,
                                       uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                       RT_NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#else
#if defined SOC_SERIES_MM32L0
#include <HAL_gpio.h>
#include <HAL_uart.h>
#include <HAL_rcc.h>
#include <HAL_misc.h>
#else
#include <hal_gpio.h>
#include <hal_uart.h>
#include <hal_rcc.h>
#include <hal_misc.h>
#endif
struct mm32_uart_config
{
    const char *name;
    UART_TypeDef *instance;
    IRQn_Type irq_type;
};

struct mm32_uart
{
    const struct mm32_uart_config *config;
    struct rt_serial_device serial;
};

static struct mm32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART1
    {
        .name = "uart1",
        .instance = UART1,
        .irq_type = UART1_IRQn,
    },
#endif
#ifdef BSP_USING_UART2
    {
        .name = "uart2",
        .instance = UART2,
        .irq_type = UART2_IRQn,
    },
#endif
#ifdef BSP_USING_UART3
    {
        .name = "uart3",
        .instance = UART3,
        .irq_type = UART3_IRQn,
    },
#endif
};

static struct mm32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static struct mm32_uart *mm32_uart_get_by_instance(UART_TypeDef *instance)
{
    rt_size_t i;

    for (i = 0; i < sizeof(uart_obj) / sizeof(uart_obj[0]); i++)
    {
        if (uart_obj[i].config->instance == instance)
        {
            return &uart_obj[i];
        }
    }

    return RT_NULL;
}

#if defined(SOC_SERIES_MM32F526)

static void mm32_uart_msp_init(UART_TypeDef *instance)
{
    mm32_msp_uart_init((void *)instance);
}

static void mm32_uart_init_struct(UART_InitTypeDef *init, const struct serial_configure *cfg)
{
    init->BaudRate = cfg->baud_rate;

    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        init->WordLength = UART_WordLength_5b;
        break;
    case DATA_BITS_6:
        init->WordLength = UART_WordLength_6b;
        break;
    case DATA_BITS_7:
        init->WordLength = UART_WordLength_7b;
        break;
    case DATA_BITS_8:
    default:
        init->WordLength = UART_WordLength_8b;
        break;
    }

    init->StopBits = (cfg->stop_bits == STOP_BITS_2) ? UART_StopBits_2 : UART_StopBits_1;
    init->Parity = UART_Parity_No;
    init->HWFlowControl = (cfg->flowcontrol == RT_SERIAL_FLOWCONTROL_CTSRTS) ?
                          UART_HWFlowControl_RTS_CTS : UART_HWFlowControl_None;
    init->Mode = UART_Mode_Rx | UART_Mode_Tx;
}

#define MM32_UART_RX_IT             UART_IT_RX
#define MM32_UART_TX_IT             UART_IT_TX
#define MM32_UART_TX_DONE_FLAG      UART_CSR_TXC_Msk

#else

static void mm32_uart_gpio_init(UART_TypeDef *instance)
{
    GPIO_InitTypeDef gpio_init;

    if (instance == UART1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);
#if defined(SOC_SERIES_MM32F327) || defined(SOC_SERIES_MM32L0)
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
#else
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
#endif

        gpio_init.GPIO_Pin = GPIO_Pin_9;
        gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
        gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &gpio_init);
        gpio_init.GPIO_Pin = GPIO_Pin_10;
#if defined(SOC_SERIES_MM32F327)
        gpio_init.GPIO_Mode = GPIO_Mode_IPU;
#else
        gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
#endif
        GPIO_Init(GPIOA, &gpio_init);

#if defined(SOC_SERIES_MM32F327)
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);
#elif defined(SOC_SERIES_MM32L0)
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
#endif
    }
    else if (instance == UART2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
#if defined(SOC_SERIES_MM32F327) || defined(SOC_SERIES_MM32L0)
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
#else
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
#endif

        gpio_init.GPIO_Pin = GPIO_Pin_2;
        gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
        gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &gpio_init);
        gpio_init.GPIO_Pin = GPIO_Pin_3;
        gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &gpio_init);

#if defined(SOC_SERIES_MM32F327)
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);
#elif defined(SOC_SERIES_MM32L0)
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
#endif
    }
#if defined(UART3) && (defined(SOC_SERIES_MM32F103) || defined(SOC_SERIES_MM32L3))
    else if (instance == UART3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART3, ENABLE);
#if defined(RCC_APB2Periph_GPIOB)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
#endif

        gpio_init.GPIO_Pin = GPIO_Pin_10;
        gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
        gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOB, &gpio_init);
        gpio_init.GPIO_Pin = GPIO_Pin_11;
        gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOB, &gpio_init);
    }
#endif
}

static void mm32_uart_msp_init(UART_TypeDef *instance)
{
    mm32_uart_gpio_init(instance);
}

static void mm32_uart_init_struct(UART_InitTypeDef *init, const struct serial_configure *cfg)
{
    init->UART_BaudRate = cfg->baud_rate;

    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        init->UART_WordLength = UART_WordLength_5b;
        break;
    case DATA_BITS_6:
        init->UART_WordLength = UART_WordLength_6b;
        break;
    case DATA_BITS_7:
        init->UART_WordLength = UART_WordLength_7b;
        break;
    case DATA_BITS_8:
    default:
        init->UART_WordLength = UART_WordLength_8b;
        break;
    }

    init->UART_StopBits = (cfg->stop_bits == STOP_BITS_2) ? UART_StopBits_2 : UART_StopBits_1;
    init->UART_Parity = UART_Parity_No;
#ifdef UART_HardwareFlowControl_RTS_CTS
    init->UART_HardwareFlowControl = (cfg->flowcontrol == RT_SERIAL_FLOWCONTROL_CTSRTS) ?
                                     UART_HardwareFlowControl_RTS_CTS : UART_HardwareFlowControl_None;
#else
    init->UART_HardwareFlowControl = UART_HardwareFlowControl_None;
#endif
    init->UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
}

#define MM32_UART_RX_IT             UART_IT_RXIEN
#define MM32_UART_TX_IT             UART_IT_TXIEN
#define MM32_UART_TX_DONE_FLAG      UART_CSR_TXC

#endif

static rt_err_t mm32_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct mm32_uart *uart;
    UART_InitTypeDef init;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct mm32_uart, serial);
    mm32_uart_msp_init(uart->config->instance);
    mm32_uart_init_struct(&init, cfg);
    UART_Init(uart->config->instance, &init);
    UART_Cmd(uart->config->instance, ENABLE);

    return RT_EOK;
}

static rt_err_t mm32_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct mm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct mm32_uart, serial);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        UART_ITConfig(uart->config->instance, MM32_UART_RX_IT, DISABLE);
        NVIC_DisableIRQ(uart->config->irq_type);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        UART_ITConfig(uart->config->instance, MM32_UART_RX_IT, ENABLE);
        NVIC_EnableIRQ(uart->config->irq_type);
        break;
    default:
        break;
    }

    return RT_EOK;
}

static int mm32_uart_putc(struct rt_serial_device *serial, char c)
{
    struct mm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct mm32_uart, serial);

    while ((uart->config->instance->CSR & MM32_UART_TX_DONE_FLAG) == 0)
    {
    }

    uart->config->instance->TDR = (rt_uint8_t)c;

    return 1;
}

static int mm32_uart_getc(struct rt_serial_device *serial)
{
    struct mm32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct mm32_uart, serial);

    if ((uart->config->instance->CSR & UART_FLAG_RXAVL) != 0)
    {
        return uart->config->instance->RDR & 0xff;
    }

    return -1;
}

static void mm32_uart_isr(struct mm32_uart *uart)
{
    RT_ASSERT(uart != RT_NULL);

    if (UART_GetITStatus(uart->config->instance, MM32_UART_RX_IT) != RESET)
    {
        UART_ClearITPendingBit(uart->config->instance, MM32_UART_RX_IT);
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_IND);
    }

    if (UART_GetITStatus(uart->config->instance, MM32_UART_TX_IT) != RESET)
    {
        UART_ClearITPendingBit(uart->config->instance, MM32_UART_TX_IT);
    }
}

#define MM32_UART_IRQHandler(n)                         \
void UART##n##_IRQHandler(void)                         \
{                                                       \
    struct mm32_uart *uart;                             \
    rt_interrupt_enter();                               \
    uart = mm32_uart_get_by_instance(UART##n);          \
    if (uart != RT_NULL)                                \
    {                                                   \
        mm32_uart_isr(uart);                            \
    }                                                   \
    rt_interrupt_leave();                               \
}

#ifdef BSP_USING_UART1
MM32_UART_IRQHandler(1)
#endif
#ifdef BSP_USING_UART2
MM32_UART_IRQHandler(2)
#endif
#ifdef BSP_USING_UART3
MM32_UART_IRQHandler(3)
#endif

static const struct rt_uart_ops mm32_uart_ops =
{
    .configure = mm32_uart_configure,
    .control = mm32_uart_control,
    .putc = mm32_uart_putc,
    .getc = mm32_uart_getc,
};

int rt_hw_uart_init(void)
{
    rt_size_t i;
    rt_err_t result = RT_EOK;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    for (i = 0; i < sizeof(uart_obj) / sizeof(uart_obj[0]); i++)
    {
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].serial.ops = &mm32_uart_ops;
        uart_obj[i].serial.config = config;

        result = rt_hw_serial_register(&uart_obj[i].serial,
                                       uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                       RT_NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#if !defined(SOC_SERIES_MM32F103) && !defined(SOC_SERIES_MM32F526)
INIT_BOARD_EXPORT(rt_hw_uart_init);
#endif

#endif

#endif /* RT_USING_SERIAL */
