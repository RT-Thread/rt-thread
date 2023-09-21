/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2021-09-19   HPMICRO     First version
 *
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include "board.h"
#include "drv_uart.h"
#include "hpm_uart_drv.h"
#include "hpm_sysctl_drv.h"

#ifdef RT_USING_SERIAL

#define UART_ROOT_CLK_FREQ BOARD_APP_UART_SRC_FREQ

struct hpm_uart {
    UART_Type *uart_base;
    uint32_t irq_num;
    struct rt_serial_device *serial;
    char *device_name;
};


extern void init_uart_pins(UART_Type *ptr);
static void hpm_uart_isr(struct rt_serial_device *serial);
static rt_err_t hpm_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t hpm_uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int hpm_uart_putc(struct rt_serial_device *serial, char ch);
static int hpm_uart_getc(struct rt_serial_device *serial);


#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;
void uart0_isr(void)
{
    hpm_uart_isr(&serial0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART0,uart0_isr)
#endif


#if defined(BSP_USING_UART1)
struct rt_serial_device serial1;
void uart1_isr(void)
{
    hpm_uart_isr(&serial1);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART1,uart1_isr)
#endif


#if defined(BSP_USING_UART2)
struct rt_serial_device serial2;
void uart2_isr(void)
{
    hpm_uart_isr(&serial2);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART2,uart2_isr)
#endif


#if defined(BSP_USING_UART3)
struct rt_serial_device serial3;
void uart3_isr(void)
{
    hpm_uart_isr(&serial3);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART3,uart3_isr)
#endif


#if defined(BSP_USING_UART4)
struct rt_serial_device serial4;
void uart4_isr(void)
{
    hpm_uart_isr(&serial4);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART4,uart4_isr)
#endif


#if defined(BSP_USING_UART5)
struct rt_serial_device serial5;
void uart5_isr(void)
{
    hpm_uart_isr(&serial5);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART5,uart5_isr)
#endif


#if defined(BSP_USING_UART6)
struct rt_serial_device serial6;
void uart6_isr(void)
{
    hpm_uart_isr(&serial6);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART6,uart6_isr)
#endif


#if defined(BSP_USING_UART7)
struct rt_serial_device serial7;
void uart7_isr(void)
{
    hpm_uart_isr(&serial7);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART7,uart7_isr)
#endif


#if defined(BSP_USING_UART8)
struct rt_serial_device serial8;
void uart8_isr(void)
{
    hpm_uart_isr(&serial8);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART8,uart8_isr)
#endif


#if defined(BSP_USING_UART9)
struct rt_serial_device serial9;
void uart9_isr(void)
{
    hpm_uart_isr(&serial9);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART9,uart9_isr)
#endif


#if defined(BSP_USING_UART10)
struct rt_serial_device serial10;
void uart10_isr(void)
{
    hpm_uart_isr(&serial10);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART10,uart10_isr)
#endif

#if defined(BSP_USING_UART11)
struct rt_serial_device serial11;
void uart11_isr(void)
{
    hpm_uart_isr(&serial11);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART11,uart11_isr)
#endif

#if defined(BSP_USING_UART12)
struct rt_serial_device serial12;
void uart12_isr(void)
{
    hpm_uart_isr(&serial12);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART12,uart12_isr)
#endif

#if defined(BSP_USING_UART13)
struct rt_serial_device serial13;
void uart13_isr(void)
{
    hpm_uart_isr(&serial13);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART13,uart13_isr)
#endif

#if defined(BSP_USING_UART14)
struct rt_serial_device serial14;
void uart14_isr(void)
{
    hpm_uart_isr(&serial14);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART14,uart14_isr)
#endif

#if defined(BSP_USING_UART15)
struct rt_serial_device serial15;
void uart15_isr(void)
{
    hpm_uart_isr(&serial15);
}
SDK_DECLARE_EXT_ISR_M(IRQn_UART15,uart15_isr)
#endif

static const struct hpm_uart uarts[] = {
#if defined(BSP_USING_UART0)
{
    HPM_UART0,
    IRQn_UART0,
    &serial0,
    "uart0",
},
#endif

#if defined(BSP_USING_UART1)
{
    HPM_UART1,
    IRQn_UART1,
    &serial1,
    "uart1",
},
#endif

#if defined(BSP_USING_UART2)
{
    HPM_UART2,
    IRQn_UART2,
    &serial2,
    "uart2",
},
#endif

#if defined(BSP_USING_UART3)
{
    HPM_UART3,
    IRQn_UART3,
    &serial3,
    "uart3",
},
#endif

#if defined(BSP_USING_UART4)
{
    HPM_UART4,
    IRQn_UART4,
    &serial4,
    "uart4",
},
#endif

#if defined(BSP_USING_UART5)
{
    HPM_UART5,
    IRQn_UART5,
    &serial5,
    "uart5",
},
#endif

#if defined(BSP_USING_UART6)
{
    HPM_UART6,
    IRQn_UART6,
    &serial6,
    "uart6",
},
#endif

#if defined(BSP_USING_UART7)
{
    HPM_UART7,
    IRQn_UART7,
    &serial7,
    "uart7",
},
#endif

#if defined(BSP_USING_UART8)
{
    HPM_UART8,
    IRQn_UART8,
    &serial8,
    "uart8",
},
#endif

#if defined(BSP_USING_UART9)
{
    HPM_UART9,
    IRQn_UART9,
    &serial9,
    "uart9",
},
#endif

#if defined(BSP_USING_UART10)
{
    HPM_UART10,
    IRQn_UART10,
    &serial10,
    "uart10",
},
#endif

#if defined(BSP_USING_UART11)
{
    HPM_UART11,
    IRQn_UART11,
    &serial11,
    "uart11",
},
#endif

#if defined(BSP_USING_UART12)
{
    HPM_UART12,
    IRQn_UART12,
    &serial12,
    "uart12",
},
#endif

#if defined(BSP_USING_UART13)
{
    HPM_UART13,
    IRQn_UART13,
    &serial13,
    "uart13",
},
#endif

#if defined(BSP_USING_UART14)
{
    HPM_UART14,
    IRQn_UART14,
    &serial14,
    "uart14",
},
#endif

#if defined(BSP_USING_UART15)
{
    HPM_UART15,
    IRQn_UART15,
    &serial15,
    "uart15",
},
#endif

};

/**
 * @brief UART common interrupt process. This
 *
 * @param serial Serial device
 */
static void hpm_uart_isr(struct rt_serial_device *serial)
{
    struct hpm_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct hpm_uart *)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    /* enter interrupt */
    rt_interrupt_enter();

    /* UART in mode Receiver */
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);

    /* leave interrupt */
    rt_interrupt_leave();
}


