/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */


#include "drv_uart.h"
#include "fsl_uart.h"

static struct rt_serial_device _k64_serial;  //abstracted serial for RTT

struct k64_serial_device
{
    /* UART base address */
    UART_Type *baseAddress;

    /* UART IRQ Number */
    int irq_num;

    /* device config */
    struct serial_configure config;
};

//hardware abstract device
static struct k64_serial_device _k64_node =
{
    (UART_Type *)UART0,
    UART0_RX_TX_IRQn,
};

static rt_err_t _configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    unsigned int reg_C1 = 0,reg_C3 = 0,reg_C4 = 0,reg_BDH = 0,reg_BDL = 0,reg_S2 = 0,reg_BRFA=0;
    unsigned int cal_SBR = 0;
    UART_Type *uart_reg;

    /* ref : drivers\system_MK60F12.c Line 64 ,BusClock = 60MHz
     * calculate baud_rate
     */
    uart_reg = ((struct k64_serial_device *)serial->parent.user_data)->baseAddress;

    /*
     * set bit order
     */
    if (cfg->bit_order == BIT_ORDER_LSB)
        reg_S2 &= ~(UART_S2_MSBF_MASK<<UART_S2_MSBF_SHIFT);
    else if (cfg->bit_order == BIT_ORDER_MSB)
        reg_S2 |= UART_S2_MSBF_MASK<<UART_S2_MSBF_SHIFT;

    /*
     * set data_bits
     */
    if (cfg->data_bits == DATA_BITS_8)
        reg_C1 &= ~(UART_C1_M_MASK<<UART_C1_M_SHIFT);
    else if (cfg->data_bits == DATA_BITS_9)
        reg_C1 |= UART_C1_M_MASK<<UART_C1_M_SHIFT;

    /*
     * set parity
     */
    if (cfg->parity == PARITY_NONE)
    {
        reg_C1 &= ~(UART_C1_PE_MASK);
    }
    else
    {
        /* first ,set parity enable bit */
        reg_C1 |= (UART_C1_PE_MASK);

        /* second ,determine parity odd or even*/
        if (cfg->parity == PARITY_ODD)
            reg_C1 |= UART_C1_PT_MASK;
        if (cfg->parity == PARITY_EVEN)
            reg_C1 &= ~(UART_C1_PT_MASK);
    }

    /*
     * set NZR mode
     * not tested
     */
    if (cfg->invert != NRZ_NORMAL)
    {
        /* not in normal mode ,set inverted polarity */
        reg_C3 |= UART_C3_TXINV_MASK;
    }

    switch ((unsigned int)uart_reg)
    {
    /*
     * if you're using other board
     * set clock and pin map for UARTx
     */
    case UART0_BASE:
            /* calc SBR */
        cal_SBR = SystemCoreClock / (16 * cfg->baud_rate);

        /* check to see if sbr is out of range of register bits */
        if ((cal_SBR > 0x1FFF) || (cal_SBR < 1))
        {
            /* unsupported baud rate for given source clock input*/
            return -RT_ERROR;
        }

        /* calc baud_rate */
        reg_BDH = (cal_SBR & 0x1FFF) >> 8 & 0x00FF;
        reg_BDL = cal_SBR & 0x00FF;

        /* fractional divider */
        reg_BRFA = ((SystemCoreClock * 32) / (cfg->baud_rate * 16)) - (cal_SBR * 32);

        reg_C4 = (unsigned char)(reg_BRFA & 0x001F);

        SIM->SOPT5 &= ~ SIM_SOPT5_UART0RXSRC(0);
        SIM->SOPT5 |= SIM_SOPT5_UART0RXSRC(0);
        SIM->SOPT5 &= ~ SIM_SOPT5_UART0TXSRC(0);
        SIM->SOPT5 |= SIM_SOPT5_UART0TXSRC(0);

        // set UART0 clock
        // Enable UART gate clocking
        // Enable PORTE gate clocking
        CLOCK_EnableClock(kCLOCK_Uart0);
        CLOCK_EnableClock(kCLOCK_PortB);

        // set UART0 pin
        PORTB->PCR[16] &= ~(3UL <<  8);
        PORTB->PCR[16] |= (3UL <<  8);      // Pin mux configured as ALT3

        PORTB->PCR[17] &= ~(3UL <<  8);
        PORTB->PCR[17] |= (3UL <<  8);      // Pin mux configured as ALT3
        break;

    default:
        return -RT_ERROR;
    }

    uart_reg->BDH = reg_BDH;
    uart_reg->BDL = reg_BDL;
    uart_reg->C1 = reg_C1;
    uart_reg->C4 = reg_C4;
    uart_reg->S2 = reg_S2;

    uart_reg->S2  =  0;
    uart_reg->C3  =  0;

    uart_reg->RWFIFO = UART_RWFIFO_RXWATER(1);
    uart_reg->TWFIFO = UART_TWFIFO_TXWATER(0);

    uart_reg->C2  =  UART_C2_RE_MASK |    //Receiver enable
                     UART_C2_TE_MASK;     //Transmitter enable

    return RT_EOK;
}

