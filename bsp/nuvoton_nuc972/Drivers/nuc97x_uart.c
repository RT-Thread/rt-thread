/*
 * File      : nuc97x_uart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2017/11/08     Urey			first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "nuc97x_conf.h"


#ifdef UART_DEBUG
#define UDEBUG          rt_kprintf
#else
#define UDEBUG(...)
#endif  /* UART_DEBUG */

#ifdef UART_FLOWCONTROL_DEBUG
#define FDEBUG          rt_kprintf
#else
#define FDEBUG(...)
#endif  /* UART_FLOWCONTROL_DEBUG */


INT UART_Configure(UART_TypeDef *UARTx,UART_Param *pParam)
{
    UINT32 u32Reg;
    /* Check UART channel */
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    /* Check the supplied parity */
    if ((pParam->ucParity != UA_PARITY_NONE) && (pParam->ucParity != UA_PARITY_EVEN) && (pParam->ucParity != UA_PARITY_ODD)
                    && (pParam->ucParity != (UA_PARITY_ODD | UA_PARITY_STICK))
                    && (pParam->ucParity != (UA_PARITY_EVEN | UA_PARITY_STICK)))
        return UART_ERR_PARITY_INVALID;

    /* Check the supplied number of data bits */
    if ((pParam->ucDataBits != UA_DATA_BITS_5) && (pParam->ucDataBits != UA_DATA_BITS_6)
                    && (pParam->ucDataBits != UA_DATA_BITS_7) && (pParam->ucDataBits != UA_DATA_BITS_8))
        return UART_ERR_DATA_BITS_INVALID;

    /* Check the supplied number of stop bits */
    if ((pParam->ucStopBits != UA_STOP_BITS_1) && (pParam->ucStopBits != UA_STOP_BITS_2))
        return UART_ERR_STOP_BITS_INVALID;

    /* Check the supplied number of trigger level bytes */
    if ((UARTx == UART1) || (UARTx == UART2) || (UARTx == UART4) || (UARTx == UART6) || (UARTx == UART8) || (UARTx == UARTA))
    {
        /* UART1,2,4,6,8,A */
        if ((pParam->ucRxTriggerLevel != UART_FCR_RFITL_1BYTE) && (pParam->ucRxTriggerLevel != UART_FCR_RFITL_4BYTES)
                        && (pParam->ucRxTriggerLevel != UART_FCR_RFITL_8BYTES)
                        && (pParam->ucRxTriggerLevel != UART_FCR_RFITL_14BYTES)
                        && (pParam->ucRxTriggerLevel != UART_FCR_RFITL_30BYTES)
                        && (pParam->ucRxTriggerLevel != UART_FCR_RFITL_46BYTES)
                        && (pParam->ucRxTriggerLevel != UART_FCR_RFITL_62BYTES))
            return UART_ERR_TRIGGERLEVEL_INVALID;
    }
    else
    {
        /* UART0,3,5,7,9 */
        if ((pParam->ucRxTriggerLevel != UART_FCR_RFITL_1BYTE) && (pParam->ucRxTriggerLevel != UART_FCR_RFITL_4BYTES)
                        && (pParam->ucRxTriggerLevel != UART_FCR_RFITL_8BYTES)
                        && (pParam->ucRxTriggerLevel != UART_FCR_RFITL_30BYTES))
            return UART_ERR_TRIGGERLEVEL_INVALID;
    }

    /* Enable UART clock */
    if (pParam->ucUartNo < UART_NUM)
    {
        outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0) | (1 << (16+pParam->ucUartNo)));
    }

    /* Reset TX/RX FIFOs */
    u32Reg = UARTx->FCR;
    UARTx->FCR = (u32Reg | (UART_FCR_TFR_Msk | UART_FCR_RFR_Msk));

    /* Setup baud rate */
    {
        UINT32 u32Baud_Div;
        UINT32 u32Clk = pParam->uFreq;
        UINT32 u32baudrate = pParam->uBaudRate;

        u32Baud_Div = UART_BAUD_MODE2_DIVIDER(u32Clk, u32baudrate);

        if(u32Baud_Div > 0xFFFF)
            u32Reg = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER(u32Clk, u32baudrate));
        else
            u32Reg = (UART_BAUD_MODE2 | u32Baud_Div);

        UARTx->BAUD = u32Reg;
    }

    /* Setup parity, data bits, and stop bits */
    UARTx->LCR = (pParam->ucParity | pParam->ucDataBits | pParam->ucStopBits);

    /* Setup Rx time out value */
    UARTx->TOR = 0x80+0x20;

    /* Setup FIFO trigger level */
    UARTx->FCR = pParam->ucRxTriggerLevel;

    return 0;
}

