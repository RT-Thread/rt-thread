/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-19     Pillar       first version
 */

#include "drv_uart.h"
#include "board.h"

typedef void (*Uart_Irq_Handler_t)(void);

struct s32k3_uart_config
{
    const char *name;
    LPUART_Type *Instance;
    IRQn_Type irq_type;
    rt_uint8_t priority;
};

struct s32k3_uart_pin
{
    SIUL2_Type *base;
    rt_uint32_t tx_pinIdx;
    rt_uint32_t tx_mux;
    rt_uint32_t rx_pinIdx;
    rt_uint32_t rx_mux;
    rt_uint32_t rx_input_mux_reg;
    rt_uint32_t rx_input_mux;
};

struct s32k3_uart
{
    struct s32k3_uart_config *config;
    struct s32k3_uart_pin *pin_config;
    struct rt_serial_device serial;
};

#ifndef BSP_USING_UART3
#error "Please define BSP_USING_UART3"
#endif

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                                \
    {                                                               \
        .name = "uart3",                                            \
        .Instance = IP_LPUART_3,                                    \
        .irq_type = LPUART3_IRQn,                                   \
        .priority = 0                                               \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */

enum
{
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
};

static struct s32k3_uart_config uart_config[] =
{
#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif
};

static struct s32k3_uart_pin uart_pin[] =
{
#ifdef BSP_USING_UART3
    {
        .base = IP_SIUL2,
        .tx_pinIdx = 98,
        .tx_mux = 6,
        .rx_pinIdx = 99,
        .rx_mux = 0,
        .rx_input_mux_reg = 190,
        .rx_input_mux = 3,
    },
#endif
};

static struct s32k3_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static inline void _lpuart3_clock_init()
{
    /* just for LPUART3 */
    IP_MC_ME->PRTN1_COFB2_CLKEN |= MC_ME_PRTN1_COFB2_CLKEN_REQ77_MASK;
    IP_MC_ME->PRTN1_COFB0_CLKEN &= (~MC_ME_PRTN1_COFB0_CLKEN_REQ24_MASK);
    IP_MC_ME->PRTN1_PCONF  |= MC_ME_PRTN1_PCONF_PCE_MASK;
    IP_MC_ME->PRTN1_PUPD   |= MC_ME_PRTN1_PUPD_PCUD_MASK;

    IP_MC_ME->CTL_KEY = 0x5AF0U; /* Enter key */
    IP_MC_ME->CTL_KEY = 0xA50FU;
}

static inline void _lpuart_set_int(LPUART_Type * Base, rt_uint32_t mask, rt_bool_t Enable)
{
    if (Enable)
        Base->CTRL |=  mask;
    else
        Base->CTRL &=  ~mask;
}

#if defined(BSP_USING_UART3)
void uart3_isr()
{
    rt_interrupt_enter();
    rt_hw_serial_isr(&uart_obj[UART3_INDEX].serial, RT_SERIAL_EVENT_RX_IND);
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

#ifndef INT_CTRL_IP_NVIC_PRIO_BITS
#define INT_CTRL_IP_NVIC_PRIO_BITS                (4U)
#endif

#define SIUL2_MSCR_SSS_ALL_MASK     (0x0F)
#define SIUL2_MSCR_SSS_ALL_SHIFT    (0)
#define SIUL2_MSCR_SSS_ALL(x)       (((rt_uint32_t)(((rt_uint32_t)(x)) << SIUL2_MSCR_SSS_ALL_SHIFT)) & SIUL2_MSCR_SSS_ALL_MASK)
#define SIUL2_MAX_NUM_OF_IMCR_REG   (512u)

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct s32k3_uart *uart = rt_container_of(serial, struct s32k3_uart, serial);
    LPUART_Type *Instance = uart->config->Instance;
    SIUL2_Type *base = uart->pin_config->base;
    rt_uint32_t irqn = (rt_uint32_t)uart->config->irq_type;
    rt_uint8_t shift = (rt_uint8_t) (8U - INT_CTRL_IP_NVIC_PRIO_BITS);
    Uart_Irq_Handler_t *vector = (Uart_Irq_Handler_t *)S32_SCB->VTOR;

    _lpuart3_clock_init();

    /* tx Pin set */
    rt_uint32_t pin_val = 0;
    pin_val |= SIUL2_MSCR_OBE_MASK;
    pin_val |= SIUL2_MSCR_SSS_ALL(uart->pin_config->tx_mux);
    base->MSCR[uart->pin_config->tx_pinIdx] = pin_val;
    /* rx Pin set */
    pin_val = 0;
    pin_val |= SIUL2_MSCR_IBE_MASK;
    pin_val |= SIUL2_MSCR_SSS_ALL(uart->pin_config->rx_mux);
    base->IMCR[uart->pin_config->rx_input_mux_reg] = SIUL2_IMCR_SSS(uart->pin_config->rx_input_mux);
    base->MSCR[uart->pin_config->rx_pinIdx] = pin_val;

    /* set IRQ */
    /* clear pending flag */
    S32_NVIC->ICPR[irqn >> 5U] = (rt_uint32_t)(1UL << (irqn & (rt_uint32_t)0x1FU));
    /* set Priority */
    S32_NVIC->IP[irqn] = (rt_uint8_t)((((rt_uint32_t)uart->config->priority) << shift) & 0xFFUL);
    /* Install the configured handler */
    vector[irqn + 16] = uart3_isr;
    /* eable irq */
    S32_NVIC->ISER[irqn >> 5U] = (rt_uint32_t)(1UL << (irqn & (rt_uint32_t)0x1FU));

    /* disable TE and RE */
    Instance->CTRL &= ~LPUART_CTRL_TE_MASK;
    Instance->CTRL &= ~LPUART_CTRL_RE_MASK;

    /* set baud rate */
    Instance->BAUD &= ~LPUART_BAUD_SBR_MASK;
    Instance->BAUD |= LPUART_BAUD_SBR((24000000)/(uart->serial.config.baud_rate*16));

    /* enable TE and RE */
    Instance->CTRL |= LPUART_CTRL_TE_MASK;
    Instance->CTRL |= LPUART_CTRL_RE_MASK;
    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct s32k3_uart *uart = rt_container_of(serial, struct s32k3_uart, serial);
    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
    {
        rt_uint32_t direction = (rt_uint32_t)arg;
        if(direction == RT_DEVICE_FLAG_INT_RX)
            _lpuart_set_int(uart->config->Instance, LPUART_CTRL_RIE_MASK, RT_FALSE);

        break;
    }

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
    {
        // HAL_NVIC_SetPriority(uart->config->irq_type, 1, 0);
        rt_uint32_t direction = (rt_uint32_t)arg;
        if(direction == RT_DEVICE_FLAG_INT_RX)
            _lpuart_set_int(uart->config->Instance, LPUART_CTRL_RIE_MASK, RT_TRUE);

        break;
    }

    default:
        break;
    }
    return RT_EOK;
}

static int uart_putchar(struct rt_serial_device *serial, char ch)
{
    struct s32k3_uart *uart = rt_container_of(serial, struct s32k3_uart, serial);
    LPUART_Type *base = uart->config->Instance;

    while((base->STAT &LPUART_STAT_TDRE_MASK) !=  LPUART_STAT_TDRE_MASK);

    base->DATA = ch;
    return 1;
}

static int uart_getchar(struct rt_serial_device *serial)
{
    struct s32k3_uart *uart = rt_container_of(serial, struct s32k3_uart, serial);
    LPUART_Type *base = uart->config->Instance;

    if ((base->STAT & LPUART_STAT_RDRF_MASK) !=  LPUART_STAT_RDRF_MASK)
        return -1;
    else
        return base->DATA;
}

static const struct rt_uart_ops uart_ops =
{
    .configure = uart_configure,
    .control = uart_control,
    .putc = uart_putchar,
    .getc = uart_getchar,
};

int rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (rt_size_t i = 0; i < sizeof(uart_obj) / sizeof(uart_obj[0]); i++)
    {
        /* init UART object */
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].pin_config = &uart_pin[i];
        uart_obj[i].serial.ops = &uart_ops;
        uart_obj[i].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                       RT_NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}
