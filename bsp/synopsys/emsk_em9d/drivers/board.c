/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>

#include <rtdevice.h>
#include <drivers/serial.h>

#include "board.h"
#include "inc/arc/arc_timer.h"
#include "inc/arc/arc_exception.h"

#include "inc/embARC_error.h"
#include "mux.h"
#include "dw_uart_obj.h"


static void rt_hw_timer_isr(int vector, void *param)
{
    arc_timer_int_clear(BOARD_OS_TIMER_ID);
    rt_tick_increase();
}

static void emsk_mux_init(void)
{
    MUX_REG *mux_regs;

    mux_regs = (MUX_REG *)(PERIPHERAL_BASE|REL_REGBASE_PINMUX);
    mux_init(mux_regs);

    /**
     * + Please refer to corresponding EMSK User Guide for detailed information
     *   -> Appendix: A  Hardware Functional Description
     *      -> Pmods Configuration summary
     * + Set up pin-multiplexer of all PMOD connections
     *   - PM1 J1: Upper row as UART 0, lower row as SPI Slave
     *   - PM2 J2: IIC 0 and run/halt signals
     *   - PM3 J3: GPIO Port A and Port C
     *   - PM4 J4: IIC 1 and Port D
     *   - PM5 J5: Upper row as SPI Master, lower row as Port A
     *   - PM6 J6: Upper row as SPI Master, lower row as Port A
     */
    set_pmod_mux(mux_regs, PM1_UR_UART_0 | PM1_LR_SPI_S \
                | PM2_I2C_HRI           \
                | PM3_GPIO_AC           \
                | PM4_I2C_GPIO_D        \
                | PM5_UR_SPI_M1 | PM5_LR_GPIO_A \
                | PM6_UR_SPI_M0 | PM6_LR_GPIO_A );

    /**
     * PM1 upper row as UART
     * UM4:RXD, UM3:TXD
     * UM2:RTS_N, UM1:CTS_N
     */
    set_uart_map(mux_regs, 0xe4);
}

static struct rt_serial_device _emsk_uart0;  //abstracted serial for RTT
static struct rt_serial_device _emsk_uart1;

static rt_err_t _configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    DEV_UART_PTR uart;
    unsigned int id;
    int ret;

    id = (unsigned int)(serial->parent.user_data);

    uart = uart_get_dev(id);

    ret = uart->uart_control(UART_CMD_SET_BAUD, (void *)(cfg->baud_rate));

    if (ret != E_OK) {
        return RT_ERROR;
    }


    return RT_EOK;
}

static rt_err_t _control(struct rt_serial_device *serial, int cmd, void *arg)
{
    DEV_UART_PTR uart;
    unsigned int id;

    id = (unsigned int)(serial->parent.user_data);
    uart = uart_get_dev(id);

    switch (cmd) {
        case RT_DEVICE_CTRL_CLR_INT:
            uart->uart_control(UART_CMD_SET_RXINT, (void *)0);
            break;
        case RT_DEVICE_CTRL_SET_INT:
            uart->uart_control(UART_CMD_SET_RXINT, (void *)1);
            break;
        case RT_DEVICE_CTRL_SUSPEND:
            uart->uart_control(UART_CMD_DIS_DEV, (void *)0);
            break;
        case RT_DEVICE_CTRL_RESUME:
            uart->uart_control(UART_CMD_ENA_DEV, (void *)0);
            break;

        default:
            return  RT_ERROR;
            break;
    }

    return RT_EOK;
}

static int _putc(struct rt_serial_device *serial, char c)
{
    DEV_UART_PTR uart;
    unsigned int id;
    int ret;

    id = (unsigned int)(serial->parent.user_data);

    uart = uart_get_dev(id);

    ret = uart->uart_write(&c, 1);

    if (ret < 0) {
        return -1;
    } else {
        return 1;
    }
}