static rt_err_t _control(struct rt_serial_device *serial, int cmd, void *arg)
{
    UART_Type *uart_reg;
    int uart_irq_num = 0;

    uart_reg = ((struct k64_serial_device *)serial->parent.user_data)->baseAddress;
    uart_irq_num = ((struct k64_serial_device *)serial->parent.user_data)->irq_num;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        uart_reg->C2 &= ~UART_C2_RIE_MASK;
        //disable NVIC
        NVIC->ICER[uart_irq_num / 32] = 1 << (uart_irq_num % 32);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        uart_reg->C2 |= UART_C2_RIE_MASK;
        //enable NVIC,we are sure uart's NVIC vector is in NVICICPR1
        NVIC->ICPR[uart_irq_num / 32] = 1 << (uart_irq_num % 32);
        NVIC->ISER[uart_irq_num / 32] = 1 << (uart_irq_num % 32);
        break;
    case RT_DEVICE_CTRL_SUSPEND:
        /* suspend device */
        uart_reg->C2  &=  ~(UART_C2_RE_MASK |    //Receiver enable
                            UART_C2_TE_MASK);     //Transmitter enable
        break;
    case RT_DEVICE_CTRL_RESUME:
        /* resume device */
        uart_reg->C2  =  UART_C2_RE_MASK |    //Receiver enable
                         UART_C2_TE_MASK;     //Transmitter enable
        break;
    }

    return RT_EOK;
}

static int _putc(struct rt_serial_device *serial, char c)
{
    UART_Type *uart_reg;
    uart_reg = ((struct k64_serial_device *)serial->parent.user_data)->baseAddress;

    while (!(uart_reg->S1 & UART_S1_TDRE_MASK));
    uart_reg->D = (c & 0xFF);
    return 1;
}

static int _getc(struct rt_serial_device *serial)
{
    UART_Type *uart_reg;
    uart_reg = ((struct k64_serial_device *)serial->parent.user_data)->baseAddress;

    if (uart_reg->S1 & UART_S1_RDRF_MASK)
        return (uart_reg->D);
    else
        return -1;
}

static const struct rt_uart_ops _k64_ops =
{
    _configure,
    _control,
    _putc,
    _getc,
};


void UART0_RX_TX_IRQHandler(void)
{
    rt_interrupt_enter();
    rt_hw_serial_isr((struct rt_serial_device*)&_k64_serial, RT_SERIAL_EVENT_RX_IND);
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
    config.bufsz     = RT_SERIAL_RB_BUFSZ;

    _k64_serial.ops    = &_k64_ops;
    _k64_serial.config = config;

    rt_hw_serial_register(&_k64_serial, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
                          (void*)&_k64_node);
}

void rt_hw_console_output(const char *str)
{
    while(*str != '\0')
    {
        if (*str == '\n')
            _putc(&_k64_serial,'\r');
        _putc(&_k64_serial,*str);
        str++;
    }
}
