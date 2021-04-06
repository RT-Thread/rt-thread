/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
    /* this driver can be disabled at menuconfig → RT-Thread Components → Device Drivers */
#endif

struct at32_usart {
    char *name;
    USART_Type* usartx;
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

static struct at32_usart usart_config[] = {
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

static rt_err_t at32_configure(struct rt_serial_device *serial,
        struct serial_configure *cfg) {
    struct at32_usart *usart_instance = (struct at32_usart *) serial->parent.user_data;
    USART_InitType USART_InitStructure;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    RT_ASSERT(usart_instance != RT_NULL);

    at32_msp_usart_init((void *)usart_instance->usartx);

    USART_StructInit(&USART_InitStructure);

    USART_Reset(usart_instance->usartx);
    USART_InitStructure.USART_BaudRate = cfg->baud_rate;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    switch (cfg->data_bits) {
    case DATA_BITS_8:
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        break;

    case DATA_BITS_9:
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;
        break;
    default:
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        break;
    }

    switch (cfg->stop_bits) {
    case STOP_BITS_1:
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        break;
    case STOP_BITS_2:
        USART_InitStructure.USART_StopBits = USART_StopBits_2;
        break;
    default:
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        break;
    }

    switch (cfg->parity) {
    case PARITY_NONE:
        USART_InitStructure.USART_Parity = USART_Parity_No;
        break;
    case PARITY_ODD:
        USART_InitStructure.USART_Parity = USART_Parity_Odd;
        break;
    case PARITY_EVEN:
        USART_InitStructure.USART_Parity = USART_Parity_Even;
        break;
    default:
        USART_InitStructure.USART_Parity = USART_Parity_No;
        break;
    }
    USART_Init(usart_instance->usartx, &USART_InitStructure);
    USART_Cmd(usart_instance->usartx, ENABLE);

    return RT_EOK;
}

static rt_err_t at32_control(struct rt_serial_device *serial, int cmd,
        void *arg) {
    struct at32_usart *usart;

    NVIC_InitType NVIC_InitStruct;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    NVIC_InitStruct.NVIC_IRQChannel = usart->irqn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;

    switch (cmd) {
    case RT_DEVICE_CTRL_CLR_INT:
        NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&NVIC_InitStruct);
        USART_INTConfig(usart->usartx, USART_INT_RDNE, DISABLE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStruct);
        USART_INTConfig(usart->usartx, USART_INT_RDNE, ENABLE);
        break;
    }

    return RT_EOK;
}

static int at32_putc(struct rt_serial_device *serial, char ch) {
    struct at32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    USART_SendData(usart->usartx, (uint8_t) ch);
    while (USART_GetFlagStatus(usart->usartx, USART_FLAG_TDE) == RESET);

    return 1;
}

static int at32_getc(struct rt_serial_device *serial) {
    int ch;
    struct at32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    ch = -1;
    if (RESET != USART_GetFlagStatus(usart->usartx, USART_FLAG_RDNE)) {
        ch = USART_ReceiveData(usart->usartx) & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops at32_usart_ops = {
        at32_configure,
        at32_control,
        at32_putc,
        at32_getc,
        RT_NULL };

static void usart_isr(struct rt_serial_device *serial) {
    struct at32_usart *usart_instance;

    RT_ASSERT(serial != RT_NULL);

    usart_instance = (struct at32_usart *) serial->parent.user_data;
    RT_ASSERT(usart_instance != RT_NULL);

    if ((USART_GetITStatus(usart_instance->usartx, USART_INT_RDNE) != RESET) \
        && (RESET != USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_RDNE))) {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        USART_ClearITPendingBit(usart_instance->usartx, USART_INT_RDNE);
        USART_ClearFlag(usart_instance->usartx, USART_FLAG_RDNE);
    } else {
        if (USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_CTSF) != RESET) {
            USART_ClearFlag(usart_instance->usartx, USART_FLAG_CTSF);
        }

        if (USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_LBDF) != RESET) {
            USART_ClearFlag(usart_instance->usartx, USART_FLAG_LBDF);
        }

        if (USART_GetFlagStatus(usart_instance->usartx, USART_FLAG_TRAC) != RESET) {
            USART_ClearFlag(usart_instance->usartx, USART_FLAG_TRAC);
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

    obj_num = sizeof(usart_config) / sizeof(struct at32_usart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++) {
        usart_config[index].serial.ops = &at32_usart_ops;
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