static int _getc(struct rt_serial_device *serial)
{
    DEV_UART_PTR uart;
    unsigned int id;
    unsigned int data;
    int ret;
    int rd_avail = 0;

    id = (unsigned int)(serial->parent.user_data);
    uart = uart_get_dev(id);

    uart->uart_control(UART_CMD_GET_RXAVAIL, (void *)(&rd_avail));

    if (rd_avail > 0) {
        ret = uart->uart_read(&data, 1);
    } else {
        return -1;
    }

    if (ret < 0) {
        return -1;
    } else {
        return data;
    }

}

static void _emsk_uart0_isr(void *ptr)
{
    rt_hw_serial_isr((struct rt_serial_device*)&_emsk_uart0, RT_SERIAL_EVENT_RX_IND);
}

static const struct rt_uart_ops _emsk_uart0_ops =
{
    _configure,
    _control,
    _putc,
    _getc,
};

static void _emsk_uart1_isr(void *ptr)
{
    rt_hw_serial_isr((struct rt_serial_device*)&_emsk_uart1, RT_SERIAL_EVENT_RX_IND);
}

static const struct rt_uart_ops _emsk_uart1_ops =
{
    _configure,
    _control,
    _putc,
    _getc,
};

int rt_hw_uart_init(void)
{
    DEV_UART_PTR uart;
    struct serial_configure config;
    int ret;

    config.baud_rate = BAUD_RATE_115200;
    config.bit_order = BIT_ORDER_LSB;
    config.data_bits = DATA_BITS_8;
    config.parity    = PARITY_NONE;
    config.stop_bits = STOP_BITS_1;
    config.invert    = NRZ_NORMAL;
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    _emsk_uart0.ops    = &_emsk_uart0_ops;
    _emsk_uart0.config = config;

    _emsk_uart1.ops    = &_emsk_uart1_ops;
    _emsk_uart1.config = config;

    /* open UART1 for USB-UART interface */
    uart = uart_get_dev(DW_UART_1_ID);
    /* default format: 8bits, no parity, 1 stop bits */
    ret = uart->uart_open(config.baud_rate);

    if (ret != E_OPNED && ret != E_OK) {
        return RT_ERROR;
    }

    /* enable rx int */
    uart->uart_control(UART_CMD_SET_RXINT, (void *)1);
    /* use customized int isr */
    uart->uart_control(UART_CMD_SET_RXCB, _emsk_uart1_isr);
    uart->uart_control(UART_CMD_SET_RXINT_BUF, NULL);

    rt_hw_serial_register(&_emsk_uart1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          (void *)DW_UART_1_ID);

     /* open UART0 in PMOD A*/
    uart = uart_get_dev(DW_UART_0_ID);
    /* default format: 8bits, no parity, 1 stop bits */
    ret = uart->uart_open(config.baud_rate);

    if (ret != E_OPNED && ret != E_OK) {
        return RT_ERROR;
    }

    /* enable rx int */
    uart->uart_control(UART_CMD_SET_RXINT, (void *)1);
    /* use customized int isr */
    uart->uart_control(UART_CMD_SET_RXCB, _emsk_uart0_isr);
    uart->uart_control(UART_CMD_SET_RXINT_BUF, NULL);

    rt_hw_serial_register(&_emsk_uart0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          (void *)DW_UART_0_ID);

    return RT_EOK;
}

void rt_hw_console_output(const char *str)
{
    while(*str != '\0')
    {
        if (*str == '\n') {
            _putc(&_emsk_uart1,'\r');
        }
        _putc(&_emsk_uart1,*str);
        str++;
    }
}

int rt_hw_timer_init(void)
{

    unsigned int cyc = BOARD_CPU_CLOCK / RT_TICK_PER_SECOND;

    int_disable(BOARD_OS_TIMER_INTNO); /* disable os timer interrupt */
    arc_timer_stop(BOARD_OS_TIMER_ID);
    arc_timer_start(BOARD_OS_TIMER_ID, TIMER_CTRL_IE | TIMER_CTRL_NH, cyc);

    int_handler_install(BOARD_OS_TIMER_INTNO, (INT_HANDLER)rt_hw_timer_isr);
    int_enable(BOARD_OS_TIMER_INTNO);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

void rt_hw_board_init()
{
    emsk_mux_init();

    rt_hw_uart_init();
    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}
