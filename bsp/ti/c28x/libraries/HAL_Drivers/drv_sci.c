/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-02-02     xuzhuoyi     first version
 */

#include "rtdevice.h"
#include "board.h"
#include "drv_sci.h"
#include "F2837xD_device.h"
#include "F2837xD_sci.h"

//typedef long off_t;
#include "F2837xD_sci_io.h"

#ifdef RT_USING_SERIAL

#define LOG_TAG             "drv.sci"

/* c28x uart driver class */
struct c28x_uart
{
    const char *name;
    volatile struct SCI_REGS *sci_regs;
    struct rt_serial_device serial;
};

static struct c28x_uart uart_obj[3] = {0};

static rt_err_t c28x_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct c28x_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct c28x_uart *)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    EALLOW;

    // default config

    // 1 stop bit,  No loopback
    // No parity,8 char bits,
    // async mode, idle-line protocol
    uart->sci_regs->SCICCR.all = 0x0007;

    // enable TX, RX, internal SCICLK,
    // Disable RX ERR, SLEEP, TXWAKE
    uart->sci_regs->SCICTL1.all = 0x0003;

    uart->sci_regs->SCICTL2.bit.TXINTENA = 1;
    uart->sci_regs->SCICTL2.bit.RXBKINTENA = 1;

    uart->sci_regs->SCIHBAUD.all = 0x0000;  // 115200 baud @LSPCLK = 22.5MHz (90 MHz SYSCLK).
    uart->sci_regs->SCILBAUD.all = 53;

    uart->sci_regs->SCICTL1.all = 0x0023;  // Relinquish SCI from Reset

    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        uart->sci_regs->SCICCR.bit.SCICHAR = 4;
        break;
    case DATA_BITS_6:
        uart->sci_regs->SCICCR.bit.SCICHAR = 5;
        break;
    case DATA_BITS_7:
        uart->sci_regs->SCICCR.bit.SCICHAR = 6;
        break;
    case DATA_BITS_8:
        uart->sci_regs->SCICCR.bit.SCICHAR = 7;
        break;
    default:
        uart->sci_regs->SCICCR.bit.SCICHAR = 7;
        break;
    }
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart->sci_regs->SCICCR.bit.STOPBITS = 0;
        break;
    case STOP_BITS_2:
        uart->sci_regs->SCICCR.bit.STOPBITS = 1;
        break;
    default:
        uart->sci_regs->SCICCR.bit.STOPBITS = 0;
        break;
    }
    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart->sci_regs->SCICCR.bit.PARITYENA = 0;
        break;
    case PARITY_ODD:
        uart->sci_regs->SCICCR.bit.PARITYENA = 1;
        uart->sci_regs->SCICCR.bit.PARITY = 0;
        break;
    case PARITY_EVEN:
        uart->sci_regs->SCICCR.bit.PARITYENA = 1;
        uart->sci_regs->SCICCR.bit.PARITY = 1;
        break;
    default:
        uart->sci_regs->SCICCR.bit.PARITYENA = 0;
        break;
    }

    EDIS;

    return RT_EOK;
}

static rt_err_t c28x_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct c28x_uart *uart;
    uart = (struct c28x_uart *)serial->parent.user_data;

    EALLOW;

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable interrupt */
        uart->sci_regs->SCICTL2.bit.TXINTENA = 0;
        uart->sci_regs->SCICTL2.bit.RXBKINTENA = 0;
        break;
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable interrupt */
        uart->sci_regs->SCICTL2.bit.TXINTENA = 1;
        uart->sci_regs->SCICTL2.bit.RXBKINTENA = 1;
        break;
    }
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
    if(SCI_read(0, &ch, 1))
        return ch;
    else
        return -1;
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial) {
    struct c28x_uart *uart = (struct c28x_uart *) serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;   // Clear Interrupt flag
    PieCtrlRegs.PIEACK.all |= 0x100;       // Issue PIE ack
}

static const struct rt_uart_ops c28x_uart_ops =
{
    .configure = c28x_configure,
    .control = c28x_control,
    .putc = c28x_putc,
    .getc = c28x_getc,
};

//
// sciaRxFifoIsr - SCIA Receive FIFO ISR
//
interrupt void sciaRxFifoIsr(void)
{
    ALLOW_ISR_PREEMPT();

    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart_obj[0].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

int rt_hw_sci_init(void)
{
    EALLOW;

    GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 3;
    GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 3;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO42 = 3;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO43 = 3;

    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;
    GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 0;
    GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 0;

    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 2;
    GpioCtrlRegs.GPEMUX1.bit.GPIO139 = 2;
    GpioCtrlRegs.GPBGMUX2.bit.GPIO56 = 1;
    GpioCtrlRegs.GPEGMUX1.bit.GPIO139 = 1;

    CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
    CpuSysRegs.PCLKCR7.bit.SCI_B = 1;
    CpuSysRegs.PCLKCR7.bit.SCI_C = 1;

    PieVectTable.SCIA_RX_INT = &sciaRxFifoIsr;

    EDIS;

    //
    // Enable interrupts required for this example
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;   // PIE Group 9, INT1
    IER |= 0x100;                        // Enable CPU INT

    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    uart_obj[0].serial.ops    = &c28x_uart_ops;
    uart_obj[0].serial.config = config;
    uart_obj[0].name          = "scia";
    uart_obj[0].sci_regs      = &SciaRegs;

    uart_obj[1].serial.ops    = &c28x_uart_ops;
    uart_obj[1].serial.config = config;
    uart_obj[1].name          = "scib";
    uart_obj[1].sci_regs      = &ScibRegs;

    uart_obj[2].serial.ops    = &c28x_uart_ops;
    uart_obj[2].serial.config = config;
    uart_obj[2].name          = "scic";
    uart_obj[2].sci_regs      = &ScicRegs;

    /* register UART device */
    result = rt_hw_serial_register(&uart_obj[0].serial, uart_obj[0].name,
                                   RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                   &uart_obj[0]);

    /* register UART device */
    result = rt_hw_serial_register(&uart_obj[1].serial, uart_obj[1].name,
                                   RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                   &uart_obj[1]);

    /* register UART device */
    result = rt_hw_serial_register(&uart_obj[2].serial, uart_obj[2].name,
                                   RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                   &uart_obj[2]);

    return result;
}

#endif /* RT_USING_SERIAL */
