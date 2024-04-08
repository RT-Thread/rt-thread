/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-09     Lyons        first version
 */

#include <rtconfig.h>

#ifdef RT_USING_SERIAL

#include "board.h"
#include "drv_uart.h"
#include "drv_common.h"

enum
{
#ifdef BSP_USING_UART1
    eDevUart_UART1,
#endif
#ifdef BSP_USING_UART2
    eDevUart_UART2,
#endif
#ifdef BSP_USING_UART3
    eDevUart_UART3,
#endif
#ifdef BSP_USING_UART4
    eDevUart_UART4,
#endif
#ifdef BSP_USING_UART5
    eDevUart_UART5,
#endif
#ifdef BSP_USING_UART6
    eDevUart_UART6,
#endif
#ifdef BSP_USING_UART7
    eDevUart_UART7,
#endif
#ifdef BSP_USING_UART8
    eDevUart_UART8,
#endif

    eDevUart_Max,
};

_internal_rw struct imx_uart _s_uart[eDevUart_Max] = {
#ifdef BSP_USING_UART1
{
    .name = "uart0",
    .periph.paddr = IMX6ULL_UART1_BASE,
    .irqno = UART1_IRQn,
    .gpio = {
        {IOMUXC_UART1_TX_DATA_UART1_TX,     0, 0x10B0},
        {IOMUXC_UART1_RX_DATA_UART1_RX,     0, 0x10B0},
    },
    .flag = (RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX),
    .param = RT_SERIAL_CONFIG_115200N81,
},
#endif

#ifdef BSP_USING_UART2
{
    .name = "uart1",
    .periph.paddr = IMX6ULL_UART2_BASE,
    .irqno = UART2_IRQn,
    .gpio = {
        {IOMUXC_UART2_TX_DATA_UART2_TX,     0, 0x10B0},
        {IOMUXC_UART2_RX_DATA_UART2_RX,     0, 0x10B0},
    },
    .flag = (RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX),
    .param = RT_SERIAL_CONFIG_DEFAULT,
},
#endif

#ifdef BSP_USING_UART3
{
    .name = "uart2",
    .periph.paddr = IMX6ULL_UART3_BASE,
    .irqno = UART3_IRQn,
    .gpio = {
        {IOMUXC_UART3_TX_DATA_UART3_TX,     0, 0x10B0},
        {IOMUXC_UART3_RX_DATA_UART3_RX,     0, 0x10B0},
    },
    .flag = (RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX),
    .param = RT_SERIAL_CONFIG_DEFAULT,
},
#endif

#ifdef BSP_USING_UART4
{
    .name = "uart3",
    .periph.paddr = IMX6ULL_UART4_BASE,
    .irqno = UART4_IRQn,
    .gpio = {
        {IOMUXC_UART4_TX_DATA_UART4_TX,     0, 0x10B0},
        {IOMUXC_UART4_RX_DATA_UART4_RX,     0, 0x10B0},
    },
    .flag = (RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX),
    .param = RT_SERIAL_CONFIG_DEFAULT,
},
#endif

#ifdef BSP_USING_UART5
{
    .name = "uart4",
    .periph.paddr = IMX6ULL_UART5_BASE,
    .irqno = UART5_IRQn,
    .gpio = {
        {IOMUXC_UART5_TX_DATA_UART5_TX,     0, 0x10B0},
        {IOMUXC_UART5_RX_DATA_UART5_RX,     0, 0x10B0},
    },
    .flag = (RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX),
    .param = RT_SERIAL_CONFIG_DEFAULT,
},
#endif

#ifdef BSP_USING_UART6
{
    .name = "uart5",
    .periph.paddr = IMX6ULL_UART6_BASE,
    .irqno = UART6_IRQn,
    .gpio = {
        {IOMUXC_ENET2_RX_DATA1_UART6_TX,    0, 0x10B0},
        {IOMUXC_ENET2_RX_DATA0_UART6_RX,    0, 0x10B0},
    },
    .flag = (RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX),
    .param = RT_SERIAL_CONFIG_DEFAULT,
},
#endif

#ifdef BSP_USING_UART7
{
    .name = "uart6",
    .periph.paddr = IMX6ULL_UART7_BASE,
    .irqno = UART7_IRQn,
    .gpio = {
        {IOMUXC_ENET2_TX_DATA0_UART7_TX,    0, 0x10B0},
        {IOMUXC_ENET2_RX_EN_UART7_RX,       0, 0x10B0},
    },
    .flag = (RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX),
    .param = RT_SERIAL_CONFIG_DEFAULT,
},
#endif

#ifdef BSP_USING_UART8
{
    .name = "uart7",
    .periph.paddr = IMX6ULL_UART8_BASE,
    .irqno = UART8_IRQn,
    .gpio = {
        {IOMUXC_ENET2_TX_DATA1_UART8_TX,    0, 0x10B0},
        {IOMUXC_ENET2_TX_EN_UART8_RX,       0, 0x10B0},
    },
    .flag = (RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX),
    .param = RT_SERIAL_CONFIG_DEFAULT,
},
#endif
};

static void _uart_gpio_init( struct imx_uart *device )
{
    for (int i=0; i<GET_ARRAY_NUM(device->gpio); i++)
    {
        imx6ull_gpio_init(&device->gpio[i]);
    }
}