void UART_EnableInterrupt(UART_TypeDef *UARTx, UINT32 uVal)
{
    UARTx->IER |= uVal;
}

void UART_DisableInterrupt(UART_TypeDef *UARTx, UINT32 uVal)
{
    if (uVal == DISABLEALLIER)
        UARTx->IER = 0;
    else
        UARTx->IER &= ~uVal;
}

UINT8 UART_ReceiveData(UART_TypeDef *UARTx)
{
    /* Receive Data */
    return (UINT8) (UARTx->RBR_THR);
}

void UART_TransmitData(UART_TypeDef *UARTx,UINT8 dat)
{
    UARTx->RBR_THR = dat;
}


/******************************************************************************
 * RT-Thread interface
*******************************************************************************/

static rt_err_t nuc970_uart_configure   (struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t nuc970_uart_control     (struct rt_serial_device *serial, int cmd, void *arg);
static int      nuc970_uart_putc        (struct rt_serial_device *serial, char c);
static int      nuc970_uart_getc        (struct rt_serial_device *serial);
static void     nuc970_usart_isr        (int vector,void *param);

struct nuc970_uart
{
    UART_TypeDef*   UARTx;
    UART_Param      param;
    IRQn_Type       vector;
};

const struct rt_uart_ops nuc970_uart_ops =
{
    nuc970_uart_configure,
    nuc970_uart_control,
    nuc970_uart_putc,
    nuc970_uart_getc,
};


#if defined(BOARD_USING_UART0)
/* UART1 device driver structure */
struct nuc970_uart uart0 =
{
    .UARTx      = UART0,
    .param      =
    {
        .uFreq      = 12000000,
        .uBaudRate  = 115200,
        .ucUartNo   = 0,
        .ucDataBits = UA_DATA_BITS_8,
        .ucStopBits = UA_STOP_BITS_1,
        .ucParity   = UA_PARITY_NONE,
        .ucRxTriggerLevel = UART_FCR_RFITL_1BYTE,
    },
    .vector = UART0_IRQn,
};

struct rt_serial_device serial0;

#endif


void rt_hw_uart_init(void)
{
    struct nuc970_uart*     uart;
    struct rt_serial_device *serial;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#if defined(BOARD_USING_UART0)
    {
        serial  = &serial0;
        uart    = &uart0;

        /* enable UART0 clock */
        outpw(REG_CLK_PCLKEN0, inpw(REG_CLK_PCLKEN0) | 0x10000);

        /* GPE0, GPE1 */
        outpw(REG_SYS_GPE_MFPL, (inpw(REG_SYS_GPE_MFPL) & 0xffffff00) | 0x99);  // UART0 multi-function

        /* UART0 line configuration for (115200,n,8,1) */
        outpw(REG_UART0_LCR, inpw(REG_UART0_LCR) | 0x7);
        outpw(REG_UART0_BAUD, 0x30000066); /* 12MHz reference clock input, 115200 */

        /* Enable the UART0 Rx Interrupt */
//        outpw(REG_UART0_IER,UART_IER_RDA_IEN_Msk|UART_IER_RLS_IEN_Msk|UART_IER_RTO_IEN_Msk|UART_IER_BUF_ERR_IEN_Msk);

        config.baud_rate = BAUD_RATE_115200;

        serial->ops    = &nuc970_uart_ops;
        serial->config = config;

        /* register UART1 device */
        rt_hw_serial_register(serial, "uart0",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);

        /* Register the UART0 ISR */
        rt_hw_interrupt_install(UART0_IRQn, nuc970_usart_isr,
                               (void *)serial, "uart0isr");

        /* Set the irq and irq trigger level for UART0 */
        rt_hw_interrupt_set_priority(UART0_IRQn,IRQ_LEVEL_7);
        rt_hw_interrupt_set_type(UART0_IRQn,HIGH_LEVEL_SENSITIVE);

        /* Enable the IRQ for UART0 */
        rt_hw_interrupt_umask(UART0_IRQn);
    }
#endif
}



static rt_err_t nuc970_uart_configure   (struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct nuc970_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct nuc970_uart *)serial->parent.user_data;

    /* ÅäÖÃUART ²ÎÊý */
    uart->param.uBaudRate = cfg->baud_rate;
    switch (cfg->data_bits)
    {
        case DATA_BITS_8:
            uart->param.ucDataBits = UA_DATA_BITS_8;
            break;
        default:
            uart->param.ucDataBits = UA_DATA_BITS_8;
            break;
    }

    switch (cfg->stop_bits)
    {
        case STOP_BITS_1:
            uart->param.ucStopBits = UA_STOP_BITS_1;
            break;
        case STOP_BITS_2:
            uart->param.ucStopBits = UA_STOP_BITS_2;
            break;
        default:
            uart->param.ucStopBits = UA_STOP_BITS_1;
            break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        uart->param.ucParity = UA_PARITY_EVEN;
        break;
    case PARITY_EVEN:
        uart->param.ucParity = UA_PARITY_ODD;
        break;
    default:
        uart->param.ucParity = UA_PARITY_NONE;
        break;
    }

    UART_Configure(uart->UARTx,&uart->param);

    return RT_EOK;
}