static rt_err_t hpm_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart_config_t uart_config;
    struct hpm_uart *uart  = (struct hpm_uart *)serial->parent.user_data;

    init_uart_pins(uart->uart_base);
    uart_default_config(uart->uart_base, &uart_config);

    uart_config.src_freq_in_hz = board_init_uart_clock(uart->uart_base);
    uart_config.baudrate = cfg->baud_rate;
    uart_config.num_of_stop_bits = cfg->stop_bits;
    uart_config.parity = cfg->parity;

    uart_config.word_length = cfg->data_bits - DATA_BITS_5;

    board_init_uart(uart->uart_base);
    uart_init(uart->uart_base, &uart_config);

    hpm_uart_control(serial, RT_DEVICE_CTRL_SET_INT, NULL);
}


static rt_err_t hpm_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    RT_ASSERT(serial != RT_NULL);

    struct hpm_uart *uart = (struct hpm_uart *)serial->parent.user_data;

    switch (cmd) {
        case RT_DEVICE_CTRL_CLR_INT:
            /* disable rx irq */
            uart_disable_irq(uart->uart_base, uart_intr_rx_data_avail_or_timeout);
            intc_m_disable_irq(uart->irq_num);
            break;

        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */
            uart_enable_irq(uart->uart_base, uart_intr_rx_data_avail_or_timeout);
            intc_m_enable_irq_with_priority(uart->irq_num, 1);
            break;
    }

    return RT_EOK;
}


static int hpm_uart_putc(struct rt_serial_device *serial, char ch)
{
    struct hpm_uart *uart  = (struct hpm_uart *)serial->parent.user_data;
    uart_write_byte(uart->uart_base, ch);
    while(!uart_check_status(uart->uart_base, uart_stat_transmitter_empty)) {
    }
}

static int hpm_uart_getc(struct rt_serial_device *serial)
{
    int result = -1;
    struct hpm_uart *uart  = (struct hpm_uart *)serial->parent.user_data;

    if (uart_check_status(uart->uart_base, uart_stat_data_ready)) {
        uart_receive_byte(uart->uart_base, (uint8_t*)&result);
    }

    return result;
}


static const struct rt_uart_ops hpm_uart_ops = {
    hpm_uart_configure,
    hpm_uart_control,
    hpm_uart_putc,
    hpm_uart_getc,
};



int rt_hw_uart_init(void)
{

    /* Added bypass logic here since the rt_hw_uart_init function will be initialized twice, the 2nd initialization should be bypassed */
    static bool initialized;
    rt_err_t err = RT_EOK;
    if (initialized)
    {
        return err;
    }
    else
    {
        initialized = true;
    }
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    for (uint32_t i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++) {
        uarts[i].serial->ops = &hpm_uart_ops;
        uarts[i].serial->config = config;

        /* register UART deivce */
        err = rt_hw_serial_register(uarts[i].serial,
                            uarts[i].device_name,
                            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                            (void*)&uarts[i]);
    }

    return err;
}

INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* RT_USING_SERIAL */
