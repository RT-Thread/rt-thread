/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-29     Rbb666       first version
 */

#include <rtthread.h>
#include "drv_uart.h"

#include "cy_retarget_io.h"
#include "cyhal_scb_common.h"

struct ifx_usart
{
    char *name;
    CySCB_Type *usart_x;
    IRQn_Type intrSrc;
    struct rt_serial_device serial;
};

enum
{
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
};

#ifdef BSP_USING_UART1
/* UART1 device driver structure */
const cy_stc_sysint_t UART1_SCB_IRQ_cfg =
{
    .intrSrc = scb_5_interrupt_IRQn,
    .intrPriority = 7u,
};
#endif

static struct ifx_usart usart_config[] =
{
#ifdef BSP_USING_UART1
    {
        "uart1",
        SCB5,
        scb_5_interrupt_IRQn,
    },
#endif
};

static void usart_isr(struct rt_serial_device *serial)
{
    RT_ASSERT(serial != RT_NULL);

#ifdef BSP_USING_UART1
    if ((SCB5->INTR_RX_MASKED & SCB_INTR_RX_MASKED_NOT_EMPTY_Msk) != 0)
    {
        /* Clear UART "RX fifo not empty interrupt" */
        SCB5->INTR_RX = SCB5->INTR_RX & SCB_INTR_RX_NOT_EMPTY_Msk;

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
#endif
}

#ifdef BSP_USING_UART1
/* UART0 Interrupt Hanlder */
void uart1_isr_callback(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&usart_config[UART1_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

/*
 * UARTHS interface
 */
static rt_err_t ifx_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct ifx_usart *usart_instance = (struct ifx_usart *) serial->parent.user_data;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(usart_instance != RT_NULL);

    cy_en_scb_uart_status_t result;

    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                                 CY_RETARGET_IO_BAUDRATE);

    /* retarget-io init failed. Stop program execution */
    RT_ASSERT(result != RT_ERROR);

    return RT_EOK;
}

static rt_err_t ifx_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    RT_ASSERT(serial != RT_NULL);
    struct ifx_usart *usart = (struct ifx_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:

        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* Unmasking only the RX fifo not empty interrupt bit */
        usart->usart_x->INTR_RX_MASK = SCB_INTR_RX_MASK_NOT_EMPTY_Msk;

#ifdef BSP_USING_UART1
        /* Interrupt Settings for UART */
        Cy_SysInt_Init(&UART1_SCB_IRQ_cfg, uart1_isr_callback);
#endif

        /* Enable the interrupt */
        NVIC_EnableIRQ(usart->intrSrc);
        break;
    }

    return (RT_EOK);
}

static int ifx_uarths_putc(struct rt_serial_device *serial, char c)
{
    RT_ASSERT(serial != RT_NULL);

    struct ifx_usart *usart = (struct ifx_usart *) serial->parent.user_data;

    RT_ASSERT(usart != RT_NULL);

    if (_cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    uint32_t count = 0;
    while (count == 0)
    {
        count = Cy_SCB_UART_Put(usart->usart_x, c);
    }

    return (1);
}

static int ifx_uarths_getc(struct rt_serial_device *serial)
{
    int ch;
    rt_uint8_t read_data;
    RT_ASSERT(serial != RT_NULL);

    ch = -1;
    if (RT_EOK == cyhal_uart_getc(&cy_retarget_io_uart_obj, (uint8_t *)&read_data, 1))
    {
        ch = read_data & 0xff;
    }
    else
    {
        ch = -1;
    }

    return ch;
}

const struct rt_uart_ops _uart_ops =
{
    ifx_configure,
    ifx_control,
    ifx_uarths_putc,
    ifx_uarths_getc,
    RT_NULL
};

void rt_hw_uart_init(void)
{
    int index;
    rt_size_t obj_num;

    obj_num = sizeof(usart_config) / sizeof(struct ifx_usart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++)
    {
        usart_config[index].serial.ops = &_uart_ops;
        usart_config[index].serial.config = config;

        /* register uart device */
        result = rt_hw_serial_register(&usart_config[index].serial,
                                       usart_config[index].name,
                                       RT_DEVICE_FLAG_RDWR |
                                       RT_DEVICE_FLAG_INT_RX,
                                       &usart_config[index]);

        RT_ASSERT(result == RT_EOK);
    }
}