static rt_err_t nuc970_uart_control     (struct rt_serial_device *serial, int cmd, void *arg)
{
    struct nuc970_uart* uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct nuc970_uart *)serial->parent.user_data;

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable interrupt */
        if (((rt_uint32_t) arg) & RT_DEVICE_FLAG_INT_RX)
            UART_DisableInterrupt(uart->UARTx,UART_IER_RDA_IEN_Msk);
        else if (((rt_uint32_t) arg) & RT_DEVICE_FLAG_INT_TX)
            UART_DisableInterrupt(uart->UARTx,UART_IER_THRE_IEN_Msk);
        break;
        /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable interrupt */
        if (((rt_uint32_t) arg) & RT_DEVICE_FLAG_INT_RX)
            UART_EnableInterrupt(uart->UARTx,UART_IER_RDA_IEN_Msk);
        else if (((rt_uint32_t) arg) & RT_DEVICE_FLAG_INT_TX)
            UART_EnableInterrupt(uart->UARTx,UART_IER_THRE_IEN_Msk);
        break;
    }

    return RT_EOK;
}

static int      nuc970_uart_putc        (struct rt_serial_device *serial, char c)
{
    struct nuc970_uart* uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct nuc970_uart *)serial->parent.user_data;

    while (uart->UARTx->FSR & UART_FSR_TX_FULL_Msk); //waits for TX_FULL bit is clear
    uart->UARTx->RBR_THR = c;
//    while(!(uart->UARTx->FSR & UART_FSR_TX_EMPTY_Msk)); // wait for TX_EMPTY
    return 1;
}

static int      nuc970_uart_getc        (struct rt_serial_device *serial)
{
    int ch;
    struct nuc970_uart* uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct nuc970_uart *)serial->parent.user_data;
    if (uart->UARTx->FSR & UART_FSR_RX_EMPTY_Msk)
    {
        return -1;
    }

    /* Read one byte */
    ch = uart->UARTx->RBR_THR;
    return (ch & 0xFF);
}

static void nuc970_usart_isr(int vector,void *param)
{
    struct rt_serial_device *serial;
    struct nuc970_uart *uart;
    UINT32 volatile uRegISR = 0, uRegFSR = 0;

    RT_ASSERT(param != RT_NULL);

    serial = (struct rt_serial_device *)param;
    uart = (struct nuc970_uart *)serial->parent.user_data;

    /* get FSR & ISR */
    uRegFSR = uart->UARTx->FSR;
    uRegISR = uart->UARTx->ISR;

    /* Clear the irq flags */
    if (uRegFSR & UART_SC_FSR_RX_OVER_ERETRY_Msk)
    {
        uart->UARTx->FSR = uRegFSR | UART_SC_FSR_RX_OVER_ERETRY_Msk;
    }

    if (uRegFSR & UART_FSR_PEF_Msk)
    {
        uart->UARTx->FSR = uRegFSR|UART_FSR_PEF_Msk;
    }

    if (uRegFSR & UART_FSR_FEF_Msk)
    {
        uart->UARTx->FSR = uRegFSR|UART_FSR_FEF_Msk;
    }

    if (uRegFSR & UART_FSR_BIF_Msk)
    {
        uart->UARTx->FSR = uRegFSR|UART_FSR_BIF_Msk;
    }

    /* Received Data Available interrupt */
    if( uRegISR & (UART_ISR_RDA_IF_Msk | UART_ISR_TOUT_IF_Msk))
    {
        if(serial->parent.open_flag & RT_DEVICE_FLAG_INT_RX)
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    /* TX empty interrupt, check LSR 4 kinds of error further */
    if(uRegISR & UART_ISR_THRE_IF_Msk)
    {
        if(serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX)
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
    }
}

