/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-11     supperthomas first version
 *
 */


#include "board.h"
#include "uart.h"
#include "rtdevice.h"
#ifdef RT_USING_SERIAL

//#define DRV_DEBUG
//#define LOG_TAG             "drv.usart"
//#include <drv_log.h>

#define UART0_CONFIG                                                \
    {                                                               \
        .name = "uart0",                                            \
        .Instance = MXC_UART_GET_UART(0),                           \
        .irq_type = MXC_UART_GET_IRQ(0),                            \
    }

#define UART1_CONFIG                                                \
    {                                                               \
        .name = "uart1",                                            \
        .Instance = MXC_UART_GET_UART(1),                           \
        .irq_type = MXC_UART_GET_IRQ(1),                            \
    }

struct mcu_uart_config
{
    const char *name;
    mxc_uart_regs_t *Instance;
    IRQn_Type irq_type;
};

struct mcu_uart
{
    mxc_uart_regs_t *handle;
    struct mcu_uart_config *config;

    rt_uint16_t uart_dma_flag;
    struct rt_serial_device serial;
};




#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1)

#error "Please define at least one BSP_USING_UARTx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

enum
{
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif

};

static struct mcu_uart_config uart_config[] =
{
#ifdef BSP_USING_UART0
    UART0_CONFIG,
#endif
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
};

static struct mcu_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

#ifdef BSP_USING_UART1
void UART1_IRQHandler(void)
{
    rt_interrupt_enter();

    rt_hw_serial_isr(&(uart_obj[UART1_INDEX].serial), RT_SERIAL_EVENT_RX_IND);

    uint32_t  intst = 0;
    intst = MXC_UART1->int_fl;
    MXC_UART1->int_fl = intst;

    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_UART0
void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_serial_isr(&(uart_obj[UART0_INDEX].serial), RT_SERIAL_EVENT_RX_IND);
    /* clear flags */

    uint32_t  intst = 0;
    intst = MXC_UART0->int_fl;
    MXC_UART0->int_fl = intst;

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif


static rt_err_t mcu_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    int error;
    struct mcu_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    const sys_cfg_uart_t sys_uart_cfg =
    {
        MAP_A,
        UART_FLOW_DISABLE,
    };
    uart = rt_container_of(serial, struct mcu_uart, serial);
    uart_cfg_t mcu_cfg;
    uart->handle = uart->config->Instance;
    mcu_cfg.baud = cfg->baud_rate;
    mcu_cfg.stop = UART_STOP_1;
    mcu_cfg.parity = UART_PARITY_DISABLE;
    mcu_cfg.size = UART_DATA_SIZE_8_BITS;
    mcu_cfg.flow = UART_FLOW_CTRL_EN;
    mcu_cfg.pol = UART_FLOW_POL_EN;

    error = UART_Init(uart->handle, &mcu_cfg, &sys_uart_cfg);
    if (error != E_NO_ERROR)
    {
        rt_kprintf("Error initializing UART %d\n", error);
        while (1) {}
    }
    return RT_EOK;
}

static rt_err_t mcu_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct mcu_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct mcu_uart, serial);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_ClearPendingIRQ(uart->config->irq_type);
        NVIC_DisableIRQ(uart->config->irq_type);
        /* disable interrupt */
        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_SetPriority(uart->config->irq_type, 1);
        NVIC_EnableIRQ(uart->config->irq_type);
        /* enable interrupt */
        uart->handle->ctrl |=  0x05 << MXC_F_UART_CTRL_RX_TO_POS;
        uart->handle->int_en |= MXC_F_UART_INT_EN_RX_FIFO_THRESH | \
                                MXC_F_UART_INT_EN_RX_TIMEOUT;

        uart->handle->int_en |= MXC_F_UART_INT_EN_RX_FRAME_ERROR | \
                                MXC_F_UART_INT_EN_RX_PARITY_ERROR | \
                                MXC_F_UART_INT_EN_RX_OVERRUN ;

        uart->handle->thresh_ctrl = MXC_UART_FIFO_DEPTH <<
                                    MXC_F_UART_THRESH_CTRL_RX_FIFO_THRESH_POS;
        break;

    case RT_DEVICE_CTRL_CLOSE:
        UART_Shutdown(uart->handle);
        break;

    }
    return RT_EOK;
}

static int mcu_putc(struct rt_serial_device *serial, char c)
{
    struct mcu_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct mcu_uart, serial);
    UART_WriteByte(uart->handle, c);
    return 1;
}

static int mcu_getc(struct rt_serial_device *serial)
{
    int ch;
    struct mcu_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct mcu_uart, serial);

    ch = -1;

    if (UART_NumReadAvail(uart->handle))
    {
        ch = UART_ReadByte(uart->handle);
    }

    return ch;
}

static const struct rt_uart_ops mcu_uart_ops =
{
    .configure = mcu_configure,
    .control = mcu_control,
    .putc = mcu_putc,
    .getc = mcu_getc,
};

int rt_hw_usart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct mcu_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].serial.ops    = &mcu_uart_ops;
        uart_obj[i].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
                                       , RT_NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}
//INIT_BOARD_EXPORT(rt_hw_usart_init);
#endif /* RT_USING_SERIAL */