static rt_err_t _uart_ops_configure( struct rt_serial_device *dev,
                                     struct serial_configure *cfg )
{
    struct imx_uart *uart = RT_NULL;
    UART_Type *periph = RT_NULL;
    rt_uint32_t reg_value;

    RT_ASSERT(RT_NULL != dev);
    RT_ASSERT(RT_NULL != cfg);

    uart = (struct imx_uart*)dev;
    periph = (UART_Type*)uart->periph.vaddr;

    _uart_gpio_init(uart);

    periph->UCR1 &= ~UART_UCR1_UARTEN_MASK;

    periph->UFCR &= ~UART_UFCR_RFDIV_MASK;
    periph->UFCR |=  UART_UFCR_RFDIV(5);

    RT_ASSERT(cfg->baud_rate <= BAUD_RATE_921600);

    periph->UBIR = UART_UBIR_INC(15);
    periph->UBMR = UART_UBMR_MOD(HW_UART_BUS_CLOCK / cfg->baud_rate - 1);

    reg_value = 0;

    switch (cfg->data_bits)
    {
        case DATA_BITS_7:
            reg_value |= UART_UCR2_WS(0);
            break;
        default:
            reg_value |= UART_UCR2_WS(1);
            break;
    }

    switch (cfg->stop_bits)
    {
        case STOP_BITS_2:
            reg_value |= UART_UCR2_STPB(1);
            break;
        default:
            reg_value |= UART_UCR2_STPB(0);
            break;
    }

    switch (cfg->parity)
    {
        case PARITY_ODD:
            reg_value |= UART_UCR2_PREN(1);
            reg_value |= UART_UCR2_PROE(1);
            break;
        case PARITY_EVEN:
            reg_value |= UART_UCR2_PREN(1);
            reg_value |= UART_UCR2_PROE(0);
            break;
        default:
            reg_value |= UART_UCR2_PREN(0);
            reg_value |= UART_UCR2_PROE(0);
            break;
    }

    periph->UCR3 |= UART_UCR3_RXDMUXSEL(1); //this bit should always be set!
    periph->UCR2 |= reg_value | UART_UCR2_IRTS(1) | UART_UCR2_TXEN(1) | UART_UCR2_RXEN(1);
    periph->UCR1 |= UART_UCR1_UARTEN(1);

    return RT_EOK;
}

static rt_err_t _uart_ops_control( struct rt_serial_device *dev,
                                   int cmd,
                                   void *arg )
{
    struct imx_uart *uart = RT_NULL;
    UART_Type *periph = RT_NULL;
    rt_err_t result;

    RT_ASSERT(RT_NULL != dev);

    uart = (struct imx_uart*)dev;
    periph = (UART_Type*)uart->periph.vaddr;

    result = RT_EOK;
    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            periph->UCR4 &= ~UART_UCR4_DREN_MASK;
            periph->UCR4 |=  UART_UCR4_DREN(0);
            break;

        case RT_DEVICE_CTRL_SET_INT:
            periph->UCR4 |=  UART_UCR4_DREN(1);
            rt_hw_interrupt_umask(uart->irqno);
            break;

        default:
            result = -RT_EINVAL;
            break;
    }

    return result;
}

static int _uart_ops_putc( struct rt_serial_device *dev,
                           char ch )
{
    struct imx_uart *uart = RT_NULL;
    UART_Type *periph = RT_NULL;

    RT_ASSERT(RT_NULL != dev);

    uart = (struct imx_uart*)dev;
    periph = (UART_Type*)uart->periph.vaddr;

    while (0 == (periph->USR2 & UART_USR2_TXDC_MASK));
    periph->UTXD = ch;

    return 1;
}

static int _uart_ops_getc( struct rt_serial_device *dev )
{
    struct imx_uart *uart = RT_NULL;
    UART_Type *periph = RT_NULL;
    int ch;

    RT_ASSERT(RT_NULL != dev);

    uart = (struct imx_uart*)dev;
    periph = (UART_Type*)uart->periph.vaddr;

    ch = (0 == (periph->USR2 & UART_USR2_RDR_MASK)) ? -1 : periph->URXD;
    return ch;
}

_internal_ro struct rt_uart_ops _k_uart_ops =
{
    _uart_ops_configure,    /* configure */
    _uart_ops_control,      /* control */
    _uart_ops_putc,         /* putc */
    _uart_ops_getc,         /* getc */
    RT_NULL,                /* dma_transmit */
};

static void _uart_isr( int irqno, void* parameter )
{
    struct rt_serial_device *serial;

    rt_interrupt_enter();

    serial = (struct rt_serial_device *)parameter;
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);

    rt_interrupt_leave();
}

int rt_hw_uart_init(void)
{
    for (int idx=0; idx<GET_ARRAY_NUM(_s_uart); idx++)
    {
        _s_uart[idx].periph.vaddr = platform_get_periph_vaddr(_s_uart[idx].periph.paddr);

        _s_uart[idx].parent.ops = &_k_uart_ops;

        rt_memcpy(&_s_uart[idx].parent.config, &_s_uart[idx].param, sizeof(struct serial_configure));

        rt_hw_serial_register( &_s_uart[idx].parent,
                               _s_uart[idx].name,
                               _s_uart[idx].flag,
                               RT_NULL );

        rt_hw_interrupt_install(_s_uart[idx].irqno, _uart_isr, &_s_uart[idx].parent, _s_uart[idx].name);
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif //#ifdef RT_USING_SERIAL
