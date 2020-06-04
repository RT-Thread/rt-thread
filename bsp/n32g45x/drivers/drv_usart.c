/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-06     shelton      first version
 */

#include <board.h>
#include "drv_usart.h"

#ifdef RT_USING_SERIAL
#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && \
    !defined(BSP_USING_UART3)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig ¡ú RT-Thread Components ¡ú Device Drivers */
#endif

struct n32_usart {
    char *name;
    USART_Module* usartx;
    IRQn_Type irqn;
    struct rt_serial_device serial;
};

enum {
#ifdef BSP_USING_UART1
    USART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    USART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    USART3_INDEX,
#endif
};

static struct n32_usart usart_config[] = {
#ifdef BSP_USING_UART1
        { "uart1",
        USART1,
        USART1_IRQn, },
#endif
#ifdef BSP_USING_UART2
        { "uart2",
        USART2,
        USART2_IRQn, },
#endif
#ifdef BSP_USING_UART3
        { "uart3",
        USART3,
        USART3_IRQn, },
#endif
};

static rt_err_t n32_configure(struct rt_serial_device *serial,
        struct serial_configure *cfg) {
    struct n32_usart *usart_instance = (struct n32_usart *) serial->parent.user_data;
    USART_InitType USART_InitStructure;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    RT_ASSERT(usart_instance != RT_NULL);

    n32_msp_usart_init((void *)usart_instance->usartx);

    USART_StructInit(&USART_InitStructure);

    USART_DeInit(usart_instance->usartx);
    USART_InitStructure.BaudRate = cfg->baud_rate;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;;
    USART_InitStructure.Mode  = USART_MODE_RX | USART_MODE_TX;

    switch (cfg->data_bits) {
    case DATA_BITS_8:
        USART_InitStructure.WordLength = USART_WL_8B;
        break;

    case DATA_BITS_9:
        USART_InitStructure.WordLength = USART_WL_9B;
        break;
    default:
        USART_InitStructure.WordLength = USART_WL_8B;
        break;
    }

    switch (cfg->stop_bits) {
    case STOP_BITS_1:
        USART_InitStructure.StopBits = USART_STPB_1;
        break;
    case STOP_BITS_2:
        USART_InitStructure.StopBits = USART_STPB_2;
        break;
    default:
        USART_InitStructure.StopBits = USART_STPB_1;
        break;
    }

    switch (cfg->parity) {
    case PARITY_NONE:
        USART_InitStructure.Parity = USART_PE_NO;
        break;
    case PARITY_ODD:
        USART_InitStructure.Parity = USART_PE_ODD;
        break;
    case PARITY_EVEN:
        USART_InitStructure.Parity = USART_PE_EVEN;
        break;
    default:
        USART_InitStructure.Parity = USART_PE_NO;
        break;
    }
    USART_Init(usart_instance->usartx, &USART_InitStructure);
    USART_Enable(usart_instance->usartx, ENABLE);

    return RT_EOK;
}

static rt_err_t n32_control(struct rt_serial_device *serial, int cmd,
        void *arg) {
    struct n32_usart *usart;

    NVIC_InitType NVIC_InitStruct;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct n32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    NVIC_InitStruct.NVIC_IRQChannel = usart->irqn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;

    switch (cmd) {
    case RT_DEVICE_CTRL_CLR_INT:
        NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&NVIC_InitStruct);
        USART_ConfigInt(usart->usartx, USART_INT_RXDNE, DISABLE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStruct);
        USART_ConfigInt(usart->usartx, USART_INT_RXDNE, ENABLE);
        break;
    }

    return RT_EOK;
}

static int n32_putc(struct rt_serial_device *serial, char ch) {
    struct n32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct n32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    USART_SendData(usart->usartx, (uint8_t) ch);
    while (USART_GetFlagStatus(usart->usartx, USART_FLAG_TXDE) == RESET);

    return 1;
}

static int n32_getc(struct rt_serial_device *serial) {
    int ch;
    struct n32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct n32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    ch = -1;
    if (RESET != USART_GetFlagStatus(usart->usartx, USART_FLAG_RXDNE)) {
        ch = USART_ReceiveData(usart->usartx) & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops n32_usart_ops = {
        n32_configure,
        n32_control,
        n32_putc,
        n32_getc,
        RT_NULL };

static void usart_isr(struct rt_serial_device *serial) {
    struct n32_usart *usart_instance;

    RT_ASSERT(serial != RT_NULL);

    usart_instance = (struct n32_usart *) serial->parent.user_data;
    RT_ASSERT(usart_instance != RT_NULL);

    if ((USART_GetIntStatus(usart_instance->usartx, USART_INT_RXDNE) != RESET) \
        && (RESET != USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_RXDNE))) {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        USART_GetIntStatus(usart_instance->usartx, USART_INT_RXDNE);
        USART_ClrFlag(usart_instance->usartx, USART_FLAG_RXDNE);
    } else {
        if (USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_CTSF) != RESET) {
            USART_ClrFlag(usart_instance->usartx, USART_FLAG_CTSF);
        }

        if (USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_LINBD) != RESET) {
            USART_ClrFlag(usart_instance->usartx, USART_FLAG_LINBD);
        }

        if (USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_TXC) != RESET) {
            USART_ClrFlag(usart_instance->usartx, USART_FLAG_TXC);
        }
    }
}

#ifdef BSP_USING_UART1
void USART1_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[USART1_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART2
void USART2_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[USART2_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART3
void USART3_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[USART3_INDEX].serial);

    rt_interrupt_leave();
}
#endif

int rt_hw_usart_init(void) {
    rt_size_t obj_num;
    int index;

    obj_num = sizeof(usart_config) / sizeof(struct n32_usart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++) {
        usart_config[index].serial.ops = &n32_usart_ops;
        usart_config[index].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&usart_config[index].serial,
                usart_config[index].name,
                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX
                        | RT_DEVICE_FLAG_INT_TX, &usart_config[index]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_usart_init);

#endif /* BSP_USING_SERIAL */

/******************** end of file *******************/
