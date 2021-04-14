/*
 * File      : uart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-27     Grissiom     port to RM48x50
 */

/* welcome, if you open this file, you may want to see uart driver code.
 * However, TI call it Serial Communication Interface(SCI) and all the low
 * level API is prefixed by "sci". To avoid messive renaming, I want to keep
 * with TI and call all the things SCI. You could safely substitude the word
 * "sci" with "uart". Enjoy. */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <reg_sci.h>

/* bring from sci.h */
enum sciIntFlags
{
    SCI_FE_INT    = 0x04000000U,  /* framing error */
    SCI_OE_INT    = 0x02000000U,  /* overrun error */
    SCI_PE_INT    = 0x01000000U,  /* parity error */
    SCI_RX_INT    = 0x00000200U,  /* receive buffer ready */
    SCI_TX_INT    = 0x00000100U,  /* transmit buffer ready */
    SCI_WAKE_INT  = 0x00000002U,  /* wakeup */
    SCI_BREAK_INT = 0x00000001U   /* break detect */
};

/* LIN1 High level interrupt. Change this if you set a different channel in
 * HALCoGen. */
#define SCI_INT_VEC 14

#define VCLK_HZ 100000000L

static rt_err_t _configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    /** - global control 1 */
    rt_uint32_t gcr1 = (1U << 25U)  /* enable transmit */
                       | (1U << 24U)  /* enable receive */
                       | (1U << 5U)   /* internal clock (device has no clock pin) */
                       | (1U << 1U);  /* asynchronous timing mode */
    if (cfg->stop_bits == STOP_BITS_2)
        gcr1 |= (1U << 4U);  /* number of stop bits */
    else if (cfg->stop_bits != STOP_BITS_1)
        return -RT_ERROR;

    if (cfg->parity == PARITY_EVEN)
    {
        gcr1 |= (1U << 3U) | (1U << 2U);
    }
    else if (cfg->parity == PARITY_ODD)
    {
        gcr1 |= (0U << 3U) | (1U << 2U);
    }

    /** - bring SCI out of reset */
    scilinREG->GCR0 = 1U;

    /** - Disable all interrupts */
    scilinREG->CLRINT    = 0xFFFFFFFFU;
    scilinREG->CLRINTLVL = 0xFFFFFFFFU;

    scilinREG->GCR1 = gcr1;

    /** - set baudrate */
    scilinREG->BRS = VCLK_HZ/16/cfg->baud_rate - 1;  /* baudrate */

    /** - transmission length */
    scilinREG->FORMAT = cfg->data_bits - 1;  /* length */

    /** - set SCI pins functional mode */
    scilinREG->FUN = (1U << 2U)  /* tx pin */
                 | (1U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI pins default output value */
    scilinREG->DOUT = (0U << 2U)  /* tx pin */
                  | (0U << 1U)  /* rx pin */
                  | (0U);  /* clk pin */

    /** - set SCI pins output direction */
    scilinREG->DIR = (0U << 2U)  /* tx pin */
                 | (0U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI pins open drain enable */
    scilinREG->ODR = (0U << 2U)  /* tx pin */
                 | (0U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI pins pullup/pulldown enable */
    scilinREG->PD = (0U << 2U)  /* tx pin */
                | (0U << 1U)  /* rx pin */
                | (0U);  /* clk pin */

    /** - set SCI pins pullup/pulldown select */
    scilinREG->PSL = (1U << 2U)  /* tx pin */
                 | (1U << 1U)  /* rx pin */
                 | (1U);  /* clk pin */

    /** - set interrupt level */
    scilinREG->SETINTLVL = (0U << 26U)  /* Framing error */
                       | (0U << 25U)  /* Overrun error */
                       | (0U << 24U)  /* Parity error */
                       | (0U << 9U)  /* Receive */
                       | (0U << 8U)  /* Transmit */
                       | (0U << 1U)  /* Wakeup */
                       | (0U);  /* Break detect */

    /** - set interrupt enable */
    scilinREG->SETINT = (0U << 26U)  /* Framing error */
                    | (0U << 25U)  /* Overrun error */
                    | (0U << 24U)  /* Parity error */
                    | (1U << 9U)  /* Receive */
                    | (0U << 1U)  /* Wakeup */
                    | (0U);  /* Break detect */

    /** - Finaly start SCILIN */
    scilinREG->GCR1 |= (1U << 7U);

    return RT_EOK;
}

static rt_err_t _control(struct rt_serial_device *serial, int cmd, void *arg)
{
    sciBASE_t *sci = (sciBASE_t*)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        sci->CLRINT = SCI_RX_INT;
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        sci->SETINT = SCI_RX_INT;
        break;
    }

    return RT_EOK;
}

static int _putc(struct rt_serial_device *serial, char c)
{
    sciBASE_t *sci = (sciBASE_t*)serial->parent.user_data;
    while ((sci->FLR & SCI_TX_INT) == 0U)
        ;
    sci->TD = c;
    return 1;
}

static int _getc(struct rt_serial_device *serial)
{
    sciBASE_t *sci = (sciBASE_t*)serial->parent.user_data;
    if (sci->FLR & (1<<9))
        return (sci->RD & 0x000000FFU);
    else
        return -1;
}

static const struct rt_uart_ops _sci_ops =
{
    _configure,
    _control,
    _putc,
    _getc,
};

static void _irq_wrapper(int vector, void *param)
{
    rt_hw_serial_isr((struct rt_serial_device*)param, RT_SERIAL_EVENT_RX_IND);
}

static struct rt_serial_device _sci2_serial;

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
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    _sci2_serial.ops    = &_sci_ops;
    _sci2_serial.config = config;

    rt_hw_serial_register(&_sci2_serial, "sci2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          (void*)scilinREG);

    rt_device_control(&_sci2_serial.parent, RT_DEVICE_CTRL_SET_INT, 0);
    rt_hw_interrupt_install(SCI_INT_VEC, _irq_wrapper, &_sci2_serial, "sci2");
    rt_hw_interrupt_umask(SCI_INT_VEC);
}

