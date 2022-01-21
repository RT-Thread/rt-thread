/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-01-23     wangyq        the first version
 * 2019-11-01     wangyq        update libraries
 * 2021-04-20     liuhy         the second version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "es_conf_info_uart.h"

#ifdef RT_USING_SERIAL

/* es32 uart driver */
struct es32_uart
{
    uart_handle_t huart;
    IRQn_Type irq;
};

/* es32 usart driver */
struct es32_usart
{
    usart_handle_t huart;
    IRQn_Type irq;
};

#ifdef BSP_USING_UART0
/* UART0 device driver structure */
struct es32_uart uart0 =
{
    {UART0},
    UART0_IRQn
};

struct rt_serial_device serial0;

void UART0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART0->RIF & 0x01)
    {
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
/* UART1 device driver structure */
struct es32_uart uart1 =
{
    {UART1},
    UART1_IRQn
};

struct rt_serial_device serial1;

void UART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART1->RIF & 0x01)
    {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
/* UART2 device driver structure */
struct es32_uart uart2 =
{
    {UART2},
    BS16T1_UART2_IRQn
};

struct rt_serial_device serial2;

void BS16T1_UART2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART2->RIF & 0x01)
    {
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
/* UART3 device driver structure */
struct es32_uart uart3 =
{
    {UART3},
    BS16T2_UART3_IRQn
};

struct rt_serial_device serial3;

void BS16T2_UART3_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART3->RIF & 0x01)
    {
        rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_USART0
/* USART0 device driver structure */
struct es32_usart usart0 =
{
    {USART0},
    USART0_IRQn
};

struct rt_serial_device serial4;

void USART0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (USART0->STAT & USART_FLAG_RXNE)
    {
        rt_hw_serial_isr(&serial4, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_USART0 */

#ifdef BSP_USING_USART1
/* USART1 device driver structure */
struct es32_usart usart1 =
{
    {USART1},
    USART1_IRQn
};

struct rt_serial_device serial5;

void USART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (USART1->STAT & USART_FLAG_RXNE)
    {
        rt_hw_serial_isr(&serial5, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_USART1 */

static rt_err_t es32f0x_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    gpio_init_t gpio_initstructure;
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    /* Initialize tx pin */
    gpio_initstructure.mode = GPIO_MODE_OUTPUT;
    gpio_initstructure.odos = GPIO_PUSH_PULL;
    gpio_initstructure.pupd = GPIO_PUSH_UP;
    gpio_initstructure.odrv = GPIO_OUT_DRIVE_NORMAL;
    gpio_initstructure.flt  = GPIO_FILTER_DISABLE;
    gpio_initstructure.type = GPIO_TYPE_TTL;

    if((uint32_t)(uart->huart.perh) > (uint32_t)UART3)  /*根据外设物理地址区分UART和USART*/
    {
       /*USART*/
        struct es32_usart *usart= (struct es32_usart *)serial->parent.user_data;

#ifdef BSP_USING_USART0
        if(usart == (&usart0))
        {
#if  defined(ES_USART0_TX_GPIO_FUNC)&&defined(ES_USART0_TX_GPIO_PORT)&&defined(ES_USART0_TX_GPIO_PIN)
            gpio_initstructure.func = ES_USART0_TX_GPIO_FUNC;
            ald_gpio_init(ES_USART0_TX_GPIO_PORT, ES_USART0_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_USART0_RX_GPIO_FUNC)&&defined(ES_USART0_RX_GPIO_PORT)&&defined(ES_USART0_RX_GPIO_PIN)
            /* Initialize rx pin ,the same as txpin except mode */
            gpio_initstructure.mode = GPIO_MODE_INPUT;
            gpio_initstructure.func = ES_USART0_RX_GPIO_FUNC;
            ald_gpio_init(ES_USART0_RX_GPIO_PORT, ES_USART0_RX_GPIO_PIN, &gpio_initstructure);
#endif
            ald_cmu_perh_clock_config(CMU_PERH_USART0, ENABLE);
        }

#endif /* usart0 gpio init */

#ifdef BSP_USING_USART1
        if(usart == (&usart1))
        {
#if  defined(ES_USART1_TX_GPIO_FUNC)&&defined(ES_USART1_TX_GPIO_PORT)&&defined(ES_USART1_TX_GPIO_PIN)
            gpio_initstructure.func = ES_USART1_TX_GPIO_FUNC;
            ald_gpio_init(ES_USART1_TX_GPIO_PORT, ES_USART1_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_USART1_RX_GPIO_FUNC)&&defined(ES_USART1_RX_GPIO_PORT)&&defined(ES_USART1_RX_GPIO_PIN)
            /* Initialize rx pin ,the same as txpin except mode */
            gpio_initstructure.mode = GPIO_MODE_INPUT;
            gpio_initstructure.func = ES_USART1_RX_GPIO_FUNC;
            ald_gpio_init(ES_USART1_RX_GPIO_PORT, ES_USART1_RX_GPIO_PIN, &gpio_initstructure);
#endif

            ald_cmu_perh_clock_config(CMU_PERH_USART1, ENABLE);
        }
#endif /* usart1 gpio init */

        usart->huart.init.mode        = USART_MODE_TX_RX;
        usart->huart.init.baud        = cfg->baud_rate;
        usart->huart.init.word_length = (usart_word_length_t)(cfg->data_bits - 8);
        usart->huart.init.stop_bits   = ((cfg->stop_bits == STOP_BITS_1) ?  USART_STOP_BITS_1 : USART_STOP_BITS_2);
        usart->huart.init.parity = (usart_parity_t)(cfg->parity == PARITY_NONE ?  cfg->parity : (4 - cfg->parity) );
        usart->huart.init.fctl        = USART_HW_FLOW_CTL_NONE;

        ald_usart_init(&usart->huart);

       /*
        BIT_ORDER_LSB  BIT_ORDER_MSB
        NRZ_NORMAL   NRZ_INVERTED
        无相关寄存器*/

        /* enable rx int */
        ald_usart_interrupt_config(&usart->huart, USART_IT_RXNE, ENABLE);

    }
    else
    {
       /*UART*/

#ifdef BSP_USING_UART0
        if(uart == (&uart0))
        {
#if  defined(ES_UART0_TX_GPIO_FUNC)&&defined(ES_UART0_TX_GPIO_PORT)&&defined(ES_UART0_TX_GPIO_PIN)
            gpio_initstructure.func = ES_UART0_TX_GPIO_FUNC;
            ald_gpio_init(ES_UART0_TX_GPIO_PORT, ES_UART0_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART0_RX_GPIO_FUNC)&&defined(ES_UART0_RX_GPIO_PORT)&&defined(ES_UART0_RX_GPIO_PIN)
            /* Initialize rx pin ,the same as txpin except mode */
            gpio_initstructure.mode = GPIO_MODE_INPUT;
            gpio_initstructure.func = ES_UART0_RX_GPIO_FUNC;
            ald_gpio_init(ES_UART0_RX_GPIO_PORT, ES_UART0_RX_GPIO_PIN, &gpio_initstructure);
#endif
            ald_cmu_perh_clock_config(CMU_PERH_UART0, ENABLE);
        }

#endif /* uart0 gpio init */

#ifdef BSP_USING_UART1
        if(uart == (&uart1))
        {
#if  defined(ES_UART1_TX_GPIO_FUNC)&&defined(ES_UART1_TX_GPIO_PORT)&&defined(ES_UART1_TX_GPIO_PIN)
            gpio_initstructure.func = ES_UART1_TX_GPIO_FUNC;
            ald_gpio_init(ES_UART1_TX_GPIO_PORT, ES_UART1_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART1_RX_GPIO_FUNC)&&defined(ES_UART1_RX_GPIO_PORT)&&defined(ES_UART1_RX_GPIO_PIN)
            /* Initialize rx pin ,the same as txpin except mode */
            gpio_initstructure.mode = GPIO_MODE_INPUT;
            gpio_initstructure.func = ES_UART1_RX_GPIO_FUNC;
            ald_gpio_init(ES_UART1_RX_GPIO_PORT, ES_UART1_RX_GPIO_PIN, &gpio_initstructure);
#endif

            ald_cmu_perh_clock_config(CMU_PERH_UART1, ENABLE);
        }
#endif /* uart1 gpio init */

#ifdef BSP_USING_UART2
        if(uart == (&uart2))
        {
#if  defined(ES_UART2_TX_GPIO_FUNC)&&defined(ES_UART2_TX_GPIO_PORT)&&defined(ES_UART2_TX_GPIO_PIN)
            gpio_initstructure.func = ES_UART2_TX_GPIO_FUNC;
            ald_gpio_init(ES_UART2_TX_GPIO_PORT, ES_UART2_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART2_RX_GPIO_FUNC)&&defined(ES_UART2_RX_GPIO_PORT)&&defined(ES_UART2_RX_GPIO_PIN)
            /* Initialize rx pin ,the same as txpin except mode */
            gpio_initstructure.mode = GPIO_MODE_INPUT;
            gpio_initstructure.func = ES_UART2_RX_GPIO_FUNC;
            ald_gpio_init(ES_UART2_RX_GPIO_PORT, ES_UART2_RX_GPIO_PIN, &gpio_initstructure);
#endif

            ald_cmu_perh_clock_config(CMU_PERH_UART2, ENABLE);
        }
#endif /* uart2 gpio init */

#ifdef BSP_USING_UART3
        if(uart == (&uart3))
        {
#if  defined(ES_UART3_TX_GPIO_FUNC)&&defined(ES_UART3_TX_GPIO_PORT)&&defined(ES_UART3_TX_GPIO_PIN)
            gpio_initstructure.func = ES_UART3_TX_GPIO_FUNC;
            ald_gpio_init(ES_UART3_TX_GPIO_PORT, ES_UART3_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART3_RX_GPIO_FUNC)&&defined(ES_UART3_RX_GPIO_PORT)&&defined(ES_UART3_RX_GPIO_PIN)
            /* Initialize rx pin ,the same as txpin except mode */
            gpio_initstructure.mode = GPIO_MODE_INPUT;
            gpio_initstructure.func = ES_UART3_RX_GPIO_FUNC;
            ald_gpio_init(ES_UART3_RX_GPIO_PORT, ES_UART3_RX_GPIO_PIN, &gpio_initstructure);
#endif

            ald_cmu_perh_clock_config(CMU_PERH_UART3, ENABLE);
        }
#endif /* uart3 gpio init */

        uart->huart.init.mode        = UART_MODE_UART;
        uart->huart.init.baud        = cfg->baud_rate;
        uart->huart.init.word_length = (uart_word_length_t)(cfg->data_bits - 5);
        uart->huart.init.stop_bits   = (uart_stop_bits_t)cfg->stop_bits;
        uart->huart.init.parity = (uart_parity_t)(cfg->parity == PARITY_EVEN ? UART_PARITY_EVEN : cfg->parity);
        uart->huart.init.fctl        = UART_HW_FLOW_CTL_DISABLE;

        ald_uart_init(&uart->huart);

        if (cfg->bit_order == BIT_ORDER_MSB)
        {
            UART_MSB_FIRST_ENABLE(&uart->huart);
        }
        else
        {
            UART_MSB_FIRST_DISABLE(&uart->huart);
        }

        if (cfg->invert == NRZ_INVERTED)
        {
            UART_DATA_INV_ENABLE(&uart->huart);
        }
        else
        {
            UART_DATA_INV_DISABLE(&uart->huart);
        }

        /* enable rx int */
        ald_uart_interrupt_config(&uart->huart, UART_IT_RXRD, ENABLE);

    }


    return RT_EOK;
}

static rt_err_t es32f0x_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = (struct es32_uart *)serial->parent.user_data;

    if((uint32_t)(uart->huart.perh) > (uint32_t)UART3)  /*根据外设物理地址区分UART和USART*/
    {
       /*USART*/
        struct es32_usart *usart= (struct es32_usart *)serial->parent.user_data;

        switch (cmd)
        {
        case RT_DEVICE_CTRL_CLR_INT:
            /* disable rx irq */
            NVIC_DisableIRQ(usart->irq);
            /* disable interrupt */
            ald_usart_interrupt_config(&usart->huart, USART_IT_RXNE, DISABLE);
            break;

        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */
            NVIC_EnableIRQ(usart->irq);
            /* enable interrupt */
            ald_usart_interrupt_config(&usart->huart, USART_IT_RXNE, ENABLE);
            break;
        }

    }
    else
    {
       /*UART*/

        switch (cmd)
        {
        case RT_DEVICE_CTRL_CLR_INT:
            /* disable rx irq */
            NVIC_DisableIRQ(uart->irq);
            /* disable interrupt */
            ald_uart_interrupt_config(&uart->huart, UART_IT_RXRD, DISABLE);
            break;

        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */
            NVIC_EnableIRQ(uart->irq);
            /* enable interrupt */
            ald_uart_interrupt_config(&uart->huart, UART_IT_RXRD, ENABLE);
            break;
        }
    }


    return RT_EOK;
}

static int es32f0x_putc(struct rt_serial_device *serial, char c)
{
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    if((uint32_t)(uart->huart.perh) > (uint32_t)UART3)  /*根据外设物理地址区分UART和USART*/
    {
       /*USART*/
        struct es32_usart *usart= (struct es32_usart *)serial->parent.user_data;
        while (!(usart->huart.perh->STAT & USART_STAT_TXEMPIF_MSK)) ;
        WRITE_REG(usart->huart.perh->DATA, c);
    }
    else
    {
       /*UART*/
        while (!(uart->huart.perh->SR & 0x40)) ;
        WRITE_REG(uart->huart.perh->TBR, c);
    }

    return 1;
}

static int es32f0x_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct es32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    if((uint32_t)(uart->huart.perh) > (uint32_t)UART3)  /*根据外设物理地址区分UART和USART*/
    {
       /*USART*/
        struct es32_usart *usart= (struct es32_usart *)serial->parent.user_data;
        if (usart->huart.perh->STAT & USART_STAT_RXNEIF_MSK)
        {
            ch = (uint8_t)(usart->huart.perh->DATA & 0xFF);
        }
    }
    else
    {
       /*UART*/
        if (uart->huart.perh->SR & 0x01)
        {
            ch = (uint8_t)(uart->huart.perh->RBR & 0xFF);
        }
    }

    return ch;
}

static const struct rt_uart_ops es32f0x_uart_ops =
{
    es32f0x_configure,
    es32f0x_control,
    es32f0x_putc,
    es32f0x_getc,
};

int rt_hw_uart_init(void)
{
#if (defined(BSP_USING_UART0)||defined(BSP_USING_UART1)||defined(BSP_USING_UART2)||defined(BSP_USING_UART3))
    struct es32_uart *uart;
#endif
#if (defined(BSP_USING_USART0)||defined(BSP_USING_USART1))
    struct es32_usart *usart;
#endif

#ifdef BSP_USING_UART0
    uart = &uart0;
    serial0.ops = &es32f0x_uart_ops;
    serial0.config = (struct serial_configure)ES_UART0_CONFIG;

    /* register UART0 device */
    rt_hw_serial_register(&serial0, ES_DEVICE_NAME_UART0,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
    uart = &uart1;
    serial1.ops = &es32f0x_uart_ops;
    serial1.config = (struct serial_configure)ES_UART1_CONFIG;

    /* register UART1 device */
    rt_hw_serial_register(&serial1, ES_DEVICE_NAME_UART1,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    uart = &uart2;
    serial2.ops = &es32f0x_uart_ops;
    serial2.config = (struct serial_configure)ES_UART2_CONFIG;

    /* register UART2 device */
    rt_hw_serial_register(&serial2, ES_DEVICE_NAME_UART2,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
    uart = &uart3;
    serial3.ops = &es32f0x_uart_ops;
    serial3.config = (struct serial_configure)ES_UART3_CONFIG;

    /* register UART3 device */
    rt_hw_serial_register(&serial3, ES_DEVICE_NAME_UART3,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_USART0
    usart = &usart0;
    serial4.ops = &es32f0x_uart_ops;
    serial4.config = (struct serial_configure)ES_USART0_CONFIG;

    /* register USART0 device */
    rt_hw_serial_register(&serial4, ES_DEVICE_NAME_USART0,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          usart);
#endif /* BSP_USING_USART0 */

#ifdef BSP_USING_USART1
    usart = &usart1;
    serial5.ops = &es32f0x_uart_ops;
    serial5.config = (struct serial_configure)ES_USART1_CONFIG;

    /* register USART1 device */
    rt_hw_serial_register(&serial5, ES_DEVICE_NAME_USART1,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          usart);
#endif /* BSP_USING_USART1 */
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif
