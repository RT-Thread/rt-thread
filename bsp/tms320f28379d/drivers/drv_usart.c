/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-02-02     xuzhuoyi     first version
 */
 
#include "board.h"
#include "drv_usart.h"

#ifdef RT_USING_SERIAL

//#define DRV_DEBUG
#define LOG_TAG             "drv.sci"
//#include <drv_log.h>

static struct c28x_uart uart_obj = {0};

static rt_err_t c28x_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    EALLOW;
    CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
    SciaRegs.SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol
    SciaRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE

    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;

    SciaRegs.SCIHBAUD.all = 0x0000;  // 115200 baud @LSPCLK = 22.5MHz (90 MHz SYSCLK).
    SciaRegs.SCILBAUD.all = 53;

    SciaRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset
    EDIS;


    return RT_EOK;
}

static rt_err_t c28x_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    
    return RT_EOK;
}

static int c28x_putc(struct rt_serial_device *serial, char c)
{
    SCI_write(0, &c, 1);
    return 1;
}

static int c28x_getc(struct rt_serial_device *serial)
{
    char ch;
    SCI_read(0, &ch, 1);
    return ch;
}

static const struct rt_uart_ops c28x_uart_ops =
{
    .configure = c28x_configure,
    .control = c28x_control,
    .putc = c28x_putc,
    .getc = c28x_getc,
};

int rt_hw_usart_init(void)
{
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 3;
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 3;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO42 = 3;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO43 = 3;
    EDIS;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    uart_obj.serial.ops    = &c28x_uart_ops;
    uart_obj.serial.config = config;
    uart_obj.name          = "scia";

    /* register UART device */
    result = rt_hw_serial_register(&uart_obj.serial, uart_obj.name,
                                   RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                   &uart_obj);
    
    c28x_configure(&uart_obj.serial, &config);

    RT_ASSERT(result == RT_EOK);

    return result;
}

#endif /* RT_USING_SERIAL */
