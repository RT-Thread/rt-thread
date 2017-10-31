/*
 * File      : drv_uart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */


#include "drv_uart.h"
#include "fsl_lpuart.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"

static struct rt_serial_device _mimxrt105x_serial;  //abstracted serial for RTT

struct mimxrt105x_serial_device
{
    /* UART base address */
    LPUART_Type *baseAddress;

    /* UART IRQ Number */
    int irq_num;

    /* device config */
    struct serial_configure config;
};

//hardware abstract device
static struct mimxrt105x_serial_device _mimxrt105x_node =
{
    (LPUART_Type *)LPUART1,
    LPUART1_IRQn,
};

static void lpuart1_isr(struct rt_serial_device *serial);


static rt_err_t _configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    lpuart_config_t lpuartCfg;


    /* Configure LPUART Pinmux */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_LPUART1_TX, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_12_LPUART1_TX, 0x0000E039);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_LPUART1_RX, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_13_LPUART1_RX, 0x0000E039);

    /* Select 80M/4 clock as UART reference clock (20MHz) */
    uint32_t cscdr1 = CCM->CSCDR1 & (uint32_t)~(CCM_CSCDR1_UART_CLK_PODF_MASK | CCM_CSCDR1_UART_CLK_SEL_MASK);
    cscdr1 |= CCM_CSCDR1_UART_CLK_PODF(3);
    CCM->CSCDR1 = cscdr1;


    /*
     * Configure LPUART
     */
    CLOCK_EnableClock(kCLOCK_Lpuart1);
    LPUART_GetDefaultConfig(&lpuartCfg);

    lpuartCfg.baudRate_Bps = cfg->baud_rate;
    lpuartCfg.enableRx = true;
    lpuartCfg.enableTx = true;

    LPUART_Type* uart_reg = ((struct mimxrt105x_serial_device *)serial->parent.user_data)->baseAddress;

    LPUART_Init(uart_reg, &lpuartCfg, 20000000u);

    return RT_EOK;
}

static rt_err_t _control(struct rt_serial_device *serial, int cmd, void *arg)
{
    LPUART_Type *uart_reg;
    int uart_irq_num = 0;

    uart_reg = ((struct mimxrt105x_serial_device *)serial->parent.user_data)->baseAddress;
    uart_irq_num = ((struct mimxrt105x_serial_device *)serial->parent.user_data)->irq_num;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        LPUART_DisableInterrupts(uart_reg, kLPUART_RxDataRegFullInterruptEnable);
        NVIC_DisableIRQ((IRQn_Type)uart_irq_num);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        LPUART_EnableInterrupts(uart_reg, kLPUART_RxDataRegFullInterruptEnable);
        NVIC_EnableIRQ((IRQn_Type)uart_irq_num);
        break;
    case RT_DEVICE_CTRL_SUSPEND:
        /* suspend device */
        LPUART_EnableTx(uart_reg, false);
        LPUART_EnableRx(uart_reg, false);
        break;
    case RT_DEVICE_CTRL_RESUME:
        /* resume device */
        LPUART_EnableTx(uart_reg, true);
        LPUART_EnableRx(uart_reg, true);
        break;
    }

    return RT_EOK;
}

static int _putc(struct rt_serial_device *serial, char c)
{
    LPUART_Type *uart_reg;
    uart_reg = ((struct mimxrt105x_serial_device *)serial->parent.user_data)->baseAddress;

    LPUART_WriteBlocking(uart_reg, (const uint8_t*)&c, 1);

    return 1;
}

static int _getc(struct rt_serial_device *serial)
{
    LPUART_Type *uart_reg;
    uint32_t flags;
    uart_reg = ((struct mimxrt105x_serial_device *)serial->parent.user_data)->baseAddress;

    flags = LPUART_GetStatusFlags(uart_reg);
    if (flags & kLPUART_RxDataRegFullFlag)
    {
        return LPUART_ReadByte(uart_reg);
    }
    else
    {
        return -RT_ERROR;
    }
}

static const struct rt_uart_ops _mimxrt105x_ops =
{
    _configure,
    _control,
    _putc,
    _getc,
};


void UART0_RX_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_hw_serial_isr((struct rt_serial_device*)&_mimxrt105x_serial, RT_SERIAL_EVENT_RX_IND);
    rt_interrupt_leave();
}


void rt_hw_uart_init(void)
{
    struct serial_configure config;

    /* fake configuration */
    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
	config.bufsz	 = RT_SERIAL_RB_BUFSZ;

    _mimxrt105x_serial.ops    = &_mimxrt105x_ops;
    _mimxrt105x_serial.config = config;

    rt_hw_serial_register(&_mimxrt105x_serial, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          (void*)&_mimxrt105x_node);
}

void rt_hw_console_output(const char *str)
{
    while(*str != '\0')
    {
        if (*str == '\n')
            _putc(&_mimxrt105x_serial,'\r');
        _putc(&_mimxrt105x_serial,*str);
        str++;
    }
}

void lpuart1_isr(struct rt_serial_device *serial)
{
    LPUART_Type *lpuart = ((struct mimxrt105x_serial_device *)serial->parent.user_data)->baseAddress;

    if (LPUART_GetStatusFlags(lpuart) & kLPUART_RxDataRegFullFlag)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
}

void LPUART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    lpuart1_isr(&_mimxrt105x_serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
